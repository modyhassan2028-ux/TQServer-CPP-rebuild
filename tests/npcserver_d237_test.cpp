// D237 — the container node builders, the two erase-then-free destructors, and the four deleters.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/container-nodes.h"

using namespace tq;

static char g_aNode[64];
static char g_aHead[0x40];
static int g_news = 0, g_deletes = 0, g_erases = 0;
static void* g_pDeleted[4];
static long long* g_pEraseSet;

static char g_aArena[0x80];
static void* FakeNew(long long nBytes) {
    ++g_news;
    if (nBytes == 8) return g_aNode;              // the node
    if (nBytes == 0x30) return g_aHead;           // the sentinel head
    return g_aArena;
}
static void* FakeDelete(void* p) { g_pDeleted[g_deletes++ & 3] = p; return p; }

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcOperatorDelete = &FakeDelete;

    assert(g_nNpcContainerNode == 10);
    int nBuild = 0, nDtor = 0, nDel = 0;

    for (int i = 0; i < g_nNpcContainerNode; ++i) {
        const NpcContainerNodeEntry& e = g_aNpcContainerNode[i];
        assert(e.pszAddress && e.pszKind && e.pfn);

        if (std::strncmp(e.pszKind, "node-builder-", 13) == 0) {
            long long aObject[8];
            std::memset(aObject, 0xCC, sizeof aObject);
            std::memset(g_aNode, 0, sizeof g_aNode);
            std::memset(g_aHead, 0, sizeof g_aHead);
            g_news = 0;
            void* pRet = ((void* (*)(void*))e.pfn)(aObject);
            assert(pRet == aObject);
            assert(g_news == 2);                                  // the 8-byte node, then the head
            assert((void*)aObject[0] == (void*)g_aNode);           // the object points at it
            assert(*(void**)g_aNode == (void*)aObject);            // and it points back
            assert((void*)aObject[6] == (void*)g_aHead);           // the sentinel head
            assert(*(unsigned char*)(g_aHead + 0x29) == 1);        // flagged as the head
            assert(*(void**)(g_aHead + 8) == g_aHead);             // all three links close on the head
            assert(*(void**)(g_aHead + 0x10) == g_aHead);
            assert(*(void**)g_aHead == g_aHead);
            assert(aObject[7] == 0);
            assert(*(unsigned char*)(g_aHead + 0x28) == 1);        // set by the real allocator
            assert(*(unsigned char*)(g_aHead + 0x29) == 1);        // and then flagged by the builder
            ++nBuild;

        } else if (std::strncmp(e.pszKind, "destructor-", 11) == 0) {
            long long aSet[8];
            std::memset(aSet, 0, sizeof aSet);
            // an empty tree: the head's three links meet itself and its nil flag is set
            long long* pHead = (long long*)g_aHead;
            pHead[0] = (long long)g_aHead;
            pHead[1] = (long long)g_aHead;
            pHead[2] = (long long)g_aHead;
            *(unsigned char*)(g_aHead + 0x29) = 1;
            aSet[0] = (long long)g_aHead;                           // the iterator's owner slot
            aSet[6] = (long long)g_aHead;
            aSet[7] = 0x77;
            g_deletes = 0;
            ((void (*)(long long*))e.pfn)(aSet);
            assert(g_deletes == 1 && g_pDeleted[0] == (void*)g_aHead);  // the head is freed
            assert(aSet[6] == 0 && aSet[7] == 0);                   // and the set forgets it
            ++nDtor;

        } else if (std::strncmp(e.pszKind, "deleter-", 8) == 0) {
            long long aSet[8];
            std::memset(aSet, 0, sizeof aSet);
            aSet[0] = 0xC000;
            aSet[6] = (long long)g_aHead;
            g_deletes = 0; g_pDeleted[0] = g_pDeleted[1] = nullptr;
            ((void (*)(long long*))e.pfn)(aSet);
            // the base destructor runs first, so the head is released before the object itself
            assert(g_deletes == 2);                                 // the head, then the object
            assert(g_pDeleted[0] == (void*)g_aHead);
            assert(g_pDeleted[1] == (void*)0xC000);                 // *pSet, not pSet
            ++nDel;
        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nBuild == 4 && nDtor == 2 && nDel == 4);
    std::printf("NPCSERVER_D237_OK: 10 container node bodies\n");
    return 0;
}
