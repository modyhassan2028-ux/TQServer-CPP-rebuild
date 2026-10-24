#include "MsgKernelSlots.h"

namespace msg {

// ===== ORIGINAL FUN_1400084e0 @ 1400084e0 =====
// if ((0xd < idx) && (idx < count)) return 1;
// return 0;
// (LITERAL: slots 0..13 are INVALID - the gate
//  is the bare comparison, no comment in the
//  binary explains why)
uint8_t MsgKernelIdxValid(MsgKernelSlots& rS,
                          uint32_t dwIdx) {
    if (0xd < dwIdx && dwIdx < rS.Count())
        return 1;
    return 0;
}

// ===== ORIGINAL FUN_140008520 @ 140008520 =====
// iVar1 = FUN_1400084e0(idx);
// if (iVar1 == 0) { log_InlineLogERROR(DAT_1406d9c10);
//   return 0; }
// if (count <= idx) { _invalid_parameter_noinfo(); }
// return DAT_140975c20 + idx * 0x850;
uint8_t* MsgKernelGetSlot(MsgKernelSlots& rS,
                          uint32_t dwIdx) {
    if (MsgKernelIdxValid(rS, dwIdx) == 0) {
        rS.m_fnLogError();      // &DAT_1406d9c10
        return nullptr;
    }
    if (rS.Count() <= (uint64_t)dwIdx)
        rS.m_fnInvalidParam(); // CRT abort
    return rS.pBegin + (uint64_t)dwIdx * 0x850;
}

// ===== ORIGINAL FUN_140006fe0 @ 140006fe0 =====
// if (count <= idx) { _invalid_parameter_noinfo(); }
// return *(obj+0x18) + idx * 0x850;
// NOTE: NO 0xd gate here - this variant trusts the
// caller's index (used by the internal walkers)
uint8_t* MsgKernelGetSlotMember(void* pObj,
                                uint32_t dwIdx,
                                std::function<void()>
                                    fnInvalidParam) {
    uint8_t** ppBegin = (uint8_t**)pObj;   // +0x18
    uint8_t** ppEnd = (uint8_t**)pObj + 1; // +0x20
    if ((uint64_t)((*ppEnd - *ppBegin) / 0x850) <=
        (uint64_t)dwIdx)
        fnInvalidParam();
    return *ppBegin + (uint64_t)dwIdx * 0x850;
}

} // namespace msg
