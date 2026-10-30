// ============================================================================
// msgsyndicate.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsyndicate.cpp
//   vtable 0x14183dc10 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417dca00 deleting dtor (sub-object at +0x410, IAT 0x1418230a0)
//     slot 1  0x1417db370 Create — base Create, then msg type 0x453
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417db7b0 Process(OBJID) — 4297-byte body, ported in
//             SyndicateMsgSyndicate.cpp (MsgSyndicateProcess)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNDICATE_H
#define SYNDICATE_MSGSYNDICATE_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSyndicate {
public:
    static constexpr uintptr_t kClassVft = 0x14183dc10;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffSubObject = 0x410;
    static constexpr uint16_t kMsgType = 0x453;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dca00
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417db370
    static void Process(void* self, uint32_t idActor);            // 0x1417db7b0
};

}  // namespace syndicate
#endif
