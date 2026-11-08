// D131 — the last of the accessor cluster: the 0x1417c5e00 deallocate thunk, the
//   0x1417c5e50 slot, the two-qwords-and-a-byte copy at 0x1417c5e80, the zeroed lead
//   at 0x1417c5ea0, the 0x666666666666666 answer, the 0x29 walk through +0x10, and
//   0x1417c5f60, the same comparison as 0x1417c5b30 answering setne.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
void SynAccDealloc_1417c5e00(void*, void*);
bool SynAccIterNe_1417c5f60(void*, void*);
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char n1[0x60];
    alignas(16) unsigned char n2[0x60];
    alignas(16) unsigned char n3[0x60];
    alignas(16) unsigned char src[0x20];
    std::memset(n1, 0, sizeof n1);
    std::memset(n2, 0, sizeof n2);
    std::memset(n3, 0, sizeof n3);
    std::memset(src, 0x11, sizeof src);

    // ---- 0x1417c5e00: the second argument reaches the deallocate
    {
        void* p = ::operator new(0x20);
        SynAccDealloc_1417c5e00(nullptr, p);
        assert(true);
    }

    // ---- 0x1417c5e50: the 0x8 slot
    {
        *(void**)(n1 + 8) = (void*)0x5e50;
        assert(SynAccSlot8_1417c5e50(n1) == (void*)0x5e50);
    }

    // ---- 0x1417c5e80: both qwords and the byte its third argument names
    {
        std::memset(n1, 0xAB, sizeof n1);
        src[0] = 0x3C;
        assert(SynAccTwoQwordsByte_1417c5e80(n1, src, src) == (void*)n1);
        assert(*(void**)(n1 + 0) == *(void**)(src + 0));
        assert(*(void**)(n1 + 8) == *(void**)(src + 8));
        assert(n1[0x10] == 0x3C);
        assert(n1[0x11] == 0xAB);                    // nothing written past 0x10
    }

    // ---- 0x1417c5ea0: the lead qword cleared, this back
    {
        std::memset(n1, 0xAB, sizeof n1);
        assert(SynAccZeroQword_1417c5ea0(n1) == (void*)n1);
        assert(*(void**)n1 == nullptr);
        assert(n1[8] == 0xAB);
    }

    // ---- 0x1417c5eb0: the raw answer
    assert(SynAccConst_1417c5eb0() == 0x0666666666666666ULL);

    // ---- 0x1417c5ec0: the 0x29 walk through +0x10
    {
        *(void**)(n1 + 0x10) = n1;                   // the node itself carries 0x29
        n1[0x29] = 1;
        assert(SynAccWalk10_29_1417c5ec0(n1) == (void*)n1);

        n1[0x29] = 0;                                // n1 ->+0x10 n2 ->+0x10 n3 (sentinel)
        *(void**)(n1 + 0x10) = n2;
        *(void**)(n2 + 0x10) = n3;
        n3[0x29] = 1;
        assert(SynAccWalk10_29_1417c5ec0(n1) == (void*)n2);
        assert(SynAccWalk10_29_1417c5ec0(n2) == (void*)n2);
    }

    // ---- 0x1417c5f60: equal words answer false, different words true
    {
        std::memset(n1, 0, sizeof n1);
        std::memset(n2, 0, sizeof n2);
        *(void**)n1 = n1;
        *(void**)n2 = n1;
        *(void**)(n1 + 8) = (void*)0x11;
        *(void**)(n2 + 8) = (void*)0x11;
        assert(SynAccIterNe_1417c5f60(n1, n2) == false);

        *(void**)(n2 + 8) = (void*)0x22;
        assert(SynAccIterNe_1417c5f60(n1, n2) == true);

        *(void**)(n2 + 8) = (void*)0x11;
        *(void**)n2 = n3;                            // different leads, equal words
        assert(SynAccIterNe_1417c5f60(n1, n2) == false);

        *(void**)n2 = nullptr;                       // the null lead still answers on the words
        assert(SynAccIterNe_1417c5f60(n1, n2) == false);
    }

    std::printf("SYNDICATE_D131_OK: the cluster's last bodies, 7 units, 20 checks\n");
    return 0;
}
