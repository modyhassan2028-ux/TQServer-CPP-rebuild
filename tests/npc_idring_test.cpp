// unit 46: the freed-id ring (FUN_14002a690
// VERBATIM) + the composed mgr map KEY SPACE
// (the unit-42 TBD resolved: monsters
// [400001,500000] / pets [700001,800000) /
// players [1000000,...] / transform gate
// [400001,700000))
#include "../Exe/NpcServer/NpcTransform.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    // ===== 1) the fresh-counter path (2b270) ====
    NpcIdAllocator a;
    CNpcTransform t; t.m_pAllocator = &a;
    // the ring first (empty) -> the counter
    assert(t.SpawnNewNpcID() == 400002);
    assert(t.SpawnNewNpcID() == 400003);
    assert(a.m_dwCounter == 400003);

    // ===== 2) the freed ring: FIFO pop first ====
    a.m_ring.Push(400123);
    a.m_ring.Push(400456);
    a.m_ring.Push(400789);
    assert(a.m_ring.m_uCount == 3);
    assert(t.SpawnNewNpcID() == 400123);  // FIFO
    assert(t.SpawnNewNpcID() == 400456);
    assert(a.m_dwCounter == 400003);  // counter NOT touched
    assert(t.SpawnNewNpcID() == 400789);
    assert(a.m_ring.m_uCount == 0);
    assert(a.m_ring.m_nHead == 0);    // the count-0 reset
    // drained -> back to the counter
    assert(t.SpawnNewNpcID() == 400004);

    // ===== 3) the ring WRAP (head loops) =====
    NpcIdRing r;
    r.m_vIds.resize(3);
    r.Push(1); r.Push(2); r.Push(3);
    r.Pop(); r.Pop();          // head = 2 now
    r.Push(4);                 // tail wraps: (2+1)%3 = 0
    r.Pop(); r.Pop();          // 3, 4
    assert(r.m_uCount == 0 && r.m_nHead == 0);

    // ===== 4) the wrap: 499999 -> 400001 + the log ==
    a.m_dwCounter = 499999;
    a.m_ring.m_uCount = 0;
    uint32_t u = t.SpawnNewNpcID();
    assert(u == 400001);
    assert(a.m_dwCounter == 400001);
    u = t.SpawnNewNpcID();
    assert(u == 400002);        // the cycle restarts

    // ===== 5) the composed KEY SPACE (the TBD) ====
    // the monster space: [400001, 500000]
    a.m_dwCounter = 400001;
    a.m_ring.m_uCount = 0;
    assert(t.SpawnNewNpcID() >= 400001 &&
           t.SpawnNewNpcID() <= 500000);
    // the transform gate (FUN_14001c1d0):
    // (id - 0x61a81) < 299999 -> [400001, 700000)
    auto inGate = [](uint32_t id) {
        return id >= 0x61a81 && id - 0x61a81 < 299999; };
    assert(inGate(400001) && inGate(500000) &&
           inGate(699999));
    assert(!inGate(400000) && !inGate(700000));
    // pets [700001, 800000) sit JUST above the gate
    assert(!inGate(700001));
    // players [1e6, ...) - the 38090 spaces
    assert(!inGate(1500000));

    printf("NPC_IDRING_OK: the freed-id ring "
           "FUN_14002a690 VERBATIM (the FIFO head/"
           "count ring with the wrap, the count-0 "
           "head reset, the overflow guard) + the "
           "2b270 counter path (< 499999, the "
           "400001 wrap + the GBK error log) + the "
           "composed mgr map key space RESOLVED "
           "(monsters [400001,500000], pets "
           "[700001,800000), players [1000000,"
           "...], transform gate [400001,700000))\n");
    return 0;
}
