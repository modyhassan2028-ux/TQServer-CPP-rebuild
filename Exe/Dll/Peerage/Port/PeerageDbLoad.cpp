// ============================================================
// Peerage.dll port — unit T5/D21: FUN_1415569f0
// verbatim (the decompile at Peerage.dll.decompiled.c
// line 4635).
// The DB objects (the instance, the recordsets, the
// rows, the fields, the dbobj at mgr+0x40) are opaque:
// every call below is the ORIGINAL vtable-offset call
// `(**(code**)(*obj + off))(obj, ...)` expressed with
// an explicit slot cast.
// ============================================================
#include "PeerageDbLoad.h"
#include "PeerageSortMgr.h"
#include "PeeragePromote.h"

namespace peerage {

// ---- the seams ----
void* (*g_fnDbInstanceGet)() = []() -> void* {
    return nullptr; };
const char* g_szDbQueryRankNum = nullptr;
const char* g_szDbQueryDynaRec = nullptr;

// ---- the raw vtable dispatch (the decompile's
// `(**(code **)(*p + off))(p, ...)`) ----
namespace {

inline void* VtSlot(void* pObj, size_t uOff) {
    // *pObj = the vftable; vft + off = the slot
    void* pVt = *(void**)pObj;
    return *(void**)((char*)pVt + uOff);
}

// the release: `(**(code **)*p)(p, ...)` — vt+0x00
inline uint64_t VtRelease1(void* pObj) {
    auto fn = (uint64_t (*)(void*))VtSlot(pObj, 0x00);
    return fn(pObj);
}
inline uint64_t VtRelease2(void* pObj, uint64_t uA) {
    auto fn = (uint64_t (*)(void*, uint64_t))
        VtSlot(pObj, 0x00);
    return fn(pObj, uA);
}

} // namespace

// ---- FUN_1415569f0 ----
uint64_t PeerageDbLoad(CPeerageSortMgr* param_1,
                       void* param_2) {
    if (param_2 == (void*)0) {
        // log_InlineLogERROR(&DAT_14155a358);
        g_fnSortLogError();
        return (uint64_t)0;   // RAX & ~0xff
    }
    *(void**)((char*)param_1 + 0x40) = param_2;
    void* plVar2 = g_fnDbInstanceGet();
    // (**(code **)(*plVar2 + 0x10))(plVar2, sql, 1)
    void* plVar3 = nullptr;
    {
        auto fn = (void* (*)(void*, const char*, int64_t))
            VtSlot(plVar2, 0x10);
        plVar3 = fn(plVar2, g_szDbQueryRankNum,
                    (int64_t)1);
    }
    if (plVar3 == (void*)0) {
        g_fnSortLogError();
        return (uint64_t)0;
    }
    // lVar4 = (**(code **)(*plVar3 + 0x40))(plVar3)
    int64_t lVar4;
    {
        auto fn = (int64_t (*)(void*))VtSlot(plVar3, 0x40);
        lVar4 = fn(plVar3);
    }
    if (lVar4 == 0) {
        // uVar5 = (**(code **)*plVar3)(plVar3);
        // uVar5 &= ~0xff
        uint64_t uVar5 = VtRelease1(plVar3);
        return uVar5 & 0xffffffffffffff00ULL;
    }
    // (**(code **)(*plVar3 + 0x30))(plVar3, 0)
    {
        auto fn = (void (*)(void*, uint64_t))
            VtSlot(plVar3, 0x30);
        fn(plVar3, (uint64_t)0);
    }
    // plVar6 = (**(code **)(*plVar3 + 0x38))(plVar3)
    void* plVar6;
    {
        auto fn = (void* (*)(void*))VtSlot(plVar3, 0x38);
        plVar6 = fn(plVar3);
    }
    if (plVar6 == (void*)0) {
        g_fnSortLogError();
        uint64_t uVar5 = VtRelease1(plVar3);
        return uVar5 & 0xffffffffffffff00ULL;
    }
    // plVar7 = vt+0x10(plVar6, 0); uVar1 = vt+0x40
    void* plVar7;
    {
        auto fn = (void* (*)(void*, int64_t))
            VtSlot(plVar6, 0x10);
        plVar7 = fn(plVar6, (int64_t)0);
    }
    uint32_t uVar1;
    {
        auto fn = (uint32_t (*)(void*))VtSlot(plVar7, 0x40);
        uVar1 = fn(plVar7);
    }
    *(uint32_t*)((char*)param_1 + 0x48) = uVar1;
    // (**(code **)*plVar3)(plVar3);
    VtRelease1(plVar3);
    // (**(code **)*plVar6)(plVar6, 1);
    VtRelease2(plVar6, (uint64_t)1);
    // plVar2 = (**(code **)(*plVar2 + 0x10))(plVar2,
    //   sql2)   [the decompile shows only 2 args]
    void* plVar5;
    {
        auto fn = (void* (*)(void*, const char*))
            VtSlot(plVar2, 0x10);
        plVar5 = fn(plVar2, g_szDbQueryDynaRec);
    }
    if (plVar5 == (void*)0) {
        g_fnSortLogError();
        return (uint64_t)0;
    }
    plVar2 = plVar5;
    uint32_t uVar12 = 0;
    while (true) {
        // uVar5 = vt+0x40(plVar2) — the row count
        uint64_t uVar5;
        {
            auto fn = (uint64_t (*)(void*))
                VtSlot(plVar2, 0x40);
            uVar5 = fn(plVar2);
        }
        if (uVar5 <= uVar12) break;
        // (**(code **)(*plVar2 + 0x30))(plVar2, uVar12)
        {
            auto fn = (void (*)(void*, uint64_t))
                VtSlot(plVar2, 0x30);
            fn(plVar2, (uint64_t)uVar12);
        }
        // plVar3 = (**(code **)(*plVar2 + 0x38))(plVar2)
        void* plVar3b;
        {
            auto fn = (void* (*)(void*))
                VtSlot(plVar2, 0x38);
            plVar3b = fn(plVar2);
        }
        if (plVar3b == (void*)0) {
            g_fnSortLogError();
        } else {
            // plVar6 = vt+0x10(plVar3b, 4)
            void* plVar6b;
            {
                auto fn = (void* (*)(void*, int64_t))
                    VtSlot(plVar3b, 0x10);
                plVar6b = fn(plVar3b, (int64_t)4);
            }
            // pcVar8 = vt+0x78(plVar6b)
            char* pcVar8;
            {
                auto fn = (char* (*)(void*))
                    VtSlot(plVar6b, 0x78);
                pcVar8 = fn(plVar6b);
            }
            // ---- the inline strcmp(str, "") ----
            int64_t lVar4b = 1;
            const char* pcVar11 = "";
            uint8_t uVar13 = 0;
            do {
                if (lVar4b == 0) break;
                lVar4b = lVar4b + -1;
                uVar13 = (*pcVar8 == *pcVar11);
                pcVar8 = pcVar8 + 1;
                pcVar11 = pcVar11 + 1;
            } while ((bool)uVar13);
            if ((bool)uVar13) {
                // the empty-name skip:
                // (**(code **)(*plVar3b + 0x40))(plVar3b, 0)
                {
                    auto fn = (void (*)(void*, uint64_t))
                        VtSlot(plVar3b, 0x40);
                    fn(plVar3b, (uint64_t)0);
                }
                // (**(code **)*plVar3b)(plVar3b, 1);
                VtRelease2(plVar3b, (uint64_t)1);
            } else {
                // plVar6 = vt+0x10(plVar3b, 4) — again
                void* plVar6c;
                {
                    auto fn = (void* (*)(void*, int64_t))
                        VtSlot(plVar3b, 0x10);
                    plVar6c = fn(plVar3b, (int64_t)4);
                }
                // puVar9 = vt+0x78(plVar6c)
                uint64_t* puVar9;
                {
                    auto fn = (uint64_t* (*)(void*))
                        VtSlot(plVar6c, 0x78);
                    puVar9 = fn(plVar6c);
                }
                // puVar9 = FUN_141552340(plVar3b, puVar9)
                puVar9 = (uint64_t*)CtorPeerageSort(
                    plVar3b, puVar9);
                uint64_t* local_res20 = puVar9;
                if (puVar9 == (uint64_t*)0) {
                    g_fnSortLogError();
                    // (**(code **)*plVar3b)(plVar3b, 1);
                    VtRelease2(plVar3b, (uint64_t)1);
                } else {
                    // plVar3 = vt+0x10(puVar9[1], 3)
                    //   (puVar9[1] = the obj's row at +0x08)
                    void* plVar3c;
                    {
                        auto fn =
                            (void* (*)(void*, int64_t))
                                VtSlot((void*)puVar9[1], 0x10);
                        plVar3c = fn((void*)puVar9[1],
                                     (int64_t)3);
                    }
                    // uVar1 = vt+0x40(plVar3c)
                    uint32_t uVar1b;
                    {
                        auto fn = (uint32_t (*)(void*))
                            VtSlot(plVar3c, 0x40);
                        uVar1b = fn(plVar3c);
                    }
                    // uVar1 = vt+0x80(*(param_1 + 0x40),
                    //   uVar1b)
                    void* pDb = *(void**)
                        ((char*)param_1 + 0x40);
                    uint32_t uVar1c;
                    {
                        auto fn = (uint32_t (*)(void*, uint32_t))
                            VtSlot(pDb, 0x80);
                        uVar1c = fn(pDb, uVar1b);
                    }
                    // FUN_141552170(puVar9, uVar1c)
                    SetSortField18(
                        (CPeerageSort*)puVar9, uVar1c);
                    // FUN_141555cb0(param_1 + 8, &local_res20)
                    VecPushBack(param_1, (void**)&local_res20);
                }
            }
        }
        uVar12 = uVar12 + 1;
    }
    // (**(code **)*plVar2)(plVar2);
    VtRelease1(plVar2);
    // uVar10 = FUN_141555f80(param_1, '\x01', 0)
    PeeragePromoteWalk(param_1, (char)1, 0);
    // return CONCAT71((uVar10 >> 8), 1): the walk's
    // RAX is unspecified leftover in the ORIGINAL
    // (141555f80 has no return value); the observable
    // contract is AL = 1 — the callers (1415516a0 ->
    // 141551170) consume only the low byte.
    return (uint64_t)1;
}

} // namespace peerage
