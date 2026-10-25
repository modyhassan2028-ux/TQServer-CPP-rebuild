// ============================================================
// Title.dll — Unit D10 regression: the mgr record map
// (the MSVC-style tree kernel, mgr+0x08 base)
// Must print TITLE-D10-OK.
#include "../Exe/Dll/Title/Port/TitleMap.h"
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace title;

int main() {
    // memory tracking
    std::vector<void*> vecLive;
    g_fnAlloc = [&](size_t n){ void* p = calloc(1, n); vecLive.push_back(p); return p; };
    g_fnFree  = [&](void* p){
        for (size_t i = 0; i < vecLive.size(); ++i)
            if (vecLive[i] == p) { vecLive.erase(vecLive.begin()+i); break; }
        free(p); };

    // ===== 1. the head ctor (141972cf0 model, D3) =====
    SMapKernel map; std::memset(&map, 0, sizeof(map));
    STreeNode* pHead = map.NewNode();
    pHead->m_pLeft00 = pHead; pHead->m_pParent08 = pHead;
    pHead->m_pRight10 = pHead; pHead->m_bIsnil29 = 1;
    map.m_pHead38 = pHead;
    map.MakeProxyNode();       // FUN_141974090
    assert(map.m_pProxy08 != nullptr);
    assert(*(void**)map.m_pProxy08 == (void*)&map);

    // ===== 2. insert at root + rotations (move-to-root) ====
    auto insertRoot = [&](uint32_t k, void* v){
        STreeNode* n = map.NewNode();
        n->m_nKey18 = (int32_t)k; n->m_pValue20 = v;
        if (map.m_pHead38->m_pParent08 == map.m_pHead38) {
            // first: attach as root
            map.m_pHead38->m_pParent08 = n;
            n->m_pParent08 = map.m_pHead38;
            n->m_pLeft00 = map.m_pHead38; n->m_pRight10 = map.m_pHead38;
        } else {
            // descend to the insert parent
            STreeNode* p = map.m_pHead38->m_pParent08;
            STreeNode* parent = map.m_pHead38;
            while (!p->m_bIsnil29) {
                parent = p;
                p = (p->m_nKey18 < (int32_t)k) ? p->m_pRight10 : p->m_pLeft00;
            }
            if (parent->m_nKey18 < (int32_t)k) {
                parent->m_pRight10 = n;   // as the RIGHT child
                n->m_pParent08 = parent;
                n->m_pLeft00 = map.m_pHead38; n->m_pRight10 = map.m_pHead38;
                map.EraseFixup(parent, n);   // rotate LEFT twin
            } else {
                parent->m_pLeft00 = n;
                n->m_pParent08 = parent;
                n->m_pLeft00 = map.m_pHead38; n->m_pRight10 = map.m_pHead38;
                map.InsertFixup(parent, n);  // rotate RIGHT
            }
        }
        map.m_nSize40++;
    };

    insertRoot(50, (void*)1);
    assert(map.m_pHead38->m_pParent08->m_nKey18 == 50);
    insertRoot(30, (void*)2);
    assert(map.m_pHead38->m_pParent08->m_nKey18 == 30); // rotated up!
    assert(map.m_pHead38->m_pParent08->m_pRight10->m_nKey18 == 50);
    // 70 attaches as 50's right child then rotates up
    // over 50 -> takes 50's slot as 30's right child
    insertRoot(70, (void*)3);
    assert(map.m_pHead38->m_pParent08->m_nKey18 == 30);  // root stays
    STreeNode* pR = map.m_pHead38->m_pParent08->m_pRight10;
    assert(pR->m_nKey18 == 70);
    assert(pR->m_pLeft00->m_nKey18 == 50);

    // ===== 3. find + lower_bound =====
    assert(map.FindNode(30) != nullptr);
    assert(map.FindNode(30)->m_pValue20 == (void*)2);
    assert(map.FindNode(50)->m_pValue20 == (void*)1);
    assert(map.FindNode(70) != nullptr);
    assert(map.FindNode(99) == nullptr);
    // lower_bound: first key >= target
    assert(map.LowerBound(31)->m_nKey18 == 50);
    assert(map.LowerBound(10)->m_nKey18 == 30);
    assert(map.LowerBound(70)->m_nKey18 == 70);
    assert(map.LowerBound(71) == map.m_pHead38);  // end

    // ===== 4. deref: value at node+0x18 (the pair area)
    STreeNode* pN = map.FindNode(30);
    int32_t* pPair = (int32_t*)((uint8_t*)pN + 0x18);
    assert(*pPair == 30);

    // ===== 5. clear (141972e10) keeps the head =====
    size_t nBefore = vecLive.size();
    map.Clear();
    assert(vecLive.size() == nBefore - 3);       // 3 data nodes freed
    assert(map.m_pHead38 == pHead);              // head alive
    assert(map.m_pHead38->m_pParent08 == pHead); // re-circularized
    assert(map.m_nSize40 == 0);
    assert(map.FindNode(30) == nullptr);

    // ===== 6. the dtor (141974360) frees the head too ==
    map.Dtor();
    assert(vecLive.size() == 1);                 // just the proxy
    assert(map.m_pHead38 == nullptr);

    std::printf("TITLE-D10-OK: the mgr record map kernel verbatim - the "
        "141974090 proxy node, the 141973ad0 lower_bound descent "
        "(key@+0x18, isnil@+0x29), the 141974260 exact find, the ROTATION "
        "decode: 141972330 = rotate RIGHT / 141972930 = rotate LEFT "
        "(the move-to-root insert!), the 141972c50 recursive subtree "
        "destroy + the 141972e10 left-spine clear with the head "
        "re-circularization, and the 141974360 dtor\n");
    return 0;
}
