#!/usr/bin/env python3
"""Family Z — the validated range setter.

    mov [rsp+8],rbx ; mov [rsp+0x10],rsi ; push rdi ; sub rsp,<f>
    mov rbx,r8 ; mov rdi,rdx ; mov rsi,rcx
    mov QWORD PTR [rcx],0x0
    test r8,r8      ; je  <call>
    cmp QWORD PTR [r8+<lo>],rdx ; ja <call>
    cmp rdx,QWORD PTR [r8+<hi>] ; jbe <after>
    <call slot>                      <- reached by all three guards
    mov rax,QWORD PTR [rbx]
    mov rbx,[rsp+..]
    mov QWORD PTR [rsi+<off>],rdi
    mov QWORD PTR [rsi],rax
    mov rax,rsi ; mov rsi,[rsp+..] ; add rsp,<f> ; pop rdi ; ret

The three guards must land exactly where the disassembly says: `je` and `ja` on the call,
`jbe` on the instruction after it. The comparisons are unsigned 64-bit (ja/jbe), so the port
compares as uint64_t, not as the pointer's signed value.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_z'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

P = re.compile(r'mov QWORD PTR \[rsp\+0x8\],rbx ; mov QWORD PTR \[rsp\+0x10\],rsi ; push rdi ; sub rsp,0x([0-9a-f]+) ; '
               r'mov rbx,r8 ; mov rdi,rdx ; mov rsi,rcx ; mov QWORD PTR \[rcx\],0x0 ; '
               r'test r8,r8 ; je (0x[0-9a-f]+) ; cmp QWORD PTR \[r8\+(0x[0-9a-f]+)\],rdx ; ja (0x[0-9a-f]+) ; '
               r'cmp rdx,QWORD PTR \[r8\+(0x[0-9a-f]+)\] ; jbe (0x[0-9a-f]+) ; '
               r'call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; mov rax,QWORD PTR \[rbx\] ; '
               r'mov rbx,QWORD PTR \[rsp\+0x[0-9a-f]+\] ; mov QWORD PTR \[rsi\+(0x[0-9a-f]+)\],rdi ; '
               r'mov QWORD PTR \[rsi\],rax ; mov rax,rsi ; mov rsi,QWORD PTR \[rsp\+0x[0-9a-f]+\] ; '
               r'add rsp,0x\1 ; pop rdi ; ret')
hits, rej = [], 0
for f in rem:
    m = P.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    ok = (idx.get(int(m.group(2), 16)) == 14 and      # first je -> the call
          idx.get(int(m.group(4), 16)) == 14 and      # ja       -> the call
          idx.get(int(m.group(6), 16)) == 15)         # jbe      -> after the call
    if not ok:
        rej += 1; continue
    hits.append({'a': f['a'], 'frame': int(m.group(1), 16), 'lo': int(m.group(3), 16),
                 'hi': int(m.group(5), 16), 'slot': int(m.group(7), 16), 'off': int(m.group(8), 16)})
print('family Z', len(hits), 'rejected', rej)

hdr = ['// synthunks_z.h — RAW Syndicate.dll v6159 · %d validated range setters (family Z).' % len(hits),
       '// *this = 0; then the guards: null source, source->lo > value, value > source->hi all report',
       '// through the same slot; only a value inside [lo, hi] skips it. The copy that follows reads',
       '// the source word unconditionally, exactly like the disassembly.',
       '#ifndef TQ_SYN_THUNKS_Z_H', '#define TQ_SYN_THUNKS_Z_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({h['slot'] for h in hits})
hdr += ['extern void (*g_fnZ_%x)(void* pThis, uint64_t nValue, void* pSrc);' % s for s in seams] + ['']
for h in hits:
    hdr.append('inline void* SynRange_%x(void* pThis, void* pValue, void* pSrc) {   // 0x%x  frame 0x%x\n'
               '    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;\n'
               '    *(void**)pThis = nullptr;                                            // insn 7\n'
               '    if (pSrc == nullptr                                                      // insn 8-9\n'
               '        || *(const uint64_t*)((const uint8_t*)pSrc + 0x%x) > nValue          // insn 10-11\n'
               '        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x%x))          // insn 12-13\n'
               '        g_fnZ_%x(pThis, nValue, pSrc);                                       // insn 14\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = pValue;                             // insn 17\n'
               '    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18\n'
               '    return pThis;                                                           // insn 19\n}'
               % (h['a'], h['a'], h['frame'], h['lo'], h['hi'], h['slot'], h['off']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_z.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_z.cpp — the report seams of family Z.',
      '#include "modules/syndicate/src/synthunks_z.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnZ_%x)(void*, uint64_t, void*) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_z.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family Z — every guard and the clean path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_z.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint64_t g_v = 0; static int g_nCalls = 0;',
     'static void Hook(void* p, uint64_t n, void* s) { g_v = n; ++g_nCalls; }', '',
     'static unsigned char g_this[64], g_src[64];', '', 'int main() {']
T += ['    g_fnZ_%x = &Hook;' % s for s in seams]
for h in hits:
    T.append('    {   // 0x%x\n'
             '        std::memset(g_this, 0xCC, sizeof(g_this));\n'
             '        *(uint64_t*)(g_src + 0x%x) = 10;   // lo\n'
             '        *(uint64_t*)(g_src + 0x%x) = 20;   // hi\n'
             '        *(void**)g_src = (void*)0xABC;     // the word copied afterwards\n'
             '        g_nCalls = 0;\n'
             '        void* pR = SynRange_%x(g_this, (void*)15, g_src);   // inside: no report\n'
             '        CHECK(g_nCalls == 0);\n'
             '        CHECK(*(void**)g_this == (void*)0xABC);\n'
             '        CHECK(*(void**)(g_this + 0x%x) == (void*)15);\n'
             '        CHECK(pR == g_this);\n'
             '        g_nCalls = 0;\n'
             '        SynRange_%x(g_this, (void*)25, g_src);              // above hi: report\n'
             '        CHECK(g_nCalls == 1);\n'
             '        CHECK(g_v == 25);\n'
             '        g_nCalls = 0;\n'
             '        SynRange_%x(g_this, (void*)5, g_src);               // below lo: report\n'
             '        CHECK(g_nCalls == 1);\n'
             '        CHECK(g_v == 5);\n'
             '        // the null-source path reports and then reads [0] out of the source, exactly as\n'
             '        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.\n'
             '    }'
             % (h['a'], h['lo'], h['hi'], h['a'], h['off'], h['a'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS_Z_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_z_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_z.json', 'w'))
