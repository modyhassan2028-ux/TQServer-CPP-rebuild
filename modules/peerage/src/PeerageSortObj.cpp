// ============================================================
// Peerage.dll port — T9/D25 (see PeerageSortObj.h for
// the address map). Every body is verbatim from
// Peerage.dll.decompiled.c.
// ============================================================
#include "PeerageSortObj.h"
#include "PeerageSortMgr.h"
#include "PeerageDonate.h"
#include "PeerageSort.h"

namespace peerage {

// ---- the seams ----
void (*g_fnRowDtorVt0)(void*, uint64_t, void*, void*,
                       int64_t) = nullptr;
void (*g_fnMyHeapCtor)(void*, const char*) = nullptr;
void (*g_fnAtexitReg)(void (*)()) = nullptr;
void (*g_fnMyHeapFree)(void*) = nullptr;
void (*g_fnMyHeapIsValidPt)(void*) = nullptr;
const void* g_pSortVftable = nullptr;

// DAT_14155f2e0 (the heap) / DAT_14155f2e8 (the init
// flag dword right after it — verbatim layout)
static uint64_t s_uHeapDat[2];
static uint64_t* s_pHeap = &s_uHeapDat[0];
static uint32_t* s_pInit =
    (uint32_t*)&s_uHeapDat[1];

// ---- FUN_141552040 ----
void DtorCPeerageSort(void* pElem, uint64_t uA,
                       uint64_t uB, uint64_t uC) {
    uint64_t* param_1 = (uint64_t*)pElem;
    uint64_t param_3 = uA;
    uint64_t param_4 = uB;
    (void)uC;   // the decompile's 4th slot (unused)
    *param_1 = (uint64_t)(uintptr_t)
        g_pSortVftable;   // peerage::CPeerageSort::vftable
    if (param_1[1] != 0) {
        // row vt[0]: (row, 1, param_3, param_4, -2)
        g_fnRowDtorVt0((void*)param_1[1], 1,
                       (void*)param_3, (void*)param_4,
                       (int64_t)0xfffffffffffffffe);
        param_1[1] = 0;
        param_1[1] = 0;
    }
}

// ---- FUN_141552180 ----
uint32_t GetSortKey18(void* pElem) {
    return *(uint32_t*)((char*)pElem + 0x18);
}

// ---- FUN_141552190 ----
void* GetHeapInstance() {
    if ((*s_pInit & 1) == 0) {
        *s_pInit = *s_pInit | 1;
        g_fnMyHeapCtor(s_pHeap, "CPeerageSort");
        // TBD-190-ATX: the original registers
        // &LAB_1415595d0 (the CMyHeap atexit thunk in
        // Common.dll) — the seam owner supplies it
        g_fnAtexitReg(nullptr);
    }
    return s_pHeap;
}

// ---- FUN_141552250 ----
void HeapFreeWrap(void* p) {
    if ((*s_pInit & 1) == 0) {
        *s_pInit = *s_pInit | 1;
        g_fnMyHeapCtor(s_pHeap, "CPeerageSort");
        // TBD-190-ATX: the original registers
        // &LAB_1415595d0 (the CMyHeap atexit thunk in
        // Common.dll) — the seam owner supplies it
        g_fnAtexitReg(nullptr);
    }
    g_fnMyHeapFree(p);
}

// ---- FUN_1415522b0 ----
void HeapIsValidPtWrap(void* p) {
    if ((*s_pInit & 1) == 0) {
        *s_pInit = *s_pInit | 1;
        g_fnMyHeapCtor(s_pHeap, "CPeerageSort");
        // TBD-190-ATX: the original registers
        // &LAB_1415595d0 (the CMyHeap atexit thunk in
        // Common.dll) — the seam owner supplies it
        g_fnAtexitReg(nullptr);
    }
    g_fnMyHeapIsValidPt(p);
}

// ---- FUN_141552310 ----
void* ScalarDeletingDtorSort(void* pElem,
                             uint64_t uFlags) {
    DtorCPeerageSort(pElem, uFlags, 0, 0);
    if ((uFlags & 1) != 0) {
        HeapFreeWrap(pElem);
    }
    return pElem;
}

// ---- FUN_141552780 ----
void ElemProbeRowId0(void* pElem) {
    long long param_1 = (long long)pElem;
    void* pRow =
        *(void**)((char*)param_1 + 8);
    void* pRec = g_fnRowQuery2(pRow, 0);
    (void)g_fnRowGetId(pRec);   // vt+0x40, discarded
}

// ---- FUN_1415527a0 ----
void ElemSetRowValue2(void* pElem, uint64_t uVal) {
    long long param_1 = (long long)pElem;
    uint64_t param_2 = uVal;
    void* pRow =
        *(void**)((char*)param_1 + 8);
    void* pRec = g_fnRowQuery2(pRow, 2);
    g_fnRecSetTotalA0(pRec, (int64_t)param_2);
    g_fnRowVt38(pRow, 0);
}

// ---- FUN_141552ed0 ----
void* ProxyAt(void** ppIter) {
    long long* param_1 = (long long*)ppIter;
    long long* plVar1 = (long long*)*param_1;
    long long lVar2;
    if (plVar1 == (long long*)0x0) {
        g_fnInvalidParameter();
        plVar1 = (long long*)*param_1;
        lVar2 = 0;
        if (plVar1 == (long long*)0x0) {
            goto LAB_CHECK;
        }
    }
    lVar2 = *plVar1;
LAB_CHECK:
    if (*(uint64_t*)(lVar2 + 0x20)
            <= (uint64_t)param_1[1]) {
        g_fnInvalidParameter();
    }
    return (void*)param_1[1];
}

// ---- FUN_141552f10 ----
void** ProxyNext(void** ppIter) {
    long long* param_1 = (long long*)ppIter;
    long long* plVar1 = (long long*)*param_1;
    long long lVar2;
    if (plVar1 == (long long*)0x0) {
        g_fnInvalidParameter();
        plVar1 = (long long*)*param_1;
        lVar2 = 0;
        if (plVar1 == (long long*)0x0) {
            goto LAB_CHECK;
        }
    }
    lVar2 = *plVar1;
LAB_CHECK:
    if (*(uint64_t*)(lVar2 + 0x20)
            <= (uint64_t)param_1[1]) {
        g_fnInvalidParameter();
    }
    param_1[1] = param_1[1] + 8;
    return (void**)param_1;
}

// ---- FUN_141552f80 ----
void** ProxyPrev(void** ppIter) {
    long long* param_1 = (long long*)ppIter;
    long long* plVar1 = (long long*)*param_1;
    long long lVar2;
    if (plVar1 == (long long*)0x0) {
        g_fnInvalidParameter();
        plVar1 = (long long*)*param_1;
        lVar2 = 0;
        if (plVar1 == (long long*)0x0) {
            goto LAB_CHECK;
        }
    }
    lVar2 = *plVar1;
LAB_CHECK:
    if ((uint64_t)param_1[1]
            <= *(uint64_t*)(lVar2 + 0x18)) {
        g_fnInvalidParameter();
    }
    param_1[1] = param_1[1] + -8;
    return (void**)param_1;
}

// ---- FUN_141552fc0 ----
bool ProxyEq(void** ppA, void** ppB) {
    long long* param_1 = (long long*)ppA;
    long long* param_2 = (long long*)ppB;
    if ((*param_1 == 0)
        || (*param_1 != *param_2)) {
        g_fnInvalidParameter();
    }
    return param_1[1] == param_2[1];
}

void ResetHeapStatic() {
    s_uHeapDat[0] = 0;
    s_uHeapDat[1] = 0;
}

} // namespace peerage
