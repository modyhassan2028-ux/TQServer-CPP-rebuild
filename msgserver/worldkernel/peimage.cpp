#include "peimage.h"
#include <cstring>

namespace {
template <class T> static T ld(const void* p) { T v; std::memcpy(&v, p, sizeof v); return v; }
template <class T> static void st(void* p, T v) { std::memcpy(p, &v, sizeof v); }
}

namespace msg {

// 140509760
int CPEImage::AttachImage(void* base, uint32_t size) {
    if (size <= 0x3f) return 0;
    base_ = (intptr_t)base;
    if (*(uint16_t*)base != 0x5a4d) return 0;                 // 'MZ'
    int32_t lfanew = ld<int32_t>((uint8_t*)base + 0x1e);
    if ((uint64_t)((int64_t)lfanew + 0x108) > (uint64_t)size) return 0;
    intptr_t nt = (intptr_t)base + lfanew;
    nt_ = nt;
    if (ld<uint32_t>((void*)nt) != 0x4550) return 0;                    // 'PE\0\0'
    uint16_t chars = ld<uint16_t>((void*)(nt + 0x16));
    if ((chars & 0x2000) == 0) return 0;                       // DLL
    if ((chars & 2) == 0) return 0;                            // EXECUTABLE_IMAGE
    if (ld<int16_t>((void*)(nt + 0x14)) != 0xf0) return 0;              // PE32 magic
    sections_ = nt + 0x108;
    int nsec = (int)ld<uint16_t>((void*)(nt + 6));
    for (int i = 0; i < nsec; i++) {
        intptr_t s = nt + 0x118 + (intptr_t)i * 0x28;
        int32_t va = ld<int32_t>((void*)s);
        int32_t raw = ld<int32_t>((void*)(s + 4));
        if (size < (uint32_t)(raw + va)) return 0;             // VirtualAddress+SizeOfRawData
    }
    return 1;
}

// 140509820
int CPEImage::GetMaxAlignedSize() {
    intptr_t nt = nt_;
    if (nt == 0) return 0;
    int align = ld<int32_t>((void*)(nt + 0x38));               // SectionAlignment
    uint16_t nsec = ld<uint16_t>((void*)(nt + 6));
    int best = ((ld<int32_t>((void*)(nt + 0x54)) + -1 + align) / align) * align;  // SizeOfHeaders
    for (uint32_t i = 0; i < (uint32_t)nsec; i++) {
        intptr_t s = sections_ + (intptr_t)i * 0x28;
        int32_t vsize = ld<int32_t>((void*)(s + 0x08));        // VirtualSize
        int32_t vaddr = ld<int32_t>((void*)(s + 0x0c));        // VirtualAddress
        int32_t rsize = ld<int32_t>((void*)(s + 0x10));        // SizeOfRawData
        int32_t big = vsize;
        if (vsize < rsize) big = rsize;
        int32_t v = ((big + vaddr + -1 + align) / align) * align;
        if (best < v) best = v;
    }
    return best;
}

// 1405094d0
void CPEImage::ApplyRelocations(intptr_t delta) {
    intptr_t nt = nt_;
    uint32_t dirRva = ld<uint32_t>((void*)(nt + 0xb0));        // relocation directory RVA
    uintptr_t blk = (uintptr_t)((int64_t)dirRva + delta);
    if (blk == 0) return;
    uint8_t* p = (uint8_t*)blk;
    uint32_t blockRva = ld<uint32_t>(p);
    uint32_t cb = ld<uint32_t>(p + 4);
    int32_t end = (int32_t)(cb + blockRva);
    while (end != 0) {
        int32_t n = (int32_t)(((uint64_t)cb - 8) >> 1);
        for (int32_t i = 0; i < n; i++) {
            uint16_t e = ld<uint16_t>(p + (intptr_t)i * 2 + 8);
            if ((e & 0xf000) == 0xa000) {
                intptr_t slot = (intptr_t)((uintptr_t)blockRva + (uintptr_t)delta + (e & 0xfff));
                int64_t v = ld<int64_t>((void*)slot);
                st<int64_t>((void*)slot, v + (delta - ld<int64_t>((void*)(nt + 0x30))));
            }
        }
        p = p + ld<uint32_t>(p + 4);
        blockRva = ld<uint32_t>(p);
        cb = ld<uint32_t>(p + 4);
        end = (int32_t)(cb + blockRva);
    }
}

} // namespace msg
