#include "MsgServerDlgProcess.h"

namespace msg {

// 140021bd0
int ProcessOnce(void* pDlg, SProcessSeams& s) {
    void* sock = *(void**)((char*)pDlg + 0x1f0);
    SRecvFrame frame{};
    if (!s.Receive(sock, -1, -1, 0x418, frame)) return 1;   // nothing to do
    if (!s.ProcessMsg(pDlg, frame.f1, frame.buf, frame.f2)) {
        s.LogError(pDlg, "ERROR: CMsgServerDlg::Process() ProcessMsg()");
        return 0;
    }
    return 1;
}

} // namespace msg
