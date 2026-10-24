#include "MsgClientSocket.h"
#include <cstring>

namespace msg {

// ===== ORIGINAL FUN_140506480 @ 140506480 =====
void MsgClientCipherInit(void* pBlock) {
    char* p = (char*)pBlock;
    // table A: 0x100 bytes from '~'
    char c = '~';
    for (int i = 0; i < 0x100; ++i) {
        p[i] = c;
        c = (char)((c * 0x12 + -0x69) * c + 0x19);
    }
    // table B: 0x100 bytes from 0xd3
    c = (char)-0x2d;
    for (int i = 0; i < 0x100; ++i) {
        p[0x100 + i] = c;
        c = (char)((c * 'H' + 'Q') * c + 0x1b);
    }
}

// ===== ORIGINAL FUN_140506e80 @ 140506e80 =====
// VERBATIM order (Ghidra qword steps folded to
// byte offsets, see the header map)
void MsgClientSockCtorBase(MsgClientSock* p,
                          std::function<uint32_t()> fnTimeGet) {
    p->At<void*>(0) = (void*)0x1;   // CClientSocket::vftable
    p->At<uint32_t>(0x1040) = 0;
    p->At<uint32_t>(0x1054) = 0;
    MsgClientCipherInit(p->ab + 0x1060);
    p->At<uint32_t>(0x105c) = 0;
    p->At<uint32_t>(0x1058) = 0;
    MsgClientCipherInit(p->ab + 0x1060);   // LITERAL 2nd
    MsgClientCipherInit(p->ab + 0x1268);
    p->At<uint32_t>(0x1264) = 0;
    p->At<uint32_t>(0x1260) = 0;
    MsgClientCipherInit(p->ab + 0x1268);   // LITERAL 2nd
    p->At<uint32_t>(0x18) = 0;
    p->At<int64_t>(0x20) = -1;
    p->At<uint32_t>(0x828) = 0;
    p->At<uint32_t>(0x102c) = 0;
    p->At<uint32_t>(0x1030) = 0;
    p->At<uint64_t>(0x1040) = 0;
    p->At<uint32_t>(0x1038) = 0xffffffff;
    p->At<uint8_t>(8) = 0;
    p->At<uint8_t>(0x1034) = 1;
    p->At<uint64_t>(0x1048) = 0;
    std::memset(p->ab + 0x28, 0, 0x800);    // recv
    std::memset(p->ab + 0x82c, 0, 0x800);   // send
    p->At<uint32_t>(0x1040) = 1;
    p->At<uint32_t>(0x1054) = fnTimeGet() / 1000;
}

// ===== ORIGINAL FUN_140503610 @ 140503610 =====
void MsgAccountClientCtor(MsgClientSock* p,
                          std::function<uint32_t()> fnTimeGet) {
    MsgClientSockCtorBase(p, fnTimeGet);
    p->At<void*>(0) = (void*)0x2;   // CAccountClient::vftable
}

} // namespace msg
