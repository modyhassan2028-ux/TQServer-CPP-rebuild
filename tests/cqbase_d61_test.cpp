// ============================================================================
// cqbase_d61 — the last unported row of three RTTI-identified classes. The tests pin the
//   exact order (body destructor always, the free only on bit 0) and the return value.
// ============================================================================
#include "modules/syndicate/src/synclassdtors.h"

#include <cassert>
#include <cstdio>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

std::vector<int> g_aOrder;      // 1 = body dtor, 2 = free, 3 = token free
void BodyDtorHook(void*) { g_aOrder.push_back(1); }
void FreeHook(void*) { g_aOrder.push_back(2); }
void Free2Hook(void*) { g_aOrder.push_back(3); }
int g_nThunks = 0;
void ThunkHook(void) { ++g_nThunks; }

}  // namespace

int main() {
    g_fnCsBodyDtor = &BodyDtorHook;
    g_fnCsFree = &FreeHook;
    g_fnCsFree2 = &Free2Hook;
    g_fnPbEBF80 = &ThunkHook;

    // ---- CSyndicate: flags 0 — the body destructor runs, no free
    {
        std::vector<uint8_t> aObj(0x40, 0xA5);
        g_aOrder.clear();
        CHECK(SynCsDeletingDtor(aObj.data(), 0) == aObj.data());
        CHECK(g_aOrder.size() == 1);
        CHECK(g_aOrder[0] == 1);
    }

    // ---- CSyndicate: flags 1 — the body destructor then the free, in that order
    {
        std::vector<uint8_t> aObj(0x40, 0xA5);
        g_aOrder.clear();
        CHECK(SynCsDeletingDtor(aObj.data(), 1) == aObj.data());
        CHECK(g_aOrder.size() == 2);
        CHECK(g_aOrder[0] == 1);
        CHECK(g_aOrder[1] == 2);
    }

    // ---- CSyndicate: any other bit alone does not free (only bit 0 is tested)
    {
        std::vector<uint8_t> aObj(0x40, 0xA5);
        g_aOrder.clear();
        SynCsDeletingDtor(aObj.data(), 0xFE);
        CHECK(g_aOrder.size() == 1);        // test bl,0x1 sees bit 0 clear
        g_aOrder.clear();
        SynCsDeletingDtor(aObj.data(), 0xFF);
        CHECK(g_aOrder.size() == 2);        // bit 0 set: both steps
    }

    // ---- CToken: no body destructor exists; the vtable is stamped back first
    {
        std::vector<uint8_t> aObj(0x40, 0x00);
        g_aOrder.clear();
        CHECK(SynTokenDeletingDtor(aObj.data(), 0) == aObj.data());
        CHECK(g_aOrder.empty());
        CHECK(*(uintptr_t*)aObj.data() == kSynCtokenVft);
        CHECK(kSynCtokenVft == 0x14183be50ULL);

        // bit 0 set: the stamp happens first, then the free
        g_aOrder.clear();
        std::vector<uint8_t> aObj2(0x40, 0x11);
        SynTokenDeletingDtor(aObj2.data(), 1);
        CHECK(g_aOrder.size() == 1);
        CHECK(g_aOrder[0] == 3);
        CHECK(*(uintptr_t*)aObj2.data() == kSynCtokenVft);
    }

    // ---- the concubines thunk forwards exactly once per call
    {
        g_nThunks = 0;
        SynConcubinesThunk();
        SynConcubinesThunk();
        CHECK(g_nThunks == 2);
    }

    std::printf("SYNDICATE_D61_OK: three class rows (CSyndicate, CToken, the concubines thunk), "
                "%d checks\n", g_nChecks);
    return 0;
}
