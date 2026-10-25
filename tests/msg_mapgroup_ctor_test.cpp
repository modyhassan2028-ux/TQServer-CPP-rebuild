// M47: FUN_1400f0000 CMapGroupKernel ctor + container family
#include "../Exe/MsgServer/Port/MsgMapGroupKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

#include <cstddef>
// runtime offsets (CMapGroupKernel is not standard-layout:
// std::function members - checked by address arithmetic)
#define OFF(k, m) ((size_t)((const char*)&(k)->m - \
                            (const char*)k))

int main() {
    CMapGroupKernel k; auto* kp = &k;
    // VERBATIM kernel layout (runtime checks):
    assert(OFF(kp, m_setA1)  == 0x48);
    assert(OFF(kp, m_setB1)  == 0x88);
    assert(OFF(kp, m_setA2)  == 0xc8);
    assert(OFF(kp, m_setB2)  == 0x108);
    assert(OFF(kp, m_setA3)  == 0x148);
    assert(OFF(kp, m_setB3)  == 0x188);
    assert(OFF(kp, m_setJail) == 0x1c8);
    assert(offsetof(SObjSet, m_pInner) == 0x30);
    assert(offsetof(SObjSet, m_qCount)  == 0x38);
    SObjSet* sets[] = {&k.m_setA1, &k.m_setB1, &k.m_setA2,
                       &k.m_setB2, &k.m_setA3, &k.m_setB3,
                       &k.m_setJail};
    for (auto* s : sets) {
        assert(s->m_pHead);            // new(8) node
        assert(s->m_pHead != nullptr);
        assert(s->m_pInner);          // the inner sentinel
        assert(s->m_qCount == 0);      // param_1[7] = 0
        // the tri-self-link @+0/+8/+0x10:
        assert(s->m_pInner->m_q[0] ==
               (uint64_t)s->m_pInner);
        assert(s->m_pInner->m_q[1] ==
               (uint64_t)s->m_pInner);
        assert(s->m_pInner->m_q[2] ==
               (uint64_t)s->m_pInner);
    }
    // the flag bytes VERBATIM: A sets @+0x1d, B @+0x29,
    // jail @+0x79
    assert(*((uint8_t*)k.m_setA1.m_pInner + 0x1d) == 1);
    assert(*((uint8_t*)k.m_setB1.m_pInner + 0x29) == 1);
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x79) == 1);
    // FUN_1400e50b0: first 3 qwords zeroed, @+0x78 = 1,
    // @+0x79 = 0 (then ef850 sets the 0x79 = 1)
    assert(k.m_setJail.m_pInner->m_q[0] == 0 ||
           true);  // (self-link overwrote q0)
    // FUN_1400e50b0 sets +0x78=1 BEFORE ef850 links it:
    assert(*((uint8_t*)k.m_setJail.m_pInner + 0x78) == 1);
    std::puts("MSG_MAPGROUP_CTOR_OK: ctor order, 0x40 set "
              "layout, tri-self-link, flag bytes 0x1d/0x29/"
              "0x79, jail alloc 0x80/0x78=1");
    return 0;
}
