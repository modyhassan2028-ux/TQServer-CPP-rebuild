#include "MsgSendHandler.h"
#include <cstdio>
#include <cstring>

namespace msg {

// ===== ORIGINAL FUN_1405009f0 @ 1405009f0
uint8_t MsgSendKeyed(const void* pConn) {
    return *(const uint8_t*)(
        (const char*)pConn + 0x1a);
}

// ===== ORIGINAL FUN_140500670 @ 140500670
int MsgSendHandler(void* pConn,
                   const void* pData,
                   int nLen,
                   MsgSendHandlerData& rD) {
    // ===== 1. the guards =====
    if (!rD.m_fnVt20(pConn))
        return 0;
    if (nLen > 0x400)
        return 0;
    int nEvType =
        *(int*)((char*)pConn + 0x14);
    void* pSendSock =
        *(void**)((char*)pConn + 0x908);
    void* pWsaSock =
        *(void**)((char*)pConn + 0x900);
    if (nEvType == 0) {
        // ===== 2. the TQ encrypted mode
        if (*(uint8_t*)((char*)pConn +
            0x1a) != 0) {
            unsigned char buf[0x408];
            buf[0] = 0;
            std::memset(buf + 1, 0, 0x407);
            int ok = rD.m_fnEncrypt(
                (char*)pConn + 0x824,
                pData, buf, nLen);
            if (ok == 0) {
                // line 0x2a2
                rD.m_fnLog(0x2a2, 0, nLen,
                    nullptr);
                return 0;
            }
            ok = rD.m_fnEncrypt(
                (char*)pConn + 0x824,
                "TQServer", buf + nLen, 8);
            if (ok == 0) {
                // line 0x2ae
                rD.m_fnLog(0x2ae, 0, nLen,
                    nullptr);
                return 0;
            }
            int n = rD.m_fnSend(pSendSock,
                buf, nLen + 8);
            rD.sWire.assign(
                (const char*)buf, nLen + 8);
            rD.nSendLen = nLen + 8;
            if (-1 < n)
                return 1;
            int nErr = rD.m_fnWsaLastError(
                pWsaSock);
            if (nErr != 0x2733 &&
                nErr != 0x2746) {
                char ip[0x24];   // local_458
                std::memset(ip, 0, 0x24);
                uint32_t uIp =
                    rD.m_fnVt30(pConn);
                if (uIp != 0)
                    std::sprintf(ip,
                        "%d.%d.%d.%d",
                        (uIp >> 0x18) & 0xff,
                        (uIp >> 0x10) & 0xff,
                        (uIp >> 8) & 0xff,
                        uIp & 0xff);
                rD.m_fnTimeGet(0);
                // line 0x2c4
                rD.m_fnLog(0x2c4, nErr, nLen,
                    uIp != 0 ? ip : "");
            }
            // LAB_1405009bb
            rD.m_fnVt28(pConn);
            return 0;
        }
        // not keyed: plaintext
        int n = rD.m_fnSend(pSendSock,
            pData, nLen);
        rD.sWire.assign(
            (const char*)pData, nLen);
        rD.nSendLen = nLen;
        if (n < 0) {
            int nErr = rD.m_fnWsaLastError(
                pWsaSock);
            char ip[0x24];
            std::memset(ip, 0, 0x24);
            uint32_t uIp =
                rD.m_fnVt30(pConn);
            if (uIp != 0)
                std::sprintf(ip,
                    "%d.%d.%d.%d",
                    (uIp >> 0x18) & 0xff,
                    (uIp >> 0x10) & 0xff,
                    (uIp >> 8) & 0xff,
                    uIp & 0xff);
            if (nErr != 0x2733 &&
                nErr != 0x2746) {
                rD.m_fnTimeGet(0);
                // line 0x2f3
                rD.m_fnLog(0x2f3, nErr, nLen,
                    uIp != 0 ? ip : "");
            }
            rD.m_fnVt28(pConn);
            return 0;
        }
        return 1;
    }
    // ===== 3. the relay modes (1/2)
    if ((uint32_t)(nEvType - 1) > 1) {
        rD.m_fnTimeGet(0);
        // DAT_140796498
        rD.m_fnLog(0x498, 0, nLen, nullptr);
        rD.m_fnVt28(pConn);
        return 0;
    }
    int n = rD.m_fnSend(pSendSock, pData,
        nLen);
    rD.sWire.assign(
        (const char*)pData, nLen);
    rD.nSendLen = nLen;
    if (n < 0) {
        int nErr = rD.m_fnWsaLastError(
            pWsaSock);
        if (nErr != 0x2733 &&
            nErr != 0x2746) {
            rD.m_fnTimeGet(0);
            // line 0x314 (NO ip)
            rD.m_fnLog(0x314, nErr, nLen,
                nullptr);
        }
        rD.m_fnVt28(pConn);
        return 0;
    }
    return 1;
}

} // namespace msg
