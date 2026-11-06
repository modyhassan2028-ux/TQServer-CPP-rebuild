// Generated with family X — the guarded and the skipped path of every body.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_x.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_v = 0; static int g_nCalls = 0;
static void Hook(void* p) { g_v = (uintptr_t)p; ++g_nCalls; }

int main() {
    g_fnXD14176b050 = &Hook;
    g_fnXD14176f3b0 = &Hook;
    g_fnXD1417e0da0 = &Hook;
    g_fnXS141823290 = &Hook;
    static unsigned char aObj[0x148];

    {   // 0x141805fe0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x40) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141805fe0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x40) = 0xBEEF;
        SynGuard_141805fe0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141806740
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x40) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141806740(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x40) = 0xBEEF;
        SynGuard_141806740(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181e450
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e450(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_14181e450(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181e480
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e480(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181e480(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181e4b0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e4b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181e4b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181e570
        *(uint32_t*)(aObj + 0xa0) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xf0) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e570(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xa0) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xa0) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xf0) = 0xBEEF;
        SynGuard_14181e570(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xa0) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181e670
        *(uint32_t*)(aObj + 0xb8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e670(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xb8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xb8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181e670(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xb8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181e6b0
        *(uint32_t*)(aObj + 0x90) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x68) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e6b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x68) = 0xBEEF;
        SynGuard_14181e6b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x68));
    }
    {   // 0x14181e6e0
        *(uint32_t*)(aObj + 0x90) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e6e0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffd);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181e6e0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181e760
        *(uint32_t*)(aObj + 0x90) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x68) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e760(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x68) = 0xBEEF;
        SynGuard_14181e760(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x68));
    }
    {   // 0x14181e790
        *(uint32_t*)(aObj + 0x90) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e790(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffd);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181e790(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181e7d0
        *(uint32_t*)(aObj + 0x90) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x68) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e7d0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x68) = 0xBEEF;
        SynGuard_14181e7d0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x68));
    }
    {   // 0x14181e800
        *(uint32_t*)(aObj + 0x90) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e800(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x90) == 0xfffffffd);
        *(uint32_t*)(aObj + 0x90) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181e800(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x90) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181e860
        *(uint32_t*)(aObj + 0x50) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x88) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e860(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x50) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x50) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x88) = 0xBEEF;
        SynGuard_14181e860(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x50) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181e8b0
        *(uint32_t*)(aObj + 0x50) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x88) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181e8b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x50) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x50) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x88) = 0xBEEF;
        SynGuard_14181e8b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x50) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181ea50
        *(uint32_t*)(aObj + 0xd0) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x100) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181ea50(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xd0) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xd0) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x100) = 0xBEEF;
        SynGuard_14181ea50(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xd0) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181ef50
        *(uint32_t*)(aObj + 0x108) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x38) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181ef50(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x108) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x108) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x38) = 0xBEEF;
        SynGuard_14181ef50(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x108) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x38));
    }
    {   // 0x14181efa0
        *(uint32_t*)(aObj + 0x108) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xc8) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181efa0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x108) == 0xfffffffd);
        *(uint32_t*)(aObj + 0x108) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xc8) = 0xBEEF;
        SynGuard_14181efa0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x108) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0xc8));
    }
    {   // 0x14181efe0
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181efe0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181efe0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f070
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f070(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f070(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f0a0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f0a0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181f0a0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181f0d0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffb;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xb8) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f0d0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffb);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaae;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xb8) = 0xBEEF;
        SynGuard_14181f0d0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaae & 0xfffffffb));
        CHECK(g_v == (uintptr_t)(aObj + 0xb8));
    }
    {   // 0x14181f110
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f110(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f110(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f180
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f180(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f180(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f1b0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f1b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181f1b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181f1e0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffb;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xb8) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f1e0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffb);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaae;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xb8) = 0xBEEF;
        SynGuard_14181f1e0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaae & 0xfffffffb));
        CHECK(g_v == (uintptr_t)(aObj + 0xb8));
    }
    {   // 0x14181f280
        *(uint32_t*)(aObj + 0xb0) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f280(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xb0) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xb0) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f280(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xb0) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f2b0
        *(uint32_t*)(aObj + 0xb0) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f2b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xb0) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xb0) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181f2b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xb0) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181f390
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f390(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f390(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f3c0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f3c0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181f3c0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181f3f0
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffb;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xb8) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f3f0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffb);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaae;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xb8) = 0xBEEF;
        SynGuard_14181f3f0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaae & 0xfffffffb));
        CHECK(g_v == (uintptr_t)(aObj + 0xb8));
    }
    {   // 0x14181f430
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f430(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f430(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f460
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f460(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f460(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f530
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f530(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffe);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_14181f530(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x14181f560
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffd;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x70) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f560(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffd);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaaa;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x70) = 0xBEEF;
        SynGuard_14181f560(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaaa & 0xfffffffd));
        CHECK(g_v == (uintptr_t)(aObj + 0x70));
    }
    {   // 0x14181f590
        *(uint32_t*)(aObj + 0xf8) = 0xfffffffb;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0xb8) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f590(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0xf8) == 0xfffffffb);
        *(uint32_t*)(aObj + 0xf8) = 0xaaaaaaae;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0xb8) = 0xBEEF;
        SynGuard_14181f590(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0xf8) == (0xaaaaaaae & 0xfffffffb));
        CHECK(g_v == (uintptr_t)(aObj + 0xb8));
    }
    {   // 0x14181f660
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f660(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_14181f660(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x14181f690
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f690(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_14181f690(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181f6c0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f6c0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_14181f6c0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181f890
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181f890(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_14181f890(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x14181fb40
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181fb40(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_14181fb40(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x14181fc10
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181fc10(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_14181fc10(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x14181fc40
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181fc40(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_14181fc40(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181fc70
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181fc70(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_14181fc70(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x14181fdc0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_14181fdc0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_14181fdc0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820070
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820070(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820070(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820100
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820100(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820100(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820130
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820130(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141820130(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820160
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820160(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141820160(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820330
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820330(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820330(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x1418205e0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418205e0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_1418205e0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x1418206b0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418206b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_1418206b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x1418206e0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418206e0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_1418206e0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820710
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820710(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141820710(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820880
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820880(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820880(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820b70
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820b70(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820b70(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820c80
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820c80(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820c80(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141820cb0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820cb0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141820cb0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820ce0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820ce0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141820ce0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141820e70
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141820e70(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141820e70(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141821160
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821160(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141821160(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141821230
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821230(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141821230(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141821260
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821260(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_141821260(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x1418213f0
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x48) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418213f0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x48) = 0xBEEF;
        SynGuard_1418213f0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)0xBEEF);
    }
    {   // 0x141821420
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821420(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141821420(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141821570
        *(uint32_t*)(aObj + 0x20) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x30) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821570(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x20) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x20) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x30) = 0xBEEF;
        SynGuard_141821570(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x20) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x30));
    }
    {   // 0x141821780
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821780(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_141821780(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x1418217b0
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418217b0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_1418217b0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x1418217e0
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_1418217e0(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_1418217e0(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x141821810
        *(uint32_t*)(aObj + 0x68) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x28) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821810(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x68) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x68) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x28) = 0xBEEF;
        SynGuard_141821810(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x68) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x28));
    }
    {   // 0x141821840
        *(uint32_t*)(aObj + 0x80) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x40) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821840(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x80) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x80) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x40) = 0xBEEF;
        SynGuard_141821840(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x80) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x40));
    }
    {   // 0x141821880
        *(uint32_t*)(aObj + 0x80) = 0xfffffffe;   // bit clear: nothing may happen
        *(uint64_t*)(aObj + 0x40) = 0xDEAD;
        g_nCalls = 0; g_v = 0;
        SynGuard_141821880(nullptr, aObj);
        CHECK(g_nCalls == 0);
        CHECK(*(uint32_t*)(aObj + 0x80) == 0xfffffffe);
        *(uint32_t*)(aObj + 0x80) = 0xaaaaaaab;   // bit set: clear it, then call
        *(uint64_t*)(aObj + 0x40) = 0xBEEF;
        SynGuard_141821880(nullptr, aObj);
        CHECK(g_nCalls == 1);
        CHECK(*(uint32_t*)(aObj + 0x80) == (0xaaaaaaab & 0xfffffffe));
        CHECK(g_v == (uintptr_t)(aObj + 0x40));
    }

    std::printf("SYNDICATE_THUNKS_X_OK: 72 bodies, %d checks\n", g_nChecks);
    return 0;
}
