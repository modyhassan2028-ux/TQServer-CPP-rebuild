#include <cstring>
#include "modules/syndicate/src/slotforwarders.h"

namespace tq {

static inline void* FQ(const void* p, uint32_t off) {
    void* v; std::memcpy(&v, (const uint8_t*)p + off, sizeof v); return v;
}

// The three thunks share one shape; `mov 0x8(%rcx),%rcx` hops to the sub-object, `mov (%rcx),%rax`
// takes its table, and the tail `jmp` is the call. Because it is a jump and not a call, the callee
// returns straight to the original caller with whatever it left in %rax/%xmm0 — which is why the port
// uses uintptr_t and lets the seam's own signature decide the real type.
static inline uintptr_t forward(void* pObj, uint32_t nId, uint32_t nSlot) {
    void* pSub = FQ(pObj, 0x8);                                     // 1417ac700 mov 0x8(%rcx),%rcx
    void* pVt = FQ(pSub, 0x0);                                      // 1417ac704 mov (%rcx),%rax
    typedef uintptr_t (*Fn)(void*, uint32_t);
    Fn f = (Fn)FQ(pVt, nSlot);                                      // 1417ac707 jmp *0x278(%rax)
    return f(pSub, nId);
}

uintptr_t Slot_1417ac700_Forward(void* pObj, uint32_t nId) {        // 0x1417ac700
    return forward(pObj, nId, 0x278);
}
uintptr_t Slot_1417ac710_Forward(void* pObj, uint32_t nId) {        // 0x1417ac710
    return forward(pObj, nId, 0x2D8);
}
uintptr_t Slot_1417ac720_Forward(void* pObj, uint32_t nId) {        // 0x1417ac720
    return forward(pObj, nId, 0x2C8);
}

// 0x1417ac730 has its own frame because it must survive the call: `sub $0x28,%rsp`, the same two
// hops, `call *0x1f8(%rax)`, then `test %eax,%eax / sete %al`. The second argument is never written,
// so the callee sees the caller's %edx; it is forwarded for that reason and not because it is used.
bool Slot_1417ac730_IsZero(void* pObj, uint32_t nId) {
    void* pSub = FQ(pObj, 0x8);                                     // 1417ac734
    void* pVt = FQ(pSub, 0x0);                                      // 1417ac738
    typedef uint32_t (*Fn)(void*, uint32_t);
    Fn f = (Fn)FQ(pVt, 0x1F8);                                      // 1417ac73b call *0x1f8(%rax)
    return f(pSub, nId) == 0;                                       // 1417ac741 test / sete %al
}

// ---------------------------------------------------------------------------------------------
void (*g_pfnL_1417a7d70)(void*) = nullptr;
void (*g_pfnL_1417d4a10)(void*) = nullptr;
void (*g_pfnL_14176aa20)(void*) = nullptr;

// 0x1417ac5e0. Three identical shapes: load a field, skip the call when it is null, otherwise pass it
// in %rcx. The fields are +0x20, +0x48 and +0x50, and the calls return normally (no tail jump).
void Slot_1417ac5e0_ReleaseRefs(void* pThis) {
    void* p = FQ(pThis, 0x20);                                      // 1417ac5e9
    if (p != nullptr && g_pfnL_1417a7d70 != nullptr) g_pfnL_1417a7d70(p);
    p = FQ(pThis, 0x48);                                            // 1417ac5f7
    if (p != nullptr && g_pfnL_1417d4a10 != nullptr) g_pfnL_1417d4a10(p);
    p = FQ(pThis, 0x50);                                            // 1417ac605
    if (p != nullptr && g_pfnL_14176aa20 != nullptr) g_pfnL_14176aa20(p);
}

}  // namespace tq
