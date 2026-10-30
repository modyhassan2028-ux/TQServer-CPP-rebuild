// ============================================================================
// flowerservice.h — RAW Flower.dll v6159
//   original path: modules/flower/src/flowerservice.cpp
//   flower::CFlowerService — vftable 0x140d9be08, 5 slots
//     slot 0  0x140d93630  deleting dtor (Complete 0x140d932f0, then delete)
//     slot 1  0x140d93360  release: vfunc0(this, 1) when this != 0
//     slot 2  0x140d93380  "initialize": kernel slot +0x30 (mode 9), owned
//                          object at +0x420, then 0x140d91490
//     slot 3  0x140d934e0  owned object's slot 0, no arguments
//     slot 4  0x140d93660  dispatch by the packed u16 at record+2
//   helpers: Lookup 0x140d93460 · Attach 0x140d91490
// ============================================================================
#ifndef FLOWER_FLOWERSERVICE_H
#define FLOWER_FLOWERSERVICE_H
#include <cstdint>
#include "modules/flower/src/module.h"

namespace flower {

// log_InlineLogERROR with the CHECKF blob (0x140d9b368)
extern void (*g_pfnFlowerLog)(const char* fmt, ...);
extern const char kCheckFormat[];
inline void CTodayFlowerMgr_LogCheck() { g_pfnFlowerLog(kCheckFormat); }

// FUN_140d97bc0 () -> the object attached at +0x18
extern void* (*g_pfnFlowerCreateHelper)();
// FUN_140d94020 (pAttached, pSecond) -> bool
extern uint8_t (*g_pfnFlowerAttachInit)(void* pAttached, void* pSecond);

class CFlowerService {
public:
    static constexpr uintptr_t kClassVft = 0x140d9be08;

    static void* DeleteDtorFull(void* self, uint64_t uFlag, void* pB, void* pC);
    static uint8_t Release(void* self);               // 0x140d93360
    static uint8_t Initialize(void* self);            // 0x140d93380
    static void ReleaseOwned(void* self);             // 0x140d934e0
    static uint16_t Process(void* self, uint32_t dwArg, uint16_t* pRecord,
                            uint16_t uCount);         // 0x140d93660
    static void* Lookup(void* self, uint16_t* pRecord,
                        uint16_t uCount);             // 0x140d93460
    static uint8_t Attach(void* pOwned, void* pSecond);  // 0x140d91490
};

}  // namespace flower
#endif
