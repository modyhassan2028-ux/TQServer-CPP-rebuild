#ifndef MSG_PORT_REGISTRY_H
#define MSG_PORT_REGISTRY_H
// ===== Path-A wave 9k: the message-port registry + CMessagePort::Init =====
// 14050c340 Get(idx)   — the global vector at DAT_140976740 with
//                        count = (end - begin) >> 3; idx < 0 or
//                        idx >= count returns 0. This is the exact
//                        call the monitor uses as 14050c340(5).
// 14050c3f0 Count()    — (DAT_140976748 - DAT_140976740) >> 3.
// 14050c410 Init()     — CSingleLock on the CSyncObject at +0x68,
//                        CreateEventA(NULL, FALSE, FALSE, NULL) into
//                        +0x20, unlock on success; on failure
//                        GetLastError + "CMessagePort::Init() failed
//                        with m_id=%d, error=%u" + unlock; returns
//                        whether the handle is non-null.
// 14050c390 Call(idx)  — invokes vtable+0x10 on the object and
//                        returns 0xffffffff for an invalid index.
//                        NOTE: the decompiler recovered no arguments
//                        for that indirect call, so its arity is
//                        unresolved; ported only as an index-checked
//                        dispatch with the arguments supplied by the
//                        caller (documented, not guessed).
// 14050f520/14050f8b0  — MSVC vector insert/erase with iterator
//                        debug checks (_invalid_parameter_noinfo):
//                        STL glue, out of scope.
#include <cstdint>
#include <cstddef>
namespace msg {
static const int kPortSyncObjOff = 0x68;
static const int kPortEventOff   = 0x20;
struct SPortRegistry {          // mirrors the global vector
    void** items;
    int    count;
};
inline void* PortRegistryGet(const SPortRegistry* r, int idx) {
    if (idx < 0) return nullptr;
    if (r->count <= idx) return nullptr;
    return r->items[idx];
}
inline int PortRegistryCount(const SPortRegistry* r) { return r->count; }
struct SPortInitSeams {
    void (*Lock)(void* syncObj);
    void (*Unlock)(void* syncObj);
    void* (*CreateEvent)(void* sa, int manualReset, int initialState,
                         const char* name);
    int  (*GetLastError)();
    void (*LogInitFail)(int id, unsigned err);
    int  (*PortId)(void* port);
};
// returns 1 on success, 0 when the event could not be created
int MessagePortInit(void* port, const SPortInitSeams& s);
}
#endif
