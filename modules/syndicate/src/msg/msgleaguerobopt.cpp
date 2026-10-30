// msgleaguerobopt.cpp — RAW Syndicate.dll v6159
#include <string>
#include "modules/syndicate/src/msg/msgleaguerobopt.h"
#include "modules/syndicate/src/msg/msgleagueroboptpb.h"
#include "modules/syndicate/src/SyndicateLeagueRobOpt.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptClass.h"
namespace syndicate {

// 0x1417d86a0 — class vftable, PB dtor at +0x408, base vftable, delete
void* CMsgLeagueRobOpt::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    CMsgLeagueRobOptPB::BaseDtor((unsigned char*)self + kOffPayload,
                                 uFlag, 0, 0);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d8420 — type 0xa52, then ParseFromArray(pb slot, pData + 4, len - 4)
bool CMsgLeagueRobOpt::Create(void* self, char* pData, uint16_t uType) {
    if (pData == nullptr) return false;
    if (*reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
        != kMsgType) {
        return false;
    }
    void* pSlot = (unsigned char*)self + kOffPayload;
    if (!g_fnPbParseFromArray(pSlot, pData + 4,
                              static_cast<int>(uType) - 4)) {
        void* pPb = *reinterpret_cast<void**>(pSlot);
        if (!g_fnPbVf20IsInit(pPb)) {
            std::string strErr;
            void* pRet = g_fnPbVf28InitErr(pPb, &strErr);
            g_fnLogRobOptErr(reinterpret_cast<const void*>(kFmtParseErr),
                             reinterpret_cast<std::string*>(pRet)->c_str());
        } else {
            g_fnLogRobOptErr(reinterpret_cast<const void*>(kFmtParseFail),
                             nullptr);
        }
        return false;
    }
    return true;
}

// 0x1417d8920 — verbatim body in SyndicateLeagueRobOpt.cpp
void CMsgLeagueRobOpt::Process(void* self, uint32_t idActor) {
    RobOptProcess(self, idActor);
}

}  // namespace syndicate
