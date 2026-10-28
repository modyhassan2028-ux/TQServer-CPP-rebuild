// ===== Path-A wave 9g: 140003dc0 initialization half =====
#include "MsgCheatMonitorThread.h"
#include <cstdio>
#include <cstring>
namespace msg {
int CheatMonitorThreadInit(void* pMainThread, SMonInitResult* out,
                           const SMonThreadSeams& s) {
    const char* kFile =
        "f:\\version\\cqserver-78.0.11-1204\\msgserver\\"
        "cheatingprogrammonitor.cpp";
    memset(out, 0, sizeof(*out));
    // 1. the port object
    void* portObj = s.PortObjGet(5);
    out->portObj = portObj;
    if (portObj == nullptr) {
        s.CheckF("pPort", 0xff, kFile);
        return 0;
    }
    s.PortObjReset(portObj);            // vtable+0x38
    // 2. the main thread
    if (pMainThread == nullptr) {
        s.CheckF("pMainThread", 0x103, kFile);
        return 0;
    }
    // 3. WSAStartup + the two version checks
    unsigned char wsa[416];
    memset(wsa, 0, sizeof wsa);
    int rc = s.WsaStartup(0x202, wsa);
    if (rc != 0) {
        return rc;
    }
    if (wsa[0] != 2 || wsa[1] != 2) {
        return rc;
    }
    // 4. the listening socket
    int64_t lsock = s.Socket(2, 1, 0, nullptr);
    if (lsock == -1) {
        int e = s.GetLastError();
        s.WsaCleanup();
        return e;
    }
    out->listenSock = lsock;
    // 5. shell.ini [CheatingMonitor]
    void* ini = s.IniOpen("shell.ini", "CheatingMonitor");
    uint32_t port = (uint32_t)s.IniGetInt(ini, "ListenPort");
    if (port == 0) {
        port = kMonitorDefPort;         // 9150
    }
    out->port = (uint16_t)port;
    int ipCount = s.IniGetInt(ini, "IPNum");
    if (kMonitorMaxIpNum < ipCount) {
        ipCount = kMonitorMaxIpNum;
        s.LogWarnStr("astrict ip number overrun max ip number!");
    }
    for (int i = 0; i < ipCount; ++i) {
        char key[10];
        snprintf(key, 10, "IP%d", i + 1);   // RAW: 1-based names
        key[9] = 0;
        char val[24];
        memset(val, 0, sizeof val);
        s.IniGetString(ini, val, key, kMonitorMaxIpNum);
        // RAW stores at base + i*4 - 4 in a block cleared from
        // base; both the writer and the accept check use the same
        // shifted index, so ips[i] is equivalent.
        out->ips[i] = (int32_t)s.InetAddr(val);
    }
    out->ipCount = ipCount;
    // 6. bind on INADDR_ANY
    unsigned char sa[16];
    memset(sa, 0, sizeof sa);
    uint16_t fam = 2;
    memcpy(sa + 0, &fam, 2);
    uint16_t nport = s.Htons((uint16_t)(port & 0xffff));
    memcpy(sa + 2, &nport, 2);          // +4 = 0 (INADDR_ANY)
    if (s.Bind(lsock, sa, 0x10) != 0) {
        int e = s.GetLastError();
        const char* ipstr = s.InetNtoa(0);
        s.LogErrFmt("Cheating Program Monitor can not bind to"
                    " (%s : %u), nErr : %d", ipstr,
                    (unsigned)port, e);
        s.CloseSocket(lsock);
        s.WsaCleanup();
        s.IniClose(ini);
        return e;
    }
    // 7. listen
    if (s.Listen(lsock, 0) != 0) {
        int e = s.GetLastError();
        s.LogErrFmt("Cheating Program Monitor listen failed : %d", e);
        s.CloseSocket(lsock);
        s.WsaCleanup();
        s.IniClose(ini);
        return e;
    }
    // 8. the 64 client slots, each 0x8020 zeroed
    for (int i = 0; i < kMonitorMaxClients; ++i) {
        SMonClient* c = (SMonClient*)s.Alloc(kMonitorSlotSize);
        if (c == nullptr) {
            s.CheckF("pClientInfo", 0x155, kFile);
            for (int k = 0; k < out->slotCount; ++k) {
                s.Free(out->slots[k]);
                out->slots[k] = nullptr;
            }
            out->slotCount = 0;
            s.IniClose(ini);
            return 0;
        }
        memset(c, 0, kMonitorSlotSize);
        out->slots[i] = c;
        out->slotCount = i + 1;
    }
    // slot 0 carries the listening socket
    out->slots[0]->sock = lsock;
    out->slots[0]->active = 1;
    // 9. the DES handshake key
    uint8_t key[16];
    memset(key, 0, sizeof key);
    s.DesStringToKey("df29duw", key);
    s.DesSetKey(key);
    memcpy(out->desKey, key, sizeof key);
    // 10. "#%u: Cheating Program Monitor thread running." (0x9c41)
    uint32_t tid = s.PortObjThreadId(portObj);
    char msg[0x3ff];
    snprintf(msg, 0x3ff,
             "#%u: Cheating Program Monitor thread running.",
             (unsigned)tid);
    s.PortObjPost(portObj, 0, 0x9c41, (uint32_t)strlen(msg));
    s.IniClose(ini);
    return 1;
}

// ===== wave 9h: the event loop (RAW 0x1400044f0..0x140005453) =====
int CheatMonitorThreadLoop(void* pMainThread, SMonLoop* st,
                           const SMonThreadSeams& s,
                           const SMonLoopSeams& ls) {
    const char* kFile =
        "f:\\version\\cqserver-78.0.11-1204\\msgserver\\"
        "cheatingprogrammonitor.cpp";
    int activeCount = st->activeCount;
    bool stop = false;
    while (!stop) {
        // RAW: iVar5 = 14001f4c0(pMainThread); != 2 -> stop
        if (ls.ThreadAlive(pMainThread) != 2) {
            break;
        }
        // ---- build the fd_set: listener first, then active slots ----
        SMonFdSet set;
        set.count = 1;
        set.fd[0] = st->listenSock;
        int guard = 1;
        for (int i = 1; i < kMonitorMaxClients; ++i) {
            st->spinBuild += 1;
            if (1000000 < (int)st->spinBuild) {
                ls.CheckF("DEAD_LOOP_BREAK", 0x177, kFile);
                guard = -1;
                break;
            }
            SMonClient* c = st->slots[i];
            if (c->active == 0 || c->sock == 0) {
                continue;
            }
            bool present = false;
            for (uint32_t k = 0; k < set.count; ++k) {
                if (set.fd[k] == c->sock) {
                    present = true;
                    break;
                }
            }
            if (!present && set.count < kMonitorMaxClients) {
                set.fd[set.count++] = c->sock;
            }
            guard += 1;
            if (activeCount <= guard) {
                break;
            }
        }
        if (guard < 0) {
            continue;               // RAW jumps back to LAB_1400044f0
        }
        // ---- select with tv = {0, 500} (RAW local_1070) ----
        int32_t tv[2] = { 0, 500 };
        int n = ls.Select(0, &set, tv);
        if (n == -1) {
            int e = ls.GetLastError();
            ls.LogErrFmt("Cheating Program Monitor select failed : %d", e);
            break;                  // -> LAB_14000524a (stop)
        }
        if (n < 1) {
            continue;
        }
        int remaining = n;
        // ---- accept on the listener ----
        if (ls.FdIsSet(st->listenSock, &set)) {
            remaining -= 1;
            if (activeCount < kMonitorMaxClients) {
                SMonPeer peer;
                memset(&peer, 0, sizeof peer);
                int plen = 0x10;
                int64_t acc = ls.Accept(st->listenSock, &peer, &plen);
                if (acc != -1) {
                    ls.LogMessage("Cheating Program Monitor client"
                                  "(%s : %u) login",
                                  ls.InetNtoa(peer.addr),
                                  (unsigned)peer.port);
                    bool allowed = false;
                    for (int i = 0; i < st->ipCount; ++i) {
                        if (st->ips[i] == (int32_t)peer.addr) {
                            allowed = true;
                            break;
                        }
                    }
                    if (!allowed) {
                        ls.LogWarnStr("lawless ip address %s!");
                        s.LogErrStr(ls.InetNtoa(peer.addr));
                        s.CloseSocket(acc);
                        continue;   // RAW: back to the select loop
                    }
                    // RAW LAB_1400048d6: first slot with active == 0
                    int pos = 0;
                    while (pos < kMonitorMaxClients
                            && st->slots[pos]->active != 0) {
                        ++pos;
                    }
                    if (kMonitorMaxClients <= pos) {
                        ls.CheckF("nNewPosition < CheatingProgram::"
                                  "MAX_CLIENT_NUMA", 0x1b7, kFile);
                        stop = true;
                        break;
                    }
                    SMonClient* c = st->slots[pos];
                    c->active = 1;              // +0x00
                    c->sock = acc;              // +0x08
                    *(uint32_t*)((char*)c + 0x10) = 0;
                    *(uint64_t*)((char*)c + 0x14) = 0;
                    c->used = 0;                // +0x1c
                    activeCount += 1;
                } else {
                    int e = ls.GetLastError();
                    ls.LogErrFmt("Cheating Program Monitor Accept"
                                 " client failed : %d", e);
                }
            } else {
                ls.LogErrStr("Cheating Program Monitor too many clients");
            }
        }
        // ---- recv on the ready slots (1..63) ----
        for (int i = 1; i < kMonitorMaxClients && remaining >= 1; ++i) {
            st->spinRecv += 1;
            if (1000000 < (int)st->spinRecv) {
                ls.CheckF("DEAD_LOOP_BREAK", 0x208, kFile);
                stop = true;
                break;
            }
            SMonClient* c = st->slots[i];
            if (c->active == 0) {
                continue;
            }
            if (!ls.FdIsSet(c->sock, &set)) {
                continue;
            }
            remaining -= 1;
            uint32_t len = (uint32_t)(0x8000 - c->used);
            if (len == 0) {
                ls.CheckF("WSABuff.len > 0", 0x1da, kFile);
            }
            void* buf = (char*)c + 0x20 + c->used;
            uint32_t got = 0, flags = 0;
            int rc = ls.WsaRecv(c->sock, buf, len, &got, &flags);
            if (rc == 0 && got != 0) {
                ls.ParsePacket(buf, got);   // 140001c70
                c->used += (int)got;        // +0x1c += bytes
                ls.PostRecv();              // 140002510
            } else {
                SMonPeer peer;
                memset(&peer, 0, sizeof peer);
                int plen = 0x10;
                if (ls.GetPeerName(c->sock, &peer, &plen) == 0) {
                    ls.LogMessage("Cheating Program Monitor client"
                                  "(%s : %u) logout",
                                  ls.InetNtoa(peer.addr),
                                  (unsigned)peer.port);
                } else {
                    ls.LogMessage("Cheating Program Monitor one"
                                  " client logout");
                }
                ls.Shutdown(c->sock, 2);
                s.CloseSocket(c->sock);
                c->active = 0;
                c->sock = 0;
                activeCount -= 1;
            }
        }
    }
    // ---- stop path (RAW LAB_14000524a): the message, the
    // listener close, every live slot shut down, WSACleanup ----
    ls.LogMessage("Cheating Program Monitor Thread stop");
    s.CloseSocket(st->listenSock);
    for (int i = 1; i < kMonitorMaxClients; ++i) {
        SMonClient* c = st->slots[i];
        if (c->active != 0) {
            ls.Shutdown(c->sock, 2);
            s.CloseSocket(c->sock);
            c->active = 0;
            c->sock = 0;
        }
    }
    ls.WsaCleanup();
    st->activeCount = activeCount;
    return 0;
}
}
