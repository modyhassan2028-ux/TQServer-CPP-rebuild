// ============================================================================
// SyndicateLeagueSupportPublish.cpp — unit D80: RAW-verbatim
// port of FUN_1417c3230 (PublishSupportTokenFromClient).
#include "modules/syndicate/src/SyndicateLeagueSupportPublish.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderSignup.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderList.h"
#include "modules/syndicate/src/SyndicateLeagueAddTodayPlunder.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptFlow.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"
#include "modules/syndicate/src/SyndicateInviteNotify.h"
#include <cmath>
#include <cstring>

namespace syndicate {
char (*g_fnPstTargetAllowed)(void*, uint32_t, uint32_t);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}

int32_t PublishSupportTokenFromClient(void** apLogic, uint32_t uUser,
        int32_t nCount, uint32_t* apTargets, char bSupport,
        uint32_t uParam6) {
    if (uUser == 0 || nCount < 1 || 10 < nCount) return 0;
    void* pVtObj = apLogic[1];
    void* pMgr   = apLogic[10];
    if ((char)g_fnSplWarState(pVtObj) != 0) return 0;
    // RAW: TWO calls (== 1 || == 2)
    if (g_fnSplMgrGate(pMgr) != 1 &&
        g_fnSplMgrGate(pMgr) != 2) return 0;
    uint32_t uUserLeague = g_fnSupUserLeague(pVtObj, uUser);
    if (uUserLeague == 0) return 0;
    void* pLeague = g_fnSplFindLeague(pMgr, uUserLeague);
    if (pLeague == nullptr) return 0;
    uint32_t uKey = g_fnSupMemberKey(pVtObj, uUser, uUserLeague);
    if (uKey == 0) return 0;

    // the vector {proxy, begin, end, cap-end}
    // the fixture container models the RAW std::vector object;
    // its insert fake updates the container at +0x20, so keep
    // headroom past the 4 proxy words
    uint64_t aVec[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    void* pProxyVec = g_fnLbrOpNew(8);
    if (pProxyVec != nullptr) {
        *(void**)pProxyVec = aVec;
        aVec[0] = (uint64_t)(uintptr_t)pProxyVec;
    }
    uint32_t uLast = 0;
    for (int32_t i = 0; i < nCount; i++) {
        uint32_t uT = apTargets[i];
        if (uT == 0) continue;
        uint32_t uMy = (uint32_t)g_fnLbrGetMyLeague(pVtObj);
        if (uMy == uT) {
            uint32_t uTgt = g_fnSplMyTarget(pMgr);
            if (uTgt == 0 || uTgt == uUserLeague) continue;
            uint32_t uMy2 = (uint32_t)g_fnLbrGetMyLeague(pVtObj);
            uT = uMy2 * 1000000 + uTgt;
        } else {
            uT = g_fnSplResolveId(pMgr, uT);
        }
        uLast = uT;
        if (uT != 0 && uKey != uT &&
            g_fnPstTargetAllowed(pMgr, uKey, uT) != 0) {
            uint32_t* pB = (uint32_t*)(uintptr_t)aVec[1];
            uint32_t* pE = (uint32_t*)(uintptr_t)aVec[2];
            uint64_t  uC = aVec[3];
            uint64_t uCapElems = (pB == nullptr)
                ? 0 : (uC - (uint64_t)(uintptr_t)pB) / 4;
            if ((uint64_t)(pE - pB) < uCapElems) {
                *pE = uT;
                aVec[2] = (uint64_t)(uintptr_t)(pE + 1);
            } else {
                uint64_t aIns[2] = { aVec[0],
                    (uint64_t)(uintptr_t)pE };
                g_fnSplVecInsert(aVec, aIns, 1, &uT);
            }
        }
    }
    // the RAW gate: the LAST resolved target AND non-empty
    if (uLast == 0 || aVec[1] == 0) {
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    void* pToken = g_fnSplTokenAcquire(pLeague, 0x6a);
    if (pToken == nullptr) {
        pToken = g_fnSplTokenRetry(pLeague, 0x6a);
        if (pToken == nullptr) {
            if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
            aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
            g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
            return 0;
        }
    }
    uint32_t uTokId = g_fnSplTokenId(pToken);
    void* pRow = g_fnSplTokenRow(pMgr, uTokId);
    if (pRow == nullptr) {
        g_fnSplDbLog("table:cq_token_type, can not find token_id[%lu] at %s, %d.",
            uTokId,
            "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
            0x2774);
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    char aStr[48];
    if (g_fnSplBuildText(pVtObj, uUser, pLeague, pToken,
                         pRow, aStr) == 0) {
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    void* pPpl = g_fnSplLeagueCount(pLeague);
    void* pF4 = g_fnSplRowField(pRow, 4);
    int64_t nMax = (int64_t)(uintptr_t)g_fnSplRowValA(pF4);
    uint64_t aMsgP[0x2300 / 8];
    if (bSupport == 0) {
        int32_t nCfg = g_fnSplTargetCfg(pMgr);
        if (nCfg < 1) {
                if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
            aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
            g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
            return 0;
        }
        nCfg = g_fnSplTargetCfg(pMgr);
        double dPages = std::ceil((double)(nMax -
            (int64_t)(uintptr_t)pPpl) / (double)nCfg);
        g_fnAtpMsgCtor(aMsgP);
        if (g_fnAtpMsgCreate(aMsgP, 6,
                (int32_t)(int64_t)dPages) == 0) {
            g_fnAtpMsgDtor(aMsgP);
                if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
            aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
            g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
            return 0;
        }
        uint32_t* pIt = (uint32_t*)(uintptr_t)aVec[1];
        uint32_t* pEndL = (uint32_t*)(uintptr_t)aVec[2];
        bool bOver = false;
        for (;;) {
            if (pIt == pEndL) break;
            if (aVec[0] == 0) g_fnLbrInvalid();
            else {
                void* pCont = *(void**)(uintptr_t)aVec[0];
                if ((void*)(uintptr_t)aVec[3] <= (void*)pIt)
                    g_fnLbrInvalid();
            }
            uint32_t uLg = *pIt / 1000000;
            if (g_fnSupMsgAppend(aMsgP, (int32_t)uLg) == 0) {
                bOver = true;
                break;
            }
            pIt++;
        }
        if (bOver)
            g_fnPwsLogErr("CSyndicateLogic::PublishSupportTokenFromClient msg over size", 0);
        if (g_fnSupMsgCount(aMsgP) != 0) {
            g_fnAtpMsgSerialize(aMsgP);
            g_fnSplSendMsg(pVtObj, uUser, aMsgP);
        }
        g_fnAtpMsgDtor(aMsgP);
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 1;
    }
    // the support branch (param_5 != 0)
    if (uParam6 == 0) {
        const char* psz = (const char*)g_fnStringMgrGetStr(
            g_fnStringMgrInstance(), "STR_SUPPORT_TOKEN_USE_FAIL");
        g_fnSupTalk(pVtObj, uUser, psz, 0xffff00);
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    int64_t nMax2 = nMax -
        (int64_t)g_fnSplTargetCfg(pMgr) * (int64_t)uParam6;
    if (nMax2 < 0) {
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    if ((int64_t)(uintptr_t)pPpl < nMax2) {
        const char* psz = (const char*)g_fnStringMgrGetStr(
            g_fnStringMgrInstance(), "STR_SUPPORT_TOKEN_USE_FAIL");
        g_fnSupTalk(pVtObj, uUser, psz, 0xffff00);
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    if (g_fnSplChargeEmoney(pVtObj, uUser, 0, uParam6) == 0) {
        const char* psz = (const char*)g_fnStringMgrGetStr(
            g_fnStringMgrInstance(),
            "STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH");
        g_fnSupTalk(pVtObj, uUser, psz, 0xffff00);
        if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
        return 0;
    }
    g_fnSplEmoneyPaid(pVtObj, uUser);
    const char* pName = (const char*)g_fnSplUserName(pVtObj, uUser);
    g_fnSupMyLogSave("gmlog/emoney_buy",
        "%lu\t%s\t%lu\t350\t4323\t%u\t%u\t1\t",
        (uint64_t)uUser, (void*)pName);
    char aBuf[0x221];
    aBuf[0x20] = 0;
    memset(aBuf + 0x21, 0, 0x1ff);
    const char* pFmt = (const char*)g_fnStringMgrGetStr(
        g_fnStringMgrInstance(),
        "STR_LEAGUE_NOTIFY_USER_SUPPORT_TOKEN_BY_EMONEY");
    g_fnSupSnprintf(aBuf + 0x20, 0x200, pFmt);
    g_fnSupNotifyTalk(pVtObj, aBuf + 0x20, 0x7d5);
    // the common tails
    g_fnSplLeagueAdd(pLeague,
        (int64_t)(uintptr_t)pPpl - nMax2, 1);
    uTokId = g_fnSplTokenId(pToken);
    g_fnSplTokenSet(pToken, 3, uTokId + 1, 0);
    uint32_t uTime = g_fnSupTimeGet(1);
    g_fnSplTokenSet(pToken, 4, uTime, 1);
    unsigned char aInfo[0x146];
    memset(aInfo, 0, 0x146);
    g_fnSplLeagueInfo(pLeague, aInfo);
    uint64_t aMsgS[0x2300 / 8];
    g_fnSplMsgStCtor(aMsgS);
    if (g_fnSplMsgStCheck(aMsgS) != 0) {
        uTokId = g_fnSplTokenId(pToken);
        uTime = g_fnSupTimeGet(1);
        void* pF3 = g_fnSplRowField(pRow, 3);
        int32_t nOff = g_fnSplRowValB(pF3);
        uint64_t uExp = 0;
        if (uTime < (uint64_t)(int64_t)(nOff + (int32_t)uTokId))
            uExp = (uint64_t)((nOff - (int32_t)uTime) +
                              (int32_t)uTokId);
        uint32_t uFlag = g_fnSplTokenFlag(pToken);
        uTokId = g_fnSplTokenId(pToken);
        if (g_fnSplMsgStCreate(aMsgS, (uint8_t)uFlag,
                (uint8_t)uTokId, uExp) != 0) {
            g_fnSplMsgStFlush(aMsgS);
            g_fnSplSendMsg(pVtObj, uUser, aMsgS);
        }
    }
    // RAW: vt+0x560 (no visible args) right after the send,
    // before the msg dtor and the cleanup
    g_fnSplDbSave(pVtObj);
    g_fnSplMsgStDtor(aMsgS);
    if (aVec[1] != 0) g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
    aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
    g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
    return 1;
}
} // namespace syndicate
