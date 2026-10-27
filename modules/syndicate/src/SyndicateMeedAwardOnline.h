// SyndicateMeedAwardOnline.h — D56: the online award
// flow 1417814c0 (CSynArenicMeed::AwardUserOnline).
//
// The D55b dispatch (1417821d0 AwardUser) routes the
// online users here via the g_fnMeedAwardOnline seam;
// this unit is its real body.
//
// Addresses (Syndicate.dll, ImageBase 0x141720000):
//   1417814c0  AwardUserOnline (this port)
//   141821a10  the static-init thunk setting
//              DAT_141886d68 = INT_MAX (the emoney
//              total cap)
//   14177ff70  MeedEmonyType     (D53, reused)
//   14177fbc0  MeedPromptGet     (D53, reused)
//   14177fad0  MeedGmLogName     (D53, reused)
#ifndef SYNDICATE_MEED_AWARD_ONLINE_H
#define SYNDICATE_MEED_AWARD_ONLINE_H

#include <cstdint>

namespace syndicate {

// DAT_141886d68 — the emoney total cap (the static
// init at 141821a10 sets it to INT_MAX)
extern int32_t g_nMeedEmoneyCap;

// ---------- FUN_1417814c0 @ 1417814c0 ----------
// (pThis = the CSynArenicMeed award host — the user
//  object lives at *(void**)pThis, matching the
//  21d0/1860 convention)
void MeedAwardOnline(void* pThis, uint32_t uUser,
    int nType, int nPoint, int nMoney,
    int nEmoney);

}  // namespace syndicate

#endif  // SYNDICATE_MEED_AWARD_ONLINE_H
