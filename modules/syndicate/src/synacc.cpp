// Syndicate.dll v6159 — the pure accessor cluster at 0x1417c5980..0x1417c5f80.
// Every body here is its own start read straight out of the binary: the small
// tail helpers around the range walkers, each of which only forms an address
// (lea 0xNN(%rcx)), loads the 0x30 slot, or copies the two qwords and the byte
// its argument is spent on. Nothing in the cluster calls out, so there is no
// seam and nothing to stub.
#include "modules/syndicate/src/synacc.h"

#include <cstring>

namespace tq {

// 0x1417c5980 — mov (%rdx),%eax / mov %eax,(%rcx) / mov (%r8),%rax /
//               mov %rax,0x8(%rcx) / ret rcx
void* SynAccIntPtr_1417c5980(void* pThis, const void* pSrc, void* pArg) {
    std::memcpy(pThis, pSrc, 4);
    void* pVal = *(void**)pArg;
    std::memcpy((unsigned char*)pThis + 8, &pVal, 8);
    return pThis;
}

// 0x1417c5990 — the same six bytes again: (%rdx) into (%rcx), (%r8) into +0x8
void* SynAccIntPtr_1417c5990(void* pThis, const void* pSrc, void* pArg) {
    std::memcpy(pThis, pSrc, 4);
    void* pVal = *(void**)pArg;
    std::memcpy((unsigned char*)pThis + 8, &pVal, 8);
    return pThis;
}

// 0x1417c59a0 — movq $0x0,(%rcx) / ret rcx
void* SynAccZeroQword_1417c59a0(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c59b0 — mov %rcx,%rax / ret   (this back, unchanged)
void* SynAccRetThis_1417c59b0(void* pThis) { return pThis; }

// 0x1417c59c0 — lea 0x29(%rcx),%rax / ret
void* SynAccPlus29_1417c59c0(void* pThis) { return (unsigned char*)pThis + 0x29; }

// 0x1417c59d0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c59d0(void* pThis) { return pThis; }

// 0x1417c59e0 — lea 0x10(%rcx),%rax / ret
void* SynAccPlus10_1417c59e0(void* pThis) { return (unsigned char*)pThis + 0x10; }

// 0x1417c59f0 — mov 0x30(%rcx),%rax / ret   (the slot, not its address)
void* SynAccSlot30_1417c59f0(void* pThis) { return *(void**)((unsigned char*)pThis + 0x30); }

// 0x1417c5a00 — mov 0x30(%rcx),%rax / add $0x10,%rax / ret
void* SynAccSlot30Plus10_1417c5a00(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 0x10;
}

// 0x1417c5a10 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5a10(void* pThis) { return pThis; }

// 0x1417c5a20 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5a20(void* pThis) { return pThis; }

// 0x1417c5a30 — lea 0x41(%rcx),%rax / ret
void* SynAccPlus41_1417c5a30(void* pThis) { return (unsigned char*)pThis + 0x41; }

// 0x1417c5a40 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5a40(void* pThis) { return pThis; }

// 0x1417c5a50 — lea 0x10(%rcx),%rax / ret
void* SynAccPlus10_1417c5a50(void* pThis) { return (unsigned char*)pThis + 0x10; }

// 0x1417c5a60 — mov 0x30(%rcx),%rax / ret
void* SynAccSlot30_1417c5a60(void* pThis) { return *(void**)((unsigned char*)pThis + 0x30); }

// 0x1417c5a70 — mov 0x30(%rcx),%rax / add $0x10,%rax / ret
void* SynAccSlot30Plus10_1417c5a70(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 0x10;
}

// 0x1417c5a80 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5a80(void* pThis) { return pThis; }

// 0x1417c5a90 — lea 0x21(%rcx),%rax / ret
void* SynAccPlus21_1417c5a90(void* pThis) { return (unsigned char*)pThis + 0x21; }

// 0x1417c5aa0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5aa0(void* pThis) { return pThis; }

// 0x1417c5ab0 — lea 0x10(%rcx),%rax / ret
void* SynAccPlus10_1417c5ab0(void* pThis) { return (unsigned char*)pThis + 0x10; }

// 0x1417c5ac0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5ac0(void* pThis) { return pThis; }

// 0x1417c5ad0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5ad0(void* pThis) { return pThis; }

// 0x1417c5ae0 — mov (%rdx),%rax / mov %rax,(%rcx) / mov 0x8(%rdx),%rax /
//               mov %rax,0x8(%rcx) / movzbl (%r8),%eax / mov %al,0x10(%rcx) / ret rcx
void* SynAccTwoQwordsByte_1417c5ae0(void* pThis, const void* pSrc, void* pArg) {
    std::memcpy(pThis, pSrc, 0x10);
    *(unsigned char*)((unsigned char*)pThis + 0x10) = *(const unsigned char*)pArg;
    return pThis;
}

// 0x1417c5b00 — mov 0x8(%rcx),%rax / ret
void* SynAccSlot8_1417c5b00(void* pThis) { return *(void**)((unsigned char*)pThis + 8); }

// 0x1417c5b10 — the 0x1417c5ae0 body again
void* SynAccTwoQwordsByte_1417c5b10(void* pThis, const void* pSrc, void* pArg) {
    std::memcpy(pThis, pSrc, 0x10);
    *(unsigned char*)((unsigned char*)pThis + 0x10) = *(const unsigned char*)pArg;
    return pThis;
}

// 0x1417c5b70 — mov 0x8(%rcx),%rax / ret
void* SynAccSlot8_1417c5b70(void* pThis) { return *(void**)((unsigned char*)pThis + 8); }

// 0x1417c5bc0 — mov 0x8(%rcx),%rax / ret
void* SynAccSlot8_1417c5bc0(void* pThis) { return *(void**)((unsigned char*)pThis + 8); }

// 0x1417c5bd0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5bd0(void* pThis) { return pThis; }

// 0x1417c5c20 — lea 0x28(%rcx),%rax / ret
void* SynAccPlus28_1417c5c20(void* pThis) { return (unsigned char*)pThis + 0x28; }

// 0x1417c5c30 — lea 0x8(%rcx),%rax / ret
void* SynAccPlus8_1417c5c30(void* pThis) { return (unsigned char*)pThis + 8; }

// 0x1417c5c40 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c5c40(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c5c90 — lea 0x40(%rcx),%rax / ret
void* SynAccPlus40_1417c5c90(void* pThis) { return (unsigned char*)pThis + 0x40; }

// 0x1417c5ca0 — lea 0x8(%rcx),%rax / ret
void* SynAccPlus8_1417c5ca0(void* pThis) { return (unsigned char*)pThis + 8; }

// 0x1417c5cb0 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c5cb0(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c5cd0 — lea 0x20(%rcx),%rax / ret
void* SynAccPlus20_1417c5cd0(void* pThis) { return (unsigned char*)pThis + 0x20; }

// 0x1417c5ce0 — lea 0x8(%rcx),%rax / ret
void* SynAccPlus8_1417c5ce0(void* pThis) { return (unsigned char*)pThis + 8; }

// 0x1417c5cf0 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c5cf0(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c5d00 — mov 0x30(%rcx),%rax / ret
void* SynAccSlot30_1417c5d00(void* pThis) { return *(void**)((unsigned char*)pThis + 0x30); }

// 0x1417c5dd0 — mov 0x30(%rcx),%rax / add $0x8,%rax / ret
void* SynAccSlot30Plus8_1417c5dd0(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 8;
}

// 0x1417c5de0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5de0(void* pThis) { return pThis; }

// 0x1417c5df0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c5df0(void* pThis) { return pThis; }

// 0x1417c5e60 — mov (%rdx),%rax / mov %rax,(%rcx) / mov 0x8(%rdx),%rax /
//               mov %rax,0x8(%rcx) / ret rcx
void* SynAccTwoQwords_1417c5e60(void* pThis, const void* pSrc) {
    std::memcpy(pThis, pSrc, 0x10);
    return pThis;
}

// 0x1417c5ef0 — movabs $0xfffffffffffffff,%rax / ret
uint64_t SynAccConst_1417c5ef0() { return 0x0fffffffffffffffULL; }

}  // namespace tq
