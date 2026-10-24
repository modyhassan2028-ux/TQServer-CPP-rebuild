// MsgServer unit M13 - the MD5 service
// FUN_140507ab0/b80/0a0/ca0/d30
#include "../Exe/MsgServer/Port/MsgMd5Service.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

static std::string S(char* p) {
    std::string r = p ? p : "(null)";
    free(p);
    return r;
}

int main() {
    // ===== the one-shot string hashes (RFC
    // + classic vectors, incl. multi-block) =====
    assert(S(MsgMd5OfString("")) ==
        "d41d8cd98f00b204e9800998ecf8427e");
    assert(S(MsgMd5OfString("abc")) ==
        "900150983cd24fb0d6963f7d28e17f72");
    assert(S(MsgMd5OfString("message digest")) ==
        "f96b697d7cb7938d525a2f31aaf161d0");
    // 62 bytes -> crosses into a second block
    assert(S(MsgMd5OfString(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789")) ==
        "d174ab98d277d9f5a5611c2c9f419d9f");
    // 160 digits -> multi-block with 64-byte
    // chunk loop + tail
    {
        std::string s;
        for (int i = 0; i < 16; ++i)
            s += "1234567890";
        assert(S(MsgMd5OfString(s.c_str())) ==
            "268c7919189d85e276d74b8c60b2f84f");
    }

    // ===== the chunked-update path =====
    {
        uint8_t ctx[MSG_MD5_CTX_SIZE];
        MsgMd5InitCtx(ctx);
        MsgMd5Update(ctx, "ab", 2);
        MsgMd5Update(ctx, "c", 1);
        MsgMd5Finalize(ctx);
        std::string r = S(MsgMd5DigestHex(
            ctx + 0x58));
        assert(r == "900150983cd24fb0d6963f7d"
                    "28e17f72");
        // the finalize zeroize (state+count+buf)
        for (int i = 0; i < 0x58; ++i)
            assert(ctx[i] == 0);
        // count: 3 bytes = 24 bits
        // (already zeroed - verified via ctx)
    }

    // ===== the bit-count mechanics =====
    {
        uint8_t ctx[MSG_MD5_CTX_SIZE];
        MsgMd5InitCtx(ctx);
        MsgMd5Update(ctx, "0123456789", 10);
        assert(*(uint32_t*)(ctx + 0x10) == 80);
        MsgMd5Update(ctx, "0123456789", 10);
        assert(*(uint32_t*)(ctx + 0x10) == 160);
        // the high word: 2^29 bytes would be
        // needed for the >> 29 path - just
        // verify the carry math symbolically:
        // count_hi increments when lo wraps
        uint8_t ctx2[MSG_MD5_CTX_SIZE];
        MsgMd5InitCtx(ctx2);
        *(uint32_t*)(ctx2 + 0x10) =
            0xfffffff8;   // 7 bytes used
        MsgMd5Update(ctx2, "0123456789abcde", 15);
        assert(*(uint32_t*)(ctx2 + 0x14) == 1);
    }

    // ===== the file hash (the LITERAL quirk) =====
    {
        MsgMd5FileSeams s;
        static uint8_t fileData[0x400];
        std::memcpy(fileData, "abc", 4);
        uint32_t uRead1 = 3, uRead2 = 0;
        bool bOpenOk = true;
        s.m_fnOpen = [&](const char* p, void** f,
                         const char* m) {
            assert(!strcmp(p, "some.dat"));
            assert(!strcmp(m, "rb"));
            *f = (void*)0x77;
            return bOpenOk ? 0 : 13; };
        s.m_fnRead = [&](void* b, void* f,
                         uint32_t n) {
            assert(f == (void*)0x77 && n == 0x400);
            if (uRead1) { std::memcpy(b, fileData,
                uRead1); uint32_t r = uRead1;
                uRead1 = uRead2; uRead2 = 0;
                return r; }
            return (uint32_t)0; };
        s.m_fnClose = [&](void* f) {
            assert(f == (void*)0x77); };
        // LITERAL: fopen_s success (==0) ->
        // returns NULL without hashing
        assert(MsgMd5OfFile("some.dat", s) ==
            nullptr);
        // failure (nonzero) -> hashes the reads
        bOpenOk = false; uRead1 = 3;
        std::string r = S(MsgMd5OfFile(
            "some.dat", s));
        assert(r == "900150983cd24fb0d6963f7d"
                    "28e17f72");   // md5("abc")
    }

    printf("MSG_MD5_SERVICE_OK: FUN_140507ab0 "
           "(the literal bit-count carry + the "
           "prev+0x7f chunk loop) + "
           "FUN_140507b80 (the DAT_140970230 "
           "padding, the 8 count bytes, the "
           "digest->+0x58, the full zeroize) + "
           "FUN_1405070a0 ('%%02x' x16 + strdup) "
           "+ FUN_140507ca0 (the inline strlen "
           "walk) + FUN_140507d30 (with the "
           "LITERAL fopen_s==0 -> NULL quirk) - "
           "validated against RFC/classic "
           "vectors incl. two multi-block cases "
           "and the chunked-update path\n");
    return 0;
}
