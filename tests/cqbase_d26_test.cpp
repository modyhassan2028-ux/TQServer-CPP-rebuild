// ============================================================================
// cqbase_d26 — the CSyndicate constructor and the ten container primitives under it,
//   checked at every offset the binary writes
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synobjects.h"
#include "modules/syndicate/src/synlist.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static void* g_pOwnerSlotArg = nullptr;
static int32_t g_nOwnerSlotId = 0;
static void* g_pBoardMarker = nullptr;

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

// the owner's vtable slot at +0x120
static void* OwnerOpenBoard(void* pSelf, int32_t nId) {
    g_pOwnerSlotArg = pSelf;
    g_nOwnerSlotId = nId;
    return g_pBoardMarker;
}

struct FakeOwner {
    void** ppVft;
};
static void* g_aOwnerVft[0x130 / 8];
static FakeOwner g_Owner;

// free everything the constructor allocated, so the leak sanitiser stays quiet
static void Cleanup(CSyndicate* p) {
    for (int i = 0; i < 11; ++i) ::operator delete(p->aList11[i].pNode);
    SynBlock* aBlocks[] = {&p->blk08, &p->blk260, &p->blk2A0, &p->blk2E0,
                           &p->blk320, &p->blk360, &p->blk3E8};
    for (size_t i = 0; i < sizeof(aBlocks) / sizeof(aBlocks[0]); ++i) {
        ::operator delete(aBlocks[i]->pNode);
        ::operator delete(aBlocks[i]->pHeader);
    }
    p->str3B8.~basic_string();
}

static void CheckBlock(SynBlock* pBlock, unsigned char* pBase, size_t uOff,
                       size_t uHeadFlagOff, size_t uNilFlagOff) {
    assert((unsigned char*)pBlock == pBase + uOff);
    assert(pBlock->pNode != nullptr);
    assert(*(void**)pBlock->pNode == (void*)pBlock);      // the node points back at its head
    assert(pBlock->pHeader != nullptr);
    // the header points at itself three times
    assert(*(void**)pBlock->pHeader == pBlock->pHeader);
    assert(*(void**)((char*)pBlock->pHeader + 0x08) == pBlock->pHeader);
    assert(*(void**)((char*)pBlock->pHeader + 0x10) == pBlock->pHeader);
    assert(*(uint8_t*)((char*)pBlock->pHeader + uHeadFlagOff) == 1);
    assert(*(uint8_t*)((char*)pBlock->pHeader + uNilFlagOff) == 1);
    assert(pBlock->u38 == 0);
    // the fields the initialiser never writes keep what was there
    assert(pBlock->u8 == 0xCDCDCDCDCDCDCDCDull);
}

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    g_aOwnerVft[0x120 / 8] = (void*)&OwnerOpenBoard;
    g_aOwnerVft[0] = (void*)&OwnerOpenBoard;
    g_Owner.ppVft = g_aOwnerVft;

    // ---- the message board comes back, so the two map blocks get cleared
    {
        alignas(8) unsigned char aMem[0x450];
        std::memset(aMem, 0xCD, sizeof(aMem));
        CSyndicate* p = (CSyndicate*)aMem;

        static int nBoard;
        g_pBoardMarker = &nBoard;
        g_nOwnerSlotId = 0;
        g_sLogs.clear();

        assert(p->Construct(&g_Owner, (void*)0xE3, (void*)0xE4) == p);
        assert(g_pOwnerSlotArg == (void*)&g_Owner);
        assert(g_nOwnerSlotId == 0x89c);                  // the board id it asks for
        assert(p->pMsgBd == (void*)&nBoard);
        assert(p->pVftable == g_pVftableCSyndicate);      // the table slot, blank for now

        // the eleven simple lists, each linked back at its own head
        for (int i = 0; i < 11; ++i) {
            SynSimpleList* pL = &p->aList11[i];
            assert(pL->pNode != nullptr);
            assert(*(void**)pL->pNode == (void*)pL);
            assert(pL->u18 == 0 && pL->u20 == 0 && pL->u28 == 0);
            assert(pL->u8 == 0xCDCDCDCDCDCDCDCDull);      // never written
            assert(pL->u10 == 0xCDCDCDCDCDCDCDCDull);
        }

        // the five owned blocks, in their two shapes
        CheckBlock(&p->blk08, aMem, 0x08, 0x20, 0x21);
        CheckBlock(&p->blk260, aMem, 0x260, 0x1c, 0x1d);
        CheckBlock(&p->blk2A0, aMem, 0x2a0, 0x1c, 0x1d);
        CheckBlock(&p->blk2E0, aMem, 0x2e0, 0x1c, 0x1d);
        CheckBlock(&p->blk320, aMem, 0x320, 0x1c, 0x1d);
        CheckBlock(&p->blk360, aMem, 0x360, 0x60, 0x61);
        CheckBlock(&p->blk3E8, aMem, 0x3e8, 0x28, 0x29);

        assert(p->u3A0 == 0);
        // the two misaligned stores wipe 0x3a4..0x3b3 and stop before +0x3b4
        for (int i = 0x3a4; i < 0x3b4; ++i) assert(aMem[i] == 0);
        assert(*(uint32_t*)(aMem + 0x3b4) == 0xCDCDCDCD);   // left as it was

        assert(p->str3B8.empty());                          // a fresh string
        assert(p->u3E0 == nullptr);
        assert(p->u428 == nullptr);
        assert(p->pOwner == (void*)&g_Owner);
        assert(p->p438 == (void*)0xE3);
        assert(p->p440 == (void*)0xE4);
        assert(p->u448 == 0);
        assert(g_sLogs.empty());                            // a board is a quiet path

        Cleanup(p);
    }

    // ---- no message board: the constructor reports it and skips the clearing
    {
        alignas(8) unsigned char aMem[0x450];
        std::memset(aMem, 0xCD, sizeof(aMem));
        CSyndicate* p = (CSyndicate*)aMem;

        g_pBoardMarker = nullptr;
        g_sLogs.clear();
        assert(p->Construct(&g_Owner, nullptr, nullptr) == p);
        assert(p->pMsgBd == nullptr);
        assert(g_sLogs.size() == 1);
        assert(g_sLogs[0].find("CHECK") != std::string::npos);
        // the blocks are still built, and the misaligned wipe did not run
        assert(p->blk2A0.u38 == 0 && p->blk2E0.u38 == 0);
        assert(*(uint32_t*)(aMem + 0x3a4) == 0xCDCDCDCD);

        Cleanup(p);
    }

    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D26_OK: the syndicate constructor and its ten container primitives, 11 units, 38 checks\n");

    return 0;
}
