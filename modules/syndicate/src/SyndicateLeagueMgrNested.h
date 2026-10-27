// ============================================================
// Syndicate.dll port — unit T16/D41c: the two NESTED
// families (the maps inside the 0x68-family nodes of
// the league mgr), verbatim.
//   Family A (1417xxxx): nodes 0x20, isnil +0x1d,
//   color byte +0x1c (the UNALIGNED color pair).
//     subtree eraser 141726210 (19, recursive: the
//     right recursion + the left spine)
//     clear          141727640 (25: head self-links)
//     erase-one      141728290 (198: the full RB
//                    rebalance, byte-color addressing)
//     leaves: advance 141724ed0 (43) + rotA 141724c50
//                    (33) + rotB 141724cb0 (33)
//     erase-range    14172a410 (77: the CRT gates +
//                    the inline advance + the whole-map
//                    clear shortcut + the erase loop)
//   Family B (14175xxxx): nodes 0x30, isnil +0x2d,
//   color +0x2c — the mirror set:
//     1417540c0 / 1417567f0 / 1417614e0 / 141750760 /
//     141752ac0 / 14174fe10 / 141762db0
//   These ARE the g_fnNestedErA/B seams the special mgr
//   erase-ones call before the node delete (D41b).
// ============================================================
#pragma once

namespace syndicate {

// family A (isnil 0x1d / color +0x1c)
void  NestedSubtreeA(void*, void*);              // 141726210
void  NestedClearA(void*);                      // 141727640
void* NestedErOneA(void*, void*, void*);        // 141728290
void* NestedErRangeA(void*, void*, void*, void*); // 14172a410

// family B (isnil 0x2d / color +0x2c)
void  NestedSubtreeB(void*, void*);              // 1417540c0
void  NestedClearB(void*);                      // 1417567f0
void* NestedErOneB(void*, void*, void*);        // 1417614e0
void* NestedErRangeB(void*, void*, void*, void*); // 141762db0

}  // namespace syndicate
