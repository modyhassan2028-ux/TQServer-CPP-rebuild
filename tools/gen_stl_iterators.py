#!/usr/bin/env python3
"""Generate the forwarding-wrapper and pair-construct bodies of NpcServer.exe 0x140080000..0x140090000.

Both shapes repeat verbatim across the range, so nothing is written by hand: every emitted body comes from that
address's own decompiled text, and the callee address a wrapper forwards to is read out of that text. A body that
does not match one of the shapes exactly is skipped and reported, never approximated.
"""
import os, re, sys, json

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
OUT_H = 'modules/npcserver/unattributed/stl-iterators.h'
OUT_C = 'modules/npcserver/unattributed/stl-iterators.cpp'
MANIFEST = '/tmp/stl_iterators.json'


def load(lo, hi):
    src = open(DECOMP, errors='ignore').read()
    out = {}
    for part in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
        part = part.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', part)
        if m and lo <= m.group(1)[4:] < hi:
            out[m.group(1)] = part.strip()
    return out


def flatten(text):
    return re.sub(r'\s+', ' ', text).strip()


def defined_in_repo():
    names = set()
    for base in ('modules/npcserver',):
        for root, _, files in os.walk(base):
            for f in files:
                if f.endswith(('.cpp', '.h')):
                    body = open(os.path.join(root, f), errors='ignore').read()
                    names.update(re.findall(r'\bFUN_([0-9a-f]{9})\s*\(', body))
    return names


def port(body, known):
    """Return (ret, params, lines, family, consts, seam) or None."""
    flat = flatten(body)
    head = re.match(r'^(longlong|undefined8|void|longlong \*|undefined8 \*|void \*) (FUN_[0-9a-f]{9})\((.*?)\) \{', flat)
    if not head:
        return None
    ret_raw, name, params_raw = head.groups()

    # forwarding wrapper: <callee>(param_1[, param_2]); return param_1;
    m = re.fullmatch(r'longlong \* FUN_[0-9a-f]{9}\(longlong \* ?param_1(, ?longlong param_2)?\) \{ '
                     r'(FUN_[0-9a-f]{9})\(param_1(, ?param_2)?\); return param_1; \}', flat)
    if m:
        callee = m.group(2)
        two = m.group(1) is not None
        args = 'pThis, nValue' if two else 'pThis'
        call = 'pThis, nValue' if two else 'pThis'
        seam = callee not in {'FUN_' + k for k in known}
        if seam:
            line = '    if (g_pfnNpc_%s != nullptr) g_pfnNpc_%s(%s);' % (callee[4:], callee[4:], call)
        else:
            line = '    %s(%s);' % (callee, call)
        params = 'long long* pThis, long long nValue' if two else 'long long* pThis'
        return ('long long*', params, [line, '    return pThis;'], 'forwarder',
                {'callee': int(callee[4:], 16), 'two': two}, callee[4:] if seam else None)

    # pair construct: *p1 = 0; p1[1] = p2; if (p3 == 0) invalid; *p1 = *p3; return p1;
    m = re.fullmatch(r'undefined8 \* FUN_[0-9a-f]{9}\(undefined8 \*param_1, ?undefined8 param_2, ?undefined8 \*param_3\) '
                     r'\{ \*param_1 = 0; param_1\[1\] = param_2; if \(param_3 == \(undefined8 \*\)0x0\) '
                     r'\{ _invalid_parameter_noinfo\(\); \} \*param_1 = \*param_3; return param_1; \}', flat)
    if m:
        lines = ['    pPair[0] = 0;',
                 '    pPair[1] = nSecond;',
                 '    if (pSource == nullptr) {',
                 '        NpcInvalidParameter();',
                 '    }',
                 '    pPair[0] = pSource[0];',
                 '    return pPair;']
        return ('unsigned long long*', 'unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource',
                lines, 'pair-construct', {}, None)
    return None


def main():
    lo, hi = sys.argv[1], sys.argv[2]
    bodies = load(lo, hi)
    known = defined_in_repo()
    got, skipped = {}, []
    for a in sorted(bodies):
        r = port(bodies[a], known)
        if r is None:
            skipped.append(a)
        else:
            got[a] = r

    fams = {}
    seams = {}
    for a, r in got.items():
        fams.setdefault(r[3], []).append(a)
        if r[5]:
            seams[r[5]] = bool(r[4].get('two'))

    for f in sorted(fams):
        print('  %-16s %4d  first=%s' % (f, len(fams[f]), fams[f][0]))

    h = ['// The forwarding wrappers and pair constructs of NpcServer.exe 0x140080000..0x140090000.',
         '//',
         '// Transcribed from each address\'s own decompiled body by tools/gen_stl_iterators.py. A wrapper calls the',
         '// address the image calls; where that callee is not ported yet it goes through a seam named for the address.',
         '#ifndef TQ_NPCSERVER_STL_ITERATORS_H',
         '#define TQ_NPCSERVER_STL_ITERATORS_H',
         '',
         'namespace tq {',
         '']
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        h.append('%-24s FUN_%s(%s);' % (ret, a[4:], params))
    h.append('')
    for s in sorted(seams):
        h.append('extern long long (*g_pfnNpc_%s)(long long*%s);' % (s, ', long long' if seams[s] else ''))
    h += ['', 'struct NpcIteratorEntry {',
          '    const char* pszAddress;',
          '    const char* pszFamily;',
          '    void*       pfn;',
          '    long long   nArg1;',
          '};',
          '',
          'extern const NpcIteratorEntry g_aNpcIter_140080000[];',
          'extern const int g_nNpcIter_140080000;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_iterators.py.',
         '#include "modules/npcserver/unattributed/stl-iterators.h"',
         '#include "modules/npcserver/unattributed/stl-internals.h"', '',
         'namespace tq {', '']
    for s in sorted(seams):
        c.append('long long (*g_pfnNpc_%s)(long long*%s) = nullptr;' % (s, ', long long' if seams[s] else ''))
    c.append('')
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        c.append('// 0x%s - %s' % (a[4:], fam))
        c.append('%s FUN_%s(%s) {' % (ret, a[4:], params))
        c.extend(lines)
        c.append('}')
        c.append('')
    c.append('const NpcIteratorEntry g_aNpcIter_140080000[] = {')
    for a in sorted(got):
        ret, params, lines, fam, consts, seam = got[a]
        c.append('    { "%s", "%s", (void*)&FUN_%s, %dLL },' % (a[4:], fam, a[4:], consts.get('callee', 0)))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcIter_140080000 = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': {a: [got[a][0], got[a][1], got[a][3]] for a in got}, 'skipped': skipped}, open(MANIFEST, 'w'))
    print('ported %d, skipped %d' % (len(got), len(skipped)))


if __name__ == '__main__':
    main()
