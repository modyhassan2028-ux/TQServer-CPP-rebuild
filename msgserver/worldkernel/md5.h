#pragma once
// MD5::CMD5Checksum — only the constructor (14050a570) is recovered so far.
// NOTE: the original tree has no __FILE__ string for the cipher files, so this
// path is inferred like peimage.*; the layout is taken from the disassembly:
//   +0x00 vftable, +0x08..+0x40 zeroed, +0x48/+0x4c zeroed,
//   +0x50..+0x5c the standard MD5 IV.
#include <cstdint>

namespace msg {

struct CMD5Checksum {
    void*    vft_;      // +0x00
    uint64_t zero1_;    // +0x08
    uint64_t zero2_;    // +0x10
    uint64_t zero3_;    // +0x18
    uint64_t zero4_;    // +0x20
    uint64_t zero5_;    // +0x28
    uint64_t zero6_;    // +0x30
    uint64_t zero7_;    // +0x38
    uint64_t zero8_;    // +0x40
    uint32_t at48_;     // +0x48
    uint32_t at4c_;     // +0x4c
    uint32_t h0_;       // +0x50
    uint32_t h1_;       // +0x54
    uint32_t h2_;       // +0x58
    uint32_t h3_;       // +0x5c

    // 14050a570 — stores the vftable, clears the running state and seeds the IV
    static CMD5Checksum* Init(CMD5Checksum* self, void* vftable);
};

} // namespace msg
