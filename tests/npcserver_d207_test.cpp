// D207 — NpcServer.exe 0x140077370 (accept), 0x140077530 (wrapper build), 0x140077620 (parse bytes).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_seqN = 0, g_seq[20];
static void Note(int c) { if (g_seqN < 20) g_seq[g_seqN] = c; ++g_seqN; }
static int g_parsed = 1, g_initialised = 1;
static unsigned char ParseSlot(long long* p, void* a) { (void)p; (void)a; Note(1); return (unsigned char)g_parsed; }
static unsigned char InitSlot(long long* p) { (void)p; Note(2); return (unsigned char)g_initialised; }
static const std::string* NameSlot(void* p, std::string* o) { (void)p; Note(3); new (o) std::string("Npc.Msg"); return o; }
static const std::string* ListSlot(void* p, std::string* o) { (void)p; Note(4); new (o) std::string("field_x"); return o; }
static int g_logSev = -1, g_logLine = 0; static const char* g_logFile = nullptr;
static void* Sink(void* pOut, int sev, const char* f, int line) {
    (void)pOut; g_logSev = sev; g_logFile = f; g_logLine = line; Note(5); return pOut;
}
static std::string g_appendedText; static int g_appendCalls = 0;
static long long AppendText(long long m, std::string* t) {
    (void)m; g_appendedText = *t; ++g_appendCalls; Note(6); return m;   // copied: the caller frees it
}
static int g_fail = 0;
static void Fail(void* f, int* t) { (void)f; (void)t; ++g_fail; Note(7); }
static int g_release = 0;
static void Release(long long p) { (void)p; ++g_release; Note(8); }
static int g_b7e0 = 0;
static void B7e0(void* p) { (void)p; ++g_b7e0; Note(9); }
static const char* g_bytes = nullptr; static int g_bytesLen = -1;
static int g_wrap24 = 1;
static void BuildWrap(void* w, const char* d, int n) {
    (void)w; g_bytes = d; g_bytesLen = n;
    *(unsigned char*)((unsigned char*)w + 0x24) = (unsigned char)g_wrap24;
    Note(10);
}
static int g_slot18 = 0;
static void Slot18(long long* p) { (void)p; ++g_slot18; Note(11); }
static int g_t370 = 0, g_t370Ret = 1;
static unsigned char T370(void* a1, long long* p) { (void)a1; (void)p; ++g_t370; Note(12); return (unsigned char)g_t370Ret; }
static int g_destroy = 0;
static void Destroy(void* p) { (void)p; ++g_destroy; Note(13); }

static void LogSink(int nSeverity, const char* pszFile, int nLine, std::string* pText) {
    g_logSev = nSeverity; g_logFile = pszFile; g_logLine = nLine;
    g_appendedText = pText != nullptr ? *pText : std::string();
    ++g_fail;
    Note(5);
}

int main() {
    long long vt[12];
    std::memset(vt, 0, sizeof vt);
    vt[1] = (long long)&NameSlot;      // +0x08
    vt[4] = (long long)&InitSlot;      // +0x20
    vt[5] = (long long)&ListSlot;      // +0x28
    vt[7] = (long long)&ParseSlot;     // +0x38
    long long aMsg[1] = { (long long)vt };
    g_pfnNpcLogSink_1401035c8 = &LogSink;   // the real log bodies now reach this seam
    g_pfnNpc_14007b7e0 = &B7e0;
    g_pfnNpc_1400776c0 = &BuildWrap;
    g_pfnNpc_140077370 = &T370;
    g_pfnNpc_14007a700 = &Destroy;

    // accepting a message: a failed parse refuses straight away
    {
        g_seqN = 0; g_parsed = 0;
        assert(FUN_140077370((void*)0x1234, aMsg) == 0);
        assert(g_seqN == 1);                            // only the parse slot ran
        // parsed but not initialised: the warning at line 0x7b, severity 2, with the required-fields text
        g_seqN = 0; g_parsed = 1; g_initialised = 0; g_fail = 0; g_release = 0; g_appendCalls = 0;
        unsigned long long u = FUN_140077370((void*)0x1234, aMsg);
        assert(u == 0);
        assert(g_logSev == 2 && g_logLine == 0x7b);
        assert(std::strcmp(g_logFile,
               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc") == 0);
        assert(g_seq[0] == 1 && g_seq[1] == 2);
        assert(g_seq[2] == 3 && g_seq[3] == 4);         // the text was built from the message's own slots
        assert(g_seqN == 5);
        assert(g_seq[4] == 5);                          // the finished message reaches the log sink
        // the text appended is exactly the sentence
        assert(g_appendedText == "Can't parse message of type \"Npc.Msg\" because it is missing required fields: field_x");
        // parsed and initialised: accepted
        g_seqN = 0; g_initialised = 1;
        assert(FUN_140077370((void*)0x1234, aMsg) == 1);
        assert(g_seqN == 2);
        g_initialised = 1;
    }

    // the wrapper build
    {
        unsigned char aWrap[0x50];
        std::memset(aWrap, 0xAA, sizeof aWrap);
        g_uNpcConst_1401036a0 = 0xDEAD;
        g_b7e0 = 0;
        void** p = FUN_140077530((void**)aWrap, (void*)0x5150);
        assert(p == (void**)aWrap);
        assert(*(void**)(aWrap + 0x00) == (void*)0x5150);
        assert(*(void**)(aWrap + 0x08) == nullptr && *(void**)(aWrap + 0x10) == nullptr);
        assert(*(unsigned int*)(aWrap + 0x18) == 0 && *(unsigned int*)(aWrap + 0x1c) == 0);
        assert(*(unsigned int*)(aWrap + 0x20) == 0);
        assert(*(unsigned char*)(aWrap + 0x24) == 0 && *(unsigned char*)(aWrap + 0x25) == 0);
        assert(*(unsigned int*)(aWrap + 0x28) == 0x7fffffff);
        assert(*(unsigned int*)(aWrap + 0x2c) == 0);
        assert(*(unsigned int*)(aWrap + 0x30) == 0x4000000);
        assert(*(unsigned int*)(aWrap + 0x34) == 0x2000000);
        assert(*(unsigned int*)(aWrap + 0x38) == 0);
        assert(*(unsigned int*)(aWrap + 0x3c) == 0xDEAD);
        assert(*(void**)(aWrap + 0x40) == nullptr && *(void**)(aWrap + 0x48) == nullptr);
        assert(g_b7e0 == 1);
    }

    // parsing bytes: the wrapper is offered, its validity decides, and it is always destroyed
    {
        long long aThisVt[8];
        std::memset(aThisVt, 0, sizeof aThisVt);
        aThisVt[3] = (long long)&Slot18;                // +0x18, opened by 0x1400774a0
        long long aThis[1] = { (long long)aThisVt };
        static const char sz[] = "{\"x\":1}";
        g_seqN = 0; g_bytes = nullptr; g_bytesLen = -1; g_wrap24 = 1; g_t370Ret = 1;
        g_destroy = 0;
        unsigned char b = FUN_140077620(sz, 7, aThis);
        assert(b == 1);
        assert(g_bytes == sz && g_bytesLen == 7);
        assert(g_seq[0] == 10 && g_seq[1] == 11 && g_seq[2] == 12);
        assert(g_destroy == 1 && g_seq[g_seqN - 1] == 13);
        // the offer refused: zero, and the wrapper still comes down
        g_seqN = 0; g_destroy = 0; g_t370Ret = 0;
        b = FUN_140077620(sz, 7, aThis);
        assert(b == 0 && g_destroy == 1);
        // accepted but the wrapper reports itself invalid: zero
        g_seqN = 0; g_destroy = 0; g_t370Ret = 1; g_wrap24 = 0;
        b = FUN_140077620(sz, 7, aThis);
        assert(b == 0 && g_destroy == 1);
    }

    std::printf("NPCSERVER_D207_OK: 0x140077370/530/620\n");
    return 0;
}
