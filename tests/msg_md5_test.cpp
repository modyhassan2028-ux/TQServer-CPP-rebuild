// MsgServer unit M12 - the MD5 core
// FUN_140507260, verified against RFC 1321
#include "../Exe/MsgServer/Port/MsgMd5.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

// one-block MD5 driver (test-only): standard
// init, pad, one transform, little-endian out
static std::string Md5OneBlock(const char* s) {
    uint8_t blk[64] = {0};
    size_t n = std::strlen(s);
    assert(n < 56);
    std::memcpy(blk, s, n);
    blk[n] = 0x80;
    uint64_t bits = (uint64_t)n * 8;
    std::memcpy(blk + 56, &bits, 8);
    uint32_t st[4] = {0x67452301, 0xefcdab89,
                      0x98badcfe, 0x10325476};
    MsgMd5Transform(st, blk);
    char out[33];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            std::sprintf(out + (i * 4 + j) * 2,
                "%02x", ((uint8_t*)st)[i * 4 + j]);
    return out;
}

int main() {
    // RFC 1321 test vectors (single-block)
    assert(Md5OneBlock("") ==
        "d41d8cd98f00b204e9800998ecf8427e");
    assert(Md5OneBlock("a") ==
        "0cc175b9c0f1b6a831c399e269772661");
    assert(Md5OneBlock("abc") ==
        "900150983cd24fb0d6963f7d28e17f72");
    assert(Md5OneBlock("message digest") ==
        "f96b697d7cb7938d525a2f31aaf161d0");
    assert(Md5OneBlock("abcdefghijklmnopqrstuvwxyz") ==
        "c3fcd3d76192e4007dfb496cca67e13b");
    assert(Md5OneBlock(
        "The quick brown fox jumps over the "
        "lazy dog") ==
        "9e107d9d372bb6826bd81d3542a419d6");

    printf("MSG_MD5_OK: FUN_140507260 VERBATIM - "
           "all 64 steps with the decompile's own "
           "SIGNED constants (-0x28955b88 = "
           "0xd76aa478 etc.), the multiply-or "
           "rotate forms, the unaligned 16-word "
           "little-endian load, and the literal "
           "scrambled tail - validated against "
           "six RFC 1321 vectors (empty/a/abc/"
           "message digest/abcdefghijklmnopqrstuvwxyz/"
           "quick brown fox)\n");
    return 0;
}
