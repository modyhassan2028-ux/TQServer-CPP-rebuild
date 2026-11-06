#!/usr/bin/env python3
"""Family V — load a member of the second argument and hand it to a target, returning its answer.

Whole-body match:
    push rbp ; sub rsp,<frame> ; mov rbp,rdx ; mov rcx,QWORD PTR [rbp+<off>]
    call <direct|slot> ; add rsp,<frame> ; pop rbp ; ret
Nothing here branches, so the match is the whole proof: the member offset, the frame size and the
target are taken from the instructions, not chosen.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
blob = ''
for root, d, fs in os.walk('modules'):
    for n in fs:
        if n.endswith(('.cpp', '.h')) and not n.startswith('synthunks_v'):
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

P = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; mov rcx,QWORD PTR \[rbp\+(0x[0-9a-f]+)\] ; '
               r'call (?:(0x[0-9a-f]+)|QWORD PTR \[rip@(0x[0-9a-f]+)\]) ; add rsp,0x\1 ; pop rbp ; ret')
hits = []
for f in rem:
    m = P.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    hits.append({'a': f['a'], 'frame': int(m.group(1), 16), 'o': int(m.group(2), 16),
                 'direct': int(m.group(3), 16) if m.group(3) else None,
                 'slot': int(m.group(4), 16) if m.group(4) else None})
print('family V', len(hits))

def sn(h):
    return 'g_fnVD%x' % h['direct'] if h['direct'] else 'g_fnVS%x' % h['slot']

hdr = ['// synthunks_v.h — RAW Syndicate.dll v6159 · %d bodies that forward a member of their second' % len(hits),
       '// argument to a target and answer whatever it returns. The offset, the frame size and the target',
       '// come straight from the instructions; there is nothing to branch on.',
       '#ifndef TQ_SYN_THUNKS_V_H', '#define TQ_SYN_THUNKS_V_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
seams = sorted({sn(h) for h in hits})
hdr += ['extern void* (*%s)(void* pArg);' % s for s in seams] + ['']
for h in hits:
    hdr.append('inline void* SynFwd_%x(void* pUnused, void* pArg2) {   // 0x%x  frame 0x%x\n'
               '    return %s(*(void**)((uint8_t*)pArg2 + 0x%x));\n}'
               % (h['a'], h['a'], h['frame'], sn(h), h['o']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_v.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_v.cpp — the seams of family V.',
      '#include "modules/syndicate/src/synthunks_v.h"', '', 'namespace tq {', '']
sc += ['void* (*%s)(void*) = nullptr;' % s for s in seams]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_v.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family V — one check per body.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '',
     '#include "modules/syndicate/src/synthunks_v.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_v = 0; static int g_nCalls = 0;',
     'static void* Hook(void* p) { g_v = (uintptr_t)p; ++g_nCalls; return (void*)0x4321; }', '',
     'int main() {']
T += ['    %s = &Hook;' % s for s in seams]
mx = max((h['o'] for h in hits), default=0)
T += ['    static unsigned char aObj[0x%x];' % (mx + 0x40), '']
for h in hits:
    T.append('    {   // 0x%x\n        *(uint64_t*)(aObj + 0x%x) = 0x%x;\n        g_nCalls = 0; g_v = 0;\n'
             '        void* pB = SynFwd_%x(nullptr, aObj);\n'
             '        CHECK(g_nCalls == 1);\n        CHECK(g_v == 0x%x);\n        CHECK(pB == (void*)0x4321);\n    }'
             % (h['a'], h['o'], 0x9000 + h['o'], h['a'], 0x9000 + h['o']))
T += ['', '    std::printf("SYNDICATE_THUNKS_V_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_v_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_v.json', 'w'))
