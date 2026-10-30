// ============================================================================
// CMsgOverheadLeagueInfoPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x141842828
//   slot 0  0x1417f2d90  the deleting destructor
//   slot 1  GetTypeName
//   slot 2  0x1417f2490  New (allocates 0x68)
//   slot 3  0x1417f24d0  Clear
//   slot 4  0x1417f1e40  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  thunk to 0x1417dd260
//   slots 7-9  MergePartialFromCodedStream / ByteSize / Serialize (pending)
//   slot 10 0x1417dee40 shared parse helper (seam)
//   slot 11 0x1417f23f0  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGOVERHEADLEAGUEINFOPB_H
#define SYNDICATE_CMSGOVERHEADLEAGUEINFOPB_H
#include <string>
#include <cstdint>
#include <string>
namespace syndicate {

// ---- seams ----
extern void     (*g_pfnPbFree)(void*);
extern uint64_t (*g_pfnPb8050)();
extern void*     g_pPbDefaultStr;
extern int32_t (*g_pfnPbVarintSize)(uint32_t);
extern void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*);
extern void (*g_pfnPbWriteByte)(uint32_t, char, void*);
extern void (*g_pfnPbWriteUnknown)(void*, void*, int32_t);
extern void (*g_pfnPb64C0)(void*, void*);
extern void (*g_pfnPb4550)(void*, void*);
extern uint64_t (*g_pfnPb3BC0)(void*);
extern uint64_t (*g_pfnPb3A50)(void*, uint32_t*);
extern void (*g_pfnPb45D0)(void*);
extern uint64_t (*g_pfnPb6510)(void*);
extern char (*g_pfnPbF3F50)(void*, uint32_t, void*);
extern void (*g_pfnPbE0110)(void*, int32_t);
extern void* (*g_pfnPbE02C0)();
extern char (*g_pfnPbEAA40)(void*, void*);
extern uint64_t (*g_pfnPbF51E0)(void*, void*);
extern void (*g_pfnPbF4B00)(uint32_t, void*, void*);
extern void (*g_pfnPbF20E0)(void*, void*);
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);

class CMsgOverheadLeagueInfoPB {
public:
    static constexpr uintptr_t kClassVft = 0x141842828;
    static constexpr const char* kTypeName = "CMsgOverheadLeagueInfoPB";

    // 0x1417f2d90
    static void* DeleteDtor(void* self, uint32_t uFlag);
    // 0x1417f2370
    static void* Ctor(void* self);
    // 0x1417f2490
    static void* New();
    // slot 1 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417f24d0
    static void Clear(void* self);
    // 0x1417f1e40
    static bool IsInitialized(void* self);
    // 0x1417f2550 — Merge
    static bool Merge(void* self, void* input);
    // 0x1417f2a50 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417f2930 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417f2b80 — MergeFrom (slot6 thunk 0x1417f2e90)
    static void MergeFrom(void* self, void* from);
    // 0x1417f23f0
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
