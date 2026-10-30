// D141 — the compiler-emitted checked iterators of Flower.dll
#include "modules/flower/src/stl_iterators.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
using namespace flower::stl;

static int s_bad;
static void OnBad() { s_bad++; }

// head node: +0x18 begin, +0x20 size, +0x30 end sentinel
struct Head {
    uint64_t pad0, pad1, pad2;   // 0x00..0x17
    uint64_t uBegin;             // +0x18
    uint64_t uSize;              // +0x20
    uint64_t pad3;               // +0x28
    uint64_t uEnd;               // +0x30
};
static Head s_head;
static void* s_container[2];     // [0] = &s_head

int main() {
    g_pfnInvalidParameter = OnBad;
    s_container[0] = &s_head;
    s_head.uBegin = 8;
    s_head.uSize = 0x40;
    s_head.uEnd = 0x50;

    CheckedIterator a{s_container, 0x10};
    CheckedIterator b{s_container, 0x10};
    CheckedIterator c{s_container, 0x18};

    // ---- equality / inequality, and the compatibility guard
    s_bad = 0;
    assert(IterEq(&a, &b) == true && IterEq(&a, &c) == false);
    assert(IterNe(&a, &c) == true && IterNe(&a, &b) == false);
    assert(IterEq2(&a, &b) == true && s_bad == 0);
    CheckedIterator bad{a.pContainer, 0x10};
    bad.pContainer = nullptr;
    s_bad = 0;
    IterEq(&bad, &b);
    assert(s_bad == 1);
    bad.pContainer = (void*)0x1234;
    s_bad = 0;
    IterEq(&bad, &b);
    assert(s_bad == 1);

    // ---- the offset read: in range answers the offset, past it complains
    s_bad = 0;
    assert(IterOffset(&a) == 0x10 && s_bad == 0);
    CheckedIterator far{s_container, 0x41};
    IterOffset(&far);
    assert(s_bad == 1);

    // ---- ++ moves eight bytes and keeps the bound check
    s_bad = 0;
    a.uOffset = 0x8;
    IterNext(&a);
    assert(a.uOffset == 0x10 && s_bad == 0);
    a.uOffset = 0x40;
    IterNext(&a);
    assert(s_bad == 1 && a.uOffset == 0x48);

    // ---- the tree value sits 0x18 into the node, the end sentinel complains
    CheckedIterator t{s_container, 0x28};
    s_bad = 0;
    assert(IterTreeValue(&t) == 0x40 && s_bad == 0);
    t.uOffset = 0x50;
    IterTreeValue(&t);
    assert(s_bad == 1);

    // ---- advance by n: the result must stay inside begin..size
    s_bad = 0;
    CheckedIterator v{s_container, 0x10};
    IterAdvance(&v, 2);
    assert(v.uOffset == 0x20 && s_bad == 0);
    CheckedIterator w{s_container, 0x10};
    IterAdvance(&w, 0x40);
    assert(s_bad == 1 && w.uOffset == 0x210);

    // ---- the growth guard throws length_error with the original text
    bool bThrown = false;
    try {
        ThrowVectorTooLong();
    } catch (const std::length_error& e) {
        bThrown = true;
        assert(std::strcmp(e.what(), "vector<T> too long") == 0);
    }
    assert(bThrown);

    // ---- the two copy constructions keep the message and set the vftable
    g_uLogicErrorVft = 0xB1;
    g_uLengthErrorVft = 0xB2;
    unsigned char src[0x40];
    unsigned char dst[0x40];
    std::memset(src, 0, sizeof src);
    std::memset(dst, 0, sizeof dst);
    std::string text(80, 'q');            // long enough for the heap form
    LogicErrorCtor(src, &text);
    LogicErrorCopyCtor(dst, src);
    assert(*(uintptr_t*)dst == 0xB1);
    assert(std::strcmp(LogicErrorWhat(dst), text.c_str()) == 0);
    LogicErrorDtor(dst, 0);               // frees the copied heap text
    std::memset(dst, 0, sizeof dst);
    LengthErrorCopyCtor(dst, src);
    assert(*(uintptr_t*)dst == 0xB2);
    assert(std::strcmp(LogicErrorWhat(dst), text.c_str()) == 0);
    LogicErrorDtor(src, 0);
    LogicErrorDtor(dst, 0);

    printf("FLOWER_D141_OK: checked iterators + length_error guard\n");
    return 0;
}
