// ============================================================
// MsgServer strict port - unit M12
// ORIGINAL: FUN_140507260 - the MD5 core
// transform (state[4], 64-byte block)
// Every constant kept in the decompile's own
// SIGNED form (-0x28955b88, not 0xd76aa478)
// and every rotate as the multiply/or shift
// the ORIGINAL shows - e.g.
//   (t * 0x80 | t >> 0x19)  = rotl 7
//   (t * 0x1000 | t >> 0x14)= rotl 12
//   (t >> 0xf | t * 0x20000)= rotl 17
//   (t >> 10 | t * 0x400000)= rotl 22
// The 16 words are read UNALIGNED little-endian
// from the block (the ORIGINAL's CONCAT dance)
// into x[0..15] (the decompile's local_78[0..3]
// = x[0..3], local_68..local_3c = x[4..15]).
// Tail (LITERAL order): s0 += a, then the last
// step's b-line lands directly in s1, s2 += c,
// s3 += b62.
// ============================================================
#pragma once
#include <cstdint>

namespace msg {

void MsgMd5Transform(uint32_t state[4],
                     const uint8_t* pBlock);

} // namespace msg
