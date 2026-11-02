// ============================================================================
// crossvlmresult.h — RAW Syndicate.dll v6159 · crossvlmresult.cpp
//   0x141741a30, the one place this class is ever made: a guarded CMyHeap and a member
//   that is filled on the first call and handed back every time after.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef SYNDICATE_CROSSVLMRESULT_H
#define SYNDICATE_CROSSVLMRESULT_H

#include <cstdint>

namespace tq {

class CCrossVlmResult {
public:
    static CCrossVlmResult* InstanceGet();   // 0x141741a30
};

// 0x141741840, the constructor, not ported yet
extern CCrossVlmResult* (*g_pfnConstructCrossVlmResult)(void* pMem);

}  // namespace tq

#endif  // SYNDICATE_CROSSVLMRESULT_H
