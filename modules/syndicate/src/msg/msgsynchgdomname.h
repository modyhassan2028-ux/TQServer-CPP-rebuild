// ============================================================================
// msgsynchgdomname.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynchgdomname.cpp
//   vtable 0x14182e520 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x14177e460 deleting dtor
//     slot 1  0x1417dae60 Create — base Create, then msg type 0x837
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417daee0 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNCHGDOMNAME_H
#define SYNDICATE_MSGSYNCHGDOMNAME_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynChgDomName {
public:
    static constexpr uintptr_t kClassVft = 0x14182e520;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0x837;
    // the reply frame the helper builds inside the payload
    static constexpr uint32_t kOffReplyCmd = 0x00;   // word 0x1c
    static constexpr uint32_t kOffReplyId = 0x02;    // word 0x837
    static constexpr uint32_t kOffReplyFlag = 0x18;  // word = the helper's flag
    static constexpr uint16_t kReplyCmd = 0x1c;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x14177e460
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dae60
    static void Process(void* self, uint32_t idActor);            // 0x1417daee0
    static bool BuildReply(void* self, uint16_t uFlag);           // 0x1417dae90
};

}  // namespace syndicate
#endif
