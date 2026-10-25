// Syndicate.dll — unit T3/D29 bodies (verbatim).
#include "SyndicateMapTree.h"
#include "SyndicateCrossMerit.h"
#include <new>
#include <stdexcept>

// the head's root slot at +8
#define HEADROOT(h) (*(char**)((char*)(h) + 8))

namespace syndicate {

// the string-move seam for the node value
// (14173de50, bound by the test kit)
extern void (*g_fnStrMoveDE50)(void* d, void* s);

// the orphan unwind seam (14173cb90)
extern void (*g_fnOrphanCB90)(void* o, void* out,
    void* a, void* b);

// ---- FUN_14173bc00 ----
// operator_new(0x68); the zeroed links; color@+0x60
// = 1 (black); _Isnil@+0x61 = 0 (the caller sets
// the head's flag)
void* TreeNodeAlloc() {
    char** puVar1 = (char**)operator new(0x68);
    if (puVar1 != nullptr) {
        *puVar1 = nullptr;
    }
    if ((char**)(puVar1 + 1) != nullptr) {
        puVar1[1] = nullptr;
    }
    if ((char**)(puVar1 + 2) != nullptr) {
        puVar1[2] = nullptr;
    }
    *(uint8_t*)(puVar1 + 0xc) = 1;   // +0x60 = 1
    *(uint8_t*)((char*)puVar1 + 0x61) = 0;
    return puVar1;
}

// ---- FUN_14173e1a0 ----
void* TreeNodeAllocKey(void* pLeft, void* pParent,
                      void* pRight, uint32_t* pKeyVal,
                      uint8_t uColor) {
    char** puVar1 = (char**)operator new(0x68);
    if (puVar1 != nullptr) {
        *puVar1 = (char*)pLeft;
        puVar1[1] = (char*)pParent;
        puVar1[2] = (char*)pRight;
        *(uint32_t*)(puVar1 + 3) = *pKeyVal;
        g_fnStrMoveDE50(puVar1 + 4, pKeyVal + 2);
        *(uint8_t*)(puVar1 + 0xc) = uColor;
        *(uint8_t*)((char*)puVar1 + 0x61) = 0;
    }
    return puVar1;
}

// ---- FUN_14173b830 ----
// the rotation on the node's RIGHT child
void TreeRotateR(void* pMap, void* pNode) {
    char* pc = (char*)pNode;
    // the map head via map+0x30
    char* pmap = (char*)pMap;
    char** head = *(char***)(pmap + 0x30);
    char** plVar1 = *(char***)(pc + 0x10);
    // node->right = right->left
    *(char***)(pc + 0x10) = *(char***)plVar1;
    if (*(char*)(*plVar1 + 0x61) == '\0') {
        *(char**)(*plVar1 + 8) = (char*)pc;
    }
    // right->parent = node->parent
    plVar1[1] = *(char**)(pc + 8);
    if ((char*)pc == HEADROOT(head)) {
        // node was the root
        HEADROOT(head) = (char*)plVar1;
        *plVar1 = (char*)pc;
        *(char***)(pc + 8) = (char**)plVar1;
        return;
    }
    char** plVar2 = *(char***)(pc + 8);
    if ((char**)pc == *(char***)plVar2) {
        // node was the left child
        *(char**)plVar2 = (char*)plVar1;
        *plVar1 = (char*)pc;
        *(char***)(pc + 8) = (char**)plVar1;
        return;
    }
    plVar2[2] = (char*)plVar1;
    *plVar1 = (char*)pc;
    *(char***)(pc + 8) = (char**)plVar1;
}

// ---- FUN_14173b890 ----
// the rotation on the node's LEFT child
void TreeRotateL(void* pMap, void* pNode) {
    char* pc = (char*)pNode;
    char* pmap = (char*)pMap;
    char** head = *(char***)(pmap + 0x30);
    char* lVar1 = *(char**)pc;    // the left child
    // node->left = left->right
    *(char**)pc = *(char**)(lVar1 + 0x10);
    if (*(char*)(*(char**)(lVar1 + 0x10) + 0x61)
        == '\0') {
        *(char**)(*(char**)(lVar1 + 0x10) + 8) = pc;
    }
    // left->parent = node->parent
    *(char**)(lVar1 + 8) = *(char**)(pc + 8);
    if ((char*)pc == HEADROOT(head)) {
        // node was the root
        HEADROOT(head) = lVar1;
        *(char**)(lVar1 + 0x10) = pc;
        *(char**)(pc + 8) = lVar1;
        return;
    }
    char** plVar2 = *(char***)(pc + 8);
    if ((char**)pc == *(char***)(plVar2 + 2)) {
        // node was the right child
        plVar2[2] = lVar1;
        *(char**)(lVar1 + 0x10) = pc;
        *(char**)(pc + 8) = lVar1;
        return;
    }
    *(char**)plVar2 = lVar1;
    *(char**)(lVar1 + 0x10) = pc;
    *(char**)(pc + 8) = lVar1;
}

// ---- FUN_14173b6c0 ----
// the iterator++ (in-order successor) with the
// debug checks; the iterator state: ptr@+0,
// the saved node@+8
void TreeIterNext(void* pIterState) {
    char* pc = (char*)pIterState;
    char** param_1 = (char**)pc;
    if (*param_1 == nullptr) {
        g_fnMeritInvalid();
    }
    char* lVar2 = param_1[1];    // the saved node
    if (*(char*)(lVar2 + 0x61) == '\0') {
        // has a successor in the right subtree?
        char* plVar3 = *(char**)(lVar2 + 0x10);
        if (*(char*)(plVar3 + 0x61) != '\0') {
            // climb until not-the-right-child
            char* lVar2b = *(char**)(lVar2 + 8);
            char cVar1 =
                *(char*)(lVar2b + 0x61);
            while ((cVar1 == '\0'
                && (param_1[1]
                    == *(char**)(lVar2b + 0x10)))) {
                param_1[1] = lVar2b;
                lVar2b = *(char**)(lVar2b + 8);
                cVar1 = *(char*)(lVar2b + 0x61);
            }
            param_1[1] = lVar2b;
            return;
        }
        // leftmost of the right subtree
        char* plVar4 = *(char**)plVar3;
        char cVar1 = *(char*)(plVar4 + 0x61);
        char* plVar3b = plVar3;
        while (cVar1 == '\0') {
            cVar1 =
                *(char*)(*(char**)plVar4 + 0x61);
            plVar3b = plVar4;
            plVar4 = *(char**)plVar4;
        }
        param_1[1] = plVar3b;
        return;
    }
    g_fnMeritInvalid();   // the past-the-end walk
}

// ---- FUN_14173e240 ----
// the recursive clear (the string dtor seam via
// the orphan call + the node deletes)
void TreeClearNodes(void* pMap, void* pNode) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pNode;
    char cVar2 = *(char*)((char*)param_2 + 0x61);
    while (cVar2 == '\0') {
        TreeClearNodes(pmap, *(char**)(param_2 + 2));
        // the recursion takes the RIGHT child;
        // the left is cleared by the reentry
        char* plVar3 = *(char**)param_2;
        char** plVar1 = param_2 + 4;   // +0x20
        char** puStack_30 =
            *(char***)(param_2 + 10);  // +0x50
        int64_t local_38 = (int64_t)*plVar1;
        void* uStack_20 = (void*)*puStack_30;
        int64_t local_28 = local_38;
        g_fnOrphanCB90(plVar1, nullptr,
            &local_28, &local_38);
        g_fnMeritOpDelete(*(void**)(param_2 + 10));
        param_2[10] = nullptr;
        param_2[0xb] = nullptr;
        g_fnMeritOpDelete((void*)*plVar1);
        g_fnMeritOpDelete(param_2);
        param_2 = (char**)plVar3;
        cVar2 = *(char*)((char*)param_2 + 0x61);
    }
}

// ---- FUN_14173d1e0 ----
// the find: out[0] = the anchor, out[1] =
// the first node >= the key (the head if none)
void* TreeFind(void* pMap, void* pOut,
                     uint32_t* pKey) {
    char* pc = (char*)pMap;
    char** param_2 = (char**)pOut;
    char* puVar4 = *(char**)(pc + 0x30);   // head
    if (*(char*)(*(char**)(puVar4 + 8)
        + 0x61) == '\0') {
        char* puVar1 = *(char**)(puVar4 + 8);
        char* puVar2;
        do {
            if (*(uint32_t*)(puVar1 + 0x18)
                < *pKey) {
                puVar2 = *(char**)(puVar1 + 0x10);
            } else {
                puVar2 = *(char**)puVar1;
                puVar4 = puVar1;
            }
            puVar1 = puVar2;
        } while (*(char*)(puVar2 + 0x61) == '\0');
    }
    char* puVar1 = *(char**)(pc + 0x30);
    // the iterator pair {owner-anchor, node}
    char* lpair[2] = { *(char**)pc, puVar4 };
    char* plVar3;
    if (lpair[0] == nullptr) {
        g_fnMeritInvalid();
    }
    if ((puVar4 == puVar1)
        || (*pKey < *(uint32_t*)(puVar4 + 0x18))) {
        // not found — the end iterator {anchor,
        // head}
        lpair[0] = *(char**)pc;
        lpair[1] = *(char**)(pc + 0x30);
        plVar3 = (char*)lpair;
    } else {
        plVar3 = (char*)lpair;
    }
    param_2[0] = ((char**)plVar3)[0];
    param_2[1] = ((char**)plVar3)[1];
    return param_2;
}

// ---- FUN_14173e790 ----
// the insert + the red-black rebalance
void* TreeInsert(void* pMap, void* pOutIter,
                 uint8_t bLeft, void* pAttach,
                 uint32_t* pKeyVal) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pOutIter;
    char* param_4 = (char*)pAttach;
    char* pHead = *(char**)(pmap + 0x30);
    // the length gate
    if (0x38e38e38e38e38c
        < *(uint64_t*)(pmap + 0x38)) {
        throw std::length_error(
            "map/set<T> too long");
    }
    // the node alloc (color RED = 0): the children
    // point at the HEAD (the MSVC leaf
    // convention), the parent = the attach node
    char* plVar5 = (char*)TreeNodeAllocKey(
        pHead, param_4, pHead, pKeyVal, 0);
    *(uint64_t*)(pmap + 0x38) =
        *(uint64_t*)(pmap + 0x38) + 1;
    if (param_4 == pHead) {
        // the empty-tree case: attach at the head
        *(char**)(pHead + 8) = plVar5;   // root
        *(char**)pHead = plVar5;         // first
        *(char**)(pHead + 0x10) = plVar5; // last
    } else if (bLeft == '\0') {
        // the attach's RIGHT child
        *(char**)(param_4 + 0x10) = plVar5;
        if (param_4 == *(char**)(pHead + 0x10)) {
            *(char**)(pHead + 0x10) = plVar5;
        }
    } else {
        // the attach's LEFT child
        *(char**)param_4 = plVar5;
        if (param_4 == *(char**)pHead) {
            *(char**)pHead = plVar5;
        }
    }
    // the rebalance: plVar7 = &node->parent
    char** plVar7 = (char**)(plVar5 + 8);
    char* plVar6 = plVar5;
    char cVar1 =
        *(char*)(*(char**)plVar7 + 0x60);
    while (cVar1 == '\0') {
        char* plVar2 = *(char**)plVar7;    // P
        char* plVar3 = *(char**)(plVar2 + 8); // G
        char* lVar4;
        if (plVar2 == *(char**)plVar3) {
            // P is G's LEFT child; U = G->right
            // (the original: plVar3[2])
            lVar4 = *(char**)(plVar3 + 0x10);
            if (*(char*)(lVar4 + 0x60) == '\0') {
                // the uncle is red: recolor
                *(char*)(plVar2 + 0x60) = 1;
                *(char*)(lVar4 + 0x60) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x60) = 0;
                plVar6 = *(char**)(
                    *(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)(plVar2 + 0x10)) {
                    // the inner-right case: rotate P
                    // left around the node (b890 on P)
                    plVar6 = *(char**)(plVar2 + 0x10);
                    *(char**)(plVar2 + 0x10) =
                        *(char**)plVar6;
                    if (*(char*)(*(char**)plVar6
                        + 0x61) == '\0') {
                        *(char**)(*(char**)plVar6 + 8)
                            = plVar2;
                    }
                    plVar7 = (char**)(plVar2 + 8);
                    *(char**)(plVar6 + 8) =
                        *(char**)plVar7;
                    if (plVar2
                        == *(char**)(pHead + 8)) {
                        *(char**)(pHead + 8) = plVar6;
                    } else {
                        char* plVar3b = *(char**)plVar7;
                        if (plVar2
                            == *(char**)plVar3b) {
                            *(char**)plVar3b = plVar6;
                        } else {
                            *(char**)(plVar3b + 0x10)
                                = plVar6;
                        }
                    }
                    *(char**)plVar6 = plVar2;
                    *(char**)plVar7 = plVar6;
                    plVar6 = plVar2;
                }
                // recolor + rotate G right (b890)
                *(char*)(*(char**)plVar7 + 0x60) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x60) = 0;
                char* plG = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)plG;   // P (the left)
                *(char**)plG =
                    *(char**)(lVar4 + 0x10);
                if (*(char*)(*(char**)(lVar4 + 0x10)
                    + 0x61) == '\0') {
                    *(char**)(*(char**)(lVar4 + 0x10)
                        + 8) = plG;
                }
                *(char**)(lVar4 + 8) =
                    *(char**)(plG + 8);
                if (plG == *(char**)(pHead + 8)) {
                    *(char**)(pHead + 8) = lVar4;
                } else {
                    char* plVar2b =
                        *(char**)(plG + 8);
                    if (plG == *(char**)(plVar2b + 0x10)) {
                        *(char**)(plVar2b + 0x10) = lVar4;
                    } else {
                        *(char**)plVar2b = lVar4;
                    }
                }
                *(char**)(lVar4 + 0x10) = plG;
                *(char**)(plG + 8) = lVar4;
            }
        } else {
            // P is G's RIGHT child; U = G->left
            lVar4 = *(char**)plVar3;
            if (*(char*)(lVar4 + 0x60) == '\0') {
                *(char*)(plVar2 + 0x60) = 1;
                *(char*)(lVar4 + 0x60) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x60) = 0;
                plVar6 = *(char**)(
                    *(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)plVar2) {
                    // the inner-left case: rotate P
                    // right around the node (b830 on P)
                    lVar4 = *(char**)plVar2;
                    *(char**)plVar2 =
                        *(char**)(lVar4 + 0x10);
                    if (*(char*)(*(char**)(lVar4 + 0x10)
                        + 0x61) == '\0') {
                        *(char**)(*(char**)(lVar4 + 0x10)
                            + 8) = plVar2;
                    }
                    plVar7 = (char**)(plVar2 + 8);
                    *(char**)(lVar4 + 8) =
                        *(char**)plVar7;
                    if (plVar2
                        == *(char**)(pHead + 8)) {
                        *(char**)(pHead + 8) = lVar4;
                    } else {
                        char* plVar6b = *(char**)plVar7;
                        if (plVar2
                            == *(char**)(plVar6b + 0x10)) {
                            *(char**)(plVar6b + 0x10)
                                = lVar4;
                        } else {
                            *(char**)plVar6b = lVar4;
                        }
                    }
                    *(char**)(lVar4 + 0x10) = plVar2;
                    *(char**)plVar7 = lVar4;
                    plVar6 = plVar2;
                }
                // recolor + rotate G left (b830)
                *(char*)(*(char**)plVar7 + 0x60) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x60) = 0;
                char* plG = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)(plG + 0x10);
                *(char**)(plG + 0x10) = *(char**)lVar4;
                if (*(char*)(*(char**)lVar4 + 0x61)
                    == '\0') {
                    *(char**)(*(char**)lVar4 + 8) = plG;
                }
                *(char**)(lVar4 + 8) =
                    *(char**)(plG + 8);
                if (plG == *(char**)(pHead + 8)) {
                    *(char**)(pHead + 8) = lVar4;
                } else {
                    char* plVar2b =
                        *(char**)(plG + 8);
                    if (plG == *(char**)plVar2b) {
                        *(char**)plVar2b = lVar4;
                    } else {
                        *(char**)(plVar2b + 0x10)
                            = lVar4;
                    }
                }
                *(char**)lVar4 = plG;
                *(char**)(plG + 8) = lVar4;
            }
        }
        plVar7 = (char**)(plVar6 + 8);
        cVar1 = *(char*)(*(char**)plVar7 + 0x60);
    }
    // the root is always black
    *(char*)(*(char**)(pHead + 8) + 0x60) = 1;
    param_2[1] = plVar5;
    param_2[0] = *(char**)pmap;
    return param_2;
}

} // namespace syndicate
