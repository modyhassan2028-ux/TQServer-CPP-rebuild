// ============================================================
// Peerage.dll — unit D25: the CPeerageSort object-family
// completion — the dtor (141552040) with the row vt[0]
// release and the double-zero, the key getter (141552180),
// the static CMyHeap wrappers (141552190/250/2b0 —
// init-once + the heap seams), the scalar deleting dtor
// (141552310 — heap free on odd flags), the elem row ops
// (141552780/7a0), and the MSVC proxy iterator family
// (141552ed0/f10/f80/fc0 — deref/next/prev/eq with the
// debug range checks).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "../Exe/Dll/Peerage/Port/PeerageSortObj.h"
#include "../Exe/Dll/Peerage/Port/PeerageSortMgr.h"
#include "../Exe/Dll/Peerage/Port/PeerageSort.h"
#include "../Exe/Dll/Peerage/Port/PeerageDonate.h"

using namespace peerage;

// ---- the mock row/elem ----
struct MockRow { uint32_t id; int64_t value; };
struct SElem {
    void* vft;           // +0x00
    void* row;           // +0x08
    uint32_t state10;    // +0x10
    uint32_t rank14;     // +0x14
    uint32_t key18;      // +0x18
    uint8_t ab[0x14];    // +0x1c..0x30
};

static std::vector<std::string> g_vLog;
static int g_nInvalid = 0;
static int g_nRowDtor = 0;
static int g_nHeapCtor = 0;
static int g_nAtexit = 0;
static std::vector<void*> g_vHeapFree;
static std::vector<void*> g_vIsValid;
static std::vector<std::string> g_vRowOps;
static void* g_pRowDtorLast = nullptr;
static uint64_t g_uRowDtorFlags = 0;
static int64_t g_nRowDtorC = 0;

static void Reset() {
    g_vLog.clear(); g_nInvalid = 0;
    g_nRowDtor = 0; g_nHeapCtor = 0;
    g_nAtexit = 0; g_vHeapFree.clear();
    g_vIsValid.clear(); g_vRowOps.clear();
    g_pRowDtorLast = nullptr;
    g_uRowDtorFlags = 0; g_nRowDtorC = 0;
    // reset the init-once static: fresh instance per
    // section (the DAT lives in the port's TU)
    ResetHeapStatic();
}

static void Bind() {
    g_fnSortLogError = []() {
        g_vLog.push_back("log"); };
    g_fnInvalidParameter = []() {
        ++g_nInvalid; };
    g_pSortVftable = (const void*)0x1234;
    g_fnRowDtorVt0 = [](void* pRow, uint64_t uF,
                       void*, void*, int64_t nC) {
        ++g_nRowDtor;
        g_pRowDtorLast = pRow;
        g_uRowDtorFlags = uF;
        g_nRowDtorC = nC; };
    g_fnMyHeapCtor = [](void* p, const char* psz) {
        (void)p;
        ++g_nHeapCtor;
        g_vLog.push_back(
            std::string("heapctor:") + psz); };
    g_fnAtexitReg = [](void (*)()) {
        ++g_nAtexit; };
    g_fnMyHeapFree = [](void* p) {
        g_vHeapFree.push_back(p); };
    g_fnMyHeapIsValidPt = [](void* p) {
        g_vIsValid.push_back(p); };
    g_fnRowQuery2 = [](void* pRow, int n) {
        g_vRowOps.push_back(
            "q:" + std::to_string(n));
        return pRow; };
    g_fnRowGetId = [](void* pRec) {
        g_vRowOps.push_back("id");
        return ((MockRow*)pRec)->id; };
    g_fnRecSetTotalA0 = [](void* pRec,
                           int64_t v) {
        (void)pRec;
        g_vRowOps.push_back(
            "a0:" + std::to_string(v)); };
    g_fnRowVt38 = [](void* pRow, int n) {
        (void)pRow;
        g_vRowOps.push_back(
            "vt38:" + std::to_string(n)); };
}

int main() {
    Bind();

    // ---- 1. DtorCPeerageSort (141552040) ----
    {
        Reset();
        MockRow row{31, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)0x99;
        e.row = &row;
        DtorCPeerageSort(&e, 7, 8, 9);
        assert(e.vft == (void*)0x1234);   // the vft
        assert(g_nRowDtor == 1);
        assert(g_pRowDtorLast == &row);
        assert(g_uRowDtorFlags == 1);
        assert(g_nRowDtorC
            == (int64_t)0xfffffffffffffffe);
        assert(e.row == nullptr);   // zeroed TWICE
        // the null-row path: no release
        Reset();
        SElem e2; memset(&e2, 0, sizeof e2);
        e2.vft = (void*)0x99;
        DtorCPeerageSort(&e2, 1, 2, 3);
        assert(g_nRowDtor == 0);
        assert(e2.vft == (void*)0x1234);
        puts("D25-1 dtor ok");
    }

    // ---- 2. GetSortKey18 (141552180) ----
    {
        Reset();
        SElem e; memset(&e, 0, sizeof e);
        e.key18 = 77;
        assert(GetSortKey18(&e) == 77);
        puts("D25-2 key ok");
    }

    // ---- 3. the static CMyHeap wrappers (190/250/2b0) ----
    {
        Reset();
        void* h1 = GetHeapInstance();
        assert(h1 != nullptr);
        assert(g_nHeapCtor == 1);
        assert(g_nAtexit == 1);
        void* h2 = GetHeapInstance();
        assert(h1 == h2);
        assert(g_nHeapCtor == 1);   // once
        // the free/valid wrappers reuse the instance
        HeapFreeWrap((void*)0x55);
        assert(g_vHeapFree.size() == 1
            && g_vHeapFree[0] == (void*)0x55);
        assert(g_nHeapCtor == 1);
        HeapIsValidPtWrap((void*)0x66);
        assert(g_vIsValid.size() == 1
            && g_vIsValid[0] == (void*)0x66);
        assert(g_nInvalid == 0);
        puts("D25-3 heap wrappers ok");
    }

    // ---- 4. ScalarDeletingDtorSort (141552310) ----
    {
        Reset();
        MockRow row{31, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)0x99;
        e.row = &row;
        // flags even: no heap free
        void* r = ScalarDeletingDtorSort(&e, 0);
        assert(r == &e);
        assert(g_nRowDtor == 1);
        assert(g_vHeapFree.empty());
        // flags odd: the heap free fires
        Reset();
        SElem e2; memset(&e2, 0, sizeof e2);
        e2.vft = (void*)0x99;
        e2.row = &row;
        ScalarDeletingDtorSort(&e2, 3);
        assert(g_nRowDtor == 1);
        assert(g_vHeapFree.size() == 1
            && g_vHeapFree[0] == &e2);
        puts("D25-4 scalar dtor ok");
    }

    // ---- 5. ElemProbeRowId0 (141552780) ----
    {
        Reset();
        MockRow row{31, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.row = &row;
        ElemProbeRowId0(&e);
        assert(g_vRowOps.size() == 2);
        assert(g_vRowOps[0] == "q:0");
        assert(g_vRowOps[1] == "id");
        puts("D25-5 probe ok");
    }

    // ---- 6. ElemSetRowValue2 (1415527a0) ----
    {
        Reset();
        MockRow row{31, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.row = &row;
        ElemSetRowValue2(&e, 5000);
        assert(g_vRowOps.size() == 3);
        assert(g_vRowOps[0] == "q:2");
        assert(g_vRowOps[1] == "a0:5000");
        assert(g_vRowOps[2] == "vt38:0");
        puts("D25-6 set ok");
    }

    // ---- 7. the proxy iterator family (ed0/f10/f80) ----
    {
        Reset();
        // the container: *proxy = container, the vec
        // begin at container+0x18, end at +0x20
        static void* slots[4];
        static void** begin = &slots[0];
        static void** end = &slots[3];
        struct SContainer {
            void* pad[3];        // +0x00..0x17
            void** ppBegin18;    // +0x18
            void** ppEnd20;      // +0x20
        } cont;
        cont.ppBegin18 = begin;
        cont.ppEnd20 = end;
        static void* pProxy = &cont;
        // the iterator {proxy, slot}
        void* iter[2] = {&pProxy,
                         (void*)&slots[1]};
        // deref: returns the slot
        assert(ProxyAt(iter)
            == (void*)&slots[1]);
        assert(g_nInvalid == 0);
        // next: slot += 8
        void** r = ProxyNext(iter);
        assert(r == iter);
        assert(iter[1] == (void*)&slots[2]);
        assert(g_nInvalid == 0);
        // prev: slot -= 8
        ProxyPrev(iter);
        assert(iter[1] == (void*)&slots[1]);
        assert(g_nInvalid == 0);
        // out-of-range next: slot == end -> invalid
        iter[1] = (void*)&slots[3];   // == end
        ProxyNext(iter);
        assert(g_nInvalid == 1);
        // prev at begin: slot <= begin -> invalid
        Reset();
        iter[1] = (void*)&slots[0];
        ProxyPrev(iter);
        assert(g_nInvalid == 1);
        // null proxy: VERBATIM the invalid call fires
        // and (the original's _invalid_parameter_noinfo
        // never returns) — with a non-aborting seam the
        // re-read stays null, lVar2 = 0, and the range
        // check reads 0x20 -> the child crash-proves
        // the semantics
        Reset();
        void* iter2[2] = {nullptr,
                          (void*)&slots[1]};
        pid_t pid = fork();
        if (pid == 0) {
            ProxyAt(iter2);
            _exit(0);
        }
        int st = 0;
        waitpid(pid, &st, 0);
        assert(!(WIFEXITED(st)
                 && WEXITSTATUS(st) == 0));
        puts("D25-7 proxy iter ok");
    }

    // ---- 8. ProxyEq (141552fc0) ----
    {
        Reset();
        static void* pProxy = (void*)0x77;
        void* a[2] = {&pProxy, nullptr};
        void* b[2] = {&pProxy, nullptr};
        a[1] = (void*)0x10;
        b[1] = (void*)0x10;
        assert(ProxyEq(a, b) == true);
        b[1] = (void*)0x18;
        assert(ProxyEq(a, b) == false);
        assert(g_nInvalid == 0);
        // mismatched proxies -> invalid
        static void* pOther = (void*)0x88;
        void* c[2] = {&pOther, nullptr};
        ProxyEq(a, c);
        assert(g_nInvalid == 1);
        puts("D25-8 proxy eq ok");
    }

    puts("PEERAGE-D25-OK: sort-object family literal — "
         "dtor (row vt[0] -2 release, double zero), "
         "key18 getter, CMyHeap static wrappers "
         "(init-once + atexit + free/valid), scalar "
         "deleting dtor (heap free on odd), elem row "
         "ops (q0/id, q2/a0/vt38), MSVC proxy iterator "
         "family (at/next/prev/eq with the debug range "
         "checks)");
    return 0;
}
