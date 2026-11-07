#!/usr/bin/env python3
"""Family GI2 - the invariant probe that also advances the stored value.

Same skeleton as family GX up to the probe, then instead of returning the field it adds an immediate to
the field and returns `this`:

    15  rax = rbx                       (the return value is the holder)
    16  add QWORD PTR [rbx+<cur>],<imm>

Transcribed from 0x141722a70 (20 instructions).
"""
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FUNC = os.path.join(REPO, 'tools', 'bulk', 'funcs.json')

BODY = [
    (0, 'push rbx'), (1, 'sub rsp,N'),
    (2, 'mov rax,QWORD PTR [rcx]'), (3, 'mov rbx,rcx'),
    (4, 'test rax,rax'), (5, 'jne N'),
    (6, 'call QWORD PTR [rip@N]'),
    (7, 'mov rax,QWORD PTR [rbx]'), (8, 'test rax,rax'), (9, 'je N'),
    (10, 'mov rax,QWORD PTR [rax]'),
    (11, 'mov rax,QWORD PTR [rax+N]'),
    (12, 'cmp QWORD PTR [rbx+N],rax'), (13, 'jb N'),
    (14, 'call QWORD PTR [rip@N]'),
    (15, 'mov rax,rbx'), (16, 'add QWORD PTR [rbx+N],N'),
    (17, 'add rsp,N'), (18, 'pop rbx'), (19, 'ret'),
]

CC = {'jb': ('>=', 'the current value is at or above the limit'), 'jne': ('==', 'the current value equals the limit'),
      'je': ('!=', 'the current value differs from the limit'), 'ja': ('<=', 'the current value is at or below the limit'),
      'jae': ('<', 'the current value is below the limit'), 'jbe': ('>', 'the current value is above the limit')}


def hexat(t, k=0):
    return int(re.findall(r'0x([0-9a-f]+)', t)[k], 16)


def parse(f):
    t = f['text']
    if len(t) != len(BODY):
        return None, 'length'
    idx = {a: i for i, a in enumerate(f['addr'])}
    for i, pat in BODY:
        if i == 13:
            if not re.match(r'^j\w+ 0x[0-9a-f]+$', t[i]):
                return None, 'insn 13 is %r' % t[i]
            continue
        if re.sub(r'0x[0-9a-f]+', 'N', t[i]) != pat:
            return None, 'insn %d is %r' % (i, t[i])
    for i, want in ((5, 10), (9, 11), (13, 15)):
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t[i])
        if not m or idx.get(int(m.group(1), 16)) != want:
            return None, 'branch %d does not land on %d' % (i, want)
    cc = t[13].split()[0]
    if cc not in CC:
        return None, 'unhandled condition %s' % cc
    h = {'a': f['a'], 'cur': hexat(t[12]), 'lim': hexat(t[11]), 'add': hexat(t[16]),
         'seam': hexat(t[14]), 'cc': cc, 'op': CC[cc][0], 'why': CC[cc][1]}
    if hexat(t[6]) != h['seam']:
        return None, 'the two seam calls differ'
    return h, None


def main():
    funcs = json.load(open(FUNC))
    blob = ''
    for root, _d, files in os.walk(os.path.join(REPO, 'modules')):
        for n in sorted(files):
            if n.endswith(('.cpp', '.h')):
                blob += open(os.path.join(root, n), errors='ignore').read().lower()
    import glob
    for n in glob.glob(os.path.join(REPO, 'tests', '*')):
        blob += open(n, errors='ignore').read().lower()

    hits, rej = [], 0
    for f in funcs:
        if ('0x%x' % f['a']) in blob:
            continue
        h, why = parse(f)
        if h:
            hits.append(h)
        elif why and why != 'length':
            rej += 1
    hits.sort(key=lambda x: x['a'])
    if not hits:
        print('family GI2: no bodies')
        return

    hdr = ['// Generated with tools/bulk/gen_gi2.py - the invariant probe that advances the stored value.',
           '#ifndef TQ_SYNTHUNKS_GI2_H', '#define TQ_SYNTHUNKS_GI2_H', '',
           '#include <cstdint>', '#include <cstddef>', '', 'namespace tq {', '',
           '#define GI2_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))', '']
    seams = sorted({h['seam'] for h in hits})
    for a in seams:
        hdr.append('extern void (*g_fnGI2_%x)(void*);' % a)
    hdr.append('')
    for h in hits:
        hdr.append('inline void* SynProbeGX_%x(void* pThis) {   // 0x%x  (%s: %s)' % (h['a'], h['a'], h['cc'], h['why']))
        hdr.append('    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5')
        hdr.append('        g_fnGI2_%x(pThis);                                       // insn 6' % h['seam'])
        hdr.append('    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)')
        hdr.append('    if (p != nullptr)                                           // insn 8-9')
        hdr.append('        p = GI2_Q(p, 0x0);                                     // insn 10')
        hdr.append('    if (GI2_Q(pThis, 0x%x) %s                              // insn 11-13'
                   % (h['cur'], h['op']))
        hdr.append('        GI2_Q(p, 0x%x))' % h['lim'])
        hdr.append('        g_fnGI2_%x(pThis);                                       // insn 14' % h['seam'])
        hdr.append('    *(uint64_t*)((uint8_t*)pThis + 0x%x) += 0x%x;               // insn 16' % (h['cur'], h['add']))
        hdr.append('    return pThis;                                              // insn 15')
        hdr.append('}')
        hdr.append('')
    hdr += ['}  // namespace tq', '', '#undef GI2_Q', '', '#endif']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_gi2.h'), 'w').write('\n'.join(hdr))

    src = ['// Generated with tools/bulk/gen_gi2.py - the seam pointers.', '#include "synthunks_gi2.h"', '',
           'namespace tq {', '']
    for a in seams:
        src.append('void (*g_fnGI2_%x)(void*) = nullptr;' % a)
    src += ['', '}  // namespace tq', '']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_gi2.cpp'), 'w').write('\n'.join(src))
    json.dump(hits, open(os.path.join(REPO, 'tools/bulk/manifest_gi2.json'), 'w'), indent=1)
    print('family GI2: %d bodies (rejected %d)' % (len(hits), rej))
    print('  cur', sorted({hex(h['cur']) for h in hits}), 'lim', sorted({hex(h['lim']) for h in hits}),
          'add', sorted({hex(h['add']) for h in hits}), 'cc', sorted({h['cc'] for h in hits}))


if __name__ == '__main__':
    main()
