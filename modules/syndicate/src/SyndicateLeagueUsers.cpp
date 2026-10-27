// Syndicate.dll — unit T10/D36 (part 2a): the USERS-MAP
// family bodies (verbatim; byte-diffed against the D32
// counterparts — identical modulo the callee ids).
#include "SyndicateLeagueUsers.h"
#include "SyndicateLeagueTree.h"   // the D32 insert (141748820)
#include "SyndicateCrossMerit.h"
#include <new>
#include <stdexcept>

namespace syndicate {

// the free / invalid seams (the established test binding)
extern void* (*g_fnMeritOpNew)(size_t);
extern void (*g_fnMeritOpDelete)(void*);
extern void (*g_fnMeritInvalid)();

// ================= FUN_1417265a0 (== 141746790) =================
// new 0x30; left/parent/right; the 16-byte key pair
// copy (+0x18, +0x20); color@+0x28; _Isnil@+0x29 = 0
void* UsersNodeAlloc(void* pLeft, void* pParent,
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

// ================= FUN_141729790 (== 141748820) =================
// the insert + the red-black rebalance (the length
// gate at 0xffffffffffffffd, the D29 leaf convention:
// the new node's children point at the head)
void* UsersInsert(void* pMap, void* pOutIter,
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
    char* plVar5 = (char*)UsersNodeAlloc(
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
                // ORIGINAL: *(longlong *)(lVar4 + 8) =
                // plVar7[1] — the grand's PARENT slot
                // (+8 on the raw grand pointer), not the
                // grand's left (was *plVar7: the lifted
                // parent inherited its own child)
                *(char**)(lVar4 + 8) = *(char**)(plVar7 + 8);
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
                        // ORIGINAL: if (plVar2 == plVar6[2])
                        // { plVar6[2] = lVar4; } else
                        // { *plVar6 = lVar4; } — the
                        // grand's RIGHT slot (plVar6[2]),
                        // not the left: the parent IS the
                        // grand's right child in this
                        // branch (was mirrored: 312 landed
                        // at 70->left and cycled)
                        if (plVar2 == *(char**)(plVar6 + 0x10)) {
                            *(char**)(plVar6 + 0x10) = lVar4;
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

// ================= FUN_14172afb0 =================
// the UNIQUE insert: the lower_bound descent + the two
// neighbor duplicate gates + the raw insert. The output
// iterator home is {anchor, node} with the inserted FLAG
// byte at out+0x10 (0 = duplicate, 1 = inserted).
void* UsersInsertUnique(void* pMap, void* pOut,
                        uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    uint32_t* param_3 = pKey;
    char* head = *(char**)((char*)param_1 + 0x30);
    char* plVar6 = head;
    bool bVar7 = true;
    if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
        char* plVar5 = *(char**)(head + 8);   // the root
        do {
            plVar6 = plVar5;
            // the key at node+0x18 (u32)
            bVar7 = *param_3
                < *(uint32_t*)((char*)plVar6 + 0x18);
            plVar5 = bVar7
                ? *(char**)plVar6              // the left
                : *(char**)(plVar6 + 0x10);    // the right
        } while (*(char*)(plVar5 + 0x29) == '\0');
    }
    char* lVar2 = *(char**)param_1;   // the anchor
    char* plVar5 = plVar6;
    // ORIGINAL: local_38 (anchor home) is ADJACENT to
    // local_30 (the node slot) — the raw insert writes
    // BOTH via its {param_2[0], param_2[1]} pair out
    int64_t insOut[2];
    insOut[0] = (int64_t)lVar2;
    char* plVar4 = plVar6;
    char* local_30 = nullptr;
    char* plVar6r = nullptr;   // head-declared: the goto must not cross it
    if (bVar7 == false) {
lab_b10d:
        local_30 = plVar4;
        // the RIGHT-candidate duplicate gate
        if (*param_3
            <= *(uint32_t*)((char*)plVar5 + 0x18)) {
            *(char*)(param_2 + 2) = 0;   // flag: dup
            *(char**)param_2 = (char*)insOut[0];
            goto lab_b13c;
        }
    } else {
        plVar5 = *(char**)head;   // head->left = the FIRST
        local_30 = plVar6;
        if (lVar2 == nullptr) {
            g_fnMeritInvalid();
        }
        if (plVar6 != plVar5) {
            if (lVar2 == nullptr) {
                g_fnMeritInvalid();
            }
            if (*(char*)(plVar6 + 0x29) == '\0') {
                plVar5 = *(char**)plVar6;   // the left
                if (*(char*)(plVar5 + 0x29) == '\0') {
                    // the rightmost of the LEFT subtree
                    char* plVar3 = *(char**)(plVar5 + 0x10);
                    char cVar1 = *(char*)(plVar3 + 0x29);
                    char* plVar4b = plVar5;
                    while (plVar4b = plVar5, cVar1 == '\0') {
                        cVar1 = *(char*)(*(char**)(plVar3 + 0x10) + 0x29);
                        plVar5 = plVar3;
                        plVar3 = *(char**)(plVar3 + 0x10);
                    }
                    plVar4 = plVar4b;
                } else {
                    // the climb: while the node is the
                    // parent's LEFT child
                    char cVar1 = *(char*)(*(char**)(plVar6 + 8) + 0x29);
                    char* plVar4b = *(char**)(plVar6 + 8);
                    char* plVar3 = plVar6;
                    while (plVar5 = plVar4b,
                           cVar1 == '\0'
                           && plVar3 == *(char**)plVar5) {
                        cVar1 = *(char*)(*(char**)(plVar5 + 8) + 0x29);
                        plVar4b = *(char**)(plVar5 + 8);
                        plVar3 = plVar5;
                        local_30 = plVar5;
                    }
                    plVar4 = plVar5;
                    if (*(char*)(plVar3 + 0x29) != '\0') {
                        g_fnMeritInvalid();
                        plVar5 = plVar3;
                        plVar4 = local_30;
                    }
                }
            } else {
                plVar5 = *(char**)(plVar6 + 0x10);
                plVar4 = plVar5;
                if (*(char*)(plVar5 + 0x29) != '\0') {
                    local_30 = plVar5;
                    g_fnMeritInvalid();
                    plVar4 = local_30;
                }
            }
            goto lab_b10d;
        }
        bVar7 = true;   // no predecessor to check
    }
    // the raw insert — insOut IS the adjacent pair home
    plVar6r = (char*)UsersInsert(
        (void*)param_1, (void*)insOut,
        (uint8_t)bVar7, (void*)plVar6,
        (void*)param_3);
    *(char*)(param_2 + 2) = 1;   // flag: inserted
    local_30 = *(char**)(plVar6r + 8);   // insOut[1]
    *(char**)param_2 = *(char**)plVar6r; // insOut[0]
lab_b13c:
    param_2[1] = (char*)local_30;
    return param_2;
}

// ================= FUN_141722ef0 (== 1417447d0) =================
// the iterator++: the right-subtree leftmost / the
// parent climb; the past-the-end tail (the
// unrecoverable jumptable in the decompile) is the
// CRT-compliant out_of_range throw
void UsersIterNext(void* pIterState) {
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

// ================= FUN_1417224f0 (== 141744560) =================
// the LEFT-lift: X->left rises above X
void UsersRotateL(void* pMap, void* pNode) {
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

// ================= FUN_141724870 (== 141745ad0) =================
// the RIGHT-lift rotation (the node's right child
// rises)
void UsersRotateR(void* pMap, void* pNode) {
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

// ================= FUN_14172b160 (== 141749c00) =================
// the erase: the invalid-iterator gate + the
// successor splice (incl. succ==right-child) + the
// unlink + the first/last descents + the verbatim
// remove-rebalance (the CARRIED entry parent) +
// the size gate
void* UsersErase(void* pMap, void* pOutIter,
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
    UsersIterNext(param_3);
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
                        UsersRotateR(pMap, plVar7x);
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
                                UsersRotateL(pMap,
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
                            UsersRotateR(pMap,
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
                        UsersRotateL(pMap, plVar7x);
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
                                UsersRotateR(pMap,
                                    plVar8d);
                                plVar8d = *(char**)plVar7x;
                            }
                            *(char*)(plVar8d + 0x28) =
                                *(char*)(plVar7x + 0x28);
                            *(char*)(plVar7x + 0x28) = 1;
                            *(char*)(*(char**)plVar8d
                                + 0x28) = 1;
                            UsersRotateL(pMap,
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


// ================= FUN_141749a50 =================
// the TOKENS-map unique insert (0x29 nodes, the map
// @ entity+0xd8): byte-identical to the users unique
// insert (14172afb0) modulo the RAW-INSERT callee — it
// calls the D32 insert (141748820), NOT the users raw
// insert. out = {anchor, node, flag@+0x10}.
// ================= FUN_141749a50 =================
// the TOKENS-map unique insert (0x29 nodes, the map
// @ entity+0xd8): byte-identical to the users unique
// insert (14172afb0) modulo the RAW-INSERT callee — it
// calls the D32 insert (141748820), NOT the users raw
// insert. out = {anchor, node, flag@+0x10}.
// the UNIQUE insert: the lower_bound descent + the two
// neighbor duplicate gates + the raw insert. The output
// iterator home is {anchor, node} with the inserted FLAG
// byte at out+0x10 (0 = duplicate, 1 = inserted).
void* TokensInsertUnique(void* pMap, void* pOut,
                        uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    uint32_t* param_3 = pKey;
    char* head = *(char**)((char*)param_1 + 0x30);
    char* plVar6 = head;
    bool bVar7 = true;
    if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
        char* plVar5 = *(char**)(head + 8);   // the root
        do {
            plVar6 = plVar5;
            // the key at node+0x18 (u32)
            bVar7 = *param_3
                < *(uint32_t*)((char*)plVar6 + 0x18);
            plVar5 = bVar7
                ? *(char**)plVar6              // the left
                : *(char**)(plVar6 + 0x10);    // the right
        } while (*(char*)(plVar5 + 0x29) == '\0');
    }
    char* lVar2 = *(char**)param_1;   // the anchor
    char* plVar5 = plVar6;
    // ORIGINAL: local_38 (anchor home) is ADJACENT to
    // local_30 (the node slot) — the raw insert writes
    // BOTH via its {param_2[0], param_2[1]} pair out
    int64_t insOut[2];
    insOut[0] = (int64_t)lVar2;
    char* plVar4 = plVar6;
    char* local_30 = nullptr;
    char* plVar6r = nullptr;   // head-declared: the goto must not cross it
    if (bVar7 == false) {
lab_b10d:
        local_30 = plVar4;
        // the RIGHT-candidate duplicate gate
        if (*param_3
            <= *(uint32_t*)((char*)plVar5 + 0x18)) {
            *(char*)(param_2 + 2) = 0;   // flag: dup
            *(char**)param_2 = (char*)insOut[0];
            goto lab_b13c;
        }
    } else {
        plVar5 = *(char**)head;   // head->left = the FIRST
        local_30 = plVar6;
        if (lVar2 == nullptr) {
            g_fnMeritInvalid();
        }
        if (plVar6 != plVar5) {
            if (lVar2 == nullptr) {
                g_fnMeritInvalid();
            }
            if (*(char*)(plVar6 + 0x29) == '\0') {
                plVar5 = *(char**)plVar6;   // the left
                if (*(char*)(plVar5 + 0x29) == '\0') {
                    // the rightmost of the LEFT subtree
                    char* plVar3 = *(char**)(plVar5 + 0x10);
                    char cVar1 = *(char*)(plVar3 + 0x29);
                    char* plVar4b = plVar5;
                    while (plVar4b = plVar5, cVar1 == '\0') {
                        cVar1 = *(char*)(*(char**)(plVar3 + 0x10) + 0x29);
                        plVar5 = plVar3;
                        plVar3 = *(char**)(plVar3 + 0x10);
                    }
                    plVar4 = plVar4b;
                } else {
                    // the climb: while the node is the
                    // parent's LEFT child
                    char cVar1 = *(char*)(*(char**)(plVar6 + 8) + 0x29);
                    char* plVar4b = *(char**)(plVar6 + 8);
                    char* plVar3 = plVar6;
                    while (plVar5 = plVar4b,
                           cVar1 == '\0'
                           && plVar3 == *(char**)plVar5) {
                        cVar1 = *(char*)(*(char**)(plVar5 + 8) + 0x29);
                        plVar4b = *(char**)(plVar5 + 8);
                        plVar3 = plVar5;
                        local_30 = plVar5;
                    }
                    plVar4 = plVar5;
                    if (*(char*)(plVar3 + 0x29) != '\0') {
                        g_fnMeritInvalid();
                        plVar5 = plVar3;
                        plVar4 = local_30;
                    }
                }
            } else {
                plVar5 = *(char**)(plVar6 + 0x10);
                plVar4 = plVar5;
                if (*(char*)(plVar5 + 0x29) != '\0') {
                    local_30 = plVar5;
                    g_fnMeritInvalid();
                    plVar4 = local_30;
                }
            }
            goto lab_b10d;
        }
        bVar7 = true;   // no predecessor to check
    }
    // the raw insert — insOut IS the adjacent pair home
    plVar6r = (char*)LeagueInsert(
        (void*)param_1, (void*)insOut,
        (uint8_t)bVar7, (void*)plVar6,
        (void*)param_3);
    *(char*)(param_2 + 2) = 1;   // flag: inserted
    local_30 = *(char**)(plVar6r + 8);   // insOut[1]
    *(char**)param_2 = *(char**)plVar6r; // insOut[0]
lab_b13c:
    param_2[1] = (char*)local_30;
    return param_2;
}

} // namespace syndicate
