#include "MsgMd5Service.h"
#include "MsgMd5.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace msg {

// DAT_140970230: 0x80 then zeros (>= 0x78)
static const uint8_t s_padding[0x78] = {
    0x80, 0, /* ... zeros */ };

void MsgMd5InitCtx(uint8_t* pCtx) {
    *(uint32_t*)(pCtx + 0x00) = 0x67452301;
    *(uint32_t*)(pCtx + 0x04) = 0xefcdab89;
    *(uint32_t*)(pCtx + 0x08) = 0x98badcfe;
    *(uint32_t*)(pCtx + 0x0c) = 0x10325476;
    *(uint32_t*)(pCtx + 0x10) = 0;
    *(uint32_t*)(pCtx + 0x14) = 0;
    // buffer UNINITIALIZED (LITERAL)
}

// ===== ORIGINAL FUN_140507ab0 @ 140507ab0 =====
void MsgMd5Update(uint8_t* pCtx, const void* pData,
                  uint32_t uLen) {
    uint32_t uCntLo = *(uint32_t*)(pCtx + 0x10);
    uint32_t uNewLo = uCntLo + uLen * 8;
    *(uint32_t*)(pCtx + 0x10) = uNewLo;
    uint32_t uIdx = uCntLo >> 3 & 0x3f;
    uint64_t uIdx64 = uIdx;
    if (uNewLo < uLen * 8)
        (*(int32_t*)(pCtx + 0x14)) += 1;
    uint32_t uSpace =
        (uint32_t)(-(int32_t)uIdx) + 0x40;
    (*(int32_t*)(pCtx + 0x14)) +=
        (int32_t)(uLen >> 0x1d);
    uint32_t uOff;
    if (uLen < uSpace) {
        uOff = 0;
    } else {
        std::memcpy(pCtx + 0x18 + uIdx64, pData,
                    uSpace);
        MsgMd5Transform((uint32_t*)pCtx,
                         pCtx + 0x18);
        // the ORIGINAL loop: prev+0x7f < len
        uint32_t uPrev = (uint32_t)(-(int32_t)uIdx);
        uOff = uSpace;
        while (uPrev + 0x7f < uLen) {
            MsgMd5Transform((uint32_t*)pCtx,
                (const uint8_t*)pData + uOff);
            uPrev = uOff;
            uOff += 0x40;
        }
        uIdx64 = 0;
    }
    std::memcpy(pCtx + 0x18 + uIdx64,
                (const uint8_t*)pData + uOff,
                uLen - uOff);
}

// ===== ORIGINAL FUN_140507b80 @ 140507b80 =====
void MsgMd5Finalize(uint8_t* pCtx) {
    // the count qword copy (2 x 4 bytes)
    uint8_t cnt8[8];
    for (int i = 0; i < 8; ++i)
        cnt8[i] = pCtx[0x10 + i];
    int nPad = 0x38;
    uint32_t uIdx =
        *(uint32_t*)(pCtx + 0x10) >> 3 & 0x3f;
    if (0x37 < uIdx) nPad = 0x78;
    MsgMd5Update(pCtx, s_padding,
                 (uint32_t)(nPad - uIdx));
    MsgMd5Update(pCtx, cnt8, 8);
    // digest: 16 bytes ctx+0 -> ctx+0x58
    for (int i = 0; i < 16; ++i)
        pCtx[0x58 + i] = pCtx[i];
    // the zeroize (LITERAL: state, count, buf)
    *(uint32_t*)(pCtx + 0x10) = 0;
    *(uint32_t*)(pCtx + 0x14) = 0;
    *(uint32_t*)(pCtx + 0x00) = 0;
    *(uint32_t*)(pCtx + 0x04) = 0;
    *(uint32_t*)(pCtx + 0x08) = 0;
    *(uint32_t*)(pCtx + 0x0c) = 0;
    for (int i = 0x18; i < 0x58; i += 8)
        *(uint64_t*)(pCtx + i) = 0;
}

// ===== ORIGINAL FUN_1405070a0 @ 1405070a0 =====
char* MsgMd5DigestHex(const uint8_t* pDigest) {
    char hex[0x100];
    char tmp[10];
    std::memset(hex, 0, 0x100);
    for (int i = 0; i < 16; ++i) {
        std::snprintf(tmp, 10, "%02x",
                      pDigest[i]);
        std::strncat(hex, tmp, 10);
    }
    return strdup(hex);
}

// ===== ORIGINAL FUN_140507ca0 @ 140507ca0 =====
char* MsgMd5OfString(const char* sz) {
    uint8_t ctx[MSG_MD5_CTX_SIZE];
    MsgMd5InitCtx(ctx);
    // the LITERAL inline strlen walk:
    // uVar2 = -1, per char decrement, stop at
    // NUL; len = ~uVar2 - 1
    uint64_t u = (uint64_t)-1;
    const char* p = sz;
    for (;;) {
        if (u == 0) break;
        u -= 1;
        char c = *p;
        p += 1;
        if (c == '\0') break;
    }
    uint32_t uLen = (uint32_t)(~u - 1);
    MsgMd5Update(ctx, sz, uLen);
    MsgMd5Finalize(ctx);
    return MsgMd5DigestHex(ctx + 0x58);
}

// ===== ORIGINAL FUN_140507d30 @ 140507d30 =====
char* MsgMd5OfFile(const char* szPath,
                   MsgMd5FileSeams& rS) {
    uint8_t ctx[MSG_MD5_CTX_SIZE];
    MsgMd5InitCtx(ctx);
    uint8_t buf[0x400];
    std::memset(buf, 0, 0x400);
    void* f = nullptr;
    int e = rS.m_fnOpen(szPath, &f, "rb");
    if (e == 0) {
        return nullptr;   // the LITERAL quirk
    }
    for (;;) {
        uint32_t n = rS.m_fnRead(buf, f, 0x400);
        if ((int)n == 0) break;
        MsgMd5Update(ctx, buf, n);
    }
    MsgMd5Finalize(ctx);
    rS.m_fnClose(f);
    return MsgMd5DigestHex(ctx + 0x58);
}

} // namespace msg
