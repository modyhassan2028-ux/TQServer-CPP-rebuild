// ============================================================================
// cqbase_d63 — the whole CopyingInputStreamAdaptor class (vtable 0x141840d68).
//   A fake underlying stream records exactly when the adaptor touches it, which is how the
//   backup-first paths are proved: Next with a pending backup must not read, Skip must take
//   the backup before asking the stream, and a negative read must set at_end_.
// ============================================================================
#include "modules/syndicate/src/synpbadaptor.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

// ---- the fake underlying CopyingInputStream: vt[1] = Read, vt[2] = Skip
int g_nReads = 0, g_nSkips = 0;
std::string g_strSource = "0123456789";
size_t g_nCursor = 0;
bool g_bFailRead = false;           // makes the fake answer -1 once
int32_t g_nLastSkip = -1;

int32_t FakeRead(void* pSelf, void* pBuf, int32_t nSize) {
    (void)pSelf; ++g_nReads;
    if (g_bFailRead) {
        g_bFailRead = false;
        return -1;
    }
    int32_t nLeft = (int32_t)(g_strSource.size() - g_nCursor);
    int32_t n = nSize < nLeft ? nSize : nLeft;
    if (n > 0) {
        std::memcpy(pBuf, g_strSource.data() + g_nCursor, (size_t)n);
        g_nCursor += (size_t)n;
    }
    return n;
}
bool FakeSkip(void* pSelf, int32_t nCount) {
    (void)pSelf; ++g_nSkips; g_nLastSkip = nCount;
    int32_t nLeft = (int32_t)(g_strSource.size() - g_nCursor);
    if (nCount > nLeft) { g_nCursor = g_strSource.size(); return false; }
    g_nCursor += (size_t)nCount;
    return true;
}
void* g_aStreamVt[4];

std::vector<uint8_t> g_aBuffer;
void* BufferHook(void* pHolder) { (void)pHolder; return g_aBuffer.empty() ? nullptr : g_aBuffer.data(); }
int g_n7140 = 0, g_n7190 = 0, g_nBodyDtors = 0, g_nFrees = 0;
void Hook7140(void*) { ++g_n7140; }
void Hook7190(void*) { ++g_n7190; }
void HookBody(void*) { ++g_nBodyDtors; }
void HookFree(void*) { ++g_nFrees; }

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

// the adaptor state at the exact offsets
struct Adaptor {
    std::vector<uint8_t> a;
    Adaptor() : a(0x40, 0) {}
    uint8_t* p() { return a.data(); }
    void set(int nOff, int32_t v) { *(int32_t*)(a.data() + nOff) = v; }
    int32_t get(int nOff) { return *(int32_t*)(a.data() + nOff); }
    void set64(int nOff, int64_t v) { *(int64_t*)(a.data() + nOff) = v; }
    int64_t get64(int nOff) { return *(int64_t*)(a.data() + nOff); }
    void setp(int nOff, void* pv) { *(void**)(a.data() + nOff) = pv; }
};

void Reset() {
    g_strSource = "0123456789";     // the zero-read case empties it, so every block restores it
    g_nReads = g_nSkips = g_n7140 = g_n7190 = 0;
    g_nCursor = 0;
    g_bFailRead = false;
    g_nLastSkip = -1;
    g_aRecs.clear();
}

}  // namespace

int main() {
    g_fnPbBuffer = &BufferHook;
    g_fnPb7140 = &Hook7140;
    g_fnPb7190 = &Hook7190;
    g_fnPb6AD0 = &HookBody;
    g_fnPbAdaptorFree = &HookFree;
    g_fnPbAdaptorCheck1 = &Check1;
    g_fnPbAdaptorCheck2 = &Check2;
    g_aStreamVt[1] = (void*)&FakeRead;
    g_aStreamVt[2] = (void*)&FakeSkip;

    // the underlying stream object: its first qword is the vtable pointer
    struct StreamObj { void** ppVt; };
    StreamObj stream;
    stream.ppVt = g_aStreamVt;

    // ---- Next with no backup reads the stream into the buffer
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x28, 8);        // buffer_size_
        ad.set64(0x18, 0);      // byte_count_
        void* pData = nullptr;
        int32_t nSize = 0;
        CHECK(SynPbAdaptorNext(ad.p(), &pData, &nSize) == true);
        CHECK(g_nReads == 1 && g_nSkips == 0);
        CHECK(nSize == 8);
        CHECK(pData == g_aBuffer.data());
        CHECK(ad.get(0x2c) == 8);           // buffer_used_
        CHECK(ad.get64(0x18) == 8);         // byte_count_ grew by the read
        CHECK(g_n7140 == 1);                // the bookkeeping call happened
        CHECK(std::memcmp(g_aBuffer.data(), "01234567", 8) == 0);
    }

    // ---- a pending backup is served out of the buffer without touching the stream
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x28, 8);
        ad.set(0x2c, 8);        // buffer_used_
        ad.set(0x30, 3);        // backup_
        void* pData = nullptr;
        int32_t nSize = 0;
        CHECK(SynPbAdaptorNext(ad.p(), &pData, &nSize) == true);
        CHECK(g_nReads == 0);
        CHECK(nSize == 3);
        CHECK(pData == g_aBuffer.data() + 5);   // buffer + used - backup
        CHECK(ad.get(0x30) == 0);               // consumed
    }

    // ---- a zero read answers false and runs the finisher, without setting at_end_
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x28, 8);
        g_strSource.clear();            // an empty source reads 0
        void* pData = nullptr;
        int32_t nSize = 0;
        CHECK(SynPbAdaptorNext(ad.p(), &pData, &nSize) == false);
        CHECK(ad.p()[0x11] == 0);       // zero is not a failure
        CHECK(g_n7190 == 1);
    }

    // ---- a negative read sets at_end_ and poisons every later call
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x28, 8);
        g_bFailRead = true;             // the fake answers -1 on this call
        void* pData = nullptr;
        int32_t nSize = 0;
        CHECK(SynPbAdaptorNext(ad.p(), &pData, &nSize) == false);
        CHECK(ad.p()[0x11] == 1);
        CHECK(g_n7190 == 1);
        // the next call refuses before any read
        g_nReads = 0;
        CHECK(SynPbAdaptorNext(ad.p(), &pData, &nSize) == false);
        CHECK(g_nReads == 0);
    }

    // ---- BackUp: the three CHECKs in instruction order, then the store
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x28, 8);
        ad.set(0x2c, 8);
        ad.set(0x30, 0);
        SynPbAdaptorBackUp(ad.p(), 4);
        CHECK(g_aRecs.empty());
        CHECK(ad.get(0x30) == 4);

        // backup_ != 0 trips 0x10c with both literals
        g_aRecs.clear();
        SynPbAdaptorBackUp(ad.p(), 1);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x10c);
        CHECK(g_aRecs[0].a == "CHECK failed: backup_bytes_ == 0 && buffer_.get() != NULL: ");
        CHECK(g_aRecs[0].b == " BackUp() can only be called after Next().");

        // count above buffer_used_ trips 0x10e
        ad.set(0x30, 0);
        g_aRecs.clear();
        SynPbAdaptorBackUp(ad.p(), 9);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x10e);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) <= (buffer_used_): ");

        // the failed call above still stored its count, so clear backup_ before the next case
        ad.set(0x30, 0);
        // a negative count trips 0x111
        g_aRecs.clear();
        SynPbAdaptorBackUp(ad.p(), -1);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x111);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) >= (0): ");
        CHECK(g_aRecs[0].b == " Parameter to BackUp() can't be negative.");
        CHECK(ad.get(0x30) == -1);       // the store still runs
    }

    // ---- a null buffer trips the same first CHECK
    {
        Reset();
        g_aBuffer.clear();
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x30, 0);
        g_aRecs.clear();
        SynPbAdaptorBackUp(ad.p(), 0);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x10c);
    }

    // ---- Skip: the backup absorbs what it can, then the stream is asked
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.set(0x30, 5);            // backup_ 5
        CHECK(SynPbAdaptorSkip(ad.p(), 3) == true);
        CHECK(ad.get(0x30) == 2);   // 5 - 3, no stream call
        CHECK(g_nSkips == 0);

        // now a skip larger than the backup drains it and asks the stream for the rest.
        // RAW quirk: the body compares the stream's answer (a bool, so 0 or 1) with the number
        // of bytes it asked for, so the call only answers true when exactly one byte was left
        g_nCursor = 0;
        CHECK(SynPbAdaptorSkip(ad.p(), 5) == false);
        CHECK(g_nSkips == 1);
        CHECK(g_nLastSkip == 3);    // 5 - 2 left over
        CHECK(ad.get(0x30) == 0);
        CHECK(ad.get64(0x18) == 1); // byte_count_ + the stream's answer

        // with exactly one byte left over the same comparison answers true
        ad.set(0x30, 4);
        g_nCursor = 0;
        CHECK(SynPbAdaptorSkip(ad.p(), 5) == true);
        CHECK(g_nLastSkip == 1);
    }

    // ---- Skip refuses after at_end_, and reports a negative count first
    {
        Reset();
        g_aBuffer.assign(8, 0);
        Adaptor ad;
        ad.setp(0x08, &stream);
        ad.p()[0x11] = 1;
        CHECK(SynPbAdaptorSkip(ad.p(), 1) == false);
        CHECK(g_nSkips == 0);

        ad.p()[0x11] = 0;
        g_aRecs.clear();
        SynPbAdaptorSkip(ad.p(), -2);
        CHECK(g_aRecs.size() == 1);
        CHECK(g_aRecs[0].nLine == 0x118);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) >= (0): ");
    }

    // ---- ByteCount is byte_count_ minus the pending backup
    {
        Adaptor ad;
        ad.set64(0x18, 100);
        ad.set(0x30, 9);
        CHECK(SynPbAdaptorByteCount(ad.p()) == 91);
        ad.set(0x30, 0);
        CHECK(SynPbAdaptorByteCount(ad.p()) == 100);
    }

    // ---- the deleting destructor: body first, the free only on bit 0
    {
        Adaptor ad;
        g_nBodyDtors = g_nFrees = 0;
        CHECK(SynPbAdaptorDeletingDtor(ad.p(), 0) == ad.p());
        CHECK(g_nBodyDtors == 1 && g_nFrees == 0);
        SynPbAdaptorDeletingDtor(ad.p(), 1);
        CHECK(g_nBodyDtors == 2 && g_nFrees == 1);
        SynPbAdaptorDeletingDtor(ad.p(), 0x100);
        CHECK(g_nFrees == 1);            // only bit 0 frees
    }

    std::printf("SYNDICATE_D63_OK: the whole CopyingInputStreamAdaptor, %d checks\n", g_nChecks);
    return 0;
}
