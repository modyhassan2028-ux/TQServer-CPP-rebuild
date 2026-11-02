// ============================================================================
// logfront.cpp — RAW CQBase.dll v6159 · the log front ends
// ============================================================================
#include "modules/cqbase/src/logfront.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace tq {

char g_szServerName[0x80];         // 0x140be7360
char g_szSysLogFileBuf[0x80];      // the text the binary keeps at 0x140be73e0
char g_szSysLogDbFileBuf[0x80];    // and at 0x140be7460
int64_t g_nLogValue;               // 0x140be9b58

static void DefaultOutputDebugStringA(const char*) {}
void (*g_pfnOutputDebugStringA)(const char*) = DefaultOutputDebugStringA;

// 0x140b8af10 — the write is capped at 0x400, the last byte of that window is forced to
// zero afterwards, and the debugger receives the line and then a newline of its own.
void DebugMsg(const char* pszFormat, ...) {
    if (pszFormat == nullptr) return;
    char szLine[0x400];
    va_list args;
    va_start(args, pszFormat);
    vsnprintf(szLine, 0x400, pszFormat, args);
    va_end(args);
    szLine[0x3ff] = 0;
    g_pfnOutputDebugStringA(szLine);
    g_pfnOutputDebugStringA("\n");
}

// The shape the four savers share: a zeroed 0x740 line, the caller's format, then the last
// byte of the window cleared before the hand off.
static void SaveFormatted(const char* pszTarget, const char* pszFormat, va_list args,
                          int nLevel) {
    char szLine[0x740];
    szLine[0] = 0;
    memset(szLine + 1, 0, 0x73f);
    vsnprintf(szLine, 0x740, pszFormat, args);
    szLine[0x73f] = 0;
    log_Save((char*)pszTarget, szLine, nLevel);
}

// 0x140b8afa0 — the name is built into its own 0x80 byte buffer, which is zeroed first and
// closed at 0x7f after the snprintf
void GmLogSave(const char* pszName, const char* pszFormat, ...) {
    if (pszName == nullptr || pszFormat == nullptr) return;
    char szTarget[0x80];
    szTarget[0] = 0;
    memset(szTarget + 1, 0, 0x7f);
    snprintf(szTarget, 0x80, "gmlog/%s", pszName);
    szTarget[0x7f] = 0;
    va_list args;
    va_start(args, pszFormat);
    SaveFormatted(szTarget, pszFormat, args, 3);
    va_end(args);
}

// 0x140b8b090
void MyLogSave(const char* pszName, const char* pszFormat, ...) {
    if (pszName == nullptr || pszFormat == nullptr) return;
    va_list args;
    va_start(args, pszFormat);
    SaveFormatted(pszName, pszFormat, args, 4);
    va_end(args);
}

// 0x140b8b140
void SysLogSave(const char* pszName, const char* pszFormat, ...) {
    if (pszName == nullptr || pszFormat == nullptr) return;
    char szTarget[0x80];
    szTarget[0] = 0;
    memset(szTarget + 1, 0, 0x7f);
    snprintf(szTarget, 0x80, "syslog/%s", pszName);
    szTarget[0x7f] = 0;
    va_list args;
    va_start(args, pszFormat);
    SaveFormatted(szTarget, pszFormat, args, 2);
    va_end(args);
}

// 0x140b8b230
void OverTimeLogSave(const char* pszName, const char* pszFormat, ...) {
    if (pszName == nullptr || pszFormat == nullptr) return;
    va_list args;
    va_start(args, pszFormat);
    SaveFormatted(pszName, pszFormat, args, 1);
    va_end(args);
}

// 0x140b9be60 — every name is cut at 0x7f characters, its buffer closed right after, and
// the last parameter lands in one global whatever the names are. A null name leaves its
// buffer alone.
void InitLog(const char* pszName, const char* pszSysLog, const char* pszSysDb, int64_t nValue) {
    if (pszName != nullptr) {
        size_t nLen = strlen(pszName);
        if (nLen > 0x7e) nLen = 0x7f;
        strncpy(g_szServerName, pszName, nLen + 1);
        g_szServerName[0x7f] = 0;
    }
    if (pszSysLog != nullptr) {
        size_t nLen = strlen(pszSysLog);
        if (nLen > 0x7e) nLen = 0x7f;
        strncpy(g_szSysLogFileBuf, pszSysLog, nLen + 1);
        g_szSysLogFileBuf[0x7f] = 0;
        g_pszSysLogFile = g_szSysLogFileBuf;      // the pointer the logger reads
    }
    if (pszSysDb != nullptr) {
        size_t nLen = strlen(pszSysDb);
        if (nLen > 0x7e) nLen = 0x7f;
        strncpy(g_szSysLogDbFileBuf, pszSysDb, nLen + 1);
        g_szSysLogDbFileBuf[0x7f] = 0;
        g_pszSysLogDbFile = g_szSysLogDbFileBuf;
    }
    g_nLogValue = nValue;
}

}  // namespace tq
