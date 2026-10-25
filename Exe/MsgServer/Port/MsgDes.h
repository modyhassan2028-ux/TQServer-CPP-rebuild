// ============================================================
// MsgServer strict port - unit M40
// THE DES OBJECT ITSELF (new(0x890),
// DES::vftable @ 0x14079b9c8):
// a descore-style fast DES.
//
// the object layout (0x890):
//   +0x08..+0x808: the 8 SP tables
//     (64 uint32 each, built by
//     FUN_14050ab10 from the S-boxes
//     + the P table - the wire
//     trick: each entry holds the
//     4 output bits of S-box b,
//     P-permuted, MSB-first in the
//     LE word; the 8 lookups OR-
//     combine with disjoint bits)
//   +0x808..+0x888: the 16 round
//     subkeys (8 bytes each; the
//     48 round bits packed 6/byte
//     in the low 6 bits, MSB-first)
//   +0x888: the mode flag. NOTE:
//     the ==2 raw-schedule path in
//     the setkey is DEAD CODE -
//     the binary clears the flag
//     to 0 FIRST and ab10 never
//     writes +0x888 (a leftover)
//   the vftable:
//     +0x00  FUN_14050b430 delete
//     +0x08  FUN_14050b340 encrypt
//     +0x10  FUN_14050b3e0 decrypt
//     +0x18  FUN_14050b0b0 set key
//     +0x20  FUN_140509220 (stub 0)
//     +0x28  FUN_140509230 (stub)
//
//  FUN_14050b340 (vt+8): the ECB
//    encrypt with the padding quirk:
//    len < 1 -> return len AS-IS;
//    per 8-byte step: if the
//    remaining < 8, memset the TAIL
//    to 0 FIRST (the pad), then
//    encrypt the block IN PLACE.
//  FUN_14050b3e0 (vt+0x10): the ECB
//    decrypt: for(len; len; len-=8)
//    decrypt block, ptr += 8 - NO
//    length guard (a non-multiple
//    runs over the buffer,
//    VERBATIM).
//  FUN_14050b0b0 (vt+0x18): the key
//    setup: time32+srand prologue
//    (the results UNUSED - Ghidra
//    artifacts of the CRT), the
//    flag=0, the SP tables, then
//    either the raw-schedule path
//    (flag==2) or the standard
//    PC-1 -> the cumulative-shift
//    rotations (the mod-28 idiom
//    i>=0x1c: i-=0x1c) -> PC-2
//    packing 6 bits/byte.
//  FUN_14050ae40: the encrypt block:
//    the block read as ONE 64-bit LE
//    word, the halves = bytes
//    0-3/4-7 (the descore IP-by-
//    load-order trick), 16 rounds
//    alternating, the halves
//    swapped at the end.
//  FUN_14050af70: the decrypt block:
//    the rounds 15..0 (the reversed
//    schedule from +0x880).
//  FUN_14050ad10: the round f: 8 SP
//    lookups ((h<<1|h>>31)^ks[7-i])
//    & 0x3f, OR-combined.
//  FUN_14050ab10: the SP table
//    builder from the extracted
//    .data tables (des_tables.json).
// ============================================================
#pragma once
#include <cstdint>
#include <cstring>
#include <vector>

namespace msg {

// the 0x890 object
struct MsgDesCtx {
    // +0x08..+0x808: 8*64 uint32
    uint32_t aSp[8][64];
    // +0x808..+0x888: 16*8 bytes
    uint8_t aKs[16][8];
    // +0x888
    int nMode;
    // vftable slot 0 = delete
    bool bDeleted = false;

    // ===== FUN_14050ab10: build the
    // SP tables (returns the mode
    // flag value it leaves)
    static void BuildSp(
        MsgDesCtx& r);

    // ===== FUN_14050b0b0 (vt+0x18)
    static void SetKey(
        MsgDesCtx& r,
        const uint8_t* pKey /*8*/);
    // the flag==2 raw schedule
    // branch as written in the
    // binary (documented; DEAD -
    // SetKey clears the flag
    // before the check)
    static void SetKeyRaw(
        MsgDesCtx& r,
        const uint8_t* pSched
        /*128*/);

    // ===== FUN_14050ae40
    static void EncryptBlock(
        MsgDesCtx& r, uint8_t*
            pBlock /*8*/);
    // ===== FUN_14050af70
    static void DecryptBlock(
        MsgDesCtx& r, uint8_t*
            pBlock /*8*/);
    // ===== FUN_14050ad10 (the round
    // f). param_3 = the 8-byte
    // subkey entry
    static uint32_t RoundF(
        const MsgDesCtx& r,
        uint32_t h,
        const uint8_t* pKs);

    // ===== FUN_14050b340 (vt+8)
    static uint32_t Encrypt(
        MsgDesCtx& r, uint8_t* p,
        uint32_t nLen);
    // ===== FUN_14050b3e0 (vt+0x10)
    static int Decrypt(
        MsgDesCtx& r, uint8_t* p,
        int nLen);
    // ===== FUN_14050b430 (vt+0)
    static void Destroy(
        MsgDesCtx& r);
};

} // namespace msg
