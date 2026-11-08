// msgsynctors.h — the seventeen message constructors, one per class, in the order the module
// constructor 0x14177ead0 builds them.
#pragma once
namespace syndicate {
void* CMsgLog_Ctor_1417d9710(void* self);  // msgsyndicate.cpp
void* CMsgLeagueRobOpt_Ctor_1417d8390(void* self);  // msgleaguerobopt.cpp (stringless)
void* CMsgLeagueToken_Ctor_1417d9000(void* self);  // msgleaguetoken.cpp
void* CMsgSelfSynMemAwardRank_Ctor_1417d9e60(void* self);  // msgselfsynmemawardrank.cpp (stringless)
void* CMsgSynAttrInfo_Ctor_1417da860(void* self);  // msgsynattrinfo.cpp (stringless)
void* CMsgSynBaseProffer_Ctor_1417dac30(void* self);  // msgsynbaseproffer.cpp
void* CMsgSynChgDomName_Ctor_1417dae10(void* self);  // msgsynchgdomname.cpp (stringless)
void* CMsgSyndicate_Ctor_1417db2b0(void* self);  // msgsyndicate.cpp
void* CMsgSynDomain_Ctor_1417dca60(void* self);  // msgsyndomain.cpp
void* CMsgSynMemberInfo_Ctor_1417dd050(void* self);  // msgsynmemberinfo.cpp
void* CMsgSynMemberList_Ctor_1417dd230(void* self);  // msgsynmemberlist.cpp
void* CMsgSynProffer_Ctor_1417dd6e0(void* self);  // msgsynproffer.cpp
void* CMsgSynProfferRank_Ctor_1417dd9f0(void* self);  // msgsynprofferrank.cpp
void* CMsgSynRecruitAdvertising_Ctor_1417ddc60(void* self);  // msgsynrecruitadvertising.cpp
void* CMsgSynRecruitAdvertisingList_Ctor_1417ddf50(void* self);  // msgsynrecruitadvertisinglist.cpp
void* CMsgSynRecruitAdvertisingOpt_Ctor_1417de240(void* self);  // msgsynrecruitadvertisingopt.cpp
void* CMsgLeagueOpt_Ctor_1417d6640(void* self);  // msgleagueopt.cpp
}
