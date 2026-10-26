// ============================================================
// Syndicate.dll port — T16/D41b: the mgr family
// erase-ones + leaves, verbatim (see the .h).
// ============================================================
#include "SyndicateLeagueMgrErOne.h"
#include "SyndicateCrossMerit.h"
#include "SyndicateLeagueMgrErase.h"   // g_fnNestedErA/B
#include <stdexcept>

namespace syndicate {

// ============ the advance (141753470-class) ============
// the {proxy, node} iterator++ : the descend to the
// leftmost of the right, or the climb past the
// was-right links; the END iterator → the CRT invalid
static void AdvTmpl(int64_t* it, int isnil) {
    if (it[0] == 0) {
        g_fnMeritInvalid();
    }
    char* node = (char*)it[1];
    if (*(char*)(node + isnil) == '\0') {
        char** plVar3 = *(char***)(node + 0x10);  // right
        if (*(char*)((char*)plVar3 + isnil) != '\0') {
            // right is nil → climb
            char* lVar2 = *(char**)(node + 8);   // parent
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
        // right not nil → the leftmost of the right
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
    // (the END iterator advance — the CRT invalid)
    g_fnMeritInvalid();
}
void MgrAdv29A(int64_t* it) { AdvTmpl(it, 0x29); }
void MgrAdv29B(int64_t* it) { AdvTmpl(it, 0x29); }
void MgrAdv69(int64_t* it)  { AdvTmpl(it, 0x69); }
void MgrAdv29C(int64_t* it) { AdvTmpl(it, 0x29); }
void MgrAdv29D(int64_t* it) { AdvTmpl(it, 0x29); }
void MgrAdv29E(int64_t* it) { AdvTmpl(it, 0x29); }
void MgrAdv59(int64_t* it)  { AdvTmpl(it, 0x59); }
void MgrAdv61A(int64_t* it) { AdvTmpl(it, 0x61); }
void MgrAdv61B(int64_t* it) { AdvTmpl(it, 0x61); }

// ============ the rotates (141752cd0/141752d30) ============
// rotA: y = x->right; x->right = y->left; the relinks
static void RotATmpl(void* pMap, void* pX, int isnil) {
    char** param_1 = (char**)pMap;
    char* x = (char*)pX;
    char* y = *(char**)(x + 0x10);          // x->right
    *(char**)(x + 0x10) = *(char**)y;        // = y->left
    if (*(char*)(*(char**)y + isnil) == '\0') {
        *(char**)(*(char**)y + 8) = x;      // y->l->par = x
    }
    *(char**)(y + 8) = *(char**)(x + 8);     // y->par = x->par
    char* head = *(char**)((char*)param_1 + 0x30);
    if (x == *(char**)(head + 8)) {         // x was root
        *(char**)(head + 8) = y;
        *(char**)y = x;
        *(char**)(x + 8) = y;
        return;
    }
    char* par = *(char**)(x + 8);
    if (x == *(char**)par) {                // x was left
        *(char**)par = y;
    } else {
        *(char**)(par + 0x10) = y;          // par->right
    }
    *(char**)y = x;                         // y->LEFT = x
    *(char**)(x + 8) = y;
}
// rotB: the mirror (y = x->left)
static void RotBTmpl(void* pMap, void* pX, int isnil) {
    char** param_1 = (char**)pMap;
    char* x = (char*)pX;
    char* y = *(char**)x;                    // x->left
    *(char**)x = *(char**)(y + 0x10);       // x->l = y->right
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
    if (x == *(char**)(par + 0x10)) {       // x was right
        *(char**)(par + 0x10) = y;
        *(char**)(y + 0x10) = x;
        *(char**)(x + 8) = y;
        return;
    }
    *(char**)par = y;
    *(char**)(y + 0x10) = x;
    *(char**)(x + 8) = y;
}
void MgrRotA29A(void* m, void* n) { RotATmpl(m, n, 0x29); }
void MgrRotB29A(void* m, void* n) { RotBTmpl(m, n, 0x29); }
void MgrRotA29B(void* m, void* n) { RotATmpl(m, n, 0x29); }
void MgrRotB29B(void* m, void* n) { RotBTmpl(m, n, 0x29); }
void MgrRotA69(void* m, void* n)  { RotATmpl(m, n, 0x69); }
void MgrRotB69(void* m, void* n)  { RotBTmpl(m, n, 0x69); }
void MgrRotA29C(void* m, void* n) { RotATmpl(m, n, 0x29); }
void MgrRotB29C(void* m, void* n) { RotBTmpl(m, n, 0x29); }
void MgrRotA29D(void* m, void* n) { RotATmpl(m, n, 0x29); }
void MgrRotB29D(void* m, void* n) { RotBTmpl(m, n, 0x29); }
void MgrRotA29E(void* m, void* n) { RotATmpl(m, n, 0x29); }
void MgrRotB29E(void* m, void* n) { RotBTmpl(m, n, 0x29); }
void MgrRotA59(void* m, void* n)  { RotATmpl(m, n, 0x59); }
void MgrRotB59(void* m, void* n)  { RotBTmpl(m, n, 0x59); }
void MgrRotA61A(void* m, void* n) { RotATmpl(m, n, 0x61); }
void MgrRotB61A(void* m, void* n) { RotBTmpl(m, n, 0x61); }
void MgrRotA61B(void* m, void* n) { RotATmpl(m, n, 0x61); }
void MgrRotB61B(void* m, void* n) { RotBTmpl(m, n, 0x61); }

// ============ the family erase-ones ============
// (verbatim from 141758050; the family differences =
//  the isnil + the color qword index + the leaf trio +
//  the SPECIAL nested-map destroy before the node
//  delete)
typedef void (*FnAdv)(int64_t*);
typedef void (*FnRot)(void*, void*);
typedef void* (*FnNestedEr2)(void*, void*, void*, void*);

static void* ErOneTmpl(void* pMap, void* pOut, void* pIt,
                       int isnil, int colorIdx,
                       FnAdv advance, FnRot rotA,
                       FnRot rotB, FnNestedEr2 nestedEr) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    int64_t* param_3 = (int64_t*)pIt;
    char** plVar2 = (char**)param_3[1];      // the node
    if (*(char*)((char*)plVar2 + isnil) != '\0') {
        // the CRT out_of_range throw (verbatim)
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    advance(param_3);
    char** plVar8 = *(char***)plVar2;        // node->left
    char** plVar9;
    char** plVar7 = nullptr;   // (the splice/fixup walker)
    if (*(char*)((char*)plVar8 + isnil) == '\0') {
        plVar9 = plVar8;
        if (*(char*)((char*)(plVar2[2]) + isnil) == '\0') {
            // two children → the successor splice
            plVar7 = (char**)param_3[1];  // succ
            plVar9 = (char**)plVar7[2];          // succ->r
            if (plVar7 != plVar2) {
                plVar8[1] = (char*)plVar7;     // l->par=succ
                *plVar7 = *plVar2;               // succ->l = l
                plVar8 = plVar7;
                if (plVar7 != (char**)plVar2[2]) {
                    plVar8 = (char**)plVar7[1];  // succ->par
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
                plVar7[1] = plVar2[1];   // succ->par = node->par
                // the color swap (verbatim)
                char** plVar3 = plVar2 + colorIdx;
                char** plVar7c = plVar7 + colorIdx;
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
        plVar9 = (char**)plVar2[2];      // the right
    }
    // one/zero child → the relink
    plVar8 = (char**)plVar2[1];          // the parent
    if (*(char*)((char*)plVar9 + isnil) == '\0') {
        plVar9[1] = (char*)plVar8;     // child->par
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
        // the FIRST patch (verbatim: the leftmost walk)
        if (*(char**)head == (char*)plVar2) {
            char** plVar7 = plVar8;
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
        // the LAST patch (verbatim: the rightmost walk)
        if (*(char**)(head + 0x10) == (char*)plVar2) {
            char** plVar7 = plVar8;
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
    // the FULL RB-erase fixup loop (verbatim; 1 = the
    // BLACK color, 0 = the RED color, as the head ctor
    // and the loop guard prove)
    if (*(char*)((char*)plVar2 + colorIdx * 8) == 1) {
        char* head = *(char**)((char*)param_1 + 0x30);
        if ((char*)plVar9 != *(char**)(head + 8)) {
            char** plVar7 = nullptr;
            do {
                plVar7 = plVar8;
                if (*(char*)((char*)plVar9 + colorIdx * 8)
                        != 1) break;   // the node is red
                plVar8 = *(char***)plVar7;   // the left
                if (plVar9 == plVar8) {
                    // the node was the LEFT child →
                    // the sibling = the parent's RIGHT
                    plVar8 = (char**)(plVar7[2]);
                    if (*(char*)((char*)plVar8
                                 + colorIdx * 8) == 0) {
                        // the sibling red → the case 3
                        *(char*)((char*)plVar8
                                 + colorIdx * 8) = 1;
                        *(char*)((char*)plVar7
                                 + colorIdx * 8) = 0;
                        rotA(pMap, (char*)plVar7);
                        plVar8 = (char**)(plVar7[2]);
                    }
                    if (*(char*)((char*)plVar8 + isnil)
                            == '\0') {
                        if ((*(char*)(*(char**)plVar8
                                      + colorIdx * 8) != 1)
                            || (*(char*)((char*)(plVar8[2])
                                         + colorIdx * 8)
                                    != 1)) {
                            // not both-black children
                            if (*(char*)((char*)(plVar8[2])
                                         + colorIdx * 8)
                                    == 1) {
                                // the right black → 5
                                *(char*)(*(char**)plVar8
                                         + colorIdx * 8) = 1;
                                *(char*)((char*)plVar8
                                         + colorIdx * 8) = 0;
                                rotB(pMap, (char*)plVar8);
                                plVar8 =
                                    (char**)(plVar7[2]);
                            }
                            *(char*)((char*)plVar8
                                     + colorIdx * 8) =
                                *(char*)((char*)plVar7
                                         + colorIdx * 8);
                            *(char*)((char*)plVar7
                                     + colorIdx * 8) = 1;
                            *(char*)((char*)(plVar8[2])
                                     + colorIdx * 8) = 1;
                            rotA(pMap, (char*)plVar7);
                            break;
                        }
                        // both black → the case 2
                        *(char*)((char*)plVar8
                                 + colorIdx * 8) = 0;
                    }
                }
                else {
                    // the node was the RIGHT child →
                    // the sibling = the parent's LEFT
                    if (*(char*)((char*)plVar8
                                 + colorIdx * 8) == 0) {
                        *(char*)((char*)plVar8
                                 + colorIdx * 8) = 1;
                        *(char*)((char*)plVar7
                                 + colorIdx * 8) = 0;
                        rotB(pMap, (char*)plVar7);
                        plVar8 = *(char***)plVar7;
                    }
                    if (*(char*)((char*)plVar8 + isnil)
                            == '\0') {
                        if ((*(char*)(*(char**)plVar8
                                      + colorIdx * 8) != 1)
                            || (*(char*)((char*)(plVar8[2])
                                         + colorIdx * 8)
                                    != 1)) {
                            if (*(char*)(*(char**)plVar8
                                         + colorIdx * 8)
                                    == 1) {
                                *(char*)((char*)(plVar8[2])
                                         + colorIdx * 8) = 1;
                                *(char*)((char*)plVar8
                                         + colorIdx * 8) = 0;
                                rotA(pMap, (char*)plVar8);
                                plVar8 = *(char***)plVar7;
                            }
                            *(char*)((char*)plVar8
                                     + colorIdx * 8) =
                                *(char*)((char*)plVar7
                                         + colorIdx * 8);
                            *(char*)((char*)plVar7
                                     + colorIdx * 8) = 1;
                            *(char*)(*(char**)plVar8
                                     + colorIdx * 8) = 1;
                            rotB(pMap, (char*)plVar7);
                            break;
                        }
                        *(char*)((char*)plVar8
                                 + colorIdx * 8) = 0;
                    }
                }
                plVar8 = (char**)(plVar7[1]);   // the parent
                plVar9 = plVar7;
            } while ((char*)plVar7
                     != *(char**)(head + 8));
        }
        *(char*)((char*)plVar9 + colorIdx * 8) = 1;
    }
    // the SPECIAL nested-map destroy (verbatim tail of
    // 141770a20/141773e60) + the node delete + the size
    if (nestedEr != nullptr) {
        char** nestedMap = plVar2 + 4;         // +0x20
        char* nhead = *(char**)(plVar2 + 10);  // +0x50
        int64_t local_b8 = *(int64_t*)nestedMap;  // proxy
        int64_t uStack_b0 = *(int64_t*)nhead;    // first
        int64_t local_a8 = local_b8;
        int64_t pair1[2] = { local_b8, uStack_b0 };
        int64_t pair2[2] = { local_a8, (int64_t)nhead };
        int64_t out[2];
        nestedEr(nestedMap, out, pair1, pair2);
        g_fnMeritOpDelete(*(void**)(plVar2 + 10));
        plVar2[10] = nullptr;
        plVar2[11] = nullptr;
        g_fnMeritOpDelete(*(void**)nestedMap);
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

void* MgrErOne38(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x29, 5,
                     MgrAdv29A, MgrRotA29A, MgrRotB29A,
                     nullptr); }
void* MgrErOne538(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x29, 5,
                     MgrAdv29B, MgrRotA29B, MgrRotB29B,
                     nullptr); }
void* MgrErOne4f8(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x69, 0xd,
                     MgrAdv69, MgrRotA69, MgrRotB69,
                     nullptr); }
void* MgrErOne4b0(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x29, 5,
                     MgrAdv29C, MgrRotA29C, MgrRotB29C,
                     nullptr); }
void* MgrErOne470(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x61, 0xc,
                     MgrAdv61A, MgrRotA61A, MgrRotB61A,
                     g_fnNestedErA); }
void* MgrErOne318(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x29, 5,
                     MgrAdv29D, MgrRotA29D, MgrRotB29D,
                     nullptr); }
void* MgrErOne2b0(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x61, 0xc,
                     MgrAdv61B, MgrRotA61B, MgrRotB61B,
                     g_fnNestedErB); }
void* MgrErOne228(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x29, 5,
                     MgrAdv29E, MgrRotA29E, MgrRotB29E,
                     nullptr); }
void* MgrErOne108(void* m, void* o, void* it) {
    return ErOneTmpl(m, o, it, 0x59, 0xb,
                     MgrAdv59, MgrRotA59, MgrRotB59,
                     nullptr); }

}  // namespace syndicate
