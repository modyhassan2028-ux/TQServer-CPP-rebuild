// ============================================================================
// cqbase_d50 — the counted node allocators, the name-node string destructor, the
//   lower_bound walk (head->parent is the root, nil byte +0x41) and the two step wrappers.
// ============================================================================
#include "modules/syndicate/src/synnodescal.h"
#include "modules/syndicate/src/synrangeB.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
static int g_nInvalid = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static void HookInvalid() { ++g_nInvalid; }

namespace {

// a name node: left +0x00, parent +0x08, right +0x10, std::string key at +0x18, nil +0x41
struct NameNode {
    std::vector<uint8_t> buf;
    NameNode() : buf(0x48, 0) { new (buf.data() + 0x18) std::string(); }
    ~NameNode() { ((std::string*)(buf.data() + 0x18))->~basic_string(); }
    uint8_t* a() { return buf.data(); }
    void Key(const char* s) { *(std::string*)(a() + 0x18) = s; }
    std::string& K() { return *(std::string*)(a() + 0x18); }
    void L(NameNode* p) { *(void**)(a() + 0x00) = p ? p->a() : nullptr; }
    void P(NameNode* p) { *(void**)(a() + 0x08) = p ? p->a() : nullptr; }
    void R(NameNode* p) { *(void**)(a() + 0x10) = p ? p->a() : nullptr; }
    void Nil() { a()[0x41] = 1; }
};

}  // namespace

int main() {
    ::syndicate::g_fnInvalidParam = &HookInvalid;

    // ---- the counted allocators: the byte sizes are 0x30 / 0x48 / 0x28
    {
        void* p30 = SynNodeNewCount30((void*)3);
        void* p48 = SynNodeNewCount48((void*)2);
        void* p28 = SynNodeNewCount28((void*)5);
        CHECK(p30 != nullptr);
        CHECK(p48 != nullptr);
        CHECK(p28 != nullptr);
        // ASan checks the extent: writing the full element range must stay legal
        std::memset(p30, 0xAA, 3 * 0x30);
        std::memset(p48, 0xBB, 2 * 0x48);
        std::memset(p28, 0xCC, 5 * 0x28);
        CHECK(((uint8_t*)p30)[3 * 0x30 - 1] == 0xAA);
        CHECK(((uint8_t*)p48)[2 * 0x48 - 1] == 0xBB);
        CHECK(((uint8_t*)p28)[5 * 0x28 - 1] == 0xCC);
        ::operator delete(p30);
        ::operator delete(p48);
        ::operator delete(p28);
        // a zero count still allocates (the div is skipped, operator new(0) runs)
        void* pZero = SynNodeNewCount30(nullptr);
        CHECK(pZero != nullptr);
        ::operator delete(pZero);
        // an overflowing count must throw bad_alloc, not allocate
        bool bThrew = false;
        try {
            SynNodeNewCount30((void*)(UINT64_MAX / 0x10));
        } catch (const std::bad_alloc&) {
            bThrew = true;
        }
        CHECK(bThrew);
    }

    // ---- the string destructor frees what the key owns
    {
        uint8_t* pRaw = (uint8_t*)::operator new(0x48);
        std::memset(pRaw, 0, 0x48);
        std::string* pKey = new (pRaw + 0x18) std::string(64, 'x');   // heap-backed
        CHECK(pKey->size() == 64);
        SynNodeStringDtor(pRaw);                                     // ASan sees the release
        ::operator delete(pRaw);
    }

    // ---- lower_bound over a real name tree: b, d, f, h
    {
        NameNode nHead, nNil, nB, nD, nF, nH;
        nNil.Nil();
        nHead.Nil();
        nB.Key("b"); nD.Key("d"); nF.Key("f"); nH.Key("h");
        nHead.P(&nD);                       // head->parent is the root
        nD.L(&nB); nD.R(&nF); nD.P(&nHead);
        nB.L(&nNil); nB.R(&nNil); nB.P(&nD);
        nF.L(&nNil); nF.R(&nH); nF.P(&nD);
        nH.L(&nNil); nH.R(&nNil); nH.P(&nF);

        uint8_t aOwner[0x40];
        std::memset(aOwner, 0, sizeof(aOwner));
        *(void**)(aOwner + 0x30) = nHead.a();

        struct Case { const char* key; uint8_t* pWant; };
        Case aCases[] = {
            {"a", nB.a()},   // nothing is smaller: the leftmost
            {"b", nB.a()},   // exact
            {"c", nD.a()},
            {"d", nD.a()},
            {"e", nF.a()},
            {"g", nH.a()},
            {"h", nH.a()},
            {"i", nHead.a()},  // past the last: the head itself
        };
        for (const Case& c : aCases) {
            std::string sKey(c.key);
            CHECK(SynMapLowerBoundName(aOwner, &sKey) == c.pWant);
        }
        // an empty tree answers the head
        NameNode nEmptyHead, nEmptyNil;
        nEmptyNil.Nil();
        nEmptyHead.Nil();
        nEmptyHead.P(&nEmptyNil);
        *(void**)(aOwner + 0x30) = nEmptyHead.a();
        std::string sKey("z");
        CHECK(SynMapLowerBoundName(aOwner, &sKey) == nEmptyHead.a());
    }

    // ---- the two step wrappers hand the iterator back
    {
        uint8_t aSent[0x50];
        std::memset(aSent, 0, sizeof(aSent));
        aSent[0x29] = 1;                 // the sentinel: the step takes its left link
        aSent[0x41] = 1;
        uint8_t aNext[0x50];
        std::memset(aNext, 0, sizeof(aNext));   // a real node, both nil bytes clear
        *(void**)(aSent + 0x00) = aNext;
        void* aIt[2] = {(void*)0x1111, aSent};
        g_nInvalid = 0;
        CHECK(SynIterPrevWrapId(aIt) == aIt);
        CHECK(aIt[1] == aNext);
        aIt[1] = aSent;                  // back onto the sentinel for the name instantiation
        CHECK(SynIterPrevWrapName(aIt) == aIt);
        CHECK(aIt[1] == aNext);
        CHECK(g_nInvalid == 0);
    }

    std::printf("SYNDICATE_D50_OK: allocators, dtor, lower_bound, wrappers, %d checks\n",
                g_nChecks);
    return 0;
}
