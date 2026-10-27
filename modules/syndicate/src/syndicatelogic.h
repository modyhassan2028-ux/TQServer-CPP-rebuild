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



};

}  // namespace syndicate

#endif  // MODULES_SYNDICATE_SRC_SYNDECATELOGIC_H
