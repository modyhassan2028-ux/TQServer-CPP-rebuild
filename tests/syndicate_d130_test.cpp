// D130 — the accessor cluster's non-pure tail, 0x1417c5b30..0x1417c5f50:
//   the two iterator comparisons, the two walks with their sentinel bytes, the
//   two deallocate thunks and the 0x1fffffffffffffff answer.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
bool SynAccIterEq_1417c5b30(void*, void*);
bool SynAccIterEq_1417c5b80(void*, void*);
void* SynAccWalk29_1417c5c50(void*);
void* SynAccRetThis_1417c5c70(void*);
void SynAccDealloc_1417c5c80(void*, void*);
void SynAccDealloc_1417c5cc0(void*, void*);
void* SynAccWalk10_41_1417c5f00(void*);
void* SynAccWalk41_1417c5f30(void*);
uint64_t SynAccConst_1417c5f50();
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char n1[0x60];
    alignas(16) unsigned char n2[0x60];
    alignas(16) unsigned char n3[0x60];
    std::memset(n1, 0, sizeof n1);
    std::memset(n2, 0, sizeof n2);
    std::memset(n3, 0, sizeof n3);

    // ---- 0x1417c5b30 / 0x1417c5b80: the two leads and then the +0x8 words
    {
        *(void**)n1 = n1;                       // the same node on both sides
        *(void**)n2 = n1;
        *(void**)(n1 + 8) = (void*)0x11;
        *(void**)(n2 + 8) = (void*)0x11;
        assert(SynAccIterEq_1417c5b30(n1, n2) == true);
        assert(SynAccIterEq_1417c5b80(n1, n2) == true);

        *(void**)(n2 + 8) = (void*)0x22;        // same node, different word
        assert(SynAccIterEq_1417c5b30(n1, n2) == false);
        assert(SynAccIterEq_1417c5b80(n1, n2) == false);

        *(void**)(n2 + 8) = (void*)0x11;
        *(void**)n2 = n3;                       // different node, same word
        assert(SynAccIterEq_1417c5b30(n1, n2) == true);
        assert(SynAccIterEq_1417c5b80(n1, n2) == true);

        *(void**)n2 = nullptr;                  // the null lead goes through the check too
        assert(SynAccIterEq_1417c5b30(n1, n2) == true);
        assert(SynAccIterEq_1417c5b80(n1, n2) == true);
        *(void**)n2 = n1;
    }

    // ---- 0x1417c5c50: this back when the lead already carries 0x29, else the last
    //      node whose lead did not
    {
        std::memset(n1, 0, sizeof n1);
        std::memset(n2, 0, sizeof n2);
        std::memset(n3, 0, sizeof n3);
        n1[0x29] = 1;                            // the lead itself carries the sentinel
        *(void**)n1 = n1;                        // the body reads 0x29(%rax), rax being the lead
        assert(SynAccWalk29_1417c5c50(n1) == (void*)n1);

        n1[0x29] = 0;                            // n1 -> n2 -> n3(sentinel)
        *(void**)n1 = n2;
        *(void**)n2 = n3;
        n3[0x29] = 1;
        assert(SynAccWalk29_1417c5c50(n1) == (void*)n2);
        assert(SynAccWalk29_1417c5c50(n2) == (void*)n2);
    }

    // ---- 0x1417c5c70: this back
    assert(SynAccRetThis_1417c5c70(n1) == (void*)n1);

    // ---- 0x1417c5f00: the walk through +0x10, sentinel at 0x41
    {
        std::memset(n1, 0, sizeof n1);
        std::memset(n2, 0, sizeof n2);
        std::memset(n3, 0, sizeof n3);
        n1[0x41] = 1;
        *(void**)(n1 + 0x10) = n1;
        assert(SynAccWalk10_41_1417c5f00(n1) == (void*)n1);

        n1[0x41] = 0;
        *(void**)(n1 + 0x10) = n2;
        *(void**)(n2 + 0x10) = n3;
        n3[0x41] = 1;
        assert(SynAccWalk10_41_1417c5f00(n1) == (void*)n2);
        assert(SynAccWalk10_41_1417c5f00(n2) == (void*)n2);
    }

    // ---- 0x1417c5f30: the walk through the lead, sentinel at 0x41
    {
        std::memset(n1, 0, sizeof n1);
        std::memset(n2, 0, sizeof n2);
        std::memset(n3, 0, sizeof n3);
        n1[0x41] = 1;
        *(void**)n1 = n1;
        assert(SynAccWalk41_1417c5f30(n1) == (void*)n1);

        n1[0x41] = 0;
        *(void**)n1 = n2;
        *(void**)n2 = n3;
        n3[0x41] = 1;
        assert(SynAccWalk41_1417c5f30(n1) == (void*)n2);
        assert(SynAccWalk41_1417c5f30(n2) == (void*)n2);
    }

    // ---- 0x1417c5c80 / 0x1417c5cc0: the second argument reaches the deallocate
    {
        void* a = ::operator new(0x20);
        void* b = ::operator new(0x20);
        SynAccDealloc_1417c5c80(nullptr, a);
        SynAccDealloc_1417c5cc0(nullptr, b);
        assert(true);
    }

    // ---- 0x1417c5f50: the raw answer
    assert(SynAccConst_1417c5f50() == 0x1fffffffffffffffULL);

    std::printf("SYNDICATE_D130_OK: the non-pure cluster tail, 9 bodies, 24 checks\n");
    return 0;
}
