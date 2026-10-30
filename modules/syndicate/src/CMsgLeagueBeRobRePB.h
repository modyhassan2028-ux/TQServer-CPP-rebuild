// ============================================================================
// CMsgLeagueBeRobRePB.h — RAW Syndicate.dll v6159
//   vtable 0x141841118 (the 12-slot table; the RTTI hit sits at +0x18)
//   slot 0  0x1417e8e40 deleting dtor · slot 1 0x1417e8630 GetTypeName
//   slot 2  0x1417e8ab0 New (0x40) · slot 3 0x1417e8460 Clear
//   slot 4  0x1417e8620 IsInitialized ((bits&1)==1)
//   slot 5  0x1417de5c0 shared · slot 6 0x1417e8ff0 thunk -> 0x1417e8520
//   slot 7  0x1417e8ea0 Merge · slot 8 0x1417e84d0 ByteSize
//   slot 9  0x1417e8480 Serialize · slot 10 0x1417dee40 shared parse
//   slot 11 0x1417e89f0 GetCachedSize
#ifndef SYNDICATE_CMSGLEAGUEBEROBREPB_H
#define SYNDICATE_CMSGLEAGUEBEROBREPB_H
#include <cstdint>
#include <string>
namespace syndicate {

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
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);

class CMsgLeagueBeRobRePB {
public:
    static constexpr uintptr_t kClassVft = 0x141841118;
    static constexpr const char* kTypeName = "CMsgLeagueBeRobRePB";

    static void* DeleteDtor(void* self, uint32_t uFlag);              // 0x1417e8e40
    static std::string* GetTypeName(std::string* out);                // 0x1417e8630
    static void* New();                                               // 0x1417e8ab0
    static void Clear(void* self);                                    // 0x1417e8460
    static bool IsInitialized(void* self);                            // 0x1417e8620
    static void MergeFrom(void* self, void* from);                    // 0x1417e8520
    static bool Merge(void* self, void* input);                       // 0x1417e8ea0
    static uint32_t ByteSize(void* self);                             // 0x1417e84d0
    static void SerializeWithCachedSizes(void* self, void* pBuf);     // 0x1417e8480
    static uint32_t GetCachedSize(void* self);                        // 0x1417e89f0
};

}  // namespace syndicate
#endif
