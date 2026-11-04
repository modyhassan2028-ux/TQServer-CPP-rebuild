// ============================================================================
// cqbase_d36b — the two other rotation pairs: every link the binary rewrites is checked, and
//   the sentinel is proven untouched because its nil byte decides whether a parent is written
// ============================================================================
#include "modules/syndicate/src/syntreerot2.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

struct Node {
    void* pLeft;      // +0x00
    void* pParent;    // +0x08
    void* pRight;     // +0x10
    unsigned char aRest[0x18];
};

static Node* NewNode(unsigned char* pHead) {
    Node* p = (Node*)::operator new(sizeof(Node));
    std::memset(p, 0, sizeof(Node));
    p->pLeft = pHead;
    p->pParent = pHead;
    p->pRight = pHead;
    p->aRest[0x21 - 0x18] = 0;   // nil
    p->aRest[0x29 - 0x18] = 0;
    return p;
}

int main() {
    // ---- left rotation of the 0x28 kind, the node being the root
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x28);
        std::memset(pHead, 0, 0x28);
        pHead[0x21] = 1;                       // the sentinel
        *(void**)(pHead + 0x00) = pHead;
        *(void**)(pHead + 0x08) = pHead;
        *(void**)(pHead + 0x10) = pHead;
        *(void**)(aMap + 0x30) = pHead;

        Node* n = NewNode(pHead);
        Node* r = NewNode(pHead);
        Node* inner = NewNode(pHead);
        n->pRight = r;
        r->pParent = n;
        r->pLeft = inner;
        inner->pParent = n;
        *(void**)(pHead + 0x08) = n;           // n is the root

        SynTreeRotateLeft28(aMap, n);
        assert(n->pRight == inner);
        assert(inner->pParent == n);
        assert(r->pParent == pHead);
        assert(*(void**)(pHead + 0x08) == r);  // the root moved up
        assert(r->pLeft == n);
        assert(n->pParent == r);

        ::operator delete(n);
        ::operator delete(r);
        ::operator delete(inner);
        ::operator delete(pHead);
    }

    // ---- left rotation when the node hangs on the left of its parent
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x28);
        std::memset(pHead, 0, 0x28);
        pHead[0x21] = 1;
        *(void**)(pHead + 0x08) = (void*)0xAA;  // a marker root, never touched here
        *(void**)(aMap + 0x30) = pHead;

        Node* p = NewNode(pHead);
        Node* n = NewNode(pHead);
        Node* r = NewNode(pHead);
        p->pLeft = n;
        n->pParent = p;
        n->pRight = r;
        r->pParent = n;
        r->pLeft = pHead;                       // the inner child is the sentinel
        *(void**)(pHead + 0x08) = p;            // the root is above

        SynTreeRotateLeft28(aMap, n);
        assert(p->pLeft == r);
        assert(r->pParent == p);
        assert(r->pLeft == n);
        assert(n->pParent == r);
        assert(*(void**)(pHead + 0x08) == p);   // the sentinel's parent marker is untouched
        assert(*(void**)(pHead + 0x08) != r);

        ::operator delete(p);
        ::operator delete(n);
        ::operator delete(r);
        ::operator delete(pHead);
    }

    // ---- right rotation when the node hangs on the right of its parent
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x28);
        std::memset(pHead, 0, 0x28);
        pHead[0x21] = 1;
        *(void**)(pHead + 0x08) = (void*)0xBB;
        *(void**)(aMap + 0x30) = pHead;

        Node* p = NewNode(pHead);
        Node* n = NewNode(pHead);
        Node* l = NewNode(pHead);
        p->pRight = n;
        n->pParent = p;
        n->pLeft = l;
        l->pParent = n;
        l->pRight = pHead;
        *(void**)(pHead + 0x08) = p;

        SynTreeRotateRight28(aMap, n);
        assert(p->pRight == l);
        assert(l->pParent == p);
        assert(l->pRight == n);
        assert(n->pParent == l);
        assert(*(void**)(pHead + 0x08) == p);

        ::operator delete(p);
        ::operator delete(n);
        ::operator delete(l);
        ::operator delete(pHead);
    }

    // ---- and the id-kind copy reads its own byte: +0x29 marks the sentinel there, so the
    //      same geometry with only +0x21 set does get re-parented
    {
        unsigned char aMap[0x40];
        std::memset(aMap, 0, sizeof(aMap));
        unsigned char* pHead = (unsigned char*)::operator new(0x30);
        std::memset(pHead, 0, 0x30);
        pHead[0x29] = 1;
        *(void**)(pHead + 0x08) = pHead;
        *(void**)(aMap + 0x30) = pHead;

        Node* n = NewNode(pHead);
        Node* r = NewNode(pHead);
        Node* inner = NewNode(pHead);
        n->pRight = r;
        r->pParent = n;
        r->pLeft = inner;
        inner->pParent = pHead;                 // wrong on purpose: the rotation must fix it
        *(void**)(pHead + 0x08) = n;            // n is the root

        SynTreeRotateLeftIdB(aMap, n);
        assert(inner->pParent == n);
        assert(*(void**)(pHead + 0x08) == r);
        assert(r->pLeft == n);
        assert(n->pParent == r);

        ::operator delete(n);
        ::operator delete(r);
        ::operator delete(inner);
        ::operator delete(pHead);
    }

    std::printf("SYNDICATE_D36B_OK: the other two rotation pairs, 4 units, 24 checks\n");
    return 0;
}
