// D129 — the pure accessor cluster at 0x1417c5980..0x1417c5f80, checked against
//   the addresses and slots its own instructions form.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace tq;

int main() {
    alignas(16) unsigned char a[0x80];
    alignas(16) unsigned char b[0x20];
    std::memset(a, 0xAB, sizeof a);
    std::memset(b, 0x11, sizeof b);

    // ---- 0x1417c5980 / 0x1417c5990: 4 bytes in, qword at +0x8 in, this back
    {
        int32_t nVal = 0x12345678;
        void* pVal = (void*)0x1122334455667788ull;
        assert(SynAccIntPtr_1417c5980(a, &nVal, &pVal) == (void*)a);
        assert(*(int32_t*)a == 0x12345678);
        assert(*(void**)(a + 8) == pVal);

        std::memset(a, 0xAB, sizeof a);
        nVal = 0x0badf00d;
        pVal = (void*)0x7;
        assert(SynAccIntPtr_1417c5990(a, &nVal, &pVal) == (void*)a);
        assert(*(int32_t*)a == 0x0badf00d);
        assert(*(void**)(a + 8) == pVal);
    }

    // ---- 0x1417c59a0 zeroes the lead qword only
    {
        std::memset(a, 0xAB, sizeof a);   // the block above left a qword at +0x8
        assert(SynAccZeroQword_1417c59a0(a) == (void*)a);
        assert(*(void**)a == nullptr);
        assert(a[8] == 0xAB);
    }

    // ---- the plain "this back" bodies
    assert(SynAccRetThis_1417c59b0(a) == (void*)a);
    assert(SynAccRetThis_1417c59d0(a) == (void*)a);
    assert(SynAccRetThis_1417c5a10(a) == (void*)a);
    assert(SynAccRetThis_1417c5a20(a) == (void*)a);
    assert(SynAccRetThis_1417c5a40(a) == (void*)a);
    assert(SynAccRetThis_1417c5a80(a) == (void*)a);
    assert(SynAccRetThis_1417c5aa0(a) == (void*)a);
    assert(SynAccRetThis_1417c5ac0(a) == (void*)a);
    assert(SynAccRetThis_1417c5ad0(a) == (void*)a);
    assert(SynAccRetThis_1417c5bd0(a) == (void*)a);
    assert(SynAccRetThis_1417c5de0(a) == (void*)a);
    assert(SynAccRetThis_1417c5df0(a) == (void*)a);

    // ---- the lea bodies, each its own offset
    assert(SynAccPlus29_1417c59c0(a) == (void*)(a + 0x29));
    assert(SynAccPlus10_1417c59e0(a) == (void*)(a + 0x10));
    assert(SynAccPlus41_1417c5a30(a) == (void*)(a + 0x41));
    assert(SynAccPlus10_1417c5a50(a) == (void*)(a + 0x10));
    assert(SynAccPlus21_1417c5a90(a) == (void*)(a + 0x21));
    assert(SynAccPlus10_1417c5ab0(a) == (void*)(a + 0x10));
    assert(SynAccPlus28_1417c5c20(a) == (void*)(a + 0x28));
    assert(SynAccPlus8_1417c5c30(a) == (void*)(a + 8));
    assert(SynAccPlus18_1417c5c40(a) == (void*)(a + 0x18));
    assert(SynAccPlus40_1417c5c90(a) == (void*)(a + 0x40));
    assert(SynAccPlus8_1417c5ca0(a) == (void*)(a + 8));
    assert(SynAccPlus18_1417c5cb0(a) == (void*)(a + 0x18));
    assert(SynAccPlus20_1417c5cd0(a) == (void*)(a + 0x20));
    assert(SynAccPlus8_1417c5ce0(a) == (void*)(a + 8));
    assert(SynAccPlus18_1417c5cf0(a) == (void*)(a + 0x18));

    // ---- the 0x30 slot, loaded three ways
    {
        alignas(16) unsigned char inner[0x40];
        std::memset(inner, 0x5A, sizeof inner);
        *(void**)(a + 0x30) = inner;
        assert(SynAccSlot30_1417c59f0(a) == (void*)inner);
        assert(SynAccSlot30_1417c5a60(a) == (void*)inner);
        assert(SynAccSlot30_1417c5d00(a) == (void*)inner);
        assert(SynAccSlot30Plus10_1417c5a00(a) == (void*)(inner + 0x10));
        assert(SynAccSlot30Plus10_1417c5a70(a) == (void*)(inner + 0x10));
        assert(SynAccSlot30Plus8_1417c5dd0(a) == (void*)(inner + 8));
    }

    // ---- the 0x8 slot
    {
        void* pVal = (void*)0x4141;
        *(void**)(a + 8) = pVal;
        assert(SynAccSlot8_1417c5b00(a) == pVal);
        assert(SynAccSlot8_1417c5b70(a) == pVal);
        assert(SynAccSlot8_1417c5bc0(a) == pVal);
    }

    // ---- 0x1417c5ae0 / 0x1417c5b10: both qwords and the byte its argument names
    {
        std::memset(a, 0xAB, sizeof a);
        b[0] = 0x7E;
        assert(SynAccTwoQwordsByte_1417c5ae0(a, b, b) == (void*)a);
        assert(*(void**)(a + 0) == *(void**)(b + 0));
        assert(*(void**)(a + 8) == *(void**)(b + 8));
        assert(a[0x10] == 0x7E);
        assert(a[0x11] == 0xAB);          // nothing past 0x10

        std::memset(a, 0xAB, sizeof a);
        b[0] = 0x01;
        assert(SynAccTwoQwordsByte_1417c5b10(a, b, b) == (void*)a);
        assert(*(void**)(a + 8) == *(void**)(b + 8));
        assert(a[0x10] == 0x01);
        assert(a[0x11] == 0xAB);
    }

    // ---- 0x1417c5e60: the two qwords alone
    {
        std::memset(a, 0xAB, sizeof a);
        assert(SynAccTwoQwords_1417c5e60(a, b) == (void*)a);
        assert(*(void**)(a + 0) == *(void**)(b + 0));
        assert(*(void**)(a + 8) == *(void**)(b + 8));
        assert(a[0x10] == 0xAB);
    }

    // ---- 0x1417c5ef0: the raw 64 bit answer
    assert(SynAccConst_1417c5ef0() == 0x0fffffffffffffffull);

    std::printf("SYNDICATE_D129_OK: the pure accessor cluster, 41 bodies, 56 checks\n");
    return 0;
}
