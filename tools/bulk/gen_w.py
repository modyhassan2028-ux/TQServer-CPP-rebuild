#!/usr/bin/env python3
"""Family W — the ranged-insert shape.

Whole body:
    push rbx ; sub rsp,<f> ; sub rdx,rcx ; mov rbx,r8 ; sar rdx,<k> ; lea rax,[rdx*<s>+0x0]
    sub rbx,rax ; test rdx,rdx ; jle <epilogue> ; mov r8,rcx ; mov r9,rax ; mov rdx,rax ;
    mov rcx,rbx ; call <slot> ; mov rax,rbx ; add rsp,<f> ; pop rbx ; ret
The `jle` is required to land on the `mov rax,rbx` epilogue, so the skip path is proven.
The port reads the element count as an unsigned difference exactly like `sar` does (signed shift).
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_w'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

P = re.compile(r'push rbx ; sub rsp,0x([0-9a-f]+) ; sub rdx,rcx ; mov rbx,r8 ; sar rdx,0x([0-9a-f]+) ; '
               r'lea rax,\[rdx\*([0-9]+)\+0x0\] ; sub rbx,rax ; test rdx,rdx ; jle (0x[0-9a-f]+) ; '
               r'mov r8,rcx ; mov r9,rax ; mov rdx,rax ; mov rcx,rbx ; '
               r'call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; mov rax,rbx ; add rsp,0x\1 ; pop rbx ; ret')
hits, rejected = [], []
for f in rem:
    m = P.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    if idx.get(int(m.group(4), 16)) != len(f['text']) - 4:      # jle -> `mov rax,rbx`
        rejected.append(f['a']); continue
    hits.append({'a': f['a'], 'frame': int(m.group(1), 16), 'shift': int(m.group(2), 16),
                 'size': int(m.group(3)), 'slot': int(m.group(5), 16)})
print('family W', len(hits), 'rejected', len(rejected))

hdr = ['// synthunks_w.h — RAW Syndicate.dll v6159 · %d ranged-insert bodies (family W).' % len(hits),
       '// Element count = (pEnd - pBegin) >> shift, byte span = count * size, and the call receives',
       '// (pBase, span, pBegin, span) exactly as the register setup does. The skip branch was verified',
       '// onto the `mov rax,rbx` epilogue.',
       '#ifndef TQ_SYN_THUNKS_W_H', '#define TQ_SYN_THUNKS_W_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({h['slot'] for h in hits})
hdr += ['extern void* (*g_fnW_%x)(void* a, void* b, void* c, void* d);' % s for s in seams] + ['']
for h in hits:
    hdr.append('inline void* SynRng_%x(void* pBegin, void* pEnd, void* pBase) {   // 0x%x\n'
               '    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> %d;\n'
               '    uint64_t nSpan = (uint64_t)n * %d;\n'
               '    void* pDst = (void*)((uint8_t*)pBase - nSpan);\n'
               '    if (!(n > 0)) return pDst;          // jle skips the call\n'
               '    g_fnW_%x(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);\n'
               '    return pDst;\n}' % (h['a'], h['a'], h['shift'], h['size'], h['slot']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_w.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_w.cpp — the seams of family W.',
      '#include "modules/syndicate/src/synthunks_w.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnW_%x)(void*, void*, void*, void*) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_w.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family W — both paths of every body.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_w.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_a = 0, g_b = 0, g_c = 0, g_d = 0; static int g_nCalls = 0;',
     'static void* Hook(void* a, void* b, void* c, void* d) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_c = (uintptr_t)c; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x77; }', '',
     'static unsigned char g_buf[0x400];', '', 'int main() {']
T += ['    g_fnW_%x = &Hook;' % s for s in seams]
T += ['    unsigned char* pBase = g_buf + 0x200;\n']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        unsigned char* pBegin = g_buf + 0x40;\n'
             '        unsigned char* pEnd = pBegin + 0x%x;   // exactly one element\n'
             '        g_nCalls = 0;\n'
             '        void* pR = SynRng_%x(pBegin, pEnd, pBase);\n'
             '        CHECK(g_nCalls == 1);\n'
             '        CHECK(g_c == (uintptr_t)pBegin);\n'
             '        CHECK((uintptr_t)pR == (uintptr_t)pBase - (%d * 0x%x));\n'
             '        CHECK(g_a == (uintptr_t)pR);\n'
             '        CHECK(g_b == (%d * 0x%x));\n'
             '        CHECK(g_d == (%d * 0x%x));\n'
             '        // same pointers: the count is zero, the call must be skipped\n'
             '        g_nCalls = 0;\n'
             '        pR = SynRng_%x(pBegin, pBegin, pBase);\n'
             '        CHECK(g_nCalls == 0);\n'
             '        CHECK((uintptr_t)pR == (uintptr_t)pBase);\n    }'
             % (h['a'], h['size'], h['a'],
                1, h['size'], 1, h['size'], 1, h['size'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS_W_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_w_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_w.json', 'w'))
