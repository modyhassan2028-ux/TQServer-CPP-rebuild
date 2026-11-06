// synthunks_x.h — RAW Syndicate.dll v6159 · 72 flag-guarded cleanups (family X).
// The guard tests one bit of a flag word on the second argument and clears it before the call;
// the skip branch was verified onto the `add rsp` epilogue. The argument is either the member
// itself or its address, exactly as the instruction says.
#ifndef TQ_SYN_THUNKS_X_H
#define TQ_SYN_THUNKS_X_H

#include <cstdint>

namespace tq {

extern void (*g_fnXD14176b050)(void* pArg);
extern void (*g_fnXD14176f3b0)(void* pArg);
extern void (*g_fnXD1417e0da0)(void* pArg);
extern void (*g_fnXS141823290)(void* pArg);

inline void SynGuard_141805fe0(void* pUnused, void* pArg2) {   // 0x141805fe0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD14176b050(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void SynGuard_141806740(void* pUnused, void* pArg2) {   // 0x141806740  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD14176f3b0(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void SynGuard_14181e450(void* pUnused, void* pArg2) {   // 0x14181e450  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_14181e480(void* pUnused, void* pArg2) {   // 0x14181e480  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181e4b0(void* pUnused, void* pArg2) {   // 0x14181e4b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181e570(void* pUnused, void* pArg2) {   // 0x14181e570  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xa0);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0xf0));
}
inline void SynGuard_14181e670(void* pUnused, void* pArg2) {   // 0x14181e670  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xb8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181e6b0(void* pUnused, void* pArg2) {   // 0x14181e6b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290((void*)((uint8_t*)pArg2 + 0x68));
}
inline void SynGuard_14181e6e0(void* pUnused, void* pArg2) {   // 0x14181e6e0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181e760(void* pUnused, void* pArg2) {   // 0x14181e760  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290((void*)((uint8_t*)pArg2 + 0x68));
}
inline void SynGuard_14181e790(void* pUnused, void* pArg2) {   // 0x14181e790  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181e7d0(void* pUnused, void* pArg2) {   // 0x14181e7d0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290((void*)((uint8_t*)pArg2 + 0x68));
}
inline void SynGuard_14181e800(void* pUnused, void* pArg2) {   // 0x14181e800  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x90);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181e860(void* pUnused, void* pArg2) {   // 0x14181e860  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x50);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x88));
}
inline void SynGuard_14181e8b0(void* pUnused, void* pArg2) {   // 0x14181e8b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x50);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x88));
}
inline void SynGuard_14181ea50(void* pUnused, void* pArg2) {   // 0x14181ea50  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xd0);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x100));
}
inline void SynGuard_14181ef50(void* pUnused, void* pArg2) {   // 0x14181ef50  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x108);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x38));
}
inline void SynGuard_14181efa0(void* pUnused, void* pArg2) {   // 0x14181efa0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x108);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0xc8));
}
inline void SynGuard_14181efe0(void* pUnused, void* pArg2) {   // 0x14181efe0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f070(void* pUnused, void* pArg2) {   // 0x14181f070  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f0a0(void* pUnused, void* pArg2) {   // 0x14181f0a0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181f0d0(void* pUnused, void* pArg2) {   // 0x14181f0d0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x4)) return;      // the je path
    nFlags &= 0xfffffffb;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0xb8));
}
inline void SynGuard_14181f110(void* pUnused, void* pArg2) {   // 0x14181f110  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f180(void* pUnused, void* pArg2) {   // 0x14181f180  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f1b0(void* pUnused, void* pArg2) {   // 0x14181f1b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181f1e0(void* pUnused, void* pArg2) {   // 0x14181f1e0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x4)) return;      // the je path
    nFlags &= 0xfffffffb;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0xb8));
}
inline void SynGuard_14181f280(void* pUnused, void* pArg2) {   // 0x14181f280  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xb0);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f2b0(void* pUnused, void* pArg2) {   // 0x14181f2b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xb0);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181f390(void* pUnused, void* pArg2) {   // 0x14181f390  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f3c0(void* pUnused, void* pArg2) {   // 0x14181f3c0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181f3f0(void* pUnused, void* pArg2) {   // 0x14181f3f0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x4)) return;      // the je path
    nFlags &= 0xfffffffb;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0xb8));
}
inline void SynGuard_14181f430(void* pUnused, void* pArg2) {   // 0x14181f430  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f460(void* pUnused, void* pArg2) {   // 0x14181f460  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f530(void* pUnused, void* pArg2) {   // 0x14181f530  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_14181f560(void* pUnused, void* pArg2) {   // 0x14181f560  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x2)) return;      // the je path
    nFlags &= 0xfffffffd;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x70));
}
inline void SynGuard_14181f590(void* pUnused, void* pArg2) {   // 0x14181f590  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0xf8);
    if (!(nFlags & 0x4)) return;      // the je path
    nFlags &= 0xfffffffb;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0xb8));
}
inline void SynGuard_14181f660(void* pUnused, void* pArg2) {   // 0x14181f660  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_14181f690(void* pUnused, void* pArg2) {   // 0x14181f690  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_14181f6c0(void* pUnused, void* pArg2) {   // 0x14181f6c0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_14181f890(void* pUnused, void* pArg2) {   // 0x14181f890  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_14181fb40(void* pUnused, void* pArg2) {   // 0x14181fb40  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_14181fc10(void* pUnused, void* pArg2) {   // 0x14181fc10  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_14181fc40(void* pUnused, void* pArg2) {   // 0x14181fc40  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_14181fc70(void* pUnused, void* pArg2) {   // 0x14181fc70  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_14181fdc0(void* pUnused, void* pArg2) {   // 0x14181fdc0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820070(void* pUnused, void* pArg2) {   // 0x141820070  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820100(void* pUnused, void* pArg2) {   // 0x141820100  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820130(void* pUnused, void* pArg2) {   // 0x141820130  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820160(void* pUnused, void* pArg2) {   // 0x141820160  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820330(void* pUnused, void* pArg2) {   // 0x141820330  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_1418205e0(void* pUnused, void* pArg2) {   // 0x1418205e0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_1418206b0(void* pUnused, void* pArg2) {   // 0x1418206b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_1418206e0(void* pUnused, void* pArg2) {   // 0x1418206e0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820710(void* pUnused, void* pArg2) {   // 0x141820710  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820880(void* pUnused, void* pArg2) {   // 0x141820880  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820b70(void* pUnused, void* pArg2) {   // 0x141820b70  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820c80(void* pUnused, void* pArg2) {   // 0x141820c80  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141820cb0(void* pUnused, void* pArg2) {   // 0x141820cb0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820ce0(void* pUnused, void* pArg2) {   // 0x141820ce0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141820e70(void* pUnused, void* pArg2) {   // 0x141820e70  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141821160(void* pUnused, void* pArg2) {   // 0x141821160  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141821230(void* pUnused, void* pArg2) {   // 0x141821230  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141821260(void* pUnused, void* pArg2) {   // 0x141821260  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_1418213f0(void* pUnused, void* pArg2) {   // 0x1418213f0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void SynGuard_141821420(void* pUnused, void* pArg2) {   // 0x141821420  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141821570(void* pUnused, void* pArg2) {   // 0x141821570  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x20);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x30));
}
inline void SynGuard_141821780(void* pUnused, void* pArg2) {   // 0x141821780  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_1418217b0(void* pUnused, void* pArg2) {   // 0x1418217b0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_1418217e0(void* pUnused, void* pArg2) {   // 0x1418217e0  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_141821810(void* pUnused, void* pArg2) {   // 0x141821810  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x68);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x28));
}
inline void SynGuard_141821840(void* pUnused, void* pArg2) {   // 0x141821840  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x80);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x40));
}
inline void SynGuard_141821880(void* pUnused, void* pArg2) {   // 0x141821880  frame 0x20
    uint32_t& nFlags = *(uint32_t*)((uint8_t*)pArg2 + 0x80);
    if (!(nFlags & 0x1)) return;      // the je path
    nFlags &= 0xfffffffe;
    g_fnXD1417e0da0((void*)((uint8_t*)pArg2 + 0x40));
}

}  // namespace tq

#endif
