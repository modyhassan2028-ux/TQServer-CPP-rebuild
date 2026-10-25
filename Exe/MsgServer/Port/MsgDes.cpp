#include "MsgDes.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace msg {

// ===== the .data tables extracted
// VERBATIM (DAT_140970660/680/3e0/
// 418/428/460). NOTE: the S-boxes
// are a CUSTOM DES VARIANT (S1 rows
// 2/3 differ from RFC - vendor
// obfuscation); PC-1/PC-2/P/the
// cumulative shifts are standard.
static const uint8_t kP[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};
// DAT_140970680 (the int8 view):
// MSB-first byte masks
static const uint8_t kMask[8] = {
    128, 64, 32, 16, 8, 4, 2, 1};
static const uint8_t kPc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};
// DAT_140970418: the CUMULATIVE
// shifts (VERBATIM)
static const uint8_t kCum[16] = {
    1, 2, 4, 6, 8, 10, 12, 14,
    15, 17, 19, 21, 23, 25, 27, 28};
static const uint8_t kPc2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};
// DAT_140970460: the 8 S-boxes
// (the custom variant)
static const int8_t kS[512] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

static inline uint32_t bswap32(
    uint32_t x) {
    return ((x & 0xff) << 24) |
           ((x & 0xff00) << 8) |
           ((x >> 8) & 0xff00) |
           (x >> 24);
}

void MsgDesCtx::BuildSp(MsgDesCtx& r) {
    // local_38: the inverse P map
    uint8_t aInvP[32];
    for (int j = 0; j < 32; ++j) {
        aInvP[j] = 0;
        for (int i = 0; i < 32; ++i) {
            if ((int)(int8_t)kP[i] -
                    1 == j) {
                aInvP[j] =
                    (uint8_t)i;
                break;
            }
        }
    }
    for (int b = 0; b < 8; ++b) {
        for (uint32_t idx = 0;
             idx < 0x40; ++idx) {
            uint32_t rc =
                (idx & 0x20) |
                ((idx & 1) << 4) |
                ((idx >> 1) & 0xf);
            uint32_t v = 0;
            for (int bit = 0;
                 bit < 4; ++bit) {
                if ((kS[b * 64 +
                         rc] &
                     (int8_t)(8 >>
                              bit)) !=
                    0) {
                    v |= 1u <<
                        (0x1f -
                         (aInvP
                              [b * 4 +
                               bit] &
                          0x1f));
                }
            }
            r.aSp[b][idx] = v;
        }
    }
}

void MsgDesCtx::SetKey(
    MsgDesCtx& r, const uint8_t* pKey) {
    // VERBATIM: the srand/time32
    // prologue with the results
    // UNUSED (CRT artifacts)
    std::srand(
        (unsigned)std::time(
            nullptr));
    r.nMode = 0;
    BuildSp(r);
    if (r.nMode == 2) {
        SetKeyRaw(r, pKey);
        return;
    }
    // the standard schedule
    uint8_t bits[112];
    for (int i = 0; i < 56; ++i) {
        int pc = kPc1[i];
        bits[i] =
            (kMask[(pc - 1) & 7] &
             pKey[(pc - 1) >> 3])
                ? 1
                : 0;
    }
    for (int rd = 0; rd < 16; ++rd) {
        int sh = kCum[rd];
        // the VERBATIM rotation with
        // the i >= 0x1c -> i -= 0x1c
        // idiom (a 28-bit rotate)
        for (int j = 0; j < 0x38;
             ++j) {
            int iv = sh + j;
            if (iv >= 0x1c)
                iv -= 0x1c;
            bits[0x38 + j] = bits[iv];
        }
        // the PC-2 packing: 6
        // bits/byte in the low 6,
        // MSB-first (mask>>2)
        for (uint32_t u = 0;
             u < 0x30; ++u) {
            if (bits[kPc2[u] +
                     0x37]) {
                r.aKs[rd][u / 6] |=
                    (uint8_t)(kMask
                                  [u % 6] >>
                              2);
            }
        }
    }
}

void MsgDesCtx::SetKeyRaw(
    MsgDesCtx& r, const uint8_t* pS) {
    // the flag==2 path: the
    // "key" IS the raw 128-byte
    // schedule
    std::memcpy(r.aKs, pS, 0x80);
}

uint32_t MsgDesCtx::RoundF(
    const MsgDesCtx& r, uint32_t h,
    const uint8_t* pKs) {
    uint32_t rol =
        (h << 1) | (h >> 31);
    uint32_t ror = (h >> 1) |
                   ((h & 1) << 31);
    return r.aSp[7][(rol ^ pKs[7]) &
                    0x3f] |
           r.aSp[6][(ror >> 2 ^
                     pKs[6]) &
                    0x3f] |
           r.aSp[0][(ror >> 0x1a ^
                     pKs[0]) &
                    0x3f] |
           r.aSp[1][(ror >> 0x16 ^
                     pKs[1]) &
                    0x3f] |
           r.aSp[2][(ror >> 0x12 ^
                     pKs[2]) &
                    0x3f] |
           r.aSp[3][(ror >> 0xe ^
                     pKs[3]) &
                    0x3f] |
           r.aSp[4][(ror >> 10 ^
                     pKs[4]) &
                    0x3f] |
           r.aSp[5][(ror >> 6 ^
                     pKs[5]) &
                    0x3f];
}

void MsgDesCtx::EncryptBlock(
    MsgDesCtx& r, uint8_t* pBlock) {
    // the block loads as ONE
    // 64-bit LE word; the halves
    // are the BE32 reads (the
    // descore IP-by-load trick)
    uint32_t l = bswap32(
        *(const uint32_t*)pBlock);
    uint32_t rr = bswap32(
        *(const uint32_t*)(pBlock +
                           4));
    for (int i = 0; i < 16; ++i) {
        if ((i & 1) == 0)
            l ^= RoundF(r, rr,
                        r.aKs[i]);
        else
            rr ^= RoundF(r, l,
                         r.aKs[i]);
    }
    // the writeback: BE32(rr') ||
    // BE32(l') (the implicit final
    // swap)
    *(uint32_t*)pBlock =
        bswap32(rr);
    *(uint32_t*)(pBlock + 4) =
        bswap32(l);
}

void MsgDesCtx::DecryptBlock(
    MsgDesCtx& r, uint8_t* pBlock) {
    uint32_t l = bswap32(
        *(const uint32_t*)pBlock);
    uint32_t rr = bswap32(
        *(const uint32_t*)(pBlock +
                           4));
    // the rounds 15..0 with the
    // OPPOSITE operand parity (the
    // roles are swapped by the wire:
    // the ct's first half is the
    // encrypt's rr')
    for (int i = 15; i >= 0; --i) {
        if ((i & 1) == 0)
            rr ^= RoundF(r, l,
                         r.aKs[i]);
        else
            l ^= RoundF(r, rr,
                        r.aKs[i]);
    }
    *(uint32_t*)pBlock =
        bswap32(rr);
    *(uint32_t*)(pBlock + 4) =
        bswap32(l);
}

uint32_t MsgDesCtx::Encrypt(
    MsgDesCtx& r, uint8_t* p,
    uint32_t nLen) {
    // FUN_14050b340 VERBATIM
    if ((int)nLen < 1)
        return nLen;
    uint32_t nRem = nLen;
    uint8_t* pCur = p;
    size_t nSize =
        (size_t)(int)(8 - (int)nLen);
    uint64_t nTail =
        (uint64_t)nLen;
    for (;;) {
        if ((int)nRem < 8) {
            // pad the tail to the
            // block boundary
            std::memset(
                p + nTail, 0,
                nSize);
        }
        EncryptBlock(r, pCur);
        uint32_t nNext =
            nRem - 8;
        pCur += 8;
        nSize += 8;
        nRem = nNext;
        if (!((int)nNext > 0))
            break;
    }
    return (uint32_t)(pCur - p);
}

int MsgDesCtx::Decrypt(
    MsgDesCtx& r, uint8_t* p,
    int nLen) {
    // FUN_14050b3e0 VERBATIM: NO
    // length guard - a non-multiple
    // runs over the buffer
    for (int n = nLen; n != 0;
         n -= 8) {
        DecryptBlock(r, p);
        p += 8;
    }
    return nLen;
}

void MsgDesCtx::Destroy(
    MsgDesCtx& r) {
    r.bDeleted = true;
}

} // namespace msg
