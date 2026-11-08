#include "modules/syndicate/src/vtableforwarders.h"

namespace synd {

void* (*g_pfn1417b6210)(void*) = nullptr;                                  // 0x1417b6210
void* (*g_pfn14173f9c0)(void*, int32_t, int32_t) = nullptr;                // 0x14173f9c0
std::int32_t (*g_pfn14173d820)(void*, int32_t, int32_t) = nullptr;         // 0x14173d820

namespace {
// The receiver is whatever pointer the object starts with, and the call goes to the slot's entry. Done
// through the real vtable pointer, because that is what the original does; there is nothing to seam here.
inline void Dispatch2B0(void* obj, std::int32_t v) {
    typedef void (*Fn)(void*, std::int32_t);
    const Fn fn = *reinterpret_cast<Fn*>(*reinterpret_cast<std::uint8_t**>(obj) + 0x2B0);
    fn(obj, v);
}
inline void Dispatch2B8(void* obj, std::int32_t v) {
    typedef void (*Fn)(void*, std::int32_t);
    const Fn fn = *reinterpret_cast<Fn*>(*reinterpret_cast<std::uint8_t**>(obj) + 0x2B8);
    fn(obj, v);
}
inline void Dispatch378(void* obj, std::int32_t v) {
    typedef void (*Fn)(void*, std::int32_t);
    const Fn fn = *reinterpret_cast<Fn*>(*reinterpret_cast<std::uint8_t**>(obj) + 0x378);
    fn(obj, v);
}
}

// mov (%rcx),%rcx / mov %r8d,%edx / mov (%rcx),%rax / jmp *0x2b0(%rax)
void ForwardSlot2B0(void* self, std::int32_t a2, std::int32_t a3) {        // 14177fa40
    (void)a2;                                            // edx is overwritten with r8d before the jump
    void* obj = *static_cast<void**>(self);              // mov (%rcx),%rcx
    Dispatch2B0(obj, a3);                                // mov %r8d,%edx / jmp *0x2b0(%rax)
}

void ForwardSlot2B8(void* self, std::int32_t a2, std::int32_t a3) {        // 14177fa50
    (void)a2;
    void* obj = *static_cast<void**>(self);              // mov (%rcx),%rcx
    Dispatch2B8(obj, a3);                                // jmp *0x2b8(%rax)
}

// ebx=r8d, edi=edx, call 0x14173f9c0, then tail-jump 0x14173d820 with the same two integers.
void ForwardVia14173D820(void* self, std::int32_t a2, std::int32_t a3) {   // 14177fa60
    void* obj = g_pfn14173f9c0(self, a2, a3);            // call 0x14173f9c0
    g_pfn14173d820(obj, a2, a3);                         // jmp 0x14173d820
}

// A different receiver source: 0x1417b6210 returns the object, then slot 0x378 is entered.
void ForwardSlot378(void* self, std::int32_t a2, std::int32_t a3) {        // 14177fa10
    (void)a2;
    void* obj = g_pfn1417b6210(self);                    // call 0x1417b6210
    Dispatch378(obj, a3);                                // mov (%rax),%r9 / jmp *0x378(%r9)
}

// The switch: 0 -> 0x14177fa40, 1 -> 0x14177fa10, 2 -> 0x14177fa50, 3 -> 0x14177fa60, else null.
void (*SelectForwarder(std::int32_t kind))(void*, std::int32_t, std::int32_t) {   // 14177fa90
    switch (kind) {
        case 0: return &ForwardSlot2B0;
        case 1: return &ForwardSlot378;
        case 2: return &ForwardSlot2B8;
        case 3: return &ForwardVia14173D820;
        default: return nullptr;
    }
}

}  // namespace synd
