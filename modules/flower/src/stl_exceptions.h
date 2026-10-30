// ============================================================================
// stl_exceptions.h — RAW Flower.dll v6159
//   The compiler-emitted standard exception classes Flower.dll carries, each
//   reproduced with the original's field layout instead of the host library's
//   ABI.  A logic_error here is: exception base (0x00..0x17), the message
//   string at +0x18 laid out as MSVC basic_string (16 byte SSO buffer or
//   pointer at +0x20, size at +0x30, capacity at +0x38).
//     0x140d93bc0 bad_alloc(char const*)        0x140d93c30 bad_alloc dtor
//     0x140d93c90 empty stub                    0x140d93ca0 logic_error ctor
//     0x140d93d30 logic_error::what             0x140d93d50 logic_error dtor
//     0x140d93db0 length_error ctor             0x140d93e60 length_error dtor
//     0x140d93ed0 out_of_range ctor             0x140d93f80 out_of_range dtor
// ============================================================================
#ifndef FLOWER_STL_EXCEPTIONS_H
#define FLOWER_STL_EXCEPTIONS_H
#include <cstdint>
#include <string>

namespace flower {
namespace stl {

// the MSVC basic_string the original puts at +0x18 of every logic_error
struct MsString {
    union {
        char szSso[16];
        char* pszHeap;
    };
    uint64_t uSize;     // +0x30
    uint64_t uCap;      // +0x38

    void CopyFrom(const std::string& s);   // basic_string copy ctor
    const char* Text() const { return uCap > 0xf ? pszHeap : szSso; }
    void Release();                        // basic_string dtor
};

struct MsLogicError {
    uint32_t uVft;      // +0x00 vftable pointer slot (documented as 8 bytes)
    uint8_t  pad[0x14];
    MsString strText;   // +0x18
};

void BadAllocCtor(void* pSelf, const char* szWhat);          // 0x140d93bc0
void BadAllocDtor(void* pSelf, uint32_t uFlag);              // 0x140d93c30
void EmptyStub();                                            // 0x140d93c90
void LogicErrorCtor(void* pSelf, const std::string* pText);  // 0x140d93ca0
const char* LogicErrorWhat(void* pSelf);                     // 0x140d93d30
void LogicErrorDtor(void* pSelf, uint32_t uFlag);            // 0x140d93d50
void LengthErrorCtor(void* pSelf, const std::string* pText); // 0x140d93db0
void LengthErrorDtor(void* pSelf, uint32_t uFlag);           // 0x140d93e60
void OutOfRangeCtor(void* pSelf, const std::string* pText);  // 0x140d93ed0
void OutOfRangeDtor(void* pSelf, uint32_t uFlag);            // 0x140d93f80

// The binary writes these vftables by symbol name (std::bad_alloc::vftable
// and friends) and the dump carries no numeric address for them, so the port
// reads each one from a seam instead of inventing an address.
extern uintptr_t g_uBadAllocVft;
extern uintptr_t g_uLogicErrorVft;
extern uintptr_t g_uLengthErrorVft;
extern uintptr_t g_uOutOfRangeVft;

}  // namespace stl
}  // namespace flower
#endif
