// D172 — NpcServer.exe 0x1400020d0 .. 0x140002630: the CKernelThread helpers (26 bodies).
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_logs = 0, g_msgs = 0, g_errno111 = 0, g_deletes = 0;
static const void* g_lastLog = nullptr;
static char g_msgUp[64] = {0}, g_msgDown[64] = {0};
static int g_dtors = 0, g_slot[11] = {0}, g_lastSlot = -1, g_lastSlotArg = -1;
static long long g_lastFd = 0, g_lastSlot3 = 0, g_lastSlot4 = 0;
static int g_sleepMs = 0, g_closed = 0; static void* g_closedHandle = nullptr;
static int g_loopExitRet = 0; static void* g_loopExitArg = nullptr;
static long long g_baseArg[4] = {0,0,0,0};
static int g_freeBases = 0, g_12190 = 0, g_enableRet = 0, g_enableEvents = 0, g_setFrom = 0;
static unsigned long g_timeNow = 0;

static void LogHook(const void* m, ...) { ++g_logs; g_lastLog = m; }
static void MsgHook(const char* s) {
    if (g_msgs == 0) std::snprintf(g_msgUp, sizeof g_msgUp, "%s", s);
    else std::snprintf(g_msgDown, sizeof g_msgDown, "%s", s);
    ++g_msgs;
}
static void Ord111Hook(void) { ++g_errno111; }
static void* DelHook(void* p) { ++g_deletes; return p; }
static void DtorHook(void* p) { (void)p; ++g_dtors; }
static void SlotN(void) { ++g_slot[g_setFrom]; g_lastSlot = g_setFrom; }
static int g_slotA = 0, g_slotB = 0;
static void SlotA(void* p) { (void)p; ++g_slotA; }
static void SlotB(void* p) { (void)p; ++g_slotB; }

int main() {
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcLogMessage = &MsgHook;
    g_pfnNpcOrdinal111 = &Ord111Hook;
    g_pfnNpcOperatorDelete = &DelHook;
    g_pfnNpcThreadBaseDtor = &DtorHook;
    g_pfnNpcSleep = [](unsigned int ms) { g_sleepMs = (int)ms; };
    g_pfnNpcCloseHandle = [](void* h) { g_closed = 1; g_closedHandle = h; return 1; };
    g_pfnNpcEventBaseLoopExit_140016280 = [](void* b, void* a) { (void)b; g_loopExitArg = a; return g_loopExitRet; };
    g_pfnNpcEventBase_140016270 = [](void* b, long long a2, long long a3, long long a4) {
        (void)b; g_baseArg[0] = a2; g_baseArg[1] = a3; g_baseArg[2] = a4; g_baseArg[3] = 1; };
    g_pfnNpcEventBaseFree_140014eb0 = [](void* b, void* a2, long long a3, long long a4) {
        (void)b; (void)a2; (void)a3; (void)a4; ++g_freeBases; };
    g_pfnNpc_140012190 = [] { ++g_12190; };
    g_pfnNpcBevGetFd_140006200 = [](void* p) { (void)p; return g_lastFd; };
    g_pfnNpcBevEnable_1400071b0 = [](void* p, int ev) { (void)p; g_enableEvents = ev; return g_enableRet; };
    g_pfnNpcTimeGet = [](unsigned long long p) { (void)p; return g_timeNow; };

    // the five silent stubs and the two logging ones
    {
        g_logs = 0;
        FUN_1400020d0(); FUN_140002270();
        assert(g_logs == 0);
        FUN_1400020f0(); FUN_140002130(); FUN_140002170(); FUN_1400021b0();
        assert(g_logs == 4 && g_lastLog == (const void*)&g_symNpcStr_1400be0b0);
        g_logs = 0;
        FUN_1400025b0(); FUN_1400025f0();
        assert(g_logs == 2);
    }

    // 0x1400021f0 — both table stores then the base destructor
    {
        unsigned char obj[0x80] = {0};
        g_dtors = 0;
        FUN_1400021f0((long long)obj);
        assert(*(void**)(obj + 0x00) == (void*)&g_symNpcVftbl_1400be730);
        assert(*(void**)(obj + 0x40) == (void*)&g_symNpcVftbl_1400be6f8);
        assert(g_dtors == 1);
    }

    // 0x140002230 .. 0x140002260 — slots 0..3 of the table at *(this+8)
    {
        unsigned char obj[16] = {0};
        // the machine loads the object at +8, its first word (the table), then the slot
        void* table[4] = { (void*)&SlotN, (void*)&SlotN, (void*)&SlotN, (void*)&SlotN };
        void* inner[1] = { (void*)table };
        *(void**)(obj + 8) = inner;
        for (int i = 0; i < 4; ++i) {
            g_setFrom = i; g_lastSlot = -1;
            if (i == 0) FUN_140002230((long long)obj);
            if (i == 1) FUN_140002240((long long)obj);
            if (i == 2) FUN_140002250((long long)obj);
            if (i == 3) FUN_140002260((long long)obj);
            assert(g_lastSlot == i);
        }
    }

    // 0x1400022a0 / 0x1400022c0 / 0x1400022e0
    {
        unsigned char obj[0x80] = {0};
        g_baseArg[3] = 0;
        FUN_1400022a0((long long)obj, 1, 2, 3);
        assert(g_baseArg[3] == 0);                         // no base yet, nothing forwarded
        *(void**)(obj + 0x58) = (void*)0xB1;
        *(void**)(obj + 0x68) = (void*)0xB2;
        FUN_1400022a0((long long)obj, 7, 8, 9);
        assert(g_baseArg[0] == 7 && g_baseArg[1] == 8 && g_baseArg[2] == 9);
        assert(FUN_1400022c0((long long)obj) == (void*)0xB1);
        assert(FUN_1400022e0((long long)obj) == (void*)0xB2);
    }

    // 0x1400022f0 — a missing fd logs; a live one dispatches with 0x1fbd1 and length 8
    {
        unsigned char socket[0x60] = {0};
        void* table[11]; for (int i = 0; i < 11; ++i) table[i] = (void*)&SlotN;
        void* target[1] = { (void*)table };
        *(void**)(socket + 0x50) = target;
        g_logs = 0; g_lastFd = -1;
        FUN_1400022f0(0x5000, (long long)socket);
        assert(g_logs == 1 && g_lastLog == (const void*)&g_symNpcStr_1400be0b0);
        g_logs = 0; g_lastFd = 42; g_setFrom = 10; g_slot[10] = 0;
        FUN_1400022f0(0x5000, (long long)socket);
        assert(g_slot[10] == 1 && g_logs == 0);
    }

    // 0x140002380 — the three branches of BufferEventCb
    {
        unsigned char socket[0x60] = {0};
        void* table[11]; for (int i = 0; i < 11; ++i) table[i] = (void*)&SlotN;
        void* target[1] = { (void*)table };
        *(void**)(socket + 0x50) = target;
        // events bit 7: enable, success returns quietly
        g_logs = 0; g_lastFd = 5; g_enableRet = 0; g_enableEvents = 0;
        FUN_140002380((long long*)0x5000, 0x80, (long long)socket);
        assert(g_enableEvents == 6 && g_logs == 0);
        // events bit 7 with a failing enable: errno plus the message
        g_logs = 0; g_errno111 = 0; g_enableRet = -1;
        FUN_140002380((long long*)0x5000, 0x80, (long long)socket);
        assert(g_errno111 == 1);
        assert(std::strcmp((const char*)g_lastLog,
               "CKernelThread::BufferEventCb, bufferevent_enable error[%d].") == 0);
        // 0x30 present: dispatch with 0x1fbd2
        g_logs = 0; g_setFrom = 10; g_slot[10] = 0;
        FUN_140002380((long long*)0x5000, 0x10, (long long)socket);
        assert(g_slot[10] == 1 && g_logs == 0);
        // neither: the events message
        g_logs = 0;
        FUN_140002380((long long*)0x5000, 0x08, (long long)socket);
        assert(g_logs == 1);
        assert(std::strcmp((const char*)g_lastLog,
               "CKernelThread::BufferEventCb, events[%0x] error.") == 0);
        // no fd at all: silence
        g_logs = 0; g_lastFd = -1;
        FUN_140002380((long long*)0x5000, 0x08, (long long)socket);
        assert(g_logs == 0);
    }

    // 0x140002450 / 0x140002480 — the time helpers
    {
        unsigned char obj[8] = {0};
        g_timeNow = 5000;
        FUN_140002450((long long)obj);
        assert(*(unsigned int*)(obj + 4) == 5);            // 5000 / 1000
        int pair[2] = { 3, 4 };
        g_timeNow = 7000;
        assert(FUN_140002480(pair) == 1);                   // 7 <= 7
        g_timeNow = 6999;
        assert(FUN_140002480(pair) == 0);
    }

    // 0x1400024c0 — release and clear
    {
        void* slot = nullptr;
        g_deletes = 0;
        FUN_1400024c0(&slot);
        assert(g_deletes == 0 && slot == nullptr);
        unsigned char* obj = (unsigned char*)std::calloc(1, 0x840);
        slot = obj;
        FUN_1400024c0(&slot);
        assert(slot == nullptr);
        std::free(obj);
    }

    // 0x1400024f0 — the two messages around the forward
    {
        unsigned char obj[0x80] = {0};
        *(void**)(obj + 0x58) = (void*)0xB3;
        g_msgs = 0; g_baseArg[3] = 0;
        assert(FUN_1400024f0((long long)obj, 1, 2, 3) == 0);
        assert(std::strcmp(g_msgUp, "EvnetRoutine worker thread is up and running") == 0);
        assert(std::strcmp(g_msgDown, "EvnetRoutine worker thread exited") == 0);
        assert(g_baseArg[3] == 1);
    }

    // 0x140002540 — stores, destructor, then delete on the low bit
    {
        unsigned char obj[0x80] = {0};
        g_dtors = 0; g_deletes = 0;
        assert(FUN_140002540((long long)obj, 0) == (void*)obj);
        assert(g_dtors == 1 && g_deletes == 0);
        assert(*(void**)(obj + 0x40) == (void*)&g_symNpcVftbl_1400be6f8);
        assert(FUN_140002540((long long)obj, 1) == (void*)obj);
        assert(g_deletes == 1);
    }

    // 0x140002630 — OnDestroy walks +0x68, +0x60, the loop exit, the sleep, the handle
    {
        unsigned char obj[0x80] = {0};
        void* t68[11]; for (int i = 0; i < 11; ++i) t68[i] = (void*)&SlotN;
        void* t50[11]; for (int i = 0; i < 11; ++i) t50[i] = (void*)&SlotN;
        t68[2] = (void*)&SlotA;                    // the +0x68 object's slot at +0x10
        t50[6] = (void*)&SlotB;                    // the +0x50 object's slot at +0x30
        void* o68[1] = { (void*)t68 };
        void* o50[1] = { (void*)t50 };
        *(void**)(obj + 0x68) = o68;
        *(void**)(obj + 0x50) = o50;
        *(void**)(obj + 0x70) = (void*)0xC0FFEE;
        unsigned char* sock = (unsigned char*)std::calloc(1, 0x840);
        *(void**)(obj + 0x60) = sock;
        *(void**)(obj + 0x58) = (void*)0xB4;
        g_slotA = g_slotB = 0;
        g_sleepMs = 0; g_closed = 0; g_freeBases = 0; g_12190 = 0; g_loopExitRet = -1; g_logs = 0;
        FUN_140002630((long long)obj, 1, 2, 3);
        assert(*(void**)(obj + 0x68) == nullptr);           // slot 2 ran and the word was cleared
        assert(*(void**)(obj + 0x60) == nullptr);           // the socket was released
        assert(g_loopExitArg != nullptr);
        assert(g_sleepMs == 0x9c4);
        assert(g_closed == 1 && g_closedHandle == (void*)0xC0FFEE);
        assert(g_freeBases == 1 && *(void**)(obj + 0x58) == nullptr);
        assert(g_12190 == 1);
        assert(g_slotA == 1 && g_slotB == 1);               // both slots, one each
        assert(g_logs == 1);                                // the loop-exit failure message
        assert(std::strcmp((const char*)g_lastLog,
               "CKernelThread::OnDestroy, event_base_loopexit error.") == 0);
        std::free(sock);
    }

    std::printf("NPCSERVER_D172_OK: 0x1400020d0..0x140002630, 26 bodies\n");
    return 0;
}
