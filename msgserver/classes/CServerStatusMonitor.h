#ifndef C_SERVER_STATUS_MONITOR_H
#define C_SERVER_STATUS_MONITOR_H
// 14002ba80 CServerStatusMonitor::StartWorkerThread()
//   DAT_140975948 == 0            -> the shared check message, return 0
//   *(this+0x00) == 0             -> the shared check message, return 0
//   h = _beginthreadex(NULL,0,Worker,*(this+0),0,&id); *(this+0x68)=h
//   h == 0 -> "CServerStatusMonitor::StartWorkerThread()
//             _beginthreadex failed at %s, %d"   (file/line args)
//   returns h
// The shared check message is DAT_1406d9c10, extracted from .rdata:
//   "\xa1\xef%s(%s)\xa1\xef in %s, %d"   (GBK-encoded)
#include <cstdint>
namespace msg {
class CServerStatusMonitor {
public:
    struct Seams {
        int (*GlobalReady)();                    // DAT_140975948
        void (*CheckFail)();                     // the shared check log
        uintptr_t (*BeginThreadEx)(void* sa, unsigned stack,
                                   unsigned (*fn)(void*), void* arg,
                                   unsigned flags, unsigned* id);
        void (*LogStartFail)(const char* file, int line);
        unsigned (*WorkerProc)(void*);
    };
    uintptr_t StartWorkerThread(Seams& s);
    void* m_pObj = nullptr;                       // +0x00
private:
    uint8_t m_Pad[0x60] = {};                     // +0x08..+0x67
public:
    uintptr_t m_hThread = 0;                      // +0x68
};
}
#endif
