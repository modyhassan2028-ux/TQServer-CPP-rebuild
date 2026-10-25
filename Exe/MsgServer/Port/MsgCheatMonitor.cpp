// ============================================================
// MsgServer strict port - unit M42
// The Cheating Program Monitor: the
// CFB64 wrapper, the packet demux,
// the two report handlers, and the
// thread as a driven state machine.
// ============================================================
#include "MsgCheatMonitor.h"
#include <cstring>
#include <cstdio>

namespace msg {

// the literal from FUN_140003dc0
static const char* kKeyPassword = "df29duw";

// ---------- FUN_140001c70 ----------
int MsgCheatDecryptMsg(uint8_t* msg, long len,
                       const MsgStdDesSchedule& ks,
                       int* num, uint8_t* ivec,
                       MsgCheatSeams& seams) {
    if (msg == nullptr) {
        seams.log_msg(0, "Cheating Program Monitor invalid msg");
        return 0;
    }
    if ((unsigned long)(len - 1) < 0x30) {
        if (num == nullptr)
            return 0;
        MsgStdDesCfb64(msg, msg, len, ks, ivec, num, 0);
        return 1;
    }
    return 0;
}

// ---------- FUN_140001900 ----------
// the type-0 report: copies the 0x30
// packet (qword 5 with byte 47
// masked off), fills the reason if
// packet[0xf] == 0, notifies.
static void ReportType0(const uint8_t* pkt,
                        MsgCheatSeams& seams,
                        void* port) {
    uint8_t report[0x30];
    memset(report, 0, sizeof(report));
    // the 6-qword copy, qword 5 masked
    memcpy(report, pkt, 0x30);
    ((uint64_t*)report)[5] =
        ((const uint64_t*)pkt)[5] & 0x00FFFFFFFFFFFFFF;
    if (pkt[0xf] == 0) {
        const char* src = seams.str("STR_GENERAL_BOT_SIN");
        strncpy((char*)report + 0xf, src, 0x21);
    }
    seams.notify(port, 0xe, 0xea61, 0x30, report);
}

// ---------- FUN_140001a50 ----------
// the type 1..4 report
static void ReportType1to4(const uint8_t* pkt,
                           MsgCheatSeams& seams,
                           void* port) {
    uint16_t type = *(const uint16_t*)(pkt + 4);
    uint8_t* report = new uint8_t[0x30];
    memset(report, 0, 0x30);
    *(uint32_t*)report = *(const uint32_t*)pkt;
    *(uint16_t*)(report + 4) = *(const uint16_t*)(pkt + 4);
    strncpy((char*)(report + 6), (const char*)(pkt + 6), 9);
    const char* reason = nullptr;
    if (type == 1)
        reason = seams.str("STR_GENERAL_BOT_SIN");
    else if (type == 2)
        reason = seams.str("STR_KEY_BOT_SIN");
    else if (type == 3)
        reason = seams.str("STR_SERIOUS_BOT_SIN");
    else if (type == 4)
        reason = seams.str("STR_HACK_TOOL_SIN");
    else {
        seams.log_msg(0,
            "CCheatingProgramMonitor::ProcessMsg, "
            "wrong cheat type : %u");
        delete[] report;
        return;
    }
    strncpy((char*)(report + 0xf), reason, 0x21);
    seams.notify(port, 0xe, 0xea61, 0x30, report);
    delete[] report;
}

// ---------- FUN_140002510 ----------
void MsgCheatProcessRecv(MsgCheatClientInfo* slot,
                         MsgCheatSeams& seams) {
    if (slot == nullptr) {
        seams.log_msg(0, "(null)"); // the truncated CHECKF
        return;
    }
    void* port = seams.get_port(5);
    if (port == nullptr) {
        seams.log_msg(0, "(null port)");
        return;
    }
    unsigned uLoopCount = 0;
    while (true) {
        uLoopCount = uLoopCount + 1;
        if (uLoopCount >= 0x3e9) {
            seams.log_msg(0, "(demux loop overrun)");
            return;
        }
        int nUsed = (int)slot->nUsed;
        if (nUsed < 8)
            return;
        uint8_t* buf = slot->buf;
        uint16_t type = *(const uint16_t*)(buf + 4);
        if (type == 0) {
            if (nUsed < 0x30)
                return;
            ReportType0(buf, seams, port);
            memmove(buf, buf + 0x30,
                    (size_t)(nUsed - 0x30));
            slot->nUsed = (uint32_t)(nUsed - 0x30);
        } else {
            if ((unsigned)(type - 1) > 3)
                return; // the stall case
            if (nUsed < 0xf)
                return;
            ReportType1to4(buf, seams, port);
            memmove(buf, buf + 0xf,
                    (size_t)(nUsed - 0xf));
            slot->nUsed = (uint32_t)(nUsed - 0xf);
        }
    }
}

// ---------- FUN_140003dc0 (init) ----------
bool MsgCheatMonitorInit(MsgCheatMonitorState& st,
                         MsgCheatSeams& seams) {
    st.port = seams.get_port(5);
    if (st.port == nullptr) {
        seams.log_msg(0, "CHECKF pPort");
        return false;
    }
    seams.port_init(st.port);

    // the ini: shell.ini / CheatingMonitor
    void* ini = seams.ini_open("shell.ini",
                               "CheatingMonitor");
    long port = seams.ini_get_int(ini, "ListenPort");
    if (port == 0)
        port = MSG_CHEAT_DEFAULT_PORT;
    st.listen_port = (uint16_t)port;

    int ipNum = (int)seams.ini_get_int(ini, "IPNum");
    if (0x14 < ipNum) {
        ipNum = 0x14;
        seams.log_msg(1,
            "astrict ip number overrun max ip number!");
    }
    st.ip_num = ipNum;
    for (int i = 0; i < ipNum; ++i) {
        char key[16];
        snprintf(key, sizeof(key), "IP%d", i + 1);
        char ipstr[24] = {};
        seams.ini_get_string(ini, ipstr, key, 0x14);
        st.ips[i] = seams.inet_addr(ipstr);
    }

    st.listen_sock = seams.sock_create();
    if (seams.sock_bind(st.listen_sock, st.listen_port) != 0) {
        seams.log_fmt(1,
            "Cheating Program Monitor can not bind to "
            "(%s : %u), nErr : %d", "", st.listen_port, 0);
        seams.sock_close(st.listen_sock);
        return false;
    }
    if (seams.sock_listen(st.listen_sock) != 0) {
        seams.log_fmt1(1,
            "Cheating Program Monitor listen failed : %d", 0);
        seams.sock_close(st.listen_sock);
        return false;
    }

    // the 64 slots (operator_new(0x8020)
    // each, zeroed; CHECKF pClientInfo)
    for (size_t i = 0; i < MSG_CHEAT_MAX_CLIENTS; ++i) {
        st.slots[i] = new MsgCheatClientInfo();
        memset(st.slots[i], 0, sizeof(MsgCheatClientInfo));
    }
    // slot 0 = the listen pseudo-client
    st.slots[0]->bUsed = 1;
    st.slots[0]->sock = st.listen_sock;
    st.nclients = 1;

    // DES_string_to_key("df29duw") +
    // DES_set_key_checked (the return
    // ignored, VERBATIM)
    MsgStdDesStringToKey(kKeyPassword, st.key);
    MsgStdDesSetKeyUnchecked(st.key, st.ks);
    memset(st.ivec, 0, 8);
    st.num = 0;

    char msg[1024];
    snprintf(msg, sizeof(msg),
             "#%u: Cheating Program Monitor thread running.",
             (unsigned)seams.sock_create());
    // (the binary formats the thread id
    // via vt+8 then notifies with
    // ~(uint)strlen)
    size_t len = strlen(msg);
    seams.notify(st.port, 0, 0x9c41,
                 (uint32_t)(~(unsigned)len), nullptr);

    st.initialized = true;
    st.running = true;
    return true;
}

// ---------- FUN_140003dc0 (one tick) ----------
bool MsgCheatMonitorTick(MsgCheatMonitorState& st,
                         MsgCheatSeams& seams) {
    // the state gate: != 2 -> stop
    if (seams.port_state(st.port) != 2) {
        seams.log_msg(2,
            "Cheating Program Monitor Thread stop");
        return false;
    }

    // build the fd set (listen + active
    // clients, deduped, max 64)
    uint64_t fds[MSG_CHEAT_MAX_CLIENTS];
    uint32_t ready[MSG_CHEAT_MAX_CLIENTS];
    size_t count = 0;
    fds[count++] = st.listen_sock;
    for (size_t i = 1; i < MSG_CHEAT_MAX_CLIENTS; ++i) {
        if (count >= MSG_CHEAT_MAX_CLIENTS) break;
        MsgCheatClientInfo* c = st.slots[i];
        if (!c->bUsed || c->sock == 0)
            continue;
        bool dup = false;
        for (size_t j = 0; j < count; ++j)
            if (fds[j] == c->sock) { dup = true; break; }
        if (!dup)
            fds[count++] = c->sock;
    }
    // the 1,000,000 DEAD_LOOP guard on
    // the set-building loop (line 0x177)
    if (count >= 1000000) {
        seams.log_msg(0, "DEAD_LOOP_BREAK uLoopCount");
        return true;
    }

    int nready = seams.sock_select(fds, count, ready,
                                   500); // 0x1F4 usec
    if (nready == -1) {
        seams.log_fmt1(0,
            "Cheating Program Monitor select failed : %d", -1);
        return false;
    }
    if (nready < 1)
        return true; // the 500us poll

    // is the listen socket readable?
    bool listen_ready = false;
    for (int i = 0; i < nready; ++i)
        if (fds[ready[i]] == st.listen_sock)
            listen_ready = true;

    if (listen_ready) {
        uint32_t ip = 0; uint16_t peerport = 0;
        uint64_t cs = seams.sock_accept(st.listen_sock,
                                        &ip, &peerport);
        if (cs != (uint64_t)-1) {
            // the ip allowlist
            bool allowed = false;
            for (int i = 0; i < st.ip_num; ++i)
                if (st.ips[i] == ip) { allowed = true; break; }
            if (!allowed) {
                char ipstr[32];
                snprintf(ipstr, sizeof(ipstr), "%u.%u.%u.%u",
                         (ip >> 24) & 0xff, (ip >> 16) & 0xff,
                         (ip >> 8) & 0xff, ip & 0xff);
                seams.log_fmt(1, "lawless ip address %s!",
                              ipstr, 0, 0);
                seams.sock_close(cs);
            } else {
                if (st.nclients >= (int)MSG_CHEAT_MAX_CLIENTS) {
                    seams.log_msg(0,
                        "Cheating Program Monitor too many clients");
                    seams.sock_close(cs);
                } else {
                    // find the first free slot
                    size_t pos = 1;
                    while (pos < MSG_CHEAT_MAX_CLIENTS - 1 &&
                           st.slots[pos]->bUsed)
                        ++pos;
                    MsgCheatClientInfo* c = st.slots[pos];
                    c->bUsed = 1;
                    c->sock = cs;
                    c->x10 = 0;
                    c->x14 = 0;
                    c->nUsed = 0;
                    st.nclients = st.nclients + 1;
                }
            }
        } else {
            seams.log_fmt1(0,
                "Cheating Program Monitor Accept client "
                "failed : %d", 0);
        }
    }

    // the readable clients
    for (int ri = 0; ri < nready; ++ri) {
        uint32_t idx = ready[ri];
        if (idx >= count || fds[idx] == st.listen_sock)
            continue;
        // locate the slot
        MsgCheatClientInfo* c = nullptr;
        for (size_t i = 1; i < MSG_CHEAT_MAX_CLIENTS; ++i)
            if (st.slots[i]->bUsed &&
                st.slots[i]->sock == fds[idx]) {
                c = st.slots[i];
                break;
            }
        if (!c)
            continue;
        // the WSABUF length MYASSERT
        if (MSG_CHEAT_BUF - c->nUsed == 0) {
            seams.log_msg(0,
                "MYASSERT WSABuff.len > 0");
            continue;
        }
        int n = seams.sock_recv(c->sock,
                                c->buf + c->nUsed,
                                MSG_CHEAT_BUF - c->nUsed);
        if (n > 0) {
            // decrypt EXACTLY the received
            // span, in place, then advance
            MsgCheatDecryptMsg(c->buf + c->nUsed, n,
                               st.ks, &st.num, st.ivec,
                               seams);
            c->nUsed = (uint32_t)(c->nUsed + n);
            MsgCheatProcessRecv(c, seams);
        } else {
            // the logout path
            uint32_t ip = 0; uint16_t pp = 0;
            if (seams.sock_getpeername(c->sock, &ip, &pp) == 0) {
                char ipstr[32];
                snprintf(ipstr, sizeof(ipstr), "%u.%u.%u.%u",
                         (ip >> 24) & 0xff, (ip >> 16) & 0xff,
                         (ip >> 8) & 0xff, ip & 0xff);
                seams.log_fmt(2,
                    "Cheating Program Monitor client(%s : %u) "
                    "logout", ipstr, pp, 0);
            } else {
                seams.log_msg(2,
                    "Cheating Program Monitor one client logout");
            }
            seams.sock_shutdown(c->sock);
            seams.sock_close(c->sock);
            c->bUsed = 0;
            c->sock = 0;
            st.nclients = st.nclients - 1;
        }
    }
    return true;
}

// ---------- FUN_14000524a ----------
void MsgCheatMonitorStop(MsgCheatMonitorState& st,
                         MsgCheatSeams& seams) {
    if (st.listen_sock)
        seams.sock_close(st.listen_sock);
    for (size_t i = 0; i < MSG_CHEAT_MAX_CLIENTS; ++i) {
        MsgCheatClientInfo* c = st.slots[i];
        if (c && c->bUsed && c->sock) {
            seams.sock_shutdown(c->sock);
            seams.sock_close(c->sock);
            c->bUsed = 0;
            c->sock = 0;
        }
        delete st.slots[i];
        st.slots[i] = nullptr;
    }
    st.nclients = 0;
    st.running = false;
    st.initialized = false;
}

} // namespace msg
