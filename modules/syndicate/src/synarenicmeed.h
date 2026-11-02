// ============================================================================
// synarenicmeed.h — RAW Syndicate.dll v6159 · synarenicmeed.cpp
//   0x141781b60: the object is eight bytes and the creator writes a single zero into it,
//   so no constructor is called at all.
// ============================================================================
#ifndef SYNDICATE_SYNARENICMEED_H
#define SYNDICATE_SYNARENICMEED_H

#include <cstdint>

namespace tq {

class CSynArenicMeed {
public:
    static CSynArenicMeed* InstanceGet();   // 0x141781b60
    uint64_t u0;                            // +0x00
};

}  // namespace tq

#endif  // SYNDICATE_SYNARENICMEED_H
