#pragma once
#include <cstdint>
#include <cstddef>

namespace tq {
// Standard SHA-1 (RFC 3174), used by the MySQL client auth scramble
class SHA1 {
public:
    static void Digest(const uint8_t* pData, size_t n, uint8_t out[20]);
};
}
