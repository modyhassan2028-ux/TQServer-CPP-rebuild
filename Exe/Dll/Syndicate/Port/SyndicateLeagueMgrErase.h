// ============================================================
// Syndicate.dll port — unit T16/D41a: the MGR family
// ERASE-RANGES (the nine seams from D40a become REAL),
// verbatim.
//   The seven uniform families + the two specials
//   (1417742e0/141775470 — the 0x68-head maps whose
//   nodes carry a NESTED map at +0x20 with its head at
//   +0x50).
//   Each family erase-range = the CRT proxy gates + the
//   whole-range fast path (the family clear) + the
//   per-node loop (the inline successor advance + the
//   family erase-one).
// Ported here: 9 erase-ranges + 5 clears + 5 subtree
//   frees + 2 recursive nested frees.
// STILL SEAMS (D41b — never reached on the empty map):
//   the 9 family erase-ones (141758050-class, the RB
//   rebalance ~193 lines) + the 2 nested erase-ranges
//   (14172a410/141762db0).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// ---- the D41b sub-seams (the erase-ones + nested) ----
typedef void* (*FnMgrEraseOne)(void*, void*, void*);
extern FnMgrEraseOne g_fnMgrErOne38;    // 141758050
extern FnMgrEraseOne g_fnMgrErOne538;   // 14175a710
extern FnMgrEraseOne g_fnMgrErOne4f8;   // 14175a300
extern FnMgrEraseOne g_fnMgrErOne4b0;   // 141759ef0
extern FnMgrEraseOne g_fnMgrErOne470;   // 141770a20
extern FnMgrEraseOne g_fnMgrErOne318;   // 141759a90
extern FnMgrEraseOne g_fnMgrErOne2b0;   // 141773e60
extern FnMgrEraseOne g_fnMgrErOne228;   // 141759600
extern FnMgrEraseOne g_fnMgrErOne108;   // 1417591f0
typedef void* (*FnNestedEr)(void*, void*, void*, void*);
extern FnNestedEr g_fnNestedErA;        // 14172a410
extern FnNestedEr g_fnNestedErB;        // 141762db0

// ---- the subtree frees (verbatim) ----
void MgrSub29A(void*, void*);   // 141755490 (0x29)
void MgrSub29B(void*, void*);   // 141755730 (0x29)
void MgrSub29C(void*, void*);   // 141755640 (0x29)
void MgrSub29D(void*, void*);   // 141756920 (0x29)
void MgrSub59A(void*, void*);   // 1417555f0 (0x59)

// ---- the recursive nested frees (the specials) ----
void MgrNestedFreeA(void*, void*);  // 1417713d0
void MgrNestedFreeB(void*, void*);  // 1417714e0

// ---- the clears (verbatim) ----
void MgrClear38(int64_t);   // 141757580 (0x29)
void MgrClear538(int64_t);  // 141757840 (0x29)
void MgrClear318(int64_t);  // 1417576c0 (0x29)
void MgrClear228(int64_t);  // 1417599c0 (0x29)
void MgrClear108(int64_t);  // 141757640 (0x59)
// (the 4b0/4f8 clears = MgrClear4b0/MgrClear4f8 —
//  already ported in SyndicateLeagueMgrLife)

// ---- the nine family erase-ranges (verbatim) ----
void* MgrEraseRange38(void*, void*, void*, void*);   // 14175bda0
void* MgrEraseRange538(void*, void*, void*, void*);  // 14175e410
void* MgrEraseRange4f8(void*, void*, void*, void*);  // 14175e0b0
void* MgrEraseRange4b0(void*, void*, void*, void*);  // 14175df00
void* MgrEraseRange470(void*, void*, void*, void*);  // 1417742e0
void* MgrEraseRange318(void*, void*, void*, void*);  // 14175dba0
void* MgrEraseRange2b0(void*, void*, void*, void*);  // 141775470
void* MgrEraseRange228(void*, void*, void*, void*);  // 14175d9f0
void* MgrEraseRange108(void*, void*, void*, void*);  // 14175d690

}  // namespace syndicate
