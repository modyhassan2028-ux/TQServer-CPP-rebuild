// Syndicate.dll — unit T2/D27 bodies (verbatim).
#include "SyndicateCrossMerit.h"

namespace syndicate {

// ---- the seam defaults ----
static void* DefOpNew(size_t n) {
    return operator new(n); }
static void DefOpDelete(void* p) {
    operator delete(p); }
static void DefInvalid() {}
static void* DefNodeAlloc() { return nullptr; }
static void DefTreeDtor(void*) {}
static void DefTreeClearOuter(void*) {}
static int64_t DefTreeInsert(void*, uint32_t*) {
    return 0; }
static void DefTreeClearNodes(void*, void*) {}
static void* DefLogFactory() { return nullptr; }
static void DefLogWrite(void*, uint32_t, int) {}
static void DefMeritLogFactory() {}

void* (*g_fnMeritOpNew)(size_t) = DefOpNew;
void (*g_fnMeritOpDelete)(void*) = DefOpDelete;
void* g_pCrossMeritVft = (void*)0x77;
void* g_pMeritDatInstance = nullptr;
void (*g_fnMeritInvalid)() = DefInvalid;
void* (*g_fnNodeAlloc)() = DefNodeAlloc;
void (*g_fnTreeDtor)(void*) = DefTreeDtor;
void (*g_fnTreeClearOuter)(void*) = DefTreeClearOuter;
int64_t (*g_fnTreeInsert)(void*, uint32_t*) =
    DefTreeInsert;
void (*g_fnTreeClearNodes)(void*, void*) =
    DefTreeClearNodes;
void* (*g_fnMeritLogFactory)() = DefLogFactory;
void (*g_fnMeritLogWrite)(void*, uint32_t, int) =
    DefLogWrite;

// ---- FUN_14173f3e0 ----
// FUN_14173ecf0(param_1); operator_delete(*param_1);
void MeritDtorAnchor(void* pOuter) {
    char* pc = (char*)pOuter;
    g_fnTreeDtor(pOuter);
    g_fnMeritOpDelete(*(void**)pc);
}

// ---- FUN_14173f410 ----
void MeritDtorVft(void* pOuter) {
    char* pc = (char*)pOuter;
    *(void**)pc = g_pCrossMeritVft;
    g_fnTreeDtor(pc + 8);
    g_fnMeritOpDelete(*(void**)(pc + 8));
}

// ---- FUN_14173f450 ----
// FUN_14173ef10(param_1); if (p) vt[0](p, 1)
void MeritDeletingDtor(void* pOuter) {
    char* pc = (char*)pOuter;
    g_fnTreeClearOuter(pOuter);
    if (pOuter != nullptr) {
        void* pVt = *(void**)pc;
        auto fn = (void* (*)(void*, uint64_t))
            *(void**)pVt;
        fn(pOuter, 1);
    }
}

// ---- FUN_14173f490 ----
void MeritStaticDispatch(uint64_t uA, uint64_t uB,
                         uint64_t uC, uint64_t uD) {
    (void)uA;
    if (g_pMeritDatInstance != nullptr) {
        MeritDeletingDtor(g_pMeritDatInstance);
    }
    (void)uB; (void)uC; (void)uD;
}

// ---- FUN_14173f4b0 ----
void MeritInsert(void* pOuter, uint32_t uKey) {
    char* pc = (char*)pOuter;
    uint32_t local_res10[6];   // the verbatim local
    local_res10[0] = uKey;
    g_fnTreeInsert(pc + 8, local_res10);
}

// ---- FUN_14173f4d0 ----
// the in-order walk with the MSVC debug checks +
// the per-key log + the final clear
void MeritWalkAndClear(void* pOuter) {
    char* pc = (char*)pOuter;
    // plVar2 = *(param_1 + 8) — the anchor at map[0]
    char** plVar2 = *(char***)(pc + 8);
    // plVar3 = **(param_1 + 0x38) — head->left
    char* plVar3 =
        *(char**)*(char**)(pc + 0x38);
    // the saved ownership node (anchor[0] = the
    // owner), checked against owner+0x30 (head)
    char* plHead = *(char**)(pc + 0x38);
    char* plVar6;
    char* plVar5;
    char cVar1;
    do {
        do {
            while (true) {
                while (true) {
                    plVar6 = plVar3;
                    plVar3 = *(char**)(pc + 0x38);
                    if ((plVar2 == nullptr)
                        || (plVar2
                            != *(char***)(pc + 8))) {
                        g_fnMeritInvalid();
                    }
                    if (plVar6 == plVar3) {
                        // DONE — the final clear
                        // e240(map@+8,
                        //   *(*(param_1+0x38) + 8))
                        g_fnTreeClearNodes(
                            pc + 8,
                            *(char**)(plHead + 8));
                        *(char**)(plHead + 8) = plHead;
                        *(void**)(pc + 0x40) = 0;
                        *(char**)plHead = plHead;
                        *(char**)(plHead + 0x10) =
                            plHead;
                        return;
                    }
                    if (plVar2 == nullptr) {
                        g_fnMeritInvalid();
                    }
                    // lVar7 = *plVar2 (the owner)
                    char* plVar7 = *plVar2;
                    if (plVar6
                        == *(char**)(plVar7 + 0x30)) {
                        g_fnMeritInvalid();
                    }
                    // the per-key log
                    void* puVar4 =
                        g_fnMeritLogFactory();
                    g_fnMeritLogWrite(
                        puVar4,
                        *(uint32_t*)(plVar6 + 0x18),
                        3);
                    if (plVar2 == nullptr) {
                        g_fnMeritInvalid();
                    }
                    if (*(char*)(plVar6 + 0x61)
                        == '\0') {
                        break;
                    }
                    g_fnMeritInvalid();
                    plVar3 = plVar6;
                }
                // ++ : the right subtree descent
                plVar3 = *(char**)(plVar6 + 0x10);
                if (*(char*)(plVar3 + 0x61) != '\0') {
                    break;
                }
                // leftmost of the right child
                plVar3 = *(char**)(plVar6 + 0x10);
                char* plVar4 = *(char**)plVar3;
                cVar1 = *(char*)(plVar4 + 0x61);
                while (cVar1 == '\0') {
                    plVar3 = plVar4;
                    plVar4 = *(char**)plVar4;
                    cVar1 =
                        *(char*)(plVar4 + 0x61);
                }
            }
            // climb: parent until not-the-right-child
            plVar3 = *(char**)(plVar6 + 8);
        } while (*(char*)(plVar3 + 0x61) != '\0');
        do {
            plVar5 = plVar3;
            plVar3 = plVar5;
            if (plVar6 != *(char**)(plVar5 + 0x10)) {
                break;
            }
            plVar3 = *(char**)(plVar5 + 8);
            plVar6 = plVar5;
        } while (*(char*)(plVar3 + 0x61) == '\0');
    } while (true);
}

// ---- FUN_14173f600 ----
void* MeritCtor(void* pOuter) {
    char* pc = (char*)pOuter;
    // operator_new(8) — the anchor node
    void* puVar1 = g_fnMeritOpNew(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *(char**)puVar1 = pc;   // anchor[0] = mgr
    }
    *(char**)pc = (char*)puVar1;
    // the head node (14173bc00)
    char* lVar2 = (char*)g_fnNodeAlloc();
    *(char**)(pc + 0x30) = lVar2;
    *(char*)(lVar2 + 0x61) = 1;      // _Isnil
    *(char**)(lVar2 + 8) = lVar2;    // parent = self
    *(char**)lVar2 = lVar2;         // left = self
    *(char**)(lVar2 + 0x10) = lVar2; // right = self
    *(void**)(pc + 0x38) = 0;       // size = 0
    return pOuter;
}

} // namespace syndicate
