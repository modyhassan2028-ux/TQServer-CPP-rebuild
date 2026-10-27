#include "MsgRecvHandler.h"
#include "MsgKeyXchg.h"
#include "MsgSessionCipher.h"
#include <cstring>

namespace msg {

int MsgRecvHandler(void* pConn,
                   MsgRecvHandlerData& rD) {
    // ===== 1. the early gate =====
    int nLen =
        *(int*)((char*)pConn + 8);
    if (nLen < 0xc)
        return 1;
    // ===== 2. the key exchange =====
    rD.bKeyXchgRan = true;
    int iVar2 = rD.m_fnKeyXchg(
        (char*)pConn + 0x824,
        (char*)pConn + 0x1b, nLen);
    if (iVar2 != 0) {
        if (iVar2 < 0)
            return 0;      // drop
        // ===== 4. consume =====
        rD.m_fnConsume(pConn, iVar2);
        ++rD.nConsume;
        rD.nConsumeArg = iVar2;
        // ===== 5. keyed =====
        *(uint8_t*)((char*)pConn + 0x1a)
            = 1;
        // ===== 6. decrypt the rest =====
        nLen = *(int*)((char*)pConn + 8);
        if (0 < nLen) {
            unsigned char scratch[2048];
            int rc = rD.m_fnDecrypt(
                (char*)pConn + 0x824,
                (char*)pConn + 0x1b,
                scratch, nLen);
            ++rD.nDecrypt;
            rD.nDecLen = nLen;
            if (rc == 0)
                return 0;
            std::memcpy((char*)pConn + 0x1b,
                scratch, nLen);
        }
    }
    return 1;
}

} // namespace msg
