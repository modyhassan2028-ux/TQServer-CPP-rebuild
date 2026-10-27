// ============================================================
// Peerage.dll — Unit T3 (D19) regression: the sort
// engine (MSVC introsort: 141555b60 + 1415545b0 +
// 141554000/141553aa0 + the heap 141553b30/1415547e0/
// 141554f80 + the insertion 141554160) and the
// comparison chain (141552810 / 141552180) + the
// f80 sort-call wrapper.
// Must print PEERAGE-D19-OK.
// ============================================================
#include "../modules/peerage/src/PeerageSort.h"
#include "../modules/peerage/src/PeerageSortMgr.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace peerage;

// the row mock: +vt+0x58 = the int64 value,
// vt+0x40 = the uint id
struct SRow { int64_t v; uint32_t id; uint32_t pad; };
static SRow g_rows[256];
static void* defRowQ2(void* p, int n) {
    // elem+8 holds the row; the query passes it
    // through (the vt+0x10(n) slot)
    (void)n; return p; }
static int64_t defRowV(void* p) {
    return ((SRow*)p)->v; }
static uint32_t defRowI(void* p) {
    return ((SRow*)p)->id; }

// the elem mock: 0x30 bytes; +8 the row, +0x18 the key
struct SElem { uint8_t ab[0x30]; };
static void MakeElem(SElem* e, int i,
                     int64_t v, uint32_t k,
                     uint32_t id) {
    memset(e->ab, 0, sizeof(e->ab));
    *(void**)(e->ab + 8) = &g_rows[i];
    *(uint32_t*)(e->ab + 0x18) = k;
    g_rows[i].v = v; g_rows[i].id = id;
}

// the expected total order: value desc, key desc,
// id asc
static bool ExpectedLess(SElem* a, SElem* b) {
    int64_t va = g_rows[0].v; // (unused)
    va = 0; (void)va;
    void* ra = *(void**)(a->ab + 8);
    void* rb = *(void**)(b->ab + 8);
    if (((SRow*)ra)->v != ((SRow*)rb)->v)
        return ((SRow*)rb)->v < ((SRow*)ra)->v;
    uint32_t ka = *(uint32_t*)(a->ab + 0x18);
    uint32_t kb = *(uint32_t*)(b->ab + 0x18);
    if (ka != kb) return kb < ka;
    return ((SRow*)ra)->id < ((SRow*)rb)->id;
}

int main() {
    g_fnRowQuery2 = defRowQ2;
    g_fnRowGetValue = defRowV;
    g_fnRowGetId = defRowI;
    int nLogs = 0;
    g_fnSortLogError2 = []() {};

    // ---------- 1. the key (141552180) ----------
    SElem e1; memset(&e1, 0, sizeof(e1));
    *(uint32_t*)(e1.ab + 0x18) = 0x999;
    assert(PeerageSortKey(&e1) == 0x999);

    // ---------- 2. the pred (141552810) ----------
    SElem a, b;
    MakeElem(&a, 0, 100, 5, 1);
    MakeElem(&b, 1, 200, 5, 1);
    assert(PeerageSortPred(&a, &b) == false); // 200 first
    assert(PeerageSortPred(&b, &a) == true);
    // the null gates
    assert(PeerageSortPred(nullptr, &b) == false);
    assert(PeerageSortPred(&a, nullptr) == false);
    // tie on value -> the key descending
    MakeElem(&a, 0, 100, 7, 1);
    MakeElem(&b, 1, 100, 9, 1);
    assert(PeerageSortPred(&a, &b) == false);  // key 9 first
    assert(PeerageSortPred(&b, &a) == true);
    // tie on value+key -> the id ascending
    MakeElem(&a, 0, 100, 7, 3);
    MakeElem(&b, 1, 100, 7, 5);
    assert(PeerageSortPred(&a, &b) == true);   // 3 asc
    assert(PeerageSortPred(&b, &a) == false);

    // ---------- 3. the insertion (141554160) ------
    SElem el[5];
    int64_t vs[5] = {50, 30, 40, 10, 20};
    void* pE[5];
    for (int i = 0; i < 5; ++i) {
        MakeElem(&el[i], i, vs[i], 0, (uint32_t)i);
        pE[i] = &el[i];
    }
    SortInsertion(pE, pE + 5, PeerageSortPred);
    for (int i = 0; i < 5; ++i)
        assert(defRowV(*(void**)((char*)pE[i] + 8))
            == (int64_t)(50 - i * 10));

    // ---------- 4. the heap fallback (depth 0) ----
    static SElem big[64];
    static void* pBig[64];
    srand(42);
    for (int i = 0; i < 64; ++i) {
        MakeElem(&big[i], i, rand() % 1000, 0,
                 (uint32_t)i);
        pBig[i] = &big[i];
    }
    // depth = 0 and count > 0x20 -> make_heap +
    // sort_heap (the 141555b60 fallback branch)
    SortIntrosort(pBig, pBig + 64, 0, PeerageSortPred);
    for (int i = 1; i < 64; ++i)
        assert(!ExpectedLess((SElem*)pBig[i],
                             (SElem*)pBig[i-1]));

    // ---------- 5. the full introsort ------------
    static SElem huge[200];
    static void* pHuge[200];
    srand(7);
    for (int i = 0; i < 200; ++i) {
        // ties on value AND key -> the id asc keeps
        // the order deterministic
        MakeElem(&huge[i], i, rand() % 50,
                 rand() % 10, (uint32_t)i);
        pHuge[i] = &huge[i];
    }
    // (the f80 call: depth = the count)
    SortIntrosort(pHuge, pHuge + 200, 200,
                  PeerageSortPred);
    for (int i = 1; i < 200; ++i)
        assert(!ExpectedLess((SElem*)pHuge[i],
                             (SElem*)pHuge[i-1]));

    // ---------- 6. the wrapper (f80's sort call) -
    CPeerageSortMgr* pMgr = MakePeerageSortMgr();
    assert(pMgr != nullptr);
    static SElem we[40];
    for (int i = 0; i < 40; ++i) {
        MakeElem(&we[i], i, rand() % 100, 0,
                 (uint32_t)i);
        void* p = &we[i];
        VecPushBack(pMgr, &p);
    }
    SortPeerageVector(pMgr);
    void** pp = pMgr->m_vec.m_ppBegin;
    for (int i = 1; i < 40; ++i)
        assert(!ExpectedLess((SElem*)pp[i],
                             (SElem*)pp[i-1]));
    // the empty vector: a no-op
    CPeerageSortMgr* pEmpty = MakePeerageSortMgr();
    SortPeerageVector(pEmpty);

    free(pMgr->m_vec.m_ppBegin);
    free(pMgr->m_vec.m_pProxy);
    free(pEmpty->m_vec.m_pProxy);
    free(pMgr); free(pEmpty);
    printf("PEERAGE-D19-OK (nLogs=%d)\n", nLogs);
    return 0;
}
