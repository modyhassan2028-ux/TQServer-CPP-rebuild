#include "CrossClient.h"
#include "../UserManager.h"
#include "../User.h"
#include "../MsgTalk.h"
#include "../MapManager.h"
#include "../Account.h"
#include "../MySQLClient.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <chrono>
#include <cstring>
#include <fstream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

// minimal ini reader (data/cross.ini)
static std::string ReadIni(const std::string& strPath, const std::string& strKey,
                           const std::string& strDefault) {
    std::ifstream f(strPath);
    std::string line;
    while (std::getline(f, line)) {
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq), val = line.substr(eq + 1);
        auto trim = [](std::string& s) {
            size_t a = s.find_first_not_of(" \t\r");
            size_t b = s.find_last_not_of(" \t\r");
            s = a == std::string::npos ? "" : s.substr(a, b - a + 1);
        };
        trim(key); trim(val);
        if (key == strKey) return val;
    }
    return strDefault;
}

namespace cross {

CCrossClient& CCrossClient::Instance() {
    static CCrossClient s;
    return s;
}

bool CCrossClient::Start() {
    if (m_bRunning.load()) return true;
    std::string strEnabled = ReadIni("data/cross.ini", "ENABLED", "1");
    if (strEnabled == "0") {
        printf("[CROSS] disabled in data/cross.ini - hub link off\n");
        return false;
    }
    m_dwServerId = strtoul(ReadIni("data/cross.ini", "SERVER_ID", "1").c_str(), nullptr, 10);
    m_strServerName = ReadIni("data/cross.ini", "SERVER_NAME", "Server1");
    m_strHubIp = ReadIni("data/cross.ini", "CROSS_IP", "127.0.0.1");
    m_usHubPort = (uint16_t)strtoul(ReadIni("data/cross.ini", "CROSS_PORT", "5820").c_str(),
                                    nullptr, 10);
    // realm identity: cq_realm row for our SERVER_ID wins over the ini
    auto* pDB = CAccountManager::Instance().GetDB();
    if (pDB && pDB->Query("SELECT name FROM cq_realm WHERE id=" +
                          std::to_string(m_dwServerId))) {
        auto& rows = pDB->GetRows();
        if (!rows.empty() && !rows[0].empty()) {
            m_strServerName = rows[0][0];
            printf("[CROSS] realm identity from cq_realm: '%s'\n",
                   m_strServerName.c_str());
        }
    }
    printf("[CROSS] linking to hub %s:%u as '%s' (id %u)\n",
           m_strHubIp.c_str(), m_usHubPort, m_strServerName.c_str(), m_dwServerId);
    m_bRunning.store(true);
    std::thread([this]() { Run(); }).detach();
    return true;
}

void CCrossClient::Stop() {
    m_bRunning.store(false);
    if (m_ullSocket != ~0ull) closesocket((SOCKET)m_ullSocket);
}

bool SendRaw(uint64_t ullSocket, const std::vector<uint8_t>& pkt) {
    if (ullSocket == ~0ull) return false;
    const char* p = (const char*)pkt.data();
    int left = (int)pkt.size(), sent = 0;
    while (sent < left) {
        int n = send((SOCKET)ullSocket, p + sent, left - sent, 0);
        if (n <= 0) return false;
        sent += n;
    }
    return true;
}

void CCrossClient::SendTalk(const std::string& strFrom, const std::string& strText) {
    TalkData t;
    t.dwServerId = m_dwServerId;
    CopyStr(t.szFrom, sizeof(t.szFrom), strFrom);
    CopyStr(t.szText, sizeof(t.szText), strText);
    std::lock_guard<std::mutex> lock(m_mutexSend);
    SendRaw(m_ullSocket, Encode(MsgType_Talk, t));
}

void CCrossClient::RequestWho(uint32_t dwUserId) {
    {
        std::lock_guard<std::mutex> lock(m_mutexPending);
        m_dwWhoUser = dwUserId;
    }
    // empty-frame who request: head only
    tq::MsgHead head;
    head.type = MsgType_WhoReq;
    head.length = sizeof(tq::MsgHead);
    std::vector<uint8_t> pkt(sizeof(head));
    std::memcpy(pkt.data(), &head, sizeof(head));
    std::lock_guard<std::mutex> lock(m_mutexSend);
    SendRaw(m_ullSocket, pkt);
}

void CCrossClient::PushRoster() {
    auto users = CUserManager::Instance().GetAllUsers();
    RosterData r;
    r.dwServerId = m_dwServerId;
    r.dwCount = 0;
    for (auto& u : users) {
        if (!u || r.dwCount >= MAX_ROSTER) break;
        CopyStr(r.entries[r.dwCount].szName, sizeof(r.entries[r.dwCount].szName),
                u->GetName());
        r.entries[r.dwCount].usLevel = (uint16_t)u->GetLevel();
        ++r.dwCount;
    }
    HeartbeatData b;
    b.dwServerId = m_dwServerId;
    b.dwOnline = (uint32_t)users.size();
    {
        std::lock_guard<std::mutex> lock(m_mutexSend);
        SendRaw(m_ullSocket, Encode(MsgType_Roster, r));
        SendRaw(m_ullSocket, Encode(MsgType_Heartbeat, b));
    }
}

void CCrossClient::HandlePacket(uint16_t usType, const std::vector<uint8_t>& payload) {
    if (usType == MsgType_Talk && payload.size() >= sizeof(TalkData)) {
        TalkData t;
        std::memcpy(&t, payload.data(), sizeof(t));
        std::string text = "[Cross] " + std::string(t.szFrom) + ": " + t.szText;
        CMsgTalk m;
        if (m.Create("SYSTEM", "", text, CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(m.GetBuf(), m.GetSize());
        return;
    }
    if (usType == MsgType_WhoResp && payload.size() >= sizeof(WhoRespData)) {
        WhoRespData w;
        std::memcpy(&w, payload.data(), sizeof(w));
        uint32_t dwUser;
        {
            std::lock_guard<std::mutex> lock(m_mutexPending);
            dwUser = m_dwWhoUser;
            m_dwWhoUser = 0;
        }
        if (!dwUser) return; // nobody asked
        auto pUser = CUserManager::Instance().GetUser(dwUser);
        if (!pUser) return;
        std::string out = "Cross servers:";
        for (uint32_t s = 0; s < std::min(w.dwServers, 8u); ++s) {
            out += std::string("\n  ") + w.servers[s].szServer + " (" +
                   std::to_string(w.servers[s].dwOnline) + " online):";
            for (uint32_t i = 0; i < std::min(w.servers[s].dwOnline, MAX_ROSTER); ++i)
                out += std::string("\n    ") + w.servers[s].entries[i].szName +
                       " lvl " + std::to_string(w.servers[s].entries[i].usLevel);
        }
        pUser->SendSysMsg(out);
        return;
    }
    if (usType == MsgType_ServerUp && payload.size() >= sizeof(ServerUpDownData)) {
        ServerUpDownData d;
        std::memcpy(&d, payload.data(), sizeof(d));
        std::string text = std::string("[Cross] Server online: ") + d.szName;
        CMsgTalk m;
        if (m.Create("SYSTEM", "", text, CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(m.GetBuf(), m.GetSize());
        return;
    }
    if (usType == MsgType_ServerDown && payload.size() >= sizeof(ServerUpDownData)) {
        ServerUpDownData d;
        std::memcpy(&d, payload.data(), sizeof(d));
        std::string text = std::string("[Cross] Server went down: ") + d.szName;
        CMsgTalk m;
        if (m.Create("SYSTEM", "", text, CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(m.GetBuf(), m.GetSize());
        return;
    }
}

void CCrossClient::Run() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    while (m_bRunning.load()) {
        SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s == INVALID_SOCKET) { std::this_thread::sleep_for(std::chrono::seconds(5)); continue; }
        sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_usHubPort);
        inet_pton(AF_INET, m_strHubIp.c_str(), &addr.sin_addr);
        if (connect(s, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            closesocket(s);
            std::this_thread::sleep_for(std::chrono::seconds(5)); // retry
            continue;
        }
        m_ullSocket = (uint64_t)s;
        m_bLinked.store(true);
        printf("[CROSS] linked to hub\n");
        // register (CCrossMsgOSConnectInfo equivalent)
        {
            HelloData h;
            h.dwServerId = m_dwServerId;
            CopyStr(h.szName, sizeof(h.szName), m_strServerName);
            std::lock_guard<std::mutex> lock(m_mutexSend);
            SendRaw(m_ullSocket, Encode(MsgType_Hello, h));
        }
        PushRoster();
        FrameDecoder decoder;
        uint8_t buf[4096];
        auto lastPush = std::chrono::steady_clock::now();
        for (;;) {
            int n = recv(s, (char*)buf, sizeof(buf), 0);
            if (n <= 0) break;
            uint16_t usType;
            std::vector<uint8_t> payload;
            bool bFresh = true;
            for (;;) {
                bool ok = bFresh ? decoder.Feed(buf, (uint32_t)n, usType, payload)
                                 : decoder.Drain(usType, payload);
                if (!ok) break;
                bFresh = false;
                HandlePacket(usType, payload);
            }
            if (std::chrono::steady_clock::now() - lastPush > std::chrono::seconds(30)) {
                PushRoster();
                lastPush = std::chrono::steady_clock::now();
            }
        }
        m_bLinked.store(false);
        m_ullSocket = ~0ull;
        closesocket(s);
        printf("[CROSS] hub link lost - retrying in 5s\n");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    WSACleanup();
}

} // namespace cross
