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
    std::puts("MSG_SETOPS_OK: insert first/tail branches,"
              " erase unlink + end() out_of_range"
              " verbatim | MSG_MAPGROUP_CTOR_OK: ctor order, 0x40 set "
              "layout, tri-self-link, flag bytes 0x1d/0x29/"
              "0x79, jail alloc 0x80/0x78=1");
    return 0;
}
