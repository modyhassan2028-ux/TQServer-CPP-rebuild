// ============================================================================
// modules/syndicate/src/league.h — the ORIGINAL file (recovered from
// the binary literals: modules/syndicate/src/league.cpp, 4 CHECKF
// references). Ported unit D89: CLeagueMgr::FlyToInvadeWarning
// (FUN_141774500) + the CMsgInvadeWarning kit (0x14183bf30).
//
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_141774500 @ 141774500 — the fly-to-invade warning flow:
//     the +8 mgr-vt state gate (slot 0x288, this-only — verified
//     in RAW: no edx at the call), the map+pos fetch (slot 0x498,
//     THREE out ptrs the decompiler kept), the transmit checks
//     (slot 0x570, called TWICE: the user's map then the target's
//     stored map at node+0x20/x24/y26), the point check (slot 0x4c0
//     with the packed x|y), the talks via slot 0x18
//     (STR_DIE / STR_MAP_NOT_TRANSMIT / STR_TARGET_MAP_NOT_TRANSMIT),
//     the error literal
//     "CLeagueMgr::FlyToInvadeWarning error point Map[u%],
//      posX[%u], posY[%u]",
//     the target-map find at +0x228 (seam 141760a20), the
//     user-map find at +0x2b0 (seam 141760af0 = g_fnTreeFindAF0),
//     the insert path (list ctor/insert, the shp copies, the
//     box-400, the map insert) vs the found path (value assign +
//     the >5 list pop via NestedErOneB), and the CMsg kit:
//     ctor 1417d50f0, Init1 1417d5250 (the 0xc1c/0x22/1 header +
//     mapId@+0xa, x*10000+y@+6, time@+0xe), the send via vt+8,
//     the dtor 1417d5140.
//
// SEAMS (documented, test-wired): g_fnInvFindTarget (141760a20),
//   g_fnInvListCtor (14176f530), g_fnInvListInsert (141761330),
//   g_fnInvShpCopy (14176dff0), g_fnInvBox400 (141770400),
//   g_fnInvMapInsert (141773cb0), g_fnInvListDtor (14176a1a0),
//   g_fnInvOpDelete, g_fnInvLogError, g_fnInvCMsgCreate,
//   g_pvD89CMsgInvadeVft (0x14183bf30).
// REUSED: g_fnTreeFindAF0 (141760af0), NestedErOneB/NestedErRangeB
//   (1417614e0/141762db0), g_fnSupTimeGet, g_fnStringMgrInstance/
//   g_fnStringMgrGetStr, g_fnCMsgInitThunk, g_fnLeagueInvalid,
//   g_pvD87CMsgVft (tq::CMsg::vftable).
// ============================================================================
#ifndef MODULES_SYNDICATE_SRC_LEAGUE_H
#define MODULES_SYNDICATE_SRC_LEAGUE_H

#include <cstdint>

namespace syndicate {

// ---- the seams ----
extern void* (*g_fnInvFindTarget)(void* pMap,
    void* pOutIter, uint32_t* pKey);          // 141760a20
extern void (*g_fnInvListCtor)(void* pList);  // 14176f530
extern void* (*g_fnInvListInsert)(void* pMap,
    void* pPair, void* pTime);                // 141761330
// (returns the inserted node — the RAW's rax slot
//  the decompiler lost into local_538)
extern void (*g_fnInvShpCopy)(void* pDst,
    int64_t lSrc);                            // 14176dff0
extern void* (*g_fnInvBox400)(void* pBox,
    uint32_t uUser, void* pShp);              // 141770400
extern void (*g_fnInvMapInsert)(void* pMap,
    void* pIter, void* pVal);                 // 141773cb0
extern void (*g_fnInvListDtor)(void* pList);  // 14176a1a0
extern void (*g_fnInvOpDelete)(void* p);      // operator_delete
extern void (*g_fnInvLogError)(const char*);  // the D89 literal
extern bool (*g_fnInvCMsgCreate)(void* pMsg,
    void* pSrc, uint16_t uType);              // tq::CMsg::Create
extern void* g_pvD89CMsgInvadeVft;            // 0x14183bf30
// the nested-erase hooks (defaults = the real ported
// 141762db0/1417614e0 bodies; test-wireable)
extern void* (*g_fnInvEraseRange)(void* pMap,
    void* pOut, void* pFirst, void* pLast);   // 141762db0
extern void* (*g_fnInvPopOne)(void* pVal,
    void* pOut, void* pIter);                // 1417614e0

class CLeagueMgr {
public:
    // ---- the body (FUN_141774500) ----
    uint8_t FlyToInvadeWarning(int64_t lThis,
        uint32_t uUser, uint32_t uTarget);
};

// ---- the CMsgInvadeWarning kit (verbatim) ----
void* CtorCMsgInvadeWarning(void* pMsg);      // 1417d50f0
void DtorCMsgInvadeWarning(void* pMsg);       // 1417d5140
uint64_t InitCMsgInvadeWarning1(void* pMsg,   // 1417d5250
    uint32_t uTime, uint32_t uMapId,
    uint16_t uX, uint16_t uY);
bool CreateCheckCMsgInvadeWarning(            // 1417d5170
    void* pMsg, void* pSrc, uint16_t uType);
void* DeletingDtorCMsgInvadeWarning(         // 1417d52f0
    void* pMsg, uint8_t bDelete);

}  // namespace syndicate

#endif  // MODULES_SYNDICATE_SRC_LEAGUE_H
