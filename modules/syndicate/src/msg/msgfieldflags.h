#ifndef SYNDICATE_MSG_MSGFIELDFLAGS_H
#define SYNDICATE_MSG_MSGFIELDFLAGS_H
#include <cstdint>

// The message base's field-presence setters. Twelve five-to-ten byte functions at
// 0x1417d9840..0x1417d98f7, which is what an inline `set_<field>()` in a header compiles to: set one bit
// in the has-word at +0x30, and optionally store the value.
//
// The bit-to-offset map is fixed by the listing, and the widths are not uniform: +0x38, +0x3c, +0x40 and
// +0x60 take a 32-bit store (`mov %edx`), while +0x44 and +0x45 take a byte (`mov %dl`). Porting those
// two as 32-bit stores would quietly corrupt +0x46.
namespace tq {
namespace msgfield {

void Flag01(void* self);                       // 0x1417d9840
void Flag02(void* self);                       // 0x1417d9860
void Flag04(void* self);                       // 0x1417d9880
void Flag08(void* self);                       // 0x1417d98a0
void Flag10(void* self);                       // 0x1417d98c0
void Flag20(void* self);                       // 0x1417d98e0

void Flag01And38(void* self, int32_t v);       // 0x1417d9850
void Flag02And3C(void* self, int32_t v);       // 0x1417d9870
void Flag04And40(void* self, int32_t v);       // 0x1417d9890
void Flag08And44(void* self, uint8_t v);       // 0x1417d98b0, byte store
void Flag10And45(void* self, uint8_t v);       // 0x1417d98d0, byte store
void Flag20And60(void* self, int32_t v);       // 0x1417d98f0

}  // namespace msgfield
}  // namespace tq
#endif
