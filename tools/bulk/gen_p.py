#!/usr/bin/env python3
"""Family P - the std::vector `insert n copies` tail shape (Syndicate.dll v6159).

Transcribed semantics, position by position over the 18 instructions:

    push rbx                         save the result register
    sub rsp,0x20                     frame; one call's shadow space
    sub rdx,rcx                      rdx = pEnd - pBegin   (byte distance)
    mov r10,r8                       r10 = pBase           (third argument, kept for the call)
    sar rdx,k                        rdx = n = (int64)distance >> k   (element count)
    lea rax,[rdx*scale+0x0]          rax = span = n * scale, scale == 1 << k
    lea rbx,[rax+r8*1]               rbx = pDst = pBase + span
    test rdx,rdx
    je   -> index 14  (or jle -> index 14)      skip the call
    mov r8,rcx                       arg3 = pBegin
    mov r9,rax                       arg4 = span
    mov rdx,rax                      arg2 = span
    mov rcx,r10                      arg1 = pBase
    call QWORD PTR [rip@slot]        seam(arg1..arg4)
    mov rax,rbx                      return pDst        (both branch targets land here)
    add rsp,0x20
    pop rbx
    ret

Two observable variants exist and both are kept, because the guard differs:
  * `je`  - the seam runs for every non-zero n, negative n included;
  * `jle` - the seam runs only for n > 0.
Every accepted body uses the same IAT slot (0x1418232a8), the same frame (0x20) and the same
tail, and differs only in shift/scale (2/4 or 3/8) and in that guard.

Nothing is matched by prefix: the whole instruction list must equal the skeleton, the single
branch must resolve to index 14 (the `mov rax,rbx` both paths share) inside this function's
[a,b) range, no other branch may appear, and the one call must be the indirect
`call QWORD PTR [rip@...]` form so it becomes an extern seam rather than a hardcoded address.

Deterministic: accepted set and emission order both derive from funcs.json ordered by start
address; no time, no randomness.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FUNCS = os.path.join(ROOT, 'tools/bulk/funcs.json')
HDR = os.path.join(ROOT, 'modules/syndicate/src/synthunks_p.h')
SRC = os.path.join(ROOT, 'modules/syndicate/src/synthunks_p.cpp')
MAN = os.path.join(ROOT, 'tools/bulk/manifest_p.json')
OWN = ('synthunks_p.h', 'synthunks_p.cpp')   # this family's own output, not "someone else's port"

JUMP = re.compile(r'^(j[a-z]+|loop[a-z]*)\s')
CALL_IAT = re.compile(r'^call QWORD PTR \[rip@(0x[0-9a-f]+)\]$')


def remaining(funcs):
    """Already ported == '0x%x' % a appears in any modules/**/*.{cpp,h} other than our own files."""
    blob = ''
    for root, _dirs, names in os.walk(os.path.join(ROOT, 'modules')):
        for n in sorted(names):
            if n.endswith(('.cpp', '.h')) and n not in OWN:
                with open(os.path.join(root, n), errors='ignore') as fh:
                    blob += fh.read().lower()
    return [f for f in funcs if ('0x%x' % f['a']) not in blob]


def match(f):
    """Return a variant dict, or a rejection-reason string."""
    t, addr = f['text'], f['addr']
    if len(t) != 18:
        return 'instruction count %d != 18' % len(t)
    if f['b'] != f['a'] + f['sz'] or addr[0] != f['a'] or addr[-1] + 1 != f['b']:
        return 'range [a,b) is inconsistent with sz / addr'
    if len(addr) != len(t) or any(addr[i] >= addr[i + 1] for i in range(len(addr) - 1)):
        return 'addr list not strictly increasing'

    sk = [r'^push rbx$', r'^sub rsp,0x([0-9a-f]+)$', r'^sub rdx,rcx$', r'^mov r10,r8$',
          r'^sar rdx,0x([0-9a-f]+)$', r'^lea rax,\[rdx\*([0-9]+)\+0x0\]$',
          r'^lea rbx,\[rax\+r8\*1\]$', r'^test rdx,rdx$', r'^(je|jle) (0x[0-9a-f]+)$',
          r'^mov r8,rcx$', r'^mov r9,rax$', r'^mov rdx,rax$', r'^mov rcx,r10$',
          CALL_IAT.pattern, r'^mov rax,rbx$', r'^add rsp,0x([0-9a-f]+)$', r'^pop rbx$', r'^ret$']
    got = []
    for i, pat in enumerate(sk):
        m = re.fullmatch(pat, t[i])
        if not m:
            return 'instruction %d is %r (expected %s)' % (i, t[i], pat)
        got.append(m)

    k = int(got[4].group(1), 16)
    scale = int(got[5].group(1))
    if scale != 1 << k:
        return 'shift %d does not match scale %d' % (k, scale)
    if got[1].group(1) != got[15].group(1):
        return 'prologue frame %s != epilogue frame %s' % (got[1].group(1), got[15].group(1))

    kind = got[8].group(1)
    tgt = int(got[8].group(2), 16)
    if not (f['a'] <= tgt < f['b']):
        return 'branch target 0x%x outside [0x%x,0x%x)' % (tgt, f['a'], f['b'])
    index = {a: i for i, a in enumerate(addr)}
    if tgt not in index:
        return 'branch target 0x%x is not an instruction boundary' % tgt
    if index[tgt] != 14:
        return 'branch target resolves to index %d, not 14 (mov rax,rbx)' % index[tgt]

    for i, s in enumerate(t):
        if i != 8 and JUMP.match(s):
            return 'unexpected branch %r at index %d' % (s, i)
    if sum(1 for s in t if s.startswith('call ')) != 1:
        return 'expected exactly one call'

    return {'a': f['a'], 'shift': k, 'scale': scale, 'skip': kind,
            'frame': int(got[1].group(1), 16), 'slot': int(got[13].group(1), 16)}


def emit(hits):
    slots = sorted({h['slot'] for h in hits})
    seam = {s: 'g_fnP_%x' % s for s in slots}

    h = ['// synthunks_p.h - RAW Syndicate.dll v6159 - %d `insert n copies` bodies (family P).' % len(hits),
         '// Shape: n = (pEnd - pBegin) sar k, span = n * (1 << k), pDst = pBase + span.',
         '// The slot is called as seam(pBase, span, pBegin, span): argument 1 is rcx <- r10, and',
         '// r10 still holds the incoming third argument because `mov r8,rcx` overwrites r8 with',
         '// pBegin only afterwards. pDst (rbx) is the return value, never an argument.',
         '// The guard is preserved exactly: the `je` variants call for any non-zero n (negative',
         '// included), the `jle` variants only for n > 0. Both land on the shared `mov rax,rbx`.',
         '#ifndef TQ_SYN_THUNKS_P_H',
         '#define TQ_SYN_THUNKS_P_H',
         '',
         '#include <cstdint>',
         '#include <cstring>',
         '',
         'namespace tq {',
         '']
    h += ['extern void* (*%s)(void* pDst, void* pSpan, void* pSrc, void* pSpan2);' % seam[s]
          for s in slots]
    h += ['',
          '// The raw 64-bit distance as a signed value, without an implementation-defined cast.',
          'inline int64_t SynP_Signed(uint64_t u) { int64_t s; std::memcpy(&s, &u, sizeof s); return s; }',
          '// `sar` is an arithmetic shift, so the sign bit is filled in.',
          'inline int64_t SynP_Sar(int64_t v, unsigned k) {',
          '    return v < 0 ? ~(~v >> k) : (v >> k);',
          '}', '']

    for x in hits:
        k, sc = x['shift'], x['scale']
        guard = 'if (n != 0)' if x['skip'] == 'je' else 'if (n > 0)'
        note = ('je: any non-zero n calls the slot' if x['skip'] == 'je'
                else 'jle: only n > 0 calls the slot')
        h.append('inline void* SynInsN_%x(void* pBegin, void* pEnd, void* pBase) {   // 0x%x'
                 % (x['a'], x['a']))
        h.append('    // n = (int64)(pEnd - pBegin) sar %d; span = n * %d; pDst = pBase + span;'
                 % (k, sc))
        h.append('    // %s; slot(pBase, span, pBegin, span); return pDst.' % note)
        h.append('    const int64_t n = SynP_Sar('
                 'SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), %d);' % k)
        h.append('    const uint64_t span = (uint64_t)n * %d;' % sc)
        h.append('    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);')
        h.append('    %s %s(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);'
                 % (guard, seam[x['slot']]))
        h.append('    return pDst;')
        h.append('}')
    h += ['', '}  // namespace tq', '', '#endif']

    s = ['// synthunks_p.cpp - the seams of family P.',
         '#include "modules/syndicate/src/synthunks_p.h"',
         '', 'namespace tq {', '']
    s += ['void* (*%s)(void*, void*, void*, void*) = nullptr;' % seam[x] for x in slots]
    s += ['', '}  // namespace tq']

    man = [{'a': x['a'], 'shift': x['shift'], 'scale': x['scale'], 'skip': x['skip'],
            'frame': x['frame'], 'slot': x['slot'], 'seam': seam[x['slot']]} for x in hits]

    for path, text in ((HDR, '\n'.join(h) + '\n'), (SRC, '\n'.join(s) + '\n')):
        with open(path, 'w') as fh:
            fh.write(text)
    with open(MAN, 'w') as fh:
        fh.write(json.dumps(man, indent=1) + '\n')
    return man


TEST = os.path.join(ROOT, 'tests/cqbase_thunks_p_test.cpp')


def emit_test(hits, seam):
    """A table-driven test: every accepted body is exercised on all three reachable paths."""
    lines = ['// Generated with family P - `insert n copies`. Every accepted body is driven through',
             '// the zero, positive and negative count paths, and each path asserts the seam call,',
             '// its four exact arguments, and the returned pDst.',
             '#include <cstdio>',
             '#include <cstdlib>',
             '#include <cstdint>',
             '#include <cstring>',
             '',
             '#include "modules/syndicate/src/synthunks_p.h"',
             '',
             'using namespace tq;',
             '',
             'static int g_nChecks = 0;',
             '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", '
             '__FILE__, __LINE__, #x); std::abort(); } } while (0)',
             '',
             'typedef void* (*Fn)(void*, void*, void*);',
             '',
             'struct Case { Fn fn; unsigned shift; unsigned scale; bool callOnNegative; uintptr_t addr; };',
             '',
             'static const Case g_cases[] = {']
    for x in hits:
        lines.append('    { &SynInsN_%x, %du, %du, %s, 0x%x },'
                     % (x['a'], x['shift'], x['scale'],
                        'true' if x['skip'] == 'je' else 'false', x['a']))
    lines += ['};',
              'static const int g_nCases = (int)(sizeof g_cases / sizeof g_cases[0]);',
              '',
              'static uintptr_t g_a1, g_a2, g_a3, g_a4;',
              'static int g_nCalls = 0;',
              'static void* Hook(void* x1, void* x2, void* x3, void* x4) {',
              '    g_a1 = (uintptr_t)x1; g_a2 = (uintptr_t)x2;',
              '    g_a3 = (uintptr_t)x3; g_a4 = (uintptr_t)x4;',
              '    ++g_nCalls;',
              '    return (void*)0xBEEF;   // must be ignored: the body returns pDst (rbx), not rax',
              '}',
              '',
              'int main() {',
              '    %s = &Hook;' % seam,
              '    unsigned char abuf[4096];',
              '    std::memset(abuf, 0x5A, sizeof abuf);',
              '    CHECK(g_nCases > 0);',
              '    for (int i = 0; i < g_nCases; ++i) {',
              '        const Case& c = g_cases[i];',
              '        // every accepted address appears exactly once',
              '        for (int j = i + 1; j < g_nCases; ++j) CHECK(c.addr != g_cases[j].addr);',
              '',
              '        void* const pBase = abuf + 2048;',
              '        void* const pBegin = abuf + 1024;',
              '        const uintptr_t kSpan = (uintptr_t)3 * c.scale;',
              '',
              '        // ---- path 1: three elements (n == +3) -> the seam always runs',
              '        g_nCalls = 0; g_a1 = g_a2 = g_a3 = g_a4 = 0;',
              '        void* pR = c.fn(pBegin, (void*)((uint8_t*)pBegin + kSpan), pBase);',
              '        CHECK(g_nCalls == 1);',
              '        CHECK(g_a1 == (uintptr_t)pBase);',
              '        CHECK(g_a2 == kSpan);',
              '        CHECK(g_a3 == (uintptr_t)pBegin);',
              '        CHECK(g_a4 == kSpan);',
              '        CHECK(pR == (void*)((uint8_t*)pBase + kSpan));',
              '',
              '        // ---- path 2: empty range (n == 0) -> the guard skips the seam',
              '        g_nCalls = 0;',
              '        pR = c.fn(pBegin, pBegin, pBase);',
              '        CHECK(g_nCalls == 0);',
              '        CHECK(pR == pBase);',
              '',
              '        // ---- path 3: pEnd below pBegin (n == -3) -> je calls, jle does not',
              '        g_nCalls = 0; g_a1 = g_a2 = g_a3 = g_a4 = 0;',
              '        pR = c.fn(pBegin, (void*)((uint8_t*)pBegin - kSpan), pBase);',
              '        const uintptr_t kNegSpan = (uintptr_t)0 - kSpan;',
              '        if (c.callOnNegative) {',
              '            CHECK(g_nCalls == 1);',
              '            CHECK(g_a1 == (uintptr_t)pBase);',
              '            CHECK(g_a2 == kNegSpan);',
              '            CHECK(g_a3 == (uintptr_t)pBegin);',
              '            CHECK(g_a4 == kNegSpan);',
              '        } else {',
              '            CHECK(g_nCalls == 0);',
              '        }',
              '        CHECK(pR == (void*)((uint8_t*)pBase - kSpan));',
              '',
              '        // ---- path 4: one element, a different count, so shift/scale is really used',
              '        g_nCalls = 0; g_a2 = 0;',
              '        void* const pOne = (void*)((uint8_t*)pBegin + c.scale);',
              '        pR = c.fn(pBegin, pOne, pBase);',
              '        CHECK(c.scale == (1u << c.shift));',
              '        CHECK(g_nCalls == 1);',
              '        CHECK(g_a2 == c.scale);',
              '        CHECK(pR == (void*)((uint8_t*)pBase + c.scale));',
              '    }',
              '    CHECK(g_nCases == %d);' % len(hits),
              '    std::printf("SYNDICATE_THUNKS_P_OK: %d bodies, %d checks\\n", g_nCases, g_nChecks);',
              '    return 0;',
              '}']
    with open(TEST, 'w') as fh:
        fh.write('\n'.join(lines) + '\n')


def main():
    funcs = json.load(open(FUNCS))
    rem = remaining(funcs)
    hits, rejects = [], []
    for f in sorted(rem, key=lambda x: x['a']):
        if 'lea rbx,[rax+r8*1]' not in f['text']:
            continue          # not a candidate for this family at all
        r = match(f)
        if isinstance(r, dict):
            hits.append(r)
        else:
            rejects.append({'a': f['a'], 'why': r})

    print('remaining %d, family P accepted %d, rejected %d' % (len(rem), len(hits), len(rejects)))
    for r in rejects:
        print('  reject 0x%x: %s' % (r['a'], r['why']))
    if not hits:
        print('nothing accepted; refusing to write empty modules')
        return 1
    man = emit(hits)
    seams = {m['seam'] for m in man}
    assert len(seams) == 1, 'family P uses one slot; got %r' % seams
    emit_test(hits, seams.pop())
    print('wrote %s, %s, %s, %s (%d bodies, 1 seam)'
          % (HDR, SRC, MAN, TEST, len(man)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
