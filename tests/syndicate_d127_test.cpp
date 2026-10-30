// D127 — CMsgLeagueOpt, CMsgLeagueRobOpt, CMsgLeagueToken
// (the original modules/syndicate/src/msg/ paths)
#include <string>
#include "modules/syndicate/src/msg/msgleagueopt.h"
#include "modules/syndicate/src/msg/msgleaguerobopt.h"
#include "modules/syndicate/src/msg/msgleaguetoken.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLeagueSalary.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptClass.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include "modules/syndicate/src/msg/msgleagueroboptpb.h"
#include "modules/syndicate/src/msg/msgleaguetokenpb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nPacker, s_nOptLog, s_nParse, s_nLog;
static bool s_bParse, s_bInit;
static uintptr_t s_uFmt;
static char s_strCopy[64];
static bool s_bStrNull = true;
static unsigned char ab[0x460];
static char bufData[0x40];

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { return true; };
    g_pfnPbDelArray = [](void*) {};   // the PB array free seam (msgleagueroboptpb.h decl)
    g_fnCStrPackerDtor = [](void* p) {
        s_nPacker++;
        assert(p == ab + CMsgLeagueOpt::kOffPacker); };
    g_fnLeagueOptLogError = [](void*, const char*, const char*,
                               const char*) { s_nOptLog++; };
    g_fnPbParseFromArray = [](void* pSlot, const void*, int nLen) -> char {
        s_nParse++;
        assert(nLen == 8);
        (void)pSlot;
        return s_bParse ? 1 : 0; };
    g_fnPbVf20IsInit = [](void*) -> bool { return s_bInit; };
    g_fnPbVf28InitErr = [](void*, void* pOut) -> void* {
        new (pOut) std::string("bad field");
        return pOut; };
    g_fnLogRobOptErr = [](const void* pFmt, const char* pStr) {
        s_nLog++; s_uFmt = (uintptr_t)pFmt;
        s_bStrNull = (pStr == nullptr);
        if (pStr) { std::strncpy(s_strCopy, pStr, 63);
                    s_strCopy[63] = '\0'; }
        else s_strCopy[0] = '\0'; };

    // ---------- CMsgLeagueOpt: CreateBufMsg type 0xa3e, 6-slot table
    memset(ab, 0, sizeof ab);
    assert(CMsgLeagueOpt::CreateBufMsg(ab, nullptr, 3) == false);
    *(uint16_t*)(ab + CMsgLeagueOpt::kOffMsgType) = 0xa3e;
    assert(CMsgLeagueOpt::CreateBufMsg(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgLeagueOpt::kOffMsgType) = 0xa3f;
    assert(CMsgLeagueOpt::CreateBufMsg(ab, (char*)1, 3) == false);
    s_nOptLog = 0;
    CMsgLeagueOpt::Process(ab, 21);        // +0x408 == 0 -> the CHECK log
    assert(s_nOptLog >= 1);
    memset(ab, 0, sizeof ab);
    CMsgLeagueOpt::DeleteDtor(ab, 0);
    assert(s_nPacker == 1 && *(uintptr_t*)ab == CMsgLeagueOpt::kBaseCMsgVft);

    // ---------- CMsgLeagueRobOpt: type 0xa52 + ParseFromArray(+0x408)
    for (int pass = 0; pass < 2; ++pass) {
        memset(ab, 0, sizeof ab);
        *(void**)(ab + CMsgLeagueRobOpt::kOffPayload) = (void*)(ab + 0x100);
        *(uint16_t*)(ab + CMsgLeagueRobOpt::kOffMsgType) = 0xa52;
        assert(CMsgLeagueRobOpt::Create(ab, nullptr, 12) == false);
        *(uint16_t*)(ab + CMsgLeagueRobOpt::kOffMsgType) = 0xa53;
        assert(CMsgLeagueRobOpt::Create(ab, bufData, 12) == false);
        *(uint16_t*)(ab + CMsgLeagueRobOpt::kOffMsgType) = 0xa52;
        s_nParse = 0; s_nLog = 0; s_uFmt = 0; s_bStrNull = true; s_strCopy[0] = 0; s_bStrNull = true; s_strCopy[0] = 0;
        s_bParse = false; s_bInit = (pass == 1);
        assert(CMsgLeagueRobOpt::Create(ab, bufData, 12) == false);
        assert(s_nParse == 1 && s_nLog == 1);
        if (pass == 0) {                    // not initialized -> the %s form
            assert(s_uFmt == CMsgLeagueRobOpt::kFmtParseErr);
            assert(!s_bStrNull && std::string(s_strCopy) == "bad field");
        } else {                            // initialized -> the short form
            assert(s_uFmt == CMsgLeagueRobOpt::kFmtParseFail);
            assert(s_bStrNull);
        }
        s_bParse = true;
        assert(CMsgLeagueRobOpt::Create(ab, bufData, 12) == true);
    }
    memset(ab, 0, sizeof ab);
    CMsgLeagueRobOpt::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgLeagueRobOpt::kBaseCMsgVft);

    // ---------- CMsgLeagueToken: type 0xa49, the log forms are mirrored
    for (int pass = 0; pass < 2; ++pass) {
        memset(ab, 0, sizeof ab);
        *(void**)(ab + CMsgLeagueToken::kOffPayload) = (void*)(ab + 0x100);
        *(uint16_t*)(ab + CMsgLeagueToken::kOffMsgType) = 0xa49;
        assert(CMsgLeagueToken::Create(ab, nullptr, 12) == false);
        *(uint16_t*)(ab + CMsgLeagueToken::kOffMsgType) = 0xa4a;
        assert(CMsgLeagueToken::Create(ab, bufData, 12) == false);
        *(uint16_t*)(ab + CMsgLeagueToken::kOffMsgType) = 0xa49;
        s_nLog = 0; s_uFmt = 0; s_bStrNull = true; s_strCopy[0] = 0;
        s_bParse = false; s_bInit = (pass == 1);
        assert(CMsgLeagueToken::Create(ab, bufData, 12) == false);
        assert(s_nLog == 1);
        if (pass == 1) {                    // initialized -> the short form
            assert(s_uFmt == CMsgLeagueToken::kFmtParseFail);
        } else {                            // not initialized -> %s form
            assert(s_uFmt == CMsgLeagueToken::kFmtParseErr);
            assert(!s_bStrNull && std::string(s_strCopy) == "bad field");
        }
    }
    s_bParse = true;
    assert(CMsgLeagueToken::Create(ab, bufData, 12) == true);
    memset(ab, 0, sizeof ab);
    CMsgLeagueToken::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgLeagueToken::kBaseCMsgVft);

    printf("SYNDICATE_D127_OK: LeagueOpt + LeagueRobOpt + LeagueToken, "
           "16/16 slots\n");
    return 0;
}
