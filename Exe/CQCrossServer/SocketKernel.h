// =====================================================================
// CCrossServerSocketKernel — ORIGINAL FUN_14002c4e0
// (crossserver\crossserversocket\socketkernel.cpp)
//
// The hub socket kernel's COMMAND/EVENT dispatch. The original
// class layout (from the decompile):
//   +0x18.. +0x30/+0x38  socket array (capacity =
//                        (m_vecEnd - m_vecBegin) / 8)
//   +0x50                kernel backlink (post-accept notify)
//   +0x60                accept map (u32 id -> socket obj)
//   +0xa0/+0xd0          server -> socket map (bimap forward)
//   +0xe0/+0x110         socket -> server map (bimap reverse)
//   +0x120/+0x150        route map (u64 key -> u64 value)
// Global stats (DAT_14007ad0c / DAT_14007acc8 / DAT_14007ad08)
// are per-class in the rebuild (counters below).
//
// Command types (the ORIGINAL switch cases):
//   0x7562 SendCmd      0x7563 ConnectResult(text "idx flag")
//   0x7564 SendCmd32    0x7565 BindPair(text "server socket")
//   0x7566 UnbindPair   0x7567 RoutePut(text 4x u32)
//   0x7568 RouteDel     0x7569 RelayAll (skip origin socket)
//   0x756b CloseSocket  0x756c Accept
//   0x756d Recv         0x756e OnClose
//
// Wire frame built by the send cases (0x10 bytes + payload):
//   +0 u16 type | +4 u32 A | +8 u32 B
//   +0xc u16 total size (payload + 0x10) | +0xe u16 C
// =====================================================================
#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <map>
#include <vector>
#include <memory>
#include <functional>

namespace cross {

// ORIGINAL socket object vtable (from the dispatch's vcalls):
//   +0x10 Send(buf, size)      +0x18 IsConnected() -> bool
//   +0x20 Close()               +0x28 (accept handshake)
//   +0x30 (accept handshake)    +0x38 GetId() -> u32
//   +0x40 BindId(u32)           +0x48 OnClose()
class CCrossSocket {
public:
    virtual ~CCrossSocket() = default;
    virtual bool Send(const void* pBuf, uint32_t dwSize) = 0;
    virtual bool IsConnected() const = 0;
    virtual void Close() = 0;
    virtual uint32_t GetId() const = 0;
    virtual void BindId(uint32_t) = 0;
    virtual void OnClose() = 0;
};

// command constants - ORIGINAL case values
enum SocketCmd {
    SockCmd_Send     = 0x7562,
    SockCmd_ConnRes  = 0x7563,
    SockCmd_Send32   = 0x7564,
    SockCmd_BindPair = 0x7565,
    SockCmd_Unbind   = 0x7566,
    SockCmd_RoutePut = 0x7567,
    SockCmd_RouteDel = 0x7568,
    SockCmd_Relay    = 0x7569,
    SockCmd_Close    = 0x756b,
    SockCmd_Accept   = 0x756c,
    SockCmd_Recv     = 0x756d,
    SockCmd_OnClose  = 0x756e,
};

// ---------------------------------------------------------------------
// CServerSocket — ORIGINAL socket object of the socketkernel layer.
// From FUN_1400301d0 (CServerSocket::ProcessIncomingPacket):
//   +0x8                recv buffer (0x800 bytes)
//   +0x101 (0x808)      buffered byte count
//   +0x203 (0x1018)     last error slot (FUN_14003a790)
//   +0x204 (0x1020)     parent kernel backlink
//   +0x205 (0x1028)     OS socket handle
// ---------------------------------------------------------------------
class CCrossServerSocketKernel;

class CServerSocket : public CCrossSocket {
public:
    static constexpr size_t SOCKET_BUF = 0x800;

    // ORIGINAL FUN_140037a80 (OS recv) - test seam
    using RecvFn = std::function<int(void*, int)>;
    // ORIGINAL FUN_14002e6d0 (the frame dispatcher walk) - TBD:
    // its 699-line body is the next porting unit; the drain
    // loop calls it after every read
    using DrainFn = std::function<void(CServerSocket*)>;

    CServerSocket(CCrossServerSocketKernel* pKernel,
                  uint64_t ullOsHandle, RecvFn fnRecv,
                  DrainFn fnDrain)
        : m_pKernel(pKernel), m_ullOsHandle(ullOsHandle),
          m_fnRecv(std::move(fnRecv)),
          m_fnDrain(std::move(fnDrain)) {}

    bool Send(const void*, uint32_t) override { return true; }
    bool IsConnected() const override { return m_ullOsHandle != 0; }
    void Close() override { m_ullOsHandle = 0; }
    uint32_t GetId() const override { return m_dwId; }
    void BindId(uint32_t dw) override { m_dwId = dw; }
    void OnClose() override {}

    // ---- ORIGINAL FUN_1400301d0: recv drain loop ----
    void ProcessIncomingPacket();

    uint32_t m_dwId = 0;
    uint8_t  m_byBuf[SOCKET_BUF] = {0};   // +0x8
    int      m_nBufBytes = 0;             // +0x101 (0x808)
    CCrossServerSocketKernel* m_pKernel; // +0x204
    uint64_t m_ullOsHandle;               // +0x205 (0x1028)
    RecvFn   m_fnRecv;
    DrainFn  m_fnDrain;
    int      m_nLastErr = 0;              // +0x203 (0x1018)
};

class CCrossServerSocketKernel {
public:
    explicit CCrossServerSocketKernel(size_t nCapacity = 64)
        : m_vecSockets(nCapacity, nullptr) {}

    // ---- ORIGINAL FUN_14002c4e0: the 13-case dispatch ----
    // returns true when the command produced a send (ORIGINAL
    // `return 1` in the send paths, fallthrough break = false)
    bool Process(uint32_t dwCmd, void* pCmd);

    // ---- ORIGINAL FUN_14002bad0: socket by OS handle ----
    CServerSocket* FindByHandle(uint64_t ullHandle) {
        if (ullHandle == (uint64_t)-1) return nullptr;
        auto it = m_mapAccept.find(ullHandle);
        return it == m_mapAccept.end() ? nullptr : it->second;
    }
    void RegisterByHandle(uint64_t ullHandle, CServerSocket* p) {
        m_mapAccept[ullHandle] = p;
    }

    // ---- test seams / rebuild wiring ----
    void SetSocket(uint32_t dwIdx, CCrossSocket* p) {
        if (dwIdx < m_vecSockets.size())
            m_vecSockets[dwIdx] = p;
    }
    uint32_t AddSocket(std::unique_ptr<CCrossSocket> p) {
        for (uint32_t i = 0; i < m_vecSockets.size(); ++i)
            if (!m_vecSockets[i]) {
                m_vecSockets[i] = p.get();
                m_vecOwned.push_back(std::move(p));
                return i;
            }
        m_vecSockets.push_back(p.get());
        m_vecOwned.push_back(std::move(p));
        return (uint32_t)(m_vecSockets.size() - 1);
    }
    uint32_t SocketOfServer(uint32_t dwSrv) const {
        auto it = m_mapServerToSocket.find(dwSrv);
        return it == m_mapServerToSocket.end() ? 0xffffffffu
                                               : it->second;
    }
    uint32_t ServerOfSocket(uint32_t dwSock) const {
        auto it = m_mapSocketToServer.find(dwSock);
        return it == m_mapSocketToServer.end() ? 0xffffffffu
                                               : it->second;
    }
    uint64_t RouteGet(uint64_t ullKey) const {
        auto it = m_mapRoute.find(ullKey);
        return it == m_mapRoute.end() ? 0 : it->second;
    }
    // stats: DAT_14007ad0c / DAT_14007acc8 / DAT_14007ad08
    uint64_t m_ullPkts = 0, m_ullBytesA = 0, m_ullBytesB = 0;

private:
    // ORIGINAL FUN_140025320: index the +0x18 socket array
    CCrossSocket** Slot(uint32_t dwIdx) {
        return dwIdx < m_vecSockets.size()
            ? &m_vecSockets[dwIdx] : nullptr;
    }
    // ORIGINAL FUN_14002b380: post-close cleanup of the maps
    void CleanupSocketRefs(uint32_t dwIdx);

    std::vector<CCrossSocket*> m_vecSockets;   // +0x18
    std::vector<std::unique_ptr<CCrossSocket>> m_vecOwned;
    std::map<uint32_t, uint32_t> m_mapServerToSocket; // +0xa0
    std::map<uint32_t, uint32_t> m_mapSocketToServer; // +0xe0
    std::map<uint64_t, uint64_t> m_mapRoute; // +0x120
    // +0x60 accept map: OS handle -> socket object
    // (ORIGINAL FUN_140029e60 lookups, FUN_14002bad0 reader)
    std::map<uint64_t, CServerSocket*> m_mapAccept;
};

} // namespace cross
