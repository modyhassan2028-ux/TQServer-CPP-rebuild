// ============================================================================
// modules/syndicate/src/syndicatelogic.h — the ORIGINAL file
// (recovered from the binary literals: 28 CHECKF references to
// modules/syndicate/src/syndicatelogic.cpp — the home of the
// CSyndicateLogic class, vtable 0x141835068, 232 slots).
// Unit D90 wave 1: the first 18 real bodies, verbatim.
//
// The class object layout (recovered across D26-D88):
//   +0x00 the logic vtable   +0x08 the game-mgr box
//   +0x10 the members map     +0x18 the log-record map
//   [1] = the mgr box, [2] = the map, [3] = the log map,
//   [10] = the acct mgr (+0x50)
//
// THE SLOTS (index = vtable offset / 8):
//   +0x000 1417b61e0 deleting dtor (base a9680 seam)
//   +0x008 1417a9f20 pushSynAttrInfo (msg kit a860/a910/a8b0)
//   +0x010 1417a9fc0 destroySoon flow (cad00/92cb0/8f4f0/c5830
//          + the CMsgSyndicate kit db2b0/db3a0/db330)
//   +0x018 1417aa170 pushMemberInfo (8c8e0/5ea0/cad00/888040)
//   +0x020 1417aa280 pushAttrChange (a860/dab00/a8b0)
//   +0x028 1417aa320 pushProffer (dd6e0/dd790/dd730)
//   +0x030 1417aa3c0 donate flow (8e590 + vt+0x30)
//   +0x040 1417aa4b0 vt+0x88 forward
//   +0x048 1417aa4e0 member-online fwd (8e540)
//   +0x058 1417aa510 log-rec syn id (785d00)
//   +0x068 1417b6620 the rank-swap flow (787370/785ea0/
//          786aa0/vt+0x328/a0760/9f650/c6bd0)
//   +0x070 1417abe60 set-player fwd (cadb0)
//   +0x078 1417ab080 rank == 1000 (vt+0xf8)
//   +0x080 1417ab0a0 rank-clear fwd (7869f0)
//   +0x088 1417ab0c0 rank == 0x3de
//   +0x090 1417ab0e0 rank == 0x37a
//   +0x098 1417ab100 the assemblyman family gate
//   +0x0a0 1417ab170 the 0x2b2/0x28a gate
//   +0x0a8 1417b6e70 OnUserDelRole (767560/cad00/5ee00/
//          630d0/74b960/8c8e0/aebb0 + the literal log)
//
// SEAMS (deep bodies, later units):
//   g_fnT1DtorBody 1417a9680, g_fnT1MsgInitA 1417da910,
//   g_fnT1MsgInitB 1417dab00, g_fnT1MsgInitC 1417dd790,
//   g_fnT1MsgInitD 1417db3a0, g_fnT1MsgDtorA 1417da8b0,
//   g_fnT1MsgDtorC 1417dd730, g_fnT1RecGetData 141788040,
//   g_fnT1IsLowMoney 14178e590, g_fnT1MemberOnline 14178e540,
//   g_fnT1DelRoleSoon 141792cb0, g_fnT1GetDestroyDays 14178f4f0,
//   g_fnT1OptGet 1417c5830, g_fnT1SetPlayer 1417cadb0,
//   g_fnT1HasFlag 1417cad90, g_fnT1RankClear 1417869f0,
//   g_fnT1IsConfirmed 141786aa0, g_fnT1FlagClear 141787370,
//   g_fnT1DelRole 14174b960, g_fnT1QuitFlow 1417aebb0,
//   g_fnT1LogError (log_InlineLogERROR, 1-arg)
// REUSED: LeagueMemberLookup (1417cad00, LeagueCmp),
//   LogRecMapFind (14178c8e0, D60), CtorCMsgSynAttrInfo
//   (1417da860), CtorCMsgSynProffer (1417dd6e0),
//   CtorCMsgSyndicate (1417db2b0), MgrUserLeagueId
//   (14175ee00), MgrLeagueFind (1417630d0),
//   g_fnA84RankSetMisc/RecordUpdate/SetMemberRank (Appoint3de),
//   g_fnStringMgrInstance/GetStr (D61),
//   g_fnLbrOpDelete (operator_delete)
#ifndef MODULES_SYNDICATE_SRC_SYNDECATELOGIC_H
#define MODULES_SYNDICATE_SRC_SYNDECATELOGIC_H

#include <cstdint>

namespace syndicate {

// ---- the seams ----
extern void  (*g_fnT1DtorBody)(void*, uint64_t, void*, char*);
extern uint64_t (*g_fnT1MsgInitA)(void*, int64_t, int64_t);
extern uint64_t (*g_fnT1MsgInitB)(void*, int32_t, const char*);
extern uint64_t (*g_fnT1MsgInitC)(void*, uint32_t, void*);
extern uint64_t (*g_fnT1MsgInitD)(void*, uint32_t, int32_t);
extern void  (*g_fnT1MsgDtorA)(void*);
extern void  (*g_fnT1MsgDtorC)(void*);
extern void  (*g_fnT1RecGetData)(void*, void*);
extern char  (*g_fnT1IsLowMoney)(void*);
extern void  (*g_fnT1MemberOnline)(void*);
extern void  (*g_fnT1DelRoleSoon)(void*, uint32_t);
extern int64_t (*g_fnT1GetDestroyDays)(void*);
extern int32_t (*g_fnT1OptGet)(void*, uint32_t);
extern void  (*g_fnT1SetPlayer)(void*, uint32_t, uint32_t);
extern char  (*g_fnT1HasFlag)(void*, uint32_t);
extern void  (*g_fnT1RankClear)(int32_t);
extern uint64_t (*g_fnT1IsConfirmed)(void*);
extern uint64_t (*g_fnT1LogRecSynId)(void*);   // 141785d0
extern void  (*g_fnT1FlagClear)(int64_t, int32_t);
extern uint64_t (*g_fnT1DelRole)(void*, uint32_t);
extern uint64_t (*g_fnT1QuitFlow)(void*, void*, void*,
                                  const char*, char, char, char);
extern void  (*g_fnT1LogError)(const char*);


// ---- the shared string-mgr + A84 tails ----
extern void*    (*g_fnStringMgrInstance)();
extern void*    (*g_fnStringMgrGetStr)(void*, const char*);
extern char     (*g_fnA84HasOldPos)(void*);
extern uint32_t (*g_fnA84GetOldId)(void*);

// ---- D104 seams (+0x358 exit flow) ----
extern void  (*g_fn74D490)(void*, uint32_t);         // 14174d490
extern void  (*g_fn7C1180)(void*, uint32_t, uint32_t,
                           uint64_t);               // 1417c1180
extern void  (*g_fn76ACA0)(void*, uint32_t);         // 14176aca0
extern char  (*g_fn79E6D0)(void*, void*);            // 14179e6d0

// ---- D103 seams (+0x350 join flow) ----
extern uint64_t (*g_fn743C80)(void*);                // 141743c80
extern char  (*g_fn7977D0)(void*, uint32_t);         // 1417977d0
extern char  (*g_fn763920)(void*, uint32_t);         // 141763920
extern void  (*g_fn74E7E0)(void*);                   // 14174e7e0
extern int32_t (*g_fn76CA70)(void*, uint32_t, int32_t,
                             uint32_t);             // 14176ca70

// ---- D102 seams (+0x340 create flow) ----
extern int64_t (*g_fn75EB70)(void*, const char*);   // 14175eb70
extern void*  (*g_fn78C8E0)(void*, uint32_t);       // 14178c8e0
extern char   (*g_fn7868C0)(void*);                 // 1417868c0
extern uint64_t (*g_fn785EA0)(void*);               // 141785ea0
extern int32_t (*g_fn74E740)(void*);                // 14174e740
extern uint64_t (*g_fn78F270)(void*);               // 14178f270
extern char*   (*g_fn787120)(void*);                // 141787120
extern void*   (*g_fn76F7F0)(void*, uint32_t,
                             const char*, char, uint32_t,
                             const char*);           // 14176f7f0
extern void    (*g_fn74DCD0)(void*, int32_t);       // 14174dcd0
extern char    (*g_fn7903D0)(void*, int32_t);       // 1417903d0
extern void    (*g_fn7B0EA0)(void*, uint32_t, char); // 1417b0ea0

// ---- D101 seams (wave 10) ----
extern void  (*g_fn76FE50)(void*, int32_t*);       // 14176fe50
extern void  (*g_fn76ACE0)(void*);                 // 14176ace0
extern void  (*g_fn763DD0)(void*, int32_t, int32_t,
                           const char*);          // 141763dd0
extern void  (*g_fn764000)(void*, int32_t, int32_t,
                           const char*);          // 141764000
extern void  (*g_fn764230)(void*, int32_t, int32_t,
                           const char*);          // 141764230
extern void  (*g_fn764300)(void*, uint32_t, int32_t);   // 141764300
extern void  (*g_fn76EFC0)(void*, int32_t, int32_t,
                           int32_t);              // 14176efc0
extern void  (*g_fn76F190)(void*);                // 14176f190
extern void  (*g_fn745920)(void*, void*);          // 141745920
extern void  (*g_fn7645C0)(void*, uint32_t);       // 1417645c0
extern char  (*g_fn74EA40)(void*);                // 14174ea40
extern void  (*g_fn74EA30)(void*, int32_t);       // 14174ea30
extern uint64_t (*g_fn790390)(void*);              // 141790390
extern void*  (*g_fn78F470)(void*);                // 14178f470
extern uint64_t (*g_fn745520)(void*);              // 141745520

// ---- D100 seams (+0x2d0 title flow) ----
extern int32_t (*g_fn74E920)(void*);               // 14174e920
extern int32_t (*g_fn74E930)(void*);               // 14174e930
extern int*    (*g_fnCQLanguageGet)(void);          // tq::CQLanguageGet
extern int32_t (*g_fn7B0370)(void*, uint32_t);     // 1417b0370
extern void    (*g_fn743F90)(void*, int32_t,
                             const char*, char);   // 141743f90
extern uint32_t (*g_fnTimeGet)(int32_t);           // tq::TimeGet
extern uint64_t (*g_fnCMsgInit6820)(void*, int32_t,
    const char*, uint32_t, int32_t, int32_t);      // 1417d6820
extern void    (*g_fnCStrFormat215d0)(void*,
    const char*, uint64_t, uint64_t);              // 1417215d0
extern void    (*g_fnStrCopy)(char*, const char*,
                              unsigned long);      // tq::StrCopy

// ---- wave-9 seams (D99) ----
extern void     (*g_fnMgrCdfD0)(void*);                // 1417cdfd0
extern int      (*g_fn647E0)(void*, uint32_t);          // 1417647e0
extern uint32_t (*g_fn74E3F0)(void*);                  // 14174e3f0
extern void*    (*g_fn7630D0)(void*, uint32_t);        // 1417630d0
extern void     (*g_fn743D10)(void*);                  // 141743d10
extern void     (*g_fn743E60)(void*);                  // 141743e60
extern void*    (*g_fn743Dd0)(void*);                  // 141743dd0
extern void*    (*g_fn743D70)(void*);                  // 141743d70
extern uint32_t (*g_fn763C80)(void*, uint32_t);        // 141763c80
extern void     (*g_fn76EE60)(void*, uint32_t, int32_t);   // 14176ee60
extern void     (*g_fn76FBF0)(void*, uint32_t, int32_t,
                               uint64_t, char);        // 14176fbf0
extern uint64_t (*g_fn763680)(void*, uint32_t);        // 141763680
extern uint64_t (*g_fn78F2D0)(void*);                  // 14178f2d0
extern void     (*g_fn76ECF0)(void*, uint32_t, int32_t);    // 14176ecf0
extern uint32_t (*g_fn7B9220)(void*, uint32_t,
                              uint32_t);               // 1417b9220
extern void     (*g_fn7B52D0)(void*, uint32_t, uint32_t,
                              void*);                  // 1417b52d0
extern void     (*g_fnCMsgCtor6640)(void*);            // 1417d6640
extern uint64_t (*g_fnCMsgInit6790)(void*, int32_t,
    uint32_t, uint32_t, uint32_t);                      // 1417d6790
extern void     (*g_fnCMsgDtor66C0)(void*);            // 1417d66c0

// ---- wave-8 seams (D98) ----
extern void     (*g_fnInvalidParam)(void);               // _invalid_parameter_noinfo
extern void     (*g_fnMyLogSave)(const char*, const char*); // tq::MyLogSave
extern char     (*g_fnLgBf80)(void*, uint64_t);          // 14179bf80
extern uint64_t (*g_fnLgF550)(void*);                    // 14178f550
extern char     (*g_fnLgFa70)(void*, uint64_t);          // 14178fa70
extern void     (*g_fnIterC50)(void*, void*);           // 141741c50
extern void     (*g_fnIter730)(void*);                   // 141741730

// the prize tables (read verbatim from .rdata, ranks 1..8)
// DAT_1418347c4+4*r  (cross money):   100000,80000,...
static const uint32_t s_auCrossMoney[8] = {
    100000, 80000, 60000, 50000, 40000, 30000,
    20000, 10000 };
// DAT_1418347e4+4*r  (cross emoney):  10000,8000,...
static const uint32_t s_auCrossEmoney[8] = {
    10000, 8000, 6000, 5000, 4000, 3000,
    2000, 1000 };
// DAT_141834804+4*r  (vlm money):     12000,10000,...
static const uint32_t s_auVlmMoney[8] = {
    12000, 10000, 8000, 6500, 5000, 4000,
    3000, 2000 };
// DAT_141834824+4*r  (vlm emoney):    3000,2000,...
static const uint32_t s_auVlmEmoney[8] = {
    3000, 2000, 1000, 600, 500, 400,
    300, 200 };

// ---- wave-7 seams (D97) ----
extern void     (*g_fnSink3OpD)(void*);                 // 1417434f0
extern void     (*g_fnSub38Cdc0)(void*, const void*,
                    const void*, int32_t, int32_t);      // 14177cdc0
extern void     (*g_fnSub28Cd0)(void*, uint32_t,
                                 uint32_t);              // 141784cd0
extern uint64_t (*g_fnSub28F980)(void*, int32_t,
                                 int32_t);               // 14177f980
extern void     (*g_fnSub48D4670)(void*, uint32_t,
                    uint32_t, const char*, uint32_t,
                    int16_t, int16_t, int16_t, int16_t,
                    int16_t, int16_t);                   // 1417d4670
extern void     (*g_fnSub48D3100)(void*, int32_t,
                                  uint64_t);              // 1417d3100
extern char     (*g_fnLgInviteOk)(void*, uint32_t,
                    uint64_t, uint64_t);                 // 14179c8b0
extern char     (*g_fnSub9D3530)(void*, uint32_t,
                    uint32_t);                           // 1417d3530
extern char     (*g_fnLgMoneyLow)(void*);               // 14178e590
extern char     (*g_fnLgMemberFull)(void*);              // 14178e600
extern uint64_t(*g_fnLgLeaderRank)(void*);               // 141790390
extern void     (*g_fnSub10Call)(void*, uint32_t,
                                 uint32_t);              // 1417638e0
extern void     (*g_fnB19C0)(void*, uint32_t, char,
                              uint64_t);                 // 1417b19c0
extern char     (*g_fnB8470)(void*, void*, uint32_t,
                    int32_t, int32_t, char);             // 1417b8470
extern void     (*g_fnLgF4E0)(void*);                    // 14178f4e0
extern void     (*g_fnDelayMs)(uint32_t);                // 1417873a0
extern void     (*g_fnLgAd50)(void*, uint32_t);          // 14179ad50
extern void     (*g_fnSub9D3680)(void*, int32_t,
                                  int32_t);              // 1417d3680
extern uint32_t (*g_fnLogicVt510)(void*, uint32_t);      // vt+0x510
extern char     (*g_fnLogicVt78)(void*);                // vt+0x78

// ---- wave-6 seams (D96) ----
extern uint32_t (*g_fnA8940)(void*, uint32_t);         // 1417a8940
extern void*    (*g_fnSink1Get)(void);                  // 14173f9c0
extern void     (*g_fnSink1OpA)(void*, uint32_t);       // 14173fa40
extern void     (*g_fnSink1OpB)(void*, uint32_t,
                    uint32_t, uint32_t);                // 14173dbc0
extern void     (*g_fnSink1OpC)(void*);                 // 14173f4d0
extern void*    (*g_fnSink2Get)(void);                  // 141781b60
extern void     (*g_fnSink2OpA)(void*, int32_t);        // 141783470
extern void*    (*g_fnSink3Get)(void);                  // 141741a30
extern void     (*g_fnSink3OpA)(void*, void*);          // 141742810
extern void     (*g_fnSink3OpB)(void*, int32_t);        // 141740fd0
extern void     (*g_fnSink3OpC)(void*);                 // 141741b10
extern void     (*g_fnB4B0)(void*, int32_t,
                    const void*, const void*);           // 14177b4b0

// ---- wave-5 seams (D95) ----
extern int64_t  (*g_fnLgFindByName)(void*, const char*); // 1417c8aa0
extern char     (*g_fnLgIsAlly)(void*, uint32_t);        // 141797750
extern char     (*g_fnLgIsAntag)(void*, uint32_t);       // 1417977d0
extern int32_t  (*g_fnLgEnemyCnt)(void*);                // 141791c70
extern int32_t  (*g_fnLgEnemyMax)(void*);                 // 1417901d0
extern uint32_t (*g_fnLgAddEnemySlot)(void*, uint32_t);  // 14178e370
extern void     (*g_fnLgSetEnemy)(void*, uint32_t, uint32_t); // 14179a500
extern uint32_t (*g_fnLgFindAllySlot)(void*, int32_t);   // 14178e200
extern void     (*g_fnLgSetAlly)(void*, uint32_t, uint32_t);  // 14179a280
extern uint32_t (*g_fnLgFindAntagSlot)(void*, int32_t);  // 14178e270
extern void*    (*g_fnLgRefresh)(void*);                // 14178f470
extern uint64_t (*g_fnRecGetName)(void*);                 // 1417867d0
extern int64_t  (*g_fnRecGetMemberNo)(void*);             // 141787120
extern uint64_t (*g_fnBoxVt1d8)(void*, uint32_t);         // vt+0x1d8

// ---- wave-4 seams (D94) ----
extern uint64_t (*g_fnLgGetId)(void*);             // 14178f270
extern void*    (*g_fnFlowerA)(void*, int32_t, uint64_t, uint64_t);  // 1417886b0
extern void*    (*g_fnFlowerB)(void*, int32_t, uint64_t, uint64_t);  // 1417888b0
extern void*    (*g_fnFlowerC)(void*, int32_t, uint64_t, uint64_t);  // 1417887b0
extern void*    (*g_fnFlowerD)(void*, int32_t, uint64_t, uint64_t);  // 1417889b0
extern int64_t  (*g_fnLgGetFunds)(void*);          // 14178f4f0
extern void     (*g_fnLgAddFunds)(void*, int64_t); // 14179bf80
extern uint64_t (*g_fnInviteB210)(void*, uint32_t, void*); // 1417b8210

// ---- wave-3 seams (D93) ----
extern uint64_t (*g_fnRecA)(void*, int32_t);       // 1417881f0
extern uint64_t (*g_fnRecB)(void*, int32_t, uint64_t, uint64_t); // 141788370
extern uint64_t (*g_fnRecC)(void*, int32_t, void*, char);   // 141788400
extern uint64_t (*g_fnRecD)(void*, int32_t, char); // 141788560
extern void     (*g_fnRecE)(void*);                // 1417862c0
extern uint64_t (*g_fnRecF)(void*);                // 141786320
extern uint64_t (*g_fnRecG)(void*);                // 141786380
extern uint64_t (*g_fnRecH)(void*);                // 1417863e0
extern int32_t  (*g_fnRecI)(void*);                // 141785d50

// ---- wave-2 seams (D92) ----
extern int64_t (*g_fnLgFind)(void*, uint32_t);      // 1417cad00
extern char    (*g_fnLgFindB)(void*, uint32_t);     // 1417cad90
extern void    (*g_fnLgClearA)(void*);              // 1417caa00
extern void    (*g_fnLgClearB)(void*);              // 1417cb030
extern uint64_t(*g_fnLgRankUpd)(void*, void*, void*, uint32_t); // 1417c6bd0
extern int64_t (*g_fnCtyFind)(void*, uint32_t);     // 1417631d0
extern void    (*g_fnCtyPush)(void*, uint32_t, int32_t, int32_t); // 14174b360
extern void    (*g_fnCtyFwdA)(void*, uint32_t, int16_t, uint32_t); // 1417679a0
extern void    (*g_fnCtyFwdB)(void*, uint32_t, int32_t, uint32_t); // 141767ab0
extern void    (*g_fnCtyFwdC)(void*, uint32_t, int16_t, uint32_t); // 141767780
extern void    (*g_fnRecKick)(void*);              // 141787120
extern void    (*g_fnRecSetA)(void*, int32_t);     // 1417871c0
extern void    (*g_fnRecSetB)(void*, int32_t);     // 1417871b0
extern void    (*g_fnRecSetC)(void*, int32_t);     // 141787150
extern void    (*g_fnRecClr)(void*);               // 141786ff0
extern uint64_t(*g_fnRecGetX)(void*, int32_t);     // 141788c20
extern uint64_t(*g_fnRecChk)(void*, int32_t);      // 141789160
extern uint64_t(*g_fnRecGetRank)(void*);            // 1417867d0
extern char    (*g_fnRecIsLeader)(void*);           // 1417868c0
extern uint64_t(*g_fnA84GetSynId2)(void*);          // 141785ea0 (rank get)
extern void    (*g_fnRankSetA)(void*, void*, int32_t);   // 14179f650
extern void    (*g_fnRankSetB)(void*, void*, int32_t, uint32_t, char); // 1417a0760
extern char    (*g_fnLgTest)(void*, char);          // 1417983e0
extern uint64_t(*g_fnLgGetX)(void*);               // 14178f2d0
extern uint64_t(*g_fnLgGetY)(void*);               // 14178f610
extern uint64_t(*g_fnLgZ)(void*, char);            // 14179c0f0
extern uint64_t(*g_fnLeaveSyn)(void*, void*, void*, const char*, char, char, char); // 1417aebb0

class CSyndicateLogic {
public:
    // ---- the vtable bodies (slot = the vtable
    // offset; the REAL name only where the binary
    // reveals it) ----
    void*   Slot000DelDtor(void* p, uint64_t u2,
                           void* p3, char* p4);   // 1417b61e0
    void    Slot008PushSynAttrInfo(               // 1417a9f20
        uint32_t uUser);
    uint64_t Slot010DestroySoon(int32_t nUser);   // 1417a9fc0
    void    Slot018PushMemberInfo(               // 1417aa170
        uint32_t uUser);
    void    Slot020PushAttrChange(               // 1417aa280
        int32_t nWho, int32_t nWhat,
        const char* pName);
    uint8_t Slot028PushProffer(uint32_t uUser,   // 1417aa320
        int64_t lA, int64_t lB);
    uint64_t Slot030Donate(uint32_t uUser,       // 1417aa3c0
        int64_t lMoney);
    uint64_t Slot040Fwd88();                     // 1417aa4b0
    void    Slot048MemberOnline(                 // 1417aa4e0
        uint32_t uUser);
    uint64_t Slot058LogRecSynId(uint32_t uUser); // 1417aa510
    uint64_t Slot068RankSwap(uint32_t uA,        // 1417b6620
                             uint32_t uB);
    void    Slot070SetPlayer(uint32_t uA,       // 1417abe60
                             uint32_t uB);
    bool    Slot078IsRank1000();                 // 1417ab080
    void    Slot080RankClear();                  // 1417ab0a0
    bool    Slot088IsRank3de();                  // 1417ab0c0
    bool    Slot090IsRank37a();                  // 1417ab0e0
    int64_t Slot098AssemblymanGate();            // 1417ab100
    int64_t Slot0a0Gate2b228a();                 // 1417ab170
    // the REAL name — the literal log names it
    uint64_t OnUserDelRole(uint32_t uUser);     // 1417b6e70

    // ---- D92 wave 2: slots +0x0b0..+0x140 ----
    uint64_t Slot0b0GetSynId(uint32_t uUser);   // 1417aacb0
    void    Slot0b8RecKick(uint32_t uUser);    // 1417abe90
    void    Slot0c0RecSet5(uint32_t uUser, int32_t n);  // 1417abec0
    void    Slot0c8RecSet9(uint32_t uUser, int32_t n);  // 1417abf50
    void    Slot0d0LgClearA();                 // 1417ac010
    uint64_t Slot0d8LeaderSwap(uint32_t uA, uint32_t uB); // 1417abcd0
    uint8_t Slot0e0LgClearB();                  // 1417ac040
    uint64_t Slot0f0QuitSyn(uint32_t u, uint32_t n);  // 1417ac510
    uint64_t Slot0f8GetRankIfLeague(uint32_t u); // 1417aabf0
    uint64_t Slot100QuitOrKick(uint32_t u);     // 1417b8150
    uint64_t Slot108RecSet6(uint32_t u, int32_t n);   // 1417ac440
    uint64_t Slot110LgZ(uint32_t u, char c);    // 1417ac270
    uint64_t Slot128LgGetY(uint32_t u);         // 1417aac80
    void    Slot130RecClr(uint32_t u);          // 1417af480
    uint64_t Slot138RecChkFwd(uint32_t u, int32_t n); // 1417aa540
    uint64_t Slot140RecGetX(uint32_t u, int32_t n);   // 1417ac0a0
    // ---- D93 wave 3: slots +0x148..+0x188 ----
    uint64_t Slot148RecA(uint32_t u, int32_t n);   // 1417ac0d0
    uint64_t Slot150RecB(uint32_t u, int32_t n,
                         uint64_t a, uint64_t b);  // 1417ac100
    uint64_t Slot158RecC(uint32_t u, int32_t n);   // 1417ac130
    uint64_t Slot160RecD(uint32_t u, int32_t n);   // 1417ac170
    void    Slot168RecE(uint32_t u);               // 1417ab310
    uint64_t Slot170RecF(uint32_t u);              // 1417ac1b0
    uint64_t Slot178RecG(uint32_t u);              // 1417ac1e0
    uint64_t Slot180RecH(uint32_t u);              // 1417ac210
    int32_t Slot188RecI(uint32_t u);               // 1417ac240
    // ---- D94 wave 4: slots +0x190..+0x1a0 ----
    // the REAL name — the literal log names it
    uint64_t OnFlowerChange(uint32_t uUser, int32_t nType,
                            int32_t n, uint64_t uB); // 1417aae40
    uint8_t Slot198MoveFunds(uint32_t uUser, uint32_t uTo,
                             int64_t lAmt);     // 1417abac0
    uint64_t Slot1a0InviteGate(uint32_t uUser,
                               uint32_t uWho);   // 1417ba630
    // ---- D95 wave 5: slots +0x1a8..+0x1c8 ----
    uint64_t Slot1a8SetAntagonize(uint32_t uUser,
                                  const char* pszName); // 1417aa5c0
    uint8_t  Slot1b0ClearAlly(uint32_t uUser,
                              const char* pszName);   // 1417ac9f0
    uint64_t Slot1b8ClearAntagonize(uint32_t uUser,
                                    const char* pszName); // 1417aa910
    uint64_t Slot1c0IsAllyGate(uint32_t uLg,
                               uint32_t uOther);       // 1417b6df0
    uint64_t Slot1c8IsAntagGate(uint32_t uLg,
                                uint32_t uOther);      // 1417b6e30
    // ---- D96 wave 6: slots +0x1d0..+0x208 ----
    uint32_t Slot1d0Sub20Delegate(uint32_t u);    // 1417af310
    void Slot1d8Sink1OpA(uint32_t u);             // 1417af330
    void Slot1e0Sink1OpB(uint32_t u, uint32_t v,
                         uint32_t w);              // 1417af350
    void Slot1e8Sink1OpC();                        // 1417af390
    void Slot1f0Sink2OpA(int32_t n);               // 1417af3b0
    void Slot1f8Sink3Loop(uint32_t u, void* p);    // 1417af3d0
    void Slot200Sink3OpB(int32_t n);               // 1417af410
    void Slot208B4b0ThenSink3(const void* p,
                              const void* q);      // 1417af430
    // ---- D97 wave 7: slots +0x210..+0x258 ----
    void Slot210Flag60Sink3();                      // 1417af460
    void Slot220Sub38Cdc0(int32_t a, int32_t b,
                          const void* p,
                          const void* q);            // 1417afa70
    void Slot228Sub28Cd0(uint32_t a, uint32_t b);    // 1417afaa0
    uint64_t Slot230Sub28F980(int32_t a,
                              int32_t b);            // 1417afac0
    void Slot238Sub30B4b0(uint32_t a, const void* p,
                          const void* q);            // 1417afae0
    void Slot240Sub48D4670(uint32_t a, uint32_t b,
                           const char* s, uint32_t c,
                           int16_t s1, int16_t s2,
                           int16_t s3, int16_t s4,
                           int16_t s5,
                           int16_t s6);             // 1417afba0
    void Slot248Sub48D3100(int32_t a,
                           uint64_t b);              // 1417afc40
    void Slot250InviteFlow(uint32_t u, uint64_t p3,
                           uint64_t p4);             // 1417b8620
    void Slot258Sub9D3680(int32_t n);                // 1417afc90
    void Slot218AwardPrizeVlmOrCross(
        void* pvSynID, void* pvBSelf, char bCross); // 1417c3ed0
    void Slot260Destroy(void);                    // 1417ac020
    uint64_t Slot268(int32_t n);                  // 1417b0770
    uint64_t Slot270(int32_t n);                  // 1417b07c0
    void Slot278(uint32_t u, int32_t n3, uint32_t u4,
                 char c5);                        // 1417b9650
    void Slot280(uint32_t u, int32_t n3,
                 void* p4);                       // 1417b9880
    void Slot288(uint32_t u);                     // 1417b1b90
    void Slot290(void);                           // 1417b1ba0
    void Slot298(void);                           // 1417b0360
    void Slot2A0(uint32_t u, int32_t n);          // 1417b1be0
    void Slot2A8(void);                           // 1417b1bf0
    void* Slot2B0(void);                          // 1417b1c30
    uint64_t Slot2B8(void);                       // 1417b1c80
    void* Slot2C0(void);                          // 1417b1cf0
    void* Slot2C8(uint32_t u);                    // 1417b1dd0
    void Slot2D0(int32_t n, uint32_t u,
                 const char* p4);                 // 1417b1e80
    void Slot2D8(int32_t* p2);                    // 1417b22a0
    void Slot2E0(void);                           // 1417b22b0
    void Slot2E8(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22c0
    void Slot2F0(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22d0
    void Slot2F8(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22e0
    void Slot300(uint32_t u2, int32_t n3);        // 1417b22f0
    void Slot308(int32_t n2, int32_t n3,
                 int32_t n4);                     // 1417b2300
    void Slot310(void);                           // 1417b2310
    void Slot318(uint16_t u2, uint32_t u3);       // 1417b2320
    void Slot320(uint32_t u2);                     // 1417b23f0
    void Slot328(uint32_t u);                      // 1417b2400
    void Slot330(void);                           // 1417b2540
    bool Slot340(uint32_t u2, const char* p3,
                 char c4);                         // 1417b8940
    void Slot350(uint32_t u2, uint32_t u3,
                 uint32_t u4);                     // 1417b16b0
    void Slot358(uint32_t u2, uint32_t u3,
                 uint32_t u4);                     // 1417c13e0



};

}  // namespace syndicate

#endif  // MODULES_SYNDICATE_SRC_SYNDECATELOGIC_H
