// ============================================================================
// msgsynrecruitadvertisinglist.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynrecruitadvertisinglist.cpp
//   vtable 0x14183e508 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417de1f0 deleting dtor
//     slot 1  0x1417ddfd0 Create — base Create, then msg type 0x8b2
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417de120 Process(OBJID) — verbatim body in
//             SyndicateMsgProcess2.cpp (MsgSynRecruitAdvertisingListProcess)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNRECRUITADVERTISINGLIST_H
#define SYNDICATE_MSGSYNRECRUITADVERTISINGLIST_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynRecruitAdvertisingList {
public:
    static constexpr uintptr_t kClassVft = 0x14183e508;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x8b2;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417de1f0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417ddfd0
    static void Process(void* self, uint32_t idActor);            // 0x1417de120
};

}  // namespace syndicate
#endif
