// ============================================================================
// synnodescal.h — RAW Syndicate.dll v6159 · the counted node allocators, the string
//   destructor of a name node, the lower_bound walk and the two step wrappers,
//   0x1417c64b0..0x1417c72e0.
//   The counted allocators all read: if (n != 0 && (SIZE_MAX / n) < element) throw
//   std::bad_alloc; returnnew(n * element) — the div/cmp pair at 0x1417c6728 is the
//   proof, jae skips the throw when the quotient is at least the element size.
// ============================================================================
#ifndef SYNDICATE_SYNNODESCAL_H
#define SYNDICATE_SYNNODESCAL_H

#include <cstdint>
#include <string>

namespace tq {

void* SynNodeNewCount30(void* pCount);    // 0x1417c6710  n * 0x30 (0x1417c6910 same body)
void* SynNodeNewCount48(void* pCount);    // 0x1417c6790  n * 0x48
void* SynNodeNewCount28(void* pCount);    // 0x1417c6810  n * 0x28

// 0x1417c69e0 — destroys the std::string that sits at +0x18 of the node
void SynNodeStringDtor(void* pNode);

// 0x1417c7080 — the lower_bound walk over the name instantiation: start at head->parent
//   (the root), go right while node->key < target, otherwise take the node as the candidate
//   and go left. The head itself is the answer when nothing is greater or equal.
void* SynMapLowerBoundName(void* pOwner, const std::string* pKey);

// 0x1417c72c0 / 0x1417c72e0 — step back, hand the iterator back
void* SynIterPrevWrapId(void* pIter);
void* SynIterPrevWrapName(void* pIter);

}  // namespace tq

#endif  // SYNDICATE_SYNNODESCAL_H
