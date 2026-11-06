// synthunks_z.h — RAW Syndicate.dll v6159 · 26 validated range setters (family Z).
// *this = 0; then the guards: null source, source->lo > value, value > source->hi all report
// through the same slot; only a value inside [lo, hi] skips it. The copy that follows reads
// the source word unconditionally, exactly like the disassembly.
#ifndef TQ_SYN_THUNKS_Z_H
#define TQ_SYN_THUNKS_Z_H

#include <cstdint>

namespace tq {

extern void (*g_fnZ_1418233c0)(void* pThis, uint64_t nValue, void* pSrc);

inline void* SynRange_141726980(void* pThis, void* pValue, void* pSrc) {   // 0x141726980  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141726b30(void* pThis, void* pValue, void* pSrc) {   // 0x141726b30  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141727040(void* pThis, void* pValue, void* pSrc) {   // 0x141727040  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141727bd0(void* pThis, void* pValue, void* pSrc) {   // 0x141727bd0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141727cc0(void* pThis, void* pValue, void* pSrc) {   // 0x141727cc0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417281e0(void* pThis, void* pValue, void* pSrc) {   // 0x1417281e0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141740790(void* pThis, void* pValue, void* pSrc) {   // 0x141740790  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141740a40(void* pThis, void* pValue, void* pSrc) {   // 0x141740a40  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141746ad0(void* pThis, void* pValue, void* pSrc) {   // 0x141746ad0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141746b30(void* pThis, void* pValue, void* pSrc) {   // 0x141746b30  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141747920(void* pThis, void* pValue, void* pSrc) {   // 0x141747920  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141747980(void* pThis, void* pValue, void* pSrc) {   // 0x141747980  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141755c10(void* pThis, void* pValue, void* pSrc) {   // 0x141755c10  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141755da0(void* pThis, void* pValue, void* pSrc) {   // 0x141755da0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141757b90(void* pThis, void* pValue, void* pSrc) {   // 0x141757b90  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141757c50(void* pThis, void* pValue, void* pSrc) {   // 0x141757c50  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141782380(void* pThis, void* pValue, void* pSrc) {   // 0x141782380  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141782b30(void* pThis, void* pValue, void* pSrc) {   // 0x141782b30  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141793270(void* pThis, void* pValue, void* pSrc) {   // 0x141793270  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_141794570(void* pThis, void* pValue, void* pSrc) {   // 0x141794570  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417a3dc0(void* pThis, void* pValue, void* pSrc) {   // 0x1417a3dc0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417a3ed0(void* pThis, void* pValue, void* pSrc) {   // 0x1417a3ed0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417a47e0(void* pThis, void* pValue, void* pSrc) {   // 0x1417a47e0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417a4840(void* pThis, void* pValue, void* pSrc) {   // 0x1417a4840  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417d2400(void* pThis, void* pValue, void* pSrc) {   // 0x1417d2400  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}
inline void* SynRange_1417d28c0(void* pThis, void* pValue, void* pSrc) {   // 0x1417d28c0  frame 0x20
    const uint64_t nValue = (uint64_t)(uintptr_t)pValue;
    *(void**)pThis = nullptr;                                            // insn 7
    if (pSrc == nullptr                                                      // insn 8-9
        || *(const uint64_t*)((const uint8_t*)pSrc + 0x18) > nValue          // insn 10-11
        || nValue > *(const uint64_t*)((const uint8_t*)pSrc + 0x20))          // insn 12-13
        g_fnZ_1418233c0(pThis, nValue, pSrc);                                       // insn 14
    *(void**)((uint8_t*)pThis + 0x8) = pValue;                             // insn 17
    *(void**)pThis = *(void**)pSrc;                                        // insn 15,18
    return pThis;                                                           // insn 19
}

}  // namespace tq

#endif
