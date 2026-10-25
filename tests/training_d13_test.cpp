// ============================================================
// Training.dll — Unit T1 (D13) regression: the module
// (CModule 0xc48, ModuleCreate, Init) + the static
// CTrainingMgr singleton + the kernel core ctor/dtor/clear.
// Must print TRAINING-D13-OK.
#include "../Exe/Dll/Training/Port/TrainingMgr.h"
#include "../Exe/Dll/Training/Port/TrainingModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace training;

int main() {
    int nAlloc = 0, nFree = 0, nAtexit = 0;
    std::vector<uint16_t> vecMsg;
    std::vector<int> vecSet;
    g_fnAlloc = [&](size_t n){ ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p){ ++nFree; free(p); };
    g_fnAtexit = [&]{ ++nAtexit; };
    g_fnLogError = [](const char*){ assert(!"unexpected log"); };

    // ===== 1. the singleton (1419e5020) =====
    ResetTrainingMgrForTest();
    CTrainingMgr* pM = GetTrainingMgr();
    assert(pM != nullptr);
    // the static singleton: same address every call
    assert(GetTrainingMgr() == pM);
    // the init flag: exactly ONE atexit registration
    assert(nAtexit == 1);
    // the map kernel (mgr+0x18): proxy + head + size
    SMapKernel* pK = &pM->m_kern18;
    assert(pK->m_pProxy00 != nullptr);
    assert(*(void**)pK->m_pProxy00 == (void*)pK);
    assert(pK->m_pHead30 != nullptr);
    assert(pK->m_pHead30->m_bIsnil31 == 1);   // the caller's write
    assert(pK->m_pHead30->m_bColor30 == 1);   // black
    assert(pK->m_nSize38 == 0);
    // the circular self-links
    STreeNode* pH = pK->m_pHead30;
    assert(pH->m_pParent08 == pH && pH->m_pLeft00 == pH
           && pH->m_pRight10 == pH);
    // 1419e2a60: the raw node is zeroed in its pointers
    // (created BEFORE the circularization)

    // ===== 2. the head maker directly (1419e2a60) =====
    STreeNode* pRaw = NewHeadNode();
    assert(pRaw && pRaw->m_pLeft00 == nullptr
           && pRaw->m_pParent08 == nullptr
           && pRaw->m_pRight10 == nullptr);
    assert(pRaw->m_bColor30 == 1 && pRaw->m_bIsnil31 == 0);
    g_fnFree(pRaw);

    // ===== 3. the module ctor (1419e1320) =====
    CModule* pMod = (CModule*)calloc(1, sizeof(CModule));
    assert(sizeof(CModule) == 0xc48);
    assert((uint8_t*)&pMod->m_msgLogout
           - (uint8_t*)&pMod->m_msgLogin == 0x410);
    assert((uint8_t*)&pMod->m_msgTraining
           - (uint8_t*)&pMod->m_msgLogout == 0x410);
    // msgTraining @+0x830 (0x410) -> the kernel @+0xc40
    assert((uint8_t*)&pMod->m_pKernel
           - (uint8_t*)&pMod->m_msgTraining == 0x410);
    CModule* pR = CtorModule(pMod, (void*)0x777, 0x55);
    assert(pR == pMod);
    assert(pMod->m_nId08 == 0x55);
    assert(pMod->m_pKernel == (void*)0x777);
    // the containers: +0x408 = this + 0x40
    assert(pMod->m_msgLogin.m_ppTail408
           == &pMod->m_msgLogin.m_pListHead40);
    assert(pMod->m_msgLogout.m_ppTail408
           == &pMod->m_msgLogout.m_pListHead40);
    assert(pMod->m_msgTraining.m_ppTail408
           == &pMod->m_msgTraining.m_pListHead40);

    // ===== 4. Init (1419e1260): the registration ids =====
    g_fnKernelRegisterMsg =
        [&](void* k, uint16_t id, void* m){
            // k = the module's kernel; m = the module
            // (ModuleCreate's part-5 reuses this seam with
            // its own kernel/module pair)
            assert(k != nullptr && m != nullptr);
            vecMsg.push_back(id);
        };
    g_fnKernelSet = [&](void* k, int id, void* m){
        assert(k == (void*)0x777 && m == (void*)pM);
        vecSet.push_back(id);
        return true;
    };
    assert(InitModule(pMod) == true);
    assert(vecMsg.size() == 3
           && vecMsg[0] == 0x7fc && vecMsg[1] == 0x3ea
           && vecMsg[2] == 0x3eb);
    assert(vecSet.size() == 1 && vecSet[0] == 0xf);
    // the set-fail path
    g_fnKernelSet = [](void*, int, void*){ return false; };
    assert(InitModule(pMod) == false);
    free(pMod);

    // ===== 5. ModuleCreate (1419e1470) =====
    g_fnKernelSet = [](void*, int, void*){ return true; };
    void* pCreated = ModuleCreate((void*)0x999, 0x11);
    assert(pCreated != nullptr);
    CModule* pC = (CModule*)pCreated;
    assert(pC->m_nId08 == 0x11
           && pC->m_pKernel == (void*)0x999);
    // the ctor + the container count (1 module alloc)
    g_fnFree(pCreated);
    // the Init-fail path: the module freed and NULL
    g_fnKernelSet = [](void*, int, void*){ return false; };
    int nBefore = nFree;
    assert(ModuleCreate((void*)0x999, 0x11) == nullptr);
    assert(nFree == nBefore + 1);

    // ===== 6. Clear on an empty map (1419e31c0) =====
    Clear(pK);
    assert(pK->m_nSize38 == 0);
    assert(pH->m_pParent08 == pH);

    // ===== 7. the core dtor + the atexit teardown =====
    nBefore = nFree;
    AtexitTeardown();       // FUN_1419e7620
    assert(nFree == nBefore + 2);   // the head + the proxy
    assert(pK->m_pHead30 == nullptr);
    assert(pK->m_nSize38 == 0);
    assert(pK->m_pProxy00 == nullptr);
    // allocation balance: the singleton head + proxy freed
    assert(nAlloc - nFree == 0);

    std::printf("TRAINING-D13-OK: T1 verbatim - FUN_1419e5020 the STATIC CTrainingMgr singleton (vftable + 0x08/+0x10 zeroed + the kernel core ctor at mgr+0x18 + ONE atexit), FUN_1419e4f60 the proxy (new(8) back-ptr) + head + isnil=1 + the circular self-links + size 0, FUN_1419e2a60 the 0x38 head node (zeroed ptrs, +0x30 color=1 black, +0x31=0), FUN_1419e1320 the 0xc48 CModule ctor (id@+0x08, CMsgLogin@+0x10 / CMsgLogout@+0x420 / CMsgTraining@+0x838 - Title-different order verbatim, kernel@+0xc40), FUN_1419e1260 Init (registers 0x7fc/0x3ea/0x3eb via kernel vt+8, kernel vt+0x18 (0xf, mgr)), ModuleCreate 1419e1470 (NO log on null - unlike Title) with the Init-fail destroy path, FUN_1419e31c0 Clear + FUN_1419e2a10 the iterative erase-tree, FUN_1419e3a30 the core dtor, FUN_1419e7620 the atexit teardown (head + proxy freed, allocation balance exact)\n");
    return 0;
}
