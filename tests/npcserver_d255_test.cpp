// D255: the transliterated unit's accounting, and the two invariants its markers depend on.
#include <cstdio>
#include <cstring>
#include <set>

#include "modules/npcserver/unattributed/transliterated.h"

#define CHECK(expr) do { if (!(expr)) { std::printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #expr); ++nFail; } } while (0)

int main()
{
    int nFail = 0;

    CHECK(tq::g_nNpcTranslitCount == tq::g_nNpcTranslitLinked + tq::g_nNpcTranslitPending);
    CHECK(tq::g_nNpcTranslitCount > 1400u);
    CHECK(tq::g_nNpcTranslitLinked > 700u);

    std::set<unsigned long long> seen;
    unsigned long long nPrev = 0;
    for (unsigned i = 0; i < tq::g_nNpcTranslitCount; ++i) {
        unsigned long long nAddr = tq::g_aNpcTranslitAddr[i];
        CHECK(nAddr >= 0x140001000ULL && nAddr < 0x141000000ULL);   // inside the image the listing was taken from
        CHECK(seen.insert(nAddr).second);                            // one body per address, no duplicate work
        CHECK(nAddr > nPrev);                                        // the table is sorted, as the report is
        nPrev = nAddr;
    }

    std::printf("NPCSERVER_D255_OK: %u transliterated bodies (%u linked, %u pending)\n",
                tq::g_nNpcTranslitCount, tq::g_nNpcTranslitLinked, tq::g_nNpcTranslitPending);
    return nFail ? 1 : 0;
}
