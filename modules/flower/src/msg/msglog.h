// ============================================================================
// msglog.h — RAW Flower.dll v6159
//   original path: modules/flower/src/msg/msglog.cpp
//   vtable 0x140d9dc60 (5 slots), class flower::CMsgLog
//     slot 0  0x140d98170 deleting dtor
//     slot 1  0x140d98090 Create  (0x3ea -> payload[8]=0, 0x3eb -> =1)
//     slot 2  0x140d980f0 Process (payload[8]: 0 -> vt[+0x08], 1 -> vt[+0x10])
//     slot 3  0x140d97c60 Process(OBJID) stub
//     slot 4  0x140d97c50 Process(void* pInfo) stub
//   ctor 0x140d98010
// ============================================================================
#ifndef FLOWER_MSGS_LOG_H
#define FLOWER_MSGS_LOG_H
#include <cstdint>
#include "modules/flower/src/msg/msgflower.h"

namespace flower {

class CMsgLog : public syndicate::CMsgBase {
public:
    static constexpr uintptr_t kClassVft = 0x140d9dc60;
    static constexpr uintptr_t kBaseVft = syndicate::CMsgBase::kVft;
    static constexpr uint32_t kOffPayloadPtr = 0x408;

    static void* Ctor(void* self);                          // 0x140d98010
    static void* DeleteDtor(void* self, uint32_t uFlag);    // 0x140d98170
    static bool Create(void* self, char* pData,
                       uint16_t uType);                     // 0x140d98090
    static void Process(void* self, void* pActor,
                        void* pInfo);                       // 0x140d980f0
};

}  // namespace flower
#endif
