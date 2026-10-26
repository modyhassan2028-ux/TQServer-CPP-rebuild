// SyndicateLeagueRobOptClass.h — D71
//
// The syndicate::CMsgLeagueRobOpt family (protobuf-backed
// CMsg, wire id 0xa52) — the league "rob opt" message used
// by FUN_14176b0d0 (CLeagueMgr::PlunderWarStart, its own
// unit) and consumed at decompile line 123718. Family map
// (all verbatim, RAW-VERIFIED against the original
// Syndicate.dll, Dec 11 2015 build):
//   ---- the wrapper (CMsgLeagueRobOpt, 0x460) ----
//   1417d8390  CMsg ctor      (ported earlier in
//                              SyndicateCMsgCtors.cpp;
//                              REUSED here)
//   1417d83e0  CMsg dtor      (vft pair + PB dtor)
//   1417d86a0  deleting dtor  (flags&1 -> op_delete)
//   1417d84d0  Create         (has-bits 1|2, f1@+0x440,
//                              f2@+0x444, 0xa52@+0xa)
//   1417d8530  Clear           (PB vt[3] + size refresh)
//   1417d8570  Serialize       (0x3fc cap + the two
//                              failure logs; RAW shape =
//                              D69's, different DATs)
//   1417d8420  CreateBufMsg    (wire check 0xa52@+0xa,
//                              parse(buf+4,len-4), the
//                              two parse failure logs)
//   1417d8700  GetCount        (u16 @+0x450)
//   1417d8710  GetEntry        (elements[i])
//   1417d8730  GetOrAddEntry   (reuse; else Reserve then
//                              new; RAW == D69 shape but
//                              entry size 0x50)
//   1417d8640  NewEntry        (op_new(0x50) + entry ctor)
//   1417d8810  AppendDword     (gate cached+4 < 0x400,
//                              entry has|=1, value@+0x48)
//   1417d8870  AppendDwordString (gate cached+0x24 <
//                              0x400, value + str1 via
//                              1417d8220, non-empty str2
//                              via 1417d82b0 — the raw
//                              strlen scan skips EMPTY)
//   ---- the entry string setters ----
//   1417d8220  SetStr1         (has|=2, lazy string
//                              @+0x38, assign(char*,n))
//   1417d82b0  SetStr2         (has|=4, lazy string
//                              @+0x40, assign(char*,n))
//   ---- the PB (CMsgLeagueRobOptPB @+0x408, 0x58) ----
//   1417f05f0  PB ctor         (ported earlier; REUSED)
//   1417f0650  PB +0x34 read   (cached size)
//   1417f0660  PB dtor         (loop to ALLOCATED@+0x4c
//                              with per-entry null check
//                              + vt[0](,1); delete
//                              elements@+0x40; the +0x08
//                              inline string; base dtor)
//   1417f06f0  PB New          (op_new(0x58) + ctor)
//   ---- the entry (CMsgLeagueRobOptServerPB, 0x50) ----
//   1417efb90  deleting helper (if != 0 -> vt[0](,1))
//   1417efbd0  entry ctor      (string@+8, default
//                              instance into the +0x38
//                              and +0x40 string slots)
//   1417efc40  entry +0x34 read
//   1417efc50  entry copy ctor (ctor + CopyFrom)
//   1417efce0  entry dtor      (frees +0x38/+0x40 unless
//                              default/null; +0x08 string;
//                              base dtor)
//   1417efd70  entry New        (op_new(0x50) + ctor)
//   1417efdb0  entry Swap       (+0x48/+0x38/+0x40/
//                              +0x30 pairwise, +the +0x34)
//   1417ef8f0  entry CopyFrom   (CHECK(this!=from) with
//                              the msgleaguerobopt.pb.cc
//                              0x120 line; has-bits 1 ->
//                              value, 2 -> 1417ef430,
//                              4 -> 1417ef520; tail:
//                              append(this+8, from+8))
//   1417ef430  str1 merge      (has|=2, lazy +0x38,
//                              assign(const string&))
//   1417ef520  str2 merge      (has|=4, lazy +0x40,
//                              assign(const string&))
//   1417e0110  ReserveEntries  (SHARED with D69 — the
//                              same raw function,
//                              reused from
//                              SyndicateLeagueBeRob)
//
// Layout (raw, from the ctors/dtors/creators):
//   CMsgLeagueRobOpt (0x460 — the stack arrays in
//   FUN_14176b0d0 (local_5a8) are exactly this size):
//     +0x000 vptr        +0x008 size u16 (PB cached sz)
//     +0x00a type u16 (0xa52)  +0x00c serialize buffer
//     +0x408 PB object (0x58 bytes, below)
//     +0x438 PB has-bits alias  +0x440 PB f1 alias
//     +0x444 PB f2 alias
//     +0x448 PB elements alias (PB+0x40)
//     +0x450 PB current_size   (u16 read by GetCount)
//     +0x454 PB allocated_size  +0x458 PB capacity
//   PB (CMsgLeagueRobOptPB, 0x58):
//     +0x00 vptr   +0x08 std::string (0x28 slot)
//     +0x30 has-bits u32   +0x34 cached u32
//     +0x38 f1 u32 (type)  +0x3c f2 u32
//     +0x40 elements void**
//     +0x48 current i32  +0x4c allocated i32
//     +0x50 capacity i32
//   entry (CMsgLeagueRobOptServerPB, 0x50):
//     +0x00 vptr  +0x08 std::string (0x28 slot)
//     +0x30 has-bits u32  +0x34 cached u32
//     +0x38 str1: std::string* (default =
//          DAT_141886ea0, the PB default instance)
//     +0x40 str2: std::string* (default, same)
//     +0x48 value i32
//
// RAW notes vs the decompile (capstone on the recovered
// original Syndicate.dll):
//   * 1417d8420's mismatch/null tails are "xor al,al;
//     ret" — the decompile's "0xa00"/"in_RAX & ~0xff"
//     are artifacts; ONLY AL is cleared.
//   * 1417d8870's str2 gate is the raw "repne scasb;
//     not rcx; cmp rcx,1; je skip" — i.e. str2 is
//     skipped when EMPTY, not merely when null.
//   * 1417f0660's loop bound is dword [rdi+0x4c]
//     (allocated), each slot null-checked before
//     vt[0](entry,1) — RAW byte shape:
//     cmp dword ptr [rcx + 0x4c], ebx; jle ..;
//     loop: mov rcx,[rsi+rax]; test; je; vt[0](,1).
//   * 1417d8220/1417d82b0 tails are
//     assign(const char*, size_t) (import-verified:
//     ?assign@...QEAAAEAV12@PEBD_K@Z); the merge
//     helpers 1417ef430/1417ef520 tail
//     assign(const string&) (AEBV12@@); the CopyFrom
//     tail is append(const string&) (??Y...AEBV12@@).
//   * 1417d8730's reuse path does NOT clear the reused
//     entry (verbatim), and the new path increments
//     allocated (+0xc) BEFORE storing, current (+0x8)
//     after (raw: inc [rbx+0xc]; mov [rax+rcx*8],r11;
//     inc dword ptr [rbx+8]).
//   * 1417d84d0 calls tq::CMsg::Init (1417e8016) FIRST
//     — no PB clear; then PB vt[8] (offset +0x40) for
//     the cached size into msg+8.
#ifndef SYNDICATE_LEAGUE_ROB_OPT_CLASS_H
#define SYNDICATE_LEAGUE_ROB_OPT_CLASS_H

#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- new seams for this family ----
// the entry class vftable seam
extern void* g_pVtCMsgLeagueRobOptServer;
// 1417dedc0 — PB ParseFromArray: (pb, buf, len) -> ok?
extern char (*g_fnPbParseFromArray)(void* pPb,
    const void* pBuf, int nLen);
// log_InlineLogERROR 2-arg (fmt, str):
//   CreateBufMsg parse fail   fmt = DAT_14183cd30
//   Serialize fail            fmt = DAT_14183cdd0
extern void (*g_fnLogRobOptErr)(const void* pFmt,
                                const char* pStr);
// log_InlineLogERROR 1-arg (the literal fail lines)
extern void (*g_fnLogRobOptFail)(const void* pStr);
// the protobuf CHECK machinery used by the entry
// CopyFrom (GoogleLog FATAL; seams so tests can trap):
//   1417e0d30 (buf, 3, file, line) -> msg-builder
extern void* (*g_fnPbCheckBuild)(void* pBuf, int nLevel,
    const void* pFile, int nLine);
//   1417e0990 (msg, text) -> stream
extern void* (*g_fnPbCheckText)(void* pMsg,
                                const void* pText);
//   1417e0ee0 (dst, src)
extern void  (*g_fnPbCheckStream)(void* pDst,
                                  void* pSrc);
//   1417e0da0 (buf) — destroy
extern void  (*g_fnPbCheckDone)(void* pBuf);

// ---- the wrapper (CMsgLeagueRobOpt, 0x460) ----
// ctor: CtorCMsgLeagueRobOpt (1417d8390) — already in
// SyndicateCMsgCtors.{h,cpp}; reused, not redefined.
void   DtorCMsgLeagueRobOpt(void* pMsg);             // 1417d83e0
void   DeletingDtorCMsgLeagueRobOpt(void* pMsg,
                                    uint64_t uFlags); // 1417d86a0
bool   CreateLeagueRobOpt(void* pMsg, uint16_t uType,
                          uint32_t uF2);              // 1417d84d0
void   ClearLeagueRobOpt(void* pMsg);                 // 1417d8530
uint64_t SerializeLeagueRobOpt(void* pMsg);           // 1417d8570
bool   CreateBufMsgLeagueRobOpt(void* pMsg,
        const void* pBuf, uint16_t uLen);              // 1417d8420
uint16_t GetCountLeagueRobOpt(void* pMsg);            // 1417d8700
void*  GetEntryLeagueRobOpt(void* pMsg, int i);       // 1417d8710
void*  GetOrAddEntryLeagueRobOpt(void* pRep);         // 1417d8730
void*  NewEntryLeagueRobOpt();                        // 1417d8640
uint64_t AppendDwordLeagueRobOpt(void* pMsg,
                                 int32_t nVal);       // 1417d8810
uint64_t AppendDwordStringLeagueRobOpt(void* pMsg,
        int32_t nVal, const char* psz1,
        const char* psz2);                            // 1417d8870
void   SetStr1EntryRobOpt(void* pEntry, const char* psz,
                          size_t n);                 // 1417d8220
void   SetStr2EntryRobOpt(void* pEntry, const char* psz,
                          size_t n);                 // 1417d82b0

// ---- the PB (CMsgLeagueRobOptPB @+0x408) ----
// ctor: CtorCMsgLeagueRobOptPB (1417f05f0) — already in
// SyndicateCMsgCtors.{h,cpp}; reused, not redefined.
uint32_t GetCachedLeagueRobOptPB(void* pPb);          // 1417f0650
void   DtorLeagueRobOptPB(void* pPb);                 // 1417f0660
void*  NewLeagueRobOptPB();                           // 1417f06f0

// ---- the entry (CMsgLeagueRobOptServerPB, 0x50) ----
void   EntryDeletingHelperRobOpt(void* pEntry);       // 1417efb90
void*  EntryCtorLeagueRobOptServer(void* pEntry);     // 1417efbd0
uint32_t EntryGetCachedLeagueRobOptServer(
    void* pEntry);                                    // 1417efc40
void*  EntryCopyCtorLeagueRobOptServer(void* pDst,
                                       void* pSrc);   // 1417efc50
void   EntryDtorLeagueRobOptServer(void* pEntry);     // 1417efce0
void*  EntryNewLeagueRobOptServer();                  // 1417efd70
void   EntrySwapLeagueRobOptServer(void* pA,
                                   void* pB);         // 1417efdb0
void   EntryCopyFromLeagueRobOptServer(void* pDst,
                                      void* pSrc);    // 1417ef8f0
void   EntryMergeStr1LeagueRobOptServer(
    void* pEntry, const void* pStr);                  // 1417ef430
void   EntryMergeStr2LeagueRobOptServer(
    void* pEntry, const void* pStr);                  // 1417ef520

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_ROB_OPT_CLASS_H
