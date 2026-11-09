// D159 - the scored walk 0x1417c8c10: zero when the cursor is already the end, and the element
// with the greatest score when two are offered, with the mode passed straight through.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

namespace tq {
extern int (*g_pfnSynScore_141798060)(void* pElem, unsigned int uMode);
void* SynAccBestMatch_1417c8c10(void* pThis, unsigned int uMode);
}

static int g_modeSeen = -1;
static int ScoreElem(void* pElem, unsigned int uMode) {
    g_modeSeen = (int)uMode;
    return *(int*)pElem;
}

int main() {
    tq::g_pfnSynScore_141798060 = &ScoreElem;

    alignas(16) unsigned char self[0x40], holder[0x60], n1[0x60], n2[0x60], stop[0x60];
    std::memset(self, 0, sizeof self); std::memset(holder, 0, sizeof holder);
    std::memset(n1, 0, sizeof n1); std::memset(n2, 0, sizeof n2); std::memset(stop, 0, sizeof stop);
    stop[0x29] = 1; holder[0x29] = 1;

    // ---- the cursor already is the end
    {
        *(void**)(self + 0x38) = holder;
        *(void**)(holder) = holder;
        *(void**)(self + 8) = holder;
        g_modeSeen = -1;
        assert(tq::SynAccBestMatch_1417c8c10(self, 5u) == nullptr);
        assert(g_modeSeen == -1);                     // nothing was scored
    }

    // ---- two elements, the second one better
    {
        int e1 = 5, e2 = 7;
        *(void**)(self + 0x38) = holder;
        *(void**)(holder) = n1;                       // the cursor starts at n1
        *(void**)(self + 8) = n1;                     // and the node the checks read is n1
        *(void**)(n1) = stop;                         // the lead the walk re-reads
        *(void**)(stop + 0x30) = nullptr;             // never equal to the cursor
        *(void**)(n1 + 0x20) = &e1;
        *(void**)(n1 + 0x10) = n2;                    // descend to n2 next
        *(void**)(n2 + 0x20) = &e2;
        *(void**)(n2) = stop;                          // the left spine stops here too
        *(void**)(n2 + 0x10) = stop;                  // the descend stops here
        *(void**)(n2 + 8) = holder;                   // and the climb leaves through the holder

        g_modeSeen = -1;
        void* r = tq::SynAccBestMatch_1417c8c10(self, 9u);
        assert(r == (void*)&e2);                      // the greater score wins
        assert(g_modeSeen == 9);                      // and the mode went through
    }

    std::puts("SYNDICATE_D159_OK: the scored walk, 3 checks");
    return 0;
}
