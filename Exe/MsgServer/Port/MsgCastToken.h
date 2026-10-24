// ============================================================
// MsgServer strict port - unit M14
// ORIGINAL: FUN_140503c00 @ 140503c00
// the CAST key-derivation token builder
// Signature (from the DISASSEMBLY):
//   rcx = this (unused), rdx = out,
//   r8 = the DH shared secret (Ghidra lost
//   the r8 argument)
// The caller: after DH_compute_key ->
//   memset(out, 0, 0x400);
//   len = FUN_140503c00(this, out, secret);
//   if (len == 0x40)
//     CAST_set_key(this+0x18, 0x40, out);
//   else CAST_set_key(this+0x18, dhLen,
//                     secret);
// The LITERAL flow:
//   hex1 = MD5(secret)        [strdup'd]
//   if (strlen(hex1) != 32) free -> 0
//   local = hex1 ++ hex1      (33-byte copy
//                             + byte-walk
//                             strcat, 64+1)
//   hex2 = MD5(local)
//   if (strlen(hex2) != 32) free both -> 0
//   out[0..31] = hex1 (4 qwords, NO nul -
//     the caller pre-zeroed out[0x400])
//   byte-walk out to its nul, strcat hex2
//   return strlen(out) & 0xffffffff
//     (= 64: hex1 ++ hex2)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgCastTokenData {
    // the ORIGINAL calls FUN_140507ca0
    // directly; the seam exists for the
    // error-branch tests (default = the real
    // one). Returns a strdup'd string.
    std::function<char*(const char*)>
        m_fnMd5OfString;
};

// ===== ORIGINAL FUN_140503c00 @ 140503c00
// returns the token length (0 on failure)
uint32_t MsgBuildCastToken(MsgCastTokenData& rD,
                           char* pOut,
                           const char* pSecret);

} // namespace msg
