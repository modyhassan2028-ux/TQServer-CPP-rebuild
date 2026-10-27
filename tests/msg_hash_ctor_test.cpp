// M71b: the hash container ctor (FUN_1400103b0)
// and reset (FUN_140010310) VERBATIM
#include "../msgserver/MsgHashCtor.h"
#include "../msgserver/MsgHashEnd.h"
#include <cassert>
#include <cstdio>
#include <cstring>

static void CheckFresh(msg::SHashContainer& c) {
    // the 2-byte owner field
    assert(c.m_wOwner == 0x1234);
    // the list proxy: new(8) node, value = &the slot
    assert(c.m_pProxy != nullptr);
    assert(*(void**)c.m_pProxy == &c.m_pProxy);
    // the END sentinel: self-linked both ways
    assert(c.m_pEnd != nullptr);
    assert(*(void**)c.m_pEnd == c.m_pEnd);
    assert(*(void**)((char*)c.m_pEnd + 8) ==
           c.m_pEnd);
    // size 0; vector EMPTY then refilled 9 entries
    assert(c.m_qSize == 0);
    assert(c.m_vec.m_q0 != 0);
    assert(*(void**)c.m_vec.m_q0 == &c.m_vec);
    char* pF = (char*)c.m_vec.m_pFirst;
    assert(pF != nullptr);
    assert((char*)c.m_vec.m_pLast - pF == 9*0x10);
    assert((char*)c.m_vec.m_pCap - pF >= 9*0x10);
    // all 9 bucket entries = {proxy, END}
    for (int i = 0; i < 9; i++) {
        uint64_t* e = (uint64_t*)(pF + i*0x10);
        assert(e[0] == (uint64_t)c.m_pProxy);
        assert(e[1] == (uint64_t)c.m_pEnd);
    }
    // mask 7, count 8, max_load 4.0f
    assert(c.m_qMask == 7);
    assert(c.m_qBuckets == 8);
    assert(c.m_fMaxLoad == 4.0f);
}

int main() {
    using namespace msg;
    // 1) the ctor on a zeroed container
    SHashContainer c; std::memset(&c, 0, sizeof c);
    uint16_t wOwner = 0x1234;
    HashCtorInit(&c, &wOwner);
    CheckFresh(c);
    void* pEnd1 = c.m_pEnd;
    void* pProxy1 = c.m_pProxy;
    void* pBuf1 = c.m_vec.m_pFirst;
    void* pVP1 = (void*)c.m_vec.m_q0;

    // 2) the RESET on a POPULATED container: two
    //    heap nodes + a modified list + dirty buckets
    struct HN { void* pNext; void* pPrev;
                int32_t dwKey; int32_t dwVal; };
    HN* n1 = new HN(); std::memset(n1,0,sizeof *n1);
    HN* n2 = new HN(); std::memset(n2,0,sizeof *n2);
    n1->pNext = n2; n1->pPrev = c.m_pEnd;
    n2->pNext = c.m_pEnd; n2->pPrev = n1;
    *(void**)c.m_pEnd = n1;          // END->next
    *(void**)((char*)c.m_pEnd + 8) = n2;  // prev
    c.m_qSize = 2;
    // dirty bucket entries (garbage heads)
    uint64_t* b0 = (uint64_t*)c.m_vec.m_pFirst;
    b0[1] = (uint64_t)n2; b0[9] = 0xdeadbeef;
    HashReset(&c);
    // END self-linked again, size 0
    assert(*(void**)c.m_pEnd == c.m_pEnd);
    assert(*(void**)((char*)c.m_pEnd + 8) ==
           c.m_pEnd);
    assert(c.m_qSize == 0);
    // mask/count/max_load preserved by the reset
    assert(c.m_qMask == 7 && c.m_qBuckets == 8 &&
           c.m_fMaxLoad == 4.0f);
    // 9 clean entries = {proxy, END} in the OLD
    // buffer (the reset keeps capacity when >= 9)
    char* pF2 = (char*)c.m_vec.m_pFirst;
    assert((char*)c.m_vec.m_pLast - pF2 == 9*0x10);
    for (int i = 0; i < 9; i++) {
        uint64_t* e = (uint64_t*)(pF2 + i*0x10);
        assert(e[0] == (uint64_t)c.m_pProxy);
        assert(e[1] == (uint64_t)c.m_pEnd);
    }
    // same END/proxy (the reset does NOT recreate
    // them - VERBATIM: it only unlinks/deletes)
    assert(c.m_pEnd == pEnd1);
    assert(c.m_pProxy == pProxy1);

    // 3) re-ctor on the SAME container (the 103b0
    //    path again): fresh proxies + a NEW END and
    //    a NEW bucket buffer (the old one is
    //    deleted by VecClearRefill's clear)
    HashCtorInit(&c, &wOwner);
    CheckFresh(c);
    assert(c.m_pEnd != pEnd1 ||
           c.m_vec.m_pFirst != pBuf1 ||
           c.m_vec.m_q0 != (uint64_t)pVP1);

    // cleanup (the ports allocate: proxies, END,
    // bucket buffers)
    operator delete((void*)c.m_vec.m_q0);
    operator delete(c.m_vec.m_pFirst);
    operator delete(c.m_pEnd);
    operator delete(c.m_pProxy);
    operator delete(pVP1);
    operator delete(pEnd1);
    operator delete(pProxy1);
    // pBuf1 was freed by the 2nd ctor's clear
    std::puts("M71B-HASH-CTOR-OK");
    return 0;
}
