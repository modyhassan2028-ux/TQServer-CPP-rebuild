// ============================================================================
// cqbase_d30 — the name-keyed erase layer: step, both rotations, the subtree sweep, the
//   single-node erase with its red/black fixup, the range erase and erase-by-name.
//   The name trees are built by a small red/black insert written here in the test only; every
//   erase is checked against std::map<std::string,int> and the red/black rules.
// ============================================================================
#include "modules/syndicate/src/syntreeerasestr.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

using namespace tq;

// ---- a name node: key string +0x18, colour +0x40, nil +0x41
static unsigned char* NewNode(const std::string& strKey, void* pValue, unsigned char* pHead) {
    unsigned char* p = (unsigned char*)::operator new(0x48);
    std::memset(p, 0, 0x48);
    new (p + 0x18) std::string(strKey);
    p[0x40] = 0;                                     // red
    p[0x41] = 0;
    *(void**)(p + 0x00) = pHead;
    *(void**)(p + 0x08) = pHead;
    *(void**)(p + 0x10) = pHead;
    // the value would live at +0x38, right after the 32-byte key string; not needed here
    (void)pValue;
    return p;
}
static unsigned char* NewHead() {
    unsigned char* p = (unsigned char*)::operator new(0x48);
    std::memset(p, 0, 0x48);
    new (p + 0x18) std::string();
    p[0x40] = 1;                                     // black
    p[0x41] = 1;                                     // the nil sentinel
    *(void**)(p + 0x00) = p;
    *(void**)(p + 0x08) = p;
    *(void**)(p + 0x10) = p;
    return p;
}
static void FreeHead(unsigned char* p) {
    ((std::string*)(p + 0x18))->~basic_string();
    ::operator delete(p);
}

static inline unsigned char*& L(unsigned char* p) { return *(unsigned char**)(p + 0x00); }
static inline unsigned char*& P(unsigned char* p) { return *(unsigned char**)(p + 0x08); }
static inline unsigned char*& R(unsigned char* p) { return *(unsigned char**)(p + 0x10); }
static inline std::string& K(unsigned char* p) { return *(std::string*)(p + 0x18); }
static inline unsigned char& C(unsigned char* p) { return p[0x40]; }
static inline bool Nil(unsigned char* p) { return p[0x41] != 0; }

// ---- red/black insert, test scaffolding only
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
static void Insert(unsigned char* pMap, unsigned char* pHead, const std::string& strKey, void* pValue) {
    unsigned char* z = NewNode(strKey, pValue, pHead);
    unsigned char* y = pHead;
    unsigned char* x = P(pHead);
    while (!Nil(x)) {
        y = x;
        if (K(z) < K(x)) x = L(x);
        else x = R(x);
    }
    P(z) = y;
    if (y == pHead) P(pHead) = z;
    else if (K(z) < K(y)) L(y) = z;
    else R(y) = z;
    *(uint64_t*)(pMap + 0x38) += 1;
    InsertFix(pHead, z);
    RefreshEnds(pHead);
}

// frees whatever is left through the same range-erase path the binary uses
static void ClearAll(unsigned char* pMap, unsigned char* pHead) {
    SynTreeIter first;
    first.pTag = pMap;
    first.pNode = pHead;
    SynTreeIter last = first;
    SynTreeIter out;
    SynTreeEraseRangeStr(pMap, &out, &first, &last);
}

static int BlackHeight(unsigned char* pHead, unsigned char* p) {
    if (Nil(p)) return 1;
    if (C(p) == 0 && (C(L(p)) == 0 || C(R(p)) == 0)) return -1;
    int nLeft = BlackHeight(pHead, L(p));
    int nRight = BlackHeight(pHead, R(p));
    if (nLeft < 0 || nRight < 0 || nLeft != nRight) return -1;
    return nLeft + (C(p) == 1 ? 1 : 0);
}
static void CheckAgainst(unsigned char* pMap, unsigned char* pHead,
                         const std::map<std::string, int>& reference) {
    SynTreeIter it;
    it.pTag = pMap;
    it.pNode = L(pHead);
    std::vector<std::string> names;
    int nGuard = 0;
    while (it.pNode != pHead && nGuard++ < 10000) {
        names.push_back(K((unsigned char*)it.pNode));
        SynTreeIterIncrementStr(&it);
    }
    assert(nGuard < 10000);
    assert(names.size() == reference.size());
    size_t i = 0;
    for (const auto& kv : reference) {
        if (names[i] != kv.first) {
            std::fprintf(stderr, "MISMATCH at %zu: tree='%s' ref='%s'\n", i,
                         names[i].c_str(), kv.first.c_str());
            std::fprintf(stderr, "tree:");
            for (const auto& s2 : names) std::fprintf(stderr, " %s", s2.c_str());
            std::fprintf(stderr, "\nref :");
            for (const auto& kv2 : reference) std::fprintf(stderr, " %s", kv2.first.c_str());
            std::fprintf(stderr, "\n");
        }
        assert(names[i++] == kv.first);
    }
    assert(*(uint64_t*)(pMap + 0x38) == reference.size());
    assert(C(P(pHead)) == 1);
    assert(BlackHeight(pHead, P(pHead)) > 0);
    unsigned char* p = P(pHead);
    while (!Nil(p) && !Nil(L(p))) p = L(p);
    assert(L(pHead) == (Nil(p) ? pHead : p));
    p = P(pHead);
    while (!Nil(p) && !Nil(R(p))) p = R(p);
    assert(R(pHead) == (Nil(p) ? pHead : p));
}

int main() {
    // ---- erase every name of a scrambled tree, checking the whole tree after each step
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x00) = (void*)0x7C0;
        *(void**)(aMap + 0x30) = pHead;

        std::map<std::string, int> reference;
        static const char* aNames[] = {"mike",  "anna",  "zoe",  "bob",  "lenny", "kate",
                                       "dora",  "pete",  "yuri", "gabe", "nina",  "otto",
                                       "sara",  "tina",  "vito", "walt", "xena",  "ivan",
                                       "jane",  "hugo"};
        int n = 0;
        for (const char* pszName : aNames) {
            Insert(aMap, pHead, pszName, (void*)(uintptr_t)(++n));
            reference[pszName] = n;
        }
        CheckAgainst(aMap, pHead, reference);

        static const char* aErase[] = {"mike", "anna", "zoe", "bob", "lenny", "kate",
                                       "dora", "pete", "yuri", "gabe", "nina",  "otto",
                                       "sara", "tina", "vito", "walt", "xena",  "ivan",
                                       "jane", "hugo"};
        for (const char* pszName : aErase) {
            std::string strKey(pszName);
            assert(SynManagerEraseByName(aMap, &strKey) == 1);
            reference.erase(strKey);
            CheckAgainst(aMap, pHead, reference);
        }
        assert(reference.empty());
        assert(L(pHead) == pHead && R(pHead) == pHead && P(pHead) == pHead);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- erasing from the top down, which walks the rightmost fixup every time
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        std::map<std::string, int> reference;
        char aKey[16];
        for (int i = 1; i <= 30; ++i) {
            std::snprintf(aKey, sizeof(aKey), "n%03d", i);
            Insert(aMap, pHead, aKey, (void*)(uintptr_t)i);
            reference[aKey] = i;
        }
        CheckAgainst(aMap, pHead, reference);
        for (int i = 30; i >= 1; --i) {
            std::snprintf(aKey, sizeof(aKey), "n%03d", i);
            std::string strKey(aKey);
            assert(SynManagerEraseByName(aMap, &strKey) == 1);
            reference.erase(strKey);
            CheckAgainst(aMap, pHead, reference);
        }
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- the same name three times comes back as three
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, "dupe", (void*)1);
        Insert(aMap, pHead, "dupe", (void*)2);
        Insert(aMap, pHead, "dupe", (void*)3);
        Insert(aMap, pHead, "other", (void*)4);
        assert(*(uint64_t*)(aMap + 0x38) == 4);
        std::string strKey("dupe");
        assert(SynManagerEraseByName(aMap, &strKey) == 3);
        assert(*(uint64_t*)(aMap + 0x38) == 1);
        assert(SynManagerEraseByName(aMap, &strKey) == 0);
        assert(*(uint64_t*)(aMap + 0x38) == 1);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- a nil iterator is the binary's out_of_range
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, "alpha", (void*)1);
        SynTreeIter it;
        it.pTag = aMap;
        it.pNode = pHead;
        SynTreeIter out;
        bool bThrew = false;
        try {
            SynTreeEraseNodeStr(aMap, &out, &it);
        } catch (const std::out_of_range&) {
            bThrew = true;
        }
        assert(bThrew);
        assert(*(uint64_t*)(aMap + 0x38) == 1);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- the count only drops while it is non-zero
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        Insert(aMap, pHead, "solo", (void*)1);
        *(uint64_t*)(aMap + 0x38) = 0;
        SynTreeIter it;
        it.pTag = aMap;
        it.pNode = L(pHead);
        SynTreeIter out;
        SynTreeEraseNodeStr(aMap, &out, &it);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- a range of names goes at once
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        std::map<std::string, int> reference;
        char aKey[16];
        for (int i = 1; i <= 20; ++i) {
            std::snprintf(aKey, sizeof(aKey), "k%02d", i);
            Insert(aMap, pHead, aKey, (void*)(uintptr_t)i);
            reference[aKey] = i;
        }
        SynTreeRange range;
        std::string strLow("k05");
        SynTreeEqualRangeStr(aMap, &range, &strLow);
        SynTreeIter first;
        first.pTag = range.pTagFirst;
        first.pNode = range.pFirst;
        std::string strHigh("k12");
        SynTreeEqualRangeStr(aMap, &range, &strHigh);
        SynTreeIter last;
        last.pTag = range.pTagLast;
        last.pNode = range.pLast;
        SynTreeIter out;
        SynTreeEraseRangeStr(aMap, &out, &first, &last);
        for (int i = 5; i <= 12; ++i) {
            std::snprintf(aKey, sizeof(aKey), "k%02d", i);
            reference.erase(aKey);
        }
        CheckAgainst(aMap, pHead, reference);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    // ---- both ends at the head clears the map through the subtree sweep
    {
        unsigned char* pHead = NewHead();
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        *(void**)(aMap + 0x30) = pHead;
        for (int i = 1; i <= 9; ++i) {
            char aKey[8];
            std::snprintf(aKey, sizeof(aKey), "c%d", i);
            Insert(aMap, pHead, aKey, nullptr);
        }
        SynTreeIter first;
        first.pTag = aMap;
        first.pNode = pHead;
        SynTreeIter last = first;
        SynTreeIter out;
        SynTreeEraseRangeStr(aMap, &out, &first, &last);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        assert(P(pHead) == pHead && L(pHead) == pHead && R(pHead) == pHead);
        ClearAll(aMap, pHead);
        FreeHead(pHead);
    }

    std::printf("SYNDICATE_D30_OK: the name erase layer, 7 units, 22 checks\n");
    return 0;
}
