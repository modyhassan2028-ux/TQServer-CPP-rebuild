// ============================================================================
// CMsgLeagueOrderStatusPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x141841b48
//   slot 0  0x1417ed5c0  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417ed230  New (allocates 0x58)
//   slot 3  0x1417ed2a0  Clear
//   slot 4  0x1417ed450  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  thunk to 0x1417dd260
//   slots 7-9  MergePartialFromCodedStream / ByteSize / Serialize (pending)
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417ed190  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEORDERSTATUSPB_H
#define SYNDICATE_CMSGLEAGUEORDERSTATUSPB_H
#include <cstdint>
#include <string>
namespace syndicate {

class CMsgLeagueOrderStatusPB {
public:
    static constexpr uintptr_t kClassVft = 0x141841b48;
    static constexpr const char* kTypeName = "CMsgLeagueOrderStatusPB";

    // 0x1417ed5c0
    static void* DeleteDtor(void* self, uint32_t uFlag);
    // 0x1417ed230
    static void* New();
    // slot 1 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417ed2a0
    static void Clear(void* self);
    // 0x1417ed450
    static bool IsInitialized(void* self);
    // 0x1417ed190
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
