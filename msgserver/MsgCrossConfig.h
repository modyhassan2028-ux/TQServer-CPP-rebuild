#ifndef MSG_CROSS_CONFIG_H
#define MSG_CROSS_CONFIG_H
// ===== Path-A wave 9f: CCrossConfig (the cross-client window) =====
// 140005ad0 Create          — operator_new(0x20), vftable, zeros
//                             (8,c,10,14 dwords + 18,19 bytes), then
//                             140005a20; on failure vtable[0](p,1)
// 140005a20 InitFromIni     — CIniFile("shell.ini","CrossClient")
//                             GetInt("Enable"); +0x18 = (v==1);
//                             if enabled -> 140005900 then the ini
//                             dtor; returns 1
// 140005900 LoadSchedule    — QueryCqConfig(0x186a1, 1); record 2 ->
//                             +0x10 = v%100, +0xc = (v/100)%100,
//                             +0x8 = (v/10000)%100, +0x14 = 0x1c20
//                             then record 3 >= 0 -> +0x14 = v*0x3c
// 140005680 IsInWindow      — now via _time32/_localtime32; only when
//                             the weekday matches: tm{sec=0,min=+0x10,
//                             hour=+0xc,mday=today,mon/year/yday/isdst
//                             from now} -> _mktime32; true iff
//                             0 < now-t <= +0x14
// 140005790 SetFromNow      — +0x8/c/10 = now's wday/hour/min
// 1400057d0 SetWindowStart  — same but from (now - +0x14); the second
//                             _localtime32 result is NOT null-checked
//                             (RAW quirk, preserved)
// 140006ad0 QueryCqConfig   — InstanceGet(); fmt with/without
//                             "LIMIT 1"; _snprintf(sql,0x400,fmt,type);
//                             vt+0x10(sql,2); count vt+0x40 != 0 keeps
//                             it, else vtable[0] dtor
// 140005550 StartWorkerThread — CCheatingProgramMonitor: the global
//                             slot must be non-null, p[0] non-null,
//                             _beginthreadex(entry,p[0]) -> p[1]
#include <cstdint>
#include <cstddef>
namespace msg {
#pragma pack(push, 1)
struct SCrossConfig {              // 0x20 (RAW)
    void**  vt;                    // +0x00
    int32_t wday;                  // +0x08
    int32_t hour;                  // +0x0c
    int32_t minute;                // +0x10
    int32_t window;                // +0x14 (seconds)
    uint8_t enabled;               // +0x18
    uint8_t u19;                   // +0x19
};
#pragma pack(pop)
struct STmBroken {                 // MSVC tm layout
    int32_t sec, min, hour, mday, mon, year, wday, yday, isdst;
};
struct SWorkerSlot {               // the monitor thread pair
    void*   arg;                   // +0x00
    uintptr_t handle;              // +0x08
};
struct SCrossCfgSeams {
    void*  (*Alloc)(size_t n);
    void   (*Free)(void* p);
    void   (*LogErrNoArg)();
    void   (*LogErrStr)(const char* s);
    void   (*LogErrFmt)(const char* s, const char* a, int b);
    void** (*VtTable)();           // CCrossConfig::vftable
    // CIniFile
    void*  (*IniOpen)(const char* file, const char* sect);
    int    (*IniGetInt)(void* ini, const char* key);
    void   (*IniClose)(void* ini);
    // DB
    void*  (*DbInstance)();
    void*  (*DbQuery)(void* db, const char* sql, int type);
    int64_t(*RecSetCount)(void* rs);
    void*  (*RecSetRecord)(void* rs, int idx);
    int    (*RecordGetInt)(void* rec);
    void   (*RecSetRelease)(void* rs);   // vtable[0] dtor
    // time
    void   (*Now32)(int32_t* out);
    STmBroken* (*LocalTime)(const int32_t* t);
    int32_t(*MkTime)(STmBroken* tm);
    // thread
    uintptr_t (*BeginThreadEx)(void* (*fn)(void*), void* arg,
                               uint32_t* tid);
    void*  (*MonitorThreadFn)();
    void*  (*MonitorGlobal)();     // DAT_1409754e8 value
};
// 140005900 loads the schedule; 140005680 the window test
void* QueryCqConfig(uint32_t type, int bLimit, const SCrossCfgSeams& s);
int   CrossConfigLoadSchedule(SCrossConfig* p, const SCrossCfgSeams& s);
int   CrossConfigIsInWindow(const SCrossConfig* p, const SCrossCfgSeams& s);
void  CrossConfigSetFromNow(SCrossConfig* p, const SCrossCfgSeams& s);
void  CrossConfigSetWindowStart(SCrossConfig* p, const SCrossCfgSeams& s);
int   CrossConfigInitFromIni(SCrossConfig* p, const SCrossCfgSeams& s);
SCrossConfig* CrossConfigCreate(const SCrossCfgSeams& s);
uintptr_t StartWorkerThread(SWorkerSlot* p, const SCrossCfgSeams& s);
}
#endif
