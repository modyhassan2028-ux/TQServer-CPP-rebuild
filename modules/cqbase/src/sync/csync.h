// ============================================================================
// csync.h — RAW CQBase.dll v6159 · the locking primitives of tq
//   CMyCriticalSection   +0x00 vftable, +0x08 the 40 byte critical section
//   CMutexLock           +0x00 vftable, +0x08 the handle
//   CMyEvent             +0x00 the handle (there is no vftable)
//   CMyMultiEvent        +0x00 count, +0x08 the handle array
//   CMySingleLock        +0x00 the ILockObj pointer it forwards to
//   The Win32 entry points are seams so the units can run off Windows; on
//   Windows the defaults are the real calls.
// ============================================================================
#ifndef CQBASE_SYNC_CSYNC_H
#define CQBASE_SYNC_CSYNC_H

#include <cstdint>

namespace tq {

// what the locks reach for
struct SyncApi {
    void (*pfnEnterCS)(void* pCs);
    void (*pfnLeaveCS)(void* pCs);
    uint32_t (*pfnWaitSingle)(void* h, uint32_t nMs);
    bool (*pfnReleaseMutex)(void* h);
    bool (*pfnSetEvent)(void* h);
    uint32_t (*pfnWaitMulti)(uint32_t nCount, void** ph, bool bWaitAll, uint32_t nMs);
};
extern SyncApi g_SyncApi;
constexpr uint32_t kWaitObject0 = 0;        // WAIT_OBJECT_0
constexpr uint32_t kWaitTimeout = 0x102;    // WAIT_TIMEOUT
constexpr int kWaitTimeoutCode = 0x7fffffff;
constexpr int kWaitFailCode = -1;

// ILockObj — only the virtual at +0x10 is used by CMySingleLock
class ILockObj {
public:
    virtual void UnlockVt4() {}   // +0x08
    virtual void Unlock() {}      // +0x10, the slot CMySingleLock::Unlock calls
    virtual ~ILockObj() {}
};

class CMyCriticalSection : public ILockObj {
public:
    uint8_t abCs[40];        // +0x08, the CRITICAL_SECTION body
    void Lock();             // 0x140ba0060
    void Unlock() override;  // 0x140ba0070
};

class CMutexLock : public ILockObj {
public:
    void* hMutex;            // +0x08
    void Lock();             // 0x140ba0110
    void Unlock() override;  // 0x140ba0130
};

class CMyEvent {
public:
    void* hEvent;            // +0x00
    int Signal();            // 0x140ba0190
    int Wait(int nMs);       // 0x140ba01b0
};

class CMyMultiEvent {
public:
    int nCount;              // +0x00
    void** phEvents;         // +0x08
    int Signal(int nIndex);  // 0x140ba02e0
    int Wait(int nMs);       // 0x140ba0320
};

class CMySingleLock {
public:
    ILockObj* pLock;         // +0x00
    void Unlock();           // 0x140ba0390
};

}  // namespace tq
#endif
