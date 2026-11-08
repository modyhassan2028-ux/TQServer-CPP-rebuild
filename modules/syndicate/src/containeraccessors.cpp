// Every function here is a single instruction plus `ret`, except the two walks and the copies. The
// listing is quoted beside each one so the offsets can be checked against the binary rather than trusted.
#include "modules/syndicate/src/containeraccessors.h"

namespace synd {
namespace acc {

void (*g_pfn1417f2fdc)(void*) = nullptr;                           // 0x1417f2fdc

void* InitU32U64(void* self, const void* src, const void* tail) {  // 1417c5980
    *static_cast<std::uint32_t*>(self) = *static_cast<const std::uint32_t*>(src);   // mov (%rdx),%eax / mov %eax,(%rcx)
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(self) + 0x8) =
        *static_cast<const std::uint64_t*>(tail);                                   // mov (%r8),%rax / mov %rax,0x8(%rcx)
    return self;                                                                    // mov %rcx,%rax
}

void* At29(void* self) { return static_cast<std::uint8_t*>(self) + 0x29; }          // lea 0x29(%rcx),%rax
void* At10(void* self) { return static_cast<std::uint8_t*>(self) + 0x10; }          // lea 0x10(%rcx),%rax
void* At41(void* self) { return static_cast<std::uint8_t*>(self) + 0x41; }          // lea 0x41(%rcx),%rax
void* At21(void* self) { return static_cast<std::uint8_t*>(self) + 0x21; }          // lea 0x21(%rcx),%rax
void* At28(void* self) { return static_cast<std::uint8_t*>(self) + 0x28; }          // lea 0x28(%rcx),%rax
void* At08(void* self) { return static_cast<std::uint8_t*>(self) + 0x8; }           // lea 0x8(%rcx),%rax
void* At18(void* self) { return static_cast<std::uint8_t*>(self) + 0x18; }          // lea 0x18(%rcx),%rax
void* At40(void* self) { return static_cast<std::uint8_t*>(self) + 0x40; }          // lea 0x40(%rcx),%rax
void* At20(void* self) { return static_cast<std::uint8_t*>(self) + 0x20; }          // lea 0x20(%rcx),%rax

void* Field30(void* self) {                                                         // mov 0x30(%rcx),%rax
    return *reinterpret_cast<void**>(static_cast<std::uint8_t*>(self) + 0x30);
}
void* Field08(void* self) {                                                         // mov 0x8(%rcx),%rax
    return *reinterpret_cast<void**>(static_cast<std::uint8_t*>(self) + 0x8);
}
void* Field30Plus10(void* self) {                                                   // add $0x10,%rax
    return static_cast<std::uint8_t*>(*reinterpret_cast<void**>(static_cast<std::uint8_t*>(self) + 0x30)) + 0x10;
}
void* Field30Plus8(void* self) {                                                    // add $0x8,%rax
    return static_cast<std::uint8_t*>(*reinterpret_cast<void**>(static_cast<std::uint8_t*>(self) + 0x30)) + 0x8;
}

void* Init16U8(void* self, const void* src, const void* byte) {                     // 1417c5ae0
    *reinterpret_cast<std::uint64_t*>(self) =
        *static_cast<const std::uint64_t*>(src);                                    // mov (%rdx),%rax / mov %rax,(%rcx)
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(self) + 0x8) =
        *(static_cast<const std::uint64_t*>(src) + 1);                              // mov 0x8(%rdx),%rax / mov %rax,0x8(%rcx)
    *reinterpret_cast<std::uint8_t*>(static_cast<std::uint8_t*>(self) + 0x10) =
        *static_cast<const std::uint8_t*>(byte);                                    // movzbl (%r8),%eax / mov %al,0x10(%rcx)
    return self;
}

void* Init16(void* self, const void* src) {                                         // 1417c5e60
    *reinterpret_cast<std::uint64_t*>(self) =
        *static_cast<const std::uint64_t*>(src);                                    // mov (%rdx),%rax / mov %rax,(%rcx)
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(self) + 0x8) =
        *(static_cast<const std::uint64_t*>(src) + 1);                              // mov 0x8(%rdx),%rax / mov %rax,0x8(%rcx)
    return self;
}

// The minimal-element walk for the node layout whose sentinel flag is at +0x29. It follows `next` at +0x0
// until the flag is set, and returns the last real node — not the sentinel.
void* MinNode29(void* self) {                                                       // 1417c5c50
    std::uint8_t* cur = static_cast<std::uint8_t*>(self);
    std::uint8_t* node = *reinterpret_cast<std::uint8_t**>(cur);                    // mov (%rcx),%rax
    while (node[0x29] == 0) {                                                       // cmpb $0x0,0x29(%rax)
        cur = node;                                                                 // mov %rax,%rcx
        node = *reinterpret_cast<std::uint8_t**>(node);                             // mov (%rax),%rax
    }
    return cur;                                                                     // mov %rcx,%rax
}

void DeleteValueThunk(void* self, void* value) {                                    // 1417c5c80
    (void)self;                                                                     // rcx is overwritten before the jump
    g_pfn1417f2fdc(value);                                                          // mov %rdx,%rcx / jmp 0x1417f2fdc
}

// The same walk for the layout whose flag is at +0x41.
void* MinNode41(void* self) {                                                       // 1417c5f30
    std::uint8_t* cur = static_cast<std::uint8_t*>(self);
    std::uint8_t* node = *reinterpret_cast<std::uint8_t**>(cur);                    // mov (%rcx),%rax
    while (node[0x41] == 0) {                                                       // cmpb $0x0,0x41(%rax)
        cur = node;                                                                 // mov %rax,%rcx
        node = *reinterpret_cast<std::uint8_t**>(node);                             // mov (%rax),%rax
    }
    return cur;                                                                     // mov %rcx,%rax
}

std::uint64_t Limit3F(void) {                                                       // 1417c5ef0
    return 0x0FFFFFFFFFFFFFFFULL;                       // movabs $0xfffffffffffffff,%rax — 15 f's, not 16
}

}  // namespace acc
}  // namespace synd
