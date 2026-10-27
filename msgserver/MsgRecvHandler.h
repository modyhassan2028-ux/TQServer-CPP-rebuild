// ============================================================
// MsgServer strict port - unit M20
// ORIGINAL: FUN_1405002a0 @ 1405002a0
// the connection's encrypted recv handler
// (a vt slot of the socket object)
// The object: +0x00 vt, +0x08 int
//  buffer len, +0x1b the recv buffer,
//  +0x1a the keyed flag, +0x824 the
//  crypto block (M19)
// The LITERAL flow (from the asm):
//  1. len = *(int*)(this+8); len < 0xc ->
//     return 1
//  2. iVar2 = FUN_140505bc0(this+0x824,
//     this+0x1b, len)   [M18]
//  3. iVar2 == 0 -> return 1 (more
//     data needed / bad shape)
//     iVar2 < 0 -> return 0 (drop)
//  4. vt+0x10(this, iVar2)   [consume]
//  5. this+0x1a = 1   [keyed]
//  6. re-read len = *(int*)(this+8)
//     (the consume shrank it);
//     len > 0: Decrypt(this+0x824,
//     this+0x1b, scratch[2048], len)
//     fail -> return 0; memcpy back
//  7. return 1
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgRecvHandlerData {
    // the vt+0x10 consume call
    std::function<void(void*, int)>
        m_fnConsume;
    // FUN_140505bc0 (M18) - seam for the
    // receive tests
    std::function<int(void*, void*, int)>
        m_fnKeyXchg;
    // FUN_140504bf0 (M19 decrypt)
    std::function<int(void*, void*, void*,
                      int)> m_fnDecrypt;
    // captures
    int nConsume = 0, nDecrypt = 0;
    int nConsumeArg = 0, nDecLen = 0;
    // injectors
    int nXchgRc = 0;
    int nDecRc = 1;
    bool bKeyXchgRan = false;
};

// the connection header (the fields the
// handler touches)
struct MsgConnHeader {
    void* vt;              // +0x00
    int nBufLen;           // +0x08
    uint8_t pad0[0x0e];    // +0x0c
    uint8_t byKeyed;       // +0x1a
    uint8_t buf[1];        // +0x1b
    // the crypto block at +0x824 is
    // addressed relative to the object
    // base (the caller owns the layout)
};

// ===== ORIGINAL FUN_1405002a0 @ 1405002a0
// pConn = the object base; pCrypto =
// conn+0x824 (the M19 block)
int MsgRecvHandler(void* pConn,
                   MsgRecvHandlerData& rD);

} // namespace msg
