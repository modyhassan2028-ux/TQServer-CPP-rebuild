// CMsgLog.h — 0x1417d97c0 (syndicate::CMsgLog::Process, vtable slot +0x150 of the table at
// 0x14182e368) and the twelve flag/field setters that follow it in the image.
#pragma once
#include <cstdint>

namespace tq {

// The packet sink the Process body hands its actor id to, and the fallback logger. Both are seams:
// 0x1417b7010 and 0x1417ac620 have no transcribed body yet, and the log is the CQBase import at
// IAT 0x141823030, called here with (format, idActor, type, msgType).
extern void (*g_pfnLogic_1417b7010)(void* pObj, uint32_t nIdActor);
extern void (*g_pfnLogic_1417ac620)(void* pObj, uint32_t nIdActor);
extern void (*g_pfn_log_1417d97c0)(const char* pFmt, uint32_t nIdActor, uint32_t nType,
                                   uint32_t nMsgType);
void Slot_1417d97c0_Process(void* pThis, uint32_t nIdActor);

// The setters. Bits live in the 32-bit word at +0x30; each pair is "raise the bit" and "raise the
// bit and store the argument", and the stored widths differ (a byte at +0x44 and +0x45, a dword
// everywhere else), so the widths are part of the parity.
void Slot_1417d9840_or1(void* pThis);                        // orl $0x1,0x30(%rcx)
void Slot_1417d9850_or1_u32_38(void* pThis, uint32_t v);     // orl $0x1 + mov %edx,0x38(%rcx)
void Slot_1417d9860_or2(void* pThis);                        // orl $0x2,0x30(%rcx)
void Slot_1417d9870_or2_u32_3c(void* pThis, uint32_t v);     // orl $0x2 + mov %edx,0x3c(%rcx)
void Slot_1417d9880_or4(void* pThis);                        // orl $0x4,0x30(%rcx)
void Slot_1417d9890_or4_u32_40(void* pThis, uint32_t v);     // orl $0x4 + mov %edx,0x40(%rcx)
void Slot_1417d98a0_or8(void* pThis);                        // orl $0x8,0x30(%rcx)
void Slot_1417d98b0_or8_u8_44(void* pThis, uint32_t v);      // orl $0x8 + mov %dl,0x44(%rcx)
void Slot_1417d98c0_or10(void* pThis);                       // orl $0x10,0x30(%rcx)
void Slot_1417d98d0_or10_u8_45(void* pThis, uint32_t v);     // orl $0x10 + mov %dl,0x45(%rcx)
void Slot_1417d98e0_or20(void* pThis);                       // orl $0x20,0x30(%rcx)
void Slot_1417d98f0_or20_u32_60(void* pThis, uint32_t v);    // orl $0x20 + mov %edx,0x60(%rcx)

// ---- the rest of the class, 0x1417dae90..0x1417db010 -------------------------------------------
// Four callees are still seams: 0x1417e8016 is the envelope each builder calls first, 0x1417e7fda
// is the one 0x1417dafe0 gates on, 0x1417afb20 is the predicate 0x1417daee0 asks, and 0x1417ac7d0
// is the report it ends with. None has a transcribed body yet.
extern void (*g_pfnLogic_1417e8016)(void* pThis);
extern bool (*g_pfnLogic_1417e7fda)(void* pThis);
extern bool (*g_pfnLogic_1417afb20)(void* pObj, uint32_t nId, uint32_t nCfg4, void* pCfg8);
extern void (*g_pfnLogic_1417ac7d0)(void* pObj, uint32_t nId, void* pThis);

// 0x1417dae90 — writes 0x1c to cfg+0x0, 0x837 to cfg+0x2 and the arg to cfg+0x18. The bytes leave
// rax holding the last cfg pointer and only overwrite %al with 1, so the return is that mix.
uint64_t Slot_1417dae90_SetDom(void* pThis, uint32_t nDom);
// 0x1417daee0 — the ChgDomName entry: predicate, then the two calls above with this as the 3rd arg.
void Slot_1417daee0_ChgDomName(void* pThis, uint32_t nId);
// 0x1417dafe0 — envelope gate, then "is the u16 at +0xa equal to 0x426". %al is rewritten but the
// rest of %eax keeps 0x426, so the value is 0x401/0x400 rather than a clean 1/0.
uint64_t Slot_1417dafe0_IsMsg426(void* pThis);
// 0x1417daf60 / 0x1417dafb0 — constructor and destructor. Both store the CMsg table at +0x0 first
// and the CMsgLog table last, so the destructor's second store is the one that survives; the
// constructor then points +0x408 at its own +0x8.
void* Slot_1417daf60_ctor(void* pThis);
void  Slot_1417dafb0_dtor(void* pThis);
// 0x1417db010 — the 0x48/0x426 builder: cfg gets 0x48, 0x426, the u16 arg, a zero Type and the id.
uint64_t Slot_1417db010_Build48(void* pThis, uint32_t nId, uint32_t nArg3);

}  // namespace tq
