#ifndef MSG_AUCTION_THREAD_H
#define MSG_AUCTION_THREAD_H
// ===== Path-A wave 7:
// CAuctionSearchThread::OnProcess
// (1400f31f0) VERBATIM, raw-verified =====
// KEY RAW DELTA vs the other threads:
// the QUEUE iface lives at +0x40 and
// the SERVICE iface at +0x48 (inverted!)
//  - Peek/WaitMsg on (+0x40), OnTimer
//    (vt+0x18) and ProcessMsg (vt+0x10,
//    FIVE raw args incl. port as 5th
//    stack arg) on (+0x48)
//  - flag 0x140975cac / base
//    0x140975ca8, slide 2000, threshold
//    cmp 0x2710
//  - ticks: 0x4a around Peek
//    ("CAuctionSearchThread WaitMsg"),
//    0x32 (process), 0x34 (service
//    OnTimer), 0x33 (ProcessMsg)
//  - NO stats; idle at
//    0x14094b928+0x1c (raw byte-writes
//    at [0x1c..0x1f] for the zero case)
//  - ERROR: (packet=[info+4],
//    port=[info+0]) raw-verified
#include "MsgWorldULChatThreads.h"  // seams

namespace msg {

extern uint32_t g_AucFirstRun,
       g_AucResyncBase, g_AucIdleMs;
void AuctionResetStatics();
uint32_t AuctionOnProcess(uint8_t* pTh);

} // namespace msg
#endif
