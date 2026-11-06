#!/usr/bin/env python3
"""Fifth wave: families I (this+offset through an IAT slot), J (mask a global) and K (store a call's
answer into a global).

Family J and K touch module-level counters, so the port reaches them through extern pointers
instead of baking an image address into the code.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_i'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

SLOT = r'call QWORD PTR \[rip@(0x[0-9a-f]+)\]'
I = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; lea rcx,\[rbp\+(0x[0-9a-f]+)\] ; '
               r'call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; add rsp,0x\1 ; pop rbp ; ret')
I2 = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; lea rcx,\[rbp\+(0x[0-9a-f]+)\] ; '
                r'add rcx,0x([0-9a-f]+) ; call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; add rsp,0x\1 ; pop rbp ; ret')
J = re.compile(r'push rbp ; mov rbp,rdx ; mov eax,DWORD PTR \[rip@(0x[0-9a-f]+)\] ; and eax,(0x[0-9a-f]+) ; '
               r'mov DWORD PTR \[rip@(0x[0-9a-f]+)\],eax ; pop rbp ; ret')
K = re.compile(r'sub rsp,0x([0-9a-f]+) ; call QWORD PTR \[rip@(0x[0-9a-f]+)\] ; '
               r'mov DWORD PTR \[rip@(0x[0-9a-f]+)\],eax ; add rsp,0x\1 ; ret')

fam = {'i': [], 'j': [], 'k': []}
for f in rem:
    b = ' ; '.join(f['text'])
    m = I.fullmatch(b)
    if m:
        fam['i'].append({'a': f['a'], 'o': int(m.group(2), 16), 'k': 0, 's': int(m.group(3), 16)}); continue
    m = I2.fullmatch(b)
    if m:
        fam['i'].append({'a': f['a'], 'o': int(m.group(2), 16), 'k': int(m.group(3), 16),
                         's': int(m.group(4), 16)}); continue
    m = J.fullmatch(b)
    if m:
        fam['j'].append({'a': f['a'], 'src': int(m.group(1), 16), 'mask': int(m.group(2), 16),
                         'dst': int(m.group(3), 16)}); continue
    m = K.fullmatch(b)
    if m:
        fam['k'].append({'a': f['a'], 's': int(m.group(2), 16), 'dst': int(m.group(3), 16)})
print({k: len(v) for k, v in fam.items()})

hdr = ['// synthunks_i.h — RAW Syndicate.dll v6159 · families I, J and K, whole-body matches only.',
       '//   I: call an IAT slot with this+offset (the indirect twin of family D)',
       '//   J: mask a module-level counter in place',
       '//   K: store the answer of a slot call into a module-level counter',
       '// Globals are reached through pointers so no image address is baked into the port.',
       '#ifndef TQ_SYN_THUNKS_I_H', '#define TQ_SYN_THUNKS_I_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
sl = sorted({e['s'] for e in fam['i']} | {e['s'] for e in fam['k']})
gl = sorted({e['src'] for e in fam['j']} | {e['dst'] for e in fam['j']} | {e['dst'] for e in fam['k']})
hdr += ['extern void* (*g_fnSlot_%x)(void* pInterior);' % s for s in sl]
hdr += ['extern int32_t* g_pnGlob_%x;' % g for g in gl] + ['']
for e in fam['i']:
    hdr.append('inline void* SynThkI_%x(void* pUnused, void* pObj) {   // 0x%x\n'
               '    return g_fnSlot_%x((void*)((uint8_t*)pObj + 0x%x));\n}' % (e['a'], e['a'], e['s'], e['o'] + e['k']))
for e in fam['j']:
    hdr.append('inline int32_t SynMask_%x(void* pUnused, void* pUnused2) {   // 0x%x\n'
               '    *g_pnGlob_%x = *g_pnGlob_%x & 0x%x;\n    return *g_pnGlob_%x;\n}'
               % (e['a'], e['a'], e['dst'], e['src'], e['mask'], e['dst']))
for e in fam['k']:
    hdr.append('inline int32_t SynStore_%x(void* pUnused, void* pUnused2) {   // 0x%x\n'
               '    *g_pnGlob_%x = (int32_t)(intptr_t)g_fnSlot_%x(nullptr);\n    return *g_pnGlob_%x;\n}'
               % (e['a'], e['a'], e['dst'], e['s'], e['dst']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_i.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_i.cpp — the seams of families I, J and K.',
      '#include "modules/syndicate/src/synthunks_i.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnSlot_%x)(void*) = nullptr;' % s for s in sl]
sc += ['int32_t* g_pnGlob_%x = nullptr;' % g for g in gl]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_i.cpp', 'w').write('\n'.join(sc) + '\n')

k_uses_slot = {e['s'] for e in fam['k']}
T = ['// Generated with families I, J and K — one check per function.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_i.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_v1 = 0; static int g_nCalls = 0;',
     'static int32_t g_counters[%d];' % (len(gl) + 1), '']
T += ['static void* SlotHook_%x(void* p) { g_v1 = (uintptr_t)p; ++g_nCalls; return (void*)0x1234; }' % s for s in sl]
mx = max((e['o'] + e['k']) for e in fam['i']) if fam['i'] else 0
T += ['', 'static unsigned char g_ab[0x%x];   // one byte past the largest offset read' % (mx + 0x40), '', 'int main() {']
T += ['    g_fnSlot_%x = &SlotHook_%x;' % (s, s) for s in sl]
T += ['    for (int i = 0; i < %d; ++i) g_counters[i] = 0;' % (len(gl) + 1)]
for i, g in enumerate(gl):
    T.append('    g_pnGlob_%x = &g_counters[%d];' % (g, i))
T.append('')
for e in fam['i']:
    off = e['o'] + e['k']
    T.append('    {   // 0x%x\n        g_nCalls = 0; g_v1 = 0;\n'
             '        void* pBack = SynThkI_%x(g_ab, g_ab);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == (uintptr_t)(g_ab + 0x%x));\n'
             '        CHECK(pBack == (void*)0x1234);\n    }' % (e['a'], e['a'], off))
for e in fam['j']:
    T.append('    {   // 0x%x\n        *g_pnGlob_%x = 0x1ff;\n        int32_t r = SynMask_%x(nullptr, nullptr);\n'
             '        CHECK(r == (0x1ff & 0x%x));\n        CHECK(*g_pnGlob_%x == (0x1ff & 0x%x));\n    }'
             % (e['a'], e['src'], e['a'], e['mask'], e['dst'], e['mask']))
for e in fam['k']:
    T.append('    {   // 0x%x\n        *g_pnGlob_%x = 0;\n        int32_t r = SynStore_%x(nullptr, nullptr);\n'
             '        CHECK(r == 0x1234);\n        CHECK(*g_pnGlob_%x == 0x1234);\n    }'
             % (e['a'], e['dst'], e['a'], e['dst']))
T += ['', '    std::printf("SYNDICATE_THUNKS5_OK: {0} functions, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(fam['i']) + len(fam['j']) + len(fam['k']))]
open('tests/cqbase_thunks5_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(fam, open('tools/bulk/manifest5.json', 'w'))
