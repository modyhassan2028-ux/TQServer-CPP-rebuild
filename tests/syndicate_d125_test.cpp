// D125 — CMsgSynProfferRank + CMsgSynCompete
#include "modules/syndicate/src/msg/msgsynprofferrank.h"
#include "modules/syndicate/src/msg/msgsyncompete.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nRank, s_nMgr, s_nQuery;
static uint8_t s_uA, s_uB;
static uint32_t s_uId;
static bool s_bQuery;
static unsigned char ab[0x440];

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { return true; };
    g_pfnGetSyndicateMgr = []() -> void* { s_nMgr++; return (void*)0x7000; };
    g_fn_1417ac6f0 = [](void*, uint32_t) -> bool { s_nQuery++; return s_bQuery; };
    g_fn_1417ae720 = [](void*, uint32_t id, uint8_t a, uint8_t b) {
        s_nRank++; s_uId = id; s_uA = a; s_uB = b; };

    // --- CMsgSynProfferRank: type 0x835, two rank bytes at +4/+5
    memset(ab, 0, sizeof ab);
    unsigned char payload[0x10];
    memset(payload, 0, sizeof payload);
    *(void**)(ab + CMsgSynProfferRank::kOffPayload) = payload;
    *(uint16_t*)(ab + CMsgSynProfferRank::kOffMsgType) = 0x835;
    assert(CMsgSynProfferRank::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynProfferRank::kOffMsgType) = 0x834;
    assert(CMsgSynProfferRank::Create(ab, (char*)1, 3) == false);

    payload[CMsgSynProfferRank::kOffRankA] = 3;
    payload[CMsgSynProfferRank::kOffRankB] = 7;
    s_bQuery = false;
    CMsgSynProfferRank::Process(ab, 21);
    assert(s_nRank == 0);
    s_bQuery = true;
    CMsgSynProfferRank::Process(ab, 21);
    assert(s_nRank == 1 && s_uId == 21 && s_uA == 3 && s_uB == 7);

    CMsgSynProfferRank::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynProfferRank::kBaseCMsgVft);

    // --- CMsgSynCompete: type 0x426, Process stays the base error stub
    memset(ab, 0, sizeof ab);
    *(uint16_t*)(ab + CMsgSynCompete::kOffMsgType) = 0x426;
    assert(CMsgSynCompete::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynCompete::kOffMsgType) = 0x427;
    assert(CMsgSynCompete::Create(ab, (char*)1, 3) == false);
    CMsgSynCompete::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynCompete::kBaseCMsgVft);

    printf("SYNDICATE_D125_OK: CMsgSynProfferRank + CMsgSynCompete 4/4 slots\n");
    return 0;
}
