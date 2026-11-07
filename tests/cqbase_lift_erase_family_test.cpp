// The erase battery for the lifted family: a hand-built red-black tree per node layout, then every element
// erased through the lifted body, with the invariants checked after each step. The rotation and successor
// helpers are the lifted ones, so the whole path is the original machine code, not a re-implementation.
#include "modules/syndicate/src/synlift.h"
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
static uint64_t WDel(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) { ++g_deleted; return 0; }
static uint64_t WThrow(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) { std::printf("unexpected throw\n"); std::abort(); }
static int g_invalidParam;
static uint64_t WIat(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) { std::abort(); }
static uint64_t WInvalid(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) { ++g_invalidParam; return 0; }

static void Node(uint8_t* n, uint32_t key, int colour) {
    std::memset(n, 0, 0x100);
    D(n, 0x90) = key;   // the erase body never reads the key, so the harness keeps it clear of the colour and mark bytes
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
        uint32_t k = D(cur, 0x90);
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
    out.push_back(D(n, 0x90));
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
            if (node == nullptr) { std::fprintf(stderr, "[%s] node null for key %u\n", name, key); continue; }
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

static uint64_t W_141724ed0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141724ed0(a, b, c, d); }
static uint64_t W_141724c50(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141724c50(a, b, c, d); }
static uint64_t W_141724cb0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141724cb0(a, b, c, d); }
static uint64_t W_141723a50(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141723a50(a, b, c, d); }
static uint64_t W_141725000(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141725000(a, b, c, d); }
static uint64_t W_141725060(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141725060(a, b, c, d); }
static uint64_t W_141722ef0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141722ef0(a, b, c, d); }
static uint64_t W_1417224f0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417224f0(a, b, c, d); }
static uint64_t W_141724870(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141724870(a, b, c, d); }
static uint64_t W_141723090(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141723090(a, b, c, d); }
static uint64_t W_141722680(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141722680(a, b, c, d); }
static uint64_t W_141724950(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141724950(a, b, c, d); }
static uint64_t W_141722fc0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141722fc0(a, b, c, d); }
static uint64_t W_1417227e0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417227e0(a, b, c, d); }
static uint64_t W_1417249e0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417249e0(a, b, c, d); }
static uint64_t W_14173b240(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14173b240(a, b, c, d); }
static uint64_t W_14173b0e0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14173b0e0(a, b, c, d); }
static uint64_t W_14173b140(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14173b140(a, b, c, d); }
static uint64_t W_141744cb0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141744cb0(a, b, c, d); }
static uint64_t W_141745c30(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141745c30(a, b, c, d); }
static uint64_t W_141745c90(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141745c90(a, b, c, d); }
static uint64_t W_1417447d0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417447d0(a, b, c, d); }
static uint64_t W_141744560(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141744560(a, b, c, d); }
static uint64_t W_141745ad0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141745ad0(a, b, c, d); }
static uint64_t W_141753470(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753470(a, b, c, d); }
static uint64_t W_141752cd0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141752cd0(a, b, c, d); }
static uint64_t W_141752d30(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141752d30(a, b, c, d); }
static uint64_t W_1417512f0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417512f0(a, b, c, d); }
static uint64_t W_141752ef0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141752ef0(a, b, c, d); }
static uint64_t W_141752f50(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141752f50(a, b, c, d); }
static uint64_t W_141754000(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141754000(a, b, c, d); }
static uint64_t W_141750a30(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141750a30(a, b, c, d); }
static uint64_t W_1417538f0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417538f0(a, b, c, d); }
static uint64_t W_141753620(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753620(a, b, c, d); }
static uint64_t W_1417530a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417530a0(a, b, c, d); }
static uint64_t W_141753100(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753100(a, b, c, d); }
static uint64_t W_141753d70(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753d70(a, b, c, d); }
static uint64_t W_141753ab0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753ab0(a, b, c, d); }
static uint64_t W_141753b10(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753b10(a, b, c, d); }
static uint64_t W_141751380(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141751380(a, b, c, d); }
static uint64_t W_141753320(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753320(a, b, c, d); }
static uint64_t W_141753380(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753380(a, b, c, d); }
static uint64_t W_1417536b0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417536b0(a, b, c, d); }
static uint64_t W_141753bf0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753bf0(a, b, c, d); }
static uint64_t W_141753c50(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141753c50(a, b, c, d); }
static uint64_t W_141750760(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141750760(a, b, c, d); }
static uint64_t W_14174fe10(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14174fe10(a, b, c, d); }
static uint64_t W_141752ac0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141752ac0(a, b, c, d); }
static uint64_t W_141776460(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141776460(a, b, c, d); }
static uint64_t W_141776070(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141776070(a, b, c, d); }
static uint64_t W_141776360(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141776360(a, b, c, d); }
static uint64_t W_14177a5c0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14177a5c0(a, b, c, d); }
static uint64_t W_14177a460(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14177a460(a, b, c, d); }
static uint64_t W_14177a860(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_14177a860(a, b, c, d); }
static uint64_t W_141789d70(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141789d70(a, b, c, d); }
static uint64_t W_141789ea0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141789ea0(a, b, c, d); }
static uint64_t W_141789f00(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141789f00(a, b, c, d); }
static uint64_t W_141790e10(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141790e10(a, b, c, d); }
static uint64_t W_141790ce0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141790ce0(a, b, c, d); }
static uint64_t W_1417923e0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417923e0(a, b, c, d); }
static uint64_t W_141792240(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141792240(a, b, c, d); }
static uint64_t W_141792160(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_141792160(a, b, c, d); }
static uint64_t W_1417921c0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417921c0(a, b, c, d); }
static uint64_t W_1417a70b0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417a70b0(a, b, c, d); }
static uint64_t W_1417a6f90(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417a6f90(a, b, c, d); }
static uint64_t W_1417a7320(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return SynLift_1417a7320(a, b, c, d); }

int main() {
    g_fnLIFT_1417f2fdc = WDel;
    g_fnLIFT_1417f3154 = WThrow;
    g_fnLIFT_141823270 = WIat; g_fnLIFT_141823288 = WIat; g_fnLIFT_1418233f8 = WIat;
    g_fnLIFT_1418233c0 = WInvalid;

    g_fnLIFT_141724ed0 = W_141724ed0;   // successor
    g_fnLIFT_141724c50 = W_141724c50;
    g_fnLIFT_141724cb0 = W_141724cb0;
    RunBody(SynLift_141728290, 0x1c, "0x141728290");

    g_fnLIFT_141723a50 = W_141723a50;   // successor
    g_fnLIFT_141725000 = W_141725000;
    g_fnLIFT_141725060 = W_141725060;
    RunBody(SynLift_141728750, 0x1a, "0x141728750");

    g_fnLIFT_141722ef0 = W_141722ef0;   // successor
    g_fnLIFT_1417224f0 = W_1417224f0;
    g_fnLIFT_141724870 = W_141724870;
    RunBody(SynLift_14172b160, 0x28, "0x14172b160");

    g_fnLIFT_141723090 = W_141723090;   // successor
    g_fnLIFT_141722680 = W_141722680;
    g_fnLIFT_141724950 = W_141724950;
    RunBody(SynLift_14172b870, 0x48, "0x14172b870");

    g_fnLIFT_141722fc0 = W_141722fc0;   // successor
    g_fnLIFT_1417227e0 = W_1417227e0;
    g_fnLIFT_1417249e0 = W_1417249e0;
    RunBody(SynLift_14172bd00, 0x1c, "0x14172bd00");

    g_fnLIFT_14173b240 = W_14173b240;   // successor
    g_fnLIFT_14173b0e0 = W_14173b0e0;
    g_fnLIFT_14173b140 = W_14173b140;
    RunBody(SynLift_14173c0b0, 0x20, "0x14173c0b0");

    g_fnLIFT_141744cb0 = W_141744cb0;   // successor
    g_fnLIFT_141745c30 = W_141745c30;
    g_fnLIFT_141745c90 = W_141745c90;
    RunBody(SynLift_141747400, 0x3c, "0x141747400");

    g_fnLIFT_1417447d0 = W_1417447d0;   // successor
    g_fnLIFT_141744560 = W_141744560;
    g_fnLIFT_141745ad0 = W_141745ad0;
    RunBody(SynLift_141749c00, 0x28, "0x141749c00");

    g_fnLIFT_141753470 = W_141753470;   // successor
    g_fnLIFT_141752cd0 = W_141752cd0;
    g_fnLIFT_141752d30 = W_141752d30;
    RunBody(SynLift_141758050, 0x28, "0x141758050");

    g_fnLIFT_1417512f0 = W_1417512f0;   // successor
    g_fnLIFT_141752ef0 = W_141752ef0;
    g_fnLIFT_141752f50 = W_141752f50;
    RunBody(SynLift_1417591f0, 0x58, "0x1417591f0");

    g_fnLIFT_141754000 = W_141754000;   // successor
    g_fnLIFT_141750a30 = W_141750a30;
    g_fnLIFT_1417538f0 = W_1417538f0;
    RunBody(SynLift_141759600, 0x28, "0x141759600");

    g_fnLIFT_141753620 = W_141753620;   // successor
    g_fnLIFT_1417530a0 = W_1417530a0;
    g_fnLIFT_141753100 = W_141753100;
    RunBody(SynLift_141759a90, 0x28, "0x141759a90");

    g_fnLIFT_141753d70 = W_141753d70;   // successor
    g_fnLIFT_141753ab0 = W_141753ab0;
    g_fnLIFT_141753b10 = W_141753b10;
    RunBody(SynLift_141759ef0, 0x28, "0x141759ef0");

    g_fnLIFT_141751380 = W_141751380;   // successor
    g_fnLIFT_141753320 = W_141753320;
    g_fnLIFT_141753380 = W_141753380;
    RunBody(SynLift_14175a300, 0x68, "0x14175a300");

    g_fnLIFT_1417536b0 = W_1417536b0;   // successor
    g_fnLIFT_141753bf0 = W_141753bf0;
    g_fnLIFT_141753c50 = W_141753c50;
    RunBody(SynLift_14175a710, 0x28, "0x14175a710");

    g_fnLIFT_141750760 = W_141750760;   // successor
    g_fnLIFT_14174fe10 = W_14174fe10;
    g_fnLIFT_141752ac0 = W_141752ac0;
    RunBody(SynLift_1417614e0, 0x2c, "0x1417614e0");

    g_fnLIFT_141776460 = W_141776460;   // successor
    g_fnLIFT_141776070 = W_141776070;
    g_fnLIFT_141776360 = W_141776360;
    RunBody(SynLift_141776c90, 0x38, "0x141776c90");

    g_fnLIFT_14177a5c0 = W_14177a5c0;   // successor
    g_fnLIFT_14177a460 = W_14177a460;
    g_fnLIFT_14177a860 = W_14177a860;
    RunBody(SynLift_14177b800, 0x28, "0x14177b800");

    g_fnLIFT_141789d70 = W_141789d70;   // successor
    g_fnLIFT_141789ea0 = W_141789ea0;
    g_fnLIFT_141789f00 = W_141789f00;
    RunBody(SynLift_14178ab70, 0x28, "0x14178ab70");

    g_fnLIFT_141790e10 = W_141790e10;   // successor
    g_fnLIFT_141790ce0 = W_141790ce0;
    g_fnLIFT_1417923e0 = W_1417923e0;
    RunBody(SynLift_1417948b0, 0x20, "0x1417948b0");

    g_fnLIFT_141792240 = W_141792240;   // successor
    g_fnLIFT_141792160 = W_141792160;
    g_fnLIFT_1417921c0 = W_1417921c0;
    RunBody(SynLift_141795230, 0x28, "0x141795230");

    g_fnLIFT_1417a70b0 = W_1417a70b0;   // successor
    g_fnLIFT_1417a6f90 = W_1417a6f90;
    g_fnLIFT_1417a7320 = W_1417a7320;
    RunBody(SynLift_1417a8160, 0x28, "0x1417a8160");

    std::printf("ERASE-FAMILY_OK: %d checks\n", g_checks);
    return g_fails ? 1 : 0;
}
