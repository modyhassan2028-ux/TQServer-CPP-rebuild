// Generated with family W — both paths of every body.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_w.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_a = 0, g_b = 0, g_c = 0, g_d = 0; static int g_nCalls = 0;
static void* Hook(void* a, void* b, void* c, void* d) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_c = (uintptr_t)c; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x77; }

static unsigned char g_buf[0x400];

int main() {
    g_fnW_1418232a8 = &Hook;
    unsigned char* pBase = g_buf + 0x200;

    {   // 0x1417243e0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417243e0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417243e0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141724480
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141724480(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141724480(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141725c20
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141725c20(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141725c20(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141725c70
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141725c70(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141725c70(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141727380
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141727380(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141727380(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141727450
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141727450(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141727450(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417400d0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417400d0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417400d0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417404d0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417404d0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417404d0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141740860
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141740860(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141740860(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417452a0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417452a0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417452a0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141746130
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141746130(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141746130(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141746440
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x4;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141746440(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x4));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x4));
        CHECK(g_d == (1 * 0x4));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141746440(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141746d00
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141746d00(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141746d00(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141752100
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141752100(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141752100(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141754a00
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141754a00(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141754a00(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141754d30
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141754d30(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141754d30(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141756d50
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141756d50(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141756d50(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141778840
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141778840(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141778840(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141791660
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141791660(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141791660(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141792840
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141792840(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141792840(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141792aa0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141792aa0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141792aa0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x141793980
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_141793980(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_141793980(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a3190
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a3190(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a3190(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a31d0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a31d0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a31d0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a3860
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a3860(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a3860(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a38a0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a38a0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a38a0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a3b90
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a3b90(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a3b90(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a3fe0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a3fe0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a3fe0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417a4050
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417a4050(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417a4050(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417d1b40
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417d1b40(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417d1b40(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417d1fa0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417d1fa0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417d1fa0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417d21f0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417d21f0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417d21f0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }
    {   // 0x1417d24d0
        unsigned char* pBegin = g_buf + 0x40;
        unsigned char* pEnd = pBegin + 0x8;   // exactly one element
        g_nCalls = 0;
        void* pR = SynRng_1417d24d0(pBegin, pEnd, pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_c == (uintptr_t)pBegin);
        CHECK((uintptr_t)pR == (uintptr_t)pBase - (1 * 0x8));
        CHECK(g_a == (uintptr_t)pR);
        CHECK(g_b == (1 * 0x8));
        CHECK(g_d == (1 * 0x8));
        // same pointers: the count is zero, the call must be skipped
        g_nCalls = 0;
        pR = SynRng_1417d24d0(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK((uintptr_t)pR == (uintptr_t)pBase);
    }

    std::printf("SYNDICATE_THUNKS_W_OK: 33 bodies, %d checks\n", g_nChecks);
    return 0;
}
