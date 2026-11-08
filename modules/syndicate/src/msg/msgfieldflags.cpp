// The twelve field-presence setters of the message base, 0x1417d9840..0x1417d98f7. Each is the same two
// instructions: or a bit into the has-word at +0x30, then (for half of them) store the value. The
// listing writes them in pairs, set-only then set-and-store, with the flag doubling each pair.
#include "modules/syndicate/src/msg/msgfieldflags.h"

namespace tq {
namespace msgfield {

void Flag01(void* self) {                                  // 1417d9840 orl $0x1,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x1u;            // 1417d9840
}
void Flag02(void* self) {                                  // 1417d9860 orl $0x2,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x2u;            // 1417d9860
}
void Flag04(void* self) {                                  // 1417d9880 orl $0x4,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x4u;            // 1417d9880
}
void Flag08(void* self) {                                  // 1417d98a0 orl $0x8,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x8u;            // 1417d98a0
}
void Flag10(void* self) {                                  // 1417d98c0 orl $0x10,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x10u;           // 1417d98c0
}
void Flag20(void* self) {                                  // 1417d98e0 orl $0x20,0x30(%rcx)
    *static_cast<std::uint32_t*>(self) |= 0x20u;           // 1417d98e0
}

void Flag01And38(void* self, int32_t v) {                  // 1417d9850
    *static_cast<std::uint32_t*>(self) |= 0x1u;            // 1417d9850 orl $0x1,0x30(%rcx)
    *reinterpret_cast<std::int32_t*>(static_cast<std::uint8_t*>(self) + 0x38) = v;   // 1417d9854 mov %edx,0x38
}
void Flag02And3C(void* self, int32_t v) {                  // 1417d9870
    *static_cast<std::uint32_t*>(self) |= 0x2u;            // 1417d9870 orl $0x2,0x30(%rcx)
    *reinterpret_cast<std::int32_t*>(static_cast<std::uint8_t*>(self) + 0x3C) = v;   // 1417d9874 mov %edx,0x3c
}
void Flag04And40(void* self, int32_t v) {                  // 1417d9890
    *static_cast<std::uint32_t*>(self) |= 0x4u;            // 1417d9890 orl $0x4,0x30(%rcx)
    *reinterpret_cast<std::int32_t*>(static_cast<std::uint8_t*>(self) + 0x40) = v;   // 1417d9894 mov %edx,0x40
}
void Flag08And44(void* self, uint8_t v) {                  // 1417d98b0
    *static_cast<std::uint32_t*>(self) |= 0x8u;            // 1417d98b0 orl $0x8,0x30(%rcx)
    *reinterpret_cast<std::uint8_t*>(static_cast<std::uint8_t*>(self) + 0x44) = v;   // 1417d98b4 mov %dl,0x44
}
void Flag10And45(void* self, uint8_t v) {                  // 1417d98d0
    *static_cast<std::uint32_t*>(self) |= 0x10u;           // 1417d98d0 orl $0x10,0x30(%rcx)
    *reinterpret_cast<std::uint8_t*>(static_cast<std::uint8_t*>(self) + 0x45) = v;   // 1417d98d4 mov %dl,0x45
}
void Flag20And60(void* self, int32_t v) {                  // 1417d98f0
    *static_cast<std::uint32_t*>(self) |= 0x20u;           // 1417d98f0 orl $0x20,0x30(%rcx)
    *reinterpret_cast<std::int32_t*>(static_cast<std::uint8_t*>(self) + 0x60) = v;   // 1417d98f4 mov %edx,0x60
}

}  // namespace msgfield
}  // namespace tq
