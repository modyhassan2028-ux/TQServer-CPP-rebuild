// ============================================================
// MsgServer strict port - unit M4
// ORIGINAL: the kernel slot registry
//  FUN_1400084e0 (validity) + FUN_140008520 (access)
//  + FUN_140006fe0 (the member-based variant)
// DAT_140975c20/c28 = the global begin/end pair of
// an array of 0x850-byte kernel slots (the worlds).
// QUIRK (LITERAL): FUN_1400084e0 requires
//  0xd < idx - the FIRST 14 SLOTS ARE INVALID
//  (indices 0..13 rejected); valid = 14..count-1.
// The failure path: log_InlineLogERROR(&DAT_1406d9c10)
//  and return 0; the second bounds miss calls
//  _invalid_parameter_noinfo (a CRT abort).
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgKernelSlots {
    // the globals DAT_140975c20 / DAT_140975c28
    uint8_t* pBegin = nullptr;
    uint8_t* pEnd = nullptr;
    // log_InlineLogERROR(&DAT_1406d9c10)
    std::function<void()> m_fnLogError;
    // _invalid_parameter_noinfo() (CRT abort)
    std::function<void()> m_fnInvalidParam;

    // (DAT_140975c28 - DAT_140975c20) / 0x850
    uint32_t Count() const {
        return (uint32_t)((pEnd - pBegin) / 0x850); }
};

// FUN_1400084e0: 1 iff 0xd < idx < count
uint8_t MsgKernelIdxValid(MsgKernelSlots& rS,
                          uint32_t dwIdx);
// FUN_140008520: the slot pointer (or 0 + error log)
uint8_t* MsgKernelGetSlot(MsgKernelSlots& rS,
                          uint32_t dwIdx);
// FUN_140006fe0: the member-variant on (obj+0x18/
//  +0x20) with NO 0xd gate - only the abort bound
uint8_t* MsgKernelGetSlotMember(void* pObj,
                                uint32_t dwIdx,
                                std::function<void()>
                                    fnInvalidParam);

} // namespace msg
