#!/usr/bin/env python3
"""Transcribe four more repeated shapes of NpcServer.exe 0x140080000..0x140090000.

Each body is read from its own decompiled text and every constant (element size, shift, member offset, comparison
order) is taken from that text. A body that does not match a shape exactly is skipped and reported.

Shapes:
  alloc-raw       the over-allocation guard and the raw block request   (operator_new)
  memmove-forward the forward move over a range of elements            (memmove_s)
  iterator-bounds the three-way range check on a size word             (vector::insert)
  position-build  the guarded position pair built from a size word
"""
import os, re, sys, json

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
OUT_H = 'modules/npcserver/unattributed/stl-shapes.h'
OUT_C = 'modules/npcserver/unattributed/stl-shapes.cpp'
MANIFEST = '/tmp/stl_shapes.json'
LO, HI = '140080000', '140090000'


def bodies():
    src = open(DECOMP, errors='ignore').read()
    out = {}
    for part in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
        part = part.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', part)
        if m and LO <= m.group(1)[4:] < HI:
            out[m.group(1)] = part.strip()
    return out


def flat(t):
    return re.sub(r'\s+', ' ', t).strip()


def port(body):
    f = flat(body)

    # ---- alloc-raw: guard against size_t overflow, then ask for nCount * ELEM
    if 'std::bad_alloc::vftable' in f and '_CxxThrowException' in f:
        th = re.search(r'ZEXT816\(0xffffffffffffffff\)\) / auVar\d,0\) < (0x[0-9a-f]+)\)', f)
        op = re.search(r'operator_new\(param_(\d)(?: (<<) (0x[0-9a-f]+|\d+)| \* (0x[0-9a-f]+|\d+))\); return; \}$', f)
        if th and op:
            limit = int(th.group(1), 16)
            pidx = int(op.group(1))
            def num(s):
                return int(s, 16) if s.lower().startswith('0x') else int(s)
            if op.group(2):                       # shift form
                sh = num(op.group(3))
                elem = 1 << sh
                expr = 'nCount << %d' % sh
            else:
                elem = num(op.group(4))
                expr = 'nCount * %d' % elem
            if limit != elem:
                return None                       # the guard and the request disagree: not this shape
            lines = ['    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x%Xull) {' % elem,
                     '        throw std::bad_alloc();',
                     '    }',
                     '    g_pfnNpcOperatorNew((long long)(%s));' % expr]
            params = 'unsigned long long nCount' if pidx == 1 else 'void* pAllocator, unsigned long long nCount'
            pre = [] if pidx == 1 else ['    (void)pAllocator;']
            return ('void', params, pre + lines, 'alloc-raw', {'elem': elem, 'pidx': pidx})

    # ---- memmove-forward: (last - first) >> SHIFT elements of ELEM bytes, moved forward
    m = re.fullmatch(r'void \* FUN_[0-9a-f]{9}\(void \*param_1,longlong param_2,void \*param_3\) \{ rsize_t _DstSize; '
                     r'longlong lVar1; lVar1 = param_2 - \(longlong\)param_1 >> (\d); _DstSize = lVar1 \* (\d+); '
                     r'if \(lVar1 != 0\) \{ memmove_s\(param_3,_DstSize,param_1,_DstSize\); \} '
                     r'return \(void \*\)\(_DstSize \+ \(longlong\)param_3\); \}', f)
    if m:
        shift, elem = int(m.group(1)), int(m.group(2))
        assert (1 << shift) == elem, (shift, elem)
        lines = ['    long long nCount = nLast - (long long)pFirst >> %d;' % shift,
                 '    size_t cbBytes = (size_t)nCount * %d;' % elem,
                 '    if (nCount != 0) {',
                 '        g_pfnNpcMemmoveS(pDest, cbBytes, pFirst, cbBytes);',
                 '    }',
                 '    return (void*)((long long)cbBytes + (long long)pDest);']
        return ('void*', 'void* pFirst, long long nLast, void* pDest', lines, 'memmove-forward',
                {'shift': shift, 'elem': elem})

    # ---- iterator-bounds: *p = 0; guard (src null OR n < src[lo] OR src[hi] < n); copy the word and the position
    m = re.fullmatch(r'undefined8 \* FUN_[0-9a-f]{9}\(undefined8 \*param_1,ulonglong param_2,undefined8 \*param_3\) '
                     r'\{ undefined8 uVar1; \*param_1 = 0; if \(\(\(param_3 == \(undefined8 \*\)0x0\) \|\| '
                     r'\(param_2 < \(ulonglong\)param_3\[(\d+)\]\)\) \|\| \(\(ulonglong\)param_3\[(\d+)\] < param_2\)\) '
                     r'\{ _invalid_parameter_noinfo\(\); \} uVar1 = \*param_3; param_1\[1\] = param_2; \*param_1 = uVar1; '
                     r'return param_1; \}', f)
    if m:
        lo, hi = int(m.group(1)), int(m.group(2))
        lines = ['    pOut[0] = 0;',
                 '    if (pSource == nullptr || nPosition < pSource[%d] || pSource[%d] < nPosition) {' % (lo, hi),
                 '        NpcInvalidParameter();',
                 '    }',
                 '    pOut[1] = nPosition;',
                 '    pOut[0] = pSource[0];',
                 '    return pOut;']
        return ('unsigned long long*', 'unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource',
                lines, 'iterator-bounds', {'elem': lo, 'pidx': hi})

    # ---- position-build: take a size word out of the container, guard the pair order, build the pair
    m = re.fullmatch(r'undefined8 \* FUN_[0-9a-f]{9}\(undefined8 \*param_1,undefined8 \*param_2\) '
                     r'\{ ulonglong uVar1; undefined8 uVar2; uVar1 = param_1\[(\d)\]; \*param_2 = 0; if '
                     r'\((\(ulonglong\)param_1\[(\d)\] < uVar1|uVar1 < \(ulonglong\)param_1\[(\d)\])\) '
                     r'\{ _invalid_parameter_noinfo\(\); \} uVar2 = \*param_1; param_2\[1\] = uVar1; \*param_2 = uVar2; '
                     r'return param_2; \}', f)
    if m:
        word, other = int(m.group(1)), int(m.group(3) if m.group(3) else m.group(4))
        order = 'lt' if m.group(3) else 'gt'      # lt: pSource[other] < uVar1 ; gt: uVar1 < pSource[other]
        cond = ('(unsigned long long)pSource[%d] < nWord' % other) if order == 'lt' else \
               ('nWord < (unsigned long long)pSource[%d]' % other)
        lines = ['    unsigned long long nWord = pSource[%d];' % word,
                 '    pOut[0] = 0;',
                 '    if (%s) {' % cond,
                 '        NpcInvalidParameter();',
                 '    }',
                 '    pOut[1] = nWord;',
                 '    pOut[0] = pSource[0];',
                 '    return pOut;']
        return ('unsigned long long*', 'unsigned long long* pOut, unsigned long long* pSource', lines,
                'position-build', {'elem': word, 'pidx': other, 'order': order})
    return None


def main():
    got, skipped = {}, []
    for a, b in sorted(bodies().items()):
        r = port(b)
        if r is None:
            skipped.append(a)
        else:
            got[a] = r

    fams = {}
    for a, r in got.items():
        fams.setdefault(r[3], []).append(a)
    for f in sorted(fams):
        print('  %-16s %4d  first=%s  %s' % (f, len(fams[f]), fams[f][0],
              ', '.join('%s=%s' % kv for kv in got[fams[f][0]][4].items())))

    h = ['// The allocation, forward-move, range-check and position shapes of NpcServer.exe 0x140080000..0x140090000.',
         '//',
         '// Transcribed from each address\'s own decompiled text by tools/gen_stl_shapes.py; every element size, shift',
         '// and member offset below was read out of that text. Bodies that do not match a shape are skipped, not',
         '// approximated.',
         '#ifndef TQ_NPCSERVER_STL_SHAPES_H',
         '#define TQ_NPCSERVER_STL_SHAPES_H',
         '',
         '#include <cstddef>',
         '',
         'namespace tq {',
         '',
         '// operator_new, as the image calls it (extern void* (*g_pfnNpcOperatorNew)(long long)).',
         'extern void* (*g_pfnNpcOperatorNew)(long long nBytes);',
         '',
         '// memmove_s: same contract the image uses (destination and source sizes both equal to the byte count).',
         '// The default forwards to std::memmove; the image links the CRT wrapper instead.',
         'extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);',
         '',
         'void NpcInvalidParameter(void);',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        h.append('%-22s FUN_%s(%s);   // %s' % (ret, a[4:], params, fam))
    h += ['', 'struct NpcShapeEntry {',
          '    const char* pszAddress;',
          '    const char* pszFamily;',
          '    void*       pfn;',
          '    long long   nElem;',
          '    long long   nArg;',
          '};',
          '',
          'extern const NpcShapeEntry g_aNpcShape_140080000[];',
          'extern const int g_nNpcShape_140080000;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_shapes.py.',
         '#include "modules/npcserver/unattributed/stl-shapes.h"',
         '',
         '#include <cstring>',
         '#include <new>',
         '',
         'namespace tq {',
         '',
         '',
         'static void NpcMemmoveForward(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc) {',
         '    (void)cbDst;',
         '    (void)cbSrc;',
         '    std::memmove(pDst, pSrc, cbSrc);',
         '}',
         '',
         'void (*g_pfnNpcMemmoveS)(void*, size_t, const void*, size_t) = &NpcMemmoveForward;',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        c.append('// 0x%s - %s' % (a[4:], fam))
        c.append('%s FUN_%s(%s) {' % (ret, a[4:], params))
        c.extend(lines)
        c.append('}')
        c.append('')
    c.append('const NpcShapeEntry g_aNpcShape_140080000[] = {')
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        elem = consts.get('elem', 0)
        narg = consts.get('pidx', 0)
        c.append('    { "%s", "%s", (void*)&FUN_%s, %dLL, %dLL },' % (a[4:], fam, a[4:], elem, narg))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcShape_140080000 = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': {a: [got[a][0], got[a][1], got[a][3], got[a][4]] for a in got}, 'skipped': skipped},
              open(MANIFEST, 'w'))
    print('ported %d, skipped %d' % (len(got), len(skipped)))


if __name__ == '__main__':
    main()
