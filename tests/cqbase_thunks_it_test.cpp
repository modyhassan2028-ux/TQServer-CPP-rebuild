// Generated with family IT — successor walk over a small hand-built tree.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_it.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static void* g_pArg = nullptr; static int g_nRep = 0;
static int Hook(void* p) { ++g_nRep; g_pArg = p; return 0; }

static unsigned char aNone[0x80], aHead[0x80], aH[0x80], aA[0x80], aB[0x80], aC[0x80];
static unsigned char aThis[0x80];

static inline void* at(void* p, size_t o) { return *(void**)((unsigned char*)p + o); }
static inline void put(void* p, size_t o, void* v) { *(void**)((unsigned char*)p + o) = v; }
static inline unsigned char mk(void* p, size_t o) { return *(unsigned char*)((unsigned char*)p + o); }
static inline void setmk(void* p, size_t o, unsigned char v) { *(unsigned char*)((unsigned char*)p + o) = v; }

// Build:  head(mark) -> left = H ;  H.left = A ;  H.right = B ;  B.left = C ;  leaves point at aNone.
static void Build(size_t nMark, size_t nRight, size_t nSelf) {
    std::memset(aNone, 0, sizeof(aNone)); std::memset(aHead, 0, sizeof(aHead));
    std::memset(aH, 0, sizeof(aH)); std::memset(aA, 0, sizeof(aA));
    std::memset(aB, 0, sizeof(aB)); std::memset(aC, 0, sizeof(aC));
    setmk(aNone, nMark, 1);                      // the nil sentinel
    setmk(aHead, nMark, 1);                      // the end() sentinel
    put(aHead, nSelf, aH);
    put(aH, nSelf, aHead); put(aH, nRight, aB); put(aH, 0, aA);
    put(aA, nSelf, aH);  put(aA, nRight, aNone); setmk(aA, nMark, 0);
    put(aB, nSelf, aH);  put(aB, nRight, aNone); setmk(aB, nMark, 0);
    put(aB, 0, aC);
    put(aC, nSelf, aB);  put(aC, nRight, aNone); put(aC, 0, aNone); setmk(aC, nMark, 0);
}

#define RUN(fn, nMark, nRight, nSelf) do { \
    Build(nMark, nRight, nSelf); g_nRep = 0; \
    put(aThis, nSelf, aA); put(aThis, 0, (void*)1); \
    fn(aThis); CHECK(at(aThis, nSelf) == aH);       /* A: climb one level */ \
    Build(nMark, nRight, nSelf); g_nRep = 0; \
    put(aThis, nSelf, aB); put(aThis, 0, (void*)1); \
    fn(aThis); CHECK(g_nRep == 0); CHECK(at(aThis, nSelf) == aHead);  /* B was a right child: end() */ \
    Build(nMark, nRight, nSelf); g_nRep = 0; \
    put(aThis, nSelf, aH); put(aThis, 0, (void*)1); \
    fn(aThis); CHECK(g_nRep == 0); CHECK(at(aThis, nSelf) == aC);    /* descend B.left spine */ \
    Build(nMark, nRight, nSelf); g_nRep = 0; \
    put(aThis, nSelf, aHead); put(aThis, 0, (void*)1); \
    fn(aThis); CHECK(g_nRep == 1); CHECK(g_pArg == (void*)aHead);    /* already at end */ \
    CHECK(at(aThis, nSelf) == aHead); \
    Build(nMark, nRight, nSelf); g_nRep = 0; \
    put(aThis, nSelf, aA); put(aThis, 0, nullptr); \
    fn(aThis); CHECK(g_nRep == 1); CHECK(g_pArg == (void*)aThis);    /* null container reports the holder */ \
    CHECK(at(aThis, nSelf) == aH); \
} while (0)

int main() {
    g_fnIT_1418233c0 = &Hook;

    RUN(SynIterNext_141722ef0, 0x29, 0x10, 0x8);   // 0x141722ef0
    RUN(SynIterNext_141722fc0, 0x1d, 0x10, 0x8);   // 0x141722fc0
    RUN(SynIterNext_141723090, 0x49, 0x10, 0x8);   // 0x141723090
    RUN(SynIterNext_141723a50, 0x1b, 0x10, 0x8);   // 0x141723a50
    RUN(SynIterNext_141724ed0, 0x1d, 0x10, 0x8);   // 0x141724ed0
    RUN(SynIterNext_1417250d0, 0x51, 0x10, 0x8);   // 0x1417250d0
    RUN(SynIterNext_14173b240, 0x21, 0x10, 0x8);   // 0x14173b240
    RUN(SynIterNext_14173b6c0, 0x61, 0x10, 0x8);   // 0x14173b6c0
    RUN(SynIterNext_1417447d0, 0x29, 0x10, 0x8);   // 0x1417447d0
    RUN(SynIterNext_141744cb0, 0x3d, 0x10, 0x8);   // 0x141744cb0
    RUN(SynIterNext_141750670, 0x61, 0x10, 0x8);   // 0x141750670
    RUN(SynIterNext_141750760, 0x2d, 0x10, 0x8);   // 0x141750760
    RUN(SynIterNext_1417512f0, 0x59, 0x10, 0x8);   // 0x1417512f0
    RUN(SynIterNext_141751380, 0x69, 0x10, 0x8);   // 0x141751380
    RUN(SynIterNext_141753470, 0x29, 0x10, 0x8);   // 0x141753470
    RUN(SynIterNext_141753500, 0x61, 0x10, 0x8);   // 0x141753500
    RUN(SynIterNext_141753620, 0x29, 0x10, 0x8);   // 0x141753620
    RUN(SynIterNext_1417536b0, 0x29, 0x10, 0x8);   // 0x1417536b0
    RUN(SynIterNext_141753d70, 0x29, 0x10, 0x8);   // 0x141753d70
    RUN(SynIterNext_141754000, 0x29, 0x10, 0x8);   // 0x141754000
    RUN(SynIterNext_141776460, 0x39, 0x10, 0x8);   // 0x141776460
    RUN(SynIterNext_14177a5c0, 0x29, 0x10, 0x8);   // 0x14177a5c0
    RUN(SynIterNext_1417899e0, 0x49, 0x10, 0x8);   // 0x1417899e0
    RUN(SynIterNext_141789d70, 0x29, 0x10, 0x8);   // 0x141789d70
    RUN(SynIterNext_141790e10, 0x21, 0x10, 0x8);   // 0x141790e10
    RUN(SynIterNext_141791080, 0x61, 0x10, 0x8);   // 0x141791080
    RUN(SynIterNext_141792240, 0x29, 0x10, 0x8);   // 0x141792240
    RUN(SynIterNext_1417a70b0, 0x29, 0x10, 0x8);   // 0x1417a70b0

    std::printf("SYNDICATE_THUNKS_IT_OK: 28 bodies, %d checks\n", g_nChecks);
    return 0;
}
