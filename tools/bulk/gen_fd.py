#!/usr/bin/env python3
"""Family FD — ordered-tree lookup: lower_bound, then the equality test.

    rax = head->parent                                  // 9   the root
    while (!isNil(rax)) {                               // 11-12, 20-21
        if (rax->key >= key) { cand = rax; rax = rax->left; }   // 13-15, 18-19
        else                 { rax = rax->right; }              // 16-17
    }
    pair = { this->f00, cand }                          // 24-25  (set before the report test)
    if (this->f00 == nullptr) report();                 // 26-30, the 28-29 `cmp rax,rax` is a tautology
    if (cand != head && key >= cand->key)               // 31-35
        give pair[0]  -> out->f00, out->f08 = pair[1]   // 36-37, 43-49
    else
        give { this->f00, head }                        // 38-42
    return out                                          // 50
"""
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
X = r'0x[0-9a-f]+'

# branch slot -> expected index in every body of the family
LINK = {12: 22, 15: 18, 17: 20, 21: 14, 27: 30, 29: 31, 32: 38, 35: 38, 37: 43}


def norm(t):
    return re.sub(X, 'N', t)


def shape(t):
    return ' ; '.join(norm(x) for x in t)


def main():
    funcs = json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))
    blob = ''
    for p in [p for p in (os.path.join(REPO, 'modules/**/*.cpp'), os.path.join(REPO, 'modules/**/*.h'))]:
        import glob
        for q in glob.glob(p, recursive=True):
            blob += open(q, errors='ignore').read().lower()
    rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]

    hits = []
    for f in rem:
        t = f['text']
        if len(t) != 55:
            continue
        if not shape(t).startswith('mov QWORD PTR [rsp+N],rbx ; mov QWORD PTR [rsp+N],rbp ; '
                                   'mov QWORD PTR [rsp+N],rsi ; mov QWORD PTR [rsp+N],rdi'):
            continue
        idx = {a: i for i, a in enumerate(f['addr'])}
        ok = True
        for i, want in LINK.items():
            m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t[i])
            if not m or idx.get(int(m.group(1), 16)) != want:
                ok = False
                break
        if not ok:
            continue
        mark = int(re.findall(r'0x([0-9a-f]+)', t[11])[0], 16)
        if int(re.findall(r'0x([0-9a-f]+)', t[20])[0], 16) != mark:
            continue
        if t[13] != 'mov r9d,DWORD PTR [r8]' or t[14] != 'cmp DWORD PTR [rax+0x18],r9d':
            continue
        hits.append({'a': f['a'], 'mark': mark, 'seam': 0x1418233c0})

    hdr = ['// synthunks_fd_family.h — generated: the ordered-tree lookup family.',
           '// Every body is the transcription below with its own node marker offset; the shape, the key',
           '// offset and the report seam are identical in all of them (verified per body).',
           '#ifndef SYNDICATE_SYNTHUNKS_FD_FAMILY_H', '#define SYNDICATE_SYNTHUNKS_FD_FAMILY_H',
           '#include <cstdint>', '', 'namespace tq {',
           '#define FD_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))',
           '#define FD_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))',
           'extern void (*g_fnFD_1418233c0)(void*);', '']

    src = ['// synthunks_fd_family.cpp — the report seam of the lookup family.',
           '#include "synthunks_fd_family.h"', '', 'namespace tq {', 
           'void (*g_fnFD_1418233c0)(void*) = nullptr;', '', '}  // namespace tq', '']

    for h in hits:
        M = '0x%x' % h['mark']
        hdr.append('''inline void* SynFind_%(a)x(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x%(a)x
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, %(M)s) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, %(M)s) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}''' % {'a': h['a'], 'M': M})
        hdr.append('')

    hdr += ['#undef FD_Q', '#undef FD_B', '}  // namespace tq', '', '#endif']
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_fd_family.h'), 'w').write('\n'.join(hdr))
    open(os.path.join(REPO, 'modules/syndicate/src/synthunks_fd_family.cpp'), 'w').write('\n'.join(src))
    json.dump(hits, open(os.path.join(REPO, 'tools/bulk/manifest_fd.json'), 'w'), indent=1)
    print('family FD: %d bodies' % len(hits))
    print('  marks', sorted({hex(h['mark']) for h in hits}))


if __name__ == '__main__':
    main()
