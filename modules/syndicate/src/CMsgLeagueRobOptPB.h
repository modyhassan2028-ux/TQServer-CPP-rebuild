// ============================================================================
// CMsgLeagueRobOptPB.h — RAW Syndicate.dll v6159
//   vtable 0x1418423d8
//   slot 0  0x1417f0ad0 deleting dtor (member body 0x1417f0660)
//   slot 1  0x1417efac0 GetTypeName "CMsgLeagueRobOptPB"
//   slot 2  0x1417f06f0 New (0x58, ctor inline)
//   slot 3  0x1417f0760 Clear
//   slot 4  0x1417f0950 IsInitialized
//   slot 5  0x1417de5c0 shared
//   slot 6  0x1417f1000 thunk -> 0x1417f0e60 MergeFrom
//   slot 7  0x1417f0b30 Merge
//   slot 8  0x1417f0890 ByteSize
//   slot 9  0x1417f07d0 SerializeWithCachedSizes
//   slot 10 0x1417dee40 shared parse
//   slot 11 0x1417f0650 GetCachedSize
#ifndef SYNDICATE_CMSGLEAGUEROBOPTPB_H
#define SYNDICATE_CMSGLEAGUEROBOPTPB_H
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
extern void (*g_pfnPbE0110)(void*, int32_t);
extern void (*g_pfnPbF4DC0)(uint32_t, void*, void*);
extern void (*g_pfnPbCheckFail)(const char*, int, const char*);
extern void (*g_pfnPbDelArray)(void*);
// D100 seams
extern void*    g_pPbDefaultStr;
extern uint32_t g_uRobOptServerVft;             // CMsgLeagueRobOptServerPB
extern uint32_t g_uPbInitFlag2;                 // DAT_141886ea8
extern void (*g_pfnPbInitGuard)(void*);         // 1417e7c70 path
extern int32_t (*g_pfnPbEF830)(void*);          // sibling ByteSize
extern char (*g_pfnPbF0330)(void*, void*);      // sibling merge
extern void (*g_pfnPbF0450)(void*, void*);      // vector merge

class CMsgLeagueRobOptPB {
public:
    static constexpr uintptr_t kClassVft = 0x1418423d8;
    static constexpr const char* kTypeName = "CMsgLeagueRobOptPB";

    static void BaseDtor(void* self, uint64_t a2, uint64_t a3, uint64_t a4); // 0x1417f0660
    static void* DeleteDtor(void* self, uint64_t uFlag);                     // 0x1417f0ad0
    static void* New();                                                      // 0x1417f06f0
    static std::string* GetTypeName(std::string* out);                       // 0x1417efac0
    static void Clear(void* self);                                           // 0x1417f0760
    static bool IsInitialized(void* self);                                   // 0x1417f0950
    static uint32_t GetCachedSize(void* self);                               // 0x1417f0650
    static int32_t ByteSize(void* self);                                     // 0x1417f0890
    static void SerializeWithCachedSizes(void* self, void* pBuf);            // 0x1417f07d0
    static bool Merge(void* self, void* input);                               // 0x1417f0b30
    static void MergeFrom(void* self, void* from);                            // 0x1417f0e60
};

}  // namespace syndicate
#endif
