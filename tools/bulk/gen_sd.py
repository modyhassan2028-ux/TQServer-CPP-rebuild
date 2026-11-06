#!/usr/bin/env python3
"""Family SD — the sentinel node initialiser.

    push rbx ; sub rsp,<f> ; mov rbx,rcx ; call <t>          // t(this) allocates the sentinel
    mov [rbx+<oSlot>],rax                                    // this->slot = node
    mov BYTE PTR [rax+<oMark>],0x1                           // node->mark = 1
    mov rax,[rbx+<oSlot>] ; mov [rax+0x8],rax                 // parent = itself
    mov rax,[rbx+<oSlot>] ; mov [rax+0x0],rax                 // left   = itself
    mov rax,[rbx+<oSlot>] ; mov [rax+0x10],rax                // right  = itself
    mov QWORD PTR [rbx+<oAux>],0x0                           // this->aux = 0
    add rsp,<f> ; pop rbx ; ret

The body re-reads [rbx+slot] from memory before each store rather than keeping the node in a register,
which is preserved here. There is no null check on the allocator's result in the raw: a null return
faults at the mark store, and that is not "fixed".
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_sd'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

TEMPLATE = ['push rbx', 'sub rsp,N', 'mov rbx,rcx', 'call T',
            'mov QWORD PTR [rbx+S],rax', 'mov BYTE PTR [rax+M],N',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax+8],rax',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax],rax',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax+16],rax',
            'mov QWORD PTR [rbx+A],N', 'add rsp,F', 'pop rbx', 'ret']


def shape(t):
    s = re.sub(r'0x([0-9a-f]+)', 'N', t)
    s = re.sub(r'\[rbx\+N\]', '[rbx+S]', s)
    s = re.sub(r'\[rax\+N\]', '[rax+M]', s)
    s = re.sub(r'\[rax\+N\]', '[rax+X]', s)
    return s


hits, rej = [], 0
for f in rem:
    if len(f['text']) != len(TEMPLATE):
        continue
    t = f['text']
    # structural match: same mnemonics and same operand kinds
    def norm(i):
        # tokenise the three fixed links of the node BEFORE the generic hex mask
        s = t[i]
        s = s.replace('[rax],', '[rax+0x0],')
        s = s.replace('[rax+0x8],', '[rax+LINK_P],')
        s = s.replace('[rax+0x0],', '[rax+LINK_L],')
        s = s.replace('[rax+0x10],', '[rax+LINK_R],')
        s = re.sub(r'0x[0-9a-f]+', 'N', s)
        s = s.replace('[rbx+N]', '[rbx+S]')
        s = s.replace('[rax+N]', '[rax+M]')
        return s
    got = [norm(i) for i in range(len(t))]
    want = ['push rbx', 'sub rsp,N', 'mov rbx,rcx', 'call N',
            'mov QWORD PTR [rbx+S],rax', 'mov BYTE PTR [rax+M],N',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax+LINK_P],rax',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax+LINK_L],rax',
            'mov rax,QWORD PTR [rbx+S]', 'mov QWORD PTR [rax+LINK_R],rax',
            'mov QWORD PTR [rbx+S],N', 'add rsp,N', 'pop rbx', 'ret']
    if got != want:
        continue
    def h(i, k=0):
        return int(re.findall(r'0x([0-9a-f]+)', t[i])[k], 16)
    d = {'a': f['a'], 'slot': h(4), 'mark': h(5), 'aux': h(12), 'markv': h(5, 1),
         'frame': h(1), 'auxv': h(12, 1), 't': h(3)}
    if h(13) != d['frame']:
        rej += 1; print('  frame mismatch', hex(f['a'])); continue
    hits.append(d)
print('family SD', len(hits), 'rejected', rej)
print('slots', sorted({x['slot'] for x in hits}), 'aux', sorted({x['aux'] for x in hits}))
print('mark offsets', sorted({x['mark'] for x in hits}), 'mark values', sorted({x['markv'] for x in hits}))
print('allocators', sorted(hex(x['t']) for x in hits))

hdr = ['// synthunks_sd.h — RAW Syndicate.dll v6159 · %d sentinel-node initialisers (family SD).' % len(hits),
       '// The node is re-read from this->slot before each link store, exactly as the raw does it.',
       '#ifndef TQ_SYN_THUNKS_SD_H', '#define TQ_SYN_THUNKS_SD_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['t'] for h in hits})
hdr += ['extern void* (*g_fnSD_%x)(void* pThis);' % t for t in tg] + ['']
for h in hits:
    hdr.append('inline void SynSentinelInit_%x(void* pThis) {   // 0x%x\n'
               '    void* const pNode = g_fnSD_%x(pThis);                        // insn 3 (rcx = this)\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = pNode;                  // insn 4\n'
               '    *(uint8_t*)((uint8_t*)pNode + 0x%x) = 0x%x;                 // insn 5\n'
               '    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x%x) + 0x8) =      // insn 6-7\n'
               '        *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    *(void**)*(void**)((uint8_t*)pThis + 0x%x) =               // insn 8-9\n'
               '        *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x%x) + 0x10) =      // insn 10-11\n'
               '        *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = (void*)0x%x;           // insn 12\n}'
               % (h['a'], h['a'], h['t'], h['slot'], h['mark'], h['markv'],
                  h['slot'], h['slot'], h['slot'], h['slot'], h['slot'], h['slot'],
                  h['aux'], h['auxv']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_sd.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_sd.cpp — the allocator seams of family SD.',
      '#include "modules/syndicate/src/synthunks_sd.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnSD_%x)(void*) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_sd.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family SD — the sentinel points at itself on all three links.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_sd.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static void* g_pThisSeen = nullptr; static int g_nAlloc = 0;',
     'static unsigned char aNode[0x80]; static unsigned char aThis[0x80];',
     'static void Zero(void* p) { std::memset(p, 0, 0x80); }',
     'static void* Hook(void* pThis) { ++g_nAlloc; g_pThisSeen = pThis; Zero(aNode); return aNode; }', '',
     'int main() {']
T += ['    g_fnSD_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        std::memset(aThis, 0, sizeof(aThis));\n'
             '        g_nAlloc = 0;\n'
             '        SynSentinelInit_%x(aThis);\n'
             '        CHECK(g_nAlloc == 1);\n'
             '        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3\n'
             '        CHECK(*(void**)(aThis + 0x%x) == (void*)aNode);           // insn 4\n'
             '        CHECK(*(unsigned char*)(aNode + 0x%x) == 0x%x);           // insn 5\n'
             '        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self\n'
             '        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self\n'
             '        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self\n'
             '        CHECK(*(void**)(aThis + 0x%x) == (void*)0x%x);            // insn 12\n    }'
             % (h['a'], h['a'], h['slot'], h['mark'], h['markv'], h['aux'], h['auxv']))
T += ['', '    std::printf("SYNDICATE_THUNKS_SD_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_sd_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_sd.json', 'w'))
