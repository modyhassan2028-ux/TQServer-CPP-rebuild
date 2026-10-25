// M71: the hash insert family (FUN_14000f880 +
// FUN_14000fd50 + FUN_140010970) VERBATIM
#include "../Exe/MsgServer/Port/MsgHashInsert.h"
#include "../Exe/MsgServer/Port/MsgHashCtor.h"
#include "../Exe/MsgServer/Port/MsgHashProbe.h"
#include <cassert>
#include <cstdio>
#include <cstring>

static int32_t NodeKey(void* p) {
    return *(int32_t*)((char*)p + 0x10);
}

int main() {
    using namespace msg;
    // 1) INSERT into the fresh container (hint=END)
    SHashContainer c; std::memset(&c, 0, sizeof c);
    uint16_t w = 1; HashCtorInit(&c, &w);
    void* pEnd = c.m_pEnd;
    int32_t k1 = 5679;
    uint64_t hint[2] = {*(uint64_t*)((char*)&c+0x10),
                        (uint64_t)pEnd};
    uint64_t out[6];
    HashInsert(&c, out, &k1, hint);
    assert(*(uint8_t*)((char*)out + 0x10) == 1);
    assert(c.m_qSize == 1);
    void* n1 = (void*)out[1];
    assert(n1 != pEnd && NodeKey(n1) == k1);
    // the boundary: the new node is head of its bucket
    uint64_t probe[2];
    HashProbeFind((uint8_t*)&c, (void**)probe, &k1);
    assert((void*)probe[1] == n1);
    // the inserted node is the list front: END->next
    assert(*(void**)pEnd == n1);

    // 2) DUP: same key again (fresh END hint)
    hint[0] = *(uint64_t*)((char*)&c+0x10);
    hint[1] = (uint64_t)pEnd;
    HashInsert(&c, out, &k1, hint);
    assert(*(uint8_t*)((char*)out + 0x10) == 0);
    assert(c.m_qSize == 1);
    assert((void*)out[1] == n1);   // the existing

    // 3) a SECOND key (different bucket) then a THIRD
    //    colliding probe walk
    int32_t k2 = 4242;
    hint[0] = *(uint64_t*)((char*)&c+0x10);
    hint[1] = (uint64_t)pEnd;
    HashInsert(&c, out, &k2, hint);
    assert(*(uint8_t*)((char*)out + 0x10) == 1);
    assert(c.m_qSize == 2);
    void* n2 = (void*)out[1];
    HashProbeFind((uint8_t*)&c, (void**)probe, &k2);
    assert((void*)probe[1] == n2);
    HashProbeFind((uint8_t*)&c, (void**)probe, &k1);
    assert((void*)probe[1] == n1);   // k1 still found
    int32_t k3 = 1234;
    hint[0] = *(uint64_t*)((char*)&c+0x10);
    hint[1] = (uint64_t)pEnd;
    HashInsert(&c, out, &k3, hint);
    assert(c.m_qSize == 3);
    void* n3 = (void*)out[1];
    HashProbeFind((uint8_t*)&c, (void**)probe, &k3);
    assert((void*)probe[1] == n3);
    HashProbeFind((uint8_t*)&c, (void**)probe, &k1);
    assert((void*)probe[1] == n1);
    HashProbeFind((uint8_t*)&c, (void**)probe, &k2);
    assert((void*)probe[1] == n2);

    // 4) the REHASH trigger: max_load tiny -> 3
    //    elements / 8 buckets = 0.375 > 0.05 fires
    c.m_fMaxLoad = 0.4f;   // 4/8=0.5 fires once; 4/64=0.0625 no cascade
    int32_t k4 = 9999;
    hint[0] = *(uint64_t*)((char*)&c+0x10);
    hint[1] = (uint64_t)pEnd;
    HashInsert(&c, out, &k4, hint);
    assert(c.m_qSize == 4);
    assert(c.m_qBuckets == 64);   // x8 VERBATIM
    assert(c.m_qMask == 63);
    // 65 entries all = {proxy, END} before fd50;
    // after the rebuild every key still found
    int32_t keys[4] = {k1, k2, k3, k4};
    void* nodes[4] = {n1, n2, n3, nullptr};
    void* n4 = (void*)out[1];
    nodes[3] = n4;
    for (int i = 0; i < 4; i++) {
        HashProbeFind((uint8_t*)&c, (void**)probe,
                      &keys[i]);
        assert((void*)probe[1] == nodes[i]);
    }

    // 5) op[]: existing key -> value ptr; a new
    //    key inserts then the value is writable
    int32_t* pv1 = (int32_t*)HashValueAt(&c, &k2);
    assert((void*)pv1 == (char*)n2 + 0x14);
    *pv1 = 555;
    assert(*(int32_t*)((char*)n2 + 0x14) == 555);
    int32_t k5 = 31337;
    int32_t* pv5 = (int32_t*)HashValueAt(&c, &k5);
    assert(c.m_qSize == 5);
    HashProbeFind((uint8_t*)&c, (void**)probe, &k5);
    assert((char*)probe[1] + 0x14 == (char*)pv5);
    *pv5 = 777;
    assert(*(int32_t*)((char*)probe[1] + 0x14)
           == 777);

    std::puts("M71-HASH-INSERT-OK");
    return 0;
}
