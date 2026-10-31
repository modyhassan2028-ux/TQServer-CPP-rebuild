// ============================================================================
// logkernel.h — RAW CQBase.dll v6159 · logkernel.cpp
//   Twenty one line loggers, all the same shape: a stamp, the caller's text, and
//   a hand off to log_Save with the file the level belongs to.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// MODELLING NOTE (declared, not guessed):
//   1. The prefix format is "%4u ..." with no visible argument in the decompiled
//      text; the only unsigned value in hand at that point is the discarded
//      GetCurrentThreadId() result, so that is what fills it. The SYSTEMTIME the
//      same prologue collects is never read again, an unused call kept as it is.
//   2. WriteDirect and PostToThread stand in for the two paths log_Save chooses
//      between: the direct writer at 0x140b9c490 and the post to the log thread at
//      0x140b9ccd0. The direct writer builds the directory and date parts of the
//      file name and is not in this batch; the predicate at 0x140b9c460 is a seam.
//   3. g_pszSysLogFile and g_pszSysLogDbFile are the two char* globals at
//      0x140be73e0 and 0x140be7460. Their text is set by the open routine, which
//      is not in this batch, so they start null here and the writer ignores them.
// ============================================================================
#ifndef CQBASE_LOGKERNEL_H
#define CQBASE_LOGKERNEL_H

#include <cstdint>

namespace tq {

struct LogApi {
    bool (*pfnIsThreadRunning)();                                        // 0x140b9c460
    void (*pfnWriteDirect)(const char* pszFile, const char* pszText, int nLevel);  // 0x140b9c490
    void (*pfnPostToThread)(void* pKernel, const char* pszFile, const char* pszText,
                            int nLevel);                                 // 0x140b9ccd0
    uint32_t (*pfnGetCurrentThreadId)();
};
extern LogApi g_LogApi;

extern char* g_pszSysLogFile;    // 0x140be73e0
extern char* g_pszSysLogDbFile;  // 0x140be7460
extern void* g_pLogKernel;       // 0x140be9b98, the log thread when it runs

// 0x140b9bfe0 — the thread when it runs, the direct writer otherwise
void log_Save(char* pszFile, const char* pszText, int nLevel);

// 0x140b9c070 / 0x140b9c0b0 — the two pure virtuals that only report
bool ILogKernelCreate(void* pThis, void* pPort, char* pszName);
bool ILogKernelProcessMsg(void* pThis, unsigned long uMsg, void* pMsg, int nLen);

void log_InlineLogWARNING(const char* pszFormat, ...);      // 0x140b81470
void log_InlineLogMessage(const char* pszFormat, ...);      // 0x140b81570
void log_InlineLogERROR(const char* pszFormat, ...);        // 0x140b81670
void log_InlineLogCATCH_ERROR(const char* pszFormat, ...);  // 0x140b81770
void log_InlineLogACTION_ERROR(const char* pszFormat, ...); // 0x140b81860
void log_InlineLogSTAMP_CHECK(const char* pszFormat, ...);  // 0x140b81960
void log_InlineLogDUMP(const char* pszFormat, ...);         // 0x140b81a60
void log_InlineLogCHEAT(const char* pszFormat, ...);        // 0x140b81b60
void log_InlineLogSTRERROR(const char* pszFormat, ...);     // 0x140b81c60
void log_InlineLogDB(const char* pszFormat, ...);           // 0x140b81d60
void log_InlineLogDBCRASH(const char* pszFormat, ...);      // 0x140b81e60
void log_InlineLogDBERROR(const char* pszFormat, ...);      // 0x140b81f60
void log_InlineLogFACEBOOK(const char* pszFormat, ...);     // 0x140b82060
void log_InlineLogNETWORK(const char* pszFormat, ...);      // 0x140b82160
void log_InlineLogOSMessage(const char* pszFormat, ...);    // 0x140b82260
void log_InlineLogOSERROR(const char* pszFormat, ...);      // 0x140b82360
void log_InlineLogOSWARNING(const char* pszFormat, ...);    // 0x140b82460
void log_InlineLogLuaERROR(const char* pszFormat, ...);     // 0x140b82560
void log_InlineLogLuaWARNING(const char* pszFormat, ...);   // 0x140b82660
void log_InlineLogProfile(const char* pszFormat, ...);      // 0x140b82760

}  // namespace tq
#endif
