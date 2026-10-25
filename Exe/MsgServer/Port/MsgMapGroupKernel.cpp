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
    // FUN_1400e50b0 default (when no seam injected):
    // new(0x80), first 3 qwords zeroed, @+0x78 = 1,
    // @+0x79 = 0 (before ef850 sets the 0x79 flag itself)
    if (!m_fnAllocJail)
        m_fnAllocJail = []{
            auto* p = (SInnerObj*)std::calloc(
                sizeof(SInnerObj), 1);
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
