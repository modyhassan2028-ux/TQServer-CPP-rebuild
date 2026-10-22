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

    // MySQL mode: the ORIGINAL 6159 `accounts` table is authoritative —
    // the same schema the original AccountServer.exe validates against
    // (name + plaintext password, banned, enabled, type = GM level).
    if (m_bMySQL && m_pDB) {
        std::lock_guard<std::mutex> dbLock(m_dbMutex);
        if (m_pDB->Query("SELECT id, password, banned + 0, enabled + 0, type FROM accounts WHERE name='" +
                         m_pDB->Escape(name) + "'") && !m_pDB->GetRows().empty()) {
            auto& row = m_pDB->GetRows()[0];
            uint32_t dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
            if (row[2] != "0") { // accounts.banned (original: blocks login)
                printf("[DB] Account '%s' is banned.\n", name.c_str());
                return Result::Banned;
            }
            if (row[3] == "0") return Result::Disabled;
            if (row[1] != password) { // original: plaintext compare (AccountServer 1051 flow)
                printf("[DB] Bad password for account '%s'.\n", name.c_str());
                return Result::WrongPassword;
            }
            dwIdOut = dwId;
            return Result::Ok;
        }
        if (!m_bAutoCreate) return Result::NoSuchAccount;
        // dev mode: register into the ORIGINAL accounts table with the
        // original defaults (enabled = 1, type = 2 player, point = 100000)
        if (!m_pDB->Query("INSERT INTO accounts (name, password, enabled, type, point) VALUES ('" +
                          m_pDB->Escape(name) + "', '" + m_pDB->Escape(password) + "', 1, 2, 100000)")) {
            printf("[DB] accounts insert failed: %s\n", m_pDB->GetError().c_str());
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
    // ORIGINAL cq_user columns (6159): exp, money_saved = bank, emoney = CP,
    // additional_point = stat points, health = vitality, metempsychosis = reborns
    if (!m_pDB->Query("SELECT level, exp, money, money_saved, emoney, pk, "
                      "recordmap_id, recordx, recordy, strength, health, additional_point, metempsychosis "
                      "FROM cq_user WHERE account_id=" + std::to_string(dwAccountId) + " ORDER BY id LIMIT 1") ||
        m_pDB->GetRows().empty())
        return false;
    auto& row = m_pDB->GetRows()[0];
    out.dwLevel    = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
    out.dwExperience = strtoull(row[1].c_str(), nullptr, 10);
    out.dwMoney    = strtoull(row[2].c_str(), nullptr, 10);
    out.dwBank     = strtoull(row[3].c_str(), nullptr, 10);
    out.dwCp       = strtoull(row[4].c_str(), nullptr, 10);
    out.dwPkPoints = (uint32_t)strtoul(row[5].c_str(), nullptr, 10);
    out.dwMapId    = (uint32_t)strtoul(row[6].c_str(), nullptr, 10);
    out.usX        = (uint16_t)strtoul(row[7].c_str(), nullptr, 10);
    out.usY        = (uint16_t)strtoul(row[8].c_str(), nullptr, 10);
    out.dwStrength   = (uint32_t)strtoul(row[9].c_str(), nullptr, 10);
    out.dwVitality   = (uint32_t)strtoul(row[10].c_str(), nullptr, 10);
    out.dwStatPoints = (uint32_t)strtoul(row[11].c_str(), nullptr, 10);
    out.dwRebornCount = (uint32_t)strtoul(row[12].c_str(), nullptr, 10);
    return true;
}

void CAccountManager::SaveCharacter(uint32_t dwAccountId, const CharacterRecord& in) {
    if (!m_bMySQL || !m_pDB) return;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    // ORIGINAL cq_user columns; the character carries the account name
    // (single-character servers: cq_user.name = accounts.name)
    std::string strName;
    if (m_pDB->Query("SELECT name FROM accounts WHERE id=" + std::to_string(dwAccountId)) &&
        !m_pDB->GetRows().empty())
        strName = m_pDB->GetRows()[0][0];
    if (strName.empty()) strName = "char_" + std::to_string(dwAccountId);
    const bool bExists =
        m_pDB->Query("SELECT id FROM cq_user WHERE account_id=" + std::to_string(dwAccountId) + " LIMIT 1") &&
        !m_pDB->GetRows().empty();
    std::string sql;
    if (bExists) {
        sql = "UPDATE cq_user SET name='" + m_pDB->Escape(strName) + "', level=" + std::to_string(in.dwLevel) +
              ", exp=" + std::to_string(in.dwExperience) +
              ", money=" + std::to_string(in.dwMoney) +
              ", money_saved=" + std::to_string(in.dwBank) +
              ", emoney=" + std::to_string(in.dwCp) +
              ", pk=" + std::to_string(in.dwPkPoints) +
              ", recordmap_id=" + std::to_string(in.dwMapId) +
              ", recordx=" + std::to_string(in.usX) +
              ", recordy=" + std::to_string(in.usY) +
              ", strength=" + std::to_string(in.dwStrength) +
              ", health=" + std::to_string(in.dwVitality) +
              ", additional_point=" + std::to_string(in.dwStatPoints) +
              ", metempsychosis=" + std::to_string(in.dwRebornCount) +
              ", last_logout=UNIX_TIMESTAMP() WHERE account_id=" + std::to_string(dwAccountId);
    } else {
        sql = "INSERT INTO cq_user (account_id, name, account, level, exp, money, money_saved, emoney, pk, "
              "recordmap_id, recordx, recordy, strength, health, additional_point, metempsychosis, "
              "first_login, last_login, auto_allot) VALUES (" +
            std::to_string(dwAccountId) + ", '" + m_pDB->Escape(strName) + "', '" + m_pDB->Escape(strName) + "', " +
            std::to_string(in.dwLevel) + ", " + std::to_string(in.dwExperience) + ", " +
            std::to_string(in.dwMoney) + ", " + std::to_string(in.dwBank) + ", " +
            std::to_string(in.dwCp) + ", " + std::to_string(in.dwPkPoints) + ", " +
            std::to_string(in.dwMapId) + ", " + std::to_string(in.usX) + ", " + std::to_string(in.usY) + ", " +
            std::to_string(in.dwStrength) + ", " + std::to_string(in.dwVitality) + ", " +
            std::to_string(in.dwStatPoints) + ", " + std::to_string(in.dwRebornCount) +
            ", UNIX_TIMESTAMP(), UNIX_TIMESTAMP(), 0)";
    }
    if (!m_pDB->Query(sql))
        printf("[DB] cq_user save failed: %s\n", m_pDB->GetError().c_str());
}

// ---------------- cq_market: the player market ----------------
std::vector<CAccountManager::MarketRow> CAccountManager::LoadMarket() {
    std::vector<MarketRow> out;
    if (!m_bMySQL || !m_pDB) return out;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT id, seller_name, item_type, item_name, sort, amount, plus, enchant, price "
                      "FROM cq_market WHERE is_sold=0 ORDER BY id DESC LIMIT 25"))
        return out;
    for (auto& row : m_pDB->GetRows()) {
        if (row.size() < 9) continue;
        MarketRow r;
        r.dwId       = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        r.strSeller  = row[1];
        r.dwType     = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        r.strName    = row[3];
        r.usSort     = (uint16_t)strtoul(row[4].c_str(), nullptr, 10);
        r.dwAmount   = (uint32_t)strtoul(row[5].c_str(), nullptr, 10);
        r.ucPlus     = (uint8_t)strtoul(row[6].c_str(), nullptr, 10);
        r.usEnchant  = (uint16_t)strtoul(row[7].c_str(), nullptr, 10);
        r.dwPrice    = strtoull(row[8].c_str(), nullptr, 10);
        out.push_back(std::move(r));
    }
    return out;
}

bool CAccountManager::SaveMarketListing(const std::string& strSeller, uint32_t dwType,
                                        const std::string& strName, uint16_t usSort,
                                        uint32_t dwAmount, uint8_t ucPlus, uint16_t usEnchant,
                                        uint64_t dwPrice, uint32_t& outId) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("INSERT INTO cq_market (seller_name, item_type, item_name, sort, amount, plus, enchant, price) "
                      "VALUES ('" + m_pDB->Escape(strSeller) + "', " + std::to_string(dwType) + ", '" +
                      m_pDB->Escape(strName) + "', " + std::to_string(usSort) + ", " +
                      std::to_string(dwAmount) + ", " + std::to_string(ucPlus) + ", " +
                      std::to_string(usEnchant) + ", " + std::to_string(dwPrice) + ")"))
        return false;
    if (!m_pDB->Query("SELECT LAST_INSERT_ID()") || m_pDB->GetRows().empty())
        return false;
    outId = (uint32_t)strtoul(m_pDB->GetRows()[0][0].c_str(), nullptr, 10);
    return true;
}

// atomic purchase: one UPDATE claims the row (is_sold 0 -> 1); if affected
// rows == 0 someone else bought it first. proceeds go straight to the
// seller's BANK (works while the seller is offline), mail confirms it.
bool CAccountManager::BuyMarketItem(uint32_t dwId, const std::string& strBuyer, MarketRow& out) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    // 1) claim the row
    if (!m_pDB->Query("UPDATE cq_market SET is_sold=1 WHERE id=" + std::to_string(dwId) +
                      " AND is_sold=0"))
        return false;
    if (m_pDB->GetAffectedRows() == 0)
        return false; // gone: raced or never existed
    // 2) fetch the claimed row
    if (!m_pDB->Query("SELECT seller_name, item_type, item_name, sort, amount, plus, enchant, price "
                      "FROM cq_market WHERE id=" + std::to_string(dwId)) ||
        m_pDB->GetRows().empty())
        return false;
    auto& row = m_pDB->GetRows()[0];
    if (row.size() < 8) return false;
    out.dwId = dwId; out.strSeller = row[0];
    out.dwType = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
    out.strName = row[2];
    out.usSort = (uint16_t)strtoul(row[3].c_str(), nullptr, 10);
    out.dwAmount = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
    out.ucPlus = (uint8_t)strtoul(row[5].c_str(), nullptr, 10);
    out.usEnchant = (uint16_t)strtoul(row[6].c_str(), nullptr, 10);
    out.dwPrice = strtoull(row[7].c_str(), nullptr, 10);
    // 3) credit the seller's bank by name (offline-safe)
    m_pDB->Query("UPDATE cq_user SET bank = bank + " + std::to_string(out.dwPrice) +
                 " WHERE name='" + m_pDB->Escape(out.strSeller) + "'");
    // 4) notify by in-game mail
    m_pDB->Query("INSERT INTO cq_mail (to_name, from_name, body) VALUES ('" +
                 m_pDB->Escape(out.strSeller) + "', 'MARKET', '" + m_pDB->Escape(strBuyer) +
                 " bought your " + m_pDB->Escape(out.strName) + " for " +
                 std::to_string(out.dwPrice) + " money (added to your bank).')");
    return true;
}

// ---------------- cq_item inventory persistence ----------------
bool CAccountManager::LoadItems(uint32_t dwAccountId, std::vector<ItemRow>& out) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT item_type, sort, amount, position, name, plus, durability FROM cq_item WHERE account_id=" +
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
        r.usDurability = (row.size() > 6) ? (uint16_t)strtoul(row[6].c_str(), nullptr, 10) : 1000;
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
        std::string sql = "INSERT INTO cq_item (account_id, item_type, sort, amount, position, name, plus, durability) VALUES (" +
            std::to_string(dwAccountId) + ", " + std::to_string(r.dwType) + ", " +
            std::to_string(r.usSort) + ", " + std::to_string(r.dwAmount) + ", " +
            std::to_string(r.dwPosition) + ", '" + m_pDB->Escape(r.strName) + "', " +
                std::to_string(r.ucPlus) + ", " + std::to_string(r.usDurability) + ")";
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

// persist the marriage state (called on /marry accept and /divorce)
bool CAccountManager::UpdateSpouse(uint32_t dwAccountId, const std::string& strSpouse) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    return m_pDB->Query("UPDATE cq_user SET spouse_name='" + m_pDB->Escape(strSpouse) +
                        "' WHERE account_id=" + std::to_string(dwAccountId));
}

// queue a mail for a player (delivered at their next login)
bool CAccountManager::SendMail(const std::string& strTo, const std::string& strFrom,
                               const std::string& strBody) {
    if (!m_bMySQL || !m_pDB) return false;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    return m_pDB->Query("INSERT INTO cq_mail (to_name, from_name, body) VALUES ('" +
                        m_pDB->Escape(strTo) + "','" + m_pDB->Escape(strFrom) + "','" +
                        m_pDB->Escape(strBody) + "')");
}

// fetch all unread mail addressed to this character
std::vector<CAccountManager::MailRow> CAccountManager::LoadUnreadMail(const std::string& strTo) {
    std::vector<MailRow> out;
    if (!m_bMySQL || !m_pDB) return out;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT id, from_name, body FROM cq_mail WHERE to_name='" +
                      m_pDB->Escape(strTo) + "' AND is_read=0 ORDER BY id"))
        return out;
    for (auto& row : m_pDB->GetRows()) {
        if (row.size() < 3) continue;
        MailRow m;
        m.dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        m.strFrom = row[1];
        m.strBody = row[2];
        out.push_back(std::move(m));
    }
    return out;
}

// mark the whole inbox read once delivered
void CAccountManager::MarkMailRead(const std::string& strTo) {
    if (!m_bMySQL || !m_pDB) return;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    m_pDB->Query("UPDATE cq_mail SET is_read=1 WHERE to_name='" + m_pDB->Escape(strTo) + "'");
}

// top-N ranking: whitelist the column, ORDER BY DESC, LIMIT n
std::vector<CAccountManager::TopRow> CAccountManager::GetTopPlayers(const std::string& strColumn, uint32_t n) {
    std::vector<TopRow> out;
    if (!m_bMySQL || !m_pDB) return out;
    if (strColumn != "level" && strColumn != "money" && strColumn != "pk_points")
        return out; // SQL-injection guard: whitelist only
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT name, " + strColumn + " FROM cq_user ORDER BY " +
                      strColumn + " DESC LIMIT " + std::to_string(n)))
        return out;
    for (auto& row : m_pDB->GetRows()) {
        if (row.size() < 2) continue;
        out.push_back({ row[0], strtoull(row[1].c_str(), nullptr, 10) });
    }
    return out;
}

// arena kill: upsert both fighters in one pass (INSERT .. ON DUPLICATE KEY)
void CAccountManager::RecordArenaKill(const std::string& strKiller, const std::string& strVictim) {
    if (!m_bMySQL || !m_pDB) return;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    m_pDB->Query("INSERT INTO cq_arena (name, kills) VALUES ('" + m_pDB->Escape(strKiller) +
                 "',1) ON DUPLICATE KEY UPDATE kills = kills + 1");
    m_pDB->Query("INSERT INTO cq_arena (name, deaths) VALUES ('" + m_pDB->Escape(strVictim) +
                 "',1) ON DUPLICATE KEY UPDATE deaths = deaths + 1");
}

// top arena fighters by kills
std::vector<CAccountManager::ArenaRow> CAccountManager::GetArenaLadder(uint32_t n) {
    std::vector<ArenaRow> out;
    if (!m_bMySQL || !m_pDB) return out;
    std::lock_guard<std::mutex> dbLock(m_dbMutex);
    if (!m_pDB->Query("SELECT name, kills, deaths FROM cq_arena ORDER BY kills DESC LIMIT " +
                      std::to_string(n)))
        return out;
    for (auto& row : m_pDB->GetRows()) {
        if (row.size() < 3) continue;
        out.push_back({ row[0],
                        (uint32_t)strtoul(row[1].c_str(), nullptr, 10),
                        (uint32_t)strtoul(row[2].c_str(), nullptr, 10) });
    }
    return out;
}
