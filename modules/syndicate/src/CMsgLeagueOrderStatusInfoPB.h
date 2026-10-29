// ============================================================================
// CMsgLeagueOrderStatusInfoPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x1418419c8
//   slot 0  0x1417ecae0  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417ec840  New (allocates 0x48)
//   slot 3  0x1417ec270  Clear
//   slot 4  0x1417ec4e0  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  0x1417ecd70 thunk -> 0x1417ec3b0 MergeFrom
//   slots 7-9  0x1417ecb40 Merge / 0x1417ec320 ByteSize / 0x1417ec290 Serialize
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417ec780  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEORDERSTATUSINFOPB_H
#define SYNDICATE_CMSGLEAGUEORDERSTATUSINFOPB_H
#include <cstdint>
#include <string>
namespace syndicate {

// ---- seams ----
extern void     (*g_pfnPbFree)(void*);        // operator_delete
extern uint64_t (*g_pfnPb8050)();             // 1417e8050
extern void*     g_pPbDefaultStr;             // DAT_141886ea0
// the shared protobuf kit (defined in CMsgLeagueConcubinesInfoPB.cpp)
extern int32_t (*g_pfnPbVarintSize)(uint32_t);
extern void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*);
extern void (*g_pfnPbWriteString)(uint32_t, void*, void*);
extern void (*g_pfnPbWriteBool)(uint32_t, char, void*);
extern void (*g_pfnPbWriteUnknown)(void*, void*, int32_t);
extern void (*g_pfnPb64C0)(void*, void*);
extern void (*g_pfnPb4550)(void*, void*);
extern uint64_t (*g_pfnPb3BC0)(void*);
extern uint64_t (*g_pfnPb3A50)(void*, uint32_t*);
extern void (*g_pfnPb45D0)(void*);
extern uint64_t (*g_pfnPb6510)(void*);
extern char (*g_pfnPbF3F50)(void*, uint32_t, void*);
// D94 additions defined in this class
extern uint64_t (*g_pfnPbE4DA0)(uint64_t);
extern void (*g_pfnPbWriteVarint64)(uint32_t, uint64_t, void*);
extern uint64_t (*g_pfnPbE3D80)(void*, uint64_t*);
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);

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
    // 0x1417ec320 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417ec290 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417ecb40 — Merge
    static bool Merge(void* self, void* input);
    // 0x1417ec3b0 — MergeFrom (slot6 thunk 0x1417ecd70)
    static void MergeFrom(void* self, void* from);
    // 0x1417ec780
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
