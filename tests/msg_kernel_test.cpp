// MsgServer unit M4 - the kernel slot registry
// FUN_1400084e0 + FUN_140008520 + FUN_140006fe0
#include "../Exe/MsgServer/Port/MsgKernelSlots.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace msg;

int main() {
    // 20 slots x 0x850
    std::vector<uint8_t> buf(20 * 0x850, 0xEE);
    MsgKernelSlots s;
    s.pBegin = buf.data();
    s.pEnd = buf.data() + buf.size();
    int nErr = 0, nAbort = 0;
    bool bAbort = false;
    s.m_fnLogError = [&]{ ++nErr; };
    s.m_fnInvalidParam = [&]{ ++nAbort; bAbort = true; };

    // the LITERAL quirk: slots 0..13 INVALID
    for (uint32_t i = 0; i <= 13; ++i)
        assert(MsgKernelIdxValid(s, i) == 0);
    // 14..19 valid
    for (uint32_t i = 14; i < 20; ++i)
        assert(MsgKernelIdxValid(s, i) == 1);
    assert(MsgKernelIdxValid(s, 20) == 0);

    // FUN_140008520: the error log + null on 0..13
    assert(MsgKernelGetSlot(s, 0) == nullptr);
    assert(MsgKernelGetSlot(s, 13) == nullptr);
    assert(nErr == 2);
    // valid: base + idx * 0x850
    assert(MsgKernelGetSlot(s, 14) == buf.data() +
           14 * 0x850);
    assert(MsgKernelGetSlot(s, 19) == buf.data() +
           19 * 0x850);
    assert(nErr == 2 && nAbort == 0);

    // the member variant (140006fe0): no 0xd gate
    uint8_t* pSlots[2] = { buf.data(),
                           buf.data() + buf.size() };
    assert(MsgKernelGetSlotMember(pSlots, 0,
        [&]{ bAbort = true; }) == buf.data());
    assert(MsgKernelGetSlotMember(pSlots, 5,
        [&]{ bAbort = true; }) == buf.data() +
           5 * 0x850);
    // out of bounds -> the abort
    MsgKernelGetSlotMember(pSlots, 20,
        [&]{ bAbort = true; });
    assert(bAbort);
    // count arithmetic
    assert(s.Count() == 20);

    printf("MSG_KERNEL_OK: FUN_1400084e0 (the LITERAL "
           "0xd gate - slots 0..13 invalid, 14..19 "
           "valid of 20) + FUN_140008520 (the "
           "DAT_1406d9c10 error log + null on the "
           "first 14, base + idx*0x850 on success, "
           "the _invalid_parameter_noinfo abort on "
           "the second bounds miss) + FUN_140006fe0 "
           "(the member variant on +0x18/+0x20 with "
           "NO 0xd gate)\n");
    return 0;
}
