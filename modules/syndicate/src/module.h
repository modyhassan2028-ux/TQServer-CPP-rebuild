// module.h — 0x14177ec90. Its CHECKF names the file:
// f:\version\cqserver-78.0.11-1204\modules\syndicate\src\module.cpp
#pragma once
#include <cstdint>

namespace tq {

// CQBase.dll!log_InlineLogERROR, IAT 0x141823030. This site is the CHECKF macro, not CHECK: the
// second string is "CHECKF" and the third is the expression name.
extern void (*g_pfn_checkf_module)(const char* pFmt, const char* pMacro, const char* pExpr,
                                   const char* pFile, uint32_t nLine);
extern void* (*g_pfnL_1417f3166)(uint64_t nBytes);          // the allocator behind `mov $0x4608,%ecx`
extern void* (*g_pfnL_14177ead0)(void* pMem, void* pArg, uint32_t nArg2);
extern bool (*g_pfnL_14177e890)(void* pModule);

// 0x14177ec90 — allocate 0x4608 bytes, construct into them, CHECKF pModule, then verify through
// 0x14177e890 and destroy through vtable +0x8 when that says no. Returns the module or null.
void* Slot_14177ec90_ModuleCreate(void* pArg, uint32_t nArg2);
// 0x14177ead0 — the module constructor. Writes the derived vtable (0x14182e5a8) over the base one
// (0x14182e428), stores both extra arguments, constructs the base sub-object at +0x10 (0x1417d9710,
// the CMsgLog constructor), then sixteen message members at fixed offsets. Every one of those
// constructors is now ported: a wired seam still wins, otherwise the real body runs.
void* Slot_14177ead0_ModuleCtor(void* pMem, void* pArg2, uint32_t nArg3);
extern void (*g_pfnL_1417d9710)(void* pBase);                    // base sub-object at this+0x10
extern void (*g_pfnL_1417d8390)(void*);  extern void (*g_pfnL_1417d9000)(void*);
extern void (*g_pfnL_1417db330)(void*);  // the message destructor behind 0x1417db330
extern void (*g_pfnL_1417da8b0)(void*);  // the message destructor behind 0x1417da8b0
extern void (*g_pfnL_1417d6640)(void*);  extern void (*g_pfnL_1417d9e60)(void*);
extern void (*g_pfnL_1417da860)(void*);  extern void (*g_pfnL_1417dac30)(void*);
extern void (*g_pfnL_1417dae10)(void*);  extern void (*g_pfnL_1417db2b0)(void*);
extern void (*g_pfnL_1417dca60)(void*);  extern void (*g_pfnL_1417dd050)(void*);
extern void (*g_pfnL_1417dd230)(void*);  extern void (*g_pfnL_1417dd6e0)(void*);
extern void (*g_pfnL_1417dd9f0)(void*);  extern void (*g_pfnL_1417ddc60)(void*);
extern void (*g_pfnL_1417ddf50)(void*);  extern void (*g_pfnL_1417de240)(void*);

// 0x14177e890 — the module's registration pass: 18 constants through the sub-object's table slot
// +0x8, then 4 through +0x10, then one through +0x18 whose answer becomes the return value.
bool Slot_14177e890_Init(void* pThis);
// 0x14177ed30 / 0x14177ed40 — the two neighbours with no strings of their own.
void** Slot_14177ed30_StoreNull(void** ppOut);
void   Slot_14177ed40_NoOp();

}  // namespace tq
