// D213 — NpcServer.exe 0x140077fc0, 0x140077f50, 0x140078d20, 0x140078d60, 0x140078d80.
//
// The vtable the fatal exception carries was read out of the image: the constructor stores 0x1400cdd70 at +0, the
// file at +0x18, the line at +0x20 and the message copy at +0x28 (objdump of 0x140078d80).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <exception>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_initCalls = 0;
static void InitOnce(void) { ++g_initCalls; }

static int g_lockCalls = 0, g_unlockCalls = 0;
static void* g_lockedMutex = nullptr; static void* g_unlockedMutex = nullptr;
static void LockMutex(void* pMutex) { ++g_lockCalls; g_lockedMutex = pMutex; }
static void UnlockMutex(void* pMutex) { ++g_unlockCalls; g_unlockedMutex = pMutex; }

static int g_vt[4];

// the log layer's one-time initialiser is a real body now, so these suites have to answer for what it needs: the
// FunctionClosure0 vtable (slot 1 runs the stored function) and the body 0x140077f50 reaches.
static long long g_onceVt[3] = { 0, 0, 0 };
static void OnceRun(void* pThis) {
    void (*pfn)(void) = *(void (**)(void))((unsigned char*)pThis + 0x08);
    if (pfn != nullptr) pfn();
}
static void OnceVtable(void) {
    g_onceVt[1] = (long long)&OnceRun;
    g_pNpcVtblFunctionClosure0 = (const void*)g_onceVt;
}

int main() {
    OnceVtable();
    g_pfnNpc_140077f50 = &InitOnce;
    g_pfnNpc_1400787c0 = &LockMutex;
    g_pfnNpc_1400787f0 = &UnlockMutex;

    // the one-time initialisation is handed the image's own state word and the address of 0x140077f50
    {
        g_pNpcLogState_140104ce8 = 0;      // a fresh module: the state word has not been spent
        g_initCalls = 0;
        FUN_140077fc0();
        assert(g_initCalls == 1);                              // the initialisation ran exactly once
        assert(g_pNpcLogState_140104ce8 == 2);                 // and the image's own state word says so
        FUN_140077fc0();
        assert(g_initCalls == 1);                              // a second call is a no-op
    }

    // the mutex wrapper stores the mutex first and then takes it
    {
        void* aWrapper[1] = { nullptr };
        int aMutex[2] = { 0, 0 };
        g_lockCalls = 0; g_lockedMutex = nullptr;
        void* p = FUN_140078d20(aWrapper, aMutex);
        assert(p == (void*)aWrapper);
        assert(aWrapper[0] == (void*)aMutex);
        assert(g_lockCalls == 1 && g_lockedMutex == (void*)aMutex);
        g_unlockCalls = 0;
        FUN_140078d60(aWrapper);
        assert(g_unlockCalls == 1 && g_unlockedMutex == (void*)aMutex);
    }

    // the fatal exception: base, vtable, file, line, and a copy of the message
    {
        g_pNpcVtblFatalException = (const void*)g_vt;
        unsigned char aException[0x48];
        std::memset(aException, 0xCC, sizeof aException);
        std::string sMessage = "CHECK failed: something";
        void* p = FUN_140078d80(aException, "F:\\path\\file.cc", 0x2a, &sMessage);
        assert(p == (void*)aException);
        assert(*(const void**)aException == (const void*)g_vt);
        assert(*(const char**)(aException + 0x18) != nullptr);
        assert(std::strcmp(*(const char**)(aException + 0x18), "F:\\path\\file.cc") == 0);
        assert(*(const unsigned int*)(aException + 0x20) == 0x2a);
        assert(*(std::string*)(aException + 0x28) == "CHECK failed: something");

        // the message is copied: changing the source afterwards does not change the exception's text
        sMessage = "changed";
        assert(*(std::string*)(aException + 0x28) == "CHECK failed: something");

        // and it is a real exception object, since it is built on top of std::exception
        std::exception* pBase = (std::exception*)aException;
        assert(pBase != nullptr);   // the base sub-object occupies the first word
        ((std::string*)(aException + 0x28))->~basic_string();
    }

    std::printf("NPCSERVER_D213_OK: 0x140077fc0/f50, 0x140078d20/d60/d80\n");
    return 0;
}
