// D202 — NpcServer.exe 0x140076670, 0x1400766c0, 0x140076710, 0x140076750 (string/bytes hand-overs).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static const char* g_data = nullptr; static long long g_len = -1; static long long* g_this = nullptr;
static int g_calls620 = 0, g_calls7a0 = 0;
static void T620(const char* p, long long n, long long* t) { g_data = p; g_len = n; g_this = t; ++g_calls620; }
static void T7a0(const char* p, long long n, long long* t) { g_data = p; g_len = n; g_this = t; ++g_calls7a0; }

int main() {
    g_pfnNpc_140077620 = &T620;
    g_pfnNpc_1400777a0 = &T7a0;
    long long aThis[3] = { 0x11, 0x22, 0x33 };

    // the string forms hand over the bytes with the length taken from the string, object last
    {
        std::string s("hello world");
        g_data = nullptr; g_len = -1; g_this = nullptr; g_calls620 = 0; g_calls7a0 = 0;
        FUN_140076670(aThis, &s);
        assert(g_calls620 == 1 && g_calls7a0 == 0);
        assert(g_data == s.data() && g_len == 11 && g_this == aThis);
        g_data = nullptr; g_len = -1; g_this = nullptr;
        FUN_1400766c0(aThis, &s);
        assert(g_calls7a0 == 1 && g_calls620 == 1);
        assert(g_data == s.data() && g_len == 11 && g_this == aThis);
        // an empty string hands over its data pointer and a zero length
        std::string e;
        g_data = nullptr; g_len = -1;
        FUN_140076670(aThis, &e);
        assert(g_len == 0 && g_data == e.data());
    }

    // the raw forms pass the pointer and length straight through, object last
    {
        static const char sz[] = "bytes";
        g_data = nullptr; g_len = -1; g_this = nullptr; g_calls620 = 0; g_calls7a0 = 0;
        FUN_140076710(aThis, sz, 5);
        assert(g_calls620 == 1 && g_data == sz && g_len == 5 && g_this == aThis);
        g_data = nullptr; g_len = -1;
        FUN_140076750(aThis, sz, 2);
        assert(g_calls7a0 == 1 && g_data == sz && g_len == 2 && g_this == aThis);
        // a negative length is passed through as it stands
        g_len = 0;
        FUN_140076710(aThis, sz, -3);
        assert(g_len == -3);
    }

    std::printf("NPCSERVER_D202_OK: 0x140076670/6c0/710/750\n");
    return 0;
}
