#pragma once
// ============================================================
// Title.dll — Port — Unit D6: removing titles
//  FUN_141971620 — the clear-bit twin (check-and-CLEAR)
//  FUN_141971fe0 — the remove chain (the +0x48 link,
//    the bit clear, the action-2 remove msg, the
//    cur-idx follow-up with the action-3 broadcast,
//    and the vt+0x20/vt+0x30 post-remove)
// ============================================================
#include <cstdint>
#include <functional>

namespace title {

struct STitleMaskRec;   // from TitleGrant.h
struct CMsgBase;        // from TitleModule.h

// ---- link (the mgr +0x48 user-link) seams ----
// vt+0x28: send the title msg to the user
extern std::function<uint32_t(void*, int, CMsgBase*)> g_fnLinkSendTitle;
// vt+0x10: get the current title index
extern std::function<uint32_t(void*, int)> g_fnLinkGetCurIdx;
// vt+0x18: set the current title index
extern std::function<void(void*, int, int)> g_fnLinkSetCurIdx;
// vt+0x20: has-title gate
extern std::function<char(void*, int)> g_fnLinkHasTitle;
// vt+0x38: broadcast the title msg
extern std::function<uint32_t(void*, int, CMsgBase*)> g_fnLinkBroadcast;
// the mgr post-remove (mgr vt+0x30)
extern std::function<void(void*, int)> g_fnMgrPostRemove;

// ORIGINAL FUN_141971620 (record, idx 1..0x20)
bool TitleMaskClearBit(STitleMaskRec* pRec, short sIdx);

// ORIGINAL FUN_141971fe0 (mgr, title id, idx)
bool RemoveTitle(void* pMgr, int nTitleId, short sIdx);

} // namespace
