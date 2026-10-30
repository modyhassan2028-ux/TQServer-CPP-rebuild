// ============================================================================
// msgsynrecruitadvertising.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynrecruitadvertising.cpp
//   vtable 0x14183e3f8 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417ddf00 deleting dtor
//     slot 1  0x1417ddce0 Create — base Create, then msg type 0x8b1
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417ddd90 Process(OBJID) — verbatim body in
//             SyndicateMsgProcess2.cpp (MsgSynRecruitAdvertisingProcess)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNRECRUITADVERTISING_H
#define SYNDICATE_MSGSYNRECRUITADVERTISING_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynRecruitAdvertising {
public:
    static constexpr uintptr_t kClassVft = 0x14183e3f8;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x8b1;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417ddf00
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417ddce0
    static void Process(void* self, uint32_t idActor);            // 0x1417ddd90
};

}  // namespace syndicate
#endif
