// Path-A wave 9d test — the auth-client class (140005c10/5ea0/
// 5e80/5d20/5b50/1e0b0) raw-verified assertions.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include "MsgAuthClient.h"
using namespace msg;
static int g_fail = 0; static int g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
// ---- seam state ----
static int s_sockCall, s_setSock[8], s_ioctlN, s_connectN;
static int64_t s_sockRet; static int s_keepRet, s_sndRet, s_rcvRet;
static int s_ioctlRet, s_connectRet, s_lastErr, s_selectRet;
static int s_gsExc, s_gsWrite, s_closeN; static int64_t s_lastClosed;
static int s_wsaRet; static short s_wsaVer;
static std::string s_logs; static std::vector<std::string> s_logV;
static int s_lvl[8], s_opt[8], s_optVal[8];
static char s_lastName[32]; static uint16_t s_htonsIn;
static int s_6880N; static std::string s_6880Buf; static int s_6880Mode;
static int s_recvRet, s_recvN, s_recvLen; static int s_sendRet, s_sendN;
static std::string s_sent; static int s_tvSec = -1, s_tvUsec = -1;
static uint32_t s_timeVal = 1700000000u;
static void* TNew(size_t n) { return std::calloc(1, n ? n : 1); }
static void TDel(void* p) { std::free(p); }
static void TSafeCopy(char* d, const char* s2, size_t n) {
    memset(d, 0, 0x10); strncpy(d, s2, n);
}
static void TLogNoArg() { s_logV.push_back("<noarg>"); }
static void TLogStr(const char* s2) { s_logV.push_back(s2); }
static void TLogFmt(const char* s2, int v) {
    char b[256]; snprintf(b, sizeof b, s2, v); s_logV.push_back(b); }
static void TLogMsg(const char* s2, int v, const char* t) {
    char b[256]; snprintf(b, sizeof b, s2, v, t); s_logV.push_back(b); }
static int64_t TSocket(int, int) { s_sockCall++; return s_sockRet; }
static int TSetSockOpt(int64_t, int lvl, int opt, const void* v) {
    int i = s_setSock[0]++;
    if (i < 8) { s_lvl[i] = lvl; s_opt[i] = opt;
        s_optVal[i] = v ? *(const int*)v : -999; }
    if (opt == 8) return s_keepRet;
    if (opt == 0x1001) return s_sndRet;
    if (opt == 0x1002) return s_rcvRet;
    return 0;
}
static int TIoctl(int64_t, long cmd, void*) {
    s_ioctlN++; if (cmd != 0x8004667e) return -99; return s_ioctlRet; }
static int32_t TInetAddr(const char* n) {
    strncpy(s_lastName, n, sizeof s_lastName - 1);
    return -1;                       // always -> gethostbyname
}
static void* s_host; static int32_t s_hostAddr;
static void* TGetHost(const char*) { return s_host; }
static int TConnect(int64_t, const void*, int n) {
    s_connectN++; if (n != 0x10) return -98; return s_connectRet; }
static int TSelect(int n, void*, void*, void*, void* tvp) {
    if (n != 0x40) return -97;
    if (tvp) { s_tvSec = ((int*)tvp)[0]; s_tvUsec = ((int*)tvp)[1]; }
    return s_selectRet;
}
static int TRecv(int64_t, void* b, int n, int) {
    s_recvN++; s_recvLen = n;
    if (s_recvRet > 0) { memset(b, 0xAB, (size_t)s_recvRet); }
    return s_recvRet; }
static int TSend(int64_t, const void* b, int n, int) {
    s_sendN++; s_sent.assign((const char*)b, (size_t)n); return s_sendRet; }
static int s_gsC = 0;
static int TGetSockOpt(int64_t, void* v) {
    ++s_gsC;
    return (s_gsC & 1) ? s_gsExc : s_gsWrite;   // 1st = exc, 2nd = write
}
static int TGetLastError() { return s_lastErr; }
static int TCloseOrd(int64_t s2) { s_closeN++; s_lastClosed = s2; return 0; }
static int TWsa(int, void* d) {
    ((short*)d)[0] = s_wsaVer; return s_wsaRet; }
static uint16_t THtons(uint16_t p) { s_htonsIn = p;
    return (uint16_t)((p >> 8) | (p << 8)); }
static uint32_t TTime() { return s_timeVal; }
static int TSprintf(char* b, uint32_t a, uint32_t c) {
    return sprintf(b, "%u %u", a, c); }
static int TFn6880(void*, const char* b, uint32_t len, int mode) {
    s_6880N++; s_6880Buf.assign(b, len); s_6880Mode = mode; return 1; }
static SAuthSeams S;
static void Wire() {
    S.New = TNew; S.Del = TDel; S.SafeCopy = TSafeCopy;
    S.LogErrNoArg = TLogNoArg; S.LogErrStr = TLogStr;
    S.LogErrFmt = TLogFmt; S.LogMsgFmt = TLogMsg;
    S.Socket = TSocket; S.SetSockOpt = TSetSockOpt;
    S.IoctlSocket = TIoctl; S.InetAddr = TInetAddr;
    S.GetHostByName = TGetHost; S.Connect = TConnect;
    S.Select = TSelect; S.GetSockOpt = TGetSockOpt;
    S.GetLastError = TGetLastError; S.CloseSocketOrd = TCloseOrd;
    S.WsaStartup = TWsa; S.Htons = THtons; S.Time32 = TTime;
    S.Sprintf2u = TSprintf; S.StrLen = strlen; S.Fn6880 = TFn6880;
    S.Recv = TRecv; S.Send = TSend;
}
static std::vector<void*> g_live;
static SAuthClient* NewAC() {
    SAuthClient* p = (SAuthClient*)TNew(sizeof(SAuthClient));
    g_live.push_back(p);
    return (SAuthClient*)AuthClientCtor(p, S);
}
static void ResetAll() {
    s_sockCall = s_ioctlN = s_connectN = s_closeN = s_6880N = 0;
    s_setSock[0] = 0; s_sockRet = 100; s_keepRet = s_sndRet = s_rcvRet = 0;
    s_ioctlRet = s_connectRet = 0; s_lastErr = 0;
    s_selectRet = 2; s_gsExc = 0; s_gsWrite = 1; s_gsC = 0;
    s_recvRet = 0; s_recvN = s_sendN = 0; s_sendRet = 0; s_sent.clear();
    s_tvSec = s_tvUsec = -1;
    s_wsaRet = 0; s_wsaVer = 2; s_logV.clear(); s_htonsIn = 0;
    s_host = nullptr;
    static char hostbuf[64];
    memset(hostbuf, 0, sizeof hostbuf);
    *(void**)(hostbuf + 0x18) = hostbuf + 0x20;
    *(int32_t*)(hostbuf + 0x20) = 0x0100007f;
    s_host = hostbuf; s_hostAddr = 0x0100007f;
}
int main() {
    Wire();
    SECT("A9d-1 ctor");
    ResetAll();
    SAuthClient* p = NewAC();
    CHECK(p->sock == -1, "sock = -1");
    CHECK(p->u10 == 0 && p->u14 == 0 && p->u18 == 0, "u10/14/18 zero");
    CHECK(p->szA == 0 && p->szB == 0 && p->state == 0,
          "szA/szB/state zero");
    CHECK(p->name[0] == '\0', "name empty");
    p->bufA[0x10] = 7; p->bufB[0x10] = 7;
    NewAC();
    CHECK(p->bufA[0x10] == 7, "ctor zeroes only its own object");
    SECT("A9d-2 wsa");
    ResetAll();
    CHECK(AuthClientWsaInit(S) == 1, "wsa ok");
    ResetAll(); s_wsaRet = 1;
    CHECK(AuthClientWsaInit(S) == 0, "wsa fail -> 0");
    CHECK(!s_logV.empty() && s_logV.back() == "ERROR: Init WSAStartup() failed.",
          "RAW wsa fail text");
    ResetAll(); s_wsaVer = 1;
    CHECK(AuthClientWsaInit(S) == 0, "version mismatch -> 0");
    CHECK(s_logV.back() == "ERROR: WSAStartup Version not match 2.0",
          "RAW version text");
    SECT("A9d-3 connect happy");
    ResetAll();
    p = NewAC();
    int r = AuthClientConnect(p, "auth.local", 6000, 3, 8192, 4096, S);
    CHECK(r == 1, "returns 1");
    CHECK(strcmp(p->name, "auth.local") == 0, "name copied");
    CHECK(p->u10 == 6000 && p->u14 == 8192 && p->u18 == 4096,
          "port/snd/rcv stored");
    CHECK(s_sockCall == 1, "socket() once");
    CHECK(s_setSock[0] == 3, "three setsockopt calls");
    CHECK(s_lvl[0] == 0xffff && s_opt[0] == 8 && s_optVal[0] == 1,
          "SO_KEEPALIVE=1");
    CHECK(s_opt[1] == 0x1001 && s_optVal[1] == 8192, "SO_SNDBUF");
    CHECK(s_opt[2] == 0x1002 && s_optVal[2] == 4096, "SO_RCVBUF");
    CHECK(s_ioctlN == 1, "FIONBIO once");
    CHECK(s_htonsIn == 6000, "htons(port)");
    CHECK(s_connectN == 1, "connect once");
    CHECK(p->state == 2, "state = 2");
    CHECK(AuthClientIsConnected(p) == 1, "IsConnected true");
    CHECK(s_logV.empty(), "no error logs");
    SECT("A9d-4 already connected");
    ResetAll();
    r = AuthClientConnect(p, "second", 1, 1, 0, 0, S);
    CHECK(r == 1, "returns 1");
    CHECK(s_sockCall == 0, "no socket call");
    CHECK(s_logV.size() == 1 && s_logV[0] == "<noarg>",
          "state!=0 -> noarg log");
    CHECK(strcmp(p->name, "second") == 0, "name still copied");
    SECT("A9d-5 socket fail");
    ResetAll(); p = NewAC(); s_sockRet = -1;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_logV.back() == "Create socket() failed.", "RAW text");
    CHECK(p->sock == -1, "sock stays -1");
    SECT("A9d-6 keepalive fail");
    ResetAll(); p = NewAC(); s_keepRet = -1;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_logV.back() == "setsockopt() set SO_KEEPALIVE failed.", "RAW");
    CHECK(s_closeN == 1, "socket closed");
    SECT("A9d-7 sndbuf fail");
    ResetAll(); p = NewAC(); s_sndRet = -1; s_lastErr = 10055;
    CHECK(AuthClientConnect(p, "h", 1, 1, 512, 0, S) == 0, "0");
    CHECK(s_logV.back() == "setsockopt() set SO_SNDBUF failed[10055].", "RAW");
    SECT("A9d-8 rcvbuf fail");
    ResetAll(); p = NewAC(); s_rcvRet = -1; s_lastErr = 7;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 512, S) == 0, "0");
    CHECK(s_logV.back() == "setsockopt() set SO_RCVBUF failed[7].", "RAW");
    SECT("A9d-9 ioctl fail");
    ResetAll(); p = NewAC(); s_ioctlRet = -1;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_logV.back() == "Init ioctlsocket() failed.", "RAW");
    SECT("A9d-10 host fail");
    ResetAll(); p = NewAC(); s_host = nullptr;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_connectN == 0, "no connect");
    CHECK(s_closeN == 1, "socket closed");
    SECT("A9d-11 connect fail");
    ResetAll(); p = NewAC(); s_connectRet = -1; s_lastErr = 10061;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_logV.back() == "connect to server failed[10061].", "RAW");
    SECT("A9d-12 connect wouldblock");
    ResetAll(); p = NewAC(); s_connectRet = -1; s_lastErr = 0x2733;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 1, "allowed -> 1");
    CHECK(p->state == 2, "state 2");
    SECT("A9d-13 select fail");
    ResetAll(); p = NewAC(); s_selectRet = -1;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_logV.back() == "select socket() failed.", "RAW");
    CHECK(s_closeN == 1 && p->sock == -1 && p->state == 0,
          "failure path closes + resets");
    SECT("A9d-14 select zero");
    ResetAll(); p = NewAC(); s_selectRet = 0;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "0");
    CHECK(s_closeN == 0 && p->state == 1, "no close, state stays 1");
    SECT("A9d-15 getsockopt gates");
    ResetAll(); p = NewAC(); s_gsExc = 0; s_gsWrite = 0;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "both zero -> 0");
    CHECK(p->state == 1, "state 1");
    ResetAll(); p = NewAC(); s_gsExc = 5;
    CHECK(AuthClientConnect(p, "h", 1, 1, 0, 0, S) == 0, "exc!=0 -> 0");
    CHECK(s_closeN == 1 && p->state == 0, "failure path (RAW)");
    SECT("A9d-16 isConnected matrix");
    SAuthClient x; memset(&x, 0, sizeof x);
    x.state = 2; x.sock = 5;
    CHECK(AuthClientIsConnected(&x) == 1, "2 + sock -> 1");
    x.sock = -1;
    CHECK(AuthClientIsConnected(&x) == 0, "2 + -1 -> 0");
    x.state = 1; x.sock = 5;
    CHECK(AuthClientIsConnected(&x) == 0, "1 -> 0");
    SECT("A9d-17 close");
    ResetAll(); p = NewAC(); p->sock = 77; p->state = 2;
    p->szA = 5; p->szB = 6;
    AuthClientClose(p, S);
    CHECK(s_closeN == 1 && s_lastClosed == 77, "closesocket(77)");
    CHECK(p->sock == -1 && p->state == 0 && p->szA == 0 && p->szB == 0,
          "reset");
    ResetAll(); p = NewAC();
    AuthClientClose(p, S);
    CHECK(s_closeN == 0, "no close when -1");
    SECT("A9d-18 sendkey");
    ResetAll(); p = NewAC(); s_timeVal = 1700000123u;
    AuthClientSendKey(p, 4242, S);
    CHECK(s_6880N == 1 && s_6880Mode == 1, "Fn6880 once, mode 1");
    {
        char raw[64];
        int rl = sprintf(raw, "%u %u", 1700000123u, 4242u);
        CHECK((int)s_6880Buf.size() == rl, "len = strlen");
        const char* key = "tqdigital";
        bool good = true;
        for (int i = 0; i < rl; ++i) {
            unsigned char c = (unsigned char)(key[i % 10] ^ raw[i]);
            unsigned char exp = (unsigned char)((c << 4) | (c >> 4));
            if ((unsigned char)s_6880Buf[i] != exp) good = false;
        }
        CHECK(good, "nibble-swap XOR matches the RAW loop");
        CHECK(s_logV.size() == 1, "one %d:%s log");
        CHECK(s_logV[0].find("1700000123 4242") != std::string::npos,
              "log carries the plaintext");
    }

    SECT("A9e-19 ClearPacket");
    ResetAll(); p = NewAC(); p->state = 2; p->szA = 10;
    memset(p->bufA, 'x', 12);
    CHECK(AuthClientClearPacket(p, 4, S) == 1, "rest > 0 -> 1");
    CHECK(p->szA == 6, "szA 10-4");
    CHECK(memcmp(p->bufA, "xxxx", 4) == 0 && p->bufA[6] == 'x',
          "remainder shifted to the head");
    CHECK(s_logV.empty(), "no log when szA >= n");
    ResetAll(); p = NewAC(); p->state = 2; p->szA = 3;
    CHECK(AuthClientClearPacket(p, 5, S) == 0, "over-clear -> 0");
    CHECK(p->szA == 0, "clamped to 0");
    CHECK(s_logV.size() == 1, "OutBufSize error logged");
    ResetAll(); p = NewAC(); p->state = 1; p->szA = 9;
    CHECK(AuthClientClearPacket(p, 2, S) == 0, "state!=2 -> 0");
    CHECK(p->szA == 9, "szA untouched");
    SECT("A9e-20 Flush");
    ResetAll(); p = NewAC();
    CHECK(AuthClientFlush(p, S) == 0, "state!=2 -> 0");
    p->state = 2; p->szB = 0;
    CHECK(AuthClientFlush(p, S) == 1, "empty -> 1");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9;
    memset(p->bufB, 'a', 8); p->szB = 8; s_sendRet = 8;
    CHECK(AuthClientFlush(p, S) == 1, "full send -> 1");
    CHECK(s_sendN == 1 && s_sent.size() == 8, "send(sock,bufB,8,0)");
    CHECK(p->szB == 0, "szB drained");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9;
    memset(p->bufB, 'a', 8); p->szB = 8; s_sendRet = 3;
    CHECK(AuthClientFlush(p, S) == 0, "partial -> 0");
    CHECK(p->szB == 5 && p->bufB[0] == 'a', "5 remain");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; p->szB = 4; s_sendRet = -1;
    s_lastErr = 10054;
    CHECK(AuthClientFlush(p, S) == 0, "send fail -> 0");
    CHECK(p->sock == -1 && p->state == 0 && p->szA == 0 && p->szB == 0,
          "full reset");
    CHECK(s_logV.empty(), "WSAECONNRESET (0x2746) not logged");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; p->szB = 4; s_sendRet = -1;
    s_lastErr = 10053;
    CHECK(AuthClientFlush(p, S) == 0, "other err -> 0");
    CHECK(s_logV.size() == 1 && s_logV[0] == "Flush packet failed[10053].",
          "RAW format with the error");
    SECT("A9e-21 GetPacket");
    ResetAll(); p = NewAC();
    CHECK(AuthClientGetPacket(p, nullptr, 1, S) == nullptr, "null len -> 0");
    uint32_t len = 77;
    CHECK(AuthClientGetPacket(p, &len, 1, S) == nullptr, "state!=2 -> 0");
    CHECK(len == 0, "*pLen zeroed first");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = -1;
    CHECK(AuthClientGetPacket(p, &len, 1, S) == nullptr, "sock -1 -> 0");
    CHECK(s_logV.size() == 1 &&
          s_logV[0] == "GetPacket() invalid socket failed.", "RAW text");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; p->szA = 5;
    void* r2 = AuthClientGetPacket(p, &len, 0, S);
    CHECK(r2 == (void*)p->bufA, "returns bufA");
    CHECK(len == 5 && s_recvN == 0, "no recv when bRecv=0, len=szA");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; s_recvRet = 6;
    r2 = AuthClientGetPacket(p, &len, 1, S);
    CHECK(len == 6 && p->szA == 6, "recv 6 appended");
    CHECK(s_recvLen == 0x1000, "recv size = 0x1000 - szA");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; s_recvRet = 0;
    // RAW falls through to LAB_140006857 after the close: it still
    // sets *pLen and returns bufA (len 0).
    r2 = AuthClientGetPacket(p, &len, 1, S);
    CHECK(r2 == (void*)p->bufA, "close still returns bufA (RAW)");
    CHECK(len == 0, "len 0 after close");
    CHECK(s_logV.size() == 1 && s_logV[0] == "GetPacket() connect be close.",
          "RAW close text");
    CHECK(p->sock == -1 && p->state == 0, "Close ran");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; s_recvRet = -1;
    s_lastErr = 0x2733;
    r2 = AuthClientGetPacket(p, &len, 1, S);
    CHECK(r2 == (void*)p->bufA && len == 0, "WOULDBLOCK -> bufA/0");
    CHECK(s_logV.empty(), "0x2733 not logged");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; s_recvRet = -1;
    s_lastErr = 1234;
    AuthClientGetPacket(p, &len, 1, S);
    CHECK(s_logV.size() == 1 && s_logV[0] == "recv packet failed[1234].",
          "RAW recv error text");
    SECT("A9e-22 SendPacket");
    ResetAll(); p = NewAC();
    CHECK(AuthClientSendPacket(p, "ab", 2, 0, S) == 0, "state!=2 -> 0");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = -1;
    CHECK(AuthClientSendPacket(p, "ab", 2, 0, S) == 0, "-1 sock -> 0");
    CHECK(s_logV.size() == 1 &&
          s_logV[0] == "SendPacket() invalid socket failed.", "RAW text");
    CHECK(p->sock == -1 && p->state == 0, "reset");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9;
    CHECK(AuthClientSendPacket(p, "ab", 2, 0, S) == 1, "append -> 1");
    CHECK(p->szB == 2 && p->bufB[0] == 'a' && p->bufB[1] == 'b', "copied");
    CHECK(s_sendN == 0, "no flush without bFlush");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9; s_sendRet = 2;
    CHECK(AuthClientSendPacket(p, "ab", 2, 1, S) == 1, "bFlush -> Flush=1");
    CHECK(s_sendN == 1 && p->szB == 0, "flushed");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9;
    memset(p->bufB, 'z', 0x1000); p->szB = 0x0fff; s_sendRet = 0x0fff;
    int rr = AuthClientSendPacket(p, "ab", 2, 0, S);
    CHECK(s_sendN == 1, "pre-flush when len+szB > 0x1000");
    CHECK(rr == 1 && p->szB == 2 && p->bufB[0] == 'a',
          "after the pre-flush the append fits");
    // NOTE (RAW analysis): the "SendPacket() buf full!" branch is
    // DEAD CODE. Both guards test the same sum (len+szB): the first
    // flushes above 0x1000, and after Flush szB is either 0 (reset)
    // or szB-sent, so (szB+len < 0x1001) is always true. Proven by
    // the identical conditions, not by guessing.
    SECT("A9e-23 ConnectStored");
    ResetAll(); p = NewAC();
    CHECK(AuthClientConnectStored(p, 7, S) == 1, "happy -> 1");
    CHECK(s_logV.size() == 1 && s_logV[0] == "<noarg>",
          "empty name noarg log (0xc7)");
    CHECK(s_tvSec == 7 && s_tvUsec == 1000, "select tv {7,1000}");
    CHECK(p->state == 2, "state 2");
    CHECK(s_sockCall == 1 && s_setSock[0] == 1, "socket + keepalive only");
    ResetAll(); p = NewAC(); p->state = 2; p->sock = 9;
    CHECK(AuthClientConnectStored(p, 3, S) == 1, "already -> 1");
    CHECK(s_sockCall == 0, "no socket");
    ResetAll(); p = NewAC(); s_sockRet = -1;
    CHECK(AuthClientConnectStored(p, 3, S) == 0, "socket fail -> 0");
    for (void* q : g_live) TDel(q);
    if (g_fail == 0) printf("AUTHCLIENT-OK: %d assertions\n", g_ok);
    else printf("AUTHCLIENT-FAIL\n");
    return g_fail ? 1 : 0;
}
