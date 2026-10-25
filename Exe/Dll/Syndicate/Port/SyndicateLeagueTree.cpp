// Syndicate.dll — unit T6/D32 bodies (verbatim).
#include "SyndicateLeagueTree.h"
#include "SyndicateCrossMerit.h"
#include <new>
#include <stdexcept>

namespace syndicate {

// the free / invalid seams (the established test
// binding; production binds them to the CRT)
extern void* (*g_fnMeritOpNew)(size_t);
extern void (*g_fnMeritOpDelete)(void*);
extern void (*g_fnMeritInvalid)();

// ================= FUN_141746790 =================
// new 0x30; left/parent/right; the 16-byte key pair
// copy (+0x18, +0x20); color@+0x28; _Isnil@+0x29 = 0
void* LeagueNodeAlloc(void* pLeft, void* pParent,
                      void* pRight, void* pKey,
                      uint8_t uColor) {
    char** puVar1 = (char**)operator new(0x30);
    if (puVar1 != nullptr) {
        puVar1[0] = (char*)pLeft;
        puVar1[1] = (char*)pParent;
        puVar1[2] = (char*)pRight;
        *(uint64_t*)(puVar1 + 3) =
            *(uint64_t*)pKey;         // +0x18
        *(uint64_t*)(puVar1 + 4) =
            *((uint64_t*)pKey + 1);   // +0x20
        *(uint8_t*)(puVar1 + 5) = uColor;   // +0x28
        *(uint8_t*)((char*)puVar1 + 0x29) = 0;
    }
    return puVar1;
}

// ================= FUN_141746a60 =================
// new 0x30; the zeroed links (the verbatim
// always-true slot-address checks); color@+0x28 =
// 1 (black); _Isnil@+0x29 = 0 — the caller (c4b0)
// sets the head's flag. NOTE: the decompile elided
// the return; c4b0 consumes the node.
void* LeagueHeadAlloc() {
    char** puVar1 = (char**)operator new(0x30);
    if (puVar1 != nullptr) {
        *puVar1 = nullptr;
    }
    if ((char**)(puVar1 + 1) != nullptr) {
        puVar1[1] = nullptr;
    }
    if ((char**)(puVar1 + 2) != nullptr) {
        puVar1[2] = nullptr;
    }
    *(uint8_t*)(puVar1 + 5) = 1;   // +0x28 = black
    *(uint8_t*)((char*)puVar1 + 0x29) = 0;
    return puVar1;
}

// ================= FUN_14174c4b0 =================
// the member map ctor: the anchor (new 8, the owner
// back-ref) + the head (the isnil flag = 1 set HERE
// after the alloc) + the self-links + size 0
void* LeagueMemberCtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char** puVar1 = (char**)operator new(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *puVar1 = (char*)param_1;   // the owner back-ref
    }
    *param_1 = (char*)puVar1;   // map+0 = the anchor
    char* lVar2 = (char*)LeagueHeadAlloc();
    param_1[6] = (char*)lVar2;   // map+0x30 = head
    *(uint8_t*)(lVar2 + 0x29) = 1;   // the head flag
    *(char**)(lVar2 + 8) = lVar2;   // parent
    *(char**)lVar2 = lVar2;         // left
    *(char**)(lVar2 + 0x10) = lVar2; // right
    param_1[7] = 0;   // map+0x38 = size
    return param_1;
}

// ================= FUN_141749fc0 =================
// the lower_bound descent (u32@+0x18) + the
// found/end output iter
void* LeagueFind(void* pMap, void* pOutIter,
                 uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    uint32_t* param_3 = pKey;
    char* puVar4 = (char*)param_1[6];
    char* puVar1;
    if (*(char*)(*(char**)(puVar4 + 8) + 0x29)
        == '\0') {
        puVar1 = *(char**)(puVar4 + 8);   // the root
        do {
            if (*(uint32_t*)(puVar1 + 0x18)
                < *param_3) {
                puVar1 = *(char**)(puVar1 + 0x10);
            } else {
                puVar4 = puVar1;   // the remember
                puVar1 = *(char**)puVar1;
            }
        } while (*(char*)(puVar1 + 0x29) == '\0');
    }
    char* puVar1b = (char*)param_1[6];
    // local_20 = the remember; local_28 = anchor
    char* local_20 = puVar4;
    if (*param_1 == nullptr) {
        g_fnMeritInvalid();
    }
    char* local_28[2];
    local_28[0] = *(char**)param_1;
    local_28[1] = local_20;
    char* local_18[2];
    char** plVar3;
    if ((puVar4 == puVar1b)
        || (*param_3
            < *(uint32_t*)(puVar4 + 0x18))) {
        // the end: {anchor, head}
        plVar3 = local_18;
        local_18[0] = *(char**)param_1;
        local_18[1] = param_1[6];
    } else {
        plVar3 = local_28;
    }
    param_2[0] = *(char**)plVar3;
    param_2[1] = plVar3[1];
    return param_2;
}

// ================= FUN_141748820 =================
// the insert + the red-black rebalance (the length
// gate at 0xffffffffffffffd, the D29 leaf convention:
// the new node's children point at the head)
void* LeagueInsert(void* pMap, void* pOutIter,
                   uint8_t bLeft, void* pAttach,
                   void* pKey) {
    char* pmap = (char*)pMap;
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char param_3 = (char)bLeft;
    char* param_4 = (char*)pAttach;
    char* head = *(char**)(pmap + 0x30);
    char* sizeSlot = pmap + 0x38;
    if (0xffffffffffffffdULL
        < *(uint64_t*)sizeSlot) {
        throw std::length_error(
            "map/set<T> too long");
    }
    char* plVar5 = (char*)LeagueNodeAlloc(
        (void*)head,        // left = head
        (void*)param_4,     // parent = attach
        (void*)head,        // right = head
        pKey, 0);           // red
    *(uint64_t*)sizeSlot = *(uint64_t*)sizeSlot + 1;
    if (param_4 == head) {
        // the first node: the root
        *(char**)(head + 8) = plVar5;   // root
        *(char**)head = plVar5;         // first
        *(char**)(head + 0x10) = plVar5; // last
    } else if (param_3 == '\0') {
        *(char**)(param_4 + 0x10) = plVar5; // R
        if (param_4 == *(char**)(head + 0x10)) {
            *(char**)(head + 0x10) = plVar5;
        }
    } else {
        *(char**)param_4 = plVar5;      // L
        if (param_4 == *(char**)head) {
            *(char**)head = plVar5;
        }
    }
    // the rebalance: P = node->parent
    char* plVar7 = plVar5 + 8;
    char cVar1 = *(char*)(*(char**)plVar7 + 0x28);
    char* plVar6 = plVar5;
    char* plVar2 = nullptr;
    char* plVar3 = nullptr;
    char* lVar4 = nullptr;
    while (cVar1 == '\0') {
        plVar2 = *(char**)plVar7;       // the parent
        plVar3 = *(char**)(plVar2 + 8); // the grand
        if (plVar2 == *(char**)plVar3) {
            // the parent IS the grand's LEFT: the
            // uncle = the grand's right
            lVar4 = *(char**)(plVar3 + 0x10);
            if (*(char*)(lVar4 + 0x28) == '\0') {
                // the uncle RED: recolor + climb
                *(char*)(plVar2 + 0x28) = 1;
                *(char*)(lVar4 + 0x28) = 1;
                *(char*)(*(char**)(*(char**)plVar7
                    + 8) + 0x28) = 0;
                plVar6 = *(char**)(*(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)(plVar2 + 0x10)) {
                    // the inner rotation (the LEFT-lift
                    // on the parent)
                    plVar6 = *(char**)(plVar2 + 0x10);
                    *(char**)(plVar2 + 0x10) =
                        *(char**)plVar6;
                    if (*(char*)(*(char**)plVar6 + 0x29)
                        == '\0') {
                        *(char**)(*(char**)plVar6 + 8) = plVar2;
                    }
                    plVar7 = plVar2 + 8;
                    *(char**)(plVar6 + 8) = *(char**)plVar7;
                    if (plVar2 == *(char**)(head + 8)) {
                        *(char**)(head + 8) = plVar6;
                    } else {
                        plVar3 = *(char**)plVar7;
                        if (plVar2 == *(char**)plVar3) {
                            *(char**)plVar3 = plVar6;
                        } else {
                            *(char**)(plVar3 + 0x10) = plVar6;
                        }
                    }
                    *(char**)plVar6 = plVar2;
                    *(char**)plVar7 = plVar6;
                    plVar6 = plVar2;
                }
                *(char*)(*(char**)plVar7 + 0x28) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8) + 0x28) = 0;
                plVar7 = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)plVar7;
                *(char**)plVar7 = *(char**)(lVar4 + 0x10);
                if (*(char*)(*(char**)(lVar4 + 0x10) + 0x29)
                    == '\0') {
                    *(char**)(*(char**)(lVar4 + 0x10) + 8)
                        = plVar7;
                }
                *(char**)(lVar4 + 8) = *(char**)plVar7;
                if (plVar7 == *(char**)(head + 8)) {
                    *(char**)(head + 8) = lVar4;
                } else {
                    plVar2 = *(char**)(plVar7 + 8);
                    if (plVar7 == *(char**)plVar2) {
                        *(char**)plVar2 = lVar4;
                    } else {
                        *(char**)(plVar2 + 0x10) = lVar4;
                    }
                }
                *(char**)(lVar4 + 0x10) = plVar7;
                *(char**)(plVar7 + 8) = lVar4;
            }
        } else {
            // the parent IS the grand's RIGHT: the
            // uncle = the grand's left
            lVar4 = *(char**)plVar3;
            if (*(char*)(lVar4 + 0x28) == '\0') {
                *(char*)(plVar2 + 0x28) = 1;
                *(char*)(lVar4 + 0x28) = 1;
                *(char*)(*(char**)(*(char**)plVar7
                    + 8) + 0x28) = 0;
                plVar6 = *(char**)(*(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)plVar2) {
                    // the inner rotation (the RIGHT-lift
                    // on the parent)
                    lVar4 = *(char**)plVar2;
                    *(char**)plVar2 =
                        *(char**)(lVar4 + 0x10);
                    if (*(char*)(*(char**)(lVar4 + 0x10)
                        + 0x29) == '\0') {
                        *(char**)(*(char**)(lVar4 + 0x10) + 8)
                            = plVar2;
                    }
                    plVar7 = plVar2 + 8;
                    *(char**)(lVar4 + 8) = *(char**)plVar7;
                    if (plVar2 == *(char**)(head + 8)) {
                        *(char**)(head + 8) = lVar4;
                    } else {
                        plVar6 = *(char**)plVar7;
                        if (plVar2 == *(char**)plVar6) {
                            *(char**)(plVar6 + 0x10)
                                = lVar4;
                        } else {
                            *(char**)plVar6 = lVar4;
                        }
                    }
                    *(char**)(lVar4 + 0x10) = plVar2;
                    *(char**)plVar7 = lVar4;
                    plVar6 = plVar2;
                }
                *(char*)(*(char**)plVar7 + 0x28) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8) + 0x28) = 0;
                lVar4 = *(char**)(*(char**)plVar7 + 8);
                plVar7 = *(char**)(lVar4 + 0x10);
                *(char**)(lVar4 + 0x10) = *(char**)plVar7;
                if (*(char*)(*(char**)plVar7 + 0x29) == '\0') {
                    *(char**)(*(char**)plVar7 + 8) = lVar4;
                }
                *(char**)(plVar7 + 8) = *(char**)(lVar4 + 8);
                if (lVar4 == *(char**)(head + 8)) {
                    *(char**)(head + 8) = plVar7;
                } else {
                    plVar2 = *(char**)(lVar4 + 8);
                    if (lVar4 == *(char**)plVar2) {
                        *(char**)plVar2 = plVar7;
                    } else {
                        *(char**)(plVar2 + 0x10) = plVar7;
                    }
                }
                *(char**)plVar7 = lVar4;
                *(char**)(lVar4 + 8) = plVar7;
            }
        }
        plVar7 = plVar6 + 8;
        cVar1 = *(char*)(*(char**)plVar7 + 0x28);
    }
    *(char*)(*(char**)(head + 8) + 0x28) = 1; // root black
    param_2[1] = (char*)plVar5;
    *param_2 = *(char**)param_1;
    return param_2;
}

// ================= FUN_1417447d0 =================
// the iterator++: the right-subtree leftmost / the
// parent climb; the past-the-end tail (the
// unrecoverable jumptable in the decompile) is the
// CRT-compliant out_of_range throw
void LeagueIterNext(void* pIterState) {
    char** param_1 = (char**)pIterState;
    if (*param_1 == nullptr) {
        g_fnMeritInvalid();
    }
    char* lVar2 = (char*)param_1[1];
    if (*(char*)(lVar2 + 0x29) == '\0') {
        char* plVar3 =
            *(char**)(lVar2 + 0x10);   // right
        if (*(char*)(plVar3 + 0x29) != '\0') {
            // no right: the parent climb
            lVar2 = *(char**)(lVar2 + 8);
            char cVar1 = *(char*)(lVar2 + 0x29);
            while (cVar1 == '\0'
                && (param_1[1]
                    == *(char**)(lVar2 + 0x10))) {
                param_1[1] = lVar2;
                lVar2 = *(char**)(lVar2 + 8);
                cVar1 = *(char*)(lVar2 + 0x29);
            }
            param_1[1] = lVar2;
            return;
        }
        // the leftmost of the right subtree
        char cVar1 = *(char*)(*(char**)plVar3 + 0x29);
        char* plVar4 = *(char**)plVar3;
        while (cVar1 == '\0') {
            cVar1 = *(char*)(*(char**)plVar4 + 0x29);
            plVar3 = plVar4;
            plVar4 = *(char**)plVar4;
        }
        param_1[1] = plVar3;
        return;
    }
    // the past-the-end iterator: the throw
    throw std::out_of_range(
        "invalid map/set<T> iterator");
}

// ================= FUN_141744560 =================
// the LEFT-lift: X->left rises above X
void LeagueRotateL(void* pMap, void* pNode) {
    char* param_1 = (char*)pMap;
    char* param_2 = (char*)pNode;
    char* head = *(char**)(param_1 + 0x30);
    char* lVar1 = *(char**)param_2;          // the left
    *(char**)param_2 = *(char**)(lVar1 + 0x10);
    if (*(char*)(*(char**)(lVar1 + 0x10) + 0x29) == '\0') {
        *(char**)(*(char**)(lVar1 + 0x10) + 8) = param_2;
    }
    *(char**)(lVar1 + 8) = *(char**)(param_2 + 8);
    if (param_2 == *(char**)(head + 8)) {
        *(char**)(head + 8) = lVar1;         // the root
        *(char**)(lVar1 + 0x10) = param_2;
        *(char**)(param_2 + 8) = lVar1;
        return;
    }
    char* plVar2 = *(char**)(param_2 + 8);   // the parent
    if (param_2 == *(char**)(plVar2 + 0x10)) {
        // the node IS the parent's right
        *(char**)(plVar2 + 0x10) = lVar1;
    } else {
        *(char**)plVar2 = lVar1;
    }
    *(char**)(lVar1 + 0x10) = param_2;
    *(char**)(param_2 + 8) = lVar1;
}

// ================= FUN_141745ad0 =================
// the RIGHT-lift rotation (the node's right child
// rises)
void LeagueRotateR(void* pMap, void* pNode) {
    char* param_1 = (char*)pMap;
    char* param_2 = (char*)pNode;
    char* head = *(char**)(param_1 + 0x30);
    char** plVar1 = *(char***)(param_2 + 0x10);
    *(char**)(param_2 + 0x10) = *(char**)plVar1;
    if (*(char*)(*(char**)plVar1 + 0x29) == '\0') {
        *(char**)(*(char**)plVar1 + 8) = param_2;
    }
    plVar1[1] = *(char**)(param_2 + 8);
    if (param_2 == *(char**)(head + 8)) {
        *(char**)(head + 8) = (char*)plVar1;
        *(char**)plVar1 = param_2;
        *(char**)(param_2 + 8) = (char*)plVar1;
        return;
    }
    char** plVar2 = *(char***)(param_2 + 8);
    if (param_2 == (char*)*(char**)plVar2) {
        *(char**)plVar2 = (char*)plVar1;
        *(char**)plVar1 = param_2;
        *(char**)(param_2 + 8) = (char*)plVar1;
        return;
    }
    plVar2[2] = (char*)plVar1;
    *(char**)plVar1 = param_2;
    *(char**)(param_2 + 8) = (char*)plVar1;
}

// ================= FUN_141749c00 =================
// the erase: the invalid-iterator gate + the
// successor splice (incl. succ==right-child) + the
// unlink + the first/last descents + the verbatim
// remove-rebalance (the CARRIED entry parent) +
// the size gate
void* LeagueErase(void* pMap, void* pOutIter,
                  void* pIter) {
    char* pmap = (char*)pMap;
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIter;
    char* head = *(char**)(pmap + 0x30);
    char* plVar2 = param_3[1];   // the node
    if (*(char*)(plVar2 + 0x29) != '\0') {
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    LeagueIterNext(param_3);
    char* plVar8 = *(char**)plVar2;      // the left
    char* plVar9 = nullptr;
    char* plVar7 = nullptr;
    if (*(char*)(plVar8 + 0x29) == '\0') {
        plVar9 = plVar8;
        if (*(char*)(*(char**)(plVar2 + 0x10) + 0x29)
            == '\0') {
            // BOTH children: the successor splice
            plVar7 = param_3[1];  // the succ
            plVar9 = *(char**)(plVar7 + 0x10); // succ->R
            if (plVar7 != plVar2) {
                *(char**)(plVar8 + 8) = plVar7;
                *(char**)plVar7 = *(char**)plVar2;
                plVar8 = plVar7;
                if (plVar7 != *(char**)(plVar2 + 0x10)) {
                    plVar8 = *(char**)(plVar7 + 8);
                    if (*(char*)(plVar9 + 0x29)
                        == '\0') {
                        *(char**)(plVar9 + 8) = plVar8;
                    }
                    *(char**)plVar8 = plVar9;
                    *(char**)(plVar7 + 0x10) =
                        *(char**)(plVar2 + 0x10);
                    *(char**)(*(char**)(plVar2 + 0x10) + 8)
                        = plVar7;
                }
                if (*(char**)(head + 8) == plVar2) {
                    *(char**)(head + 8) = plVar7;
                } else {
                    char** puVar4 =
                        (char**)*(char**)(plVar2 + 8);
                    if (*(char**)puVar4 == plVar2) {
                        *(char**)puVar4 = plVar7;
                    } else {
                        puVar4[2] = (char*)plVar7;
                    }
                }
                *(char**)(plVar7 + 8) =
                    *(char**)(plVar2 + 8);
                // the color swap at +0x28
                char* plVar3c = plVar2 + 0x28;
                char* plVar7c = plVar7 + 0x28;
                if (plVar7c != plVar3c) {
                    long lVar5 = *(long*)plVar7c;
                    *(char*)plVar7c = *(char*)plVar3c;
                    *(char*)plVar3c = (char)lVar5;
                }
                goto rebalance;
            }
        }
    } else {
        plVar9 = *(char**)(plVar2 + 0x10);  // the right
    }
    // the unlink
    plVar8 = *(char**)(plVar2 + 8);   // P
    if (*(char*)(plVar9 + 0x29) == '\0') {
        *(char**)(plVar9 + 8) = plVar8;
    }
    if (*(char**)(head + 8) == plVar2) {
        *(char**)(head + 8) = plVar9;
    } else if (*(char**)plVar8 == plVar2) {
        *(char**)plVar8 = plVar9;
    } else {
        *(char**)(plVar8 + 0x10) = plVar9;
    }
    // the first descent (the leftmost)
    if (*(char**)head == plVar2) {
        char* plVar7b = plVar8;
        if (*(char*)(plVar9 + 0x29) == '\0') {
            char cVar1 = *(char*)(*(char**)plVar9 + 0x29);
            char* plVar3 = *(char**)plVar9;
            plVar7b = plVar9;
            char* plVar6;
            while (plVar6 = plVar3, cVar1 == '\0') {
                plVar3 = *(char**)plVar6;
                cVar1 = *(char*)(plVar3 + 0x29);
                plVar7b = plVar6;
            }
        }
        *(char**)head = plVar7b;
    }
    // the last descent (the rightmost)
    if (*(char**)(head + 0x10) == plVar2) {
        char* plVar7b = plVar8;
        if (*(char*)(plVar9 + 0x29) == '\0') {
            char cVar1 =
                *(char*)(*(char**)(plVar9 + 0x10) + 0x29);
            char* plVar3 = *(char**)(plVar9 + 0x10);
            plVar7b = plVar9;
            char* plVar6;
            while (plVar6 = plVar3, cVar1 == '\0') {
                plVar3 = *(char**)(plVar6 + 0x10);
                cVar1 = *(char*)(plVar3 + 0x29);
                plVar7b = plVar6;
            }
        }
        *(char**)(head + 0x10) = plVar7b;
    }
rebalance:
    if (*(char*)(plVar2 + 0x28) == '\x01') {
        // the node was BLACK: the fixup
        if (plVar9 != *(char**)(head + 8)) {
            char* plVar7x = nullptr;
            char* plVar8x = plVar8;   // the CARRIED P
            char* plVar8d = nullptr;
            char cVar1;
            do {
                plVar7x = plVar8x;
                if (*(char*)(plVar9 + 0x28)
                    != '\x01') {
                    break;   // the walker RED
                }
                plVar8d = *(char**)plVar7x;  // P->L
                if (plVar9 == plVar8d) {
                    // the walker IS P->left: sib =
                    // P->right
                    plVar8d = *(char**)(plVar7x + 0x10);
                    if (*(char*)(plVar8d + 0x28)
                        == '\0') {
                        *(char*)(plVar8d + 0x28) = 1;
                        *(char*)(plVar7x + 0x28) = 0;
                        LeagueRotateR(pMap, plVar7x);
                        plVar8d =
                            *(char**)(plVar7x + 0x10);
                    }
                    if (*(char*)(plVar8d + 0x29)
                        == '\0') {
                        if ((*(char*)(*(char**)plVar8d
                            + 0x28) != '\x01')
                            || (*(char*)(*(char**)(plVar8d
                                + 0x10) + 0x28)
                                != '\x01')) {
                            if (*(char*)(*(char**)(plVar8d
                                + 0x10) + 0x28)
                                == '\x01') {
                                *(char*)(*(char**)plVar8d
                                    + 0x28) = 1;
                                *(char*)(plVar8d + 0x28) = 0;
                                LeagueRotateL(pMap,
                                    plVar8d);
                                plVar8d =
                                    *(char**)(plVar7x
                                        + 0x10);
                            }
                            *(char*)(plVar8d + 0x28) =
                                *(char*)(plVar7x + 0x28);
                            *(char*)(plVar7x + 0x28) = 1;
                            *(char*)(*(char**)(plVar8d
                                + 0x10) + 0x28) = 1;
                            LeagueRotateR(pMap,
                                plVar7x);
                            break;
                        }
                        *(char*)(plVar8d + 0x28) = 0;
                    }
                } else {
                    // the walker IS P->right: sib =
                    // P->left
                    if (*(char*)(plVar8d + 0x28)
                        == '\0') {
                        *(char*)(plVar8d + 0x28) = 1;
                        *(char*)(plVar7x + 0x28) = 0;
                        LeagueRotateL(pMap, plVar7x);
                        plVar8d = *(char**)plVar7x;
                    }
                    if (*(char*)(plVar8d + 0x29)
                        == '\0') {
                        if ((*(char*)(*(char**)(plVar8d
                            + 0x10) + 0x28) != '\x01')
                            || (*(char*)(*(char**)plVar8d
                                + 0x28) != '\x01')) {
                            if (*(char*)(*(char**)plVar8d
                                + 0x28) == '\x01') {
                                *(char*)(*(char**)(plVar8d
                                    + 0x10) + 0x28) = 1;
                                *(char*)(plVar8d + 0x28) = 0;
                                LeagueRotateR(pMap,
                                    plVar8d);
                                plVar8d = *(char**)plVar7x;
                            }
                            *(char*)(plVar8d + 0x28) =
                                *(char*)(plVar7x + 0x28);
                            *(char*)(plVar7x + 0x28) = 1;
                            *(char*)(*(char**)plVar8d
                                + 0x28) = 1;
                            LeagueRotateL(pMap,
                                plVar7x);
                            break;
                        }
                        *(char*)(plVar8d + 0x28) = 0;
                    }
                }
                plVar8x = *(char**)(plVar7x + 8);
                plVar9 = plVar7x;
            } while (plVar7x != *(char**)(head + 8));
        }
        *(char*)(plVar9 + 0x28) = 1;
    }
    g_fnMeritOpDelete((void*)plVar2);
    if (*(uint64_t*)(pmap + 0x38) != 0) {
        *(uint64_t*)(pmap + 0x38) =
            *(uint64_t*)(pmap + 0x38) - 1;
    }
    char* lVar5 = (char*)param_3[1];   // the advanced
    *(char**)param_2 = *(char**)param_1;
    param_2[1] = lVar5;
    return param_2;
}

// ================= FUN_14174a150 =================
// the erase-range: the owner checks + the both-end
// clear + the inline successor advance loop
void* LeagueEraseRange(void* pMap, void* pOutIter,
                       void* pBegin, void* pEnd) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pBegin;
    char** param_4 = (char**)pEnd;
    char* lVar2 = *(char**)param_1[6];   // *head
    if (*param_3 == nullptr
        || *param_3 != *(char**)param_1) {
        g_fnMeritInvalid();
    }
    if (param_3[1] == (char*)lVar2) {
        lVar2 = (char*)param_1[6];       // the head
        if (*param_4 == nullptr
            || *param_4 != *(char**)param_1) {
            g_fnMeritInvalid();
        }
        if (param_4[1] == lVar2) {
            // both END: the full clear
            LeagueClear((void*)param_1);
            // *head = the head itself post-clear
            param_2[1] = *(char**)param_1[6];
            *param_2 = *(char**)param_1;
            return param_2;
        }
    }
    char* plVar6 = nullptr;
    char* plVar5 = nullptr;
    char cVar1;
    while (true) {
        if (*param_3 == nullptr
            || *param_3 != *param_4) {
            g_fnMeritInvalid();
        }
        char* lVar2b = *(char**)param_3;   // the owner
        if (param_3[1] == param_4[1]) break;
        char* lVar3 = (char*)param_3[1];   // the node
        if (*param_3 == nullptr) {
            g_fnMeritInvalid();
        }
        char* lVar4 = (char*)param_3[1];
        // the inline successor advance
        if (*(char*)(lVar4 + 0x29) == '\0') {
            plVar6 = *(char**)(lVar4 + 0x10);
            if (*(char*)(plVar6 + 0x29) == '\0') {
                cVar1 = *(char*)(*(char**)plVar6 + 0x29);
                plVar5 = *(char**)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5 + 0x29);
                    plVar6 = plVar5;
                    plVar5 = *(char**)plVar5;
                }
            } else {
                plVar6 = *(char**)(lVar4 + 8);
                cVar1 = *(char*)(plVar6 + 0x29);
                while (cVar1 == '\0'
                    && (param_3[1]
                        == *(char**)(plVar6 + 0x10))) {
                    param_3[1] = (char*)plVar6;
                    plVar6 = *(char**)(plVar6 + 8);
                    cVar1 = *(char*)(plVar6 + 0x29);
                }
                param_3[1] = (char*)plVar6;
                goto advance_done;
            }
            param_3[1] = (char*)plVar6;
advance_done:;
        } else {
            g_fnMeritInvalid();
        }
        // save the OLD begin node, erase it
        char* local_28[2];
        local_28[0] = lVar2b;
        local_28[1] = lVar3;
        char* local_18[2];
        LeagueErase((void*)param_1,
            (void*)local_18, (void*)local_28);
    }
    char* lVar2c = (char*)param_3[1];
    *param_2 = *(char**)param_1;
    param_2[1] = lVar2c;
    return param_2;
}

// ================= FUN_141746650 =================
// the recursive right-subtree free
void LeagueFreeSubtree(void* pMap, void* pNode) {
    char** param_2 = (char**)pNode;
    char cVar1 = *(char*)((char*)param_2 + 0x29);
    char** plVar2 = nullptr;
    while (cVar1 == '\0') {
        LeagueFreeSubtree(pMap,
            *(char**)(param_2 + 2));   // the right
        plVar2 = *(char***)param_2;     // the left
        g_fnMeritOpDelete((void*)param_2);
        param_2 = plVar2;
        cVar1 = *(char*)((char*)plVar2 + 0x29);
    }
}

// ================= FUN_141747270 =================
// the clear: the root walk (the right-subtree
// recursive frees + delete + the left advance) +
// the head relinks + size 0
void LeagueClear(void* pMap) {
    char* param_1 = (char*)pMap;
    char* head = *(char**)(param_1 + 0x30);
    char** plVar2 = *(char***)(head + 8);  // root
    char cVar1 = *(char*)((char*)plVar2 + 0x29);
    while (cVar1 == '\0') {
        LeagueFreeSubtree(pMap,
            *(char**)(plVar2 + 2));   // the right
        char** plVar3 = *(char***)plVar2;
        g_fnMeritOpDelete((void*)plVar2);
        plVar2 = plVar3;
        cVar1 = *(char*)((char*)plVar3 + 0x29);
    }
    *(char**)(head + 8) = head;   // root = head
    *(uint64_t*)(param_1 + 0x38) = 0;
    *(char**)head = head;         // left = first
    *(char**)(head + 0x10) = head; // right = last
}

// ================= FUN_14174c530 =================
// the member map dtor: the full-range erase
// [begin={anchor,*head}, end={anchor,head}] + the
// head delete + the zeroed slots (the ANCHOR is
// freed by the CLeague dtor cfc0)
void LeagueMemberDtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char* local_38[2];
    local_38[0] = *(char**)param_1;   // anchor
    char* puStack_30 = (char*)param_1[6];
    local_38[1] = puStack_30;          // END: head
    char* local_28[2];
    local_28[0] = *(char**)param_1;
    local_28[1] = *(char**)puStack_30;  // BEGIN: *head
    char* local_18[2];
    LeagueEraseRange((void*)param_1,
        (void*)local_18, (void*)local_28,
        (void*)local_38);
    g_fnMeritOpDelete((void*)param_1[6]);
    param_1[6] = nullptr;
    param_1[7] = nullptr;
}

} // namespace syndicate
