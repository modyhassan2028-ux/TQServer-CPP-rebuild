// The class batch: 8 complete units, 14002ba80 / 14003a8e0 / 14003ffb0
// / 140073740 / 14024e750 / 14045c0c0 / 1404ddb30 / 1405935c0.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "serverstatusmonitor.h"
#include "chatgamemap.h"
#include "gmtalkmgr.h"
#include "connectuser.h"
#include "auramgr.h"
#include "crossmsgleaguelist.h"
#include "msgroulettebet.h"
#include "boothactor.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static int s_check = 0, s_logf = 0, s_begin = 0;
static int s_ready = 1; static uintptr_t s_hRet = 0x1234;
static int TReady() { return s_ready; }
static void TCheck() { s_check++; }
static unsigned TWorker(void*) { return 0; }
static uintptr_t TBegin(void*, unsigned, unsigned (*)(void*), void*, unsigned,
                        unsigned* id) { s_begin++; if (id) *id = 7; return s_hRet; }
static void TLogStart(const char*, int) { s_logf++; }
int main() {
    SECT("cls1 CServerStatusMonitor::StartWorkerThread");
    CServerStatusMonitor::Seams s1;
    s1.GlobalReady = TReady; s1.CheckFail = TCheck;
    s1.BeginThreadEx = TBegin; s1.LogStartFail = TLogStart;
    s1.WorkerProc = TWorker;
    CServerStatusMonitor mon;
    mon.m_pObj = (void*)0xAA;
    s_ready = 0; s_check = s_begin = 0;
    CHECK(mon.StartWorkerThread(s1) == 0, "no global -> 0");
    CHECK(s_check == 1 && s_begin == 0, "check log, no thread");
    s_ready = 1; s_check = 0; mon.m_pObj = nullptr;
    CHECK(mon.StartWorkerThread(s1) == 0, "no object -> 0");
    CHECK(s_check == 1 && s_begin == 0, "check log, no thread");
    mon.m_pObj = (void*)0xAA; s_hRet = 0x1234; s_begin = 0; s_logf = 0;
    CHECK(mon.StartWorkerThread(s1) == 0x1234, "thread handle returned");
    CHECK(mon.m_hThread == 0x1234, "stored at +0x68");
    CHECK(s_begin == 1 && s_logf == 0, "one begin, no failure log");
    s_hRet = 0; s_logf = 0;
    CHECK(mon.StartWorkerThread(s1) == 0, "begin failure -> 0");
    CHECK(mon.m_hThread == 0, "+0x68 holds the null handle");
    CHECK(s_logf == 1, "the %s,%d failure literal logged");
    SECT("cls2 CChatGameBlock::QueryBlock");
    static int s_rowArg = -1, s_colArg = -1;
    static void* s_rowRet = (void*)0x10; static void* s_colRet = (void*)0x20;
    static int s_inv = 0; static unsigned s_invMap = 0; static int s_invX = 0;
    static int s_invY = 0;
    CChatGameBlock::Seams s2;
    s2.RowGet = +[](void*, int x) -> void* { s_rowArg = x; return s_rowRet; };
    s2.ColGet = +[](void* r, int y) -> void* { s_colArg = y; return s_colRet; };
    s2.LogInvalid = +[](unsigned m, int x, int y) { s_inv++; s_invMap = m;
        s_invX = x; s_invY = y; };
    CChatGameBlock blk;
    blk.m_nWidth = 4; blk.m_nHeight = 3;
    s_rowArg = s_colArg = -1; s_inv = 0;
    CHECK(blk.QueryBlock(9, 0x24, 0x24, s2) == s_colRet, "valid -> col");
    CHECK(s_rowArg == 2, "x/0x12 = 2 for 0x24");
    CHECK(s_colArg == 2, "y/0x12 = 2 for 0x24");
    CHECK(s_inv == 0, "no invalid log");
    s_rowArg = s_colArg = -1;
    CHECK(blk.QueryBlock(9, 3 * 0x12, 0, s2) == s_colRet, "last row valid");
    CHECK(s_rowArg == 3, "row 3 of 4");
    s_inv = 0;
    CHECK(blk.QueryBlock(11, 4 * 0x12, 0, s2) == nullptr, "row == width -> 0");
    CHECK(s_inv == 1 && s_invMap == 11 && s_invX == 0x48 && s_invY == 0,
          "invalid log gets map and the ORIGINAL x");
    // RAW divides BEFORE the bounds check, and integer division
    // truncates toward zero: x = -1 and x = -0x12 both land on cx = 0
    s_inv = 0; s_rowArg = -1;
    CHECK(blk.QueryBlock(9, -1, 0, s2) == s_colRet,
          "-1 / 0x12 == 0 -> VALID (RAW truncation)");
    CHECK(s_rowArg == 0 && s_inv == 0, "row 0, no log");
    s_inv = 0; s_rowArg = -1;
    CHECK(blk.QueryBlock(9, -0x11, 0, s2) == s_colRet,
          "-0x11 / 0x12 == 0 -> valid");
    CHECK(s_rowArg == 0, "still row 0");
    CHECK(blk.QueryBlock(9, -0x12, 0, s2) == nullptr,
          "-0x12 / 0x12 == -1 -> invalid");
    CHECK(s_inv == 1 && s_invX == -0x12, "logs the raw x");
    s_inv = 0;
    CHECK(blk.QueryBlock(9, -0x13, 0, s2) == nullptr,
          "-0x13 truncates to -1 -> invalid");
    CHECK(s_inv == 1, "logged");
    s_inv = 0;
    CHECK(blk.QueryBlock(9, 0, 3 * 0x12, s2) == nullptr, "col == height -> 0");
    CHECK(s_inv == 1, "logged");
    SECT("cls3 CGMTalkMgr::CreateNew");
    static int s_ctor = 0, s_atexit = 0, s_allocN = 0; static int s_heapInit = 0;
    static char s_pool[0x18];
    static const char* s_ctorName = nullptr;
    CGMTalkMgr::Seams s3;
    s3.HeapInitOnce = +[]() -> int { return s_heapInit; };
    s3.HeapCtor = +[](const char* n) { s_ctor++; s_ctorName = n; };
    s3.AtExit = +[](void (*)()) { s_atexit++; };
    s3.AtExitTarget = +[]() {};
    s3.Alloc = +[](size_t) -> void* { s_allocN++; return s_pool; };
    s3.LogCreateFail = +[]() { s_logf++; };
    static void* vtbl[4] = {};
    s3.Vftable = vtbl;
    s_ctor = s_atexit = s_allocN = 0; s_heapInit = 0; s_logf = 0;
    CGMTalkMgr* gm = CGMTalkMgr::CreateNew(s3);
    CHECK(gm != nullptr, "created");
    CHECK(s_ctor == 1 && s_atexit == 1, "one-time heap ctor + atexit");
    CHECK(s_ctorName && std::strcmp(s_ctorName, "CGMTalkMgr") == 0,
          "the RAW heap name");
    CHECK(gm->m_Vt == vtbl, "vftable installed");
    CHECK(gm->m_a == 0 && gm->m_b == 0 && gm->m_c == 0 && gm->m_d == 0,
          "the four dwords zeroed");
    s_heapInit = 1; s_ctor = s_atexit = 0;
    CHECK(CGMTalkMgr::CreateNew(s3) != nullptr, "second create");
    CHECK(s_ctor == 0 && s_atexit == 0, "heap ctor runs only once");
    s3.Alloc = +[](size_t) -> void* { return nullptr; };
    s_logf = 0;
    CHECK(CGMTalkMgr::CreateNew(s3) == nullptr, "alloc failure -> null");
    CHECK(s_logf == 1, "CGMTalkMgr::CreateNew fail logged");
    SECT("cls4 CConnectUser::SetType");
    static uint32_t s_time = 0; static int s_wrong = -1;
    CConnectUser::Seams s4;
    s4.TimeGet = +[](int) -> uint32_t { return s_time; };
    s4.LogWrongType = +[](int t) { s_wrong = t; };
    CConnectUser cu;
    cu.m_nType = 9; cu.m_nMode = 9; cu.m_nTickSec = 9;
    CHECK(cu.SetType(0, s4) == 0, "type 0 -> 0");
    CHECK(cu.m_nType == 0 && cu.m_nMode == 0 && cu.m_nTickSec == 0,
          "all three cleared");
    s_time = 45000; s_wrong = -1;
    uint64_t r = cu.SetType(1, s4);
    CHECK(cu.m_nMode == 0x14, "+0x78 = 0x14");
    CHECK(cu.m_nType == 1, "+0x34 = 1");
    CHECK(cu.m_nTickSec == 45, "+0x7c = TimeGet/1000");
    CHECK(r == (uint64_t)(uint32_t)(45000u * 0x10624dd3u),
          "RAW magic-number return preserved");
    cu.m_nMode = 0x14; cu.m_nType = 1; s_wrong = -1;
    cu.SetType(2, s4);
    CHECK(s_wrong == 2, "wrong type logged");
    CHECK(cu.m_nMode == 0x14 && cu.m_nType == 1, "fields untouched");
    SECT("cls5 CAuraMgr::SendAuraInfo");
    static int s_nullRole = 0, s_sendN = 0; static void* s_inst = nullptr;
    static void* s_sendInst = nullptr; static void* s_sendRole = nullptr;
    CAuraMgr::Seams s5;
    s5.GetInstance = +[]() -> void* { return s_inst; };
    s5.SendInfo = +[](void* i, void* r) { s_sendN++; s_sendInst = i;
        s_sendRole = r; };
    s5.LogNullRole = +[](unsigned) { s_nullRole++; };
    CAuraMgr am;
    s_nullRole = s_sendN = 0;
    am.SendAuraInfo(nullptr, s5);
    CHECK(s_nullRole == 1 && s_sendN == 0, "null role -> log only");
    s_inst = nullptr; s_sendN = 0; s_nullRole = 0;
    am.SendAuraInfo((void*)0x30, s5);
    CHECK(s_sendN == 0 && s_nullRole == 0, "no instance -> silent");
    s_inst = (void*)0x40; s_sendN = 0;
    am.SendAuraInfo((void*)0x30, s5);
    CHECK(s_sendN == 1 && s_sendInst == (void*)0x40 &&
          s_sendRole == (void*)0x30, "send(inst, role)");
    SECT("cls6 CCrossMsgLeagueList::Process");
    static int s_cf = 0, s_wrongAct = -1, s_dispN = 0;
    static void* s_dispBody = nullptr; static int s_dispA = -1;
    static void* s_mgr = (void*)0x50;
    CCrossMsgLeagueList::Seams s6;
    s6.GetMgr = +[]() -> void* { return s_mgr; };
    s6.Dispatch = +[](void*, int a, void* b) { s_dispN++; s_dispA = a;
        s_dispBody = b; };
    s6.CheckFail = +[]() { s_cf++; };
    s6.LogWrongAction = +[](unsigned a) { s_wrongAct = (int)a; };
    CCrossMsgLeagueList cl;
    s_cf = 0;
    cl.Process(s6);
    CHECK(s_cf == 1, "no message -> check fail");
    static uint8_t s_msg[16];
    memset(s_msg, 0, sizeof s_msg);
    cl.m_pMsg = s_msg;
    s_mgr = nullptr; s_cf = 0;
    cl.Process(s6);
    CHECK(s_cf == 1, "no manager -> check fail");
    s_mgr = (void*)0x50; s_dispN = 0; s_wrongAct = -1;
    cl.Process(s6);
    CHECK(s_dispN == 1 && s_dispA == 0, "action 0 dispatches");
    CHECK(s_dispBody == (void*)(s_msg + 8), "body at hdr+4");
    *(short*)s_msg = 3; s_dispN = 0;
    cl.Process(s6);
    CHECK(s_dispN == 0 && s_wrongAct == 3, "wrong action logged");
    *(short*)s_msg = 0;
    SECT("cls7 CMsgRoulettePlayerBet::Create");
    static int s_badSeat = -1; static uint8_t s_body[8];
    CMsgRoulettePlayerBet::Seams s7;
    s7.LogBadSeat = +[](unsigned s) { s_badSeat = (int)s; };
    CMsgRoulettePlayerBet bet;
    bet.m_pBody = s_body;
    s_badSeat = -1; memset(s_body, 0xEE, sizeof s_body);
    CHECK(bet.Create(5, s7) == 0, "seat 5 -> 0");
    CHECK(s_badSeat == 5, "bad seat logged");
    CHECK(bet.m_nMsgId == 0 && s_body[0] == 0xEE, "nothing written");
    for (uint8_t seat = 0; seat <= 4; ++seat) {
        memset(s_body, 0xEE, sizeof s_body);
        bet.m_nMsgId = 0; bet.m_nKind = 0; s_badSeat = -1;
        CHECK(bet.Create(seat, s7) == 1, "seat ok -> 1");
        CHECK(bet.m_nMsgId == 0xafa && bet.m_nKind == 2,
              "0xafa / kind 2");
        CHECK(s_body[0] == seat && s_body[1] == 0,
              "body[0]=seat, body[1]=0");
        CHECK(s_badSeat == -1, "no log");
    }
    SECT("cls8 CBoothActor::RecordEmoney");
    static int s_recN = 0, s_logFail = 0;
    static void* s_user = (void*)0x60;
    static int s_rt = 0, s_rs = 0, s_rn = 0, s_re = 0;
    CBoothActor::Seams s8;
    s8.GetUserByVt = +[](void*) -> void* { return s_user; };
    s8.RecordEmoney = +[](void*, int t, int sr, int n, int e) {
        s_recN++; s_rt = t; s_rs = sr; s_rn = n; s_re = e; };
    s8.LogFail = +[](unsigned, int, int, int) { s_logFail++; };
    CBoothActor ba;
    ba.m_pOwner = (void*)0x70;
    s_user = nullptr; s_recN = 0; s_logFail = 0;
    ba.RecordEmoney(1, 2, 3, 4, s8);
    CHECK(s_logFail == 1 && s_recN == 0, "no user -> log only");
    s_user = (void*)0x60; s_recN = 0; s_logFail = 0;
    ba.RecordEmoney(1, 2, 3, 4, s8);
    CHECK(s_recN == 1 && s_logFail == 0, "user -> record");
    CHECK(s_rt == 1 && s_rs == 2 && s_rn == 3 && s_re == 4,
          "type/source/number/extra forwarded");
    if (g_fail == 0) printf("CLASSES-OK: %d assertions\n", g_ok);
    else printf("CLASSES-FAIL\n");
    return g_fail ? 1 : 0;
}
