// ============================================================================
// module.h — RAW Flower.dll v6159
//   original path: modules/flower/src/module.cpp
//   flower::CModule — object size 0x848, vftable 0x140d9bcb8 (9 slots)
//     slot 0  0x140d93290 deleting dtor  (resets [this] to the base vftable)
//     slot 1..4  0x140d982ac _purecall
//     slot 5..8  0x140d93250 / 0x140d93260 / 0x140d93270 / 0x140d93280
//                (each is `xor eax,eax` -> return 0)
//   ctor           0x140d935b0
//   complete dtor  0x140d932f0
//   members: +0x000 vft · +0x008 dwModuleIndex · +0x010 CMsgLog
//            +0x420 owned object · +0x428 CMsgFlower · +0x838 zero
//            +0x840 kernel
// ============================================================================
#ifndef FLOWER_MODULE_H
#define FLOWER_MODULE_H
#include <cstdint>
#include "modules/flower/src/msg/msgflower.h"
#include "modules/flower/src/msg/msglog.h"

namespace flower {

// the CRT _purecall reached through the four pure slots of this vftable
extern void (*g_pfnPureCall)();

class CModule {
public:
    static constexpr uintptr_t kClassVft = 0x140d9bcb8;
    static constexpr uint32_t kSize = 0x848;
    static constexpr uint32_t kOffIndex = 0x008;
    static constexpr uint32_t kOffLog = 0x010;
    static constexpr uint32_t kOffOwned = 0x420;
    static constexpr uint32_t kOffFlower = 0x428;
    static constexpr uint32_t kOffZero = 0x838;
    static constexpr uint32_t kOffKernel = 0x840;

    static void* Ctor(void* self, void* pKernel, uint32_t dwIndex);  // 0x140d935b0
    static void Complete(void* self, uint64_t uA, void* pB,
                         void* pC);                                  // 0x140d932f0
    static void* DeleteDtor(void* self, uint32_t uFlag);             // 0x140d93290
    static uint64_t Slot5();                                         // 0x140d93250
    static uint64_t Slot6();                                         // 0x140d93260
    static uint64_t Slot7();                                         // 0x140d93270
    static uint64_t Slot8();                                         // 0x140d93280
    static void PureCall();                                          // 0x140d982ac
};

}  // namespace flower
#endif
