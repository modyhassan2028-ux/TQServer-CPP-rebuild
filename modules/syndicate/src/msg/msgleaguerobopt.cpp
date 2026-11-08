#include <cstring>
#include "modules/syndicate/src/msg/msgleaguerobopt.h"
#include "modules/syndicate/src/msg/msgleagueopt.h"          // g_pfnL_1417ac700
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"  // Slot_1417b6210_singleton

namespace tq {

static inline uint32_t RB_D(const void* p, uint32_t off) {
    uint32_t v; std::memcpy(&v, (const uint8_t*)p + off, sizeof v); return v;
}
static inline void* RB_Q(const void* p, uint32_t off) {
    void* v; std::memcpy(&v, (const uint8_t*)p + off, sizeof v); return v;
}

// The three vtable shapes this body calls. 0x680 and 0x6e0 take six arguments (the last two on the
// stack), while 0x730 takes five: case 2/3 never writes the 0x28 home slot, so its sixth is not an
// argument the original passes on purpose.
typedef void (*Vt6)(void*, uint32_t, uint32_t, void*, uint32_t, uint32_t);
typedef void (*Vt5)(void*, uint32_t, uint32_t, uint32_t, uint32_t);

// ============================================================================
// 0x1417d8920. The early exit for id 0 is a `test %edx,%edx / je 0x1417d8c00` that lands on the
// `repz ret` past the frame teardown, so it returns before the frame exists.
//
//   1417d8963  jb  epilogue            mode < 2 never dispatches on the known path
//   1417d896c  jbe dispatch            mode 2..3 dispatches
//   1417d8971  add $0xfffffffb         mode-5 must be 0 or 1, i.e. mode 5..6
//   1417d8984  cmp $0x6 / ja           the second, unconditional bound
void Slot_1417d8920_Process(void* pThis, uint32_t nId) {
    if (nId == 0) return;                                    // 1417d8920
    void* pObj = Slot_1417b6210_singleton();                  // 1417d8947
    const bool bKnown = (g_pfnL_1417ac700 != nullptr)         // 1417d8954
                            ? g_pfnL_1417ac700(pObj, nId) : false;
    if (bKnown) {
        const uint32_t nFirst = RB_D(pThis, 0x440);           // 1417d895d
        if (nFirst < 2) return;                               // 1417d8963 jb
        if (nFirst > 3 && (uint32_t)(nFirst - 5) > 1) return;  // 1417d896c / 1417d8971
    }
    const uint32_t nMode = RB_D(pThis, 0x440);                // 1417d897d, reloaded
    if (nMode > 6) return;                                    // 1417d8984
    const int32_t nCount = (int32_t)RB_D(pThis, 0x450);       // 1417d89a2 movslq, signed
    const uint32_t nCfg444 = RB_D(pThis, 0x444);
    uint32_t anIds[10];

    // The loop every list case runs: ten slots zeroed, then each element's +0x48 copied in, stopping
    // at ten even when the count is larger. The callee is still handed the *raw* count.
    auto build = [&]() {
        for (int i = 0; i < 10; ++i) anIds[i] = 0;
        if (nCount <= 0) return;
        void** ppList = (void**)RB_Q(pThis, 0x448);
        int64_t n = 0;
        uint32_t nUsed = 0;
        for (;;) {
            if (nUsed >= 0xAu) break;                          // 1417d89e0 cmp $0xa,%r8d; jae
            ++n;                                               // 1417d89ed inc %rdx
            ++nUsed;                                           // 1417d89f0 inc %r8d
            void* pElem = ppList[n - 1];                       // 1417d89f6 mov -0x8(%rax,%rdx,8)
            anIds[n - 1] = RB_D(pElem, 0x48);                  // 1417d89fb
            if (!(n < (int64_t)nCount)) break;                 // 1417d89f3 cmp/jl
        }
    };

    switch (nMode) {
    case 0: {                                                 // 1417d89a2
        build();
        Vt6 f = (Vt6)*(void**)(*(uint8_t**)pObj + 0x680);
        f(pObj, nId, (uint32_t)nCount, anIds, 0, 0);           // [0x20]=bl(0), [0x28]=ebx(0)
        break;
    }
    case 1: {                                                 // 1417d8a27
        build();
        Vt6 f = (Vt6)*(void**)(*(uint8_t**)pObj + 0x680);
        f(pObj, nId, (uint32_t)nCount, anIds, 1, nCfg444);     // [0x20]=1, [0x28]=this+0x444
        break;
    }
    case 2:
    case 3: {                                                 // 1417d8bba, shared by two modes
        // mul 0x10624dd3 then shr 6 of the high half: an unsigned divide by 1000.
        const uint32_t nQuot = (uint32_t)(((uint64_t)nCfg444 * 0x10624DD3ULL) >> 38);
        const uint32_t nRem = nCfg444 - nQuot * 1000u;
        Vt5 f = (Vt5)*(void**)(*(uint8_t**)pObj + 0x730);
        f(pObj, nId, nMode, nRem, nQuot);  // r8d is the untouched switch value, [0x20]=quotient
        break;
    }
    case 4:                                                   // 1417d8bea: straight to the epilogue
        break;
    case 5: {                                                 // 1417d8aad
        build();
        Vt6 f = (Vt6)*(void**)(*(uint8_t**)pObj + 0x6e0);
        f(pObj, nId, (uint32_t)nCount, anIds, 0, 0);
        break;
    }
    case 6: {                                                 // 1417d8b37
        build();
        Vt6 f = (Vt6)*(void**)(*(uint8_t**)pObj + 0x6e0);
        f(pObj, nId, (uint32_t)nCount, anIds, 1, nCfg444);
        break;
    }
    default:
        break;
    }
}

}  // namespace tq
