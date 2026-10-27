// D95 — CSyndicateLogic wave 5 — the diplomacy bodies
// (+0x1a8..+0x1c8): set/clear antagonize, clear ally,
// the two relation gates.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x60];
static void* apBoxVt[160];
static void* apBox[1];
static uint8_t abRecBox[0x20];
static uint8_t abLogNode[0x40], abLogHead[0x40],
    abLogAnchor[0x40];
static void* apLogMap[8];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;

static void BuildMap(void** apMap, uint8_t* pHead,
                     uint8_t* pNode, uint8_t* pAnchor,
                     uint32_t uKey, void* pVal) {
    memset(pNode, 0, 0x40);
    *(void**)pNode = pHead;
    *(void**)(pNode + 0x10) = pHead;
    *(void**)(pNode + 8) = pHead;
    *(uint32_t*)(pNode + 0x18) = uKey;
    ((char*)pNode)[0x29] = 0;
    *(void**)(pNode + 0x20) = pVal;
    memset(pHead, 0, 0x40);
    ((char*)pHead)[0x29] = 1;
    *(void**)(pHead + 8) = pNode;
    memset(pAnchor, 0, 0x40);
    *(void**)pAnchor = pAnchor;
    *(void**)(pAnchor + 0x30) = pHead;
    apMap[0] = pAnchor; apMap[6] = pHead;
}

// the capture state
static int s_nTip, s_nBcast, s_nLog, s_nRefresh,
    s_nSetEnemy, s_nSetAlly;
static uint32_t s_uTipUser, s_uBcastId, s_uEnemySlot,
    s_uAllySlot;
static uint32_t s_auEnemyCall[4], s_auAllyCall[4];
static char s_acStr[64];
static char s_bLeader, s_bAlly, s_bAntag;
static uint32_t s_uSlotRet;
static char s_acBcast[128];

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(apBoxVt, 0, sizeof(apBoxVt));
    BuildMap(apLogMap, abLogHead, abLogNode,
             abLogAnchor, 5, abRecBox);
    apBox[0] = apBoxVt;
    *(void**)(abLogic + 8) = apBox;
    *(void**)(abLogic + 0x10) = (void*)0x22;
    *(void**)(abLogic + 0x18) = apLogMap;
    s_nTip = s_nBcast = s_nLog = s_nRefresh = 0;
    s_nSetEnemy = s_nSetAlly = 0;
    s_uTipUser = s_uBcastId = 0;
    s_acStr[0] = 0; s_acBcast[0] = 0;
    s_bLeader = 1; s_bAlly = 0; s_bAntag = 0;
    s_uSlotRet = 2;
    g_fnT1LogError = [](const char*) { s_nLog++; };
    g_fnRecIsLeader = [](void*) -> char {
        return s_bLeader; };
    g_fnA84GetSynId2 = [](void*) -> uint64_t {
        return 0x50; };
    g_fnLgFind = [](void*, uint32_t u) -> int64_t {
        return u == 0x50 ? 0x30 : u == 0x60 ? 0x31 : 0;
    };
    g_fnLgFindByName = [](void*, const char* n)
        -> int64_t { return strcmp(n, "TGT") == 0
            ? 0x31 : 0; };
    g_fnLgGetId = [](void* p) -> uint64_t {
        return p == (void*)0x31 ? 0x60 : 0x1234; };
    g_fnLgIsAlly = [](void*, uint32_t) -> char {
        return s_bAlly; };
    g_fnLgIsAntag = [](void*, uint32_t) -> char {
        return s_bAntag; };
    g_fnLgEnemyCnt = [](void*) -> int32_t {
        return 0; };
    g_fnLgEnemyMax = [](void*) -> int32_t {
        return 5; };
    g_fnLgAddEnemySlot = [](void*, uint32_t)
        -> uint32_t { return s_uSlotRet; };
    g_fnLgSetEnemy = [](void*, uint32_t s,
                        uint32_t v) {
        s_auEnemyCall[s_nSetEnemy] = s;
        s_auEnemyCall[s_nSetEnemy + 1] = v;
        s_nSetEnemy += 2; };
    g_fnLgFindAllySlot = [](void*, int32_t)
        -> uint32_t { return s_uSlotRet; };
    g_fnLgSetAlly = [](void*, uint32_t s, uint32_t v) {
        s_auAllyCall[s_nSetAlly] = s;
        s_auAllyCall[s_nSetAlly + 1] = v;
        s_nSetAlly += 2; };
    g_fnLgFindAntagSlot = [](void*, int32_t)
        -> uint32_t { return s_uSlotRet; };
    g_fnLgRefresh = [](void*) -> void* {
        s_nRefresh++; return (void*)"tgtnm"; };
    g_fnRecGetName = [](void*) -> uint64_t {
        return 0x7777; };
    g_fnRecGetMemberNo = [](void*) -> int64_t {
        return 42; };
    g_fnBoxVt1d8 = [](void*, uint32_t) -> uint64_t {
        return 0x99; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                             const char* k) -> void* {
        strncpy(s_acStr, k, 63);
        return (void*)(const char*)s_acStr; };
    apBoxVt[0x18 / 8] = (void*)+[](
        void*, uint32_t u, const void* pv)
        -> uint64_t {
        s_nTip++; s_uTipUser = u;
        strncpy(s_acBcast, (const char*)pv, 127);
        return 0; };
    apBoxVt[0x88 / 8] = (void*)+[](
        void*, uint32_t u, const char* psz,
        uint64_t) -> uint64_t {
        s_nBcast++; s_uBcastId = u;
        strncpy(s_acBcast, psz, 127);
        return 0x300; };
}

int main() {
    // ---- S1: Slot1a8SetAntagonize — the gates ----
    Reset();
    assert(pL->Slot1a8SetAntagonize(0, "TGT") == 0 &&
           s_nLog >= 1);
    assert(pL->Slot1a8SetAntagonize(5, nullptr) == 0);
    s_bLeader = 0;
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 0);
    s_bLeader = 1;
    assert(pL->Slot1a8SetAntagonize(9, "TGT") == 0);
    // target name not found
    assert(pL->Slot1a8SetAntagonize(5, "NOPE") == 0);
    // ally already
    s_bAlly = 1;
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 0);
    assert(s_nTip == 1 && s_uTipUser == 5);
    assert(strstr(s_acBcast, "FRIENDLY") != 0);
    // antagonized already
    Reset(); s_bAntag = 1;
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 0);
    assert(strstr(s_acBcast, "ALREADY_SET") != 0);
    // over the enemy count
    Reset(); g_fnLgEnemyCnt = [](
        void*) -> int32_t { return 5; };
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 0);
    assert(strstr(s_acBcast, "OVER_ENEMY") != 0);
    // the enemy table full
    Reset(); s_uSlotRet = 0xffffffff;
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 0);
    assert(strstr(s_acBcast, "ANTAGONIZE_FULL") != 0);
    // ---- S2: the success path ----
    Reset();
    assert(pL->Slot1a8SetAntagonize(5, "TGT") == 1);
    assert(s_nSetEnemy == 2);   // the add + none more
    assert(s_auEnemyCall[0] == 2 &&
           s_auEnemyCall[1] == 0x60);
    assert(s_nRefresh == 1);    // the target refresh
    assert(s_nBcast == 2);      // both messages
    assert(s_uBcastId == 0x60); // to the target
    assert(strstr(s_acBcast, "TO_TARGET") != 0);
    // ---- S3: Slot1b0ClearAlly ----
    Reset();
    assert(pL->Slot1b0ClearAlly(5, nullptr) == 0 &&
           s_nLog >= 1);
    assert(pL->Slot1b0ClearAlly(5, "NOPE") == 0);
    s_uSlotRet = 0xffffffff;
    assert(pL->Slot1b0ClearAlly(5, "TGT") == 0);
    assert(strstr(s_acBcast, "STR_NOT_ALLY") != 0);
    Reset(); s_uSlotRet = 1;
    assert(pL->Slot1b0ClearAlly(5, "TGT") == 1);
    assert(s_nSetAlly == 4);   // mine + theirs
    assert(s_auAllyCall[0] == 1 && s_auAllyCall[1] == 0);
    assert(s_auAllyCall[2] == 1 && s_auAllyCall[3] == 0);
    assert(s_nBcast == 2);
    assert(strstr(s_acBcast, "CLEAR_ALLY") != 0);
    // ---- S4: Slot1b8ClearAntagonize ----
    Reset();
    assert(pL->Slot1b8ClearAntagonize(5, nullptr) ==
           0 && s_nLog >= 1);
    s_uSlotRet = 0xffffffff;
    assert(pL->Slot1b8ClearAntagonize(5, "TGT") == 0);
    assert(strstr(s_acBcast, "STR_NOT_ANTAGONIZE") != 0);
    Reset(); s_uSlotRet = 3;
    assert(pL->Slot1b8ClearAntagonize(5, "TGT") == 1);
    assert(s_nSetEnemy == 2);
    assert(s_auEnemyCall[0] == 3 &&
           s_auEnemyCall[1] == 0);
    assert(s_nBcast == 2);
    assert(strstr(s_acBcast, "TO_TARGET") != 0);
    // ---- S5: the two relation gates ----
    Reset();
    assert(pL->Slot1c0IsAllyGate(0, 1) == 0);
    assert(pL->Slot1c0IsAllyGate(1, 0) == 0);
    assert(pL->Slot1c0IsAllyGate(0x50, 1) == 0);
    s_bAlly = 1;
    assert(pL->Slot1c0IsAllyGate(0x50, 1) == 1);
    assert(pL->Slot1c8IsAntagGate(0x50, 1) == 0);
    s_bAntag = 1;
    assert(pL->Slot1c8IsAntagGate(0x50, 1) == 1);
    puts("SYNDICATE_D95_OK: the diplomacy wave");
    return 0;
}
