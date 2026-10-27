// M68: the hash map intrusive LIST family
// (FUN_14000a280/a300/cae0/cbd0/f1c0) VERBATIM
#include "../msgserver/MsgHashList.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>

struct LNode { void* pNext; void* pPrev;
               uint64_t qKey; };

int main() {
    // the list fixture: +0x0 first slot, +0x28 END,
    // +0x30 size (offsets VERBATIM)
    uint8_t aL[0x38]; std::memset(aL,0,sizeof aL);
    LNode nd; nd.pNext=&nd; nd.pPrev=&nd; nd.qKey=0;
    *(void**)(aL+0x28) = &nd;
    *(uint64_t*)(aL+0x30) = 0;
    *(void**)aL = &nd;   // empty: first = END

    // 1) node ctor VERBATIM (0x18 bytes):
    uint64_t qK = 0xABCD1234;
    void* pN1 = msg::HashListNodeNew(
        aL, &nd, &nd, &qK);
    assert(*(void**)pN1 == &nd &&
           *(void**)((char*)pN1+8) == &nd &&
           *(uint64_t*)((char*)pN1+0x10) == qK);
    operator delete(pN1);

    // 2) the size guard: bump then throw at max:
    msg::HashListBump(aL, 3);
    assert(*(uint64_t*)(aL+0x30) == 3);
    *(uint64_t*)(aL+0x30) = 0x1fffffffffffffffULL;
    bool bThrew = false;
    try { msg::HashListBump(aL, 1); }
    catch (const std::length_error& e) {
        bThrew = true;
        assert(std::strcmp(e.what(),
               "list<T> too long") == 0);
    }
    assert(bThrew);
    *(uint64_t*)(aL+0x30) = 0;

    // 3) emplace into the empty list (hint = END):
    void* it[2] = {nullptr, &nd};   // END-hint
    void* out[2] = {nullptr, nullptr};
    uint64_t qA = 10, qB = 20, qC = 30;
    msg::HashListEmplace(aL, out, it, &qA);
    void* pA = out[1];
    assert(pA != nullptr);
    assert(*(void**)((char*)pA+0) == &nd);      // next
    assert(*(void**)((char*)pA+8) == &nd);      // prev
    assert(*(uint64_t*)((char*)pA+0x10) == qA); // key
    assert(nd.pPrev == pA);                    // END prev
    assert(nd.pNext == pA);                    // END next
    assert(*(uint64_t*)(aL+0x30) == 1);        // size
    assert(out[0] == *(void**)aL);             // first

    // 4) emplace a tail node before END:
    it[1] = &nd;
    msg::HashListEmplace(aL, out, it, &qB);
    void* pB = out[1];
    assert(*(void**)((char*)pA+0) == pB);   // A next B
    assert(*(void**)((char*)pB+8) == pA);   // B prev A
    assert(nd.pPrev == pB);
    assert(*(uint64_t*)(aL+0x30) == 2);

    // 5) transfer: move B to the position of A
    // (the f1c0 same-list reposition) - the walk
    // math (traced from the VERBATIM relink) gives
    // the new order END->B->A->END:
    void* it1[2] = {*(void**)aL, pA};
    void* it2[2] = {*(void**)aL, pB};
    msg::HashListTransfer(aL, it1, aL, it2);
    assert(nd.pNext == pB && nd.pPrev == pA);
    assert(*(void**)((char*)pB+8) == &nd);   // B prev
    assert(*(void**)((char*)pB+0) == pA);   // B next
    assert(*(void**)((char*)pA+8) == pB);   // A prev
    assert(*(void**)((char*)pA+0) == &nd);  // A tail

    // 6) erase the node at it[1] (B = the head):
    void* itE[2] = {*(void**)aL, pB};
    msg::HashListErase(aL, out, itE);
    assert(*(void**)((char*)pA+0) == &nd);  // A->END
    assert(nd.pPrev == pA);
    assert(*(uint64_t*)(aL+0x30) == 1);     // size--
    assert(out[1] == pA);   // the next node
    // adjacency checks return without change:
    void* itS[2] = {*(void**)aL, pA};
    msg::HashListTransfer(aL, itS, aL, itS);
    assert(nd.pNext == pA && nd.pPrev == pA);

    std::puts("M68-HASH-LIST-OK");
    return 0;
}
