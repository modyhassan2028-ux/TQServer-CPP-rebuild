#!/usr/bin/env python3
"""Family NF — the tree-node factory.

    push rdi ; sub rsp,<f> ; mov [rsp+<seh>],-2
    mov [rsp+<s1>],rbx ; mov [rsp+<s2>],rsi
    mov rbx,r9 ; mov rdi,r8 ; mov rsi,rdx          ; the three pointer arguments
    mov ecx,<size> ; call <alloc>
    mov r11,rax
    mov [rsp+<spill1>],rax ; mov [rsp+<spill2>],rax
    test rax,rax ; je <epilogue>                    ; a null allocation returns null, no stores at all
    mov [rax+0x0],rsi ; mov [rax+0x8],rdi ; mov [rax+0x10],rbx
    mov rax,[rsp+<stk key>] ; mov ecx,DWORD PTR [rax] ; mov DWORD PTR [r11+<offkey>],ecx
    movzx eax,BYTE PTR [rsp+<stk flag>] ; mov BYTE PTR [r11+<offflag1>],al
    mov BYTE PTR [r11+<offflag2>],0x0
    mov rax,r11 ; restore ; ret

The node is 0x20 bytes: three pointers, a 32-bit key, a flag byte and the tree's nil marker cleared. The
key is read through a pointer taken from a stack slot, so it survives the call. This is the routine the
220-instruction insert family calls to build its node.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_nf'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

WANT = ['push rdi', 'sub rsp,N', 'mov QWORD PTR [rsp+N],N', 'mov QWORD PTR [rsp+N],rbx',
        'mov QWORD PTR [rsp+N],rsi', 'mov rbx,r9', 'mov rdi,r8', 'mov rsi,rdx', 'mov ecx,N',
        'call N', 'mov r11,rax', 'mov QWORD PTR [rsp+N],rax', 'mov QWORD PTR [rsp+N],rax',
        'test rax,rax', 'je N', 'mov QWORD PTR [rax],rsi', 'mov QWORD PTR [rax+N],rdi',
        'mov QWORD PTR [rax+N],rbx', 'mov rax,QWORD PTR [rsp+N]', 'mov ecx,DWORD PTR [rax]',
        'mov DWORD PTR [r11+N],ecx', 'movzx eax,BYTE PTR [rsp+N]', 'mov BYTE PTR [r11+N],al',
        'mov BYTE PTR [r11+N],N', 'mov rax,r11', 'mov rbx,QWORD PTR [rsp+N]',
        'mov rsi,QWORD PTR [rsp+N]', 'add rsp,N', 'pop rdi', 'ret']


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

    bad = []
    if idx.get(h(14)) != 24: bad.append('je->24')          # the null path lands on the epilogue
    if h(23, 1) != 0: bad.append('nil marker not zero')
    if h(27) != h(1): bad.append('frame')
    if h(2, 1) != 0xfffffffffffffffe: bad.append('seh const')
    if bad:
        rej += 1; print('  rejected', hex(f['a']), bad); continue
    hits.append({'a': f['a'], 'size': h(8), 't': h(9), 'key': h(20), 'flag1': h(22),
                 'flag2': h(23), 'frame': h(1)})

print('family NF', len(hits), 'rejected', rej)
print('sizes', sorted({x['size'] for x in hits}), 'key off', sorted({x['key'] for x in hits}),
      'flag offs', sorted({(x['flag1'], x['flag2']) for x in hits}))

hdr = ['// synthunks_nf.h — RAW Syndicate.dll v6159 · %d tree-node factories (family NF).' % len(hits),
       '// 0x20-byte node: three pointers, a 32-bit key read through a stack-passed pointer, a flag byte and',
       '// the nil marker cleared. A null allocation returns null and stores nothing.',
       '#ifndef TQ_SYN_THUNKS_NF_H', '#define TQ_SYN_THUNKS_NF_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['t'] for h in hits})
hdr += ['extern void* (*g_fnNF_%x)(uint32_t uSize);' % t for t in tg] + ['']
for h in hits:
    hdr.append('inline void* SynMakeNode_%x(void* pThis, void* a2, void* a3, void* a4,\n'
               '                                 const uint32_t* pKey, uint8_t bFlag) {   // 0x%x\n'
               '    void* const pNode = g_fnNF_%x(0x%x);                          // insn 8-9\n'
               '    if (pNode == nullptr)                                         // insn 13-14\n'
               '        return nullptr;                                           // rax is still the null\n'
               '    *(void**)pNode = a2;                                          // insn 15\n'
               '    *(void**)((uint8_t*)pNode + 0x8) = a3;                        // insn 16\n'
               '    *(void**)((uint8_t*)pNode + 0x10) = a4;                       // insn 17\n'
               '    *(uint32_t*)((uint8_t*)pNode + 0x%x) = *pKey;                 // insn 18-20\n'
               '    *(uint8_t*)((uint8_t*)pNode + 0x%x) = bFlag;                  // insn 21-22\n'
               '    *(uint8_t*)((uint8_t*)pNode + 0x%x) = 0x0;                    // insn 23\n'
               '    return pNode;                                                 // insn 24\n}'
               % (h['a'], h['a'], h['t'], h['size'], h['key'], h['flag1'], h['flag2']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_nf.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_nf.cpp — the allocator seams of family NF.',
      '#include "modules/syndicate/src/synthunks_nf.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnNF_%x)(uint32_t) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_nf.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family NF — every field of the node, plus the null path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_nf.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint32_t g_nSize = 0; static int g_nAlloc = 0; static bool g_bNull = false;',
     'static unsigned char aNode[0x40];',
     'static void* Hook(uint32_t uSize) { ++g_nAlloc; g_nSize = uSize;',
     '    if (g_bNull) return nullptr;',
     '    std::memset(aNode, 0xCC, sizeof(aNode)); return aNode; }', '', 'int main() {']
T += ['    g_fnNF_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        static unsigned char key[4]; unsigned char a2 = 0, a3 = 0, a4 = 0;\n'
             '        const uint32_t uKey = 0xA1B2C3D4u; std::memcpy(key, &uKey, 4);\n'
             '        g_nAlloc = 0; g_nSize = 0; g_bNull = false;\n'
             '        void* pR = SynMakeNode_%x(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);\n'
             '        CHECK(g_nAlloc == 1); CHECK(g_nSize == 0x%x);\n'
             '        CHECK(pR == (void*)aNode);\n'
             '        CHECK(*(void**)(aNode + 0x0) == (void*)&a2);\n'
             '        CHECK(*(void**)(aNode + 0x8) == (void*)&a3);\n'
             '        CHECK(*(void**)(aNode + 0x10) == (void*)&a4);\n'
             '        CHECK(*(uint32_t*)(aNode + 0x%x) == 0xA1B2C3D4u);\n'
             '        CHECK(*(unsigned char*)(aNode + 0x%x) == 0x77);\n'
             '        CHECK(*(unsigned char*)(aNode + 0x%x) == 0x00);\n'
             '        g_bNull = true; g_nAlloc = 0;\n'
             '        pR = SynMakeNode_%x(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);\n'
             '        CHECK(pR == nullptr); CHECK(g_nAlloc == 1);   // no store ran: the block is untouched\n'
             '    }'
             % (h['a'], h['a'], h['size'], h['key'], h['flag1'], h['flag2'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS_NF_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_nf_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_nf.json', 'w'))
