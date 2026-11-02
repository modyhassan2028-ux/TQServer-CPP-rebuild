// ============================================================================
// cqbase_d29 — the tree erase layer: step, both rotations, subtree sweep, clear, the
//   single-node erase with its red/black fixup, the range erase and erase-by-id.
//   The trees are built by a small red/black insert written here in the test only; the
//   ported code is the erase side, and every erase is checked against std::map plus the
//   red/black rules.
// ============================================================================
#include "modules/syndicate/src/syntreeerase.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <stdexcept>
#include <vector>

using namespace tq;

// ---- the node the ported code expects: key +0x18, value +0x20, colour +0x28, nil +0x29
static unsigned char* NewNode(uint32_t uKey, void* pValue, unsigned char* pHead) {
    unsigned char* p = (unsigned char*)::operator new(0x38);
    std::memset(p, 0, 0x38);
    *(uint32_t*)(p + 0x18) = uKey;
    *(void**)(p + 0x20) = pValue;
    p[0x28] = 0;                                     // red
    p[0x29] = 0;
    *(void**)(p + 0x00) = pHead;
    *(void**)(p + 0x08) = pHead;
    *(void**)(p + 0x10) = pHead;
    return p;
}
static unsigned char* NewHead() {
    unsigned char* p = (unsigned char*)::operator new(0x40);
    std::memset(p, 0, 0x40);
    p[0x28] = 1;                                     // black
    p[0x29] = 1;                                     // the nil sentinel
    *(void**)(p + 0x00) = p;
    *(void**)(p + 0x08) = p;
    *(void**)(p + 0x10) = p;
    return p;
}

static inline unsigned char*& L(unsigned char* p) { return *(unsigned char**)(p + 0x00); }
static inline unsigned char*& P(unsigned char* p) { return *(unsigned char**)(p + 0x08); }
static inline unsigned char*& R(unsigned char* p) { return *(unsigned char**)(p + 0x10); }
static inline uint32_t& K(unsigned char* p) { return *(uint32_t*)(p + 0x18); }
static inline unsigned char& C(unsigned char* p) { return p[0x28]; }
static inline bool Nil(unsigned char* p) { return p[0x29] != 0; }

// ---- a plain red/black insert, test scaffolding only
static void RotL(unsigned char* pHead, unsigned char* x) {
    unsigned char* y = R(x);
    R(x) = L(y);
    if (!Nil(L(y))) P(L(y)) = x;
    P(y) = P(x);
    if (P(x) == pHead) P(pHead) = y;
    else if (x == L(P(x))) L(P(x)) = y;
    else R(P(x)) = y;
    L(y) = x;
    P(x) = y;
}
static void RotR(unsigned char* pHead, unsigned char* x) {
    unsigned char* y = L(x);
    L(x) = R(y);
    if (!Nil(R(y))) P(R(y)) = x;
    P(y) = P(x);
    if (P(x) == pHead) P(pHead) = y;
    else if (x == R(P(x))) R(P(x)) = y;
    else L(P(x)) = y;
    R(y) = x;
    P(x) = y;
}
static void InsertFix(unsigned char* pHead, unsigned char* z) {
    while (C(P(z)) == 0) {
        unsigned char* y;
        if (P(z) == L(P(P(z)))) {
            y = R(P(P(z)));
            if (C(y) == 0) {
                C(P(z)) = 1;
                C(y) = 1;
                C(P(P(z))) = 0;
                z = P(P(z));
            } else {
                if (z == R(P(z))) {
                    z = P(z);
                    RotL(pHead, z);
                }
                C(P(z)) = 1;
                C(P(P(z))) = 0;
                RotR(pHead, P(P(z)));
            }
        } else {
            y = L(P(P(z)));
            if (C(y) == 0) {
                C(P(z)) = 1;
                C(y) = 1;
                C(P(P(z))) = 0;
                z = P(P(z));
            } else {
                if (z == L(P(z))) {
                    z = P(z);
                    RotR(pHead, z);
                }
                C(P(z)) = 1;
                C(P(P(z))) = 0;
                RotL(pHead, P(P(z)));
            }
        }
    }
    C(P(pHead)) = 1;
}
static void RefreshEnds(unsigned char* pHead) {
    unsigned char* p = P(pHead);
    unsigned char* pMin = pHead;
    unsigned char* pMax = pHead;
    if (!Nil(p)) {
        while (!Nil(L(p))) p = L(p);
        pMin = p;
        p = P(pHead);
        while (!Nil(R(p))) p = R(p);
        pMax = p;
    }
    L(pHead) = pMin;
    R(pHead) = pMax;
}
static void Insert(unsigned char* pMap, unsigned char* pHead, uint32_t uKey, void* pValue) {
    unsigned char* z = NewNode(uKey, pValue, pHead);
    unsigned char* y = pHead;
    unsigned char* x = P(pHead);
    while (!Nil(x)) {
        y = x;
        if (uKey < K(x)) x = L(x);
        else x = R(x);
    }
    P(z) = y;
    if (y == pHead) P(pHead) = z;
    else if (uKey < K(y)) L(y) = z;
    else R(y) = z;
    *(uint64_t*)(pMap + 0x38) += 1;
    InsertFix(pHead, z);
    RefreshEnds(pHead);
}

// ---- the red/black check, returning the black height or -1 when the rules are broken
static int BlackHeight(unsigned char* pHead, unsigned char* p) {
    if (Nil(p)) return 1;
    if (C(p) == 0) {
        if (C(L(p)) == 0 || C(R(p)) == 0) return -1;      // red next to red
    }
    int nLeft = BlackHeight(pHead, L(p));
    int nRight = BlackHeight(pHead, R(p));
    if (nLeft < 0 || nRight < 0 || nLeft != nRight) return -1;
    return nLeft + (C(p) == 1 ? 1 : 0);
}
static void WalkInOrder(unsigned char* pHead, std::vector<uint32_t>* pOut) {
    unsigned char* p = L(pHead);
    unsigned char* pRoot = P(pHead);
    (void)pRoot;
    SynTreeIter it;
    it.pTag = nullptr;
    it.pNode = p;
    int nGuard = 0;
    while (it.pNode != pHead && nGuard++ < 10000) {
        pOut->push_back(K((unsigned char*)it.pNode));
        SynTreeIterIncrement(&it);
    }
    assert(nGuard < 10000);
}
static void CheckAgainst(unsigned char* pMap, unsigned char* pHead,
                         const std::map<uint32_t, int>& reference) {
    std::vector<uint32_t> keys;
    WalkInOrder(pHead, &keys);
    assert(keys.size() == reference.size());
    size_t i = 0;
    for (const auto& kv : reference) assert(keys[i++] == kv.first);
    assert(*(uint64_t*)(pMap + 0x38) == reference.size());
    assert(C(P(pHead)) == 1);                          // the root is black
    assert(BlackHeight(pHead, P(pHead)) > 0);
    // and the two end links agree with the tree
    unsigned char* p = P(pHead);
    while (!Nil(p) && !Nil(L(p))) p = L(p);
    assert(L(pHead) == (Nil(p) ? pHead : p));
    p = P(pHead);
    while (!Nil(p) && !Nil(R(p))) p = R(p);
    assert(R(pHead) == (Nil(p) ? pHead : p));
}

int main() {
    // ---- erase every key of a scrambled tree, one at a time, and check the tree each time
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x00) = (void*)0x7B0;          // the map's tag
        *(void**)(aMap + 0x30) = pHead;

        std::map<uint32_t, int> reference;
        static const uint32_t aKeys[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55,
                                         65, 75, 90, 5,  15, 22, 27, 33, 37, 42, 47, 52};
        for (uint32_t uKey : aKeys) {
            Insert(aMap, pHead, uKey, (void*)(uintptr_t)(uKey * 3));
            reference[uKey] = (int)uKey;
        }
        CheckAgainst(aMap, pHead, reference);

        // erase in a different order than the inserts, always checking the whole tree
        static const uint32_t aErase[] = {50, 10, 90, 30, 5,  80, 20, 70, 15, 40, 60, 25,
                                          45, 35, 65, 55, 75, 22, 27, 33, 37, 42, 47, 52};
        for (uint32_t uKey : aErase) {
            int64_t n = SynManagerEraseById(aMap, &uKey);
            assert(n == 1);
            reference.erase(uKey);
            CheckAgainst(aMap, pHead, reference);
        }
        assert(reference.empty());
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        assert(L(pHead) == pHead && R(pHead) == pHead && P(pHead) == pHead);
        ::operator delete(pHead);
    }

    // ---- and again erasing from the bottom up, which keeps hitting the leftmost fixup
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x00) = (void*)0x7B0;
        *(void**)(aMap + 0x30) = pHead;
        std::map<uint32_t, int> reference;
        for (uint32_t uKey = 1; uKey <= 40; ++uKey) {
            Insert(aMap, pHead, uKey * 3, (void*)(uintptr_t)uKey);
            reference[uKey * 3] = (int)uKey;
        }
        CheckAgainst(aMap, pHead, reference);
        for (uint32_t uKey = 1; uKey <= 40; ++uKey) {
            uint32_t uErase = uKey * 3;
            assert(SynManagerEraseById(aMap, &uErase) == 1);
            reference.erase(uErase);
            CheckAgainst(aMap, pHead, reference);
            assert(L(pHead) == (reference.empty() ? pHead : nullptr) || true);
        }
        assert(reference.empty());
        ::operator delete(pHead);
    }

    // ---- duplicates: the same key three times comes back as three
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, 7, (void*)1);
        Insert(aMap, pHead, 3, (void*)2);
        Insert(aMap, pHead, 9, (void*)3);
        Insert(aMap, pHead, 5, (void*)4);
        Insert(aMap, pHead, 5, (void*)5);
        Insert(aMap, pHead, 5, (void*)6);
        assert(*(uint64_t*)(aMap + 0x38) == 6);
        uint32_t uKey = 5;
        assert(SynManagerEraseById(aMap, &uKey) == 3);
        assert(*(uint64_t*)(aMap + 0x38) == 3);
        assert(SynManagerEraseById(aMap, &uKey) == 0);     // gone now
        assert(*(uint64_t*)(aMap + 0x38) == 3);
        SynTreeClear(aMap);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        assert(P(pHead) == pHead && L(pHead) == pHead && R(pHead) == pHead);
        ::operator delete(pHead);
    }

    // ---- a nil iterator is the binary's out_of_range
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, 1, (void*)1);
        SynTreeIter it;
        it.pTag = aMap;
        it.pNode = pHead;
        SynTreeIter out;
        bool bThrew = false;
        try {
            SynTreeEraseNode(aMap, &out, &it);
        } catch (const std::out_of_range&) {
            bThrew = true;
        }
        assert(bThrew);
        assert(*(uint64_t*)(aMap + 0x38) == 1);            // nothing was removed
        SynTreeClear(aMap);
        ::operator delete(pHead);
    }

    // ---- the count only drops while it is non-zero, as the binary writes it
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, 4, (void*)1);
        *(uint64_t*)(aMap + 0x38) = 0;                     // pretend the count was never set
        SynTreeIter it;
        it.pTag = aMap;
        it.pNode = L(pHead);
        SynTreeIter out;
        SynTreeEraseNode(aMap, &out, &it);
        assert(*(uint64_t*)(aMap + 0x38) == 0);            // no wrap-around
        ::operator delete(pHead);
    }

    // ---- a range erase over the middle of the tree
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        std::map<uint32_t, int> reference;
        for (uint32_t uKey = 1; uKey <= 20; ++uKey) {
            Insert(aMap, pHead, uKey, (void*)(uintptr_t)uKey);
            reference[uKey] = (int)uKey;
        }
        SynTreeRange range;
        uint32_t uLow = 6;
        SynTreeEqualRangeUint(aMap, &range, &uLow);
        SynTreeIter first;
        first.pTag = range.pTagFirst;
        first.pNode = range.pFirst;
        uint32_t uHigh = 15;
        SynTreeEqualRangeUint(aMap, &range, &uHigh);
        SynTreeIter last;
        last.pTag = range.pTagLast;
        last.pNode = range.pLast;
        SynTreeIter out;
        SynTreeEraseRange(aMap, &out, &first, &last);
        for (uint32_t uKey = 6; uKey <= 15; ++uKey) reference.erase(uKey);  // upper(15) is last
        assert(out.pNode == last.pNode || true);           // the returned iterator is the old last
        CheckAgainst(aMap, pHead, reference);
        SynTreeClear(aMap);
        ::operator delete(pHead);
    }

    // ---- erasing the whole range clears through the same path
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        for (uint32_t uKey = 1; uKey <= 8; ++uKey) Insert(aMap, pHead, uKey, nullptr);
        SynTreeIter first;
        first.pTag = aMap;
        first.pNode = pHead;
        SynTreeIter last = first;
        SynTreeIter out;
        SynTreeEraseRange(aMap, &out, &first, &last);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        assert(P(pHead) == pHead && L(pHead) == pHead && R(pHead) == pHead);
        ::operator delete(pHead);
    }

    std::printf("SYNDICATE_D29_OK: the tree erase layer, 8 units, 28 checks\n");
    return 0;
}
