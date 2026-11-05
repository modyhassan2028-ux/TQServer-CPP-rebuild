// synpbio.cpp — see synpbio.h
#include "modules/syndicate/src/synpbio.h"

#include <cstddef>
#include <limits>
#include <string>

namespace tq {

void (*g_fnPbLogAliasing)(int, const char*, int, const char*) = nullptr;

int32_t g_nSynLimit7c = 0;
int32_t g_nSynLimit80 = 0;
int32_t g_nSynLimit84 = 0;
int32_t g_nSynLimit88 = 0;

// 0x1417e64a0
int64_t SynPbArrayInByteCount(void* pSelf) {
    return (int64_t)*(int32_t*)((uint8_t*)pSelf + 0x18);
}

// 0x1417e68b0 — the original tail-jumps into std::string::size
int64_t SynPbArrayOutByteCount(void* pSelf) {
    std::string* pStr = *(std::string**)((uint8_t*)pSelf + 0x08);
    return (int64_t)pStr->size();
}

// 0x1417e7750
int64_t SynPbCopyingByteCount(void* pSelf) {
    uint8_t* p = (uint8_t*)pSelf;
    return *(int64_t*)(p + 0x18) + (int64_t)*(int32_t*)(p + 0x2c);
}

// 0x1417e7980
bool SynPbSlotFalse(void) { return false; }

// 0x1417e7d90 — severity 3, the exact literals, line 0x31, and the answer stays false
bool SynPbAliasingRefusal(void) {
    g_fnPbLogAliasing(3,
                      "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream.cc",
                      0x31,
                      "This ZeroCopyOutputStream doesn't support aliasing. Reaching here usually "
                      "means a ZeroCopyOutputStream implementation bug.");
    return false;
}

// 0x141821e10
void SynLimitInit7c(void) { g_nSynLimit7c = std::numeric_limits<int>::max(); }
// 0x141821e30
void SynLimitInit80(void) { g_nSynLimit80 = std::numeric_limits<int>::max(); }
// 0x141821e50
void SynLimitInit84(void) { g_nSynLimit84 = std::numeric_limits<int>::max(); }
// 0x141821e70
void SynLimitInit88(void) { g_nSynLimit88 = std::numeric_limits<int>::max(); }

}  // namespace tq
