// Path-A wave 9m test — 14002f100 + 14002f260.
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "MsgChangeServer.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static int s_postN = 0, s_postId = -1, s_postMsg = -1;
static uint32_t s_postLen = 0; static std::string s_postData;
static int s_okFlag = -1; static SChangeServerLog s_f;
static std::vector<std::string> s_texts;
static int TPost(void*, int id, int m, uint32_t len, void* d) {
    s_postN++; s_postId = id; s_postMsg = m; s_postLen = len;
    if (d) s_postData.assign((const char*)d, len);
    return s_okFlag; }
static void TLog(int ok, const SChangeServerLog& f) { s_okFlag = ok; s_f = f; }
static void TText(const char* t) { s_texts.push_back(t); }
static const char* TName(uint32_t i) { return i == 5 ? "S5" : "S?"; }
static SChangeServerSeams S;
static void Reset() {
    s_postN = 0; s_postId = s_postMsg = -1; s_postLen = 0;
    s_postData.clear(); s_okFlag = 1; s_texts.clear();
    memset(&s_f, 0, sizeof s_f);
}
int main() {
    S.PostMsg = TPost; S.LogChangeServer = TLog;
    S.LogChangeServerText = TText; S.ServerName = TName;
    S.PortObj = nullptr;
    SECT("9m-1 forward to the message port");
    unsigned char m[0x60];
    for (int i = 0; i < 0x60; ++i) m[i] = (unsigned char)(i + 1);
    Reset(); s_okFlag = 1;
    ChangeServerForwardToMsgPort((void*)0x1111, m, S);
    CHECK(s_postN == 1, "one post");
    CHECK(s_postId == 0x0e && s_postMsg == 0x273f, "id 0xe msg 0x273f");
    CHECK(s_postLen == 0x48, "0x48 bytes");
    CHECK(s_postData.size() == 0x48, "body posted");
    CHECK(memcmp(s_postData.data(), m + 4, 0x48) == 0,
          "CONTIGUOUS copy from msg+4");
    CHECK((unsigned char)s_postData[0] == m[4], "first byte is msg+4");
    CHECK((unsigned char)s_postData[0x47] == m[0x4b], "last is msg+0x4b");
    CHECK(s_okFlag == 1, "logged as success");
    CHECK(s_f.action == *(uint32_t*)(m + 0x0c), "action from +0xc");
    CHECK(s_f.result == *(int*)(m + 0x44), "result from +0x44");
    CHECK(s_f.ip == (const char*)m + 0x20, "ip points at +0x20");
    CHECK(std::string(s_f.inServer) == "S?",
          "inServer through the name lookup");
    Reset(); *(uint32_t*)(m + 0x40) = 5;
    ChangeServerForwardToMsgPort((void*)0x1111, m, S);
    CHECK(std::string(s_f.inServer) == "S5", "index 5 -> name S5");
    Reset(); s_okFlag = 0;
    ChangeServerForwardToMsgPort((void*)0x1111, m, S);
    CHECK(s_okFlag == 0, "failure path logs ok=0");
    CHECK(s_postN == 1, "still posts before logging");
    SECT("9m-2 the result switch");
    const char* want[10] = {
        "服务器配置中没有对应的IP。",
        "服务器已经存在该服务器的连接!",
        "服务器配置的IP与本机不符",
        "服务器已存在连接，但IP不符",
        "服务器没有配置该服务名!",
        "心跳有问题，服务器踢出!",
        "连接服务器成功", "转服服务器即将关闭!",
        "转服服务器繁忙，当前处理数[%u]",
        "转服服务器空闲，当前处理数[%u]" };
    unsigned char r[0x20];
    for (int k = 0; k <= 9; ++k) {
        Reset(); memset(r, 0, sizeof r);
        *(int*)(r + 4) = k;
        *(uint32_t*)(r + 0x18) = 77;
        ChangeServerOnRecResult((void*)0x2222, r, S);
        char msg[80];
        snprintf(msg, sizeof msg, "kind %d text", k);
        CHECK(s_texts.size() == 1 && s_texts[0] == want[k], msg);
        if (k >= 6) {
            snprintf(msg, sizeof msg, "kind %d posts 8 bytes", k);
            CHECK(s_postN == 1 && s_postLen == 8 &&
                  s_postMsg == 0x2740, msg);
            uint32_t a = *(uint32_t*)s_postData.data();
            uint32_t b = *(uint32_t*)(s_postData.data() + 4);
            uint32_t ea = (uint32_t)(k - 6), eb = (k >= 8) ? 77u : 1u;
            snprintf(msg, sizeof msg, "kind %d pair {%u,%u}", k, ea, eb);
            CHECK(a == ea && b == eb, msg);
        } else {
            snprintf(msg, sizeof msg, "kind %d no post", k);
            CHECK(s_postN == 0, msg);
        }
    }
    Reset(); memset(r, 0, sizeof r);
    *(int*)(r + 4) = 10;
    ChangeServerOnRecResult((void*)0x2222, r, S);
    CHECK(s_postN == 0 && s_texts.empty(), "kind 10 is ignored");
    Reset(); *(int*)(r + 4) = -1;
    ChangeServerOnRecResult((void*)0x2222, r, S);
    CHECK(s_postN == 0 && s_texts.empty(), "negative kind ignored");
    if (g_fail == 0) printf("CHGSRV-OK: %d assertions\n", g_ok);
    else printf("CHGSRV-FAIL\n");
    return g_fail ? 1 : 0;
}
