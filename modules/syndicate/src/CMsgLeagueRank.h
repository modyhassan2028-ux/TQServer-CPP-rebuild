// ============================================================================
// CMsgLeagueRank.h — syndicate message wrapper
// RAW: Syndicate.dll v6159
//   vtable 0x14183c998, 5 slots
//   slot 0  0x1417d7ce0   destructor
//   slot 1  0x1417d7b30   Create
//   slots 2-4 14177e2f0 / 14177e2e0 / 14177e2d0  the shared tq::CMsg error loggers
// The destructor writes the class vtable, then the base 0x14182e368, and only
// then deletes when flag bit 0 is set (verified at 0x1417d7ce0).
// Create calls the base 1417e7fda and then requires the message id at [this+0xa]
// to equal 0x0a43 (verified at 0x1417d7b30: mov eax,0x0a43 / cmp ax,[rbx+0xa]).
#ifndef SYNDICATE_CMSGLEAGUERANK_H
#define SYNDICATE_CMSGLEAGUERANK_H
#include <cstdint>

namespace syndicate {

// seams — the shared base create, the deallocator and the error log
extern bool (*g_pfnCMsgLeagueRankBaseCreate)(void* self, const char* buf, uint16_t len);   // 1417e7fda
extern void (*g_pfnCMsgLeagueRankDelete)(void* p);                                         // 1417f2fdc
extern void (*g_pfnCMsgLeagueRankLogError)(const char* text);                              // log_InlineLogERROR

class CMsgLeagueRank {
public:
    static constexpr uint16_t kMsgId    = 0x0a43;
    static constexpr uintptr_t kClassVft = 0x14183c998;
    static constexpr uintptr_t kBaseVft  = 0x14182e368;

    // 0x1417d7ce0
    void Destruct(unsigned char flag);
    // 0x1417d7b30
    static bool Create(void* self, const char* buf, uint16_t len);

    // slots 2-4, byte-identical for every message wrapper in this family
    static void ProcessActorInfoError();   // 14177e2f0
    static void ProcessActorError();       // 14177e2e0
    static void ProcessInfoError();        // 14177e2d0
};

} // namespace syndicate
#endif
