// ============================================================================
// CMsgBase.h — RAW Syndicate.dll v6159 · tq::CMsg, the message base class
//   vtable 0x14182e368
//     slot 0  0x14177e300 deleting dtor (writes 0x14182e368, delete on bit 0)
//     slot 1  0x1417e7fda imported Create thunk -> IAT 0x141823000
//     slot 2  0x14177e2f0 Process(OBJID idActor, void* pInfo) stub
//     slot 3  0x14177e2e0 Process(OBJID idActor) stub
//     slot 4  0x14177e2d0 Process(void* pInfo) stub
//   NOTE: the class is tq::CMsg, so the original file lived in a tq module;
//   the exact path is not recoverable from this binary. Kept beside the
//   syndicate messages for now.
// ============================================================================
#ifndef SYNDICATE_CMSGBASE_H
#define SYNDICATE_CMSGBASE_H
#include <cstdint>
#include "modules/syndicate/src/CMsgSeams.h"
namespace syndicate {

class CMsgBase {
public:
    static constexpr uintptr_t kVft = 0x14182e368;
    static constexpr uint32_t kOffMsgType = 0x0A;
    static constexpr uint32_t kOffPayload = 0x408;

    static void* DeleteDtor(void* self, uint32_t uFlag);           // 0x14177e300
    static bool Create(void* self, char* pData, uint16_t uType);   // 0x1417e7fda
    static void ProcessActorInfo(void*, uint32_t, void*);          // 0x14177e2f0
    static void ProcessActor(void*, uint32_t);                     // 0x14177e2e0
    static void ProcessInfo(void*, void*);                          // 0x14177e2d0
};

}  // namespace syndicate
#endif
