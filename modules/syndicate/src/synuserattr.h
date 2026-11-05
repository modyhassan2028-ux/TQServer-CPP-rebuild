// ============================================================================
// synuserattr.h — RAW Syndicate.dll v6159 · the three attribute getters of a user object,
//   0x14178f270 / 0x14178f330 / 0x14178f3a0. All three share one gate: the provider at
//   user + 0x428 must be non-null (otherwise the CHECKF log reports the source line and the
//   getter answers its default), then the provider's vtable slot 2 (byte +0x10) is asked for
//   a container by index, and the container's own slot answers the value.
//     index 0x00 -> container vtable +0x40 (slot 8)  : the id      (default 0)
//     index 0x02 -> container vtable +0x78 (slot f)  : the name    (default "")
//     index 0x2b -> container vtable +0x48 (slot 9)  : the number  (default 0)
//   WHAT THE PROVIDER IS (proved 2026-11-05, see PORTING_LOG): user + 0x428 is filled by
//   0x14178df30, which calls DB.dll!InstanceGet (IAT 0x141823108) and then the factory's
//   vt[4] with the blob at 0x141831938 — the ASCII name "cq_syndicate". So the provider is
//   a DB.dll table, and the slot-8 / slot-9 / slot-0xf readers belong to its record class,
//   which lives in DB.dll and not in this binary. The dispatch here stays raw vtable
//   arithmetic on purpose: no class of ours is involved.
// ============================================================================
#ifndef SYNDICATE_SYNUSERATTR_H
#define SYNDICATE_SYNUSERATTR_H

#include <cstdint>

namespace tq {

uint64_t SynUserAttrId(void* pUser);       // 0x14178f270
const char* SynUserAttrName(void* pUser);  // 0x14178f330
uint64_t SynUserAttrNumber(void* pUser);   // 0x14178f3a0

}  // namespace tq

#endif  // SYNDICATE_SYNUSERATTR_H
