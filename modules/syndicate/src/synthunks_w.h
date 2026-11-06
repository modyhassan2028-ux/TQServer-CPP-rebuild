// synthunks_w.h — RAW Syndicate.dll v6159 · 33 ranged-insert bodies (family W).
// Element count = (pEnd - pBegin) >> shift, byte span = count * size, and the call receives
// (pBase, span, pBegin, span) exactly as the register setup does. The skip branch was verified
// onto the `mov rax,rbx` epilogue.
#ifndef TQ_SYN_THUNKS_W_H
#define TQ_SYN_THUNKS_W_H

#include <cstdint>

namespace tq {

extern void* (*g_fnW_1418232a8)(void* a, void* b, void* c, void* d);

inline void* SynRng_1417243e0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417243e0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141724480(void* pBegin, void* pEnd, void* pBase) {   // 0x141724480
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141725c20(void* pBegin, void* pEnd, void* pBase) {   // 0x141725c20
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141725c70(void* pBegin, void* pEnd, void* pBase) {   // 0x141725c70
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141727380(void* pBegin, void* pEnd, void* pBase) {   // 0x141727380
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141727450(void* pBegin, void* pEnd, void* pBase) {   // 0x141727450
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417400d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417400d0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417404d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417404d0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141740860(void* pBegin, void* pEnd, void* pBase) {   // 0x141740860
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417452a0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417452a0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141746130(void* pBegin, void* pEnd, void* pBase) {   // 0x141746130
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141746440(void* pBegin, void* pEnd, void* pBase) {   // 0x141746440
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 2;
    uint64_t nSpan = (uint64_t)n * 4;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141746d00(void* pBegin, void* pEnd, void* pBase) {   // 0x141746d00
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141752100(void* pBegin, void* pEnd, void* pBase) {   // 0x141752100
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141754a00(void* pBegin, void* pEnd, void* pBase) {   // 0x141754a00
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141754d30(void* pBegin, void* pEnd, void* pBase) {   // 0x141754d30
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141756d50(void* pBegin, void* pEnd, void* pBase) {   // 0x141756d50
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141778840(void* pBegin, void* pEnd, void* pBase) {   // 0x141778840
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141791660(void* pBegin, void* pEnd, void* pBase) {   // 0x141791660
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141792840(void* pBegin, void* pEnd, void* pBase) {   // 0x141792840
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141792aa0(void* pBegin, void* pEnd, void* pBase) {   // 0x141792aa0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_141793980(void* pBegin, void* pEnd, void* pBase) {   // 0x141793980
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a3190(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3190
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a31d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a31d0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a3860(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3860
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a38a0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a38a0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a3b90(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3b90
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a3fe0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a3fe0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417a4050(void* pBegin, void* pEnd, void* pBase) {   // 0x1417a4050
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417d1b40(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d1b40
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417d1fa0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d1fa0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417d21f0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d21f0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}
inline void* SynRng_1417d24d0(void* pBegin, void* pEnd, void* pBase) {   // 0x1417d24d0
    int64_t n = ((int64_t)(uintptr_t)pEnd - (int64_t)(uintptr_t)pBegin) >> 3;
    uint64_t nSpan = (uint64_t)n * 8;
    void* pDst = (void*)((uint8_t*)pBase - nSpan);
    if (!(n > 0)) return pDst;          // jle skips the call
    g_fnW_1418232a8(pDst, (void*)(uintptr_t)nSpan, pBegin, (void*)(uintptr_t)nSpan);
    return pDst;
}

}  // namespace tq

#endif
