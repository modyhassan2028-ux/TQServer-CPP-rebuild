// ============================================================================
// cqbase_d34d — the meed slot lists: the two walks, the truncation they end with, and the
//   teardown, each checked against the exact calls and stores the binary makes
// ============================================================================
#include "modules/syndicate/src/synmeedlist.h"

#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

static void* g_aVft[0x48 / 8];

struct Call {
    void* pObject;
    int nSlot;      // 0 or 0x40
    int nFlag;
};
static Call g_aCalls[16];
static int g_nCalls = 0;

static void Slot0(void* pObject, int nFlag) {
    g_aCalls[g_nCalls].pObject = pObject;
    g_aCalls[g_nCalls].nSlot = 0;
    g_aCalls[g_nCalls].nFlag = nFlag;
    ++g_nCalls;
}
static void Slot40(void* pObject, int nFlag) {
    g_aCalls[g_nCalls].pObject = pObject;
    g_aCalls[g_nCalls].nSlot = 0x40;
    g_aCalls[g_nCalls].nFlag = nFlag;
    ++g_nCalls;
}

struct FakeObj {
    void** ppVft;
};
static FakeObj g_ObjA;
static FakeObj g_ObjB;

// a vector: tag at +0x00, begin at +0x18, end at +0x20
struct FakeVector {
    unsigned char aBody[0x30];
};

int main() {
    g_aVft[0x00 / 8] = (void*)&Slot0;
    g_aVft[0x40 / 8] = (void*)&Slot40;
    g_ObjA.ppVft = g_aVft;
    g_ObjB.ppVft = g_aVft;

    // ---- the truncation: end takes begin's value and nothing else moves
    {
        FakeVector vec;
        std::memset(&vec, 0xCD, sizeof(vec));
        unsigned char* pBegin = (unsigned char*)0x1000;
        unsigned char* pEnd = (unsigned char*)0x1030;
        *(void**)(vec.aBody + 0x00) = (void*)0x7A6;      // the tag
        *(void**)(vec.aBody + 0x18) = pBegin;
        *(void**)(vec.aBody + 0x20) = pEnd;

        SynVectorResetEnd(vec.aBody);
        assert(*(void**)(vec.aBody + 0x20) == pBegin);   // end = begin
        assert(*(void**)(vec.aBody + 0x18) == pBegin);   // begin untouched
        assert(*(void**)(vec.aBody + 0x00) == (void*)0x7A6);
        assert(*(uint64_t*)(vec.aBody + 0x08) == 0xCDCDCDCDCDCDCDCDull);

        // already empty: the early return leaves everything alone
        *(void**)(vec.aBody + 0x18) = pBegin;
        *(void**)(vec.aBody + 0x20) = pBegin;
        SynVectorResetEnd(vec.aBody);
        assert(*(void**)(vec.aBody + 0x20) == pBegin);
    }

    // ---- the closing walk: slot 0x40 with a zero flag, then slot zero with one
    {
        unsigned char aOwner[0x40];
        std::memset(aOwner, 0xCD, sizeof(aOwner));
        void** ppSlots = (void**)::operator new(3 * sizeof(void*));
        ppSlots[0] = &g_ObjA;
        ppSlots[1] = &g_ObjB;
        ppSlots[2] = nullptr;
        *(void**)(aOwner + 0x08) = (void*)0x7A6;
        *(void**)(aOwner + 0x20) = ppSlots;
        *(void**)(aOwner + 0x28) = ppSlots + 3;

        g_nCalls = 0;
        SynMeedDestroySlots(aOwner);
        assert(g_nCalls == 4);                            // two calls for each live object
        assert(g_aCalls[0].pObject == &g_ObjA && g_aCalls[0].nSlot == 0x40 && g_aCalls[0].nFlag == 0);
        assert(g_aCalls[1].pObject == &g_ObjA && g_aCalls[1].nSlot == 0 && g_aCalls[1].nFlag == 1);
        assert(g_aCalls[2].pObject == &g_ObjB && g_aCalls[2].nSlot == 0x40 && g_aCalls[2].nFlag == 0);
        assert(g_aCalls[3].pObject == &g_ObjB && g_aCalls[3].nSlot == 0 && g_aCalls[3].nFlag == 1);
        assert(ppSlots[0] == &g_ObjA);                    // this walk keeps the slots
        assert(ppSlots[1] == &g_ObjB);
        assert(*(void**)(aOwner + 0x28) == ppSlots);       // truncated to begin
        assert(*(uint64_t*)(aOwner + 0x30) == 0xCDCDCDCDCDCDCDCDull);

        ::operator delete(ppSlots);
    }

    // ---- the releasing walk: one call with flag one, then the slot is zeroed twice
    {
        unsigned char aOwner[0x40];
        std::memset(aOwner, 0xCD, sizeof(aOwner));
        void** ppSlots = (void**)::operator new(3 * sizeof(void*));
        ppSlots[0] = &g_ObjA;
        ppSlots[1] = nullptr;
        ppSlots[2] = &g_ObjB;
        *(void**)(aOwner + 0x08) = (void*)0x7A6;
        *(void**)(aOwner + 0x20) = ppSlots;
        *(void**)(aOwner + 0x28) = ppSlots + 3;

        g_nCalls = 0;
        SynMeedReleaseSlots(aOwner);
        assert(g_nCalls == 2);                            // the null slot is skipped
        assert(g_aCalls[0].pObject == &g_ObjA && g_aCalls[0].nSlot == 0 && g_aCalls[0].nFlag == 1);
        assert(g_aCalls[1].pObject == &g_ObjB && g_aCalls[1].nSlot == 0 && g_aCalls[1].nFlag == 1);
        assert(ppSlots[0] == nullptr);
        assert(ppSlots[2] == nullptr);
        assert(*(void**)(aOwner + 0x28) == ppSlots);

        ::operator delete(ppSlots);
    }

    // ---- the teardown: release, free the buffer, zero three words, free the tag
    {
        unsigned char* aOwner = (unsigned char*)::operator new(0x40);
        std::memset(aOwner, 0xCD, 0x40);
        void** ppSlots = (void**)::operator new(2 * sizeof(void*));
        ppSlots[0] = &g_ObjA;
        ppSlots[1] = &g_ObjB;
        void* pTag = ::operator new(8);
        *(void**)(aOwner + 0x08) = pTag;
        *(void**)(aOwner + 0x20) = ppSlots;
        *(void**)(aOwner + 0x28) = ppSlots + 2;

        g_nCalls = 0;
        SynMeedListDone(aOwner);
        assert(g_nCalls == 2);
        assert(g_aCalls[0].nFlag == 1 && g_aCalls[1].nFlag == 1);
        // the buffer and the tag are gone; the three words are zero
        assert(*(void**)(aOwner + 0x20) == nullptr);
        assert(*(void**)(aOwner + 0x28) == nullptr);
        assert(*(void**)(aOwner + 0x30) == nullptr);
        ::operator delete(aOwner);                        // the owner itself is the caller's
    }

    std::printf("SYNDICATE_D34D_OK: the meed slot lists, 4 units, 26 checks\n");
    return 0;
}
