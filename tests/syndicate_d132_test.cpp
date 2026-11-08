// D132 — the next sixteen bodies of the cluster: 0x1417c5fa0 and 0x1417c6040 (the two
//   tree increments), 0x1417c60e0 / 0x1417c60f0 / 0x1417c6160 (addresses and the 0x30
//   slot), 0x1417c6100 / 0x1417c6170 (the two rotations), 0x1417c61d0, 0x1417c6210,
//   0x1417c6250 / 0x1417c6280 (four qword copies), 0x1417c62b0 / 0x1417c6330 (the two
//   0x29 / 0x21 node builds), 0x1417c6360 and the two 0x21 walks.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
void SynAccInc29_1417c5fa0(void*);
void SynAccInc41_1417c6040(void*);
void* SynAccCurrPlus18_1417c61d0(void*);
bool SynAccIterNe_1417c6210(void*, void*);
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char it[0x10];
    alignas(16) unsigned char H[0x60], X[0x60], Y[0x60], N[0x60], P[0x60], S[0x60];
    alignas(16) unsigned char T[0x40];
    alignas(16) unsigned char dst[0x40], pa[0x20], pb[0x20], pair[0x20];
    std::memset(it, 0, sizeof it);
    std::memset(H, 0, sizeof H); std::memset(X, 0, sizeof X); std::memset(Y, 0, sizeof Y);
    std::memset(N, 0, sizeof N); std::memset(P, 0, sizeof P); std::memset(S, 0, sizeof S);
    std::memset(T, 0, sizeof T);

    // ---- 0x1417c5fa0: the node is the header, so the iterator takes its 0x10 child
    {
        H[0x29] = 1;                        // the header carries the flag
        *(void**)(H + 0x10) = X;
        X[0x29] = 0;
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = H;
        SynAccInc29_1417c5fa0(it);
        assert(*(void**)(it + 8) == (void*)X);
    }

    // ---- the real node whose left child carries the flag climbs to its parent
    {
        std::memset(it, 0, sizeof it);
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = N;
        N[0x29] = 0;
        S[0x29] = 1;
        *(void**)(N) = S;                   // left child is the flagged node
        *(void**)(N + 8) = P;               // its parent
        P[0x29] = 1;                        // the parent is flagged too, so the walk stops
        SynAccInc29_1417c5fa0(it);
        assert(*(void**)(it + 8) == (void*)P);
    }

    // ---- 0x1417c6040: the same shape on the 0x41 flag
    {
        std::memset(it, 0, sizeof it);
        H[0x41] = 1;
        *(void**)(H + 0x10) = X;
        X[0x41] = 0;
        *(void**)it = (void*)0x1;
        *(void**)(it + 8) = H;
        SynAccInc41_1417c6040(it);
        assert(*(void**)(it + 8) == (void*)X);
    }

    // ---- 0x1417c60e0 / 0x1417c60f0 / 0x1417c6160
    {
        assert(SynAccPlus28_1417c60e0(N) == (void*)(N + 0x28));
        assert(SynAccPlus18_1417c60f0(N) == (void*)(N + 0x18));
        alignas(16) unsigned char inner[0x40];
        *(void**)(N + 0x30) = inner;
        assert(SynAccSlot30Plus10_1417c6160(N) == (void*)(inner + 0x10));
    }

    // ---- 0x1417c6100: the 0x10 side rises, and the head's 0x8 takes it
    {
        std::memset(H, 0, sizeof H); std::memset(X, 0, sizeof X); std::memset(S, 0, sizeof S);
        std::memset(T, 0, sizeof T);
        *(void**)(T + 0x30) = H;
        H[0x29] = 1;
        *(void**)(H + 8) = X;
        X[0x29] = 0;
        *(void**)(X + 8) = H;
        *(void**)(X + 0x10) = S;
        S[0x29] = 1;
        *(void**)(S) = S;                   // the flagged node points at itself
        assert(SynAccRotRight_1417c6100(T, X) == (void*)X);
        assert(*(void**)(H + 8) == (void*)S);   // the head took the new root
        assert(*(void**)(S) == (void*)X);       // and the rotation kept the two leads
        assert(*(void**)(X + 8) == (void*)S);
    }

    // ---- 0x1417c6170: the mirror, the 0x0 side rises
    {
        std::memset(H, 0, sizeof H); std::memset(X, 0, sizeof X); std::memset(Y, 0, sizeof Y);
        std::memset(T, 0, sizeof T);
        *(void**)(T + 0x30) = H;
        H[0x29] = 1;
        *(void**)(H + 8) = X;
        X[0x29] = 0;
        *(void**)(X + 8) = H;
        *(void**)(X) = Y;
        Y[0x29] = 1;
        *(void**)(Y + 0x10) = Y;
        assert(SynAccRotLeft_1417c6170(T, X) == (void*)X);
        assert(*(void**)(H + 8) == (void*)Y);
        assert(*(void**)(Y + 0x10) == (void*)X);
        assert(*(void**)(X + 8) == (void*)Y);
    }

    // ---- 0x1417c61d0: the 0x30 slot of the lead's lead, then 0x18 on the node
    {
        std::memset(it, 0, sizeof it);
        unsigned char* L = S;
        *(void**)(it) = L;                    // the lead the body starts from
        *(void**)(L) = P;                    // the lead's lead
        *(void**)(P + 0x30) = (void*)0x1234; // its 0x30 slot
        *(void**)(it + 8) = N;               // the node, different from the slot
        assert(SynAccCurrPlus18_1417c61d0(it) == (void*)(N + 0x18));
    }

    // ---- 0x1417c6210: equal words answer false, different words true
    {
        std::memset(N, 0, sizeof N); std::memset(P, 0, sizeof P);
        *(void**)N = N; *(void**)P = N;
        *(void**)(N + 8) = (void*)0x11;
        *(void**)(P + 8) = (void*)0x11;
        assert(SynAccIterNe_1417c6210(N, P) == false);
        *(void**)(P + 8) = (void*)0x22;
        assert(SynAccIterNe_1417c6210(N, P) == true);
        *(void**)(P + 8) = (void*)0x11;
        *(void**)P = X;
        assert(SynAccIterNe_1417c6210(N, P) == false);
    }

    // ---- 0x1417c6250 / 0x1417c6280: 0x20 bytes, the first 0x10 from rdx, the rest from r8
    {
        std::memset(pa, 0x11, sizeof pa);
        std::memset(pb, 0x22, sizeof pb);
        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAccCopy32_1417c6250(dst, pa, pb) == (void*)dst);
        assert(*(void**)(dst + 0) == *(void**)(pa + 0));
        assert(*(void**)(dst + 8) == *(void**)(pa + 8));
        assert(*(void**)(dst + 0x10) == *(void**)(pb + 0));
        assert(*(void**)(dst + 0x18) == *(void**)(pb + 8));
        assert(dst[0x20] == 0xAB);                 // nothing past 0x20

        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAccCopy32_1417c6280(dst, pa, pb) == (void*)dst);
        assert(*(void**)(dst + 0x10) == *(void**)(pb + 0));
        assert(*(void**)(dst + 0x18) == *(void**)(pb + 8));
    }

    // ---- 0x1417c62b0: the 0x29 node, the sentinel cleared after the pair lands
    {
        std::memset(dst, 0xAB, sizeof dst);
        memset(pair, 0, sizeof pair);
        *(void**)(pair) = (void*)0xA1;
        *(void**)(pair + 8) = (void*)0xA2;
        assert(SynAccCtor_1417c62b0(dst, (void*)0x01, (void*)0x02, (void*)0x03, pair, 0x5A)
               == (void*)dst);
        assert(*(void**)(dst + 0) == (void*)0x01);
        assert(*(void**)(dst + 8) == (void*)0x02);
        assert(*(void**)(dst + 0x10) == (void*)0x03);
        assert(*(void**)(dst + 0x18) == (void*)0xA1);
        assert(*(void**)(dst + 0x20) == (void*)0xA2);
        assert(dst[0x28] == 0x5A);
        assert(dst[0x29] == 0x00);                 // cleared, whatever it held
    }

    // ---- 0x1417c6330: the 0x21 node, the byte at 0x20 and the sentinel at 0x21
    {
        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAccCtor_1417c6330(dst, (void*)0x01, (void*)0x02, (void*)0x03, pair, 0x7E)
               == (void*)dst);
        assert(*(void**)(dst + 0) == (void*)0x01);
        assert(*(void**)(dst + 8) == (void*)0x02);
        assert(*(void**)(dst + 0x10) == (void*)0x03);
        assert(*(void**)(dst + 0x18) == (void*)0xA1);
        assert(dst[0x20] == 0x7E);
        assert(dst[0x21] == 0x00);
        assert(dst[0x22] == 0xAB);                 // nothing past 0x21
    }

    // ---- 0x1417c6360: the lead qword cleared
    {
        std::memset(N, 0xAB, sizeof N);
        assert(SynAccZeroQword_1417c6360(N) == (void*)N);
        assert(*(void**)N == nullptr);
        assert(N[8] == 0xAB);
    }

    // ---- 0x1417c6370: the 0x21 walk through +0x10
    {
        std::memset(N, 0, sizeof N); std::memset(P, 0, sizeof P); std::memset(S, 0, sizeof S);
        *(void**)(N + 0x10) = N;
        N[0x21] = 1;
        assert(SynAccWalk10_21_1417c6370(N) == (void*)N);

        N[0x21] = 0;
        *(void**)(N + 0x10) = P;
        *(void**)(P + 0x10) = S;
        S[0x21] = 1;
        assert(SynAccWalk10_21_1417c6370(N) == (void*)P);
        assert(SynAccWalk10_21_1417c6370(P) == (void*)P);
    }

    // ---- 0x1417c63a0: the 0x21 walk through the lead
    {
        std::memset(N, 0, sizeof N); std::memset(P, 0, sizeof P); std::memset(S, 0, sizeof S);
        *(void**)N = N;
        N[0x21] = 1;
        assert(SynAccWalk21_1417c63a0(N) == (void*)N);

        N[0x21] = 0;
        *(void**)N = P;
        *(void**)P = S;
        S[0x21] = 1;
        assert(SynAccWalk21_1417c63a0(N) == (void*)P);
        assert(SynAccWalk21_1417c63a0(P) == (void*)P);
    }

    std::printf("SYNDICATE_D132_OK: sixteen more cluster bodies, 16 units, 48 checks\n");
    return 0;
}
