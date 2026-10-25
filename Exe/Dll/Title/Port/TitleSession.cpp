#include "TitleSession.h"
#include "TitleModule.h"
#include "TitleGrant.h"
#include "TitleRemove.h"
#include "TitleQuery.h"
#include <cstring>

namespace title {

std::function<bool(CMsgBase*, const char*, uint16_t)>
    g_fnCMsgCreate = [](CMsgBase*, const char*, uint16_t) {
        return false; };

// ORIGINAL FUN_141974c30 — Create + the 0x3ea check
bool CMsgLoginCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen) {
    if (!g_fnCMsgCreate(pMsg, pBuf, uLen)) return false;
    // ORIGINAL: *(short*)(param_1 + 10) — CMsg* + 10
    // elements = +0x50 bytes (data + 0x10)
    return *(int16_t*)((uint8_t*)pMsg + 0x50) == 0x3ea;
}

// ORIGINAL FUN_141974c60 — the login chain
void CMsgLoginProcess(CMsgBase* pMsg, int nUserId) {
    if (nUserId == 0) {
        g_fnLogError("DAT_141978310");
        return;
    }
    // the mgr singleton (1419749f0)
    CTitleMgr* pMgr = GetTitleMgr();
    if (pMgr == nullptr) {
        g_fnLogError("DAT_141978310");
        return;
    }
    // FUN_1419721d0: the +0x48 link
    void* pLink = GetMgrLink(pMgr);
    if (pLink == nullptr) {
        g_fnLogError("DAT_141978310");
        return;
    }
    // mgr vt+0x28(id) -> the record
    STitleMaskRec* pRec =
        (STitleMaskRec*)g_fnMgrGetRecord(pMgr);
    if (pRec == nullptr) {
        g_fnLogError("DAT_141978310");
        return;
    }
    // the stack CMsgTitle (FUN_141975030)
    CMsgBase msg;
    memset(&msg, 0xAB, sizeof(msg));
    CtorMsgTitle(&msg);
    // link vt+0x10(id) -> the cur idx (byte)
    uint8_t uIdx = (uint8_t)g_fnLinkGetCurIdx(pLink, nUserId);
    if (!CMsgTitleBuild(&msg, '\x03', nUserId, uIdx)) {
        CMsgTitleDestroy(&msg);
        return;
    }
    // the VERBATIM SECOND vt+0x10 call
    int nCur = (int)g_fnLinkGetCurIdx(pLink, nUserId);
    if (nCur == 0) {
        g_fnLinkSendTitle(pLink, nUserId, &msg);   // vt+0x28
    } else {
        g_fnLinkBroadcast(pLink, nUserId, &msg);  // vt+0x38
    }
    CMsgTitleDestroy(&msg);
}

// ORIGINAL FUN_141974e00 — deleting dtor
void CMsgLoginDtorDel(CMsgBase* pMsg, uint8_t uFlags) {
    pMsg->m_pVftable = (void*)"title::CMsgLogin::vftable";
    pMsg->m_pVftable = (void*)"tq::CMsg::vftable";
    if ((uFlags & 1) != 0) g_fnFree(pMsg);
}

// ORIGINAL FUN_141974f10 — Create + the 0x3eb check
bool CMsgLogoutCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen) {
    if (!g_fnCMsgCreate(pMsg, pBuf, uLen)) return false;
    return *(int16_t*)((uint8_t*)pMsg + 0x50) == 0x3eb;
}

// ORIGINAL FUN_141974f40 — mgr vt+0x30
void CMsgLogoutProcess(int nUserId) {
    if (nUserId == 0) {
        g_fnLogError("DAT_141978310");
        return;
    }
    CTitleMgr* pMgr = GetTitleMgr();
    if (pMgr == nullptr) {
        g_fnLogError("DAT_141978310");
        return;
    }
    g_fnMgrPostRemove(pMgr, nUserId);
}

// ORIGINAL FUN_141974ea0 — the vtable swap
void CMsgLogoutDtor(CMsgBase* pMsg) {
    pMsg->m_pVftable = (void*)"title::CMsgLogout::vftable";
    pMsg->m_pVftable = (void*)"tq::CMsg::vftable";
}

} // namespace
