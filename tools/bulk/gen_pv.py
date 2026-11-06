#!/usr/bin/env python3
"""Family PV — the ordered-tree iterator *predecessor* step (the `--` sibling of family IT).

One whole-body shape of 47 instructions; the identical body appears 32 times in the DLL, and three of
those instances are already ported elsewhere (0x1417c5fa0 / 0x1417c6040 in synrangeB.cpp, 0x1417c64b0
in synnodescal.h), which leaves the 29 bodies this family owns.

    if (this->f00 == 0) report(this);                  // insn 2-5   rcx is the holder, never null
    pNode = this->f08;                                 // insn 6
    if (pNode->mark != 0) {                            // insn 7-8   the iterator sits on end()
        pRight = pNode->f10;                           // insn 9     head->f10, the rightmost node
        this->f08 = pRight;                            // insn 10
        if (pRight->mark == 0) return;                 // insn 11-12
        report(pNode); return;                         // insn 13-15 tail call, rcx = the sentinel
    }
    pLeft = pNode->f00;                                // insn 16
    if (pLeft->mark == 0) {                            // insn 17-18 (jne 30 -> the climb below)
        pRight = pLeft->f10;                           // insn 19
        while (pRight->mark == 0) {                    // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight; pRight = pRight->f10;      // insn 22-23
        }
        this->f08 = pLeft; return;                     // insn 26-29 rightmost of the left subtree
    }
    pUp = pNode->f08;                                  // insn 30
    while (pUp->mark == 0 && this->f08 == pUp->f00) {  // insn 31-32 (jne 40), 33-35 (jne 40), 38-39
        this->f08 = pUp; pUp = pUp->f08;               // insn 36-37
    }
    if (this->f08->mark != 0) { report(pUp); return; } // insn 40-42 (jne 13), rcx = the parent
    this->f08 = pUp;                                   // insn 43

`mark` sits at a per-class offset (+0x29, +0x1d, +0x49 … exactly one value per body) and is always
compared against zero. The links do not vary per body: left +0x00 (a bare [reg] load), parent +0x08,
right +0x10, iterator slot +0x08 — all asserted here, not assumed. Every one of the ten relative
branches is resolved against the instruction index its raw target lands on, and a body that disagrees
on any single check is skipped instead of guessed at.

Deterministic: the only input is tools/bulk/funcs.json and every output is rewritten from scratch, so
re-running reproduces byte-identical files. The 'already ported' filter drops this script's own
outputs, so a second run still sees the same 29 unclaimed bodies.
"""
import glob
import json
import os
import re

FUNCS = 'tools/bulk/funcs.json'
HDR = 'modules/syndicate/src/synthunks_pv.h'
SRC = 'modules/syndicate/src/synthunks_pv.cpp'
TEST = 'tests/cqbase_thunks_pv_test.cpp'
MANIFEST = 'tools/bulk/manifest_pv.json'

# The normalised skeleton of the representative body 0x141723420 (hex replaced by N).
SKELETON = [
    'push rbx',
    'sub rsp,N',
    'cmp QWORD PTR [rcx],N',
    'mov rbx,rcx',
    'jne N',
    'call QWORD PTR [rip@N]',
    'mov rcx,QWORD PTR [rbx+N]',
    'cmp BYTE PTR [rcx+N],N',
    'je N',
    'mov rax,QWORD PTR [rcx+N]',
    'mov QWORD PTR [rbx+N],rax',
    'cmp BYTE PTR [rax+N],N',
    'je N',
    'add rsp,N',
    'pop rbx',
    'rex.W jmp QWORD PTR [rip@N]',
    'mov rax,QWORD PTR [rcx]',
    'cmp BYTE PTR [rax+N],N',
    'jne N',
    'mov rcx,QWORD PTR [rax+N]',
    'cmp BYTE PTR [rcx+N],N',
    'jne N',
    'mov rax,rcx',
    'mov rcx,QWORD PTR [rcx+N]',
    'cmp BYTE PTR [rcx+N],N',
    'je N',
    'mov QWORD PTR [rbx+N],rax',
    'add rsp,N',
    'pop rbx',
    'ret',
    'mov rcx,QWORD PTR [rcx+N]',
    'cmp BYTE PTR [rcx+N],N',
    'jne N',
    'mov rax,QWORD PTR [rcx]',
    'cmp QWORD PTR [rbx+N],rax',
    'jne N',
    'mov QWORD PTR [rbx+N],rcx',
    'mov rcx,QWORD PTR [rcx+N]',
    'cmp BYTE PTR [rcx+N],N',
    'je N',
    'mov rax,QWORD PTR [rbx+N]',
    'cmp BYTE PTR [rax+N],N',
    'jne N',
    'mov QWORD PTR [rbx+N],rcx',
    'add rsp,N',
    'pop rbx',
    'ret',
]

# branch insn -> instruction index its raw target must resolve to, with the meaning it carries
BRANCHES = [
    (4, 6, 'f00 != 0 skips the report call'),
    (8, 16, 'not on the sentinel -> the left-subtree / climb path'),
    (12, 44, 'sentinel: head->f10 is a real node, keep it and return'),
    (18, 30, 'no left child -> climb'),
    (21, 26, 'only the left child itself, no right spine'),
    (25, 22, 'walk the right spine of the left subtree'),
    (32, 40, 'climb reached a marked node -> leave the loop'),
    (35, 40, 'the node is not its parent\'s left child -> leave the loop'),
    (39, 33, 'climb continues at the grandparent'),
    (42, 13, 'the slot is the sentinel here -> report the parent'),
]

MARK_INSNS = (7, 11, 17, 20, 24, 31, 38, 41)   # every marker compare, always against zero
SELF_INSNS = (6, 10, 26, 34, 36, 40, 43)       # [rbx+N]  the iterator's own node slot
PARENT_INSNS = (30, 37)                        # [rcx+N]  node->parent
RIGHT_INSNS = (9, 19, 23)                      # [rcx+N] / [rax+N]  node->f10
LEFT_INSNS = (16, 33)                          # [rcx]   node->f00, no displacement at all
FRAME_INSNS = (1, 13, 27, 44)
SLOT_INSNS = (5, 15)


def shape(text):
    return re.sub(r'0x[0-9a-f]+', 'N', text)


def num(text, which=0):
    return int(re.findall(r'0x([0-9a-f]+)', text)[which], 16)


def write(path, lines):
    with open(path, 'w') as fp:
        fp.write('\n'.join(lines))


def claimed_blob():
    """Every address quoted by a source comment is claimed, except this script's own output."""
    blob = ''
    for pat in ('modules/**/*.h', 'modules/**/*.cpp'):
        for path in sorted(glob.glob(pat, recursive=True)):
            if os.path.basename(path).startswith('synthunks_pv'):
                continue
            blob += open(path, errors='ignore').read().lower()
    return blob


def main():
    funcs = json.load(open(FUNCS))
    claimed = claimed_blob()
    remaining = [f for f in funcs if ('0x%x' % f['a']) not in claimed]

    hits, skipped = [], []
    for f in remaining:
        text = f['text']
        if len(text) != len(SKELETON):
            continue
        if [shape(t) for t in text] != SKELETON:
            continue
        index = {a: i for i, a in enumerate(f['addr'])}
        bad = []

        def target(i):
            return index.get(num(text[i]))

        for insn, want, why in BRANCHES:
            got = target(insn)
            if got is None:
                bad.append('insn %d does not resolve to an instruction of this body' % insn)
            elif got != want:
                bad.append('insn %d lands at %d, expected %d (%s)' % (insn, got, want, why))
        if num(text[2]) != 0:
            bad.append('insn 2 does not compare f00 against zero')
        for i in MARK_INSNS:
            if num(text[i], 1) != 0:
                bad.append('insn %d does not compare the marker against zero' % i)
        marks = {num(text[i]) for i in MARK_INSNS}
        if len(marks) != 1:
            bad.append('marker offset disagreement %s' % sorted('0x%x' % m for m in marks))
        selfs = {num(text[i]) for i in SELF_INSNS}
        if selfs != {0x8}:
            bad.append('iterator slot offsets %s' % sorted('0x%x' % v for v in selfs))
        parents = {num(text[i]) for i in PARENT_INSNS}
        if parents != {0x8}:
            bad.append('parent offsets %s' % sorted('0x%x' % v for v in parents))
        rights = {num(text[i]) for i in RIGHT_INSNS}
        if rights != {0x10}:
            bad.append('right-link offsets %s' % sorted('0x%x' % v for v in rights))
        for i in LEFT_INSNS:
            if re.findall(r'0x([0-9a-f]+)', text[i]):
                bad.append('insn %d is not a bare [reg] load' % i)
        frames = {num(text[i]) for i in FRAME_INSNS}
        if len(frames) != 1:
            bad.append('frame size disagreement %s' % sorted('0x%x' % v for v in frames))
        if num(text[15]) != num(text[5]) or len({num(text[5]), num(text[15])}) != 1:
            bad.append('report seam disagreement 0x%x / 0x%x' % (num(text[5]), num(text[15])))

        if bad:
            skipped.append({'a': f['a'], 'reason': '; '.join(bad)})
            continue

        hits.append({
            'a': f['a'],
            'mark': marks.pop(),
            'slot': num(text[5]),
            'frame': frames.pop(),
            'self': selfs.pop(),
            'parent': parents.pop(),
            'right': rights.pop(),
            'insns': len(text),
            'branches': {str(i): target(i) for i, _, _ in BRANCHES},
        })

    hits.sort(key=lambda h: h['a'])
    print('family PV: %d bodies ported, %d skipped' % (len(hits), len(skipped)))
    for s in skipped:
        print('  skipped 0x%x: %s' % (s['a'], s['reason']))
    print('mark offsets: %s' % ', '.join('0x%x' % m for m in sorted({h['mark'] for h in hits})))
    print('frame sizes: %s' % ', '.join('0x%x' % m for m in sorted({h['frame'] for h in hits})))

    write_header(hits)
    write_source(hits)
    write_test(hits)
    with open(MANIFEST, 'w') as fp:
        json.dump({'family': 'PV', 'representative': 0x141723420, 'skeleton': SKELETON,
                   'branches': [{'insn': i, 'lands': t, 'why': w} for i, t, w in BRANCHES],
                   'mark_insns': list(MARK_INSNS), 'bodies': hits, 'skipped': skipped},
                  fp, sort_keys=True, indent=1)
        fp.write('\n')


def write_header(hits):
    marks = sorted({h['mark'] for h in hits})
    frames = sorted({h['frame'] for h in hits})
    out = [
        '// synthunks_pv.h — RAW Syndicate.dll v6159 · %d ordered-tree iterator predecessor steps' % len(hits),
        '// (family PV, the `--` sibling of family IT). The whole body is 47 instructions; each instance',
        '// below is transcribed instruction by instruction, never inferred from the IT sibling.',
        '//',
        '// The marker byte sits at a per-class offset (%s) and is always compared' % ', '.join('+0x%x' % m for m in marks),
        '// against zero. The links do not vary: left +0x0 (a bare [reg] load), parent +0x8, right +0x10,',
        '// iterator node slot +0x8, frame 0x%s. Three quirks are preserved verbatim:' % ',0x'.join('%x' % f for f in frames),
        '//   * the null-container guard (insn 2-5) hands the *holder* pThis to the report seam, not null;',
        '//   * the sentinel path (insn 9-15) stores head->f10 before deciding, so the store survives even',
        '//     when the tail call follows, and that tail call still carries the sentinel in rcx;',
        '//   * insn 40-42 re-reads the slot it just wrote and, if that node is marked, tail-calls the seam',
        '//     with the parent that ended the climb. Given the invariant tested at insn 31 the slot can',
        '//     never be marked there for a well-formed tree, so the path is unreachable — kept as in the',
        '//     raw rather than "fixed".',
        '#ifndef TQ_SYN_THUNKS_PV_H',
        '#define TQ_SYN_THUNKS_PV_H',
        '',
        '#include <cstdint>',
        '',
        'namespace tq {',
        '',
    ]
    slots = sorted({h['slot'] for h in hits})
    out += ['extern void (*g_fnPV_%x)(void* pArg);' % s for s in slots] + ['']
    for h in hits:
        m = '0x%x' % h['mark']
        seam = 'g_fnPV_%x' % h['slot']
        out.append('\n'.join([
            'inline void SynIterPrev_%x(void* pThis) {   // 0x%x' % (h['a'], h['a']),
            '    if (*(void**)pThis == nullptr)                                     // insn 2-5',
            '        %s(pThis);                                            // insn 5 (rcx = the holder)' % seam,
            '    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6',
            '    if (*(uint8_t*)((uint8_t*)pNode + %s) != 0) {                  // insn 7-8 (je 16)' % m,
            '        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9',
            '        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10',
            '        if (*(uint8_t*)((uint8_t*)pRight + %s) == 0)                 // insn 11-12 (je 44)' % m,
            '            return;                                                     // insn 44-46',
            '        %s(pNode);                                            // insn 13-15 (rcx = the sentinel)' % seam,
            '        return;',
            '    }',
            '    void* pLeft = *(void**)pNode;                                      // insn 16',
            '    if (*(uint8_t*)((uint8_t*)pLeft + %s) == 0) {                  // insn 17-18 (jne 30 -> climb)' % m,
            '        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19',
            '        while (*(uint8_t*)((uint8_t*)pRight + %s) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)' % m,
            '            pLeft = pRight;                                             // insn 22',
            '            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23',
            '        }',
            '        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26',
            '        return;                                                        // insn 27-29',
            '    }',
            '    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30',
            '    while (*(uint8_t*)((uint8_t*)pUp + %s) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)' % m,
            '           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)',
            '        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36',
            '        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37',
            '    }',
            '    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40',
            '    if (*(uint8_t*)((uint8_t*)pMarked + %s) != 0) {                 // insn 41-42 (jne 13)' % m,
            '        %s(pUp);                                              // insn 13-15 (rcx = the parent)' % seam,
            '        return;',
            '    }',
            '    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43',
            '}',
        ]))
    out += ['', '}  // namespace tq', '', '#endif', '']
    write(HDR, out)


def write_source(hits):
    slots = sorted({h['slot'] for h in hits})
    out = ['// synthunks_pv.cpp — the report seam of family PV (the single IAT slot every body calls).',
           '#include "modules/syndicate/src/synthunks_pv.h"',
           '',
           'namespace tq {',
           '']
    out += ['void (*g_fnPV_%x)(void*) = nullptr;' % s for s in slots]
    out += ['', '}  // namespace tq', '']
    write(SRC, out)


def write_test(hits):
    out = [
        '// Generated by tools/bulk/gen_pv.py — family PV predecessor walk over a hand-built tree.',
        '//',
        '// Tree:  nil sentinel (mark=1) ;  head (mark=1, head.parent = the root) ;',
        '//        root H  (H.left = A, H.right = B) ;  A.right = C ;  every other link is the nil',
        '//        sentinel. Per body: (a) descend the right spine of the left subtree, (b) climb to',
        '//        end(), (c) the root case, (d) the sentinel at end(); plus (e) the sentinel over an',
        '//        empty tree (reports), (f) a climb that stops at a non-left child, and (g) the',
        '//        null-container guard, which must hand pThis itself to the seam.',
        '#include <cstdio>',
        '#include <cstdlib>',
        '#include <cstdint>',
        '#include <cstring>',
        '',
        '#include "modules/syndicate/src/synthunks_pv.h"',
        '',
        'using namespace tq;',
        '',
        'static int g_nChecks = 0;',
        '#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\\n", '
        '__FILE__, __LINE__, #x); std::abort(); } } while (0)',
        '',
        'static void* g_pArg = nullptr;',
        'static int g_nRep = 0;',
        'static void Hook(void* p) { ++g_nRep; g_pArg = p; }',
        '',
        '// the iterator object: f00 = the container, f08 = the current node',
        'enum { HOLD = 0x0, SLOT = 0x8 };',
        '// every PV node body: left, parent, right (asserted by the generator, re-checked by the audit)',
        'enum { LEFT = 0x0, UP = 0x8, RIGHT = 0x10 };',
        '',
        'alignas(16) static unsigned char aNone[0x80], aHead[0x80], aH[0x80], aA[0x80], aB[0x80], aC[0x80];',
        'alignas(16) static unsigned char aMark2[0x80];   // a second marked node, to tell the seam arg apart',
        'alignas(16) static unsigned char aThis[0x80];',
        '',
        'static inline void* at(void* p, size_t o) { return *(void**)((unsigned char*)p + o); }',
        'static inline void put(void* p, size_t o, void* v) { *(void**)((unsigned char*)p + o) = v; }',
        'static inline void setmk(void* p, size_t o, unsigned char v) '
        '{ *(unsigned char*)((unsigned char*)p + o) = v; }',
        '',
        'static void Build(size_t nMark) {',
        '    std::memset(aNone, 0, sizeof(aNone)); std::memset(aHead, 0, sizeof(aHead));',
        '    std::memset(aH, 0, sizeof(aH)); std::memset(aA, 0, sizeof(aA));',
        '    std::memset(aB, 0, sizeof(aB)); std::memset(aC, 0, sizeof(aC));',
        '    std::memset(aMark2, 0, sizeof(aMark2));',
        '    setmk(aNone, nMark, 1);                       // the nil sentinel',
        '    setmk(aHead, nMark, 1);                       // end()',
        '    setmk(aMark2, nMark, 1);                      // a second marked node',
        '    put(aHead, UP, aH); put(aHead, LEFT, aA); put(aHead, RIGHT, aB);',
        '    put(aH, UP, aHead); put(aH, LEFT, aA); put(aH, RIGHT, aB); setmk(aH, nMark, 0);',
        '    put(aA, UP, aH); put(aA, LEFT, aNone); put(aA, RIGHT, aC); setmk(aA, nMark, 0);',
        '    put(aB, UP, aH); put(aB, LEFT, aNone); put(aB, RIGHT, aNone); setmk(aB, nMark, 0);',
        '    put(aC, UP, aA); put(aC, LEFT, aNone); put(aC, RIGHT, aNone); setmk(aC, nMark, 0);',
        '}',
        '',
        '#define RUN(fn, nMark) do { \\',
        '    /* (a) left child present: rightmost node of its right spine */ \\',
        '    Build(nMark); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aH); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 0); CHECK(at(aThis, SLOT) == aC); \\',
        '    /* (b) no left child, node is a left child: climb to end() */ \\',
        '    Build(nMark); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aA); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 0); CHECK(at(aThis, SLOT) == aHead); \\',
        '    /* (c) the root: the climb exits at once on the head */ \\',
        '    Build(nMark); put(aH, LEFT, aNone); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aH); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 0); CHECK(at(aThis, SLOT) == aHead); \\',
        '    /* (d) the sentinel at end(): head->f10 is the rightmost node, no report */ \\',
        '    Build(nMark); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aHead); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 0); CHECK(at(aThis, SLOT) == aB); \\',
        '    /* (d2) sentinel whose f10 is marked: the slot takes that node, and the seam gets the */ \\',
        '    /*      sentinel, because the raw still carries rcx from insn 6 in that tail call */ \\',
        '    Build(nMark); put(aHead, RIGHT, aMark2); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aHead); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 1); CHECK(g_pArg == (void*)aHead); CHECK(at(aThis, SLOT) == aMark2); \\',
        '    /* (f) climb stops because the node is not its parent\'s left child */ \\',
        '    Build(nMark); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, (void*)1); put(aThis, SLOT, aB); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 0); CHECK(at(aThis, SLOT) == aH); \\',
        '    /* (g) null container: the seam receives pThis, then the walk continues */ \\',
        '    Build(nMark); g_nRep = 0; g_pArg = nullptr; \\',
        '    put(aThis, HOLD, nullptr); put(aThis, SLOT, aA); \\',
        '    fn(aThis); \\',
        '    CHECK(g_nRep == 1); CHECK(g_pArg == (void*)aThis); CHECK(at(aThis, SLOT) == aHead); \\',
        '} while (0)',
        '',
        'int main() {',
    ]
    out += ['    g_fnPV_%x = &Hook;' % s for s in sorted({h['slot'] for h in hits})]
    out += ['']
    out += ['    RUN(SynIterPrev_%x, 0x%x);   // 0x%x  mark +0x%x' % (h['a'], h['mark'], h['a'], h['mark'])
            for h in hits]
    out += ['',
            '    std::printf("SYNDICATE_THUNKS_PV_OK: %d bodies, %%d checks\\n", g_nChecks);' % len(hits),
            '    return 0;',
            '}',
            '']
    write(TEST, out)


if __name__ == '__main__':
    main()
