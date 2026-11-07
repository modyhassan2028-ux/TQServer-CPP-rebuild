// Exercises the transcription of 0x141727e60 (ordered-tree insert + rebalance).
//
// The test builds a real tree the way the original caller does: search for the position, then call the routine
// with (parent, insert_left). After every insert it checks the red-black invariants, the ordering, the head
// sentinel links and the element count, so a wrong rotation or a wrong colour flip fails immediately.
#include "synrbinsert.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace tq;

static int g_checks = 0;
static int g_fails = 0;

#define CHECK(cond) do { ++g_checks; if (!(cond)) { ++g_fails; \
    std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #cond); } } while (0)

static unsigned char g_pool[64][0x30];
static int g_poolUsed = 0;

static void* HookFactory(void* a1, void* a2, void* a3, void* a4, const uint32_t* pKey, uint8_t bColour) {
    (void)a1;
    if (g_poolUsed >= 64) return nullptr;
    unsigned char* n = g_pool[g_poolUsed++];
    std::memset(n, 0xEE, 0x30);
    *(void**)(n + 0x00) = a2;
    *(void**)(n + 0x08) = a3;
    *(void**)(n + 0x10) = a4;
    *(uint32_t*)(n + 0x18) = *pKey;
    *(uint8_t*)(n + 0x1c) = bColour;
    *(uint8_t*)(n + 0x1d) = 0;
    return n;
}

static void HookThrow(void) {
    std::printf("unexpected throw seam reached\n");
    std::abort();
}

static inline void* Q(void* p, int off) { return *(void**)((unsigned char*)p + off); }
static inline void  S(void* p, int off, void* v) { *(void**)((unsigned char*)p + off) = v; }
static inline unsigned char B(void* p, int off) { return *(unsigned char*)((unsigned char*)p + off); }
static inline int IsNil(void* n) { return B(n, 0x1d) != 0; }
static inline uint32_t Key(void* n) { return *(uint32_t*)((unsigned char*)n + 0x18); }
static inline int IsRed(void* n) { return B(n, 0x1c) == 0; }

struct Iter { void* f00; void* f08; };

static void* Insert(unsigned char* pDb, uint32_t key) {
    void* head = Q(pDb, 0x30);
    void* root = Q(head, 0x08);
    void* parent = head;
    int left = 0;
    if (root != nullptr && !IsNil(root)) {
        void* cur = root;
        for (;;) {
            uint32_t k = Key(cur);
            if (key < k) {
                void* c = Q(cur, 0x00);
                if (IsNil(c)) { parent = cur; left = 1; break; }
                cur = c;
            } else if (k < key) {
                void* c = Q(cur, 0x10);
                if (IsNil(c)) { parent = cur; left = 0; break; }
                cur = c;
            } else {
                return cur;                       // duplicate: map::insert does not call the routine
            }
        }
    }
    Iter it = { nullptr, nullptr };
    static uint32_t sKey;
    sKey = key;
    void* r = SynRbInsert_141727e60(pDb, &it, (uint8_t)left, parent, &sKey);
    CHECK(r == (void*)&it);                        // insn 212 returns rbp
    CHECK(it.f00 == Q(pDb, 0x00));                 // insn 211: out->f00 = this->f00
    CHECK(it.f08 != nullptr);                      // insn 209: out->f08 = the new node
    return it.f08;
}

static int BlackHeight(void* node, void* nil) {
    if (IsNil(node)) {
        CHECK(node == nil);
        return 1;
    }
    if (IsRed(node)) {
        CHECK(!IsRed(Q(node, 0x00)));
        CHECK(!IsRed(Q(node, 0x10)));
    }
    int l = BlackHeight(Q(node, 0x00), nil);
    int r = BlackHeight(Q(node, 0x10), nil);
    CHECK(l == r);
    // a nil child points at the head sentinel, whose parent is the root, so only real children are checked
    if (!IsNil(Q(node, 0x00))) CHECK(Q(Q(node, 0x00), 0x08) == node);
    if (!IsNil(Q(node, 0x10))) CHECK(Q(Q(node, 0x10), 0x08) == node);
    return l + (IsRed(node) ? 0 : 1);
}

static void InOrder(void* node, void* nil, std::vector<uint32_t>& out) {
    if (IsNil(node)) return;
    InOrder(Q(node, 0x00), nil, out);
    out.push_back(Key(node));
    InOrder(Q(node, 0x10), nil, out);
}

static void* Leftmost(void* node, void* nil) {
    while (!IsNil(Q(node, 0x00))) node = Q(node, 0x00);
    return node;
}
static void* Rightmost(void* node, void* nil) {
    while (!IsNil(Q(node, 0x10))) node = Q(node, 0x10);
    return node;
}

int main(void) {
    g_fnRB_141726e10 = HookFactory;
    g_fnRB_1417f3154 = HookThrow;

    unsigned char db[0x40];
    unsigned char headNode[0x30];
    std::memset(db, 0, sizeof(db));
    std::memset(headNode, 0, sizeof(headNode));
    *(uint8_t*)(headNode + 0x1c) = 1;              // the sentinel is black
    *(uint8_t*)(headNode + 0x1d) = 1;              // and it is the nil mark
    S(headNode, 0x00, headNode);
    S(headNode, 0x08, nullptr);
    S(headNode, 0x10, headNode);
    S(db, 0x30, headNode);
    *(uint64_t*)(db + 0x38) = 0;

    // 50/30/70/20/40/60/80 then 10 (left-left), 45 (left-right), 65 (right-left), 90 (right-right):
    // between them they force the red-uncle recolour and all four rotation cases.
    const uint32_t keys[] = { 50, 30, 70, 20, 40, 60, 80, 10, 45, 65, 90 };
    const int nKeys = (int)(sizeof(keys) / sizeof(keys[0]));

    std::vector<uint32_t> inserted;
    for (int i = 0; i < nKeys; ++i) {
        void* node = Insert(db, keys[i]);
        CHECK(node != nullptr);
        CHECK(Key(node) == keys[i]);
        inserted.push_back(keys[i]);

        CHECK(*(uint64_t*)(db + 0x38) == (uint64_t)inserted.size());   // insn 37
        void* root = Q(headNode, 0x08);
        CHECK(root != nullptr);
        CHECK(!IsRed(root));                                            // insn 206-208
        (void)BlackHeight(root, headNode);
        CHECK(Q(headNode, 0x00) == Leftmost(root, headNode));           // insn 53 / 59
        CHECK(Q(headNode, 0x10) == Rightmost(root, headNode));

        std::vector<uint32_t> order;
        InOrder(root, headNode, order);
        std::vector<uint32_t> sorted = inserted;
        for (size_t a = 0; a + 1 < sorted.size(); ++a)
            for (size_t b = a + 1; b < sorted.size(); ++b)
                if (sorted[b] < sorted[a]) { uint32_t t = sorted[a]; sorted[a] = sorted[b]; sorted[b] = t; }
        CHECK(order == sorted);
    }

    // a duplicate must not reach the routine at all
    CHECK(Insert(db, 50) != nullptr);
    CHECK(*(uint64_t*)(db + 0x38) == (uint64_t)nKeys);

    std::printf("RB_OK: %d inserts, %d checks\n", nKeys, g_checks);
    return g_fails != 0;
}
