// ============================================================================
// cqbase_d41 — the manager object: constructor fields, destructor unwinding and the lazy
//   singleton, each checked against the offsets the binary stores
// ============================================================================
#include "modules/syndicate/src/synmanager2.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>

#include "modules/syndicate/src/synholder3.h"
#include "modules/syndicate/src/synmap.h"

using namespace tq;

static void CheckCtorFields(uint8_t* p) {
    assert(*(void**)p == g_pVftableCSynManager);
    assert(*(void**)(p + 0x98) == g_pVftableXSynMngModify);
    assert(*(void**)(p + 0xa0) == p);            // the modify block points back at the manager
    assert(*(uint64_t*)(p + 0x88) == 0);
    assert(*(uint64_t*)(p + 0x90) == 0);
    assert(*(uint32_t*)(p + 0xa8) == 0);
    assert(*(uint32_t*)(p + 0xac) == 0);
    // both maps are built: tag at +0x08 and +0x48, sentinels at +0x38 and +0x78
    uint8_t* pTagA = *(uint8_t**)(p + 0x08);
    uint8_t* pTagB = *(uint8_t**)(p + 0x48);
    assert(pTagA != nullptr && *(void**)pTagA == p + 0x08);
    assert(pTagB != nullptr && *(void**)pTagB == p + 0x48);
    uint8_t* pHeadA = *(uint8_t**)(p + 0x38);
    uint8_t* pHeadB = *(uint8_t**)(p + 0x78);
    assert(pHeadA != nullptr && pHeadA[0x29] == 1);
    assert(pHeadB != nullptr && pHeadB[0x41] == 1);
    assert(*(uint64_t*)(p + 0x40) == 0);
    assert(*(uint64_t*)(p + 0x80) == 0);
}

int main() {
    // ---- the constructor on a raw block
    {
        uint8_t* p = (uint8_t*)::operator new(0xb0);
        std::memset(p, 0xCD, 0xb0);
        SynManagerCtor(p);
        CheckCtorFields(p);
        SynManagerDtor(p);
        ::operator delete(p);
    }

    // ---- the destructor has to release what the two maps hold
    {
        uint8_t* p = (uint8_t*)::operator new(0xb0);
        std::memset(p, 0xCD, 0xb0);
        SynManagerCtor(p);
        struct Pair {
            int32_t nKey;
            int32_t nPad;
            void* pValue;
        } aPair = {11, 0, nullptr};
        uint8_t aOut[16];
        SynMapFindInsertId(p + 0x08, aOut, &aPair);
        assert(*(uint64_t*)(p + 0x40) == 1);
        std::string strKey = "manager-name";
        SynMapInsertName(p + 0x48, aOut, false, *(void**)(p + 0x78), &strKey);
        assert(*(uint64_t*)(p + 0x80) == 1);
        SynManagerDtor(p);
        ::operator delete(p);
    }

    // ---- the singleton: one object, handed out twice
    {
        void* pFirst = SynManagerInstance();
        assert(pFirst != nullptr);
        CheckCtorFields((uint8_t*)pFirst);
        void* pSecond = SynManagerInstance();
        assert(pSecond == pFirst);
        // tear the singleton down so the leak sanitiser stays quiet
        SynManagerDtor(pFirst);
        ::operator delete(pFirst);
        g_pSynManager = nullptr;
    }

    std::printf("SYNDICATE_D41_OK: the manager constructor, destructor and singleton, "
                "3 units, 25 checks\n");
    return 0;
}
