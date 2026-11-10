// D225 — NpcServer.exe once-init cluster: 0x140078bf0, 0x1400786c0, 0x140078d00, 0x140078b90, 0x1400786e0,
// 0x14007f340, 0x14007f3f0, 0x14007f5b0, 0x14007f410, 0x14007f360, 0x140078b30.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_runs = 0, g_yields = 0, g_closureCalls = 0;
static long long g_closureArg = 0;
static void* g_closureThis = nullptr;
static long long* g_flipState = nullptr;      // what the yield does to the state word, if anything
static long long g_flipTo = 0;

static void Body(void) { ++g_runs; }

// FunctionClosure0::Run, which the image reaches through slot 1: it calls the function at +0x08 and hands itself on.
static void Run(void* pThis) {
    ++g_closureCalls;
    g_closureThis = pThis;
    g_closureArg = *(long long*)((unsigned char*)pThis + 0x08);
    void (*pfn)(void) = *(void (**)(void))((unsigned char*)pThis + 0x08);
    if (pfn != nullptr) pfn();
}
static void Yield(unsigned int nMs) {
    (void)nMs; ++g_yields;
    if (g_flipState != nullptr) *g_flipState = g_flipTo;
}

static long long g_baseVt[2] = { 0, 0 };
static long long g_funcVt[3] = { 0, 0, 0 };
static long long g_object[4];

int main() {
    g_pfnNpcSleep = &Yield;
    g_pNpcVtblClosure = (const void*)g_baseVt;
    g_funcVt[1] = (long long)&Run;
    g_pNpcVtblFunctionClosure0 = (const void*)g_funcVt;

    // the two constructors and the two destructors only move the vtable word, and the base is written first and
    // restored last
    {
        std::memset(g_object, 0, sizeof g_object);
        assert(FUN_140078bf0(g_object) == g_object);
        assert(g_object[0] == (long long)g_baseVt);

        assert(FUN_140078b90(g_object, &Body, 0) == g_object);
        assert(g_object[0] == (long long)g_funcVt);                 // the derived vtable replaced the base
        assert(*(void (**)(void))((unsigned char*)g_object + 0x08) == &Body);
        assert(*(unsigned char*)((unsigned char*)g_object + 0x10) == 0);

        assert(FUN_140078b90(g_object, &Body, 1) == g_object);
        assert(*(unsigned char*)((unsigned char*)g_object + 0x10) == 1);   // the self-delete byte is kept as given

        FUN_1400786e0(g_object);
        assert(g_object[0] == (long long)g_baseVt);                 // the base wins last
    }

    // the state word is read and written plainly
    {
        long long nOnce = 7;
        assert(FUN_140078d00(&nOnce) == 7);
        FUN_14007f3f0(&nOnce, 2);
        assert(nOnce == 2);
    }

    // the exchange answers what the word held, and only replaces a matching word
    {
        long long nOnce = 0;
        assert(FUN_14007f5b0(&nOnce, 0, 1) == 0);
        assert(nOnce == 1);
        assert(FUN_14007f5b0(&nOnce, 0, 1) == 1);                   // it does not match, so nothing moves
        assert(nOnce == 1);
        assert(FUN_14007f5b0(&nOnce, 1, 2) == 1);
        assert(nOnce == 2);
    }

    // the once run: the winner runs the closure's slot 1 and stores 2, and a second visit is a no-op
    {
        long long nOnce = 0;
        g_runs = 0; g_closureCalls = 0; g_closureThis = nullptr; g_closureArg = 0;
        std::memset(g_object, 0, sizeof g_object);
        FUN_140078b90(g_object, &Body, 0);
        FUN_14007f360(&nOnce, g_object);
        assert(g_closureCalls == 1 && g_runs == 1);
        assert(g_closureThis == (void*)g_object);
        assert(g_closureArg == (long long)&Body);
        assert(nOnce == 2);
        FUN_14007f360(&nOnce, g_object);
        assert(g_closureCalls == 1 && g_runs == 1);                 // done means done
    }

    // the once with a function: one run, then the state word says so
    {
        long long nOnce = 0;
        g_runs = 0; g_closureCalls = 0;
        FUN_140078b30(&nOnce, &Body);
        assert(g_runs == 1 && nOnce == 2);
        FUN_140078b30(&nOnce, &Body);
        assert(g_runs == 1 && nOnce == 2);
    }

    // losing the race: the word is already 1, so this caller only spins, yields, and leaves the work to the winner
    {
        long long nOnce = 1;
        g_closureCalls = 0; g_yields = 0;
        g_flipState = &nOnce; g_flipTo = 2;                          // the winner finishes during the yield
        FUN_14007f360(&nOnce, g_object);
        assert(g_closureCalls == 0);                                 // the loser never runs the closure
        assert(g_yields == 1);
        assert(nOnce == 2);
        g_flipState = nullptr;
    }

    std::printf("NPCSERVER_D225_OK: once-init cluster\n");
    return 0;
}
