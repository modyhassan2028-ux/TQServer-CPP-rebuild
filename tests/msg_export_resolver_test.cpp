// MsgServer unit M24 - the export
// resolver FUN_140509380 + world-kernel
// dispatch FUN_140508f10 + channel
// factory FUN_140509280
#include "../Exe/MsgServer/Port/MsgExportResolver.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <sys/mman.h>
using namespace msg;

// the resolver truncates to 32 bits
// (VERBATIM Win32 semantics), so the
// fake image must live below 4GB
static unsigned char* img =
    (unsigned char*)mmap(
        (void*)0x20000000, 0x1000,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS |
            MAP_32BIT, -1, 0);

int main() {
    // ===== build a fake module image
    // layout: [0..0x1000) the image;
    // export dir at RVA 0x200
    std::memset(img, 0xCC, 0x1000);
    const int kBase = (int)(uintptr_t)img;   // the buffer IS the mapped module
    const int kExpRva = 0x200;
    char* pExp = (char*)img + kExpRva;
    auto w32 = [&](int off, uint32_t v) {
        std::memcpy(img + off, &v, 4); };
    auto w16 = [&](int off, uint16_t v) {
        std::memcpy(img + off, &v, 2); };
    // the export dir
    w32(0x200 + 0x10, 1);      // ordBase
    w32(0x200 + 0x14, 3);      // nFuncs
    w32(0x200 + 0x18, 3);      // nNames
    w32(0x200 + 0x1c, 0x300);  // funcs RVA
    w32(0x200 + 0x20, 0x320);  // names RVA
    w32(0x200 + 0x24, 0x330);  // nameOrds
    // funcs table at RVA 0x300:
    //   [0]=0x800 [1]=0x900 [2]=0xA00
    w32(0x300 + 0, 0x800);
    w32(0x300 + 4, 0x900);
    w32(0x300 + 8, 0xA00);
    // names RVAs at 0x320
    w32(0x320 + 0, 0x500);   // "alpha"
    w32(0x320 + 4, 0x520);   // "beta"
    w32(0x320 + 8, 0x540);   // "CreateMapGroup"
    // name ordinals at 0x330
    w16(0x330 + 0, 0);
    w16(0x330 + 2, 1);
    w16(0x330 + 4, 2);
    // the names
    std::memcpy(img + 0x500, "alpha", 6);
    std::memcpy(img + 0x520, "beta", 5);
    std::memcpy(img + 0x540,
        "CreateMapGroup", 15);
    // the header: a struct with +0x88
    // = exp RVA, +0x8c = size (we place
    // the header struct at img+0x80 so
    // its +0x88 lands at 0x108)
    static char hdr[0x100];
    std::memset(hdr, 0, sizeof(hdr));
    std::memcpy(hdr + 0x88, &kExpRva, 4);
    uint32_t sz = 0x200;
    std::memcpy(hdr + 0x8c, &sz, 4);
    // the descriptor: +0 flag, +0x10
    // base, +0x20 hdr ptr
    static char desc[0x30];
    std::memset(desc, 0, sizeof(desc));
    *(int*)(desc + 0x00) = 1;
    std::memcpy(desc + 0x10, &kBase, 4);
    char* pLocHdr = hdr;
    std::memcpy(desc + 0x20, &pLocHdr, 8);

    // ===== 1. by name
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"alpha") ==
        (void*)(uintptr_t)(
            kBase + 0x800));
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"beta") ==
        (void*)(uintptr_t)(
            kBase + 0x900));
    // missing name -> 0
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"gamma") ==
        nullptr);

    // ===== 2. by ordinal (the quirk:
    // (0xffff - base=1) & ord = 0xFFFE
    // & ord)
    // ord 2: 0xFFFE & 2 = 2 -> funcs[2]
    assert(MsgResolveExport(desc, 2) ==
        (void*)(uintptr_t)(
            kBase + 0xA00));
    // ord 1: 0xFFFE & 1 = 0 -> funcs[0]
    assert(MsgResolveExport(desc, 1) ==
        (void*)(uintptr_t)(
            kBase + 0x800));

    // ===== 3. the guards
    *(int*)(desc + 0x00) = 0;
    assert(MsgResolveExport(desc, 1) ==
        nullptr);
    *(int*)(desc + 0x00) = 1;
    *(int*)(hdr + 0x88) = 0;
    assert(MsgResolveExport(desc, 1) ==
        nullptr);
    *(int*)(hdr + 0x88) = kExpRva;
    *(int*)(hdr + 0x8c) = 0;
    assert(MsgResolveExport(desc, 1) ==
        nullptr);
    *(int*)(hdr + 0x8c) = 0x200;

    // ===== 4. the forwarder check
    // func[1] -> RVA 0x900 (inside
    // [0x200, 0x400)? NO: 0x900 > 0x400
    // -> real). make it a forwarder:
    w32(0x300 + 4, 0x280);   // inside!
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"beta") ==
        nullptr);
    // exactly at the end boundary ->
    // real (outside)
    w32(0x300 + 4, 0x400);
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"beta") !=
        nullptr);
    w32(0x300 + 4, 0x900);

    // ===== 5. the idx bounds
    w16(0x330 + 2, 5);   // ordIdx 5 >= 3
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)"beta") ==
        nullptr);
    w16(0x330 + 2, 1);

    // direct resolve of the kernel name
    assert(MsgResolveExport(desc,
        (uint64_t)(uintptr_t)
        "CreateMapGroup") ==
        (void*)(uintptr_t)(
            kBase + 0xA00));

    // ===== 6. the dispatch
    assert(MsgLoadWorldKernel(0, desc) ==
        (void*)(uintptr_t)(
            kBase + 0xA00));
    assert(MsgLoadWorldKernel(1, desc) ==
        nullptr);   // not exported
    assert(MsgLoadWorldKernel(2, desc) ==
        nullptr);   // not exported
    assert(MsgLoadWorldKernel(3, desc) ==
        nullptr);

    // ===== 7. the channel factory
    MsgChannelFactoryData f;
    static char pool[0x900];
    int nPoolUse = 0;
    f.m_fnNew = [&](size_t n) {
        assert(n == 0x890 || n == 0x60);
        return f.bNewOk && !(n == 0x60 &&
            !f.bNew2Ok)
            ? (void*)(pool) : nullptr; };
    f.m_fnCtorReporter = [&](void* p) {
        assert(p == pool);
        *(void**)p = f.pRepVt; };
    void* out = nullptr;
    MsgGetChannel(0, &out, f);
    assert(out == pool);
    assert(*(void**)pool == f.pDesVt);
    assert(f.nLastSize == 0x890);
    MsgGetChannel(1, &out, f);
    assert(*(void**)pool == f.pRepVt);
    assert(f.nCtors == 1);
    MsgGetChannel(2, &out, f);
    assert(*(void**)pool == f.pMd5Vt);
    // ch 3: untouched
    out = (void*)0x777;
    MsgGetChannel(3, &out, f);
    assert(out == (void*)0x777);
    // ch 4: null
    MsgGetChannel(4, &out, f);
    assert(out == nullptr);
    assert(f.nNews == 3);

    printf("MSG_EXPORT_RESOLVER_OK: "
           "FUN_140509380/140508f10/"
           "140509280 VERBATIM (the export "
           "resolver with the ordinal "
           "quirk (0xffff-base)&ord, the "
           "name scan, the forwarder "
           "window, the guards, the "
           "world-kernel dispatch, the "
           "DES/reporter/MD5 channel "
           "factory with the untouched "
           "ch-3 out - 18 branches)\n");
    return 0;
}
