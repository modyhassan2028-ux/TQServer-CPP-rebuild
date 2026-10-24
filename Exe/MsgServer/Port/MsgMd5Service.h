// ============================================================
// MsgServer strict port - unit M13
// ORIGINAL: the MD5 service around the core
//  FUN_140507ab0 - MD5Update (ctx, data, len)
//  FUN_140507b80 - MD5Finalize (digest lands
//                  INSIDE the ctx at +0x58)
//  FUN_1405070a0 - digest -> "%02x" hex,
//                  strdup'd (caller frees)
//  FUN_140507ca0 - one-shot string hash
//  FUN_140507d30 - one-shot FILE hash
// The ctx layout (0x68 bytes):
//  +0x00 state[4]     +0x10 count[2]
//  +0x18 buf[64]       +0x58 digest[16]
// LITERAL quirks kept:
//  - Update's bit count: count_lo += len*8
//    with the carry check `if (newLo < len*8)
//    ++count_hi` and `count_hi += len >> 29`
//  - Finalize pads from DAT_140970230 (the
//    0x80,0,... table): 56 - idx, or 120 - idx
//    when idx > 0x37, then the 8 count bytes
//  - Finalize ZEROES state+count+buf after
//    copying the digest to +0x58
//  - the file hash checks `if (fopen_s(...)==0)
//    return NULL` - on the LITERAL binary this
//    returns NULL when fopen_s SUCCEEDS (kept
//    verbatim; presumably TQ's fopen_s wrapper
//    returns nonzero on success)
//  - the string hash's strlen is the inline
//    byte walk (uVar2 = -1 ... ~uVar2 - 1)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

constexpr uint32_t MSG_MD5_CTX_SIZE = 0x68;

// inline init (the ORIGINALs init the state
// fields inline; buffer left UNINITIALIZED)
void MsgMd5InitCtx(uint8_t* pCtx);

// ===== ORIGINAL FUN_140507ab0 @ 140507ab0 =====
void MsgMd5Update(uint8_t* pCtx, const void* pData,
                  uint32_t uLen);

// ===== ORIGINAL FUN_140507b80 @ 140507b80 =====
void MsgMd5Finalize(uint8_t* pCtx);

// ===== ORIGINAL FUN_1405070a0 @ 1405070a0 =====
// digest -> 32-char lowercase hex, strdup'd
char* MsgMd5DigestHex(const uint8_t* pDigest);

// ===== ORIGINAL FUN_140507ca0 @ 140507ca0 =====
char* MsgMd5OfString(const char* sz);

// the FILE seams (FUN_140507d30)
struct MsgMd5FileSeams {
    // fopen_s(&f, path, "rb") -> the errno_t
    std::function<int(const char*, void**,
                      const char*)> m_fnOpen;
    // fread(buf, 1, 0x400, f) -> bytes
    std::function<uint32_t(void*, void*,
                           uint32_t)> m_fnRead;
    std::function<void(void*)> m_fnClose;
};

// ===== ORIGINAL FUN_140507d30 @ 140507d30 =====
// returns a strdup'd hex or NULL (see quirk)
char* MsgMd5OfFile(const char* szPath,
                   MsgMd5FileSeams& rS);

} // namespace msg
