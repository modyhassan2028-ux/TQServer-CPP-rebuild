#include "MsgMd5Checksum.h"
#include "MsgMd5.h"
#include <cstring>

namespace msg {

// DAT_1409703a0 (extracted:
// 80 00 00 ... )
const unsigned char g_MsgMd5Pad[64] = {
    0x80, 0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };

// the LITERAL salt:
// += '\xA3' += '\xAC' += '\xA1' +=
// '\xA3' += "eur506,j89jfmncvl"
// NOTE: split literals - the greedy \x
// escape would eat "3e" of "eur506..."
const char* const g_MsgMd5Salt =
    "\xA3" "\xAC" "\xA1" "\xA3"
    "eur506,j89jfmncvl";

// ===== FUN_14050a4a0 @ 14050a4a0
void MsgMd5CsUpdate(MsgMd5CsCtx& rC,
                    const void* p,
                    uint32_t nLen) {
    const unsigned char* pData =
        (const unsigned char*)p;
    uint32_t uIdx = rC.nCountLo;
    uint32_t uNew = uIdx + nLen * 8;
    rC.nCountLo = uNew;
    uIdx = (uIdx >> 3) & 0x3f;
    if (uNew < nLen * 8)
        ++rC.nCountHi;
    rC.nCountHi += nLen >> 0x1d;
    uint32_t uRoom = 0x40 - uIdx;
    uint32_t uOff;
    if (nLen < uRoom) {
        uOff = 0;
    } else {
        std::memcpy(rC.buf + uIdx, pData,
            uRoom);
        uint32_t st[4] = {
            rC.nA, rC.nB, rC.nC, rC.nD };
        MsgMd5Transform(st, rC.buf);
        rC.nA = st[0]; rC.nB = st[1];
        rC.nC = st[2]; rC.nD = st[3];
        uOff = uRoom;
        // VERBATIM loop: the decompile
        // advances uVar1 = uVar4 each
        // iteration, so the condition
        // is (prevOff + 0x7f < len)
        uint32_t uPrev = uIdx;
        while (uPrev + 0x7f < nLen) {
            uint32_t st2[4] = {
                rC.nA, rC.nB, rC.nC,
                rC.nD };
            MsgMd5Transform(st2,
                pData + uOff);
            rC.nA = st2[0];
            rC.nB = st2[1];
            rC.nC = st2[2];
            rC.nD = st2[3];
            uPrev = uOff;
            uOff += 0x40;
        }
    }
    // VERBATIM: the no-spill path keeps
    // writing at buf+idx; the spill path
    // resets the index to 0
    uint32_t uDst = (uOff == 0)
        ? uIdx : 0;
    std::memcpy(rC.buf + uDst,
        pData + uOff, nLen - uOff);
}

// ===== FUN_14050a5d0 @ 14050a5d0
void MsgMd5CsFinalize(MsgMd5CsCtx& rC,
                      std::string& rOut) {
    // save the 8-byte LE bit count
    // (from ctx+0x48)
    unsigned char nCount[8];
    std::memcpy(nCount, &rC.nCountLo, 4);
    std::memcpy(nCount + 4, &rC.nCountHi,
        4);
    // the padding length
    uint32_t uIdx =
        (rC.nCountLo >> 3) & 0x3f;
    uint32_t nPad = (uIdx < 0x38)
        ? (0x38 - uIdx)
        : (0x78 - uIdx);
    MsgMd5CsUpdate(rC, g_MsgMd5Pad,
        nPad);
    MsgMd5CsUpdate(rC, nCount, 8);
    // the digest: A,B,C,D LE
    unsigned char digest[16];
    std::memcpy(digest, &rC.nA, 4);
    std::memcpy(digest + 4, &rC.nB, 4);
    std::memcpy(digest + 8, &rC.nC, 4);
    std::memcpy(digest + 12, &rC.nD, 4);
    // the 32-char lowercase hex
    char tmp[8];
    rOut.clear();
    for (int i = 0; i < 0x10; ++i) {
        unsigned char b = digest[i];
        if (b == 0) {
            rOut += "00";
        } else if (b < 0x10) {
            std::sprintf(tmp, "0%x",
                (unsigned)b);
            rOut += tmp;
        } else {
            std::sprintf(tmp, "%x",
                (unsigned)b);
            rOut += tmp;
        }
    }
}

// ===== FUN_14050a910 @ 14050a910
void MsgMd5CsGetCheckSum(
    std::string& rOut, const char* pIn) {
    // the local ctx, initialized like
    // the ctor (14050a570)
    MsgMd5CsCtx c;
    std::memset(&c, 0, sizeof(c));
    c.nA = 0x67452301;
    c.nB = 0xefcdab89;
    c.nC = 0x98badcfe;
    c.nD = 0x10325476;
    // input + the literal salt
    std::string s(pIn);
    s += (char)0xA3;
    s += (char)0xAC;
    s += (char)0xA1;
    s += (char)0xA3;
    s += "eur506,j89jfmncvl";
    MsgMd5CsUpdate(c, s.data(),
        (uint32_t)s.size());
    MsgMd5CsFinalize(c, rOut);
}

// ===== FUN_14050aa70 @ 14050aa70
uint64_t MsgMd5CsVt8InPlace(void* pObj,
                            char* pBuf) {
    (void)pObj;
    std::string r;
    MsgMd5CsGetCheckSum(r, pBuf);
    // the VERBATIM copy loop (until
    // the NUL)
    const char* q = r.c_str();
    char c;
    do {
        c = *q++;
        *pBuf++ = c;
    } while (c != '\0');
    return 0;
}

// ===== FUN_14050a7f0 @ 14050a7f0
uint64_t MsgMd5StdVt8InPlace(void* pObj,
                             char* pBuf) {
    (void)pObj;
    MsgMd5CsCtx c;
    std::memset(&c, 0, sizeof(c));
    c.nA = 0x67452301;
    c.nB = 0xefcdab89;
    c.nC = 0x98badcfe;
    c.nD = 0x10325476;
    // NO salt - the raw input only
    MsgMd5CsUpdate(c, pBuf,
        (uint32_t)std::strlen(pBuf));
    std::string r;
    MsgMd5CsFinalize(c, r);
    const char* q = r.c_str();
    char ch;
    do {
        ch = *q++;
        *pBuf++ = ch;
    } while (ch != '\0');
    return 0;
}

} // namespace msg
