// ============================================================================
// basecode.h — RAW CQBase.dll v6159 · basecode.cpp
//   the line reader, the two line parsers, the xor blob decoder that reads the
//   .dat tables, and the tq::CIni wrapper. The log calls in these bodies name
//   modules\cqbase\src\basecode.cpp, which is how they are placed here.
// ============================================================================
#ifndef CQBASE_BASECODE_H
#define CQBASE_BASECODE_H

#include <cstdint>
#include <cstdio>

namespace tq {

// the seam the bodies call for a refused argument (log_InlineLogERROR)
extern void (*g_pfnLogError)(const char* pszTag, const char* pszExpr, const char* pszFile, int nLine);
void LogError(const char* pszTag, const char* pszExpr, const char* pszFile, int nLine);

// 0x140b82860 — the five line wrapper that hands its tag straight to the log
void LogErrorMessage(const char* pszTag, const char* pszExpr, const char* pszFile, int nLine);

// 0x140b82970 — one line without its 0x0a
int64_t ReadLine(FILE* pFile, void* pBuf, int nBufSize);

// 0x140b82a50 — "#define STR_xxx" into the caller's buffer
int ParseDefineStr(char* pszOut, char* pszLine);

// 0x140b82b30 — the text inside the first pair of quotes
int ParseQuotedStr(char* pszOut, char* pszMsg);

// getw: the two byte little endian read the blob headers use
int64_t GetWord(FILE* pFile);

// 0x140b82c30 — a length prefixed, xor decoded blob at an offset
uint8_t DecodeBlob(FILE* pFile, long lOffset, char* pszOut);

// 0x140b82d30 — the four blob table
uint8_t LoadDat(char* pszPath, int* pnA, int* pnB, char* pszOne, char* pszTwo,
                char* pszThree, char* pszFour);

// 0x140b82890 — tq::CIni is its vftable and one pointer at +8, sixteen bytes.
// The vftable store the decompiler shows is the compiler's own vptr write, so
// the virtual destructor alone gives the port that slot.
class CIni {
public:
    CIni();
    CIni(const CIni& rOther);            // 0x140b82890
    CIni& operator=(const CIni& rOther); // 0x140b828b0
    virtual ~CIni();
    void* pData;                         // +8
};
void* CIniScalarDelete(CIni* pThis, uint32_t uFlags);   // 0x140b828c0
void* CIniVectorDelete(CIni* pThis, uint32_t uFlags);   // 0x140b828f0

}  // namespace tq
#endif
