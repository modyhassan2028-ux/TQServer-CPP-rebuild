// M71a: FUN_140009f20 - the END sentinel creator
#include "../msgserver/MsgHashEnd.h"
#include <cassert>
#include <cstdio>
#include <cstring>

int main() {
    // the sentinel: 0x18 bytes, next/prev self-linked
    void* p = msg::HashEndCreate();
    assert(p != nullptr);
    void** pn = (void**)p;
    assert(pn[0] == p);    // +0x00 next = self
    assert(pn[1] == p);    // +0x08 prev = self
    // the remaining 0x08 bytes (key/value area)
    // are UNINITIALIZED by the ORIGINAL - verify the
    // size only via a zeroed second node's usage
    void* q = msg::HashEndCreate();
    assert(q != nullptr && q != p);
    void** qn = (void**)q;
    assert(qn[0] == q && qn[1] == q);
    operator delete(p);
    operator delete(q);
    // drop-in for the ctor wiring: a fresh container's
    // +0x38 points at a self-linked sentinel (the empty
    // circular list of M68)
    uint8_t abC[0x90]; std::memset(abC, 0, sizeof abC);
    void* pSent = msg::HashEndCreate();
    *(void**)(abC + 0x38) = pSent;
    assert(*(void**)(*(void**)(abC + 0x38)) ==
           *(void**)(abC + 0x38));   // END->next == END
    operator delete(pSent);
    std::puts("M71A-HASH-END-OK");
    return 0;
}
