// ============================================================================
// CMsgLeagueOrderStatusInfoPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x1418419c8
//   slot 0  0x1417ecae0  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417ec840  New (allocates 0x48)
//   slot 3  0x1417ec270  Clear
//   slot 4  0x1417ec4e0  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  thunk to 0x1417dd260
//   slots 7-9  MergePartialFromCodedStream / ByteSize / Serialize (pending)
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417ec780  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEORDERSTATUSINFOPB_H
#define SYNDICATE_CMSGLEAGUEORDERSTATUSINFOPB_H
#include <cstdint>
#include <string>
namespace syndicate {

class CMsgLeagueOrderStatusInfoPB {
public:
    static constexpr uintptr_t kClassVft = 0x1418419c8;
    static constexpr const char* kTypeName = "CMsgLeagueOrderStatusInfoPB";

    // 0x1417ecae0
    static void* DeleteDtor(void* self, uint32_t uFlag);
    // the class dtor body
    static void BaseDtor(void* self);
    // 0x1417ec840
    static void* New();
    // slot 1 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417ec270
    static void Clear(void* self);
    // 0x1417ec4e0
    static bool IsInitialized(void* self);
    // 0x1417ec780
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
