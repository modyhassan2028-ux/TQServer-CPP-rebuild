// D251 — CInstanceMgr: the lookup, CreateInstance and DestroyInstance, over a real map node set.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "modules/npcserver/unattributed/cinstancemgr.h"
#include "modules/npcserver/unattributed/cinstance.h"
#include "modules/npcserver/unattributed/map-insert-erase.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"

using namespace tq;

namespace {

struct Node {
    long long left, parent, right;
    unsigned long long key, value;
    unsigned char color, isnil;
};

long long aMgr[32];                 // the manager; its tree object starts at +0x48
Node* g_pHeadNode1 = nullptr;
Node* g_pHeadNode2 = nullptr;
long long aWrapper1[1], aWrapper2[1];
Node* g_aNodes[32];
int g_nNodes = 0;
void FreeNodes() { for (int i = 0; i < g_nNodes; ++i) std::free(g_aNodes[i]); g_nNodes = 0; }
Node* NewNode() { Node* p = (Node*)std::calloc(1, sizeof(Node)); g_aNodes[g_nNodes++] = p; return p; }
long long g_aArena[64];             // where the fake allocator hands out memory
int g_nArena = 0;
int g_logs = 0, g_mapReleases = 0, g_deleted = 0, g_invalids = 0;
const void* g_pLastMsg = nullptr;
long long g_nReleasedId = -1;
long long* g_pInstance = nullptr;
long long aWrapper[1];               // what the iterator owner points at: its first field is the tree

// CInstanceMgr carries two maps: the instance-type records at +8 (owner +8, head +0x38) and the live instances at
// +0x48 (owner +0x48, head +0x78). Both are the same tree object shape, 0x30 bytes apart from owner to head.
long long* Tree1() { return (long long*)((char*)aMgr + 0x08); }
long long* Tree2() { return (long long*)((char*)aMgr + 0x48); }
Node* Head1() { return g_pHeadNode1; }
Node* Head2() { return g_pHeadNode2; }

void* FakeNew(long long nBytes) {
    long long* p = &g_aArena[g_nArena];
    g_nArena += (nBytes / 8) + 1;
    std::memset(p, 0, (size_t)nBytes);
    return p;
}
void* FakeDelete(void* p) { (void)p; ++g_deleted; return nullptr; }
void Log(const void* pMsg, ...) { ++g_logs; g_pLastMsg = pMsg; }
void Invalid(void) { ++g_invalids; }
unsigned long long MapRelease(long long pSingleton, unsigned nId) {
    ++g_mapReleases; g_nReleasedId = (long long)nId; (void)pSingleton; return 1;
}
void InstanceDtor(long long* pObj, long long nFlag) { (void)nFlag; g_pInstance = pObj; }

long long aMapVt[4], aMapObj[4];
int g_mapOk = 1, g_mapCreates = 0;
unsigned MapId(void* pMap, long long nWhat) { (void)pMap; (void)nWhat; return 0x11; }
unsigned long long CreateMap(long long pSingleton, unsigned nMapId, unsigned nLow) {
    (void)pSingleton; (void)nMapId; (void)nLow;
    ++g_mapCreates;
    return g_mapOk ? 1 : 0;
}

void Reset() {
    FreeNodes();
    std::memset(aMgr, 0, sizeof aMgr);
    std::memset(g_aArena, 0, sizeof g_aArena);
    g_nArena = 0;
    g_logs = g_mapReleases = g_deleted = g_invalids = 0;
    g_pLastMsg = nullptr;
    g_nReleasedId = -1;
    g_pInstance = nullptr;

    Node* pH1 = NewNode();
    pH1->left = pH1->parent = pH1->right = (long long)pH1;
    pH1->isnil = 1;
    pH1->color = 1;                      // the head is black, as 0x140022a40 builds it
    g_pHeadNode1 = pH1;

    Node* pH2 = NewNode();
    pH2->left = pH2->parent = pH2->right = (long long)pH2;
    pH2->isnil = 1;
    pH2->color = 1;
    g_pHeadNode2 = pH2;

    aWrapper1[0] = (long long)Tree1();
    Tree1()[0] = (long long)aWrapper1;
    Tree1()[6] = (long long)pH1;
    Tree1()[7] = 0;

    aWrapper2[0] = (long long)Tree2();
    Tree2()[0] = (long long)aWrapper2;
    Tree2()[6] = (long long)pH2;
    Tree2()[7] = 0;
}

// one node in tree2, keyed by the type id, carrying the instance pointer at +0x20
Node* AddNode(unsigned nKey) {
    Node* pH = Head2();
    Node* pNode = NewNode();
    pNode->key = nKey;
    pNode->value = (unsigned long long)pNode;    // stands in for the instance pointer
    pNode->parent = (long long)pH;
    pNode->left = pH->right = 0;
    pNode->left = (long long)pH;
    pNode->right = (long long)pH;
    pH->parent = (long long)pNode;                // root
    pH->left = (long long)pNode;                  // leftmost
    pH->right = (long long)pNode;                 // rightmost
    Tree2()[7] = 1;
    return pNode;
}

// one node in tree1: the instance-type record, whose +0x20 is the map the new instance takes
Node* AddRecord(unsigned nKey, long long pMap) {
    Node* pH = Head1();
    Node* pNode = NewNode();
    pNode->key = nKey;
    pNode->left = pNode->right = (long long)pH;
    pNode->parent = (long long)pH;
    pH->parent = pH->left = pH->right = (long long)pNode;
    *(long long*)((char*)pNode + 0x20) = pMap;
    Tree1()[7] = 1;
    return pNode;
}

}  // namespace

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpcInvalidParameter = &Invalid;
    g_pfnNpc_14003cc10 = &MapRelease;
    g_pfnNpc_14003cd80 = &CreateMap;
    aMapVt[0x10 / 8] = (long long)&MapId;
    aMapObj[0] = (long long)aMapVt;
    g_pNpcModuleBase_1401045b8 = aMgr;          // the singletons hang off the same object

    assert(g_nNpcInstanceMgr == 3);
    int nFind = 0, nCreate = 0, nDestroy = 0;

    for (int i = 0; i < g_nNpcInstanceMgr; ++i) {
        const NpcInstanceMgrEntry& e = g_aNpcInstanceMgr[i];

        if (std::strcmp(e.pszKind, "find-instance") == 0) {
            typedef unsigned long long (*FindFn)(long long, unsigned);
            FindFn pfn = (FindFn)e.pfn;

            Reset();
            Node* pNode = AddNode(0x21);
            assert(pfn((long long)aMgr, 0x21) == (unsigned long long)pNode);   // the value at +0x20
            assert(pfn((long long)aMgr, 0x22) == 0);                          // no such type
            assert(g_invalids == 0);
            ++nFind;

        } else if (std::strcmp(e.pszKind, "create-instance") == 0) {
            typedef unsigned long long (*CreateFn)(long long, unsigned, unsigned, unsigned);
            CreateFn pfn = (CreateFn)e.pfn;

            // the instance-type record is not in the map: the literal line, and 0
            Reset();
            assert(pfn((long long)aMgr, 1, 2, 0x33) == 0);
            assert(g_logs == 1);
            assert(std::strcmp((const char*)g_pLastMsg,
                               "CInstanceMgr::CreateInstance InstanceType:%u not find") == 0);

            // the record is there, but the instance cannot be built (no map on the record)
            Reset();
            // the record exists but the map refuses to come up: two lines, the map one then 0x1400be0b0
            std::memset(g_aArena, 0, sizeof g_aArena);
            g_nArena = 0;
            g_mapOk = 0;
            g_logs = 0;
            AddRecord(0x33, (long long)aMapObj);
            assert(pfn((long long)aMgr, 1, 2, 0x33) == 0);
            assert(g_mapCreates == 1);
            assert(g_logs == 2 && g_pLastMsg == (const void*)0x1400be0b0);
            assert(Tree2()[7] == 0);
            g_mapOk = 1;

            // the happy path: the instance is built and its own type id ends up in the map
            Reset();
            AddRecord(0x33, (long long)aMapObj);
            assert(pfn((long long)aMgr, 0x11, 0x77, 0x33) == 1);
            assert(Tree2()[7] == 1);                    // the instance went into the live map
            bool bFound = false;
            Node* pWalk = (Node*)Head2()->parent;
            Node* pH = Head2();
            for (;;) {
                if (pWalk == pH) break;
                if (pWalk->key == 0x77) { bFound = true; assert(pWalk->value != 0); break; }
                pWalk = (Node*)(pWalk->key > 0x77 ? pWalk->left : pWalk->right);
            }
            assert(bFound);

        } else if (std::strcmp(e.pszKind, "destroy-instance") == 0) {
            typedef void (*DestroyFn)(long long, unsigned);
            DestroyFn pfn = (DestroyFn)e.pfn;

            // nothing of that type: nothing happens at all
            Reset();
            pfn((long long)aMgr, 0x21);
            assert(g_mapReleases == 0 && g_deleted == 0);

            // the instance is there: its map is released, the object is destroyed, and the entry is erased
            Reset();
            Node* pNode = AddNode(0x21);
            long long* pObject = &g_aArena[32];
            std::memset(pObject, 0, 0x18);
            pObject[0] = (long long)&InstanceDtor;      // slot 0
            *(unsigned*)((char*)pObject + 0xc) = 0x21;  // the map id the release reports
            *(long long*)((char*)pNode + 0x20) = (long long)pObject;
            pfn((long long)aMgr, 0x21);
            assert(g_mapReleases == 1 && g_nReleasedId == 0x21);
            assert(g_pInstance == pObject);             // the deleting destructor ran on it
            assert(g_deleted == 1);                     // and the node itself was freed
            assert(Tree2()[7] == 0);                    // the entry is gone
            assert(Head2()->parent == (long long)Head2());   // the tree is empty again
            ++nDestroy;

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    FreeNodes();
    assert(nFind == 1 && nDestroy == 1);
    std::printf("NPCSERVER_D251_OK: instance lookup, create and destroy\n");
    return 0;
}
