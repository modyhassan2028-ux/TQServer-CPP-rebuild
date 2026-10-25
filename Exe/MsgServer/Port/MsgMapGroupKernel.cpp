#include "MsgMapGroupKernel.h"
#include <cstdlib>
namespace msg {
// the VERBATIM container init pattern (FUN_14000ef40 /
// FUN_1400ec260 / FUN_1400ef850 - identical except the inner
// allocator and the flag byte offset):
static void InitObjSet(SObjSet* pSet,
        std::function<SInnerObj*()>& fnAlloc,
        size_t nFlagByteOff) {  // BYTE offset
    // *param_1 = new(8){param_1}
    struct SHead { void* pOwner; };
    auto* pHead = (SHead*)std::malloc(sizeof(SHead));
    if (pHead) pHead->pOwner = pSet;
    pSet->m_pHead = pHead;
    // param_1[6] = <alloc>(param_1)
    SInnerObj* pInner = fnAlloc ? fnAlloc()
                               : (SInnerObj*)std::calloc(16,8);
    pSet->m_pInner = pInner;
    if (pInner) {
        // byte @inner+flagOffset = 1 (VERBATIM)
        *((uint8_t*)pInner + nFlagByteOff) = 1;
        // the tri-self-link @+0/+8/+0x10:
        pInner->m_q[1] = (uint64_t)pInner;  // +8
        pInner->m_q[0] = (uint64_t)pInner;  // +0
        pInner->m_q[2] = (uint64_t)pInner;  // +0x10
    }
    // param_1[7] = 0
    pSet->m_qCount = 0;
}
// ===== ORIGINAL FUN_1400f0000 @ 1400f0000 =====
CMapGroupKernel::CMapGroupKernel() {
    // +0x44 dword = 0 (implicit: zero-init members)
    // FUN_140009e80 (A sentinel): new(0x20), 3 qwords
    // zeroed, +0x1c = 1, +0x1d = 0 (ef40 raises 0x1d later)
    if (!m_fnAllocA)
        m_fnAllocA = [this]{
            m_vecAllocSizes.push_back(0x20);
            auto* p = (SInnerObj*)operator new(0x20);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x1c) = 1;
                *((uint8_t*)p + 0x1d) = 0;
            }
            return p; };
    // FUN_1400e4f40 (B sentinel): new(0x30), +0x28 = 1,
    // +0x29 = 0 (ec260 raises 0x29 later)
    if (!m_fnAllocB)
        m_fnAllocB = [this]{
            m_vecAllocSizes.push_back(0x30);
            auto* p = (SInnerObj*)operator new(0x30);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x28) = 1;
                *((uint8_t*)p + 0x29) = 0;
            }
            return p; };
    // FUN_1400e50b0 default (when no seam injected):
    // new(0x80), first 3 qwords zeroed, @+0x78 = 1,
    // @+0x79 = 0 (before ef850 sets the 0x79 flag itself)
    if (!m_fnAllocJail)
        m_fnAllocJail = [this]{
            m_vecAllocSizes.push_back(0x80);
            auto* p = (SInnerObj*)operator new(0x80);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x78) = 1;
                *((uint8_t*)p + 0x79) = 0;
            }
            return p; };
    // the 3 A/B pairs + the jail list, VERBATIM order:
    InitObjSet(&m_setA1,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB1,   m_fnAllocB,    0x29);
    InitObjSet(&m_setA2,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB2,   m_fnAllocB,    0x29);
    InitObjSet(&m_setA3,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB3,   m_fnAllocB,    0x29);
    InitObjSet(&m_setJail, m_fnAllocJail, 0x79);
}
} // namespace msg
