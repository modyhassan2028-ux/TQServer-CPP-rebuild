#include "MsgMd5.h"
#include <cstring>

namespace msg {

void MsgMd5Transform(uint32_t state[4],
                     const uint8_t* pBlock) {
    uint32_t x[16];
    // the unaligned little-endian word load
    for (int i = 0; i < 16; ++i)
        std::memcpy(&x[i], pBlock + i * 4, 4);

    uint32_t vA0 = state[0];   // iVar1
    uint32_t vB = state[1];    // uVar9
    uint32_t vC = state[2];    // uVar7
    uint32_t vD = state[3];    // uVar4
    uint32_t vT = 0, vT2 = 0;  // uVar2/uVar5

    // ===== round 1 (F) =====
    vT = (~vB & vD | vC & vB) + x[0] + -0x28955b88 + vA0;
    vT = (vT * 0x80 | vT >> 0x19) + vB;
    vD = (~vT & vC | vB & vT) + x[1] + -0x173848aa + vD;
    vD = (vD * 0x1000 | vD >> 0x14) + vT;
    vC = (~vD & vB | vD & vT) + x[2] + 0x242070db + vC;
    vC = (vC >> 0xf | vC * 0x20000) + vD;
    vB = (~vC & vT | vD & vC) + x[3] + -0x3e423112 + vB;
    vB = (vB >> 10 | vB * 0x400000) + vC;
    vT = (~vB & vD | vC & vB) + x[4] + -0xa83f051 + vT;
    vT = (vT * 0x80 | vT >> 0x19) + vB;
    vD = (~vT & vC | vB & vT) + x[5] + 0x4787c62a + vD;
    vD = (vD * 0x1000 | vD >> 0x14) + vT;
    vC = (~vD & vB | vD & vT) + x[6] + -0x57cfb9ed + vC;
    vC = (vC >> 0xf | vC * 0x20000) + vD;
    vB = (~vC & vT | vD & vC) + x[7] + -0x2b96aff + vB;
    vB = (vB >> 10 | vB * 0x400000) + vC;
    vT = (~vB & vD | vC & vB) + x[8] + 0x698098d8 + vT;
    vT = (vT * 0x80 | vT >> 0x19) + vB;
    vD = (~vT & vC | vB & vT) + x[9] + -0x74bb0851 + vD;
    vD = (vD * 0x1000 | vD >> 0x14) + vT;
    vC = (~vD & vB | vD & vT) + x[10] + -0xa44f + vC;
    vC = (vC >> 0xf | vC * 0x20000) + vD;
    vB = (~vC & vT | vD & vC) + x[11] + -0x76a32842 + vB;
    vB = (vB >> 10 | vB * 0x400000) + vC;
    vT = (~vB & vD | vC & vB) + x[12] + 0x6b901122 + vT;
    vT = (vT * 0x80 | vT >> 0x19) + vB;
    vD = (~vT & vC | vB & vT) + x[13] + -0x2678e6d + vD;
    vD = (vD * 0x1000 | vD >> 0x14) + vT;
    vC = (~vD & vB | vD & vT) + x[14] + -0x5986bc72 + vC;
    vC = (vC >> 0xf | vC * 0x20000) + vD;
    vB = (~vC & vT | vD & vC) + x[15] + 0x49b40821 + vB;
    vB = (vB >> 10 | vB * 0x400000) + vC;
    // ===== round 2 (G) =====
    vT = (~vD & vC | vD & vB) + x[1] + -0x9e1da9e + vT;
    vT = (vT * 0x20 | vT >> 0x1b) + vB;
    vD = (~vC & vB | vC & vT) + x[6] + -0x3fbf4cc0 + vD;
    vD = (vD * 0x200 | vD >> 0x17) + vT;
    vC = (~vB & vT | vD & vB) + x[11] + 0x265e5a51 + vC;
    vC = (vC * 0x4000 | vC >> 0x12) + vD;
    vB = (~vT & vD | vC & vT) + x[0] + -0x16493856 + vB;
    vB = (vB >> 0xc | vB * 0x100000) + vC;
    vT = (~vD & vC | vD & vB) + x[5] + -0x29d0efa3 + vT;
    vT = (vT * 0x20 | vT >> 0x1b) + vB;
    vD = (~vC & vB | vC & vT) + x[10] + 0x2441453 + vD;
    vD = (vD * 0x200 | vD >> 0x17) + vT;
    vC = (~vB & vT | vD & vB) + x[15] + -0x275e197f + vC;
    vC = (vC * 0x4000 | vC >> 0x12) + vD;
    vB = (~vT & vD | vC & vT) + x[4] + -0x182c0438 + vB;
    vB = (vB >> 0xc | vB * 0x100000) + vC;
    vT = (~vD & vC | vD & vB) + x[9] + 0x21e1cde6 + vT;
    vT = (vT * 0x20 | vT >> 0x1b) + vB;
    vD = (~vC & vB | vC & vT) + x[14] + -0x3cc8f82a + vD;
    vD = (vD * 0x200 | vD >> 0x17) + vT;
    vC = (~vB & vT | vD & vB) + x[3] + -0xb2af279 + vC;
    vC = (vC * 0x4000 | vC >> 0x12) + vD;
    vB = (~vT & vD | vC & vT) + x[8] + 0x455a14ed + vB;
    vB = (vB >> 0xc | vB * 0x100000) + vC;
    vT = (~vD & vC | vD & vB) + x[13] + -0x561c16fb + vT;
    vT = (vT * 0x20 | vT >> 0x1b) + vB;
    vD = (~vC & vB | vC & vT) + x[2] + -0x3105c08 + vD;
    vD = (vD * 0x200 | vD >> 0x17) + vT;
    vC = (~vB & vT | vD & vB) + x[7] + 0x676f02d9 + vC;
    vC = (vC * 0x4000 | vC >> 0x12) + vD;
    vB = (~vT & vD | vC & vT) + x[12] + -0x72d5b376 + vB;
    vB = (vB >> 0xc | vB * 0x100000) + vC;
    // ===== round 3 (H) =====
    vT = (vD ^ vC ^ vB) + x[5] + -0x5c6be + vT;
    vT = (vT * 0x10 | vT >> 0x1c) + vB;
    vD = (vC ^ vB ^ vT) + x[8] + -0x788e097f + vD;
    vD = (vD * 0x800 | vD >> 0x15) + vT;
    vC = (vD ^ vB ^ vT) + x[11] + 0x6d9d6122 + vC;
    vC = (vC * 0x10000 | vC >> 0x10) + vD;
    vB = (vD ^ vC ^ vT) + x[14] + -0x21ac7f4 + vB;
    vB = (vB >> 9 | vB * 0x800000) + vC;
    vT = (vD ^ vC ^ vB) + x[1] + -0x5b4115bc + vT;
    vT = (vT * 0x10 | vT >> 0x1c) + vB;
    vD = (vC ^ vB ^ vT) + x[4] + 0x4bdecfa9 + vD;
    vD = (vD * 0x800 | vD >> 0x15) + vT;
    vC = (vD ^ vB ^ vT) + x[7] + -0x944b4a0 + vC;
    vC = (vC * 0x10000 | vC >> 0x10) + vD;
    vB = (vD ^ vC ^ vT) + x[10] + -0x41404390 + vB;
    vB = (vB >> 9 | vB * 0x800000) + vC;
    vT = (vD ^ vC ^ vB) + x[13] + 0x289b7ec6 + vT;
    vT = (vT * 0x10 | vT >> 0x1c) + vB;
    vD = (vC ^ vB ^ vT) + x[0] + -0x155ed806 + vD;
    vD = (vD * 0x800 | vD >> 0x15) + vT;
    vC = (vD ^ vB ^ vT) + x[3] + -0x2b10cf7b + vC;
    vC = (vC * 0x10000 | vC >> 0x10) + vD;
    vB = (vD ^ vC ^ vT) + x[6] + 0x4881d05 + vB;
    vB = (vB >> 9 | vB * 0x800000) + vC;
    vT = (vD ^ vC ^ vB) + x[9] + -0x262b2fc7 + vT;
    vT = (vT * 0x10 | vT >> 0x1c) + vB;
    vD = (vC ^ vB ^ vT) + x[12] + -0x1924661b + vD;
    vD = (vD * 0x800 | vD >> 0x15) + vT;
    vC = (vD ^ vB ^ vT) + x[15] + 0x1fa27cf8 + vC;
    vC = (vC * 0x10000 | vC >> 0x10) + vD;
    vB = (vD ^ vC ^ vT) + x[2] + -0x3b53a99b + vB;
    vB = (vB >> 9 | vB * 0x800000) + vC;
    // ===== round 4 (I) =====
    vT = ((~vD | vB) ^ vC) + x[0] + -0xbd6ddbc + vT;
    vT = (vT * 0x40 | vT >> 0x1a) + vB;
    vD = ((~vC | vT) ^ vB) + x[7] + 0x432aff97 + vD;
    vD = (vD * 0x400 | vD >> 0x16) + vT;
    vC = ((~vB | vD) ^ vT) + x[14] + -0x546bdc59 + vC;
    vC = (vC * 0x8000 | vC >> 0x11) + vD;
    vB = ((~vT | vC) ^ vD) + x[5] + -0x36c5fc7 + vB;
    vB = (vB >> 0xb | vB * 0x200000) + vC;
    vT = ((~vD | vB) ^ vC) + x[12] + 0x655b59c3 + vT;
    vT = (vT * 0x40 | vT >> 0x1a) + vB;
    vD = ((~vC | vT) ^ vB) + x[3] + -0x70f3336e + vD;
    vD = (vD * 0x400 | vD >> 0x16) + vT;
    vC = ((~vB | vD) ^ vT) + x[10] + -0x100b83 + vC;
    vC = (vC * 0x8000 | vC >> 0x11) + vD;
    vB = ((~vT | vC) ^ vD) + x[1] + -0x7a7ba22f + vB;
    vB = (vB >> 0xb | vB * 0x200000) + vC;
    vT = ((~vD | vB) ^ vC) + x[8] + 0x6fa87e4f + vT;
    vT = (vT * 0x40 | vT >> 0x1a) + vB;
    vD = ((~vC | vT) ^ vB) + x[15] + -0x1d31920 + vD;
    vD = (vD * 0x400 | vD >> 0x16) + vT;
    vC = ((~vB | vD) ^ vT) + x[6] + -0x5cfebcec + vC;
    vC = (vC * 0x8000 | vC >> 0x11) + vD;
    vB = ((~vT | vC) ^ vD) + x[13] + 0x4e0811a1 + vB;
    vB = (vB >> 0xb | vB * 0x200000) + vC;
    // ===== the last steps + tail (LITERAL) =====
    vT = ((~vD | vB) ^ vC) + x[4] + -0x8ac817e + vT;
    vT2 = (vT * 0x40 | vT >> 0x1a) + vB;
    vD = ((~vC | vT2) ^ vB) + x[11] + -0x42c50dcb + vD;
    vT = (vD * 0x400 | vD >> 0x16) + vT2;
    vC = ((~vB | vT) ^ vT2) + x[2] + 0x2ad7d2bb + vC;
    vD = (vC * 0x8000 | vC >> 0x11) + vT;
    state[0] = vA0 + vT2;
    vB = ((~vT2 | vD) ^ vT) + x[9] + -0x14792c6f + vB;
    state[1] = (vB >> 0xb | vB * 0x200000) + state[1] + vD;
    state[2] = state[2] + vD;
    state[3] = state[3] + vT;
}

} // namespace msg
