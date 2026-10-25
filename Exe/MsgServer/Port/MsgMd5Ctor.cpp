#include "MsgMd5Ctor.h"

namespace msg {

// MD5::CMD5Checksum::vftable (an image
// address marker in the port)
const void* g_pMd5ChecksumVt =
    (const void*)0x1407B0000ULL;

// ===== ORIGINAL FUN_14050a570 @ 14050a570
void* MsgMd5ChecksumCtor(void* pObj) {
    uint64_t* p = (uint64_t*)pObj;
    p[0] = (uint64_t)(uintptr_t)
        g_pMd5ChecksumVt;   // +0x00
    for (int i = 1; i <= 8; ++i)
        p[i] = 0;   // +0x08..+0x47
    *(uint32_t*)((char*)pObj + 0x48) = 0;
    *(uint32_t*)((char*)pObj + 0x4c) = 0;
    *(uint32_t*)((char*)pObj + 0x50) =
        0x67452301;   // MD5 A
    *(uint32_t*)((char*)pObj + 0x54) =
        0xefcdab89;   // MD5 B
    *(uint32_t*)((char*)pObj + 0x58) =
        0x98badcfe;   // MD5 C
    *(uint32_t*)((char*)pObj + 0x5c) =
        0x10325476;   // MD5 D
    return pObj;
}

} // namespace msg
