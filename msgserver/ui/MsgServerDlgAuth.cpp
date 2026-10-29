#include "MsgServerDlgAuth.h"
#include <cstring>

namespace msg {
namespace {
inline int32_t& F32(void* p, size_t off) { return *(int32_t*)((char*)p + off); }
inline uint64_t& F64(void* p, size_t off) { return *(uint64_t*)((char*)p + off); }

// the RAW's byte-by-byte copy loop: copy *src into *dst until the NUL is copied
void CopyAddress(char* dst, const char* src) {
    char c;
    do {
        c = *src;
        *dst = c;
        ++src;
        ++dst;
    } while (c != 0);
}
} // namespace

// 140024860 lines 881-917
bool AuthTryConnect(void* pDlg, SAuthSeams& s) {
    void* cli = (char*)pDlg + 0x240;
    CopyAddress((char*)pDlg + 0x229c, (char*)pDlg + 0x227c);
    if (!s.Connect(cli, (char*)pDlg + 0x229c)) {
        s.Close(cli);
        CopyAddress((char*)pDlg + 0x229c, (char*)pDlg + 0x228c);
        if (!s.Connect(cli, (char*)pDlg + 0x229c)) s.Close(cli);
    }
    if (!s.IsConnected(cli)) {
        if (s.deadLoop) { /* the verbose flag is checked by the caller */ }
        return false;
    }
    F32(pDlg, 0x2278) = 1;
    s.SetParam(cli, F32(pDlg, 0x22c4));
    return true;
}

// 140024860 lines 918-958
void AuthSendFailPacket(void* pDlg, SAuthSeams& s) {
    void* cli = (char*)pDlg + 0x240;
    char packet[128];
    packet[0] = 0;                       // the length prefix byte
    std::memset(packet + 1, 0, 0x7f);
    // the RAW compares the first four letters of the DEADLOOP global by hand
    if (s.deadLoop && s.deadLoop[0] == 'D' && s.deadLoop[1] == 'E' &&
        s.deadLoop[2] == 'A' && s.deadLoop[3] == 'D') {
        s.FormatIpVersion(packet + 1, sizeof(packet) - 1);
    } else {
        s.PrepareVersion();
        s.FormatIpVersion(packet + 1, sizeof(packet) - 1);
    }
    size_t len = std::strlen(packet + 1);        // the RAW counts it by hand
    if ((int)(len - 1) - 1U < 0xfe) {
        packet[0] = (char)(uint8_t)(len - 1);
        if (s.Connect(cli, (char*)pDlg + 0x229c)) {
            s.SendPacket(cli, packet);
            s.Close(cli);
        }
    }
    F32(pDlg, 0x2278) = 3;
    s.KillTimer(pDlg, 2);
    s.PostQuit(pDlg);
}

// 140024860 lines 959-1002
void AuthDrainImport(void* pDlg, SAuthSeams& s) {
    void* cli = (char*)pDlg + 0x240;
    int got = 0;
    void* pkt = s.GetPacket(cli, &got);
    if (pkt != nullptr && got > 0) {
        if (F64(pDlg, 0x22b0) == 0) {
            if (got > 3) {
                std::memmove((char*)pDlg + 0x22b8, pkt, 4);
                void* buf = s.New(*(uint32_t*)((char*)pDlg + 0x22b8));
                F64(pDlg, 0x22b0) = (uint64_t)buf;
                s.Consume(cli, 4);
                s.acc = 0;                            // DAT_140975938 = 0
            }
        } else {
            std::memmove((char*)(uintptr_t)(F64(pDlg, 0x22b0) + s.acc), pkt, got);
            s.acc = s.acc + (uint32_t)got;
            s.Consume(cli, 0);                        // the RAW passes nothing
        }
    }
    if (F64(pDlg, 0x22b0) != 0 &&
        *(uint32_t*)((char*)pDlg + 0x22b8) <= s.acc) {
        s.acc = 0;
        s.Close(cli);
        F32(pDlg, 0x2278) = 3;
        s.KillTimer(pDlg, 2);
        if (!s.ImportFunctions((void*)F64(pDlg, 0x22b0),
                               *(uint32_t*)((char*)pDlg + 0x22b8), 1)) {
            s.PostQuit(pDlg);
        } else {
            F32(pDlg, 0x22c0) = 0;
            F32(pDlg, 0x22bc) = 0;
        }
    }
}

} // namespace msg
