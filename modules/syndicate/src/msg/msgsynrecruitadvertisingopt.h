// ============================================================================
// msgsynrecruitadvertisingopt.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynrecruitadvertisingopt.cpp
//   vtable 0x14183e620 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417de410 deleting dtor
//     slot 1  0x1417de2c0 Create — base Create, then msg type 0x8b3
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417de2f0 Process(OBJID) — verbatim body in
//             SyndicateMsgProcess2.cpp (MsgSynRecruitAdvertisingOptProcess)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNRECRUITADVERTISINGOPT_H
#define SYNDICATE_MSGSYNRECRUITADVERTISINGOPT_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynRecruitAdvertisingOpt {
public:
    static constexpr uintptr_t kClassVft = 0x14183e620;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x8b3;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417de410
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417de2c0
    static void Process(void* self, uint32_t idActor);            // 0x1417de2f0
};

}  // namespace syndicate
#endif
