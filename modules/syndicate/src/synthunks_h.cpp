// synthunks_h.cpp — the allocator seams. 0x1417f3166 is operator new in this build.
#include "modules/syndicate/src/synthunks_h.h"

namespace tq {

void* (*g_fnAlloc1417f3166)(uint64_t) = nullptr;

}  // namespace tq
