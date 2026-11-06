// ============================================================================
// synleaguemerge.h — RAW Syndicate.dll v6159 · 0x1417ebc90, the last unported row of the
//   CMsgLeagueConcubinesPB vtable (row 7, MergePartialFromCodedStream). Size 748 bytes,
//   [0x1417ebc90, 0x1417ebf7c), per .pdata.
//   The body, exactly as the instructions run it:
//     CodedInputStream over this+8 -> reader   (0x1417e64c0)
//     a second wrapper over the reader         (0x1417e4550)
//     loop { fast tag byte (>0 and present) else 0x1417e3bc0; when (tag-1) >= 0x7f -> unknown }
//       field 1 (tag 8) : varint, this+0x50 = (value != 0), this+0x30 |= 1, then a fast 0x12 probe
//       field 2 (tag 12): element path
//       anything else   : unknown path
//     element path: idx = this+0x40; if (idx < cap at +0x44) reuse arr[idx]; else grow
//       0x1417e0110(&arr, cap+1), operator new 0x68 (0x1417f3166), two vftable stores
//       (0x14183eee8 then 0x1418415e8), std::string ctor at +8 (MSVCP90 0x141823280), the
//       instance-tracker dance against 0x141886ea8, then zeroes at +0x34..+0x3c, the default
//       qword 0x141886ea0 at +0x40, more zeroes +0x48..+0x60 and a 0 at +0x30.
//       RAW: +0x44 is incremented BEFORE the store, the store lands at index +0x40, and
//       +0x40 is incremented after it; then 0x1417eb540(reader, elem) parses the element.
//     end: the reader is at its end and (+0x2c != 0 or +0x28 == +0x18) -> success,
//          clearing last_tag (+0x20) and setting +0x24 = 1 on that path.
//     unknown: a zero tag or wire type 4 ends the loop; otherwise 0x1417f3f50 skips it.
//     Both exits destroy the wrapper (0x1417e45d0) and the reader (0x1417e6510); the
//     failure exit answers 0 and the success exit answers 1.
// ============================================================================
#ifndef SYNDICATE_SYNLEAGUEMERGE_H
#define SYNDICATE_SYNLEAGUEMERGE_H

#include <cstddef>
#include <cstdint>

namespace tq {

// the reader state at the offsets this body touches
struct SynPbReaderState {
    uint8_t        a00[8];       // +0x00
    const uint8_t* pPtr;         // +0x08
    const uint8_t* pEnd;         // +0x10
    int32_t        n18;          // +0x18
    int32_t        n1c;          // +0x1c
    uint32_t       uLastTag;     // +0x20
    uint8_t        b24;          // +0x24
    uint8_t        a25[3];
    int32_t        n28;          // +0x28
    int32_t        n2c;          // +0x2c
};

// 0x1417e64c0 — builds the reader over the message payload
extern void (*g_fnPb64C0)(void* pReader, void* pPayload);
// 0x1417e4550 — the tag wrapper used by every generated parser
extern void (*g_fnPb4550)(void* pWrapper, void* pReader);
// 0x1417e3bc0 — the slow tag read
extern uint32_t (*g_fnPb3BC0)(void* pReader);
// 0x1417e3d80 — the slow varint read into the destination
extern bool (*g_fnPb3D80)(void* pReader, uint64_t* pValue);
// 0x1417f3f50 — skip an unknown field
extern bool (*g_fnPbT3F50)(void* pReader, uint32_t uTag, void* pWrapper);
// 0x1417e45d0 / 0x1417e6510 — the two destructors on both exits
extern void (*g_fnPb45D0)(void* pWrapper);
extern void (*g_fnPb6510)(void* pReader);
// 0x1417eb540 — parse one element
extern bool (*g_fnPb540)(void* pReader, void* pElem);
// 0x1417e0110 — grow the element vector
extern void (*g_fnPb0110)(void* pVec, int32_t nNewCap);
// 0x1417f3166 — the allocator
extern void* (*g_fnPb3166)(size_t uBytes);
// 0x141823280 — MSVCP90 std::string::string()
extern void (*g_fnPbStrCtor)(void* pStr);
// the instance tracker: 0x1417e7c70 on 0x141886ea8 with the 0x1417e1040 finisher, and the
// two .rdata function pointers it carries (0x14183f660 / 0x14183f678 / 0x1417de4f0)
extern void (*g_fnPbInstanceTrack)(void);

// 0x1417ebc90
bool SynPbConcubinesMerge(void* pSelf, void* pIn);

}  // namespace tq

#endif  // SYNDICATE_SYNLEAGUEMERGE_H
