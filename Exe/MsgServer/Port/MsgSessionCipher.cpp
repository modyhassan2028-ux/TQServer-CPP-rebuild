#include "MsgSessionCipher.h"
#include "MsgKeyXchg.h"

namespace msg {

// ===== ORIGINAL FUN_140504b80 @ 140504b80
int MsgSessionEncrypt(MsgCryptoBlock& rB,
                      const void* pIn,
                      void* pOut, int nLen,
                      MsgSessionCipherData& rD) {
    if (g_bXchgDhInit && g_pXchgDh !=
        nullptr && pOut != nullptr &&
        pIn != nullptr && 0 < nLen) {
        rD.m_fnCfb64(pIn, pOut, nLen,
            rB.ctx + 0x00,   // block+0x18
            &rB.uIvEnc,      // block+0x10
            &rB.uNumEnc,     // block+0x4
            1);              // enc
        ++rD.nEncCalls;
        return 1;
    }
    return 0;
}

// ===== ORIGINAL FUN_140504bf0 @ 140504bf0
int MsgSessionDecrypt(MsgCryptoBlock& rB,
                      const void* pIn,
                      void* pOut, int nLen,
                      MsgSessionCipherData& rD) {
    if (g_bXchgDhInit && g_pXchgDh !=
        nullptr && pOut != nullptr &&
        pIn != nullptr && 0 < nLen) {
        rD.m_fnCfb64(pIn, pOut, nLen,
            rB.ctx + 0x00,   // block+0x18
            &rB.uIvDec,      // block+0x8
            &rB.uNumDec,     // block+0x0
            0);              // dec
        ++rD.nDecCalls;
        return 1;
    }
    return 0;
}

} // namespace msg
