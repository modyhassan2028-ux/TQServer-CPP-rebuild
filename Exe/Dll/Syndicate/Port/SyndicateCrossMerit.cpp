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


// ---- the D28 seams ----
static void* DefOpNew2(size_t n) {
    return operator new(n); }
static void* DefListAnchor() { return nullptr; }
static void DefStrMove(void*, void*) {}
static void DefStrDtor(void*) {}
static void* DefInsF0C0(void*, void*, void*,
                        uint32_t*) {
    return nullptr; }
static void DefOrphan(void*, void*, void*, void*) {}
static void DefSplice(void*, void*) {}
static void* DefLowerD1E0(void*, void*, uint32_t*) {
    return nullptr; }
static void* DefGetMgr() { return nullptr; }
static char DefValid(void*, uint32_t) { return 0; }
static void DefLogErr() {}

void* (*g_fnMeritOpNew2)(size_t) = DefOpNew2;
void* (*g_fnListAnchorAlloc)() = DefListAnchor;
void (*g_fnStrMoveDE50)(void*, void*) = DefStrMove;
void (*g_fnStrDtorCE30)(void*) = DefStrDtor;
void* (*g_fnTreeInsertF0C0)(void*, void*, void*,
    uint32_t*) = DefInsF0C0;
void (*g_fnOrphanCB90)(void*, void*, void*, void*) =
    DefOrphan;
void (*g_fnSpliceCD80)(void*, void*) = DefSplice;
void* (*g_fnLowerBoundD1E0)(void*, void*,
    uint32_t*) = DefLowerD1E0;
void* (*g_fnGetGameMgr)() = DefGetMgr;
char (*g_fnMeritValid)(void*, uint32_t) = DefValid;
void (*g_fnMeritLogError)() = DefLogErr;

// ---- FUN_14173f680 ----
// the keyed fetch: lower_bound descent, insert if
// missing, the end deref check, value @+0x20
void* MeritValueFetch(void* pMap, uint32_t* pKey) {
    char* pc = (char*)pMap;
    // puVar4 = head; the root at head+8
    char* puVar4 = *(char**)(pc + 0x30);
    if (*(char*)(*(char**)(puVar4 + 8) + 0x61)
        == '\0') {
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
    char* plVar3 = *(char**)pc;   // the anchor
    char* puVar1 = *(char**)(pc + 0x30);  // head
    char* plVar5;
    if (plVar3 == nullptr) {
        g_fnMeritInvalid();
    }
    if ((puVar4 == puVar1)
        || (*pKey < *(uint32_t*)(puVar4 + 0x18))) {
        // the insert-if-missing path: the owner
        // node chain + the list anchor + the
        // string move + the tree insert
        void* local_d8[1] = { nullptr };
        char* plVar4 =
            (char*)g_fnMeritOpNew2(8);
        if (plVar4 != nullptr) {
            *(void**)plVar4 = local_d8;
            local_d8[0] = plVar4;
        }
        char* local_a8 = (char*)g_fnListAnchorAlloc();
        *(char*)(local_a8 + 0x21) = 1;
        *(char**)(local_a8 + 8) = local_a8;
        *(char**)local_a8 = local_a8;
        *(char**)(local_a8 + 0x10) = local_a8;
        uint32_t local_90[2];
        local_90[0] = *pKey;
        // the pair {anchor, lower_bound node}
        void* local_108[2];
        local_108[0] = plVar3;
        local_108[1] = puVar4;
        char local_88[0x48];   // the string dst
        g_fnStrMoveDE50(local_88, local_d8);
        char* local_48[2];
        char* plVar6 = (char*)g_fnTreeInsertF0C0(
            pc, local_48, local_108, local_90);
        plVar3 = *(char**)plVar6;  // local_f8
        puVar4 = ((char**)plVar6)[1];  // the new node
        g_fnStrDtorCE30(local_88);
        g_fnMeritOpDelete(*(void**)local_88);
        // the anchor unwind
        void* local_e8[2];
        local_e8[0] = local_d8[0];
        local_e8[1] = local_a8;
        void* local_108b[2];
        local_108b[0] = local_d8[0];
        g_fnOrphanCB90((void*)local_d8, nullptr,
            local_108b, local_e8);
        g_fnMeritOpDelete(local_a8);
        local_a8 = nullptr;
        g_fnMeritOpDelete(local_d8[0]);
    }
    if (plVar3 == nullptr) {
        g_fnMeritInvalid();
    } else {
        plVar5 = *(char**)plVar3;
    }
    if (puVar4 == *(char**)(plVar5 + 0x30)) {
        g_fnMeritInvalid();
    }
    return puVar4 + 0x20;
}

// ---- FUN_14173f8e0 ----
// vft + the ctor(map@+8) + the defensive clear
void* MeritCtorVft(void* pOuter) {
    char* pc = (char*)pOuter;
    *(void**)pc = g_pCrossMeritVft;
    MeritCtor(pc + 8);
    // head = *(outer+0x38) (the map@+8's head)
    char* head = *(char**)(pc + 0x38);
    g_fnTreeClearNodes(pc + 8, *(char**)(head + 8));
    *(char**)(head + 8) = head;
    *(void**)(pc + 0x40) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
    return pOuter;
}

// ---- FUN_14173f950 ----
void* MeritDtorVftScalar(void* pOuter, uint32_t uF) {
    char* pc = (char*)pOuter;
    *(void**)pc = g_pCrossMeritVft;
    g_fnTreeDtor(pc + 8);
    g_fnMeritOpDelete(*(void**)(pc + 8));
    if ((uF & 1) != 0) {
        g_fnMeritOpDelete(pOuter);
    }
    return pOuter;
}

// ---- FUN_14173f9c0 ----
void* MeritSingleton() {
    void* puVar1;
    if (g_pMeritDatInstance == nullptr) {
        puVar1 = g_fnMeritOpNew2(0x48);
        if (puVar1 == nullptr) {
            g_pMeritDatInstance = nullptr;
        } else {
            g_pMeritDatInstance =
                MeritCtorVft(puVar1);
        }
        if (g_pMeritDatInstance == nullptr) {
            g_fnMeritLogError();
        }
    }
    return g_pMeritDatInstance;
}

// ---- FUN_14173fa40 ----
// grant a merit: the key gate + the mgr validity
// check + the lower_bound + the insert-if-missing
uint8_t MeritGrant(void* pOuter, uint32_t uKey) {
    char* pc = (char*)pOuter;
    uint32_t local_res10[2];
    local_res10[0] = uKey;
    if (uKey == 0) {
        g_fnMeritLogError();
        return 0;
    }
    char* plVar4 = (char*)g_fnGetGameMgr();
    char cVar3 = g_fnMeritValid(plVar4, uKey);
    if (cVar3 == '\0') {
        return 0;
    }
    // map = outer+8; the lower_bound
    char* map = pc + 8;
    void* out[2] = { nullptr, nullptr };
    g_fnLowerBoundD1E0(map, out, local_res10);
    char* lVar1 = *(char**)(pc + 0x38);   // head
    if ((*(char**)out == nullptr)
        || (*(char**)out != *(char**)map)) {
        g_fnMeritInvalid();
    }
    if (((char**)out)[1] == lVar1) {
        // end — insert via the keyed fetch
        void* local_48[1] = { nullptr };
        char* local_res18 =
            (char*)g_fnMeritOpNew2(8);
        if (local_res18 != nullptr) {
            *(void**)local_res18 = local_48;
            local_48[0] = local_res18;
        }
        char* local_18 =
            (char*)g_fnListAnchorAlloc();
        *(char*)(local_18 + 0x21) = 1;
        *(char**)(local_18 + 8) = local_18;
        *(char**)local_18 = local_18;
        *(char**)(local_18 + 0x10) = local_18;
        void* pplVar5[2];
        pplVar5[0] = MeritValueFetch(
            map, local_res10);
        // (the verbatim iterator-registration
        // chain: the seam calls absorb the
        // decompiler's node/owner pairing)
        if ((void*)pplVar5 != (void*)local_48) {
            // plStack_70 = pplVar5[6]; local_78 =
            // *pplVar5; puStack_60 = *plStack_70
            char* plStack_70 =
                ((char**)pplVar5)[6];
            char* local_78 = *(char**)pplVar5;
            char* puStack_60 = *(char**)plStack_70;
            g_fnOrphanCB90(pplVar5, nullptr,
                &puStack_60, &local_78);
            g_fnSpliceCD80(pplVar5, local_48);
        }
        char* plStack_70 = *(char**)local_18;
        char* local_68 = *(char**)local_48;
        g_fnOrphanCB90(local_48, nullptr,
            &local_68, &plStack_70);
        g_fnMeritOpDelete(local_18);
        local_18 = nullptr;
        g_fnMeritOpDelete(local_48[0]);
    }
    return 1;
}

// ---- FUN_14173fc80 ----
void MeritDeleteAnchor(void* pMap) {
    char* pc = (char*)pMap;
    g_fnMeritOpDelete(*(void**)pc);
}

} // namespace syndicate
