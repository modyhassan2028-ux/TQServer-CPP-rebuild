// ============================================================
// Peerage.dll — Unit T2 (D18) regression: the
// CPeerageSort obj family + the CPeerageSortMgr +
// its MSVC-debug std::vector<void*> grow family.
// Addresses: ctor 141554ff0, builder 141555690, obj
// 141552340, setter 141552170, push 141555cb0, grow
// 141555a30, _Insert_n 1415553d0, move 141554f40 /
// 141553ef0, alloc 141553850, length_error 141553050,
// FindById 1415548b0, heap 1415521f0.
// Must print PEERAGE-D18-OK.
// ============================================================
#include "../Exe/Dll/Peerage/Port/PeerageSortMgr.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace peerage;

static int g_nLogs = 0, g_nInvalid = 0,
    g_nThrowLen = 0;
int main() {
    int nSortA = 0, nVecA = 0, nVecD = 0,
        nProxyA = 0, nProxyD = 0;
    int& nLogs = g_nLogs;
    g_fnSortAlloc = [&](size_t n) {
        ++nSortA; return calloc(1, n); };
    g_fnVecAlloc = [&](size_t n) {
        ++nVecA; return malloc(n); };
    g_fnVecDelete = [&](void* p) {
        ++nVecD; free(p); };
    g_fnProxyAlloc = [&](size_t n) {
        ++nProxyA; return calloc(1, n); };
    g_fnProxyDelete = [&](void* p) {
        ++nProxyD; free(p); };
    g_fnSortLogError = []() { ++g_nLogs; };
    g_fnInvalidParameter = []() {
        ++g_nInvalid; };

    // ---------- 1. the sizes ----------
    assert(sizeof(CPeerageSort) == 0x30);
    assert(sizeof(SPtrVec) == 0x30);
    assert(sizeof(CPeerageSortMgr) == 0x50);

    // ---------- 2. CtorPeerageSort (141552340) ------
    uint64_t pair[2] = {0x1122334455667788ull,
                        0xffeeddccbbaa9988ull};
    assert(CtorPeerageSort(nullptr, pair) == nullptr);
    assert(CtorPeerageSort((void*)7, nullptr) == nullptr);
    assert(nLogs == 0);   // (no log in this ctor)
    CPeerageSort* pS = CtorPeerageSort((void*)0x55, pair);
    assert(pS != nullptr);
    assert(pS->Vft() == (void*)1);
    assert(pS->Row() == (void*)0x55);
    assert(pS->N14() == 0 && pS->N18() == 0);
    assert(pS->Field1c() == pair[0]);
    // +0x24 = pair[1] THEN the byte 0x2b = 0 (the top
    // byte of that qword is cleared!)
    assert(pS->Field24()
        == (pair[1] & 0x00ffffffffffffffull));
    assert(pS->m_ab[0x2b] == 0);
    // SetSortField18 (141552170)
    SetSortField18(pS, 0x999);
    assert(pS->N18() == 0x999);

    // ---------- 3. the mgr ctor (141554ff0) ----------
    CPeerageSortMgr mgr;
    memset(&mgr, 0xee, sizeof(mgr));
    CtorPeerageSortMgr(&mgr);
    assert(mgr.m_pVftable == (void*)2);
    assert(mgr.m_vec.m_pProxy != nullptr);
    // *proxy = &vec (the container backref)
    assert(*(void**)mgr.m_vec.m_pProxy
        == (char*)&mgr + 8);
    assert(mgr.m_vec.m_ppBegin == nullptr);
    assert(mgr.m_vec.m_ppEnd == nullptr);
    assert(mgr.m_vec.m_ppCap == nullptr);
    assert(mgr.m_uSpare38 == 0);
    assert(mgr.m_pDb == nullptr);
    assert(mgr.m_nRankNum48 == 0);
    assert(nProxyA == 1);
    // the proxy alloc-fail: plVar2 = 0 (no crash)
    CPeerageSortMgr mgr2;
    g_fnProxyAlloc = [](size_t) { return nullptr; };
    CtorPeerageSortMgr(&mgr2);
    assert(mgr2.m_vec.m_pProxy == nullptr);
    g_fnProxyAlloc = [&](size_t n) {
        ++nProxyA; return calloc(1, n); };

    // ---------- 4. MakePeerageSortMgr (5690) -------
    CPeerageSortMgr* pM = MakePeerageSortMgr();
    assert(pM != nullptr && nLogs == 0);
    assert(nSortA == 2);   // the sort obj + this mgr
    g_fnSortAlloc = [](size_t) { return nullptr; };
    assert(MakePeerageSortMgr() == nullptr);
    assert(nLogs == 1);
    g_fnSortAlloc = [&](size_t n) {
        ++nSortA; return calloc(1, n); };

    // ---------- 5. VecPushBack (141555cb0) ---------
    // growth: cap 1 -> 2 -> 3 -> 4 -> 6 -> 9 (MSVC:
    // size + size/2), order preserved
    static CPeerageSort objs[9];
    static void* pElems[9];   // the stored value =
                              // *ppObj (the obj POINTER)
    int vals[9] = {10,20,30,40,50,60,70,80,90};
    for (int i = 0; i < 9; ++i) {
        memset(&objs[i], 0, sizeof(objs[i]));
        *(int*)(objs[i].m_ab + 8) = vals[i];
        pElems[i] = &objs[i];
        VecPushBack(pM, &pElems[i]);
    }
    size_t uCap = (size_t)((char*)pM->m_vec.m_ppCap
        - (char*)pM->m_vec.m_ppBegin) / 8;
    size_t uSize = (size_t)((char*)pM->m_vec.m_ppEnd
        - (char*)pM->m_vec.m_ppBegin) / 8;
    assert(uSize == 9);
    assert(uCap == 9);   // 1,2,3,4,6,9 (after 9)
    assert(nVecD == 5);  // the freed old bufs
    for (int i = 0; i < 9; ++i) {
        assert(*(int*)(*(char**)((char*)
            pM->m_vec.m_ppBegin + i * 8) + 8)
            == vals[i]);
    }

    // ---------- 6. FindSortById (1415548b0) ---------
    // the row seams: elem+8 -> vt+0x10(3) -> rec;
    // rec vt+0x40 -> int
    g_fnRowQuery = [](void* pRow, int n) {
        assert(n == 3); (void)pRow;
        return (void*)0x11; };
    g_fnRowGetInt = [](void*) { return 20; };
    // (any elem "queries" to 20 -> the first match)
    void* pFound = FindSortById(pM, 20);
    assert(pFound == &objs[0]);
    assert(*(int*)((char*)pFound + 8) == 10);
    // no match -> null
    assert(FindSortById(pM, 777) == nullptr);
    // a null elem -> the log branch
    *(void**)((char*)pM->m_vec.m_ppBegin) = nullptr;
    // (elem0 null -> the log; elem1 now the match)
    assert(FindSortById(pM, 20) == &objs[1]);
    nLogs = 0;
    assert(FindSortById(pM, 777) == nullptr);
    assert(nLogs >= 1);   // (the null elem logged)
    // the empty vector
    CPeerageSortMgr mEmpty; CtorPeerageSortMgr(&mEmpty);
    g_fnRowGetInt = [](void*) { return 20; };
    assert(FindSortById(&mEmpty, 20) == nullptr);

    // ---------- 7. VecInsertN direct paths ---------
    // (a) count = 0: a no-op
    CPeerageSortMgr mI; CtorPeerageSortMgr(&mI);
    void* pE0 = &objs[0]; void* pE1 = &objs[1];
    VecPushBack(&mI, &pE0);
    void* itP[2] = { mI.m_vec.m_ppBegin,
                     mI.m_vec.m_ppBegin };
    void* v = (void*)0x99;
    VecInsertN((SPtrVec*)((char*)&mI + 8),
               itP, 0, &v);
    assert(mI.m_vec.m_ppEnd
        == mI.m_vec.m_ppBegin + 1);
    // (b) the mid-insert without realloc: push room
    // first (cap 2), then insert at begin
    VecPushBack(&mI, &pE1);
    assert(mI.m_vec.m_ppCap
        == mI.m_vec.m_ppBegin + 2);
    itP[0] = mI.m_vec.m_ppBegin;
    itP[1] = mI.m_vec.m_ppBegin;
    VecInsertN((SPtrVec*)((char*)&mI + 8),
               itP, 1, &v);
    assert(mI.m_vec.m_ppEnd
        == mI.m_vec.m_ppBegin + 3);
    assert(*(void**)mI.m_vec.m_ppBegin == (void*)0x99);
    assert(*(void**)((char*)mI.m_vec.m_ppBegin
        + 8) == (void*)&objs[0]);
    assert(*(void**)((char*)mI.m_vec.m_ppBegin
        + 16) == (void*)&objs[1]);

    // ---------- 8. the throw/abort paths ----------
    g_fnThrowLengthError = []() { ++g_nThrowLen; };
    // (modeled: the original throws; the seam counts)
    // count = 1, size 0: 0x1fff... - 0 >= 1 -> no throw

    // ---------- balance ----------
    free(mI.m_vec.m_ppBegin);
    free(mEmpty.m_vec.m_ppBegin);
    free(pM->m_vec.m_ppBegin);
    free(mgr.m_vec.m_pProxy);
    free(mgr2.m_vec.m_pProxy);
    free(mEmpty.m_vec.m_pProxy);
    free(mI.m_vec.m_pProxy);
    free(pM->m_vec.m_pProxy);
    free(pS); free(pM);
    printf("PEERAGE-D18-OK\n");
    return 0;
}
