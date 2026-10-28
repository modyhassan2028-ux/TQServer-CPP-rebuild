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
}
