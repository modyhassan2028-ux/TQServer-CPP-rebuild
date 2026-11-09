// D148 — twelve bodies: 0x1417c7850 (the copied-temp comparison), the pair fillers
//   0x1417c78a0 / 0x1417c78c0 and the keyed one 0x1417c7a10, the two +0x18 accessors
//   0x1417c78e0 / 0x1417c7930, 0x1417c7920, the wrapper 0x1417c7970 and the four lead frees.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/syndicate/src/synacc.h"
using namespace tq;

namespace tq {
bool SynAccIterEq_1417c7850(void*, void*);
void* SynAccCurrPlus18_1417c78e0(void*);
void* SynAccCurrPlus18_1417c7930(void*);
void* SynAccDecCall_1417c7970(void*);
void SynAccFreeLead_1417c7990(void*);
void SynAccFreeLead_1417c79b0(void*);
void SynAccFreeLead_1417c79d0(void*);
void SynAccFreeLead_1417c79f0(void*);
void* SynAccFindPair_1417c7a10(void*, void*, const void*);
}

int main() {
    alignas(16) unsigned char tree[0x40], head[0x60], root[0x60], n5[0x60], out[0x20];
    std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
    std::memset(root, 0, sizeof root); std::memset(n5, 0, sizeof n5);

    *(void**)(tree + 0x30) = head;
    *(void**)(head + 8) = root;
    *(void**)(head) = head;                 // the header's own lead
    *(void**)(root) = n5;
    *(void**)(root + 0x10) = n5;            // a stand-in sentinel-free stand-in
    *(uint32_t*)(root + 0x18) = 10;
    *(void**)(n5) = n5;
    *(void**)(n5 + 0x10) = n5;
    *(uint32_t*)(n5 + 0x18) = 5;
    n5[0x29] = 1;                           // n5 is the stop node

    // ---- 0x1417c78a0: the header's lead and the tree's first qword
    {
        std::memset(out, 0, sizeof out);
        assert(SynAccIterFromHeader_1417c78a0(tree, out) == (void*)out);
        assert(*(void**)(out) == *(void**)tree);
        assert(*(void**)(out + 8) == *(void**)(head));
    }

    // ---- 0x1417c78c0: the header itself
    {
        std::memset(out, 0xAB, sizeof out);
        assert(SynAccIterHeaderPair_1417c78c0(tree, out) == (void*)out);
        assert(*(void**)(out) == *(void**)tree);
        assert(*(void**)(out + 8) == (void*)head);
    }

    // ---- 0x1417c7920: both qwords cleared
    {
        unsigned char two[0x20];
        std::memset(two, 0xCD, sizeof two);
        assert(SynAccZeroTwo_1417c7920(two) == (void*)two);
        assert(*(uint64_t*)(two) == 0 && *(uint64_t*)(two + 8) == 0);
        assert(*(unsigned char*)(two + 0x10) == 0xCD);       // nothing past the two qwords
    }

    // ---- 0x1417c7850: the comparison copies first, then compares the +0x8 words
    {
        unsigned char a[0x20], b[0x20];
        std::memset(a, 0, sizeof a); std::memset(b, 0, sizeof b);
        *(void**)(a) = a; *(void**)(b) = a;
        *(void**)(a + 8) = (void*)0x5151; *(void**)(b + 8) = (void*)0x5151;
        assert(SynAccIterEq_1417c7850(a, b) == true);
        *(void**)(b + 8) = (void*)0x6262;
        assert(SynAccIterEq_1417c7850(a, b) == false);
    }

    // ---- the two +0x18 accessors answer with the node slot advanced by 0x18
    {
        unsigned char it[0x10];
        std::memset(it, 0, sizeof it);
        *(void**)(it) = root;                    // lead
        *(void**)(it + 8) = n5;                  // the node slot
        assert(SynAccCurrPlus18_1417c78e0(it) == (void*)(n5 + 0x18));
        assert(SynAccCurrPlus18_1417c7930(it) == (void*)(n5 + 0x18));
    }

    // ---- 0x1417c7970: the decrement wrapper hands the iterator back
    {
        unsigned char it[0x10];
        std::memset(it, 0, sizeof it);
        n5[0x29] = 1;                            // the node carries the flag, so it stays put
        *(void**)(it) = head;
        *(void**)(it + 8) = n5;
        assert(SynAccDecCall_1417c7970(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)n5);
    }

    // ---- the four lead frees take the lead, and the lead slot still reads back
    {
        void* p1 = ::operator new(0x10);
        std::memset(p1, 0, 0x10);
        unsigned char hold[0x10];
        *(void**)(hold) = p1;
        SynAccFreeLead_1417c7990(hold);
        assert(*(void**)(hold) == p1);
        void* p2 = ::operator new(0x10);
        *(void**)(hold) = p2;
        SynAccFreeLead_1417c79b0(hold);
        assert(*(void**)(hold) == p2);
        void* p3 = ::operator new(0x10);
        *(void**)(hold) = p3;
        SynAccFreeLead_1417c79d0(hold);
        assert(*(void**)(hold) == p3);
        void* p4 = ::operator new(0x10);
        *(void**)(hold) = p4;
        SynAccFreeLead_1417c79f0(hold);
        assert(*(void**)(hold) == p4);
    }

    // ---- 0x1417c7a10: the keyed descent fills the pair
    {
        // the two stop nodes the walk ends on, flagged in their own 0x29 byte
        alignas(16) unsigned char stopL[0x60], stopR[0x60];
        std::memset(stopL, 0, sizeof stopL); std::memset(stopR, 0, sizeof stopR);
        stopL[0x29] = 1; stopR[0x29] = 1;

        n5[0x29] = 0;                            // n5 is a real node for this walk
        *(void**)(root) = n5;                    // root's left
        *(void**)(root + 0x10) = stopR;          // root's right
        *(void**)(n5) = stopL;                   // n5's left
        *(void**)(n5 + 0x10) = stopL;            // n5's right

        std::memset(out, 0, sizeof out);
        uint32_t k7 = 7;
        assert(SynAccFindPair_1417c7a10(tree, out, &k7) == (void*)out);
        assert(*(void**)(out) == *(void**)tree);
        assert(*(void**)(out + 8) == (void*)root);   // 10 >= 7 turned left at the root

        std::memset(out, 0, sizeof out);
        uint32_t k3 = 3;
        assert(SynAccFindPair_1417c7a10(tree, out, &k3) == (void*)out);
        assert(*(void**)(out + 8) == (void*)n5);     // 5 >= 3 turned left at n5 as well

        std::memset(out, 0xCD, sizeof out);
        uint32_t k99 = 99;
        assert(SynAccFindPair_1417c7a10(tree, out, &k99) == (void*)out);
        assert(*(void**)(out + 8) == (void*)head);   // never turned left: the header
    }

    std::printf("SYNDICATE_D148_OK: twelve bodies, 8 units, 30 checks\n");
    return 0;
}
