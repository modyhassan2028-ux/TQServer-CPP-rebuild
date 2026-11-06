// synthunks_nf.h — RAW Syndicate.dll v6159 · 2 tree-node factories (family NF).
// 0x20-byte node: three pointers, a 32-bit key read through a stack-passed pointer, a flag byte and
// the nil marker cleared. A null allocation returns null and stores nothing.
#ifndef TQ_SYN_THUNKS_NF_H
#define TQ_SYN_THUNKS_NF_H

#include <cstdint>

namespace tq {

extern void* (*g_fnNF_1417f3166)(uint32_t uSize);

inline void* SynMakeNode_1417264d0(void* pThis, void* a2, void* a3, void* a4,
                                 const uint32_t* pKey, uint8_t bFlag) {   // 0x1417264d0
    void* const pNode = g_fnNF_1417f3166(0x20);                          // insn 8-9
    if (pNode == nullptr)                                         // insn 13-14
        return nullptr;                                           // rax is still the null
    *(void**)pNode = a2;                                          // insn 15
    *(void**)((uint8_t*)pNode + 0x8) = a3;                        // insn 16
    *(void**)((uint8_t*)pNode + 0x10) = a4;                       // insn 17
    *(uint32_t*)((uint8_t*)pNode + 0x18) = *pKey;                 // insn 18-20
    *(uint8_t*)((uint8_t*)pNode + 0x1c) = bFlag;                  // insn 21-22
    *(uint8_t*)((uint8_t*)pNode + 0x1d) = 0x0;                    // insn 23
    return pNode;                                                 // insn 24
}
inline void* SynMakeNode_141726e10(void* pThis, void* a2, void* a3, void* a4,
                                 const uint32_t* pKey, uint8_t bFlag) {   // 0x141726e10
    void* const pNode = g_fnNF_1417f3166(0x20);                          // insn 8-9
    if (pNode == nullptr)                                         // insn 13-14
        return nullptr;                                           // rax is still the null
    *(void**)pNode = a2;                                          // insn 15
    *(void**)((uint8_t*)pNode + 0x8) = a3;                        // insn 16
    *(void**)((uint8_t*)pNode + 0x10) = a4;                       // insn 17
    *(uint32_t*)((uint8_t*)pNode + 0x18) = *pKey;                 // insn 18-20
    *(uint8_t*)((uint8_t*)pNode + 0x1c) = bFlag;                  // insn 21-22
    *(uint8_t*)((uint8_t*)pNode + 0x1d) = 0x0;                    // insn 23
    return pNode;                                                 // insn 24
}

}  // namespace tq

#endif
