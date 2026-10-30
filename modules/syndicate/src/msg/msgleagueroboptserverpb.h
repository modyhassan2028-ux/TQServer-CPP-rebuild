// ============================================================================
// CMsgLeagueRobOptServerPB.h — RAW Syndicate.dll v6159
//   vtable 0x141842278
//   slot 0  0x1417effe0 deleting dtor (member body 0x1417efce0)
//   slot 1  0x1417efa30 GetTypeName "CMsgLeagueRobOptServerPB"
//   slot 2  0x1417efd70 New (0x50, ctor 0x1417efbd0)
//   slot 3  0x1417ef730 Clear
//   slot 4  0x1417efa20 IsInitialized ((bits&1)==1)
//   slot 5  0x1417de5c0 shared
//   slot 6  0x1417f0260 thunk -> 0x1417ef8f0 MergeFrom
//   slot 7  0x1417f0010 Merge
//   slot 8  0x1417ef830 ByteSize
//   slot 9  0x1417ef7a0 SerializeWithCachedSizes
//   slot 10 0x1417dee40 shared parse
//   slot 11 0x1417efc40 GetCachedSize
#ifndef SYNDICATE_CMSGLEAGUEROBOPTSERVERPB_H
#define SYNDICATE_CMSGLEAGUEROBOPTSERVERPB_H
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
extern void*    g_pPbDefaultStr;
extern void (*g_pfnPbEF430)(void*, void*);   // string field 2 set
extern void (*g_pfnPbEF520)(void*, void*);   // string field 3 set

class CMsgLeagueRobOptServerPB {
public:
    static constexpr uintptr_t kClassVft = 0x141842278;
    static constexpr const char* kTypeName = "CMsgLeagueRobOptServerPB";

    static void BaseDtor(void* self);                                 // 0x1417efce0
    static void* DeleteDtor(void* self, uint32_t uFlag);              // 0x1417effe0
    static void* Ctor(void* self);                                    // 0x1417efbd0
    static void* New();                                               // 0x1417efd70
    static std::string* GetTypeName(std::string* out);                // 0x1417efa30
    static void Clear(void* self);                                    // 0x1417ef730
    static bool IsInitialized(void* self);                            // 0x1417efa20
    static uint32_t GetCachedSize(void* self);                        // 0x1417efc40
    static int32_t ByteSize(void* self);                              // 0x1417ef830
    static void SerializeWithCachedSizes(void* self, void* pBuf);     // 0x1417ef7a0
    static bool Merge(void* self, void* input);                       // 0x1417f0010
    static void MergeFrom(void* self, void* from);                     // 0x1417ef8f0
};

}  // namespace syndicate
#endif
