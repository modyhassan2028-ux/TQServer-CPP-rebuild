// synattrsend.cpp — see synattrsend.h
#include "modules/syndicate/src/synattrsend.h"

#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include "modules/syndicate/src/msg/cmsgbase.h"

#include <cstddef>
#include <cstring>

namespace tq {

uint32_t (*g_fnSynMsgPackerSize)(void*) = nullptr;
void (*g_fnSynAttrInsertCore)(void*, void*, void*, uint32_t, char) = nullptr;

namespace {

uint8_t* U8(void* p) { return (uint8_t*)p; }

void ReportCheck(const void* pExpr, int nLine) {
    // ORIGINAL, verbatim: call [0x141823030](&DAT_141824ca8, &DAT_14182664c, expr,
    //                                       &DAT_141839fe0, line)
    ::syndicate::g_fn_141823030((const char*)0x141824ca8ULL, (const void*)0x14182664cULL,
                                pExpr, (const void*)0x141839fe0ULL, nLine);
}

}  // namespace

// 0x1417db530 — the announce builder
bool SynMsgSyndicateAnnounce(void* pMsg, uint16_t uAction, uint32_t uParam, const char* pszText) {
    if (uAction == 0) {
        ReportCheck((const void*)0x0, 0x6b);
        return false;
    }
    if (pszText == nullptr) {
        ReportCheck((const void*)0x0, 0x6c);
        return false;
    }
    ::syndicate::CMsgBase::Init(pMsg);
    uint8_t* pHdr = *(uint8_t**)(U8(pMsg) + 0x408);
    *(uint16_t*)(pHdr + 4) = uAction;
    *(uint32_t*)(pHdr + 8) = uParam;
    void* pPacker = U8(pMsg) + 0x410;
    ::syndicate::g_fnM83AddString(pPacker, pszText);
    uint32_t uPackSize = g_fnSynMsgPackerSize(pPacker);
    *(uint16_t*)(pHdr + 0) = (uint16_t)(uPackSize + 0x1b);
    *(uint16_t*)(pHdr + 2) = 0x453;
    return true;
}

// 0x1417c6a60 — the attribute pointer entry: both arguments are guarded
void SynAttrInsertByUser(void* pOwner, void* pUser, void* pAttrInfo, char cAnnounce) {
    if (pUser == nullptr) {
        ReportCheck((const void*)0x141836e5cULL, 0x32a);
        return;
    }
    if (pAttrInfo == nullptr) {
        ReportCheck((const void*)0x141831610ULL, 0x32b);
        return;
    }
    uint32_t uId = ::syndicate::g_fnA84GetId(pAttrInfo);
    g_fnSynAttrInsertCore(pOwner, pUser, pAttrInfo, uId, cAnnounce);
}

// 0x1417c6b30 — the id entry: the object is looked up under the owner, no guard on the result
void SynAttrInsertById(void* pOwner, void* pUser, uint32_t uId, char cAnnounce) {
    if (pUser == nullptr) {
        ReportCheck((const void*)0x141836e5cULL, 0x339);
        return;
    }
    void* pObj = ::syndicate::g_fnA84FindUserById(*(void**)(U8(pOwner) + 0x90), uId);
    g_fnSynAttrInsertCore(pOwner, pUser, pObj, uId, cAnnounce);
}

}  // namespace tq
