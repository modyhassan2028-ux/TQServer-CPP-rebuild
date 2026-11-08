// D136 — the four bodies at the head of the 0x1417c69e0 stretch:
//   0x1417c6a10 (two words from two arguments), 0x1417c6a20 / 0x1417c6a30 ("this back")
//   and 0x1417c6a40, whose source is the first argument and whose answer is the second.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

int main() {
    alignas(16) unsigned char dst[0x20];
    alignas(16) unsigned char a[0x10];
    alignas(16) unsigned char b[0x10];

    // ---- 0x1417c6a10: the first word at +0x0, the second at +0x4, nothing else
    {
        std::memset(dst, 0xAB, sizeof dst);
        *(unsigned int*)a = 0x11223344u;
        *(unsigned int*)b = 0x55667788u;
        assert(SynAccCopy2Ints_1417c6a10(dst, a, b) == (void*)dst);
        assert(*(unsigned int*)(dst + 0) == 0x11223344u);
        assert(*(unsigned int*)(dst + 4) == 0x55667788u);
        assert(dst[8] == 0xAB);                       // nothing past the two words
    }

    // ---- 0x1417c6a20 / 0x1417c6a30
    assert(SynAccRetThis_1417c6a20(dst) == (void*)dst);
    assert(SynAccRetThis_1417c6a30(dst) == (void*)dst);

    // ---- 0x1417c6a40: rcx is the source, rdx the destination and the answer
    {
        std::memset(dst, 0xAB, sizeof dst);
        std::memset(a, 0x3C, sizeof a);
        void* pRet = SynAccCopy16To_1417c6a40(a, dst);
        assert(pRet == (void*)dst);                   // the answer is rdx
        assert(*(void**)(dst + 0) == *(void**)(a + 0));
        assert(*(void**)(dst + 8) == *(void**)(a + 8));
        assert(dst[0x10] == 0xAB);                    // two qwords only
        assert(a[0x10 - 0x10] == 0x3C);               // and the source is left alone
    }

    std::printf("SYNDICATE_D136_OK: four bodies, 4 units, 12 checks\n");
    return 0;
}
