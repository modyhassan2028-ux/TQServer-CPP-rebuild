// ============================================================================
// CMsgLeagueTokenPB.h — RAW Syndicate.dll v6159
//   vtable 0x141842658 (the RTTI hit sits at +0x18)
//   slot 0 0x1417f1940 deleting dtor (body 0x1417f1710)
//   slot 1 0x1417f15a0 GetTypeName · slot 2 0x1417f1780 New (0x50 -> 0x1417f1600)
//   slot 3 0x1417f1220 Clear · slot 4 0x1417f1590 IsInitialized ((bits&0x1f)==0x1f)
//   slot 5 shared · slot 6 0x1417f1ca0 thunk -> 0x1417f1430
//   slot 7 0x1417f19a0 Merge · slot 8 0x1417f1330 ByteSize
//   slot 9 0x1417f1270 Serialize · slot 10 shared parse · slot 11 0x1417f1670 cached
#ifndef SYNDICATE_CMSGLEAGUETOKENPB_H
#define SYNDICATE_CMSGLEAGUETOKENPB_H
#include <cstdint>
#include <string>
namespace syndicate {

extern uint64_t (*g_pfnPb8050)();
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
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);
extern void* g_pPbDefaultStr;
extern void (*g_pfnPbF10A0)(void*, void*);   // string field 5 set

class CMsgLeagueTokenPB {
public:
    static constexpr uintptr_t kClassVft = 0x141842658;
    static constexpr const char* kTypeName = "CMsgLeagueTokenPB";

    static void BaseDtor(void* self);                                  // 0x1417f1710
    static void* DeleteDtor(void* self, uint32_t uFlag);               // 0x1417f1940
    static void* New();                                                // 0x1417f1780
    static std::string* GetTypeName(std::string* out);                 // 0x1417f15a0
    static void Clear(void* self);                                     // 0x1417f1220
    static bool IsInitialized(void* self);                             // 0x1417f1590
    static uint32_t GetCachedSize(void* self);                         // 0x1417f1670
    static int32_t ByteSize(void* self);                               // 0x1417f1330
    static void SerializeWithCachedSizes(void* self, void* pBuf);      // 0x1417f1270
    static bool Merge(void* self, void* input);                        // 0x1417f19a0
    static void MergeFrom(void* self, void* from);                     // 0x1417f1430
};

}  // namespace syndicate
#endif
