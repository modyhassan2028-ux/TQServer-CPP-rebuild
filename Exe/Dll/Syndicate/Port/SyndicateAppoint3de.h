// D84 seams: appoint to 0x3de (FUN_1417acda0)
#ifndef SYNDICATE_APPOINT3DE_H
#define SYNDICATE_APPOINT3DE_H
#include <cstdint>
namespace syndicate {
extern void     (*g_fnA84LogErr)(const char*, uint64_t, uint64_t);
extern void*    (*g_fnA84FindUserById)(void*, uint32_t);        // 14178c8e0
extern char     (*g_fnA84IsValid)(void*);                      // 1417868c0
extern uint32_t (*g_fnA84GetSynId)(void*);                     // 141785ea0
extern void*    (*g_fnA84FindSyn)(void*, uint32_t);            // 1417cad00
extern void*    (*g_fnA84FindUserByName)(void*, const char*);  // 14178c9f0
extern char     (*g_fnA84IsOnline)(void*);                    // 141787300
extern uint32_t (*g_fnA84GetId)(void*);                       // 141785dc0
extern char     (*g_fnA84HasFlag)(void*);                      // 141786960
extern uint32_t (*g_fnA84GetRank)(void*);                     // 1417867d0
extern uint32_t (*g_fnA84RankCount)(void*, uint32_t);          // 141797ce0
extern int32_t  (*g_fnA84RankMax)(void*, uint32_t);            // 141791a50
extern char     (*g_fnA84HasSubRank)(void*);                   // 141786a20
extern void     (*g_fnA84ClearSubRank)(void*, uint32_t);       // 141787050
extern void     (*g_fnA84SetMemberRank)(void*, void*, uint32_t);// 14179f650
extern uint32_t (*g_fnA84Vt328)(void*, uint32_t);              // vt+0x328
extern void     (*g_fnA84RecordUpdate)(void*, void*, void*, uint32_t); // 1417c6bd0
extern void*    (*g_fnA84GetActorName)(void*);                 // 141787120
extern void*    (*g_fnA84StrMgr)(void);
extern const char* (*g_fnA84GetStr)(void*, const char*);
extern void     (*g_fnA84Snprintf)(char*, uint64_t, const char*, const char*);
extern void     (*g_fnA84SynTalk)(void*, uint32_t, const char*, uint32_t); // vt+0x88
extern void     (*g_fnA84UserTalk)(void*, uint32_t, const char*, uint32_t); // vt+0x18
extern void     (*g_fnA84SendMsg)(void*, uint32_t, void*);     // vt+8
extern void     (*g_fnA84MsgCtor)(void*);                      // 1417db2b0
extern char     (*g_fnA84MsgAppend)(void*, uint32_t, uint32_t, uint32_t, const char*); // 1417db630
extern void     (*g_fnA84MsgDtor)(void*);                      // 1417db330
extern char     (*g_fnA84HasOldPos)(void*);                    // 141787390
extern uint32_t (*g_fnA84GetOldId)(void*);                     // 141787380
extern void     (*g_fnA84RankSetMisc)(void*, void*, uint32_t, uint32_t, const char*); // 1417a0760
extern void     (*g_fnA84SynSave)(void*);                      // 14179e020
extern char s_szLogicPath84[];
uint32_t AppointPosition3de(void** apLogic, uint32_t idActor, const char* szAccept);
} // namespace syndicate
#endif
