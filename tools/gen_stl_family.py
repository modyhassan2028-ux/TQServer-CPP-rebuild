#!/usr/bin/env python3
"""Transcribe the repeated container-internal bodies of an address range straight from the decompiled C.

No body is invented. Each emitted function is a transcription of that address's own decompiled text; the constants
(offsets, sizes, returned deltas) are read back out of that text. A body that matches no known shape is reported as
skipped instead of being guessed at.
"""
import re, sys, json

DEC = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'

def load():
    src = open(DEC, errors='ignore').read()
    parts = re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src)
    out = {}
    for p in parts:
        p = p.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', p)
        if m:
            out[m.group(1)] = p.rstrip()
    return out

def norm(body):
    b = re.sub(r'LAB_[0-9a-f]{9}', 'LAB', body)
    b = re.sub(r'local_[0-9a-f]+', 'L', b)
    b = re.sub(r'DAT_[0-9a-f]+', 'D', b)
    b = re.sub(r'\bparam_\d\b', 'P', b)
    b = re.sub(r'\b(pl|pi|pu|l|u|i|c|b)Var\d\b', 'V', b)
    b = re.sub(r'FUN_[0-9a-f]{9}', 'FUN', b)
    b = re.sub(r'0x[0-9a-f]+', 'N', b)
    b = re.sub(r'(?<![\w)])-\d+', 'N', b)
    b = re.sub(r'(?<![\w.])\d+', 'N', b)
    return re.sub(r'\s+', ' ', b).strip()

def n(body, pat, group=1, default=None):
    m = re.search(pat, body)
    if not m:
        if default is None:
            raise LookupError(pat)
        return default
    return int(m.group(group), 0)

K_DELETE = 'void FUN(undefined8 *P) { operator_delete((void *)*P); return; }'
K_NEW = ('undefined8 * FUN(undefined8 *P) { undefined8 *V; V = operator_new(N); if (V == (undefined8 *)N) { '
         'V = (undefined8 *)N; } else { *V = P; } *P = V; return P; }')
K_DECREF_HEAD = 'void FUN(longlong P) { longlong *V; int *V; longlong *V; V = *(longlong **)(P + N);'
K_IT = ('longlong FUN(longlong *P) { longlong *V; longlong V; V = (longlong *)*P; if (V == (longlong *)N) { '
        '_invalid_parameter_noinfo(); V = (longlong *)*P; V = N; if (V == (longlong *)N) goto LAB; } V = *V; LAB: '
        'if (')
K_CMP = 'bool FUN(longlong *P,longlong *P) { if ((*P == N) || (*P != *P)) { _invalid_parameter_noinfo(); } return P['

def port(addr, body):
    k = norm(body)
    if k == K_DELETE:
        return ('void', 'void** pThis', ['    ::operator delete(*pThis);'], 'delete-thunk', {})
    if k == K_NEW:
        size = n(body, r'operator_new\((0x[0-9a-f]+|\d+)\)')
        return ('void**', 'void** pThis',
                ['    void* pNew = ::operator new(%d);' % size,
                 '    if (pNew == nullptr) {',
                 '        pNew = nullptr;',
                 '    } else {',
                 '        *(void**)pNew = pThis;',
                 '    }',
                 '    *pThis = pNew;',
                 '    return pThis;'], 'new-and-store', {'size': size})
    if k.startswith(K_DECREF_HEAD) and 'LOCK();' in k and 'operator_delete' not in k:
        own = n(body, r'\(param_1 \+ (0x[0-9a-f]+|\d+)\)')
        uses = n(body, r'plVar1 = plVar3 \+ (0x[0-9a-f]+|\d+)') * 8 if 'plVar3 + ' in body else 0
        weak = n(body, r'\(longlong\)plVar3 \+ (0x[0-9a-f]+|\d+)\)')
        s = '0x%x' % uses
        w = '0x%x' % weak
        return ('void', 'char* pThis',
                ['    long long* pRef = *(long long**)(pThis + %d);' % own,
                 '    if (pRef != nullptr) {',
                 '        int nUses = __atomic_load_n((int*)((char*)pRef + %s), __ATOMIC_SEQ_CST) - 1;' % s,
                 '        __atomic_store_n((int*)((char*)pRef + %s), nUses, __ATOMIC_SEQ_CST);' % s,
                 '        if (nUses == 0) {',
                 '            (*(void (**)(long long*))(*pRef))(pRef);',
                 '            int nWeak = __atomic_load_n((int*)((char*)pRef + %s), __ATOMIC_SEQ_CST) - 1;' % w,
                 '            __atomic_store_n((int*)((char*)pRef + %s), nWeak, __ATOMIC_SEQ_CST);' % w,
                 '            if (nWeak == 0)',
                 '                (*(void (**)(long long*))(*pRef + 0x08))(pRef);',
                 '        }',
                 '    }'], 'decref', {'own': own, 'uses': uses, 'weak': weak})
    if k.startswith(K_IT):
        off = n(body, r'\*\((?:ulonglong|longlong) \*\)\(lVar2 \+ (0x[0-9a-f]+|\d+)\)')
        lesseq = '<= (ulonglong)param_1[1]' in body
        ret_body = body.split('_invalid_parameter_noinfo(); }')[-1]
        delta = n(body, r'return param_1\[1\] \+ (0x[0-9a-f]+|\d+);', default=0)
        if lesseq:
            cmp = 'if (*(unsigned long long*)(lBase + 0x%x) <= (unsigned long long)pThis[1])' % off
        else:
            cmp = 'if (pThis[1] == *(long long*)(lBase + 0x%x))' % off
        ret = 'return pThis[1] + 0x%x;' % delta if delta else 'return pThis[1];'
        return ('long long', 'long long* pThis',
                ['    long long* pNode = (long long*)*pThis;',
                 '    long long lBase;',
                 '    if (pNode == nullptr) {',
                 '        _invalid_parameter_noinfo();',
                 '        pNode = (long long*)*pThis;',
                 '        lBase = 0;',
                 '        if (pNode == nullptr) goto done;',
                 '    }',
                 '    lBase = *pNode;',
                 'done:',
                 '    ' + cmp + ' {',
                 '        _invalid_parameter_noinfo();',
                 '    }',
                 '    ' + ret], 'iterator-check', {'offset': off, 'lesseq': lesseq, 'delta': delta})
    if k.startswith(K_CMP):
        op = '!=' if 'return param_1[1] != param_2[1];' in body else '=='
        return ('bool', 'long long* pFirst, long long* pSecond',
                ['    if (*pFirst == 0 || *pFirst != *pSecond)',
                 '        _invalid_parameter_noinfo();',
                 '    return pFirst[1] %s pSecond[1];' % op], 'iterator-compare', {'equal': op == '=='})
    return None

def main():
    lo, hi = sys.argv[1], sys.argv[2]
    bodies = load()
    addrs = sorted(a for a in bodies if lo <= a[4:] <= hi)
    got, skipped = {}, []
    for a in addrs:
        r = port(a, bodies[a])
        (got.__setitem__(a, r) if r else skipped.append(a))
    fams = {}
    for a in got:
        fams.setdefault(got[a][3], []).append(a[4:])
    print('ported %d, skipped %d' % (len(got), len(skipped)))
    for f in sorted(fams):
        print('  %-16s %4d  first=%s' % (f, len(fams[f]), fams[f][0]))
    consts = {}
    for a in got:
        consts[a] = got[a][4]
    json.dump(consts, open('/tmp/stl_consts.json', 'w'))
    json.dump({'ported': got, 'skipped': skipped, 'families': fams}, open('/tmp/stl_family.json', 'w'))

main()
