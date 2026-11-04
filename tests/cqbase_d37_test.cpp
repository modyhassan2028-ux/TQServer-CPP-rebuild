// ============================================================================
// cqbase_d37 — the third and fourth erase families: the step, the node erase with its
//   fixup, the range erase and the clear that frees the sentinel. Every check reads the
//   kind's own colour and nil bytes.
// ============================================================================
#include "modules/syndicate/src/synerase2.h"
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/syntreeclear2.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string>
#include <set>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

// ---------------------------------------------------------------- 0x28 kind
static uint8_t* Make28(uint32_t uKey, uint8_t uColor, uint8_t* pHead) {
    uint8_t* p = (uint8_t*)::operator new(0x28);
    std::memset(p, 0, 0x28);
    *(uint8_t**)(p + 0x00) = pHead;
    *(uint8_t**)(p + 0x08) = pHead;
    *(uint8_t**)(p + 0x10) = pHead;
    *(uint32_t*)(p + 0x18) = uKey;
    p[0x20] = uColor;      // 1 black, 0 red
    p[0x21] = 0;
    return p;
}

static uint8_t* MakeHead28() {
    uint8_t* p = (uint8_t*)::operator new(0x28);
    std::memset(p, 0, 0x28);
    *(uint8_t**)(p + 0x00) = p;
    *(uint8_t**)(p + 0x08) = p;
    *(uint8_t**)(p + 0x10) = p;
    p[0x20] = 1;
    p[0x21] = 1;
    return p;
}

static void Walk28(uint8_t* pNode, uint8_t* pHead, std::vector<uint32_t>* pOut) {
    if (pNode[0x21] != 0) return;
    Walk28(*(uint8_t**)pNode, pHead, pOut);
    pOut->push_back(*(uint32_t*)(pNode + 0x18));
    Walk28(*(uint8_t**)(pNode + 0x10), pHead, pOut);
}

// -1 means the subtree breaks a rule
static int BlackHeight28(uint8_t* pNode) {
    if (pNode[0x21] != 0) return 1;
    if (pNode[0x20] == 0) {
        uint8_t* pLeft = *(uint8_t**)pNode;
        uint8_t* pRight = *(uint8_t**)(pNode + 0x10);
        if (pLeft[0x20] == 0 || pRight[0x20] == 0) return -1;
    }
    int nLeft = BlackHeight28(*(uint8_t**)pNode);
    int nRight = BlackHeight28(*(uint8_t**)(pNode + 0x10));
    if (nLeft < 0 || nRight < 0 || nLeft != nRight) return -1;
    return nLeft + (pNode[0x20] == 1 ? 1 : 0);
}

int main() {
    // ---- the step visits the in-order successor of every node
    {
        uint8_t* pHead = MakeHead28();
        uint8_t* n1 = Make28(40, 1, pHead);
        uint8_t* n2 = Make28(20, 1, pHead);
        uint8_t* n3 = Make28(60, 1, pHead);
        uint8_t* n4 = Make28(10, 0, pHead);
        uint8_t* n5 = Make28(30, 0, pHead);
        uint8_t* n6 = Make28(50, 0, pHead);
        uint8_t* n7 = Make28(70, 0, pHead);
        *(uint8_t**)(pHead + 0x08) = n1;
        *(uint8_t**)(pHead + 0x00) = n4;
        *(uint8_t**)(pHead + 0x10) = n7;
        *(uint8_t**)(n1 + 0x00) = n2; *(uint8_t**)(n1 + 0x10) = n3;
        *(uint8_t**)(n2 + 0x00) = n4; *(uint8_t**)(n2 + 0x10) = n5;
        *(uint8_t**)(n3 + 0x00) = n6; *(uint8_t**)(n3 + 0x10) = n7;
        *(uint8_t**)(n2 + 0x08) = n1; *(uint8_t**)(n3 + 0x08) = n1;
        *(uint8_t**)(n4 + 0x08) = n2; *(uint8_t**)(n5 + 0x08) = n2;
        *(uint8_t**)(n6 + 0x08) = n3; *(uint8_t**)(n7 + 0x08) = n3;

        uint8_t* aNodes[] = {n4, n2, n5, n1, n6, n3, n7};
        uint32_t aNext[] = {20, 30, 40, 50, 60, 70, 0};   // 0 means: ends at the head
        for (int i = 0; i < 7; ++i) {
            SynTreeIter it;
            it.pTag = pHead;      // any non-null tag
            it.pNode = aNodes[i];
            SynTreeIter aCopy = it;
            SynTreeIterIncrement28(&aCopy);
            if (aNext[i] == 0) {
                CHECK(aCopy.pNode == pHead);
            } else {
                CHECK(*(uint32_t*)((uint8_t*)aCopy.pNode + 0x18) == aNext[i]);
            }
        }
        // a node whose nil byte is set is not stepped at all
        SynTreeIter aEnd;
        aEnd.pTag = pHead;
        aEnd.pNode = pHead;
        SynTreeIter aEndCopy = aEnd;
        SynTreeIterIncrement28(&aEndCopy);
        CHECK(aEndCopy.pNode == pHead);

        // ---- the erase walks the whole tree, one node at a time
        std::set<uint32_t> aLeft = {10, 20, 30, 40, 50, 60, 70};
        uint8_t* aMap = (uint8_t*)::operator new(0x50);
        std::memset(aMap, 0xCD, 0x50);
        *(void**)aMap = aMap;
        *(uint8_t**)(aMap + 0x30) = pHead;
        *(uint64_t*)(aMap + 0x38) = 7;
        uint32_t aOrder[] = {10, 30, 70, 20, 50, 60, 40};
        for (int i = 0; i < 7; ++i) {
            SynTreeIter aSearch;
            aSearch.pTag = pHead;
            aSearch.pNode = pHead;
            // find the node holding this key by walking the tree
            uint8_t* pFound = *(uint8_t**)(pHead + 0x08);
            while (pFound[0x21] == 0) {
                uint32_t uAt = *(uint32_t*)(pFound + 0x18);
                if (uAt == aOrder[i]) break;
                pFound = (aOrder[i] < uAt) ? *(uint8_t**)pFound
                                           : *(uint8_t**)(pFound + 0x10);
            }
            CHECK(pFound[0x21] == 0);
            SynTreeIter aErase;
            aErase.pTag = pHead;
            aErase.pNode = pFound;
            SynTreeIter aOut;
            SynTreeEraseNode28(aMap, &aOut, &aErase);
            aLeft.erase(aOrder[i]);
            CHECK(*(uint64_t*)(aMap + 0x38) == aLeft.size());
            std::vector<uint32_t> aWalk;
            Walk28(*(uint8_t**)(pHead + 0x08), pHead, &aWalk);
            CHECK(aWalk.size() == aLeft.size());
            size_t uIndex = 0;
            for (uint32_t uKey : aLeft) CHECK(aWalk[uIndex++] == uKey);
            CHECK(BlackHeight28(*(uint8_t**)(pHead + 0x08)) > 0);
        }
        CHECK(BlackHeight28(*(uint8_t**)(pHead + 0x08)) == 1);
        ::operator delete(pHead);
        ::operator delete(aMap);
    }

    // ---- the range erase of the id kind, built by the ported insert
    {
        uint8_t* aMap = (uint8_t*)::operator new(0x50);
        std::memset(aMap, 0xCD, 0x50);
        *(void**)aMap = aMap;
        SynMapInitId(aMap);
        uint8_t* pHead = *(uint8_t**)(aMap + 0x30);
        uint32_t aKeys[] = {50, 30, 70, 20, 40, 60, 80};
        for (uint32_t uKey : aKeys) {
            uint8_t* pWhere = pHead;
            bool bLeft = false;
            uint8_t* pWalker = *(uint8_t**)(pHead + 0x08);
            while (pWalker[0x29] == 0) {
                pWhere = pWalker;
                if (uKey < *(uint32_t*)(pWalker + 0x18)) {
                    bLeft = true;
                    pWalker = *(uint8_t**)pWalker;
                } else {
                    bLeft = false;
                    pWalker = *(uint8_t**)(pWalker + 0x10);
                }
            }
            struct Pair {
                uint32_t uKey;
                uint32_t uPad;
                void* pValue;
            } aPair = {uKey, 0, nullptr};
            SynTreeIter aOut;
            SynMapInsertId(aMap, &aOut, bLeft, pWhere, &aPair);
        }
        CHECK(*(uint64_t*)(aMap + 0x38) == 7);

        // the id variant steps an id-shaped node with its own nil byte
        {
            uint8_t* pWalker = *(uint8_t**)(pHead + 0x08);
            while (pWalker[0x29] == 0 && *(uint32_t*)(pWalker + 0x18) != 40) {
                pWalker = (40 < *(uint32_t*)(pWalker + 0x18)) ? *(uint8_t**)pWalker
                                                             : *(uint8_t**)(pWalker + 0x10);
            }
            CHECK(pWalker[0x29] == 0);
            SynTreeIter aStep;
            aStep.pTag = aMap;
            aStep.pNode = pWalker;
            SynTreeIterIncrementIdB(&aStep);
            CHECK(*(uint32_t*)((uint8_t*)aStep.pNode + 0x18) == 50);
        }

        SynTreeIter aFirst;
        aFirst.pTag = aMap;
        aFirst.pNode = pHead;
        SynTreeIter aLast = aFirst;
        SynTreeIter aOut;
        SynTreeEraseRangeIdB(aMap, &aOut, &aFirst, &aLast);   // both ends at the head
        CHECK(*(uint64_t*)(aMap + 0x38) == 0);
        CHECK(*(uint8_t**)(pHead + 0x08) == pHead);

        // fill it again and clear it the way the binary does, sentinel included
        for (uint32_t uKey : aKeys) {
            uint8_t* pWhere = pHead;
            bool bLeft = false;
            uint8_t* pWalker = *(uint8_t**)(pHead + 0x08);
            while (pWalker[0x29] == 0) {
                pWhere = pWalker;
                if (uKey < *(uint32_t*)(pWalker + 0x18)) {
                    bLeft = true;
                    pWalker = *(uint8_t**)pWalker;
                } else {
                    bLeft = false;
                    pWalker = *(uint8_t**)(pWalker + 0x10);
                }
            }
            struct Pair {
                uint32_t uKey;
                uint32_t uPad;
                void* pValue;
            } aPair = {uKey, 0, nullptr};
            SynTreeIter aInsertOut;
            SynMapInsertId(aMap, &aInsertOut, bLeft, pWhere, &aPair);
        }
        CHECK(*(uint64_t*)(aMap + 0x38) == 7);
        SynMapClearAndFreeD(aMap);
        CHECK(*(void**)(aMap + 0x30) == nullptr);
        CHECK(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(aMap);
    }

    // ---- and the 0x28 clear, sentinel included
    {
        uint8_t* aMap = (uint8_t*)::operator new(0x50);
        std::memset(aMap, 0xCD, 0x50);
        *(void**)aMap = aMap;
        uint8_t* pHead = MakeHead28();
        *(uint8_t**)(aMap + 0x30) = pHead;
        *(uint64_t*)(aMap + 0x38) = 0;
        uint8_t* n1 = Make28(20, 1, pHead);
        uint8_t* n2 = Make28(10, 0, pHead);
        uint8_t* n3 = Make28(30, 0, pHead);
        *(uint8_t**)(pHead + 0x08) = n1;
        *(uint8_t**)(pHead + 0x00) = n2;
        *(uint8_t**)(pHead + 0x10) = n3;
        *(uint8_t**)(n1 + 0x00) = n2; *(uint8_t**)(n1 + 0x10) = n3;
        *(uint8_t**)(n2 + 0x08) = n1; *(uint8_t**)(n3 + 0x08) = n1;
        *(uint64_t*)(aMap + 0x38) = 3;
        SynMapClearAndFreeC(aMap);
        CHECK(*(void**)(aMap + 0x30) == nullptr);
        CHECK(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(aMap);
    }

    // ---- erasing the sentinel itself is refused with the binary's own message
    {
        uint8_t* aMap = (uint8_t*)::operator new(0x50);
        std::memset(aMap, 0, 0x50);
        uint8_t* pHead = MakeHead28();
        *(uint8_t**)(aMap + 0x30) = pHead;
        SynTreeIter aIter;
        aIter.pTag = aMap;
        aIter.pNode = pHead;
        SynTreeIter aOut;
        bool bThrew = false;
        try {
            SynTreeEraseNode28(aMap, &aOut, &aIter);
        } catch (const std::out_of_range& rError) {
            bThrew = true;
            CHECK(std::string(rError.what()) == "invalid map/set<T> iterator");
        }
        CHECK(bThrew);
        ::operator delete(pHead);
        ::operator delete(aMap);
    }

    std::printf("SYNDICATE_D37_OK: the 0x28 and idB erase families, 8 units, %d checks\n", g_nChecks);
    return 0;
}
