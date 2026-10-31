// ============================================================================
// cstrpacker.h — RAW CQBase.dll v6159 · tq::CStringPacker
//   0x140bb0b00..0x140bb0d90. A buffer of counted strings:
//     [0]  how many strings it holds (a byte)
//     then for each string a length byte followed by that many characters
//     +0x00 vftable   +0x08 char*   +0x10 buffer size
//   A null SetBuf target is not checked anywhere: AddString only guards the
//   pointer being null, and GetSize reads through it regardless.
// ============================================================================
#ifndef CQBASE_STR_CSTRPACKER_H
#define CQBASE_STR_CSTRPACKER_H

#include <cstdint>

namespace tq {
class CStringPacker {
public:
    void** pVft;            // +0x00
    char* pBuf;             // +0x08
    uint32_t nBufSize;      // +0x10

    CStringPacker();                                  // 0x140bb0b40
    CStringPacker(const CStringPacker& r);             // 0x140bb0b00
    virtual ~CStringPacker();                          // 0x140bb0b60
    CStringPacker& operator=(const CStringPacker& r);  // 0x140bb0b20

    void SetBuf(char* pBuf, uint32_t nSize, bool bClear);  // 0x140bb0b70
    uint32_t GetStrAmount();                               // 0x140bb0ba0
    uint32_t GetSize();                                    // 0x140bb0bb0
    bool AddString(const char* psz);                       // 0x140bb0ca0
    bool GetString(uint32_t nIndex, char* pOut, uint32_t nOutSize);  // 0x140bb0d90
};

extern void* g_pVftCStringPacker;
}  // namespace tq
#endif
