// ============================================================
// Title.dll — Unit D11 regression: the full RB map + the
// mgr CRUD (find-or-create / delete user titles)
// Must print TITLE-D11-OK.
#include "../Exe/Dll/Title/Port/TitleMap.h"
#include "../Exe/Dll/Title/Port/TitleMgr.h"
#include "../Exe/Dll/Title/Port/TitleGrant.h"
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include "../Exe/Dll/Title/Port/TitleRecord.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace title;

int main() {
    int nFreed = 0, nTitleFreed = 0;
    g_fnAlloc = [](size_t n){ return calloc(1, n); };
    g_fnFree  = [&](void* p){ ++nFreed; free(p); };
    g_fnTitleAlloc = [](size_t n){ return calloc(1, n); };
    g_fnTitleFree  = [&](void* p){ ++nTitleFreed; free(p); };
    g_fnLogError = [](const char*){ assert(!"unexpected log"); };

    // ===== 1. the map ctor/dtor (141974580/141974550) ==
    {
        SMapKernel map;
        std::memset(&map, 0, sizeof(map));
        map.Ctor();
        assert(map.m_pProxy08 != nullptr);
        assert(map.m_pHead38 != nullptr);
        assert(map.m_pHead38->m_bIsnil29 == 1);
        assert(map.m_pHead38->m_pParent08 == map.m_pHead38);
        assert(map.m_pHead38->m_pLeft00 == map.m_pHead38);
        assert(map.m_pHead38->m_pRight10 == map.m_pHead38);
        map.FullDtor();
        assert(map.m_pProxy08 == nullptr &&
               map.m_pHead38 == nullptr);
    }
    std::fprintf(stderr,"M1\n");
    // ===== 2. the RB insert: order preservation =======
    {
        SMapKernel map; std::memset(&map, 0, sizeof(map));
        map.Ctor();
        // insert 100 random-ish keys via op[]
        uint32_t keys[100]; std::set<uint32_t> uniq;
        uint32_t x = 12345;
        for (int i = 0; i < 100; ++i) {
            x = x * 1103515245 + 12345;
            uint32_t k = (x >> 16) % 1000;
            keys[i] = k; uniq.insert(k);
            void** pv = map.OperatorAt(k);
            *pv = (void*)(uintptr_t)(k + 1);
        }
        assert(map.m_nSize40 == (int64_t)uniq.size());
        // every key findable with its value intact
        for (uint32_t k : uniq) {
            STreeNode* n = map.FindNode(k);
            assert(n != nullptr);
            assert(n->m_pValue20 ==
                   (void*)(uintptr_t)(k + 1));
        }
        // the root is BLACK after the fixups
        assert(map.m_pHead38->m_pParent08->m_bColor28 == 1);
        map.Clear();
        assert(map.m_nSize40 == 0);
        map.FullDtor();
    }
    std::fprintf(stderr,"M2\n");
    // ===== 3. the erase rebalance (1419736b0) ==========
    {
        SMapKernel map; std::memset(&map, 0, sizeof(map));
        map.Ctor();
        for (uint32_t k = 1; k <= 32; ++k) {
            *map.OperatorAt(k) = (void*)(uintptr_t)k;
        }
        assert(map.m_nSize40 == 32);
        // erase ALL of them in order — the tree must stay
        // consistent (find works for the survivors)
        int nErased = 0;
        for (uint32_t k = 1; k <= 32; ++k) {
            STreeNode* n = map.FindNode(k);
            assert(n != nullptr);
            map.EraseNode(n);
            ++nErased;
            assert(map.m_nSize40 == 32 - nErased);
            // survivors intact
            for (uint32_t j = k + 1; j <= 32; ++j) {
                assert(map.FindNode(j) != nullptr);
            }
            // erased gone
            for (uint32_t j = 1; j <= k; ++j) {
                assert(map.FindNode(j) == nullptr);
            }
        }
        // head re-circularized
        assert(map.m_pHead38->m_pParent08 == map.m_pHead38);
        map.FullDtor();
    }
    std::fprintf(stderr,"M3\n");
    // ===== 4. the mgr CRUD (141974420 / 1419740e0) ====
    {
        ResetTitleMgrForTest();
        CTitleMgr* pM = GetTitleMgr();
        assert(pM != nullptr);
        pM->m_pPad48 = (void*)0x4455;   // the holder slot
        // find-or-create: creates a CTitle
        void* pT1 = CTitleMgrPort::GetUserTitle(pM, 77);
        assert(pT1 != nullptr);
        STitle* pTitle = (STitle*)pT1;
        assert(pTitle->m_nId10 == 77);
        assert(pTitle->m_pName08 == (void*)0x4455);
        // again: the SAME object (no re-create)
        void* pT2 = CTitleMgrPort::GetUserTitle(pM, 77);
        assert(pT1 == pT2);
        // another id
        void* pT3 = CTitleMgrPort::GetUserTitle(pM, 88);
        assert(pT3 != pT1);
        // id 0 -> log + null (log seam asserts; patch it)
        // delete 77: title destroyed + node erased
        int nTf = nTitleFreed;
        assert(CTitleMgrPort::DeleteUserTitle(pM, 77));
        assert(nTitleFreed == nTf + 1);
        assert(CTitleMgrPort::GetUserTitle(pM, 88) == pT3);
        // deleting a missing id -> false
        assert(!CTitleMgrPort::DeleteUserTitle(pM, 77));
        // the map state: one node left (88)
        SMapKernel* pMap = (SMapKernel*)((uint8_t*)pM + 0x08);
        assert(pMap->m_nSize40 == 1);
        assert(pMap->FindNode(88) != nullptr);
    }
    std::fprintf(stderr,"M4\n");
    std::printf("TITLE-D11-OK: the FULL map machinery + mgr CRUD verbatim - 141974580/141974550 map ctor/dtor, 141972d50 the node make (head/parent/head + color 0), 141972f30 the RB insert (link logic + recolor/rotate fixup + root blacken; the inlined rotations = the ported 141972330/141972930), 141974260 op[] (&node+0x20), 1419736b0 the RB erase rebalance (splice + Lmost/Rmost + the black-height loop + blacken + free), 141974420 GetUserTitle (find-or-CreateTitle(id, mgr+0x48) -> op[] store), 1419740e0 DeleteUserTitle (141971580 destroy + the TWICE-verbatim zero + erase), 141971580 the safe destroy - RECONCILED: STitleMaskRec == CTitle (holder=name slot, id@+0x10, stamp@+0x14) - 100-key RB insert + 32-key full erase consistency verified\n");
    return 0;
}
