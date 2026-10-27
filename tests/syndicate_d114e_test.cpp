// D114e unit test — vtable closure: the two giant CLIENT
// entries wired as class slots:
// Slot680 = 1417c2470 (SignUpPlunderWarFromClient, D78)
// Slot6e0 = 1417c3230 (PublishSupportTokenFromClient, D80)
// Proves the delegation: this array, arg order and the
// gate chain reached through the class methods.
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include "modules/syndicate/src/syndicatelogic.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderSignup.h"
#include "modules/syndicate/src/SyndicateLeagueSupportPublish.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderList.h"  // g_fnSplWarState
using namespace syndicate;

static void* s_pLogic[0x100];
static void* s_vtBox[0x120];
static char s_abBox[0x100];
static void* s_pBox = (void*)s_abBox;
static void* s_host = (void*)0x1234;

// gate stubs (shared by both helpers)
static char s_cWarState = 0;         // vt+0x278
static int s_nWarState = 0;
static int s_nMgrGate = 0;           // 14174ebd0
static int s_iMgrGate = 0;           // return value
static uint32_t s_uUserLeague = 0;   // vt+0x4a8 path
static int s_nUserLeague = 0;
static void* s_pLeague = 0;          // 1417630d0
static int s_nFindLeague = 0;
static uint32_t s_uMemberKey = 0;
static int s_nMemberKey = 0;
static char s_cAlready = 0;          // 141766a70

static char TSupWarState(void* p) {
    ++s_nWarState; (void)p;
    return s_cWarState;
}
static char TSplMgrGate(void* p) {
    ++s_nMgrGate; (void)p;
    return (char)s_iMgrGate;
}
static uint32_t TSupUserLeague(void* p, uint32_t u) {
    ++s_nUserLeague; (void)p; (void)u;
    return s_uUserLeague;
}
static void* TSupFindLeague(void* p, uint32_t u) {
    ++s_nFindLeague; (void)p; (void)u; return s_pLeague;
}
static uint32_t TSupMemberKey(void* p, uint32_t u,
                              uint32_t l) {
    ++s_nMemberKey; (void)p; (void)u; (void)l;
    return s_uMemberKey;
}
static char TAlready(void* p, uint32_t u) {
    (void)p; (void)u; return s_cAlready;
}

static void Wire() {
    memset(s_vtBox, 0, sizeof s_vtBox);
    memset(s_pLogic, 0, sizeof s_pLogic);
    s_pLogic[1] = s_pBox;
    s_pLogic[10] = s_host;
    *(void**)s_pBox = s_vtBox;
    s_cWarState = 0; s_nWarState = 0;
    s_iMgrGate = 0; s_nMgrGate = 0;
    s_uUserLeague = 0; s_nUserLeague = 0;
    s_pLeague = 0; s_nFindLeague = 0;
    s_uMemberKey = 0; s_nMemberKey = 0;
    s_cAlready = 0;
    // the helper seams (both helpers share the gate set)
    g_fnSupWarState = TSupWarState;
    g_fnSplMgrGate = TSplMgrGate;
    g_fnSupUserLeague = TSupUserLeague;
    g_fnSupFindLeague = TSupFindLeague;
    g_fnSupMemberKey = TSupMemberKey;
    g_fnSplAlreadySigned = TAlready;
    g_fnSplFindLeague = TSupFindLeague;   // the Publish helper's own league seam
}

int main() {
    Wire();
    CSyndicateLogic* pL = (CSyndicateLogic*)s_pLogic;
    uint32_t aT[10] = { 7, 8, 9, 0 };
    printf("D114e start\n");

    // ==== S1: Slot680 (1417c2470) delegation ====
    {
        // arg gates: no seams touched
        assert(pL->Slot680(0, 3, aT, 1, 5) == 0);
        assert(pL->Slot680(5, 0, aT, 1, 5) == 0);
        assert(pL->Slot680(5, 11, aT, 1, 5) == 0);
        assert(s_nWarState == 0 && s_nMgrGate == 0);
        // war-state gate (vt+0x278 == 0 required): nonzero -> stop
        s_cWarState = 1;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        assert(s_nWarState == 1 && s_nMgrGate == 0);
        // mgr gate (14174ebd0 == 0 required)
        s_cWarState = 0; s_iMgrGate = 1;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        assert(s_nWarState == 2 && s_nMgrGate == 1);
        // user league (vt+0x4a8 != 0 required)
        s_iMgrGate = 0;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        assert(s_nUserLeague == 1 && s_nFindLeague == 0);
        // league find (1417630d0 != 0 required)
        s_uUserLeague = 0x99;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        assert(s_nFindLeague == 1 && s_nMemberKey == 0);
        // member key (vt+0x568 != 0 required)
        s_pLeague = (void*)0x900;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        assert(s_nMemberKey == 1);
        // already signed (141766a70 == false required)
        s_uMemberKey = 0x42; s_cAlready = 1;
        assert(pL->Slot680(5, 3, aT, 1, 5) == 0);
        printf("S1 ok (680 delegation)\n");
    }

    // ==== S2: Slot6e0 (1417c3230) delegation ====
    {
        Wire();
        g_fnSplWarState = TSupWarState;
        // arg gates
        assert(pL->Slot6e0(0, 3, aT, 1, 5) == 0);
        assert(pL->Slot6e0(5, 0, aT, 1, 5) == 0);
        assert(pL->Slot6e0(5, 11, aT, 1, 5) == 0);
        assert(s_nWarState == 0 && s_nMgrGate == 0);
        // war-state gate
        s_cWarState = 1;
        assert(pL->Slot6e0(5, 3, aT, 1, 5) == 0);
        assert(s_nWarState == 1 && s_nMgrGate == 0);
        // mgr gate: ==1 || ==2 required; returning 0 ->
        // called TWICE (the RAW double call)
        s_cWarState = 0; s_iMgrGate = 0;
        assert(pL->Slot6e0(5, 3, aT, 1, 5) == 0);
        assert(s_nWarState == 2 && s_nMgrGate == 2);
        // pass gate (==1) on the FIRST call
        s_iMgrGate = 1;
        assert(pL->Slot6e0(5, 3, aT, 1, 5) == 0);
        assert(s_nMgrGate == 3 && s_nUserLeague == 1);
        // league find
        s_uUserLeague = 0x99;
        assert(pL->Slot6e0(5, 3, aT, 1, 5) == 0);
        assert(s_nFindLeague == 1 && s_nMemberKey == 0);
        // member key
        s_pLeague = (void*)0x900;
        assert(pL->Slot6e0(5, 3, aT, 1, 5) == 0);
        assert(s_nMemberKey == 1);
        printf("S2 ok (6e0 delegation)\n");
    }

    printf("D114e ALL-OK\n");
    return 0;
}
