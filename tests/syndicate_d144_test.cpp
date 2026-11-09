// D144 — nine bodies: the no-ops 0x1417c7050 / 0x1417c7060 / 0x1417c71a0, the constants
//   0x1417c7070 and 0x1417c71b0, the two 0x41 rotations 0x1417c70e0 / 0x1417c7140 and the
//   0x21 keyed search 0x1417c71c0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
using namespace tq;

int main() {
    alignas(16) unsigned char tree[0x40], head[0x60], x[0x60], y[0x60], s[0x60];
    int checks = 0;

    // ---- the three no-ops and the two constants
    SynAccNoop_1417c7050();
    SynAccNoop_1417c7060();
    SynAccNoop_1417c71a0();
    assert(SynAccConst_1417c7070() == 0x0666666666666666ULL); ++checks;
    assert(SynAccConst_1417c71b0() == 0x1FFFFFFFFFFFFFFFULL); ++checks;

    // ---- 0x1417c70e0: the head link case, exactly as D132 read 0x1417c6100
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(y, 0, sizeof y); std::memset(s, 0, sizeof s);
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;      // the head names x as the root
        *(void**)(x + 8) = head;
        *(void**)(x + 0x10) = s;      // the 0x10 side is the sentinel
        *(void**)(s) = s;             // the sentinel points at itself
        s[0x41] = 1;                  // and carries the flag, so no parent is written
        // the lifted node is the one on the 0x10 side, which here is the sentinel itself
        assert(SynAccRotRight_1417c70e0(tree, x) == (void*)s);
        assert(*(void**)(x + 0x10) == (void*)s);   // mov (%r8),%rax wrote the sentinel back
        assert(*(void**)(head + 8) == (void*)s);
        assert(*(void**)(s) == (void*)x);
        assert(*(void**)(x + 8) == (void*)s);
        ++checks;
    }

    // ---- 0x1417c7140: the mirror head link case
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(y, 0, sizeof y); std::memset(s, 0, sizeof s);
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;
        *(void**)(x + 8) = head;
        *(void**)(x) = y;             // the 0x0 side is the one being lifted
        *(void**)(y + 0x10) = y;      // its 0x10 side points at itself and carries the flag
        y[0x41] = 1;
        assert(SynAccRotLeft_1417c7140(tree, x) == (void*)y);
        assert(*(void**)(x) == (void*)y);          // mov 0x10(%r8),%rax wrote it back
        assert(*(void**)(head + 8) == (void*)y);
        assert(*(void**)(y + 0x10) == (void*)x);
        assert(*(void**)(x + 8) == (void*)y);
        ++checks;
    }

    // ---- 0x1417c71c0: the 0x21 search, 32-bit compare, last left turn wins
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(y, 0, sizeof y); std::memset(s, 0, sizeof s);
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;      // root
        *(unsigned int*)(x + 0x18) = 10;
        *(void**)(x) = y;             // left child
        *(void**)(x + 0x10) = s;      // right child: the sentinel
        *(unsigned int*)(y + 0x18) = 5;
        *(void**)(y) = s;
        *(void**)(y + 0x10) = s;
        s[0x21] = 1;
        unsigned int k = 7;
        assert(SynAccSearch21_1417c71c0(tree, &k) == (void*)x);   // 10 >= 7 turns left, then 5 < 7
        k = 3;
        assert(SynAccSearch21_1417c71c0(tree, &k) == (void*)y);   // 10 >= 3, then 5 >= 3
        k = 99;
        assert(SynAccSearch21_1417c71c0(tree, &k) == (void*)head); // never turned left
        k = 10;
        assert(SynAccSearch21_1417c71c0(tree, &k) == (void*)x);   // an equal key takes jae
        ++checks;
    }

    std::printf("SYNDICATE_D144_OK: nine bodies, %d units, %d checks\n", 9, checks);
    return 0;
}
