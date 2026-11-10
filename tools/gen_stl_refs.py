#!/usr/bin/env python3
"""Transcribe the shared-owner and too-long shapes of NpcServer.exe 0x140080000..0x140090000.

  ref-assign   the intrusive refcount store: keep a reference, then release the one already held
  ref-release  release the held control block, then optionally free the object itself
  ref-copy     build from another pair, forwarding into ref-assign
  too-long     throw length_error carrying the image's own message text

Control-block offsets, the two reference counters and the vtable slots are read from each body.
"""
import os, re, json

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
OUT_H = 'modules/npcserver/unattributed/stl-refs.h'
OUT_C = 'modules/npcserver/unattributed/stl-refs.cpp'
MANIFEST = '/tmp/stl_refs.json'
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


def skeleton(text):
    """Shape of a body with every name and constant collapsed, so a family is one short pattern."""
    s = re.sub(r'\b(pl|pi|pu|l|u|i|c|b)Var\d+\b', 'V', flat(text))
    s = re.sub(r'\b(pl|pi|pu|l|u|i|c|b)Var\d+\b', 'V', s)
    s = re.sub(r'\bparam_(\d)\b', lambda m: 'P' + m.group(1), s)
    s = re.sub(r'\bFUN_[0-9a-f]{9}\b', 'FUN', s)
    s = re.sub(r'\bDAT_[0-9a-f]+\b', 'DAT', s)
    s = re.sub(r'0x[0-9a-f]+', 'N', s)
    s = re.sub(r'(?<![\w.])-?\d+(?![\w])', 'N', s)
    s = re.sub(r'\b(auVar|local_[0-9a-f]+|aVar)\b', lambda m: m.group(1), s)
    s = re.sub(r'\s+', ' ', s)
    return s


REF_ASSIGN = ('void FUN(P1,P2,P3) { V; V; V; if (P3 != N) { LOCK(); *(int *)(P3 + N) = *(int *)(P3 + N) + N; UNLOCK(); } '
              'V = (V) P1[N]; if (V == (V) N) { P1[N] = P3; *P1 = P2; } else { LOCK(); V = V + N; *(int *) V = (int)*V + N; '
              'UNLOCK(); if ((int)*V == N) { (** (code **)*V)(V); LOCK(); V = (int *)((V)V + N); *V = *V + N; UNLOCK(); '
              'if (*V == N) { (** (code **)(*V + N))(V); } P1[N] = P3; *P1 = P2; } else { P1[N] = P3; *P1 = P2; } } } '
              'return; }')

REF_RELEASE = ('void * FUN(void *P1,uint P2) { V; V; V; V = *(V *)((V)P1 + N); if (V != (V) N) { LOCK(); V = V + N; '
               '*(int *) V = (int)*V + N; UNLOCK(); if ((int)*V == N) { (** (code **)*V)(V); LOCK(); V = (int *)((V)V + N); '
               '*V = *V + N; UNLOCK(); if (*V == N) { (** (code **)(*V + N))(V); } } } if ((P2 & N) != N) { '
               'operator_delete(P1); } return P1; }')

REF_COPY = ('undefined8 * FUN(undefined8 *P1,undefined8 *P2) { *P1 = N; P1[N] = N; FUN(P1,*P2,P2[N]); return P1; }')


def port(body, known):
    raw = flat(body)
    sk = skeleton(body)

    if (re.search(r'\(\*\*\(code \*\*\)\*V\)\(V\); LOCK\(\); V = \(int \*\)\(\(longlong\)V \+ N\);', sk)
            and re.search(r'\(\*\*\(code \*\*\)\(\*V \+ N\)\)\(V\);', sk)
            and sk.startswith('void FUN(undefined8 *P1,undefined8 P2,longlong P3)')
            and 'LOCK(); *(int *)(P3 + N)' in sk):
        strong = re.search(r'param_3 \+ (0x[0-9a-f]+)\) = \*\(int \*\)\(param_3', raw)
        weak = re.search(r'piVar\d = \(int \*\)\(\(longlong\)plVar\d \+ (0x[0-9a-f]+)\)', raw)
        slot = re.search(r'\(\*\*\(code \*\*\)\(\*plVar\d \+ (0x[0-9a-f]+|\d+)\)', raw)
        if not (strong and weak and slot):
            return None
        num = lambda s: int(s, 16) if s.lower().startswith('0x') else int(s)
        strong, weak, slot = num(strong.group(1)), num(weak.group(1)), num(slot.group(1))
        lines = ['    if (pControl != nullptr) {',
                 '        __atomic_add_fetch((int*)((char*)pControl + 0x%X), 1, __ATOMIC_SEQ_CST);' % strong,
                 '    }',
                 '    void** pOld = (void**)pOut[1];',
                 '    if (pOld != nullptr) {',
                 '        // the block this pair already held loses its strong reference, then its weak one',
                 '        if (__atomic_sub_fetch((int*)((char*)pOld + 0x%X), 1, __ATOMIC_SEQ_CST) == 0) {' % strong,
                 '            ((void (*)(void**))pOld[0])(pOld);',
                 '            if (__atomic_sub_fetch((int*)((char*)pOld + 0x%X), 1, __ATOMIC_SEQ_CST) == 0) {' % weak,
                 '                ((void (*)(void**))pOld[%d])(pOld);' % (slot // 8 if slot % 8 == 0 else slot),
                 '            }',
                 '        }',
                 '    }',
                 '    pOut[1] = (unsigned long long)pControl;',
                 '    pOut[0] = pValue;']
        return ('void', 'unsigned long long* pOut, unsigned long long pValue, void* pControl', lines, 'ref-assign',
                {'strong': strong, 'weak': weak, 'slot': slot}, None)

    if (re.search(r'= \*\(longlong \*\*\)\(\(longlong\)P1 \+ N\);', sk)
            and 'operator_delete(P1); } return P1; }' in sk
            and sk.startswith('void * FUN(void *P1,uint P2)')):
        at = re.search(r'= \*\(longlong \*\*\)\(\(longlong\)param_1 \+ (\d+)\)', raw)
        weak = re.search(r'piVar\d = \(int \*\)\(\(longlong\)plVar\d \+ (0x[0-9a-f]+)\)', raw)
        slot = re.search(r'\(\*\*\(code \*\*\)\(\*plVar\d \+ (\d+)\)', raw)
        if not (at and weak and slot):
            return None
        num = lambda s: int(s, 16) if s.lower().startswith('0x') else int(s)
        at, weak, slot = num(at.group(1)), num(weak.group(1)), num(slot.group(1))
        lines = ['    void** pControl = *(void***)((char*)pThis + %d);' % at,
                 '    if (pControl != nullptr) {',
                 '        if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {',
                 '            ((void (*)(void**))pControl[0])(pControl);',
                 '            if (__atomic_sub_fetch((int*)((char*)pControl + 0x%X), 1, __ATOMIC_SEQ_CST) == 0) {' % weak,
                 '                ((void (*)(void**))pControl[%d])(pControl);' % (slot // 8 if slot % 8 == 0 else slot),
                 '            }',
                 '        }',
                 '    }',
                 '    if ((nFlags & 1) != 0) {',
                 '        g_pfnNpcOperatorDelete(pThis);',
                 '    }',
                 '    return pThis;']
        return ('void*', 'void* pThis, unsigned int nFlags', lines, 'ref-release', {'at': at}, None)

    if re.search(r'\*P1 = N; P1\[N\] = N; FUN\(P1,\*P2,P2\[N\]\); return P1; \}$', sk):
        g = re.fullmatch(REF_COPY, sk)
        callee = re.search(r'\{ \*param_1 = 0; param_1\[1\] = 0; (FUN_[0-9a-f]{9})\(', raw).group(1)
        direct = callee in {'FUN_' + k for k in known}
        call = ('    %s(pOut, pSource[0], (void*)pSource[1]);' % callee) if direct else \
               ('    if (g_pfnNpc_%s != nullptr) g_pfnNpc_%s(pOut, pSource[0], (void*)(unsigned long long)pSource[1]);'
                % (callee[4:], callee[4:]))
        lines = ['    pOut[0] = 0;', '    pOut[1] = 0;', call, '    return pOut;']
        return ('unsigned long long*', 'unsigned long long* pOut, unsigned long long* pSource', lines, 'ref-copy',
                {'callee': int(callee[4:], 16)}, None if direct else callee[4:])

    if 'std::length_error::vftable' in raw and '_CxxThrowException' in raw:
        msg = re.search(r'"([^"]+)"', raw)
        if msg:
            return ('void', 'void', ['    throw std::length_error("%s");' % msg.group(1)], 'too-long',
                    {'msg': msg.group(1)}, None)
    return None


def defined_in_repo():
    names = set()
    for root, _, files in os.walk('modules/npcserver'):
        for f in files:
            if f.endswith(('.cpp', '.h')):
                names.update(re.findall(r'\bFUN_([0-9a-f]{9})',
                                        open(os.path.join(root, f), errors='ignore').read()))
    return names


def main():
    known = defined_in_repo()
    src = bodies()
    got, skipped = {}, []
    for a, b in sorted(src.items()):
        r = port(b, known)
        if r is None:
            skipped.append(a)
        else:
            got[a] = r
    # a second pass, now that this batch's own bodies count as ported: ref-copy can call ref-assign directly
    known |= {a[4:] for a in got}
    got = {a: port(b, known) for a, b in sorted(src.items()) if a in got}

    fams, seams = {}, {}
    for a, r in got.items():
        fams.setdefault(r[3], []).append(a)
        if r[5]:
            seams[r[5]] = r[5]
    for f in sorted(fams):
        print('  %-12s %3d  first=%s' % (f, len(fams[f]), fams[f][0]))

    h = ['// The shared-owner and length-error shapes of NpcServer.exe 0x140080000..0x140090000.',
         '//',
         '// Transcribed from each address\'s own decompiled text by tools/gen_stl_refs.py. The control-block offsets,',
         '// the two reference counters and the vtable slots are the ones that text names.',
         '#ifndef TQ_NPCSERVER_STL_REFS_H',
         '#define TQ_NPCSERVER_STL_REFS_H',
         '',
         'namespace tq {',
         '',
         'extern void* (*g_pfnNpcOperatorDelete)(void* p);',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        h.append('%-22s FUN_%s(%s);   // %s' % (ret, a[4:], params, fam))
    h.append('')
    for s in sorted(seams):
        h.append('extern void (*g_pfnNpc_%s)(unsigned long long*, unsigned long long, void*);' % s)
    h += ['', 'struct NpcRefEntry {',
          '    const char* pszAddress;',
          '    const char* pszFamily;',
          '    void*       pfn;',
          '    const char* pszText;',
          '    long long   nOffset;',
          '};',
          '',
          'extern const NpcRefEntry g_aNpcRef_140080000[];',
          'extern const int g_nNpcRef_140080000;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_refs.py.',
         '#include "modules/npcserver/unattributed/stl-refs.h"',
         '#include "modules/npcserver/unattributed/front-of-image.h"',
         '',
         '#include <stdexcept>',
         '',
         'namespace tq {',
         '']
    for s in sorted(seams):
        c.append('void (*g_pfnNpc_%s)(unsigned long long*, unsigned long long, void*) = nullptr;' % s)
    c.append('')
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        c.append('// 0x%s - %s' % (a[4:], fam))
        c.append('%s FUN_%s(%s) {' % (ret, a[4:], params))
        c.extend(lines)
        c.append('}')
        c.append('')
    c.append('const NpcRefEntry g_aNpcRef_140080000[] = {')
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        text = consts.get('msg', '')
        off = consts.get('strong', consts.get('at', consts.get('callee', 0)))
        c.append('    { "%s", "%s", (void*)&FUN_%s, "%s", %dLL },' % (a[4:], fam, a[4:], text, off))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcRef_140080000 = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': {a: [got[a][0], got[a][1], got[a][3], got[a][4]] for a in got}, 'skipped': skipped},
              open(MANIFEST, 'w'))
    print('ported %d, skipped %d' % (len(got), len(skipped)))


if __name__ == '__main__':
    main()
