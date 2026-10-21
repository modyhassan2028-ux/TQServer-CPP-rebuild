#include "MySQLClient.h"

#include <cstring>
#include <cstdio>
#include "../../Core/CQBase/SHA1.h" // TQ core helper for the auth scramble

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <winsock2.h>
  #include <ws2tcpip.h>
  typedef int socklen_t;
  #define TQ_CLOSE_SOCK closesocket
  typedef int tq_sock_t;
#else
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <netinet/tcp.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <unistd.h>
  #define TQ_CLOSE_SOCK close
  typedef int tq_sock_t;
#endif

CMySQLClient::CMySQLClient() {}
CMySQLClient::~CMySQLClient() { Disconnect(); }

// ---------- low level ----------

bool CMySQLClient::RecvPacket(std::vector<uint8_t>& out, uint8_t& seqOut) {
    uint8_t hdr[4];
    size_t got = 0;
    while (got < 4) {
        ssize_t n = recv(m_sock, hdr + got, 4 - got, 0);
        if (n <= 0) { m_strError = "socket closed reading header"; return false; }
        got += (size_t)n;
    }
    uint32_t len = (uint32_t)hdr[0] | ((uint32_t)hdr[1] << 8) | ((uint32_t)hdr[2] << 16);
    seqOut = hdr[3];
    out.resize(len);
    got = 0;
    while (got < len) {
        ssize_t n = recv(m_sock, out.data() + got, len - got, 0);
        if (n <= 0) { m_strError = "socket closed reading body"; return false; }
        got += (size_t)n;
    }
    return true;
}

bool CMySQLClient::SendPacket(uint8_t seq, const void* pBuf, size_t n) {
    uint8_t hdr[4] = { (uint8_t)(n & 0xff), (uint8_t)((n >> 8) & 0xff),
                       (uint8_t)((n >> 16) & 0xff), seq };
    if (send(m_sock, hdr, 4, 0) != 4) return false;
    if (n && send(m_sock, pBuf, n, 0) != (ssize_t)n) return false;
    return true;
}

uint64_t CMySQLClient::ReadLenInt(const uint8_t*& p, const uint8_t* end) {
    if (p >= end) return 0;
    uint8_t first = *p;
    if (first < 0xfb) { ++p; return first; }
    if (first == 0xfb) { ++p; return 0; }          // NULL
    if (first == 0xfc) { if (end - p < 3) return 0; uint64_t v = p[1] | (p[2] << 8); p += 3; return v; }
    if (first == 0xfd) { if (end - p < 4) return 0; uint64_t v = p[1] | (p[2] << 8) | (p[3] << 16); p += 4; return v; }
    if (first == 0xfe) { if (end - p < 9) return 0; uint64_t v = 0; for (int i = 0; i < 8; ++i) v |= (uint64_t)p[1 + i] << (8 * i); p += 9; return v; }
    ++p; return 0;
}

std::string CMySQLClient::ReadLenStr(const uint8_t*& p, const uint8_t* end) {
    uint64_t len = ReadLenInt(p, end);
    if (len > (uint64_t)(end - p)) len = (uint64_t)(end - p);
    std::string s(reinterpret_cast<const char*>(p), (size_t)len);
    p += len;
    return s;
}


static void NativeScramble(const std::string& password, const std::string& salt, uint8_t out[20]) {
    uint8_t h1[20], h2[20], h3[20];
    tq::SHA1::Digest((const uint8_t*)password.data(), password.size(), h1);
    tq::SHA1::Digest(h1, 20, h2);
    {
        uint8_t buf[32];
        size_t sl = salt.size() > 20 ? 20 : salt.size();
        std::memcpy(buf, salt.data(), sl);
        std::memcpy(buf + sl, h2, 20);
        tq::SHA1::Digest(buf, sl + 20, h3);
    }
    for (int i = 0; i < 20; ++i) out[i] = h1[i] ^ h3[i];
}

// ---------- auth ----------

bool CMySQLClient::ReadHandshake(std::string& saltOut) {
    std::vector<uint8_t> pkt;
    uint8_t seq = 0;
    if (!RecvPacket(pkt, seq) || pkt.empty() || pkt[0] == 0xff) {
        m_strError = "bad handshake packet";
        return false;
    }
    // protocol version (1) + server version (null str)
    size_t pos = 1;
    while (pos < pkt.size() && pkt[pos]) ++pos;
    ++pos;
    pos += 4; // thread id
    // auth-plugin-data-part-1 (8 bytes) + filler
    std::string salt(reinterpret_cast<const char*>(&pkt[pos]), 8);
    pos += 8 + 1;
    pos += 2 + 1 + 2; // capability flags lower, charset, status flags
    pos += 2 + 10;     // capability upper, reserved
    // auth-plugin-data-part-2 (at least 13 bytes: 12 + null)
    if (pos + 13 <= pkt.size())
        salt.append(reinterpret_cast<const char*>(&pkt[pos]), 12);
    saltOut = salt;
    return true;
}

bool CMySQLClient::SendAuth(const std::string& user, const std::string& password,
                             const std::string& database, const std::string& salt) {
    uint8_t h4[20];
    NativeScramble(password, salt, h4);

    std::vector<uint8_t> body;
    auto put32 = [&](uint32_t v) { for (int i = 0; i < 4; ++i) body.push_back((v >> (8 * i)) & 0xff); };

    uint32_t caps = 0x0200 | 0x0800 | 0x00080000 | 0x00200000; // PROTOCOL_41|SECURE_CONN|PLUGIN_AUTH|MULTI_RESULTS
    put32(caps);
    put32(0x40000000); // max packet 16MB
    body.push_back(0x21); // utf8_general_ci
    for (int i = 0; i < 23; ++i) body.push_back(0);
    body.insert(body.end(), user.begin(), user.end());
    body.push_back(0);
    body.push_back(20); body.insert(body.end(), h4, h4 + 20);
    // CLIENT_PLUGIN_AUTH: name the auth plugin we used
    static const char kPlugin[] = "mysql_native_password";
    body.insert(body.end(), kPlugin, kPlugin + sizeof(kPlugin));

    m_strAuthUser = user;
    m_strAuthPass = password;
    m_strAuthDb = database;
    return SendPacket(1, body.data(), body.size());
}

bool CMySQLClient::HandleAuthResult() {
    for (int round = 0; round < 3; ++round) {
        std::vector<uint8_t> pkt;
        uint8_t seq = 0;
        if (!RecvPacket(pkt, seq)) return false;
        if (pkt.empty()) { m_strError = "empty auth reply"; return false; }
        if (pkt[0] == 0x00) return true;                       // OK
        if (pkt[0] == 0xff) {                                   // ERR
            uint16_t err = pkt[1] | (pkt[2] << 8);
            m_strError = "auth/SQL error " + std::to_string(err) + ": " +
                         std::string(reinterpret_cast<const char*>(pkt.data() + 9),
                                     pkt.size() > 9 ? pkt.size() - 9 : 0);
            return false;
        }
        if (pkt[0] == 0xfe) {                                   // AuthSwitchRequest
            const uint8_t* p = pkt.data() + 1;
            const uint8_t* end = pkt.data() + pkt.size();
            std::string plugin;
            while (p < end && *p) plugin.push_back((char)*p++);
            ++p; // null
            std::string salt(reinterpret_cast<const char*>(p), (size_t)(end - p));
            while (!salt.empty() && salt.back() == 0) salt.pop_back();
            if (plugin != "mysql_native_password") {
                m_strError = "server wants unsupported plugin: " + plugin;
                return false;
            }
            uint8_t h4[20];
            NativeScramble(m_strAuthPass, salt, h4);
            if (!SendPacket(seq + 1, h4, 20)) { m_strError = "send switch reply failed"; return false; }
            continue; // read the final result
        }
        m_strError = "unexpected auth packet";
        return false;
    }
    m_strError = "auth switch loop";
    return false;
}

bool CMySQLClient::Connect(const std::string& host, uint16_t port,
                           const std::string& user, const std::string& password,
                           const std::string& database) {
    Disconnect();
#ifdef _WIN32
    static bool s_bWsaInit = false;
    if (!s_bWsaInit) { WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa); s_bWsaInit = true; }
#endif
    m_sock = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0) { m_strError = "socket() failed"; return false; }
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) != 1) {
        addrinfo hints{}, *res = nullptr;
        hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host.c_str(), nullptr, &hints, &res) != 0 || !res) {
            m_strError = "cannot resolve host " + host;
            return false;
        }
        addr.sin_addr = ((sockaddr_in*)res->ai_addr)->sin_addr;
        freeaddrinfo(res);
    }
    if (connect((tq_sock_t)m_sock, (sockaddr*)&addr, (socklen_t)sizeof(addr)) != 0) {
        m_strError = "connect failed";
        return false;
    }
    int one = 1;
    setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));

    std::string salt;
    if (!ReadHandshake(salt)) return false;
    if (!SendAuth(user, password, database, salt)) { m_strError = "send auth failed"; return false; }
    if (!HandleAuthResult()) return false;
    if (!database.empty() && !Query("USE `" + Escape(database) + "`")) {
        m_strError = "cannot select database " + database + ": " + m_strError;
        return false;
    }
    return true;
}

void CMySQLClient::Disconnect() {
    if (m_sock >= 0) { TQ_CLOSE_SOCK(m_sock); m_sock = -1; }
}

bool CMySQLClient::ReadResultSet() {
    m_rows.clear();
    std::vector<uint8_t> pkt;
    uint8_t seq = 0;
    if (!RecvPacket(pkt, seq)) return false;
    if (pkt.empty()) { m_strError = "empty result"; return false; }
    if (pkt[0] == 0x00) { // OK packet: [0][affected lenenc][insert_id lenenc]...
        const uint8_t* p = pkt.data() + 1;
        const uint8_t* end = pkt.data() + pkt.size();
        m_ullAffected = ReadLenInt(p, end);
        return true;
    }
    if (pkt[0] == 0xff) {
        uint16_t err = pkt[1] | (pkt[2] << 8);
        m_strError = "SQL error " + std::to_string(err) + ": " +
                     std::string(reinterpret_cast<const char*>(pkt.data() + 9),
                                 pkt.size() > 9 ? pkt.size() - 9 : 0);
        return false;
    }
    // column count (lenenc)
    const uint8_t* p = pkt.data();
    const uint8_t* end = pkt.data() + pkt.size();
    uint64_t cols = ReadLenInt(p, end);

    for (uint64_t i = 0; i < cols; ++i) {
        std::vector<uint8_t> cp; // column definition packet - read and discard
        if (!RecvPacket(cp, seq)) return false;
    }
    {   // EOF after the column definitions (no CLIENT_DEPRECATE_EOF negotiated)
        std::vector<uint8_t> eofPkt;
        if (!RecvPacket(eofPkt, seq)) return false;
    }

    // EOF or OK (DEPRECATE_EOF off: EOF 0xfe)
    for (;;) {
        std::vector<uint8_t> rp;
        if (!RecvPacket(rp, seq)) return false;
        if (rp.empty()) continue;
        if (rp[0] == 0xfe && rp.size() < 9) break; // EOF: end of rows
        if (rp[0] == 0xfe && rp.size() >= 9) { /* auth-switch like, ignore */ }
        const uint8_t* rp2 = rp.data();
        const uint8_t* rend = rp2 + rp.size();
        std::vector<std::string> row;
        row.reserve(cols);
        for (uint64_t c = 0; c < cols; ++c) {
            // NULL marker or lenenc string
            if (rp2 < rend && *rp2 == 0xfb) { ++rp2; row.push_back(""); continue; }
            row.push_back(ReadLenStr(rp2, rend));
        }
        m_rows.push_back(std::move(row));
    }
    m_ullAffected = m_rows.size();
    return true;
}

bool CMySQLClient::Query(const std::string& sql) {
    if (m_sock < 0) { m_strError = "not connected"; return false; }
    std::vector<uint8_t> body;
    body.push_back(0x03); // COM_QUERY
    body.insert(body.end(), sql.begin(), sql.end());
    if (!SendPacket(0, body.data(), body.size())) { m_strError = "send query failed"; return false; }
    return ReadResultSet();
}

std::string CMySQLClient::Scalar(const std::string& sql, const std::string& fallback) {
    if (!Query(sql) || GetRows().empty() || GetRows()[0].empty()) return fallback;
    return GetRows()[0][0];
}

std::string CMySQLClient::Escape(const std::string& in) {
    std::string out;
    out.reserve(in.size() * 2);
    for (char c : in) {
        switch (c) {
        case '\\': out += "\\\\"; break;
        case '\'': out += "\\'"; break;
        case '"': out += "\\\""; break;
        case '\0': out += "\\0"; break;
        case '\n': out += "\\n"; break;
        case '\r': out += "\\r"; break;
        default: out += c;
        }
    }
    return out;
}
