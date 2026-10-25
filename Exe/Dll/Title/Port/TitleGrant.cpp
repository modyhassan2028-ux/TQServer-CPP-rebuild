#include "TitleGrant.h"
#include <cstring>

namespace title {

std::function<uint32_t(void*, int)> g_fnGetTitleMask =
    [](void*, int){ return 0u; };
std::function<void(void*, int, uint32_t)> g_fnSetTitleMask =
    [](void*, int, uint32_t){};
std::function<void*(void*, int)> g_fnMgrGetRecord =
    [](void*, int){ return (void*)nullptr; };
std::function<void(void*, int, CMsgBase*)> g_fnSendTitleMsg =
    [](void*, int, CMsgBase*){};
std::function<void(const char*)> g_fnGrantLogError =
    [](const char*){};

// ============================================================
// FUN_1419715a0 — check-and-set the title bit
bool TitleMaskCheckSet(STitleMaskRec* pRec, short sIdx) {
    if (pRec->m_pHolder08 != nullptr) {
        uint32_t u = (uint32_t)sIdx - 1u;
        if ((uint16_t)u < 0x20) {   // idx in 1..0x20
            // 1 << ((char)idx - 1 & 0x1f)
            uint32_t uBit =
                1u << (((uint32_t)(uint8_t)sIdx - 1u) & 0x1f);
            uint32_t uMask =
                g_fnGetTitleMask(pRec->m_pHolder08,
                                pRec->m_nId10);
            if (uBit == (uMask & uBit)) {
                // already set: the VERBATIM masked return
                // (low byte cleared -> false)
                return false;
            }
            g_fnSetTitleMask(pRec->m_pHolder08,
                             pRec->m_nId10,
                             uMask | uBit);
            return true;    // CONCAT71(..., 1)
        }
    }
    return false;   // in_RAX masked
}

// ============================================================
// FUN_1419750b0 — the wire build
bool CMsgTitleBuild(CMsgBase* pMsg, char cAction,
                    int nTitleId, uint8_t uIdx) {
    if (cAction == 0 || nTitleId == 0) {
        g_fnGrantLogError("DAT_141978310");
        return false;
    }
    g_fnCMsgInit();                 // tq::CMsg::Init
    // ORIGINAL: **(u16**)(msg + 0x408) — the tail field
    // at +0x408 HOLDS the data-node address (this+0x40),
    // so ONE deref of the field yields the node
    uint8_t* p = (uint8_t*)pMsg->m_ppTail408;
    *(uint16_t*)(p + 0x00) = 0xc;       // the size word
    *(uint16_t*)(p + 0x02) = 0x46a;    // the msg id
    *(int*)(p + 0x04) = nTitleId;      // the title id
    *(uint8_t*)(p + 0x08) = uIdx;     // the index
    *(char*)(p + 0x09) = cAction;     // the action
    *(uint8_t*)(p + 0x0a) = 0;        // the terminator
    return true;    // CONCAT71(..., 1)
}

// ============================================================
// FUN_141975080 — the dtor (vtable swap)
void CMsgTitleDestroy(CMsgBase* pMsg) {
    pMsg->m_pVftable = (void*)"title::CMsgTitle::vftable";
    pMsg->m_pVftable = (void*)"tq::CMsg::vftable";
}

// ============================================================
// FUN_141971f00 — the grant
bool GrantTitle(CTitleMgr* pMgr, int nTitleId, short sIdx) {
    // the mgr's +0x48 link (param_1[9])
    void** ppLink = (void**)((uint8_t*)pMgr + 0x48);
    if (*ppLink == nullptr) return false;   // masked 0
    if (nTitleId == 0) {
        g_fnGrantLogError("DAT_141978310");
        return false;
    }
    // mgr vtable+0x28 () -> the record
    void* pRec = g_fnMgrGetRecord(pMgr, nTitleId);
    if (pRec == nullptr) return false;
    if (!TitleMaskCheckSet((STitleMaskRec*)pRec, sIdx))
        return false;
    // the stack CMsgTitle (0x410)
    CMsgBase* pMsg = (CMsgBase*)calloc(1, 0x410);
    CtorMsgTitle(pMsg);
    bool bOk = CMsgTitleBuild(pMsg, 1, nTitleId,
                              (uint8_t)sIdx);
    if (bOk) {
        // link vt+0x28 (link, titleId, msg)
        g_fnSendTitleMsg(*ppLink, nTitleId, pMsg);
    }
    CMsgTitleDestroy(pMsg);
    free(pMsg);
    return true;    // CONCAT71(..., 1)
}

} // namespace title
