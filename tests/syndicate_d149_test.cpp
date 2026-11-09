// D149 — eight bodies: the recursive destroy 0x1417c7a50, the three iterator builders
//   0x1417c7aa0 / 0x1417c7b40 / 0x1417c7b80, the +0x18 accessor 0x1417c7ae0, the two
//   increment wrappers 0x1417c7b20 / 0x1417c7bc0 and the pair builder 0x1417c7be0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/syndicate/src/synacc.h"
using namespace tq;

namespace tq {
extern void (*g_pfnLogic_1417f2fdc)(void* p);
void SynAccEraseAll_1417c7a50(void*, void*);
void* SynAccIterCtor_1417c7aa0(void*, void*, void*);
void* SynAccIterCtor_1417c7b40(void*, void*, void*);
void* SynAccIterCtor_1417c7b80(void*, void*, void*);
void* SynAccCurrPlus18_1417c7ae0(void*);
void* SynAccIncCall_1417c7b20(void*);
void* SynAccIncCall_1417c7bc0(void*);
void* SynAccPair_1417c7be0(void*, void*, void*);
}

static int g_nFreed;
static void* g_aFreed[8];
static void FreeHook(void* p) { g_aFreed[g_nFreed++] = p; }

int main() {
    g_pfnLogic_1417f2fdc = &FreeHook;

    alignas(16) unsigned char r[0x60], l[0x60], ll[0x60], stop[0x60];
    std::memset(r, 0, sizeof r); std::memset(l, 0, sizeof l);
    std::memset(ll, 0, sizeof ll); std::memset(stop, 0, sizeof stop);
    stop[0x29] = 1;

    // ---- 0x1417c7a50: the 0x10 side first, then the node, then along the 0x0 side
    {
        // r: right = stop, left = l ; l: right = stop, left = ll ; ll: right = stop, left = stop
        *(void**)(r + 0x10) = stop;
        *(void**)(r) = l;
        *(void**)(l + 0x10) = stop;
        *(void**)(l) = ll;
        *(void**)(ll + 0x10) = stop;
        *(void**)(ll) = stop;

        g_nFreed = 0;
        SynAccEraseAll_1417c7a50(nullptr, r);
        assert(g_nFreed == 3);
        assert(g_aFreed[0] == (void*)r);        // the first node freed is the one handed in
        assert(g_aFreed[1] == (void*)l);
        assert(g_aFreed[2] == (void*)ll);

        // a flagged node stops the walk before it touches anything
        g_nFreed = 0;
        SynAccEraseAll_1417c7a50(nullptr, stop);
        assert(g_nFreed == 0);
    }

    // ---- the three iterator builders
    {
        unsigned char it[0x10], holder[8];
        *(void**)holder = l;
        std::memset(it, 0xAB, sizeof it);
        assert(SynAccIterCtor_1417c7aa0(it, r, holder) == (void*)it);
        assert(*(void**)(it) == (void*)l && *(void**)(it + 8) == (void*)r);
        std::memset(it, 0xAB, sizeof it);
        assert(SynAccIterCtor_1417c7b40(it, r, holder) == (void*)it);
        assert(*(void**)(it) == (void*)l && *(void**)(it + 8) == (void*)r);
        std::memset(it, 0xAB, sizeof it);
        assert(SynAccIterCtor_1417c7b80(it, r, holder) == (void*)it);
        assert(*(void**)(it) == (void*)l && *(void**)(it + 8) == (void*)r);
    }

    // ---- 0x1417c7ae0: the node slot advanced by 0x18
    {
        unsigned char it[0x10];
        std::memset(it, 0, sizeof it);
        *(void**)(it) = l;
        *(void**)(it + 8) = r;
        assert(SynAccCurrPlus18_1417c7ae0(it) == (void*)(r + 0x18));
    }

    // ---- the two increment wrappers hand the iterator back
    {
        unsigned char it[0x10];
        std::memset(it, 0, sizeof it);
        unsigned char hdr[0x60], root[0x60];
        std::memset(hdr, 0, sizeof hdr); std::memset(root, 0, sizeof root);
        hdr[0x29] = 1; hdr[0x41] = 1;            // a header for both bodies
        *(void**)(hdr + 0x10) = root;
        *(void**)(it) = hdr;                     // the lead the check looks at
        *(void**)(it + 8) = hdr;
        assert(SynAccIncCall_1417c7b20(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)root);
        *(void**)(it + 8) = hdr;
        assert(SynAccIncCall_1417c7bc0(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)root);
    }

    // ---- 0x1417c7be0: the object's first qword and the argument's +0x8
    {
        unsigned char obj[0x10], arg[0x10], out[0x20];
        std::memset(obj, 0, sizeof obj); std::memset(arg, 0, sizeof arg);
        std::memset(out, 0xCD, sizeof out);
        *(void**)(obj) = (void*)0x1234;
        *(void**)(arg + 8) = (void*)0x5678;
        assert(SynAccPair_1417c7be0(obj, out, arg) == (void*)out);
        assert(*(void**)(out) == (void*)0x1234);
        assert(*(void**)(out + 8) == (void*)0x5678);
        assert(*(unsigned char*)(out + 0x10) == 0xCD);      // nothing past the pair
    }

    std::printf("SYNDICATE_D149_OK: eight bodies, 5 units, 17 checks\n");
    return 0;
}
