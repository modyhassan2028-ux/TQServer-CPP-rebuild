#include "modules/syndicate/src/synrbfindoradd.h"
#include "modules/syndicate/src/synrbinsert_family.h"    // the transcribed 0x1417293c0
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"   // _invalid_parameter_noinfo seam

// The generated family header #undefs its accessors on the way out; these are the same two.
#define RB_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define RB_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))

namespace tq {

// ============================================================================
// 0x14172ae00 — find-or-insert. The walk is a lower bound: stay on a node whose key is greater
// than the search key and step left, otherwise step right, remembering the last real node (rdi)
// and which way the last step went (bpl).
//   14172ae2a root nil -> the tree is empty, rdi stays the header
//   14172ae40..47  setb: bpl = (key < node->key), unsigned
//   14172ae6f      bpl clear -> straight to the key check
//   14172ae94      rdi == header->left -> insert in front of everything, from the header
//   14172aed7..af58 the "arrived from the left" fixup: the candidate becomes the in-order
//                   predecessor, rdi stays the node the walk stopped on (it is the hint handed
//                   to 0x1417293c0, not the running candidate)
//   14172af60      candidate->key >= key -> the key is already there, answer false
void* Slot_14172ae00(void* pThis, void* pOutIter, const uint32_t* pKey) {
    void* pHeader = RB_Q(pThis, 0x30);                        // 14172ae16
    void* pNode = RB_Q(pHeader, 0x8);                         // 14172ae20, the root
    uint8_t bLeft = 1;                                        // 14172ae27 mov $0x1,%bpl
    void* pParent = pHeader;                                  // rdi

    if (RB_B(pNode, 0x1d) == 0) {                             // 14172ae2a
        const uint32_t uKey = *(const uint32_t*)pKey;         // 14172ae30
        do {
            pParent = pNode;                                  // 14172ae44 mov %rax,%rdi
            bLeft = (uint8_t)(uKey < *(const uint32_t*)((uint8_t*)pNode + 0x18));   // 14172ae40..47
            pNode = bLeft ? RB_Q(pNode, 0x0) : RB_Q(pNode, 0x10);                   // 14172ae4b..55
        } while (RB_B(pNode, 0x1d) == 0);                     // 14172ae59
    }

    void* const pIterWord = RB_Q(pThis, 0x0);                  // 14172ae5f
    void* aPos[2] = { pIterWord, pParent };                    // 14172ae65/ae6a, [rsp+0x30]

    // The shared insert tail: 0x1417293c0(this, &pos, bLeft, hint, key), then the pair.
    const auto do_insert = [&](uint8_t bLeftArg) -> void* {
        void* pRes = SynRbInsert_1417293c0(pThis, aPos, bLeftArg, pParent, pKey);   // 14172aea9..aeb1
        RB_B(pOutIter, 0x10) = 1;                             // 14172aeb6
        RB_Q(pOutIter, 0x0) = RB_Q(pRes, 0x0);                // 14172aebc..aec3
        RB_Q(pOutIter, 0x8) = RB_Q(pRes, 0x8);                // 14172af8c/af99
        return pOutIter;                                      // 14172af9e mov %r12,%rax
    };

    if (bLeft != 0) {                                         // 14172ae6f test %bpl,%bpl
        void* pLeftmost = RB_Q(RB_Q(pThis, 0x30), 0x0);       // 14172ae78..ae81
        if (pIterWord == nullptr)                             // 14172ae84 test %rsi,%rsi
            g_pfn_invalid_parameter_noinfo();                 // 14172ae8e
        // 14172ae89 cmp %rsi,%rsi compares the word with itself: that call can never be taken
        if (pParent == pLeftmost)                             // 14172ae94 cmp %r13,%rdi
            return do_insert(1);                              // 14172ae9e..aec7, r8b = 1

        void* pHint = pParent;                                // rbx
        if (RB_B(pHint, 0x1d) != 0) {                         // 14172aed7
            void* pRight = RB_Q(pHint, 0x10);                 // 14172aedd
            aPos[1] = pRight;                                 // 14172aee1 [rsp+0x38]
            if (RB_B(pRight, 0x1d) == 0) {                    // 14172aee6
                /* the right child is a real node: it is the candidate */ ;
            } else {
                g_pfn_invalid_parameter_noinfo();             // 14172aeec
            }
        } else {
            void* pChild = RB_Q(pHint, 0x0);                  // 14172aef4 mov (%rdi),%rax
            if (RB_B(pChild, 0x1d) == 0) {                    // 14172aef7
                pHint = pChild;                               // 14172aefd mov %rax,%rbx
                void* pNext = RB_Q(pChild, 0x10);             // 14172af00
                while (RB_B(pNext, 0x1d) == 0) {              // 14172af08..af1b
                    pHint = pNext;
                    pNext = RB_Q(pNext, 0x10);
                }
                aPos[1] = pHint;                              // 14172af1d
            } else {
                void* pUp = RB_Q(pHint, 0x8);                 // 14172af24
                if (RB_B(pUp, 0x1d) == 0) {                   // 14172af28
                    while (pHint == RB_Q(pUp, 0x0)) {         // 14172af30..af33 cmp (%rax),%rbx
                        pHint = pUp;                          // 14172af35 mov %rax,%rbx
                        aPos[1] = pUp;                        // 14172af38 [rsp+0x38]
                        pUp = RB_Q(pUp, 0x8);                 // 14172af3d
                        if (RB_B(pUp, 0x1d) != 0) break;      // 14172af41
                    }
                }
                if (RB_B(pHint, 0x1d) != 0) {                 // 14172af47
                    g_pfn_invalid_parameter_noinfo();         // 14172af4d
                } else {
                    pHint = pUp;                              // 14172af55
                    aPos[1] = pUp;                            // 14172af58
                }
            }
        }
    }

    const uint32_t uKey2 = *(const uint32_t*)pKey;             // 14172af5d mov (%r14),%eax
    void* pHint = aPos[1];                                     // rbx at the key check
    if (*(const uint32_t*)((const uint8_t*)pHint + 0x18) >= uKey2) {   // 14172af60..af63 jae
        RB_B(pOutIter, 0x10) = 0;                             // 14172af7b
        RB_Q(pOutIter, 0x0) = aPos[0];                        // 14172af81..af84
        RB_Q(pOutIter, 0x8) = aPos[1];                        // 14172af88..af99
        return pOutIter;                                      // 14172af9e
    }
    return do_insert(bLeft);                                  // 14172af65..af71, r8d = movzbl %bpl
}

}  // namespace tq
