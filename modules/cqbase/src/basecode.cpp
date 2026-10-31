// CQBase.dll v6159 — basecode.cpp (0x140b82860..0x140b82d30)
#include "modules/cqbase/src/basecode.h"

#include <cstring>
#include <cstdlib>

namespace tq {

// getw — the two byte little endian read behind _getw
int64_t GetWord(FILE* pFile) {
    int lo = fgetc(pFile);
    int hi = fgetc(pFile);
    if ((lo == -1) || (hi == -1)) return -1;
    return (int64_t)(int16_t)((uint16_t)lo | ((uint16_t)hi << 8));
}

static void DefLogError(const char*, const char*, const char*, int) {}
void (*g_pfnLogError)(const char*, const char*, const char*, int) = DefLogError;

void LogError(const char* pszTag, const char* pszExpr, const char* pszFile, int nLine) {
    g_pfnLogError(pszTag, pszExpr, pszFile, nLine);
}

// 0x140b82860 — the tag comes in as the first argument, everything else follows
void LogErrorMessage(const char* pszTag, const char* pszExpr, const char* pszFile, int nLine) {
    g_pfnLogError(pszTag, pszExpr, pszFile, nLine);
}

// 0x140b82970 — reads up to the newline into a zeroed buffer.
// -1 is end of file, -3 the buffer filled, -2 a refused argument. The newline is
// consumed but not stored, and the buffer is always zeroed first.
int64_t ReadLine(FILE* pFile, void* pBuf, int nBufSize) {
    if (((pFile != nullptr) && (pBuf != nullptr)) && (0 < nBufSize)) {
        std::memset(pBuf, 0, (size_t)nBufSize);
        uint64_t uIndex = 0;
        uint64_t uCount = 0;
        int c = fgetc(pFile);
        while (true) {
            if (c == -1) return 0xffffffff;
            if (c == 10) break;
            ((char*)pBuf)[uIndex] = (char)c;
            uIndex = uIndex + 1;
            uCount = (uint64_t)((int)uCount + 1);
            if ((int64_t)nBufSize <= (int64_t)uIndex) return 0xfffffffd;
            c = fgetc(pFile);
        }
        return (int64_t)uCount;
    }
    LogError("IF_NOT", "fp && pszLine && nBufSize > 0",
             "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\basecode.cpp", 0x3c);
    return 0xfffffffe;
}

// 0x140b82a50 — "#define STR_" then the name. The original returns a masked
// register when the line is null, which reads as a refusal; it is written as 0.
int ParseDefineStr(char* pszOut, char* pszLine) {
    if (pszLine == nullptr) {
        LogError("IF_NOT", "pszLine", "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\basecode.cpp", 0x5a);
        return 0;
    }
    char szName[64];
    std::memset(szName, 0, sizeof(szName));
    int nGot = sscanf(pszLine, "#define STR_%s", szName);
    if (nGot == 1) {
        char* pWrite = pszOut;
        const char* pRead = szName;
        char c;
        do {
            c = *pRead++;
            *pWrite++ = c;
        } while (c != '\0');
        return 1;
    }
    return 0;
}

// 0x140b82b30 — the text after the first quote, with the closing quote dropped
// by writing a terminator over the last byte.
int ParseQuotedStr(char* pszOut, char* pszMsg) {
    if ((pszMsg == nullptr) || (pszOut == nullptr)) {
        LogError("IF_NOT", "pszLine && pszMsgOut",
                 "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\basecode.cpp", 0x6f);
        return 0;
    }
    char* pQuote = std::strstr(pszMsg, "\"");
    if (pQuote != nullptr) {
        if (std::strlen(pQuote) != 0) {
            char* pWrite = pszOut;
            const char* pRead = pQuote + 1;
            char c;
            do {
                c = *pRead++;
                *pWrite++ = c;
            } while (c != '\0');
            size_t nLen = std::strlen(pszOut);
            if (nLen != 0) pszOut[nLen - 1] = '\0';
            return 1;
        }
    }
    LogError("IF_NOT", "pszMsg && strlen(pszMsg) > 0",
             "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\basecode.cpp", 0x75);
    return 0;
}

// 0x140b82c30 — seek, read the 16 bit length, then xor the bytes with a sixteen
// byte key indexed by the counter's low nibble. The answer is 1 either way, and
// the caller chains them with an or.
uint8_t DecodeBlob(FILE* pFile, long lOffset, char* pszOut) {
    static const uint8_t kKey[16] = { 0xa4, 0x49, 0x12, 0x11, 0x99, 0x53, 0xf0, 0x5f,
                                      0x32, 0x77, 0xe4, 0x82, 0x2e, 0x6b, 0x10, 0x34 };
    if ((pszOut != nullptr) && (pFile != nullptr)) {
        fseek(pFile, lOffset, 0);
        int nLen = (int)GetWord(pFile);
        uint64_t uIndex = 0;
        int nKey = 0;
        while ((int64_t)uIndex < (int64_t)nLen) {
            int c = getc(pFile);
            uIndex = uIndex + 1;
            int nSlot = nKey;
            nKey = nSlot + 1;
            uint32_t uSlot = (uint32_t)(nSlot & 0xf);
            pszOut[-1 + uIndex] = (char)((uint8_t)c ^ kKey[uSlot]);
        }
        pszOut[nLen] = 0;
    }
    return 1;
}

// 0x140b82d30 — two counts then four blobs at the fixed offsets.
uint8_t LoadDat(char* pszPath, int* pnA, int* pnB, char* pszOne, char* pszTwo,
                char* pszThree, char* pszFour) {
    FILE* pFile = fopen(pszPath, "rb");
    if (pFile != nullptr) {
        *pnA = (int)GetWord(pFile);
        *pnB = (int)GetWord(pFile);
        uint8_t uOne = DecodeBlob(pFile, 0x1b, pszOne);
        uint8_t uTwo = DecodeBlob(pFile, 0x171, pszTwo);
        uint8_t uThree = DecodeBlob(pFile, 0x309, pszThree);
        uint8_t uFour = DecodeBlob(pFile, 0x462, pszFour);
        fclose(pFile);
        return (uint8_t)(uOne | 1 | uTwo | uThree | uFour);
    }
    return 0;
}

// ---- tq::CIni: its vftable and one pointer at +8
CIni::CIni() { pData = nullptr; }

// 0x140b82890 — the copy constructor copies the pointer, nothing else
CIni::CIni(const CIni& rOther) { pData = rOther.pData; }

// 0x140b828b0 — assignment touches +8 only, the vftable stays
CIni& CIni::operator=(const CIni& rOther) {
    pData = rOther.pData;
    return *this;
}

CIni::~CIni() = default;

// 0x140b828c0 — scalar deleting destructor
void* CIniScalarDelete(CIni* pThis, uint32_t uFlags) {
    pThis->~CIni();
    if ((uFlags & 1) != 0) {
        operator delete(pThis);
    }
    return pThis;
}

// 0x140b828f0 — vector deleting destructor: flag 2 walks the elements backwards
// from the count stored eight bytes before the array, then frees that address.
void* CIniVectorDelete(CIni* pThis, uint32_t uFlags) {
    if ((uFlags & 2) != 0) {
        int nCount = *(int*)((char*)pThis - 8);
        for (int i = nCount - 1; i >= 0; --i) {
            pThis[i].~CIni();
        }
        if ((uFlags & 1) != 0) {
            operator delete((char*)pThis - 8);
        }
        return (char*)pThis - 8;
    }
    pThis->~CIni();
    if ((uFlags & 1) != 0) {
        operator delete(pThis);
    }
    return pThis;
}

}  // namespace tq
