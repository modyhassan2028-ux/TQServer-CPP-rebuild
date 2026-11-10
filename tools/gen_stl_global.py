#!/usr/bin/env python3
"""Transcribe the three shapes that recur across the whole of NpcServer.exe.

They are template instantiations, not module code, so they sit wherever the compiler put them:

  node-push      allocate one node, put the object inside, point the object at the node   (88 bodies)
  delete-holder  hand the object's own pointer to operator_delete                          (86 bodies)
  move-forward   shift a range forwards and return the new end                            (52 bodies)

Only bodies whose text matches exactly are emitted; anything else is left alone.
"""
import os, re, json

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
OUT_H = 'modules/npcserver/unattributed/stl-global.h'
OUT_C = 'modules/npcserver/unattributed/stl-global.cpp'
MANIFEST = '/tmp/stl_global.json'


def bodies():
    src = open(DECOMP, errors='ignore').read()
    out = {}
    for part in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
        part = part.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', part)
        if m:
            out[m.group(1)] = part.strip()
    return out


def flat(t):
    return re.sub(r'\s+', ' ', t).strip()


def num(s):
    return int(s, 16) if s.lower().startswith('0x') else int(s)


def port(body):
    f = flat(body)

    g = re.fullmatch(r'undefined8 \* FUN_[0-9a-f]{9}\((\S+?) \*param_1\) \{ \S+ \*puVar\d; '
                     r'puVar\d = operator_new\((\d+|0x[0-9a-f]+)\); if \(puVar\d == \(\S+ \*\)0x0\) \{ '
                     r'puVar\d = \(\S+ \*\)0x0; \} else \{ \*puVar\d = (.+?); \} \*param_1 = puVar\d; '
                     r'return param_1; \}', f)
    if g and g.group(3) == 'param_1':
        size = num(g.group(2))
        lines = ['    void** pNode = (void**)g_pfnNpcOperatorNew(%d);' % size,
                 '    if (pNode == nullptr) {',
                 '        pNode = nullptr;',
                 '    } else {',
                 '        *pNode = pObject;',
                 '    }',
                 '    *(void**)pObject = pNode;',
                 '    return pObject;']
        return ('void*', 'void* pObject', lines, 'node-push', {'size': size})

    g = re.fullmatch(r'void FUN_[0-9a-f]{9}\((\S+?) \*?param_1\) \{ operator_delete\(\(void \*\)(.+?)\); '
                     r'return; \}', f)
    if g and g.group(2) == '*param_1':
        lines = ['    g_pfnNpcOperatorDelete(*(void**)pObject);']
        return ('void', 'void* pObject', lines, 'delete-holder', {'expr': '*(void**)pObject'})

    g = re.fullmatch(r'void \* FUN_[0-9a-f]{9}\(void \*param_1,longlong param_2,void \*param_3\) \{ '
                     r'rsize_t _DstSize; longlong lVar\d; lVar\d = param_2 - \(longlong\)param_1 >> (\d+); '
                     r'_DstSize = lVar\d \* (\d+); if \(lVar\d != 0\) \{ '
                     r'memmove_s\(param_3,_DstSize,param_1,_DstSize\); \} '
                     r'return \(void \*\)\(_DstSize \+ \(longlong\)param_3\); \}', f)
    if g:
        shift, elem = num(g.group(1)), num(g.group(2))
        if elem != 1 << shift:
            return None
        lines = ['    long long nCount = nLast - (long long)pFirst >> %d;' % shift,
                 '    size_t cbBytes = (size_t)(nCount * %d);' % elem,
                 '    if (nCount != 0) {',
                 '        g_pfnNpcMemmoveS(pDst, cbBytes, pFirst, cbBytes);',
                 '    }',
                 '    return (void*)(cbBytes + (long long)pDst);']
        return ('void*', 'void* pFirst, long long nLast, void* pDst', lines, 'move-forward',
                {'shift': shift, 'elem': elem})
    return None


def main():
    done = set()
    if os.path.exists('/tmp/ported_addrs.txt'):
        done = set(open('/tmp/ported_addrs.txt').read().split())
    got, skipped = {}, []
    for a, b in sorted(bodies().items()):
        if a in done:
            continue
        r = port(b)
        if r is None:
            continue
        got[a] = r
    fams = {}
    for a, r in got.items():
        fams.setdefault(r[3], []).append(a)
    for f in sorted(fams):
        print('  %-14s %3d  first=%s  last=%s' % (f, len(fams[f]), fams[f][0], fams[f][-1]))

    h = ['// The template shapes that recur across the whole of NpcServer.exe.',
         '//',
         '// Transcribed from each address\'s own decompiled text by tools/gen_stl_global.py.',
         '#ifndef TQ_NPCSERVER_STL_GLOBAL_H',
         '#define TQ_NPCSERVER_STL_GLOBAL_H',
         '',
         '#include <cstddef>',
         '',
         'namespace tq {',
         '',
         'extern void* (*g_pfnNpcOperatorNew)(long long nBytes);',
         'extern void* (*g_pfnNpcOperatorDelete)(void* p);',
         'extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        h.append('%-12s FUN_%s(%s);   // %s' % (ret, a[4:], params, fam))
    h += ['', 'struct NpcGlobalEntry {',
          '    const char* pszAddress;',
          '    const char* pszFamily;',
          '    void*       pfn;',
          '    long long   nValue;',
          '};',
          '',
          'extern const NpcGlobalEntry g_aNpcGlobal[];',
          'extern const int g_nNpcGlobal;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe by tools/gen_stl_global.py.',
         '#include "modules/npcserver/unattributed/stl-global.h"',
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
    c.append('const NpcGlobalEntry g_aNpcGlobal[] = {')
    for a in sorted(got):
        ret, params, lines, fam, consts = got[a]
        v = consts.get('size', consts.get('elem', 0))
        c.append('    { "%s", "%s", (void*)&FUN_%s, %dLL },' % (a[4:], fam, a[4:], v))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcGlobal = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': {a: [got[a][0], got[a][1], got[a][3], got[a][4]] for a in got}}, open(MANIFEST, 'w'))
    print('  ported %d' % len(got))


if __name__ == '__main__':
    main()
