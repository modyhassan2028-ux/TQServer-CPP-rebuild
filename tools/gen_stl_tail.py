#!/usr/bin/env python3
"""Transcribe four tail shapes of NpcServer.exe 0x140080000..0x140090000 (three bodies each).

  move-backward   shift a range backwards and return the new start
  clear-or-drop   clear a pair, releasing the control block it held first
  ref-fill        guarded copy from another pair into a fresh one
  position-member a position pair taken from a member word of a third object
"""
import os, re, json

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
OUT_H = 'modules/npcserver/unattributed/stl-tail.h'
OUT_C = 'modules/npcserver/unattributed/stl-tail.cpp'
MANIFEST = '/tmp/stl_tail.json'
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


def num(s):
    return int(s, 16) if s.lower().startswith('0x') else int(s)


def port(body):
    f = flat(body)

    g = re.fullmatch(r'void \* FUN_[0-9a-f]{9}\(void \*param_1,longlong param_2,longlong param_3\) \{ '
                     r'longlong lVar\d; void \*_Dst; lVar\d = param_2 - \(longlong\)param_1 >> (\d+); '
                     r'_Dst = \(void \*\)\(param_3 \+ lVar\d \* -(\d+)\); if \(0 < lVar\d\) \{ '
                     r'memmove_s\(_Dst,lVar\d \* \d+,param_1,lVar\d \* \d+\); \} return _Dst; \}', f)
    if g:
        shift, elem = num(g.group(1)), num(g.group(2))
        lines = ['    long long nCount = nLast - (long long)pFirst >> %d;' % shift,
                 '    void* pDst = (void*)(nDst + nCount * -%d);' % elem,
                 '    if (0 < nCount) {',
                 '        g_pfnNpcMemmoveS(pDst, (size_t)(nCount * %d), pFirst, (size_t)(nCount * %d));' % (elem, elem),
                 '    }',
                 '    return pDst;']
        return ('void*', 'void* pFirst, long long nLast, long long nDst', lines, 'move-backward',
                {'shift': shift, 'elem': elem})

    g = re.fullmatch(r'void FUN_[0-9a-f]{9}\(undefined8 \*param_1\) \{ longlong \*plVar\d; int \*piVar\d; '
                     r'longlong \*plVar\d; plVar\d = \(longlong \*\)param_1\[(\d)\]; if \(plVar\d == '
                     r'\(longlong \*\)0x0\) \{ param_1\[\d\] = 0; \*param_1 = 0; return; \} LOCK\(\); '
                     r'plVar\d = plVar\d \+ 2; \*\(int \*\)plVar\d = \(int\)\*plVar\d \+ -1; UNLOCK\(\); '
                     r'if \(\(int\)\*plVar\d == 0\) \{ \(\*\*\(code \*\*\)\*plVar\d\)\(plVar\d\); LOCK\(\); '
                     r'piVar\d = \(int \*\)\(\(longlong\)plVar\d \+ (0x[0-9a-f]+)\); \*piVar\d = \*piVar\d \+ -1; '
                     r'UNLOCK\(\); if \(\*piVar\d == 0\) \{ \(\*\*\(code \*\*\)\(\*plVar\d \+ (\d+)\)\)\(plVar\d\); \} '
                     r'param_1\[\d\] = 0; \*param_1 = 0; return; \} param_1\[\d\] = 0; \*param_1 = 0; return; \}', f)
    if g:
        weak, slot = num(g.group(2)), num(g.group(3))
        lines = ['    void** pControl = (void**)pOut[1];',
                 '    if (pControl == nullptr) {',
                 '        pOut[1] = 0;',
                 '        pOut[0] = 0;',
                 '        return;',
                 '    }',
                 '    if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {',
                 '        ((void (*)(void**))pControl[0])(pControl);',
                 '        if (__atomic_sub_fetch((int*)((char*)pControl + 0x%X), 1, __ATOMIC_SEQ_CST) == 0) {' % weak,
                 '            ((void (*)(void**))pControl[%d])(pControl);' % (slot // 8 if slot % 8 == 0 else slot),
                 '        }',
                 '    }',
                 '    pOut[1] = 0;',
                 '    pOut[0] = 0;']
        return ('void', 'unsigned long long* pOut', lines, 'clear-or-drop', {'weak': weak})

    g = re.fullmatch(r'void FUN_[0-9a-f]{9}\(undefined8 \*param_1,undefined8 \*param_2\) \{ if \(param_1 != '
                     r'\(undefined8 \*\)0x0\) \{ \*param_1 = 0; param_1\[1\] = 0; (FUN_[0-9a-f]{9})\(param_1,'
                     r'\*param_2,param_2\[1\]\); \} return; \}', f)
    if g:
        callee = g.group(1)
        lines = ['    if (pOut != nullptr) {',
                 '        pOut[0] = 0;',
                 '        pOut[1] = 0;',
                 '        %s(pOut, pSource[0], (void*)(unsigned long long)pSource[1]);' % callee,
                 '    }']
        return ('void', 'unsigned long long* pOut, unsigned long long* pSource', lines, 'ref-fill',
                {'callee': int(callee[4:], 16)})

    g = re.fullmatch(r'undefined8 \* FUN_[0-9a-f]{9}\(undefined8 \*param_1,undefined8 \*param_2,longlong param_3\) '
                     r'\{ ulonglong uVar\d; undefined8 uVar\d; uVar\d = \*\(ulonglong \*\)\(param_3 \+ (\d+)\); '
                     r'\*param_2 = 0; if \(\(\(param_1 == \(undefined8 \*\)0x0\) \|\| '
                     r'\(uVar\d < \(ulonglong\)param_1\[(\d)\]\)\) \|\| \(\(ulonglong\)param_1\[(\d)\] < uVar\d\)\) '
                     r'\{ _invalid_parameter_noinfo\(\); \} uVar\d = \*param_1; param_2\[1\] = uVar\d; '
                     r'\*param_2 = uVar\d; return param_2; \}', f)
    if g:
        at, lo_word, hi_word = num(g.group(1)), num(g.group(2)), num(g.group(3))
        lines = ['    unsigned long long nWord = *(unsigned long long*)(pMember + %d);' % at,
                 '    pOut[0] = 0;',
                 '    if (pSource == nullptr || nWord < pSource[%d] || pSource[%d] < nWord) {' % (lo_word, hi_word),
                 '        NpcInvalidParameter();',
                 '    }',
                 '    pOut[1] = nWord;',
                 '    pOut[0] = pSource[0];',
                 '    return pOut;']
        return ('unsigned long long*', 'unsigned long long* pSource, unsigned long long* pOut, long long pMember',
                lines, 'position-member', {'at': at})
    return None


def main():
    done = set()
    if os.path.exists('/tmp/ported_addrs.txt'):
        done = set(open('/tmp/ported_addrs.txt').read().split())
    got, skipped, already = {}, [], []
    for a, b in sorted(bodies().items()):
        if a in done:
            already.append(a)
            continue
        r = port(b)
        if r is None:
            skipped.append(a)
        else:
            got[a] = r

    fams = {}
    for a, r in got.items():
        fams.setdefault(r[3], []).append(a)
    for f in sorted(fams):
        print('  %-16s %3d  first=%s' % (f, len(fams[f]), fams[f][0]))
    print('  ported %d, still skipped %d, already done %d' % (len(got), len(skipped), len(already)))

    h = ['// Four tail shapes of NpcServer.exe 0x140080000..0x140090000.',
         '//',
         '// Transcribed from each address\'s own decompiled text by tools/gen_stl_tail.py.',
         '#ifndef TQ_NPCSERVER_STL_TAIL_H',
         '#define TQ_NPCSERVER_STL_TAIL_H',
         '',
         '#include <cstddef>',
         '',
         'namespace tq {',
         '',
         'extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);',
         'void NpcInvalidParameter(void);',
         'void FUN_1400814a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);',
         'void FUN_1400819a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);',
         'void FUN_140081a30(unsigned long long* pOut, unsigned long long pValue, void* pControl);',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        h.append('%-22s FUN_%s(%s);   // %s' % (ret, a[4:], params, fam))
    h += ['', 'struct NpcTailEntry {',
          '    const char* pszAddress;',
          '    const char* pszFamily;',
          '    void*       pfn;',
          '    long long   nValue;',
          '};',
          '',
          'extern const NpcTailEntry g_aNpcTail_140080000[];',
          'extern const int g_nNpcTail_140080000;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_tail.py.',
         '#include "modules/npcserver/unattributed/stl-tail.h"',
         '',
         'namespace tq {',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        c.append('// 0x%s - %s' % (a[4:], fam))
        c.append('%s FUN_%s(%s) {' % (ret, a[4:], params))
        c.extend(lines)
        c.append('}')
        c.append('')
    c.append('const NpcTailEntry g_aNpcTail_140080000[] = {')
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        v = consts.get('elem', consts.get('weak', consts.get('callee', consts.get('at', 0))))
        c.append('    { "%s", "%s", (void*)&FUN_%s, %dLL },' % (a[4:], fam, a[4:], v))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcTail_140080000 = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': {a: [got[a][0], got[a][1], got[a][3], got[a][4]] for a in got},
               'skipped': skipped, 'already': already}, open(MANIFEST, 'w'))


if __name__ == '__main__':
    main()
