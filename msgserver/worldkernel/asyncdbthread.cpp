#include "asyncdbthread.h"
#include <cstring>

namespace msg {

static CAsyncDBThread* g_asyncDbInstance = nullptr;   // DAT_1409754e8

CAsyncDBThread*& CAsyncDBThread::InstanceRef(SAsyncDbSeams&) { return g_asyncDbInstance; }

CAsyncDBThread* CAsyncDBThread::Instance() { return g_asyncDbInstance; }

void CAsyncDBThread::DestroyInstance(SAsyncDbSeams& s) {
    CAsyncDBThread* p = g_asyncDbInstance;
    if (p == nullptr) return;
    void* handle = *(void**)(p->raw_ + 8);
    if (handle != nullptr) s.CloseHandle(handle);
    s.Delete(p);
    g_asyncDbInstance = nullptr;
}

CAsyncDBThread* CAsyncDBThread::DeleteSelf(CAsyncDBThread* self, uint32_t flags,
                                           SAsyncDbSeams& s) {
    s.Dtor(self);
    if ((flags & 1) != 0) s.Delete(self);
    return self;
}

// 140005c70 — the RAW only touches the buffer when the state is 2, and reports
// failure (after clamping the length to zero) when nLen overruns the buffered
// length. An overrun length is logged but does not abort the copy.
int CAsyncDBThread::ClearPacket(int nLen, SAsyncDbSeams& s) {
    if (*(int*)(raw_ + 0x1028) < nLen) s.Log("ClearPacket log");
    if (*(int*)(raw_ + 0x2030) != 2) return 0;
    int rest = *(int*)(raw_ + 0x1028) - nLen;
    if (rest > 0) std::memmove(raw_ + 0x28, raw_ + 0x28 + nLen, (size_t)rest);
    *(int*)(raw_ + 0x1028) = *(int*)(raw_ + 0x1028) - nLen;
    if (*(int*)(raw_ + 0x1028) >= 0) return 1;
    *(int*)(raw_ + 0x1028) = 0;
    return 0;
}


// 140005d60 — sends the pending buffer. A short send keeps the remainder in
// place and reports false; a failed send logs, closes the socket, wipes the
// lengths and parks the socket at -1. Sending nothing reports true.
bool CAsyncDBThread::FlushPending(SAsyncDbSeams& s) {
    if (*(int*)(raw_ + 0x2030) != 2) return false;
    if (*(int*)(raw_ + 0x202c) == 0) return true;
    intptr_t sock = *(intptr_t*)(raw_ + 0x20);
    int sent = (int)(intptr_t)s.Ordinal19((void*)sock, raw_ + 0x102c,
                                          *(int*)(raw_ + 0x202c), 0);
    if (sent > 0) {
        int rest = *(int*)(raw_ + 0x202c) - sent;
        if (rest > 0) std::memmove(raw_ + 0x102c, raw_ + 0x102c + sent, (size_t)rest);
        *(int*)(raw_ + 0x202c) = *(int*)(raw_ + 0x202c) - sent;
        if (*(int*)(raw_ + 0x202c) < 0) s.Log("Flush pending overrun");
        return *(int*)(raw_ + 0x202c) == 0;
    }
    int err = s.Ordinal111();
    if (err != 0x2746) s.Log("Flush packet failed");
    if (*(intptr_t*)(raw_ + 0x20) != -1) s.Ordinal3((void*)sock);
    *(int*)(raw_ + 0x2030) = 0;
    *(int*)(raw_ + 0x1028) = 0;
    *(int*)(raw_ + 0x202c) = 0;
    *(intptr_t*)(raw_ + 0x20) = -1;
    return false;
}

// 140006730 — fetches the next packet. Only state 2 with a live socket reads;
// a null out pointer, a wrong state or the dead socket path all report null.
// A zero-length recv is logged as a close, and the error codes 0x2733 / 0x2746
// are silently accepted, otherwise the recv error is logged.
void* CAsyncDBThread::GetPacket(uint32_t* lenOut, char fill, SAsyncDbSeams& s) {
    if (lenOut == nullptr) { s.Log("GetPacket null length"); return nullptr; }
    *lenOut = 0;
    if (*(int*)(raw_ + 0x2030) != 2) return nullptr;
    if (*(intptr_t*)(raw_ + 0x20) == -1) {
        s.Log("GetPacket() invalid socket failed.");
        if (*(intptr_t*)(raw_ + 0x20) != -1) s.Ordinal3((void*)*(intptr_t*)(raw_ + 0x20));
        *(intptr_t*)(raw_ + 0x20) = -1;
        *(int*)(raw_ + 0x2030) = 0;
        *(int*)(raw_ + 0x1028) = 0;
        *(int*)(raw_ + 0x202c) = 0;
        return nullptr;
    }
    if (fill != 0) {
        int have = *(int*)(raw_ + 0x1028);
        if (have < 0x1000) {
            int got = s.Ordinal16((void*)*(intptr_t*)(raw_ + 0x20), raw_ + 0x28 + have,
                                  0x1000 - have, 0);
            if (got < 1) {
                if (got == 0) {
                    s.Log("GetPacket() connect be close.");
                } else {
                    int err = s.Ordinal111();
                    if (err == 0x2733) goto done;
                    if (err != 0x2746) s.Log("recv packet failed");
                }
                s.Teardown(this);
            } else {
                *(int*)(raw_ + 0x1028) = *(int*)(raw_ + 0x1028) + got;
            }
        }
    }
done:
    *lenOut = *(uint32_t*)(raw_ + 0x1028);
    return raw_ + 0x28;
}

// the shared reset tail: socket -1, state 0, +0x1028 0, pending length 0
void CAsyncDBThread::ResetLink() {
    *(intptr_t*)(raw_ + 0x20) = -1;
    *(int32_t*)(raw_ + 0x2030) = 0;
    *(int32_t*)(raw_ + 0x1028) = 0;
    *(int32_t*)(raw_ + 0x202c) = 0;
}

// 140006880
int CAsyncDBThread::SendPacket(const void* data, int size, char flush, SAsyncDbSeams& s) {
    intptr_t* sock = (intptr_t*)(raw_ + 0x20);
    int32_t*  pending = (int32_t*)(raw_ + 0x202c);
    int32_t*  state = (int32_t*)(raw_ + 0x2030);
    if (*state != 2) return 0;
    if (*sock == -1) {
        s.Log("SendPacket() invalid socket failed.");
        // the RAW re-tests the handle it has just found to be -1: kept as-is
        if (*sock != -1) s.Ordinal3((void*)*sock);
    } else {
        if (0x1000 < size + *pending) FlushPending(s);   // the result is ignored
        if (*pending + size < 0x1001) {
            std::memcpy(raw_ + 0x102c + *pending, data, (size_t)size);
            *pending = *pending + size;
            if (flush != '\0') return FlushPending(s) ? 1 : 0;
            return 1;
        }
        s.Log("SendPacket() buf full!");
        if (*sock != -1) {
            s.Ordinal3((void*)*sock);
            ResetLink();
            return 0;
        }
    }
    ResetLink();
    return 0;
}
} // namespace msg
