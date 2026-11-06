// synthunks_gi.h — RAW Syndicate.dll v6159 · 22 container invariant probes (family GI).
// Reports through the same seam the iterators use, then returns the current value unchanged.
#ifndef TQ_SYN_THUNKS_GI_H
#define TQ_SYN_THUNKS_GI_H

#include <cstdint>

namespace tq {

extern void (*g_fnGI_1418233c0)(void* pArg);

inline void* SynProbe_141722a20(void* pThis) {   // 0x141722a20
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141722b40(void* pThis) {   // 0x141722b40
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141724690(void* pThis) {   // 0x141724690
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141724770(void* pThis) {   // 0x141724770
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_14174fb70(void* pThis) {   // 0x14174fb70
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_14174fc10(void* pThis) {   // 0x14174fc10
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141752560(void* pThis) {   // 0x141752560
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417525e0(void* pThis) {   // 0x1417525e0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417801b0(void* pThis) {   // 0x1417801b0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141780230(void* pThis) {   // 0x141780230
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141790620(void* pThis) {   // 0x141790620
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_141791c80(void* pThis) {   // 0x141791c80
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417a2b40(void* pThis) {   // 0x1417a2b40
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417a35f0(void* pThis) {   // 0x1417a35f0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b59e0(void* pThis) {   // 0x1417b59e0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b5ab0(void* pThis) {   // 0x1417b5ab0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b5b80(void* pThis) {   // 0x1417b5b80
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b9b70(void* pThis) {   // 0x1417b9b70
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b9c30(void* pThis) {   // 0x1417b9c30
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417b9cf0(void* pThis) {   // 0x1417b9cf0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417d1750(void* pThis) {   // 0x1417d1750
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}
inline void* SynProbe_1417d1df0(void* pThis) {   // 0x1417d1df0
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGI_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) >=
        *(void**)((uint8_t*)p + 0x20))                            // insn 11-13
        g_fnGI_1418233c0(pThis);                                         // insn 14
    return *(void**)((uint8_t*)pThis + 0x8);                     // insn 15
}

}  // namespace tq

#endif
