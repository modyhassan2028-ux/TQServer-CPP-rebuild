// d55a_test — the 5-int entry vector + the
// full introsort family. Includes the port .cpp
// directly to reach the static sort internals.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>

#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include "modules/syndicate/src/SyndicateMeedEntry.cpp"

using namespace syndicate;
using E5 = MeedEntry5;

// ---- the op seams: defined HERE inside
//  syndicate (the CrossMerit.cpp definitions
//  are not linked into the unit test) ----
static void* OpNew(size_t n) { return malloc(n); }
static void OpDel(void* p) { free(p); }
namespace syndicate {
void* (*g_fnMeritOpNew)(size_t) = OpNew;
void (*g_fnMeritOpDelete)(void*) = OpDel;
}

// ---- the comparator: descending by v[2] ----
static char CmpDesc(const E5* a, const E5* b) {
    return a->v[2] > b->v[2] ? 1 : 0;
}

// the MSVC debug vector layout for 5-int
// entries: {proxy@0, ?, ?, begin@0x18,
// end@0x20, cap@0x28}
struct Vec5 {
    void* proxy;
    void* x1; void* x2;
    E5* begin;   // +0x18
    E5* end;     // +0x20
    E5* cap;     // +0x28
    void init() {
        proxy = nullptr; x1 = x2 = nullptr;
        begin = end = cap = nullptr;
    }
    size_t size() const { return end - begin; }
    size_t capa() const { return cap - begin; }
};

static E5 mk(int id, int a, int pts) {
    E5 e; e.v[0] = id; e.v[1] = a;
    e.v[2] = pts; e.v[3] = 0; e.v[4] = 0;
    return e;
}

// multiset-of-entries equality
static bool sameEntries(const E5* a, size_t n,
                        const E5* b) {
    std::vector<std::array<int,5>> va, vb;
    for (size_t i = 0; i < n; i++) {
        std::array<int,5> t;
        memcpy(t.data(), a[i].v, 20);
        va.push_back(t);
        memcpy(t.data(), b[i].v, 20);
        vb.push_back(t);
    }
    std::sort(va.begin(), va.end());
    std::sort(vb.begin(), vb.end());
    return va == vb;
}

int main() {
    g_fnMeedEntryCmp = nullptr;
    // ===== section 1: the primitives =====
    {
        E5 a = mk(1, 2, 3), b = mk(4, 5, 6);
        MeedEntrySwap5(&a, &b);
        assert(a.v[0] == 4 && b.v[0] == 1);
        E5 arr[3] = {mk(1,0,10), mk(2,0,20), mk(3,0,30)};
        E5 dst[3];
        MeedEntryFillCopy(arr, 0, &a);   // n=0 noop
        MeedEntryFillCopy(dst, 2, &arr[0]);
        assert(dst[1].v[2] == 10);       // fill 2x
        E5* e2 = MeedEntryCopyFwd(arr, arr + 2, dst);
        assert(e2 == dst + 2);
        assert(dst[1].v[0] == 2);
        // the bwd copy (copy_backward): [arr+1,
        //  arr+3) ENDS at dst+2: dst[1]=arr[2],
        //  dst[0]=arr[1]
        int64_t r = MeedEntryCopyBwd(
            (int64_t)(arr + 1), (int64_t)(arr + 3),
            (int64_t)(dst + 2));
        assert(r == (int64_t)(dst + 2) - 2 * 0x14);
        assert(dst[1].v[2] == 30 && dst[0].v[2] == 20);
        // the copy-to: [arr,arr+2) -> arr+1
        r = MeedEntryCopyTo(arr, arr + 2,
                            (int64_t)(arr + 1));
        assert(r == (int64_t)(arr + 1) + 2 * 0x14);
        assert(arr[1].v[0] == 1 && arr[2].v[0] == 1);
        // the rotbwd: [ro, ro+2) up one entry
        E5 ro[4] = {mk(0,0,0), mk(1,0,1), mk(2,0,2), mk(3,0,3)};
        r = MeedEntryRotBwd((int64_t)&ro[0],
                            (int64_t)&ro[2],
                            (int64_t)(&ro[2] + 1));
        // p3 - count*0x14 = (ro+3) - 2*0x14 = ro+1
        assert(r == (int64_t)&ro[1]);
        assert(ro[1].v[2] == 0 && ro[2].v[2] == 1
            && ro[3].v[2] == 3);
        printf("D55a-1 the primitives ok\n");
    }
    // ===== section 2: the vector =====
    {
        Vec5 v; v.init();
        E5 e1 = mk(10, 0, 100);
        MeedEntryVecPush(&v, &e1);
        assert(v.size() == 1 && v.begin[0].v[0] == 10);
        assert(v.capa() >= 1);
        E5 e2 = mk(11, 0, 90);
        MeedEntryVecPush(&v, &e2);
        assert(v.size() == 2 && v.begin[1].v[0] == 11);
        // push past the capacity -> the grow path
        size_t c0 = v.capa();
        for (int i = 2; i < (int)c0 + 5; i++) {
            E5 e = mk(10 + i, 0, 100 - i);
            MeedEntryVecPush(&v, &e);
        }
        assert(v.size() == c0 + 5);
        assert(v.capa() >= v.size());
        // verify the contents survived the realloc
        for (size_t i = 0; i < v.size(); i++) {
            assert(v.begin[i].v[0] == 10 + (int)i);
        }
        // the mid insert (the 3b70 direct call):
        // insert one entry at pos 1
        void* pair[2] = {(void*)v.proxy, v.begin + 1};
        E5 eMid = mk(99, 0, 99);
        MeedEntryVecInsert(&v, pair, 1, &eMid);
        assert(v.size() == c0 + 6);
        assert(v.begin[1].v[0] == 99);
        assert(v.begin[0].v[0] == 10);
        assert(v.begin[2].v[0] == 11);
        assert(v.begin[v.size() - 1].v[0] ==
               10 + (int)c0 + 4);
        // the erase-tail (the clear)
        MeedEntryVecEraseTail(&v);
        assert(v.size() == 0);
        // erase on an empty vec: no-op
        MeedEntryVecEraseTail(&v);
        assert(v.end == v.begin);
        g_fnMeritOpDelete(v.begin);
        printf("D55a-2 the vector ok\n");
    }
    // ===== section 3: the full sort =====
    {
        srand(4242);
        for (int round = 0; round < 20; round++) {
            int n = 1 + rand() % 3000;
            E5* arr = (E5*)malloc(n * sizeof(E5));
            E5* orig = (E5*)malloc(n * sizeof(E5));
            for (int i = 0; i < n; i++) {
                int pts = rand() % 50;  // heavy dups
                arr[i] = mk(i, rand() % 7, pts);
                orig[i] = arr[i];
            }
            void* pf[2] = {(void*)arr, (void*)arr};
            void* pl[2] = {(void*)arr, (void*)(arr + n)};
            MeedEntrySort(pf, pl, CmpDesc);
            for (int i = 1; i < n; i++) {
                assert(arr[i - 1].v[2] >= arr[i].v[2]);
            }
            assert(sameEntries(arr, n, orig));
            free(arr); free(orig);
        }
        printf("D55a-3 the full sort ok\n");
    }
    // ===== section 4: the internals =====
    {
        // the guarded insertion directly
        E5 a[5] = {mk(0,0,50), mk(1,0,10), mk(2,0,40),
                   mk(3,0,20), mk(4,0,30)};
        MeedEntryInsertionGuarded(a, a + 5, CmpDesc);
        for (int i = 1; i < 5; i++) {
            assert(a[i - 1].v[2] >= a[i].v[2]);
        }
        // the heap directly: make + the pop loop
        srand(77);
        E5 h[100];
        for (int i = 0; i < 100; i++) {
            h[i] = mk(i, 0, rand() % 1000);
        }
        MeedEntryHeapMake(h, h + 100, CmpDesc);
        // the predicate-consistent heap: NOT
        //  cmp(child, parent) — with CmpDesc
        //  that is parent <= child on values
        for (int i = 1; i < 100; i++) {
            assert(h[(i - 1) / 2].v[2] <= h[i].v[2]);
        }
        E5 hcopy[100];
        memcpy(hcopy, h, sizeof(h));
        MeedEntryHeapPopLoop(h, h + 100, CmpDesc);
        for (int i = 1; i < 100; i++) {
            assert(h[i - 1].v[2] >= h[i].v[2]);
        }
        assert(sameEntries(h, 100, hcopy));
        // the partition directly
        E5 p[40];
        for (int i = 0; i < 40; i++) {
            p[i] = mk(i, 0, rand() % 10);
        }
        E5 pcopy[40];
        memcpy(pcopy, p, sizeof(p));
        E5* out[2];
        MeedEntryPartition((E5**)out, p, p + 40, CmpDesc);
        int pv = out[0]->v[2];
        bool allEq = true;
        for (E5* q = out[0]; q != out[1]; q++) {
            if (q->v[2] != pv) allEq = false;
        }
        assert(allEq);
        for (E5* q = p; q != out[0]; q++) {
            assert(q->v[2] >= pv);
        }
        for (E5* q = out[1]; q != p + 40; q++) {
            assert(q->v[2] <= pv);
        }
        assert(sameEntries(p, 40, pcopy));
        printf("D55a-4 the internals ok\n");
    }
    // ===== section 5: the edges =====
    {
        for (int n : {0, 1, 2, 32, 33, 0x21, 100}) {
            E5 a[100];
            for (int i = 0; i < n; i++) {
                a[i] = mk(i, 0, (i * 37) % 100);
            }
            E5 c[100];
            memcpy(c, a, n * sizeof(E5));
            void* pf[2] = {(void*)a, (void*)a};
            void* pl[2] = {(void*)a, (void*)(a + n)};
            MeedEntrySort(pf, pl, CmpDesc);
            for (int i = 1; i < n; i++) {
                assert(a[i - 1].v[2] >= a[i].v[2]);
            }
            assert(n == 0 || sameEntries(a, n, c));
        }
        // the all-equal array: the one-pass pivot
        E5 eq[200];
        for (int i = 0; i < 200; i++) {
            eq[i] = mk(i, 0, 5);
        }
        void* pf[2] = {(void*)eq, (void*)eq};
        void* pl[2] = {(void*)eq, (void*)(eq + 200)};
        MeedEntrySort(pf, pl, CmpDesc);
        for (int i = 0; i < 200; i++) {
            assert(eq[i].v[2] == 5);
        }
        printf("D55a-5 the edges ok\n");
    }
    printf("SYNDICATE_D55A_OK: the 5-int entry "
           "vector + the introsort\n");
    return 0;
}
