// msgleagueopt.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueopt.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLeagueSalary.h"
namespace syndicate {

// 0x1417d7260 — class vftable, CStringPacker dtor at +0x410, base vftable
void* CMsgLeagueOpt::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    g_fnCStrPackerDtor((unsigned char*)self + kOffPacker);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d68d0 — verbatim body in SyndicateLeagueOpt.cpp
void CMsgLeagueOpt::Process(void* self, uint32_t idActor) {
    LeagueOptProcess(self, idActor);
}

// 0x1417d6700 — slot 5: a null buffer fails without touching the base
bool CMsgLeagueOpt::CreateBufMsg(void* self, char* pData, uint16_t uType) {
    if (pData == nullptr) return false;
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kBufMsgType;
}

}  // namespace syndicate
