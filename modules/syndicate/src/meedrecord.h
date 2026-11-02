// ============================================================================
// meedrecord.h — RAW Syndicate.dll v6159 · meedrecord.cpp
//   0x1417791e0: the creator takes the record's id, builds it through the constructor at
//   0x141778ff0, and reports with CHECKF when the result comes back empty.
// ============================================================================
#ifndef SYNDICATE_MEEDRECORD_H
#define SYNDICATE_MEEDRECORD_H

#include <cstdint>

namespace tq {

class CMeedRecord {
public:
    static CMeedRecord* Create(uint32_t uId);   // 0x1417791e0
};

// 0x141778ff0, the constructor, not ported yet
extern CMeedRecord* (*g_pfnConstructMeedRecord)(void* pMem, uint32_t uId);

}  // namespace tq

#endif  // SYNDICATE_MEEDRECORD_H
