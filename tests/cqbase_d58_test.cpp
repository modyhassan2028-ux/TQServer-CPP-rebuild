// ============================================================================
// cqbase_d58 — google::protobuf::io::ArrayInputStream, the three remaining vtable
//   slots of the class whose table base is 0x141840c40 (the brief's "0x141840c50" is
//   the +0x10 BackUp slot inside it):
//       0x1417e5ca0  BackUp(int count)          vtable +0x10
//       0x1417e5f20  Skip(int count) -> bool    vtable +0x18
//       0x1417e6050  ByteCount() -> int64       vtable +0x20
//   Every expectation below is read off objdump of those three bodies; the state is a
//   raw 0x20-byte buffer so the tests also prove the exact offsets touched.
// ============================================================================
#include "modules/syndicate/src/synpbinstream.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

// ---- the two seams, recorded ------------------------------------------------
struct CheckRec {
    const char* pszFile;
    int32_t     nLine;
    const char* pszA;
    const char* pszB;   // nullptr for the single-append form
};
static std::vector<CheckRec> g_aChecks;

static void SeamOne(const char* f, int32_t line, const char* a) {
    g_aChecks.push_back(CheckRec{f, line, a, nullptr});
}
static void SeamTwo(const char* f, int32_t line, const char* a, const char* b) {
    g_aChecks.push_back(CheckRec{f, line, a, b});
}

// ---- raw state buffer helpers (offsets from the ctor at 0x1417e5af0) --------
static const size_t kStateBytes = 0x20;
struct Raw {
    uint8_t a[kStateBytes];
    Raw() { for (size_t i = 0; i < kStateBytes; ++i) a[i] = (uint8_t)(0xA0 + i); }
    void*   p()       { return a; }
    int32_t get(int off) const { int32_t v; std::memcpy(&v, a + off, 4); return v; }
    void    set(int off, int32_t v) { std::memcpy(a + off, &v, 4); }
};

int main() {
    // the seam the ported BackUp/Skip call must not dangle during the test
    syndicate::g_pfnPbCheckFail = &SeamOne;
    g_pfnPbCheckFail2 = &SeamTwo;

    // ---- return shapes, straight from the instruction tails -----------------
    static_assert(std::is_same<decltype(SynPbArrayInBackUp((void*)nullptr, 0)), void>::value,
                  "1417e5ca0 returns nothing (add rsp,0x140 / pop rdi / ret)");
    static_assert(std::is_same<decltype(SynPbArrayInSkip((void*)nullptr, 0)), bool>::value,
                  "1417e5f20 returns al");
    static_assert(std::is_same<decltype(SynPbArrayInByteCount6050((void*)nullptr)), int64_t>::value,
                  "1417e6050 movsxd rax into a qword");

    // =====================================================================
    // 0x1417e6050 — ByteCount() == movsxd of the dword at +0x18
    // =====================================================================
    {
        Raw s;
        s.set(0x18, 0);
        CHECK(SynPbArrayInByteCount6050(s.p()) == 0);
        s.set(0x18, 7);
        CHECK(SynPbArrayInByteCount6050(s.p()) == 7);
        s.set(0x18, 0x12345678);
        CHECK(SynPbArrayInByteCount6050(s.p()) == 0x12345678);
        s.set(0x18, 0x7FFFFFFF);
        CHECK(SynPbArrayInByteCount6050(s.p()) == 2147483647LL);
        // movsxd sign-extends: a negative position comes back as a negative int64
        s.set(0x18, -1);
        CHECK(SynPbArrayInByteCount6050(s.p()) == -1LL);
        s.set(0x18, (int32_t)0x80000000u);
        CHECK(SynPbArrayInByteCount6050(s.p()) == -2147483648LL);
        // the sibling dwords are not consulted (0x14/0x1c carry junk here)
        s.set(0x18, 42);
        CHECK(SynPbArrayInByteCount6050(s.p()) == 42);
        // read-only: nothing in the state changes
        for (size_t i = 0; i < kStateBytes; ++i) {
            if (i >= 0x18 && i < 0x1c) continue;
            CHECK(s.a[i] == (uint8_t)(0xA0 + i));
        }
    }

    // =====================================================================
    // 0x1417e5f20 — Skip(int count)
    //   last_returned_size_ = 0 ; if (count > size_ - position_) { pos = size_; 0 }
    //   else { pos += count; 1 }
    // =====================================================================
    {
        // plain advance: 16-byte buffer, 4 consumed, skip 5
        Raw s;
        s.set(0x10, 16);
        s.set(0x14, 16);
        s.set(0x18, 4);
        s.set(0x1c, 9);           // must be cleared even on the success path
        g_aChecks.clear();
        CHECK(SynPbArrayInSkip(s.p(), 5) == true);
        CHECK(s.get(0x18) == 9);          // 1417e6028 add ecx,[rsp+0xa8]
        CHECK(s.get(0x1c) == 0);          // 1417e5fd9 store 0 BEFORE the range test
        CHECK(g_aChecks.empty());         // no CHECK for a legal count
        // untouched bytes, exactly: only 0x18..0x1f may differ
        CHECK(s.get(0x10) == 16);
        CHECK(s.get(0x14) == 16);
        CHECK(s.a[0x00] == 0xA0 && s.a[0x0f] == 0xAF);
        CHECK(s.get(0x14) == 16);   // block_size_ is not touched by Skip
    }
    {
        // count == exactly the remaining bytes -> jle taken, position lands on size_
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 10);
        s.set(0x1c, 3);
        g_aChecks.clear();
        CHECK(SynPbArrayInSkip(s.p(), 6) == true);
        CHECK(s.get(0x18) == 16);
        CHECK(s.get(0x1c) == 0);
        CHECK(g_aChecks.empty());
    }
    {
        // exhausted buffer: one byte too many -> clamp to size_, answer false
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 10);
        s.set(0x1c, 6);
        g_aChecks.clear();
        CHECK(SynPbArrayInSkip(s.p(), 7) == false);
        CHECK(s.get(0x18) == 16);         // 1417e6014 mov [rcx+0x18],eax(size)
        CHECK(s.get(0x1c) == 0);
        CHECK(g_aChecks.empty());         // exhaustion is NOT an error in the original
        CHECK(s.get(0x10) == 16);         // size_ itself is never rewritten
    }
    {
        // already exhausted (position_ == size_): any positive skip clamps to the same
        // value and answers false; the load-bearing quirk is position_ = size_, not -= count
        Raw s;
        s.set(0x10, 8);
        s.set(0x18, 8);
        CHECK(SynPbArrayInSkip(s.p(), 1) == false);
        CHECK(s.get(0x18) == 8);
        CHECK(SynPbArrayInSkip(s.p(), 1000) == false);
        CHECK(s.get(0x18) == 8);
    }
    {
        // count 0 -> true, position unchanged
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 5);
        s.set(0x1c, 2);
        CHECK(SynPbArrayInSkip(s.p(), 0) == true);
        CHECK(s.get(0x18) == 5);
        CHECK(s.get(0x1c) == 0);
    }
    {
        // raw quirk: Skip is bounded by size_ only, never by last_returned_size_
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 0);
        s.set(0x1c, 1);                   // previous Next() returned a single byte
        CHECK(SynPbArrayInSkip(s.p(), 15) == true);
        CHECK(s.get(0x18) == 15);
    }
    {
        // invalid count: CHECK at line 0x5c with the one literal, then the body runs on
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 8);
        s.set(0x1c, 4);
        g_aChecks.clear();
        CHECK(SynPbArrayInSkip(s.p(), -3) == true);   // -3 <= 16-8 -> "success"
        CHECK(g_aChecks.size() == 1u);
        CHECK(g_aChecks[0].nLine == 0x5c);
        CHECK(std::string(g_aChecks[0].pszFile) == kSynPbZeroCopyLiteFile);
        CHECK(std::string(g_aChecks[0].pszA) == "CHECK failed: (count) >= (0): ");
        CHECK(g_aChecks[0].pszB == nullptr);          // single append
        CHECK(s.get(0x18) == 5);                      // 8 + (-3): no rejection
        CHECK(s.get(0x1c) == 0);
    }

    // =====================================================================
    // 0x1417e5ca0 — BackUp(int count)
    //   1) last_returned_size_ <= 0   -> CHECK line 0x53, TWO literals
    //   2) count > last_returned_size_-> CHECK line 0x55
    //   3) count < 0                  -> CHECK line 0x56
    //   then position_ -= count ; last_returned_size_ = 0
    // =====================================================================
    {
        // the legal path: all three checks stay silent, both stores run
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 10);
        s.set(0x1c, 6);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), 4);
        CHECK(g_aChecks.empty());
        CHECK(s.get(0x18) == 6);          // 1417e5ee9 sub ecx,eax
        CHECK(s.get(0x1c) == 0);          // 1417e5efe store 0
        CHECK(s.get(0x10) == 16);         // size_ untouched
    }
    {
        // count == last_returned_size_ is accepted (cmp/jg is strictly greater)
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 6);
        s.set(0x1c, 6);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), 6);
        CHECK(g_aChecks.empty());
        CHECK(s.get(0x18) == 0);
        CHECK(s.get(0x1c) == 0);
    }
    {
        // nothing was handed out yet -> first CHECK, the only two-literal block
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 4);
        s.set(0x1c, 0);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), 0);
        CHECK(g_aChecks.size() == 1u);
        CHECK(g_aChecks[0].nLine == 0x53);
        CHECK(std::string(g_aChecks[0].pszFile) == kSynPbZeroCopyLiteFile);
        CHECK(std::string(g_aChecks[0].pszA) ==
              "CHECK failed: (last_returned_size_) > (0): ");
        CHECK(g_aChecks[0].pszB != nullptr);
        CHECK(std::string(g_aChecks[0].pszB) ==
              "BackUp() can only be called after a successful Next().");
        // the body still falls through to the stores, exactly as the instructions do
        CHECK(s.get(0x18) == 4);
        CHECK(s.get(0x1c) == 0);
    }
    {
        // a negative last_returned_size_ also trips check 1 (cmp 0 / jle)
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 9);
        s.set(0x1c, -1);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), 0);
        // the first CHECK fires (last_returned_size_ <= 0) and the body keeps going, so
        // count 0 > -1 trips the second CHECK too: two reports, lines 0x53 then 0x55
        CHECK(g_aChecks.size() == 2u);
        CHECK(g_aChecks[0].nLine == 0x53);
        CHECK(g_aChecks[1].nLine == 0x55);
        CHECK(s.get(0x18) == 9);
    }
    {
        // count larger than what Next() returned -> check 2, line 0x55, one literal
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 12);
        s.set(0x1c, 3);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), 4);
        CHECK(g_aChecks.size() == 1u);
        CHECK(g_aChecks[0].nLine == 0x55);
        CHECK(std::string(g_aChecks[0].pszFile) == kSynPbZeroCopyLiteFile);
        CHECK(std::string(g_aChecks[0].pszA) ==
              "CHECK failed: (count) <= (last_returned_size_): ");
        CHECK(g_aChecks[0].pszB == nullptr);
        CHECK(s.get(0x18) == 8);          // 12 - 4 still applied
        CHECK(s.get(0x1c) == 0);
    }
    {
        // negative count -> check 3, line 0x56, one literal
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 8);
        s.set(0x1c, 5);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), -2);
        CHECK(g_aChecks.size() == 1u);
        CHECK(g_aChecks[0].nLine == 0x56);
        CHECK(std::string(g_aChecks[0].pszFile) == kSynPbZeroCopyLiteFile);
        CHECK(std::string(g_aChecks[0].pszA) == "CHECK failed: (count) >= (0): ");
        CHECK(g_aChecks[0].pszB == nullptr);
        CHECK(s.get(0x18) == 10);         // 8 - (-2): the sub wraps upward
        CHECK(s.get(0x1c) == 0);
    }
    {
        // all three fire in instruction order 0x53 -> 0x55 -> 0x56
        Raw s;
        s.set(0x10, 16);
        s.set(0x18, 5);
        s.set(0x1c, -7);
        g_aChecks.clear();
        SynPbArrayInBackUp(s.p(), -50);
        // count -50 is not greater than -7, so the middle CHECK stays quiet: 0x53 then 0x56
        CHECK(g_aChecks.size() == 2u);
        CHECK(g_aChecks[0].nLine == 0x53);
        CHECK(g_aChecks[1].nLine == 0x56);
        CHECK(s.get(0x18) == 55);         // 5 - (-50), still stored
        CHECK(s.get(0x1c) == 0);
    }
    {
        // BackUp does not look at size_ or block_size_ at all: they stay as written
        Raw s;
        s.set(0x10, 0x11111111);
        s.set(0x14, 0x22222222);
        s.set(0x18, 7);
        s.set(0x1c, 7);
        SynPbArrayInBackUp(s.p(), 7);
        CHECK(s.get(0x10) == 0x11111111);
        CHECK(s.get(0x14) == 0x22222222);
        CHECK(s.get(0x18) == 0);
        CHECK(s.get(0x1c) == 0);
        // the two fields that were written above are what must survive; the fill pattern
        // cannot apply to them, which is why this block asserts the values instead
    }

    // ---- a Next()/BackUp()/Skip() walk over one real buffer -----------------
    {
        const char szBuf[] = "0123456789abcdef";
        SynPbArrayInputStreamState st{};
        st.pBuffer = szBuf;
        st.nSize = 16;
        st.nBlockSize = 16;
        st.nPosition = 0;
        st.nLastReturnedSize = 0;
        // Next() handed out [0,8)
        st.nLastReturnedSize = 8;
        st.nPosition = 8;
        CHECK(SynPbArrayInByteCount6050(&st) == 8);
        SynPbArrayInBackUp(&st, 3);                 // give 3 back
        CHECK(st.nPosition == 5);
        CHECK(st.nLastReturnedSize == 0);
        CHECK(SynPbArrayInSkip(&st, 15) == false);  // 15 > 16-5: clamps to the end
        CHECK(st.nPosition == 16);
        CHECK(SynPbArrayInByteCount6050(&st) == 16);
        CHECK(SynPbArrayInSkip(&st, 1) == false);   // exhausted
        CHECK(st.nPosition == 16);
        CHECK(SynPbArrayInByteCount6050(&st) == 16);
    }

    std::printf("SYNDICATE_D58_OK: ArrayInputStream BackUp/Skip/ByteCount "
                "(0x1417e5ca0, 0x1417e5f20, 0x1417e6050), %d checks\n", g_nChecks);
    return 0;
}
