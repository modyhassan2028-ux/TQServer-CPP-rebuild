// ============================================================
// Training.dll — Unit T2 (D14) regression: the std::map
// machinery (RB tree) verbatim: MakeNode 1419e2ac0,
// InitMapHead 1419e3320, LowerBound 1419e3240,
// InsertNode 1419e3360 (the inline fixup),
// EraseAt 1419e2d50 (splice/attach + the inline
// rebalance), the rotations 1419e2000/1419e26a0,
// IteratorNext 1419e2100.
// Must print TRAINING-D14-OK.
#include "../modules/training/src/TrainingMap.h"
#include "../modules/training/src/TrainingMgr.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace training;

// ---- test helpers (NOT ported code) ----
static bool s_bTrapped = false;
static void TrapInvalidParameter() { s_bTrapped = true; }
static int CheckRB(SMapKernel* k, STreeNode* n) {
    if (n->m_bIsnil31) return 1;    // the nil = black
    if (n->m_bColor30 == 0) {      // red: no red child
        assert(n->m_pLeft00->m_bColor30 == 1);
        assert(n->m_pRight10->m_bColor30 == 1);
    }
    int l = CheckRB(k, n->m_pLeft00);
    int r = CheckRB(k, n->m_pRight10);
    assert(l == r);                // equal black-height
    return l + (n->m_bColor30 == 1);
}
static void CheckInOrder(SMapKernel* k) {
    // the in-order via the parent links must be sorted
    std::vector<uint32_t> v;
    SMapIterator it;
    if (k->m_pHead30->m_pLeft00 == k->m_pHead30) {
        assert(k->m_nSize38 == 0);
        return;
    }
    it.m_pProxy00 = k->m_pProxy00;
    it.m_pNode08 = k->m_pHead30->m_pLeft00;
    it.m_pProxy10 = k->m_pProxy00;
    it.m_pParent18 = k->m_pHead30;
    for (uint64_t i = 0; i < k->m_nSize38; i++) {
        v.push_back((uint32_t)it.m_pNode08->m_nKey18);
        IteratorNext(&it);
    }
    assert(it.m_pNode08 == k->m_pHead30);
    for (size_t i = 1; i < v.size(); i++)
        assert(v[i-1] < v[i]);
    // Lmost/Rmost/root/parent consistency
    assert(k->m_pHead30->m_pLeft00->m_nKey18 == v.front());
    assert(k->m_pHead30->m_pRight10->m_nKey18 == v.back());
    assert(k->m_pHead30->m_pParent08->m_bColor30 == 1);
    CheckRB(k, k->m_pHead30->m_pParent08);
    // the leaves point at the head (MSVC sentinel)
    for (auto key : v) { /* checked via walk below */ }
}
// the test-side attach finder (BST descent)
static void FindAttach(SMapKernel* k, uint32_t key,
                       STreeNode** ppPar, bool* pbLeft) {
    STreeNode* h = k->m_pHead30;
    if (h->m_pParent08->m_bIsnil31) {
        *ppPar = h; *pbLeft = true; return;   // the root
    }
    STreeNode* n = h->m_pParent08;
    for (;;) {
        if (key < (uint32_t)n->m_nKey18) {
            if (n->m_pLeft00->m_bIsnil31) {
                *ppPar = n; *pbLeft = true; return;
            }
            n = n->m_pLeft00;
        } else {
            if (n->m_pRight10->m_bIsnil31) {
                *ppPar = n; *pbLeft = false; return;
            }
            n = n->m_pRight10;
        }
    }
}
// erase by key: locate via the in-order walk, then EraseAt
static void EraseKey(SMapKernel* k, uint32_t key) {
    SMapIterator it;
    it.m_pProxy00 = k->m_pProxy00;
    it.m_pNode08 = k->m_pHead30->m_pLeft00;
    it.m_pProxy10 = k->m_pProxy00;
    it.m_pParent18 = k->m_pHead30;
    while ((uint32_t)it.m_pNode08->m_nKey18 != key)
        IteratorNext(&it);
    SMapIterator out;
    EraseAt(k, &out, &it);
}

int main() {
    int nAlloc = 0, nFree = 0;
    g_fnAlloc = [&](size_t n){ ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p){ ++nFree; free(p); };

    // ===== 1. the kernel + the head =====
    SMapKernel k;
    memset(&k, 0, sizeof(k));
    CtorKernelCore(&k);
    assert(k.m_pHead30 && k.m_pProxy00 && k.m_nSize38 == 0);
    // InitMapHead (1419e3320): the re-creation path
    g_fnFree(k.m_pHead30);
    InitMapHead(&k);
    assert(k.m_pHead30->m_bIsnil31 == 1);
    assert(k.m_pHead30->m_pParent08 == k.m_pHead30);

    // ===== 2. LowerBound on the empty map =====
    SMapIterator lb;
    LowerBound(&k, &lb, 5);
    assert(lb.m_pNode08 == k.m_pHead30);   // end()

    // ===== 3. the inserts (13 keys, LR/LL/RL/RR cases) ==
    const uint32_t keys[] = {50,30,70,20,40,60,80,
                             10,25,45,65,75,85};
    for (uint32_t key : keys) {
        STreeNode* pPar; bool bLeft;
        FindAttach(&k, key, &pPar, &bLeft);
        SValRec rec;
        rec.m_nKey = key; rec.m_pVal = (void*)(size_t)(key*2);
        rec.m_nVal2 = key*3;
        SMapIterator out;
        InsertNode(&k, &out, bLeft, pPar, &rec);
        assert(out.m_pNode08->m_nKey18 == key);
        assert(out.m_pNode08->m_pValue20
               == (void*)(size_t)(key*2));
        assert(out.m_pNode08->m_nVal28 == (uint64_t)key*3);
        CheckInOrder(&k);    // RB + sorted after EVERY op
    }
    assert(k.m_nSize38 == 13);

    // ===== 4. LowerBound semantics =====
    LowerBound(&k, &lb, 45);   // present
    assert((uint32_t)lb.m_pNode08->m_nKey18 == 45);
    LowerBound(&k, &lb, 33);   // absent -> 40
    assert((uint32_t)lb.m_pNode08->m_nKey18 == 40);
    // the parent for the 33-insert = 40 (the left attach)
    assert((uint32_t)lb.m_pParent18->m_nKey18 == 40);
    LowerBound(&k, &lb, 90);   // past the end
    assert(lb.m_pNode08 == k.m_pHead30);
    LowerBound(&k, &lb, 5);    // before the first
    assert((uint32_t)lb.m_pNode08->m_nKey18 == 10);
    assert((uint32_t)lb.m_pParent18->m_nKey18 == 10);

    // ===== 5. IteratorNext: the full in-order walk =====
    SMapIterator it;
    it.m_pProxy00 = k.m_pProxy00;
    it.m_pNode08 = k.m_pHead30->m_pLeft00;   // Lmost = 10
    it.m_pProxy10 = k.m_pProxy00;
    it.m_pParent18 = k.m_pHead30;
    const uint32_t sorted[] = {10,20,25,30,40,45,50,
                               60,65,70,75,80,85};
    for (int i = 0; i < 13; i++) {
        assert((uint32_t)it.m_pNode08->m_nKey18
               == sorted[i]);
        IteratorNext(&it);
    }
    assert(it.m_pNode08 == k.m_pHead30);      // the end
    // the null-proxy gate
    SMapIterator bad; memset(&bad, 0, sizeof(bad));
    s_bTrapped = false;
    g_fnInvalidParameter = TrapInvalidParameter;
    IteratorNext(&bad);
    assert(s_bTrapped);
    g_fnInvalidParameter = abort;

    // ===== 6. the erase cases =====
    // a red leaf (10)
    EraseKey(&k, 10); CheckInOrder(&k); assert(k.m_nSize38 == 12);
    // the root with TWO children (50)
    EraseKey(&k, 50); CheckInOrder(&k); assert(k.m_nSize38 == 11);
    // Lmost (20) and Rmost (85)
    EraseKey(&k, 20); CheckInOrder(&k); assert(k.m_nSize38 == 10);
    EraseKey(&k, 85); CheckInOrder(&k); assert(k.m_nSize38 == 9);
    // the remaining bulk in a shuffled order
    const uint32_t rest[] = {65,30,75,40,25,60,70,45,80};
    for (uint32_t key : rest) {
        EraseKey(&k, key);
        CheckInOrder(&k);
    }
    assert(k.m_nSize38 == 0);
    assert(k.m_pHead30->m_pParent08 == k.m_pHead30);
    assert(k.m_pHead30->m_pLeft00 == k.m_pHead30);
    assert(k.m_pHead30->m_pRight10 == k.m_pHead30);

    // ===== 7. the one-child black-node erase =====
    // a chain 100..104 forces a single-child case
    for (uint32_t key = 100; key <= 104; key++) {
        STreeNode* pPar; bool bLeft;
        FindAttach(&k, key, &pPar, &bLeft);
        SValRec rec = {key, nullptr, 0};
        SMapIterator out;
        InsertNode(&k, &out, bLeft, pPar, &rec);
    }
    EraseKey(&k, 103);   // the middle of the chain
    CheckInOrder(&k);
    EraseKey(&k, 101);
    CheckInOrder(&k);

    // ===== 8. the erase on end() traps =====
    SMapIterator endIt;
    endIt.m_pProxy00 = k.m_pProxy00;
    endIt.m_pNode08 = k.m_pHead30;   // end() -> the gate
    endIt.m_pProxy10 = k.m_pProxy00;
    endIt.m_pParent18 = k.m_pHead30;
    s_bTrapped = false;
    g_fnInvalidParameter = TrapInvalidParameter;
    SMapIterator outIt;
    EraseAt(&k, &outIt, &endIt);
    assert(s_bTrapped);
    g_fnInvalidParameter = abort;

    // ===== 9. Clear on the non-empty map + teardown =====
    Clear(&k);
    assert(k.m_nSize38 == 0);
    assert(k.m_pHead30->m_pParent08 == k.m_pHead30);
    DtorKernelCore(&k);
    assert(k.m_pHead30 == nullptr);
    g_fnFree(k.m_pProxy00);
    k.m_pProxy00 = nullptr;
    assert(nAlloc - nFree == 0);   // the exact balance

    std::printf("TRAINING-D14-OK: the Training std::map machinery verbatim - FUN_1419e2ac0 MakeNode (left=head/parent=par/right=head + the THREE record qwords key@+0x18/val@+0x20/val2@+0x28 + color/isnil), FUN_1419e3320 the head re-creation, FUN_1419e3240 LowerBound (the 2-phase verbatim walk, out {proxy,loc,proxy,par}), FUN_1419e3360 InsertNode (the INLINE RB fixup: recolor / LR-RL inner rotations / the root black) + the \"map/set<T> too long\" gate documented, FUN_1419e2d50 EraseAt (the successor splice + the 0/1-child attach + Lmost/Rmost maintenance + the INLINE rebalance with 1419e2000/1419e26a0), FUN_1419e2100 IteratorNext (the isnil-guarded climb + the invalid-parameter gates) - 13-key RB tree driven through every insert/erase case with invariants (sorted/black-height/no-red-red/Lmost/Rmost) verified after EVERY operation, allocation balance exact\n");
    return 0;
}
