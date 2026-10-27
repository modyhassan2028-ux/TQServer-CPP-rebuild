// D88 tests: FUN_14179ba80 — lower_bound walk + sub-key insert.
#include "modules/syndicate/src/SyndicateMemberSubkeyAdd.h"
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
struct Node {
    void* left; void* parent; void* right; int key; char pad[0x45];
    Node() { memset(this, 0, sizeof(Node)); }
    bool nil() const { return *(char*)((char*)this + 0x61) != 0; }
    void setNil() { *(char*)((char*)this + 0x61) = 1; }
};
static Node s_nil;   // the shared nil sentinel
static Node s_head;  // the tree head
static Node s_a10, s_a20, s_a30;
static struct { Node* n10; Node* n20; Node* n30; } s_t = {&s_a10, &s_a20, &s_a30};
static char s_mgr[0x400];
static char s_proxy[8];
static char s_inner[0x40];
static int g_keyIn, g_subIn, g_invCount;
static uint64_t g_insertRet = 0x1234;
static struct { void* tree; uint32_t key; int n; } g_ins;
static uint64_t FakeKey88(void* m) { return (uint64_t)(uintptr_t)m; }
static uint64_t FakeSub88(void*) { return 0xABCD; }
static uint64_t FakeInsert88(void* tree, uint32_t* k) {
    g_ins.tree = tree; g_ins.key = *k; g_ins.n++;
    return g_insertRet;
}
static void FakeInvalid88() { g_invCount++; }
static void BuildTree() {
    memset(s_mgr, 0, sizeof(s_mgr));
    memset(s_inner, 0, sizeof(s_inner));
    memset(&s_head, 0, sizeof(s_head));
    memset(&s_nil, 0, sizeof(s_nil));
    s_nil.setNil();
    s_head.parent = nullptr; *(char*)((char*)&s_head + 0x61) = 0;
    memset(&s_a10, 0, sizeof(Node)); memset(&s_a20, 0, sizeof(Node));
    memset(&s_a30, 0, sizeof(Node));
    s_t.n10->key = 10; s_t.n20->key = 20; s_t.n30->key = 30;
    // root=20, left=10, right=30, children -> nil
    s_head.parent = s_t.n20;              // head[1] = root
    s_t.n20->left = s_t.n10; s_t.n20->right = s_t.n30;
    s_t.n10->left = &s_nil; s_t.n10->right = &s_nil;
    s_t.n30->left = &s_nil; s_t.n30->right = &s_nil;
    *(void**)(s_mgr + 0x390) = &s_head;
    *(void**)(s_mgr + 0x360) = s_proxy;
    *(void**)s_proxy = s_inner;
    *(uint64_t*)(s_inner + 0x30) = 0xdead; // never equals a node
}
static int g_fail = 0;
#define CHECK(c, msg) do { if (c) printf("  ok %s\n", msg); \
    else { printf("  FAIL %s\n", msg); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
int main() {
    syndicate::g_fnD88MemberKey = FakeKey88;
    syndicate::g_fnD88MemberSub = FakeSub88;
    syndicate::g_fnD88TreeInsert = FakeInsert88;
    syndicate::g_fnD88Invalid = FakeInvalid88;
    SECT("D88-1 null member");
    BuildTree();
    CHECK(syndicate::MemberSubkeyAdd88(s_mgr, nullptr) == 0, "null -> 0");
    CHECK(g_ins.n == 0, "null -> no insert");
    SECT("D88-2 exact key found (20)");
    BuildTree();
    g_ins.n = 0;
    uint64_t r = syndicate::MemberSubkeyAdd88(s_mgr, (void*)20);
    CHECK(g_ins.n == 1, "insert called once");
    CHECK(g_ins.key == 0xABCD, "sub-key passed");
    CHECK(g_ins.tree == (void*)((char*)s_t.n20 + 0x20), "target = node20+0x20");
    CHECK(r == 0x1201, "return (res&~0xff)|1 = 0x1201");
    SECT("D88-3 lower_bound semantics");
    BuildTree();
    g_ins.n = 0;
    r = syndicate::MemberSubkeyAdd88(s_mgr, (void*)30);   // deepest right
    CHECK(g_ins.n == 1 && g_ins.tree == (void*)((char*)s_t.n30 + 0x20),
          "key 30 found, node30+0x20");
    g_ins.n = 0;
    r = syndicate::MemberSubkeyAdd88(s_mgr, (void*)10);
    CHECK(g_ins.n == 1 && g_ins.tree == (void*)((char*)s_t.n10 + 0x20),
          "key 10 found, node10+0x20");
    SECT("D88-4 missing keys -> end iterator, no insert");
    BuildTree();
    g_ins.n = 0;
    r = syndicate::MemberSubkeyAdd88(s_mgr, (void*)25);   // 25 < cand 30
    CHECK(g_ins.n == 0, "25 not found, no insert");
    CHECK((r & 0xff) == 1, "still returns low byte 1 (RAW)");
    CHECK(r == ((uint64_t)(uintptr_t)&s_head & ~(uint64_t)0xff) | 1,
          "end path returns head-based value");
    g_ins.n = 0;
    syndicate::MemberSubkeyAdd88(s_mgr, (void*)5);         // 5 < cand 10
    CHECK(g_ins.n == 0, "5 not found, no insert");
    g_ins.n = 0;
    syndicate::MemberSubkeyAdd88(s_mgr, (void*)99);       // > all -> cand=head
    CHECK(g_ins.n == 0, "99 not found, no insert");
    SECT("D88-5 empty tree");
    BuildTree();
    s_head.parent = &s_nil;             // head->_Parent = nil -> not found
    g_ins.n = 0;
    r = syndicate::MemberSubkeyAdd88(s_mgr, (void*)20);
    CHECK(g_ins.n == 0 && (r & 1) == 1, "empty tree -> no insert, true");
    CHECK(g_invCount == 0, "no invalid calls in the happy paths");
    if (g_fail == 0) printf("D88-OK: 15 assertions\n");
    else printf("D88-FAIL\n");
    return g_fail ? 1 : 0;
}
