// ============================================================================
// cqbase_d79 — the throw/log dispatcher. Pinned here: the kind test decides THROWING only, the
//   sink is called in both cases, and the logging wrapper is skipped for kind 3.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "modules/syndicate/src/synexcthrow.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static int32_t g_nLevel = 0;
static int g_nInit = 0, g_nBegin = 0, g_nEnd = 0, g_nSink = 0, g_nThrow = 0;
static std::string g_strSinkMsg; static int32_t g_nSinkKind = -1;
static std::string g_strThrowMsg; static const void* g_pType = nullptr;

static void LogInitHook(void) { ++g_nInit; }
static void LogBeginHook(int32_t*, int32_t*) { ++g_nBegin; }
static void LogEndHook(int32_t*) { ++g_nEnd; }
static void SinkHook(int32_t nKind, const char*, int32_t, std::string* pMsg) {
    ++g_nSink; g_nSinkKind = nKind; g_strSinkMsg = *pMsg;
}
static void ThrowHook(SynMsgBlock* pMsg, const void* pType) {
    ++g_nThrow; g_strThrowMsg = pMsg->strMessage; g_pType = pType;
}

static void ResetCounters() { g_nInit = g_nBegin = g_nEnd = g_nSink = g_nThrow = 0; }

int main() {
    g_pnLogLevel = &g_nLevel;
    g_fnLogInit = &LogInitHook;
    g_fnLogBegin = &LogBeginHook;
    g_fnLogEnd = &LogEndHook;
    g_pfnLogSink = &SinkHook;
    g_fnThrowException = &ThrowHook;

    alignas(SynMsgBlock) unsigned char aStorage[sizeof(SynMsgBlock)];
    SynMsgBlock* p = (SynMsgBlock*)aStorage;

    // ---- a message kind that is not 3 with a live log level: recorded, so the sink is skipped
    {
        SynMsgInit(p, 1, "coded_stream.cc", 0x219);
        SynMsgAppend(p, "danger");
        ResetCounters(); g_nLevel = 1;
        SynReportMsg(p);
        CHECK(g_nInit == 1);
        CHECK(g_nBegin == 1);
        CHECK(g_nEnd == 1);
        CHECK(g_nSink == 0);          // the wrapper recorded it, so the sink is not used
        CHECK(g_nThrow == 0);
        SynMsgDestroy(p);
    }

    // ---- the same with a zero log level falls through to the sink
    {
        SynMsgInit(p, 1, "coded_stream.cc", 0x219);
        SynMsgAppend(p, "quiet");
        ResetCounters(); g_nLevel = 0;
        SynReportMsg(p);
        CHECK(g_nSink == 1);
        CHECK(g_strSinkMsg == "quiet");
        CHECK(g_nThrow == 0);
        SynMsgDestroy(p);
    }

    // ---- kind 3: the logging wrapper is skipped, the sink still runs, and then it throws
    {
        SynMsgInit(p, 3, "coded_stream.cc", 0x207);
        SynMsgAppend(p, "CHECK failed: (0) == (BufferSize()): ");
        ResetCounters(); g_nLevel = 5;      // even with a live log level the wrapper is skipped
        SynReportMsg(p);
        CHECK(g_nInit == 0);
        CHECK(g_nBegin == 0);
        CHECK(g_nEnd == 0);
        CHECK(g_nSink == 1);
        CHECK(g_strSinkMsg == "CHECK failed: (0) == (BufferSize()): ");
        CHECK(g_nThrow == 1);
        CHECK(g_strThrowMsg == "CHECK failed: (0) == (BufferSize()): ");
        CHECK(g_pType == (const void*)0x141881eb8);   // the std::exception type_info
        SynMsgDestroy(p);
    }

    std::printf("SYNDICATE_D79_OK: the throw dispatcher, %d checks\n", g_nChecks);
    return 0;
}
