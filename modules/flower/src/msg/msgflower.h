// ============================================================================
// msgflower.h — RAW Flower.dll v6159
//   original path: modules/flower/src/msg/msgflower.cpp
//   vtable 0x140d9db08 (5 slots), class flower::CMsgFlower
//     slot 0  0x140d97fc0 deleting dtor
//     slot 1  0x140d97ec0 Create(CMsg*, char*, ushort)
//     slot 2  0x140d97ef0 Process(void*)
//     slot 3  0x140d97c60 Process(OBJID) stub
//     slot 4  0x140d97c50 Process(void* pInfo) stub
//   ctor 0x140d97cb0 · Init chain tq::CMsg::Init, payload ptr at +0x408
// ============================================================================
#ifndef FLOWER_MSGS_FLOWER_H
#define FLOWER_MSGS_FLOWER_H
#include <cstdint>
#include <cstring>
#include "modules/syndicate/src/msg/cmsgbase.h"

namespace flower {

class CMsgFlower : public syndicate::CMsgBase {
public:
    static constexpr uintptr_t kClassVft = 0x140d9db08;
    static constexpr uintptr_t kBaseVft = syndicate::CMsgBase::kVft;
    static constexpr uint16_t kMsgType = 0x047e;   // Create accepts only this
    static constexpr uint32_t kOffPayloadPtr = 0x408;

    static void* Ctor(void* self);                        // 0x140d97cb0
    static void BaseDtor(void* self);                     // 0x140d97d00
    // 0x140d97d30 — build the 0x3c/0x047e record into the payload buffer:
    //   +0  u16 0x3c · +2 u16 0x047e · +4 u16 child
    //   +0x10 two 16-byte names · +0x30 u32 · +0x34 u32 · +0x38 u8
    static bool Build(void* self, uint16_t uChild, const char* pSender,
                      const char* pReceiver, uint32_t uValue, uint32_t uSlot,
                      uint8_t uFlag);
    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x140d97fc0
    static bool Create(void* self, char* pData,
                       uint16_t uType);                   // 0x140d97ec0
    static void Process(void* self, void* pActor,
                        void* pInfo);                     // 0x140d97ef0
    static void ProcessActor(void* self, uint32_t idActor);   // 0x140d97c60
    static void ProcessInfo(void* self, void* pInfo);         // 0x140d97c50
};

}  // namespace flower
#endif
