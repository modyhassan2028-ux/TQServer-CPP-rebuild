// ===== Path-A wave 9l: 14050c490 =====
#include "MsgPortWait.h"
namespace msg {
int MessagePortWaitMessage(void* port, uint32_t timeout,
                           const SPortWaitSeams& s) {
    void* sync  = (char*)port + 0x68;
    void* event = *(void**)((char*)port + 0x20);
    s.Lock(sync);
    if (*(int*)((char*)port + 0x14) == 1) {   // stopping
        s.Unlock(sync);
        return 0;
    }
    if (*(int*)((char*)port + 0x10) == 0) {   // nothing pending yet
        s.ResetEvent(event);
        s.Unlock(sync);
        uint32_t r = s.WaitForSingleObject(event, timeout);
        if (r == kWaitObject0) {
            s.Unlock(sync);                   // RAW unlocks again
            return 1;
        }
        if (r == kWaitAbandoned) {
            s.OnAbandoned(port);              // vtable+0x30
        }
        s.Unlock(sync);
        return 0;
    }
    s.Unlock(sync);
    return 1;
}
}
