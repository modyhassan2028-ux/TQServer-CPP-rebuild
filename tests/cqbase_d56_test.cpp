// ============================================================================
// cqbase_d56 — the last slots of the three protobuf io stream classes and the four
//   numeric-limit statics. The byte-count offsets (+0x18, +0x2c, the std::string at +8)
//   come from the instructions, and the aliasing refusal carries the exact literals.
// ============================================================================
#include "modules/syndicate/src/synpbio.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nLogs = 0;
int g_nSeverity = -1;
int g_nLine = -1;
std::string g_strFile, g_strMessage;
void LogHook(int nSeverity, const char* pszFile, int nLine, const char* pszMessage) {
    ++g_nLogs; g_nSeverity = nSeverity; g_nLine = nLine;
    g_strFile = pszFile; g_strMessage = pszMessage;
}

}  // namespace

int main() {
    g_fnPbLogAliasing = &LogHook;

    // ---- the three byte counts, each off its own offset
    {
        std::vector<uint8_t> aIn(0x40, 0);
        *(int32_t*)(aIn.data() + 0x18) = 0x1234;
        CHECK(SynPbArrayInByteCount(aIn.data()) == 0x1234);

        std::vector<uint8_t> aOut(0x40, 0);
        std::string sBuf(7, 'z');
        *(void**)(aOut.data() + 0x08) = &sBuf;
        CHECK(SynPbArrayOutByteCount(aOut.data()) == 7);
        sBuf.assign(21, 'z');
        CHECK(SynPbArrayOutByteCount(aOut.data()) == 21);

        std::vector<uint8_t> aCopy(0x40, 0);
        *(int64_t*)(aCopy.data() + 0x18) = 0x1000;
        *(int32_t*)(aCopy.data() + 0x2c) = 0x35;
        CHECK(SynPbCopyingByteCount(aCopy.data()) == 0x1035);
        *(int32_t*)(aCopy.data() + 0x2c) = -1;            // the low part is a signed int
        CHECK(SynPbCopyingByteCount(aCopy.data()) == 0xfff);
    }

    // ---- the constant slot
    CHECK(SynPbSlotFalse() == false);

    // ---- the aliasing refusal: severity 3, line 0x31, the exact literals, false back
    {
        g_nLogs = 0;
        CHECK(SynPbAliasingRefusal() == false);
        CHECK(g_nLogs == 1);
        CHECK(g_nSeverity == 3);
        CHECK(g_nLine == 0x31);
        CHECK(g_strFile == "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream.cc");
        CHECK(g_strMessage ==
              "This ZeroCopyOutputStream doesn't support aliasing. Reaching here usually means a "
              "ZeroCopyOutputStream implementation bug.");
    }

    // ---- the four statics write INT_MAX into their own global only
    g_nSynLimit7c = g_nSynLimit80 = g_nSynLimit84 = g_nSynLimit88 = 0;
    SynLimitInit7c();
    CHECK(g_nSynLimit7c == 2147483647);
    CHECK(g_nSynLimit80 == 0 && g_nSynLimit84 == 0 && g_nSynLimit88 == 0);
    SynLimitInit80();
    CHECK(g_nSynLimit80 == 2147483647);
    SynLimitInit84();
    CHECK(g_nSynLimit84 == 2147483647);
    SynLimitInit88();
    CHECK(g_nSynLimit88 == 2147483647);
    CHECK(std::numeric_limits<int>::max() == 2147483647);

    std::printf("SYNDICATE_D56_OK: three io stream slots, the refusal and four statics, %d checks\n",
                g_nChecks);
    return 0;
}
