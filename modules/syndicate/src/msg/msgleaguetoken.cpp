// msgleaguetoken.cpp — RAW Syndicate.dll v6159
#include <string>
#include "modules/syndicate/src/msg/msgleaguetoken.h"
#include "modules/syndicate/src/msg/msgleaguetokenpb.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptClass.h"
namespace syndicate {

// 0x1417d93b0 — class vftable, PB dtor at +0x408, base vftable, delete
void* CMsgLeagueToken::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    CMsgLeagueTokenPB::BaseDtor((unsigned char*)self + kOffPayload);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d9090 — type 0xa49, then ParseFromArray(pb slot, pData + 4, len - 4)
bool CMsgLeagueToken::Create(void* self, char* pData, uint16_t uType) {
    if (pData == nullptr) return false;
    if (*reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
        != kMsgType) {
        return false;
    }
    void* pSlot = (unsigned char*)self + kOffPayload;
    if (!g_fnPbParseFromArray(pSlot, pData + 4,
                              static_cast<int>(uType) - 4)) {
        void* pPb = *reinterpret_cast<void**>(pSlot);
        if (g_fnPbVf20IsInit(pPb)) {
            g_fnLogRobOptErr(reinterpret_cast<const void*>(kFmtParseFail),
                             nullptr);
        } else {
            std::string strErr;
            void* pRet = g_fnPbVf28InitErr(pPb, &strErr);
            g_fnLogRobOptErr(reinterpret_cast<const void*>(kFmtParseErr),
                             reinterpret_cast<std::string*>(pRet)->c_str());
        }
        return false;
    }
    return true;
}

// 0x1417d92d0 — verbatim body in SyndicateMsgProcess2.cpp
void CMsgLeagueToken::Process(void* self, uint32_t idActor) {
    MsgLeagueTokenProcess(self, idActor);
}

} // namespace syndicate
