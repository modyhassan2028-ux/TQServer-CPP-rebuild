// ============================================================================
// cqbase_d53 — the insert core 0x1417c5640. Proves the manager at owner+0x88 is driven
//   through the three slots the binary uses (0x3f compare, 1 insert, 0x1b commit), that
//   the commit runs even when the message build is refused, that the actor is passed only
//   when the ids match, and that the announce goes out only on the caller's flag.
// ============================================================================
#include "modules/syndicate/src/synattrsend.h"
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/synuserattr.h"
#include "modules/syndicate/src/msg/cmsgbase.h"
#include "modules/syndicate/src/msg/msgseams.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nLogs = 0;
void LogHook(const char*, ...) { ++g_nLogs; }
int g_nInitMsg = 0, g_nInitPacker = 0;
void InitHook(void*) {}
void PackerInitHook(void* p) { (void)p; }

// ---- the manager: vtable slots 0x3f, 1 and 0x1b
std::vector<int> g_aCalls;          // 1 = compare, 2 = insert(attr), 3 = insert(announce), 4 = commit
uint32_t g_uMgrId = 0;
uint32_t g_uCompareReturns = 0;
uint32_t g_uInsertedId = 0;
int g_nInserts = 0;
uint64_t g_uAnnounceParam = 0;
std::string g_strAnnounce;

uint32_t MgrCompare(void* p, uint32_t uId) { g_aCalls.push_back(1); (void)p; (void)uId; return g_uCompareReturns; }
void MgrInsert(void* p, uint32_t uId, void* pMsg) {
    (void)p;
    g_aCalls.push_back(++g_nInserts == 1 ? 2 : 3);
    g_uInsertedId = uId;
    uint8_t* hdr = *(uint8_t**)((uint8_t*)pMsg + 0x408);
    g_strAnnounce = (const char*)((uint8_t*)pMsg + 0x420);
    if (hdr) g_uAnnounceParam = *(uint32_t*)(hdr + 8);
}
void MgrCommit(void* p, uint32_t uId) { (void)p; (void)uId; g_aCalls.push_back(4); }

void* g_aMgrVt[0x40];

// ---- the attribute record, the message build and the destructors
int g_nFill = 0;
void FillHook(void* pAttr, void* pRec) { (void)pAttr; (void)pRec; ++g_nFill; }
bool g_bMsgInitOk = true;
void* g_pInitActor = (void*)0x1;
void* g_pInitRec = nullptr;
bool MsgInitHook(void* pMsg, void* pRec, void* pActor) {
    (void)pMsg; g_pInitRec = pRec; g_pInitActor = pActor; return g_bMsgInitOk;
}
int g_nDtorAttr = 0, g_nDtorAnn = 0;
void Dtor1088Hook(void*) { ++g_nDtorAttr; }
void Dtor0428Hook(void*) { ++g_nDtorAnn; }

// ---- the user attribute getters (their own dispatch, faked)
uint32_t g_uUserId = 0;
const char* g_pszUserName = "Nova";
uint64_t SynUserIdStub(void* p) { (void)p; return 0; }
int g_nReset = 0;

struct Manager { void** vt; };

struct UserAttrProvider {
    void** vt;
};
struct UserAttrContainer {
    void** vt;
};
UserAttrContainer g_aContainer;
void* ProviderSlot2(void*, int) { return &g_aContainer; }   // one container answers all three slots

}  // namespace

// the getters are real functions in synuserattr.cpp; the test drives them through a fake
// provider so the core sees the id / name / number it should
namespace {

void* g_aContVt[0x12];
void* g_aProvVt[4];
uint64_t ContId(void*) { return g_uUserId; }
const char* ContName(void*) { return g_pszUserName; }
uint64_t ContNumber(void*) { return 0x77; }

}  // namespace

int main() {
    syndicate::g_fn_141823030 = (decltype(syndicate::g_fn_141823030))&LogHook;
    syndicate::g_pfnCMsgInit = (decltype(syndicate::g_pfnCMsgInit))&InitHook;
    syndicate::g_fnM83AddString = (decltype(syndicate::g_fnM83AddString))[](void* p, const char* s) {
        std::strcpy((char*)p + 0x10, s ? s : "");
    };
    g_fnSynMsgPackerSize = [] (void* p) -> uint32_t { return (uint32_t)std::strlen((const char*)p + 0x10); };
    g_fnSynAttrFillRec = &FillHook;
    g_fnSynAttrMsgInit = &MsgInitHook;
    syndicate::g_fnModMem1088 = (decltype(syndicate::g_fnModMem1088))&Dtor1088Hook;
    syndicate::g_fnModMem0428 = (decltype(syndicate::g_fnModMem0428))&Dtor0428Hook;

    g_aMgrVt[0x3f] = (void*)&MgrCompare;
    g_aMgrVt[1] = (void*)&MgrInsert;
    g_aMgrVt[0x1b] = (void*)&MgrCommit;

    // the fake user: the provider at +0x428
    g_aContainer.vt = g_aContVt;
    g_aContVt[8] = (void*)&ContId;
    g_aContVt[0x9] = (void*)&ContNumber;
    g_aContVt[0xf] = (void*)&ContName;
    g_aProvVt[2] = (void*)&ProviderSlot2;
    UserAttrProvider aProv;
    aProv.vt = g_aProvVt;

    std::vector<uint8_t> aOwner(0x100, 0), aUser(0x440, 0), aAttr(0x40, 0);
    Manager aMgr;
    aMgr.vt = g_aMgrVt;
    *(void**)(aOwner.data() + 0x88) = &aMgr;
    *(void**)(aUser.data() + 0x428) = &aProv;

    // ---- the ids match: the user rides as the actor, and the announce is built
    g_uCompareReturns = 0x42;
    g_uUserId = 0x42;
    g_aCalls.clear(); g_nInserts = 0; g_nFill = 0;
    g_bMsgInitOk = true;
    SynAttrInsertCore(aOwner.data(), aUser.data(), aAttr.data(), 0x42, 1);
    CHECK(g_aCalls.size() == 4);
    CHECK(g_aCalls[0] == 1);                     // compare first
    CHECK(g_aCalls[1] == 2);                     // the attribute message
    CHECK(g_aCalls[2] == 4);                     // commit
    CHECK(g_aCalls[3] == 3);                     // then the announce, through the same slot
    CHECK(g_pInitActor == (void*)aUser.data());  // the ids matched, so the user is the actor
    CHECK(g_nFill == 1);
    CHECK(g_uInsertedId == 0x42);
    CHECK(g_uAnnounceParam == 0x77);             // the number from the announce getter
    CHECK(g_strAnnounce == "Nova");
    CHECK(g_nDtorAttr == 1 && g_nDtorAnn == 1);

    // ---- the ids differ: no actor, but the announce still goes (with "" and 0)
    g_uCompareReturns = 0x99;
    g_aCalls.clear(); g_nInserts = 0; g_nDtorAttr = g_nDtorAnn = 0;
    SynAttrInsertCore(aOwner.data(), aUser.data(), aAttr.data(), 0x42, 1);
    CHECK(g_pInitActor == nullptr);
    CHECK(g_uAnnounceParam == 0);
    CHECK(g_strAnnounce.empty());
    CHECK(g_nDtorAttr == 1 && g_nDtorAnn == 1);

    // ---- the build is refused: the log fires, the commit still runs, no insert
    g_uCompareReturns = 0x42;
    g_bMsgInitOk = false;
    g_aCalls.clear(); g_nInserts = 0; g_nLogs = 0; g_nDtorAttr = g_nDtorAnn = 0;
    SynAttrInsertCore(aOwner.data(), aUser.data(), aAttr.data(), 0x42, 0);
    CHECK(g_nLogs == 1);                         // line 0x35a
    CHECK(g_aCalls.size() == 2);
    CHECK(g_aCalls[0] == 1);
    CHECK(g_aCalls[1] == 4);                     // the commit is unconditional
    CHECK(g_nDtorAttr == 1 && g_nDtorAnn == 0);  // no announce, no announce dtor

    // ---- no user: one report and nothing else happens
    g_aCalls.clear(); g_nLogs = 0; g_nDtorAttr = g_nDtorAnn = 0;
    SynAttrInsertCore(aOwner.data(), nullptr, aAttr.data(), 0x42, 1);
    CHECK(g_nLogs == 1);                         // line 0x348
    CHECK(g_aCalls.empty());
    CHECK(g_nDtorAttr == 0 && g_nDtorAnn == 0);  // every destructor is skipped

    // ---- no attribute pointer: the fill is skipped, everything else stands
    g_bMsgInitOk = true;
    g_aCalls.clear(); g_nInserts = 0; g_nFill = 0; g_nDtorAttr = g_nDtorAnn = 0;
    SynAttrInsertCore(aOwner.data(), aUser.data(), nullptr, 0x42, 0);
    CHECK(g_nFill == 0);
    CHECK(g_aCalls.size() == 3);
    CHECK(g_nDtorAttr == 1 && g_nDtorAnn == 0);

    // ---- the hook really does point at the core by default
    CHECK(g_fnSynAttrInsertCore != nullptr);

    std::printf("SYNDICATE_D53_OK: the insert core, %d checks\n", g_nChecks);
    return 0;
}
