#!/usr/bin/env python3
"""Family GR — forward the tail of a record to a helper.

    push rbp ; sub rsp,<f> ; mov rbp,rdx ; lea rcx,[rbp+<a>] ; add rcx,<b> ; call <t> ; add rsp,<f> ; pop rbp ; ret

The displacement is split across the `lea` and the `add`; the effective argument is arg2 + (a + b). rbp is
only used to hold arg2, so it emits nothing. The caller's return value is the helper's.
"""
import json, re, os, glob

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_gr'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

P = re.compile(r'push rbp ; sub rsp,0x([0-9a-f]+) ; mov rbp,rdx ; lea rcx,\[rbp\+0x([0-9a-f]+)\] ; '
               r'add rcx,0x([0-9a-f]+) ; call 0x([0-9a-f]+) ; add rsp,0x\1 ; pop rbp ; ret')
hits = []
for f in rem:
    m = P.fullmatch(' ; '.join(f['text']))
    if not m:
        continue
    hits.append({'a': f['a'], 'off': int(m.group(2), 16) + int(m.group(3), 16),
                 'part1': int(m.group(2), 16), 'part2': int(m.group(3), 16),
                 't': int(m.group(4), 16)})
print('family GR', len(hits))

hdr = ['// synthunks_gr.h — RAW Syndicate.dll v6159 · %d tail-forwarders (family GR).' % len(hits),
       '// The displacement the original splits between `lea` and `add` is summed here; rbp only carries arg2.',
       '#ifndef TQ_SYN_THUNKS_GR_H', '#define TQ_SYN_THUNKS_GR_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
tg = sorted({h['t'] for h in hits})
hdr += ['extern void* (*g_fnGR_%x)(void* pArg);' % t for t in tg] + ['']
for h in hits:
    hdr.append('inline void* SynFwdTail_%x(void* pThis, void* pRec) {   // 0x%x  +0x%x (lea 0x%x then add 0x%x)\n'
               '    (void)pThis;\n'
               '    return g_fnGR_%x((uint8_t*)pRec + 0x%x);   // insn 3-5\n}'
               % (h['a'], h['a'], h['off'], h['part1'], h['part2'], h['t'], h['off']))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_gr.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_gr.cpp — the seams of family GR.',
      '#include "modules/syndicate/src/synthunks_gr.h"', '', 'namespace tq {', '']
sc += ['void* (*g_fnGR_%x)(void*) = nullptr;' % t for t in tg]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_gr.cpp', 'w').write('\n'.join(sc) + '\n')

T = ['// Generated with family GR — the forwarded pointer is arg2 plus the summed displacement.',
     '#include <cstdio>', '#include <cstdlib>', '#include <cstdint>', '#include <cstring>', '',
     '#include "modules/syndicate/src/synthunks_gr.h"', '', 'using namespace tq;', '',
     'static int g_nChecks = 0;',
     '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)',
     'static uintptr_t g_pSeen = 0; static int g_nCalls = 0;',
     'static void* Hook(void* p) { ++g_nCalls; g_pSeen = (uintptr_t)p; return (void*)0xA55A; }', '',
     'static unsigned char aRec[0x400];', '', 'int main() {']
T += ['    g_fnGR_%x = &Hook;' % t for t in tg]
T += ['']
for h in hits:
    T.append('    {   // 0x%x\n'
             '        g_nCalls = 0;\n'
             '        void* pR = SynFwdTail_%x(nullptr, aRec);\n'
             '        CHECK(g_nCalls == 1);\n'
             '        CHECK(g_pSeen == (uintptr_t)aRec + 0x%x);\n'
             '        CHECK(pR == (void*)0xA55A);\n    }'
             % (h['a'], h['a'], h['off']))
T += ['', '    std::printf("SYNDICATE_THUNKS_GR_OK: {0} bodies, %d checks\\n", g_nChecks);\n    return 0;\n}}'
      .format(len(hits))]
open('tests/cqbase_thunks_gr_test.cpp', 'w').write('\n'.join(T) + '\n')
json.dump(hits, open('tools/bulk/manifest_gr.json', 'w'))
