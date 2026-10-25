// ============================================================
// MsgServer strict port - unit M30
// The CMD5Checksum Update family
// ORIGINALS:
//  FUN_14050a4a0 @ 14050a4a0 - MD5Update
//   (the ctx: buf@+8 (64), countLo
//   @+0x48, countHi@+0x4c, A/B/C/D
//   @+0x50/+0x54/+0x58/+0x5c)
//  FUN_14050a5d0 @ 14050a5d0 -
//   MD5Finalize -> the 32-char
//   LOWERCASE hex std::string (per
//   byte: 0 -> "00", <0x10 -> "0%x",
//   else "%x"); the padding from
//   DAT_1409703a0 (0x80,0,0,...) with
//   the standard 0x38/0x78 pad length
//   and the 8-byte LE bit count
//   appended AFTER (from ctx+0x48)
//  FUN_14050a910 @ 14050a910 -
//   Checksum::GetCheckSum(sret,
//   input): builds the local ctx then
//   hashes input + the LITERAL SALT:
//   += '\xA3' += '\xAC' += '\xA1' +=
//   '\xA3' += "eur506,j89jfmncvl"
//  FUN_14050aa70 @ 14050aa70 - vt+8:
//   in place (the input buffer gets
//   the checksum string)
//  FUN_14050a7f0 @ 14050a7f0 -
//   Standard::Update (vt+8 of the
//   Standard vftable): hashes ONLY the
//   raw input (NO salt), in place
// The block math = the standard MD5
// transform (140509c00; 0x242070db
// confirmed) - REUSED from M13's
// RFC-verified MsgMd5Transform.
// ============================================================
#pragma once
#include <cstdint>
#include <string>

namespace msg {

// the checksum ctx (0x60 bytes)
struct MsgMd5CsCtx {
    void* pVt;              // +0x00
    unsigned char buf[64];  // +0x08
    uint32_t nCountLo;      // +0x48
    uint32_t nCountHi;      // +0x4c
    uint32_t nA;            // +0x50
    uint32_t nB;            // +0x54
    uint32_t nC;            // +0x58
    uint32_t nD;            // +0x5c
};

// the MD5 padding (DAT_1409703a0)
extern const unsigned char
    g_MsgMd5Pad[64];

// ===== FUN_14050a4a0
void MsgMd5CsUpdate(MsgMd5CsCtx& rC,
                    const void* p,
                    uint32_t nLen);
// ===== FUN_14050a5d0
void MsgMd5CsFinalize(MsgMd5CsCtx& rC,
                      std::string& rOut);
// ===== FUN_14050a910
void MsgMd5CsGetCheckSum(
    std::string& rOut, const char* pIn);
// ===== FUN_14050aa70 (vt+8,
// in place). Returns 0.
uint64_t MsgMd5CsVt8InPlace(void* pObj,
                            char* pBuf);
// ===== FUN_14050a7f0 (Standard vt+8,
// in place, NO salt). Returns 0.
uint64_t MsgMd5StdVt8InPlace(void* pObj,
                             char* pBuf);

// the literal salt
extern const char* const
    g_MsgMd5Salt;

} // namespace msg
