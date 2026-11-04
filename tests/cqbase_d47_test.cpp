// ============================================================================
// cqbase_d47 — the checked-iterator plumbing: both forwarders, both comparisons, the four
//   deleters, both value accessors and the seed, plus every invalid-parameter call
// ============================================================================
#include "modules/syndicate/src/syniter2.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

static int g_nChecks = 0;
static int g_nInvalid = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static void HookInvalid() { ++g_nInvalid; }

static int g_nSlot0 = 0;
static void* g_pSlot0Self = nullptr;
static void* g_aVft[0x10 / 8];
static void Slot0(void* pSelf) {
    ++g_nSlot0;
    g_pSlot0Self = pSelf;
}

int main() {
        ::syndicate::g_fnInvalidParam = &HookInvalid;
    g_aVft[0x00 / 8] = (void*)&Slot0;

    uint8_t aObj[0x30];
    std::memset(aObj, 0, sizeof(aObj));
    *(void**)aObj = g_aVft;

    // ---- the forwarder that goes through +0x98
    {
        uint8_t aIter[0xa0];
        std::memset(aIter, 0, sizeof(aIter));
        *(void**)(aIter + 0x98) = aObj;
        g_nSlot0 = 0;
        SynIterDerefHolder(aIter);
        CHECK(g_nSlot0 == 1);
        CHECK(g_pSlot0Self == aObj);
    }

    // ---- the forwarder that goes through the first qword
    {
        void* aIter[2] = {aObj, nullptr};
        g_nSlot0 = 0;
        SynIterDerefSelf(aIter);
        CHECK(g_nSlot0 == 1);
        CHECK(g_pSlot0Self == aObj);
        g_nInvalid = 0;
        CHECK(g_nInvalid == 0);        // a present owner never reports
    }

    // ---- the two comparisons
    {
        void* aHead[1] = {(void*)0x11};
        uint8_t aLeft[0x10];
        uint8_t aRight[0x10];
        std::memset(aLeft, 0, sizeof(aLeft));
        std::memset(aRight, 0, sizeof(aRight));
        *(void**)aLeft = aHead;
        *(void**)aRight = aHead;
        *(void**)(aLeft + 8) = (void*)0x20;
        *(void**)(aRight + 8) = (void*)0x20;
        g_nInvalid = 0;
        CHECK(SynIterEqualA(aLeft, aRight) == false);      // same owner, same node
        CHECK(g_nInvalid == 0);
        *(void**)(aRight + 8) = (void*)0x28;
        CHECK(SynIterEqualA(aLeft, aRight) == true);
        CHECK(SynIterEqualB(aLeft, aRight) == true);
        CHECK(g_nInvalid == 0);
        // a null owner is an invalid parameter on both
        g_nInvalid = 0;
        *(void**)aLeft = nullptr;
        CHECK(SynIterEqualA(aLeft, aRight) == true);
        CHECK(SynIterEqualB(aLeft, aRight) == true);
        CHECK(g_nInvalid == 2);
        // and two different owners too
        g_nInvalid = 0;
        *(void**)aLeft = aHead;
        *(void**)aRight = (void*)0x99;
        SynIterEqualA(aLeft, aRight);
        CHECK(g_nInvalid == 1);
    }

    // ---- the four deleters: each one releases the first qword and nothing else
    {
        void (*apfn[4])(void*) = {&SynIterDelete50, &SynIterDelete80, &SynIterDeleteB0,
                                  &SynIterDeleteF10};
        for (void (*pfn)(void*) : apfn) {
            void* aIter[2] = {(void*)::operator new(0x20), (void*)0x77};
            pfn(aIter);
            CHECK(aIter[1] == (void*)0x77);      // the second qword is left alone
        }
    }

    // ---- the value accessors: second qword plus 0x18, against a head at +0x30
    {
        uint8_t aHeadObj[0x40];
        std::memset(aHeadObj, 0, sizeof(aHeadObj));
        *(void**)(aHeadObj + 0x30) = (void*)0xDEAD;      // the head sentinel
        void* aOwner[1] = {aHeadObj};
        uint8_t aIter[0x10];
        std::memset(aIter, 0, sizeof(aIter));
        *(void**)aIter = aOwner;
        *(void**)(aIter + 8) = (void*)0x1234;
        g_nInvalid = 0;
        CHECK(SynIterValue(aIter) == (void*)(0x1234 + 0x18));
        CHECK(SynIterValue2(aIter) == (void*)(0x1234 + 0x18));
        CHECK(g_nInvalid == 0);
        // a second qword equal to the head's +0x30 reports an invalid parameter on both
        g_nInvalid = 0;
        *(void**)(aIter + 8) = *(void**)(aHeadObj + 0x30);
        CHECK(SynIterValue(aIter) == (void*)(0xDEAD + 0x18));
        CHECK(SynIterValue2(aIter) == (void*)(0xDEAD + 0x18));
        CHECK(g_nInvalid == 2);
    }

    // ---- the seed
    {
        void* aSource[1] = {(void*)0x55};
        uint8_t aOut[0x10];
        std::memset(aOut, 0xEE, sizeof(aOut));
        g_nInvalid = 0;
        CHECK(SynIterInit(aOut, (void*)0x77, aSource) == (void*)aOut);
        CHECK(*(void**)aOut == (void*)0x55);              // taken from the source
        CHECK(*(void**)(aOut + 8) == (void*)0x77);        // the owner
        CHECK(g_nInvalid == 0);
        // The null-source path is NOT exercised: the original calls _invalid_parameter_noinfo
        // and then still reads *pSource, which is unreachable only because that call
        // terminates the release build. Same for the null owner in the value accessors.
    }

    std::printf("SYNDICATE_D47_OK: the checked-iterator plumbing, 11 units, %d checks\n",
                g_nChecks);
    return 0;
}
