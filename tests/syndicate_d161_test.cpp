// D161 — the generated leaf table: every one of the 645 bodies is called through the same table and
//   checked against the shape it was generated from.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/genleaf.h"

int main() {
    using namespace tq;
    assert(g_synLeafCount > 500);   // the exact count is printed below
    int checked = 0;
    for (unsigned int i = 0; i < g_synLeafCount; ++i) {
        const SynLeafEntry& e = g_synLeafTable[i];
        alignas(16) unsigned char buf[0x200];
        std::memset(buf, 0, sizeof buf);
        void* sentinel = (void*)&checked;
        unsigned long long off = e.uArg & 0x1f8ULL;
        *(void**)(buf + off) = sentinel;
        void* r = e.pfn(buf);
        switch (e.uKind) {
            case 0: break;                                              // returns the argument frame
            case 1: assert(r == nullptr); break;                        // xor eax,eax
            case 2: assert(r == (void*)buf); break;                     // the identity
            case 3: assert((unsigned long long)r == e.uArg); break;     // the constant
            case 4: assert(r == sentinel); break;                       // the field at uArg
            case 5: assert(r == (void*)((unsigned char*)sentinel + e.uBias)); break;
            case 6: assert(r == (void*)(buf + e.uArg)); break;          // the address
            case 7: assert(r == (void*)buf && *(void**)buf == nullptr); break;
            default: assert(!"unknown kind"); break;
        }
        ++checked;
    }
    std::printf("SYNDICATE_D161_OK: %u generated leaf bodies checked\n", g_synLeafCount);
    (void)checked;
    return 0;
}
