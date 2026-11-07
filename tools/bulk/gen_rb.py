#!/usr/bin/env python3
"""Family RB — the ordered-tree insert + rebalance, 28 more instantiations.

The reference transcription of 0x141727e60 lives in modules/syndicate/src/synrbinsert.h and is proven by
tests/cqbase_thunks_rb_test.cpp. Every other body of the family has the same 220 instructions in the same order
(that is how they were grouped); only three things differ:

    the capacity limit   (insn 11)
    the node factory     (insn 35)
    the colour offset C  (insns 63,70,72,73,76,107,110,137,139,140,143,174,177,204,208)  with the nil mark at C+1

So this generator takes the proven reference text, substitutes those three values per body, and refuses any body
whose branch instructions do not land on exactly the same instruction indices as the reference, or whose colour
and nil offsets are not consistent everywhere they appear.
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
REF_H = os.path.join(REPO, 'modules/syndicate/src/synrbinsert.h')
REF_ADDR = 0x141727e60

# expected branch landing indices, read off the reference listing (insn -> insn)
WANT_BRANCH = {13: 29, 40: 47, 46: 60, 48: 55, 52: 60, 54: 60, 58: 60, 64: 206, 68: 136, 71: 80,
               79: 202, 81: 106, 88: 90, 95: 98, 97: 104, 100: 103, 102: 104, 118: 120, 124: 127,
               126: 133, 129: 132, 131: 133, 135: 202, 138: 147, 146: 202, 148: 173, 155: 157,
               162: 165, 164: 171, 167: 170, 169: 171, 185: 187, 191: 194, 193: 200, 196: 199,
               198: 200, 205: 65}
COLOR_IDX = [63, 70, 72, 73, 76, 107, 110, 137, 139, 140, 143, 174, 177, 204, 208]
NIL_IDX = [87, 117, 154, 184]


def reference_body():
    txt = open(REF_H).read()
    start = txt.index('inline void* SynRbInsert_141727e60(')
    end = txt.index('#undef RB_Q')
    body = txt[start:end]
    return body.rstrip()


def body_of(f):
    return f['text'], {a: i for i, a in enumerate(f['addr'])}


def analyse(f):
    t, idx = body_of(f)
    if len(t) != 220:
        return None, 'length %d != 220' % len(t)
    for insn, want in WANT_BRANCH.items():
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t[insn])
        if not m:
            return None, 'insn %d is not a branch' % insn
        if idx.get(int(m.group(1), 16)) != want:
            return None, 'insn %d lands on %s, expected %d' % (insn, idx.get(int(m.group(1), 16)), want)
    cols = {int(re.findall(r'\+0x([0-9a-f]+)\]', t[i])[0], 16) for i in COLOR_IDX}
    if len(cols) != 1:
        return None, 'colour offset is not consistent: %s' % sorted(hex(c) for c in cols)
    C = cols.pop()
    nils = {int(re.findall(r'\+0x([0-9a-f]+)\]', t[i])[0], 16) for i in NIL_IDX}
    if nils != {C + 1}:
        return None, 'nil offset %s is not colour+1' % sorted(hex(n) for n in nils)
    limit = t[11].split(',')[-1].strip()
    factory = int(t[35].split()[-1], 16)
    return {'a': f['a'], 'C': C, 'N': C + 1, 'limit': limit, 'factory': factory}, None


def main():
    funcs = json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))
    blob = ''
    for root, _d, files in os.walk(os.path.join(REPO, 'modules')):
        for n in files:
            if n.endswith(('.cpp', '.h')):
                if n in ('synrbinsert.h', 'synrbinsert.cpp', 'synrbinsert_family.h', 'synrbinsert_family.cpp'):
                    continue
                blob += open(os.path.join(root, n), errors='ignore').read().lower()
    blob += open(REF_H, errors='ignore').read().lower()

    hits, rejected = [], []
    for f in funcs:
        if ('0x%x' % f['a']) in blob:
            continue
        info, why = analyse(f)
        if info is None:
            if 'length' not in why and 'lands on' not in why and 'consistent' not in why and 'colour+1' not in why:
                continue
            if len(f['text']) == 220 or len(f['text']) in (78, 86):
                pass
            continue
        hits.append(info)

    ref = reference_body()
    hdr = ['// synrbinsert_family.h — the remaining instantiations of the routine transcribed in synrbinsert.h.',
           '// Generated from the proven reference text by tools/bulk/gen_rb.py; only the capacity limit, the node',
           '// factory and the colour/nil offsets differ per body. Do not hand edit.',
           '#pragma once',
           '#include <cstdint>',
           '#include "synrbinsert.h"',
           '',
           '#define RB_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))',
           '#define RB_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))',
           '',
           'namespace tq {', '']
    src = ['#include "synrbinsert_family.h"', '', 'namespace tq {', '']
    for h in hits:
        tag = '%x' % h['a']
        hdr += ['extern void* (*g_fnRB_%s_factory)(void*, void*, void*, void*, const uint32_t*, uint8_t);' % tag,
                'extern void (*g_fnRB_%s_throw)(void);' % tag]
        src += ['void* (*g_fnRB_%s_factory)(void*, void*, void*, void*, const uint32_t*, uint8_t) = nullptr;' % tag,
                'void (*g_fnRB_%s_throw)(void) = nullptr;' % tag]
    hdr.append('')
    for h in hits:
        tag = '%x' % h['a']
        txt = ref
        txt = txt.replace('SynRbInsert_141727e60', 'SynRbInsert_%s' % tag)
        txt = txt.replace('g_fnRB_141726e10', 'g_fnRB_%s_factory' % tag)
        txt = txt.replace('g_fnRB_1417f3154', 'g_fnRB_%s_throw' % tag)
        txt = txt.replace('0x3ffffffffffffffeULL', '%sULL' % h['limit'])
        txt = txt.replace('0x3ffffffffffffffe', h['limit'])   # the same value quoted in the insn 11 comment
        txt = txt.replace('0x1c', '0x%x' % h['C'])
        txt = txt.replace('0x1d', '0x%x' % h['N'])
        hdr += [txt, '']
    hdr += ['}  // namespace tq', '', '#undef RB_Q', '#undef RB_B', '']
    open(os.path.join(REPO, 'modules/syndicate/src/synrbinsert_family.h'), 'w').write('\n'.join(hdr))
    src += ['', '}  // namespace tq', '']
    open(os.path.join(REPO, 'modules/syndicate/src/synrbinsert_family.cpp'), 'w').write('\n'.join(src))

    # one battery per body, reusing the same harness shape as the reference test
    man = [{'a': h['a'], 'C': h['C'], 'N': h['N'], 'limit': h['limit'], 'factory': h['factory']} for h in hits]
    json.dump(man, open(os.path.join(REPO, 'tools/bulk/manifest_rb.json'), 'w'), indent=1)
    print('family RB: %d bodies' % len(hits))
    print('  colour offsets', sorted({hex(h['C']) for h in hits}))
    print('  limits', sorted({h['limit'] for h in hits}))
    print('  factories', len({h['factory'] for h in hits}))


if __name__ == '__main__':
    main()
