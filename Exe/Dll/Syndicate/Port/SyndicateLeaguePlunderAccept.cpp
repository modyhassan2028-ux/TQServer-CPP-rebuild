// ============================================================================
// SyndicateLeaguePlunderAccept.cpp — unit D73: the two
// plunder-war ACCEPT handlers, ported verbatim from the
// recovered v6159 Syndicate.dll (FUN_141765920 /
// FUN_141765d60). The map iterator dance mirrors D70's
// RAW-verified kit.
// ============================================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderAccept.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include <cstring>

namespace syndicate {

char     (*g_fnPwaWarOpenGate)(void*);
void     (*g_fnPwaTalkSend)(void*, int32_t, const char*);
char     (*g_fnPwaAliveGate)(void*, int32_t);
int32_t  (*g_fnPwaGetUserLeague)(void*, int32_t);
uint32_t (*g_fnPwaGetUnionKey)(void*, int32_t, int32_t);
char     (*g_fnPwaGetMapInfo)(void*, int32_t, void*, void*, void*);
char     (*g_fnPwaCheckMapTransmit)(void*, int32_t, uint32_t,
                                    uint32_t, uint64_t);
int32_t  (*g_fnPwaGetUserState)(void*, int32_t);
void     (*g_fnPwaSetUserState)(void*, int32_t, int32_t);
char     (*g_fnPwaEnterLocalMap)(void*, int32_t, uint32_t, uint64_t);
uint32_t (*g_fnPwaGetUserLeague2)(void*, int32_t);
char     (*g_fnPwaCheckEnterOs)(void*, int32_t);
char     (*g_fnPwaCheckCanEnter)(void*, int32_t);
char     (*g_fnPwaEnterOsLeague)(void*, int32_t, uint32_t);
void     (*g_fnPwaTeleport)(void*, int32_t, uint32_t, uint32_t,
                            uint64_t, uint32_t);
char     (*g_fnPwaWarReplyGate)(void*, int32_t);

static inline void*  RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}
static inline uint32_t RdU32(void* p, size_t off) {
    return *(uint32_t*)((char*)p + off);
}
static inline uint64_t RdU64(void* p, size_t off) {
    return *(uint64_t*)((char*)p + off);
}

// the STR_DIE / STR_MAP_NOT_TRANSMIT / STR_USER_CAN_NOT_
// ENTER_OS talk — theInstance() + GetStr + vt+0x18.
static void TalkStr(char* pc, int32_t nUser, const char* pszKey) {
    g_fnPwaTalkSend(RdP(pc, 8), nUser,
        (const char*)g_fnStringMgrGetStr(
            g_fnStringMgrInstance(), pszKey));
}

// FUN_141765920 — the PLUNDERING side
bool UserAcceptPlunderWarInvite(void* pMgr, int32_t nUser) {
    char* pc = (char*)pMgr;
    if (nUser == 0) return false;
    if (*(int32_t*)(pc + 0x35c) != 2) return false;
    void* pLogic = RdP(pc, 8);
    if (g_fnPwaWarOpenGate(pLogic) == 0) {
        TalkStr(pc, nUser, "STR_DIE");
        return false;
    }
    if (g_fnPwaAliveGate(pLogic, nUser) == 0) return false;
    int32_t nLeague = g_fnPwaGetUserLeague(pLogic, nUser);
    if (nLeague == 0) return false;
    uint32_t uKey = g_fnPwaGetUnionKey(pLogic, nUser, nLeague);
    // lower_bound into mgr+0x370 (FUN_141760e40)
    uint64_t aIter[2] = { 0, 0 };
    g_fnLbrMapLowerBound(pc + 0x370, aIter, &uKey);
    void* pItProxy = (void*)(uintptr_t)aIter[0];
    void* pItNode  = (void*)(uintptr_t)aIter[1];
    if (RdP(pc, 0x370) == nullptr || RdP(pc, 0x370) != pItProxy)
        g_fnPwsInvalid();
    if (RdP(pc, 0x3a0) == pItNode) return false;   // absent
    if (pItProxy == nullptr) g_fnPwsInvalid();
    else {
        void* pCont = RdP(pItProxy, 0);
        if (pItNode == RdP(pCont, 0x30)) g_fnPwsInvalid();
    }
    char* pNode = (char*)pItNode;
    if (RdU64(pNode, 0x58) == 0) return false;     // size gate
    void* pFirst = RdP(RdP(pNode, 0x50), 0);       // head->left
    void* pProxyIn = RdP(pNode, 0x20);
    if (pProxyIn == nullptr) g_fnPwsInvalid();
    else {
        void* pCont2 = RdP(pProxyIn, 0);
        if (pFirst == RdP(pCont2, 0x30)) g_fnPwsInvalid();
    }
    uint32_t uLeague = RdU32(pFirst, 0x18) / 1000000;
    if (uLeague == 0) return false;
    // the map-info res block
    uint32_t aRes20[2] = { 0, 0 };
    uint16_t aRes18[4] = { 0, 0, 0, 0 };
    uint16_t aRes10[4] = { 0, 0, 0, 0 };
    if (g_fnPwaGetMapInfo(pLogic, nUser, aRes20, aRes18,
                          aRes10) == 0)
        return false;
    uint64_t uPacked = *(uint64_t*)aRes10;         // the RAW uVar6
    uint32_t uPosHi  = (uint32_t)(uPacked >> 0x20); // uVar11
    if (g_fnPwaCheckMapTransmit(pLogic, nUser, aRes20[0],
                                aRes18[0], uPacked) == 0) {
        TalkStr(pc, nUser, "STR_MAP_NOT_TRANSMIT");
        return false;
    }
    if (g_fnPwaGetUserState(pLogic, nUser) != 9)
        g_fnPwaSetUserState(pLogic, nUser, 9);
    if (g_fnPwsGetMyLeague(pLogic) == uLeague) {
        // the local map enter
        if (g_fnPwaEnterLocalMap(pLogic, nUser,
                RdU32(pc, 0x360), RdU64(pc, 0x364)) == 0) {
            g_fnPwsLogErr(
              "UserAcceptPlunderWarInvite error point", 0);
            return false;
        }
        return true;
    }
    if (g_fnPwaGetUserLeague2(pLogic, nUser) == uLeague) {
        if (g_fnPwaCheckEnterOs(pLogic, nUser) == 0) {
            g_fnPwsLogErr("OS-enter gate log", 0);
        } else {
            g_fnPwaTeleport(pLogic, nUser, uLeague,
                RdU32(pc, 0x360),
                (uint64_t)RdU32(pc, 0x364) |
                ((uint64_t)uPosHi << 0x20),
                RdU32(pc, 0x368));
        }
        return true;
    }
    if (g_fnPwaCheckCanEnter(pLogic, nUser) == 0) {
        TalkStr(pc, nUser, "STR_USER_CAN_NOT_ENTER_OS");
        return false;
    }
    if (g_fnPwaEnterOsLeague(pLogic, nUser, uLeague) == 0) {
        g_fnPwsLogErr("OS-enter gate log", 0);
    }
    g_fnPwaTeleport(pLogic, nUser, uLeague,
        RdU32(pc, 0x360),
        (uint64_t)RdU32(pc, 0x364) |
            ((uint64_t)uPosHi << 0x20),
        RdU32(pc, 0x368));
    return true;
}

// FUN_141765d60 — the PLUNDERED side
bool UserAcceptPlunderWarInvitePlundered(void* pMgr,
                                          int32_t nUser) {
    char* pc = (char*)pMgr;
    if (nUser == 0) return false;
    if (*(int32_t*)(pc + 0x35c) != 2) return false;
    void* pLogic = RdP(pc, 8);
    if (g_fnPwaWarOpenGate(pLogic) == 0) {
        TalkStr(pc, nUser, "STR_DIE");
        return false;
    }
    int32_t nLeague = g_fnPwaGetUserLeague(pLogic, nUser);
    if (nLeague == 0) return false;
    uint32_t uKey = g_fnPwaGetUnionKey(pLogic, nUser, nLeague);
    // lower_bound into mgr+0x3b0
    uint64_t aIter[2] = { 0, 0 };
    g_fnLbrMapLowerBound(pc + 0x3b0, aIter, &uKey);
    void* pItProxy = (void*)(uintptr_t)aIter[0];
    void* pItNode  = (void*)(uintptr_t)aIter[1];
    if (RdP(pc, 0x3b0) == nullptr || RdP(pc, 0x3b0) != pItProxy)
        g_fnPwsInvalid();
    if (RdP(pc, 0x3e0) == pItNode) return false;   // absent
    if (pItProxy == nullptr) g_fnPwsInvalid();
    else {
        void* pCont = RdP(pItProxy, 0);
        if (pItNode == RdP(pCont, 0x30)) g_fnPwsInvalid();
    }
    // NO inner-map gate here — straight to the res block
    uint32_t aRes20[2] = { 0, 0 };
    uint16_t aRes18[4] = { 0, 0, 0, 0 };
    uint16_t aRes10[4] = { 0, 0, 0, 0 };
    if (g_fnPwaGetMapInfo(pLogic, nUser, aRes20, aRes18,
                          aRes10) == 0)
        return false;
    uint64_t uPacked = *(uint64_t*)aRes10;
    uint32_t uPosHi  = (uint32_t)(uPacked >> 0x20);
    if (g_fnPwaCheckMapTransmit(pLogic, nUser, aRes20[0],
                                aRes18[0], uPacked) == 0) {
        TalkStr(pc, nUser, "STR_MAP_NOT_TRANSMIT");
        return false;
    }
    if (g_fnPwaGetUserState(pLogic, nUser) != 9)
        g_fnPwaSetUserState(pLogic, nUser, 9);
    // the war-reply gate — RAW 65d60 splits here
    if (g_fnPwaWarReplyGate(pLogic, nUser) == 0) {
        // the local map enter path
        if (g_fnPwaEnterLocalMap(pLogic, nUser,
                RdU32(pc, 0x360), RdU64(pc, 0x364)) == 0) {
            g_fnPwsLogErr(
              "UserAcceptPlunderWarInvite error point", 0);
            return false;
        }
        return true;
    }
    if (g_fnPwaCheckEnterOs(pLogic, nUser) != 0) {
        uint32_t uL2 = g_fnPwaGetUserLeague2(pLogic, nUser);
        g_fnPwaTeleport(pLogic, nUser, uL2,
            RdU32(pc, 0x360),
            (uint64_t)RdU32(pc, 0x364) |
                ((uint64_t)uPosHi << 0x20),
            RdU32(pc, 0x368));
    }
    return true;                                   // unconditional
}

}  // namespace syndicate
