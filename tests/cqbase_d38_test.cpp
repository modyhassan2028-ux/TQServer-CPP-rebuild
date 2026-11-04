// ============================================================================
// cqbase_d38 — four more holder constructors and the id map's iterator distance
// ============================================================================
#include "modules/syndicate/src/synholder2.h"
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

int main() {
    // ---- every holder stores its owner and puts itself at the owner's first word
    {
        void* (*apfn[])(void*) = {&SynMapCtorHolderC, &SynMapCtorHolderD, &SynMapCtorHolderE,
                                  &SynMapCtorHolderF};
        for (void* (*pfn)(void*) : apfn) {
            unsigned char aOwner[0x10];
            std::memset(aOwner, 0xCD, sizeof(aOwner));
            void* pBack = pfn(aOwner);
            CHECK(pBack == aOwner);
            void** ppHolder = *(void***)aOwner;
            CHECK(ppHolder != nullptr);
            CHECK(*ppHolder == aOwner);                   // the holder points back at its owner
            CHECK(*(uint64_t*)(aOwner + 0x08) == 0xCDCDCDCDCDCDCDCDull);
            ::operator delete(ppHolder);
        }
    }

    // ---- the distance walks the in-order list from first to last
    {
        unsigned char aMap[0x50];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)aMap = aMap;
        SynMapInitId(aMap);
        uint8_t* pHead = *(uint8_t**)(aMap + 0x30);

        uint32_t aKeys[] = {50, 30, 70, 20, 40, 60, 80, 10};
        for (uint32_t uKey : aKeys) {
            struct Pair {
                uint32_t uKey;
                uint32_t uPad;
                void* pValue;
            } aPair = {uKey, 0, nullptr};
            uint8_t* pWhere = pHead;
            bool bLeft = false;
            uint8_t* pWalk = *(uint8_t**)(pHead + 0x08);
            while (pWalk[0x29] == 0) {
                pWhere = pWalk;
                if (uKey < *(uint32_t*)(pWalk + 0x18)) {
                    bLeft = true;
                    pWalk = *(uint8_t**)pWalk;
                } else {
                    bLeft = false;
                    pWalk = *(uint8_t**)(pWalk + 0x10);
                }
            }
            SynTreeIter aOut;
            SynMapInsertId(aMap, &aOut, bLeft, pWhere, &aPair);
        }
        CHECK(*(uint64_t*)(aMap + 0x38) == 8);

        // first = the leftmost node, last = the head
        SynTreeIter aFirst;
        aFirst.pTag = aMap;
        aFirst.pNode = *(void**)(pHead + 0x00);
        SynTreeIter aLast;
        aLast.pTag = aMap;
        aLast.pNode = pHead;

        int64_t nCount = 0;
        SynTreeIterDistanceId(&aFirst, &aLast, &nCount);
        CHECK(nCount == 8);
        // the binary works on local copies, so the caller's iterators are untouched
        CHECK(*(uint32_t*)((uint8_t*)aFirst.pNode + 0x18) == 10);
        CHECK(aLast.pNode == pHead);

        // an empty range counts nothing and does not move
        int64_t nZero = 0;
        SynTreeIter aSame = aLast;
        SynTreeIterDistanceId(&aSame, &aLast, &nZero);
        CHECK(nZero == 0);

        // and a partial range counts exactly the entries it crosses
        int64_t nRange = 0;
        SynTreeIter aBegin;
        aBegin.pTag = aMap;
        aBegin.pNode = *(void**)(pHead + 0x00);
        SynTreeIter aEndAt = aBegin;
        // walk three entries forward with the distance over a range built by stepping the walk
        for (int i = 0; i < 3; ++i) SynTreeIterIncrement(&aEndAt);
        SynTreeIterDistanceId(&aBegin, &aEndAt, &nRange);
        CHECK(nRange == 3);

        SynTreeIter aOut2;
        SynTreeIter aClearFirst;
        aClearFirst.pTag = aMap;
        aClearFirst.pNode = pHead;
        SynTreeIter aClearLast = aClearFirst;
        SynTreeEraseRange(aMap, &aOut2, &aClearFirst, &aClearLast);
        ::operator delete(*(void**)pHead);
    }

    std::printf("SYNDICATE_D38_OK: four more holders and the iterator distance, 5 units, %d checks\n",
                g_nChecks);
    return 0;
}
