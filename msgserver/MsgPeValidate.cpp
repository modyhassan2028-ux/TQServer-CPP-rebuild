#include "MsgPeValidate.h"
#include <cstring>

namespace msg {

static inline int AlignUp(int v, int align) {
    return ((v + align - 1) / align) * align;
}

// ===== FUN_140509760 @ 140509760
int MsgPeValidate(MsgPeDesc& rD,
                  void* pFile,
                  uint32_t nSize) {
    if (nSize < 0x40)
        return 0;
    unsigned char* p =
        (unsigned char*)pFile;
    if (*(uint16_t*)p != 0x5a4d)
        return 0;
    int nLfanew = *(int*)(p + 0x3c);   // short*+0x1e = byte 0x3c
    if ((uint32_t)nLfanew + 0x108U
        > nSize)
        return 0;
    unsigned char* pNt =
        p + (uint32_t)nLfanew;
    rD.pFile = pFile;          // +0x18
    rD.pNt = pNt;              // +0x20
    if (*(uint32_t*)pNt != 0x4550)
        return 0;
    uint16_t uChars =
        *(uint16_t*)(pNt + 0x16);
    if ((uChars & 0x2000) == 0)
        return 0;
    if ((uChars & 2) == 0)
        return 0;
    if (*(uint16_t*)(pNt + 0x14)
        != 0xf0)
        return 0;
    unsigned char* pSec =
        pNt + 0x108;
    rD.pSections = pSec;       // +0x28
    int i = 0;
    if (*(uint16_t*)(pNt + 6) != 0) {
        // NOTE: the section count is
        // re-read from the desc on
        // every iteration (literal)
        do {
            // sec+0x10 = SizeOfRawData,
            // sec+0x14 = PointerToRawData
            int* pS = (int*)(pSec
                + (size_t)i * 0x28 + 0x10);
            if (nSize <
                (uint32_t)(pS[1] + pS[0]))
                return 0;
            ++i;
        } while (i < (int)(uint32_t)*(
            (uint16_t*)((char*)rD.pNt
                + 6)));
    }
    return 1;
}

// ===== FUN_140509820 @ 140509820
int MsgPeImageSize(MsgPeDesc& rD) {
    if (rD.pNt == nullptr)
        return 0;
    unsigned char* pNt =
        (unsigned char*)rD.pNt;
    int nAlign = *(int*)(pNt + 0x38);
    int nTotal = AlignUp(
        *(int*)(pNt + 0x54), nAlign);
    uint16_t nSecs =
        *(uint16_t*)(pNt + 6);
    if (nSecs != 0) {
        unsigned char* pSec =
            (unsigned char*)rD.pSections;
        for (uint16_t s = 0;
                 s < nSecs; ++s) {
            unsigned char* pS = pSec
                + (size_t)s * 0x28;
            int vSize =
                *(int*)(pS + 0x8);
            int rSize =
                *(int*)(pS + 0x10);
            int nMax = vSize;
            if (vSize < rSize)
                nMax = rSize;
            int nEnd = AlignUp(nMax +
                *(int*)(pS + 0xc),
                nAlign);
            if (nTotal < nEnd)
                nTotal = nEnd;
        }
    }
    return nTotal;
}

} // namespace msg
