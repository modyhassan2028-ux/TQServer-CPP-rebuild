// Syndicate.dll — unit T5/D31 bodies (verbatim).
#include "SyndicateEraseLayer.h"
#include "SyndicateMapTree.h"
#include "SyndicateOwnTree.h"
#include "SyndicateCrossMerit.h"
#include <stdexcept>

namespace syndicate {

extern void (*g_fnMeritInvalid)();
extern void (*g_fnMeritOpDelete)(void* p);

// ================= FUN_14173b0e0 =================
// the rotation on the node's RIGHT child (0x28)
void OwnRotateR(void* pMap, void* pNode) {
    char* pmap = (char*)pMap;
    char* pc = (char*)pNode;
    char* pHead = *(char**)(pmap + 0x30);
    char** plVar1 = *(char***)(pc + 0x10);
    *(char**)(pc + 0x10) = *(char**)plVar1;
    if (*(char*)(*(char**)plVar1 + 0x21) == '\0') {
        *(char**)(*(char**)plVar1 + 8) = pc;
    }
    plVar1[1] = *(char**)(pc + 8);
    if (pc == *(char**)(pHead + 8)) {
        *(char**)(pHead + 8) = (char*)plVar1;
        *(char**)plVar1 = pc;
        *(char**)(pc + 8) = (char*)plVar1;
        return;
    }
    char** plVar2 = *(char***)(pc + 8);
    if (pc == *(char**)plVar2) {
        *(char**)plVar2 = (char*)plVar1;
        *(char**)plVar1 = pc;
        *(char**)(pc + 8) = (char*)plVar1;
        return;
    }
    plVar2[2] = (char*)plVar1;
    *(char**)plVar1 = pc;
    *(char**)(pc + 8) = (char*)plVar1;
}

// ================= FUN_14173b140 =================
// the rotation on the node's LEFT child (0x28)
void OwnRotateL(void* pMap, void* pNode) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pNode;
    char* pHead = *(char**)(pmap + 0x30);
    char* lVar1 = *(char**)param_2;     // the left
    *(char**)param_2 = *(char**)(lVar1 + 0x10);
    if (*(char*)(*(char**)(lVar1 + 0x10) + 0x21)
        == '\0') {
        *(char**)(*(char**)(lVar1 + 0x10) + 8)
            = (char*)param_2;
    }
    *(char**)(lVar1 + 8) = param_2[1];
    if ((char*)param_2 == *(char**)(pHead + 8)) {
        *(char**)(pHead + 8) = lVar1;
        *(char**)(lVar1 + 0x10) = (char*)param_2;
        param_2[1] = lVar1;
        return;
    }
    char** plVar2 = (char**)param_2[1];
    if ((char*)param_2
        == *(char**)(plVar2 + 2)) {   // P->right
        plVar2[2] = lVar1;
        *(char**)(lVar1 + 0x10) = (char*)param_2;
        param_2[1] = lVar1;
        return;
    }
    *(char**)plVar2 = lVar1;
    *(char**)(lVar1 + 0x10) = (char*)param_2;
    param_2[1] = lVar1;
}

// ================= FUN_14173c0b0 =================
// the 0x28 erase
void* OwnErase(void* pMap, void* pOutIter,
               void* pIterState) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIterState;
    char* pHead = *(char**)(pmap + 0x30);
    char** plVar2 = (char**)param_3[1];  // node
    if (*(char*)((char*)plVar2 + 0x21) != '\0') {
        // the past-the-end erase
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    OwnIterNext(param_3);
    char** plVar8 = *(char***)plVar2;   // the left
    char** plVar9;
    char** plVar8b = nullptr;
    if (*(char*)((char*)plVar8 + 0x21) == '\0') {
        plVar9 = plVar8;
        if (*(char*)((char*)(plVar2[2]) + 0x21)
            == '\0') {
            // both children: the successor swap
            char** plVar7 = (char**)param_3[1];
            plVar9 = (char**)plVar7[2];
            if (plVar7 != plVar2) {
                plVar8[1] = (char*)plVar7;
                *plVar7 = *(char**)plVar2;
                plVar8 = plVar7;
                if (plVar7
                    != (char**)(plVar2[2])) {
                    plVar8 = (char**)plVar7[1];
                    if (*(char*)((char*)plVar9
                        + 0x21) == '\0') {
                        plVar9[1] = (char*)plVar8;
                    }
                    *(char**)plVar8 = (char*)plVar9;
                    plVar7[2] = plVar2[2];
                    *(char**)(plVar2[2] + 8)
                        = (char*)plVar7;
                }
                if (*(char**)(pHead + 8)
                    == (char*)plVar2) {
                    *(char**)(pHead + 8)
                        = (char*)plVar7;
                } else {
                    char** puVar4 =
                        (char**)plVar2[1];
                    if ((char**)plVar2
                        == *(char***)puVar4) {
                        *(char**)puVar4 =
                            (char*)plVar7;
                    } else {
                        puVar4[2] = (char*)plVar7;
                    }
                }
                plVar7[1] = plVar2[1];
                // the color swap (+0x20)
                char* pa = (char*)(plVar2 + 4);
                char* pb = (char*)(plVar7 + 4);
                if (pb != pa) {
                    int64_t lVar5 = *(int64_t*)pb;
                    *(char*)pb = *(char*)pa;
                    *(char*)pa = (char)lVar5;
                }
                plVar8b = plVar8;   // succ's old P
                goto rebalance;
            }
        }
        // one or no children: the unlink
        plVar9 = plVar8;   // the left child
    } else {
        plVar9 = (char**)plVar2[2];  // the right
    }
    {
        plVar8b = (char**)plVar2[1];  // P
        if (*(char*)((char*)plVar9 + 0x21) == '\0') {
            plVar9[1] = (char*)plVar8b;
        }
        if (*(char**)(pHead + 8) == (char*)plVar2) {
            *(char**)(pHead + 8) = (char*)plVar9;
        } else if ((char*)plVar2
            == *(char**)plVar8b) {   // P->left
            *(char**)plVar8b = (char*)plVar9;
        } else {
            plVar8b[2] = (char*)plVar9;
        }
        // the first/last updates
        if (*(char**)pHead == (char*)plVar2) {
            char** plVar7 = plVar8b;
            if (*(char*)((char*)plVar9 + 0x21)
                == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar9 + 0x21);
                char** plVar3 = *(char***)plVar9;
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                    cVar1 == '\0')) {
                    plVar3 = *(char***)plVar6;
                    cVar1 = *(char*)((char*)plVar3
                        + 0x21);
                    plVar7 = plVar6;
                }
            }
            *(char**)pHead = (char*)plVar7;
        }
        if (*(char**)(pHead + 0x10)
            == (char*)plVar2) {
            char** plVar7 = plVar8b;
            if (*(char*)((char*)plVar9 + 0x21)
                == '\0') {
                char cVar1 = *(char*)
                    (plVar9[2] + 0x21);
                char** plVar3 = (char**)plVar9[2];
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                    cVar1 == '\0')) {
                    plVar3 =
                        (char**)(plVar6[2]);
                    cVar1 = *(char*)((char*)plVar3
                        + 0x21);
                    plVar7 = plVar6;
                }
            }
            *(char**)(pHead + 0x10) = (char*)plVar7;
        }
    }
rebalance:
    // the remove-rebalance (the verbatim c0b0 loop);
    // the entry P = the parent CAPTURED by the
    // unlink/swap path (the spliced slot may be
    // the head sentinel)
    if (*(char*)(plVar2 + 0x4) == '\x01') {
        char* root = *(char**)(pHead + 8);
        if (plVar9 != (char**)root) {
            char** plVar8x = plVar8b;   // P
            char** plVar7 = nullptr;
            do {
                plVar7 = plVar8x;                // P
                if (*(char*)(plVar9 + 0x4) != '\x01') {
                    break;   // the current is RED: done
                }
                char** plVar8d = *(char***)plVar7;   // P->left
                if (plVar9 == plVar8d) {
                    // the current IS P->left: the
                    // sibling = P->right
                    char** plVar8e = (char**)plVar7[2];
                    if (*(char*)(plVar8e + 0x4) == '\0') {
                        *(char*)(plVar8e + 0x4) = 1;
                        *(char*)(plVar7 + 0x4) = 0;
                        OwnRotateR(pmap, plVar7);
                        plVar8e = (char**)plVar7[2];
                    }
                    if (*(char*)((char*)plVar8e + 0x21)
                        == '\0') {
                        if ((*(char*)(*(char**)plVar8e
                            + 0x20) != '\x01')
                            || (*(char*)
                            (plVar8e[2] + 0x20)
                             != '\x01')) {
                            if (*(char*)
                                (plVar8e[2] + 0x20)
                                == '\x01') {
                                *(char*)
                                    (*(char**)plVar8e + 0x20)
                                    = 1;
                                *(char*)(plVar8e + 0x4) = 0;
                                OwnRotateL(pmap, plVar8e);
                                plVar8e = (char**)plVar7[2];
                            }
                            *(char*)(plVar8e + 0x4) =
                                *(char*)(plVar7 + 0x4);
                            *(char*)(plVar7 + 0x4) = 1;
                            *(char*)
                                (plVar8e[2] + 0x20)
                                = 1;
                            OwnRotateR(pmap, plVar7);
                            break;
                        }
                        *(char*)(plVar8e + 0x4) = 0;
                    }
                } else {
                    // the current IS P->right: the
                    // sibling = P->left
                    char** plVar8e = plVar8d;
                    if (*(char*)(plVar8d + 0x4) == '\0') {
                        *(char*)(plVar8d + 0x4) = 1;
                        *(char*)(plVar7 + 0x4) = 0;
                        OwnRotateL(pmap, plVar7);
                        plVar8e = *(char***)plVar7;
                    }
                    if (*(char*)((char*)plVar8e + 0x21)
                        == '\0') {
                        if ((*(char*)
                            (plVar8e[2] + 0x20)
                             != '\x01')
                            || (*(char*)(*(char**)plVar8e
                            + 0x20) != '\x01')) {
                            if (*(char*)(*(char**)plVar8e
                                + 0x20) == '\x01') {
                                *(char*)
                                    (plVar8e[2] + 0x20)
                                    = 1;
                                *(char*)(plVar8e + 0x4) = 0;
                                OwnRotateR(pmap, plVar8e);
                                plVar8e = *(char***)plVar7;
                            }
                            *(char*)(plVar8e + 0x4) =
                                *(char*)(plVar7 + 0x4);
                            *(char*)(plVar7 + 0x4) = 1;
                            *(char*)(*(char**)plVar8e
                                + 0x20) = 1;
                            OwnRotateL(pmap, plVar7);
                            break;
                        }
                        *(char*)(plVar8e + 0x4) = 0;
                    }
                }
                plVar8x = (char**)plVar7[1];
                plVar9 = plVar7;
            } while (plVar7 != (char**)root);
        }
        *(char*)(plVar9 + 0x4) = 1;   // black
    }
    g_fnMeritOpDelete((void*)plVar2);
    if (*(uint64_t*)(pmap + 0x38) != 0) {
        *(uint64_t*)(pmap + 0x38) =
            *(uint64_t*)(pmap + 0x38) - 1;
    }
    int64_t lVar5 = (int64_t)(char*)param_3[1];
    *(char**)param_2 = *(char**)pmap;
    param_2[1] = (char*)lVar5;
    return param_2;
}

// ================= FUN_14173cb90 =================
// the 0x28 erase-range
void* OwnEraseRange(void* pMap, void* pOutIter,
                    void* pIterFirst,
                    void* pIterLast) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIterFirst;
    char** param_4 = (char**)pIterLast;
    char* lVar2 = *(char**)(param_1 + 6);  // head
    if ((*param_3 == nullptr)
        || (*param_3 != *(char**)param_1)) {
        g_fnMeritInvalid();   // the proxy gate (VERBATIM:
    }                        //  *param_3 != *param_1)
    if (param_3[1] == (char*)lVar2) {
        // the first is the end iter
        lVar2 = (char*)param_1[6];
        if ((*param_4 == nullptr)
            || (*param_4 != *(char**)param_1)) {
            g_fnMeritInvalid();
        }
        if (param_4[1] == lVar2) {
            // both end → the full clear
            OwnClear((void*)param_1);
            param_2[1] = *(char**)(param_1 + 6);
            *param_2 = *param_1;
            return param_2;
        }
    }
    while (true) {
        if ((*param_3 == nullptr)
            || (*param_3 != (char*)param_4)) {
            g_fnMeritInvalid();
        }
        lVar2 = *param_3;
        if (param_3[1] == param_4[1]) break;
        int64_t lVar3 = (int64_t)(char*)param_3[1];
        if (*param_3 == nullptr) {
            g_fnMeritInvalid();
        }
        int64_t lVar4 = (int64_t)(char*)param_3[1];
        if (*(char*)(lVar4 + 0x21) == '\0') {
            // the inline iterator++
            char* plVar6 = *(char**)(lVar4 + 0x10);
            if (*(char*)(plVar6 + 0x21) == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar6 + 0x21);
                char* plVar5 = *(char**)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5
                            + 0x21);
                    plVar6 = plVar5;
                    plVar5 = *(char**)plVar5;
                }
            } else {
                plVar6 = *(char**)(lVar4 + 8);
                char cVar1 = *(char*)(plVar6 + 0x21);
                while ((cVar1 == '\0'
                    && ((char*)param_3[1]
                        == *(char**)(plVar6 + 0x10)))) {
                    param_3[1] = (char*)plVar6;
                    plVar6 = *(char**)(plVar6 + 8);
                    cVar1 = *(char*)(plVar6 + 0x21);
                }
            }
            param_3[1] = (char*)plVar6;
        } else {
            g_fnMeritInvalid();
        }
        char local_28[16];
        *(char**)local_28 = (char*)lVar2;
        *(char**)(local_28 + 8) = (char*)lVar3;
        char local_18[16];
        OwnErase((void*)param_1, local_18,
            (void*)local_28);
    }
    lVar2 = (char*)param_3[1];
    *param_2 = *param_1;
    param_2[1] = (char*)lVar2;
    return param_2;
}

// ================= FUN_14173e350 =================
// the 0x68 erase (+ the nested-tree value dtor)
void* MapErase(void* pMap, void* pOutIter,
               void* pIterState) {
    char* pmap = (char*)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIterState;
    char* pHead = *(char**)(pmap + 0x30);
    char** plVar2 = (char**)param_3[1];  // node
    if (*(char*)((char*)plVar2 + 0x61) != '\0') {
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    TreeIterNext(param_3);
    char** plVar8 = *(char***)plVar2;
    char** plVar9;
    char** plVar8b = nullptr;
    if (*(char*)((char*)plVar8 + 0x61) == '\0') {
        plVar9 = plVar8;
        if (*(char*)((char*)(plVar2[2]) + 0x61)
            == '\0') {
            char** plVar7 = (char**)param_3[1];
            plVar9 = (char**)plVar7[2];
            if (plVar7 != plVar2) {
                plVar8[1] = (char*)plVar7;
                *plVar7 = *(char**)plVar2;
                plVar8 = plVar7;
                if (plVar7
                    != (char**)(plVar2[2])) {
                    plVar8 = (char**)plVar7[1];
                    if (*(char*)((char*)plVar9
                        + 0x61) == '\0') {
                        plVar9[1] = (char*)plVar8;
                    }
                    *(char**)plVar8 = (char*)plVar9;
                    plVar7[2] = plVar2[2];
                    *(char**)(plVar2[2] + 8)
                        = (char*)plVar7;
                }
                if (*(char**)(pHead + 8)
                    == (char*)plVar2) {
                    *(char**)(pHead + 8)
                        = (char*)plVar7;
                } else {
                    char** puVar4 =
                        (char**)plVar2[1];
                    if ((char**)plVar2
                        == *(char***)puVar4) {
                        *(char**)puVar4 =
                            (char*)plVar7;
                    } else {
                        puVar4[2] = (char*)plVar7;
                    }
                }
                plVar7[1] = plVar2[1];
                char* pa = (char*)(plVar2 + 0xc);
                char* pb = (char*)(plVar7 + 0xc);
                if (pb != pa) {
                    int64_t lVar5 = *(int64_t*)pb;
                    *(char*)pb = *(char*)pa;
                    *(char*)pa = (char)lVar5;
                }
                plVar8b = plVar8;   // succ's old P
                goto rebalance;
            }
        }
        plVar9 = plVar8;
    } else {
        plVar9 = (char**)plVar2[2];
    }
    {
        plVar8b = (char**)plVar2[1];
        if (*(char*)((char*)plVar9 + 0x61) == '\0') {
            plVar9[1] = (char*)plVar8b;
        }
        if (*(char**)(pHead + 8) == (char*)plVar2) {
            *(char**)(pHead + 8) = (char*)plVar9;
        } else if ((char*)plVar2
            == *(char**)plVar8b) {   // P->left
            *(char**)plVar8b = (char*)plVar9;
        } else {
            plVar8b[2] = (char*)plVar9;
        }
        if (*(char**)pHead == (char*)plVar2) {
            char** plVar7 = plVar8b;
            if (*(char*)((char*)plVar9 + 0x61)
                == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar9 + 0x61);
                char** plVar3 = *(char***)plVar9;
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                    cVar1 == '\0')) {
                    plVar3 = *(char***)plVar6;
                    cVar1 = *(char*)((char*)plVar3
                        + 0x61);
                    plVar7 = plVar6;
                }
            }
            *(char**)pHead = (char*)plVar7;
        }
        if (*(char**)(pHead + 0x10)
            == (char*)plVar2) {
            char** plVar7 = plVar8b;
            if (*(char*)((char*)plVar9 + 0x61)
                == '\0') {
                char cVar1 = *(char*)
                    (plVar9[2] + 0x61);
                char** plVar3 = (char**)plVar9[2];
                plVar7 = plVar9;
                char** plVar6;
                while ((plVar6 = plVar3,
                    cVar1 == '\0')) {
                    plVar3 =
                        (char**)(plVar6[2]);
                    cVar1 = *(char*)((char*)plVar3
                        + 0x61);
                    plVar7 = plVar6;
                }
            }
            *(char**)(pHead + 0x10) = (char*)plVar7;
        }
    }
rebalance:
    // the remove-rebalance (the verbatim e350 loop);
    // the entry P = the parent CAPTURED by the
    // unlink/swap path (the spliced slot may be
    // the head sentinel)
    if (*(char*)(plVar2 + 0xc) == '\x01') {
        char* root = *(char**)(pHead + 8);
        if (plVar9 != (char**)root) {
            char** plVar8x = plVar8b;   // P
            char** plVar7 = nullptr;
            do {
                plVar7 = plVar8x;                // P
                if (*(char*)(plVar9 + 0xc) != '\x01') {
                    break;   // the current is RED: done
                }
                char** plVar8d = *(char***)plVar7;   // P->left
                if (plVar9 == plVar8d) {
                    // the current IS P->left: the sibling = P->right
                    char** plVar8e = (char**)plVar7[2];
                    if (*(char*)(plVar8e + 0xc) == '\0') {
                        *(char*)(plVar8e + 0xc) = 1;
                        *(char*)(plVar7 + 0xc) = 0;
                        TreeRotateR(pmap, plVar7);
                        plVar8e = (char**)plVar7[2];
                    }
                    if (*(char*)((char*)plVar8e + 0x61)
                        == '\0') {
                        if ((*(char*)(*(char**)plVar8e
                            + 0x60) != '\x01')
                            || (*(char*)
                            (plVar8e[2] + 0x60)
                             != '\x01')) {
                            if (*(char*)
                                (plVar8e[2] + 0x60)
                                == '\x01') {
                                *(char*)
                                    (*(char**)plVar8e + 0x60)
                                    = 1;
                                *(char*)(plVar8e + 0xc) = 0;
                                TreeRotateL(pmap, plVar8e);
                                plVar8e = (char**)plVar7[2];
                            }
                            *(char*)(plVar8e + 0xc) =
                                *(char*)(plVar7 + 0xc);
                            *(char*)(plVar7 + 0xc) = 1;
                            *(char*)
                                (plVar8e[2] + 0x60)
                                = 1;
                            TreeRotateR(pmap, plVar7);
                            break;
                        }
                        *(char*)(plVar8e + 0xc) = 0;
                    }
                } else {
                    // the current IS P->right: the sibling = P->left
                    char** plVar8e = plVar8d;
                    if (*(char*)(plVar8d + 0xc) == '\0') {
                        *(char*)(plVar8d + 0xc) = 1;
                        *(char*)(plVar7 + 0xc) = 0;
                        TreeRotateL(pmap, plVar7);
                        plVar8e = *(char***)plVar7;
                    }
                    if (*(char*)((char*)plVar8e + 0x61)
                        == '\0') {
                        if ((*(char*)
                            (plVar8e[2] + 0x60)
                             != '\x01')
                            || (*(char*)(*(char**)plVar8e
                            + 0x60) != '\x01')) {
                            if (*(char*)(*(char**)plVar8e
                                + 0x60) == '\x01') {
                                *(char*)
                                    (plVar8e[2] + 0x60)
                                    = 1;
                                *(char*)(plVar8e + 0xc) = 0;
                                TreeRotateR(pmap, plVar8e);
                                plVar8e = *(char***)plVar7;
                            }
                            *(char*)(plVar8e + 0xc) =
                                *(char*)(plVar7 + 0xc);
                            *(char*)(plVar7 + 0xc) = 1;
                            *(char*)(*(char**)plVar8e
                                + 0x60) = 1;
                            TreeRotateL(pmap, plVar7);
                            break;
                        }
                        *(char*)(plVar8e + 0xc) = 0;
                    }
                }
                plVar8x = (char**)plVar7[1];
                plVar9 = plVar7;
            } while (plVar7 != (char**)root);
        }
        *(char*)(plVar9 + 0xc) = 1;   // black
    }
    // the value dtor: the nested 0x28 tree clear
    // (the verbatim e350 tail: the full range
    // [begin,end) on the value's own tree)
    {
        char* plVar8v = (char*)(plVar2 + 4);   // node+0x20
        char* local_50[2];
        char* local_b8[2];
        char* local_a8[2];
        char* puStack_a0 = *(char**)(plVar2 + 10);  // the nested head
        local_b8[0] = *(char**)plVar8v;             // the anchor
        local_b8[1] = *(char**)puStack_a0;          // begin: the nested first
        local_a8[0] = *(char**)plVar8v;
        local_a8[1] = puStack_a0;                   // end: the head
        OwnEraseRange(plVar8v, local_50, local_b8, local_a8);
        g_fnMeritOpDelete(*(void**)(plVar2 + 10));  // the nested head
        plVar2[10] = nullptr;
        plVar2[0xb] = nullptr;
        g_fnMeritOpDelete((void*)*(char**)plVar8v);  // the anchor
    }
    g_fnMeritOpDelete((void*)plVar2);
    if (*(uint64_t*)(pmap + 0x38) != 0) {
        *(uint64_t*)(pmap + 0x38) =
            *(uint64_t*)(pmap + 0x38) - 1;
    }
    int64_t lVar5 = (int64_t)(char*)param_3[1];
    *(char**)param_2 = *(char**)pmap;
    param_2[1] = (char*)lVar5;
    return param_2;
}
// ================= FUN_14173eb10 =================
// the 0x68 erase-range
void* MapEraseRange(void* pMap, void* pOutIter,
                    void* pIterFirst,
                    void* pIterLast) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pIterFirst;
    char** param_4 = (char**)pIterLast;
    char* lVar2 = *(char**)(param_1 + 6);
    if ((*param_3 == nullptr)
        || (*param_3 != (char*)param_1)) {
        g_fnMeritInvalid();
    }
    if (param_3[1] == (char*)lVar2) {
        lVar2 = (char*)param_1[6];
        if ((*param_4 == nullptr)
            || (*param_4 != (char*)param_1)) {
            g_fnMeritInvalid();
        }
        if (param_4[1] == lVar2) {
            // both end → the full clear
            TreeClearNodes((void*)param_1,
                *(char**)(param_1[6] + 8));
            *(char**)(param_1[6] + 8)
                = param_1[6];
            param_1[7] = 0;
            *(char**)param_1[6] = param_1[6];
            *(char**)(param_1[6] + 0x10)
                = param_1[6];
            lVar2 = *(char**)param_1[6];
            *param_2 = *param_1;
            param_2[1] = (char*)lVar2;
            return param_2;
        }
    }
    while (true) {
        if ((*param_3 == nullptr)
            || (*param_3 != (char*)param_4)) {
            g_fnMeritInvalid();
        }
        lVar2 = *param_3;
        if (param_3[1] == param_4[1]) break;
        int64_t lVar3 = (int64_t)(char*)param_3[1];
        if (*param_3 == nullptr) {
            g_fnMeritInvalid();
        }
        int64_t lVar4 = (int64_t)(char*)param_3[1];
        if (*(char*)(lVar4 + 0x61) == '\0') {
            char* plVar6 = *(char**)(lVar4 + 0x10);
            if (*(char*)(plVar6 + 0x61) == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar6 + 0x61);
                char* plVar5 = *(char**)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5
                            + 0x61);
                    plVar6 = plVar5;
                    plVar5 = *(char**)plVar5;
                }
            } else {
                plVar6 = *(char**)(lVar4 + 8);
                char cVar1 = *(char*)(plVar6 + 0x61);
                while ((cVar1 == '\0'
                    && ((char*)param_3[1]
                        == *(char**)(plVar6 + 0x10)))) {
                    param_3[1] = (char*)plVar6;
                    plVar6 = *(char**)(plVar6 + 8);
                    cVar1 = *(char*)(plVar6 + 0x61);
                }
            }
            param_3[1] = (char*)plVar6;
        } else {
            g_fnMeritInvalid();
        }
        char local_28[16];
        *(char**)local_28 = (char*)lVar2;
        *(char**)(local_28 + 8) = (char*)lVar3;
        char local_18[16];
        MapErase((void*)param_1, local_18,
            (void*)local_28);
    }
    lVar2 = (char*)param_3[1];
    *param_2 = *param_1;
    param_2[1] = (char*)lVar2;
    return param_2;
}

// ================= FUN_14173ecf0 =================
// the 0x68 tree dtor
void MapTreeDtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char local_38[16];
    *(char**)local_38 = *(char**)param_1;
    char* puStack_30 = (char*)param_1[6];
    *(char**)(local_38 + 8) = (char*)puStack_30;   // END: {anchor, head}
    char local_28[16];
    *(char**)local_28 = *(char**)param_1;
    *(char**)(local_28 + 8) = *(char**)puStack_30; // BEGIN: {anchor, first}
    char local_18[16];
    MapEraseRange((void*)param_1, local_18,
        (void*)local_28, (void*)local_38);
    g_fnMeritOpDelete((void*)param_1[6]);
    param_1[6] = 0;
    param_1[7] = 0;
}

} // namespace syndicate

