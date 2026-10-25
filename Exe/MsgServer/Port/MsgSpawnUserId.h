#ifndef MSG_SPAWN_USER_ID_H
#define MSG_SPAWN_USER_ID_H
#include <cstdint>

namespace msg {

// ===== M69: ORIGINAL FUN_1402aed50 =====
// CUserManager::SpawnNewOSUserID() - the FIRST
// external consumer of the ported set container:
// allocates a player ID for the OTHER server.
//
// Object layout (offsets VERBATIM):
//   +0x14  the ID counter (uint)
//   +0x98  the released-ID set (SObjSet, erased via
//          FUN_14000ab40 = our SetErase)
//   +0xc8  the SET'S m_pInner (set@+0x98 + 0x30): the
//          sentinel ptr - the ORIGINAL reads it as the
//          iterator slot; *slot == slot when the set is
//          EMPTY (the self-linked sentinel)
//   +0xd0  the SET'S m_qCount (set@+0x98 + 0x38):
//          nonzero = released IDs pending
uint32_t SpawnNewOSUserID(uint8_t* pObj);

} // namespace msg
#endif
