// msgsynctors.cpp — the seventeen tq::CMsg constructors the Syndicate module builds in its own
// constructor (0x14177ead0 puts them at fixed offsets). Every one of them is the same handful of
// instructions, so they are collected here with the source file each belongs to recorded per body
// rather than split into seventeen files of one function each.
//
// The shape they share, in the original's order — note the base table is written, then Init runs, and
// only then is the class table installed, so a virtual call during Init still reaches tq::CMsg:
//
//   *(void**)this = tq::CMsg::vftable;     0x14182e368, the same in all seventeen
//   tq::CMsg::Init(this);                  0x1417e8016, called a second time after the class table
//   *(void**)this = <class>::vftable;
//   *(void**)(this + 0x408) = this + 8;
//
// Three of them do more: the CMsgSyndicate, CMsgSynDomain and CMsgLeagueOpt constructors put a
// CStringPacker at +0x410 and point its buffer into the message body, and the CMsgLeagueRobOpt and
// CMsgLeagueToken constructors hand +0x408 to a reset instead of storing this+8 there.
#include "modules/syndicate/src/msg/msgseams.h"
#include "modules/syndicate/src/msg/msgsynctors.h"
#include <cstdint>

namespace syndicate {

using u8 = std::uint8_t;

// 0x1417d9710 — msgsyndicate.cpp  (CMsgLog, no CHECK of its own)
void* CMsgLog_Ctor_1417d9710(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E4A0ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417d8390 — msgleaguerobopt.cpp (stringless)
void* CMsgLeagueRobOpt_Ctor_1417d8390(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183CC78ULL;
    if (g_fn_1417f05f0 != nullptr) g_fn_1417f05f0(static_cast<u8*>(self) + 0x408);
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    return self;
}

// 0x1417d9000 — msgleaguetoken.cpp
void* CMsgLeagueToken_Ctor_1417d9000(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183CFA0ULL;
    if (g_fn_1417f1600 != nullptr) g_fn_1417f1600(static_cast<u8*>(self) + 0x408);
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    return self;
}

// 0x1417d9e60 — msgselfsynmemawardrank.cpp (stringless)
void* CMsgSelfSynMemAwardRank_Ctor_1417d9e60(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183D558ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417da860 — msgsynattrinfo.cpp (stringless)
void* CMsgSynAttrInfo_Ctor_1417da860(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183D768ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417dac30 — msgsynbaseproffer.cpp
void* CMsgSynBaseProffer_Ctor_1417dac30(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183D888ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417dae10 — msgsynchgdomname.cpp (stringless)
void* CMsgSynChgDomName_Ctor_1417dae10(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E520ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417db2b0 — msgsyndicate.cpp
void* CMsgSyndicate_Ctor_1417db2b0(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183DC10ULL;
    if (g_pfnCStringPackerCtor != nullptr) g_pfnCStringPackerCtor(static_cast<u8*>(self) + 0x410);
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    if (g_pfnCStringPackerSetBuf != nullptr)
        g_pfnCStringPackerSetBuf(static_cast<u8*>(self) + 0x410,
                                reinterpret_cast<char*>(static_cast<u8*>(self) + 0x20), 0x3E5u, true);
    return self;
}

// 0x1417dca60 — msgsyndomain.cpp
void* CMsgSynDomain_Ctor_1417dca60(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183DE00ULL;
    if (g_pfnCStringPackerCtor != nullptr) g_pfnCStringPackerCtor(static_cast<u8*>(self) + 0x410);
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    if (g_pfnCStringPackerSetBuf != nullptr)
        g_pfnCStringPackerSetBuf(static_cast<u8*>(self) + 0x410,
                                reinterpret_cast<char*>(static_cast<u8*>(self) + 0x128), 0x2D9u, true);
    return self;
}

// 0x1417dd050 — msgsynmemberinfo.cpp
void* CMsgSynMemberInfo_Ctor_1417dd050(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183DF00ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417dd230 — msgsynmemberlist.cpp
void* CMsgSynMemberList_Ctor_1417dd230(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E010ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417dd6e0 — msgsynproffer.cpp
void* CMsgSynProffer_Ctor_1417dd6e0(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E180ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417dd9f0 — msgsynprofferrank.cpp
void* CMsgSynProfferRank_Ctor_1417dd9f0(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E2B0ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417ddc60 — msgsynrecruitadvertising.cpp
void* CMsgSynRecruitAdvertising_Ctor_1417ddc60(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E3F8ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417ddf50 — msgsynrecruitadvertisinglist.cpp
void* CMsgSynRecruitAdvertisingList_Ctor_1417ddf50(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E508ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417de240 — msgsynrecruitadvertisingopt.cpp
void* CMsgSynRecruitAdvertisingOpt_Ctor_1417de240(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183E620ULL;
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    return self;
}

// 0x1417d6640 — msgleagueopt.cpp
void* CMsgLeagueOpt_Ctor_1417d6640(void* self) {
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14182E368ULL;   // tq::CMsg::vftable
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<std::uintptr_t*>(self) = 0x14183C5A8ULL;
    if (g_pfnCStringPackerCtor != nullptr) g_pfnCStringPackerCtor(static_cast<u8*>(self) + 0x410);
    if (g_pfnCMsgInit != nullptr) g_pfnCMsgInit(self);
    *reinterpret_cast<void**>(static_cast<u8*>(self) + 0x408) = static_cast<u8*>(self) + 8;
    if (g_pfnCStringPackerSetBuf != nullptr)
        g_pfnCStringPackerSetBuf(static_cast<u8*>(self) + 0x410,
                                reinterpret_cast<char*>(static_cast<u8*>(self) + 0x1A), 0x3EEu, true);
    return self;
}

}  // namespace syndicate
