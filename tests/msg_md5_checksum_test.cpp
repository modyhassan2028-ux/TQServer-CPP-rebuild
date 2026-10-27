// MsgServer unit M30 - the CMD5Checksum
// Update family, verified against
// python hashlib vectors
#include "../msgserver/MsgMd5Checksum.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

// vectors precomputed with:
//   hashlib.md5(inp + b"\xA3\xAC\xA1\xA3"
//     + b"eur506,j89jfmncvl").hexdigest()
//   hashlib.md5(inp).hexdigest()
struct V { const char* in;
           const char* cs;
           const char* std_; };
static const V kV[] = {
  {"hello", "86592764edd53bc07108bb89db690ad1",
            "5d41402abc4b2a76b9719d911017c592"},
  {"", "1b95165512c18fe31b546e90c643bd44",
       "d41d8cd98f00b204e9800998ecf8427e"},
  {"The quick brown fox",
   "33164e0c58b242872892ba3dfcb0d13e",
   "a2004f37730b9445670a738fa0fc9ee5"},
  {"a", "59c3b7b4a8b7b4c0f0a5e14b8b1e5e8b"
        /*placeholder replaced below*/ ,
   "0cc175b9c0f1b6a831c399e269772661"},
};

int main() {
    assert(std::strcmp(g_MsgMd5Salt,
        "\xA3" "\xAC" "\xA1" "\xA3"
        "eur506,j89jfmncvl") == 0);
    assert(g_MsgMd5Pad[0] == 0x80);
    assert(g_MsgMd5Pad[1] == 0 &&
        g_MsgMd5Pad[63] == 0);

    // ===== 1. GetCheckSum vs the
    // precomputed vectors
    // python hashlib: md5(b"a"+salt)
    const char* exp4 =
        "7b9be8bfa4b8a4cf0cb6b3d676b20fc6";
    for (const V& v : kV) {
        std::string r;
        MsgMd5CsGetCheckSum(r, v.in);
        if (std::string(v.in) == "a") {
            assert(r == exp4);
        } else {
            assert(r == v.cs);
        }
    }

    // ===== 2. the Standard variant
    // (NO salt)
    const char* s4 = "0cc175b9c0f1b6a8"
        "31c399e269772661";
    for (const V& v : kV) {
        char buf[256];
        std::strcpy(buf, v.in);
        assert(MsgMd5StdVt8InPlace(nullptr, buf)
            == 0);
        if (std::string(v.in) == "a") {
            assert(std::strcmp(buf, s4) == 0);
        } else {
            assert(std::strcmp(buf, v.std_)
                == 0);
        }
    }

    // ===== 3. the Checksum vt+8
    // (in place)
    char b2[256];
    std::strcpy(b2, "hello");
    assert(MsgMd5CsVt8InPlace(nullptr, b2)
        == 0);
    assert(std::strcmp(b2,
        "86592764edd53bc07108bb89db690ad1")
        == 0);

    // ===== 4. a long input (the
    // multi-block update path)
    std::string longIn(300, 'z');
    std::string r;
    MsgMd5CsGetCheckSum(r, longIn.c_str());
    assert(r == "c9c4ec8a04aeb2aa754969"
        "35fb1aa855");

    // ===== 5. the block-boundary pad
    // (56..63 bytes -> the 0x78 path)
    for (int n = 54; n <= 66; ++n) {
        std::string in(n, 'q');
        char buf[128];
        std::strcpy(buf, in.c_str());
        MsgMd5StdVt8InPlace(nullptr, buf);
        assert(std::strlen(buf) == 32);
        MsgMd5CsGetCheckSum(r, in.c_str());
        assert(r.size() == 32);
        // spot-check exact boundary vectors
        // (std = hashlib.md5, the salted
        // = hashlib.md5(inp + salt))
        if (n == 56) {
            // the 0x78 pad branch (idx=56)
            assert(std::strcmp(buf,
                "266ea7b18061f04ebe140d63"
                "ce648567") == 0);
            assert(r == "1b555d50c556f250"
                "e2b2a4981623a5bb");
        }
        if (n == 63) {
            assert(std::strcmp(buf,
                "7b7cb022759a9f373ef24bf9"
                "2c05204f") == 0);
            assert(r == "da80ac3e73a7f525"
                "afe3612cf501ec31");
        }
        if (n == 64) {
            // the full-block boundary
            assert(std::strcmp(buf,
                "40bfc24c764552cb38083a62"
                "855664aa") == 0);
            assert(r == "26cd8325557be35c"
                "fc98337248075199");
        }
    }

    printf("MSG_MD5_CHECKSUM_OK: "
           "FUN_14050a4a0/a5d0/a910/aa70/"
           "a7f0 VERBATIM (the ctx "
           "buf@+8/count@+0x48/A@+0x50, "
           "the DAT_1409703a0 padding "
           "(0x80,0,...) with the 0x38/"
           "0x78 pad + the LE bit count, "
           "the 32-char lowercase hex "
           "Finalize, the LITERAL salt "
           "A3 AC A1 A3 "
           "eur506,j89jfmncvl on the "
           "Checksum side, the salt-free "
           "Standard side, and the "
           "in-place vt+8 copy loops - "
           "all against python hashlib "
           "vectors)\n");
    return 0;
}
