#include "TitleRemove.h"
#include "TitleGrant.h"
#include "TitleModule.h"
#include <cstring>

namespace title {

std::function<uint32_t(void*, int, CMsgBase*)>
    g_fnLinkSendTitle = [](void*, int, CMsgBase*) -> uint32_t { return 0; };
std::function<uint32_t(void*, int)>
    g_fnLinkGetCurIdx = [](void*, int) -> uint32_t { return 0; };
std::function<void(void*, int, int)>
    g_fnLinkSetCurIdx = [](void*, int, int) {};
std::function<char(void*, int)>
    g_fnLinkHasTitle = [](void*, int) -> char { return 0; };
std::function<uint32_t(void*, int, CMsgBase*)>
    g_fnLinkBroadcast = [](void*, int, CMsgBase*) -> uint32_t { return 0; };
std::function<void(void*, int)>
    g_fnMgrPostRemove = [](void*, int) {};

// ============================================================
// ORIGINAL FUN_141971620 — the check-and-CLEAR bit twin
// (record, idx): window 1..0x20; if the bit is CLEAR ->
// the masked false; else CLEAR it via vt+8 and return 1
// ============================================================
bool TitleMaskClearBit(STitleMaskRec* pRec, short sIdx) {
    // ORIGINAL: *(longlong*)(rec + 8) != 0
    if (pRec->m_pHolder08 != nullptr) {
        uint32_t u = (uint32_t)((int)sIdx - 1);
        if ((uint16_t)u < 0x20) {          // (ushort)u < 0x20
            uint32_t uBit =
                1u << (((uint32_t)(uint8_t)sIdx) - 1u & 0x1f);
            uint32_t uMask = g_fnGetTitleMask(
                pRec->m_pHolder08, pRec->m_nId10);
            if ((uBit & uMask) == 0) {
                // VERBATIM: return uMask & 0xff..00
                // (low byte 0 -> false)
                return false;
            }
            g_fnSetTitleMask(pRec->m_pHolder08, pRec->m_nId10,
                             ~uBit & uMask);
            return true;   // CONCAT71(..., 1)
        }
    }
    return false;           // the stale-register mask
}

// ============================================================
// ORIGINAL FUN_141971fe0 — the remove chain
// ============================================================
bool RemoveTitle(void* pMgr, int nTitleId, short sIdx) {
    uint8_t* pM = (uint8_t*)pMgr;
    // ORIGINAL: if (param_1[9] != 0) — mgr[9] = +0x48
    void* pLink = *(void**)(pM + 0x48);
    if (pLink == nullptr) return false;   // the stale reg

    if (nTitleId == 0) {
        g_fnLogError("DAT_141978310"); // the literal log
        return false;
    }
    // ORIGINAL: mgr vt+0x28 -> the record
    STitleMaskRec* pRec =
        (STitleMaskRec*)g_fnMgrGetRecord(pMgr);
    if (pRec == nullptr) return false;
    if (!TitleMaskClearBit(pRec, sIdx)) return false;

    // ORIGINAL: FUN_141975030 stack CMsgTitle ctor
    CMsgBase msg;
    memset(&msg, 0xAB, sizeof(msg));
    CtorMsgTitle(&msg);

    // action-2 remove msg, sent via the link vt+0x28
    bool bSent = false;
    if (CMsgTitleBuild(&msg, '\x02', nTitleId,
                       (uint8_t)sIdx)) {
        g_fnLinkSendTitle(pLink, nTitleId, &msg);
        bSent = true;
    }
    (void)bSent;   // ORIGINAL ignores the send result

    // the cur-idx follow-up: link vt+0x10(id)
    uint32_t uCur = g_fnLinkGetCurIdx(pLink, nTitleId);
    if (uCur == (uint32_t)sIdx) {
        g_fnLinkSetCurIdx(pLink, nTitleId, 0);
        if (CMsgTitleBuild(&msg, '\x03', nTitleId, 0)) {
            g_fnLinkBroadcast(pLink, nTitleId, &msg);
        }
    }
    // the post-remove: link vt+0x20 -> mgr vt+0x30
    char cHas = g_fnLinkHasTitle(pLink, nTitleId);
    if (cHas == '\0') {
        g_fnMgrPostRemove(pMgr, nTitleId);
    }
    CMsgTitleDestroy(&msg);   // FUN_141975080
    return true;               // CONCAT71(..., 1)
}

} // namespace
