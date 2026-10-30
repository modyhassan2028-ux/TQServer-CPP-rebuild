// ============================================================================
// msgleaguetoken.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgleaguetoken.cpp
//   vtable 0x14183cfa0 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417d93b0 deleting dtor (PB sub-object at +0x408)
//     slot 1  0x1417d9090 Create — type 0xa49 then PB ParseFromArray
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417d92d0 Process(OBJID)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGLEAGUETOKEN_H
#define SYNDICATE_MSGLEAGUETOKEN_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgLeagueToken {
public:
    static constexpr uintptr_t kClassVft = 0x14183cfa0;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0xa49;
    static constexpr uintptr_t kFmtParseErr = 0x14183d050;  // "...,error：%s"
    static constexpr uintptr_t kFmtParseFail = 0x14183d018; // "failed."

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417d93b0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417d9090
    static void Process(void* self, uint32_t idActor);            // 0x1417d92d0
};

}  // namespace syndicate
#endif
