// ============================================================================
// cqbase_d65 — the protobuf log append family (six formats) and two small helpers.
//   The fake seams record the exact literal handed to the formatter and the bytes appended
//   into the string at +0x18, which is where every one of these bodies writes.
// ============================================================================
#include "modules/syndicate/src/synpblog.h"

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

std::string g_strLastFmt;
std::string g_strLastAppended;
void AppendCStrHook(void* pStr, const char* psz) {
    g_strLastAppended = psz ? psz : "";
    ((std::string*)pStr)->append(psz ? psz : "");
}
std::string g_strAppendedOther;
void AppendStrHook(void* pStr, const void* pOther) {
    g_strAppendedOther = *(const std::string*)pOther;
    ((std::string*)pStr)->append(*(const std::string*)pOther);
}
int FmtHook(char* pszBuf, size_t uSize, const char* pszFmt, ...) {
    g_strLastFmt = pszFmt ? pszFmt : "";
    va_list ap;
    va_start(ap, pszFmt);
    int n = vsnprintf(pszBuf, uSize, pszFmt, ap);
    va_end(ap);
    return n;
}

// a message-shaped object: the appended string lives at +0x18
struct Msg {
    std::vector<uint8_t> a;
    std::string* pStr;
    Msg() : a(0x60, 0) {
        pStr = new (a.data() + 0x18) std::string();
    }
    ~Msg() { pStr->~basic_string(); }
    uint8_t* p() { return a.data(); }
};

}  // namespace

int main() {
    g_fnLogAppendCStr = &AppendCStrHook;
    g_fnLogAppendStr = &AppendStrHook;
    g_fnLogFormat = &FmtHook;

    // ---- %c: the byte is sign-extended, and the answer is the message itself
    {
        Msg m;
        g_strLastFmt.clear(); g_strLastAppended.clear();
        CHECK(SynLogAppendChar(m.p(), 'A') == m.p());
        CHECK(g_strLastFmt == "%c");
        CHECK(g_strLastAppended == "A");
        CHECK(*m.pStr == "A");
    }

    // ---- %d
    {
        Msg m;
        g_strLastFmt.clear();
        SynLogAppendInt(m.p(), -42);
        CHECK(g_strLastFmt == "%d");
        CHECK(*m.pStr == "-42");
    }

    // ---- %u
    {
        Msg m;
        g_strLastFmt.clear();
        SynLogAppendUInt(m.p(), 4000000000u);
        CHECK(g_strLastFmt == "%u");
        CHECK(*m.pStr == "4000000000");
    }

    // ---- %ld keeps the full 64-bit value
    {
        Msg m;
        g_strLastFmt.clear();
        SynLogAppendLong(m.p(), -9007199254740993LL);
        CHECK(g_strLastFmt == "%ld");
        CHECK(*m.pStr == "-9007199254740993");
    }

    // ---- %lu
    {
        Msg m;
        g_strLastFmt.clear();
        SynLogAppendULong(m.p(), 18446744073709551615ULL);
        CHECK(g_strLastFmt == "%lu");
        CHECK(*m.pStr == "18446744073709551615");
    }

    // ---- %g
    {
        Msg m;
        g_strLastFmt.clear();
        SynLogAppendDouble(m.p(), 1.5);
        CHECK(g_strLastFmt == "%g");
        CHECK(*m.pStr == "1.5");
        SynLogAppendDouble(m.p(), 0.25);
        CHECK(*m.pStr == "1.50.25");
    }

    // ---- the appended text piles up, because the string is never cleared
    {
        Msg m;
        SynLogAppendInt(m.p(), 1);
        SynLogAppendInt(m.p(), 2);
        SynLogAppendChar(m.p(), 'x');
        CHECK(*m.pStr == "12x");
    }

    // ---- the string overload appends the other string's contents
    {
        Msg m;
        std::string sOther = "tail";
        g_strAppendedOther.clear();
        CHECK(SynLogAppendString(m.p(), &sOther) == m.p());
        CHECK(g_strAppendedOther == "tail");
        CHECK(*m.pStr == "tail");
    }

    // ---- the predicate is a plain non-zero test on the first qword
    {
        std::vector<uint8_t> aObj(8, 0);
        CHECK(SynLogHasValue(aObj.data()) == false);
        *(uint64_t*)aObj.data() = 1;
        CHECK(SynLogHasValue(aObj.data()) == true);
        *(uint64_t*)aObj.data() = 0xFFFFFFFFFFFFFFFCULL;
        CHECK(SynLogHasValue(aObj.data()) == true);
    }

    std::printf("SYNDICATE_D65_OK: the log append family, %d checks\n", g_nChecks);
    return 0;
}
