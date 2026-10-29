#pragma once
// CPEImage — the PE view + loader used by the module loader (140509*** family).
// The name is inferred from behaviour; the binary carries no RTTI name.
// Layout as used by the ported members:
//   +0x00 loaded flag, +0x08 entry point, +0x10 loaded image base,
//   +0x18 file base, +0x20 NT headers, +0x28 first section.
#include <cstdint>
#include <cstddef>

namespace msg {

class CPEImage;

struct SLoadSeams {
    void* (*Alloc)(size_t size);                      // VirtualAlloc(0,size,0x3000,0x40)
    int   (*Protect)(void* p, size_t n, uint32_t fl);  // VirtualProtect(..,0x40,&old)
    void  (*Free)(void* p);                           // VirtualFree(p,0,0x8000)
    int   (*ResolveImports)(CPEImage* self, void* img);   // 1405095a0
    int   (*CallEntry)(intptr_t entry, void* image, int a, int b);  // (*entry)(img,1)
};

class CPEImage {
public:
    // 140509760 — validates and attaches a file image (see the .cpp for the
    // exact order of the base/NT stores and the section bound check).
    int  AttachImage(void* base, uint32_t size);
    // 140509820 — the largest section-aligned end (0 without an image)
    int  GetMaxAlignedSize();
    // 1405098b0 — copies the headers and the raw sections into the new image
    // and re-points the view at it
    void CopySections(void* newBase, void* fileBase);
    // 1405094d0 — applies the 0xA000 relocation entries
    void ApplyRelocations(intptr_t delta);
    // 140509990 — virtual-allocates, copies, relocates, resolves and calls the
    // entry point with (image, 1); a rejected entry frees and reports 0
    int  Load(void* fileBase, uint32_t fileSize, SLoadSeams& s);

    int32_t  loaded_;    // +0x00
    int32_t  pad04_;
    intptr_t entry_;     // +0x08
    intptr_t image_;     // +0x10
    intptr_t base_;      // +0x18
    intptr_t nt_;        // +0x20
    intptr_t sections_;  // +0x28
};

} // namespace msg
