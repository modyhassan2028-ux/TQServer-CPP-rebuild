// synthunks_gr.h — RAW Syndicate.dll v6159 · 32 tail-forwarders (family GR).
// The displacement the original splits between `lea` and `add` is summed here; rbp only carries arg2.
#ifndef TQ_SYN_THUNKS_GR_H
#define TQ_SYN_THUNKS_GR_H

#include <cstdint>

namespace tq {

extern void* (*g_fnGR_141727880)(void* pArg);
extern void* (*g_fnGR_141731c00)(void* pArg);
extern void* (*g_fnGR_14173db90)(void* pArg);
extern void* (*g_fnGR_141740c20)(void* pArg);
extern void* (*g_fnGR_14176f350)(void* pArg);
extern void* (*g_fnGR_14178d7f0)(void* pArg);

inline void* SynFwdTail_1417fac10(void* pThis, void* pRec) {   // 0x1417fac10  +0x68 (lea 0x60 then add 0x8)
    (void)pThis;
    return g_fnGR_141727880((uint8_t*)pRec + 0x68);   // insn 3-5
}
inline void* SynFwdTail_1417fac50(void* pThis, void* pRec) {   // 0x1417fac50  +0x68 (lea 0x60 then add 0x8)
    (void)pThis;
    return g_fnGR_141727880((uint8_t*)pRec + 0x68);   // insn 3-5
}
inline void* SynFwdTail_1417fd570(void* pThis, void* pRec) {   // 0x1417fd570  +0xa0 (lea 0x98 then add 0x8)
    (void)pThis;
    return g_fnGR_14173db90((uint8_t*)pRec + 0xa0);   // insn 3-5
}
inline void* SynFwdTail_1417fd5b0(void* pThis, void* pRec) {   // 0x1417fd5b0  +0xa0 (lea 0x98 then add 0x8)
    (void)pThis;
    return g_fnGR_14173db90((uint8_t*)pRec + 0xa0);   // insn 3-5
}
inline void* SynFwdTail_1417fe280(void* pThis, void* pRec) {   // 0x1417fe280  +0x58 (lea 0x40 then add 0x18)
    (void)pThis;
    return g_fnGR_141740c20((uint8_t*)pRec + 0x58);   // insn 3-5
}
inline void* SynFwdTail_1417fe2e0(void* pThis, void* pRec) {   // 0x1417fe2e0  +0x58 (lea 0x40 then add 0x18)
    (void)pThis;
    return g_fnGR_141740c20((uint8_t*)pRec + 0x58);   // insn 3-5
}
inline void* SynFwdTail_141807530(void* pThis, void* pRec) {   // 0x141807530  +0x158 (lea 0x150 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x158);   // insn 3-5
}
inline void* SynFwdTail_141807570(void* pThis, void* pRec) {   // 0x141807570  +0x158 (lea 0x150 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x158);   // insn 3-5
}
inline void* SynFwdTail_141807650(void* pThis, void* pRec) {   // 0x141807650  +0x1f8 (lea 0x1f0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x1f8);   // insn 3-5
}
inline void* SynFwdTail_141807a10(void* pThis, void* pRec) {   // 0x141807a10  +0x158 (lea 0x150 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x158);   // insn 3-5
}
inline void* SynFwdTail_141807a50(void* pThis, void* pRec) {   // 0x141807a50  +0x158 (lea 0x150 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x158);   // insn 3-5
}
inline void* SynFwdTail_141807b30(void* pThis, void* pRec) {   // 0x141807b30  +0x1f8 (lea 0x1f0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x1f8);   // insn 3-5
}
inline void* SynFwdTail_141808030(void* pThis, void* pRec) {   // 0x141808030  +0x670 (lea 0x668 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x670);   // insn 3-5
}
inline void* SynFwdTail_141808070(void* pThis, void* pRec) {   // 0x141808070  +0x670 (lea 0x668 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x670);   // insn 3-5
}
inline void* SynFwdTail_141808150(void* pThis, void* pRec) {   // 0x141808150  +0x7a8 (lea 0x7a0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x7a8);   // insn 3-5
}
inline void* SynFwdTail_141808470(void* pThis, void* pRec) {   // 0x141808470  +0x5e0 (lea 0x5d8 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x5e0);   // insn 3-5
}
inline void* SynFwdTail_1418084b0(void* pThis, void* pRec) {   // 0x1418084b0  +0x5e0 (lea 0x5d8 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x5e0);   // insn 3-5
}
inline void* SynFwdTail_141808590(void* pThis, void* pRec) {   // 0x141808590  +0x880 (lea 0x878 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x880);   // insn 3-5
}
inline void* SynFwdTail_1418088d0(void* pThis, void* pRec) {   // 0x1418088d0  +0x628 (lea 0x620 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x628);   // insn 3-5
}
inline void* SynFwdTail_141808910(void* pThis, void* pRec) {   // 0x141808910  +0x628 (lea 0x620 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x628);   // insn 3-5
}
inline void* SynFwdTail_1418089f0(void* pThis, void* pRec) {   // 0x1418089f0  +0x7f0 (lea 0x7e8 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x7f0);   // insn 3-5
}
inline void* SynFwdTail_141808c30(void* pThis, void* pRec) {   // 0x141808c30  +0x6b8 (lea 0x6b0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x6b8);   // insn 3-5
}
inline void* SynFwdTail_141808c70(void* pThis, void* pRec) {   // 0x141808c70  +0x6b8 (lea 0x6b0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x6b8);   // insn 3-5
}
inline void* SynFwdTail_141808d50(void* pThis, void* pRec) {   // 0x141808d50  +0x838 (lea 0x830 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x838);   // insn 3-5
}
inline void* SynFwdTail_141808fb0(void* pThis, void* pRec) {   // 0x141808fb0  +0x598 (lea 0x590 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x598);   // insn 3-5
}
inline void* SynFwdTail_141808ff0(void* pThis, void* pRec) {   // 0x141808ff0  +0x598 (lea 0x590 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x598);   // insn 3-5
}
inline void* SynFwdTail_1418090d0(void* pThis, void* pRec) {   // 0x1418090d0  +0x8c8 (lea 0x8c0 then add 0x8)
    (void)pThis;
    return g_fnGR_141731c00((uint8_t*)pRec + 0x8c8);   // insn 3-5
}
inline void* SynFwdTail_1418097f0(void* pThis, void* pRec) {   // 0x1418097f0  +0xe0 (lea 0xd8 then add 0x8)
    (void)pThis;
    return g_fnGR_14176f350((uint8_t*)pRec + 0xe0);   // insn 3-5
}
inline void* SynFwdTail_141809830(void* pThis, void* pRec) {   // 0x141809830  +0xe0 (lea 0xd8 then add 0x8)
    (void)pThis;
    return g_fnGR_14176f350((uint8_t*)pRec + 0xe0);   // insn 3-5
}
inline void* SynFwdTail_141809910(void* pThis, void* pRec) {   // 0x141809910  +0x128 (lea 0x120 then add 0x8)
    (void)pThis;
    return g_fnGR_14176f350((uint8_t*)pRec + 0x128);   // insn 3-5
}
inline void* SynFwdTail_1418128b0(void* pThis, void* pRec) {   // 0x1418128b0  +0xc0 (lea 0xb8 then add 0x8)
    (void)pThis;
    return g_fnGR_14178d7f0((uint8_t*)pRec + 0xc0);   // insn 3-5
}
inline void* SynFwdTail_1418128f0(void* pThis, void* pRec) {   // 0x1418128f0  +0xc0 (lea 0xb8 then add 0x8)
    (void)pThis;
    return g_fnGR_14178d7f0((uint8_t*)pRec + 0xc0);   // insn 3-5
}

}  // namespace tq

#endif
