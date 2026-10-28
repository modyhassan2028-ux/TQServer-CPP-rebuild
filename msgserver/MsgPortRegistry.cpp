// ===== Path-A wave 9k: 14050c410 =====
#include "MsgPortRegistry.h"
namespace msg {
int MessagePortInit(void* port, const SPortInitSeams& s) {
    void* sync = (char*)port + kPortSyncObjOff;
    s.Lock(sync);                       // CSingleLock(..., TRUE)
    void* ev = s.CreateEvent(nullptr, 0, 0, nullptr);
    *(void**)((char*)port + kPortEventOff) = ev;
    if (ev != nullptr) {
        s.Unlock(sync);
        return 1;
    }
    unsigned err = (unsigned)s.GetLastError();
    if (s.LogInitFail != nullptr) {
        s.LogInitFail(s.PortId ? s.PortId(port) : 0, err);
    }
    s.Unlock(sync);
    return 0;
}
}
