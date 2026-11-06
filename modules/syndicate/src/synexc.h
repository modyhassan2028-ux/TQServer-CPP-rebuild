// ============================================================================
// synexc.h — RAW Syndicate.dll v6159 · the little message block the throw sites build.
//   Every call in this family was resolved through its import slot, not assumed:
//     0x1417e0d30  four fields then an empty std::string          (import 0x141823280 ctor)
//     0x1417e0da0  the string destroyed                           (import 0x141823290 dtor)
//     0x1417e0990  operator+= (char const*) on +0x18, returns the BLOCK  (import 0x141823230)
//     0x1417e0a60  _snprintf(buf,0x80,"%d",value), buf[0x7f]=0, then +=  (0x1418233c8/0x141823230)
//   The layout is reproduced field for field; the std::string inside it belongs to the platform,
//   so its bytes are the platform's, not the original's.
// ============================================================================
#ifndef TQ_SYN_EXC_H
#define TQ_SYN_EXC_H

#include <cstdint>
#include <string>

namespace tq {

struct SynMsgBlock {
    int32_t     nKind;
    const char* pszFile;
    int32_t     nLine;
    std::string strMessage;
};

SynMsgBlock* SynMsgInit(SynMsgBlock* p, int32_t nKind, const char* pszFile, int32_t nLine);  // 0x1417e0d30
void         SynMsgDestroy(SynMsgBlock* p);                                                  // 0x1417e0da0
SynMsgBlock* SynMsgAppend(SynMsgBlock* p, const char* pszText);                              // 0x1417e0990
SynMsgBlock* SynMsgAppendNumber(SynMsgBlock* p, int32_t nValue);                             // 0x1417e0a60

}  // namespace tq

#endif
