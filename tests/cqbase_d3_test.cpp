// D3 (CQBase) — tq::CStringPacker and the locking primitives
#include "modules/cqbase/src/cstrpacker.h"
#include "modules/cqbase/src/csync.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace tq;

static int g_nEnter = 0, g_nLeave = 0, g_nWait = 0, g_nRelease = 0, g_nSet = 0;
static void* g_pLastHandle = nullptr;
static uint32_t g_uWaitResult = 0;
static void HookEnter(void*) { g_nEnter++; }
static void HookLeave(void*) { g_nLeave++; }
static uint32_t HookWaitOne(void* h, uint32_t) { g_nWait++; g_pLastHandle = h; return g_uWaitResult; }
static bool HookRelease(void*) { g_nRelease++; return true; }
static bool HookSet(void* h) { g_nSet++; g_pLastHandle = h; return true; }
static uint32_t HookWaitMany(uint32_t, void**, bool, uint32_t) { return g_uWaitResult; }

int main() {
    g_SyncApi = SyncApi{ HookEnter, HookLeave, HookWaitOne, HookRelease, HookSet, HookWaitMany };

    // ---------------- CStringPacker
    static int s_aVft[3] = { 0 };
    g_pVftCStringPacker = (void*)s_aVft;
    CStringPacker pk;
    assert(pk.pBuf == nullptr && pk.pVft == (void**)g_pVftCStringPacker);
    assert(pk.AddString("x") == false);              // no buffer at all

    char abBuf[64];
    pk.SetBuf(abBuf, sizeof(abBuf), true);
    assert(abBuf[0] == 0 && abBuf[63] == 0);
    assert(pk.GetStrAmount() == 0);
    assert(pk.GetSize() == 1);                        // only the count byte

    // ---- three strings: the count, then length prefixed entries
    assert(pk.AddString("abc") == true);
    assert(pk.GetStrAmount() == 1);
    assert(pk.GetSize() == 5);                        // 1 + (1+3)
    assert(pk.AddString("") == true);                 // the empty string is legal
    assert(pk.GetStrAmount() == 2);
    assert(pk.GetSize() == 6);                        // 1 + (1+3) + (1+0)
    assert(pk.AddString("de") == true);
    assert(pk.GetSize() == 9);
    assert(abBuf[0] == 3);
    assert(abBuf[1] == 3 && std::memcmp(abBuf + 2, "abc", 3) == 0);
    assert(abBuf[5] == 0);
    assert(abBuf[6] == 2 && std::memcmp(abBuf + 7, "de", 2) == 0);

    // ---- a null string bumps the count and writes one terminator, and the
    // next real string lands after it
    assert(pk.AddString(nullptr) == true);
    assert(pk.GetStrAmount() == 4);

    // ---- reading back: the index is found by walking, the size is a <= test
    char abOut[16];
    assert(pk.GetString(0, abOut, sizeof(abOut)) == true);
    assert(std::strcmp(abOut, "abc") == 0);
    assert(pk.GetString(1, abOut, sizeof(abOut)) == true);
    assert(abOut[0] == '\0');                         // the empty string
    assert(pk.GetString(2, abOut, sizeof(abOut)) == true);
    assert(std::strcmp(abOut, "de") == 0);
    assert(pk.GetString(3, abOut, sizeof(abOut)) == true);   // the null entry
    assert(abOut[0] == '\0');
    assert(pk.GetString(4, abOut, sizeof(abOut)) == false);  // past the count
    // the caller size refuses a full fit: three characters need more than three
    assert(pk.GetString(0, abOut, 3) == false);
    assert(pk.GetString(0, abOut, 4) == true);
    // the output is cleared before anything is decided
    std::memset(abOut, 0x7F, sizeof(abOut));
    assert(pk.GetString(9, abOut, sizeof(abOut)) == false);
    assert(abOut[0] == 0);

    // ---- a buffer too small refuses the string instead of overrunning
    char abSmall[8];
    CStringPacker pk2;
    pk2.SetBuf(abSmall, sizeof(abSmall), true);
    assert(pk2.AddString("abcdefgh") == false);        // 1 + 1 + 8 > 8
    assert(abSmall[0] == 0);                           // nothing was written
    assert(pk2.AddString("abcdef") == true);           // 1 + 1 + 6 == 8 fits

    // ---- a string of 0x100 bytes is refused before the buffer is consulted
    char abLong[300];
    std::memset(abLong, 'a', 299);
    abLong[299] = '\0';
    assert(pk2.AddString(abLong) == false);

    // ---- copy construction shares the buffer, assignment copies both fields
    CStringPacker pk3(pk);
    assert(pk3.pBuf == pk.pBuf && pk3.nBufSize == pk.nBufSize);
    CStringPacker pk4;
    pk4 = pk;
    assert(pk4.pBuf == pk.pBuf && pk4.nBufSize == pk.nBufSize);
    // SetBuf without the clear flag leaves the bytes alone
    char abKeep[8] = { 9, 8, 7, 6, 5, 4, 3, 2 };
    pk4.SetBuf(abKeep, sizeof(abKeep), false);
    assert(abKeep[0] == 9);

    // ---------------- the locking primitives
    CMyCriticalSection cs(2000);      // the spin count is accepted and ignored
    cs.Lock();
    assert(g_nEnter == 1);
    cs.Unlock();
    assert(g_nLeave == 1);

    CMutexLock mx;
    mx.hMutex = nullptr;
    mx.Lock();                                        // a null handle is skipped
    assert(g_nWait == 0);
    mx.Unlock();
    assert(g_nRelease == 0);
    int nFake = 0;
    mx.hMutex = &nFake;
    mx.Lock();
    assert(g_nWait == 1 && g_pLastHandle == &nFake);
    mx.Unlock();
    assert(g_nRelease == 1);

    // ---- CMyEvent: zero answers zero, the timeout becomes the marker
    CMyEvent ev;
    ev.hEvent = &nFake;
    assert(ev.Signal() == 0);
    assert(g_nSet == 1);
    g_uWaitResult = kWaitObject0;
    assert(ev.Wait(10) == 0);
    g_uWaitResult = kWaitTimeout;
    assert(ev.Wait(10) == kWaitTimeoutCode);
    g_uWaitResult = 0x80;                             // a failure value
    assert(ev.Wait(10) == -1);

    // ---- CMyMultiEvent: the guards on Signal, and the Wait arithmetic
    void* apHandles[3] = { &nFake, (void*)0x10, nullptr };
    CMyMultiEvent me;
    me.nCount = 3;
    me.phEvents = apHandles;
    assert(me.Signal(-1) == -1);
    assert(me.Signal(3) == -1);
    assert(me.Signal(2) == -1);                       // the handle is null
    assert(me.Signal(1) == 0);
    assert(g_pLastHandle == (void*)0x10);
    me.phEvents = nullptr;
    assert(me.Signal(0) == -1);
    me.phEvents = apHandles;
    g_uWaitResult = 1;                                // inside the count
    assert(me.Wait(5) == 1);
    g_uWaitResult = kWaitTimeout;
    assert(me.Wait(5) == kWaitTimeoutCode);           // the timeout marker
    g_uWaitResult = 5;                                // past the count
    assert(me.Wait(5) == -1);                         // the failed arm

    // ---- CMySingleLock forwards to the object it holds
    struct CountingLock : ILockObj {
        int nLock = 0;
        int nUnlock = 0;
        void Lock() override { nLock++; }
        void Unlock() override { nUnlock++; }
    } lock;
    {
        CMySingleLock single(&lock);  // construction takes the slot at +0x08
        assert(lock.nLock == 1 && lock.nUnlock == 0);
    }
    assert(lock.nUnlock == 1);        // destruction takes the one at +0x10

    printf("CQBASE_D3_OK: CStringPacker, critical section, mutex, event, "
           "multi event, single lock\n");
    return 0;
}
