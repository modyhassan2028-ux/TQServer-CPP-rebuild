#include "Account.h"
#include "MySQLClient.h"
#include <cstdlib>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <algorithm>

// ---------- self-contained SHA-256 (no external deps) ----------
namespace {
struct Sha256 {
    uint32_t state[8];
    uint64_t bitlen = 0;
    uint8_t buffer[64]{};
    size_t buflen = 0;

    static uint32_t rotr(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }

    void init() {
        static const uint32_t initstate[8] = {0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
                                              0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};
        std::memcpy(state, initstate, sizeof(state));
        bitlen = 0; buflen = 0;
    }

    void transform(const uint8_t* p) {
        static const uint32_t K[64] = {
            0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
            0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
            0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
            0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
            0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
            0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
            0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
            0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
        uint32_t w[64];
        for (int i = 0; i < 16; ++i)
            w[i] = (uint32_t(p[i*4]) << 24) | (uint32_t(p[i*4+1]) << 16) |
                   (uint32_t(p[i*4+2]) << 8) | uint32_t(p[i*4+3]);
        for (int i = 16; i < 64; ++i) {
            uint32_t s0 = rotr(w[i-15],7) ^ rotr(w[i-15],18) ^ (w[i-15] >> 3);
            uint32_t s1 = rotr(w[i-2],17) ^ rotr(w[i-2],19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        uint32_t a=state[0],b=state[1],c=state[2],d=state[3],e=state[4],f=state[5],g=state[6],h=state[7];
        for (int i = 0; i < 64; ++i) {
            uint32_t S1 = rotr(e,6) ^ rotr(e,11) ^ rotr(e,25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t t1 = h + S1 + ch + K[i] + w[i];
            uint32_t S0 = rotr(a,2) ^ rotr(a,13) ^ rotr(a,22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t t2 = S0 + maj;
            h=g; g=f; f=e; e=d+t1; d=c; c=b; b=a; a=t1+t2;
        }
        state[0]+=a; state[1]+=b; state[2]+=c; state[3]+=d;
        state[4]+=e; state[5]+=f; state[6]+=g; state[7]+=h;
    }

    void update(const uint8_t* p, size_t n) {
        while (n > 0) {
            size_t take = 64 - buflen;
            if (take > n) take = n;
            std::memcpy(buffer + buflen, p, take);
            buflen += take; p += take; n -= take;
            if (buflen == 64) { transform(buffer); bitlen += 512; buflen = 0; }
        }
    }

    void final(uint8_t out[32]) {
        bitlen += buflen * 8;
        buffer[buflen++] = 0x80;
        if (buflen > 56) { while (buflen < 64) buffer[buflen++] = 0; transform(buffer); buflen = 0; }
        while (buflen < 56) buffer[buflen++] = 0;
        uint64_t bl = bitlen;
        for (int i = 0; i < 8; ++i) buffer[56 + i] = uint8_t(bl >> (56 - i*8));
        transform(buffer);
        for (int i = 0; i < 8; ++i) {
            out[i*4]   = uint8_t(state[i] >> 24);
            out[i*4+1] = uint8_t(state[i] >> 16);
            out[i*4+2] = uint8_t(state[i] >> 8);
            out[i*4+3] = uint8_t(state[i]);
        }
    }
};
} // namespace

std::string CAccountManager::Sha256Hex(const std::string& input) {
    Sha256 sha;
    sha.init();
    sha.update(reinterpret_cast<const uint8_t*>(input.data()), input.size());
    uint8_t digest[32];
    sha.final(digest);
    char hex[65];
    for (int i = 0; i < 32; ++i) snprintf(hex + i*2, 3, "%02x", digest[i]);
    return std::string(hex);
}

std::string CAccountManager::RandomSaltHex() {
    static std::mt19937_64 rng(static_cast<uint64_t>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    char buf[33];
    for (int i = 0; i < 32; i += 8)
        snprintf(buf + i, 9, "%08llx", (unsigned long long)(rng() & 0xffffffffULL));
    return std::string(buf, 32);
}

// ---------- manager ----------

CAccountManager& CAccountManager::Instance() {
    static CAccountManager s_instance;
    return s_instance;
}

void CAccountManager::Load(const std::string& path) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_byName.clear();
    std::ifstream in(path);
    if (!in) { m_bLoaded = true; printf("[ACCOUNT] No %s found, starting with an empty account store.\n", path.c_str()); return; }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        Account acc;
        int banned = 0;
        if (ss >> acc.name >> acc.dwId >> acc.saltHex >> acc.hashHex >> banned) {
            acc.bBanned = banned != 0;
            std::string key = acc.name;
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            m_byName[key] = acc;
            if (acc.dwId >= m_dwNextId) m_dwNextId = acc.dwId + 1;
        }
    }
    m_bLoaded = true;
    printf("[ACCOUNT] Loaded %zu account(s).\n", m_byName.size());
}

bool CAccountManager::Save(const std::string& path) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::ofstream out(path);
    if (!out) return false;
    out << "# name id salt hash banned\n";
    for (const auto& kv : m_byName)
        out << kv.second.name << ' ' << kv.second.dwId << ' '
            << kv.second.saltHex << ' ' << kv.second.hashHex << ' '
            << (kv.second.bBanned ? 1 : 0) << '\n';
    return true;
}

bool CAccountManager::CreateAccount(const std::string& name, const std::string& password, uint32_t& dwIdOut) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (name.empty() || password.empty()) return false;
    std::string key = name;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    if (m_byName.count(key)) return false;

    Account acc;
    acc.name = name;
    acc.dwId = m_dwNextId++;
    acc.saltHex = RandomSaltHex();
    acc.hashHex = Sha256Hex(acc.saltHex + password);
    m_byName[key] = acc;
    dwIdOut = acc.dwId;
    printf("[ACCOUNT] Created account '%s' (id %u).\n", name.c_str(), acc.dwId);
    return true;
}

CAccountManager::Result CAccountManager::Validate(const std::string& name, const std::string& password, uint32_t& dwIdOut) {
    if (!m_bLoaded) Load();
    std::string key = name;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    // MySQL mode: cq_account is authoritative; flat files stay untouched
    if (m_bMySQL && m_pDB) {
        std::lock_guard<std::mutex> dbLock(m_dbMutex);
        if (m_pDB->Query("SELECT id, password FROM cq_account WHERE name='" +
                         m_pDB->Escape(name) + "'") && !m_pDB->GetRows().empty()) {
            auto& row = m_pDB->GetRows()[0];
            uint32_t dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
            // stored hash = sha256(salt + password), salt embedded as "salt$hash"
            std::string stored = row[1];
            size_t sep = stored.find('$');
            if (sep == std::string::npos ||
                Sha256Hex(stored.substr(0, sep) + password) != stored.substr(sep + 1)) {
                printf("[DB] Bad password for account '%s'.\n", name.c_str());
                return Result::WrongPassword;
            }
            dwIdOut = dwId;
            return Result::Ok;
        }
        if (!m_bAutoCreate) return Result::NoSuchAccount;
        // dev mode: register into cq_account
        std::string salt = RandomSaltHex();
        std::string hash = Sha256Hex(salt + password);
        if (!m_pDB->Query("INSERT INTO cq_account (name, password) VALUES ('" +
                          m_pDB->Escape(name) + "', '" + m_pDB->Escape(salt + "$" + hash) + "')")) {
            printf("[DB] cq_account insert failed: %s\n", m_pDB->GetError().c_str());
            return Result::NoSuchAccount;
        }
        std::string idStr = m_pDB->Scalar("SELECT LAST_INSERT_ID()", "10000");
        dwIdOut = (uint32_t)strtoul(idStr.c_str(), nullptr, 10);
        printf("[DB] New account '%s' registered in MySQL (id %u).\n", name.c_str(), dwIdOut);
        return Result::Ok;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(key);
    if (it == m_byName.end()) {
        if (m_bAutoCreate) {
            // dev mode: first login registers the account, then this same
            // password is required from then on
            Account acc;
            acc.name = name;
            acc.dwId = m_dwNextId++;
            acc.saltHex = RandomSaltHex();
            acc.hashHex = Sha256Hex(acc.saltHex + password);
            m_byName[key] = acc;
            dwIdOut = acc.dwId;
            Save();
            printf("[ACCOUNT] New account '%s' registered (id %u).\n", name.c_str(), acc.dwId);
            return Result::Ok;
        }
        return Result::NoSuchAccount;
    }
    if (it->second.bBanned) return Result::Banned;
    if (Sha256Hex(it->second.saltHex + password) != it->second.hashHex)
        return Result::WrongPassword;
    dwIdOut = it->second.dwId;
    return Result::Ok;
}

// ---------------- MySQL mode ----------------
bool CAccountManager::TryMySQL(const std::string& host, uint16_t port, const std::string& user,
                               const std::string& password, const std::string& database) {
    if (!m_pDB) m_pDB = std::make_unique<CMySQLClient>();
    if (!m_pDB->Connect(host, port, user, password, database)) {
        printf("[DB] MySQL unavailable (%s) - staying in flat-file mode.\n",
               m_pDB->GetError().c_str());
        m_bMySQL = false;
        return false;
    }
    m_bMySQL = true;
    printf("[DB] MySQL connected: %s:%u/%s - accounts (cq_account) and characters (cq_user) persist to MySQL.\n",
           host.c_str(), port, database.c_str());
    return true;
}

// ---------------- cq_user character persistence ----------------
bool CAccountManager::LoadCharacter(uint32_t dwAccountId, CharacterRecord& out) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT level, money, cp, bank, pk_points, recordmap_id, recordx, recordy, experience, "
                      "stat_points, strength, vitality, reborn_count, last_reward_day "
                      "FROM cq_user WHERE account_id=" + std::to_string(dwAccountId)) ||
        m_pDB->GetRows().empty())
        return false;
    auto& row = m_pDB->GetRows()[0];
    out.dwLevel    = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
    out.dwMoney    = strtoull(row[1].c_str(), nullptr, 10);
    out.dwCp       = strtoull(row[2].c_str(), nullptr, 10);
    out.dwBank     = strtoull(row[3].c_str(), nullptr, 10);
    out.dwPkPoints = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
    out.dwMapId    = (uint32_t)strtoul(row[5].c_str(), nullptr, 10);
    out.usX        = (uint16_t)strtoul(row[6].c_str(), nullptr, 10);
    out.usY        = (uint16_t)strtoul(row[7].c_str(), nullptr, 10);
    out.dwExperience = (row.size() > 8) ? strtoull(row[8].c_str(), nullptr, 10) : 0;
    out.dwStatPoints = (row.size() > 9) ? (uint32_t)strtoul(row[9].c_str(), nullptr, 10) : 0;
    out.dwStrength   = (row.size() > 10) ? (uint32_t)strtoul(row[10].c_str(), nullptr, 10) : 0;
    out.dwVitality   = (row.size() > 11) ? (uint32_t)strtoul(row[11].c_str(), nullptr, 10) : 0;
    out.dwRebornCount = (row.size() > 12) ? (uint32_t)strtoul(row[12].c_str(), nullptr, 10) : 0;
    out.strLastRewardDay = (row.size() > 13) ? row[13] : "";
    return true;
}

void CAccountManager::SaveCharacter(uint32_t dwAccountId, const CharacterRecord& in) {
    if (!m_bMySQL || !m_pDB) return;
    std::string sql = "INSERT INTO cq_user (account_id, name, level, money, cp, bank, pk_points, "
                      "recordmap_id, recordx, recordy, experience, stat_points, strength, vitality, reborn_count) VALUES (" +
        std::to_string(dwAccountId) + ", '" + m_pDB->Escape(std::to_string(dwAccountId) + "_char") + "', " +
        std::to_string(in.dwLevel) + ", " + std::to_string(in.dwMoney) + ", " +
        std::to_string(in.dwCp) + ", " + std::to_string(in.dwBank) + ", " +
        std::to_string(in.dwPkPoints) + ", " + std::to_string(in.dwMapId) + ", " +
        std::to_string(in.usX) + ", " + std::to_string(in.usY) + ") "
        "ON DUPLICATE KEY UPDATE level=VALUES(level), money=VALUES(money), cp=VALUES(cp), "
        "bank=VALUES(bank), pk_points=VALUES(pk_points), recordmap_id=VALUES(recordmap_id), "
        "recordx=VALUES(recordx), recordy=VALUES(recordy)";
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query(sql))
        printf("[DB] cq_user save failed: %s\n", m_pDB->GetError().c_str());
}

// ---------------- cq_item inventory persistence ----------------
bool CAccountManager::LoadItems(uint32_t dwAccountId, std::vector<ItemRow>& out) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT item_type, sort, amount, position, name, plus FROM cq_item WHERE account_id=" +
                      std::to_string(dwAccountId)))
        return false;
    for (auto& row : m_pDB->GetRows()) {
        if (row.size() < 5) continue;
        ItemRow r;
        r.dwType     = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        r.usSort     = (uint16_t)strtoul(row[1].c_str(), nullptr, 10);
        r.dwAmount   = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        r.dwPosition = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        r.strName    = row[4];
        if (r.dwType) out.push_back(r);
    }
    return !out.empty();
}

void CAccountManager::SaveItems(uint32_t dwAccountId, const std::vector<ItemRow>& items) {
    if (!m_bMySQL || !m_pDB) return;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("DELETE FROM cq_item WHERE account_id=" + std::to_string(dwAccountId))) {
        printf("[DB] cq_item clear failed: %s\n", m_pDB->GetError().c_str());
        return;
    }
    for (const auto& r : items) {
        std::string sql = "INSERT INTO cq_item (account_id, item_type, sort, amount, position, name, plus) VALUES (" +
            std::to_string(dwAccountId) + ", " + std::to_string(r.dwType) + ", " +
            std::to_string(r.usSort) + ", " + std::to_string(r.dwAmount) + ", " +
            std::to_string(r.dwPosition) + ", '" + m_pDB->Escape(r.strName) + "', " +
                std::to_string(r.ucPlus) + ")";
        if (!m_pDB->Query(sql))
            printf("[DB] cq_item insert failed: %s\n", m_pDB->GetError().c_str());
    }
}

// persist the daily-reward day marker (kept separate from SaveCharacter
// because it must survive logout even when nothing else changed)
bool CAccountManager::SaveRewardDay(uint32_t dwAccountId, const std::string& strDay) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    return m_pDB->Query("UPDATE cq_user SET last_reward_day='" + m_pDB->Escape(strDay) +
                        "' WHERE account_id=" + std::to_string(dwAccountId));
}
