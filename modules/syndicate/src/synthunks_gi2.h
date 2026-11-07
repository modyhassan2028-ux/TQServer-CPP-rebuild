// Generated with tools/bulk/gen_gi2.py - the invariant probe that advances the stored value.
#ifndef TQ_SYNTHUNKS_GI2_H
#define TQ_SYNTHUNKS_GI2_H

#include <cstdint>
#include <cstddef>

namespace tq {

#define GI2_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))

extern void (*g_fnGI2_1418233c0)(void*);

inline void* SynProbeGX_141722a60(void* pThis) {   // 0x141722a60  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_141722b80(void* pThis) {   // 0x141722b80  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417246d0(void* pThis) {   // 0x1417246d0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417247b0(void* pThis) {   // 0x1417247b0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_14174fbb0(void* pThis) {   // 0x14174fbb0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_14174fc50(void* pThis) {   // 0x14174fc50  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417525a0(void* pThis) {   // 0x1417525a0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_141752620(void* pThis) {   // 0x141752620  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417801f0(void* pThis) {   // 0x1417801f0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_141780270(void* pThis) {   // 0x141780270  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_141790660(void* pThis) {   // 0x141790660  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_141791cc0(void* pThis) {   // 0x141791cc0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417a2b80(void* pThis) {   // 0x1417a2b80  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417a3630(void* pThis) {   // 0x1417a3630  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b5a20(void* pThis) {   // 0x1417b5a20  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b5af0(void* pThis) {   // 0x1417b5af0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b5bc0(void* pThis) {   // 0x1417b5bc0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b9bb0(void* pThis) {   // 0x1417b9bb0  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b9c70(void* pThis) {   // 0x1417b9c70  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417b9d30(void* pThis) {   // 0x1417b9d30  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417d1790(void* pThis) {   // 0x1417d1790  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

inline void* SynProbeGX_1417d1e30(void* pThis) {   // 0x1417d1e30  (jb: the current value is at or above the limit)
    if (GI2_Q(pThis, 0x0) == nullptr)                          // insn 2-5
        g_fnGI2_1418233c0(pThis);                                       // insn 6
    void* p = GI2_Q(pThis, 0x0);                                 // insn 7 (re-read)
    if (p != nullptr)                                           // insn 8-9
        p = GI2_Q(p, 0x0);                                     // insn 10
    if (GI2_Q(pThis, 0x8) >=                              // insn 11-13
        GI2_Q(p, 0x20))
        g_fnGI2_1418233c0(pThis);                                       // insn 14
    *(uint64_t*)((uint8_t*)pThis + 0x8) += 0x8;               // insn 16
    return pThis;                                              // insn 15
}

}  // namespace tq

#undef GI2_Q

#endif