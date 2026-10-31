// D12 (CQBase) — myheap.cpp: the counted heaps
#include "modules/cqbase/src/myheap.h"
#include "modules/cqbase/src/cini.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
using namespace tq;

static int g_nLogs = 0;
static std::string g_strLast;
static void CatchLog(const char* pszFormat, ...) {
    va_list vaArgs; va_start(vaArgs, pszFormat);
    char szBuf[1024]; vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
    va_end(vaArgs);
    g_strLast = szBuf; ++g_nLogs;
}

int main() {
    g_pfnLogPrintf = CatchLog;
    {
        CMyHeap heap("TestHeap");
        assert(heap.m_pBaseHeap != nullptr);
        assert(heap.m_pBaseHeap->m_strName == "TestHeap");
        assert(heap.m_pBaseHeap->m_hHeap != nullptr);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 0);

        // allocs are counted, a zero size is not
        void* pA = heap.Alloc(16);
        assert(pA != nullptr);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 1);
        assert(heap.Alloc(0) == nullptr);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 1);
        void* pB = heap.Alloc(32);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 2);

        assert(heap.IsValidPt(pA) == true);
        assert(heap.IsValidPt(nullptr) == false);       // nothing to validate

        // frees are counted, a null pointer is ignored
        g_nLogs = 0;
        heap.Free(nullptr);
        assert(g_nLogs == 0);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 2);
        heap.Free(pA);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 1);
        heap.Free(pB);
        assert(heap.m_pBaseHeap->m_nNumAlloc == 0);

        // a free with a count already at zero is reported and still goes through,
        // the report falls through to the heap handle check rather than returning
        g_nLogs = 0;
        void* pC = heap.Alloc(8);
        heap.m_pBaseHeap->m_nNumAlloc = 0;              // pretend the count was lost
        heap.Free(pC);
        assert(g_nLogs == 1);
        assert(g_strLast.find("m_lNumAlloc > 0") != std::string::npos);
        assert(heap.m_pBaseHeap->m_nNumAlloc == -1);     // it still went down

        // the assignment shares the base, it does not copy it
        CMyHeap other("OtherHeap");
        other = heap;
        assert(other.m_pBaseHeap == heap.m_pBaseHeap);
        // break the sharing so the two destructors do not both free it
        other.m_pBaseHeap = nullptr;
        heap.m_pBaseHeap->m_nNumAlloc = 0;

        // a heap with no base refuses every call and says why
        g_nLogs = 0;
        CMyHeap* pEmpty = new CMyHeap("Empty");
        CMyBaseHeap* pKeep = pEmpty->m_pBaseHeap;
        pEmpty->m_pBaseHeap = nullptr;
        assert(pEmpty->Alloc(4) == nullptr);
        pEmpty->Free(pA);
        assert(pEmpty->IsValidPt(pA) == false);
        assert(g_nLogs == 3);
        pEmpty->m_pBaseHeap = pKeep;
        delete pEmpty;

        // a base without its heap: alloc reports, free reports and returns, the
        // validator answers false without a word
        CMyBaseHeap base("NoHeap");
        void* hKeep = base.m_hHeap;
        base.m_hHeap = nullptr;
        g_nLogs = 0;
        assert(base.Alloc(4) == nullptr);
        assert(g_nLogs == 1);
        g_nLogs = 0;
        base.Free(pA);
        // two reports: the count is zero on a fresh base and the handle is gone
        assert(g_nLogs == 2);
        assert(g_strLast.find("m_hHeap") != std::string::npos);
        base.m_hHeap = hKeep;
    }
    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D12_OK: CMyHeap/CMyBaseHeap counts, refusals, sharing\n");
    return 0;
}
