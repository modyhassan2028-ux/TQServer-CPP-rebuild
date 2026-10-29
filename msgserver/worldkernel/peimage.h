#pragma once
// CPEImage — the PE view used by the module loader (140509xxx family).
// NOTE: the class name is inferred from behaviour (it stores the DOS header,
// the NT headers and the section table and walks the relocation directory);
// the binary carries no RTTI name for it. Offsets match the disassembly:
//   +0x18 base, +0x20 nt headers, +0x28 first section.
#include <cstdint>
#include <cstddef>

namespace msg {

struct SPEImageSeams {
    void (*Log)(const char* text);      // log_InlineLogERROR
};

class CPEImage {
public:
    // 140509760 — validates and attaches a mapped image. The base pointer is
    // stored even when the MZ check fails; the NT pointer only after the
    // e_lfanew bound check.
    int  AttachImage(void* base, uint32_t size);
    // 140509820 — the largest section-aligned end (0 without an image)
    int  GetMaxAlignedSize();
    // 1405094d0 — applies the 0xA000 relocation entries inside the blocks
    void ApplyRelocations(intptr_t delta);

    intptr_t base_;      // +0x18
    intptr_t nt_;        // +0x20
    intptr_t sections_;  // +0x28
};

} // namespace msg
