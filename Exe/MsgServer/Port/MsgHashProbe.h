#ifndef MSG_HASH_PROBE_H
#define MSG_HASH_PROBE_H
#include <cstdint>

namespace msg {

// ===== M67: ORIGINAL FUN_14000db40 - the hash-map
// find of the ACTIVITY map (called from the cq_config
// 0x1777 block as db40(kernel+0x10, &it, &id)).
//
// Container layout walked (offsets VERBATIM):
//   +0x10  the first LIST node ptr (slot)
//   +0x38  the END marker ptr
//   +0x60  buckets base, +0x68 buckets end
//   +0x78  the mask, +0x80 the bucket count
// Bucket entries are 0x10 bytes each; the chain
// head node ptr lives at entry+8 (the probe reads
// base + 8 + idx*0x10). The chain of bucket i is
// the list interval [bucket[i], bucket[i+1]).
// Node layout: chain-next @+0x0, key (int) @+0x10.
// The chain terminator: bucket[idx+1] == the current
// node (the classic TQ sentinel-terminated probe).
void HashProbeFind(uint8_t* pC, void** ppOut,
                   int32_t* pKey);

} // namespace msg
#endif
