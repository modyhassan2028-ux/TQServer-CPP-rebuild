#ifndef MSG_AUTH_CLIENT_H
#define MSG_AUTH_CLIENT_H
// ===== Path-A wave 9d: the auth-client class (RAW batch) =====
// 140005c10 ctor   — sock=-1, u10/14/18=0, szA/szB/state=0,
//                    name[0]=0, memset(bufA,0x1000),
//                    memset(bufB,0x1000)
// 140005ea0 Connect — the verbatim state machine (state 0/1/2),
//                    socket/setsockopt(8,0x1001,0x1002)/ioctlsocket
//                    (0x8004667e), inet_addr → gethostbyname,
//                    connect with WSAEWOULDBLOCK (0x2733) allowed,
//                    select(0x40,NULL,&w,&e,{p4,1000}) then the
//                    double getsockopt on the exc then write sets
// 140005e80 IsConnected — state==2 && sock!=-1
// 140005d20 Close   — closesocket if != -1, sock=-1, state=0,
//                     szA=0, szB=0
// 140005b50 WsaInit — WSAStartup(2,&wsa), version check
// 14001e0b0 SendKey — RAW-verified: sprintf(buf,"%u %u",
//                    _time32(0), arg), log "%d:%s" (len, buf),
//                    then buf[i] = nibble-swap(buf[i] ^ key[i%10])
//                    with key "tqdigital\0", then Fn6880(obj,
//                    buf, len, 1)
#include <cstdint>
#include <cstddef>
namespace msg {
#pragma pack(push, 1)
struct SAuthClient {               // 0x2034 bytes (RAW)
    char     name[0x10];           // +0x0000
    uint32_t u10;                  // +0x0010 port
    uint32_t u14;                  // +0x0014 sndbuf
    uint32_t u18;                  // +0x0018 rcvbuf
    int64_t  sock;                 // +0x0020 (-1 = invalid)
    unsigned char bufA[0x1000];    // +0x0028
    uint32_t szA;                  // +0x1028
    unsigned char bufB[0x1000];    // +0x102c
    uint32_t szB;                  // +0x202c
    uint32_t state;                // +0x2030 (bytes 2030..2033)
};
#pragma pack(pop)
struct SAuthSeams {
    void* (*New)(size_t n);        // host-side allocation seam
    void  (*Del)(void* p);
    // tq::SafeCopy(dst, src, 0x10)
    void  (*SafeCopy)(char* dst, const char* src, size_t n);
    void  (*LogErrNoArg)();        // log_InlineLogERROR(&DAT_..)
    void  (*LogErrStr)(const char* s);
    void  (*LogErrFmt)(const char* s, int v);
    void  (*LogMsgFmt)(const char* s, int v, const char* t);
    // winsock ordinals
    int64_t (*Socket)(int af, int type);              // 23
    int   (*SetSockOpt)(int64_t s, int lvl, int opt, const void* v);
    int   (*IoctlSocket)(int64_t s, long cmd, void* v);
    int32_t (*InetAddr)(const char* name);            // 11
    void* (*GetHostByName)(const char* name);         // 52
    int   (*Connect)(int64_t s, const void* sa, int n); // 4
    int   (*Select)(int n, void* rd, void* wr, void* ex, void* tv); // 18
    int   (*GetSockOpt)(int64_t s, void* v);          // 151
    int   (*GetLastError)();                          // 111
    int   (*CloseSocketOrd)(int64_t s);               // 3
    int   (*WsaStartup)(int ver, void* data);         // 115
    int   (*Recv)(int64_t s, void* b, int n, int f);  // 16
    int   (*Send)(int64_t s, const void* b, int n, int f); // 19
    uint16_t (*Htons)(uint16_t p);                    // 9
    uint32_t (*Time32)();                             // _time32(NULL)
    int   (*Sprintf2u)(char* buf, uint32_t a, uint32_t b);
    size_t (*StrLen)(const char* s);
    // FUN_140006880(obj, buf, len, mode)
    int   (*Fn6880)(void* obj, const char* buf, uint32_t len, int mode);
};
void* AuthClientCtor(SAuthClient* p, const SAuthSeams& s);          // 140005c10
int   AuthClientConnect(SAuthClient* p, const char* name,
        uint32_t u3, uint32_t u4, uint32_t u5, uint32_t u6,
        const SAuthSeams& s);                                       // 140005ea0
int   AuthClientIsConnected(const SAuthClient* p);                  // 140005e80
void  AuthClientClose(SAuthClient* p, const SAuthSeams& s);         // 140005d20
int   AuthClientWsaInit(const SAuthSeams& s);                       // 140005b50
void  AuthClientSendKey(SAuthClient* p, uint32_t arg,
        const SAuthSeams& s);                                       // 14001e0b0
// ---- the packet half of the class (wave 9e) ----
// 140005c70 ClearPacket — the OutBufSize error log, the memmove
//            of the remainder, szA -= n, the clamp to 0
// 140005d60 Flush       — send(sock, bufB, szB, 0), the shift of
//            the remainder, the negative-size noarg log, the
//            WSAECONNRESET (0x2746) special case, then the full
//            failure reset (sock=-1, state/szA/szB=0)
// 140006730 GetPacket   — *pLen=0, state==2 && sock!=-1 gate, the
//            recv into bufA+szA of (0x1000-szA), 0 -> close-be-
//            close log, -1 -> 0x2733/0x2746 tolerated else
//            "recv packet failed[%d].", then *pLen=szA and
//            return bufA (even when nothing was read)
// 140006880 SendPacket  — state==2 gate, invalid-socket log, the
//            pre-flush when len+szB>0x1000, the memcpy append,
//            optional flush, and the "buf full!" reset path
// 1400062f0 ConnectStored — the 2-arg twin of Connect: name must
//            already be set (noarg log at 0xc7), no SafeCopy, no
//            port store, tv_sec = the argument, tv_usec = 1000
int   AuthClientClearPacket(SAuthClient* p, int nLen,
        const SAuthSeams& s);                                       // 140005c70
int   AuthClientFlush(SAuthClient* p, const SAuthSeams& s);         // 140005d60
void* AuthClientGetPacket(SAuthClient* p, uint32_t* pLen, int bRecv,
        const SAuthSeams& s);                                       // 140006730
int   AuthClientSendPacket(SAuthClient* p, const void* buf, int len,
        int bFlush, const SAuthSeams& s);                           // 140006880
// The REAL 140006880: pass this as SAuthSeams::Fn6880 so SendKey
// writes through the genuine SendPacket instead of a stub.
void  AuthClientUseSeams(const SAuthSeams* s);
int   AuthClientFn6880(void* obj, const char* buf, uint32_t len,
                       int mode);
int   AuthClientConnectStored(SAuthClient* p, uint32_t tvSec,
        const SAuthSeams& s);                                       // 1400062f0
}
#endif
