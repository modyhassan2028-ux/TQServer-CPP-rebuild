// ===== Path-A wave 8c: the ORIGINAL
// status-monitor socket loop —
// VERBATIM (raw objdump-verified) =====
#include "MsgStatusMonitorSock.h"
#include "MsgStatusMonitorCmd.h"
#include <cstring>
#include <cstdlib>

namespace msg {

SMSockSeams g_MSSockSeams = {};

struct SRawFdSet {           // 0x210
    uint32_t count;
    uint32_t pad;
    int64_t fd[0x40];
};

struct SRawTimeval {         // tv
    uint32_t sec;
    uint32_t usec;
};

struct SRawSockAddrIn {      // 0x10
    uint16_t family;
    uint16_t port;
    uint32_t addr;
    uint8_t pad[8];
};

struct SRawWSABuf {
    uint32_t len;
    uint8_t* buf;
};

// client entry: 0x50 {sock@+0,
// offset@+8 (int32), buf@+0xc}
static const int kMaxClients = 0x40;

uint32_t MonitorSocketThread(
        void* pMainThread) {
    SMSockSeams& s = g_MSSockSeams;
    s.LogStart();
    if (pMainThread == nullptr) {
        // raw CHECKF "pMainThread"
        s.LogCheckf();
        return 0;
    }
    uint8_t wsaData[0x1a0];   // WSADATA
    if (s.WSAStartup(0x0202, wsaData) == 0 &&
        wsaData[0] == 2 && wsaData[1] == 2) {
        int64_t lsock = s.WSASocketA(
            2, 1, 0, nullptr, 0, 0, nullptr);
        if (lsock == -1) {
            uint32_t e = s.WSAGetLastError();
            s.WSACleanup();
            s.LogErrCode(e, 0x17e);
        }
        else {
            uint8_t iniBuf[0x400];
            s.IniNew(iniBuf);
            uint32_t port = (uint32_t)
                s.IniGetInt(iniBuf, "port");
            if ((int32_t)port < 1)
                port = 0x16e4;
            SRawSockAddrIn sa;
            sa.family = 2;
            s.WSAHtons(lsock,
                (uint16_t)(port & 0xffff),
                &sa.port);
            sa.addr = 0;
            if (s.Bind(lsock, &sa, 0x10) == 0) {
                s.LogUsingPort(port);
                if (s.Listen(lsock) == 0) {
                    uint8_t clients[0x1400] = {};
                    *(int64_t*)clients = lsock;
                    int n = 1;
                    while (s.MainThreadState(
                            pMainThread) == 2) {
                        // build fd_set
                        SRawFdSet fds;
                        fds.count = 1;
                        fds.pad = 0;
                        fds.fd[0] = lsock;
                        uint32_t cnt = 1;
                        for (int i = 0; i < n;
                             i++) {
                            int64_t cur =
                              ((int64_t*)
                               clients)[i * 10];
                            uint32_t j = 0;
                            while (j < cnt &&
                                   fds.fd[j] != cur)
                                j++;
                            if (j == cnt &&
                                cnt < 0x40) {
                                fds.fd[j] = cur;
                                cnt++;
                                fds.count = cnt;
                            }
                        }
                        SRawTimeval tv =
                            {0, 500};
                        int sr = s.Select(
                            0, &fds, nullptr,
                            nullptr, &tv);
                        if (sr == -1) {
                            s.LogSelectFailed(
                                s.WSAGetLastError());
                            break;
                        }
                        if (sr > 0) {
                            if (s.IsSet(
                                    lsock, &fds)) {
                                if (n < 0x40) {
                                    SRawSockAddrIn
                                        csa = {};
                                    int32_t cl =
                                        0x10;
                                    int64_t cs =
                                      s.Accept(
                                        lsock, &csa,
                                        &cl, nullptr);
                                    ((int64_t*)
                                     clients)[n * 10]
                                        = cs;
                                    if (cs == -1) {
                                        s.LogLoginError();
                                    }
                                    else {
                                        uint16_t cport =
                                            csa.port;
                                        s.LogLogin(
                                            s.InetNtoa(
                                              csa.addr),
                                            cport);
                                        ((int32_t*)
                                         clients)[n * 0x14
                                           + 2] = 0;
                                        n++;
                                    }
                                }
                                else {
                                    s.LogOverflow();
                                }
                                sr--;
                            }
                            int i = 1;
                            while (sr > 0 &&
                                   i < n) {
                                uint8_t* ent =
                                    clients +
                                    (size_t)i *
                                    0x50;
                                int64_t cs =
                                    *(int64_t*)
                                    ent;
                                if (s.IsSet(
                                        cs, &fds)) {
                                    sr--;
                                    int32_t* pOff =
                                        (int32_t*)
                                        (ent + 8);
                                    int32_t space =
                                        0x1f -
                                        *pOff;
                                    if (space == 0)
                                        s.LogMyAssert();
                                    SRawWSABuf wb;
                                    wb.len =
                                        (uint32_t)
                                        space;
                                    wb.buf = ent +
                                        0xc +
                                        *pOff;
                                    uint32_t got =
                                        0;
                                    uint32_t ovl
                                        [4] = {0,0,
                                               0,0};
                                    int rr = s
                                        .WSARecv(cs,
                                        &wb, 1, &got,
                                        nullptr, ovl);
                                    if (rr == 0 &&
                                        got != 0) {
                                        *pOff +=
                                            (int32_t)
                                            got;
                                        if (wb.buf[
                                              got - 1]
                                              == 0) {
                                            *pOff -= 1;
                                        }
                                        else {
                                            wb.buf[got]
                                                = 0;
                                        }
                                        // 14002aef0
                                        MonitorHandleCmd(
                                            g_pStatusMonitor,
                                            ent);
                                    }
                                    else {
                                        SRawSockAddrIn
                                            psa = {};
                                        int32_t pl =
                                            0x10;
                                        if (s
                                            .GetPeerName(
                                            cs, &psa,
                                            &pl) == 0) {
                                            s.LogLogout(
                                              s.InetNtoa(
                                                psa.addr),
                                              psa.port);
                                        }
                                        else {
                                            s.LogLogoutPlain();
                                        }
                                        s.Shutdown(
                                            cs, 2);
                                        s.CloseSocket(
                                            cs);
                                        std::memmove(
                                          ent, ent + 0x50,
                                          (size_t)
                                          (n - i - 1)
                                            * 0x50);
                                        n--;
                                        i--;
                                    }
                                }
                                i++;
                            }
                        }
                    }
                    s.CloseSocket(lsock);
                    for (int i = 1; i < n; i++) {
                        int64_t cs =
                            ((int64_t*)
                             clients)[i * 10];
                        s.Shutdown(cs, 2);
                        s.CloseSocket(cs);
                    }
                    s.WSACleanup();
                    s.LogThreadEnd();
                    s.IniDel(iniBuf);
                    return 0;
                }
                else {
                    uint32_t e = s.WSAGetLastError();
                    s.LogListenFail(e);
                    s.CloseSocket(lsock);
                    s.WSACleanup();
                    s.LogErrCode(e, 0x1aa);
                    s.IniDel(iniBuf);
                }
            }
            else {
                uint32_t e = s.WSAGetLastError();
                s.LogBindFail(s.InetNtoa(sa.addr),
                              sa.port, e);
                s.CloseSocket(lsock);
                s.WSACleanup();
                s.IniDel(iniBuf);
            }
        }
    }
    return 0;
}

} // namespace msg
