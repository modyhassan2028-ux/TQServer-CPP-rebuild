// ============================================================================
// synpbrows.h — RAW Syndicate.dll v6159 · every remaining incomplete vtable row found by
//   tools/scan_classes.py (RTTI). Thirteen of them are byte-identical scalar deleting
//   destructors: the class body destructor, then 0x1417f2fdc only when bit 0 of the flags
//   is set, then `this` returned. Their body destructors, all read from the call targets:
//     0x1417e79d0 ArrayOutputStream           -> 0x1417e6120
//     0x1417e7a10 StringOutputStream          -> 0x1417e6510
//     0x1417e7b10 CopyingOutputStreamAdaptor  -> 0x1417e7360
//     0x1417e7a50 CopyingInputStream          -> 0x1417e68e0
//     0x1417e78e0 ZeroCopyInputStream         -> 0x1417e7d50
//     0x1417e7990 ZeroCopyOutputStream        -> 0x1417e7d70
//     0x1417e7ad0 CopyingOutputStream         -> 0x1417e7280
//     0x1417e1620 FunctionClosure0           -> 0x1417e1040
//     0x1417e1760 FatalException              -> 0x1417e13e0
//     0x1417e1570 Closure                    -> 0x1417e1020
//     0x1417df9e0 MessageLite                -> 0x1417de5a0
//   The non-trivial rows:
//     0x1417e6160 ArrayOutputStream::Next     (position_ +0x18, size_ +0x10, last_returned_ +0x1c,
//                                               buffer_ +0x08, the clamp 0x1417e5aa0)
//     0x1417e6220 ArrayOutputStream::BackUp   three CHECKs at 0x88 / 0x8a / 0x8b, then
//                                               position_ -= count and last_returned_ = 0
//     0x1417e7420 CopyingOutputStreamAdaptor::Next (buffer_size_ +0x28, buffer_used_ +0x2c,
//                                               0x1417e7770 gate, 0x1417e7830 flush)
//     0x1417e6900 CopyingInputStream::Skip    a 4 KB temporary buffer, the clamp, and Read
//     0x1417e15b0 FunctionClosure0::Run       this->[+8](this), then vt[0](this, 1) when the
//                                               byte at +0x10 is set
//     0x1417e1430 FatalException's predicate  std::string::empty on this + 0x28
//     0x1417e6550 StringOutputStream::Next    target_->size() (MSVCP90 0x1418231c0),
//                                               target_->capacity() (0x141823208), the growth
//                                               path guarded by numeric_limits<int>::max
//                                               / 2 (0x141823268, level 2 at line 0xaa with
//                                               the two literals 0x1418402e0 + 0x141840318),
//                                               the clamp 0x1417e0370, the resize 0x1417dffb0,
//                                               then data + old_size and capacity - old_size
// ============================================================================
#ifndef SYNDICATE_SYNPBROWS_H
#define SYNDICATE_SYNPBROWS_H

#include <cstddef>
#include <cstdint>

namespace tq {

// the eleven body destructors
extern void (*g_fnRow6120)(void*);   // ArrayOutputStream
extern void (*g_fnRow6510)(void*);   // StringOutputStream
extern void (*g_fnRow7360)(void*);   // CopyingOutputStreamAdaptor
extern void (*g_fnRow68E0)(void*);   // CopyingInputStream
extern void (*g_fnRow7D50)(void*);   // ZeroCopyInputStream
extern void (*g_fnRow7D70)(void*);   // ZeroCopyOutputStream
extern void (*g_fnRow7280)(void*);   // CopyingOutputStream
extern void (*g_fnRow1040)(void*);   // FunctionClosure0
extern void (*g_fnRow13E0)(void*);   // FatalException
extern void (*g_fnRow1020)(void*);   // Closure
extern void (*g_fnRowDE5A0)(void*);  // MessageLite
// 0x1417f2fdc — the free all of them reach
extern void (*g_fnRowFree)(void*);

// 0x1417e5aa0 — the clamp (returns a pointer to the chosen int)
extern int32_t* (*g_fnRowClamp)(int32_t* pA, int32_t* pB);
// 0x1417e7770 / 0x1417e7830 — the adaptor's gate and flush
extern bool (*g_fnRow7770)(void* pThis);
extern void (*g_fnRow7830)(void* pThis);
// 0x1417e7bf0 — the raw buffer behind the holder
extern void* (*g_fnRowBuffer)(void* pHolder);
// 0x1417e7c40 — the temporary buffer's size probe used by Skip
extern int32_t (*g_fnRow7C40)(void* pDesc);

extern void (*g_fnRowCheck1)(const char* pszFile, int32_t nLine, const char* pszText);
extern void (*g_fnRowCheck2)(const char* pszFile, int32_t nLine, const char* pszA,
                             const char* pszB);
extern const char* const kSynRowFile;

// the eleven deleting destructors
void* SynRowArrayOutDtor(void* p, uint32_t f);      // 0x1417e79d0
void* SynRowStringOutDtor(void* p, uint32_t f);     // 0x1417e7a10
void* SynRowCopyOutAdaptorDtor(void* p, uint32_t f);// 0x1417e7b10
void* SynRowCopyInDtor(void* p, uint32_t f);        // 0x1417e7a50
void* SynRowZeroInDtor(void* p, uint32_t f);        // 0x1417e78e0
void* SynRowZeroOutDtor(void* p, uint32_t f);       // 0x1417e7990
void* SynRowCopyOutDtor(void* p, uint32_t f);       // 0x1417e7ad0
void* SynRowFuncClosureDtor(void* p, uint32_t f);   // 0x1417e1620
void* SynRowFatalExcDtor(void* p, uint32_t f);      // 0x1417e1760
void* SynRowClosureDtor(void* p, uint32_t f);       // 0x1417e1570
void* SynRowMessageLiteDtor(void* p, uint32_t f);   // 0x1417df9e0

// the seven real rows
bool SynRowArrayOutNext(void* p, void** ppData, int32_t* pnSize);   // 0x1417e6160
void SynRowArrayOutBackUp(void* p, int32_t nCount);                // 0x1417e6220
bool SynRowCopyOutAdaptorNext(void* p, void** ppData, int32_t* pnSize); // 0x1417e7420
int32_t SynRowCopyInSkip(void* p, int32_t nCount);                 // 0x1417e6900
void* SynRowFuncClosureRun(void* p);                               // 0x1417e15b0
bool SynRowFatalExcIsEmpty(void* p);                               // 0x1417e1430
// 0x1417e6550 StringOutputStream::Next — target_ is the std::string at self+8
bool SynRowStringOutNext(void* p, void** ppData, int32_t* pnSize);
// the underlying-stream rows CopyingInputStream::Skip reaches: vt[1] = Read
extern int32_t (*g_fnRowRead)(void* pIn, void* pBuf, int32_t nSize);
// 0x1417e0370 — the MAX clamp the growth path uses (never below 16), and 0x1417dffb0 — the
// thin std::string::resize wrapper
extern int32_t* (*g_fnRowClamp2)(int32_t* pA, int32_t* pB);
extern void (*g_fnRowStrResizeHelper)(void* pStr, int64_t nNewSize);

}  // namespace tq

#endif  // SYNDICATE_SYNPBROWS_H
