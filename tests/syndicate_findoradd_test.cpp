// 0x14172ae00 — the map's find-or-insert, driven through the ported RB insert helper.
// Only the node factory and the CRT hook are stubbed; the wrapper and the insert logic are ported.
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include "modules/syndicate/src/synrbfindoradd.h"
#include "modules/syndicate/src/synrbinsert_family.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

// the synattr comparator logs through this hook; the find-or-insert never reaches it
namespace tq {
void log_InlineLogERROR(const char*, ...) {}
}

using namespace tq;
#define Q(p,o) (*(void**)((uint8_t*)(p)+(o)))
#define B(p,o) (*(uint8_t*)((uint8_t*)(p)+(o)))
#define D(p,o) (*(uint32_t*)((uint8_t*)(p)+(o)))

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char pool[512][0x80];
static int used;
static unsigned char arena[0x80];
static unsigned char outbuf[0x40];
static void* head;
static uint32_t g_colour = 0x1c;
static int g_throws;

static void* Alloc(void*, void* nil, void* parent, void*, const uint32_t* key, uint8_t c) {
    void* n = pool[used++];
    std::memset(n, 0, 0x80);
    Q(n, 0x00) = nil; Q(n, 0x10) = nil; Q(n, 0x08) = parent;
    D(n, 0x18) = *key;
    B(n, g_colour) = c; B(n, 0x1d) = 0;
    return n;
}
static void Throw(void) { ++g_throws; }
static void NoInfo(void) { ++g_throws; }

static bool nil(void* n) { return B(n, 0x1d) != 0; }
static void inorder(void* n, uint32_t* out, int* k) {
    if (nil(n)) return;
    inorder(Q(n, 0x00), out, k);
    out[(*k)++] = D(n, 0x18);
    inorder(Q(n, 0x10), out, k);
}
static int black_height(void* n) {
    if (nil(n)) return 1;
    const int l = black_height(Q(n, 0x00)), r = black_height(Q(n, 0x10));
    if (l < 0 || r < 0 || l != r) return -1;
    return l + (B(n, g_colour) ? 1 : 0);
}
static bool no_red_red(void* n) {
    if (nil(n)) return true;
    if (!B(n, g_colour)) {
        if (!nil(Q(n, 0x00)) && !B(Q(n, 0x00), g_colour)) return false;
        if (!nil(Q(n, 0x10)) && !B(Q(n, 0x10), g_colour)) return false;
    }
    return no_red_red(Q(n, 0x00)) && no_red_red(Q(n, 0x10));
}
static void reset() {
    used = 0; g_throws = 0;
    std::memset(pool, 0, sizeof pool);
    std::memset(arena, 0, sizeof arena);
    std::memset(outbuf, 0, sizeof outbuf);
    head = pool[511];
    std::memset(head, 0, 0x80);
    B(head, 0x1d) = 1; B(head, g_colour) = 1;
    Q(head, 0x00) = head; Q(head, 0x08) = head; Q(head, 0x10) = head;
    Q(arena, 0x00) = arena;                    // the word every iterator carries
    Q(arena, 0x30) = head;
}
static void verify(const char* what, const uint32_t* expect, int n) {
    uint32_t got[256]; int k = 0;
    inorder(Q(head, 0x08), got, &k);
    CHECK(k == n);
    for (int i = 0; i < k && i < n; ++i) CHECK(got[i] == expect[i]);
    CHECK(*(uint64_t*)(arena + 0x38) == (uint64_t)n);
    void* root = Q(head, 0x08);
    if (!nil(root)) CHECK(B(root, g_colour) != 0);
    CHECK(no_red_red(root));
    CHECK(black_height(root) >= 0);
    (void)what;
}
static void insert(uint32_t key, int expect_new, uint32_t* pNodeKey) {
    void* out = outbuf;
    void* p = Slot_14172ae00(arena, out, &key);
    CHECK(p == out);                                   // the out pointer comes back
    CHECK(B(out, 0x10) == (uint8_t)(expect_new ? 1 : 0));
    CHECK(Q(out, 0x00) == (void*)arena);               // the iterator's container word
    void* n = Q(out, 0x08);
    CHECK(n != nullptr && !nil(n));
    if (pNodeKey) *pNodeKey = D(n, 0x18);
    CHECK(D(n, 0x18) == key);                          // the iterator names this key
}

int main() {
    g_fnRB_1417293c0_factory = Alloc;
    g_fnRB_1417293c0_throw = Throw;
    g_pfn_invalid_parameter_noinfo = NoInfo;

    static const uint32_t suite[6][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
        {1, 2, 3, 4, 5, 6, 7},
    };
    for (int s = 0; s < 6; ++s) {
        reset();
        for (int i = 0; i < 7; ++i) insert(suite[s][i], 1, nullptr);
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; ++i)
            for (int j = i + 1; j < 7; ++j)
                if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        verify("order", expect, 7);
        // every key again: no growth, the flag clears, the iterator still names the key
        for (int i = 0; i < 7; ++i) insert(suite[s][i], 0, nullptr);
        verify("dup", expect, 7);
        CHECK(g_throws == 0);
    }

    // --- one key, then the same key: the pair must say false and keep the size
    {
        reset();
        insert(42, 1, nullptr);
        CHECK(*(uint64_t*)(arena + 0x38) == 1);
        insert(42, 0, nullptr);
        CHECK(*(uint64_t*)(arena + 0x38) == 1);
        uint32_t expect[1] = {42};
        verify("single", expect, 1);
    }

    // --- a sweep big enough to exercise the predecessor fixup and the red-black balancing
    {
        reset();
        uint64_t seed = 0x243F6A8885A308D3ULL;
        uint32_t keys[120];
        for (int i = 0; i < 120; ++i) {
            seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
            keys[i] = (uint32_t)((seed >> 33) % 200);
        }
        bool seen[200] = {false};
        int nNew = 0;
        for (int i = 0; i < 120; ++i) {
            insert(keys[i], seen[keys[i]] ? 0 : 1, nullptr);   // the pair must say whether it was new
            if (!seen[keys[i]]) { seen[keys[i]] = true; ++nNew; }
        }
        CHECK(nNew == (int)*(uint64_t*)(arena + 0x38));
        uint32_t expect[120];
        std::memcpy(expect, keys, sizeof expect);
        for (int i = 0; i < 120; ++i)          // a small insertion sort for the expectation
            for (int j = i + 1; j < 120; ++j)
                if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        int nUniq = 0;
        for (int i = 0; i < 120; ++i)
            if (i == 0 || expect[i] != expect[i - 1]) expect[nUniq++] = expect[i];
        verify("sweep", expect, nUniq);
        CHECK(*(uint64_t*)(arena + 0x38) == (uint64_t)nUniq);
        CHECK(g_throws == 0);
    }

    std::printf("FINDORADD_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
