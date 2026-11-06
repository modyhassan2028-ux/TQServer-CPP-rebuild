// The four deleting-destructor wrappers and the id setter.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_dl.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static void* g_pBody = nullptr;
static void* g_pFreed = nullptr;
static int g_nBody = 0, g_nFree = 0;
static void Body(void* p) { ++g_nBody; g_pBody = p; }
static void Free(void* p) { ++g_nFree; g_pFreed = p; }

static void Reset() { g_nBody = g_nFree = 0; g_pBody = g_pFreed = nullptr; }

template <typename Fn>
static void CheckWrapper(Fn pfn, uintptr_t uExpectBody) {
    static unsigned char aObj[0x40];
    Reset();
    void* pR = pfn(aObj, 0u);                        // flag clear: body only
    CHECK(g_nBody == 1);
    CHECK(g_nFree == 0);
    CHECK(pR == aObj);                               // the wrapper returns the object
    CHECK((uintptr_t)g_pBody == (uintptr_t)aObj + uExpectBody);

    Reset();
    pR = pfn(aObj, 1u);                              // flag set: body then free
    CHECK(g_nBody == 1);
    CHECK(g_nFree == 1);
    CHECK(g_pFreed == aObj);
    CHECK(pR == aObj);

    Reset();
    pfn(aObj, 0x100u);                               // bit 0 clear, other bits irrelevant
    CHECK(g_nBody == 1);
    CHECK(g_nFree == 0);
}

int main() {
    g_fnDL_1417ceb80 = &Body;
    g_fnDL_14174cfc0 = &Body;
    g_fnDL_141775800 = &Body;
    g_fnDL_14173ecf0 = &Body;
    g_fnDL_del = &Free;

    CheckWrapper(SynDelWrap_1417cf2b0, 0);
    CheckWrapper(SynDelWrap_14174d8d0, 0);
    CheckWrapper(SynDelWrap_141775df0, 0);

    {   // the merit wrapper: vtable store, member at +8 teardown, member free, then the flag
        static unsigned char aObj[0x40];
        std::memset(aObj, 0, sizeof(aObj));
        *(void**)(aObj + 0x8) = (void*)0x4001;       // the member pointer that gets freed
        Reset();
        void* pR = SynDelWrap_14173f950(aObj, 0u);
        CHECK(g_nBody == 1);
        CHECK((uintptr_t)g_pBody == (uintptr_t)aObj + 0x8);   // member, not the object
        CHECK(g_nFree == 1);
        CHECK(g_pFreed == (void*)0x4001);                    // *(void**)(this+8)
        CHECK(pR == aObj);
        CHECK(*(void**)aObj == (void*)g_vtMerit_141828048);  // the vtable store came first

        *(void**)(aObj + 0x8) = (void*)0x4002;
        Reset();
        pR = SynDelWrap_14173f950(aObj, 1u);
        CHECK(g_nBody == 1);
        CHECK(g_nFree == 2);                                 // member free + object free
        CHECK(pR == aObj);
    }

    {   // the id setter: two ids, everything else untouched
        static unsigned char aObj[0x100];
        std::memset(aObj, 0xCC, sizeof(aObj));
        SynSetById_1417c5860(aObj, 0x40eu, 0x1111);
        CHECK(*(uint32_t*)(aObj + 0xa8) == 0x1111);
        CHECK(*(uint32_t*)(aObj + 0xac) == 0xCCCCCCCCu);     // the other field untouched
        SynSetById_1417c5860(aObj, 0x3e8u, 0x2222);
        CHECK(*(uint32_t*)(aObj + 0xac) == 0x2222);
        CHECK(*(uint32_t*)(aObj + 0xa8) == 0x1111);          // unchanged
        SynSetById_1417c5860(aObj, 0x1234u, 0x3333);         // unknown id: nothing happens
        CHECK(*(uint32_t*)(aObj + 0xa8) == 0x1111);
        CHECK(*(uint32_t*)(aObj + 0xac) == 0x2222);
    }

    std::printf("SYNDICATE_THUNKS_DL_OK: 5 bodies, %d checks\n", g_nChecks);
    return 0;
}
