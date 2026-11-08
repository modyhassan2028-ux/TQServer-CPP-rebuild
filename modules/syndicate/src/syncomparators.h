#ifndef SYNDICATE_SYNCOMPARATORS_H
#define SYNDICATE_SYNCOMPARATORS_H
#include <cstdint>

// Four leaf functions whose bodies are only compare logic, at 0x141780100, 0x1417e0830, 0x14174e3a0 and
// 0x1417b0920. Two of them are the ordering predicates of a three-key record, and the ordering is not
// monotonic in the keys: the field at +0x8 orders descending while +0x4 and +0x0 order ascending, which
// is the sort of thing a "simplified" port flattens and then cannot reproduce.
namespace synd {

// 0x141780100 — signed compare of the word at +0x8, true when a >= b. `setge`, so signed.
bool Key8GreaterEqual(const void* a, const void* b);

// 0x1417e0830 — four arguments stored to the home space and returned from. Nothing is read, nothing is
// called: the original body is empty and its four stores are the shadow space. Kept with the same
// signature so call sites keep their shape.
void NoOp4(std::int32_t a, void* b, std::int32_t c, void* d);

// 0x14174e3a0 — the three-key ordering predicate. A zero first key means "empty" and sorts first; the
// word at +0x8 orders descending, then +0x4 ascending, then +0x0 ascending.
bool KeyLess3(const void* a, const void* b);

// 0x1417b0920 — a flag at +0xe decides before the word at +0x27 is compared ascending. The word sits at
// an unaligned offset, and the original reads it as a dword there.
bool FlagThenKeyLess(const void* a, const void* b);

}  // namespace synd
#endif
