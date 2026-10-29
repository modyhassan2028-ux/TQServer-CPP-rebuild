// ============================================================================
// CMsgLeagueBeRobPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x141841318 (resolved from RTTI .?AVCMsgLeagueBeRobPB@@)
//   slot 0  0x1417e99c0  deleting dtor (member body 0x1417e9440)
//   slot 1  0x1417e8710  GetTypeName "CMsgLeagueBeRobPB"
//   slot 2  0x1417e94f0  New (allocates 0x68, ctor 0x1417e93b0)
//   slot 3  0x1417e9530  Clear
//   slot 4  0x1417e9810  IsInitialized
//   slot 5  0x1417de5c0  shared lite GetTypeName fallback
//   slot 6  0x1417e9fb0  thunk -> MergeFrom
//   slot 7  0x1417e9a20  Merge
//   slot 8  0x1417e96b0  ByteSize
//   slot 9  0x1417e95c0  SerializeWithCachedSizes
//   slot 10 0x1417dee40  shared parse helper
//   slot 11 0x1417e9430  GetCachedSize (+0x34)
#ifndef SYNDICATE_CMSGLEAGUEBEROBPB_H
#define SYNDICATE_CMSGLEAGUEBEROBPB_H
#include <cstdint>
#include <string>
namespace syndicate {

extern void     (*g_pfnPbFree)(void*);
extern uint64_t (*g_pfnPb8050)();
extern void*     g_pPbDefaultStr;
extern void     (*g_pfnPbDelArray)(void*);      // operator_delete__
// shared kit
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
extern void (*g_pfnPbE0110)(void*, int32_t);
extern void (*g_pfnPbF4DC0)(uint32_t, void*, void*);
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);
// D99 additions
extern uint32_t g_uBeRobReVft;                 // CMsgLeagueBeRobRePB::vftable
extern char (*g_pfnPbE90E0)(void*, void*);      // element merge
extern void (*g_pfnPbE9200)(void*, void*);      // vector merge
extern void (*g_pfnPbE81E0)(void*, void*);      // string set

class CMsgLeagueBeRobPB {
public:
    static constexpr uintptr_t kClassVft = 0x141841318;
    static constexpr const char* kTypeName = "CMsgLeagueBeRobPB";

    // 0x1417e9440 — the class dtor body
    static void BaseDtor(void* self, uint64_t a2, uint64_t a3, uint64_t a4);
    // 0x1417e99c0 — deleting dtor
    static void* DeleteDtor(void* self, uint64_t uFlag);
    // 0x1417e93b0 — the in-place ctor
    static void* Ctor(void* self);
    // 0x1417e94f0 — New
    static void* New();
    // 0x1417e8710 — the type name
    static std::string* GetTypeName(std::string* out);
    // 0x1417e9530 — Clear
    static void Clear(void* self);
    // 0x1417e9810 — IsInitialized
    static bool IsInitialized(void* self);
    // 0x1417e96b0 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417e95c0 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417e9a20 — Merge
    static bool Merge(void* self, void* input);
    // 0x1417e9dc0 — MergeFrom (slot6 thunk 0x1417e9fb0)
    static void MergeFrom(void* self, void* from);
    // 0x1417e9430 — GetCachedSize
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
