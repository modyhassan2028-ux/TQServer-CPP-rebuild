// SyndicateInviteNotify.cpp — D68
//
// The five deep bodies, verbatim from raw disasm.
// The vt-call shapes ride the header comments.
#include "modules/syndicate/src/SyndicateInviteNotify.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h" // D66 seams
#include "modules/syndicate/src/SyndicateLeagueOpt.h" // str mgr
#include "modules/syndicate/src/SyndicateLeagueMgr.h"
#include "modules/syndicate/src/SyndicateLeagueMember.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include <cstdio>
#include <cstring>

namespace syndicate {

uint32_t (*g_fn1417b0370)(void*, uint32_t) = nullptr;
bool (*g_fn14174f020)(void*, uint32_t, void*) = nullptr;
void (*g_fn141745580)(void*, void*) = nullptr;
uint32_t (*g_fn1417b5370)(void*, uint32_t, void*) = nullptr;
void (*g_fn141766b60)(void*, uint32_t, void*, void*,
                      uint32_t) = nullptr;
void (*g_fn141766d10)(void*, uint32_t, void*, void*,
                      uint32_t) = nullptr;
void (*g_fn1417d6110)(void*) = nullptr;
bool (*g_fn1417d61c0)(void*, const void*, uint32_t, uint32_t,
    uint32_t, const char*, const char*) = nullptr;
void (*g_fn1417d6160)(void*) = nullptr;
bool (*g_fn1417d6790)(void*, uint32_t, uint32_t, uint32_t,
                      uint32_t) = nullptr;
bool (*g_fn1417d6820)(void*, uint32_t, const char*, uint32_t,
    uint32_t, uint32_t) = nullptr;
void (*g_fn1417d66c0)(void*) = nullptr;
void (*g_fn1417d9900)(void*) = nullptr;
bool (*g_fn1417d9b30)(void*, uint32_t, uint32_t, uint32_t,
    uint8_t, uint8_t, const char*, uint32_t) = nullptr;
void (*g_fn1417d9950)(void*) = nullptr;
// g_fn14174e3f0 defined in SyndicateLeagueOpt.cpp (int32_t)
bool (*g_fn14174b6c0)(void*, uint32_t, void*) = nullptr;
uint32_t (*g_fn14174e7e0)(void*) = nullptr;
void (*g_fn14174e7f0)(void*, uint32_t, uint32_t, uint8_t,
                      uint16_t) = nullptr;
bool (*g_fn141763920)(void*, uint32_t) = nullptr;
void (*g_fn14176ca70)(void*, uint32_t, uint32_t,
                      uint32_t) = nullptr;
uint32_t (*g_fn14178f2d0)(void*) = nullptr;
void (*g_fn14178f470)(void*) = nullptr;
int32_t (*g_fn141790390)(void*) = nullptr;
void (*g_fn1417903d0)(void*, uint32_t) = nullptr;
void (*g_fn14174dcd0)(void*, uint32_t) = nullptr;
void (*g_fnTqStrCopy)(char*, const char*, size_t) = nullptr;

static const char kSynLogicCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\syndicatelogic.cpp";

// ---- the shared gate shorthands (raw vt shapes) ----
static inline void** MgrOf(void* pLogic) {
    return *(void***)((char*)pLogic + 8);
}
static inline void** HostOf(void* pLogic) {
    return *(void***)((char*)pLogic + 0x50);
}
static inline void** InnerOf(void* pLogic) {
    return *(void***)((char*)pLogic + 0x10);
}

// ================= 1417b0680: SynTalkGate =================
bool SynTalkGate(void* pLogic, uint32_t uActor,
                 const char* psz, void* pR9Stale) {
    if (psz == nullptr)          // raw: rax&~0xff (al=0)
        return false;
    if (strlen(psz) >= 0x100)    // cmp rcx, 0x100; jae end
        return false;
    if (!g_fnAnnounceStrCheck(psz, 1)) {
        void* pMgr = g_fnStringMgrInstance();
        const char* pszErr = (const char*)
            g_fnStringMgrGetStr(pMgr,
                                "STR_INVALID_CHARACTER");
        // r9 not set -> pR9Stale (verbatim ride)
        g_fnAnnounce750(pLogic, uActor, pszErr, pR9Stale);
        return false;            // raw: al = 0
    }
    // mgr-vt[0x4a8/8=149](mgr, actor) -> id
    void** ppMgr = MgrOf(pLogic);
    uint32_t uId = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x4a8 / 8])(ppMgr, uActor);
    if (uId == 0)
        return false;
    void* pRec = MgrLeagueFind((int64_t)HostOf(pLogic), uId);
    if (pRec == nullptr)
        return false;
    // FUN_141745520 -> LeagueGetId; then b0370(logic, id)
    uint32_t uLid = (uint32_t)LeagueGetId((int64_t)pRec);
    if (g_fn1417b0370(pLogic, uLid) != uActor)
        return false;
    // LeagueSetRecStr(rec, 6, str, 1)
    LeagueSetRecStr((int64_t)pRec, 6,
                    (uint64_t)(uintptr_t)psz, 1);
    return true;                 // raw: al = 1
}

// ================= 1417b0ea0: MemberOverhead =================
void MemberOverhead(void* pLogic, uint32_t uActor,
                    uint8_t bFlag) {
    if (uActor == 0)
        return;
    void** ppMgr = MgrOf(pLogic);
    // mgr-vt[0x268/8=77](mgr) — edx stale
    if (!(((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x268 / 8])(ppMgr, 0)))
        return;
    // mgr-vt[0x4a8/8=149](mgr, actor) -> id
    uint32_t uId = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x4a8 / 8])(ppMgr, uActor);
    uint32_t uCount = g_fn14174e3f0(HostOf(pLogic));
    uint8_t bLeader = 0;         // CVar9
    if (uId != 0) {
        // FUN_1417647e0 = MgrGetLeaderId(host, id)
        uint32_t uLdr = MgrGetLeaderId(
            (int64_t)HostOf(pLogic), uId);
        if (uLdr == uActor)
            bLeader = 1;
    }
    uint8_t bCountry;            // CVar10
    const char* pszName;
    if (uId == uCount) {
        bCountry = 1;
        // logic-vt[0x468/8=141](logic) -> name
        const char* p = (const char*)
            ((void*(*)(void*))(*(void***)pLogic)
                [0x468 / 8])(pLogic);
        pszName = (p != nullptr) ? p : "";
    } else {
        bCountry = 0;
        // logic-vt[0x470/8=142](logic, id)
        const char* p = (const char*)
            ((void*(*)(void*, uint32_t))
                (*(void***)pLogic)[0x470 / 8])(pLogic,
                                               uId);
        pszName = (p != nullptr) ? p : "";
    }
    // mgr-vt[0x280/8=80](mgr, actor)
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x280 / 8])(ppMgr, uActor)) {
        // the fast path: vt+0x410 SIX args
        // RAW 0x1417b0f9f/a: r9d = r12b (Leader),
        // [rsp+0x20] = r13b (Country)
        ((void(*)(void*, uint32_t, uint32_t, uint8_t,
                  uint8_t, const char*))
            (*(void***)ppMgr)[0x410 / 8])(ppMgr,
                uActor, uId, bLeader, bCountry,
                pszName);
        return;
    }
    // the notify path
    uint8_t abMsg[0x470];
    g_fn1417d9900(abMsg);
    // mgr-vt[0x3f0/8=126](mgr) -> server id
    uint32_t uServer = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x3f0 / 8])(ppMgr, 0);
    if (!g_fn1417d9b30(abMsg, 0, uActor, uId,
                       bLeader, bCountry, pszName,
                       uServer)) {
        g_fnMsgBatchLog("IF_OK",
            "msg.Create(OVERHEAD_USER, idUser, idLeague, "
            "bIsLeagueLeader, bIsCountryLeagueMember, "
            "pszLeagueName, m_pConsumer->GetThisServerID"
            "())",
            kSynLogicCpp, 0x1a36);
    } else if (bFlag == 0) {
        // mgr-vt[8](mgr, actor, msg) — the ac7d0 family
        ((void(*)(void*, uint32_t, void*))
            (*(void***)ppMgr)[1])(ppMgr, uActor, abMsg);
    } else {
        // mgr-vt[0x58/8=11](mgr, actor, msg, 1)
        ((void(*)(void*, uint32_t, void*, uint32_t))
            (*(void***)ppMgr)[0x58 / 8])(ppMgr, uActor,
                                         abMsg, 1);
    }
    g_fn1417d9950(abMsg);
}

// ================= 1417b98e0: LeagueInfoPush =================
void LeagueInfoPush(void* pLogic, uint32_t uActor) {
    void** ppMgr = MgrOf(pLogic);
    // mgr-vt[0x278/8=83](mgr) — edx stale
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x278 / 8])(ppMgr, 0))
        return;
    // logic-vt[0x510/8=162](logic, actor) -> league id
    uint32_t uLid = ((uint32_t(*)(void*, uint32_t))
        (*(void***)pLogic)[0x510 / 8])(pLogic, uActor);
    void* pRec = MgrLeagueFind((int64_t)HostOf(pLogic),
                               uLid);
    if (pRec == nullptr)
        return;
    if (!g_fn14174f020(HostOf(pLogic), uActor, pRec))
        return;
    // the record string block + the two scratch pairs
    static thread_local uint8_t s_abRec[0x146];
    memset(s_abRec, 0, 0x146);
    g_fn141745580(pRec, s_abRec);
    uint32_t uKeyOut = 0;   // local_9e4[0]
    uint32_t uValOut = 0;   // local_9e8
    uint8_t abBuf1[0x10];   // local_48+0x10
    uint8_t abBuf2[0x10];   // local_48
    memset(abBuf1, 0, 0x10);
    memset(abBuf2, 0, 0x10);
    // mgr-vt[0x568/8=173](mgr, actor, uLid) -> id
    uint32_t uId = ((uint32_t(*)(void*, uint32_t, uint32_t))
        (*(void***)ppMgr)[0x568 / 8])(ppMgr, uActor, uLid);
    g_fn141766b60(HostOf(pLogic), uId, &uKeyOut, abBuf1,
                  0x10);
    g_fn141766d10(HostOf(pLogic), uId, &uValOut, abBuf2,
                  0x10);
    uint8_t abMsg[0x470];
    g_fn1417d6110(abMsg);
    // RAW: BOTH are /1000 (magic 0x431bde83 >> 0x12),
    // NOT the decompile's /1000000
    uint32_t uA = uValOut / 1000;
    uint32_t uB = uKeyOut / 1000;
    uint32_t uFlag = g_fn1417b5370(pLogic, uActor, pRec);
    if (!g_fn1417d61c0(abMsg, s_abRec, uFlag, uB, uA,
                       (const char*)abBuf1,
                       (const char*)abBuf2)) {
        g_fnMsgBatchLog("IF_OK",
            "msgLeagueInfo.Create(stLeagueInfo, "
            "GetLeagueAwardFlag(idUser ,pLeague), "
            "ID_SERVER_LEAGUE_SERVER(idPlunder), "
            "ID_SERVER_LEAGUE_SERVER(idPlundered), "
            "szPlunder, szPlundered)",
            kSynLogicCpp, 0x2415);
    } else {
        // mgr-vt[8](mgr, actor, msg)
        ((void(*)(void*, uint32_t, void*))
            (*(void***)ppMgr)[1])(ppMgr, uActor, abMsg);
    }
    g_fn1417d6160(abMsg);
    // the 0x2e broadcast
    uint8_t abMsg2[0x470];
    CtorCMsgLeagueOpt(abMsg2);   // 1417d6640 (D57 REAL)
    if (g_fn1417d6790(abMsg2, 0x2e, 0, 0, 0))
        ((void(*)(void*, uint32_t, void*))
            (*(void***)ppMgr)[1])(ppMgr, uActor, abMsg2);
    g_fn1417d66c0(abMsg2);
}

// ================= 1417b48b0: InviteSynReply =================
void InviteSynReply(void* pLogic, uint32_t uActor,
    uint32_t uTarget, uint8_t bAccept, uint8_t bRefuse) {
    if (uActor == 0 || uTarget == 0)
        return;
    void** ppMgr = MgrOf(pLogic);
    // mgr-vt[0x278](mgr) edx stale; then (mgr, target)
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x278 / 8])(ppMgr, 0))
        return;
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x278 / 8])(ppMgr, uTarget))
        return;
    // mgr-vt[0x2d0/8=86](mgr, actor); then (mgr, target)
    if (!(((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x2d0 / 8])(ppMgr, uActor)))
        return;
    if (!(((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x2d0 / 8])(ppMgr, uTarget)))
        return;
    char szBuf[0x400];   // raw: the [rsp+0x86f] terminator
    if (bAccept != 0 && bRefuse != 0) {
        // the refuse announce
        szBuf[0] = 0;
        memset(szBuf + 1, 0, 0x1ff);
        void* pMgr = g_fnStringMgrInstance();
        const char* pszLg = (const char*)
            ((void*(*)(void*, uint32_t))
                (*(void***)ppMgr)[0x1d8 / 8])(ppMgr,
                                              uTarget);
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr,
                "STR_LEAGUE_REFUSE_INVITE_SYN");
        // ONE hidden vararg: the 1d8 string
        snprintf(szBuf, 0x200, psz, pszLg);
        szBuf[0x1ff] = 0;
        // mgr-vt[0x28/8=5](mgr, actor, buf, 0xffff00)
        ((void(*)(void*, uint32_t, const char*, uint32_t))
            (*(void***)ppMgr)[5])(ppMgr, uActor, szBuf,
                                  0xffff00);
        return;
    }
    // the shared gates
    uint32_t uId = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x4a8 / 8])(ppMgr, uActor);
    void* pRec = MgrLeagueFind((int64_t)HostOf(pLogic),
                               uId);
    if (pRec == nullptr)
        return;
    if (LeagueGetLeaderId((int64_t)pRec) != uActor)
        return;
    // mgr-vt[0x1f8/8=63](mgr, target) -> target league id
    uint32_t uTgtLid = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x1f8 / 8])(ppMgr, uTarget);
    if (uTgtLid == 0)
        return;
    void* pLeague = (void*)LeagueMemberLookup(
        (void*)InnerOf(pLogic), uTgtLid);
    if (pLeague == nullptr)
        return;
    if (g_fn14178f2d0(pLeague) != uTarget)
        return;
    if (g_fn141790390(pLeague) != 0)
        return;
    if (bAccept == 0) {
        // the invite-not-yet-accepted path
        if (g_fn141763920(HostOf(pLogic), uTarget)) {
            // JOIN: mgr-vt[0x188/8=49](mgr, actor, 10, t)
            ((void(*)(void*, uint32_t, uint32_t, uint32_t))
                (*(void***)ppMgr)[0x188 / 8])(ppMgr,
                    uActor, 10, uTarget);
            szBuf[0] = 0;
            memset(szBuf + 1, 0, 0x1ff);
            void* pMgr = g_fnStringMgrInstance();
            // mgr-vt[0x1d8](mgr, actor) -> name
            const char* pszN = (const char*)
                ((void*(*)(void*, uint32_t))
                    (*(void***)ppMgr)[0x1d8 / 8])(ppMgr,
                                                  uActor);
            LeagueGetRec1Str((int64_t)pRec);
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_LEAGUE_INVITE_JOIN_LEAGUE");
            // TWO hidden varargs: (the league rec ride,
            // the 1d8 name) — verbatim
            snprintf(szBuf, 0x200, psz, pLeague, pszN);
            szBuf[0x1ff] = 0;
            uint8_t abMsg[0x470];
            CtorCMsgLeagueOpt(abMsg);
            if (g_fn1417d6820(abMsg, 0x4a, szBuf, 0,
                              uActor, 0)) {
                ((void(*)(void*, uint32_t, void*))
                    (*(void***)ppMgr)[1])(ppMgr, uTarget,
                                          abMsg);
                ((void(*)(void*, uint32_t, void*))
                    (*(void***)ppMgr)[1])(ppMgr, uActor,
                                          abMsg);
            }
            g_fn1417d66c0(abMsg);
        } else {
            // LEAVE SOON
            szBuf[0] = 0;
            memset(szBuf + 1, 0, 0x1ff);
            void* pMgr = g_fnStringMgrInstance();
            uint32_t uSoon = g_fn14174e7e0(
                HostOf(pLogic));
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_LEAGUE_INVITE_LEAVE_SOON");
            // ONE hidden vararg: the e7e0 int
            snprintf(szBuf, 0x200, psz, uSoon);
            szBuf[0x1ff] = 0;
            ((void(*)(void*, uint32_t, const char*,
                      uint32_t))
                (*(void***)ppMgr)[5])(ppMgr, uActor,
                                      szBuf, 0xffff00);
        }
        return;
    }
    // the accept path
    if (!(((bool(*)(void*, uint32_t, uint32_t, uint32_t))
        (*(void***)ppMgr)[0x180 / 8])(ppMgr, uActor, 10,
                                      uTarget)))
        return;
    g_fn1417903d0(pLeague, uId);
    g_fn14174dcd0(pRec, uTgtLid);
    // logic-vt[0x710/8=226](logic, league, uId, 0xb)
    ((void(*)(void*, void*, uint32_t, uint32_t))
        (*(void***)pLogic)[0x710 / 8])(pLogic, pLeague,
                                       uId, 0xb);
    uint32_t uCnt = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x3f0 / 8])(ppMgr, 0);
    g_fn14176ca70(HostOf(pLogic),
                  uId + uCnt * 1000000, 0, uTgtLid);
    szBuf[0] = 0;
    memset(szBuf + 1, 0, 0x3ff);
    void* pMgr = g_fnStringMgrInstance();
    uint64_t uDd0 = LeagueGetRec1Str((int64_t)pRec);
    g_fn14178f470(pLeague);
    const char* psz = (const char*)
        g_fnStringMgrGetStr(pMgr, "STR_SYN_JOIN_LEAGUE");
    // TWO hidden varargs: (the league rec, the dd0 ret)
    snprintf(szBuf, 0x3ff, psz, pLeague,
             (void*)(uintptr_t)uDd0);
    szBuf[0x3ff] = 0;
    // mgr-vt[0x90/8=18](mgr, buf, 0x843)
    ((void(*)(void*, const char*, uint32_t))
        (*(void***)ppMgr)[0x90 / 8])(ppMgr, szBuf,
                                     0x843);
}

// ================= 1417b4d60: InviteLeagueReply =================
void InviteLeagueReply(void* pLogic, uint32_t uActor,
    uint32_t uTarget, uint8_t bAccept, uint8_t bRefuse) {
    if (uActor == 0 || uTarget == 0)
        return;
    void** ppMgr = MgrOf(pLogic);
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x278 / 8])(ppMgr, 0))
        return;
    if (((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x278 / 8])(ppMgr, uTarget))
        return;
    if (!(((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x2d0 / 8])(ppMgr, uActor)))
        return;
    if (!(((bool(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x2d0 / 8])(ppMgr, uTarget)))
        return;
    char szBuf[0x400];
    if (bAccept != 0 && bRefuse != 0) {
        szBuf[0] = 0;
        memset(szBuf + 1, 0, 0x1ff);
        void* pMgr = g_fnStringMgrInstance();
        const char* pszLg = (const char*)
            ((void*(*)(void*, uint32_t))
                (*(void***)ppMgr)[0x1d8 / 8])(ppMgr,
                                              uTarget);
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr,
                "STR_LEAGUE_REFUSE_INVITE_SYN");
        snprintf(szBuf, 0x200, psz, pszLg);
        szBuf[0x1ff] = 0;
        ((void(*)(void*, uint32_t, const char*, uint32_t))
            (*(void***)ppMgr)[5])(ppMgr, uActor, szBuf,
                                  0xffff00);
        return;
    }
    // no league yet: mgr-vt[0x1f8](mgr, target) == 0 AND
    // logic-vt[0x510](logic, target) == 0
    uint32_t uTgtLid = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x1f8 / 8])(ppMgr, uTarget);
    if (uTgtLid != 0)
        return;
    uTgtLid = ((uint32_t(*)(void*, uint32_t))
        (*(void***)pLogic)[0x510 / 8])(pLogic, uTarget);
    if (uTgtLid != 0)
        return;
    uint32_t uId = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x4a8 / 8])(ppMgr, uActor);
    void* pRec = MgrLeagueFind((int64_t)HostOf(pLogic),
                               uId);
    if (pRec == nullptr)
        return;
    if (LeagueGetLeaderId((int64_t)pRec) != uActor)
        return;
    if (bAccept == 0) {
        if (g_fn141763920(HostOf(pLogic), uTarget)) {
            // mgr-vt[0x188](mgr, actor, 0xb, target)
            ((void(*)(void*, uint32_t, uint32_t, uint32_t))
                (*(void***)ppMgr)[0x188 / 8])(ppMgr,
                    uActor, 0xb, uTarget);
            szBuf[0] = 0;
            memset(szBuf + 1, 0, 0x1ff);
            void* pMgr = g_fnStringMgrInstance();
            const char* pszN = (const char*)
                ((void*(*)(void*, uint32_t))
                    (*(void***)ppMgr)[0x1d8 / 8])(ppMgr,
                                                  uActor);
            LeagueGetRec1Str((int64_t)pRec);
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_LEAGUE_INVITE_JOIN_LEAGUE");
            // TWO varargs: (bAccept ride = rbx, the
            // 1d8 name) — verbatim raw 1417b502f
            snprintf(szBuf, 0x200, psz, (int)bAccept,
                     pszN);
            szBuf[0x1ff] = 0;
            uint8_t abMsg[0x470];
            CtorCMsgLeagueOpt(abMsg);
            if (g_fn1417d6820(abMsg, 0x4a, szBuf, 0,
                              uActor, 0)) {
                ((void(*)(void*, uint32_t, void*))
                    (*(void***)ppMgr)[1])(ppMgr, uTarget,
                                          abMsg);
                ((void(*)(void*, uint32_t, void*))
                    (*(void***)ppMgr)[1])(ppMgr, uActor,
                                          abMsg);
            }
            g_fn1417d66c0(abMsg);
        } else {
            szBuf[0] = 0;
            memset(szBuf + 1, 0, 0x1ff);
            void* pMgr = g_fnStringMgrInstance();
            uint32_t uSoon = g_fn14174e7e0(
                HostOf(pLogic));
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_LEAGUE_INVITE_LEAVE_SOON");
            // ONE hidden vararg: the e7e0 int
            snprintf(szBuf, 0x200, psz, uSoon);
            szBuf[0x1ff] = 0;
            ((void(*)(void*, uint32_t, const char*,
                      uint32_t))
                (*(void***)ppMgr)[5])(ppMgr, uActor,
                                      szBuf, 0xffff00);
        }
        return;
    }
    // the accept path (0xb gate)
    if (!(((bool(*)(void*, uint32_t, uint32_t, uint32_t))
        (*(void***)ppMgr)[0x180 / 8])(ppMgr, uActor,
                                      0xb, uTarget)))
        return;
    // the member-info block (16 bytes + the name field)
    uint8_t abInfo[0x20];
    memset(abInfo, 0, sizeof abInfo);
    *(uint32_t*)(abInfo + 0) = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x290 / 8])(ppMgr, uTarget);
    *(uint32_t*)(abInfo + 4) = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x220 / 8])(ppMgr, uTarget);
    *(uint16_t*)(abInfo + 8) = ((uint16_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x1f0 / 8])(ppMgr, uTarget);
    *(uint32_t*)(abInfo + 0xa) = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x240 / 8])(ppMgr, uTarget);
    abInfo[0xe] = 1;
    const char* pszN = (const char*)
        ((void*(*)(void*, uint32_t))
            (*(void***)ppMgr)[0x1d8 / 8])(ppMgr, uTarget);
    g_fnTqStrCopy((char*)(abInfo + 0xf), pszN, 0x10);
    if (!g_fn14174b6c0(pRec, uTarget, abInfo)) {
        // the failure tail still runs e7f0/ca70/notify
        g_fn14174e7f0(HostOf(pLogic), uTarget, uId, 1, 8);
        uint32_t uCnt = ((uint32_t(*)(void*, uint32_t))
            (*(void***)ppMgr)[0x3f0 / 8])(ppMgr, 0);
        g_fn14176ca70(HostOf(pLogic),
                      uId + uCnt * 1000000, uTarget, 0);
        MemberOverhead(pLogic, uTarget, 1);
        return;
    }
    // the success announce
    szBuf[0] = 0;
    memset(szBuf + 1, 0, 0x1ff);
    void* pMgr = g_fnStringMgrInstance();
    uint64_t uDd0 = LeagueGetRec1Str((int64_t)pRec);
    const char* pszN2 = (const char*)
        ((void*(*)(void*, uint32_t))
            (*(void***)ppMgr)[0x1d8 / 8])(ppMgr, uTarget);
    const char* psz = (const char*)
        g_fnStringMgrGetStr(pMgr,
            "STR_LEAGUE_JOIN_SUCESSS");
    // TWO varargs: (the 1d8 name, the dd0 ret)
    snprintf(szBuf, 0x200, psz, pszN2,
             (void*)(uintptr_t)uDd0);
    szBuf[0x1ff] = 0;
    ((void(*)(void*, const char*, uint32_t))
        (*(void***)ppMgr)[0x90 / 8])(ppMgr, szBuf, 0x7d5);
    g_fn14174e7f0(HostOf(pLogic), uTarget, uId, 1, 8);
    uint32_t uCnt = ((uint32_t(*)(void*, uint32_t))
        (*(void***)ppMgr)[0x3f0 / 8])(ppMgr, 0);
    g_fn14176ca70(HostOf(pLogic),
                  uId + uCnt * 1000000, uTarget, 0);
    MemberOverhead(pLogic, uTarget, 1);
}

} // namespace syndicate
