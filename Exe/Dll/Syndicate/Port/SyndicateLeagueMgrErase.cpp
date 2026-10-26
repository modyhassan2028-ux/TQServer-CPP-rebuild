// ============================================================
// Syndicate.dll port — T16/D41a: the mgr family
// erase-ranges, verbatim (see SyndicateLeagueMgrErase.h).
// ============================================================
#include "SyndicateLeagueMgrErase.h"
#include "SyndicateCrossMerit.h"
#include "SyndicateLeagueMgrLife.h"   // the clears 4b0/4f8
#include "SyndicateLeagueMgrErOne.h" // the D41b real
                                     //  erase-ones
#include "SyndicateLeagueMgrNested.h" // the D41c real
                                     //  nested ranges

namespace syndicate {

// the D41b erase-ones now REAL (the defaults)
FnMgrEraseOne g_fnMgrErOne38  = &MgrErOne38;
FnMgrEraseOne g_fnMgrErOne538 = &MgrErOne538;
FnMgrEraseOne g_fnMgrErOne4f8 = &MgrErOne4f8;
FnMgrEraseOne g_fnMgrErOne4b0 = &MgrErOne4b0;
FnMgrEraseOne g_fnMgrErOne470 = &MgrErOne470;
FnMgrEraseOne g_fnMgrErOne318 = &MgrErOne318;
FnMgrEraseOne g_fnMgrErOne2b0 = &MgrErOne2b0;
FnMgrEraseOne g_fnMgrErOne228 = &MgrErOne228;
FnMgrEraseOne g_fnMgrErOne108 = &MgrErOne108;
// the D41c nested ranges now REAL (the defaults)
FnNestedEr g_fnNestedErA = &NestedErRangeA;   // 14172a410
FnNestedEr g_fnNestedErB = &NestedErRangeB;   // 141762db0

// ============ the recursive subtree frees ============
// the shared shape (verbatim per family): walk while
// the node isnil == 0: free the right subtree, then
// delete the node and go left
static void SubFreeTmpl(void* pMap, void* pNode,
                        int isnilOff) {
    char** node = (char**)pNode;
    while (*(char*)((char*)node + isnilOff) == '\0') {
        SubFreeTmpl(pMap, *(char**)(node + 2), isnilOff);
        char** next = *(char***)node;   // the left
        g_fnMeritOpDelete(node);
        node = next;
    }
}
void MgrSub29A(void* m, void* n) { SubFreeTmpl(m, n, 0x29); }
void MgrSub29B(void* m, void* n) { SubFreeTmpl(m, n, 0x29); }
void MgrSub29C(void* m, void* n) { SubFreeTmpl(m, n, 0x29); }
void MgrSub29D(void* m, void* n) { SubFreeTmpl(m, n, 0x29); }
void MgrSub59A(void* m, void* n) { SubFreeTmpl(m, n, 0x59); }

// ============ the recursive nested frees ============
// 1417713d0/1417714e0: a node of the 0x68 families
// carries a NESTED map at +0x20 (proxy) with its head
// at +0x50: recurse the right, run the nested erase-
// range on the nested map (a seam until D41b), delete
// the nested head + the nested proxy + the node, then
// go left
static void NestedFreeTmpl(void* pMap, void* pNode,
                           FnNestedEr nestedEr) {
    char** node = (char**)pNode;
    while (*(char*)((char*)node + 0x61) == '\0') {
        NestedFreeTmpl(pMap, *(char**)(node + 2),
                       nestedEr);
        char** next = *(char***)node;   // the left
        char** nestedMap = node + 4;    // +0x20
        char* nhead = *(char**)(node + 0x50/8);
        int64_t local_38 = *(int64_t*)nestedMap;  // proxy
        int64_t uStack_20 = *(int64_t*)nhead;     // first
        int64_t local_28 = local_38;
        int64_t pair1[2] = { local_28, uStack_20 };
        int64_t pair2[2] = { local_38,
                             (int64_t)nhead };
        int64_t out[2];
        nestedEr(nestedMap, out, pair1, pair2);
        g_fnMeritOpDelete(*(void**)(node + 10));  // head
        node[10] = nullptr;
        node[11] = nullptr;
        g_fnMeritOpDelete(*(void**)nestedMap);    // proxy
        g_fnMeritOpDelete(node);                  // node
        node = next;
    }
}
void MgrNestedFreeA(void* m, void* n) {
    NestedFreeTmpl(m, n, g_fnNestedErA); }
void MgrNestedFreeB(void* m, void* n) {
    NestedFreeTmpl(m, n, g_fnNestedErB); }

// ============ the clears ============
typedef void (*FnSub)(void*, void*);
// the shared shape (verbatim): the root walk (subtree
// free + delete per node) + the head relinks + size 0
static void ClearTmpl(int64_t lMap, int isnilOff,
                     FnSub sub) {
    char* m = (char*)lMap;
    char* head = *(char**)(m + 0x30);
    char* node = *(char**)(head + 8);   // the root
    while (*(char*)(node + isnilOff) == '\0') {
        sub((void*)m, *(char**)(node + 0x10));  // right
        char* next = *(char**)node;             // left
        g_fnMeritOpDelete(node);
        node = next;
    }
    *(char**)(head + 8) = head;
    *(uint64_t*)(m + 0x38) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}
void MgrClear38(int64_t m)  { ClearTmpl(m, 0x29, MgrSub29A); }
void MgrClear538(int64_t m) { ClearTmpl(m, 0x29, MgrSub29B); }
void MgrClear318(int64_t m) { ClearTmpl(m, 0x29, MgrSub29C); }
void MgrClear228(int64_t m) { ClearTmpl(m, 0x29, MgrSub29D); }
void MgrClear108(int64_t m) { ClearTmpl(m, 0x59, MgrSub59A); }

// ============ the family erase-ranges ============
// the shared body (verbatim from 14175bda0): the CRT
// proxy gates, the whole-range fast path (the family
// clear — or the SPECIAL inline relinks + the recursive
// nested free for the two 0x68 families), and the
// per-node loop (the inline successor advance + the
// family erase-one seam)
static void* ErTmpl(void* pMap, void* pOut, void* pFirst,
                   void* pLast, int isnil,
                   void (*clear)(int64_t),
                   void (*freeNested)(void*, void*),
                   FnMgrEraseOne eraseOne) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOut;
    char** param_3 = (char**)pFirst;
    char** param_4 = (char**)pLast;
    char* lVar2 = *(char**)(param_1 + 6);  // head
    lVar2 = *(char**)lVar2;                // *head = first
    if ((*param_3 == nullptr)
        || (*param_3 != *(char**)param_1)) {
        g_fnMeritInvalid();
    }
    if (param_3[1] == lVar2) {
        lVar2 = *(char**)(param_1 + 6);    // the head
        if ((*param_4 == nullptr)
            || (*param_4 != *(char**)param_1)) {
            g_fnMeritInvalid();
        }
        if (param_4[1] == lVar2) {
            // the whole-range fast path
            if (freeNested != nullptr) {
                // the SPECIAL (1417742e0/141775470):
                // the recursive nested free from the
                // root, then the inline relinks
                freeNested(pMap,
                    *(char**)(*(char**)(param_1 + 6) + 8));
                char* head = *(char**)(param_1 + 6);
                *(char**)(head + 8) = head;
                *(uint64_t*)((char*)param_1 + 0x38) = 0;
                *(char**)head = head;
                *(char**)(head + 0x10) = head;
                lVar2 = *(char**)head;
            } else {
                clear((int64_t)param_1);
                lVar2 = *(char**)(*(char**)(param_1 + 6));
            }
            param_2[1] = lVar2;
            *param_2 = *param_1;
            return param_2;
        }
    }
    while (true) {
        if ((*param_3 == nullptr)
            || (*param_3 != *param_4)) {
            g_fnMeritInvalid();
        }
        lVar2 = *param_3;              // the proxy value
        if (param_3[1] == param_4[1]) break;
        char* lVar3 = param_3[1];      // the node
        if (*param_3 == nullptr) {
            g_fnMeritInvalid();
        }
        char* lVar4 = param_3[1];
        if (*(char*)(lVar4 + isnil) == '\0') {
            // the inline successor advance (verbatim)
            char** plVar6 = *(char***)((char*)lVar4 + 0x10);
            if (*(char*)((char*)plVar6 + isnil) == '\0') {
                char cVar1 =
                    *(char*)(*(char**)plVar6 + isnil);
                char** plVar5 = *(char***)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5 + isnil);
                    plVar6 = plVar5;
                    plVar5 = *(char***)plVar5;
                }
            } else {
                char** plVar6b =
                    *(char***)((char*)lVar4 + 8);  // parent
                char cVar1 =
                    *(char*)((char*)plVar6b + isnil);
                while ((cVar1 == '\0')
                       && (param_3[1]
                           == *(char**)(plVar6b + 2))) {
                    param_3[1] = (char*)plVar6b;
                    plVar6b = *(char***)((char*)plVar6b + 8);
                    cVar1 =
                        *(char*)((char*)plVar6b + isnil);
                }
                plVar6 = plVar6b;
            }
            param_3[1] = (char*)plVar6;
        } else {
            g_fnMeritInvalid();
        }
        // the family erase-one on {proxy, old node}
        int64_t pair[2] = { (int64_t)lVar2, (int64_t)lVar3 };
        int64_t out[2];
        eraseOne(pMap, out, pair);
    }
    lVar2 = param_3[1];
    *param_2 = *param_1;
    param_2[1] = lVar2;
    return param_2;
}

void* MgrEraseRange38(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x29, MgrClear38,
                  nullptr, g_fnMgrErOne38); }
void* MgrEraseRange538(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x29, MgrClear538,
                  nullptr, g_fnMgrErOne538); }
void* MgrEraseRange4f8(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x69, MgrClear4f8,
                  nullptr, g_fnMgrErOne4f8); }
void* MgrEraseRange4b0(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x29, MgrClear4b0,
                  nullptr, g_fnMgrErOne4b0); }
void* MgrEraseRange470(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x61, nullptr,
                  MgrNestedFreeA, g_fnMgrErOne470); }
void* MgrEraseRange318(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x29, MgrClear318,
                  nullptr, g_fnMgrErOne318); }
void* MgrEraseRange2b0(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x61, nullptr,
                  MgrNestedFreeB, g_fnMgrErOne2b0); }
void* MgrEraseRange228(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x29, MgrClear228,
                  nullptr, g_fnMgrErOne228); }
void* MgrEraseRange108(void* m, void* o, void* f, void* l) {
    return ErTmpl(m, o, f, l, 0x59, MgrClear108,
                  nullptr, g_fnMgrErOne108); }

}  // namespace syndicate
