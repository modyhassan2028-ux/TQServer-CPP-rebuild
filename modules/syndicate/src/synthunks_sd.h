// synthunks_sd.h — RAW Syndicate.dll v6159 · 30 sentinel-node initialisers (family SD).
// The node is re-read from this->slot before each link store, exactly as the raw does it.
#ifndef TQ_SYN_THUNKS_SD_H
#define TQ_SYN_THUNKS_SD_H

#include <cstdint>

namespace tq {

extern void* (*g_fnSD_141726c30)(void* pThis);
extern void* (*g_fnSD_141726c90)(void* pThis);
extern void* (*g_fnSD_141726cf0)(void* pThis);
extern void* (*g_fnSD_141726d50)(void* pThis);
extern void* (*g_fnSD_141726db0)(void* pThis);
extern void* (*g_fnSD_141726ec0)(void* pThis);
extern void* (*g_fnSD_14173bc00)(void* pThis);
extern void* (*g_fnSD_14173bcb0)(void* pThis);
extern void* (*g_fnSD_141746a00)(void* pThis);
extern void* (*g_fnSD_141746a60)(void* pThis);
extern void* (*g_fnSD_141755f90)(void* pThis);
extern void* (*g_fnSD_141756200)(void* pThis);
extern void* (*g_fnSD_141756260)(void* pThis);
extern void* (*g_fnSD_1417562c0)(void* pThis);
extern void* (*g_fnSD_1417563b0)(void* pThis);
extern void* (*g_fnSD_141756410)(void* pThis);
extern void* (*g_fnSD_141756470)(void* pThis);
extern void* (*g_fnSD_1417564d0)(void* pThis);
extern void* (*g_fnSD_1417565b0)(void* pThis);
extern void* (*g_fnSD_141756610)(void* pThis);
extern void* (*g_fnSD_141776670)(void* pThis);
extern void* (*g_fnSD_14177ace0)(void* pThis);
extern void* (*g_fnSD_14178a6a0)(void* pThis);
extern void* (*g_fnSD_14178a700)(void* pThis);
extern void* (*g_fnSD_1417935d0)(void* pThis);
extern void* (*g_fnSD_141793680)(void* pThis);
extern void* (*g_fnSD_141793760)(void* pThis);
extern void* (*g_fnSD_1417a76e0)(void* pThis);
extern void* (*g_fnSD_1417c8590)(void* pThis);
extern void* (*g_fnSD_1417c8620)(void* pThis);

inline void SynSentinelInit_141727d20(void* pThis) {   // 0x141727d20
    void* const pNode = g_fnSD_141726c30(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x1d) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141727d60(void* pThis) {   // 0x141727d60
    void* const pNode = g_fnSD_141726c90(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141727da0(void* pThis) {   // 0x141727da0
    void* const pNode = g_fnSD_141726cf0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x51) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141727de0(void* pThis) {   // 0x141727de0
    void* const pNode = g_fnSD_141726d50(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x49) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141727e20(void* pThis) {   // 0x141727e20
    void* const pNode = g_fnSD_141726db0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x1d) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417281a0(void* pThis) {   // 0x1417281a0
    void* const pNode = g_fnSD_141726ec0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x1b) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_14173c020(void* pThis) {   // 0x14173c020
    void* const pNode = g_fnSD_14173bc00(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_14173c580(void* pThis) {   // 0x14173c580
    void* const pNode = g_fnSD_14173bcb0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x21) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417478a0(void* pThis) {   // 0x1417478a0
    void* const pNode = g_fnSD_141746a00(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x3d) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417478e0(void* pThis) {   // 0x1417478e0
    void* const pNode = g_fnSD_141746a60(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141757df0(void* pThis) {   // 0x141757df0
    void* const pNode = g_fnSD_141755f90(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x2d) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417584f0(void* pThis) {   // 0x1417584f0
    void* const pNode = g_fnSD_141756200(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758530(void* pThis) {   // 0x141758530
    void* const pNode = g_fnSD_141756260(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x59) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758590(void* pThis) {   // 0x141758590
    void* const pNode = g_fnSD_1417562c0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758910(void* pThis) {   // 0x141758910
    void* const pNode = g_fnSD_1417563b0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758950(void* pThis) {   // 0x141758950
    void* const pNode = g_fnSD_141756410(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758990(void* pThis) {   // 0x141758990
    void* const pNode = g_fnSD_141756470(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417589d0(void* pThis) {   // 0x1417589d0
    void* const pNode = g_fnSD_1417564d0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758d50(void* pThis) {   // 0x141758d50
    void* const pNode = g_fnSD_1417565b0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x69) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141758d90(void* pThis) {   // 0x141758d90
    void* const pNode = g_fnSD_141756610(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417768c0(void* pThis) {   // 0x1417768c0
    void* const pNode = g_fnSD_141776670(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x39) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_14177adf0(void* pThis) {   // 0x14177adf0
    void* const pNode = g_fnSD_14177ace0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_14178b090(void* pThis) {   // 0x14178b090
    void* const pNode = g_fnSD_14178a6a0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_14178b260(void* pThis) {   // 0x14178b260
    void* const pNode = g_fnSD_14178a700(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x49) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141794800(void* pThis) {   // 0x141794800
    void* const pNode = g_fnSD_1417935d0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141794dd0(void* pThis) {   // 0x141794dd0
    void* const pNode = g_fnSD_141793680(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x21) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_141795150(void* pThis) {   // 0x141795150
    void* const pNode = g_fnSD_141793760(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417a7860(void* pThis) {   // 0x1417a7860
    void* const pNode = g_fnSD_1417a76e0(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417c9cd0(void* pThis) {   // 0x1417c9cd0
    void* const pNode = g_fnSD_1417c8590(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x21) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}
inline void SynSentinelInit_1417c9d10(void* pThis) {   // 0x1417c9d10
    void* const pNode = g_fnSD_1417c8620(pThis);                        // insn 3 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pNode;                  // insn 4
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x1;                 // insn 5
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x8) =      // insn 6-7
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)*(void**)((uint8_t*)pThis + 0x30) =               // insn 8-9
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)*(void**)((uint8_t*)pThis + 0x30) + 0x10) =      // insn 10-11
        *(void**)((uint8_t*)pThis + 0x30);
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;           // insn 12
}

}  // namespace tq

#endif
