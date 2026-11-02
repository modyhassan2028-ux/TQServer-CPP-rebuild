// ============================================================================
// crossvlmresult.h — RAW Syndicate.dll v6159 · crossvlmresult.cpp
//   0x141741840 the constructor, 0x141741a30 the one place the object is ever made.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef SYNDICATE_CROSSVLMRESULT_H
#define SYNDICATE_CROSSVLMRESULT_H

#include <cstdint>

namespace tq {

// The eight byte node the object's list head points at: one pointer and nothing else.
struct SynListNode {
    SynListNode* pNext;
};

class CCrossVlmResult {
public:
    CCrossVlmResult* Construct();            // 0x141741840
    static CCrossVlmResult* InstanceGet();   // 0x141741a30

    uint64_t u0;        // +0x00, written last by the constructor
    void* pListHead;    // +0x08, the node above
    uint64_t u10;       // +0x10
    uint64_t u18;       // +0x18
    uint64_t u20;       // +0x20
    uint64_t u28;       // +0x28
    uint64_t u30;       // +0x30
};

// the hook the test hangs the constructor on, the default is the ported body
extern CCrossVlmResult* (*g_pfnConstructCrossVlmResult)(void* pMem);

// 0x14172cfe0, called on the list head by the constructor, not ported yet
extern void (*g_pfnInitCrossVlmList)(void** ppListHead);

}  // namespace tq

#endif  // SYNDICATE_CROSSVLMRESULT_H
