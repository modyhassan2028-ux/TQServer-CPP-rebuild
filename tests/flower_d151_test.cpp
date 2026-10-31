// D151 — the container helpers and the base constructions the D-series left
// (0x140d95f10, 0x140d970e0, 0x140d96710/96e60, 0x140d94940/94980,
//  0x140d94a50/94ea0, 0x140d95400, 0x140d949c0, 0x140d970b0/97160,
//  0x140d961d0/96b20, 0x140d9a730/988cc, 0x140d939b0, 0x140d97c10/97c40/97c80,
//  0x140d93240)
#include "modules/flower/src/stl_helpers.h"
#include "modules/flower/src/stl_tree.h"
#include "modules/flower/src/stl_iterators.h"
#include "modules/flower/src/flowerbase.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace flower::stl;

struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uKey, uVal;
    uint8_t cColor, cNil, tail[6];
};
static uint64_t Size(void** tree) { return (uint64_t)tree[7]; }
static Node* InsertValue(void** tree, uint32_t key) {
    uint64_t elem[2] = { key, 0 };
    int64_t out[3] = { 0, 0, 0 };
    TreeInsertValue((int64_t*)tree, out, (uint32_t*)elem);
    return (Node*)out[1];
}
static void* g_pHeapName = nullptr;
static int g_nHeapCtor = 0;
static int g_nTerminate = 0;
static int g_nAtexit = 0;
static void HookHeapCtor(void* p, const char* psz) { g_pHeapName = (void*)psz; g_nHeapCtor++; (void)p; }
static void HookTerminate() { g_nTerminate++; }
static void HookAtexit(void*) { g_nAtexit++; }

int main() {
    g_pfnInvalidParameter = nullptr;

    // ---- the owner init: the same head shape as 0x140d97b10
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelfB(tree);
    Node* nil = (Node*)tree[6];
    assert(tree[0] != nullptr && nil != nullptr);
    assert(nil->cColor == 1 && nil->cNil == 1);
    assert(nil->pLeft == nil && nil->pParent == nil && nil->pRight == nil);
    assert(Size(tree) == 0);
    for (uint32_t k = 1; k <= 4; ++k) InsertValue(tree, k * 10);
    assert(Size(tree) == 4);

    // ---- the advance that writes the iterator back, against TreeDistance
    int64_t itFirst[2] = { (int64_t)tree[0], (int64_t)nil->pLeft };
    int64_t itEnd[2] = { (int64_t)tree[0], (int64_t)tree[6] };
    uint64_t uWalk = 0;
    TreeAdvanceCount(itFirst, itEnd, &uWalk);
    assert(uWalk == 4);
    assert(itFirst[1] == (int64_t)tree[6]);          // the walk left the iterator at the end
    uint64_t uSame = 0;
    int64_t itAgain[2] = { (int64_t)tree[0], (int64_t)nil->pLeft };
    TreeDistance(itAgain, itEnd, &uSame);
    assert(uSame == 4);                              // the two agree on the count

    // ---- the inequality and the bind
    int64_t itA[4] = { (int64_t)tree[0], (int64_t)nil->pLeft,
                       (int64_t)tree[0], (int64_t)tree[6] };
    assert(IterNotEqual(&itA[0], &itA[2]) == true);
    assert(IterNotEqual(&itA[0], &itA[0]) == false);
    int64_t aTagWord = 0x1234;
    void* pNodeWord = tree[0];
    void* abOut[2] = { nullptr, nullptr };
    IteratorBind(abOut, (void*)&aTagWord, &pNodeWord);
    assert(abOut[0] == tree[0]);                     // the tag comes from the node
    assert(abOut[1] == (void*)&aTagWord);

    // ---- the two allocator binds: a fresh node that points back at the owner
    void* aOwner[2] = { nullptr, nullptr };
    ContainerBindA(aOwner);
    assert(aOwner[0] != nullptr && aOwner[1] == nullptr);
    assert(*(void**)aOwner[0] == (void*)aOwner);     // the node points at its owner
    FreeBlockA(&aOwner[0]);
    void* aOwnerB[2] = { nullptr, nullptr };
    ContainerBindB(aOwnerB);
    assert(aOwnerB[0] != nullptr);
    assert(*(void**)aOwnerB[0] == (void*)aOwnerB);
    FreeBlockB(&aOwnerB[0]);

    // ---- the vector cursor: the step and the deref, both against +0x20
    int64_t aStore[3] = { 0xAA, 0xBB, 0xCC };
    int64_t aCtl[5] = { 0, 0, 0, 0, 0 };
    aCtl[4] = (int64_t)&aStore[3];                   // the +0x20 limit
    int64_t aCtlTag[1] = { (int64_t)aCtl };          // the cursor's first word
    int64_t itVec[2] = { (int64_t)aCtlTag, (int64_t)&aStore[0] };
    assert(VectorIterValue(itVec) == (int64_t)&aStore[0]);
    VectorIterNext(itVec);
    assert(itVec[1] == (int64_t)&aStore[1]);
    assert(*(int64_t*)VectorIterValue(itVec) == 0xBB);
    VectorIterNext(itVec);
    VectorIterNext(itVec);
    assert(itVec[1] == (int64_t)&aStore[3]);         // the end is allowed as a value

    // ---- the record-set cursor: refused at the +0x30 end, else the element
    int64_t aSetCtl[7] = { 0, 0, 0, 0, 0, 0, 0 };
    aSetCtl[6] = 0;                                  // the +0x30 end marker
    int64_t aSetTag[1] = { (int64_t)aSetCtl };
    int64_t itSet[2] = { (int64_t)aSetTag, (int64_t)nil->pLeft };
    assert(TreeIterValue(itSet) == (int64_t)nil->pLeft + 0x18);
    assert(TreeIterValueB(itSet) == (int64_t)nil->pLeft + 0x18);
    assert(*(uint32_t*)TreeIterValue(itSet) == 10);  // the first key of the set

    // ---- the magic guards
    int aMagicA = -0x3ffffffb;
    int aMagicOther = 0x1234;
    void* pMagicA = &aMagicA;
    void* pMagicOther = &aMagicOther;
    assert(MemMagicCheckA(&pMagicA) == true);
    assert(MemMagicCheckA(&pMagicOther) == false);
    g_pfnHelperTerminate = HookTerminate;
    int aMagicB = -0x1f928c9d;
    void* pMagicB = &aMagicB;
    assert(MemMagicCheckB(&pMagicOther) == 0);
    assert(g_nTerminate == 0);
    MemMagicCheckB(&pMagicB);
    assert(g_nTerminate == 1);                       // the match terminates

    // ---- the heap singleton: one construction, the name, the atexit bracket
    g_pfnHelperHeapCtor = HookHeapCtor;
    g_pfnHelperAtexit = HookAtexit;
    void* pHeap1 = TodayFlowerHeap();
    void* pHeap2 = TodayFlowerHeap();
    assert(pHeap1 == pHeap2);
    assert(g_nHeapCtor == 1);                        // the once flag holds
    assert(std::strcmp((const char*)g_pHeapName, "CTodayFlower") == 0);
    assert(g_nAtexit == 1);

    // ---- the base constructions
    flower::g_pVftCMsgFlowerBase = (void*)0xC0FFEE;
    flower::g_pVftIModuleFlower = (void*)0xBEEF;
    static int s_nInit = 0;
    flower::g_pfnCMsgInitFlower = [](void*) { s_nInit++; };
    int64_t aObj[4] = { 0, 0, 0, 0 };
    flower::CMsgCtorFlower(aObj);
    assert(*(void**)aObj == (void*)0xC0FFEE && s_nInit == 1);
    int64_t aObj2[4] = { 0, 0, 0, 0 };
    flower::CMsgBaseCtorFlower(aObj2);
    assert(*(void**)aObj2 == (void*)0xC0FFEE && s_nInit == 1);   // no Init here
    int64_t aObj3[4] = { 0, 0, 0, 0 };
    flower::CMsgDtorFlower(aObj3, 0);
    assert(*(void**)aObj3 == (void*)0xC0FFEE);
    int64_t aObj4[4] = { 0, 0, 0, 0 };
    flower::IModuleBaseCtorFlower(aObj4);
    assert(*(void**)aObj4 == (void*)0xBEEF);

    // ---- the CRT glue: the empty initterm passes and the exit-state word
    flower::InitTermA();
    flower::InitTermB();
    flower::g_iFlowerExitState = 0;
    flower::ExitStateReset();
    assert(flower::g_iFlowerExitState == -1);

    // ---- the dispose path: the whole set, then the owner node
    TreeDispose((int64_t*)tree);

    printf("FLOWER_D151_OK: container helpers and base constructions\n");
    return 0;
}
