// ============================================================
// Analyst.dll — Unit D2 regression: CAnalyst record ops
// (Add 41200 / Get 41280 / TicksAdd 41490 / Report 1310 /
// ResetStats 1460) + the vtable slots + the 41050 log.
// Must print ANALYST-D2-OK.
// ============================================================
#include "../modules/analyst/src/TickAnalyst.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace analyst;

static uint32_t s_uTime = 0;

struct LogCap {
    std::vector<std::pair<std::string, std::string>> v;
    void Clear() { v.clear(); }
} s_log;

int main() {
    SetTimeGet([]{ return s_uTime; });
    SetLogSave([](const char* p, const char* m){
        s_log.v.push_back({p, m}); });
    s_log.Clear();
    AnalystTestResetSingleton();

    // singleton -> the concrete CAnalyst
    s_uTime = 1000;
    IAnalyst* p = AnalystSingleton();
    CAnalyst* pC = AnalystConcrete();
    assert(p != nullptr && pC != nullptr);
    assert(p == pC);            // is-a

    // ===== 1. Add 41200 =========================
    assert(pC->Add(5, 100, "ItemUse"));   // type 100
    assert(pC->Count() == 6);
    // same id again: type != 0 -> masked-false
    assert(!pC->Add(5, 100, "X"));
    // bad id
    assert(!pC->Add(0x100, 1, "X"));
    // null/empty name
    assert(!pC->Add(6, 1, nullptr));
    assert(!pC->Add(6, 1, ""));
    // the record fields
    assert(pC->m_arr[5].nType == 100);
    assert(pC->m_arr[5].strName == "ItemUse");
    assert(pC->m_arr[5].nCount == 0);
    assert(pC->m_arr[5].llMax == 0);
    assert(pC->m_arr[5].llTotal == 0);
    // gap add: count = max(count, id+1)
    assert(pC->Add(9, 200, "NpcTick"));
    assert(pC->Count() == 10);

    // ===== 2. TicksAdd 41490 (vtable +0x20) ====
    // through the interface (the dtor path)
    p->TickRecord(5, 30);
    assert(pC->m_arr[5].nCount == 1);
    assert(pC->m_arr[5].llTotal == 30);
    assert(pC->m_arr[5].llMax == 30);
    p->TickRecord(5, 10);
    assert(pC->m_arr[5].nCount == 2);
    assert(pC->m_arr[5].llTotal == 40);
    assert(pC->m_arr[5].llMax == 30);   // max kept
    p->TickRecord(5, 90);
    assert(pC->m_arr[5].llMax == 90);
    // out of range: the literal error log
    s_log.Clear();
    p->TickRecord(50, 1);
    assert(s_log.v.size() == 1);
    assert(s_log.v[0].second ==
        "TicksAdd failed for index 50");
    // negative id
    s_log.Clear();
    p->TickRecord(-1, 1);
    assert(s_log.v.size() == 1);
    // id inside 0x100 but beyond count -> error
    s_log.Clear();
    p->TickRecord(7, 1);   // 7 < count 10 but type 0
    // NOTE: bounds use the COUNT (10), so id 7 is in
    // range and adds into an untyped record (verbatim)
    assert(s_log.v.empty());

    // ===== 3. Get 41280 ==========================
    {
        int64_t t = -1, mx = -1; int32_t c = -1;
        assert(pC->Get(5, &t, &mx, &c));
        assert(t == 130 && mx == 90 && c == 3);
        // out of range
        assert(!pC->Get(50, &t, &mx, &c));
        assert(!pC->Get((uint32_t)-1, &t, &mx, &c));
    }

    // ===== 4. the CTickAnalyst dtor dispatch ====
    // (end-to-end through the singleton)
    s_uTime = 2000;
    AnalystSetTickZero();
    s_uTime = 2100;         // +100 ticks
    {
        CTickAnalyst t(5);  // start = 100
        s_uTime = 2130;     // dtor: finish = 130, used 30
    }
    assert(pC->m_arr[5].nCount == 4);
    assert(pC->m_arr[5].llTotal == 160);
    assert(pC->m_arr[5].llMax == 90);

    // ===== 5. Report 1310 ========================
    s_log.Clear();
    pC->Report("logs/an1.log");   // contains '/'
    assert(s_log.v.size() == 2);  // ids 5 and 9 typed
    assert(s_log.v[0].first == "logs/an1.log");
    // verbatim format pieces
    assert(s_log.v[0].second.rfind("ItemUse, cnt=", 0) == 0);
    assert(s_log.v[0].second.find(", avg=")
        != std::string::npos);
    assert(s_log.v[0].second.find("max=90ms")
        != std::string::npos);
    // the avg: 160/4 = 40.00
    assert(s_log.v[0].second.find("avg=40.00ms")
        != std::string::npos);
    assert(s_log.v[1].second.rfind("NpcTick, ", 0) == 0);
    assert(s_log.v[1].second.find("cnt=0")
        != std::string::npos);
    // path WITHOUT '/': the 41050 find npos -> no log
    s_log.Clear();
    pC->Report("nologfile");
    assert(s_log.v.empty());

    // ===== 6. ResetStats 1460 ===================
    pC->ResetStats();
    assert(pC->m_arr[5].nCount == 0);
    assert(pC->m_arr[5].llMax == 0);
    assert(pC->m_arr[5].llTotal == 0);
    // type + name KEPT (the verbatim reset scope)
    assert(pC->m_arr[5].nType == 100);
    assert(pC->m_arr[5].strName == "ItemUse");
    assert(pC->m_arr[9].nType == 200);
    assert(pC->m_arr[9].strName == "NpcTick");
    // count NOT touched by the reset
    assert(pC->Count() == 10);

    // ===== 7. the vtable slots ==================
    // +0x10 TickEcho: identity, no side effect
    s_log.Clear();
    p->TickEcho(5);
    assert(s_log.v.empty());
    // +0x18 TickLog: the literal analyst.cpp line via
    // 41050 then the tick-zero reset
    s_uTime = 5000;
    AnalystSetTickZero();
    s_uTime = 5100;
    s_log.Clear();
    p->TickLog("logs/an2.log", nullptr, nullptr);
    assert(s_log.v.size() == 1);
    assert(s_log.v[0].first == "logs/an2.log");
    assert(s_log.v[0].second ==
        "f:\\version\\cqserver-78.0.11-1204\\"
        "analyst\\analyst.cpp");
    // the 41650 reset ran: zero = 5100 now
    assert(g_dwTickZero490a4 == 5100);
    assert(AnalystNow64() == 0);
    // path without '/' -> no log (41050 npos)
    s_log.Clear();
    p->TickLog("nolog", nullptr, nullptr);
    assert(s_log.v.empty());
    // the tick zero STILL reset (verbatim: the reset
    // runs AFTER the log call regardless)
    s_uTime = 5200;
    AnalystSetTickZero(); s_uTime = 5250;
    p->TickLog("nolog", nullptr, nullptr);
    assert(g_dwTickZero490a4 == 5250);

    AnalystTestResetSingleton();
    printf("ANALYST-D2-OK: CAnalyst verbatim — Add 140a41200 "
           "(the rec+0x00 type gate, name at +0x18, count=max"
           "(count,id+1)), TicksAdd 140a41490 (vtable+0x20: "
           "++count at rec+0x04, total+= at +0x10, max at "
           "+0x08, the literal 'TicksAdd failed for index "
           "%d' bounds log), Get 140a41280, Report 140a41310 "
           "with the literal '%s, cnt=%ld, tot=%dms, "
           "avg=%.2fms, max=%dms' + the 41050 '/' find npos "
           "skip, ResetStats 140a41460 (only +0x04/+0x08/"
           "+0x10, type+name kept), TickEcho 140a412e0, "
           "TickLog 140a412f0 (the literal analyst.cpp line "
           "+ the 41650 zero reset AFTER), and the "
           "~CTickAnalyst->TicksAdd end-to-end dispatch\n");
    return 0;
}
