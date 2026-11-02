// ============================================================================
// synmsg.h — RAW Syndicate.dll v6159 · msg/msgsyndicate.cpp
//   0x1417db730: the string goes into the packer that sits at +0x410 of the packet, and
//   the size the packet advertises at +0x408 is the packer's size plus the header's 0x1b.
// ============================================================================
#ifndef SYNDICATE_SYNMSG_H
#define SYNDICATE_SYNMSG_H

#include <cstdint>

namespace tq {

// 0x1417db730 — answers true once the string is in, false (with the CHECKF text at 0xa7)
// when there is nothing to add.
bool SynMsgAddString(void* pPacket, const char* pszString);

}  // namespace tq

#endif  // SYNDICATE_SYNMSG_H
