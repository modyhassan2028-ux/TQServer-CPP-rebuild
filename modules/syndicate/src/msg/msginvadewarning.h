// ============================================================================
// CMsgInvadeWarning.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   vtable 0x14183bf30 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417d52f0 deleting dtor
//     slot 1  0x1417d5170 Create  (msg type 0xc1c)
//     slot 2  0x14177e2f0 base Process(OBJID idActor, void* pInfo) stub
//     slot 3  0x14177e2e0 base Process(OBJID idActor) stub
//     slot 4  0x14177e2d0 base Process(void* pInfo) stub
//   sender 0x1417d51a0 fills the payload at +0x408:
//     u16 +0x00 = 0x22 · u16 +0x02 = 0xc1c · u16 +0x04 = 0
//     u32 +0x06 · u32 +0x0a · u32 +0x0e · char* string copied at +0x12
// ============================================================================
#ifndef SYNDICATE_CMSGINVADEWARNING_H
#define SYNDICATE_CMSGINVADEWARNING_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {


class CMsgInvadeWarning {
public:
    static constexpr uintptr_t kClassVft = 0x14183bf30;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;
    static constexpr uint16_t kMsgType = 0xc1c;
    static constexpr uint16_t kKind = 0x22;

    static void* DeleteDtor(void* self, uint32_t uFlag);          // 0x1417d52f0
    static bool Create(void* self, char* pData, uint16_t uType);  // 0x1417d5170
    static bool Send(void* self, uint32_t uA, uint32_t uB, uint32_t uC,
                     const char* pszName);                        // 0x1417d51a0
    static void BaseProcessActorInfo(void*, uint32_t, void*);     // 0x14177e2f0
    static void BaseProcessActor(void*, uint32_t);                // 0x14177e2e0
    static void BaseProcessInfo(void*, void*);                    // 0x14177e2d0
};

}  // namespace syndicate
#endif
