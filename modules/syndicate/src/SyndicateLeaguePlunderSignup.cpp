// ============================================================================
// SyndicateLeaguePlunderSignup.cpp — unit D78:
// CSyndicateLogic::SignUpPlunderWarFromClient. Every call
// order mirrors the recovered v6159 RAW; the seams carry
// the raw addresses in the header. No guessing.
#include "modules/syndicate/src/SyndicateLeaguePlunderSignup.h"
#include "modules/syndicate/src/SyndicateLeagueAddTodayPlunder.h"  // RobOpt + OpNew/OpDelete
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"       // lower bound, names, myleague
#include "modules/syndicate/src/SyndicateLeaguePlunderList.h"     // vt+8 send
#include "modules/syndicate/src/SyndicateLeagueRobOptFlow.h"       // the log seam
#include "modules/syndicate/src/SyndicateLeagueOpt.h"              // string mgr
#include <cstring>
#include <cmath>

namespace syndicate {

// ---- the seams ----
char     (*g_fnSupWarState)(void*);
char     (*g_fnSplMgrGate)(void*);
uint32_t (*g_fnSupUserLeague)(void*, uint32_t);
void*    (*g_fnSupFindLeague)(void*, uint32_t);
uint32_t (*g_fnSupMemberKey)(void*, uint32_t, uint32_t);
char     (*g_fnSplAlreadySigned)(void*, uint32_t);
uint32_t (*g_fnSplMyTarget)(void*);
uint32_t (*g_fnSplResolveId)(void*, uint32_t);
void*    (*g_fnSplVecInsert)(void*, void*, uint64_t, void*);
void*    (*g_fnSplTokenAcquire)(void*, int32_t);
void*    (*g_fnSplTokenRetry)(void*, int32_t);
uint32_t (*g_fnSplTokenId)(void*);
uint32_t (*g_fnSplTokenFlag)(void*);
void     (*g_fnSplTokenSet)(void*, int32_t, uint32_t, char);
void*    (*g_fnSplTokenRow)(void*, uint32_t);
char     (*g_fnSplBuildText)(void*, uint32_t, void*, void*, void*, void*);
void*    (*g_fnSplLeagueCount)(void*);
void     (*g_fnSplLeagueAdd)(void*, int64_t, char);
void     (*g_fnSplLeagueInfo)(void*, void*);
void     (*g_fnSplGetNameA)(void*, uint32_t, uint32_t*, char*, int32_t);
void     (*g_fnSplGetNameB)(void*, uint32_t, uint32_t*, char*, int32_t);
int32_t  (*g_fnSplTargetCfg)(void*);
void     (*g_fnSupTalk)(void*, uint32_t, const void*, uint32_t);
uint32_t (*g_fnSplSupportCnt)(void*, uint32_t);
char     (*g_fnSplChargeEmoney)(void*, uint32_t, int32_t, uint32_t);
void     (*g_fnSplEmoneyPaid)(void*, uint32_t);
void*    (*g_fnSplUserName)(void*, uint32_t);
void     (*g_fnSupMyLogSave)(const char*, const char*, uint64_t, void*);
void     (*g_fnSupSnprintf)(char*, uint64_t, const char*);
void     (*g_fnSupNotifyTalk)(void*, const char*, uint16_t);
uint32_t (*g_fnSupTimeGet)(int32_t);
void     (*g_fnSplDbLog)(const char*, uint64_t, const char*, uint32_t);
void     (*g_fnSplInfoFailLog)(const char*, const char*, const char*, const char*);
void     (*g_fnSplMsgInfoCtor)(void*);
char     (*g_fnSplMsgInfoCreate)(void*, void*, uint32_t, uint32_t, uint32_t, const char*, const char*);
void     (*g_fnSplMsgInfoDtor)(void*);
uint32_t (*g_fnSplAwardFlag)(void*, uint32_t, void*);
void     (*g_fnSplMsgStCtor)(void*);
char     (*g_fnSplMsgStCheck)(void*);
char     (*g_fnSplMsgStCreate)(void*, uint8_t, uint8_t, uint64_t);
void     (*g_fnSplMsgStFlush)(void*);
void     (*g_fnSplMsgStDtor)(void*);
void     (*g_fnSplDbSave)(void*);
void*    (*g_fnSplRowField)(void*, int32_t);
int64_t  (*g_fnSplRowValA)(void*);
int32_t  (*g_fnSplRowValB)(void*);

// the D78 msg family: 1417d8810 (append id) — a RAW
// neighbor of D76's 1417d8870 (append id+2 strings), NOT
// the same function; 1417d8700 (count) IS D76's seam
char    (*g_fnSupMsgAppend)(void* pMsg, int32_t nId);
int16_t (*g_fnSupMsgCount)(void* pMsg);

static inline void* RdP(void* p, size_t o) {
    return *(void**)((char*)p + o);
}

int32_t SignUpPlunderWarFromClient(void** apLogic, uint32_t uUser,
    int32_t nCount, uint32_t* apTargets, char bSupport,
    uint32_t uParam6) {
    if (uUser == 0 || nCount < 1 || 10 < nCount) return 0;
    void* pVtObj = apLogic[1];
    void* pMgr = apLogic[10];
    void* apTargetsSaved = apTargets;   // local_1128

    // (1) the gates
    if ((char)g_fnSupWarState(pVtObj) != 0) return 0;      // vt+0x278
    if ((char)g_fnSplMgrGate(pMgr) != 0) return 0;        // 14174ebd0
    uint32_t uUserLeague = g_fnSupUserLeague(pVtObj, uUser);
    if (uUserLeague == 0) return 0;
    void* pLeague = g_fnSupFindLeague(pMgr, uUserLeague); // 1417630d0
    if (pLeague == nullptr) return 0;
    uint32_t uKey = g_fnSupMemberKey(pVtObj, uUser, uUserLeague);
    if (uKey == 0) return 0;                              // local_1118
    if ((char)g_fnSplAlreadySigned(pMgr, uKey) != 0) return 0;

    // (2) the vector: {proxy, begin, end, cap}
    uint64_t aVec[4] = { 0, 0, 0, 0 };
    void* pProxyVec = g_fnLbrOpNew(8);
    if (pProxyVec != nullptr) {
        *(void**)pProxyVec = aVec;
        aVec[0] = (uint64_t)(uintptr_t)pProxyVec;
    }
    for (int64_t i = 0; i < (int64_t)(int32_t)nCount; i++) {
        uint32_t uT = *(uint32_t*)((char*)apTargetsSaved + i * 4);
        if (uT == 0) continue;
        uint32_t uMy = (uint32_t)(uintptr_t)
            g_fnLbrGetMyLeague(pVtObj);                  // vt+0x3f0
        if (uMy == uT) {
            // the compose path: myLeague*1e6 + my-target
            uint32_t uTgt = g_fnSplMyTarget(pMgr);       // 14174e3f0
            if (uTgt == 0 || uTgt == uKey) continue;
            uint32_t uMy2 = (uint32_t)(uintptr_t)
                g_fnLbrGetMyLeague(pVtObj);
            uT = uMy2 * 1000000 + uTgt;
        } else {
            uT = g_fnSplResolveId(pMgr, uT);              // 141766950
        }
        if (uT != 0 && uKey != uT) {
            uint32_t* pBegin = (uint32_t*)(uintptr_t)aVec[1];
            uint32_t* pEnd = (uint32_t*)(uintptr_t)aVec[2];
            uint64_t uCap = aVec[3];
            uint64_t uCapElems = (pBegin == nullptr) ?
                0 : (uCap - (uint64_t)(uintptr_t)pBegin) / 4;
            if ((uint64_t)(pEnd - pBegin) < uCapElems) {
                *pEnd = uT;
                aVec[2] = (uint64_t)(uintptr_t)(pEnd + 1);
            } else {
                uint64_t aIter[2] = { aVec[0],
                    (uint64_t)(uintptr_t)pEnd };
                g_fnSplVecInsert(aVec, aIter, 1, &uT);   // 14172d120
            }
        }
    }
    // empty -> cleanup + out
    uint32_t* pBegin = (uint32_t*)(uintptr_t)aVec[1];
    uint32_t* pEnd = (uint32_t*)(uintptr_t)aVec[2];
    auto VecCleanup = [&]() {
        if (aVec[1] != 0)
            g_fnLbrOpDelete((void*)(uintptr_t)aVec[1]);
        aVec[1] = 0; aVec[2] = 0; aVec[3] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aVec[0]);
    };
    if ((uint64_t)(pEnd - pBegin) == 0) {
        VecCleanup();
        return 0;
    }

    // (3) the token
    void* pToken = g_fnSplTokenAcquire(pLeague, 0x65);   // 14174bac0
    if (pToken == nullptr) {
        pToken = g_fnSplTokenRetry(pLeague, 0x65);       // 14174bbe0
        if (pToken == nullptr) {
            VecCleanup();
            return 0;
        }
    }
    uint32_t uTokId = g_fnSplTokenId(pToken);            // 1417d4ed0
    void* pRow = g_fnSplTokenRow(pMgr, uTokId);          // 141764870
    if (pRow == nullptr) {
        g_fnSplDbLog("table:cq_token_type, can not find token_id[%lu] at %s, %d.",
            uTokId,
            "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
            0x2610);
        VecCleanup();
        return 0;
    }

    // (4) the sign text
    uint64_t aStr[6] = { 0, 0, 0, 0, 0, 0 };             // std::string
    if ((char)g_fnSplBuildText(apLogic, uUser, pLeague, pToken,
                               pRow, aStr) == 0) {        // 1417b2570
        VecCleanup();
        return 0;                                        // string dtor seam-less: RAW calls it; the port models via g_fnSplStrDtor? -- documented below
    }

    // (5) the ceilings
    void* pPpl = g_fnSplLeagueCount(pLeague);           // 1417440d0
    void* pF4 = g_fnSplRowField(pRow, 4);               // row vt+0x10(4)
    int64_t nMax = g_fnSplRowValA(pF4);                 // vt+0x58

    // (6) NOT support: the ceil path
    if (bSupport == 0) {
        if ((int64_t)(uintptr_t)pPpl < nMax) {
            int32_t nCfg = g_fnSplTargetCfg(pMgr);      // 14174e940
            if (nCfg < 1) { VecCleanup(); return 0; }
            nCfg = g_fnSplTargetCfg(pMgr);               // RAW calls twice
            double dPages = std::ceil(
                (double)(nMax - (int64_t)(uintptr_t)pPpl) /
                (double)nCfg);
            alignas(8) unsigned char aMsg1[0x2300];
            g_fnAtpMsgCtor(aMsg1);                      // 1417d8390
            if ((char)g_fnAtpMsgCreate(aMsg1, 1,
                    (int32_t)(int64_t)dPages) == 0) {    // 1417d84d0
                g_fnAtpMsgDtor(aMsg1);                   // 1417d83e0
                VecCleanup();
                return 0;
            }
            uint32_t* pIt = (uint32_t*)(uintptr_t)aVec[1];
            uint32_t* pEndL = (uint32_t*)(uintptr_t)aVec[2];
            bool bOver = false;
            while (true) {
                if (pIt == pEndL) break;
                // the vector debug guards (proxy/cap)
                if (aVec[0] == 0) g_fnLbrInvalid();
                else {
                    void* pCont = *(void**)(uintptr_t)aVec[0];
                    if ((void*)(uintptr_t)aVec[3] <= pIt)
                        g_fnLbrInvalid();
                }
                uint32_t uLg = *pIt / 1000000;
                if ((char)g_fnSupMsgAppend(aMsg1, (int32_t)uLg)
                        == 0) {                          // 1417d8810
                    bOver = true;
                    break;
                }
                pIt++;
            }
            if (bOver)
                g_fnPwsLogErr(
                    "CSyndicateLogic::SignUpPlunderWarFromClient msg over size",
                    0);
            if (g_fnSupMsgCount(aMsg1) != 0) {           // 1417d8700
                g_fnAtpMsgSerialize(aMsg1);              // 1417d8570
                g_fnSplSendMsg(pVtObj, uUser, aMsg1);    // vt+8
            }
            g_fnAtpMsgDtor(aMsg1);                       // 1417d83e0
            VecCleanup();
            return 1;
        }
        // ppl >= max: fall through to the tails
    } else {
        // (7) the support path
        if (uParam6 == 0) {
            g_fnSupTalk(pVtObj, uUser,
                g_fnStringMgrGetStr(g_fnStringMgrInstance(),
                    "STR_PLUNDER_WAR_TOKEN_USE_FAIL"),
                0xffff00);                               // vt+0x28
            VecCleanup();
            return 0;
        }
        uint32_t uCnt = g_fnSplSupportCnt(pVtObj, uUser); // vt+0x238
        if (uCnt < uParam6) { VecCleanup(); return 0; }
        int64_t nMax2 = nMax -
            (int64_t)g_fnSplTargetCfg(pMgr) * uParam6;
        if (nMax2 < 0) { VecCleanup(); return 0; }
        if ((int64_t)(uintptr_t)pPpl < nMax2) {
            g_fnSupTalk(pVtObj, uUser,
                g_fnStringMgrGetStr(g_fnStringMgrInstance(),
                    "STR_PLUNDER_WAR_TOKEN_USE_FAIL"),
                0xffff00);
            VecCleanup();
            return 0;
        }
        if ((char)g_fnSplChargeEmoney(pVtObj, uUser, 0,
                uParam6) == 0) {                          // vt+0x140
            g_fnSupTalk(pVtObj, uUser,
                g_fnStringMgrGetStr(g_fnStringMgrInstance(),
                    "STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH"),
                0xffff00);
            VecCleanup();
            return 0;
        }
        g_fnSplEmoneyPaid(pVtObj, uUser);                 // vt+0x200
        void* pName = g_fnSplUserName(pVtObj, uUser);    // vt+0x1d8
        g_fnSupMyLogSave("gmlog/emoney_buy",
            "%lu\t%s\t%lu\t350\t4238\t%u\t%u\t1\t",
            uUser, pName);                               // tq::MyLogSave
        // the notify buffer: [0x20] = NUL + memset 0x1ff
        char aBuf[0x220];
        aBuf[0x20] = 0;
        memset(aBuf + 0x21, 0, 0x1ff);
        g_fnSupSnprintf(aBuf + 0x20, 0x200,
            (const char*)g_fnStringMgrGetStr(
                g_fnStringMgrInstance(),
                "STR_LEAGUE_NOTIFY_USER_PLUNDER_WAR_BY_EMONEY"));
        g_fnSupNotifyTalk(pVtObj, aBuf + 0x20, 0x7d5);  // vt+0x90
    }

    // (8) the tails — both paths
    g_fnSplLeagueAdd(pLeague,
        (int64_t)(uintptr_t)pPpl - nMax, 1);             // 141744130
    uTokId = g_fnSplTokenId(pToken);
    g_fnSplTokenSet(pToken, 3, uTokId + 1, 0);           // 1417d4f30
    uint32_t uTime = g_fnSupTimeGet(1);                  // tq::TimeGet(1)
    g_fnSplTokenSet(pToken, 4, uTime, 1);
    unsigned char aInfo[0x146];
    memset(aInfo, 0, 0x146);
    g_fnSplLeagueInfo(pLeague, aInfo);                   // 141745580
    // the name pair into the RAW buffers
    char aNames[0x20];
    memset(aNames, 0, 0x20);
    uint32_t uIdA = 0, uIdB = 0;
    g_fnSplGetNameA(pMgr, uKey, &uIdA, aNames + 0x10,
                    0x10);                               // 141766b60
    g_fnSplGetNameB(pMgr, uKey, &uIdB, aNames, 0x10);    // 141766d10
    // msg1: the league info
    alignas(8) unsigned char aMsgI[0x2100];              // local_10c8[1040]
    g_fnSplMsgInfoCtor(aMsgI);                           // 1417d6110
    uint32_t uAward = g_fnSplAwardFlag(apLogic, uUser,
                                      pLeague);          // 1417b5370
    if ((char)g_fnSplMsgInfoCreate(aMsgI, aInfo, uAward,
            uIdA / 1000000, uIdB / 1000000,
            (const char*)(aNames + 0x10),
            (const char*)aNames) == 0) {                  // 1417d61c0
        g_fnSplInfoFailLog("", "IF_OK",
            "msgLeagueInfo.Create(stLeagueInfo, GetLeagueAwardFlag(idUser ,pSynLeague), ID_SERVER_LEAGUE_SERVER(idPlunder), ID_SERVER_LEAGUE_SERVER(idPlundered), szPlunder, szPlundered)",
            "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp");
    } else {
        g_fnSplSendMsg(pVtObj, uUser, aMsgI);             // vt+8
    }
    // msg2: the token status
    alignas(8) unsigned char aMsgS[0x2300];              // local_6d8[1120]
    g_fnSplMsgStCtor(aMsgS);                             // 1417d7350
    if ((char)g_fnSplMsgStCheck(aMsgS) != 0) {           // 1417d73e0
        uTokId = g_fnSplTokenId(pToken);
        uTime = g_fnSupTimeGet(1);
        void* pF3 = g_fnSplRowField(pRow, 3);            // vt+0x10(3)
        int32_t nOff = g_fnSplRowValB(pF3);              // vt+0x50
        uint64_t uExp = 0;
        if (uTime < (uint32_t)(nOff + (int32_t)uTokId))
            uExp = (uint64_t)(((int32_t)nOff -
                (int32_t)uTime) + (int32_t)uTokId);
        uTokId = g_fnSplTokenId(pToken);
        uint32_t uFlag = g_fnSplTokenFlag(pToken);       // 1417d4e70
        if ((char)g_fnSplMsgStCreate(aMsgS,
                (uint8_t)uFlag, (uint8_t)uTokId,
                uExp) != 0) {                            // 1417d7770
            g_fnSplMsgStFlush(aMsgS);                    // 1417d7440
            g_fnSplSendMsg(pVtObj, uUser, aMsgS);        // vt+8
        }
    }
    g_fnSplDbSave(pVtObj);                               // vt+0x560
    g_fnSplMsgStDtor(aMsgS);                             // 1417d73a0
    g_fnSplMsgInfoDtor(aMsgI);                           // 1417d6160
    VecCleanup();
    return 1;
}

} // namespace syndicate
