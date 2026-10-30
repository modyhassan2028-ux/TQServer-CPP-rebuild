// ============================================================================
// module.h — RAW Syndicate.dll v6159
//   original path: modules/syndicate/src/module.cpp
//   (the CHECKF logs carry exactly this path, line 0x1e / 0x22)
//   three class shapes live here:
//     tq::CMsg      vftable 0x14182e368 (5 slots)
//     gs::IModule   vftable 0x14182e428 (9 slots)
//     syndicate::CModule vftable 0x14182e5a8 (9 slots)
// ============================================================================
#ifndef SYNDICATE_MODULE_H
#define SYNDICATE_MODULE_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

// ---- tq::CMsg — the message base (slots 2/3/4 are the error stubs)
class CMsgBase {
public:
    static constexpr uintptr_t kClassVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uintptr_t kFmtProcessInfo = 0x14182e390;   // Process(void*)
    static constexpr uintptr_t kFmtProcessActor = 0x14182e3b8;  // Process(OBJID)
    static constexpr uintptr_t kFmtProcessBoth = 0x14182e3e0;   // (OBJID, void*)

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x14177e300
    static void ProcessInfo(void* self);                  // 0x14177e2d0
    static void ProcessActor(void* self, uint32_t idActor);   // 0x14177e2e0
    static void ProcessBoth(void* self, uint32_t idActor,
                            void* pInfo);                 // 0x14177e2f0
};

// ---- gs::IModule — the module interface
class IModule {
public:
    static constexpr uintptr_t kClassVft = 0x14182e428;
    static constexpr uintptr_t kPureCallThunk = 0x1417f3374;

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x14177e380
    static bool PureVirtual();
    static bool Off340();  // 0x14177e340
    static bool Off350();  // 0x14177e350
    static bool Off360();  // 0x14177e360
    static bool Off370();  // 0x14177e370
};

// ---- syndicate::CModule — the module root (member messages at fixed offsets)
class CModule {
public:
    static constexpr uintptr_t kClassVft = 0x14182e5a8;
    static constexpr uintptr_t kBaseIModuleVft = 0x14182e428;
    static constexpr uint32_t kOffConsumer = 0x420;

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x14177ec00
    static void MemberDtor(void* self);                   // 0x14177e4c0
    static bool Slot600(void* self, void* pObj);          // 0x14177e600
    static bool Init(void* self);                          // 0x14177e620
    static void* SlotAA0(void* self);                      // 0x14177eaa0
    static void* CreateMsg(void* self, uint32_t uCount32,
                           void* pPacket,
                           uint16_t uCount16);             // 0x14177ec30
    static void* CreateMsgCore(void* self, void* pPacket,
                               uint16_t uCount);           // 0x14177e6c0
};

// ---- the member-destructor seams (called with only `this` in rcx)
extern void (*g_fnModBaseDtor)(void*);        // 0x1417a9ed0
extern void (*g_fnModMem41a8)(void*);         // 0x1417d83e0
extern void (*g_fnModMem3d50)(void*);         // 0x1417d9050
extern void (*g_fnModMem3928)(void*);         // 0x1417d66c0
extern void (*g_fnModMem3518)(void*);         // 0x1417ddfa0
extern void (*g_fnModMem3108)(void*);         // 0x1417de290
extern void (*g_fnModMem2cf8)(void*);         // 0x1417ddcb0
extern void (*g_fnModMem28e8)(void*);         // 0x1417d9eb0
extern void (*g_fnModMem24d8)(void*);         // 0x1417dda40
extern void (*g_fnModMem20c8)(void*);         // 0x1417dac80
extern void (*g_fnModMem1cb8)(void*);         // 0x1417dd280
extern void (*g_fnModMem18a8)(void*);         // 0x1417dd0a0
extern void (*g_fnModMem1088)(void*);         // 0x1417da8b0
extern void (*g_fnModMem0c78)(void*);         // 0x1417dd730
extern void (*g_fnModMem0850)(void*);         // 0x1417dcaf0
extern void (*g_fnModMem0428)(void*);         // 0x1417db330
extern void (*g_fnModPureCall)();             // 0x1418232b8 (the purecall slot)
// the same 0x141823030 import, called with the format pointer only
extern void (*g_fnModuleLog1)(const char* pFmt);
extern bool (*g_fnModProviderInit)(void* pMgr, void* pProvider);  // 0x1417a96f0
extern void* (*g_fnModSlotAA0Tail)(void* pMgr);  // 0x1417ac5e0

}  // namespace syndicate
#endif
