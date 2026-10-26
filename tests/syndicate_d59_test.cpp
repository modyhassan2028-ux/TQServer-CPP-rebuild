// D59 test — the CMsgLog + CMsgSynChgDomName
// Process handlers (1417d97c0 / 1417daee0).
#include "Exe/Dll/Syndicate/Port/SyndicateMsgProcess.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cstdio>
#include <cassert>
#include <cstring>
using namespace syndicate;

// ---- the mock state ----
static const char* s_pLastErr;
static void MockD59LogError(const char* p, ...) {
    s_pLastErr = p;
}
static int s_nRecord, s_nRemove, s_nChk, s_nInit;
static uint32_t s_uLastActor; static void* s_pLastLogic;
static uint32_t s_uChkSyn; static char s_szChkName[32];
static int s_nTailCall;
static char s_cChkRet;
static void* s_pMgrRet = (void*)0x99;

int main() {
    // bind the seams
    g_fnGetGameMgr = []() -> void* {
        return s_pMgrRet; };
    g_fnLogRecord = [](void* p, uint32_t u) {
        s_nRecord++; s_pLastLogic = p;
        s_uLastActor = u; };
    g_fnLogRemove = [](void* p, uint32_t u) {
        s_nRemove++; s_pLastLogic = p;
        s_uLastActor = u; };
    g_fnChgDomCheck = [](void* p, uint32_t u,
        uint32_t uSyn, char* pName) -> uint64_t {
        s_nChk++; s_uLastActor = u;
        s_uChkSyn = uSyn; strcpy(s_szChkName, pName);
        return s_cChkRet; };
    g_fnD59LogError = MockD59LogError;
    g_fnCMsgInitThunk = [](void* p) {
        s_nInit++; (void)p; };

    // ---- D59-1: the CMsgLog dispatch ----
    {
        // the msg: PB at +0x408, the PB +8 = Type
        static uint8_t abMsg[0x410 + 8];
        static uint8_t abPb[0x10];
        *(void**)(abMsg + 0x408) = abPb;
        // Type 0 -> the record flow
        *(int*)(abPb + 8) = 0;
        MsgLogProcess(abMsg, 0x77);
        assert(s_nRecord == 1 && s_nRemove == 0);
        assert(s_pLastLogic == (void*)0x99);
        assert(s_uLastActor == 0x77);
        // Type 1 -> the removal flow
        *(int*)(abPb + 8) = 1;
        MsgLogProcess(abMsg, 0x78);
        assert(s_nRecord == 1 && s_nRemove == 1);
        assert(s_uLastActor == 0x78);
        // Type 7 -> the literal ERROR, no flows
        *(int*)(abPb + 8) = 7;
        MsgLogProcess(abMsg, 0x79);
        assert(s_nRecord == 1 && s_nRemove == 1);
        assert(s_pLastErr != nullptr);
        assert(strcmp(s_pLastErr,
            "syndicate::CMsgLog::Process(idActor), "
            "idActor:%d, Type:%d, MsgType:%d") == 0);
        printf("D59-1 the log dispatch ok\n");
    }
    // ---- D59-2: the ChgDomName Process ----
    {
        static uint8_t abMsg[0x410 + 8];
        static uint8_t abPb[0x20];
        *(void**)(abMsg + 0x408) = abPb;
        // the request PB: +4 = the syn id, +8 the name
        *(uint32_t*)(abPb + 4) = 0x1234;
        strcpy((char*)(abPb + 8), "nile");
        // the tail call (1417ac7d0): rcx=[p+8],
        // rax=[rcx], jmp [rax+8] — i.e. the object
        // at logic+8, its vt slot +8 (index 1)
        static void* apVt[4];
        apVt[1] = (void*)+[] { s_nTailCall++;
            return (uint64_t)0; };
        static void* abObj[2];
        abObj[0] = apVt;         // the object's vt
        static void* abLogic[2];
        abLogic[1] = abObj;      // *(logic+8) = obj
        s_pMgrRet = abLogic;
        s_nTailCall = 0;
        // the check returns 1 -> the reply uOk=1
        s_cChkRet = 1;
        MsgChgDomNameProcess(abMsg, 0x55);
        assert(s_nChk == 1);
        assert(s_uChkSyn == 0x1234);
        assert(strcmp(s_szChkName, "nile") == 0);
        assert(s_nInit == 1);   // the reply Init
        assert(s_nTailCall == 1);
        // the reply writes: +0x18=1, +2=0x837, +0=0x1c
        assert(*(uint16_t*)(abPb + 0x18) == 1);
        assert(*(uint16_t*)(abPb + 0x02) == 0x837);
        assert(*(uint16_t*)(abPb + 0x00) == 0x1c);
        // the check returns 0 -> uOk=0
        s_cChkRet = 0;
        MsgChgDomNameProcess(abMsg, 0x56);
        assert(*(uint16_t*)(abPb + 0x18) == 0);
        assert(s_nTailCall == 2);
        printf("D59-2 the chg-dom-name flow ok\n");
    }
    printf("SYNDICATE_D59_OK: the msg process\n");
    return 0;
}
