// ===== Path-A wave 9f: CCrossConfig, RAW-verbatim =====
#include "MsgCrossConfig.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>
namespace msg {
// 140006ad0 — the cq_config query
void* QueryCqConfig(uint32_t type, int bLimit, const SCrossCfgSeams& s) {
    void* db = s.DbInstance();
    const char* fmt = bLimit
        ? "SELECT * FROM cq_config WHERE type = %d LIMIT 1"
        : "SELECT * FROM cq_config WHERE type = %d";
    char sql[0x400];
    snprintf(sql, 0x400, fmt, (int)type);   // RAW _snprintf
    sql[0x3ff] = '\0';              // RAW: local_19 terminator
    void* rs = s.DbQuery(db, sql, 2);
    if (rs != nullptr) {
        if (s.RecSetCount(rs) != 0) {
            return rs;
        }
        s.RecSetRelease(rs);        // vtable[0]
    }
    return nullptr;
}
// 140005900 — load the window from cq_config type 0x186a1
int CrossConfigLoadSchedule(SCrossConfig* p, const SCrossCfgSeams& s) {
    void* rs = QueryCqConfig(0x186a1, 1, s);
    if (rs == nullptr) {
        s.LogErrStr("");            // &DAT_1406da820
        return 0;
    }
    void* rec = s.RecSetRecord(rs, 2);
    int v = s.RecordGetInt(rec);
    p->minute = v % 100;
    p->hour = (v / 100) % 100;
    p->wday = (v / 10000) % 100;
    p->window = 0x1c20;
    void* rec3 = s.RecSetRecord(rs, 3);
    int v3 = s.RecordGetInt(rec3);
    if (-1 < v3) {
        p->window = v3 * 0x3c;
    }
    s.RecSetRelease(rs);
    return 1;
}
// 140005680 — is now inside [scheduled, scheduled + window]?
int CrossConfigIsInWindow(const SCrossConfig* p, const SCrossCfgSeams& s) {
    int32_t now = 0;
    s.Now32(&now);
    STmBroken* t = s.LocalTime(&now);
    if (t == nullptr) {
        return 0;
    }
    STmBroken tm;
    tm.mon = t->mon;
    tm.year = t->year;
    int wday = t->wday;
    tm.wday = t->wday;
    tm.yday = t->yday;
    tm.isdst = t->isdst;
    if (p->wday == wday) {
        tm.mday = t->mday;
        tm.hour = p->hour;
        tm.sec = 0;                 // RAW: the packed qword = min<<32
        tm.min = p->minute;
        int32_t t2 = s.MkTime(&tm);
        if (p->wday == wday && (now - t2 <= p->window)
                && (0 < now - t2)) {
            return 1;
        }
    }
    return 0;
}
// 140005790 — set the window from "now"
void CrossConfigSetFromNow(SCrossConfig* p, const SCrossCfgSeams& s) {
    int32_t now = 0;
    s.Now32(&now);
    STmBroken* t = s.LocalTime(&now);
    if (t != nullptr) {
        p->wday = t->wday;
        p->hour = t->hour;
        p->minute = t->min;
    }
}
// 1400057d0 — set it from "now - window"
void CrossConfigSetWindowStart(SCrossConfig* p, const SCrossCfgSeams& s) {
    int32_t now = 0;
    s.Now32(&now);
    STmBroken* t = s.LocalTime(&now);
    if (t != nullptr) {
        now = now - p->window;
        t = s.LocalTime(&now);      // RAW: no null check on this one
        p->minute = t->min;
        p->hour = t->hour;
        p->wday = t->wday;
    }
}
// 140005a20 — shell.ini [CrossClient] Enable
int CrossConfigInitFromIni(SCrossConfig* p, const SCrossCfgSeams& s) {
    void* ini = s.IniOpen("shell.ini", "CrossClient");
    int e = s.IniGetInt(ini, "Enable");
    p->enabled = (e == 1) ? 1 : 0;
    if (p->enabled == 0) {
        s.IniClose(ini);
    } else {
        CrossConfigLoadSchedule(p, s);
        s.IniClose(ini);
    }
    return 1;
}
// 140005ad0 — the factory
SCrossConfig* CrossConfigCreate(const SCrossCfgSeams& s) {
    SCrossConfig* p = (SCrossConfig*)s.Alloc(0x20);
    if (p == nullptr) {
        return nullptr;
    }
    p->vt = s.VtTable();
    p->wday = 0;
    p->hour = 0;
    p->minute = 0;
    p->window = 0;
    p->enabled = 0;
    p->u19 = 0;
    if (CrossConfigInitFromIni(p, s) == 0) {
        // RAW: vtable[0](p, 1, ...) — the scalar deleting dtor
        typedef void (*DtorFn)(void*, int);
        ((DtorFn)(p->vt[0]))(p, 1);
        return nullptr;
    }
    return p;
}
// 140005550 — CCheatingProgramMonitor::StartWorkerThread
uintptr_t StartWorkerThread(SWorkerSlot* p, const SCrossCfgSeams& s) {
    if (s.MonitorGlobal() == nullptr) {    // DAT_1409754e8
        s.LogErrNoArg();
        return 0;
    }
    if (p->arg == nullptr) {
        s.LogErrNoArg();
        return 0;
    }
    uint32_t tid = 0;
    uintptr_t h = s.BeginThreadEx(
        (void* (*)(void*))s.MonitorThreadFn(), p->arg, &tid);
    p->handle = h;
    if (h == 0) {
        s.LogErrFmt("CCheatingProgramMonitor::StartWorkerThread()"
                    " _beginthreadex failed at %s, %d", "", 0);
        return 0;
    }
    return h;
}
}
