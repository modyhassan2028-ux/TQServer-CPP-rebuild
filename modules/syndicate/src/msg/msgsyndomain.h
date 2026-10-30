// ============================================================================
// msgsyndomain.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsyndomain.cpp
//   vtable 0x14183de00 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417dcff0 deleting dtor (destroys the sub-object at +0x410)
//     slot 1  0x1417dcb30 Create — base Create, then msg type 0x9ce
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417dcf90 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNDOMAIN_H
#define SYNDICATE_MSGSYNDOMAIN_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynDomain {
public:
    static constexpr uintptr_t kClassVft = 0x14183de00;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint32_t kOffSubObject = 0x410;
    static constexpr uint16_t kMsgType = 0x9ce;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dcff0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dcb30
    static void Process(void* self, uint32_t idActor);            // 0x1417dcf90
};

}  // namespace syndicate
#endif
