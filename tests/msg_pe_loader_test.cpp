// MsgServer unit M27 - the manual PE
// loader: FUN_1405098b0 (sections copy)
// + FUN_1405094d0 (relocs) +
// FUN_1405095a0 (imports) +
// FUN_140509990 (the orchestrator)
#include "../Exe/MsgServer/Port/MsgPeLoader.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <sys/mman.h>
using namespace msg;

// the file image
static unsigned char fimg[0x600];
static void w16f(int off, uint16_t v) {
    std::memcpy(fimg + off, &v, 2); }
static void w32f(int off, uint32_t v) {
    std::memcpy(fimg + off, &v, 4); }
static void w64f(int off, uint64_t v) {
    std::memcpy(fimg + off, &v, 8); }
// write inside the section: RVA -
// 0x1000 + 0x200 = file offset
static int sec(int rva) {
    return 0x200 + rva - 0x1000; }

static void build() {
    std::memset(fimg, 0, sizeof(fimg));
    const int NT = 0x40;
    w16f(0, 0x5a4d);
    w32f(0x3c, 0x40);
    w32f(NT, 0x4550);
    w16f(NT + 6, 1);          // 1 section
    w16f(NT + 0x14, 0xf0);
    w16f(NT + 0x16, 0x2002);
    w32f(NT + 0x28, 0x1500);  // entry RVA
    w64f(NT + 0x30, 0x20000000ULL);  // img base
    w32f(NT + 0x38, 0x1000);  // sect align
    w32f(NT + 0x54, 0x200);   // hdrs size
    w32f(NT + 0x90, 0x1200);  // imports RVA
    w32f(NT + 0xb0, 0x1100);  // relocs RVA
    w32f(NT + 0xb4, 0x10);    // relocs size
    // the section header
    w32f(0x148 + 0x8, 0x800);   // VirtualSize
    w32f(0x148 + 0xc, 0x1000);  // VA
    w32f(0x148 + 0x10, 0x400);  // raw size
    w32f(0x148 + 0x14, 0x200);  // raw ptr
    // ===== the reloc block (RVA 0x1100)
    w32f(sec(0x1100), 0x1120);  // PageRVA
    w32f(sec(0x1104), 0x10);    // BlockSize
    w16f(sec(0x1108), 0xa008);  // DIR64 @1128
    w16f(sec(0x110a), 0xa018);  // DIR64 @1138
    w16f(sec(0x110c), 0x0003);  // padding
    w16f(sec(0x110e), 0x0000);
    w64f(sec(0x1128), 0x100);
    w64f(sec(0x1138), 0x200);
    // ===== the imports (RVA 0x1200)
    w32f(sec(0x1200), 0x1240);  // ILT
    w32f(sec(0x120c), 0x1300);  // name
    w32f(sec(0x1210), 0x1260);  // FT
    // (the terminator descriptor at
    // 0x1214 is all zeros)
    w64f(sec(0x1240), 0x1280);  // by name
    w64f(sec(0x1248),
        0x8000000000000042ULL); // ordinal
    w64f(sec(0x1250), 0);       // end
    // hint (2 bytes) then the name -
    // split to avoid the greedy \x hex
    // escape (\x02F would eat the F)
    unsigned char hint[2] = {1, 2};
    std::memcpy(fimg + sec(0x1280), hint, 2);
    std::memcpy(fimg + sec(0x1282),
        "FuncOne", 8);
    std::memcpy(fimg + sec(0x1300),
        "KERN", 5);
}

int main() {
    build();

    MsgPeLoaderData L;
    // the mapped buffer (below 4GB:
    // the port truncates VERBATIM)
    unsigned char* mapped =
        (unsigned char*)mmap((void*)0x30000000,
            0x2000, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS |
                MAP_32BIT, -1, 0);
    assert(mapped != MAP_FAILED);
    L.m_fnVAlloc = [&](size_t n) {
        assert(n == 0x2000);
        return (void*)mapped; };
    L.m_fnVFree = [&](void* p) {
        assert(p == mapped); };
    L.m_fnVProtect = [&](void* p,
                         size_t n, uint32_t pr,
                         uint32_t* o) {
        assert(p == mapped && n == 0x2000);
        assert(pr == 0x40);
        *o = 0; };
    L.m_fnGetModuleHandleA =
        [&](const char* nm) {
        assert(std::strcmp(nm, "KERN") == 0);
        return L.bGmhOk ? L.pModule
            : nullptr; };
    L.m_fnGetProcAddress =
        [&](void* h, uint64_t a) {
        assert(h == L.pModule);
        if (a > 0xffff) {
            assert(std::strcmp(
                (const char*)a,
                "FuncOne") == 0);
            return (void*)0x11110000;
        }
        assert(a == 0x42);
        return L.bGpaOk
            ? (void*)0x22220000
            : nullptr; };
    L.m_fnEntry = [&](void* p, int reason,
                      int rsv) {
        assert(p == mapped);
        ++L.nEntryCalls;
        L.nEntryLastReason = reason;
        assert(reason == 1 || rsv == 0);
        return L.bEntryOk ? 1 : 0; };

    MsgPeDesc d;
    // ===== 1. the happy path
    assert(MsgPeLoad(d, fimg, sizeof(fimg),
        L) == 1);
    assert(d.nLoaded == 1);
    assert(d.nBase == (int)(uintptr_t)mapped);
    assert(d.pFile == mapped);
    assert(d.pNt == mapped + 0x40);
    assert(d.pSections == mapped + 0x148);
    assert(d.pEntry == mapped + 0x1500);
    // the mapped headers copied
    assert(*(uint32_t*)(mapped + 0x40)
        == 0x4550);
    // the section copied
    assert(*(uint32_t*)(mapped + 0x1128)
        != 0x100);   // relocated!
    int64_t nDelta = (int64_t)(
        uintptr_t)mapped - 0x20000000;
    uint64_t v1, v2;
    std::memcpy(&v1, mapped + 0x1128, 8);
    std::memcpy(&v2, mapped + 0x1138, 8);
    assert(v1 == (uint64_t)(0x100 +
        nDelta));
    assert(v2 == (uint64_t)(0x200 +
        nDelta));
    // the first thunk patched
    uint64_t t0, t1;
    std::memcpy(&t0, mapped + 0x1260, 8);
    std::memcpy(&t1, mapped + 0x1268, 8);
    assert(t0 == 0x11110000);
    assert(t1 == 0x22220000);
    assert(L.nVAlloc == 1 && L.nVFree == 0);
    assert(L.nGmh == 1 && L.nGpa == 2);
    assert(L.nEntryCalls == 1);
    assert(L.nEntryLastReason == 1);

    // ===== 2. already loaded
    assert(MsgPeLoad(d, fimg, sizeof(fimg),
        L) == 0);
    assert(L.nVAlloc == 1);   // no new

    // ===== 3. entry failure -> detach
    MsgPeDesc d2;
    L.bEntryOk = false;
    assert(MsgPeLoad(d2, fimg,
        sizeof(fimg), L) == 0);
    assert(L.nEntryCalls == 3);
    assert(L.nEntryLastReason == 0);
    assert(L.nVFree == 1);
    assert(d2.pEntry == nullptr);
    assert(d2.nLoaded == 0);

    // ===== 4. import failure paths
    L.bEntryOk = true;
    MsgPeDesc d3;
    L.bGpaOk = false;
    assert(MsgPeLoad(d3, fimg,
        sizeof(fimg), L) == 0);
    assert(L.nVFree == 2);
    assert(d3.nLoaded == 0);
    L.bGpaOk = true;
    L.bGmhOk = false;
    MsgPeDesc d4;
    assert(MsgPeLoad(d4, fimg,
        sizeof(fimg), L) == 0);
    assert(L.nVFree == 3);

    // ===== 5. no imports/relocs
    L.bGmhOk = true;
    MsgPeDesc d5;
    // zero out the dirs
    w32f(0x40 + 0x90, 0);
    w32f(0x40 + 0xb0, 0);
    w32f(0x40 + 0xb4, 0);
    assert(MsgPeLoad(d5, fimg,
        sizeof(fimg), L) == 1);
    assert(L.nGmh == 4);   // 3 fails + happy
    assert(L.nVAlloc == 5);
    assert(L.nEntryCalls == 4);
    assert(L.nEntryLastReason == 1);
    // restore
    w32f(0x40 + 0x90, 0x1200);
    w32f(0x40 + 0xb0, 0x1100);
    w32f(0x40 + 0xb4, 0x10);

    // ===== 6. validate failure
    MsgPeDesc d6;
    w16f(0, 0x4d4d);
    assert(MsgPeLoad(d6, fimg,
        sizeof(fimg), L) == 0);
    assert(L.nVAlloc == 5);
    w16f(0, 0x5a4d);

    printf("MSG_PE_LOADER_OK: "
           "FUN_1405098b0/1405094d0/"
           "1405095a0/140509990 VERBATIM "
           "(the headers+sections memmove "
           "with the desc +0x18/+0x20/"
           "+0x28 rebind to the mapped "
           "copy, the DIR64 reloc walk "
           "(PageSize-8)/2 with the "
           "base-ImageBase delta, the "
           "import descriptor walk with "
           "the 0xff name guard, hint+2 "
           "names, ordinals &0xffff, the "
           "FirstThunk patch, and the "
           "orchestrator: "
           "VirtualAlloc 0x3000/0x40, the "
           "reloc gate hdr+0xb0/0xb4, the "
           "unchecked VirtualProtect, "
           "hdr+0x30=base, entry(base,1) "
           "and the detach path entry("
           "base,0,0)+VirtualFree 0x8000 "
           "with the entry ptr cleared)\n");
    return 0;
}
