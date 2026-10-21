#pragma once
#include <string>
#include <map>
#include <mutex>
#include <cstdint>

// Real account validation (v2 of the login flow).
// Storage format is one record per line in "accounts.dat":
//   <name> <accountId> <saltHex> <hashHex> <banned 0|1>
// hash = SHA-256(salt + password). The original 6159 flow routes through the
// C# AccountServer (1051 + AuthHash handoff); this store gives the C++ server
// standalone real validation now, and can sync from the MySQL `accounts`
// table when the AccountServer link is wired.

class CAccountManager {
public:
    enum class Result { Ok, NoSuchAccount, WrongPassword, Banned, Disabled };

    struct Account {
        std::string name;
        uint32_t dwId{0};
        std::string saltHex;
        std::string hashHex;
        bool bBanned{false};
    };

    static CAccountManager& Instance();

    void Load(const std::string& path = "accounts.dat");
    bool Save(const std::string& path = "accounts.dat");

    // validate an account+password pair; m_bAutoCreate registers first-time
    // accounts (dev mode) instead of rejecting them
    Result Validate(const std::string& name, const std::string& password, uint32_t& dwIdOut);
    bool CreateAccount(const std::string& name, const std::string& password, uint32_t& dwIdOut);
    void SetAutoCreate(bool b) { m_bAutoCreate = b; }

    static std::string Sha256Hex(const std::string& input);
    static std::string RandomSaltHex();

private:
    CAccountManager() = default;
    std::map<std::string, Account> m_byName; // key: lower-cased name
    std::mutex m_mutex;
    uint32_t m_dwNextId{ 10000 };
    bool m_bAutoCreate{ true };
    bool m_bLoaded{ false };
};
