#include "modules/syndicate/src/CMsgLog.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"   // Slot_1417b6210_singleton

namespace tq {

void (*g_pfnLogic_1417b7010)(void* pObj, uint32_t nIdActor) = nullptr;
void (*g_pfnLogic_1417ac620)(void* pObj, uint32_t nIdActor) = nullptr;
void (*g_pfn_log_1417d97c0)(const char* pFmt, uint32_t nIdActor, uint32_t nType,
                            uint32_t nMsgType) = nullptr;
void (*g_pfnLogic_1417e8016)(void* pThis) = nullptr;
bool (*g_pfnLogic_1417e7fda)(void* pThis) = nullptr;
bool (*g_pfnLogic_1417afb20)(void* pObj, uint32_t nId, uint32_t nCfg4, void* pCfg8) = nullptr;
void (*g_pfnLogic_1417ac7d0)(void* pObj, uint32_t nId, void* pThis) = nullptr;

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



// ============================================================================
// 0x1417dae90 — the domain-name builder. cfg+0x18 takes the argument, then the two halves of the
// message header: 0x837 at +0x2 and 0x1c at +0x0. The stores go through a fresh load of this+0x408
// each time, and only %al carries the 1, so rax leaves as "last cfg pointer with a 1 in the low byte".
uint64_t Slot_1417dae90_SetDom(void* pThis, uint32_t nDom) {
    const uint16_t wDom = (uint16_t)(nDom & 0xFFFFu);                 // 1417dae9a movzwl %dx,%ebx
    if (g_pfnLogic_1417e8016 != nullptr) g_pfnLogic_1417e8016(pThis); // 1417daea0
    void* pCfg = CL_Q(pThis, 0x408);                                  // 1417daea5
    CL_W(pCfg, 0x18) = wDom;                                          // 1417daeb1
    pCfg = CL_Q(pThis, 0x408);                                        // 1417daeb5
    CL_W(pCfg, 0x2) = 0x837;                                          // 1417daec1
    pCfg = CL_Q(pThis, 0x408);                                        // 1417daec5
    CL_W(pCfg, 0x0) = 0x1c;                                           // 1417daed1
    return ((uint64_t)(uintptr_t)pCfg & ~(uint64_t)0xFFULL) | 0x1ULL;  // 1417daed4 mov $0x1,%al
}

// ============================================================================
// 0x1417daee0 — ChgDomName. The predicate is asked with (pObj, id, cfg->4, &cfg->8): the fourth
// argument is the *address* of the Type field, not its value.
void Slot_1417daee0_ChgDomName(void* pThis, uint32_t nId) {
    volatile uint64_t uTag = 0xfffffffffffffffeULL;                   // 1417daef1, never read
    (void)uTag;
    void* pObj = Slot_1417b6210_singleton();                          // 1417daf04
    uint32_t nFlag = 0;                                               // 1417daf0c xor %esi,%esi
    void* pCfg = CL_Q(pThis, 0x408);                                  // 1417daf0e
    void* pTypeSlot = (uint8_t*)pCfg + 0x8;                           // 1417daf15 lea 0x8(%r8),%r9
    const uint32_t nCfg4 = CL_D(pCfg, 0x4);                            // 1417daf19
    if (g_pfnLogic_1417afb20 != nullptr &&                              // 1417daf22
        g_pfnLogic_1417afb20(pObj, nId, nCfg4, pTypeSlot))
        nFlag = 1;                                                    // 1417daf2b
    Slot_1417dae90_SetDom(pThis, nFlag & 0xFFFFu);                    // 1417daf30 movzwl %si,%edx
    if (g_pfnLogic_1417ac7d0 != nullptr)                              // 1417daf43
        g_pfnLogic_1417ac7d0(pObj, nId, pThis);                       // 3rd arg is this
}

// ============================================================================
// 0x1417dafe0 — the 0x426 test. First the envelope: a false answer returns immediately. Otherwise
// %eax still holds 0x426 while %al becomes the comparison, so the result is 0x401 or 0x400.
uint64_t Slot_1417dafe0_IsMsg426(void* pThis) {
    const bool bOk = (g_pfnLogic_1417e7fda != nullptr)                // 1417dafe9
                         ? g_pfnLogic_1417e7fda(pThis) : false;
    if (!bOk) return 0;                                               // 1417daff2, %al stays clear
    return (uint64_t)(0x426u & ~0xFFu) |                                // 1417daff8 mov $0x426,%eax
           (uint64_t)(CL_W(pThis, 0xa) == 0x426 ? 1 : 0);           // 1417daffd..db001 sete %al
}

// ============================================================================
// 0x1417daf60 — constructor. CMsg's table, the envelope call, CMsgLog's table, the envelope again,
// then +0x408 = this+8 (the configuration object lives inside the message).
void* Slot_1417daf60_ctor(void* pThis) {
    volatile uint64_t uTag = 0xfffffffffffffffeULL;                   // 1417daf6a, never read
    (void)uTag;
    CL_Q(pThis, 0x0) = (void*)(uintptr_t)0x14182e368ULL;              // 1417daf76 CMsg vftable
    if (g_pfnLogic_1417e8016 != nullptr) g_pfnLogic_1417e8016(pThis); // 1417daf80
    CL_Q(pThis, 0x0) = (void*)(uintptr_t)0x14183dad0ULL;              // 1417daf86 CMsgLog vftable
    if (g_pfnLogic_1417e8016 != nullptr) g_pfnLogic_1417e8016(pThis); // 1417daf93
    CL_Q(pThis, 0x408) = (uint8_t*)pThis + 0x8;                       // 1417daf9c
    return pThis;                                                     // 1417dafa3 mov %rbx,%rax
}

// 0x1417dafb0 — destructor. Two vtable stores and not a single call, so the CMsg table wins.
void Slot_1417dafb0_dtor(void* pThis) {
    CL_Q(pThis, 0x0) = (void*)(uintptr_t)0x14183dad0ULL;              // 1417dafc1
    CL_Q(pThis, 0x0) = (void*)(uintptr_t)0x14182e368ULL;              // 1417dafcb, this store survives
}

// ============================================================================
// 0x1417db010 — the 0x48/0x426 builder. Note the zero it writes into the Type field at cfg+0x8: this
// is what makes CMsgLog::Process take its first branch. Same "last cfg pointer with %al = 1" return.
uint64_t Slot_1417db010_Build48(void* pThis, uint32_t nId, uint32_t nArg3) {
    const uint16_t wArg3 = (uint16_t)(nArg3 & 0xFFFFu);               // 1417db01f movzwl %r8w,%ebx
    if (g_pfnLogic_1417e8016 != nullptr) g_pfnLogic_1417e8016(pThis); // 1417db028
    void* pCfg = CL_Q(pThis, 0x408);                                  // 1417db02d
    CL_W(pCfg, 0x0) = 0x48;                                           // 1417db039
    pCfg = CL_Q(pThis, 0x408);                                        // 1417db03c
    CL_W(pCfg, 0x2) = 0x426;                                          // 1417db048
    pCfg = CL_Q(pThis, 0x408);                                        // 1417db04c
    CL_W(pCfg, 0x4) = wArg3;                                          // 1417db053
    pCfg = CL_Q(pThis, 0x408);                                        // 1417db057
    CL_D(pCfg, 0x8) = 0;                                              // 1417db063 movl $0x0,0x8(%rax)
    pCfg = CL_Q(pThis, 0x408);                                        // 1417db06a
    CL_D(pCfg, 0xc) = nId;                                            // 1417db071
    return ((uint64_t)(uintptr_t)pCfg & ~(uint64_t)0xFFULL) | 0x1ULL;  // 1417db079 mov $0x1,%al
}

}  // namespace tq
