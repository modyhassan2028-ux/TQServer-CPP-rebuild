#ifndef SYNDICATE_CONTAINERACCESSORS_H
#define SYNDICATE_CONTAINERACCESSORS_H
#include <cstdint>

// The container family's trivial accessors, 0x1417c5980..0x1417c5f5a — twenty functions of one to six
// instructions each, from the two files `synrangeB.cpp` and `synleaves.cpp`. They are what `begin()`,
// `_Lmost()`, a member reference and a two-field initializer compile to when everything is inlined away
// except the entry point, which is why each one is a bare `lea` or `mov` and a `ret`.
//
// Three facts in here are worth more than the rest:
//   * the tree sentinel byte sits at +0x29 for one node layout and +0x41 for the other, so the two
//     minimal-element walks are not interchangeable;
//   * `Init16U8` copies sixteen bytes and then exactly one byte to +0x10, not a word;
//   * the two "maximum" constants are 0x0fffffffffffffff and 0x1fffffffffffffff — one hex digit apart,
//     and swapping them would be invisible until something compared against them.
namespace synd {
namespace acc {

void* InitU32U64(void* self, const void* src, const void* tail);   // 0x1417c5980
void* At29(void* self);                                            // 0x1417c59c0
void* At10(void* self);                                            // 0x1417c59e0
void* Field30(void* self);                                         // 0x1417c59f0
void* Field30Plus10(void* self);                                   // 0x1417c5a00
void* At41(void* self);                                            // 0x1417c5a30
void* At21(void* self);                                            // 0x1417c5a90
void* Init16U8(void* self, const void* src, const void* byte);     // 0x1417c5ae0
void* Field08(void* self);                                         // 0x1417c5b00
void* At28(void* self);                                            // 0x1417c5c20
void* At08(void* self);                                            // 0x1417c5c30
void* At18(void* self);                                            // 0x1417c5c40
void* MinNode29(void* self);                                       // 0x1417c5c50
void  DeleteValueThunk(void* self, void* value);                   // 0x1417c5c80, tail call
void* At40(void* self);                                            // 0x1417c5c90
void* At20(void* self);                                            // 0x1417c5cd0
void* Field30Plus8(void* self);                                    // 0x1417c5dd0
void* Init16(void* self, const void* src);                         // 0x1417c5e60
std::uint64_t Limit3F(void);                                       // 0x1417c5ef0
void* MinNode41(void* self);                                       // 0x1417c5f30

// 0x1417f2fdc, the target of the three tail calls in this family.
extern void (*g_pfn1417f2fdc)(void*);

}  // namespace acc
}  // namespace synd
#endif
