// ============================================================================
// cqbase_d51 — the three user attribute getters. A fake provider/container pair with real
//   vtables proves the exact slots the binary uses: provider vt+0x10, then the container's
//   +0x40 (id), +0x78 (name) and +0x48 (number), with indexes 0 / 2 / 0x2b.
// ============================================================================
#include "modules/syndicate/src/synuserattr.h"
#include "modules/syndicate/src/msg/msgseams.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
static int g_nLogs = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

struct Container {
    void** ppVt;
    uint64_t uValue;
    const char* pszName;
};

struct Provider {
    void** ppVt;
    Container* apContainers[3];   // index 0, 2 and 0x2b
};

Container g_cId, g_cName, g_cNumber;

uint64_t GetId(void* p) { return ((Container*)p)->uValue; }
uint64_t GetNumber(void* p) { return ((Container*)p)->uValue + 1; }
const char* GetName(void* p) { return ((Container*)p)->pszName; }

// container vtable: slots 0..0x10, only 8, 9 and 0xf are ever called
void* g_aContainersVt[0x12];
// provider vtable: slot 2 answers the container by index
void* g_aProviderVt[4];

int g_nLastIndex = -1;
void* ProviderSlot2(void* p, int nIndex) {
    g_nLastIndex = nIndex;
    Provider* pProv = (Provider*)p;
    if (nIndex == 0) return pProv->apContainers[0];
    if (nIndex == 2) return pProv->apContainers[1];
    if (nIndex == 0x2b) return pProv->apContainers[2];
    return nullptr;
}

}  // namespace

int main() {
    // the log seam is only reached on the defensive branch

    g_cId.ppVt = g_aContainersVt;
    g_cId.uValue = 0xABCDEF;
    g_cName.ppVt = g_aContainersVt;
    g_cName.pszName = "Pilot";
    g_cNumber.ppVt = g_aContainersVt;
    g_cNumber.uValue = 0x99;

    g_aContainersVt[8] = (void*)&GetId;
    g_aContainersVt[9] = (void*)&GetNumber;
    g_aContainersVt[0xf] = (void*)&GetName;
    g_aProviderVt[2] = (void*)&ProviderSlot2;

    Provider aProvider;
    aProvider.ppVt = g_aProviderVt;
    aProvider.apContainers[0] = &g_cId;
    aProvider.apContainers[1] = &g_cName;
    aProvider.apContainers[2] = &g_cNumber;

    std::vector<uint8_t> aUser(0x430, 0);
    *(void**)(aUser.data() + 0x428) = &aProvider;

    CHECK(SynUserAttrId(aUser.data()) == 0xABCDEF);
    CHECK(g_nLastIndex == 0);
    CHECK(SynUserAttrName(aUser.data()) == std::string("Pilot"));
    CHECK(g_nLastIndex == 2);
    CHECK(SynUserAttrNumber(aUser.data()) == 0x9A);
    CHECK(g_nLastIndex == 0x2b);

    // ---- the defensive branch: no provider, defaults come back and the seam is reported
    {
        static int aLogCalls = 0;
        struct Hook {
            static void Call(const char*, ...) { ++aLogCalls; }
        };
        syndicate::g_fn_141823030 = (decltype(syndicate::g_fn_141823030))&Hook::Call;
        std::vector<uint8_t> aBare(0x430, 0);
        CHECK(SynUserAttrId(aBare.data()) == 0);
        CHECK(std::string(SynUserAttrName(aBare.data())).empty());
        CHECK(SynUserAttrNumber(aBare.data()) == 0);
        CHECK(aLogCalls == 3);        // one report per getter, on its own source line
        g_nLogs = aLogCalls;
    }

    std::printf("SYNDICATE_D51_OK: the user attribute getters, %d checks, %d guard reports\n",
                g_nChecks, g_nLogs);
    return 0;
}
