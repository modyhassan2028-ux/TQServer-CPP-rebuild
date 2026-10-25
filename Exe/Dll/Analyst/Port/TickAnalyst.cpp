#include "TickAnalyst.h"

namespace analyst {

// the TimeGet seam
static std::function<uint32_t()> s_fnTimeGet = []{ return 0u; };
std::function<uint32_t()> g_fnTimeGet;
void SetTimeGet(std::function<uint32_t()> fn) { g_fnTimeGet = fn; }

// ===== ORIGINAL DAT_140a490a4 =====
uint32_t g_dwTickZero490a4 = 0;

// ===== ORIGINAL FUN_140a41650 =====
uint32_t AnalystSetTickZero() {
    g_dwTickZero490a4 = g_fnTimeGet();
    // VERBATIM: return DAT & 0xffffff00
    return g_dwTickZero490a4 & 0xffffff00u;
}

// ===== ORIGINAL FUN_140a41670 =====
int64_t AnalystNow64() {
    return (int64_t)(uint64_t)g_fnTimeGet()
           - (int64_t)(uint64_t)g_dwTickZero490a4;
}

// ===== ORIGINAL FUN_140a41690 =====
uint32_t AnalystIdentity(uint32_t u) { return u; }

// ===== ORIGINAL FUN_140a416a0 =====
int32_t AnalystNow32() {
    return (int32_t)g_fnTimeGet() - (int32_t)g_dwTickZero490a4;
}

// ============================================================
// IAnalyst
// ============================================================
IAnalyst::IAnalyst() {}                 // 140a41020: vptr
IAnalyst::IAnalyst(const IAnalyst&) {}  // 140a41030: vptr only
IAnalyst& IAnalyst::operator=(const IAnalyst&) {
    // 140a41040: returns this, copies NOTHING
    return *this;
}
// vtable slot +0x20 — TBD slot target (see PORTING_LOG)
void IAnalyst::TickRecord(int, int64_t) {}

// ============================================================
// CTickAnalyst
// ============================================================
// ===== ORIGINAL FUN_140a41730 =====
CTickAnalyst::CTickAnalyst(int nId)
    : m_nId(nId), m_llFinish(0), m_llStart(0) {
    m_llStart = (int64_t)(uint64_t)g_fnTimeGet()
                - (int64_t)(uint64_t)g_dwTickZero490a4;
}

// ===== ORIGINAL FUN_140a41000 =====
// VERBATIM: copies the three qwords (0x00/0x08/0x10)
CTickAnalyst& CTickAnalyst::operator=(const CTickAnalyst& o) {
    m_nId     = o.m_nId;
    m_llFinish = o.m_llFinish;
    m_llStart  = o.m_llStart;
    return *this;
}

// ===== ORIGINAL FUN_140a41700 =====
void CTickAnalyst::Start() {
    m_llStart = (int64_t)(uint64_t)g_fnTimeGet()
                - (int64_t)(uint64_t)g_dwTickZero490a4;
}

// ===== ORIGINAL FUN_140a416c0 =====
void CTickAnalyst::Finish() {
    m_llFinish = (int64_t)(uint64_t)g_fnTimeGet()
                 - (int64_t)(uint64_t)g_dwTickZero490a4;
}

// ===== ORIGINAL FUN_140a416f0 =====
int64_t CTickAnalyst::GetUsedTicks() const {
    return m_llFinish - m_llStart;
}

// ===== ORIGINAL FUN_140a417b0 =====
// VERBATIM: reads the two halves as INTS
int32_t CTickAnalyst::GetUsedMS() const {
    return (int32_t)m_llFinish - (int32_t)m_llStart;
}

// ===== ORIGINAL FUN_140a41760 =====
CTickAnalyst::~CTickAnalyst() {
    // VERBATIM: Finish() inline, then the singleton
    // vtable+0x20 dispatch with (id, usedTicks)
    m_llFinish = (int64_t)(uint64_t)g_fnTimeGet()
                 - (int64_t)(uint64_t)g_dwTickZero490a4;
    IAnalyst* p = AnalystSingleton();
    if (p != nullptr) {
        p->TickRecord(m_nId, m_llFinish - m_llStart);
    }
}

// ============================================================
// FUN_140a41150 / FUN_140a41190 — record ctor/dtor
// ============================================================
void AnalystRecordCtor(SAnalystRecord* p) {
    // 140a41150: zero the first 0x18 bytes
    for (int i = 0; i < 0x18; ++i) p->abyZero18[i] = 0;
    // then construct the string at +0x18
    new (&p->strName) std::string();
}
void AnalystRecordDtor(SAnalystRecord* p) {
    // 140a41190: destroy the string at +0x18
    p->strName.~basic_string();
    p->strName = "";
    // reconstruct so the storage stays reusable
    new (&p->strName) std::string();
}

// ============================================================
// FUN_140a41640 — the singleton
// ============================================================
static bool s_bInited = false;           // DAT_140a490a0 bit0
static IAnalyst* s_pInstance = nullptr;  // &DAT_140a45090
static uint32_t s_dwRecordCount = 0;      // DAT_140a45098
static const uint32_t kRecordCount = 0x100;
static SAnalystRecord* s_arrRecords = nullptr;  // DAT_140a450a0
// the singleton backing storage: the IAnalyst at
// DAT_140a45090 gets CAnalyst::vftable written into it
static IAnalyst s_StaticInstance;

bool AnalystSingletonInited() { return s_bInited; }
uint32_t AnalystRecordCount() { return s_dwRecordCount; }
SAnalystRecord* AnalystRecordPtr(uint32_t i) {
    return i < kRecordCount ? &s_arrRecords[i] : nullptr;
}
void AnalystRecordAt(uint32_t i, SAnalystRecord& out) {
    if (i < kRecordCount) out = s_arrRecords[i];
}

IAnalyst* AnalystSingleton() {
    if (!s_bInited) {
        s_bInited = true;    // DAT_140a490a0 |= 1
        s_pInstance = static_cast<IAnalyst*>(&s_StaticInstance);
        s_dwRecordCount = 0;  // DAT_140a45098 = 0
        // eh_vector ctor: 0x100 records via the 41150 ctor
        s_arrRecords = new SAnalystRecord[kRecordCount];
        for (uint32_t i = 0; i < kRecordCount; ++i)
            AnalystRecordCtor(&s_arrRecords[i]);
        // (atexit(FUN_140a426e0) dtor — process exit; not
        //  modeled per the CRT-inlined rule)
    }
    return s_pInstance;
}

void AnalystTestResetSingleton() {
    delete[] s_arrRecords;
    s_arrRecords = nullptr;
    s_bInited = false;
    s_pInstance = nullptr;
    s_dwRecordCount = 0;
}

} // namespace analyst
