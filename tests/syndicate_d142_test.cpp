// D142 — seven bodies from 0x1417c6e00: the iterator builder, the third +0x18 accessor, the
//   fourth 0x29 decrement, the lead deallocate, the 16-byte copy, the zeroed lead and the
//   0x0fffffffffffffff constant.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

namespace tq {
void* SynAccIterCtor_1417c6e00(void*, void*, void*);
void* SynAccCurrPlus18_1417c6e40(void*);
void SynAccDec29_1417c6e80(void*);
void SynAccFreeLead_1417c6f10(void*);
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char it[0x10];
    alignas(16) unsigned char N[0x60], R[0x60], L[0x60], holder[0x10];
    alignas(16) unsigned char dst[0x20], src[0x20];

    // ---- 0x1417c6e00: the node at +0x8, the holder's lead at +0x0
    {
        std::memset(it, 0xAB, sizeof it);
        std::memset(holder, 0, sizeof holder);
        *(void**)holder = L;
        assert(SynAccIterCtor_1417c6e00(it, N, holder) == (void*)it);
        assert(*(void**)it == (void*)L);              // mov (%rdi),%rax / mov %rax,(%rbx)
        assert(*(void**)(it + 8) == (void*)N);        // mov %rdx,0x8(%rcx)

        // the holder's own lead decides the iterator lead, whatever it holds
        std::memset(it, 0xAB, sizeof it);
        std::memset(holder, 0, sizeof holder);        // holder lead cleared
        assert(SynAccIterCtor_1417c6e00(it, R, holder) == (void*)it);
        assert(*(void**)it == nullptr);               // mov (%rdi),%rax with a cleared holder
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c6e40: lead's lead, its 0x30 slot, then +0x18 on the node
    {
        std::memset(it, 0, sizeof it);
        std::memset(N, 0, sizeof N); std::memset(L, 0, sizeof L); std::memset(R, 0, sizeof R);
        *(void**)it = N;
        *(void**)N = L;
        *(void**)(L + 0x30) = (void*)0x1234;
        *(void**)(it + 8) = R;
        assert(SynAccCurrPlus18_1417c6e40(it) == (void*)(R + 0x18));
    }

    // ---- 0x1417c6e80: the 0x29 decrement takes the 0x10 child when its lead is flagged
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
        SynAccDec29_1417c6e80(it);
        assert(*(void**)(it + 8) == (void*)R);
    }

    // ---- 0x1417c6f10: the lead is what goes to the deallocate
    {
        void* p = ::operator new(0x20);
        std::memset(N, 0, sizeof N);
        *(void**)N = p;
        SynAccFreeLead_1417c6f10(N);
        assert(*(void**)N == p);                      // the body only reads it
    }

    // ---- 0x1417c6f20: two qwords, this back
    {
        std::memset(src, 0x3C, sizeof src);
        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAccCopy16_1417c6f20(dst, src) == (void*)dst);
        assert(*(void**)(dst + 0) == *(void**)(src + 0));
        assert(*(void**)(dst + 8) == *(void**)(src + 8));
        assert(dst[0x10] == 0xAB);
    }

    // ---- 0x1417c6f40: the lead cleared, this back
    {
        std::memset(N, 0xAB, sizeof N);
        assert(SynAccZeroLead_1417c6f40(N) == (void*)N);
        assert(*(void**)N == nullptr);
        assert(N[8] == 0xAB);
    }

    // ---- 0x1417c6f50
    assert(SynAccConst_1417c6f50() == 0x0fffffffffffffffull);

    std::printf("SYNDICATE_D142_OK: seven bodies, 7 units, 17 checks\n");
    return 0;
}
