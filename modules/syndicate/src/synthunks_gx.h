// synthunks_gx.h — RAW Syndicate.dll v6159 · 86 container invariant probes (family GX).
// The report fires when the raw's own conditional is not taken; each body keeps its own mnemonic.
#ifndef TQ_SYN_THUNKS_GX_H
#define TQ_SYN_THUNKS_GX_H

#include <cstdint>

namespace tq {

extern void (*g_fnGX_1418233c0)(void* pArg);

inline void* SynProbeGX_141722eb0(void* pThis) {   // 0x141722eb0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141722f80(void* pThis) {   // 0x141722f80  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141723050(void* pThis) {   // 0x141723050  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417231c0(void* pThis) {   // 0x1417231c0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141724a60(void* pThis) {   // 0x141724a60  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141724aa0(void* pThis) {   // 0x141724aa0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141724b00(void* pThis) {   // 0x141724b00  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141724b60(void* pThis) {   // 0x141724b60  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141724bf0(void* pThis) {   // 0x141724bf0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141725f10(void* pThis) {   // 0x141725f10  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141725f50(void* pThis) {   // 0x141725f50  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141725fe0(void* pThis) {   // 0x141725fe0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141726070(void* pThis) {   // 0x141726070  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417260d0(void* pThis) {   // 0x1417260d0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173ae00(void* pThis) {   // 0x14173ae00  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173af50(void* pThis) {   // 0x14173af50  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173b5c0(void* pThis) {   // 0x14173b5c0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173b620(void* pThis) {   // 0x14173b620  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173ba50(void* pThis) {   // 0x14173ba50  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14173ba90(void* pThis) {   // 0x14173ba90  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141744750(void* pThis) {   // 0x141744750  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141744790(void* pThis) {   // 0x141744790  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141745b50(void* pThis) {   // 0x141745b50  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141745b90(void* pThis) {   // 0x141745b90  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141746520(void* pThis) {   // 0x141746520  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141746560(void* pThis) {   // 0x141746560  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750450(void* pThis) {   // 0x141750450  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417504d0(void* pThis) {   // 0x1417504d0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750570(void* pThis) {   // 0x141750570  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417505b0(void* pThis) {   // 0x1417505b0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417505f0(void* pThis) {   // 0x1417505f0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750630(void* pThis) {   // 0x141750630  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750720(void* pThis) {   // 0x141750720  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417507f0(void* pThis) {   // 0x1417507f0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750830(void* pThis) {   // 0x141750830  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141750870(void* pThis) {   // 0x141750870  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752900(void* pThis) {   // 0x141752900  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752940(void* pThis) {   // 0x141752940  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752980(void* pThis) {   // 0x141752980  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417529c0(void* pThis) {   // 0x1417529c0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752a00(void* pThis) {   // 0x141752a00  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752a40(void* pThis) {   // 0x141752a40  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752b40(void* pThis) {   // 0x141752b40  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752ba0(void* pThis) {   // 0x141752ba0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752be0(void* pThis) {   // 0x141752be0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141752c20(void* pThis) {   // 0x141752c20  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755070(void* pThis) {   // 0x141755070  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417550b0(void* pThis) {   // 0x1417550b0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755110(void* pThis) {   // 0x141755110  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755150(void* pThis) {   // 0x141755150  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755190(void* pThis) {   // 0x141755190  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417551d0(void* pThis) {   // 0x1417551d0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755210(void* pThis) {   // 0x141755210  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755250(void* pThis) {   // 0x141755250  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141755290(void* pThis) {   // 0x141755290  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417552d0(void* pThis) {   // 0x1417552d0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141775ff0(void* pThis) {   // 0x141775ff0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417762c0(void* pThis) {   // 0x1417762c0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141776580(void* pThis) {   // 0x141776580  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14177a580(void* pThis) {   // 0x14177a580  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14177a8e0(void* pThis) {   // 0x14177a8e0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14177ab00(void* pThis) {   // 0x14177ab00  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141789d30(void* pThis) {   // 0x141789d30  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141789e00(void* pThis) {   // 0x141789e00  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14178a300(void* pThis) {   // 0x14178a300  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14178a360(void* pThis) {   // 0x14178a360  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14178a3e0(void* pThis) {   // 0x14178a3e0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_14178a940(void* pThis) {   // 0x14178a940  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141791e20(void* pThis) {   // 0x141791e20  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141791e60(void* pThis) {   // 0x141791e60  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141791ea0(void* pThis) {   // 0x141791ea0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141791ee0(void* pThis) {   // 0x141791ee0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141793000(void* pThis) {   // 0x141793000  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141793040(void* pThis) {   // 0x141793040  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141793080(void* pThis) {   // 0x141793080  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417930c0(void* pThis) {   // 0x1417930c0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417932f0(void* pThis) {   // 0x1417932f0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_141794320(void* pThis) {   // 0x141794320  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417a7070(void* pThis) {   // 0x1417a7070  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417a73a0(void* pThis) {   // 0x1417a73a0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417a7530(void* pThis) {   // 0x1417a7530  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417c7320(void* pThis) {   // 0x1417c7320  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417c78e0(void* pThis) {   // 0x1417c78e0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417c7930(void* pThis) {   // 0x1417c7930  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417c7ae0(void* pThis) {   // 0x1417c7ae0  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}
inline void* SynProbeGX_1417c9060(void* pThis) {   // 0x1417c9060  (jne: the current value equals the limit)
    if (*(void**)pThis == nullptr)                                 // insn 2-5
        g_fnGX_1418233c0(pThis);                                         // insn 6
    void* p = *(void**)pThis;                                     // insn 7 (re-read)
    if (p != nullptr)                                             // insn 8-9
        p = *(void**)p;                                           // insn 10
    if (*(void**)((uint8_t*)pThis + 0x8) ==
        *(void**)((uint8_t*)p + 0x30))                            // insn 11-13
        g_fnGX_1418233c0(pThis);                                         // insn 14
    return (uint8_t*)*(void**)((uint8_t*)pThis + 0x8) + 0x18;                          // insn 15-16
}

}  // namespace tq

#endif
