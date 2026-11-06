// ============================================================================
// synthunks_s.h — RAW Syndicate.dll v6159 · family S, 32 bodies.
//
// The this[0] + owner[+0x8] store thunk. Every body is instruction-for-instruction
// identical; only the `jne` displacement and the IAT slot vary, and both are recorded
// per body below.
//
//   dest[0] = this[0];
//   dest[1] = owner[+0x8];     // the spill at [rsp+0x28] is the temp's upper qword
//   return dest;
//
// in front of which sits `test rcx,rcx / jne`: the IAT slot runs only when `this` is
// null. Argument registers: rcx = this (arg1), rdx = dest (arg2), r8 = owner (arg3).
// r9 (arg4) is never read and is not modelled, exactly as in the raw.
//
// Quirks preserved exactly as disassembled:
//   * `mov rax,QWORD PTR [r8+0x8]` (owner[+0x8]) is read BEFORE the null guard, so the
//     original dereferences the owner even when `this` is null; the port keeps the read
//     and its position.
//   * the spill at [rsp+0x28] is live: `lea rcx,[rsp+0x20]` makes the temporary 16
//     bytes wide and `[rcx+0x8]` reads the spill back. dest[1] therefore comes from the
//     OWNER, not from this[+0x8].
//   * the guard tests arg1 (`this`) only.
//   * the `lea` clobbers rcx (the `this` argument) before the loads, so `this` is dead
//     after instruction 10 and this[+0x8] is never read.
//   * the null path calls the slot and then still executes `mov rax,[rdi]` with rdi == 0,
//     i.e. it faults instead of returning; the port reproduces that order.
//   * frame 0x30 = 0x20 locals + 0x10 shadow; rbx is homed at entry_rsp+8 and restored
//     from [rsp+0x40] after `add rsp,0x30`.
//   * exactly two qwords are written through `dest` ([rbx] and [rbx+0x8]).
//
// The IAT slot 0x1418233c0 is _invalid_parameter_noinfo. It is reached through an extern
// function-pointer seam, never as a hardcoded address. The prototype carries the three
// argument registers live at the call site (rcx == this == null, rdx == dest,
// r8 == owner); the CRT callee ignores them, and exposing them lets the test pin the
// exact call state.
// ============================================================================
#ifndef TQ_SYN_THUNKS_S_H
#define TQ_SYN_THUNKS_S_H

#include <cstdint>

namespace tq {

// _invalid_parameter_noinfo — the guard slot, shared by all 32 bodies
extern void (*g_fnS_1418233c0)(void* pThis, void* pDest, void* pOwner);

// — one body per pdata entry ------------------------------------------------------
inline void* SynStorePair_141728240(void* pThis, void* pDest, void* pOwner) {
    // 0x141728240 · 22 insns · jne 0x141728264 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417286b0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417286b0 · 22 insns · jne 0x1417286d4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141728700(void* pThis, void* pDest, void* pOwner) {
    // 0x141728700 · 22 insns · jne 0x141728724 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141729700(void* pThis, void* pDest, void* pOwner) {
    // 0x141729700 · 22 insns · jne 0x141729724 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141729b10(void* pThis, void* pDest, void* pOwner) {
    // 0x141729b10 · 22 insns · jne 0x141729b34 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141729ee0(void* pThis, void* pDest, void* pOwner) {
    // 0x141729ee0 · 22 insns · jne 0x141729f04 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14173bef0(void* pThis, void* pDest, void* pOwner) {
    // 0x14173bef0 · 22 insns · jne 0x14173bf14 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14173c060(void* pThis, void* pDest, void* pOwner) {
    // 0x14173c060 · 22 insns · jne 0x14173c084 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417473b0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417473b0 · 22 insns · jne 0x1417473d4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141748790(void* pThis, void* pDest, void* pOwner) {
    // 0x141748790 · 22 insns · jne 0x1417487b4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141758000(void* pThis, void* pDest, void* pOwner) {
    // 0x141758000 · 22 insns · jne 0x141758024 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417591a0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417591a0 · 22 insns · jne 0x1417591c4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417595b0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417595b0 · 22 insns · jne 0x1417595d4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141759a40(void* pThis, void* pDest, void* pOwner) {
    // 0x141759a40 · 22 insns · jne 0x141759a64 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141759e50(void* pThis, void* pDest, void* pOwner) {
    // 0x141759e50 · 22 insns · jne 0x141759e74 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141759ea0(void* pThis, void* pDest, void* pOwner) {
    // 0x141759ea0 · 22 insns · jne 0x141759ec4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14175a2b0(void* pThis, void* pDest, void* pOwner) {
    // 0x14175a2b0 · 22 insns · jne 0x14175a2d4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14175a6c0(void* pThis, void* pDest, void* pOwner) {
    // 0x14175a6c0 · 22 insns · jne 0x14175a6e4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14175c9a0(void* pThis, void* pDest, void* pOwner) {
    // 0x14175c9a0 · 22 insns · jne 0x14175c9c4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14175d210(void* pThis, void* pDest, void* pOwner) {
    // 0x14175d210 · 22 insns · jne 0x14175d234 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141776c40(void* pThis, void* pDest, void* pOwner) {
    // 0x141776c40 · 22 insns · jne 0x141776c64 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14177aee0(void* pThis, void* pDest, void* pOwner) {
    // 0x14177aee0 · 22 insns · jne 0x14177af04 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14178ab20(void* pThis, void* pDest, void* pOwner) {
    // 0x14178ab20 · 22 insns · jne 0x14178ab44 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_14178b0f0(void* pThis, void* pDest, void* pOwner) {
    // 0x14178b0f0 · 22 insns · jne 0x14178b114 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141794860(void* pThis, void* pDest, void* pOwner) {
    // 0x141794860 · 22 insns · jne 0x141794884 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_141795190(void* pThis, void* pDest, void* pOwner) {
    // 0x141795190 · 22 insns · jne 0x1417951b4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417951e0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417951e0 · 22 insns · jne 0x141795204 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417a7950(void* pThis, void* pDest, void* pOwner) {
    // 0x1417a7950 · 22 insns · jne 0x1417a7974 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417c7be0(void* pThis, void* pDest, void* pOwner) {
    // 0x1417c7be0 · 22 insns · jne 0x1417c7c04 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417c8170(void* pThis, void* pDest, void* pOwner) {
    // 0x1417c8170 · 22 insns · jne 0x1417c8194 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417c9d90(void* pThis, void* pDest, void* pOwner) {
    // 0x1417c9d90 · 22 insns · jne 0x1417c9db4 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}
inline void* SynStorePair_1417ca220(void* pThis, void* pDest, void* pOwner) {
    // 0x1417ca220 · 22 insns · jne 0x1417ca244 -> insn 10 · slot 0x1418233c0
    void* pSrc = *(void**)((uint8_t*)pOwner + 0x8);   // 3: [r8+0x8], before the guard
    if (pThis == nullptr)
        g_fnS_1418233c0(pThis, pDest, pOwner);              // 9: rcx/rdx/r8 as they stand
    void* pTmp[2];                                    // [rsp+0x20] / [rsp+0x28]
    pTmp[1] = pSrc;                                   // 6: the spill (upper qword)
    pTmp[0] = *(void**)pThis;                         // 10/12: this[0] into the temp
    *(void**)pDest = pTmp[0];                         // 13/14: through rcx
    *(void**)((uint8_t*)pDest + 0x8) = pTmp[1];       // 15/16: owner[+0x8]
    return pDest;                                     // 17
}

}  // namespace tq

#endif
