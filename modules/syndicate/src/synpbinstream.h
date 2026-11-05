// ============================================================================
// synpbinstream.h — RAW Syndicate.dll v6159 · the three remaining vtable slots of
//   google::protobuf::io::ArrayInputStream.
//
//   The RTTI complete-object-locator at 0x141840c38 resolves to
//     ".?AVArrayInputStream@io@protobuf@google@@"
//   so the class vtable really begins at 0x141840c40:
//     +0x00  0x1417e7920   deleting dtor  (body 0x1417e5ba0 -> 0x1417e7d50)
//     +0x08  0x1417e5be0   Next(void** data, int* size)  — already ported elsewhere
//     +0x10  0x1417e5ca0   BackUp(int count)             <-- ported here
//     +0x18  0x1417e5f20   Skip(int count) -> bool       <-- ported here
//     +0x20  0x1417e6050   ByteCount() -> int64          <-- ported here
//     +0x28  0x141845128   the ZeroCopyInputStream RTTI-held interface table
//   CORRECTION to the task brief: "vtable 0x141840c50" is not the base, it is the
//   +0x10 slot that holds 0x1417e5ca0. Base = 0x141840c40. Both readings select the
//   same three bodies, which are the ones ported below.
//
//   State layout, proved instruction-by-instruction from the ctor at 0x1417e5af0
//   (rcx=this, rdx=buffer, r8d=size, r9d=block_size):
//       +0x00  qword  pVft
//       +0x08  qword  pBuffer             <- arg buffer
//       +0x10  int    nSize               <- arg size
//       +0x14  int    nBlockSize          <- (block_size > 0) ? block_size : size
//       +0x18  int    nPosition           <- 0
//       +0x1c  int    nLastReturnedSize   <- 0
//   The three bodies touch ONLY +0x10, +0x18 and +0x1c.
//
//   SEAMS: the brief listed g_pfnPbVarintSize / g_pfnPbWriteBool / g_pfnPbWriteUnknown
//   / g_pfnPbT3F50 / g_pfnPb45D0 / g_pfnPb6510. Those are the serialize/parse kit and
//   are NOT reached here — the complete call inventory of 0x1417e5ca0..0x1417e6050 is
//   only the protobuf CHECK log chain. That chain, per instruction:
//       0x1417e0d30  entry ctor (rcx=entry, edx=severity, r8=file, r9d=line)
//       0x1417e0990  entry::Append (rcx=entry, rdx=text) -> entry, called 1 or 2 times
//       0x1417e0ee0  entry::Finish -> logs, calls 0x1417e0dd0
//       0x1417e0da0  entry dtor, run by each block's unwind tail
//   msg/msgleagueconcubinesinfopb.h already exposes that chain as the 3-argument
//   g_pfnPbCheckFail(file, line, text) == ctor + ONE Append + Finish + dtor, and is
//   reused as-is for every single-append CHECK. BackUp's FIRST check appends TWO
//   literals before Finish, so a 4-argument form of the same chain is declared here
//   (concatenating them into one literal would fabricate a string absent from .rdata).
// ============================================================================
#ifndef SYNDICATE_SYNPBINSTREAM_H
#define SYNDICATE_SYNPBINSTREAM_H

#include <cstddef>
#include <cstdint>

#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"

namespace tq {

// 0x141840c40 — vtable base of google::protobuf::io::ArrayInputStream
constexpr uintptr_t kSynPbArrayInputStreamVft = 0x141840c40;
// 0x141840c50 — the address the brief names: vtable + 0x10, the BackUp slot itself
constexpr uintptr_t kSynPbArrayInputStreamBackUpSlot = 0x141840c50;

// Two-literal form of the CHECK chain on the same addresses as g_pfnPbCheckFail:
//   0x1417e0d30 -> 0x1417e0990(szTextA) -> 0x1417e0990(szTextB) -> 0x1417e0ee0
//   with 0x1417e0da0 on the unwind tail. Severity is the literal edx=3.
extern void (*g_pfnPbCheckFail2)(const char* szFile, int32_t nLine,
                                 const char* szTextA, const char* szTextB);

// The .rdata file literal every CHECK block leas:
//   0x14183fea0 / 0x14183ff60 / 0x14183fff0 / 0x141840060
//   "F:\cq\64\develop\protobuf\src\google\protobuf\io\zero_copy_stream_impl_lite.cc"
extern const char* const kSynPbZeroCopyLiteFile;
// the five message literals, one per CHECK block
extern const char* const kSynPbChkLastReturnedPositive;  // 0x14183fef0, line 0x53
extern const char* const kSynPbChkBackUpAfterNext;       // 0x14183ff20, appended 2nd
extern const char* const kSynPbChkCountLeLastReturned;   // 0x14183ffb0, line 0x55
extern const char* const kSynPbChkCountGeZeroBackUp;     // 0x141840040, line 0x56
extern const char* const kSynPbChkCountGeZeroSkip;       // 0x1418400b0, line 0x5c

// ---- the three bodies -------------------------------------------------------
// 0x1417e5ca0 — BackUp(int count): three CHECKs, then position_ -= count and
// last_returned_size_ = 0. No return value.
void SynPbArrayInBackUp(void* pSelf, int32_t nCount);

// 0x1417e5f20 — Skip(int count): one CHECK, clears last_returned_size_, then either
// advances position_ by count and answers 1, or clamps position_ to size_ and answers 0.
bool SynPbArrayInSkip(void* pSelf, int32_t nCount);

// 0x1417e6050 — ByteCount(): movsxd of the int at +0x18.
int64_t SynPbArrayInByteCount6050(void* pSelf);

// ---- the state mirror: offsets/widths straight from the ctor at 0x1417e5af0 -----
struct SynPbArrayInputStreamState {
    void*       pVft;               // +0x00
    const void* pBuffer;            // +0x08
    int32_t     nSize;              // +0x10
    int32_t     nBlockSize;         // +0x14
    int32_t     nPosition;          // +0x18
    int32_t     nLastReturnedSize;  // +0x1c
};

static_assert(offsetof(SynPbArrayInputStreamState, pVft) == 0x00, "layout");
static_assert(offsetof(SynPbArrayInputStreamState, pBuffer) == 0x08, "layout");
static_assert(offsetof(SynPbArrayInputStreamState, nSize) == 0x10, "layout");
static_assert(offsetof(SynPbArrayInputStreamState, nBlockSize) == 0x14, "layout");
static_assert(offsetof(SynPbArrayInputStreamState, nPosition) == 0x18, "layout");
static_assert(offsetof(SynPbArrayInputStreamState, nLastReturnedSize) == 0x1c, "layout");
static_assert(sizeof(SynPbArrayInputStreamState) == 0x20, "layout");

}  // namespace tq

#endif  // SYNDICATE_SYNPBINSTREAM_H
