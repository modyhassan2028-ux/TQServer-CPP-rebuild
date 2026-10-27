// D94 — CSyndicateLogic wave 4 (OnFlowerChange +0x190,
// the funds move +0x198, the invite gate +0x1a0).
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x60];
static void* apLogicVt[160];
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

static int s_nFl[4], s_nAdd, s_nLog, s_nInvite;
static char s_acLog[160]; static int64_t s_lFunds,
    s_lAdded;
static uint32_t s_uVt1f8, s_uInvUser;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(apLogicVt, 0, sizeof(apLogicVt));
    memset(apBoxVt, 0, sizeof(apBoxVt));
    BuildMap(apLogMap, abLogHead, abLogNode,
             abLogAnchor, 5, abRecBox);
    apBox[0] = apBoxVt;
    *(void**)(abLogic + 0) = apLogicVt;
    *(void**)(abLogic + 8) = apBox;
    *(void**)(abLogic + 0x10) = (void*)0x22;
    *(void**)(abLogic + 0x18) = apLogMap;
    s_nFl[0] = s_nFl[1] = s_nFl[2] = s_nFl[3] = 0;
    s_nAdd = s_nLog = s_nInvite = 0;
    s_acLog[0] = 0; s_lFunds = 0; s_lAdded = 0;
    s_uVt1f8 = 0x77; s_uInvUser = 0;
    g_fnLgFind = [](void*, uint32_t) -> int64_t {
        return 0x30; };
    g_fnLgGetId = [](void*) -> uint64_t {
        return 0x8899; };
    g_fnFlowerA = [](void*, int32_t, uint64_t,
                     uint64_t) -> void* {
        s_nFl[0]++; return (void*)0x20100; };
    g_fnFlowerB = [](void*, int32_t, uint64_t,
                     uint64_t) -> void* {
        s_nFl[1]++; return (void*)0x21100; };
    g_fnFlowerC = [](void*, int32_t, uint64_t,
                     uint64_t) -> void* {
        s_nFl[2]++; return (void*)0x22100; };
    g_fnFlowerD = [](void*, int32_t, uint64_t,
                     uint64_t) -> void* {
        s_nFl[3]++; return (void*)0x23100; };
    g_fnLgGetFunds = [](void*) -> int64_t {
        return s_lFunds; };
    g_fnLgAddFunds = [](void*, int64_t l) {
        s_nAdd++; s_lAdded = l; };
    g_fnInviteB210 = [](void*, uint32_t u,
                        void*) -> uint64_t {
        s_nInvite++; s_uInvUser = u; return 0x99; };
    g_fnT1LogError = [](const char* pc) {
        s_nLog++;
        strncpy(s_acLog, pc ? pc : "?", 159); };
    g_fnA84GetSynId2 = [](void*)
        -> uint64_t { return 0x8899; };
    g_fnRecIsLeader = [](void*) -> char { return 1; };
    apBoxVt[0x1f8 / 8] = (void*)+[]() -> uint64_t {
        return s_uVt1f8; };
}

int main() {
    // ---- S1: OnFlowerChange — the vt gate ----
    Reset();
    s_uVt1f8 = 0;
    assert(pL->OnFlowerChange(5, 0, 1, 2) == 1);
    // the league find fails
    s_uVt1f8 = 0x77; g_fnLgFind =
        [](void*, uint32_t) -> int64_t { return 0; };
    assert(pL->OnFlowerChange(5, 0, 1, 2) == 0);
    assert(strstr(s_acLog, "OnFlowerChange") != 0);
    // the rank mismatch
    Reset(); g_fnLgGetId = [](void*) -> uint64_t {
        return 0x1111; };
    assert(pL->OnFlowerChange(5, 0, 1, 2) == 0);
    // the four flower types + the bad type
    Reset();
    // CONCAT71: (ret & ~0xff) | 1
    assert(pL->OnFlowerChange(5, 0, 1, 2) == 0x20101);
    assert(pL->OnFlowerChange(5, 1, 1, 2) == 0x21101);
    assert(pL->OnFlowerChange(5, 2, 1, 2) == 0x22101);
    assert(pL->OnFlowerChange(5, 3, 1, 2) == 0x23101);
    assert(s_nFl[0] == 1 && s_nFl[1] == 1 &&
           s_nFl[2] == 1 && s_nFl[3] == 1);
    assert(pL->OnFlowerChange(5, 9, 1, 2) == 0);
    assert(strstr(s_acLog, "SetFlower error") != 0);
    // ---- S2: the funds move ----
    Reset();
    assert(pL->Slot198MoveFunds(0, 3, 5) == 0 &&
           s_nLog >= 1);
    assert(pL->Slot198MoveFunds(5, 3, 0) == 0);
    assert(pL->Slot198MoveFunds(5, 0, 5) == 0);
    assert(pL->Slot198MoveFunds(5, 3, 9999) == 0);
    s_lFunds = 20000;   // the league has funds >= amt
    assert(pL->Slot198MoveFunds(5, 3, 10000) == 1);
    assert(s_nAdd == 2 && s_lAdded == 10000);
    s_lFunds = 5000;
    assert(pL->Slot198MoveFunds(5, 3, 10000) == 0);
    // not a leader
    g_fnRecIsLeader = [](void*) -> char { return 0; };
    s_lFunds = 0;
    assert(pL->Slot198MoveFunds(5, 3, 10000) == 0);
    // same target
    g_fnRecIsLeader = [](void*) -> char { return 1; };
    assert(pL->Slot198MoveFunds(5, 0x8899, 10000) == 0);
    // the dest find fails
    g_fnA84GetSynId2 = [](void*) -> uint64_t {
        return 0x1234; };
    g_fnLgFind = [](void*, uint32_t u) -> int64_t {
        return u == 3 ? 0x30 : 0; };
    assert(pL->Slot198MoveFunds(5, 3, 10000) == 0);
    // ---- S3: the invite gate ----
    Reset();
    assert(pL->Slot1a0InviteGate(0, 5) == 0);
    assert(pL->Slot1a0InviteGate(5, 0) == 0);
    assert(pL->Slot1a0InviteGate(5, 9) == 0); // no rec
    assert(pL->Slot1a0InviteGate(5, 5) == 0x99);
    assert(s_nInvite == 1 && s_uInvUser == 5);
    g_fnRecIsLeader = [](void*) -> char { return 0; };
    assert(pL->Slot1a0InviteGate(5, 5) == 0);
    g_fnRecIsLeader = [](void*) -> char { return 1; };
    g_fnA84GetSynId2 = [](void*) -> uint64_t {
        return 0; };
    assert(pL->Slot1a0InviteGate(5, 5) == 0);
    assert(s_nLog >= 1);
    g_fnLgFind = [](void*, uint32_t) -> int64_t {
        return 0; };
    Reset(); g_fnLgFind =
        [](void*, uint32_t) -> int64_t { return 0; };
    assert(pL->Slot1a0InviteGate(5, 5) == 0);
    puts("SYNDICATE_D94_OK: the logic table wave 4");
    return 0;
}
