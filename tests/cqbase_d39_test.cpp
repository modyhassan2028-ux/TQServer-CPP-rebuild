// ============================================================================
// cqbase_d39 — the second id insert and the two-map teardown: the objects behind the entries
//   must be released through the entry's own slot, both trees must go, and both sentinels must
//   end up pointing at themselves
// ============================================================================
#include "modules/syndicate/src/synrecordrelease.h"
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static void* g_aObjVft[8];
static int g_nReleased = 0;
static void* g_aReleased[4];
static void ObjectDelete(void* pSelf, int nFlag) {
    g_aReleased[g_nReleased] = pSelf;
    ++g_nReleased;
    (void)nFlag;
}

static uint8_t* MakeIdNode(uint8_t* pHead, uint32_t uKey, void* pValue, uint8_t uColor) {
    uint8_t* p = (uint8_t*)::operator new(0x30);
    std::memset(p, 0, 0x30);
    *(uint8_t**)(p + 0x00) = pHead;
    *(uint8_t**)(p + 0x08) = pHead;
    *(uint8_t**)(p + 0x10) = pHead;
    *(uint32_t*)(p + 0x18) = uKey;
    *(void**)(p + 0x20) = pValue;
    p[0x28] = uColor;
    p[0x29] = 0;
    return p;
}

int main() {
    g_aObjVft[0] = (void*)&ObjectDelete;

    // ---- the B insert puts the entry where the A insert does
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)aMap = aMap;
        SynMapInitId(aMap);
        uint8_t* pHead = *(uint8_t**)(aMap + 0x30);
        struct Pair {
            uint32_t uKey;
            uint32_t uPad;
            void* pValue;
        } aKeys[] = {{10, 0, (void*)1}, {5, 0, (void*)2}, {20, 0, (void*)3}};
        for (Pair& rPair : aKeys) {
            uint8_t* pWhere = pHead;
            bool bLeft = false;
            uint8_t* pWalker = *(uint8_t**)(pHead + 0x08);
            while (pWalker[0x29] == 0) {
                pWhere = pWalker;
                if (rPair.uKey < *(uint32_t*)(pWalker + 0x18)) {
                    bLeft = true;
                    pWalker = *(uint8_t**)pWalker;
                } else {
                    bLeft = false;
                    pWalker = *(uint8_t**)(pWalker + 0x10);
                }
            }
            SynTreeIter aOut;
            SynMapInsertIdB(aMap, &aOut, bLeft, pWhere, &rPair);
        }
        CHECK(*(uint64_t*)(aMap + 0x38) == 3);
        SynTreeIter it;
        it.pTag = aMap;
        it.pNode = *(void**)(pHead + 0x00);
        CHECK(*(uint32_t*)((uint8_t*)it.pNode + 0x18) == 5);
        SynTreeIterIncrement(&it);
        CHECK(*(uint32_t*)((uint8_t*)it.pNode + 0x18) == 10);
        SynTreeIterIncrement(&it);
        CHECK(*(uint32_t*)((uint8_t*)it.pNode + 0x18) == 20);

        SynTreeIter aOut2;
        SynTreeIter aFirst;
        aFirst.pTag = aMap;
        aFirst.pNode = pHead;
        SynTreeIter aLast = aFirst;
        SynTreeEraseRange(aMap, &aOut2, &aFirst, &aLast);
        ::operator delete(*(void**)pHead);
    }

    // ---- the teardown: two entries with objects, one name entry, both sentinels reused
    {
        unsigned char* aOwner = (unsigned char*)::operator new(0x88);
        std::memset(aOwner, 0xCD, 0x88);
        *(void**)(aOwner + 0x08) = (void*)0x1111;
        *(void**)(aOwner + 0x48) = (void*)0x2222;

        // the id map: its sentinel is the map object itself
        uint8_t* pHead = (uint8_t*)::operator new(0x30);
        std::memset(pHead, 0, 0x30);
        *(uint8_t**)(pHead + 0x00) = pHead;
        *(uint8_t**)(pHead + 0x08) = pHead;
        *(uint8_t**)(pHead + 0x10) = pHead;
        pHead[0x28] = 1;
        pHead[0x29] = 1;
        *(void**)(aOwner + 0x38) = pHead;

        void* aObjA[1];
        void* aObjB[1];
        aObjA[0] = g_aObjVft;
        aObjB[0] = g_aObjVft;
        uint8_t* pRoot = MakeIdNode(pHead, 20, aObjA, 1);
        uint8_t* pLeft = MakeIdNode(pHead, 10, aObjB, 0);
        uint8_t* pRight = MakeIdNode(pHead, 30, nullptr, 0);
        *(uint8_t**)(pHead + 0x08) = pRoot;
        *(uint8_t**)(pHead + 0x00) = pLeft;
        *(uint8_t**)(pHead + 0x10) = pRight;
        *(uint8_t**)(pRoot + 0x00) = pLeft;
        *(uint8_t**)(pRoot + 0x10) = pRight;
        *(uint8_t**)(pLeft + 0x08) = pRoot;
        *(uint8_t**)(pRight + 0x08) = pRoot;
        *(uint64_t*)(aOwner + 0x40) = 3;

        // the name map at +0x78
        uint8_t* pNameHead = (uint8_t*)::operator new(0x48);
        std::memset(pNameHead, 0, 0x48);
        new (pNameHead + 0x18) std::string();
        *(uint8_t**)(pNameHead + 0x00) = pNameHead;
        *(uint8_t**)(pNameHead + 0x08) = pNameHead;
        *(uint8_t**)(pNameHead + 0x10) = pNameHead;
        pNameHead[0x40] = 1;
        pNameHead[0x41] = 1;
        *(void**)(aOwner + 0x78) = pNameHead;
        uint8_t* pNameNode = (uint8_t*)::operator new(0x48);
        std::memset(pNameNode, 0, 0x48);
        new (pNameNode + 0x18) std::string("alpha");
        *(uint8_t**)(pNameNode + 0x00) = pNameHead;
        *(uint8_t**)(pNameNode + 0x08) = pNameHead;
        *(uint8_t**)(pNameNode + 0x10) = pNameHead;
        pNameNode[0x40] = 1;
        pNameNode[0x41] = 0;
        *(uint8_t**)(pNameHead + 0x08) = pNameNode;
        *(uint8_t**)(pNameHead + 0x00) = pNameNode;
        *(uint8_t**)(pNameHead + 0x10) = pNameNode;
        *(uint64_t*)(aOwner + 0x80) = 1;

        g_nReleased = 0;
        CHECK(SynRecordReleaseMaps(aOwner) == 1);
        CHECK(g_nReleased == 2);                       // only the two entries holding objects
        CHECK(g_aReleased[0] == aObjB);                // in-order: 10 first, then 20
        CHECK(g_aReleased[1] == aObjA);
        CHECK(*(uint8_t**)(pHead + 0x00) == pHead);    // the id sentinel points at itself
        CHECK(*(uint8_t**)(pHead + 0x10) == pHead);
        CHECK(*(uint64_t*)(aOwner + 0x40) == 0);
        CHECK(*(uint8_t**)(pNameHead + 0x08) == pNameHead);
        CHECK(*(uint8_t**)(pNameHead + 0x00) == pNameHead);
        CHECK(*(uint8_t**)(pNameHead + 0x10) == pNameHead);
        CHECK(*(uint64_t*)(aOwner + 0x80) == 0);
        CHECK(*(void**)(aOwner + 0x08) == (void*)0x1111);
        CHECK(*(void**)(aOwner + 0x48) == (void*)0x2222);

        // the maps themselves are the caller's, the entries and the strings are gone
        ((std::string*)(pNameHead + 0x18))->~basic_string();
        ::operator delete(pNameHead);
        ::operator delete(pHead);
        ::operator delete(aOwner);
    }

    std::printf("SYNDICATE_D39_OK: the B insert and the two-map teardown, 2 units, %d checks\n",
                g_nChecks);
    return 0;
}
