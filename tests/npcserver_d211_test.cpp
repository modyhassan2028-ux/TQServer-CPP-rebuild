// D211 — NpcServer.exe log message helpers: 0x1400783d0, 0x140078440, 0x140078030, 0x140077ff0, 0x140078100,
// 0x140078580, 0x140078470.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_logCalls = 0, g_logSeverity = 0, g_logLine = 0;
static std::string g_logFile, g_logText;
static int g_throwCalls = 0;
static int g_order[8]; static int g_orderN = 0;
static void Note(int n) { if (g_orderN < 8) g_order[g_orderN] = n; ++g_orderN; }

static void LogSink(int nSeverity, const char* pszFile, int nLine, std::string* pText) {
    ++g_logCalls; g_logSeverity = nSeverity; g_logLine = nLine;
    g_logFile = pszFile ? pszFile : ""; g_logText = *pText;
    Note(1);
}
static void ThrowFatal(void* pException, void* pThrowInfo) {
    (void)pException; (void)pThrowInfo; ++g_throwCalls; Note(2);
    throw false;                                  // stands in for the exception the sink raises
}
static void Rotate(void) { Note(3); }
static void Lock(void* pLock, void* pConst) { (void)pLock; (void)pConst; Note(4); }
static void Unlock(void* pLock) { (void)pLock; Note(5); }

static unsigned char g_msg[0x40];
static const char* const kFile = "C:\\path\\file.cc";

int main() {
    g_pfnNpcLogSink_1401035c8 = &LogSink;
    g_pfnNpcThrowFatal = &ThrowFatal;
    g_pfnNpc_140077fc0 = &Rotate;
    g_pfnNpc_140078d20 = &Lock;
    g_pfnNpc_140078d60 = &Unlock;

    // the message holds the severity, the file, the line and an empty text
    {
        std::memset(g_msg, 0xCC, sizeof g_msg);
        void* p = FUN_1400783d0(g_msg, 2, kFile, 0x7b);
        assert(p == g_msg);
        assert(*(unsigned int*)(g_msg + 0x00) == 2);
        assert(*(const char**)(g_msg + 0x08) == kFile);
        assert(*(unsigned int*)(g_msg + 0x10) == 0x7b);
        assert(((std::string*)(g_msg + 0x18))->empty());          // a real, empty string

        // the text grows in order: a C string, then another string, then a number
        assert(FUN_140078030((long long)g_msg, "alpha ") == (long long)g_msg);
        std::string sTail = "beta ";
        assert(FUN_140077ff0((long long)g_msg, &sTail) == (long long)g_msg);
        assert(FUN_140078100((long long)g_msg, 42) == (long long)g_msg);
        assert(*(std::string*)(g_msg + 0x18) == "alpha beta 42");

        // a negative number keeps its sign, it is the "%d" of the word
        assert(FUN_140078100((long long)g_msg, 0xFFFFFFF0u) == (long long)g_msg);
        assert(*(std::string*)(g_msg + 0x18) == "alpha beta 42-16");

        FUN_140078440((long long)g_msg);
    }

    // severity 2: rotation, lock, unlock, then the sink with the text as it stands
    {
        std::memset(g_msg, 0, sizeof g_msg);
        FUN_1400783d0(g_msg, 2, kFile, 0x2a);
        FUN_140078030((long long)g_msg, "hello");
        g_logCalls = 0; g_orderN = 0; g_throwCalls = 0;
        g_nNpcConst_140104cd8 = 0;
        FUN_140078470((int*)g_msg);
        assert(g_orderN == 4);
        assert(g_order[0] == 3 && g_order[1] == 4 && g_order[2] == 5 && g_order[3] == 1);
        assert(g_logCalls == 1 && g_logSeverity == 2 && g_logLine == 0x2a);
        assert(g_logFile == kFile && g_logText == "hello");
        assert(g_throwCalls == 0);
        FUN_140078440((long long)g_msg);
    }

    // a quiet rotation keeps the sink closed, but the rotation still runs
    {
        std::memset(g_msg, 0, sizeof g_msg);
        FUN_1400783d0(g_msg, 1, kFile, 7);
        g_logCalls = 0; g_orderN = 0;
        g_nNpcConst_140104cd8 = 1;                     // the rotation said "quiet"
        FUN_140078470((int*)g_msg);
        assert(g_logCalls == 0);
        assert(g_orderN == 3 && g_order[0] == 3 && g_order[1] == 4 && g_order[2] == 5);
        g_nNpcConst_140104cd8 = 0;
        FUN_140078440((long long)g_msg);
    }

    // severity 3 skips the rotation altogether and throws after the sink
    {
        std::memset(g_msg, 0, sizeof g_msg);
        FUN_1400783d0(g_msg, 3, kFile, 0x45);
        g_logCalls = 0; g_orderN = 0; g_throwCalls = 0;
        bool caught = false;
        try { FUN_140078470((int*)g_msg); } catch (bool) { caught = true; }
        assert(caught);
        assert(g_orderN == 2);
        assert(g_order[0] == 1 && g_order[1] == 2);    // the sink first, the throw last
        assert(g_logCalls == 1 && g_logSeverity == 3);
        assert(g_throwCalls == 1);
        FUN_140078440((long long)g_msg);
    }

    // 0x140078580 is the same sink with the finisher word ignored
    {
        std::memset(g_msg, 0, sizeof g_msg);
        FUN_1400783d0(g_msg, 2, kFile, 9);
        g_logCalls = 0; g_orderN = 0;
        long long aFinisher[1] = { 0 };
        FUN_140078580(aFinisher, (int*)g_msg);
        assert(g_logCalls == 1 && g_logLine == 9);
        FUN_140078440((long long)g_msg);
    }

    std::printf("NPCSERVER_D211_OK: log message helpers\n");
    return 0;
}
