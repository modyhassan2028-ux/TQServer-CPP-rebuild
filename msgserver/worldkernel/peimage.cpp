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
    int32_t lfanew = ld<int32_t>((uint8_t*)base + 0x3c);   // e_lfanew (the RAW reaches it as short* + 0x1e)
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


// 1405098b0 — moves the headers (SizeOfHeaders + nsec*0x28 bytes) and each raw
// section to the new image, then re-points base/NT/sections at that image.
// Sections with a zero VirtualAddress or a zero size are skipped.
void CPEImage::CopySections(void* newBase, void* fileBase) {
    intptr_t nt = nt_;
    uint16_t nsec = ld<uint16_t>((void*)(nt + 6));
    int32_t hdr = ld<int32_t>((void*)(nt + 0x54));
    size_t head = (size_t)(int)(hdr + ((uint32_t)nsec + (uint32_t)nsec * 4) * 8);
    std::memmove(newBase, fileBase, head);
    for (uint32_t i = 0; i < (uint32_t)nsec; i++) {
        intptr_t s = sections_ + (intptr_t)i * 0x28;
        int32_t va = ld<int32_t>((void*)(s + 0x0c));
        uint32_t rsize = (uint32_t)ld<int32_t>((void*)(s + 0x10));
        int32_t raw = ld<int32_t>((void*)(s + 0x14));
        if (va == 0 || rsize == 0) continue;
        std::memmove((void*)(uintptr_t)(uint32_t)(va + (int)(intptr_t)newBase),
                     (void*)(uintptr_t)(uint32_t)(raw + (int)(intptr_t)fileBase),
                     (size_t)rsize);
    }
    base_ = (intptr_t)newBase;
    int32_t lfanew = ld<int32_t>((void*)((uint8_t*)newBase + 0x3c));
    nt_ = (intptr_t)newBase + lfanew;
    sections_ = nt_ + 0x108;
}

// 140509990
int CPEImage::Load(void* fileBase, uint32_t fileSize, SLoadSeams& s) {
    if (image_ != 0) return 0;                       // +0x10 already occupied
    if (AttachImage(fileBase, fileSize) == 0) return 0;
    int size = GetMaxAlignedSize();
    if (size == 0) return 0;
    void* img = s.Alloc((size_t)size);
    if (img == nullptr) return 0;
    CopySections(img, fileBase);
    if (ld<int32_t>((void*)(nt_ + 0xb0)) != 0 && ld<int32_t>((void*)(nt_ + 0xb4)) != 0)
        ApplyRelocations((intptr_t)img);
    if (s.ResolveImports(this, img) == 0) {
        s.Free(img);
        return 0;
    }
    s.Protect(img, (size_t)size, 0x40);
    st<intptr_t>((void*)(nt_ + 0x30), (intptr_t)img);
    intptr_t entry = (intptr_t)img + ld<int32_t>((void*)(nt_ + 0x28));
    entry_ = entry;
    if (s.CallEntry(entry, img, 1, 0) != 0) {
        loaded_ = 1;
        image_ = (intptr_t)img;
        return 1;
    }
    s.CallEntry(entry, img, 0, 0);
    s.Free(img);
    entry_ = 0;
    return 0;
}

// 1405095a0 — resolves every import descriptor. The DLL name is copied into a
// 256-byte buffer (a name of 0x100 or more fails the load), then each thunk is
// resolved by name (hint byte skipped with +2) or by ordinal (high bit set).
int CPEImage::ResolveImports(void* img, SImportSeams& s) {
    intptr_t nt = nt_;
    uint32_t dirRva = ld<uint32_t>((void*)(nt + 0x90));        // import directory RVA
    if (dirRva == 0) return 1;
    uint8_t* image = (uint8_t*)img;
    intptr_t desc = (intptr_t)image + dirRva;
    uint32_t oft = ld<uint32_t>((void*)desc);                  // OriginalFirstThunk
    while (oft != 0) {
        uint32_t nameRva = ld<uint32_t>((void*)(desc + 0x0c));
        uint32_t firstThunk = ld<uint32_t>((void*)(desc + 0x10));
        char dll[256];
        const char* src = (const char*)(image + nameRva);
        size_t n = 0;
        dll[0] = '\0';
        while (src[n] != '\0') {
            dll[n] = src[n];
            n++;
            if (n > 0xff) return 0;
        }
        dll[n] = '\0';
        void* mod = s.GetModuleHandleA(dll);
        if (mod == nullptr) return 0;
        intptr_t thunk = (intptr_t)image + oft;
        for (uint32_t i = 0;; i++) {
            uint64_t ent = ld<uint64_t>((void*)(thunk + (intptr_t)i * 8));
            if (ent == 0) break;
            void* fn;
            if ((ent & 0x8000000000000000ull) == 0)
                fn = s.GetProcAddress(mod, (const char*)(image + (uintptr_t)ent + 2));
            else
                fn = s.GetProcAddressOrdinal(mod, (uint16_t)(ent & 0xffff));
            if (fn == nullptr) return 0;
            st<uint64_t>((void*)((intptr_t)image + firstThunk + (intptr_t)i * 8),
                         (uint64_t)(uintptr_t)fn);
        }
        desc += 0x14;
        oft = ld<uint32_t>((void*)desc);
    }
    return 1;
}

// 140509380 — a value below 0x10000 is treated as an ordinal (the export Base
// is subtracted, the function table is bounds-checked and the RVA must fall
// outside the export directory itself), anything wider is a name pointer that
// is matched against the AddressOfNames table.
intptr_t CPEImage::LookupExport(uintptr_t nameOrOrdinal) {
    intptr_t nt = nt_;
    if (nt == 0) return 0;
    intptr_t image = image_;
    uint32_t dirRva = ld<uint32_t>((void*)(nt + 0x88));
    uint32_t dirSize = ld<uint32_t>((void*)(nt + 0x8c));
    if (dirRva == 0 || dirSize == 0 || loaded_ == 0) return 0;
    intptr_t dir = image + (intptr_t)dirRva;
    if ((nameOrOrdinal & 0xffff0000) == 0) {
        uint32_t baseVal = ld<uint32_t>((void*)(dir + 0x10));
        uint32_t ord = (uint32_t)(0xffff - baseVal) & (uint32_t)nameOrOrdinal;
        if ((int32_t)ord >= 0 && (int32_t)ord < ld<int32_t>((void*)(dir + 0x14))) {
            int32_t aof = ld<int32_t>((void*)(dir + 0x1c));
            uint32_t rva = ld<uint32_t>((void*)(image + aof + (intptr_t)ord * 4));
            if (rva <= dirRva || dirSize + dirRva <= rva) return image + (intptr_t)rva;
        }
        return 0;
    }
    int32_t nNames = ld<int32_t>((void*)(dir + 0x18));
    if (nNames <= 0) return 0;
    int32_t aon = ld<int32_t>((void*)(dir + 0x20));
    int32_t aono = ld<int32_t>((void*)(dir + 0x24));
    for (int32_t i = 0; i < nNames; i++) {
        int32_t nameRva = ld<int32_t>((void*)(image + aon + (intptr_t)i * 4));
        const char* nm = (const char*)(image + nameRva);
        if (std::strcmp(nm, (const char*)nameOrOrdinal) != 0) continue;
        uint16_t ord = ld<uint16_t>((void*)(image + aono + (intptr_t)i * 2));
        if ((int32_t)ord >= 0 && (int32_t)ord < ld<int32_t>((void*)(dir + 0x14))) {
            int32_t aof = ld<int32_t>((void*)(dir + 0x1c));
            uint32_t rva = ld<uint32_t>((void*)(image + aof + (intptr_t)ord * 4));
            if (rva <= dirRva || dirSize + dirRva <= rva) return image + (intptr_t)rva;
        }
        return 0;
    }
    return 0;
}

// 140508f60 — the only 3 objects the factory knows are DES (0x890) and the two
// MD5 flavours (0x60); kind 3 leaves the out slot untouched (RAW quirk).
int CPEImage::BootValidate(void* data, int32_t size, char decrypt,
                           SLoaderSeams& s, CPEImage& img) {
    if (data == nullptr || size <= 0) return 0;
    if (((size + ((size >> 31) & 7)) & 7) != ((size >> 31) & 7)) return 0;
    if (decrypt != 0) {
        void* obj = s.CreateObject(0);
        if (obj == nullptr) return 0;
        s.CipherSetKey(obj, "*J_@'n 3");
        s.CipherProcess(obj, data, (uint32_t)size);
        s.CipherDestroy(obj);
    }
    if (s.LoadLibraryA("msvcp90.dll") == nullptr) s.Log("Cannot load msvcp90.dll");
    if (s.LoadLibraryA("msvcr90.dll") == nullptr) s.Log("Cannot load msvcr90.dll");
    if (s.ParseImage(&img, data, (uint32_t)size) == 0) return 0;
    if (img.LookupExport((uintptr_t)"CreateMapGroup") == 0) return 0;
    if (img.LookupExport((uintptr_t)"CreateWorldKernel") == 0) return 0;
    if (img.LookupExport((uintptr_t)"CreateNewMapData") == 0) return 0;
    if (img.LookupExport((uintptr_t)"CreateMapGroupDefaultData") == 0) return 0;
    return 1;
}
} // namespace msg
