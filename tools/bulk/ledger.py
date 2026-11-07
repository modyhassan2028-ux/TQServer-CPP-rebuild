#!/usr/bin/env python3
"""The porting ledger. A row counts as ported only when the module actually *defines* it.

Three rules, from strictest to loosest, are reported together because the repo carries two naming
conventions from different sessions:

  authoritative  address listed in a tools/bulk/manifest_*.json, or in a generated family header
                 (SynLift_<addr>, SynThkB_<addr>, SynProbeGX_<addr>, ...). Exact, but blind to the
                 hand-written modules from earlier sessions.
  header-comment the address appears on a code line with '(' , or on a `// 0x<addr>` line that is
                 followed within two lines by a definition. Catches the hand-written modules;
                 still rejects prose mentions such as "// -- 0x141727640 - walk from ...".
  loose          any mention at all. Kept only to show how much a comment can inflate the count.
"""
import glob
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def main():
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    routines = json.load(open(os.path.join(REPO, 'tools/bulk/routines.json')))

    auth = set()
    for p in glob.glob(os.path.join(REPO, 'tools/bulk/manifest_*.json')):
        try:
            for h in json.load(open(p)):
                if isinstance(h, dict) and 'a' in h:
                    auth.add(h['a'])
        except Exception:
            pass
    for p in glob.glob(os.path.join(REPO, 'modules/syndicate/src/*.h')):
        text = open(p, errors='ignore').read()
        for a in re.findall(r'_([0-9a-f]{6,})\(', text):
            auth.add(int(a, 16))

    hdr = set()
    loose_text = []
    for p in glob.glob(os.path.join(REPO, 'modules/**/*.cpp'), recursive=True) + \
             glob.glob(os.path.join(REPO, 'modules/**/*.h'), recursive=True):
        L = [l.rstrip('\n') for l in open(p, errors='ignore')]
        for i, ln in enumerate(L):
            s, low = ln.strip(), ln.lower()
            loose_text.append(low)
            for m in re.finditer(r'0x([0-9a-f]{6,})', low):
                a = int(m.group(1), 16)
                if a not in funcs:
                    continue
                if not s.startswith('//'):
                    if '(' in s:
                        hdr.add(a)
                else:
                    nxt = ' '.join(x.strip() for x in L[i + 1:i + 3])
                    if '(' in nxt or '{' in nxt or '=' in nxt:
                        hdr.add(a)
    loose = set()
    blob = '\n'.join(loose_text)
    for a in funcs:
        if ('0x%x' % a) in blob:
            loose.add(a)

    total_ins = sum(len(x['text']) for x in funcs.values())
    for name, have in (('authoritative', auth), ('header-comment', hdr), ('loose', loose)):
        have = have & set(funcs)
        rows = len(have)
        done = sum(1 for r in routines if all(a in have for a in r['rows']))
        ins = sum(len(funcs[a]['text']) for a in have)
        print('%-15s rows %5d/%d | routines %4d/%d (%.1f%%) | insns %6d/%d (%.1f%%)'
              % (name, rows, len(funcs), done, len(routines), 100.0 * done / len(routines),
                 ins, total_ins, 100.0 * ins / total_ins))


if __name__ == '__main__':
    main()
