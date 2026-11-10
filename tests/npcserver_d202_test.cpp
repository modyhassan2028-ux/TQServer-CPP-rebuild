// D202 — NpcServer.exe 0x140076670, 0x1400766c0, 0x140076710, 0x140076750 (string/bytes hand-overs).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static const char* g_data = nullptr; static long long g_len = -1; static long long* g_this = nullptr;
static int g_destroyed = 0, g_closer = 0, g_slot7 = 0; static long long g_span = 0;
// both the builder and the parse are real now: the wrapper keeps the bytes at +8 and +0x10 with the length at
// +0x18, so the bytes are watched where that wrapper is torn down
static void Destroy(void* w) {
    void** p = (void**)w;
    g_data = (const char*)p[1];
    g_span = (long long)p[2] - (long long)p[1];
    g_len = *(int*)((unsigned char*)w + 0x18);
    ++g_destroyed;
}
// and the object is watched where the parse closes it, through the object's own slot 3
static unsigned char Closer(long long* p) { g_this = p; ++g_closer; return 0; }
static unsigned char Slot7(long long* p, void* a) { (void)p; (void)a; ++g_slot7; return 1; }
static unsigned char T370(void* a, long long* p) { (void)a; (void)p; return 1; }

int main() {
    long long aVt[8];
    std::memset(aVt, 0, sizeof aVt);
    aVt[3] = (long long)&Closer;      // +0x18
    aVt[7] = (long long)&Slot7;       // +0x38
    long long aThis[2] = { (long long)aVt, 0x33 };
    g_pfnNpc_140077370 = &T370;
    g_pfnNpc_14007a700 = &Destroy;

    // the string forms hand over the bytes with the length taken from the string, object last
    {
        std::string s("hello world");
        g_data = nullptr; g_len = -1; g_this = nullptr; g_destroyed = 0; g_closer = 0; g_slot7 = 0;
        FUN_140076670(aThis, &s);
        assert(g_destroyed == 1 && g_closer == 1 && g_slot7 == 0);
        assert(g_data == s.data() && g_len == 11 && g_span == 11 && g_this == aThis);
        g_data = nullptr; g_len = -1; g_this = nullptr;
        FUN_1400766c0(aThis, &s);
                assert(g_destroyed == 2 && g_closer == 2 && g_slot7 == 1);   // the twin closes through slot 7
        assert(g_data == s.data() && g_len == 11 && g_span == 11 && g_this == aThis);
        // an empty string hands over its data pointer and a zero length
        std::string e;
        g_data = nullptr; g_len = -1;
        FUN_140076670(aThis, &e);
        assert(g_len == 0 && g_data == e.data());
    }

    // the raw forms pass the pointer and length straight through, object last
    {
        static const char sz[] = "bytes";
        g_data = nullptr; g_len = -1; g_this = nullptr; g_destroyed = 0; g_closer = 0; g_slot7 = 0;
        FUN_140076710(aThis, sz, 5);
        assert(g_destroyed == 1 && g_data == sz && g_len == 5 && g_this == aThis);
        g_data = nullptr; g_len = -1;
        FUN_140076750(aThis, sz, 2);
        assert(g_slot7 == 1 && g_data == sz && g_len == 2 && g_this == aThis);
        // a negative length is passed through as it stands
        g_len = 0;
        FUN_140076710(aThis, sz, -3);
        assert(g_len == -3);
    }

    std::printf("NPCSERVER_D202_OK: 0x140076670/6c0/710/750\n");
    return 0;
}
