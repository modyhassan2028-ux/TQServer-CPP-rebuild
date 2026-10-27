// SyndicateLeagueInvadeWarn.cpp — unit D89 (see the header
// for the address map and the seam list).
#include "modules/syndicate/src/league.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"        // g_fnTreeFindAF0
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgrNested.h"  // NestedErOneB/RangeB
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderSignup.h"   // g_fnSupTimeGet
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"         // str mgr seams
#include "Exe/Dll/Syndicate/Port/SyndicateMsgProcess.h"        // g_fnCMsgInitThunk
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"         // g_fnLeagueInvalid
#include "Exe/Dll/Syndicate/Port/SyndicateProfferRankList.h"   // g_pvD87CMsgVft
#include <cstring>

namespace syndicate {

// ================= FUN_1417d50f0 =================
// the CMsgInvadeWarning ctor: tq vft + Init, the derived
// vft + Init, then the PB obj at +0x408 = this + 8.
void* CtorCMsgInvadeWarning(void* pMsg) {
    char* pcMsg = (char*)pMsg;
    *(void**)pcMsg = g_pvD87CMsgVft;
    g_fnCMsgInitThunk(pMsg);
    *(void**)pcMsg = g_pvD89CMsgInvadeVft;
    g_fnCMsgInitThunk(pMsg);
    *(void**)(pcMsg + 0x408) = pcMsg + 8;
    return pMsg;
}

// ================= FUN_1417d5140 =================
// the dtor: the derived vft then the base vft (the
// verbatim two stores, no Init).
void DtorCMsgInvadeWarning(void* pMsg) {
    *(void**)pMsg = g_pvD89CMsgInvadeVft;
    *(void**)pMsg = g_pvD87CMsgVft;
}

// ================= FUN_1417d5250 =================
// the Init variant 1: the 0xc1c header + the fields.
uint64_t InitCMsgInvadeWarning1(void* pMsg, uint32_t uTime,
                                uint32_t uMapId, uint16_t uX,
                                uint16_t uY) {
    g_fnCMsgInitThunk(pMsg);
    char* pcPb = *(char**)((char*)pMsg + 0x408);
    *(uint16_t*)(pcPb + 2) = 0xc1c;
    *(uint16_t*)(pcPb + 0) = 0x22;
    *(uint16_t*)(pcPb + 4) = 1;
    *(uint32_t*)(pcPb + 10) = uMapId;
    *(uint32_t*)(pcPb + 6) =
        (uint32_t)uX * 10000 + (uint32_t)uY;
    *(uint32_t*)(pcPb + 0xe) = uTime;
    return 1;
}

// ================= FUN_1417d5170 =================
// the Create check: the base Create then the type match.
bool CreateCheckCMsgInvadeWarning(void* pMsg, void* pSrc,
                                  uint16_t uType) {
    if (!g_fnInvCMsgCreate(pMsg, pSrc, uType)) {
        return false;
    }
    return *(uint16_t*)((char*)pMsg + 10) == 0xc1c;
}

// ================= FUN_1417d52f0 =================
void* DeletingDtorCMsgInvadeWarning(void* pMsg,
                                    uint8_t bDelete) {
    *(void**)pMsg = g_pvD89CMsgInvadeVft;
    if ((bDelete & 1) != 0) {
        g_fnInvOpDelete(pMsg);
    }
    return pMsg;
}

}  // namespace syndicate

namespace syndicate {

// ================= FUN_141774500 =================
// CLeagueMgr::FlyToInvadeWarning — verbatim.
uint8_t CLeagueMgr::FlyToInvadeWarning(
    int64_t lMgr, uint32_t uUser, uint32_t uTarget) {
    char* pcMgr = (char*)lMgr;
    if (uUser == 0 || uTarget == 0) {
        return 0;
    }
    // the three outs of the 0x498 fetch: mapId,
    // x, y (local_5c4[0] / local_5c8[0] /
    // local_res20[0])
    uint32_t aMapPos[3] = {0, 0, 0};
    uint16_t uX = 0;
    uint16_t uY = 0;

    // the +8 mgr object (the box) + its vtable
    void* pObj = *(void**)(pcMgr + 8);
    void** pVt = *(void***)pObj;

    // ---- the state gate (slot 0x288, this-only;
    //      RAW-verified: no edx at the call) ----
    if (((char (*)(void*))pVt[0x288 / 8])(pObj) == 0) {
        void* pIv = g_fnStringMgrInstance();
        const char* pcDie = (const char*)
            g_fnStringMgrGetStr(pIv, "STR_DIE");
        ((void (*)(void*, uint32_t,
                   const char*))pVt[0x18 / 8])(
            pObj, uUser, pcDie);
        return 0;
    }
    // ---- the map+pos fetch (slot 0x498) ----
    if (((char (*)(void*, uint32_t, uint32_t*,
                   uint16_t*, uint16_t*))
             pVt[0x498 / 8])(
            pObj, uUser, &aMapPos[0], &uX,
            &uY) == 0) {
        return 0;
    }
    // ---- the user's transmit check (slot 0x570) ----
    if (((char (*)(void*, uint32_t, uint32_t,
                   uint16_t, uint16_t))
             pVt[0x570 / 8])(
            pObj, uUser, aMapPos[0], uX, uY) ==
        0) {
        void* pIv = g_fnStringMgrInstance();
        const char* pcMsg = (const char*)
            g_fnStringMgrGetStr(
                pIv, "STR_MAP_NOT_TRANSMIT");
        ((void (*)(void*, uint32_t,
                   const char*))pVt[0x18 / 8])(
            pObj, uUser, pcMsg);
        return 0;
    }
    // ---- the target-map find at +0x228
    //      (key = uTarget; seam 141760a20) ----
    uint32_t uKeyT = uTarget;
    int64_t aTIter[2];       // {local_5a8, uStack_5a0}
    g_fnInvFindTarget((void*)(pcMgr + 0x228),
                      aTIter, &uKeyT);
    int64_t lTHead = *(int64_t*)(pcMgr + 600);
    if ((*(int64_t*)(pcMgr + 0x228) == 0) ||
        (*(int64_t*)(pcMgr + 0x228) !=
         aTIter[0])) {
        g_fnLeagueInvalid();
    }
    int64_t lTNode = aTIter[1];
    int64_t lTProxy = aTIter[0];   // saved BEFORE
                                   // the pair build
    if (lTHead == lTNode) {
        return 0;   // the end iterator
    }
    // ---- the insert pair: value =
    //      {uTarget, vt[0x3e8](mgr, user)}, key =
    //      mapId|<<x|<<y (the CONCAT26/24 packing)
    //      ----
    aTIter[1] = 0;
    aTIter[0] = (int64_t)(uint64_t)uTarget;
    uint32_t uVar9 = (uint32_t)((uint64_t (*)(
        void*, uint32_t))pVt[0x3e8 / 8])(
        pObj, uUser);
    aTIter[0] = (int64_t)(((uint64_t)uVar9 << 32) |
        (uint64_t)(uint32_t)aTIter[0]);
    aTIter[1] = (int64_t)(((uint64_t)uY << 32) |
        ((uint64_t)uX << 16) |
        (uint64_t)(aMapPos[0] & 0xffff));
    // the 3x proxy unwrap (the +0x30 orphan check)
    for (int i = 0; i < 3; i++) {
        if (lTProxy == 0) {
            g_fnLeagueInvalid();
        } else if (lTNode ==
            *(int64_t*)(*(int64_t*)lTProxy +
                        0x30)) {
            g_fnLeagueInvalid();
        }
    }
    // ---- the target's transmit check on the
    //      stored pos at node+0x20/24/26 ----
    if (((char (*)(void*, uint32_t, uint32_t,
                   uint16_t, uint16_t))
             pVt[0x570 / 8])(
            pObj, uUser,
            *(uint32_t*)(lTNode + 0x20),
            *(uint16_t*)(lTNode + 0x24),
            *(uint16_t*)(lTNode + 0x26)) == 0) {
        void* pIv = g_fnStringMgrInstance();
        const char* pcMsg = (const char*)
            g_fnStringMgrGetStr(
                pIv,
                "STR_TARGET_MAP_NOT_TRANSMIT");
        ((void (*)(void*, uint32_t,
                   const char*))pVt[0x18 / 8])(
            pObj, uUser, pcMsg);
        return 0;
    }
    // ---- the point check (slot 0x4c0) with the
    //      packed x|y from the stored pos ----
    uint32_t uXY = (uint32_t)
        *(uint16_t*)(lTNode + 0x24);
    uXY = ((uint32_t)*(uint16_t*)(lTNode + 0x26)
           << 16) | (uXY & 0xffff);
    if (((char (*)(void*, uint32_t, uint32_t,
                   uint32_t))pVt[0x4c0 / 8])(
            pObj, uUser,
            *(uint32_t*)(lTNode + 0x20),
            uXY) == 0) {
        for (int i = 0; i < 4; i++) {
            if (lTProxy == 0) {
                g_fnLeagueInvalid();
            } else if (lTNode ==
                *(int64_t*)(*(int64_t*)lTProxy +
                            0x30)) {
                g_fnLeagueInvalid();
            }
        }
        g_fnInvLogError(
            "CLeagueMgr::FlyToInvadeWarning error"
            " point Map[u%], posX[%u], posY[%u]");
        return 0;
    }
    // ---- the time + the user-map find at +0x2b0
    //      (141760af0 = g_fnTreeFindAF0) ----
    uint32_t uNow = g_fnSupTimeGet(0);
    uint32_t uKeyU = uUser;
    int64_t aUIter[2];       // {local_5b8, lStack_5b0}
    g_fnTreeFindAF0((void*)(pcMgr + 0x2b0),
                    aUIter, &uKeyU);
    int64_t lUHead = *(int64_t*)(pcMgr + 0x2e0);
    if ((*(int64_t*)(pcMgr + 0x2b0) == 0) ||
        (*(int64_t*)(pcMgr + 0x2b0) !=
         aUIter[0])) {
        g_fnLeagueInvalid();
    }
    int64_t lUNode = aUIter[1];
    int64_t lUProxy = aUIter[0];
    // the 20-byte block {time, pair} (the
    // local_588/584/580/57c/578 run)
    uint32_t aBlock[5];
    aBlock[0] = uNow;
    aBlock[1] = (uint32_t)(uint64_t)aTIter[0];
    aBlock[2] = (uint32_t)((uint64_t)aTIter[0] >>
                           32);
    aBlock[3] = (uint32_t)(uint64_t)aTIter[1];
    aBlock[4] = (uint32_t)((uint64_t)aTIter[1] >>
                           32);
    if (lUHead == lUNode) {
        // ---- the NOT-FOUND insert path ----
        char acSubMap[0x30];      // local_568[6]
        g_fnInvListCtor(acSubMap);
        void* pInsNode = g_fnInvListInsert(
            acSubMap, aTIter, aBlock);
        char acShp490[0x48];      // local_490[9]
        g_fnInvShpCopy(acShp490,
                       (int64_t)(intptr_t)acSubMap);
        char acBox4d8[0x10];      // local_4d8[2]
        void* p400 = g_fnInvBox400(
            acBox4d8, uUser, acShp490);
        uint64_t uVal520[1];      // local_520[0]
        uVal520[0] = *(uint64_t*)p400;
        char acShp518[0x40];      // local_518[8]
        g_fnInvShpCopy(
            acShp518,
            (int64_t)(uintptr_t)((char*)p400 +
                                 16));
        g_fnInvMapInsert(
            (void*)(pcMgr + 0x2b0), aBlock,
            uVal520);
        g_fnInvListDtor(acShp518);
        g_fnInvOpDelete(*(void**)acShp518);
        char acBox4d0[0x40];      // local_4d0[8]
        g_fnInvListDtor(acBox4d0);
        g_fnInvOpDelete(*(void**)acBox4d0);
        // the erase-range from the temp sub-map:
        // first = {map[0], *node}, last =
        // {map[0], node} (the saved RAW slots)
        int64_t aFirst[2], aLast[2];
        aFirst[0] = *(int64_t*)acSubMap;
        aFirst[1] = *(int64_t*)pInsNode;
        aLast[0] = *(int64_t*)acSubMap;
        aLast[1] = (int64_t)(intptr_t)pInsNode;
        g_fnInvEraseRange(acSubMap, aBlock, aFirst,
                          aLast);
        g_fnInvOpDelete(pInsNode);
        g_fnInvOpDelete(*(void**)acSubMap);
    }
    else {
        // ---- the FOUND update path ----
        if (lUProxy == 0) {
            g_fnLeagueInvalid();
        } else if (lUNode ==
            *(int64_t*)(*(int64_t*)lUProxy +
                        0x30)) {
            g_fnLeagueInvalid();
        }
        int64_t* plVal =
            (int64_t*)(lUNode + 0x20);
        g_fnInvListInsert((void*)plVal, aTIter,
                          aBlock);
        // the >5 pop via NestedErOneB
        if (5 < *(uint64_t*)(lUNode + 0x58)) {
            int64_t* plList =
                *(int64_t**)(lUNode + 0x50);
            int64_t* plHead =
                (int64_t*)*plList;
            int64_t aIter1[2];
            aIter1[0] = *(int64_t*)plVal;
            aIter1[1] = (int64_t)plHead;
            if (aIter1[0] == 0) {
                g_fnLeagueInvalid();
            }
            if (plList != plHead) {
                int64_t aTmp[2];
                g_fnInvPopOne(plVal, aTmp,
                              aIter1);
            }
        }
    }
    // ---- the message kit + the send ----
    char acMsg[0x2080];           // local_448[1040]
    CtorCMsgInvadeWarning(acMsg);
    uint64_t uVar12 = InitCMsgInvadeWarning1(
        acMsg, uNow, aMapPos[0], uX, uY);
    if ((char)uVar12 != 0) {
        ((void (*)(void*, uint32_t,
                   void*))pVt[8 / 8])(
            pObj, uUser, acMsg);
    }
    DtorCMsgInvadeWarning(acMsg);
    return 1;
}

// ---- the seam defaults ----
static void* DefErRange(void* pM, void* pO, void* pF,
                        void* pL) {
    return NestedErRangeB(pM, pO, pF, pL);
}
void* (*g_fnInvEraseRange)(void*, void*, void*,
    void*) = DefErRange;
static void* DefPopOne(void* pV, void* pO, void* pI) {
    return NestedErOneB(pV, pO, pI);
}
void* (*g_fnInvPopOne)(void*, void*, void*) =
    DefPopOne;
static void* DefFindT(void*, void*, uint32_t*) {
    return 0;
}
void* (*g_fnInvFindTarget)(void*, void*,
    uint32_t*) = DefFindT;
static void DefListCtor(void*) {}
void (*g_fnInvListCtor)(void*) = DefListCtor;
static void* DefListIns(void*, void*, void*) {
    return 0;
}
void* (*g_fnInvListInsert)(void*, void*,
    void*) = DefListIns;
static void DefShpCopy(void*, int64_t) {}
void (*g_fnInvShpCopy)(void*, int64_t) =
    DefShpCopy;
static void* DefBox400(void*, uint32_t, void*) {
    return 0;
}
void* (*g_fnInvBox400)(void*, uint32_t,
    void*) = DefBox400;
static void DefMapIns(void*, void*, void*) {}
void (*g_fnInvMapInsert)(void*, void*,
    void*) = DefMapIns;
static void DefListDtor(void*) {}
void (*g_fnInvListDtor)(void*) = DefListDtor;
static void DefOpDel(void*) {}
void (*g_fnInvOpDelete)(void*) = DefOpDel;
static void DefLogErr(const char*) {}
void (*g_fnInvLogError)(const char*) =
    DefLogErr;
static bool DefCreate(void*, void*, uint16_t) {
    return false;
}
bool (*g_fnInvCMsgCreate)(void*, void*,
    uint16_t) = DefCreate;
void* g_pvD89CMsgInvadeVft = nullptr;

}  // namespace syndicate
