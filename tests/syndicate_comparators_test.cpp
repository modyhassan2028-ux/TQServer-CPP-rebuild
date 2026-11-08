// The four comparator leaves. The point of the test is the ordering itself: which key orders which way,
// what a zero key means, and that the flag at +0xe short-circuits the key comparison entirely.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/syncomparators.h"

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

struct Rec { uint32_t k0, k4, k8; uint8_t pad[0x20]; };
struct FlagRec { uint8_t pad0[0xe]; uint8_t flag; uint8_t pad1[0x18]; uint32_t key; };

int main() {
    // 0x141780100: signed, and it is >= not > (equal counts as true)
    Rec a, b;
    std::memset(&a, 0, sizeof a); std::memset(&b, 0, sizeof b);
    a.k8 = 10; b.k8 = 10;
    CHECK(synd::Key8GreaterEqual(&a, &b));
    a.k8 = 9;  CHECK(!synd::Key8GreaterEqual(&a, &b));
    a.k8 = 11; CHECK(synd::Key8GreaterEqual(&a, &b));
    a.k8 = 0xFFFFFFFFu; b.k8 = 0;                       // -1 vs 0: signed, so -1 is not greater
    CHECK(!synd::Key8GreaterEqual(&a, &b));
    b.k8 = 0xFFFFFFFEu;                                 // -1 >= -2
    CHECK(synd::Key8GreaterEqual(&a, &b));

    // 0x14174e3a0: a zero first key means empty and sorts first, before anything else is read
    std::memset(&a, 0, sizeof a); std::memset(&b, 0, sizeof b);
    b.k0 = 7;
    CHECK(synd::KeyLess3(&a, &b));                      // A empty
    CHECK(!synd::KeyLess3(&b, &a));                     // B empty, A not
    // both empty still returns true: the zero-key branch is taken before anything is compared, so
    // the predicate is not irreflexive for empty records. That is the binary's behaviour, not a bug here.
    CHECK(synd::KeyLess3(&a, &a));

    // +0x8 orders DESCENDING: the larger key sorts first
    std::memset(&a, 0, sizeof a); std::memset(&b, 0, sizeof b);
    a.k0 = 1; b.k0 = 1; a.k8 = 20; b.k8 = 10;
    CHECK(synd::KeyLess3(&a, &b));                      // bigger +0x8 sorts first, so it *is* less
    CHECK(!synd::KeyLess3(&b, &a));
    // +0x4 orders ASCENDING, and only when +0x8 ties
    a.k8 = b.k8 = 5;
    a.k4 = 1; b.k4 = 2;
    CHECK(synd::KeyLess3(&a, &b));
    CHECK(!synd::KeyLess3(&b, &a));
    // +0x0 last
    a.k4 = b.k4 = 0;
    a.k0 = 3; b.k0 = 4;
    CHECK(synd::KeyLess3(&a, &b));
    CHECK(!synd::KeyLess3(&b, &a));

    // 0x1417b0920: the flag decides before the key, and equal flags fall through to the key
    FlagRec fa, fb;
    std::memset(&fa, 0, sizeof fa); std::memset(&fb, 0, sizeof fb);
    fa.key = 100; fb.key = 1;
    CHECK(!synd::FlagThenKeyLess(&fa, &fb));            // no flags: 100 < 1 is false
    fa.flag = 1;
    CHECK(synd::FlagThenKeyLess(&fa, &fb));             // flag on A, off on B: true whatever the keys
    CHECK(!synd::FlagThenKeyLess(&fb, &fa));            // and false the other way
    fb.flag = 1;
    CHECK(!synd::FlagThenKeyLess(&fa, &fb));            // both flagged: back to the keys
    fa.key = 0; fb.key = 1;
    CHECK(synd::FlagThenKeyLess(&fa, &fb));
    fa.key = 1; fb.key = 1;
    CHECK(!synd::FlagThenKeyLess(&fa, &fb));            // strictly less

    // 0x1417e0830 is empty: calling it must simply do nothing
    synd::NoOp4(1, &fa, 2, &fb);
    CHECK(fa.key == 1);
    CHECK(fb.key == 1);

    // the unaligned read at +0x27 really is a dword at +0x27, not a dword at +0x24
    static unsigned char raw[0x40];
    std::memset(raw, 0, sizeof raw);
    raw[0x27] = 0xFF; raw[0x28] = 0x00; raw[0x29] = 0x00; raw[0x2A] = 0x00;
    unsigned char other[0x40];
    std::memset(other, 0, sizeof other);
    CHECK(!synd::FlagThenKeyLess(raw, other));          // 0xFF > 0
    CHECK(synd::FlagThenKeyLess(other, raw));

    std::printf("COMPARATORS_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
