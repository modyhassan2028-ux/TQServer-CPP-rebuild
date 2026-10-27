// ============================================================
// Training.dll port — the map kernel + the CTrainingMgr
// singleton core. Addresses verbatim.
// ============================================================
#include "TrainingMgr.h"
#include <cstdlib>

namespace training {

// the seams (defaults; the tests override)
std::function<void*(size_t)> g_fnAlloc =
    [](size_t n){ return calloc(1, n); };
std::function<void(void*)> g_fnFree =
    [](void* p){ free(p); };
std::function<void()> g_fnAtexit = []{};
std::function<void(const char*)> g_fnLogError =
    [](const char*){};

const char* k_pszCTrainingMgr = "CTrainingMgr";

// ---- FUN_1419e2a60 ----
STreeNode* NewHeadNode() {
    STreeNode* pNode =
        (STreeNode*)g_fnAlloc(sizeof(STreeNode));
    if (pNode == nullptr) {
        // the ORIGINAL's null-path: puVar1 stays null and
        // the flag writes below are guarded by the checks
        return nullptr;
    }
    pNode->m_pLeft00 = nullptr;      // *puVar1 = 0
    pNode->m_pParent08 = nullptr;    // puVar1[1] = 0
    pNode->m_pRight10 = nullptr;     // puVar1[2] = 0
    pNode->m_bColor30 = 1;           // *(byte*)(puVar1+6)=1
    pNode->m_bIsnil31 = 0;           // *(byte*)(ptr+0x31)=0
    return pNode;
}

// ---- FUN_1419e2a10 ----
void EraseTreeRightThenLeft(STreeNode* pNode) {
    while (!pNode->m_bIsnil31) {
        EraseTreeRightThenLeft(pNode->m_pRight10);
        STreeNode* pLeft = pNode->m_pLeft00;
        g_fnFree(pNode);
        pNode = pLeft;
    }
}

// ---- FUN_1419e31c0 ----
void Clear(SMapKernel* pKern) {
    // plVar2 = *(head + 8) = the root
    STreeNode* pNode = pKern->m_pHead30->m_pParent08;
    while (!pNode->m_bIsnil31) {
        EraseTreeRightThenLeft(pNode->m_pRight10);
        STreeNode* pLeft = pNode->m_pLeft00;
        g_fnFree(pNode);
        pNode = pLeft;
    }
    // the head re-circularization
    pKern->m_pHead30->m_pParent08 = pKern->m_pHead30;
    pKern->m_nSize38 = 0;                  // map+0x38 = 0
    pKern->m_pHead30->m_pLeft00 = pKern->m_pHead30;
    pKern->m_pHead30->m_pRight10 = pKern->m_pHead30;
}

// ---- FUN_1419e4f60 ----
void CtorKernelCore(SMapKernel* pKern) {
    // proxy = new(8); *proxy = param_1 (the back-ptr)
    void** pProxy = (void**)g_fnAlloc(8);
    if (pProxy == nullptr) pProxy = nullptr;
    else *pProxy = (void*)pKern;
    pKern->m_pProxy00 = pProxy;
    // the head + the caller's isnil write
    STreeNode* pHead = NewHeadNode();
    pKern->m_pHead30 = pHead;
    // *(byte*)(lVar2 + 0x31) = 1
    if (pHead) pHead->m_bIsnil31 = 1;
    // the circular self-links
    if (pHead) {
        pHead->m_pParent08 = pHead;    // +8 = self
        pHead->m_pLeft00 = pHead;      // +0 = self
        pHead->m_pRight10 = pHead;     // +0x10 = self
    }
    // param_1[7] = 0
    pKern->m_nSize38 = 0;
}

// ---- FUN_1419e3a30 ----
void DtorKernelCore(SMapKernel* pKern) {
    // (1419e3860's erase(end,end) path -> the Clear;
    // the end iterator refresh is a caller-local detail)
    Clear(pKern);
    // the head freed and nulled
    g_fnFree(pKern->m_pHead30);
    pKern->m_pHead30 = nullptr;    // param_1[6] = 0
    pKern->m_nSize38 = 0;          // param_1[7] = 0
}

// ---- the singleton state (DAT_1419ec2d0/1419ec328) ----
static CTrainingMgr s_mgrStorage;
static bool s_bInit = false;       // DAT_1419ec328

CTrainingMgr* GetTrainingMgr() {
    if (!s_bInit) {
        s_bInit = true;            // |= 1 (the CMyHeap init
        // CTrainingMgr's vftable marker + the zero fields
        s_mgrStorage.m_pVftable00 =
            (void*)k_pszCTrainingMgr;
        s_mgrStorage.m_pPad08 = nullptr;
        s_mgrStorage.m_pPad10 = nullptr;
        CtorKernelCore(&s_mgrStorage.m_kern18);
        g_fnAtexit();              // atexit(FUN_1419e7620)
    }
    return &s_mgrStorage;
}

void ResetTrainingMgrForTest() {
    // TEST-ONLY (the atexit dtor is the original's only
    // reset path)
    s_bInit = false;
}

// ---- FUN_1419e7620 ----
void AtexitTeardown() {
    // _DAT_1419ec2d0 = training::CTrainingMgr::vftable
    s_mgrStorage.m_pVftable00 =
        (void*)k_pszCTrainingMgr;
    // FUN_1419e3a30(&DAT_1419ec2e8)
    DtorKernelCore(&s_mgrStorage.m_kern18);
    // operator_delete(DAT_1419ec2e8) — the PROXY free
    // (the kernel's +0x00, NOT the head)
    g_fnFree(s_mgrStorage.m_kern18.m_pProxy00);
    s_mgrStorage.m_kern18.m_pProxy00 = nullptr;
}

} // namespace training
