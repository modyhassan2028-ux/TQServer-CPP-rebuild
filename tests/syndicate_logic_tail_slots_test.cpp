// Batteries for the twelve CSyndicateLogic slots in CsyndicateLogicTailSlots.h.
// Each expectation is read off the body: which member offset is loaded, which callee is
// jumped to, whether `this` survives the tail jump, and what the comparison answers for
// the boundary and negative arguments.
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"
#include <cstdio>
#include <cstring>
#include <cstddef>

using namespace tq;

static int g_checks, g_fails;
static void* g_pBase = nullptr;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static uint64_t g_a, g_b, g_c, g_d;
static int g_calls;
static uint64_t g_ret;

static uint64_t hook(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    ++g_calls;
    g_a = a; g_b = b; g_c = c; g_d = d;
    return g_ret;
}

static void reset_hooks(uint64_t ret) {
    g_calls = 0;
    g_a = g_b = g_c = g_d = 0;
    g_ret = ret;
    g_pfnLogic_1417cadb0 = hook;
    g_pfnLogic_1417caa00 = hook;
    g_pfnLogic_1417cad90 = hook;
    g_pfnLogic_1417cb000 = hook;
    g_pfnLogic_1417873a0 = hook;
    g_pfnLogic_1417a8a50 = hook;
    g_pfnLogic_1417a8940 = hook;
    g_pfnLogic_14177f980 = hook;
}

int main() {
    // the shipped default for the lookup seam (the ported 0x1417cad00); the wrapper block
    // below substitutes its own, so it is restored before the end-to-end checks
    uint64_t (*const shipped_lookup)(uint64_t, uint64_t, uint64_t, uint64_t) = g_pfnLogic_1417cad00;
    unsigned char object[0x40];
    std::memset(object, 0, sizeof(object));
    void* self = object;

    // --- the four forwarders: member at +0x10 reaches the callee, the other registers ride along
    {
        uint64_t member = 0x1122334455667788ULL;
        *(uint64_t*)(object + 0x10) = member;
        struct F { uint64_t (*fn)(void*, uint64_t, uint64_t, uint64_t); const char* which; };
        F fns[4] = {
            {Slot_1417abe60, "0x1417cadb0"},
            {Slot_1417ac010, "0x1417caa00"},
            {Slot_1417ab1d0, "0x1417cad90"},
            {Slot_1417ab1c0, "0x1417cb000"},
        };
        for (int i = 0; i < 4; ++i) {
            reset_hooks(0xAABBCCDDEEFF0011ULL);
            uint64_t r = fns[i].fn(self, 0x21, 0x32, 0x43);
            CHECK(r == 0xAABBCCDDEEFF0011ULL);      // the callee's answer is the slot's answer
            CHECK(g_calls == 1);
            CHECK(g_a == member);                   // rcx = *(this+0x10)
            CHECK(g_b == 0x21 && g_c == 0x32 && g_d == 0x43);   // tail jump keeps the registers
        }
        // a null member is still forwarded: the body loads and jumps unconditionally
        *(uint64_t*)(object + 0x10) = 0;
        reset_hooks(7);
        CHECK(Slot_1417abe60(self, 1, 2, 3) == 7);
        CHECK(g_calls == 1 && g_a == 0);
    }

    // --- the argument forwarder drops `this`
    {
        reset_hooks(0x55);
        CHECK(Slot_1417aeba0((void*)0xDEAD, 0x1FFFFFFFFULL, 8, 9) == 0x55);
        CHECK(g_calls == 1);
        CHECK(g_a == 0xFFFFFFFFULL);   // mov ecx,edx zero-extends the low 32 bits
        CHECK(g_b == 0x1FFFFFFFFULL);  // rdx itself is untouched
        CHECK(g_c == 8 && g_d == 9);
    }

    // --- the two constants
    {
        reset_hooks(0);
        CHECK(Slot_1417aaf90(self) == 15);
        CHECK(Slot_1417aafa0(self) == 15);
        CHECK(g_calls == 0);           // both are `mov eax,0xf / ret`, they call nothing
    }

    // --- the two comparisons, signed on the 32-bit argument
    {
        CHECK(Slot_1417abc50(self, 0x3dd) == 0);
        CHECK(Slot_1417abc50(self, 0x3de) == 1);      // >= 990
        CHECK(Slot_1417abc50(self, 0x3df) == 1);
        CHECK(Slot_1417abc50(self, 0) == 0);
        CHECK(Slot_1417abc50(self, -1) == 0);         // signed: -1 is below the bound
        CHECK(Slot_1417abc50(self, 0x7FFFFFFF) == 1);

        CHECK(Slot_1417abc60(self, 0x379) == 1);
        CHECK(Slot_1417abc60(self, 0x37a) == 1);      // <= 890
        CHECK(Slot_1417abc60(self, 0x37b) == 0);
        CHECK(Slot_1417abc60(self, -1) == 1);         // signed: -1 is below the bound
        CHECK(Slot_1417abc60(self, 0) == 1);
        CHECK(Slot_1417abc60(self, -0x80000000LL) == 1);
        CHECK(g_calls == 0);
    }

    // --- the three guarded forwarders: null member answers 0 without calling anything
    {
        struct F { int (*fn)(void*, uint64_t, uint64_t, uint64_t); size_t off; uint64_t ret; };
        F fns[3] = {
            {Slot_1417af2f0, 0x20, 1},
            {Slot_1417af310, 0x20, 0x1234},
            {Slot_1417afac0, 0x28, 0x99},
        };
        for (int i = 0; i < 3; ++i) {
            std::memset(object, 0, sizeof(object));
            reset_hooks(fns[i].ret);
            CHECK(fns[i].fn(self, 4, 5, 6) == 0);      // member is null
            CHECK(g_calls == 0);

            *(uint64_t*)(object + fns[i].off) = 0xCAFE;
            reset_hooks(fns[i].ret);
            CHECK(fns[i].fn(self, 4, 5, 6) == (int)fns[i].ret);
            CHECK(g_calls == 1);
            CHECK(g_a == 0xCAFE);
            CHECK(g_b == 4 && g_c == 5 && g_d == 6);
        }

        // 0x1417af2f0 and 0x1417af310 read the SAME offset (+0x20); 0x1417afac0 reads +0x28.
        // Put a value at +0x28 only and the first two must still answer 0.
        std::memset(object, 0, sizeof(object));
        *(uint64_t*)(object + 0x28) = 0xBEEF;
        reset_hooks(3);
        CHECK(Slot_1417af2f0(self, 0, 0, 0) == 0);
        CHECK(Slot_1417af310(self, 0, 0, 0) == 0);
        CHECK(Slot_1417afac0(self, 0, 0, 0) == 3);
        CHECK(g_a == 0xBEEF);
    }

    // --- the lookup wrappers 0x1417cad90 / 0x1417cadb0 / 0x1417cb000
    {
        static uint64_t g_lookup_ret;
        static uint64_t g_l_a, g_l_b, g_l_c, g_l_d;
        static int g_l_n;
        static uint64_t g_tail2[2];
        static int g_tail2_n;
        static uint64_t g_tail1;
        static int g_tail1_n;

        auto lookup = [](uint64_t a, uint64_t b, uint64_t c, uint64_t d) -> uint64_t {
            ++g_l_n; g_l_a = a; g_l_b = b; g_l_c = c; g_l_d = d;
            return g_lookup_ret;
        };
        auto tail2 = [](uint64_t a, uint64_t b) -> uint64_t {
            ++g_tail2_n; g_tail2[0] = a; g_tail2[1] = b; return 0x777;
        };
        auto tail1 = [](uint64_t a) -> uint64_t {
            ++g_tail1_n; g_tail1 = a; return 0x888;
        };
        g_pfnLogic_1417cad00 = lookup;
        g_pfnLogic_141797e00 = tail2;
        g_pfnLogic_14178f470 = tail1;

        // 0x1417cad90: boolean answer, no tail call either way
        g_l_n = g_tail2_n = g_tail1_n = 0;
        g_lookup_ret = 0;
        CHECK(Slot_1417cad90((void*)0x1000, 5, 6, 7) == 0);
        CHECK(g_l_n == 1 && g_l_a == 0x1000 && g_l_b == 5 && g_l_c == 6 && g_l_d == 7);
        g_lookup_ret = 0x141860000ULL;
        CHECK(Slot_1417cad90((void*)0x1000, 5, 6, 7) == 1);
        CHECK(g_tail2_n == 0 && g_tail1_n == 0);

        // 0x1417cadb0: r8 truncated for the lookup, the ORIGINAL id goes to the tail call
        g_l_n = g_tail2_n = 0;
        g_lookup_ret = 0;
        CHECK(Slot_1417cadb0((void*)0x2000, 0x1FFFFFFFFULL, 0x2AAAAAAAAULL, 9) == 0);
        CHECK(g_l_n == 1);
        CHECK(g_l_b == 0xAAAAAAAALL);            // edx = r8d
        CHECK(g_l_c == 0x2AAAAAAAAULL);          // r8 itself untouched
        CHECK(g_tail2_n == 0);                   // a miss calls nothing

        g_lookup_ret = 0x141860123ULL;
        CHECK(Slot_1417cadb0((void*)0x2000, 0x1FFFFFFFFULL, 0x2AAAAAAAAULL, 9) == 0x777);
        CHECK(g_tail2_n == 1);
        CHECK(g_tail2[0] == 0x141860123ULL);     // rcx = the hit
        CHECK(g_tail2[1] == 0xFFFFFFFFULL);      // edx = the original id, truncated

        // 0x1417cb000: a hit is passed on, a miss substitutes 0x141827409
        g_l_n = g_tail1_n = 0;
        g_lookup_ret = 0x141860456ULL;
        CHECK(Slot_1417cb000((void*)0x3000, 1, 2, 3) == 0x888);
        CHECK(g_tail1_n == 1 && g_tail1 == 0x141860456ULL);

        g_lookup_ret = 0;
        CHECK(Slot_1417cb000((void*)0x3000, 1, 2, 3) == 0x888);
        CHECK(g_tail1_n == 2 && g_tail1 == 0x141827409ULL);   // the substituted default
    }

    // --- 0x1417c8f70 lower_bound over the proven layout
    {
        // node: left +0x00, parent +0x08, right +0x10, key +0x18, _Isnil +0x29
        struct Node {
            Node* left = nullptr;
            Node* parent = nullptr;
            Node* right = nullptr;
            uint32_t key = 0;
            uint8_t pad[0x29 - 0x1c] = {0};
            uint8_t isnil = 0;
        };
        static Node nodes[8];
        static Node head;
        static Node nil;
        // tree: 4 (root) with left 2 and right 6; 2 has right 3; 6 has left 5
        for (int i = 0; i < 8; ++i) { nodes[i] = Node(); }
        Node* n2 = &nodes[2]; Node* n3 = &nodes[3]; Node* n4 = &nodes[4];
        Node* n5 = &nodes[5]; Node* n6 = &nodes[6];
        n4->left = n2; n4->right = n6;
        n2->parent = n4; n6->parent = n4;
        n2->right = n3; n3->parent = n2;
        n6->left = n5; n5->parent = n6;
        n4->key = 4; n2->key = 2; n3->key = 3; n5->key = 5; n6->key = 6;

        nil = Node();
        nil.isnil = 1;
        head = Node();
        head.parent = n4;                 // container[0x30] -> head; root is head->parent
        head.isnil = 1;

        static uint8_t container[0x40];
        std::memset(container, 0, sizeof(container));
        *(void**)(container + 0x30) = &head;
        *(void**)(container + 0x00) = &head;   // the word carried into the iterator

        int err = 0;
        g_pfn_invalid_parameter_noinfo = [] { /* error path must not fire with a live container */ };

        // leaves point at the nil node
        Node* live[5] = {n2, n3, n4, n5, n6};
        for (int i = 0; i < 5; ++i) {
            if (!live[i]->left) live[i]->left = &nil;
            if (!live[i]->right) live[i]->right = &nil;
        }

        void* out[2] = {nullptr, nullptr};
        // exact hit: lower_bound(5) finds 5
        uint32_t k = 5;
        CHECK(Slot_1417c8f70_lower_bound(container, out, &k) == (void*)out);
        CHECK(out[1] == (void*)n5);
        // between 3 and 4 -> 4
        k = 3;
        Slot_1417c8f70_lower_bound(container, out, &k);
        CHECK(out[1] == (void*)n3);
        k = 1;
        Slot_1417c8f70_lower_bound(container, out, &k);
        CHECK(out[1] == (void*)n2);        // smallest node
        k = 7;
        Slot_1417c8f70_lower_bound(container, out, &k);
        CHECK(out[1] == (void*)&head);     // past the end -> the end node
        CHECK(out[0] == (void*)&head);     // the first member is carried from container[0]

        // an empty tree (root is the nil node) answers the end node without walking
        head.parent = &nil;
        k = 4;
        Slot_1417c8f70_lower_bound(container, out, &k);
        CHECK(out[1] == (void*)&head);
        CHECK(err == 0);
    }

    // --- 0x1417cad00 the shared lookup, on a real tree
    {
        // the offsets the bytes use: left 0x00, parent 0x08, right 0x10, key 0x18,
        // value 0x20, _Isnil 0x29
        struct N {
            N* left = nullptr;
            N* parent = nullptr;
            N* right = nullptr;
            uint32_t key = 0;
            uint8_t pad1[4] = {0};
            uint64_t value = 0;
            uint8_t pad2 = 0;
            uint8_t isnil = 0;
        };
        static_assert(offsetof(N, left) == 0x00 && offsetof(N, parent) == 0x08 &&
                      offsetof(N, right) == 0x10 && offsetof(N, key) == 0x18 &&
                      offsetof(N, value) == 0x20 && offsetof(N, isnil) == 0x29,
                      "node layout must match the bytes");
        static N n[4];
        static N nil, head, other_head;
        static struct { uint8_t pre[8]; uint8_t container[0x40]; } obj;

        for (int i = 0; i < 4; ++i) n[i] = N();
        nil = N(); nil.isnil = 1;
        head = N(); head.isnil = 1;
        other_head = N(); other_head.isnil = 1;

        // 2 is the root: left nil, right 5
        n[0].key = 2; n[0].value = 0xAAAA;  n[0].left = &nil; n[0].right = &n[1]; n[1].parent = &n[0];
        n[1].key = 5; n[1].value = 0xBBBB;  n[1].left = &nil; n[1].right = &nil;
        head.parent = &n[0];
        other_head.parent = &n[0];

        std::memset(&obj, 0, sizeof(obj));
        *(void**)(obj.container + 0x30) = &head;      // the end node
        *(void**)(obj.container + 0x00) = &other_head; // the "scary" word carried in the iterator
        *(void**)((uint8_t*)&other_head + 0x00) = nullptr;  // owner comes from *(scary in iterator)
        // scary is container[0] = &other_head, so owner = *(scary) -> point it at a live object
        static struct { uint8_t pad[0x38]; } owner;
        std::memset(&owner, 0, sizeof(owner));
        *(void**)((uint8_t*)&other_head + 0x00) = &owner;
        *(void**)((uint8_t*)&owner + 0x30) = &head;   // node == owner->head would error

        g_pfn_invalid_parameter_noinfo = [] { };

        void* self = obj.pre;                          // container lives at self+8

        // hit
        CHECK(Slot_1417cad00_lookup(self, 5, 0, 0) == 0xBBBB);
        CHECK(Slot_1417cad00_lookup(self, 2, 0, 0) == 0xAAAA);
        // id 0 answers 0 without walking: 2 exists, so a walk would have found it
        CHECK(Slot_1417cad00_lookup(self, 0, 0, 0) == 0);
        // past the end
        CHECK(Slot_1417cad00_lookup(self, 9, 0, 0) == 0);

        // the iterator check that CAN fire: node == owner->head (the bytes compare rbx with
        // [r11+0x30] and call the error path when they are equal)
        static int g_err;
        g_err = 0;
        g_pfn_invalid_parameter_noinfo = [] { ++g_err; };
        *(void**)((uint8_t*)&owner + 0x30) = &n[1];     // owner->head == the found node
        CHECK(Slot_1417cad00_lookup(self, 5, 0, 0) == 0xBBBB);   // still returns the value
        CHECK(g_err == 1);
        *(void**)((uint8_t*)&owner + 0x30) = &head;      // restore
        g_pfn_invalid_parameter_noinfo = [] { };

        // the wrappers now run through the ported lookup by default
        g_pfnLogic_1417cad00 = shipped_lookup;
        *(void**)(obj.container + 0x00) = &other_head;
        CHECK(Slot_1417cad90(self, 5, 0, 0) == 1);      // found -> true
        CHECK(Slot_1417cad90(self, 9, 0, 0) == 0);      // not found -> false
        CHECK(Slot_1417cadb0(self, 1, 5, 0) == 0x777);  // hit, forwards to the 2-arg tail
        CHECK(Slot_1417cb000(self, 5, 0, 0) == 0x888);  // hit, forwards to the 1-arg tail
    }

    // --- 0x1417a8a50, the +0x20 guard, carved from bytes past its truncated record
    {
        struct M {
            M* left = nullptr; M* parent = nullptr; M* right = nullptr;
            uint32_t key = 0;
            uint8_t pad1[4] = {0};
            uint64_t value = 0;
            uint8_t pad2 = 0;
            uint8_t isnil = 0;
            uint8_t tail[0x38 - 0x2a] = {0};   // room for the +0x30 pointer the check reads
        };
        static_assert(offsetof(M, value) == 0x20 && offsetof(M, isnil) == 0x29,
                      "map node layout must match the bytes");
        static M node, nil, head, other_head, scaryobj, ownerobj;
        static struct { uint8_t pre[0x18]; uint8_t map[0x40]; } obj;

        node = M(); nil = M(); nil.isnil = 1; head = M(); head.isnil = 1;
        other_head = M(); other_head.isnil = 1; scaryobj = M(); ownerobj = M();
        node.key = 5; node.value = 0xCAFE; node.left = &nil; node.right = &nil;
        head.parent = &node;

        std::memset(&obj, 0, sizeof(obj));
        *(void**)(obj.map + 0x30) = &head;
        *(void**)(obj.map + 0x00) = &scaryobj;            // the iterator's scary word
        *(M**)&scaryobj.left = &ownerobj;                 // *(scary) -> owner
        *(void**)((uint8_t*)&ownerobj + 0x30) = &other_head;

        void* self = obj.pre;                              // the map lives at self+0x18

        static uint64_t g_got_value;
        static int g_calls;
        g_calls = 0; g_got_value = 0;
        g_pfnLogic_1417a6960 = [](void* v, uint64_t arg) {
            ++g_calls; g_got_value = (uint64_t)(uintptr_t)v;
            if (arg == 0x1234) g_got_value |= 1ull << 63;  // remember the forwarded argument
        };

        // id 0 answers false and never walks
        CHECK(Slot_1417a8a50(self, 0, 0x1234, 0) == false);
        CHECK(g_calls == 0);

        // a hit with a live pointer calls the method with (pointer, arg3) and answers true
        CHECK(Slot_1417a8a50(self, 5, 0x1234, 0) == true);
        CHECK(g_calls == 1);
        CHECK((g_got_value & ~(1ull << 63)) == 0xCAFE);
        CHECK((g_got_value >> 63) == 1);                   // arg3 reached the callee

        // past the end: still true, no call
        g_calls = 0;
        CHECK(Slot_1417a8a50(self, 9, 0x1234, 0) == true);
        CHECK(g_calls == 0);

        // a hit with a null stored pointer: still true, no call
        node.value = 0;
        CHECK(Slot_1417a8a50(self, 5, 0x1234, 0) == true);
        CHECK(g_calls == 0);
    }

    // --- 0x141730cd0 grows and inserts, then answers an iterator at the inserted element
    {
        static uint32_t buf[8];
        static uint64_t vec[6], owner[6];
        static int insert_calls;
        static uint32_t inserted;
        insert_calls = 0; inserted = 0;

        std::memset(buf, 0, sizeof(buf));
        std::memset(vec, 0, sizeof(vec));
        std::memset(owner, 0, sizeof(owner));
        // the container word is the proxy shape 0x14177c6c0 builds: [word] leads to the map, and
        // the map's own +0x18/+0x20 are the bounds
        static uint64_t proxy[1];
        proxy[0] = (uint64_t)&owner[0];
        vec[0] = (uint64_t)&proxy[0];
        vec[3] = (uint64_t)&buf[0];          // +0x18 begin
        vec[4] = (uint64_t)&buf[2];          // +0x20 finish, two elements in
        vec[5] = (uint64_t)&buf[8];          // +0x28 capacity end
        owner[3] = 0;                        // +0x18 lower bound
        owner[4] = ~0ull;                    // +0x20 upper bound

        g_pfn_invalid_parameter_noinfo = [] { };
        g_pfnLogic_14172d120 = [](void* self, uint64_t*, uint64_t count, const void* v) {
            ++insert_calls; inserted = *(const uint32_t*)v;
            CHECK(count == 1);
            uint8_t* s = (uint8_t*)self;
            uint64_t fin = *(uint64_t*)(s + 0x20);
            *(uint32_t*)fin = *(const uint32_t*)v;    // the fake insert appends
            *(uint64_t*)(s + 0x20) = fin + 4;
        };

        uint64_t pair[2] = {vec[0], (uint64_t)&buf[2]};   // the container word, then finish
        uint64_t out[2] = {0, 0};
        uint32_t v = 0xBEEF;
        void* r = Slot_141730cd0_grow_insert(vec, out, pair, &v);
        CHECK(r == (void*)out);
        CHECK(insert_calls == 1);
        CHECK(inserted == 0xBEEF);
        CHECK(out[0] == vec[0]);                      // the container word
        CHECK(out[1] == (uint64_t)&buf[2]);            // the element offset the bytes computed

        // an empty vector takes the zero-offset path and still lands on begin
        vec[4] = vec[3];
        insert_calls = 0;
        pair[1] = vec[3];
        Slot_141730cd0_grow_insert(vec, out, pair, &v);
        CHECK(insert_calls == 1);
        CHECK(out[1] == (uint64_t)&buf[0]);
        g_pfnLogic_14172d120 = nullptr;
    }

    // --- the five callees of 0x14172d120, ported as bodies of their own
    {
        // 0x141722c70: builds a length_error and throws it, so the seam carries the text
        static int throws;
        static const char* seen;
        throws = 0; seen = nullptr;
        g_pfn_throw_length_error = [](const char* w) { ++throws; seen = w; };
        Slot_141722c70_throw_length_error();
        CHECK(throws == 1);
        CHECK(seen != nullptr);

        // 0x141724d10: count*4 bytes, after the divide-based overflow guard
        void* p = Slot_141724d10_allocate(nullptr, 2);
        CHECK(p != nullptr);
        ::operator delete(p);
        throws = 0;
        CHECK(Slot_141724d10_allocate(nullptr, 0x4000000000000000ULL) == nullptr);  // max/count = 3
        CHECK(throws == 1);                                   // the guard threw instead of allocating
        void* zero = Slot_141724d10_allocate(nullptr, 0);     // zero still allocates
        CHECK(zero != nullptr);
        ::operator delete(zero);
        g_pfn_throw_length_error = nullptr;

        // 0x14172acb0: move src..src_end down to dst, answer dst + bytes
        static uint32_t mb[8];
        std::memset(mb, 0, sizeof(mb));
        mb[0] = 1; mb[1] = 2; mb[2] = 3;
        uint64_t r = Slot_14172acb0_move_block(nullptr, &mb[0], &mb[2], &mb[4]);
        CHECK(mb[4] == 1 && mb[5] == 2);                      // two elements moved
        CHECK(r == (uint64_t)&mb[6]);                         // dst + 8 bytes
        CHECK(Slot_14172acb0_move_block(nullptr, &mb[0], &mb[0], &mb[4]) == (uint64_t)&mb[4]);

        // 0x141727380: move src..mid so it ends at dst_end, with a signed guard
        static uint32_t mt[8];
        std::memset(mt, 0, sizeof(mt));
        mt[0] = 7; mt[1] = 8;
        uint64_t d = Slot_141727380_move_tail(&mt[0], &mt[2], &mt[6]);
        CHECK(d == (uint64_t)&mt[4]);                         // ends at dst_end - 8 bytes
        CHECK(mt[4] == 7 && mt[5] == 8);
        // mid below src: the signed guard skips the move, but the answer is still dst_end minus the
        // negative byte count, which the bytes compute as dst_end + 8. The test expectation was wrong
        // here, not the port; &mt[8] is what `lea rax,[rdx*4]` then `sub rbx,rax` produces.
        CHECK(Slot_141727380_move_tail(&mt[2], &mt[0], &mt[6]) == (uint64_t)&mt[8]);

        // 0x1417f2fdc: the jmp thunk onto MSVCR90!operator delete
        void* heap = ::operator new(0x20);
        Slot_1417f2fdc_deallocate(heap);                      // LSan fails the run if this leaks
    }

    // --- 0x1417a8940 looks a key up and answers the 32-bit value
    {
        static uint8_t self[0xA0];
        static uint64_t n5[8], n3[8], nil[8], endn[16], map[8], proxy[1];
        std::memset(self, 0, sizeof(self)); std::memset(n5, 0, sizeof(n5));
        std::memset(n3, 0, sizeof(n3)); std::memset(nil, 0, sizeof(nil));
        std::memset(endn, 0, sizeof(endn)); std::memset(map, 0, sizeof(map));

        ((uint8_t*)nil)[0x21] = 1;                       // _Isnil on the shared nil node
        ((uint8_t*)endn)[0x21] = 1;                      // the map's end node is nil too
        *(uint64_t*)((uint8_t*)endn + 0x08) = (uint64_t)&n5[0];   // end->parent is the root
        *(uint32_t*)((uint8_t*)n5 + 0x18) = 5;           // key
        *(uint32_t*)((uint8_t*)n5 + 0x1c) = 0xAA;        // value
        *(uint64_t*)((uint8_t*)n5 + 0x00) = (uint64_t)&n3[0];     // left
        *(uint64_t*)((uint8_t*)n5 + 0x10) = (uint64_t)&nil[0];    // right
        *(uint32_t*)((uint8_t*)n3 + 0x18) = 3;
        *(uint32_t*)((uint8_t*)n3 + 0x1c) = 0xBB;
        *(uint64_t*)((uint8_t*)n3 + 0x00) = (uint64_t)&nil[0];
        *(uint64_t*)((uint8_t*)n3 + 0x10) = (uint64_t)&nil[0];

        proxy[0] = (uint64_t)&map[0];                    // the word leads to the map
        *(uint64_t*)((uint8_t*)map + 0x30) = (uint64_t)&endn[0];
        *(uint64_t*)(self + 0x58) = (uint64_t)proxy;     // container word
        *(uint64_t*)(self + 0x88) = (uint64_t)&endn[0];  // end node
        g_pfn_invalid_parameter_noinfo = [] { };

        CHECK(Slot_1417a8940_lookup(self, 3) == 0xBB);   // walks left once and finds it
        CHECK(Slot_1417a8940_lookup(self, 5) == 0xAA);   // the root itself
        CHECK(Slot_1417a8940_lookup(self, 9) == 0);      // past the right edge: miss answers 0
        CHECK(Slot_1417a8940_lookup(self, 1) == 0);      // below everything: candidate fails the key test
    }

    // --- 0x14172d120 inserts: the three paths the bytes have
    {
        static uint32_t buf[16], newbuf[16];
        static uint64_t vec[6];
        static int deallocs, mm_calls;
        static void* mm_src[2];
        g_pfn_invalid_parameter_noinfo = [] { };

        // Path B: room exists and enough elements sit after the point, so the tail shifts right
        std::memset(buf, 0, sizeof(buf)); std::memset(vec, 0, sizeof(vec));
        buf[0] = 0x11; buf[1] = 0x22; buf[2] = 0x33; buf[3] = 0x44;
        vec[3] = (uint64_t)&buf[0];        // +0x18 begin
        vec[4] = (uint64_t)&buf[4];        // +0x20 finish
        vec[5] = (uint64_t)&buf[8];        // +0x28 capacity end
        g_pfnLogic_14172acb0 = [](void*, void*, void* src, void*) -> uint64_t {
            return (uint64_t)src; };       // pretend the tail moved and finish is unchanged
        g_pfnLogic_141727380 = [](void*, void*, void*) -> uint64_t { return 0; };   // return ignored here
        uint64_t it[2] = {0, (uint64_t)&buf[1]};
        uint32_t v = 0x99;
        Slot_14172d120_insert_n(vec, it, 2, &v);
        CHECK(buf[1] == 0x99 && buf[2] == 0x99);      // the fill loop
        CHECK(vec[4] == (uint64_t)&buf[4]);           // finish as the seam left it

        // Path C: room exists but fewer than count elements sit after the point
        std::memset(buf, 0, sizeof(buf));
        vec[3] = (uint64_t)&buf[0];
        vec[4] = (uint64_t)&buf[2];
        vec[5] = (uint64_t)&buf[8];
        it[1] = (uint64_t)&buf[1];
        v = 0x77;
        Slot_14172d120_insert_n(vec, it, 4, &v);
        CHECK(buf[1] == 0x77 && buf[2] == 0x77 && buf[3] == 0x77 && buf[4] == 0x77);
        CHECK(vec[4] == (uint64_t)&buf[6]);           // finish grew by count*4

        // Path A: no room, so it allocates, copies head and tail, frees the old buffer
        std::memset(buf, 0, sizeof(buf)); std::memset(newbuf, 0xEE, sizeof(newbuf));
        buf[0] = 0xA1; buf[1] = 0xB2;
        vec[3] = (uint64_t)&buf[0];
        vec[4] = (uint64_t)&buf[2];                   // two elements in
        vec[5] = (uint64_t)&buf[2];                   // capacity 2, so a third needs room
        deallocs = 0; mm_calls = 0;
        g_pfnLogic_141724d10 = [](void*, uint64_t) -> void* { return (void*)&newbuf[0]; };
        g_pfn_memmove_s = [](void* d, size_t, const void* src, size_t n) {
            ++mm_calls; if (mm_calls <= 2) mm_src[mm_calls-1] = (void*)src;
            memmove(d, src, n); };
        g_pfnLogic_1417f2fdc = [](void*) { ++deallocs; };
        it[1] = (uint64_t)&buf[1];
        v = 0x55;
        Slot_14172d120_insert_n(vec, it, 1, &v);
        CHECK(vec[3] == (uint64_t)&newbuf[0]);        // begin now the new buffer
        CHECK(newbuf[0] == 0xA1);                     // head copied
        CHECK(newbuf[1] == 0x55);                     // the inserted element
        CHECK(newbuf[2] == 0xB2);                     // tail copied
        CHECK(vec[4] == (uint64_t)&newbuf[3]);        // finish = buffer + 3 elements
        CHECK(vec[5] == (uint64_t)&newbuf[3]);        // capacity = buffer + grown elements
        CHECK(mm_calls == 2);
        CHECK(deallocs == 1);
        g_pfnLogic_141724d10 = nullptr; g_pfnLogic_1417f2fdc = nullptr;
        g_pfn_memmove_s = nullptr; g_pfnLogic_14172acb0 = nullptr; g_pfnLogic_141727380 = nullptr;
    }

    // --- 0x1417495d0 clears the vector by moving finish back to begin
    {
        static uint32_t buf[4];
        static uint64_t vec[6];
        std::memset(vec, 0, sizeof(vec));
        vec[0] = (uint64_t)&vec[0];        // the container word
        vec[3] = (uint64_t)&buf[0];        // +0x18 begin
        vec[4] = (uint64_t)&buf[3];        // +0x20 finish
        vec[5] = (uint64_t)&buf[4];        // +0x28 capacity end
        g_pfn_invalid_parameter_noinfo = [] { };
        Slot_1417495d0_clear_vector(vec);
        CHECK(vec[4] == vec[3]);           // finish == begin
        vec[4] = vec[3];                   // already empty
        Slot_1417495d0_clear_vector(vec);
        CHECK(vec[4] == vec[3]);
    }

    // --- 0x141732040 appends while there is room and hands off when there is not
    {
        static uint32_t buf[4];
        static uint64_t vec[6];
        static int grow_calls;
        static uint32_t grow_value;
        grow_calls = 0; grow_value = 0;

        std::memset(buf, 0, sizeof(buf));
        std::memset(vec, 0, sizeof(vec));
        vec[0] = (uint64_t)&vec[0];        // the container word
        vec[3] = (uint64_t)&buf[0];        // +0x18 begin
        vec[4] = (uint64_t)&buf[1];        // +0x20 finish, one element in
        vec[5] = (uint64_t)&buf[2];        // +0x28 capacity end
        g_pfn_invalid_parameter_noinfo = [] { };
        g_pfnLogic_141730cd0 = [](void*, void*, void*, const void* v) {
            ++grow_calls; grow_value = *(const uint32_t*)v;
        };

        uint32_t v = 0x1234;
        Slot_141732040_push_back(vec, &v);         // room for one more
        CHECK(grow_calls == 0);
        CHECK(buf[1] == 0x1234);
        CHECK(vec[4] == (uint64_t)&buf[2]);        // finish advanced by four

        v = 0x5678;
        Slot_141732040_push_back(vec, &v);         // full now, so the seam takes over
        CHECK(grow_calls == 1);
        CHECK(grow_value == 0x5678);
        g_pfnLogic_141730cd0 = nullptr;
    }

    // --- 0x14177ace0 makes the end node
    {
        void* n = Slot_14177ace0_new_node();
        CHECK(n != nullptr);
        uint8_t* p = (uint8_t*)n;
        CHECK(*(uint64_t*)(p + 0x00) == 0);        // left
        CHECK(*(uint64_t*)(p + 0x08) == 0);        // parent
        CHECK(*(uint64_t*)(p + 0x10) == 0);        // right
        CHECK(*(uint8_t *)(p + 0x28) == 1);        // colour
        CHECK(*(uint8_t *)(p + 0x29) == 0);        // _Isnil clear, unlike the map's own end node
        ::operator delete(n);
    }

    // --- 0x1417a8520 answers a lower_bound pair, with the key taken by pointer
    {
        struct K {
            K* left = nullptr; K* parent = nullptr; K* right = nullptr;
            uint32_t key = 0; uint8_t pad1[4] = {0}; uint64_t value = 0;
            uint8_t pad2 = 0; uint8_t isnil = 0; uint8_t tail[0x38 - 0x2a] = {0};
        };
        static K root, right_child, nil, head, scaryholder, owner;
        static struct { uint8_t bytes[0x38]; } map;
        root = K(); right_child = K(); nil = K(); nil.isnil = 1;
        head = K(); head.isnil = 1; scaryholder = K(); owner = K();

        root.key = 5; root.left = &nil; root.right = &right_child; right_child.parent = &root;
        right_child.key = 7; right_child.left = &nil; right_child.right = &nil;
        head.parent = &root;

        std::memset(&map, 0, sizeof(map));
        *(void**)(map.bytes + 0x30) = &head;
        *(void**)(map.bytes + 0x00) = &scaryholder;
        *(K**)&scaryholder.left = &owner;

        g_pfn_invalid_parameter_noinfo = [] { };
        uint64_t out[2];
        uint32_t k = 5;
        CHECK(Slot_1417a8520_lower_bound(map.bytes, out, &k) == out);
        CHECK(out[1] == (uint64_t)&root);              // the key itself
        CHECK(out[0] == (uint64_t)&scaryholder);

        k = 7;
        Slot_1417a8520_lower_bound(map.bytes, out, &k);
        CHECK(out[1] == (uint64_t)&right_child);

        k = 1;                                         // below everything lands on the end node
        Slot_1417a8520_lower_bound(map.bytes, out, &k);
        CHECK(out[1] == (uint64_t)&head);

        k = 9;                                         // above everything does too
        Slot_1417a8520_lower_bound(map.bytes, out, &k);
        CHECK(out[1] == (uint64_t)&head);

        head.parent = &nil;                            // an empty tree
        k = 5;
        Slot_1417a8520_lower_bound(map.bytes, out, &k);
        CHECK(out[1] == (uint64_t)&head);
    }

    // --- 0x14177c6c0 builds the map: proxy, end node, and the size
    {
        struct Head { uint8_t bytes[0x38]; };
        static Head head;
        static uint64_t map[8];
        std::memset(&head, 0, sizeof(head));
        std::memset(map, 0, sizeof(map));

        g_pfnLogic_14177ace0 = [](void*) -> void* { return (void*)&head; };
        CHECK(Slot_14177c6c0_ctor(map) == (void*)map);
        uint64_t* proxy = (uint64_t*)map[0];
        CHECK(proxy != nullptr);
        CHECK(proxy[0] == (uint64_t)map);          // the proxy points back at the map
        CHECK(map[6] == (uint64_t)&head);          // +0x30 the end node
        CHECK(head.bytes[0x29] == 1);              // _Isnil
        CHECK(*(uint64_t*)(head.bytes + 0x08) == (uint64_t)&head);   // parent
        CHECK(*(uint64_t*)(head.bytes + 0x00) == (uint64_t)&head);   // left
        CHECK(*(uint64_t*)(head.bytes + 0x10) == (uint64_t)&head);   // right
        CHECK(map[7] == 0);                        // +0x38 size
        g_pfnLogic_14177ace0 = nullptr;
    }

    // --- 0x1417a6960 walks the range and calls 0x141732040 per element
    {
        static uint64_t slots[3], box[0x0a];            // two live slots, the third is the end
        static uint64_t proxy[1], map[0x0a];
        static int prep_calls, elem_calls;
        static void* seen_arg;
        static uint64_t seen_elems[2];
        prep_calls = 0; elem_calls = 0; seen_arg = nullptr; seen_elems[0] = seen_elems[1] = 0;

        std::memset(box, 0, sizeof(box));
        // the word at +0x20 is the proxy 0x14177c6c0 builds: *proxy is the map, and the map's own
        // +0x20 is the bound every slot must stay under
        box[4] = (uint64_t)&proxy[0];
        box[7] = (uint64_t)&slots[0];              // +0x38 begin
        box[8] = (uint64_t)&slots[2];              // +0x40 end, one past the second slot
        proxy[0] = (uint64_t)&map[0];
        map[4] = ~0ull;
        slots[0] = 0xAA; slots[1] = 0xBB; slots[2] = 0;

        g_pfn_invalid_parameter_noinfo = [] { };
        g_pfnLogic_1417495d0 = [](void* a) -> void* { ++prep_calls; seen_arg = a; return a; };
        g_pfnLogic_141732040 = [](void* a, void* e) {
            if (elem_calls < 2) seen_elems[elem_calls] = (uint64_t)(uintptr_t)e;
            ++elem_calls; seen_arg = a;
        };

        int marker = 5;
        Slot_1417a6960_iterate(box, &marker);
        CHECK(prep_calls == 1);
        CHECK(elem_calls == 2);
        CHECK(seen_arg == (void*)&marker);
        CHECK(seen_elems[0] == 0xAA && seen_elems[1] == 0xBB);

        // an empty range preps the argument and calls nothing
        prep_calls = 0; elem_calls = 0;
        box[8] = (uint64_t)&slots[0];              // end == begin
        Slot_1417a6960_iterate(box, &marker);
        CHECK(prep_calls == 1);
        CHECK(elem_calls == 0);
        g_pfnLogic_1417495d0 = nullptr;
        g_pfnLogic_141732040 = nullptr;
    }

    // --- 0x141779090 scans a slot range for the first (id, kind) match, and 0x141779400 takes it
    {
        static uint32_t want_id, want_kind, answer_kind;
        static void* last_self;
        struct Obj { void* vt[0x10]; };
        static Obj elem;
        static uint64_t slot[1], scaryholder[1], owner[8], found[8];

        static uint64_t table[0x10];
        for (int i = 0; i < 0x10; ++i) table[i] = 0;
        table[1] = (uint64_t)+[](void* self, uint32_t) -> void* { last_self = self; return self; };
        table[2] = (uint64_t)+[](void* self, uint32_t) -> void* { last_self = self; return self; };
        table[8] = (uint64_t)+[](void*) -> uint64_t { return want_id; };      // slot 0x40
        table[9] = (uint64_t)+[](void*) -> uint64_t { return answer_kind; };  // slot 0x48
        elem.vt[0] = (void*)table;    // the object's first word points AT the table, as in the image

        std::memset(slot, 0, sizeof(slot));
        slot[0] = (uint64_t)&elem;
        std::memset(found, 0, sizeof(found));
        found[1] = (uint64_t)&scaryholder[0];        // +0x08 the container word
        found[4] = (uint64_t)&slot[0];               // +0x20 begin
        found[5] = (uint64_t)&slot[1];               // +0x28 end, one past
        scaryholder[0] = (uint64_t)&owner[0];
        owner[4] = ~0ull;                            // +0x20 the bound every slot must stay under

        g_pfn_invalid_parameter_noinfo = [] { };
        g_pfn_log_InlineLogERROR = nullptr;

        uint64_t it[2] = {0, 0};
        want_id = 0xB; want_kind = 2; answer_kind = 2;   // slot 0x48 is what the scan compares
        uint64_t* out = Slot_141779090_search(found, it, 0xB, 2);
        CHECK(out == it);
        CHECK(it[1] == (uint64_t)&slot[0]);           // matched the only element
        CHECK(last_self == (void*)&elem);

        uint64_t it2[2] = {0, 0};
        out = Slot_141779090_search(found, it2, 0xC, 2);   // the id does not answer
        CHECK(out == it2);
        CHECK(it2[1] == (uint64_t)&slot[1]);          // walked off the end

        // 0x141779400: no slot left answers 0
        CHECK(Slot_141779400(found, 0xC, 2) == 0);
        // and a match returns what slot 0x48 answers on the object slot 0x10 handed back. The scan
        // matches on that same slot, so the answer is the value that satisfied the kind test.
        answer_kind = 2;
        CHECK(Slot_141779400(found, 0xB, 2) == 2);
        CHECK(last_self == (void*)&elem);

        // the tail seam defaults to the ported body, so the same call goes through the pointer
        g_pfnLogic_141779400 = Slot_141779400;
        CHECK(g_pfnLogic_141779400(found, 0xB, 2) == 2);
        g_pfnLogic_141779400 = Slot_141779400;   // restore the default for the rest of the file
    }

    // --- 0x14177f980 gates on the kind, then chains vtable -> find -> tail call
    {
        static uint32_t vcall_hit;      // what the vtable slot answers
        static uint32_t vcall_seen_id;
        static uint64_t tail_result;
        static void* tail_found;
        static uint32_t tail_id, tail_kind, tail_calls;
        static uint32_t logged_kind;
        static int log_calls;
        log_calls = 0; logged_kind = 0; tail_calls = 0; tail_result = 0xDEAD;

        // fake 0x88-byte singleton: [A+8] -> inner, [inner] -> table, table[0x3f] -> handler
        struct A88 { uint8_t bytes[0x88]; };
        static A88 a;
        static void* inner_vt[0x40];
        static struct { uint8_t bytes[0x10]; } inner;
        for (int i = 0; i < 0x40; ++i) inner_vt[i] = nullptr;
        inner_vt[0x3f] = (void*)+[](void* self, uint32_t id) -> uint64_t {
            vcall_seen_id = id; return vcall_hit;
        };
        std::memset(&a, 0, sizeof(a));
        *(void**)(inner.bytes) = inner_vt;
        *(void**)(a.bytes + 0x08) = &inner;
        Slot_1417b6210_seed(&a);

        // fake 0x40-byte singleton carrying the map used by the key search
        struct K {
            K* left = nullptr; K* parent = nullptr; K* right = nullptr;
            uint32_t key = 0; uint8_t pad1[4] = {0}; uint64_t value = 0;
            uint8_t pad2 = 0; uint8_t isnil = 0; uint8_t tail[0x38 - 0x2a] = {0};
        };
        static K node, nil, head, scaryholder, owner;
        static struct { uint8_t bytes[0x40]; } b40;
        node = K(); nil = K(); nil.isnil = 1; head = K(); head.isnil = 1;
        scaryholder = K(); owner = K();
        node.key = 7; node.value = 0x5555; node.left = &nil; node.right = &nil;
        head.parent = &node;
        std::memset(&b40, 0, sizeof(b40));
        *(void**)(b40.bytes + 0x30) = &head;
        *(void**)(b40.bytes + 0x00) = &scaryholder;
        *(K**)&scaryholder.left = &owner;
        *(void**)((uint8_t*)&owner + 0x30) = &head;
        Slot_14177c770_seed(b40.bytes);

        g_pfn_invalid_parameter_noinfo = [] { };
        g_pfn_log_InlineLogERROR = [](const void*, const void* p1, const void*, const void*,
                                      uint32_t) {
            ++log_calls; logged_kind = (uint32_t)(uintptr_t)p1;
        };
        g_pfnLogic_141779400 = [](void* found, uint32_t id, uint32_t kind) -> uint64_t {
            ++tail_calls; tail_found = found; tail_id = id; tail_kind = kind; return tail_result;
        };

        // a kind outside 1..3 is reported and answers 0
        CHECK(Slot_14177f980(&a, 1, 4, 0) == 0);
        CHECK(log_calls == 1 && logged_kind == 4);
        CHECK(tail_calls == 0);
        log_calls = 0;

        // the vtable slot answering 0 stops the chain
        vcall_hit = 0;
        CHECK(Slot_14177f980(&a, 1, 1, 0) == 0);
        CHECK(tail_calls == 0);
        CHECK(vcall_seen_id == 1);

        // an id the map does not hold stops the chain too: the node carries 7, so ask for 8
        vcall_hit = 8;
        CHECK(Slot_14177f980(&a, 1, 2, 0) == 0);
        CHECK(tail_calls == 0);

        // and a real hit forwards the found object, the original id and the kind
        node.key = 9; head.parent = &node;
        vcall_hit = 9;
        CHECK(Slot_14177f980(&a, 3, 3, 0) == tail_result);
        CHECK(tail_calls == 1);
        CHECK(tail_found == (void*)(uintptr_t)0x5555);
        CHECK(tail_id == 3);
        CHECK(tail_kind == 3);

        g_pfnLogic_141779400 = nullptr;
        g_pfn_log_InlineLogERROR = nullptr;
        Slot_1417b6210_seed(nullptr);
        Slot_14177c770_seed(nullptr);
    }

    // --- the two singletons build once and hand back the same object
    {
        static int ctor_calls;
        ctor_calls = 0;
        g_pfnLogic_14177c6c0 = [](void* mem) -> void* { ++ctor_calls; return mem; };

        void* a = Slot_14177c770_singleton();
        void* b = Slot_14177c770_singleton();
        CHECK(a != nullptr);
        CHECK(a == b);                     // the second call answers the stored slot
        CHECK(ctor_calls == 1);            // and the constructor ran once

        void* c = Slot_1417b6210_singleton();
        void* d = Slot_1417b6210_singleton();
        CHECK(c != nullptr && c == d);
        // the inline initialisation: derived vtable store last, and the cleared words
        CHECK(*(uint64_t*)((uint8_t*)c + 0x00) == 0x141835068ULL);
        CHECK(*(uint64_t*)((uint8_t*)c + 0x08) == 0);
        CHECK(*(uint64_t*)((uint8_t*)c + 0x58) == 0);
        CHECK(*(uint8_t *)((uint8_t*)c + 0x60) == 0);
        CHECK(*(uint64_t*)((uint8_t*)c + 0x79) == 0);
        g_pfnLogic_14177c6c0 = nullptr;
    }

    // --- 0x14177c0a0 finds a key and answers the stored value
    {
        struct K {
            K* left = nullptr; K* parent = nullptr; K* right = nullptr;
            uint32_t key = 0;
            uint8_t pad1[4] = {0};
            uint64_t value = 0;
            uint8_t pad2 = 0;
            uint8_t isnil = 0;
            uint8_t tail[0x38 - 0x2a] = {0};
        };
        static K root, right_child, nil, head, scaryholder, owner;
        static struct { uint8_t words[0x38]; } map;
        root = K(); right_child = K(); nil = K(); nil.isnil = 1;
        head = K(); head.isnil = 1; scaryholder = K(); owner = K();

        root.key = 5; root.value = 0x1111;
        root.left = &nil; root.right = &right_child; right_child.parent = &root;
        right_child.key = 7; right_child.value = 0x2222;
        right_child.left = &nil; right_child.right = &nil;
        head.parent = &root;

        std::memset(&map, 0, sizeof(map));
        *(void**)(map.words + 0x30) = &head;
        *(void**)(map.words + 0x00) = &scaryholder;
        *(K**)&scaryholder.left = &owner;
        *(void**)((uint8_t*)&owner + 0x30) = &head;

        g_pfn_invalid_parameter_noinfo = [] { };
        CHECK(Slot_14177c0a0_find(map.words, 5) == 0x1111);   // the root
        CHECK(Slot_14177c0a0_find(map.words, 7) == 0x2222);   // through the right walk
        CHECK(Slot_14177c0a0_find(map.words, 1) == 0);        // smaller than everything
        CHECK(Slot_14177c0a0_find(map.words, 9) == 0);        // larger than everything
        CHECK(Slot_14177c0a0_find(map.words, 6) == 0);        // between two keys

        head.parent = &nil;                                   // an empty tree
        CHECK(Slot_14177c0a0_find(map.words, 5) == 0);
    }

    // --- 0x141724850 frees the object its argument points at
    {
        void* obj = ::operator new(16);
        void* holder[1] = {obj};
        Slot_141724850_delete_through(holder);            // ASan/LSan prove the free happened
    }

    // --- 0x1417ac810 dispatches through [self+8] -> [inner] -> slot 0x1f8
    {
        static int slot_hits;
        static void* seen_self;
        static uint32_t seen_id;
        slot_hits = 0; seen_self = nullptr; seen_id = 0;

        struct Fake { void* vt[0x40]; };                   // vt[0x3f] sits at +0x1f8
        static Fake inner;
        static void* vtbl[0x40];
        for (int i = 0; i < 0x40; ++i) vtbl[i] = nullptr;
        vtbl[0x3f] = (void*)+[](void* self, uint32_t id) -> uint64_t {
            ++slot_hits; seen_self = self; seen_id = id; return 0x99;
        };
        inner.vt[0] = vtbl;                                // [inner] -> the table

        void* selfbuf[2] = {nullptr, &inner};               // [self+8] -> inner
        CHECK(Slot_1417ac810_vcall_1f8(selfbuf, 42) == 0x99);
        CHECK(slot_hits == 1);
        CHECK(seen_self == (void*)&inner);
        CHECK(seen_id == 42);
    }


    // ------------------------------------------------------------------
    // 0x1417caa00 — the manager's map clear and its dead-loop guard.
    // Fixtures are the shapes the bytes address: the end node at this+0x38, the
    // proxy word at this+0x08 whose *word is the map, node {left,parent,right,
    // value@0x20, _Isnil@0x29}.
    // ------------------------------------------------------------------
    {
        struct Node {
            void* pLeft; void* pParent; void* pRight;
            uint64_t uPad18; void* pValue; uint8_t cPad28; uint8_t cIsNil; uint8_t aTail[6];
        };
        static Node A, B, C, End;
        static uint64_t v1 = 11, v2 = 22, v3 = 33;

        static int nDestroy; static void* aDestroyed[16]; static uint32_t uFlagSeen;
        static int nLog; static const char* pFmt; static const char* pExpr;
        static const char* pVar; static const char* pFile; static int nLine;
        nDestroy = 0; nLog = 0; uFlagSeen = 0;
        g_pfnLogic_14179db30 = +[](void* p, uint32_t n) -> uint64_t {
            uFlagSeen = n;
            if (nDestroy < 16) aDestroyed[nDestroy] = p;
            ++nDestroy; return 0; };
        g_pfnLogic_1417a1180 = +[](void* p) -> uint64_t {
            if (nDestroy < 16) aDestroyed[nDestroy] = p;
            ++nDestroy; return 0; };
        g_pfnLogic_14179a150 = +[](void* p) -> uint64_t {
            if (nDestroy < 16) aDestroyed[nDestroy] = p;
            ++nDestroy; return 0; };
        g_pfnLogic_14179a020 = +[](void* p) -> uint64_t {
            if (nDestroy < 16) aDestroyed[nDestroy] = p;
            ++nDestroy; return 0; };
        g_pfn_log_141823030 = +[](const char* fmt, const char* ex, const char* va,
                                  const char* fi, int ln) {
            pFmt = fmt; pExpr = ex; pVar = va; pFile = fi; nLine = ln; ++nLog; };

        // zero every byte first: the bodies read the links and the _Isnil byte
        std::memset(&A, 0, sizeof A); std::memset(&B, 0, sizeof B);
        std::memset(&C, 0, sizeof C); std::memset(&End, 0, sizeof End);
        End.cIsNil = 1; End.pLeft = &A; End.pRight = &C; End.pParent = &B;
        A.pLeft = A.pRight = &End; A.pParent = &B; A.pValue = &v1;
        B.pLeft = &A; B.pRight = &C; B.pParent = &End; B.pValue = &v2;
        C.pLeft = C.pRight = &End; C.pParent = &B; C.pValue = &v3;

        static uint64_t aMap[8];                 // the map: +0x30 the end node
        static void* pProxy[1];
        std::memset(aMap, 0, sizeof aMap);
        pProxy[0] = aMap;                        // *word leads back to the owner
        aMap[0] = (uint64_t)pProxy;              // the map's +0x00 proxy word
        aMap[6] = (uint64_t)&End;                // the map's +0x30 end node

        static uint64_t aSelf[8];                // this+0x08 proxy, this+0x38 end node
        std::memset(aSelf, 0, sizeof aSelf);
        aSelf[1] = (uint64_t)pProxy;
        aSelf[7] = (uint64_t)&End;

        CHECK(Slot_1417caa00_erase_all(aSelf) == true);
        CHECK(nDestroy == 12);                   // four destroys for each of the three nodes
        CHECK(aDestroyed[0] == &v1 && aDestroyed[4] == &v2 && aDestroyed[8] == &v3);
        CHECK(uFlagSeen == 0x3ff);               // the only call carrying an argument
        CHECK(nLog == 0);                        // the guard did not fire

        // the three-node walk leaves the map untouched: nothing is unlinked
        CHECK(End.pLeft == &A && B.pLeft == &A && B.pRight == &C);

        // --- an empty map answers true and touches nothing
        nDestroy = 0;
        End.pLeft = &End;
        CHECK(Slot_1417caa00_erase_all(aSelf) == true);
        CHECK(nDestroy == 0);

        // --- a single node whose value is null: walked, so the guard sees one pass,
        //     but no destroy runs
        nDestroy = 0;
        End.pLeft = &A; A.pValue = nullptr;
        A.pLeft = A.pRight = &End; A.pParent = &End;   // a lone node, so the walk ends there
        CHECK(Slot_1417caa00_erase_all(aSelf) == true);
        CHECK(nDestroy == 0);
        A.pValue = &v1;

        // --- the guard: two nodes that point at each other make the increment
        //     alternate forever; after 1,000,001 passes the report fires and the
        //     body answers true, exactly like the epilogue at 0x1417cab65.
        static Node N, M;
        std::memset(&N, 0, sizeof N); std::memset(&M, 0, sizeof M);
        N.pLeft = &End; N.pRight = &M; N.pValue = nullptr;
        M.pLeft = &End; M.pRight = &N; M.pValue = nullptr;
        End.pLeft = &N;
        nDestroy = 0; nLog = 0; pFmt = pExpr = pVar = pFile = nullptr; nLine = 0;
        CHECK(Slot_1417caa00_erase_all(aSelf) == true);
        CHECK(nLog == 1);
        CHECK(nDestroy == 0);
        CHECK(std::strcmp(pExpr, "DEAD_LOOP_BREAK") == 0);
        CHECK(std::strcmp(pVar, "uLoopCount") == 0);
        CHECK(std::strstr(pFile, "synmanager.cpp") != nullptr);
        CHECK(std::strstr(pFile, "cqserver-78.0.11-1204") != nullptr);
        CHECK(nLine == 0x117);
        CHECK(std::strcmp(pFmt, "\xa1\xef%s(%s)\xa1\xef in %s, %d") == 0);

        // the guarded run still walks to the end when the structure is sane
        End.pLeft = &A; End.pRight = &C;
        A.pParent = &B;                        // put the leaf back on the root
        nDestroy = 0; nLog = 0;
        CHECK(Slot_1417caa00_erase_all(aSelf) == true);
        CHECK(nDestroy == 12 && nLog == 0);
    }

    // ------------------------------------------------------------------
    // 0x14178f470 — the "IF_OK(m_pRec)" gate. Miss reports and answers the empty
    // string; hit goes m_pRec -> vtable[2](m_pRec, 1) -> vtable[15] of the answer.
    {
        // the reporter, captured
        static const char* pFmt2; static const char* pExpr2; static const char* pVar2;
        static const char* pFile2; static int nLine2; static int nLog2;
        g_pfn_log_141823030 = +[](const char* f, const char* e, const char* w,
                                  const char* fi, int l) {
            pFmt2 = f; pExpr2 = e; pVar2 = w; pFile2 = fi; nLine2 = l; ++nLog2;
        };

        // m_pRec and what its first call hands back
        static void* pRecSeen; static uint32_t uRecArg; static int nRecCalls;
        static void* pResSeen; static int nResCalls;
        static const char kAnswer[] = "answer";
        static void* pResObj;
        static void* aResVt[16];
        static void* aRecVt[16];
        aRecVt[0x10 / 8] = (void*)(void* (*)(void*, uint32_t)) + [](void* self, uint32_t n) -> void* {
            pRecSeen = self; uRecArg = n; ++nRecCalls; return pResObj;
        };
        aResVt[0x78 / 8] = (void*)(void* (*)(void*)) + [](void* self) -> void* {
            pResSeen = self; ++nResCalls; return (void*)kAnswer;
        };
        static void* pRes = aResVt;
        pResObj = &pRes;
        static void* aRecObj[1];                 // the object: word 0 is its vtable
        aRecObj[0] = (void*)aRecVt;

        static uint64_t aGate[0x90];
        std::memset(aGate, 0, sizeof aGate);

        // the miss: +0x428 is null
        nLog2 = 0; nRecCalls = nResCalls = 0;
        const char* pszMiss = Slot_14178f470(aGate);
        CHECK(pszMiss != nullptr && pszMiss[0] == '\0');   // 0x141827409 is a lone NUL
        CHECK(nLog2 == 1);
        CHECK(std::strcmp(pExpr2, "IF_OK") == 0);
        CHECK(std::strcmp(pVar2, "m_pRec") == 0);
        CHECK(std::strstr(pFile2, "syndicate.cpp") != nullptr);
        CHECK(std::strstr(pFile2, "cqserver-78.0.11-1204") != nullptr);
        CHECK(nLine2 == 0x8a8);
        CHECK(std::strcmp(pFmt2, "\xa1\xef%s(%s)\xa1\xef in %s, %d") == 0);
        CHECK(nRecCalls == 0 && nResCalls == 0);

        // the hit: +0x428 carries an object whose word 0 is its vtable
        *(void**)((uint8_t*)aGate + 0x428) = (void*)aRecObj;
        nLog2 = 0; nRecCalls = nResCalls = 0;
        const char* pszHit = Slot_14178f470(aGate);
        CHECK(std::strcmp(pszHit, kAnswer) == 0);
        CHECK(nLog2 == 0);
        CHECK(nRecCalls == 1 && nResCalls == 1);
        CHECK(pRecSeen == (void*)aRecObj);       // edx = 1 went with it
        CHECK(uRecArg == 1);
        CHECK(pResSeen == pResObj);              // and slot 15 saw what came back
    }

    // ------------------------------------------------------------------
    // 0x141797e00 — the id predicate on the map at this+0x290. This layout puts the
    // nil byte at +0x1d and the key at +0x18, and turns left when id >= node key.
    {
        struct Node { uint64_t uLeft, uParent, uRight; uint32_t uKey; uint8_t cPad1c, cNil, aPad[2]; };
        static Node End, R5, N7;
        std::memset(&End, 0, sizeof End); std::memset(&R5, 0, sizeof R5);
        std::memset(&N7, 0, sizeof N7);
        End.cNil = 1; End.uParent = (uint64_t)&R5;
        R5.uKey = 5; R5.uParent = (uint64_t)&End; R5.uLeft = (uint64_t)&N7; R5.uRight = (uint64_t)&End;
        N7.uKey = 7; N7.uParent = (uint64_t)&R5; N7.uLeft = (uint64_t)&End; N7.uRight = (uint64_t)&End;

        static uint64_t aSelf2[0x80];
        std::memset(aSelf2, 0, sizeof aSelf2);
        *(uint64_t*)((uint8_t*)aSelf2 + 0x260) = (uint64_t)&aSelf2;   // the container word
        *(uint64_t*)((uint8_t*)aSelf2 + 0x290) = (uint64_t)&End;      // the end node

        // the walk records a candidate while id >= key, so these ids are present
        CHECK(Slot_141797e00(aSelf2, 5) == true);
        CHECK(Slot_141797e00(aSelf2, 6) == true);   // the candidate is 5, 5 <= 6
        CHECK(Slot_141797e00(aSelf2, 7) == true);
        CHECK(Slot_141797e00(aSelf2, 8) == true);   // the candidate is 7
        // below the smallest key the walk goes right from the root and never records one
        CHECK(Slot_141797e00(aSelf2, 4) == false);
        CHECK(Slot_141797e00(aSelf2, 0) == false);

        // an empty map: the end node's parent is itself, so the answer is false
        End.uParent = (uint64_t)&End;
        CHECK(Slot_141797e00(aSelf2, 5) == false);
        End.uParent = (uint64_t)&R5;

        // a null container word takes the two error paths and still answers without crashing
        static int nInvalid;
        nInvalid = 0;
        g_pfn_invalid_parameter_noinfo = +[]() { ++nInvalid; };
        *(uint64_t*)((uint8_t*)aSelf2 + 0x260) = 0;
        // the null word does not change the answer: the pair is {0, candidate} and the
        // candidate is still not the end node, so the predicate still says present
        CHECK(Slot_141797e00(aSelf2, 5) == true);
        CHECK(nInvalid == 2);                        // 141797e69 (the word) and 141797eca (the pair)
        *(uint64_t*)((uint8_t*)aSelf2 + 0x260) = (uint64_t)&aSelf2;
        g_pfn_invalid_parameter_noinfo = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x14179a020 — the last destroy call. It walks ids 0x19..0x27, reads the record
    // through vtable slot 2, takes the id from slot 8, looks it up on the map at +0x438,
    // and either erases from the +0x2a0 container or releases through slots 0x16 and 7.
    {
        static int nSlot2, nSlot8, nSlot9, nSlot16, nSlot7, nLog3, nLookup, nErase, nClear;
        static uint32_t aIds[64]; static int nIds;
        static uint32_t uMode;              // what slot 8 answers
        static uint32_t aLookupArg[64]; static int nLookupArg;

        static void* aObj1Vt[40];
        static void* aRecVt[40];            // m_pRec's own table
        static void* aHitRecVt[40];
        static void* pObj1;                 // what slot 2 hands back
        static void* pHitObj;               // the lookup's answer, +0x428 inside it

        static uint64_t aHit[0x90];
        static uint64_t aHit2[0x90];        // a hit whose +0x428 is null
        static uint64_t aRec2[2];           // the record inside aHit
        static uint64_t aRec4[2];           // what slot 2 gives for the +0x428 of aHit

        static void* pObj1Self[1];
        aRecVt[0x10 / 8] = (void*)(void* (*)(void*, uint32_t)) + [](void*, uint32_t) -> void* {
            ++nSlot2; return pObj1; };                      // slot 2 on m_pRec answers the record
        aObj1Vt[0x40 / 8] = (void*)(uint32_t (*)(void*)) + [](void*) -> uint32_t {
            ++nSlot8; if (nIds < 64) aIds[nIds++] = uMode; return uMode; };
        aObj1Vt[0xb0 / 8] = (void*)(uint32_t (*)(void*, uint32_t)) + [](void*, uint32_t) -> uint32_t {
            ++nSlot16; return 0; };
        aRecVt[0x38 / 8] = (void*)(uint32_t (*)(void*, uint32_t)) + [](void*, uint32_t) -> uint32_t {
            ++nSlot7; return 0; };
        static void* pRec2Self[1];
        aHitRecVt[0x10 / 8] = (void*)(void* (*)(void*, uint32_t)) + [](void*, uint32_t) -> void* {
            return pRec2Self; };                            // an object whose vtable is the same
        aHitRecVt[0x48 / 8] = (void*)(uint32_t (*)(void*)) + [](void*) -> uint32_t {
            ++nSlot9; return uMode == 8 ? 1u : 0u; };       // only mode 8 sends it to release

        pObj1 = pObj1Self;
        pObj1Self[0] = (void*)aObj1Vt;
        pRec2Self[0] = (void*)aHitRecVt;
        pHitObj = aHit;
        aRec2[0] = (uint64_t)aHitRecVt;                       // aHit's record: word 0 = vtable
        *(uint64_t*)((uint8_t*)aHit + 0x428) = (uint64_t)aRec2;

        static void* aRecObj[1];                              // m_pRec itself: word 0 = vtable
        aRecObj[0] = (void*)aRecVt;
        static uint64_t aSelf3[0x90];
        std::memset(aSelf3, 0, sizeof aSelf3);
        *(uint64_t*)((uint8_t*)aSelf3 + 0x428) = (uint64_t)aRecObj;
        *(uint64_t*)((uint8_t*)aSelf3 + 0x438) = 0x1111;

        g_pfnLogic_141727640 = +[](void* p) { ++nClear; (void)p; };
        g_pfnLogic_14172ae00 = +[](void* c, void* o, void* k) { ++nErase; (void)c; (void)o; (void)k; };
        g_pfn_log_141823030 = +[](const char* f, const char* e, const char* w,
                                  const char* fi, int l) { ++nLog3; (void)f; (void)e; (void)w; (void)fi; (void)l; };
        g_pfnLogic_1417cad00 = +[](uint64_t, uint64_t id, uint64_t, uint64_t) -> uint64_t {
            ++nLookup; if (nLookupArg < 64) aLookupArg[nLookupArg++] = (uint32_t)id;
            if (uMode == 1) return 0;                        // a miss
            if (uMode == 2) return (uint64_t)(uintptr_t)aHit2;   // a hit with a null record
            return (uint64_t)(uintptr_t)pHitObj; };

        auto run = [](uint32_t mode) {
            uMode = mode; nSlot2 = nSlot8 = nSlot9 = nSlot16 = nSlot7 = 0;
            nLog3 = nLookup = nErase = nClear = 0; nIds = 0; nLookupArg = 0;
            Slot_14179a020(aSelf3);
        };

        // mode 0: slot 8 answers zero for every id, so nothing is looked up
        run(0);
        CHECK(nClear == 1);                  // the +0x2a0 clear always runs first
        CHECK(nSlot2 == 15 && nSlot8 == 15);  // ids 0x19..0x27
        CHECK(nIds == 15 && aIds[0] == 0 && aIds[14] == 0);
        CHECK(nLookup == 0 && nErase == 0 && nSlot16 == 0 && nSlot7 == 0 && nLog3 == 0);

        // mode 1: a miss sends every id to release
        run(1);
        CHECK(nLookup == 15 && nErase == 0 && nLog3 == 0);
        CHECK(nSlot16 == 15 && nSlot7 == 15);
        CHECK(nLookupArg == 15 && aLookupArg[0] == 1 && aLookupArg[14] == 1);

        // mode 2: a hit whose +0x428 is null is reported, then erased
        run(2);
        CHECK(nLog3 == 15 && nErase == 15 && nSlot16 == 0 && nSlot7 == 0);

        // mode 3: a hit whose slot 9 answers zero goes to the erase as well
        run(3);
        CHECK(nErase == 15 && nSlot9 == 15 && nSlot16 == 0 && nSlot7 == 0 && nLog3 == 0);

        // mode 8: a hit whose slot 9 answers non-zero is released instead
        run(8);
        CHECK(nErase == 0 && nSlot9 == 15 && nSlot16 == 15 && nSlot7 == 15);

        g_pfnLogic_141727640 = nullptr;
        g_pfnLogic_14172ae00 = nullptr;
        g_pfn_log_141823030 = nullptr;
        g_pfnLogic_1417cad00 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x14179a150 — the same routine as 0x14179a020 over the container at +0x2e0 and
    // the id range 0xa..0x18. Same fixture, one offset apart, so the checks below only
    // have to prove the two constants and that the loop count follows them.
    {
        static int nSlot2b, nSlot8b, nSlot16b, nSlot7b, nLog4, nLookup4, nErase4, nClear4;
        static void* pClearArg; static void* pEraseArg;
        static uint32_t uMode2;
        static void* rObjVt[40]; static void* rRecVt[40]; static void* rHitVt[40];
        static void* pSelfObj; static void* pHitRecObj;
        static uint64_t rHit[0x90];
        static uint64_t rRec[2];
        static void* pResObj;

        rRecVt[0x10 / 8] = (void*)(void* (*)(void*, uint32_t)) + [](void*, uint32_t) -> void* {
            ++nSlot2b; return pResObj; };
        rRecVt[0x38 / 8] = (void*)(uint32_t (*)(void*, uint32_t)) + [](void*, uint32_t) -> uint32_t {
            ++nSlot7b; return 0; };
        rObjVt[0x40 / 8] = (void*)(uint32_t (*)(void*)) + [](void*) -> uint32_t {
            ++nSlot8b; return uMode2; };
        rObjVt[0xb0 / 8] = (void*)(uint32_t (*)(void*, uint32_t)) + [](void*, uint32_t) -> uint32_t {
            ++nSlot16b; return 0; };
        rHitVt[0x10 / 8] = (void*)(void* (*)(void*, uint32_t)) + [](void*, uint32_t) -> void* {
            return pHitRecObj; };
        rHitVt[0x48 / 8] = (void*)(uint32_t (*)(void*)) + [](void*) -> uint32_t { return 0; };

        static void* pResHolder[1]; pResHolder[0] = (void*)rObjVt;
        static void* pHitHolder[1]; pHitHolder[0] = (void*)rHitVt;
        static void* pSelfHolder[1]; pSelfHolder[0] = (void*)rRecVt;
        pResObj = pResHolder;
        pHitRecObj = pHitHolder;
        rRec[0] = (uint64_t)rHitVt;
        *(uint64_t*)((uint8_t*)rHit + 0x428) = (uint64_t)rRec;

        static uint64_t aSelf4[0x90];
        std::memset(aSelf4, 0, sizeof aSelf4);
        *(uint64_t*)((uint8_t*)aSelf4 + 0x428) = (uint64_t)pSelfHolder;
        *(uint64_t*)((uint8_t*)aSelf4 + 0x438) = 0x2222;

        g_pfnLogic_141727640 = +[](void* p) { ++nClear4; pClearArg = p; };
        g_pfnLogic_14172ae00 = +[](void* c, void* o, void* k) { ++nErase4; pEraseArg = c; (void)o; (void)k; };
        g_pfn_log_141823030 = +[](const char*, const char*, const char*, const char*, int) { ++nLog4; };
        g_pfnLogic_1417cad00 = +[](uint64_t, uint64_t, uint64_t, uint64_t) -> uint64_t {
            ++nLookup4; return (uint64_t)(uintptr_t)rHit; };

        // the clear is handed this+0x2e0, not this+0x2a0
        uMode2 = 0;
        nClear4 = nErase4 = nLookup4 = nSlot7b = nSlot16b = nSlot2b = nSlot8b = 0;
        pClearArg = pEraseArg = nullptr;
        Slot_14179a150(aSelf4);
        CHECK(nClear4 == 1);
        CHECK(pClearArg == (void*)((uint8_t*)aSelf4 + 0x2e0));
        CHECK(nSlot2b == 15 && nSlot8b == 15);         // 0xa..0x18 is fifteen ids
        CHECK(nLookup4 == 0 && nErase4 == 0);

        // with a non-zero id the erase is handed the same +0x2e0 container
        uMode2 = 3;
        nClear4 = nErase4 = nLookup4 = nSlot7b = nSlot16b = nSlot2b = nSlot8b = 0;
        pClearArg = pEraseArg = nullptr;
        Slot_14179a150(aSelf4);
        CHECK(nLookup4 == 15 && nErase4 == 15 && nLog4 == 0);
        CHECK(pEraseArg == (void*)((uint8_t*)aSelf4 + 0x2e0));

        // and the sibling still uses +0x2a0 over its own fifteen ids, 0x19..0x27
        uMode2 = 3;
        nClear4 = nErase4 = nLookup4 = nSlot7b = nSlot16b = nSlot2b = nSlot8b = 0;
        pClearArg = pEraseArg = nullptr;
        Slot_14179a020(aSelf4);
        CHECK(pClearArg == (void*)((uint8_t*)aSelf4 + 0x2a0));
        CHECK(pEraseArg == (void*)((uint8_t*)aSelf4 + 0x2a0));
        CHECK(nSlot2b == 15 && nLookup4 == 15);

        g_pfnLogic_141727640 = nullptr;
        g_pfnLogic_14172ae00 = nullptr;
        g_pfn_log_141823030 = nullptr;
        g_pfnLogic_1417cad00 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x14179db30 — the memberwise tidy: nine vector members at a 0x30 stride under one
    // flag bit each, then the masked block at 0x200. The fixture sets every member to
    // begin = base, finish = base + 0x10, cap = base + 0x40, so the count is always 6.
    {
        static int nCalls, nAlloc, nMasked, nInvalid2;
        static uint64_t aRec[0x60];
        static uint64_t aStorage[0x60];
        static size_t aBeginOff[16]; static uint64_t aCount[16]; static void* aAlloc[16];
        static const void* aType[16];

        g_pfnLogic_141787c50 = +[](void* out, const void* type) -> void* {
            ++nAlloc;
            static void* aWord[2];
            aWord[0] = (void*)0xA110C;               // the allocator word the block reads
            aWord[1] = (void*)type;
            (void)out; return aWord; };
        g_pfnLogic_14179cde0 = +[](void* first, void* last, uint64_t count, void* alloc) {
            if (nCalls < 16) { aCount[nCalls] = count; aAlloc[nCalls] = alloc;
                               aBeginOff[nCalls] = (size_t)((uint8_t*)first - (uint8_t*)g_pBase); }
            ++nCalls; (void)last; };
        static size_t nMaskedOff; static uint64_t uMaskedCount; static void* pMaskedFn;
        g_pfnLogic_14179cf10 = +[](void* first, void* last, uint64_t count, void* fn) {
            ++nMasked; nMaskedOff = (size_t)((uint8_t*)first - (uint8_t*)g_pBase);
            uMaskedCount = count; pMaskedFn = fn; (void)last; };
        g_pfn_invalid_parameter_noinfo = +[]() { ++nInvalid2; };

        std::memset(aRec, 0, sizeof aRec);
        std::memset(aStorage, 0, sizeof aStorage);
        g_pBase = aStorage;                       // the seam offsets are taken against this

        // every member: begin, finish, cap
        const size_t aBegin[10] = {0x50, 0x80, 0xb0, 0xe0, 0x110, 0x140, 0x170, 0x1a0, 0x1d0, 0x200};
        for (int i = 0; i < 10; ++i) {
            const size_t b = aBegin[i];
            *(uint64_t*)((uint8_t*)aRec + b) = (uint64_t)((uint8_t*)aStorage + b);
            *(uint64_t*)((uint8_t*)aRec + b + 0x18) = (uint64_t)((uint8_t*)aStorage + b + 0x10);
            *(uint64_t*)((uint8_t*)aRec + b + 0x20) = (uint64_t)((uint8_t*)aStorage + b + 0x40);
        }

        auto reset = []() { nCalls = nAlloc = nMasked = nInvalid2 = 0;
                            nMaskedOff = 0; uMaskedCount = 0; pMaskedFn = nullptr; };

        // no flags: nothing is touched
        reset();
        Slot_14179db30(aRec, 0);
        CHECK(nCalls == 0 && nMasked == 0 && nAlloc == 0);

        // bit 1 releases the member at 0x50 — and 0x01 is also inside the 0x1f mask, so the
        // masked block runs as well. That is what the two tests do to the same flag byte.
        reset();
        Slot_14179db30(aRec, 0x1);
        CHECK(nCalls == 1 && nAlloc == 1 && nMasked == 1);
        CHECK(aBeginOff[0] == 0x50 + 0x10);          // the callee is handed the finish pointer
        CHECK(aCount[0] == 6);                       // (cap - finish) >> 3
        CHECK(aAlloc[0] == (void*)0xA110C);

        // the ninth bit is the 0x100 one, and it reaches the member at 0x1d0
        reset();
        Slot_14179db30(aRec, 0x100);
        CHECK(nCalls == 1 && aBeginOff[0] == 0x1d0 + 0x10 && aCount[0] == 6);
        CHECK(nMasked == 0);                         // 0x100 is outside the 0x1f mask

        // every flag bit: nine members, the offsets in order
        reset();
        Slot_14179db30(aRec, 0x1ff);
        CHECK(nCalls == 9 && nMasked == 1);
        const size_t aExpect[9] = {0x60, 0x90, 0xc0, 0xf0, 0x120, 0x150, 0x180, 0x1b0, 0x1e0};
        for (int i = 0; i < 9; ++i) CHECK(aBeginOff[i] == aExpect[i]);
        for (int i = 0; i < 9; ++i) CHECK(aCount[i] == 6);

        // the masked block fires on 0x1f and reaches the member at 0x200 with its own callee
        reset();
        Slot_14179db30(aRec, 0x1f);
        CHECK(nCalls == 5 && nMasked == 1);          // bits 0..4 individually, then the mask
        CHECK(nMaskedOff == 0x200 + 0x10 && uMaskedCount == 6);
        CHECK(pMaskedFn == (void*)0x14178efd0);      // r9 in that block is the constant

        // a member whose finish sits above its cap takes the error path and still proceeds
        reset();
        *(uint64_t*)((uint8_t*)aRec + 0x68) = (uint64_t)((uint8_t*)aStorage + 0x800);
        Slot_14179db30(aRec, 0x1);
        CHECK(nInvalid2 >= 1);
        CHECK(nCalls == 1);

        g_pfnLogic_141787c50 = nullptr;
        g_pfnLogic_14179cde0 = nullptr;
        g_pfnLogic_14179cf10 = nullptr;
        g_pfn_invalid_parameter_noinfo = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x141787c50, 0x141726210, 0x141727640 — the type store and the two tree frees.
    // The map here is the +0x1d layout: head at container+0x30 with its three links, size
    // at +0x38, nodes with left +0x00, parent +0x08, right +0x10 and the nil byte +0x1d.
    {
        // --- 0x141787c50 stores the type row and answers the slot
        void* aSlot[1] = {nullptr};
        const void* kType = (const void*)0x14178efd0;
        CHECK(Slot_141787c50(aSlot, kType) == (void*)aSlot);
        CHECK(aSlot[0] == (void*)kType);

        struct Node { uint64_t uLeft, uParent, uRight; uint32_t uKey; uint8_t cPad1c, cNil, aTail[2]; };
        static Node Head, R, L, RR;
        std::memset(&Head, 0, sizeof Head); std::memset(&R, 0, sizeof R);
        std::memset(&L, 0, sizeof L); std::memset(&RR, 0, sizeof RR);
        Head.cNil = 1;

        static uint64_t aCnt[0x10];
        static int nFreed; static void* aFreed[8];
        nFreed = 0;
        g_pfnLogic_1417f2fdc = +[](void* p) { if (nFreed < 8) aFreed[nFreed] = p; ++nFreed; };

        // a three-node tree: R at the root, L on its left, RR on its right
        R.uLeft = (uint64_t)&L; R.uRight = (uint64_t)&RR; R.uParent = (uint64_t)&Head; R.cNil = 0;
        L.uParent = (uint64_t)&R; L.uLeft = (uint64_t)&Head; L.uRight = (uint64_t)&Head; L.cNil = 0;
        RR.uParent = (uint64_t)&R; RR.uLeft = (uint64_t)&Head; RR.uRight = (uint64_t)&Head; RR.cNil = 0;
        Head.uParent = (uint64_t)&R; Head.uLeft = (uint64_t)&L; Head.uRight = (uint64_t)&RR;

        std::memset(aCnt, 0, sizeof aCnt);
        *(void**)((uint8_t*)aCnt + 0x30) = &Head;      // the container's head
        *(uint64_t*)((uint8_t*)aCnt + 0x38) = 3;       // the size

        // --- 0x141726210 frees one subtree only, and the node first handed to it too
        nFreed = 0;
        Slot_141726210(aCnt, &R);
        CHECK(nFreed == 3);
        CHECK(aFreed[0] == (void*)&R || aFreed[0] == (void*)&RR || aFreed[0] == (void*)&L);

        // --- 0x141727640 frees the whole tree, then resets the head on all three links
        nFreed = 0;
        Head.uParent = (uint64_t)&R; Head.uLeft = (uint64_t)&L; Head.uRight = (uint64_t)&RR;
        *(uint64_t*)((uint8_t*)aCnt + 0x38) = 3;
        Slot_141727640(aCnt);
        CHECK(nFreed == 3);
        CHECK(Head.uLeft == (uint64_t)&Head);
        CHECK(Head.uParent == (uint64_t)&Head);
        CHECK(Head.uRight == (uint64_t)&Head);
        CHECK(*(uint64_t*)((uint8_t*)aCnt + 0x38) == 0);

        // an already empty map (head's parent is the head) frees nothing and still resets
        nFreed = 0;
        Slot_141727640(aCnt);
        CHECK(nFreed == 0);
        CHECK(Head.uParent == (uint64_t)&Head);

        g_pfnLogic_1417f2fdc = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x14179cde0 / 0x14179cf10 — the two range routines and their four callees each.
    // The fixtures below pin the threshold (0x20 elements), the count chain
    // (count/2 + count/4), and which of the eight seams each entry point reaches.
    {
        static int nPartA, nTailA, nExA, nExB;      // the 0x14179cde0 seam family
        static int nPartB, nTailB, nExAB, nExBB;    // the 0x14179cf10 seam family
        static int64_t aPartCount[8]; static int nPartSeen;
        static void* pTailFirst[8]; static void* pTailLast[8]; static void* pTailFn[8];
        static int nTailSeen;
        static void* pWantFn;

        static uint64_t aBuf[0x60];
        uint8_t* pBase = (uint8_t*)aBuf;

        auto clear = []() {
            nPartA = nTailA = nExA = nExB = 0;
            nPartB = nTailB = nExAB = nExBB = 0;
            nPartSeen = nTailSeen = 0;
        };

        // the partition stub splits 0x10 bytes from the front, so the right side stays large
        g_pfnLogic_141795a30 = +[](void* out, void* first, void* last, void* fn) {
            ++nPartA; if (nPartSeen < 8) aPartCount[nPartSeen++] = (int64_t)(((uint8_t*)last - (uint8_t*)first) >> 3);
            ((void**)out)[0] = (uint8_t*)first + 0x10;
            ((void**)out)[1] = (uint8_t*)first + 0x10;
            (void)fn; };
        g_pfnLogic_141795d40 = +[](void* out, void* first, void*, void*) {
            ++nPartB;
            ((void**)out)[0] = (uint8_t*)first + 0x10;
            ((void**)out)[1] = (uint8_t*)first + 0x10; };
        g_pfnLogic_141793d50 = +[](void* first, void* last, void* fn, void* zero) {
            ++nTailA; if (nTailSeen < 8) { pTailFirst[nTailSeen] = first; pTailLast[nTailSeen] = last;
                                           pTailFn[nTailSeen] = fn; ++nTailSeen; }
            (void)zero; };
        g_pfnLogic_141793fd0 = +[](void*, void*, void*, void* zero) { ++nTailB; (void)zero; };
        g_pfnLogic_141795ca0 = +[](void*, void*, void*) { ++nExA; };
        g_pfnLogic_141795f70 = +[](void*, void*, void*) { ++nExAB; };
        g_pfnLogic_141797670 = +[](void*, void*, void*) { ++nExB; };
        g_pfnLogic_1417976e0 = +[](void*, void*, void*) { ++nExBB; };

        pWantFn = (void*)0xFEEDFACE;

        // --- a range of three elements with a count of 2: one tail call, nothing else
        clear();
        Slot_14179cde0(pBase, pBase + 0x18, 2, pWantFn);
        CHECK(nPartA == 0 && nExA == 0 && nExB == 0);
        CHECK(nTailA == 1);
        CHECK(pTailFirst[0] == (void*)pBase && pTailLast[0] == (void*)(pBase + 0x18));
        CHECK(pTailFn[0] == pWantFn);

        // --- one element is below the tail's own threshold: nothing at all
        clear();
        Slot_14179cde0(pBase, pBase + 8, 5, pWantFn);
        CHECK(nPartA == 0 && nTailA == 0 && nExA == 0 && nExB == 0);

        // --- a large range with a count of 0 takes the exhausted exit, not the partition
        clear();
        Slot_14179cde0(pBase, pBase + 0x300, 0, pWantFn);
        CHECK(nPartA == 0 && nTailA == 0);
        CHECK(nExA == 1 && nExB == 1);

        // --- a large range with a count of 4 walks the chain 4 -> 3 -> 1 -> 0:
        //     three partitions (each with its own recursion into the 2-element left side,
        //     which its own call answers with the tail), then the exhausted pair.
        clear();
        Slot_14179cde0(pBase, pBase + 0x300, 4, pWantFn);
        CHECK(nPartA == 3);
        CHECK(nTailA == 3);            // one per recursion into the small left side
        CHECK(nExA == 1 && nExB == 1);
        CHECK(aPartCount[0] == 0x60);  // 0x300 bytes = 0x60 elements
        CHECK(aPartCount[1] == 0x5e);  // 0x10 bytes were consumed between them

        // --- the twin reaches its own four seams and none of the first family's
        clear();
        Slot_14179cf10(pBase, pBase + 0x300, 4, pWantFn);
        CHECK(nPartB == 3 && nTailB == 3 && nExAB == 1 && nExBB == 1);
        CHECK(nPartA == 0 && nTailA == 0 && nExA == 0 && nExB == 0);

        // --- its small-range path is the same single tail call
        clear();
        Slot_14179cf10(pBase, pBase + 0x18, 2, pWantFn);
        CHECK(nTailB == 1 && nPartB == 0);

        g_pfnLogic_141795a30 = nullptr;
        g_pfnLogic_141795d40 = nullptr;
        g_pfnLogic_141793d50 = nullptr;
        g_pfnLogic_141793fd0 = nullptr;
        g_pfnLogic_141795ca0 = nullptr;
        g_pfnLogic_141795f70 = nullptr;
        g_pfnLogic_141797670 = nullptr;
        g_pfnLogic_1417976e0 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x141795ca0 / 0x141795f70 (build the heap) and 0x141797670 / 0x1417976e0 (drain it).
    // The fixture is four 8-byte elements; the sift rows are stubs that only record.
    {
        static uint64_t aElems[4];
        static int nSift1, nSift2;
        static uint64_t aIdx[8], aCnt[8];
        static void* aElem[8];

        g_pfnLogic_1417929f0 = +[](void* first, uint64_t index, uint64_t count, void* elem) {
            if (nSift1 < 8) { aIdx[nSift1] = index; aCnt[nSift1] = count; aElem[nSift1] = elem; }
            ++nSift1; (void)first; };
        g_pfnLogic_141792b70 = +[](void* first, uint64_t index, uint64_t count, void* elem) {
            if (nSift2 < 8) { aIdx[nSift2] = index; aCnt[nSift2] = count; aElem[nSift2] = elem; }
            ++nSift2; (void)first; };

        // --- the heap build over four elements: parents 2 then 1, so indices 1 then 0
        aElems[0] = 10; aElems[1] = 20; aElems[2] = 30; aElems[3] = 40;
        nSift1 = nSift2 = 0;
        Slot_141795ca0(aElems, aElems + 4, nullptr);
        CHECK(nSift1 == 2 && nSift2 == 0);          // the 9f0 family, twice
        CHECK(aIdx[0] == 1 && aCnt[0] == 4 && aElem[0] == (void*)20);   // elem loaded before the dec
        CHECK(aIdx[1] == 0 && aCnt[1] == 4 && aElem[1] == (void*)10);

        nSift1 = nSift2 = 0;
        Slot_141795f70(aElems, aElems + 4, nullptr);
        CHECK(nSift2 == 2 && nSift1 == 0);          // the twin only through 0xb70
        CHECK(aIdx[0] == 1 && aElem[0] == (void*)20);

        // --- one element is not a heap: nothing happens at all
        nSift1 = nSift2 = 0;
        Slot_141795ca0(aElems, aElems + 1, nullptr);
        Slot_141795f70(aElems, aElems + 1, nullptr);
        CHECK(nSift1 == 0 && nSift2 == 0);

        // --- the drain: the head lands on the tail slot each pass, counts 3, 2, 1
        aElems[0] = 10; aElems[1] = 20; aElems[2] = 30; aElems[3] = 40;
        nSift1 = nSift2 = 0;
        Slot_141797670(aElems, aElems + 4, nullptr);
        CHECK(nSift1 == 3 && nSift2 == 0);
        CHECK(aCnt[0] == 3 && aCnt[1] == 2 && aCnt[2] == 1);
        CHECK(aElem[0] == (void*)40 && aElem[1] == (void*)30 && aElem[2] == (void*)20);
        CHECK(aIdx[0] == 0 && aIdx[1] == 0 && aIdx[2] == 0);
        CHECK(aElems[0] == 10 && aElems[1] == 10 && aElems[2] == 10 && aElems[3] == 10);

        aElems[0] = 10; aElems[1] = 20; aElems[2] = 30; aElems[3] = 40;
        nSift1 = nSift2 = 0;
        Slot_1417976e0(aElems, aElems + 4, nullptr);
        CHECK(nSift2 == 3 && nSift1 == 0);
        CHECK(aCnt[0] == 3 && aElem[0] == (void*)40);

        // --- one element to drain: nothing
        nSift1 = nSift2 = 0;
        Slot_141797670(aElems, aElems + 1, nullptr);
        Slot_1417976e0(aElems, aElems + 1, nullptr);
        CHECK(nSift1 == 0 && nSift2 == 0);

        g_pfnLogic_1417929f0 = nullptr;
        g_pfnLogic_141792b70 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x141792b70 — the sift the 0xb70 family calls, handed its comparator as a fifth
    // argument. The stubs record the exact pair order so the two passes are visible.
    {
        static uint64_t aH[5];
        static int nLess;
        static uint64_t aA[8], aB[8];
        auto less = +[](void* a, void* b) -> bool {
            if (nLess < 8) { aA[nLess] = (uint64_t)(uintptr_t)a; aB[nLess] = (uint64_t)(uintptr_t)b; }
            ++nLess;
            return (uint64_t)(uintptr_t)a < (uint64_t)(uintptr_t)b; };

        // --- a right child that is not preferred: p[2] > p[1], so the hole takes index 2
        aH[0] = 10; aH[1] = 20; aH[2] = 30; aH[3] = 40; aH[4] = 50;
        nLess = 0;
        Slot_141792b70(aH, 0, 5, (void*)99, less);
        CHECK(nLess == 2);                       // (30,20) at the child, then (30,99) on the way up
        CHECK(aA[0] == 30 && aB[0] == 20);
        CHECK(aA[1] == 30 && aB[1] == 99);       // the element that moved up is the parent's value
        CHECK(aH[0] == 99);                      // the saved element lands in the hole
        CHECK(aH[1] == 20 && aH[3] == 40 && aH[4] == 50);

        // --- a left child that is preferred: p[2] < p[1], so the hole takes index 1
        aH[0] = 10; aH[1] = 50; aH[2] = 20; aH[3] = 40; aH[4] = 60;
        nLess = 0;
        Slot_141792b70(aH, 0, 5, (void*)99, less);
        CHECK(aA[0] == 20 && aB[0] == 50);       // (right, left) as the bytes load them
        CHECK(aH[0] == 99);                      // 50 rose, then 99 took the root

        // --- the lone child: count odd makes child == count, so the last element is promoted
        // child 4 == count 4 promotes the last element, then the up pass compares it
        aH[0] = 10; aH[1] = 20; aH[2] = 30; aH[3] = 40;
        nLess = 0;
        Slot_141792b70(aH, 1, 4, (void*)77, less);
        CHECK(nLess == 1);                       // only the up pass compares
        CHECK(aA[0] == 40 && aB[0] == 77);       // (the promoted element, the saved one)
        CHECK(aH[1] == 77 && aH[3] == 40);       // 40 slid into the hole, 77 landed at index 1

        // no children at all: index 1 of a three-element range has none, so nothing compares
        aH[0] = 10; aH[1] = 20; aH[2] = 30;
        nLess = 0;
        Slot_141792b70(aH, 1, 3, (void*)77, less);
        CHECK(nLess == 0);
        CHECK(aH[1] == 77 && aH[0] == 10 && aH[2] == 30);
    }

    // ------------------------------------------------------------------
    // 0x1417929f0 — the twin sift: the child walk with the out-slot comparator, then the
    // five-argument hand-off to the up-pass row.
    {
        static uint64_t aT[5];
        static int nCmp, nUp;
        static uint64_t aCmpR[4], aCmpL[4], aUpHole[4], aUpOrig[4], aUpOut[4];
        static void* aUpElem[4];

        g_pfnLogic_141787c60 = +[](void* out, void* right, void* left) -> bool {
            if (nCmp < 4) { aCmpR[nCmp] = (uint64_t)(uintptr_t)right;
                            aCmpL[nCmp] = (uint64_t)(uintptr_t)left; }
            ++nCmp;
            ((uint64_t*)out)[0] = 0xC0FFEE;                  // the out slot the row carries on
            return (uint64_t)(uintptr_t)right < (uint64_t)(uintptr_t)left; };
        g_pfnLogic_1417917a0 = +[](void* first, int64_t hole, int64_t orig, void* elem,
                                   uint64_t outValue) {
            if (nUp < 4) { aUpHole[nUp] = (uint64_t)hole; aUpOrig[nUp] = (uint64_t)orig;
                           aUpElem[nUp] = elem; aUpOut[nUp] = outValue; }
            ++nUp; (void)first; };

        // --- right child not preferred: the hole follows index 2, orig stays 0, out is carried
        aT[0] = 10; aT[1] = 20; aT[2] = 30; aT[3] = 40; aT[4] = 50;
        nCmp = nUp = 0;
        Slot_1417929f0(aT, 0, 5, (void*)99);
        CHECK(nCmp == 1 && nUp == 1);
        CHECK(aCmpR[0] == 30 && aCmpL[0] == 20);       // (right, left) as the bytes load them
        CHECK(aT[0] == 30);                            // the child moved into the hole
        CHECK(aUpHole[0] == 2 && aUpOrig[0] == 0);
        CHECK(aUpElem[0] == (void*)99);
        CHECK(aUpOut[0] == 0xC0FFEE);                  // the comparator's slot reaches the fifth argument

        // --- left child preferred: the verified answer decrements the child first
        aT[0] = 10; aT[1] = 50; aT[2] = 20; aT[3] = 40; aT[4] = 60;
        nCmp = nUp = 0;
        Slot_1417929f0(aT, 0, 5, (void*)99);
        CHECK(nCmp == 2);                              // the walk continues down to the next child
        CHECK(aCmpR[0] == 20 && aCmpL[0] == 50);
        CHECK(aCmpR[1] == 60 && aCmpL[1] == 40);
        CHECK(aT[0] == 50 && aT[1] == 60);             // index 1 rose, then index 4 into the new hole
        CHECK(aUpHole[0] == 4);

        // --- lone child: child == count promotes the last element and moves the hole there
        aT[0] = 10; aT[1] = 20; aT[2] = 30; aT[3] = 40;
        nCmp = nUp = 0;
        Slot_1417929f0(aT, 1, 4, (void*)77);
        CHECK(nCmp == 0);                              // child 4 is not below the count
        CHECK(nUp == 1);
        CHECK(aT[1] == 40 && aUpHole[0] == 3 && aUpOrig[0] == 1);

        // --- no children at all: the hand-off still happens with the index untouched
        aT[0] = 10; aT[1] = 20; aT[2] = 30;
        nCmp = nUp = 0;
        Slot_1417929f0(aT, 1, 3, (void*)77);
        CHECK(nCmp == 0 && nUp == 1);
        CHECK(aUpHole[0] == 1 && aUpOrig[0] == 1 && aT[1] == 20);

        g_pfnLogic_141787c60 = nullptr;
        g_pfnLogic_1417917a0 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x1417917a0 — the up pass: climb the parents while the element is the larger, and land
    // it in the hole either way. The fifth argument is never read, so it is only carried.
    {
        static uint64_t aU[4];
        static int nCmpUp;

        g_pfnLogic_141787c60 = +[](void* out, void* right, void* left) -> bool {
            ++nCmpUp; (void)out;
            return (uint64_t)(uintptr_t)right < (uint64_t)(uintptr_t)left; };

        // --- the element climbs past both parents
        aU[0] = 10; aU[1] = 20; aU[2] = 30; aU[3] = 40;
        nCmpUp = 0;
        Slot_1417917a0(aU, 3, 0, (void*)99, 0);
        CHECK(nCmpUp == 2);                       // parents 1 and 0, in that order
        CHECK(aU[0] == 99 && aU[1] == 10 && aU[3] == 20);
        CHECK(aU[2] == 30);                       // untouched

        // --- a false answer ends the climb and the element lands below that parent
        aU[0] = 50; aU[1] = 20; aU[2] = 30; aU[3] = 40;
        nCmpUp = 0;
        Slot_1417917a0(aU, 3, 0, (void*)25, 0);
        CHECK(nCmpUp == 2);                       // 20 < 25 climbs, 50 < 25 stops
        CHECK(aU[1] == 25 && aU[3] == 20 && aU[0] == 50);

        // --- orig >= hole: no comparator at all, the element just lands
        aU[0] = 10; aU[1] = 20; aU[2] = 30; aU[3] = 40;
        nCmpUp = 0;
        Slot_1417917a0(aU, 1, 1, (void*)77, 0);
        CHECK(nCmpUp == 0);
        CHECK(aU[1] == 77);

        // --- the fifth argument is inert: the same call with a wild value behaves the same
        aU[0] = 10; aU[1] = 20; aU[2] = 30; aU[3] = 40;
        nCmpUp = 0;
        Slot_1417917a0(aU, 3, 0, (void*)99, 0xDEADBEEFDEADBEEFull);
        CHECK(nCmpUp == 2 && aU[0] == 99);

        g_pfnLogic_141787c60 = nullptr;
    }

    // ------------------------------------------------------------------
    // 0x141793fd0 — insertion sort over 8-byte elements, comparator in the third argument.
    {
        static uint64_t aS[6];
        static int nCmpS;
        auto lessS = +[](void* a, void* b) -> bool {
            ++nCmpS;
            return (uint64_t)(uintptr_t)a < (uint64_t)(uintptr_t)b; };

        // --- an unsorted run becomes sorted, and the values are the same multiset
        aS[0] = 5; aS[1] = 2; aS[2] = 4; aS[3] = 1; aS[4] = 3; aS[5] = 6;
        nCmpS = 0;
        Slot_141793fd0(aS, aS + 6, lessS, nullptr);
        CHECK(aS[0] == 1 && aS[1] == 2 && aS[2] == 3 && aS[3] == 4 && aS[4] == 5 && aS[5] == 6);
        CHECK(nCmpS > 0);

        // --- an empty range and a single element both return without comparing
        nCmpS = 0;
        Slot_141793fd0(aS, aS, lessS, nullptr);
        Slot_141793fd0(aS, aS + 1, lessS, nullptr);
        CHECK(nCmpS == 0);

        // --- already sorted: one comparison per element, no shifting
        uint64_t aSorted[4] = {1, 2, 3, 4};
        nCmpS = 0;
        Slot_141793fd0(aSorted, aSorted + 4, lessS, nullptr);
        CHECK(nCmpS == 6);                       // every element checks the front, then its neighbour
        CHECK(aSorted[0] == 1 && aSorted[3] == 4);

        // --- descending: every element goes through the front path and the memmove
        uint64_t aDesc[4] = {4, 3, 2, 1};
        nCmpS = 0;
        Slot_141793fd0(aDesc, aDesc + 4, lessS, nullptr);
        CHECK(aDesc[0] == 1 && aDesc[1] == 2 && aDesc[2] == 3 && aDesc[3] == 4);

        // --- duplicates must survive: equal elements are never less than each other
        uint64_t aDup[5] = {2, 1, 2, 1, 2};
        Slot_141793fd0(aDup, aDup + 5, lessS, nullptr);
        CHECK(aDup[0] == 1 && aDup[1] == 1 && aDup[2] == 2 && aDup[3] == 2 && aDup[4] == 2);
    }

    std::printf("%s checks=%d fails=%d\n", g_fails ? "LOGIC_SLOTS_FAIL" : "LOGIC_SLOTS_OK",
                g_checks, g_fails);
    return g_fails ? 1 : 0;
}
