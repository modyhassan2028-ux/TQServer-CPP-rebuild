// The twenty container accessors at 0x1417c5980..0x1417c5f5a. What is worth testing is not that a `lea`
// works: it is the offsets (each one is a claim about a layout), the copy widths, the two different
// sentinel bytes, and the constants that differ by one hex digit.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/containeraccessors.h"

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char obj[0x100];

int main() {
    namespace A = synd::acc;

    // every `lea` accessor against the offset it claims
    std::memset(obj, 0, sizeof obj);
    CHECK((char*)A::At29(obj) - (char*)obj == 0x29);
    CHECK((char*)A::At10(obj) - (char*)obj == 0x10);
    CHECK((char*)A::At41(obj) - (char*)obj == 0x41);
    CHECK((char*)A::At21(obj) - (char*)obj == 0x21);
    CHECK((char*)A::At28(obj) - (char*)obj == 0x28);
    CHECK((char*)A::At08(obj) - (char*)obj == 0x08);
    CHECK((char*)A::At18(obj) - (char*)obj == 0x18);
    CHECK((char*)A::At40(obj) - (char*)obj == 0x40);
    CHECK((char*)A::At20(obj) - (char*)obj == 0x20);

    // the dereferencing accessors, and the two that step past what they load
    void* inner = obj + 0x80;
    *(void**)(obj + 0x30) = inner;
    *(void**)(obj + 0x08) = obj + 0x90;
    CHECK(A::Field30(obj) == inner);
    CHECK(A::Field08(obj) == obj + 0x90);
    CHECK((char*)A::Field30Plus10(obj) - (char*)inner == 0x10);
    CHECK((char*)A::Field30Plus8(obj) - (char*)inner == 0x08);

    // InitU32U64: a word from src, a quad from tail, and nothing else written
    std::memset(obj, 0xCC, sizeof obj);
    std::uint32_t w = 0xAABBCCDD; std::uint64_t q = 0x1122334455667788ULL;
    void* r = A::InitU32U64(obj, &w, &q);
    CHECK(r == obj);
    CHECK(*(uint32_t*)obj == 0xAABBCCDD);
    CHECK(*(uint64_t*)(obj + 0x8) == 0x1122334455667788ULL);
    CHECK(obj[0x10] == 0xCC);                        // the word store stops at +0x3

    // Init16 copies sixteen bytes; Init16U8 copies them and one byte more
    struct Src16 { uint64_t a, b; } src = { 0x0102030405060708ULL, 0x1112131415161718ULL };
    std::memset(obj, 0xCC, sizeof obj);
    CHECK(A::Init16(obj, &src) == obj);
    CHECK(*(uint64_t*)obj == 0x0102030405060708ULL);
    CHECK(*(uint64_t*)(obj + 0x8) == 0x1112131415161718ULL);
    CHECK(obj[0x10] == 0xCC);                        // Init16 stops at sixteen bytes

    std::memset(obj, 0xCC, sizeof obj);
    unsigned char b = 0x7E;
    CHECK(A::Init16U8(obj, &src, &b) == obj);
    CHECK(obj[0x10] == 0x7E);
    CHECK(obj[0x11] == 0xCC);                        // one byte, not a word

    // The walk returns the node *before* the one carrying the sentinel flag, and returns `self` itself
    // when the first node it sees already carries it. Both cases are tested because the difference
    // decides whether an empty container yields the header or a node.
    unsigned char tree[0x100];
    std::memset(tree, 0, sizeof tree);
    void* n0 = tree + 0x00; void* n1 = tree + 0x30; void* n2 = tree + 0x60;
    *(void**)n0 = n1; *(void**)n1 = n2;
    *(unsigned char*)((char*)n2 + 0x29) = 1;        // the sentinel, flagged in both layouts
    *(unsigned char*)((char*)n2 + 0x41) = 1;
    *(void**)obj = n0;
    CHECK(A::MinNode29(obj) == n1);                 // stops one short of the sentinel
    CHECK(A::MinNode41(obj) == n1);

    // now flag the *first* node: both walks return the holder untouched
    *(unsigned char*)((char*)n0 + 0x29) = 1;
    CHECK(A::MinNode29(obj) == obj);
    *(unsigned char*)((char*)n0 + 0x29) = 0;
    *(unsigned char*)((char*)n0 + 0x41) = 1;
    CHECK(A::MinNode41(obj) == obj);
    CHECK(A::MinNode29(obj) == n1);                 // +0x29 is clear again, so the 29 walk still descends
    *(unsigned char*)((char*)n0 + 0x41) = 0;

    // the two sentinel bytes really are different positions: clearing +0x29 on the sentinel makes the
    // 29 walk run past it, and it then reads whatever +0x0 of the sentinel holds (null here) as the next
    // node, so this layout must never be walked with the other layout's flag cleared
    *(unsigned char*)((char*)n2 + 0x29) = 0;
    CHECK(A::MinNode41(obj) == n1);                 // the 41 walk is unaffected
    *(unsigned char*)((char*)n2 + 0x29) = 1;

    // the delete thunk forwards its second argument and drops the first
    static void* seen; seen = nullptr;
    static void (*const sink)(void*) = [](void* p) { seen = p; };
    A::g_pfn1417f2fdc = sink;
    void* value = obj + 0x70;
    A::DeleteValueThunk(obj, value);
    CHECK(seen == value);
    A::g_pfn1417f2fdc = nullptr;

    // the constant is 0x0fffffffffffffff — fifteen f's
    CHECK(A::Limit3F() == 0x0FFFFFFFFFFFFFFFULL);
    CHECK(A::Limit3F() != 0xFFFFFFFFFFFFFFFFULL);

    std::printf("CONTAINERACC_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
