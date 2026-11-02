// ============================================================================
// synobjects.h — RAW Syndicate.dll v6159 · the objects whose source file the binary
//   does not name. Four classes, each with the creator that the binary reaches for them
//   through: the class's own CMyHeap, then the fields the creator sets in the order it
//   sets them. The constructors that are not ported yet are seams.
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
};

// 0x1417c4b60 — 0x28 bytes: a zero qword, a zero dword at +0x08, then the three arguments
class CSynDomain {
public:
    static CSynDomain* Create(void* p1, void* p2, void* p3);
    uint64_t u0;        // +0x00
    uint32_t u8;        // +0x08
    void* p1;           // +0x10
    void* p2;           // +0x18
    void* p3;           // +0x20
};

// 0x1417c5320 — 0x20 bytes: a zero qword and the three arguments
class CSynFacility {
public:
    static CSynFacility* Create(void* p1, void* p2, void* p3);
    uint64_t u0;        // +0x00
    void* p1;           // +0x08
    void* p2;           // +0x10
    void* p3;           // +0x18
};

// 0x1417a2470, the CSyndicate constructor, not ported yet
extern void (*g_pfnConstructSyndicate)(void* pMem, void* pOwner, void* p2, void* p3);

}  // namespace tq

#endif  // SYNDICATE_SYNOBJECTS_H
