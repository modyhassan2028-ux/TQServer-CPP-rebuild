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

// ---- D114a seams (wave 19: TRUE +0x560..+0x678, the small half) ----
extern bool     (*g_fn1417d9cc0)(void*, uint32_t,
    uint32_t, uint32_t, uint32_t,
    const char*, const char*);   // 1417d9cc0 (Create type 2)
extern void     (*g_fn14175efe0)(void*, uint32_t,
                                 uint32_t);           // 14175efe0
extern void     (*g_fn141798a20)(void*, uint32_t,
                                 uint64_t);           // 141798a20
extern void     (*g_fn14174eee0)(void*, uint32_t,
                                 void*, uint64_t);   // 14174eee0
extern void     (*g_fn14175f4a0)(void*, uint32_t,
                                 uint32_t);           // 14175f4a0
extern void     (*g_fn141764b80)(void*, uint32_t,
                                 uint32_t);           // 141764b80
extern void     (*g_fn141764f10)(void*, uint32_t,
                                 uint32_t);           // 141764f10
extern void     (*g_fn14175fa60)(void*, uint32_t);   // 14175fa60
extern void     (*g_fn1417652c0)(void*, uint32_t);   // 1417652c0
extern void     (*g_fn1417684b0)(void*, uint16_t);   // 1417684b0
extern void     (*g_fn1417685f0)(void*, uint16_t);   // 1417685f0
extern void     (*g_fn14174ebb0)(void*);             // 14174ebb0
extern void     (*g_fn1417715f0)(void*, uint32_t,
                                 int32_t, void***);   // 1417715f0
extern void     (*g_fn141774c20)(void*);             // 141774c20
extern void     (*g_fn141766330)(void*, uint16_t,
                                 uint32_t*);          // 141766330
extern void     (*g_fn14176ff50)(void*, uint16_t,
                                 uint32_t*);          // 14176ff50
// the 0x2d-byte stride record of the info-list vector
// (14174dda0 fill contract)
struct Rec2d {
    uint8_t ab[0x2d];
};

// the 0x2b-byte stride record of the list-page vector
// (14174ef80 fill contract)
struct Rec2b {
    uint8_t ab[0x2b];
};

extern void*    (*g_fn1417630d0)(void*, uint32_t);   // 1417630d0
extern void     (*g_fn14174dda0)(void*, void*);           // 14174dda0
extern void     (*g_fn1417bf610)(void*, void*, int64_t,
                                 void*);                  // 1417bf610
extern void     (*g_fn1417d9410)(void*);                  // 1417d9410
extern uint8_t  (*g_fn1417d94c0)(void*, uint32_t, int64_t,
                                 uint32_t);              // 1417d94c0
extern uint8_t  (*g_fn1417d9550)(void*, void*);           // 1417d9550
extern void     (*g_fn1417d9690)(void*);                  // 1417d9690
extern void     (*g_fn1417d9460)(void*);                  // 1417d9460
extern void     (*g_fn14174ef80)(void*, void*);           // 14174ef80
extern void     (*g_fn1417bf7c0)(void*, void*, int64_t,
                                 void*);                  // 1417bf7c0
extern void     (*g_fn1417d7800)(void*);                  // 1417d7800
extern uint8_t  (*g_fn1417d78b0)(void*, uint8_t);         // 1417d78b0
extern void     (*g_fn1417d7850)(void*);                  // 1417d7850
extern uint8_t  (*g_fn1417d7910)(void*, void*);           // 1417d7910
extern void     (*g_fn1417d7a40)(void*);                  // 1417d7a40
extern void     (*g_fn14174ef60)(void*, void*);           // 14174ef60
extern void     (*g_fn14174efa0)(void*, void*);           // 14174efa0
extern void     (*g_fn1417d5e50)(void*);                   // 1417d5e50
extern uint8_t  (*g_fn1417d5f00)(void*, uint8_t);         // 1417d5f00
extern uint8_t  (*g_fn1417d5f60)(void*, void*);           // 1417d5f60
extern void     (*g_fn1417d60a0)(void*);                   // 1417d60a0
extern void     (*g_fn1417d5ea0)(void*);                   // 1417d5ea0
extern void*    (*g_fn141777a30)(void*, uint32_t,
                                 uint32_t);               // 141777a30
extern void     (*g_fn141745580)(void*, void*);           // 141745580
extern uint32_t (*g_fn1417b5370)(void*, uint32_t,
                                 void*);                  // 1417b5370
extern void     (*g_fn141766b60)(void*, uint32_t, void*,
                                 void*, uint32_t);       // 141766b60
extern void     (*g_fn141766d10)(void*, uint32_t, void*,
                                 void*, uint32_t);       // 141766d10
extern void     (*g_fn1417d6110)(void*);                  // 1417d6110
extern bool     (*g_fn1417d61c0)(void*, const void*,
    uint32_t, uint32_t, uint32_t, const char*,
    const char*);                                          // 1417d61c0
extern void     (*g_fn1417d6160)(void*);                  // 1417d6160
extern void*    (*g_fn141764870)(void*, uint32_t);         // 141764870
extern void*    (*g_fn14174bac0)(void*, uint32_t);          // 14174bac0
extern uint32_t (*g_fn141745520)(void*);                     // 141745520
extern uint32_t (*g_fn141743e70)(void*);                     // 141743e70
extern char     (*g_fn14174f000)(void*, uint32_t,
                                 uint32_t);                 // 14174f000
extern int32_t  (*g_fn14174e950)(void*);                      // 14174e950
extern void     (*g_fn141823090)(const char*,
    uint32_t, const char*, uint32_t);                       // 141823090
extern void     (*g_fn1418230a8)(const char*, const char*,
    uint32_t, void*, uint32_t, uint32_t, uint32_t, uint32_t,
    uint32_t);                                               // 1418230a8
extern void     (*g_fn1417d4f30)(void*, uint32_t, uint32_t,
                                 uint8_t);                   // 1417d4f30
extern void     (*g_fn1417d7350)(void*);                     // 1417d7350
extern uint32_t (*g_fn1417d4ed0)(void*, uint32_t);           // 1417d4ed0
extern char     (*g_fn1417d7650)(void*, uint32_t,
                                 uint8_t, uint32_t);         // 1417d7650
extern void     (*g_fn1417d73a0)(void*);                     // 1417d73a0
extern char     (*g_fn1417632e0)(void*, uint32_t, void*,
                                 uint32_t);                 // 1417632e0
extern void     (*g_fn141790440)(void*, void*);              // 141790440
extern void     (*g_fn1417d8c20)(void*);                     // 1417d8c20
extern char     (*g_fn1417d8cd0)(void*, int32_t);           // 1417d8cd0
extern char     (*g_fn1417d8d40)(void*, void*);              // 1417d8d40
extern void     (*g_fn1417d8e50)(void*);                     // 1417d8e50
extern void     (*g_fn1417d8c70)(void*);                     // 1417d8c70
extern void     (*g_fn14174d5a0)(void*, void*);               // 14174d5a0
extern uint32_t (*g_fn1417d4e70)(void*);                      // 1417d4e70
extern uint32_t (*g_fn141823048)(uint32_t);                  // 141823048
extern char     (*g_fn1417d73e0)(void*);                     // 1417d73e0
extern char     (*g_fn1417d7440)(void*);                     // 1417d7440
extern char     (*g_fn1417d7770)(void*, uint32_t, uint8_t,
                                 void*);                      // 1417d7770
extern void*    (*g_fn14174bbe0)(void*, uint32_t);          // 14174bbe0
extern int64_t  (*g_fn1417440d0)(void*);                      // 1417440d0
extern void     (*g_fn141744130)(void*, int64_t,
                                 uint8_t);                  // 141744130
extern char     (*g_fn1417b2570)(void*, uint32_t, void*,
    void*, void*, void*);                                    // 1417b2570
extern void     (*g_fn141823280)(void*);                     // 141823280
extern void     (*g_fn141823290)(void*);                     // 141823290
extern void     (*g_fn1417be5f0)(void*, uint32_t, uint32_t,
    uint32_t, void*);                                        // 1417be5f0
extern void     (*g_fn141732040)(void*, void*);               // 141732040
extern void     (*g_fn1417d9000)(void*);                     // 1417d9000
extern char     (*g_fn1417d9140)(void*, uint32_t, uint32_t,
    uint32_t, const char*, uint32_t);                        // 1417d9140
extern void     (*g_fn1417d9050)(void*);                     // 1417d9050
extern void     (*g_fn141777de0)(void*, uint32_t, uint32_t,
                                 void*);                     // 141777de0
extern uint32_t (*g_fn1418232c8)(uint32_t);               // 1418232c8
extern uint64_t (*g_fn141764990)(void*, uint32_t,
                                 uint32_t);           // 141764990
extern char     (*g_fn141774500)(void*, uint32_t,
                                 uint64_t);           // 141774500
extern void*    (*g_fn14178c8e0)(void*, uint32_t);   // 14178c8e0
extern void     (*g_fn141787d70)(void*, uint64_t);   // 141787d70
extern int32_t  (*g_fn141787de0)(void*);              // 141787de0
extern void     (*g_fn141767890)(void*, uint32_t,
                                 uint64_t, uint32_t); // 141767890
extern void     (*g_fn14174b360)(void*, uint32_t,
                                 int32_t, uint64_t);  // 14174b360
extern char     (*g_fn14174be40)(void*, uint32_t);   // 14174be40
extern void     (*g_fn1417d6640)(void*);              // 1417d6640 ctor

// ---- D113 seams (wave 18: TRUE +0x378..+0x470) ----
extern uint32_t (*g_fn1417a8940)(void*, uint32_t);     // 1417a8940
extern void*    (*g_fn14173f9c0)();                     // 14173f9c0
extern void     (*g_fn14173fa40)(void*, uint32_t);      // 14173fa40
extern void     (*g_fn14173dbc0)(void*, uint32_t,
                                 uint32_t, uint32_t);  // 14173dbc0
extern void     (*g_fn14173f4d0)(void*);                // 14173f4d0
extern void*    (*g_fn141781b60)();                     // 141781b60
extern void     (*g_fn141783470)(void*, uint32_t);       // 141783470
extern void*    (*g_fn141741a30)();                     // 141741a30
extern void     (*g_fn141742810)(void*, void*);          // 141742810
extern void     (*g_fn141740fd0)(void*, uint32_t);       // 141740fd0
extern void     (*g_fn141741b10)(void*);                // 141741b10
extern void     (*g_fn1417434f0)(void*);                // 1417434f0
extern void     (*g_fn14177b4b0)(void*, int32_t,
                                 int64_t, int64_t);    // 14177b4b0
// RAW afa70: the callee args are REORDERED —
// cdc0(x, p4, p5, p2, p3)
extern void     (*g_fn14177cdc0)(void*, int64_t,
                                 int64_t, uint32_t,
                                 uint32_t);            // 14177cdc0
extern void     (*g_fn141784cd0)(void*, uint32_t,
                                 uint32_t);            // 141784cd0
extern uint64_t (*g_fn14177f980)(void*, uint32_t,
                                 uint32_t);           // 14177f980
extern void     (*g_fn1417d4670)(void*, uint32_t,
                                 uint32_t, const void*,
                                 uint32_t, int16_t, int16_t,
                                 int16_t, int16_t, int16_t,
                                 int16_t);             // 1417d4670
extern void     (*g_fn1417d3100)(void*, uint32_t,
                                 uint32_t);            // 1417d3100
extern void     (*g_fn1417d3680)(void*, uint32_t,
                                 uint32_t);            // 1417d3680
extern char     (*g_fn14179c8b0)(void*, uint32_t,
                                 int64_t, int64_t);    // 14179c8b0
extern char     (*g_fn1417d3530)(void*, uint32_t,
                                 uint32_t);            // 1417d3530
extern char     (*g_fn14178e600)(void*);                // 14178e600
extern int32_t   (*g_fn141790390)(void* pLeague);          // 141790390 (shared with InviteNotify)
extern void     (*g_fn1417638e0)(void*, uint32_t,
                                 uint32_t);            // 1417638e0
extern char     (*g_fn1417b8470)(void*, void*,
                                 uint32_t, int32_t,
                                 int32_t, int32_t);    // 1417b8470
extern void*    (*g_fn1417873a0)(int32_t);              // 1417873a0
extern void*    (*g_fn14178f4e0)(void*);                // 14178f4e0
extern void     (*g_fn14179ad50)(void*, uint32_t);       // 14179ad50

// ---- D112 seams (wave 17: TRUE +0x2e0..+0x370) ----
extern void*    (*g_fn1417c8c10)(void*, uint32_t);     // 1417c8c10
extern void*    (*g_fn1417c8d80)(void*, uint32_t);     // 1417c8d80 (ret discarded)
extern void     (*g_fn1417cb270)(void*, uint32_t);      // 1417cb270
extern void     (*g_fn1417cb360)(void*, uint32_t,
                                 uint32_t);            // 1417cb360
extern void*    (*g_fn141790100)(void*);                // 141790100
extern uint32_t (*g_fn14178f790)(void*);                // 14178f790
extern uint64_t (*g_fn14178f7d0)(void*, uint32_t);       // 14178f7d0
extern uint64_t (*g_fn14178f7b0)(void*, int64_t,
                                 int64_t, int64_t);    // 14178f7b0
extern void     (*g_fn1417c6c90)(void*);                // 1417c6c90
extern void     (*g_fn1417c6c80)(void*);                // 1417c6c80
extern void     (*g_fn1417cfb60)(void*, uint32_t);       // 1417cfb60
extern void     (*g_fn1417a8d30)(void*, uint32_t,
                                 uint32_t);            // 1417a8d30
extern void     (*g_fn1417a8e40)(void*, uint32_t,
                                 int32_t, uint32_t,
                                 uint32_t);            // 1417a8e40
extern void     (*g_fn1417a8f70)(void*, uint32_t,
                                 int32_t, uint32_t,
                                 uint32_t);            // 1417a8f70
extern void     (*g_fn1417a8810)(void*, uint32_t);       // 1417a8810
extern void     (*g_fn1417a88a0)(void*, uint32_t, void*);// 1417a88a0
extern void     (*g_fn1417a8b00)(void*, uint32_t);       // 1417a8b00
extern void     (*g_fn1417a7e70)(void*);                // 1417a7e70
extern uint8_t  (*g_fn1417a8a50)(void*, uint32_t, void*);// 1417a8a50
extern void     (*g_fn14179d3c0)(void*, int32_t,
                                 int32_t);             // 14179d3c0
// RAW: KERNEL32 MulDiv(nMult1, nMult2, nDiv) — rounds to
// nearest, 0 on overflow/div0 (ac2d0: MulDiv(p4,2,100) =
// the 2% SynWar prize cut)
extern int32_t  (*g_fnMulDiv)(uint32_t, uint32_t,
                              uint32_t);
// the RAW 5-arg star log: (fmt "★%s(%s)★ in %s, %d",
// type, var, path, line) — D112 lines 0x1487/0x149a/
// 0x14a2/0x14aa/0x14b2/0x664/0x66c
extern void     (*g_fnSynLogCheck)(const char*, const char*,
                                   const char*, const char*,
                                   uint32_t);
// the RAW 4-vararg gmlog/syndenote save (ac2d0: the prize
// cut): MyLogSave(file, fmt, name, actor, synId, money)
extern void     (*g_fnSynNoteLog)(const char*, const char*,
                                  const void*, uint32_t,
                                  uint32_t, uint32_t);

// ---- D111 seams (wave 16: +0x038/+0x0e8/+0x118) ----
extern char     (*g_fn797750)(void*, uint32_t);     // 141797750
extern void*    (*g_fn78C9F0)(void*, void*);        // 14178c9f0 (by-name find; RAW takes the std::string obj)
extern char     (*g_fn787300)(void*);                // 141787300
extern uint64_t (*g_fn785DC0)(void*);                // 141785dc0
extern char     (*g_fn786960)(void*);                // 141786960
extern void     (*g_fn79F650)(void*, void*, int32_t); // 14179f650
extern void     (*g_fn7C6BD0)(void*, void*, void*,
                              uint32_t);            // 1417c6bd0
extern char     (*g_fn787390)(void*);                // 141787390
extern uint64_t (*g_fn787380)(void*);                // 141787380
extern void     (*g_fn79FA60)(void*, uint32_t);      // 14179fa60
extern void     (*g_fn78F900)(void*, const char*);   // 14178f900
extern void     (*g_fn78F960)(void*, uint32_t);       // 14178f960
extern char     (*g_fn7DB630)(void*, int32_t, int32_t,
                              uint32_t, void*);     // 1417db630
extern void     (*g_fn79E020)(void*);                // 14179e020
extern void*    (*g_fn796390)(void*, int32_t);       // 141796390
extern void     (*g_fn786E30)(void*, int32_t);       // 141786e30

// ---- D110 seams (wave 15: +0x050/+0x060/+0x120) ----
extern void     (*g_fn787370)(void*, uint32_t);     // 141787370

extern int32_t  (*g_fn7AEA90)(void*, void*, void*); // 1417aea90
extern int64_t  (*g_fn7862C0)(void*);              // 1417862c0
extern void     (*g_fn785F00)(void*, int32_t,
                              void*, int64_t);    // 141785f00
extern char     (*g_fn78E590)(void*);              // 14178e590
extern int64_t  (*g_fn7867D0)(void*);              // 1417867d0
extern int64_t  (*g_fn7A05D0)(void*, void*,
                              void*);              // 1417a05d0
extern void     (*g_fn7A0760)(void*, void*, int32_t,
                              uint32_t, char);     // 1417a0760
extern uint64_t (*g_fn7AEBB0)(void*, void*, void*,
                              const char*, char, char,
                              char);               // 1417aebb0
extern void     (*g_fn7DB2B0)(void*);              // 1417db2b0
extern char     (*g_fn7DB3A0)(void*, int32_t,
                              int32_t);           // 1417db3a0
extern uint64_t (*g_fn7DB330)(void*);              // 1417db330

// ---- D109 seams (wave 14: +0x230/+0x238) ----
extern uint64_t (*g_fn7CEC20)(void*, uint32_t);     // 1417cec20
extern void     (*g_fn77D180)(void*, uint32_t, int32_t); // 14177d180
extern void     (*g_fn77BEB0)(void*, uint32_t, int32_t,
                              int64_t);             // 14177beb0
extern void*    (*g_fn73F9C0)();                    // 14173f9c0
extern void     (*g_fn73F4B0)(void*, uint32_t);     // 14173f4b0
extern void     (*g_fn7D4870)(void*, uint32_t, void*,
                              int64_t);             // 1417d4870
extern char     (*g_fn7CD250)(void*, const char*);  // 1417cd250

// ---- D108 seams (wave 13, TRUE numbering +0x1d0..+0x288) ----
extern uint32_t (*g_fn78E4A0)(void*, int32_t);        // 14178e4a0
extern uint32_t (*g_fn78E400)(void*, int32_t);        // 14178e400
extern uint64_t (*g_fn78F4F0)(void*);                // 14178f4f0
extern uint64_t (*g_fn79BF80)(void*, int64_t);       // 14179bf80
extern uint64_t (*g_fn7CAB90)(void*);                // 1417cab90
extern uint64_t (*g_fn78FB00)(void*, uint8_t);       // 14178fb00
extern uint64_t (*g_fn78F5B0)(void*);                // 14178f5b0
extern uint32_t (*g_fn786440)(void*);                // 141786440
extern void     (*g_fn786620)(void*, int32_t);       // 141786620
extern void     (*g_fn7DD6E0)(void*);                // 1417dd6e0
extern char     (*g_fn7DD790)(void*, int32_t, void*); // 1417dd790
extern uint64_t (*g_fn7DD730)(void*);                // 1417dd730
extern void     (*g_fn7CFA30)(void*, void*);         // 1417cfa30
extern void     (*g_fn79DB30)(void*, int32_t);       // 14179db30
extern uint32_t (*g_fn7CE230)(void*, uint32_t, const char*,
                              uint32_t, int32_t, uint32_t); // 1417ce230
extern void     (*g_fn77C4F0)(void*, uint32_t);      // 14177c4f0
extern uint64_t (*g_fn7B9010)(void*, uint32_t, uint32_t); // 1417b9010
extern void     (*g_fn7CAD90)(void*, uint32_t);      // 1417cad90
extern int64_t  (*g_fn7C8AA0)(void*, const char*);   // 1417c8aa0
extern uint64_t (*g_fn7CADE0)(void*, uint32_t);      // 1417cade0
extern uint64_t (*g_fn78F550)(void*);                // 14178f550
extern uint64_t (*g_fn78FA70)(void*, int32_t);       // 14178fa70

// ---- D107 seams (wave 12) ----
extern void     (*g_fn7CB000)(void*, uint32_t);       // 1417cb000
extern int64_t  (*g_fn78F4E0)(void*);                 // 14178f4e0
extern void     (*g_fn7873A0)(int32_t);               // 1417873a0
extern int32_t  (*g_fn798800)(void*);                 // 141798800
extern uint32_t (*g_fn78F400)(void*);                 // 14178f400
extern uint64_t (*g_fn78F410)(void*);                 // 14178f410
extern void     (*g_fn76ACF0)(void*, int32_t, uint32_t,
                              int32_t, uint16_t, uint16_t); // 14176acf0

// ---- D106 seams (wave 11) ----
extern uint32_t (*g_fn75EE00)(void*, uint32_t);      // 14175ee00
extern uint64_t (*g_fn74EF00)(void*, uint32_t);      // 14174ef00
extern uint64_t (*g_fn74EF20)(void*, int32_t);       // 14174ef20
extern void    (*g_fn74ED30)(void*, uint32_t);       // 14174ed30
extern void    (*g_fn74EBE0)(void*, uint32_t, int32_t); // 14174ebe0
extern void    (*g_fn74EC50)(void*, uint32_t, int32_t); // 14174ec50
extern uint64_t (*g_fn74ECC0)(void*, uint32_t, int32_t); // 14174ecc0
extern void    (*g_fn768020)(void*, uint16_t);       // 141768020
extern void    (*g_fn7524D0)(void*, int32_t, uint32_t); // 1417524d0

// ---- D105 seams (+0x360 leader change) ----
extern void  (*g_fn743E80)(void*, int32_t, int32_t,
                          char);                // 141743e80
extern void  (*g_fn74D3E0)(void*);                // 14174d3e0
extern void  (*g_fn7B92B0)(void*, uint32_t, uint32_t,
                           uint32_t, const char*); // 1417b92b0

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
    // ==== NUMBERING CORRECTION (2026-10-27) ====
    // The TRUE vtable is 232 slots at file off 0x113668
    // (+0x000..+0x738). D97-D107 slot labels were taken
    // from a base 53 slots late: a label "+0xNNN" written
    // in those units is truly +0xNNN+0x1a8. Mapping of
    // the mislabeled waves to TRUE offsets:
    //   D97  +0x210..0x258 -> +0x3b8..+0x400
    //   D98  +0x218        -> +0x3c0
    //   D99/D100 +0x2d0    -> +0x478
    //   D101 +0x2d8..+0x330-> +0x480..+0x4d8
    //   D102 +0x340        -> +0x4e8
    //   D103 +0x350        -> +0x4f8
    //   D104 +0x358        -> +0x500
    //   D105 +0x360        -> +0x508
    //   D106 +0x368..+0x3b0-> +0x510..+0x558
    //   D107 +0x0e8..+0x130-> +0x2b0..+0x2d8
    // Method NAMES below (SlotXXX from those waves) keep
    // their old labels; do not reuse those numbers for
    // new slots. All ported bodies verified genuine.

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
    uint64_t Slot410(int32_t n);                  // 1417b0770
    uint64_t Slot418(int32_t n);                  // 1417b07c0
    void Slot420(uint32_t u, int32_t n3, uint32_t u4,
                 char c5);                        // 1417b9650
    void Slot428(uint32_t u, int32_t n3,
                 void* p4);                       // 1417b9880
    void Slot430(uint32_t u);                     // 1417b1b90
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
    void Slot480(int32_t* p2);                    // 1417b22a0
    void Slot488(void);                           // 1417b22b0
    void Slot490(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22c0
    void Slot498(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22d0
    void Slot4A0(int32_t n2, int32_t n3,
                 const char* p4);                 // 1417b22e0
    void Slot4A8(uint32_t u2, int32_t n3);        // 1417b22f0
    void Slot4B0(int32_t n2, int32_t n3,
                 int32_t n4);                     // 1417b2300
    void Slot4B8(void);                           // 1417b2310
    void Slot4C0(uint16_t u2, uint32_t u3);       // 1417b2320
    void Slot4C8(uint32_t u2);                     // 1417b23f0
    void Slot4D0(uint32_t u);                      // 1417b2400
    void Slot4D8(void);                           // 1417b2540
    bool Slot4E8(uint32_t u2, const char* p3,
                 char c4);                         // 1417b8940
    void Slot4F8(uint32_t u2, uint32_t u3,
                 uint32_t u4);                     // 1417b16b0
    void Slot500(uint32_t u2, uint32_t u3,
                 uint32_t u4);                     // 1417c13e0
    void Slot508(uint32_t u2, uint32_t u3,
                 uint32_t u4);                     // 1417b9380
    uint32_t Slot510(uint32_t u2);                 // 1417b02f0
    uint64_t Slot518(uint32_t u2);                 // 1417afe40
    uint64_t Slot520(uint32_t u2);                 // 1417b5810
    uint64_t Slot528(int32_t n2);                   // 1417b5820
    void Slot530(uint32_t u2);                     // 1417b0e90
    void Slot538(uint32_t u2);                     // 1417afe70
    void Slot540(uint32_t u2);                     // 1417afec0
    uint64_t Slot548(uint32_t u2);                 // 1417aff10
    void Slot550(uint16_t u2);                     // 1417aff60
    void Slot558(int32_t n2, uint32_t u3);         // 1417aff80
    void Slot0E8(uint32_t u2);                     // 1417ab1c0
    int64_t Slot0F0(uint32_t u2);                  // 1417ab2b0
    void Slot0F8(int32_t n2);                      // 1417aeba0
    bool Slot100(uint32_t u2);                      // 1417af4b0
    uint64_t Slot108(uint32_t u2, void** pp3);      // 1417af720
    int32_t Slot110(uint32_t u2);                   // 1417af780
    uint32_t Slot118(uint32_t u2);                  // 1417afd50
    uint64_t Slot120(uint32_t u2);                  // 1417afdb0
    uint64_t Slot128(uint32_t u2);                  // 1417afe10
    void Slot130(int32_t n2, uint32_t u3,
                 int32_t n4, uint16_t u5,
                 uint16_t u6);                      // 1417b2780
    // ---- D108 wave 13 (TRUE offsets) ----
    uint64_t Slot1D0();                             // 1417aaf90
    uint64_t Slot1D8();                             // 1417aafa0
    const char* Slot1E0(uint32_t u2, int32_t n3);    // 1417ab220
    const char* Slot1E8(uint32_t u2, int32_t n3);    // 1417b6f80
    uint64_t Slot1F0(uint32_t u2, int64_t l3);       // 1417af4d0
    uint64_t Slot1F8(uint32_t u2, int32_t n3);       // 1417af580
    uint64_t Slot200();                             // 1417abe70
    uint64_t Slot208(uint32_t u2, uint8_t c3);       // 1417ab1e0
    uint64_t Slot210(uint32_t u2);                   // 1417abfe0
    uint64_t Slot218(uint32_t u2, int32_t n3);       // 1417aad30
    void Slot220();                                 // 1417bd1a0
    uint64_t Slot228(uint32_t u2, const char* pc3,
                     uint32_t u4, int32_t n5,
                     uint32_t u6);                   // 1417ba5a0
    uint64_t Slot248(uint32_t u2);                   // 1417ab1d0
    uint64_t Slot250(const char* pc2);               // 1417abc70
    uint32_t Slot258(uint32_t u2);                   // 1417ab2e0
    uint64_t Slot260(uint32_t* pu2);                 // 1417abc20
    uint64_t Slot268(uint32_t u2);                   // 1417aaff0
    uint64_t Slot270(uint32_t u2, int32_t n3);       // 1417aafb0
    uint64_t Slot278(uint32_t u2);                   // 1417ab020
    bool Slot280(int32_t n2);                        // 1417abc50
    bool Slot288(int32_t n2);                        // 1417abc60
    // ---- D109 wave 14 (TRUE offsets) ----
    uint64_t Slot230(uint32_t u2);                   // 1417bd310
    uint64_t Slot238(uint32_t u2, const char* pc3,
                     uint32_t u4, uint32_t u5);      // 1417ab610
    // ---- D110 wave 15 (TRUE offsets) ----
    int64_t  Slot050(uint32_t u2, uint64_t u3,
                     int64_t l4);                   // 1417b62e0
    uint64_t Slot060(uint32_t u2, uint32_t u3);     // 1417b64e0
    uint64_t Slot120(uint32_t u2, uint32_t u3);     // 1417b6ab0
    // ---- D111 wave 16 (TRUE offsets) ----
    void Slot038(uint32_t u2, int64_t l3);          // 1417c0510
    char Slot0e8(uint32_t u2, const char* pc3,
                  char c4);                          // 1417ba6f0
    uint64_t Slot118(uint32_t u2,
                      const char* pc3);              // 1417b6770



    // ---- D112 wave 17 (TRUE offsets +0x2e0..+0x370) ----
    uint8_t  Slot2E0(uint32_t u2);                 // 1417af7d0
    uint8_t  Slot2E8(uint32_t u2);                 // 1417af8e0
    uint32_t Slot2F0(uint32_t u2);                  // 1417af940
    uint64_t Slot2F8(uint32_t u2, uint32_t u3);      // 1417af990
    uint64_t Slot300(uint32_t u2, int64_t l3,
                     int64_t l4, int64_t l5);       // 1417af9f0
    char     Slot308(uint32_t u2, uint32_t u3,
                     int32_t n4);                   // 1417ac2d0
    void     Slot310(void);                         // 1417bd550
    uint8_t  Slot318(void);                         // 1417ac060
    uint8_t  Slot320(void);                         // 1417ac080
    uint8_t  Slot328(uint32_t u2);                  // 1417ab340
    uint8_t  Slot330(uint32_t u2);                  // 1417ab1a0
    void     Slot338(uint32_t u2, uint32_t u3);     // 1417af290
    void     Slot340(uint32_t u2, int32_t n3,
                     uint32_t u4, uint32_t u5);     // 1417af230
    void     Slot348(uint32_t u2, int32_t n3,
                     uint32_t u4, uint32_t u5);     // 1417af250
    void     Slot350(uint32_t u2);                  // 1417af270
    void     Slot358(uint32_t u2, void* p3);        // 1417af2b0
    void     Slot360(uint32_t u2);                  // 1417af2d0
    void     Slot368(void);                         // 1417afb00
    uint8_t  Slot370(uint32_t u2, void* p3);        // 1417af2f0

    // ---- D113 wave 18 (TRUE offsets +0x378..+0x470) ----
    uint32_t Slot378(uint32_t u2);                 // 1417af310
    void     Slot380(uint32_t u2);                 // 1417af330
    void     Slot388(uint32_t u2, uint32_t u3,
                     uint32_t u4);                 // 1417af350
    void     Slot390(void);                        // 1417af390
    void     Slot398(uint32_t u2);                 // 1417af3b0
    void     Slot3a0(int32_t n2, void* p3);        // 1417af3d0
    void     Slot3a8(uint32_t u2);                 // 1417af410
    void     Slot3b0(int32_t n2, int64_t l3,
                     int64_t l4);                   // 1417af430
    void     Slot3b8(void);                        // 1417af460
    void     Slot3c8(uint32_t u2, uint32_t u3,
                     int64_t l4, int64_t l5);       // 1417afa70
    void     Slot3d0(uint32_t u2, uint32_t u3);    // 1417afaa0
    uint64_t Slot3d8(uint32_t u2, uint32_t u3);    // 1417afac0
    void     Slot3e0(uint32_t u2, uint32_t u3,
                     uint32_t u4);                  // 1417afae0
    void     Slot3e8(uint32_t u2, uint32_t u3,
                     const char* pc4, uint32_t u5,
                     int16_t n6, int16_t n7,
                     int16_t n8, int16_t n9,
                     int16_t n10, int16_t n11);    // 1417afba0
    void     Slot3f0(uint32_t u2, uint32_t u3);    // 1417afc40
    void     Slot3f8(uint32_t u2, uint32_t u3,
                     uint32_t u4);                  // 1417b8620
    void     Slot400(uint32_t u2);                 // 1417afc90

    // ---- D114a wave 19 (TRUE offsets +0x560..+0x678) ----
    void Slot560(uint32_t u2, uint32_t u3,
                 uint8_t b4, uint8_t b5,
                 const char* psz6,
                 uint32_t u7);     // 1417affa0
    void Slot568(uint32_t u2, uint32_t u3,
                 uint8_t b4, uint8_t b5,
                 const char* psz6,
                 uint32_t u7);     // 1417b0100
    void Slot570(uint32_t u2, uint32_t u3,
                 uint32_t u4, const char* psz5,
                 const char* psz6); // 1417b0200
    bool Slot588(uint32_t u2,
                 uint32_t u3);      // 1417b27b0
    void Slot590(uint32_t u2,
                 uint32_t u3);      // 1417b28a0
    void Slot598(uint32_t u2,
                 uint32_t u3);      // 1417b28b0
    bool Slot5a0(uint32_t u2,
                 int32_t n3);       // 1417b5830
    bool Slot5a8(uint32_t u2,
                 int32_t n3);       // 1417b5880
    void Slot5b8(uint32_t u2,
                 uint32_t u3);      // 1417b0810
    void Slot5c8(int32_t n2, uint32_t u3,
                 int32_t n4);      // 1417b0890
    void Slot5d0(uint32_t u2, uint32_t u3,
                 uint32_t u4);     // 1417c0860
    void Slot5f0(uint32_t u2,
                 uint8_t b3);      // 1417c0d10
    void Slot5e8(uint32_t u2);      // 1417bfdd0
    bool Slot608(uint32_t u2, uint32_t u3,
                 uint32_t u4);     // 1417b2a30
    void Slot5b0(uint32_t u2);     // 1417b8d90
    void Slot5e0(uint32_t u2);     // 1417bfa40
    bool Slot580(uint32_t u2, uint32_t u3,
                 uint32_t u4);     // 1417b2e30
    void Slot5c0(uint32_t u2, uint32_t u3,
                 uint32_t u4);     // 1417bd730
    void Slot578(uint32_t u2);     // 1417bdb20
    bool Slot610(uint32_t u2, uint32_t u3,
                 uint32_t u4, uint32_t u5,
                 uint32_t u6, uint32_t u7);   // 1417c1a90
    void Slot5d8(int32_t n2,
                 uint32_t u3);      // 1417b1e00
    void Slot5f8(uint32_t u2, void* p3,
                 uint64_t l4);      // 1417b1450
    bool Slot600(uint32_t u2);       // 1417b1380
    void Slot618(uint32_t u2, uint32_t u3,
                 const char* psz4); // 1417b31c0
    void Slot620(uint16_t u2);      // 1417b3a50
    void Slot628(uint16_t u2);      // 1417b3a60
    void Slot630(uint32_t u2);      // 1417b2980
    void Slot638(uint32_t u2);      // 1417b2990
    void Slot640(uint32_t u2, uint32_t u3,
                 int32_t n4);      // 1417b29a0
    uint64_t Slot648(int32_t n2,
                     uint32_t u3);  // 1417b28c0
    void Slot650(uint32_t u2, uint32_t u3,
                 uint32_t u4, uint16_t u5,
                 uint16_t u6);      // 1417b5760
    void Slot658(uint16_t u2,
                 uint32_t* pu3);    // 1417b5730
    void Slot660(uint16_t u2,
                 uint32_t* pu3);    // 1417b5740
    void Slot668(void);             // 1417b5670
    void Slot670(uint32_t u2, int32_t n3,
                 void*** ppp4);     // 1417b56b0
    void Slot678(void);             // 1417b56c0

};
}


  // namespace syndicate

#endif  // MODULES_SYNDICATE_SRC_SYNDECATELOGIC_H
