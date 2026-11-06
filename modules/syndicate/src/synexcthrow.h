// ============================================================================
// synexcthrow.h — RAW Syndicate.dll v6159 · 0x1417e0dd0, what every CHECK site ends in.
//   Resolved facts behind this port:
//     +0x00 kind   3 means "throw":  the block is handed to __CxxThrowException with the
//                  std::exception type_info (0x141881eb8, a .rdata RTTI record).
//                 other kinds only log.
//     0x14188664   is a function pointer living in .data (a log sink), not an import, called
//                  with (kind, file, line, &message). It is the FALLBACK: the wrapper sets a
//                  "already recorded" flag when the log level is above zero, and only an
//                  unrecorded message reaches the sink. Kind 3 skips the wrapper, so it always
//                  reaches the sink and is then thrown.
// ============================================================================
#ifndef TQ_SYN_EXCTHROW_H
#define TQ_SYN_EXCTHROW_H

#include <cstdint>

#include "modules/syndicate/src/synexc.h"

namespace tq {

extern int32_t* g_pnLogLevel;                                        // 0x1418a3xxx counter
extern void     (*g_fnLogBegin)(int32_t* pOut, int32_t* pSomewhere);  // 0x1417e1680
extern void     (*g_fnLogEnd)(int32_t* pSomewhere);                   // 0x1417e16c0
extern void     (*g_fnLogInit)(void);                                 // 0x1417e0920
extern void     (*g_pfnLogSink)(int32_t nKind, const char* pszFile, int32_t nLine, std::string* pMsg);
extern void     (*g_fnThrowException)(SynMsgBlock* pMsg, const void* pTypeInfo);   // 0x1417e16e0/0x1417f3154

// 0x1417e0dd0
void SynReportMsg(SynMsgBlock* pMsg);

}  // namespace tq

#endif
