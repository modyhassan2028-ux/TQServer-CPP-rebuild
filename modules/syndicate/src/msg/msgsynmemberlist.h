// ============================================================================
// msgsynmemberlist.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynmemberlist.cpp
//   vtable 0x14183e010 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417dd690 deleting dtor
//     slot 1  0x1417dd2b0 Create — base Create, then msg type 0x836
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417dd610 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNMEMBERLIST_H
#define SYNDICATE_MSGSYNMEMBERLIST_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynMemberList {
public:
    static constexpr uintptr_t kClassVft = 0x14183e010;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0x836;
    static constexpr const char* kInvalidActionFmt =
        "CMsgSynMemberList::Process invalid action:%d";

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dd690
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dd2b0
    static void Process(void* self, uint32_t idActor);            // 0x1417dd610
};

}  // namespace syndicate
#endif
