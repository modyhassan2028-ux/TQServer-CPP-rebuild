#include "MsgServerDlgGate.h"

namespace msg {
namespace {
inline int32_t& F32(void* p, size_t off) { return *(int32_t*)((char*)p + off); }
}

// the RAW counts with a register starting at -1 and stops after the NUL
long long HandLength(const char* s) {
    long long n = -1;
    const char* p = s;
    char c;
    do {
        if (n == 0) break;
        n = n - 1;
        c = *p;
        ++p;
    } while (c != 0);
    return n;
}

void OnTimerShutdownGate(void* pDlg, SGateSeams& s) {
    int handleWait = 0;
    if (s.shutdownFlag != nullptr && *s.shutdownFlag == 0) {
        s.waitResult = s.WaitEvent(*(void**)((char*)pDlg + 0x208), 0x14);
        handleWait = (s.waitResult == 0);
    }
    if (s.shutdownFlag != nullptr && *s.shutdownFlag == 0 && handleWait) {
        *s.shutdownFlag = 1;
        char cmd[9];
        const char* src = s.shutdownText;
        for (int i = 0; i < 9; ++i) cmd[i] = src[i];
        (void)HandLength(cmd);                       // counted, then discarded
        s.SocketCall50(*(void**)((char*)pDlg + 0x1f0), 2);
        F32(pDlg, 0x210) = 0x32;
        F32(pDlg, 0x214) = (int32_t)(s.TimeGet(0) / 1000);
        return;
    }
    uint32_t now = s.TimeGet(0);
    if (F32(pDlg, 0x214) == 0 ||
        now / 1000 < (uint32_t)(F32(pDlg, 0x210) + F32(pDlg, 0x214))) {
        if (F32(pDlg, 0x21c) != 0) {
            uint32_t now2 = s.TimeGet(0);
            if ((uint32_t)(F32(pDlg, 0x21c) + F32(pDlg, 0x218)) <= now2 / 1000) {
                F32(pDlg, 0x21c) = 0;
                F32(pDlg, 0x218) = 0;
                F32(pDlg, 0x1fc) = 3;
                s.LogNoArgs();
            }
        }
        return;
    }
    F32(pDlg, 0x214) = 0;
    F32(pDlg, 0x210) = 0;
    char cmd[11];
    const char* src = s.kickoutText;
    for (int i = 0; i < 11; ++i) cmd[i] = src[i];
    (void)HandLength(cmd);
    s.SocketCall50(*(void**)((char*)pDlg + 0x1f0), 2);
    F32(pDlg, 0x218) = 10;
    F32(pDlg, 0x21c) = (int32_t)(s.TimeGet(0) / 1000);
}

} // namespace msg
