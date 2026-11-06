#!/usr/bin/env python3
"""Ninth wave: the allocate-and-register family again, matched structurally instead of by a fixed
prologue. The allocator call, the spills, the two branches and the epilogue are located by index,
and both branch targets are required to land where the skeleton says:
    je  -> the `xor eax,eax`
    jmp -> the `mov QWORD PTR [rbx],rax`
so a table variant with a different prologue or frame still has to prove its shape.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_h2'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

CALLRE = re.compile(r'call (?:0x([0-9a-f]+)|QWORD PTR \[rip@(0x[0-9a-f]+)\])')
def match(f):
    t = f['text']
    # the allocator call: `mov ecx,K` immediately followed by a call
    alloc = None
    for i in range(len(t) - 1):
        m = re.fullmatch(r'mov ecx,0x([0-9a-f]+)', t[i])
        if m:
            c = CALLRE.fullmatch(t[i + 1])
            if c:
                alloc = (i, int(m.group(1), 16), int(c.group(1), 16) if c.group(1) else None,
                         int(c.group(2), 16) if c.group(2) else None)
                break
    if not alloc:
        return None
    i, k, direct, slot = alloc
    # `mov rbx,rcx` must have happened before the allocator is called
    if 'mov rbx,rcx' not in t[:i]:
        return None
    j = i + 2
    while j < len(t) and re.fullmatch(r'mov QWORD PTR \[rsp\+0x[0-9a-f]+\],rax', t[j]):
        j += 1
    if j + 6 > len(t):
        return None
    if t[j] != 'test rax,rax' or t[j + 2] != 'mov QWORD PTR [rax],rbx' \
            or t[j + 4] != 'xor eax,eax' or t[j + 5] != 'mov QWORD PTR [rbx],rax':
        return None
    if not t[j + 1].startswith('je ') or not t[j + 3].startswith('jmp '):
        return None
    if j + 7 > len(t) or t[j + 6] != 'mov rax,rbx':
        return None
    idx = {a: n for n, a in enumerate(f['addr'])}
    if idx.get(int(t[j + 1].split()[1], 16)) != j + 4:      # je -> xor eax,eax
        return None
    if idx.get(int(t[j + 3].split()[1], 16)) != j + 5:      # jmp -> mov [rbx],rax
        return None
    # epilogue: add rsp / pop rbx / ret with nothing after
    if t[-1] != 'ret' or t[-2] != 'pop rbx' or not t[-3].startswith('add rsp,0x'):
        return None
    return {'a': f['a'], 'k': k, 'direct': direct, 'slot': slot, 'frame': int(t[-3].split(',')[1], 16)}

hits = [m for m in (match(f) for f in rem) if m]
print('family H2', len(hits), 'direct', sum(1 for h in hits if h['direct']), 'slot', sum(1 for h in hits if h['slot']))

def sn(h):
    return 'g_fnH2D%x' % h['direct'] if h['direct'] else 'g_fnH2S%x' % h['slot']

hdr = ['// synthunks_h2.h — RAW Syndicate.dll v6159 · %d table variants of allocate-and-register.' % len(hits),
       '// The prologue differs between tables (some spill the arguments first, some do not), so the shape',
       '// was located by index and both branch targets were verified onto the xor and the store.',
       '#ifndef TQ_SYN_THUNKS_H2_H', '#define TQ_SYN_THUNKS_H2_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({sn(h) for h in hits})
hdr += ['extern void* (*%s)(uint64_t nBytes);' % s for s in seams] + ['']
for h in hits:
    hdr.append('inline void* SynAlc2_%x(void* pThis) {   // 0x%x  frame 0x%x\n'
               '    void** p = (void**)%s(0x%x);\n'
               '    if (p) *p = pThis;\n'
               '    *(void**)pThis = p;\n'
               '    return pThis;\n}' % (h['a'], h['a'], h['frame'], sn(h), h['k']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_h2.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_h2.cpp — allocator seams for the table variants.',
      '#include "modules/syndicate/src/synthunks_h2.h"', '', 'namespace tq {', '']
sc += ['void* (*%s)(uint64_t) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_h2.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family H2 — one check per variant, plus the null path.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstring>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_h2.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uint64_t g_nAsked = 0; static int g_bNull = 0; static unsigned char g_blk[64];',
     'static void* Hook(uint64_t n) { g_nAsked = n; return g_bNull ? nullptr : (void*)g_blk; }', '',
     'int main() {']
T += ['    %s = &Hook;' % s for s in seams]
T += ['    unsigned char aThis[16];', '    std::memset(aThis, 0xCC, sizeof(aThis));', '']
for h in hits:
    T.append('    {   // 0x%x\n        g_bNull = 0; g_nAsked = 0;\n'
             '        void* pB = SynAlc2_%x(aThis);\n'
             '        CHECK(g_nAsked == 0x%x);\n        CHECK(pB == aThis);\n'
             '        CHECK(*(void**)g_blk == aThis);\n        CHECK(*(void**)aThis == (void*)g_blk);\n'
             '        g_bNull = 1;\n        pB = SynAlc2_%x(aThis);\n        CHECK(pB == aThis);\n'
             '        CHECK(*(void**)aThis == nullptr);\n    }' % (h['a'], h['a'], h['k'], h['a']))
T += ['', '    std::printf("SYNDICATE_THUNKS9_OK: {0} variants, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks9_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest9.json', 'w'))
