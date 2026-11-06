// synthunks_p.h - RAW Syndicate.dll v6159 - 54 `insert n copies` bodies (family P).
// Shape: n = (pEnd - pBegin) sar k, span = n * (1 << k), pDst = pBase + span.
// The slot is called as seam(pBase, span, pBegin, span): argument 1 is rcx <- r10, and
// r10 still holds the incoming third argument because `mov r8,rcx` overwrites r8 with
// pBegin only afterwards. pDst (rbx) is the return value, never an argument.
// The guard is preserved exactly: the `je` variants call for any non-zero n (negative
// included), the `jle` variants only for n > 0. Both land on the shared `mov rax,rbx`.
#ifndef TQ_SYN_THUNKS_P_H
#define TQ_SYN_THUNKS_P_H

#include <cstdint>
#include <cstring>

namespace tq {

extern void* (*g_fnP_1418232a8)(void* pDst, void* pSpan, void* pSrc, void* pSpan2);

// The raw 64-bit distance as a signed value, without an implementation-defined cast.
inline int64_t SynP_Signed(uint64_t u) { int64_t s; std::memcpy(&s, &u, sizeof s); return s; }
// `sar` is an arithmetic shift, so the sign bit is filled in.
inline int64_t SynP_Sar(int64_t v, unsigned k) {
    return v < 0 ? ~(~v >> k) : (v >> k);
}

inline void* SynInsN_1417241f0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417241f0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141724390(void* pBegin, void* pEnd, void* pBase) {   // 0x141724390
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141724440(void* pBegin, void* pEnd, void* pBase) {   // 0x141724440
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141724600(void* pBegin, void* pEnd, void* pBase) {   // 0x141724600
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141725bd0(void* pBegin, void* pEnd, void* pBase) {   // 0x141725bd0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141725d90(void* pBegin, void* pEnd, void* pBase) {   // 0x141725d90
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141725e30(void* pBegin, void* pEnd, void* pBase) {   // 0x141725e30
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417272d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417272d0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141727520(void* pBegin, void* pEnd, void* pBase) {   // 0x141727520
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417275d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417275d0
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141728ec0(void* pBegin, void* pEnd, void* pBase) {   // 0x141728ec0
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_14173ffd0(void* pBegin, void* pEnd, void* pBase) {   // 0x14173ffd0
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141740120(void* pBegin, void* pEnd, void* pBase) {   // 0x141740120
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141740540(void* pBegin, void* pEnd, void* pBase) {   // 0x141740540
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417407f0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417407f0
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141740900(void* pBegin, void* pEnd, void* pBase) {   // 0x141740900
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141740b50(void* pBegin, void* pEnd, void* pBase) {   // 0x141740b50
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141745120(void* pBegin, void* pEnd, void* pBase) {   // 0x141745120
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141745440(void* pBegin, void* pEnd, void* pBase) {   // 0x141745440
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417462d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417462d0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141746c30(void* pBegin, void* pEnd, void* pBase) {   // 0x141746c30
    // n = (int64)(pEnd - pBegin) sar 2; span = n * 4; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 2);
    const uint64_t span = (uint64_t)n * 4;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141746ef0(void* pBegin, void* pEnd, void* pBase) {   // 0x141746ef0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141747c40(void* pBegin, void* pEnd, void* pBase) {   // 0x141747c40
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141751f60(void* pBegin, void* pEnd, void* pBase) {   // 0x141751f60
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141752350(void* pBegin, void* pEnd, void* pBase) {   // 0x141752350
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141754b80(void* pBegin, void* pEnd, void* pBase) {   // 0x141754b80
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141756cb0(void* pBegin, void* pEnd, void* pBase) {   // 0x141756cb0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141756ec0(void* pBegin, void* pEnd, void* pBase) {   // 0x141756ec0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_14175af90(void* pBegin, void* pEnd, void* pBase) {   // 0x14175af90
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141791510(void* pBegin, void* pEnd, void* pBase) {   // 0x141791510
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141791610(void* pBegin, void* pEnd, void* pBase) {   // 0x141791610
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141791730(void* pBegin, void* pEnd, void* pBase) {   // 0x141791730
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141792910(void* pBegin, void* pEnd, void* pBase) {   // 0x141792910
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141793910(void* pBegin, void* pEnd, void* pBase) {   // 0x141793910
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_141793bb0(void* pBegin, void* pEnd, void* pBase) {   // 0x141793bb0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417959f0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417959f0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3030(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3030
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a30a0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a30a0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3300(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3300
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3340(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3340
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3970(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3970
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a39b0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a39b0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3f30(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3f30
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a3f70(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3f70
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a4100(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a4100
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a4140(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a4140
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a4900(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a4900
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417a4940(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a4940
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d1aa0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d1aa0
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d1c30(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d1c30
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d2040(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d2040
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d2460(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d2460
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // jle: only n > 0 calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n > 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d2550(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d2550
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}
inline void* SynInsN_1417d2950(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d2950
    // n = (int64)(pEnd - pBegin) sar 3; span = n * 8; pDst = pBase + span;
    // je: any non-zero n calls the slot; slot(pBase, span, pBegin, span); return pDst.
    const int64_t n = SynP_Sar(SynP_Signed((uint64_t)(uintptr_t)pEnd - (uint64_t)(uintptr_t)pBegin), 3);
    const uint64_t span = (uint64_t)n * 8;
    void* const pDst = (void*)((uintptr_t)pBase + (uintptr_t)span);
    if (n != 0) g_fnP_1418232a8(pBase, (void*)(uintptr_t)span, pBegin, (void*)(uintptr_t)span);
    return pDst;
}

}  // namespace tq

#endif
