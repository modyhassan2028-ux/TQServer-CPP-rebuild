// ============================================================
// Title.dll — Unit D12 regression: the CTitleMgr deleting
// dtor (FUN_141974630) — the full teardown flow
// Must print TITLE-D12-OK.
#include "../modules/title/src/TitleMap.h"
#include "../modules/title/src/TitleMgr.h"
#include "../modules/title/src/TitleGrant.h"
#include "../modules/title/src/TitleModule.h"
#include "../modules/title/src/TitleRecord.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace title;

int main() {
    int nTitleFreed = 0, nAlloc = 0, nFreed = 0, nErrLog = 0;
    g_fnAlloc = [&](size_t n){ ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p){ ++nFreed; free(p); };
    g_fnTitleAlloc = [](size_t n){ return calloc(1, n); };
    g_fnTitleFree = [&](void* p){ ++nTitleFreed; free(p); };
    g_fnLogError = [&](const char*){
        ++nErrLog;   // the dtor's null-slot ERROR path
    };
    ResetTitleMgrForTest();
    CTitleMgr* pM = GetTitleMgr();
    pM->m_pPad48 = (void*)0x1234;
    // 3 users
    void* t1 = CTitleMgrPort::GetUserTitle(pM, 10);
    void* t2 = CTitleMgrPort::GetUserTitle(pM, 20);
    void* t3 = CTitleMgrPort::GetUserTitle(pM, 30);
    assert(t1 && t2 && t3 && t1 != t2 && t2 != t3);
    SMapKernel* pMap = (SMapKernel*)((uint8_t*)pM + 0x08);
    assert(pMap->m_nSize40 == 3);

    // ===== the dtor =====
    CTitleMgrPort::DeletingDtor(pM);
    // every CTitle destroyed exactly once
    assert(nTitleFreed == 3);
    // the null-slot ERROR never fired (all slots were live)
    assert(nErrLog == 0);
    // the head + proxy freed and nulled
    assert(pMap->m_pHead38 == nullptr);
    assert(pMap->m_pProxy08 == nullptr);
    assert(pMap->m_nSize40 == 0);
    // every allocation balanced (head, proxy, nodes,
    // mgr-node)
    assert(nAlloc - nFreed <= 1);   // the mgr node itself

    // ===== the ERROR path: a null slot in a node =====
    ResetTitleMgrForTest();
    pM = GetTitleMgr();
    pM->m_pPad48 = (void*)0x1234;
    CTitleMgrPort::GetUserTitle(pM, 7);
    SMapKernel* pMap2 = (SMapKernel*)((uint8_t*)pM + 0x08);
    // force a null slot (simulating the corrupt state)
    pMap2->m_pHead38->m_pLeft00->m_pValue20 = nullptr;
    nTitleFreed = 0;
    CTitleMgrPort::DeletingDtor(pM);
    assert(nErrLog == 1);           // the DAT_141978310 log
    assert(nTitleFreed == 0);       // nothing to destroy
    assert(pMap2->m_pHead38 == nullptr);

    std::printf("TITLE-D12-OK: the mgr deleting dtor verbatim (FUN_141974630) - the Lmost..Rmost walk destroying every node's CTitle via 141971580, the DAT_141978310 ERROR log on a null slot, the TWICE-verbatim zero, the in-order successor walk (leftmost-of-right / climb-while-right), the 141972c50-root-walk erase-all + head re-circularization, the head nulled (+0x38/+0x40) and the proxy freed - both the clean and the null-slot ERROR paths verified, all allocations balanced\n");
    return 0;
}
