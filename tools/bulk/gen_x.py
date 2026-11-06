#!/usr/bin/env python3
"""Family X — flag-guarded cleanup.

    push rbp ; sub rsp,<f> ; mov rbp,rdx
    mov eax,DWORD PTR [rbp+<flags>] ; and eax,<mask> ; test eax,eax ; je <epilogue>
    and DWORD PTR [rbp+<flags>],<inv>          ; clear the bit
    <argument setup>                            ; mov rcx,[rbp+<off>]  or  lea rcx,[rbp+<off>]
    call <direct|slot> ; add rsp,<f> ; pop rbp ; ret
The single `je` is required to land on the `add rsp` epilogue, so the skip path is proven.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_x'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

P = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; '
               r'mov eax,DWORD PTR \[rbp\+(0x[0-9a-f]+)\] ; and eax,(0x[0-9a-f]+) ; '
               r'test eax,eax ; je (0x[0-9a-f]+) ; '
               r'and DWORD PTR \[rbp\+\2\],(0x[0-9a-f]+) ; '
               r'(mov rcx,QWORD PTR \[rbp\+(0x[0-9a-f]+)\]|lea rcx,\[rbp\+(0x[0-9a-f]+)\]) ; '
               r'call (?:(0x[0-9a-f]+)|QWORD PTR \[rip@(0x[0-9a-f]+)\]) ; '
               r'add rsp,0x\1 ; pop rbp ; ret')
hits, rej = [], 0
for f in rem:
    m = P.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    if idx.get(int(m.group(4), 16)) != len(f['text']) - 3:      # je -> add rsp
        rej += 1; continue
    kind = 'deref' if m.group(7) else 'addr'
    off = int(m.group(7) or m.group(8), 16)
    hits.append({'a': f['a'], 'frame': int(m.group(1), 16), 'flags': int(m.group(2), 16),
                 'mask': int(m.group(3), 16), 'inv': int(m.group(5), 16), 'kind': kind,
                 'o': off, 'direct': int(m.group(9), 16) if m.group(9) else None,
                 'slot': int(m.group(10), 16) if m.group(10) else None})
print('family X', len(hits), 'rejected', rej)

def sn(h):
    return 'g_fnXD%x' % h['direct'] if h['direct'] else 'g_fnXS%x' % h['slot']

hdr = ['// synthunks_x.h — RAW Syndicate.dll v6159 · %d flag-guarded cleanups (family X).' % len(hits),
       '// The guard tests one bit of a flag word on the second argument and clears it before the call;',
       '// the skip branch was verified onto the `add rsp` epilogue. The argument is either the member',
       '// itself or its address, exactly as the instruction says.',
       '#ifndef TQ_SYN_THUNKS_X_H', '#define TQ_SYN_THUNKS_X_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({sn(h) for h in hits})
hdr += ['extern void (*%s)(void* pArg);' % s for s in seams] + ['']
for h in hits:
    arg = ('*(void**)((uint8_t*)pArg2 + 0x%x)' % h['o']) if h['kind'] == 'deref' \
        else ('(void*)((uint8_t*)pArg2 + 0x%x)' % h['o'])
    hdr.append('inline void SynGuard_%x(void* pUnused, void* pArg2) {   // 0x%x  frame 0x%x\n'
               '    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x%x);\n'
               '    if (!(nFlags & 0x%x)) return;      // the je path\n'
               '    nFlags &= 0x%x;\n'
               '    %s(%s);\n}'
               % (h['a'], h['a'], h['frame'], h['flags'], h['mask'], h['inv'], sn(h), arg))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_x.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_x.cpp — the seams of family X.',
      '#include "modules/syndicate/src/synthunks_x.h"', '', 'namespace tq {', '']
sc += ['void (*%s)(void*) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_x.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family X — the guarded and the skipped path of every body.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_x.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_v = 0; static int g_nCalls = 0;',
     'static void Hook(void* p) { g_v = (uintptr_t)p; ++g_nCalls; }', '',
     'int main() {']
T += ['    %s = &Hook;' % s for s in seams]
mx = max((max(h['flags'], h['o']) for h in hits), default=0)
T += ['    static unsigned char aObj[0x%x];' % (mx + 0x40), '']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        *(uint32_t*)(aObj + 0x%x) = 0x%x;   // bit clear: nothing may happen\n'
             '        *(uint64_t*)(aObj + 0x%x) = 0xDEAD;\n'
             '        g_nCalls = 0; g_v = 0;\n'
             '        SynGuard_%x(nullptr, aObj);\n'
             '        CHECK(g_nCalls == 0);\n'
             '        CHECK(*(uint32_t*)(aObj + 0x%x) == 0x%x);\n'
             '        *(uint32_t*)(aObj + 0x%x) = 0x%x;   // bit set: clear it, then call\n'
             '        *(uint64_t*)(aObj + 0x%x) = 0xBEEF;\n'
             '        SynGuard_%x(nullptr, aObj);\n'
             '        CHECK(g_nCalls == 1);\n'
             '        CHECK(*(uint32_t*)(aObj + 0x%x) == (0x%x & 0x%x));\n'
             '        CHECK(g_v == %s);\n    }'
             % (h['a'], h['flags'], (h['mask'] ^ 0xFFFFFFFF) & 0xFFFFFFFF,
                h['o'], h['a'], h['flags'], (h['mask'] ^ 0xFFFFFFFF) & 0xFFFFFFFF,
                h['flags'], (h['mask'] | 0xAAAAAAAA) & 0xFFFFFFFF,
                h['o'], h['a'], h['flags'], (h['mask'] | 0xAAAAAAAA) & 0xFFFFFFFF, h['inv'],
                ('(uintptr_t)0xBEEF' if h['kind'] == 'deref' else '(uintptr_t)(aObj + 0x%x)' % h['o'])))
T += ['', '    std::printf("SYNDICATE_THUNKS_X_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_x_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_x.json', 'w'))
