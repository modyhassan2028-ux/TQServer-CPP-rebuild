// ============================================================================
// CMsgSynMemberInfo.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   original path: modules/syndicate/src/msg/msgsynmemberinfo.cpp
//   vtable 0x14183df00 · base tq::CMsg::vftable 0x14182d368
//     slot 0  0x1417dd1e0 deleting dtor
//     slot 1  0x1417dd0d0 Create (msg type 0x458)
//     slot 2  0x14177e2f0 base Process(OBJID idActor, void* pInfo) stub
//     slot 3  0x1417dd1c0 Process(idActor) -> tail 0x1417ae9b0(mgr, idActor)
//     slot 4  0x14177e2d0 base Process(void* pInfo) stub
//   sender 0x1417dd100 payload at +0x408 (0x1c bytes):
//     u16 +0x00 = 0x1c · u16 +0x02 = 0x458 · u32 +0x04 = uB · u32 +0x08 = uA
//     char[16] +0x0c = szName (NULL name trips CHECKF at line 47)
// ============================================================================
#ifndef SYNDICATE_CMSGSYNMEMBERINFO_H
#define SYNDICATE_CMSGSYNMEMBERINFO_H
#include <cstdint>
#include "modules/syndicate/src/CMsgSeams.h"
namespace syndicate {

// 0x1417ae9b0 — the member-info handler (mgr, idActor), tail-called
extern void (*g_fn_1417ae9b0)(void* pMgr, uint32_t idActor);

class CMsgSynMemberInfo {
public:
    static constexpr uintptr_t kClassVft = 0x14183df00;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182d368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0x458;
    static constexpr uint16_t kKind = 0x1c;
    static constexpr uint32_t kNameBytes = 0x10;
    static constexpr int kAssertLine = 0x2f;   // 47
    static constexpr const char* kAssertFmt = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
    static constexpr const char* kAssertExpr = "CHECKF";
    static constexpr const char* kAssertFunc = "szName";
    static constexpr const char* kAssertFile =
        "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg"
        "\\msgsynmemberinfo.cpp";

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417dd1e0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417dd0d0
    static void Process(void* self, uint32_t idActor);            // 0x1417dd1c0
    static bool Send(void* self, const char* pszName,
                     uint32_t uA, uint32_t uB);                   // 0x1417dd100
    static void BaseProcessActorInfo(void*, uint32_t, void*);     // 0x14177e2f0
    static void BaseProcessInfo(void*, void*);                    // 0x14177e2d0
};

}  // namespace syndicate
#endif
