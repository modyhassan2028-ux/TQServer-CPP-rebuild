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

}  // namespace tq
