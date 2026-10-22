#pragma once
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <cstdint>
#include <memory>
#include <mutex>

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

    // character persistence (cq_user), MySQL mode only
    struct CharacterRecord {
        uint32_t dwLevel{1};
        uint64_t dwExperience{0};
        uint64_t dwMoney{100000}, dwCp{5000}, dwBank{0};
        uint32_t dwPkPoints{0};
        uint32_t dwMapId{1002};
        uint16_t usX{315}, usY{275};
    };
    // inventory persistence (cq_item), MySQL mode only
    // runtime ids regenerate on load (MakeItemId) - rows store types/amounts
    struct ItemRow { uint32_t dwType; uint16_t usSort; uint32_t dwAmount; uint32_t dwPosition; std::string strName; };
    bool LoadItems(uint32_t dwAccountId, std::vector<ItemRow>& out);
    void SaveItems(uint32_t dwAccountId, const std::vector<ItemRow>& items);

    // returns true if a saved character was found and loaded into 'out'
    bool LoadCharacter(uint32_t dwAccountId, CharacterRecord& out);
    void SaveCharacter(uint32_t dwAccountId, const CharacterRecord& in);

    // connect to MySQL (cq_account/cq_user); returns false -> flat-file mode
    bool TryMySQL(const std::string& host, uint16_t port, const std::string& user,
                   const std::string& password, const std::string& database);
    bool IsMySQLMode() const { return m_bMySQL; }
    class CMySQLClient* GetDB() { return m_pDB.get(); }

    static std::string Sha256Hex(const std::string& input);
    static std::string RandomSaltHex();

private:
    CAccountManager() = default;
    std::map<std::string, Account> m_byName; // key: lower-cased name
    std::mutex m_mutex;
    uint32_t m_dwNextId{ 10000 };
    bool m_bAutoCreate{ true };
    bool m_bLoaded{ false };
    // MySQL persistence (falls back to accounts.dat when unreachable)
    std::unique_ptr<class CMySQLClient> m_pDB;
    bool m_bMySQL{ false };
    std::mutex m_dbMutex;
};
