// Path-A wave 9f test — CCrossConfig + StartWorkerThread (raw).
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include "MsgCrossConfig.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static std::string s_sql, s_iniFile, s_iniSect, s_logs;
static std::vector<std::string> s_logV;
static int s_enable = 0; static int s_rec2 = 1030, s_rec3 = 30;
static int64_t s_count = 1; static int s_queryType = -1;
static int s_releaseN = 0, s_queryN = 0, s_vtdtorN = 0;
static int32_t s_now = 100000; static int32_t s_mktimeRet = 0;
static STmBroken s_tm; static int s_tmNull = 0, s_tmCalls = 0;
static STmBroken s_tm2;
static uintptr_t s_handle = 0x1234; static int s_btN = 0;
static void* s_btArg = nullptr; static void* s_globalSlot = nullptr;
static void** s_globalPtr = &s_globalSlot;
static int g_allocN = 0;
static char s_rsTok;
static void* TAlloc(size_t n) { g_allocN++; return calloc(1, n); }
static void TFree(void* p) { free(p); }
static void TLogNoArg() { s_logV.push_back("<noarg>"); }
static void TLogStr(const char* s) { s_logV.push_back(s); }
static void TLogFmt(const char* f, const char* a, int b) {
    char buf[256]; snprintf(buf, sizeof buf, f, a, b);
    s_logV.push_back(buf); }
static void* g_vt[2]; static int s_vtReady = 0;
static void TDtor(void*, int flag) { s_vtdtorN++; (void)flag; }
static void** TVt() { return (void**)g_vt; }
static void* TIniOpen(const char* f, const char* s) {
    s_iniFile = f; s_iniSect = s; return (void*)1; }
static int TIniGetInt(void*, const char*) { return s_enable; }
static void TIniClose(void*) {}
static void* TDb() { return (void*)0xDB; }
static void* TQuery(void*, const char* sql, int type) {
    s_queryN++; s_sql = sql; s_queryType = type;
    return s_count == -1 ? nullptr : (void*)&s_rsTok; }
static int64_t TCount(void*) { return s_count; }
static void* TRecord(void*, int idx) {
    static int v2, v3;
    if (idx == 2) { v2 = s_rec2; return &v2; }
    v3 = s_rec3; return &v3; }
static int TGetInt(void* r) { return *(int*)r; }
static void TRelease(void*) { s_releaseN++; }
static void TNow(int32_t* o) { *o = s_now; }
static STmBroken* TLocal(const int32_t* t) {
    s_tmCalls++;
    if (s_tmNull) return nullptr;
    if (s_tmCalls == 1) return &s_tm;
    (void)t;
    return &s_tm2; }
static int32_t TMk(STmBroken*) { return s_mktimeRet; }
static uintptr_t TBegin(void* (*fn)(void*), void* arg, uint32_t*) {
    s_btN++; s_btArg = arg; (void)fn; return s_handle; }
static void* TThreadFn() { return (void*)0xF00; }
static void* TGlobal() { return s_globalSlot; }
static SCrossCfgSeams S;
static void Wire() {
    S.Alloc = TAlloc; S.Free = TFree;
    S.LogErrNoArg = TLogNoArg; S.LogErrStr = TLogStr;
    S.LogErrFmt = TLogFmt; S.VtTable = TVt;
    S.IniOpen = TIniOpen; S.IniGetInt = TIniGetInt;
    S.IniClose = TIniClose;
    S.DbInstance = TDb; S.DbQuery = TQuery; S.RecSetCount = TCount;
    S.RecSetRecord = TRecord; S.RecordGetInt = TGetInt;
    S.RecSetRelease = TRelease;
    S.Now32 = TNow; S.LocalTime = TLocal; S.MkTime = TMk;
    S.BeginThreadEx = TBegin; S.MonitorThreadFn = TThreadFn;
    S.MonitorGlobal = TGlobal;
}
static void ResetAll() {
    if (!s_vtReady) { g_vt[0] = (void*)TDtor; g_vt[1] = nullptr;
        s_vtReady = 1; }
    s_sql.clear(); s_iniFile.clear(); s_iniSect.clear(); s_logV.clear();
    s_enable = 0; s_rec2 = 21030; s_rec3 = 30; s_count = 1;
    s_queryType = -1; s_releaseN = s_queryN = s_vtdtorN = 0;
    s_now = 100000; s_mktimeRet = 0; s_tmNull = 0; s_tmCalls = 0;
    memset(&s_tm, 0, sizeof s_tm);
    s_tm.wday = 3; s_tm.hour = 4; s_tm.min = 5; s_tm.mday = 12;
    s_tm.mon = 9; s_tm.year = 126; s_tm.yday = 285; s_tm.isdst = 0;
    memset(&s_tm2, 0, sizeof s_tm2);
    s_tm2.wday = 9; s_tm2.hour = 21; s_tm2.min = 47; s_tm2.mday = 1;
    s_handle = 0x1234; s_btN = 0; s_btArg = nullptr;
    s_globalSlot = (void*)0xCAFE;
    g_allocN = 0;
}
int main() {
    Wire();
    SECT("A9f-1 QueryCqConfig");
    ResetAll();
    CHECK(QueryCqConfig(0x186a1, 1, S) == (void*)&s_rsTok, "returns rs");
    CHECK(s_sql == "SELECT * FROM cq_config WHERE type = 100001 LIMIT 1",
          "LIMIT form + the type");
    CHECK(s_queryType == 2, "query type 2");
    ResetAll(); s_count = 0;
    CHECK(QueryCqConfig(5, 0, S) == nullptr, "empty rs -> 0");
    CHECK(s_sql == "SELECT * FROM cq_config WHERE type = 5", "no LIMIT");
    CHECK(s_releaseN == 1, "vtable[0] release");
    ResetAll(); s_count = -1;
    CHECK(QueryCqConfig(7, 1, S) == nullptr, "null rs -> 0");
    CHECK(s_releaseN == 0, "no release on null");
    SECT("A9f-2 LoadSchedule");
    ResetAll(); s_count = -1;
    SCrossConfig c; memset(&c, 0, sizeof c);
    CHECK(CrossConfigLoadSchedule(&c, S) == 0, "no rs -> 0");
    CHECK(s_logV.size() == 1, "logged");
    ResetAll(); memset(&c, 0, sizeof c); s_rec2 = 21030; s_rec3 = 30;
    CHECK(CrossConfigLoadSchedule(&c, S) == 1, "-> 1");
    CHECK(c.minute == 30, "minute = v%100");
    CHECK(c.hour == 10, "hour = (v/100)%100");
    CHECK(c.wday == 2, "wday = (v/10000)%100");
    CHECK(c.window == 1800, "window = 30*0x3c");
    CHECK(s_releaseN == 1, "rs released");
    ResetAll(); memset(&c, 0, sizeof c); s_rec3 = -1;
    CHECK(CrossConfigLoadSchedule(&c, S) == 1, "-> 1");
    CHECK(c.window == 0x1c20, "negative -> default 7200");
    SECT("A9f-3 IsInWindow");
    ResetAll(); memset(&c, 0, sizeof c); s_tmNull = 1;
    CHECK(CrossConfigIsInWindow(&c, S) == 0, "no localtime -> 0");
    ResetAll(); memset(&c, 0, sizeof c);
    c.wday = 2; c.hour = 4; c.minute = 5; c.window = 7200;
    CHECK(CrossConfigIsInWindow(&c, S) == 0, "wday mismatch -> 0");
    ResetAll(); memset(&c, 0, sizeof c);
    c.wday = 3; c.hour = 4; c.minute = 5; c.window = 7200;
    s_now = 100000; s_mktimeRet = 100000 - 60;   // 60s after schedule
    CHECK(CrossConfigIsInWindow(&c, S) == 1, "inside -> 1");
    s_mktimeRet = 100000;                        // exactly now
    CHECK(CrossConfigIsInWindow(&c, S) == 0, "diff 0 -> 0");
    s_mktimeRet = 100000 - 8000;                 // past the window
    CHECK(CrossConfigIsInWindow(&c, S) == 0, "diff > window -> 0");
    s_mktimeRet = 100000 + 60;                   // in the future
    CHECK(CrossConfigIsInWindow(&c, S) == 0, "future -> 0");
    SECT("A9f-4 SetFromNow / SetWindowStart");
    ResetAll(); memset(&c, 0, sizeof c);
    CrossConfigSetFromNow(&c, S);
    CHECK(c.wday == 3 && c.hour == 4 && c.minute == 5, "from now");
    ResetAll(); memset(&c, 0, sizeof c); c.window = 3600;
    CrossConfigSetWindowStart(&c, S);
    CHECK(c.wday == 9 && c.hour == 21 && c.minute == 47,
          "from now - window (2nd localtime)");
    CHECK(s_tmCalls == 2, "two localtime calls");
    SECT("A9f-5 InitFromIni");
    ResetAll(); memset(&c, 0, sizeof c); s_enable = 1;
    CHECK(CrossConfigInitFromIni(&c, S) == 1, "returns 1");
    CHECK(s_iniFile == "shell.ini" && s_iniSect == "CrossClient",
          "RAW ini file/section");
    CHECK(c.enabled == 1, "enabled = 1");
    CHECK(s_queryN == 1, "schedule loaded when enabled");
    ResetAll(); memset(&c, 0, sizeof c); s_enable = 0;
    CrossConfigInitFromIni(&c, S);
    CHECK(c.enabled == 0 && s_queryN == 0, "disabled -> no query");
    ResetAll(); memset(&c, 0, sizeof c); s_enable = 2;
    CrossConfigInitFromIni(&c, S);
    CHECK(c.enabled == 0, "Enable=2 is NOT enabled (RAW ==1)");
    SECT("A9f-6 Create");
    ResetAll(); s_enable = 1;
    SCrossConfig* p = CrossConfigCreate(S);
    CHECK(p != nullptr, "created");
    CHECK(g_allocN == 1 && p->vt == (void**)g_vt, "0x20 alloc + vftable");
    CHECK(p->u19 == 0 && p->enabled == 1, "bytes initialised");
    TFree(p);
    SECT("A9f-7 StartWorkerThread");
    ResetAll(); SWorkerSlot w; memset(&w, 0, sizeof w);
    w.arg = (void*)0x77;
    uintptr_t h = StartWorkerThread(&w, S);
    CHECK(h == 0x1234 && w.handle == 0x1234, "handle stored at +8");
    CHECK(s_btArg == (void*)0x77, "thread arg = p[0]");
    ResetAll(); s_globalSlot = nullptr;
    CHECK(StartWorkerThread(&w, S) == 0, "no global -> 0");
    CHECK(s_logV.size() == 1 && s_btN == 0, "noarg log, no thread");
    ResetAll(); w.arg = nullptr;
    CHECK(StartWorkerThread(&w, S) == 0, "null arg -> 0");
    CHECK(s_btN == 0, "no thread");
    ResetAll(); w.arg = (void*)0x77; s_handle = 0;
    CHECK(StartWorkerThread(&w, S) == 0, "thread fail -> 0");
    CHECK(!s_logV.empty() &&
          s_logV[0].find("_beginthreadex failed") != std::string::npos,
          "RAW thread-fail text");
    if (g_fail == 0) printf("CROSSCFG-OK: %d assertions\n", g_ok);
    else printf("CROSSCFG-FAIL\n");
    return g_fail ? 1 : 0;
}
