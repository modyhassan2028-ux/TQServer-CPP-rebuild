#include "TickAnalyst.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <vector>

namespace analyst {

// the TimeGet seam
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
// IAnalyst — 140a41020/30/40 (no-copy semantics)
// ============================================================
IAnalyst::IAnalyst() {}
IAnalyst::IAnalyst(const IAnalyst&) {}
IAnalyst& IAnalyst::operator=(const IAnalyst&) { return *this; }
void IAnalyst::TickEcho(int) {}
void IAnalyst::TickLog(const char*, const void*, const void*) {}
void IAnalyst::TickRecord(int, int64_t) {}

// ============================================================
// CTickAnalyst (D1)
// ============================================================
// ===== ORIGINAL FUN_140a41730 =====
CTickAnalyst::CTickAnalyst(int nId)
    : m_nId(nId), m_llFinish(0), m_llStart(0) {
    m_llStart = (int64_t)(uint64_t)g_fnTimeGet()
                - (int64_t)(uint64_t)g_dwTickZero490a4;
}
// ===== ORIGINAL FUN_140a41000 =====
CTickAnalyst& CTickAnalyst::operator=(const CTickAnalyst& o) {
    m_nId = o.m_nId;
    m_llFinish = o.m_llFinish;
    m_llStart = o.m_llStart;
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
int32_t CTickAnalyst::GetUsedMS() const {
    return (int32_t)m_llFinish - (int32_t)m_llStart;
}
// ===== ORIGINAL FUN_140a41760 =====
CTickAnalyst::~CTickAnalyst() {
    m_llFinish = (int64_t)(uint64_t)g_fnTimeGet()
                 - (int64_t)(uint64_t)g_dwTickZero490a4;
    IAnalyst* p = AnalystSingleton();
    if (p != nullptr) {
        // VERBATIM: vtable+0x20 with (id, usedTicks)
        p->TickRecord(m_nId, m_llFinish - m_llStart);
    }
}

// ============================================================
// FUN_140a41150 / FUN_140a41190 — record ctor/dtor
// ============================================================
void AnalystRecordCtor(SAnalystRecord* p) {
    // 41150: zero +0x00..0x18, string ctor at +0x18
    p->nType = 0; p->nCount = 0;
    p->llMax = 0; p->llTotal = 0;
    new (&p->strName) std::string();
}
void AnalystRecordDtor(SAnalystRecord* p) {
    // 41190: string dtor at +0x18, then re-construct so
    // the storage stays valid (test-model of placement)
    p->strName.~basic_string();
    new (&p->strName) std::string();
}

// ============================================================
// FUN_140a41050 — the log function
// VERBATIM: vsnprintf into a 0x740 buffer (memset 0x73f
// + NUL); std::string(path); find('/', 0, 1); if NOT npos
// -> tq::log_Save(path, buf, 1). (npos skips the log.)
// ============================================================
static std::function<void(const char*, const char*)>
    s_fnLogSave = [](const char*, const char*) {};
void SetLogSave(std::function<
    void(const char*, const char*)> fn) {
    s_fnLogSave = fn;
}
static thread_local char s_szLogBuf[0x740];
void AnalystLog(const char* pszPath, const char* pszFmt,
                ...) {
    memset(s_szLogBuf + 1, 0, 0x73f);
    s_szLogBuf[0] = '\0';
    va_list ap;
    va_start(ap, pszFmt);
    vsnprintf(s_szLogBuf, 0x740, pszFmt, ap);
    va_end(ap);
    std::string strPath(pszPath ? pszPath : "");
    // MSVC 3-arg overload: find(const char*, pos=0, n=1)
    // = search for a 1-char '/' substring
    if (strPath.find("/", 0) != std::string::npos) {
        s_fnLogSave(pszPath, s_szLogBuf);
    }
}

// ============================================================
// CAnalyst
// ============================================================
// ===== ORIGINAL FUN_140a414d0 =====
CAnalyst::CAnalyst() : IAnalyst(), m_nCount(0) {
    for (uint32_t i = 0; i < 0x100; ++i)
        AnalystRecordCtor(&m_arr[i]);
}
// ===== ORIGINAL FUN_140a411c0 (complete dtor) =====
CAnalyst::~CAnalyst() {
    for (uint32_t i = 0; i < 0x100; ++i)
        AnalystRecordDtor(&m_arr[i]);
}

// ===== ORIGINAL FUN_140a412e0 (slot +0x10) =====
void CAnalyst::TickEcho(int nId) {
    // VERBATIM: calls FUN_140a41690 and discards
    (void)AnalystIdentity((uint32_t)nId);
}
// ===== ORIGINAL FUN_140a412f0 (slot +0x18) =====
void CAnalyst::TickLog(const char* pszPath,
                       const void*, const void*) {
    // VERBATIM: 41050 with the literal file string as the
    // format, then the 41650 tick-zero reset
    AnalystLog(pszPath,
        "f:\\version\\cqserver-78.0.11-1204\\"
        "analyst\\analyst.cpp");
    (void)AnalystSetTickZero();
}

// ===== ORIGINAL FUN_140a41490 (slot +0x20) =====
void CAnalyst::TickRecord(int nId, int64_t nTicks) {
    // bounds: id in [0, count)
    if (nId < 0 || m_nCount <= nId) {
        char sz[0x100];
        snprintf(sz, sizeof(sz),
                 "TicksAdd failed for index %d", nId);
        s_fnLogSave("ERROR", sz);   // log_InlineLogERROR
        return;
    }
    SAnalystRecord& r = m_arr[nId];
    r.nCount = r.nCount + 1;                 // +0x04
    r.llTotal = r.llTotal + nTicks;         // +0x10
    if (r.llMax < nTicks) r.llMax = nTicks; // +0x08
}

// ===== ORIGINAL FUN_140a41200 — Add =====
bool CAnalyst::Add(uint32_t uId, int32_t nType,
                   const char* pszName) {
    if (uId < 0x100 && pszName != nullptr
        && *pszName != '\0') {
        SAnalystRecord& r = m_arr[uId];
        if (r.nType == 0) {                  // rec+0x00
            r.nType = nType;
            r.strName = pszName;             // rec+0x18
            if (m_nCount < (int32_t)(uId + 1))
                m_nCount = (int32_t)uId + 1;
            // VERBATIM masked-true return
            return true;
        }
    }
    return false;
}

// ===== ORIGINAL FUN_140a41280 — Get =====
bool CAnalyst::Get(uint32_t uId, int64_t* pTotal,
                   int64_t* pMax, int32_t* pCount) {
    if ((int32_t)uId < 0 || (int32_t)uId >= m_nCount)
        return false;                 // masked low byte 0
    SAnalystRecord& r = m_arr[uId];
    if (pTotal) *pTotal = r.llTotal;   // read +0x20/rel
    if (pMax)   *pMax   = r.llMax;     // read +0x18/rel
    if (pCount) *pCount = r.nCount;    // read +0x14/rel
    return true;
}

// ===== ORIGINAL FUN_140a41310 — Report =====
void CAnalyst::Report(const char* pszPath) {
    for (int32_t i = 0; i < m_nCount; ++i) {
        SAnalystRecord& r = m_arr[i];
        if (r.nType != 0) {                  // rec+0x00
            int64_t nMax   = r.llMax;
            int64_t nTotal = r.llTotal;
            int32_t nCount = r.nCount;
            float fAvg = 0.0f;
            if (0 < nCount)
                fAvg = (float)nTotal / (float)nCount;
            char sz[0x400];
            snprintf(sz, 0x3ff,
                "%s, cnt=%ld, tot=%dms, avg=%.2fms, "
                "max=%dms",
                r.strName.c_str(), (long)nCount,
                (int)nTotal, (double)fAvg,
                (int)nMax);
            AnalystLog(pszPath, "%s", sz);
        }
    }
}

// ===== ORIGINAL FUN_140a41460 — ResetStats =====
void CAnalyst::ResetStats() {
    for (int32_t i = 0; i < m_nCount; ++i) {
        SAnalystRecord& r = m_arr[i];
        r.nCount = 0;        // +0x04
        r.llMax = 0;         // +0x08
        r.llTotal = 0;       // +0x10
    }
}

// ============================================================
// FUN_140a41640 / 140a415a0 — the singleton
// ============================================================
static CAnalyst* s_pInstance = nullptr;   // DAT_140a45090
static bool s_bInited = false;            // DAT_140a490a0

bool AnalystSingletonInited() { return s_bInited; }
uint32_t AnalystRecordCount() {
    return s_pInstance ? (uint32_t)s_pInstance->Count() : 0;
}
void AnalystRecordAt(uint32_t i, SAnalystRecord& out) {
    if (s_pInstance && i < 0x100) out = s_pInstance->m_arr[i];
}

IAnalyst* AnalystSingleton() {
    if (!s_bInited) {
        s_bInited = true;              // DAT_140a490a0 |= 1
        static CAnalyst s_storage;     // DAT_140a45090..
        s_pInstance = &s_storage;
    }
    return s_pInstance;
}

void AnalystTestResetSingleton() {
    // NOTE: the storage is a static placement object; a
    // real reset re-runs the ctor: destroy + reconstruct
    s_bInited = false;
    s_pInstance = nullptr;
}

CAnalyst* AnalystConcrete() {           // test hook
    return s_pInstance;
}

} // namespace analyst
