// synthunks_l.h — RAW Syndicate.dll v6159 · 76 literal-reporting helpers (family L).
// Each one reports (text2, text, line, arg4) to the same sink and answers a fixed address.
// The tail jump was required to land on the epilogue before the body was accepted.
#ifndef TQ_SYN_THUNKS_L_H
#define TQ_SYN_THUNKS_L_H

#include <cstdint>

namespace tq {

extern void (*g_fnRep_141823038)(void* pA, void* pB, uint32_t nLine, void* pFourth);

inline void* SynLit_1417f5f00(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f5f00
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0x8d, a4);
    return (void*)0x141721874;
}
inline void* SynLit_1417f5f60(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f5f60
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0x93, a4);
    return (void*)0x1417218b6;
}
inline void* SynLit_1417f5fc0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f5fc0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0xa2, a4);
    return (void*)0x141721949;
}
inline void* SynLit_1417f6000(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f6000
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0xad, a4);
    return (void*)0x141721a09;
}
inline void* SynLit_1417f6040(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f6040
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0x70d, a4);
    return (void*)0x141721ccc;
}
inline void* SynLit_1417f60e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417f60e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0x8fd, a4);
    return (void*)0x14172205e;
}
inline void* SynLit_1417fa030(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fa030
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0xa3b, a4);
    return (void*)0x141734db4;
}
inline void* SynLit_1417faee0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417faee0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0xa2b, a4);
    return (void*)0x141736088;
}
inline void* SynLit_1417fb980(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fb980
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141824e30, 0x5b, a4);
    return (void*)0x14173ac36;
}
inline void* SynLit_1417fd320(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fd320
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141828078, (void*)0x141827bb0, 0x1c, a4);
    return (void*)0x14173f46e;
}
inline void* SynLit_1417fec40(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fec40
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141828950, 0xbe, a4);
    return (void*)0x141748f35;
}
inline void* SynLit_1417fec80(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fec80
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141828950, 0xeb, a4);
    return (void*)0x14174911d;
}
inline void* SynLit_1417fefd0(void* a1, void* a2, void* a3, void* a4) {   // 0x1417fefd0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141828950, 0x45, a4);
    return (void*)0x14174a6a4;
}
inline void* SynLit_141800080(void* a1, void* a2, void* a3, void* a4) {   // 0x141800080
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141829668, (void*)0x141828950, 0x52, a4);
    return (void*)0x14174e03b;
}
inline void* SynLit_1418000e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418000e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141828950, 0x32, a4);
    return (void*)0x14174e0d3;
}
inline void* SynLit_141800120(void* a1, void* a2, void* a3, void* a4) {   // 0x141800120
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141828950, 0x38, a4);
    return (void*)0x14174e0f0;
}
inline void* SynLit_141800160(void* a1, void* a2, void* a3, void* a4) {   // 0x141800160
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x273, a4);
    return (void*)0x14174e50f;
}
inline void* SynLit_1418001a0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418001a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x288, a4);
    return (void*)0x14174e5bd;
}
inline void* SynLit_1418001e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418001e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x296, a4);
    return (void*)0x14174e692;
}
inline void* SynLit_141800220(void* a1, void* a2, void* a3, void* a4) {   // 0x141800220
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x2a4, a4);
    return (void*)0x14174e72a;
}
inline void* SynLit_141800260(void* a1, void* a2, void* a3, void* a4) {   // 0x141800260
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x2e8, a4);
    return (void*)0x14174e7ce;
}
inline void* SynLit_1418002c0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418002c0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x7ab, a4);
    return (void*)0x14174eacf;
}
inline void* SynLit_141800300(void* a1, void* a2, void* a3, void* a4) {   // 0x141800300
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x84d, a4);
    return (void*)0x14174eb96;
}
inline void* SynLit_1418029e0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418029e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x2cf, a4);
    return (void*)0x14175f36f;
}
inline void* SynLit_141802a60(void* a1, void* a2, void* a3, void* a4) {   // 0x141802a60
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x833, a4);
    return (void*)0x14175fc82;
}
inline void* SynLit_141802aa0(void* a1, void* a2, void* a3, void* a4) {   // 0x141802aa0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x128b, a4);
    return (void*)0x14175ffaf;
}
inline void* SynLit_141803730(void* a1, void* a2, void* a3, void* a4) {   // 0x141803730
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x1a5, a4);
    return (void*)0x141763485;
}
inline void* SynLit_141803810(void* a1, void* a2, void* a3, void* a4) {   // 0x141803810
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x7fd, a4);
    return (void*)0x141765225;
}
inline void* SynLit_141803850(void* a1, void* a2, void* a3, void* a4) {   // 0x141803850
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x803, a4);
    return (void*)0x14176529f;
}
inline void* SynLit_141803970(void* a1, void* a2, void* a3, void* a4) {   // 0x141803970
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182bb78, (void*)0x1418297c0, 0xf69, a4);
    return (void*)0x14176752e;
}
inline void* SynLit_1418039b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418039b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x1260, a4);
    return (void*)0x141768e69;
}
inline void* SynLit_1418039f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418039f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x1262, a4);
    return (void*)0x141768e95;
}
inline void* SynLit_141804cb0(void* a1, void* a2, void* a3, void* a4) {   // 0x141804cb0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0xf5, a4);
    return (void*)0x14176aace;
}
inline void* SynLit_141805110(void* a1, void* a2, void* a3, void* a4) {   // 0x141805110
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x1273, a4);
    return (void*)0x14176db2f;
}
inline void* SynLit_141805150(void* a1, void* a2, void* a3, void* a4) {   // 0x141805150
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x1283, a4);
    return (void*)0x14176dba2;
}
inline void* SynLit_141806390(void* a1, void* a2, void* a3, void* a4) {   // 0x141806390
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x132, a4);
    return (void*)0x14176fa5f;
}
inline void* SynLit_1418063d0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418063d0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418297c0, 0x19b, a4);
    return (void*)0x14176fb67;
}
inline void* SynLit_141806a30(void* a1, void* a2, void* a3, void* a4) {   // 0x141806a30
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182cc38, (void*)0x1418297c0, 0xd6, a4);
    return (void*)0x1417705e2;
}
inline void* SynLit_14180be50(void* a1, void* a2, void* a3, void* a4) {   // 0x14180be50
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182d450, 0x23, a4);
    return (void*)0x14177808e;
}
inline void* SynLit_14180c010(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c010
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182d540, 0x46, a4);
    return (void*)0x141779384;
}
inline void* SynLit_14180c050(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c050
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182d540, 0x157, a4);
    return (void*)0x1417795fd;
}
inline void* SynLit_14180c090(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c090
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182d540, 0x16b, a4);
    return (void*)0x14177972c;
}
inline void* SynLit_14180c550(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c550
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182db40, 0x21, a4);
    return (void*)0x14177b3e8;
}
inline void* SynLit_14180c770(void* a1, void* a2, void* a3, void* a4) {   // 0x14180c770
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182db40, 0x67, a4);
    return (void*)0x14177c00c;
}
inline void* SynLit_14180cf00(void* a1, void* a2, void* a3, void* a4) {   // 0x14180cf00
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182db40, 0xb0, a4);
    return (void*)0x14177c857;
}
inline void* SynLit_14180cff0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180cff0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182de70, 0x29, a4);
    return (void*)0x14177d10f;
}
inline void* SynLit_14180d030(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d030
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14182de70, 0xff, a4);
    return (void*)0x14177d2d8;
}
inline void* SynLit_14180d1a0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d1a0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182de70, 0x22b, a4);
    return (void*)0x14177db70;
}
inline void* SynLit_14180d8e0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180d8e0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182e750, 0xf2, a4);
    return (void*)0x14177f323;
}
inline void* SynLit_14180ddb0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180ddb0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14182ed30, 0x5c7, a4);
    return (void*)0x141782293;
}
inline void* SynLit_14180e080(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e080
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182fe18, (void*)0x14182ed30, 0x3ca, a4);
    return (void*)0x1417846b9;
}
inline void* SynLit_14180e0c0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e0c0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182fea0, (void*)0x14182ed30, 0x402, a4);
    return (void*)0x1417848cb;
}
inline void* SynLit_14180e5b0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180e5b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418302d0, 0x2a, a4);
    return (void*)0x14178577f;
}
inline void* SynLit_14180f110(void* a1, void* a2, void* a3, void* a4) {   // 0x14180f110
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141830e10, 0x74, a4);
    return (void*)0x14178c836;
}
inline void* SynLit_14180fe70(void* a1, void* a2, void* a3, void* a4) {   // 0x14180fe70
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141830e10, 0xe8, a4);
    return (void*)0x14178dc30;
}
inline void* SynLit_14180feb0(void* a1, void* a2, void* a3, void* a4) {   // 0x14180feb0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141831828, (void*)0x141830e10, 0xeb, a4);
    return (void*)0x14178dc38;
}
inline void* SynLit_141810150(void* a1, void* a2, void* a3, void* a4) {   // 0x141810150
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141830e10, 0x30, a4);
    return (void*)0x14178de78;
}
inline void* SynLit_141810f10(void* a1, void* a2, void* a3, void* a4) {   // 0x141810f10
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418319b0, 0xb44, a4);
    return (void*)0x1417986f3;
}
inline void* SynLit_141813530(void* a1, void* a2, void* a3, void* a4) {   // 0x141813530
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418319b0, 0x36, a4);
    return (void*)0x1417a1c5b;
}
inline void* SynLit_141813570(void* a1, void* a2, void* a3, void* a4) {   // 0x141813570
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418319b0, 0x3c, a4);
    return (void*)0x1417a1ca0;
}
inline void* SynLit_1418135b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418135b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x1418319b0, 0x4b, a4);
    return (void*)0x1417a1d31;
}
inline void* SynLit_141815000(void* a1, void* a2, void* a3, void* a4) {   // 0x141815000
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x1418345b0, 0xf2, a4);
    return (void*)0x1417a8bfe;
}
inline void* SynLit_141815760(void* a1, void* a2, void* a3, void* a4) {   // 0x141815760
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141835bd0, 0xe7, a4);
    return (void*)0x1417a9f08;
}
inline void* SynLit_141815b40(void* a1, void* a2, void* a3, void* a4) {   // 0x141815b40
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141836528, (void*)0x141835bd0, 0xb43, a4);
    return (void*)0x1417ac6c9;
}
inline void* SynLit_141815fc0(void* a1, void* a2, void* a3, void* a4) {   // 0x141815fc0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141836e28, (void*)0x141835bd0, 0x1203, a4);
    return (void*)0x1417aea62;
}
inline void* SynLit_141818260(void* a1, void* a2, void* a3, void* a4) {   // 0x141818260
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141839348, (void*)0x141835bd0, 0x1ba, a4);
    return (void*)0x1417c083f;
}
inline void* SynLit_1418193b0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418193b0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141839b40, 0x1d, a4);
    return (void*)0x1417c458f;
}
inline void* SynLit_1418194f0(void* a1, void* a2, void* a3, void* a4) {   // 0x1418194f0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x141839cd0, 0x1c, a4);
    return (void*)0x1417c4c8f;
}
inline void* SynLit_141819630(void* a1, void* a2, void* a3, void* a4) {   // 0x141819630
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141839fe0, 0x3b, a4);
    return (void*)0x1417c5459;
}
inline void* SynLit_141819d90(void* a1, void* a2, void* a3, void* a4) {   // 0x141819d90
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14183a7a8, (void*)0x141839fe0, 0x2bc, a4);
    return (void*)0x1417c8d52;
}
inline void* SynLit_141819dd0(void* a1, void* a2, void* a3, void* a4) {   // 0x141819dd0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14183a808, (void*)0x141839fe0, 0x2d1, a4);
    return (void*)0x1417c8e8d;
}
inline void* SynLit_14181b000(void* a1, void* a2, void* a3, void* a4) {   // 0x14181b000
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x141839fe0, 0xf8, a4);
    return (void*)0x1417cde52;
}
inline void* SynLit_14181c790(void* a1, void* a2, void* a3, void* a4) {   // 0x14181c790
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14183b7b0, 0x20, a4);
    return (void*)0x1417d005f;
}
inline void* SynLit_14181cc40(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cc40
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14183b940, 0x2a, a4);
    return (void*)0x1417d3d6f;
}
inline void* SynLit_14181cce0(void* a1, void* a2, void* a3, void* a4) {   // 0x14181cce0
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x14182db20, (void*)0x14183b940, 0x44, a4);
    return (void*)0x1417d4140;
}
inline void* SynLit_14181d050(void* a1, void* a2, void* a3, void* a4) {   // 0x14181d050
    (void)a1; (void)a2; (void)a3;
    g_fnRep_141823038((void*)0x141824e18, (void*)0x14183beb0, 0x1d, a4);
    return (void*)0x1417d4de2;
}

}  // namespace tq

#endif
