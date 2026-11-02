// ============================================================================
// cqbase_d21 — CMyMultiEvent's constructor, CAutoPop's destructor and its reporter
// ============================================================================
#include "modules/cqbase/src/autopop.h"
#include "modules/cqbase/src/csync.h"
#include "modules/cqbase/src/logkernel.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static int g_nEvents = 0;
static std::vector<int> g_vManual;
static int g_nNames = 0;

static bool HookRunning() { return false; }
static void HookWrite(const char* pszFile, const char* pszText, int) {
    g_sLogs.push_back(std::string(pszFile != nullptr ? pszFile : "(no file)") + " | " +
                      (pszText != nullptr ? pszText : ""));
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

static std::vector<int> g_vManualFlags;
static void* HookCreateEventA(void* pAttr, int bManualReset, int bInitialState, const char*) {
    ++g_nEvents;
    assert(pAttr == nullptr);
    assert(bManualReset == 0);       // the raw always asks for an auto reset event
    g_vManual.push_back(bInitialState);   // the caller's bool lands in the initial state
    return (void*)(uintptr_t)(0xE000 + g_nEvents);
}
static const char* HookAutoPopName(void*) {
    ++g_nNames;
    return "someguard";
}

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};
    g_pfnCreateEventA = &HookCreateEventA;
    g_pfnAutoPopName = &HookAutoPopName;

    // ---- one event per slot, and the manual reset flag is passed through untouched
    {
        CMyMultiEvent multi(3, true);
        assert(multi.nCount == 3);
        assert(multi.phEvents != nullptr);
        assert(g_nEvents == 3);
        assert((int)g_vManual.size() == 3);
        for (int flag : g_vManual) assert(flag == 1);   // created already signalled
        assert(multi.phEvents[0] == (void*)0xE001);
        assert(multi.phEvents[1] == (void*)0xE002);
        assert(multi.phEvents[2] == (void*)0xE003);

        g_nEvents = 0;
        CMyMultiEvent autoReset(2, false);
        assert(autoReset.nCount == 2);
        assert(g_nEvents == 2);
        assert(g_vManual[g_vManual.size() - 1] == 0);   // created unsignalled
        ::operator delete[](autoReset.phEvents);
        ::operator delete[](multi.phEvents);
    }
    // a count that is not positive builds no array and asks for no event
    {
        g_nEvents = 0;
        CMyMultiEvent none(0, true);
        assert(none.nCount == 0 && none.phEvents == nullptr && g_nEvents == 0);
        CMyMultiEvent negative(-2, true);
        assert(negative.phEvents == nullptr && g_nEvents == 0);
    }

    // ---- the reporter: the trip is counted, and the report depends on the counter
    {
        const int64_t tNow = g_pfnTime64();
        g_sLogs.clear();
        g_nAutoPopAllCount = 0;
        g_nAutoPopDecCount = 0;
        g_AutoPopDelay.llUpdate = tNow;              // the sixty milliseconds have not passed
        CAutoPop::DeadLoopDump("first", 12);
        // the counter stood at zero, so nothing was written, and it came down to minus one
        assert(g_sLogs.empty());
        assert(g_nAutoPopAllCount == 1);
        assert(g_nAutoPopDecCount == -1);

        CAutoPop::DeadLoopDump("second", 34);        // minus one is not zero: it reports
        assert(g_sLogs.size() == 1);
        assert(g_sLogs[0].find("DeadLoopDump[second], ms[34], count[2]") != std::string::npos);
        assert(g_nAutoPopDecCount == -2);

        // when its own timer has passed, the counter is put back to ten and reports
        g_nAutoPopDecCount = 0;
        g_sLogs.clear();
        g_AutoPopDelay.llUpdate = tNow - 100000;
        CAutoPop::DeadLoopDump("timer", 56);
        assert(g_sLogs.size() == 1);
        assert(g_sLogs[0].find("DeadLoopDump[timer], ms[56], count[3]") != std::string::npos);
        assert(g_nAutoPopDecCount == 9);
    }

    // ---- the destructor: an empty list says nothing, a busy one is named and reported
    {
        int64_t abList[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        void* pGuard = nullptr;
        // the guard holds a pointer, and the list's two pointers at +0x18 and +0x20 are the
        // same, which is what the raw calls empty
        pGuard = &abList[0];
        abList[3] = 0;
        abList[4] = 0;
        g_nNames = 0;
        g_sLogs.clear();
        {
            CAutoPop pop;
            pop.m_pGuard = (void*)&pGuard;
            pop.m_nLastMs = (int32_t)(TimeGet(0) - 5000);
        }
        assert(g_nNames == 0);                       // never even named
        assert(g_sLogs.empty());

        // now the list holds one entry, so it is named, and five seconds have gone by
        abList[3] = 0;
        abList[4] = 8;
        g_nNames = 0;
        g_sLogs.clear();
        g_nAutoPopDecCount = 5;
        {
            CAutoPop pop;
            pop.m_pGuard = (void*)&pGuard;
            pop.m_nLastMs = (int32_t)(TimeGet(0) - 5000);
        }
        assert(g_nNames == 1);
        assert(g_sLogs.size() == 1);
        assert(g_sLogs[0].find("DeadLoopDump[someguard]") != std::string::npos);

        // the same busy list, but only a little time has gone by: it is named, no report
        g_nNames = 0;
        g_sLogs.clear();
        {
            CAutoPop pop;
            pop.m_pGuard = (void*)&pGuard;
            pop.m_nLastMs = (int32_t)TimeGet(0);
        }
        assert(g_nNames == 1);
        assert(g_sLogs.empty());
    }

    tq::g_LogApi = savedLog;
    std::printf("CQBASE_D21_OK: the multi event, the auto pop guard, its reporter, 3 units, %d checks\n", 31);
    return 0;
}
