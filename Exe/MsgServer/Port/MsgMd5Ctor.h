// ============================================================
// MsgServer strict port - unit M25
// ORIGINAL: FUN_14050a570 @ 14050a570
// The MD5::CMD5Checksum ctor (the 0x60
// object behind channel 1/2 of the
// factory FUN_140509280):
//  +0x00 the CMD5Checksum vftable
//  +0x08..0x4c zeroed
//  +0x50 = 0x67452301 (A)
//  +0x54 = 0xefcdab89 (B)
//  +0x58 = 0x98badcfe (C)
//  +0x5c = 0x10325476 (D)
// (the standard MD5 init state)
// ============================================================
#pragma once
#include <cstdint>

namespace msg {

extern const void* g_pMd5ChecksumVt;

// ===== ORIGINAL FUN_14050a570
void* MsgMd5ChecksumCtor(void* pObj);

} // namespace msg
