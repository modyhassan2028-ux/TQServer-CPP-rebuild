#!/usr/bin/env python3
"""Family Q synthesizer -- the guarded container compare pair (== form / != form).

Raw Syndicate.dll v6159, 18 instructions, frame 0x20, one saved rbx:

  0  mov QWORD PTR [rsp+0x8],rbx        ; home rbx
  1  push rdi
  2  sub rsp,0x20
  3  mov rax,QWORD PTR [rcx]            ; rax = this->head (offset 0)
  4  mov rbx,rdx                        ; rbx = other
  5  mov rdi,rcx                        ; rdi = this
  6  test rax,rax
  7  je   -> idx 10                     ; null head always calls the slot
  8  cmp rax,QWORD PTR [rdx]            ; this->head vs other->head
  9  je   -> idx 11                     ; equal heads -> skip the slot
 10  call QWORD PTR [rip@0x1418233c0]   ; seam: rcx=this, rdx=other, rax discarded
 11  mov rdx,QWORD PTR [rbx+0x8]        ; second word of other, loaded AFTER the call
 12  mov rbx,QWORD PTR [rsp+0x30]
 13  cmp QWORD PTR [rdi+0x8],rdx
 14  sete al | setne al
 15  add rsp,0x20
 16  pop rdi
 17  ret

Acceptance is positional: every one of the 18 instruction strings must match the
pattern above at its own index, both relative jumps must resolve to exactly the
index the semantics implies (10 = the call itself, 11 = the load after it), every
instruction address must lie in [a,b), and the call target must be an IAT slot.
Anything else is refused, never guessed.

The 82 accepted bodies are 41 `sete` and 41 `setne`; index 14 is the only textual
difference between the two families. 22 further remaining bodies share the identical
guard prefix but count elements instead of comparing (`sar rax,0x2`, `sar rax,0x3`
and four imul-magic division tails); they are a different semantic family, left for
a separate batch, and therefore refused here.
"""
import json
import os
import re

FUNCS = 'tools/bulk/funcs.json'
MANIFEST = 'tools/bulk/manifest_q.json'
HDR = 'modules/syndicate/src/synthunks_q.h'
SRC = 'modules/syndicate/src/synthunks_q.cpp'
TEST = 'tests/cqbase_thunks_q_test.cpp'

# "already ported" = '0x%x' % a appears somewhere under modules/. The two files this
# script owns are excluded so a re-run reproduces exactly the same accepted set.
OWN = {'synthunks_q.h', 'synthunks_q.cpp'}

PATTERN = [
    r'mov QWORD PTR \[rsp\+0x8\],rbx',
    r'push rdi',
    r'sub rsp,0x20',
    r'mov rax,QWORD PTR \[rcx\]',
    r'mov rbx,rdx',
    r'mov rdi,rcx',
    r'test rax,rax',
    r'je (0x[0-9a-f]+)',
    r'cmp rax,QWORD PTR \[rdx\]',
    r'je (0x[0-9a-f]+)',
    r'call QWORD PTR \[rip@(0x[0-9a-f]+)\]',
    r'mov rdx,QWORD PTR \[rbx\+0x8\]',
    r'mov rbx,QWORD PTR \[rsp\+0x30\]',
    r'cmp QWORD PTR \[rdi\+0x8\],rdx',
    r'(sete|setne) al',
    r'add rsp,0x20',
    r'pop rdi',
    r'ret',
]
JE1_IDX = 10   # null head -> the call
JE2_IDX = 11   # equal heads -> the load after the call


def already_ported():
    blob = ''
    for root, _dirs, files in os.walk('modules'):
        for name in files:
            if name in OWN:
                continue
            blob += open(os.path.join(root, name), errors='ignore').read().lower()
    return blob


def classify(f):
    """Return ('ok', info) or ('skip', reason); any positional disagreement refuses."""
    text = f['text']
    addr = f['addr']
    for i, a in enumerate(addr):
        if not (f['a'] <= a < f['b']):
            return 'skip', 'insn %d at 0x%x outside [0x%x,0x%x)' % (i, a, f['a'], f['b'])
    if len(text) != len(PATTERN):
        return 'skip', 'shape: instruction count %d != %d' % (len(text), len(PATTERN))
    if len(addr) != len(text):
        return 'skip', 'shape: addr/text length mismatch'
    idx = {a: i for i, a in enumerate(addr)}
    m = []
    for i, rx in enumerate(PATTERN):
        mm = re.fullmatch(rx, text[i])
        if not mm:
            return 'skip', 'shape: insn %d is %r' % (i, text[i])
        m.append(mm)
    t1 = int(m[7].group(1), 16)
    t2 = int(m[9].group(1), 16)
    if t1 not in idx or t2 not in idx:
        return 'skip', 'branch target outside the function'
    if idx[t1] != JE1_IDX:
        return 'skip', 'je@7 resolves to index %d, semantics require %d' % (idx[t1], JE1_IDX)
    if idx[t2] != JE2_IDX:
        return 'skip', 'je@9 resolves to index %d, semantics require %d' % (idx[t2], JE2_IDX)
    if t1 != addr[JE1_IDX] or t2 != addr[JE2_IDX]:
        return 'skip', 'branch target value mismatch'
    return 'ok', {'a': f['a'], 'slot': int(m[10].group(1), 16), 'op': m[14].group(1)}


def name_of(h):
    return ('SynCmpEq_%x' if h['op'] == 'sete' else 'SynCmpNe_%x') % h['a']


def main():
    funcs = json.load(open(FUNCS))
    blob = already_ported()
    remaining = [f for f in funcs if ('0x%x' % f['a']) not in blob]

    accepted, refused, seen = [], [], set()
    for f in remaining:
        kind, info = classify(f)
        if kind == 'ok':
            if f['a'] in seen:
                raise SystemExit('duplicate function start 0x%x' % f['a'])
            seen.add(f['a'])
            accepted.append(info)
        else:
            refused.append((f['a'], info))
    accepted.sort(key=lambda h: h['a'])
    refused.sort()

    n_eq = sum(1 for h in accepted if h['op'] == 'sete')
    n_ne = sum(1 for h in accepted if h['op'] == 'setne')
    slots = sorted({h['slot'] for h in accepted})

    # ---- header -------------------------------------------------------------
    o = []
    o.append('// synthunks_q.h -- RAW Syndicate.dll v6159, %d guarded container compares' % len(accepted))
    o.append('// (family Q: %d "==" bodies ending in `sete al`, %d "!=" bodies ending in `setne al`).' % (n_eq, n_ne))
    o.append('//')
    o.append('// All %d bodies are textually identical except for index 14 (sete/setne) and their address:' % len(accepted))
    o.append('//     head = *(void**)this;                                  // insn 3: mov rax,[rcx]')
    o.append('//     if (!head)                        seam(this, other);  // insn 6-7: je -> the call')
    o.append('//     else if (head != *(void**)other)  seam(this, other);  // insn 8-9: cmp/je -> skip the call')
    o.append('//     return *(uint64_t*)(this+0x8) <op> *(uint64_t*)(other+0x8);')
    o.append('//')
    o.append('// Preserved quirks: the second word of `other` is loaded at insn 11, i.e. AFTER the seam')
    o.append('// returns, so a seam that rewrites other+0x8 is observed by the compare. The seam result')
    o.append('// in rax is discarded (insn 14 overwrites al), hence the void seam type. this+0x8 is')
    o.append('// reloaded at insn 13 as well. Nothing is stored: both bodies are pure compares.')
    o.append('//')
    o.append('// The call target is the single IAT slot [rip@0x1418233c0], modelled as an extern')
    o.append('// function-pointer seam, never as an absolute address.')
    o.append('#ifndef TQ_SYN_THUNKS_Q_H')
    o.append('#define TQ_SYN_THUNKS_Q_H')
    o.append('')
    o.append('#include <cstdint>')
    o.append('')
    o.append('namespace tq {')
    o.append('')
    for s in slots:
        o.append('// IAT [rip@0x%x]: rcx = this, rdx = other, rax discarded.' % s)
        o.append('extern void (*g_fnQ_%x)(void* pThis, void* pOther);' % s)
    o.append('')
    for h in accepted:
        cmp_op = '==' if h['op'] == 'sete' else '!='
        o.append('// 0x%x -- guarded container compare: calls the seam when the head word is null or' % h['a'])
        o.append('//   differs from other\'s head, then answers (this+0x8 %s other+0x8) via `%s al`.' % (cmp_op, h['op']))
        o.append('inline bool %s(void* pThis, void* pOther) {' % name_of(h))
        o.append('    void* pHead = *(void**)pThis;                             // insn 3-5')
        o.append('    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9')
        o.append('        g_fnQ_%x(pThis, pOther);                             // insn 10' % h['slot'])
        o.append('    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12')
        o.append('    return *(uint64_t*)((uint8_t*)pThis + 0x8) %s qOther;   // insn 13-14' % cmp_op)
        o.append('}')
    o.append('')
    o.append('}  // namespace tq')
    o.append('')
    o.append('#endif')
    open(HDR, 'w').write('\n'.join(o) + '\n')

    # ---- seams --------------------------------------------------------------
    s2 = ['// synthunks_q.cpp -- the IAT seam of family Q.',
          '#include "modules/syndicate/src/synthunks_q.h"',
          '',
          'namespace tq {',
          '']
    s2 += ['void (*g_fnQ_%x)(void*, void*) = nullptr;' % s for s in slots]
    s2 += ['', '}  // namespace tq']
    open(SRC, 'w').write('\n'.join(s2) + '\n')

    # ---- test ---------------------------------------------------------------
    t = []
    t.append('// cqbase_thunks_q_test.cpp -- generated by tools/bulk/gen_q.py: family Q, %d bodies.' % len(accepted))
    t.append('// Per body: both guarded paths (null head, differing head) must call the seam with exactly')
    t.append('// (this, other); the unguarded path (equal non-null heads) must not call it. Both outcomes')
    t.append('// of the second-word compare are asserted, and one case proves other+0x8 is read after')
    t.append('// the seam returns.')
    t.append('#include <cstdio>')
    t.append('#include <cstdlib>')
    t.append('#include <cstdint>')
    t.append('')
    t.append('#include "modules/syndicate/src/synthunks_q.h"')
    t.append('')
    t.append('namespace {')
    t.append('')
    t.append('int g_nChecks = 0;')
    t.append('int g_nCalls = 0;')
    t.append('void* g_p1 = nullptr;')
    t.append('void* g_p2 = nullptr;')
    t.append('int g_bMutate = 0;')
    t.append('uint64_t g_mutateValue = 0;')
    t.append('')
    t.append('void Hook(void* pThis, void* pOther) {')
    t.append('    ++g_nCalls;')
    t.append('    g_p1 = pThis;')
    t.append('    g_p2 = pOther;')
    t.append('    if (g_bMutate) *(uint64_t*)((uint8_t*)pOther + 0x8) = g_mutateValue;')
    t.append('}')
    t.append('')
    t.append('void Reset() { g_nCalls = 0; g_p1 = nullptr; g_p2 = nullptr; }')
    t.append('')
    t.append('}  // namespace')
    t.append('')
    t.append('#define CHECK(x) do { ++g_nChecks; if (!(x)) { \\')
    t.append('    std::fprintf(stderr, "FAILED %s:%d  %s\\n", __FILE__, __LINE__, #x); \\')
    t.append('    std::abort(); } } while (0)')
    t.append('')
    t.append('int main() {')
    for s in slots:
        t.append('    tq::g_fnQ_%x = &Hook;' % s)
    t.append('')
    for h in accepted:
        # equal second words -> answer is (sete ? true : false)
        eq_true = (h['op'] == 'sete')
        t.append('    {   // 0x%x' % h['a'])
        t.append('        uint64_t aThis[3] = {0, 0, 0};')
        t.append('        uint64_t aOther[3] = {0, 0, 0};')
        t.append('')
        t.append('        // guarded path 1: null head -> je at insn 7 goes to the call')
        t.append('        aThis[0] = 0; aThis[1] = 0x1111; aOther[0] = 0x2222; aOther[1] = 0x1111;')
        t.append('        Reset();')
        t.append('        CHECK(tq::%s(aThis, aOther) == %s);' % (name_of(h), 'true' if eq_true else 'false'))
        t.append('        CHECK(g_nCalls == 1);')
        t.append('        CHECK(g_p1 == (void*)aThis);')
        t.append('        CHECK(g_p2 == (void*)aOther);')
        t.append('')
        t.append('        // guarded path 2: differing non-null heads -> je at insn 9 not taken')
        t.append('        aThis[0] = 0x2222; aOther[0] = 0x3333; aThis[1] = 0x1111; aOther[1] = 0x9999;')
        t.append('        Reset();')
        t.append('        CHECK(tq::%s(aThis, aOther) == %s);' % (name_of(h), 'false' if eq_true else 'true'))
        t.append('        CHECK(g_nCalls == 1);')
        t.append('        CHECK(g_p1 == (void*)aThis);')
        t.append('        CHECK(g_p2 == (void*)aOther);')
        t.append('')
        t.append('        // unguarded path: equal non-null heads -> no seam, both second-word outcomes')
        t.append('        aThis[0] = 0x2222; aOther[0] = 0x2222; aThis[1] = 0x1111; aOther[1] = 0x1111;')
        t.append('        Reset();')
        t.append('        CHECK(tq::%s(aThis, aOther) == %s);' % (name_of(h), 'true' if eq_true else 'false'))
        t.append('        CHECK(g_nCalls == 0);')
        t.append('        aOther[1] = 0x2222;')
        t.append('        Reset();')
        t.append('        CHECK(tq::%s(aThis, aOther) == %s);' % (name_of(h), 'false' if eq_true else 'true'))
        t.append('        CHECK(g_nCalls == 0);')
        t.append('')
        t.append('        // insn 11 loads other+0x8 after the call, so the seam rewrite is observed')
        t.append('        aThis[0] = 0; aThis[1] = 0x1111; aOther[0] = 0x2222; aOther[1] = 0x1111;')
        t.append('        Reset();')
        t.append('        g_bMutate = 1;')
        t.append('        g_mutateValue = 0x5555;')
        t.append('        CHECK(tq::%s(aThis, aOther) == %s);' % (name_of(h), 'false' if eq_true else 'true'))
        t.append('        g_bMutate = 0;')
        t.append('        CHECK(g_nCalls == 1);')
        t.append('        CHECK(aOther[1] == 0x5555);')
        t.append('    }')
    t.append('')
    t.append('    std::printf("SYNDICATE_THUNKS_Q_OK: %d bodies, %%d checks\\n", g_nChecks);' % len(accepted))
    t.append('    return 0;')
    t.append('}')
    open(TEST, 'w').write('\n'.join(t) + '\n')

    # ---- manifest -----------------------------------------------------------
    json.dump([{'a': h['a'], 'op': h['op'], 'slot': h['slot']} for h in accepted],
              open(MANIFEST, 'w'), indent=1)
    open(MANIFEST, 'a').write('\n')

    print('remaining in funcs.json: %d' % len(remaining))
    print('family Q accepted: %d (sete %d, setne %d, slots %s)'
          % (len(accepted), n_eq, n_ne, ['0x%x' % s for s in slots]))
    print('refused: %d' % len(refused))
    buckets = {}
    for a, why in refused:
        if why.startswith('shape: instruction count'):
            key = 'not this family: instruction count != 18'
        elif why.startswith('shape: insn'):
            key = why
        elif why.startswith('shape: addr'):
            key = why
        elif why.startswith('branch target outside'):
            key = 'branch target outside [a,b)'
        else:
            key = why
        buckets.setdefault(key, []).append(a)
    for key, addrs in sorted(buckets.items(), key=lambda kv: -len(kv[1])):
        print('  %4d x %s' % (len(addrs), key))
    return accepted, refused


if __name__ == '__main__':
    main()
