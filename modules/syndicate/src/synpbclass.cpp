// synpbclass.cpp — see synpbclass.h
#include "modules/syndicate/src/synpbclass.h"

#include <limits>

namespace tq {

int32_t g_nSynLimit8c = 0;
int32_t g_nSynLimit90 = 0;
int32_t g_nSynLimit94 = 0;
int32_t g_nSynLimit98 = 0;

// 0x1417ea8f0 — the self pointer is never read
std::string* SynPbNameConcubines(void* pSelf, std::string* pOut) {
    (void)pSelf;
    *pOut = "CMsgLeagueConcubinesPB";
    return pOut;
}

// 0x1417ec4f0
std::string* SynPbNameOrderStatusInfo(void* pSelf, std::string* pOut) {
    (void)pSelf;
    *pOut = "CMsgLeagueOrderStatusInfoPB";
    return pOut;
}

// 0x1417ec580
std::string* SynPbNameOrderStatus(void* pSelf, std::string* pOut) {
    (void)pSelf;
    *pOut = "CMsgLeagueOrderStatusPB";
    return pOut;
}

// 0x1417eded0
std::string* SynPbNameRobItem(void* pSelf, std::string* pOut) {
    (void)pSelf;
    *pOut = "CMsgLeagueRobItemPB";
    return pOut;
}

// 0x1417edf60
std::string* SynPbNameRobList(void* pSelf, std::string* pOut) {
    (void)pSelf;
    *pOut = "CMsgLeagueRobListPB";
    return pOut;
}

// 0x141821e90
void SynLimitInit8c(void) { g_nSynLimit8c = std::numeric_limits<int>::max(); }
// 0x141821eb0
void SynLimitInit90(void) { g_nSynLimit90 = std::numeric_limits<int>::max(); }
// 0x141821ed0
void SynLimitInit94(void) { g_nSynLimit94 = std::numeric_limits<int>::max(); }
// 0x141821ef0
void SynLimitInit98(void) { g_nSynLimit98 = std::numeric_limits<int>::max(); }

}  // namespace tq
