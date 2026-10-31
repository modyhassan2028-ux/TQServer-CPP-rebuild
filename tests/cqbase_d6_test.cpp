// D6 (CQBase) — basecode.cpp: the line reader, the parsers, the blob table, CIni
#include "modules/cqbase/src/basecode.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <new>

using namespace tq;

static const char* kFile = "/tmp/cqbase_d6.bin";

static FILE* MakeFile(const void* pData, size_t nSize) {
    FILE* f = fopen(kFile, "wb");
    if (nSize) fwrite(pData, 1, nSize, f);
    fclose(f);
    return fopen(kFile, "rb");
}

int main() {
    // ---------------- ReadLine: the answers are the 32 bit values the original
    // puts in rax, 0xFFFFFFFF for end of file, 0xFFFFFFFD for a full buffer and
    // 0xFFFFFFFE for a refused argument, never the negative shapes of those
    FILE* f = MakeFile("ab\ncd", 5);
    char szBuf[16];
    assert(ReadLine(f, szBuf, 16) == 2);
    assert(std::strcmp(szBuf, "ab") == 0);
    // a last line without its newline reports end of file while still filling
    // the buffer, because the loop tests the character before it tests the break
    assert(ReadLine(f, szBuf, 16) == 0xffffffff);
    assert(std::strcmp(szBuf, "cd") == 0);
    assert(ReadLine(f, szBuf, 16) == 0xffffffff);
    fclose(f);
    f = MakeFile("abcdefgh\n", 9);
    assert(ReadLine(f, szBuf, 4) == 0xfffffffd);    // the buffer filled
    assert(std::strcmp(szBuf, "abcd") == 0);
    fclose(f);
    assert(ReadLine(nullptr, szBuf, 16) == 0xfffffffe);
    assert(ReadLine(f, nullptr, 16) == 0xfffffffe);
    f = MakeFile("x\n", 2);
    assert(ReadLine(f, szBuf, 0) == 0xfffffffe);
    fclose(f);

    // ---------------- ParseDefineStr
    char szOut[128];
    std::memset(szOut, 0, sizeof(szOut));
    assert(ParseDefineStr(szOut, (char*)"#define STR_HERO_NAME") == 1);
    assert(std::strcmp(szOut, "HERO_NAME") == 0);
    assert(ParseDefineStr(szOut, (char*)"#define OTHER_THING") == 0);
    assert(ParseDefineStr(szOut, (char*)"nothing here") == 0);
    assert(ParseDefineStr(szOut, nullptr) == 0);

    // ---------------- ParseQuotedStr
    std::memset(szOut, 0, sizeof(szOut));
    assert(ParseQuotedStr(szOut, (char*)"GREET \"Hello\"") == 1);
    assert(std::strcmp(szOut, "Hello") == 0);
    assert(ParseQuotedStr(szOut, (char*)"no quotes at all") == 0);
    assert(ParseQuotedStr(szOut, nullptr) == 0);
    assert(ParseQuotedStr(nullptr, (char*)"\"x\"") == 0);
    // the closing quote is dropped by writing over the last byte, so text that
    // follows the closing quote keeps everything but its final character
    std::memset(szOut, 0, sizeof(szOut));
    assert(ParseQuotedStr(szOut, (char*)"A \"x\" B") == 1);
    assert(std::strcmp(szOut, "x\" ") == 0);

    // ---------------- DecodeBlob and LoadDat
    unsigned char aby[0x500];
    std::memset(aby, 0, sizeof(aby));
    const unsigned char kKey[16] = { 0xa4, 0x49, 0x12, 0x11, 0x99, 0x53, 0xf0, 0x5f,
                                     0x32, 0x77, 0xe4, 0x82, 0x2e, 0x6b, 0x10, 0x34 };
    const char* pszOne = "AAA";
    const char* pszTwo = "BBBB";
    const char* pszThree = "CC";
    const char* pszFour = "DDDDD";
    struct { long lOff; const char* psz; } aBlob[4] = { { 0x1b, pszOne }, { 0x171, pszTwo },
                                                        { 0x309, pszThree }, { 0x462, pszFour } };
    for (int b = 0; b < 4; ++b) {
        long off = aBlob[b].lOff;
        int nLen = (int)std::strlen(aBlob[b].psz);
        aby[off] = (unsigned char)(nLen & 0xff);
        aby[off + 1] = (unsigned char)((nLen >> 8) & 0xff);
        for (int i = 0; i < nLen; ++i) {
            aby[off + 2 + i] = (unsigned char)(aBlob[b].psz[i] ^ kKey[i & 0xf]);
        }
    }
    aby[0] = 7; aby[1] = 0; aby[2] = 9; aby[3] = 0;      // the two counts
    f = MakeFile(aby, sizeof(aby));
    char szBlob[64];
    std::memset(szBlob, 0, sizeof(szBlob));
    assert(DecodeBlob(f, 0x1b, szBlob) == 1);            // it answers one always
    assert(std::strcmp(szBlob, "AAA") == 0);
    fclose(f);
    assert(DecodeBlob(nullptr, 0x1b, szBlob) == 1);
    f = MakeFile(aby, sizeof(aby));
    int nA = 0, nB = 0;
    char szOne[64], szTwo[64], szThree[64], szFour[64];
    std::memset(szOne, 0, 64); std::memset(szTwo, 0, 64);
    std::memset(szThree, 0, 64); std::memset(szFour, 0, 64);
    assert(LoadDat((char*)kFile, &nA, &nB, szOne, szTwo, szThree, szFour) == 1);
    assert(nA == 7 && nB == 9);
    assert(std::strcmp(szOne, "AAA") == 0);
    assert(std::strcmp(szTwo, "BBBB") == 0);
    assert(std::strcmp(szThree, "CC") == 0);
    assert(std::strcmp(szFour, "DDDDD") == 0);
    assert(LoadDat((char*)"/tmp/cqbase_d6_missing.bin", &nA, &nB, szOne, szTwo, szThree,
                   szFour) == 0);
    fclose(f);

    // ---------------- tq::CIni
    static_assert(sizeof(CIni) == 16, "the original is a vftable and one pointer");
    CIni aIni;
    int nPayload = 5;
    aIni.pData = &nPayload;
    CIni bIni(aIni);
    assert(bIni.pData == &nPayload);
    CIni cIni;
    cIni = bIni;
    assert(cIni.pData == &nPayload);                     // assignment copies +8
    CIniScalarDelete(new CIni(aIni), 1);
    // the vector form reads its count from the eight bytes before the array
    int nCount = 3;
    char* pRaw = (char*)operator new(8 + (size_t)nCount * sizeof(CIni));
    std::memset(pRaw, 0, 8);
    std::memcpy(pRaw, &nCount, sizeof(nCount));   // the count is a four byte int
    CIni* pArr = (CIni*)(pRaw + 8);
    for (int i = 0; i < nCount; ++i) { new (&pArr[i]) CIni(aIni); }
    assert(CIniVectorDelete(pArr, 2 | 1) == (void*)pRaw);

    std::remove(kFile);
    printf("CQBASE_D6_OK: ReadLine, ParseDefineStr, ParseQuotedStr, DecodeBlob, LoadDat, CIni\n");
    return 0;
}
