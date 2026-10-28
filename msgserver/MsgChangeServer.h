#ifndef MSG_CHANGE_SERVER_H
#define MSG_CHANGE_SERVER_H
// ===== Path-A wave 9m: the change-server path =====
// 14002f100 ForwardToMsgPort(port, msg)
//   The 0x48-byte body is CONTIGUOUS from msg+4 (verified by the
//   RAW local offsets: +4 -> block+0, +8 -> +4, +0xc -> +8,
//   +0x10..+0x3f -> +0xc..+0x3b, +0x40 -> +0x3c, +0x44 -> +0x40,
//   +0x48 -> +0x44). Post(port, 0xe, 0x273f, 0x48, block) and log
//   "receive change server message and send to msgport
//    succeed/failure, action:%u, iduser:%u, idacount:%u, ip:%s
//    Result[%d] InServer[%s]" into gmlog/ChangeServer.
// 14002f260 OnRecResult(port, msg) — switch on *(int*)(msg+4):
//   0 服务器配置中没有对应的IP。
//   1 服务器已经存在该服务器的连接!
//   2 服务器配置的IP与本机不符
//   3 服务器已存在连接，但IP不符
//   4 服务器没有配置该服务名!
//   5 心跳有问题，服务器踢出!
//   6 连接服务器成功                     + post {0, 1}
//   7 转服服务器即将关闭!                + post {1, 1}
//   8 转服服务器繁忙，当前处理数[%u]     + post {2, msg[0x18]}
//   9 转服服务器空闲，当前处理数[%u]     + post {3, msg[0x18]}
//   (all strings extracted from .rdata, GBK decoded; every post is
//    (port, 0xe, 0x2740, 8, &pair) with two u32s)
// DOCUMENTED LIMITS (no guessing):
//   - the decompiler dropped the register-passed varargs of the
//     gmlog call, so iduser/idacount reach the seam from the caller
//     while action(+0xc)/ip(+0x20)/Result(+0x44)/InServer(+0x40 via
//     the server-name lookup) are the memory slots the RAW proves;
//   - 140030ee0 / 140031130 (the socket-thread receive side) are
//     std::map lookups with iterator-debug noise and are NOT ported
//     in this batch.
#include <cstdint>
#include <cstddef>
namespace msg {
static const int  kCsPostId     = 0x0e;
static const int  kCsFwdMsg     = 0x273f;
static const int  kCsResultMsg  = 0x2740;
static const int  kCsBodyLen    = 0x48;
static const int  kCsResultLen  = 8;
struct SChangeServerLog {
    uint32_t action;        // msg + 0x0c
    uint32_t idUser;        // caller (RAW vararg dropped)
    uint32_t idAccount;     // caller (RAW vararg dropped)
    const char* ip;         // msg + 0x20
    int      result;        // msg + 0x44
    const char* inServer;   // server name of msg + 0x40
};
struct SChangeServerSeams {
    int  (*PostMsg)(void* port, int id, int msg, uint32_t len, void* data);
    void (*PortObj)(void* port, void** out);        // +0x40->vt+0x50
    void (*LogChangeServer)(int ok, const SChangeServerLog& f);
    void (*LogChangeServerText)(const char* text);
    const char* (*ServerName)(uint32_t idx);        // Ordinal_12
};
// 14002f100
void ChangeServerForwardToMsgPort(void* port, const void* msg,
                                 const SChangeServerSeams& s);
// 14002f260
void ChangeServerOnRecResult(void* port, const void* msg,
                             const SChangeServerSeams& s);
}
#endif
