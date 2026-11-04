// ============================================================================
// synattrsend.h — RAW Syndicate.dll v6159 · the attribute send path,
//   0x1417c6a60 / 0x1417c6b30 (the two entries) and 0x1417db530 (the CMsgSyndicate
//   announce builder). The two entries only guard their arguments (both report through
//   the CHECKF log when a pointer is null) and then hand over to the same core,
//   0x1417c5640, which is not ported yet and therefore stays a seam.
//     by user   : id = 0x141785dc0(pAttrInfo), then the core
//     by id     : obj = 0x14178c8e0(owner->[+0x90], uId), then the core
//   The builder writes the message the original writes:
//     hdr[+0] = the packer size + 0x1b (the whole message), hdr[+2] = 0x453,
//     hdr[+4] = the action (u16), hdr[+8] = the parameter (u32), then the string at +0x1b.
// ============================================================================
#ifndef SYNDICATE_SYNATTRSEND_H
#define SYNDICATE_SYNATTRSEND_H

#include <cstdint>

namespace tq {

// tq::CStringPacker::GetSize — the packer at +0x410 of the message
extern uint32_t (*g_fnSynMsgPackerSize)(void* pPacker);
// 0x141788040 — fill the 0x28 attribute record from the attribute pointer
extern void (*g_fnSynAttrFillRec)(void* pAttrInfo, void* pRec);
// 0x1417da910 — build the attribute message out of the record (false = refused)
extern bool (*g_fnSynAttrMsgInit)(void* pMsg, void* pRec, void* pUser);

// 0x1417c5640 — the shared insert core (this implementation)
void SynAttrInsertCore(void* pOwner, void* pUser, void* pAttrInfo, uint32_t uId, char cAnnounce);

// the hook the two entries call, so a caller (or a test) can replace the core

extern void (*g_fnSynAttrInsertCore)(void* pOwner, void* pUser, void* pAttrInfo,
                                     uint32_t uId, char cAnnounce);

// 0x1417db530 — build the CMsgSyndicate announce; false when an argument is rejected
bool SynMsgSyndicateAnnounce(void* pMsg, uint16_t uAction, uint32_t uParam, const char* pszText);

// 0x1417c6a60 — insert through the attribute pointer, the id read from it
void SynAttrInsertByUser(void* pOwner, void* pUser, void* pAttrInfo, char cAnnounce);

// 0x1417c6b30 — insert through an id, the object looked up in the owner
void SynAttrInsertById(void* pOwner, void* pUser, uint32_t uId, char cAnnounce);

}  // namespace tq

#endif  // SYNDICATE_SYNATTRSEND_H
