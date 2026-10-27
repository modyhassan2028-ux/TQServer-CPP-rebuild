// D93 — the CSyndicateLogic table wave 3 (slots
// +0x148..+0x188) — the rec-delegate family.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x60];
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
    apMap[0] = pAnchor;
    apMap[6] = pHead;
}

static void* s_pLast; static int s_nA, s_nE, s_nI;
static int32_t s_nLast; static uint64_t s_uA, s_uB;
static char s_cLast; static void* s_pC;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    BuildMap(apLogMap, abLogHead, abLogNode,
             abLogAnchor, 5, abRecBox);
    *(void**)(abLogic + 0x18) = apLogMap;
    s_nA = s_nE = s_nI = 0;
    s_nLast = 0; s_uA = s_uB = 0; s_cLast = 0;
    s_pLast = nullptr; s_pC = nullptr;
    g_fnRecA = [](void* p, int32_t n) -> uint64_t {
        s_pLast = p; s_nLast = n; s_nA++;
        return 0xA1; };
    g_fnRecB = [](void* p, int32_t n, uint64_t a,
                  uint64_t b) -> uint64_t {
        s_pLast = p; s_nLast = n; s_uA = a; s_uB = b;
        return 0xB2; };
    g_fnRecC = [](void* p, int32_t n, void* pc,
                  char c) -> uint64_t {
        s_pLast = p; s_nLast = n; s_pC = pc;
        s_cLast = c; return 0xC3; };
    g_fnRecD = [](void* p, int32_t n,
                  char c) -> uint64_t {
        s_pLast = p; s_nLast = n; s_cLast = c;
        return 0xD4; };
    g_fnRecE = [](void* p) { s_pLast = p; s_nE++; };
    g_fnRecF = [](void*) -> uint64_t { return 0xF5; };
    g_fnRecG = [](void*) -> uint64_t { return 0xF6; };
    g_fnRecH = [](void*) -> uint64_t { return 0xF7; };
    g_fnRecI = [](void*) -> int32_t {
        s_nI++; return 0x99; };
}

int main() {
    // ---- S1: the not-found gates ----
    Reset();
    assert(pL->Slot148RecA(9, 3) == 0);
    assert(pL->Slot150RecB(9, 3, 1, 2) == 0);
    assert(pL->Slot158RecC(9, 3) == 0);
    assert(pL->Slot160RecD(9, 3) == 0);
    pL->Slot168RecE(9);
    assert(pL->Slot170RecF(9) == 0);
    assert(pL->Slot178RecG(9) == 0);
    assert(pL->Slot180RecH(9) == 0);
    assert(pL->Slot188RecI(9) == 0);
    // ---- S2: the found delegates ----
    assert(pL->Slot148RecA(5, 3) == 0xA1 &&
           s_nLast == 3 && s_pLast == (void*)abRecBox);
    assert(pL->Slot150RecB(5, 4, 0x11, 0x22) == 0xB2);
    assert(s_nLast == 4 && s_uA == 0x11 && s_uB == 0x22);
    assert(pL->Slot158RecC(5, 5) == 0xC3);
    assert(s_pC == (void*)0x1418347c0 && s_cLast == 1);
    assert(pL->Slot160RecD(5, 6) == 0xD4 &&
           s_cLast == 1);
    pL->Slot168RecE(5);
    assert(s_nE == 1 && s_pLast == (void*)abRecBox);
    assert(pL->Slot170RecF(5) == 0xF5);
    assert(pL->Slot178RecG(5) == 0xF6);
    assert(pL->Slot180RecH(5) == 0xF7);
    assert(pL->Slot188RecI(5) == 0x99 && s_nI == 1);
    puts("SYNDICATE_D93_OK: the logic table wave 3");
    return 0;
}
