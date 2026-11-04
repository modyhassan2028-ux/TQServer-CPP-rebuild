// synattrsend.cpp — see synattrsend.h
#include "modules/syndicate/src/synattrsend.h"

#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/synuserattr.h"
#include "modules/syndicate/src/msg/cmsgbase.h"

#include <cstddef>
#include <cstring>

namespace tq {

uint32_t (*g_fnSynMsgPackerSize)(void*) = nullptr;
void (*g_fnSynAttrFillRec)(void*, void*) = nullptr;
bool (*g_fnSynAttrMsgInit)(void*, void*, void*) = nullptr;
void (*g_fnSynAttrInsertCore)(void*, void*, void*, uint32_t, char) = &SynAttrInsertCore;

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

// ============================================================================
// 0x1417c5640 — the shared insert core. The manager lives at owner + 0x88 and is driven
// through three vtable slots, in this order: 0x3f (compare the id), 1 (insert the
// attribute message), 0x1b (commit, ALWAYS, even when the insert was refused). The
// announce message goes out through the same slot 1 only when the caller asked for it.
// ============================================================================
namespace {

// the manager is driven by raw vtable arithmetic, exactly as the binary does it
uint32_t ManagerCompareId(void* pMgr, uint32_t uId) {
    typedef uint32_t (*Slot3fFn)(void*, uint32_t);
    return ((Slot3fFn)(*(void***)pMgr)[0x3f])(pMgr, uId);
}

void ManagerInsert(void* pMgr, uint32_t uId, void* pMsg) {
    typedef void (*Slot1Fn)(void*, uint32_t, void*);
    ((Slot1Fn)(*(void***)pMgr)[1])(pMgr, uId, pMsg);
}

void ManagerCommit(void* pMgr, uint32_t uId) {
    typedef void (*Slot1bFn)(void*, uint32_t);
    ((Slot1bFn)(*(void***)pMgr)[0x1b])(pMgr, uId);
}

}  // namespace

void SynAttrInsertCore(void* pOwner, void* pUser, void* pAttrInfo, uint32_t uId,
                       char cAnnounce) {
    if (pUser == nullptr) {
        // ORIGINAL line 0x348, the only path that skips every destructor
        ReportCheck((const void*)0x141836e5cULL, 0x348);
        return;
    }
    uint8_t aRec[0x28];
    std::memset(aRec, 0, sizeof(aRec));

    void* pMgr = *(void**)(U8(pOwner) + 0x88);
    uint32_t uCompare = ManagerCompareId(pMgr, uId);
    void* pActor = (uCompare == (uint32_t)SynUserAttrId(pUser)) ? pUser : nullptr;

    if (pAttrInfo != nullptr) g_fnSynAttrFillRec(pAttrInfo, aRec);

    // the 1088-byte attribute message
    uint8_t aAttrMsg[1088];
    std::memset(aAttrMsg, 0, sizeof(aAttrMsg));
    ::syndicate::CtorCMsgSynAttrInfo(aAttrMsg);
    if (g_fnSynAttrMsgInit(aAttrMsg, aRec, pActor)) {
        ManagerInsert(pMgr, uId, aAttrMsg);
    } else {
        ReportCheck((const void*)0x14183a0c8ULL, 0x35a);
    }
    ManagerCommit(pMgr, uId);          // unconditional, the refusal path reaches it too

    if (cAnnounce != 0) {
        // ORIGINAL: rbx = &DAT_141827409 — the image's empty string; a real "" stands in
        static const char kEmptyString[] = "";
        const char* pszAnnounce = kEmptyString;
        uint32_t uNumber = 0;
        if (pActor != nullptr) {
            pszAnnounce = SynUserAttrName(pActor);
            uNumber = (uint32_t)SynUserAttrNumber(pActor);
        }
        uint8_t aAnnMsg[1064];
        std::memset(aAnnMsg, 0, sizeof(aAnnMsg));
        ::syndicate::CtorCMsgSyndicate(aAnnMsg);
        if (SynMsgSyndicateAnnounce(aAnnMsg, 0x1b, uNumber, pszAnnounce)) {
            ManagerInsert(pMgr, uId, aAnnMsg);
        }
        ::syndicate::g_fnModMem0428(aAnnMsg);      // 0x1417db330
    }
    ::syndicate::g_fnModMem1088(aAttrMsg);         // 0x1417da8b0
}

}  // namespace tq
