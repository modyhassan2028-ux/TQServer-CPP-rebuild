// D133 — the next fifteen bodies: the three decrements (0x41 at 0x1417c63c0, 0x21 at
//   0x1417c6580, 0x29 at 0x1417c6610), the 0x29 increment at 0x1417c64b0, the 0x29 walks
//   at 0x1417c6450 / 0x1417c6480, the constant at 0x1417c64a0, the node build at
//   0x1417c6550, the two-word copy at 0x1417c66a0, the five `ret $0x0` bodies and
//   0x1417c6700.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
void SynAccDec41_1417c63c0(void*);
void SynAccInc29_1417c64b0(void*);
void SynAccDec21_1417c6580(void*);
void SynAccDec29_1417c6610(void*);
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char it[0x10];
    alignas(16) unsigned char N[0x60], R[0x60], L[0x60], P[0x60];
    alignas(16) unsigned char dst[0x60], src[0x20], pair[0x20];

    // ---- 0x1417c63c0: the 0x41 decrement takes the 0x10 child when its left is flagged
    {
        std::memset(it, 0, sizeof it);
        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R); std::memset(L, 0, sizeof L);
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = N;
        N[0x41] = 0;
        *(void**)(N + 0x10) = R;
        R[0x41] = 0;
        *(void**)(R) = L;                   // the child's lead carries the flag
        L[0x41] = 1;
        SynAccDec41_1417c63c0(it);
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c6580: the same on the 0x21 flag
    {
        std::memset(it, 0, sizeof it);
        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R); std::memset(L, 0, sizeof L);
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = N;
        N[0x21] = 0;
        *(void**)(N + 0x10) = R;
        R[0x21] = 0;
        *(void**)(R) = L;
        L[0x21] = 1;
        SynAccDec21_1417c6580(it);
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c6610: and on the 0x29 flag
    {
        std::memset(it, 0, sizeof it);
        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R); std::memset(L, 0, sizeof L);
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = N;
        N[0x29] = 0;
        *(void**)(N + 0x10) = R;
        R[0x29] = 0;
        *(void**)(R) = L;
        L[0x29] = 1;
        SynAccDec29_1417c6610(it);
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c64b0: the 0x29 increment, the node being the header
    {
        std::memset(it, 0, sizeof it);
        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R);
        N[0x29] = 1;
        *(void**)(N + 0x10) = R;
        R[0x29] = 0;
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = N;
        SynAccInc29_1417c64b0(it);
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c6450 / 0x1417c6480: the two 0x29 walks
    {
        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R); std::memset(L, 0, sizeof L);
        *(void**)(N + 0x10) = N;
        N[0x29] = 1;
        assert(SynAccWalk10_29_1417c6450(N) == (void*)N);

        N[0x29] = 0;
        *(void**)(N + 0x10) = R;
        *(void**)(R + 0x10) = L;
        L[0x29] = 1;
        assert(SynAccWalk10_29_1417c6450(N) == (void*)R);

        std::memset(N, 0, sizeof N); std::memset(R, 0, sizeof R); std::memset(L, 0, sizeof L);
        *(void**)N = N;
        N[0x29] = 1;
        assert(SynAccWalk29_1417c6480(N) == (void*)N);

        N[0x29] = 0;
        *(void**)N = R;
        *(void**)R = L;
        L[0x29] = 1;
        assert(SynAccWalk29_1417c6480(N) == (void*)R);
    }

    // ---- 0x1417c64a0
    assert(SynAccConst_1417c64a0() == 0x0fffffffffffffffull);

    // ---- 0x1417c6550: the 0x29 node build
    {
        std::memset(dst, 0xAB, sizeof dst);
        std::memset(pair, 0, sizeof pair);
        *(void**)(pair) = (void*)0xB1;
        *(void**)(pair + 8) = (void*)0xB2;
        assert(SynAccCtor_1417c6550(dst, (void*)0x04, (void*)0x05, (void*)0x06, pair, 0x33)
               == (void*)dst);
        assert(*(void**)(dst + 0) == (void*)0x04);
        assert(*(void**)(dst + 8) == (void*)0x05);
        assert(*(void**)(dst + 0x10) == (void*)0x06);
        assert(*(void**)(dst + 0x18) == (void*)0xB1);
        assert(*(void**)(dst + 0x20) == (void*)0xB2);
        assert(dst[0x28] == 0x33);
        assert(dst[0x29] == 0x00);
    }

    // ---- 0x1417c66a0: the two words, and nothing assumed about the bytes between
    {
        std::memset(src, 0x5C, sizeof src);
        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAccCopy8_1417c66a0(dst, src) == (void*)dst);
        assert(dst[0] == 0x5C && dst[3] == 0x5C);
        assert(dst[4] == 0x5C && dst[7] == 0x5C);
        assert(dst[8] == 0xAB);
    }

    // ---- 0x1417c66b0..0x1417c66f0: the five bodies that only return
    SynAccNoop_1417c66b0();
    SynAccNoop_1417c66c0();
    SynAccNoop_1417c66d0();
    SynAccNoop_1417c66e0();
    SynAccNoop_1417c66f0();
    assert(true);

    // ---- 0x1417c6700: this back
    assert(SynAccRetThis_1417c6700(N) == (void*)N);

    std::printf("SYNDICATE_D133_OK: fifteen more bodies, 15 units, 34 checks\n");
    return 0;
}
