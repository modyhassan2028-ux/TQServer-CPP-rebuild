// ============================================================================
// cqbase_d28 — the three tree searches and the two manager queries over them, on maps
//   built by hand at the exact offsets the binary reads
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/syntreemap.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

// ---- an id map node: key at +0x18, value at +0x20, nil at +0x29
static unsigned char* NewUNode(uint32_t uKey, void* pValue, unsigned char* pNilTarget) {
    unsigned char* p = (unsigned char*)::operator new(0x38);
    std::memset(p, 0, 0x38);
    *(uint32_t*)(p + 0x18) = uKey;
    *(void**)(p + 0x20) = pValue;
    *(void**)(p + 0x00) = pNilTarget;
    *(void**)(p + 0x10) = pNilTarget;
    *(void**)(p + 0x08) = pNilTarget;
    p[0x29] = 0;
    return p;
}
static unsigned char* NewUNil() {
    unsigned char* p = (unsigned char*)::operator new(0x38);
    std::memset(p, 0, 0x38);
    p[0x29] = 1;
    return p;
}

// ---- a name map node: a string at +0x18 and the nil byte at +0x41
static unsigned char* NewSNode(const char* pszKey, unsigned char* pHead) {
    unsigned char* p = (unsigned char*)::operator new(0x50);
    std::memset(p, 0, 0x50);
    new (p + 0x18) std::string(pszKey);
    p[0x41] = 0;
    *(void**)(p + 0x00) = pHead;                 // every empty link points at the head
    *(void**)(p + 0x08) = pHead;
    *(void**)(p + 0x10) = pHead;
    return p;
}
static unsigned char* NewSNil() {
    unsigned char* p = (unsigned char*)::operator new(0x50);
    std::memset(p, 0, 0x50);
    new (p + 0x18) std::string();
    p[0x41] = 1;
    return p;
}
static void FreeSNode(unsigned char* p) {
    ((std::string*)(p + 0x18))->~basic_string();
    ::operator delete(p);
}

// the manager object: the id map at +0x08 (head +0x38) and the name map at +0x48 (head +0x78)
struct FakeMgr {
    unsigned char a[0x100];
};

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    // ---- the id map: 10 <- 20 -> 30, the head is the nil node
    unsigned char* pHead = NewUNil();
    unsigned char* p10 = NewUNode(10, (void*)0x1010, pHead);
    unsigned char* p20 = NewUNode(20, (void*)0x2020, pHead);
    unsigned char* p30 = NewUNode(30, (void*)0x3030, pHead);
    pHead[0x29] = 1;
    *(void**)(pHead + 0x00) = p10;                  // the leftmost
    *(void**)(pHead + 0x08) = p20;                  // the root
    *(void**)(pHead + 0x10) = p30;                  // the rightmost
    *(void**)(p10 + 0x08) = p20;
    *(void**)(p30 + 0x08) = p20;
    *(void**)(p20 + 0x00) = p10;
    *(void**)(p20 + 0x10) = p30;

    FakeMgr mgr;
    std::memset(&mgr, 0, sizeof(mgr));
    *(void**)(mgr.a + 0x38) = pHead;                // the id map's head
    *(void**)(mgr.a + 0x08) = (void*)0x7A6;         // the map's tag
    *(void**)(mgr.a + 0x00) = (void*)0x7A6;

    // ---- the lower bound lands where the tree says
    {
        SynTreeIter it;
        uint32_t uKey;
        uKey = 20;
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == p20);
        assert(it.pTag == (void*)0x7A6);
        uKey = 15;                                       // no such key: the head comes back
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == pHead);
        uKey = 10;
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == p10);
        uKey = 5;
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == pHead);
        uKey = 35;                                       // past the end
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == pHead);
        uKey = 25;
        SynTreeFindUint(mgr.a + 0x08, &it, &uKey);
        assert(it.pNode == pHead);
    }

    // ---- the range covers exactly the wanted key
    {
        SynTreeRange range;
        uint32_t uKey = 20;
        SynTreeEqualRangeUint(mgr.a + 0x08, &range, &uKey);
        assert(range.pFirst == p20);
        assert(range.pLast == p30);                      // the next key up
        assert(range.pTagFirst == (void*)0x7A6 && range.pTagLast == (void*)0x7A6);
        uKey = 10;
        SynTreeEqualRangeUint(mgr.a + 0x08, &range, &uKey);
        assert(range.pFirst == p10);
        assert(range.pLast == p20);
        uKey = 40;                                       // nothing that high
        SynTreeEqualRangeUint(mgr.a + 0x08, &range, &uKey);
        assert(range.pFirst == pHead);
        assert(range.pLast == pHead);
    }

    // ---- the record lookup reads the value at +0x20 and refuses id zero
    {
        assert(SynManagerRecordById(&mgr, 20) == (void*)0x2020);
        assert(SynManagerRecordById(&mgr, 10) == (void*)0x1010);
        assert(SynManagerRecordById(&mgr, 30) == (void*)0x3030);
        assert(SynManagerRecordById(&mgr, 15) == nullptr);
        assert(SynManagerRecordById(&mgr, 0) == nullptr);
    }

    // ---- and the name map: alpha <- beta -> gamma
    unsigned char* pSHead = NewSNil();
    unsigned char* pAlpha = NewSNode("alpha", pSHead);
    unsigned char* pBeta = NewSNode("beta", pSHead);
    unsigned char* pGamma = NewSNode("gamma", pSHead);
    *(void**)(pSHead + 0x00) = pAlpha;
    *(void**)(pSHead + 0x08) = pBeta;
    *(void**)(pSHead + 0x10) = pGamma;
    *(void**)(pAlpha + 0x08) = pBeta;
    *(void**)(pGamma + 0x08) = pBeta;
    *(void**)(pBeta + 0x00) = pAlpha;
    *(void**)(pBeta + 0x10) = pGamma;
    *(void**)(mgr.a + 0x78) = pSHead;
    *(void**)(mgr.a + 0x48) = (void*)0x7A7;

    {
        g_sLogs.clear();
        assert(SynManagerNameAbsent(&mgr, "alpha") == false);   // it is there
        assert(SynManagerNameAbsent(&mgr, "beta") == false);
        assert(SynManagerNameAbsent(&mgr, "gamma") == false);
        assert(SynManagerNameAbsent(&mgr, "delta") == true);    // absent
        assert(SynManagerNameAbsent(&mgr, "aaa") == true);
        assert(SynManagerNameAbsent(&mgr, "zzz") == true);
        assert(g_sLogs.empty());
        assert(SynManagerNameAbsent(&mgr, nullptr) == false);
        assert(g_sLogs.size() == 1);
        assert(g_sLogs[0].find("pszNewName") != std::string::npos);

        SynTreeRange range;
        std::string strKey("beta");
        SynTreeEqualRangeStr(mgr.a + 0x48, &range, &strKey);
        assert(range.pFirst == pBeta);
        assert(range.pLast == pGamma);
        strKey = "aaaa";
        SynTreeEqualRangeStr(mgr.a + 0x48, &range, &strKey);
        assert(range.pFirst == pAlpha);
        assert(range.pLast == pAlpha);
    }

    FreeSNode(pAlpha);
    FreeSNode(pBeta);
    FreeSNode(pGamma);
    FreeSNode(pSHead);
    ::operator delete(p10);
    ::operator delete(p20);
    ::operator delete(p30);
    ::operator delete(pHead);

    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D28_OK: the three tree searches and the two manager queries, "
                "5 units, 33 checks\n");
    return 0;
}
