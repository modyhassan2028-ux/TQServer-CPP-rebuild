// ============================================================================
// synpbio.h — RAW Syndicate.dll v6159 · the last missing slots of the three protobuf io
//   stream classes, and the four numeric-limit statics that go with them.
//     0x1417e64a0  ArrayOutputStream's ByteCount   -> (int64)*(int*)(self + 0x18)
//                  (proved: the only .rdata reference to this address sits in the table at
//                   0x141840ca0, and 0x1417e64a0's body is the sign-extend of +0x18.
//                   The INPUT stream's ByteCount is 0x1417e6050, ported in synpbinstream
//                   as SynPbArrayInByteCount6050; the two bodies are byte-identical.)
//     0x1417e68b0  the std::string size at self + 8
//     0x1417e7750  CopyingAdaptor's    ByteCount  -> *(int64*)(self + 0x18) + (int)*(self + 0x2c)
//     0x1417e7980  the constant-false slot        -> 0
//     0x1417e7d90  the aliasing refusal: the protobuf log carries severity 3,
//                  the file literal at 0x141840e00 and the message at 0x141840e50, line 0x31,
//                  then the body answers 0. The log chain itself (0x1417e0d30 ctor,
//                  0x1417e0990 stream, 0x1417e0ee0 dtor, 0x1417e0da0 finalise) is a seam.
//   The four statics store numeric_limits<int>::max() into their own global, the same
//   proven shape as the D54 ones (MSVCP90 IAT 0x141823268).
// ============================================================================
#ifndef SYNDICATE_SYNPBIO_H
#define SYNDICATE_SYNPBIO_H

#include <cstdint>

namespace tq {

// 0x1417e0d30 / 0x1417e0990 / 0x1417e0ee0 / 0x1417e0da0 — protobuf's log chain
extern void (*g_fnPbLogAliasing)(int nSeverity, const char* pszFile, int nLine,
                                 const char* pszMessage);

int64_t SynPbArrayInByteCount(void* pSelf);      // 0x1417e64a0
int64_t SynPbArrayOutByteCount(void* pSelf);     // 0x1417e68b0
int64_t SynPbCopyingByteCount(void* pSelf);      // 0x1417e7750
bool SynPbSlotFalse(void);                       // 0x1417e7980
bool SynPbAliasingRefusal(void);                 // 0x1417e7d90

// the four statics
void SynLimitInit7c(void);   // 0x141821e10 -> 0x141886e7c
void SynLimitInit80(void);   // 0x141821e30 -> 0x141886e80
void SynLimitInit84(void);   // 0x141821e50 -> 0x141886e84
void SynLimitInit88(void);   // 0x141821e70 -> 0x141886e88

extern int32_t g_nSynLimit7c;
extern int32_t g_nSynLimit80;
extern int32_t g_nSynLimit84;
extern int32_t g_nSynLimit88;

}  // namespace tq

#endif  // SYNDICATE_SYNPBIO_H
