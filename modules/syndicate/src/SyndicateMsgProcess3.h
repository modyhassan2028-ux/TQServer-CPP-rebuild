// ============================================================================
// SyndicateMsgProcess3.h — unit D83 seams:
// CMsgSyndicate::Process (FUN_1417db7b0)
#ifndef SYNDICATE_MSGPROCESS3_H
#define SYNDICATE_MSGPROCESS3_H
#include <cstdint>

namespace syndicate {

// mgr access + state gates
extern void*    (*g_fnM83GetMgr)(void);                       // 1417b6210
extern char     (*g_fnM83GateA)(void*);                       // 1417ac6f0
extern char     (*g_fnM83InWar)(void*);                       // 1417ac710
extern char     (*g_fnM83GateB)(void*);                       // 1417ac700
extern char     (*g_fnM83GateC)(void*);                       // 1417ac720
extern char     (*g_fnM83WarOpen)(void*);                     // 1417ac730
extern int64_t  (*g_fnM83MaxRank)(void*);                     // 1417ac7e0
extern uint32_t (*g_fnM83TargetUser)(void*);                  // 1417ac7f0
extern uint32_t (*g_fnM83TalkArg)(void*);                     // 1417ac800
extern uint32_t (*g_fnM83LockA)(void*);                       // 1417ac810
extern void     (*g_fnM83Ac430)(void*);                       // 1417ac430
extern void     (*g_fnM83Unlock)(void*);                      // 1417ac7d0
extern void*    (*g_fnM83FindByUser)(void*, uint32_t);        // 1417ae630
// talk + strings
extern void     (*g_fnM83Talk)(void*, uint32_t, const char*, uint64_t); // 1417ac750
extern void*    (*g_fnM83StrMgr)(void);                       // theInstance
extern const char* (*g_fnM83GetStr)(void*, const char*);
// vt calls on the mgr
extern uint32_t (*g_fnM83GetRank)(void*, uint32_t);           // vt+0xf8
extern void     (*g_fnM83Vt018)(void*, uint32_t);             // vt+0x18
extern void     (*g_fnM83Vt0e8)(void*, uint32_t, const char*, uint32_t); // vt+0xe8
extern void     (*g_fnM83Vt100)(void*, uint32_t);             // vt+0x100
extern void     (*g_fnM83Vt120)(void*, uint32_t, uint32_t);   // vt+0x120
extern void     (*g_fnM83Vt138)(void*, uint32_t, uint32_t);   // vt+0x138
extern void     (*g_fnM83Vt1a8)(void*, uint32_t, const char*); // vt+0x1a8
extern void     (*g_fnM83Vt1b0)(void*, uint32_t, const char*); // vt+0x1b0
extern void     (*g_fnM83Vt1b8)(void*, uint32_t, const char*); // vt+0x1b8
// plain state functions
extern void     (*g_fnM83Bad50)(void*, uint32_t, uint32_t, uint64_t);   // 1417bad50
extern void     (*g_fnM83Bb0e0)(void*, uint32_t, uint32_t);             // 1417bb0e0
extern void     (*g_fnM83Ac820)(void*, uint32_t, uint32_t);             // 1417ac820
extern void     (*g_fnM83B7850)(void*, uint32_t, const char*);         // 1417b7850
extern void     (*g_fnM83Ac9c0)(void*, uint32_t, int32_t);              // 1417ac9c0
extern void     (*g_fnM83Bb500)(void*, uint32_t, const char*, int32_t); // 1417bb500
extern void     (*g_fnM83Aab70)(void*, uint32_t, uint32_t, uint32_t, uint32_t); // 1417aab70
extern void     (*g_fnM83Acc80)(void*, uint32_t, const char*);          // 1417acc80
extern void     (*g_fnM83B7ae0)(void*, uint32_t, const char*, int32_t); // 1417b7ae0
extern void     (*g_fnM83Acda0)(void*, uint32_t, const char*);          // 1417acda0
extern void     (*g_fnM83B7c10)(void*, uint32_t, uint32_t, int32_t);    // 1417b7c10
extern void     (*g_fnM83B7e70)(void*, uint32_t, const char*);          // 1417b7e70
extern void     (*g_fnM83Adeb0)(void*, uint32_t);                       // 1417adeb0
extern void     (*g_fnM83Ae130)(void*, uint32_t);                       // 1417ae130
extern void     (*g_fnM83Ae3a0)(void*, uint32_t, const char*);          // 1417ae3a0
extern void     (*g_fnM83Ad190)(void*, uint32_t, const char*, uint32_t); // 1417ad190
extern void     (*g_fnM83Ad790)(void*, uint32_t, const char*);          // 1417ad790
extern void     (*g_fnM83Adbb0)(void*, uint32_t, const char*);          // 1417adbb0
extern void     (*g_fnM83Ae6b0)(void*, uint32_t, int32_t);              // 1417ae6b0
extern char     (*g_fnM83BackAdd)(void*, uint32_t);           // 1417983e0
extern char     (*g_fnM83BlAdd)(void*, uint32_t, uint32_t);   // 14179c700
extern char     (*g_fnM83BlRem)(void*, uint32_t, uint32_t);   // 14179c820
// rank setters for case 0x25
extern void     (*g_fnM83RankSet)(void*, uint32_t);           // 141797ce0
extern void     (*g_fnM83RankAdd)(void*, uint32_t);           // 141791a50
// msg plumbing
extern void     (*g_fnM83MsgCtor)(void*);                     // 1417db2b0
extern void     (*g_fnM83MsgInit)(void*);                    // CMsg::Init
extern void     (*g_fnM83MsgSetVft)(void*);                  // vftable write
extern uint32_t (*g_fnM83GetStrAmount)(void*);                // CStringPacker
extern void     (*g_fnM83GetString)(void*, uint32_t, char*, uint32_t);
extern void     (*g_fnM83AddString)(void*, const char*);
extern uint32_t (*g_fnM83GetSize)(void*);
extern void     (*g_fnM83PackerDtor)(void*);
extern void     (*g_fnM83Snprintf)(char*, uint64_t, const char*, uint32_t);
extern int32_t  (*g_fnM83AnnounceChk)(const char*, int32_t);  // tq::AnnounceStrCheck
extern void     (*g_fnM83LogErr)(const char*, uint64_t, uint64_t); // log_InlineLogERROR

void MsgSyndicateProcess(void** apMsg, uint32_t idActor, uint64_t uArg4);

} // namespace syndicate
#endif
