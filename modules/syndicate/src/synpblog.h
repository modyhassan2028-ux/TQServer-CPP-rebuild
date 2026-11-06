// ============================================================================
// synpblog.h — RAW Syndicate.dll v6159 · the protobuf log-message append family and two
//   small helpers. Every append body is the same shape, only the format literal differs:
//       char aBuf[0x80];  sprintf_s(aBuf, 0x80, "<literal>", value); aBuf[0x7f] = 0;
//       *(std::string*)(this + 0x18).append(aBuf);  return this;
//   The literals are read from .rdata:
//     0x1417e09d0  "%c"   (0x14183f3fc)  the byte is sign-extended into r9d
//     0x1417e0a60  "%d"   (0x14183f400)
//     0x1417e0af0  "%u"   (0x14183f404)
//     0x1417e0b80  "%ld"  (0x14183f408)  a 64-bit value
//     0x1417e0c10  "%lu"  (0x14183f40c)  a 64-bit value
//     0x1417e0ca0  "%g"   (0x14183f410)  the double arrives in xmm1
//   Two more, exact:
//     0x1417e0950  *(std::string*)(this + 0x18).append(*(const std::string*)arg); return this
//     0x1417e00e0  return (*(const uint64_t*)this != 0)   — the cmp/je/set shape, not a try
// ============================================================================
#ifndef SYNDICATE_SYNPBLOG_H
#define SYNDICATE_SYNPBLOG_H

#include <cstddef>
#include <cstdint>

namespace tq {

// MSVCP90 std::string::append(const char*)
extern void (*g_fnLogAppendCStr)(void* pStr, const char* psz);
// MSVCP90 std::string::append(const std::string&)
extern void (*g_fnLogAppendStr)(void* pStr, const void* pOther);
// the sprintf_s the originals call
extern int (*g_fnLogFormat)(char* pszBuf, size_t uSize, const char* pszFmt, ...);

void* SynLogAppendChar(void* pThis, uint8_t uValue);     // 0x1417e09d0
void* SynLogAppendInt(void* pThis, int32_t nValue);      // 0x1417e0a60
void* SynLogAppendUInt(void* pThis, uint32_t uValue);    // 0x1417e0af0
void* SynLogAppendLong(void* pThis, int64_t nValue);     // 0x1417e0b80
void* SynLogAppendULong(void* pThis, uint64_t uValue);   // 0x1417e0c10
void* SynLogAppendDouble(void* pThis, double dValue);    // 0x1417e0ca0
void* SynLogAppendString(void* pThis, const void* pOther); // 0x1417e0950
bool  SynLogHasValue(void* pThis);                       // 0x1417e00e0

}  // namespace tq

#endif  // SYNDICATE_SYNPBLOG_H
