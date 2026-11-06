// ============================================================================
// synpbadaptor.h — RAW Syndicate.dll v6159 · the whole CopyingInputStreamAdaptor class
//   (vtable 0x141840d68, RTTI name CopyingInputStreamAdaptor@io@protobuf@google).
//   State, every offset taken from the instructions:
//     +0x08  input_        the underlying CopyingInputStream (its vt[1] is Read, vt[2] Skip)
//     +0x11  at_end_       byte flag: a negative read, or a failed skip, sets it
//     +0x18  byte_count_   int64
//     +0x20  buffer_       the holder 0x1417e7bf0 hands the raw pointer for
//     +0x28  buffer_size_  int
//     +0x2c  buffer_used_  int
//     +0x30  backup_       int
//   Rows:
//     0x1417e6b70 Next    — refuses once at_end_; a pending backup_ is served out of the
//                          buffer without touching the stream; otherwise Read into the
//                          buffer, a negative answer sets at_end_, a zero or negative one
//                          calls 0x1417e7190 first; a positive one adds to byte_count_.
//     0x1417e6cc0 BackUp  — CHECK(backup_ == 0 && buffer_ != NULL) 0x10c, then
//                          CHECK(count <= buffer_used_) 0x10e, then CHECK(count >= 0) 0x111
//                          (two literals each, three files at 0x141840420 / 4e0 / 5b0),
//                          and finally backup_ = count.
//     0x1417e6f60 Skip    — CHECK(count >= 0) 0x118, refuses at at_end_, takes what it can
//                          from backup_ and only then asks the stream, adding the stream's
//                          answer to byte_count_ and answering (read == count).
//     0x1417e7110 ByteCount — byte_count_ - backup_ (int64 minus sign-extended int).
//     0x1417e7a90 the deleting destructor — 0x1417e6ad0 then the free on bit 0.
// ============================================================================
#ifndef SYNDICATE_SYNPBADAPTOR_H
#define SYNDICATE_SYNPBADAPTOR_H

#include <cstdint>

namespace tq {

// 0x1417e7bf0 — the raw buffer behind the holder at +0x20
extern void* (*g_fnPbBuffer)(void* pHolder);
// 0x1417e7140 / 0x1417e7190 — the two small bookkeeping calls Next makes
extern void (*g_fnPb7140)(void* pSelf);
extern void (*g_fnPb7190)(void* pSelf);
// 0x1417e6ad0 — the adaptor's body destructor
extern void (*g_fnPb6AD0)(void* pSelf);
// 0x1417f2fdc — the free every path reaches
extern void (*g_fnPbAdaptorFree)(void* p);

// the one-literal and two-literal CHECK reports
extern void (*g_fnPbAdaptorCheck1)(const char* pszFile, int32_t nLine, const char* pszText);
extern void (*g_fnPbAdaptorCheck2)(const char* pszFile, int32_t nLine, const char* pszA,
                                   const char* pszB);

extern const char* const kSynPbAdaptorFile;   // 0x141840420 and its three copies

bool SynPbAdaptorNext(void* pSelf, void** ppData, int32_t* pnSize);   // 0x1417e6b70
void SynPbAdaptorBackUp(void* pSelf, int32_t nCount);                 // 0x1417e6cc0
bool SynPbAdaptorSkip(void* pSelf, int32_t nCount);                   // 0x1417e6f60
int64_t SynPbAdaptorByteCount(void* pSelf);                           // 0x1417e7110
void* SynPbAdaptorDeletingDtor(void* pSelf, uint32_t uFlags);         // 0x1417e7a90

}  // namespace tq

#endif  // SYNDICATE_SYNPBADAPTOR_H
