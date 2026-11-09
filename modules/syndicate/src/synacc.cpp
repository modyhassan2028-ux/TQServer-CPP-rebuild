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

// 0x1417c5e50 — mov 0x8(%rcx),%rax / ret
void* SynAccSlot8_1417c5e50(void* pThis) { return *(void**)((unsigned char*)pThis + 8); }

// 0x1417c5e80 — mov (%rdx),%rax / mov %rax,(%rcx) / mov 0x8(%rdx),%rax /
//               mov %rax,0x8(%rcx) / movzbl (%r8),%eax / mov %al,0x10(%rcx) / ret rcx
void* SynAccTwoQwordsByte_1417c5e80(void* pThis, const void* pSrc, void* pArg) {
    std::memcpy(pThis, pSrc, 0x10);
    *(unsigned char*)((unsigned char*)pThis + 0x10) = *(const unsigned char*)pArg;
    return pThis;
}

// 0x1417c5ea0 — movq $0x0,(%rcx) / ret rcx
void* SynAccZeroQword_1417c5ea0(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c5eb0 — movabs $0x666666666666666,%rax / ret
uint64_t SynAccConst_1417c5eb0() { return 0x0666666666666666ULL; }

// 0x1417c5ec0 — mov 0x10(%rcx),%rax / cmpb $0x0,0x29(%rax) / jne 0x1417c5edd /
//               mov %rax,%rcx / mov 0x10(%rax),%rax / cmpb $0x0,0x29(%rax) / je back
void* SynAccWalk10_29_1417c5ec0(void* pThis) {
    unsigned char* pRet = (unsigned char*)pThis;                        // rcx
    unsigned char* pNode = *(unsigned char**)((unsigned char*)pThis + 0x10);  // mov 0x10(%rcx),%rax
    if (*(unsigned char*)(pNode + 0x29) == 0) {                         // cmpb $0x0,0x29(%rax) / jne
        for (;;) {
            pRet = pNode;                                               // mov %rax,%rcx
            pNode = *(unsigned char**)(pNode + 0x10);                   // mov 0x10(%rax),%rax
            if (*(unsigned char*)(pNode + 0x29) != 0) break;             // cmpb $0x0,0x29(%rax) / je back
        }
    }
    return pRet;                                                        // mov %rcx,%rax
}

// 0x1417c60e0 — lea 0x28(%rcx),%rax / ret
void* SynAccPlus28_1417c60e0(void* pThis) { return (unsigned char*)pThis + 0x28; }

// 0x1417c60f0 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c60f0(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c6100 — the rotate that moves the 0x10 side up:
//   r8 = 0x10(%rdx) / rax = (%r8) / 0x10(%rdx) = rax / rax = (%r8) /
//   if 0x29(%rax)==0 : 0x8(%rax) = rdx / rax = 0x8(%rdx) / 0x8(%r8) = rax /
//   rax = 0x30(%rcx) / if rdx == 0x8(%rax) : 0x8(%rax)=r8, (%r8)=rdx, 0x8(%rdx)=r8 /
//   else rax = 0x8(%rdx) / if rdx == (%rax) : (%rax)=r8, (%r8)=rdx, 0x8(%rdx)=r8 /
//   else 0x10(%rax)=r8, (%r8)=rdx, 0x8(%rdx)=r8
void* SynAccRotRight_1417c6100(void* pTree, void* pNode) {
    unsigned char* s = (unsigned char*)pTree;             // rcx
    unsigned char* x = (unsigned char*)pNode;             // rdx
    unsigned char* y = *(unsigned char**)(x + 0x10);      // mov 0x10(%rdx),%r8
    *(void**)(x + 0x10) = *(void**)(y);                   // mov (%r8),%rax / mov %rax,0x10(%rdx)
    unsigned char* l = *(unsigned char**)(y);             // mov (%r8),%rax
    if (*(unsigned char*)(l + 0x29) == 0)                 // cmpb $0x0,0x29(%rax) / jne
        *(void**)(l + 8) = x;                             // mov %rdx,0x8(%rax)
    *(void**)(y + 8) = *(void**)(x + 8);                  // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    unsigned char* head = *(unsigned char**)(s + 0x30);   // mov 0x30(%rcx),%rax
    if (x == *(unsigned char**)(head + 8)) {              // cmp 0x8(%rax),%rdx / jne
        *(void**)(head + 8) = y;                          // mov %r8,0x8(%rax)
        *(void**)(y) = x;                                 // mov %rdx,(%r8)
        *(void**)(x + 8) = y;                             // mov %r8,0x8(%rdx)
        return pNode;
    }
    unsigned char* p = *(unsigned char**)(x + 8);         // mov 0x8(%rdx),%rax
    if (x == *(unsigned char**)p) {                       // cmp (%rax),%rdx / jne
        *(void**)(p) = y;                                 // mov %r8,(%rax)
        *(void**)(y) = x;                                 // mov %rdx,(%r8)
        *(void**)(x + 8) = y;                             // mov %r8,0x8(%rdx)
        return pNode;
    }
    *(void**)(p + 0x10) = y;                              // mov %r8,0x10(%rax)
    *(void**)(y) = x;                                     // mov %rdx,(%r8)
    *(void**)(x + 8) = y;                                 // mov %r8,0x8(%rdx)
    return pNode;
}

// 0x1417c6160 — mov 0x30(%rcx),%rax / add $0x10,%rax / ret
void* SynAccSlot30Plus10_1417c6160(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 0x10;
}

// 0x1417c6170 — the mirror: the 0x0 side moves up.
void* SynAccRotLeft_1417c6170(void* pTree, void* pNode) {
    unsigned char* s = (unsigned char*)pTree;             // rcx
    unsigned char* x = (unsigned char*)pNode;             // rdx
    unsigned char* y = *(unsigned char**)(x);             // mov (%rdx),%r8
    *(void**)(x) = *(void**)(y + 0x10);                   // mov 0x10(%r8),%rax / mov %rax,(%rdx)
    unsigned char* r = *(unsigned char**)(y + 0x10);      // mov 0x10(%r8),%rax
    if (*(unsigned char*)(r + 0x29) == 0)                 // cmpb $0x0,0x29(%rax) / jne
        *(void**)(r + 8) = x;                             // mov %rdx,0x8(%rax)
    *(void**)(y + 8) = *(void**)(x + 8);                  // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    unsigned char* head = *(unsigned char**)(s + 0x30);   // mov 0x30(%rcx),%rax
    if (x == *(unsigned char**)(head + 8)) {              // cmp 0x8(%rax),%rdx / jne
        *(void**)(head + 8) = y;
        *(void**)(y + 0x10) = x;                          // mov %rdx,0x10(%r8)
        *(void**)(x + 8) = y;
        return pNode;
    }
    unsigned char* p = *(unsigned char**)(x + 8);         // mov 0x8(%rdx),%rax
    if (x == *(unsigned char**)(p + 0x10)) {              // cmp 0x10(%rax),%rdx / jne
        *(void**)(p + 0x10) = y;                          // mov %r8,0x10(%rax)
        *(void**)(y + 0x10) = x;
        *(void**)(x + 8) = y;
        return pNode;
    }
    *(void**)(p) = y;                                     // mov %r8,(%rax)
    *(void**)(y + 0x10) = x;                              // mov %rdx,0x10(%r8)
    *(void**)(x + 8) = y;
    return pNode;
}

// 0x1417c6250 — 0x10 bytes from rdx into the lead, 0x10 from r8 into +0x10, this back.
void* SynAccCopy32_1417c6250(void* pThis, const void* pA, const void* pB) {
    std::memcpy(pThis, pA, 0x10);
    std::memcpy((unsigned char*)pThis + 0x10, pB, 0x10);
    return pThis;
}

// 0x1417c6280 — the same four qword stores, its own start.
void* SynAccCopy32_1417c6280(void* pThis, const void* pA, const void* pB) {
    std::memcpy(pThis, pA, 0x10);
    std::memcpy((unsigned char*)pThis + 0x10, pB, 0x10);
    return pThis;
}

// 0x1417c62b0 — the 0x29-byte node built around two qwords of the pair in the fifth
// argument and the byte of the sixth; the sentinel at +0x29 is cleared last.
void* SynAccCtor_1417c62b0(void* pThis, void* a, void* b, void* c, const void* pPair,
                           unsigned char uFlag) {
    unsigned char* s = (unsigned char*)pThis;
    *(void**)(s) = a;                                     // mov %rdx,(%rcx)
    *(void**)(s + 8) = b;                                 // mov %r8,0x8(%rcx)
    *(void**)(s + 0x10) = c;                              // mov %r9,0x10(%rcx)
    *(void**)(s + 0x18) = *(void**)pPair;                 // mov (%rdx),%rax / mov %rax,0x18(%rcx)
    *(unsigned char*)(s + 0x29) = 0;                      // movb $0x0,0x29(%rcx)
    *(void**)(s + 0x20) = *(void**)((const unsigned char*)pPair + 8);  // mov 0x8(%rdx),%rax / mov %rax,0x20(%rcx)
    *(unsigned char*)(s + 0x28) = uFlag;                  // movzbl 0x30(%rsp),%eax / mov %al,0x28(%rcx)
    return pThis;
}

// 0x1417c6330 — the same build in the order the bytes take it: the pair first, then the
// byte at +0x20, then the sentinel at +0x21.
void* SynAccCtor_1417c6330(void* pThis, void* a, void* b, void* c, const void* pPair,
                           unsigned char uFlag) {
    unsigned char* s = (unsigned char*)pThis;
    *(void**)(s) = a;                                     // mov %rdx,(%rcx)
    *(void**)(s + 8) = b;                                 // mov %r8,0x8(%rcx)
    *(void**)(s + 0x10) = c;                              // mov %r9,0x10(%rcx)
    *(unsigned char*)(s + 0x20) = uFlag;                  // movzbl 0x30(%rsp),%eax / mov %al,0x20(%rcx)
    *(void**)(s + 0x18) = *(void**)pPair;                 // mov (%rax),%rdx / mov %rdx,0x18(%rcx)
    *(unsigned char*)(s + 0x21) = 0;                      // movb $0x0,0x21(%rcx)
    return pThis;
}

// 0x1417c6360 — movq $0x0,(%rcx) / ret rcx
void* SynAccZeroQword_1417c6360(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c6370 — mov 0x10(%rcx),%rax / cmpb $0x0,0x21(%rax) / jne out /
//               mov %rax,%rcx / mov 0x10(%rax),%rax / cmpb $0x0,0x21(%rax) / je back
void* SynAccWalk10_21_1417c6370(void* pThis) {
    unsigned char* pRet = (unsigned char*)pThis;          // rcx
    unsigned char* pNode = *(unsigned char**)((unsigned char*)pThis + 0x10);
    if (*(unsigned char*)(pNode + 0x21) == 0) {
        for (;;) {
            pRet = pNode;                                 // mov %rax,%rcx
            pNode = *(unsigned char**)(pNode + 0x10);     // mov 0x10(%rax),%rax
            if (*(unsigned char*)(pNode + 0x21) != 0) break;
        }
    }
    return pRet;                                          // mov %rcx,%rax
}

// 0x1417c63a0 — the same walk through the lead instead of +0x10.
void* SynAccWalk21_1417c63a0(void* pThis) {
    unsigned char* pRet = (unsigned char*)pThis;
    unsigned char* pNode = *(unsigned char**)pThis;       // mov (%rcx),%rax
    if (*(unsigned char*)(pNode + 0x21) == 0) {
        for (;;) {
            pRet = pNode;
            pNode = *(unsigned char**)pNode;              // mov (%rax),%rax
            if (*(unsigned char*)(pNode + 0x21) != 0) break;
        }
    }
    return pRet;
}

// 0x1417c6450 — mov 0x10(%rcx),%rax / cmpb $0x0,0x29(%rax) / jne out /
//               mov %rax,%rcx / mov 0x10(%rax),%rax / cmpb / je back
void* SynAccWalk10_29_1417c6450(void* pThis) {
    unsigned char* pRet = (unsigned char*)pThis;                       // rcx
    unsigned char* pNode = *(unsigned char**)((unsigned char*)pThis + 0x10);
    if (*(unsigned char*)(pNode + 0x29) == 0) {
        for (;;) {
            pRet = pNode;                                              // mov %rax,%rcx
            pNode = *(unsigned char**)(pNode + 0x10);                  // mov 0x10(%rax),%rax
            if (*(unsigned char*)(pNode + 0x29) != 0) break;
        }
    }
    return pRet;
}

// 0x1417c6480 — the same walk through the lead
void* SynAccWalk29_1417c6480(void* pThis) {
    unsigned char* pRet = (unsigned char*)pThis;
    unsigned char* pNode = *(unsigned char**)pThis;                    // mov (%rcx),%rax
    if (*(unsigned char*)(pNode + 0x29) == 0) {
        for (;;) {
            pRet = pNode;
            pNode = *(unsigned char**)pNode;                           // mov (%rax),%rax
            if (*(unsigned char*)(pNode + 0x29) != 0) break;
        }
    }
    return pRet;
}

// 0x1417c64a0 — movabs $0xfffffffffffffff,%rax / ret
uint64_t SynAccConst_1417c64a0() { return 0x0fffffffffffffffULL; }

// 0x1417c6550 — the 0x29 node build again, its own start, the pair the fifth argument
// and the byte the sixth: (%rdx) into +0x18, 0x8(%rdx) into +0x20, the sentinel cleared
// between the two stores exactly where the bytes put it.
void* SynAccCtor_1417c6550(void* pThis, void* a, void* b, void* c, const void* pPair,
                           unsigned char uFlag) {
    unsigned char* s = (unsigned char*)pThis;
    *(void**)(s) = a;                                     // mov %rdx,(%rcx)
    *(void**)(s + 8) = b;                                 // mov %r8,0x8(%rcx)
    *(void**)(s + 0x10) = c;                              // mov %r9,0x10(%rcx)
    *(void**)(s + 0x18) = *(void**)pPair;                 // mov (%rdx),%rax / mov %rax,0x18(%rcx)
    *(unsigned char*)(s + 0x29) = 0;                      // movb $0x0,0x29(%rcx)
    *(void**)(s + 0x20) = *(void**)((const unsigned char*)pPair + 8);
    *(unsigned char*)(s + 0x28) = uFlag;                  // movzbl 0x30(%rsp),%eax / mov %al,0x28(%rcx)
    return pThis;
}

// 0x1417c66a0 — mov (%rdx),%eax / mov %eax,(%rcx) / mov 0x4(%rdx),%eax / mov %eax,0x4(%rcx)
// The two halves are copied as words, not as one qword, so nothing is assumed about the
// four bytes between them.
void* SynAccCopy8_1417c66a0(void* pThis, const void* pSrc) {
    std::memcpy(pThis, pSrc, 4);                          // mov (%rdx),%eax / mov %eax,(%rcx)
    std::memcpy((unsigned char*)pThis + 4, (const unsigned char*)pSrc + 4, 4);
    return pThis;                                         // mov %rcx,%rax
}

// 0x1417c66b0 — ret $0x0
void SynAccNoop_1417c66b0() {}
// 0x1417c66c0 — ret $0x0
void SynAccNoop_1417c66c0() {}
// 0x1417c66d0 — ret $0x0
void SynAccNoop_1417c66d0() {}
// 0x1417c66e0 — ret $0x0
void SynAccNoop_1417c66e0() {}
// 0x1417c66f0 — ret $0x0
void SynAccNoop_1417c66f0() {}

// 0x1417c6700 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6700(void* pThis) { return pThis; }

// 0x1417c6780 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6780(void* pThis) { return pThis; }

// 0x1417c6800 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6800(void* pThis) { return pThis; }

// 0x1417c6880 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6880(void* pThis) { return pThis; }

// 0x1417c6890 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6890(void* pThis) { return pThis; }

// 0x1417c68a0 — test %rcx,%rcx / je out / mov (%rdx),%rax / mov %rax,(%rcx) / repz ret
// A null destination writes nothing; the body answers nothing.
void SynAccAssign1_1417c68a0(void* pDst, const void* pSrc) {
    if (pDst != nullptr)                                   // test %rcx,%rcx / je
        *(void**)pDst = *(void**)pSrc;                     // mov (%rdx),%rax / mov %rax,(%rcx)
}

// 0x1417c68b0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c68b0(void* pThis) { return pThis; }

// 0x1417c68c0 — the same guarded single-qword store, its own start
void SynAccAssign1_1417c68c0(void* pDst, const void* pSrc) {
    if (pDst != nullptr)
        *(void**)pDst = *(void**)pSrc;
}

// 0x1417c68d0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c68d0(void* pThis) { return pThis; }

// 0x1417c68e0 — ret $0x0
void SynAccNoop_1417c68e0() {}

// 0x1417c68f0 — the same guarded single-qword store again
void SynAccAssign1_1417c68f0(void* pDst, const void* pSrc) {
    if (pDst != nullptr)
        *(void**)pDst = *(void**)pSrc;
}

// 0x1417c6900 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6900(void* pThis) { return pThis; }

// 0x1417c6980 — ret $0x0
void SynAccNoop_1417c6980() {}

// 0x1417c6990 — and once more, its own start
void SynAccAssign1_1417c6990(void* pDst, const void* pSrc) {
    if (pDst != nullptr)
        *(void**)pDst = *(void**)pSrc;
}

// 0x1417c69a0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c69a0(void* pThis) { return pThis; }

// 0x1417c69b0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c69b0(void* pThis) { return pThis; }

// 0x1417c69c0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c69c0(void* pThis) { return pThis; }

// 0x1417c69d0 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c69d0(void* pThis) { return pThis; }

// The seams the element-count allocators run through. Null by default, exactly like the
// rest of the port's seams: the bodies test before they call.
void (*g_pfnSynErrCtor_1418233e8)(void*, void*) = nullptr;      // 0x1418233e8
void (*g_pfnSynThrow_1417f3154)(void*, const void*) = nullptr;  // 0x1417f3154
void* (*g_pfnSynNew_1417f3166)(uint64_t) = nullptr;             // 0x1417f3166

// 0x1417c6710 — the 0x30-byte element allocator:
//   movq $0xfffffffffffffffe,0x20(%rsp) / test %rcx,%rcx / je good /
//   xor %edx,%edx / or $-1,%rax / div %rcx / cmp $0x30,%rax / jae good /
//   xor %ecx,%ecx / mov %rcx,0x50(%rsp) / lea 0x50(%rsp),%rdx / lea 0x28(%rsp),%rcx /
//   call *0x1418233e8 / lea 0x141824c40,%rax / mov %rax,0x28(%rsp) /
//   lea 0x141881df0,%rdx / lea 0x28(%rsp),%rcx / call 0x1417f3154 /
//   good: lea (%rcx,%rcx,2),%rcx / shl $0x4,%rcx / jmp 0x1417f3166
void* SynAccNew48_1417c6710(uint64_t nElems) {
    volatile int64_t sentinel = -2;                 // movq $0xfffffffffffffffe,0x20(%rsp)
    (void)sentinel;
    if (nElems != 0) {                              // test %rcx,%rcx / je good
        uint64_t q = 0xFFFFFFFFFFFFFFFFull / nElems; // or $-1,%rax / xor %edx,%edx / div %rcx
        if (q < 0x30) {                             // cmp $0x30,%rax / jae good
            unsigned char obj[0x40] = {};
            uint64_t empty = 0;                     // xor %ecx,%ecx / mov %rcx,0x50(%rsp)
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(obj, &empty);        // call *0x1418233e8
            *(const void**)obj = (const void*)(uintptr_t)0x141824c40ULL;  // the vtable store
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881df0ULL);
        }
    }
    uint64_t cb = nElems * 3 * 16;                  // lea (%rcx,%rcx,2) / shl $0x4
    if (g_pfnSynNew_1417f3166 != nullptr)
        return g_pfnSynNew_1417f3166(cb);           // jmp 0x1417f3166
    return nullptr;
}

// 0x1417c6790 — the 0x48-byte element allocator: the same frame, `cmp $0x48,%rax`,
//   `lea (%rcx,%rcx,8),%rcx / shl $0x3,%rcx`.
void* SynAccNew72_1417c6790(uint64_t nElems) {
    volatile int64_t sentinel = -2;
    (void)sentinel;
    if (nElems != 0) {
        uint64_t q = 0xFFFFFFFFFFFFFFFFull / nElems;
        if (q < 0x48) {
            unsigned char obj[0x40] = {};
            uint64_t empty = 0;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(obj, &empty);
            *(const void**)obj = (const void*)(uintptr_t)0x141824c40ULL;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881df0ULL);
        }
    }
    uint64_t cb = nElems * 9 * 8;                   // lea (%rcx,%rcx,8) / shl $0x3
    if (g_pfnSynNew_1417f3166 != nullptr)
        return g_pfnSynNew_1417f3166(cb);
    return nullptr;
}

// 0x1417c6810 — the 0x28-byte element allocator: `cmp $0x28,%rax`,
//   `lea (%rcx,%rcx,4),%rcx / shl $0x3,%rcx`.
void* SynAccNew40_1417c6810(uint64_t nElems) {
    volatile int64_t sentinel = -2;
    (void)sentinel;
    if (nElems != 0) {
        uint64_t q = 0xFFFFFFFFFFFFFFFFull / nElems;
        if (q < 0x28) {
            unsigned char obj[0x40] = {};
            uint64_t empty = 0;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(obj, &empty);
            *(const void**)obj = (const void*)(uintptr_t)0x141824c40ULL;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881df0ULL);
        }
    }
    uint64_t cb = nElems * 5 * 8;                   // lea (%rcx,%rcx,4) / shl $0x3
    if (g_pfnSynNew_1417f3166 != nullptr)
        return g_pfnSynNew_1417f3166(cb);
    return nullptr;
}

// 0x1417c6910 — the 0x30-byte element allocator again, its own start: the body is
//   byte for byte the one at 0x1417c6710, `cmp $0x30,%rax` and the 3*16 size included.
void* SynAccNew48_1417c6910(uint64_t nElems) {
    volatile int64_t sentinel = -2;
    (void)sentinel;
    if (nElems != 0) {
        uint64_t q = 0xFFFFFFFFFFFFFFFFull / nElems;
        if (q < 0x30) {
            unsigned char obj[0x40] = {};
            uint64_t empty = 0;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(obj, &empty);
            *(const void**)obj = (const void*)(uintptr_t)0x141824c40ULL;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881df0ULL);
        }
    }
    uint64_t cb = nElems * 3 * 16;
    if (g_pfnSynNew_1417f3166 != nullptr)
        return g_pfnSynNew_1417f3166(cb);
    return nullptr;
}

// 0x1417c6a10 — mov (%rdx),%eax / mov %eax,(%rcx) / mov (%r8),%eax /
//               mov %eax,0x4(%rcx) / mov %rcx,%rax / ret
// Two words from two different arguments, the second landing at +0x4.
void* SynAccCopy2Ints_1417c6a10(void* pThis, const void* pA, const void* pB) {
    std::memcpy(pThis, pA, 4);                                  // mov (%rdx),%eax / mov %eax,(%rcx)
    std::memcpy((unsigned char*)pThis + 4, pB, 4);              // mov (%r8),%eax / mov %eax,0x4(%rcx)
    return pThis;                                               // mov %rcx,%rax
}

// 0x1417c6a20 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6a20(void* pThis) { return pThis; }

// 0x1417c6a30 — mov %rcx,%rax / ret
void* SynAccRetThis_1417c6a30(void* pThis) { return pThis; }

// 0x1417c6a40 — mov (%rcx),%rax / mov %rax,(%rdx) / mov 0x8(%rcx),%rax /
//               mov %rax,0x8(%rdx) / mov %rdx,%rax / ret
// The source is the first argument here and the answer is the second, unlike the
// neighbouring bodies that build into rcx.
void* SynAccCopy16To_1417c6a40(void* pSrc, void* pDst) {
    std::memcpy(pDst, pSrc, 0x10);                              // the two qword stores
    return pDst;                                                // mov %rdx,%rax
}

// The assertion and forward seams. Null by default: every body checks first, so an unset
// seam removes nothing but the side effect.
void (*g_pfnSynAssert_141823030)(const void*, const void*, const void*, const void*,
                                 uint32_t) = nullptr;          // 0x141823030
int (*g_pfnSynPrep_141785dc0)(void*) = nullptr;                // 0x141785dc0
void* (*g_pfnSynPrep_14178c8e0)(void*, uint32_t) = nullptr;    // 0x14178c8e0
void (*g_pfnSynFwd_1417c5640)(void*, void*, void*, int, unsigned char) = nullptr;  // 0x1417c5640

// 0x1417c6a60 — the checked forwarder:
//   movzbl %r9b,%esi / mov %r8,%rbx / mov %rdx,%rdi / mov %rcx,%r12 /
//   test %rdx,%rdx / jne 0x1417c6abc / line 0x32a, 0x141824ca8, 0x14182664c,
//   0x141836e5c, 0x141839fe0 / call *0x141823030 / jmp end /
//   test %rbx,%rbx / jne 0x1417c6aed / line 0x32b with 0x141831610 in the third slot /
//   mov %rbx,%rcx / call 0x141785dc0 / mov %eax,%r9d / mov %sil,0x20(%rsp) /
//   mov %rbx,%r8 / mov %rdi,%rdx / mov %r12,%rcx / call 0x1417c5640
// The two failing branches differ in one pointer only: the text 0x141836e5c for the second
// argument, 0x141831610 for the third.
void* SynAccChecked2_1417c6a60(void* pThis, void* a2, void* a3, unsigned char uFlag) {
    volatile int64_t sentinel = -2;                  // movq $0xfffffffffffffffe,0x30(%rsp)
    (void)sentinel;
    if (a2 == nullptr) {                             // test %rdx,%rdx / jne
        if (g_pfnSynAssert_141823030 != nullptr)
            g_pfnSynAssert_141823030((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x14182664cULL,
                                     (const void*)(uintptr_t)0x141836e5cULL,
                                     (const void*)(uintptr_t)0x141839fe0ULL, 0x32a);
        return pThis;                                // jmp 0x1417c6b0c
    }
    if (a3 == nullptr) {                             // test %rbx,%rbx / jne
        if (g_pfnSynAssert_141823030 != nullptr)
            g_pfnSynAssert_141823030((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x14182664cULL,
                                     (const void*)(uintptr_t)0x141831610ULL,
                                     (const void*)(uintptr_t)0x141839fe0ULL, 0x32b);
        return pThis;                                // jmp 0x1417c6b0c
    }
    int nFrom = 0;                                   // mov %eax,%r9d
    if (g_pfnSynPrep_141785dc0 != nullptr)
        nFrom = g_pfnSynPrep_141785dc0(a3);          // mov %rbx,%rcx / call 0x141785dc0
    if (g_pfnSynFwd_1417c5640 != nullptr)            // mov %sil,0x20(%rsp) is the stack flag
        g_pfnSynFwd_1417c5640(pThis, a2, a3, nFrom, uFlag);
    return pThis;
}

// 0x1417c6b30 — the same frame, one argument fewer checked and a slot read first:
//   movzbl %r9b,%r12d / mov %r8d,%edi / test %rdx,%rdx / jne 0x1417c6b8c /
//   line 0x339 with 0x141836e5c / call *0x141823030 / jmp end /
//   mov %r8d,%edx / mov 0x90(%rcx),%rcx / call 0x14178c8e0 / mov %r12b,0x20(%rsp) /
//   mov %edi,%r9d / mov %rax,%r8 / mov %rbx,%rdx / mov %rsi,%rcx / call 0x1417c5640
void* SynAccChecked3_1417c6b30(void* pThis, void* a2, uint32_t uA3, unsigned char uFlag) {
    volatile int64_t sentinel = -2;
    (void)sentinel;
    if (a2 == nullptr) {                             // test %rdx,%rdx / jne
        if (g_pfnSynAssert_141823030 != nullptr)
            g_pfnSynAssert_141823030((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x14182664cULL,
                                     (const void*)(uintptr_t)0x141836e5cULL,
                                     (const void*)(uintptr_t)0x141839fe0ULL, 0x339);
        return pThis;                                // jmp 0x1417c6bb2
    }
    void* pFrom = nullptr;                           // mov %rax,%r8
    if (g_pfnSynPrep_14178c8e0 != nullptr)           // mov 0x90(%rcx),%rcx / call 0x14178c8e0
        pFrom = g_pfnSynPrep_14178c8e0(*(void**)((unsigned char*)pThis + 0x90), uA3);
    if (g_pfnSynFwd_1417c5640 != nullptr)            // mov %r12b,0x20(%rsp) is the stack flag
        g_pfnSynFwd_1417c5640(pThis, a2, pFrom, (int)uA3, uFlag);
    return pThis;
}

// The tail slot 0x1417c69e0 jumps through. Its entry in the image is an unresolved RVA
// (0x1628a6), so nothing is claimed about what sits behind it.
void* (*g_pfnSynTail_141823290)(void*) = nullptr;              // 0x141823290

// 0x1417c69e0 — mov %rcx,0x8(%rsp) / sub $0x38,%rsp /
//               movq $0xfffffffffffffffe,0x20(%rsp) / add $0x18,%rcx /
//               add $0x38,%rsp / jmp *0x141823290
// The frame is torn down before the jump, so this is a true tail call on `this + 0x18`.
void* SynAccTail18_1417c69e0(void* pThis) {
    volatile int64_t sentinel = -2;                            // movq $0xfffffffffffffffe,0x20(%rsp)
    (void)sentinel;
    void* pArg = (unsigned char*)pThis + 0x18;                 // add $0x18,%rcx
    if (g_pfnSynTail_141823290 != nullptr)
        return g_pfnSynTail_141823290(pArg);                   // jmp *0x141823290
    return nullptr;
}

// The boolean test and the virtual slot 0x1417c6bd0 goes through.
bool (*g_pfnSynPrepBool_141787300)(void*) = nullptr;                        // 0x141787300
void (*g_pfnSynVirt_1417c6bd0)(void*, void*, int, unsigned char) = nullptr; // call *0x1a0(%r9)

// 0x1417c6bd0 — the checked forwarder that also dispatches:
//   mov %r9d,%esi / mov %r8,%rbp / mov %rdx,%rbx / mov %rcx,%rdi /
//   test %rdx,%rdx / jne 0x1417c6c23 /
//   line 0x39c with 0x141824ca8, 0x141827b98, 0x141831610, 0x141839fe0 /
//   call *0x141823030 / xor %al,%al / jmp end /
//   mov %rdx,%rcx / call 0x141787300 / test %al,%al / je 0x1417c6c5e /
//   mov %rbx,%rcx / call 0x141785dc0 / mov 0x88(%rdi),%rcx / mov %esi,%r8d /
//   mov (%rcx),%r9 / mov %eax,%edx / call *0x1a0(%r9) /
//   xor %r9d,%r9d / mov %rbx,%r8 / mov %rbp,%rdx / mov %rdi,%rcx / call 0x1417c6a60 /
//   end: mov $0x1,%al
// The failing branch is the only one that answers false; the 0x141787300 answer only decides
// whether the dispatch runs, not what comes back.
bool SynAccChecked4_1417c6bd0(void* pThis, void* a2, void* a3, unsigned char uFlag) {
    if (a2 == nullptr) {                                   // test %rdx,%rdx / jne
        if (g_pfnSynAssert_141823030 != nullptr)
            g_pfnSynAssert_141823030((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x141827b98ULL,
                                     (const void*)(uintptr_t)0x141831610ULL,
                                     (const void*)(uintptr_t)0x141839fe0ULL, 0x39c);
        return false;                                      // xor %al,%al
    }
    bool bGo = false;                                      // test %al,%al after 0x141787300
    if (g_pfnSynPrepBool_141787300 != nullptr)
        bGo = g_pfnSynPrepBool_141787300(a2);              // mov %rbx,%rcx / call 0x141787300
    if (bGo) {
        int nFrom = 0;                                     // mov %eax,%edx
        if (g_pfnSynPrep_141785dc0 != nullptr)
            nFrom = g_pfnSynPrep_141785dc0(a2);            // mov %rbx,%rcx / call 0x141785dc0
        unsigned char* pSlot = *(unsigned char**)((unsigned char*)pThis + 0x88);  // mov 0x88(%rdi),%rcx
        void* pVft = *(void**)pSlot;                       // mov (%rcx),%r9
        void* pFn = *(void**)((unsigned char*)pVft + 0x1a0);   // call *0x1a0(%r9)
        if (g_pfnSynVirt_1417c6bd0 != nullptr)
            g_pfnSynVirt_1417c6bd0(pSlot, pFn, nFrom, uFlag);  // rcx, edx, r8d
        SynAccChecked2_1417c6a60(pThis, a2, a3, 0);        // xor %r9d,%r9d / call 0x1417c6a60
    }
    return true;                                           // mov $0x1,%al
}

// The slot-0 tail call the two bodies below take. The target read out of the vtable is handed
// to the seam together with the object, so nothing is invented about what it does.
void* (*g_pfnSynVirt0_1417c6c80)(void*, void*) = nullptr;       // jmp *(%rax)

// 0x1417c6c80 — add $0x98,%rcx / mov (%rcx),%rax / jmp *(%rax)
// The object is the one at this+0x98, its vtable slot 0 the target.
void* SynAccVirt0At98_1417c6c80(void* pThis) {
    unsigned char* pObj = *(unsigned char**)((unsigned char*)pThis + 0x98);   // add $0x98,%rcx
    void* pFn = *(void**)pObj;                                                // mov (%rcx),%rax
    if (g_pfnSynVirt0_1417c6c80 != nullptr)
        return g_pfnSynVirt0_1417c6c80(pObj, pFn);                            // jmp *(%rax)
    return nullptr;
}

// 0x1417c6c90 — mov (%rcx),%rax / jmp *(%rax)
// The same jump, with this itself as the object.
void* SynAccVirt0_1417c6c90(void* pThis) {
    unsigned char* pObj = (unsigned char*)pThis;                              // rcx unchanged
    void* pFn = *(void**)pObj;                                                // mov (%rcx),%rax
    if (g_pfnSynVirt0_1417c6c80 != nullptr)
        return g_pfnSynVirt0_1417c6c80(pObj, pFn);                            // jmp *(%rax)
    return nullptr;
}

// 0x1417c6d20 — movq $0x0,(%rcx) / mov %rcx,%rax / ret
void* SynAccZeroLead_1417c6d20(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c6d30 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c6d30(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c6d40 — mov 0x30(%rcx),%rax / add $0x8,%rax / ret
void* SynAccSlot30Plus8_1417c6d40(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 8;
}

// 0x1417c6d60 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c6d60(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c6d70 — mov 0x30(%rcx),%rax / add $0x8,%rax / ret
void* SynAccSlot30Plus8_1417c6d70(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 8;
}

// 0x1417c6d90 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c6d90(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c6da0 — mov 0x30(%rcx),%rax / add $0x8,%rax / ret
void* SynAccSlot30Plus8_1417c6da0(void* pThis) {
    return (unsigned char*)*(void**)((unsigned char*)pThis + 0x30) + 8;
}

// 0x1417c6f20 — mov (%rdx),%rax / mov %rax,(%rcx) / mov 0x8(%rdx),%rax /
//               mov %rax,0x8(%rcx) / mov %rcx,%rax / ret
void* SynAccCopy16_1417c6f20(void* pThis, const void* pSrc) {
    std::memcpy(pThis, pSrc, 0x10);                       // the two qword stores
    return pThis;                                         // mov %rcx,%rax
}

// 0x1417c6f40 — movq $0x0,(%rcx) / mov %rcx,%rax / ret
void* SynAccZeroLead_1417c6f40(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c6f50 — movabs $0xfffffffffffffff,%rax / ret
uint64_t SynAccConst_1417c6f50() { return 0x0fffffffffffffffULL; }

// 0x1417c6f60 — the keyed search:
//   mov 0x30(%rcx),%r8 / mov 0x8(%r8),%rax / cmpb $0x0,0x29(%rax) / jne done /
//   loop: mov (%rdx),%ecx / cmp %ecx,0x18(%rax) / jae left / mov 0x10(%rax),%rax / jmp test /
//   left: mov %rax,%r8 / mov (%rax),%rax / test: cmpb $0x0,0x29(%rax) / je loop /
//   done: mov %r8,%rax
// `cmp %ecx,0x18(%rax)` is a 32-bit compare, so the key at +0x18 is read as one; `jae` keeps the
// last node whose key was >= the argument and turns left there, otherwise the walk goes right.
// The answer is that candidate, not the node the walk stopped on.
void* SynAccSearch_1417c6f60(void* pTree, const void* pKey) {
    unsigned char* s = (unsigned char*)pTree;                     // rcx
    unsigned char* pCand = *(unsigned char**)(s + 0x30);          // mov 0x30(%rcx),%r8
    unsigned char* pNode = *(unsigned char**)(pCand + 8);         // mov 0x8(%r8),%rax
    while (*(unsigned char*)(pNode + 0x29) == 0) {                // cmpb / jne done
        uint32_t uKey = *(const uint32_t*)pKey;                   // mov (%rdx),%ecx
        if (*(uint32_t*)(pNode + 0x18) >= uKey) {                 // cmp %ecx,0x18(%rax) / jae
            pCand = pNode;                                        // mov %rax,%r8
            pNode = *(unsigned char**)(pNode);                    // mov (%rax),%rax
        } else {
            pNode = *(unsigned char**)(pNode + 0x10);             // mov 0x10(%rax),%rax
        }
    }
    return pCand;                                                 // mov %r8,%rax
}

// 0x1417c6f90 — the 0x10-side rotation, byte for byte the body at 0x1417c6100:
//   mov 0x10(%rdx),%r8 / mov (%r8),%rax / mov %rax,0x10(%rdx) / mov (%r8),%rax /
//   cmpb $0x0,0x29(%rax) / jne / mov %rdx,0x8(%rax) / mov 0x8(%rdx),%rax / mov %rax,0x8(%r8) /
//   mov 0x30(%rcx),%rax / cmp 0x8(%rax),%rdx / jne / then the three link cases
void* SynAccRotRight_1417c6f90(void* pTree, void* pNode) {
    unsigned char* s = (unsigned char*)pTree;                     // rcx
    unsigned char* x = (unsigned char*)pNode;                     // rdx
    unsigned char* y = *(unsigned char**)(x + 0x10);              // mov 0x10(%rdx),%r8
    *(void**)(x + 0x10) = *(void**)(y);                           // mov (%r8),%rax / mov %rax,0x10(%rdx)
    unsigned char* l = *(unsigned char**)(y);                     // mov (%r8),%rax
    if (*(unsigned char*)(l + 0x29) == 0)                         // cmpb / jne
        *(void**)(l + 8) = x;                                     // mov %rdx,0x8(%rax)
    *(void**)(y + 8) = *(void**)(x + 8);                          // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    unsigned char* head = *(unsigned char**)(s + 0x30);           // mov 0x30(%rcx),%rax
    if (x == *(unsigned char**)(head + 8)) {                      // cmp 0x8(%rax),%rdx / jne
        *(void**)(head + 8) = y;
        *(void**)(y) = x;
        *(void**)(x + 8) = y;
        return pNode;
    }
    unsigned char* p = *(unsigned char**)(x + 8);                 // mov 0x8(%rdx),%rax
    if (x == *(unsigned char**)p) {                               // cmp (%rax),%rdx / jne
        *(void**)(p) = y;
        *(void**)(y) = x;
        *(void**)(x + 8) = y;
        return pNode;
    }
    *(void**)(p + 0x10) = y;                                      // mov %r8,0x10(%rax)
    *(void**)(y) = x;
    *(void**)(x + 8) = y;
    return pNode;
}

// 0x1417c6ff0 — the mirror rotation, byte for byte the body at 0x1417c6170:
//   mov (%rdx),%r8 / mov 0x10(%r8),%rax / mov %rax,(%rdx) / ...
void* SynAccRotLeft_1417c6ff0(void* pTree, void* pNode) {
    unsigned char* s = (unsigned char*)pTree;                     // rcx
    unsigned char* x = (unsigned char*)pNode;                     // rdx
    unsigned char* y = *(unsigned char**)(x);                     // mov (%rdx),%r8
    *(void**)(x) = *(void**)(y + 0x10);                           // mov 0x10(%r8),%rax / mov %rax,(%rdx)
    unsigned char* r = *(unsigned char**)(y + 0x10);              // mov 0x10(%r8),%rax
    if (*(unsigned char*)(r + 0x29) == 0)                         // cmpb / jne
        *(void**)(r + 8) = x;                                     // mov %rdx,0x8(%rax)
    *(void**)(y + 8) = *(void**)(x + 8);                          // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    unsigned char* head = *(unsigned char**)(s + 0x30);           // mov 0x30(%rcx),%rax
    if (x == *(unsigned char**)(head + 8)) {                      // cmp 0x8(%rax),%rdx / jne
        *(void**)(head + 8) = y;
        *(void**)(y + 0x10) = x;
        *(void**)(x + 8) = y;
        return pNode;
    }
    unsigned char* p = *(unsigned char**)(x + 8);                 // mov 0x8(%rdx),%rax
    if (x == *(unsigned char**)(p + 0x10)) {                      // cmp 0x10(%rax),%rdx / jne
        *(void**)(p + 0x10) = y;
        *(void**)(y + 0x10) = x;
        *(void**)(x + 8) = y;
        return pNode;
    }
    *(void**)(p) = y;                                             // mov %r8,(%rax)
    *(void**)(y + 0x10) = x;
    *(void**)(x + 8) = y;
    return pNode;
}

// ---------------------------------------------------------------------------
// D144 — 0x1417c7050..0x1417c71c0: two no-ops, two constants, the two 0x41
// rotations and the 0x21 search. Each body is its own instruction run.

// 0x1417c7050 — ret $0x0
void SynAccNoop_1417c7050() {}

// 0x1417c7060 — ret $0x0
void SynAccNoop_1417c7060() {}

// 0x1417c7070 — movabs $0x666666666666666,%rax / ret
uint64_t SynAccConst_1417c7070() { return 0x0666666666666666ULL; }

// 0x1417c70e0 — the 0x10-side rotation, its links tested against the 0x41 byte.
void* SynAccRotRight_1417c70e0(void* pTree, void* pNode) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* x = (unsigned char*)pNode;
    unsigned char* y = *(unsigned char**)(x + 0x10);          // mov 0x10(%rdx),%r8
    *(void**)(x + 0x10) = *(void**)(y);                      // mov (%r8),%rax / mov %rax,0x10(%rdx)
    {
        unsigned char* l = *(unsigned char**)(y);            // mov (%r8),%rax
        if (*(unsigned char*)(l + 0x41) == 0)                // cmpb $0x0,0x41(%rax) / jne
            *(void**)(l + 8) = x;                            // mov %rdx,0x8(%rax)
    }
    *(void**)(y + 8) = *(void**)(x + 8);                     // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    {
        unsigned char* h = *(unsigned char**)(t + 0x30);     // mov 0x30(%rcx),%rax
        if (x == *(unsigned char**)(h + 8)) {                // cmp 0x8(%rax),%rdx / jne
            *(void**)(h + 8) = y;                            // mov %r8,0x8(%rax)
            *(void**)(y) = x;                                // mov %rdx,(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        unsigned char* p = *(unsigned char**)(x + 8);        // mov 0x8(%rdx),%rax
        if (x == *(unsigned char**)(p)) {                    // cmp (%rax),%rdx / jne
            *(void**)(p) = y;                                // mov %r8,(%rax)
            *(void**)(y) = x;                                // mov %rdx,(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        *(void**)(p + 0x10) = y;                             // mov %r8,0x10(%rax)
        *(void**)(y) = x;                                    // mov %rdx,(%r8)
        *(void**)(x + 8) = y;                                // mov %r8,0x8(%rdx)
        return y;
    }
}

// 0x1417c7140 — the mirror, the 0x0 side first and the last link case on 0x10.
void* SynAccRotLeft_1417c7140(void* pTree, void* pNode) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* x = (unsigned char*)pNode;
    unsigned char* y = *(unsigned char**)(x);                // mov (%rdx),%r8
    *(void**)(x) = *(void**)(y + 0x10);                      // mov 0x10(%r8),%rax / mov %rax,(%rdx)
    {
        unsigned char* r = *(unsigned char**)(y + 0x10);     // mov 0x10(%r8),%rax
        if (*(unsigned char*)(r + 0x41) == 0)                // cmpb $0x0,0x41(%rax) / jne
            *(void**)(r + 8) = x;                            // mov %rdx,0x8(%rax)
    }
    *(void**)(y + 8) = *(void**)(x + 8);                     // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    {
        unsigned char* h = *(unsigned char**)(t + 0x30);     // mov 0x30(%rcx),%rax
        if (x == *(unsigned char**)(h + 8)) {                // cmp 0x8(%rax),%rdx / jne
            *(void**)(h + 8) = y;                            // mov %r8,0x8(%rax)
            *(void**)(y + 0x10) = x;                         // mov %rdx,0x10(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        unsigned char* p = *(unsigned char**)(x + 8);        // mov 0x8(%rdx),%rax
        if (x == *(unsigned char**)(p + 0x10)) {             // cmp 0x10(%rax),%rdx / jne
            *(void**)(p + 0x10) = y;                         // mov %r8,0x10(%rax)
            *(void**)(y + 0x10) = x;                         // mov %rdx,0x10(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        *(void**)(p) = y;                                    // mov %r8,(%rax)
        *(void**)(y + 0x10) = x;                             // mov %rdx,0x10(%r8)
        *(void**)(x + 8) = y;                                // mov %r8,0x8(%rdx)
        return y;
    }
}

// 0x1417c71a0 — ret $0x0
void SynAccNoop_1417c71a0() {}

// 0x1417c71b0 — movabs $0x1fffffffffffffff,%rax / ret
uint64_t SynAccConst_1417c71b0() { return 0x1FFFFFFFFFFFFFFFULL; }

// 0x1417c71c0 — the keyed search against the 0x21 byte, 32-bit compare, answer is the
// last node the walk turned left at.
void* SynAccSearch21_1417c71c0(void* pTree, const void* pKey) {
    unsigned char* t = (unsigned char*)pTree;                // mov 0x30(%rcx),%r8
    unsigned char* cand = *(unsigned char**)(t + 0x30);      // r8 = header
    unsigned char* n = *(unsigned char**)(cand + 8);         // mov 0x8(%r8),%rax
    while (*(unsigned char*)(n + 0x21) == 0) {               // cmpb $0x0,0x21(%rax) / jne
        unsigned int key = *(const unsigned int*)pKey;       // mov (%rdx),%ecx
        if (*(unsigned int*)(n + 0x18) >= key) {             // cmp %ecx,0x18(%rax) / jae
            cand = n;                                        // mov %rax,%r8
            n = *(unsigned char**)(n);                       // mov (%rax),%rax
        } else {
            n = *(unsigned char**)(n + 0x10);                // mov 0x10(%rax),%rax
        }
    }
    return cand;                                             // mov %r8,%rax
}

// ---------------------------------------------------------------------------
// D145 — the two 0x21 rotations at 0x1417c71f0 / 0x1417c7250 and the stub 0x1417c72b0.

// 0x1417c71f0 — the 0x10-side rotation with every link tested against the 0x21 byte.
void* SynAccRotRight21_1417c71f0(void* pTree, void* pNode) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* x = (unsigned char*)pNode;
    unsigned char* y = *(unsigned char**)(x + 0x10);          // mov 0x10(%rdx),%r8
    *(void**)(x + 0x10) = *(void**)(y);                      // mov (%r8),%rax / mov %rax,0x10(%rdx)
    {
        unsigned char* l = *(unsigned char**)(y);            // mov (%r8),%rax
        if (*(unsigned char*)(l + 0x21) == 0)                // cmpb $0x0,0x21(%rax) / jne
            *(void**)(l + 8) = x;                            // mov %rdx,0x8(%rax)
    }
    *(void**)(y + 8) = *(void**)(x + 8);                     // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    {
        unsigned char* hd = *(unsigned char**)(t + 0x30);    // mov 0x30(%rcx),%rax
        if (x == *(unsigned char**)(hd + 8)) {               // cmp 0x8(%rax),%rdx / jne
            *(void**)(hd + 8) = y;                           // mov %r8,0x8(%rax)
            *(void**)(y) = x;                                // mov %rdx,(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        unsigned char* p = *(unsigned char**)(x + 8);        // mov 0x8(%rdx),%rax
        if (x == *(unsigned char**)(p)) {                    // cmp (%rax),%rdx / jne
            *(void**)(p) = y;                                // mov %r8,(%rax)
            *(void**)(y) = x;                                // mov %rdx,(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        *(void**)(p + 0x10) = y;                             // mov %r8,0x10(%rax)
        *(void**)(y) = x;                                    // mov %rdx,(%r8)
        *(void**)(x + 8) = y;                                // mov %r8,0x8(%rdx)
        return y;
    }
}

// 0x1417c7250 — the mirror on the 0x0 side, last link case on 0x10, 0x21 byte throughout.
void* SynAccRotLeft21_1417c7250(void* pTree, void* pNode) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* x = (unsigned char*)pNode;
    unsigned char* y = *(unsigned char**)(x);                // mov (%rdx),%r8
    *(void**)(x) = *(void**)(y + 0x10);                      // mov 0x10(%r8),%rax / mov %rax,(%rdx)
    {
        unsigned char* r = *(unsigned char**)(y + 0x10);     // mov 0x10(%r8),%rax
        if (*(unsigned char*)(r + 0x21) == 0)                // cmpb $0x0,0x21(%rax) / jne
            *(void**)(r + 8) = x;                            // mov %rdx,0x8(%rax)
    }
    *(void**)(y + 8) = *(void**)(x + 8);                     // mov 0x8(%rdx),%rax / mov %rax,0x8(%r8)
    {
        unsigned char* hd = *(unsigned char**)(t + 0x30);    // mov 0x30(%rcx),%rax
        if (x == *(unsigned char**)(hd + 8)) {               // cmp 0x8(%rax),%rdx / jne
            *(void**)(hd + 8) = y;                           // mov %r8,0x8(%rax)
            *(void**)(y + 0x10) = x;                         // mov %rdx,0x10(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        unsigned char* p = *(unsigned char**)(x + 8);        // mov 0x8(%rdx),%rax
        if (x == *(unsigned char**)(p + 0x10)) {             // cmp 0x10(%rax),%rdx / jne
            *(void**)(p + 0x10) = y;                         // mov %r8,0x10(%rax)
            *(void**)(y + 0x10) = x;                         // mov %rdx,0x10(%r8)
            *(void**)(x + 8) = y;                            // mov %r8,0x8(%rdx)
            return y;
        }
        *(void**)(p) = y;                                    // mov %r8,(%rax)
        *(void**)(y + 0x10) = x;                             // mov %rdx,0x10(%r8)
        *(void**)(x + 8) = y;                                // mov %r8,0x8(%rdx)
        return y;
    }
}

// 0x1417c72b0 — ret $0x0
void SynAccNoop_1417c72b0() {}

// 0x1417c7300 — lea 0x18(%rcx),%rax / ret
void* SynAccPlus18_1417c7300(void* pThis) { return (unsigned char*)pThis + 0x18; }

// 0x1417c7310 — ret $0x0
void SynAccNoop_1417c7310() {}

// 0x1417c7360 — movq $0x0,(%rcx) / mov %rcx,%rax / ret
void* SynAccZeroLead_1417c7360(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c7370 — the count arrives in rdx, and the throw branch zeroes r8, so a seam that
// returns leaves the size at zero: the bytes compute the size from the same register.
void* SynAccNew48FromCount_1417c7370(void* pUnused, uint64_t nCount) {
    int64_t nSentinel = -2;                          // movq $0xfffffffffffffffe,0x20(%rsp)
    (void)nSentinel; (void)pUnused;
    uint64_t r8 = nCount;                            // mov %rdx,%r8
    if (r8 != 0) {                                   // test %rdx,%rdx / je
        uint64_t uQuot = 0xFFFFFFFFFFFFFFFFull / r8; // or $-1,%rax / xor %edx,%edx / div %r8
        if (uQuot < 0x30) {                          // cmp $0x30,%rax / jae
            r8 = 0;                                  // xor %r8d,%r8d
            unsigned char aErr[0x40] = {};
            uint64_t uZero = r8;                     // mov %r8,0x58(%rsp)
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(aErr, &uZero);          // call *0x1418233e8
            *(const void**)aErr = (const void*)(uintptr_t)0x141824c40;  // lea 0x141824c40 / mov %rax
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(aErr, (const void*)(uintptr_t)0x141881df0);
        }
    }
    uint64_t uBytes = r8 * 3 * 16;                   // lea (%r8,%r8,2) / shl $0x4
    if (g_pfnSynNew_1417f3166 == nullptr) return nullptr;
    return g_pfnSynNew_1417f3166(uBytes);            // call 0x1417f3166
}

// 0x1417c73e0 — the same body with the 0x48 limit and a nine-wide element.
void* SynAccNew72FromCount_1417c73e0(void* pUnused, uint64_t nCount) {
    int64_t nSentinel = -2;
    (void)nSentinel; (void)pUnused;
    uint64_t r8 = nCount;
    if (r8 != 0) {
        uint64_t uQuot = 0xFFFFFFFFFFFFFFFFull / r8;
        if (uQuot < 0x48) {
            r8 = 0;
            unsigned char aErr[0x40] = {};
            uint64_t uZero = r8;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(aErr, &uZero);
            *(const void**)aErr = (const void*)(uintptr_t)0x141824c40;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(aErr, (const void*)(uintptr_t)0x141881df0);
        }
    }
    uint64_t uBytes = r8 * 9 * 8;                    // lea (%r8,%r8,8) / shl $0x3
    if (g_pfnSynNew_1417f3166 == nullptr) return nullptr;
    return g_pfnSynNew_1417f3166(uBytes);
}

// 0x1417c7450 — and again with the 0x28 limit and a five-wide element.
void* SynAccNew40FromCount_1417c7450(void* pUnused, uint64_t nCount) {
    int64_t nSentinel = -2;
    (void)nSentinel; (void)pUnused;
    uint64_t r8 = nCount;
    if (r8 != 0) {
        uint64_t uQuot = 0xFFFFFFFFFFFFFFFFull / r8;
        if (uQuot < 0x28) {
            r8 = 0;
            unsigned char aErr[0x40] = {};
            uint64_t uZero = r8;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(aErr, &uZero);
            *(const void**)aErr = (const void*)(uintptr_t)0x141824c40;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(aErr, (const void*)(uintptr_t)0x141881df0);
        }
    }
    uint64_t uBytes = r8 * 5 * 8;                    // lea (%r8,%r8,4) / shl $0x3
    if (g_pfnSynNew_1417f3166 == nullptr) return nullptr;
    return g_pfnSynNew_1417f3166(uBytes);
}

// 0x1417c7580 — movabs $0xfffffffffffffff,%rax / ret
uint64_t SynAccConst_1417c7580() { return 0x0fffffffffffffffull; }

// 0x1417c75b0 — movq $0x0,(%rcx) / mov %rcx,%rax / ret
void* SynAccZeroLead_1417c75b0(void* pThis) {
    *(void**)pThis = nullptr;
    return pThis;
}

// 0x1417c75c0 — test %rdx,%rdx / je / mov (%r8),%rax / mov %rax,(%rdx) / repz ret
void SynAccStoreFromR8_1417c75c0(void* pUnused, void* pDst, const void* pSrc) {
    (void)pUnused;
    if (pDst != nullptr) *(void**)pDst = *(void**)pSrc;
}

// 0x1417c75d0 — the same body at its own start.
void SynAccStoreFromR8_1417c75d0(void* pUnused, void* pDst, const void* pSrc) {
    (void)pUnused;
    if (pDst != nullptr) *(void**)pDst = *(void**)pSrc;
}

// 0x1417c75e0 — ret $0x0
void SynAccNoop_1417c75e0() {}

// 0x1417c75f0 — the same body at its own start.
void SynAccStoreFromR8_1417c75f0(void* pUnused, void* pDst, const void* pSrc) {
    (void)pUnused;
    if (pDst != nullptr) *(void**)pDst = *(void**)pSrc;
}

// 0x1417c7620 — the same allocator body as 0x1417c7370 at its own start: count in rdx,
// 0x30 limit, 48-byte element, `call 0x1417f3166`.
void* SynAccNew48Count2_1417c7620(void* pUnused, uint64_t nCount) {
    int64_t nSentinel = -2;
    (void)nSentinel; (void)pUnused;
    uint64_t r8 = nCount;                            // mov %rdx,%r8
    if (r8 != 0) {
        uint64_t uQuot = 0xFFFFFFFFFFFFFFFFull / r8;
        if (uQuot < 0x30) {
            r8 = 0;                                  // xor %r8d,%r8d
            unsigned char aErr[0x40] = {};
            uint64_t uZero = r8;
            if (g_pfnSynErrCtor_1418233e8 != nullptr)
                g_pfnSynErrCtor_1418233e8(aErr, &uZero);
            *(const void**)aErr = (const void*)(uintptr_t)0x141824c40;
            if (g_pfnSynThrow_1417f3154 != nullptr)
                g_pfnSynThrow_1417f3154(aErr, (const void*)(uintptr_t)0x141881df0);
        }
    }
    uint64_t uBytes = r8 * 3 * 16;                   // lea (%r8,%r8,2) / shl $0x4
    if (g_pfnSynNew_1417f3166 == nullptr) return nullptr;
    return g_pfnSynNew_1417f3166(uBytes);
}

// 0x1417c7690 — ret $0x0
void SynAccNoop_1417c7690() {}

// 0x1417c76a0 — the guarded store once more, destination rdx and source r8.
void SynAccStoreFromR8_1417c76a0(void* pUnused, void* pDst, const void* pSrc) {
    (void)pUnused;
    if (pDst != nullptr) *(void**)pDst = *(void**)pSrc;
}

// 0x1417c76d0 — takes eight bytes from 0x1417f3166, writes the object into them, then stores
// the block (or zero) in the object's first qword and answers with the object.
void* SynAccNewNode_1417c76d0(void* pThis) {
    int64_t nSentinel = -2; (void)nSentinel;
    void* pBlk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) pBlk = g_pfnSynNew_1417f3166(8);   // mov $0x8,%ecx / call
    void* pSpill = pBlk; (void)pSpill;              // mov %rax,0x50(%rsp) / mov %rax,0x58(%rsp)
    if (pBlk != nullptr) *(void**)pBlk = pThis;     // mov %rbx,(%rax)
    else pBlk = nullptr;                            // xor %eax,%eax
    *(void**)pThis = pBlk;                          // mov %rax,(%rbx)
    return pThis;
}

// 0x1417c7710 — the same body at its own start.
void* SynAccNewNode_1417c7710(void* pThis) {
    int64_t nSentinel = -2; (void)nSentinel;
    void* pBlk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) pBlk = g_pfnSynNew_1417f3166(8);
    void* pSpill = pBlk; (void)pSpill;
    if (pBlk != nullptr) *(void**)pBlk = pThis;
    else pBlk = nullptr;
    *(void**)pThis = pBlk;
    return pThis;
}

// 0x1417c7750 — the same body at its own start.
void* SynAccNewNode_1417c7750(void* pThis) {
    int64_t nSentinel = -2; (void)nSentinel;
    void* pBlk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) pBlk = g_pfnSynNew_1417f3166(8);
    void* pSpill = pBlk; (void)pSpill;
    if (pBlk != nullptr) *(void**)pBlk = pThis;
    else pBlk = nullptr;
    *(void**)pThis = pBlk;
    return pThis;
}

// 0x1417c7790 — the same body at its own start.
void* SynAccNewNode_1417c7790(void* pThis) {
    int64_t nSentinel = -2; (void)nSentinel;
    void* pBlk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) pBlk = g_pfnSynNew_1417f3166(8);
    void* pSpill = pBlk; (void)pSpill;
    if (pBlk != nullptr) *(void**)pBlk = pThis;
    else pBlk = nullptr;
    *(void**)pThis = pBlk;
    return pThis;
}

// 0x1417c77d0 — mov %edx,(%rcx) / mov %r8d,0x4(%rcx) / mov %rcx,%rax / ret
void* SynAcc2Words_1417c77d0(void* pThis, uint32_t uA, uint32_t uB) {
    *(uint32_t*)pThis = uA;
    *(uint32_t*)((unsigned char*)pThis + 4) = uB;
    return pThis;
}

// 0x1417c78a0 - the header's lead and the tree's first qword into the pair, the pair back.
void* SynAccIterFromHeader_1417c78a0(void* pTree, void* pOut) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* o = (unsigned char*)pOut;
    unsigned char* h = *(unsigned char**)(t + 0x30);        // mov 0x30(%rcx),%rax
    void* lead = *(void**)h;                                 // mov (%rax),%r8
    *(void**)o = *(void**)t;                                 // mov (%rcx),%rax / mov %rax,(%rdx)
    *(void**)(o + 8) = lead;                                 // mov %r8,0x8(%rdx)
    return o;                                                // mov %rdx,%rax
}

// 0x1417c78c0 - the same pair as 0x1417c78a0, but the header itself is stored, not its lead,
// and the two stores happen in the other order.
void* SynAccIterHeaderPair_1417c78c0(void* pTree, void* pOut) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* o = (unsigned char*)pOut;
    unsigned char* h = *(unsigned char**)(t + 0x30);        // mov 0x30(%rcx),%rax
    *(void**)(o + 8) = h;                                    // mov %rax,0x8(%rdx)
    *(void**)o = *(void**)t;                                 // mov (%rcx),%rax / mov %rax,(%rdx)
    return o;                                                // mov %rdx,%rax
}

// 0x1417c7920 - both qwords cleared through one register, the object back.
void* SynAccZeroTwo_1417c7920(void* pThis) {
    uint64_t zero = 0;                                       // xor %eax,%eax
    *(uint64_t*)pThis = zero;                                // mov %rax,(%rcx)
    *(uint64_t*)((unsigned char*)pThis + 8) = zero;          // mov %rax,0x8(%rcx)
    return pThis;                                            // mov %rcx,%rax
}

// The four seams the erase body needs, null until something supplies them.
void (*g_pfnSynTmp_141823270)(void*, void*) = nullptr;      // 0x141823270
void (*g_pfnSyn_1418233f8)(void*) = nullptr;                // 0x1418233f8
void (*g_pfnSyn_141823288)(void*, void*) = nullptr;         // 0x141823288


// 0x1417c7c30 - the subtree erase with the full fix-up.
//   rcx = tree, rdx = the pair it answers with, r8 = the iterator that names the node.
// The neighbours it leans on live in CsyndicateLogicTailSlots.cpp.
extern void SynAccDec29_1417c6e80(void* pIter);             // 0x1417c6e80
extern void (*g_pfnLogic_1417f2fdc)(void* p);               // 0x1417f2fdc

void* SynTreeErase_1417c7c30(void* pTree, void* pOut, void* pIter) {
    int64_t frame = -2; (void)frame;
    unsigned char* tree = (unsigned char*)pTree;              // rbp
    unsigned char* out  = (unsigned char*)pOut;               // r13
    unsigned char* it   = (unsigned char*)pIter;              // r12
    unsigned char* n    = *(unsigned char**)(it + 8);         // rsi

    if (*(unsigned char*)(n + 0x29) != 0) {                   // the sentinel path throws
        unsigned char buf[0xa0] = {};
        unsigned char* obj = buf + 0x38;
        if (g_pfnSynTmp_141823270 != nullptr)
            g_pfnSynTmp_141823270(buf, (void*)(uintptr_t)0x141825ca8);
        if (g_pfnSyn_1418233f8 != nullptr) g_pfnSyn_1418233f8(obj);
        *(const void**)obj = (const void*)(uintptr_t)0x141824a60;
        if (g_pfnSyn_141823288 != nullptr) g_pfnSyn_141823288(buf + 0x50, buf + 0x78);
        *(const void**)obj = (const void*)(uintptr_t)0x141824ba0;
        if (g_pfnSynThrow_1417f3154 != nullptr)
            g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881e50);
    }

    SynAccDec29_1417c6e80(it);                                // the iterator is stepped first
    unsigned char* l = *(unsigned char**)(n);                  // r11
    unsigned char* rep = nullptr;                              // rdi
    bool doSwap = false;

    if (*(unsigned char*)(l + 0x29) == 0) {                    // the 0x0 side is real
        unsigned char* rr = *(unsigned char**)(n + 0x10);
        if (*(unsigned char*)(rr + 0x29) != 0) {
            rep = l;
        } else {
            unsigned char* pred = *(unsigned char**)(it + 8);
            rep = *(unsigned char**)(pred + 0x10);
            if (pred != n) doSwap = true;
        }
    } else {
        rep = *(unsigned char**)(n + 0x10);
    }

    if (!doSwap) {
        unsigned char* parent = *(unsigned char**)(n + 8);      // rbx
        if (*(unsigned char*)(rep + 0x29) == 0) *(void**)(rep + 8) = parent;
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 8)) *(void**)(head + 8) = rep;
            else if (n == *(unsigned char**)parent) *(void**)parent = rep;
            else *(void**)(parent + 0x10) = rep;
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)head) {
                unsigned char* cc;
                if (*(unsigned char*)(rep + 0x29) != 0) cc = parent;
                else {
                    cc = rep;
                    unsigned char* a = *(unsigned char**)rep;
                    while (*(unsigned char*)(a + 0x29) == 0) { cc = a; a = *(unsigned char**)a; }
                }
                *(void**)head = cc;
            }
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 0x10)) {
                unsigned char* cc;
                if (*(unsigned char*)(rep + 0x29) != 0) cc = parent;
                else {
                    cc = rep;
                    unsigned char* a = *(unsigned char**)(rep + 0x10);
                    while (*(unsigned char*)(a + 0x29) == 0) { cc = a; a = *(unsigned char**)(a + 0x10); }
                }
                *(void**)(head + 0x10) = cc;
            }
        }
    } else {
        unsigned char* pred = *(unsigned char**)(it + 8);
        *(void**)(l + 8) = pred;
        *(void**)pred = *(void**)n;
        if (pred == *(unsigned char**)(n + 0x10)) {
            ;                                                      // the direct case only fixes the links below
        } else {
            unsigned char* parent = *(unsigned char**)(pred + 8);
            if (*(unsigned char*)(rep + 0x29) == 0) *(void**)(rep + 8) = parent;
            *(void**)parent = rep;
            *(void**)(pred + 0x10) = *(unsigned char**)(n + 0x10);
            *(void**)(*(unsigned char**)(n + 0x10) + 8) = pred;
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 8)) *(void**)(head + 8) = pred;
            else {
                unsigned char* p2 = *(unsigned char**)(n + 8);
                if (n == *(unsigned char**)p2) *(void**)p2 = pred;
                else *(void**)(p2 + 0x10) = pred;
            }
        }
        *(void**)(pred + 8) = *(unsigned char**)(n + 8);
        {
            unsigned char* a = n + 0x28;
            unsigned char* b = pred + 0x28;
            if (a != b) { unsigned char t = *b; unsigned char u = *a; *b = u; *a = t; }
        }
    }

    unsigned char* colTarget = rep;                            // rdi at 0x1417c7f6a
    if (*(unsigned char*)(n + 0x28) == 1) {
        unsigned char* head = *(unsigned char**)(tree + 0x30);
        if (rep != *(unsigned char**)(head + 8) && *(unsigned char*)(rep + 0x28) == 1) {
            unsigned char* cur = rep;
            unsigned char* node = *(unsigned char**)(n + 8);
            for (;;) {
                bool stop = false;
                if (cur == *(unsigned char**)node) {
                    unsigned char* sib = *(unsigned char**)(node + 0x10);
                    if (*(unsigned char*)(sib + 0x28) == 0) {
                        *(unsigned char*)(sib + 0x28) = 1;
                        *(unsigned char*)(node + 0x28) = 0;
                        SynAccRotRight_1417c6f90(tree, node);
                        sib = *(unsigned char**)(node + 0x10);
                    }
                    if (*(unsigned char*)(sib + 0x29) != 0) {
                        cur = node; stop = true;
                    } else if (*(unsigned char*)(*(unsigned char**)sib + 0x28) != 1 ||
                               *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) != 1) {
                        if (*(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) == 1) {
                            *(unsigned char*)(*(unsigned char**)sib + 0x28) = 1;
                            *(unsigned char*)(sib + 0x28) = 0;
                            SynAccRotLeft_1417c6ff0(tree, sib);
                            sib = *(unsigned char**)(node + 0x10);
                        }
                        *(unsigned char*)(sib + 0x28) = *(unsigned char*)(node + 0x28);
                        *(unsigned char*)(node + 0x28) = 1;
                        *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) = 1;
                        SynAccRotRight_1417c6f90(tree, node);
                        stop = true;
                    } else {
                        *(unsigned char*)(sib + 0x28) = 0;
                        cur = node;
                    }
                } else {
                    unsigned char* sib = *(unsigned char**)node;
                    if (*(unsigned char*)(sib + 0x28) == 0) {
                        *(unsigned char*)(sib + 0x28) = 1;
                        *(unsigned char*)(node + 0x28) = 0;
                        SynAccRotLeft_1417c6ff0(tree, node);
                        sib = *(unsigned char**)node;
                    }
                    if (*(unsigned char*)(sib + 0x29) != 0) {
                        cur = node; stop = true;
                    } else if (*(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) != 1 ||
                               *(unsigned char*)(*(unsigned char**)sib + 0x28) != 1) {
                        if (*(unsigned char*)(*(unsigned char**)sib + 0x28) == 1) {
                            *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) = 1;
                            *(unsigned char*)(sib + 0x28) = 0;
                            SynAccRotRight_1417c6f90(tree, sib);
                            sib = *(unsigned char**)node;
                        }
                        *(unsigned char*)(sib + 0x28) = *(unsigned char*)(node + 0x28);
                        *(unsigned char*)(node + 0x28) = 1;
                        *(unsigned char*)(*(unsigned char**)sib + 0x28) = 1;
                        SynAccRotLeft_1417c6ff0(tree, node);
                        stop = true;
                    } else {
                        *(unsigned char*)(sib + 0x28) = 0;
                        cur = node;
                    }
                }
                if (stop) break;
                node = *(unsigned char**)(node + 8);
                head = *(unsigned char**)(tree + 0x30);
                if (cur == *(unsigned char**)(head + 8)) break;
            }
            colTarget = cur;
        }
    }
    *(unsigned char*)(colTarget + 0x28) = 1;                    // 0x1417c7f6a

    if (g_pfnLogic_1417f2fdc != nullptr) g_pfnLogic_1417f2fdc(n);
    {
        unsigned char* cnt = tree + 0x38;
        uint64_t v = *(uint64_t*)cnt;
        if (v != 0) *(uint64_t*)cnt = v - 1;
    }
    {
        unsigned char tmp[0x10];
        *(void**)tmp = *(void**)it;
        *(void**)(tmp + 8) = *(void**)(it + 8);
        *(void**)tmp = *(void**)tree;
        *(void**)out = *(void**)tmp;
        *(void**)(out + 8) = *(void**)(tmp + 8);
    }
    return out;
}

// the two seams these bodies reach: the DEBUG iterator check and the node comparator
extern void (*g_pfn_invalid_parameter_noinfo)(void);
extern bool (*g_pfnSynCmp_141823260)(void* pA, void* pB);
// 0x1417c7ff0 - the two bounds in one pass, then four qwords out.
void* SynAccLowerUpper_1417c7ff0(void* pTree, void* pOut, const void* pKey) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* out = (unsigned char*)pOut;
    unsigned char* h = *(unsigned char**)(t + 0x30);          // mov 0x30(%rcx),%r11
    unsigned char* cand = h;                                  // mov %r11,%r9
    unsigned char* n = *(unsigned char**)(h + 8);             // mov 0x8(%r11),%rax
    if (*(unsigned char*)(n + 0x29) == 0) {                   // cmpb $0x0,0x29(%rax) / jne
        for (;;) {
            uint32_t key = *(const uint32_t*)pKey;            // mov (%r8),%r10d
            uint32_t nk = *(uint32_t*)(n + 0x18);             // mov 0x18(%rax),%edx
            if (nk < key) {                                   // cmp %r10d,%edx / jae
                n = *(unsigned char**)(n + 0x10);             // mov 0x10(%rax),%rax
            } else {
                if (*(unsigned char*)(cand + 0x29) == 0) {     // cmpb $0x0,0x29(%r9) / je
                    if (key < nk) cand = n;                    // cmp %edx,%r10d / cmovb
                }
                h = n;                                        // mov %rax,%r11
                n = *(unsigned char**)n;                      // mov (%rax),%rax
            }
            if (*(unsigned char*)(n + 0x29) != 0) break;       // cmpb / je
        }
    }
    unsigned char* q;
    if (*(unsigned char*)(cand + 0x29) == 0) {                 // cmpb $0x0,0x29(%r9) / je
        q = *(unsigned char**)cand;                            // mov (%r9),%rcx
    } else {
        unsigned char* a = *(unsigned char**)(t + 0x30);       // mov 0x30(%rcx),%rax
        q = *(unsigned char**)(a + 8);                         // mov 0x8(%rax),%rcx
    }
    while (*(unsigned char*)(q + 0x29) == 0) {                 // cmpb / jne
        uint32_t key = *(const uint32_t*)pKey;                // mov (%r8),%eax
        if (key >= *(uint32_t*)(q + 0x18)) {                  // cmp 0x18(%rcx),%eax / jae
            q = *(unsigned char**)(q + 0x10);                 // mov 0x10(%rcx),%rcx
        } else {
            cand = q;                                          // mov %rcx,%r9
            q = *(unsigned char**)q;                           // mov (%rcx),%rcx
        }
    }
    void* v0 = *(void**)t;                                     // mov (%rbx),%rax
    *(void**)(out) = v0;                                       // mov %rax,(%rdi)
    *(void**)(out + 8) = h;                                    // mov %r11,0x8(%rdi)
    *(void**)(out + 0x10) = v0;                                // mov %rax,0x10(%rdi)
    *(void**)(out + 0x18) = cand;                              // mov %r9,0x18(%rdi)
    return out;                                                // mov %rdi,%rax
}

// 0x1417c80d0 - the 0x30-byte node: three words, the argument's two, the flag, then a clear 0x29.
void* SynAccNew30_1417c80d0(void* pUnused, void* p2, void* p3, void* p4,
                            const void* pPair, unsigned char uFlag) {
    (void)pUnused;
    int64_t s = -2; (void)s;                                   // movq $..fe,0x28(%rsp)
    void* pBlk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) pBlk = g_pfnSynNew_1417f3166(0x30);  // mov $0x30,%ecx
    if (pBlk != nullptr) {
        unsigned char* b = (unsigned char*)pBlk;
        *(void**)(b) = p2;                                     // mov %rsi,(%rax)
        *(void**)(b + 8) = p3;                                 // mov %rdi,0x8(%rax)
        *(void**)(b + 0x10) = p4;                              // mov %rbx,0x10(%rax)
        *(void**)(b + 0x18) = *(void**)pPair;                  // mov (%rcx),%rax
        *(void**)(b + 0x20) = *(void**)((const unsigned char*)pPair + 8);  // mov 0x8(%rcx),%rax
        *(unsigned char*)(b + 0x28) = uFlag;                   // mov %al,0x28(%r11)
        *(unsigned char*)(b + 0x29) = 0;                       // movb $0x0,0x29(%r11)
    }
    return pBlk;                                               // mov %r11,%rax
}

// 0x1417c8150 - the header into +0x8 and the tree's first qword into +0x0.
void* SynAccPairHeader_1417c8150(void* pTree, void* pOut) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* out = (unsigned char*)pOut;
    unsigned char* h = *(unsigned char**)(t + 0x30);           // mov 0x30(%rcx),%rax
    *(void**)(out + 8) = h;                                    // mov %rax,0x8(%rdx)
    *(void**)(out) = *(void**)t;                               // mov (%rcx),%rax
    return out;                                                // mov %rdx,%rax
}

// 0x1417c8170 - the object's first qword and the argument's +0x8, through a temp, after the check.
void* SynAccPairChecked_1417c8170(void* pThis, void* pOut, const void* pArg) {
    int64_t s = -2; (void)s;
    unsigned char* t = (unsigned char*)pThis;
    unsigned char* out = (unsigned char*)pOut;
    void* hi = *(void**)((const unsigned char*)pArg + 8);     // mov 0x8(%r8),%rax
    if (pThis == nullptr) {                                    // test %rcx,%rcx / jne
        if (g_pfn_invalid_parameter_noinfo != nullptr) g_pfn_invalid_parameter_noinfo();
    }
    *(void**)(out) = *(void**)t;                               // the temp then moves both qwords
    *(void**)(out + 8) = hi;
    return out;                                                // mov %rbx,%rax
}

// 0x1417c81c0 - the comparator range: 0x41 flags, two comparator calls per turn on the left side.
void* SynAccRangeCmp_1417c81c0(void* pTree, void* pOut, void* pKey) {
    unsigned char* t = (unsigned char*)pTree;
    unsigned char* out = (unsigned char*)pOut;
    unsigned char* h = *(unsigned char**)(t + 0x30);           // mov 0x30(%rcx),%rbp
    unsigned char* cand = h;                                   // mov %rbp,%rdi
    unsigned char* n = *(unsigned char**)(h + 8);              // mov 0x8(%rbp),%rbx
    unsigned char* last = h;                                   // rbp doubles as the first bound
    if (*(unsigned char*)(n + 0x41) == 0) {                    // cmpb $0x0,0x41(%rbx) / jne
        for (;;) {
            int a = 0;
            if (g_pfnSynCmp_141823260 != nullptr)              // lea 0x18(%rbx),%rcx / call
                a = g_pfnSynCmp_141823260(n + 0x18, pKey);
            if (a != 0) {
                n = *(unsigned char**)(n + 0x10);              // mov 0x10(%rbx),%rbx
            } else {
                if (*(unsigned char*)(cand + 0x41) == 0) {      // cmpb $0x0,0x41(%rdi) / je
                    int b = 0;
                    if (g_pfnSynCmp_141823260 != nullptr)      // mov %r12,%rcx / lea 0x18(%rbx),%rdx
                        b = g_pfnSynCmp_141823260(pKey, n + 0x18);
                    if (b != 0) cand = n;                      // cmovne %rbx,%rdi
                }
                last = n;                                      // mov %rbx,%rbp
                n = *(unsigned char**)n;                       // mov (%rbx),%rbx
            }
            if (*(unsigned char*)(n + 0x41) != 0) break;       // cmpb / je
        }
    }
    unsigned char* q;
    if (*(unsigned char*)(cand + 0x41) == 0) {                 // cmpb $0x0,0x41(%rdi) / je
        q = *(unsigned char**)cand;                            // mov (%rdi),%rbx
    } else {
        unsigned char* a = *(unsigned char**)(t + 0x30);       // mov 0x30(%r13),%rax
        q = *(unsigned char**)(a + 8);                         // mov 0x8(%rax),%rbx
    }
    while (*(unsigned char*)(q + 0x41) == 0) {                 // cmpb / jne
        int c = 0;
        if (g_pfnSynCmp_141823260 != nullptr)                  // mov %r12,%rcx / lea 0x18(%rbx),%rdx
            c = g_pfnSynCmp_141823260(pKey, q + 0x18);
        if (c != 0) {
            cand = q;                                          // mov %rbx,%rdi
            q = *(unsigned char**)q;                           // mov (%rbx),%rbx
        } else {
            q = *(unsigned char**)(q + 0x10);                  // mov 0x10(%rbx),%rbx
        }
    }
    void* v0 = *(void**)t;                                     // mov 0x0(%r13),%rax
    *(void**)(out) = v0;                                       // mov %rax,(%r14)
    *(void**)(out + 8) = last;                                 // mov %rbp,0x28(%rsp) pair
    *(void**)(out + 0x10) = v0;                                // mov %rax,0x30(%rsp)
    *(void**)(out + 0x18) = cand;                              // mov %rdi,0x38(%rsp)
    return out;                                                // mov %r14,%rax
}

// 0x1417c82e0 - the 0x48 node: three words, a sub-object built at +0x18 through 0x141823288,
// the flag byte at +0x40 and a cleared +0x41.
void* SynAccNew48Node_1417c82e0(void* pUnused, void* p2, void* p3, void* p4,
                                const void* pArg5, unsigned char uFlag) {
    (void)pUnused;
    int64_t frame = -2; (void)frame;                      // movq $0xfffffffffffffffe,0x28(%rsp)
    unsigned char* blk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) blk = (unsigned char*)g_pfnSynNew_1417f3166(0x48);
    if (blk != nullptr) {                                 // test %rax,%rax / je
        *(void**)(blk) = p2;                              // mov %r12,(%rax)
        *(void**)(blk + 8) = p3;                          // mov %rsi,0x8(%rax)
        *(void**)(blk + 0x10) = p4;                       // mov %rdi,0x10(%rax)
        if (g_pfnSyn_141823288 != nullptr)                // lea 0x18(%rax),%rcx / call *0x141823288
            g_pfnSyn_141823288(blk + 0x18, (void*)pArg5);
        *(unsigned char*)(blk + 0x40) = uFlag;            // mov %al,0x40(%rbx)
        *(unsigned char*)(blk + 0x41) = 0;                // movb $0x0,0x41(%rbx)
    }
    return blk;                                           // mov %rbx,%rax
}

// 0x1417c8370 - the 0x28 node: three words, one qword from the argument, the flag byte at +0x20
// and a cleared +0x21.
void* SynAccNew28Node_1417c8370(void* pUnused, void* p2, void* p3, void* p4,
                                const void* pArg5, unsigned char uFlag) {
    (void)pUnused;
    int64_t frame = -2; (void)frame;                      // movq $0xfffffffffffffffe,0x28(%rsp)
    unsigned char* blk = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) blk = (unsigned char*)g_pfnSynNew_1417f3166(0x28);
    if (blk != nullptr) {                                 // test %rax,%rax / je
        *(void**)(blk) = p2;                              // mov %rsi,(%rax)
        *(void**)(blk + 8) = p3;                          // mov %rdi,0x8(%rax)
        *(void**)(blk + 0x10) = p4;                       // mov %rbx,0x10(%rax)
        *(void**)(blk + 0x18) = *(void**)pArg5;           // mov (%rax),%rcx / mov %rcx,0x18(%r11)
        *(unsigned char*)(blk + 0x20) = uFlag;            // mov %al,0x20(%r11)
        *(unsigned char*)(blk + 0x21) = 0;                // movb $0x0,0x21(%r11)
    }
    return blk;                                           // mov %r11,%rax
}

// 0x1417c84d0 - the zeroed 0x30 node: three cleared slots, colour 1 at +0x28, +0x29 cleared.
// The two 0x20(%rsp) markers (1 then 2) are spilled before each of the +0x8 and +0x10 stores;
// they are dead afterwards, so they are kept here as locals and nothing reads them.
void* SynAccNew30Zero_1417c84d0() {
    int64_t marker = -2; (void)marker;
    unsigned char* b = (unsigned char*)(g_pfnSynNew_1417f3166 != nullptr
                                        ? g_pfnSynNew_1417f3166(0x30) : nullptr);
    if (b != nullptr) *(void**)b = nullptr;                  // xor %ecx,%ecx / mov %rcx,(%rax)
    { uint32_t m = 1; (void)m; }                             // movl bashx1,0x20(%rsp)
    if (b + 8 != nullptr) *(void**)(b + 8) = nullptr;         // lea 0x8(%rax),%rdx / test / mov
    { uint32_t m = 2; (void)m; }                             // movl bashx2,0x20(%rsp)
    if (b + 0x10 != nullptr) *(void**)(b + 0x10) = nullptr;   // lea 0x10(%rax),%rdx / test / mov
    if (b != nullptr) { b[0x28] = 1; b[0x29] = 0; }           // movb bashx1,0x28 / movb bashx0,0x29
    return b;
}

// 0x1417c8530 - the same body for the 0x48 node: the pair of bytes sits at +0x40 / +0x41.
void* SynAccNew48Zero_1417c8530() {
    int64_t marker = -2; (void)marker;
    unsigned char* b = (unsigned char*)(g_pfnSynNew_1417f3166 != nullptr
                                        ? g_pfnSynNew_1417f3166(0x48) : nullptr);
    if (b != nullptr) *(void**)b = nullptr;
    { uint32_t m = 1; (void)m; }
    if (b + 8 != nullptr) *(void**)(b + 8) = nullptr;
    { uint32_t m = 2; (void)m; }
    if (b + 0x10 != nullptr) *(void**)(b + 0x10) = nullptr;
    if (b != nullptr) { b[0x40] = 1; b[0x41] = 0; }
    return b;
}

// 0x1417c8590 - the zeroed 0x28 node: three slots cleared, colour 1 at +0x20, +0x21 cleared.
void* SynAccNew28Zero_1417c8590() {
    int64_t marker = -2; (void)marker;                    // movq $0xfffffffffffffffe,0x28(%rsp)
    unsigned char* b = (unsigned char*)(g_pfnSynNew_1417f3166 ? g_pfnSynNew_1417f3166(0x28) : nullptr);
    int64_t zero = 0; (void)zero;                          // xor %ecx,%ecx
    if (b != nullptr) *(void**)b = nullptr;                // mov %rcx,(%rax) / jmp
    int32_t spill1 = 1; (void)spill1;                      // movl $0x1,0x20(%rsp)
    if (b + 8 != nullptr) *(void**)(b + 8) = nullptr;      // lea 0x8(%rax),%rdx / test / mov
    int32_t spill2 = 2; (void)spill2;                      // movl $0x2,0x20(%rsp)
    if (b + 0x10 != nullptr) *(void**)(b + 0x10) = nullptr;
    b[0x20] = 1;                                           // movb $0x1,0x20(%rax)
    b[0x21] = 0;                                           // movb $0x0,0x21(%rax)
    return b;
}

// 0x1417c8620 - the zeroed 0x30 node: the same three slots, its pair at +0x28.
void* SynAccNew30Zero2_1417c8620() {
    int64_t marker = -2; (void)marker;
    unsigned char* b = (unsigned char*)(g_pfnSynNew_1417f3166 ? g_pfnSynNew_1417f3166(0x30) : nullptr);
    int64_t zero = 0; (void)zero;
    if (b != nullptr) *(void**)b = nullptr;
    int32_t spill1 = 1; (void)spill1;
    if (b + 8 != nullptr) *(void**)(b + 8) = nullptr;
    int32_t spill2 = 2; (void)spill2;
    if (b + 0x10 != nullptr) *(void**)(b + 0x10) = nullptr;
    b[0x28] = 1;
    b[0x29] = 0;
    return b;
}

// 0x1417c8680 - the 0x30 node with both pair qwords from the fifth argument.
void* SynAccNew30Pair_1417c8680(void* pUnused, void* p2, void* p3, void* p4, const void* pPair, unsigned char uFlag) {
    (void)pUnused;
    int64_t marker = -2; (void)marker;
    unsigned char* b = (unsigned char*)(g_pfnSynNew_1417f3166 ? g_pfnSynNew_1417f3166(0x30) : nullptr);
    if (b != nullptr) {
        *(void**)b = p2;                                   // mov %rsi,(%rax)
        *(void**)(b + 8) = p3;                             // mov %rdi,0x8(%rax)
        *(void**)(b + 0x10) = p4;                          // mov %rbx,0x10(%rax)
        const unsigned char* src = (const unsigned char*)pPair;
        *(void**)(b + 0x18) = *(void**)src;                 // mov (%rcx),%rax / mov %rax,0x18(%r11)
        *(void**)(b + 0x20) = *(void**)(src + 8);           // mov 0x8(%rcx),%rax / mov %rax,0x20(%r11)
        b[0x28] = uFlag;                                    // movzbl 0x78(%rsp),%eax / mov %al,0x28(%r11)
        b[0x29] = 0;                                        // movb $0x0,0x29(%r11)
    }
    return b;
}

// 0x1417c8810 / 0x1417c8860 / 0x1417c88b0 - the eight-byte node that points back at its owner:
// the block is stored in the owner's first qword and the owner in the block's. A null answer from
// the allocator leaves that first qword zero.
void* SynAccSelf8_1417c8810(void* pThis) {
    int64_t marker = -2; (void)marker;                     // movq $0xfffffffffffffffe,0x20(%rsp)
    void* p = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) p = g_pfnSynNew_1417f3166(8);   // mov $0x8,%ecx / call
    if (p != nullptr) *(void**)p = pThis;                  // mov %rbx,(%rax) / jmp
    else p = nullptr;                                      // xor %eax,%eax
    *(void**)pThis = p;                                    // mov %rax,(%rbx)
    return pThis;                                          // mov %rbx,%rax
}

void* SynAccSelf8_1417c8860(void* pThis) {
    int64_t marker = -2; (void)marker;
    void* p = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) p = g_pfnSynNew_1417f3166(8);
    if (p != nullptr) *(void**)p = pThis;
    else p = nullptr;
    *(void**)pThis = p;
    return pThis;
}

void* SynAccSelf8_1417c88b0(void* pThis) {
    int64_t marker = -2; (void)marker;
    void* p = nullptr;
    if (g_pfnSynNew_1417f3166 != nullptr) p = g_pfnSynNew_1417f3166(8);
    if (p != nullptr) *(void**)p = pThis;
    else p = nullptr;
    *(void**)pThis = p;
    return pThis;
}

}  // namespace tq
