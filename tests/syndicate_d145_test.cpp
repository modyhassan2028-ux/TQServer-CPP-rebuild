// D145 — six bodies: the 0x21 rotations 0x1417c71f0 / 0x1417c7250, the stub 0x1417c72b0,
//   the comparator descent 0x1417c7080 and the two increment wrappers 0x1417c72c0 / 0x1417c72e0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"

namespace tq {
extern bool (*g_pfnSynCmp_141823260)(void*, void*);
void* SynAccFindOrAdd_1417c7080(void*, void*);
void* SynAccIncIter_1417c72c0(void*);
void* SynAccIncIter_1417c72e0(void*);
}

using namespace tq;

static const unsigned int* g_pKey;          // what the comparator is asked about

static bool CmpLess(void* pNodeKey, void* pKey) {
    assert(pKey == (void*)g_pKey);
    return *(const unsigned int*)pNodeKey < *(const unsigned int*)pKey;
}

int main() {
    std::printf("D145 built\n");
    alignas(16) unsigned char tree[0x40], head[0x60], x[0x60], s[0x60], it[0x10], h2[0x60], r2[0x60];
    int checks = 0;

    SynAccNoop_1417c72b0(); ++checks;

    // ---- 0x1417c71f0: the 0x10-side rotation on the 0x21 byte
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(s, 0, sizeof s);
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;
        *(void**)(x + 8) = head;
        *(void**)(x + 0x10) = s;
        *(void**)(s) = s;
        s[0x21] = 1;
        assert(SynAccRotRight21_1417c71f0(tree, x) == (void*)s);
        assert(*(void**)(head + 8) == (void*)s);
        assert(*(void**)(s) == (void*)x);
        assert(*(void**)(x + 8) == (void*)s);
        ++checks;
    }

    // ---- 0x1417c7250: the mirror on the 0x0 side
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(s, 0, sizeof s);
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;
        *(void**)(x + 8) = head;
        *(void**)(x) = s;
        *(void**)(s + 0x10) = s;
        s[0x21] = 1;
        assert(SynAccRotLeft21_1417c7250(tree, x) == (void*)s);
        assert(*(void**)(head + 8) == (void*)s);
        assert(*(void**)(s + 0x10) == (void*)x);
        assert(*(void**)(x + 8) == (void*)s);
        ++checks;
    }

    // ---- 0x1417c7080: comparator-driven descent, 0x41 byte, answer is the left-link node
    {
        std::memset(tree, 0, sizeof tree); std::memset(head, 0, sizeof head);
        std::memset(x, 0, sizeof x); std::memset(s, 0, sizeof s); std::memset(h2, 0, sizeof h2);
        g_pfnSynCmp_141823260 = &CmpLess;
        *(void**)(tree + 0x30) = head;
        *(void**)(head + 8) = x;              // root
        *(unsigned int*)(x + 0x18) = 10;
        *(void**)(x) = h2;                    // left child, key 5
        *(void**)(x + 0x10) = s;              // right child: the sentinel
        *(unsigned int*)(h2 + 0x18) = 5;
        *(void**)(h2) = s;
        *(void**)(h2 + 0x10) = s;
        s[0x41] = 1;
        unsigned int k = 7; g_pKey = &k;
        assert(SynAccFindOrAdd_1417c7080(tree, (void*)&k) == (void*)x);    // 10 < 7 false -> left
        k = 3;
        assert(SynAccFindOrAdd_1417c7080(tree, (void*)&k) == (void*)h2);   // 10 and 5 both keep
        k = 99;
        assert(SynAccFindOrAdd_1417c7080(tree, (void*)&k) == (void*)head); // right at the root
        ++checks;
    }

    // ---- 0x1417c72c0 / 0x1417c72e0: run the increment, hand the iterator back
    {
        std::memset(it, 0, sizeof it); std::memset(h2, 0, sizeof h2); std::memset(r2, 0, sizeof r2);
        *(void**)(it) = h2;                   // a non-null lead so the DEBUG check stays quiet
        *(void**)(it + 8) = h2;               // the header, flagged
        h2[0x29] = 1;
        *(void**)(h2 + 0x10) = r2;            // its root
        *(void**)(r2 + 8) = h2;
        assert(SynAccIncIter_1417c72c0(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)r2);
        ++checks;

        std::memset(it, 0, sizeof it); std::memset(h2, 0, sizeof h2); std::memset(r2, 0, sizeof r2);
        *(void**)(it) = h2;
        *(void**)(it + 8) = h2;
        h2[0x41] = 1;
        *(void**)(h2 + 0x10) = r2;
        assert(SynAccIncIter_1417c72e0(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)r2);
        ++checks;
    }

    std::printf("SYNDICATE_D145_OK: six bodies, %d units, %d checks\n", 6, checks);
    return 0;
}
