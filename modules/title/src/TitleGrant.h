#pragma once
// ============================================================
// Title.dll — Port — Unit D5: granting titles
//  FUN_1419715a0 — the check-and-set title bit
//  FUN_141971f00 — the grant (mask gate + the msg)
//  FUN_1419750b0 — the CMsgTitle wire build
//                 (0xc size / 0x46a id / id / idx /
//                  action / 0)
//  FUN_141975080 — the CMsgTitle dtor (vtable swap)
#include <cstdint>
#include <functional>
#include "TitleModule.h"

namespace title {

// the user's title-mask record (param_1 of 1419715a0):
// +0x08 the mask holder, +0x10 the record id
struct STitleMaskRec {
    uint8_t m_abPad00[8];
    void* m_pHolder08;
    uint8_t m_abPad10[0x10 - 8];
    int32_t m_nId10;       // +0x10 the mask-holder id
    uint32_t m_nStamp14 = 0;   // +0x14 the edit stamp
};

// ---- seams ----
extern std::function<uint32_t(void*, int)>
    g_fnGetTitleMask;    // holder vtable+0 (holder, id)
extern std::function<void(void*, int, uint32_t)>
    g_fnSetTitleMask;    // holder vtable+8 (holder, id, m)
extern std::function<void*(void*, int)>
    g_fnMgrGetRecord;    // mgr vtable+0x28 (mgr, id) -> record
extern std::function<void(void*, int, CMsgBase*)>
    g_fnSendTitleMsg;    // link vt+0x28 (link, id, msg)
extern std::function<void(const char*)> g_fnGrantLogError;

// 1419715a0 — check-and-set
bool TitleMaskCheckSet(STitleMaskRec* pRec, short sIdx);
// 141971f00 — the grant
bool GrantTitle(CTitleMgr* pMgr, int nTitleId, short sIdx);
// 1419750b0 — the msg build
bool CMsgTitleBuild(CMsgBase* pMsg, char cAction,
                    int nTitleId, uint8_t uIdx);
// 141975080 — the msg dtor
void CMsgTitleDestroy(CMsgBase* pMsg);

} // namespace title
