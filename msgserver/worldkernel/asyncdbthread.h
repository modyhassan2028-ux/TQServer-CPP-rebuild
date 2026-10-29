#pragma once
// CAsyncDBThread — MsgServer, key 0x4b. Only the members whose bodies are fully
// recovered from the disassembly are ported here; the class keeps the original
// layout so the remaining helpers can be added without moving offsets.
#include <cstdint>
#include <cstddef>

namespace msg {

class CAsyncDBThread;

struct SAsyncDbSeams {
    void  (*Log)(const char* text);                 // log_InlineLogERROR
    void  (*CloseHandle)(void* h);                  // CloseHandle
    void  (*Delete)(void* p);                       // operator delete
    void  (*Dtor)(CAsyncDBThread* self);            // ~CAsyncDBThread
    void* (*Ordinal19)(void* sock, void* buf, int len, int flags); // Ordinal_19
    int   (*Ordinal16)(void* sock, void* buf, int len, int flags); // Ordinal_16 (recv)
    int   (*Ordinal111)();                                        // Ordinal_111 (last error)
    void  (*Ordinal3)(void* sock);                                // Ordinal_3 (closesocket)
    void  (*Teardown)(CAsyncDBThread* self);                      // 140005d20
};

class CAsyncDBThread {
public:
    // 1400018c0 — the module-private instance pointer (DAT_1409754e8)
    static CAsyncDBThread* Instance();
    // 1400029f0 — closes the socket handle at +0x08, deletes, clears the pointer
    static void DestroyInstance(SAsyncDbSeams& s);
    // 140026a60 — the vtable slot 0 deleting destructor
    static CAsyncDBThread* DeleteSelf(CAsyncDBThread* self, uint32_t flags,
                                      SAsyncDbSeams& s);
    // 140005c70 — consumes nLen bytes from the receive buffer at +0x28
    int  ClearPacket(int nLen, SAsyncDbSeams& s);
    // 140005d60 — pushes whatever is pending at +0x102c and reports "drained"
    bool FlushPending(SAsyncDbSeams& s);
    // 140006730 — the packet fetch: returns +0x28 (or null) and the length out
    void* GetPacket(uint32_t* lenOut, char fill, SAsyncDbSeams& s);
    // 140006880 — SendPacket: appends to the 0x1000-byte pending buffer at
    // +0x102c and optionally flushes. Non-2 state refuses, -1 socket logs and
    // resets, a full buffer logs, closes and resets.
    int  SendPacket(const void* data, int size, char flush, SAsyncDbSeams& s);

    // layout (bytes as used by the ported members)
    //  +0x0000 vftable
    //  +0x0008 socket handle (closed by DestroyInstance)
    //  +0x0020 base socket object for Ordinal_19
    //  +0x0028 receive buffer start
    //  +0x1028 buffered length
    //  +0x102c pending flush buffer
    //  +0x202c pending flush length
    //  +0x2030 state (2 = connected/running)
    uint8_t  raw_[0x2034];

    // the shared reset tail used by SendPacket
    void ResetLink();

    static CAsyncDBThread*& InstanceRef(SAsyncDbSeams& s);
};

} // namespace msg
