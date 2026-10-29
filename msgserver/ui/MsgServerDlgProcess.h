#ifndef MSG_SERVER_DLG_PROCESS_H
#define MSG_SERVER_DLG_PROCESS_H
// ===== CMsgServerDlg::Process — the receive step (140021bd0) =====
//
// The RAW names itself: the failure branch logs
//     "ERROR: CMsgServerDlg::Process() ProcessMsg()"
// so this belongs to Process(), not to OnTimer, even though OnTimer calls it.
//
// Verbatim shape:
//     cVar1 = (**(code**)(*socket + 0x48))(socket, -1, -1, 0x418);
//     if (!cVar1) return 1;                      // nothing received
//     if (!14001e670(dlg, out2, buf, out3)) {    // dispatch failed
//         log("ERROR: CMsgServerDlg::Process() ProcessMsg()"); return 0;
//     }
//     return 1;
//
// The socket object lives at dlg+0x1f0. Its vtable slot +0x48 fills three
// stack dwords and a 0x420-byte buffer, so the seam carries them explicitly.
#include <cstdint>

namespace msg {

struct SRecvFrame {
    int32_t f0;                 // local_458 — filled, never used by the RAW
    int32_t f1;                 // local_454 — passed to the dispatcher
    int32_t f2;                 // local_450 — passed to the dispatcher
    unsigned char buf[1056];    // local_438 — 0x420 bytes
};

struct SProcessSeams {
    // socket vtable +0x48 on *(dlg + 0x1f0)
    bool (*Receive)(void* sock, int arg1, int arg2, int bytes, SRecvFrame& out);
    // 14001e670 — the message dispatcher
    bool (*ProcessMsg)(void* pDlg, int f1, void* buf, int f2);
    // 14001e540 — the log path used with a format string
    void (*LogError)(void* pDlg, const char* text);
};

// 140021bd0
int ProcessOnce(void* pDlg, SProcessSeams& s);

} // namespace msg
#endif
