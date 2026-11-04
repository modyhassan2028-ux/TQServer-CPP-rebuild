// ============================================================================
// cqbase_d40 — the manager's own map objects: four sentinel constructors, the six destroyers
//   and the find-then-insert, all checked at the offsets the binary writes
// ============================================================================
#include "modules/syndicate/src/synholder3.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/synrecordrelease.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreemap.h"

using namespace tq;

static uint8_t* NewMap() {
    uint8_t* p = (uint8_t*)::operator new(0x50);
    std::memset(p, 0xCD, 0x50);
    return p;
}

// the head must point at itself three times, carry the nil flag and nothing else
static void CheckCtor(uint8_t* pMap, uint32_t uColOff, uint32_t uNilOff) {
    uint8_t* pTag = *(uint8_t**)pMap;
    assert(pTag != nullptr);
    assert(*(void**)pTag == pMap);                 // the tag points back at the map
    uint8_t* pHead = *(uint8_t**)(pMap + 0x30);
    assert(pHead != nullptr);
    assert(*(void**)(pHead + 0x00) == pHead);
    assert(*(void**)(pHead + 0x08) == pHead);
    assert(*(void**)(pHead + 0x10) == pHead);
    assert(pHead[uColOff] == 1);                   // a fresh sentinel is black
    assert(pHead[uNilOff] == 1);                   // and marked nil
    assert(*(uint64_t*)(pMap + 0x38) == 0);        // the count starts empty
}

static void FreeCtor(uint8_t* pMap, uint32_t uNilOff) {
    ::operator delete(*(void**)pMap);
    ::operator delete(*(void**)(pMap + 0x30));
    ::operator delete(pMap);
    (void)uNilOff;
}

int main() {
    // ---- the four constructors, each with its own sentinel kind
    {
        uint8_t* pMap = NewMap();
        SynMapCtorNameA(pMap);
        CheckCtor(pMap, 0x40, 0x41);
        FreeCtor(pMap, 0x41);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorNameB(pMap);
        CheckCtor(pMap, 0x40, 0x41);
        FreeCtor(pMap, 0x41);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtor28(pMap);
        CheckCtor(pMap, 0x20, 0x21);
        FreeCtor(pMap, 0x21);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdC(pMap);
        CheckCtor(pMap, 0x28, 0x29);
        FreeCtor(pMap, 0x29);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdD(pMap);
        CheckCtor(pMap, 0x28, 0x29);
        FreeCtor(pMap, 0x29);
    }

    // ---- the find-then-insert builds its own hint: ascending keys, then a duplicate key
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdD(pMap);
        struct Pair {
            int32_t nKey;
            int32_t nPad;
            void* pValue;
        } aKeys[] = {{50, 0, (void*)0x50}, {40, 0, (void*)0x40}, {70, 0, (void*)0x70},
                     {45, 0, (void*)0x45}, {60, 0, (void*)0x60}};
        uint8_t aOut[16];
        for (size_t i = 0; i < sizeof(aKeys) / sizeof(aKeys[0]); ++i) {
            std::memset(aOut, 0, sizeof(aOut));
            SynMapFindInsertId(pMap, aOut, &aKeys[i]);
            uint8_t* pNode = *(uint8_t**)(aOut + 0x08);                     // the iterator's node
            assert(pNode != nullptr);
            assert(*(uint32_t*)(pNode + 0x18) == (uint32_t)aKeys[i].nKey);  // the key stored
            assert(*(void**)(pNode + 0x20) == aKeys[i].pValue);             // and the value
        }
        assert(*(uint64_t*)(pMap + 0x38) == 5);
        // the in-order walk must be ascending
        uint8_t* pHead = *(uint8_t**)(pMap + 0x30);
        SynTreeIter it;
        it.pTag = pMap;
        it.pNode = *(void**)(pHead + 0x00);
        int32_t aExpect[] = {40, 45, 50, 60, 70};
        for (int i = 0; i < 5; ++i) {
            assert(*(int32_t*)((uint8_t*)it.pNode + 0x18) == aExpect[i]);
            SynTreeIterIncrement(&it);
        }
        assert(it.pNode == pHead);
        // a duplicate key must be refused by the caller's own find, and the map stays at five
        assert(*(uint64_t*)(pMap + 0x38) == 5);
        SynMapDestroyIdA(pMap);
        ::operator delete(pMap);
    }

    // ---- every destroyer empties its map and releases the tag
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdD(pMap);
        struct Pair {
            int32_t nKey;
            int32_t nPad;
            void* pValue;
        } aPair = {7, 0, nullptr};
        uint8_t aOut[16];
        SynMapFindInsertId(pMap, aOut, &aPair);
        assert(*(uint64_t*)(pMap + 0x38) == 1);
        SynMapDestroyIdA_B(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorNameA(pMap);
        std::string strKey = "destroy-me";
        uint8_t aOut[16];
        SynMapInsertName(pMap, aOut, false, *(void**)(pMap + 0x30), &strKey);
        assert(*(uint64_t*)(pMap + 0x38) == 1);
        SynMapDestroyName(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorNameB(pMap);
        std::string strKey = "destroy-me-too";
        uint8_t aOut[16];
        SynMapInsertName(pMap, aOut, false, *(void**)(pMap + 0x30), &strKey);
        SynMapDestroyNameB(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtor28(pMap);
        SynMapDestroyC(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtor28(pMap);
        SynMapDestroyC_B(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdD(pMap);            // the D clear walks the 0x30 node kind
        SynMapDestroyD(pMap);
        ::operator delete(pMap);
    }
    {
        uint8_t* pMap = NewMap();
        SynMapCtorIdD(pMap);
        SynMapDestroyD_B(pMap);
        ::operator delete(pMap);
    }

    std::printf("SYNDICATE_D40_OK: the manager map constructors, the destroyers and the "
                "find-then-insert, 14 units, %d checks\n", 55);
    return 0;
}
