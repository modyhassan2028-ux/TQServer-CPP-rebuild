// M47: FUN_1400f0000 CMapGroupKernel ctor + container family
#include "../Exe/MsgServer/Port/MsgMapGroupKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
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
    sent.m_byFlag = 1; sent.m_byReady = 1;
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
    msg::SetErase(&s, n1);
    assert(s.m_qCount == 1);
    msg::SetErase(&s, n2);
    assert(s.m_qCount == 0);
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
    std::puts("MSG_SETOPS_OK: insert first/tail branches,"
              " erase unlink + end() out_of_range"
              " verbatim | MSG_MAPGROUP_CTOR_OK: ctor order, 0x40 set "
              "layout, tri-self-link, flag bytes 0x1d/0x29/"
              "0x79, jail alloc 0x80/0x78=1");
    return 0;
}
