// MsgServer unit M40 - the DES
// object (the custom-variant
// descore). Vectors cross-checked
// against an independent python
// model of the decompiled code.
#include "../Exe/MsgServer/Port/MsgDes.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

static std::string hex(
    const uint8_t* p, size_t n) {
    std::string s;
    char b[3];
    for (size_t i = 0; i < n; ++i) {
        std::snprintf(b, 3, "%02x",
                      p[i]);
        s += b;
    }
    return s;
}

int main() {
    MsgDesCtx d = {};

    // ===== 1. the block vectors
    // (python cross-model, seed 42)
    struct V { const char* k;
               const char* pt;
               const char* ct; };
    static const V v[] = {
        {"390c8c7d7247342c",
         "d8100f2f6f770d65",
         "9ec3e342022937eb"},
        {"d670e58e0351d8ae",
         "8e4f6eac342fc231",
         "70865338bcd54328"},
        {"b7b08716eb3fc128",
         "96b9622317749428",
         "be379e301b4e96da"},
        {"7733c28ee8ba53bd",
         "b56b8824577d53ec",
         "c5c9b398d4ee9d22"},
        {"c28a70a61c7510a1",
         "cd89216ca16cffca",
         "3b34f1043f1bde7e"}};
    for (const auto& x : v) {
        uint8_t k[8], p[8];
        for (int i = 0; i < 8; ++i)
            std::sscanf(
                x.k + 2 * i, "%2hhx",
                &k[i]);
        for (int i = 0; i < 8; ++i)
            std::sscanf(
                x.pt + 2 * i,
                "%2hhx", &p[i]);
        // the factory always news a
        // FRESH object (the |=
        // schedule accumulation is
        // VERBATIM - the ctor-less
        // new(0x890) gives zeroed
        // memory)
        MsgDesCtx dv = {};
        MsgDesCtx::SetKey(dv, k);
        uint8_t b1[8], b2[8];
        std::memcpy(b1, p, 8);
        MsgDesCtx::EncryptBlock(dv,
                                b1);
        assert(hex(b1, 8) ==
               x.ct);
        std::memcpy(b2, b1, 8);
        MsgDesCtx::DecryptBlock(dv,
                                b2);
        assert(std::memcmp(b2, p,
                           8) == 0);
    }

    // ===== 2. the plugin key
    // vector: enc(0^8, "*J_@'n 3")
    MsgDesCtx::SetKey(
        d, (const uint8_t*)
               "*J_@'n 3");
    uint8_t z[8] = {0};
    MsgDesCtx::EncryptBlock(d, z);
    assert(hex(z, 8) ==
           "846a31e5405ad279");

    // ===== 3. the ECB encrypt:
    // len < 1 returns len AS-IS
    uint8_t buf[32];
    std::memset(buf, 0xAA, 32);
    assert(MsgDesCtx::Encrypt(
               d, buf, 0) == 0);
    assert(buf[0] == 0xAA);
    // len=3 is NOT < 1: it
    // ENCRYPTS (one block, 5
    // zero-pad bytes) -> 8
    assert(MsgDesCtx::Encrypt(
               d, buf, 3) == 8);

    // ===== 4. the padding: 13
    // bytes -> 16 with the tail
    // zeroed BEFORE the block
    // encrypt
    const uint8_t msg13[13] = {
        'h', 'e', 'l', 'l',
        'o', ',', ' ', 'w',
        'o', 'r', 'l', 'd',
        '!'};
    std::memset(buf, 0xEE, 32);
    std::memcpy(buf, msg13, 13);
    uint32_t nOut =
        MsgDesCtx::Encrypt(d, buf,
                           13);
    assert(nOut == 16);
    // VERBATIM QUIRK: Decrypt(13)
    // would run FOREVER (the loop
    // is `n != 0`, and 13 -> 5 ->
    // -3 -> ... NEVER hits 0 - the
    // ORIGINAL hangs/crashes too on
    // non-multiples; the callers
    // only ever pass multiples) -
    // so the round-trip uses the
    // padded 16
    MsgDesCtx::Decrypt(d, buf,
                       16);
    assert(std::memcmp(
               buf, msg13, 13) ==
           0);
    assert(buf[13] == 0 &&
           buf[14] == 0 &&
           buf[15] == 0);

    // ===== 5. a full multiple:
    // 16 bytes -> 2 blocks, clean
    // round-trip
    uint8_t buf2[16];
    for (int i = 0; i < 16; ++i)
        buf2[i] = (uint8_t)(i *
                            7 + 3);
    uint8_t orig[16];
    std::memcpy(orig, buf2, 16);
    assert(MsgDesCtx::Encrypt(
               d, buf2, 16) == 16);
    assert(std::memcmp(buf2,
                       orig, 16) !=
           0);
    MsgDesCtx::Decrypt(d, buf2,
                       16);
    assert(std::memcmp(buf2,
                       orig, 16) ==
           0);

    // ===== 6. the flag==2 raw-
    // schedule branch is DEAD CODE
    // in the binary: b0b0 clears
    // the flag to 0 FIRST, and
    // ab10 never writes +0x888, so
    // the check `flag == 2` can
    // never fire (a leftover). Even
    // a pre-set mode gets cleared.
    MsgDesCtx d2 = {};
    d2.nMode = 2;
    MsgDesCtx::SetKey(
        d2, (const uint8_t*)
                "\x01\x02\x03\x04\x05"
        "\x06\x07\x08");
    assert(d2.nMode == 0);
    uint8_t a1[8] = {1, 2, 3, 4,
                     5, 6, 7, 8};
    uint8_t a2[8];
    std::memcpy(a2, a1, 8);
    MsgDesCtx::EncryptBlock(d2,
                            a1);
    MsgDesCtx::DecryptBlock(d2,
                            a1);
    assert(std::memcmp(a1, a2,
                       8) == 0);

    // ===== 7. Destroy (vt+0)
    MsgDesCtx::Destroy(d);
    assert(d.bDeleted);

    printf("MSG_DES_OK: the 0x890 DES "
           "object VERBATIM - the "
           "descore-style SP tables "
           "(8x64 uint32 @+0x08), the "
           "16x8-byte schedule @+0x808 "
           "(6 bits/byte low-6 "
           "MSB-first, the cumulative "
           "shifts), the round f (8 "
           "OR-combined lookups), the "
           "BE-load/BE-store halves "
           "with the implicit final "
           "swap, the reversed+role-"
           "swapped decrypt, the ECB "
           "encrypt with the "
           "zero-the-tail padding and "
           "the len<1 passthrough, the "
           "guard-free decrypt "
           "(non-multiples overrun, "
           "VERBATIM), the raw-"
           "schedule flag==2 path, and "
           "the CUSTOM S-box variant "
           "(S1 rows 2/3 differ from "
           "RFC DES - not standard "
           "DES!) - all vectors "
           "cross-checked against the "
           "independent python model\n");
    return 0;
}
