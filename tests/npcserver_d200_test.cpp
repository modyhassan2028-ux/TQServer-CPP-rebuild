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
static unsigned char T370(void* a2, long long* pThis) { g_targetArg = a2; g_targetThis = pThis; ++g_calls; return 1; }
static unsigned char T4a0(void* a2, long long* pThis) { g_targetArg = a2; g_targetThis = pThis; ++g_calls; return 1; }
static unsigned char T4e0(void* a2, long long* pThis) { g_targetArg = a2; g_targetThis = pThis; ++g_calls; return 1; }

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
        g_pfnNpc_1400774a0 = &T4a0;
        g_pfnNpc_1400774e0 = &T4e0;
        long long aThis[2] = { 0x1111, 0x2222 };
        void* pArg = (void*)0x9999;
        g_calls = 0; g_targetThis = nullptr; g_targetArg = nullptr;
        FUN_140076320(aThis, pArg);
        assert(g_calls == 1 && g_targetArg == pArg && g_targetThis == aThis);
        g_calls = 0;
        FUN_140076350(aThis, pArg);
        assert(g_calls == 1 && g_targetArg == pArg && g_targetThis == aThis);
        g_calls = 0;
        FUN_140076380(aThis, pArg);
        assert(g_calls == 1 && g_targetArg == pArg && g_targetThis == aThis);
    }

    std::printf("NPCSERVER_D200_OK: 0x140076190/320/350/380\n");
    return 0;
}
