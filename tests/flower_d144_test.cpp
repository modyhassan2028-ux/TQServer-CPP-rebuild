// D144 — the third batch of container bodies
#include "modules/flower/src/stl_tree.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower::stl;

int main() {
    int nBad = 0;
    static void (*s_prev)() = nullptr;
    (void)s_prev;
    g_pfnInvalidParameter = nullptr;

    // a head with begin +0x18 and size +0x20; the iterator's container holds
    // the head's address, exactly the layout 0x140d954f0 dereferences
    unsigned char head[0x40];
    std::memset(head, 0, sizeof head);
    *(uint64_t*)(head + 0x18) = 0x8;
    *(uint64_t*)(head + 0x20) = 0x40;
    void* cont[1];
    cont[0] = head;

    // ---- an iterator n back from a cursor
    void* it[2];
    it[0] = cont;
    it[1] = (void*)0x20;
    void* out[2];
    assert(IterOffsetBack(out, it, 2) == out);
    assert(out[0] == cont && out[1] == (void*)0x10);

    // ---- the copy that takes its offset from the node's +0x08
    unsigned char node[0x30];
    std::memset(node, 0, sizeof node);
    *(uint64_t*)(node + 8) = 0x18;
    void* out2[2];
    assert(IterCopyFromNode(out2, it, node) == out2);
    assert(out2[0] == cont && out2[1] == (void*)0x18);

    // ---- the iterator from a node, offset from a third object
    void* pNode[6];
    pNode[0] = cont;
    pNode[3] = (void*)0x8;
    pNode[4] = (void*)0x40;
    unsigned char from[0x10];
    std::memset(from, 0, sizeof from);
    *(uint64_t*)(from + 8) = 0x28;
    void* out3[2];
    assert(IterFromNodeChecked(out3, pNode, from) == out3);
    assert(out3[0] == cont && out3[1] == (void*)0x28);

    // ---- the container stands up around a fresh head
    unsigned char tree[0x40];
    std::memset(tree, 0, sizeof tree);
    TreeInit(tree);
    char* pHead = *(char**)(tree + 0x30);
    assert(pHead != nullptr);
    assert(*(uint8_t*)(pHead + 0x29) == 1);
    assert(*(char**)(pHead + 8) == pHead);
    assert(*(char**)pHead == pHead);
    assert(*(char**)(pHead + 0x10) == pHead);
    assert(*(uint64_t*)(tree + 0x38) == 0);
    ::operator delete(pHead);

    // ---- the out_of_range copy keeps both the text and the vftable
    g_uLogicErrorVft = 0xD1;
    g_uOutOfRangeVft = 0xD2;
    unsigned char src[0x40], dst[0x40];
    std::memset(src, 0, sizeof src);
    std::memset(dst, 0, sizeof dst);
    std::string text("past the end");
    LogicErrorCtor(src, &text);
    OutOfRangeCopyCtor(dst, src);
    assert(*(uintptr_t*)dst == 0xD2);
    assert(std::strcmp(LogicErrorWhat(dst), "past the end") == 0);
    LogicErrorDtor(src, 0);
    LogicErrorDtor(dst, 0);

    // ---- the last self-allocating node form
    void** pSelf = (void**)::operator new(sizeof(void*));
    *pSelf = nullptr;
    NodeSelfAllocE(pSelf);
    assert(*pSelf != nullptr && *(void**)*pSelf == pSelf);
    ::operator delete(*pSelf);
    ::operator delete(pSelf);
    (void)nBad;
    printf("FLOWER_D144_OK: iterator moves, tree init, out_of_range copy\n");
    return 0;
}
