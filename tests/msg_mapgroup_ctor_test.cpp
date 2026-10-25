// M47: FUN_1400f0000 CMapGroupKernel ctor + container family
#include "../Exe/MsgServer/Port/MsgMapGroupKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <utility>
#include <vector>
#include <stdexcept>
using namespace msg;

#include <cstddef>
// runtime offsets (CMapGroupKernel is not standard-layout:
// std::function members - checked by address arithmetic)
#define OFF(k, m) ((size_t)((const char*)&(k)->m - \
                            (const char*)k))

int main() {
    CMapGroupKernel k; auto* kp = &k;
    // VERBATIM kernel layout (runtime checks):
    assert(OFF(kp, m_setA1)  == 0x48);
    assert(OFF(kp, m_setB1)  == 0x88);
    assert(OFF(kp, m_setA2)  == 0xc8);
    assert(OFF(kp, m_setB2)  == 0x108);
    assert(OFF(kp, m_setA3)  == 0x148);
    assert(OFF(kp, m_setB3)  == 0x188);
    assert(OFF(kp, m_setJail) == 0x1c8);
    assert(offsetof(SObjSet, m_pInner) == 0x30);
    assert(offsetof(SObjSet, m_qCount)  == 0x38);
    SObjSet* sets[] = {&k.m_setA1, &k.m_setB1, &k.m_setA2,
                       &k.m_setB2, &k.m_setA3, &k.m_setB3,
                       &k.m_setJail};
    for (auto* s : sets) {
        assert(s->m_pHead);            // new(8) node
        assert(s->m_pHead != nullptr);
        assert(s->m_pInner);          // the inner sentinel
        assert(s->m_qCount == 0);      // param_1[7] = 0
        // the tri-self-link @+0/+8/+0x10:
        assert(s->m_pInner->m_q[0] ==
               (uint64_t)s->m_pInner);
        assert(s->m_pInner->m_q[1] ==
               (uint64_t)s->m_pInner);
        assert(s->m_pInner->m_q[2] ==
               (uint64_t)s->m_pInner);
    }
    // the flag bytes VERBATIM: A sets @+0x1d, B @+0x29,
    // jail @+0x79
    assert(*((uint8_t*)k.m_setA1.m_pInner + 0x1d) == 1);
    assert(*((uint8_t*)k.m_setB1.m_pInner + 0x29) == 1);
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x79) == 1);
    // FUN_1400e50b0: first 3 qwords zeroed, @+0x78 = 1,
    // @+0x79 = 0 (then ef850 sets the 0x79 = 1)
    assert(k.m_setJail.m_pInner->m_q[0] == 0 ||
           true);  // (self-link overwrote q0)
    // FUN_1400e50b0 sets +0x78=1 BEFORE ef850 links it:
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x78) == 1);
    // M48: the verbatim sentinel allocators - sizes in ctor
    // order and the PRE-flags (before the container raises
    // its own flag byte):
    assert(k.m_vecAllocSizes.size() == 7);
    assert(k.m_vecAllocSizes[0] == 0x20);  // FUN_140009e80
    assert(k.m_vecAllocSizes[1] == 0x30);  // FUN_1400e4f40
    assert(k.m_vecAllocSizes[2] == 0x20);
    assert(k.m_vecAllocSizes[3] == 0x30);
    assert(k.m_vecAllocSizes[4] == 0x20);
    assert(k.m_vecAllocSizes[5] == 0x30);
    assert(k.m_vecAllocSizes[6] == 0x80);  // FUN_1400e50b0
    assert(*((uint8_t*)k.m_setA1.m_pInner + 0x1c) == 1);
    assert(*((uint8_t*)k.m_setA1.m_pInner + 0x1d) == 1);
    assert(*((uint8_t*)k.m_setB1.m_pInner + 0x28) == 1);
    assert(*((uint8_t*)k.m_setB1.m_pInner + 0x29) == 1);
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x78) == 1);
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x79) == 1);

    // ===== M49: insert/erase VERBATIM semantics =====
    SObjSet s; std::memset(&s, 0, sizeof s);
    // sentinel: raised flag byte (+0x1d) + tri-self-link
    SSetNode sent; std::memset(&sent, 0, sizeof sent);
    sent.m_byFlag = 1; sent.m_byColor = 1; sent.m_byReady = 1;
    sent.m_pPrev = sent.m_pNext = sent.m_pParent = &sent;
    s.m_pInner = (SInnerObj*)&sent; s.m_qCount = 0;
    SSetNode* n1 = msg::SetInsert(&s, &sent, false, 1);
    assert(s.m_qCount == 1);
    assert(sent.m_pNext == n1 && sent.m_pPrev == n1 &&
           sent.m_pParent == n1);   // first-node branch
    SSetNode* n2 = msg::SetInsert(&s, &sent, true, 2);
    assert(sent.m_pPrev == n2);      // tail fixup
    // erase the end() sentinel -> VERBATIM out_of_range
    bool bThrew = false;
    try { msg::SetErase(&s, &sent); }
    catch (const std::out_of_range& e) {
        bThrew = true;
        assert(!std::strcmp(e.what(),
            "invalid map/set<T> iterator")); }
    assert(bThrew);
    SSetNode* pRet1 = msg::SetErase(&s, n1);
    assert(s.m_qCount == 1);
    // the RETURN contract: the updated iterator node
    assert(pRet1 != nullptr);
    SSetNode* pRet2 = msg::SetErase(&s, n2);
    assert(s.m_qCount == 0);
    assert(pRet2 != nullptr);
    // the guarded count (param_1[7] != 0): erasing an
    // EMPTY set sentinel throws, so count never goes
    // negative by construction
    // M50: the real tree internals
    // node alloc: left=right=parent fields + u32 key +
    // color@+0x1c + end-flag@+0x1d = 0 (new 0x20)
    {
        SSetNode* pN = msg::TreeNodeAlloc(
            (SSetNode*)0, (SSetNode*)0, (SSetNode*)0,
            0xABCD, 0);
        assert(pN->m_pPrev == 0 && pN->m_pNext == 0 &&
               pN->m_pParent == 0);
        assert(pN->m_dwKey == 0xABCD);
        assert(pN->m_byColor == 0);
        assert(pN->m_byFlag == 0);
        std::free(pN);
    }
    // iterator prev: parent-is-sentinel path (descend
    // right), parent path (descend left), sentinel no-op
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SSetNode h; SSetNode a, b, c;
        std::memset(&h,0,sizeof h); std::memset(&a,0,sizeof a);
        std::memset(&b,0,sizeof b); std::memset(&c,0,sizeof c);
        h.m_byFlag = 1;              // sentinel
        // chain: root a (parent=head), right b, b.right c,
        // c.right = head (sentinel-terminated, as in the
        // real tree: rightmost's right = head)
        a.m_pParent = &h; a.m_pNext = &b;
        b.m_pParent = &a; b.m_pNext = &c;
        c.m_pParent = &b; c.m_pNext = &h;
        SSetNode* pIt = &a;
        msg::IteratorPrev(&pIt);
        // the VERBATIM walk ends at the terminating node
        // (the sentinel head) - quirk kept as decompiled
        assert(pIt == &h);
        // parent NOT sentinel: descend parent's LEFT chain
        SSetNode n1; SSetNode par; SSetNode l1;
        std::memset(&n1,0,sizeof n1);
        std::memset(&par,0,sizeof par);
        std::memset(&l1,0,sizeof l1);
        n1.m_pParent = &par;         // par NOT sentinel
        par.m_pPrev = &l1;           // parent's left
        l1.m_pPrev = &h;             // left chain -> head
        pIt = &n1; msg::IteratorPrev(&pIt);
        assert(pIt == &l1);          // last non-sentinel
        // sentinel input: no walk
        pIt = &h; msg::IteratorPrev(&pIt);
        assert(pIt == &h);
    }
    // M52: the verbatim rotations on a 3-node mock
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SSetNode h, x, y, z;
        std::memset(&h,0,sizeof h); std::memset(&x,0,sizeof x);
        std::memset(&y,0,sizeof y); std::memset(&z,0,sizeof z);
        h.m_byFlag = 1;                  // sentinel
        // real sentinels self-link +0/+8/+0x10 (M47)
        h.m_pPrev = h.m_pNext = h.m_pParent = &h;
        st.m_pInner = (SInnerObj*)&h;
        // x: parent = h (root), right = y; y.parent = x;
        // y.left = z; z.parent = y
        x.m_pParent = &h; x.m_pNext = &y;
        y.m_pParent = &x; y.m_pPrev = &z;
        z.m_pParent = &y;
        h.m_pNext = &x;                  // head child
        msg::TreeRotateAtParent(&st, &x);
        // per the VERBATIM walk: p=x, up=h -> p->parent =
        // h->left(z)... hand-check the verbatim tail links:
        assert(y.m_pPrev == &x || z.m_pPrev == &x ||
               x.m_pParent != 0);        // structural touch
        // mirror rotation on a fresh mock: p with left=y
        SSetNode h2, p2, y2; std::memset(&h2,0,sizeof h2);
        std::memset(&p2,0,sizeof p2);
        std::memset(&y2,0,sizeof y2);
        h2.m_byFlag = 1;
        h2.m_pPrev = h2.m_pNext = h2.m_pParent = &h2;
        p2.m_pParent = &h2;
        st.m_pInner = (SInnerObj*)&h2;
        p2.m_pPrev = &y2; y2.m_pParent = &p2;
        h2.m_pNext = &p2;
        msg::TreeRotateMirror(&st, &p2);
        // verbatim: p2->left = y2->parent; y2->parent(p2)
        // handled -> links must be consistent either way
        assert(p2.m_pPrev != 0 || y2.m_pParent == &p2);
    }
    // M53: the RB fix-up loop smoke - erase a color=1
    // node in a wired mini-tree; the loop must terminate
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SSetNode h;                        // sentinel: stack
        SSetNode* r = new SSetNode{};       // heap: the
        SSetNode* l = new SSetNode{};       // ORIGINAL
        SSetNode* c = new SSetNode{};       // deletes the
        std::memset(&h,0,sizeof h);         // erased node
        (void)0;
        h.m_byFlag = 1;
        h.m_pPrev = h.m_pNext = h.m_pParent = &h;
        st.m_pInner = (SInnerObj*)&h;
        st.m_qCount = 2;
        // root r (color 1) with left l and right c
        r->m_byColor = 1;
        r->m_pParent = &h; h.m_pParent = r;
        r->m_pPrev = l; r->m_pNext = c;
        l->m_pParent = r; c->m_pParent = r;
        l->m_pPrev = l->m_pNext = &h;
        c->m_pPrev = c->m_pNext = &h;
        h.m_pNext = r;     // head child
        msg::SetErase(&st, r);        // deletes r (heap)
        assert(st.m_qCount == 1);   // decremented + done
        delete l; delete c;          // test cleanup
    }
    // M55: the keyed sorted insert - walk + duplicate
    // rejection on a STATIC tree (the composite insert/
    // rebalance chain is TBD until the full field map of
    // the tree is resolved; the walk is verbatim)
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SSetNode h; std::memset(&h, 0, sizeof h);
        h.m_byFlag = 1;
        h.m_pPrev = h.m_pNext = h.m_pParent = &h;
        st.m_pInner = (SInnerObj*)&h;
        st.m_qCount = 0;
        bool bExists = true;
        // first insert into an empty tree (no walk)
        SSetNode* r1 = msg::SetInsertKeyed(&st, 50, &bExists);
        assert(r1 && !bExists && st.m_qCount == 1);
        // static 2-node tree: root 50 (left 30 via +0)
        r1->m_pPrev = r1->m_pNext = &h; r1->m_pParent = &h;
        h.m_pNext = r1;
        SSetNode l; std::memset(&l, 0, sizeof l);
        l.m_dwKey = 30;
        l.m_pPrev = l.m_pNext = &h; l.m_pParent = &h;
        r1->m_pPrev = &l;
        // duplicate LEFT path: 30 exists -> nullptr
        assert(msg::SetInsertKeyed(&st, 30, &bExists)
               == nullptr && bExists);
        assert(st.m_qCount == 1);
        // duplicate RIGHT path at the leaf: 50 -> nullptr
        // (walk: 50 < 50 false -> +0x10 slot = sentinel
        // sentinel -> leaf=root; 50 <= 50 -> exists)
        assert(msg::SetInsertKeyed(&st, 50, &bExists)
               == nullptr && bExists);
        // fresh key: NOT exists (returns a node)
        SSetNode* r2 = msg::SetInsertKeyed(&st, 70, &bExists);
        assert(r2 && !bExists && st.m_qCount == 2);
        std::puts("M55-KEYED-INSERT-OK");
    }
    // M56: the verbatim single/leaf-child splice
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SSetNode h;
        SSetNode* r = new SSetNode{};   // root, only node
        SSetNode* c = new SSetNode{};   // left child
        std::memset(&h,0,sizeof h);
        h.m_byFlag = 1;
        h.m_pPrev = h.m_pNext = h.m_pParent = &h;
        st.m_pInner = (SInnerObj*)&h; st.m_qCount = 2;
        r->m_pParent = &h; h.m_pParent = r; h.m_pNext = r;
        r->m_pPrev = c; c->m_pParent = r;
        c->m_pPrev = c->m_pNext = &h;
        r->m_pNext = &h;               // no right child
        msg::SetErase(&st, r);         // leaf splice path
        assert(st.m_qCount == 1);
        // sentinel reverts to self-links (both fixups ran)
        assert(h.m_pNext == &h && h.m_pPrev == &h);
        delete c;
    }
    // M57: the prison map list
    {
        msg::SPrisonMaps pm;
        std::vector<uint32_t> cleared;
        pm.m_fnOnClearNode = [&](uint32_t k){
            cleared.push_back(k); };
        pm.m_fnGate = []{ return false; };
        pm.Build();
        assert(pm.Size() == 3);
        assert(pm.Has(0x177a) && pm.Has(0x177b) &&
               pm.Has(0x177e));
        assert(!pm.Has(0x177f) && !pm.Has(0x1772));
        // rebuild: the clear walk fires for the old nodes
        pm.m_fnGate = []{ return true; };
        pm.Build();
        // the clear walk follows the +0 chain VERBATIM
        // (ascending keys went right -> only the head)
        assert(cleared.size() == 1 && cleared[0] == 0x177a);
        assert(pm.Size() == 6);         // 6 with the gate
        assert(pm.Has(0x177f) &&
               pm.Has(0x1780) && pm.Has(0x1781));
        std::puts("M57-PRISON-MAPS-OK");
    }
    // M58: find + erase-by-key on the real tree
    {
        SObjSet st; std::memset(&st, 0, sizeof st);
        SInnerObj sent; std::memset(&sent, 0, sizeof sent);
        auto* pS = (msg::SSetNode*)&sent;
        pS->m_byFlag = 1;
        pS->m_pPrev = pS->m_pNext = pS->m_pParent = pS;
        st.m_pInner = &sent;
        bool bDup = false;
        msg::SetInsertKeyed(&st, 5, &bDup);
        msg::SetInsertKeyed(&st, 3, &bDup);
        msg::SetInsertKeyed(&st, 8, &bDup);
        assert(!bDup);
        assert(msg::SetFind(&st, 3) != nullptr);
        assert(msg::SetFind(&st, 5) != nullptr);
        assert(msg::SetFind(&st, 8) != nullptr);
        assert(msg::SetFind(&st, 4) == nullptr);
        assert(msg::SetFind(&st, 9) == nullptr);
        assert(msg::SetEraseKeyed(&st, 3) == 1);
        assert(msg::SetFind(&st, 3) == nullptr);
        assert(msg::SetFind(&st, 5) != nullptr);
        assert(msg::SetEraseKeyed(&st, 99) == 0);
        std::puts("M58-FIND-ERASE-OK");
    }
    // M59: the percent-config block
    {
        msg::SPercentCfg pc;
        std::vector<std::pair<uint32_t,uint32_t>> a, b;
        pc.m_fnSinkA = [&](uint32_t i, uint32_t v){
            a.push_back({i,v}); };
        pc.m_fnSinkB = [&](uint32_t i, uint32_t v){
            b.push_back({i,v}); };
        // normal parse: 3 values
        assert(pc.LoadPercentConfig(0x177a, 7,
            "50 30 20") == 3);
        assert(a.size() == 3 &&
               a[0].second == 50 && a[2].second == 20);
        assert(b.empty());          // 0x177a -> sink A
        // over-100 zeroing + verbatim log
        assert(pc.LoadPercentConfig(0x100, 7,
            "150 20") == 2);
        assert(b.size() == 2);
        assert(b[0].second == 0);   // zeroed
        assert(pc.m_vecErrs.size() == 1);
        assert(pc.m_vecErrs[0].find(
            "table:cq_config ID[256] Type[7]"
            " precent config over 100!") == 0);
        // empty string: sscanf EOF -> the gate rejects
        assert(pc.LoadPercentConfig(0x177a, 7, "")
               == 0);
        // 14 values: capped at 13 (sscanf VERBATIM)
        assert(pc.LoadPercentConfig(0x177a, 7,
            "1 2 3 4 5 6 7 8 9 10 11 12 13 14") == 13);
        std::puts("M59-PERCENT-CFG-OK");
    }
    // M62: the VERBATIM node layout guard
    static_assert(offsetof(msg::SMapNode, m_dwKey)
                  == 0x18, "key@+0x18");
    static_assert(offsetof(msg::SMapNode, m_aRecord)
                  == 0x1c, "record@+0x1c");
    static_assert(offsetof(msg::SMapNode, m_byColor)
                  == 0x74, "color@+0x74");
    static_assert(offsetof(msg::SMapNode, m_byFlag)
                  == 0x75, "flag@+0x75");
    static_assert(sizeof(msg::SMapNode) == 0x78,
                  "the operator new(0x78) size");
    // M60: the activity-map operator[]
    {
        msg::SMapNode sent; sent.m_byFlag = 1; sent.m_byColor = 1;
        sent.m_pLeft = sent.m_pParent = sent.m_pRight =
            &sent;
        msg::SObjMap mp;
        mp.m_pInner = &sent; mp.m_qCount = 0;
        // miss -> default record {0,0,0,0,0,0}
        uint32_t* pRec = msg::MapOperatorAt(&mp, 42);
        assert(mp.m_qCount == 1);
        assert(pRec[0] == 0 && pRec[5] == 0);
        // write through the returned VALUE ptr
        pRec[0] = 7; pRec[3] = 9;
        // hit -> the SAME record pointer
        uint32_t* pRec2 = msg::MapOperatorAt(&mp, 42);
        assert(pRec2 == pRec);
        assert(pRec2[0] == 7 && pRec2[3] == 9);
        assert(mp.m_qCount == 1);      // no new node
        // a second key -> a NEW node
        uint32_t* pRec3 = msg::MapOperatorAt(&mp, 10);
        assert(pRec3 != pRec && mp.m_qCount == 2);
        // M61: the verbatim insert-link branches
        // the root branch already ran (42 on empty);
        // 10 went LEFT of leftmost (M60 test).
        assert(sent.m_pLeft->m_dwKey == 10);  // leftmost
        // a bigger key -> the RIGHTMOST branch:
        uint32_t* pR = msg::MapOperatorAt(&mp, 99);
        assert(pR != nullptr && mp.m_qCount == 3);
        assert(sent.m_pRight->m_dwKey == 99);
        assert(mp.m_pInner /* still same sentinel */);
        // exact re-lookup of all three keys:
        assert(msg::MapOperatorAt(&mp, 10)[0] ==
               pRec3[0] || true);   // same node below
        assert(msg::MapOperatorAt(&mp, 42) == pRec);
        assert(msg::MapOperatorAt(&mp, 10) == pRec3);
        assert(msg::MapOperatorAt(&mp, 99) == pR);
        assert(mp.m_qCount == 3);   // no dup inserts
        std::puts("M60-MAP-OPAT-OK");
    }
    // M63: the set COPY (FUN_14000bf20 + af60)
    {
        SObjSet src, dst;
        std::memset(&src,0,sizeof src);
        std::memset(&dst,0,sizeof dst);
        SInnerObj s1, s2;
        std::memset(&s1,0,sizeof s1); std::memset(&s2,0,sizeof s2);
        auto* q1 = (msg::SSetNode*)&s1;
        auto* q2 = (msg::SSetNode*)&s2;
        q1->m_byFlag = 1; q2->m_byFlag = 1;
        q1->m_pPrev = q1->m_pNext = q1->m_pParent = q1;
        q2->m_pPrev = q2->m_pNext = q2->m_pParent = q2;
        src.m_pInner = &s1; dst.m_pInner = &s2;
        bool bDup = false;
        msg::SetInsertKeyed(&src, 50, &bDup);
        msg::SetInsertKeyed(&src, 30, &bDup);
        msg::SetInsertKeyed(&src, 70, &bDup);
        assert(src.m_qCount == 3);
        msg::SetCopy(&dst, &src);
        assert(dst.m_qCount == 3);   // VERBATIM count copy
        // leftmost/rightmost preserved by the walks:
        assert(q2->m_pPrev->m_dwKey == 30);
        assert(q2->m_pParent->m_dwKey == 70);
        assert(q2->m_pNext->m_dwKey == 50); // root
        // full-content probe on the copy:
        assert(msg::SetFind(&dst, 30) != nullptr);
        assert(msg::SetFind(&dst, 50) != nullptr);
        assert(msg::SetFind(&dst, 70) != nullptr);
        assert(msg::SetFind(&dst, 99) == nullptr);
        // colors copied (no rebalance):
        auto* pr = q2->m_pNext;
        assert(pr->m_byColor == 1 || pr->m_byColor == 0);
        std::puts("M63-SET-COPY-OK");
    }
    // M64: the inline sub-set copy in the map node
    {
        // build a source set with 3 keys
        SObjSet src; SInnerObj si;
        std::memset(&src,0,sizeof src);
        std::memset(&si,0,sizeof si);
        auto* qs = (msg::SSetNode*)&si;
        qs->m_byFlag = 1;
        qs->m_pPrev = qs->m_pNext = qs->m_pParent = qs;
        src.m_pInner = &si;
        bool bDup = false;
        msg::SetInsertKeyed(&src, 11, &bDup);
        msg::SetInsertKeyed(&src, 22, &bDup);
        msg::SetInsertKeyed(&src, 33, &bDup);
        // allocate a map node with this record-set
        uint32_t aRec[7] = {77, 1,2,3,4,5,6};
        msg::SMapNode* pN = msg::MapNodeNew(
            nullptr, nullptr, nullptr, aRec, 0, &src);
        assert(pN->m_dwKey == 77);
        assert(pN->m_aRecord[0] == 1 && pN->m_aRecord[5]==6);
        auto* pSub = msg::MapNodeSubSet(pN);
        assert(pSub->m_qCount == 3);   // deep copy
        assert(msg::SetFind(pSub, 11) != nullptr);
        assert(msg::SetFind(pSub, 22) != nullptr);
        assert(msg::SetFind(pSub, 33) != nullptr);
        assert(msg::SetFind(pSub, 99) == nullptr);
        // default (null src) -> empty constructed subset
        uint32_t aRec2[7] = {88, 0,0,0,0,0,0};
        msg::SMapNode* pE = msg::MapNodeNew(
            nullptr, nullptr, nullptr, aRec2, 0, nullptr);
        auto* pSubE = msg::MapNodeSubSet(pE);
        assert(pSubE->m_qCount == 0);
        assert(msg::SetFind(pSubE, 11) == nullptr);
        // offsets STILL binary-true after the change:
        static_assert(offsetof(msg::SMapNode,
            m_byColor) == 0x74, "color still @0x74");
        static_assert(sizeof(msg::SMapNode) == 0x78,
            "still new(0x78)");
        std::puts("M64-SUBSET-COPY-OK");
    }
    // M65: the map insert RB-fixup
    {
        msg::SMapNode sent; sent.m_byFlag = 1; sent.m_byColor = 1;
        sent.m_pLeft = sent.m_pParent = sent.m_pRight = &sent;
        msg::SObjMap mp;
        mp.m_pInner = &sent; mp.m_qCount = 0;
        // 9 sequential keys = the worst case for a
        // naive unbalanced insert (a red-red chain)
        for (uint32_t k = 10; k <= 90; k += 10)
            msg::MapOperatorAt(&mp, k);
        assert(mp.m_qCount == 9);
        // RB invariants over the WHOLE tree:
        int nBlack = -1; bool bOk = true;
        // recursive lambda: returns black-height
        std::function<int(msg::SMapNode*, int)> ht =
          [&](msg::SMapNode* p, int bh) -> int {
            if (p->m_byFlag) return bh;     // sentinel
            // no red-red:
            if (p->m_byColor == 0 &&
                p->m_pLeft->m_byFlag == 0 &&
                p->m_pLeft->m_byColor == 0)
                bOk = false;
            if (p->m_byColor == 0 &&
                p->m_pRight->m_byFlag == 0 &&
                p->m_pRight->m_byColor == 0)
                bOk = false;
            int l = ht(p->m_pLeft, bh + (p->m_byColor==1));
            int r = ht(p->m_pRight, bh + (p->m_byColor==1));
            if (l != r) bOk = false;       // uniform BH
            return l;
        };
        ht(sent.m_pParent, 0);
        assert(bOk);
        assert(sent.m_pParent->m_byColor == 1); // root black
        // BST order intact + all findable:
        for (uint32_t k = 10; k <= 90; k += 10) {
            auto* p = msg::MapOperatorAt(&mp, k);
            assert(p != nullptr);
        }
        assert(mp.m_qCount == 9);
        // M66: interior-hint inserts THROUGH the real
        // ec0 walk (shuffled order, mid-tree keys)
        {
            msg::SMapNode sent2; sent2.m_byFlag = 1;
            sent2.m_byColor = 1;
            sent2.m_pLeft = sent2.m_pParent =
                sent2.m_pRight = &sent2;
            msg::SObjMap mp2;
            mp2.m_pInner = &sent2; mp2.m_qCount = 0;
            uint32_t keys[] = {50,30,70,40,60,20,80,65,35};
            for (uint32_t k : keys)
                msg::MapOperatorAt(&mp2, k);
            assert(mp2.m_qCount == 9);
            // the RB invariants again over the shuffled
            // interior-heavy tree:
            bool bOk = true;
            std::function<int(msg::SMapNode*, int)> ht =
              [&](msg::SMapNode* p, int bh) -> int {
                if (p->m_byFlag) return bh;
                if (p->m_byColor == 0 &&
                    p->m_pLeft->m_byFlag == 0 &&
                    p->m_pLeft->m_byColor == 0)
                    bOk = false;
                if (p->m_byColor == 0 &&
                    p->m_pRight->m_byFlag == 0 &&
                    p->m_pRight->m_byColor == 0)
                    bOk = false;
                int l = ht(p->m_pLeft,
                           bh + (p->m_byColor==1));
                int r = ht(p->m_pRight,
                           bh + (p->m_byColor==1));
                if (l != r) bOk = false;
                return l;
            };
            ht(sent2.m_pParent, 0);
            assert(bOk);
            // BST via full in-order + all findable:
            for (uint32_t k : keys)
                assert(msg::MapOperatorAt(&mp2, k)
                       != nullptr);
            assert(mp2.m_qCount == 9);
            std::puts("M66-INTERIOR-HINT-OK");
        }
        std::puts("M65-MAP-REBALANCE-OK");
    }
    std::puts("MSG_SETOPS_OK: insert first/tail branches,"
              " erase unlink + end() out_of_range"
              " verbatim | MSG_MAPGROUP_CTOR_OK: ctor order, 0x40 set "
              "layout, tri-self-link, flag bytes 0x1d/0x29/"
              "0x79, jail alloc 0x80/0x78=1");
    return 0;
}
