// Erase battery for the lifted 0x141728290: build a tree with the ported insert (0x141727e60), erase keys one
// by one through the lifted body, and after every step check the red-black invariants, the ordering, the head
// links and the element count.
#include "modules/syndicate/src/synlift.h"
#include "modules/syndicate/src/synrbinsert.h"
#include "modules/syndicate/src/synrbrace.h"
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

static const int kColour = 0x1c, kNil = 0x1d, kHead = 0x30, kCount = 0x38, kKey = 0x18;

static unsigned char g_pool[64][0x80];
static int g_used;
static int g_deleted;
static void* g_head;
static void* g_this;

static bool IsNil(void* p) { return p == nullptr || B(p, kNil) != 0; }

static void* HookFactory(void*, void* a2, void* a3, void* a4, const uint32_t* pKey, uint8_t bColour) {
    unsigned char* n = g_pool[g_used++];
    std::memset(n, 0xEE, 0x80);
    Q(n, 0x00) = a2; Q(n, 0x08) = a3; Q(n, 0x10) = a4;
    D(n, kKey) = *pKey;
    B(n, kColour) = bColour; B(n, kNil) = 0;
    return n;
}
static void HookDelete(void* p) { (void)p; ++g_deleted; }
static void HookThrow() { std::printf("unexpected throw\n"); std::abort(); }
static void HookIat() { std::abort(); }
static uint64_t WDel(uint64_t a, uint64_t, uint64_t, uint64_t) { HookDelete(reinterpret_cast<void*>(a)); return 0; }
static uint64_t WThrow(uint64_t, uint64_t, uint64_t, uint64_t) { HookThrow(); return 0; }
static uint64_t WIat(uint64_t, uint64_t, uint64_t, uint64_t) { HookIat(); return 0; }
static uint64_t HookNext(uint64_t a, uint64_t, uint64_t, uint64_t) {
    SynIterNext_141724ed0(reinterpret_cast<void*>(a));
    return 0;
}
static uint64_t HookRotL(uint64_t a, uint64_t b, uint64_t, uint64_t) {
    SynRotateLeft_141724c50(reinterpret_cast<void*>(a), reinterpret_cast<void*>(b));
    return 0;
}
static uint64_t HookRotR(uint64_t a, uint64_t b, uint64_t, uint64_t) {
    SynRotateRight_141724cb0(reinterpret_cast<void*>(a), reinterpret_cast<void*>(b));
    return 0;
}

static void Insert(uint32_t key) {
    void* head = Q(g_this, kHead);
    void* cur = Q(head, 0x08);
    void* parent = head;
    bool left = false;
    while (!IsNil(cur)) {
        uint32_t k = D(cur, kKey);
        if (key == k) return;
        parent = cur;
        if (key < k) { left = true; cur = Q(cur, 0x00); }
        else { left = false; cur = Q(cur, 0x10); }
    }
    struct { void* c; void* n; } it = {nullptr, nullptr};
    SynRbInsert_141727e60(g_this, &it, left ? 1 : 0, parent, &key);
}

static void* Find(uint32_t key) {
    void* cur = Q(Q(g_this, kHead), 0x08);
    while (!IsNil(cur)) {
        uint32_t k = D(cur, kKey);
        if (key == k) return cur;
        cur = key < k ? Q(cur, 0x00) : Q(cur, 0x10);
    }
    return nullptr;
}

static int BlackHeight(void* n, int depth) {
    if (IsNil(n)) return depth + 1;
    if (B(n, kColour) == 0) {
        CHECK(B(Q(n, 0x00), kColour) == 1);      // a red node never has a red child
        CHECK(B(Q(n, 0x10), kColour) == 1);
    }
    if (!IsNil(Q(n, 0x00))) CHECK(Q(Q(n, 0x00), 0x08) == n);
    if (!IsNil(Q(n, 0x10))) CHECK(Q(Q(n, 0x10), 0x08) == n);
    int l = BlackHeight(Q(n, 0x00), depth + (B(n, kColour) ? 1 : 0));
    int r = BlackHeight(Q(n, 0x10), depth + (B(n, kColour) ? 1 : 0));
    CHECK(l == r);
    return l;
}

static void Inorder(void* n, std::vector<uint32_t>& out) {
    if (IsNil(n)) return;
    Inorder(Q(n, 0x00), out);
    out.push_back(D(n, kKey));
    Inorder(Q(n, 0x10), out);
}

static void Verify(const std::vector<uint32_t>& expect) {
    void* head = Q(g_this, kHead);
    void* root = Q(head, 0x08);
    if (!IsNil(root)) CHECK(B(root, kColour) == 1);
    std::vector<uint32_t> got;
    Inorder(root, got);
    CHECK(got == expect);
    CHECK(static_cast<uint64_t>(got.size()) == *reinterpret_cast<uint64_t*>((uint8_t*)g_this + kCount));
    void* lo = root;
    while (!IsNil(lo) && !IsNil(Q(lo, 0x00))) lo = Q(lo, 0x00);
    void* hi = root;
    while (!IsNil(hi) && !IsNil(Q(hi, 0x10))) hi = Q(hi, 0x10);
    CHECK(Q(head, 0x00) == (IsNil(lo) ? head : lo));
    CHECK(Q(head, 0x10) == (IsNil(hi) ? head : hi));
    BlackHeight(root, 0);
    for (size_t i = 1; i < got.size(); ++i) CHECK(got[i - 1] < got[i]);
}

int main() {
    g_fnRB_141726e10 = HookFactory;
    g_fnRB_1417f3154 = HookThrow;
    g_fnLIFT_141724c50 = HookRotL;
    g_fnLIFT_141724cb0 = HookRotR;
    g_fnLIFT_141724ed0 = HookNext;
    g_fnLIFT_1417f2fdc = WDel;
    g_fnLIFT_1417f3154 = WThrow;
    g_fnLIFT_141823270 = WIat;
    g_fnLIFT_141823288 = WIat;
    g_fnLIFT_1418233f8 = WIat;

    const uint32_t kKeys[] = {50, 30, 70, 20, 40, 60, 80, 10, 45, 65, 90, 5, 55};
    const int n = static_cast<int>(sizeof(kKeys) / sizeof(kKeys[0]));

    // erase in insertion order, in reverse, and from the middle outwards
    const int orders[3][2] = {{0, 1}, {1, -1}, {-1, 2}};
    for (int o = 0; o < 3; ++o) {
        unsigned char arena[0x60];
        std::memset(arena, 0, sizeof arena);
        g_this = arena;
        g_head = g_pool[63];
        std::memset(g_head, 0, 0x80);
        B(g_head, kNil) = 1;
        B(g_head, kColour) = 1;
        Q(g_head, 0x00) = g_head;
        Q(g_head, 0x10) = g_head;
        Q(g_head, 0x08) = g_head;
        Q(arena, kHead) = g_head;
        *reinterpret_cast<uint64_t*>((uint8_t*)arena + kCount) = 0;
        g_used = 0;
        g_deleted = 0;

        for (int i = 0; i < n; ++i) Insert(kKeys[i]);
        std::vector<uint32_t> expect(kKeys, kKeys + n);
        for (size_t i = 1; i < expect.size(); ++i)
            for (size_t j = i; j > 0 && expect[j - 1] > expect[j]; --j) std::swap(expect[j - 1], expect[j]);
        Verify(expect);

        int pos = (orders[o][0] == 0) ? 0 : (orders[o][0] == 1 ? n - 1 : n / 2);
        for (int step = 0; step < n; ++step) {
            uint32_t key = kKeys[pos];
            void* node = Find(key);
            CHECK(node != nullptr);
            // arg3 is an iterator holder {container, node}: the erased element is holder->f08, and the body
            // throws when it is the sentinel (erasing end()).
            struct { void* c; void* n; } it = {nullptr, nullptr};
            struct { void* c; void* n; } at = {g_this, node};
            SynLift_141728290(reinterpret_cast<uint64_t>(g_this), reinterpret_cast<uint64_t>(&it),
                              reinterpret_cast<uint64_t>(&at), 0);
            for (size_t i = 0; i < expect.size(); ++i) {
                if (expect[i] == key) { expect.erase(expect.begin() + i); break; }
            }
            Verify(expect);
            pos += orders[o][1] > 0 ? 1 : (orders[o][1] < 0 ? -1 : -1);
            if (pos >= n) pos = 0;
            if (pos < 0) pos = n - 1;
        }
        CHECK(Q(g_head, 0x08) == g_head);
        CHECK(*reinterpret_cast<uint64_t*>((uint8_t*)arena + kCount) == 0);
    }
    std::printf(g_fails ? "ERASE-FAIL %d\n" : "ERASE_OK: %d checks\n", g_fails ? g_fails : g_checks);
    return g_fails ? 1 : 0;
}
