// ============================================================
// Syndicate.dll port — T16/D41c: the nested families,
// verbatim (see the .h). The leaf templates are the same
// shapes as the mgr unit's (D41b) with the family isnil;
// the erase-one uses the BYTE color offset (the nested
// color pair +0x1c/+0x2c is not qword-aligned).
// ============================================================
#include "SyndicateLeagueMgrNested.h"
#include "SyndicateCrossMerit.h"
#include <stdexcept>

namespace syndicate {

// ============ the advance (141724ed0 / 141750760) ============
static void NestedAdv(int64_t* it, int isnil) {
    if (it[0] == 0) {
        g_fnMeritInvalid();
    }
    char* node = (char*)it[1];
    if (*(char*)(node + isnil) == '\0') {
        char** plVar3 = *(char***)(node + 0x10);  // right
        if (*(char*)((char*)plVar3 + isnil) != '\0') {
            // right is nil → climb past the was-right
            char* lVar2 = *(char**)(node + 8);
            char cVar1 = *(char*)(lVar2 + isnil);
            while ((cVar1 == '\0')
                   && (it[1] == *(int64_t*)(lVar2 + 0x10))) {
                it[1] = (int64_t)lVar2;
                lVar2 = *(char**)(lVar2 + 8);
                cVar1 = *(char*)(lVar2 + isnil);
            }
            it[1] = (int64_t)lVar2;
            return;
        }
        // the leftmost of the right
        char cVar1 = *(char*)(*(char**)plVar3 + isnil);
        char** plVar4 = *(char***)plVar3;
        while (cVar1 == '\0') {
            cVar1 = *(char*)(*(char**)plVar4 + isnil);
            plVar3 = plVar4;
            plVar4 = *(char***)plVar4;
        }
        it[1] = (int64_t)plVar3;
        return;
    }
    g_fnMeritInvalid();   // the END iterator (the CRT)
}

// ============ the rotates (141724c50/141724cb0-class) ============
static void NestedRotA(void* pMap, void* pX, int isnil) {
    char** param_1 = (char**)pMap;
    char* x = (char*)pX;
    char* y = *(char**)(x + 0x10);           // x->right
    *(char**)(x + 0x10) = *(char**)y;         // = y->left
    if (*(char*)(*(char**)y + isnil) == '\0') {
        *(char**)(*(char**)y + 8) = x;
    }
    *(char**)(y + 8) = *(char**)(x + 8);
    char* head = *(char**)((char*)param_1 + 0x30);
    if (x == *(char**)(head + 8)) {
        *(char**)(head + 8) = y;
        *(char**)y = x;                       // y->LEFT = x
        *(char**)(x + 8) = y;
        return;
    }
    char* par = *(char**)(x + 8);
    if (x == *(char**)par) {
        *(char**)par = y;
    } else {
        *(char**)(par + 0x10) = y;
    }
    *(char**)y = x;                           // y->LEFT = x
    *(char**)(x + 8) = y;
}
static void NestedRotB(void* pMap, void* pX, int isnil) {
    char** param_1 = (char**)pMap;
    char* x = (char*)pX;
    char* y = *(char**)x;                     // x->left
    *(char**)x = *(char**)(y + 0x10);         // x->l = y->right
    if (*(char*)(*(char**)(y + 0x10) + isnil) == '\0') {
        *(char**)(*(char**)(y + 0x10) + 8) = x;
    }
    *(char**)(y + 8) = *(char**)(x + 8);
    char* head = *(char**)((char*)param_1 + 0x30);
    if (x == *(char**)(head + 8)) {
        *(char**)(head + 8) = y;
        *(char**)(y + 0x10) = x;
        *(char**)(x + 8) = y;
        return;
    }
    char* par = *(char**)(x + 8);
    if (x == *(char**)(par + 0x10)) {         // x was right
        *(char**)(par + 0x10) = y;
        *(char**)(y + 0x10) = x;
        *(char**)(x + 8) = y;
        return;
    }
    *(char**)par = y;
    *(char**)(y + 0x10) = x;
    *(char**)(x + 8) = y;
}

// ============ the nested erase-one (141728290/1417614e0) ============
// (the mgr template with the BYTE color offset — 1 =
//  BLACK, 0 = RED, the CRT out_of_range throw)
typedef void (*NAdv)(int64_t*);
typedef void (*NRot)(void*, void*);

static void* NestedErOneTmpl(void* pMap, void* pOut, void* pIt,
                             int isnil, int colorOff,
                             NAdv advance, NRot rotA,
                             NRot rotB) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    int64_t* param_3 = (int64_t*)pIt;
    char** plVar2 = (char**)param_3[1];      // the node
    char** plVar7 = nullptr;   // (the splice/fixup walker)
    if (*(char*)((char*)plVar2 + isnil) != '\0') {
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    advance(param_3);
    char** plVar8 = *(char***)plVar2;        // node->left
    char** plVar9;
    if (*(char*)((char*)plVar8 + isnil) == '\0') {
        plVar9 = plVar8;
        if (*(char*)((char*)(plVar2[2]) + isnil) == '\0') {
            // two children → the successor splice
            plVar7 = (char**)param_3[1];      // succ
            plVar9 = (char**)plVar7[2];       // succ->r
            if (plVar7 != plVar2) {
                plVar8[1] = (char*)plVar7;    // l->par=succ
                *plVar7 = *plVar2;            // succ->l = l
                plVar8 = plVar7;
                if (plVar7 != (char**)plVar2[2]) {
                    plVar8 = (char**)(plVar7[1]);  // succ->par
                    if (*(char*)((char*)plVar9 + isnil) == '\0') {
                        plVar9[1] = (char*)plVar8;
                    }
                    *plVar8 = (char*)plVar9;
                    plVar7[2] = plVar2[2];
                    *(char**)((char*)(plVar2[2]) + 8) = (char*)plVar7;
                }
                char* head = *(char**)((char*)param_1 + 0x30);
                if (*(char**)(head + 8) == (char*)plVar2) {
                    *(char**)(head + 8) = (char*)plVar7;
                } else {
                    char** puVar4 = *(char***)(plVar2[1]);
                    if ((char**)*puVar4 == plVar2) {
                        *puVar4 = (char*)plVar7;
                    } else {
                        puVar4[2] = (char*)plVar7;
                    }
                }
                plVar7[1] = plVar2[1];
                // the color swap (BYTE addressing — the
                // +0x1c/+0x2c pair)
                char* plVar3 = (char*)plVar2 + colorOff;
                char* plVar7c = (char*)plVar7 + colorOff;
                if (plVar7c != plVar3) {
                    char lVar5 = *(char*)plVar7c;
                    *(char*)plVar7c = *(char*)plVar3;
                    *(char*)plVar3 = lVar5;
                }
                goto LAB_FIXUP;
            }
        }
    }
    else {
        plVar9 = (char**)(plVar2[2]);      // the right
    }
    // one/zero child → the relink
    plVar8 = (char**)(plVar2[1]);          // the parent
    if (*(char*)((char*)plVar9 + isnil) == '\0') {
        plVar9[1] = (char*)plVar8;         // child->par
    }
    {
        char* head = *(char**)((char*)param_1 + 0x30);
        if (*(char**)(head + 8) == (char*)plVar2) {
            *(char**)(head + 8) = (char*)plVar9;
        } else if ((char**)*plVar8 == plVar2) {
            *plVar8 = (char*)plVar9;
        } else {
            plVar8[2] = (char*)plVar9;
        }
        // the FIRST patch (the leftmost walk)
        if (*(char**)head == (char*)plVar2) {
            plVar7 = plVar8;
            if (*(char*)((char*)plVar9 + isnil) == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar9 + isnil);
                char** plVar3 = *(char***)plVar9;
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                        cVar1 == '\0')) {
                    plVar3 = *(char***)plVar6;
                    cVar1 =
                        *(char*)((char*)plVar3 + isnil);
                    plVar7 = plVar6;
                }
            }
            *(char**)head = (char*)plVar7;
        }
        // the LAST patch (the rightmost walk)
        if (*(char**)(head + 0x10) == (char*)plVar2) {
            plVar7 = plVar8;
            if (*(char*)((char*)plVar9 + isnil) == '\0') {
                char cVar1 =
                    *(char*)((char*)(plVar9[2]) + isnil);
                char** plVar3 = (char**)(plVar9[2]);
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                        cVar1 == '\0')) {
                    plVar3 = (char**)(plVar6[2]);
                    cVar1 =
                        *(char*)((char*)plVar3 + isnil);
                    plVar7 = plVar6;
                }
            }
            *(char**)(head + 0x10) = (char*)plVar7;
        }
    }
LAB_FIXUP:
    // the FULL RB-erase fixup loop (1 = BLACK, 0 = RED)
    if (*(char*)((char*)plVar2 + colorOff) == 1) {
        char* head = *(char**)((char*)param_1 + 0x30);
        if ((char*)plVar9 != *(char**)(head + 8)) {
            do {
                plVar7 = plVar8;
                if (*(char*)((char*)plVar9 + colorOff)
                        != 1) break;   // the node is red
                plVar8 = *(char***)plVar7;   // the left
                if (plVar9 == plVar8) {
                    // the node was the LEFT child → the
                    // sibling = the parent's RIGHT
                    plVar8 = (char**)(plVar7[2]);
                    if (*(char*)((char*)plVar8
                                 + colorOff) == 0) {
                        // the sibling red → the case 3
                        *(char*)((char*)plVar8
                                 + colorOff) = 1;
                        *(char*)((char*)plVar7
                                 + colorOff) = 0;
                        rotA(pMap, (char*)plVar7);
                        plVar8 = (char**)(plVar7[2]);
                    }
                    if (*(char*)((char*)plVar8 + isnil)
                            == '\0') {
                        if ((*(char*)(*(char**)plVar8
                                      + colorOff) != 1)
                            || (*(char*)((char*)(plVar8[2])
                                         + colorOff)
                                    != 1)) {
                            // not both-black children
                            if (*(char*)((char*)(plVar8[2])
                                         + colorOff)
                                    == 1) {
                                // the right black → 5
                                *(char*)(*(char**)plVar8
                                         + colorOff) = 1;
                                *(char*)((char*)plVar8
                                         + colorOff) = 0;
                                rotB(pMap, (char*)plVar8);
                                plVar8 =
                                    (char**)(plVar7[2]);
                            }
                            *(char*)((char*)plVar8
                                     + colorOff) =
                                *(char*)((char*)plVar7
                                         + colorOff);
                            *(char*)((char*)plVar7
                                     + colorOff) = 1;
                            *(char*)((char*)(plVar8[2])
                                     + colorOff) = 1;
                            rotA(pMap, (char*)plVar7);
                            break;
                        }
                        // both black → the case 2
                        *(char*)((char*)plVar8
                                 + colorOff) = 0;
                    }
                }
                else {
                    // the node was the RIGHT child → the
                    // sibling = the parent's LEFT
                    if (*(char*)((char*)plVar8
                                 + colorOff) == 0) {
                        *(char*)((char*)plVar8
                                 + colorOff) = 1;
                        *(char*)((char*)plVar7
                                 + colorOff) = 0;
                        rotB(pMap, (char*)plVar7);
                        plVar8 = *(char***)plVar7;
                    }
                    if (*(char*)((char*)plVar8 + isnil)
                            == '\0') {
                        if ((*(char*)(*(char**)plVar8
                                      + colorOff) != 1)
                            || (*(char*)((char*)(plVar8[2])
                                         + colorOff)
                                    != 1)) {
                            if (*(char*)(*(char**)plVar8
                                         + colorOff)
                                    == 1) {
                                *(char*)((char*)(plVar8[2])
                                         + colorOff) = 1;
                                *(char*)((char*)plVar8
                                         + colorOff) = 0;
                                rotA(pMap, (char*)plVar8);
                                plVar8 = *(char***)plVar7;
                            }
                            *(char*)((char*)plVar8
                                     + colorOff) =
                                *(char*)((char*)plVar7
                                         + colorOff);
                            *(char*)((char*)plVar7
                                     + colorOff) = 1;
                            *(char*)(*(char**)plVar8
                                     + colorOff) = 1;
                            rotB(pMap, (char*)plVar7);
                            break;
                        }
                        *(char*)((char*)plVar8
                                 + colorOff) = 0;
                    }
                }
                plVar8 = (char**)(plVar7[1]);   // the parent
                plVar9 = plVar7;
            } while ((char*)plVar7
                     != *(char**)(head + 8));
        }
        *(char*)((char*)plVar9 + colorOff) = 1;
    }
    g_fnMeritOpDelete(plVar2);
    if (param_1[7] != 0) {
        param_1[7] = param_1[7] - 1;
    }
    int64_t lVar5 = param_3[1];
    *param_2 = *param_1;
    param_2[1] = (char*)lVar5;
    return param_2;
}

// ============ the family entries ============
static void NestedAdvA(int64_t* it) { NestedAdv(it, 0x1d); }
static void NestedAdvB(int64_t* it) { NestedAdv(it, 0x2d); }

void* NestedErOneA(void* m, void* o, void* it) {
    return NestedErOneTmpl(m, o, it, 0x1d, 0x1c,
        NestedAdvA,
        [](void* pm, void* n) { NestedRotA(pm, n, 0x1d); },
        [](void* pm, void* n) { NestedRotB(pm, n, 0x1d); });
}
void* NestedErOneB(void* m, void* o, void* it) {
    return NestedErOneTmpl(m, o, it, 0x2d, 0x2c,
        NestedAdvB,
        [](void* pm, void* n) { NestedRotA(pm, n, 0x2d); },
        [](void* pm, void* n) { NestedRotB(pm, n, 0x2d); });
}

// ============ the subtree erasers (141726210/1417540c0) ============
// recursive: the right subtree recursion + the left
// spine loop + the node deletes
static void NestedSubtreeTmpl(void* pMap, char* node,
                              int isnil) {
    char cVar1 = *(char*)(node + isnil);
    while (cVar1 == '\0') {
        NestedSubtreeTmpl(pMap, *(char**)(node + 0x10),
                         isnil);
        char** plVar2 = *(char***)node;       // the left
        g_fnMeritOpDelete(node);
        node = (char*)plVar2;
        cVar1 = *(char*)(node + isnil);
    }
}
void NestedSubtreeA(void* m, void* n) {
    NestedSubtreeTmpl(m, (char*)n, 0x1d); }
void NestedSubtreeB(void* m, void* n) {
    NestedSubtreeTmpl(m, (char*)n, 0x2d); }

// ============ the clears (141727640/1417567f0) ============
static void NestedClearTmpl(void* pMap, int isnil) {
    char* head = *(char**)((char*)pMap + 0x30);
    char** plVar2 = *(char***)(head + 8);    // the root
    while (*(char*)((char*)plVar2 + isnil) == '\0') {
        // destroy the root's RIGHT subtree recursively
        NestedSubtreeTmpl(pMap,
                         *(char**)((char*)plVar2 + 0x10),
                         isnil);
        char** plVar3 = *(char***)plVar2;     // the left
        g_fnMeritOpDelete(plVar2);
        plVar2 = plVar3;
    }
    // the head self-links + the size reset
    *(char**)(head + 8) = head;
    *(int64_t*)((char*)pMap + 0x38) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}
void NestedClearA(void* m) { NestedClearTmpl(m, 0x1d); }
void NestedClearB(void* m) { NestedClearTmpl(m, 0x2d); }

// ============ the erase-ranges (14172a410/141762db0) ====
// the CRT pair gates + the whole-map clear shortcut +
// the advance + erase-one loop
static void* NestedErRangeTmpl(void* pMap, void* pOut,
                               int64_t* pFirst,
                               int64_t* pLast,
                               int isnil,
                               void (*clearFn)(void*),
                               void* (*erOne)(void*, void*,
                                              void*)) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    char* firstNode = *(char**)param_1[6];  // *head (FIRST)
    if (pFirst[0] == 0 || pFirst[0] != *(int64_t*)param_1) {
        g_fnMeritInvalid();
    }
    if (pFirst[1] == (int64_t)firstNode) {
        // the first-pair IS begin → maybe the full clear
        char* head = (char*)param_1[6];
        if (pLast[0] == 0
            || pLast[0] != *(int64_t*)param_1) {
            g_fnMeritInvalid();
        }
        if (pLast[1] == (int64_t)head) {
            // [begin, end) → the clear (verbatim)
            clearFn(pMap);
            param_2[1] = *(char**)param_1[6];
            *param_2 = *param_1;
            return param_2;
        }
    }
    while (true) {
        if (pFirst[0] == 0
            || pFirst[0] != pLast[0]) {
            g_fnMeritInvalid();
        }
        int64_t lVar2 = pFirst[0];           // the proxy
        if (pFirst[1] == pLast[1]) break;
        int64_t lVar3 = pFirst[1];           // the node
        if (pFirst[0] == 0) {
            g_fnMeritInvalid();
        }
        char* lVar4 = (char*)pFirst[1];
        if (*(char*)(lVar4 + isnil) == '\0') {
            // the inline advance (verbatim from the
            // range body: the descend when the right is
            // real, the climb otherwise)
            char** plVar6 = *(char***)(lVar4 + 0x10);
            if (*(char*)((char*)plVar6 + isnil)
                    != '\0') {
                // the right is nil → the climb (past the
                // was-right links)
                char** plVar6b = *(char***)(lVar4 + 8);
                char cVar1 =
                    *(char*)((char*)plVar6b + isnil);
                while ((cVar1 == '\0'
                        && (pFirst[1]
                            == *(int64_t*)((char*)plVar6b
                                           + 0x10)))) {
                    pFirst[1] = (int64_t)plVar6b;
                    plVar6b =
                        *(char***)((char*)plVar6b + 8);
                    cVar1 = *(char*)((char*)plVar6b
                                     + isnil);
                }
                pFirst[1] = (int64_t)plVar6b;
            }
            else {
                // the leftmost of the right
                char cVar1 =
                    *(char*)(*(char**)(plVar6) + isnil);
                char** plVar5 = *(char***)plVar6;
                while ((plVar6 = plVar5,
                        cVar1 == '\0')) {
                    plVar5 = *(char***)plVar6;
                    cVar1 = *(char*)(*(char**)(plVar6)
                                     + isnil);
                }
                pFirst[1] = (int64_t)plVar6;
            }
        }
        else {
            g_fnMeritInvalid();
        }
        // erase the OLD pair (verbatim)
        int64_t pair[2] = { lVar2, lVar3 };
        int64_t outIt[2];
        erOne(pMap, outIt, pair);
    }
    int64_t lVar2 = pFirst[1];
    *param_2 = *param_1;
    param_2[1] = (char*)lVar2;
    return param_2;
}

void* NestedErRangeA(void* m, void* o, void* f, void* l) {
    return NestedErRangeTmpl(m, o, (int64_t*)f,
                             (int64_t*)l, 0x1d,
                             NestedClearA, NestedErOneA);
}
void* NestedErRangeB(void* m, void* o, void* f, void* l) {
    return NestedErRangeTmpl(m, o, (int64_t*)f,
                             (int64_t*)l, 0x2d,
                             NestedClearB, NestedErOneB);
}

}  // namespace syndicate
