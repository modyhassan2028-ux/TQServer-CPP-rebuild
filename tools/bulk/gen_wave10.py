#!/usr/bin/env python3
"""Tenth wave: family O — the two-word setter that resolves a null third argument through a slot.

    *this = 0
    this[8] = arg2
    if (!arg3) slot(this, arg2, 0)      // jne skips the call, so the call only runs when arg3 == 0
    *this = *(void**)arg3               // read unconditionally, exactly as the disassembly does
    return this
The jne target is required to land on the load.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_o'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

O = re.compile(r'mov QWORD PTR \[rsp\+0x8\],rbx ; push rdi ; sub rsp,0x20 ; mov rdi,r8 ; mov rbx,rcx ; '
               r'mov QWORD PTR \[rcx\],0x0 ; mov QWORD PTR \[rcx\+0x8\],rdx ; test r8,r8 ; jne (0x[0-9a-f]+) ; '
               r'call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; mov rax,QWORD PTR \[rdi\] ; '
               r'mov QWORD PTR \[rbx\],rax ; mov rax,rbx ; mov rbx,QWORD PTR \[rsp\+0x30\] ; '
               r'add rsp,0x20 ; pop rdi ; ret')

hits = []
for f in rem:
    m = O.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    if idx.get(int(m.group(1), 16)) != 10:
        continue
    hits.append({'a': f['a'], 'slot': int(m.group(2), 16)})
print('family O', len(hits))

hdr = ['// synthunks_o.h — RAW Syndicate.dll v6159 · %d two-word setters (family O).' % len(hits),
       '// The third argument is read unconditionally after the guard, so the port does the same;',
       '// the guard only decides whether the slot is called first.',
       '#ifndef TQ_SYN_THUNKS_O_H', '#define TQ_SYN_THUNKS_O_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
sl = sorted({h['slot'] for h in hits})
hdr += ['extern void (*g_fnO_%x)(void* pThis, void* pArg2, void* pArg3);' % s for s in sl] + ['']
for h in hits:
    hdr.append('inline void* SynSet2_%x(void* pThis, void* pArg2, void* pArg3) {   // 0x%x\n'
               '    *(void**)pThis = nullptr;\n'
               '    *(void**)((uint8_t*)pThis + 0x8) = pArg2;\n'
               '    if (!pArg3) g_fnO_%x(pThis, pArg2, nullptr);\n'
               '    *(void**)pThis = *(void**)pArg3;\n'
               '    return pThis;\n}' % (h['a'], h['a'], h['slot']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_o.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_o.cpp — the seams of family O.',
      '#include "modules/syndicate/src/synthunks_o.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnO_%x)(void*, void*, void*) = nullptr;' % s for s in sl]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_o.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family O — the guarded path and the plain path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstring>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_o.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_t = 0, g_2 = 0; static int g_nCalls = 0;',
     'static void Hook(void* t, void* a2, void* a3) { g_t = (uintptr_t)t; g_2 = (uintptr_t)a2; ++g_nCalls; }', '',
     'int main() {']
T += ['    g_fnO_%x = &Hook;' % s for s in sl]
T += ['    unsigned char aThis[16], aSecond[16];', '    std::memset(aThis, 0xCC, sizeof(aThis));',
      '    *(void**)aSecond = (void*)0x1234;', '']
for h in hits:
    T.append('    {   // 0x%x\n        g_nCalls = 0;\n'
             '        void* pB = SynSet2_%x(aThis, (void*)0x77, aSecond);\n'
             '        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused\n'
             '        CHECK(pB == aThis);\n        CHECK(*(void**)aThis == (void*)0x1234);\n'
             '        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);\n'
             '        g_nCalls = 0; g_t = 0;\n'
             '        *(void**)aSecond = (void*)0x1234;\n'
             '        pB = SynSet2_%x(aThis, (void*)0x77, aSecond);\n'
             '        CHECK(g_nCalls == 0);\n    }' % (h['a'], h['a'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS10_OK: {0} setters, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks10_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest10.json', 'w'))
