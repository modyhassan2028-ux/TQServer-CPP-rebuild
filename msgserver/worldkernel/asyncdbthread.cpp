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

} // namespace msg
