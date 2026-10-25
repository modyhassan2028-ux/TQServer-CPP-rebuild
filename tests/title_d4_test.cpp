// ============================================================
// Title.dll — Unit D4 regression: the CTitle family
// Must print TITLE-D4-OK.
#include "../Exe/Dll/Title/Port/TitleRecord.h"
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace title;

int main() {
    std::vector<std::string> vecLogs;
    int nAtexit = 0, nIsValid = 0;
    std::vector<void*> vecFrees;
    std::vector<size_t> vecAllocs;
    g_fnTitleLogError = [&](const char* s){
        vecLogs.push_back(s); };
    g_fnTitleHeapAtexit = [&]{ ++nAtexit; };
    g_fnTitleIsValid = [&](void*){ ++nIsValid; };
    g_fnTitleAlloc = [&](size_t n){
        vecAllocs.push_back(n);
        return calloc(1, n); };
    g_fnTitleFree = [&](void* p){ vecFrees.push_back(p); };
    g_fnFree = [&](void* p){ vecFrees.push_back(p); };

    // ===== 1. Create happy ==================
    {
        STitle* p = CreateTitle(42, (void*)0x1234);
        assert(p != nullptr);
        assert(p->m_nId10 == 42);
        assert(p->m_pName08 == (void*)0x1234);
        assert(p->m_nPad14 == 0);
        assert(std::strcmp((const char*)p->m_pVftable,
               "title::CTitle::vftable") == 0);
        assert(vecAllocs.size() == 1 &&
               vecAllocs[0] == 0x18);
        assert(vecLogs.empty());
    }
    // ===== 2. id 0 -> log + null ===========
    {
        size_t nL = vecLogs.size();
        STitle* p = CreateTitle(0, (void*)0x1234);
        assert(p == nullptr);
        assert(vecLogs.size() == nL + 1);
    }
    // ===== 3. name null -> log + null ======
    {
        size_t nL = vecLogs.size();
        STitle* p = CreateTitle(5, nullptr);
        assert(p == nullptr);
        assert(vecLogs.size() == nL + 1);
    }
    // ===== 4. alloc fail -> log + null =====
    {
        g_fnTitleAlloc = [](size_t){ return nullptr; };
        size_t nL = vecLogs.size();
        STitle* p = CreateTitle(5, (void*)0x9);
        assert(p == nullptr);
        assert(vecLogs.size() == nL + 1);
        g_fnTitleAlloc = [&](size_t n){
            return calloc(1, n); };
    }
    // ===== 5. deleting dtor with the flag ==
    {
        STitle* p = CreateTitle(7, (void*)0x5);
        size_t nF = vecFrees.size();
        STitle* r = DtorTitle(p, 1);
        assert(r == p);
        assert(vecFrees.size() == nF + 1);
        // flag 0 -> no free
        DtorTitle(p, 0);
        assert(vecFrees.size() == nF + 1);
    }
    // ===== 6. the one-time heap init =======
    {
        assert(nAtexit == 1);   // only once so far
        void* p = TitleAlloc(8);
        assert(p != nullptr);
        assert(nAtexit == 1);   // still once
        TitleFree(p);
        TitleIsValid(p);
        assert(nIsValid == 1);
        assert(nAtexit == 1);
    }
    // ===== 7. the mgr atexit destroy =======
    {
        ResetTitleMgrForTest();
        g_fnAlloc = [](size_t n){ return calloc(1, n); };
        assert(GetTitleMgr() != nullptr);
        size_t nF = vecFrees.size();
        DestroyTitleMgr();
        assert(vecFrees.size() == nF + 1);
        // null instance -> no-op
        ResetTitleMgrForTest();
        nF = vecFrees.size();
        DestroyTitleMgr();
        assert(vecFrees.size() == nF);
    }
    std::printf(
        "TITLE-D4-OK: CTitle verbatim — Create 1419718f0 "
        "(the id/name gates with the DAT_141978310 "
        "literal log, the 0x18 CMyHeap alloc, vtable + "
        "+0x10 id + +0x08 name + +0x14=0, the alloc-fail "
        "log), the deleting dtor 1419719e0 (vtable write "
        "+ the flag-conditional FUN_141971830 free), the "
        "CTitle heap trio 1419717d0/830/890 (the one-time "
        "init + atexit(&LAB_141977560) + the tag literal), "
        "and the 141971ed0 mgr atexit destroy "
        "(vtable+0x20 (instance, 1))\n");
    return 0;
}
