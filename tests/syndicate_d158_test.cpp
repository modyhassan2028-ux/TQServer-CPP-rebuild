// D158 — the matching walk 0x1417c8aa0: the assert on a null argument, the immediate end when the
//   node already is the limit, and the element the comparison seam accepts.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
namespace tq {
void* SynAccFindMatch_1417c8aa0(void* pThis, void* pArg2);
extern void (*g_pfnSynAssert_141823030)(const void*, const void*, const void*, const void*, uint32_t);
extern int (*g_pfnSynCmp3_1418232b0)(void*, void*, unsigned int);
extern uint64_t (*g_pfnLogic_14178f470)(uint64_t);
}
using namespace tq;

static int g_asserts = 0;
static void* g_aFile; static void* g_aLine; static void* g_aR8; static void* g_aR9;
static uint32_t g_aNum;
static void AssertHook(const void* a, const void* b, const void* c, const void* d, uint32_t n) {
    g_asserts++; g_aFile = (void*)a; g_aR8 = (void*)b; g_aR9 = (void*)c; g_aNum = n; (void)d;
}
static void* g_expectElem;
static int g_cmpCalls;
static int g_cmpVerdict;
static unsigned int g_cmpFlags;
static int Cmp3(void* a, void* b, unsigned int flags) {
    g_cmpCalls++; g_cmpFlags = flags; (void)b;
    return (a == g_expectElem) ? g_cmpVerdict : 1;
}
static uint64_t Gate(uint64_t v) { return v; }             // the 0x14178f470 hand-over

int main() {
    alignas(16) unsigned char self[0x60], holder[0x20], limit[0x60], node[0x60], elem[0x20];
    std::memset(self, 0, sizeof self); std::memset(holder, 0, sizeof holder);
    std::memset(limit, 0, sizeof limit); std::memset(node, 0, sizeof node);
    std::memset(elem, 0, sizeof elem);

    g_pfnSynAssert_141823030 = &AssertHook;
    g_pfnSynCmp3_1418232b0 = &Cmp3;
    g_pfnLogic_14178f470 = &Gate;

    // ---- the null argument is the only thing the assert guards
    assert(SynAccFindMatch_1417c8aa0(self, nullptr) == nullptr);
    assert(g_asserts == 1);
    assert(g_aFile == (void*)(uintptr_t)0x141824ca8);
    assert(g_aR8 == (void*)(uintptr_t)0x141827b98);
    assert(g_aR9 == (void*)(uintptr_t)0x14183a778);
    assert(g_aNum == 0x172);

    // ---- the holder's first qword is the limit; reaching it answers nothing
    *(void**)(self + 0x38) = holder;
    *(void**)(holder) = holder;                             // the cursor is the holder itself
    *(void**)(self + 8) = holder;
    g_asserts = 0; g_cmpCalls = 0;
    assert(SynAccFindMatch_1417c8aa0(self, elem) == nullptr);
    assert(g_asserts == 0);
    assert(g_cmpCalls == 0);

    // ---- one element tested, the seam accepts it, the answer is that element
    *(void**)(holder) = limit;                              // the cursor starts at limit
    *(void**)(self + 8) = node;
    *(void**)(node) = limit;                                // the lead the walk re-reads
    *(void**)(limit + 0x30) = nullptr;                      // so the seam check sees no match
    *(void**)(limit + 0x20) = elem;   // the element is read from the cursor, not from the node
    g_expectElem = elem; g_cmpVerdict = 0;
    g_cmpCalls = 0;
    void* got = SynAccFindMatch_1417c8aa0(self, nullptr == elem ? elem : elem);
    assert(got == elem);
    assert(g_cmpCalls == 1);
    assert(g_cmpFlags == 0x10);                             // the third argument the bytes pass

    std::puts("SYNDICATE_D158_OK: matching walk, 3 paths");
    return 0;
}
