// D200 — NpcServer.exe 0x140076190 (required-fields text), 0x140076320/350/380 (argument-swapping thunks).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static long long g_msgVt[6];
static const char* g_typeName = "Foo.Bar";
static const char* g_missing = "a, b";
static int g_nameCalls = 0, g_listCalls = 0;
static const std::string* NameSlot(void* pSelf, std::string* pOut) {
    (void)pSelf; ++g_nameCalls;
    new (pOut) std::string(g_typeName);
    return pOut;
}
static const std::string* ListSlot(void* pSelf, std::string* pOut) {
    (void)pSelf; ++g_listCalls;
    new (pOut) std::string(g_missing);
    return pOut;
}
static long long* g_targetThis = nullptr; static void* g_targetArg = nullptr; static int g_calls = 0;
// the thunks are real now, so the pair only reaches a seam at the last hop: 0x140077370, which is still unported
static unsigned char T370(void* a2, long long* pThis) { g_targetArg = a2; g_targetThis = pThis; ++g_calls; return 1; }
// the object is closed through its own slot 3 before that, and answered through slot 7 on the other path
static int g_closed = 0, g_slot7 = 0;
static void Closer(long long* p) { (void)p; ++g_closed; }
static unsigned char Slot7(long long* p, void* a) { (void)p; (void)a; ++g_slot7; return 1; }

int main() {
    g_msgVt[0] = 0;
    g_msgVt[1] = (long long)&NameSlot;                 // vtable +0x08
    g_msgVt[2] = 0; g_msgVt[3] = 0; g_msgVt[4] = 0;
    g_msgVt[5] = (long long)&ListSlot;                 // vtable +0x28
    long long aMessage[1] = { (long long)g_msgVt };

    // the sentence, with the type name and the missing list taken from the message's own vtable
    {
        unsigned char storage[sizeof(std::string)];
        g_nameCalls = 0; g_listCalls = 0;
        std::string* p = FUN_140076190((std::string*)storage, "parse", aMessage);
        assert(p == (std::string*)storage);
        assert(g_nameCalls == 1 && g_listCalls == 1);
        assert(*p == "Can't parse message of type \"Foo.Bar\" because it is missing required fields: a, b");
        p->~basic_string();
        // the action word is whatever the caller passes
        g_typeName = "T"; g_missing = "";
        p = FUN_140076190((std::string*)storage, "serialize", aMessage);
        assert(*p == "Can't serialize message of type \"T\" because it is missing required fields: ");
        p->~basic_string();
        g_typeName = "Foo.Bar"; g_missing = "a, b";
    }

    // the three thunks hand the pair on with the two the other way round
    {
        g_pfnNpc_140077370 = &T370;
        long long aThisVt[8];
        std::memset(aThisVt, 0, sizeof aThisVt);
        aThisVt[3] = (long long)&Closer;            // +0x18, closed before the work
        aThisVt[7] = (long long)&Slot7;             // +0x38, the second path's own answer
        long long aThis[2] = { (long long)aThisVt, 0x2222 };
        void* pArg = (void*)0x9999;
        g_calls = 0; g_targetThis = nullptr; g_targetArg = nullptr; g_closed = 0; g_slot7 = 0;
        FUN_140076320(aThis, pArg);
        assert(g_calls == 1 && g_targetArg == pArg && g_targetThis == aThis);
        g_calls = 0;
        unsigned char b = FUN_140076350(aThis, pArg);
        assert(b == 1 && g_calls == 1 && g_targetArg == pArg && g_targetThis == aThis);
        assert(g_closed == 1);                      // closed first, then worked on
        g_calls = 0;
        b = FUN_140076380(aThis, pArg);
        assert(b == 1 && g_closed == 2 && g_slot7 == 1);
        assert(g_calls == 0);                       // the second path never reaches the seam
    }

    std::printf("NPCSERVER_D200_OK: 0x140076190/320/350/380\n");
    return 0;
}
