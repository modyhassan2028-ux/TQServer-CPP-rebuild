// ============================================================
// MsgServer strict port - unit M21
// ORIGINAL: FUN_140500670 @ 140500670
//           FUN_1405009f0 @ 1405009f0
// The connection's Send (from the leaked
// path: f:\version\cqserver-78.0.11-1204\
// msgserver\evnet\serversocket.cpp)
// The object: +0x14 m_nEvType, +0x1a the
// keyed flag, +0x824 the crypto block,
// +0x900 the WSA socket, +0x908 the
// send socket
// The LITERAL flow:
//  1. vt+0x20(this) == 0 -> return 0
//     len > 0x400 -> return 0
//  2. m_nEvType == 0 (the TQ socket):
//     keyed: memset(buf,0,0x408);
//       Encrypt(this+0x824, data, buf,
//         len)   fail -> log 0x2a2 -> 0
//       Encrypt(this+0x824, "TQServer",
//         buf+len, 8)   fail -> 0x2ae->0
//       n = Send(+0x908, buf, len+8);
//         n > -1 -> return 1
//         err = WsaLastError(+0x900)
//         err not 0x2733/0x2746 ->
//           ip = vt+0x30 ->
//           sprintf "%d.%d.%d.%d"
//           log line 0x2c4
//       LAB: vt+0x28(this) -> return 0
//     not keyed: plaintext Send(data,
//         len); n < 0 -> err check ->
//         log 0x2f3 (with ip) -> LAB
//  3. m_nEvType != 0: (evType-1) > 1
//     -> log 0x3f8-ish DAT_140796498 ->
//     vt+0x28 -> 0; else plaintext
//     Send; n < 0 -> err check ->
//     log 0x314 (NO ip) -> vt+0x28 -> 0
// FUN_1405009f0: return *(conn+0x1a)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgSendHandlerData {
    // vt+0x20 - the send guard
    std::function<bool(void*)> m_fnVt20;
    // vt+0x28 - the close/notify
    std::function<void(void*)> m_fnVt28;
    // vt+0x30 - get the peer IP (u32)
    std::function<uint32_t(void*)>
        m_fnVt30;
    // FUN_140504b80 (M19 encrypt)
    std::function<int(void*, const void*,
        void*, int)> m_fnEncrypt;
    // FUN_140544000 - the raw send
    std::function<int(void*, const void*,
        int)> m_fnSend;
    // FUN_140545950 - WSA last error
    std::function<int(void*)>
        m_fnWsaLastError;
    // tq::TimeGet(0) / tq::SysLogSave
    std::function<uint32_t(int)>
        m_fnTimeGet;
    // (line, errCode, dataLen, ipStr)
    std::function<void(int, int, int,
        const char*)> m_fnLog;
    // captures
    std::string sWire;    // the sent bytes
    int nSendLen = 0;
    int nVt28 = 0;
    // injectors
    bool bVt20 = true;
    int nSendRc = 1;
    int nWsaErr = 0;
    int nEncRc = 1;
    uint32_t uIp = 0xC0A80107;
};

// ===== ORIGINAL FUN_140500670 @ 140500670
int MsgSendHandler(void* pConn,
                   const void* pData,
                   int nLen,
                   MsgSendHandlerData& rD);

// ===== ORIGINAL FUN_1405009f0 @ 1405009f0
uint8_t MsgSendKeyed(const void* pConn);

} // namespace msg
