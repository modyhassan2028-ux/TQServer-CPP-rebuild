// ============================================================================
// synobjects.h — RAW Syndicate.dll v6159 · the objects whose source file the binary does
//   not name. Both initialisers build a data object by name through DB.dll's InstanceGet
//   and then fill its children one by one through vtable slots read by offset, because the
//   binary itself never names those slots.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef SYNDICATE_SYNOBJECTS_H
#define SYNDICATE_SYNOBJECTS_H

#include <cstdint>

namespace tq {

// 0x141788b60 — 0x50 bytes: three arguments at +0x08..+0x18, then the counters and flags
// the creator clears one by one, with the byte at +0x48 set to one.
class CSynAttr {
public:
    static CSynAttr* Create(void* p1, void* p2, void* p3);
    uint64_t u0;        // +0x00
    void* p1;           // +0x08
    void* p2;           // +0x10
    void* p3;           // +0x18
    uint64_t u20;       // +0x20
    uint64_t u28;       // +0x28
    uint32_t u30;       // +0x30
    uint32_t u34;       // +0x34
    uint32_t u38;       // +0x38
    uint8_t u3C;        // +0x3c
    uint32_t u40;       // +0x40
    uint32_t u44;       // +0x44
    uint8_t u48;        // +0x48, one
    uint32_t u4C;       // +0x4c
};

// 0x1417a28c0 — 0x450 bytes, built by the constructor at 0x1417a2470
class CSyndicate {
public:
    static CSyndicate* Create(void* pOwner, void* p2, void* p3);
    void* pInner;       // +0x00, the "cq_syndicate" data object once Create has run
};

// 0x1417c4b60 creator, 0x1417c4c00 release · 0x28 bytes: a zero qword, a zero dword at
// +0x08, then the three arguments
class CSynDomain {
public:
    static CSynDomain* Create(void* p1, void* p2, void* p3);
    static void Release(CSynDomain* pDomain);      // 0x1417c4c00
    static void FreeAlloc(void* pMem);             // 0x1417c4a70
    uint64_t Init(uint32_t uId, const char* pszName);   // 0x1417c45c0
    void Destroy(void* u1, void* u2);                   // 0x1417c4550
    void* pInner;       // +0x00, the "cq_syndomain" data object
    uint32_t u8;        // +0x08
    void* p1;           // +0x10
    void* p2;           // +0x18
    void* p3;           // +0x20
};

// 0x1417c5320 creator, 0x1417c53c0 release · 0x20 bytes: a zero qword and the three
// arguments
class CSynFacility {
public:
    static CSynFacility* Create(void* p1, void* p2, void* p3);
    static void Release(CSynFacility* pFacility);  // 0x1417c53c0
    static void FreeAlloc(void* pMem);             // 0x1417c5230
    uint64_t Init(uint32_t uId, int32_t nFacilityType);  // 0x1417c4cc0
    void Destroy(void* u1, void* u2);                    // 0x1417c4c50
    void* pInner;       // +0x00, the "cq_synfacility" data object
    void* p1;           // +0x08
    void* p2;           // +0x10
    void* p3;           // +0x18
};

// DB.dll!InstanceGet — the module instance both initialisers ask for the data object
extern void* (*g_pfnDbInstanceGet)();

// 0x1417a2470, the CSyndicate constructor, not ported yet
extern void (*g_pfnConstructSyndicate)(void* pMem, void* pOwner, void* p2, void* p3);

// the halves of each release, kept as hooks so a test can watch the order
extern void (*g_pfnDestroyDomain)(void* pDomain, void* u1, void* u2);   // 0x1417c4550
extern void (*g_pfnFreeDomainAlloc)(void* pDomain);                     // 0x1417c4a70
extern void (*g_pfnDestroyFacility)(void* pFacility, void* u1, void* u2);  // 0x1417c4c50
extern void (*g_pfnFreeFacilityAlloc)(void* pFacility);                 // 0x1417c5230

}  // namespace tq

#endif  // SYNDICATE_SYNOBJECTS_H
