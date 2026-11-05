// ============================================================================
// synpbsize.h — RAW Syndicate.dll v6159 · the protobuf size/serialize kit behind the
//   interface table at 0x141841788 [ByteSizeLong, SerializeWithCachedSizes, ...]:
//     0x1417e4d40  VarintSize32      — the five size buckets
//     0x1417f4dc0  WriteMessageField — tag(2,2), the sub-message size, then the payload
//     0x1417eba30  ByteSizeLong      — has-bit 2 bytes + one tag per element + varint
//                                      lengths + the string length, cached at +0x34
//     0x1417eb990  Serialize         — the bool field, each element, then the raw string
//   Field layout proved from the instructions: the has mask is the byte at +0x30, the
//   bool is at +0x50, the repeated array is at +0x38 with its count at +0x40, the cached
//   size lands at +0x34, and the trailing std::string is inline at +0x10 (SSO when the
//   capacity at +0x28 is under 0x10) with its length at +0x20.
// ============================================================================
#ifndef SYNDICATE_SYNPBSIZE_H
#define SYNDICATE_SYNPBSIZE_H

#include <cstdint>

namespace tq {

// 0x1417f5400 — writes the tag varint (field << 3 | type)
extern void (*g_fnPbWriteTag)(uint32_t uField, uint32_t uType, void* pOut);
// 0x1417ea4c0 — the element ByteSizeLong the cached-size walk calls directly
extern int32_t (*g_fnPbElemByteSize)(void* pElem);
// 0x1417e4a60 — writes a bare varint
extern void (*g_fnPbWriteVarintNoTag)(void* pOut, uint32_t uValue);

int32_t SynPbVarintSize32(uint32_t uValue);                       // 0x1417e4d40
void SynPbWriteMessageField(uint32_t uField, void* pSub, void* pOut);  // 0x1417f4dc0
int32_t SynPbMsgByteSize188(void* pMsg);                          // 0x1417eba30
void SynPbMsgSerialize188(void* pMsg, void* pOut);                // 0x1417eb990

}  // namespace tq

#endif  // SYNDICATE_SYNPBSIZE_H
