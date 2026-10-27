// SyndicateLogicTable1.cpp — unit D90 (the header has the
// address map + the seam list).
#include <cstdio>
#include "modules/syndicate/src/syndicatelogic.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"       // LeagueMemberLookup
#include "modules/syndicate/src/SyndicateLogRemove.h"        // LogRecMapFind
#include "modules/syndicate/src/SyndicateCMsgCtors.h"        // the msg ctors
#include "modules/syndicate/src/SyndicateLeagueMgr.h"        // MgrUserLeagueId/Find
#include "modules/syndicate/src/SyndicateAppoint3de.h"   // A84FindSyn (7cad00)
#include "modules/syndicate/src/SyndicateLeagueOpt.h"        // the string mgr
#include "modules/syndicate/src/SyndicateAppoint3de.h"       // the A84 seams
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"  // g_fnLbrOpDelete
#include "modules/syndicate/src/SyndicateInviteNotify.h"      // D114a msg seams
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>

namespace syndicate {

// ---- the seams ----
static void DefDtorBody(void*, uint64_t, void*, char*) {}
void (*g_fnT1DtorBody)(void*, uint64_t, void*, char*) =
    DefDtorBody;
static uint64_t DefInitA(void*, int64_t, int64_t) { return 0; }
uint64_t (*g_fnT1MsgInitA)(void*, int64_t, int64_t) = DefInitA;
static uint64_t DefInitB(void*, int32_t, const char*) {
    return 0;
}
uint64_t (*g_fnT1MsgInitB)(void*, int32_t, const char*) =
    DefInitB;
static uint64_t DefInitC(void*, uint32_t, void*) { return 0; }
uint64_t (*g_fnT1MsgInitC)(void*, uint32_t, void*) = DefInitC;
static uint64_t DefInitD(void*, uint32_t, int32_t) {
    return 0;
}
uint64_t (*g_fnT1MsgInitD)(void*, uint32_t, int32_t) = DefInitD;
static void DefDtorA(void*) {}
void (*g_fnT1MsgDtorA)(void*) = DefDtorA;
static void DefDtorC(void*) {}
void (*g_fnT1MsgDtorC)(void*) = DefDtorC;
static void DefRecData(void*, void*) {}
void (*g_fnT1RecGetData)(void*, void*) = DefRecData;
static char DefLowMoney(void*) { return 0; }
char (*g_fnT1IsLowMoney)(void*) = DefLowMoney;
static void DefOnline(void*) {}
void (*g_fnT1MemberOnline)(void*) = DefOnline;
static void DefSoon(void*, uint32_t) {}
void (*g_fnT1DelRoleSoon)(void*, uint32_t) = DefSoon;
static int64_t DefDays(void*) { return 0; }
int64_t (*g_fnT1GetDestroyDays)(void*) = DefDays;
static int32_t DefOptGet(void*, uint32_t) { return 0; }
int32_t (*g_fnT1OptGet)(void*, uint32_t) = DefOptGet;
static void DefSetPlayer(void*, uint32_t, uint32_t) {}
void (*g_fnT1SetPlayer)(void*, uint32_t, uint32_t) =
    DefSetPlayer;
static char DefFlag(void*, uint32_t) { return 0; }
char (*g_fnT1HasFlag)(void*, uint32_t) = DefFlag;
static void DefRankClear(int32_t) {}
void (*g_fnT1RankClear)(int32_t) = DefRankClear;
static uint64_t DefConfirmed(void*) { return 0; }
uint64_t (*g_fnT1IsConfirmed)(void*) = DefConfirmed;
static uint64_t DefRecSynId(void*) { return 0; }
uint64_t (*g_fnT1LogRecSynId)(void*) = DefRecSynId;
static void DefFlagClear(int64_t, int32_t) {}
void (*g_fnT1FlagClear)(int64_t, int32_t) = DefFlagClear;
static uint64_t DefDelRole(void*, uint32_t) { return 0; }
uint64_t (*g_fnT1DelRole)(void*, uint32_t) = DefDelRole;
static uint64_t DefQuit(void*, void*, void*, const char*,
                        char, char, char) { return 0; }
uint64_t (*g_fnT1QuitFlow)(void*, void*, void*, const char*,
                           char, char, char) = DefQuit;
static void DefLogErr(const char*) {}
void (*g_fnT1LogError)(const char*) = DefLogErr;

// ================= +0x000 FUN_1417b61e0 =================
// the deleting dtor: the base body + the flag delete.
void* CSyndicateLogic::Slot000DelDtor(
    void* p, uint64_t u2, void* p3, char* p4) {
    g_fnT1DtorBody(p, u2, p3, p4);
    if ((u2 & 1) != 0) g_fnLbrOpDelete(p);
    return p;
}

// ================= +0x008 FUN_1417a9f20 =================
// push SynAttrInfo: build, Init, vt+8 send, dtor.
void CSyndicateLogic::Slot008PushSynAttrInfo(
    uint32_t uUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    char acMsg[0x2080];           // CMsg local_418[1040]
    CtorCMsgSynAttrInfo(acMsg);
    uint64_t uOk = g_fnT1MsgInitA(acMsg, 0, 0);
    if ((char)uOk == 0) {
        g_fnT1LogError("syndicate.cpp");
    } else {
        void* pObj = *(void**)(pcL + 8);
        void** pVt = *(void***)pObj;
        ((void (*)(void*, uint32_t, void*))pVt[1])(
            pObj, uUser, acMsg);
    }
    g_fnT1MsgDtorA(acMsg);
}

// ================= +0x010 FUN_1417a9fc0 =================
uint64_t CSyndicateLogic::Slot010DestroySoon(
    int32_t nUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    // param_1 is longlong*: [1] the mgr box, [2] the map
    void* pBox = *(void**)(pcL + 8);
    void** pBoxVt = *(void***)pBox;
    ((void (*)(void*))pBoxVt[0x18 / 8])(pBox);
    uint32_t uId = ((uint32_t (*)(void*, int32_t))
        (*(void***)pBox)[0x1f8 / 8])(pBox, nUser);
    int64_t lMem = LeagueMemberLookup(
        *(void**)(pcL + 0x10), uId);
    if (lMem != 0) {
        g_fnT1DelRoleSoon((void*)lMem, (uint32_t)nUser);
        int64_t lDays = g_fnT1GetDestroyDays((void*)lMem);
        if (lDays < 1) {
            void* pIv = g_fnStringMgrInstance();
            const char* pcStr = (const char*)
                g_fnStringMgrGetStr(pIv,
                    "STR_DESTROY_SYNDICATE_SOON");
            void** pVt2 = *(void***)pBox;
            ((void (*)(void*, int32_t, uint32_t,
                const char*))pVt2[2])(pBox, nUser,
                0x7db, pcStr);
        }
    }
    int32_t nOpt = g_fnT1OptGet(
        *(void**)(pcL + 0x10), 0x40e);
    if (nOpt != 0) {
        char acMsg[0x2190];   // CMsg local_438[1072]
        CtorCMsgSyndicate(acMsg);
        uint64_t uOk = g_fnT1MsgInitD(acMsg, 0x11, nOpt);
        if ((char)uOk == 0) {
            g_fnT1LogError("syndicate.cpp");
        } else {
            ((void (*)(void*, int32_t, void*))
                (*(void***)pBox)[1])(pBox, nUser, acMsg);
        }
        g_fnA84MsgDtor(acMsg);
    }
    nOpt = g_fnT1OptGet(*(void**)(pcL + 0x10), 1000);
    if (nOpt != 0) {
        char acMsg[0x2190];
        CtorCMsgSyndicate(acMsg);
        uint64_t uOk = g_fnT1MsgInitD(acMsg, 0x12, nOpt);
        if ((char)uOk == 0) {
            g_fnT1LogError("syndicate.cpp");
        } else {
            ((void (*)(void*, int32_t, void*))
                (*(void***)pBox)[1])(pBox, nUser, acMsg);
        }
        g_fnA84MsgDtor(acMsg);
    }
    return 1;
}

// ================= +0x018 FUN_1417aa170 =================
void CSyndicateLogic::Slot018PushMemberInfo(
    uint32_t uUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    char acMsg[0x2080];
    uint32_t aData[10];           // local_48[10]
    memset(aData, 0, 0x28);
    int64_t lMem = 0;
    int64_t lRec = LogRecMapFind(
        *(void**)(pcL + 0x18), uUser);
    if (lRec != 0) {
        uint64_t uId = g_fnA84GetSynId((void*)lRec);
        lMem = LeagueMemberLookup(
            *(void**)(pcL + 0x10), (uint32_t)uId);
        g_fnT1RecGetData((void*)lRec, aData);
    }
    CtorCMsgSynAttrInfo(acMsg);
    uint64_t uOk = g_fnT1MsgInitA(acMsg, (int64_t)(intptr_t)aData,
                                  lMem);
    if ((char)uOk == 0) {
        g_fnT1LogError("syndicate.cpp");
    } else {
        void* pObj = *(void**)(pcL + 8);
        ((void (*)(void*, uint32_t, void*))
            (*(void***)pObj)[1])(pObj, uUser, acMsg);
    }
    g_fnT1MsgDtorA(acMsg);
}

// ================= +0x020 FUN_1417aa280 =================
void CSyndicateLogic::Slot020PushAttrChange(
    int32_t nWho, int32_t nWhat, const char* pName) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    if (((nWho != 0) && (nWhat != 0)) &&
        (pName != (const char*)0)) {
        char acMsg[0x2080];
        CtorCMsgSynAttrInfo(acMsg);
        uint64_t uOk = g_fnT1MsgInitB(acMsg, nWhat, pName);
        if ((char)uOk != 0) {
            void* pObj = *(void**)(pcL + 8);
            ((void (*)(void*, int32_t, void*))
                (*(void***)pObj)[1])(pObj, nWho, acMsg);
        }
        g_fnT1MsgDtorA(acMsg);
    }
}

// ================= +0x028 FUN_1417aa320 =================
uint8_t CSyndicateLogic::Slot028PushProffer(
    uint32_t uUser, int64_t lA, int64_t lB) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    int64_t lRec = LogRecMapFind(
        *(void**)(pcL + 0x18), uUser);
    if (lRec == 0) return 0;
    char acMsg[0x2080];
    CtorCMsgSynProffer(acMsg);
    uint64_t uOk = g_fnT1MsgInitC(acMsg, 0x3ff, (void*)lRec);
    if ((char)uOk == 0) {
        g_fnT1MsgDtorC(acMsg);
        return 0;
    }
    void* pObj = *(void**)(pcL + 8);
    uint8_t uR = (uint8_t)((uint8_t (*)(
        void*, uint32_t, void*))(*(void***)pObj)[1])(
        pObj, uUser, acMsg);
    g_fnT1MsgDtorC(acMsg);
    return uR;
}

// ================= +0x030 FUN_1417aa3c0 =================
uint64_t CSyndicateLogic::Slot030Donate(
    uint32_t uUser, int64_t lMoney) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    if (lMoney == 0) {
        g_fnT1LogError("syndicate.cpp");
        return 0;
    }
    int64_t lRec = LogRecMapFind(
        *(void**)(pcL + 0x18), uUser);
    if (lRec == 0) return 0;
    uint64_t uId = g_fnA84GetSynId((void*)lRec);
    int64_t lMem = LeagueMemberLookup(
        *(void**)(pcL + 0x10), (uint32_t)uId);
    if (lMem == 0) return 0;
    if (!g_fnT1IsLowMoney((void*)lMem)) {
        void* pObj = *(void**)(pcL + 8);
        return ((uint64_t (*)(void*, uint32_t, int64_t,
            uint32_t))(*(void***)pObj)[0x30 / 8])(
            pObj, (uint32_t)uId, lMoney, uUser);
    }
    void* pIv = g_fnStringMgrInstance();
    const char* pcStr = (const char*)g_fnStringMgrGetStr(
        pIv, "STR_TOO_LOWER_SYN_MONEY");
    void* pObj = *(void**)(pcL + 8);
    ((void (*)(void*, uint32_t, const char*))
        (*(void***)pObj)[3])(pObj, uUser, pcStr);
    return 0;
}

// ================= +0x040 FUN_1417aa4b0 =================
uint64_t CSyndicateLogic::Slot040Fwd88() {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    void* pObj = *(void**)(pcL + 8);
    return ((uint64_t (*)(void*))(
        *(void***)pObj)[0x88 / 8])(pObj);
}

// ================= +0x048 FUN_1417aa4e0 =================
void CSyndicateLogic::Slot048MemberOnline(
    uint32_t uUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    int64_t lMem = LeagueMemberLookup(
        *(void**)(pcL + 0x10), uUser);
    if (lMem == 0) return;
    g_fnT1MemberOnline((void*)lMem);
}

// ================= +0x058 FUN_1417aa510 =================
uint64_t CSyndicateLogic::Slot058LogRecSynId(
    uint32_t uUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    int64_t lRec = LogRecMapFind(
        *(void**)(pcL + 0x18), uUser);
    if (lRec == 0) return 0;
    // ORIGINAL: uVar2 = FUN_141785d00(plVar1);
    //   return CONCAT71((int7)(uVar2 >> 8), 1);
    uint64_t u = g_fnT1LogRecSynId((void*)lRec);
    return (u & 0xffffffffffffff00ULL) | 1;
}

// ================= +0x068 FUN_1417b6620 =================
uint64_t CSyndicateLogic::Slot068RankSwap(
    uint32_t uA, uint32_t uB) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    int64_t lRecA = LogRecMapFind(
        *(void**)(pcL + 0x18), uA);
    if (lRecA != 0) g_fnT1FlagClear(lRecA, 0);
    int64_t lRecB = LogRecMapFind(
        *(void**)(pcL + 0x18), uB);
    if (lRecB == 0) return 0;
    g_fnT1FlagClear(lRecB, 0);
    if (lRecA == 0) return 0;
    uint64_t uIdA = g_fnA84GetSynId((void*)lRecA);
    uint32_t uIdALo = (uint32_t)uIdA;
    if (uIdALo == 0) return 0;
    uint64_t uIdB = g_fnA84GetSynId((void*)lRecB);
    if (uIdALo != (uint32_t)uIdB) return 0;
    int64_t lMem = LeagueMemberLookup(
        *(void**)(pcL + 0x10), uIdALo);
    if (lMem == 0) return 0;
    uint64_t uConfA = g_fnT1IsConfirmed((void*)lRecA);
    uint64_t uConfB;
    if (((char)uConfA == 0 &&
        (uConfB = g_fnT1IsConfirmed((void*)lRecB),
         (char)uConfB == 0)) || lRecA == 0) {
        return 1;
    }
    void* pObj = *(void**)(pcL + 8);
    uint32_t uParam = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pObj)[0x328 / 8])(pObj, uIdALo);
    g_fnA84RankSetMisc((void*)lMem, (void*)lRecB, 200,
                       uParam, "");
    g_fnA84SetMemberRank((void*)lMem, (void*)lRecB, 200);
    g_fnA84RecordUpdate(
        *(void**)(pcL + 0x10), (void*)lRecB, (void*)lMem,
        uParam);
    // RAW: uVar5 = FUN_1417c6bd0(...); the return
    // encoded CONCAT71((int7)(uVar5 >> 8), 1) -> 1
    return 1;
}

// ================= +0x070 FUN_1417abe60 =================
void CSyndicateLogic::Slot070SetPlayer(
    uint32_t uA, uint32_t uB) {
    void* pLogic = this;
    g_fnT1SetPlayer(*(void**)((char*)pLogic + 0x10),
                     uA, uB);
}

// ================= +0x078 FUN_1417ab080 =================
bool CSyndicateLogic::Slot078IsRank1000() {
    void* pLogic = this;
    // ORIGINAL: (*(p+0) obj) vt+0xf8 — the FIRST deref
    // on the logic itself: `**(p+0)`. The logic's +0
    // is the vtable: *(*(p+0)+0xf8)(...)
    void** pVt = *(void***)pLogic;
    int32_t n = ((int32_t (*)())pVt[0xf8 / 8])();
    return n == 1000;
}

// ================= +0x080 FUN_1417ab0a0 =================
void CSyndicateLogic::Slot080RankClear() {
    void* pLogic = this;
    void** pVt = *(void***)pLogic;
    int32_t n = ((int32_t (*)())pVt[0xf8 / 8])();
    g_fnT1RankClear(n);
}

// ================= +0x088 FUN_1417ab0c0 =================
bool CSyndicateLogic::Slot088IsRank3de() {
    void* pLogic = this;
    void** pVt = *(void***)pLogic;
    int32_t n = ((int32_t (*)())pVt[0xf8 / 8])();
    return n == 0x3de;
}

// ================= +0x090 FUN_1417ab0e0 =================
bool CSyndicateLogic::Slot090IsRank37a() {
    void* pLogic = this;
    void** pVt = *(void***)pLogic;
    int32_t n = ((int32_t (*)())pVt[0xf8 / 8])();
    return n == 0x37a;
}

// ================= +0x098 FUN_1417ab100 =================
int64_t CSyndicateLogic::Slot098AssemblymanGate() {
    void* pLogic = this;
    void** pVt = *(void***)pLogic;
    uint64_t u = ((uint64_t (*)())pVt[0xf8 / 8])();
    int32_t n = (int32_t)u;
    uint64_t uHi = u & 0xffffffffffffff00ULL;
    if (((((n != 0x35b) && (n != 0x35a)) &&
          (n != 0x359)) &&
         ((n != 0x358 && (n != 0x357)))) &&
        ((n != 0x356 &&
          ((n != 0x355 && (n != 0x354))))) &&
        ((n != 0x353 && (n != 0x352)))) {
        return (int64_t)uHi;
    }
    return (int64_t)(uHi | 1);
}

// ================= +0x0a0 FUN_1417ab170 =================
int64_t CSyndicateLogic::Slot0a0Gate2b228a() {
    void* pLogic = this;
    void** pVt = *(void***)pLogic;
    uint64_t u = ((uint64_t (*)())pVt[0xf8 / 8])();
    uint64_t uHi = u & 0xffffffffffffff00ULL;
    if (((int32_t)u != 0x2b2) && ((int32_t)u != 0x28a)) {
        return (int64_t)uHi;
    }
    return (int64_t)(uHi | 1);
}

// ================= +0x0a8 FUN_1417b6e70 =================
uint64_t CSyndicateLogic::OnUserDelRole(
    uint32_t uUser) {
    void* pLogic = this;
    char* pcL = (char*)pLogic;
    // param_1[1] the mgr box, [2] the map, [3] the log map,
    // [10] the acct (+0x50)
    void* pBox = *(void**)(pcL + 8);
    void* pAcct = *(void**)(pcL + 0x50);
    uint32_t uId = ((uint32_t (*)(void*))
        (*(void***)pBox)[0x4a8 / 8])(pBox);
    // RAW: FUN_141767560(acct, uId, user,
    //   CONCAT71((int7)(uVar3 >> 8), 1)) — the byte
    //   slot pattern (the D62 lesson): the low byte 1
    g_fn141767560(pAcct, uId, uUser, 1);
    uId = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pBox)[0x1f8 / 8])(pBox, uUser);
    int64_t lMem = LeagueMemberLookup(
        *(void**)(pcL + 0x10), uId);
    if (lMem == 0) {
        uint64_t uL = MgrUserLeagueId(
            (int64_t)(intptr_t)pAcct, uUser);
        if ((uint32_t)uL == 0) {
            // LAB_1417b6f69: CONCAT71((0 >> 8), 1)
            return 1;
        }
        lMem = (int64_t)(intptr_t)MgrLeagueFind(
            (int64_t)(intptr_t)pAcct, (uint32_t)uL);
        if (lMem == 0) {
            g_fnT1LogError(
                "CSyndicateLogic::OnUserDelRole, "
                "league[%u] is not exist.");
            // RAW: extraout_RAX garbage; the masked 0
            return 0;
        }
        uint64_t uR = g_fnT1DelRole((void*)lMem, uUser);
        if ((char)uR != 0) {
            // LAB: CONCAT71((uR >> 8), 1)
            return (uR & 0xffffffffffffff00ULL) | 1;
        }
        return uR & 0xffffffffffffff00ULL;
    }
    // the found branch: the logic's own vt+0xf8 rank
    void** pVt = *(void***)pLogic;
    uint64_t uRank = ((uint64_t (*)(void*))
        pVt[0xf8 / 8])(pLogic);
    if ((int32_t)uRank != 1000) {
        int64_t lRec = LogRecMapFind(
            *(void**)(pcL + 0x18), uUser);
        g_fnT1QuitFlow(pLogic, (void*)lMem,
            (void*)lRec, "DelRole", 0, 1, 1);
        return 1;
    }
    return uRank & 0xffffffffffffff00ULL;
}



// ---- D92 seams (default null — tests bind them) ----
int64_t (*g_fnLgFind)(void*, uint32_t);
char    (*g_fnLgFindB)(void*, uint32_t);
void    (*g_fnLgClearA)(void*);
void    (*g_fnLgClearB)(void*);
uint64_t(*g_fnLgRankUpd)(void*, void*, void*, uint32_t);
int64_t (*g_fnCtyFind)(void*, uint32_t);
void    (*g_fnCtyPush)(void*, uint32_t, int32_t, int32_t);
void    (*g_fnCtyFwdA)(void*, uint32_t, int16_t, uint32_t);
void    (*g_fnCtyFwdB)(void*, uint32_t, int32_t, uint32_t);
void    (*g_fnCtyFwdC)(void*, uint32_t, int16_t, uint32_t);
void    (*g_fnRecKick)(void*);
void    (*g_fnRecSetA)(void*, int32_t);
void    (*g_fnRecSetB)(void*, int32_t);
void    (*g_fnRecSetC)(void*, int32_t);
void    (*g_fnRecClr)(void*);
uint64_t(*g_fnRecGetX)(void*, int32_t);
uint64_t(*g_fnRecChk)(void*, int32_t);
uint64_t(*g_fnRecGetRank)(void*);
char    (*g_fnRecIsLeader)(void*);
uint64_t(*g_fnA84GetSynId2)(void*);
void    (*g_fnRankSetA)(void*, void*, int32_t);
void    (*g_fnRankSetB)(void*, void*, int32_t, uint32_t, char);
char    (*g_fnLgTest)(void*, char);
uint64_t(*g_fnLgGetX)(void*);
uint64_t(*g_fnLgGetY)(void*);
uint64_t(*g_fnLgZ)(void*, char);
uint64_t(*g_fnLeaveSyn)(void*, void*, void*, const char*, char, char, char);


// ---- D93 seams (default null — tests bind them) ----
uint64_t (*g_fnRecA)(void*, int32_t);
uint64_t (*g_fnRecB)(void*, int32_t, uint64_t, uint64_t);
uint64_t (*g_fnRecC)(void*, int32_t, void*, char);
uint64_t (*g_fnRecD)(void*, int32_t, char);
void     (*g_fnRecE)(void*);
uint64_t (*g_fnRecF)(void*);
uint64_t (*g_fnRecG)(void*);
uint64_t (*g_fnRecH)(void*);
int32_t  (*g_fnRecI)(void*);

// ================= D92 wave 2 (+0x0b0..+0x140) =================

uint64_t CSyndicateLogic::Slot0b0GetSynId(uint32_t uUser) {
    void* pLogic = this;
    if (uUser == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    uint32_t uRankLo = (uint32_t)uRank;
    char bHas = g_fnLgFindB(
        *(void**)((char*)pLogic + 0x10), uRankLo);
    if (!bHas) return 0;
    return uRankLo;
}

void CSyndicateLogic::Slot0b8RecKick(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return;
    g_fnRecKick((void*)lRec);
}

void CSyndicateLogic::Slot0c0RecSet5(uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) {
        int64_t lCty = g_fnCtyFind(
            *(void**)((char*)pLogic + 0x50), uUser);
        if (lCty != 0)
            g_fnCtyPush((void*)lCty, uUser, 5, n);
    } else {
        g_fnRecSetA((void*)lRec, n);
    }
    uint32_t uR = ((uint32_t (*)(void*, uint32_t))
        (*(void***)*(char***)((char*)pLogic + 8))[0x4a8/8])(
        *(void**)((char*)pLogic + 8), uUser);
    if (uR != 0)
        g_fnCtyFwdA(
            *(void**)((char*)pLogic + 0x50), uUser,
            (int16_t)n, uR);
}

void CSyndicateLogic::Slot0c8RecSet9(uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) {
        int64_t lCty = g_fnCtyFind(
            *(void**)((char*)pLogic + 0x50), uUser);
        if (lCty != 0)
            g_fnCtyPush((void*)lCty, uUser, 9, n);
    } else {
        g_fnRecSetB((void*)lRec, n);
    }
    uint32_t uR = ((uint32_t (*)(void*, uint32_t))
        (*(void***)*(char***)((char*)pLogic + 8))[0x4a8/8])(
        *(void**)((char*)pLogic + 8), uUser);
    if (uR != 0)
        g_fnCtyFwdB(
            *(void**)((char*)pLogic + 0x50), uUser, n, uR);
}

void CSyndicateLogic::Slot0d0LgClearA() {
    void* pLogic = this;
    g_fnLgClearA(*(void**)((char*)pLogic + 0x10));
}

uint64_t CSyndicateLogic::Slot0d8LeaderSwap(
    uint32_t uA, uint32_t uB) {
    void* pLogic = this;
    int64_t lRecA = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uA);
    if (lRecA == 0) return 0;
    int64_t lRecB = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uB);
    if (lRecB == 0) return 0;
    uint64_t uRank = g_fnA84GetSynId2((void*)lRecA);
    uint32_t uRankLo = (uint32_t)uRank;
    if (uRankLo == 0) return 0;
    if ((uint32_t)g_fnA84GetSynId2((void*)lRecB) !=
        uRankLo) {
        return 0;
    }
    // the RAW: uVar10 = the last leader flag
    char bLeadA = g_fnRecIsLeader((void*)lRecA);
    char bLeadB = bLeadA;
    if (bLeadA && (bLeadB = g_fnRecIsLeader(
            (void*)lRecB), !bLeadB)) {
        int64_t lLg = g_fnLgFind(
            *(void**)((char*)pLogic + 0x10), uRankLo);
        if (lLg == 0) return 0;
        uint32_t uParam = ((uint32_t (*)(void*, uint32_t))
            (*(void***)*(char***)((char*)pLogic + 8))
                [0x328/8])(
            *(void**)((char*)pLogic + 8), uRankLo);
        g_fnRankSetA((void*)lLg, (void*)lRecB, 200);
        g_fnRankSetB((void*)lLg, (void*)lRecB, 200,
                     uParam, '\0');
        // the verified-old chain
        if (g_fnA84HasOldPos((void*)lRecB)) {
            uint32_t uOld = g_fnA84GetOldId(
                (void*)lRecB);
            int64_t lRecO = LogRecMapFind(
                *(void**)((char*)pLogic + 0x18), uOld);
            if (lRecO != 0 &&
                (char)g_fnT1IsConfirmed((void*)lRecO) &&
                (uint32_t)g_fnA84GetSynId2(
                    (void*)lRecO) == uRankLo) {
                g_fnRankSetA((void*)lLg, (void*)lRecO,
                             200);
                g_fnLgRankUpd(
                    *(void**)((char*)pLogic + 0x10),
                    (void*)lRecO, (void*)lLg, uParam);
            }
        }
        uint64_t uUp = g_fnLgRankUpd(
            *(void**)((char*)pLogic + 0x10),
            (void*)lRecB, (void*)lLg, uParam);
        return ((uUp >> 8) & ~0xffULL) | 1;
    }
    return (uint64_t)(uint8_t)bLeadB << 8;
}

uint8_t CSyndicateLogic::Slot0e0LgClearB() {
    void* pLogic = this;
    g_fnLgClearB(*(void**)((char*)pLogic + 0x10));
    return 1;
}

uint64_t CSyndicateLogic::Slot0f0QuitSyn(
    uint32_t uUser, uint32_t uAmt) {
    void* pLogic = this;
    if (uAmt < 1000000) return 0;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), (uint32_t)uRank);
    if (lLg == 0) return 0;
    uint64_t uRk = g_fnRecGetRank((void*)lRec);
    if ((int)uRk != 0x3de) return 0;
    char bOk = g_fnLgTest((void*)lLg, '\x01');
    if (!bOk) return 0;
    uint64_t uKick = 0; g_fnRecKick((void*)lRec); uKick = 0;
    uint64_t uX = g_fnLgGetX((void*)lLg);
    uint64_t uRet = ((uint64_t (*)(void*, uint32_t,
        uint64_t, char))
        (*(void***)pLogic)[0xe8/8])(
        pLogic, (uint32_t)uX, uKick, 1);
    return uRet;
}

uint64_t CSyndicateLogic::Slot0f8GetRankIfLeague(
    uint32_t uUser) {
    void* pLogic = this;
    if (uUser == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), (uint32_t)uRank);
    if (lLg == 0) return 0;
    return g_fnRecGetRank((void*)lRec);
}

uint64_t CSyndicateLogic::Slot100QuitOrKick(
    uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    char bLead = g_fnRecIsLeader((void*)lRec);
    if (bLead) {
        // the RAW: talk STR_NO_DISBAND via the box
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv, "STR_NO_DISBAND");
        uint64_t uR = ((uint64_t (*)(void*, uint32_t,
            const void*))
            (*(void***)*(char***)((char*)pLogic + 8))
                [0x18/8])(
            *(void**)((char*)pLogic + 8), uUser, pc);
        return uR;
    }
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), (uint32_t)uRank);
    if (lLg == 0) return 0;
    return g_fnLeaveSyn(pLogic, (void*)lLg,
        (void*)lRec, "LeaveSyn", '\0', '\x01', '\0');
}

uint64_t CSyndicateLogic::Slot108RecSet6(
    uint32_t uUser, int32_t n) {
    void* pLogic = this;
    if (uUser == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) {
        int64_t lCty = g_fnCtyFind(
            *(void**)((char*)pLogic + 0x50), uUser);
        if (lCty == 0) return 0;
        g_fnCtyPush((void*)lCty, uUser, 6, n);
    } else {
        g_fnRecSetC((void*)lRec, n);
    }
    uint32_t uR = ((uint32_t (*)(void*, uint32_t))
        (*(void***)*(char***)((char*)pLogic + 8))[0x4a8/8])(
        *(void**)((char*)pLogic + 8), uUser);
    if (uR != 0)
        g_fnCtyFwdC(
            *(void**)((char*)pLogic + 0x50), uUser,
            (int16_t)n, uR);
    return 1;
}

uint64_t CSyndicateLogic::Slot110LgZ(uint32_t uLg, char c) {
    void* pLogic = this;
    if (uLg == 0) { g_fnT1LogError(0); return 0; }
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uLg);
    if (lLg == 0) return 0;
    return g_fnLgZ((void*)lLg, c);
}

uint64_t CSyndicateLogic::Slot128LgGetY(uint32_t uLg) {
    void* pLogic = this;
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uLg);
    if (lLg == 0) return 0;
    return g_fnLgGetY((void*)lLg);
}

void CSyndicateLogic::Slot130RecClr(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return;
    g_fnRecClr((void*)lRec);
}

uint64_t CSyndicateLogic::Slot138RecChkFwd(
    uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    uint64_t uOk = g_fnRecChk((void*)lRec, n);
    char c = (char)uOk;
    if (c != '\0') {
        uint64_t uR = ((uint64_t (*)(void*, uint32_t,
            int32_t))
            (*(void***)pLogic)[0xf0/8])(
            pLogic, uUser, n);
        // CONCAT71((int7)(uR >> 8), c):
        // high bytes from uR, low byte = c
        return (uR & ~0xffULL) |
               (uint64_t)(uint8_t)c;
    }
    // CONCAT71((int7)(uVar3 >> 8), cVar1)
    return (uOk & ~0xffULL) |
           (uint64_t)(uint8_t)c;
}

uint64_t CSyndicateLogic::Slot140RecGetX(
    uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecGetX((void*)lRec, n);
}

// ---- D94 seams (default null — tests bind them) ----
uint64_t (*g_fnLgGetId)(void*);
void*    (*g_fnFlowerA)(void*, int32_t, uint64_t, uint64_t);
void*    (*g_fnFlowerB)(void*, int32_t, uint64_t, uint64_t);
void*    (*g_fnFlowerC)(void*, int32_t, uint64_t, uint64_t);
void*    (*g_fnFlowerD)(void*, int32_t, uint64_t, uint64_t);
int64_t  (*g_fnLgGetFunds)(void*);
void     (*g_fnLgAddFunds)(void*, int64_t);
uint64_t (*g_fnInviteB210)(void*, uint32_t, void*);

// ================= D93 wave 3 (+0x148..+0x188) =================

uint64_t CSyndicateLogic::Slot148RecA(uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecA((void*)lRec, n);
}

uint64_t CSyndicateLogic::Slot150RecB(uint32_t uUser,
    int32_t n, uint64_t uB, uint64_t uC) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecB((void*)lRec, n, uB, uC);
}

uint64_t CSyndicateLogic::Slot158RecC(uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    // RAW: FUN_141788400(rec, n, DAT_1418347c0, 1)
    return g_fnRecC((void*)lRec, n,
        (void*)0x1418347c0, '\x01');
}

uint64_t CSyndicateLogic::Slot160RecD(uint32_t uUser, int32_t n) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecD((void*)lRec, n, '\x01');
}

void CSyndicateLogic::Slot168RecE(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return;
    g_fnRecE((void*)lRec);
}

uint64_t CSyndicateLogic::Slot170RecF(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecF((void*)lRec);
}

uint64_t CSyndicateLogic::Slot178RecG(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecG((void*)lRec);
}

uint64_t CSyndicateLogic::Slot180RecH(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecH((void*)lRec);
}

int32_t CSyndicateLogic::Slot188RecI(uint32_t uUser) {
    void* pLogic = this;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    return g_fnRecI((void*)lRec);
}

// ---- D95 seams (default null — tests bind them) ----
int64_t  (*g_fnLgFindByName)(void*, const char*);
char     (*g_fnLgIsAlly)(void*, uint32_t);
char     (*g_fnLgIsAntag)(void*, uint32_t);
int32_t  (*g_fnLgEnemyCnt)(void*);
int32_t  (*g_fnLgEnemyMax)(void*);
uint32_t (*g_fnLgAddEnemySlot)(void*, uint32_t);
void     (*g_fnLgSetEnemy)(void*, uint32_t, uint32_t);
uint32_t (*g_fnLgFindAllySlot)(void*, int32_t);
void     (*g_fnLgSetAlly)(void*, uint32_t, uint32_t);
uint32_t (*g_fnLgFindAntagSlot)(void*, int32_t);
void*    (*g_fnLgRefresh)(void*);
uint64_t (*g_fnRecGetName)(void*);
int64_t  (*g_fnRecGetMemberNo)(void*);
uint64_t (*g_fnBoxVt1d8)(void*, uint32_t);

// ================= D94 wave 4 (+0x190..+0x1a0) =================

uint64_t CSyndicateLogic::OnFlowerChange(
    uint32_t uUser, int32_t nType, int32_t n,
    uint64_t uB) {
    void* pLogic = this;
    uint64_t uVar7 = (uint64_t)(int64_t)nType;
    uint64_t uVar8 = uB;
    uint64_t uVt = ((uint64_t (*)())
        (*(void***)*(char***)((char*)pLogic + 8))
            [0x1f8/8])();
    uint64_t uRet;
    if ((uint32_t)uVt == 0) {
        // RAW: CONCAT71((int7)(uVar1 >> 8), 1)
        return (uVt & ~0xffULL) | 1;
    }
    int64_t lLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), (uint32_t)uVt);
    if (lLg == 0) {
        g_fnT1LogError(
            "CSyndicateLogic::OnFlowerChange. can't find"
            " syndicate. user[%d] syndicate[%d]");
        return 0;
    }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) { g_fnT1LogError(0); return 0; }
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    uint64_t uLgId = g_fnLgGetId((void*)lLg);
    if ((int32_t)uRank != (int32_t)uLgId) return 0;
    void* pRes = nullptr;
    if (nType == 0) {
        pRes = g_fnFlowerA((void*)lRec, n, uVar7, uVar8);
    } else if (nType == 1) {
        pRes = g_fnFlowerB((void*)lRec, n, uVar7, uVar8);
    } else if (nType == 2) {
        pRes = g_fnFlowerC((void*)lRec, n, uVar7, uVar8);
    } else if (nType == 3) {
        pRes = g_fnFlowerD((void*)lRec, n, uVar7, uVar8);
    } else {
        g_fnT1LogError(
            "ERROR: CUser::SetFlower error flower type %d");
        return 0;
    }
    // RAW: CONCAT71((int7)(puVar5 >> 8), 1)
    return ((uint64_t)pRes & ~0xffULL) | 1;
}

uint8_t CSyndicateLogic::Slot198MoveFunds(
    uint32_t uUser, uint32_t uTo, int64_t lAmt) {
    void* pLogic = this;
    if (uUser == 0) { g_fnT1LogError(0); return 0; }
    if (lAmt < 1)   { g_fnT1LogError(0); return 0; }
    if (uTo == 0)  return 0;
    if (lAmt < 10000) return 0;
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    if (!g_fnRecIsLeader((void*)lRec)) return 0;
    uint64_t uRank = g_fnA84GetSynId2((void*)lRec);
    if ((uint32_t)uRank == uTo) return 0;
    int64_t lFrom = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), (uint32_t)uRank);
    if (lFrom == 0) return 0;
    if (g_fnLgGetFunds((void*)lFrom) < lAmt) return 0;
    int64_t lDest = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uTo);
    if (lDest == 0) return 0;
    g_fnLgAddFunds((void*)lFrom, -lAmt);
    g_fnLgAddFunds((void*)lDest, lAmt);
    return 1;
}

uint64_t CSyndicateLogic::Slot1a0InviteGate(
    uint32_t uUser, uint32_t uWho) {
    void* pLogic = this;
    if (uUser != 0 && uWho != 0) {
        int64_t lRec = LogRecMapFind(
            *(void**)((char*)pLogic + 0x18), uWho);
        if (lRec != 0) {
            char bLead = g_fnRecIsLeader((void*)lRec);
            uint64_t uLead = (uint64_t)(uint8_t)bLead;
            if (bLead) {
                uint64_t uRank =
                    g_fnA84GetSynId2((void*)lRec);
                if ((uint32_t)uRank == 0) {
                    g_fnT1LogError(0);
                    return 0;
                }
                int64_t lLg = g_fnLgFind(
                    *(void**)((char*)pLogic + 0x10),
                    (uint32_t)uRank);
                if (lLg != 0)
                    return g_fnInviteB210(
                        pLogic, uUser, (void*)lLg);
                return 0;
            }
            // RAW: CONCAT71(extraout_var, bVar1)
            return (uLead & ~0xffULL) |
                   (uint64_t)(uint8_t)bLead;
        }
    }
    return 0;
}

// ---- D96 seams (default null — tests bind them) ----
uint32_t (*g_fnA8940)(void*, uint32_t);
void*    (*g_fnSink1Get)(void);
void     (*g_fnSink1OpA)(void*, uint32_t);
void     (*g_fnSink1OpB)(void*, uint32_t, uint32_t, uint32_t);
void     (*g_fnSink1OpC)(void*);
void*    (*g_fnSink2Get)(void);
void     (*g_fnSink2OpA)(void*, int32_t);
void*    (*g_fnSink3Get)(void);
void     (*g_fnSink3OpA)(void*, void*);
void     (*g_fnSink3OpB)(void*, int32_t);
void     (*g_fnSink3OpC)(void*);
void     (*g_fnB4B0)(void*, int32_t, const void*, const void*);

// ================= D95 wave 5 (+0x1a8..+0x1c8) =================

// the box vt+0x88 broadcast (RAW: (**(code**)(boxvt+0x88))(box, id, buf, 0))
static uint64_t BoxVt88Broadcast(void* pBox,
                                 uint32_t uId, const char* psz) {
    // RAW: box is the object at logic+8; its first
    // pointer is the vt
    return ((uint64_t (*)(void*, uint32_t, const char*,
                          uint64_t))
        (*(void***)pBox)[0x88/8])(
            pBox, uId, psz, 0);
}

// the box vt+0x18 tip (RAW: (**(code**)(boxvt+0x18))(box, user, str))
static uint64_t BoxVt18Tip(void* pBox, uint32_t uUser,
                           const void* pv) {
    return ((uint64_t (*)(void*, uint32_t, const void*))
        (*(void***)pBox)[0x18/8])(
            pBox, uUser, pv);
}

uint64_t CSyndicateLogic::Slot1a8SetAntagonize(
    uint32_t uUser, const char* pszName) {
    void* pLogic = this;
    char szBuf[1024];
    if (uUser == 0) { g_fnT1LogError(0); return 0; }
    if (pszName == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    if (!g_fnRecIsLeader((void*)lRec)) return 0;
    uint32_t uMyLg =
        (uint32_t)g_fnA84GetSynId2((void*)lRec);
    int64_t lMyLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uMyLg);
    if (lMyLg == 0) return 0;
    int64_t lTgtLg = g_fnLgFindByName(
        *(void**)((char*)pLogic + 0x10), pszName);
    if (lTgtLg == 0) return 0;
    uint32_t uTgtLg =
        (uint32_t)g_fnLgGetId((void*)lTgtLg);
    if (uMyLg == uTgtLg) return 0;
    void* pBox = *(void**)((char*)pLogic + 8);
    if (g_fnLgIsAlly((void*)lMyLg, uTgtLg)) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pIv,
            "STR_SET_ALLY_SYNDICATE_FRIENDLY");
        return BoxVt18Tip(pBox, uUser, pv);
    }
    if (g_fnLgIsAntag((void*)lMyLg, uTgtLg)) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pIv,
            "STR_SET_ANTAGONIZE_ALREADY_SET");
        return BoxVt18Tip(pBox, uUser, pv);
    }
    if (g_fnLgEnemyMax((void*)lMyLg) <=
        g_fnLgEnemyCnt((void*)lMyLg)) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pIv,
            "STR_OVER_ENEMY_SYNDICATE_COUNT");
        return BoxVt18Tip(pBox, uUser, pv);
    }
    uint32_t uSlot = g_fnLgAddEnemySlot(
        (void*)lMyLg, uTgtLg);
    if (uSlot == 0xffffffff) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pIv,
            "STR_SET_ANTAGONIZE_FULL");
        return BoxVt18Tip(pBox, uUser, pv);
    }
    g_fnLgSetEnemy((void*)lMyLg, uSlot, uTgtLg);
    uint64_t uName = g_fnRecGetName((void*)lRec);
    int64_t lNo = g_fnRecGetMemberNo((void*)lRec);
    {
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_SET_ANTAGONIZE_SUCCESS");
        snprintf(szBuf, 0x400, pc,
                 (int64_t)lNo, pszName);
        BoxVt88Broadcast(pBox, uMyLg, szBuf);
    }
    g_fnLgRefresh((void*)lTgtLg);
    {
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_SET_ANTAGONIZE_SUCCESS_TO_TARGET");
        snprintf(szBuf, 0x400, pc,
                 (uint32_t)uName, (char*)lNo);
        uint64_t uR = BoxVt88Broadcast(pBox,
            uTgtLg, szBuf);
        // RAW: CONCAT71((int7)(uVar7 >> 8), 1)
        return ((uR >> 8) & ~0xffULL) | 1;
    }
}

uint8_t CSyndicateLogic::Slot1b0ClearAlly(
    uint32_t uUser, const char* pszName) {
    void* pLogic = this;
    char szBuf[1024]; szBuf[0] = 0;
    if (pszName == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    if (!g_fnRecIsLeader((void*)lRec)) return 0;
    uint32_t uMyLg =
        (uint32_t)g_fnA84GetSynId2((void*)lRec);
    int64_t lMyLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uMyLg);
    if (lMyLg == 0) return 0;
    int64_t lTgtLg = g_fnLgFindByName(
        *(void**)((char*)pLogic + 0x10), pszName);
    if (lTgtLg == 0) return 0;
    int32_t nTgtLg =
        (int32_t)g_fnLgGetId((void*)lTgtLg);
    uint32_t uSlot = g_fnLgFindAllySlot(
        (void*)lMyLg, nTgtLg);
    if (uSlot == 0xffffffff) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(
            pIv, "STR_NOT_ALLY");
        void* pBox = *(void**)((char*)pLogic + 8);
        BoxVt18Tip(pBox, uUser, pv);
        return 0;
    }
    g_fnLgSetAlly((void*)lMyLg, uSlot, 0);
    uint32_t uOther = g_fnLgFindAllySlot(
        (void*)lTgtLg, (int32_t)uMyLg);
    if (uOther != 0xffffffff)
        g_fnLgSetAlly((void*)lTgtLg, uOther, 0);
    szBuf[0] = 0;
    memset(szBuf + 1, 0, 0x3ff);
    void* pBox = *(void**)((char*)pLogic + 8);
    void* pvTgtName = (void*)g_fnLgRefresh(
        (void*)lTgtLg);
    int64_t lNo = g_fnRecGetMemberNo((void*)lRec);
    g_fnRecGetName((void*)lRec);
    {
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_CLEAR_ALLY_SUCCESS");
        snprintf(szBuf, 0x400, pc, pvTgtName, lNo);
        BoxVt88Broadcast(pBox, uMyLg, szBuf);
    }
    lNo = g_fnRecGetMemberNo((void*)lRec);
    uint64_t uName = g_fnRecGetName((void*)lRec);
    g_fnLgRefresh((void*)lMyLg);
    {
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_CLEAR_ALLY_SUCCESS_TO_TARGET");
        snprintf(szBuf, 0x400, pc, (uint32_t)uName,
                 (void*)lNo);
        BoxVt88Broadcast(pBox, (uint32_t)nTgtLg,
            szBuf);
    }
    return 1;
}

uint64_t CSyndicateLogic::Slot1b8ClearAntagonize(
    uint32_t uUser, const char* pszName) {
    void* pLogic = this;
    char szBuf[1024];
    if (pszName == 0) { g_fnT1LogError(0); return 0; }
    int64_t lRec = LogRecMapFind(
        *(void**)((char*)pLogic + 0x18), uUser);
    if (lRec == 0) return 0;
    if (!g_fnRecIsLeader((void*)lRec)) return 0;
    uint32_t uMyLg =
        (uint32_t)g_fnA84GetSynId2((void*)lRec);
    int64_t lMyLg = g_fnLgFind(
        *(void**)((char*)pLogic + 0x10), uMyLg);
    if (lMyLg == 0) return 0;
    int64_t lTgtLg = g_fnLgFindByName(
        *(void**)((char*)pLogic + 0x10), pszName);
    if (lTgtLg == 0) return 0;
    int32_t nTgtLg =
        (int32_t)g_fnLgGetId((void*)lTgtLg);
    uint32_t uSlot = g_fnLgFindAntagSlot(
        (void*)lMyLg, nTgtLg);
    if (uSlot == 0xffffffff) {
        void* pIv = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(
            pIv, "STR_NOT_ANTAGONIZE");
        void* pBox = *(void**)((char*)pLogic + 8);
        return BoxVt18Tip(pBox, uUser, pv);
    }
    g_fnLgSetEnemy((void*)lMyLg, uSlot, 0);
    uint64_t uName = g_fnRecGetName((void*)lRec);
    int64_t lNo = g_fnRecGetMemberNo((void*)lRec);
    void* pBox = *(void**)((char*)pLogic + 8);
    {
        uint64_t uVt = g_fnBoxVt1d8(pBox, uUser);
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_CLEAR_ANTAGONIZE_SUCCESS");
        snprintf(szBuf, 0x400, pc, uVt, pszName);
        BoxVt88Broadcast(pBox, uMyLg, szBuf);
    }
    g_fnLgRefresh((void*)lMyLg);
    {
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_CLEAR_ANTAGONIZE_SUCCESS_TO_TARGET");
        snprintf(szBuf, 0x400, pc, (uint32_t)uName,
                 (char*)lNo);
        uint64_t uR = BoxVt88Broadcast(pBox,
            (uint32_t)nTgtLg, szBuf);
        // RAW: CONCAT71((int7)(uVar4 >> 8), 1)
        return ((uR >> 8) & ~0xffULL) | 1;
    }
}

uint64_t CSyndicateLogic::Slot1c0IsAllyGate(
    uint32_t uLg, uint32_t uOther) {
    void* pLogic = this;
    if (uOther != 0 && uLg != 0) {
        int64_t lLg = g_fnLgFind(
            *(void**)((char*)pLogic + 0x10), uLg);
        if (lLg != 0)
            return (uint64_t)(uint8_t)g_fnLgIsAlly(
                (void*)lLg, uOther);
    }
    return 0;
}

uint64_t CSyndicateLogic::Slot1c8IsAntagGate(
    uint32_t uLg, uint32_t uOther) {
    void* pLogic = this;
    if (uOther != 0 && uLg != 0) {
        int64_t lLg = g_fnLgFind(
            *(void**)((char*)pLogic + 0x10), uLg);
        if (lLg != 0)
            return (uint64_t)(uint8_t)g_fnLgIsAntag(
                (void*)lLg, uOther);
    }
    return 0;
}

// ---- D97 seams (default null — tests bind them) ----
void     (*g_fnSink3OpD)(void*);
void     (*g_fnSub38Cdc0)(void*, const void*, const void*, int32_t, int32_t);
void     (*g_fnSub28Cd0)(void*, uint32_t, uint32_t);
uint64_t (*g_fnSub28F980)(void*, int32_t, int32_t);
void     (*g_fnSub48D4670)(void*, uint32_t, uint32_t, const char*, uint32_t, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
void     (*g_fnSub48D3100)(void*, int32_t, uint64_t);
char     (*g_fnLgInviteOk)(void*, uint32_t, uint64_t, uint64_t);
char     (*g_fnSub9D3530)(void*, uint32_t, uint32_t);
char     (*g_fnLgMoneyLow)(void*);
char     (*g_fnLgMemberFull)(void*);
uint64_t (*g_fnLgLeaderRank)(void*);
void     (*g_fnSub10Call)(void*, uint32_t, uint32_t);
void     (*g_fnB19C0)(void*, uint32_t, char, uint64_t);
char     (*g_fnB8470)(void*, void*, uint32_t, int32_t, int32_t, char);
void     (*g_fnLgF4E0)(void*);
void     (*g_fnDelayMs)(uint32_t);
void     (*g_fnLgAd50)(void*, uint32_t);
void     (*g_fnSub9D3680)(void*, int32_t, int32_t);
uint32_t (*g_fnLogicVt510)(void*, uint32_t);
char     (*g_fnLogicVt78)(void*);

// ================= D96 wave 6 (+0x1d0..+0x208) =================

uint32_t CSyndicateLogic::Slot1d0Sub20Delegate(
    uint32_t u) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x20) != 0)
        return g_fnA8940(
            *(void**)((char*)pLogic + 0x20), u);
    return 0;
}

void CSyndicateLogic::Slot1d8Sink1OpA(uint32_t u) {
    void* pObj = g_fnSink1Get();
    g_fnSink1OpA(pObj, u);
}

void CSyndicateLogic::Slot1e0Sink1OpB(
    uint32_t u, uint32_t v, uint32_t w) {
    void* pObj = g_fnSink1Get();
    g_fnSink1OpB(pObj, u, v, w);
}

void CSyndicateLogic::Slot1e8Sink1OpC() {
    void* pObj = g_fnSink1Get();
    g_fnSink1OpC(pObj);
}

void CSyndicateLogic::Slot1f0Sink2OpA(int32_t n) {
    void* pObj = g_fnSink2Get();
    g_fnSink2OpA(pObj, n);
}

void CSyndicateLogic::Slot1f8Sink3Loop(
    uint32_t u, void* p) {
    void* pCur = p;
    // RAW: if ((0 < (int)param_2) && (0 < (int)param_2))
    // — the doubled check kept verbatim
    if ((int32_t)u > 0 && (int32_t)u > 0) {
        uint64_t uN = u;
        do {
            void* pObj = g_fnSink3Get();
            g_fnSink3OpA(pObj, pCur);
            pCur = (char*)pCur + 0x48;
            uN--;
        } while (uN != 0);
    }
}

void CSyndicateLogic::Slot200Sink3OpB(int32_t n) {
    void* pObj = g_fnSink3Get();
    g_fnSink3OpB(pObj, n);
}

void CSyndicateLogic::Slot208B4b0ThenSink3(
    const void* p, const void* q) {
    void* pLogic = this;
    g_fnB4B0(*(void**)((char*)pLogic + 0x30), 3, p, q);
    void* pObj = g_fnSink3Get();
    g_fnSink3OpC(pObj);
}

// ---- D111 seams (default null — tests bind them) ----
char     (*g_fn797750)(void*, uint32_t);
void*    (*g_fn78C9F0)(void*, void*);
char     (*g_fn787300)(void*);
uint64_t (*g_fn785DC0)(void*);
char     (*g_fn786960)(void*);
void     (*g_fn79F650)(void*, void*, int32_t);
void     (*g_fn7C6BD0)(void*, void*, void*, uint32_t);
char     (*g_fn787390)(void*);
uint64_t (*g_fn787380)(void*);
void     (*g_fn79FA60)(void*, uint32_t);
void     (*g_fn78F900)(void*, const char*);
void     (*g_fn78F960)(void*, uint32_t);
char     (*g_fn7DB630)(void*, int32_t, int32_t, uint32_t, void*);
void     (*g_fn79E020)(void*);
void*    (*g_fn796390)(void*, int32_t);
void     (*g_fn786E30)(void*, int32_t);

// ---- D110 seams (default null — tests bind them) ----
void     (*g_fn787370)(void*, uint32_t);
int32_t  (*g_fn7AEA90)(void*, void*, void*);
int64_t  (*g_fn7862C0)(void*);
void     (*g_fn785F00)(void*, int32_t, void*, int64_t);
char     (*g_fn78E590)(void*);
int64_t  (*g_fn7867D0)(void*);
int64_t  (*g_fn7A05D0)(void*, void*, void*);
void     (*g_fn7A0760)(void*, void*, int32_t, uint32_t, char);
uint64_t (*g_fn7AEBB0)(void*, void*, void*, const char*, char, char, char);
void     (*g_fn7DB2B0)(void*);
char     (*g_fn7DB3A0)(void*, int32_t, int32_t);
uint64_t (*g_fn7DB330)(void*);

// ---- D109 seams (default null — tests bind them) ----
uint64_t (*g_fn7CEC20)(void*, uint32_t);
void     (*g_fn77D180)(void*, uint32_t, int32_t);
void     (*g_fn77BEB0)(void*, uint32_t, int32_t, int64_t);
void*    (*g_fn73F9C0)();
void     (*g_fn73F4B0)(void*, uint32_t);
void     (*g_fn7D4870)(void*, uint32_t, void*, int64_t);
char     (*g_fn7CD250)(void*, const char*);

// ---- D108 seams (default null — tests bind them) ----
uint32_t (*g_fn78E4A0)(void*, int32_t);
uint32_t (*g_fn78E400)(void*, int32_t);
uint64_t (*g_fn78F4F0)(void*);
uint64_t (*g_fn79BF80)(void*, int64_t);
uint64_t (*g_fn7CAB90)(void*);
uint64_t (*g_fn78FB00)(void*, uint8_t);
uint64_t (*g_fn78F5B0)(void*);
uint32_t (*g_fn786440)(void*);
void     (*g_fn786620)(void*, int32_t);
void     (*g_fn7DD6E0)(void*);
char     (*g_fn7DD790)(void*, int32_t, void*);
uint64_t (*g_fn7DD730)(void*);
void     (*g_fn7CFA30)(void*, void*);
void     (*g_fn79DB30)(void*, int32_t);
uint32_t (*g_fn7CE230)(void*, uint32_t, const char*,
                       uint32_t, int32_t, uint32_t);
void     (*g_fn77C4F0)(void*, uint32_t);
uint64_t (*g_fn7B9010)(void*, uint32_t, uint32_t);
void     (*g_fn7CAD90)(void*, uint32_t);
int64_t  (*g_fn7C8AA0)(void*, const char*);
uint64_t (*g_fn7CADE0)(void*, uint32_t);
uint64_t (*g_fn78F550)(void*);
uint64_t (*g_fn78FA70)(void*, int32_t);

// ---- D107 seams (default null — tests bind them) ----
void     (*g_fn7CB000)(void*, uint32_t);
int64_t  (*g_fn78F4E0)(void*);
void     (*g_fn7873A0)(int32_t);
int32_t  (*g_fn798800)(void*);
uint32_t (*g_fn78F400)(void*);
uint64_t (*g_fn78F410)(void*);
void     (*g_fn76ACF0)(void*, int32_t, uint32_t, int32_t,
                       uint16_t, uint16_t);

// ---- D106 seams (default null — tests bind them) ----
uint32_t (*g_fn75EE00)(void*, uint32_t);
uint64_t (*g_fn74EF00)(void*, uint32_t);
uint64_t (*g_fn74EF20)(void*, int32_t);
void     (*g_fn74ED30)(void*, uint32_t);
void     (*g_fn74EBE0)(void*, uint32_t, int32_t);
void     (*g_fn74EC50)(void*, uint32_t, int32_t);
uint64_t (*g_fn74ECC0)(void*, uint32_t, int32_t);
void     (*g_fn768020)(void*, uint16_t);
void     (*g_fn7524D0)(void*, int32_t, uint32_t);

// ---- D105 seams (default null — tests bind them) ----
void  (*g_fn743E80)(void*, int32_t, int32_t, char);
void  (*g_fn74D3E0)(void*);
void  (*g_fn7B92B0)(void*, uint32_t, uint32_t, uint32_t,
                    const char*);

// ---- D104 seams (default null — tests bind them) ----
void  (*g_fn74D490)(void*, uint32_t);
void  (*g_fn7C1180)(void*, uint32_t, uint32_t, uint64_t);
void  (*g_fn76ACA0)(void*, uint32_t);
char  (*g_fn79E6D0)(void*, void*);

// ---- D103 seams (default null — tests bind them) ----
uint64_t (*g_fn743C80)(void*);
char     (*g_fn7977D0)(void*, uint32_t);
char     (*g_fn763920)(void*, uint32_t);
void     (*g_fn74E7E0)(void*);
int32_t  (*g_fn76CA70)(void*, uint32_t, int32_t,
                       uint32_t);

// ---- D102 seams (default null — tests bind them) ----
int64_t  (*g_fn75EB70)(void*, const char*);
void*    (*g_fn78C8E0)(void*, uint32_t);
char     (*g_fn7868C0)(void*);
uint64_t (*g_fn785EA0)(void*);
int32_t  (*g_fn74E740)(void*);
uint64_t (*g_fn78F270)(void*);
char*    (*g_fn787120)(void*);
void*    (*g_fn76F7F0)(void*, uint32_t, const char*,
                       char, uint32_t, const char*);
void     (*g_fn74DCD0)(void*, int32_t);
char     (*g_fn7903D0)(void*, int32_t);
void     (*g_fn7B0EA0)(void*, uint32_t, char);

// ---- D101 seams (default null — tests bind them) ----
void     (*g_fn76FE50)(void*, int32_t*);
void     (*g_fn76ACE0)(void*);
void     (*g_fn763DD0)(void*, int32_t, int32_t, const char*);
void     (*g_fn764000)(void*, int32_t, int32_t, const char*);
void     (*g_fn764230)(void*, int32_t, int32_t, const char*);
void     (*g_fn764300)(void*, uint32_t, int32_t);
void     (*g_fn76EFC0)(void*, int32_t, int32_t, int32_t);
void     (*g_fn76F190)(void*);
void     (*g_fn745920)(void*, void*);
void     (*g_fn7645C0)(void*, uint32_t);
char     (*g_fn74EA40)(void*);
void     (*g_fn74EA30)(void*, int32_t);
uint64_t (*g_fn790390)(void*);
void*    (*g_fn78F470)(void*);
uint64_t (*g_fn745520)(void*);

// ---- D100 seams (default null — tests bind them) ----
int32_t  (*g_fn74E920)(void*);
int32_t  (*g_fn74E930)(void*);
int*     (*g_fnCQLanguageGet)(void);
int32_t  (*g_fn7B0370)(void*, uint32_t);
void     (*g_fn743F90)(void*, int32_t, const char*, char);
uint32_t (*g_fnTimeGet)(int32_t);
uint64_t (*g_fnCMsgInit6820)(void*, int32_t, const char*,
                             uint32_t, int32_t, int32_t);
void     (*g_fnCStrFormat215d0)(void*, const char*,
                                uint64_t, uint64_t);
void     (*g_fnStrCopy)(char*, const char*,
                         unsigned long);

// ---- D99 seams (default null — tests bind them) ----
void     (*g_fnMgrCdfD0)(void*);
int      (*g_fn647E0)(void*, uint32_t);
uint32_t (*g_fn74E3F0)(void*);
void*    (*g_fn7630D0)(void*, uint32_t);
void     (*g_fn743D10)(void*);
void     (*g_fn743E60)(void*);
void*    (*g_fn743Dd0)(void*);
void*    (*g_fn743D70)(void*);
uint32_t (*g_fn763C80)(void*, uint32_t);
void     (*g_fn76EE60)(void*, uint32_t, int32_t);
void     (*g_fn76FBF0)(void*, uint32_t, int32_t,
                       uint64_t, char);
uint64_t (*g_fn763680)(void*, uint32_t);
uint64_t (*g_fn78F2D0)(void*);
void     (*g_fn76ECF0)(void*, uint32_t, int32_t);
uint32_t (*g_fn7B9220)(void*, uint32_t, uint32_t);
void     (*g_fn7B52D0)(void*, uint32_t, uint32_t, void*);
void     (*g_fnCMsgCtor6640)(void*);
uint64_t (*g_fnCMsgInit6790)(void*, int32_t,
                             uint32_t, uint32_t, uint32_t);
void     (*g_fnCMsgDtor66C0)(void*);

// ---- D98 seams (default null — tests bind them) ----
void     (*g_fnInvalidParam)(void);
void     (*g_fnMyLogSave)(const char*, const char*);
char     (*g_fnLgBf80)(void*, uint64_t);
uint64_t (*g_fnLgF550)(void*);
char     (*g_fnLgFa70)(void*, uint64_t);
void     (*g_fnIterC50)(void*, void*);
void     (*g_fnIter730)(void*);

// ================= D97 wave 7 (+0x210..+0x258) =================

void CSyndicateLogic::Slot210Flag60Sink3() {
    void* pLogic = this;
    if (*((char*)pLogic + 0x60) != 0) {
        void* pObj = g_fnSink3Get();
        g_fnSink3OpD(pObj);
    }
}

void CSyndicateLogic::Slot220Sub38Cdc0(
    int32_t a, int32_t b, const void* p, const void* q) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x38) != 0)
        g_fnSub38Cdc0(
            *(void**)((char*)pLogic + 0x38), p, q, a, b);
}

void CSyndicateLogic::Slot228Sub28Cd0(
    uint32_t a, uint32_t b) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x28) != 0)
        g_fnSub28Cd0(*(void**)((char*)pLogic + 0x28),
                     a, b);
}

uint64_t CSyndicateLogic::Slot230Sub28F980(
    int32_t a, int32_t b) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x28) != 0)
        return g_fnSub28F980(
            *(void**)((char*)pLogic + 0x28), a, b);
    return 0;
}

void CSyndicateLogic::Slot238Sub30B4b0(
    uint32_t a, const void* p, const void* q) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x30) != 0)
        g_fnB4B0(*(void**)((char*)pLogic + 0x30), a,
                 p, q);
}

void CSyndicateLogic::Slot240Sub48D4670(
    uint32_t a, uint32_t b, const char* s, uint32_t c,
    int16_t s1, int16_t s2, int16_t s3, int16_t s4,
    int16_t s5, int16_t s6) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x48) == 0) {
        g_fnT1LogError(0); return;
    }
    g_fnSub48D4670(
        *(void**)((char*)pLogic + 0x48), a, b, s, c,
        s1, s2, s3, s4, s5, s6);
}

void CSyndicateLogic::Slot248Sub48D3100(
    int32_t a, uint64_t b) {
    void* pLogic = this;
    if (*(void**)((char*)pLogic + 0x48) == 0) {
        g_fnT1LogError(0); return;
    }
    g_fnSub48D3100(*(void**)((char*)pLogic + 0x48),
                   a, b);
}

void CSyndicateLogic::Slot250InviteFlow(
    uint32_t u, uint64_t p3, uint64_t p4) {
    void* pLogic = this;
    void** pp = (void**)pLogic;
    void* pBox = pp[1];
    uint32_t uLgId = (uint32_t)p3;
    char szBuf[1024]; szBuf[0] = 0;
    if (pp[9] == 0) { g_fnT1LogError(0); }
    else if (pp[2] == 0) { g_fnT1LogError(0); }
    else if (uLgId == 0) { g_fnT1LogError(0); }
    else {
        // RAW: (**(code**)(boxvt + 0x1f8))() — no
        // visible args (same shape as OnFlowerChange)
        int32_t iVar4 = (int32_t)((uint64_t (*)())
            (*(void***)pBox)[0x1f8/8])();
        if (iVar4 == 0) {
            int64_t lLg = g_fnLgFind(pp[2], uLgId);
            if (lLg != 0) {
                char bOk = g_fnLgInviteOk(
                    (void*)lLg, u, p3, p4);
                if (bOk) {
                    char bInv = g_fnSub9D3530(
                        (void*)pp[9], u, uLgId);
                    if (bInv) {
                        if (g_fnLgMoneyLow(
                                (void*)lLg)) {
                            void* pIv =
                                g_fnStringMgrInstance();
                            const void* pv =
                                g_fnStringMgrGetStr(pIv,
                                    "STR_TOO_LOWER_SYN_MONEY");
                            BoxVt18Tip(pBox, u, pv);
                        } else if (g_fnLgMemberFull(
                                       (void*)lLg)) {
                            void* pIv =
                                g_fnStringMgrInstance();
                            const void* pv =
                                g_fnStringMgrGetStr(pIv,
                                    "STR_SYN_FULL");
                            BoxVt18Tip(pBox, u, pv);
                        } else {
                            // RAW: logic vt+0x510
                            // (this, u)
                            uint32_t uLeader =
                                g_fnLogicVt510(pLogic,
                                               u);
                            if (uLeader != 0) {
                                uint64_t uRank =
                                    g_fnLgLeaderRank(
                                        (void*)lLg);
                                if (uLeader == uRank)
                                    g_fnSub10Call(
                                        pp[10], uLeader,
                                        u);
                                else
                                    g_fnB19C0(pLogic, u,
                                              1, p4);
                            }
                            char bSent = g_fnB8470(
                                pLogic, (void*)lLg, u,
                                200, 0, 0);
                            if (bSent) {
                                // RAW: box vt+0x370 ()
                                ((void (*)())
                                    (*(void***)
                                        *(char**)
                                            ((char*)pLogic
                                             + 8))
                                        [0x370/8])();
                                szBuf[0] = 0;
                                memset(szBuf + 1, 0,
                                       0x3ff);
                                // RAW: box vt+0x1d8
                                // (box, u)
                                g_fnBoxVt1d8(pBox, u);
                                g_fnLgRefresh(
                                    (void*)lLg);
                                g_fnLgF4E0((void*)lLg);
                                g_fnDelayMs(1000);
                                void* pIv =
                                    g_fnStringMgrInstance();
                                const char* pc =
                                    (const char*)
                                    g_fnStringMgrGetStr(
                                        pIv,
                                        "STR_SYN_INVITE_JOIN");
                                snprintf(szBuf, 0x400,
                                         pc);
                                uint64_t uBc =
                                    g_fnLgGetId(
                                        (void*)lLg);
                                BoxVt88Broadcast(pBox,
                                    (uint32_t)uBc,
                                    szBuf);
                                g_fnLgAd50((void*)lLg,
                                           u);
                            }
                        }
                    }
                }
            }
        }
    }
}

void CSyndicateLogic::Slot258Sub9D3680(int32_t n) {
    void* pLogic = this;
    void** pp = (void**)pLogic;
    void* pBox = pp[1];
    if (n == 0) { g_fnT1LogError(0); return; }
    if (pp[9] == 0) { g_fnT1LogError(0); return; }
    // RAW: (**(code**)(logicvt + 0x78))()
    char cOk = g_fnLogicVt78(pLogic);
    if (cOk) {
        int32_t iVar2 = (int32_t)((int32_t (*)(
            void*, int32_t))
            (*(void***)pBox)[0x1f8/8])(pBox, n);
        if (iVar2 != 0)
            g_fnSub9D3680((void*)pp[9], n, iVar2);
    }
}

// ================= D98 (+0x218) — the iterator monster =================
// RAW 1417c3ed0: CSyndicateLogic::AwardPrizeVlmOrCross.
// vecSynID (param_2) and vecBSelf (param_3) are MSVC vector /
// checked-iterator structs; every _invalid_parameter_noinfo()
// release check kept via g_fnInvalidParam.

void CSyndicateLogic::Slot218AwardPrizeVlmOrCross(
    void* pvSynID, void* pvBSelf, char bCross) {
    void* pLogic = this;
    void** pp = (void**)pLogic;
    void** ppSynID = (void**)pvSynID;
    void** ppBSelf = (void**)pvBSelf;
    // local_4a8 == param_4 (the cross flag)
    char bCrossLocal = bCross;
    char szBuf[1024];
    if ((uint32_t)((uint64_t)ppSynID[4] -
                   (uint64_t)ppSynID[3]) >> 2 ==
        (uint32_t)(uint64_t)ppBSelf[2]) {
        uint32_t* puId = (uint32_t*)ppSynID[3];
        if ((uint32_t*)ppSynID[4] < puId)
            g_fnInvalidParam();
        uint32_t* puB = (uint32_t*)ppBSelf[6];
        void** plOwner = (void**)*ppSynID;
        if ((uint32_t*)ppBSelf[7] < puB)
            g_fnInvalidParam();
        void** plIter = (void**)*ppBSelf;
        uint64_t lIdx = 0;
        uint32_t uCount = 0;
        uint64_t lRank = 0;
        do {
            // RAW local_470: set once, never updated
            lIdx = 0;
            uint32_t* puBCur = puB;
            void** plIterCur = plIter;
            uint32_t* puEnd =
                (uint32_t*)ppSynID[4];
            if (puEnd < (uint32_t*)ppSynID[3])
                g_fnInvalidParam();
            if (plOwner == 0 ||
                plOwner != (void**)*ppSynID)
                g_fnInvalidParam();
            if (puId == puEnd) return;
            uint32_t* puB2 =
                (uint32_t*)ppBSelf[6];
            if ((uint32_t*)ppBSelf[7] < puB2)
                g_fnInvalidParam();
            // RAW: the {current,pos} iterator pair the
            // C50 call may update; local_470 stays 0
            uint64_t pIterPair[2];
            *(void**)pIterPair = *(void**)ppBSelf;
            pIterPair[1] = 0;
            uint32_t* puBCur2 = puB2;
            if (ppBSelf[2] != 0)
                g_fnIterC50(pIterPair, ppBSelf[2]);
            if (puBCur == puBCur2 && lIdx ==
                pIterPair[1])
                return;
            uCount = uCount + 1;
            uint64_t lRankNew = lRank + 1;
            lRank = lRankNew;
            // the owner deref chain (release checks)
            uint64_t lOwner;
            if (plOwner == 0) {
                g_fnInvalidParam();
                lOwner = 0;
            } else lOwner = (uint64_t)*plOwner;
            if (*(uint32_t**)(lOwner + 0x20) <=
                puId)
                g_fnInvalidParam();
            if (*puId != 0) {
                if (bCrossLocal != 0) {
                    // the cross path: the vecBSelf
                    // iterator walk + the flag bit
                    void** plWalk = plIterCur;
                    if (plWalk == 0) {
                        plWalk = 0;
                        g_fnInvalidParam();
                    } else {
                        plWalk = (void**)*plWalk;
                        if (plWalk == 0) {
                            g_fnInvalidParam();
                            goto next_iter;
                        }
                    }
                    plWalk = (void**)*plWalk;
                    if (plWalk == 0 || puBCur == 0)
                        g_fnInvalidParam();
                    uint64_t lNode;
                    if (plWalk == 0) lNode = 0;
                    else lNode = (uint64_t)*plWalk;
                    uint64_t uBase = *(uint64_t*)
                        (lNode + 0x30);
                    if (*(uint64_t*)(lNode + 0x38) <
                        uBase)
                        g_fnInvalidParam();
                    if (plWalk == 0) lNode = 0;
                    else lNode = (uint64_t)*plWalk;
                    if (*(uint64_t*)(lNode + 0x10) <=
                        ((uint64_t)(puBCur - uBase)
                         >> 2) * 0x20 + lIdx)
                        g_fnInvalidParam();
                    // the eligibility bit
                    if ((*puBCur &
                         (1u << ((uint32_t)lIdx &
                                 0x1f))) == 0)
                        goto next_iter;
                }
                if (plOwner == 0) {
                    g_fnInvalidParam();
                } else if (*(uint32_t**)
                               ((uint64_t)*plOwner +
                                0x20) <= puId) {
                    g_fnInvalidParam();
                }
                uint64_t lLg = g_fnLgFind(
                    pp[2], *puId);
                if (lLg == 0) {
                    if (plOwner == 0) {
                        g_fnInvalidParam();
                    } else if (*(uint32_t**)
                                   ((uint64_t)
                                        *plOwner +
                                    0x20) <= puId) {
                        g_fnInvalidParam();
                    }
                    g_fnT1LogError(
                        "CSyndicateLogic::"
                        "AwardPrizeVlmOrCross, SynID"
                        "[%u] is not exist");
                } else {
                    uint32_t uMoney, uEmoney;
                    if (bCrossLocal == 0) {
                        uMoney =
                            s_auVlmMoney[lRankNew-1];
                        uEmoney =
                            s_auVlmEmoney[lRankNew-1];
                    } else {
                        uMoney = s_auCrossMoney[
                            lRankNew-1];
                        uEmoney = s_auCrossEmoney[
                            lRankNew-1];
                    }
                    uint32_t uMoneyX100 =
                        uMoney * 10000;
                    char bMoney = g_fnLgBf80(
                        (void*)lLg, uMoneyX100);
                    if (bMoney) {
                        if (plOwner == 0) {
                            g_fnInvalidParam();
                        } else if (*(uint32_t**)
                                       ((uint64_t)
                                            *plOwner +
                                        0x20) <=
                                   puId) {
                            g_fnInvalidParam();
                        }
                        g_fnLgRefresh((void*)lLg);
                        if (bCrossLocal == 0)
                            g_fnMyLogSave(
                                "gmlog/synvlmaward",
                                "Syn:%s[%u] Rank[%d]"
                                " Get money %u");
                        else
                            g_fnMyLogSave(
                                "gmlog/"
                                "syncrossvlmaward",
                                "Syn:%s[%u] Rank[%d]"
                                " Get money %u");
                    }
                    uint64_t uCur =
                        g_fnLgF550((void*)lLg);
                    uint32_t uSum =
                        (uint32_t)uCur + uEmoney;
                    if (uSum < 1000000000) {
                        void* pBox = pp[1];
                        uint64_t uLgId =
                            g_fnLgGetId(
                                (void*)lLg);
                        // RAW: box vt+0x350
                        ((void (*)(void*, uint32_t,
                                   uint32_t,
                                   uint32_t))
                            (*(void***)pBox)
                                [0x350/8])(
                            pBox, 0x2b, 0,
                            (uint32_t)uLgId);
                        char bEmoney = g_fnLgFa70(
                            (void*)lLg, uSum);
                        if (bEmoney) {
                            if (bCrossLocal != 0) {
                                if (plOwner == 0) {
                                    g_fnInvalidParam();
                                } else if (
                                    *(uint32_t**)
                                    ((uint64_t)
                                     *plOwner + 0x20)
                                    <= puId) {
                                    g_fnInvalidParam();
                                }
                                g_fnLgRefresh(
                                    (void*)lLg);
                                g_fnMyLogSave(
                                    "gmlog/"
                                    "syncrossvlmaward",
                                    "Syn:%s[%u] "
                                    "Rank[%d] Get "
                                    "emoney %u");
                                }
                            else {
                            if (plOwner == 0) {
                                g_fnInvalidParam();
                            } else if (*(uint32_t**)
                                           ((uint64_t)
                                                *plOwner +
                                            0x20) <=
                                       puId) {
                                g_fnInvalidParam();
                            }
                            g_fnLgRefresh(
                                (void*)lLg);
                            g_fnMyLogSave(
                                "gmlog/synvlmaward",
                                "Syn:%s[%u] Rank[%d]"
                                " Get emoney %u");
                            // RAW: no goto here — the
                            // vlm path falls through to
                            // the STR_VLM_AWARD bcast
                            }
                        }
                    }
                    // the award broadcast
                    szBuf[0] = 0;
                    memset(szBuf + 1, 0, 0x3ff);
                    {
                        void* pIv =
                            g_fnStringMgrInstance();
                        const char* pc;
                        if (bCrossLocal != 0)
                            pc = (const char*)
                                g_fnStringMgrGetStr(
                                    pIv,
                                    "STR_CROSS_VLM_AWARD");
                        else
                            pc = (const char*)
                                g_fnStringMgrGetStr(
                                    pIv,
                                    "STR_VLM_AWARD");
                        snprintf(szBuf, 0x400, pc);
                        if (plOwner == 0) {
                            g_fnInvalidParam();
                        } else if (*(uint32_t**)
                                       ((uint64_t)
                                            *plOwner +
                                        0x20) <=
                                   puId) {
                            g_fnInvalidParam();
                        }
                        // RAW: logic vt+0x40
                        ((void (*)(void*, uint32_t,
                                   const char*,
                                   uint32_t))
                            (*(void***)pLogic)
                                [0x40/8])(
                            pLogic, *puId, szBuf, 0);
                        bCrossLocal = bCrossLocal;
                        goto next_iter;
                    }
                }
            }
next_iter:
            if (plOwner == 0) {
                g_fnInvalidParam();
            } else if (*(uint32_t**)
                           ((uint64_t)*plOwner +
                            0x20) <= puId) {
                g_fnInvalidParam();
            }
            puId = puId + 1;
            g_fnIter730((void**)&plIter);
        } while ((int32_t)uCount < 8);
    } else {
        g_fnT1LogError(
            "CSyndicateLogic::AwardPrizeVlmOrCross."
            " bCross && vecSynID.size() != "
            "vecBSelf.size()");
    }
}

// ================= D99 wave 9 (+0x260..+0x2c8) =================

// +0x260: 1417ac020
void CSyndicateLogic::Slot260Destroy(void) {
    if (*(void**)((char*)this + 0x10) != 0)
        g_fnMgrCdfD0(*(void**)((char*)this + 0x10));
}

// TRUE +0x410: 1417b0770 (old wave-9 label +0x268)
uint64_t CSyndicateLogic::Slot410(int32_t n) {
    void** pp = (void**)this;
    if (n == 0) {
        // RAW: return in_RAX & ~0xff (CONCAT71 form)
        uint64_t uRaw = 0;
        return uRaw & 0xffffffffffffff00ULL;
    }
    uint32_t uId = ((uint32_t(*)())
        (*(void***)pp)[0x510/8])();
    int32_t iVar = g_fn647E0(pp[10], uId);
    return (uint64_t)(uint32_t)(n == iVar);
}

// TRUE +0x418: 1417b07c0 (old wave-9 label +0x270)
uint64_t CSyndicateLogic::Slot418(int32_t n) {
    void** pp = (void**)this;
    if (n == 0) {
        uint64_t uRaw = 0;
        return uRaw & 0xffffffffffffff00ULL;
    }
    uint64_t uVar2 =
        ((uint64_t(*)())(*(void***)pp)[0x510/8])();
    if ((int32_t)uVar2 == 0) return uVar2;
    // RAW: FUN_14174e3f0(param_1[10]) directly
    int32_t iVar = (int32_t)g_fn74E3F0(pp[10]);
    return (uint64_t)(uint32_t)((int32_t)uVar2 == iVar);
}

// TRUE +0x420: 1417b9650 (old wave-9 label +0x278)
void CSyndicateLogic::Slot420(uint32_t u, int32_t n3,
                              uint32_t u4, char c5) {
    void** pp = (void**)this;
    char* pc4 = (char*)(uint64_t)u4;
    uint32_t uVar3 = g_fn763C80(pp[10], u);
    g_fn76FBF0(pp[10], u, n3, (uint64_t)pc4, c5);
    uint64_t uVar4 = g_fn763680(pp[10], u);
    int64_t lLg = g_fnLgFind(pp[2], (uint32_t)uVar4);
    uint32_t uType = 0;
    if (lLg != 0) uType = (uint32_t)g_fn78F2D0(
        (void*)lLg);
    uint64_t uVar8 = (uint64_t)u;
    uType = g_fn7B9220(this, uType, u);
    g_fn7B52D0(this, uType, uVar8, pc4);
    char msgA[1072]; char msgB[1072];
    g_fnCMsgCtor6640(msgA);
    g_fnCMsgInit6790(msgA, 0x11, u, 0, 0);
    uVar4 = g_fn763680(pp[10], u);
    lLg = g_fnLgFind(pp[2], (uint32_t)uVar4);
    uint32_t uType2 = 0;
    if (lLg != 0) uType2 = (uint32_t)g_fn78F2D0(
        (void*)lLg);
    // RAW: box vt+8(box, type, msg)
    ((void (*)(void*, uint32_t, void*))
        (*(void***)pp[1])[0x8/8])(pp[1], uType2, msgA);
    g_fnCMsgCtor6640(msgB);
    uint32_t uCur = g_fn74E3F0(pp[10]);
    uint64_t uInit = g_fnCMsgInit6790(msgB, 0x15, u,
                                      uCur, 0);
    if ((char)uInit != 0) {
        // RAW: box vt+0x98 (no visible args)
        ((void (*)(void*, void*))
            (*(void***)pp[1])[0x98/8])(pp[1], msgB);
    }
    if (((int32_t)uVar3 < n3) && (c5 == 0)) {
        char buf[512];
        buf[0] = c5;
        memset(buf + 1, 0, 0x1ff);
        void* pIv = g_fnStringMgrInstance();
        const char* pc = (const char*)
            g_fnStringMgrGetStr(pIv,
                "STR_NOTIFY_NEW_COUNTRY_LEAGUE");
        snprintf(buf, 0x200, pc);
        // RAW: box vt+0xa0(box, u, buf, 0)
        ((void (*)(void*, uint32_t, const char*,
                   uint32_t))
            (*(void***)pp[1])[0xa0/8])(pp[1], u,
                                       buf, 0);
        g_fnCMsgDtor66C0(msgB);
        g_fnCMsgDtor66C0(msgA);
    } else {
        g_fnCMsgDtor66C0(msgB);
        g_fnCMsgDtor66C0(msgA);
    }
}

// TRUE +0x428: 1417b9880 (old wave-9 label +0x280)
void CSyndicateLogic::Slot428(uint32_t u, int32_t n3,
                             void* p4) {
    void** pp = (void**)this;
    g_fn76ECF0(pp[10], u, n3);
    uint64_t uVar2 = g_fn763680(pp[10], u);
    int64_t lLg = g_fnLgFind(pp[2], (uint32_t)uVar2);
    uint32_t uType = 0;
    if (lLg != 0) uType = (uint32_t)g_fn78F2D0(
        (void*)lLg);
    uint64_t uVar4 = (uint64_t)u;
    uType = g_fn7B9220(this, uType, u);
    g_fn7B52D0(this, uType, uVar4, p4);
}

// TRUE +0x430: 1417b1b90 (old wave-9 label +0x288)
void CSyndicateLogic::Slot430(uint32_t u) {
    g_fn763C80(*(void**)((char*)this + 0x50), u);
}

// +0x290: 1417b1ba0
void CSyndicateLogic::Slot290(void) {
    void** pp = (void**)this;
    uint32_t uVar1 = g_fn74E3F0(pp[10]);
    void* lVar2 = g_fn7630D0(pp[10], uVar1);
    if (lVar2 == 0) return;
    g_fn743D10(lVar2);
}

// +0x298: 1417b0360
void CSyndicateLogic::Slot298(void) {
    g_fn74E3F0(*(void**)((char*)this + 0x50));
}

// +0x2a0: 1417b1be0
void CSyndicateLogic::Slot2A0(uint32_t u, int32_t n) {
    g_fn76EE60(*(void**)((char*)this + 0x50), u, n);
}

// +0x2a8: 1417b1bf0
void CSyndicateLogic::Slot2A8(void) {
    void** pp = (void**)this;
    uint32_t uVar1 = g_fn74E3F0(pp[10]);
    void* lVar2 = g_fn7630D0(pp[10], uVar1);
    if (lVar2 == 0) return;
    g_fn743E60(lVar2);
}

// +0x2b0: 1417b1c30
void* CSyndicateLogic::Slot2B0(void) {
    void** pp = (void**)this;
    uint32_t uVar1 = g_fn74E3F0(pp[10]);
    if (uVar1 == 0) return (void*)"";
    void* lVar2 = g_fn7630D0(pp[10], uVar1);
    if (lVar2 == 0) return 0;
    return g_fn743Dd0(lVar2);
}

// +0x2b8: 1417b1c80
uint64_t CSyndicateLogic::Slot2B8(void) {
    void** pp = (void**)this;
    uint32_t uVar1 = g_fn74E3F0(pp[10]);
    if (uVar1 != 0) {
        void* lVar2 = g_fn7630D0(pp[10], uVar1);
        if (lVar2 != 0)
            return (uint64_t)(uint64_t*)
                g_fn743D70(lVar2);
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    }
    return 0;
}

// +0x2c0: 1417b1cf0
void* CSyndicateLogic::Slot2C0(void) {
    void** pp = (void**)this;
    uint32_t uVar1 = g_fn74E3F0(pp[10]);
    if (uVar1 == 0) return 0;
    void* lVar2 = g_fn7630D0(pp[10], uVar1);
    if (lVar2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    char* pcName = (char*)g_fn743D70(lVar2);
    // RAW: the manual strcmp against ""
    char* pcA = pcName; char* pcB = "";
    char uLast = 1; int64_t lCount = 1;
    do {
        if (lCount == 0) break;
        lCount = lCount - 1;
        uLast = (*pcA == *pcB);
        pcA = pcA + 1; pcB = pcB + 1;
    } while (uLast);
    if (uLast) {
        void* puVar4 = g_fn743Dd0(lVar2);
        if (puVar4 != 0) return puVar4;
        return (void*)"";
    }
    return (void*)((char*)this + 0x61);
}

// +0x2c8: 1417b1dd0
void* CSyndicateLogic::Slot2C8(uint32_t u) {
    void** pp = (void**)this;
    if (u != 0) {
        void* lVar1 = g_fn7630D0(pp[10], u);
        if (lVar1 != 0) return g_fn743Dd0(lVar1);
    }
    return 0;
}
// +0x2d0: 1417b1e80 — the title flow monster
void CSyndicateLogic::Slot2D0(int32_t n, uint32_t u,
                             const char* p4) {
    void** pp = (void**)this;
    if (p4 == 0) return;
    // RAW: the strlen scan gate (lVar10 != -2 =>
    // non-empty name)
    const char* pc = p4;
    int64_t lCnt = -1; char c;
    do {
        if (lCnt == 0) break;
        lCnt = lCnt - 1;
        c = *pc; pc = pc + 1;
    } while (c != '\0');
    if (lCnt == -2) return;
    int32_t iVar = g_fn74E920(pp[10]);
    int* piLang = g_fnCQLanguageGet();
    if ((*piLang != 0) &&
        (piLang = g_fnCQLanguageGet(), *piLang != 6)) {
        iVar = g_fn74E930(pp[10]);
    }
    // RAW: the second strlen (uVar11 counter)
    pc = p4;
    uint64_t uLen = (uint64_t)-1;
    do {
        if (uLen == 0) break;
        uLen = uLen - 1;
        c = *pc; pc = pc + 1;
    } while (c != '\0');
    // ~uLen - 1 = the name length
    // RAW short-circuit: vt+0x2e8 runs only when
    // the length check passes
    if ((uint64_t)(int64_t)iVar < ~uLen - 1) {
        // RAW || short-circuit: vt+0x2e8 NOT called
        void* pIvA = g_fnStringMgrInstance();
        uint64_t uStrA = (uint64_t)
            g_fnStringMgrGetStr(pIvA, "STR_INVALID_NAME");
        ((void (*)(void*, int32_t, uint64_t))
            (*(void***)pp[1])[0x18/8])(pp[1], n, uStrA);
    } else if (((char (*)(void*, const char*))
        (*(void***)pp[1])[0x2e8/8])(pp[1], p4) == 0) {
        void* pIvA2 = g_fnStringMgrInstance();
        uint64_t uStrA2 = (uint64_t)
            g_fnStringMgrGetStr(pIvA2, "STR_INVALID_NAME");
        ((void (*)(void*, int32_t, uint64_t))
            (*(void***)pp[1])[0x18/8])(pp[1], n, uStrA2);
    } else {
        uint32_t uVar4 = g_fn74E3F0(pp[10]);
        if ((uVar4 == u) && (u != 0)) {
            void* lLg = g_fn7630D0(pp[10], u);
            if (lLg != 0) {
                int32_t iOwner =
                    g_fn7B0370(this, u);
                if (iOwner == n) {
                    g_fn743F90(lLg, 4, p4, 1);
                    uint32_t uTime =
                        g_fnTimeGet(3);
                    uVar4 = uTime + 19000000;
                    char msg[1072];
                    g_fnCMsgCtor6640(msg);
                    uint64_t uOk =
                        g_fnCMsgInit6820(msg,
                            0x12, p4, uVar4, 0, 0);
                    if ((char)uOk != 0) {
                        // RAW: box vt+0xe0 (no
                        // visible args)
                        ((void (*)(void*, void*))
                            (*(void***)pp[1])
                             [0xe0/8])(pp[1], msg);
                    }
                    char buf[512];
                    buf[0] = 0;
                    memset(buf + 1, 0, 0x1ff);
                    void* pIv2 =
                        g_fnStringMgrInstance();
                    const char* pcTitle =
                        (const char*)
                        g_fnStringMgrGetStr(pIv2,
                            "STR_LEAGUE_SET_TITLE");
                    snprintf(buf, 0x200, pcTitle);
                    ((void (*)(void*, int32_t,
                               const char*))
                        (*(void***)pp[1])
                         [0x18/8])(pp[1], n, buf);
                    // RAW: std::string tmp("")
                    // + assign + dtor pair
                    char sTmp[16];
                    sTmp[0] = 0;
                    char sVal[32]; sVal[0] = 0;
                    // assign(local_280, tmp.c_str())
                    strncpy(sVal, sTmp, 31);
                    sVal[31] = 0;
                    // (string1 destroyed — empty)
                    void* pIv3 =
                        g_fnStringMgrInstance();
                    // RAW: box vt+0x1d8(p2), vt+0x488
                    ((void (*)(void*, int32_t))
                        (*(void***)pp[1])
                         [0x1d8/8])(pp[1], n);
                    ((uint64_t (*)(void*))
                        (*(void***)pp[1])
                         [0x488/8])(pp[1]);
                    const char* pcBcast =
                        (const char*)
                        g_fnStringMgrGetStr(pIv3,
                            "STR_LEAGUE_BROADCAST_TITLE");
                    // the tq::CString object at
                    // &local_288: vt + SSO buffer
                    uint8_t acCStr[8 + 0x20 + 16];
                    memset(acCStr, 0, sizeof(acCStr));
                    g_fnCStrFormat215d0(acCStr,
                        pcBcast,
                        (uint64_t)(uVar4 / 10000),
                        (uint64_t)((uVar4 % 10000)
                            / 100));
                    const char* pcData =
                        (const char*)(acCStr + 8);
                    ((void (*)(void*, const char*))
                        (*(void***)pp[1])
                         [0x438/8])(pp[1], pcData);
                    g_fnStrCopy((char*)this + 0x61,
                                p4, 0x20);
                    void* pIv4 =
                        g_fnStringMgrInstance();
                    const char* pcCty =
                        (const char*)
                        g_fnStringMgrGetStr(pIv4,
                            "STR_LEAGUE_COUNTRY");
                    // RAW: the strlen scan of
                    // this+0x61 then the manual
                    // strcpy at the end position
                    const char* pcS =
                        (const char*)this + 0x61;
                    const char* pcEnd;
                    int64_t lC2 = -1;
                    do {
                        pcEnd = pcS;
                        if (lC2 == 0) break;
                        lC2 = lC2 - 1;
                        pcEnd = pcS + 1;
                        c = *pcS;
                        pcS = pcEnd;
                    } while (c != '\0');
                    int64_t lJ = 0;
                    do {
                        c = pcCty[lJ];
                        ((char*)pcEnd)[lJ - 1] = c;
                        lJ = lJ + 1;
                    } while (c != '\0');
                    ((void (*)(void*, int32_t,
                               uint32_t, int32_t))
                        (*(void***)pp[1])
                         [0x70/8])(pp[1], 7, u, 0);
                    ((void (*)(void*, uint32_t,
                               const char*))
                        (*(void***)pp[1])
                         [0x440/8])(pp[1], u, p4);
                    // RAW: ~basic_string(local_280)
                    // then CMsg dtor
                    g_fnCMsgDtor66C0(msg);
                } else {
                    void* pIv5 =
                        g_fnStringMgrInstance();
                    uint64_t uStr2 = (uint64_t)
                        g_fnStringMgrGetStr(pIv5,
                            "STR_LEAGUE_CAN_NOT_SET_TITLE");
                    ((void (*)(void*, int32_t,
                               uint64_t))
                        (*(void***)pp[1])
                         [0x18/8])(pp[1], n, uStr2);
                }
            }
        }
    }
}
// ================= D101 wave 10 (+0x2d8..+0x330) =================

// +0x2d8: 1417b22a0
void CSyndicateLogic::Slot480(int32_t* p2) {
    g_fn76FE50(((void**)this)[10], p2);
}

// +0x2e0: 1417b22b0
void CSyndicateLogic::Slot488(void) {
    g_fn76ACE0(((void**)this)[10]);
}

// +0x2e8: 1417b22c0
void CSyndicateLogic::Slot490(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn763DD0(((void**)this)[10], n2, n3, p4);
}

// +0x2f0: 1417b22d0
void CSyndicateLogic::Slot498(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn764000(((void**)this)[10], n2, n3, p4);
}

// +0x2f8: 1417b22e0
void CSyndicateLogic::Slot4A0(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn764230(((void**)this)[10], n2, n3, p4);
}

// +0x300: 1417b22f0
void CSyndicateLogic::Slot4A8(uint32_t u2, int32_t n3) {
    g_fn764300(((void**)this)[10], u2, n3);
}

// +0x308: 1417b2300
void CSyndicateLogic::Slot4B0(int32_t n2, int32_t n3,
                              int32_t n4) {
    g_fn76EFC0(((void**)this)[10], n2, n3, n4);
}

// +0x310: 1417b2310
void CSyndicateLogic::Slot4B8(void) {
    g_fn76F190(((void**)this)[10]);
}

// +0x318: 1417b2320
void CSyndicateLogic::Slot4C0(uint16_t u2, uint32_t u3) {
    void** pp = (void**)this;
    void* lLg = g_fn7630D0(pp[10], u3);
    if (lLg == 0) {
        // RAW: local_68 = 0x1e02 (a dead store kept
        // verbatim) + the literal log
        volatile uint32_t local_68 = 0x1e02;
        (void)local_68;
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    } else {
        uint8_t ab[0x40];
        memset(ab, 0, sizeof(ab));
        g_fn745920(lLg, ab);
        // RAW: box vt+0x480(box, &local_58, u2)
        ((void (*)(void*, void*, uint16_t))
            (*(void***)pp[1])[0x480/8])(pp[1], ab,
                                        u2);
    }
}

// +0x320: 1417b23f0
void CSyndicateLogic::Slot4C8(uint32_t u2) {
    g_fn7645C0(((void**)this)[10], u2);
}

// +0x328: 1417b2400
void CSyndicateLogic::Slot4D0(uint32_t u) {
    void** pp = (void**)this;
    int32_t iVar3 = (int32_t)g_fn74E3F0(pp[10]);
    if (iVar3 == 0 && g_fn74EA40(pp[10]) == 0) {
        int64_t lLg = g_fnLgFind(pp[2], u);
        if (lLg == 0) {
            g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
            return;
        }
        uint64_t uVar5 = g_fn790390((void*)lLg);
        if ((uint32_t)uVar5 == 0) {
            void* pv = g_fn78F470((void*)lLg);
            uint64_t uType = g_fn78F2D0((void*)lLg);
            // RAW: logic vt+0x4e8(this, type, pv, 1)
            ((void (*)(void*, uint32_t, void*,
                       int32_t))
                (*(void***)this)[0x4e8/8])(
                    this, (uint32_t)uType, pv, 1);
        } else {
            void* lLg2 = g_fn7630D0(pp[10],
                                    (uint32_t)uVar5);
            if (lLg2 == 0) {
                g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
            } else {
                // RAW: box vt+0x478(box, type, 6)
                uint64_t uType2 =
                    g_fn745520(lLg2);
                ((void (*)(void*, uint32_t,
                           int32_t))
                    (*(void***)pp[1])[0x478/8])(
                        pp[1], (uint32_t)uType2, 6);
                g_fn74EA30(pp[10], 1);
            }
        }
    }
}

// +0x330: 1417b2540
void CSyndicateLogic::Slot4D8(void) {
    void** pp = (void**)this;
    // RAW: box vt+0xa0 (no visible args at all)
    ((void (*)(void*))
        (*(void***)pp[1])[0xa0/8])(pp[1]);
}
// +0x340: 1417b8940 — the create-league flow
bool CSyndicateLogic::Slot4E8(uint32_t u2,
                              const char* p3, char c4) {
    void** pp = (void**)this;
    if (p3 == 0) return false;
    // RAW: the strlen counter (uVar13)
    const char* pc = p3;
    char c; uint64_t uCnt = (uint64_t)-1;
    do {
        if (uCnt == 0) break;
        uCnt = uCnt - 1;
        c = *pc; pc = pc + 1;
    } while (c != '\0');
    // RAW: 0xf < ~uCnt - 1 -> too long
    // (short-circuit: vt+0x2e8 only if length ok)
    if (0xf < ~uCnt - 1) {
        void* pIv = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(pIv, "STR_INVALID_NAME");
        ((void (*)(void*, uint32_t, uint64_t))
            (*(void***)pp[1])[0x18/8])(pp[1], u2, uStr);
        return false;
    }
    if (((char (*)(void*, const char*))
            (*(void***)pp[1])[0x2e8/8])(pp[1], p3)
        == 0) {
        void* pIv2 = g_fnStringMgrInstance();
        uint64_t uStr2 = (uint64_t)
            g_fnStringMgrGetStr(pIv2, "STR_INVALID_NAME");
        ((void (*)(void*, uint32_t, uint64_t))
            (*(void***)pp[1])[0x18/8])(pp[1], u2, uStr2);
        return false;
    }
    if (g_fn75EB70(pp[10], p3) != 0) {
        void* pIv3 = g_fnStringMgrInstance();
        uint64_t uStr3 = (uint64_t)
            g_fnStringMgrGetStr(pIv3,
                "STR_FORBIDDEN_LEAGUE_NAME");
        ((void (*)(void*, uint32_t, uint64_t))
            (*(void***)pp[1])[0x18/8])(pp[1], u2, uStr3);
        return false;
    }
    void* plPlayer = g_fn78C8E0(pp[3], u2);
    if (plPlayer == 0) return false;
    if (!g_fn7868C0(plPlayer)) return false;
    uint64_t uSynId = g_fn785EA0(plPlayer);
    int64_t lLg = g_fnLgFind(pp[2], (uint32_t)uSynId);
    if (lLg == 0) return false;
    if ((int32_t)g_fn790390((void*)lLg) != 0)
        return false;
    int32_t iVar5 = g_fn74E740(pp[10]);
    if (c4 == 0) {
        uint64_t uMoney = g_fnLgF550((void*)lLg);
        if ((int32_t)uMoney < iVar5) return false;
        uMoney = g_fnLgF550((void*)lLg);
        g_fnLgFa70((void*)lLg,
                   (int32_t)uMoney - iVar5);
        // RAW: box vt+0x350(box, 0x42, emoney)
        uint64_t uEm = g_fn78F270((void*)lLg);
        ((void (*)(void*, int32_t, uint32_t))
            (*(void***)pp[1])[0x350/8])(
                pp[1], 0x42, (uint32_t)uEm);
        // RAW: box vt+0x200(box, p2)
        ((void (*)(void*, uint32_t))
            (*(void***)pp[1])[0x200/8])(pp[1], u2);
        ((void (*)(void*, uint32_t))
            (*(void***)pp[1])[0x1d8/8])(pp[1], u2);
        g_fnMyLogSave("gmlog/emoney_buy",
            "%u\t%s\t%u\t350\t4227\t%d\t%d\t1\t");
    }
    const char* pcName = g_fn787120(plPlayer);
    uint64_t uSynId2 = g_fn785EA0(plPlayer);
    void* puNew = g_fn76F7F0(pp[10], (uint32_t)uSynId2,
                             p3, c4, u2, pcName);
    if (puNew != 0) {
        uint64_t uEm2 = g_fn78F270((void*)lLg);
        g_fn74DCD0(puNew, (int32_t)uEm2);
        uint64_t uType = g_fn745520(puNew);
        g_fn7903D0((void*)lLg, (int32_t)uType);
        uint8_t ab[0x40];
        memset(ab, 0, sizeof(ab));
        g_fn745920(puNew, ab);
        ((void (*)(void*, void*, int32_t))
            (*(void***)pp[1])[0x480/8])(pp[1], ab, 0);
        if (c4 != 0) {
            char msg[1072];
            g_fnCMsgCtor6640(msg);
            uint32_t uCur = g_fn74E3F0(pp[10]);
            uint64_t uType2 = g_fn745520(puNew);
            uint64_t uOk = g_fnCMsgInit6790(msg, 6,
                (uint32_t)uType2, uCur, 0);
            if ((char)uOk != 0) {
                ((void (*)(void*, uint32_t, void*))
                    (*(void***)pp[1])[0x8/8])(
                        pp[1], u2, msg);
            }
            g_fnCMsgDtor66C0(msg);
        }
        // RAW: logic vt+0x710(this, lg, type, 7)
        uint64_t uType3 = g_fn745520(puNew);
        ((void (*)(void*, void*, uint32_t, int32_t))
            (*(void***)this)[0x710/8])(
                this, (void*)lLg, (uint32_t)uType3, 7);
        g_fn7B0EA0(this, u2, 1);
        if ((c4 == 0) ||
            (iVar5 = g_fn74E740(pp[10]),
             iVar5 != 0)) {
            char buf[512];
            buf[0] = 0;
            memset(buf + 1, 0, 0x1ff);
            void* pIv4 = g_fnStringMgrInstance();
            ((void (*)(void*, uint32_t))
                (*(void***)pp[1])[0x1d8/8])(pp[1],
                                            u2);
            const char* pcTitle =
                (const char*)
                g_fnStringMgrGetStr(pIv4,
                    "STR_LEAGUE_CREATE_LEAGUE");
            snprintf(buf, 0x200, pcTitle);
            // RAW: local_59 = 0 after buf
            buf[512 - 2] = 0; // model local_59
            // RAW: box vt+0x90(box, buf, 0x7d5)
            ((void (*)(void*, const char*, uint32_t))
                (*(void***)pp[1])[0x90/8])(
                    pp[1], buf, 0x7d5);
        } else {
            uint64_t uType4 = g_fn745520(puNew);
            ((void (*)(void*, uint32_t, int32_t))
                (*(void***)pp[1])[0x478/8])(
                    pp[1], (uint32_t)uType4, 6);
            g_fn74EA30(pp[10], 1);
        }
        return true;
    }
    return false;
}
// +0x350: 1417b16b0 — the join-league flow
void CSyndicateLogic::Slot4F8(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    int64_t lLg = g_fnLgFind(pp[2], u3);
    if (lLg != 0
        && (uint32_t)g_fn78F2D0((void*)lLg) == u2
        && (int32_t)g_fn790390((void*)lLg) == 0) {
        void* lVar4 = g_fn7630D0(pp[10], u4);
        if (lVar4 != 0) {
            uint64_t uLead = g_fn743C80(lVar4);
            int64_t lLeader =
                g_fnLgFind(pp[2], (uint32_t)uLead);
            if (lLeader == 0) {
                // RAW: FUN_141743c80(lVar4) again
                // before the literal log
                g_fn743C80(lVar4);
                g_fnT1LogError(
                    "CSyndicateLogic::SynJoinLeague,"
                    " league[%lu] leader syndicate[%lu]"
                    " is null");
            } else {
                if (g_fn7977D0((void*)lLeader, u3)
                    == 0) {
                    uint64_t uLead2 =
                        g_fn743C80(lVar4);
                    if (g_fn7977D0((void*)lLg,
                                   (uint32_t)uLead2)
                        == 0) {
                        // RAW: 141763920(sub, u2)
                        char cLeave =
                            g_fn763920(pp[10], u2);
                        if (cLeave == 0) {
                            char buf[512];
                            buf[0] = 0;
                            memset(buf + 1, 0, 0x1ff);
                            void* pIv =
                                g_fnStringMgrInstance();
                            g_fn74E7E0(pp[10]);
                            const char* pc =
                                (const char*)
                                g_fnStringMgrGetStr(pIv,
                                    "STR_LEAGUE_LEAVE_SOON");
                            snprintf(buf, 0x200, pc);
                            // RAW: box vt+0x28(box,
                            // u2, buf, 0xffff00)
                            ((void (*)(void*,
                                uint32_t,
                                const char*,
                                uint32_t))
                                (*(void***)pp[1])
                                 [0x28/8])(
                                    pp[1], u2, buf,
                                    0xffff00);
                            return;
                        }
                        if (g_fn7903D0((void*)lLg,
                                       (int32_t)u4)
                            == 0) {
                            g_fn78F470((void*)lLg);
                            g_fnT1LogError(
                                "SynJoinLeague failure"
                                "\xa3\xacidSyn:%d ,"
                                " SynName:%s ,"
                                " idLeague:%d ");
                            return;
                        }
                        g_fn74DCD0(lVar4,
                                   (int32_t)u3);
                        // RAW: logic vt+0x710(this,
                        // lg, u4, 0xb)
                        ((void (*)(void*, void*,
                                   uint32_t, int32_t))
                            (*(void***)this)[0x710/8])(
                                this, (void*)lLg, u4,
                                0xb);
                        int32_t iVar1 =
                            ((int32_t (*)(void*, void*))
                                (*(void***)pp[1])
                                 [0x3f0/8])(
                                    pp[1], 0);
                        g_fn76CA70(pp[10],
                                   u4 + (uint32_t)
                                       iVar1 * 1000000,
                                   0, u3);
                        char buf2[1024];
                        buf2[0] = 0;
                        memset(buf2 + 1, 0, 0x3ff);
                        void* pIv2 =
                            g_fnStringMgrInstance();
                        uint64_t uName =
                            (uint64_t)
                            g_fn743Dd0(lVar4);
                        g_fn78F470((void*)lLg);
                        const char* pc2 =
                            (const char*)
                            g_fnStringMgrGetStr(pIv2,
                                "STR_SYN_JOIN_LEAGUE");
                        (void)uName; // RAW: local_658
                        snprintf(buf2, 0x3ff, pc2);
                        // RAW: box vt+0x90(box, buf2,
                        // 0x843)
                        ((void (*)(void*,
                                   const char*,
                                   uint32_t))
                            (*(void***)pp[1])
                             [0x90/8])(
                                pp[1], buf2, 0x843);
                        return;
                    }
                }
                // the enemy path
                void* pIv3 = g_fnStringMgrInstance();
                uint64_t uStr = (uint64_t)
                    g_fnStringMgrGetStr(pIv3,
                        "STR_LEAGUE_IS_ENEMY_SYN");
                ((void (*)(void*, uint32_t,
                           const char*, uint32_t))
                    (*(void***)pp[1])[0x28/8])(
                        pp[1], u2,
                        (const char*)(uintptr_t)uStr,
                        0xffff00);
            }
        }
    }
}
// +0x358: 1417c13e0 — the exit-league flow
void CSyndicateLogic::Slot500(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    void* lLg2 = g_fn7630D0(pp[10], u4);
    if (lLg2 != 0
        && (uint32_t)g_fn743C80(lLg2) != u3) {
        int64_t lLg = g_fnLgFind(pp[2], u3);
        if (lLg != 0
            && (uint32_t)g_fn78F2D0((void*)lLg) == u2
            && (uint32_t)g_fn790390((void*)lLg) == u4
            && g_fn7903D0((void*)lLg, 0) != 0) {
            g_fn74D490(lLg2, u3);
            char buf[1024];
            buf[0] = 0;
            memset(buf + 1, 0, 0x3ff);
            void* pIv = g_fnStringMgrInstance();
            g_fn743Dd0(lLg2);
            const char* pcFmt = (const char*)
                g_fnStringMgrGetStr(pIv,
                    "STR_SYN_EXIT_LEAGUE");
            snprintf(buf, 0x400, pcFmt);
            // RAW: local_4a8 = 0x7d5
            uint16_t uLocal4a8 = 0x7d5;
            (void)uLocal4a8;
            // RAW: box vt+0x88(box, u3, buf, 0)
            ((void (*)(void*, uint32_t,
                       const char*, uint32_t))
                (*(void***)pp[1])[0x88/8])(
                    pp[1], u3, buf, 0);
            uint64_t uVar7 = 5;
            // RAW: logic vt+0x710(this, lg, 0, 5)
            ((void (*)(void*, void*, uint32_t,
                       int32_t))
                (*(void***)this)[0x710/8])(
                    this, (void*)lLg, 0,
                    (int32_t)uVar7);
            g_fn7C1180(this, u3, u4, uVar7);
            g_fn76ACA0(pp[10], u2);
            // ---- the checked-iterator member sweep
            // (MSVC vector: apVec[0]=proxy,
            // apVec[1]=begin, apVec[2]=end; the
            // _invalid_parameter_noinfo probes are
            // the debug checks, modeled by asserts) ----
            void* pProxy = malloc(8);
            void* apVec[3];
            apVec[0] = 0; apVec[1] = 0; apVec[2] = 0;
            if (pProxy != 0) {
                *(void**)pProxy = apVec;
                apVec[0] = pProxy;
            }
            uint64_t uOk = g_fn79E6D0(
                (void*)lLg, apVec);
            uint32_t* puBegin = (uint32_t*)apVec[1];
            uint32_t* puEnd = (uint32_t*)apVec[2];
            uint32_t* puIt = puBegin;
            if ((char)uOk != 0) {
                while (true) {
                    uint32_t* puCur = puEnd;
                    if (puIt == puCur) break;
                    uint32_t uId = *puIt;
                    char c268 =
                        ((char (*)(void*, uint32_t))
                            (*(void***)pp[1])
                             [0x268/8])(pp[1], uId);
                    if (c268 != 0) {
                        char c280 =
                            ((char (*)(void*,
                                uint32_t))
                                (*(void***)pp[1])
                                 [0x280/8])(
                                    pp[1], uId);
                        if (c280 == 0) {
                            int32_t i2a0 =
                                ((int32_t (*)
                                  (void*, uint32_t))
                                    (*(void***)pp[1])
                                     [0x2a0/8])(
                                        pp[1], uId);
                            if (i2a0 == 9) {
                                ((void (*)(void*,
                                    uint32_t,
                                    int32_t))
                                    (*(void***)pp[1])
                                     [0x2a8/8])(
                                        pp[1], uId,
                                        3);
                            }
                        }
                    }
                    puIt = puIt + 1;
                }
            }
            if (puBegin != 0) {
                free(puBegin);
            }
            apVec[1] = 0;
            apVec[2] = 0;
            free(apVec[0]);
        }
    }
}
// +0x360: 1417b9380 — the leader-change flow
void CSyndicateLogic::Slot508(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    if (u2 == u4) return;
    void* lLg2 = g_fn7630D0(pp[10], u3);
    if (lLg2 == 0) return;
    void* plA = g_fn78C8E0(pp[3], u2);
    void* plB = g_fn78C8E0(pp[3], u4);
    if (plA != 0 && plB != 0
        && g_fn7868C0(plB) && g_fn7868C0(plA)) {
        uint64_t uSynA = g_fn785EA0(plA);
        uint64_t uLead = g_fn743C80(lLg2);
        if ((int32_t)uSynA == (int32_t)uLead) {
            uint64_t uSynB = g_fn785EA0(plB);
            int64_t lLg =
                g_fnLgFind(pp[2], (uint32_t)uSynB);
            if (lLg != 0
                && (uint32_t)g_fn790390((void*)lLg)
                    == u3) {
                uint64_t uEm =
                    g_fn78F270((void*)lLg);
                g_fn743E80(lLg2, 2, (int32_t)uEm, 1);
                g_fn74D3E0(lLg2);
                char buf[1024];
                buf[0] = 0;
                memset(buf + 1, 0, 0x3ff);
                void* pIv = g_fnStringMgrInstance();
                g_fn787120(plB);
                g_fn787120(plA);
                const char* pc = (const char*)
                    g_fnStringMgrGetStr(pIv,
                        "STR_LEAGUE_LEADER_CHANGE");
                snprintf(buf, 0x400, pc);
                // RAW: box vt+0xa0(box, u3, buf, 0)
                ((void (*)(void*, uint32_t,
                           const char*, uint32_t))
                    (*(void***)pp[1])[0xa0/8])(
                        pp[1], u3, buf, 0);
                const char* pcName =
                    g_fn787120(plB);
                g_fn7B92B0(this, u2, u4, u3, pcName);
                int32_t iVar2 = g_fn74E3F0(pp[10]);
                uint64_t uType = g_fn745520(lLg2);
                if ((int32_t)uType == iVar2) {
                    memset(buf, 0, 0x400);
                    void* pIv2 =
                        g_fnStringMgrInstance();
                    g_fn787120(plB);
                    g_fn787120(plA);
                    const char* pc2 = (const char*)
                        g_fnStringMgrGetStr(pIv2,
                            "STR_LEAGUE_KING_CHANGE");
                    snprintf(buf, 0x400, pc2);
                    // RAW: box vt+0x90(box, buf, 0x843)
                    ((void (*)(void*,
                               const char*,
                               uint32_t))
                        (*(void***)pp[1])[0x90/8])(
                            pp[1], buf, 0x843);
                    const char* pcName2 =
                        g_fn787120(plB);
                    // RAW: box vt+0x430(box, u3, name)
                    ((void (*)(void*, uint32_t,
                               const char*))
                        (*(void***)pp[1])[0x430/8])(
                            pp[1], u3, pcName2);
                }
            }
        }
    }
}
// ================= D106 wave 11 (+0x368..+0x3b0) =================

// +0x368: 1417b02f0
uint32_t CSyndicateLogic::Slot510(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0) return 0;
    void* plPlayer = g_fn78C8E0(pp[3], u2);
    if (plPlayer == 0) {
        return g_fn75EE00(pp[10], u2);
    }
    uint64_t uSyn = g_fn785EA0(plPlayer);
    if ((int32_t)uSyn != 0) {
        // RAW: logic vt+0x518(this, synId)
        return ((uint32_t (*)(void*, uint32_t))
            (*(void***)this)[0x518/8])(
                this, (uint32_t)uSyn);
    }
    return 0;
}

// +0x370: 1417afe40
uint64_t CSyndicateLogic::Slot518(uint32_t u2) {
    void** pp = (void**)this;
    int64_t lLg = g_fnLgFind(pp[2], u2);
    if (lLg != 0) {
        return g_fn790390((void*)lLg);
    }
    return 0;
}

// +0x378: 1417b5810
uint64_t CSyndicateLogic::Slot520(uint32_t u2) {
    if (u2 == 0) {
        // RAW: in_RAX & 0xff..00 (upper garbage)
        return 0;
    }
    return g_fn74EF00(((void**)this)[10], u2);
}

// +0x380: 1417b5820
uint64_t CSyndicateLogic::Slot528(int32_t n2) {
    if (n2 == 0) {
        return 0;
    }
    return g_fn74EF20(((void**)this)[10], n2);
}

// +0x388: 1417b0e90
void CSyndicateLogic::Slot530(uint32_t u2) {
    g_fn74ED30(((void**)this)[10], u2);
}

// +0x390: 1417afe70
void CSyndicateLogic::Slot538(uint32_t u2) {
    void** pp = (void**)this;
    int32_t iVar1 =
        ((int32_t (*)(void*, void*))
            (*(void***)pp[1])[0x4a8/8])(pp[1], 0);
    if (iVar1 == 0) return;
    g_fn74EBE0(pp[10], u2, iVar1);
}

// +0x398: 1417afec0
void CSyndicateLogic::Slot540(uint32_t u2) {
    void** pp = (void**)this;
    int32_t iVar1 =
        ((int32_t (*)(void*, void*))
            (*(void***)pp[1])[0x4a8/8])(pp[1], 0);
    if (iVar1 == 0) return;
    g_fn74EC50(pp[10], u2, iVar1);
}

// +0x3a0: 1417aff10
uint64_t CSyndicateLogic::Slot548(uint32_t u2) {
    void** pp = (void**)this;
    uint64_t uVar1 =
        (uint64_t)(int64_t)
        ((int32_t (*)(void*, void*))
            (*(void***)pp[1])[0x4a8/8])(pp[1], 0);
    if ((int32_t)uVar1 == 0) {
        // RAW: CONCAT71((int7)(uVar1 >> 8), 1)
        return (uVar1 & ~0xffULL) | 1;
    }
    return g_fn74ECC0(pp[10], u2, (int32_t)uVar1);
}

// +0x3a8: 1417aff60
void CSyndicateLogic::Slot550(uint16_t u2) {
    void** pp = (void**)this;
    if (u2 != 0 && pp[10] != 0) {
        g_fn768020(pp[10], u2);
    }
}

// +0x3b0: 1417aff80
void CSyndicateLogic::Slot558(int32_t n2, uint32_t u3) {
    if (n2 != 0) {
        g_fn7524D0(((void**)this)[10], n2, u3);
    }
}
// ================= D107 wave 12 (+0x0e8..+0x130) =================
// NB: these slots read *(this+0x10) / *(this+0x50)
// which in the ported layout are pp[2] / pp[10].

// +0x0e8: 1417ab1c0
void CSyndicateLogic::Slot0E8(uint32_t u2) {
    g_fn7CB000(((void**)this)[2], u2);
}

// +0x0f0: 1417ab2b0
int64_t CSyndicateLogic::Slot0F0(uint32_t u2) {
    if (u2 == 0) return 0;
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    if (lLg != 0) {
        return g_fn78F4E0((void*)lLg);
    }
    return 0;
}

// +0x0f8: 1417aeba0 — no `this` use at all
void CSyndicateLogic::Slot0F8(int32_t n2) {
    g_fn7873A0(n2);
}

// +0x100: 1417af4b0
bool CSyndicateLogic::Slot100(uint32_t u2) {
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    return lLg != 0;
}

// +0x108: 1417af720
uint64_t CSyndicateLogic::Slot108(uint32_t u2,
                                  void** pp3) {
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    if (lLg == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    return g_fn79E6D0((void*)lLg, pp3);
}

// +0x110: 1417af780
int32_t CSyndicateLogic::Slot110(uint32_t u2) {
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    if (lLg == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    return g_fn798800((void*)lLg);
}

// +0x118: 1417afd50
uint32_t CSyndicateLogic::Slot118(uint32_t u2) {
    void** pp = (void**)this;
    if (pp[2] == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    } else {
        int64_t lLg = g_fnLgFind(pp[2], u2);
        if (lLg != 0) {
            return g_fn78F400((void*)lLg);
        }
    }
    return 0;
}

// +0x120: 1417afdb0
uint64_t CSyndicateLogic::Slot120(uint32_t u2) {
    void** pp = (void**)this;
    if (pp[2] == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    } else {
        int64_t lLg = g_fnLgFind(pp[2], u2);
        if (lLg != 0) {
            return g_fn78F410((void*)lLg);
        }
    }
    return 0;
}

// +0x128: 1417afe10
uint64_t CSyndicateLogic::Slot128(uint32_t u2) {
    if (u2 == 0) return 0;
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    if (lLg != 0) {
        return g_fn78F2D0((void*)lLg);
    }
    return 0;
}

// +0x130: 1417b2780
void CSyndicateLogic::Slot130(int32_t n2, uint32_t u3,
                              int32_t n4, uint16_t u5,
                              uint16_t u6) {
    g_fn76ACF0(((void**)this)[10], n2, u3, n4, u5,
               u6);
}
// ============ D108 wave 13 (TRUE +0x1d0..+0x288) ============

// +0x1d0: 1417aaf90
uint64_t CSyndicateLogic::Slot1D0() { return 0xf; }

// +0x1d8: 1417aafa0
uint64_t CSyndicateLogic::Slot1D8() { return 0xf; }

// +0x1e0: 1417ab220
const char* CSyndicateLogic::Slot1E0(uint32_t u2,
                                      int32_t n3) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            uint64_t uSyn =
                g_fn78E4A0((void*)lLg, n3);
            if ((uint32_t)uSyn != 0) {
                int64_t lLg2 =
                    g_fnLgFind(((void**)this)[2],
                               (uint32_t)uSyn);
                if (lLg2 != 0) {
                    return (const char*)g_fn78F470((void*)lLg2);
                }
                g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
            }
        }
    }
    return 0;
}

// +0x1e8: 1417b6f80 — same shape with 14178e400
const char* CSyndicateLogic::Slot1E8(uint32_t u2,
                                      int32_t n3) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            uint64_t uSyn =
                g_fn78E400((void*)lLg, n3);
            if ((uint32_t)uSyn != 0) {
                int64_t lLg2 =
                    g_fnLgFind(((void**)this)[2],
                               (uint32_t)uSyn);
                if (lLg2 != 0) {
                    return (const char*)g_fn78F470((void*)lLg2);
                }
                g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
            }
        }
    }
    return 0;
}

// +0x1f0: 1417af4d0 — funds add with the 200000000000 cap
uint64_t CSyndicateLogic::Slot1F0(uint32_t u2, int64_t l3) {
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    if (l3 == 0) {
        // RAW: CONCAT71((int7)(in_RAX >> 8), 1)
        return 1;
    }
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    uint64_t uVar3 = 0;
    if (lLg != 0) {
        uVar3 = g_fn78F4F0((void*)lLg);
        int64_t lSum = (int64_t)uVar3 + l3;
        if (0 <= lSum && lSum < 200000000000LL) {
            return g_fn79BF80((void*)lLg, l3);
        }
    }
    return uVar3 & ~0xffULL;
}

// +0x1f8: 1417af580 — rank add with the 0x3b9aca01 cap
uint64_t CSyndicateLogic::Slot1F8(uint32_t u2, int32_t n3) {
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    if (n3 == 0) return 1;
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    uint64_t uVar2 = 0;
    if (lLg != 0) {
        uVar2 = g_fn78F550((void*)lLg);
        int32_t iVar3 = (int32_t)uVar2 + n3;
        if (0 <= iVar3 && iVar3 < 0x3b9aca01) {
            return g_fn78FA70((void*)lLg, iVar3);
        }
    }
    return uVar2 & ~0xffULL;
}

// +0x200: 1417abe70
uint64_t CSyndicateLogic::Slot200() {
    uint64_t uVar1 =
        g_fn7CAB90(((void**)this)[2]);
    // RAW: CONCAT71((int7)(uVar1 >> 8), 1)
    return (uVar1 & ~0xffULL) | 1;
}

// +0x208: 1417ab1e0
uint64_t CSyndicateLogic::Slot208(uint32_t u2, uint8_t c3) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            return g_fn78FB00((void*)lLg, c3);
        }
    }
    return 0;
}

// +0x210: 1417abfe0
uint64_t CSyndicateLogic::Slot210(uint32_t u2) {
    int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
    if (lLg != 0) {
        return g_fn78F5B0((void*)lLg);
    }
    return 0;
}

// +0x218: 1417aad30 — push the attribute-change CMsg
uint64_t CSyndicateLogic::Slot218(uint32_t u2, int32_t n3) {
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    void* plPlayer =
        g_fn78C8E0(((void**)this)[3], u2);
    if (plPlayer == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    uint64_t uCur = g_fn786440(plPlayer);
    if ((int32_t)uCur != n3) {
        g_fn786620(plPlayer, n3);
    }
    // RAW: CMsg local_418[1040] kit
    static uint8_t abMsg[1040];
    g_fn7DD6E0(abMsg);
    char cOk = g_fn7DD790(abMsg, 0x10, plPlayer);
    if (cOk != 0) {
        // RAW: box vt+0x8(box, u2, msg)
        void** pp = (void**)this;
        ((void (*)(void*, uint32_t, void*))
            (*(void***)pp[1])[0x8/8])(
                pp[1], u2, abMsg);
    }
    uint64_t uRet = g_fn7DD730(abMsg);
    // RAW: CONCAT71((int7)(uRet >> 8), 1)
    return (uRet & ~0xffULL) | 1;
}

// +0x220: 1417bd1a0 — sweep all member ids, 14179db30(lg,0x10)
// RAW models an MSVC checked-iterated std::vector<uint>;
// the _invalid_parameter_noinfo probes are iterator-safety
// no-ops modeled by std::vector itself here.
void CSyndicateLogic::Slot220() {
    static std::vector<uint32_t> vec;
    vec.clear();
    g_fn7CFA30(((void**)this)[2], &vec);
    for (uint32_t u : vec) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u);
        if (lLg != 0) {
            g_fn79DB30((void*)lLg, 0x10);
        }
    }
}

// +0x228: 1417ba5a0 — the 6-arg create + broadcast
uint64_t CSyndicateLogic::Slot228(uint32_t u2,
                                  const char* pc3,
                                  uint32_t u4, int32_t n5,
                                  uint32_t u6) {
    uint64_t uVar2 = g_fn7CE230(((void**)this)[2], u2,
                                pc3, u4, n5, u6);
    uint32_t uId = (uint32_t)uVar2;
    if (uId != 0) {
        // RAW: box vt+0x108(box, u2, id, 0)
        void** pp = (void**)this;
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t))
            (*(void***)pp[1])[0x108/8])(
                pp[1], u2, uId, 0);
        g_fn77C4F0(((void**)this)[6], uId);
        uint64_t uVar3 = g_fn7B9010(this, u2, uId);
        // RAW: CONCAT71((int7)(uVar3 >> 8), 1)
        return (uVar3 & ~0xffULL) | 1;
    }
    return uVar2 & ~0xffULL;
}

// +0x248: 1417ab1d0
uint64_t CSyndicateLogic::Slot248(uint32_t u2) {
    g_fn7CAD90(((void**)this)[2], u2);
    return 0;
}

// +0x250: 1417abc70 — name -> emoney
uint64_t CSyndicateLogic::Slot250(const char* pc2) {
    if (pc2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    } else {
        int64_t lLg = g_fn7C8AA0(((void**)this)[2], pc2);
        if (lLg != 0) {
            return g_fn78F270((void*)lLg);
        }
    }
    return 0;
}

// +0x258: 1417ab2e0
uint32_t CSyndicateLogic::Slot258(uint32_t u2) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            return g_fn78F400((void*)lLg);
        }
    }
    return 0;
}

// +0x260: 1417abc20 — in-out id probe
uint64_t CSyndicateLogic::Slot260(uint32_t* pu2) {
    uint64_t uVar1 =
        g_fn7CADE0(((void**)this)[2], *pu2);
    uint64_t uVar2 = uVar1 >> 8;
    if ((uint32_t)uVar1 != 0) {
        *pu2 = (uint32_t)uVar1;
        return (uVar2 & ~0xffULL) | 1;
    }
    return (uint64_t)(uVar2 & ~0xffULL) << 8;
}

// +0x268: 1417aaff0
uint64_t CSyndicateLogic::Slot268(uint32_t u2) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            return g_fn78F4F0((void*)lLg);
        }
    }
    return 0;
}

// +0x270: 1417aafb0
uint64_t CSyndicateLogic::Slot270(uint32_t u2, int32_t n3) {
    if (u2 != 0) {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            return g_fn79BF80((void*)lLg,
                              (int64_t)n3);
        }
    }
    return 0;
}

// +0x278: 1417ab020
uint64_t CSyndicateLogic::Slot278(uint32_t u2) {
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
    } else {
        int64_t lLg = g_fnLgFind(((void**)this)[2], u2);
        if (lLg != 0) {
            return g_fn78F550((void*)lLg);
        }
    }
    return 0;
}

// +0x280: 1417abc50
bool CSyndicateLogic::Slot280(int32_t n2) {
    return 0x3dd < n2;
}

// +0x288: 1417abc60
bool CSyndicateLogic::Slot288(int32_t n2) {
    return n2 < 0x37b;
}
// ============ D109 wave 14 (TRUE +0x230/+0x238) ============

// +0x230: 1417bd310 — the guild-disband-all flow
uint64_t CSyndicateLogic::Slot230(uint32_t u2) {
    void** pp = (void**)this;
    uint64_t uVar12 = 0xfffffffffffffffeULL;
    // RAW: the MSVC proxy pattern for a checked
    // std::vector<uint>; modeled with std::vector and
    // the raw register-leak args kept verbatim.
    static std::vector<uint32_t> vec;
    vec.clear();
    // RAW: uVar2 = box vt+0x1f8(box, u2)
    uint32_t uVar2 = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x1f8/8])(pp[1], u2);
    // RAW: lVar9 = **box (the box vtable base)
    int64_t lVar9 = **(int64_t**)pp[1];
    // RAW: box vt+0x2f0(box, uVar2, &vec, vt, 0xff..fe)
    ((void (*)(void*, uint32_t, void*,
               int64_t, uint64_t))
        (*(void***)pp[1])[0x2f0/8])(
            pp[1], uVar2, &vec, lVar9, uVar12);
    uint64_t uVar5 =
        g_fn7CEC20(pp[2], u2);
    uint32_t uVar3 = (uint32_t)uVar5;
    if (uVar3 == 0) {
        return 0;   // RAW: extraout_RAX & ~0xff
    }
    for (uint32_t uId : vec) {
        // RAW: box vt+0x108(box, uId, uVar3, vt)
        ((void (*)(void*, uint32_t, uint32_t,
                   int64_t))
            (*(void***)pp[1])[0x108/8])(
                pp[1], uId, uVar3, lVar9);
    }
    g_fn77D180(pp[7], uVar3, 2);
    g_fn77D180(pp[7], uVar3, 1);
    uVar12 = 3;
    g_fn77D180(pp[7], uVar3, 3);
    g_fn77BEB0(pp[6], uVar3, 3, lVar9);
    // RAW: box vt+0x368(box, uVar5)
    ((void (*)(void*, uint32_t))
        (*(void***)pp[1])[0x368/8])(pp[1], uVar5);
    void* puVar6 = g_fn73F9C0();
    g_fn73F4B0(puVar6, uVar3);
    if (pp[9] != 0) {
        g_fn7D4870(pp[9], uVar3, &vec, lVar9);
    }
    // RAW: CONCAT71((int7)(extraout_RAX >> 8), 1)
    return 1;
}

// +0x238: 1417ab610 — the syndicate name-change flow
uint64_t CSyndicateLogic::Slot238(uint32_t u2,
                                  const char* pc3,
                                  uint32_t u4,
                                  uint32_t u5) {
    void** pp = (void**)this;
    if (pp[3] == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    if (pp[2] == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    if (pp[1] == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    if (u2 == 0 || pc3 == 0) {
        return 0;   // RAW: in_RAX & ~0xff
    }
    // RAW: the do-while strlen loop; ~uVar7 - 1 == L
    uint64_t uVar7 = 0xffffffffffffffffULL;
    const char* pc = pc3;
    char cVar1;
    do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pc;
        pc = pc + 1;
    } while (cVar1 != '\0');
    if (((1 < ~uVar7 - 1) && (~uVar7 - 1 < 0x24)) &&
        // RAW: cVar1 = box vt+0x2e8(box, name)
        ((cVar1 = ((char (*)(void*, const char*))
            (*(void***)pp[1])[0x2e8/8])(pp[1],
                                        pc3)) != '\0')) {
        void* plVar3 = g_fn78C8E0(pp[3], u2);
        uVar7 = 0;
        if (plVar3 != 0) {
            char bVar2 = g_fn7868C0(plVar3);
            uVar7 = (uint64_t)bVar2;
            if (bVar2) {
                uVar7 = g_fn785EA0(plVar3);
                if ((uint32_t)uVar7 == 0) {
                    g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
                    return 0;
                }
                int64_t lVar4 = g_fnLgFind(pp[2],
                                           (uint32_t)uVar7);
                if (lVar4 == 0) {
                    return 0;
                }
                char bVar3 = g_fn7CD250(pp[2], pc3);
                if (!bVar3) {
                    void* pIVar5 = g_fnStringMgrInstance();
                    const void* pv = g_fnStringMgrGetStr(
                        pIVar5,
                        "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE");
                    uint64_t uVar6 =
                        ((uint64_t (*)(void*, uint32_t,
                                       const void*))
                         (*(void***)pp[1])[0x18/8])(
                             pp[1], u2, pv);
                    return uVar6 & ~0xffULL;
                }
                lVar4 = g_fn7C8AA0(pp[2], pc3);
                if (lVar4 != 0) {
                    void* pIVar5 = g_fnStringMgrInstance();
                    const void* pv = g_fnStringMgrGetStr(
                        pIVar5,
                        "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE");
                    uint64_t uVar6 =
                        ((uint64_t (*)(void*, uint32_t,
                                       const void*))
                         (*(void***)pp[1])[0x18/8])(
                             pp[1], u2, pv);
                    return uVar6 & ~0xffULL;
                }
                // RAW: box vt+0x3d8(box, u2, lg, name, u4, u5)
                uint64_t uVar6 =
                    ((uint64_t (*)(void*, uint32_t,
                                   uint32_t, const char*,
                                   uint32_t, uint32_t))
                     (*(void***)pp[1])[0x3d8/8])(
                         pp[1], u2,
                         (uint32_t)uVar7, pc3, u4, u5);
                return (uVar6 & ~0xffULL) | 1;
            }
        }
        return uVar7 & ~0xffULL;
    }
    // bad name length or vt+0x2e8 rejected
    {
        void* pIVar5 = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(
            pIVar5, "STR_INVALID_GUILD_NAME");
        uint64_t uVar7 =
            ((uint64_t (*)(void*, uint32_t,
                           const void*))
             (*(void***)pp[1])[0x18/8])(
                 pp[1], u2, pv);
        return uVar7 & ~0xffULL;
    }
}
// ============ D110 wave 15 (TRUE +0x050/+0x060/+0x120) ============

// +0x050: 1417b62e0 — the death money-spend flow
int64_t CSyndicateLogic::Slot050(uint32_t u2,
                                uint64_t u3,
                                int64_t l4) {
    (void)u3;   // RAW: param_3 unused
    void** pp = (void**)this;
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        l4 = 0;
        return l4;
    }
    int64_t lVar6 = l4;
    void* plVar3 = g_fn78C8E0(pp[3], u2);
    if (plVar3 != 0) {
        uint64_t uVar4 = g_fn785EA0(plVar3);
        int64_t lVar5 = g_fnLgFind(pp[2],
                                   (uint32_t)uVar4);
        if (lVar5 != 0) {
            int64_t lVar10 = lVar5;
            uVar4 = g_fn7AEA90(this, plVar3,
                               (void*)lVar5);
            int64_t lVar1 = ((int32_t)uVar4 * l4)
                            / 10000;
            char bVar2 = g_fn7868C0(plVar3);
            int32_t iVar9 = (int32_t)lVar1;
            if (!bVar2) {
                int32_t iVar8 = iVar9 / 10000;
                uVar4 = g_fn7862C0(plVar3);
                if (iVar8 < 1) iVar8 = 1;
                if ((int32_t)uVar4 < iVar8) {
                    if (-1 < l4) return l4;
                    return 0;
                }
                g_fn785F00(plVar3,
                           (int32_t)uVar4 - iVar8,
                           (void*)lVar10, lVar6);
            }
            lVar6 = g_fn78F4F0((void*)lVar5);
            if (lVar6 < iVar9) lVar1 = lVar6;
            iVar9 = (int32_t)lVar1;
            if (9999 < iVar9) {
                g_fn785EA0(plVar3);   // RAW: result unused
                int64_t lName =
                    (int64_t)g_fn787120(plVar3);
                // RAW: MyLogSave(file, fmt, name, u2)
                g_fnMyLogSave("gmlog/syndenote",
                    "User:%s[%u] Spend (Death Lost)"
                    " syn[%u] money %u");
            }
            g_fn79BF80((void*)lVar5, -(int64_t)iVar9);
            l4 = l4 - (int64_t)iVar9 * 100;
            void* pIVar7 = g_fnStringMgrInstance();
            int64_t lVar6b = **(int64_t**)pp[1];
            const void* pv = g_fnStringMgrGetStr(
                pIVar7, "EXPLOST_PAYBY_SYNFUND");
            // RAW: box vt+0x10(box, u2, 2000, str)
            ((void (*)(void*, uint32_t, int32_t,
                       const void*))
                (*(void***)pp[1])[0x10/8])(
                    pp[1], u2, 2000, pv);
            if (l4 < 0) l4 = 0;
        }
    }
    return l4;
}

// +0x060: 1417b64e0 — the member rank-swap flow
uint64_t CSyndicateLogic::Slot060(uint32_t u2,
                                  uint32_t u3) {
    void** pp = (void**)this;
    void* plVar3 = g_fn78C8E0(pp[3], u2);
    if (plVar3 != 0) {
        g_fn787370(plVar3, u3);
    }
    void* plVar4 = g_fn78C8E0(pp[3], u3);
    uint64_t uVar5 = 0;
    if (plVar4 != 0) {
        g_fn787370(plVar4, u2);
        uVar5 = 0;   // RAW: extraout << 8
    }
    if (plVar3 != 0 && plVar4 != 0) {
        uint64_t uLgA = g_fn785EA0(plVar3);
        uint32_t uVar1 = (uint32_t)uLgA;
        uint32_t uVar10 = (uint32_t)uLgA;
        if (uVar1 != 0) {
            uint64_t uLgB = g_fn785EA0(plVar4);
            if ((uint32_t)uLgB == uVar1) {
                int64_t lVar6 = g_fnLgFind(pp[2],
                                           uVar1);
                uVar5 = 0;
                if (lVar6 != 0) {
                    int64_t lVar7 = g_fn7A05D0(
                        (void*)lVar6, plVar3,
                        plVar4);
                    if (lVar7 == 0) {
                        lVar7 = g_fn7A05D0(
                            (void*)lVar6, plVar4,
                            plVar3);
                        plVar4 = plVar3;
                    }
                    if (lVar7 != 0 &&
                        plVar4 != 0) {
                        int64_t lR =
                            g_fn7867D0(plVar4);
                        int32_t iVar9 = 200;
                        if ((int32_t)lR == 0x398)
                            iVar9 = 0x262;
                        // RAW: box vt+0x328(box,u10)
                        uint32_t uVar2 =
                            ((uint32_t (*)
                              (void*, uint32_t))
                             (*(void***)
                              pp[1])[0x328/8])(
                                 pp[1], uVar10);
                        g_fn7A0760((void*)lVar6,
                                   plVar4, iVar9,
                                   uVar2, 0);
                    }
                    // RAW: CONCAT71((lVar7>>8), 1)
                    uVar5 = ((uint64_t)lVar7
                             & ~0xffULL) | 1;
                }
            }
            else {
                uVar5 = uVar5 & ~0xffULL;
            }
        }
    }
    return uVar5;
}

// +0x120: 1417b6ab0 — the kick-out-by-id flow
uint64_t CSyndicateLogic::Slot120(uint32_t u2,
                                  uint32_t u3) {
    void** pp = (void**)this;
    if (u2 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;   // RAW: RAX & ~0xff
    }
    if (u3 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    void* plVar3 = g_fn78C8E0(pp[3], u2);
    uint64_t uVar6 = 0;
    if (plVar3 != 0) {
        void* plVar4 = g_fn78C8E0(pp[3], u3);
        uVar6 = 0;
        if (plVar4 != 0) {
            uint64_t uVar5 = g_fn785EA0(plVar3);
            uint64_t uLgB = g_fn785EA0(plVar4);
            if ((uint32_t)uVar5 == (uint32_t)uLgB) {
                int64_t lRkA = g_fn7867D0(plVar3);
                int64_t lRkB = g_fn7867D0(plVar4);
                if ((int32_t)lRkA == 1000 ||
                    (0x397 < (int32_t)lRkA &&
                     (int32_t)lRkB < 0x2b3)) {
                    int64_t lVar8 = g_fnLgFind(
                        pp[2], (uint32_t)uVar5);
                    uVar6 = 0;
                    if (lVar8 != 0) {
                        char bVar2 =
                            g_fn78E590((void*)lVar8);
                        if (bVar2) {
                            void* pIVar9 =
                                g_fnStringMgrInstance();
                            int64_t lVt =
                                **(int64_t**)pp[1];
                            const void* pv =
                                g_fnStringMgrGetStr(
                                    pIVar9,
                                    "STR_TOO_LOWER_SYN_MONEY");
                            // RAW: box vt+0x18
                            ((uint64_t (*)
                              (void*, uint32_t,
                               const void*))
                             (*(void***)
                              pp[1])[0x18/8])(
                                 pp[1], u2, pv);
                            uVar6 = uVar6 &
                                    ~0xffULL;
                        }
                        else {
                            char szBuf[143];
                            memset(szBuf, 0, 17);
                            char* pcVar10 =
                                g_fn787120(plVar4);
                            strncpy(szBuf, pcVar10,
                                    0x10);
                            szBuf[0x10] = 0;
                            memset(szBuf + 0x11, 0,
                                   0x7f);
                            // RAW: the %lu arg was
                            // lost by the
                            // decompiler (edx)
                            snprintf(szBuf + 0x10,
                                0x80,
                                "User[%lu]"
                                " KickOutMember"
                                " By ID");
                            uVar6 = g_fn7AEBB0(
                                this, (void*)lVar8,
                                plVar4,
                                szBuf + 0x10,
                                0, 1, 0);
                            if ((char)uVar6 == 0) {
                                uVar6 = uVar6 &
                                        ~0xffULL;
                            }
                            else {
                                void* pIVar9b =
                                    g_fnStringMgrInstance();
                                int64_t lVt2 =
                                    **(int64_t**)
                                    pp[1];
                                char* pcName =
                                    g_fn787120(
                                        plVar3);
                                const void* pv2 =
                                    g_fnStringMgrGetStr(
                                        pIVar9b,
                                        "STR_KICKOUT_ME_s");
                                // RAW: box vt+0x18,
                                // 4 args
                                ((uint64_t (*)
                                  (void*, uint32_t,
                                   const void*,
                                   char*))
                                 (*(void***)
                                  pp[1])[0x18/8])(
                                     pp[1], u3,
                                     pv2, pcName);
                                char szBc
                                    [1024];
                                szBc[0] = 0;
                                memset(szBc + 1, 0,
                                       0x3ff);
                                void* pIVar9c =
                                    g_fnStringMgrInstance();
                                const void* pv3 =
                                    g_fnStringMgrGetStr(
                                        pIVar9c,
                                        "STR_KICKOUT_MEMBER_s");
                                // RAW: format args
                                // lost (varargs in
                                // registers)
                                snprintf(szBc, 0x3ff,
                                         (const char*)
                                         pv3);
                                int64_t lVt3 =
                                    **(int64_t**)
                                    pp[1];
                                uint64_t uLg =
                                    g_fn78F270(
                                        (void*)lVar8);
                                // RAW: box vt+0x88
                                ((uint64_t (*)
                                  (void*, uint32_t,
                                   void*, uint64_t))
                                 (*(void***)
                                  pp[1])[0x88/8])(
                                     pp[1],
                                     (uint32_t)
                                     (uLg &
                                      0xffffffff),
                                     szBc, 0);
                                static uint8_t
                                    abMsg[1072];
                                g_fn7DB2B0(abMsg);
                                uVar6 =
                                    g_fn7DB3A0(
                                        abMsg,
                                        0x2c, 0);
                                if ((char)uVar6 != 0) {
                                    // RAW: box vt+8
                                    ((void (*)
                                      (void*, uint32_t,
                                       void*))
                                     (*(void***)
                                      pp[1])[8/8])(
                                         pp[1], u2,
                                         abMsg);
                                }
                                uint64_t uVar5b =
                                    g_fn7DB330(
                                        abMsg);
                                uVar6 = (uVar5b &
                                         ~0xffULL)|1;
                            }
                        }
                    }
                }
                else {
                    uVar6 = uVar6 & ~0xffULL;
                }
            }
            else {
                uVar6 = uVar6 & ~0xffULL;
            }
        }
    }
    return uVar6;
}
// ============ D111 wave 16 (TRUE +0x038/+0x0e8/+0x118) ============

// +0x038: 1417c0510 — the targeted-guild member
// sweep/broadcast flow
void CSyndicateLogic::Slot038(uint32_t u2, int64_t l3) {
    void** pp = (void**)this;
    if (l3 != 0 && pp[1] != 0) {
        void* plVar5 = g_fn78C8E0(pp[3], u2);
        if (plVar5 != 0) {
            uint64_t uVar6 = g_fn785EA0(plVar5);
            int64_t lVar7 = g_fnLgFind(pp[2],
                                       (uint32_t)uVar6);
            if (lVar7 != 0) {
                char bVar3 = g_fn78E590(
                    (void*)lVar7);
                if (bVar3) {
                    void* pIVar8 =
                        g_fnStringMgrInstance();
                    int64_t lVt = **(int64_t**)pp[1];
                    const void* pv =
                        g_fnStringMgrGetStr(pIVar8,
                            "STR_TOO_LOWER_SYN_MONEY");
                    ((uint64_t (*)(void*, uint32_t,
                                   const void*))
                     (*(void***)pp[1])[0x18/8])(
                         pp[1], u2, pv);
                    (void)lVt;
                }
                else {
                    // RAW: the MSVC checked-vector
                    // proxy (1417495d0 init +
                    // 141732040 push) modeled
                    // with std::vector
                    static std::vector<uint32_t>
                        vAll, vMatch;
                    vAll.clear(); vMatch.clear();
                    // RAW: box vt+0x50(box, &v, u2, 0)
                    ((void (*)(void*, void*,
                               uint32_t, uint64_t))
                     (*(void***)pp[1])[0x50/8])(
                         pp[1], &vAll, u2, 0);
                    for (uint32_t uId : vAll) {
                        // RAW: box vt+0x1f8() —
                        // the id arg was lost by
                        // the decompiler
                        uint32_t uVar4 =
                            ((uint32_t (*)
                              (void*, uint32_t))
                             (*(void***)
                              pp[1])[0x1f8/8])(
                                 pp[1], uId);
                        if (uId != 0 &&
                            uVar4 != 0) {
                            if ((uint32_t)uVar6 ==
                                uVar4 ||
                                g_fn797750(
                                    (void*)lVar7,
                                    uVar4) != 0) {
                                vMatch.push_back(
                                    uId);
                            }
                        }
                    }
                    // RAW: (end - begin & ~3) == 0
                    if (!vMatch.empty()) {
                        // RAW: box vt+0x48(box,
                        // param_3, &vMatch)
                        ((void (*)(void*, int64_t,
                                   void*))
                         (*(void***)pp[1])[0x48/8])(
                             pp[1], l3, &vMatch);
                    }
                }
            }
        }
    }
    return;
}

// +0x0e8: 1417ba6f0 — the leader demise/abdicate flow
char CSyndicateLogic::Slot0e8(uint32_t u2,
                              const char* pc3,
                              char c4) {
    void** pp = (void**)this;
    if (pc3 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;
    }
    void* plVar8 = g_fn78C8E0(pp[3], u2);
    char uVar3 = 0;
    if (plVar8 != 0) {
        uint64_t uVar9 = g_fn785EA0(plVar8);
        uint32_t uVar4 = (uint32_t)uVar9;
        int64_t lVar10 = g_fnLgFind(pp[2], uVar4);
        uVar3 = 0;
        if (lVar10 != 0) {
            char bVar1 = g_fn7868C0(plVar8);
            uVar3 = 0;
            if (bVar1) {
                std::string sName(pc3);
                void* plVar11 = g_fn78C9F0(
                    pp[3], &sName);
                if (plVar11 == 0) {
                    uVar3 = 0;
                }
                else {
                    char cVar2 =
                        g_fn787300(plVar11);
                    if (cVar2 == 0) {
                        void* pIVar12 =
                            g_fnStringMgrInstance();
                        const void* pv =
                            g_fnStringMgrGetStr(
                                pIVar12,
                                "STR_SYN_APPOINT_TARGET_OFFLINE");
                        ((uint64_t (*)
                          (void*, uint32_t,
                           const void*))
                         (*(void***)pp[1])[0x18/8])(
                             pp[1], u2, pv);
                        uVar3 = 0;
                    }
                    else {
                        uint64_t uVar14 =
                            g_fn785DC0(plVar11);
                        uint32_t uVar5 =
                            (uint32_t)uVar14;
                        if (u2 == uVar5) {
                            uVar3 = 0;
                        }
                        else {
                            uint64_t uVar13 =
                                g_fn785EA0(
                                    plVar11);
                            if (uVar4 ==
                                (uint32_t)uVar13) {
                                uVar13 =
                                    g_fn7867D0(
                                        plVar11);
                                char uVar15 =
                                    g_fn786960(
                                        plVar11);
                                if (uVar15 == 0 ||
                                    (int32_t)uVar13
                                        == 0x25a) {
                                    // RAW: box
                                    // vt+0x328
                                    uint32_t uVar6 =
                                        ((uint32_t (*)
                                          (void*,
                                           uint32_t))
                                         (*(void***)
                                          pp[1])
                                          [0x328/8])(
                                             pp[1],
                                             uVar9 &
                                             0xffffffff);
                                    g_fn79F650(
                                        (void*)lVar10,
                                        plVar8, 200);
                                    g_fn7C6BD0(
                                        pp[2],
                                        plVar8,
                                        (void*)lVar10,
                                        uVar6);
                                    char bA =
                                        g_fn787390(
                                            plVar8);
                                    if (bA) {
                                        uint64_t uVar7 =
                                            g_fn787380(
                                                plVar8);
                                        void* plVar16 =
                                            g_fn78C8E0(
                                                pp[3],
                                                (uint32_t)
                                                uVar7);
                                        if (plVar16 != 0 &&
                                            (uint32_t)
                                            g_fn785EA0(
                                                plVar16)
                                            == uVar4 &&
                                            (int32_t)
                                            g_fn7867D0(
                                                plVar16)
                                            == 0x398) {
                                            g_fn7A0760(
                                                (void*)lVar10,
                                                plVar16,
                                                200,
                                                uVar6,
                                                0);
                                            g_fn79F650(
                                                (void*)lVar10,
                                                plVar16,
                                                200);
                                            g_fn7C6BD0(
                                                pp[2],
                                                plVar16,
                                                (void*)lVar10,
                                                uVar6);
                                        }
                                    }
                                    g_fn79FA60(
                                        (void*)lVar10,
                                        u2);
                                    g_fn79F650(
                                        (void*)lVar10,
                                        plVar11,
                                        1000);
                                    g_fn78F900(
                                        (void*)lVar10,
                                        pc3);
                                    g_fn78F960(
                                        (void*)lVar10,
                                        uVar5);
                                    g_fn7C6BD0(
                                        pp[2], plVar11,
                                        (void*)lVar10,
                                        uVar6);
                                    char szBc[1025];
                                    if (c4 == 0) {
                                        void* pIV =
                                            g_fnStringMgrInstance();
                                        const void* pvF =
                                            g_fnStringMgrGetStr(
                                                pIV,
                                                "STR_DEMISE_SUCCESS");
                                        char* pcName =
                                            g_fn787120(
                                                plVar8);
                                        snprintf(szBc,
                                            0x400,
                                            (const char*)
                                            pvF, pcName);
                                    }
                                    else {
                                        void* pIV =
                                            g_fnStringMgrInstance();
                                        const void* pvF =
                                            g_fnStringMgrGetStr(
                                                pIV,
                                                "STR_SYN_REPLACE_SUCCESS");
                                        snprintf(szBc,
                                            0x400,
                                            (const char*)
                                            pvF, pc3);
                                    }
                                    szBc[1024] = 0;
                                    uint64_t uLg =
                                        g_fn78F270(
                                            (void*)lVar10);
                                    ((uint64_t (*)
                                      (void*, uint32_t,
                                       void*, uint64_t))
                                     (*(void***)
                                      pp[1])[0x88/8])(
                                         pp[1],
                                         (uint32_t)
                                         (uLg &
                                          0xffffffff),
                                         szBc, 0);
                                    static uint8_t
                                        abMsgA[1072],
                                        abMsgB[1072];
                                    if (c4 == 0) {
                                        g_fn7DB2B0(
                                            abMsgA);
                                        uint64_t uR =
                                            g_fn7DB630(
                                                abMsgA,
                                                0x27,
                                                1000,
                                                uVar6,
                                                (void*)pc3);
                                        if ((char)uR) {
                                            ((void (*)
                                              (void*,
                                               uint32_t,
                                               void*))
                                             (*(void***)
                                              pp[1])[8/8])(
                                                 pp[1],
                                                 u2,
                                                 abMsgA);
                                        }
                                        g_fn7DB2B0(
                                            abMsgB);
                                        char* pcName =
                                            g_fn787120(
                                                plVar8);
                                        uR =
                                            g_fn7DB630(
                                                abMsgB,
                                                0x28,
                                                1000,
                                                uVar6,
                                                pcName);
                                        if ((char)uR) {
                                            ((void (*)
                                              (void*,
                                               uint32_t,
                                               void*))
                                             (*(void***)
                                              pp[1])[8/8])(
                                                 pp[1],
                                                 (uint32_t)
                                                 (uVar14 &
                                                  0xffffffff),
                                                 abMsgB);
                                        }
                                        g_fn7DB330(
                                            abMsgB);
                                        g_fn7DB330(
                                            abMsgA);
                                    }
                                    else {
                                        g_fn7DB2B0(
                                            abMsgA);
                                        char* pcName =
                                            g_fn787120(
                                                plVar8);
                                        uint64_t uR =
                                            g_fn7DB630(
                                                abMsgA,
                                                0x2e,
                                                1000,
                                                uVar6,
                                                pcName);
                                        if ((char)uR) {
                                            ((void (*)
                                              (void*,
                                               uint32_t,
                                               void*))
                                             (*(void***)
                                              pp[1])[8/8])(
                                                 pp[1],
                                                 (uint32_t)
                                                 (uVar14 &
                                                  0xffffffff),
                                                 abMsgA);
                                        }
                                        // RAW: box
                                        // vt+0x3b8
                                        void* pIV =
                                            g_fnStringMgrInstance();
                                        const void* pvL =
                                            g_fnStringMgrGetStr(
                                                pIV,
                                                "STR_SYN_REPLACE_SUCCESS_LEAVEWORD");
                                        uint64_t uDc =
                                            g_fn785DC0(
                                                plVar8);
                                        int64_t lF4 =
                                            g_fn78F4E0(
                                                (void*)lVar10);
                                        ((void (*)
                                          (void*, int64_t,
                                           uint32_t,
                                           const void*))
                                         (*(void***)
                                          pp[1])
                                          [0x3b8/8])(
                                              pp[1],
                                              lF4,
                                              (uint32_t)
                                              (uDc &
                                               0xffffffff),
                                              pvL);
                                        g_fn7DB330(
                                            abMsgA);
                                    }
                                    char bB =
                                        g_fn787390(
                                            plVar11);
                                    if (bB) {
                                        uint64_t uVar7 =
                                            g_fn787380(
                                                plVar11);
                                        void* plV8 =
                                            g_fn78C8E0(
                                                pp[3],
                                                (uint32_t)
                                                uVar7);
                                        if (plV8 != 0 &&
                                            (uint32_t)
                                            g_fn785EA0(
                                                plV8)
                                            == uVar4) {
                                            int64_t lR =
                                                g_fn7867D0(
                                                    plV8);
                                            if ((int32_t)lR
                                                != 0x3de) {
                                                lR =
                                                    g_fn7867D0(
                                                        plV8);
                                                if ((int32_t)lR
                                                    != 0x3d4 &&
                                                    g_fn786960(
                                                        plV8)
                                                    == 0) {
                                                    g_fn79F650(
                                                        (void*)lVar10,
                                                        plV8,
                                                        0x398);
                                                    g_fn7C6BD0(
                                                        pp[2],
                                                        plV8,
                                                        (void*)lVar10,
                                                        uVar6);
                                                    g_fn7A0760(
                                                        (void*)lVar10,
                                                        plV8,
                                                        0x262,
                                                        uVar6,
                                                        0);
                                                }
                                            }
                                        }
                                    }
                                    g_fn7A0760(
                                        (void*)lVar10,
                                        plVar11, 200,
                                        uVar6, 0);
                                    g_fn79E020(
                                        (void*)lVar10);
                                    uint64_t uP =
                                        g_fn790390(
                                            (void*)lVar10);
                                    if ((int32_t)uP
                                        != 0) {
                                        uP =
                                            g_fn790390(
                                                (void*)lVar10);
                                        uint64_t uChk =
                                            g_fn763680(
                                                pp[10],
                                                (uint32_t)uP);
                                        uint64_t uLg2 =
                                            g_fn78F270(
                                                (void*)lVar10);
                                        if ((int32_t)uChk ==
                                            (int32_t)uLg2) {
                                            uP =
                                                g_fn790390(
                                                    (void*)lVar10);
                                            g_fn7B92B0(
                                                this, u2,
                                                uVar5,
                                                (uint32_t)uP,
                                                pc3);
                                        }
                                    }
                                    g_fnMyLogSave(
                                        "gmlog/syn_demise",
                                        "player:%u to player:%u %s");
                                    uVar3 = 1;
                                }
                                else {
                                    uVar3 = 0;
                                }
                            }
                            else {
                                uVar3 = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return uVar3;
}

// +0x118: 1417b6770 — the kick-out-by-name flow
uint64_t CSyndicateLogic::Slot118(uint32_t u2,
                                  const char* pc3) {
    void** pp = (void**)this;
    if (pc3 == 0) {
        g_fnT1LogError("\xa1\xef%s(%s)\xa1\xef in %s, %d");
        return 0;   // RAW: RAX & ~0xff
    }
    void* plVar4 = g_fn78C8E0(pp[3], u2);
    uint64_t uVar7 = 0;
    if (plVar4 != 0) {
        std::string sName(pc3);
        void* plVar5 = g_fn78C9F0(pp[3], &sName);
        if (plVar5 == 0) {
            uVar7 = uVar7 & ~0xffULL;
        }
        else {
            uint64_t uVar6 = g_fn785EA0(plVar4);
            uVar7 = g_fn785EA0(plVar5);
            if ((uint32_t)uVar7 == (uint32_t)uVar6) {
                int64_t uVar8 = g_fn7867D0(plVar4);
                uVar7 = g_fn7867D0(plVar5);
                if ((int32_t)uVar8 == 1000 ||
                    (0x397 < (int32_t)uVar8 &&
                     (int32_t)uVar7 < 0x2b3)) {
                    int64_t lVar9 = g_fnLgFind(
                        pp[2], (uint32_t)uVar6);
                    uVar7 = 0;
                    if (lVar9 != 0) {
                        char bVar2 = g_fn78E590(
                            (void*)lVar9);
                        if (bVar2) {
                            void* pIVar10 =
                                g_fnStringMgrInstance();
                            const void* pv =
                                g_fnStringMgrGetStr(
                                    pIVar10,
                                    "STR_TOO_LOWER_SYN_MONEY");
                            ((uint64_t (*)
                              (void*, uint32_t,
                               const void*))
                             (*(void***)pp[1])
                              [0x18/8])(
                                  pp[1], u2, pv);
                            uVar7 = uVar7 &
                                    ~0xffULL;
                        }
                        else {
                            uint64_t uVar11 =
                                g_fn785DC0(
                                    plVar5);
                            char cVar3 =
                                g_fn787300(
                                    plVar5);
                            char szBuf[129];
                            szBuf[0] = 0;
                            memset(szBuf + 1, 0,
                                   0x7f);
                            snprintf(szBuf, 0x80,
                                "User[%lu]"
                                " KickOutMember"
                                " By Name",
                                (unsigned long)u2);
                            uVar7 = g_fn7AEBB0(
                                this, (void*)lVar9,
                                plVar5, szBuf, 0,
                                1, 0);
                            if ((char)uVar7 == 0) {
                                uVar7 = uVar7 &
                                        ~0xffULL;
                            }
                            else {
                                void* plV5 =
                                    g_fn796390(
                                        (void*)lVar9,
                                        (int32_t)
                                        uVar11);
                                if (plV5 != 0) {
                                    g_fn786E30(
                                        plV5, 0);
                                }
                                if (cVar3 != 0) {
                                    void* pIV =
                                        g_fnStringMgrInstance();
                                    int64_t lVt =
                                        **(int64_t**)
                                        pp[1];
                                    char* pcName =
                                        g_fn787120(
                                            plVar4);
                                    const void* pv2 =
                                        g_fnStringMgrGetStr(
                                            pIV,
                                            "STR_KICKOUT_ME_s");
                                    // RAW: box
                                    // vt+0x18, 4 args
                                    ((uint64_t (*)
                                      (void*, uint32_t,
                                       const void*,
                                       char*))
                                     (*(void***)
                                      pp[1])[0x18/8])(
                                         pp[1],
                                         (uint32_t)
                                         (uVar11 &
                                          0xffffffff),
                                         pv2, pcName);
                                    (void)lVt;
                                }
                                char szBc[1025];
                                szBc[0] = 0;
                                memset(szBc + 1, 0,
                                       0x3ff);
                                void* pIV2 =
                                    g_fnStringMgrInstance();
                                const void* pv3 =
                                    g_fnStringMgrGetStr(
                                        pIV2,
                                        "STR_KICKOUT_MEMBER_s");
                                snprintf(szBc, 0x3ff,
                                         (const char*)
                                         pv3, pc3);
                                szBc[1024] = 0;
                                int64_t lVt2 =
                                    **(int64_t**)
                                    pp[1];
                                uint64_t uLg =
                                    g_fn78F270(
                                        (void*)lVar9);
                                ((uint64_t (*)
                                  (void*, uint32_t,
                                   void*, uint64_t))
                                 (*(void***)
                                  pp[1])[0x88/8])(
                                     pp[1],
                                     (uint32_t)
                                     (uLg &
                                      0xffffffff),
                                     szBc, 0);
                                (void)lVt2;
                                static uint8_t
                                    abMsg[1072];
                                g_fn7DB2B0(abMsg);
                                uVar7 =
                                    g_fn7DB3A0(
                                        abMsg,
                                        0x2c, 0);
                                if ((char)uVar7 != 0) {
                                    ((void (*)
                                      (void*, uint32_t,
                                       void*))
                                     (*(void***)
                                      pp[1])[8/8])(
                                         pp[1], u2,
                                         abMsg);
                                }
                                uint64_t uVar6b =
                                    g_fn7DB330(
                                        abMsg);
                                uVar7 = (uVar6b &
                                         ~0xffULL)|1;
                            }
                        }
                    }
                }
                else {
                    uVar7 = uVar7 & ~0xffULL;
                }
            }
            else {
                uVar7 = uVar7 & ~0xffULL;
            }
        }
    }
    return uVar7;
}




// ============================================================
// D112 — wave 17 (TRUE offsets +0x2e0..+0x370), 19 bodies,
// raw-verified against Syndicate.dll (imagebase 0x141720000).
// ============================================================

// ---- the D112 seams (default null — tests bind them) ----
void*    (*g_fn1417c8c10)(void*, uint32_t);
void*    (*g_fn1417c8d80)(void*, uint32_t);
void     (*g_fn1417cb270)(void*, uint32_t);
void     (*g_fn1417cb360)(void*, uint32_t, uint32_t);
void*    (*g_fn141790100)(void*);
uint32_t (*g_fn14178f790)(void*);
uint64_t (*g_fn14178f7d0)(void*, uint32_t);
uint64_t (*g_fn14178f7b0)(void*, int64_t, int64_t,
                          int64_t);
void     (*g_fn1417c6c90)(void*);
void     (*g_fn1417c6c80)(void*);
void     (*g_fn1417cfb60)(void*, uint32_t);
void     (*g_fn1417a8d30)(void*, uint32_t, uint32_t);
void     (*g_fn1417a8e40)(void*, uint32_t, int32_t,
                          uint32_t, uint32_t);
void     (*g_fn1417a8f70)(void*, uint32_t, int32_t,
                          uint32_t, uint32_t);
void     (*g_fn1417a8810)(void*, uint32_t);
void     (*g_fn1417a88a0)(void*, uint32_t, void*);
void     (*g_fn1417a8b00)(void*, uint32_t);
void     (*g_fn1417a7e70)(void*);
uint8_t  (*g_fn1417a8a50)(void*, uint32_t, void*);
void     (*g_fn14179d3c0)(void*, int32_t, int32_t);

// ---- the D112 seam defaults ----
static void DefSynLogCheck(const char*, const char*,
                           const char*, const char*,
                           uint32_t) {}
static void DefSynNoteLog(const char*, const char*,
                          const void*, uint32_t,
                          uint32_t, uint32_t) {}
// KERNEL32 MulDiv semantics: (a*b)/c rounded to the
// nearest integer; 0 on overflow or c==0.
static int32_t DefMulDiv(uint32_t a, uint32_t b,
                         uint32_t c) {
    if (c == 0) return 0;
    uint64_t n = (uint64_t)a * b;
    if (n > 0x7fffffffull * (uint64_t)c) return 0;
    uint64_t q = n / c, r = n % c;
    if (r * 2 >= c) ++q;          // round to nearest
    return (int32_t)q;
}
char     (*g_fn1417bf960)(void*, void*) = nullptr;
char     (*g_fn14179e6d0)(void*, void*) = nullptr;
char     (*g_fn141787300)(void*) = nullptr;
uint32_t (*g_fn141785dc0)(void*) = nullptr;
uint32_t (*g_fn14178f270)(void*) = nullptr;
void     (*g_fn14176aca0)(void*, uint32_t) = nullptr;
void     (*g_fn14174d490)(void*, uint32_t) = nullptr;
uint32_t (*g_fn141743c80)(void*) = nullptr;
int32_t  (*g_fn141743e60)(void*) = nullptr;
void     (*g_fn1417c1180)(void*, uint32_t, uint32_t) = nullptr;
void     (*g_fn1417b1090)(void*, uint32_t) = nullptr;
void*    (*g_fn1417f3166)(uint32_t) = nullptr;
void     (*g_fn1417f2fdc)(void*) = nullptr;
void     (*g_fn1417f30c0)(void*, int, size_t) = nullptr;
void*    (*g_fn141823050)(void) = nullptr;
int      (*g_fn1418233c8)(char*, size_t, const char*, void*) = nullptr;
void (*g_fnSynLogCheck)(const char*, const char*,
    const char*, const char*, uint32_t) = DefSynLogCheck;
void (*g_fnSynNoteLog)(const char*, const char*,
    const void*, uint32_t, uint32_t, uint32_t) =
    DefSynNoteLog;
int32_t (*g_fnMulDiv)(uint32_t, uint32_t, uint32_t) =
    DefMulDiv;
// the ORIGINAL source path literal in the star logs
static const char* s_pszLogicSrc =
    "f:\\version\\cqserver-78.0.11-1204\\modules"
    "\\syndicate\\src\\syndicatelogic.cpp";
// the RAW fmt DAT_141824ca8 (GBK \xa1\xef = ★)
#define STAR_FMT "\xa1\xef%s(%s)\xa1\xef in %s, %d"

// ================= +0x2e0: 1417af7d0 =================
// the 9-field clear: cb270(mgr,u2) then cb360 for the
// fields 1..9; miss -> the star log (dUser/pSyn,
// line 0x1487) -> 0; always returns 1 on success.
uint8_t CSyndicateLogic::Slot2E0(uint32_t u2) {
    void** pp = (void**)this;
    void* pSyn = (void*)g_fnLgFind(pp[2], u2);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "dUser", "pSyn",
                        s_pszLogicSrc, 0x1487);
        return 0;
    }
    g_fn1417cb270(pp[2], u2);
    g_fn1417cb360(pp[2], u2, 1);
    g_fn1417cb360(pp[2], u2, 2);
    g_fn1417cb360(pp[2], u2, 3);
    g_fn1417cb360(pp[2], u2, 4);
    g_fn1417cb360(pp[2], u2, 5);
    g_fn1417cb360(pp[2], u2, 6);
    g_fn1417cb360(pp[2], u2, 7);
    g_fn1417cb360(pp[2], u2, 8);
    g_fn1417cb360(pp[2], u2, 9);
    return 1;
}

// ================= +0x2e8: 1417af8e0 =================
// find -> 90100(syn) != 0; the star log on miss
// (CHECKF/pSyn, line 0x149a).
uint8_t CSyndicateLogic::Slot2E8(uint32_t u2) {
    void** pp = (void**)this;
    void* pSyn = (void*)g_fnLgFind(pp[2], u2);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "CHECKF", "pSyn",
                        s_pszLogicSrc, 0x149a);
        return 0;
    }
    return g_fn141790100(pSyn) != 0;
}

// ================= +0x2f0: 1417af940 =================
// find -> the f790 tail; the star log on miss
// (CHECKF/pSyn, line 0x14a2).
uint32_t CSyndicateLogic::Slot2F0(uint32_t u2) {
    void** pp = (void**)this;
    void* pSyn = (void*)g_fnLgFind(pp[2], u2);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "CHECKF", "pSyn",
                        s_pszLogicSrc, 0x14a2);
        return 0;
    }
    return g_fn14178f790(pSyn);
}

// ================= +0x2f8: 1417af990 =================
// find -> the f7d0(syn, p3) tail; the star log on miss
// (dUser/pSyn, line 0x14aa). RAW: ebx = r8d rides the
// second arg straight into the tail.
uint64_t CSyndicateLogic::Slot2F8(uint32_t u2,
                                  uint32_t u3) {
    void** pp = (void**)this;
    void* pSyn = (void*)g_fnLgFind(pp[2], u2);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "dUser", "pSyn",
                        s_pszLogicSrc, 0x14aa);
        return 0;
    }
    return g_fn14178f7d0(pSyn, u3);
}

// ================= +0x300: 1417af9f0 =================
// find -> the f7b0(syn, p3, p4, p5) tail — p5 rides
// the first STACK slot; the star log on miss
// (CHECKF/pSyn, line 0x14b2).
uint64_t CSyndicateLogic::Slot300(uint32_t u2,
    int64_t l3, int64_t l4, int64_t l5) {
    void** pp = (void**)this;
    void* pSyn = (void*)g_fnLgFind(pp[2], u2);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "CHECKF", "pSyn",
                        s_pszLogicSrc, 0x14b2);
        return 0;
    }
    return g_fn14178f7b0(pSyn, l3, l4, l5);
}

// ================= +0x308: 1417ac2d0 =================
// the SynWar prize cut (the 2% flow):
//   p4<=0 -> 0; box vt+0x1f8(box) [NO 2nd arg] -> synA;
//   0 -> 0; box vt+0x2f8(box, p3) -> synB; synA==synB ->
//   0; the leagues find pair; cut = MulDiv(p4,2,100);
//   cut>0: cap by f4f0(synB) (cmovg), >=10000 -> the
//   gmlog/syndenote save, bf80(synB,-cut), box
//   vt+0x138(box,p2,cut,1); then ALWAYS d3c0(synA,p3,p4)
//   when synA!=0 -> return 1.
char CSyndicateLogic::Slot308(uint32_t u2,
                              uint32_t u3, int32_t n4) {
    if (n4 <= 0)
        return 0;
    void** pp = (void**)this;
    // RAW: mov rcx,[rcx+8]; call [rax+0x1f8] — single arg
    uint32_t uSynA = ((uint32_t (*)(void*))
        (*(void***)pp[1])[0x1f8 / 8])(pp[1]);
    if (uSynA == 0)
        return 0;
    uint32_t uSynB = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x2f8 / 8])(pp[1], u3);
    if (uSynA == uSynB)
        return 0;
    void* pSynA = (void*)g_fnLgFind(pp[2], uSynA);
    void* pSynB = (void*)g_fnLgFind(pp[2], uSynB);
    // RAW: MulDiv(p4, 2, 100) — the 2% cut
    int32_t nCut = g_fnMulDiv((uint32_t)n4, 2, 100);
    if (nCut > 0) {
        if (pSynB != 0) {
            uint32_t uCap =
                (uint32_t)g_fn78F4F0(pSynB);
            // RAW: cmp ebx,eax; cmovg ebx,eax (min)
            if (nCut > (int32_t)uCap)
                nCut = (int32_t)uCap;
        }
        if (nCut >= 0x2710) {
            // RAW: box vt+0x1d8(box, p2) -> the name
            const void* pvName = ((const void* (*)(
                void*, uint32_t))
                (*(void***)pp[1])[0x1d8 / 8])(pp[1], u2);
            // RAW: MyLogSave(file, fmt, name(r8),
            // actor(r9=p2), synA([rsp+0x20]),
            // cut([rsp+0x28]))
            g_fnSynNoteLog("gmlog/syndenote",
                "User:%s[%u] Get (SynWar Prize) "
                "syn[%u] money %u",
                pvName, u2, uSynA, (uint32_t)nCut);
        }
        // RAW: eax=ebx; neg; movsxd -> bf80(synB, -cut)
        g_fn79BF80(pSynB, -(int64_t)nCut);
        // RAW: movsxd r8,ebx; mov r9b,1; edx=p2
        ((void (*)(void*, uint32_t, int64_t,
                   uint8_t))
            (*(void***)pp[1])[0x138 / 8])(
                pp[1], u2, (int64_t)nCut, 1);
    }
    if (pSynA != 0)
        g_fn14179d3c0(pSynA, (int32_t)u3, n4);
    return 1;
}

// ================= +0x310: 1417bd550 =================
// the targeted war-status sweep:
//   vt+0x2f8(box) [NO args] -> id; 0 -> out;
//   cad00(mgr,id)==0 -> out; new(8) sentinel;
//   vt+0x2b0(this, id, &anchorHome) -> ok; then for
//   each u32 in the vector: box vt+0x268(box, id) ->
//   fire vt+0x2e0(box, id, 0x283e); the cleanup deletes
//   the buffer then the sentinel node.
void CSyndicateLogic::Slot310(void) {
    void** pp = (void**)this;
    uint32_t uId = ((uint32_t (*)(void*))
        (*(void***)pp[1])[0x2f8 / 8])(pp[1]);
    if (uId == 0)
        return;
    void* pMember = (void*)g_fnLgFind(pp[2], uId);
    if (pMember == 0)
        return;
    // RAW: operator new(8) then *node = &home
    void** pNode = (void**)operator new(8);
    void* apHome[3] = {0};
    if (pNode != 0) {
        *pNode = apHome;
        apHome[0] = pNode;
    }
    // RAW: the vector {begin, end, cap} zeroed
    uint32_t* puBegin = 0; uint32_t* puEnd = 0;
    uint32_t* puCap = 0;
    // RAW: this+0 -> the vtable (lea rax,[rbp]) slot 0x2b0
    char bOk = ((char (*)(void*, uint32_t, void*))
        (*(void***)pp)[0x2b0 / 8])(
            this, uId, apHome);
    if (bOk != 0 &&
        (puEnd != 0) &&
        (((uintptr_t)puEnd - (uintptr_t)puBegin) >> 2
         != 0)) {
        for (uint32_t* pu = puBegin; pu != puEnd;
             ++pu) {
            // RAW: the checked-vector re-validation
            // hops (4x _invalid_parameter_noinfo)
            // ride before each deref — kept as the
            // raw read below
            uint32_t uOne = *pu;
            // RAW: box vt+0x268(box, id) — TRUE -> send
            char bLive = ((char (*)(void*, uint32_t))
                (*(void***)pp[1])[0x268 / 8])(
                    pp[1], uOne);
            if (bLive != 0) {
                ((void (*)(void*, uint32_t, uint32_t))
                    (*(void***)pp[1])[0x2e0 / 8])(
                        pp[1], uOne, 0x283e);
            }
        }
    }
    // the RAW cleanup: delete[] the buffer, zero the
    // trio, delete the sentinel node
    ::operator delete(puBegin);
    puBegin = 0; puEnd = 0; puCap = 0;
    ::operator delete(apHome[0]);
}

// ============ +0x318/+0x320/+0x330: the mgr pass-throughs ============
// RAW: rcx = [this+0x10]; c6c90/c6c80/cfb60(mgr, u2)
uint8_t CSyndicateLogic::Slot318(void) {
    g_fn1417c6c90(*(void**)((char*)this + 0x10));
    return 1;
}
uint8_t CSyndicateLogic::Slot320(void) {
    g_fn1417c6c80(*(void**)((char*)this + 0x10));
    return 1;
}
// RAW: ab1a0 — cfb60(mgr, u2) with the edx ride
uint8_t CSyndicateLogic::Slot330(uint32_t u2) {
    g_fn1417cfb60(*(void**)((char*)this + 0x10), u2);
    return 1;
}

// ============ +0x338..+0x370: the box(+0x20) forwards ============
// RAW: af290 — the null gate on this+0x20
void CSyndicateLogic::Slot338(uint32_t u2, uint32_t u3) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox != 0)
        g_fn1417a8d30(pBox, u2, u3);
}
// RAW: af230 — NO null gate, 5 args ride through
void CSyndicateLogic::Slot340(uint32_t u2, int32_t n3,
                              uint32_t u4, uint32_t u5) {
    g_fn1417a8e40(*(void**)((char*)this + 0x20),
                  u2, n3, u4, u5);
}
// RAW: af250 — NO null gate, the mirror
void CSyndicateLogic::Slot348(uint32_t u2, int32_t n3,
                              uint32_t u4, uint32_t u5) {
    g_fn1417a8f70(*(void**)((char*)this + 0x20),
                  u2, n3, u4, u5);
}
// RAW: af270 — the gate + a8810(box, u2)
void CSyndicateLogic::Slot350(uint32_t u2) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox != 0)
        g_fn1417a8810(pBox, u2);
}
// RAW: af2b0 — the gate + a88a0(box, u2, p3)
void CSyndicateLogic::Slot358(uint32_t u2, void* p3) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox != 0)
        g_fn1417a88a0(pBox, u2, p3);
}
// RAW: af2d0 — the gate + a8b00(box, u2)
void CSyndicateLogic::Slot360(uint32_t u2) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox != 0)
        g_fn1417a8b00(pBox, u2);
}
// RAW: afb00 — the gate + a7e70(box)
void CSyndicateLogic::Slot368(void) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox != 0)
        g_fn1417a7e70(pBox);
}
// RAW: af2f0 — the gate then the a8a50 TAIL; the miss
// path returns `xor al, al` (0 in AL only)
uint8_t CSyndicateLogic::Slot370(uint32_t u2, void* p3) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox == 0)
        return 0;
    return g_fn1417a8a50(pBox, u2, p3);
}

// ================= +0x328: 1417ab340 =================
// the SynWar prize flow (the giant, 706 bytes):
//   c8c10(mgr,u2) -> the war record (0 -> out);
//   (void)c8d80(mgr,u2) — the RAW side-effect call with
//   the return DISCARDED; f270(rec)==0 -> out;
//   vt+0x2f8(box,u2) -> the league id; !=0: its record;
//   f4f0>0: the x*10/10 magic (sar 6 + the sign fix) ->
//   bf80(league,-x) + bf80(rec,+x);
//   always: vt+0x308(box,u2, f270&0xffffffff); the
//   STR_GOT_WIN_s notify (ONE snprintf vararg = the
//   f470 name) via vt+0x78; vt+0x300 -> warId; when
//   warId==0x40e: db3a0(msg,0x11,f318ret) with the
//   IF_OK(SET_WHITE_SYN) log on miss, line 0x664; when
//   warId==1000: the mirror with 0x12 (SET_BLACK_SYN),
//   line 0x66c; both end in the dtor.
uint8_t CSyndicateLogic::Slot328(uint32_t u2) {
    void** pp = (void**)this;
    void* pWarRec = g_fn1417c8c10(pp[2], u2);
    // RAW: the second lookup call fires UNCONDITIONALLY
    // with its return thrown away
    (void)g_fn1417c8d80(pp[2], u2);
    if (pWarRec == 0)
        return 0;
    if (g_fn78F270(pWarRec) == 0)
        return 0;
    uint32_t uLgId = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x2f8 / 8])(pp[1], u2);
    if (uLgId != 0) {
        void* pLg = (void*)g_fnLgFind(pp[2], uLgId);
        if (pLg != 0) {
            int32_t nPrize =
                (int32_t)g_fn78F4F0(pLg);
            if (nPrize > 0) {
                // RAW: lea rcx,[rcx+rcx*4]; add rcx,rcx
                //   (x*10); movabs 0xa3d70a3d70a3d70b;
                //   imul; lea rbx,[rcx+rdx]; sar rbx,6;
                //   mov rax,rbx; shr rax,0x3f; add rbx,rax
                int64_t lTen =
                    (int64_t)(int32_t)nPrize;
                lTen = lTen + lTen * 4;
                lTen = lTen + lTen;      // *10
                int64_t lHi = (int64_t)(
                    ((__int128)lTen *
                     (__int128)(int64_t)
                     0xa3d70a3d70a3d70bLL)
                    >> 64);
                int64_t lSum = lTen + lHi;
                lSum >>= 6;              // sar
                lSum += (int64_t)(
                    (uint64_t)lSum >> 63);
                int32_t nX = (int32_t)lSum;
                if (nX > 0) {
                    g_fn79BF80(pLg,
                        -(int64_t)nX);
                    g_fn79BF80(pWarRec,
                        (int64_t)nX);
                }
            }
        }
    }
    // RAW: vt+0x308(box, u2, f270(rec)&0xffffffff)
    ((void (*)(void*, uint32_t, uint32_t))
        (*(void***)pp[1])[0x308 / 8])(
            pp[1], u2,
            (uint32_t)g_fn78F270(pWarRec));
    // the STR_GOT_WIN_s notify
    char acBuf[0x400];
    acBuf[0] = 0;
    memset(acBuf + 1, 0, 0x3ff);
    void* pInst = g_fnStringMgrInstance();
    const void* pvName = g_fn78F470(pWarRec);
    const char* pcFmt = (const char*)
        g_fnStringMgrGetStr(pInst,
            "STR_GOT_WIN_s");
    snprintf(acBuf, 0x400, pcFmt, pvName);
    acBuf[0x3ff] = 0;
    ((void (*)(void*, void*))
        (*(void***)pp[1])[0x78 / 8])(pp[1], acBuf);
    uint32_t uWarId = ((uint32_t (*)(void*,
        uint32_t))(*(void***)pp[1])[0x300 / 8])(
            pp[1], u2);
    uint32_t uF318 = ((uint32_t (*)(void*,
        uint32_t))(*(void***)pp[1])[0x318 / 8])(
            pp[1], u2);
    // RAW: vt+0x310(box, uWarId) — the return discarded
    (void)((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x310 / 8])(pp[1], uWarId);
    if (uWarId == 0x40e) {
        uint8_t abMsg[0x430];
        g_fn7DB2B0(abMsg);
        if (g_fn7DB3A0(abMsg, 0x11,
                       (int32_t)uF318) != 0) {
            ((void (*)(void*, void*))
                (*(void***)pp[1])[0xe0 / 8])(
                    pp[1], abMsg);
        } else {
            g_fnSynLogCheck(STAR_FMT, "IF_OK",
                "msg.Create(SET_WHITE_SYN, "
                "idMapOwnerID)",
                s_pszLogicSrc, 0x664);
        }
        g_fn7DB330(abMsg);
        return 1;
    }
    if (uWarId == 0x3e8) {
        uint8_t abMsg[0x430];
        g_fn7DB2B0(abMsg);
        if (g_fn7DB3A0(abMsg, 0x12,
                       (int32_t)uF318) != 0) {
            ((void (*)(void*, void*))
                (*(void***)pp[1])[0xe0 / 8])(
                    pp[1], abMsg);
        } else {
            g_fnSynLogCheck(STAR_FMT, "IF_OK",
                "msg.Create(SET_BLACK_SYN, "
                "idMapOwnerID)",
                s_pszLogicSrc, 0x66c);
        }
        g_fn7DB330(abMsg);
    }
    return 1;
}


// ============================================================
// D113 — wave 18 (TRUE offsets +0x378..+0x470), 17 bodies,
// raw-verified against Syndicate.dll (imagebase 0x141720000).
// ============================================================

// ---- the D113 seams (default null — tests bind them) ----
uint32_t (*g_fn1417a8940)(void*, uint32_t);
void*    (*g_fn14173f9c0)();
void     (*g_fn14173fa40)(void*, uint32_t);
void     (*g_fn14173dbc0)(void*, uint32_t, uint32_t,
                          uint32_t);
void     (*g_fn14173f4d0)(void*);
void*    (*g_fn141781b60)();
void     (*g_fn141783470)(void*, uint32_t);
void*    (*g_fn141741a30)();
void     (*g_fn141742810)(void*, void*);
void     (*g_fn141740fd0)(void*, uint32_t);
void     (*g_fn141741b10)(void*);
void     (*g_fn1417434f0)(void*);
void     (*g_fn14177b4b0)(void*, int32_t, int64_t,
                          int64_t);
void     (*g_fn14177cdc0)(void*, int64_t, int64_t,
                          uint32_t, uint32_t);
void     (*g_fn141784cd0)(void*, uint32_t, uint32_t);
uint64_t (*g_fn14177f980)(void*, uint32_t, uint32_t);
void     (*g_fn1417d4670)(void*, uint32_t, uint32_t,
                          const void*, uint32_t, int16_t,
                          int16_t, int16_t, int16_t,
                          int16_t, int16_t);
void     (*g_fn1417d3100)(void*, uint32_t, uint32_t);
void     (*g_fn1417d3680)(void*, uint32_t, uint32_t);
char     (*g_fn14179c8b0)(void*, uint32_t, int64_t,
                          int64_t);
char     (*g_fn1417d3530)(void*, uint32_t, uint32_t);
char     (*g_fn14178e600)(void*);
void     (*g_fn1417638e0)(void*, uint32_t, uint32_t);
char     (*g_fn1417b8470)(void*, void*, uint32_t,
                          int32_t, int32_t, int32_t);
void*    (*g_fn1417873a0)(int32_t);
void*    (*g_fn14178f4e0)(void*);
void     (*g_fn14179ad50)(void*, uint32_t);

// ============ +0x378..+0x3b8: the singleton forwards ============
// RAW af310: +0x20 gate -> the a8940 TAIL; miss = xor eax
uint32_t CSyndicateLogic::Slot378(uint32_t u2) {
    void* pBox = *(void**)((char*)this + 0x20);
    if (pBox == 0)
        return 0;
    return g_fn1417a8940(pBox, u2);
}
// RAW af330: 3f9c0() singleton -> the fa40(inst, u2) TAIL
void CSyndicateLogic::Slot380(uint32_t u2) {
    void* pInst = g_fn14173f9c0();
    g_fn14173fa40(pInst, u2);
}
// RAW af350: 3f9c0() -> 3dbc0(inst, u2, u3, u4)
void CSyndicateLogic::Slot388(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void* pInst = g_fn14173f9c0();
    g_fn14173dbc0(pInst, u2, u3, u4);
}
// RAW af390: 3f9c0() -> the 3f4d0(inst) TAIL
void CSyndicateLogic::Slot390(void) {
    g_fn14173f4d0(g_fn14173f9c0());
}
// RAW af3b0: 81b60() -> the 83470(inst, u2) TAIL
void CSyndicateLogic::Slot398(uint32_t u2) {
    void* pInst = g_fn141781b60();
    g_fn141783470(pInst, u2);
}
// RAW af3d0: the DOUBLE-jle quirk (test edx,edx; jle TWICE —
// verbatim), then the do-while over the p3 array (stride 0x48)
void CSyndicateLogic::Slot3a0(int32_t n2, void* p3) {
    if (0 < n2 && 0 < n2) {
        void* p = p3;
        for (int i = 0; i < n2; ++i) {
            g_fn141742810(g_fn141741a30(), p);
            p = (char*)p + 0x48;
        }
    }
}
// RAW af410: 1a30() -> the 40fd0(inst, u2) TAIL
void CSyndicateLogic::Slot3a8(uint32_t u2) {
    void* pInst = g_fn141741a30();
    g_fn141740fd0(pInst, u2);
}
// RAW af430: 77b4b0(this+0x30, 3, p3, p4) — the incoming
// edx(p2) is OVERWRITTEN by the literal 3; then
// 1a30() -> the 41b10(inst) TAIL
void CSyndicateLogic::Slot3b0(int32_t n2, int64_t l3,
                              int64_t l4) {
    (void)n2;   // RAW: discarded, edx := 3
    g_fn14177b4b0(
        *(void**)((char*)this + 0x30), 3, l3, l4);
    g_fn141741b10(g_fn141741a30());
}
// RAW af460: the +0x60 byte gate -> 1a30()/434f0(inst)
void CSyndicateLogic::Slot3b8(void) {
    if (*(char*)((char*)this + 0x60) != 0)
        g_fn1417434f0(g_fn141741a30());
}

// ============ +0x3c8..+0x3f0: the gated forwards ============
// RAW afa70: +0x38 gate; the callee args are REORDERED:
// cdc0(x, p4, p5, p2, p3) — rax=r9(p4), r8=[rsp+0x60](p5),
// r9d=edx(p2), [rsp+0x20]=r8d(p3)
void CSyndicateLogic::Slot3c8(uint32_t u2, uint32_t u3,
                              int64_t l4, int64_t l5) {
    void* pX = *(void**)((char*)this + 0x38);
    if (pX != 0)
        g_fn14177cdc0(pX, l4, l5, u2, u3);
}
// RAW afaa0: +0x28 -> 784cd0(x, u2, u3) ride
void CSyndicateLogic::Slot3d0(uint32_t u2, uint32_t u3) {
    void* pX = *(void**)((char*)this + 0x28);
    if (pX != 0)
        g_fn141784cd0(pX, u2, u3);
}
// RAW afac0: +0x28 -> the 77f980 TAIL; miss = xor eax
uint64_t CSyndicateLogic::Slot3d8(uint32_t u2,
                                  uint32_t u3) {
    void* pX = *(void**)((char*)this + 0x28);
    if (pX == 0)
        return 0;
    return g_fn14177f980(pX, u2, u3);
}
// RAW afae0: +0x30 -> 77b4b0(x, u2, u3, u4) ride
void CSyndicateLogic::Slot3e0(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void* pX = *(void**)((char*)this + 0x30);
    if (pX != 0)
        g_fn14177b4b0(pX, (int32_t)u2, (int64_t)u3,
                      (int64_t)u4);
}
// RAW afba0: +0x48 gate; miss -> the IF_NOT/
// m_pSynRecruitAdvertisingMgr log, line 0x1501; hit ->
// 7d4670(x, p2..p11) — the RAW re-spills p5(dword) and
// p6..p11(words) to the callee stack
void CSyndicateLogic::Slot3e8(uint32_t u2, uint32_t u3,
    const char* pc4, uint32_t u5, int16_t n6,
    int16_t n7, int16_t n8, int16_t n9, int16_t n10,
    int16_t n11) {
    void* pX = *(void**)((char*)this + 0x48);
    if (pX == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "m_pSynRecruitAdvertisingMgr",
            s_pszLogicSrc, 0x1501);
        return;
    }
    g_fn1417d4670(pX, u2, u3, pc4, u5, n6, n7, n8,
                  n9, n10, n11);
}
// RAW afc40: +0x48 gate; miss -> the 0x150b log; hit ->
// the 7d3100(x, u2, u3) TAIL
void CSyndicateLogic::Slot3f0(uint32_t u2, uint32_t u3) {
    void* pX = *(void**)((char*)this + 0x48);
    if (pX == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "m_pSynRecruitAdvertisingMgr",
            s_pszLogicSrc, 0x150b);
        return;
    }
    g_fn1417d3100(pX, u2, u3);
}

// ================= +0x3f8: 1417b8620 =================
// the join/invite flow (the giant, 790 bytes):
//   the three head gates (+0x48 -> 0x1516, +0x10 ->
//   0x151a, p3==0 -> 0x151e, all IF_NOT logs);
//   vt+0x1f8(box) != 0 -> out; cad00(mgr,p3) -> syn;
//   9c8b0(syn,p2,p3,p4 ride) -> d3530(this+0x48,p2,p3);
//   8e590 -> STR_TOO_LOWER_SYN_MONEY via vt+0x18; else
//   8e600 -> STR_SYN_FULL; else vt+0x510(this,p2) ->
//   90390(syn) compare: equal -> 638e0(this+0x50, id, p2),
//   else b19c0(this, p2, 1, p4-ride); ALWAYS 8470(this,
//   syn, p2, 200, 0, 0) -> vt+0x370(box, p2); the
//   STR_SYN_INVITE_JOIN notify: snprintf(buf, 0x400, fmt,
//   873a0(1000), f4e0, f470, vt1d8name) — FOUR varargs;
//   vt+0x88(box, f270ret, buf, 0, u16 0x7d4); 9ad50(syn,
//   p2)
void CSyndicateLogic::Slot3f8(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    if (pp[9] == 0) {          // RAW: this+0x48
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "m_pSynRecruitAdvertisingMgr",
            s_pszLogicSrc, 0x1516);
        return;
    }
    if (pp[2] == 0) {          // RAW: this+0x10
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "m_pSynMgr", s_pszLogicSrc, 0x151a);
        return;
    }
    if (u3 == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "idSyn", s_pszLogicSrc, 0x151e);
        return;
    }
    // RAW: mov rcx,[rcx+8]; call [rax+0x1f8] — single arg
    uint32_t uBox = ((uint32_t (*)(void*))
        (*(void***)pp[1])[0x1f8 / 8])(pp[1]);
    if (uBox != 0)
        return;
    void* pSyn = (void*)g_fnLgFind(pp[2], u3);
    if (pSyn == 0)
        return;
    // RAW: rcx=syn, edx=p2; r8/r9 ride stale (p3/p4)
    if (g_fn14179c8b0(pSyn, u2, (int64_t)u3,
                      (int64_t)u4) == 0)
        return;
    if (g_fn1417d3530(pp[9], u2, u3) == 0)
        return;
    if (g_fn78E590(pSyn) != 0) {
        // RAW: GetStr -> vt+0x18(box, p2, str)
        void* pInst = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pInst,
            "STR_TOO_LOWER_SYN_MONEY");
        ((void (*)(void*, uint32_t, const void*))
         (*(void***)pp[1])[0x18 / 8])(pp[1], u2, pv);
        return;
    }
    if (g_fn14178e600(pSyn) != 0) {
        void* pInst = g_fnStringMgrInstance();
        const void* pv = g_fnStringMgrGetStr(pInst,
            "STR_SYN_FULL");
        ((void (*)(void*, uint32_t, const void*))
         (*(void***)pp[1])[0x18 / 8])(pp[1], u2, pv);
        return;
    }
    // RAW: vt+0x510(this, p2)
    uint32_t uVt510 =
        ((uint32_t (*)(void*, uint32_t))
         (*(void***)this)[0x510 / 8])(this, u2);
    if (uVt510 != 0) {
        if (uVt510 == g_fn141790390(pSyn)) {
            // RAW: 638e0(this+0x50, vt510ret, p2)
            g_fn1417638e0(pp[10], uVt510, u2);
        } else {
            // RAW: r8b=1; r9 (p4) rides stale
            g_fn1417b19c0(this, u2, 1, (void*)(uintptr_t)u4);
        }
    }
    // RAW: 8470(this, syn, p2, 200, 0, 0)
    if (g_fn1417b8470(this, pSyn, u2, 200, 0, 0)
        != 0) {
        ((void (*)(void*, uint32_t))
         (*(void***)pp[1])[0x370 / 8])(pp[1], u2);
        // the STR_SYN_INVITE_JOIN notify (4 varargs)
        char acBuf[0x400];
        acBuf[0] = 0;
        memset(acBuf + 1, 0, 0x3ff);
        void* pInst = g_fnStringMgrInstance();
        // RAW: box vt+0x1d8(box, p2) -> the inviter name
        void* pvInviter =
            ((void* (*)(void*, uint32_t))
             (*(void***)pp[1])[0x1d8 / 8])(pp[1], u2);
        void* pvName1 = g_fn78F470(pSyn);
        void* pvName2 = g_fn14178f4e0(pSyn);
        void* pvRate = g_fn1417873a0(1000);
        const char* pcFmt = (const char*)
            g_fnStringMgrGetStr(pInst,
                "STR_SYN_INVITE_JOIN");
        snprintf(acBuf, 0x400, pcFmt, pvRate, pvName2,
                 pvName1, pvInviter);
        acBuf[0x3ff] = 0;
        // RAW: vt+0x88(box, f270ret&0xffffffff, buf, 0,
        // u16 0x7d4 on the stack)
        ((void (*)(void*, uint32_t, void*, uint64_t,
                   uint16_t))
         (*(void***)pp[1])[0x88 / 8])(
             pp[1],
             (uint32_t)g_fn78F270(pSyn),
             acBuf, 0, 0x7d4);
        g_fn14179ad50(pSyn, u2);
    }
}

// ================= +0x400: 1417afc90 =================
// the recruit-ad reply: p2==0 -> the IF_NOT/idUser log
// (0x1562); this+0x48==0 -> 0x1566; vt+0x78(this) [1
// arg]; vt+0x1f8(box, p2) -> 7d3680(this+0x48, p2, id)
void CSyndicateLogic::Slot400(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "idUser", s_pszLogicSrc, 0x1562);
        return;
    }
    if (pp[9] == 0) {          // RAW: this+0x48
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "m_pSynRecruitAdvertisingMgr",
            s_pszLogicSrc, 0x1566);
        return;
    }
    // RAW: mov rax,[rcx]; call [rax+0x78] — rcx = this
    char cOk = ((char (*)(void*))
        (*(void***)this)[0x78 / 8])(this);
    if (cOk == 0)
        return;
    uint32_t uId = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x1f8 / 8])(pp[1], u2);
    if (uId != 0)
        g_fn1417d3680(pp[9], u2, uId);
}


// ============================================================
// D114a — wave 19 (TRUE offsets +0x560..+0x678, the small
// half), 26 bodies, raw-verified against Syndicate.dll
// (imagebase 0x141720000).
// ============================================================

// ---- the D114a seams (default null — tests bind them) ----
bool     (*g_fn1417d9cc0)(void*, uint32_t, uint32_t,
    uint32_t, uint32_t, const char*, const char*);
void     (*g_fn14175efe0)(void*, uint32_t, uint32_t);
void     (*g_fn141798a20)(void*, uint32_t, uint64_t);
void     (*g_fn14174eee0)(void*, uint32_t, void*,
                          uint64_t);
void     (*g_fn14175f4a0)(void*, uint32_t, uint32_t);
void     (*g_fn141764b80)(void*, uint32_t, uint32_t);
void     (*g_fn141764f10)(void*, uint32_t, uint32_t);
void     (*g_fn14175fa60)(void*, uint32_t);
void     (*g_fn1417652c0)(void*, uint32_t);
void     (*g_fn1417684b0)(void*, uint16_t);
void     (*g_fn1417685f0)(void*, uint16_t);
void     (*g_fn14174ebb0)(void*);
void     (*g_fn1417715f0)(void*, uint32_t, int32_t,
                          void***);
void     (*g_fn141774c20)(void*);
void     (*g_fn141766330)(void*, uint16_t, uint32_t*);
void     (*g_fn14176ff50)(void*, uint16_t, uint32_t*);
void*    (*g_fn1417630d0)(void*, uint32_t);
void     (*g_fn14174dda0)(void*, void*);
void     (*g_fn1417bf610)(void*, void*, int64_t, void*);
void     (*g_fn1417d9410)(void*);
uint8_t  (*g_fn1417d94c0)(void*, uint32_t, int64_t,
                          uint32_t);
uint8_t  (*g_fn1417d9550)(void*, void*);
void     (*g_fn1417d9690)(void*);
void     (*g_fn1417d9460)(void*);
void     (*g_fn14174ef80)(void*, void*);
void     (*g_fn1417bf7c0)(void*, void*, int64_t, void*);
void     (*g_fn1417d7800)(void*);
uint8_t  (*g_fn1417d78b0)(void*, uint8_t);
void     (*g_fn1417d7850)(void*);
uint8_t  (*g_fn1417d7910)(void*, void*);
void     (*g_fn1417d7a40)(void*);
void     (*g_fn14174ef60)(void*, void*);
void     (*g_fn14174efa0)(void*, void*);
void     (*g_fn1417d5e50)(void*);
uint8_t  (*g_fn1417d5f00)(void*, uint8_t);
uint8_t  (*g_fn1417d5f60)(void*, void*);
void     (*g_fn1417d60a0)(void*);
void     (*g_fn1417d5ea0)(void*);
void*    (*g_fn141777a30)(void*, uint32_t, uint32_t);
uint32_t (*g_fn1418232c8)(uint32_t);
void*    (*g_fn141764870)(void*, uint32_t);
void*    (*g_fn14174bac0)(void*, uint32_t);
uint32_t (*g_fn141745520)(void*);
uint32_t (*g_fn141743e70)(void*);
char     (*g_fn14174f000)(void*, uint32_t, uint32_t);
int32_t  (*g_fn14174e950)(void*);
void     (*g_fn141823090)(const char*, uint32_t,
                          const char*, uint32_t);
void     (*g_fn1418230a8)(const char*, const char*, uint32_t,
                          void*, uint32_t, uint32_t, uint32_t,
                          uint32_t, uint32_t);
void     (*g_fn1417d4f30)(void*, uint32_t, uint32_t, uint8_t);
void     (*g_fn1417d7350)(void*);
uint32_t (*g_fn1417d4ed0)(void*, uint32_t);
char     (*g_fn1417d7650)(void*, uint32_t, uint8_t,
                          uint32_t);
void     (*g_fn1417d73a0)(void*);
char     (*g_fn1417632e0)(void*, uint32_t, void*, uint32_t);
void     (*g_fn141790440)(void*, void*);
void     (*g_fn1417d8c20)(void*);
char     (*g_fn1417d8cd0)(void*, int32_t);
char     (*g_fn1417d8d40)(void*, void*);
void     (*g_fn1417d8e50)(void*);
void     (*g_fn1417d8c70)(void*);
void     (*g_fn14174d5a0)(void*, void*);
uint32_t (*g_fn1417d4e70)(void*);
uint32_t (*g_fn141823048)(uint32_t);
char     (*g_fn1417d73e0)(void*);
char     (*g_fn1417d7440)(void*);
char     (*g_fn1417d7770)(void*, uint32_t, uint8_t, void*);
void*    (*g_fn14174bbe0)(void*, uint32_t);
int64_t  (*g_fn1417440d0)(void*);
void     (*g_fn141744130)(void*, int64_t, uint8_t);
char     (*g_fn1417b2570)(void*, uint32_t, void*, void*,
                          void*, void*);
void     (*g_fn141823280)(void*);
void     (*g_fn141823290)(void*);
void     (*g_fn1417be5f0)(void*, uint32_t, uint32_t, uint32_t,
                         void*);
void     (*g_fn141732040)(void*, void*);
void     (*g_fn1417d9000)(void*);
char     (*g_fn1417d9140)(void*, uint32_t, uint32_t, uint32_t,
                         const char*, uint32_t);
void     (*g_fn1417d9050)(void*);
void     (*g_fn141777de0)(void*, uint32_t, uint32_t, void*);
void     (*g_fn14176b0d0)(void*, uint32_t);
void     (*g_fn141774c70)(void*, uint32_t);
void     (*g_fn141775350)(void*, uint32_t);
void     (*g_fn14174ebc0)(void*, uint32_t);
char     (*g_fn141765410)(void*, uint32_t, uint32_t);
void     (*g_fn141765800)(void*, uint32_t);
void     (*g_fn141765920)(void*, uint32_t);
void     (*g_fn141765d60)(void*, uint32_t);
char     (*g_fn1417655c0)(void*, uint32_t, uint32_t);
char     (*g_fn141765540)(void*, uint32_t);
void     (*g_fn141771f90)(void*, uint32_t, uint32_t,
                          uint32_t);
char     (*g_fn14174f120)(void*);
void     (*g_fn14175f830)(void*, uint32_t, uint32_t);
char     (*g_fn141763a90)(void*, uint32_t, uint32_t);
char     (*g_fn141763bc0)(void*, uint32_t, uint32_t,
                          uint32_t);
void     (*g_fn141766500)(void*, uint32_t);
void     (*g_fn141766e90)(void*, uint32_t, uint32_t,
                          uint32_t, uint32_t);
void     (*g_fn141769100)(void*, uint32_t);
uint64_t (*g_fn141764990)(void*, uint32_t, uint32_t);
char     (*g_fn141774500)(void*, uint32_t, uint64_t);
void*    (*g_fn14178c8e0)(void*, uint32_t);
void     (*g_fn141787d70)(void*, uint64_t);
int32_t  (*g_fn141787de0)(void*);
void     (*g_fn141767890)(void*, uint32_t, uint64_t,
                          uint32_t);
void     (*g_fn14174b360)(void*, uint32_t, int32_t,
                          uint64_t);
char     (*g_fn14174be40)(void*, uint32_t);

// ===== the OVERHEAD broadcast trio (msg.Create family) =====
// RAW ffa0: p2==0 out; p5==0 out [RAW: [rsp+0x538] =
// arg6 psz]; vt+0x278(box) -> 0 = SILENT out; the four
// box setters vt+0x158(u2,u3)/+0x168(u2,b4)/+0x170(u2,
// b5)/+0x178(u2,psz6); msg ctor d9900; d9b30(buf, **0**,
// u2, u3, b4, b5, psz6, u7); miss -> the IF_OK log
// 0x15f9; hit -> vt+0x58(box, u2, buf, r9b=1); d9950
void CSyndicateLogic::Slot560(uint32_t u2, uint32_t u3,
    uint8_t b4, uint8_t b5, const char* psz6,
    uint32_t u7) {
    void** pp = (void**)this;
    if (u2 == 0 || psz6 == 0)
        return;
    void** ppVt = *(void***)pp[1];    // box vtable
    void* pBox = pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pBox);
    if (cOk == 0)
        return;                     // RAW: silent out
    ((void (*)(void*, uint32_t, uint32_t))
     ppVt[0x158 / 8])(pBox, u2, u3);
    ((void (*)(void*, uint32_t, uint8_t))
     ppVt[0x168 / 8])(pBox, u2, b4);
    ((void (*)(void*, uint32_t, uint8_t))
     ppVt[0x170 / 8])(pBox, u2, b5);
    ((void (*)(void*, uint32_t, const void*))
     ppVt[0x178 / 8])(pBox, u2, psz6);
    char acMsg[0x440];
    g_fn1417d9900(acMsg);
    if (!g_fn1417d9b30(acMsg, 0, u2, u3, b4, b5,
                       psz6, u7)) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msg.Create(OVERHEAD_USER, idUser, "
            "idLeague, bIsLeagueLeader, "
            "bIsCountryLeagueMember, pszLeagueName, "
            "idServer)",
            s_pszLogicSrc, 0x15f9);
    } else {
        ((void (*)(void*, uint32_t, void*, uint8_t))
         ppVt[0x58 / 8])(pBox, u2, acMsg, 1);
    }
    g_fn1417d9950(acMsg);
}

// RAW 0100: p2==0 out; p6 psz==0 out; msg ctor; spill
// [0x38]=u7(dword), [0x30]=psz6, [0x28]=b5(byte),
// [0x20]=b4(byte); d9b30(buf, **1**, u2, u3, b4, b5,
// psz6, u7); miss -> 0x1607; hit -> vt+0x98(box, buf)
void CSyndicateLogic::Slot568(uint32_t u2, uint32_t u3,
    uint8_t b4, uint8_t b5, const char* psz6,
    uint32_t u7) {
    void** pp = (void**)this;
    if (u2 == 0 || psz6 == 0)
        return;
    char acMsg[0x440];
    g_fn1417d9900(acMsg);
    if (!g_fn1417d9b30(acMsg, 1, u2, u3, b4, b5,
                       psz6, u7)) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msg.Create(OVERHEAD_SYNDICATE, idSyn, "
            "idLeague, bIsLeagueLeader, "
            "bIsCountryLeagueMember, pszLeagueName, "
            "idServer)",
            s_pszLogicSrc, 0x1607);
    } else {
        void** ppBox = *(void***)pp[1];
        ((void (*)(void*, void*))(
            ppBox[0x98 / 8]))(pp[1], acMsg);
    }
    g_fn1417d9950(acMsg);
}

// RAW 0200: p5 psz==0 out; p6 psz==0 out; d9cc0(buf,
// **2**, u2, u3, u4, psz5, psz6); miss -> 0x1615; hit ->
// vt+0x98(box, buf)
void CSyndicateLogic::Slot570(uint32_t u2, uint32_t u3,
    uint32_t u4, const char* psz5, const char* psz6) {
    void** pp = (void**)this;
    if (psz5 == 0 || psz6 == 0)
        return;
    char acMsg[0x440];
    g_fn1417d9900(acMsg);
    if (!g_fn1417d9cc0(acMsg, 2, u2, u3, u4,
                       psz5, psz6)) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msg.Create(OVERHEAD_ON_COUNTRY_CHANGED, "
            "idOldCountryLeague, idNewCountryLeague, "
            "idServer, pszStepDownLeague, "
            "pszOnStageLeague)",
            s_pszLogicSrc, 0x1615);
    } else {
        void** ppBox = *(void***)pp[1];
        ((void (*)(void*, void*))(
            ppBox[0x98 / 8]))(pp[1], acMsg);
    }
    g_fn1417d9950(acMsg);
}

// ===== the talk-channel family (vt+0x278 gate ->
// vt+0x538(box, N, u2, 0, u3) with the literal channel
// numbers; else the this+0x50 forward) =====
// RAW 0810: u2==0 out; vt+0x278(box) -> vt+0x538(box,
// **5**, u2, 0, u3); else 75efe0(this+0x50, u2, u3)
void CSyndicateLogic::Slot5b8(uint32_t u2, uint32_t u3) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0) {
        ((void (*)(void*, int, uint32_t, int, uint32_t))
         ppVt[0x538 / 8])(pp[1], 5, u2, 0, u3);
        return;
    }
    g_fn14175efe0(pp[10], u2, u3);
}

// RAW 0890: u2==0 or u3==0 out; vt+0x278 -> vt+0x538(
// box, **3**, u2, u3, n4); else cad00(mgr,u3) syn ->
// 798a20(syn, u2, n4)
void CSyndicateLogic::Slot5c8(int32_t n2, uint32_t u3,
                              int32_t n4) {
    void** pp = (void**)this;
    if (n2 == 0 || u3 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk == 0) {
        void* pSyn = (void*)g_fnLgFind(pp[2], u3);
        if (pSyn != 0)
            g_fn141798a20(pSyn, (uint32_t)n2,
                          (uint64_t)(uint32_t)n4);
    } else {
        ((void (*)(void*, int, uint32_t, uint32_t, int))
         ppVt[0x538 / 8])(pp[1], 3, (uint32_t)n2, u3,
                           n4);
    }
}

// RAW 1e00: vt+0x278 -> vt+0x538(box, **6**, u2, 0,
// u3); else 75f4a0(this+0x50, u2, u3)
void CSyndicateLogic::Slot5d8(int32_t n2, uint32_t u3) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0) {
        ((void (*)(void*, int, uint32_t, int, uint32_t))
         ppVt[0x538 / 8])(pp[1], 6, (uint32_t)n2, 0,
                           u3);
        return;
    }
    g_fn14175f4a0(pp[10], (uint32_t)n2, u3);
}

// RAW 1450: u2==0 out; vt+0x278 -> vt+0x538(box, **9**,
// u2, 0, 0); else 74eee0(this+0x50, u2, p3, l4)
void CSyndicateLogic::Slot5f8(uint32_t u2, void* p3,
                              uint64_t l4) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0) {
        ((void (*)(void*, int, uint32_t, int, int))
         ppVt[0x538 / 8])(pp[1], 9, u2, 0, 0);
        return;
    }
    g_fn14174eee0(pp[10], u2, p3, l4);
}

// ===== 27b0/28c0: the member-in-my-syn arbitration =====
// RAW 27b0: u2==0 or u3==0 -> 0; vt+0x278 -> vt+0x550(
// box, u2, u3) return 1; else vt+0x510(this,u2) != 0 &&
// vt+0x440(this) != 0 && equal && (b0370(this,id)==u2
// || vt+0x530(this,u2)) -> 774500(this+0x50, u2, u3)
bool CSyndicateLogic::Slot588(uint32_t u2, uint32_t u3) {
    void** pp = (void**)this;
    void** ppVtSelf = *(void***)this;
    if (u2 == 0 || u3 == 0)
        return 0;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0) {
        ((void (*)(void*, uint32_t, uint32_t))
         ppVt[0x550 / 8])(pp[1], u2, u3);
        return 1;
    }
    uint32_t uVt510 = ((uint32_t (*)(void*, uint32_t))
        ppVtSelf[0x510 / 8])(this, u2);
    if (uVt510 != 0) {
        uint32_t uVt440 = ((uint32_t (*)(void*))
            ppVtSelf[0x440 / 8])(this);
        if (uVt440 != 0 && uVt510 == uVt440) {
            if (g_fn1417b0370(this, uVt510) == (int)u2)
                return g_fn141774500(pp[10], u2, u3);
            char c530 = ((char (*)(void*, uint32_t))
                ppVtSelf[0x530 / 8])(this, u2);
            if (c530 != 0)
                return g_fn141774500(pp[10], u2, u3);
        }
    }
    return 0;
}

// RAW 28c0: u2==0 or u3==0 -> 0; vt+0x280(box) -> 0
// = out (RAW: in_RAX & 0xff..ff00 quirk); vt+0x510(this,
// u2) != 0 && vt+0x440(this) equal && (b0370==u2 ||
// vt+0x530) -> 764990(this+0x50, u2, u3)
uint64_t CSyndicateLogic::Slot648(int32_t n2,
                                  uint32_t u3) {
    void** pp = (void**)this;
    void** ppVtSelf = *(void***)this;
    if (n2 == 0 || u3 == 0)
        return 0;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x280 / 8]))(pp[1]);
    if (cOk == 0)
        return 0;
    uint32_t uVt510 = ((uint32_t (*)(void*, uint32_t))
        ppVtSelf[0x510 / 8])(this, (uint32_t)n2);
    if (uVt510 != 0) {
        uint32_t uVt440 = ((uint32_t (*)(void*))
            ppVtSelf[0x440 / 8])(this);
        if (uVt440 != 0 && uVt510 == uVt440) {
            if (g_fn1417b0370(this, uVt510) == n2)
                return g_fn141764990(pp[10],
                                      (uint32_t)n2, u3);
            char c530 = ((char (*)(void*, uint32_t))
                ppVtSelf[0x530 / 8])(this, (uint32_t)n2);
            if (c530 != 0)
                return g_fn141764990(pp[10],
                                      (uint32_t)n2, u3);
        }
    }
    return 0;
}

// the d6640 seam (declared in syndicatelogic.h)
void     (*g_fn1417d6640)(void*);

// ===== 1380/29a0/31c0/5760/5830/5880 + the getters =====
// RAW 1380 (beats the decompile's (cOk<<8) CONCAT
// artifact): vt+0x278 != 0 -> xor al,al ret 0; vt+0x4a8(
// box, u2) id == 0 -> 0; 74e3f0(this+0x50) != id -> 0;
// 630d0(this+0x50, id) syn == 0 -> 0; 78c8e0(this+0x18,
// u2): miss -> 74be40(syn, u2): al==1 -> 1 else 0; hit
// -> 787de0(lVar): al==1 -> 1 else 0
bool CSyndicateLogic::Slot600(uint32_t u2) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0)
        return false;
    uint32_t uId = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    if (uId == 0)
        return 0;
    if ((uint32_t)g_fn14174e3f0(pp[10]) != uId)
        return 0;
    void* pSyn = g_fn1417630d0(pp[10], uId);
    if (pSyn == 0)
        return 0;
    void* pRec = g_fn14178c8e0(pp[3], u2);
    if (pRec == 0) {
        char cBe = g_fn14174be40(pSyn, u2);
        if (cBe != 1)
            return 0;
        return 1;
    }
    if (g_fn141787de0(pRec) != 1)
        return 0;
    return 1;
}

// RAW 29a0: u3==0 out; 78c8e0(this+0x18, u2) hit ->
// 787d70(rec, l4); miss -> 630d0(this+0x50, u3) syn ->
// 74b360(syn, u2, **4**, l4); ALWAYS 767890(this+0x50,
// u2, l4, u3)
void CSyndicateLogic::Slot640(uint32_t u2, uint32_t u3,
                              int32_t n4) {
    void** pp = (void**)this;
    if (u3 == 0)
        return;
    void* pRec = g_fn14178c8e0(pp[3], u2);
    if (pRec != 0) {
        g_fn141787d70(pRec,
                      (uint64_t)(uint32_t)n4);
    } else {
        void* pSyn = g_fn1417630d0(pp[10], u3);
        if (pSyn == 0)
            return;                  // RAW: je -> out
        g_fn14174b360(pSyn, u2, 4,
                      (uint64_t)(uint32_t)n4);
    }
    g_fn141767890(pp[10], u2,
                  (uint64_t)(uint32_t)n4, u3);
}

// RAW 31c0: the 0x34-family msg — d6640(buf); d6820(buf,
// 0x34, psz4, u2, u3, 0); hit -> vt+0x98(box, buf);
// d66c0(buf)
void CSyndicateLogic::Slot618(uint32_t u2, uint32_t u3,
                              const char* psz4) {
    void** pp = (void**)this;
    char acMsg[0x438];       // RAW: 1072-byte local
    g_fn1417d6640(acMsg);
    if (g_fn1417d6820(acMsg, 0x34, psz4, u2, u3, 0)) {
        void** ppVt = *(void***)pp[1];
        ((void (*)(void*, void*))(
            ppVt[0x98 / 8]))(pp[1], acMsg);
    }
    g_fn1417d66c0(acMsg);
}

// RAW 5760: vt+0x278 -> vt+0x578(box, u2) == 0 -> the
// IF_OK log line 0x26d3 ("m_pConsumer->OSUserLogout(
// idUser)" — the decompile showed a bare
// InlineLogERROR; RAW wins); else vt+0x4e8(box, u2,
// u3, u4, u5, u6)
void CSyndicateLogic::Slot650(uint32_t u2, uint32_t u3,
    uint32_t u4, uint16_t u5, uint16_t u6) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    char cOk = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOk != 0) {
        char c578 = ((char (*)(void*, uint32_t))
            ppVt[0x578 / 8])(pp[1], u2);
        if (c578 == 0)
            g_fnSynLogCheck(STAR_FMT, "IF_OK",
                "m_pConsumer->OSUserLogout(idUser)",
                s_pszLogicSrc, 0x26d3);
        else
            ((void (*)(void*, uint32_t, uint32_t,
                       uint32_t, uint16_t, uint16_t))
             ppVt[0x4e8 / 8])(pp[1], u2, u3, u4, u5,
                               u6);
    }
}

// RAW 5830: 630d0(this+0x50, u2) syn; 7440d0(syn) +
// n3 < 0x2e90edd001 (the DATE magic)
bool CSyndicateLogic::Slot5a0(uint32_t u2, int32_t n3) {
    void** pp = (void**)this;
    void* pSyn = g_fn1417630d0(pp[10], u2);
    if (pSyn == 0)
        return false;
    int64_t lTime = g_fn1417440d0(pSyn);
    return (uint64_t)(lTime + n3) < 0x2e90edd001ull;
}

// ===== Slot610 = 1417c1a90 (RAW) =====
// The publish-token flow (the largest in D114b).
// RAW (6 params): u2/u3/u4/u5==0 -> 0; vt+0x288
// (box) map miss -> the STR_DIE vt+0x18 notify ->
// 0; vt+0x278(box, u2) online: vt+0x4c8(box, u2)
// miss -> STR_MAP_CANNOT_PUBLISH_TOKEN -> 0; hit
// -> vt+0x450(box, **u3, u2**, u4, u5, u6, u7) ->
// 1. OFFLINE: vt+0x280(box, u2) or vt+0x4c8 hit ->
// main, else the notify -> 0. MAIN: vt+0x4a8(box,
// u2) lid (0 -> 0); 630d0 miss -> the **0x201a**
// "pSynLeague" log -> 0; 74bac0(lg, u3) member,
// fallback 74bbe0, both miss -> the **0x2025**
// "pToken" log -> 0; d4ed0(mem, **2**) type ->
// 64870(host, type) objB null -> the 4-arg
// 141823090 log (**0x202d**) -> 0; the string obj
// (141823280 ctor) + b2570(this, u2, lg, mem, objB,
// &str) miss -> 141823290 dtor -> 0; objB-vt[2](
// objB, 4) sub -> vt+0x58 = cost; 440d0(lg) <
// cost -> STR_NOT_ENOUGH_LEAGUE_MONEY_... ->
// dtor -> 0; else the delta (0 or 440d0-cost) ->
// 44130(lg, delta, 1); 4f30(mem, **3**, f3+1, 0);
// 4f30(mem, **4**, 23048(1), 1); the /1000-style
// cap adjust (cap = objB-vt[2](objB, **3**)->
// vt+0x50; f4 = d4ed0(mem,4); adj = cap+now2 >
// now ? cap-now2+f4 : 0); d7350 ctor + d7650(
// msg, d4e70(mem), (uint8_t)f3, adj) hit -> vt+0x8;
// then the Slot5b0-twin block: memset 0x146 +
// 45580(lg, rec); vt+0x568(box, u2, lid) ->
// 66b60(host, id, &out1@0x40, 0x10, buf1) +
// 66d10(host, id, &out2@0x48, 0x10, buf2); the
// /1000 magic BOTH outs; b5370(this, u2, lg) flag;
// d6110 + d61c0(msg, rec, flag, out1/1000,
// out2/1000, buf1, buf2) miss -> the **0x2060**
// IF_OK log, hit -> vt+0x8; the vec1 fill via
// be5f0(this, u2, lid, type, &vec1); the loop:
// id 0 or == u2 skip; vt+0x268/0x4d8 gates;
// (vt+0x280 OR vt+0x4d0) hit -> 141732040(vec2,
// id); d9000 msg ctor + vt+0x4b0(box) + d4ed0(
// mem, 2) type -> d9140(msg, **1**, u2, type,
// str.data(), 4b0) miss -> the **0x2087** IF_OK
// log, hit -> vt+0x40(box, msg, vec2); the pack:
// {u4, u5, u6, u7, 4b0+232c8(0)} -> 777de0(
// this+0x58, u2, type, &pack); d9050 dtor; free
// vecs; d6160 + d73a0 + 141823290; return 1.
bool CSyndicateLogic::Slot610(uint32_t u2,
                              uint32_t u3,
                              uint32_t u4,
                              uint32_t u5,
                              uint32_t u6,
                              uint32_t u7) {
    void** pp = (void**)this;
    if (u2 == 0 || u3 == 0 || u4 == 0 ||
        u5 == 0)
        return 0;
    void** ppVt = *(void***)pp[1];
    if (((char (*)(void*))ppVt[0x288 / 8])
            (pp[1]) == 0) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(pInst, "STR_DIE");
        ((void (*)(void*, uint32_t, uint64_t))
         ppVt[0x18 / 8])(pp[1], u2, uStr);
        return 0;
    }
    if (((char (*)(void*, uint32_t))ppVt[0x278/8])
            (pp[1], u2) != 0) {
        if (((char (*)(void*, uint32_t))
                 ppVt[0x4c8 / 8])(pp[1], u2) == 0) {
            void* pInst = g_fnStringMgrInstance();
            uint64_t uStr = (uint64_t)
                g_fnStringMgrGetStr(
                    pInst,
                    "STR_MAP_CANNOT_PUBLISH_"
                    "TOKEN");
            ((void (*)(void*, uint32_t, uint64_t))
             ppVt[0x18 / 8])(pp[1], u2, uStr);
            return 0;
        }
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x450 / 8])(pp[1], u3, u2, u4,
                          u5, u6, u7);
        return 1;
    }
    char cMain = ((char (*)(void*, uint32_t))
                     ppVt[0x280 / 8])(pp[1], u2);
    if (cMain == 0)
        cMain = ((char (*)(void*, uint32_t))
                     ppVt[0x4c8 / 8])(pp[1],
                                       u2);
    if (cMain == 0) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst,
                "STR_MAP_CANNOT_PUBLISH_"
                "TOKEN");
        ((void (*)(void*, uint32_t, uint64_t))
         ppVt[0x18 / 8])(pp[1], u2, uStr);
        return 0;
    }
    uint32_t uLid = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    if (uLid == 0)
        return 0;
    void* pLg = g_fn1417630d0(pp[10], uLid);
    if (pLg == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "pSynLeague", s_pszLogicSrc, 0x201a);
        return 0;
    }
    void* pMem = g_fn14174bac0(pLg, u3);
    if (pMem == 0)
        pMem = g_fn14174bbe0(pLg, u3);
    if (pMem == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "pToken", s_pszLogicSrc, 0x2025);
        return 0;
    }
    uint32_t uType = g_fn1417d4ed0(pMem, 2);
    void* pObjB = g_fn141764870(pp[10], uType);
    if (pObjB == 0) {
        g_fn141823090(
            "table:cq_token_type, can not find "
            "token_id[%lu] at %s, %d.", uType,
            s_pszLogicSrc, 0x202d);
        return 0;
    }
    char acStr[0x40];
    g_fn141823280(acStr);
    if (g_fn1417b2570(this, u2, pLg, pMem, pObjB,
                      acStr) == 0) {
        g_fn141823290(acStr);
        return 0;
    }
    void* pSub4 = ((void* (*)(void*, int32_t))
        (*(void***)pObjB)[0x10 / 8])(pObjB, 4);
    int64_t nCost = ((int64_t (*)(void*))
        (*(void***)pSub4)[0x58 / 8])(pSub4);
    if (g_fn1417440d0(pLg) < nCost) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst,
                "STR_NOT_ENOUGH_LEAGUE_MONEY_"
                "TO_PUBLISH_TOKEN");
        ((void (*)(void*, uint32_t, uint64_t))
         ppVt[0x18 / 8])(pp[1], u2, uStr);
        g_fn141823290(acStr);
        return 0;
    }
    int64_t nDelta = g_fn1417440d0(pLg) - nCost;
    if (g_fn1417440d0(pLg) < nCost)
        nDelta = 0;
    g_fn141744130(pLg, nDelta, 1);
    uint32_t uF3 = g_fn1417d4ed0(pMem, 3);
    g_fn1417d4f30(pMem, 3, uF3 + 1, 0);
    uint32_t uNow = g_fn141823048(1);
    g_fn1417d4f30(pMem, 4, uNow, 1);
    uint32_t uF4 = g_fn1417d4ed0(pMem, 4);
    uint32_t uNow2 = g_fn141823048(1);
    void* pSub3 = ((void* (*)(void*, int32_t))
        (*(void***)pObjB)[0x10 / 8])(pObjB, 3);
    uint32_t uCap = ((uint32_t (*)(void*))
        (*(void***)pSub3)[0x50 / 8])(pSub3);
    uint32_t uAdj = 0;
    if (uCap + uF4 > uNow2)
        uAdj = uCap - uNow2 + uF4;
    uint8_t acMsgA[0x200];
    g_fn1417d7350(acMsgA);
    uint32_t uId = g_fn1417d4e70(pMem);
    uint32_t uF3b = g_fn1417d4ed0(pMem, 3);
    if (g_fn1417d7650(acMsgA, uId, (uint8_t)uF3b,
                      uAdj) != 0) {
        ((void (*)(void*, uint32_t, void*))
         ppVt[0x8 / 8])(pp[1], u2, acMsgA);
    }
    uint8_t acRec[0x146];
    memset(acRec, 0, 0x146);
    g_fn141745580(pLg, acRec);
    uint32_t uOut1 = 0;       // [rsp+0x40]
    uint32_t uOut2 = 0;       // [rsp+0x48]
    uint8_t abBuf1[0x11];     // 0xf70
    uint8_t abBuf2[0x11];     // 0xf60
    memset(abBuf1, 0, 0x11);
    memset(abBuf2, 0, 0x11);
    uint32_t uMsgId = ((uint32_t (*)(void*,
        uint32_t, uint32_t))
        ppVt[0x568 / 8])(pp[1], u2, uLid);
    g_fn141766b60(pp[10], uMsgId, &uOut1, abBuf1,
                  0x10);
    g_fn141766d10(pp[10], uMsgId, &uOut2, abBuf2,
                  0x10);
    uint8_t acMsgB[0x470];
    g_fn1417d6110(acMsgB);
    uint32_t uFlag = g_fn1417b5370(this, u2, pLg);
    // the /1000 magic (0x431bde83 >> 0x12)
    if (!g_fn1417d61c0(acMsgB, acRec, uFlag,
                       uOut1 / 1000, uOut2 / 1000,
                       (const char*)abBuf1,
                       (const char*)abBuf2)) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msgLeagueInfo.Create(stLeagueInfo, "
            "this->GetLeagueAwardFlag(idUser ,"
            "pSynLeague), ID_SERVER_LEAGUE_SERVER("
            "idPlunder), ID_SERVER_LEAGUE_SERVER("
            "idPlundered), szPlunder, szPlundered)",
            s_pszLogicSrc, 0x2060);
    } else {
        ((void (*)(void*, uint32_t, void*))
         ppVt[0x8 / 8])(pp[1], u2, acMsgB);
    }
    static std::vector<uint32_t> s_vec1;
    s_vec1.clear();
    g_fn1417be5f0(this, u2, uLid, uType,
                  (void*)&s_vec1);
    static std::vector<uint32_t> s_vec2;
    s_vec2.clear();
    for (uint32_t uId2 : s_vec1) {
        if (uId2 == 0 || uId2 == u2)
            continue;
        if (((char (*)(void*, uint32_t))
                 ppVt[0x268 / 8])(pp[1], uId2)
                == 0)
            continue;
        if (((char (*)(void*, uint32_t))
                 ppVt[0x4d8 / 8])(pp[1], uId2)
                == 0)
            continue;
        char cAdd = ((char (*)(void*, uint32_t))
            ppVt[0x280 / 8])(pp[1], uId2);
        if (cAdd == 0)
            cAdd = ((char (*)(void*, uint32_t))
                ppVt[0x4d0 / 8])(pp[1], uId2);
        if (cAdd != 0)
            g_fn141732040((void*)&s_vec2, &uId2);
    }
    uint8_t acMsgC[0x200];
    g_fn1417d9000(acMsgC);
    uint32_t u4b0 = ((uint32_t (*)(void*))
        ppVt[0x4b0 / 8])(pp[1]);
    uint32_t uType2 = g_fn1417d4ed0(pMem, 2);
    if (g_fn1417d9140(acMsgC, 1, u2, uType2,
                      (const char*)acStr,
                      u4b0) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msgLeagueToken.Create(CMsgLeagueToken::"
            "LEAGUE_TOKEN_CALLUP, idUser, pToken->"
            "GetInt(LEAGUE_TOKEN_DATA_TOKEN_TYPE), "
            "strPublishName, iArg1)",
            s_pszLogicSrc, 0x2087);
    } else {
        ((void (*)(void*, void*, void*))
         ppVt[0x40 / 8])(pp[1], acMsgC,
                         (void*)&s_vec2);
    }
    uint32_t auPack[5];
    auPack[0] = u4;
    auPack[1] = u5;
    auPack[2] = u6;
    auPack[3] = u7;
    auPack[4] = u4b0 + g_fn1418232c8(0);
    g_fn141777de0(pp[11], u2, uType2, auPack);
    g_fn1417d9050(acMsgC);
    g_fn1417d6160(acMsgB);
    g_fn1417d73a0(acMsgA);
    g_fn141823290(acStr);
    return 1;
}

// ===== D114c: the class tail (+0x680..+0x738) =====
// RAW thunks: mov rcx,[rcx+0x50]; jmp <target>
void CSyndicateLogic::Slot688(uint32_t u2) {
    g_fn14176b0d0(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot690(uint32_t u2) {
    g_fn141774c70(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot698(uint32_t u2) {
    g_fn141775350(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot6a0(uint32_t u2) {
    // 74ebc0: mov dword [rcx+0x35c],0 ; ret
    g_fn14174ebc0(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot6b8(uint32_t u2) {
    g_fn141765800(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot6c0(uint32_t u2) {
    g_fn141765920(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot6c8(uint32_t u2) {
    g_fn141765d60(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot6e8(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    g_fn141771f90(
        *(void**)((char*)this + 0x50), u2, u3, u4);
}
char CSyndicateLogic::Slot6f0(void) {
    // 74f120: mov al,[rcx+0x2c]; ret
    return g_fn14174f120(
        *(void**)((char*)this + 0x50));
}
void CSyndicateLogic::Slot6f8(uint32_t u2,
                              uint32_t u3) {
    g_fn14175f830(
        *(void**)((char*)this + 0x50), u2, u3);
}
void CSyndicateLogic::Slot720(uint32_t u2) {
    g_fn141766500(
        *(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot730(uint32_t u2, uint32_t u3,
                              uint32_t u4,
                              uint32_t u5) {
    // RAW 5710: sub 0x38; arg5 forwarded via
    // [rsp+0x20] to 766e90 (host, u2..u5)
    g_fn141766e90(
        *(void**)((char*)this + 0x50),
        u2, u3, u4, u5);
}
void CSyndicateLogic::Slot738(uint32_t u2) {
    g_fn141769100(
        *(void**)((char*)this + 0x50), u2);
}

// RAW 5430: box8-vt+0x4a8(box, u3) -> esi (0 ->
// skip, returns al=0); vt+0x3e8(box, u3) -> eax;
// sum = esi + eax*0xf4240; tail 765410(host, u2,
// sum)
char CSyndicateLogic::Slot6a8(uint32_t u2,
                              uint32_t u3) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    uint32_t uR = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u3);
    if (uR == 0)
        return 0;
    uint32_t uF = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x3e8 / 8])(pp[1], u3);
    return g_fn141765410(pp[10], u2,
        uR + uF * 0xf4240);
}

// RAW 54a0: u2==0 -> false; this-vt+0x440(this) ->
// ebx; box8-vt+0x3f0(box) (edx leftover) -> eax;
// sum = ebx + eax*0xf4240; tail 765410(host, u2,
// sum)
char CSyndicateLogic::Slot6b0(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return 0;
    uint32_t u440 = ((uint32_t (*)(void*))
        (*(void***)this)[0x440 / 8])(this);
    void** ppVt = *(void***)pp[1];
    // RAW: vt+0x3f0(box) arg-less (edx leftover)
    uint32_t uF = ((uint32_t (*)(void*))
        ppVt[0x3f0 / 8])(pp[1]);
    return g_fn141765410(pp[10], u2,
        u440 + uF * 0xf4240);
}

// RAW 5510: u2==0 -> false; box8-vt+0x278(box)
// (edx=u2 leftover in RAW) true -> false;
// vt+0x280(box, u2) true -> false; vt+0x4a8(box,
// u2) -> esi; 0 -> false; this-vt+0x440(this) ->
// edi; 0 -> false; esi != edi -> false; vt+0x3f0(
// box) -> eax; tail 765540(host, edi + eax*0xf4240)
char CSyndicateLogic::Slot6d8(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return 0;
    void** ppVt = *(void***)pp[1];
    // RAW: vt+0x278(box) arg-less (edx leftover)
    if (((char (*)(void*))
            ppVt[0x278 / 8])(pp[1]) != 0)
        return 0;
    if (((char (*)(void*, uint32_t))
            ppVt[0x280 / 8])(pp[1], u2) != 0)
        return 0;
    uint32_t uEsi = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    if (uEsi == 0)
        return 0;
    uint32_t uEdi = ((uint32_t (*)(void*))
        (*(void***)this)[0x440 / 8])(this);
    if (uEdi == 0)
        return 0;
    if (uEsi != uEdi)
        return 0;
    // RAW: vt+0x3f0(box) arg-less (edx leftover)
    uint32_t uF = ((uint32_t (*)(void*))
        ppVt[0x3f0 / 8])(pp[1]);
    return g_fn141765540(pp[10],
        uEdi + uF * 0xf4240);
}

// RAW 55d0: box8-vt+0x4a8(box, u2) -> esi; 0 ->
// false; vt+0x3e8(box, u2) -> edi = esi +
// edi*0xf4240; vt+0x4a8(box, u3) -> esi; 0 ->
// false; vt+0x3e8(box, u3) -> eax; 7655c0(host,
// sum1, esi + eax*0xf4240) (r9 leftover in RAW)
char CSyndicateLogic::Slot6d0(uint32_t u2,
                              uint32_t u3) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    uint32_t uEsi = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    if (uEsi == 0)
        return 0;
    uint32_t uA = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x3e8 / 8])(pp[1], u2);
    uint32_t uSum1 = uEsi + uA * 0xf4240;
    uint32_t uEsi2 = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u3);
    if (uEsi2 == 0)
        return 0;
    uint32_t uB = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x3e8 / 8])(pp[1], u3);
    return g_fn1417655c0(pp[10], uSum1,
        uEsi2 + uB * 0xf4240);
}

// RAW 1ae0: u2==0 -> false; this-vt+0x510(this) ->
// eax; 0 -> false; tail 763a90(host, u2, eax)
char CSyndicateLogic::Slot710(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return 0;
    uint32_t uR = ((uint32_t (*)(void*))
        (*(void***)this)[0x510 / 8])(this);
    if (uR == 0)
        return 0;
    return g_fn141763a90(pp[10], u2, uR);
}

// RAW 1b30: u2==0 or u3==0 -> false; this-vt+0x510(
// this) -> eax; 0 -> false; tail 763bc0(host, u2,
// eax, u3)
char CSyndicateLogic::Slot718(uint32_t u2,
                              uint32_t u3) {
    void** pp = (void**)this;
    if (u2 == 0 || u3 == 0)
        return 0;
    uint32_t uR = ((uint32_t (*)(void*))
        (*(void***)this)[0x510 / 8])(this);
    if (uR == 0)
        return 0;
    return g_fn141763bc0(pp[10], u2, uR, u3);
}

// ===== Slot700 = 1417c16f0 (RAW) =====
// league-dismiss flow: pSyn = 7630d0(host,u4);
// u3 != 743c80(pSyn) required; pLeague2 =
// 7cad00(this+0x10, 743c80(pSyn)); 790390(pLeague2)
// == u4 required; 7903d0(pLeague2,0) required;
// 74d490(pSyn,u3); then two vsnprintf-format rounds
// (STR_LEAGUE_DEL_SYN via 78f470(pLeague2), and
// STR_SYN_DEL_BY_LEAGUE via 743e60(pSyn)) -> box
// vt+0x10(box,u2,0x7d5,buf) and box vt+0x88(box,u3,
// buf,0,0x7d5); this-vt+0x710(this,pLeague2,0,5);
// c1180(this,u3,u4); 76aca0(host,78f2d0(pLeague2));
// 9e6d0(pLeague2,&cont) int-vector; per id: vt+0x268
// && !vt+0x280 && vt+0x2a0==9 -> vt+0x2a8(box,id,3)
struct RawCont114c {
    void* pPad0;      // +0x00
    void* pPad1;      // +0x08
    void* pPad2;      // +0x10
    void* pFirst;     // +0x18
    void* pLast;      // +0x20
    void* pEnd;       // +0x28
    void* pProxy;     // +0x30
};
void CSyndicateLogic::Slot700(uint32_t u2, uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    void* pHost = *(void**)((char*)this + 0x50);
    void* pSyn = g_fn1417630d0(pHost, u4);
    if (pSyn == 0)
        return;
    if (u3 == g_fn141743c80(pSyn))
        return;
    void* pLeague2 = (void*)
        ((void* (*)(void*, uint32_t))
         g_fnA84FindSyn)(pp[2], g_fn141743c80(pSyn));
    if (pLeague2 == 0)
        return;
    if (g_fn141790390(pLeague2) != (int32_t)u4)
        return;
    if (!g_fn1417903d0(pLeague2, 0))
        return;
    g_fn14174d490(pSyn, u3);

    // ---- format round 1: STR_LEAGUE_DEL_SYN ----
    char acBuf[0x400];
    acBuf[0] = 0;
    g_fn1417f30c0(acBuf + 1, 0, 0x3ff);
    void* pProv = g_fn141823050();
    int32_t nName = g_fn14178f470(pLeague2);
    const char* pszFmt1 = ((const char* (*)(void*, const char*))
        (*(void***)pProv)[0])(pProv,
            "STR_LEAGUE_DEL_SYN");
    g_fn1418233c8(acBuf, 0x400, pszFmt1, (void*)(intptr_t)nName);
    acBuf[0x3ff] = 0;
    ((void (*)(void*, uint32_t, uint32_t, void*))
     (*(void***)pp[1])[0x10 / 8])(pp[1], u2, 0x7d5, acBuf);

    // ---- format round 2: STR_SYN_DEL_BY_LEAGUE ----
    g_fn1417f30c0(acBuf, 0, 0x400);
    pProv = g_fn141823050();
    int32_t nSyn = g_fn141743e60(pSyn);
    const char* pszFmt2 = ((const char* (*)(void*, const char*))
        (*(void***)pProv)[0])(pProv,
            "STR_SYN_DEL_BY_LEAGUE");
    g_fn1418233c8(acBuf, 0x400, pszFmt2, (void*)(intptr_t)nSyn);
    acBuf[0x3ff] = 0;
    ((void (*)(void*, uint32_t, void*, uint32_t, uint32_t))
     (*(void***)pp[1])[0x88 / 8])(pp[1], u3, acBuf, 0, 0x7d5);

    // this-vt+0x710 dispatch (RAW: rdx=pLeague2,
    // r8=0, r9=5; slot consumes only u2)
    ((char (*)(void*, uint32_t))
     (*(void***)this)[0x710 / 8])(this,
        (uint32_t)(uintptr_t)pLeague2);
    g_fn1417c1180(this, u3, u4);
    g_fn14176aca0(pHost, g_fn14178f2d0(pLeague2));

    // ---- member-id iteration (9e6d0 fills) ----
    RawCont114c sCont;
    void* pSent = g_fn1417f3166(8);
    if (pSent != 0)
        *(void**)pSent = &sCont;
    sCont.pPad0 = pSent;
    sCont.pFirst = sCont.pLast = sCont.pEnd = 0;
    if (g_fn14179e6d0(pLeague2, &sCont)) {
        void** ppBox = *(void***)pp[1];
        int32_t* p = (int32_t*)sCont.pFirst;
        int32_t* pEnd = (int32_t*)sCont.pLast;
        for (; p != pEnd; ++p) {
            uint32_t id = (uint32_t)*p;
            if (((char (*)(void*, uint32_t))
                    ppBox[0x268 / 8])(pp[1], id) == 0)
                continue;
            if (((char (*)(void*, uint32_t))
                    ppBox[0x280 / 8])(pp[1], id) != 0)
                continue;
            if (((uint32_t (*)(void*, uint32_t))
                    ppBox[0x2a0 / 8])(pp[1], id) != 9)
                continue;
            ((void (*)(void*, uint32_t, uint32_t))
             ppBox[0x2a8 / 8])(pp[1], id, 3);
        }
    }
    if (sCont.pFirst != 0)
        g_fn1417f2fdc(sCont.pFirst);
    sCont.pFirst = sCont.pLast = sCont.pEnd = 0;
    g_fn1417f2fdc(sCont.pPad0);
}

// ===== Slot708 = 1417c16f0's twin: 1417c0110 (RAW) =====
// msgOpt.Create(usAction, idNewLeague, country) flow:
// cont init (f3166(8) sentinel); bf960(pLeague,&cont);
// msg ctor; r9d = 74e3f0(host); d6790(&msg,u4,u3,r9d,
// 0) -> if !al: CHECK-log 0x1c67 "msgOpt.Create(
// usAction, idNewLeague, m_pLeagueMgr->
// GetCountryLeague())"; else loop over cont elems
// {elem!=0, 787300(elem) -> vt+0x158(box,
// 785dc0(elem), u3); found=1}; vt+0x38(box,
// 78f270(pLeague), &msg, 0); if found vt+0x110(box,
// 78f270(pLeague), u3, 8); b1090(this, 78f270(
// pLeague)); vt+0x70(box, 8, 790390(pLeague),
// 78f270(pLeague), ""); dtor; cleanup
void CSyndicateLogic::Slot708(void* pLeague,
                              uint32_t u3,
                              uint16_t u4) {
    void** pp = (void**)this;
    void* pHost = *(void**)((char*)this + 0x50);

    // ---- container init (literal raw pattern) ----
    RawCont114c sCont;
    void* pSent = g_fn1417f3166(8);
    if (pSent != 0)
        *(void**)pSent = &sCont;
    sCont.pPad0 = pSent;
    sCont.pFirst = sCont.pLast = sCont.pEnd = 0;
    g_fn1417bf960(pLeague, &sCont);

    // ---- msg + create ----
    char acMsg[0x470];
    g_fn1417d6640(acMsg);
    uint32_t uCountry = (uint32_t)g_fn14174e3f0(pHost);
    if (!g_fn1417d6790(acMsg, (uint32_t)u4, u3,
                      uCountry, 0)) {
        g_fnSynLogCheck(STAR_FMT, "CHECK",
            "msgOpt.Create(usAction, idNewLeague, "
            "m_pLeagueMgr->GetCountryLeague())",
            s_pszLogicSrc, 0x1c67);
    } else {
        void** ppBox = *(void***)pp[1];
        char cFound = 0;
        void** p = (void**)sCont.pFirst;
        void** pEnd = (void**)sCont.pLast;
        for (; p != pEnd; ++p) {
            void* pElem = *p;
            if (pElem == 0)
                continue;
            if (!g_fn141787300(pElem))
                continue;
            ((void (*)(void*, uint32_t, uint32_t))
             ppBox[0x158 / 8])(pp[1],
                g_fn141785dc0(pElem), u3);
            cFound = 1;
        }
        ((void (*)(void*, uint32_t, void*, uint32_t))
         ppBox[0x38 / 8])(pp[1],
            g_fn14178f270(pLeague), acMsg, 0);
        if (cFound) {
            ((void (*)(void*, uint32_t, uint32_t,
                       uint32_t))
             ppBox[0x110 / 8])(pp[1],
                g_fn14178f270(pLeague), u3, 8);
        }
        g_fn1417b1090(this, g_fn14178f270(pLeague));
        ((void (*)(void*, uint32_t, uint32_t, uint32_t,
                   const char*))
         ppBox[0x70 / 8])(pp[1], 8,
            (uint32_t)g_fn141790390(pLeague),
            g_fn14178f270(pLeague), "");
    }
    g_fn1417d66c0(acMsg);
    if (sCont.pFirst != 0)
        g_fn1417f2fdc(sCont.pFirst);
    sCont.pFirst = sCont.pLast = sCont.pEnd = 0;
    g_fn1417f2fdc(sCont.pPad0);
}

// ===== Slot578 = 1417bdb20 (RAW) =====
// The token/member-list broadcaster. RAW: online ->
// vt+0x460(box, u2) + out; THIS-vt+0x510(this, u2)
// -> league id; 630d0(host, id) league (null -> out);
// the PTR-stride-8 vector filled by 74d5a0(lg,
// &vec); d7350 msg ctor + d73e0(msg) header (miss ->
// dtor + out); the loop (stride **8**, elements are
// member PTRs): null element -> the **0x1e57**
// IF_NOT "pToken" log -> next; d4e70(member) ->
// 64870(host, id) objA (null -> the 141823090
// "table:cq_token_type, token[%lu] is not exist"
// log -> next); ebx = d4ed0(member, **4**); r13 =
// 141823048(**1**); objA-vt[2](objA, **3**) subA ->
// subA-vt[0x50/8=10](subA) = cap; edx = 0; if (ebx
// != 0 && cap + ebx > r13) edx = cap - r13 + ebx;
// r12 = edx; ebx = d4ed0(member, **3**); eax =
// d4e70(member); d7770(msg, eax, (uint8_t)ebx, r12)
// != 0 -> next (added); == 0 -> the flush: d7440(
// msg) hit -> vt+0x8(box, u2, msg); d73e0(msg)
// re-header (miss -> dtor + out); the retry d7770;
// loop end -> d7440 hit -> vt+0x8 + d73a0 dtor.
void CSyndicateLogic::Slot578(uint32_t u2) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    if (((char (*)(void*))ppVt[0x278 / 8])
            (pp[1]) != 0) {
        ((void (*)(void*, uint32_t))
         ppVt[0x460 / 8])(pp[1], u2);
        return;
    }
    uint32_t uLid = ((uint32_t (*)(void*, uint32_t))
        (*(void***)this)[0x510 / 8])(this, u2);
    void* pLg = g_fn1417630d0(pp[10], uLid);
    if (pLg == 0)
        return;
    static std::vector<void*> s_vec578;
    s_vec578.clear();
    g_fn14174d5a0(pLg, (void*)&s_vec578);
    uint8_t acMsg[0x200];
    g_fn1417d7350(acMsg);
    if (g_fn1417d73e0(acMsg) == 0) {
        g_fn1417d73a0(acMsg);
        return;
    }
    for (void* pMember : s_vec578) {
        if (pMember == 0) {
            g_fnSynLogCheck(STAR_FMT, "IF_NOT",
                "pToken", s_pszLogicSrc, 0x1e57);
            continue;
        }
        uint32_t uTokId = g_fn1417d4e70(pMember);
        void* pObjA = g_fn141764870(pp[10],
                                    uTokId);
        if (pObjA == 0) {
            // RAW: only (fmt, uTokId) set
            g_fn141823090(
                "table:cq_token_type, token[%lu] "
                "is not exist", uTokId, 0, 0);
            continue;
        }
        uint32_t uF4 = g_fn1417d4ed0(pMember, 4);
        uint32_t uNow = g_fn141823048(1);
        void* pSubA = ((void* (*)(void*, int32_t))
            (*(void***)pObjA)[0x10 / 8])(pObjA, 3);
        uint32_t uCap = ((uint32_t (*)(void*))
            (*(void***)pSubA)[0x50 / 8])(pSubA);
        uint32_t uAdj = 0;
        if (uF4 != 0) {
            uint32_t uSum = uCap + uF4;
            if (uSum > uNow)
                uAdj = uCap - uNow + uF4;
        }
        uint32_t uF3 = g_fn1417d4ed0(pMember, 3);
        uint32_t uId2 = g_fn1417d4e70(pMember);
        if (g_fn1417d7770(acMsg, uId2,
                          (uint8_t)uF3,
                          (void*)(size_t)uAdj) != 0)
            continue;
        if (g_fn1417d7440(acMsg) != 0) {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(
                pp[1], u2, acMsg);
        }
        if (g_fn1417d73e0(acMsg) == 0) {
            g_fn1417d73a0(acMsg);
            return;
        }
        g_fn1417d7770(acMsg, uId2, (uint8_t)uF3,
                      (void*)(size_t)uAdj);
    }
    if (g_fn1417d7440(acMsg) != 0) {
        ((void (*)(void*, uint32_t, void*))
         (*(void***)pp[1])[0x8 / 8])(
            pp[1], u2, acMsg);
    }
    g_fn1417d73a0(acMsg);
}

// ===== Slot5c0 = 1417bd730 (RAW) =====
// The member-list pager. RAW: u2==0 or u3==0 out;
// vt+0x278(box) online -> vt+0x538(box, **2**, u2,
// u3, u4); else nPage = u4 * **0xF** (15 per page);
// the dword vector filled by 632e0(this+0x50, u3,
// &vec, 0) (miss -> free + out); count = size();
// nPage >= count or nPage < 0 -> out; d8c20 msg
// ctor + d8cd0(msg, count) miss -> the **0x17a4**
// IF_NOT log ("msgList.Create((int)vecMember."
// "size())") -> dtor + out; the loop from
// &vec[nPage], max **15** iterations: LgFind(
// this+0x10, id) user (null -> SKIP, no count, no
// send); the 0x30 info block zeroed + 90440(user,
// block) fill; d8d40(msg, block) MISS -> vt+0x8(
// box, u2, msg) + d8e50 clear + d8d40 RETRY; then
// the tail vt+0x8 + d8c70 dtor.
void CSyndicateLogic::Slot5c0(uint32_t u2,
                              uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    if (u2 == 0 || u3 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        ((void (*)(void*, uint8_t, uint32_t,
                   uint32_t, uint32_t))
         ppVt[0x538 / 8])(pp[1], 2, u2, u3, u4);
        return;
    }
    int32_t nPage = (int32_t)u4 * 0xF;
    static std::vector<uint32_t> s_vec5c0;
    s_vec5c0.clear();
    if (g_fn1417632e0(pp[10], u3,
                      (void*)&s_vec5c0, 0) == 0)
        return;
    int32_t nCnt = (int32_t)s_vec5c0.size();
    if (nPage >= nCnt || nPage < 0)
        return;
    uint8_t acMsg[0x200];
    g_fn1417d8c20(acMsg);
    if (g_fn1417d8cd0(acMsg, nCnt) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "msgList.Create((int)vecMember.size())",
            s_pszLogicSrc, 0x17a4);
        g_fn1417d8c70(acMsg);
        return;
    }
    int n = 0;
    for (size_t i = (size_t)nPage;
         i < s_vec5c0.size(); ++i) {
        if (n >= 0xF)
            break;
        void* pUser = (void*)g_fnLgFind(
            pp[2], s_vec5c0[i]);
        if (pUser == 0)
            continue;      // RAW: skip, NO count
        uint8_t abInfo[0x30];
        memset(abInfo, 0, 0x30);
        g_fn141790440(pUser, abInfo);
        if (g_fn1417d8d40(acMsg, abInfo) == 0) {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(
                pp[1], u2, acMsg);
            g_fn1417d8e50(acMsg);
            g_fn1417d8d40(acMsg, abInfo);
        }
        ++n;
    }
    ((void (*)(void*, uint32_t, void*))
     (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                 acMsg);
    g_fn1417d8c70(acMsg);
}

// ===== Slot580 = 1417b2e30 (RAW) =====
// The clean-CD/emoney-buy flow. RAW: online ->
// vt+0x468(box, u2, u3) + return 1; 64870(host, u3)
// objA (null -> 0); objA-vt[2](objA, **8**) subA,
// subA-vt[9](subA)==0 -> 0; vt+0x4a8(box, u2) league
// id (0 -> 0); 630d0(host, id) league (null -> 0);
// 74bac0(lg, u3) member (null -> 0); THIS-vt+0x440
// vs 45520(lg): equal -> main; else objA-vt[2]
// (objA, **0**) + subA-vt[9], the **signed /100**
// (magic 0x51eb851f sar 5) == 1 AND 43e70(lg) == u2
// -> main; else the position loop i=5..7: objA-vt[2]
// (objA, i) subA, subA-vt[9] != 0 -> 74f000(host,
// u2, n) hit -> main; i>7 -> 0. MAIN: 74e950(host)
// count <= 0 -> 141823090("cq_config: type=%u ,"
// "clean token cd money is not config", **0x249fa**)
// -> 0; vt+0x238(box,u2): count > it -> the
// STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH notify via
// vt+0x28(box, u2, str, **0xffff00**) -> 0; the
// switch u3: **0x66** -> (0x47, 0x10dc), **0xCC** ->
// (0x48, 0x10dd), else 141823090("cq_token_type: "
// "token %u can not clean cd", u3) -> 0; vt+0x140
// (box, u2, 0, count, uPos, 1) miss -> the same
// notify -> 0; vt+0x200 -> u200 + vt+0x1d8(box,u2)
// -> p1d8; the 1418230a8 gmlog ("gmlog/emoney_buy",
// "%lu\t%s\t%lu\t%lu\t%lu\t%u\t%u\t1\t", u2,
// p1d8, u200, **0x15e**, uR14, count, count);
// 4f30(member, 4, 0, 1); vt+0x280(box,u2) hit ->
// vt+0x470(box, u2, u4); d7350 msg ctor;
// 4ed0(member, 3) -> d7650(msg, (uint8_t)u3, n,
// 0) hit -> vt+0x8(box, u2, msg); d73a0 dtor;
// return 1.
bool CSyndicateLogic::Slot580(uint32_t u2,
                              uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    void** ppVt = *(void***)pp[1];
    if (((char (*)(void*, uint32_t))ppVt[0x278 / 8])
            (pp[1], u2) != 0) {
        ((void (*)(void*, uint32_t, uint32_t))
         ppVt[0x468 / 8])(pp[1], u2, u3);
        return 1;
    }
    void* pObjA = g_fn141764870(pp[10], u3);
    if (pObjA == 0)
        return 0;
    void* pSubA = ((void* (*)(void*, int32_t))
        (*(void***)pObjA)[0x10 / 8])(pObjA, 8);
    if (((int32_t (*)(void*))(*(void***)pSubA)
         [0x48 / 8])(pSubA) == 0)
        return 0;
    uint32_t uLid = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    if (uLid == 0)
        return 0;
    void* pLg = g_fn1417630d0(pp[10], uLid);
    if (pLg == 0)
        return 0;
    void* pMem = g_fn14174bac0(pLg, u3);
    if (pMem == 0)
        return 0;
    uint32_t u440 = ((uint32_t (*)(void*))
        (*(void***)this)[0x440 / 8])(this);
    bool bMain = false;
    if (g_fn141745520(pLg) == u440) {
        bMain = true;
    } else {
        void* pSubB = ((void* (*)(void*, int32_t))
            (*(void***)pObjA)[0x10 / 8])(pObjA, 0);
        int32_t n9 = ((int32_t (*)(void*))
            (*(void***)pSubB)[0x48 / 8])(pSubB);
        // RAW: the signed /100 magic 0x51eb851f
        if (n9 / 100 == 1) {
            if (g_fn141743e70(pLg) == u2)
                bMain = true;
        }
        if (!bMain) {
            for (uint32_t i = 5;; ++i) {
                void* pSubC =
                    ((void* (*)(void*, int32_t))
                     (*(void***)pObjA)[0x10 / 8])(
                        pObjA, (int32_t)i);
                int32_t n9c = ((int32_t (*)(void*))
                    (*(void***)pSubC)[0x48 / 8])(
                        pSubC);
                if (n9c != 0) {
                    if (g_fn14174f000(pp[10], u2,
                            (uint32_t)n9c) != 0) {
                        bMain = true;
                        break;
                    }
                }
                if (i + 1 > 7)      // inc; cmp 7
                    return 0;
            }
        }
    }
    (void)bMain;
    int32_t nCnt = g_fn14174e950(pp[10]);
    if (nCnt <= 0) {
        // RAW passes only (fmt, line); r8/r9 left
        // as register leftovers
        g_fn141823090(
            "cq_config: type=%u ,clean token cd "
            "money is not config", 0x249fa, 0, 0);
        return 0;
    }
    uint32_t u238 = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x238 / 8])(pp[1], u2);
    if (nCnt > (int32_t)u238) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst,
                "STR_TRAINING_GONGFU_EMONEY_"
                "NOT_ENOUGH");
        ((void (*)(void*, uint32_t, uint64_t,
                   uint32_t))
         (*(void***)pp[1])[0x28 / 8])(
            pp[1], u2, uStr, 0xffff00);
        return 0;
    }
    uint32_t uPos, uR14;
    if (u3 == 0x66) {
        uPos = 0x47;
        uR14 = 0x10dc;
    } else if (u3 == 0xCC) {
        uPos = 0x48;
        uR14 = 0x10dd;
    } else {
        // RAW: only (fmt, u3) set
        g_fn141823090(
            "cq_token_type: token %u can not clean "
            "cd", u3, 0, 0);
        return 0;
    }
    char c140 = ((char (*)(void*, uint32_t, uint32_t,
                           uint32_t, uint32_t, uint8_t))
        (*(void***)pp[1])[0x140 / 8])(
            pp[1], u2, 0, (uint32_t)nCnt, uPos, 1);
    if (c140 == 0) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst,
                "STR_TRAINING_GONGFU_EMONEY_"
                "NOT_ENOUGH");
        ((void (*)(void*, uint32_t, uint64_t,
                   uint32_t))
         (*(void***)pp[1])[0x28 / 8])(
            pp[1], u2, uStr, 0xffff00);
        return 0;
    }
    uint32_t u200 = ((uint32_t (*)(void*, uint32_t))
        (*(void***)pp[1])[0x200 / 8])(pp[1], u2);
    void* p1d8 = ((void* (*)(void*, uint32_t))
        (*(void***)pp[1])[0x1d8 / 8])(pp[1], u2);
    g_fn1418230a8(
        "gmlog/emoney_buy",
        "%lu\t%s\t%lu\t%lu\t%lu\t%u\t%u\t1\t",
        u2, p1d8, u200, 0x15e, uR14, (uint32_t)nCnt,
        (uint32_t)nCnt);
    g_fn1417d4f30(pMem, 4, 0, 1);
    if (((char (*)(void*, uint32_t))
             (*(void***)pp[1])[0x280 / 8])
            (pp[1], u2) != 0) {
        ((void (*)(void*, uint32_t, uint32_t))
         (*(void***)pp[1])[0x470 / 8])(pp[1], u2,
                                       u4);
    }
    uint8_t acMsg[0x200];
    g_fn1417d7350(acMsg);
    uint32_t u4ed = g_fn1417d4ed0(pMem, 3);
    char c765 = g_fn1417d7650(acMsg,
                              (uint32_t)(uint8_t)u3,
                              (uint8_t)u4ed, 0);
    if (c765 != 0) {
        ((void (*)(void*, uint32_t, void*))
         (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                     acMsg);
    }
    g_fn1417d73a0(acMsg);
    return 1;
}

// ===== Slot5e0 = 1417bfa40 (RAW) =====
// The IMPERIAL official-list broadcaster (sibling of
// Slot5e8, same msg family). RAW: u2==0 out;
// vt+0x278(box) online -> vt+0x538(box, **7**, u2,
// 0, 0); else the 0x2b-record vector filled by
// 74efa0(this+0x50, &vec); count == 0 -> d5e50 ctor
// + d5f00(msg, **0**) [NOT 1 like Slot5e8]; miss ->
// the 0x19b3 IF_NOT log ("msgList.Create(
// STATE_OFFICIAL_TYPE_IMPERIAL)") -> dtor + free;
// hit -> vt+0x8(box, u2, msg) + dtor + free, NO
// loop, NO header record; count != 0 -> d5e50 +
// d5f00(msg, 0), miss -> the **0x19bc** log ->
// dtor + free; else the loop d5f60(msg, elem)
// miss -> vt+0x8 + d60a0 clear + d5f60 RETRY
// (stride 0x2b); then ALWAYS vt+0x8 + d5ea0 dtor.
void CSyndicateLogic::Slot5e0(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        ((void (*)(void*, uint8_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x538 / 8])(pp[1], 7, u2, 0, 0);
        return;
    }
    static std::vector<Rec2b> s_vec5e0;
    s_vec5e0.clear();
    g_fn14174efa0(pp[10], (void*)&s_vec5e0);
    if (s_vec5e0.empty()) {
        uint8_t acMsgA[0x200];
        g_fn1417d5e50(acMsgA);
        if (g_fn1417d5f00(acMsgA, 0) == 0) {
            g_fnSynLogCheck(STAR_FMT, "IF_NOT",
                "msgList.Create("
                "STATE_OFFICIAL_TYPE_IMPERIAL)",
                s_pszLogicSrc, 0x19b3);
        } else {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                         acMsgA);
        }
        g_fn1417d5ea0(acMsgA);
        return;
    }
    uint8_t acMsg[0x200];
    g_fn1417d5e50(acMsg);
    if (g_fn1417d5f00(acMsg, 0) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "msgList.Create("
            "STATE_OFFICIAL_TYPE_IMPERIAL)",
            s_pszLogicSrc, 0x19bc);
        g_fn1417d5ea0(acMsg);
        return;
    }
    for (Rec2b& r : s_vec5e0) {
        if (g_fn1417d5f60(acMsg, r.ab) == 0) {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                         acMsg);
            g_fn1417d60a0(acMsg);
            g_fn1417d5f60(acMsg, r.ab);  // retry
        }
    }
    ((void (*)(void*, uint32_t, void*))
     (*(void***)pp[1])[0x8 / 8])(pp[1], u2, acMsg);
    g_fn1417d5ea0(acMsg);
}

// ===== Slot5b0 = 1417b8d90 (RAW) =====
// The league-award info sender (twin of the
// InviteNotify flow, same seams). RAW: u2==0 out;
// vt+0x278(box) online -> vt+0x538(box, **1**, u2,
// 0, 0) [channel **1**]; THIS-vt+0x510(this, u2) ->
// the league id (0 -> silent out); 630d0(host, id)
// syn miss -> the 0x1761 IF_NOT "pLeague" log; the
// 0x146 record block memset(0,0x146) + 45580 fill;
// the two 17-byte char buffers with the LITERAL
// clear pattern (b/q/d/w/b at +0x5c0 and +0x5b0);
// box-vt+0x568(box, u2, id) -> the msg id;
// 66b60(host, id, &valOut@0x44, buf5c0, 0x10) +
// 66d10(host, id, &keyOut@0x40, buf5b0, 0x10);
// d6110 msg ctor; BOTH outs are the RAW magic
// 0x431bde83>>0x12 = **/1000** (per the InviteNotify
// precedent); b5370(this, u2, syn) -> the award
// flag; d61c0(msg, rec, flag, keyOut/1000,
// valOut/1000, buf5c0, buf5b0) miss -> the 0x1772
// IF_OK log ("msgInfo.Create(stInfo, this->
// GetLeagueAwardFlag...)"); hit -> vt+0x8(box, u2,
// msg); d6160 dtor either way.
void CSyndicateLogic::Slot5b0(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        ((void (*)(void*, uint8_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x538 / 8])(pp[1], 1, u2, 0, 0);
        return;
    }
    uint32_t uLid = ((uint32_t (*)(void*, uint32_t))
        (*(void***)this)[0x510 / 8])(this, u2);
    if (uLid == 0)
        return;
    void* pSyn = g_fn1417630d0(pp[10], uLid);
    if (pSyn == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT", "pLeague",
                        s_pszLogicSrc, 0x1761);
        return;
    }
    uint8_t acRec[0x146];
    memset(acRec, 0, 0x146);    // f30c0(0, 0x146)
    g_fn141745580(pSyn, acRec);
    uint32_t uValOut = 0;       // [rsp+0x44]
    uint32_t uKeyOut = 0;       // [rsp+0x40]
    uint8_t abBuf1[0x11];       // [rsp+0x5c0]
    uint8_t abBuf2[0x11];       // [rsp+0x5b0]
    memset(abBuf1, 0, 0x11);
    memset(abBuf2, 0, 0x11);
    uint32_t uId = ((uint32_t (*)(void*, uint32_t,
                                  uint32_t))
        ppVt[0x568 / 8])(pp[1], u2, uLid);
    g_fn141766b60(pp[10], uId, &uValOut, abBuf1,
                  0x10);
    g_fn141766d10(pp[10], uId, &uKeyOut, abBuf2,
                  0x10);
    uint8_t acMsg[0x470];
    g_fn1417d6110(acMsg);
    // RAW magic 0x431bde83 >> 0x12 on BOTH = /1000
    uint32_t uB = uKeyOut / 1000;
    uint32_t uA = uValOut / 1000;
    uint32_t uFlag = g_fn1417b5370(this, u2, pSyn);
    if (!g_fn1417d61c0(acMsg, acRec, uFlag, uB, uA,
                       (const char*)abBuf1,
                       (const char*)abBuf2)) {
        g_fnSynLogCheck(STAR_FMT, "IF_OK",
            "msgInfo.Create(stInfo, this->"
            "GetLeagueAwardFlag(idUser ,pLeague), "
            "ID_SERVER_LEAGUE_SERVER(idPlunder), "
            "ID_SERVER_LEAGUE_SERVER(idPlundered), "
            "szPlunder, szPlundered)",
            s_pszLogicSrc, 0x1772);
    } else {
        ((void (*)(void*, uint32_t, void*))
         (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                     acMsg);
    }
    g_fn1417d6160(acMsg);
}

// ===== Slot608 = 1417b2a30 (RAW) =====
// The call-up token ack. RAW: three 0-gates on
// u2/u3/u4 -> return 0; vt+0x288(box) war gate miss
// -> the STR_DIE notify via the string-mgr pair +
// vt+0x18(box, u2, str) -> 0; online (vt+0x278):
// vt+0x4d0 miss -> the STR_MAP_CANNOT_ACK_TOKEN
// notify -> 0; else vt+0x458(box, u2, u3, u4) ->
// **1**; offline: vt+0x268(box,u2) miss -> 0 [al
// from the call]; the twin vt+0x4a8(box,u2) vs
// vt+0x4a8(box,u3) id check (unequal -> 0);
// vt+0x4d8(box,u2) miss -> 0; 777a30(this+0x58,
// u3, u4) rec (null -> 0); the global 1418232c8(0)
// counter: [rec+0x10] < counter -> the
// STR_CALLUP_ACK_TOKEN_TIMEOUT notify -> 0;
// vt+0x3f0(box) vs [rec]: MISMATCH branch ->
// vt+0x280(box,u2) ? vt+0x448(box, u3f0, u2,
// [rec], [rec+4], [rec+8], [rec+0xc]) : (vt+0x4d0
// gate -> the CANNOT_ACK notify + 0; vt+0x4e0(box,
// u2, [rec]) miss -> the IF_OK log **0x1fda**
// ("m_pConsumer->NotifyCSAddEnterOSUser(idMember,
// pStPublishToken->idPublishServer)") — **but still
// returns 1**; hit -> vt+0x4e8(box, u2, [rec],
// [rec+4], [rec+8], [rec+0xc])); MATCH branch ->
// vt+0x280 ? vt+0x448(...) : (vt+0x4d0 gate ->
// notify + 0; vt+0x4c0(box, u2, [rec+4], the packed
// qword [rec+8]|[rec+0xc])); every tail path
// returns 1.
bool CSyndicateLogic::Slot608(uint32_t u2,
                              uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    if (u2 == 0)
        return 0;
    if (u3 == 0)
        return 0;
    if (u4 == 0)
        return 0;
    void** ppVt = *(void***)pp[1];
    if (((char (*)(void*))ppVt[0x288 / 8])
            (pp[1]) == 0) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(pInst, "STR_DIE");
        ((void (*)(void*, uint32_t, uint64_t))
         ppVt[0x18 / 8])(pp[1], u2, uStr);
        return 0;
    }
    if (((char (*)(void*, uint32_t))ppVt[0x278 / 8])
            (pp[1], u2) != 0) {
        if (((char (*)(void*, uint32_t))
                 ppVt[0x4d0 / 8])(pp[1], u2) == 0) {
            void* pInst = g_fnStringMgrInstance();
            uint64_t uStr = (uint64_t)
                g_fnStringMgrGetStr(
                    pInst,
                    "STR_MAP_CANNOT_ACK_TOKEN");
            ((void (*)(void*, uint32_t, uint64_t))
             ppVt[0x18 / 8])(pp[1], u2, uStr);
            return 0;
        }
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x458 / 8])(pp[1], u2, u3, u4);
        return 1;
    }
    if (((char (*)(void*, uint32_t))ppVt[0x268 / 8])
            (pp[1], u2) == 0)
        return 0;
    uint32_t uIdA = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u2);
    uint32_t uIdB = ((uint32_t (*)(void*, uint32_t))
        ppVt[0x4a8 / 8])(pp[1], u3);
    if (uIdA != uIdB)
        return 0;
    if (((char (*)(void*, uint32_t))ppVt[0x4d8 / 8])
            (pp[1], u2) == 0)
        return 0;
    void* pRec = g_fn141777a30(pp[11], u3, u4);
    if (pRec == 0)
        return 0;
    uint32_t uCnt = g_fn1418232c8(0);
    if (*(int32_t*)((char*)pRec + 0x10) <
        (int32_t)uCnt) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst, "STR_CALLUP_ACK_TOKEN_TIMEOUT");
        ((void (*)(void*, uint32_t, uint64_t))
         ppVt[0x18 / 8])(pp[1], u2, uStr);
        return 0;
    }
    uint32_t u3f0 = ((uint32_t (*)(void*))
        (*(void***)pp[1])[0x3f0 / 8])(pp[1]);
    uint32_t* pu = (uint32_t*)pRec;
    if (u3f0 != pu[0]) {
        // the MISMATCH branch
        if (((char (*)(void*, uint32_t))
                 (*(void***)pp[1])[0x280 / 8])
                (pp[1], u2) != 0) {
            ((void (*)(void*, uint32_t, uint32_t,
                       uint32_t, uint32_t, uint32_t,
                       uint32_t))
             (*(void***)pp[1])[0x448 / 8])(
                pp[1], u3f0, u2, pu[0], pu[1],
                pu[2], pu[3]);
            return 1;
        }
        if (((char (*)(void*, uint32_t))
                 (*(void***)pp[1])[0x4d0 / 8])
                (pp[1], u2) == 0) {
            void* pInst = g_fnStringMgrInstance();
            uint64_t uStr = (uint64_t)
                g_fnStringMgrGetStr(
                    pInst,
                    "STR_MAP_CANNOT_ACK_TOKEN");
            ((void (*)(void*, uint32_t, uint64_t))
             (*(void***)pp[1])[0x18 / 8])(
                pp[1], u2, uStr);
            return 0;
        }
        if (((char (*)(void*, uint32_t, uint32_t))
                 (*(void***)pp[1])[0x4e0 / 8])
                (pp[1], u2, pu[0]) == 0) {
            // RAW: logs but STILL returns 1
            g_fnSynLogCheck(STAR_FMT, "IF_OK",
                "m_pConsumer->NotifyCSAddEnterOSUser("
                "idMember, pStPublishToken->"
                "idPublishServer)",
                s_pszLogicSrc, 0x1fda);
        } else {
            ((void (*)(void*, uint32_t, uint32_t,
                       uint32_t, uint32_t, uint32_t))
             (*(void***)pp[1])[0x4e8 / 8])(
                pp[1], u2, pu[0], pu[1], pu[2], pu[3]);
        }
        return 1;
    }
    // the MATCH branch
    if (((char (*)(void*, uint32_t))
             (*(void***)pp[1])[0x280 / 8])
            (pp[1], u2) != 0) {
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t, uint32_t, uint32_t,
                   uint32_t))
         (*(void***)pp[1])[0x448 / 8])(
            pp[1], u3f0, u2, pu[0], pu[1], pu[2],
            pu[3]);
        return 1;
    }
    if (((char (*)(void*, uint32_t))
             (*(void***)pp[1])[0x4d0 / 8])
            (pp[1], u2) == 0) {
        void* pInst = g_fnStringMgrInstance();
        uint64_t uStr = (uint64_t)
            g_fnStringMgrGetStr(
                pInst, "STR_MAP_CANNOT_ACK_TOKEN");
        ((void (*)(void*, uint32_t, uint64_t))
         (*(void***)pp[1])[0x18 / 8])(pp[1], u2,
                                      uStr);
        return 0;
    }
    ((void (*)(void*, uint32_t, uint32_t,
               uint64_t))
     (*(void***)pp[1])[0x4c0 / 8])(
        pp[1], u2, pu[1],
        *(const uint64_t*)(pu + 2));   // packed
    return 1;
}

// ===== Slot5e8 = 1417bfdd0 (RAW) =====
// The official-list broadcaster. RAW: u2==0 out;
// vt+0x278(box) online -> vt+0x538(box, **8**, u2,
// 0, 0) [xor esi + [rsp+0x20]=0]; else a 0x2b header
// record zeroed at rsp+0x490 (the literal clear
// pattern: d490/w494/d496/d49a/d49e/d4a2/w4a6/w4a8/
// b4aa/q4ab/q4b3) filled by 74ef60(this+0x50, &rec);
// a 0x2b-record vector filled by 74efa0(this+0x50,
// &vec); msg d5e50 ctor; d5f00(msg, **1**) miss -> the
// IF_NOT log **0x19e4** ("msgList.Create(
// STATE_OFFICIAL_TYPE_IMPERIAL_AND_KING)") -> d5ea0
// dtor + free, out; else d5f60(msg, &rec) [result
// NOT checked]; the loop over the vector: d5f60 miss
// -> vt+0x8(box, u2, msg) + d60a0(msg) [clear] +
// d5f60 RETRY; stride 0x2b; then ALWAYS vt+0x8(box,
// u2, msg) + d5ea0 + free.
void CSyndicateLogic::Slot5e8(uint32_t u2) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        ((void (*)(void*, uint8_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x538 / 8])(pp[1], 8, u2, 0, 0);
        return;
    }
    Rec2b acRec;
    memset(acRec.ab, 0, 0x2b);    // the literal clear
    g_fn14174ef60(pp[10], acRec.ab);
    static std::vector<Rec2b> s_vec5e8;
    s_vec5e8.clear();
    g_fn14174efa0(pp[10], (void*)&s_vec5e8);
    uint8_t acMsg[0x200];
    g_fn1417d5e50(acMsg);
    if (g_fn1417d5f00(acMsg, 1) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "msgList.Create("
            "STATE_OFFICIAL_TYPE_IMPERIAL_AND_KING)",
            s_pszLogicSrc, 0x19e4);
        g_fn1417d5ea0(acMsg);
        return;
    }
    g_fn1417d5f60(acMsg, acRec.ab);   // NOT checked
    for (Rec2b& r : s_vec5e8) {
        if (g_fn1417d5f60(acMsg, r.ab) == 0) {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                         acMsg);
            g_fn1417d60a0(acMsg);
            g_fn1417d5f60(acMsg, r.ab); // the retry
        }
    }
    ((void (*)(void*, uint32_t, void*))
     (*(void***)pp[1])[0x8 / 8])(pp[1], u2, acMsg);
    g_fn1417d5ea0(acMsg);
}

// the RAW sort predicate 1417b0950 (baked into the lea
// of c0d10 — ported verbatim as a module static):
// flag byte @+0x1a, key WORD @+0x4, **seta = DESCENDING**
// (vs b0920's setb ascending).
static char SynListPred1417b0950(const void* pa,
                                const void* pb) {
    const uint8_t* a = (const uint8_t*)pa;
    const uint8_t* b = (const uint8_t*)pb;
    uint8_t aF = a[0x1a];
    if (aF != 0) {
        if (b[0x1a] == 0)
            return 1;               // mov al,1; ret
        // both set -> the word compare
    } else {
        if (b[0x1a] != 0)
            return 0;              // xor al,al; ret
        // both clear -> the word compare
    }
    uint16_t uB = *(const uint16_t*)(b + 0x4);
    return *(const uint16_t*)(a + 0x4) > uB;   // seta
}

// ===== Slot5f0 = 1417c0d10 (RAW, the 5th big fn) =====
// The 0x2b-stride list pager. RAW: u2==0 out; b3 =
// movzx r8b; b3 < 1 (unsigned jb) out; vt+0x278(box)
// online -> vt+0x538(box, **10**, u2, **0**, b3 [the
// 5th stack arg]); else 74ef80(this+0x50, &vec) —
// NOTE: no syn lookup, the manager pointer directly;
// the 0x2b records; nPage = b3*10 - 10 (lea *5, *2,
// -0xa); count = (end-begin)/43 (the
// 0x5f417d05f417d06 magic); nPage >= count -> the
// SINGLE-PAGE branch: d7800 ctor + d78b0(msg, b3),
// miss -> the IF_NOT log **0x195b** ("msgList.Create(
// ucPage)"), hit -> vt+0x8(box, u2, msg), then d7850
// dtor + free either way; nPage < count -> sort the
// WHOLE vector bf7c0(begin, end, count,
// &SynListPred1417b0950), d7800 + d78b0 (miss -> the
// **0x1967** log), then the window loop p = begin +
// nPage*0x2b, n=0, cap 10: d7910(msg, p) miss ->
// vt+0x8(box, u2, msg) + d7a40(msg) + d7910 RETRY;
// then ALWAYS vt+0x8(box, u2, msg) + d7850 + free.
void CSyndicateLogic::Slot5f0(uint32_t u2,
                              uint8_t b3) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    if (b3 < 1)                     // cmp bl,1; jb
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        // RAW: [rsp+0x20] = (uint32_t)b3
        ((void (*)(void*, uint8_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x538 / 8])(pp[1], 0xa, u2, 0, b3);
        return;
    }
    // RAW models the MSVC checked-iterated vector of
    // 0x2b records (f3166(8)/anchor probes = no-ops)
    static std::vector<Rec2b> s_vec2b;
    s_vec2b.clear();
    g_fn14174ef80(pp[10], (void*)&s_vec2b);
    int32_t nPage = (int32_t)(b3 * 10 - 10);   // ebp
    int64_t nCount = (int64_t)s_vec2b.size();
    char* pBegin = (char*)s_vec2b.data();
    char* pEnd = pBegin + s_vec2b.size() * 0x2b;
    if (nPage >= nCount) {
        // the single-page branch
        uint8_t acMsg2[0x200];
        g_fn1417d7800(acMsg2);
        if (g_fn1417d78b0(acMsg2, b3) == 0) {
            g_fnSynLogCheck(STAR_FMT, "IF_NOT",
                "msgList.Create(ucPage)",
                s_pszLogicSrc, 0x195b);
        } else {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                         acMsg2);
        }
        g_fn1417d7850(acMsg2);
        return;
    }
    g_fn1417bf7c0(pBegin, pEnd, nCount,
                  (void*)&SynListPred1417b0950);
    uint8_t acMsg[0x200];
    g_fn1417d7800(acMsg);
    if (g_fn1417d78b0(acMsg, b3) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "msgList.Create(ucPage)",
            s_pszLogicSrc, 0x1967);
        g_fn1417d7850(acMsg);
        return;
    }
    char* p = pBegin + (int64_t)nPage * 0x2b;
    uint32_t n = 0;
    for (; p != pEnd && n < 0xa; ++n, p += 0x2b) {
        if (g_fn1417d7910(acMsg, p) == 0) {
            ((void (*)(void*, uint32_t, void*))
             (*(void***)pp[1])[0x8 / 8])(pp[1], u2,
                                         acMsg);
            g_fn1417d7a40(acMsg);
            g_fn1417d7910(acMsg, p);      // the retry
        }
    }
    ((void (*)(void*, uint32_t, void*))
     (*(void***)pp[1])[0x8 / 8])(pp[1], u2, acMsg);
    g_fn1417d7850(acMsg);
}

// ===== Slot5d0 = 1417c0860 (RAW, the 4th big fn) =====
// The 0x2d-stride info-list fn. RAW: u2==0 out; u3==0
// out; vt+0x278(box) online -> vt+0x538(box, **4**, u2,
// u3, u4) [NOTE the 5th stack arg = u4 — different arg
// order than the channel-3/5 family]; else
// 630d0(this+0x50, **u3**) syn (==0 out); a checked-
// iterated std::vector<0x2d records> filled by
// 74dda0(syn, &vec); edi = u4*10 (32-bit lea);
// count = (end-begin)/45 (the 0x2d82d82d82d82d83 magic);
// u4*10 >= count or < 0 -> vector free, OUT (no msg
// yet); std::sort bf610(begin, end, count, &SynInfoPred
// [1417b0920]); msg d9410 ctor; d94c0(msg, 0, count, 0)
// miss -> the IF_NOT log 0x17fb ("msgInfo.Create(ID_NONE
// , (int)vecInfo.size())") + d9460 dtor + free, out;
// the record loop: p = begin + movsxd(u4*10)*0x2d,
// n=0; while (p != end && n < 10): copy the 45 bytes,
// then with uKey = *(uint32_t*)(rec+0x27): rec.d0x23 =
// vt+0x228(box, uKey); rec.d0x1f = vt+0x540(**this**,
// uKey); if vt+0x268(box, uKey) -> rec.w0x2b = vt+0x258(
// box, uKey); d9550(msg, &rec) miss -> vt+0x8(box, u2,
// msg) + d9690(msg) + d9550(msg, &rec) RETRY; inc n;
// p += 0x2d; then ALWAYS vt+0x8(box, u2, msg) + d9460
// dtor + vector free.
//
// the RAW sort predicate 1417b0920 (a real fn ADDRESS
// baked into the lea — ported verbatim as a module
// static): pred(a,b): a.b0xe&&!b.b0xe -> true; !a.b0xe&&
// b.b0xe -> false; equal flags -> a.d0x27 <u b.d0x27
// (setb).
static char SynInfoPred1417b0920(const void* pa,
                                 const void* pb) {
    const uint8_t* a = (const uint8_t*)pa;
    const uint8_t* b = (const uint8_t*)pb;
    uint8_t aE = a[0xe];
    if (aE != 0) {
        if (b[0xe] == 0)
            return 1;               // mov al,1; ret
        // both set -> the d27 compare
    } else {
        if (b[0xe] != 0)
            return 0;              // xor al,al; ret
        // both clear -> the d27 compare
    }
    uint32_t uB = *(const uint32_t*)(b + 0x27);
    return *(const uint32_t*)(a + 0x27) < uB;
}

void CSyndicateLogic::Slot5d0(uint32_t u2,
                              uint32_t u3,
                              uint32_t u4) {
    void** pp = (void**)this;
    if (u2 == 0)
        return;
    if (u3 == 0)
        return;
    void** ppVt = *(void***)pp[1];
    char cOn = ((char (*)(void*))(
        ppVt[0x278 / 8]))(pp[1]);
    if (cOn != 0) {
        // RAW: [rsp+0x20] = u4 (the 5th arg)
        ((void (*)(void*, uint8_t, uint32_t, uint32_t,
                   uint32_t))
         ppVt[0x538 / 8])(pp[1], 4, u2, u3, u4);
        return;
    }
    void* pSyn = g_fn1417630d0(pp[10], u3);
    if (pSyn == 0)
        return;
    // RAW models an MSVC checked-iterated
    // std::vector<0x2d records>; the f3166(8)/f2fdc +
    // anchor probes are iterator-safety no-ops modeled
    // by std::vector itself here.
    static std::vector<Rec2d> s_vec2d;
    s_vec2d.clear();
    g_fn14174dda0(pSyn, (void*)&s_vec2d);
    int32_t nOff = (int32_t)(u4 * 10);   // lea edi*5; add
    int64_t nCount = (int64_t)s_vec2d.size();
    if (nOff >= nCount || nOff < 0)
        return;                        // jge / js -> free+out
    char* pBegin = (char*)s_vec2d.data();
    char* pEnd = pBegin + s_vec2d.size() * 0x2d;
    g_fn1417bf610(pBegin, pEnd, nCount,
                  (void*)&SynInfoPred1417b0920);
    uint8_t acMsg[0x200];
    g_fn1417d9410(acMsg);
    if (g_fn1417d94c0(acMsg, 0, nCount, 0) == 0) {
        g_fnSynLogCheck(STAR_FMT, "IF_NOT",
            "msgInfo.Create(ID_NONE, "
            "(int)vecInfo.size())",
            s_pszLogicSrc, 0x17fb);
        g_fn1417d9460(acMsg);
        return;
    }
    char* p = pBegin + (int64_t)nOff * 0x2d;
    uint32_t n = 0;
    for (; p != pEnd && n < 0xa;
         ++n, p += 0x2d) {
        Rec2d acRec;
        memcpy(acRec.ab, p, 0x2d);     // the verbatim copy
        uint32_t uKey = *(uint32_t*)(acRec.ab + 0x27);
        void** ppBox = *(void***)pp[1];
        *(uint32_t*)(acRec.ab + 0x23) =
            ((uint32_t (*)(void*, uint32_t))
             ppBox[0x228 / 8])(pp[1], uKey);
        *(uint32_t*)(acRec.ab + 0x1f) =
            ((uint32_t (*)(void*, uint32_t))
             (*(void***)this)[0x540 / 8])(this, uKey);
        if (((char (*)(void*, uint32_t))
             ppBox[0x268 / 8])(pp[1], uKey) != 0)
            *(uint16_t*)(acRec.ab + 0x2b) =
                ((uint16_t (*)(void*, uint32_t))
                 ppBox[0x258 / 8])(pp[1], uKey);
        if (g_fn1417d9550(acMsg, acRec.ab) == 0) {
            ((void (*)(void*, uint32_t, void*))
             ppBox[0x8 / 8])(pp[1], u2, acMsg);
            g_fn1417d9690(acMsg);
            g_fn1417d9550(acMsg, acRec.ab);  // the retry
        }
    }
    ((void (*)(void*, uint32_t, void*))
     (*(void***)pp[1])[0x8 / 8])(pp[1], u2, acMsg);
    g_fn1417d9460(acMsg);
}

// RAW 5880 (beats the decompile's 200000000000/CONCAT
// artifacts): movsxd n3; sum = 7440d0(syn) + n3 (FULL
// 64-bit lea); cmp sum, 0x2e90edd000; **ja** -> xor
// al,al ret 0; else 744130(syn, sum, r8b=1); mov al,1
bool CSyndicateLogic::Slot5a8(uint32_t u2,
                              int32_t n3) {
    void** pp = (void**)this;
    void* pSyn = g_fn1417630d0(pp[10], u2);
    if (pSyn == 0)
        return false;
    uint64_t uSum = (uint64_t)g_fn1417440d0(pSyn) +
                    (uint64_t)(int64_t)n3;
    if (uSum > 0x2e90edd000ull)
        return false;
    g_fn141744130(pSyn, (uint32_t)uSum, 1);
    return true;
}

// ===== the +0x50 getter cluster (all verbatim
// forwards) =====
void CSyndicateLogic::Slot590(uint32_t u2,
                              uint32_t u3) {
    g_fn141764b80(*(void**)((char*)this + 0x50),
                  u2, u3);
}
void CSyndicateLogic::Slot598(uint32_t u2,
                              uint32_t u3) {
    g_fn141764f10(*(void**)((char*)this + 0x50),
                  u2, u3);
}
void CSyndicateLogic::Slot620(uint16_t u2) {
    g_fn1417684b0(*(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot628(uint16_t u2) {
    g_fn1417685f0(*(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot630(uint32_t u2) {
    g_fn14175fa60(*(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot638(uint32_t u2) {
    g_fn1417652c0(*(void**)((char*)this + 0x50), u2);
}
void CSyndicateLogic::Slot668(void) {
    g_fn14174ebb0(*(void**)((char*)this + 0x50));
}
void CSyndicateLogic::Slot670(uint32_t u2, int32_t n3,
                              void*** ppp4) {
    g_fn1417715f0(*(void**)((char*)this + 0x50),
                  u2, n3, ppp4);
}
void CSyndicateLogic::Slot678(void) {
    g_fn141774c20(*(void**)((char*)this + 0x50));
}
void CSyndicateLogic::Slot658(uint16_t u2,
                              uint32_t* pu3) {
    g_fn141766330(*(void**)((char*)this + 0x50),
                  u2, pu3);
}
void CSyndicateLogic::Slot660(uint16_t u2,
                              uint32_t* pu3) {
    g_fn14176ff50(*(void**)((char*)this + 0x50),
                  u2, pu3);
}

}  // namespace syndicate
