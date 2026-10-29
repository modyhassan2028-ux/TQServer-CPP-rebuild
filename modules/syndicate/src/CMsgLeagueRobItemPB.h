// ============================================================================
// CMsgLeagueRobItemPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x141841e08
//   slot 0  0x1417ee420  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417ee1d0  New (allocates 0x48)
//   slot 3  0x1417edc50  Clear
//   slot 4  0x1417edec0  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  thunk to 0x1417dd260
//   slots 7-9  MergePartialFromCodedStream / ByteSize / Serialize (pending)
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417ee0d0  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEROBITEMPB_H
#define SYNDICATE_CMSGLEAGUEROBITEMPB_H
#include <cstdint>
#include <string>
namespace syndicate {

class CMsgLeagueRobItemPB {
public:
    static constexpr uintptr_t kClassVft = 0x141841e08;
    static constexpr const char* kTypeName = "CMsgLeagueRobItemPB";

    // 0x1417ee420
    static void* DeleteDtor(void* self, uint32_t uFlag);
    // 0x1417ee070
    static void* Ctor(void* self);
    // 0x1417ee420 base body (sentinel string at +0x38)
    static void BaseDtor(void* self);
    // 0x1417ee1d0
    static void* New();
    // slot 1 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417edc50
    static void Clear(void* self);
    // 0x1417edec0
    static bool IsInitialized(void* self);
    // 0x1417ee0d0
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
