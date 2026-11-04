// ============================================================================
// cqbase_d34e — the nine CSynAttr field readers: the kind each one asks for, the value it
//   answers, and the IF_OK(m_pRec) report the null record produces
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synattrget.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static int32_t g_nKindAsked = -1;
static void* g_pChild = nullptr;
static void* g_pValue = (void*)0x5150;

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

// the record: slot 0x10 hands back the child and remembers which kind was asked for
static void* g_aRecVft[0x18 / 8];
static void* g_aChildVft[0x50 / 8];

static void* RecGetChild(void* pSelf, int32_t nKind) {
    g_nKindAsked = nKind;
    return g_pChild;
}
static void* ChildValue(void* /*pSelf*/) { return g_pValue; }

int main() {
    LogApi savedLog = g_LogApi;
    g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    void* aRecObj[1];
    void* aChild[1];
    aRecObj[0] = g_aRecVft;      // the record object: its first word is its vtable
    aChild[0] = g_aChildVft;
    void* aRec[1];
    aRec[0] = aRecObj;           // the member the readers take the address of
    g_aRecVft[0x10 / 8] = (void*)&RecGetChild;
    g_aChildVft[0x48 / 8] = (void*)&ChildValue;
    g_pChild = aChild;

    // ---- every reader asks for its own kind and answers what the child's slot returns
    {
        struct Case {
            void* (*pfn)(void*);
            int32_t nKind;
            uint32_t uLine;
            const char* pszName;
        };
        const Case aCases[] = {
            {&SynAttrValueKind3, 3, 0x31c, "Kind3"},   {&SynAttrValueKind4, 4, 0x329, "Kind4"},
            {&SynAttrValueKind5, 5, 0x336, "Kind5"},   {&SynAttrValueKind6, 6, 0x343, "Kind6"},
            {&SynAttrValueKind7, 7, 0x350, "Kind7"},   {&SynAttrValueKindC, 0x0c, 0x3f8, "KindC"},
            {&SynAttrValueKindD, 0x0d, 0x405, "KindD"}, {&SynAttrValueKindE, 0x0e, 0x412, "KindE"},
            {&SynAttrValueKindF, 0x0f, 0x41f, "KindF"},
        };
        for (const Case& c : aCases) {
            g_nKindAsked = -1;
            g_sLogs.clear();
            assert(c.pfn(aRec) == g_pValue);
            assert(g_nKindAsked == c.nKind);        // the exact kind went into slot 0x10
            assert(g_sLogs.empty());                // nothing reported on a valid record

            // the value the child answers is passed straight through, whatever it is
            g_pValue = (void*)0xABCD;
            assert(c.pfn(aRec) == (void*)0xABCD);
            g_pValue = (void*)0x5150;
        }
    }

    // ---- a null record reports IF_OK(m_pRec) at its own line and answers null
    {
        struct Case {
            void* (*pfn)(void*);
            uint32_t uLine;
        };
        const Case aCases[] = {
            {&SynAttrValueKind3, 0x31c}, {&SynAttrValueKind4, 0x329}, {&SynAttrValueKind5, 0x336},
            {&SynAttrValueKind6, 0x343}, {&SynAttrValueKind7, 0x350}, {&SynAttrValueKindC, 0x3f8},
            {&SynAttrValueKindD, 0x405}, {&SynAttrValueKindE, 0x412}, {&SynAttrValueKindF, 0x41f},
        };
        for (const Case& c : aCases) {
            void* aNull[1] = {nullptr};
            g_nKindAsked = -1;
            g_sLogs.clear();
            assert(c.pfn(aNull) == nullptr);
            assert(g_nKindAsked == -1);             // the child was never asked
            assert(g_sLogs.size() == 1);
            assert(g_sLogs[0].find("IF_OK") != std::string::npos);
            assert(g_sLogs[0].find("m_pRec") != std::string::npos);
            assert(g_sLogs[0].find("synattr.cpp") != std::string::npos);
            char szLine[16];
            std::snprintf(szLine, sizeof(szLine), "%u", c.uLine);
            assert(g_sLogs[0].find(szLine) != std::string::npos);
        }
    }
    // ---- and it really is the address of the pointer that is read, not the pointer itself
    {
        struct Holder {
            void* pPad;
            void* pRec;
        } aHolder[] = {{(void*)0x1234, aRecObj}};
        g_nKindAsked = -1;
        SynAttrValueKind3(&aHolder[0].pRec);      // a member address, not the object address
        assert(g_nKindAsked == 3);
        assert(aHolder[0].pPad == (void*)0x1234); // and nothing beside it is touched
    }

    g_LogApi = savedLog;
    std::printf("SYNDICATE_D34E_OK: the nine attribute field readers, 9 units, 74 checks\n");
    return 0;
}
