// Syndicate.dll — unit T4/D30 bodies (verbatim).
#include "SyndicateOwnTree.h"
#include "SyndicateCrossMerit.h"
#include <new>
#include <stdexcept>

namespace syndicate {

// the invalid-parameter seam (the past-the-end /
// the null-owner gates)
extern void (*g_fnMeritInvalid)();

// ---- FUN_14173bcb0 ----
// new 0x28; the zeroed links (the verbatim
// always-true slot-address checks); color@+0x20
// = 1 (black); _Isnil@+0x21 = 0 — the caller
// sets the head's flag. NOTE: the decompile
// elided the return; c580 consumes the node.
void* OwnAnchorAlloc() {
    char** puVar1 = (char**)operator new(0x28);
    if (puVar1 != nullptr) {
        *puVar1 = nullptr;
    }
    if ((char**)(puVar1 + 1) != nullptr) {
        puVar1[1] = nullptr;
    }
    if ((char**)(puVar1 + 2) != nullptr) {
        puVar1[2] = nullptr;
    }
    *(uint8_t*)(puVar1 + 4) = 1;   // +0x20 = 1
    *(uint8_t*)((char*)puVar1 + 0x21) = 0;
    return puVar1;
}

// ---- FUN_14173bd10 ----
void* OwnNodeAlloc(void* pLeft, void* pParent,
                   void* pRight, void* pKey,
                   uint8_t uColor) {
    char** puVar1 = (char**)operator new(0x28);
    if (puVar1 != nullptr) {
        *puVar1 = (char*)pLeft;
        puVar1[1] = (char*)pParent;
        puVar1[2] = (char*)pRight;
        *(uint64_t*)(puVar1 + 3) =
            *(uint64_t*)pKey;   // the qword copy
        *(uint8_t*)(puVar1 + 4) = uColor;
        *(uint8_t*)((char*)puVar1 + 0x21) = 0;
    }
    return puVar1;
}

// ---- FUN_14173bc60 ----
void OwnFreeRecurse(void* pMap, void* pNode) {
    char** param_2 = (char**)pNode;
    char cVar1 = *(char*)((char*)param_2 + 0x21);
    while (cVar1 == '\0') {
        OwnFreeRecurse(pMap,
            *(char**)(param_2 + 2));   // the right
        char** plVar2 = *(char***)param_2; // left
        g_fnMeritOpDelete((void*)param_2);
        param_2 = plVar2;
        cVar1 = *(char*)((char*)param_2 + 0x21);
    }
}

// ---- FUN_14173b240 ----
// the iterator++ (in-order successor); the state:
// {ptr@+0, the saved node@+8}
void OwnIterNext(void* pIterState) {
    char** param_1 = (char**)pIterState;
    if (*param_1 == nullptr) {
        g_fnMeritInvalid();
    }
    char* lVar2 = (char*)param_1[1];
    if (*(char*)(lVar2 + 0x21) == '\0') {
        char* plVar3 = *(char**)(lVar2 + 0x10);
        if (*(char*)(plVar3 + 0x21) != '\0') {
            // the right is nil: climb the parents
            char* lVar2b = *(char**)(lVar2 + 8);
            char cVar1 = *(char*)(lVar2b + 0x21);
            while ((cVar1 == '\0'
                && ((char*)param_1[1]
                    == *(char**)(lVar2b + 0x10)))) {
                param_1[1] = (char*)lVar2b;
                lVar2b = *(char**)(lVar2b + 8);
                cVar1 = *(char*)(lVar2b + 0x21);
            }
            param_1[1] = (char*)lVar2b;
            return;
        }
        // the leftmost of the right subtree
        char cVar1 = *(char*)(*(char**)plVar3 + 0x21);
        char* plVar4 = *(char**)plVar3;
        char* plVar3b = plVar3;
        while (cVar1 == '\0') {
            cVar1 =
                *(char*)(*(char**)plVar4 + 0x21);
            plVar3b = plVar4;
            plVar4 = *(char**)plVar4;
        }
        param_1[1] = (char*)plVar3b;
        return;
    }
    g_fnMeritInvalid();   // the past-the-end walk
}

// ---- FUN_14173c580 ----
void OwnMapCtor(void* pMap) {
    char* pc = (char*)pMap;
    char* lVar1 = (char*)OwnAnchorAlloc();
    *(char**)(pc + 0x30) = lVar1;
    *(uint8_t*)(lVar1 + 0x21) = 1;
    *(char**)(lVar1 + 8) = *(char**)(pc + 0x30);
    *(char**)lVar1 = *(char**)(pc + 0x30);
    *(char**)(lVar1 + 0x10) = *(char**)(pc + 0x30);
    *(uint64_t*)(pc + 0x38) = 0;
}

// ---- FUN_14173c470 ----
void OwnClear(void* pMap) {
    char* pc = (char*)pMap;
    char* pHead = *(char**)(pc + 0x30);
    char* plVar2 = *(char**)(pHead + 8);  // root
    char cVar1 = *(char*)(plVar2 + 0x21);
    while (cVar1 == '\0') {
        OwnFreeRecurse(pMap, *(char**)(plVar2 + 0x10));
        char* plVar3 = *(char**)plVar2;   // left
        g_fnMeritOpDelete((void*)plVar2);
        plVar2 = plVar3;
        cVar1 = *(char*)(plVar3 + 0x21);
    }
    // the head relinks + the size reset
    *(char**)(pHead + 8) = pHead;
    *(uint64_t*)(pc + 0x38) = 0;
    *(char**)pHead = pHead;
    *(char**)(pHead + 0x10) = pHead;
}

// ---- FUN_14173c5c0 ----
void* OwnInsert(void* pMap, void* pOutIter,
                uint8_t bLeft, void* pAttach,
                void* pKey) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pOutIter;
    char* param_4 = (char*)pAttach;
    char* pHead = *(char**)(pmap + 0x30);
    // the length gate
    if (0x1ffffffffffffffd
        < *(uint64_t*)(pmap + 0x38)) {
        throw std::length_error(
            "map/set<T> too long");
    }
    // the node alloc (color RED = 0); the children
    // point at the HEAD, the parent = the attach
    char** plVar5 = (char**)OwnNodeAlloc(
        pHead, param_4, pHead, pKey, 0);
    *(uint64_t*)(pmap + 0x38) =
        *(uint64_t*)(pmap + 0x38) + 1;
    if (param_4 == pHead) {
        // the empty-tree case: attach at the head
        *(char**)(pHead + 8) = (char*)plVar5;
        *(char**)pHead = (char*)plVar5;
        *(char**)(pHead + 0x10) = (char*)plVar5;
    } else if (bLeft == '\0') {
        *(char**)(param_4 + 0x10) = (char*)plVar5;
        if (param_4 == *(char**)(pHead + 0x10)) {
            *(char**)(pHead + 0x10) = (char*)plVar5;
        }
    } else {
        *(char**)param_4 = (char*)plVar5;
        if (param_4 == *(char**)pHead) {
            *(char**)pHead = (char*)plVar5;
        }
    }
    // the rebalance: plVar7 = &node->parent
    char** plVar7 = (char**)((char*)plVar5 + 8);
    char* plVar6 = (char*)plVar5;
    char cVar1 =
        *(char*)(*(char**)plVar7 + 0x20);
    while (cVar1 == '\0') {
        char* plVar2 = *(char**)plVar7;    // P
        char* plVar3 = *(char**)(plVar2 + 8); // G
        char* lVar4;
        if (plVar2 == *(char**)plVar3) {
            // P is G's LEFT child; U = G->right
            lVar4 = *(char**)(plVar3 + 0x10);
            if (*(char*)(lVar4 + 0x20) == '\0') {
                // the uncle is red: recolor
                *(char*)(plVar2 + 0x20) = 1;
                *(char*)(lVar4 + 0x20) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x20) = 0;
                plVar6 = *(char**)(
                    *(char**)plVar7 + 8);
            } else {
                if (plVar6
                    == *(char**)(plVar2 + 0x10)) {
                    // the inner-right case (b890 on P)
                    plVar6 = *(char**)(plVar2 + 0x10);
                    *(char**)(plVar2 + 0x10) =
                        *(char**)plVar6;
                    if (*(char*)(*(char**)plVar6
                        + 0x21) == '\0') {
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
                *(char*)(*(char**)plVar7 + 0x20) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x20) = 0;
                char* plG = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)plG;   // P (the left)
                *(char**)plG =
                    *(char**)(lVar4 + 0x10);
                if (*(char*)(*(char**)(lVar4 + 0x10)
                    + 0x21) == '\0') {
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
                    if (plG
                        == *(char**)(plVar2b + 0x10)) {
                        *(char**)(plVar2b + 0x10)
                            = lVar4;
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
            if (*(char*)(lVar4 + 0x20) == '\0') {
                *(char*)(plVar2 + 0x20) = 1;
                *(char*)(lVar4 + 0x20) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x20) = 0;
                plVar6 = *(char**)(
                    *(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)plVar2) {
                    // the inner-left case (b830 on P)
                    lVar4 = *(char**)plVar2;
                    *(char**)plVar2 =
                        *(char**)(lVar4 + 0x10);
                    if (*(char*)(*(char**)(lVar4 + 0x10)
                        + 0x21) == '\0') {
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
                *(char*)(*(char**)plVar7 + 0x20) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8)
                    + 0x20) = 0;
                char* plG = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)(plG + 0x10);
                *(char**)(plG + 0x10) = *(char**)lVar4;
                if (*(char*)(*(char**)lVar4 + 0x21)
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
        cVar1 = *(char*)(*(char**)plVar7 + 0x20);
    }
    // the root is always black
    *(char*)(*(char**)(pHead + 8) + 0x20) = 1;
    param_2[1] = (char*)plVar5;
    param_2[0] = *(char**)pmap;
    return param_2;
}

// ---- FUN_14173bf40 ----
// the double descent: out = {owner, the remember
// node (the exact-or-next from the first walk),
// owner, the second-walk node}
void* OwnDescendPair(void* pMap, void* pOut4,
                     uint32_t* pKey) {
    char* pc = (char*)pMap;
    char** param_2 = (char**)pOut4;
    char* pHead = *(char**)(pc + 0x30);
    // the first walk: lower_bound-style with the
    // strict-remember gate
    char* puVar4 = pHead;
    char* puVar5 = pHead;
    if (*(char*)(*(char**)(pHead + 8) + 0x21)
        == '\0') {
        char* puVar2 = *(char**)(pHead + 8);
        char* puVar3;
        do {
            if (*(uint32_t*)(puVar2 + 0x18)
                < *pKey) {
                puVar3 = *(char**)(puVar2 + 0x10);
            } else {
                if ((*(char*)(puVar4 + 0x21) != '\0')
                    && (*pKey
                        < *(uint32_t*)(puVar2 + 0x18))) {
                    puVar4 = puVar2;
                }
                puVar3 = *(char**)puVar2;
                puVar5 = puVar2;
            }
            puVar2 = puVar3;
        } while (*(char*)(puVar3 + 0x21) == '\0');
    }
    // the second walk: from the leftmost of puVar4
    // (the root when nothing remembered)
    char* puVar2;
    if (*(char*)(puVar4 + 0x21) == '\0') {
        puVar2 = *(char**)puVar4;
    } else {
        puVar2 = *(char**)(pHead + 8);
    }
    char* puVar3;
    if (*(char*)(puVar2 + 0x21) == '\0') {
        do {
            if (*pKey < *(uint32_t*)(puVar2 + 0x18)) {
                puVar3 = *(char**)puVar2;
                puVar4 = puVar2;
            } else {
                puVar3 = *(char**)(puVar2 + 0x10);
            }
            puVar2 = puVar3;
        } while (*(char*)(puVar3 + 0x21) == '\0');
    }
    uint64_t uVar1 = *(uint64_t*)pc;   // the anchor
    param_2[0] = (char*)uVar1;
    param_2[1] = puVar5;
    param_2[2] = (char*)uVar1;
    param_2[3] = puVar4;
    return param_2;
}

} // namespace syndicate
