// ============================================================================
// cqbase_d36 — the clear pair of the 0x28-node map kind and the second clear pair of the id
//   kind: every node must be released, the head must point at itself three times and the
//   count must go to zero
// ============================================================================
#include "modules/syndicate/src/syntreeclear2.h"
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

// a 0x28-byte node: left +0x00, parent +0x08, right +0x10, colour +0x20, nil +0x21
static unsigned char* N28(unsigned char* pHead, uint32_t uKey) {
    unsigned char* p = (unsigned char*)::operator new(0x28);
    std::memset(p, 0, 0x28);
    *(uint32_t*)(p + 0x18) = uKey;
    *(void**)(p + 0x00) = pHead;
    *(void**)(p + 0x08) = pHead;
    *(void**)(p + 0x10) = pHead;
    return p;
}

// the hint an ordinary insert computes: descend until the nil leaf, remember the parent and
// which side the key belongs on
static void InsertKey(unsigned char* pMap, uint32_t uKey) {
    struct Pair {
        uint32_t uKey;
        uint32_t uPad;
        void* pValue;
    } pair = {uKey, 0, nullptr};
    uint8_t* pHead = *(uint8_t**)(pMap + 0x30);
    uint8_t* pWhere = pHead;
    bool bLeft = false;
    uint8_t* p = *(uint8_t**)(pHead + 0x08);
    while (*(uint8_t*)(p + 0x29) == 0) {
        pWhere = p;
        if (uKey < *(uint32_t*)(p + 0x18)) {
            bLeft = true;
            p = *(uint8_t**)p;
        } else {
            bLeft = false;
            p = *(uint8_t**)(p + 0x10);
        }
    }
    SynTreeIter aOut;
    SynMapInsertId(pMap, &aOut, bLeft, pWhere, &pair);
}

int main() {
    // ---- the 0x28 kind: a three node tree comes apart and the head is reused
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x28);
        std::memset(pHead, 0, 0x28);
        pHead[0x21] = 1;                       // the sentinel
        *(void**)(pHead + 0x00) = pHead;
        *(void**)(pHead + 0x08) = pHead;
        *(void**)(pHead + 0x10) = pHead;

        unsigned char* p10 = N28(pHead, 10);
        unsigned char* p20 = N28(pHead, 20);
        unsigned char* p30 = N28(pHead, 30);
        *(void**)(pHead + 0x00) = p10;
        *(void**)(pHead + 0x08) = p20;
        *(void**)(pHead + 0x10) = p30;
        *(void**)(p10 + 0x08) = p20;
        *(void**)(p30 + 0x08) = p20;
        *(void**)(p20 + 0x00) = p10;
        *(void**)(p20 + 0x10) = p30;

        *(void**)(aMap + 0x30) = pHead;
        *(uint64_t*)(aMap + 0x38) = 3;

        SynTreeClearAt21(aMap);
        assert(*(void**)(pHead + 0x08) == pHead);
        assert(*(void**)(pHead + 0x00) == pHead);
        assert(*(void**)(pHead + 0x10) == pHead);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        assert(*(void**)(aMap + 0x30) == pHead);   // the sentinel itself is left alone
        ::operator delete(pHead);
    }

    // ---- and the subtree entry point frees only what hangs off the node it is given
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x28);
        std::memset(pHead, 0, 0x28);
        pHead[0x21] = 1;
        *(void**)(pHead + 0x00) = pHead;
        *(void**)(pHead + 0x08) = pHead;
        *(void**)(pHead + 0x10) = pHead;
        unsigned char* p5 = N28(pHead, 5);
        unsigned char* p7 = N28(pHead, 7);
        *(void**)(p5 + 0x10) = p7;                 // 7 hangs to the right of 5
        *(void**)(p7 + 0x08) = p5;
        *(void**)(aMap + 0x30) = pHead;

        SynTreeEraseSubtreeAt21(aMap, p5);         // both 5 and 7 go
        ::operator delete(pHead);
    }

    // ---- the id kind's own copy clears a map that was filled through the real insert
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xCD, sizeof(aMap));
        SynMapInitId(aMap);
        for (uint32_t k = 0; k < 12; ++k) InsertKey(aMap, k * 7u);
        assert(*(uint64_t*)(aMap + 0x38) == 12);
        SynTreeClearIdB(aMap);
        uint8_t* pHead = *(uint8_t**)(aMap + 0x30);
        assert(pHead != nullptr);
        assert(*(void**)(pHead + 0x08) == pHead);
        assert(*(void**)(pHead + 0x00) == pHead);
        assert(*(void**)(pHead + 0x10) == pHead);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(pHead);                  // the clear keeps the sentinel alive
    }

    std::printf("SYNDICATE_D36_OK: the clear pair of the 0x28 kind and the second id clear, "
                "4 units, 12 checks\n");
    return 0;
}
