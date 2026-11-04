// ============================================================================
// cqbase_d52 — the attribute send path: the two guarded entries and the announce builder.
//   The header offsets below (+0 total, +2 type 0x453, +4 action, +8 parameter) and the
//   +0x90 lookup base come straight from the disassembly of the three bodies.
// ============================================================================
#include "modules/syndicate/src/synattrsend.h"
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include "modules/syndicate/src/msg/cmsgbase.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nLogs = 0;
void LogHook(const char*, ...) { ++g_nLogs; }

int g_nInits = 0;
void InitHook(void*) { ++g_nInits; }

uint32_t GetIdHook(void* p) { return *(uint32_t*)p + 7; }
void* FindByIdHook(void* pUnder, uint32_t uId) { return (void*)((uint8_t*)pUnder + 0x40 + uId); }

void* g_pLastCoreOwner = nullptr;
void* g_pLastCoreUser = nullptr;
void* g_pLastCoreInfo = nullptr;
uint32_t g_uLastCoreId = 0;
char g_cLastCoreFlag = 0;
int g_nCores = 0;
void CoreHook(void* pOwner, void* pUser, void* pInfo, uint32_t uId, char cFlag) {
    ++g_nCores;
    g_pLastCoreOwner = pOwner; g_pLastCoreUser = pUser; g_pLastCoreInfo = pInfo;
    g_uLastCoreId = uId; g_cLastCoreFlag = cFlag;
}

std::string g_strAdded;
std::string g_strInitSeen;
void* g_pAddStringPacker = nullptr;
void AddStringHook(void* pPacker, const char* psz) {
    g_pAddStringPacker = pPacker;
    g_strAdded = psz;
}
uint32_t PackerSizeHook(void* p) { return (uint32_t)g_strAdded.size() + (p ? 0 : 0); }

// a message: the base CMsg with the payload pointer at +0x408 and the packer at +0x410
struct Msg {
    std::vector<uint8_t> buf;
    uint8_t aHeader[0x20];
    uint8_t aPacker[0x20];
    Msg() : buf(0x440, 0) {
        std::memset(aHeader, 0, sizeof(aHeader));   // stack members are not zeroed for us
        std::memset(aPacker, 0, sizeof(aPacker));
        *(void**)(buf.data() + 0x408) = aHeader;
        *(void**)(buf.data() + 0x410) = (void*)0x1;
    }
    uint8_t* H() { return aHeader; }
};

}  // namespace

int main() {
    syndicate::g_fn_141823030 = (decltype(syndicate::g_fn_141823030))&LogHook;
    syndicate::g_fnM83MsgInit = (decltype(syndicate::g_fnM83MsgInit))&InitHook;
    syndicate::g_pfnCMsgInit = (decltype(syndicate::g_pfnCMsgInit))&InitHook;
    syndicate::g_fnM83AddString = (decltype(syndicate::g_fnM83AddString))&AddStringHook;
    g_fnSynMsgPackerSize = &PackerSizeHook;
    g_fnSynAttrInsertCore = &CoreHook;
    syndicate::g_fnA84GetId = (decltype(syndicate::g_fnA84GetId))&GetIdHook;
    syndicate::g_fnA84FindUserById = (decltype(syndicate::g_fnA84FindUserById))&FindByIdHook;

    // ---- the announce builder writes the exact header the binary writes
    {
        Msg m;
        CHECK(SynMsgSyndicateAnnounce(m.buf.data(), 0x1b, 0x11223344, "hello"));
        CHECK(*(uint16_t*)(m.H() + 4) == 0x1b);
        CHECK(*(uint32_t*)(m.H() + 8) == 0x11223344);
        CHECK(*(uint16_t*)(m.H() + 2) == 0x453);
        CHECK(*(uint16_t*)(m.H() + 0) == (uint16_t)(g_strAdded.size() + 0x1b));
        CHECK(g_nInits == 1);                    // CMsg::Init ran once
        CHECK(g_strAdded == "hello");
        CHECK(g_pAddStringPacker == (void*)(m.buf.data() + 0x410));   // the packer, not the header
    }

    // ---- the two refusals: no action, then no text
    {
        Msg m;
        g_nLogs = 0;
        CHECK(!SynMsgSyndicateAnnounce(m.buf.data(), 0, 1, "x"));
        CHECK(g_nLogs == 1);
        CHECK(!SynMsgSyndicateAnnounce(m.buf.data(), 1, 1, nullptr));
        CHECK(g_nLogs == 2);
        CHECK(*(uint16_t*)(m.H() + 2) == 0);     // nothing was written
    }

    // ---- the by-user entry: the id comes from the attribute pointer
    {
        uint8_t aOwner[0x100]; std::memset(aOwner, 0, sizeof(aOwner));
        uint8_t aUser[8]; std::memset(aUser, 0, sizeof(aUser));
        uint32_t aInfo = 0x30;
        g_nCores = 0; g_nLogs = 0;
        SynAttrInsertByUser(aOwner, aUser, &aInfo, 1);
        CHECK(g_nCores == 1);
        CHECK(g_uLastCoreId == 0x37);            // 0x30 + 7 through the seam
        CHECK(g_pLastCoreInfo == &aInfo);
        CHECK(g_pLastCoreUser == aUser);
        CHECK(g_pLastCoreOwner == aOwner);
        CHECK(g_cLastCoreFlag == 1);

        // the two guards: no user, then no attribute pointer
        SynAttrInsertByUser(aOwner, nullptr, &aInfo, 0);
        CHECK(g_nLogs == 1);
        SynAttrInsertByUser(aOwner, aUser, nullptr, 0);
        CHECK(g_nLogs == 2);
        CHECK(g_nCores == 1);                    // neither reached the core
    }

    // ---- the by-id entry: the lookup starts at owner + 0x90
    {
        uint8_t aOwner[0x100]; std::memset(aOwner, 0, sizeof(aOwner));
        uint8_t aUser[8]; std::memset(aUser, 0, sizeof(aUser));
        uint8_t aUnder[0x80]; std::memset(aUnder, 0, sizeof(aUnder));
        *(void**)(aOwner + 0x90) = aUnder;
        g_nCores = 0; g_nLogs = 0;
        SynAttrInsertById(aOwner, aUser, 5, 1);
        CHECK(g_nCores == 1);
        CHECK(g_uLastCoreId == 5);
        CHECK(g_pLastCoreInfo == (void*)(aUnder + 0x40 + 5));   // the +0x90 base was used
        CHECK(g_cLastCoreFlag == 1);

        SynAttrInsertById(aOwner, nullptr, 5, 0);
        CHECK(g_nLogs == 1);
        CHECK(g_nCores == 1);
    }

    std::printf("SYNDICATE_D52_OK: the attribute send path, %d checks\n", g_nChecks);
    return 0;
}
