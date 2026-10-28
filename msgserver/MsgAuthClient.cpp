// ===== Path-A wave 9d: the auth-client class, RAW-verbatim =====
#include "MsgAuthClient.h"
#include <cstring>
namespace msg {
// 140005c10 — the ctor
void* AuthClientCtor(SAuthClient* p, const SAuthSeams&) {
    p->sock = -1;                       // +0x20 = -1 (all 8 bytes)
    p->u10 = 0;
    p->u14 = 0;
    p->u18 = 0;
    p->szA = 0;                         // +0x1028
    p->szB = 0;                         // +0x202c
    p->state = 0;                       // +0x2030
    p->name[0] = '\0';                  // *param_1 = 0
    memset(p->bufA, 0, 0x1000);         // memset(+0x28, 0x1000)
    memset(p->bufB, 0, 0x1000);         // memset(+0x102c, 0x1000)
    return p;
}
// 140005e80 — IsConnected
int AuthClientIsConnected(const SAuthClient* p) {
    if ((int)p->state == 2 && p->sock != -1) return 1;
    return 0;
}
// 140005d20 — Close
void AuthClientClose(SAuthClient* p, const SAuthSeams& s) {
    if (p->sock != -1) {
        s.CloseSocketOrd(p->sock);
    }
    p->sock = -1;
    p->state = 0;
    p->szA = 0;
    p->szB = 0;
}
// 140005b50 — WSAStartup wrapper
int AuthClientWsaInit(const SAuthSeams& s) {
    short wsa[208];
    int r = s.WsaStartup(2, wsa);
    if (r != 0) {
        s.LogErrStr("ERROR: Init WSAStartup() failed.");
        return 0;
    }
    if (wsa[0] != 2) {
        s.LogErrStr("ERROR: WSAStartup Version not match 2.0");
        return 0;
    }
    return 1;
}
// 140005ea0 — the connect state machine
int AuthClientConnect(SAuthClient* p, const char* name,
        uint32_t u3, uint32_t u4, uint32_t u5, uint32_t u6,
        const SAuthSeams& s) {
    if ((int)p->state != 0) {
        s.LogErrNoArg();                // RAW line 0x3a
    }
    s.SafeCopy(p->name, name, 0x10);
    p->u10 = u3;
    p->u14 = u5;
    p->u18 = u6;
    if ((int)p->state == 2 && p->sock != -1) {
        return 1;
    }
    if ((int)p->state == 0 || p->sock == -1) {
        if (p->sock != -1) {
            s.LogErrNoArg();            // RAW line 0x48
        }
        int64_t fd = s.Socket(2, 1);    // AF_INET, SOCK_STREAM
        p->sock = fd;
        if (fd == -1) {
            s.LogErrStr("Create socket() failed.");
            return 0;
        }
        p->szA = 0;                     // bytes 0x1028..0x102b
        int opt = 1;
        if (s.SetSockOpt(fd, 0xffff, 8, &opt) != 0) {   // SO_KEEPALIVE
            s.LogErrStr("setsockopt() set SO_KEEPALIVE failed.");
            AuthClientClose(p, s);
            return 0;
        }
        opt = (int)p->u14;
        if (opt != 0) {
            if (s.SetSockOpt(fd, 0xffff, 0x1001, &opt) != 0) {
                int e = s.GetLastError();
                s.LogErrFmt("setsockopt() set SO_SNDBUF failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        opt = (int)p->u18;
        if (opt != 0) {
            if (s.SetSockOpt(fd, 0xffff, 0x1002, &opt) != 0) {
                int e = s.GetLastError();
                s.LogErrFmt("setsockopt() set SO_RCVBUF failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        int nb = 1;
        if (s.IoctlSocket(fd, 0x8004667e, &nb) != 0) {  // FIONBIO
            s.LogErrStr("Init ioctlsocket() failed.");
            AuthClientClose(p, s);
            return 0;
        }
        int32_t addr = s.InetAddr(p->name);
        if (addr == -1) {
            void* host = s.GetHostByName(p->name);
            if (host == nullptr) {
                s.LogErrStr("");        // &DAT_1406daaa0
                AuthClientClose(p, s);
                return 0;
            }
            addr = *(int32_t*)*(void**)((char*)host + 0x18);
        }
        // sockaddr_in: family=2, port=htons(u10), addr, pad
        unsigned char sa[16];
        memset(sa, 0, sizeof(sa));
        uint16_t fam = 2;
        uint16_t port = s.Htons((uint16_t)p->u10);
        memcpy(sa + 0, &fam, 2);
        memcpy(sa + 2, &port, 2);
        memcpy(sa + 4, &addr, 4);
        if (s.Connect(fd, sa, 0x10) == -1) {
            int e = s.GetLastError();
            if (e != 0x2733) {          // WSAEWOULDBLOCK allowed
                s.LogErrFmt("connect to server failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        p->state = 1;                   // bytes 0x2030..0x2033
    }
    if (p->sock == -1) {
        s.LogErrStr("Init socket() failed.");
        AuthClientClose(p, s);
        return 0;
    }
    if ((int)p->state != 1) {
        s.LogErrNoArg();                // RAW line 0xa3
    }
    // select on write + except sets, tv {param_4, 1000}
    int wset[2] = { 1, (int)p->sock };
    int eset[2] = { 1, (int)p->sock };
    int tv[2] = { (int)u4, 1000 };
    int r = s.Select(0x40, nullptr, wset, eset, tv);
    if (r == -1) {
        s.LogErrStr("select socket() failed.");
    } else {
        if (r < 1) {
            return 0;
        }
        if (s.GetSockOpt(p->sock, &eset[0]) == 0) {
            if (s.GetSockOpt(p->sock, &wset[0]) == 0) {
                return 0;
            }
            p->state = 2;
            return 1;
        }
    }
    // the verbatim failure path
    if (p->sock != -1) {
        s.CloseSocketOrd(p->sock);
    }
    p->sock = -1;
    p->state = 0;
    p->szA = 0;
    p->szB = 0;
    return 0;
}
// 14001e0b0 — build and send the auth key
void AuthClientSendKey(SAuthClient* p, uint32_t arg,
        const SAuthSeams& s) {
    char buf[128];
    buf[0] = '\0';
    memset(buf + 1, 0, 0x7f);
    uint32_t t = s.Time32();
    s.Sprintf2u(buf, t, arg);           // "%u %u"
    size_t len = s.StrLen(buf);
    s.LogMsgFmt("%d:%s", (int)len, buf);
    static const unsigned char key[10] = {
        't','q','d','i','g','i','t','a','l', 0 };
    int n = (int)len;
    for (int i = 0; i < n; ++i) {
        unsigned k = (unsigned)((long long)(int)((unsigned)i) % 10);
        unsigned char c = (unsigned char)
            (key[k] ^ (unsigned char)buf[i]);
        buf[i] = (char)(unsigned char)((c << 4) | (c >> 4));
    }
    s.Fn6880(p, buf, (uint32_t)len, 1);
}

// ===== wave 9e: the packet half (RAW-verbatim) =====
// 140005c70 — ClearPacket
int AuthClientClearPacket(SAuthClient* p, int nLen,
        const SAuthSeams& s) {
    (void)s;
    if ((int)p->szA < nLen) {
        // RAW: "ClearPacket()  error, Getpacket OutBufSize:%d,
        // ClearPacket nLen:%d, m_nLen:%d, unMsgType:%d at %s, %d"
        s.LogErrFmt("ClearPacket()  error, Getpacket OutBufSize:%d,"
                    " ClearPacket nLen:%d, m_nLen:%d, unMsgType:%d"
                    " at %s, %d", (int)p->szA);
    }
    if ((int)p->state == 2) {
        int rest = (int)p->szA - nLen;
        if (0 < rest) {
            // RAW calls memcpy here with overlapping ranges (dst < src):
            // UB in C++, but MSVC's forward copy yields exactly the
            // memmove result, so we use memmove to keep it defined.
            memmove(p->bufA, p->bufA + nLen, (size_t)rest);
        }
        p->szA = (uint32_t)((int)p->szA - nLen);
        if (-1 < (int)p->szA) {
            return 1;
        }
        p->szA = 0;
    }
    return 0;
}
// 140005d60 — Flush
int AuthClientFlush(SAuthClient* p, const SAuthSeams& s) {
    if ((int)p->state != 2) {
        return 0;
    }
    if (p->szB == 0) {
        return 1;
    }
    int n = s.Send(p->sock, p->bufB, (int)p->szB, 0);
    if (0 < n) {
        int rest = (int)p->szB - n;
        if (0 < rest) {
            // RAW memcpy with overlap (dst < src) -> memmove semantics.
            memmove(p->bufB, p->bufB + n, (size_t)rest);
        }
        p->szB = (uint32_t)((int)p->szB - n);
        if ((int)p->szB < 0) {
            s.LogErrNoArg();        // &DAT_1406d9c10
        }
        return p->szB == 0 ? 1 : 0;
    }
    int e = s.GetLastError();
    if (e != 0x2746) {              // WSAECONNRESET tolerated
        s.LogErrFmt("Flush packet failed[%d].", e);
    }
    if (p->sock != -1) {
        s.CloseSocketOrd(p->sock);
    }
    p->state = 0;
    p->szA = 0;
    p->szB = 0;
    p->sock = -1;
    return 0;
}
// 140006730 — GetPacket
void* AuthClientGetPacket(SAuthClient* p, uint32_t* pLen, int bRecv,
        const SAuthSeams& s) {
    if (pLen == nullptr) {
        s.LogErrNoArg();
        return nullptr;
    }
    *pLen = 0;
    if ((int)p->state == 2) {
        if (p->sock != -1) {
            if (bRecv) {
                int have = (int)p->szA;
                if (have < 0x1000) {
                    int n = s.Recv(p->sock, (char*)p->bufA + have,
                                   0x1000 - have, 0);
                    if (n < 1) {
                        if (n == 0) {
                            s.LogErrStr("GetPacket() connect be close.");
                        } else {
                            int e = s.GetLastError();
                            if (e != 0x2733 && e != 0x2746) {
                                s.LogErrFmt("recv packet failed[%d].", e);
                            }
                        }
                        AuthClientClose(p, s);
                    } else {
                        p->szA = (uint32_t)((int)p->szA + n);
                    }
                }
            }
            *pLen = p->szA;
            return p->bufA;
        }
        s.LogErrStr("GetPacket() invalid socket failed.");
        if (p->sock != -1) {
            s.CloseSocketOrd(p->sock);
        }
        p->sock = -1;
        p->state = 0;
        p->szA = 0;
        p->szB = 0;
    }
    return nullptr;
}
// 140006880 — SendPacket
int AuthClientSendPacket(SAuthClient* p, const void* buf, int len,
        int bFlush, const SAuthSeams& s) {
    if ((int)p->state != 2) {
        return 0;
    }
    if (p->sock == -1) {
        s.LogErrStr("SendPacket() invalid socket failed.");
        if (p->sock != -1) {
            s.CloseSocketOrd(p->sock);
        }
    } else {
        if (0x1000 < len + (int)p->szB) {
            AuthClientFlush(p, s);
        }
        if ((int)p->szB + len < 0x1001) {
            memcpy(p->bufB + p->szB, buf, (size_t)len);
            p->szB = (uint32_t)((int)p->szB + len);
            if (bFlush) {
                return AuthClientFlush(p, s);
            }
            return 1;
        }
        s.LogErrStr("SendPacket() buf full!");
        if (p->sock != -1) {
            s.CloseSocketOrd(p->sock);
            p->sock = -1;
            p->state = 0;
            p->szA = 0;
            p->szB = 0;
            return 0;
        }
    }
    p->sock = -1;
    p->state = 0;
    p->szA = 0;
    p->szB = 0;
    return 0;
}
// 1400062f0 — ConnectStored (the 2-arg twin of 140005ea0)
int AuthClientConnectStored(SAuthClient* p, uint32_t tvSec,
        const SAuthSeams& s) {
    if (p->name[0] == '\0') {
        s.LogErrNoArg();            // RAW line 199 (0xc7)
    }
    if ((int)p->state == 2 && p->sock != -1) {
        return 1;
    }
    if ((int)p->state == 0 || p->sock == -1) {
        if (p->sock != -1) {
            s.LogErrNoArg();        // RAW line 0xd0
        }
        int64_t fd = s.Socket(2, 1);
        p->sock = fd;
        if (fd == -1) {
            s.LogErrStr("Create socket() failed.");
            return 0;
        }
        p->szA = 0;
        int opt = 1;
        if (s.SetSockOpt(fd, 0xffff, 8, &opt) != 0) {
            s.LogErrStr("setsockopt() set SO_KEEPALIVE failed.");
            AuthClientClose(p, s);
            return 0;
        }
        opt = (int)p->u14;
        if (opt != 0) {
            if (s.SetSockOpt(fd, 0xffff, 0x1001, &opt) != 0) {
                int e = s.GetLastError();
                s.LogErrFmt("setsockopt() set SO_SNDBUF failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        opt = (int)p->u18;
        if (opt != 0) {
            if (s.SetSockOpt(fd, 0xffff, 0x1002, &opt) != 0) {
                int e = s.GetLastError();
                s.LogErrFmt("setsockopt() set SO_RCVBUF failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        int nb = 1;
        if (s.IoctlSocket(fd, 0x8004667e, &nb) != 0) {
            s.LogErrStr("Init ioctlsocket() failed.");
            AuthClientClose(p, s);
            return 0;
        }
        int32_t addr = s.InetAddr(p->name);
        if (addr == -1) {
            void* host = s.GetHostByName(p->name);
            if (host == nullptr) {
                s.LogErrStr("");
                AuthClientClose(p, s);
                return 0;
            }
            addr = *(int32_t*)*(void**)((char*)host + 0x18);
        }
        unsigned char sa[16];
        memset(sa, 0, sizeof(sa));
        uint16_t fam = 2;
        uint16_t port = s.Htons((uint16_t)p->u10);
        memcpy(sa + 0, &fam, 2);
        memcpy(sa + 2, &port, 2);
        memcpy(sa + 4, &addr, 4);
        if (s.Connect(fd, sa, 0x10) == -1) {
            int e = s.GetLastError();
            if (e != 0x2733) {
                s.LogErrFmt("connect to server failed[%d].", e);
                AuthClientClose(p, s);
                return 0;
            }
        }
        p->state = 1;
    }
    if (p->sock == -1) {
        s.LogErrStr("Init socket() failed.");
        AuthClientClose(p, s);
        return 0;
    }
    if ((int)p->state != 1) {
        s.LogErrNoArg();
    }
    int wset[2] = { 1, (int)p->sock };
    int eset[2] = { 1, (int)p->sock };
    int tv[2] = { (int)tvSec, 1000 };
    int r = s.Select(0x40, nullptr, wset, eset, tv);
    if (r == -1) {
        s.LogErrStr("select socket() failed.");
    } else {
        if (r < 1) {
            return 0;
        }
        if (s.GetSockOpt(p->sock, &eset[0]) == 0) {
            if (s.GetSockOpt(p->sock, &wset[0]) == 0) {
                return 0;
            }
            p->state = 2;
            return 1;
        }
    }
    if (p->sock != -1) {
        s.CloseSocketOrd(p->sock);
    }
    p->sock = -1;
    p->state = 0;
    p->szA = 0;
    p->szB = 0;
    return 0;
}
}
