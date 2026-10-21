#pragma once
#include <cstdint>
#include <string>
#include <vector>

// Minimal MySQL wire-protocol client (no external libs, portable C++).
// Implements: handshake + mysql_native_password auth, COM_QUERY with
// text result set parsing, escaping. Enough for the server's cq_* tables.
// Wire format reference: dev.mysql.com/doc/dev/mysql-server/latest/
// (client/server protocol pages) - verified against MariaDB 10.11.

class CMySQLClient {
public:
    CMySQLClient();
    ~CMySQLClient();

    // returns false with sError set on failure
    bool Connect(const std::string& host, uint16_t port,
                 const std::string& user, const std::string& password,
                 const std::string& database);
    void Disconnect();
    bool IsConnected() const { return m_sock != -1; }

    // raw SQL; SELECT returns rows, everything else returns affected rows
    bool Query(const std::string& sql);
    const std::vector<std::vector<std::string>>& GetRows() const { return m_rows; }
    uint64_t GetAffectedRows() const { return m_ullAffected; }

    // single value helpers
    std::string Scalar(const std::string& sql, const std::string& fallback = "");

    // escape into a safe SQL string literal (without quotes)
    std::string Escape(const std::string& in);

    const std::string& GetError() const { return m_strError; }

private:
    // packet helpers
    bool RecvPacket(std::vector<uint8_t>& out, uint8_t& seqOut);
    bool SendPacket(uint8_t seq, const void* pBuf, size_t n);
    bool ReadHandshake(std::string& saltOut);
    bool SendAuth(const std::string& user, const std::string& password,
                  const std::string& database, const std::string& salt);
    bool HandleAuthResult();
    bool ReadResultSet();
    std::string ReadLenStr(const uint8_t*& p, const uint8_t* end);
    static uint64_t ReadLenInt(const uint8_t*& p, const uint8_t* end);

    int m_sock{-1};
    // auth state kept for AuthSwitchRequest handling
    std::string m_strAuthUser, m_strAuthPass, m_strAuthDb;
    std::string m_strError;
    std::vector<std::vector<std::string>> m_rows;
    uint64_t m_ullAffected{0};
};
