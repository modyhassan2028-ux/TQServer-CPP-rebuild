// D246 — the map's insert-with-hint and the counted range erase, over a real five-node tree.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "modules/npcserver/unattributed/map-insert-erase.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static long long* g_pInsertNode = nullptr;      // what the insert core answers
static long long  g_aInsertAns[2] = { 0x1111, 0x2222 };
static int g_inserts = 0, g_deletes = 0, g_invalids = 0;
static long long* g_pInsertHint = nullptr;
static char g_insertFlag = 1;
static void* g_pDeleted = nullptr;

static long long* g_pNode10; static long long* g_pNode20; static long long* g_pNode30;
static long long* g_pNode40; static long long* g_pNode50;
static long long aHeader[6];
static long long aMap[8];
static long long* g_pBegin = nullptr; static long long* g_pEnd = nullptr;
static long long aLookup[8];
static long long aOwner[1];

static void SetNil(long long* pNode, char c) { ((char*)pNode)[0x29] = c; }
static void SetColor(long long* pNode, char c) { ((char*)pNode)[0x28] = c; }
static long long* g_aPool[64];
static int g_nPool = 0;
static void FreePool() {
    for (int i = 0; i < g_nPool; ++i) std::free(g_aPool[i]);
    g_nPool = 0;
}
static long long* NewNode(unsigned nKey) {
    long long* p = (long long*)std::calloc(6, 8);
    assert(g_nPool < 64);
    g_aPool[g_nPool++] = p;
    p[3] = (long long)nKey;
    SetColor(p, 1);                 // black
    SetNil(p, 0);                   // a real node
    return p;
}
static long long* g_aNodePool[64];
static int g_nNodePool = 0;
static void* FakeNew(long long nBytes) {
    assert(nBytes == 0x30);
    ++g_inserts;
    long long* p = (long long*)std::calloc(6, 8);
    g_aNodePool[g_nNodePool++] = p;
    return p;
}
static void* FakeDelete(void* p) { ++g_deletes; g_pDeleted = p; return nullptr; }
static void Invalid(void) { ++g_invalids; }
static void RangeLookup(long long* pMap, long long* pOutRange, unsigned* pKey) {
    assert(pMap == aMap); (void)pKey;
    pOutRange[0] = aMap[0];
    pOutRange[1] = (long long)g_pBegin;
    pOutRange[2] = aMap[0];
    pOutRange[3] = (long long)g_pEnd;
}

static void BuildTree() {
    FreePool();
    g_pNode10 = NewNode(10); g_pNode20 = NewNode(20); g_pNode30 = NewNode(30);
    g_pNode40 = NewNode(40); g_pNode50 = NewNode(50);
    SetColor(g_pNode20, 0); SetColor(g_pNode40, 0);   // red

    g_pNode30[0] = (long long)g_pNode20; g_pNode30[1] = (long long)aHeader; g_pNode30[2] = (long long)g_pNode40;
    g_pNode20[0] = (long long)g_pNode10; g_pNode20[1] = (long long)g_pNode30; g_pNode20[2] = (long long)aHeader;
    g_pNode10[0] = (long long)aHeader;   g_pNode10[1] = (long long)g_pNode20; g_pNode10[2] = (long long)aHeader;
    g_pNode40[0] = (long long)aHeader;   g_pNode40[1] = (long long)g_pNode30; g_pNode40[2] = (long long)g_pNode50;
    g_pNode50[0] = (long long)aHeader;   g_pNode50[1] = (long long)g_pNode40; g_pNode50[2] = (long long)aHeader;

    std::memset(aHeader, 0, sizeof aHeader);
    aHeader[0] = (long long)g_pNode10;   // leftmost
    aHeader[1] = (long long)g_pNode30;   // root
    aHeader[2] = (long long)g_pNode50;   // rightmost
    aHeader[3] = 0;                      // the end value's key
    SetColor((long long*)aHeader, 1);    // the head is black, as 0x140022a40 builds it
    SetNil((long long*)aHeader, 1);      // and nil

    std::memset(aMap, 0, sizeof aMap);
    aMap[0] = (long long)aMap;           // the owner an iterator carries
    aMap[6] = (long long)aHeader;

    // the values the lookup answers with live at node+0x20
    *(long long*)((char*)g_pNode10 + 0x20) = 0x1A1A;
    *(long long*)((char*)g_pNode20 + 0x20) = 0x2B2B;
    *(long long*)((char*)g_pNode30 + 0x20) = 0x3C3C;
    *(long long*)((char*)g_pNode40 + 0x20) = 0x4D4D;
    *(long long*)((char*)g_pNode50 + 0x20) = 0x5E5E;

    // the lookup object: the owner at +8, the head at +0x38, and the owner's own first field is the tree
    std::memset(aLookup, 0, sizeof aLookup);
    aOwner[0] = (long long)aMap;
    aLookup[1] = (long long)aOwner;      // +8
    aLookup[7] = (long long)aHeader;     // +0x38
}

static void ResetCase() {
    g_inserts = g_deletes = g_invalids = 0;
    g_pInsertHint = nullptr;
    g_insertFlag = 1;
    g_pDeleted = nullptr;
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpc_140023290 = &RangeLookup;
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcInvalidParameter = &Invalid;

    assert(g_nNpcMapInsert == 4);
    int nInsert = 0, nErase = 0, nFind = 0, nRange = 0;

    for (int i = 0; i < g_nNpcMapInsert; ++i) {
        const NpcMapInsertEntry& e = g_aNpcMapInsert[i];

        if (std::strcmp(e.pszKind, "insert-hinted") == 0) {
            typedef long long* (*InsertFn)(long long*, long long*, unsigned*);
            InsertFn pfn = (InsertFn)e.pfn;
            long long aOut[3];   // {owner, node, bool at +0x10}

            // a key that is already there: no new node, the pair carries the owner and the node found
            BuildTree(); ResetCase();
            unsigned long long aKey30[2] = { 30, 0x1fe };   // {key, value}
            assert(pfn(aMap, aOut, (unsigned*)aKey30) == aOut);
            assert(g_inserts == 0);                       // nothing was allocated
            assert(aOut[0] == aMap[0]);
            assert((long long*)aOut[1] == g_pNode30);
            assert(((unsigned char*)aOut)[0x10] == 0);

            // a gap: the new node becomes 20's right child and the tree still links up
            BuildTree(); ResetCase();
            unsigned long long aKey25[2] = { 25, 0x1a9 };
            pfn(aMap, aOut, (unsigned*)aKey25);
            assert(g_inserts == 1);
            assert(((unsigned char*)aOut)[0x10] == 1);
            assert((long long*)aOut[1] == (long long*)g_aNodePool[g_nNodePool - 1]);
            assert(((long long*)aOut[1])[3] == 25);       // the key landed in the value pair
            assert((long long*)g_pNode20[2] == (long long*)aOut[1]);
            assert(((long long*)aOut[1])[1] == (long long)g_pNode20);

            // above the root: the new node becomes 40's left child
            BuildTree(); ResetCase();
            unsigned long long aKey35[2] = { 35, 0x253 };
            pfn(aMap, aOut, (unsigned*)aKey35);
            assert(g_inserts == 1);
            assert((long long*)g_pNode40[0] == (long long*)aOut[1]);

            // below the leftmost: the new node becomes 10's left child and the head follows it
            BuildTree(); ResetCase();
            unsigned long long aKey5[2] = { 5, 0x55 };
            pfn(aMap, aOut, (unsigned*)aKey5);
            assert(g_inserts == 1);
            assert((long long*)g_pNode10[0] == (long long*)aOut[1]);
            assert((long long*)aHeader[0] == (long long*)aOut[1]);   // the new leftmost
            for (int i = 0; i < g_nNodePool; ++i) std::free(g_aNodePool[i]);
            g_nNodePool = 0;
            ++nInsert;

        } else if (std::strcmp(e.pszKind, "erase-counted") == 0) {
            typedef long long (*EraseFn)(long long*, unsigned*);
            EraseFn pfn = (EraseFn)e.pfn;

            // an empty range counts nothing and leaves the tree alone
            BuildTree(); ResetCase();
            g_pBegin = g_pNode30; g_pEnd = g_pNode30;
            unsigned nKey30 = 30;
            assert(pfn(aMap, &nKey30) == 0);
            assert(g_deletes == 0);
            assert((long long*)aHeader[1] == g_pNode30);      // the root is untouched

            // the whole tree: five nodes counted, five freed, the head closed on itself
            BuildTree(); ResetCase();
            g_pBegin = g_pNode10; g_pEnd = (long long*)aHeader;
            unsigned nAny = 0;
            assert(pfn(aMap, &nAny) == 5);
            assert(g_deletes == 5);
            assert((long long*)aHeader[1] == (long long*)aHeader);   // the head points at itself
            assert((long long*)aHeader[0] == (long long*)aHeader);
            assert((long long*)aHeader[2] == (long long*)aHeader);
            assert(aMap[7] == 0);                                    // the size at +0x38 is zeroed

            // a single red leaf-range: one node counted and erased, its child moved up
            BuildTree(); ResetCase();
            g_pBegin = g_pNode20; g_pEnd = g_pNode30;
            unsigned nAny2 = 0;
            assert(pfn(aMap, &nAny2) == 1);
            assert(g_deletes == 1);
            assert(g_pDeleted == (void*)g_pNode20);
            assert((long long*)aHeader[0] == g_pNode10);             // the leftmost is still 10
            assert((long long*)g_pNode30[0] == g_pNode10);           // and it hangs off the root
            assert((long long*)g_pNode10[1] == g_pNode30);
            ++nErase;

        } else if (std::strcmp(e.pszKind, "find-value") == 0) {
            typedef unsigned long long (*FindFn)(long long, unsigned);
            FindFn pfn = (FindFn)e.pfn;

            BuildTree(); ResetCase();
            assert(pfn((long long)aLookup, 30) == 0x3C3C);      // the root's value
            assert(pfn((long long)aLookup, 10) == 0x1A1A);      // the leftmost
            assert(pfn((long long)aLookup, 50) == 0x5E5E);      // the rightmost
            assert(g_invalids == 0);

            // a key that is not there answers zero, on both sides of the tree
            BuildTree(); ResetCase();
            assert(pfn((long long)aLookup, 25) == 0);
            assert(pfn((long long)aLookup, 45) == 0);
            assert(pfn((long long)aLookup, 5) == 0);            // below the leftmost: the head stands in
            assert(pfn((long long)aLookup, 55) == 0);
            assert(g_invalids == 0);
            ++nFind;

        } else if (std::strcmp(e.pszKind, "equal-range") == 0) {
            typedef long long* (*RangeFn)(long long*, long long*, unsigned*);
            RangeFn pfn = (RangeFn)e.pfn;
            long long aOut[4];

            BuildTree(); ResetCase();
            unsigned long long aKey30[2] = { 30, 0x1fe };   // {key, value}
            assert(pfn(aMap, aOut, (unsigned*)aKey30) == aOut);
            assert((long long*)aOut[1] == g_pNode30);     // lower bound is the node itself
            assert((long long*)aOut[3] == g_pNode40);     // upper bound is its successor
            assert(aOut[0] == aMap[0] && aOut[2] == aMap[0]);

            // a key between two nodes: both bounds collapse on the upper neighbour
            BuildTree(); ResetCase();
            unsigned long long aKey25b[2] = { 25, 0x1a9 };
            pfn(aMap, aOut, (unsigned*)aKey25b);
            assert((long long*)aOut[1] == g_pNode30);
            assert((long long*)aOut[3] == g_pNode30);

            // the leftmost node: the range covers just it
            BuildTree(); ResetCase();
            unsigned nKey10 = 10;
            pfn(aMap, aOut, &nKey10);
            assert((long long*)aOut[1] == g_pNode10);
            assert((long long*)aOut[3] == g_pNode20);

            // below everything: an empty range standing on the leftmost node
            BuildTree(); ResetCase();
            unsigned long long aKey5b[2] = { 5, 0x55 };
            pfn(aMap, aOut, (unsigned*)aKey5b);
            assert((long long*)aOut[1] == g_pNode10);
            assert((long long*)aOut[3] == g_pNode10);

            // the rightmost node: the upper bound is the head, i.e. end()
            BuildTree(); ResetCase();
            unsigned nKey50 = 50;
            pfn(aMap, aOut, &nKey50);
            assert((long long*)aOut[1] == g_pNode50);
            assert((long long*)aOut[3] == (long long*)aHeader);

            // above everything: empty, but still anchored on the head
            BuildTree(); ResetCase();
            unsigned nKey99 = 99;
            pfn(aMap, aOut, &nKey99);
            assert((long long*)aOut[3] == (long long*)aHeader);
            assert(g_invalids == 0);
            ++nRange;

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    FreePool();
    assert(nInsert == 1 && nErase == 1 && nFind == 1 && nRange == 1);
    std::printf("NPCSERVER_D246_OK: insert-with-hint and the counted range erase\n");
    return 0;
}
