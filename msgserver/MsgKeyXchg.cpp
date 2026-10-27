#include "MsgKeyXchg.h"
#include "MsgCastToken.h"
#include "MsgMd5Service.h"
#include "MsgDhInit.h"
#include <cstring>

namespace msg {

bool g_bXchgDhInit = false;   // DAT_140976588
void* g_pXchgDh = nullptr;    // DAT_140976590

// the connection object's CAST ctx slot
static inline void* ConnCast(void* pConn) {
    return (char*)pConn + 0x18;
}

int MsgKeyXchgRecv(void* pConn,
                   const void* pWire,
                   int nWireLen,
                   MsgKeyXchgData& rD) {
    // ===== 1. the guards =====
    if (!g_bXchgDhInit || g_pXchgDh ==
        nullptr || pWire == nullptr ||
        nWireLen < 0)
        return -1;
    if (nWireLen < 0xc)
        return 0;
    // ===== 2. the hardcoded key =====
    char ctx[144];               // local_8d8
    rD.m_fnCastSetKey(ctx, 0x10,
        "C238xs65pjy7HU9Q");
    ++rD.nCastSetKey;
    // ===== 3. IV + num =====
    uint64_t uIv = 0;            // rsp+0x120
    int nNum = 0;                // rsp+0x70
    // ===== 4. the first 0xb bytes =====
    // out buffer: [7 pad][int32 len]
    // [payload follows at +0xb]
    unsigned char work[0x410];
    rD.m_fnCastCfb64(pWire, work, 0xb,
                     ctx, &uIv, &nNum);
    // ===== 5. the length gate =====
    int nLen = *(int*)(work + 7);
    if (!(nLen < 0x401 && 0xb < nLen))
        return 0;
    int iVar8 = nLen + 7;
    if (nWireLen < iVar8)
        return 0;
    // ===== 6. the payload =====
    rD.m_fnCastCfb64((const char*)pWire
        + 0xb, work + 0xb, nLen, ctx,
        &uIv, &nNum);
    // ===== 7. the TQClient magic =====
    const unsigned char* p =
        work + 0xb;              // payload
    uint64_t uMagic =
        *(const uint64_t*)(p + nLen
            - 0xc);
    if (uMagic != 0x746E65696C435154ULL)
        // "TQClient" LE
        return -1;
    // ===== 8. BN_new =====
    void* pBn = rD.m_fnBnNew();
    if (pBn == nullptr)
        return -1;
    void* pBnGuard = rD.m_fnGuardMakeDh();
    // ===== 9. the TLV walk (one pass)
    int nCursor = 4;
    {
        int nL1 = *(const int*)(p +
            nCursor - 4);
        if (nL1 < 1) {
            if (pBnGuard)
                rD.m_fnGuardRelease(
                    pBnGuard);
            return -1;
        }
        nCursor = nCursor + 4 + nL1;
        if (nLen < nCursor) {
            if (pBnGuard)
                rD.m_fnGuardRelease(
                    pBnGuard);
            return -1;
        }
    }
    // ===== 10. the second block =====
    int nL2 = *(const int*)(p + nCursor
        - 4);
    if (!(0 < nL2 &&
          nCursor + 4 + nL2 <= nLen)) {
        if (pBnGuard)
            rD.m_fnGuardRelease(
                pBnGuard);
        return -1;   // LAB_14050617d
    }
    // ===== 11. the pub-key hex =====
    const unsigned char* pSrc = p +
        nCursor;
    char* pHex = new char[nL2 + 1];
    void* pHexGuard =
        rD.m_fnGuardMakeStr();
    if (pHex == nullptr) {
        // BN_free + the guards -> -1
        rD.m_fnBnFree(pBn);
        if (pHexGuard)
            rD.m_fnGuardRelease(
                pHexGuard);
        if (pBnGuard)
            rD.m_fnGuardRelease(
                pBnGuard);
        return -1;
    }
    std::memset(pHex, 0, nL2 + 1);
    std::memcpy(pHex, pSrc, nL2);
    void* apBn[1] = {pBn};
    int nRc = rD.m_fnBnHex2bn(apBn,
                              pHex);
    if (nRc == 0) {
        delete[] pHex;
        if (pHexGuard)
            rD.m_fnGuardRelease(
                pHexGuard);
        if (pBnGuard)
            rD.m_fnGuardRelease(
                pBnGuard);
        return -1;
    }
    // ===== 12. the shared secret =====
    int nDhSize = rD.m_fnDhSize();
    unsigned char* pSecret =
        new unsigned char[nDhSize + 1];
    void* pSecGuard =
        rD.m_fnGuardMakeStr();
    if (pSecret == nullptr) {
        delete[] pHex;
        if (pSecGuard)
            rD.m_fnGuardRelease(
                pSecGuard);
        if (pHexGuard)
            rD.m_fnGuardRelease(
                pHexGuard);
        if (pBnGuard)
            rD.m_fnGuardRelease(
                pBnGuard);
        return -1;
    }
    std::memset(pSecret, 0,
                nDhSize + 1);
    nRc = rD.m_fnDhComputeKey(pSecret,
                              pBn,
                              g_pXchgDh);
    if (nRc == -1) {
        delete[] pHex;
        delete[] pSecret;
        if (pSecGuard)
            rD.m_fnGuardRelease(
                pSecGuard);
        if (pHexGuard)
            rD.m_fnGuardRelease(
                pHexGuard);
        if (pBnGuard)
            rD.m_fnGuardRelease(
                pBnGuard);
        return -1;
    }
    // ===== 13. the CAST session key
    char token[0x400];
    std::memset(token, 0, 0x400);
    MsgCastTokenData dTok;
    dTok.m_fnMd5OfString =
        MsgMd5OfString;
    int nTok = MsgBuildCastToken(dTok,
        token, (const char*)pSecret);
    if (nTok == 0x40) {
        rD.m_fnCastSetKey(
            ConnCast(pConn), 0x40,
            token);
        rD.sSetKeyMaterial.assign(
            token, 0x40);
    } else {
        rD.m_fnCastSetKey(
            ConnCast(pConn), nDhSize,
            pSecret);
        rD.sSetKeyMaterial.assign(
            (const char*)pSecret,
            nDhSize);
    }
    // ===== 14. done =====
    delete[] pHex;
    delete[] pSecret;
    if (pSecGuard)
        rD.m_fnGuardRelease(
            pSecGuard);
    if (pHexGuard)
        rD.m_fnGuardRelease(
            pHexGuard);
    if (pBnGuard)
        rD.m_fnGuardRelease(
            pBnGuard);
    return iVar8;
}

} // namespace msg
