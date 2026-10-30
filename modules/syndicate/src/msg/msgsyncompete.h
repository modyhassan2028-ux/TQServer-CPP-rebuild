// ============================================================================
// msgsyncompete.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsyncompete.cpp
//   vtable 0x14183dad0 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417db260 deleting dtor
//     slot 1  0x1417dafe0 Create — base Create, then msg type 0x426
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x14177e2e0 base Process(OBJID) error stub — NOT overridden
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNCOMPETE_H
#define SYNDICATE_MSGSYNCOMPETE_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynCompete {
public:
    static constexpr uintptr_t kClassVft = 0x14183dad0;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x426;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417db260
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dafe0
};

}  // namespace syndicate
#endif
