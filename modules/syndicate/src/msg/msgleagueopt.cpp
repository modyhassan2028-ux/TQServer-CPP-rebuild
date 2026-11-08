#include <cstring>
#include "modules/syndicate/src/slotforwarders.h"
#include "modules/syndicate/src/msg/msgleagueopt.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"   // Slot_1417b6210_singleton

namespace tq {

bool (*g_pfnCStringPacker_GetString)(void*, uint32_t, char*, uint32_t) = nullptr;
uint32_t (*g_pfnCStringPacker_GetStrAmount)(void*) = nullptr;
void (*g_pfn_check_msgleagueopt)(const char*, const char*, const char*, const char*, uint32_t) = nullptr;
bool (*g_pfnL_1417ac700)(void*, uint32_t) = nullptr;
void (*g_pfnL_1417ac7d0)(void*, uint32_t, void*) = nullptr;
bool (*g_pfnL_1417b0a40)(void*, uint32_t, uint32_t, void*) = nullptr;
bool (*g_pfnL_1417b03b0)(void*, uint32_t, uint32_t, void*) = nullptr;
void (*g_pfnL_1417b0db0)(void*, uint32_t, void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b0e20)(void*, uint32_t, void*, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b14c0)(void*, uint32_t, void*, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b1660)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417bf4d0)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b48b0)(void*, uint32_t, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b4d60)(void*, uint32_t, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b0de0)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b0e00)(void*, uint32_t) = nullptr;
void (*g_pfnL_1417b0e50)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b0e70)(void*, uint32_t) = nullptr;
void (*g_pfnL_1417b15b0)(void*, uint32_t, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b1690)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b4310)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b98e0)(void*, uint32_t) = nullptr;
void (*g_pfnL_1417b1980)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b19c0)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b1a40)(void*, uint32_t, uint32_t) = nullptr;
void (*g_pfnL_1417b0680)(void*, uint32_t, void*) = nullptr;
void (*g_pfnL_1417f30c0)(void*, int, uint32_t) = nullptr;

#define LO_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
// cfg+0x2/0x4/0x6/0xa/0xe are unaligned in the message header, so the reads go through memcpy: the
// original does `mov 0xe(%rdx),%r9d` and the x86 allows it, C++ does not.
static inline uint32_t LO_D(const void* p, uint32_t off) {
    uint32_t v; std::memcpy(&v, (const uint8_t*)p + off, sizeof v); return v;
}
static inline uint16_t LO_W(const void* p, uint32_t off) {
    uint16_t v; std::memcpy(&v, (const uint8_t*)p + off, sizeof v); return v;
}
static inline void ST_W(void* p, uint32_t off, uint16_t v) {
    std::memcpy((uint8_t*)p + off, &v, sizeof v);
}

// A vtable dispatch is `mov (%rbx),%r10 / ... / call *0xNNN(%r10)` with this (the singleton object,
// not the message) in rcx. Word 0 of the object is the table address.
#define VT0(off)          ((void(*)(void*, uint32_t))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId)
#define VT1(off, a)       ((void(*)(void*, uint32_t, uint32_t))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId, (a))
#define VT2(off, a, b)    ((void(*)(void*, uint32_t, uint32_t, uint32_t))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId, (a), (b))
#define VT1P(off, p)      ((void(*)(void*, uint32_t, void*))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId, (p))
#define VT2P(off, a, p)   ((void(*)(void*, uint32_t, uint32_t, void*))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId, (a), (p))
#define VT2P1(off, p, a)  ((void(*)(void*, uint32_t, void*, uint32_t))*(void**)(*(uint8_t**)pObj + (off)))(pObj, nId, (p), (a))

// The 79-byte gate at 0x1417b70cc: after the predicate answers "known", a 1 means the case is
// already handled and the body returns without dispatching. Index = the u16 at cfg+4.
static const uint8_t g_abLeagueOptGate[0x4F] = {
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 0
};

// ============================================================================
// 0x1417d68d0. Frame is 0x180 with the __security_cookie at 0x141886c40 xor'd into 0x170(%rsp); the
// cookie is a compiler guard and is noted here rather than reproduced. The four scratch buffers live
// at 0x40/0x50/0x60/0x70 and the stack argument homes at 0x20/0x28 are the callees' 5th/6th args.
void Slot_1417d68d0_Process(void* pThis, uint32_t nId) {
    uint8_t abFrame[0x180];
    uint8_t* const pBuf40 = abFrame + 0x40;
    uint8_t* const pBuf50 = abFrame + 0x50;
    uint8_t* const pBuf60 = abFrame + 0x60;
    uint8_t* const pBuf70 = abFrame + 0x70;
    for (int i = 0; i < 0x180; ++i) abFrame[i] = 0;         // the buffers are built before use below

    void* pCfg = LO_Q(pThis, 0x408);
    if (pCfg == nullptr) {                                   // 1417d6908 cmpq $0x0,0x408(%rcx)
        if (g_pfn_check_msgleagueopt != nullptr)             // 1417d6936 through IAT 0x141823030
            g_pfn_check_msgleagueopt(
                "\xA1\xEF%s(%s)\xA1\xEF in %s, %d", "CHECK", "m_pInfo",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg\\msgleagueopt.cpp",
                0x54);
        return;                                              // 1417d693c -> 1417d709e
    }
    void* pObj = Slot_1417b6210_singleton();                 // 1417d6941
    const bool bKnown = (g_pfnL_1417ac700 != nullptr)        // 1417d694e
                            ? g_pfnL_1417ac700(pObj, nId) : false;
    if (bKnown) {
        const uint16_t wGate = LO_W(LO_Q(pThis, 0x408), 0x4);   // 1417d6957 movzwl 0x4(%rcx)
        if (wGate > 0x4E) return;                            // 1417d6962 cmp $0x4e / ja
        if (g_abLeagueOptGate[wGate] == 1) return;           // label 1 -> 0x1417d6984 -> epilogue
    }
    const uint16_t wType = LO_W(LO_Q(pThis, 0x408), 0x4);      // 1417d6997 / 1417d69a6
    if (wType > 0x4E) return;                                // 1417d699c ja 0x1417d709e
    pCfg = LO_Q(pThis, 0x408);
    const uint32_t nCfg6 = LO_D(pCfg, 0x6);
    const uint32_t nCfgA = LO_D(pCfg, 0xA);
    const uint32_t nCfgE = LO_D(pCfg, 0xE);
    const uint16_t wCfg0 = LO_W(pCfg, 0x0);
    const uint16_t wCfg4 = LO_W(pCfg, 0x4);

    switch (wType) {
    case 0:  VT0(0x5b0); break;                              // 1417d69b3
    case 1:  VT2(0x5c0, nCfg6, nCfgE); break;                // 1417d69c6
    case 2:  VT2(0x5c8, nCfg6, nCfgE); break;                // 1417d69e2
    case 3:  VT2(0x5d0, nCfg6, nCfgE); break;                // 1417d69fe
    case 4:  VT1(0x5b8, nCfgE); break;                       // 1417d6a1a
    case 6:                                                  // 1417d6a31
        if (g_pfnCStringPacker_GetString != nullptr)
            g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf40, 0x10);
        if (g_pfnL_1417b0a40 != nullptr && g_pfnL_1417b0a40(pObj, nId, nCfg6, pBuf40)) {
            ST_W(LO_Q(pThis, 0x408), 0x4, 0x16);              // 1417d6a74 mov $0x16,%ecx
            if (g_pfnL_1417ac7d0 != nullptr) g_pfnL_1417ac7d0(pObj, nId, pThis);
        }
        break;
    case 7:                                                  // 1417d6a8f
        if (g_pfnCStringPacker_GetString != nullptr)
            g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf40, 0x10);
        VT2P1(0x4e8, pBuf40, 0);
        break;
    case 8:  if (g_pfnL_1417b1980) g_pfnL_1417b1980(pObj, nId, nCfgE); break;   // 1417d6b35
    case 9:  if (g_pfnL_1417b19c0) g_pfnL_1417b19c0(pObj, nId, 0); break;       // 1417d6b48
    case 10: if (g_pfnL_1417b1a40) g_pfnL_1417b1a40(pObj, nId, nCfgE); break;   // 1417d6b5a
    case 11: VT2(0x4f8, nCfg6, nCfgE); break;                 // 1417d6ac5
    case 12: VT2(0x500, nCfg6, nCfgE); break;                 // 1417d6ae1
    case 13: VT2(0x708, nCfg6, nCfgE); break;                 // 1417d6afd
    case 14: VT2(0x508, nCfgE, nCfgA); break;                 // 1417d6b19 r9=cfg+0xa, r8=cfg+0xe
    case 15: VT1(0x5d8, nCfgE); break;                        // 1417d6b6d
    case 16: VT1(0x700, nCfgE); break;                        // 1417d6b84
    case 18:                                                  // 1417d6b9b
        if (g_pfnCStringPacker_GetString != nullptr)
            g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf50, 0xA);
        VT2P(0x478, nCfg6, pBuf50);
        break;
    case 19: VT0(0x718); break;                               // 1417d6bd9
    case 20: {                                                // 1417d6bec
        pBuf70[0] = 0;
        if (g_pfnL_1417f30c0 != nullptr) g_pfnL_1417f30c0(pBuf70 + 1, 0, 0xFF);
        bool bOk = false;
        if (g_pfnCStringPacker_GetString != nullptr)
            bOk = g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf70, 0x100);
        if (bOk) VT1P(0x720, pBuf70);
        break;
    }
    case 23: VT1(0x5f0, (uint32_t)((uint8_t*)pCfg)[0xE]); break;  // 1417d6c3d movzbl 0xe(%rdx)
    case 24: case 48: {                                       // 1417d6c55
        for (int i = 0; i < 0x10; ++i) pBuf50[i] = 0;
        bool bOk = false;
        if (g_pfnCStringPacker_GetString != nullptr)
            bOk = g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf50, 0x10);
        if (bOk && g_pfnL_1417b0db0 != nullptr)
            g_pfnL_1417b0db0(pObj, nId, pBuf50, nCfg6, (uint32_t)wCfg4);
        break;
    }
    case 25: if (g_pfnL_1417b0de0) g_pfnL_1417b0de0(pObj, nId, nCfgA); break;   // 1417d6cb5
    case 26: if (g_pfnL_1417b0e00) g_pfnL_1417b0e00(pObj, nId); break;           // 1417d6cc8
    case 27: VT0(0x5e0); break;                               // 1417d6cd7
    case 28: case 47: {                                       // 1417d6cea
        for (int i = 0; i < 0x10; ++i) pBuf60[i] = 0;
        bool bOk = false;
        if (g_pfnCStringPacker_GetString != nullptr)
            bOk = g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf60, 0x10);
        if (bOk && g_pfnL_1417b0e20 != nullptr)
            g_pfnL_1417b0e20(pObj, nId, pBuf60, (uint32_t)LO_W(pCfg, 0xE), nCfg6, (uint32_t)wCfg4);
        break;
    }
    case 29: if (g_pfnL_1417b0e50) g_pfnL_1417b0e50(pObj, nId, nCfgA); break;   // 1417d6d52
    case 30: if (g_pfnL_1417b0e70) g_pfnL_1417b0e70(pObj, nId); break;           // 1417d6d65
    case 31: VT1(0x588, nCfgE); break;                        // 1417d6d74
    case 32: VT1(0x590, nCfgE); break;                        // 1417d6d8b
    case 33: VT1(0x598, nCfgE); break;                        // 1417d6da2
    case 34: VT0(0x5e8); break;                               // 1417d6db9
    case 37: VT0(0x578); break;                               // 1417d6dcc
    case 39: if (g_pfnL_1417b4310) g_pfnL_1417b4310(pObj, nId, nCfgE); break;   // 1417d6f39
    case 40: VT0(0x5f8); break;                               // 1417d6e3d
    case 41: case 49: {                                       // 1417d6e50
        for (int i = 0; i < 0x10; ++i) pBuf40[i] = 0;
        bool bOk = false;
        if (g_pfnCStringPacker_GetString != nullptr)
            bOk = g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf40, 0x10);
        if (bOk && g_pfnL_1417b14c0 != nullptr)
            g_pfnL_1417b14c0(pObj, nId, pBuf40, (uint32_t)LO_W(pCfg, 0xE), nCfg6, (uint32_t)wCfg4);
        break;
    }
    case 42: case 50:                                         // 1417d6eb8
        if (g_pfnL_1417b1660 != nullptr)
            g_pfnL_1417b1660(pObj, nId, nCfg6, (uint32_t)LO_W(pCfg, 0xE), nCfgA, (uint32_t)wCfg4);
        break;
    case 43:                                                  // 1417d6edf
        if (g_pfnL_1417b15b0 != nullptr)
            g_pfnL_1417b15b0(pObj, nId, nCfg6, (uint32_t)LO_W(pCfg, 0xE));
        break;
    case 44: if (g_pfnL_1417b1690) g_pfnL_1417b1690(pObj, nId, nCfgA); break;   // 1417d6ef7
    case 38: case 45:                                         // 1417d6f0a
        if (g_pfnL_1417bf4d0 != nullptr)
            g_pfnL_1417bf4d0(pObj, nId, (uint32_t)LO_W(pCfg, 0x6), nCfgE, nCfgA,
                             (wCfg4 == 0x2D) ? 1u : 0u);
        break;
    case 46: if (g_pfnL_1417b98e0) g_pfnL_1417b98e0(pObj, nId); break;           // 1417d6f4c
    case 51:                                                  // 1417d6ddf
        if (g_pfnCStringPacker_GetString != nullptr)
            g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf40, 0x10);
        if (g_pfnL_1417b03b0 != nullptr && g_pfnL_1417b03b0(pObj, nId, nCfg6, pBuf40)) {
            ST_W(LO_Q(pThis, 0x408), 0x4, 0x33);              // 1417d6e22 mov $0x33,%ecx
            if (g_pfnL_1417ac7d0 != nullptr) g_pfnL_1417ac7d0(pObj, nId, pThis);
        }
        break;
    case 60: VT0(0x728); break;                               // 1417d6f5b
    case 64: VT0(0x6c0); break;                               // 1417d6f6e
    case 66: {                                                // 1417d6f94
        uint32_t nAmount = 0;
        if (g_pfnCStringPacker_GetStrAmount != nullptr)
            nAmount = g_pfnCStringPacker_GetStrAmount((uint8_t*)pThis + 0x410);
        if (nAmount != 0) {
            if (g_pfnCStringPacker_GetString != nullptr)
                g_pfnCStringPacker_GetString((uint8_t*)pThis + 0x410, 0, (char*)pBuf70, 0x100);
            if (g_pfnL_1417b0680 != nullptr) g_pfnL_1417b0680(pObj, nId, pBuf70);
        }
        VT0(0x5b0);                                           // 1417d6fda, outside the branch
        break;
    }
    case 71: VT0(0x6c8); break;                               // 1417d6f81
    case 72: VT2(0x580, nCfgE, 0); break;                     // 1417d6fe6, 4th arg r9 = 0
    case 78: VT0(0x738); break;                               // 1417d7000
    case 74:                                                  // 1417d7013
        if (g_pfnL_1417b48b0 != nullptr)
            g_pfnL_1417b48b0(pObj, nId, nCfgA, (wCfg4 == 0x4C) ? 1u : 0u,
                             (nCfgE == 0) ? 1u : 0u);
        break;
    case 76:                                                  // 1417d7036: the two u32s swapped
        if (g_pfnL_1417b48b0 != nullptr)
            g_pfnL_1417b48b0(pObj, nCfgA, nId, (wCfg4 == 0x4C) ? 1u : 0u,
                             (nCfgE == 0) ? 1u : 0u);
        break;
    case 75:                                                  // 1417d7059
        if (g_pfnL_1417b4d60 != nullptr)
            g_pfnL_1417b4d60(pObj, nId, nCfgA, (wCfg4 == 0x4D) ? 1u : 0u,
                             (nCfgE == 0) ? 1u : 0u);
        break;
    case 77:                                                  // 1417d707c: swapped as well
        if (g_pfnL_1417b4d60 != nullptr)
            g_pfnL_1417b4d60(pObj, nCfgA, nId, (wCfg4 == 0x4D) ? 1u : 0u,
                             (nCfgE == 0) ? 1u : 0u);
        break;
    default:                                                  // 1417d709e: 5,17,21,22,35,36,52..59,
        (void)wCfg0;                                          // 61..63,65,67..70,73 return here
        break;
    }
}

}  // namespace tq
