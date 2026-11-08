// synrbfindoradd.h — 0x14172ae00, the map's find-or-insert: a lower-bound walk, the hint fixed up
// to the predecessor when the walk ended on the left, then the shared insert tail of 0x1417293c0.
// Node layout (as the sibling rows use it): 0x00 left, 0x08 parent, 0x10 right, 0x18 uint32 key,
// 0x1d the nil/colour byte. The map carries the word copied into every iterator at +0x00 and the
// header node at +0x30.
#pragma once
#include <cstdint>

namespace tq {

// (this, pair<iterator,bool>* out, const uint32_t* key) -> out, as the bytes return rdx in rax.
void* Slot_14172ae00(void* pThis, void* pOutIter, const uint32_t* pKey);

}  // namespace tq
