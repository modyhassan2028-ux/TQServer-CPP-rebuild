#pragma once
// ============================================================
// Title.dll — Port — Unit D10: the CTitleMgr record map
//  (the MSVC tree kernel used by the mgr, mgr+0x08 base)
//  FUN_141974090 — the container proxy node
//  FUN_141973ad0 — lower_bound (the descent)
//  FUN_141974260 — find by key
//  FUN_141972330 — insert fixup (link + Lmost/Rmost)
//  FUN_141972930 — erase fixup (unlink + Lmost/Rmost)
//  FUN_141972430 — iterator deref (node+0x18)
//  FUN_141972510 / 141972470 — iterator ++ / --
//  FUN_141972220 — iterator ==
//  FUN_141972ab0 — iterator copy+++
//  FUN_141972ae0 / 141972990 — node new (0x30) / delete
//  FUN_141974360 — clear (erase-all + head free)
//  FUN_141972e10 — erase-all (range to end)
// Node layout (verbatim from the fixups):
//   +0x00 left, +0x08 parent, +0x10 right,
//   +0x18 key(int), +0x20 value ptr, +0x29 isnil
// Container (mgr+0x08): +0x00 proxy, +0x30 head,
//   +0x38 size
// ============================================================
#include <cstdint>
#include <cstdlib>

namespace title {

struct STreeNode {          // 0x30
    STreeNode* m_pLeft00;
    STreeNode* m_pParent08;
    STreeNode* m_pRight10;
    int32_t    m_nKey18;
    uint8_t    m_abPad1c[4];
    void*      m_pValue20;
    uint8_t    m_abPad28[1];
    uint8_t    m_bIsnil29;
    uint8_t    m_abPad2a[6];
};

struct SMapKernel {        // mgr+0x08
    void*      m_pProxy08;   // FUN_141974090
    uint8_t    m_abPad10[0x28];
    STreeNode* m_pHead38;    // the sentinel head
    int64_t    m_nSize40;    // mgr+0x40

    // ---- the ported kernel ----
    // FUN_141974090: make the proxy node
    void MakeProxyNode();
    // FUN_141973ad0: lower_bound -> iter {node}
    STreeNode* LowerBound(uint32_t uKey);
    // FUN_141974260: find -> node or null (exact match)
    STreeNode* FindNode(uint32_t uKey);
    // FUN_141972330: rotate RIGHT (the just-inserted
    // left child N rotates up over its parent P)
    void InsertFixup(STreeNode* pP, STreeNode* pN);
    // FUN_141972930: rotate LEFT (the twin)
    void EraseFixup(STreeNode* pP, STreeNode* pN);
    // FUN_141972430 deref / iterator ops on nodes
    static void* DerefValue(STreeNode* p) { return p + 1; }
    void Clear();   // FUN_141972e10 (erase-all)
    void Dtor();    // FUN_141974360 (the map dtor)
    // helpers
    STreeNode* NewNode();     // FUN_141972ae0 (0x30)
    static void FreeNode(STreeNode* p); // 141972990
    bool IsHead(STreeNode* p) const { return p == m_pHead38; }
};

} // namespace
