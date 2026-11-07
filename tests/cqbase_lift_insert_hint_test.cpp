// Insert-with-hint wrappers (SynLift, staged) driven through the ported RB insert helper.
// Only the node factory is stubbed; the wrapper and the insert logic are the ported ones.
#include <initializer_list>
#include <cstdio>
#include <cstring>
#include "modules/syndicate/src/synlift.h"
#include "modules/syndicate/src/synlift_stage.h"
#include "modules/syndicate/src/synrbinsert_family.h"

using namespace tq;
#define Q(p,o) (*(void**)((uint8_t*)(p)+(o)))
#define B(p,o) (*(uint8_t*)((uint8_t*)(p)+(o)))
#define D(p,o) (*(uint32_t*)((uint8_t*)(p)+(o)))

static unsigned char pool[4096][0x100];
static int used, checks, failures;
static unsigned char arena[0x80];
static void* head;
static unsigned char outbuf[0x40];
static uint32_t g_mark, g_colour;

static void* Alloc(void*, void* nil, void* parent, void*, const uint32_t* key, uint8_t c) {
    void* n = pool[used++];
    std::memset(n, 0, 0x100);
    Q(n, 0x00) = nil; Q(n, 0x10) = nil; Q(n, 0x08) = parent;
    D(n, 0x18) = *key;
    B(n, g_colour) = c; B(n, g_mark) = 0;
    return n;
}
template <void* (*INS)(void*, void*, uint8_t, void*, const uint32_t*)>
static uint64_t Tramp(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t) {
    return (uint64_t)(uintptr_t)INS((void*)a, (void*)b, (uint8_t)c, (void*)d, (const uint32_t*)e);
}
static void Throw(void) { std::printf("UNEXPECTED THROW\n"); failures++; }

static bool is_nil(void* n, unsigned mark) { return B(n, mark) != 0; }
static void inorder(void* n, unsigned mark, uint32_t* out, int* k) {
    if (is_nil(n, mark)) return;
    inorder(Q(n, 0x00), mark, out, k);
    out[(*k)++] = D(n, 0x18);
    inorder(Q(n, 0x10), mark, out, k);
}
static int black_height(void* n, unsigned mark, unsigned colour) {
    if (is_nil(n, mark)) return 1;
    int l = black_height(Q(n, 0x00), mark, colour), r = black_height(Q(n, 0x10), mark, colour);
    if (l < 0 || r < 0 || l != r) return -1;
    return l + (B(n, colour) ? 1 : 0);
}
static bool no_red_red(void* n, unsigned mark, unsigned colour) {
    if (is_nil(n, mark)) return true;
    if (!B(n, colour)) {
        if (!is_nil(Q(n, 0x00), mark) && !B(Q(n, 0x00), colour)) return false;
        if (!is_nil(Q(n, 0x10), mark) && !B(Q(n, 0x10), colour)) return false;
    }
    return no_red_red(Q(n, 0x00), mark, colour) && no_red_red(Q(n, 0x10), mark, colour);
}
static void reset(unsigned mark, unsigned colour) {
    used = 0; g_mark = mark; g_colour = colour;
    std::memset(pool, 0, sizeof pool); std::memset(arena, 0, sizeof arena); std::memset(outbuf, 0, sizeof outbuf);
    head = pool[4095]; std::memset(head, 0, 0x100);
    B(head, mark) = 1; B(head, colour) = 1;
    Q(head, 0x00) = head; Q(head, 0x08) = head; Q(head, 0x10) = head;
    Q(arena, 0x00) = arena;
    Q(arena, 0x30) = head;
}
static void verify(const char* what, const uint32_t* expect, int n_expect) {
    void* root = Q(head, 0x08);
    uint32_t got[64]; int k = 0;
    inorder(root, g_mark, got, &k);
    checks++;
    if (k != n_expect) { std::printf("FAIL %s: size %d != %d\n", what, k, n_expect); failures++; return; }
    for (int i = 0; i < k; i++)
        if (got[i] != expect[i]) { std::printf("FAIL %s: order %d (%u != %u)\n", what, i, got[i], expect[i]); failures++; return; }
    checks++;
    if (*(uint64_t*)(arena + 0x38) != (uint64_t)n_expect) {
        std::printf("FAIL %s: count %llu\n", what, (unsigned long long)*(uint64_t*)(arena + 0x38)); failures++; return; }
    checks++;
    if (!is_nil(root, g_mark) && !B(root, g_colour)) { std::printf("FAIL %s: red root\n", what); failures++; return; }
    checks++;
    if (!no_red_red(root, g_mark, g_colour)) { std::printf("FAIL %s: red-red\n", what); failures++; return; }
    checks++;
    if (black_height(root, g_mark, g_colour) < 0) { std::printf("FAIL %s: black height\n", what); failures++; return; }
}

static void run_14172ae00() {
    const unsigned mark = 0x1d, colour = mark - 1;
    g_fnLIFT_1417293c0 = &Tramp<SynRbInsert_1417293c0>;
    g_fnRB_1417293c0_factory = Alloc; g_fnRB_1417293c0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14172ae00((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14172ae00 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14172ae00((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14172ae00 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14172afb0() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_141729790 = &Tramp<SynRbInsert_141729790>;
    g_fnRB_141729790_factory = Alloc; g_fnRB_141729790_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14172afb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14172afb0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14172afb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14172afb0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14172b6c0() {
    const unsigned mark = 0x49, colour = mark - 1;
    g_fnLIFT_141729ba0 = &Tramp<SynRbInsert_141729ba0>;
    g_fnRB_141729ba0_factory = Alloc; g_fnRB_141729ba0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14172b6c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14172b6c0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14172b6c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14172b6c0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14173cea0() {
    const unsigned mark = 0x21, colour = mark - 1;
    g_fnLIFT_14173c5c0 = &Tramp<SynRbInsert_14173c5c0>;
    g_fnRB_14173c5c0_factory = Alloc; g_fnRB_14173c5c0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14173cea0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14173cea0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14173cea0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14173cea0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14173ed60() {
    const unsigned mark = 0x61, colour = mark - 1;
    g_fnLIFT_14173e790 = &Tramp<SynRbInsert_14173e790>;
    g_fnRB_14173e790_factory = Alloc; g_fnRB_14173e790_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14173ed60((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14173ed60 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14173ed60((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14173ed60 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141749690() {
    const unsigned mark = 0x3d, colour = mark - 1;
    g_fnLIFT_1417483e0 = &Tramp<SynRbInsert_1417483e0>;
    g_fnRB_1417483e0_factory = Alloc; g_fnRB_1417483e0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141749690((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141749690 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141749690((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141749690 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141749a50() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_141748820 = &Tramp<SynRbInsert_141748820>;
    g_fnRB_141748820_factory = Alloc; g_fnRB_141748820_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141749a50((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141749a50 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141749a50((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141749a50 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14175d840() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_1417585d0 = &Tramp<SynRbInsert_1417585d0>;
    g_fnRB_1417585d0_factory = Alloc; g_fnRB_1417585d0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14175d840((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14175d840 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14175d840((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14175d840 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14175dd50() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_141758a10 = &Tramp<SynRbInsert_141758a10>;
    g_fnRB_141758a10_factory = Alloc; g_fnRB_141758a10_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14175dd50((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14175dd50 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14175dd50((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14175dd50 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417601b0() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_14175bfb0 = &Tramp<SynRbInsert_14175bfb0>;
    g_fnRB_14175bfb0_factory = Alloc; g_fnRB_14175bfb0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417601b0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417601b0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417601b0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417601b0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417607a0() {
    const unsigned mark = 0x59, colour = mark - 1;
    g_fnLIFT_14175c600 = &Tramp<SynRbInsert_14175c600>;
    g_fnRB_14175c600_factory = Alloc; g_fnRB_14175c600_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417607a0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417607a0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417607a0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417607a0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141760bc0() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_14175ca70 = &Tramp<SynRbInsert_14175ca70>;
    g_fnRB_14175ca70_factory = Alloc; g_fnRB_14175ca70_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141760bc0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141760bc0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141760bc0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141760bc0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141761330() {
    const unsigned mark = 0x2d, colour = mark - 1;
    g_fnLIFT_14175d350 = &Tramp<SynRbInsert_14175d350>;
    g_fnRB_14175d350_factory = Alloc; g_fnRB_14175d350_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141761330((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141761330 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141761330((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141761330 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141770ea0() {
    const unsigned mark = 0x61, colour = mark - 1;
    g_fnLIFT_141770600 = &Tramp<SynRbInsert_141770600>;
    g_fnRB_141770600_factory = Alloc; g_fnRB_141770600_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141770ea0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141770ea0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141770ea0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141770ea0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_141773cb0() {
    const unsigned mark = 0x61, colour = mark - 1;
    g_fnLIFT_141771050 = &Tramp<SynRbInsert_141771050>;
    g_fnRB_141771050_factory = Alloc; g_fnRB_141771050_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_141773cb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x141773cb0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_141773cb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x141773cb0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14177b650() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_14177af70 = &Tramp<SynRbInsert_14177af70>;
    g_fnRB_14177af70_factory = Alloc; g_fnRB_14177af70_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14177b650((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14177b650 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14177b650((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14177b650 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_14178cb80() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_14178ba80 = &Tramp<SynRbInsert_14178ba80>;
    g_fnRB_14178ba80_factory = Alloc; g_fnRB_14178ba80_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_14178cb80((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x14178cb80 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_14178cb80((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x14178cb80 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417970d0() {
    const unsigned mark = 0x21, colour = mark - 1;
    g_fnLIFT_141794e10 = &Tramp<SynRbInsert_141794e10>;
    g_fnRB_141794e10_factory = Alloc; g_fnRB_141794e10_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417970d0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417970d0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417970d0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417970d0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417995c0() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_141796d90 = &Tramp<SynRbInsert_141796d90>;
    g_fnRB_141796d90_factory = Alloc; g_fnRB_141796d90_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417995c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417995c0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417995c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417995c0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417a7fb0() {
    const unsigned mark = 0x29, colour = mark - 1;
    g_fnLIFT_1417a79e0 = &Tramp<SynRbInsert_1417a79e0>;
    g_fnRB_1417a79e0_factory = Alloc; g_fnRB_1417a79e0_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417a7fb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417a7fb0 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417a7fb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417a7fb0 dup %d", s);
        verify(what, expect, 7);
    }
}

static void run_1417cd520() {
    const unsigned mark = 0x21, colour = mark - 1;
    g_fnLIFT_1417cbb60 = &Tramp<SynRbInsert_1417cbb60>;
    g_fnRB_1417cbb60_factory = Alloc; g_fnRB_1417cbb60_throw = Throw;
    static const uint32_t suite[5][7] = {
        {40, 20, 60, 10, 30, 50, 70},
        {10, 20, 30, 40, 50, 60, 70},
        {70, 60, 50, 40, 30, 20, 10},
        {40, 10, 70, 20, 60, 30, 50},
        {50, 25, 75, 12, 37, 62, 87},
    };
    for (int s = 0; s < 5; s++) {
        reset(mark, colour);
        for (int i = 0; i < 7; i++) {
            uint32_t key = suite[s][i];
            SynLift_1417cd520((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        uint32_t expect[7];
        std::memcpy(expect, suite[s], sizeof expect);
        for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++)
            if (expect[j] < expect[i]) { uint32_t t = expect[i]; expect[i] = expect[j]; expect[j] = t; }
        char what[64];
        std::snprintf(what, sizeof what, "0x1417cd520 order %d", s);
        verify(what, expect, 7);
        for (int i = 0; i < 3; i++) {          // duplicates must not grow the tree
            uint32_t key = suite[s][i * 2];
            SynLift_1417cd520((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)outbuf,
                          (uint64_t)(uintptr_t)&key, (uint64_t)(uintptr_t)head);
        }
        std::snprintf(what, sizeof what, "0x1417cd520 dup %d", s);
        verify(what, expect, 7);
    }
}

int main() {
    g_fnLIFT_1418233c0 = [](uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) -> uint64_t { std::printf("INVALID PARAMETER\n"); failures++; return 0; };
    run_14172ae00();
    run_14172afb0();
    run_14172b6c0();
    run_14173cea0();
    run_14173ed60();
    run_141749690();
    run_141749a50();
    run_14175d840();
    run_14175dd50();
    run_1417601b0();
    run_1417607a0();
    run_141760bc0();
    run_141761330();
    run_141770ea0();
    run_141773cb0();
    run_14177b650();
    run_14178cb80();
    run_1417970d0();
    run_1417995c0();
    run_1417a7fb0();
    run_1417cd520();
    if (failures) { std::printf("INSERT-HINT_FAIL: %d failures after %d checks\n", failures, checks); return 1; }
    std::printf("INSERT-HINT_OK: %d checks\n", checks);
    return 0;
}
