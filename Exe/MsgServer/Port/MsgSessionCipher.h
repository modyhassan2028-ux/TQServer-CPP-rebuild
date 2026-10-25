// ============================================================
// MsgServer strict port - unit M19
// ORIGINAL: FUN_140504b80 @ 140504b80 (enc)
//           FUN_140504bf0 @ 140504bf0 (dec)
// The session CAST-CFB64 cipher pair over
// the crypto block at conn+0x824:
//  +0x00 num_d  (4)   decrypt counter
//  +0x04 num_e  (4)   encrypt counter
//  +0x08 iv_d   (8)   decrypt IV
//  +0x10 iv_e   (8)   encrypt IV
//  +0x18 cast ctx (the key set by M18)
// ENCRYPT: cfb64(in, out, len, ctx+0x18,
//   ivec = +0x10, num = +0x4, enc=1)
// DECRYPT: cfb64(in, out, len, ctx+0x18,
//   ivec = +0x8, num = +0x0, enc=0)
// Both guard on DAT_140976588/590 (the DH
// globals) + out/in/len and return 1/0.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgCryptoBlock {   // conn + 0x824
    uint32_t uNumDec;    // +0x00
    uint32_t uNumEnc;    // +0x04
    uint64_t uIvDec;     // +0x08
    uint64_t uIvEnc;     // +0x10
    unsigned char ctx[0x40];  // +0x18
};

struct MsgSessionCipherData {
    // CAST_cfb64_encrypt(in, out, len,
    //   schedule, ivec, num, enc)
    std::function<void(const void*, void*,
                       int, void*, uint64_t*,
                       uint32_t*, int)>
        m_fnCfb64;
    // captures for the tests
    int nEncCalls = 0, nDecCalls = 0;
};

// ===== ORIGINAL FUN_140504b80 @ 140504b80
int MsgSessionEncrypt(MsgCryptoBlock& rB,
                      const void* pIn,
                      void* pOut, int nLen,
                      MsgSessionCipherData& rD);
// ===== ORIGINAL FUN_140504bf0 @ 140504bf0
int MsgSessionDecrypt(MsgCryptoBlock& rB,
                      const void* pIn,
                      void* pOut, int nLen,
                      MsgSessionCipherData& rD);

} // namespace msg
