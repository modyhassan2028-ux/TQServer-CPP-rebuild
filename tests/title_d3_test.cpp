// ============================================================
// Title.dll — Unit D3 regression: the module skeleton
// Must print TITLE-D3-OK.
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace title;

struct Harness {
    std::vector<size_t> m_vecAllocs;
    std::vector<void*> m_vecFrees;
    int nCMsgInit = 0, nAtexit = 0;
    std::vector<std::string> vecLogs;
    std::vector<std::pair<uint32_t, void*>> vecReg;
    std::vector<std::pair<uint32_t, void*>> vecSet;
    bool bKernelSet = true;
    bool bFailMgrAlloc = false;
    bool bFailModuleAlloc = false;

    Harness() {
        g_fnAlloc = [this](size_t n) -> void* {
            m_vecAllocs.push_back(n);
            if (n == sizeof(CModule) && bFailModuleAlloc)
                return nullptr;
            if (n == sizeof(CTitleMgr) && bFailMgrAlloc)
                return nullptr;
            return calloc(1, n);
        };
        g_fnFree = [this](void* p) {
            m_vecFrees.push_back(p);
            free(p);
        };
        g_fnCMsgInit = [this]{ ++nCMsgInit; };
        g_fnAtexit = [this]{ ++nAtexit; };
        g_fnLogError = [this](const char* s) {
            vecLogs.push_back(s);
        };
        g_fnKernelRegisterMsg =
            [this](uint32_t id, void* p) {
                vecReg.push_back({id, p});
                return true;
            };
        g_fnKernelSet =
            [this](uint32_t id, void* p) {
                vecSet.push_back({id, p});
                return bKernelSet;
            };
    }
};

int main() {
    ResetTitleMgrForTest();
    // ===== 1. the module ctor (141971330) ====
    {
        Harness h;
        CModule m;
        memset(&m, 0xAB, sizeof(m));
        CModule* r = CtorModule(&m, (void*)0x1234, 7);
        assert(r == &m);
        assert(m.m_nId08 == 7);
        assert(m.m_pKernel == (void*)0x1234);
        // literal-pointer identity across TUs is not
        // guaranteed -> compare the CONTENT
        auto isv = [](void* v, const char* t) {
            return v && std::strcmp((const char*)v, t) == 0;
        };
        assert(isv(m.m_msgLogin.m_pVftable,
                   "title::CMsgLogin::vftable"));
        assert(isv(m.m_msgTitle.m_pVftable,
                   "title::CMsgTitle::vftable"));
        assert(isv(m.m_msgLogout.m_pVftable,
                   "title::CMsgLogout::vftable"));
        assert((void*)m.m_msgLogin.m_ppTail408 ==
               (void*)&m.m_msgLogin.m_pListHead40);
        assert((void*)m.m_msgTitle.m_ppTail408 ==
               (void*)&m.m_msgTitle.m_pListHead40);
        assert((void*)m.m_msgLogout.m_ppTail408 ==
               (void*)&m.m_msgLogout.m_pListHead40);
        assert(h.nCMsgInit == 6);   // 2 per CMsg ctor
        // the layout offsets in the 0xc48
        assert((uint8_t*)&m.m_msgLogin ==
               (uint8_t*)&m + 0x10);
        assert((uint8_t*)&m.m_msgTitle ==
               (uint8_t*)&m + 0x420);
        assert((uint8_t*)&m.m_msgLogout ==
               (uint8_t*)&m + 0x830);
        assert((uint8_t*)&m.m_pKernel ==
               (uint8_t*)&m + 0xc40);
    }
    // ===== 2. the CTitleMgr singleton =========
    {
        ResetTitleMgrForTest();
        Harness h;
        CTitleMgr* p1 = GetTitleMgr();
        assert(p1 != nullptr);
        // one heap alloc only (cached afterwards)
        CTitleMgr* p2 = GetTitleMgr();
        assert(p1 == p2);
        // 141974900: the node, the list, the zero fields
        assert(p1->m_pNode08 != nullptr);
        assert(p1->m_pNode08->m_pSelf ==
               (void*)((uint8_t*)p1 + 0x08));
        assert(p1->m_pList38 != nullptr);
        assert(p1->m_pList38->m_pFront == p1->m_pList38);
        assert(p1->m_pList38->m_pBack == p1->m_pList38);
        assert(p1->m_pList38->m_pAnchor == p1->m_pList38);
        assert(p1->m_pList38->m_bFlag28 == 1);
        assert(p1->m_pList38->m_bFlag29 == 1);
        assert(p1->m_pPad40 == nullptr);
        assert(p1->m_pPad48 == nullptr);
        assert(h.nAtexit == 1);        // registered once
        assert(h.vecLogs.empty());
    }
    // ===== 3. ModuleCreate happy path =========
    {
        ResetTitleMgrForTest();
        Harness h;
        void* p = ModuleCreate((void*)0x5678, 9);
        assert(p != nullptr);
        CModule* m = (CModule*)p;
        assert(m->m_nId08 == 9);
        assert(m->m_pKernel == (void*)0x5678);
        // alloc order: module(0xc48), mgr(0x50),
        // node(8), list(0x30) — the CMyHeap::Alloc
        // runs FIRST in 1419749f0
        assert(h.m_vecAllocs.size() == 4);
        assert(h.m_vecAllocs[0] == sizeof(CModule));
        assert(h.m_vecAllocs[1] == sizeof(CTitleMgr));
        assert(h.m_vecAllocs[2] == 8);
        assert(h.m_vecAllocs[3] == 0x30);
        // the registrations (0x46a, 0x3ea, 0x3eb, this)
        assert(h.vecReg.size() == 3);
        assert(h.vecReg[0].first == 0x46a);
        assert(h.vecReg[1].first == 0x3ea);
        assert(h.vecReg[2].first == 0x3eb);
        assert(h.vecReg[0].second == p);
        assert(h.vecReg[1].second == p);
        assert(h.vecReg[2].second == p);
        // vt+0x18 (0xe, mgr)
        assert(h.vecSet.size() == 1);
        assert(h.vecSet[0].first == 0xe);
        assert(h.vecSet[0].second != nullptr);
        assert(h.vecLogs.empty());
        assert(h.m_vecFrees.empty());
        free(p);
    }
    // ===== 4. ctor alloc fail -> log + null ====
    {
        ResetTitleMgrForTest();
        Harness h;
        h.bFailModuleAlloc = true;
        void* p = ModuleCreate((void*)1, 2);
        assert(p == nullptr);
        assert(h.vecLogs.size() == 1);  // DAT_141978310
        assert(h.vecReg.empty());
    }
    // ===== 5. mgr alloc fail -> Init false ====
    {
        ResetTitleMgrForTest();
        Harness h;
        h.bFailMgrAlloc = true;
        void* p = ModuleCreate((void*)1, 3);
        assert(p == nullptr);
        // the vtable+8 destroying dtor freed the module
        assert(h.m_vecFrees.size() == 1);
        // the titlemgr.cpp:0x16 literal log
        assert(h.vecLogs.size() == 1);
        assert(h.vecLogs[0].find("titlemgr.cpp") !=
               std::string::npos);
        assert(h.vecLogs[0].find("0x16") !=
               std::string::npos ||
               h.vecLogs[0].find(":16") !=
               std::string::npos);
    }
    // ===== 6. kernel vt+0x18 false -> destroy ===
    {
        ResetTitleMgrForTest();
        Harness h;
        h.bKernelSet = false;
        void* p = ModuleCreate((void*)1, 4);
        assert(p == nullptr);
        assert(h.m_vecFrees.size() == 1);
        assert(h.vecSet.size() == 1);
    }
    std::printf(
        "TITLE-D3-OK: ModuleCreate 1419714b0 (the 0xc48 "
        "alloc, the ctor chain, the DAT_141978310 literal "
        "log, the vtable+8 destroy on Init fail) + CModule "
        "ctor 141971330 (CMsgLogin/Title/Logout at "
        "+0x10/+0x420/+0x830, +0xc40 kernel, the 6 "
        "CMsg::Init calls) + Init 141971290 (the singleton "
        "gate, the 0x46a/0x3ea/0x3eb registrations, the "
        "0xe kernel set) + the CTitleMgr singleton 1419749f0 "
        "(the CMyHeap alloc + atexit, the 141974900 core "
        "ctor: the 8-byte self node, the 0x30 circular "
        "list-head with the 0x28/0x29 flags, the +0x40/+0x48 "
        "zeroes, the titlemgr.cpp:0x16 literal log)\n");
    return 0;
}
