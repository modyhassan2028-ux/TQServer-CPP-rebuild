// The erase battery for the lifted family: a hand-built red-black tree per node layout, then every element
// erased through the lifted body, with the invariants checked after each step. The rotation and successor
// helpers are the lifted ones, so the whole path is the original machine code, not a re-implementation.
#include "modules/syndicate/src/synlift.h"
#include "modules/syndicate/src/synthunks_it.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

#define Q(p, o) (*(void**)((uint8_t*)(p) + (o)))
#define B(p, o) (*(uint8_t*)((uint8_t*)(p) + (o)))
#define D(p, o) (*(uint32_t*)((uint8_t*)(p) + (o)))

static int g_c, g_n;
static void* g_head;
static void* g_this;
static int g_deleted;
static unsigned char g_pool[16][0x100];

static bool IsNil(void* p) { return p == nullptr || B(p, g_n) != 0; }
static uint64_t WDel(uint64_t, uint64_t, uint64_t, uint64_t) { ++g_deleted; return 0; }
static uint64_t WThrow(uint64_t, uint64_t, uint64_t, uint64_t) { std::printf("unexpected throw\n"); std::abort(); }
static int g_invalidParam;
static uint64_t WIat(uint64_t, uint64_t, uint64_t, uint64_t) { std::abort(); }
static uint64_t WInvalid(uint64_t, uint64_t, uint64_t, uint64_t) { ++g_invalidParam; return 0; }
static uint64_t WNext_141722ef0(uint64_t a, uint64_t, uint64_t, uint64_t) {
    SynIterNext_141722ef0(reinterpret_cast<void*>(a)); return 0;
}

static void Node(uint8_t* n, uint32_t key, int colour) {
    std::memset(n, 0, 0x100);
    D(n, 0x68) = key;   // the erase body never reads the key, so the harness keeps it clear of the colour and mark bytes
    B(n, g_c) = static_cast<uint8_t>(colour);
    B(n, g_n) = 0;
}

// root 40 black, children 20/60 red, grandchildren 10/30/50/70 black: a valid red-black tree
static void* Build() {
    uint8_t* k40 = g_pool[0]; uint8_t* k20 = g_pool[1]; uint8_t* k60 = g_pool[2];
    uint8_t* k10 = g_pool[3]; uint8_t* k30 = g_pool[4]; uint8_t* k50 = g_pool[5]; uint8_t* k70 = g_pool[6];
    Node(k40, 40, 1); Node(k20, 20, 0); Node(k60, 60, 0);
    Node(k10, 10, 1); Node(k30, 30, 1); Node(k50, 50, 1); Node(k70, 70, 1);
    Q(k20, 0x00) = k10; Q(k20, 0x10) = k30; Q(k20, 0x08) = k40;
    Q(k60, 0x00) = k50; Q(k60, 0x10) = k70; Q(k60, 0x08) = k40;
    Q(k40, 0x00) = k20; Q(k40, 0x10) = k60; Q(k40, 0x08) = g_head;
    Q(k10, 0x00) = g_head; Q(k10, 0x10) = g_head; Q(k10, 0x08) = k20;
    Q(k30, 0x00) = g_head; Q(k30, 0x10) = g_head; Q(k30, 0x08) = k20;
    Q(k50, 0x00) = g_head; Q(k50, 0x10) = g_head; Q(k50, 0x08) = k60;
    Q(k70, 0x00) = g_head; Q(k70, 0x10) = g_head; Q(k70, 0x08) = k60;
    Q(g_head, 0x00) = k10; Q(g_head, 0x10) = k70; Q(g_head, 0x08) = k40;
    *reinterpret_cast<uint64_t*>((uint8_t*)g_this + 0x38) = 7;
    return k40;
}

static void* Find(uint32_t key) {
    void* cur = Q(g_head, 0x08);
    while (!IsNil(cur)) {
        uint32_t k = D(cur, 0x68);
        if (key == k) return cur;
        cur = key < k ? Q(cur, 0x00) : Q(cur, 0x10);
    }
    return nullptr;
}

static int BlackHeight(void* n, int depth) {
    if (IsNil(n)) return depth + 1;
    if (B(n, g_c) == 0) {
        CHECK(B(Q(n, 0x00), g_c) == 1);
        CHECK(B(Q(n, 0x10), g_c) == 1);
    }
    if (!IsNil(Q(n, 0x00))) CHECK(Q(Q(n, 0x00), 0x08) == n);
    if (!IsNil(Q(n, 0x10))) CHECK(Q(Q(n, 0x10), 0x08) == n);
    int l = BlackHeight(Q(n, 0x00), depth + (B(n, g_c) ? 1 : 0));
    int r = BlackHeight(Q(n, 0x10), depth + (B(n, g_c) ? 1 : 0));
    CHECK(l == r);
    return l;
}

static void Inorder(void* n, std::vector<uint32_t>& out) {
    if (IsNil(n)) return;
    Inorder(Q(n, 0x00), out);
    out.push_back(D(n, 0x68));
    Inorder(Q(n, 0x10), out);
}

static void Verify(const std::vector<uint32_t>& expect) {
    void* root = Q(g_head, 0x08);
    if (!IsNil(root)) CHECK(B(root, g_c) == 1);
    std::vector<uint32_t> got;
    Inorder(root, got);
    CHECK(got == expect);
    CHECK(static_cast<uint64_t>(got.size()) == *reinterpret_cast<uint64_t*>((uint8_t*)g_this + 0x38));
    void* lo = root;
    while (!IsNil(lo) && !IsNil(Q(lo, 0x00))) lo = Q(lo, 0x00);
    void* hi = root;
    while (!IsNil(hi) && !IsNil(Q(hi, 0x10))) hi = Q(hi, 0x10);
    CHECK(Q(g_head, 0x00) == (IsNil(lo) ? g_head : lo));
    CHECK(Q(g_head, 0x10) == (IsNil(hi) ? g_head : hi));
    BlackHeight(root, 0);
}

typedef uint64_t (*EraseFn)(uint64_t, uint64_t, uint64_t, uint64_t);

static void RunBody(EraseFn fn, int colour, const char* name) {
    g_c = colour;                 // the harness must lay out the nodes the way this body expects them
    g_n = colour + 1;
    const uint32_t kOrder[] = {40, 20, 60, 10, 70, 30, 50};
    for (int pass = 0; pass < 2; ++pass) {
        unsigned char arena[0x60];
        std::memset(arena, 0, sizeof arena);
        for (auto& blk : g_pool) std::memset(blk, 0, 0x100);
        g_this = arena;
        g_head = g_pool[15];
        std::memset(g_head, 0, 0x100);
        B(g_head, g_n) = 1;
        B(g_head, g_c) = 1;
        Q(arena, 0x30) = g_head;
        g_deleted = 0;
        Build();
        std::vector<uint32_t> expect = {10, 20, 30, 40, 50, 60, 70};
        Verify(expect);
        for (int i = 0; i < 7; ++i) {
            uint32_t key = pass == 0 ? kOrder[i] : kOrder[6 - i];
            void* node = Find(key);
            CHECK(node != nullptr);
            struct { void* c; void* n; } out = {nullptr, nullptr};
            struct { void* c; void* n; } at = {g_this, node};
            if (node == nullptr) std::fprintf(stderr, "node null for key %u\n", key);
            fn(reinterpret_cast<uint64_t>(g_this), reinterpret_cast<uint64_t>(&out),
               reinterpret_cast<uint64_t>(&at), 0);
            for (size_t j = 0; j < expect.size(); ++j)
                if (expect[j] == key) { expect.erase(expect.begin() + j); break; }
            {
                std::vector<uint32_t> got;
                Inorder(Q(g_head, 0x08), got);
                if (got != expect) {
                    std::printf("  [%s pass%d key=%u] got:", name, pass, key);
                    for (uint32_t v : got) std::printf(" %u", v);
                    std::printf(" | expect:");
                    for (uint32_t v : expect) std::printf(" %u", v);
                    std::printf("\n");
                }
            }
            Verify(expect);
        }
        CHECK(Q(g_head, 0x08) == g_head);
        CHECK(*reinterpret_cast<uint64_t*>((uint8_t*)arena + 0x38) == 0);
        CHECK(g_deleted == 7);
    }
    (void)name;
}

int main() {
    g_fnLIFT_1417f2fdc = WDel;
    g_fnLIFT_1417f3154 = WThrow;
    g_fnLIFT_141823270 = WIat;
    g_fnLIFT_141823288 = WIat;
    g_fnLIFT_1418233f8 = WIat;
    g_fnLIFT_1418233c0 = WInvalid;

    // 0x14172b160: colour 0x28, nil 0x29; rotations 0x1417224f0 / 0x141724870, successor 0x141722ef0
    g_fnLIFT_1417224f0 = SynLift_1417224f0;
    g_fnLIFT_141724870 = SynLift_141724870;
    g_fnLIFT_141722ef0 = WNext_141722ef0;
    RunBody(SynLift_14172b160, 0x28, "0x14172b160");

    // 0x141728750: colour 0x1a, nil 0x1b; rotations 0x141725000 / 0x141725060, successor 0x141723a50
    g_fnLIFT_141725000 = SynLift_141725000;
    g_fnLIFT_141725060 = SynLift_141725060;
    g_fnLIFT_141723a50 = SynLift_141723a50;
    RunBody(SynLift_141728750, 0x1a, "0x141728750");

    std::printf(g_fails ? "ERASE-FAMILY-FAIL %d\n" : "ERASE-FAMILY_OK: %d checks\n", g_fails ? g_fails : g_checks);
    return g_fails ? 1 : 0;
}
