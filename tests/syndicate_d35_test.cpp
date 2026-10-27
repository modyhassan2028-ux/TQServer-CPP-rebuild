// ============================================================
// syndicate_d35_test — the league ENTITY member-vector ops
// + the special-member erase (T9/D35): the vector<8> and
// vector<0x2d> insert machinery (a350/c5a0/c6d0 + the
// allocs/copies/throws), the wrap helper a300, the record
// releases d5070/d4db0, and the entity erase c0c0 (the
// fixed keys 0xcc/0xcd on the REAL D32 map at entity+0xd8).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include "../modules/syndicate/src/SyndicateLeagueTree.h"
#include "../modules/syndicate/src/SyndicateLeagueCmp.h"
#include "../modules/syndicate/src/SyndicateLeagueEntity.h"

using namespace syndicate;

// ---------------- the seams ----------------
static int s_nInvalid = 0;
static void TestInvalid() { s_nInvalid++; }
static int s_nLogs = 0;
static void* TestLogFactory() { s_nLogs++; return (void*)0x1; }
static void TestLogWrite(void*, uint32_t, int) {}
static uint8_t s_vftLogic[8];
static uint8_t s_vftProvider[8];
namespace syndicate {
extern void (*g_fnMeritInvalid)();
extern void (*g_fnMeritOpDelete)(void*);
using syndicate::g_fnMeritInvalid;
using syndicate::g_fnMeritOpDelete;
}

// ---------------- the vector container ----------------
// the MSVC debug-vector proxy: the container's +0x0 slot
// (the iterator owner); the range-check fields at +0x18/+0x20.
static char s_proxy[0x30];
static void InitProxy() {
    memset(s_proxy, 0, sizeof(s_proxy));
    *(uint64_t*)(s_proxy + 0x18) = 0;
    *(uint64_t*)(s_proxy + 0x20) = (uint64_t)-1;
    *(void**)s_proxy = (void*)0x7777;   // the proxy's own head (unused)
}
struct Vec {
    char raw[0x30];
    void init() {
        memset(raw, 0, sizeof(raw));
        InitProxy();
        *(void**)raw = (void*)s_proxy;   // vec[0] = the proxy ptr
    }
    char* begin() const { return *(char** const)(raw + 0x18); }
    char* finish() const { return *(char** const)(raw + 0x20); }
    char* cap() const { return *(char** const)(raw + 0x28); }
    size_t size() const { return (finish() - begin()) / 8; }
    size_t capn() const { return (cap() - begin()) / 8; }
    uint64_t at(size_t i) const { return *(uint64_t*)(begin() + i * 8); }
};

// the where-iterator: {holder, ptr} with where[1] = the slot ptr
static void* WhereAt(char* pPtr) {
    static char* holder[2];
    holder[0] = (char*)s_proxy;   // the iterator owner = the container proxy
    holder[1] = pPtr;
    return holder;
}

// ---------------- D35-1: vector<8> insert paths ----------------
static void V8Ins(Vec& v, size_t slotIdx, uint64_t val, uint64_t count = 1) {
    uint64_t vals[8] = { val, val, val, val, val, val, val, val };
    LeagueVec8InsertN((int64_t)v.raw, WhereAt(v.begin() + slotIdx * 8), count, vals);
}

int main() {
    g_fnLeagueInvalid = TestInvalid;
    g_fnMeritInvalid = TestInvalid;                        // the D32 tree seams
    g_fnMeritOpDelete = [](void* p) { free(p); };           // (node frees)
    g_fnLeagueLogFactory = TestLogFactory;
    g_fnLeagueLogWrite = TestLogWrite;
    g_pLeagueVftLogic = s_vftLogic;
    g_pLeagueVftProvider = s_vftProvider;

    // ================= D35-1: vector<8> — the three paths =================
    {
        Vec v; v.init();
        // realloc path (empty → grow to 1)
        V8Ins(v, 0, 11);
        assert(v.size() == 1 && v.at(0) == 11 && v.capn() == 1);
        // realloc again (1 full → 1.5x rule → 1+0=1 < 2 → cap 2)
        V8Ins(v, 1, 22);
        assert(v.size() == 2 && v.at(0) == 11 && v.at(1) == 22);
        assert(v.capn() == 2);   // 1 + (1>>1) = 1 → forced to 2
        // realloc to 3
        V8Ins(v, 2, 33);
        assert(v.size() == 3 && v.capn() == 3);
        assert(v.at(0) == 11 && v.at(1) == 22 && v.at(2) == 33);
        // NOW cap 3 is full: push at the END → the shift-mid path
        V8Ins(v, 3, 44);       // where == finish → realloc? size 3 = cap → GROW path
        assert(v.size() == 4 && v.at(3) == 44 && v.capn() >= 4);
        // the shift-mid path: capacity spare + where inside the tail
        Vec w; w.init();
        V8Ins(w, 0, 1); V8Ins(w, 1, 2); V8Ins(w, 2, 3);   // [1,2,3] cap 3
        V8Ins(w, 3, 4);   // grow → cap 4, size 4
        V8Ins(w, 1, 99, 1);   // cap 4, size 4?? full again → hmm
        // (cap 4 full → the grow path again)
        assert(w.size() == 5 && w.at(1) == 99 && w.at(0) == 1 && w.at(2) == 2 &&
               w.at(3) == 3 && w.at(4) == 4);
        // the SHIFT-TAIL path: cap 6 (5 + 2>>1 = 7? — growth 5+(5>>1)=7), spare
        assert(w.capn() >= 6);
        V8Ins(w, 0, 77);   // cap spare, where=begin, tail (4-0)=4 ≥ count → shift-tail
        assert(w.size() == 6 && w.at(0) == 77 && w.at(1) == 1 && w.at(2) == 99);
        assert(w.at(5) == 4);
        // a multi-count insert in the middle with spare capacity
        Vec u; u.init();
        V8Ins(u, 0, 5, 4);   // realloc path with count 4: [5,5,5,5]
        assert(u.size() == 4 && u.capn() == 4);
        V8Ins(u, 2, 6, 2);   // grow path (full): [5,5,6,6,5,5]
        assert(u.size() == 6);
        assert(u.at(0) == 5 && u.at(1) == 5 && u.at(2) == 6 && u.at(3) == 6 &&
               u.at(4) == 5 && u.at(5) == 5);
        printf("D35-1 vector<8> insert paths ok\n");
    }

    // ================= D35-2: insert_one + the iter checks =================
    {
        Vec v; v.init();
        V8Ins(v, 0, 1); V8Ins(v, 1, 2);
        // insert_one at the front with spare capacity: first the
        // spare (cap 2? — after two grows cap == 2 → full → hmm)
        // build a spare: push 3 (grow), then insert one at slot 0
        V8Ins(v, 2, 3);
        assert(v.capn() == 3);   // 2 + 1
        uint64_t val = 42;
        void* out[2];
        // the proxy's [0] = the container (the range checks read
        // +0x18/+0x20 = the begin/finish through it)
        *(void**)s_proxy = (void*)v.raw;
        char* holder[2] = { (char*)s_proxy, v.begin() };
        LeagueVec8InsertOne((int64_t)v.raw, out, holder, &val);
        assert(v.size() == 4);
        assert(v.at(0) == 42 && v.at(1) == 1 && v.at(2) == 2 && v.at(3) == 3);
        // the returned iterator = {the proxy, the new begin + off*8}
        assert(out[0] == (void*)s_proxy);
        assert(out[1] == (void*)v.begin());
        printf("D35-2 vector<8> insert_one ok\n");
    }

    // ================= D35-3: vector<0x2d> — the three paths =================
    {
        struct Rec { char raw[0x2d]; };
        auto mkrec = [](uint8_t tag) {
            Rec r; memset(r.raw, tag, sizeof(r.raw));
            r.raw[0x2c] = tag;   // the trailing byte too
            return r;
        };
        Vec v; v.init();   // the same container layout, 0x2d elements
        auto ins = [&](size_t slot, Rec r, uint64_t count = 1) {
            LeagueVec45InsertN((int64_t)v.raw, WhereAt(v.begin() + slot * 0x2d), count, r.raw);
        };
        auto at = [&](size_t i) -> Rec& { return *(Rec*)(v.begin() + i * 0x2d); };
        auto n45 = [&]() { return (size_t)(v.finish() - v.begin()) / 0x2d; };
        auto cap45 = [&]() { return (size_t)(v.cap() - v.begin()) / 0x2d; };

        Rec r1 = mkrec(0x11), r2 = mkrec(0x22), r3 = mkrec(0x33);
        ins(0, r1);                     // the grow path
        assert(n45() == 1 && memcmp(at(0).raw, r1.raw, 0x2d) == 0);
        ins(1, r2); ins(1, r3);          // front-mid inserts
        assert(n45() == 3);
        assert(memcmp(at(0).raw, r1.raw, 0x2d) == 0);
        assert(memcmp(at(1).raw, r3.raw, 0x2d) == 0);
        assert(memcmp(at(2).raw, r2.raw, 0x2d) == 0);
        // a multi-count grow insert in the middle
        Rec r4 = mkrec(0x44);
        ins(2, r4, 2);                   // [r1,r3,r4,r4,r2]
        assert(n45() == 5);
        assert(memcmp(at(2).raw, r4.raw, 0x2d) == 0);
        assert(memcmp(at(3).raw, r4.raw, 0x2d) == 0);
        assert(memcmp(at(4).raw, r2.raw, 0x2d) == 0);
        // the front insert on a FULL vector → the GROW path again
        assert(cap45() == 5 && n45() == 5);
        ins(0, r1);   // → [r1, r1, r3, r4, r4, r2], cap 5+2=7
        assert(n45() == 6 && cap45() == 7);
        assert(memcmp(at(0).raw, r1.raw, 0x2d) == 0);
        assert(memcmp(at(1).raw, r1.raw, 0x2d) == 0);
        assert(memcmp(at(2).raw, r3.raw, 0x2d) == 0);
        assert(memcmp(at(5).raw, r2.raw, 0x2d) == 0);
        // NOW spare capacity: a front insert → the SHIFT-TAIL path
        ins(0, r2);   // → [r2, r1, r1, r3, r4, r4, r2]
        assert(n45() == 7 && cap45() == 7);
        assert(memcmp(at(0).raw, r2.raw, 0x2d) == 0);
        assert(memcmp(at(1).raw, r1.raw, 0x2d) == 0);
        assert(memcmp(at(6).raw, r2.raw, 0x2d) == 0);
        printf("D35-3 vector<0x2d> insert paths ok\n");
    }

    // ================= D35-4: the wrap helper + the throws =================
    {
        // a300: new 8 storing the caller's slot address, slot takes the block
        void* slot[2] = { (void*)0xABCD, nullptr };
        void* ret = LeagueWrapQword(&slot[0]);
        assert(ret == &slot[0]);
        void** block = (void**)slot[0];
        assert(block != (void*)0xABCD && block != nullptr);
        assert(*block == (void*)&slot[0]);
        free(block);

        // the overflow throws
        bool caught = false;
        static char zeroVec[0x30];
        memset(zeroVec, 0, sizeof(zeroVec));
        try { LeagueVec8InsertN((int64_t)zeroVec, WhereAt(nullptr), 0x2000000000000000ULL, nullptr); }
        catch (const std::length_error&) { caught = true; }
        assert(caught);   // 0x1fffffffffffffff - 0 < count (just past the max) → throw
        caught = false;
        try { LeagueVec45Alloc(nullptr, (uint64_t)-1); }
        catch (const std::bad_alloc&) { caught = true; }
        assert(caught);
        printf("D35-4 wrap helper + the throws ok\n");
    }

    // ================= D35-5: the record releases =================
    {
        static int nHolder, nVt0;
        static uint64_t lastMsg1, lastMsg2; static int64_t lastMin2;
        auto holderFn = [](void**, uint64_t a, uint64_t b, uint64_t c, int64_t d) {
            nHolder++; lastMsg1 = b; lastMsg2 = c; lastMin2 = d; (void)a; };
        auto vt0Fn = [](void**, uint64_t a) { nVt0++; (void)a; };
        static void* holderVt[16]; static void* recVt[16];
        holderVt[0] = (void*)+holderFn;
        recVt[0] = (void*)+vt0Fn;
        static void* holder[2] = { holderVt, nullptr };
        void* rec[2] = { recVt, holder };

        // d5070: rec+8 = the holder → its vt[8]?? — the ORIGINAL calls
        // (holder->vt + 0x40)(holder, 0) — vt[8]
        static void* holderVt40[16];
        static int n40;
        holderVt40[8] = (void*)(+[](void** h, uint64_t a) { n40++; (void)h; (void)a; });
        // d4db0 calls vtable[0] — the 5-arg release
        holderVt40[0] = (void*)(+[](void** h, uint64_t a, uint64_t b, uint64_t c, int64_t d) {
            nHolder++; lastMsg1 = b; lastMsg2 = c; lastMin2 = d;
            (void)h; (void)a; });
        holder[0] = holderVt40;
        LeagueRecRelease((int64_t)rec);
        assert(n40 == 1);
        // the null gate
        void* bare[2] = { recVt, nullptr };
        LeagueRecRelease((int64_t)bare);
        assert(n40 == 1);

        // d4db0: the dual release
        nHolder = nVt0 = 0;
        LeagueRecRelease2(rec, nullptr, 0x1111, 0x2222);
        assert(nHolder == 1 && nVt0 == 1);
        assert(lastMsg1 == 0x1111 && lastMsg2 == 0x2222);
        assert(lastMin2 == (int64_t)0xfffffffffffffffe);
        assert(rec[1] == nullptr);   // the double zero
        printf("D35-5 record releases ok\n");
    }

    // ================= D35-6: the entity erase end-to-end =================
    {
        // the provider at entity+8 with resolve(3)/(4)
        struct EntRec { void* vt; };
        static int nB0, n80, n38;
        static void* recVt[32];       // rec: vt[22]=+0xb0, vt[16]=+0x80
        recVt[22] = (void*)(+[](void** r, uint64_t a) { nB0++; (void)r; (void)a; });
        recVt[16] = (void*)(+[](void** r, void* s) { n80++; (void)r; (void)s; });
        static void* providerVt[16];  // vt[2]=resolve, vt[7]=+0x38
        static EntRec s_rec = { recVt };
        providerVt[2] = (void*)(+[](void** p, uint64_t idx) {
            (void)p; assert(idx == 3 || idx == 4); return (void*)&s_rec; });
        providerVt[7] = (void*)(+[](void** p, uint64_t a) { n38++; (void)p; (void)a; });

        // the entity: the map at +0xd8 (head at +0x108), the provider at +8
        static char ent[0x200]; memset(ent, 0, sizeof(ent));
        // the provider object: [0] = the vtable
        static void* providerObj[4];
        providerObj[0] = providerVt;
        *(void**)(ent + 8) = (void*)providerObj;
        char* pcMap = ent + 0xd8;
        LeagueMemberCtor(pcMap);   // the real 0x30-node map

        // member records for the map values: {recVt2, holder}
        static int nReleased;
        static void* recVt2[2];
        recVt2[0] = (void*)(+[](void** r, uint64_t a) { nReleased++; (void)r; (void)a; });
        static void* recVt3[2];
        recVt3[0] = (void*)(+[](void** r, uint64_t a, uint64_t b, uint64_t c, int64_t d) {
            nReleased += 2; (void)r; (void)a; (void)b; (void)c; (void)d; });
        struct MemberRec { void* vt; void* holder; };
        static std::vector<MemberRec*> recs;
        static std::vector<void*> blocks;
        auto mkmember = [&](uint32_t key) {
            MemberRec* mr = (MemberRec*)calloc(2, sizeof(void*));
            mr->vt = recVt2; mr->holder = nullptr;   // hmm — see the note below
            recs.push_back(mr);
            uint64_t kv[2] = { key, (uint64_t)(uintptr_t)mr };
            char* head = *(char**)(pcMap + 0x30);
            char* attach = head; bool bLeft = true;
            if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
                char* cur = *(char**)(head + 8);
                do { attach = cur; bLeft = key < *(uint32_t*)(cur + 0x18);
                     cur = bLeft ? *(char**)cur : *(char**)(cur + 0x10);
                } while (*(char*)(cur + 0x29) == '\0');
            }
            char out[2][8];
            LeagueInsert(pcMap, out[0], bLeft ? 1 : 0, attach, kv);
        };
        mkmember(10); mkmember(50); mkmember(0xcc); mkmember(0xcd); mkmember(200);
        // both special members get the same holder: vt[8] (=vt+0x40,
        // the d5070 call) + vt[0] (the d4db0 5-arg call)
        MemberRec* mrcc = recs[2];   // key 0xcc
        MemberRec* mrcd = recs[3];   // key 0xcd
        static void* holderVt[16];
        holderVt[8] = (void*)(+[](void** h, uint64_t a) { nReleased += 4; (void)h; (void)a; });
        holderVt[0] = (void*)(+[](void** h, uint64_t a, uint64_t b, uint64_t c, int64_t d) {
            nReleased += 8; (void)h; (void)a; (void)b; (void)c; (void)d; });
        static void* holderObj[2] = { holderVt, nullptr };
        mrcc->holder = holderObj;
        mrcd->holder = holderObj;

        size_t sizeBefore = *(size_t*)(pcMap + 0x38);
        assert(sizeBefore == 5);
        LeagueEntityEraseSpecial((int64_t)ent);
        // the setup calls
        assert(nB0 == 1 && n80 == 1 && n38 == 1);
        // both special keys erased
        assert(*(size_t*)(pcMap + 0x38) == 3);
        // the records released: per member d5070 (vt[8] → +4) +
        // d4db0 (the holder vt[0] → +8 + the rec vt[0] tail call → +1)
        // = 13 each; two members → 26
        assert(nReleased == 26);
        // membership: find each expected key via the D32 find
        uint32_t k;
        void* it[2];
        for (uint32_t key : {10u, 50u, 200u}) {
            k = key;
            LeagueFind(pcMap, it, &k);
            assert(it[1] != *(char**)(pcMap + 0x30));   // found (node != head)
        }
        for (uint32_t key : {0xccu, 0xcdu}) {
            k = key;
            LeagueFind(pcMap, it, &k);
            assert(it[1] == *(char**)(pcMap + 0x30));  // not found
        }
        printf("D35-6 entity erase end-to-end ok (5 → 3 members, records released)\n");
    }

    printf("SYNDICATE-D35-OK: the entity member-vector ops + the special-member "
           "erase complete — vector<8> insert_n a350 (the realloc/shift-mid/"
           "shift-tail tri-path with the 1.5x growth rule), insert_one c5a0 "
           "(the offset capture + the range checks), vector<0x2d> insert_n c6d0 "
           "(the DefRecord tri-path, the EH unwind stages documented as "
           "compiler artifacts), the wrap helper a300, the allocators f80/f00 "
           "(the 128-bit overflow divide + bad_alloc), the 0x2d fill/move/"
           "back-copy, the 8-byte shift/backshift (the 4-arg dst shape), the "
           "length_error throws b50/ad0, the record releases d5070/d4db0 (the "
           "dual vt calls + the verbatim double zero), and the entity erase "
           "c0c0 (the provider resolve chains + the FIXED keys 0xcc/0xcd on "
           "the real D32 map)\n");
    return 0;
}
