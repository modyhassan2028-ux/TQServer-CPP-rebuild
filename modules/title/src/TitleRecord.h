#pragma once
// ============================================================
// Title.dll — Port — Unit D4: the CTitle family
//  Create  @ 1419718f0 (id, name) -> 0x18 record
//  dtor    @ 1419719e0 (vtable + the flag-destroy)
//  heap    @ 1419717d0 / 141971830 / 141971890
//          (CMyHeap "CTitle" alloc/free/IsValidPt
//           + atexit(&LAB_141977560))
//  the mgr atexit destroy @ 141971ed0
//    (vtable+0x20 (instance, 1))
#include <cstdint>
#include <functional>

namespace title {

struct STitle {                   // 0x18 (1419718f0)
    void* m_pVftable;             // +0x00 title::CTitle::vftable
    void* m_pName08;              // +0x08 (the ctor's param_2)
    int32_t m_nId10;              // +0x10 (the ctor's param_1)
    uint32_t m_nPad14;            // +0x14 = 0
};

// the CTitle heap seams (CMyHeap @ DAT_14197d290,
// the init flag @ DAT_14197d298, tag "CTitle")
extern std::function<void*(size_t)> g_fnTitleAlloc;
extern std::function<void(void*)> g_fnTitleFree;
extern std::function<void(void*)> g_fnTitleIsValid;
extern std::function<void()> g_fnTitleHeapAtexit;
extern std::function<void(const char*)> g_fnTitleLogError;
extern const char* k_pszCTitle;   // "CTitle"

// 1419717d0 — the alloc (with the one-time heap init)
void* TitleAlloc(size_t n);
// 141971830 — the free
void TitleFree(void* p);
// 141971890 — the IsValidPt wrapper
void TitleIsValid(void* p);
// 1419718f0 — Create(id, name)
STitle* CreateTitle(int nId, void* pName);
// 1419719e0 — the deleting dtor
STitle* DtorTitle(STitle* p, uint32_t uFlags);
// 141971ed0 — the mgr atexit destroy
void DestroyTitleMgr();

} // namespace title
