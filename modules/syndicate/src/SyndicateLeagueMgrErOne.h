// ============================================================
// Syndicate.dll port — unit T16/D41b: the mgr family
// ERASE-ONES (the RB-rebalance erases) + their 27 leaf
// functions, verbatim.
//   Each family erase-one (141758050-class, 193 lines;
//   the two specials 141770a20/141773e60, 210) =
//     the out_of_range gate (the CRT throw) +
//     the advance + the two-child splice / one-child
//     relink + the first/last patch + the FULL
//     RB-erase fixup loop (the red/black cases with
//     the family rotate pair) + the node delete +
//     the size decrement.
//   Leaves (all template-identical across families,
//   differing only in the isnil offset):
//     the advance (141753470-class, 43 lines) +
//     rotA (right-child rotate, 33) + rotB (the
//     mirror, 33).
//   The two SPECIAL families (0x68 heads) destroy the
//   node's NESTED map (+0x20 proxy / +0x50 head) via
//   the nested erase-range before the node delete —
//   still the D41c seams g_fnNestedErA/B.
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// ---- the advances (verbatim; isnil-family) ----
void MgrAdv29A(int64_t*);   // 141753470 (family 38)
void MgrAdv29B(int64_t*);   // 1417536b0 (538)
void MgrAdv69(int64_t*);    // 141751380 (4f8)
void MgrAdv29C(int64_t*);   // 141753d70 (4b0)
void MgrAdv29D(int64_t*);   // 141753620 (318)
void MgrAdv29E(int64_t*);   // 141754000 (228)
void MgrAdv59(int64_t*);    // 1417512f0 (108)
void MgrAdv61A(int64_t*);   // 141753500 (470)
void MgrAdv61B(int64_t*);   // 141750670 (2b0)

// ---- the rotates (verbatim; rotA = the right-child
// rotation, rotB = the mirror) ----
void MgrRotA29A(void*, void*);  // 141752cd0 (38)
void MgrRotB29A(void*, void*);  // 141752d30 (38)
void MgrRotA29B(void*, void*);  // 141753bf0 (538)
void MgrRotB29B(void*, void*);  // 141753c50 (538)
void MgrRotA69(void*, void*);   // 141753320 (4f8)
void MgrRotB69(void*, void*);   // 141753380 (4f8)
void MgrRotA29C(void*, void*);  // 141753ab0 (4b0)
void MgrRotB29C(void*, void*);  // 141753b10 (4b0)
void MgrRotA29D(void*, void*);  // 1417530a0 (318)
void MgrRotB29D(void*, void*);  // 141753100 (318)
void MgrRotA29E(void*, void*);  // 1417538f0 (228)
void MgrRotB29E(void*, void*);  // 141750a30 (228)
void MgrRotA59(void*, void*);   // 141752ef0 (108)
void MgrRotB59(void*, void*);   // 141752f50 (108)
void MgrRotA61A(void*, void*);  // 1417531c0 (470)
void MgrRotB61A(void*, void*);  // 141753220 (470)
void MgrRotA61B(void*, void*);  // 141752760 (2b0)
void MgrRotB61B(void*, void*);  // 14174f930 (2b0)

// ---- the family erase-ones (verbatim) ----
void* MgrErOne38(void*, void*, void*);   // 141758050
void* MgrErOne538(void*, void*, void*);  // 14175a710
void* MgrErOne4f8(void*, void*, void*);  // 14175a300
void* MgrErOne4b0(void*, void*, void*);  // 141759ef0
void* MgrErOne470(void*, void*, void*);  // 141770a20 (special)
void* MgrErOne318(void*, void*, void*);  // 141759a90
void* MgrErOne2b0(void*, void*, void*);  // 141773e60 (special)
void* MgrErOne228(void*, void*, void*);  // 141759600
void* MgrErOne108(void*, void*, void*);  // 1417591f0

}  // namespace syndicate
