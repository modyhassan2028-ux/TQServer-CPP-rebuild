// ============================================================================
// CMsgLog.h — RAW Syndicate.dll v6159 · tq::CMsg-derived message class
//   vtable 0x14182e4a0 (5 slots) · base tq::CMsg::vftable 0x14182d368
//     slot 0  0x14177e3e0 deleting dtor
//     slot 1  0x1417d9760 Create(this, char* pData, uint16_t type)
//     slot 2  0x14177e2f0 tq::CMsg::Process(OBJID, void*) error stub
//     slot 3  0x1417d97c0 CMsgLog::Process(this, uint32_t idActor)
//     slot 4  0x14177e2d0 tq::CMsg::Process(void*) error stub
//   layout: uint16 msgType +0x0A · void* payload +0x408 (int type at +0x8)
//   accepted message types: 0x3ea -> type 0 · 0x3eb -> type 1
// ============================================================================
#ifndef SYNDICATE_CMSGLOG_H
#define SYNDICATE_CMSGLOG_H
#include <cstdint>
#include "modules/syndicate/src/CMsgSeams.h"
namespace syndicate {


// 0x1417b6210 — the SyndicateMgr accessor
extern void* (*g_pfnGetSyndicateMgr)();
// 0x1417b7010 — the type-0 handler (this, uint32_t idActor)
extern void (*g_pfnLogProcessA)(void* mgr, uint32_t idActor);
// 0x1417ac620 — the type-1 handler (this, uint32_t idActor)
extern void (*g_pfnLogProcessB)(void* mgr, uint32_t idActor);
// InlineLogERROR, resolved through the import at 0x141827030

class CMsgLog {
public:
    static constexpr uintptr_t kClassVft = 0x14182e4a0;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182d368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kTypeA = 0x3ea;
    static constexpr uint16_t kTypeB = 0x3eb;

    static void* DeleteDtor(void* self, uint32_t uFlag);             // 0x14177e3e0
    static bool Create(void* self, char* pData, uint16_t uType);     // 0x1417d9760
    static void Process(void* self, uint32_t idActor);               // 0x1417d97c0
    // the base stubs the class keeps in slots 2 and 4
    static void BaseProcessActor(void* self, uint32_t idActor, void* pInfo);
    static void BaseProcessInfo(void* self, void* pInfo);
};

}  // namespace syndicate
#endif
