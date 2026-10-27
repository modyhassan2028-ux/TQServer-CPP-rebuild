// ============================================================
// Training.dll port — the map kernel + the CTrainingMgr
// singleton core (Wave 1, unit T1/D13).
// ALL addresses/offsets verbatim from the Ghidra listing of
// Training.dll (1419e1000 base).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace training {

// ---- the allocation/log seams (test-injectable) ----
extern std::function<void*(size_t)> g_fnAlloc;   // operator new
extern std::function<void(void*)> g_fnFree;     // operator delete
extern std::function<void()> g_fnAtexit;         // atexit()
extern std::function<void(const char*)> g_fnLogError;

// ---- the RB node (0x38) — FUN_1419e2a60 family ----
struct STreeNode {
    STreeNode* m_pLeft00;       // +0x00
    STreeNode* m_pParent08;     // +0x08
    STreeNode* m_pRight10;      // +0x10
    uint64_t m_nKey18;          // +0x18 (key: LOW uint,
                                //  the compare in 1419e3240)
    void* m_pValue20;           // +0x20
    uint64_t m_nVal28;          // +0x28 (the THIRD qword
                                //  copied by 1419e2ac0)
    uint8_t m_bColor30;         // +0x30 (1 = black)
    uint8_t m_bIsnil31;         // +0x31 (1 = sentinel)
};

// ---- the map kernel — the ctor base is mgr + 0x18 ----
// FUN_1419e4f60: proxy @+0x00 (new(8), stores the base),
// head @+0x30, size @+0x38
struct SMapKernel {
    void* m_pProxy00;          // +0x00
    uint8_t m_abPad08[0x28];
    STreeNode* m_pHead30;      // +0x30 (the sentinel head)
    uint64_t m_nSize38;        // +0x38
};

// ---- the static manager singleton — DAT_1419ec2d0 ----
// vftable @+0x00, +0x08/+0x10 zeroed by 1419e5020,
// the map kernel base = mgr + 0x18
struct CTrainingMgr {
    void* m_pVftable00;        // +0x00
    void* m_pPad08;            // +0x08
    void* m_pPad10;            // +0x10
    SMapKernel m_kern18;       // +0x18 (the kernel)
};

// vtable markers (binary-only addresses; the literal tags)
extern const char* k_pszCTrainingMgr;   // "CTrainingMgr"

// ---- FUN_1419e2a60: the head node maker ----
// new(0x38); +0x00/+0x08/+0x10 zeroed; +0x30 = 1 (black);
// +0x31 = 0 (the caller sets 1). NOTE the ORIGINAL's
// impossible null-checks on (new-ptr)+1/+2 are compiler
// noise on the inlined checks.
STreeNode* NewHeadNode();

// ---- FUN_1419e4f60: the kernel core ctor ----
// proxy = new(8) storing the back-pointer to the base;
// head = NewHeadNode(); head+0x31 = 1 (isnil); the
// circular self-links +0x08/+0x00/+0x10; size = 0
void CtorKernelCore(SMapKernel* pKern);

// ---- FUN_1419e2a10: the erase-tree helper ----
// (iterative, tail-call-optimized): destroy the node's
// RIGHT subtree, free it, move LEFT, until isnil
void EraseTreeRightThenLeft(STreeNode* pNode);

// ---- FUN_1419e31c0: Clear ----
// walk from the root (head+0x08): EraseTree on the right,
// free, move left; then the head re-circularization and
// size = 0
void Clear(SMapKernel* pKern);

// ---- FUN_1419e3a30: the kernel core dtor ----
// (1419e3860 erase(end,end) -> the Clear path) + the head
// freed and nulled (+0x30/+0x38)
void DtorKernelCore(SMapKernel* pKern);

// ---- FUN_1419e5020: the singleton ----
// STATIC storage (DAT_1419ec2d0, unlike Title's heap mgr):
// first call: vftable, +0x08 = 0, +0x10 = 0,
// CtorKernelCore(mgr+0x18), atexit(FUN_1419e7620)
CTrainingMgr* GetTrainingMgr();
// TEST-ONLY: clears the singleton globals
void ResetTrainingMgrForTest();

// ---- FUN_1419e7620: the atexit teardown ----
// vftable write + DtorKernelCore + free the proxy
void AtexitTeardown();

} // namespace training
