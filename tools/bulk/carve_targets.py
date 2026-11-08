#!/usr/bin/env python3
"""Add a body for every control-transfer target that no row covers.

280 such targets exist: 22,029 call/jump targets, of which the ones that fall inside an existing
row are that row's labels, and the rest land in .text with no .pdata record at all. They decode as
complete little routines (`mov [rcx],rdx; mov rax,rcx; ret` followed by int3 padding), so the code
is there and a body is the honest way to make it callable.

Nothing is invented: each body is exactly the instructions capstone decodes from the target until
the routine ends (a ret, or a transfer followed by padding), formatted in the syntax lift.py parses.
A carve stops early rather than swallow another carved target or an existing row.
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
MAX_BYTES = 0x200


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True
    funcs = {x['a']: dict(x) for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    for k, v in load('rows_fixed.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))

    import bisect
    spans = sorted((v['a'], v['b']) for v in funcs.values())
    starts = [s0 for s0, _ in spans]

    def inside(t):
        i = bisect.bisect_right(starts, t) - 1
        return i >= 0 and spans[i][0] <= t < spans[i][1]

    targets = set()
    for a in sorted(funcs):
        f = funcs[a]
        off = a - BASE + TEXT_OFF
        for ins in md.disasm(image[off:off + max(0, f['b'] - a)], a):
            if ins.mnemonic.split()[0] in ('call', 'jmp') or ins.mnemonic.startswith('j'):
                for op in ins.operands:
                    if op.type == capstone.x86.X86_OP_IMM:
                        targets.add(op.imm)
    # a vtable slot is the DLL's own declaration of a function entry point, so a slot with no row
    # is a missing body on the same footing as a call target
    vt = json.load(open(os.path.join(BULK, 'class_vtables.json')))
    targets |= {int(a, 16) for v in vt.values() for a in v['slots']}
    missing = sorted(t for t in targets if not inside(t))
    missing_set = set(missing)

    extra = load('extra_bodies.json')
    added = refused = 0
    for t in missing:
        off = t - BASE + TEXT_OFF
        addr, text = [], []
        end = t
        for ins in md.disasm(image[off:off + MAX_BYTES], t):
            addr.append(ins.address)
            text.append(fmt(ins))
            end = ins.address + ins.size
            nxt = ins.address + ins.size
            if nxt in missing_set and nxt != t:
                break                       # do not swallow another routine's entry
            if inside(nxt):
                break                       # do not walk into an indexed row
            if ins.mnemonic == 'ret' or ins.mnemonic.startswith('ret'):
                break
        if not text:
            refused += 1
            continue
        key = '0x%x' % t
        if key in funcs:
            continue
        extra[key] = {'a': t, 'b': end, 'addr': addr, 'text': text, 'src': 'carve'}
        added += 1
    json.dump(extra, open(os.path.join(BULK, 'extra_bodies.json'), 'w'), indent=1)
    print('targets with no row:', len(missing), '| bodies carved:', added, '| unreadable:', refused)


if __name__ == '__main__':
    main()
