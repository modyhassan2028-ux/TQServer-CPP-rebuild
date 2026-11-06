// synthunks_n.h — RAW Syndicate.dll v6159 · families L2 and N.
//   L2: the reporter with a frame size other than 0x20 (tail jump verified onto the epilogue)
//   N:  copy two qwords into the destination, call the target with (source, destination),
//       then answer the destination
#ifndef TQ_SYN_THUNKS_N_H
#define TQ_SYN_THUNKS_N_H

#include <cstdint>

namespace tq {

extern void (*g_fnRep2_141823038)(void* pA, void* pB, uint32_t nLine, void* pFourth);
extern void* (*g_fnN2_141722ef0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141722fc0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141723090)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141723a50)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141724ed0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417250d0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_14173b240)(void* pSrc, void* pDst);
extern void* (*g_fnN2_14173b6c0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417447d0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141744cb0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141750670)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141750760)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417512f0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141751380)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141753470)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141753500)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141753620)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417536b0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141753d70)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141754000)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141776460)(void* pSrc, void* pDst);
extern void* (*g_fnN2_14177a5c0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417899e0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141789d70)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141790e10)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141791080)(void* pSrc, void* pDst);
extern void* (*g_fnN2_141792240)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417a70b0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417c63c0)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417c6580)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417c6610)(void* pSrc, void* pDst);
extern void* (*g_fnN2_1417c6e80)(void* pSrc, void* pDst);

inline void* SynLit2_1417f9730(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f9730
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0x6aa, a4);
    return (void*)0x141732c1a;
}
inline void* SynLit2_1417f9770(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f9770
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0x6cb, a4);
    return (void*)0x141732e5d;
}
inline void* SynLit2_1417f97b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f97b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0x6cd, a4);
    return (void*)0x141732e87;
}
inline void* SynLit2_1417fafe0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fafe0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0xe7, a4);
    return (void*)0x1417365c6;
}
inline void* SynLit2_1417fb020(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fb020
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0xfd, a4);
    return (void*)0x141736836;
}
inline void* SynLit2_1417fb060(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fb060
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141824e30, 0x121, a4);
    return (void*)0x141736b96;
}
inline void* SynLit2_1417fc3c0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fc3c0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141827cc8, (void*)0x141827bb0, 0x7a, a4);
    return (void*)0x14173dcee;
}
inline void* SynLit2_1417fe0f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fe0f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828540, 0x53, a4);
    return (void*)0x1417427e5;
}
inline void* SynLit2_1417ff070(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff070
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x75, a4);
    return (void*)0x14174a9b0;
}
inline void* SynLit2_1417ff0b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff0b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x77, a4);
    return (void*)0x14174a9fa;
}
inline void* SynLit2_1417ff170(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff170
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x86, a4);
    return (void*)0x14174ab11;
}
inline void* SynLit2_1417ff1f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff1f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x96, a4);
    return (void*)0x14174ac75;
}
inline void* SynLit2_1417ff230(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff230
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x9c, a4);
    return (void*)0x14174ace6;
}
inline void* SynLit2_1417ff310(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff310
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0xdc, a4);
    return (void*)0x14174af4b;
}
inline void* SynLit2_1417ff350(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff350
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0xe2, a4);
    return (void*)0x14174afad;
}
inline void* SynLit2_1417ff3b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff3b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x2b8, a4);
    return (void*)0x14174b862;
}
inline void* SynLit2_1417ff3f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff3f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x2d3, a4);
    return (void*)0x14174ba67;
}
inline void* SynLit2_1417ff430(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff430
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x310, a4);
    return (void*)0x14174bdd7;
}
inline void* SynLit2_1417ff470(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff470
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x316, a4);
    return (void*)0x14174bdf3;
}
inline void* SynLit2_1417ff4b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff4b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x367, a4);
    return (void*)0x14174c298;
}
inline void* SynLit2_1417ff4f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417ff4f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x374, a4);
    return (void*)0x14174c3c0;
}
inline void* SynLit2_1417fff80(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fff80
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0x21, a4);
    return (void*)0x14174d9d8;
}
inline void* SynLit2_141800020(void* a1, void* a2, void* a3, void* a4) {   // 0x141800020
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141828950, 0xb3, a4);
    return (void*)0x14174dc73;
}
inline void* SynLit2_141803770(void* a1, void* a2, void* a3, void* a4) {   // 0x141803770
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x2b4, a4);
    return (void*)0x141763804;
}
inline void* SynLit2_1418037b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418037b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x2c6, a4);
    return (void*)0x1417638b7;
}
inline void* SynLit2_141803890(void* a1, void* a2, void* a3, void* a4) {   // 0x141803890
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182b968, (void*)0x1418297c0, 0xb4a, a4);
    return (void*)0x141765d46;
}
inline void* SynLit2_1418038d0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418038d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182baa8, (void*)0x1418297c0, 0xb9d, a4);
    return (void*)0x141765fef;
}
inline void* SynLit2_141806310(void* a1, void* a2, void* a3, void* a4) {   // 0x141806310
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x109, a4);
    return (void*)0x14176f8bd;
}
inline void* SynLit2_141806350(void* a1, void* a2, void* a3, void* a4) {   // 0x141806350
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x112, a4);
    return (void*)0x14176f924;
}
inline void* SynLit2_14180c170(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c170
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182d540, 0x30, a4);
    return (void*)0x141779aed;
}
inline void* SynLit2_14180c1b0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c1b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182d540, 0x38, a4);
    return (void*)0x141779b11;
}
inline void* SynLit2_14180c940(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c940
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x14182db40, 0x3f, a4);
    return (void*)0x14177c45a;
}
inline void* SynLit2_14180d120(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d120
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182de70, 0x46, a4);
    return (void*)0x14177d59f;
}
inline void* SynLit2_14180d160(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d160
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182de70, 0x4d, a4);
    return (void*)0x14177d5c9;
}
inline void* SynLit2_14180d800(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d800
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182e620, 0xcf, a4);
    return (void*)0x14177ed1b;
}
inline void* SynLit2_14180d840(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d840
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182e7c8, (void*)0x14182e750, 0xb8, a4);
    return (void*)0x14177f0af;
}
inline void* SynLit2_14180d880(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d880
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182e750, 0xdb, a4);
    return (void*)0x14177f218;
}
inline void* SynLit2_14180d9b0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d9b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14182e750, 0x46, a4);
    return (void*)0x14177f551;
}
inline void* SynLit2_14180e100(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e100
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182ff68, (void*)0x14182ed30, 0x37d, a4);
    return (void*)0x141784cbe;
}
inline void* SynLit2_14180e5f0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e5f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418302d0, 0x9c, a4);
    return (void*)0x141785cdd;
}
inline void* SynLit2_14180e730(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e730
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x1418302d0, 0x8f, a4);
    return (void*)0x141788024;
}
inline void* SynLit2_14180f350(void* a1, void* a2, void* a3, void* a4) {   // 0x14180f350
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141830e10, 0x5c, a4);
    return (void*)0x14178d259;
}
inline void* SynLit2_14180f410(void* a1, void* a2, void* a3, void* a4) {   // 0x14180f410
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141830e10, 0x64, a4);
    return (void*)0x14178d30f;
}
inline void* SynLit2_14180f450(void* a1, void* a2, void* a3, void* a4) {   // 0x14180f450
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141830e10, 0xc5, a4);
    return (void*)0x14178d401;
}
inline void* SynLit2_14180f510(void* a1, void* a2, void* a3, void* a4) {   // 0x14180f510
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418315e8, (void*)0x141830e10, 0xd0, a4);
    return (void*)0x14178d4a6;
}
inline void* SynLit2_141810ed0(void* a1, void* a2, void* a3, void* a4) {   // 0x141810ed0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418323d0, (void*)0x1418319b0, 0x29d, a4);
    return (void*)0x141797cca;
}
inline void* SynLit2_141810f70(void* a1, void* a2, void* a3, void* a4) {   // 0x141810f70
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418326c0, (void*)0x1418319b0, 0xc9e, a4);
    return (void*)0x141798e55;
}
inline void* SynLit2_141812b90(void* a1, void* a2, void* a3, void* a4) {   // 0x141812b90
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141833e00, (void*)0x1418319b0, 0x366, a4);
    return (void*)0x1417a09fd;
}
inline void* SynLit2_1418156e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418156e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141835bd0, 0xca, a4);
    return (void*)0x1417a9ea4;
}
inline void* SynLit2_141815720(void* a1, void* a2, void* a3, void* a4) {   // 0x141815720
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141835bd0, 0xd0, a4);
    return (void*)0x1417a9ebe;
}
inline void* SynLit2_141815800(void* a1, void* a2, void* a3, void* a4) {   // 0x141815800
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141835cd8, (void*)0x141835bd0, 0x11f, a4);
    return (void*)0x1417aa14d;
}
inline void* SynLit2_1418158a0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418158a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141835e48, (void*)0x141835bd0, 0x3c3, a4);
    return (void*)0x1417aa8dd;
}
inline void* SynLit2_1418158e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418158e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141835f78, (void*)0x141835bd0, 0x3ff, a4);
    return (void*)0x1417aab3d;
}
inline void* SynLit2_141815940(void* a1, void* a2, void* a3, void* a4) {   // 0x141815940
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836068, (void*)0x141835bd0, 0x4bd, a4);
    return (void*)0x1417aaf6b;
}
inline void* SynLit2_1418159c0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418159c0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836158, (void*)0x141835bd0, 0x674, a4);
    return (void*)0x1417ab5d9;
}
inline void* SynLit2_141815a00(void* a1, void* a2, void* a3, void* a4) {   // 0x141815a00
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836218, (void*)0x141835bd0, 0x6ed, a4);
    return (void*)0x1417ab896;
}
inline void* SynLit2_141815a40(void* a1, void* a2, void* a3, void* a4) {   // 0x141815a40
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418362d8, (void*)0x141835bd0, 0x71e, a4);
    return (void*)0x1417aba9b;
}
inline void* SynLit2_141815a80(void* a1, void* a2, void* a3, void* a4) {   // 0x141815a80
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418363b8, (void*)0x141835bd0, 0x781, a4);
    return (void*)0x1417abbf5;
}
inline void* SynLit2_141815ac0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815ac0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836438, (void*)0x141835bd0, 0x7ee, a4);
    return (void*)0x1417abe39;
}
inline void* SynLit2_141815b00(void* a1, void* a2, void* a3, void* a4) {   // 0x141815b00
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836498, (void*)0x141835bd0, 0x94c, a4);
    return (void*)0x1417ac40b;
}
inline void* SynLit2_141815b80(void* a1, void* a2, void* a3, void* a4) {   // 0x141815b80
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836588, (void*)0x141835bd0, 0xcc3, a4);
    return (void*)0x1417ac98f;
}
inline void* SynLit2_141815bc0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815bc0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418365f8, (void*)0x141835bd0, 0xd77, a4);
    return (void*)0x1417acc54;
}
inline void* SynLit2_141815c20(void* a1, void* a2, void* a3, void* a4) {   // 0x141815c20
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418366b8, (void*)0x141835bd0, 0xda2, a4);
    return (void*)0x1417acd83;
}
inline void* SynLit2_141815ca0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815ca0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836718, (void*)0x141835bd0, 0xe16, a4);
    return (void*)0x1417ad166;
}
inline void* SynLit2_141815d20(void* a1, void* a2, void* a3, void* a4) {   // 0x141815d20
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418367c8, (void*)0x141835bd0, 0xf16, a4);
    return (void*)0x1417ad768;
}
inline void* SynLit2_141815da0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815da0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836998, (void*)0x141835bd0, 0xf7b, a4);
    return (void*)0x1417adb84;
}
inline void* SynLit2_141815e20(void* a1, void* a2, void* a3, void* a4) {   // 0x141815e20
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836b18, (void*)0x141835bd0, 0xfcb, a4);
    return (void*)0x1417ade85;
}
inline void* SynLit2_141815e80(void* a1, void* a2, void* a3, void* a4) {   // 0x141815e80
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836b98, (void*)0x141835bd0, 0x1061, a4);
    return (void*)0x1417ae0fb;
}
inline void* SynLit2_141815ee0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815ee0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836c38, (void*)0x141835bd0, 0x10b7, a4);
    return (void*)0x1417ae369;
}
inline void* SynLit2_141815f60(void* a1, void* a2, void* a3, void* a4) {   // 0x141815f60
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836ce8, (void*)0x141835bd0, 0x10fd, a4);
    return (void*)0x1417ae5fc;
}
inline void* SynLit2_141816000(void* a1, void* a2, void* a3, void* a4) {   // 0x141816000
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836e98, (void*)0x141835bd0, 0x129c, a4);
    return (void*)0x1417af022;
}
inline void* SynLit2_141816040(void* a1, void* a2, void* a3, void* a4) {   // 0x141816040
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141836fc8, (void*)0x141835bd0, 0x1312, a4);
    return (void*)0x1417af20c;
}
inline void* SynLit2_1418162a0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418162a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141837708, (void*)0x141835bd0, 0x1fe7, a4);
    return (void*)0x1417b2dcb;
}
inline void* SynLit2_1418164e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418164e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141837e38, (void*)0x141835bd0, 0x217, a4);
    return (void*)0x1417b64b2;
}
inline void* SynLit2_141816520(void* a1, void* a2, void* a3, void* a4) {   // 0x141816520
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141837ee8, (void*)0x141835bd0, 0x271, a4);
    return (void*)0x1417b6600;
}
inline void* SynLit2_141816560(void* a1, void* a2, void* a3, void* a4) {   // 0x141816560
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141837f48, (void*)0x141835bd0, 0x2bb, a4);
    return (void*)0x1417b6748;
}
inline void* SynLit2_1418165e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418165e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141837fa8, (void*)0x141835bd0, 0x311, a4);
    return (void*)0x1417b6a84;
}
inline void* SynLit2_141816640(void* a1, void* a2, void* a3, void* a4) {   // 0x141816640
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838058, (void*)0x141835bd0, 0x35e, a4);
    return (void*)0x1417b6dc8;
}
inline void* SynLit2_141816760(void* a1, void* a2, void* a3, void* a4) {   // 0x141816760
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838148, (void*)0x141835bd0, 0xb1b, a4);
    return (void*)0x1417b7816;
}
inline void* SynLit2_1418167c0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418167c0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838228, (void*)0x141835bd0, 0xd13, a4);
    return (void*)0x1417b7abf;
}
inline void* SynLit2_141816820(void* a1, void* a2, void* a3, void* a4) {   // 0x141816820
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838318, (void*)0x141835bd0, 0xe37, a4);
    return (void*)0x1417b7bee;
}
inline void* SynLit2_1418168a0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418168a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838378, (void*)0x141835bd0, 0xe83, a4);
    return (void*)0x1417b7e47;
}
inline void* SynLit2_141816920(void* a1, void* a2, void* a3, void* a4) {   // 0x141816920
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418383d8, (void*)0x141835bd0, 0x1016, a4);
    return (void*)0x1417b8125;
}
inline void* SynLit2_141816960(void* a1, void* a2, void* a3, void* a4) {   // 0x141816960
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838458, (void*)0x141835bd0, 0x1196, a4);
    return (void*)0x1417b8449;
}
inline void* SynLit2_1418169a0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418169a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418384d8, (void*)0x141835bd0, 0x12d1, a4);
    return (void*)0x1417b85fc;
}
inline void* SynLit2_1418169e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418169e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838538, (void*)0x141835bd0, 0x155c, a4);
    return (void*)0x1417b8913;
}
inline void* SynLit2_141816ae0(void* a1, void* a2, void* a3, void* a4) {   // 0x141816ae0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838978, (void*)0x141835bd0, 0x741, a4);
    return (void*)0x1417ba6dc;
}
inline void* SynLit2_141816ba0(void* a1, void* a2, void* a3, void* a4) {   // 0x141816ba0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x1418389e8, (void*)0x141835bd0, 0xa2d, a4);
    return (void*)0x1417bad1e;
}
inline void* SynLit2_141816c00(void* a1, void* a2, void* a3, void* a4) {   // 0x141816c00
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838ac8, (void*)0x141835bd0, 0xc0e, a4);
    return (void*)0x1417bb0ad;
}
inline void* SynLit2_141816c80(void* a1, void* a2, void* a3, void* a4) {   // 0x141816c80
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838b58, (void*)0x141835bd0, 0xc89, a4);
    return (void*)0x1417bb4d1;
}
inline void* SynLit2_141816cc0(void* a1, void* a2, void* a3, void* a4) {   // 0x141816cc0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141838bc8, (void*)0x141835bd0, 0xd35, a4);
    return (void*)0x1417bb5cd;
}
inline void* SynLit2_141817ad0(void* a1, void* a2, void* a3, void* a4) {   // 0x141817ad0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141839088, (void*)0x141835bd0, 0x1f76, a4);
    return (void*)0x1417bed4c;
}
inline void* SynLit2_141818b00(void* a1, void* a2, void* a3, void* a4) {   // 0x141818b00
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141839518, (void*)0x141835bd0, 0x2096, a4);
    return (void*)0x1417c243a;
}
inline void* SynLit2_1418193f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418193f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839b40, 0x81, a4);
    return (void*)0x1417c48ad;
}
inline void* SynLit2_141819530(void* a1, void* a2, void* a3, void* a4) {   // 0x141819530
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839cd0, 0x9f, a4);
    return (void*)0x1417c509d;
}
inline void* SynLit2_1418196b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418196b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183a098, (void*)0x141839fe0, 0x374, a4);
    return (void*)0x1417c57ff;
}
inline void* SynLit2_1418197b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418197b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183a098, (void*)0x141839fe0, 0x32f, a4);
    return (void*)0x1417c6b0c;
}
inline void* SynLit2_1418197f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418197f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183a098, (void*)0x141839fe0, 0x33e, a4);
    return (void*)0x1417c6bb2;
}
inline void* SynLit2_14181a2d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a2d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x3fa, a4);
    return (void*)0x1417cb338;
}
inline void* SynLit2_14181a310(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a310
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x411, a4);
    return (void*)0x1417cb428;
}
inline void* SynLit2_14181a890(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a890
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xa6, a4);
    return (void*)0x1417cccb6;
}
inline void* SynLit2_14181a8d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a8d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xb3, a4);
    return (void*)0x1417ccd54;
}
inline void* SynLit2_14181a910(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a910
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xb8, a4);
    return (void*)0x1417ccd1e;
}
inline void* SynLit2_14181a950(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a950
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xbc, a4);
    return (void*)0x1417ccd75;
}
inline void* SynLit2_14181a990(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a990
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xd5, a4);
    return (void*)0x1417ccea7;
}
inline void* SynLit2_14181a9d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181a9d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xe2, a4);
    return (void*)0x1417ccf45;
}
inline void* SynLit2_14181aa10(void* a1, void* a2, void* a3, void* a4) {   // 0x14181aa10
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xe7, a4);
    return (void*)0x1417ccf0f;
}
inline void* SynLit2_14181aa50(void* a1, void* a2, void* a3, void* a4) {   // 0x14181aa50
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0xeb, a4);
    return (void*)0x1417ccf64;
}
inline void* SynLit2_14181b170(void* a1, void* a2, void* a3, void* a4) {   // 0x14181b170
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141839fe0, 0x1e1, a4);
    return (void*)0x1417ce640;
}
inline void* SynLit2_14181b1b0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181b1b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183b0a8, (void*)0x141839fe0, 0x207, a4);
    return (void*)0x1417ce680;
}
inline void* SynLit2_14181bbb0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181bbb0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141839fe0, 0x24c, a4);
    return (void*)0x1417ceecd;
}
inline void* SynLit2_14181bbf0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181bbf0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183b498, (void*)0x141839fe0, 0x250, a4);
    return (void*)0x1417ceee5;
}
inline void* SynLit2_14181c2d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c2d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x60, a4);
    return (void*)0x1417cf5a1;
}
inline void* SynLit2_14181c410(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c410
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141839fe0, 0x70, a4);
    return (void*)0x1417cf86f;
}
inline void* SynLit2_14181c450(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c450
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x71, a4);
    return (void*)0x1417cf88c;
}
inline void* SynLit2_14181c490(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c490
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x141839fe0, 0x7d, a4);
    return (void*)0x1417cf924;
}
inline void* SynLit2_14181c4d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c4d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x7e, a4);
    return (void*)0x1417cf93e;
}
inline void* SynLit2_14181c510(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c510
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x83, a4);
    return (void*)0x1417cf77c;
}
inline void* SynLit2_14181c550(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c550
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x141839fe0, 0x87, a4);
    return (void*)0x1417cf955;
}
inline void* SynLit2_14181c750(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c750
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183b718, (void*)0x141839fe0, 0x307, a4);
    return (void*)0x1417cffa9;
}
inline void* SynLit2_14181c7d0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c7d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14183b7b0, 0xa5, a4);
    return (void*)0x1417d040d;
}
inline void* SynLit2_14181cad0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cad0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183bb18, (void*)0x14183b940, 0x240, a4);
    return (void*)0x1417d3504;
}
inline void* SynLit2_14181cd20(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cd20
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x14183b940, 0x11a, a4);
    return (void*)0x1417d4451;
}
inline void* SynLit2_14181cd60(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cd60
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14183b940, 0x72, a4);
    return (void*)0x1417d45e8;
}
inline void* SynLit2_14181cda0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cda0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x14183b940, 0x78, a4);
    return (void*)0x1417d4619;
}
inline void* SynLit2_14181cde0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cde0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14183b940, 0x79, a4);
    return (void*)0x1417d4630;
}
inline void* SynLit2_14181ce20(void* a1, void* a2, void* a3, void* a4) {   // 0x14181ce20
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x141824e18, (void*)0x14183b940, 0x80, a4);
    return (void*)0x1417d4663;
}
inline void* SynLit2_14181ce60(void* a1, void* a2, void* a3, void* a4) {   // 0x14181ce60
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183bcb8, (void*)0x14183b940, 0xec, a4);
    return (void*)0x1417d484d;
}
inline void* SynLit2_14181cea0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cea0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14182db20, (void*)0x14183b940, 0x182, a4);
    return (void*)0x1417d49a6;
}
inline void* SynLit2_14181cee0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cee0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183bd20, (void*)0x14183b940, 0x188, a4);
    return (void*)0x1417d49ea;
}
inline void* SynLit2_14181cff0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cff0
    (void)a1; (void)a2; (void)a3;
    g_fnRep2_141823038((void*)0x14183bd88, (void*)0x14183b940, 0x1c4, a4);
    return (void*)0x1417d4d12;
}
inline void* SynCp2_1417255a0(void* pSrc, void* pDst) {   // 0x1417255a0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141722ef0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417255f0(void* pSrc, void* pDst) {   // 0x1417255f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141722fc0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141725620(void* pSrc, void* pDst) {   // 0x141725620
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141723090(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141725fb0(void* pSrc, void* pDst) {   // 0x141725fb0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141722ef0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141726040(void* pSrc, void* pDst) {   // 0x141726040
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141722fc0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141726e90(void* pSrc, void* pDst) {   // 0x141726e90
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141724ed0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141726f20(void* pSrc, void* pDst) {   // 0x141726f20
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141723a50(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141726f70(void* pSrc, void* pDst) {   // 0x141726f70
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417250d0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14173b7b0(void* pSrc, void* pDst) {   // 0x14173b7b0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_14173b240(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14173bb80(void* pSrc, void* pDst) {   // 0x14173bb80
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_14173b6c0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141745ec0(void* pSrc, void* pDst) {   // 0x141745ec0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417447d0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141746850(void* pSrc, void* pDst) {   // 0x141746850
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141744cb0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141754090(void* pSrc, void* pDst) {   // 0x141754090
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141750670(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141754190(void* pSrc, void* pDst) {   // 0x141754190
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141750760(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141755b40(void* pSrc, void* pDst) {   // 0x141755b40
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753470(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141756710(void* pSrc, void* pDst) {   // 0x141756710
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753d70(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141756740(void* pSrc, void* pDst) {   // 0x141756740
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417512f0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141756770(void* pSrc, void* pDst) {   // 0x141756770
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753500(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417567c0(void* pSrc, void* pDst) {   // 0x1417567c0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141754000(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141756870(void* pSrc, void* pDst) {   // 0x141756870
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753620(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417568a0(void* pSrc, void* pDst) {   // 0x1417568a0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141751380(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417568f0(void* pSrc, void* pDst) {   // 0x1417568f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417536b0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417578e0(void* pSrc, void* pDst) {   // 0x1417578e0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753470(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14175bb00(void* pSrc, void* pDst) {   // 0x14175bb00
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141753d70(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141776780(void* pSrc, void* pDst) {   // 0x141776780
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141776460(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14177aa30(void* pSrc, void* pDst) {   // 0x14177aa30
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_14177a5c0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14178a5f0(void* pSrc, void* pDst) {   // 0x14178a5f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141789d70(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_14178a620(void* pSrc, void* pDst) {   // 0x14178a620
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417899e0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_141792300(void* pSrc, void* pDst) {   // 0x141792300
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141790e10(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417937c0(void* pSrc, void* pDst) {   // 0x1417937c0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141792240(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417937f0(void* pSrc, void* pDst) {   // 0x1417937f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_141791080(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417a74f0(void* pSrc, void* pDst) {   // 0x1417a74f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417a70b0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417c8450(void* pSrc, void* pDst) {   // 0x1417c8450
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417c6e80(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417c8480(void* pSrc, void* pDst) {   // 0x1417c8480
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417c63c0(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417c85f0(void* pSrc, void* pDst) {   // 0x1417c85f0
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417c6580(pSrc, pDst);
    return pDst;
}
inline void* SynCp2_1417c8740(void* pSrc, void* pDst) {   // 0x1417c8740
    *(void**)pDst = *(void**)pSrc;
    *(void**)((uint8_t*)pDst + 0x8) = *(void**)((uint8_t*)pSrc + 0x8);
    g_fnN2_1417c6610(pSrc, pDst);
    return pDst;
}

}  // namespace tq

#endif
