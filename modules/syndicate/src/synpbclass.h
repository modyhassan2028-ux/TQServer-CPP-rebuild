// ============================================================================
// synpbclass.h — RAW Syndicate.dll v6159 · the last missing slot of five protobuf
//   message classes, plus the four numeric-limit statics they share.
//   Every GetTypeName below was read off the instructions: the body puts the class
//   name into the std::string through MSVCP90's std::string(char const*) at IAT
//   0x141823270, with the literal taken from the exact .rdata address the lea names.
//     CMsgLeagueConcubinesPB      std::string literal 0x141841598
//     CMsgLeagueOrderStatusInfoPB std::string literal 0x141841930
//     CMsgLeagueOrderStatusPB     std::string literal 0x141841978
//     CMsgLeagueRobItemPB         std::string literal 0x141841d80
//     CMsgLeagueRobListPB         std::string literal 0x141841dc0
//   The four statics call MSVCP90 std::numeric_limits<int>::max() (IAT 0x141823268,
//   the import table proves the name) and store the answer into their own global.
// ============================================================================
#ifndef SYNDICATE_SYNPBCLASS_H
#define SYNDICATE_SYNPBCLASS_H

#include <cstdint>
#include <string>

namespace tq {

// the GetTypeName slot of each class (slot 5 of the vtable)
std::string* SynPbNameConcubines(void* pSelf, std::string* pOut);        // 0x1417ea8f0
std::string* SynPbNameOrderStatusInfo(void* pSelf, std::string* pOut);   // 0x1417ec4f0
std::string* SynPbNameOrderStatus(void* pSelf, std::string* pOut);       // 0x1417ec580
std::string* SynPbNameRobItem(void* pSelf, std::string* pOut);           // 0x1417eded0
std::string* SynPbNameRobList(void* pSelf, std::string* pOut);           // 0x1417edf60

// the four static initialisers: global = numeric_limits<int>::max()
void SynLimitInit8c(void);   // 0x141821e90 -> 0x141886e8c
void SynLimitInit90(void);   // 0x141821eb0 -> 0x141886e90
void SynLimitInit94(void);   // 0x141821ed0 -> 0x141886e94
void SynLimitInit98(void);   // 0x141821ef0 -> 0x141886e98

// the globals themselves, kept so the initialisers can be observed
extern int32_t g_nSynLimit8c;
extern int32_t g_nSynLimit90;
extern int32_t g_nSynLimit94;
extern int32_t g_nSynLimit98;

}  // namespace tq

#endif  // SYNDICATE_SYNPBCLASS_H
