#!/usr/bin/env python3
"""Family K2 — the four-qword staging call.

    mov r11,rsp ; push rbx ; sub rsp,<f>
    mov rdx,[rcx+<o1>] ; mov rax,[rcx+<o2>] ; lea r9,[r11-<x1>]
    mov [r11-<x2>],rax ; mov rax,[rax] ; mov [r11-<x3>],rdx
    (movaps/movdqa pair on the same slot: a no-op self copy, nothing to emit)
    mov [r11-<x4>],rdx ; mov [r11-<x5>],rax ; lea r8,[r11-<x6>]
    (a second no-op pair) ; lea rdx,[r11-<x7>] ; mov rbx,rcx ; call <t1>
    mov rcx,[rbx+<o2>] ; call <t2> ; xor r11d,r11d
    mov [rbx+<o2>],r11 ; mov [rbx+<o3>],r11 ; add rsp,<f> ; pop rbx ; ret

Every [r11-<x>] is resolved to a frame offset (rsp after `sub` plus the pushed rbx), so the staged
qwords land where the disassembly puts them. The movaps/movdqa pairs load and store the SAME slot,
so they are compiler noise and contribute nothing. The returned value is t2's, which is what rax
holds at the epilogue.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_k2'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

X = r'0x[0-9a-f]+'
P = re.compile(
    f'mov r11,rsp ; push rbx ; sub rsp,0x([0-9a-f]+) ; '
    f'mov rdx,QWORD PTR \\[rcx\\+({X})\\] ; mov rax,QWORD PTR \\[rcx\\+({X})\\] ; lea r9,\\[r11-({X})\\] ; '
    f'mov QWORD PTR \\[r11-({X})\\],rax ; mov rax,QWORD PTR \\[rax\\+0x0\\] ; mov QWORD PTR \\[r11-({X})\\],rdx ; '
    f'movaps xmm0,XMMWORD PTR \\[rsp\\+({X})\\] ; movdqa XMMWORD PTR \\[rsp\\+({X})\\],xmm0 ; '
    f'mov QWORD PTR \\[r11-({X})\\],rdx ; mov QWORD PTR \\[r11-({X})\\],rax ; lea r8,\\[r11-({X})\\] ; '
    f'movaps xmm1,XMMWORD PTR \\[rsp\\+({X})\\] ; movdqa XMMWORD PTR \\[rsp\\+({X})\\],xmm1 ; '
    f'lea rdx,\\[r11-({X})\\] ; mov rbx,rcx ; call ({X}) ; '
    f'mov rcx,QWORD PTR \\[rbx\\+({X})\\] ; call ({X}) ; xor r11d,r11d ; '
    f'mov QWORD PTR \\[rbx\\+({X})\\],r11 ; mov QWORD PTR \\[rbx\\+({X})\\],r11 ; '
    f'add rsp,0x\\1 ; pop rbx ; ret')
GROUPS = ['f', 'o1', 'o2', 'x1', 'x2', 'x3', 'y1a', 'y1b', 'x4', 'x5', 'x6', 'y2a', 'y2b', 'x7',
          't1', 'o2b', 't2', 'o2c', 'o3']

hits, rej = [], 0
def norm(body):
    # objdump prints a zero displacement as `[reg]`; canonicalise so one pattern covers both forms
    return re.sub(r'\[(r[a-z0-9]+)\]', r'[\1+0x0]', body)

for f in rem:
    m = P.fullmatch(norm(' ; '.join(f['text'])))
    if not m:
        continue
    g = {k: int(v, 16) for k, v in zip(GROUPS, m.groups())}
    if g['o2'] != g['o2b'] or g['o2'] != g['o2c']:
        rej += 1; continue
    if g['y1a'] != g['y1b'] or g['y2a'] != g['y2b']:
        rej += 1; continue          # the movaps pair must be a self copy, else it would matter
    fr = g['f'] + 8                       # r11 - frame_base
    hits.append({'a': f['a'], 'frame': g['f'], 'o1': g['o1'], 'o2': g['o2'], 'o3': g['o3'],
                 'slots': {k: fr - g[k] for k in ('x1', 'x2', 'x3', 'x4', 'x5', 'x6', 'x7')},
                 't1': g['t1'], 't2': g['t2']})
print('family K2', len(hits), 'rejected', rej)

hdr = ['// synthunks_k2.h — RAW Syndicate.dll v6159 · %d four-qword staging calls (family K2).' % len(hits),
       '// The staged words and the three pointers handed to the first target are addressed exactly as the',
       '// [r11-<x>] operands say; the movaps/movdqa pairs copy a slot onto itself and emit nothing.',
       '#ifndef TQ_SYN_THUNKS_K2_H', '#define TQ_SYN_THUNKS_K2_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({(h['t1'], h['t2']) for h in hits})
hdr += ['extern void (*g_fnK2A_%x)(void* pThis, void* pArg3, void* pArg2, void* pArg1);' % h['t1'] for h in hits[:0]]
hdr += ['extern void* (*g_fnK2B_%x)(void* pObj);' % h['t2'] for h in hits[:0]]
s1 = sorted({h['t1'] for h in hits}); s2 = sorted({h['t2'] for h in hits})
hdr += ['extern void (*g_fnK2A_%x)(void* pThis, void* pD, void* pC, void* pB);' % x for x in s1]
hdr += ['extern void* (*g_fnK2B_%x)(void* pObj);' % x for x in s2] + ['']
for h in hits:
    sl = h['slots']
    size = max(sl.values()) + 8
    hdr.append('inline void* SynStage_%x(void* pThis) {   // 0x%x  frame 0x%x\n'
               '    uint8_t aFrame[0x%x] = {};\n'
               '    void* const pFirst = *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    void* const pObj   = *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    *(void**)(aFrame + 0x%x) = pObj;                       // [r11-0x%x]\n'
               '    void* const pInner = *(void**)pObj;                    // insn 7\n'
               '    *(void**)(aFrame + 0x%x) = pFirst;                     // [r11-0x%x]\n'
               '    *(void**)(aFrame + 0x%x) = pFirst;                     // [r11-0x%x]\n'
               '    *(void**)(aFrame + 0x%x) = pInner;                     // [r11-0x%x]\n'
               '    g_fnK2A_%x(pThis, aFrame + 0x%x, aFrame + 0x%x, aFrame + 0x%x);\n'
               '    void* const pR = g_fnK2B_%x(*(void**)((uint8_t*)pThis + 0x%x));\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = nullptr;\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = nullptr;\n'
               '    return pR;\n}'
               % (h['a'], h['a'], h['frame'], size, h['o1'], h['o2'],
                  sl['x2'], h['frame'] + 8 - sl['x2'],
                  sl['x3'], h['frame'] + 8 - sl['x3'],
                  sl['x4'], h['frame'] + 8 - sl['x4'],
                  sl['x5'], h['frame'] + 8 - sl['x5'],
                  h['t1'], sl['x7'], sl['x6'], sl['x1'],
                  h['t2'], h['o2'], h['o2'], h['o3']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_k2.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_k2.cpp — the seams of family K2.',
      '#include "modules/syndicate/src/synthunks_k2.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnK2A_%x)(void*, void*, void*, void*) = nullptr;' % x for x in s1]
sc += ['void* (*g_fnK2B_%x)(void*) = nullptr;' % x for x in s2]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_k2.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family K2 — staged words, the three pointers, and the teardown.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_k2.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_p2 = 0, g_p3 = 0, g_p4 = 0, g_this = 0, g_obj = 0; static int g_nA = 0, g_nB = 0;',
     'static void HookA(void* pThis, void* d, void* c, void* b) { ++g_nA; g_this = (uintptr_t)pThis; g_p2 = (uintptr_t)b; g_p3 = (uintptr_t)c; g_p4 = (uintptr_t)d; }',
     'static void* HookB(void* pObj) { ++g_nB; g_obj = (uintptr_t)pObj; return (void*)0x5150; }', '',
     'static unsigned char aThis[0x200]; static unsigned char aObj[0x40];', '', 'int main() {']
T += ['    g_fnK2A_%x = &HookA;' % x for x in s1]
T += ['    g_fnK2B_%x = &HookB;' % x for x in s2]
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        std::memset(aThis, 0xCC, sizeof(aThis));\n'
             '        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7\n'
             '        *(void**)(aThis + 0x%x) = (void*)0x1111;       // [this+o1]\n'
             '        *(void**)(aThis + 0x%x) = aObj;                // [this+o2]\n'
             '        *(void**)(aThis + 0x%x) = (void*)0x2222;       // [this+o3]\n'
             '        g_nA = g_nB = 0;\n'
             '        void* pR = SynStage_%x(aThis);\n'
             '        CHECK(g_nA == 1);\n        CHECK(g_nB == 1);\n'
             '        CHECK(g_this == (uintptr_t)aThis);\n'
             '        CHECK(g_obj == (uintptr_t)aObj);\n'
             '        CHECK(pR == (void*)0x5150);                    // t2 decides the answer\n'
             '        CHECK(*(void**)(aThis + 0x%x) == nullptr);     // [this+o2] cleared\n'
             '        CHECK(*(void**)(aThis + 0x%x) == nullptr);     // [this+o3] cleared\n'
             '        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);\n'
             '        (void)g_p3; (void)g_p4;\n    }'
             % (h['a'], h['o1'], h['o2'], h['o3'], h['a'], h['o2'], h['o3']))
T += ['', '    std::printf("SYNDICATE_THUNKS_K2_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_k2_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_k2.json', 'w'))
