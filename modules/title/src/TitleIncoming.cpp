#include "TitleIncoming.h"
#include "TitleModule.h"
#include "TitleGrant.h"
#include "TitleRemove.h"
#include "TitleQuery.h"
#include <cstring>
#include <cstdlib>

namespace title {

std::function<uint32_t()> g_fnTimeGet = []{ return 0u; };
std::function<const char*(const char*)> g_fnGetString =
    [](const char*){ return (const char*)0; };
std::function<void(void*, int, const char*, uint32_t, uint32_t)>
    g_fnLinkSendText = [](void*, int, const char*, uint32_t, uint32_t){};

// ORIGINAL FUN_1419716f0 — the +0x14 stamp read
uint32_t TitleEditStampGet(STitleMaskRec* pRec) {
    return pRec->m_nStamp14;
}

// ORIGINAL FUN_141971700 — the +0x14 stamp write
void TitleEditStampSet(STitleMaskRec* pRec) {
    pRec->m_nStamp14 = g_fnTimeGet();   // tq::TimeGet(0)
}

// ORIGINAL FUN_141975170
bool CMsgTitleCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen) {
    if (!g_fnCMsgCreate(pMsg, pBuf, uLen))   // CMsg::Create thunk
        return false;
    // *(short*)(msg + 10 elems) == 0x46a
    return *(short*)((uint8_t*)pMsg + 0x50) == 0x46a;
}

// ORIGINAL FUN_1419751a0 — the idx append
bool CMsgTitleAppendIdx(CMsgBase* pMsg, char cIdx) {
    uint8_t* pNode = (uint8_t*)pMsg->m_ppTail408;  // +0x408 field
    if (pNode != nullptr) {
        uint16_t uNew = (uint16_t)(pNode[10] + 0xc);
        if (uNew < 0x401) {
            // append at node + 0xb + count
            *(uint8_t*)((uintptr_t)pNode[10] + 0xb +
                        (uintptr_t)pNode) = (uint8_t)cIdx;
            pNode[10] = (uint8_t)(pNode[10] + 1);   // count++
            *(uint16_t*)pNode = uNew;               // size = 0xc+count
            return true;
        }
    }
    return false;   // the masked return
}

// ORIGINAL FUN_141975260 — the incoming process
void CMsgTitleProcess(CMsgBase* pMsg, int nId) {
    if (nId == 0) { g_fnLogError("DAT_141978310"); return; }
    CTitleMgr* pMgr = GetTitleMgr();
    if (pMgr == nullptr) { g_fnLogError("DAT_141978310"); return; }
    void* pLink = GetMgrLink(pMgr);
    if (pLink == nullptr) { g_fnLogError("DAT_141978310"); return; }
    STitleMaskRec* pRec =
        (STitleMaskRec*)g_fnMgrGetRecord(pMgr, nId);
    if (pRec == nullptr) { g_fnLogError("DAT_141978310"); return; }
    uint8_t* pNode = (uint8_t*)pMsg->m_ppTail408;
    char cAction = *(char*)(pNode + 9);
    if (cAction == '\x02') {
        // remove request: verify + clear
        if (HasTitleBit(pRec, (uint16_t)pNode[8]) && pNode[8] != 0) {
            if (!TitleMaskClearBit(pRec, (uint16_t)pNode[8])) {
                g_fnLogError("DAT_141978310");
            } else {
                // echo the ORIGINAL incoming msg back
                g_fnLinkSendTitle(pLink, nId, pMsg);
                uint32_t uCur = g_fnLinkGetCurIdx(pLink, nId);
                if (uCur == pNode[8]) {
                    g_fnLinkSetCurIdx(pLink, nId, 0);
                    if (CMsgTitleBuild(pMsg, '\x03', nId, 0))
                        g_fnLinkBroadcast(pLink, nId, pMsg);
                }
            }
        }
    } else if (cAction == '\x03') {
        // equip/unequip request
        uint32_t uCur = g_fnLinkGetCurIdx(pLink, nId);
        if (uCur != pNode[8]) {
            uint32_t uStamp = TitleEditStampGet(pRec);
            uint32_t uNow = g_fnTimeGet();
            if (uNow - uStamp < 5000) {
                // the string-manager literal + the color/param
                const char* psz = g_fnGetString("STR_TITLE_EDIT_TOOMANY");
                g_fnLinkSendText(pLink, nId, psz, 0xff0000, 0x7d5);
            } else if (pNode[8] == 0) {
                g_fnLinkSetCurIdx(pLink, nId, 0);
                if (CMsgTitleBuild(pMsg, '\x03', nId, 0))
                    g_fnLinkBroadcast(pLink, nId, pMsg);
            } else {
                if (HasTitleBit(pRec, (uint16_t)pNode[8])) {
                    g_fnLinkSetCurIdx(pLink, nId, pNode[8]);
                    TitleEditStampSet(pRec);
                    if (CMsgTitleBuild(pMsg, '\x03', nId,
                                       pNode[8]))
                        g_fnLinkBroadcast(pLink, nId, pMsg);
                }
            }
        }
    } else if (cAction == '\x04') {
        // the full-title query: build the answer with the mask
        CMsgBase local;
        memset(&local, 0, sizeof(local));
        CtorMsgTitle(&local);
        if (CMsgTitleBuild(&local, '\x04', nId, 0)) {
            for (uint32_t u = 1; u < 0x21; u++) {
                if (HasTitleBit(pRec, (uint16_t)u))
                    CMsgTitleAppendIdx(&local, (char)u);
            }
            // the local_30 artifact: the local msg's data
            // node (+0x408 field) + its count byte @+0xa
            uint8_t* pLocalNode = (uint8_t*)local.m_ppTail408;
            if (pLocalNode != nullptr && pLocalNode[10] != 0)
                g_fnLinkSendTitle(pLink, nId, &local);
        }
    }
}

} // namespace
