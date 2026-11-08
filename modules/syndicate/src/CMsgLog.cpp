#include "modules/syndicate/src/CMsgLog.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"   // Slot_1417b6210_singleton

namespace tq {

void (*g_pfnLogic_1417b7010)(void* pObj, uint32_t nIdActor) = nullptr;
void (*g_pfnLogic_1417ac620)(void* pObj, uint32_t nIdActor) = nullptr;
void (*g_pfn_log_1417d97c0)(const char* pFmt, uint32_t nIdActor, uint32_t nType,
                            uint32_t nMsgType) = nullptr;

#define CL_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define CL_D(p, off) (*(uint32_t*)((uint8_t*)(p) + (off)))
#define CL_W(p, off) (*(uint16_t*)((uint8_t*)(p) + (off)))

// ============================================================================
// 0x1417d97c0 — syndicate::CMsgLog::Process(idActor). The 0x28-byte frame holds a
// $0xfffffffffffffffe tag at 0x30(%rsp) that no later instruction reads; it is a leftover of the
// inlined caller-side machinery, and the port keeps the store visible rather than dropping it.
//   1417d97e1  call 0x1417b6210      the singleton; rcx is still this and the body ignores it
//   1417d97e6  mov 0x408(%rdi),%r8   this->0x408 is the configuration object
//   1417d97ed  mov 0x8(%r8),%r8d     its Type field decides the branch, signed-free 32-bit
//   1417d97fb  Type 0 -> 0x1417b7010(pObj, idActor)
//   1417d980d  Type 1 -> 0x1417ac620(pObj, idActor)
//   1417d9814  anything else: log(format, idActor, Type, this->0xa as a 16-bit load)
void Slot_1417d97c0_Process(void* pThis, uint32_t nIdActor) {
    volatile uint64_t uTag = 0xfffffffffffffffeULL;                       // 1417d97ce, never read
    (void)uTag;
    void* pObj = Slot_1417b6210_singleton();                              // 1417d97e1
    void* pCfg = CL_Q(pThis, 0x408);                                      // 1417d97e6
    const uint32_t nType = CL_D(pCfg, 0x8);                               // 1417d97ed
    if (nType == 0) {                                                     // 1417d97f1 test/jne
        if (g_pfnLogic_1417b7010 != nullptr)
            g_pfnLogic_1417b7010(pObj, nIdActor);                         // 1417d97fb
        return;                                                           // 1417d9800 jmp epilogue
    }
    if (nType == 1) {                                                     // 1417d9802 cmp/jne
        if (g_pfnLogic_1417ac620 != nullptr)
            g_pfnLogic_1417ac620(pObj, nIdActor);                         // 1417d980d
        return;
    }
    const uint32_t nMsgType = (uint32_t)CL_W(pThis, 0xa);                 // 1417d9814 movzwl 0xa(%rdi)
    if (g_pfn_log_1417d97c0 != nullptr)                                   // 1417d9822
        g_pfn_log_1417d97c0(
            "syndicate::CMsgLog::Process(idActor), idActor:%d, Type:%d, MsgType:%d",
            nIdActor, nType, nMsgType);                                   // rdx, r8d, r9d
}

// ============================================================================
// 0x1417d9840..0x1417d98f7 — twelve leaf setters, each three or four instructions. The bit word at
// +0x30 accumulates which fields a message carries, and the value store follows the bit.
void Slot_1417d9840_or1(void* pThis) { CL_D(pThis, 0x30) |= 0x1u; }
void Slot_1417d9850_or1_u32_38(void* pThis, uint32_t v) { CL_D(pThis, 0x30) |= 0x1u; CL_D(pThis, 0x38) = v; }
void Slot_1417d9860_or2(void* pThis) { CL_D(pThis, 0x30) |= 0x2u; }
void Slot_1417d9870_or2_u32_3c(void* pThis, uint32_t v) { CL_D(pThis, 0x30) |= 0x2u; CL_D(pThis, 0x3c) = v; }
void Slot_1417d9880_or4(void* pThis) { CL_D(pThis, 0x30) |= 0x4u; }
void Slot_1417d9890_or4_u32_40(void* pThis, uint32_t v) { CL_D(pThis, 0x30) |= 0x4u; CL_D(pThis, 0x40) = v; }
void Slot_1417d98a0_or8(void* pThis) { CL_D(pThis, 0x30) |= 0x8u; }
// 0x1417d98b4 and 0x1417d98d4 store only %dl: the field is a byte, not a dword.
void Slot_1417d98b0_or8_u8_44(void* pThis, uint32_t v) {
    CL_D(pThis, 0x30) |= 0x8u;
    *(uint8_t*)((uint8_t*)pThis + 0x44) = (uint8_t)(v & 0xFFu);
}
void Slot_1417d98c0_or10(void* pThis) { CL_D(pThis, 0x30) |= 0x10u; }
void Slot_1417d98d0_or10_u8_45(void* pThis, uint32_t v) {
    CL_D(pThis, 0x30) |= 0x10u;
    *(uint8_t*)((uint8_t*)pThis + 0x45) = (uint8_t)(v & 0xFFu);
}
void Slot_1417d98e0_or20(void* pThis) { CL_D(pThis, 0x30) |= 0x20u; }
void Slot_1417d98f0_or20_u32_60(void* pThis, uint32_t v) { CL_D(pThis, 0x30) |= 0x20u; CL_D(pThis, 0x60) = v; }

}  // namespace tq
