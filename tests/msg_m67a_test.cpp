// M67a unit test — the broadcast-queue vector family:
//   FUN_140096be0 alloc / FUN_140098660 copy /
//   FUN_14009cc60 fill / FUN_1400a17a0 move-back /
//   FUN_14008e820 length_error / FUN_1400b6290 the
//   generic insert engine / FUN_1400ec4f0 resize
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include "MsgBcastVector.h"
using namespace msg;

static int s_nInvalid = 0;
static void TInvalid() { ++s_nInvalid; }

// a plain heap-vector fixture (buffers owned by test)
struct Fixture {
    SBVec v;
    uint8_t* buf;
    void Init(size_t capElems, size_t nElems,
              const uint64_t* pairs) {
        buf = (uint8_t*)operator new(
            capElems * 0x10 + 0x20);
        std::memset(buf, 0, capElems * 0x10 + 0x20);
        std::memset(&v, 0, sizeof v);
        v.m_pFirst = buf;
        v.m_pLast = buf + nElems * 0x10;
        v.m_pCap = buf + capElems * 0x10;
        for (size_t i = 0; i < nElems; i++) {
            ((uint64_t*)buf)[i*2] = pairs[i*2];
            ((uint64_t*)buf)[i*2+1] = pairs[i*2+1];
        }
        // the raw debug-proxy chain: *head = container
        pCont = &v;
        v.m_q0 = (uint64_t)&pCont;
    }
    void* pCont;
    size_t Size() const {
        return ((char*)v.m_pLast -
                (char*)v.m_pFirst) >> 4;
    }
    uint64_t A(size_t i) const {
        return ((uint64_t*)v.m_pFirst)[i*2];
    }
    uint64_t B(size_t i) const {
        return ((uint64_t*)v.m_pFirst)[i*2+1];
    }
    ~Fixture() { operator delete(v.m_pFirst); }
};

int main() {
    g_fnBcastInvalidParam = TInvalid;
    printf("M67a start\n"); fflush(stdout);

    // ==== S1: BcastVecAlloc (FUN_140096be0) ====
    {
        bool threw = false;
        try { BcastVecAlloc(nullptr, 0x1000000000000000ULL); }
        catch (const std::bad_alloc&) { threw = true; }
        assert(threw);   // max/n < 0x10
        void* p = BcastVecAlloc(nullptr, 4);
        assert(p != nullptr);
        operator delete(p);
        // n = 0: NO throw, new(0)
        p = BcastVecAlloc(nullptr, 0);
        assert(p != nullptr);
        operator delete(p);
        printf("S1 ok (alloc)\n"); fflush(stdout);
    }

    // ==== S2: copy + fill (98660 / 9cc60) ====
    {
        uint64_t src[4] = { 11, 12, 13, 14 };
        uint64_t dst[4] = { 0 };
        uint64_t* pRet = BcastVecCopy(src, src + 2, dst);
        assert(pRet == dst + 2);
        assert(dst[0] == 11 && dst[1] == 12 &&
               dst[2] == 0 && dst[3] == 0);
        // the literal null-dst guard: ONE pair ->
        // advances to 0x10 without copying (further
        // iterations would deref 0x10 in the ORIGINAL
        // raw too)
        pRet = BcastVecCopy(src, src + 2, nullptr);
        assert((uint64_t*)pRet == (uint64_t*)nullptr + 2);
        uint64_t val[2] = { 0xAA, 0xBB };
        BcastVecFill(dst, 2, val);
        assert(dst[0] == 0xAA && dst[1] == 0xBB &&
               dst[2] == 0xAA && dst[3] == 0xBB);
        BcastVecFill(nullptr, 1, val);
        // (n>1 with a null dst walks to 0x10 and
        // faults in the ORIGINAL raw as well)
        printf("S2 ok (copy/fill)\n"); fflush(stdout);
    }

    // ==== S3: MoveBack (a17a0) ====
    {
        uint64_t d[8] = { 0,1,2,3,4,5,6,7 };
        // move the PAIR [0,0x10) to end at 0x20:
        // (pEnd - pTo) = 0x10 offset
        void* r = BcastVecMoveBack(d, (char*)d + 0x10,
                                        (char*)d + 0x20);
        assert((uint64_t*)r == d + 2);
        assert(d[2] == 0 && d[3] == 1);   // moved copy
        assert(d[0] == 0 && d[1] == 1);   // src intact
        assert(d[4] == 4 && d[5] == 5);   // untouched
        printf("S3 ok (moveback)\n"); fflush(stdout);
    }

    // ==== S4: Insert GROW at FRONT, empty ====
    {
        Fixture f;
        uint64_t pairs[1] = { 0 };
        f.Init(0, 0, pairs);
        // capture old first (null)
        uint64_t pair[2] = { 0x1111, 0x2222 };
        uint64_t stackPair[2];
        stackPair[0] = 0;
        stackPair[1] = (uint64_t)f.v.m_pFirst;
        BcastVecInsert(&f.v, stackPair, 2, pair);
        assert(f.Size() == 2);
        assert(f.A(0) == 0x1111 && f.B(0) == 0x2222);
        assert(f.A(1) == 0x1111 && f.B(1) == 0x2222);
        // new cap = max(need, 0 + 0>>1) = 2
        assert(f.v.m_pCap == (char*)f.v.m_pFirst
                                 + 2 * 0x10);
        printf("S4 ok (insert grow front empty)\n"); fflush(stdout);
    }

    // ==== S5: Insert GROW at FRONT with 2 existing ====
    {
        uint64_t pairs[4] = { 1, 100, 2, 200 };
        Fixture f; f.Init(2, 2, pairs);
        uint64_t pair[2] = { 9, 99 };
        uint64_t stackPair[2];
        stackPair[0] = 0;
        stackPair[1] = (uint64_t)f.v.m_pFirst;
        BcastVecInsert(&f.v, stackPair, 3, pair);
        // cap 2 -> 2+1=3 < need 5 -> 5
        assert(f.Size() == 5);
        assert(f.v.m_pCap == (char*)f.v.m_pFirst
                                 + 5 * 0x10);
        assert(f.A(0) == 9 && f.B(0) == 99);
        assert(f.A(1) == 9 && f.B(1) == 99);
        assert(f.A(2) == 9 && f.B(2) == 99);
        assert(f.A(3) == 1 && f.B(3) == 100);
        assert(f.A(4) == 2 && f.B(4) == 200);
        printf("S5 ok (insert grow front)\n"); fflush(stdout);
    }

    // ==== S6: Insert MIDDLE (move-back branch) ====
    {
        uint64_t pairs[8] = { 10,1, 20,2, 30,3, 40,4 };
        Fixture f; f.Init(8, 4, pairs);
        uint64_t pair[2] = { 77, 7 };
        uint64_t stackPair[2];
        stackPair[0] = 0;
        stackPair[1] = (uint64_t)((char*)f.v.m_pFirst
                                   + 2 * 0x10);
        BcastVecInsert(&f.v, stackPair, 2, pair);
        assert(f.Size() == 6);
        assert(f.A(0) == 10 && f.A(1) == 20);
        assert(f.A(2) == 77 && f.B(2) == 7);
        assert(f.A(3) == 77 && f.B(3) == 7);
        assert(f.A(4) == 30 && f.A(5) == 40);
        assert(f.v.m_pFirst == f.buf); // no realloc
        printf("S6 ok (insert middle moveback)\n"); fflush(stdout);
    }

    // ==== S7: Insert SHIFT branch (tail < qN) ====
    {
        // 4 elems, insert 3 at pos=elem3 (tail=1 < 3)
        uint64_t pairs[8] = { 10,1, 20,2, 30,3, 40,4 };
        Fixture f; f.Init(8, 4, pairs);
        uint64_t pair[2] = { 55, 5 };
        uint64_t stackPair[2];
        stackPair[0] = 0;
        stackPair[1] = (uint64_t)((char*)f.v.m_pFirst
                                   + 3 * 0x10);
        BcastVecInsert(&f.v, stackPair, 3, pair);
        assert(f.Size() == 7);
        assert(f.A(0) == 10 && f.A(1) == 20 &&
               f.A(2) == 30);
        assert(f.A(3) == 55 && f.B(3) == 5);
        assert(f.A(4) == 55 && f.B(4) == 5);
        assert(f.A(5) == 55 && f.B(5) == 5);
        assert(f.A(6) == 40 && f.B(6) == 4);
        assert(f.v.m_pFirst == f.buf);
        printf("S7 ok (insert shift)\n"); fflush(stdout);
    }

    // ==== S8: Insert APPEND at END (pos = LAST) ====
    {
        uint64_t pairs[4] = { 1, 10, 2, 20 };
        Fixture f; f.Init(4, 2, pairs);
        uint64_t pair[2] = { 88, 8 };
        uint64_t stackPair[2];
        stackPair[0] = 0;
        stackPair[1] = (uint64_t)f.v.m_pLast;
        BcastVecInsert(&f.v, stackPair, 2, pair);
        assert(f.Size() == 4);
        assert(f.A(0) == 1 && f.A(1) == 2);
        assert(f.A(2) == 88 && f.B(2) == 8);
        assert(f.A(3) == 88 && f.B(3) == 8);
        printf("S8 ok (insert append)\n"); fflush(stdout);
    }

    // ==== S9: Resize GROW (append at end) ====
    {
        uint64_t pairs[4] = { 1, 10, 2, 20 };
        Fixture f; f.Init(4, 2, pairs);
        uint64_t pair[2] = { 66, 6 };
        BcastVecResize(&f.v, 4, pair);
        assert(f.Size() == 4);
        assert(f.A(0) == 1 && f.A(1) == 2);
        assert(f.A(2) == 66 && f.B(2) == 6);
        assert(f.A(3) == 66 && f.B(3) == 6);
        assert(f.v.m_pCap == (char*)f.v.m_pFirst
                                 + 4 * 0x10);
        printf("S9 ok (resize grow)\n"); fflush(stdout);
    }

    // ==== S10: Resize SHRINK ====
    {
        uint64_t pairs[8] = { 1,1, 2,2, 3,3, 4,4 };
        Fixture f; f.Init(8, 4, pairs);
        uint64_t pair[2] = { 0, 0 };
        BcastVecResize(&f.v, 2, pair);
        assert(f.Size() == 2);
        assert(f.A(0) == 1 && f.A(1) == 2);
        assert(s_nInvalid == 0);
        printf("S10 ok (resize shrink)\n"); fflush(stdout);
    }

    // ==== S11: Resize EQUAL -> no-op ====
    {
        uint64_t pairs[4] = { 5, 5, 6, 6 };
        Fixture f; f.Init(4, 2, pairs);
        uint64_t pair[2] = { 0, 0 };
        BcastVecResize(&f.v, 2, pair);
        assert(f.Size() == 2 && f.A(0) == 5 &&
               f.A(1) == 6);
        assert(s_nInvalid == 0);
        printf("S11 ok (resize equal)\n"); fflush(stdout);
    }

    // ==== S12: the throws ====
    {
        Fixture f;
        uint64_t pairs[1] = { 0 };
        f.Init(2, 1, pairs);
        bool threw = false;
        try {
            uint64_t stackPair[2];
            stackPair[0] = 0;
            stackPair[1] = (uint64_t)f.v.m_pFirst;
            BcastVecInsert(&f.v, stackPair,
                0xffffffffffffffffULL, (void*)0);
        } catch (const std::length_error& e) {
            threw = true;
            assert(std::string(e.what()) ==
                   "vector<T> too long");
        }
        assert(threw);
        // NOTE: the bad_alloc of the alloc guard is
        // UNREACHABLE through the insert engine in
        // the raw: the engine's own _Max - oldN < n
        // length guard fires first for every n that
        // could overflow the alloc guard (documented
        // gate ORDER - verified against 1400b6290)
        printf("S12 ok (throws)\n"); fflush(stdout);
    }

    // ==== S13: the invalid-param seam ====
    {
        uint64_t pairs[8] = { 1,1, 2,2, 3,3, 4,4 };
        Fixture f; f.Init(8, 4, pairs);
        // corrupt the proxy chain: the "container"
        // seen through the head is a fake with a
        // smaller LAST -> shrink range check fires
        SBVec fake;
        std::memset(&fake, 0, sizeof fake);
        fake.m_pFirst = f.v.m_pFirst;
        fake.m_pLast = (char*)f.v.m_pFirst + 2*0x10;
        f.pCont = &fake;
        uint64_t pair[2] = { 0, 0 };
        BcastVecResize(&f.v, 3, pair);
        assert(s_nInvalid == 1);
        // size unchanged (aborted before the cut)
        assert(f.Size() == 4);
        printf("S13 ok (invalid seam)\n"); fflush(stdout);
    }

    printf("M67a ALL-OK\n");
    return 0;
}
