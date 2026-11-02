// ============================================================================
// cqbase_d31 — the node builders, the two iterator comparisons and the owner accessors,
//   each checked byte for byte against the layout the binary writes
// ============================================================================
#include "modules/syndicate/src/synnode.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>

using namespace tq;

int main() {
    // ---- the id node builder: links, the 16-byte pair, the colour and a clean nil byte
    {
        int aLeft, aParent, aRight;
        struct Pair {
            uint32_t uKey;
            uint32_t uPad;
            void* pValue;
        } pair = {0xDEADBEEF, 0x11223344, (void*)0xCAFEBABE};

        unsigned char* p = (unsigned char*)SynNodeNewIdA(&aLeft, &aParent, &aRight, &pair, 0);
        assert(*(void**)(p + 0x00) == &aLeft);
        assert(*(void**)(p + 0x08) == &aParent);
        assert(*(void**)(p + 0x10) == &aRight);
        assert(*(uint32_t*)(p + 0x18) == 0xDEADBEEF);
        assert(*(uint64_t*)(p + 0x20) == (uint64_t)(uintptr_t)0xCAFEBABE);
        assert(p[0x28] == 0);
        assert(p[0x29] == 0);
        ::operator delete(p);

        p = (unsigned char*)SynNodeNewIdB(&aLeft, &aParent, &aRight, &pair, 1);
        assert(*(uint32_t*)(p + 0x18) == 0xDEADBEEF);
        assert(p[0x28] == 1);
        assert(p[0x29] == 0);
        ::operator delete(p);
    }

    // ---- the empty id node: every link null, black, and the nil byte cleared
    {
        unsigned char* p = (unsigned char*)SynNodeNewIdEmptyA();
        assert(*(void**)(p + 0x00) == nullptr);
        assert(*(void**)(p + 0x08) == nullptr);
        assert(*(void**)(p + 0x10) == nullptr);
        assert(p[0x28] == 1);
        assert(p[0x29] == 0);           // the builders leave it cleared, unlike the sentinel
        ::operator delete(p);
        p = (unsigned char*)SynNodeNewIdEmptyB();
        assert(p[0x28] == 1 && p[0x29] == 0);
        ::operator delete(p);
    }

    // ---- the name node builder, both the allocating and the placement form
    {
        std::string strKey("syndicate-name-that-is-long-enough-to-heap-allocate");
        unsigned char* p = (unsigned char*)SynNodeNewName((void*)1, (void*)2, (void*)3, &strKey, 0);
        assert(*(void**)(p + 0x00) == (void*)1);
        assert(*(void**)(p + 0x08) == (void*)2);
        assert(*(void**)(p + 0x10) == (void*)3);
        assert(*(std::string*)(p + 0x18) == strKey);
        assert(p[0x40] == 0);
        assert(p[0x41] == 0);
        ((std::string*)(p + 0x18))->~basic_string();
        ::operator delete(p);

        unsigned char aBuffer[0x48];
        std::memset(aBuffer, 0xEE, sizeof(aBuffer));
        void* pPlaced = SynNodeBuildName(aBuffer, (void*)4, (void*)5, (void*)6, &strKey, 1);
        assert(pPlaced == aBuffer);
        assert(*(void**)(aBuffer + 0x00) == (void*)4);
        assert(*(void**)(aBuffer + 0x08) == (void*)5);
        assert(*(void**)(aBuffer + 0x10) == (void*)6);
        assert(*(std::string*)(aBuffer + 0x18) == strKey);
        assert(aBuffer[0x40] == 1);
        assert(aBuffer[0x41] == 0);
        ((std::string*)(aBuffer + 0x18))->~basic_string();
    }

    // ---- and the empty name node
    {
        unsigned char* p = (unsigned char*)SynNodeNewNameEmpty();
        assert(*(void**)(p + 0x00) == nullptr);
        assert(*(void**)(p + 0x08) == nullptr);
        assert(*(void**)(p + 0x10) == nullptr);
        assert(((std::string*)(p + 0x18))->empty());
        assert(p[0x40] == 1);
        assert(p[0x41] == 0);
        ((std::string*)(p + 0x18))->~basic_string();
        ::operator delete(p);
    }

    // ---- the iterator comparisons only look at the node word
    {
        SynTreeIter a;
        a.pTag = (void*)0x1000;
        a.pNode = (void*)0x2000;
        SynTreeIter b = a;
        assert(SynIterEquals(&a, &b));
        assert(!SynIterNotEquals(&a, &b));
        b.pNode = (void*)0x3000;
        assert(!SynIterEquals(&a, &b));
        assert(SynIterNotEquals(&a, &b));
        b.pNode = (void*)0x2000;
        b.pTag = (void*)0x4000;          // a different tag is only the debug check
        assert(SynIterEquals(&a, &b));
    }

    // ---- storing a pointer only when it is not null
    {
        void* pOut = (void*)0x1111;
        assert(SynOwnerAssignA(&pOut, (void*)0x2222) == true);
        assert(pOut == (void*)0x2222);
        assert(SynOwnerAssignA(&pOut, nullptr) == false);
        assert(pOut == (void*)0x2222);           // untouched on the null path
        assert(SynOwnerAssignB(&pOut, (void*)0x3333) == true);
        assert(pOut == (void*)0x3333);
        assert(SynOwnerAssignB(&pOut, nullptr) == false);
        assert(pOut == (void*)0x3333);
    }

    // ---- the word at +0x08
    {
        unsigned char aObj[0x20];
        std::memset(aObj, 0, sizeof(aObj));
        assert(SynOwnerGetWordAt8(aObj) == 0);
        SynOwnerSetWordAt8(aObj, 0xAABBCCDDu);
        assert(SynOwnerGetWordAt8(aObj) == 0xAABBCCDDu);
        assert(*(uint32_t*)(aObj + 0x08) == 0xAABBCCDDu);
        assert(*(uint32_t*)(aObj + 0x04) == 0);          // nothing next door was touched
        assert(*(uint32_t*)(aObj + 0x0c) == 0);
    }

    std::printf("SYNDICATE_D31_OK: the node builders and the owner accessors, 11 units, 53 checks\n");
    return 0;
}
