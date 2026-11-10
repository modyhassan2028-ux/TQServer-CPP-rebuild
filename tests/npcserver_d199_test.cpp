// D199 — NpcServer.exe 0x140075ef0 (lite message constructor), 0x140075f10 (description),
// 0x140075f60 (byte-size consistency check).
//
// Since the log message bodies are real (D211), the checks are observed where the real code ends up: the sink at
// 0x140078470 hands the finished message to the log function seam, so severity, file, line and the whole text are
// read there instead of at the constructor and the append helpers.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_vt[4];
static int g_sinkCalls = 0;
static int g_sinkSeverity[4]; static std::string g_sinkFile[4]; static int g_sinkLine[4];
static std::string g_sinkText[4];
static void LogSink(int nSeverity, const char* pszFile, int nLine, std::string* pText) {
    if (g_sinkCalls < 4) {
        g_sinkSeverity[g_sinkCalls] = nSeverity;
        g_sinkFile[g_sinkCalls] = pszFile != nullptr ? pszFile : "";
        g_sinkLine[g_sinkCalls] = nLine;
        g_sinkText[g_sinkCalls] = pText != nullptr ? *pText : std::string();
    }
    ++g_sinkCalls;
}

static const char* kLitePath = "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc";

int main() {
    g_pNpcVtblMessageLite = (const void*)g_vt;
    g_pfnNpcLogSink_1401035c8 = &LogSink;

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
        assert(*p == "(cannot determine missing fields for lite message)");
        p->~basic_string();
    }

    // all three sizes agree: only the unconditional third check is reached, at line 0x45
    {
        g_sinkCalls = 0;
        FUN_140075f60(5, 5, 5);
        assert(g_sinkCalls == 1);
        assert(g_sinkSeverity[0] == 3);
        assert(g_sinkFile[0] == kLitePath);
        assert(g_sinkLine[0] == 0x45);
        assert(g_sinkText[0] == "This shouldn't be called if all the sizes are equal.");
    }

    // the first size differs: both sized checks are reached, at 0x3f and 0x41, and then the unconditional one
    {
        g_sinkCalls = 0;
        FUN_140075f60(5, 6, 7);
        assert(g_sinkCalls == 3);
        assert(g_sinkLine[0] == 0x3f && g_sinkLine[1] == 0x41 && g_sinkLine[2] == 0x45);
        assert(g_sinkText[0] ==
            "CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): "
            "Protocol message was modified concurrently during serialization.");
        assert(g_sinkText[1] ==
            "CHECK failed: (bytes_produced_by_serialization) == (byte_size_before_serialization): "
            "Byte size calculation and serialization were inconsistent.  This may indicate a bug in protocol "
            "buffers or it may be caused by concurrent modification of the message.");
        assert(g_sinkText[2] == "This shouldn't be called if all the sizes are equal.");
    }

    // only the produced count differs: the first check is skipped, the second and third run
    {
        g_sinkCalls = 0;
        FUN_140075f60(5, 5, 4);
        assert(g_sinkCalls == 2);
        assert(g_sinkLine[0] == 0x41 && g_sinkLine[1] == 0x45);
        assert(g_sinkText[0].find("(bytes_produced_by_serialization)") != std::string::npos);
    }

    // only the after count differs: the first and third checks run
    {
        g_sinkCalls = 0;
        FUN_140075f60(5, 4, 5);
        assert(g_sinkCalls == 2);
        assert(g_sinkLine[0] == 0x3f && g_sinkLine[1] == 0x45);
        assert(g_sinkText[0].find("(byte_size_before_serialization)") != std::string::npos);
    }

    // the text stays as built: the message object's own string is the one handed to the sink, so a second check
    // never reuses the first one's text
    {
        g_sinkCalls = 0;
        FUN_140075f60(1, 2, 3);
        assert(g_sinkCalls == 3);
        assert(g_sinkText[0].find("message_modified_concurrently") == std::string::npos);
        assert(g_sinkText[0] != g_sinkText[1]);
    }

    std::printf("NPCSERVER_D199_OK: 0x140075ef0/f10/f60\n");
    return 0;
}
