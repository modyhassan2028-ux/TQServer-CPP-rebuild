#include "TitleModule.h"
#include <cstring>

namespace title {

// ---- seams (default: no-ops) ----
std::function<void*(size_t)> g_fnAlloc = [](size_t){ return nullptr; };
std::function<void(void*)> g_fnFree   = [](void*){};
std::function<void()> g_fnCMsgInit    = []{};
std::function<void(const char*)> g_fnLogError = [](const char*){};
std::function<void()> g_fnAtexit     = []{};
std::function<bool(uint32_t, void*)> g_fnKernelRegisterMsg =
    [](uint32_t, void*){ return true; };
std::function<bool(uint32_t, void*)> g_fnKernelSet =
    [](uint32_t, void*){ return true; };

const char* k_pszCTitleMgr = "CTitleMgr";

// ============================================================
// FUN_141972cf0 — the 0x30 list-head node ctor
// (operator_new(0x30); the ORIGINAL null-checks on
//  puVar1+1/+2 are always-true artifacts — ported as
//  plain zeroing with a comment)
static SListHead* NewListHead() {
    SListHead* p = (SListHead*)g_fnAlloc(sizeof(SListHead));
    if (p) {
        p->m_pFront = nullptr;       // puVar1[0] = 0
        p->m_pBack = nullptr;        // puVar1[1] = 0
        p->m_pAnchor = nullptr;      // puVar1[2] = 0
        memset(p->m_abPad, 0, sizeof(p->m_abPad));
        p->m_bFlag28 = 1;            // *(byte*)(p+5) = 1
        p->m_bFlag29 = 0;            // +0x29 = 0
    }
    return p;
}

// ============================================================
// FUN_141974900 — the CTitleMgr core ctor
// (param_1 = mgr + 0x08)
static void CtorTitleMgrCore(uint8_t* pMgrBase) {
    STitleMgrNode** ppNode =
        (STitleMgrNode**)(pMgrBase + 0x08);
    STitleMgrNode* pNode =
        (STitleMgrNode*)g_fnAlloc(sizeof(STitleMgrNode));
    if (pNode == nullptr) pNode = nullptr;
    else pNode->m_pSelf = ppNode;    // *puVar1 = param_1
    *ppNode = pNode;                 // *param_1 = puVar1

    // param_1[6] = the list head (+0x38 from the mgr)
    SListHead** ppList = (SListHead**)(pMgrBase + 0x38);
    SListHead* pList = NewListHead();
    *ppList = pList;
    // *(byte*)(lVar2 + 0x29) = 1  (the caller's write)
    if (pList) pList->m_bFlag29 = 1;
    // the circular self-links (lVar2 + 8/+0/+0x10 = self)
    if (pList) {
        pList->m_pBack = pList;      // *(lVar2 + 8)
        pList->m_pFront = pList;     // *(lVar2 + 0)
        pList->m_pAnchor = pList;    // *(lVar2 + 0x10)
    }
    // param_1[7] = 0  (+0x40)
    *(void**)(pMgrBase + 0x40) = nullptr;
}

// ============================================================
// FUN_1419749f0 — the CTitleMgr singleton
// DAT_14197d2a0 = the instance, DAT_14197d2b0 = the flag
static CTitleMgr* s_pMgrInstance = nullptr;   // DAT_14197d2a0
static bool s_bMgrInit = false;               // DAT_14197d2b0

CTitleMgr* GetTitleMgr() {
    CTitleMgr* pMgr = s_pMgrInstance;
    if (s_pMgrInstance == nullptr) {
        if ((s_bMgrInit & 1) == 0) {
            s_bMgrInit = true;      // |= 1 (the CMyHeap ctor
            // CMyHeap::CMyHeap(&DAT_14197d2a8,"CTitleMgr")
            // — the heap object + the tag; modeled: the tag
            // literal captured by the alloc seam contract)
            g_fnAtexit();          // atexit(&LAB_141977570)
        }
        // CMyHeap::Alloc(&DAT_14197d2a8, 0x50)
        pMgr = (CTitleMgr*)g_fnAlloc(sizeof(CTitleMgr));
        if (pMgr == nullptr) {
            // stays null
        } else {
            pMgr->m_pVftable =
                (void*)k_pszCTitleMgr;  // *puVar1 = title::
                // CTitleMgr::vftable (the vtable marker;
                // the real vtable address is binary-only)
            CtorTitleMgrCore((uint8_t*)pMgr);
            pMgr->m_pPad48 = nullptr;   // puVar1[9] = 0
        }
        s_pMgrInstance = pMgr;
        if (pMgr == nullptr) {
            // log_InlineLogERROR(&DAT_141978310,"IF_NOT",
            //   "m_pInstance",
            //   "f:\\version\\cqserver-78.0.11-1204\\"
            //   "modules\\title\\src\\titlemgr.cpp", 0x16)
            g_fnLogError(
                "f:\\version\\cqserver-78.0.11-1204\\"
                "modules\\title\\src\\titlemgr.cpp:0x16");
        }
    }
    return s_pMgrInstance;
}

// ============================================================
// the three CMsg ctors (0x410 each)
// 141974b70 — title::CMsgLogin
CMsgBase* CtorMsgLogin(CMsgBase* p) {
    p->m_pVftable = (void*)"tq::CMsg::vftable";
    g_fnCMsgInit();               // tq::CMsg::Init
    p->m_pVftable = (void*)"title::CMsgLogin::vftable";
    g_fnCMsgInit();               // again after the swap
    p->m_ppTail408 = (void**)&p->m_pListHead40;  // +0x408 = this+0x40
    return p;
}
// 141975030 — title::CMsgTitle
CMsgBase* CtorMsgTitle(CMsgBase* p) {
    p->m_pVftable = (void*)"tq::CMsg::vftable";
    g_fnCMsgInit();
    p->m_pVftable = (void*)"title::CMsgTitle::vftable";
    g_fnCMsgInit();
    p->m_ppTail408 = (void**)&p->m_pListHead40;
    return p;
}
// 141974e50 — title::CMsgLogout
CMsgBase* CtorMsgLogout(CMsgBase* p) {
    p->m_pVftable = (void*)"tq::CMsg::vftable";
    g_fnCMsgInit();
    p->m_pVftable = (void*)"title::CMsgLogout::vftable";
    g_fnCMsgInit();
    p->m_ppTail408 = (void**)&p->m_pListHead40;
    return p;
}

// ============================================================
// FUN_141971330 — the CModule ctor
CModule* CtorModule(CModule* pThis, void* pKernel,
                    uint32_t uId) {
    pThis->m_pVftable = (void*)"gs::IModule::vftable";
    pThis->m_pVftable = (void*)"title::CModule::vftable";
    pThis->m_nId08 = uId;
    CtorMsgLogin(&pThis->m_msgLogin);    // +0x10
    CtorMsgTitle(&pThis->m_msgTitle);    // +0x420
    CtorMsgLogout(&pThis->m_msgLogout);  // +0x830
    pThis->m_pKernel = pKernel;          // +0xc40
    return pThis;
}

// ============================================================
// FUN_141971290 — Init
bool InitModule(CModule* pThis) {
    CTitleMgr* pMgr = GetTitleMgr();
    if (pMgr == nullptr) return false;
    // kernel vt+0x8 registrations (id, this)
    g_fnKernelRegisterMsg(0x46a, pThis);
    g_fnKernelRegisterMsg(0x3ea, pThis);
    g_fnKernelRegisterMsg(0x3eb, pThis);
    // kernel vt+0x18 (0xe, mgr) -> bool
    return g_fnKernelSet(0xe, pMgr);
}

// ============================================================
// FUN_1419714b0 — ModuleCreate
void* ModuleCreate(void* pKernel, uint32_t uId) {
    CModule* p = (CModule*)g_fnAlloc(sizeof(CModule));
    if (p == nullptr) {
        p = nullptr;               // plVar3 = 0
    } else {
        p = CtorModule(p, pKernel, uId);
    }
    if (p == nullptr) {
        g_fnLogError("DAT_141978310");  // the literal log
        p = nullptr;
    } else {
        if (!InitModule(p)) {
            // (**(code **)(*plVar3 + 8))(plVar3)
            // — the vtable+8 destroying dtor
            g_fnFree(p);
            p = nullptr;
        }
    }
    return p;
}

// TEST-ONLY reset of the singleton globals
void ResetTitleMgrForTest() {
    s_pMgrInstance = nullptr;
    s_bMgrInit = false;
}

} // namespace title
