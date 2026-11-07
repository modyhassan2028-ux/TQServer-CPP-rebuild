#!/usr/bin/env python3
"""Pull an unindexed routine out of the DLL by disassembling it, in the shape funcs.json uses.

Some helpers (the out-of-line tree rotations, for instance) have no .pdata row, so they are not in the index.
This reads the raw bytes with objdump, stops at the first `ret` that is followed by padding, and normalises
the operands: `[rip+0x..]` becomes `[rip@<absolute>]` because the lifter needs the target, not the encoding.
"""
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'


def disasm(start, limit=0x200):
    out = subprocess.run(['objdump', '-d', '-M', 'intel', '--start-address=0x%x' % start,
                          '--stop-address=0x%x' % (start + limit), DLL],
                         capture_output=True, text=True).stdout
    rows = []
    for line in out.splitlines():
        m = re.match(r'^\s+([0-9a-f]+):\t([0-9a-f ]{2,})\t(.*)$', line)
        if m:
            rows.append([int(m.group(1), 16), len(m.group(2).split()), m.group(3).strip()])
    return rows


def normalise(rows):
    body = []
    for a, size, text in rows:
        t = text.replace('\t', ' ')
        t = re.sub(r'\s+', ' ', t).strip()
        # objdump prints the absolute target for direct branches already
        m = re.search(r'\[rip\+(0x[0-9a-f]+)\]', t)
        if m:
            target = a + size + int(m.group(1), 16)
            t = t.replace(m.group(0), '[rip@0x%x]' % target)
        t = re.sub(r'^rex(\.[WRX]+)? ', '', t)
        t = t.split('#')[0].strip()
        t = t.replace('movabs ', 'mov ')
        body.append((a, size, t))
    return body


def build(start):
    rows = normalise(disasm(start))
    if not rows or rows[0][0] != start:
        return None
    keep = []
    for i, (a, size, t) in enumerate(rows):
        if t in ('int3',) or t.startswith('nop'):
            break
        keep.append((a, size, t))
    # trim anything after the final ret
    last = max(i for i, (_, _, t) in enumerate(keep) if t.split()[0] == 'ret')
    keep = keep[:last + 1]
    return {'a': start, 'b': keep[-1][0] + keep[-1][1],
            'addr': [a for a, _, _ in keep], 'text': [t for _, _, t in keep]}


def main():
    extra_path = os.path.join(REPO, 'tools/bulk/extra_bodies.json')
    extra = json.load(open(extra_path)) if os.path.exists(extra_path) else {}
    for a in sys.argv[1:]:
        addr = int(a, 16)
        b = build(addr)
        if not b:
            print('0x%x: could not read' % addr)
            continue
        extra['0x%x' % addr] = b
        print('0x%x: %d instructions (%d bytes)' % (addr, len(b['text']), b['b'] - b['a']))
    json.dump(extra, open(extra_path, 'w'), indent=1)


if __name__ == '__main__':
    main()
