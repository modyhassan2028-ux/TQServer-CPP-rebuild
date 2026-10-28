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
// 14050c390 Call(idx, a, b, c) — RESOLVED FROM THE DISASSEMBLY
//                        (0x14050c390): after the index check it does
//                          mov rcx,(rdx,rbx,8)  ; rcx = items[idx]
//                          mov rax,(rcx)        ; vtable
//                          jmp *0x10(rax)       ; TAIL JUMP
//                        Only rcx is rewritten, so rdx/r8/r9 reach
//                        the target untouched: it is a perfect-
//                        forwarding dispatcher that consumes idx as
//                        arg0 and forwards three more arguments.
//                        Invalid index returns 0xffffffff. The
//                        decompiler had dropped the arguments; the
//                        asm shows there is no hidden arity.
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
// vtable slot +0x10 of a registered port object
typedef int (*PortVt10Fn)(void* self, void* a, void* b, void* c);
inline int PortRegistryCall(const SPortRegistry* r, int idx,
                            void* a, void* b, void* c) {
    void* obj = PortRegistryGet(r, idx);
    if (obj == nullptr) return -1;              // 0xffffffff
    void** vt = *(void***)obj;
    PortVt10Fn f = (PortVt10Fn)vt[2];           // byte offset 0x10
    return f(obj, a, b, c);                     // idx replaced by self
}
}
#endif
