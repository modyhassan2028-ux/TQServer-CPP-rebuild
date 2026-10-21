#include "Account.h"

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
