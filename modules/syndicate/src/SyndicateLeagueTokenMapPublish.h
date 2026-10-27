// ============================================================================
// SyndicateLeagueTokenMapPublish.h — unit D81 seams:
// PublishSupportTokenFromMap (FUN_1417c1a90)
#ifndef SYNDICATE_LEAGUE_TOKEN_MAP_PUBLISH_H
#define SYNDICATE_LEAGUE_TOKEN_MAP_PUBLISH_H
#include <cstdint>

namespace syndicate {

// --- helper seams already established (declared here so this
// unit links against its own definition sites) ---
extern char     (*g_fnMapWarStateB)(void*);                       // vt+0x288
extern char     (*g_fnMapMemberSigned)(void*, uint32_t);          // vt+0x278
extern char     (*g_fnMapMemberGateC)(void*, uint32_t);           // vt+0x280
extern char     (*g_fnMapMemberGateF)(void*, uint32_t);           // vt+0x4c8
extern uint32_t (*g_fnMapUserLeague)(void*, uint32_t);            // vt+0x4a8
extern char     (*g_fnMapSignedPublish)(void*, uint32_t, uint32_t, uint32_t); // vt+0x450
extern uint32_t (*g_fnMapMemberTreeKey)(void*, uint32_t, uint32_t); // vt+0x568
extern uint32_t (*g_fnMapCallupTimeout)(void*);                   // vt+0x4b0
extern char     (*g_fnMapMemberGateA)(void*, uint32_t);           // vt+0x268
extern char     (*g_fnMapMemberGateD)(void*, uint32_t);           // vt+0x4d8
extern char     (*g_fnMapMemberGateE)(void*, uint32_t);           // vt+0x4d0
extern void     (*g_fnMapSendMsg)(void*, uint32_t, void*);        // vt+8
extern void     (*g_fnMapTalk)(void*, uint32_t, const void*, uint32_t); // vt+0x18
extern void     (*g_fnMapBroadcast)(void*, void*, uint64_t*);        // vt+0x40
// --- RAW helpers ---
extern void*    (*g_fnMapFindLeague)(void*, uint32_t);            // 1417630d0
extern void*    (*g_fnMapTokenFindA)(void*, uint32_t);            // 14174bac0
extern void*    (*g_fnMapTokenFindB)(void*, uint32_t, uint32_t, uint32_t); // 14174bbe0
extern uint32_t (*g_fnMapTokenId)(void*);                         // 1417d4ed0
extern uint32_t (*g_fnMapTokenFlag)(void*);                       // 1417d4e70
extern void*    (*g_fnMapTokenRow)(void*, uint32_t);              // 141764870
extern char     (*g_fnMapBuildText)(void*, uint32_t, void*, void*, void*, void*); // 1417b2570
extern int64_t  (*g_fnMapLeagueMoney)(void*);                     // 1417440d0
extern void     (*g_fnMapLeagueSetMoney)(void*, uint64_t, char);  // 141744130
extern void     (*g_fnMapTokenSet)(void*, int32_t, uint32_t, char); // 1417d4f30
extern void     (*g_fnMapMsgStCtor)(void*);                       // 1417d7350
extern char     (*g_fnMapMsgTokCreate)(void*, uint8_t, uint8_t, uint64_t); // 1417d7650
extern void     (*g_fnMapMsgStDtor)(void*, uint64_t, uint64_t, void*); // 1417d73a0
extern void     (*g_fnMapLeagueInfo)(void*, void*);               // 141745580
extern void     (*g_fnMapGetNameA)(void*, uint32_t, uint32_t*, char*, int32_t); // 141766b60
extern void     (*g_fnMapGetNameB)(void*, uint32_t, uint32_t*, char*, int32_t); // 141766d10
extern void     (*g_fnMapMsgInfoCtor)(void*);                     // 1417d6110
extern uint32_t (*g_fnMapAwardFlag)(void*, uint32_t, void*);      // 1417b5370
extern char     (*g_fnMapMsgInfoCreate)(void*, void*, uint32_t, uint32_t, uint32_t, const char*, const char*); // 1417d61c0
extern void     (*g_fnMapMsgInfoDtor)(void*);                     // 1417d6160
extern void*    (*g_fnMapTreeInsert)(uint64_t*, void*);           // 141732040
extern void     (*g_fnMapReserveCallup)(void*, uint32_t, uint32_t, uint32_t, uint64_t*); // 1417be5f0
extern void     (*g_fnMapMsgLtCtor)(void*);                       // 1417d9000
extern char     (*g_fnMapMsgLtCreate)(void*, int32_t, uint32_t, int32_t, const char*, uint64_t); // 1417d9140
extern void     (*g_fnMapMsgLtDtor)(void*);                       // 1417d9050
extern void     (*g_fnMapPublishRecord)(void*, uint32_t, int32_t, void*); // 141777de0
extern void     (*g_fnMapLogErr)(const char*, const char*, const char*, const char*);
extern void     (*g_fnMapDbLogErr)(const char*, uint64_t, const char*, uint32_t);
extern const char* (*g_fnMapGetStr)(void*, const char*);          // theInstance GetStr
extern void*    (*g_fnMapStrMgr)(void);                           // theInstance
extern uint32_t (*g_fnMapTimeGet)(int32_t);                       // tq::TimeGet
extern uint64_t (*g_fnMapTimeNow)(void);                          // _time64
extern void*    (*g_fnMapNew)(uint64_t);                          // operator new
extern void     (*g_fnMapDelete)(void*);                          // operator delete
extern void*    (*g_fnMapRowField)(void*, int32_t);
extern int64_t  (*g_fnMapRowCost)(void*);                         // row vt+0x58
extern int32_t  (*g_fnMapRowOffset)(void*);                       // row vt+0x50

int32_t PublishSupportTokenFromMap(void** apLogic, uint32_t uUser,
        uint32_t uLeagueTarget, uint32_t uTarget, int32_t nParam5,
        uint32_t uParam6, uint32_t uParam7);

} // namespace syndicate
#endif
