#!/usr/bin/env python3
"""Family NP - "forward to the member if it exists".

    sub rsp,<f> ; mov rcx,[rcx+<off>] ; test rcx,rcx ; je <end> ; call <target> ; add rsp,<f> ; ret

The body loads a member pointer and, when it is not null, tail-calls a helper with it as the only argument.
The skip path leaves rax untouched, so the function is declared void: nothing is returned either way.
"""
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

BODY = ['sub rsp,N', 'mov rcx,QWORD PTR [rcx+N]', 'test rcx,rcx', 'je N', 'call N', 'add rsp,N', 'ret']


def hexat(t, k=0):
    return int(re.findall(r'0x([0-9a-f]+)', t)[k], 16)


def parse(f):
    t = f['text']
    if len(t) != len(BODY):
        return None, 'length'
    for i, pat in enumerate(BODY):
        if re.sub(r'0x[0-9a-f]+', 'N', t[i]) != pat:
            return None, 'insn %d is %r' % (i, t[i])
    idx = {a: i for i, a in enumerate(f['addr'])}
    m = re.match(r'^je (0x[0-9a-f]+)$', t[3])
    if not m or idx.get(int(m.group(1), 16)) != 5:
        return None, 'je does not land on the epilogue'
    if hexat(t[0]) != hexat(t[5]):
        return None, 'frame differs'
    return {'a': f['a'], 'frame': hexat(t[0]), 'off': hexat(t[1]), 'target': hexat(t[4])}, None


def main():
    funcs = json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))
    blob = ''
    for p in ('modules',):
        for root, _d, files in os.walk(os.path.join(REPO, p)):
            for n in files:
                if n.endswith(('.cpp', '.h')) and 'synthunks_np' not in n:
                    blob += open(os.path.join(root, n), errors='ignore').read().lower()
    hits, rej = [], 0
    for f in funcs:
        if ('0x%x' % f['a']) in blob:
            continue
        h, why = parse(f)
        if h is None:
            if why != 'length' and why != 'insn 0 is %r' % f['text'][0] if f['text'] else True:
                pass
            continue
        hits.append(h)
    hdr = ['// synthunks_np.h - RAW Syndicate.dll v6159 - "forward to the member if it exists".',
           '// Generated with tools/bulk/gen_np.py; every body was matched against the raw instruction list',
           '// before it was emitted, and the je must land on the epilogue.', '',
           '#ifndef SYNTHUNKS_NP_H', '#define SYNTHUNKS_NP_H', '',
           '#include <cstdint>', '#include <cstddef>', '',
           'namespace tq {', '']
    src = ['// synthunks_np.cpp - seam definitions for family NP.', '#include "modules/syndicate/src/synthunks_np.h"', '', 'namespace tq {', '']
    tests = ['// Generated with tools/bulk/gen_np.py - the forward-if-present battery.',
             '#include "modules/syndicate/src/synthunks_np.h"',
             '#include <cstdio>', '#include <cstdlib>', '#include <cstring>', '', 'using namespace tq;', '',
             'static int g_checks, g_fails;',
             '#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); } } while (0)',
             '', 'static void* g_pArg;', 'static int g_nCalls;', '',
             'static void Hook(void* p) { g_pArg = p; ++g_nCalls; }', '']
    seen = set()
    for h in sorted(hits, key=lambda x: x['a']):
        name = 'g_fnNP_%x' % h['target']
        if name not in seen:
            seen.add(name)
            hdr.append('extern void (*%s)(void*);   // 0x%x' % (name, h['target']))
            src.append('void (*%s)(void*) = nullptr;' % name)
        hdr.append('')
        hdr.append('inline void SynForward_%x(void* pThis) {   // 0x%x' % (h['a'], h['a']))
        hdr.append('    void* const pInner = *(void**)((uint8_t*)pThis + 0x%x);   // insn 1' % h['off'])
        hdr.append('    if (pInner != nullptr)                                  // insn 2-3')
        hdr.append('        %s(pInner);                                        // insn 4 (rcx = the member)' % name)
        hdr.append('}')
        tests.append('static void Run_%x(void) {   // forward at +0x%x' % (h['a'], h['off']))
        tests.append('    uint8_t aObj[0x%x];' % (max(0x600, h['off'] + 16)))
        tests.append('    std::memset(aObj, 0, sizeof(aObj));')
        tests.append('    %s = Hook;' % name)
        tests.append('    g_nCalls = 0; g_pArg = nullptr;')
        tests.append('    SynForward_%x(aObj);                        // the member is null: no call' % h['a'])
        tests.append('    CHECK(g_nCalls == 0);')
        tests.append('    *(void**)(aObj + 0x%x) = (void*)0xA5A5;' % h['off'])
        tests.append('    SynForward_%x(aObj);' % h['a'])
        tests.append('    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);')
        tests.append('}')
        tests.append('')
    hdr += ['}  // namespace tq', '', '#endif']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_np.h'), 'w').write('\n'.join(hdr) + '\n')
    src += ['', '}  // namespace tq', '']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_np.cpp'), 'w').write('\n'.join(src) + '\n')
    tests.append('int main() {')
    for h in sorted(hits, key=lambda x: x['a']):
        tests.append('    Run_%x();' % h['a'])
    tests.append('    std::printf("NP_OK: %d bodies, %%d checks\\n", g_checks);' % len(hits))
    tests.append('    return g_fails ? 1 : 0;')
    tests.append('}')
    open(os.path.join(REPO, 'tests/cqbase_thunks_np_test.cpp'), 'w').write('\n'.join(tests) + '\n')
    json.dump(hits, open(os.path.join(REPO, 'tools/bulk/manifest_np.json'), 'w'), indent=1)
    print('family NP: %d bodies' % len(hits))
    print('  offsets', sorted({hex(h['off']) for h in hits}))
    print('  targets', len({h['target'] for h in hits}))


if __name__ == '__main__':
    main()
