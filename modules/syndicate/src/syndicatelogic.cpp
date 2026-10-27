// SyndicateLogicTable1.cpp — unit D90 (the header has the
// address map + the seam list).
#include "modules/syndicate/src/syndicatelogic.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"       // LeagueMemberLookup
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"        // LogRecMapFind
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"        // the msg ctors
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"        // MgrUserLeagueId/Find
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"        // the string mgr
#include "Exe/Dll/Syndicate/Port/SyndicateAppoint3de.h"       // the A84 seams
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"  // g_fnLbrOpDelete
#include <cstring>

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

}  // namespace syndicate
