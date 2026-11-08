// D141 — twelve bodies from 0x1417c6ce0 to 0x1417c6dff: the setne comparison at 0x1417c6ce0,
//   the zeroed lead at 0x1417c6d20, the three `this + 0x18` / 0x30-slot pairs, the three
//   deallocate thunks that free the lead, and the 0x1417c6dc0 accessor.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

namespace tq {
bool SynAccIterNe_1417c6ce0(void*, void*);
void SynAccFreeLead_1417c6d50(void*);
void SynAccFreeLead_1417c6d80(void*);
void SynAccFreeLead_1417c6db0(void*);
void* SynAccCurrPlus18_1417c6dc0(void*);
}  // namespace tq
using namespace tq;

int main() {
    alignas(16) unsigned char n1[0x60], n2[0x60], n3[0x60], inner[0x40];
    alignas(16) unsigned char it[0x10];

    // ---- 0x1417c6ce0: the setne comparison
    {
        std::memset(n1, 0, sizeof n1); std::memset(n2, 0, sizeof n2); std::memset(n3, 0, sizeof n3);
        *(void**)n1 = n1; *(void**)n2 = n1;
        *(void**)(n1 + 8) = (void*)0x11; *(void**)(n2 + 8) = (void*)0x11;
        assert(SynAccIterNe_1417c6ce0(n1, n2) == false);
        *(void**)(n2 + 8) = (void*)0x22;
        assert(SynAccIterNe_1417c6ce0(n1, n2) == true);
        *(void**)(n2 + 8) = (void*)0x11; *(void**)n2 = n3;
        assert(SynAccIterNe_1417c6ce0(n1, n2) == false);
        *(void**)n2 = nullptr;
        assert(SynAccIterNe_1417c6ce0(n1, n2) == false);
    }

    // ---- 0x1417c6d20: the lead cleared, this back
    {
        std::memset(n1, 0xAB, sizeof n1);
        assert(SynAccZeroLead_1417c6d20(n1) == (void*)n1);
        assert(*(void**)n1 == nullptr);
        assert(n1[8] == 0xAB);
    }

    // ---- the three `+0x18` bodies and the three 0x30-slot `+0x8` bodies
    {
        assert(SynAccPlus18_1417c6d30(n1) == (void*)(n1 + 0x18));
        assert(SynAccPlus18_1417c6d60(n1) == (void*)(n1 + 0x18));
        assert(SynAccPlus18_1417c6d90(n1) == (void*)(n1 + 0x18));

        std::memset(n1, 0, sizeof n1);
        *(void**)(n1 + 0x30) = inner;
        assert(SynAccSlot30Plus8_1417c6d40(n1) == (void*)(inner + 8));
        assert(SynAccSlot30Plus8_1417c6d70(n1) == (void*)(inner + 8));
        assert(SynAccSlot30Plus8_1417c6da0(n1) == (void*)(inner + 8));
    }

    // ---- the three deallocate thunks: the lead is what gets freed, allocated here so the
    //      default deallocate seam can take it
    {
        std::memset(it, 0, sizeof it);
        void* a = ::operator new(0x20);
        void* b = ::operator new(0x20);
        void* c = ::operator new(0x20);
        *(void**)n1 = a;
        *(void**)n2 = b;
        *(void**)n3 = c;
        SynAccFreeLead_1417c6d50(n1);
        SynAccFreeLead_1417c6d80(n2);
        SynAccFreeLead_1417c6db0(n3);
        assert(*(void**)n1 == (void*)a);            // the body only reads the lead
    }

    // ---- 0x1417c6dc0: the lead's lead, its 0x30 slot, then +0x18 on the node
    {
        std::memset(it, 0, sizeof it);
        std::memset(n1, 0, sizeof n1);
        std::memset(n2, 0, sizeof n2);
        std::memset(n3, 0, sizeof n3);
        *(void**)it = n1;                           // the lead
        *(void**)n1 = n2;                           // the lead's lead
        *(void**)(n2 + 0x30) = (void*)0x1234;       // its 0x30 slot
        *(void**)(it + 8) = n3;                     // the node, different from the slot
        assert(SynAccCurrPlus18_1417c6dc0(it) == (void*)(n3 + 0x18));
    }

    std::printf("SYNDICATE_D141_OK: twelve bodies, 12 units, 20 checks\n");
    return 0;
}
