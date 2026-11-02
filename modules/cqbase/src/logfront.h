// ============================================================================
// logfront.h — RAW CQBase.dll v6159 · the log front ends
//   Six small functions that format a caller's text and hand it to log_Save, plus the
//   initialiser that fills the three names the logger keeps.
// MODELLING NOTE (declared, not guessed):
//   1. The binary carries no source path for these six: none of them logs an error, so
//      none of them mentions its file. They are kept together here rather than dropped
//      into a file whose name would be invented.
//   2. InitLog writes into three fixed 0x80 byte buffers (0x140be7360, 0x140be73e0,
//      0x140be7460). The ported logger holds the last two as char* globals, so InitLog
//      points them at the buffers it filled; the bytes and the cut at 0x7f are the
//      binary's own.
//   3. DebugMsg calls OutputDebugStringA twice, so that call is a hook here; there is no
//      such API in this build and the hook starts empty.
// ============================================================================
#ifndef CQBASE_LOGFRONT_H
#define CQBASE_LOGFRONT_H

#include <cstdint>

namespace tq {

// 0x140b8af10 — straight to the debugger, no file and no level
void DebugMsg(const char* pszFormat, ...);

// 0x140b8afa0 — "gmlog/" in front of the name, level 3
void GmLogSave(const char* pszName, const char* pszFormat, ...);

// 0x140b8b090 — the name as it is, level 4
void MyLogSave(const char* pszName, const char* pszFormat, ...);

// 0x140b8b140 — "syslog/" in front of the name, level 2
void SysLogSave(const char* pszName, const char* pszFormat, ...);

// 0x140b8b230 — the name as it is, level 1
void OverTimeLogSave(const char* pszName, const char* pszFormat, ...);

// 0x140b9be60 — the three names the logger keeps, each cut at 0x7f characters
void InitLog(const char* pszName, const char* pszSysLog, const char* pszSysDb, int64_t nValue);

extern void (*g_pfnOutputDebugStringA)(const char*);

extern char g_szServerName[0x80];      // 0x140be7360
extern int64_t g_nLogValue;            // 0x140be9b58

}  // namespace tq

#endif  // CQBASE_LOGFRONT_H
