#include "MsgHashCtor.h"
#include "MsgHashEnd.h"
#include <cassert>
#include <cstddef>

namespace msg {

static_assert(sizeof(SHashContainer) >= 0x8c,
    "hash container size");
#define HOFF(x, o) \
    static_assert(offsetof(SHashContainer, x) == o, \
        #x " @ " #o)
HOFF(m_wOwner,   0x08);
HOFF(m_pProxy,   0x10);
HOFF(m_pEnd,     0x38);
HOFF(m_qSize,    0x40);
HOFF(m_vec,      0x48);
HOFF(m_qMask,    0x78);
HOFF(m_qBuckets, 0x80);
HOFF(m_fMaxLoad, 0x88);

// ===== M71b: ORIGINAL FUN_1400103b0 VERBATIM =====
// (the Ghidra-dropped tail `return param_1` documented)
void HashCtorInit(SHashContainer* pC,
                  const uint16_t* pOwner) {
    uint8_t* pB = (uint8_t*)pC;
    // *(param_1 + 8) = *param_2 (the 2-byte copy)
    *(uint16_t*)(pB + 8) = *pOwner;
    // the LIST proxy: new(8) node, value = &the slot
    void** pSlot = (void**)(pB + 0x10);
    void* pProxy = operator new(8);
    if (pProxy != nullptr) {
        *(void**)pProxy = pSlot;
    }
    *pSlot = pProxy;
    // END via FUN_140009f20 (M71a), stored at +0x38
    void* pEnd = HashEndCreate();
    *(void**)(pB + 0x38) = pEnd;
    // size = 0
    *(uint64_t*)(pB + 0x40) = 0;
    // the VECTOR proxy at +0x48 (same new(8) pattern)
    SVec* pV = (SVec*)(pB + 0x48);
    void* pVProxy = operator new(8);
    if (pVProxy != nullptr) {
        *(void**)pVProxy = pV;
    }
    pV->m_q0 = (uint64_t)pVProxy;
    pV->m_pFirst = nullptr;
    pV->m_pLast  = nullptr;
    pV->m_pCap   = nullptr;
    // max_load = 0x40800000 = 4.0f VERBATIM
    *(uint32_t*)(pB + 0x88) = 0x40800000u;
    // the fill pair {local_30 = the proxy, local_28
    // = END}: plVar6 = *(the proxy) = the slot addr;
    // local_30 = *plVar6 = the proxy (the ORIGINAL
    // leaves plVar6 uninitialized in the impossible
    // null branch - defaulted here, documented)
    void* plVar6 = pSlot;
    if (*pSlot != nullptr) {
        plVar6 = *(void**)*pSlot;   // = the slot addr
    }
    uint64_t pair[2];
    pair[0] = *(uint64_t*)plVar6;    // the proxy
    pair[1] = (uint64_t)pEnd;       // END
    // f4a0(vec, 9, pair): 9 bucket entries
    VecClearRefill(pV, 9, pair);
    *(uint64_t*)(pB + 0x78) = 7;    // mask
    *(uint64_t*)(pB + 0x80) = 8;    // bucket count
}

// ===== M71b: ORIGINAL FUN_140010310 VERBATIM =====
// the RESET: empty the list, destroy every node,
// rebuild the bucket array
void HashReset(SHashContainer* pC) {
    uint8_t* pB = (uint8_t*)pC;
    void* pEnd = *(void**)(pB + 0x38);
    void* pOld = *(void**)pEnd;          // END->next
    *(void**)pEnd = pEnd;                // END->next
    *(void**)((char*)pEnd + 8) = pEnd;   // END->prev
    *(uint64_t*)(pB + 0x40) = 0;         // size = 0
    // destroy every old node (->next walk to END)
    if (pOld != pEnd) {
        void* p = pOld;
        void* pNext = nullptr;
        do {
            pNext = *(void**)p;
            operator delete(p);
            p = pNext;
        } while (pNext != pEnd);
    }
    // the fill pair {local_18 = the proxy, local_10
    // = END}: puVar3 = *(the proxy) = the slot
    // addr; local_18 = *puVar3 = the proxy
    uint64_t pair[2];
    pair[1] = (uint64_t)pEnd;
    pair[0] = 0;
    void* puVar3 = nullptr;
    if (*(void**)(pB + 0x10) != nullptr) {
        puVar3 = *(void**)*(void**)(pB + 0x10);
    }
    // (the impossible-null branch leaves puVar3 = 0
    // in the ORIGINAL - guarded, documented)
    pair[0] = puVar3 ?
        *(uint64_t*)puVar3 : 0;          // the proxy
    VecClearRefill((SVec*)(pB + 0x48), 9,
                   pair);
    *(uint64_t*)(pB + 0x78) = 7;
    *(uint64_t*)(pB + 0x80) = 8;
}

} // namespace msg
