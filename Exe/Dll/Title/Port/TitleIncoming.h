#pragma once
// ============================================================
// Title.dll — Port — Unit D9: the incoming title msg
//  FUN_141975170 — CMsgTitle::Create (id 0x46a @+0x50)
//  FUN_1419751a0 — the idx-byte append (size bookkeeping)
//  FUN_141975210 — the deleting dtor
//  FUN_141975260 — the process: actions 2/3/4
//  FUN_1419716f0 / 141971700 — the edit stamp get/set
// ============================================================
#include <cstdint>
#include <functional>

namespace title {

struct CMsgBase;        // TitleModule.h
struct STitleMaskRec;   // TitleGrant.h

// ---- new seams ----
extern std::function<uint32_t()> g_fnTimeGet;       // tq::TimeGet(0)
// the string-manager lookup (theInstance()->Get("STR_..."))
extern std::function<const char*(const char*)> g_fnGetString;
// the link vt+0x30: send the text (id, str, color, param)
extern std::function<void(void*, int, const char*,
                          uint32_t, uint32_t)> g_fnLinkSendText;

// ORIGINAL FUN_1419716f0 (record+0x14 stamp read)
uint32_t TitleEditStampGet(STitleMaskRec* pRec);
// ORIGINAL FUN_141971700 (record+0x14 stamp write)
void TitleEditStampSet(STitleMaskRec* pRec);

// ORIGINAL FUN_141975170
bool CMsgTitleCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen);
// ORIGINAL FUN_1419751a0 — append an idx byte at
// data+0xb+count, count++ at data+0xa, size=data+0
bool CMsgTitleAppendIdx(CMsgBase* pMsg, char cIdx);
// ORIGINAL FUN_141975260 — the incoming process
void CMsgTitleProcess(CMsgBase* pMsg, int nId);

} // namespace
