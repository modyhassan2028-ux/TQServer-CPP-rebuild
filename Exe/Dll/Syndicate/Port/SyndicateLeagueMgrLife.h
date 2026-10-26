// ============================================================
// Syndicate.dll port — unit T15/D40a: the CLeagueMgr
// LIFE cycle — verbatim.
//   141775b40 — the MGR ctor (0x580 bytes): vftable +
//     19 map-family members (each with its own proxy +
//     head of a family-specific node size/isnil) + 3
//     inline proxy-head groups (+0x78/+0xa8/+0xd8) +
//     the config defaults (10000/0x10e/22/2/5/180000/1/
//     0xb4...) + DAT_141886d00 = 0 + the two post-init
//     clears (141757740/1417577c0).
//   141775800 — the MGR dtor (the reverse walk: each
//     family dtor + delete of the proxy groups).
//   141775df0 — the scalar deleting dtor.
// The 10 head allocators + 10 map ctors (incl. the
// special 141775ac0 with the 0x68 tree) + the 9 family
// dtor wrappers + the 2 post-init clears + the 2
// recursive subtree frees — all verbatim.
// The family ERASE-RANGE bodies (14175bda0/14175e410/
// 14175e0b0/14175df00/1417742e0/14175dba0/141775470/
// 14175d9f0/14175d690) are SEAMS until D41 — the
// 14173df20-family wrapper (14173ce30) is wired to
// the ALREADY-PORTED OwnEraseRange (14173cb90).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// the mgr singleton slot the ctor zeroes
extern int64_t g_MgrDat141886d00;
// the vtable seam (the real vftable slots = the ~65
// function manager API — later units)
extern void* g_fnMgrVftable;

// family erase-range seams (defaulted null until D41)
typedef void* (*FnMgrEraseRange)(void*, void*, void*,
                                 void*);
extern FnMgrEraseRange g_fnMgrErase38;   // 14175bda0
extern FnMgrEraseRange g_fnMgrErase538;  // 14175e410
extern FnMgrEraseRange g_fnMgrErase4f8;  // 14175e0b0
extern FnMgrEraseRange g_fnMgrErase4b0;  // 14175df00
extern FnMgrEraseRange g_fnMgrErase470;  // 1417742e0
extern FnMgrEraseRange g_fnMgrErase318;  // 14175dba0
extern FnMgrEraseRange g_fnMgrErase2b0;  // 141775470
extern FnMgrEraseRange g_fnMgrErase228;  // 14175d9f0
extern FnMgrEraseRange g_fnMgrErase108;  // 14175d690

// ---------- the head allocators (verbatim) ----------
void* MgrHeadAlloc30_29();   // 141756200 (0x30/isnil 0x29)
void* MgrHeadAlloc60_59();   // 141756260 (0x60/isnil 0x59)
void* MgrHeadAlloc2c0();     // 1417562c0 (0x30/0x29)
void* MgrHeadAlloc68_61();   // 141756470 (0x68/isnil 0x61)
void* MgrHeadAlloc4d0();     // 1417564d0 (0x30/0x29)
void* MgrHeadAlloc70_69();   // 1417565b0 (0x70/isnil 0x69)
void* MgrHeadAlloc610();     // 141756610 (0x30, NO isnil writes)
void* MgrHeadAlloc410();     // 141756410 (0x30/0x29)
void* MgrHeadAlloc3b0();     // 1417563b0 (0x68/isnil 0x61)

// ---------- the map ctors (verbatim) ----------
// (each takes its map slot address)
void* MgrMapCtor38R(void*);   // 14176dbc0 (+0x38)
void* MgrMapCtor108R(void*);  // 14176dcf0 (+0x108)
void* MgrMapCtor148R(void*);  // 14173df20 (the 0x28)
void* MgrMapCtor228R(void*);  // 14176dd70 (+0x228)
void* MgrMapCtor370R(void*);  // 141775750 (5 slots)
void* MgrMapCtor4b0R(void*);  // 14176de70 (+0x4b0)
void* MgrMapCtor4f8R(void*);  // 14176def0 (+0x4f8)
void* MgrMapCtor538R(void*);  // 14176df70 (+0x538)
void* MgrMapCtor318R(void*);  // 14176ddf0 (+0x318)
void* MgrMapCtor2b0(void*);   // 141775ac0 (+0x2b0)

// the family dtor wrappers (verbatim; the erase-range
// via the seams above — the 0x28 one wired to
// OwnEraseRange)
void MgrMapDtorC2f0(void*);  // 14175c2f0 (+0x38 family)
void MgrMapDtor2770(void*);  // 141762770 (+0x538)
void MgrMapDtor23d0(void*);  // 1417623d0 (+0x4f8)
void MgrMapDtor2360(void*);  // 141762360 (+0x4b0)
void MgrMapDtor5400(void*);  // 141775400 (the 5-slot)
void MgrMapDtor1fd0(void*);  // 141761fd0 (+0x318)
void MgrMapDtor5680(void*);  // 141775680 (+0x2b0)
void MgrMapDtor1f60(void*);  // 141761f60 (+0x228)
void MgrMapDtor1bd0(void*);  // 141761bd0 (+0x108)
void MgrMapDtor028(void*);   // 14173ce30 (the 0x28)

// the post-init clears + the recursive subtree frees
void MgrClear4b0(int64_t);   // 141757740 (isnil 0x29)
void MgrClear4f8(int64_t);   // 1417577c0 (isnil 0x69)
void MgrSubtreeFree29(void*, void*);  // 141755690
void MgrSubtreeFree69(void*, void*);  // 1417556e0

// ---------- the mgr life cycle ----------
void* MgrCtor(void* pMgr);      // 141775b40 (0x580 bytes)
void  MgrDtor(void* pMgr);      // 141775800
void* MgrDeletingDtor(void* pMgr,  // 141775df0
                      uint32_t uFlags);

}  // namespace syndicate
