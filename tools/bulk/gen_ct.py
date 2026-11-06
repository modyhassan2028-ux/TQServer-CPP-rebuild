#!/usr/bin/env python3
"""Family CT — the container constructor (map/set-style).

Optional inert prologue: one or two `mov [rsp+N],<arg reg>` home-store spills of the incoming arguments
that the body never reads back. Then:

    push rbx ; sub rsp,<f> ; mov [rsp+<seh>],-2 ; mov rbx,rcx
    mov ecx,<s> ; call <alloc8>                     ; the small "owning" node
    mov [rsp+..],rax (x2, spills) ; test rax,rax ; je L_null
    mov [rax],rbx ; jmp L_join                      ; L_null: xor eax,eax
    L_join: mov [rbx],rax                           ; this->f00 = small node (null on the null path)
    mov rcx,rbx ; call <sentinel>                   ; the sentinel allocator, rcx = this
    mov [rbx+0x30],rax ; mov BYTE PTR [rax+<m>],0x1
    mov rax,[rbx+0x30] ; mov [rax+0x8],rax          ; parent = self
    mov rax,[rbx+0x30] ; mov [rax],rax              ; left   = self
    mov rax,[rbx+0x30] ; mov [rax+0x10],rax         ; right  = self
    mov QWORD PTR [rbx+0x38],0x0 ; mov rax,rbx      ; returns this
    add rsp,<f> ; pop rbx ; ret

Both the null check and its `xor eax,eax` are kept in the C++ even though the two branches produce the same
value, because the raw's shape is part of the port.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_ct'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

BODY = ['push rbx', 'sub rsp,N', 'mov QWORD PTR [rsp+N],N', 'mov rbx,rcx', 'mov ecx,N', 'call N',
        'mov QWORD PTR [rsp+N],rax', 'mov QWORD PTR [rsp+N],rax', 'test rax,rax', 'je N',
        'mov QWORD PTR [rax],rbx', 'jmp N', 'xor eax,eax', 'mov QWORD PTR [rbx],rax',
        'mov rcx,rbx', 'call N', 'mov QWORD PTR [rbx+N],rax', 'mov BYTE PTR [rax+N],N',
        'mov rax,QWORD PTR [rbx+N]', 'mov QWORD PTR [rax+N],rax',
        'mov rax,QWORD PTR [rbx+N]', 'mov QWORD PTR [rax],rax',
        'mov rax,QWORD PTR [rbx+N]', 'mov QWORD PTR [rax+N],rax',
        'mov QWORD PTR [rbx+N],N', 'mov rax,rbx', 'add rsp,N', 'pop rbx', 'ret']

hits, rej = [], 0
for f in rem:
    t = f['text']
    lead = 0
    while lead < len(t) and re.fullmatch(r'mov QWORD PTR \[rsp\+0x[0-9a-f]+\],r(dx|cx|8|9)', t[lead]):
        lead += 1
    if lead > 2 or lead < 1:
        continue
    body = t[lead:]
    if len(body) != len(BODY) or [re.sub(r'0x[0-9a-f]+', 'N', x) for x in body] != BODY:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}

    def h(k, j=0, off=None):
        return int(re.findall(r'0x([0-9a-f]+)', (body if off is None else t)[k])[j], 16)

    def tgt(k):
        return idx.get(h(k))

    bad = []
    if tgt(9) != lead + 12: bad.append('je->null')
    if tgt(11) != lead + 13: bad.append('jmp->join')
    if h(2, 1) != 0xfffffffffffffffe: bad.append('seh const')
    if h(26) != h(1): bad.append('frame')
    if h(24, 1) != 0: bad.append('aux not zero')
    if h(4) != 8: bad.append('small node size')
    if bad:
        rej += 1; print('  rejected', hex(f['a']), bad); continue
    hits.append({'a': f['a'], 'lead': lead, 'alloc8': h(5), 'sent': h(15), 'mark': h(17),
                 'slot': h(16), 'aux': h(24), 'frame': h(1), 'markv': h(17, 1)})

print('family CT', len(hits), 'rejected', rej)
for k in ('lead', 'alloc8', 'sent', 'mark', 'slot', 'aux', 'markv'):
    print('  %-6s %s' % (k, sorted({str(x[k]) for x in hits})[:8]))

hdr = ['// synthunks_ct.h — RAW Syndicate.dll v6159 · %d container constructors (family CT).' % len(hits),
       '// Small owning node in this->f00, sentinel in this->f30 wired to itself, this->f38 cleared.',
       '#ifndef TQ_SYN_THUNKS_CT_H', '#define TQ_SYN_THUNKS_CT_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
for t2 in sorted({h['alloc8'] for h in hits}):
    hdr.append('extern void* (*g_fnCT_small_%x)(uint32_t uSize);' % t2)
for t2 in sorted({h['sent'] for h in hits}):
    hdr.append('extern void* (*g_fnCT_sent_%x)(void* pThis);' % t2)
hdr.append('')
for h in hits:
    hdr.append('inline void* SynContainerCtor_%x(void* pThis) {   // 0x%x\n'
               '    void* pSmall = g_fnCT_small_%x(0x%x);                        // insn %d-%d\n'
               '    if (pSmall == nullptr)                                       // both paths yield a null here\n'
               '        pSmall = nullptr;                                        //   (xor eax,eax)\n'
               '    *(void**)pThis = pSmall;                                     // insn %d\n'
               '    void* const pSent = g_fnCT_sent_%x(pThis);                   // insn %d-%d (rcx = this)\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = pSent;                   // insn %d\n'
               '    *(uint8_t*)((uint8_t*)pSent + 0x%x) = 0x%x;                  // insn %d\n'
               '    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn %d-%d\n'
               '    *(void**)pSent = pSent;                                      // insn %d-%d\n'
               '    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn %d-%d\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = (void*)0x0;              // insn %d\n'
               '    return pThis;                                                // insn %d\n}'
               % (h['a'], h['a'], h['alloc8'], 8, h['lead'] + 4, h['lead'] + 5, h['lead'] + 13,
                  h['sent'], h['lead'] + 14, h['lead'] + 15, h['slot'], h['lead'] + 16,
                  h['mark'], h['markv'], h['lead'] + 17, h['lead'] + 18, h['lead'] + 19,
                  h['lead'] + 20, h['lead'] + 21, h['lead'] + 22, h['lead'] + 23,
                  h['aux'], h['lead'] + 24, h['lead'] + 25))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_ct.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_ct.cpp — the allocator seams of family CT.',
      '#include "modules/syndicate/src/synthunks_ct.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnCT_small_%x)(uint32_t) = nullptr;' % t2 for t2 in sorted({h['alloc8'] for h in hits})]
sc += ['void* (*g_fnCT_sent_%x)(void*) = nullptr;' % t2 for t2 in sorted({h['sent'] for h in hits})]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_ct.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family CT — both allocators hooked, both the normal and the null small-node path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_ct.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint32_t g_nSize = 0; static int g_nSmall = 0, g_nSent = 0; static bool g_bNullSmall = false;',
     'static void* g_pSentArg = nullptr;',
     'static unsigned char aSmall[0x20], aSent[0x80], aThis[0x80];', '',
     'static void* SmallHook(uint32_t uSize) { ++g_nSmall; g_nSize = uSize;',
     '    if (g_bNullSmall) return nullptr;',
     '    std::memset(aSmall, 0xCC, sizeof(aSmall)); return aSmall; }',
     'static void* SentHook(void* pThis) { ++g_nSent; g_pSentArg = pThis;',
     '    std::memset(aSent, 0xCC, sizeof(aSent)); return aSent; }', '', 'int main() {']
for t2 in sorted({h['alloc8'] for h in hits}):
    T.append('    g_fnCT_small_%x = &SmallHook;' % t2)
for t2 in sorted({h['sent'] for h in hits}):
    T.append('    g_fnCT_sent_%x = &SentHook;' % t2)
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        std::memset(aThis, 0, sizeof(aThis));\n'
             '        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;\n'
             '        void* pR = SynContainerCtor_%x(aThis);\n'
             '        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);\n'
             '        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call\n'
             '        CHECK(pR == (void*)aThis);                          // returns this\n'
             '        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node\n'
             '        CHECK(*(void**)(aThis + 0x%x) == (void*)aSent);      // this->f30\n'
             '        CHECK(*(unsigned char*)(aSent + 0x%x) == 0x%x);      // mark\n'
             '        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self\n'
             '        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self\n'
             '        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self\n'
             '        CHECK(*(void**)(aThis + 0x%x) == nullptr);           // this->f38 = 0\n'
             '        std::memset(aThis, 0, sizeof(aThis));\n'
             '        g_nSmall = g_nSent = 0; g_bNullSmall = true;\n'
             '        pR = SynContainerCtor_%x(aThis);                     // null small node\n'
             '        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);\n'
             '        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path\n'
             '        CHECK(pR == (void*)aThis);\n    }'
             % (h['a'], h['a'], h['slot'], h['mark'], h['markv'], h['aux'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS_CT_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_ct_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_ct.json', 'w'))
