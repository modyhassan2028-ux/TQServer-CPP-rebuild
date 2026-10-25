// ============================================================
// MsgServer strict port - unit M18
// ORIGINAL: FUN_140505bc0 @ 140505bc0
// the encrypted key-exchange receiver
//  param_1 = the connection object (the
//    CAST ctx lands at +0x18)
//  param_2 = the wire, param_3 = its len
// The LITERAL flow (offsets from the asm):
//  1. guards: !DH-init/!DH/!wire/len<0 -1;
//     len < 0xc -> 0
//  2. CAST_set_key(ctx, 0x10,
//     "C238xs65pjy7HU9Q")   [the hardcoded
//     handshake key @ 0x14079ae58]
//  3. IV (8 bytes) = 0; num = 0
//  4. cfb64(wire -> out, 0xb, ...):
//     out[7..10] = the payload length
//  5. len > 0x400 (signed) or <= 0xb -> 0;
//     param_3 < len+7 -> 0
//  6. cfb64(wire+0xb -> payload, len, ...)
//  7. *(u64*)(payload + len - 0xc) must
//     equal "TQClient" (0x14079ae38) or -1
//  8. BN_new == 0 -> -1
//  9. TLV walk: cursor = 4;
//     L = payload[cursor-4]; L < 1 -> -1;
//     cursor += L + 4; len < cursor -> -1
//     (ONE iteration)
// 10. L2 = payload[cursor-4]; needs
//     L2 > 0 && cursor + 4 + L2 <= len
// 11. hex = new(L2+1); memcpy
//     payload[cursor..]; BN_hex2bn == 0
//     -> -1   [the client pub key]
// 12. secret = new(DH_size+1);
//     DH_compute_key(secret, pub, DH)
//     == -1 -> -1
// 13. memset(token,0,0x400);
//     tokLen = FUN_140503c00(conn, token,
//     secret)   [M14]
//     0x40 -> CAST_set_key(conn+0x18,0x40,
//             token)
//     else -> CAST_set_key(conn+0x18,
//             DH_size, secret)
// 14. return len + 7
// The RAII guards (hex, secret, the BN)
// as construct/release seams at the
// exact spots.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgKeyXchgData {
    // CAST_set_key(ctx, len, key)
    std::function<void(void*, int,
                       const void*)>
        m_fnCastSetKey;
    // CAST_cfb64_encrypt(in, out, len,
    //   ctx, ivec, num, enc=0)
    std::function<void(const void*, void*,
                       int, void*, void*,
                       int*)> m_fnCastCfb64;
    // BN_new / BN_hex2bn / BN_free
    std::function<void*()> m_fnBnNew;
    std::function<int(void**,
                      const char*)>
        m_fnBnHex2bn;
    std::function<void(void*)> m_fnBnFree;
    // DH_size(DH) / DH_compute_key(...)
    std::function<int()> m_fnDhSize;
    std::function<int(void*, void*,
                      void*)> m_fnDhComputeKey;
    // the RAII guards (hex str, secret,
    // the BIGNUM)
    std::function<void*()> m_fnGuardMakeStr;
    std::function<void*()> m_fnGuardMakeDh;
    std::function<void(void*)>
        m_fnGuardRelease;
    // captures for the tests
    int nCastSetKey = 0;
    std::string sSetKeyMaterial;
};

// ===== ORIGINAL FUN_140505bc0 @ 140505bc0
int MsgKeyXchgRecv(void* pConn,
                   const void* pWire,
                   int nWireLen,
                   MsgKeyXchgData& rD);

// the module DH state (DAT_140976588/590)
extern bool g_bXchgDhInit;
extern void* g_pXchgDh;

} // namespace msg
