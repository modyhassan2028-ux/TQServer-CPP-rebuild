// ============================================================================
// msgsynbaseproffer.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynbaseproffer.cpp
//   vtable 0x14183d888 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417dadc0 deleting dtor
//     slot 1  0x1417dacb0 Create — base Create, then msg type 0x425
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417dadb0 Process(OBJID) — empty body (plain ret)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNBASEPROFFER_H
#define SYNDICATE_MSGSYNBASEPROFFER_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynBaseProffer {
public:
    static constexpr uintptr_t kClassVft = 0x14183d888;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x425;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dadc0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dacb0
    static void Process(void* self, uint32_t idActor);            // 0x1417dadb0
};

}  // namespace syndicate
#endif
