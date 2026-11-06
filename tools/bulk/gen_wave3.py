#!/usr/bin/env python3
"""Third wave: families E (member+offset), F (call then answer the receiver) and G (call with nulls).

A call target is either a direct address or an IAT slot (`call QWORD PTR [rip@0x...]`); the
slot address is what the disassembler resolved, so an indirect call keeps being indirect here
instead of being guessed into a name.
"""
import json, re, os

def load():
    funcs = json.load(open('tools/bulk/funcs.json'))
    for f in funcs:
        f['ins'] = [' '.join(t.split()) for t in f['ins']]
    blob = ''
    for root, d, fs in os.walk('modules'):
        for n in fs:
            if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks'):
                blob += open(os.path.join(root, n), errors='ignore').read().lower()
    return [f for f in funcs if ('0x%x' % f['a']) not in blob]

CALL = r'(?:(0x[0-9a-f]+)|QWORD PTR \[rip@(0x[0-9a-f]+)\])'
def tgt(m, base):
    return {'direct': int(m.group(base), 16)} if m.group(base) else {'slot': int(m.group(base + 1), 16)}

E = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; mov rcx,QWORD PTR \[rbp\+(0x[0-9a-f]+)\] ; '
               r'add rcx,0x([0-9a-f]+) ; call ' + CALL + r' ; add rsp,0x\1 ; pop rbp ; ret')
F = re.compile(r'push rbx ; sub rsp,0x([0-9a-f]+) ; mov rbx,rcx ; call ' + CALL +
               r' ; mov rax,rbx ; add rsp,0x\1 ; pop rbx ; ret')
G = re.compile(r'mov QWORD PTR \[rsp\+0x10\],rdx ; push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; '
               r'xor edx,edx ; xor ecx,ecx ; call ' + CALL + r' ; add rsp,0x\1 ; pop rbp ; ret')

rem = load()
fam = {'e': [], 'f': [], 'g': []}
for f in rem:
    b = ' ; '.join(f['ins'])
    m = E.fullmatch(b)
    if m:
        rec = {'a': f['a'], 'o': int(m.group(2), 16), 'k': int(m.group(3), 16)}
        rec.update(tgt(m, 4)); fam['e'].append(rec); continue
    m = F.fullmatch(b)
    if m:
        rec = {'a': f['a']}; rec.update(tgt(m, 2)); fam['f'].append(rec); continue
    m = G.fullmatch(b)
    if m:
        rec = {'a': f['a']}; rec.update(tgt(m, 2)); fam['g'].append(rec)
print({k: len(v) for k, v in fam.items()})

def key(rec):
    return ('d%d' % rec['direct']) if 'direct' in rec else ('s%x' % rec['slot'])
def seam(rec):
    return ('g_fnThk' + ('D%d' % rec['direct'] if 'direct' in rec else 'S%x' % rec['slot']))

# ---- header
hdr = ['// synthunks_e.h — RAW Syndicate.dll v6159 · families E, F and G, transcribed whole-body.',
       '//   E: call a target with the pointer at [arg2+off] advanced by k',
       '//   F: call a target with the receiver, then answer the receiver',
       '//   G: call a target with two nulls',
       '// A "S..." seam is an IAT slot (indirect call), a "D..." seam a direct target.',
       '#ifndef TQ_SYN_THUNKS_E_H', '#define TQ_SYN_THUNKS_E_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = []
for k in sorted({key(r) for r in fam['e']}):
    seams.append('extern void* (*%s_E)(void* pArg);' % seam(next(r for r in fam['e'] if key(r) == k)))
for k in sorted({key(r) for r in fam['f']}):
    seams.append('extern void* (*%s_F)(void* pThis);' % seam(next(r for r in fam['f'] if key(r) == k)))
for k in sorted({key(r) for r in fam['g']}):
    seams.append('extern void* (*%s_G)(void*, void*);' % seam(next(r for r in fam['g'] if key(r) == k)))
hdr += seams + ['']
for rec in fam['e']:
    hdr.append('inline void* SynThkE_%x(void* pUnused, void* pObj) {   // 0x%x\n'
               '    return %s_E((void*)((uint8_t*)*(void**)((uint8_t*)pObj + 0x%x) + 0x%x));\n}'
               % (rec['a'], rec['a'], seam(rec), rec['o'], rec['k']))
for rec in fam['f']:
    hdr.append('inline void* SynThkF_%x(void* pThis) {   // 0x%x\n    %s_F(pThis);\n    return pThis;\n}'
               % (rec['a'], rec['a'], seam(rec)))
for rec in fam['g']:
    hdr.append('inline void* SynThkG_%x(void* pUnused, void* pObj) {   // 0x%x\n'
               '    (void)pObj;\n    return %s_G(nullptr, nullptr);\n}' % (rec['a'], rec['a'], seam(rec)))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_e.h', 'w').write('\n'.join(hdr) + '\n')

# ---- seams
sc = ['// synthunks_e.cpp — the seams of families E, F and G. Each one names the target (or the IAT',
      '// slot) of the original call instruction.',
      '#include "modules/syndicate/src/synthunks_e.h"', '', 'namespace tq {', '']
sc += [s.replace('extern ', '').replace(';', ' = nullptr;') for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_e.cpp', 'w').write('\n'.join(sc) + '\n')

# ---- test
hooks, wires, checks = [], [], []
for kind in ('e', 'f', 'g'):
    for k in sorted({key(r) for r in fam[kind]}):
        rec = next(r for r in fam[kind] if key(r) == k)
        nm = '%s_%s' % (seam(rec), kind.upper())
        if kind == 'g':
            hooks.append('static void* Hook%s(void* a, void* b) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0xBAD; }' % nm)
        else:
            hooks.append('static void* Hook%s(void* a) { g_v1 = (uintptr_t)a; ++g_nCalls; return (void*)0xBAD; }' % nm)
        wires.append('    %s = &Hook%s;' % (nm, nm))

for rec in fam['e']:
    checks.append('    {{   // 0x{a:x}\n        *(uint64_t*)(g_ab + 0x{o:x}) = 0x7777{a4:04x}ULL;\n        g_nCalls = 0;\n        void* pBack = SynThkE_{a:x}(g_ab, g_ab);\n        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == (uintptr_t)(0x7777{a4:04x}ULL + 0x{k:x}));\n        CHECK(pBack == (void*)0xBAD);\n    }}'.format(a=rec['a'], o=rec['o'], a4=rec['a'] % 0x10000, k=rec['k']))
for rec in fam['f']:
    checks.append('    {   // 0x%x\n        g_nCalls = 0;\n        void* pBack = SynThkF_%x(g_ab);\n'
                  '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == (uintptr_t)g_ab);\n'
                  '        CHECK(pBack == g_ab);\n    }' % (rec['a'], rec['a']))
for rec in fam['g']:
    checks.append('    {   // 0x%x\n        g_nCalls = 0; g_v1 = 1; g_v2 = 2;\n'
                  '        void* pBack = SynThkG_%x(g_ab, g_ab);\n'
                  '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == 0);\n        CHECK(g_v2 == 0);\n'
                  '        CHECK(pBack == (void*)0xBAD);\n    }' % (rec['a'], rec['a']))

T = ['// Generated with families E, F and G — one check per wrapper.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_e.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_v1 = 0, g_v2 = 0; static int g_nCalls = 0;', '']
T += hooks + ['', 'static unsigned char g_ab[0x2000];', '', 'int main() {'] + wires
T += ['    void* o = g_ab;  (void)o;', ''] + checks + ['']
T.append('    std::printf("SYNDICATE_THUNKS3_OK: {0} wrappers, %d checks\\n", g_nChecks);\n    return 0;\n}}'
         .format(len(fam['e']) + len(fam['f']) + len(fam['g'])))
open('tests/cqbase_thunks3_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(fam, open('tools/bulk/manifest3.json', 'w'))
