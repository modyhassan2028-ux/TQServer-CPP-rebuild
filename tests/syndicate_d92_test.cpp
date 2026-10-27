// D92 — the CSyndicateLogic table wave 2 (slots
// +0x0b0..+0x140) — the consolidated batch test.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

// ---- the fixture (the same real-map shape as d90) ----
static uint8_t abLogic[0x60];
static void* apLogicVt[160];
static void* apBoxVt[160];
static void* apBox[1];
static uint8_t abMember[0x20];
static uint8_t abRecBox[0x20];
static uint8_t abMemNode[0x40], abMemHead[0x40],
    abMemAnchor[0x40];
static void* apMemMap[8];
static uint8_t abMemMgr[0x40];
static uint8_t abLogNode[0x40], abLogHead[0x40],
    abLogAnchor[0x40];
static void* apLogMap[8];

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
    apMap[0] = pAnchor;
    apMap[6] = pHead;
}

// ---- the recording state ----
static int s_nKick, s_nSetA, s_nSetB, s_nSetC, s_nClr;
static int s_nRankA, s_nRankB, s_nUpd, s_nLeave;
static int s_nCtyPush, s_nFwdA, s_nFwdB, s_nFwdC;
static int s_nClearA, s_nClearB, s_nLgTest, s_nLgZ;
static uint64_t s_uRetX, s_uRetY, s_uRetZ, s_uRec;
static int s_nE8, s_nF0, s_nTalk, s_nLog;
static uint32_t s_uCtyOp;
static char s_acTalk[64];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(apLogicVt, 0, sizeof(apLogicVt));
    memset(apBoxVt, 0, sizeof(apBoxVt));
    BuildMap(apMemMap, abMemHead, abMemNode,
             abMemAnchor, 5, abMember);
    memset(abMemMgr, 0, sizeof(abMemMgr));
    *(void**)(abMemMgr + 8) = apMemMap;
    *(void**)(abMemMgr + 0x38) = apMemMap;
    BuildMap(apLogMap, abLogHead, abLogNode,
             abLogAnchor, 5, abRecBox);
    apBox[0] = apBoxVt;
    *(void**)(abLogic + 8) = apBox;
    *(void**)(abLogic + 0) = apLogicVt;
    *(void**)(abLogic + 0x10) = (void*)0x22;
    *(void**)(abLogic + 0x18) = apLogMap;
    *(void**)(abLogic + 0x50) = (void*)0x55;
    s_nKick = s_nSetA = s_nSetB = s_nSetC = 0;
    s_nClr = s_nRankA = s_nRankB = s_nUpd = 0;
    s_nLeave = s_nCtyPush = s_nFwdA = s_nFwdB = 0;
    s_nFwdC = s_nClearA = s_nClearB = 0;
    s_nLgTest = s_nLgZ = s_nE8 = s_nF0 = 0;
    s_nTalk = s_nLog = 0; s_uCtyOp = 0;
    s_uRetX = s_uRetY = s_uRetZ = s_uRec = 0;
    // the default seam binds
    g_fnLgFind = [](void*, uint32_t) -> int64_t {
        return 0x30; };
    g_fnLgFindB = [](void*, uint32_t) -> char {
        return 1; };
    g_fnLgClearA = [](void*) { s_nClearA++; };
    g_fnLgClearB = [](void*) { s_nClearB++; };
    g_fnLgRankUpd = [](void*, void*, void*, uint32_t)
        -> uint64_t { s_nUpd++; return 0x200; };
    g_fnCtyFind = [](void*, uint32_t) -> int64_t {
        return 0; };
    g_fnCtyPush = [](void*, uint32_t u, int32_t op,
                     int32_t) {
        s_nCtyPush++; s_uCtyOp = op; (void)u; };
    g_fnCtyFwdA = [](void*, uint32_t, int16_t, uint32_t)
        { s_nFwdA++; };
    g_fnCtyFwdB = [](void*, uint32_t, int32_t, uint32_t)
        { s_nFwdB++; };
    g_fnCtyFwdC = [](void*, uint32_t, int16_t, uint32_t)
        { s_nFwdC++; };
    g_fnRecKick = [](void*) { s_nKick++; };
    g_fnRecSetA = [](void*, int32_t) { s_nSetA++; };
    g_fnRecSetB = [](void*, int32_t) { s_nSetB++; };
    g_fnRecSetC = [](void*, int32_t) { s_nSetC++; };
    g_fnRecClr = [](void*) { s_nClr++; };
    g_fnRecGetX = [](void*, int32_t)
        -> uint64_t { return 0x77; };
    g_fnRecChk = [](void*, int32_t)
        -> uint64_t { return 1; };
    g_fnRecGetRank = [](void*)
        -> uint64_t { return 0x3de; };
    g_fnRecIsLeader = [](void*) -> char { return 0; };
    g_fnA84GetSynId2 = [](void*)
        -> uint64_t { return 0x8899; };
    g_fnRankSetA = [](void*, void*, int32_t) {
        s_nRankA++; };
    g_fnRankSetB = [](void*, void*, int32_t, uint32_t,
                      char) { s_nRankB++; };
    g_fnLgTest = [](void*, char) -> char {
        s_nLgTest++; return 1; };
    g_fnLgGetX = [](void*)
        -> uint64_t { return s_uRetX; };
    g_fnLgGetY = [](void*)
        -> uint64_t { return s_uRetY; };
    g_fnLgZ = [](void*, char)
        -> uint64_t { return s_uRetZ; };
    g_fnLeaveSyn = [](void*, void*, void*,
                     const char* pc, char, char, char)
        -> uint64_t {
        s_nLeave++;
        return strcmp(pc, "LeaveSyn") ? 0 : 0x11; };
    g_fnT1LogError = [](const char*) { s_nLog++; };
    g_fnStringMgrInstance =
        []() -> void* { return (void*)0x11; };
    g_fnStringMgrGetStr = [](void*, const char* pc)
        -> void* {
        return (void*)pc; };
    g_fnA84HasOldPos = [](void*) -> char {
        return 0; };
    g_fnA84GetOldId = [](void*) -> uint32_t {
        return 0; };
    g_fnT1IsConfirmed = [](void*) -> uint64_t {
        return 0; };
    apBoxVt[0x4a8 / 8] = (void*)+[](void*,
        uint32_t) -> uint32_t { return 7; };
    apBoxVt[0x328 / 8] = (void*)+[](void*,
        uint32_t) -> uint32_t { return 0x999; };
    apBoxVt[0x18 / 8] = (void*)+[](void*, uint32_t,
        const void* pc) -> uint64_t {
        strncpy(s_acTalk, (const char*)pc, 63);
        s_nTalk++; return 0x40; };
    apLogicVt[0xe8 / 8] = (void*)+[](void*,
        uint32_t, uint64_t, char) -> uint64_t {
        s_nE8++; return 0x700; };
    apLogicVt[0xf0 / 8] = (void*)+[](void*, uint32_t,
        int32_t) -> uint64_t {
        s_nF0++; return 0x300; };
}

int main() {
    // ---- S1: Slot0b0 the syn-id gate ----
    Reset();
    assert(pL->Slot0b0GetSynId(0) == 0 && s_nLog == 1);
    assert(pL->Slot0b0GetSynId(5) == 0x8899);
    g_fnLgFindB = [](void*, uint32_t) -> char {
        return 0; };
    Reset();
    g_fnLgFindB = [](void*, uint32_t) -> char {
        return 0; };
    assert(pL->Slot0b0GetSynId(5) == 0);
    // ---- S2: Slot0b8 the kick ----
    Reset();
    pL->Slot0b8RecKick(9);
    assert(s_nKick == 0);      // not found: silent
    pL->Slot0b8RecKick(5);
    assert(s_nKick == 1);
    // ---- S3: Slot0c0 rec-found: set + fwd ----
    Reset();
    pL->Slot0c0RecSet5(5, 3);
    assert(s_nSetA == 1 && s_nFwdA == 1);
    // rec NOT found + cty find 0: NO push, but the
    // fwd still fires (it is outside the if/else)
    pL->Slot0c0RecSet5(6, 3);
    assert(s_nCtyPush == 0 && s_nFwdA == 2);
    g_fnCtyFind = [](void*, uint32_t) -> int64_t {
        return 0x66; };
    pL->Slot0c0RecSet5(6, 3);
    assert(s_uCtyOp == 5 && s_nCtyPush == 1);
    // ---- S4: Slot0c8 the same shape with 9 ----
    Reset();
    pL->Slot0c8RecSet9(5, 4);
    assert(s_nSetB == 1 && s_nFwdB == 1);
    g_fnCtyFind = [](void*, uint32_t) -> int64_t {
        return 0x66; };
    pL->Slot0c8RecSet9(6, 4);
    assert(s_uCtyOp == 9);
    // ---- S5: the two clears ----
    Reset();
    pL->Slot0d0LgClearA();
    assert(s_nClearA == 1);
    assert(pL->Slot0e0LgClearB() == 1 &&
           s_nClearB == 1);
    // ---- S6: Slot0d8 the leader swap ----
    Reset();
    g_fnRecIsLeader = [](void*) -> char { return 0; };
    assert(pL->Slot0d8LeaderSwap(5, 5) == 0);
    g_fnRecIsLeader = [](void*) -> char {
        return 1; };      // both leaders: 0x100
    assert(pL->Slot0d8LeaderSwap(5, 5) == 0x100);
    // A leader, B not: drive via the call order
    // (both finds hit the same node — the RAW reads
    // the leader flag per record; the counter
    // distinguishes the two reads)
    static int s_nLead = 0;
    g_fnRecIsLeader = [](void*) -> char {
        return ++s_nLead == 1; };
    uint64_t uR = pL->Slot0d8LeaderSwap(5, 5);
    assert((uR & 0xff) == 1);
    assert(s_nRankA >= 1 && s_nRankB >= 1);
    assert(s_nUpd >= 1);
    // ---- S7: Slot0f0 the quit flow ----
    Reset();
    assert(pL->Slot0f0QuitSyn(5, 999999) == 0);
    assert(pL->Slot0f0QuitSyn(6, 1000000) == 0);
    s_uRetX = 0x1234;
    assert(pL->Slot0f0QuitSyn(5, 1000000) == 0x700);
    assert(s_nLgTest == 1 && s_nKick == 1 &&
           s_nE8 == 1);
    g_fnRecGetRank = [](void*) -> uint64_t {
        return 5; };
    assert(pL->Slot0f0QuitSyn(5, 1000000) == 0);
    // ---- S8: Slot0f8 the rank-if-league ----
    Reset();
    assert(pL->Slot0f8GetRankIfLeague(0) == 0 &&
           s_nLog == 1);
    assert(pL->Slot0f8GetRankIfLeague(5) == 0x3de);
    g_fnLgFind = [](void*, uint32_t) -> int64_t {
        return 0; };
    assert(pL->Slot0f8GetRankIfLeague(5) == 0);
    // ---- S9: Slot100 quit-or-kick ----
    Reset();
    g_fnRecIsLeader = [](void*) -> char { return 1; };
    assert(pL->Slot100QuitOrKick(5) == 0x40);
    assert(s_nTalk == 1 &&
           !strcmp(s_acTalk, "STR_NO_DISBAND"));
    g_fnRecIsLeader = [](void*) -> char { return 0; };
    assert(pL->Slot100QuitOrKick(5) == 0x11);
    assert(s_nLeave == 1);
    // ---- S10: Slot108 rec-set-6 ----
    Reset();
    assert(pL->Slot108RecSet6(0, 2) == 0 && s_nLog==1);
    pL->Slot108RecSet6(5, 2);
    assert(s_nSetC == 1 && s_nFwdC == 1);
    g_fnCtyFind = [](void*, uint32_t) -> int64_t {
        return 0x66; };
    assert(pL->Slot108RecSet6(6, 2) == 1);
    assert(s_uCtyOp == 6);
    g_fnCtyFind = [](void*, uint32_t) -> int64_t {
        return 0; };
    assert(pL->Slot108RecSet6(6, 2) == 0);
    // ---- S11: Slot110/128 the league getters ----
    Reset();
    s_uRetZ = 0x5a; s_uRetY = 0x5b;
    assert(pL->Slot110LgZ(0, 1) == 0 && s_nLog == 1);
    assert(pL->Slot110LgZ(5, 1) == 0x5a);
    assert(pL->Slot128LgGetY(5) == 0x5b);
    g_fnLgFind = [](void*, uint32_t) -> int64_t {
        return 0; };
    assert(pL->Slot128LgGetY(5) == 0);
    // ---- S12: Slot130/138/140 the rec tails ----
    Reset();
    pL->Slot130RecClr(6);           // not found
    assert(s_nClr == 0);
    pL->Slot130RecClr(5);
    assert(s_nClr == 1);
    assert(pL->Slot138RecChkFwd(5, 8) == 0x301);
    assert(s_nF0 == 1);
    g_fnRecChk = [](void*, int32_t)
        -> uint64_t { return 0; };
    assert(pL->Slot138RecChkFwd(5, 8) == 0);
    assert(pL->Slot140RecGetX(5, 8) == 0x77);
    assert(pL->Slot140RecGetX(6, 8) == 0);
    puts("SYNDICATE_D92_OK: the logic table wave 2");
    return 0;
}
