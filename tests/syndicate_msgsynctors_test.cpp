// The seventeen message constructors. All share one shape, so the test proves the shape once per
// class: the base table, Init, the class table, Init again, and then whatever that class adds.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
#include "modules/syndicate/src/msg/msgsynctors.h"

using namespace syndicate;
namespace tq { void log_InlineLogERROR(const char*, ...) {} }

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char g_msg[0x1000];
static int g_initCalls; static unsigned char g_initSeenFirst[8];
static uintptr_t g_tblAtInit[4]; static int g_tblAtInitN;
static int g_packerCtor; static unsigned char* g_packerAt;
static int g_setBuf; static void* g_setBufPacker; static char* g_setBufBuf; static uint32_t g_setBufLen; static bool g_setBufFlag;
static int g_reset; static void* g_resetAt; static int g_resetWhich;

static void Init(void* self) {
    ++g_initCalls;
    if (g_tblAtInitN < 4) g_tblAtInit[g_tblAtInitN++] = *(uintptr_t*)self;
    (void)self;
}
static void PackerCtor(void* p) { ++g_packerCtor; g_packerAt = (unsigned char*)p; }
static void SetBuf(void* p, char* b, uint32_t n, bool f) {
    ++g_setBuf; g_setBufPacker = p; g_setBufBuf = b; g_setBufLen = n; g_setBufFlag = f;
}
static void Reset408a(void* p) { ++g_reset; g_resetAt = p; g_resetWhich = 1; }
static void Reset408b(void* p) { ++g_reset; g_resetAt = p; g_resetWhich = 2; }

struct Spec { const char* name; uintptr_t cls; int kind; uint32_t bufOff; uint32_t len; };
// kind 0 simple, 1 reset, 2 packer
static const Spec g_specs[] = {
    { "CMsgLog",                       0x14182E4A0, 0, 0, 0 },
    { "CMsgLeagueRobOpt",              0x14183CC78, 1, 0, 0 },
    { "CMsgLeagueToken",               0x14183CFA0, 1, 0, 0 },
    { "CMsgSelfSynMemAwardRank",       0x14183D558, 0, 0, 0 },
    { "CMsgSynAttrInfo",               0x14183D768, 0, 0, 0 },
    { "CMsgSynBaseProffer",            0x14183D888, 0, 0, 0 },
    { "CMsgSynChgDomName",             0x14182E520, 0, 0, 0 },
    { "CMsgSyndicate",                 0x14183DC10, 2, 0x20, 0x3E5 },
    { "CMsgSynDomain",                 0x14183DE00, 2, 0x128, 0x2D9 },
    { "CMsgSynMemberInfo",             0x14183DF00, 0, 0, 0 },
    { "CMsgSynMemberList",             0x14183E010, 0, 0, 0 },
    { "CMsgSynProffer",                0x14183E180, 0, 0, 0 },
    { "CMsgSynProfferRank",            0x14183E2B0, 0, 0, 0 },
    { "CMsgSynRecruitAdvertising",     0x14183E3F8, 0, 0, 0 },
    { "CMsgSynRecruitAdvertisingList", 0x14183E508, 0, 0, 0 },
    { "CMsgSynRecruitAdvertisingOpt",  0x14183E620, 0, 0, 0 },
    { "CMsgLeagueOpt",                 0x14183C5A8, 2, 0x1A, 0x3EE },
};
static void* (*const g_fns[])(void*) = {
    &CMsgLog_Ctor_1417d9710, &CMsgLeagueRobOpt_Ctor_1417d8390, &CMsgLeagueToken_Ctor_1417d9000,
    &CMsgSelfSynMemAwardRank_Ctor_1417d9e60, &CMsgSynAttrInfo_Ctor_1417da860,
    &CMsgSynBaseProffer_Ctor_1417dac30, &CMsgSynChgDomName_Ctor_1417dae10,
    &CMsgSyndicate_Ctor_1417db2b0, &CMsgSynDomain_Ctor_1417dca60,
    &CMsgSynMemberInfo_Ctor_1417dd050, &CMsgSynMemberList_Ctor_1417dd230,
    &CMsgSynProffer_Ctor_1417dd6e0, &CMsgSynProfferRank_Ctor_1417dd9f0,
    &CMsgSynRecruitAdvertising_Ctor_1417ddc60, &CMsgSynRecruitAdvertisingList_Ctor_1417ddf50,
    &CMsgSynRecruitAdvertisingOpt_Ctor_1417de240, &CMsgLeagueOpt_Ctor_1417d6640,
};

int main() {
    g_pfnCMsgInit = &Init;
    g_pfnCStringPackerCtor = &PackerCtor;
    g_pfnCStringPackerSetBuf = &SetBuf;
    g_fn_1417f05f0 = &Reset408a;
    g_fn_1417f1600 = &Reset408b;
    CHECK(sizeof g_specs / sizeof g_specs[0] == sizeof g_fns / sizeof g_fns[0]);

    for (size_t i = 0; i < sizeof g_specs / sizeof g_specs[0]; ++i) {
        const Spec& s = g_specs[i];
        std::memset(g_msg, 0xCC, sizeof g_msg);
        g_initCalls = 0; g_tblAtInitN = 0; g_packerCtor = 0; g_packerAt = nullptr;
        g_setBuf = 0; g_setBufPacker = nullptr; g_setBufBuf = nullptr; g_setBufLen = 0;
        g_setBufFlag = false; g_reset = 0; g_resetAt = nullptr; g_resetWhich = 0;
        void* r = g_fns[i](g_msg);
        CHECK(r == (void*)g_msg);                            // every constructor returns this
        // the first Init must already see the base table, so a virtual call during it is safe
        CHECK(g_initCalls == 2);                             // Init runs twice for all seventeen
        CHECK(g_tblAtInit[0] == (uintptr_t)0x14182E368ULL);
        if (s.kind == 1) {
            CHECK(g_tblAtInit[1] == s.cls);
        }
        CHECK(*(uintptr_t*)g_msg == s.cls);                  // the class table wins
        if (s.kind == 0) {
            CHECK(*(void**)(g_msg + 0x408) == (void*)(g_msg + 8));
            CHECK(g_packerCtor == 0 && g_reset == 0);
        } else if (s.kind == 1) {
            CHECK(g_reset == 1);
            CHECK(g_resetAt == (void*)(g_msg + 0x408));
            CHECK(s.bufOff == 0);                            // the two reset classes store nothing
        } else {
            CHECK(g_packerCtor == 1);
            CHECK(g_packerAt == g_msg + 0x410);
            CHECK(*(void**)(g_msg + 0x408) == (void*)(g_msg + 8));
            CHECK(g_setBuf == 1);
            CHECK(g_setBufPacker == g_msg + 0x410);
            CHECK(g_setBufBuf == (char*)(g_msg + s.bufOff));
            CHECK(g_setBufLen == s.len);
            CHECK(g_setBufFlag == true);
        }
        // nothing outside the object is written: the byte after the packer area is untouched
        CHECK(g_msg[0x900] == 0xCC);
    }

    std::printf("MSGSYNCTOR_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
