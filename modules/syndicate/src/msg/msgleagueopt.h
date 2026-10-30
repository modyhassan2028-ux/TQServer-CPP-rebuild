// ============================================================================
// msgleagueopt.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgleagueopt.cpp
//   vtable 0x14183c5a8 (SIX slots) · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417d7260 deleting dtor — also destroys the CStringPacker
//             sub-object at +0x410 (tq::CStringPacker::~CStringPacker)
//     slot 1  0x1417e7fda base Create thunk — NOT overridden
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417d68d0 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
//     slot 5  0x1417d6700 CreateBufMsg — base Create then msg type 0xa3e
// ============================================================================
#ifndef SYNDICATE_MSGLEAGUEOPT_H
#define SYNDICATE_MSGLEAGUEOPT_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgLeagueOpt {
public:
    static constexpr uintptr_t kClassVft = 0x14183c5a8;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPacker = 0x410;
    static constexpr uint16_t kBufMsgType = 0xa3e;

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x1417d7260
    static void Process(void* self, uint32_t idActor);    // 0x1417d68d0
    static bool CreateBufMsg(void* self, char* pData, uint16_t uType);
};

}  // namespace syndicate
#endif
