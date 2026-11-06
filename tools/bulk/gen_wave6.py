#!/usr/bin/env python3
"""Sixth wave: family L — the literal-reporting helpers.

Body (13 instructions, matched exactly):
    mov [rsp+0x10],rdx ; push rbp ; sub rsp,0x20 ; mov rbp,rdx ; mov r8d,<line>
    lea rdx,[rip@<text>] ; lea rcx,[rip@<text2>] ; call [rip@<slot>]
    lea rax,[rip@<answer>] ; jmp <epilogue> ; add rsp,0x20 ; pop rbp ; ret
`r9` is never written, so the fourth argument of the wrapper is forwarded untouched.
The tail jump must land on the epilogue instruction, which is checked, not assumed.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_l'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

L = re.compile(r'mov QWORD PTR \[rsp\+0x10\],rdx ; push rbp ; sub rsp,0x20 ; mov rbp,rdx ; '
               r'mov r8d,(0x[0-9a-f]+) ; lea rdx,\[rip@(0x[0-9a-f]+)\] ; '
               r'lea rcx,\[rip@(0x[0-9a-f]+)\] ; call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; '
               r'lea rax,\[rip@(0x[0-9a-f]+)\] ; jmp (0x[0-9a-f]+) ; add rsp,0x20 ; pop rbp ; ret')

hits, rejected = [], 0
for f in rem:
    m = L.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    if idx.get(int(m.group(6), 16)) != 10:      # the tail jump must reach the epilogue
        rejected += 1
        continue
    hits.append({'a': f['a'], 'line': int(m.group(1), 16), 'text': int(m.group(2), 16),
                 'text2': int(m.group(3), 16), 'slot': int(m.group(4), 16), 'ans': int(m.group(5), 16)})
print('family L', len(hits), 'rejected', rejected)

hdr = ['// synthunks_l.h — RAW Syndicate.dll v6159 · %d literal-reporting helpers (family L).' % len(hits),
       '// Each one reports (text2, text, line, arg4) to the same sink and answers a fixed address.',
       '// The tail jump was required to land on the epilogue before the body was accepted.',
       '#ifndef TQ_SYN_THUNKS_L_H', '#define TQ_SYN_THUNKS_L_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
sl = sorted({h['slot'] for h in hits})
hdr += ['extern void (*g_fnRep_%x)(void* pA, void* pB, uint32_t nLine, void* pFourth);' % s for s in sl] + ['']
for h in hits:
    hdr.append('inline void* SynLit_%x(void* a1, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    (void)a1; (void)a2; (void)a3;\n'
               '    g_fnRep_%x((void*)0x%x, (void*)0x%x, 0x%x, a4);\n'
               '    return (void*)0x%x;\n}'
               % (h['a'], h['a'], h['slot'], h['text2'], h['text'], h['line'], h['ans']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_l.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_l.cpp — the report seams of family L.',
      '#include "modules/syndicate/src/synthunks_l.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnRep_%x)(void*, void*, uint32_t, void*) = nullptr;' % s for s in sl]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_l.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family L — one check per helper.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_l.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_a = 0, g_b = 0, g_f = 0; static uint32_t g_nLine = 0; static int g_nCalls = 0;', '']
T += ['static void RepHook_%x(void* a, void* b, uint32_t n, void* f) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_nLine = n; g_f = (uintptr_t)f; ++g_nCalls; }' % s for s in sl]
T += ['', 'int main() {']
T += ['    g_fnRep_%x = &RepHook_%x;' % (s, s) for s in sl]
T += ['    int sentinel = 7;']
for h in hits:
    T.append('    {   // 0x%x\n        g_nCalls = 0;\n'
             '        void* pBack = SynLit_%x(nullptr, nullptr, nullptr, &sentinel);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_a == 0x%x);\n        CHECK(g_b == 0x%x);\n'
             '        CHECK(g_nLine == 0x%x);\n        CHECK(g_f == (uintptr_t)&sentinel);\n'
             '        CHECK(pBack == (void*)0x%x);\n    }'
             % (h['a'], h['a'], h['text2'], h['text'], h['line'], h['ans']))
T += ['', '    std::printf("SYNDICATE_THUNKS6_OK: {0} helpers, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks6_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest6.json', 'w'))
