// synrbrace.h — RAW Syndicate.dll v6159 · the out-of-line tree rotations.
// 0x141724c50 rotate_left, 0x141724cb0 rotate_right. Both take rcx = the container, rdx = the pivot, and
// both have three exits (the pivot was the root, it was its parent's left child, or its parent's right child).
// Transcribed from the listing; the head pointer lives at container+0x30, links at +0x00/+0x08/+0x10 and the
// nil marker at +0x1d.
#pragma once
#include <cstdint>

namespace tq {

#define RB_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define RB_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))

inline void SynRotateLeft_141724c50(void* pThis, void* pPivot) {   // 0x141724c50
    void* r8 = RB_Q(pPivot, 0x10);                       // r8 = pivot->right
    RB_Q(pPivot, 0x10) = RB_Q(r8, 0x00);                 // pivot->right = r8->left
    void* rax = RB_Q(r8, 0x00);
    if (RB_B(rax, 0x1d) == 0)                            // if r8->left is a real node
        RB_Q(rax, 0x08) = pPivot;                        //   its parent becomes the pivot
    RB_Q(r8, 0x08) = RB_Q(pPivot, 0x08);                 // r8->parent = pivot->parent
    rax = RB_Q(pThis, 0x30);                             // the head
    if (pPivot == RB_Q(rax, 0x08)) {                     // the pivot was the root
        RB_Q(rax, 0x08) = r8;
        RB_Q(r8, 0x00) = pPivot;
        RB_Q(pPivot, 0x08) = r8;
        return;
    }
    rax = RB_Q(pPivot, 0x08);                            // pivot->parent
    if (pPivot == RB_Q(rax, 0x00)) {                     // the pivot was the left child
        RB_Q(rax, 0x00) = r8;
        RB_Q(r8, 0x00) = pPivot;
        RB_Q(pPivot, 0x08) = r8;
        return;
    }
    RB_Q(rax, 0x10) = r8;                                // the pivot was the right child
    RB_Q(r8, 0x00) = pPivot;
    RB_Q(pPivot, 0x08) = r8;
}

inline void SynRotateRight_141724cb0(void* pThis, void* pPivot) {  // 0x141724cb0
    void* r8 = RB_Q(pPivot, 0x00);                       // r8 = pivot->left
    RB_Q(pPivot, 0x00) = RB_Q(r8, 0x10);                 // pivot->left = r8->right
    void* rax = RB_Q(r8, 0x10);
    if (RB_B(rax, 0x1d) == 0)
        RB_Q(rax, 0x08) = pPivot;
    RB_Q(r8, 0x08) = RB_Q(pPivot, 0x08);
    rax = RB_Q(pThis, 0x30);
    if (pPivot == RB_Q(rax, 0x08)) {
        RB_Q(rax, 0x08) = r8;
        RB_Q(r8, 0x10) = pPivot;
        RB_Q(pPivot, 0x08) = r8;
        return;
    }
    rax = RB_Q(pPivot, 0x08);
    if (pPivot == RB_Q(rax, 0x10)) {
        RB_Q(rax, 0x10) = r8;
        RB_Q(r8, 0x10) = pPivot;
        RB_Q(pPivot, 0x08) = r8;
        return;
    }
    RB_Q(rax, 0x00) = r8;
    RB_Q(r8, 0x10) = pPivot;
    RB_Q(pPivot, 0x08) = r8;
}

#undef RB_Q
#undef RB_B

}  // namespace tq
