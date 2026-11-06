#!/usr/bin/env python3
"""Fourth wave: the allocate-and-register skeleton (family H).

The body is matched position by position, and each branch target is RESOLVED to an instruction
index and checked against the skeleton, so the control flow is verified rather than assumed:
    p = operator new(K)
    if (p) *p = this
    *this = p
    return this
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_h'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

SK = ['push rbx', 'sub rsp,0x@N', 'mov QWORD PTR [rsp+0x20],0xfffffffffffffffe',
      'mov rbx,rcx', 'mov ecx,0x@K', 'call @T', 'mov QWORD PTR [rsp+0x@X],rax',
      'mov QWORD PTR [rsp+0x@Y],rax', 'test rax,rax', 'je @J1', 'mov QWORD PTR [rax],rbx',
      'jmp @J2', 'xor eax,eax', 'mov QWORD PTR [rbx],rax', 'mov rax,rbx', 'add rsp,0x@N',
      'pop rbx', 'ret']

def match(f):
    t = f['text']
    if len(t) != len(SK):
        return None
    out = {}
    for i, pat in enumerate(SK):
        if '@' not in pat:
            if t[i] != pat:
                return None
            continue
        rx = re.escape(pat).replace(re.escape('@N'), r'([0-9a-f]+)').replace(re.escape('@K'), r'([0-9a-f]+)') \
            .replace(re.escape('@X'), r'([0-9a-f]+)').replace(re.escape('@Y'), r'([0-9a-f]+)') \
            .replace(re.escape('@T'), r'(0x[0-9a-f]+)').replace(re.escape('@J1'), r'(0x[0-9a-f]+)') \
            .replace(re.escape('@J2'), r'(0x[0-9a-f]+)')
        if pat.startswith('mov QWORD PTR [rsp'):
            rx = rx.replace(re.escape('0x'), '0x', 1)
        m = re.fullmatch(rx, t[i])
        if not m:
            return None
        out[pat] = m.group(1)
    # the two stack spills are only SEH bookkeeping; nothing to check
    # branch targets must land exactly on the skeleton's instructions
    idx = {a: i for i, a in enumerate(f['addr'])}
    j1 = idx.get(int(out['je @J1'], 16)); j2 = idx.get(int(out['jmp @J2'], 16))
    if j1 != 12 or j2 != 13:
        return None
    if int(out['sub rsp,0x@N'], 16) != int(out['add rsp,0x@N'], 16):
        return None
    return {'a': f['a'], 'k': int(out['mov ecx,0x@K'], 16), 't': int(out['call @T'], 16)}

hits = [m for m in (match(f) for f in rem) if m]
print('family H', len(hits))

hdr = ['// synthunks_h.h — RAW Syndicate.dll v6159 · %d functions with the allocate-and-register' % len(hits),
       '// skeleton. Each body was matched position by position and both branch targets were resolved to',
       '// the skeleton instruction they must reach (the "skip the store" branch and the "skip the null"',
       '// branch), so the shape below is the disassembly, not an assumption.',
       '#ifndef TQ_SYN_THUNKS_H_H', '#define TQ_SYN_THUNKS_H_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({h['t'] for h in hits})
hdr += ['extern void* (*g_fnAlloc%x)(uint64_t nBytes);' % t for t in seams] + ['']
for h in hits:
    hdr.append('inline void* SynAlc_%x(void* pThis) {   // 0x%x\n'
               '    void** p = (void**)g_fnAlloc%x(0x%x);\n'
               '    if (p) *p = pThis;\n'
               '    *(void**)pThis = p;\n'
               '    return pThis;\n}' % (h['a'], h['a'], h['t'], h['k']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_h.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_h.cpp — the allocator seams. 0x1417f3166 is operator new in this build.',
      '#include "modules/syndicate/src/synthunks_h.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnAlloc%x)(uint64_t) = nullptr;' % t for t in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_h.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family H — one check per function, plus the null path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstring>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_h.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint64_t g_nAsked = 0; static int g_bGiveNull = 0; static unsigned char g_blk[64];',
     'static void* AllocHook(uint64_t n) { g_nAsked = n; return g_bGiveNull ? nullptr : (void*)g_blk; }', '']
T += ['', 'int main() {']
T += ['    g_fnAlloc%x = &AllocHook;' % t for t in seams]
T += ['', '    unsigned char aThis[16];', '    std::memset(aThis, 0xCC, sizeof(aThis));', '']
for h in hits:
    T.append('    {   // 0x%x\n        g_bGiveNull = 0; g_nAsked = 0;\n'
             '        void* pBack = SynAlc_%x(aThis);\n'
             '        CHECK(g_nAsked == 0x%x);\n        CHECK(pBack == aThis);\n'
             '        CHECK(*(void**)g_blk == aThis);\n'
             '        CHECK(*(void**)aThis == (void*)g_blk);\n'
             '        g_bGiveNull = 1;\n'
             '        pBack = SynAlc_%x(aThis);\n        CHECK(pBack == aThis);\n'
             '        CHECK(*(void**)aThis == nullptr);\n    }'
             % (h['a'], h['a'], h['k'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS4_OK: {0} functions, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks4_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest4.json', 'w'))
