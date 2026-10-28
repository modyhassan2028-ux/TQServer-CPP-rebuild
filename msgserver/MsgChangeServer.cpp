// ===== Path-A wave 9m: 14002f100 + 14002f260 =====
#include "MsgChangeServer.h"
#include <cstring>
namespace msg {
// the .rdata texts, GBK-decoded verbatim
static const char* kCsText[10] = {
    "服务器配置中没有对应的IP。",
    "服务器已经存在该服务器的连接!",
    "服务器配置的IP与本机不符",
    "服务器已存在连接，但IP不符",
    "服务器没有配置该服务名!",
    "心跳有问题，服务器踢出!",
    "连接服务器成功",
    "转服服务器即将关闭!",
    "转服服务器繁忙，当前处理数[%u]",
    "转服服务器空闲，当前处理数[%u]"
};
void ChangeServerForwardToMsgPort(void* port, const void* msg,
                                 const SChangeServerSeams& s) {
    uint8_t block[kCsBodyLen];
    memcpy(block, (const char*)msg + 4, kCsBodyLen);
    int ok = s.PostMsg(port, kCsPostId, kCsFwdMsg, kCsBodyLen, block);
    SChangeServerLog f;
    f.action    = *(const uint32_t*)((const char*)msg + 0x0c);
    f.idUser    = 0;
    f.idAccount = 0;
    f.ip        = (const char*)msg + 0x20;
    f.result    = *(const int*)((const char*)msg + 0x44);
    f.inServer  = s.ServerName
        ? s.ServerName(*(const uint32_t*)((const char*)msg + 0x40))
        : "";
    s.LogChangeServer(ok ? 1 : 0, f);
}
void ChangeServerOnRecResult(void* port, const void* msg,
                             const SChangeServerSeams& s) {
    int32_t kind = *(const int32_t*)((const char*)msg + 4);
    if (kind < 0 || kind > 9) return;
    uint32_t pair[2];
    switch (kind) {
        case 6:      // 连接服务器成功
            pair[0] = 0; pair[1] = 1;
            s.PostMsg(port, kCsPostId, kCsResultMsg, kCsResultLen, pair);
            s.LogChangeServerText(kCsText[6]);
            return;
        case 7:      // 转服服务器即将关闭!
            s.LogChangeServerText(kCsText[7]);
            pair[0] = 1; pair[1] = 1;
            s.PostMsg(port, kCsPostId, kCsResultMsg, kCsResultLen, pair);
            return;
        case 8:      // 繁忙 + the processed count
            s.LogChangeServerText(kCsText[8]);
            pair[0] = 2;
            pair[1] = *(const uint32_t*)((const char*)msg + 0x18);
            s.PostMsg(port, kCsPostId, kCsResultMsg, kCsResultLen, pair);
            return;
        case 9:      // 空闲 + the processed count
            s.LogChangeServerText(kCsText[9]);
            pair[0] = 3;
            pair[1] = *(const uint32_t*)((const char*)msg + 0x18);
            s.PostMsg(port, kCsPostId, kCsResultMsg, kCsResultLen, pair);
            return;
        default:
            s.LogChangeServerText(kCsText[kind]);
            return;
    }
}
}
