// ============================================================
// Training.dll — Unit T3 (D15) regression: the std::map
// PUBLIC-API family + the mgr accessor + the CMsg
// wire-glue family. Verbatim: 1419e3750/3840/3860/3a10/
// 3aa0/3c50/3ca0/3de0/3e00/42a0/4320/4350/4170 + the
// CMsg glue (50b0..56c0) + the dispatcher 1419e54c0.
// Must print TRAINING-D15-OK.
#include "../Exe/Dll/Training/Port/TrainingMapApi.h"
#include "../Exe/Dll/Training/Port/TrainingMsgGlue.h"
#include "../Exe/Dll/Training/Port/TrainingModule.h"
#include "../Exe/Dll/Training/Port/TrainingMgr.h"
#include "../Exe/Dll/Training/Port/TrainingMap.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace training;

// ---- test helpers (NOT ported code) ----
static bool s_bTrapped = false;
static void TrapInvalidParameter() { s_bTrapped = true; }
static int CheckRB(SMapKernel* k, STreeNode* n) {
    if (n->m_bIsnil31) return 1;
    if (n->m_bColor30 == 0) {
        assert(n->m_pLeft00->m_bColor30 == 1);
        assert(n->m_pRight10->m_bColor30 == 1);
    }
    int l = CheckRB(k, n->m_pLeft00);
    int r = CheckRB(k, n->m_pRight10);
    assert(l == r);
    return l + (n->m_bColor30 == 1);
}
static void CheckTree(SMapKernel* k) {
    if (k->m_pHead30->m_pLeft00 == k->m_pHead30) {
        assert(k->m_nSize38 == 0);
        return;
    }
    std::vector<uint32_t> v;
    SMapIterator it;
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
    assert((uint32_t)k->m_pHead30->m_pLeft00->m_nKey18
        == v.front());
    assert((uint32_t)k->m_pHead30->m_pRight10->m_nKey18
        == v.back());
    assert(k->m_pHead30->m_pParent08->m_bColor30 == 1);
    CheckRB(k, k->m_pHead30->m_pParent08);
}
// the map-side helper (test-side ctor)
static void TstCtor(SMapKernel* k) {
    k->m_pProxy00 = nullptr;
    CtorKernelCore(k);
}
static SValRec MkRec(uint32_t k) {
    SValRec r;
    r.m_nKey = k;
    r.m_pVal = (void*)0;
    r.m_nVal2 = 0;
    return r;
}
static STreeNode* FindNode(SMapKernel* k,
                           uint32_t key) {
    STreeNode* n = k->m_pHead30->m_pParent08;
    while (!n->m_bIsnil31) {
        if ((uint32_t)n->m_nKey18 == key)
            return n;
        if ((uint32_t)n->m_nKey18 < key)
            n = n->m_pRight10;
        else
            n = n->m_pLeft00;
    }
    return nullptr;
}

int main() {
    int nAlloc = 0, nFree = 0;
    g_fnAlloc = [&](size_t n) {
        ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p) { ++nFree; free(p); };
    g_fnInvalidParameter = TrapInvalidParameter;
    g_fnTime64 = []() -> int64_t { return 1000; };

    // ---------- 1. TryEmplace ----------
    {
        SMapKernel k;
        TstCtor(&k);
        STryEmplaceOut o;
        SValRec r = MkRec(50);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 1);
        assert(o.m_pNode08->m_nKey18 == 50);
        CheckTree(&k);
        // dup: right path (key > the root)
        r = MkRec(70);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 1);
        r = MkRec(70);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 0);
        assert(o.m_pNode08->m_nKey18 == 70);
        assert(k.m_nSize38 == 2);
        // left path dup: 40, 40
        r = MkRec(40);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 1);
        r = MkRec(40);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 0);
        assert(o.m_pNode08->m_nKey18 == 40);
        assert(k.m_nSize38 == 3);
        // between: the left path pred check (60 between
        // 50 and 70)
        r = MkRec(60);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 1);
        CheckTree(&k);
        assert(k.m_nSize38 == 4);
        // the Lmost path (smaller than all)
        r = MkRec(10);
        TryEmplace(&k, &o, &r);
        assert(o.m_bInserted10 == 1);
        CheckTree(&k);
        assert(k.m_nSize38 == 5);
        KernelDtorProxy(&k);
    }

    // ---------- 2. Distance ----------
    {
        SMapKernel k;
        TstCtor(&k);
        for (uint32_t key : {5u, 3u, 8u, 1u, 9u}) {
            SValRec r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        // distance(begin, end) == 5
        const void* aBeg[2] = {k.m_pProxy00,
            k.m_pHead30->m_pLeft00};
        const void* aEnd[2] = {k.m_pProxy00,
            k.m_pHead30};
        uint64_t n = 0;
        Distance(aBeg, aEnd, &n);
        assert(n == 5);
        // distance(mid, end) == 3 (from 5)
        const void* aMid[2] = {k.m_pProxy00,
            FindNode(&k, 5)};
        n = 0;
        Distance(aMid, aEnd, &n);
        assert(n == 3);
        // distance(x, x) == 0
        n = 0;
        Distance(aMid, aMid, &n);
        assert(n == 0);
        // the proxy gate: mismatched proxies
        const void* aBad[2] = {(void*)0x1234,
            k.m_pHead30};
        n = 0;
        s_bTrapped = false;
        Distance(aBad, aEnd, &n);
        assert(s_bTrapped);
        KernelDtorProxy4320(&k);
    }

    // ---------- 3. EraseRange ----------
    {
        SMapKernel k;
        TstCtor(&k);
        for (uint32_t key : {2u, 4u, 6u, 8u, 10u}) {
            SValRec r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        // erase(begin, end) -> the Clear path
        void* aBeg[2] = {k.m_pProxy00,
            k.m_pHead30->m_pLeft00};
        void* aEnd[2] = {k.m_pProxy00,
            k.m_pHead30};
        SMapIterator out;
        EraseRange(&k, &out, aBeg, aEnd);
        assert(k.m_nSize38 == 0);
        assert(k.m_pHead30->m_pLeft00 == k.m_pHead30);
        CheckTree(&k);
        // rebuild + erase a middle range [4..8)
        for (uint32_t key : {2u, 4u, 6u, 8u, 10u}) {
            SValRec r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        void* aF[2] = {k.m_pProxy00,
            FindNode(&k, 4)};
        void* aL[2] = {k.m_pProxy00,
            FindNode(&k, 8)};
        EraseRange(&k, &out, aF, aL);
        assert(k.m_nSize38 == 3);
        assert(FindNode(&k, 4) == nullptr);
        assert(FindNode(&k, 6) == nullptr);
        assert(FindNode(&k, 2) && FindNode(&k, 8)
            && FindNode(&k, 10));
        CheckTree(&k);
        assert(out.m_pProxy00 == k.m_pProxy00);
        assert(out.m_pNode08 == FindNode(&k, 8));
        KernelDtorProxy(&k);
    }

    // ---------- 4. LowerBoundRef ----------
    {
        SMapKernel k;
        TstCtor(&k);
        for (uint32_t key : {1u, 3u, 5u}) {
            SValRec r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        SMapIterator lb;
        void* pRet = LowerBoundRef(&k, &lb, 4);
        assert(pRet == &lb);
        assert((uint32_t)lb.m_pNode08->m_nKey18 == 5);
        KernelDtorProxy(&k);
    }

    // ---------- 5. EraseKeyCount ----------
    {
        SMapKernel k;
        TstCtor(&k);
        for (uint32_t key : {5u, 7u, 9u}) {
            SValRec r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        assert(EraseKeyCount(&k, 7) == 1);
        assert(FindNode(&k, 7) == nullptr);
        assert(k.m_nSize38 == 2);
        CheckTree(&k);
        assert(EraseKeyCount(&k, 100) == 0);
        assert(EraseKeyCount(&k, 5) == 1);
        assert(EraseKeyCount(&k, 9) == 1);
        assert(k.m_nSize38 == 0);
        KernelDtorProxy(&k);
    }

    // ---------- 6. EmplaceHint ----------
    {
        // the empty tree
        SMapKernel k;
        TstCtor(&k);
        SValRec r = MkRec(42);
        SMapIterator out;
        const void* aHint[2] = {k.m_pProxy00,
            k.m_pHead30};
        EmplaceHint(&k, &out, aHint, &r);
        assert(k.m_nSize38 == 1);
        assert(FindNode(&k, 42));
        KernelDtorProxy(&k);

        // begin/end/middle hints on {10,20,30}
        TstCtor(&k);
        for (uint32_t key : {10u, 20u, 30u}) {
            r = MkRec(key);
            STryEmplaceOut o;
            TryEmplace(&k, &o, &r);
        }
        // hint == begin, key < begin -> LEFT of hint
        r = MkRec(5);
        const void* aB[2] = {k.m_pProxy00,
            FindNode(&k, 10)};
        EmplaceHint(&k, &out, aB, &r);
        assert(FindNode(&k, 5)
            && (uint32_t)k.m_pHead30->m_pLeft00
                ->m_nKey18 == 5);
        CheckTree(&k);
        // hint == end, key > Rmost -> RIGHT of Rmost
        r = MkRec(99);
        const void* aE[2] = {k.m_pProxy00,
            k.m_pHead30};
        EmplaceHint(&k, &out, aE, &r);
        assert(FindNode(&k, 99)
            && (uint32_t)k.m_pHead30->m_pRight10
                ->m_nKey18 == 99);
        CheckTree(&k);
        // middle: key < hint, pred->key < key -> insert
        // between (pred has no right child)
        r = MkRec(15);
        const void* aM[2] = {k.m_pProxy00,
            FindNode(&k, 20)};
        EmplaceHint(&k, &out, aM, &r);
        assert(FindNode(&k, 15));
        CheckTree(&k);
        // middle: hint->key < key, next check
        r = MkRec(17);
        EmplaceHint(&k, &out, aM, &r);   // aM = 20
        assert(FindNode(&k, 17));
        CheckTree(&k);
        // dup via hint: no insert possible through
        // TryEmplace fallback — the hint points at a
        // non-adjacent node
        r = MkRec(12);   // between 10 and 15: the
                         // hint 20 fails both checks
        EmplaceHint(&k, &out, aM, &r);
        assert(FindNode(&k, 12));
        CheckTree(&k);
        assert(k.m_nSize38 == 8);
        KernelDtorProxy(&k);
    }

    // ---------- 7. ProxyChainPush x3 ----------
    {
        void* pChain = nullptr;
        ProxyChainPush(&pChain);
        assert(pChain != nullptr);
        void* p1 = pChain;
        ProxyChainPush4120(&pChain);
        assert(*(void**)pChain == p1);
        void* p2 = pChain;
        ProxyChainPush42d0(&pChain);
        assert(*(void**)pChain == p2);
        void* p3 = pChain;
        assert(*(void**)p3 == p2);
        // DeletePtr/DeletePtr2 free the value; the
        // chain pointer var itself is untouched (the
        // ORIGINAL frees *pp only)
        DeletePtr(&p3);
        DeletePtr2((void**)&p2);
        g_fnFree(p1);   // the chain tail
    }

    // ---------- 8. MgrOpIndex (the mgr accessor) ------
    {
        SMapKernel k;   // a kernel like mgr+0x18
        TstCtor(&k);
        uint32_t uId = 77;
        uint64_t nSize0 = k.m_nSize38;
        void** pSlot = MgrOpIndex(&k, &uId);
        assert(k.m_nSize38 == nSize0 + 1);
        // the slot = node + 0x20: slot[1] = +0x28
        pSlot[1] = (void*)0xdeadbeef;
        STreeNode* n = FindNode(&k, 77);
        assert(n && n->m_nVal28 == 0xdeadbeef);
        assert(n->m_nVal28 == (uint64_t)(uintptr_t)
            (void*)0xdeadbeef);
        // hit: the same slot, no insert
        void** pSlot2 = MgrOpIndex(&k, &uId);
        assert(pSlot2 == pSlot);
        assert(k.m_nSize38 == nSize0 + 1);
        // a second miss: the rec carries the g_fnTime64
        // clock (1000) as the val2 default
        uint32_t uId2 = 33;
        void** pSlot3 = MgrOpIndex(&k, &uId2);
        assert(pSlot3 != pSlot);
        STreeNode* n2 = FindNode(&k, 33);
        assert((uint32_t)n2->m_nKey18 == 33);
        assert(n2->m_nVal28 == 1000);   // _time64 seam
        CheckTree(&k);
        KernelDtorProxy(&k);
    }

    // ---------- 9. the CMsg glue family ----------
    {
        // base ctor
        CMsgBase msg;
        memset(&msg, 0, sizeof(msg));
        CtorCMsgBase(&msg);
        assert(strcmp((char*)msg.m_pVftable,
                      "tq::CMsg") == 0);

        // CMsgTraining: ctor (module ctor) + Make
        CtorMsgTraining(&msg);
        assert(strcmp(
            (char*)msg.m_pVftable,
            "training::CMsgTraining::vftable") == 0);
        assert(MakeMsgTraining(&msg, 2, 0));
        uint8_t* pBuf =
            (uint8_t*)*(void**)((uint8_t*)&msg
                + 0x408);
        assert(*(uint16_t*)pBuf == 0xc);
        assert(*(uint16_t*)(pBuf + 2) == 0x7fc);
        assert(*(uint16_t*)(pBuf + 4) == 2);
        assert(*(uint32_t*)(pBuf + 8) == 0);
        // the dispatcher: action 0/1/3/4
        int nAct = -1;
        g_fnMgrvt30 = [&](uint32_t u) {
            nAct = 0; assert(u == 5); };
        g_fnMgrvt40 = [&](uint32_t u) {
            nAct = 1; assert(u == 5); };
        g_fnMgrvt28 = [&](uint32_t u) {
            nAct = 3; assert(u == 5); };
        g_fnMgrvt38 = [&](uint32_t u) {
            nAct = 4; assert(u == 5); };
        // the dispatcher uses the SINGLETON mgr — reset
        // it for a clean state
        ResetTrainingMgrForTest();
        *(uint16_t*)(pBuf + 4) = 0;
        DispatchMsgTraining(&msg, 5);
        assert(nAct == 0);
        *(uint16_t*)(pBuf + 4) = 1;
        DispatchMsgTraining(&msg, 5);
        assert(nAct == 1);
        *(uint16_t*)(pBuf + 4) = 3;
        DispatchMsgTraining(&msg, 5);
        assert(nAct == 3);
        *(uint16_t*)(pBuf + 4) = 4;
        DispatchMsgTraining(&msg, 5);
        assert(nAct == 4);
        *(uint16_t*)(pBuf + 4) = 9;
        DispatchMsgTraining(&msg, 5);   // no-op
        assert(nAct == 4);
        // the dispatcher's singleton: the atexit
        // teardown (the balance) + the flag reset
        AtexitTeardown();
        ResetTrainingMgrForTest();

        // CMsgTrainingInfo
        memset(&msg, 0, sizeof(msg));
        CtorMsgTrainingInfo(&msg);
        assert(strcmp(
            (char*)msg.m_pVftable,
            "training::CMsgTrainingInfo::vftable")
            == 0);
        assert(MakeMsgTrainingInfo(&msg, 1, 2, 3,
                                   4));
        pBuf = (uint8_t*)*(void**)((uint8_t*)&msg
            + 0x408);
        assert(*(uint16_t*)pBuf == 0x10);
        assert(*(uint16_t*)(pBuf + 2) == 0x7fb);
        assert(*(uint16_t*)(pBuf + 4) == 1);
        assert(*(uint16_t*)(pBuf + 6) == 2);
        assert(*(uint16_t*)(pBuf + 8) == 3);
        assert(*(uint32_t*)(pBuf + 0xc) == 4);

        // TryCreate type checks
        bool bCreated = false;
        g_fnCMsgCreate = [&](void* p, const char*,
                            uint16_t) {
            bCreated = true;
            *(uint16_t*)((uint8_t*)p + 0x50) = 0x3ea;
            return true;
        };
        assert(TryCreateMsgLogin(&msg, "x", 1));
        assert(!TryCreateMsgLogout(&msg, "x", 1));
        assert(!TryCreateMsgTraining(&msg, "x", 1));
        assert(!TryCreateMsgTrainingInfo(&msg, "x",
                                         1));
        g_fnCMsgCreate = [&](void* p, const char*,
                            uint16_t) {
            *(uint16_t*)((uint8_t*)p + 0x50) = 0x7fb;
            return true;
        };
        assert(TryCreateMsgTrainingInfo(&msg, "x", 1));
        // the create-false path
        g_fnCMsgCreate = [](void*, const char*,
                            uint16_t) {
            return false;
        };
        assert(!TryCreateMsgLogin(&msg, "x", 1));

        // the dtors + deleting dtors. The deleting dtors
        // FREE the object -> each gets its own HEAP
        // buffer (a stack buffer would corrupt the
        // balance with the counting free seam)
        uint8_t* mem = (uint8_t*)g_fnAlloc(0x410);
        memset(mem, 0xCD, 0x410);
        DtorMsgLogin((CMsgBase*)mem);
        assert(strcmp((char*)((CMsgBase*)mem)
            ->m_pVftable, "tq::CMsg") == 0);
        DtorMsgLogout((CMsgBase*)mem);
        DtorMsgTraining((CMsgBase*)mem);
        DtorMsgTrainingInfo((CMsgBase*)mem);
        // the deleting dtors, uDel = 0: no free
        assert(DtorDeletingMsgLogin((CMsgBase*)mem, 0)
            == (CMsgBase*)mem);
        assert(DtorDeletingMsgLogout((CMsgBase*)mem, 0)
            == (CMsgBase*)mem);
        assert(DtorDeletingMsgTraining(
                    (CMsgBase*)mem, 0)
            == (CMsgBase*)mem);
        assert(DtorDeletingMsgTrainingInfo(
                    (CMsgBase*)mem, 0)
            == (CMsgBase*)mem);
        // the deleting paths with the free: 4 heap objs
        for (int i = 0; i < 4; i++) {
            uint8_t* p = (uint8_t*)g_fnAlloc(0x410);
            memset(p, 0, 0x410);
            switch (i) {
            case 0:
                DtorDeletingMsgLogin((CMsgBase*)p, 1);
                break;
            case 1:
                DtorDeletingMsgLogout((CMsgBase*)p, 1);
                break;
            case 2:
                DtorDeletingMsgTraining(
                    (CMsgBase*)p, 1);
                break;
            case 3:
                DtorDeletingMsgTrainingInfo(
                    (CMsgBase*)p, 1);
                break;
            }
        }
        g_fnFree(mem);   // the plain-dtor buffer
    }

    // ---------- 10. MgrDtorProxy ----------
    {
        ResetTrainingMgrForTest();
        CTrainingMgr* pMgr = GetTrainingMgr();
        uint64_t nSz = pMgr->m_kern18.m_nSize38;
        assert(nSz == 0);
        MgrDtorProxy(pMgr);
        assert(strcmp((char*)pMgr->m_pVftable00,
            "training::CTrainingMgr::vftable") == 0);
            ResetTrainingMgrForTest();
    }

    assert(nAlloc == nFree);   // the exact balance
    printf("TRAINING-D15-OK\n");
    return 0;
}
