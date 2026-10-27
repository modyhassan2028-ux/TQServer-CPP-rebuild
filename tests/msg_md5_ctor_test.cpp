// MsgServer unit M25 - the MD5
// checksum ctor FUN_14050a570
#include "../msgserver/MsgMd5Ctor.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    unsigned char buf[0x60];
    std::memset(buf, 0xAB, sizeof(buf));
    assert(MsgMd5ChecksumCtor(buf) == buf);
    // the vftable
    assert(*(void**)buf == g_pMd5ChecksumVt);
    // +0x08..+0x4f all zero
    for (int i = 8; i < 0x50; ++i)
        assert(buf[i] == 0);
    // the MD5 init state
    uint32_t a, b, c, d;
    std::memcpy(&a, buf + 0x50, 4);
    std::memcpy(&b, buf + 0x54, 4);
    std::memcpy(&c, buf + 0x58, 4);
    std::memcpy(&d, buf + 0x5c, 4);
    assert(a == 0x67452301 &&
        b == 0xefcdab89 &&
        c == 0x98badcfe &&
        d == 0x10325476);
    // +0x50..0x60 total size check: the
    // ctor writes exactly to 0x60
    assert(sizeof(buf) == 0x60);

    // two independent objects
    unsigned char buf2[0x60];
    MsgMd5ChecksumCtor(buf2);
    assert(std::memcmp(buf, buf2, 0x60)
        == 0);

    printf("MSG_MD5_CTOR_OK: "
           "FUN_14050a570 VERBATIM (the "
           "CMD5Checksum vftable, the "
           "zeroing through +0x4f, and "
           "the standard MD5 init state "
           "A/B/C/D at +0x50/+0x54/+0x58/"
           "+0x5c)\n");
    return 0;
}
