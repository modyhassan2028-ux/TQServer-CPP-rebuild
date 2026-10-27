// ============================================================================
// SyndicateVlmAward.h — unit D82 seams:
// AwardPrizeVlmOrCross (FUN_1417c3ed0)
#ifndef SYNDICATE_VLM_AWARD_H
#define SYNDICATE_VLM_AWARD_H
#include <cstdint>

namespace syndicate {

extern void*    (*g_fnVlmFindSyn)(void*, uint32_t);          // 1417cad00
extern char     (*g_fnVlmAddMoney)(void*, uint64_t);          // 14179bf80
extern void*    (*g_fnVlmSynName)(void*);                     // 14178f470
extern uint64_t (*g_fnVlmGetEmoney)(void*);                   // 14178f550
extern uint32_t (*g_fnVlmEmoneyField)(void*);                 // 14178f270
extern char     (*g_fnVlmSetEmoney)(void*, uint64_t);          // 14178fa70
extern void     (*g_fnVlmBitAdv)(void*);                      // 141741730
extern void*    (*g_fnVlmBitSeek)(void*, int64_t);             // 141741c50
extern void     (*g_fnVlmSendMsg)(void*, uint32_t, uint32_t, uint32_t); // vt+0x350
extern void     (*g_fnVlmBroadcast)(void*, uint32_t, const void*, uint32_t); // vt+0x40
extern void     (*g_fnVlmMyLogSave)(const char*, const char*,
        void*, uint32_t, uint64_t, uint32_t);                  // tq::MyLogSave
extern const char* (*g_fnVlmGetStr)(void*, const char*);       // theInstance GetStr
extern void*    (*g_fnVlmStrMgr)(void);                        // theInstance
extern void     (*g_fnVlmSnprintf)(char*, uint64_t, const char*,
        uint32_t, uint32_t);                                   // _snprintf
extern void     (*g_fnVlmLogErr)(const char*);                 // log_InlineLogERROR

void AwardPrizeVlmOrCross(void** apLogic, uint64_t* aVecSyn,
        uint64_t* aBitset, char bCross);

} // namespace syndicate
#endif
