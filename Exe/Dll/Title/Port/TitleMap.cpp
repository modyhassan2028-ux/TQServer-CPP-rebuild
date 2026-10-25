#include "TitleMap.h"
#include "TitleModule.h"   // g_fnAlloc / g_fnFree
#include <cstring>

namespace title {

// the kernel base = mgr+0x08 (this == &mgr.m_pProxy08)

// ============ FUN_141974090: the proxy node ============
// new(8); *node = param_1 (the map base); *param_1 = node
void SMapKernel::MakeProxyNode() {
    void** ppNode = (void**)g_fnAlloc(8);
    if (ppNode == nullptr) { /* new returns null: keep base */ }
    else { *ppNode = this; }
    m_pProxy08 = ppNode;
}

// ============ FUN_141973ad0: lower_bound ============
// descends from head->m_pParent08 (the root); key at
// node+0x18; isnil at +0x29 stops; keeps last node with
// key >= target. Returns the found node (head = end).
STreeNode* SMapKernel::LowerBound(uint32_t uKey) {
    STreeNode* pLast = m_pHead38;           // puVar4
    STreeNode* pCur = m_pHead38->m_pParent08;  // root
    while (pCur != nullptr && !pCur->m_bIsnil29) {
        STreeNode* pNext;
        if (pCur->m_nKey18 < uKey) {
            pNext = pCur->m_pRight10;
        } else {
            pNext = pCur->m_pLeft00;
            pLast = pCur;
        }
        pCur = pNext;
    }
    return pLast;
}

// ============ FUN_141974260: find (exact) ============
// same descent; exact match only, else null
STreeNode* SMapKernel::FindNode(uint32_t uKey) {
    STreeNode* pLast = m_pHead38;
    STreeNode* pCur = m_pHead38->m_pParent08;
    while (pCur != nullptr && !pCur->m_bIsnil29) {
        STreeNode* pNext;
        if (pCur->m_nKey18 < uKey) {
            pNext = pCur->m_pRight10;
        } else {
            pNext = pCur->m_pLeft00;
            pLast = pCur;
        }
        pCur = pNext;
    }
    if (pLast == m_pHead38 || uKey < pLast->m_nKey18)
        return nullptr;                     // end or not-found
    return pLast;
}

// ============ FUN_141972330: rotate RIGHT ============
// P (param_2) has the just-inserted node N as its LEFT
// child. N rotates up over P; P becomes N->right; N's
// old right subtree becomes P->left; head/root fixups.
void SMapKernel::InsertFixup(STreeNode* pP, STreeNode* pN) {
    STreeNode* pS = pN->m_pRight10;
    pP->m_pLeft00 = pS;                    // *param_2 = N->right
    if (!pS->m_bIsnil29)
        pS->m_pParent08 = pP;              // S->parent = P
    pN->m_pParent08 = pP->m_pParent08;     // N->parent = grandparent
    STreeNode* pG = pN->m_pParent08;
    if (pP == m_pHead38->m_pParent08) {    // P was the root
        m_pHead38->m_pParent08 = pN;       // head->parent = N (root)
    } else if (pP == pG->m_pRight10) {      // P was G's right
        pG->m_pRight10 = pN;
    } else {                               // P was G's left
        pG->m_pLeft00 = pN;
    }
    pN->m_pRight10 = pP;                   // N->right = P
    pP->m_pParent08 = pN;                  // P->parent = N
}

// ============ FUN_141972930: rotate LEFT ============
// the twin: P has N as its RIGHT child; N rotates up.
void SMapKernel::EraseFixup(STreeNode* pP, STreeNode* pN) {
    STreeNode* pS = pN->m_pLeft00;
    pP->m_pRight10 = pS;
    if (!pS->m_bIsnil29)
        pS->m_pParent08 = pP;
    pN->m_pParent08 = pP->m_pParent08;
    STreeNode* pG = pN->m_pParent08;
    if (pP == m_pHead38->m_pParent08) {
        m_pHead38->m_pParent08 = pN;
    } else if (pP == pG->m_pLeft00) {
        pG->m_pLeft00 = pN;
    } else {
        pG->m_pRight10 = pN;
    }
    pN->m_pLeft00 = pP;
    pP->m_pParent08 = pN;
}

// ============ FUN_141972ae0 / 141972990: node new/free =
// (the 0xffffffffffffffff/size < 0x30 max-count gate:
// dead for realistic counts — noted verbatim)
STreeNode* SMapKernel::NewNode() {
    STreeNode* p = (STreeNode*)g_fnAlloc(sizeof(STreeNode));
    if (p) { std::memset(p, 0, sizeof(*p)); p->m_bIsnil29 = 0; }
    return p;
}
void SMapKernel::FreeNode(STreeNode* p) { g_fnFree(p); }

// ============ FUN_141972c50: subtree destroy ============
// recursive: destroy the right subtree, free the node,
// continue down the left spine
static void SubtreeDestroy(STreeNode* p) {
    while (p != nullptr && !p->m_bIsnil29) {
        SubtreeDestroy(p->m_pRight10);
        STreeNode* pNext = p->m_pLeft00;
        g_fnFree(p);
        p = pNext;
    }
}

// ============ FUN_141972e10: erase-all (clear) ============
void SMapKernel::Clear() {
    STreeNode* p = m_pHead38->m_pParent08;   // the root
    while (p != nullptr && !p->m_bIsnil29) {
        SubtreeDestroy(p->m_pRight10);       // 141972c50
        STreeNode* pNext = p->m_pLeft00;
        g_fnFree(p);
        p = pNext;
    }
    m_pHead38->m_pParent08 = m_pHead38;      // root = head
    m_nSize40 = 0;                            // +0x38 of base
    m_pHead38->m_pLeft00 = m_pHead38;         // Lmost = head
    m_pHead38->m_pRight10 = m_pHead38;        // Rmost = head
}

// ============ FUN_141974360: the map dtor ============
// (clear + free the head + null out base fields)
void SMapKernel::Dtor() {
    Clear();
    g_fnFree(m_pHead38);
    m_pHead38 = nullptr;   // param_1[6] = 0
    m_nSize40 = 0;         // param_1[7] = 0
}

} // namespace
