// The twelve message field setters at 0x1417d9840..0x1417d98f7. The content of the test is the map:
// which bit goes with which offset, that the flags accumulate rather than replace, and that +0x44 and
// +0x45 are byte stores while their neighbours are not.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/msg/msgfieldflags.h"

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char obj[0x100];

int main() {
    namespace F = tq::msgfield;
    std::memset(obj, 0, sizeof obj);

    // set-only variants, one bit each, and they accumulate
    F::Flag01(obj); CHECK(*(uint32_t*)obj == 0x01);
    F::Flag02(obj); CHECK(*(uint32_t*)obj == 0x03);
    F::Flag04(obj); CHECK(*(uint32_t*)obj == 0x07);
    F::Flag08(obj); CHECK(*(uint32_t*)obj == 0x0F);
    F::Flag10(obj); CHECK(*(uint32_t*)obj == 0x1F);
    F::Flag20(obj); CHECK(*(uint32_t*)obj == 0x3F);
    CHECK(obj[0x34] == 0);                       // the has-word ends at +0x33

    // the set-and-store variants: flag plus value, at the offset the listing gives
    std::memset(obj, 0, sizeof obj);
    F::Flag01And38(obj, 0x11223344);
    CHECK(*(uint32_t*)obj == 0x01);
    CHECK(*(uint32_t*)(obj + 0x38) == 0x11223344);
    F::Flag02And3C(obj, -2);
    CHECK(*(uint32_t*)obj == 0x03);
    CHECK(*(int32_t*)(obj + 0x3C) == -2);
    F::Flag04And40(obj, 0x55667788);
    CHECK(*(uint32_t*)obj == 0x07);
    CHECK(*(uint32_t*)(obj + 0x40) == 0x55667788);
    F::Flag20And60(obj, 0x7FFFFFFF);
    CHECK(*(uint32_t*)obj == 0x27);
    CHECK(*(int32_t*)(obj + 0x60) == 0x7FFFFFFF);

    // the two byte stores must not touch a byte beyond their own
    std::memset(obj, 0xEE, sizeof obj);
    F::Flag08And44(obj, 0x7F);
    CHECK(obj[0x44] == 0x7F);
    CHECK(obj[0x45] == 0xEE);                    // 0x1417d98b4 is `mov %dl`, not `mov %edx`
    CHECK(obj[0x46] == 0xEE);
    CHECK(obj[0x47] == 0xEE);
    F::Flag10And45(obj, 0x80);
    CHECK(obj[0x45] == 0x80);
    CHECK(obj[0x44] == 0x7F);                    // still the previous value
    CHECK(obj[0x46] == 0xEE);
    CHECK((*(uint32_t*)obj & 0x18) == 0x18);     // 0x8 | 0x10, on top of the 0xEE fill

    // setting a field twice keeps the flag and takes the newer value
    F::Flag04And40(obj, 5);
    F::Flag04And40(obj, 6);
    CHECK(*(int32_t*)(obj + 0x40) == 6);
    CHECK((*(uint32_t*)obj & 0x04) == 0x04);
    CHECK((*(uint32_t*)obj & 0x1C) == 0x1C);     // only the bits this section set
    CHECK(*(uint32_t*)obj == 0xEEEEEEFEu);       // the fill survived: only bits are or-ed in

    std::printf("FLAGFLAGS_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
