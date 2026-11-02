// ============================================================================
// meedrecord.h — RAW Syndicate.dll v6159 · meedrecord.cpp
//   0x141778ff0 the constructor, 0x1417791e0 the creator. The id sits at +0x00 and the
//   constructor reports an id of zero with a log call that is handed no arguments at all.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef SYNDICATE_MEEDRECORD_H
#define SYNDICATE_MEEDRECORD_H

#include <cstdint>

namespace tq {

struct SynListNode;

class CMeedRecord {
public:
    CMeedRecord* Construct(uint32_t uId);       // 0x141778ff0
    static CMeedRecord* Create(uint32_t uId);   // 0x1417791e0

    uint32_t uId;       // +0x00
    uint32_t uPad04;    // +0x04
    void* pListHead;    // +0x08
    uint64_t u10;       // +0x10
    uint64_t u18;       // +0x18
    uint32_t u20;       // +0x20
    uint32_t u24;       // +0x24
    uint32_t u28;       // +0x28
    uint32_t u2C;       // +0x2c
    uint32_t u30;       // +0x30
    uint32_t u34;       // +0x34
    uint8_t u38;        // +0x38
};

// the hook the test hangs the constructor on, the default is the ported body
extern CMeedRecord* (*g_pfnConstructMeedRecord)(void* pMem, uint32_t uId);

}  // namespace tq

#endif  // SYNDICATE_MEEDRECORD_H
