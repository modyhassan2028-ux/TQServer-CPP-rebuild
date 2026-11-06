// synthunks_al.h — RAW Syndicate.dll v6159 · 24 sentinel-node allocator wrappers (family AL).
// The allocator gets the size in rcx; the body returns its pointer in rax unchanged. The null branch
// only skips the store at [rax] and is followed straight into the `lea rdx,[rax+8]` store, so a null
// return faults there exactly as the raw does.
#ifndef TQ_SYN_THUNKS_AL_H
#define TQ_SYN_THUNKS_AL_H

#include <cstdint>

namespace tq {

extern void* (*g_fnAL_1417f3166)(uint32_t uSize);

inline void* SynAllocNode_141726c90(void* pThis) {   // 0x141726c90
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141726cf0(void* pThis) {   // 0x141726cf0
    void* const pNode = g_fnAL_1417f3166(0x58);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x50) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x51) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141726d50(void* pThis) {   // 0x141726d50
    void* const pNode = g_fnAL_1417f3166(0x50);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x48) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x49) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141726db0(void* pThis) {   // 0x141726db0
    void* const pNode = g_fnAL_1417f3166(0x20);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x1c) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x1d) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141726ec0(void* pThis) {   // 0x141726ec0
    void* const pNode = g_fnAL_1417f3166(0x20);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x1a) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x1b) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_14173bc00(void* pThis) {   // 0x14173bc00
    void* const pNode = g_fnAL_1417f3166(0x68);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x60) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_14173bcb0(void* pThis) {   // 0x14173bcb0
    void* const pNode = g_fnAL_1417f3166(0x28);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x20) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x21) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141746a00(void* pThis) {   // 0x141746a00
    void* const pNode = g_fnAL_1417f3166(0x40);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x3c) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x3d) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141746a60(void* pThis) {   // 0x141746a60
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141755f90(void* pThis) {   // 0x141755f90
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x2c) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x2d) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141756200(void* pThis) {   // 0x141756200
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141756260(void* pThis) {   // 0x141756260
    void* const pNode = g_fnAL_1417f3166(0x60);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x58) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x59) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_1417562c0(void* pThis) {   // 0x1417562c0
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_1417563b0(void* pThis) {   // 0x1417563b0
    void* const pNode = g_fnAL_1417f3166(0x68);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x60) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141756410(void* pThis) {   // 0x141756410
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141756470(void* pThis) {   // 0x141756470
    void* const pNode = g_fnAL_1417f3166(0x68);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x60) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x61) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_1417564d0(void* pThis) {   // 0x1417564d0
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_1417565b0(void* pThis) {   // 0x1417565b0
    void* const pNode = g_fnAL_1417f3166(0x70);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x68) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x69) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141756610(void* pThis) {   // 0x141756610
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_141776670(void* pThis) {   // 0x141776670
    void* const pNode = g_fnAL_1417f3166(0x40);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x38) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x39) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_14177ace0(void* pThis) {   // 0x14177ace0
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_14178a6a0(void* pThis) {   // 0x14178a6a0
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_14178a700(void* pThis) {   // 0x14178a700
    void* const pNode = g_fnAL_1417f3166(0x50);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x48) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x49) = 0x0;                 // insn 22
    return pNode;                                                // rax
}
inline void* SynAllocNode_1417a76e0(void* pThis) {   // 0x1417a76e0
    void* const pNode = g_fnAL_1417f3166(0x30);                        // insn 2-3 (rcx = size)
    if (pNode != nullptr)                                        // insn 5-6
        *(void**)pNode = nullptr;                                // insn 7-8 (ecx = 0)
    if ((uint8_t*)pNode + 0x8 != nullptr)                       // insn 12-14
        *(void**)((uint8_t*)pNode + 0x8) = nullptr;             // insn 15
    if ((uint8_t*)pNode + 0x10 != nullptr)                       // insn 17-19
        *(void**)((uint8_t*)pNode + 0x10) = nullptr;             // insn 20
    *(uint8_t*)((uint8_t*)pNode + 0x28) = 0x1;                 // insn 21
    *(uint8_t*)((uint8_t*)pNode + 0x29) = 0x0;                 // insn 22
    return pNode;                                                // rax
}

}  // namespace tq

#endif
