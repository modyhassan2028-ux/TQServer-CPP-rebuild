// SyndicateLogicTable1.cpp — unit D90 (the header has the
// address map + the seam list).
#include <cstdio>
#include "modules/syndicate/src/syndicatelogic.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"       // LeagueMemberLookup
#include "modules/syndicate/src/SyndicateLogRemove.h"        // LogRecMapFind
#include "modules/syndicate/src/SyndicateCMsgCtors.h"        // the msg ctors
#include "modules/syndicate/src/SyndicateLeagueMgr.h"        // MgrUserLeagueId/Find
#include "modules/syndicate/src/SyndicateLeagueOpt.h"        // the string mgr
#include "modules/syndicate/src/SyndicateAppoint3de.h"       // the A84 seams
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"  // g_fnLbrOpDelete
#include <cstring>
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

// +0x268: 1417b0770
uint64_t CSyndicateLogic::Slot268(int32_t n) {
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

// +0x270: 1417b07c0
uint64_t CSyndicateLogic::Slot270(int32_t n) {
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

// +0x278: 1417b9650
void CSyndicateLogic::Slot278(uint32_t u, int32_t n3,
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

// +0x280: 1417b9880
void CSyndicateLogic::Slot280(uint32_t u, int32_t n3,
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

// +0x288: 1417b1b90
void CSyndicateLogic::Slot288(uint32_t u) {
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
void CSyndicateLogic::Slot2D8(int32_t* p2) {
    g_fn76FE50(((void**)this)[10], p2);
}

// +0x2e0: 1417b22b0
void CSyndicateLogic::Slot2E0(void) {
    g_fn76ACE0(((void**)this)[10]);
}

// +0x2e8: 1417b22c0
void CSyndicateLogic::Slot2E8(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn763DD0(((void**)this)[10], n2, n3, p4);
}

// +0x2f0: 1417b22d0
void CSyndicateLogic::Slot2F0(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn764000(((void**)this)[10], n2, n3, p4);
}

// +0x2f8: 1417b22e0
void CSyndicateLogic::Slot2F8(int32_t n2, int32_t n3,
                              const char* p4) {
    g_fn764230(((void**)this)[10], n2, n3, p4);
}

// +0x300: 1417b22f0
void CSyndicateLogic::Slot300(uint32_t u2, int32_t n3) {
    g_fn764300(((void**)this)[10], u2, n3);
}

// +0x308: 1417b2300
void CSyndicateLogic::Slot308(int32_t n2, int32_t n3,
                              int32_t n4) {
    g_fn76EFC0(((void**)this)[10], n2, n3, n4);
}

// +0x310: 1417b2310
void CSyndicateLogic::Slot310(void) {
    g_fn76F190(((void**)this)[10]);
}

// +0x318: 1417b2320
void CSyndicateLogic::Slot318(uint16_t u2, uint32_t u3) {
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
void CSyndicateLogic::Slot320(uint32_t u2) {
    g_fn7645C0(((void**)this)[10], u2);
}

// +0x328: 1417b2400
void CSyndicateLogic::Slot328(uint32_t u) {
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
void CSyndicateLogic::Slot330(void) {
    void** pp = (void**)this;
    // RAW: box vt+0xa0 (no visible args at all)
    ((void (*)(void*))
        (*(void***)pp[1])[0xa0/8])(pp[1]);
}
// +0x340: 1417b8940 — the create-league flow
bool CSyndicateLogic::Slot340(uint32_t u2,
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
void CSyndicateLogic::Slot350(uint32_t u2, uint32_t u3,
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
void CSyndicateLogic::Slot358(uint32_t u2, uint32_t u3,
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


}  // namespace syndicate
