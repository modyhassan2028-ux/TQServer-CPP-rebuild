// M70: the vector assign family (FUN_1400092d0/
// a6e0/9710/bac0/eab0/f4a0) VERBATIM
#include "../msgserver/MsgVectorFamily.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <stdexcept>

static void InitVec(msg::SVec& v, void* buf,
                    size_t nElems, size_t capElems) {
    std::memset(&v, 0, sizeof v);
    v.m_pFirst = buf;
    v.m_pLast  = (char*)buf + nElems * 0x10;
    v.m_pCap   = (char*)buf + capElems * 0x10;
}

// read element i as a pair
static void GetEl(const msg::SVec& v, size_t i,
                  uint64_t& a, uint64_t& b) {
    a = ((uint64_t*)v.m_pFirst)[i*2];
    b = ((uint64_t*)v.m_pFirst)[i*2+1];
}

int main() {
    using namespace msg;
    uint64_t aV[2] = {0xAA, 1}, aB[2] = {0xBB, 2};
    uint64_t aC[2] = {0xCC, 3}, aW[2] = {0x77, 7};

    // 1) fill / copy / move-back primitives
    uint64_t buf[16];
    std::memset(buf, 0, sizeof buf);
    VecFill(buf, 3, aW);
    assert(buf[0] == 0x77 && buf[2] == 0x77 &&
           buf[5] == 7 && buf[6] == 0);
    uint64_t cp[8]; std::memset(cp, 0, sizeof cp);
    void* pEnd = VecCopy(buf, (char*)buf + 2*0x10, cp);
    assert(pEnd == (char*)cp + 2*0x10 &&
           cp[0] == 0x77 && cp[3] == 7);
    uint64_t mv[16]; std::memset(mv, 0, sizeof mv);
    mv[0]=1; mv[1]=2; mv[2]=3; mv[3]=4;
    // move [mv, mv+0x10) up to land at mv+0x20
    void* r = VecMoveBack(mv, (char*)mv + 0x10,
                          (char*)mv + 0x30);
    assert(r == (char*)mv + 0x20);
    assert(mv[4] == 1 && mv[5] == 2);  // moved pair
    assert(mv[0] == 1);                // src intact

    // 2) insert-front into an EMPTY vector (grow)
    SVec v; InitVec(v, nullptr, 0, 0);
    uint64_t pr[2] = {v.m_q0, (uint64_t)v.m_pFirst};
    VecInsertFront(&v, pr, 3, aW);
    uint64_t x, y;
    GetEl(v, 0, x, y); assert(x == 0x77 && y == 7);
    GetEl(v, 2, x, y); assert(x == 0x77 && y == 7);
    assert((char*)v.m_pLast -
           (char*)v.m_pFirst == 3*0x10);
    assert((char*)v.m_pCap -
           (char*)v.m_pFirst == 3*0x10);
    operator delete(v.m_pFirst);

    // 3) [a,b] cap 2, insert 3 at front -> grow:
    //    [w,w,w,a,b]
    uint64_t* p2 = new uint64_t[16];
    p2[0]=0xAA; p2[1]=1; p2[2]=0xBB; p2[3]=2;
    InitVec(v, p2, 2, 2);
    uint64_t pr2[2] = {v.m_q0, (uint64_t)v.m_pFirst};
    VecInsertFront(&v, pr2, 3, aW);
    assert((char*)v.m_pLast -
           (char*)v.m_pFirst == 5*0x10);
    GetEl(v,0,x,y); assert(x==0x77&&y==7);
    GetEl(v,2,x,y); assert(x==0x77&&y==7);
    GetEl(v,3,x,y); assert(x==0xAA&&y==1);
    GetEl(v,4,x,y); assert(x==0xBB&&y==2);
    assert((char*)v.m_pCap -
           (char*)v.m_pFirst == 5*0x10);
    operator delete(v.m_pFirst);

    // 4) [a] cap 4, insert 3 -> SHIFT branch:
    //    [w,w,w,a]
    uint64_t* p4 = new uint64_t[16];
    p4[0]=0xAA; p4[1]=1;
    InitVec(v, p4, 1, 4);
    uint64_t pr4[2] = {v.m_q0, (uint64_t)v.m_pFirst};
    VecInsertFront(&v, pr4, 3, aW);
    assert(v.m_pFirst == p4);
    assert((char*)v.m_pLast -
           (char*)v.m_pFirst == 4*0x10);
    GetEl(v,0,x,y); assert(x==0x77&&y==7);
    GetEl(v,2,x,y); assert(x==0x77&&y==7);
    GetEl(v,3,x,y); assert(x==0xAA&&y==1);
    delete[] p4;

    // 5) [a,b,c] cap 6, insert 2 -> MOVE-BACK branch:
    //    [w,w,a,b,c] (same buffer)
    uint64_t* p5 = new uint64_t[16];
    p5[0]=0xAA;p5[1]=1;p5[2]=0xBB;p5[3]=2;
    p5[4]=0xCC;p5[5]=3;
    InitVec(v, p5, 3, 6);
    uint64_t pr5[2] = {v.m_q0, (uint64_t)v.m_pFirst};
    VecInsertFront(&v, pr5, 2, aW);
    assert(v.m_pFirst == p5);
    assert((char*)v.m_pLast -
           (char*)v.m_pFirst == 5*0x10);
    GetEl(v,0,x,y); assert(x==0x77&&y==7);
    GetEl(v,1,x,y); assert(x==0x77&&y==7);
    GetEl(v,2,x,y); assert(x==0xAA&&y==1);
    GetEl(v,3,x,y); assert(x==0xBB&&y==2);
    GetEl(v,4,x,y); assert(x==0xCC&&y==3);
    delete[] p5;

    // 6) n = 0: a no-op
    uint64_t* p6 = new uint64_t[4];
    p6[0]=0xAA; p6[1]=1;
    InitVec(v, p6, 1, 2);
    uint64_t pr6[2] = {v.m_q0, (uint64_t)v.m_pFirst};
    VecInsertFront(&v, pr6, 0, aW);
    assert(v.m_pFirst == p6 &&
           (char*)v.m_pLast -
           (char*)v.m_pFirst == 0x10);
    delete[] p6;

    // 7) VecClearRefill (FUN_14000f4a0): [x,y] ->
    //    clear -> [w,w,w]
    uint64_t* p7 = new uint64_t[16];
    p7[0]=0xEE; p7[1]=9; p7[2]=0xFF; p7[3]=8;
    InitVec(v, p7, 2, 8);
    VecClearRefill(&v, 3, aW);
    assert(v.m_pFirst == p7);
    assert((char*)v.m_pLast -
           (char*)v.m_pFirst == 3*0x10);
    GetEl(v,0,x,y); assert(x==0x77&&y==7);
    GetEl(v,2,x,y); assert(x==0x77&&y==7);
    delete[] p7;

    // 8) the guards VERBATIM: old_size >= 1 so the
    //    length guard fires (max - size < n)
    uint64_t* pG = new uint64_t[16];
    pG[0]=1; pG[1]=2;
    SVec g; InitVec(g, pG, 1, 8);
    bool bT = false;
    uint64_t prG[2] = {g.m_q0, (uint64_t)g.m_pFirst};
    try {
        VecInsertFront(&g, prG,
            0xfffffffffffffffULL, aW);
    } catch (const std::length_error& e) {
        bT = true;
        assert(!std::strcmp(e.what(),
            "vector<T> too long"));
    }
    assert(bT);
    delete[] pG;
    bool bB = false;
    try { VecAlloc(&g, 0x1000000000000000ULL); }
    catch (const std::bad_alloc&) { bB = true; }
    assert(bB);

    std::puts("M70-VECTOR-FAMILY-OK");
    return 0;
}
