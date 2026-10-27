#include "TitleQuery.h"
#include "TitleGrant.h"
#include <functional>

namespace title {

// ORIGINAL FUN_141971720 — the bit TEST (no clear/set)
bool HasTitleBit(STitleMaskRec* pRec, uint16_t uIdx) {
    if (pRec->m_pHolder08 != nullptr &&
        (uint16_t)(uIdx - 1) < 0x20) {
        uint32_t uMask = g_fnGetTitleMask(
            pRec->m_pHolder08, pRec->m_nId10);
        return ((uMask >>
                 (((uint8_t)(uint16_t)(char)uIdx) - 1 & 0x1f))
                & 1) != 0;
    }
    return false;
}

// ORIGINAL FUN_1419716a0 — the popcount loop with
// the VERBATIM rotate idiom u2 = (u2 << 1) | (u2 < 0)
int CountTitles(STitleMaskRec* pRec) {
    if (pRec->m_pHolder08 == nullptr) return 0;
    int n = 0;
    uint32_t uMask = g_fnGetTitleMask(
        pRec->m_pHolder08, pRec->m_nId10);
    uint32_t u2 = 1;
    int64_t c = 0x20;
    do {
        if (u2 == (uMask & u2)) ++n;   // equality test
        // VERBATIM: rotate-left through the sign bit
        u2 = (u2 << 1) | (uint32_t)((int32_t)u2 < 0);
        --c;
    } while (c != 0);
    return n;
}

// ORIGINAL FUN_141972130
bool MgrHasTitle(void* pMgr, int nTitleId, uint16_t uIdx) {
    if (nTitleId == 0) {
        g_fnLogError("DAT_141978310");  // the literal log
        return false;
    }
    STitleMaskRec* pRec =
        (STitleMaskRec*)g_fnMgrGetRecord(pMgr, nTitleId);
    if (pRec == nullptr) return false;
    return HasTitleBit(pRec, uIdx);
}

// ORIGINAL FUN_1419721a0
int MgrCountTitles(void* pMgr, int nTitleId) {
    if (nTitleId != 0) {
        STitleMaskRec* pRec =
            (STitleMaskRec*)g_fnMgrGetRecord(pMgr, nTitleId);
        if (pRec != nullptr) return CountTitles(pRec);
    }
    return 0;
}

// ORIGINAL FUN_1419721d0
void* GetMgrLink(void* pMgr) {
    return *(void**)((uint8_t*)pMgr + 0x48);
}

} // namespace
