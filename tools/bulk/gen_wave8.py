#!/usr/bin/env python3
"""Eighth wave: family L2 (the same reporter with any frame size) and family N (copy two qwords,
then hand both pointers to a target and answer the destination).

L2 exists because the first pass hard-coded a 0x20 frame; the shape only differs by the frame
size and the epilogue that the tail jump must reach.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_n'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

L2 = re.compile(r'mov QWORD PTR \[rsp\+0x10\],rdx ; push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; '
                r'mov r8d,(0x[0-9a-f]+) ; lea rdx,\[rip@(0x[0-9a-f]+)\] ; '
                r'lea rcx,\[rip@(0x[0-9a-f]+)\] ; call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; '
                r'lea rax,\[rip@(0x[0-9a-f]+)\] ; jmp (0x[0-9a-f]+) ; add rsp,0x\1 ; pop rbp ; ret')
N = re.compile(r'push rbx ; sub rsp,0x([0-9a-f]+) ; mov rax,QWORD PTR \[rcx\] ; mov rbx,rdx ; '
               r'mov QWORD PTR \[rdx\],rax ; mov rax,QWORD PTR \[rcx\+0x8\] ; '
               r'mov QWORD PTR \[rdx\+0x8\],rax ; call (0x[0-9a-f]+) ; mov rax,rbx ; '
               r'add rsp,0x\1 ; pop rbx ; ret')

l2, nn = [], []
for f in rem:
    b = ' ; '.join(f['text'])
    m = L2.fullmatch(b)
    if m:
        idx = {a: i for i, a in enumerate(f['addr'])}
        if idx.get(int(m.group(7), 16)) == len(f["text"]) - 3:
            l2.append({'a': f['a'], 'frame': int(m.group(1), 16), 'line': int(m.group(2), 16),
                       'text': int(m.group(3), 16), 'text2': int(m.group(4), 16),
                       'slot': int(m.group(5), 16), 'ans': int(m.group(6), 16)})
        continue
    m = N.fullmatch(b)
    if m:
        nn.append({'a': f['a'], 't': int(m.group(2), 16)})
print('L2', len(l2), 'N', len(nn))

hdr = ['// synthunks_n.h — RAW Syndicate.dll v6159 · families L2 and N.',
       '//   L2: the reporter with a frame size other than 0x20 (tail jump verified onto the epilogue)',
       '//   N:  copy two qwords into the destination, call the target with (source, destination),',
       '//       then answer the destination',
       '#ifndef TQ_SYN_THUNKS_N_H', '#define TQ_SYN_THUNKS_N_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
sl = sorted({e['slot'] for e in l2}); st = sorted({e['t'] for e in nn})
hdr += ['extern void (*g_fnRep2_%x)(void* pA, void* pB, uint32_t nLine, void* pFourth);' % s for s in sl]
hdr += ['extern void* (*g_fnN2_%x)(void* pSrc, void* pDst);' % t for t in st] + ['']
for e in l2:
    hdr.append('inline void* SynLit2_%x(void* a1, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    (void)a1; (void)a2; (void)a3;\n'
               '    g_fnRep2_%x((void*)0x%x, (void*)0x%x, 0x%x, a4);\n'
               '    return (void*)0x%x;\n}'
               % (e['a'], e['a'], e['slot'], e['text2'], e['text'], e['line'], e['ans']))
for e in nn:
    hdr.append('inline void* SynCp2_%x(void* pSrc, void* pDst) {   // 0x%x\n'
               '    *(void**)pDst = *(void**)pSrc;\n'
               '    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);\n'
               '    g_fnN2_%x(pSrc, pDst);\n'
               '    return pDst;\n}' % (e['a'], e['a'], e['t']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_n.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_n.cpp — the seams of families L2 and N.',
      '#include "modules/syndicate/src/synthunks_n.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnRep2_%x)(void*, void*, uint32_t, void*) = nullptr;' % s for s in sl]
sc += ['void* (*g_fnN2_%x)(void*, void*) = nullptr;' % t for t in st]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_n.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with families L2 and N — one check per body.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_n.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_a = 0, g_b = 0, g_f = 0, g_s = 0, g_d = 0; static uint32_t g_nLine = 0; static int g_nCalls = 0;', '']
T += ['static void Rep2_%x(void* a, void* b, uint32_t n, void* f) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_nLine = n; g_f = (uintptr_t)f; ++g_nCalls; }' % s for s in sl]
T += ['static void* N2_%x(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }' % t for t in st]
T += ['', 'int main() {']
T += ['    g_fnRep2_%x = &Rep2_%x;' % (s, s) for s in sl]
T += ['    g_fnN2_%x = &N2_%x;' % (t, t) for t in st]
T += ['    int sentinel = 3;', '    unsigned char aSrc[32], aDst[32];', '']
for e in l2:
    T.append('    {   // 0x%x\n        g_nCalls = 0;\n'
             '        void* pB = SynLit2_%x(nullptr, nullptr, nullptr, &sentinel);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_a == 0x%x);\n        CHECK(g_b == 0x%x);\n'
             '        CHECK(g_nLine == 0x%x);\n        CHECK(g_f == (uintptr_t)&sentinel);\n'
             '        CHECK(pB == (void*)0x%x);\n    }'
             % (e['a'], e['a'], e['text2'], e['text'], e['line'], e['ans']))
for e in nn:
    T.append('    {   // 0x%x\n        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;\n'
             '        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;\n        g_nCalls = 0;\n'
             '        void* pB = SynCp2_%x(aSrc, aDst);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_s == (uintptr_t)aSrc);\n'
             '        CHECK(g_d == (uintptr_t)aDst);\n'
             '        CHECK(*(uint64_t*)aDst == 0x1111);\n        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);\n'
             '        CHECK(pB == aDst);\n    }' % (e['a'], e['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS8_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(l2) + len(nn))]
open('tests/cqbase_thunks8_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump({'l2': l2, 'n': nn}, open('tools/bulk/manifest8.json', 'w'))
