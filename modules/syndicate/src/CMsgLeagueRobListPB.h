// ============================================================================
// CMsgLeagueRobListPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x141841f68
//   slot 0  0x1417eef10  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417eeaf0  New (allocates 0x58)
//   slot 3  0x1417eeb60  Clear
//   slot 4  0x1417eeda0  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  thunk to 0x1417dd260
//   slots 7-9  MergePartialFromCodedStream / ByteSize / Serialize (pending)
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417eea50  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEROBLISTPB_H
#define SYNDICATE_CMSGLEAGUEROBLISTPB_H
#include <cstdint>
#include <string>
namespace syndicate {

class CMsgLeagueRobListPB {
public:
    static constexpr uintptr_t kClassVft = 0x141841f68;
    static constexpr const char* kTypeName = "CMsgLeagueRobListPB";

    // 0x1417eef10
    static void* DeleteDtor(void* self, uint32_t uFlag);
    // 0x1417eeaf0
    static void* New();
    // slot 1 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417eeb60
    static void Clear(void* self);
    // 0x1417eeda0
    static bool IsInitialized(void* self);
    // 0x1417eea50
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
