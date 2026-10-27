#include "TitleRecord.h"
#include "TitleModule.h"
#include <cstring>

namespace title {

std::function<void*(size_t)> g_fnTitleAlloc =
    [](size_t){ return nullptr; };
std::function<void(void*)> g_fnTitleFree = [](void*){};
std::function<void(void*)> g_fnTitleIsValid = [](void*){};
std::function<void()> g_fnTitleHeapAtexit = []{};
std::function<void(const char*)> g_fnTitleLogError =
    [](const char*){};

const char* k_pszCTitle = "CTitle";

// DAT_14197d298 — the heap init flag
static bool s_bTitleHeapInit = false;

// 1419717d0
void* TitleAlloc(size_t n) {
    if ((s_bTitleHeapInit & 1) == 0) {
        s_bTitleHeapInit = true;
        // CMyHeap::CMyHeap(&DAT_14197d290,"CTitle")
        // + atexit(&LAB_141977560)
        g_fnTitleHeapAtexit();
    }
    // CMyHeap::Alloc(&DAT_14197d290, n)
    return g_fnTitleAlloc(n);
}

// 141971830
void TitleFree(void* p) {
    if ((s_bTitleHeapInit & 1) == 0) {
        s_bTitleHeapInit = true;
        g_fnTitleHeapAtexit();
    }
    g_fnTitleFree(p);
}

// 141971890
void TitleIsValid(void* p) {
    if ((s_bTitleHeapInit & 1) == 0) {
        s_bTitleHeapInit = true;
        g_fnTitleHeapAtexit();
    }
    g_fnTitleIsValid(p);
}

// 1419718f0 — Create
STitle* CreateTitle(int nId, void* pName) {
    STitle* p = nullptr;
    if (nId == 0) {
        // log_InlineLogERROR(&DAT_141978310)
        g_fnTitleLogError("DAT_141978310");
        p = nullptr;
    } else if (pName == nullptr) {
        g_fnTitleLogError("DAT_141978310");
        p = nullptr;
    } else {
        // FUN_1419717d0(0x18)
        p = (STitle*)TitleAlloc(sizeof(STitle));
        if (p == nullptr) {
            p = nullptr;
        } else {
            p->m_pVftable = (void*)"title::CTitle::vftable";
            p->m_nId10 = nId;          // *(int*)(p+2 qwords)
            p->m_pName08 = pName;      // p[1]
            p->m_nPad14 = 0;           // +0x14 = 0
        }
        if (p == nullptr) {
            g_fnTitleLogError("DAT_141978310");
            p = nullptr;
        }
    }
    return p;
}

// 1419719e0 — the deleting dtor
STitle* DtorTitle(STitle* p, uint32_t uFlags) {
    p->m_pVftable = (void*)"title::CTitle::vftable";
    if ((uFlags & 1) != 0) {
        TitleFree(p);       // FUN_141971830
    }
    return p;
}

// 141971ed0 — the atexit mgr destroy:
// if (DAT_14197d2a0) vtable+0x20(instance, 1)
void DestroyTitleMgr() {
    // NOTE: reaches into TitleModule.cpp's singleton
    // via its accessor; the vtable+0x20 destroying dtor
    // is modeled by the free seam
    extern CTitleMgr* GetTitleMgrRefForDestroy();
    extern std::function<void(void*)> g_fnFree;
    CTitleMgr* pMgr = GetTitleMgrRefForDestroy();
    if (pMgr != nullptr) {
        g_fnFree(pMgr);   // vtable+0x20 (instance, 1)
    }
}

} // namespace title
