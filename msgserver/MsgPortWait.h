#ifndef MSG_PORT_WAIT_H
#define MSG_PORT_WAIT_H
// ===== Path-A wave 9l: CMessagePort::WaitMessage (14050c490) =====
// The port fields, from RAW:
//   +0x10  pending flag   (param_1[2]); non-zero -> a message waits
//   +0x14  stopped flag   (int); == 1 -> the port is shutting down
//   +0x20  the message event handle
//   +0x68  the CSyncObject used by CSingleLock
// Body, verbatim:
//   lock(+0x68)
//   +0x14 == 1            -> unlock, return 0
//   +0x10 == 0            -> ResetEvent(+0x20), unlock,
//                            r = WaitForSingleObject(+0x20, timeout)
//                            r == 0   -> unlock, return 1
//                            else     -> if r == 0x80 OnAbandoned()
//                                        (vtable+0x30; MFC maps
//                                        WAIT_ABANDONED to 0x80)
//                                        unlock, return 0
//   +0x10 != 0            -> unlock, return 1
// RAW quirk preserved: Unlock is called once BEFORE the wait and
// again after it; the second call is a no-op when already unlocked.
// Neighbours 14050c570/5d0/610/650/690 (vector iterator ops),
// 14050c6d0 (operator delete) and 14050c6e0 (allocator with the
// bad_alloc throw) are MSVC STL/CRT glue: out of scope.
#include <cstdint>
namespace msg {
static const int kPortPendingOff = 0x10;
static const int kPortStoppedOff = 0x14;
static const uint32_t kWaitAbandoned = 0x80;   // MFC WAIT_ABANDONED
static const uint32_t kWaitObject0   = 0x00;
struct SPortWaitSeams {
    void (*Lock)(void* syncObj);
    int  (*Unlock)(void* syncObj);
    int  (*ResetEvent)(void* handle);
    uint32_t (*WaitForSingleObject)(void* handle, uint32_t ms);
    void (*OnAbandoned)(void* port);           // vtable+0x30
};
// 1 = a message is available, 0 = none / stopping
int MessagePortWaitMessage(void* port, uint32_t timeout,
                           const SPortWaitSeams& s);
}
#endif
