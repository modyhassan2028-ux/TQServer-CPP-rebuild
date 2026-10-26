// Syndicate.dll — unit T10/D36 (part 2b): the MEMBERS-MAP
// family bodies (verbatim; byte-diffed against the D32
// counterparts — identical modulo the 0x40-node offsets).
#include "SyndicateLeagueMembers.h"
#include "SyndicateCrossMerit.h"
#include <new>
#include <stdexcept>

namespace syndicate {

// the free / invalid seams (the established test binding)
extern void* (*g_fnMeritOpNew)(size_t);
extern void (*g_fnMeritOpDelete)(void*);
extern void (*g_fnMeritInvalid)();

// ================= FUN_141746a00 =================
// ================= FUN_141746a00 =================
// new 0x40; the zeroed link slots (the always-true
// slot-address checks); color@+0x3c = 1 (black)
void* MembersHeadAlloc() {
    char** puVar1 = (char**)operator new(0x40);
    if (puVar1 != nullptr) {
        *puVar1 = nullptr;
    }
    if (puVar1 + 1 != nullptr) {
        puVar1[1] = nullptr;
    }
    if (puVar1 + 2 != nullptr) {
        puVar1[2] = nullptr;
    }
    *(uint8_t*)((char*)puVar1 + 0x3c) = 1;
    return puVar1;
}

// ================= FUN_1417466e0 =================
// new 0x40; left/parent/right; the NINE-u32 value copy
// at +0x18..+0x38; color@+0x3c; _Isnil@+0x3d = 0
void* MembersNodeAlloc(void* pLeft, void* pParent,
                       void* pRight, uint32_t* pVal,
                       uint8_t uColor) {
    char** puVar1 = (char**)operator new(0x40);
    if (puVar1 != nullptr) {
        puVar1[0] = (char*)pLeft;
        puVar1[1] = (char*)pParent;
        puVar1[2] = (char*)pRight;
        *(uint32_t*)((char*)puVar1 + 0x18) = pVal[0];
        *(uint32_t*)((char*)puVar1 + 0x1c) = pVal[1];
        *(uint32_t*)((char*)puVar1 + 0x20) = pVal[2];
        *(uint32_t*)((char*)puVar1 + 0x24) = pVal[3];
        *(uint32_t*)(puVar1 + 5) = pVal[4];       // +0x28
        *(uint32_t*)((char*)puVar1 + 0x2c) = pVal[5];
        *(uint32_t*)(puVar1 + 6) = pVal[6];       // +0x30
        *(uint32_t*)((char*)puVar1 + 0x34) = pVal[7];
        *(uint32_t*)(puVar1 + 7) = pVal[8];       // +0x38
        *(uint8_t*)((char*)puVar1 + 0x3c) = uColor;
        *(uint8_t*)((char*)puVar1 + 0x3d) = 0;
    }
    return puVar1;
}

// ================= FUN_1417478a0 =================
// the members-map ctor: the head (isnil set HERE after
// the alloc) + the self-links + size 0. NOTE: the anchor
// (map[0]) is NOT created here — the CLeague ctor owns
// the members-map anchor slot (unlike the D32 ctor).
void MembersMapCtor(void* pMap) {
    char* lVar1 = (char*)MembersHeadAlloc();
    *(char**)((char*)pMap + 0x30) = lVar1;
    *(uint8_t*)(lVar1 + 0x3d) = 1;       // the head flag
    *(char**)(lVar1 + 8) = lVar1;        // parent
    *(char**)lVar1 = lVar1;              // left
    *(char**)(lVar1 + 0x10) = lVar1;     // right
    *(char**)((char*)pMap + 0x38) = nullptr;  // size 0
}

// ================= FUN_1417477c0 =================
// the equal_range: TWO lower_bound descents (the D29
// leaf rule); out[0..3] = {anchor, first, anchor, last}
void* MembersEqualRange(void* pMap, void* pOut,
                        uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    uint32_t* param_3 = pKey;
    char* puVar4 = *(char**)((char*)param_1 + 0x30);  // head
    char* puVar5 = puVar4;    // the FIRST candidate
    if (*(char*)(*(char**)(puVar4 + 8) + 0x3d) == '\0') {
        char* puVar2 = *(char**)(puVar4 + 8);   // root
        do {
            if (*(uint32_t*)(puVar2 + 0x18) < *param_3) {
                puVar2 = *(char**)(puVar2 + 0x10);
            } else {
                if ((*(char*)(puVar4 + 0x3d) != '\0')
                    && (*param_3
                        < *(uint32_t*)(puVar2 + 0x18))) {
                    puVar4 = puVar2;
                }
                // ORIGINAL: puVar3 = *puVar2; puVar5 =
                // puVar2 — the CURRENT node is the
                // first-bound candidate (was saving the
                // left child)
                puVar5 = puVar2;
                puVar2 = *(char**)puVar2;
            }
        } while (*(char*)(puVar2 + 0x3d) == '\0');
    }
    // the second descent: the LAST candidate
    char* puVar2b;
    if (*(char*)(puVar4 + 0x3d) == '\0') {
        puVar2b = *(char**)puVar4;
    } else {
        puVar2b = *(char**)(*(char**)((char*)param_1
            + 0x30) + 8);   // the root
    }
    if (*(char*)(puVar2b + 0x3d) == '\0') {
        do {
            if (*param_3 < *(uint32_t*)(puVar2b + 0x18)) {
                // ORIGINAL: puVar3 = *puVar2; puVar4 =
                // puVar2 — remember the CURRENT node,
                // THEN descend left
                puVar4 = puVar2b;
                puVar2b = *(char**)puVar2b;
            } else {
                puVar2b = *(char**)(puVar2b + 0x10);
            }
        } while (*(char*)(puVar2b + 0x3d) == '\0');
    }
    char* uVar1 = *(char**)param_1;   // the anchor
    param_2[0] = uVar1;
    param_2[1] = puVar5;
    param_2[2] = uVar1;
    param_2[3] = puVar4;
    return param_2;
}

// ================= FUN_141749840 =================
// the erase(key): equal_range + the successor count walk
// + the erase-range; returns the removed count.
// NOTE: the ORIGINAL's local_38/local_30/local_28/
// local_20 are a CONTIGUOUS 32-byte home (the
// equal_range writes all four slots) — one rg[4] array
// models the adjacency (the afb0 trap).
uint64_t MembersEraseKey(void* pMap, uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    uint32_t* param_2 = pKey;
    // the range home: {anchor, first, anchor, last}
    int64_t rg[4];
    MembersEqualRange((void*)param_1, (void*)rg,
                     param_2);
    char* plVar5 = (char*)rg[3];   // the LAST node
    char* plVar7 = (char*)rg[1];   // the FIRST node
    int64_t lVar8 = 0;
    while (true) {
        if (plVar7 == plVar5) break;
        lVar8 = lVar8 + 1;
        if (plVar7 == nullptr) {
            g_fnMeritInvalid();
        }
        if (*(char*)(plVar7 + 0x3d) == '\0') {
            char* plVar2 = *(char**)(plVar7 + 0x10);
            if (*(char*)(plVar2 + 0x3d) == '\0') {
                // the leftmost of the right subtree
                char cVar1 = *(char*)(*(char**)plVar2 + 0x3d);
                char* plVar2b = *(char**)plVar2;
                plVar7 = plVar2;
                char* plVar3 = plVar2b;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*(char**)plVar3 + 0x3d);
                    plVar7 = plVar3;
                    plVar3 = *(char**)plVar3;
                }
            } else {
                // the climb: while the node is the
                // parent's RIGHT child
                char cVar1 = *(char*)(*(char**)(plVar7 + 8) + 0x3d);
                char* plVar6 = *(char**)(plVar7 + 8);
                char* plVar2 = plVar7;
                while (plVar7 = plVar6,
                       cVar1 == '\0'
                       && plVar2 == *(char**)(plVar7 + 0x10)) {
                    cVar1 = *(char*)(*(char**)(plVar7 + 8) + 0x3d);
                    plVar6 = *(char**)(plVar7 + 8);
                    plVar2 = plVar7;
                }
                plVar7 = plVar6;
            }
        } else {
            g_fnMeritInvalid();
        }
    }
    // the erase-range over [first, last): the iterator
    // homes ARE the rg slots (rg+0 the begin home,
    // rg+2 the end home)
    int64_t outIter[2];
    MembersEraseRange((void*)param_1, (void*)outIter,
                      (void*)rg, (void*)(rg + 2));
    return (uint64_t)lVar8;
}
// ================= FUN_141746600 =================
// the recursive right-subtree free
void MembersFreeSubtree(void* pMap, void* pNode) {
    char** param_2 = (char**)pNode;
    char cVar1 = *(char*)((char*)param_2 + 0x3d);
    char** plVar2 = nullptr;
    while (cVar1 == '\0') {
        MembersFreeSubtree(pMap,
            *(char**)(param_2 + 2));   // the right
        plVar2 = *(char***)param_2;     // the left
        g_fnMeritOpDelete((void*)param_2);
        param_2 = plVar2;
        cVar1 = *(char*)((char*)plVar2 + 0x3d);
    }
}

// ================= FUN_1417483e0 =================
// the insert + the red-black rebalance (the length
// gate at 0xffffffffffffffd, the D29 leaf convention:
// the new node's children point at the head)
void* MembersInsert(void* pMap, void* pOutIter,
                   uint8_t bLeft, void* pAttach,
                   void* pKey) {
    char* pmap = (char*)pMap;
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char param_3 = (char)bLeft;
    char* param_4 = (char*)pAttach;
    char* head = *(char**)(pmap + 0x30);
    char* sizeSlot = pmap + 0x38;
    if (0x71c71c71c71c71aULL
        < *(uint64_t*)sizeSlot) {
        throw std::length_error(
            "map/set<T> too long");
    }
    char* plVar5 = (char*)MembersNodeAlloc(
        (void*)head,        // left = head
        (void*)param_4,     // parent = attach
        (void*)head,        // right = head
        (uint32_t*)pKey, 0);  // red
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
    char cVar1 = *(char*)(*(char**)plVar7 + 0x3c);
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
            if (*(char*)(lVar4 + 0x3c) == '\0') {
                // the uncle RED: recolor + climb
                *(char*)(plVar2 + 0x3c) = 1;
                *(char*)(lVar4 + 0x3c) = 1;
                *(char*)(*(char**)(*(char**)plVar7
                    + 8) + 0x3c) = 0;
                plVar6 = *(char**)(*(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)(plVar2 + 0x10)) {
                    // the inner rotation (the LEFT-lift
                    // on the parent)
                    plVar6 = *(char**)(plVar2 + 0x10);
                    *(char**)(plVar2 + 0x10) =
                        *(char**)plVar6;
                    if (*(char*)(*(char**)plVar6 + 0x3d)
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
                *(char*)(*(char**)plVar7 + 0x3c) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8) + 0x3c) = 0;
                plVar7 = *(char**)(*(char**)plVar7 + 8);
                lVar4 = *(char**)plVar7;
                *(char**)plVar7 = *(char**)(lVar4 + 0x10);
                if (*(char*)(*(char**)(lVar4 + 0x10) + 0x3d)
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
            if (*(char*)(lVar4 + 0x3c) == '\0') {
                *(char*)(plVar2 + 0x3c) = 1;
                *(char*)(lVar4 + 0x3c) = 1;
                *(char*)(*(char**)(*(char**)plVar7
                    + 8) + 0x3c) = 0;
                plVar6 = *(char**)(*(char**)plVar7 + 8);
            } else {
                if (plVar6 == *(char**)plVar2) {
                    // the inner rotation (the RIGHT-lift
                    // on the parent)
                    lVar4 = *(char**)plVar2;
                    *(char**)plVar2 =
                        *(char**)(lVar4 + 0x10);
                    if (*(char*)(*(char**)(lVar4 + 0x10)
                        + 0x3d) == '\0') {
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
                *(char*)(*(char**)plVar7 + 0x3c) = 1;
                *(char*)(*(char**)(*(char**)plVar7 + 8) + 0x3c) = 0;
                lVar4 = *(char**)(*(char**)plVar7 + 8);
                plVar7 = *(char**)(lVar4 + 0x10);
                *(char**)(lVar4 + 0x10) = *(char**)plVar7;
                if (*(char*)(*(char**)plVar7 + 0x3d) == '\0') {
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
        cVar1 = *(char*)(*(char**)plVar7 + 0x3c);
    }
    *(char*)(*(char**)(head + 8) + 0x3c) = 1; // root black
    param_2[1] = (char*)plVar5;
    *param_2 = *(char**)param_1;
    return param_2;
}

// ================= FUN_141749690 =================
// the UNIQUE insert: the lower_bound descent + the two
// neighbor duplicate gates + the raw insert. The output
// iterator home is {anchor, node} with the inserted FLAG
// byte at out+0x10 (0 = duplicate, 1 = inserted).
void* MembersInsertUnique(void* pMap, void* pOut,
                        uint32_t* pKey) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    uint32_t* param_3 = pKey;
    char* head = *(char**)((char*)param_1 + 0x30);
    char* plVar6 = head;
    bool bVar7 = true;
    if (*(char*)(*(char**)(head + 8) + 0x3d) == '\0') {
        char* plVar5 = *(char**)(head + 8);   // the root
        do {
            plVar6 = plVar5;
            // the key at node+0x18 (u32)
            bVar7 = *param_3
                < *(uint32_t*)((char*)plVar6 + 0x18);
            plVar5 = bVar7
                ? *(char**)plVar6              // the left
                : *(char**)(plVar6 + 0x10);    // the right
        } while (*(char*)(plVar5 + 0x3d) == '\0');
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
            if (*(char*)(plVar6 + 0x3d) == '\0') {
                plVar5 = *(char**)plVar6;   // the left
                if (*(char*)(plVar5 + 0x3d) == '\0') {
                    // the rightmost of the LEFT subtree
                    char* plVar3 = *(char**)(plVar5 + 0x10);
                    char cVar1 = *(char*)(plVar3 + 0x3d);
                    char* plVar4b = plVar5;
                    while (plVar4b = plVar5, cVar1 == '\0') {
                        cVar1 = *(char*)(*(char**)(plVar3 + 0x10) + 0x3d);
                        plVar5 = plVar3;
                        plVar3 = *(char**)(plVar3 + 0x10);
                    }
                    plVar4 = plVar4b;
                } else {
                    // the climb: while the node is the
                    // parent's LEFT child
                    char cVar1 = *(char*)(*(char**)(plVar6 + 8) + 0x3d);
                    char* plVar4b = *(char**)(plVar6 + 8);
                    char* plVar3 = plVar6;
                    while (plVar5 = plVar4b,
                           cVar1 == '\0'
                           && plVar3 == *(char**)plVar5) {
                        cVar1 = *(char*)(*(char**)(plVar5 + 8) + 0x3d);
                        plVar4b = *(char**)(plVar5 + 8);
                        plVar3 = plVar5;
                        local_30 = plVar5;
                    }
                    plVar4 = plVar5;
                    if (*(char*)(plVar3 + 0x3d) != '\0') {
                        g_fnMeritInvalid();
                        plVar5 = plVar3;
                        plVar4 = local_30;
                    }
                }
            } else {
                plVar5 = *(char**)(plVar6 + 0x10);
                plVar4 = plVar5;
                if (*(char*)(plVar5 + 0x3d) != '\0') {
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
    plVar6r = (char*)MembersInsert(
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

// ================= FUN_141744cb0 =================
// the iterator++: the right-subtree leftmost / the
// parent climb; the past-the-end tail (the
// unrecoverable jumptable in the decompile) is the
// CRT-compliant out_of_range throw
void MembersIterNext(void* pIterState) {
    char** param_1 = (char**)pIterState;
    if (*param_1 == nullptr) {
        g_fnMeritInvalid();
    }
    char* lVar2 = (char*)param_1[1];
    if (*(char*)(lVar2 + 0x3d) == '\0') {
        char* plVar3 =
            *(char**)(lVar2 + 0x10);   // right
        if (*(char*)(plVar3 + 0x3d) != '\0') {
            // no right: the parent climb
            lVar2 = *(char**)(lVar2 + 8);
            char cVar1 = *(char*)(lVar2 + 0x3d);
            while (cVar1 == '\0'
                && (param_1[1]
                    == *(char**)(lVar2 + 0x10))) {
                param_1[1] = lVar2;
                lVar2 = *(char**)(lVar2 + 8);
                cVar1 = *(char*)(lVar2 + 0x3d);
            }
            param_1[1] = lVar2;
            return;
        }
        // the leftmost of the right subtree
        char cVar1 = *(char*)(*(char**)plVar3 + 0x3d);
        char* plVar4 = *(char**)plVar3;
        while (cVar1 == '\0') {
            cVar1 = *(char*)(*(char**)plVar4 + 0x3d);
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

// ================= FUN_141745c90 =================
// the LEFT-lift: X->left rises above X
void MembersRotateL(void* pMap, void* pNode) {
    char* param_1 = (char*)pMap;
    char* param_2 = (char*)pNode;
    char* head = *(char**)(param_1 + 0x30);
    char* lVar1 = *(char**)param_2;          // the left
    *(char**)param_2 = *(char**)(lVar1 + 0x10);
    if (*(char*)(*(char**)(lVar1 + 0x10) + 0x3d) == '\0') {
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

// ================= FUN_141745c30 =================
// the RIGHT-lift rotation (the node's right child
// rises)
void MembersRotateR(void* pMap, void* pNode) {
    char* param_1 = (char*)pMap;
    char* param_2 = (char*)pNode;
    char* head = *(char**)(param_1 + 0x30);
    char** plVar1 = *(char***)(param_2 + 0x10);
    *(char**)(param_2 + 0x10) = *(char**)plVar1;
    if (*(char*)(*(char**)plVar1 + 0x3d) == '\0') {
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

// ================= FUN_141747400 =================
// the erase: the invalid-iterator gate + the
// successor splice (incl. succ==right-child) + the
// unlink + the first/last descents + the verbatim
// remove-rebalance (the CARRIED entry parent) +
// the size gate
void* MembersErase(void* pMap, void* pOutIter,
                  void* pIter) {
    char* pmap = (char*)pMap;
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIter;
    char* head = *(char**)(pmap + 0x30);
    char* plVar2 = param_3[1];   // the node
    if (*(char*)(plVar2 + 0x3d) != '\0') {
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    MembersIterNext(param_3);
    char* plVar8 = *(char**)plVar2;      // the left
    char* plVar9 = nullptr;
    char* plVar7 = nullptr;
    if (*(char*)(plVar8 + 0x3d) == '\0') {
        plVar9 = plVar8;
        if (*(char*)(*(char**)(plVar2 + 0x10) + 0x3d)
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
                    if (*(char*)(plVar9 + 0x3d)
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
                // the color swap at +0x3c (the 0x3d
                // node color slot — was left at the D32
                // +0x28 and wrote over the value record)
                char* plVar3c = plVar2 + 0x3c;
                char* plVar7c = plVar7 + 0x3c;
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
    if (*(char*)(plVar9 + 0x3d) == '\0') {
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
        if (*(char*)(plVar9 + 0x3d) == '\0') {
            char cVar1 = *(char*)(*(char**)plVar9 + 0x3d);
            char* plVar3 = *(char**)plVar9;
            plVar7b = plVar9;
            char* plVar6;
            while (plVar6 = plVar3, cVar1 == '\0') {
                plVar3 = *(char**)plVar6;
                cVar1 = *(char*)(plVar3 + 0x3d);
                plVar7b = plVar6;
            }
        }
        *(char**)head = plVar7b;
    }
    // the last descent (the rightmost)
    if (*(char**)(head + 0x10) == plVar2) {
        char* plVar7b = plVar8;
        if (*(char*)(plVar9 + 0x3d) == '\0') {
            char cVar1 =
                *(char*)(*(char**)(plVar9 + 0x10) + 0x3d);
            char* plVar3 = *(char**)(plVar9 + 0x10);
            plVar7b = plVar9;
            char* plVar6;
            while (plVar6 = plVar3, cVar1 == '\0') {
                plVar3 = *(char**)(plVar6 + 0x10);
                cVar1 = *(char*)(plVar3 + 0x3d);
                plVar7b = plVar6;
            }
        }
        *(char**)(head + 0x10) = plVar7b;
    }
rebalance:
    if (*(char*)(plVar2 + 0x3c) == '\x01') {
        // the node was BLACK: the fixup
        if (plVar9 != *(char**)(head + 8)) {
            char* plVar7x = nullptr;
            char* plVar8x = plVar8;   // the CARRIED P
            char* plVar8d = nullptr;
            char cVar1;
            do {
                plVar7x = plVar8x;
                if (*(char*)(plVar9 + 0x3c)
                    != '\x01') {
                    break;   // the walker RED
                }
                plVar8d = *(char**)plVar7x;  // P->L
                if (plVar9 == plVar8d) {
                    // the walker IS P->left: sib =
                    // P->right
                    plVar8d = *(char**)(plVar7x + 0x10);
                    if (*(char*)(plVar8d + 0x3c)
                        == '\0') {
                        *(char*)(plVar8d + 0x3c) = 1;
                        *(char*)(plVar7x + 0x3c) = 0;
                        MembersRotateR(pMap, plVar7x);
                        plVar8d =
                            *(char**)(plVar7x + 0x10);
                    }
                    if (*(char*)(plVar8d + 0x3d)
                        == '\0') {
                        if ((*(char*)(*(char**)plVar8d
                            + 0x3c) != '\x01')
                            || (*(char*)(*(char**)(plVar8d
                                + 0x10) + 0x3c)
                                != '\x01')) {
                            if (*(char*)(*(char**)(plVar8d
                                + 0x10) + 0x3c)
                                == '\x01') {
                                *(char*)(*(char**)plVar8d
                                    + 0x3c) = 1;
                                *(char*)(plVar8d + 0x3c) = 0;
                                MembersRotateL(pMap,
                                    plVar8d);
                                plVar8d =
                                    *(char**)(plVar7x
                                        + 0x10);
                            }
                            *(char*)(plVar8d + 0x3c) =
                                *(char*)(plVar7x + 0x3c);
                            *(char*)(plVar7x + 0x3c) = 1;
                            *(char*)(*(char**)(plVar8d
                                + 0x10) + 0x3c) = 1;
                            MembersRotateR(pMap,
                                plVar7x);
                            break;
                        }
                        *(char*)(plVar8d + 0x3c) = 0;
                    }
                } else {
                    // the walker IS P->right: sib =
                    // P->left
                    if (*(char*)(plVar8d + 0x3c)
                        == '\0') {
                        *(char*)(plVar8d + 0x3c) = 1;
                        *(char*)(plVar7x + 0x3c) = 0;
                        MembersRotateL(pMap, plVar7x);
                        plVar8d = *(char**)plVar7x;
                    }
                    if (*(char*)(plVar8d + 0x3d)
                        == '\0') {
                        if ((*(char*)(*(char**)(plVar8d
                            + 0x10) + 0x3c) != '\x01')
                            || (*(char*)(*(char**)plVar8d
                                + 0x3c) != '\x01')) {
                            if (*(char*)(*(char**)plVar8d
                                + 0x3c) == '\x01') {
                                *(char*)(*(char**)(plVar8d
                                    + 0x10) + 0x3c) = 1;
                                *(char*)(plVar8d + 0x3c) = 0;
                                MembersRotateR(pMap,
                                    plVar8d);
                                plVar8d = *(char**)plVar7x;
                            }
                            *(char*)(plVar8d + 0x3c) =
                                *(char*)(plVar7x + 0x3c);
                            *(char*)(plVar7x + 0x3c) = 1;
                            *(char*)(*(char**)plVar8d
                                + 0x3c) = 1;
                            MembersRotateL(pMap,
                                plVar7x);
                            break;
                        }
                        *(char*)(plVar8d + 0x3c) = 0;
                    }
                }
                plVar8x = *(char**)(plVar7x + 8);
                plVar9 = plVar7x;
            } while (plVar7x != *(char**)(head + 8));
        }
        *(char*)(plVar9 + 0x3c) = 1;
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

// ================= FUN_1417481d0 =================
// the erase-range: the owner checks + the both-end
// clear + the inline successor advance loop
void* MembersEraseRange(void* pMap, void* pOutIter,
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
            MembersClear((void*)param_1);
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
        if (*(char*)(lVar4 + 0x3d) == '\0') {
            plVar6 = *(char**)(lVar4 + 0x10);
            if (*(char*)(plVar6 + 0x3d) == '\0') {
                cVar1 = *(char*)(*(char**)plVar6 + 0x3d);
                plVar5 = *(char**)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5 + 0x3d);
                    plVar6 = plVar5;
                    plVar5 = *(char**)plVar5;
                }
            } else {
                plVar6 = *(char**)(lVar4 + 8);
                cVar1 = *(char*)(plVar6 + 0x3d);
                while (cVar1 == '\0'
                    && (param_3[1]
                        == *(char**)(plVar6 + 0x10))) {
                    param_3[1] = (char*)plVar6;
                    plVar6 = *(char**)(plVar6 + 8);
                    cVar1 = *(char*)(plVar6 + 0x3d);
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
        MembersErase((void*)param_1,
            (void*)local_18, (void*)local_28);
    }
    char* lVar2c = (char*)param_3[1];
    *param_2 = *(char**)param_1;
    param_2[1] = lVar2c;
    return param_2;
}

// ================= FUN_1417471f0 =================
// the clear: the root walk (the right-subtree
// recursive frees + delete + the left advance) +
// the head relinks + size 0
void MembersClear(void* pMap) {
    char* param_1 = (char*)pMap;
    char* head = *(char**)(param_1 + 0x30);
    char** plVar2 = *(char***)(head + 8);  // root
    char cVar1 = *(char*)((char*)plVar2 + 0x3d);
    while (cVar1 == '\0') {
        MembersFreeSubtree(pMap,
            *(char**)(plVar2 + 2));   // the right
        char** plVar3 = *(char***)plVar2;
        g_fnMeritOpDelete((void*)plVar2);
        plVar2 = plVar3;
        cVar1 = *(char*)((char*)plVar3 + 0x3d);
    }
    *(char**)(head + 8) = head;   // root = head
    *(uint64_t*)(param_1 + 0x38) = 0;
    *(char**)head = head;         // left = first
    *(char**)(head + 0x10) = head; // right = last
}

} // namespace syndicate
