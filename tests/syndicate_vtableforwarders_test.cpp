// The forwarder family at 0x14177fa10..0x14177fa90. A fake vtable with a receiver check in every slot is
// the only way to prove the two things that matter: which slot each forwarder enters, and that the third
// argument arrives as the second.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/vtableforwarders.h"

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

// A vtable wide enough for the highest slot used (0x378) and a receiver that records what it was told.
static unsigned char g_vtable[0x400];
static void* g_seenSelf;
static int32_t g_seenValue;

static void SlotBody(void* self, int32_t v) {
    (void)self;
    g_seenSelf = self;
    g_seenValue = v;
}

int main() {
    namespace S = synd;

    // install the same body in each slot the forwarders use
    struct Obj { void* vt; int marker; } obj;
    obj.vt = g_vtable;
    obj.marker = 0x5151;
    *(void**)(g_vtable + 0x2B0) = (void*)&SlotBody;
    *(void**)(g_vtable + 0x2B8) = (void*)&SlotBody;
    *(void**)(g_vtable + 0x378) = (void*)&SlotBody;

    // 0x14177fa40: the receiver is *(self), and the second argument is dropped in favour of the third
    void* holder[2] = { &obj, nullptr };
    g_seenSelf = nullptr; g_seenValue = 0;
    S::ForwardSlot2B0(holder, 111, 222);
    CHECK(g_seenSelf == &obj);
    CHECK(g_seenValue == 222);                          // not 111: edx is overwritten with r8d

    // 0x14177fa50 does the same through the other slot
    g_seenSelf = nullptr; g_seenValue = 0;
    S::ForwardSlot2B8(holder, 1, 2);
    CHECK(g_seenSelf == &obj);
    CHECK(g_seenValue == 2);

    // 0x14177fa10 gets its receiver from 0x1417b6210, not from *self
    static void* provided = nullptr;
    S::g_pfn1417b6210 = [](void*) -> void* { return provided; };
    provided = &obj;
    g_seenSelf = nullptr; g_seenValue = 0;
    S::ForwardSlot378(holder, 5, 6);
    CHECK(g_seenSelf == &obj);
    CHECK(g_seenValue == 6);

    // and when that seam hands back a different object, the slot sees that one
    static Obj other; other.vt = g_vtable; other.marker = 0x6262;
    provided = &other;
    g_seenSelf = nullptr;
    S::ForwardSlot378(holder, 5, 7);
    CHECK(g_seenSelf == &other);

    // 0x14177fa60 calls one function and tail-jumps another with the same two integers
    static void* made = nullptr; static int32_t seenArg2 = -1, seenArg3 = -1;
    static int32_t tailArg2 = -1, tailArg3 = -1; static void* tailSelf = nullptr;
    S::g_pfn14173f9c0 = [](void* self, int32_t a2, int32_t a3) -> void* { (void)self; seenArg2 = a2; seenArg3 = a3; return made; };
    S::g_pfn14173d820 = [](void* self, int32_t a2, int32_t a3) -> int32_t { tailSelf = self; tailArg2 = a2; tailArg3 = a3; return 0; };
    made = &other;
    S::ForwardVia14173D820(holder, 8, 9);
    CHECK(seenArg2 == 8); CHECK(seenArg3 == 9);
    CHECK(tailSelf == &other);
    CHECK(tailArg2 == 8); CHECK(tailArg3 == 9);         // the same integers, not the callee's result

    // the selector maps 0..3 and nothing else
    CHECK(S::SelectForwarder(0) == &S::ForwardSlot2B0);
    CHECK(S::SelectForwarder(1) == &S::ForwardSlot378);
    CHECK(S::SelectForwarder(2) == &S::ForwardSlot2B8);
    CHECK(S::SelectForwarder(3) == &S::ForwardVia14173D820);
    CHECK(S::SelectForwarder(4) == nullptr);
    CHECK(S::SelectForwarder(-1) == nullptr);

    // and the selected forwarder really dispatches when called through the pointer
    void (*sel)(void*, int32_t, int32_t) = S::SelectForwarder(0);
    g_seenValue = 0;
    sel(holder, 0, 42);
    CHECK(g_seenValue == 42);
    CHECK(g_seenSelf == &obj);

    std::printf("VTABLEFWD_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
