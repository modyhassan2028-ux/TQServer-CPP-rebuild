// synthunks_q.h -- RAW Syndicate.dll v6159, 82 guarded container compares
// (family Q: 41 "==" bodies ending in `sete al`, 41 "!=" bodies ending in `setne al`).
//
// All 82 bodies are textually identical except for index 14 (sete/setne) and their address:
//     head = *(void**)this;                                  // insn 3: mov rax,[rcx]
//     if (!head)                        seam(this, other);  // insn 6-7: je -> the call
//     else if (head != *(void**)other)  seam(this, other);  // insn 8-9: cmp/je -> skip the call
//     return *(uint64_t*)(this+0x8) <op> *(uint64_t*)(other+0x8);
//
// Preserved quirks: the second word of `other` is loaded at insn 11, i.e. AFTER the seam
// returns, so a seam that rewrites other+0x8 is observed by the compare. The seam result
// in rax is discarded (insn 14 overwrites al), hence the void seam type. this+0x8 is
// reloaded at insn 13 as well. Nothing is stored: both bodies are pure compares.
//
// The call target is the single IAT slot [rip@0x1418233c0], modelled as an extern
// function-pointer seam, never as an absolute address.
#ifndef TQ_SYN_THUNKS_Q_H
#define TQ_SYN_THUNKS_Q_H

#include <cstdint>

namespace tq {

// IAT [rip@0x1418233c0]: rcx = this, rdx = other, rax discarded.
extern void (*g_fnQ_1418233c0)(void* pThis, void* pOther);

// 0x1417220d0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417220d0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141722110 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141722110(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141722160 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141722160(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417221a0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417221a0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417221e0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417221e0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141722220 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141722220(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417222b0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417222b0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417222f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417222f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141722330 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141722330(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141722860 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141722860(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141722aa0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141722aa0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141722bc0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141722bc0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141723680 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141723680(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141724650 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141724650(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141724710 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141724710(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417247f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417247f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14173ac60 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14173ac60(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14173aca0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14173aca0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14173ad10 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14173ad10(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14173b530 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14173b530(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14173feb0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14173feb0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141740450 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141740450(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141744310 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141744310(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141744350 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141744350(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417443a0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417443a0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417443e0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417443e0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f1a0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f1a0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f1e0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f1e0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f230 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f230(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f270 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f270(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f2b0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f2b0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f2f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f2f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f330 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f330(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f370 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f370(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f3b0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f3b0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f3f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f3f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f430 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f430(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f470 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f470(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f4b0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f4b0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f500 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f500(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f540 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f540(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f580 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f580(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f5c0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f5c0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174f600 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f600(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f670 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174f670(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14174f6b0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14174f6b0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14174fc90 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14174fc90(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141750bf0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141750bf0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141750d80 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141750d80(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141752660 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141752660(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141775ed0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141775ed0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141776260 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141776260(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x14177a4f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_14177a4f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x14177a810 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_14177a810(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417802f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417802f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141781c40 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141781c40(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141789560 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141789560(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417895d0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417895d0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141789c50 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141789c50(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141789c90 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141789c90(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417906a0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417906a0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417906e0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417906e0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141790720 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141790720(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141790760 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141790760(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417908f0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417908f0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141790960 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_141790960(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x141791d00 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141791d00(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x141791d40 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_141791d40(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417a2a50 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417a2a50(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417a2a90 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417a2a90(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417a2da0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417a2da0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417a3700 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417a3700(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417a6e20 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417a6e20(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417a6e60 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417a6e60(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417b5a60 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417b5a60(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417b5b30 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417b5b30(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417b5c00 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417b5c00(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417b9bf0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417b9bf0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417b9cb0 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417b9cb0(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417b9d70 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417b9d70(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}
// 0x1417d1800 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 == other+0x8) via `sete al`.
inline bool SynCmpEq_1417d1800(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) == qOther;   // insn 13-14
}
// 0x1417d1e70 -- guarded container compare: calls the seam when the head word is null or
//   differs from other's head, then answers (this+0x8 != other+0x8) via `setne al`.
inline bool SynCmpNe_1417d1e70(void* pThis, void* pOther) {
    void* pHead = *(void**)pThis;                             // insn 3-5
    if (pHead == nullptr || pHead != *(void**)pOther)        // insn 6-9
        g_fnQ_1418233c0(pThis, pOther);                             // insn 10
    uint64_t qOther = *(uint64_t*)((uint8_t*)pOther + 0x8); // insn 11-12
    return *(uint64_t*)((uint8_t*)pThis + 0x8) != qOther;   // insn 13-14
}

}  // namespace tq

#endif
