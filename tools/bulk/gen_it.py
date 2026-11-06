#!/usr/bin/env python3
"""Family IT — the ordered-tree iterator advance.

    if (this->f00 == 0) report();                 // the container pointer is never null in practice
    pNode = this->f08;
    if (pNode->mark != 0) { report(pNode); return; }          // the sentinel: advance from end
    pRight = pNode->f10;
    if (pRight->mark == 0) {                                  // descend the left spine of the right child
        pChild = pRight->f00;
        while (pChild->mark == 0) { pRight = pChild; pChild = pChild->f00; }
        this->f08 = pRight;
        return;
    }
    pUp = pNode->f08;                                          // climb while this node is a right child
    while (pUp->mark == 0 && this->f08 == pUp->f10) {
        this->f08 = pUp;
        pUp = pUp->f08;
    }
    this->f08 = pUp;

`mark` sits at a per-instance offset (+0x29 here, +0x1d in the sibling family) and is always compared
against zero. Every branch target is asserted against the instruction index the disassembly jumps to,
so the port cannot drift from the original control flow.
"""
import json, re, os

funcs = json.load(open('tools/bulk/funcs.json'))
low = ''
for p in __import__('glob').glob('modules/**/*.cpp', recursive=True) + __import__('glob').glob('modules/**/*.h', recursive=True):
    if os.path.basename(p).startswith('synthunks_it'):
        continue
    low += open(p, errors='ignore').read().lower()
rem = [f for f in funcs if ('0x%x' % f['a']) not in low]

TEMPLATE = [
 'push rbx', 'sub rsp,N', 'cmp QWORD PTR [rcx],N', 'mov rbx,rcx', 'jne N',
 'call QWORD PTR [rip@N]', 'mov rcx,QWORD PTR [rbx+N]', 'cmp BYTE PTR [rcx+N],N', 'je N',
 'add rsp,N', 'pop rbx', 'rex.W jmp QWORD PTR [rip@N]', 'mov rax,QWORD PTR [rcx+N]',
 'cmp BYTE PTR [rax+N],N', 'jne N', 'mov rcx,QWORD PTR [rax]', 'cmp BYTE PTR [rcx+N],N', 'jne N',
 'xchg ax,ax', 'mov rax,rcx', 'mov rcx,QWORD PTR [rcx]', 'cmp BYTE PTR [rcx+N],N', 'je N',
 'mov QWORD PTR [rbx+N],rax', 'add rsp,N', 'pop rbx', 'ret', 'mov rcx,QWORD PTR [rcx+N]',
 'cmp BYTE PTR [rcx+N],N', 'jne N', 'mov rax,QWORD PTR [rcx+N]', 'cmp QWORD PTR [rbx+N],rax',
 'jne N', 'mov QWORD PTR [rbx+N],rcx', 'mov rcx,QWORD PTR [rcx+N]', 'cmp BYTE PTR [rcx+N],N', 'je N',
 'mov QWORD PTR [rbx+N],rcx', 'add rsp,N', 'pop rbx', 'ret']


def shape(t):
    return re.sub(r'0x[0-9a-f]+', 'N', t)


hits, rej = [], 0
for f in rem:
    if len(f['text']) != len(TEMPLATE):
        continue
    if [shape(t) for t in f['text']] != TEMPLATE:
        continue
    idx = {a: i for i, a in enumerate(f['addr'])}
    t, ad = f['text'], f['addr']

    def num(i, which=0):
        return int(re.findall(r'0x([0-9a-f]+)', t[i])[which], 16)

    def tgt(i):
        return idx.get(num(i))

    bad = []
    if tgt(4) != 6: bad.append('jne->6')
    if tgt(8) != 12: bad.append('je->12')
    if tgt(14) != 27: bad.append('jne->27')
    if tgt(17) != 23: bad.append('jne->23')
    if tgt(22) != 19: bad.append('je->19')
    if tgt(29) != 37: bad.append('jne->37')
    if tgt(32) != 37: bad.append('jne->37b')
    if tgt(36) != 30: bad.append('je->30')
    if num(2) != 0: bad.append('cmp!=0')
    for i in (7, 13, 16, 21, 28, 35):                 # every marker compare tests zero
        if num(i, 1) != 0: bad.append('mark!=0@%d' % i)
    marks = {num(i) for i in (7, 13, 16, 21, 28, 35)}
    rights = {num(12), num(30)}
    selfs = {num(i) for i in (6, 23, 27, 31, 33, 37)}
    if len(marks) != 1 or len(rights) != 1 or len(selfs) != 1:
        bad.append('offset disagreement')
    if bad:
        rej += 1; print('  rejected', hex(f['a']), bad); continue
    hits.append({'a': f['a'], 'mark': marks.pop(), 'right': rights.pop(), 'self': selfs.pop(),
                 'slot': num(5)})

print('family IT', len(hits), 'rejected', rej)

hdr = ['// synthunks_it.h — RAW Syndicate.dll v6159 · %d ordered-tree iterator advances (family IT).' % len(hits),
       '// Marker byte at a per-instance offset, always compared against zero; the climb and the left-spine',
       '// descent keep the exact branch order of the original.',
       '#ifndef TQ_SYN_THUNKS_IT_H', '#define TQ_SYN_THUNKS_IT_H', '', '#include <cstdint>', '',
       'namespace tq {', '']
slots = sorted({h['slot'] for h in hits})
hdr += ['extern int (*g_fnIT_%x)(void* pArg);' % s for s in slots] + ['']
for h in hits:
    m, r, s = h['mark'], h['right'], h['self']
    hdr.append('inline void SynIterNext_%x(void* pThis) {   // 0x%x\n'
               '    if (*(void**)pThis == nullptr)                                     // insn 2-5\n'
               '        g_fnIT_%x(pThis);\n'
               '    void* pNode = *(void**)((uint8_t*)pThis + 0x%x);                   // insn 6\n'
               '    if (*(uint8_t*)((uint8_t*)pNode + 0x%x) != 0) {                    // insn 7-8\n'
               '        g_fnIT_%x(pNode);                                              // insn 11 (tail)\n'
               '        return;\n    }\n'
               '    void* pRight = *(void**)((uint8_t*)pNode + 0x%x);                  // insn 12\n'
               '    if (*(uint8_t*)((uint8_t*)pRight + 0x%x) == 0) {                   // insn 13-14\n'
               '        void* pChild = *(void**)pRight;                                // insn 15\n'
               '        while (*(uint8_t*)((uint8_t*)pChild + 0x%x) == 0) {             // insn 16,21-22\n'
               '            pRight = pChild;                                           // insn 19\n'
               '            pChild = *(void**)pChild;                                   // insn 20\n'
               '        }\n'
               '        *(void**)((uint8_t*)pThis + 0x%x) = pRight;                     // insn 23\n'
               '        return;\n    }\n'
               '    void* pUp = *(void**)((uint8_t*)pNode + 0x%x);                     // insn 27\n'
               '    while (*(uint8_t*)((uint8_t*)pUp + 0x%x) == 0                    // insn 28-29,35-36\n'
               '           && *(void**)((uint8_t*)pThis + 0x%x) == *(void**)((uint8_t*)pUp + 0x%x)) {  // insn 30-32\n'
               '        *(void**)((uint8_t*)pThis + 0x%x) = pUp;                        // insn 33\n'
               '        pUp = *(void**)((uint8_t*)pUp + 0x%x);                          // insn 34\n'
               '    }\n'
               '    *(void**)((uint8_t*)pThis + 0x%x) = pUp;                           // insn 37\n}'
               % (h['a'], h['a'], h['slot'], s, m, h['slot'], r, m, m, s, s, m, s, r, s, s, s))
hdr += ['', '}  // namespace tq', '', '#endif']
open('modules/syndicate/src/synthunks_it.h', 'w').write('\n'.join(hdr) + '\n')

sc = ['// synthunks_it.cpp — the report seam of family IT.',
      '#include "modules/syndicate/src/synthunks_it.h"', '', 'namespace tq {', '']
sc += ['int (*g_fnIT_%x)(void*) = nullptr;' % s for s in slots]
sc += ['', '}  // namespace tq']
open('modules/syndicate/src/synthunks_it.cpp', 'w').write('\n'.join(sc) + '\n')
json.dump(hits, open('tools/bulk/manifest_it.json', 'w'))
