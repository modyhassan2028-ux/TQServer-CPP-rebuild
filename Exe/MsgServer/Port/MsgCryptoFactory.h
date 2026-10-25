// ============================================================
// MsgServer strict port - unit M38
// The crypto provider factory
// FUN_140509280 + the vt interface
// layout (the answer to "who uses
// vt+8" - the meaning of the salt):
//
//  factory(id, &slot):
//    0 -> DES (new(0x890),
//           DES::vftable)
//    1 -> MD5::CMD5Checksum (new(
//           0x60), FUN_14050a570)
//           - the SALTED digest
//             (vt+8 =
//             FUN_14050aa70):
//             MD5(input +
//             "\xA3\xAC\xA1\xA3"
//             "eur506,j89jfmncvl")
//    2 -> MD5::CMD5ChecksumStandard
//           (new(0x60) + ctor +
//           the Standard vftable)
//           - the RAW digest
//             (vt+8 = FUN_14050a7f0)
//    3 -> the output slot is LEFT
//         UNTOUCHEN (VERBATIM: the
//         branch chain falls through
//         with no assignment)
//    other -> *slot = 0
//
//  the vt interface (the observed
//  call sites):
//    vt+0x00: the destroy call
//    vt+0x08: DES: encrypt(buf,
//              len) [key.dat: the
//              seed dword, len 4]
//             MD5: the digest
//              (src, len) IN PLACE -
//              the SALT applies to
//              the MAC fingerprint
//              path only
//    vt+0x10: DES: decrypt(buf,
//              len) [shell.dat:
//              the 0x400 read, and
//              the plugin image]
//    vt+0x18: DES: set key
//              ("*J_@'n 3" for the
//              plugin image)
//
//  M41: the factory now wires
//  REAL implementations by default
//  (pImpl owns the object):
//    DES -> MsgDes (M40, the
//      custom-variant descore;
//      zero-init = the fresh-heap
//      zeroed-pages observation)
//    Checksum/Standard ->
//      MsgMd5Checksum (M30)
//  The std::function seams stay
//  overridable (the unit tests
//  may rewire).
//
//  the users of vt+8 (the M23
//  leftover):
//    - FUN_140508610 (key.dat gen):
//      DES vt+8 (local_e8, 4) on
//      the seed
//    - FUN_1405097xx (the MAC
//      fingerprint, channel 1):
//      CMD5Checksum vt+8 (&str,
//      strlen) - THE SALT'S ONLY
//      IN-PLACE DIGEST USER: the
//      hardware fingerprint digest
//      is MD5(mac + salt)
//    - the Standard provider's
//      vt+8 is the unsalted
//      integrity digest
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace msg {

// the provider ids (VERBATIM)
enum MsgCryptoId : int {
    MSG_CRYPTO_DES = 0,
    MSG_CRYPTO_MD5_CHECKSUM = 1,
    MSG_CRYPTO_MD5_STANDARD = 2,
    MSG_CRYPTO_ID3 = 3,
};

// the provider object: the vftable
// layout of the DES/MD5 classes
struct MsgCryptoProvider {
    // vt+0x00: the dtor+delete
    std::function<void()>
        m_fnDestroy;
    // vt+0x08: DES encrypt /
    // MD5 digest (salted for the
    // Checksum, raw for the
    // Standard) - IN PLACE
    std::function<void(uint8_t*
                          pBuf,
                      uint32_t nLen)>
        m_fnProcess8;
    // vt+0x10: DES decrypt - IN
    // PLACE
    std::function<void(uint8_t*
                          pBuf,
                      uint32_t nLen)>
        m_fnProcess10;
    // vt+0x18: DES set key
    std::function<void(const
        std::string& sKey)>
        m_fnSetKey;
    int nKind = -1;   // which class
    // M41: the real object (the
    // DES ctx / the MD5 ctx),
    // owned by the provider
    std::shared_ptr<void> pImpl;
};

// the factory: VERBATIM
// FUN_140509280(param_1, param_2)
// returns false when the caller's
// slot holds nullptr
bool MsgCryptoFactory(int nId,
                      MsgCryptoProvider**
                          ppOut);

} // namespace msg
