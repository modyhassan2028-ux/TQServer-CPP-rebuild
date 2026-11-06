#!/usr/bin/env python3
"""Family GX — the container invariant probe, generalised (superset of family GI).

Skeleton, with the parts that vary per body marked:

    0 push rbx ; 1 sub rsp,<f> ; 2 mov rax,[rcx] ; 3 mov rbx,rcx ; 4 test rax,rax
    5 jne -> 10
    6 call [rip@<seam>]                     ; this->f00 == 0 -> report
    7 mov rax,[rbx] ; 8 test rax,rax ; 9 je -> 11
   10 mov rax,[rax]                        ; p = this->f00->f00
   11 mov rax,[rax+<oLim>]
   12 cmp [rbx+<oCur>],rax
   13 <cc> -> 15
   14 call [rip@<seam>]                    ; the compare failed -> report
   15 mov rax,[rbx+<oCur2>]
  [16 add rax,<oAdd>]                       ; optional: the value handed back is offset
   .. add rsp,<f> ; pop rbx ; ret

Every branch index, both call targets being identical, and the frame size are asserted per body. The
conditional is taken from the raw: the report fires when the branch is NOT taken, so the C++ test is the
negation of the mnemonic. Mnemonics outside the table are rejected rather than guessed.

Preserved quirks: the `test rax,rax ; je` at 8-9 is only reachable with this->f00 already null and then
reads [rax+oLim] with rax == 0 (a fault); `[rbx]` is re-read at 7.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_gx'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

# report fires when the mnemonic is NOT taken; each entry is (C++ operator, the value it compares against)
CC = {
    'jb':  ('>=', 'the current value is not below the limit'),
    'jbe': ('>',  'the current value is above the limit'),
    'jae': ('<',  'the current value is below the limit'),
    'ja':  ('<=', 'the current value is not above the limit'),
    'jne': ('==', 'the current value equals the limit'),
    'je':  ('!=', 'the current value differs from the limit'),
}


def parse(f):
    t = f['text']
    if len(t) < 19:
        return None
    want = ['push rbx', 'sub rsp,N', 'mov rax,QWORD PTR [rcx]', 'mov rbx,rcx', 'test rax,rax',
            'jne N', 'call QWORD PTR [rip@N]', 'mov rax,QWORD PTR [rbx]', 'test rax,rax', 'je N',
            'mov rax,QWORD PTR [rax]', 'mov rax,QWORD PTR [rax+N]', 'cmp QWORD PTR [rbx+N],rax',
            None, 'call QWORD PTR [rip@N]', 'mov rax,QWORD PTR [rbx+N]']
    for i, w in enumerate(want):
        if w is None:
            continue
        if re.sub(r'0x[0-9a-f]+', 'N', t[i]) != w:
            return None
    m = re.fullmatch(r'(j\w+) 0x([0-9a-f]+)', t[13])
    if not m or m.group(1) not in CC:
        return None
    cc = m.group(1)
    idx = {a: i for i, a in enumerate(f['addr'])}
    if idx.get(int(m.group(2), 16)) != 15:
        return None
    # tail: either the epilogue straight away, or an add rax,imm first
    add = 0
    i = 16
    m2 = re.fullmatch(r'add rax,0x([0-9a-f]+)', t[i]) if i < len(t) else None
    if m2:
        add = int(m2.group(1), 16)
        i += 1
    if i + 3 != len(t):
        return None
    if re.sub(r'0x[0-9a-f]+', 'N', t[i]) != 'add rsp,N' or t[i + 1] != 'pop rbx' or t[i + 2] != 'ret':
        return None

    def h(k, j=0):
        return int(re.findall(r'0x([0-9a-f]+)', t[k])[j], 16)

    if idx.get(h(5)) != 10 or idx.get(h(9)) != 11:
        return None
    if h(6) != h(14):
        return None
    if h(i) != h(1):
        return None
    return {'a': f['a'], 'lim': h(11), 'cur': h(12), 'cur2': h(15), 'add': add,
            'cc': cc, 'op': CC[cc][0], 'why': CC[cc][1], 'seam': h(6)}


hits, seen = [], set()
for f in rem:
    d = parse(f)
    if d:
        hits.append(d)
print('family GX', len(hits))
for k in ('lim', 'cur', 'add', 'cc', 'seam'):
    print('  %-5s %s' % (k, sorted({str(x[k]) for x in hits})[:14]))

hdr = ['// synthunks_gx.h — RAW Syndicate.dll v6159 · %d container invariant probes (family GX).' % len(hits),
       '// The report fires when the raw\'s own conditional is not taken; each body keeps its own mnemonic.',
       '#ifndef TQ_SYN_THUNKS_GX_H', '#define TQ_SYN_THUNKS_GX_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['seam'] for h in hits})
hdr += ['extern void (*g_fnGX_%x)(void* pArg);' % t for t in tg] + ['']
for h in hits:
    expr = '(uint8_t*)*(void**)((uint8_t*)pThis + 0x%x)' % h['cur2']
    note = '15'
    if h['add']:
        expr += ' + 0x%x' % h['add']
        note = '15-16'
    hdr.append('inline void* SynProbeGX_%x(void* pThis) {   // 0x%x  (%s: %s)\n'
               '    if (*(void**)pThis == nullptr)                                 // insn 2-5\n'
               '        g_fnGX_%x(pThis);                                         // insn 6\n'
               '    void* p = *(void**)pThis;                                     // insn 7 (re-read)\n'
               '    if (p != nullptr)                                             // insn 8-9\n'
               '        p = *(void**)p;                                           // insn 10\n'
               '    if (*(void**)((uint8_t*)pThis + 0x%x) %s\n'
               '        *(void**)((uint8_t*)p + 0x%x))                            // insn 11-13\n'
               '        g_fnGX_%x(pThis);                                         // insn 14\n'
               '    return %s;                          // insn %s\n}'
               % (h['a'], h['a'], h['cc'], h['why'], h['seam'], h['cur'], h['op'], h['lim'],
                  h['seam'], expr, note))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_gx.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_gx.cpp — the report seams of family GX.',
      '#include "modules/syndicate/src/synthunks_gx.h"', '', 'namespace tq {', '']
sc += ['void (*g_fnGX_%x)(void*) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_gx.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family GX — for each body: below, equal and above the limit.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_gx.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static void* g_pSeen = nullptr; static int g_nRep = 0;',
     'static void Hook(void* p) { ++g_nRep; g_pSeen = p; }',
     'static unsigned char aThis[0x120], aA[0x80], aB[0x80];', '',
     'static void put(void* p, uint64_t off, void* v) { *(void**)((unsigned char*)p + off) = v; }',
     'static void* at(void* p, uint64_t off) { return *(void**)((unsigned char*)p + off); }', '',
     '// evaluates the body\'s own condition in C++, so the expectation is not hand-written per case',
     'static bool ShouldReport(const char* op, uintptr_t cur, uintptr_t lim) {',
     '    if (op[0] == \'>\' && op[1] == \'=\') return cur >= lim;',
     '    if (op[0] == \'<\' && op[1] == \'=\') return cur <= lim;',
     '    if (op[0] == \'>\') return cur > lim;',
     '    if (op[0] == \'<\') return cur < lim;',
     '    if (op[0] == \'=\' && op[1] == \'=\') return cur == lim;',
     '    if (op[0] == \'!\' && op[1] == \'=\') return cur != lim;',
     '    std::abort();',
     '}', '', 'int main() {']
T += ['    g_fnGX_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x   lim +0x%x, cur +0x%x, add 0x%x, %s\n'
             '        const uintptr_t uLim = 0x1000;\n'
             '        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };\n'
             '        for (int i = 0; i < 3; ++i) {\n'
             '            std::memset(aThis, 0, sizeof(aThis));\n'
             '            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x%x, (void*)uLim);\n'
             '            put(aThis, 0x%x, (void*)uCases[i]);\n'
             '            g_nRep = 0; g_pSeen = nullptr;\n'
             '            void* pR = SynProbeGX_%x(aThis);\n'
             '            CHECK(g_nRep == (ShouldReport("%s", uCases[i], uLim) ? 1 : 0));\n'
             '            if (g_nRep) CHECK(g_pSeen == (void*)aThis);\n'
             '            CHECK(pR == (uint8_t*)uCases[i] + 0x%x);\n'
             '        }\n    }'
             % (h['a'], h['lim'], h['cur'], h['add'], h['cc'], h['lim'], h['cur'],
                h['a'], h['op'], h['add']))
T += ['', '    std::printf("SYNDICATE_THUNKS_GX_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_gx_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_gx.json', 'w'))
