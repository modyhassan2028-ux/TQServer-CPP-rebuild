#pragma once
// ============================================================
// Title.dll — Port — Unit D3: the module skeleton
//  ModuleCreate @ 1419714b0 — the gs::IModule entry
//  CModule ctor @ 141971330 (the 0xc48 object)
//  Init        @ 141971290 (msg registration)
//  CTitleMgr singleton @ 1419749f0 + core ctor 141974900
//    + the 0x30 list head node ctor 141972cf0
//  The three CMsg ctors: 141974b70 (CMsgLogin),
//    141975030 (CMsgTitle), 141974e50 (CMsgLogout)
#include <cstdint>
#include <functional>

namespace title {

// ---- seams ----
extern std::function<void*(size_t)> g_fnAlloc;
    // operator_new / CMyHeap::Alloc (returns null on
    // "out of memory" to simulate the failure paths)
extern std::function<void(void*)> g_fnFree;
    // operator_delete
extern std::function<void()> g_fnCMsgInit;
    // tq::CMsg::Init — the ORIGINAL is an unrecovered
    // jumptable thunk (141975678/14197567e region)
extern std::function<void(const char*)> g_fnLogError;
    // log_InlineLogERROR(&DAT_141978310, ...)
extern std::function<void()> g_fnAtexit;
    // atexit(&LAB_141977570) — the CMyHeap dtor
extern std::function<bool(uint32_t, void*)> g_fnKernelRegisterMsg;
    // kernel vtable+0x8 (msg id, handler obj)
extern std::function<bool(uint32_t, void*)> g_fnKernelSet;
    // kernel vtable+0x18 (0xe, CTitleMgr*)

// ---- the CMyHeap tag literal (1419749f0) ----
extern const char* k_pszCTitleMgr;      // "CTitleMgr"

// ------------------------------------------------------------
// CTitleMgr — 0x50 (vtable + the 141974900 core ctor)
struct STitleMgrNode {          // the operator_new(8) node
    void* m_pSelf;              // holds the mgr back-ptr
};
struct SListHead {              // the 0x30 node (141972cf0)
    void* m_pFront;             // +0x00 (self)
    void* m_pBack;              // +0x08 (self)
    void* m_pAnchor;            // +0x10 (self)
    uint8_t m_abPad[0x14];
    uint8_t m_bFlag28;          // +0x28 = 1
    uint8_t m_bFlag29;          // +0x29 = 0 then 1
};
struct CTitleMgr {              // 0x50
    void* m_pVftable;           // +0x00 title::CTitleMgr::vftable
    STitleMgrNode* m_pNode08;   // +0x08 (operator_new(8))
    uint8_t m_abPad10[0x28];
    SListHead* m_pList38;       // +0x38 (the 141972cf0 node)
    void* m_pPad40;             // +0x40 = 0
    void* m_pPad48;             // +0x48 = 0
};

// the singleton (1419749f0). DAT_14197d2a0 = instance,
// DAT_14197d2b0 = the init flag (bit 0)
CTitleMgr* GetTitleMgr();
// TEST-ONLY: clears DAT_14197d2a0/14197d2b0 (the atexit
// dtor is the original's only reset path)
void ResetTitleMgrForTest();

// ------------------------------------------------------------
// the CMsg objects (0x410 each, three of them in the module)
struct CMsgBase {               // the tq::CMsg-derived base
    void* m_pVftable;           // +0x00
    uint8_t m_abPad08[0x38];
    void* m_pListHead40;        // +0x40 (the queue head node)
    uint8_t m_abPad48[0x3c0];
    void** m_ppTail408;         // +0x408 (points to +0x40)
};
// the three ctors (each: CMsg vftable + Init, the derived
// vftable + Init, +0x408 = this + 0x40)
CMsgBase* CtorMsgLogin(CMsgBase* p);
CMsgBase* CtorMsgTitle(CMsgBase* p);
CMsgBase* CtorMsgLogout(CMsgBase* p);

// ------------------------------------------------------------
// title::CModule — 0xc48
struct CModule {                // gs::IModule-derived
    void* m_pVftable;           // +0x00
    uint32_t m_nId08;            // +0x08 (the ctor's param_3)
    uint32_t m_nPad0c;
    CMsgBase m_msgLogin;         // +0x10  (0x410)
    CMsgBase m_msgTitle;         // +0x420 (0x410)
    CMsgBase m_msgLogout;        // +0x830 (0x410)
    void* m_pKernel;             // +0xc40 (the ctor's param_2)
};

// the ctor (141971330): (this, kernel, id)
CModule* CtorModule(CModule* pThis, void* pKernel,
                    uint32_t uId);
// Init (141971290): the singleton + the registrations
bool InitModule(CModule* pThis);
// ModuleCreate (1419714b0)
void* ModuleCreate(void* pKernel, uint32_t uId);

} // namespace title
