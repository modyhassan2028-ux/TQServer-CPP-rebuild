#!/usr/bin/env python3
"""Family CL - ordered-tree clear().

Transcribed from 0x1417276c0 (31 instructions, verified branch by branch):

    head = this->head                    // 4
    rsi  = head->parent                  // 6   the root
    rdi  = rsi                           // 7
    if (!isNil(rsi)) {                   // 8-9
      do {
        rdx = rdi->right                 // 10
        helper(this, rdx)                // 11-12  (the node's teardown helper)
        rdi = rdi->left                  // 13     (the next node, read BEFORE the delete)
        free(rsi)                        // 14-15
        rsi = rdi                        // 17
      } while (!isNil(rdi));             // 16-18
    }
    h = this->head ; h->parent = h        // 19-21
    this->count = 0                       // 22-23
    h = this->head ; h->left  = h         // 24
    h = this->head ; h->right = h         // 25-27   (and that head is the return value)

The alternation `rdi = rdi->left` before the free at 15 matters: the next node is read out of the
node that is about to be released.
"""
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FUNC = os.path.join(REPO, 'tools', 'bulk', 'funcs.json')
MARK = 'mark'

BODY = [
    (0, 'mov QWORD PTR [rsp+N],rbx'), (1, 'mov QWORD PTR [rsp+N],rsi'),
    (2, 'push rdi'), (3, 'sub rsp,N'),
    (4, 'mov rax,QWORD PTR [rcx+N]'), (5, 'mov rbx,rcx'),
    (6, 'mov rsi,QWORD PTR [rax+N]'), (7, 'mov rdi,rsi'),
    (8, 'cmp BYTE PTR [rsi+N],N'), (9, 'jne N'),
    (10, 'mov rdx,QWORD PTR [rdi+N]'), (11, 'mov rcx,rbx'),
    (12, 'call N'), (13, 'mov rdi,QWORD PTR [rdi]'),
    (14, 'mov rcx,rsi'), (15, 'call N'),
    (16, 'cmp BYTE PTR [rdi+N],N'), (17, 'mov rsi,rdi'),
    (18, 'je N'),
    (19, 'mov rax,QWORD PTR [rbx+N]'), (20, 'mov rsi,QWORD PTR [rsp+N]'),
    (21, 'mov QWORD PTR [rax+N],rax'), (22, 'mov rax,QWORD PTR [rbx+N]'),
    (23, 'mov QWORD PTR [rbx+N],N'), (24, 'mov QWORD PTR [rax],rax'),
    (25, 'mov rax,QWORD PTR [rbx+N]'), (26, 'mov rbx,QWORD PTR [rsp+N]'),
    (27, 'mov QWORD PTR [rax+N],rax'), (28, 'add rsp,N'),
    (29, 'pop rdi'), (30, 'ret'),
]


def norm(t):
    s = t
    s = re.sub(r'\+0x([0-9a-f]+)\]', lambda m: '+N]' if m.group(1) not in ('8', '0x10') else m.group(0), s)
    return s


def hexat(t, k=0):
    v = re.findall(r'0x([0-9a-f]+)', t)
    return int(v[k], 16)


def parse(f):
    t = f['text']
    if len(t) != len(BODY):
        return None, 'length %d' % len(t)
    idx = {a: i for i, a in enumerate(f['addr'])}
    for i, pat in BODY:
        if re.sub(r'0x[0-9a-f]+', 'N', t[i]) != pat:
            return None, 'insn %d is %r' % (i, t[i])
    h = {'head': hexat(t[4]), 'count': hexat(t[23]), 'mark': hexat(t[8]),
         't1': hexat(t[12]), 't2': hexat(t[15])}
    if hexat(t[16]) != h['mark']:
        return None, 'mark differs at 16'
    if hexat(t[21]) != 8 or hexat(t[6]) != 8 or hexat(t[10]) != 0x10 or hexat(t[27]) != 0x10:
        return None, 'link offsets differ'
    for i, want in ((9, 19), (18, 10)):
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t[i])
        if not m or idx.get(int(m.group(1), 16)) != want:
            return None, 'branch %d does not land on %d' % (i, want)
    return h, None


def main():
    funcs = json.load(open(FUNC))
    blob = ''
    for root, _d, files in os.walk(os.path.join(REPO, 'modules')):
        for n in sorted(files):
            if n.endswith(('.cpp', '.h')):
                blob += open(os.path.join(root, n), errors='ignore').read().lower()
    blob += open(os.path.join(REPO, 'tests', 'cqbase_thunks_cl_test.cpp'), errors='ignore').read().lower() \
        if os.path.exists(os.path.join(REPO, 'tests', 'cqbase_thunks_cl_test.cpp')) else ''
    import glob
    for n in glob.glob(os.path.join(REPO, 'tests', '*')):
        blob += open(n, errors='ignore').read().lower()

    hits, rej = [], []
    for f in funcs:
        if ('0x%x' % f['a']) in blob:
            continue
        h, why = parse(f)
        if h:
            h['a'] = f['a']
            hits.append(h)
        elif why and why != 'length' and why.startswith('insn 0'):
            rej.append((f['a'], why))
    hits.sort(key=lambda x: x['a'])
    if not hits:
        print('family CL: no bodies')
        return

    hdr = ['// Generated with tools/bulk/gen_cl.py - ordered-tree clear().',
           '// Every body is the same 31-instruction routine with its own head/count/mark offsets.',
           '#ifndef TQ_SYNTHUNKS_CL_H', '#define TQ_SYNTHUNKS_CL_H', '',
           '#include <cstdint>', '#include <cstddef>', '', 'namespace tq {', '',
           '#define CL_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))',
           '#define CL_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))', '']
    seams = sorted({(h['t1'], 'teardown') for h in hits} | {(h['t2'], 'free') for h in hits})
    for a, kind in seams:
        if kind == 'teardown':
            hdr.append('extern void (*g_fnCL_t_%x)(void*, void*);' % a)
        else:
            hdr.append('extern void (*g_fnCL_d_%x)(void*);' % a)
    hdr.append('')
    for h in hits:
        hdr.append('inline void* SynTreeClear_%x(void* pThis) {   // 0x%x' % (h['a'], h['a']))
        hdr.append('    void* const pHead = CL_Q(pThis, 0x%x);                        // insn 4' % h['head'])
        hdr.append('    void* rsi = CL_Q(pHead, 0x8);                               // insn 6')
        hdr.append('    void* rdi = rsi;                                          // insn 7')
        hdr.append('    if (CL_B(rsi, 0x%x) == 0) {                               // insn 8-9' % h['mark'])
        hdr.append('        do {')
        hdr.append('            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10')
        hdr.append('            g_fnCL_t_%x(pThis, rdx);                            // insn 11-12' % h['t1'])
        hdr.append('            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)')
        hdr.append('            g_fnCL_d_%x(rsi);                                  // insn 14-15' % h['t2'])
        hdr.append('            rsi = rdi;                                        // insn 17')
        hdr.append('        } while (CL_B(rdi, 0x%x) == 0);                          // insn 16-18' % h['mark'])
        hdr.append('    }')
        hdr.append('    void* h = CL_Q(pThis, 0x%x);                                // insn 19' % h['head'])
        hdr.append('    CL_Q(h, 0x8) = h;                                          // insn 21')
        hdr.append('    h = CL_Q(pThis, 0x%x);                                     // insn 22' % h['head'])
        hdr.append('    *(uint64_t*)((uint8_t*)pThis + 0x%x) = 0x0;               // insn 23' % h['count'])
        hdr.append('    CL_Q(h, 0x00) = h;                                         // insn 24')
        hdr.append('    h = CL_Q(pThis, 0x%x);                                     // insn 25' % h['head'])
        hdr.append('    CL_Q(h, 0x10) = h;                                         // insn 27')
        hdr.append('    return h;                                                  // rax')
        hdr.append('}')
        hdr.append('')
    hdr += ['}  // namespace tq', '', '#undef CL_Q', '#undef CL_B', '', '#endif']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_cl.h'), 'w').write('\n'.join(hdr))

    src = ['// Generated with tools/bulk/gen_cl.py - the seam pointers.', '#include "modules/syndicate/src/synthunks_cl.h"', '',
           'namespace tq {', '']
    for a, kind in seams:
        if kind == 'teardown':
            src.append('void (*g_fnCL_t_%x)(void*, void*) = nullptr;' % a)
        else:
            src.append('void (*g_fnCL_d_%x)(void*) = nullptr;' % a)
    src += ['', '}  // namespace tq', '']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_cl.cpp'), 'w').write('\n'.join(src))

    json.dump([{'a': h['a'], 'head': h['head'], 'count': h['count'], 'mark': h['mark'],
                't1': h['t1'], 't2': h['t2']} for h in hits],
              open(os.path.join(REPO, 'tools/bulk/manifest_cl.json'), 'w'), indent=1)
    print('family CL: %d bodies (rejected %d)' % (len(hits), len(rej)))
    print('  heads', sorted({hex(h['head']) for h in hits}))
    print('  marks', sorted({hex(h['mark']) for h in hits}))
    print('  teardown helpers', len({h['t1'] for h in hits}), '| free', len({h['t2'] for h in hits}))


if __name__ == '__main__':
    main()
