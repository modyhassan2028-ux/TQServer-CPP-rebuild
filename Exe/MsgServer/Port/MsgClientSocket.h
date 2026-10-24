// ============================================================
// MsgServer strict port - unit M8
// ORIGINAL: the CAccountClient socket family
//  FUN_140503610 (CAccountClient ctor, the M6
//                 operator-new(0x1468) target)
//  FUN_140506e80 (CClientSocket base ctor)
//  FUN_140506480 (the CIPHER TABLE generator -
//                 two 0x100-byte LCG tables per
//                 call; object blocks at +0x1060
//                 and +0x1268, each 0x200 bytes)
// LAYOUT of the 0x1468 object (byte offsets):
//  +0x000 CClientSocket::vftable, then
//         CAccountClient::vftable
//  +0x008 byte 0
//  +0x018 dword 0
//  +0x020 qword -1
//  +0x028..+0x827 the 0x800 recv buffer (zeroed)
//  +0x82c..+0x102b the 0x800 send buffer (zeroed)
//  +0x102c dword 0
//  +0x1030 dword 0
//  +0x1034 byte 1
//  +0x1038 dword 0xffffffff
//  +0x1040 dword: 0 (qword), then 1 at the end
//  +0x1048 qword 0
//  +0x1054 dword 0, then TimeGet(0)/1000
//  +0x1058 dword 0; +0x105c dword 0
//  +0x1060..+0x125f CIPHER BLOCK 1 (0x200)
//  +0x1260 dword 0
//  +0x1268..+0x1467 CIPHER BLOCK 2 (0x200)
// NOTE the LITERAL double calls: FUN_140506480
//  runs TWICE on +0x1060 and TWICE on +0x1268
//  (documented, kept), and +0x1040/+0x1054 are
//  written 0 first then 1/timestamp (LITERAL).
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgClientSock {
    uint8_t ab[0x1468];
    template <typename T>
    T& At(uint32_t off) {
        return *(T*)((char*)ab + off); }
};

// ===== ORIGINAL FUN_140506480 @ 140506480 =====
// the two 0x100-byte LCG cipher tables:
//  table A starts '~' : c = (c*0x12 - 0x69)*c + 0x19
//  table B starts 0xd3: c = (c*0x48 + 0x51)*c + 0x1b
// (SIGNED char arithmetic - LITERAL)
void MsgClientCipherInit(void* pBlock);

// ===== ORIGINAL FUN_140506e80 @ 140506e80 =====
void MsgClientSockCtorBase(MsgClientSock* p,
    std::function<uint32_t()> fnTimeGet);

// ===== ORIGINAL FUN_140503610 @ 140503610 =====
void MsgAccountClientCtor(MsgClientSock* p,
    std::function<uint32_t()> fnTimeGet);

} // namespace msg
