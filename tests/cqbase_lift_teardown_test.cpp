// RB container teardown: destroy / clear / erase(first,last) for every map class, driven only through
// the ported bodies. The single stub is the node deallocator; its call count is asserted.
#include <cstdio>
#include <cstring>
#include <set>
#include "modules/syndicate/src/synlift.h"
#include "modules/syndicate/src/synlift_stage.h"

using namespace tq;
#define Q(p,o) (*(void**)((uint8_t*)(p)+(o)))
#define B(p,o) (*(uint8_t*)((uint8_t*)(p)+(o)))
#define D(p,o) (*(uint32_t*)((uint8_t*)(p)+(o)))

static unsigned char pool[4096][0x100];
static unsigned char arena[0x80];
static void* head_node;
static int checks, failures, deallocs;
static unsigned g_mark, g_colour;
static uint32_t g_key[7];
static void* g_node[7];

static uint64_t DeallocSeam(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) { deallocs++; return 0; }
static uint64_t Invalid(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) {
    std::printf("INVALID PARAMETER\n"); failures++; return 0;
}

template <uint64_t (*F)(uint64_t, uint64_t, uint64_t, uint64_t)>
static uint64_t Tramp(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t, uint64_t) { return F(a, b, c, d); }

static bool is_nil(void* n) { return B(n, g_mark) != 0; }
static void inorder(void* n, uint32_t* out, int* k) {
    if (is_nil(n)) return;
    inorder(Q(n, 0x00), out, k);
    out[(*k)++] = D(n, 0x18);
    inorder(Q(n, 0x10), out, k);
}
static int black_height(void* n) {
    if (is_nil(n)) return 1;
    int l = black_height(Q(n, 0x00)), r = black_height(Q(n, 0x10));
    if (l < 0 || r < 0 || l != r) return -1;
    return l + (B(n, g_colour) ? 1 : 0);
}
static bool no_red_red(void* n) {
    if (is_nil(n)) return true;
    if (!B(n, g_colour)) {
        if (!is_nil(Q(n, 0x00)) && !B(Q(n, 0x00), g_colour)) return false;
        if (!is_nil(Q(n, 0x10)) && !B(Q(n, 0x10), g_colour)) return false;
    }
    return no_red_red(Q(n, 0x00)) && no_red_red(Q(n, 0x10));
}

static const uint32_t kAll[7] = {10, 20, 30, 40, 50, 60, 70};
static void* node_of(uint32_t key) {
    for (int i = 0; i < 7; i++) if (g_key[i] == key) return g_node[i];
    return head_node;
}
static void MakeNode(void* n, uint32_t key, uint8_t colour) {
    std::memset(n, 0, 0x100);
    D(n, 0x18) = key; B(n, g_colour) = colour; B(n, g_mark) = 0;
}
// same shape as the erase battery: root black, two red children, black leaves
static void Build() {
    std::memset(pool, 0, sizeof pool);
    head_node = pool[4095];
    std::memset(head_node, 0, 0x100);
    B(head_node, g_mark) = 1; B(head_node, g_colour) = 1;
    Q(head_node, 0x00) = head_node; Q(head_node, 0x08) = head_node; Q(head_node, 0x10) = head_node;
    std::memset(arena, 0, sizeof arena);
    Q(arena, 0x00) = arena; Q(arena, 0x30) = head_node;
    void* n40 = pool[0]; void* n20 = pool[1]; void* n60 = pool[2];
    void* n10 = pool[3]; void* n30 = pool[4]; void* n50 = pool[5]; void* n70 = pool[6];
    MakeNode(n40, 40, 1); MakeNode(n20, 20, 0); MakeNode(n60, 60, 0);
    MakeNode(n10, 10, 1); MakeNode(n30, 30, 1); MakeNode(n50, 50, 1); MakeNode(n70, 70, 1);
    Q(n20, 0x00) = n10; Q(n20, 0x10) = n30; Q(n20, 0x08) = n40;
    Q(n60, 0x00) = n50; Q(n60, 0x10) = n70; Q(n60, 0x08) = n40;
    Q(n40, 0x00) = n20; Q(n40, 0x10) = n60; Q(n40, 0x08) = head_node;
    Q(n10, 0x00) = head_node; Q(n10, 0x10) = head_node; Q(n10, 0x08) = n20;
    Q(n30, 0x00) = head_node; Q(n30, 0x10) = head_node; Q(n30, 0x08) = n20;
    Q(n50, 0x00) = head_node; Q(n50, 0x10) = head_node; Q(n50, 0x08) = n60;
    Q(n70, 0x00) = head_node; Q(n70, 0x10) = head_node; Q(n70, 0x08) = n60;
    Q(head_node, 0x00) = n10; Q(head_node, 0x10) = n70; Q(head_node, 0x08) = n40;
    *(uint64_t*)(arena + 0x38) = 7;
    g_key[0] = 10; g_node[0] = n10; g_key[1] = 20; g_node[1] = n20; g_key[2] = 30; g_node[2] = n30;
    g_key[3] = 40; g_node[3] = n40; g_key[4] = 50; g_node[4] = n50; g_key[5] = 60; g_node[5] = n60;
    g_key[6] = 70; g_node[6] = n70;
    deallocs = 0;
}
static void check_tree(const char* what, const std::set<uint32_t>& want) {
    void* root = Q(head_node, 0x08);
    uint32_t got[16]; int k = 0;
    inorder(root, got, &k);
    checks++;
    if (k != (int)want.size()) { std::printf("FAIL %s: size %d != %zu\n", what, k, want.size()); failures++; return; }
    int i = 0;
    for (uint32_t w : want) {
        checks++;
        if (got[i++] != w) { std::printf("FAIL %s: order at %d\n", what, i - 1); failures++; return; }
    }
    checks++;
    if (*(uint64_t*)(arena + 0x38) != (uint64_t)want.size()) {
        std::printf("FAIL %s: count %llu != %zu\n", what, (unsigned long long)*(uint64_t*)(arena + 0x38), want.size()); failures++; return;
    }
    checks++;
    if (!is_nil(root) && !B(root, g_colour)) { std::printf("FAIL %s: red root\n", what); failures++; return; }
    checks++;
    if (!no_red_red(root)) { std::printf("FAIL %s: red-red\n", what); failures++; return; }
    checks++;
    if (black_height(root) < 0) { std::printf("FAIL %s: black height\n", what); failures++; return; }
    checks++;
    if (want.empty()) {
        if (Q(head_node, 0x00) != head_node || Q(head_node, 0x08) != head_node || Q(head_node, 0x10) != head_node) {
            std::printf("FAIL %s: head not self-linked after emptying\n", what); failures++; return;
        }
    } else {
        if (Q(head_node, 0x00) != node_of(*want.begin())) { std::printf("FAIL %s: begin link\n", what); failures++; return; }
        if (Q(head_node, 0x10) != node_of(*want.rbegin())) { std::printf("FAIL %s: end link\n", what); failures++; return; }
    }
}

static void run_14172a410() {
    std::printf("run %s\n", "14172a410");
    const unsigned mark = 0x1d; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141724ed0 = Tramp<SynLift_141724ed0>;
    g_fnLIFT_141726210 = Tramp<SynLift_141726210>;
    g_fnLIFT_141727640 = Tramp<SynLift_141727640>;
    g_fnLIFT_141728290 = Tramp<SynLift_141728290>;
    Build();
    SynLift_141727640((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14172a410 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14172a410 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14172a410((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14172a410 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14172a7c0() {
    std::printf("run %s\n", "14172a7c0");
    const unsigned mark = 0x1b; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141723a50 = Tramp<SynLift_141723a50>;
    g_fnLIFT_1417270a0 = Tramp<SynLift_1417270a0>;
    g_fnLIFT_141728750 = Tramp<SynLift_141728750>;
    g_fnLIFT_141728b10 = Tramp<SynLift_141728b10>;
    Build();
    SynLift_141728b10((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14172a7c0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14172a7c0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14172a7c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14172a7c0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14172d3c0() {
    std::printf("run %s\n", "14172d3c0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141722ef0 = Tramp<SynLift_141722ef0>;
    g_fnLIFT_1417262c0 = Tramp<SynLift_1417262c0>;
    g_fnLIFT_1417276c0 = Tramp<SynLift_1417276c0>;
    g_fnLIFT_14172b160 = Tramp<SynLift_14172b160>;
    Build();
    SynLift_1417276c0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14172d3c0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14172d3c0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14172d3c0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14172d3c0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14172d610() {
    std::printf("run %s\n", "14172d610");
    const unsigned mark = 0x49; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141723090 = Tramp<SynLift_141723090>;
    g_fnLIFT_141726310 = Tramp<SynLift_141726310>;
    g_fnLIFT_141727740 = Tramp<SynLift_141727740>;
    g_fnLIFT_14172b870 = Tramp<SynLift_14172b870>;
    Build();
    SynLift_141727740((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14172d610 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14172d610 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14172d610((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14172d610 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14172d810() {
    std::printf("run %s\n", "14172d810");
    const unsigned mark = 0x1d; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141722fc0 = Tramp<SynLift_141722fc0>;
    g_fnLIFT_141726360 = Tramp<SynLift_141726360>;
    g_fnLIFT_1417277c0 = Tramp<SynLift_1417277c0>;
    g_fnLIFT_14172bd00 = Tramp<SynLift_14172bd00>;
    Build();
    SynLift_1417277c0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14172d810 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14172d810 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14172d810((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14172d810 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14173cb90() {
    std::printf("run %s\n", "14173cb90");
    const unsigned mark = 0x21; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_14173b240 = Tramp<SynLift_14173b240>;
    g_fnLIFT_14173bc60 = Tramp<SynLift_14173bc60>;
    g_fnLIFT_14173c0b0 = Tramp<SynLift_14173c0b0>;
    g_fnLIFT_14173c470 = Tramp<SynLift_14173c470>;
    Build();
    SynLift_14173c470((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14173cb90 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14173cb90 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14173cb90((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14173cb90 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_1417481d0() {
    std::printf("run %s\n", "1417481d0");
    const unsigned mark = 0x3d; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141744cb0 = Tramp<SynLift_141744cb0>;
    g_fnLIFT_141746600 = Tramp<SynLift_141746600>;
    g_fnLIFT_1417471f0 = Tramp<SynLift_1417471f0>;
    g_fnLIFT_141747400 = Tramp<SynLift_141747400>;
    Build();
    SynLift_1417471f0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x1417481d0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x1417481d0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_1417481d0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x1417481d0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14174a150() {
    std::printf("run %s\n", "14174a150");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_1417447d0 = Tramp<SynLift_1417447d0>;
    g_fnLIFT_141746650 = Tramp<SynLift_141746650>;
    g_fnLIFT_141747270 = Tramp<SynLift_141747270>;
    g_fnLIFT_141749c00 = Tramp<SynLift_141749c00>;
    Build();
    SynLift_141747270((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14174a150 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14174a150 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14174a150((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14174a150 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175bda0() {
    std::printf("run %s\n", "14175bda0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141753470 = Tramp<SynLift_141753470>;
    g_fnLIFT_141755490 = Tramp<SynLift_141755490>;
    g_fnLIFT_141757580 = Tramp<SynLift_141757580>;
    g_fnLIFT_141758050 = Tramp<SynLift_141758050>;
    Build();
    SynLift_141757580((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175bda0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175bda0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175bda0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175bda0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175d690() {
    std::printf("run %s\n", "14175d690");
    const unsigned mark = 0x59; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_1417512f0 = Tramp<SynLift_1417512f0>;
    g_fnLIFT_1417555f0 = Tramp<SynLift_1417555f0>;
    g_fnLIFT_141757640 = Tramp<SynLift_141757640>;
    g_fnLIFT_1417591f0 = Tramp<SynLift_1417591f0>;
    Build();
    SynLift_141757640((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175d690 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175d690 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175d690((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175d690 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175d9f0() {
    std::printf("run %s\n", "14175d9f0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141754000 = Tramp<SynLift_141754000>;
    g_fnLIFT_141756920 = Tramp<SynLift_141756920>;
    g_fnLIFT_141759600 = Tramp<SynLift_141759600>;
    g_fnLIFT_1417599c0 = Tramp<SynLift_1417599c0>;
    Build();
    SynLift_1417599c0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175d9f0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175d9f0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175d9f0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175d9f0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175dba0() {
    std::printf("run %s\n", "14175dba0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141753620 = Tramp<SynLift_141753620>;
    g_fnLIFT_141755640 = Tramp<SynLift_141755640>;
    g_fnLIFT_1417576c0 = Tramp<SynLift_1417576c0>;
    g_fnLIFT_141759a90 = Tramp<SynLift_141759a90>;
    Build();
    SynLift_1417576c0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175dba0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175dba0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175dba0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175dba0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175df00() {
    std::printf("run %s\n", "14175df00");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141753d70 = Tramp<SynLift_141753d70>;
    g_fnLIFT_141755690 = Tramp<SynLift_141755690>;
    g_fnLIFT_141757740 = Tramp<SynLift_141757740>;
    g_fnLIFT_141759ef0 = Tramp<SynLift_141759ef0>;
    Build();
    SynLift_141757740((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175df00 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175df00 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175df00((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175df00 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175e0b0() {
    std::printf("run %s\n", "14175e0b0");
    const unsigned mark = 0x69; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141751380 = Tramp<SynLift_141751380>;
    g_fnLIFT_1417556e0 = Tramp<SynLift_1417556e0>;
    g_fnLIFT_1417577c0 = Tramp<SynLift_1417577c0>;
    g_fnLIFT_14175a300 = Tramp<SynLift_14175a300>;
    Build();
    SynLift_1417577c0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175e0b0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175e0b0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175e0b0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175e0b0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14175e410() {
    std::printf("run %s\n", "14175e410");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_1417536b0 = Tramp<SynLift_1417536b0>;
    g_fnLIFT_141755730 = Tramp<SynLift_141755730>;
    g_fnLIFT_141757840 = Tramp<SynLift_141757840>;
    g_fnLIFT_14175a710 = Tramp<SynLift_14175a710>;
    Build();
    SynLift_141757840((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14175e410 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14175e410 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14175e410((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14175e410 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_141762db0() {
    std::printf("run %s\n", "141762db0");
    const unsigned mark = 0x2d; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141750760 = Tramp<SynLift_141750760>;
    g_fnLIFT_1417540c0 = Tramp<SynLift_1417540c0>;
    g_fnLIFT_1417567f0 = Tramp<SynLift_1417567f0>;
    g_fnLIFT_1417614e0 = Tramp<SynLift_1417614e0>;
    Build();
    SynLift_1417567f0((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x141762db0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x141762db0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_141762db0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x141762db0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_141777350() {
    std::printf("run %s\n", "141777350");
    const unsigned mark = 0x39; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141776460 = Tramp<SynLift_141776460>;
    g_fnLIFT_1417767b0 = Tramp<SynLift_1417767b0>;
    g_fnLIFT_141776c90 = Tramp<SynLift_141776c90>;
    g_fnLIFT_141777050 = Tramp<SynLift_141777050>;
    Build();
    SynLift_141777050((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x141777350 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x141777350 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_141777350((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x141777350 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14177bcb0() {
    std::printf("run %s\n", "14177bcb0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_14177a5c0 = Tramp<SynLift_14177a5c0>;
    g_fnLIFT_14177aa60 = Tramp<SynLift_14177aa60>;
    g_fnLIFT_14177ac60 = Tramp<SynLift_14177ac60>;
    g_fnLIFT_14177b800 = Tramp<SynLift_14177b800>;
    Build();
    SynLift_14177ac60((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14177bcb0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14177bcb0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14177bcb0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14177bcb0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_14178b8b0() {
    std::printf("run %s\n", "14178b8b0");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141789d70 = Tramp<SynLift_141789d70>;
    g_fnLIFT_14178a650 = Tramp<SynLift_14178a650>;
    g_fnLIFT_14178ab70 = Tramp<SynLift_14178ab70>;
    g_fnLIFT_14178af30 = Tramp<SynLift_14178af30>;
    Build();
    SynLift_14178af30((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x14178b8b0 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x14178b8b0 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_14178b8b0((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x14178b8b0 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_141796b10() {
    std::printf("run %s\n", "141796b10");
    const unsigned mark = 0x21; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141790e10 = Tramp<SynLift_141790e10>;
    g_fnLIFT_141793630 = Tramp<SynLift_141793630>;
    g_fnLIFT_1417948b0 = Tramp<SynLift_1417948b0>;
    g_fnLIFT_141794c70 = Tramp<SynLift_141794c70>;
    Build();
    SynLift_141794c70((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x141796b10 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x141796b10 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_141796b10((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x141796b10 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_141797280() {
    std::printf("run %s\n", "141797280");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_141792240 = Tramp<SynLift_141792240>;
    g_fnLIFT_141793220 = Tramp<SynLift_141793220>;
    g_fnLIFT_141794280 = Tramp<SynLift_141794280>;
    g_fnLIFT_141795230 = Tramp<SynLift_141795230>;
    Build();
    SynLift_141794280((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x141797280 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x141797280 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_141797280((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x141797280 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

static void run_1417a8610() {
    std::printf("run %s\n", "1417a8610");
    const unsigned mark = 0x29; g_mark = mark; g_colour = mark - 1; g_fnLIFT_1417f2fdc = DeallocSeam;
    g_fnLIFT_1417a70b0 = Tramp<SynLift_1417a70b0>;
    g_fnLIFT_1417a75b0 = Tramp<SynLift_1417a75b0>;
    g_fnLIFT_1417a7780 = Tramp<SynLift_1417a7780>;
    g_fnLIFT_1417a8160 = Tramp<SynLift_1417a8160>;
    Build();
    SynLift_1417a7780((uint64_t)(uintptr_t)arena, 0, 0, 0);
    check_tree("0x1417a8610 clear", std::set<uint32_t>());
    checks++;
    if (deallocs != 7) { std::printf("FAIL 0x1417a8610 clear: %d deallocs\n", deallocs); failures++; }

#ifdef ERASE_RANGE_WIP
    static const uint32_t bounds[9][2] = {{10,10},{10,20},{10,40},{20,60},{40,70},{10,0},{60,70},{70,0},{30,30}};
    for (int s = 0; s < 9; s++) {
        Build();
        uint32_t fk = bounds[s][0], lk = bounds[s][1];
        uint8_t it1[16] = {0}, it2[16] = {0}, out[16] = {0};
        Q(it1, 0) = arena; Q(it1, 8) = fk ? node_of(fk) : head_node;
        Q(it2, 0) = arena; Q(it2, 8) = lk ? node_of(lk) : head_node;
        void* expect_node = lk ? node_of(lk) : head_node;
        SynLift_1417a8610((uint64_t)(uintptr_t)arena, (uint64_t)(uintptr_t)out,
                    (uint64_t)(uintptr_t)it1, (uint64_t)(uintptr_t)it2);
        std::set<uint32_t> want(kAll, kAll + 7);
        if (lk) want.erase(want.find(fk), want.find(lk)); else want.erase(want.find(fk), want.end());
        char what[64];
        std::snprintf(what, sizeof what, "0x1417a8610 erase [%u,%u)", fk, lk);
        check_tree(what, want);
        checks++;
        if (Q(out, 0) != arena) { std::printf("FAIL %s: out container\n", what); failures++; }
        checks++;
        if (Q(out, 8) != expect_node) { std::printf("FAIL %s: out node\n", what); failures++; }
        checks++;
        if (deallocs != 7 - (int)want.size()) {
            std::printf("FAIL %s: %d deallocs for %d erased\n", what, deallocs, 7 - (int)want.size()); failures++;
        }
    }
#endif
}

int main() {
    // any seam the ported bodies reach but nobody supplied counts as a failure
    g_fnLIFT_1417224f0 = Invalid;
    g_fnLIFT_141722680 = Invalid;
    g_fnLIFT_1417227e0 = Invalid;
    g_fnLIFT_141722ef0 = Invalid;
    g_fnLIFT_141722fc0 = Invalid;
    g_fnLIFT_141723090 = Invalid;
    g_fnLIFT_141723a50 = Invalid;
    g_fnLIFT_141724870 = Invalid;
    g_fnLIFT_141724950 = Invalid;
    g_fnLIFT_1417249e0 = Invalid;
    g_fnLIFT_141724c50 = Invalid;
    g_fnLIFT_141724cb0 = Invalid;
    g_fnLIFT_141724ed0 = Invalid;
    g_fnLIFT_141725000 = Invalid;
    g_fnLIFT_141725060 = Invalid;
    g_fnLIFT_141726210 = Invalid;
    g_fnLIFT_1417262c0 = Invalid;
    g_fnLIFT_141726310 = Invalid;
    g_fnLIFT_141726360 = Invalid;
    g_fnLIFT_1417270a0 = Invalid;
    g_fnLIFT_141727640 = Invalid;
    g_fnLIFT_1417276c0 = Invalid;
    g_fnLIFT_141727740 = Invalid;
    g_fnLIFT_1417277c0 = Invalid;
    g_fnLIFT_141728290 = Invalid;
    g_fnLIFT_141728750 = Invalid;
    g_fnLIFT_141728b10 = Invalid;
    g_fnLIFT_1417293c0 = Invalid;
    g_fnLIFT_141729790 = Invalid;
    g_fnLIFT_141729ba0 = Invalid;
    g_fnLIFT_14172b160 = Invalid;
    g_fnLIFT_14172b870 = Invalid;
    g_fnLIFT_14172bd00 = Invalid;
    g_fnLIFT_14173b0e0 = Invalid;
    g_fnLIFT_14173b140 = Invalid;
    g_fnLIFT_14173b240 = Invalid;
    g_fnLIFT_14173bc60 = Invalid;
    g_fnLIFT_14173c0b0 = Invalid;
    g_fnLIFT_14173c470 = Invalid;
    g_fnLIFT_14173c5c0 = Invalid;
    g_fnLIFT_14173e790 = Invalid;
    g_fnLIFT_141744560 = Invalid;
    g_fnLIFT_1417447d0 = Invalid;
    g_fnLIFT_141744cb0 = Invalid;
    g_fnLIFT_141745ad0 = Invalid;
    g_fnLIFT_141745c30 = Invalid;
    g_fnLIFT_141745c90 = Invalid;
    g_fnLIFT_141746600 = Invalid;
    g_fnLIFT_141746650 = Invalid;
    g_fnLIFT_1417471f0 = Invalid;
    g_fnLIFT_141747270 = Invalid;
    g_fnLIFT_141747400 = Invalid;
    g_fnLIFT_1417483e0 = Invalid;
    g_fnLIFT_141748820 = Invalid;
    g_fnLIFT_141749c00 = Invalid;
    g_fnLIFT_14174fe10 = Invalid;
    g_fnLIFT_141750760 = Invalid;
    g_fnLIFT_141750a30 = Invalid;
    g_fnLIFT_1417512f0 = Invalid;
    g_fnLIFT_141751380 = Invalid;
    g_fnLIFT_141752ac0 = Invalid;
    g_fnLIFT_141752cd0 = Invalid;
    g_fnLIFT_141752d30 = Invalid;
    g_fnLIFT_141752ef0 = Invalid;
    g_fnLIFT_141752f50 = Invalid;
    g_fnLIFT_1417530a0 = Invalid;
    g_fnLIFT_141753100 = Invalid;
    g_fnLIFT_141753320 = Invalid;
    g_fnLIFT_141753380 = Invalid;
    g_fnLIFT_141753470 = Invalid;
    g_fnLIFT_141753620 = Invalid;
    g_fnLIFT_1417536b0 = Invalid;
    g_fnLIFT_1417538f0 = Invalid;
    g_fnLIFT_141753ab0 = Invalid;
    g_fnLIFT_141753b10 = Invalid;
    g_fnLIFT_141753bf0 = Invalid;
    g_fnLIFT_141753c50 = Invalid;
    g_fnLIFT_141753d70 = Invalid;
    g_fnLIFT_141754000 = Invalid;
    g_fnLIFT_1417540c0 = Invalid;
    g_fnLIFT_141755490 = Invalid;
    g_fnLIFT_1417555f0 = Invalid;
    g_fnLIFT_141755640 = Invalid;
    g_fnLIFT_141755690 = Invalid;
    g_fnLIFT_1417556e0 = Invalid;
    g_fnLIFT_141755730 = Invalid;
    g_fnLIFT_1417567f0 = Invalid;
    g_fnLIFT_141756920 = Invalid;
    g_fnLIFT_141757580 = Invalid;
    g_fnLIFT_141757640 = Invalid;
    g_fnLIFT_1417576c0 = Invalid;
    g_fnLIFT_141757740 = Invalid;
    g_fnLIFT_1417577c0 = Invalid;
    g_fnLIFT_141757840 = Invalid;
    g_fnLIFT_141758050 = Invalid;
    g_fnLIFT_1417585d0 = Invalid;
    g_fnLIFT_141758a10 = Invalid;
    g_fnLIFT_1417591f0 = Invalid;
    g_fnLIFT_141759600 = Invalid;
    g_fnLIFT_1417599c0 = Invalid;
    g_fnLIFT_141759a90 = Invalid;
    g_fnLIFT_141759ef0 = Invalid;
    g_fnLIFT_14175a300 = Invalid;
    g_fnLIFT_14175a710 = Invalid;
    g_fnLIFT_14175bfb0 = Invalid;
    g_fnLIFT_14175c600 = Invalid;
    g_fnLIFT_14175ca70 = Invalid;
    g_fnLIFT_14175d350 = Invalid;
    g_fnLIFT_1417614e0 = Invalid;
    g_fnLIFT_141770600 = Invalid;
    g_fnLIFT_141771050 = Invalid;
    g_fnLIFT_141776070 = Invalid;
    g_fnLIFT_141776360 = Invalid;
    g_fnLIFT_141776460 = Invalid;
    g_fnLIFT_1417767b0 = Invalid;
    g_fnLIFT_141776c90 = Invalid;
    g_fnLIFT_141777050 = Invalid;
    g_fnLIFT_14177a460 = Invalid;
    g_fnLIFT_14177a5c0 = Invalid;
    g_fnLIFT_14177a860 = Invalid;
    g_fnLIFT_14177aa60 = Invalid;
    g_fnLIFT_14177ac60 = Invalid;
    g_fnLIFT_14177af70 = Invalid;
    g_fnLIFT_14177b800 = Invalid;
    g_fnLIFT_141789d70 = Invalid;
    g_fnLIFT_141789ea0 = Invalid;
    g_fnLIFT_141789f00 = Invalid;
    g_fnLIFT_14178a650 = Invalid;
    g_fnLIFT_14178ab70 = Invalid;
    g_fnLIFT_14178af30 = Invalid;
    g_fnLIFT_14178ba80 = Invalid;
    g_fnLIFT_141790ce0 = Invalid;
    g_fnLIFT_141790e10 = Invalid;
    g_fnLIFT_141792160 = Invalid;
    g_fnLIFT_1417921c0 = Invalid;
    g_fnLIFT_141792240 = Invalid;
    g_fnLIFT_1417923e0 = Invalid;
    g_fnLIFT_141793220 = Invalid;
    g_fnLIFT_141793630 = Invalid;
    g_fnLIFT_141794280 = Invalid;
    g_fnLIFT_1417948b0 = Invalid;
    g_fnLIFT_141794c70 = Invalid;
    g_fnLIFT_141794e10 = Invalid;
    g_fnLIFT_141795230 = Invalid;
    g_fnLIFT_141796d90 = Invalid;
    g_fnLIFT_1417a6f90 = Invalid;
    g_fnLIFT_1417a70b0 = Invalid;
    g_fnLIFT_1417a7320 = Invalid;
    g_fnLIFT_1417a75b0 = Invalid;
    g_fnLIFT_1417a7780 = Invalid;
    g_fnLIFT_1417a79e0 = Invalid;
    g_fnLIFT_1417a8160 = Invalid;
    g_fnLIFT_1417c9310 = Invalid;
    g_fnLIFT_1417cbb60 = Invalid;
    g_fnLIFT_1417f2fdc = Invalid;
    g_fnLIFT_1417f3154 = Invalid;
    g_fnLIFT_141823270 = Invalid;
    g_fnLIFT_141823288 = Invalid;
    g_fnLIFT_1418233c0 = Invalid;
    g_fnLIFT_1418233f8 = Invalid;
    // exception seams of the standard containers: unreachable on a well-formed tree
    g_fnLIFT_1417f3154 = [](uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) -> uint64_t {
        std::printf("UNEXPECTED THROW\n"); failures++; return 0; };
    g_fnLIFT_1418233f8 = [](uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) -> uint64_t {
        std::printf("UNEXPECTED EXCEPTION CTOR\n"); failures++; return 0; };
    run_14172a410();
    run_14172a7c0();
    run_14172d3c0();
    run_14172d610();
    run_14172d810();
    run_14173cb90();
    run_1417481d0();
    run_14174a150();
    run_14175bda0();
    run_14175d690();
    run_14175d9f0();
    run_14175dba0();
    run_14175df00();
    run_14175e0b0();
    run_14175e410();
    run_141762db0();
    run_141777350();
    run_14177bcb0();
    run_14178b8b0();
    run_141796b10();
    run_141797280();
    run_1417a8610();
    if (failures) { std::printf("TEARDOWN_FAIL: %d failures after %d checks\n", failures, checks); return 1; }
    std::printf("TEARDOWN_OK: %d checks\n", checks);
    return 0;
}
