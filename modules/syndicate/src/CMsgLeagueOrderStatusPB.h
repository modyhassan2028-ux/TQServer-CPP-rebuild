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
#include "modules/syndicate/src/CMsgLeagueOrderStatusInfoPB.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
namespace syndicate {

// ---- seams ----
extern void     (*g_pfnPbFree)(void*);
extern uint64_t (*g_pfnPb8050)();
extern void*     g_pPbDefaultStr;
extern int32_t (*g_pfnPbVarintSize)(uint32_t);
extern void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*);
extern void (*g_pfnPbWriteUnknown)(void*, void*, int32_t);
extern void (*g_pfnPb64C0)(void*, void*);
extern void (*g_pfnPb4550)(void*, void*);
extern uint64_t (*g_pfnPb3BC0)(void*);
extern uint64_t (*g_pfnPb3A50)(void*, uint32_t*);
extern void (*g_pfnPb45D0)(void*);
extern uint64_t (*g_pfnPb6510)(void*);
extern char (*g_pfnPbF3F50)(void*, uint32_t, void*);
extern void (*g_pfnPbE0110)(void*, int32_t);
extern char (*g_pfnPbECE60)(void*, void*);
extern void (*g_pfnPbF4DC0)(uint32_t, void*, void*);
extern void (*g_pfnPbECF80)(void*, void*);

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
    // 0x1417ed620 — Merge
    static bool Merge(void* self, void* input);
    // 0x1417ed3b0 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417ed310 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417ed880 — MergeFrom (slot6 thunk 0x1417eda00)
    static void MergeFrom(void* self, void* from);
    // 0x1417ed190
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
