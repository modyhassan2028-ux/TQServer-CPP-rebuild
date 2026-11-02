// ============================================================================
// common.h — RAW CQBase.dll v6159 · common.cpp
// ============================================================================
#ifndef CQBASE_COMMON_H
#define CQBASE_COMMON_H

#include <cstddef>
#include <cstdint>

namespace tq {

class CMyCriticalSection;

// 0x140b8b2e0 — a bounded copy. It answers false for a target that is missing, a
// source that is missing, or a zero length, and true once the text fits.
bool SafeCopy(char* pTarget, const char* pSource, size_t nBufLen);

// 0x140b8b3f0 — the one debug help lock, built on first use
CMyCriticalSection* GetDbgHelpCS();

}  // namespace tq
#endif
