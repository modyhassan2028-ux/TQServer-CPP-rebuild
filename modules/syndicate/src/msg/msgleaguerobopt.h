// ============================================================================
// msgleaguerobopt.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgleaguerobopt.cpp
//   vtable 0x14183cc78 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417d86a0 deleting dtor (PB sub-object at +0x408)
//     slot 1  0x1417d8420 Create — type 0xa52 then PB ParseFromArray
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417d8920 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGLEAGUEROBOPT_H
#define SYNDICATE_MSGLEAGUEROBOPT_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgLeagueRobOpt {
public:
    static constexpr uintptr_t kClassVft = 0x14183cc78;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0xa52;
    static constexpr uintptr_t kFmtParseErr = 0x14183cd30;  // "...,error：%s"
    static constexpr uintptr_t kFmtParseFail = 0x14183ccf0; // "failed."

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417d86a0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417d8420
    static void Process(void* self, uint32_t idActor);            // 0x1417d8920
};

}  // namespace syndicate
#endif
