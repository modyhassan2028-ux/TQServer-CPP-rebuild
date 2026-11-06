#!/usr/bin/env python3
"""Family GI — the container invariant probe.

    push rbx ; sub rsp,<f> ; mov rax,[rcx] ; mov rbx,rcx ; test rax,rax ; jne L10
    call <report>                                            ; this->f00 == 0 -> report
L10: mov rax,[rbx] ; test rax,rax ; je L11
    mov rax,[rax]                                            ; p = this->f00->f00
L11: mov rax,[rax+<oLim>] ; cmp [rbx+<oCur>],rax ; jb L15
    call <report>                                            ; cur >= lim -> report
L15: mov rax,[rbx+<oCur>] ; ... ; ret

The branches land on instruction indices 10, 11 and 15 and nowhere else; a body that disagrees is skipped.
Two quirks are kept exactly as the raw has them:
  * the `test rax,rax ; je` at insn 8-9 can only fire on the path where this->f00 was already null, and
    that path then reads [rax+oLim] with rax == 0, so it faults; no guard is added here.
  * `[rbx]` is re-read at insn 7 instead of reusing rax from insn 2.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_gi'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

WANT = ['push rbx', 'sub rsp,N', 'mov rax,QWORD PTR [rcx]', 'mov rbx,rcx', 'test rax,rax',
        'jne N', 'call QWORD PTR [rip@N]', 'mov rax,QWORD PTR [rbx]', 'test rax,rax', 'je N',
        'mov rax,QWORD PTR [rax]', 'mov rax,QWORD PTR [rax+N]', 'cmp QWORD PTR [rbx+N],rax',
        'jb N', 'call QWORD PTR [rip@N]', 'mov rax,QWORD PTR [rbx+N]', 'add rsp,N', 'pop rbx', 'ret']


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
    if idx.get(h(5)) != 10: bad.append('jne->10')
    if idx.get(h(9)) != 11: bad.append('je->11')
    if idx.get(h(13)) != 15: bad.append('jb->15')
    if h(16) != h(1): bad.append('frame')
    if h(14) != h(6): bad.append('report seam differs on the two sites')
    if bad:
        rej += 1; print('  rejected', hex(f['a']), bad); continue
    hits.append({'a': f['a'], 'lim': h(11), 'cur': h(12), 'cur2': h(15), 'seam': h(6)})

print('family GI', len(hits), 'rejected', rej)
print('limit offsets', sorted({x['lim'] for x in hits}), 'current offsets', sorted({(x['cur'], x['cur2']) for x in hits}))

hdr = ['// synthunks_gi.h — RAW Syndicate.dll v6159 · %d container invariant probes (family GI).' % len(hits),
       '// Reports through the same seam the iterators use, then returns the current value unchanged.',
       '#ifndef TQ_SYN_THUNKS_GI_H', '#define TQ_SYN_THUNKS_GI_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['seam'] for h in hits})
hdr += ['extern void (*g_fnGI_%x)(void* pArg);' % t for t in tg] + ['']
for h in hits:
    hdr.append('inline void* SynProbe_%x(void* pThis) {   // 0x%x\n'
               '    if (*(void**)pThis == nullptr)                                 // insn 2-5\n'
               '        g_fnGI_%x(pThis);                                         // insn 6\n'
               '    void* p = *(void**)pThis;                                     // insn 7 (re-read)\n'
               '    if (p != nullptr)                                             // insn 8-9\n'
               '        p = *(void**)p;                                           // insn 10\n'
               '    if (*(void**)((uint8_t*)pThis + 0x%x) >=\n'
               '        *(void**)((uint8_t*)p + 0x%x))                            // insn 11-13\n'
               '        g_fnGI_%x(pThis);                                         // insn 14\n'
               '    return *(void**)((uint8_t*)pThis + 0x%x);                     // insn 15\n}'
               % (h['a'], h['a'], h['seam'], h['cur'], h['lim'], h['seam'], h['cur2']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_gi.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_gi.cpp — the report seams of family GI.',
      '#include "modules/syndicate/src/synthunks_gi.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnGI_%x)(void*) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_gi.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family GI — both sides of the limit comparison, plus the report seam argument.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_gi.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static void* g_pSeen = nullptr; static int g_nRep = 0;',
     'static void Hook(void* p) { ++g_nRep; g_pSeen = p; }',
     'static unsigned char aThis[0x80], aA[0x80], aB[0x80];', '',
     'static void put(void* p, uint64_t off, void* v) { *(void**)((unsigned char*)p + off) = v; }',
     'static void* at(void* p, uint64_t off) { return *(void**)((unsigned char*)p + off); }', '', 'int main() {']
T += ['    g_fnGI_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x   lim +0x%x, cur +0x%x\n'
             '        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));\n'
             '        put(aThis, 0x0, aA);      // this->f00\n'
             '        put(aA, 0x0, aB);         // this->f00->f00\n'
             '        put(aB, 0x%x, (void*)0x100);\n'
             '        g_nRep = 0; g_pSeen = nullptr;\n'
             '        put(aThis, 0x%x, (void*)0x10);          // below the limit\n'
             '        void* pR = SynProbe_%x(aThis);\n'
             '        CHECK(g_nRep == 0);\n'
             '        CHECK(pR == (void*)0x10);\n'
             '        g_nRep = 0; g_pSeen = nullptr;\n'
             '        put(aThis, 0x%x, (void*)0x100);         // exactly at the limit: reports\n'
             '        pR = SynProbe_%x(aThis);\n'
             '        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);\n'
             '        CHECK(pR == (void*)0x100);\n'
             '        g_nRep = 0; g_pSeen = nullptr;\n'
             '        put(aThis, 0x%x, (void*)0x1000);        // above the limit\n'
             '        pR = SynProbe_%x(aThis);\n'
             '        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);\n'
             '        CHECK(pR == (void*)0x1000);\n    }'
             % (h['a'], h['lim'], h['cur'], h['lim'], h['cur'], h['a'],
                h['cur'], h['a'], h['cur'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS_GI_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_gi_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_gi.json', 'w'))
