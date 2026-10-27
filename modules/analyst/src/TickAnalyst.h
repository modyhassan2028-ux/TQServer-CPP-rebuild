#pragma once
// ============================================================
// Analyst.dll — Port — Unit D1
//  CTickAnalyst family + IAnalyst basics + the Analyst()
//  singleton shell + the tick-zero globals.
//  Source: Analyst.dll.decompiled.c (verbatim, addresses
//  in comments).
// ============================================================
#include <cstdint>
#include <string>
#include <functional>

namespace analyst {

// tq::TimeGet(0) seam (the dll imports it from CQBase)
extern std::function<uint32_t()> g_fnTimeGet;
void SetTimeGet(std::function<uint32_t()> fn);

// ------------------------------------------------------------
// ORIGINAL DAT_140a490a4 — the tick zero point global,
// set by FUN_140a41650. All CTickAnalyst stamps are
// (TimeGet(0) - DAT_140a490a4).
// ------------------------------------------------------------
extern uint32_t g_dwTickZero490a4;

// ------------------------------------------------------------
// FUN_140a41650 — set the tick zero point.
// VERBATIM: returns DAT & 0xffffff00 (the low-byte-cleared
// FALSE pattern).
// ------------------------------------------------------------
uint32_t AnalystSetTickZero();

// FUN_140a41670 — (longlong)TimeGet(0) - DAT_140a490a4
int64_t AnalystNow64();
// FUN_140a416a0 — (int)TimeGet(0) - DAT_140a490a4
int32_t AnalystNow32();
// FUN_140a41690 — identity passthrough
uint32_t AnalystIdentity(uint32_t u);

// ------------------------------------------------------------
// IAnalyst — the interface base (vftable only).
//  ctor  @ 140a41020: *this = vftable
//  copy  @ 140a41030: *this = vftable  (NO member copy)
//  op=   @ 140a41040: return this      (NO member copy)
//  layout: vptr only.
// ------------------------------------------------------------
class IAnalyst {
public:
    IAnalyst();                    // 140a41020
    IAnalyst(const IAnalyst&);     // 140a41030
    IAnalyst& operator=(const IAnalyst&);  // 140a41040
    virtual ~IAnalyst() = default;
    // vtable slots (resolved D2):
    //   +0x10 -> FUN_140a412e0 (this, id) — identity echo
    //   +0x18 -> FUN_140a412f0 (this, path, ...) — the
    //            literal analyst.cpp log + tick-zero reset
    //   +0x20 -> FUN_140a41490 TicksAdd (this, id, ticks)
    //            — THE slot ~CTickAnalyst dispatches
    virtual void TickEcho(int nId);
    virtual void TickLog(const char* pszPath,
                        const void* p1 = nullptr,
                        const void* p2 = nullptr);
    virtual void TickRecord(int nId, int64_t nUsedTicks);
};

// ------------------------------------------------------------
// CTickAnalyst — layout 0x18 (three qwords):
//   +0x00 int  m_nId        (ctor writes param_1)
//   +0x08 int64 m_llFinish
//   +0x10 int64 m_llStart
//  operator= @ 140a41000 copies the three qwords.
//  ctor @ 140a41730, Start @ 140a41700,
//  Finish @ 140a416c0, GetUsedTicks @ 140a416f0,
//  GetUsedMS @ 140a417b0, dtor @ 140a41760.
// ------------------------------------------------------------
class CTickAnalyst {
public:
    explicit CTickAnalyst(int nId);   // 140a41730
    CTickAnalyst& operator=(const CTickAnalyst& o);  // 140a41000
    void Start();                    // 140a41700
    void Finish();                   // 140a416c0
    int64_t GetUsedTicks() const;    // 140a416f0
    int32_t GetUsedMS() const;       // 140a417b0
    ~CTickAnalyst();                 // 140a41760
private:
    friend class CTickAnalystAccess;
    int     m_nId;        // +0x00
    int64_t m_llFinish;   // +0x08
    int64_t m_llStart;    // +0x10
};

// test/friend access to the private layout
class CTickAnalystAccess {
public:
    static int Id(const CTickAnalyst& t) { return t.m_nId; }
    static int64_t Finish(const CTickAnalyst& t) { return t.m_llFinish; }
    static int64_t Start(const CTickAnalyst& t) { return t.m_llStart; }
};

// ------------------------------------------------------------
// FUN_140a41150 / FUN_140a41190 — the 0x40 record ctor/dtor.
// Layout CONFIRMED (D2) by crossing 41200/41280/41490/1310/
// 1460 (all analyst-relative; the array base is analyst+0x10):
//   +0x00 int32 type    (Add 41200; the report gate)
//   +0x04 int32 count   (TicksAdd ++, report cnt)
//   +0x08 int64 max     (TicksAdd)
//   +0x10 int64 total   (TicksAdd)
//   +0x18 std::string name (MSVC 0x20 -> record total 0x40)
// ------------------------------------------------------------
struct SAnalystRecord {              // 0x40
    int32_t  nType;      // +0x00
    int32_t  nCount;     // +0x04
    int64_t  llMax;      // +0x08
    int64_t  llTotal;    // +0x10
    std::string strName; // +0x18
};
void AnalystRecordCtor(SAnalystRecord* p);   // 140a41150
void AnalystRecordDtor(SAnalystRecord* p);   // 140a41190

// ------------------------------------------------------------
// FUN_140a41640 — the Analyst() singleton.
// One-time init (flag DAT_140a490a0 bit 0):
//   *(_QWORD*)DAT_140a45090 = CAnalyst::vftable
//   DAT_140a45098 = 0            (the record count)
//   eh_vector ctor on DAT_140a450a0: 0x100 records of 0x40
// Returns (IAnalyst*)&DAT_140a45090.
// ------------------------------------------------------------
IAnalyst* AnalystSingleton();
// ===== CAnalyst (D2) — the concrete singleton =====
class CAnalyst : public IAnalyst {
public:
    CAnalyst();                       // 140a414d0
    ~CAnalyst() override;             // 140a411c0 / 41530
    // 140a412e0 (this, id) -> FUN_140a41690 identity
    void TickEcho(int nId) override;
    // 140a412f0 (this, path, ...) -> 41050 with the
    // literal "f:\version\cqserver-78.0.11-1204\
    // analyst\analyst.cpp" + the 41650 tick reset
    void TickLog(const char* pszPath,
                 const void* p1, const void* p2) override;
    // 140a41490 — TicksAdd; bounds -> the literal log
    // "TicksAdd failed for index %d"
    void TickRecord(int nId, int64_t nUsedTicks) override;

    // 140a41200 — Add(id, type, name):
    // id < 0x100, name non-null and non-empty; writes
    // rec+0x00 type, rec+0x18 name, count = max(count,
    // id+1); returns the masked TRUE.
    bool Add(uint32_t uId, int32_t nType,
             const char* pszName);
    // 140a41280 — Get(id, &total, &max, &count)
    bool Get(uint32_t uId, int64_t* pTotal,
             int64_t* pMax, int32_t* pCount);
    // 140a41310 — Report(path): per record with type!=0
    // the literal "%s, cnt=%ld, tot=%dms, avg=%.2fms,
    // max=%dms" line via the 41050 log
    void Report(const char* pszPath);
    // 140a41460 — ResetStats: clears rec+0x04/+0x08/
    // +0x10 only (type + name kept)
    void ResetStats();

    int32_t Count() const { return m_nCount; }
    SAnalystRecord m_arr[0x100];  // +0x10 (public: test)
private:
    friend IAnalyst* AnalystSingleton();
    int32_t  m_nCount;      // +0x08
};

// 140a41050 — the log fn: _vsnprintf(0x740 buffer),
// basic_string(path), find('/',0,1); if FOUND ->
// tq::log_Save(path, buf, 1)  (VERBATIM: npos skips)
void AnalystLog(const char* pszPath, const char* pszFmt,
                ...);
// test hooks
bool AnalystSingletonInited();
uint32_t AnalystRecordCount();
void AnalystRecordAt(uint32_t i, SAnalystRecord& out);
void AnalystTestResetSingleton();
CAnalyst* AnalystConcrete();   // test hook
void SetLogSave(std::function<
    void(const char*, const char*)> fn);

} // namespace analyst
