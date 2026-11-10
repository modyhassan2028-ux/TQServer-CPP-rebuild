// D199 — NpcServer.exe 0x140075ef0 (lite message constructor), 0x140075f10 (description),
// 0x140075f60 (byte-size consistency check).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_vt[4];
static unsigned char g_sinks[3][64];
static int g_sinkCalls = 0;
static int g_sinkSeverity[3]; static const char* g_sinkFile[3]; static int g_sinkLine[3];
static void* Sink(void* pOut, int sev, const char* file, int line) {
    if (g_sinkCalls < 3) {
        g_sinkSeverity[g_sinkCalls] = sev; g_sinkFile[g_sinkCalls] = file; g_sinkLine[g_sinkCalls] = line;
    }
    ++g_sinkCalls;
    std::memcpy(pOut, g_sinks[g_sinkCalls % 3], 64);
    return pOut;
}
static const char* g_text[8]; static void* g_textOwner[8]; static int g_textN = 0;
static long long Append(long long pMessage, const char* pszText) {
    if (g_textN < 8) { g_text[g_textN] = pszText; g_textOwner[g_textN] = (void*)pMessage; }
    ++g_textN;
    return pMessage;
}
static int g_failCalls = 0; static int* g_failText[3];
static void Fail(void* finisher, int* pText) {
    if (g_failCalls < 3) g_failText[g_failCalls] = pText;
    ++g_failCalls;
    (void)finisher;
}
static long long g_released[3]; static int g_releaseCalls = 0;
static void Release(long long pMessage) {
    if (g_releaseCalls < 3) g_released[g_releaseCalls] = pMessage;
    ++g_releaseCalls;
}

int main() {
    g_pNpcVtblMessageLite = (const void*)g_vt;
    g_pfnNpc_1400783d0 = &Sink;
    g_pfnNpc_140078030 = &Append;
    g_pfnNpc_140078580 = &Fail;
    g_pfnNpc_140078440 = &Release;

    // the constructor installs only the vtable
    {
        void* obj[4] = { (void*)0x111, (void*)0x222, (void*)0x333, (void*)0x444 };
        FUN_140075ef0(obj);
        assert(obj[0] == (void*)g_vt);
        assert(obj[1] == (void*)0x222 && obj[2] == (void*)0x333 && obj[3] == (void*)0x444);
    }

    // the missing-fields description
    {
        unsigned char storage[sizeof(std::string)];
        std::string* p = FUN_140075f10(nullptr, (std::string*)storage);
        assert(p == (std::string*)storage);
        assert(*p == "(cannot determine missing fields for lite message)");
        p->~basic_string();
    }

    // all three sizes agree: only the unconditional third check is built, with line 0x45
    {
        g_sinkCalls = 0; g_textN = 0; g_failCalls = 0; g_releaseCalls = 0;
        FUN_140075f60(5, 5, 5);
        assert(g_sinkCalls == 1);
        assert(g_sinkSeverity[0] == 3);
        assert(std::strcmp(g_sinkFile[0],
               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc") == 0);
        assert(g_sinkLine[0] == 0x45);
        assert(g_textN == 1);
        assert(std::strcmp(g_text[0], "This shouldn't be called if all the sizes are equal.") == 0);
        assert(g_failCalls == 1);
        assert(g_releaseCalls == 1);                    // the last sink is always released
    }

    // the first size differs: both sized checks are built, at 0x3f and 0x41, and both sinks are released in
    // that order, each release following its own failure
    {
        g_sinkCalls = 0; g_textN = 0; g_failCalls = 0; g_releaseCalls = 0;
        FUN_140075f60(5, 6, 7);
        assert(g_sinkCalls == 3);
        assert(g_sinkLine[0] == 0x3f && g_sinkLine[1] == 0x41 && g_sinkLine[2] == 0x45);
        assert(g_textN == 5);
        assert(std::strcmp(g_text[0],
            "CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): ") == 0);
        assert(std::strcmp(g_text[1],
            "Protocol message was modified concurrently during serialization.") == 0);
        assert(std::strcmp(g_text[2],
            "CHECK failed: (bytes_produced_by_serialization) == (byte_size_before_serialization): ") == 0);
        assert(std::strcmp(g_text[3],
            "Byte size calculation and serialization were inconsistent.  This may indicate a bug in protocol buffers or it may be caused by concurrent modification of the message.") == 0);
        assert(std::strcmp(g_text[4], "This shouldn't be called if all the sizes are equal.") == 0);
        assert(g_failCalls == 3);
        assert(g_releaseCalls == 3);
    }

    // only the produced count differs: the first check is skipped, the second and third run
    {
        g_sinkCalls = 0; g_textN = 0; g_failCalls = 0; g_releaseCalls = 0;
        FUN_140075f60(5, 5, 4);
        assert(g_sinkCalls == 2);
        assert(g_sinkLine[0] == 0x41 && g_sinkLine[1] == 0x45);
        assert(g_textN == 3);
        assert(g_failCalls == 2 && g_releaseCalls == 2);
    }

    // only the after count differs: the first and third checks run
    {
        g_sinkCalls = 0; g_textN = 0; g_failCalls = 0; g_releaseCalls = 0;
        FUN_140075f60(5, 4, 5);
        assert(g_sinkCalls == 2);
        assert(g_sinkLine[0] == 0x3f && g_sinkLine[1] == 0x45);
        assert(g_failCalls == 2 && g_releaseCalls == 2);
    }

    std::printf("NPCSERVER_D199_OK: 0x140075ef0/f10/f60\n");
    return 0;
}
