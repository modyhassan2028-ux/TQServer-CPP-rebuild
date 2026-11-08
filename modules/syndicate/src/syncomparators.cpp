#include "modules/syndicate/src/syncomparators.h"
#include <cstring>

namespace synd {

namespace {
// The record's word fields are read at the offsets the listing uses, which for +0x27 is not aligned.
inline std::uint32_t LoadU32(const void* p) { std::uint32_t v; std::memcpy(&v, p, 4); return v; }
inline std::int32_t LoadI32(const void* p) { std::int32_t v; std::memcpy(&v, p, 4); return v; }
inline std::uint8_t LoadU8(const void* p) { return *static_cast<const std::uint8_t*>(p); }
}

bool Key8GreaterEqual(const void* a, const void* b) {                        // 141780100
    const std::int32_t ka = LoadI32(static_cast<const std::uint8_t*>(a) + 0x8);   // mov 0x8(%rcx)
    const std::int32_t kb = LoadI32(static_cast<const std::uint8_t*>(b) + 0x8);   // mov 0x8(%rdx)
    return ka >= kb;                                                          // cmp %edx,0x8(%rcx) / setge
}

void NoOp4(std::int32_t a, void* b, std::int32_t c, void* d) {                // 1417e0830
    (void)a; (void)b; (void)c; (void)d;   // the body is four stores into its own home space and a ret
}

bool KeyLess3(const void* a, const void* b) {                                 // 14174e3a0
    const std::uint8_t* pa = static_cast<const std::uint8_t*>(a);
    const std::uint8_t* pb = static_cast<const std::uint8_t*>(b);
    const std::uint32_t a0 = LoadU32(pa);                                     // mov (%rcx),%r8d
    if (a0 == 0) return true;                                                 // test %r8d,%r8d / je -> mov $1,%al
    const std::uint32_t b0 = LoadU32(pb);                                     // mov (%rdx),%ecx
    if (b0 == 0) return false;                                                // test %ecx,%ecx / je -> xor %al,%al
    const std::uint32_t a8 = LoadU32(pa + 0x8);                               // mov 0x8(%rax),%r9d
    const std::uint32_t b8 = LoadU32(pb + 0x8);                               // mov 0x8(%rdx),%r10d
    if (a8 != b8) return a8 > b8;                                             // cmp / setg — descending
    const std::uint32_t a4 = LoadU32(pa + 0x4);                               // mov 0x4(%rax),%r9d
    const std::uint32_t b4 = LoadU32(pb + 0x4);                               // mov 0x4(%rdx),%r10d
    if (a4 != b4) return a4 < b4;                                             // cmp / setb — ascending
    return a0 < b0;                                                           // cmp %ecx,%r8d / setb
}

bool FlagThenKeyLess(const void* a, const void* b) {                          // 1417b0920
    const std::uint8_t* pa = static_cast<const std::uint8_t*>(a);
    const std::uint8_t* pb = static_cast<const std::uint8_t*>(b);
    const std::uint8_t fa = LoadU8(pa + 0xE);                                 // movzbl 0xe(%rcx)
    if (fa != 0) {
        if (LoadU8(pb + 0xE) == 0) return true;                               // cmpb $0x0,0xe(%rdx) / jne -> mov $1,%al
    } else {
        if (LoadU8(pb + 0xE) != 0) return false;                              // je -> xor %al,%al
    }
    return LoadU32(pa + 0x27) < LoadU32(pb + 0x27);                           // cmp %ecx,0x27(%r8) / setb
}

}  // namespace synd
