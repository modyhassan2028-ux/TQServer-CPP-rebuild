// ============================================================
// Peerage.dll port — unit T2/D18: the CPeerageSort obj
// family (0x30) + the CPeerageSortMgr (0x50) + its
// MSVC-debug std::vector<void*> (the grow family).
// Addresses verbatim: ctor 141554ff0, builder 141555690,
// obj ctor 141552340, setter 141552170, push_back
// 141555cb0, insert-at-end 141555a30, _Insert_n 1415553d0,
// move helpers 141554f40 / 141553ef0, alloc 141553850,
// length_error 141553050, FindById 1415548b0, the
// "CPeerageSort" heap 1415521f0.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace peerage {

// ---- the seams ----
// FUN_1415521f0: the static CMyHeap("CPeerageSort")
// one-time init + Alloc(n)
extern std::function<void*(size_t)> g_fnSortAlloc;
// operator_new / operator_delete for the vector buf
extern std::function<void*(size_t)> g_fnVecAlloc;
extern std::function<void(void*)> g_fnVecDelete;
// operator_new(8) for the debug proxy (141554ff0)
extern std::function<void*(size_t)> g_fnProxyAlloc;
extern std::function<void(void*)> g_fnProxyDelete;
// _invalid_parameter_noinfo (the MSVC debug checks)
extern void (*g_fnInvalidParameter)();
// the throw paths (length_error / bad_alloc) — the
// ORIGINAL throws; the port aborts by default
extern void (*g_fnThrowLengthError)();
extern void (*g_fnThrowBadAlloc)();
// the log seam (DAT_14155a358)
extern void (*g_fnSortLogError)();
// FindById's row-object calls (elem+8: vt+0x10(3) ->
// rec; rec vt+0x40 -> int)
extern std::function<void*(void*, int)>
    g_fnRowQuery;
extern std::function<int(void*)> g_fnRowGetInt;

// ---- peerage::CPeerageSort — 0x30 ----
// (raw-byte storage: the original's +0x1c/+0x24
// qwords are NOT 8-aligned relative to the struct
// start — accessors keep the layout verbatim)
struct CPeerageSort {
    uint8_t m_ab[0x30];
    // +0x00 the vftable, +0x08 the row, +0x14/0x18
    // dwords, +0x1c/+0x24 the field pair, +0x2b the
    // bool (the TOP byte of the +0x24 qword!)
    void* Vft() const {
        return *(void**)(m_ab + 0x00); }
    void SetVft(void* p) {
        *(void**)(m_ab + 0x00) = p; }
    void* Row() const {
        return *(void**)(m_ab + 0x08); }
    void SetRow(void* p) {
        *(void**)(m_ab + 0x08) = p; }
    uint32_t N14() const {
        return *(uint32_t*)(m_ab + 0x14); }
    void SetN14(uint32_t v) {
        *(uint32_t*)(m_ab + 0x14) = v; }
    uint32_t N18() const {
        return *(uint32_t*)(m_ab + 0x18); }
    void SetN18(uint32_t v) {
        *(uint32_t*)(m_ab + 0x18) = v; }
    void SetField1c(uint64_t v) {
        *(uint64_t*)(m_ab + 0x1c) = v; }
    uint64_t Field1c() const {
        return *(uint64_t*)(m_ab + 0x1c); }
    void SetField24(uint64_t v) {
        *(uint64_t*)(m_ab + 0x24) = v; }
    uint64_t Field24() const {
        return *(uint64_t*)(m_ab + 0x24); }
    void SetB2b(uint8_t v) {
        m_ab[0x2b] = v; }
};
static_assert(sizeof(CPeerageSort) == 0x30);

// FUN_141552340: (row, fieldPair) -> obj | null
CPeerageSort* CtorPeerageSort(void* pRow,
                               uint64_t* puPair);
// FUN_141552170: obj->+0x18 = value
void SetSortField18(CPeerageSort* p, uint32_t uVal);

// ---- the vector (MSVC debug std::vector<void*>) ----
struct SPtrVec {
    void* m_pProxy;            // +0x00 (the container
                               // proxy; *proxy = this)
    uint8_t m_abPad08[0x10];  // begin at +0x18
    void** m_ppBegin;          // +0x18
    void** m_ppEnd;            // +0x20
    void** m_ppCap;            // +0x28
};

// ---- peerage::CPeerageSortMgr — 0x50 ----
struct CPeerageSortMgr {
    void* m_pVftable;           // +0x00
    SPtrVec m_vec;              // +0x08 (0x28)
    uint64_t m_uSpare38;        // +0x38 (0)
    void* m_pDb;                // +0x40 (1415569f0 p2)
    uint32_t m_nRankNum48;      // +0x48 (the rank count)
    uint32_t m_nPad4c;
};
static_assert(sizeof(CPeerageSortMgr) == 0x50);

// FUN_141554ff0: the ctor (vftable + the proxy + the
// zeroed vector + the zeroed fields)
CPeerageSortMgr* CtorPeerageSortMgr(
    CPeerageSortMgr* p);
// FUN_141555690: new(0x50) + ctor; null -> log + null
CPeerageSortMgr* MakePeerageSortMgr();
// FUN_1415548b0: find by the row int (elem+8 ->
// vt+0x10(3) -> vt+0x40 == n) — logs the null elems
void* FindSortById(CPeerageSortMgr* p, int n);
// the vector ops (this = mgr, the vec at mgr+8):
// FUN_141555cb0: push_back(&obj)
void VecPushBack(CPeerageSortMgr* p, void** ppObj);
// FUN_141555a30 / 1415553d0: the grow family (used
// internally by push_back)
void VecGrowForPush(SPtrVec* pVec, void* it[2],
                    void* pProxyPair[2],
                    void* pValueQword);
void VecInsertN(SPtrVec* pVec, void* itPair[2],
               uint64_t uCount,
               void* pValueQword);

} // namespace peerage
