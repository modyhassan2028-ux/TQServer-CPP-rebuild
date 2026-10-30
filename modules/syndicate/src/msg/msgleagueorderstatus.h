// ============================================================================
// CMsgLeagueOrderStatus.h — syndicate message wrapper
// RAW: Syndicate.dll v6159
//   vtable 0x14183c708, 5 slots
//   slot 0  0x1417d7550   destructor
//   slot 1  1417e7fda   the shared tq::CMsg base Create
//   slots 2-4 14177e2f0 / 14177e2e0 / 14177e2d0  the shared tq::CMsg error loggers
// The destructor writes the class vtable, runs the member PB destructor at
// byte offset 0x408 (1417ed1a0), writes the base tq::CMsg vftable, and only then
// deletes when flag bit 0 is set (verified at 0x1417d7550).
#ifndef SYNDICATE_CMSGLEAGUEORDERSTATUS_H
#define SYNDICATE_CMSGLEAGUEORDERSTATUS_H
#include <cstdint>

namespace syndicate {

// seams — the shared base create, the deallocator, the error log and
// the member PB destructor
extern bool (*g_pfnCMsgLeagueOrderStatusBaseCreate)(void* self, const char* buf, uint16_t len);   // 1417e7fda
extern void (*g_pfnCMsgLeagueOrderStatusDelete)(void* p);                                     // 1417f2fdc
extern void (*g_pfnCMsgLeagueOrderStatusLogError)(const char* text);                            // log_InlineLogERROR
extern void (*g_pfnCMsgLeagueOrderStatusMemDtor)(void* self, uint64_t flags,
                       uint64_t a3, uint64_t a4);                    // 1417ed1a0

class CMsgLeagueOrderStatus {
public:
    static constexpr uintptr_t kClassVft = 0x14183c708;
    static constexpr uintptr_t kBaseVft  = 0x14182e368;
    static constexpr uintptr_t kMemberOff = 0x408;

    // 0x1417d7550
    void* Destruct(uint64_t flags, uint64_t a3, uint64_t a4);

    // slot 1: the base create, verbatim
    static bool Create(void* self, const char* buf, uint16_t len);

    // slots 2-4, byte-identical for every message wrapper in this family
    static void ProcessActorInfoError();   // 14177e2f0
    static void ProcessActorError();       // 14177e2e0
    static void ProcessInfoError();        // 14177e2d0
};

} // namespace syndicate
#endif
