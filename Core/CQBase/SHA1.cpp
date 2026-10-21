#include "SHA1.h"
#include <cstring>

namespace tq {

static uint32_t ROL(uint32_t v, int b) { return (v << b) | (v >> (32 - b)); }

void SHA1::Digest(const uint8_t* pData, size_t n, uint8_t out[20]) {
    uint32_t h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    uint64_t total = (uint64_t)n * 8;

    // padded message: data + 0x80 + zeros + 8-byte big-endian bit length
    size_t padded = ((n + 8) / 64 + 1) * 64;
    uint8_t* buf = new uint8_t[padded];
    std::memset(buf, 0, padded);
    std::memcpy(buf, pData, n);
    buf[n] = 0x80;
    for (int i = 0; i < 8; ++i)
        buf[padded - 1 - i] = (uint8_t)(total >> (8 * i));

    for (size_t off = 0; off < padded; off += 64) {
        uint32_t w[80];
        for (int i = 0; i < 16; ++i)
            w[i] = (uint32_t)buf[off + i * 4] << 24 | (uint32_t)buf[off + i * 4 + 1] << 16
                 | (uint32_t)buf[off + i * 4 + 2] << 8 | buf[off + i * 4 + 3];
        for (int i = 16; i < 80; ++i)
            w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i < 20)      { f = (b & c) | (~b & d);          k = 0x5A827999; }
            else if (i < 40) { f = b ^ c ^ d;                   k = 0x6ED9EBA1; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else             { f = b ^ c ^ d;                   k = 0xCA62C1D6; }
            uint32_t t = ROL(a, 5) + f + e + k + w[i];
            e = d; d = c; c = ROL(b, 30); b = a; a = t;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e;
    }
    delete[] buf;

    for (int i = 0; i < 5; ++i) {
        out[i * 4]     = (uint8_t)(h[i] >> 24);
        out[i * 4 + 1] = (uint8_t)(h[i] >> 16);
        out[i * 4 + 2] = (uint8_t)(h[i] >> 8);
        out[i * 4 + 3] = (uint8_t)h[i];
    }
}

}
