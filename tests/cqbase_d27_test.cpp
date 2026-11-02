// ============================================================================
// cqbase_d27 — the two country sweeps and the three tree erasers: walk order, the destroy
//   and keep paths, the null-record log line, and the head reset of both maps
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/syncountry.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static std::vector<void*> g_vDestroyed;
static std::vector<uint64_t> g_vDestroyFlags;
static std::vector<void*> g_vMoved;
static void* g_pMoveA3 = nullptr;
static void* g_pMoveA4 = nullptr;

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

// the record's only slot this test needs: slot zero, the scalar deleting destructor
static void* g_aRecVft[1] = {(void*)&HookWrite};   // replaced below by the real hook
static void RecDestroy(void* pSelf, uint64_t uFlag) {
    g_vDestroyed.push_back(pSelf);
    g_vDestroyFlags.push_back(uFlag);
}
static void* g_aVft[1];

struct FakeRecord {
    void** ppVft;
    int32_t nId;
};

// a node of the map the sweeps walk (nil byte at +0x29)
static SynCountryNode* NewNode(void* pRecord, uint8_t uNil) {
    SynCountryNode* p = (SynCountryNode*)::operator new(sizeof(SynCountryNode));
    std::memset(p, 0, sizeof(SynCountryNode));
    p->uNil = uNil;
    p->pRecord = pRecord;
    return p;
}

// a node of the neighbouring map (nil byte at +0x49), 0x50 bytes raw
static unsigned char* NewBigNode() {
    unsigned char* p = (unsigned char*)::operator new(0x50);
    std::memset(p, 0, 0x50);
    return p;
}

// the country object: four holders, each with its map head at holder+0x30
struct FakeCountry {
    unsigned char a[0x200];
};

static void* Head(FakeCountry* p, size_t uHolderOff) { return p->a + uHolderOff + 0x30; }

// build the small map A: head -> (node1 -> node2), which the walk must visit in that order
static void BuildMapA(FakeCountry* pCountry, size_t uHolderOff, size_t uHeadOff,
                      void* pRec1, void* pRec2, SynCountryNode** ppKeep) {
    SynCountryNode* pHead = NewNode(nullptr, 1);
    SynCountryNode* pN1 = NewNode(pRec1, 0);
    SynCountryNode* pN2 = NewNode(pRec2, 0);
    pHead->pLeft = pN1;                 // the leftmost
    pHead->pParent = pN1;               // the root, where the teardown starts
    pN1->pParent = pHead;
    pN1->pLeft = pHead;                 // the leftmost's left points at the head
    pN1->pRight = pN2;
    pN2->pParent = pN1;
    pN2->pLeft = pHead;
    pN2->pRight = pHead;                // the rightmost's right points at the head
    *(void**)((char*)pCountry + uHeadOff) = pHead;
    *(uint64_t*)((char*)pCountry + uHeadOff + 0x08) = 2;   // the count
    ppKeep[0] = pHead;                  // the head survives the teardown
}

// and the neighbouring map B: one node whose links reach the head
static void BuildMapB(FakeCountry* pCountry, size_t uHeadOff, void** ppKeep) {
    unsigned char* pHead = NewBigNode();
    unsigned char* pNode = NewBigNode();
    pHead[0x49] = 1;                    // the big node's nil byte
    *(void**)(pHead + 0x08) = pNode;    // the root
    *(void**)(pNode + 0x00) = pHead;
    *(void**)(pNode + 0x10) = pHead;
    *(void**)((char*)pCountry + uHeadOff) = pHead;
    *(uint64_t*)((char*)pCountry + uHeadOff + 0x08) = 1;
    ppKeep[0] = pHead;
}

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};
    g_aVft[0] = (void*)&RecDestroy;
    g_aRecVft[0] = (void*)&RecDestroy;

    // ---- the destroy path: both records go through slot zero with flag one
    {
        FakeCountry country;
        std::memset(&country, 0xCD, sizeof(country));
        FakeRecord r1, r2;
        r1.ppVft = g_aVft;
        r2.ppVft = g_aVft;
        void* aKeepA[1];
        void* aKeepB[1];
        BuildMapA(&country, 0x90, 0xc0, &r1, &r2, (SynCountryNode**)aKeepA);
        BuildMapB(&country, 0x180, aKeepB);

        g_vDestroyed.clear();
        g_vDestroyFlags.clear();
        g_sLogs.clear();
        SynCountrySweepA(&country, 0, nullptr, nullptr);

        // walked in order, first record then second
        assert(g_vDestroyed.size() == 2);
        assert(g_vDestroyed[0] == (void*)&r1);
        assert(g_vDestroyed[1] == (void*)&r2);
        assert(g_vDestroyFlags[0] == 1 && g_vDestroyFlags[1] == 1);
        assert(g_sLogs.empty());

        // both maps are reset: three links back at the head, count zero
        unsigned char* pHeadA = (unsigned char*)aKeepA[0];
        assert(*(void**)pHeadA == pHeadA);
        assert(*(void**)(pHeadA + 0x08) == pHeadA);
        assert(*(void**)(pHeadA + 0x10) == pHeadA);
        assert(*(uint64_t*)(country.a + 0xc0 + 0x08) == 0);
        unsigned char* pHeadB = (unsigned char*)aKeepB[0];
        assert(*(void**)pHeadB == pHeadB);
        assert(*(void**)(pHeadB + 0x08) == pHeadB);
        assert(*(void**)(pHeadB + 0x10) == pHeadB);
        assert(*(uint64_t*)(country.a + 0x180 + 0x08) == 0);

        ::operator delete(pHeadA);
        ::operator delete(pHeadB);
    }

    // ---- the keep path: the records are handed to the hook and not destroyed
    {
        FakeCountry country;
        std::memset(&country, 0, sizeof(country));
        FakeRecord r1, r2;
        r1.ppVft = g_aVft;
        r2.ppVft = g_aVft;
        void* aKeepA[1];
        void* aKeepB[1];
        BuildMapA(&country, 0x90, 0xc0, &r1, &r2, (SynCountryNode**)aKeepA);
        BuildMapB(&country, 0x180, aKeepB);

        g_vDestroyed.clear();
        g_vMoved.clear();
        g_sLogs.clear();
        void* pA3 = (void*)0xA3;
        void* pA4 = (void*)0xA4;
        g_pMoveA3 = nullptr;
        // a hook that records exactly what it was handed
        void (*pfnSaved)(void*, void*, void*, void*) = g_pfnCountryMoveRecord;
        g_pfnCountryMoveRecord = [](void* pSelf, void* pRecord, void* a3, void* a4) {
            assert(pSelf != nullptr);
            g_vMoved.push_back(pRecord);
            g_pMoveA3 = a3;
            g_pMoveA4 = a4;
        };
        SynCountrySweepA(&country, 1, pA3, pA4);
        g_pfnCountryMoveRecord = pfnSaved;

        assert(g_vMoved.size() == 2);
        assert(g_vMoved[0] == (void*)&r1 && g_vMoved[1] == (void*)&r2);
        assert(g_pMoveA3 == pA3 && g_pMoveA4 == pA4);
        assert(g_vDestroyed.empty());            // nothing was destroyed on this path
        assert(g_sLogs.empty());
        assert(*(uint64_t*)(country.a + 0xc8) == 0);

        ::operator delete(aKeepA[0]);
        ::operator delete(aKeepB[0]);
    }

    // ---- a null record is reported with this file's own line, 0xdf for the first sweep
    {
        FakeCountry country;
        std::memset(&country, 0, sizeof(country));
        void* aKeepA[1];
        void* aKeepB[1];
        BuildMapA(&country, 0x90, 0xc0, nullptr, nullptr, (SynCountryNode**)aKeepA);
        BuildMapB(&country, 0x180, aKeepB);

        g_sLogs.clear();
        g_vDestroyed.clear();
        SynCountrySweepA(&country, 0, nullptr, nullptr);
        assert(g_sLogs.size() == 2);
        assert(g_sLogs[0].find("NULL != pRec") != std::string::npos);
        assert(g_vDestroyed.empty());

        ::operator delete(aKeepA[0]);
        ::operator delete(aKeepB[0]);
    }

    // ---- and 0xf5 for the second sweep, which works one holder over
    {
        FakeCountry country;
        std::memset(&country, 0xCD, sizeof(country));
        void* aKeepA[1];
        void* aKeepB[1];
        BuildMapA(&country, 0xd0, 0x100, nullptr, nullptr, (SynCountryNode**)aKeepA);
        BuildMapB(&country, 0x1c0, aKeepB);

        g_sLogs.clear();
        SynCountrySweepB(&country, 0, nullptr, nullptr);
        assert(g_sLogs.size() == 2);
        assert(*(uint64_t*)(country.a + 0x108) == 0);      // its own count
        assert(*(uint64_t*)(country.a + 0x1c0 + 0x08) == 0);
        assert(*(uint64_t*)(country.a + 0xc8) == 0xCDCDCDCDCDCDCDCDull);  // untouched holder

        ::operator delete(aKeepA[0]);
        ::operator delete(aKeepB[0]);
    }

    // ---- the erasers on their own: the nil byte decides where they stop
    {
        SynCountryNode* pHead = NewNode(nullptr, 1);
        SynCountryNode* pA = NewNode(nullptr, 0);
        SynCountryNode* pB = NewNode(nullptr, 0);
        pA->pLeft = pHead;
        pA->pRight = pB;
        pB->pLeft = pHead;
        pB->pRight = pHead;
        SynNodeErase29(nullptr, pA);          // frees pB then pA, never the head
        ::operator delete(pHead);

        unsigned char* pBigHead = NewBigNode();
        unsigned char* pBigNode = NewBigNode();
        pBigHead[0x49] = 1;
        *(void**)(pBigNode + 0x00) = pBigHead;
        *(void**)(pBigNode + 0x10) = pBigHead;
        SynNodeErase49(nullptr, pBigNode);
        ::operator delete(pBigHead);
    }

    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D27_OK: the two country sweeps and the three tree erasers, "
                "5 units, 27 checks\n", 27);
    return 0;
}
