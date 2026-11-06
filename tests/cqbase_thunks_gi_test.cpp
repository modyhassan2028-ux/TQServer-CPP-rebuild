// Generated with family GI — both sides of the limit comparison, plus the report seam argument.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_gi.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static void* g_pSeen = nullptr; static int g_nRep = 0;
static void Hook(void* p) { ++g_nRep; g_pSeen = p; }
static unsigned char aThis[0x80], aA[0x80], aB[0x80];

static void put(void* p, uint64_t off, void* v) { *(void**)((unsigned char*)p + off) = v; }
static void* at(void* p, uint64_t off) { return *(void**)((unsigned char*)p + off); }

int main() {
    g_fnGI_1418233c0 = &Hook;

    {   // 0x141722a20   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141722a20(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141722a20(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141722a20(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141722b40   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141722b40(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141722b40(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141722b40(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141724690   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141724690(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141724690(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141724690(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141724770   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141724770(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141724770(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141724770(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x14174fb70   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_14174fb70(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_14174fb70(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_14174fb70(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x14174fc10   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_14174fc10(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_14174fc10(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_14174fc10(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141752560   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141752560(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141752560(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141752560(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417525e0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417525e0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417525e0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417525e0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417801b0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417801b0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417801b0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417801b0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141780230   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141780230(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141780230(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141780230(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141790620   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141790620(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141790620(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141790620(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x141791c80   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_141791c80(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_141791c80(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_141791c80(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417a2b40   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417a2b40(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417a2b40(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417a2b40(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417a35f0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417a35f0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417a35f0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417a35f0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b59e0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b59e0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b59e0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b59e0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b5ab0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b5ab0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b5ab0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b5ab0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b5b80   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b5b80(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b5b80(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b5b80(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b9b70   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b9b70(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b9b70(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b9b70(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b9c30   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b9c30(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b9c30(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b9c30(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417b9cf0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417b9cf0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417b9cf0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417b9cf0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417d1750   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417d1750(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417d1750(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417d1750(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }
    {   // 0x1417d1df0   lim +0x20, cur +0x8
        std::memset(aThis, 0, sizeof(aThis)); std::memset(aA, 0, sizeof(aA));
        put(aThis, 0x0, aA);      // this->f00
        put(aA, 0x0, aB);         // this->f00->f00
        put(aB, 0x20, (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x10);          // below the limit
        void* pR = SynProbe_1417d1df0(aThis);
        CHECK(g_nRep == 0);
        CHECK(pR == (void*)0x10);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x100);         // exactly at the limit: reports
        pR = SynProbe_1417d1df0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x100);
        g_nRep = 0; g_pSeen = nullptr;
        put(aThis, 0x8, (void*)0x1000);        // above the limit
        pR = SynProbe_1417d1df0(aThis);
        CHECK(g_nRep == 1); CHECK(g_pSeen == (void*)aThis);
        CHECK(pR == (void*)0x1000);
    }

    std::printf("SYNDICATE_THUNKS_GI_OK: 22 bodies, %d checks\n", g_nChecks);
    return 0;
}
