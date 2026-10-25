// MsgServer unit M26 - the manual PE
// loader validation + size computation
// FUN_140509760 + FUN_140509820
#include "../Exe/MsgServer/Port/MsgPeValidate.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

static unsigned char img[0x400];

static void w16(int off, uint16_t v) {
    std::memcpy(img + off, &v, 2); }
static void w32(int off, uint32_t v) {
    std::memcpy(img + off, &v, 4); }

// build a PE32+ DLL image:
//  DOS (0x40) + NT at 0x40 +
//  optional 0xf0 -> sections at 0x148
static void build(int nSecs, int secRawEnd) {
    std::memset(img, 0, sizeof(img));
    w16(0, 0x5a4d);          // MZ
    w32(0x3c, 0x40);          // e_lfanew
    const int NT = 0x40;
    w32(NT, 0x4550);          // PE sig
    w16(NT + 6, (uint16_t)nSecs);
    w16(NT + 0x14, 0xf0);     // opt size
    w16(NT + 0x16, 0x2002);   // DLL|EXEC
    w32(NT + 0x38, 0x1000);   // sect align
    w32(NT + 0x54, 0x200);    // hdrs size
    // sections at NT+0x108 = 0x148
    for (int i = 0; i < nSecs; ++i) {
        int s = 0x148 + i * 0x28;
        w32(s + 0x8, 0x800);   // VirtualSize
        w32(s + 0xc, 0x1000);  // VA
        w32(s + 0x10, 0x100); // SizeOfRaw
        w32(s + 0x14, 0x200); // raw ptr
    }
    if (secRawEnd > 0)
        w32(0x148 + 0x10, (uint32_t)secRawEnd);
}

int main() {
    MsgPeDesc d;

    // ===== 1. size guard (< 0x40)
    build(2, 0);
    assert(MsgPeValidate(d, img, 0x3f) == 0);
    // MZ missing
    build(2, 0);
    w16(0, 0x4d4d);
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // e_lfanew + 0x108 > size
    build(2, 0);
    w32(0x3c, 0x380);   // 0x380+0x108 >
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // PE sig missing
    build(2, 0);
    w32(0x40, 0x1234);
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // not a DLL
    build(2, 0);
    w16(0x40 + 0x16, 0x0002);
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // not executable
    build(2, 0);
    w16(0x40 + 0x16, 0x2000);
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // wrong optional size
    build(2, 0);
    w16(0x40 + 0x14, 0xe0);
    assert(MsgPeValidate(d, img, 0x400) == 0);

    // ===== 2. section raw bounds
    build(2, 0);   // sec0 raw: 0x200+0x600
    w32(0x148 + 0x14, 0x300);   // ptr
    w32(0x148 + 0x10, 0x300);   // size
    // end 0x600 <= 0x400? no: 0x600>0x400
    assert(MsgPeValidate(d, img, 0x400) == 0);
    // fits exactly (sec1 too)
    w32(0x148 + 0x28 + 0x14, 0x300);
    w32(0x148 + 0x28 + 0x10, 0x100);
    w32(0x148 + 0x10, 0x100);   // end 0x400
    assert(MsgPeValidate(d, img, 0x400) == 1);
    assert(d.pFile == img);
    assert(d.pNt == img + 0x40);
    assert(d.pSections == img + 0x148);
    // sec1 out of bounds (the second loop)
    w32(0x148 + 0x28 + 0x14, 0x380);
    w32(0x148 + 0x28 + 0x10, 0x100);
    assert(MsgPeValidate(d, img, 0x400) == 0);

    // ===== 3. the image size
    build(3, 0);
    assert(MsgPeValidate(d, img, 0x2400) == 1);
    // hdrs 0x200 align 0x1000 -> 0x1000;
    // each sec: max(0x800,0x600)=0x800 +
    // 0x1000 = 0x1800 -> align -> 0x2000
    assert(MsgPeImageSize(d) == 0x2000);
    // a bigger VA on section 2
    w32(0x148 + 2 * 0x28 + 0xc, 0x5000);
    w32(0x148 + 2 * 0x28 + 0x8, 0x1000);
    // max(0x1000,0x600)+0x5000 = 0x6000
    assert(MsgPeImageSize(d) == 0x6000);
    // VirtualSize < SizeOfRawData wins
    w32(0x148 + 2 * 0x28 + 0x8, 0);
    w32(0x148 + 2 * 0x28 + 0x10, 0x2000);
    // 0x2000+0x5000 = 0x7000 (raw end
    // 0x2200 <= 0x2400 still valid)
    assert(MsgPeImageSize(d) == 0x7000);
    // null NT -> 0
    MsgPeDesc d2;
    assert(MsgPeImageSize(d2) == 0);
    // zero sections: just the headers
    build(0, 0);
    assert(MsgPeValidate(d, img, 0x400) == 1);
    assert(MsgPeImageSize(d) == 0x1000);

    printf("MSG_PE_VALIDATE_OK: "
           "FUN_140509760/140509820 VERBATIM "
           "(the MZ/e_lfanew@0x3c/PE sig/"
           "DLL|EXEC/0xf0 guards, the "
           "e_lfanew+0x108 file bound, the "
           "per-section raw-end checks from "
           "NT+0x118, the desc fields "
           "+0x18/+0x20/+0x28, and the "
           "alignUp(SizeOfHeaders) + "
           "max-per-section virtual size)\n");
    return 0;
}
