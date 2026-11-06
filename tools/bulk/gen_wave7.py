#!/usr/bin/env python3
"""Seventh wave: the small call-shaped bodies (family M).

  M1  ret                                  -> an empty function
  M2  sub rsp,N ; call T ; add rsp,N ; ret -> return T()
  M3  ... movsxd rdx,edx ...               -> return T(a1, (int64_t)(int32_t)a2)
  M4  ... mov rcx,[rcx+off] ...            -> return T(this->member)
  M5  ... test rcx,rcx ; je ep ; call T    -> if (member) T(member)
  M6  M5 then mov al,k                     -> if (member) T(member); return k
Every je is required to land on the epilogue before the body is accepted.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_m'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
print('remaining', len(rem))

CALL = r'(?:(0x[0-9a-f]+)|QWORD PTR \[rip@(0x[0-9a-f]+)\])'
def tgt(m, base):
    return {'direct': int(m.group(base), 16)} if m.group(base) else {'slot': int(m.group(base + 1), 16)}

P = {
 'm2': re.compile(r'sub rsp,0x([0-9a-f]+) ; call ' + CALL + r' ; add rsp,0x\1 ; ret'),
 'm3': re.compile(r'sub rsp,0x([0-9a-f]+) ; movsxd rdx,edx ; call ' + CALL + r' ; add rsp,0x\1 ; ret'),
 'm4': re.compile(r'sub rsp,0x([0-9a-f]+) ; mov rcx,QWORD PTR \[rcx\+(0x[0-9a-f]+)\] ; call ' + CALL +
                  r' ; add rsp,0x\1 ; ret'),
 'm5': re.compile(r'sub rsp,0x([0-9a-f]+) ; mov rcx,QWORD PTR \[rcx\+(0x[0-9a-f]+)\] ; test rcx,rcx ; '
                  r'je (0x[0-9a-f]+) ; call ' + CALL + r' ; add rsp,0x\1 ; ret'),
 'm6': re.compile(r'sub rsp,0x([0-9a-f]+) ; mov rcx,QWORD PTR \[rcx\+(0x[0-9a-f]+)\] ; test rcx,rcx ; '
                  r'je (0x[0-9a-f]+) ; call ' + CALL + r' ; mov al,(0x[0-9a-f]+) ; add rsp,0x\1 ; ret'),
}

fam = {k: [] for k in ('m1', 'm2', 'm3', 'm4', 'm5', 'm6')}
for f in rem:
    t = ['ret' if x in ('repz ret','rep ret') else x for x in f['text']]
    if t == ['ret']:
        fam['m1'].append({'a': f['a']}); continue
    b = ' ; '.join(t)
    for k, base_new in (('m2', 2), ('m3', 2)):
        m = P[k].fullmatch(b)
        if m:
            rec = {'a': f['a']}; rec.update(tgt(m, base_new)); fam[k].append(rec); break
    else:
        m = P['m4'].fullmatch(b)
        if m:
            rec = {'a': f['a'], 'o': int(m.group(2), 16)}; rec.update(tgt(m, 3)); fam['m4'].append(rec); continue
        m = P['m5'].fullmatch(b)
        if m:
            rec = {'a': f['a'], 'o': int(m.group(2), 16), 'j': int(m.group(3), 16)}; rec.update(tgt(m, 4))
            fam['m5'].append(rec); continue
        m = P['m6'].fullmatch(b)
        if m:
            rec = {'a': f['a'], 'o': int(m.group(2), 16), 'j': int(m.group(3), 16), 'r': int(m.group(5), 16)}
            rec.update(tgt(m, 4)); fam['m6'].append(rec)

# verify every je lands on the epilogue (the instruction after the call)
for k in ('m5', 'm6'):
    keep = []
    for rec in fam[k]:
        f = next(x for x in rem if x['a'] == rec['a'])
        idx = {a: i for i, a in enumerate(f['addr'])}
        if idx.get(rec['j']) == len(f['text']) - 3:      # add rsp / pop? -> the epilogue start
            keep.append(rec)
    fam[k] = keep
print({k: len(v) for k, v in fam.items()}, 'total', sum(len(v) for v in fam.values()))

def sn(rec):
    return 'g_fnM' + ('D%d' % rec['direct'] if 'direct' in rec else 'S%x' % rec['slot'])

hdr = ['// synthunks_m.h — RAW Syndicate.dll v6159 · family M, the small call-shaped bodies.',
       '#ifndef TQ_SYN_THUNKS_M_H', '#define TQ_SYN_THUNKS_M_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
allrec = [r for v in fam.values() for r in v if 'direct' in r or 'slot' in r]
seams = sorted({sn(r) for r in allrec})
hdr += ['extern void* (*%s)(void*, void*, void*, void*);' % s for s in seams] + ['']
for r in fam['m1']:
    hdr.append('inline void SynM1_%x(void*, void*, void*, void*) {   // 0x%x  (body is only ret)\n}'
               % (r['a'], r['a']))
for r in fam['m2']:
    hdr.append('inline void* SynM2_%x(void* a1, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    return %s(nullptr, nullptr, nullptr, nullptr);\n}' % (r['a'], r['a'], sn(r)))
for r in fam['m3']:
    hdr.append('inline void* SynM3_%x(void* a1, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    return %s(a1, (void*)(int64_t)(int32_t)(intptr_t)a2, nullptr, nullptr);\n}'
               % (r['a'], r['a'], sn(r)))
for r in fam['m4']:
    hdr.append('inline void* SynM4_%x(void* pThis, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    return %s(*(void**)((uint8_t*)pThis + 0x%x), nullptr, nullptr, nullptr);\n}'
               % (r['a'], r['a'], sn(r), r['o']))
for r in fam['m5']:
    hdr.append('inline void* SynM5_%x(void* pThis, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    void* pM = *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    if (pM) %s(pM, nullptr, nullptr, nullptr);\n    return nullptr;\n}'
               % (r['a'], r['a'], r['o'], sn(r)))
for r in fam['m6']:
    hdr.append('inline void* SynM6_%x(void* pThis, void* a2, void* a3, void* a4) {   // 0x%x\n'
               '    void* pM = *(void**)((uint8_t*)pThis + 0x%x);\n'
               '    if (pM) %s(pM, nullptr, nullptr, nullptr);\n    return (void*)(uintptr_t)0x%x;\n}'
               % (r['a'], r['a'], r['o'], sn(r), r['r']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_m.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_m.cpp — the seams of family M.',
      '#include "modules/syndicate/src/synthunks_m.h"', '', 'namespace tq {', '']
sc += ['void* (*%s)(void*, void*, void*, void*) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_m.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family M — one check per body.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_m.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_v1 = 0, g_v2 = 0; static int g_nCalls = 0;', '']
T += ['static void* Hook%s(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }' % s for s in seams]
T += ['', 'static unsigned char g_ab[0x3000];', '', 'int main() {']
T += ['    %s = &Hook%s;' % (s, s) for s in seams]
T += ['    int arg2 = -5;']
for r in fam['m2']:
    T.append('    {   // 0x%x\n        g_nCalls = 0;\n        void* pB = SynM2_%x(g_ab, nullptr, nullptr, nullptr);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == 0);\n        CHECK(pB == (void*)0x99);\n    }'
             % (r['a'], r['a']))
for r in fam['m3']:
    T.append('    {   // 0x%x\n        g_nCalls = 0;\n        void* pB = SynM3_%x(g_ab, &arg2, nullptr, nullptr);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == (uintptr_t)g_ab);\n'
             '        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);\n        CHECK(pB == (void*)0x99);\n    }' % (r['a'], r['a']))
for r in fam['m4']:
    T.append('    {   // 0x%x\n        *(uint64_t*)(g_ab + 0x%x) = 0xABCD;\n        g_nCalls = 0;\n'
             '        void* pB = SynM4_%x(g_ab, nullptr, nullptr, nullptr);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == 0xABCD);\n        CHECK(pB == (void*)0x99);\n    }'
             % (r['a'], r['o'], r['a']))
for r in fam['m5']:
    T.append('    {   // 0x%x\n        *(uint64_t*)(g_ab + 0x%x) = 0;\n        g_nCalls = 0;\n'
             '        void* pB = SynM5_%x(g_ab, nullptr, nullptr, nullptr);\n        CHECK(g_nCalls == 0);\n'
             '        *(uint64_t*)(g_ab + 0x%x) = 0xBEEF;\n'
             '        pB = SynM5_%x(g_ab, nullptr, nullptr, nullptr);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v1 == 0xBEEF);\n        CHECK(pB == nullptr);\n    }'
             % (r['a'], r['o'], r['a'], r['o'], r['a']))
for r in fam['m6']:
    T.append('    {   // 0x%x\n        *(uint64_t*)(g_ab + 0x%x) = 0;\n        g_nCalls = 0;\n'
             '        void* pB = SynM6_%x(g_ab, nullptr, nullptr, nullptr);\n        CHECK(g_nCalls == 0);\n'
             '        CHECK(pB == (void*)(uintptr_t)0x%x);\n    }' % (r['a'], r['o'], r['a'], r['r']))
T += ['', '    std::printf("SYNDICATE_THUNKS7_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(sum(len(v) for v in fam.values()))]
open('tests/cqbase_thunks7_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(fam, open('tools/bulk/manifest7.json', 'w'))
