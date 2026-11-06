#!/usr/bin/env python3
"""Wave S — family S of Syndicate.dll v6159: the "store this[0] and owner[+0x8]" thunk.

Only ONE shape exists in the pdata listing under the requested prologue, and it occurs 32
times, byte-identical apart from the `jne` displacement and the IAT slot:

    0  mov QWORD PTR [rsp+0x8],rbx      ; home rbx at entry_rsp+8
    1  push rdi                         ; entry_rsp -= 8
    2  sub rsp,0x30                     ; 0x20 locals + 0x10 shadow
    3  mov rax,QWORD PTR [r8+0x8]       ; owner[+0x8]     (owner = r8 = 3rd argument)
    4  mov rbx,rdx                      ; dest <- arg2
    5  mov rdi,rcx                      ; this <- arg1
    6  mov QWORD PTR [rsp+0x28],rax     ; spill owner[+0x8] into the temp's upper qword
    7  test rcx,rcx
    8  jne <inside>                     ; MUST resolve to instruction index 10
    9  call QWORD PTR [rip@0x1418233c0] ; _invalid_parameter_noinfo, only when this == null
   10  mov rax,QWORD PTR [rdi]          ; <- jne target: this[0]
   11  lea rcx,[rsp+0x20]               ; rcx = &tmp (clobbers the `this` argument)
   12  mov QWORD PTR [rsp+0x20],rax     ; tmp[0] = this[0]
   13  mov rax,QWORD PTR [rcx]          ; tmp[0]
   14  mov QWORD PTR [rbx],rax          ; dest[0] = this[0]
   15  mov rax,QWORD PTR [rcx+0x8]      ; [rsp+0x28] == the spill == owner[+0x8]
   16  mov QWORD PTR [rbx+0x8],rax      ; dest[1] = owner[+0x8]
   17  mov rax,rbx
   18  mov rbx,QWORD PTR [rsp+0x40]     ; entry_rsp+8 -> the homed rbx
   19  add rsp,0x30
   20  pop rdi
   21  ret

So the body is NOT a two-qword copy of `this`: the second store's source is the owner:
    dest[0] = this[0]
    dest[1] = owner[+0x8]

Quirks preserved on purpose:
  * `[r8+0x8]` is read BEFORE the null guard, so the original dereferences the owner even when
    `this` is null, and the read keeps that position in the port.
  * the "spill" at [rsp+0x28] is live: `lea rcx,[rsp+0x20]` gives the temporary 16 bytes, and
    `[rcx+0x8]` reads the spill back. That is why dest[1] is the owner's qword, not this[1].
  * the guard tests arg1 (`this`) only — never dest, never owner.
  * the `lea` clobbers rcx before the loads, so `this` is dead after instruction 10 and
    this[+0x8] is never read.
  * the null path calls the slot and then still runs `mov rax,[rdi]` with rdi == 0, i.e. it
    faults rather than returning; the port keeps that order and the test verifies the call
    reaches the seam before any store, using a non-returning seam.
  * frame 0x30 = 0x20 locals + 0x10 shadow; rbx is homed at entry_rsp+8 and restored from
    [rsp+0x40] after `add rsp,0x30`.
  * exactly two qwords are written through `dest` ([rbx] and [rbx+0x8]).

Matching is structural, never by memory: every instruction is compared position by position
against BODY, the single branch must resolve to instruction index 10, a branch target outside
[a,b) rejects the function, and any additional branch rejects it too. The generator ignores its
own outputs when computing the already-ported set so it is re-runnable and deterministic.
"""
import json
import os
import re

FUNCS = 'tools/bulk/funcs.json'
OWN = ('synthunks_s',)          # files this generator emits (excluded from "already ported")

BODY = [
    'mov QWORD PTR [rsp+0x8],rbx',
    'push rdi',
    'sub rsp,0x30',
    'mov rax,QWORD PTR [r8+0x8]',
    'mov rbx,rdx',
    'mov rdi,rcx',
    'mov QWORD PTR [rsp+0x28],rax',
    'test rcx,rcx',
    None,                                   # 8  jne <target>
    None,                                   # 9  call QWORD PTR [rip@<slot>]
    'mov rax,QWORD PTR [rdi]',
    'lea rcx,[rsp+0x20]',
    'mov QWORD PTR [rsp+0x20],rax',
    'mov rax,QWORD PTR [rcx]',
    'mov QWORD PTR [rbx],rax',
    'mov rax,QWORD PTR [rcx+0x8]',
    'mov QWORD PTR [rbx+0x8],rax',
    'mov rax,rbx',
    'mov rbx,QWORD PTR [rsp+0x40]',
    'add rsp,0x30',
    'pop rdi',
    'ret',
]
JNE_IDX = 8
CALL_IDX = 9
TARGET_IDX = 10          # `mov rax,QWORD PTR [rdi]` — what the semantics implies
NAME = 'SynStorePair_%x'


def ported_blob():
    """A lowercase '0x%x' % a found under modules/ marks that function as already ported."""
    blob = ''
    for root, _dirs, files in os.walk('modules'):
        for n in sorted(files):
            if not n.endswith(('.cpp', '.h')):
                continue
            if n.startswith(OWN):
                continue                      # our own output must not hide its own bodies
            blob += open(os.path.join(root, n), errors='ignore').read().lower()
    return blob


def classify(text):
    if len(text) != len(BODY):
        return 'length %d != %d' % (len(text), len(BODY))
    for i, want in enumerate(BODY):
        if want is not None and text[i] != want:
            return 'instruction %d differs: expected %r, got %r' % (i, want, text[i])
    if not re.fullmatch(r'jne (0x[0-9a-f]+)', text[JNE_IDX]):
        return 'instruction 8 is not `jne <absolute>`'
    if not re.fullmatch(r'call QWORD PTR \[rip@(0x[0-9a-f]+)\]', text[CALL_IDX]):
        return 'instruction 9 is not `call QWORD PTR [rip@...]`'
    return 'match'


def analyse(f):
    text, addrs = f['text'], f['addr']
    if addrs[0] != f['a']:
        raise ValueError('%x: addr[0] != a' % f['a'])
    if f['b'] <= f['a']:
        raise ValueError('%x: empty range' % f['a'])
    if f['sz'] != f['b'] - f['a']:
        raise ValueError('%x: sz %d != b-a %d' % (f['a'], f['sz'], f['b'] - f['a']))
    why = classify(text)
    if why != 'match':
        raise ValueError('%x: %s' % (f['a'], why))

    target = int(re.fullmatch(r'jne (0x[0-9a-f]+)', text[JNE_IDX]).group(1), 16)
    if not (f['a'] <= target < f['b']):
        raise ValueError('%x: jne target %x outside [%x,%x)' % (f['a'], target, f['a'], f['b']))
    index_of = {a: i for i, a in enumerate(addrs)}
    if target not in index_of:
        raise ValueError('%x: jne target %x is not an instruction start' % (f['a'], target))
    if index_of[target] != TARGET_IDX:
        raise ValueError('%x: jne lands on index %d, semantics implies %d'
                         % (f['a'], index_of[target], TARGET_IDX))
    if [i for i, s in enumerate(text) if re.match(r'^(j|loop)', s)] != [JNE_IDX]:
        raise ValueError('%x: unexpected branch set' % f['a'])
    if text[-1] != 'ret':
        raise ValueError('%x: last instruction is not ret' % f['a'])
    slot = int(re.fullmatch(r'call QWORD PTR \[rip@(0x[0-9a-f]+)\]', text[CALL_IDX]).group(1), 16)
    return {'a': f['a'], 'b': f['b'], 'sz': f['sz'], 'slot': slot,
            'target': target, 'jne_index': index_of[target]}


def scan():
    funcs = json.load(open(FUNCS))
    blob = ported_blob()
    rem = [f for f in funcs if ('0x%x' % f['a']) not in blob]
    prologue = ['mov QWORD PTR [rsp+0x8],rbx', 'push rdi']
    cands = [f for f in rem if f['text'][:2] == prologue]
    accepted, refused = [], []
    for f in cands:
        try:
            accepted.append(analyse(f))
        except ValueError as e:
            refused.append((f['a'], str(e)))
    accepted.sort(key=lambda r: r['a'])
    return rem, cands, accepted, refused


def emit_header(hits):
    slots = sorted({h['slot'] for h in hits})
    L = ['// ============================================================================',
         '// synthunks_s.h — RAW Syndicate.dll v6159 · family S, %d bodies.' % len(hits),
         '//',
         '// The this[0] + owner[+0x8] store thunk. Every body is instruction-for-instruction',
         '// identical; only the `jne` displacement and the IAT slot vary, and both are recorded',
         '// per body below.',
         '//',
         '//   dest[0] = this[0];',
         '//   dest[1] = owner[+0x8];     // the spill at [rsp+0x28] is the temp\'s upper qword',
         '//   return dest;',
         '//',
         '// in front of which sits `test rcx,rcx / jne`: the IAT slot runs only when `this` is',
         '// null. Argument registers: rcx = this (arg1), rdx = dest (arg2), r8 = owner (arg3).',
         '// r9 (arg4) is never read and is not modelled, exactly as in the raw.',
         '//',
         '// Quirks preserved exactly as disassembled:',
         '//   * `mov rax,QWORD PTR [r8+0x8]` (owner[+0x8]) is read BEFORE the null guard, so the',
         '//     original dereferences the owner even when `this` is null; the port keeps the read',
         '//     and its position.',
         '//   * the spill at [rsp+0x28] is live: `lea rcx,[rsp+0x20]` makes the temporary 16',
         '//     bytes wide and `[rcx+0x8]` reads the spill back. dest[1] therefore comes from the',
         '//     OWNER, not from this[+0x8].',
         '//   * the guard tests arg1 (`this`) only.',
         '//   * the `lea` clobbers rcx (the `this` argument) before the loads, so `this` is dead',
         '//     after instruction 10 and this[+0x8] is never read.',
         '//   * the null path calls the slot and then still executes `mov rax,[rdi]` with rdi == 0,',
         '//     i.e. it faults instead of returning; the port reproduces that order.',
         '//   * frame 0x30 = 0x20 locals + 0x10 shadow; rbx is homed at entry_rsp+8 and restored',
         '//     from [rsp+0x40] after `add rsp,0x30`.',
         '//   * exactly two qwords are written through `dest` ([rbx] and [rbx+0x8]).',
         '//',
         '// The IAT slot 0x1418233c0 is _invalid_parameter_noinfo. It is reached through an extern',
         '// function-pointer seam, never as a hardcoded address. The prototype carries the three',
         '// argument registers live at the call site (rcx == this == null, rdx == dest,',
         '// r8 == owner); the CRT callee ignores them, and exposing them lets the test pin the',
         '// exact call state.',
         '// ============================================================================',
         '#ifndef TQ_SYN_THUNKS_S_H',
         '#define TQ_SYN_THUNKS_S_H',
         '',
         '#include <cstdint>',
         '',
         'namespace tq {',
         '']
    for s in slots:
        L.append('// _invalid_parameter_noinfo — the guard slot, shared by all %d bodies' % len(hits))
        L.append('extern void (*g_fnS_%x)(void* pThis, void* pDest, void* pOwner);' % s)
    L.append('')
    L.append('// — one body per pdata entry ------------------------------------------------------')
    for h in hits:
        L.append('inline void* %s(void* pThis, void* pDest, void* pOwner) {' % (NAME % h['a']))
        L.append('    // 0x%x · 22 insns · jne 0x%x -> insn %d · slot 0x%x'
                 % (h['a'], h['target'], h['jne_index'], h['slot']))
        L.append('    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard')
        L.append('    if (pThis == nullptr)')
        L.append('        g_fnS_%x(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand'
                 % h['slot'])
        L.append('    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]')
        L.append('    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)')
        L.append('    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp')
        L.append('    *(void**)pDest = pTmp[0];                         // 13/14: through rcx')
        L.append('    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]')
        L.append('    return pDest;                                     // 17')
        L.append('}')
    L += ['', '}  // namespace tq', '', '#endif']
    return '\n'.join(L) + '\n'


def emit_source(hits):
    L = ['// synthunks_s.cpp — the seams of family S.',
         '#include "modules/syndicate/src/synthunks_s.h"',
         '',
         'namespace tq {',
         '']
    for s in sorted({h['slot'] for h in hits}):
        L.append('void (*g_fnS_%x)(void*, void*, void*) = nullptr;   // _invalid_parameter_noinfo' % s)
    L += ['', '}  // namespace tq']
    return '\n'.join(L) + '\n'


def emit_test(hits):
    T = ['// Generated by tools/bulk/gen_s.py — family S, both paths per body.',
         '//',
         '// Path A (this != null): the seam must stay uncalled, dest[0] must receive this[0],',
         '// dest[1] must receive owner[+0x8] even though this[+0x8] holds a different value,',
         '// nothing past dest[+0xf] may be written and `this` must be left untouched.',
         '// Path B (this == null): the seam must run, with exactly (null, dest, owner), before',
         '// any store reaches dest; the seam does not return (longjmp), which is how the test',
         '// observes the call without executing the original\'s faulting `mov rax,[rdi]`.',
         '#include <csetjmp>',
         '#include <cstdint>',
         '#include <cstdio>',
         '#include <cstdlib>',
         '#include <cstring>',
         '',
         '#include "modules/syndicate/src/synthunks_s.h"',
         '',
         'using namespace tq;',
         '',
         'static int g_nChecks = 0;',
         '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n",'
         ' __FILE__, __LINE__, #x); std::abort(); } } while (0)',
         '',
         'static std::jmp_buf g_jmp;',
         'static bool  g_bArmed = false;',
         'static void* g_pSeamThis = nullptr;',
         'static void* g_pSeamDest = nullptr;',
         'static void* g_pSeamOwner = nullptr;',
         'static int   g_nSeam = 0;',
         '',
         'static void Seam(void* pThis, void* pDest, void* pOwner) {',
         '    ++g_nSeam;',
         '    g_pSeamThis = pThis;',
         '    g_pSeamDest = pDest;',
         '    g_pSeamOwner = pOwner;',
         '    if (g_bArmed) { g_bArmed = false; std::longjmp(g_jmp, 1); }',
         '}',
         '',
         'static bool BytesAre(const void* p, size_t n, unsigned char v) {',
         '    const unsigned char* q = (const unsigned char*)p;',
         '    for (size_t i = 0; i < n; ++i) if (q[i] != v) return false;',
         '    return true;',
         '}',
         '',
         'int main() {']
    for s in sorted({h['slot'] for h in hits}):
        T.append('    g_fnS_%x = &Seam;' % s)
    T += ['    unsigned char aThis[0x20], aOwner[0x20], aDest[0x20], aBefore[0x20];', '']
    for h in hits:
        a = h['a']
        T.append('    {   // 0x%x' % a)
        T.append('        std::memset(aThis, 0x11, sizeof aThis);')
        T.append('        std::memset(aOwner, 0x22, sizeof aOwner);')
        T.append('        std::memset(aDest, 0xA5, sizeof aDest);')
        tag = a & 0xFFFF
        T.append('        *(void**)(aThis + 0x0) = (void*)(uintptr_t)0x%xULL;   // this[0]' % (0xC0DE0000 | tag))
        T.append('        *(void**)(aThis + 0x8) = (void*)(uintptr_t)0x%xULL;   // this[+8]: must NOT be read' % (0xD1FF0000 | tag))
        T.append('        *(void**)(aOwner + 0x0) = (void*)(uintptr_t)0x%xULL;  // owner[0]: unused' % (0xA0A00000 | tag))
        T.append('        *(void**)(aOwner + 0x8) = (void*)(uintptr_t)0x%xULL;  // owner[+8]: dest[1]' % (0xB0B00000 | tag))
        T.append('        std::memcpy(aBefore, aThis, sizeof aBefore);')
        T.append('        g_nSeam = 0; g_pSeamThis = g_pSeamDest = g_pSeamOwner = nullptr;')
        T.append('        void* pRet = %s(aThis, aDest, aOwner);' % (NAME % a))
        T.append('        CHECK(pRet == (void*)aDest);              // returned value is the destination')
        T.append('        CHECK(g_nSeam == 0);                      // non-null this: slot untouched')
        T.append('        CHECK(*(void**)(aDest + 0x0) == *(void**)(aThis + 0x0));   // dest[0] = this[0]')
        T.append('        CHECK(*(void**)(aDest + 0x8) == *(void**)(aOwner + 0x8));  // dest[1] = owner[+8]')
        T.append('        CHECK(*(void**)(aDest + 0x8) != *(void**)(aThis + 0x8));   // NOT this[+8]')
        T.append('        CHECK(*(void**)(aDest + 0x0) != *(void**)(aOwner + 0x0));   // NOT owner[0]')
        T.append('        CHECK(BytesAre(aDest + 0x10, 0x10, 0xA5));   // exactly two qwords written')
        T.append('        CHECK(std::memcmp(aThis, aBefore, sizeof aBefore) == 0);      // this preserved')
        T.append('        std::memset(aDest, 0xA5, sizeof aDest);')
        T.append('        g_nSeam = 0; g_bArmed = true;')
        T.append('        if (setjmp(g_jmp) == 0) {')
        T.append('            %s(nullptr, aDest, aOwner);' % (NAME % a))
        T.append('            CHECK(false);   // unreachable: the seam must not return')
        T.append('        } else {')
        T.append('            CHECK(g_nSeam == 1);                       // exactly one slot call')
        T.append('            CHECK(g_pSeamThis == nullptr);             // rcx == this == null')
        T.append('            CHECK(g_pSeamDest == (void*)aDest);        // rdx == dest')
        T.append('            CHECK(g_pSeamOwner == (void*)aOwner);      // r8 == owner')
        T.append('            CHECK(BytesAre(aDest, sizeof aDest, 0xA5)); // no store before the call')
        T.append('        }')
        T.append('    }')
    T += ['',
          '    std::printf("SYNDICATE_THUNKS_S_OK: %d bodies, %%d checks\\n", g_nChecks);' % len(hits),
          '    return 0;',
          '}']
    return '\n'.join(T) + '\n'


def main():
    rem, cands, hits, refused = scan()
    if not hits:
        raise SystemExit('no family S bodies matched')
    open('modules/syndicate/src/synthunks_s.h', 'w').write(emit_header(hits))
    open('modules/syndicate/src/synthunks_s.cpp', 'w').write(emit_source(hits))
    open('tests/cqbase_thunks_s_test.cpp', 'w').write(emit_test(hits))
    json.dump([{'a': h['a'], 'b': h['b'], 'sz': h['sz'], 'slot': h['slot'],
                'jne_target': h['target'], 'jne_index': h['jne_index']} for h in hits],
              open('tools/bulk/manifest_s.json', 'w'), indent=1)
    print('remaining          %d' % len(rem))
    print('prefix candidates  %d' % len(cands))
    print('family S accepted  %d' % len(hits))
    for i, h in enumerate(hits):
        print('  [%2d] 0x%x slot 0x%x jne->0x%x idx %d' % (i, h['a'], h['slot'], h['target'], h['jne_index']))
    print('refused            %d' % len(refused))


if __name__ == '__main__':
    main()
