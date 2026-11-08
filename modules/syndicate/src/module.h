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
// 0x14177ed30 / 0x14177ed40 — the two neighbours with no strings of their own.
void** Slot_14177ed30_StoreNull(void** ppOut);
void   Slot_14177ed40_NoOp();

}  // namespace tq
