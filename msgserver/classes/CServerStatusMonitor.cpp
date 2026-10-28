// 14002ba80
#include "CServerStatusMonitor.h"
namespace msg {
uintptr_t CServerStatusMonitor::StartWorkerThread(Seams& s) {
    if (s.GlobalReady() == 0) { s.CheckFail(); return 0; }
    if (m_pObj == nullptr)    { s.CheckFail(); return 0; }
    unsigned id = 0;
    uintptr_t h = s.BeginThreadEx(nullptr, 0, s.WorkerProc, m_pObj, 0, &id);
    m_hThread = h;
    if (h == 0) {
        s.LogStartFail(__FILE__, __LINE__);
        return 0;
    }
    return h;
}
}
