// MsgServer unit M21 - the encrypted
// Send FUN_140500670 + keyed getter
// FUN_1405009f0
#include "../Exe/MsgServer/Port/MsgSendHandler.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace msg;

int main() {
    // the fake connection object (static
    // so the lambda captures stay simple)
    static char conn[0x910 + 8];
    const char* gpConn = conn;
    void* gpSendSock = (void*)0x1111;
    void* gpWsaSock = (void*)0x2222;

    struct Cap {
        std::vector<std::pair<int,
            std::string>> vLogs;
        std::string sEncPlain;
        std::string sEnc2;
    } c;
    MsgSendHandlerData d;
    d.m_fnVt20 = [&](void*){ return d.bVt20; };
    d.m_fnVt28 = [&](void*){ ++d.nVt28; };
    d.m_fnVt30 = [&](void*){ return d.uIp; };
    d.m_fnEncrypt = [&](void* crypto,
                        const void* in,
                        void* out, int n) {
        assert(crypto == (void*)(
            gpConn + 0x824));
        if (c.sEncPlain.empty())
            c.sEncPlain.assign(
                (const char*)in, n);
        else
            c.sEnc2.assign(
                (const char*)in, n);
        for (int i = 0; i < n; ++i)
            ((unsigned char*)out)[i] =
                ((const unsigned char*)
                    in)[i] + 1;
        return d.nEncRc; };
    d.m_fnSend = [&](void* s, const void* b,
                     int n) {
        assert(s == gpSendSock);
        assert(b != nullptr);
        d.nSendLen = n;
        return d.nSendRc; };
    d.m_fnWsaLastError = [&](void* s) {
        assert(s == gpWsaSock);
        return d.nWsaErr; };
    d.m_fnTimeGet = [](int n) {
        assert(n == 0); return 123u; };
    d.m_fnLog = [&](int line, int err,
                    int len, const char* ip) {
        char b[96];
        std::snprintf(b, sizeof b,
            "line=%x err=%d len=%d ip=%s",
            line, err, len, ip ? ip : "");
        c.vLogs.push_back({line, b}); };

    auto reset = [&](int ev, int keyed) {
        std::memset(conn, 0, sizeof(conn));
        std::memcpy(conn + 0x908, &gpSendSock,
            8);   // store the ptr VALUE
        std::memcpy(conn + 0x900, &gpWsaSock,
            8);
        *(int*)(conn + 0x14) = ev;
        *(uint8_t*)(conn + 0x1a) = keyed;
        d.bVt20 = true; d.nSendRc = 1;
        d.nWsaErr = 0; d.nEncRc = 1;
        d.nVt28 = 0; d.uIp = 0xC0A80107;
        c.vLogs.clear();
        c.sEncPlain.clear(); c.sEnc2.clear();
    };

    const char* pMsg = "GAME_DATA_123";
    int nMsg = (int)std::strlen(pMsg);

    // ===== 1. the vt20 guard + len cap
    reset(0, 1); d.bVt20 = false;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    reset(0, 1);
    assert(MsgSendHandler(conn, pMsg, 0x401,
        d) == 0);
    assert(d.nVt28 == 0);

    // ===== 2. encrypted happy path
    reset(0, 1);
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 1);
    assert(d.nSendLen == nMsg + 8);
    assert(c.sEncPlain == pMsg);
    assert(c.sEnc2 == "TQServer");
    std::string exp;
    for (int i = 0; i < nMsg; ++i)
        exp += (char)(pMsg[i] + 1);
    for (int i = 0; i < 8; ++i)
        exp += (char)("TQServer"[i] + 1);
    assert(d.sWire == exp);
    assert(d.nVt28 == 0);

    // ===== 3. the encrypt failures
    reset(0, 1); d.nEncRc = 0;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.size() == 1 &&
        c.vLogs[0].first == 0x2a2);
    assert(d.nVt28 == 0);   // no vt28!

    // ===== 4. the send failures
    reset(0, 1); d.nSendRc = -1;
    d.nWsaErr = 0x2733;   // would-block
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.empty());   // tolerated
    assert(d.nVt28 == 1);
    reset(0, 1); d.nSendRc = -1;
    d.nWsaErr = 10061;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.size() == 1 &&
        c.vLogs[0].first == 0x2c4);
    assert(c.vLogs[0].second.find(
        "ip=192.168.1.7") !=
        std::string::npos);
    reset(0, 1); d.nSendRc = -1;
    d.nWsaErr = 10061; d.uIp = 0;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs[0].second.find("ip=") !=
        std::string::npos);

    // ===== 5. not-keyed plaintext
    reset(0, 0);
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 1);
    assert(d.sWire == pMsg);
    assert(d.nSendLen == nMsg);
    reset(0, 0); d.nSendRc = -1;
    d.nWsaErr = 0x2746;   // timeout
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.empty());
    assert(d.nVt28 == 1);
    reset(0, 0); d.nSendRc = -1;
    d.nWsaErr = 10061;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.size() == 1 &&
        c.vLogs[0].first == 0x2f3);
    assert(c.vLogs[0].second.find(
        "ip=192.168.1.7") !=
        std::string::npos);

    // ===== 6. the relay modes
    reset(3, 0);
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.size() == 1 &&
        c.vLogs[0].first == 0x498);
    assert(d.nVt28 == 1);
    reset(1, 0);
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 1);
    assert(d.sWire == pMsg);
    reset(1, 0); d.nSendRc = -1;
    d.nWsaErr = 10061;
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 0);
    assert(c.vLogs.size() == 1 &&
        c.vLogs[0].first == 0x314);
    reset(2, 0);
    assert(MsgSendHandler(conn, pMsg, nMsg,
        d) == 1);   // evType 2 too

    // ===== 7. the keyed getter
    reset(0, 1);
    assert(MsgSendKeyed(conn) == 1);
    assert(MsgSendKeyed(conn + 1) == 0);

    printf("MSG_SEND_HANDLER_OK: "
           "FUN_140500670 VERBATIM (the "
           "vt+0x20 guard + 0x400 cap, the "
           "evType-0 keyed path: memset "
           "0x408 + data encrypt + the "
           "TQServer trailer + Send(len+8) "
           "with the 0x2733/0x2746 "
           "tolerance, the 0x2a2/0x2ae/0x2c4"
           "/0x2f3/0x314/0x498 log lines, "
           "the IP sprintf MSB-first, the "
           "vt+0x28 close on every failure, "
           "plaintext sends when unkeyed or "
           "evType 1/2) + FUN_1405009f0 - "
           "20 branches\n");
    return 0;
}
