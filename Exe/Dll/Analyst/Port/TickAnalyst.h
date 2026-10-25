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
    // vtable slot +0x20 — called by ~CTickAnalyst as
    // (id, usedTicks). Slot target not yet identified
    // in the binary: documented TBD in PORTING_LOG.
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
// FUN_140a41150 / FUN_140a41190 — the 0x40 record ctor/dtor
// used by the eh_vector iterator on the singleton's array:
//   ctor: zero the first 0x18 bytes, then construct a
//         std::string at +0x18
//   dtor: destroy the string at +0x18
// ------------------------------------------------------------
struct SAnalystRecord {              // 0x40
    uint8_t  abyZero18[0x18];        // +0x00 (type at +0x10, u32 at +0x14)
    std::string strName;             // +0x18 (MSVC layout 0x28 -> 0x40 total)
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
// test hooks
bool AnalystSingletonInited();
uint32_t AnalystRecordCount();
void AnalystRecordAt(uint32_t i, SAnalystRecord& out);
void AnalystTestResetSingleton();

} // namespace analyst
