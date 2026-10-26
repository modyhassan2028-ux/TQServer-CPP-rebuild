// D60 test — the user log-record removal flow
// (FUN_1417ac620 + the 13 verbatim callees).
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include <cstdio>
#include <cassert>
#include <cstring>
using namespace syndicate;

// ---- the mock state ----
static int s_nInvalid, s_nLogErr, s_nSend;
static void* s_pSendSess; static uint32_t s_uSendId;
static int s_nInsertF10, s_nFindAF0, s_nErase;
static uint32_t s_uInsertKey;
static void* s_pEraseMap, * s_pEraseOut, * s_pEraseIter;
static void* s_pSortFirst, * s_pSortLast;
static int64_t s_nSortCount; static void* s_pSortPred;
static int s_nKeyLookup; static uint32_t s_uKeyLookup;
static uint64_t s_uKeyLookupRet;

// the node layout (0x30 stride): left@0,
// parent@8, right@0x10, key@0x18, value@0x20,
// isnil@0x29 (+0x3d for the acct tree)
struct TNode {
    void* pLeft; void* pParent; void* pRight;
    uint32_t uKey; uint32_t uPad;
    void* pValue;
    uint8_t ab[0x20];   // the 0x40 stride
                        // (acct-tree isnil@0x3d)
    TNode() { memset(this, 0, sizeof(*this)); }
    bool IsNil() const { return ab[1] != 0; }
};
struct TTree {   // head + 2 payload nodes
    TNode nodes[3];
    TTree() { memset(this, 0, sizeof(*this)); }
};
// write the map box {head@0, head@0x30} at pBox
static void BuildTreeIn(TTree* pT, void* pBox,
                        uint32_t aKey, void* aVal,
                        uint32_t bKey, void* bVal) {
    TNode* H = &pT->nodes[0];
    TNode* A = &pT->nodes[1];
    TNode* B = &pT->nodes[2];
    H->ab[1] = 1;
    H->pLeft = H; H->pRight = H; H->pParent = A;
    A->uKey = aKey; A->pValue = aVal;
    A->pParent = H; A->pLeft = H;
    A->pRight = B;      // b > a: B at A's right
    B->uKey = bKey; B->pValue = bVal;
    B->pParent = A; B->pLeft = H; B->pRight = H;
    void** pp = (void**)pBox;
    pp[0] = H; pp[6] = H;
}

// the fake vtable objects
static int s_nTickA, s_nTickB, s_nTickC;
static uint64_t s_uTickT;
static void* s_pInnerObj;   // the inner-object box

struct FakeObj {   // *(FakeObj*) = the vt
    void* apVt[64];
};
static FakeObj s_o1, s_o2, * s_pO1 = &s_o1,
    * s_pO2 = &s_o2;

static int s_nRankA;

// the tick mocks (the vt slots) — MockTickA is
// driven by BOTH the tick (arg 0x1a) and the
// rank get (arg 1): record the call sequence
static int64_t s_anTickArgs[8];
static int s_nTickCalls;
static void* MockTickA(void*, int64_t n) {
    if (s_nTickCalls < 8)
        s_anTickArgs[s_nTickCalls] = n;
    s_nTickCalls++;
    return s_pO2; }
static void MockTickB(void*, uint32_t t) {
    s_nTickB++; s_uTickT = t; }
static void MockTickC(void*, int64_t n) {
    s_nTickC = (int)n; }
// the getter mocks
static void* MockGetRankA(void*, int64_t n) {
    s_nRankA = (int)n; return s_pO2; }
static uint64_t MockVal77(void*) { return 0x77; }
static uint64_t MockVal33(void*) { return 0x33; }
static uint64_t MockVal0(void*)  { return 0; }
// the mgr vt mock
static uint64_t MockMgrSyn(void*, int64_t) {
    return 0; }

int main() {
    // ---- bind the seams ----
    g_fnLogRemoveInvalid = [] { s_nInvalid++; };
    g_fnLogRemoveLogError = [] { s_nLogErr++; };
    g_fnSendToSession = [](void* p, uint32_t u) {
        s_nSend++; s_pSendSess = p; s_uSendId = u; };
    g_fnTreeInsertF10 = [](void* pMap, void* pOut,
        uint32_t* pKey) -> void* {
        s_nInsertF10++; s_uInsertKey = *pKey;
        // the out-iter pair {node, next}: BOTH
        // dereferenceable (the unwrap reads
        // node->left then *(next+0x20))
        static TNode s_Node, s_Parent, s_Next;
        s_Node.pLeft = &s_Parent;   // the *iter
        s_Next.pValue = (void*)0xBEEF;
        void** pp = (void**)pOut;
        pp[0] = &s_Node; pp[1] = &s_Next;
        return pMap;
    };
    g_fnTreeFindAF0 = [](void* pMap, void* pOut,
        uint32_t*) -> void* {
        s_nFindAF0++;
        // the pair: {the head (=*pMap), a next}
        void** pp = (void**)pOut;
        pp[0] = *(void**)pMap; pp[1] = (void*)0x1;
        return pMap;
    };
    g_fnTreeErase = [](void* pMap, void* pOut,
        void* pIter) {
        s_nErase++; s_pEraseMap = pMap;
        s_pEraseOut = pOut; s_pEraseIter = pIter; };
    g_fnSortRange = [](void* pF, void* pL,
        int64_t n, void* pPred) {
        s_pSortFirst = pF; s_pSortLast = pL;
        s_nSortCount = n; s_pSortPred = pPred; };
    g_fnSessionKeyLookup = [](void*,
        uint32_t u) -> uint64_t {
        s_nKeyLookup++; s_uKeyLookup = u;
        return s_uKeyLookupRet; };

    // ---- D60-1: LogRecMapFind (14178c8e0) ----
    {
        static TTree t;
        static void* apBox[8];
        BuildTreeIn(&t, apBox, 5, (void*)0xAAA,
                    9, (void*)0xBBB);
        assert(LogRecMapFind(apBox, 5) ==
               (int64_t)0xAAA);
        assert(LogRecMapFind(apBox, 9) ==
               (int64_t)0xBBB);
        assert(LogRecMapFind(apBox, 7) == 0);
        assert(LogRecMapFind(apBox, 1) == 0);
        assert(s_nInvalid == 0);
        printf("D60-1 the log-rec map find ok\n");
    }
    // ---- D60-2: AcctTreeFind (1417631d0) ----
    {
        static uint8_t abMgr[0x70];
        static TTree t;
        static void* apBox[8];
        s_uKeyLookupRet = 0x1111;
        BuildTreeIn(&t, apBox, 0x1111,
                    (void*)0xACC1, 9, (void*)0);
        *(void**)(abMgr + 0x38) = apBox[0];
        *(void**)(abMgr + 0x68) = apBox[0];
        assert(AcctTreeFind(abMgr, 0x42) ==
               (int64_t)0xACC1);
        assert(s_nKeyLookup == 1);
        assert(s_uKeyLookup == 0x42);
        // the miss
        BuildTreeIn(&t, apBox, 0x1111, (void*)0,
                    9, (void*)0);
        *(void**)(abMgr + 0x68) = apBox[0];
        assert(AcctTreeFind(abMgr, 0x43) == 0);
        printf("D60-2 the acct tree find ok\n");
    }
    // ---- D60-3: AcctFieldSet (14174b360) ----
    {
        static uint8_t abMgr[0xd0];   // the
        // head @ +200 (decimal 0xc8) needs 0xd0
        static TTree t;
        static void* apAox[8];
        BuildTreeIn(&t, apAox, 9, (void*)0,
                    0x11, (void*)0);   // 9 < 0x11: BST
        *(void**)(abMgr + 0x98) = apAox[0];
        *(void**)(abMgr + 200) = apAox[0];
        // the nodes in THIS tree carry the 0x3d
        // isnil byte (the layout the walk uses)
        TNode* pH = &t.nodes[0];
        TNode* pA = &t.nodes[1];   // key 9 = the root
        ((uint8_t*)pH)[0x3d] = 1;
        ((uint8_t*)pA)[0x3d] = 0;
        AcctFieldSet(abMgr, 9, 4, 0x1234);
        assert(*(int*)((char*)pA + 0x1c) ==
               0x1234);
        AcctFieldSet(abMgr, 9, 5, -7);
        assert(*(int*)((char*)pA + 0x20) == -7);
        AcctFieldSet(abMgr, 9, 6, 0x1234);
        assert(*(short*)((char*)pA + 0x24) ==
               (short)0x1234);
        AcctFieldSet(abMgr, 9, 8, 1);
        assert(*(bool*)((char*)pA + 0x2a) == true);
        AcctFieldSet(abMgr, 9, 9, 0x555);
        assert(*(int*)((char*)pA + 0x26) == 0x555);
        // the miss → no write
        AcctFieldSet(abMgr, 1, 4, 0x999);
        assert(*(int*)((char*)pA + 0x1c) == 0x1234);
        assert(s_nInvalid == 0);
        printf("D60-3 the acct field set ok\n");
    }
    // ---- D60-4: RecFlagTick (141787310) ----
    {
        s_nTickA = s_nTickB = s_nTickC = 0;
        FakeObj& o1 = s_o1; FakeObj& o2 = s_o2;
        memset(o1.apVt, 0, sizeof(o1.apVt));
        memset(o2.apVt, 0, sizeof(o2.apVt));
        o1.apVt[0] = o1.apVt;   // *(obj) = the vt
        o2.apVt[0] = o2.apVt;
        o1.apVt[2] = (void*)MockTickA;
        o2.apVt[0xb0 / 8] = (void*)MockTickB;
        o1.apVt[0x38 / 8] = (void*)MockTickC;
        static void* apRec[8];
        apRec[0] = &o1;
        RecFlagTick(apRec, 1);
        assert(*(uint8_t*)((char*)apRec + 0x3c)
               == 1);
        assert(s_nTickCalls == 1);
        assert(s_anTickArgs[0] == 0x1a);
        assert(s_nTickB == 1);
        assert(s_nTickC == 0);
        // the null object → nothing
        apRec[0] = 0;
        RecFlagTick(apRec, 0);
        assert(s_nTickB == 1);
        assert(s_nTickCalls == 1);
        printf("D60-4 the flag tick ok\n");
    }
    // ---- D60-5: the getters + comparator ----
    {
        FakeObj& o1 = s_o1; FakeObj& o2 = s_o2;
        memset(o1.apVt, 0, sizeof(o1.apVt));
        memset(o2.apVt, 0, sizeof(o2.apVt));
        o1.apVt[0] = o1.apVt;
        o2.apVt[0] = o2.apVt;
        o1.apVt[2] = (void*)MockGetRankA;
        o2.apVt[8] = (void*)MockVal77;
        o2.apVt[9] = (void*)MockVal33;
        static void* apRec[8];
        apRec[0] = &o1;
        assert(RecRankGet(apRec) == 0x77);
        assert(RecCmpKey(apRec) == 0x33);
        assert(RecCmpSub(apRec) == 0x77);
        // the null → the log error + 0
        apRec[0] = 0;
        s_nLogErr = 0;
        assert(RecRankGet(apRec) == 0);
        assert(RecCmpKey(apRec) == 0);
        assert(RecCmpSub(apRec) == 0);
        assert(s_nLogErr == 3);
        // the online flag byte
        static uint8_t abRec[0x40];
        abRec[0x3c] = 1;
        assert(RecIsOnline(abRec) == true);
        abRec[0x3c] = 0;
        assert(RecIsOnline(abRec) == false);
        printf("D60-5 the getters ok\n");
    }
    // ---- D60-6: RecVecSort (14179e020) ----
    {
        static uint8_t abM[0x260];
        static void* apElems[8];
        *(void**)(abM + 0x230) = (void*)0xC000;
        *(void**)(abM + 0x248) = &apElems[0];
        *(void**)(abM + 0x250) = &apElems[4];
        RecVecSort(abM);
        assert(s_pSortFirst == &apElems[0]);
        assert(s_pSortLast == &apElems[4]);
        assert(s_nSortCount == 4);
        assert(s_pSortPred == (void*)RecComparator);
        // end < first → invalid
        *(void**)(abM + 0x250) = &apElems[0];
        *(void**)(abM + 0x248) = &apElems[4];
        s_nInvalid = 0;
        RecVecSort(abM);
        // the ORIGINAL runs the SAME end<first check
        // TWICE (the two checked-iterator derefs) →
        // invalid fires 2x
        assert(s_nInvalid == 2);
        printf("D60-6 the sort prep ok\n");
    }
    // ---- D60-7: SessionMapBranch (141767cd0) ----
    {
        static uint8_t abMgr[0x4f8];
        static uint8_t abSess[0x60];
        // the owner set: +0x4f0 → sess, +0x54 == syn
        *(uint32_t*)(abSess + 0x54) = 0x66;
        *(void**)(abMgr + 0x4f0) = abSess;
        s_nSend = 0;
        SessionMapBranch(abMgr, 0x11, 0x66);
        assert(s_nSend == 1);
        assert(s_pSendSess == abSess);
        assert(s_uSendId == 0x11);
        // the owner mismatch → the insert path:
        // the out-iter {node(0xBEEF value), next}
        s_nInsertF10 = 0; s_nSend = 0;
        SessionMapBranch(abMgr, 0x11, 0x77);
        assert(s_nInsertF10 == 1);
        assert(s_uInsertKey == 0x77);
        assert(s_nSend == 1);
        assert(s_uSendId == 0x11);
        // the anchor equality → the insert node's
        // value: the seam writes next=0xCAFE,
        // lVar2 = *(mgr+0x4e0) != next → send w/
        // *(next+0x20)... our fake: 0xBEEF
        // (checked above via the count only)
        // the id-0 gate → nothing
        s_nSend = 0;
        SessionMapBranch(abMgr, 0, 0x66);
        assert(s_nSend == 0);
        printf("D60-7 the session branch ok\n");
    }
    // ---- D60-8: ErasePrep (141774ba0) ----
    {
        static uint8_t abMgr[0x2f0];
        static void* apHead = (void*)0xEA0;
        *(void**)(abMgr + 0x2b0) = apHead;
        *(void**)(abMgr + 0x2e0) = (void*)0xE0;
        s_nFindAF0 = 0; s_nErase = 0;
        ErasePrep(abMgr, 0x11);
        assert(s_nFindAF0 == 1);
        // the pair {head, 0x1}: *map == head ok;
        // lVar2(0xE0) != pair[1](0x1) → erase
        assert(s_nErase == 1);
        assert(s_pEraseMap == (void*)(abMgr + 0x2b0));
        // the id-0 gate
        s_nFindAF0 = 0;
        ErasePrep(abMgr, 0);
        assert(s_nFindAF0 == 0);
        printf("D60-8 the erase prep ok\n");
    }
    // ---- D60-9: the flow (1417ac620) ----
    {
        // the logic: +0x08 the mgr (vt[149]→0),
        // +0x10 the member mgr, +0x18 the rec map,
        // +0x50 the acct mgr
        static uint8_t abLogic[0x58];
        static TTree tRec;
        static void* apRecBox[8];
        // the rec: a FakeObj driving the tick+rank
        FakeObj& o1 = s_o1; FakeObj& o2 = s_o2;
        memset(o1.apVt, 0, sizeof(o1.apVt));
        memset(o2.apVt, 0, sizeof(o2.apVt));
        o1.apVt[0] = o1.apVt;   // *(obj) = the vt
        o2.apVt[0] = o2.apVt;
        o1.apVt[2] = (void*)MockTickA;
        o2.apVt[0xb0 / 8] = (void*)MockTickB;
        o1.apVt[0x38 / 8] = (void*)MockTickC;
        o2.apVt[8] = (void*)MockVal0;
        static void* apRec[8];
        apRec[0] = &o1;
        BuildTreeIn(&tRec, apRecBox, 0x11, apRec,
                    9, (void*)0);
        *(void**)(abLogic + 0x18) = apRecBox;
        // the mgr: vt[0x4a8/8=149] → 0 (no syn)
        static void* apMgrVt[160];
        memset(apMgrVt, 0, sizeof(apMgrVt));
        apMgrVt[149] = (void*)MockMgrSyn;
        static void* apMgrBox[1] = { apMgrVt };
        *(void**)(abLogic + 8) = apMgrBox;
        // the member mgr: rank 0 → the 0-key
        // gate → no lookup work needed
        *(void**)(abLogic + 0x10) = (void*)0x1000;
        // the acct mgr for the erase prep
        static uint8_t abAcct[0x2f0];
        static void* apHead2 = (void*)0x2EA0;
        *(void**)(abAcct + 0x2b0) = apHead2;
        *(void**)(abAcct + 0x2e0) = (void*)0xE0;
        *(void**)(abLogic + 0x50) = abAcct;
        // flow A: the rec found → tick + rank +
        // member lookup (0) + erase
        s_nTickA = s_nTickB = s_nTickC = 0;
        s_nTickCalls = 0;
        s_nKeyLookup = 0; s_nErase = 0;
        LogRemoveFlow(abLogic, 0x11);
        // the tick (0x1a) then the rank get (1) —
        // BOTH drive o1's vt slot 2
        assert(s_nTickCalls == 2);
        assert(s_anTickArgs[0] == 0x1a);
        assert(s_anTickArgs[1] == 1);
        assert(s_nTickB == 1);
        assert(s_nTickC == 0);
        assert(s_nKeyLookup == 0);   // the rec path
        assert(s_nErase == 1);
        // flow B: the rec miss → the acct path:
        // the rec tree misses 0x11 (values 0)
        BuildTreeIn(&tRec, apRecBox, 5, (void*)0,
                    9, (void*)0);
        // the acct tree at +0x38/+0x68 keyed by the
        // session key 0x1111 → the ACCOUNT object
        static TTree tAcct;
        static void* apAcctBox[8];
        // the account: its OWN inner tree at
        // +0x98 (anchor) / +0xc8 (head), keyed by
        // the user id, isnil @ +0x3d
        static uint8_t abAcctObj[0xd0];
        static TTree tInner;
        TNode* pIHead = &tInner.nodes[0];
        TNode* pIRoot = &tInner.nodes[1];
        memset(&tInner, 0, sizeof(tInner));
        ((uint8_t*)pIHead)[0x3d] = 1;
        pIHead->pLeft = pIHead;
        pIHead->pRight = pIHead;
        pIHead->pParent = pIRoot;
        pIRoot->uKey = 0x11;   // the user id
        pIRoot->pParent = pIHead;
        pIRoot->pLeft = pIHead;
        pIRoot->pRight = pIHead;
        *(void**)(abAcctObj + 0x98) = pIHead;
        *(void**)(abAcctObj + 200) = pIHead;
        s_uKeyLookupRet = 0x1111;
        BuildTreeIn(&tAcct, apAcctBox, 0x1111,
                    abAcctObj, 9, (void*)0);
        // one buffer serving BOTH 1417631d0
        // (+0x38/+0x68) and 141774ba0 (+0x2b0)
        static uint8_t abAcctMgr[0x4f8];
        *(void**)(abAcctMgr + 0x38) = apAcctBox[0];
        *(void**)(abAcctMgr + 0x68) = apAcctBox[0];
        *(void**)(abAcctMgr + 0x2b0) = apHead2;
        *(void**)(abAcctMgr + 0x2e0) = (void*)0xE0;
        *(void**)(abLogic + 0x50) = abAcctMgr;
        s_nKeyLookup = 0; s_nTickB = 0;
        s_nInsertF10 = 0; s_nSend = 0;
        s_nErase = 0;
        LogRemoveFlow(abLogic, 0x11);
        // the acct path: the key lookup ran, no tick
        assert(s_nKeyLookup == 1);
        assert(s_nTickB == 0);
        // the field set 8 wrote bool 0 at the
        // inner root node +0x2a
        assert(*(bool*)((char*)pIRoot + 0x2a) ==
               false);
        assert(s_nErase == 1);   // this pass's erase
        printf("D60-9 the flow ok\n");
    }
    printf("SYNDICATE_D60_OK: the log remove\n");
    return 0;
}
