// ============================================================================
// msgsynattrinfo.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynattrinfo.cpp
//   vtable 0x14183d768 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417dabe0 deleting dtor
//     slot 1  0x1417da8e0 Create — base Create, then msg type 0x452
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x1417daba0 Process(OBJID) — ASSERT trap (line 121)
//     slot 4  0x14177e2d0 base Process(void*) stub
// ============================================================================
#ifndef SYNDICATE_MSGSYNATTRINFO_H
#define SYNDICATE_MSGSYNATTRINFO_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgSynAttrInfo {
public:
    static constexpr uintptr_t kClassVft = 0x14183d768;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint16_t kMsgType = 0x452;
    static constexpr int kAssertLine = 0x79;   // 121
    static constexpr const char* kAssertFmt = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
    static constexpr const char* kAssertExpr = "ASSERT";
    static constexpr const char* kAssertFunc = "\"CMsgSynAttrInfo::Process()\"";
    static constexpr const char* kAssertFile =
        "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg"
        "\\msgsynattrinfo.cpp";

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dabe0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417da8e0
    static void Process(void* self, uint32_t idActor);            // 0x1417daba0
};

}  // namespace syndicate
#endif
