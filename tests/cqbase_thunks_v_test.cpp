// Generated with family V — one check per body.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_v.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_v = 0; static int g_nCalls = 0;
static void* Hook(void* p) { g_v = (uintptr_t)p; ++g_nCalls; return (void*)0x4321; }

int main() {
    g_fnVS141823290 = &Hook;
    g_fnVS141823400 = &Hook;
    static unsigned char aObj[0x110];

    {   // 0x1417f5aa0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5aa0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5ae0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5ae0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5b20
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5b20(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5b60
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5b60(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5be0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5be0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5c40
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5c40(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5c80
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5c80(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5d00
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5d00(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5d60
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5d60(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5da0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5da0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5dc0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5dc0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f5de0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f5de0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f61c0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f61c0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f6200
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f6200(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f64a0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f64a0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x1417f6ff0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_1417f6ff0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e870
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e870(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e890
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e890(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e8b0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e8b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e930
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e930(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e990
        *(uint64_t*)(aObj + 0x48) = 0x9048;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e990(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9048);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180e9f0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180e9f0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180ebb0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180ebb0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180ecf0
        *(uint64_t*)(aObj + 0x48) = 0x9048;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180ecf0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9048);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180eff0
        *(uint64_t*)(aObj + 0xd0) = 0x90d0;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180eff0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x90d0);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14180f030
        *(uint64_t*)(aObj + 0x48) = 0x9048;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14180f030(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9048);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14181ebf0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14181ebf0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14181ec70
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14181ec70(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }
    {   // 0x14181ecb0
        *(uint64_t*)(aObj + 0x40) = 0x9040;
        g_nCalls = 0; g_v = 0;
        void* pB = SynFwd_14181ecb0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(g_v == 0x9040);
        CHECK(pB == (void*)0x4321);
    }

    std::printf("SYNDICATE_THUNKS_V_OK: 29 bodies, %d checks\n", g_nChecks);
    return 0;
}
