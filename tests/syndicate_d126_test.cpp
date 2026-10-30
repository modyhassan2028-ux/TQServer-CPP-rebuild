// D126 — CMsgSyndicate, CMsgSelfSynMemAwardRank and the three
// CMsgSynRecruitAdvertising* classes (original msg/ paths)
#include "modules/syndicate/src/msg/msgsyndicate.h"
#include "modules/syndicate/src/msg/msgselfsynmemawardrank.h"
#include "modules/syndicate/src/msg/msgsynrecruitadvertising.h"
#include "modules/syndicate/src/msg/msgsynrecruitadvertisinglist.h"
#include "modules/syndicate/src/msg/msgsynrecruitadvertisingopt.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
#include "modules/syndicate/src/SyndicateMsgSyndicate.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nSub, s_nMgr, s_nGate, s_nLog;
static bool s_bCreate;
static unsigned char ab[0x440];

static int s_nCreateShim(void*, char*, uint16_t) { return s_bCreate ? 1 : 0; }

static void Init(void) {
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool {
        s_nCreate++; return s_bCreate; };
    g_fn_1418230a0 = [](void* p) {
        s_nSub++; assert(p == ab + CMsgSyndicate::kOffSubObject); };
    g_fnGetGameMgr = []() -> void* { s_nMgr++; return (void*)0x9000; };
    g_fnMgrGateUserOnline = [](void*, uint32_t) -> bool {
        s_nGate++; return false; };
    g_fnMsgBatchLog = [](const char*, const char*, const char*, uint32_t) {
        s_nLog++; };
    (void)s_nCreateShim;
}

template <class C>
static void CheckShape(uint16_t uType) {
    memset(ab, 0, sizeof ab);
    s_bCreate = true;
    *(uint16_t*)(ab + C::kOffMsgType) = uType;
    assert(C::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + C::kOffMsgType) = (uint16_t)(uType + 1);
    assert(C::Create(ab, (char*)1, 3) == false);
    s_bCreate = false;
    *(uint16_t*)(ab + C::kOffMsgType) = uType;
    assert(C::Create(ab, (char*)1, 3) == false);
    C::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == C::kBaseCMsgVft);
}

int main() {
    Init();

    // --- CMsgSyndicate: type 0x453, Process(0) hits the CHECK log
    CheckShape<CMsgSyndicate>(CMsgSyndicate::kMsgType);
    assert(s_nSub == 1);
    memset(ab, 0, sizeof ab);
    s_nLog = 0;
    CMsgSyndicate::Process(ab, 0);
    assert(s_nLog == 1);
    s_nMgr = 0;
    CMsgSyndicate::Process(ab, 7);      // gate false stops right after
    assert(s_nMgr == 1 && s_nGate == 1);

    // --- CMsgSelfSynMemAwardRank: type 0x427
    CheckShape<CMsgSelfSynMemAwardRank>(CMsgSelfSynMemAwardRank::kMsgType);
    s_nMgr = 0; s_nGate = 0;
    CMsgSelfSynMemAwardRank::Process(ab, 7);
    assert(s_nMgr == 1 && s_nGate == 1);

    // --- the three recruit-advertising types 0x8b1 / 0x8b2 / 0x8b3
    CheckShape<CMsgSynRecruitAdvertising>(
        CMsgSynRecruitAdvertising::kMsgType);
    s_nMgr = 0;
    CMsgSynRecruitAdvertising::Process(ab, 7);
    assert(s_nMgr == 1);

    CheckShape<CMsgSynRecruitAdvertisingList>(
        CMsgSynRecruitAdvertisingList::kMsgType);
    s_nMgr = 0;
    CMsgSynRecruitAdvertisingList::Process(ab, 7);
    assert(s_nMgr == 1);

    CheckShape<CMsgSynRecruitAdvertisingOpt>(
        CMsgSynRecruitAdvertisingOpt::kMsgType);
    s_nMgr = 0;
    CMsgSynRecruitAdvertisingOpt::Process(ab, 7);
    assert(s_nMgr == 1);

    printf("SYNDICATE_D126_OK: CMsgSyndicate + SelfSynMemAwardRank + "
           "3x RecruitAdvertising, 22/22 slots\n");
    return 0;
}
