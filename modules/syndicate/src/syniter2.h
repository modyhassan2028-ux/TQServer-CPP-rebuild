// ============================================================================
// syniter2.h — RAW Syndicate.dll v6159 · the checked-iterator plumbing at 0x1417c6c80..0x1417c6f10:
//   the two slot-zero forwarders, the two iterator comparisons, the four deleters, the two
//   value accessors and the iterator seed. Every _invalid_parameter_noinfo stays a real call
//   through g_fnInvalidParam, exactly like the rest of this port.
// ============================================================================
#ifndef SYNDICATE_SYNITER2_H
#define SYNDICATE_SYNITER2_H

#include <cstdint>

// the port already keeps one hook for _invalid_parameter_noinfo (syndicatelogic.h, the same
// one D98 bound): global namespace, so this is a re-declaration, not a second symbol
namespace syndicate { extern void (*g_fnInvalidParam)(void); }

namespace tq {


// 0x1417c6c80 — call slot zero of the object held at +0x98
void SynIterDerefHolder(void* pIter);
// 0x1417c6c90 — call slot zero of the object the iterator's first qword points at
void SynIterDerefSelf(void* pIter);
// 0x1417c6ca0 / 0x1417c6ce0 — the same comparison: the owners must both exist and match,
//   answered by comparing the second qword
bool SynIterEqualA(void* pLeft, void* pRight);
bool SynIterEqualB(void* pLeft, void* pRight);
// 0x1417c6d50 / 0x1417c6d80 / 0x1417c6db0 / 0x1417c6f10 — release the first qword
void SynIterDelete50(void* pIter);
void SynIterDelete80(void* pIter);
void SynIterDeleteB0(void* pIter);
void SynIterDeleteF10(void* pIter);
// 0x1417c6dc0 / 0x1417c6e40 — the value sits 0x18 past the second qword; a missing owner or a
//   second qword equal to the head's +0x30 is an invalid parameter
void* SynIterValue(void* pIter);
void* SynIterValue2(void* pIter);
// 0x1417c6e00 — seed: clear the first qword, take the second from the argument, then take the
//   first from the third (a null third argument is an invalid parameter)
void* SynIterInit(void* pOut, void* pOwner, void* pSource);

}  // namespace tq

#endif  // SYNDICATE_SYNITER2_H
