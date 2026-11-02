// ============================================================================
// cqbase_d32 — the map constructors and the insert side. Every insert is fed the hint a normal
//   insert would compute, then the whole tree is checked against std::set (order, count,
//   red/black rules) and finally erased through the already verified erase path.
// ============================================================================
#include "modules/syndicate/src/synmap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreeerasestr.h"
#include "modules/syndicate/src/syntreemap.h"

using namespace tq;

// ---- layout helpers for the checks
static inline uint8_t* Nd(uint8_t* p, size_t off) { return *(uint8_t**)(p + off); }
static inline uint32_t Key32(uint8_t* p) { return *(uint32_t*)(p + 0x18); }
static inline std::string& KeyStr(uint8_t* p) { return *(std::string*)(p + 0x18); }

static int BlackHeightId(uint8_t* pHead, uint8_t* p) {
    if (p[0x29] != 0) return 1;
    if (p[0x28] == 0 && (Nd(p, 0x00)[0x28] == 0 || Nd(p, 0x10)[0x28] == 0)) return -1;
    int a = BlackHeightId(pHead, Nd(p, 0x00));
    int b = BlackHeightId(pHead, Nd(p, 0x10));
    if (a < 0 || b < 0 || a != b) return -1;
    return a + (p[0x28] == 1 ? 1 : 0);
}
static int BlackHeightStr(uint8_t* pHead, uint8_t* p) {
    if (p[0x41] != 0) return 1;
    if (p[0x40] == 0 && (Nd(p, 0x00)[0x40] == 0 || Nd(p, 0x10)[0x40] == 0)) return -1;
    int a = BlackHeightStr(pHead, Nd(p, 0x00));
    int b = BlackHeightStr(pHead, Nd(p, 0x10));
    if (a < 0 || b < 0 || a != b) return -1;
    return a + (p[0x40] == 1 ? 1 : 0);
}

// ---- a normal insert built on the ported insert: find the hint, then hand it over
static void InsertKey(uint8_t* pMap, uint32_t uKey, void* pValue) {
    uint8_t* pHead = Nd(pMap, 0x30);
    uint8_t* pWhere = pHead;
    bool bLeft = false;
    uint8_t* p = Nd(pHead, 0x08);
    while (p[0x29] == 0) {
        pWhere = p;
        if (uKey < Key32(p)) { bLeft = true; p = Nd(p, 0x00); }
        else { bLeft = false; p = Nd(p, 0x10); }
    }
    struct Pair {
        uint32_t uKey;
        uint32_t uPad;
        void* pValue;
    } pair = {uKey, 0, pValue};
    uint8_t aOut[0x10];
    SynMapInsertId(pMap, aOut, bLeft, pWhere, &pair);
}
static void InsertName(uint8_t* pMap, const std::string& strKey) {
    uint8_t* pHead = Nd(pMap, 0x30);
    uint8_t* pWhere = pHead;
    bool bLeft = false;
    uint8_t* p = Nd(pHead, 0x08);
    while (p[0x41] == 0) {
        pWhere = p;
        if (strKey < KeyStr(p)) { bLeft = true; p = Nd(p, 0x00); }
        else { bLeft = false; p = Nd(p, 0x10); }
    }
    uint8_t aOut[0x10];
    SynMapInsertName(pMap, aOut, bLeft, pWhere, &strKey);
}

int main() {
    // ---- the constructors lay a proper sentinel and empty the map
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xEE, sizeof(aMap));
        SynMapInitId(aMap);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(pHead != nullptr);
        assert(pHead[0x29] == 1);                        // the sentinel
        assert(pHead[0x28] == 1);                        // black
        assert(Nd(pHead, 0x08) == pHead);
        assert(Nd(pHead, 0x00) == pHead);
        assert(Nd(pHead, 0x10) == pHead);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(pHead);

        std::memset(aMap, 0xEE, sizeof(aMap));
        SynMapInitName(aMap);
        pHead = Nd(aMap, 0x30);
        assert(pHead[0x41] == 1);
        assert(pHead[0x40] == 1);
        assert(Nd(pHead, 0x08) == pHead);
        assert(Nd(pHead, 0x00) == pHead);
        assert(Nd(pHead, 0x10) == pHead);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ((std::string*)(pHead + 0x18))->~basic_string();
        ::operator delete(pHead);
    }

    // ---- the two holder constructors: an eight-byte self-reference at +0x00, then a sentinel
    for (int nForm = 0; nForm < 2; ++nForm) {
        unsigned char aMap[0x40];
        std::memset(aMap, 0xEE, sizeof(aMap));
        if (nForm == 0) SynMapCtorHolderA(aMap);
        else SynMapCtorHolderB(aMap);
        void** ppHolder = *(void***)aMap;
        assert(ppHolder != nullptr);
        assert(*ppHolder == aMap);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(pHead[0x29] == 1);
        assert(Nd(pHead, 0x08) == pHead);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(ppHolder);
        ::operator delete(pHead);
    }

    // ---- insert a scrambled set of keys, checking the tree after every single one
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        SynMapInitId(aMap);
        std::set<uint32_t> reference;
        static const uint32_t aKeys[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55,
                                         65, 75, 90, 5,  15, 22, 27, 33, 37, 42, 47, 52,
                                         1,  99, 66, 44, 11, 88};
        for (uint32_t uKey : aKeys) {
            InsertKey(aMap, uKey, (void*)(uintptr_t)uKey);
            reference.insert(uKey);
            assert(*(uint64_t*)(aMap + 0x38) == reference.size());
            uint8_t* pHead = Nd(aMap, 0x30);
            assert(pHead[0x28] == 1 && Nd(pHead, 0x08)[0x28] == 1);   // the root is black
            assert(BlackHeightId(pHead, Nd(pHead, 0x08)) > 0);
            // the walk matches the reference set
            SynTreeIter it;
            it.pTag = aMap;
            it.pNode = Nd(pHead, 0x00);
            size_t i = 0;
            while (it.pNode != pHead) {
                auto itRef = reference.begin();
                std::advance(itRef, i);
                assert(Key32((uint8_t*)it.pNode) == *itRef);
                ++i;
                SynTreeIterIncrement(&it);
            }
            assert(i == reference.size());
        }
        // and the whole thing comes apart again through the erase path
        for (uint32_t uKey : aKeys) {
            uint32_t uErase = uKey;
            assert(SynManagerEraseById(aMap, &uErase) == 1);
            reference.erase(uErase);
            uint8_t* pHead = Nd(aMap, 0x30);
            assert(*(uint64_t*)(aMap + 0x38) == reference.size());
            assert(BlackHeightId(pHead, Nd(pHead, 0x08)) > 0);
        }
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(Nd(pHead, 0x08) == pHead);
        ::operator delete(pHead);
    }

    // ---- duplicates are kept, inserted to the right
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        SynMapInitId(aMap);
        InsertKey(aMap, 7, (void*)1);
        InsertKey(aMap, 7, (void*)2);
        InsertKey(aMap, 7, (void*)3);
        assert(*(uint64_t*)(aMap + 0x38) == 3);
        uint32_t uKey = 7;
        assert(SynManagerEraseById(aMap, &uKey) == 3);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        ::operator delete(pHead);
    }

    // ---- the size guard answers with length_error at the binary's own limit
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        SynMapInitId(aMap);
        *(uint64_t*)(aMap + 0x38) = 0x0FFFFFFFFFFFFFFEULL;
        bool bThrew = false;
        struct Pair {
            uint32_t uKey;
            uint32_t uPad;
            void* pValue;
        } pair = {1, 0, nullptr};
        uint8_t aOut[0x10];
        try {
            SynMapInsertId(aMap, aOut, false, Nd(aMap, 0x30), &pair);
        } catch (const std::length_error&) {
            bThrew = true;
        }
        assert(bThrew);
        assert(*(uint64_t*)(aMap + 0x38) == 0x0FFFFFFFFFFFFFFEULL);   // untouched
        ::operator delete(Nd(aMap, 0x30));

        std::memset(aMap, 0, sizeof(aMap));
        SynMapInitName(aMap);
        *(uint64_t*)(aMap + 0x38) = 0x0666666666666665ULL;
        std::string strKey("overflow");
        bThrew = false;
        try {
            SynMapInsertName(aMap, aOut, false, Nd(aMap, 0x30), &strKey);
        } catch (const std::length_error&) {
            bThrew = true;
        }
        assert(bThrew);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(*(uint64_t*)(aMap + 0x38) == 0x0666666666666665ULL);
        ((std::string*)(pHead + 0x18))->~basic_string();
        ::operator delete(pHead);
    }

    // ---- and the name insert, checked the same way
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        SynMapInitName(aMap);
        std::set<std::string> reference;
        static const char* aNames[] = {"mike", "anna", "zoe",  "bob",  "lenny", "kate",
                                       "dora", "pete", "yuri", "gabe", "nina",  "otto"};
        for (const char* pszName : aNames) {
            InsertName(aMap, pszName);
            reference.insert(pszName);
            assert(*(uint64_t*)(aMap + 0x38) == reference.size());
            uint8_t* pHead = Nd(aMap, 0x30);
            assert(pHead[0x40] == 1 && Nd(pHead, 0x08)[0x40] == 1);
            assert(BlackHeightStr(pHead, Nd(pHead, 0x08)) > 0);
            SynTreeIter it;
            it.pTag = aMap;
            it.pNode = Nd(pHead, 0x00);
            size_t i = 0;
            while (it.pNode != pHead) {
                auto itRef = reference.begin();
                std::advance(itRef, i);
                assert(KeyStr((uint8_t*)it.pNode) == *itRef);
                ++i;
                SynTreeIterIncrementStr(&it);
            }
            assert(i == reference.size());
        }
        for (const char* pszName : aNames) {
            std::string strErase(pszName);
            assert(SynManagerEraseByName(aMap, &strErase) == 1);
            reference.erase(strErase);
            uint8_t* pHead = Nd(aMap, 0x30);
            assert(*(uint64_t*)(aMap + 0x38) == reference.size());
            assert(BlackHeightStr(pHead, Nd(pHead, 0x08)) > 0);
        }
        assert(*(uint64_t*)(aMap + 0x38) == 0);
        uint8_t* pHead = Nd(aMap, 0x30);
        assert(Nd(pHead, 0x08) == pHead);
        ((std::string*)(pHead + 0x18))->~basic_string();
        ::operator delete(pHead);
    }

    std::printf("SYNDICATE_D32_OK: the map constructors and the insert side, 6 units, 45 checks\n");
    return 0;
}
