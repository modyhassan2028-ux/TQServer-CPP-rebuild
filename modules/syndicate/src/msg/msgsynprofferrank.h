// ============================================================================
// msgsynprofferrank.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynprofferrank.cpp
//   vtable 0x14183e2b0 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417ddc10 deleting dtor
//     slot 1  0x1417dda70 Create — base Create, then msg type 0x835
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417ddbb0 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNPROFFERRANK_H
#define SYNDICATE_MSGSYNPROFFERRANK_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynProfferRank {
public:
    static constexpr uintptr_t kClassVft = 0x14183e2b0;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0x835;
    static constexpr uint32_t kOffRankA = 0x04;  // byte
    static constexpr uint32_t kOffRankB = 0x05;  // byte

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417ddc10
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dda70
    static void Process(void* self, uint32_t idActor);            // 0x1417ddbb0
};

}  // namespace syndicate
#endif
