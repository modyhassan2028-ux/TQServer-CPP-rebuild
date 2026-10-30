// D124 — CMsgLeagueBeRob + CMsgSynProffer
#include "modules/syndicate/src/msg/msgleagueberob.h"
#include "modules/syndicate/src/msg/msgsynproffer.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nMgr, s_nQuery, s_nVf28, s_nSub;
static void* s_pVfMgr;
static uint32_t s_uVfId;
static bool s_bQuery;
static unsigned char ab[0x440];

int main() {
    g_pfnGetSyndicateMgr = []() -> void* { s_nMgr++; return (void*)0x6000; };
    g_fn_1417ac6f0 = [](void*, uint32_t) -> bool { s_nQuery++; return s_bQuery; };
    g_pfnMgrVf28 = [](void* p, uint32_t id) {
        s_nVf28++; s_pVfMgr = p; s_uVfId = id; };
    g_fn_1417e9440 = [](void* p) {
        s_nSub++; assert(p == ab + CMsgLeagueBeRob::kOffSubObject); };
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { return true; };

    // --- CMsgLeagueBeRob: dtor only, every other slot is the base one
    memset(ab, 0, sizeof ab);
    CMsgLeagueBeRob::DeleteDtor(ab, 0);
    assert(s_nSub == 1);
    assert(*(uintptr_t*)ab == CMsgLeagueBeRob::kBaseCMsgVft);

    // --- CMsgSynProffer: type 0x422
    memset(ab, 0, sizeof ab);
    *(uint16_t*)(ab + CMsgSynProffer::kOffMsgType) = 0x422;
    assert(CMsgSynProffer::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynProffer::kOffMsgType) = 0x423;
    assert(CMsgSynProffer::Create(ab, (char*)1, 3) == false);

    s_bQuery = false;
    CMsgSynProffer::Process(ab, 9);
    assert(s_nMgr == 1 && s_nVf28 == 0);

    s_bQuery = true;
    CMsgSynProffer::Process(ab, 9);
    assert(s_nVf28 == 1 && s_pVfMgr == (void*)0x6000 && s_uVfId == 9);

    CMsgSynProffer::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynProffer::kBaseCMsgVft);

    printf("SYNDICATE_D124_OK: CMsgLeagueBeRob + CMsgSynProffer 6/6 slots\n");
    return 0;
}
