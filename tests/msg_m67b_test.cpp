// M67b unit test — the broadcast queue: ctor
// (1400f03b0), update (1400ef8d0), list append
// (1400a5f80), node (14009ad30), sentinel
// (14009a2a0)
#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <stdexcept>
#if defined(__SANITIZE_ADDRESS__)
#include <sanitizer/lsan_interface.h>
#define HAVE_LSAN 1
#elif defined(__has_feature)
#if __has_feature(address_sanitizer)
#include <sanitizer/lsan_interface.h>
#define HAVE_LSAN 1
#endif
#endif
#include "MsgBcastQueue.h"
#include "MsgBcastVector.h"
using namespace msg;

static int s_nInvalid = 0;
static void TInvalid() { ++s_nInvalid; }

struct QFixture {
    SBcastQ q;
    void*   pAnchCell;   // list anchor cell
    uint64_t* aNode;     // node data array
    void*  nodes[8];
    uint64_t* pairs;     // src vector buffer
    size_t nNodes;
    QFixture() : pAnchCell(nullptr), aNode(nullptr),
                 pairs(nullptr), nNodes(0) {
        std::memset(&q, 0, sizeof q);
    }
    // build a src-style queue: K nodes + vector
    void Build(size_t k, uint64_t firstVal,
               uint64_t pairSecondOver = 0) {
        pAnchCell = operator new(8);
        *(void***)pAnchCell =
            (void**)((char*)&q + 0x10);
        *(void***)((char*)&q + 0x10) = (void**)pAnchCell;
        q.m_pSent = BcastSentNew();
        q.m_qSize = 0;
        // append k nodes: data[i].qword0 = v+i
        for (size_t i = 0; i < k; i++) {
            uint64_t data[6];
            std::memset(data, 0, sizeof data);
            data[0] = firstVal + i;
            void* s = q.m_pSent;
            void* n = BcastListNodeNew(
                s, *(void**)((char*)s + 8), data);
            *(void**)((char*)s + 8) = n;
            *(void**)(*(void**)((char*)n + 8)) = n;
            q.m_qSize++;
            nodes[i] = n;
        }
        nNodes = k;
        // vector pairs {0xAA.., node[i]} (or the
        // override for guard tests)
        pairs = (uint64_t*)operator new(
            (k ? k : 1) * 0x10);
        for (size_t i = 0; i < k; i++) {
            pairs[i*2] = 0xA0000 + i;
            pairs[i*2+1] = pairSecondOver
                ? pairSecondOver
                : (uint64_t)nodes[i];
        }
        q.m_vFirst = pairs;
        q.m_vLast = (char*)pairs + k * 0x10;
        q.m_vCap = (char*)pairs + k * 0x10 + 0x40;
        q.m_q78 = 0x7878; q.m_q80 = 0x8080;
        q.m_dw88 = 0x88888888;
        *(uint8_t*)((char*)&q + 8) = 7;
        // vector anchor cell
        void* vc = operator new(8);
        *(void***)vc = (void**)((char*)&q + 0x48);
        *(void***)((char*)&q + 0x48) = (void**)vc;
    }
    void Cleanup() {
        for (size_t i = 0; i < nNodes; i++)
            operator delete(nodes[i]);
        operator delete((void*)q.m_vFirst);
        operator delete((void*)q.m_pSent);
        operator delete(pAnchCell);
        operator delete(
            *(void**)((char*)&q + 0x48));
    }
};

int main() {
    g_fnBcastInvalidParam = TInvalid;
    printf("M67b start\n"); fflush(stdout);

    // ==== S1: sentinel (9a2a0) + node (9ad30) ====
    {
        void* s = BcastSentNew();
        assert(*(void**)s == s &&
               *(void**)((char*)s + 8) == s);
        operator delete(s);
        uint64_t data[6] = {1,2,3,4,5,6};
        void* n = BcastListNodeNew(
            (void*)0x11, (void*)0x22, data);
        assert(n != nullptr);
        uint64_t* pn = (uint64_t*)n;
        assert(pn[0] == 0x11 && pn[1] == 0x22);
        assert(pn[2] == 1 && pn[7] == 6);
        operator delete(n);
        printf("S1 ok (sent/node)\n"); fflush(stdout);
    }

    // ==== S2: ctor with empty src (f03b0+ef8d0) ====
    {
        QFixture src;
        src.Build(0, 0);
        SBcastQ* dst = (SBcastQ*)operator new(
            sizeof(SBcastQ));
        std::memset(dst, 0, sizeof(SBcastQ));
        SBcastQ* r = BcastQCreate(dst, &src.q);
        assert(r == dst);
        // anchors wired
        void* la = *(void**)((char*)dst + 0x10);
        assert(la != nullptr &&
               *(void**)la == (char*)dst + 0x10);
        void* va = *(void**)((char*)dst + 0x48);
        assert(va != nullptr &&
               *(void**)va == (char*)dst + 0x48);
        // sentinel + size + vector nulls
        assert(dst->m_pSent != nullptr);
        assert(*(void**)dst->m_pSent ==
               dst->m_pSent);
        assert(dst->m_qSize == 0);
        assert(dst->m_vFirst == nullptr);
        // fields + byte
        assert(dst->m_q78 == 0x7878 &&
               dst->m_q80 == 0x8080 &&
               dst->m_dw88 == 0x88888888);
        assert(*(uint8_t*)((char*)dst + 8) == 7);
        operator delete(la);
        operator delete(va);
        operator delete(dst->m_pSent);
        operator delete(dst->m_vFirst);
        operator delete(dst);
        src.Cleanup();
        printf("S2 ok (ctor empty)\n"); fflush(stdout);
    }

    // ==== S3: full update 3 nodes + 3 pairs ====
    {
        QFixture src;
        src.Build(3, 100);
        SBcastQ* dst = (SBcastQ*)operator new(
            sizeof(SBcastQ));
        std::memset(dst, 0, sizeof(SBcastQ));
        BcastQCreate(dst, &src.q);
        // dest list: 3 nodes copied in order
        assert(dst->m_qSize == 3);
        void* d1 = *(void**)dst->m_pSent;
        void* d2 = *(void**)d1;
        void* d3 = *(void**)d2;
        assert(*(void**)d3 == dst->m_pSent);
        uint64_t* pn1 = (uint64_t*)d1;
        assert(pn1[2] == 100);   // data qword0
        assert(((uint64_t*)d2)[2] == 101);
        assert(((uint64_t*)d3)[2] == 102);
        assert(*(void**)((char*)d1 + 8) ==
               dst->m_pSent);      // prev of first
        assert(*(void**)((char*)d3 + 8) == d2);
        // dest vector: resized to 3, sync pairs
        // = {anchor value, D1/D2/D3}
        uint64_t anchorVal =
            *(uint64_t*)((char*)dst + 0x10);
        uint64_t* dv = (uint64_t*)dst->m_vFirst;
        assert(((char*)dst->m_vLast -
                (char*)dst->m_vFirst) >> 4 == 3);
        assert(dv[0] == anchorVal &&
               dv[1] == (uint64_t)d1);
        assert(dv[2] == anchorVal &&
               dv[3] == (uint64_t)d2);
        assert(dv[4] == anchorVal &&
               dv[5] == (uint64_t)d3);
        assert(s_nInvalid == 0);
        // cleanup
        void* la = *(void**)((char*)dst + 0x10);
        void* va = *(void**)((char*)dst + 0x48);
        operator delete(la); operator delete(va);
        operator delete(dst->m_pSent);
        operator delete(d1); operator delete(d2);
        operator delete(d3);
        operator delete(dst->m_vFirst);
        operator delete(dst);
        src.Cleanup();
        printf("S3 ok (full update)\n"); fflush(stdout);
    }

    // ==== S4: repeated match (walkers do not
    // advance on a match - a NON-node second
    // would walk past the end and fire the CRT
    // guard, proven in S6) ====
    {
        QFixture src;
        src.Build(2, 50);
        // pair[1].second repeats N1
        src.pairs[3] = (uint64_t)src.nodes[0];
        SBcastQ* dst = (SBcastQ*)operator new(
            sizeof(SBcastQ));
        std::memset(dst, 0, sizeof(SBcastQ));
        BcastQCreate(dst, &src.q);
        uint64_t anchorVal =
            *(uint64_t*)((char*)dst + 0x10);
        uint64_t* dv = (uint64_t*)dst->m_vFirst;
        // BOTH slots matched at the SAME dest node
        // D1 (the match consumes an src pair but
        // never advances the walkers)
        void* d1 = *(void**)dst->m_pSent;
        assert(dv[0] == anchorVal &&
               dv[1] == (uint64_t)d1);
        assert(dv[2] == anchorVal &&
               dv[3] == (uint64_t)d1);
        assert(s_nInvalid == 0);
        void* la = *(void**)((char*)dst + 0x10);
        void* va2 = *(void**)((char*)dst + 0x48);
        operator delete(la);
        operator delete(va2);
        // delete 2 nodes BEFORE the sentinel
        void* n = *(void**)dst->m_pSent;
        for (int i = 0; i < 2; i++) {
            void* nx = *(void**)n;
            operator delete(n); n = nx;
        }
        operator delete(dst->m_pSent);
        operator delete(dst->m_vFirst);
        operator delete(dst);
        src.Cleanup();
        printf("S4 ok (unmatched fill)\n"); fflush(stdout);
    }

    // ==== S5: list<T> too long (a5f80) ====
    {
        QFixture src;
        src.Build(1, 10);
        // craft a list obj with size at max
        char listObj[0x38];
        std::memset(listObj, 0, sizeof listObj);
        *(uint64_t*)(listObj + 0x30) =
            0x555555555555555ULL;
        uint64_t aPos[2] = { 0,
            (uint64_t)src.q.m_pSent };
        uint64_t aBeg[2] = { (uint64_t)
            *(void**)((char*)&src.q + 0x10),
            *(uint64_t*)src.q.m_pSent };
        uint64_t aEnd[2] = { aBeg[0],
            (uint64_t)src.q.m_pSent };
        bool threw = false;
#ifdef HAVE_LSAN
        __lsan_disable();   // the RAW leaks the node
#endif
        try {
            BcastListAppend(listObj, aPos,
                            aBeg, aEnd);
        } catch (const std::length_error& e) {
            threw = true;
            assert(std::string(e.what()) ==
                   "list<T> too long");
        }
#ifdef HAVE_LSAN
        __lsan_enable();    // ...allocation order:
        // 9ad30 node precedes the count check in
        // the ORIGINAL - exception path = leak
#endif
        assert(threw);
        // the thrown (unlinked) node: the raw
        // leaks it into the sentinel - replicate the
        // relink the original state left, then free
        // the TEST copies
        *(void**)((char*)src.q.m_pSent + 8) =
            src.q.m_pSent;
        *(void**)src.q.m_pSent = src.q.m_pSent;
        src.Cleanup();
        printf("S5 ok (too long)\n"); fflush(stdout);
    }

    // ==== S6: the walker end-guard fires the seam ====
    {
        QFixture src;
        src.Build(2, 60);
        // both pairs point at a non-node ->
        // src walker walks to the sentinel
        src.pairs[1] = 0x9999;
        src.pairs[3] = 0x9999;
        SBcastQ* dst = (SBcastQ*)operator new(
            sizeof(SBcastQ));
        std::memset(dst, 0, sizeof(SBcastQ));
        BcastQCreate(dst, &src.q);
        // the guard fired exactly once (the src
        // walker == sentinel) and the port returned
        assert(s_nInvalid == 1);
        void* la = *(void**)((char*)dst + 0x10);
        void* va2 = *(void**)((char*)dst + 0x48);
        operator delete(la);
        operator delete(va2);
        void* n = *(void**)dst->m_pSent;
        for (int i = 0; i < 2; i++) {
            void* nx = *(void**)n;
            operator delete(n); n = nx;
        }
        operator delete(dst->m_pSent);
        operator delete(dst->m_vFirst);
        operator delete(dst);
        src.Cleanup();
        printf("S6 ok (end guard)\n"); fflush(stdout);
    }

    // ==== S7: the compat-mismatch guard (a5f80) ====
    {
        QFixture src;
        src.Build(1, 70);
        uint64_t aPos[2] = { 0,
            (uint64_t)src.q.m_pSent };
        uint64_t aBeg[2] = { 0x1000,
            *(uint64_t*)src.q.m_pSent };
        uint64_t aEnd[2] = { 0x2000,
            (uint64_t)src.q.m_pSent };
        BcastListAppend((char*)&src.q + 0x10,
                        aPos, aBeg, aEnd);
        assert(s_nInvalid == 2);
        src.Cleanup();
        printf("S7 ok (compat guard)\n"); fflush(stdout);
    }

    // ==== S8: update REPEAT (idempotent rebuild) ====
    {
        QFixture src;
        src.Build(2, 200);
        SBcastQ* dst = (SBcastQ*)operator new(
            sizeof(SBcastQ));
        std::memset(dst, 0, sizeof(SBcastQ));
        BcastQCreate(dst, &src.q);
        // a second update: dest list cleared and
        // rebuilt (no leaks of the old nodes)
        BcastQueueUpdate(dst, &src.q);
        assert(dst->m_qSize == 2);
        void* d1 = *(void**)dst->m_pSent;
        assert(((uint64_t*)d1)[2] == 200);
        uint64_t anchorVal =
            *(uint64_t*)((char*)dst + 0x10);
        uint64_t* dv = (uint64_t*)dst->m_vFirst;
        assert(dv[1] == (uint64_t)d1);
        assert(dv[0] == anchorVal);
        void* la = *(void**)((char*)dst + 0x10);
        void* va2 = *(void**)((char*)dst + 0x48);
        operator delete(la);
        operator delete(va2);
        void* n = *(void**)dst->m_pSent;
        for (int i = 0; i < 2; i++) {
            void* nx = *(void**)n;
            operator delete(n); n = nx;
        }
        operator delete(dst->m_pSent);
        operator delete(dst->m_vFirst);
        operator delete(dst);
        src.Cleanup();
        printf("S8 ok (repeat update)\n"); fflush(stdout);
    }

    printf("M67b ALL-OK\n");
    return 0;
}
