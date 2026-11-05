// ============================================================================
// cqbase_d59 — the two output-stream BackUp bodies. Each state offset (+0x28 buffer_size_,
//   +0x2c buffer_used_, the std::string at +0x8) and each CHECK line/literal comes from the
//   instructions; the tests assert the report order and the stores that follow it.
// ============================================================================
#include "modules/syndicate/src/synpboutstream.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

struct Rec { int32_t nLine; std::string a, b; };
std::vector<Rec> g_aRecs;
void Check1(const char* pszFile, int32_t nLine, const char* pszA) {
    g_aRecs.push_back(Rec{nLine, pszA ? pszA : "", ""});
    assert(pszFile && std::strstr(pszFile, "zero_copy_stream_impl_lite.cc"));
}
void Check2(const char* pszFile, int32_t nLine, const char* pszA, const char* pszB) {
    g_aRecs.push_back(Rec{nLine, pszA ? pszA : "", pszB ? pszB : ""});
    assert(pszFile && std::strstr(pszFile, "zero_copy_stream_impl_lite.cc"));
}

}  // namespace

int main() {
    g_fnPbOutCheck1 = &Check1;
    g_fnPbOutCheck2 = &Check2;

    // ---- StringOutputStream: a legal back-up resizes the target
    {
        std::vector<uint8_t> aSelf(0x20, 0);
        std::string sTarget = "0123456789";
        *(void**)(aSelf.data() + 0x08) = &sTarget;
        g_aRecs.clear();
        SynPbStringOutBackUp(aSelf.data(), 3);
        CHECK(g_aRecs.empty());
        CHECK(sTarget == "0123456");
        CHECK(sTarget.size() == 7);

        // backing up everything leaves an empty target
        SynPbStringOutBackUp(aSelf.data(), 7);
        CHECK(sTarget.empty());
        CHECK(g_aRecs.empty());
    }

    // ---- StringOutputStream: a negative count reports line 0xbc and still resizes
    {
        std::vector<uint8_t> aSelf(0x20, 0);
        std::string sTarget = "abcd";
        *(void**)(aSelf.data() + 0x08) = &sTarget;
        g_aRecs.clear();
        bool bThrew = false;
        try { SynPbStringOutBackUp(aSelf.data(), -2); }
        catch (const std::length_error&) { bThrew = true; }
        // the negative trips 0xbc, and the very same value then fails the UNSIGNED size
        // compare, so 0xbd follows: two reports, then the resize still runs
        CHECK(g_aRecs.size() == 2);
        CHECK(g_aRecs[0].nLine == 0xbc);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) >= (0): ");
        CHECK(g_aRecs[0].b.empty());
        CHECK(g_aRecs[1].nLine == 0xbd);
        // the resize still runs: size - (-2) in unsigned arithmetic is 6, so the target
        // grows by two fill bytes and the four letters survive
        CHECK(!bThrew);
        CHECK(sTarget.size() == 6);
        CHECK(sTarget.compare(0, 4, "abcd") == 0);
    }

    // ---- StringOutputStream: backing up past the end reports line 0xbd, then the
    //      wrapped size - count cannot be held, so the resize throws exactly as MSVCP90's
    //      does. Only count <= size is a legal call.
    {
        std::vector<uint8_t> aSelf(0x20, 0);
        std::string sTarget = "abc";
        *(void**)(aSelf.data() + 0x08) = &sTarget;
        g_aRecs.clear();
        bool bThrew = false;
        try { SynPbStringOutBackUp(aSelf.data(), 4); }
        catch (const std::length_error&) { bThrew = true; }
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0xbd);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) <= (target_->size()): ");
        CHECK(bThrew);
        CHECK(sTarget == "abc");

        // the boundary itself is legal: count == size empties the target
        g_aRecs.clear();
        SynPbStringOutBackUp(aSelf.data(), 3);
        CHECK(g_aRecs.empty());
        CHECK(sTarget.empty());
    }

    // ---- CopyingOutputStreamAdaptor: a legal back-up lowers buffer_used_
    {
        std::vector<uint8_t> aSelf(0x40, 0);
        *(int32_t*)(aSelf.data() + 0x28) = 0x40;   // buffer_size_
        *(int32_t*)(aSelf.data() + 0x2c) = 0x40;   // buffer_used_, so the equality holds
        g_aRecs.clear();
        SynPbCopyingAdaptorBackUp(aSelf.data(), 0x10);
        CHECK(g_aRecs.empty());
        CHECK(*(int32_t*)(aSelf.data() + 0x2c) == 0x30);
        CHECK(*(int32_t*)(aSelf.data() + 0x28) == 0x40);
    }

    // ---- the equality check: buffer_used_ != buffer_size_ reports line 0x166, both literals
    {
        std::vector<uint8_t> aSelf(0x40, 0);
        *(int32_t*)(aSelf.data() + 0x28) = 0x40;
        *(int32_t*)(aSelf.data() + 0x2c) = 0x20;
        g_aRecs.clear();
        SynPbCopyingAdaptorBackUp(aSelf.data(), 4);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x166);
        CHECK(g_aRecs[0].a == "CHECK failed: (buffer_used_) == (buffer_size_): ");
        CHECK(g_aRecs[0].b == " BackUp() can only be called after Next().");
        CHECK(*(int32_t*)(aSelf.data() + 0x2c) == 0x1c);   // the store still runs
    }

    // ---- the range check: count above buffer_used_ reports line 0x168
    {
        std::vector<uint8_t> aSelf(0x40, 0);
        *(int32_t*)(aSelf.data() + 0x28) = 0x10;
        *(int32_t*)(aSelf.data() + 0x2c) = 0x10;
        g_aRecs.clear();
        SynPbCopyingAdaptorBackUp(aSelf.data(), 0x11);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x168);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) <= (buffer_used_): ");
        CHECK(g_aRecs[0].b ==
              " Can't back up over more bytes than were returned by the last call to Next().");
        CHECK(*(int32_t*)(aSelf.data() + 0x2c) == -1);     // 0x10 - 0x11, plain 32-bit wrap
    }

    // ---- a negative count reports 0x165 first, then the other checks in instruction order
    {
        std::vector<uint8_t> aSelf(0x40, 0);
        *(int32_t*)(aSelf.data() + 0x28) = 0x10;
        *(int32_t*)(aSelf.data() + 0x2c) = 0x0;            // differs: 0x166 fires next
        g_aRecs.clear();
        SynPbCopyingAdaptorBackUp(aSelf.data(), -5);
        CHECK(g_aRecs.size() == 2);
        CHECK(g_aRecs[0].nLine == 0x165);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) >= (0): ");
        CHECK(g_aRecs[1].nLine == 0x166);                  // count -5 is not above 0
        CHECK(*(int32_t*)(aSelf.data() + 0x2c) == 5);      // 0 - (-5)
    }

    std::printf("SYNDICATE_D59_OK: the two output-stream BackUp bodies, %d checks\n", g_nChecks);
    return 0;
}
