// D160 — four bodies: the per-element walk 0x1417c8d80, the two pair fillers 0x1417c8eb0 /
//   0x1417c8ed0 and the clear 0x1417c8ef0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
extern void (*g_pfnLogic_1417f2fdc)(void* p);
void SynAccEachWalk_1417c8d80(void* pThis, unsigned int uMode);
void* SynAccClear_1417c8ef0(void* pTree);
void* SynAccPairLeftHeader_1417c8eb0(void* pTree, void* pOut);
void* SynAccPairHeaderLeft_1417c8ed0(void* pTree, void* pOut);
}

static int g_freed = 0;
static void FreeHook(void* p) { (void)p; ++g_freed; }
static int g_elems = 0;
static unsigned int g_mode = 0;
static void ElemHook(void* p, unsigned int m) { (void)p; ++g_elems; g_mode = m; }
namespace tq { extern void (*g_pfnSynPerElem_14179bf60)(void*, unsigned int); }

int main() {
    using namespace tq;

    alignas(16) unsigned char tree[0x40], h[0x60], n1[0x60], n2[0x60], stop[0x60];
    std::memset(tree, 0, sizeof tree); std::memset(h, 0, sizeof h);
    std::memset(n1, 0xCD, sizeof n1); std::memset(n2, 0xCD, sizeof n2);
    std::memset(stop, 0, sizeof stop);
    stop[0x29] = 1;

    // ---- the pair fillers
    *(void**)(tree) = n1;
    *(void**)(tree + 0x30) = h;
    *(void**)(h) = n2;
    unsigned char out[0x20];
    std::memset(out, 0, sizeof out);
    assert(SynAccPairLeftHeader_1417c8eb0(tree, out) == (void*)out);
    assert(*(void**)out == (void*)n1);
    assert(*(void**)(out + 8) == (void*)n2);   // the header's first qword, not the header
    std::memset(out, 0, sizeof out);
    assert(SynAccPairHeaderLeft_1417c8ed0(tree, out) == (void*)out);
    assert(*(void**)out == (void*)n1);
    assert(*(void**)(out + 8) == (void*)h);    // here it is the header itself

    // ---- the per-element walk: the immediate end, then one element handed over
    {
        alignas(16) unsigned char self[0x40], holder[0x60];
        std::memset(self, 0, sizeof self); std::memset(holder, 0, sizeof holder);
        holder[0x29] = 1;
        *(void**)(self + 0x38) = holder;
        *(void**)(holder) = holder;             // the cursor is already the end
        *(void**)(self + 8) = holder;
        g_elems = 0;
        SynAccEachWalk_1417c8d80(self, 4);
        assert(g_elems == 0);
    }
    {
        alignas(16) unsigned char self[0x40], holder[0x60], node[0x60], st[0x60], ele[0x10];
        std::memset(self, 0, sizeof self); std::memset(holder, 0, sizeof holder);
        std::memset(node, 0, sizeof node); std::memset(st, 0, sizeof st);
        st[0x29] = 1; holder[0x29] = 1;
        *(void**)(self + 0x38) = holder;
        *(void**)(holder) = node;               // the cursor
        *(void**)(self + 8) = node;             // the node the check compares
        *(void**)(node) = st;                   // the lead
        *(void**)(node + 0x20) = ele;           // the element
        *(void**)(node + 0x10) = st;            // the step stops at once
        *(void**)(node + 0x8) = holder;
        g_elems = 0; g_mode = 0;
        g_pfnSynPerElem_14179bf60 = &ElemHook;
        SynAccEachWalk_1417c8d80(self, 11);
        assert(g_elems == 1);                   // handed over exactly once before the walk ends
        assert(g_mode == 11);
    }

    // ---- the clear: the 0x0 chain loses its 0x10 subtrees, every node is freed, the header resets
    {
        alignas(16) unsigned char t2[0x40], hd[0x60], root[0x60], child[0x60], st2[0x60];
        std::memset(t2, 0, sizeof t2); std::memset(hd, 0, sizeof hd);
        std::memset(root, 0, sizeof root); std::memset(child, 0, sizeof child);
        std::memset(st2, 0, sizeof st2);
        st2[0x29] = 1; hd[0x29] = 1;
        *(void**)(t2 + 0x30) = hd;
        *(void**)(t2 + 0x38) = (void*)3;        // the size
        *(void**)(hd + 8) = root;
        *(void**)(root) = child;                // the 0x0 chain
        *(void**)(root + 0x10) = st2;           // nothing to destroy on the 0x10 side
        *(void**)(child) = st2;
        *(void**)(child + 0x10) = st2;
        g_freed = 0;
        g_pfnLogic_1417f2fdc = &FreeHook;
        assert(SynAccClear_1417c8ef0(t2) == (void*)t2);
        assert(g_freed == 2);                   // root and child
        assert(*(void**)(hd + 8) == (void*)hd); // the header names itself again
        assert(*(void**)hd == (void*)hd);
        assert(*(void**)(hd + 0x10) == (void*)hd);
        assert(*(void**)(t2 + 0x38) == nullptr);// and the size is zero
        g_pfnLogic_1417f2fdc = nullptr;
    }

    std::printf("SYNDICATE_D160_OK: per-element walk, pair fillers, clear\n");
    return 0;
}
