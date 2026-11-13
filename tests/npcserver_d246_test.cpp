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
static long long* InsertCore(long long* pMap, long long* pOutOwner, char bInsert,
                             long long* pHint, unsigned long long* pKey) {
    ++g_inserts;
    g_insertFlag = bInsert;
    g_pInsertHint = pHint;
    (void)pOutOwner; (void)pKey;
    assert(pMap == aMap);
    return g_aInsertAns;
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
    SetColor((long long*)aHeader, 0);
    SetNil((long long*)aHeader, 1);      // the head is nil

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
    g_pfnNpc_140024000 = &InsertCore;
    g_pfnNpc_140023290 = &RangeLookup;
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcInvalidParameter = &Invalid;

    assert(g_nNpcMapInsert == 3);
    int nInsert = 0, nErase = 0, nFind = 0;

    for (int i = 0; i < g_nNpcMapInsert; ++i) {
        const NpcMapInsertEntry& e = g_aNpcMapInsert[i];

        if (std::strcmp(e.pszKind, "insert-hinted") == 0) {
            typedef long long* (*InsertFn)(long long*, long long*, unsigned*);
            InsertFn pfn = (InsertFn)e.pfn;
            long long aOut[3];   // {owner, node, bool at +0x10}

            // a key that is already there: no new node, the pair carries the owner and the node found
            BuildTree(); ResetCase();
            unsigned nKey30 = 30;
            assert(pfn(aMap, aOut, &nKey30) == aOut);
            assert(g_inserts == 0);
            assert(aOut[0] == aMap[0]);
            assert((long long*)aOut[1] == g_pNode30);
            assert(((unsigned char*)aOut)[0x10] == 0);

            // a gap: the search hands 20 to the insert core with the "went left" answer
            BuildTree(); ResetCase();
            unsigned nKey25 = 25;
            pfn(aMap, aOut, &nKey25);
            assert(g_inserts == 1);
            assert((long long*)g_pInsertHint == g_pNode20);
            assert(g_insertFlag == false);
            assert(aOut[0] == g_aInsertAns[0] && aOut[1] == g_aInsertAns[1]);
            assert(((unsigned char*)aOut)[0x10] == 1);

            // above the root: the hint is 40 and the flag says the search went right
            BuildTree(); ResetCase();
            unsigned nKey35 = 35;
            pfn(aMap, aOut, &nKey35);
            assert(g_inserts == 1);
            assert((long long*)g_pInsertHint == g_pNode40);
            assert(g_insertFlag == true);

            // below the leftmost: the search stops on 10, which is the head's left child
            BuildTree(); ResetCase();
            unsigned nKey5 = 5;
            pfn(aMap, aOut, &nKey5);
            assert(g_inserts == 1);
            assert((long long*)g_pInsertHint == g_pNode10);
            assert(g_insertFlag == true);
            assert(nInsert == 0);
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

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    FreePool();
    assert(nInsert == 1 && nErase == 1 && nFind == 1);
    std::printf("NPCSERVER_D246_OK: insert-with-hint and the counted range erase\n");
    return 0;
}
