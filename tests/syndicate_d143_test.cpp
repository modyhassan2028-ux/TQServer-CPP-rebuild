// D143 — 0x1417c6f60 (the keyed search that answers the last node whose 0x18 key was not below
//   the argument), 0x1417c6f90 and 0x1417c6ff0 (the two rotations, byte for byte the bodies at
//   0x1417c6100 and 0x1417c6170 but at their own starts).
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

int main() {
    alignas(16) unsigned char tree[0x40];
    alignas(16) unsigned char S[0x60], R[0x60], N5[0x60], X[0x60], Y[0x60];

    // ---- 0x1417c6f60: the candidate is the last node the walk turned left at
    {
        std::memset(tree, 0, sizeof tree);
        std::memset(S, 0, sizeof S); S[0x29] = 1;
        std::memset(R, 0, sizeof R);
        std::memset(N5, 0, sizeof N5);
        *(void**)(tree + 0x30) = S;            // the header lives in the 0x30 slot
        *(void**)(S + 8) = R;                  // header's 0x8 is the root
        *(uint32_t*)(R + 0x18) = 10;           // root key
        *(void**)(R) = N5;                     // left
        *(void**)(R + 0x10) = S;               // right
        *(uint32_t*)(N5 + 0x18) = 5;
        *(void**)(N5) = S;
        *(void**)(N5 + 0x10) = S;

        uint32_t uKey = 7;                     // 10 >= 7 -> candidate root, then 5 < 7 -> right
        assert(SynAccSearch_1417c6f60(tree, &uKey) == (void*)R);

        uKey = 3;                              // 10 >= 3, then 5 >= 3 -> candidate N5
        assert(SynAccSearch_1417c6f60(tree, &uKey) == (void*)N5);

        uKey = 10;                             // equal is a `jae` too, so it turns left as well
        assert(SynAccSearch_1417c6f60(tree, &uKey) == (void*)R);

        uKey = 99;                             // nothing is >= it: the walk keeps the header
        assert(SynAccSearch_1417c6f60(tree, &uKey) == (void*)S);
    }

    // ---- 0x1417c6f90: the 0x10 side rises into the header
    {
        std::memset(tree, 0, sizeof tree); std::memset(S, 0, sizeof S);
        std::memset(X, 0, sizeof X);
        *(void**)(tree + 0x30) = S;
        S[0x29] = 1;
        *(void**)(S + 8) = X;
        *(void**)(X + 8) = S;
        unsigned char* pY = S;                 // y must be the node X points at on 0x10
        *(void**)(X + 0x10) = pY;
        *(void**)(pY) = pY;                    // and its 0x0 lead points at itself, flagged
        assert(SynAccRotRight_1417c6f90(tree, X) == (void*)X);
        assert(*(void**)(S + 8) == (void*)pY); // the header took the new root
        assert(*(void**)(pY) == (void*)X);     // and the two leads were re-pointed
        assert(*(void**)(X + 8) == (void*)pY);
    }

    // ---- 0x1417c6ff0: the mirror
    {
        std::memset(tree, 0, sizeof tree); std::memset(S, 0, sizeof S);
        std::memset(X, 0, sizeof X); std::memset(Y, 0, sizeof Y);
        *(void**)(tree + 0x30) = S;
        S[0x29] = 1;
        *(void**)(S + 8) = X;
        *(void**)(X + 8) = S;
        *(void**)(X) = Y;
        Y[0x29] = 1;
        *(void**)(Y + 0x10) = Y;
        assert(SynAccRotLeft_1417c6ff0(tree, X) == (void*)X);
        assert(*(void**)(S + 8) == (void*)Y);
        assert(*(void**)(Y + 0x10) == (void*)X);
        assert(*(void**)(X + 8) == (void*)Y);
    }

    std::printf("SYNDICATE_D143_OK: the keyed search and two rotations, 3 units, 11 checks\n");
    return 0;
}
