// msgleaguerobopt.h — 0x1417d8920. Unlike 0x1417d68d0 there is no CHECK string in this body, so the
// original file name is not recoverable from the image; the unit is filed next to msgleagueopt.cpp
// because it dispatches the neighbouring league message on the same singleton.
#pragma once
#include <cstdint>

namespace tq {

// The predicate is the same 0x1417ac700 the LeagueOpt dispatcher asks, so the seam is shared with
// msgleagueopt.h rather than declared twice.
struct CMsgLeagueRobOpt;

// 0x1417d8920 — dispatches on the u32 at this+0x440. Cases 0/1/5/6 build a ten-slot array from the
// u32 at +0x48 of each pointer in the array at this+0x448 (length at this+0x450) and hand it to a
// vtable slot; cases 2 and 3 split the u32 at +0x444 into quotient and remainder by 1000.
void Slot_1417d8920_Process(void* pThis, uint32_t nId);

}  // namespace tq
