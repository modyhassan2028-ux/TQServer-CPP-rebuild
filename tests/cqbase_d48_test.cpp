// ============================================================================
// cqbase_d48 — the second block of iterator/tree plumbing: the two value accessors, the two
//   predecessor steps on a real tree, the four tree ends, and the eight tiny shapes.
//   Node layout: left +0x00, parent +0x08, right +0x10, key +0x18, value +0x20,
//   nil byte +0x29 (id) / +0x41 (name).
// ============================================================================
#include "modules/syndicate/src/synrangeB.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

static int g_nChecks = 0;
static int g_nInvalid = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static void HookInvalid() { ++g_nInvalid; }

namespace {

struct Node {
    uint8_t a[0x30];
    Node() { std::memset(a, 0, sizeof(a)); }
    void Nil(uint64_t key) { a[0x29] = 1; SetKey(key); }
    void SetKey(uint64_t k) { *(uint64_t*)(a + 0x18) = k; }
    Node* L() { return (Node*)(*(void**)(a + 0x00)); }
    void L(Node* p) { *(void**)(a + 0x00) = p; }
    Node* P() { return (Node*)(*(void**)(a + 0x08)); }
    void P(Node* p) { *(void**)(a + 0x08) = p; }
    Node* R() { return (Node*)(*(void**)(a + 0x10)); }
    void R(Node* p) { *(void**)(a + 0x10) = p; }
};

}  // namespace

int main() {
    ::syndicate::g_fnInvalidParam = &HookInvalid;

    Node nHead, nNilId, nNilName, n20, n10, n30, n25, n35;
    nNilId.Nil(0);
    nNilName.Nil(0);

    // ---- a real tree: 20 (root) with 10 / 30, and 30 with 25 / 35
    n20.SetKey(20); n10.SetKey(10); n30.SetKey(30); n25.SetKey(25); n35.SetKey(35);
    nHead.a[0x29] = 1;                    // the head is the id sentinel
    nHead.L(&n20);
    nHead.R(&n35);
    nHead.P(&nHead);

    n20.L(&n10); n20.R(&n30); n20.P(&nHead);
    n10.L(&nNilId); n10.R(&nNilId); n10.P(&n20);
    n30.L(&n25); n30.R(&n35); n30.P(&n20);
    n25.L(&nNilId); n25.R(&nNilId); n25.P(&n30);
    n35.L(&nNilId); n35.R(&nNilId); n35.P(&n30);

    // ---- the two ends
    {
        CHECK(SynMapMinId(nHead.a) == &n10);
        CHECK(SynMapMaxId(nHead.a) == &n35);
        // the name instantiation reads its nil byte at +0x41, so it is only ever run on
        // 0x48-byte nodes (see the big-node block below), never on these id nodes
        // an empty tree answers the argument itself, both ways
        Node nEmptyHead;
        nEmptyHead.L(&nNilId);
        nEmptyHead.R(&nNilId);
        CHECK(SynMapMinId(nEmptyHead.a) == nEmptyHead.a);
        CHECK(SynMapMaxId(nEmptyHead.a) == nEmptyHead.a);
    }

    // ---- the predecessor steps, sitting on the sentinel head: -1 lands on the maximum
    {
        void* aIter[2] = {&nHead, nHead.a};   // the head is the sentinel here
        (void)aIter;
        uint8_t aSent[0x50];
        std::memset(aSent, 0, sizeof(aSent));
        aSent[0x29] = 1;                       // the sentinel
        *(void**)(aSent + 0x00) = &n35;        // its left link is the maximum
        void* aIt[2] = {nHead.a, aSent};
        g_nInvalid = 0;
        SynIterPrevId(aIt);
        CHECK(aIt[1] == &n35);
        CHECK(g_nInvalid == 0);
    }

    // ---- predecessors on the real tree: 35->30->25->20->10
    {
        Node* apOrder[5] = {&n35, &n30, &n25, &n20, &n10};
        for (int i = 0; i + 1 < 5; ++i) {
            void* aIt[2] = {&nHead, apOrder[i]};
            g_nInvalid = 0;
            SynIterPrevId(aIt);
            CHECK(aIt[1] == apOrder[i + 1]);
            CHECK(g_nInvalid == 0);
        }
        // from 30 the step goes left to 25 then down its right spine (which is nil here)
        void* aIt[2] = {&nHead, &n30};
        SynIterPrevId(aIt);
        CHECK(aIt[1] == &n25);
    }

    // ---- the name instantiation uses +0x41: the same order with a 0x48-byte node
    {
        uint8_t aBig[0x48 * 5];
        std::memset(aBig, 0, sizeof(aBig));
        uint8_t* pBigHead = aBig + 0x00;
        uint8_t* pBig20 = aBig + 0x48;
        uint8_t* pBig10 = aBig + 0x90;
        uint8_t* pBig30 = aBig + 0xd8;
        uint8_t* pBigNil = aBig + 0x120;
        pBigNil[0x41] = 1;
        pBigHead[0x41] = 1;                   // the head is the name sentinel too
        *(void**)(pBigHead + 0x00) = pBig20;
        *(void**)(pBigHead + 0x08) = pBigHead;
        *(void**)(pBigHead + 0x10) = pBig30;
        *(void**)(pBig20 + 0x00) = pBig10;
        *(void**)(pBig20 + 0x08) = pBigHead;
        *(void**)(pBig20 + 0x10) = pBig30;
        *(void**)(pBig10 + 0x00) = pBigNil;
        *(void**)(pBig10 + 0x08) = pBig20;
        *(void**)(pBig10 + 0x10) = pBigNil;
        *(void**)(pBig30 + 0x00) = pBigNil;
        *(void**)(pBig30 + 0x08) = pBig20;
        *(void**)(pBig30 + 0x10) = pBigNil;
        void* aIt[2] = {pBigHead, pBig30};
        g_nInvalid = 0;
        SynIterPrevName(aIt);
        CHECK(aIt[1] == pBig20);               // 30 has no left child, so climb to its parent
        CHECK(g_nInvalid == 0);
        // and the ends agree with the name nil byte
        CHECK(SynMapMinName(pBigHead) == pBig10);
        CHECK(SynMapMaxName(pBigHead) == pBig30);
        // from the minimum the step reaches the sentinel head, which is accepted here
        void* aEnd[2] = {pBigHead, pBig10};
        g_nInvalid = 0;
        SynIterPrevName(aEnd);
        CHECK(aEnd[1] == pBigHead);            // 10's left link is the sentinel, then climb
        CHECK(g_nInvalid == 0);                // the climb stops on the head without a report
    }

    // ---- the value accessors: qword[1] + 0x18, guarded by the owner's +0x30 qword
    {
        uint8_t aHeadBuf[0x40];               // the map object's first qword is the head node
        std::memset(aHeadBuf, 0, sizeof(aHeadBuf));
        *(void**)(aHeadBuf + 0x30) = (void*)0xDEAD;
        uint8_t aOwner[0x40];
        std::memset(aOwner, 0, sizeof(aOwner));
        *(void**)aOwner = aHeadBuf;
        void* aIter[2] = {aOwner, &n20};
        g_nInvalid = 0;
        CHECK(SynIterValueId(aIter) == (void*)(n20.a + 0x18));
        CHECK(SynIterValueName(aIter) == (void*)(n20.a + 0x18));
        CHECK(g_nInvalid == 0);
        // a second qword equal to the head's +0x30 reports
        void* aBad[2] = {aOwner, *(void**)(aHeadBuf + 0x30)};
        g_nInvalid = 0;
        CHECK(SynIterValueId(aBad) == (void*)((uint8_t*)*(void**)(aHeadBuf + 0x30) + 0x18));
        CHECK(SynIterValueName(aBad) == (void*)((uint8_t*)*(void**)(aHeadBuf + 0x30) + 0x18));
        CHECK(g_nInvalid == 2);
    }

    // ---- the tiny shapes
    {
        uint8_t aSrc[0x20];
        std::memset(aSrc, 0xAB, sizeof(aSrc));
        *(uint64_t*)(aSrc + 0x00) = 0x1111;
        *(uint64_t*)(aSrc + 0x08) = 0x2222;
        uint8_t aOut[0x30];
        std::memset(aOut, 0, sizeof(aOut));
        CHECK(SynIterCopy16(aOut, aSrc) == aOut);
        CHECK(*(uint64_t*)(aOut + 0x00) == 0x1111);
        CHECK(*(uint64_t*)(aOut + 0x08) == 0x2222);
        CHECK(aOut[0x10] == 0);                      // only 16 bytes move

        uint8_t aFlag = 7;
        std::memset(aOut, 0, sizeof(aOut));
        CHECK(SynIterCopy16Flag(aOut, aSrc, &aFlag) == aOut);
        CHECK(*(uint64_t*)(aOut + 0x00) == 0x1111);
        CHECK(*(uint64_t*)(aOut + 0x08) == 0x2222);
        CHECK(aOut[0x10] == 7);

        uint32_t aKey = 0x12345678;
        uint64_t aValue = 0x99;
        uint8_t aPair[0x20];
        std::memset(aPair, 0, sizeof(aPair));
        CHECK(SynPairInit(aPair, &aKey, &aValue) == aPair);
        CHECK(*(uint32_t*)(aPair + 0x00) == 0x12345678);
        CHECK(*(uint64_t*)(aPair + 0x08) == 0x99);

        void* pBlock = ::operator new(0x20);
        SynIterRelease((void*)0x5, pBlock);           // the first argument is overwritten

        CHECK(SynIterIdent(&n20) == &n20);
        void* aClear[2] = {(void*)0x77, (void*)0x88};
        CHECK(SynIterClearIdent(aClear) == aClear);
        CHECK(aClear[0] == nullptr);
        CHECK(aClear[1] == (void*)0x88);
        CHECK(SynIterOff40(&n20) == (void*)(n20.a + 0x40));
        CHECK(SynIterMaxSize() == 0x1fffffffffffffffULL);
    }

    std::printf("SYNDICATE_D48_OK: the second iterator/tree block, 16 units, %d checks\n",
                g_nChecks);
    return 0;
}
