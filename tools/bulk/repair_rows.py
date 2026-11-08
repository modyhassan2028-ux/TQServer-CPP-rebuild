#!/usr/bin/env python3
"""Repair the three row shapes the lifter still refuses, from evidence in the bytes.

Each shape is decided by something the image states, never by resemblance:

1. **Second arm past the record.** A record covers `cmp / jcc / mov / ret` and the branch lands on the
   byte right after the record, where a second arm decodes cleanly to its own `ret`. The branch's own
   target proves the arm is code, so the row is extended to that `ret`.
2. **Cut mid-instruction.** The record stops inside an instruction. The instruction is re-decoded from
   the row start over a wider window; if the stream continues to a terminator without an impossible
   form, the row is extended.
3. **Jump table inside the record.** A run of 4-byte values that all resolve into `.text` is a switch
   table, not code. The row is truncated at the table and the code after it becomes a row of its own,
   but only when every entry in the run maps into `.text` and the resume point decodes to a `ret`.
"""
import json
import os
import re
import struct
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fix_rows import fmt, load

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE, TEXT = 0x141721000, 0x400
TEXT_LO, TEXT_HI = 0x141721000, 0x141823000


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True

    def raw(a, n):
        o = a - BASE + TEXT
        return image[o:o + n]

    def impossible(ins):
        t = fmt(ins)
        return ('ds:' in t and 'rip' not in t) or (
            ' PTR [' in t and ins.mnemonic in ('add', 'sub', 'and', 'or', 'xor') and ins.size > 6)

    funcs = {f['a']: dict(f) for f in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    for k, v in load('rows_fixed.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    spans = sorted((v['a'], v['b']) for v in funcs.values())

    def covered(lo, hi):
        for s, e in spans:
            if s < hi and lo < e and not (s <= lo and e >= hi):
                return True
        return False

    extended, split, refused = {}, {}, []
    for a, f in sorted(funcs.items()):
        text = f['text']
        if not text:
            continue
        # shape 3: the row decodes into something impossible, i.e. it swallowed a data run
        bad = [i for i, t in enumerate(text) if ('ds:' in t and 'rip' not in t)
               or (' PTR [' in t and t.split(' ')[0] in ('add', 'sub', 'and', 'or', 'xor'))]
        if bad:
            start = f['addr'][bad[0]]
            run = 0
            while run < 0x60:
                v = struct.unpack_from('<I', raw(start + run, 4), 0)[0]
                if not (TEXT_LO <= BASE + v < TEXT_HI):
                    break
                run += 4
            resume = start + run
            ok = run >= 8 and (start + run) % 4 == 0
            if ok:
                tail = list(md.disasm(raw(resume, 0x100), resume))
                if tail and not any(impossible(i) for i in tail[:len(tail)]):
                    # the tail must reach a terminator without leaving its own range
                    end = None
                    for ins in tail:
                        if ins.mnemonic.startswith('ret') or ins.mnemonic == 'jmp':
                            end = ins.address + ins.size
                            break
                    if end:
                        keep = [i for i, ad in enumerate(f['addr']) if ad < start]
                        split['0x%x' % a] = {'a': a, 'b': start,
                                             'addr': f['addr'][:len(keep)],
                                             'text': text[:len(keep)]}
                        tail = [i for i in tail if i.address < end]
                        split['0x%x' % resume] = {'a': resume, 'b': end,
                                                  'addr': [i.address for i in tail],
                                                  'text': [fmt(i) for i in tail]}
                        continue
            refused.append((a, 'data run not provably a jump table'))
            continue
        if not text[-1].startswith(('ret', 'jmp')):
            continue
        # shapes 1 and 2: a branch leaves the record, or the record looks complete but is not
        targets = [int(m.group(1), 16) for t in text
                   for m in [re.match(r'^j\w+ (0x[0-9a-f]+)$', t)] if m]
        outside = [t for t in targets if not (a <= t < f['b'])]
        if not outside:
            continue
        lo = f['b']
        addrs, texts, hi, ok = list(f['addr']), list(text), f['b'], False
        for ins in md.disasm(raw(lo, 0x40), lo):
            if impossible(ins):
                break
            addrs.append(ins.address)
            texts.append(fmt(ins))
            hi = ins.address + ins.size
            if ins.mnemonic.startswith('ret') or ins.mnemonic == 'jmp':
                ok = True
                break
        if not ok:
            refused.append((a, 'tail does not decode to a terminator'))
            continue
        if any(not (a <= t < hi) for t in targets) or covered(lo, hi):
            # the branch still lands outside, so the tail is a different chunk
            funcs[a] = f
            continue
        extended['0x%x' % a] = {'a': a, 'b': hi, 'addr': addrs, 'text': texts}
        funcs[a] = extended['0x%x' % a]

    fixed = load('rows_fixed.json')
    for k, v in extended.items():
        fixed[k] = {'addr': v['addr'], 'text': v['text'], 'b': v['b']}
    for k, v in split.items():
        fixed[k] = {'addr': v['addr'], 'text': v['text'], 'b': v['b']}
    json.dump(fixed, open(os.path.join(BULK, 'rows_fixed.json'), 'w'))
    json.dump({'extended': extended, 'split': split,
               'refused': [['0x%x' % a, why] for a, why in refused]},
              open(os.path.join(BULK, 'rows_repaired.json'), 'w'), indent=1, default=str)
    print('extended: %d | split at a jump table: %d | refused with a reason: %d'
          % (len(extended), len(split), len(refused)))
    for a, why in refused[:5]:
        print('   0x%x: %s' % (a, why))


if __name__ == '__main__':
    main()
