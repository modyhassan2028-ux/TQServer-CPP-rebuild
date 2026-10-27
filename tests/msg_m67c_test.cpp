// M67c unit test — the broadcast queue's ordered-
// hash lookup: FUN_1400a3410 (BcastQueueFind) +
// FUN_1400b29c0 (BcastQueueLookupData)
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgBcastQueue.h"
#include "MsgBcastVector.h"
using namespace msg;

static int s_nInvalid = 0;
static void TInvalid() { ++s_nInvalid; }

// the raw Park-Miller bucket hash (recomputed in the
// test to build the index — the SAME formula)
static uint32_t TBucket(uint32_t k, uint64_t mask) {
    uint32_t v = (k ^ 0xdeadbeefU) & 0x7fffffffU;
    uint32_t q = v / 0x1f31dU;
    int32_t n = (int32_t)(v % 0x1f31dU) * 0x41a7
              - (int32_t)q * 0xb14;
    if (n < 0) n += 0x7fffffff;
    return (uint32_t)((uint64_t)n & mask);
}

struct MapFixture {
    // a CMapGroup-style parent: queue at +0x4b8
    uint8_t group[0x540];
    SBcastQ* Q() { return (SBcastQ*)(group + 0x4b8); }
    void* nodes[4];
    uint64_t* vec;         // bucket vector buffer
    void*  pAnchCell;
    MapFixture() : vec(nullptr), pAnchCell(nullptr) {
        std::memset(group, 0, sizeof group);
    }
    // keys sorted ascending; mask fixed 3
    void Build(const uint32_t* keys, size_t k) {
        SBcastQ* q = Q();
        // the list: anchor cell {->q+0x10}, sentinel,
        // k nodes with data[0]=key
        pAnchCell = operator new(8);
        *(void***)pAnchCell =
            (void**)((char*)q + 0x10);
        q->m_pAnchor = pAnchCell;
        q->m_pSent = BcastSentNew();
        q->m_qSize = k;
        for (size_t i = 0; i < k; i++) {
            uint64_t data[6];
            std::memset(data, 0, sizeof data);
            data[0] = keys[i];      // the key
            data[1] = 0x100 + i;    // payload tag
            void* s = q->m_pSent;
            void* n = BcastListNodeNew(
                s, *(void**)((char*)s + 8), data);
            *(void**)((char*)s + 8) = n;
            *(void**)(*(void**)((char*)n + 8)) = n;
            nodes[i] = n;
        }
        // the bucket index: 5 slots (mask 3 + extra)
        const uint64_t mask = 3;
        q->m_q78 = mask;       // +0x78 mask
        q->m_q80 = mask + 1;   // +0x80 threshold: fold off
        vec = (uint64_t*)operator new(5 * 0x10);
        // extra slot -> sentinel (list end)
        for (size_t b = 0; b <= mask; b++) {
            void* hit = nullptr;
            for (size_t i = 0; i < k; i++) {
                if (TBucket(keys[i], mask) == b) {
                    hit = nodes[i]; break;
                }
            }
            vec[b*2] = 0;
            vec[b*2+1] = (uint64_t)hit;
        }
        // empty buckets inherit the NEXT non-empty
        // pointer (consecutive-equal = empty marker);
        // all-empty tail -> sentinel
        void* next = q->m_pSent;
        for (int b = 3; b >= 0; b--) {
            if (vec[b*2+1] == 0)
                vec[b*2+1] = (uint64_t)next;
            else
                next = (void*)vec[b*2+1];
        }
        vec[8] = 0;                    // slot 4 extra
        vec[9] = (uint64_t)q->m_pSent;  // -> sentinel
        q->m_vFirst = vec;
        q->m_vLast = (char*)vec + 5 * 0x10;
        q->m_vCap = (char*)vec + 5 * 0x10;
    }
    void Cleanup(size_t k) {
        SBcastQ* q = Q();
        for (size_t i = 0; i < k; i++)
            operator delete(nodes[i]);
        operator delete((void*)q->m_pSent);
        operator delete(pAnchCell);
        operator delete(vec);
    }
};

int main() {
    g_fnBcastInvalidParam = TInvalid;
    printf("M67c start\n"); fflush(stdout);

    uint32_t keys[3] = { 100, 200, 300 };
    const uint64_t mask = 3;
    printf("buckets: k100=%d k200=%d k300=%d\n",
        TBucket(100,mask), TBucket(200,mask),
        TBucket(300,mask)); fflush(stdout);

    // ==== S1: Find each existing key ====
    {
        MapFixture f;
        f.Build(keys, 3);
        uint64_t out[2] = {0,0};
        for (size_t i = 0; i < 3; i++) {
            BcastQueueFind(f.Q(), keys[i], out);
            assert(out[0] == (uint64_t)f.pAnchCell);
            assert(out[1] == (uint64_t)f.nodes[i]);
            assert(*(uint32_t*)out[1] ==
                   *(uint32_t*)((char*)f.nodes[i]));
        }
        assert(s_nInvalid == 0);
        printf("S1 ok (find existing)\n"); fflush(stdout);
        // keep fixture for S2/S3 — cleaned at S4
        // S2: a missing key BETWEEN keys (no crash)
        uint64_t out2[2] = {0,0};
        BcastQueueFind(f.Q(), 250, out2);
        // lower_bound overshoots to node 300 ->
        // END pair {anchor, sentinel}
        assert(out2[0] == (uint64_t)f.pAnchCell);
        assert(out2[1] == (uint64_t)f.Q()->m_pSent);
        assert(s_nInvalid == 0);
        printf("S2 ok (missing key -> END)\n"); fflush(stdout);
        // S3: LookupData via the parent object
        void* p = BcastQueueLookupData(f.group, 200);
        assert(p == (void*)((char*)f.nodes[1] + 0x18));
        assert(*(uint64_t*)p == 0x101);
        assert(BcastQueueLookupData(f.group, 250)
               == nullptr);
        assert(s_nInvalid == 0);
        printf("S3 ok (lookup data)\n"); fflush(stdout);
        f.Cleanup(3);
    }

    // ==== S4: an EMPTY bucket (its hash unused) ====
    {
        MapFixture f;
        uint32_t k2[2] = { 100, 300 };
        f.Build(k2, 2);
        // find a key hashing to an empty bucket:
        // 200 is absent; its bucket b200 is empty
        // (or shared) -> the END pair (no walk)
        uint64_t out[2] = {0,0};
        BcastQueueFind(f.Q(), 200, out);
        assert(out[0] == (uint64_t)f.pAnchCell);
        assert(out[1] ==
               (uint64_t)f.Q()->m_pSent);
        assert(BcastQueueLookupData(f.group, 200)
               == nullptr);
        assert(s_nInvalid == 0);
        // existing keys still resolve
        void* p = BcastQueueLookupData(f.group, 300);
        assert(p == (void*)((char*)f.nodes[1] + 0x18));
        f.Cleanup(2);
        printf("S4 ok (empty bucket)\n"); fflush(stdout);
    }

    printf("M67c ALL-OK\n");
    return 0;
}
