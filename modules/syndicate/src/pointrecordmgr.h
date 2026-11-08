// pointrecordmgr.h — 0x14177ed50. The CHECKF carries
// f:\version\cqserver-78.0.11-1204\modules\syndicate\src\pointrecordmgr.cpp and the expression
// "pConsumer", so the second argument is the consumer being attached.
#pragma once
#include <cstdint>

namespace tq {

extern void (*g_pfn_checkf_pointrecordmgr)(const char* pFmt, const char* pMacro, const char* pExpr,
                                          const char* pFile, uint32_t nLine);

// 0x14177ed50 — store the consumer through the out pointer; a null consumer logs and returns false.
bool Slot_14177ed50_AttachConsumer(void** ppOut, void* pConsumer);

}  // namespace tq
