// ============================================================================
// CMsgPBMemberDtors.h — the member PB destructor bodies that the four
// message wrappers call at byte offset 0x408
// RAW: Syndicate.dll v6159
//   0x1417eb830  CMsgLeagueConcubinesPB member dtor
//   0x1417ed1a0  CMsgLeagueOrderStatusPB member dtor
//   0x1417eea60  CMsgLeagueRobListPB member dtor
//   0x1417f2400  CMsgOverheadLeagueInfoPB member dtor
//   0x1417e0320  the per-string destructor used by the Overhead vector
//   0x1417de5a0  the shared base: writes google::protobuf::MessageLite::vftable
// The Concubines/OrderStatus/RobList bodies are byte-identical apart from the
// vtable they store; the Overhead one walks a string vector at +0x54/+0x48.
#ifndef SYNDICATE_CMSG_PBMEMBERDTORS_H
#define SYNDICATE_CMSG_PBMEMBERDTORS_H
#include <cstdint>

namespace syndicate {

// operator_delete (the worker CRT deallocator)
extern void (*g_pfnPbOperatorDelete)(void* p);

// 0x1417de5a0: writes the protobuf base vftable only.
void PbBaseDtor(void* self);

// 0x1417e0320: delete one vector element when it is not null.
void PbStringDtor(void* elem);

// the four member destructors, each writing its own PB class vtable
// 0x1417eb830
void ConcubinesPbMemberDtor(void* self, uint64_t flags,
                            uint64_t a3, uint64_t a4);
// 0x1417ed1a0
void OrderStatusPbMemberDtor(void* self, uint64_t flags,
                             uint64_t a3, uint64_t a4);
// 0x1417eea60
void RobListPbMemberDtor(void* self, uint64_t flags,
                         uint64_t a3, uint64_t a4);
// 0x1417f2400
void OverheadPbMemberDtor(void* self, uint64_t flags,
                          uint64_t a3, uint64_t a4);

// the class vtables the bodies store (quoted from the RTTI table)
extern const uintptr_t kConcubinesPbVft;    // CMsgLeagueConcubinesPB::vftable
extern const uintptr_t kOrderStatusPbVft;   // CMsgLeagueOrderStatusPB::vftable
extern const uintptr_t kRobListPbVft;       // CMsgLeagueRobListPB::vftable
extern const uintptr_t kOverheadPbVft;      // CMsgOverheadLeagueInfoPB::vftable
extern const uintptr_t kMessageLiteVft;     // google::protobuf::MessageLite::vftable

} // namespace syndicate
#endif
