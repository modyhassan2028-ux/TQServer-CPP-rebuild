// =====================================================================
// CCrossServerSocketKernel::Process — ORIGINAL FUN_14002c4e0 @
// 14002c4e0 (crossserver\crossserversocket\socketkernel.cpp)
// 13-case command dispatch, ported case by case. Every gate,
// log line and counter matches the decompile; helpers that live
// in other functions (accept plumbing FUN_140030390 etc.) carry
// TBD notes with their addresses.
// =====================================================================
#include "SocketKernel.h"

namespace cross {

// the ORIGINAL MYASSERT text (all cases share it)
static const char* SZ_SOCKETKERNEL_SRC =
    "f:\\version\\cqserver-78.0.11-1204\\crossserver\\"
    "crossserversocket\\socketkernel.cpp";

void CCrossServerSocketKernel::CleanupSocketRefs(uint32_t dwIdx) {
    // ORIGINAL FUN_14002b380(kernel, idx): drop the bimap and
    // accept-map entries that point at this socket slot
    CCrossSocket* pClosed =
        dwIdx < m_vecSockets.size() ? m_vecSockets[dwIdx]
                                     : nullptr;
    for (auto it = m_mapServerToSocket.begin();
         it != m_mapServerToSocket.end();) {
        if (it->second == dwIdx) {
            m_mapSocketToServer.erase(it->second);
            it = m_mapServerToSocket.erase(it);
        } else ++it;
    }
    for (auto it = m_mapAccept.begin(); it != m_mapAccept.end();)
        it = (it->second == pClosed)
            ? m_mapAccept.erase(it) : std::next(it);
    // TBD: the original also purges the route map (+0x120);
    // its key/value layout there is derived by FUN_14002b380's
    // walk, unrecovered at port time
}


// ===== CServerSocket::ProcessIncomingPacket (FUN_1400301d0) ==
void CServerSocket::ProcessIncomingPacket() {
    // ORIGINAL gates: no handle -> nothing; buffered > 0x7ff ->
    // flush frames first (the kernel walk)
    if (!m_ullOsHandle) return;
    if (0x7ff < m_nBufBytes) m_fnDrain(this);
    // FUN_1400379c0(handle) + FUN_14003f5c0 = OS bytes available
    // (the test seam exposes it as the RecvFn's internal state);
    // the drain loop: read min(available, 0x800 - buffered)
    int nAvail = m_fnRecv(nullptr, 0);
    while (nAvail > 0) {
        int nRoom = 0x800 - m_nBufBytes;
        int nRead = nAvail < nRoom ? nAvail : nRoom;
        int nGot = m_fnRecv(m_byBuf + m_nBufBytes, nRead);
        if (nGot < 1) {
            // ORIGINAL: FUN_14003a790(+0x203) then
            // "CServerSocket::ProcessIncomingPacket can not
            // drain the buffer for socket[%u], err:%d."
            m_nLastErr = -1;
            printf("[SOCKETKERNEL] CServerSocket::"
                   "ProcessIncomingPacket can not drain the "
                   "buffer for socket[%u], err:%d.\n",
                   (unsigned)m_ullOsHandle, m_nLastErr);
            return;
        }
        m_nBufBytes += nGot;
        nAvail -= nGot;
        // process complete frames after every read
        m_fnDrain(this);
        if (nAvail < 1) return;
    }
}


// ===== FUN_14002e6d0: the frame walker =======================
size_t CServerSocket::WalkFrames() {
    size_t nWalked = 0;
    const uint8_t* p = m_byBuf;
    int nAvail = m_nBufBytes;
    while (true) {
        // ORIGINAL gate: avail < 1 -> done (return 1)
        if (nAvail < 1) return nWalked;
        // ORIGINAL: 0x10 < avail && size@0xc <= avail &&
        //           0xf < size && size < 0x419
        if (!(0x10 < nAvail)) return nWalked;
        uint16_t uSize; std::memcpy(&uSize, p + 0xc, 2);
        if (!((int)uSize <= nAvail && 0xf < uSize
              && uSize < 0x419)) {
            // TBD: the original's failure tail beyond the gate
            // (frame drop/flush) is unrecovered at port time
            return nWalked;
        }
        uint16_t uC;   std::memcpy(&uC, p + 0x0, 2);
        uint32_t uA;   std::memcpy(&uA, p + 0x4, 4);
        uint32_t uB;   std::memcpy(&uB, p + 0x8, 4);
        uint16_t uType; std::memcpy(&uType, p + 0xe, 2);
        const int nPay = uSize - 0x10;
        const uint8_t* pay = p + 0x10;

        if (uType == 0x9c4f) {
            // ---- ORIGINAL ServerName/hello frame ----
            // socket slot lookup (vcall +0x48 = slot id), then
            // FUN_140022780 parse; on success sprintf
            // "%u %u %u %s" (slotid, vcall+0x28, name) and
            // PostCommand(3, 0x3ef, len) - the BIND command
            char szName[80] = {0};
            uint32_t dwPeer = 0;
            if (m_fnParseName && m_fnParseName(&dwPeer, szName,
                                               pay)) {
                char szCmd[160];
                // ORIGINAL: sprintf("%u %u %u %s", slotid,
                // vcall+0x28 result, ???, name) - the third
                // %u argument is unrecovered in the decompile;
                // TBD(0) placeholder rather than a guess
                int nLen = std::snprintf(szCmd, sizeof szCmd,
                    "%u %u %u %s", (uint32_t)(uintptr_t)
                    m_ullOsHandle, dwPeer, 0, szName);
                if (m_fnPostCmd) m_fnPostCmd(3, 0x3ef, szCmd);
            }
        } else if (uType == 0x9c55) {
            // ---- EnterOSUserSocketOpt (FUN_140049090) ----
            uint16_t usMode = 0xffff;
            uint32_t dwSrv = 0, dwSlot = 0xffffffff;
            if (m_fnParseOsOpt && m_fnParseOsOpt(&usMode, &dwSrv,
                                                 &dwSlot, pay)) {
                if (usMode == 0 || usMode == 1 || usMode == 3) {
                    // bind: route[(slot, srv)] = (B, peer-slot)
                    // + PostCommand(1, 0x7562, 0x418)
                    if (m_pKernel)
                        m_pKernel->RoutePut(uA, dwSlot, uB,
                                            dwSrv);
                    if (m_fnPostCmd)
                        m_fnPostCmd(1, 0x7562, "\x18");
                } else if (usMode == 2 || usMode == 4) {
                    // del: log on server miss +
                    // route erase of (dwSlot-of-srv, B)
                    uint32_t dwSl = dwSlot;
                    if (dwSrv != 0 && m_pKernel)
                        dwSl = m_pKernel->SlotOfServer(dwSrv);
                    if (dwSl == 0xffffffff)
                        printf("[SOCKETKERNEL] CCrossMsgEnterOS"
                               "UserSocketOpt::ENTER_OS_USER_"
                               "SOCKET_OPT_DEL, not find server"
                               "(%u) soket\n", dwSrv);
                    if (m_pKernel)
                        m_pKernel->RouteDel(uA, dwSl);
                }
                // TBD: case 5 tail (partially recovered)
            }
        } else if (uC < 2 || uC == 10) {
            // ---- LAB_14002f500: pre-registration frames ----
            // route lookup by (slotid, A); miss ->
            // PostCommand(3, 0x3ec); TBD: the recovered
            // sub-walk with the node+0x21 connected flag and
            // the mode-6/8 tails (FUN_14002e650/e1c0,
            // FUN_140014e20, FUN_14002b560 delivery)
            if (m_fnDeliverMsg)
                m_fnDeliverMsg(uType, pay, nPay);
        } else {
            // TBD: remaining walker branches (mode 6 main
            // delivery chain FUN_14002b560, mode 8 bimap walk)
            if (m_fnDeliverMsg)
                m_fnDeliverMsg(uType, pay, nPay);
        }
        // consume the frame: socket vcall[1](size) and the
        // DAT_14007ad10 recv counter
        p += uSize; nAvail -= uSize; nWalked += uSize;
        m_ullRecvBytes += uSize;
    }
}

bool CCrossServerSocketKernel::Process(uint32_t dwCmd, void* pCmd) {
    // every case reinterprets the command buffer: u32 words for
    // the binary cases, a text line for the sscanf cases
    uint32_t* p = (uint32_t*)pCmd;

    switch (dwCmd) {
    case SockCmd_Send: { // ---------------- ORIGINAL case 0x7562
        // p[0] socket idx; frame: type=p[4], A=p[1], B=p[2],
        // C=p[3]; p[5] = payload size; p+6 = payload bytes
        if (CCrossSocket** ppSlot = Slot(p[0])) {
            if (*ppSlot) {
                uint32_t dwSize = p[5];
                if ((int32_t)(dwSize + 0x10) < 0x419) {
                    // frame = 0x10 head + payload
                    std::vector<uint8_t> frame(dwSize + 0x10, 0);
                    uint16_t u16;
                    u16 = (uint16_t)p[4];
                    std::memcpy(frame.data() + 0x0, &u16, 2);
                    std::memcpy(frame.data() + 0x4, &p[1], 4);
                    std::memcpy(frame.data() + 0x8, &p[2], 4);
                    u16 = (uint16_t)(dwSize + 0x10);
                    std::memcpy(frame.data() + 0xc, &u16, 2);
                    u16 = (uint16_t)p[3];
                    std::memcpy(frame.data() + 0xe, &u16, 2);
                    std::memcpy(frame.data() + 0x10, p + 6, dwSize);
                    // ORIGINAL: tq::TimeGet(0) then vcall +0x10
                    (*ppSlot)->Send(frame.data(),
                                    (uint32_t)frame.size());
                    m_ullPkts++;   // DAT_14007ad0c
                    m_ullBytesA += frame.size(); // DAT_14007acc8
                    m_ullBytesB += frame.size(); // DAT_14007ad08
                    return true;
                }
                // ORIGINAL: MYASSERT("nNetPacketSize") line 0x123
                printf("[SOCKETKERNEL] MYASSERT nNetPacketSize "
                       "%s @%d\n", SZ_SOCKETKERNEL_SRC, 0x123);
            }
        }
        break;
    }
    case SockCmd_ConnRes: { // ---------- ORIGINAL case 0x7563
        // sscanf "%lu %d": socket idx, result flag
        uint32_t dwIdx; int nFlag;
        if (sscanf((const char*)pCmd, "%lu %d",
                   &dwIdx, &nFlag) == 2) {
            CCrossSocket** ppSlot = Slot(dwIdx);
            if (!ppSlot || !*ppSlot) return false;
            // ORIGINAL gate: vcall +0x18 IsConnected
            if (!(*ppSlot)->IsConnected()) return false;
            if (nFlag == 0) {
                // connect failed -> vcall +0x20 Close +
                // FUN_14002b380 cleanup + slot null + destroy
                (*ppSlot)->Close();
                CleanupSocketRefs(dwIdx);
                *ppSlot = nullptr;
                // ORIGINAL: FUN_140030480(socket) - destroy
            } else if (nFlag != 1) {
                // bad flag: log line 0x18b
                printf("[SOCKETKERNEL] SOCKET_CHECK_CONNECT_RESULT"
                       " has a bad param \"%s\" @%d\n",
                       (const char*)pCmd, 0x18b);
            }
        } else {
            // sscanf failed: log line 0x191
            printf("[SOCKETKERNEL] SOCKET_CHECK_CONNECT_RESULT"
                   " has a bad param \"%s\" @%d\n",
                   (const char*)pCmd, 0x191);
        }
        break;
    }
    case SockCmd_Send32: { // ------------- ORIGINAL case 0x7564
        // like 0x7562 but the payload carries u32 words first:
        // frame: type=p[4], A=p[2], B=p[1] (word count), C=p[3];
        // payload = p[6..] for (count*4 + p[5]) bytes
        if (CCrossSocket** ppSlot = Slot(p[0])) {
            if (*ppSlot) {
                uint32_t dwCount = p[1], dwSize = p[5];
                if ((int32_t)(dwSize + 0x10 + dwCount * 4)
                        < 0x419) {
                    const uint32_t dwPay =
                        dwCount * 4 + dwSize;
                    std::vector<uint8_t> frame(dwPay + 0x10, 0);
                    uint16_t u16;
                    u16 = (uint16_t)p[4];
                    std::memcpy(frame.data() + 0x0, &u16, 2);
                    std::memcpy(frame.data() + 0x4, &p[2], 4);
                    std::memcpy(frame.data() + 0x8, &p[1], 4);
                    u16 = (uint16_t)(dwPay + 0x10);
                    std::memcpy(frame.data() + 0xc, &u16, 2);
                    u16 = (uint16_t)p[3];
                    std::memcpy(frame.data() + 0xe, &u16, 2);
                    std::memcpy(frame.data() + 0x10, p + 6, dwPay);
                    (*ppSlot)->Send(frame.data(),
                                    (uint32_t)frame.size());
                    m_ullPkts++;
                    m_ullBytesA += frame.size();
                    m_ullBytesB += frame.size();
                    return true;
                }
                printf("[SOCKETKERNEL] MYASSERT nNetPacketSize "
                       "%s @%d\n", SZ_SOCKETKERNEL_SRC, 0x14a);
            }
        }
        break;
    }
    case SockCmd_BindPair: { // ---------- ORIGINAL case 0x7565
        // sscanf "%u %u": server, socket -> bimap both ways
        uint32_t dwA, dwB;
        if (sscanf((const char*)pCmd, "%u %u", &dwA, &dwB) == 2) {
            // +0xa0 map keyed by A, +0xe0 map keyed by B
            m_mapServerToSocket[dwA] = dwB;
            m_mapSocketToServer[dwB] = dwA;
        }
        break;
    }
    case SockCmd_Unbind: { // ------------- ORIGINAL case 0x7566
        // sscanf "%u %u": erase server from the forward map and
        // socket from the reverse map (only when actually found:
        // ORIGINAL FUN_14000d040 lower_bound + FUN_14000bd70)
        uint32_t dwA, dwB;
        if (sscanf((const char*)pCmd, "%u %u", &dwA, &dwB) == 2) {
            m_mapServerToSocket.erase(dwA);
            m_mapSocketToServer.erase(dwB);
        }
        break;
    }
    case SockCmd_RoutePut: { // ----------- ORIGINAL case 0x7567
        // sscanf "%u %u %u %u" -> +0x120 route map: 64-bit key
        // (CONCAT44 of the 3rd/4th) -> 64-bit value (1st/2nd)
        uint32_t dw1, dw2, dw3, dw4;
        if (sscanf((const char*)pCmd, "%u %u %u %u",
                   &dw1, &dw2, &dw3, &dw4) == 4) {
            uint64_t ullKey =
                ((uint64_t)dw1 << 32) | dw2;
            uint64_t ullVal =
                ((uint64_t)dw3 << 32) | dw4;
            m_mapRoute[ullKey] = ullVal;
        }
        break;
    }
    case SockCmd_RouteDel: { // ----------- ORIGINAL case 0x7568
        uint32_t dw1, dw2;
        if (sscanf((const char*)pCmd, "%u %u",
                   &dw1, &dw2) == 2) {
            m_mapRoute.erase(((uint64_t)dw1 << 32) | dw2);
        }
        break;
    }
    case SockCmd_Relay: { // -------------- ORIGINAL case 0x7569
        // send the SAME frame on every bimap socket except the
        // origin (p[0] on entry); *p is the scratch "current
        // socket" field the original rewrites in place
        const uint32_t dwOrigin = p[0];
        for (const auto& kv : m_mapServerToSocket) {
            if (kv.second == dwOrigin) continue;
            CCrossSocket** ppSlot = Slot(kv.second);
            if (!ppSlot || !*ppSlot) continue;
            uint32_t dwSize = p[5];
            if ((int32_t)(dwSize + 0x10) >= 0x419) {
                printf("[SOCKETKERNEL] MYASSERT nNetPacketSize "
                       "%s @%d\n", SZ_SOCKETKERNEL_SRC, 0x1fe);
                continue;
            }
            std::vector<uint8_t> frame(dwSize + 0x10, 0);
            uint16_t u16;
            u16 = (uint16_t)p[4];
            std::memcpy(frame.data() + 0x0, &u16, 2);
            std::memcpy(frame.data() + 0x4, &p[1], 4);
            std::memcpy(frame.data() + 0x8, &p[2], 4);
            u16 = (uint16_t)(dwSize + 0x10);
            std::memcpy(frame.data() + 0xc, &u16, 2);
            u16 = (uint16_t)p[3];
            std::memcpy(frame.data() + 0xe, &u16, 2);
            std::memcpy(frame.data() + 0x10, p + 6, dwSize);
            (*ppSlot)->Send(frame.data(),
                            (uint32_t)frame.size());
            m_ullPkts++;
            m_ullBytesA += frame.size();
            m_ullBytesB += frame.size();
        }
        return true; // ORIGINAL: LAB_14002d115 return 1
    }
    case SockCmd_Close: { // -------------- ORIGINAL case 0x756b
        // binary variant of 0x7563's flag-0 path: close + cleanup
        // + null slot + FUN_140030480 destroy
        if (CCrossSocket** ppSlot = Slot(p[0])) {
            if (*ppSlot && (*ppSlot)->IsConnected()) {
                (*ppSlot)->Close();
                CleanupSocketRefs(p[0]);
                *ppSlot = nullptr;
            }
        }
        break;
    }
    case SockCmd_Accept: { // ------------- ORIGINAL case 0x756c
        // accept plumbing: FUN_140030390 creates the socket
        // object, FUN_14002c260 finds a free +0x18 slot,
        // FUN_14002bba0 registers it in the +0x60 accept map,
        // vcall +0x40 binds the id, then the accept handshake
        // (FUN_14002fcc0 walks) queues a message to the kernel
        // through the +0x50 backlink vcall +0x50.
        // TBD: the FUN_140030390 accept object internals and
        // the +0x50 post-accept message payload are unrecovered;
        // the rebuild models the slot/bind part so the class can
        // be driven by the tests.
        // (the test seam AddSocket covers the observable part)
        break;
    }
    case SockCmd_Recv: { // --------------- ORIGINAL case 0x756d
        // FUN_14002bad0(kernel, handle) -> FUN_1400301d0(sock):
        // the recv drain loop on the socket's OS handle
        CServerSocket* pSock =
            FindByHandle(*(uint64_t*)pCmd);
        if (pSock) pSock->ProcessIncomingPacket();
        break;
    }
    case SockCmd_OnClose: { // ------------ ORIGINAL case 0x756e
        // FUN_14002bad0(kernel, handle) -> vcall +0x48 OnClose
        CServerSocket* pSock =
            FindByHandle(*(uint64_t*)pCmd);
        if (pSock) pSock->OnClose();
        break;
    }
    }
    return false;
}

} // namespace cross
