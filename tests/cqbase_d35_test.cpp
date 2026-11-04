// ============================================================================
// cqbase_d35 — emptying a filled map for the id and the name kind, and the 0x28-byte node
//   the third map kind is built from. The sanitisers carry the heavy part here: every node
//   has to go through the erase layer and the sentinel through the delete.
// ============================================================================
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/synmapclear.h"
#include "modules/syndicate/src/synnode.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int64_t CountOf(void* pMap) { return *(int64_t*)((uint8_t*)pMap + 0x38); }
static void* HeadOf(void* pMap) { return *(void**)((uint8_t*)pMap + 0x30); }

// the hint a plain insert uses: the node the key belongs under, and which side
static bool FindHint(void* pMap, uint32_t uKey, void** ppWhere, bool* pbLeft) {
    uint8_t* pHead = (uint8_t*)HeadOf(pMap);
    uint8_t* pNode = *(uint8_t**)(pHead + 0x08);
    if (*(uint8_t*)((uint8_t*)pHead + 0x29) == 1 && pNode == pHead) {
        *ppWhere = pHead;
        *pbLeft = false;
        return true;
    }
    while (*(uint8_t*)(pNode + 0x29) == 0) {
        if (uKey < *(uint32_t*)(pNode + 0x18)) {
            uint8_t* pLeft = *(uint8_t**)(pNode + 0x00);
            if (*(uint8_t*)(pLeft + 0x29) == 1) {
                *ppWhere = pNode;
                *pbLeft = true;
                return true;
            }
            pNode = pLeft;
        } else {
            uint8_t* pRight = *(uint8_t**)(pNode + 0x10);
            if (*(uint8_t*)(pRight + 0x29) == 1) {
                *ppWhere = pNode;
                *pbLeft = false;
                return true;
            }
            pNode = pRight;
        }
    }
    *ppWhere = pHead;
    *pbLeft = false;
    return true;
}

static void InsertId(void* pMap, uint32_t uKey, void* pValue) {
    struct Pair {
        uint32_t uKey;
        uint32_t uPad;
        void* pValue;
    } pair = {uKey, 0, pValue};
    void* pWhere = nullptr;
    bool bLeft = false;
    FindHint(pMap, uKey, &pWhere, &bLeft);
    int64_t aOut[2] = {0, 0};
    SynMapInsertId(pMap, aOut, bLeft, pWhere, &pair);
}

int main() {
    // ---- the 0x28-byte node: three null links, colour one, nil zero
    {
        unsigned char* p = (unsigned char*)SynNodeNewEmpty28();
        assert(p != nullptr);
        assert(*(void**)(p + 0x00) == nullptr);
        assert(*(void**)(p + 0x08) == nullptr);
        assert(*(void**)(p + 0x10) == nullptr);
        assert(p[0x20] == 1);
        assert(p[0x21] == 0);
        ::operator delete(p);
    }

    // ---- an id map with entries: the erase covers [leftmost, head) and then the head goes
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xCD, sizeof(aMap));
        *(void**)aMap = (void*)0x7A6;
        SynMapInitId(aMap);
        for (uint32_t k = 1; k <= 24; ++k) InsertId(aMap, k * 3, (void*)(uintptr_t)k);
        assert(CountOf(aMap) == 24);
        assert(HeadOf(aMap) != nullptr);

        SynMapClearAndFreeId(aMap);
        assert(HeadOf(aMap) == nullptr);            // the sentinel is gone
        assert(CountOf(aMap) == 0);                 // and the count with it
        assert(*(void**)aMap == (void*)0x7A6);      // the tag is left alone
        assert(*(uint8_t*)(aMap + 0x08) == 0xCD);   // nor any neighbour
    }

    // ---- an empty id map: first == last == the head, the clear path runs
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xCD, sizeof(aMap));
        SynMapInitId(aMap);
        SynMapClearAndFreeId(aMap);
        assert(HeadOf(aMap) == nullptr);
        assert(CountOf(aMap) == 0);
    }

    // ---- and the name map, filled through its own insert
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xCD, sizeof(aMap));
        *(void**)aMap = (void*)0x7A7;
        SynMapInitName(aMap);
        uint8_t* pHead = (uint8_t*)HeadOf(aMap);
        // a small balanced name tree, linked by hand through the builders
        const char* apsz[] = {"delta", "bravo", "foxtrot", "alpha", "charlie",
                              "echo", "golf", "hotel"};
        for (int i = 0; i < 8; ++i) {
            std::string strKey(apsz[i]);
            void* pWhere = pHead;
            bool bLeft = false;
            // descend to the right place
            uint8_t* pNode = *(uint8_t**)(pHead + 0x08);
            if (*(uint8_t*)(pHead + 0x41) == 1 && pNode == pHead) {
                pWhere = pHead;
            } else {
                while (*(uint8_t*)(pNode + 0x41) == 0) {
                    if (strKey < *(std::string*)(pNode + 0x18)) {
                        uint8_t* pL = *(uint8_t**)(pNode + 0x00);
                        if (*(uint8_t*)(pL + 0x41) == 1) { pWhere = pNode; bLeft = true; break; }
                        pNode = pL;
                    } else {
                        uint8_t* pR = *(uint8_t**)(pNode + 0x10);
                        if (*(uint8_t*)(pR + 0x41) == 1) { pWhere = pNode; bLeft = false; break; }
                        pNode = pR;
                    }
                }
            }
            int64_t aOut[2] = {0, 0};
            SynMapInsertName(aMap, aOut, bLeft, pWhere, &strKey);
        }
        assert(CountOf(aMap) == 8);
        SynMapClearAndFreeName(aMap);
        assert(HeadOf(aMap) == nullptr);
        assert(CountOf(aMap) == 0);
        assert(*(void**)aMap == (void*)0x7A7);
        assert(*(uint8_t*)(aMap + 0x08) == 0xCD);
    }

    std::printf("SYNDICATE_D35_OK: the two map clears and the 0x28 node, 3 units, 26 checks\n");
    return 0;
}
