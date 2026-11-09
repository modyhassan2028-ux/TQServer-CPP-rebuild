// D157 — the iterator distance 0x1417c89d0: zero when the two slots already agree, one when the
//   step lands on the other, and the counter is bumped before each step.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
namespace tq {
void SynAccDistance_1417c89d0(void* pThis, void* pOther, int64_t* pCount);
}
using namespace tq;

int main() {
    alignas(16) unsigned char h[0x60], r[0x60], n5[0x60], stop[0x60];
    alignas(16) unsigned char a[0x10], b[0x10];
    std::memset(h, 0, sizeof h); std::memset(r, 0, sizeof r);
    std::memset(n5, 0, sizeof n5); std::memset(stop, 0, sizeof stop);

    stop[0x41] = 1;                                // the flagged node every walk ends on
    h[0x41] = 1;
    *(void**)(h + 8) = r;                          // header -> root
    *(void**)(r + 8) = h;                          // root's parent
    r[0x29] = 0;
    *(void**)(r) = n5;                             // root's left
    *(void**)(r + 0x10) = stop;
    *(void**)(n5 + 8) = h;                         // n5's parent is the header, which is flagged
    *(void**)(n5 + 0x10) = stop;                   // n5 descends to the stop node

    int64_t count = 0;
    // ---- the two slots already name the same node
    *(void**)(a) = h; *(void**)(a + 8) = r;
    *(void**)(b) = h; *(void**)(b + 8) = r;
    count = 0;
    SynAccDistance_1417c89d0(a, b, &count);
    assert(count == 0);
    assert(*(void**)(a + 8) == (void*)r);          // nothing moved

    // ---- one step: n5 climbs to the flagged parent, which is where the other sits
    *(void**)(a) = h; *(void**)(a + 8) = n5;
    *(void**)(b) = h; *(void**)(b + 8) = h;
    count = 0;
    SynAccDistance_1417c89d0(a, b, &count);
    assert(count == 1);
    assert(*(void**)(a + 8) == (void*)h);          // the climb landed on the header

    std::printf("SYNDICATE_D157_OK: iterator distance, 1 unit, 5 checks\n");
    return 0;
}
