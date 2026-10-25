// ============================================================
// MsgServer strict port - unit M42
// THE STANDARD DES ENGINE (the OpenSSL
// libeay32 emulation). The Cheating
// Program Monitor thread imports
// DES_string_to_key / DES_set_key_checked
// / DES_cfb64_encrypt from libeay32 -
// these are the REAL OpenSSL routines
// (NOT the custom-variant descore of
// M40), so this port implements the
// standard FIPS DES tables verbatim.
//
// Every piece is cross-verified:
//   - the block cipher vs OpenSSL
//     (legacy provider) + pycryptodome
//     on 500 random vectors + the
//     classic pairs
//   - DES_string_to_key per the
//     OpenSSL str2key.c source (the
//     parity table, the <<1 fold, the
//     CBC-cksum fold with ivec=key,
//     the second parity pass)
//   - DES_cfb64_encrypt vs
//     `openssl enc -des-cfb` on full
//     and partial blocks (the num
//     cycling, the cipher-byte
//     feedback on decrypt)
// ============================================================
#pragma once
#include <cstdint>

namespace msg {

// the OpenSSL DES_key_schedule (the
// binary allocates 0x80 bytes on the
// stack: local_a88 = the schedule)
struct MsgStdDesSchedule {
    // 16 round keys, 48 bits each,
    // 6 bits/byte in the low bits,
    // MSB-first (same packing as the
    // M40 setkey, standard tables)
    uint8_t round[16][8];
};

// DES_set_odd_parity - the computed
// form of the literal 256-entry table
// from set_key.c (verified entry by
// entry against the published table)
uint8_t MsgStdDesOddParity(uint8_t b);

// DES_set_key_unchecked (the checked
// wrapper only adds the parity/weak
// test whose result the binary IGNORES)
void MsgStdDesSetKeyUnchecked(const uint8_t key[8],
                              MsgStdDesSchedule& ks);

// DES_encrypt1 - one ECB block
void MsgStdDesEncryptBlock(const uint8_t in[8],
                           uint8_t out[8],
                           const MsgStdDesSchedule& ks);

// DES_string_to_key - the OpenSSL
// str2key.c verbatim: the <<1 fold,
// odd parity, cbc_cksum(str, key,
// len, ks, ivec=key) with the zero-
// padded tail block, odd parity again
void MsgStdDesStringToKey(const char* str,
                          uint8_t key[8]);

// DES_cfb64_encrypt - the OpenSSL
// semantics: byte-at-a-time, the
// keystream re-encrypted every 8
// bytes through the sliding ivec;
// decrypt feeds the CIPHER byte
// back, encrypt the output byte.
// *num carries the offset (0..7).
// enc=0 decrypts (DES_DECRYPT).
void MsgStdDesCfb64(const uint8_t* in,
                    uint8_t* out,
                    long length,
                    const MsgStdDesSchedule& ks,
                    uint8_t ivec[8],
                    int* num,
                    int enc);

} // namespace msg
