// ============================================================================
// cqbase_d42 — the domain and facility accessors: every kind, every slot, the flag on each
//   call, the cleared record pointer and the reported source line
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synaccessor.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

// the record and its children
static int32_t g_nKind = -1;
static void* g_pChild = nullptr;
static uint64_t g_uSlot38Value = 0x38AA;
static uint64_t g_uSlot48Value = 0x48BB;
static uint64_t g_uSlot78Value = 0x78CC;
static uint64_t g_uSlot40ChildValue = 0x40DD;
static uint64_t g_uSlot40RecValue = 0xFF00FF00FF00FF41ull;   // low byte 0x41: must become 1
static int g_nSlot40Calls = 0;
static int g_nSlot40Flag = -1;
static int g_nSlot0Calls = 0;
static void* g_pSlot0Flag = nullptr;
static int g_nSetCalls = 0;
static void* g_pSetValue = nullptr;

static void* g_aRecVft[0x88 / 8];
static void* g_aChildVft[0x88 / 8];

static void* RecGetChild(void*, int32_t nKind) {
    g_nKind = nKind;
    return g_pChild;
}
static uint64_t Child38(void*) { return g_uSlot38Value; }
static uint64_t Child48(void*) { return g_uSlot48Value; }
static uint64_t Child78(void*) { return g_uSlot78Value; }
static uint64_t Child40(void*) { return g_uSlot40ChildValue; }
static uint64_t Rec40(void*, void* pFlag) {
    ++g_nSlot40Calls;
    g_nSlot40Flag = (int)(intptr_t)pFlag;
    return g_uSlot40RecValue;
}
static uint64_t Rec0(void*, void* pFlag) {
    ++g_nSlot0Calls;
    g_pSlot0Flag = pFlag;
    return 0x1122334455667788ull;
}
static void Child80(void*, void* pValue) {
    ++g_nSetCalls;
    g_pSetValue = pValue;
}

int main() {
    LogApi savedLog = g_LogApi;
    g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    void* aChild[1];
    void* aRecObj[1];
    aChild[0] = g_aChildVft;
    aRecObj[0] = g_aRecVft;
    void* aRec[1];
    aRec[0] = aRecObj;
    g_pChild = aChild;

    g_aRecVft[0x00 / 8] = (void*)&Rec0;
    g_aRecVft[0x10 / 8] = (void*)&RecGetChild;
    g_aRecVft[0x38 / 8] = (void*)&Child38;
    g_aRecVft[0x40 / 8] = (void*)&Rec40;
    g_aChildVft[0x38 / 8] = (void*)&Child38;
    g_aChildVft[0x40 / 8] = (void*)&Child40;
    g_aChildVft[0x48 / 8] = (void*)&Child48;
    g_aChildVft[0x78 / 8] = (void*)&Child78;
    g_aChildVft[0x80 / 8] = (void*)&Child80;

    // ---- the name: kind 1, slot 0x78, straight through
    {
        g_nKind = -1;
        CHECK(SynDomainName(aRec) == (void*)0x78CC);
        CHECK(g_nKind == 1);
    }

    // ---- the four child reads
    {
        uint32_t aTwo[2] = {0, 0};
        uint32_t uFive = 0, uSix = 0;
        g_uSlot38Value = 0x3333;
        g_uSlot48Value = 0x5555;
        g_nKind = -1;
        CHECK(SynDomainGetFour(aRec, aTwo, &uFive, &uSix) == true);
        CHECK(aTwo[0] == 0x3333);       // kind 3 through slot 0x38
        CHECK(aTwo[1] == 0x3333);       // kind 4 through slot 0x38
        CHECK(uFive == 0x5555);         // kind 5 through slot 0x48
        CHECK(uSix == 0x5555);          // kind 6 through slot 0x48
        CHECK(g_nKind == 6);            // the last kind asked for
    }

    // ---- close A: slot 0x40 with a zero flag, then slot 0 with flag one, pointer cleared twice
    {
        g_nSlot40Calls = g_nSlot0Calls = 0;
        g_nSlot40Flag = -1;
        g_pSlot0Flag = nullptr;
        uint64_t uAnswer = SynDomainCloseA(aRec);
        CHECK(g_nSlot40Calls == 1);
        CHECK(g_nSlot40Flag == 0);
        CHECK(g_nSlot0Calls == 1);
        CHECK(g_pSlot0Flag == (void*)1);
        CHECK((uAnswer & 0xff) == 1);                    // bit zero forced on
        CHECK((uAnswer & ~(uint64_t)0xff) == 0x1122334455667700ull);   // the rest from slot zero
        CHECK(aRec[0] == nullptr);                       // cleared
        // and a second call finds a null record: it reports and answers zero
        g_sLogs.clear();
        uint64_t uAgain = SynDomainCloseA(aRec);
        CHECK(g_nSlot40Calls == 1);                      // no further slot call
        CHECK(uAgain == 0);
        CHECK(g_sLogs.size() == 1);
        aRec[0] = aRecObj;
    }

    // ---- close B: one call through slot 0x38 with a zero flag
    {
        g_uSlot38Value = 0xABCDEF01;
        uint64_t uAnswer = SynDomainCloseB(aRec);
        CHECK((uAnswer & 0xff) == 1);
        CHECK((uAnswer & ~(uint64_t)0xff) == (0xABCDEF01ull & ~0xffull));
        CHECK(aRec[0] == aRecObj);                       // this close keeps the pointer
    }

    // ---- set field 1: kind 1, slot 0x80, then the record's own slot 0x38
    {
        g_nKind = -1;
        g_nSetCalls = 0;
        g_pSetValue = nullptr;
        g_uSlot38Value = 0x1000;
        uint64_t uAnswer = SynDomainSetField1(aRec, (void*)0xCAFE);
        CHECK(g_nKind == 1);
        CHECK(g_nSetCalls == 1);
        CHECK(g_pSetValue == (void*)0xCAFE);
        CHECK((uAnswer & 0xff) == 1);
        CHECK((uAnswer & ~(uint64_t)0xff) == 0x1000ull);
    }

    // ---- the facility twins answer the same way
    {
        g_nSlot40Calls = g_nSlot0Calls = 0;
        uint64_t uAnswer = SynFacilityCloseA(aRec);
        CHECK(g_nSlot40Calls == 1);
        CHECK(g_nSlot0Calls == 1);
        CHECK((uAnswer & 0xff) == 1);
        CHECK(aRec[0] == nullptr);
        aRec[0] = aRecObj;

        g_uSlot38Value = 0x2200;
        uint64_t uB = SynFacilityCloseB(aRec);
        CHECK((uB & 0xff) == 1);
        CHECK((uB & ~(uint64_t)0xff) == 0x2200ull);

        g_nKind = -1;
        CHECK(SynFacilityField2(aRec) == (void*)0x40DD);   // kind 2 through slot 0x40
        CHECK(g_nKind == 2);
    }

    // ---- the null paths: the report carries the macro, the expression and the line
    {
        struct Case {
            uint64_t (*pfn)(void*);
            int nLine;
            const char* pszFile;
        };
        void* aNull[1] = {nullptr};
        const Case aCases[] = {
            {&SynDomainCloseA, 126, "syndomain.cpp"},
            {&SynDomainCloseB, 137, "syndomain.cpp"},
            {&SynFacilityCloseA, 126, "synfacility.cpp"},
            {&SynFacilityCloseB, 167, "synfacility.cpp"},
        };
        for (const Case& c : aCases) {
            g_sLogs.clear();
            CHECK(c.pfn(aNull) == 0);
            CHECK(g_sLogs.size() == 1);
            CHECK(g_sLogs[0].find("CHECKF") != std::string::npos);
            CHECK(g_sLogs[0].find("m_pRec") != std::string::npos);
            CHECK(g_sLogs[0].find(c.pszFile) != std::string::npos);
            char szLine[8];
            std::snprintf(szLine, sizeof(szLine), "%d", c.nLine);
            CHECK(g_sLogs[0].find(szLine) != std::string::npos);
        }
        // the name answers the empty string, and it reports IF_OK at line 86
        g_sLogs.clear();
        void* pName = SynDomainName(aNull);
        CHECK(*(const char*)pName == '\0');
        CHECK(g_sLogs.size() == 1);
        CHECK(g_sLogs[0].find("IF_OK") != std::string::npos);
        CHECK(g_sLogs[0].find("86") != std::string::npos);
        // the field read answers null and reports at line 177
        g_sLogs.clear();
        CHECK(SynFacilityField2(aNull) == nullptr);
        CHECK(g_sLogs.size() == 1);
        CHECK(g_sLogs[0].find("177") != std::string::npos);
        // and the four-child read reports at 126 and answers false
        {
            uint32_t aTwo[2];
            uint32_t uFive, uSix;
            g_sLogs.clear();
            CHECK(SynDomainGetFour(aNull, aTwo, &uFive, &uSix) == false);
            CHECK(g_sLogs.size() == 1);
            CHECK(g_sLogs[0].find("126") != std::string::npos);
        }
    }

    g_LogApi = savedLog;
    std::printf("SYNDICATE_D42_OK: the domain and facility accessors, 8 units, %d checks\n",
                g_nChecks);
    return 0;
}
