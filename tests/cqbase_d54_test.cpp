// ============================================================================
// cqbase_d54 — the five protobuf GetTypeName slots (the last missing slot of five
//   classes) and the four numeric-limit statics. The expected strings are the exact
//   .rdata literals the original lea instructions point at.
// ============================================================================
#include "modules/syndicate/src/synpbclass.h"

#include <cassert>
#include <cstdio>
#include <limits>
#include <string>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

int main() {
    struct Case { std::string* (*pfn)(void*, std::string*); const char* pszWant; };
    Case aCases[] = {
        {&SynPbNameConcubines, "CMsgLeagueConcubinesPB"},
        {&SynPbNameOrderStatusInfo, "CMsgLeagueOrderStatusInfoPB"},
        {&SynPbNameOrderStatus, "CMsgLeagueOrderStatusPB"},
        {&SynPbNameRobItem, "CMsgLeagueRobItemPB"},
        {&SynPbNameRobList, "CMsgLeagueRobListPB"},
    };
    for (const Case& c : aCases) {
        std::string sFrom("garbage-that-must-be-overwritten");
        std::string* pRet = c.pfn(nullptr, &sFrom);
        CHECK(pRet == &sFrom);                     // the argument is handed back
        CHECK(sFrom == c.pszWant);                 // and carries the exact literal
    }

    // the self pointer is ignored by every one of them
    {
        int nSelf = 0;
        std::string s;
        CHECK(SynPbNameRobList(&nSelf, &s) == &s);
        CHECK(s == "CMsgLeagueRobListPB");
    }

    // ---- the four statics: each writes INT_MAX into its own global only
    g_nSynLimit8c = g_nSynLimit90 = g_nSynLimit94 = g_nSynLimit98 = 0;
    SynLimitInit8c();
    CHECK(g_nSynLimit8c == std::numeric_limits<int>::max());
    CHECK(g_nSynLimit90 == 0 && g_nSynLimit94 == 0 && g_nSynLimit98 == 0);
    SynLimitInit90();
    CHECK(g_nSynLimit90 == std::numeric_limits<int>::max());
    CHECK(g_nSynLimit94 == 0 && g_nSynLimit98 == 0);
    SynLimitInit94();
    CHECK(g_nSynLimit94 == std::numeric_limits<int>::max());
    CHECK(g_nSynLimit98 == 0);
    SynLimitInit98();
    CHECK(g_nSynLimit98 == std::numeric_limits<int>::max());
    CHECK(g_nSynLimit8c == 2147483647);            // the byte value, not just the symbol

    std::printf("SYNDICATE_D54_OK: five class name slots and four limit statics, %d checks\n",
                g_nChecks);
    return 0;
}
