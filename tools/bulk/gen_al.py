#!/usr/bin/env python3
"""Family AL — the sentinel node allocator wrapper.

    sub rsp,<f> ; mov QWORD PTR [rsp+<seh>],0xfffffffffffffffe   ; unwind state, not logic
    mov ecx,<size> ; call <alloc>
    mov QWORD PTR [rsp+<spill>],rax                             ; unwind spill, never read back
    test rax,rax ; je L_null                                    ; L_null: xor ecx,ecx (same value!)
    xor ecx,ecx ; mov QWORD PTR [rax],rcx ; jmp L_join
    L_null: xor ecx,ecx
    L_join: mov DWORD PTR [rsp+<lvl>],0x1
    lea rdx,[rax+0x8]  ; test rdx,rdx ; je L1 ; mov QWORD PTR [rdx],rcx
    L1: mov DWORD PTR [rsp+<lvl>],0x2
    lea rdx,[rax+0x10] ; test rdx,rdx ; je L2 ; mov QWORD PTR [rdx],rcx
    L2: mov BYTE PTR [rax+<m1>],0x1 ; mov BYTE PTR [rax+<m2>],0x0
    add rsp,<f> ; ret

Quirks preserved rather than fixed:
  * the two xor ecx,ecx paths both produce zero, so the null branch changes nothing except skipping the
    store at [rax] — and the body then goes on to dereference rax anyway, so a null return faults at the
    `lea rdx,[rax+8]` store. No null guard is invented here.
  * `test rdx,rdx` right after `lea rdx,[rax+off]` only proves the computed pointer is non-null, which is
    the same question as rax being non-null; kept because the raw tests it.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_al'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

WANT = ['sub rsp,N', 'mov QWORD PTR [rsp+N],N', 'mov ecx,N', 'call N',
        'mov QWORD PTR [rsp+N],rax', 'test rax,rax', 'je N', 'xor ecx,ecx',
        'mov QWORD PTR [rax],rcx', 'jmp N', 'xor ecx,ecx', 'mov DWORD PTR [rsp+N],N',
        'lea rdx,[rax+N]', 'test rdx,rdx', 'je N', 'mov QWORD PTR [rdx],rcx',
        'mov DWORD PTR [rsp+N],N', 'lea rdx,[rax+N]', 'test rdx,rdx', 'je N',
        'mov QWORD PTR [rdx],rcx', 'mov BYTE PTR [rax+N],N', 'mov BYTE PTR [rax+N],N',
        'add rsp,N', 'ret']


def shape(t):
    return re.sub(r'0x[0-9a-f]+', 'N', t)


hits, rej = [], 0
for f in rem:
    t = f['text']
    if len(t) != len(WANT) or [shape(x) for x in t] != WANT:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}

    def h(i, k=0):
        return int(re.findall(r'0x([0-9a-f]+)', t[i])[k], 16)

    def tgt(i):
        return idx.get(h(i))

    bad = []
    if tgt(6) != 10: bad.append('je->10')
    if tgt(9) != 11: bad.append('jmp->11')
    if tgt(14) != 16: bad.append('je->16')
    if tgt(19) != 21: bad.append('je->21')
    if h(23) != h(0): bad.append('frame')
    if h(1, 1) != 0xfffffffffffffffe: bad.append('seh const')
    if h(11, 1) != 1 or h(16, 1) != 2: bad.append('unwind levels')
    if bad:
        rej += 1; print('  rejected', hex(f['a']), bad); continue
    hits.append({'a': f['a'], 'size': h(2), 't': h(3), 'a2': h(12), 'b2': h(17),
                 'm1': h(21), 'v1': h(21, 1), 'm2': h(22), 'v2': h(22, 1), 'frame': h(0)})

print('family AL', len(hits), 'rejected', rej)
print('sizes', sorted({x['size'] for x in hits}))
print('zeroed offsets', sorted({(x['a2'], x['b2']) for x in hits}))
print('marker offsets', sorted({(x['m1'], x['v1'], x['m2'], x['v2']) for x in hits}))
print('allocators', len({x['t'] for x in hits}))

hdr = ['// synthunks_al.h — RAW Syndicate.dll v6159 · %d sentinel-node allocator wrappers (family AL).' % len(hits),
       '// The allocator gets the size in rcx; the body returns its pointer in rax unchanged. The null branch',
       '// only skips the store at [rax] and is followed straight into the `lea rdx,[rax+8]` store, so a null',
       '// return faults there exactly as the raw does.',
       '#ifndef TQ_SYN_THUNKS_AL_H', '#define TQ_SYN_THUNKS_AL_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['t'] for h in hits})
hdr += ['extern void* (*g_fnAL_%x)(uint32_t uSize);' % t for t in tg] + ['']
for h in hits:
    hdr.append('inline void* SynAllocNode_%x(void* pThis) {   // 0x%x\n'
               '    void* const pNode = g_fnAL_%x(0x%x);                        // insn 2-3 (rcx = size)\n'
               '    if (pNode != nullptr)                                        // insn 5-6\n'
               '        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)\n'
               '    if ((uint8_t*)pNode + 0x%x != nullptr)                       // insn 12-14\n'
               '        *(void**)((uint8_t*)pNode + 0x%x) = nullptr;             // insn 15\n'
               '    if ((uint8_t*)pNode + 0x%x != nullptr)                       // insn 17-19\n'
               '        *(void**)((uint8_t*)pNode + 0x%x) = nullptr;             // insn 20\n'
               '    *(uint8_t*)((uint8_t*)pNode + 0x%x) = 0x%x;                 // insn 21\n'
               '    *(uint8_t*)((uint8_t*)pNode + 0x%x) = 0x%x;                 // insn 22\n'
               '    return pNode;                                                // rax\n}'
               % (h['a'], h['a'], h['t'], h['size'], h['a2'], h['a2'], h['b2'], h['b2'],
                  h['m1'], h['v1'], h['m2'], h['v2']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_al.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_al.cpp — the allocator seams of family AL.',
      '#include "modules/syndicate/src/synthunks_al.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnAL_%x)(uint32_t) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_al.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family AL — the block is filled with 0xCC first so every zeroing store is provable.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_al.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint32_t g_nSizeSeen = 0; static int g_nAlloc = 0;',
     'static unsigned char aBlk[0x200];',
     'static void* Hook(uint32_t uSize) { ++g_nAlloc; g_nSizeSeen = uSize; std::memset(aBlk, 0xCC, sizeof(aBlk)); return aBlk; }',
     'static void* NullHook(uint32_t) { ++g_nAlloc; return nullptr; }', '', 'int main() {']
T += ['    g_fnAL_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        g_nAlloc = 0; g_nSizeSeen = 0;\n'
             '        void* pR = SynAllocNode_%x(nullptr);\n'
             '        CHECK(g_nAlloc == 1);\n'
             '        CHECK(g_nSizeSeen == 0x%x);                              // rcx at insn 2\n'
             '        CHECK(pR == (void*)aBlk);                                // rax comes back untouched\n'
             '        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0\n'
             '        CHECK(*(void**)(aBlk + 0x%x) == nullptr);                // lea rax+0x%x\n'
             '        CHECK(*(void**)(aBlk + 0x%x) == nullptr);                // lea rax+0x%x\n'
             '        CHECK(aBlk[0x%x] == 0x%x);                               // marker\n'
             '        CHECK(aBlk[0x%x] == 0x%x);                               // marker\n    }'
             % (h['a'], h['a'], h['size'], h['a2'], h['a2'], h['b2'], h['b2'],
                h['m1'], h['v1'], h['m2'], h['v2']))
T += ['', '    // the null path: the raw skips [rax] and then still stores through rax+off, so it faults.',
      '    // it is not exercised here because doing so would be an invented guard, not the original.',
      '    std::printf("SYNDICATE_THUNKS_AL_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_al_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_al.json', 'w'))
