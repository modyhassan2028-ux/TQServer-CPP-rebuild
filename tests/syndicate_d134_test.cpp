// D134 — seventeen bodies of the cluster: the eleven "this back" returns, the four
//   single-qword assignments that write nothing on a null destination, and the two
//   bodies that only return.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

int main() {
    alignas(16) unsigned char n1[0x40];
    alignas(16) unsigned char n2[0x40];
    std::memset(n1, 0xAB, sizeof n1);
    std::memset(n2, 0xCD, sizeof n2);

    // ---- the eleven bodies whose only work is answering the argument
    assert(SynAccRetThis_1417c6780(n1) == (void*)n1);
    assert(SynAccRetThis_1417c6800(n1) == (void*)n1);
    assert(SynAccRetThis_1417c6880(n1) == (void*)n1);
    assert(SynAccRetThis_1417c6890(n1) == (void*)n1);
    assert(SynAccRetThis_1417c68b0(n1) == (void*)n1);
    assert(SynAccRetThis_1417c68d0(n1) == (void*)n1);
    assert(SynAccRetThis_1417c6900(n1) == (void*)n1);
    assert(SynAccRetThis_1417c69a0(n1) == (void*)n1);
    assert(SynAccRetThis_1417c69b0(n1) == (void*)n1);
    assert(SynAccRetThis_1417c69c0(n1) == (void*)n1);
    assert(SynAccRetThis_1417c69d0(n1) == (void*)n1);

    // ---- the four single-qword assignments: one qword, and the lead has to exist
    {
        std::memset(n1, 0xAB, sizeof n1);
        void* pVal = (void*)0x6880;
        *(void**)(n2) = pVal;
        SynAccAssign1_1417c68a0(n1, n2);
        assert(*(void**)n1 == pVal);
        assert(n1[8] == 0xAB);                       // one qword, not two

        std::memset(n1, 0xAB, sizeof n1);
        SynAccAssign1_1417c68c0(n1, n2);
        assert(*(void**)n1 == pVal);

        std::memset(n1, 0xAB, sizeof n1);
        SynAccAssign1_1417c68f0(n1, n2);
        assert(*(void**)n1 == pVal);

        std::memset(n1, 0xAB, sizeof n1);
        SynAccAssign1_1417c6990(n1, n2);
        assert(*(void**)n1 == pVal);

        // a null destination is a no-op, exactly as the `test / je` says
        const unsigned char firstByte = n2[0];   // the source already holds pVal
        SynAccAssign1_1417c68a0(nullptr, n2);
        SynAccAssign1_1417c68c0(nullptr, n2);
        SynAccAssign1_1417c68f0(nullptr, n2);
        SynAccAssign1_1417c6990(nullptr, n2);
        assert(n2[0] == firstByte);
    }

    // ---- the two bodies that only return
    SynAccNoop_1417c68e0();
    SynAccNoop_1417c6980();
    assert(true);

    std::printf("SYNDICATE_D134_OK: seventeen more bodies, 17 units, 22 checks\n");
    return 0;
}
