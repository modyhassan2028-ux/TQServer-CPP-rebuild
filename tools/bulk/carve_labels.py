#!/usr/bin/env python3
"""Add entry points for branches that leave their row.

A function is sometimes split across .pdata records, so a conditional branch can land in the middle
of another record. The lifter refuses such a branch rather than drop the other arm, which is right:
the target needs a body of its own first.

This carves a body at exactly the targets that block a row, decoding from the target to the end of
the record that contains it (or to its first ret). Only blocked targets are carved, so the module
does not fill up with an entry point for every loop label.
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import capstone  # noqa: E402
from fix_rows import fmt, load  # noqa: E402

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141721000
TEXT_OFF = 0x400


def rows():
    funcs = {x['a']: dict(x) for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    for k, v in load('rows_fixed.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    return funcs


def main():
    import bisect
    import lift as L

    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True
    funcs = rows()
    spans = sorted((v['a'], v['b']) for v in funcs.values())
    starts = [s0 for s0, _ in spans]

    def containing(t):
        i = bisect.bisect_right(starts, t) - 1
        return spans[i] if i >= 0 and spans[i][0] <= t < spans[i][1] else None

    wanted = set()
    for a in sorted(funcs):
        try:
            L.lift(a, funcs)
        except BaseException as ex:
            msg = str(ex) or type(ex).__name__
            if 'leaves the row' not in msg and 'branch target has no body' not in msg:
                continue
            tb = ex.__traceback__
            bad = '?'
            while tb:
                if 'ins' in tb.tb_frame.f_locals:
                    bad = tb.tb_frame.f_locals['ins']
                tb = tb.tb_next
            import re
            m = re.search(r'0x([0-9a-f]+)$', str(bad))
            if m:
                wanted.add(int(m.group(1), 16))

    extra = load('extra_bodies.json')
    added = 0
    skipped = []
    for t in sorted(wanted):
        if t in funcs:
            continue
        box = containing(t)
        # a target outside every row is a cold block: decode it from the target with a bounded window
        limit = max(0, box[1] - t) if box else 0x100
        off = t - BASE + TEXT_OFF
        addr, text, end = [], [], t
        for ins in md.disasm(image[off:off + limit], t):
            addr.append(ins.address)
            text.append(fmt(ins))
            end = ins.address + ins.size
            if ins.mnemonic == 'ret' or ins.mnemonic.startswith('ret'):
                break
        if not text:
            skipped.append((t, 'undecodable'))
            continue
        extra['0x%x' % t] = {'a': t, 'b': end, 'addr': addr, 'text': text, 'src': 'label'}
        added += 1
        funcs[t] = extra['0x%x' % t]
    json.dump(extra, open(os.path.join(BULK, 'extra_bodies.json'), 'w'), indent=1)
    print('blocked branch targets:', len(wanted), '| entry points added:', added,
          '| skipped:', len(skipped))
    for t, why in skipped[:6]:
        print('   0x%x: %s' % (t, why))


if __name__ == '__main__':
    main()
