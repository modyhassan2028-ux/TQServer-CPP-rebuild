// ============================================================================
// synpbrefresh.h — RAW Syndicate.dll v6159 · 0x1417e4140, CodedInputStream::Refresh().
//   The three messages it can raise were read out of .rdata, so they are the original text:
//     0x14183fad8  "CHECK failed: (0) == (BufferSize()): "              line 0x207
//     0x14183fb50  "Reading dangerously large protocol message.  If the message turns out to be
//                   larger than " + <the limit at +0x30> + " bytes, parsing will be halted for
//                   security reasons.  To inc..."                        line 0x219
//     0x14183fcb8  "CHECK failed: (buffer_size) >= (0): "                line 0x22a
//   The order of the guards is the port's whole value:
//     1. nothing buffered                        -> raise the first CHECK
//     2. no back-up, no overflow, counters differ -> the limit check, then read
//        anything else                           -> answer false (and 0x1417e3430 reports)
//     3. the total-bytes limit reached           -> raise the security message
//     4. the stream brings a block               -> bookkeeping, then reset the bounds
//        the stream has nothing                   -> clear the pointers and answer false
// ============================================================================
#ifndef TQ_SYN_PBREFRESH_H
#define TQ_SYN_PBREFRESH_H

#include <cstdint>

#include "modules/syndicate/src/synexc.h"

namespace tq {

extern int32_t (*g_fnRfAvail)(void* pThis);                        // 0x1417e4fb0
extern void    (*g_fnRfReport)(void* pThis);                       // 0x1417e3430
extern bool    (*g_fnRfNext)(void* pStream, void** ppData, int32_t* pSize);  // 0x1417e54d0
extern void    (*g_fnSynThrow)(SynMsgBlock* pMsg);                 // 0x1417e0dd0 via 0x1417e0ee0

// 0x1417e4140
bool SynRefresh(void* pThis);

}  // namespace tq

#endif
