#ifndef MSG_HASH_CTOR_H
#define MSG_HASH_CTOR_H
#include <cstdint>
#include "MsgVectorFamily.h"

namespace msg {

// ===== M71b: the ACTIVITY hash container - layout
// VERBATIM (ctor FUN_1400103b0 / reset FUN_140010310):
//   +0x08  2-byte owner field (ctor param_2)
//   +0x10  the LIST PROXY node slot: a new(8) node
//          whose value points BACK at this slot
//   +0x38  the END sentinel (FUN_140009f20 = M71a)
//   +0x40  the element count
//   +0x48  the buckets SVec (proxy@+0, FIRST@+0x60,
//          LAST@+0x68, CAP@+0x70)
//   +0x78  the mask = 7
//   +0x80  the bucket count = 8 (9 entries = 8 + 1)
//   +0x88  max_load_factor = 4.0f (0x40800000)
struct SHashContainer {
    uint64_t m_q0;
    uint16_t m_wOwner;      // +0x08
    uint8_t  m_abA[6];
    void*    m_pProxy;      // +0x10
    uint8_t  m_ab18[0x20];
    void*    m_pEnd;        // +0x38
    uint64_t m_qSize;       // +0x40
    SVec     m_vec;         // +0x48
    uint64_t m_qMask;       // +0x78
    uint64_t m_qBuckets;    // +0x80
    float    m_fMaxLoad;    // +0x88
    uint32_t m_pad;
};

// ORIGINAL FUN_1400103b0: the container ctor
void HashCtorInit(SHashContainer* pC,
                  const uint16_t* pOwner);

// ORIGINAL FUN_140010310: the RESET (destroy every
// node, empty the list, rebuild 9 bucket entries)
void HashReset(SHashContainer* pC);

} // namespace msg
#endif
