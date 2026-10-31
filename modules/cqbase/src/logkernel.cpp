// CQBase.dll v6159 — logkernel.cpp (0x140b81470..0x140b9c0b0)
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/csync.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace tq {

char* g_pszSysLogFile = nullptr;
char* g_pszSysLogDbFile = nullptr;
void* g_pLogKernel = nullptr;

#if defined(_WIN32)
static uint32_t ThreadId() { return (uint32_t)GetCurrentThreadId(); }
#else
static uint32_t ThreadId() { return 1; }
#endif
static bool ThreadRunning() { return false; }
static void WriteDirect(const char*, const char*, int) {}
static void PostToThread(void*, const char*, const char*, int) {}

LogApi g_LogApi = { ThreadRunning, WriteDirect, PostToThread, ThreadId };

static CMyCriticalSection* g_pLogLock = nullptr;   // DAT_140be9b68

// 0x140b9bfe0 — the log thread when it is running and there is one, the direct
// writer otherwise. A kernel handle that is missing sends the text to the writer
// even while the thread reports itself running.
void log_Save(char* pszFile, const char* pszText, int nLevel) {
    if ((g_LogApi.pfnIsThreadRunning() == false) || (g_pLogKernel == nullptr)) {
        if (g_pLogLock == nullptr) g_pLogLock = new CMyCriticalSection(2000);
        CMySingleLock lockGuard(g_pLogLock);
        g_LogApi.pfnWriteDirect(pszFile, pszText, nLevel);
    } else if (g_pLogKernel != nullptr) {
        g_LogApi.pfnPostToThread(g_pLogKernel, pszFile, pszText, nLevel);
    }
}

// the one body the twenty loggers share: the stamp, the caller's text, and the
// hand off. A message that does not fit replaces the whole line with the assert
// text rather than being cut short.
static void LogLine(const char* pszFile, const char* pszPrefix, const char* pszFormat,
                    va_list vaArgs) {
    char szBuf[0x740];
    std::memset(szBuf, 0, sizeof(szBuf));
    int nRet = snprintf(szBuf, 0x740, pszPrefix, (unsigned)g_LogApi.pfnGetCurrentThreadId());
    if (nRet < 0) return;
    if ((size_t)nRet >= 0x740) return;      // the original stops when the prefix filled it
    int nMsg = vsnprintf(szBuf + nRet, 0x740 - (size_t)nRet, pszFormat, vaArgs);
    const char* pszText = szBuf;
    if ((nMsg < 0) || ((long)(0x73e - nRet) < (long)nMsg)) {
        pszText = "ASSERT(ret < MAX_LOG_BUF_SIZE-2)\n";
    }
    log_Save((char*)pszFile, pszText, 1);
}

// 0x140b9c070 — a pure virtual that only reports, answering false
bool ILogKernelCreate(void*, void*, char*) {
    log_InlineLogERROR("MYASSERT !\"PURE_VIRTUAL_FUNCTION_0\" logthread.h:0xb");
    return false;
}

// 0x140b9c0b0
bool ILogKernelProcessMsg(void*, unsigned long, void*, int) {
    log_InlineLogERROR("MYASSERT !\"PURE_VIRTUAL_FUNCTION_0\" logthread.h:0xc");
    return false;
}

#define CQBASE_LOG_LOGGER(fnName, pszPrefix, pszTarget)                     \
    void fnName(const char* pszFormat, ...) {                               \
        va_list vaArgs;                                                     \
        va_start(vaArgs, pszFormat);                                        \
        LogLine((pszTarget), (pszPrefix), pszFormat, vaArgs);               \
        va_end(vaArgs);                                                     \
    }

CQBASE_LOG_LOGGER(log_InlineLogWARNING, "%4u WARNING: ", g_pszSysLogFile)
CQBASE_LOG_LOGGER(log_InlineLogMessage, "%4u Message: ", g_pszSysLogFile)
CQBASE_LOG_LOGGER(log_InlineLogERROR, "%4u ERROR: ", g_pszSysLogFile)
CQBASE_LOG_LOGGER(log_InlineLogCATCH_ERROR, "%4u CATCH_ERROR: ", "syslog/catch")
CQBASE_LOG_LOGGER(log_InlineLogACTION_ERROR, "%4u ACTION_ERROR: ", "syslog/actionerror")
CQBASE_LOG_LOGGER(log_InlineLogSTAMP_CHECK, "%4u STAMP_CHECK: ", "syslog/stampchk")
CQBASE_LOG_LOGGER(log_InlineLogDUMP, "%4u DUMP: ", "syslog/dump")
CQBASE_LOG_LOGGER(log_InlineLogCHEAT, "%4u CHEAT: ", "syslog/cheat")
// the target keeps the original's own misspelling, syslg and not syslog
CQBASE_LOG_LOGGER(log_InlineLogSTRERROR, "%4u STRERROR: ", "syslg/strerror")
CQBASE_LOG_LOGGER(log_InlineLogDB, "%4u DB: ", g_pszSysLogDbFile)
CQBASE_LOG_LOGGER(log_InlineLogDBCRASH, "%4u DBCRASH: ", "syslog/dbcrash")
CQBASE_LOG_LOGGER(log_InlineLogDBERROR, "%4u DBERROR: ", "syslog/dberror")
CQBASE_LOG_LOGGER(log_InlineLogFACEBOOK, "%4u FACEBOOK: ", "gmlog/facebook")
CQBASE_LOG_LOGGER(log_InlineLogNETWORK, "%4u NETWORK: ", "syslog/network")
CQBASE_LOG_LOGGER(log_InlineLogOSMessage, "%4u OSMessage: ", "syslog/otherserver")
CQBASE_LOG_LOGGER(log_InlineLogOSERROR, "%4u OSERROR: ", "syslog/otherserver")
CQBASE_LOG_LOGGER(log_InlineLogOSWARNING, "%4u OSWARNING: ", "syslog/otherserver")
CQBASE_LOG_LOGGER(log_InlineLogLuaERROR, "%4u LuaERROR: ", "syslog/lua")
CQBASE_LOG_LOGGER(log_InlineLogLuaWARNING, "%4u LuaWARNING: ", "syslog/lua")
CQBASE_LOG_LOGGER(log_InlineLogProfile, "%4u Profile: ", g_pszSysLogFile)

}  // namespace tq
