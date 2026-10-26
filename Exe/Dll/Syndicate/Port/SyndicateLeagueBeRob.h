// SyndicateLeagueBeRob.h — D69
//
// The syndicate::CMsgLeagueBeRob family (protobuf-backed
// CMsg, wire id 0xa51) — the league "be rob" notify used
// by FUN_141771f90 (the 7453-byte distributor, its own
// unit). Family map (all verbatim):
//   1417d5460  CMsg ctor        (tq CMsg Init TWICE —
//                                verbatim base+derived)
//   1417d54b0  CMsg dtor        (vft pair + PB dtor)
//   1417d5710  deleting dtor    (flags&1 -> delete)
//   1417d54f0  Create           (fields + name + 0xa51)
//   1417d55a0  Clear            (PB vt[3] + size refresh)
//   1417d55e0  Serialize/BufMsg  (0x3fc cap + the two
//                                failure logs)
//   1417d5770  GetCount         (u16 @+0x458)
//   1417d5780  GetOrAddEntry    (the repeated field Add)
//   1417d5820  AppendDword      (size gate + entry fill)
//   1417d56b0  NewEntry         (op_new(0x40) + entry ctor)
//   1417d53f0  SetNamePB        (has-bits |= 8, +0x40 str)
//   1417e93b0  PB ctor          (CMsgLeagueBeRobPB)
//   1417e9440  PB dtor          (entries via vt[0](,1),
//                                delete[] elements)
//   1417e89a0  entry ctor       (CMsgLeagueBeRobRePB)
//   1417e89f0  entry +0x34 read (cached/has getter)
//   1417e9430  PB   +0x34 read
//   1417e0110  ReserveEntries    (max(cap*2,n) then the
//                                DAT_14183f028 floor;
//                                128-bit overflow ->
//                                op_new(~0) verbatim)
//
// NOT this family (documented exclusion): 1417d58d0
// (sets has-bits |= 4 and owns the +0x40 string slot
// with a (ptr,len) assign) — its caller at decompile
// line 149253 passes (param_2+0x1b, 0x10) from another
// message Create; it belongs to a sibling PB class.
//
// Layout (raw, from the ctor/dtor/creators):
//   CMsg (0x470 = 1136 — the three stack arrays in
//   FUN_141771f90 are exactly this size):
//     +0x000 vptr        +0x008 size u16 (PB cached sz)
//     +0x00a type u16    +0x00c serialize buffer
//     +0x408 PB object (0x68 bytes, below)
//     +0x438 PB has-bits alias   +0x440 PB f1 alias
//     +0x444 PB f2 alias         +0x450 rep (PB+0x48)
//     +0x458 rep current_size (u16 read by GetCount)
//     +0x468 PB f3 alias
//   PB (CMsgLeagueBeRobPB, 0x68):
//     +0x00 vptr   +0x08 std::string (0x28 slot)
//     +0x30 has-bits u32   +0x34 cached u32
//     +0x38 f1 u32 (type)  +0x3c f2 u32 (id)
//     +0x40 name field: std::string* (default =
//          DAT_141886ea0, the PB default instance)
//     +0x48 elements void**  +0x50 current_size i32
//     +0x54 allocated_size i32 +0x58 capacity i32
//     +0x60 f3 u32
//   entry (CMsgLeagueBeRobRePB, 0x40):
//     +0x00 vptr  +0x08 std::string (0x28 slot)
//     +0x30 has-bits u32  +0x34 cached u32
//     +0x38 value i32
//
// RAW notes vs the decompile:
//   * 1417d54f0 writes 0xa51 at "param_1+10" = +0xa
//     (CMsg byte-indexed) and the PB cached size at +8:
//     size u16 @+8, type u16 @+0xa.
//   * 1417d54b0 indexes param_1 as undefined8*: "+0x81"
//     = +0x408 bytes.
//   * 1417d5820's PB vt[8] call shows NO args in the
//     decompile (the PB this rides rcx); the size gate
//     is (i64)(i32)cached + 4 < 0x400, and the zero/
//     fail tails return rax & ~0xff (AL=0).
//   * RAW-VERIFIED against the original Syndicate.dll
//     (Dec 11 2015 build, recovered from the source
//     archive; placed at
//     co_decomp/orig_binaries/Source/Syndicate.dll):
//     1417d55e0's vt[5] sret read IS "cmp qword[rax+0x20],
//     0x10; jb -> rdx=rax+8 else rdx=[rax+8]" (the
//     exact byte shape), and AppendDword's gate/tail is
//     "test edx,edx; jne; ...; movsxd rcx,eax; add
//     rcx,4; cmp rcx,0x400; jae -> xor al,al" and the
//     entry fill "[rax+0x30]|=1; [rax+0x38]=edx".
#ifndef SYNDICATE_LEAGUE_BE_ROB_H
#define SYNDICATE_LEAGUE_BE_ROB_H

#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the class vftable seams (new for this family) ----
extern void* g_pVtCMsgLeagueBeRob;      // CMsgLeagueBeRob
extern void* g_pVtCMsgLeagueBeRobPB;     // CMsgLeagueBeRobPB
extern void* g_pVtCMsgLeagueBeRobRePB;   // CMsgLeagueBeRobRePB

// ---- PB runtime seams ----
// 1417df630: (pb, buf, cap) -> ok? — SerializeToArray
extern char (*g_fnPbSerializeToArray)(void* pPb,
    void* pBuf, size_t uCap);
// 1417e0370: (int*, int*) -> int* (returns the LARGER;
// used twice by the reserve: max(cap*2, n) then the
// DAT_14183f028 floor)
extern const int* (*g_fnPbIntMax)(const int* pA,
                                  const int* pB);
// DAT_14183f028 — the reserve floor (int global)
extern const int* g_pPbReserveFloor;
// operator delete[] (the CRT vector-delete the PB
// dtor and reserve use on the elements array)
extern void (*g_fnOpDeleteArr)(void* p);
// 1417de5a0 — the MessageLite base dtor tail
extern void (*g_fnPbBaseDtor)(void* pPb);
// log_InlineLogERROR — 2-arg (fmt DAT_14183c0c0, str)
// and 1-arg (the literal fail line)
extern void (*g_fnLogBeRobSerializeErr)(const void* pFmt,
                                         const char* pStr);
extern void (*g_fnLogBeRobSerializeFail)(const void* pFmt);

// ---- the message (raw 0x470 buffer) ----
struct CMsgLeagueBeRobMsg {
    uint8_t m_ab[0x470];
};

// ---- the family (addresses in the header banner) ----
void*     CtorCMsgLeagueBeRob(void* pMsg);          // 1417d5460
void      DtorCMsgLeagueBeRob(void* pMsg, uint64_t uA,
                              uint64_t uB, uint64_t uC); // 1417d54b0
uint64_t  DeletingDtorCMsgLeagueBeRob(void* pMsg,
                              uint64_t uFlags);     // 1417d5710
bool      CreateLeagueBeRob(void* pMsg, uint32_t uType,
                              uint32_t uId, uint32_t uParam,
                              const char* pszName);  // 1417d54f0
void      ClearLeagueBeRob(void* pMsg);              // 1417d55a0
uint64_t  SerializeLeagueBeRob(void* pMsg);          // 1417d55e0
uint16_t  GetCountLeagueBeRob(void* pMsg);           // 1417d5770
void*     GetOrAddEntryLeagueBeRob(void* pRep);      // 1417d5780
uint64_t  AppendDwordLeagueBeRob(void* pMsg,
                              int32_t nVal);        // 1417d5820
void*     NewLeagueBeRobRe();                        // 1417d56b0
void*     ProtoCtorLeagueBeRobPB(void* pPb);         // 1417e93b0
void      ProtoDtorLeagueBeRobPB(void* pPb, uint64_t uA,
                              uint64_t uB, uint64_t uC); // 1417e9440
void*     EntryCtorLeagueBeRobRe(void* pEntry);      // 1417e89a0
uint32_t  EntryGetCachedLeagueBeRobRe(void* pEntry);  // 1417e89f0
uint32_t  ProtoGetCachedLeagueBeRobPB(void* pPb);    // 1417e9430
void      ReserveEntriesLeagueBeRob(void* pRep,
                              int nMin);             // 1417e0110
void      SetNameLeagueBeRobPB(void* pPb,
                              const char* psz);      // 1417d53f0

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_BE_ROB_H
