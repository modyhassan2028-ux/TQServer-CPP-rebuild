#!/usr/bin/env python3
"""Give every row the end its own bytes call for.

A `.pdata` record can stop before the function does: the next chunk then belongs to the same function
and control simply falls into it. Lifting such a row produces a body that runs off its end, which is
undefined behaviour and cannot match the original. So a row whose last instruction is neither `ret`
nor a jump is extended by decoding forward until one appears.

The extension is only accepted when it is provable: the bytes must decode cleanly the whole way (no
impossible operand, which is how data reads in this image) and the extension must not overlap another
row, because then the tail is a separate chunk that some branch owns.
"""
import json
import os
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fix_rows import fmt, load

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE, TEXT = 0x141721000, 0x400
CAP = 0x400          # a chunk longer than this is not a chunk any more; refuse instead of guessing


def impossible(ins):
    """the shapes an instruction can never take, i.e. what data looks like to the decoder"""
    text = fmt(ins)
    if 'ds:' in text and 'rip' not in text:
        return True
    if ' PTR [' in text and ins.mnemonic in ('add', 'sub', 'and', 'or', 'xor') and ins.size > 6:
        return True
    return False


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True
    funcs = {f['a']: dict(f) for f in load('funcs.json')}
    extra = load('extra_bodies.json')
    for k, v in extra.items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    for k, v in load('rows_fixed.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    spans = sorted((v['a'], v['b']) for v in funcs.values())

    def covered(lo, hi):
        for s, e in spans:
            if s < hi and lo < e and not (s <= lo and e >= hi):
                return True
        return False

    extended, refused_overlap, refused_decode = {}, 0, 0
    for a, f in sorted(funcs.items()):
        if not f['text'] or f['text'][-1].startswith(('ret', 'jmp')):
            continue
        lo, hi = f['b'], f['b']
        addrs, texts = list(f['addr']), list(f['text'])
        ok = False
        while hi - lo < CAP:
            ins = next(md.disasm(image[hi - BASE + TEXT:hi - BASE + TEXT + 15], hi), None)
            if ins is None or impossible(ins):
                break
            addrs.append(ins.address)
            texts.append(fmt(ins))
            hi = ins.address + ins.size
            if ins.mnemonic.startswith('ret') or ins.mnemonic == 'jmp':
                ok = True
                break
        if not ok:
            refused_decode += 1
            continue
        # an extension is only valid if the row is still self-consistent: every branch the extended
        # body contains must land inside it, or the tail belonged to another chunk after all
        import re as _re
        stray = None
        for t in texts:
            m = _re.match(r'^j\w+ (0x[0-9a-f]+)$', t)
            if m and not (a <= int(m.group(1), 16) < hi):
                stray = int(m.group(1), 16)
                break
        if stray is not None and stray not in funcs:
            refused_overlap += 1
            continue
        if covered(lo, hi):
            refused_overlap += 1
            continue
        new = dict(f, addr=addrs, text=texts, b=hi)
        extended['0x%x' % a] = new
        funcs[a] = new

    json.dump(extended, open(os.path.join(BULK, 'rows_extended.json'), 'w'), indent=1)
    # the lifter and the ledger read rows_fixed.json, so the extensions are merged there as well
    fixed = load('rows_fixed.json')
    for k, v in extended.items():
        fixed[k] = {'addr': v['addr'], 'text': v['text'], 'b': v['b']}
    json.dump(fixed, open(os.path.join(BULK, 'rows_fixed.json'), 'w'))
    print('rows ending without a terminator: %d' % (len(extended) + refused_overlap + refused_decode))
    print('   extended to a real end: %d' % len(extended))
    print('   left alone, tail is another chunk: %d' % refused_overlap)
    print('   left alone, bytes stop decoding: %d' % refused_decode)


if __name__ == '__main__':
    main()
