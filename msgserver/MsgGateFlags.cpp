#include "MsgGateFlags.h"
#include <cstdio>
#include <cstring>

namespace msg {

uint32_t g_uGateFlags = 0;   // DAT_140976718
uint32_t g_uGateLastTick = 0;  // DAT_140976724
unsigned char g_shellData[0xc4];  // DAT_1409765d0

// ===== FUN_140508ca0
void MsgGateSet4(void) {
    g_uGateFlags = g_uGateFlags | 4;
}

// ===== FUN_140508cd0
int MsgGateSet4Ret(void) {
    g_uGateFlags = g_uGateFlags | 4;
    return 1;
}

// ===== FUN_140508d00
int MsgGateCheckDate(MsgGateFlagsData& rD) {
    uint32_t uTick = rD.m_fnTick();
    if (599999 < uTick - g_uGateLastTick) {
        g_uGateLastTick = rD.m_fnTick();
        int tm[9];
        std::memcpy(tm, rD.m_tmStamp,
            9 * sizeof(int));
        int64_t tNow = rD.m_fnTime64();
        int64_t tRec = rD.m_fnMktime(tm);
        int64_t diff = tNow - tRec;
        if (diff < 0 ||
            0x794a00 < diff)
            return 0;
        g_uGateFlags = g_uGateFlags | 0x10;
    }
    return 1;
}

// ===== FUN_140508eb0 (from the asm)
uint32_t MsgGateMaster(MsgGateFlagsData& rD) {
    uint32_t uNow = rD.m_fnTimeGet(1);
    uint32_t uElapsed = uNow -
        rD.uStampTime;
    int nRand = rD.m_fnRandGet(0x3c);
    uint32_t uThresh =
        (uint32_t)nRand + 0xedaU;
    if (uElapsed <= uThresh)
        return uThresh & 0xffffff00U;
    uint32_t uFlag = g_uGateFlags;
    bool bPass = ((uFlag & 8) != 0) ||
        ((uFlag & 2) == 0) ||
        ((uFlag & 4) == 0) ||
        ((uFlag & 0x10) == 0);
    if (bPass)
        return (uFlag & 0xffffff00U)
            | 1U;
    return uFlag & 0xffffff00U;
}

// ===== FUN_140508b80
void MsgReportFingerprint(char* pOut,
                          MsgGateFlagsData& rD) {
    unsigned char mac[6];
    rD.m_fnGetMac(mac);
    char sz[32];    // local_98 area
    sz[0] = 0;
    std::memset(sz + 1, 0, 0x1f);
    std::sprintf(sz,
        "%02x%02x%02x-%02x%02x-%02x",
        mac[0], mac[1], mac[2],
        mac[3], mac[4], mac[5]);
    void* pCh = rD.m_fnGetChannel(1);
    if (pCh != nullptr) {
        // the inline strlen
        int n = 0;
        while (sz[n] != '\0' && n < 31)
            ++n;
        rD.m_fnChSend(pCh, sz, n);
        ++rD.nSends;
        rD.m_fnChRelease(pCh);
    }
    // *param_1 = the 25-byte out
    std::memcpy(pOut, sz, 25);
}

// ===== FUN_140508dc0
unsigned char* MsgLoadShellDat(
    MsgGateFlagsData& rD) {
    void* pFile = rD.m_fnFopen();
    if (pFile == nullptr)
        return nullptr;
    unsigned char buf[0x400];
    size_t n = rD.m_fnFread(buf, pFile);
    if (n == 0)
        return nullptr;
    rD.m_fnFclose(pFile);
    void* pCh = rD.m_fnGetChannel(0);
    if (pCh != nullptr) {
        rD.m_fnChSend(pCh, buf,
            (int)(n & 0xffffffff));
        rD.m_fnChRelease(pCh);
    }
    std::memcpy(g_shellData, buf, 0xc4);
    return g_shellData;
}

} // namespace msg
