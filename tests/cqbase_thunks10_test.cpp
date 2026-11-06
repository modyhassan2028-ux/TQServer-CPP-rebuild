// Generated with family O — the guarded path and the plain path.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "modules/syndicate/src/synthunks_o.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_t = 0, g_2 = 0; static int g_nCalls = 0;
static void Hook(void* t, void* a2, void* a3) { g_t = (uintptr_t)t; g_2 = (uintptr_t)a2; ++g_nCalls; }

int main() {
    g_fnO_1418233c0 = &Hook;
    unsigned char aThis[16], aSecond[16];
    std::memset(aThis, 0xCC, sizeof(aThis));
    *(void**)aSecond = (void*)0x1234;

    {   // 0x1417266b0
        g_nCalls = 0;
        void* pB = SynSet2_1417266b0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417266b0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141726720
        g_nCalls = 0;
        void* pB = SynSet2_141726720(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141726720(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141726770
        g_nCalls = 0;
        void* pB = SynSet2_141726770(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141726770(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417267c0
        g_nCalls = 0;
        void* pB = SynSet2_1417267c0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417267c0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141726880
        g_nCalls = 0;
        void* pB = SynSet2_141726880(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141726880(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417269f0
        g_nCalls = 0;
        void* pB = SynSet2_1417269f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417269f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727a50
        g_nCalls = 0;
        void* pB = SynSet2_141727a50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727a50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727ab0
        g_nCalls = 0;
        void* pB = SynSet2_141727ab0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727ab0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727af0
        g_nCalls = 0;
        void* pB = SynSet2_141727af0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727af0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727b30
        g_nCalls = 0;
        void* pB = SynSet2_141727b30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727b30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727b70
        g_nCalls = 0;
        void* pB = SynSet2_141727b70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727b70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141727c30
        g_nCalls = 0;
        void* pB = SynSet2_141727c30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141727c30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14173bb40
        g_nCalls = 0;
        void* pB = SynSet2_14173bb40(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14173bb40(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14173bbc0
        g_nCalls = 0;
        void* pB = SynSet2_14173bbc0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14173bbc0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14173be70
        g_nCalls = 0;
        void* pB = SynSet2_14173be70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14173be70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14173beb0
        g_nCalls = 0;
        void* pB = SynSet2_14173beb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14173beb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141746810
        g_nCalls = 0;
        void* pB = SynSet2_141746810(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141746810(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141746880
        g_nCalls = 0;
        void* pB = SynSet2_141746880(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141746880(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141747330
        g_nCalls = 0;
        void* pB = SynSet2_141747330(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141747330(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141747370
        g_nCalls = 0;
        void* pB = SynSet2_141747370(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141747370(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755b00
        g_nCalls = 0;
        void* pB = SynSet2_141755b00(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755b00(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755c80
        g_nCalls = 0;
        void* pB = SynSet2_141755c80(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755c80(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755e00
        g_nCalls = 0;
        void* pB = SynSet2_141755e00(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755e00(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755e60
        g_nCalls = 0;
        void* pB = SynSet2_141755e60(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755e60(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755ed0
        g_nCalls = 0;
        void* pB = SynSet2_141755ed0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755ed0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141755f50
        g_nCalls = 0;
        void* pB = SynSet2_141755f50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141755f50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141756090
        g_nCalls = 0;
        void* pB = SynSet2_141756090(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141756090(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417560d0
        g_nCalls = 0;
        void* pB = SynSet2_1417560d0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417560d0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141756130
        g_nCalls = 0;
        void* pB = SynSet2_141756130(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141756130(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417561a0
        g_nCalls = 0;
        void* pB = SynSet2_1417561a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417561a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757b50
        g_nCalls = 0;
        void* pB = SynSet2_141757b50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757b50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757bf0
        g_nCalls = 0;
        void* pB = SynSet2_141757bf0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757bf0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757cb0
        g_nCalls = 0;
        void* pB = SynSet2_141757cb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757cb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757d10
        g_nCalls = 0;
        void* pB = SynSet2_141757d10(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757d10(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757d70
        g_nCalls = 0;
        void* pB = SynSet2_141757d70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757d70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757db0
        g_nCalls = 0;
        void* pB = SynSet2_141757db0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757db0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757e30
        g_nCalls = 0;
        void* pB = SynSet2_141757e30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757e30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757e70
        g_nCalls = 0;
        void* pB = SynSet2_141757e70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757e70(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757ed0
        g_nCalls = 0;
        void* pB = SynSet2_141757ed0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757ed0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141757f30
        g_nCalls = 0;
        void* pB = SynSet2_141757f30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141757f30(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417765f0
        g_nCalls = 0;
        void* pB = SynSet2_1417765f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417765f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141776860
        g_nCalls = 0;
        void* pB = SynSet2_141776860(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141776860(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14177ac20
        g_nCalls = 0;
        void* pB = SynSet2_14177ac20(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14177ac20(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14177adb0
        g_nCalls = 0;
        void* pB = SynSet2_14177adb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14177adb0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14178a440
        g_nCalls = 0;
        void* pB = SynSet2_14178a440(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14178a440(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14178a4a0
        g_nCalls = 0;
        void* pB = SynSet2_14178a4a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14178a4a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14178aaa0
        g_nCalls = 0;
        void* pB = SynSet2_14178aaa0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14178aaa0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x14178aae0
        g_nCalls = 0;
        void* pB = SynSet2_14178aae0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_14178aae0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141793330
        g_nCalls = 0;
        void* pB = SynSet2_141793330(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141793330(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141793370
        g_nCalls = 0;
        void* pB = SynSet2_141793370(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141793370(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141793510
        g_nCalls = 0;
        void* pB = SynSet2_141793510(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141793510(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141793590
        g_nCalls = 0;
        void* pB = SynSet2_141793590(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141793590(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417945d0
        g_nCalls = 0;
        void* pB = SynSet2_1417945d0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417945d0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x141794630
        g_nCalls = 0;
        void* pB = SynSet2_141794630(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_141794630(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417a76a0
        g_nCalls = 0;
        void* pB = SynSet2_1417a76a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417a76a0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417a7820
        g_nCalls = 0;
        void* pB = SynSet2_1417a7820(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417a7820(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c7aa0
        g_nCalls = 0;
        void* pB = SynSet2_1417c7aa0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c7aa0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c7b40
        g_nCalls = 0;
        void* pB = SynSet2_1417c7b40(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c7b40(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c7b80
        g_nCalls = 0;
        void* pB = SynSet2_1417c7b80(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c7b80(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c83f0
        g_nCalls = 0;
        void* pB = SynSet2_1417c83f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c83f0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c8700
        g_nCalls = 0;
        void* pB = SynSet2_1417c8700(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c8700(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c9ac0
        g_nCalls = 0;
        void* pB = SynSet2_1417c9ac0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c9ac0(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }
    {   // 0x1417c9d50
        g_nCalls = 0;
        void* pB = SynSet2_1417c9d50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);   // third argument was non-null, the slot stays unused
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == (void*)0x1234);
        CHECK(*(void**)((uint8_t*)aThis + 8) == (void*)0x77);
        g_nCalls = 0; g_t = 0;
        *(void**)aSecond = (void*)0x1234;
        pB = SynSet2_1417c9d50(aThis, (void*)0x77, aSecond);
        CHECK(g_nCalls == 0);
    }

    std::printf("SYNDICATE_THUNKS10_OK: 63 setters, %d checks\n", g_nChecks);
    return 0;
}
