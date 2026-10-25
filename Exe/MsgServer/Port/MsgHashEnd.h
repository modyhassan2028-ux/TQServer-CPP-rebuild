#ifndef MSG_HASH_END_H
#define MSG_HASH_END_H
#include <cstdint>

namespace msg {

// ===== M71a: ORIGINAL FUN_140009f20 - the END
// sentinel creator of the activity hash-map list.
// Called by the container ctor FUN_1400103b0:
//   *(container + 0x38) = FUN_140009f20(container+0x10)
// Allocates the 0x18 sentinel node and self-links it:
//   +0x00 next = self, +0x08 prev = self
// (the prev write carries the ORIGINAL's literal
// non-null check on the FIELD's address - the
// MSVC null-formality; Ghidra dropped the tail
// return: the ctor stores the result at +0x38)
void* HashEndCreate();

} // namespace msg
#endif
