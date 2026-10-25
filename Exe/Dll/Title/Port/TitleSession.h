#pragma once
// ============================================================
// Title.dll — Port — Unit D8: the login/logout msgs
//  FUN_141974c30 — CMsgLogin::Create (id 0x3ea @+0x50)
//  FUN_141974c60 — CMsgLogin::Process (the full chain)
//  FUN_141974e00 — the login deleting dtor
//  FUN_141974f10 — CMsgLogout::Create (id 0x3eb)
//  FUN_141974f40 — CMsgLogout::Process (mgr vt+0x30)
//  FUN_141974ea0 — the logout dtor vtable swap
// ============================================================
#include <cstdint>
#include <functional>

namespace title {

struct CMsgBase;   // from TitleModule.h
// (g_fnCMsgCreate lives in TitleModule.h — D9)

// ORIGINAL FUN_141974c30
bool CMsgLoginCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen);

// ORIGINAL FUN_141974c60
void CMsgLoginProcess(CMsgBase* pMsg, int nUserId);

// ORIGINAL FUN_141974e00
void CMsgLoginDtorDel(CMsgBase* pMsg, uint8_t uFlags);

// ORIGINAL FUN_141974f10
bool CMsgLogoutCreate(CMsgBase* pMsg, const char* pBuf, uint16_t uLen);

// ORIGINAL FUN_141974f40
void CMsgLogoutProcess(int nUserId);

// ORIGINAL FUN_141974ea0
void CMsgLogoutDtor(CMsgBase* pMsg);

} // namespace
