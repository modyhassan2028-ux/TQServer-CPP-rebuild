// ============================================================================
// flowerservice.h — RAW Flower.dll v6159
//   original path: modules/flower/src/flowerservice.cpp
//   flower::CFlowerService — vftable 0x140d9be08, 5 slots
//     slot 0  0x140d93630  deleting dtor (Complete 0x140d932f0, then delete)
//     slot 1  0x140d93360  release: vfunc0(this, 1) when this != 0
//     slot 2  0x140d93380  "initialize": kernel slot +0x30 (mode 9), owned
//                          object at +0x420, then 0x140d91490
//     slot 3  0x140d934e0  owned object's slot 0, no arguments
//     slot 4  0x140d93660  dispatch by the packed u16 at record+2
//   helpers: Lookup 0x140d93460 · Attach 0x140d91490
// ============================================================================
#ifndef FLOWER_FLOWERSERVICE_H
#define FLOWER_FLOWERSERVICE_H
#include <cstdint>
#include "modules/flower/src/module.h"

namespace flower {

// log_InlineLogERROR with the CHECKF blob (0x140d9b368)
extern void (*g_pfnFlowerLog)(const char* fmt, ...);
extern const char kCheckFormat[];
inline void CTodayFlowerMgr_LogCheck() { g_pfnFlowerLog(kCheckFormat); }

// theInstance() -> the string manager; its slot 0 answers a literal by key
extern void* (*g_pfnTheInstance)();
const char* StrGet(const char* szKey);

// FUN_140d97bc0 () -> the object attached at +0x18
extern void* (*g_pfnFlowerCreateHelper)();
// FUN_140d94020 (pAttached, pSecond) -> bool
extern uint8_t (*g_pfnFlowerAttachInit)(void* pAttached, void* pSecond);
// 0x140d91a70 — gift slot/count resolve: (pThis, nArg, &slot, &count)
// defaults to CFlowerService::ResolveGiftSlot; tests may swap it out
extern uint32_t (*g_pfnResolveGift)(void* pThis, int nArg,
                                    uint32_t* pSlot, int* pCount);

class CFlowerService {
public:
    static constexpr uintptr_t kClassVft = 0x140d9be08;

    static void* DeleteDtorFull(void* self, uint64_t uFlag, void* pB, void* pC);
    static uint8_t Release(void* self);               // 0x140d93360
    static uint8_t Initialize(void* self);            // 0x140d93380
    static void ReleaseOwned(void* self);             // 0x140d934e0
    static uint16_t Process(void* self, uint32_t dwArg, uint16_t* pRecord,
                            uint16_t uCount);         // 0x140d93660
    static void* Lookup(void* self, uint16_t* pRecord,
                        uint16_t uCount);             // 0x140d93460
    static uint8_t Attach(void* pOwned, void* pSecond);  // 0x140d91490

    // 0x140d91be0 — the flower gift itself
    //   this+0x08 session · this+0x18 todayflower map
    //   idSender 0 or idReceiver 0 -> CHECKF
    //   session mode != 1 -> nothing happens
    //   nArg == 0 is the self path (level gate, one-per-day gate, count 1,
    //   slot 0); otherwise the resolve at 0x140d91980 supplies slot and count
    static uint8_t Send(void* pThis, uint32_t idSender, uint32_t idReceiver,
                        int nArg);

    // 0x140d91a70 — packed raw -> gift slot (4..7) and count
    //   raw / 1000 selects the band: 0x2f3..0x2f6 -> slots 4..7,
    //   count = raw - 755000 / 756000 / 757000 / 758000
    static uint32_t ResolveGiftSlot(void* pThis, int nArg, uint32_t* pSlot,
                                    int* pCount);

    // 0x140d926c0 — the gift path (message type 2, male receiver)
    static uint8_t SendGift(void* pThis, uint32_t idSender, uint32_t idReceiver,
                            int nArg);
    static constexpr uint32_t kMinSendLevel = 50;    // 0x140da2008
    static constexpr uint32_t kGiftGm99 = 99;        // 0x140da2020
    static constexpr uint32_t kGiftGm999 = 999;      // 0x140da2024
    static constexpr uint32_t kGmCount99 = 99;       // 0x140da2018
    static constexpr uint32_t kGmCount999 = 999;     // 0x140da201c

    // 0x140d91050 — today as itymmdd
    static int TodayStamp();
    // 0x140d910c0 — true when the yyyymmdd stamp is already behind the clock
    static uint8_t IsExpiredDate(uint32_t dwDate);
    // 0x140d91980 — the session's +0xa0 value / 1000 selects flower slot 0..3
    // and the remainder becomes the count; returns the raw value
    static uint32_t ResolveFlowerSlot(void* pCtx, int nArg, uint32_t* pOutType,
                                      int* pOutCount);
};

}  // namespace flower
#endif
