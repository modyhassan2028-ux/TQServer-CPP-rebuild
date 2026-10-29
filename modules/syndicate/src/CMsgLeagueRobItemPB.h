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

// ---- seams ----
extern void     (*g_pfnPbFree)(void*);
extern uint64_t (*g_pfnPb8050)();
extern void*     g_pPbDefaultStr;
extern int32_t (*g_pfnPbVarintSize)(uint32_t);
extern void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*);
extern void (*g_pfnPbWriteString)(uint32_t, void*, void*);
extern void (*g_pfnPbWriteUnknown)(void*, void*, int32_t);
extern void (*g_pfnPb64C0)(void*, void*);
extern void (*g_pfnPb4550)(void*, void*);
extern uint64_t (*g_pfnPb3BC0)(void*);
extern uint64_t (*g_pfnPb3A50)(void*, uint32_t*);
extern void (*g_pfnPb45D0)(void*);
extern uint64_t (*g_pfnPb6510)(void*);
extern char (*g_pfnPbF3F50)(void*, uint32_t, void*);
extern uint64_t (*g_pfnPbF51E0)(void*, void*);
extern void (*g_pfnPbEDA90)(void*, void*);
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);

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
    // 0x1417ee450 — Merge
    static bool Merge(void* self, void* input);
    // 0x1417edd10 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417edca0 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417edda0 — MergeFrom (slot6 thunk 0x1417ee620)
    static void MergeFrom(void* self, void* from);
    // 0x1417ee0d0
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
