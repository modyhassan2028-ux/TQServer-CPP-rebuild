// Generated with family GX — for each body: below, equal and above the limit.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_gx.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static void* g_pSeen = nullptr; static int g_nRep = 0;
static void Hook(void* p) { ++g_nRep; g_pSeen = p; }
static unsigned char aThis[0x120], aA[0x80], aB[0x80];

static void put(void* p, uint64_t off, void* v) { *(void**)((unsigned char*)p + off) = v; }
static void* at(void* p, uint64_t off) { return *(void**)((unsigned char*)p + off); }

// evaluates the body's own condition in C++, so the expectation is not hand-written per case
static bool ShouldReport(const char* op, uintptr_t cur, uintptr_t lim) {
    if (op[0] == '>' && op[1] == '=') return cur >= lim;
    if (op[0] == '<' && op[1] == '=') return cur <= lim;
    if (op[0] == '>') return cur > lim;
    if (op[0] == '<') return cur < lim;
    if (op[0] == '=' && op[1] == '=') return cur == lim;
    if (op[0] == '!' && op[1] == '=') return cur != lim;
    std::abort();
}

int main() {
    g_fnGX_1418233c0 = &Hook;

    {   // 0x141722eb0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141722eb0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141722f80   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141722f80(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141723050   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141723050(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417231c0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417231c0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141724a60   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141724a60(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141724aa0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141724aa0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141724b00   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141724b00(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141724b60   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141724b60(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141724bf0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141724bf0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141725f10   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141725f10(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141725f50   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141725f50(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141725fe0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141725fe0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141726070   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141726070(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417260d0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417260d0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173ae00   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173ae00(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173af50   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173af50(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173b5c0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173b5c0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173b620   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173b620(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173ba50   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173ba50(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14173ba90   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14173ba90(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141744750   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141744750(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141744790   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141744790(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141745b50   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141745b50(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141745b90   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141745b90(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141746520   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141746520(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141746560   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141746560(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750450   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750450(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417504d0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417504d0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750570   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750570(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417505b0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417505b0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417505f0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417505f0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750630   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750630(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750720   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750720(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417507f0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417507f0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750830   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750830(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141750870   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141750870(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752900   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752900(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752940   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752940(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752980   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752980(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417529c0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417529c0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752a00   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752a00(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752a40   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752a40(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752b40   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752b40(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752ba0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752ba0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752be0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752be0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141752c20   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141752c20(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755070   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755070(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417550b0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417550b0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755110   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755110(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755150   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755150(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755190   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755190(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417551d0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417551d0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755210   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755210(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755250   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755250(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141755290   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141755290(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417552d0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417552d0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141775ff0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141775ff0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417762c0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417762c0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141776580   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141776580(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14177a580   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14177a580(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14177a8e0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14177a8e0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14177ab00   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14177ab00(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141789d30   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141789d30(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141789e00   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141789e00(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14178a300   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14178a300(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14178a360   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14178a360(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14178a3e0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14178a3e0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x14178a940   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_14178a940(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141791e20   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141791e20(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141791e60   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141791e60(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141791ea0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141791ea0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141791ee0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141791ee0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141793000   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141793000(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141793040   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141793040(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141793080   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141793080(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417930c0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417930c0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417932f0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417932f0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x141794320   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_141794320(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417a7070   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417a7070(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417a73a0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417a73a0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417a7530   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417a7530(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417c7320   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417c7320(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417c78e0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417c78e0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417c7930   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417c7930(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417c7ae0   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417c7ae0(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }
    {   // 0x1417c9060   lim +0x30, cur +0x8, add 0x18, jne
        const uintptr_t uLim = 0x1000;
        const uintptr_t uCases[3] = { 0xF00, 0x1000, 0x1100 };
        for (int i = 0; i < 3; ++i) {
            std::memset(aThis, 0, sizeof(aThis));
            put(aThis, 0x0, aA); put(aA, 0x0, aB); put(aB, 0x30, (void*)uLim);
            put(aThis, 0x8, (void*)uCases[i]);
            g_nRep = 0; g_pSeen = nullptr;
            void* pR = SynProbeGX_1417c9060(aThis);
            CHECK(g_nRep == (ShouldReport("==", uCases[i], uLim) ? 1 : 0));
            if (g_nRep) CHECK(g_pSeen == (void*)aThis);
            CHECK(pR == (uint8_t*)uCases[i] + 0x18);
        }
    }

    std::printf("SYNDICATE_THUNKS_GX_OK: 86 bodies, %d checks\n", g_nChecks);
    return 0;
}
