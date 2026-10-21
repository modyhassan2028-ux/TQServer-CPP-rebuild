#include "ConfigManager.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

namespace loader {

    static const char* DEFAULT_SHELL_INI = 
R"(; Conquer Online Game Server Configuration
; Auto-Generated Self-Reliant Configuration

[System]
MAPGROUP_SIZE = 1
MSGCOUNT_OUT = 130

[Database]
DB_IP = 127.0.0.1
DB_USER = root
DB_PW = 12345678
DB_DB = cq1

[AccountServer]
ACCOUNT_IP = 127.0.0.1
ACCOUNT_PORT = 9870
SERVERNAME = xbox
LOGINNAME = root
PASSWORD = 12345678
MAXLOGINTABLESIZE = 1500
LOGINOVERTIMESECS = 120

[InternetPort]
CURRENT_PORTID = 0
PORT_SIZE = 5
MASTER_IP = 127.0.0.1
MASTER_PORT = 8653

[Language]
StringFile = ini\En_Res.ini
ActionStringFile = ini\action_Res.ini

[CheatingMonitor]
ListenPort = 9150
IPNum = 0

[CrossClient]
Enable = 0
CrossServerPort = 5819
CrossServerIP = 127.0.0.1

[ChangeServerClient]
IsConnectChangeServer = 0
ChangeServerPort = 5821
ChangeServerIP = 127.0.0.1
)";

    static const char* DEFAULT_CONFIG_INI = 
R"(; Game Server Port & Network Config
; Auto-Generated Self-Reliant Configuration

[System]

[GameServer]
GAMESERVER_IP = 127.0.0.1
GAMESERVER_PORT = 5816
SND_SIZE = 1048576
RCV_SIZE = 32000
MaxNpcPerTimer = 120

[Database]
DBServer = 127.0.0.1
LoginName = root
Password = 12345678
DBName = cq1
)";

    static const char* DEFAULT_SERVER_GAME_CONFIG_INI = 
R"([SlotMachine]
ExpRewardTime = 300
PrizeRewardMultiply = 300

[Items]
AllowRedeemEquip = false

[Upgrade]
MeteorFirstSocket = 1200
MeteorSecondSocket = 2400
QualitySocket = 300

[Player]
ForceMerchant = true

[Security]
BlowfishKey = C238xs65pjy7HU9Q
)";

    static const char* DEFAULT_ACCOUNT_CONFIG_INI = 
R"([AccountServer]
AuthPort = 9960
LinkPort = 9870
GMOnly = false
ClientLimit = 40

[AuthDatabase]
Port = 3306
Host = localhost
User = root
Pass = 12345678
Name = cq1
OnlineColumn = online_us

[GameDatabase]
Port = 3306
Host = localhost
User = root
Pass = 12345678
Name = cq1
DefaultVIP = 4
)";

    static const char* DEFAULT_CROSSCONN_INI = 
R"([Client-IP-Config]
Amount = 2
ClientIP0 = 127.0.0.1
ClientIPMASK0 = 
ClientIP1 = 127.0.0.1
ClientIPMASK1 = 
)";

    static bool FileExists(const std::string& path) {
        DWORD dwAttrib = GetFileAttributesA(path.c_str());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    static bool DirectoryExists(const std::string& path) {
        DWORD dwAttrib = GetFileAttributesA(path.c_str());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    static void WriteFileIfMissing(const std::string& path, const char* content) {
        if (!FileExists(path)) {
            std::ofstream out(path, std::ios::binary);
            if (out.is_open()) {
                out << content;
                out.close();
            }
        }
    }

    std::string CConfigManager::GetExecutableDirectory() {
        char buf[MAX_PATH]{};
        GetModuleFileNameA(nullptr, buf, MAX_PATH);
        PathRemoveFileSpecA(buf);
        return std::string(buf);
    }

    std::string CConfigManager::ResolveServerDirectory(const std::string& preferred) {
        if (!preferred.empty() && DirectoryExists(preferred) && FileExists(preferred + "\\MsgServer.exe")) {
            return preferred;
        }

        std::string exeDir = GetExecutableDirectory();
        if (FileExists(exeDir + "\\MsgServer.exe")) {
            return exeDir;
        }

        // Relative checks:
        std::vector<std::string> candidates = {
            exeDir + "\\..\\Source - Copy",
            exeDir + "\\Source - Copy",
            exeDir + "\\..\\Source",
            exeDir + "\\Source",
            "G:\\Malfat conquer\\RealCo\\Source - Copy",
            "G:\\Malfat conquer\\RealCo\\Source"
        };

        for (const auto& path : candidates) {
            char canonical[MAX_PATH]{};
            if (PathCanonicalizeA(canonical, path.c_str())) {
                if (DirectoryExists(canonical) && FileExists(std::string(canonical) + "\\MsgServer.exe")) {
                    return std::string(canonical);
                }
            }
        }

        return exeDir;
    }

    std::string CConfigManager::ResolveAccountDirectory(const std::string& preferred) {
        if (!preferred.empty() && DirectoryExists(preferred) && FileExists(preferred + "\\AccountServerBinary2015.exe")) {
            return preferred;
        }

        std::string exeDir = GetExecutableDirectory();
        if (FileExists(exeDir + "\\AccountServerBinary2015.exe")) {
            return exeDir;
        }

        std::vector<std::string> candidates = {
            exeDir + "\\AccountServer",
            exeDir + "\\..\\AccountServer",
            "G:\\Malfat conquer\\RealCo\\AccountServer"
        };

        for (const auto& path : candidates) {
            char canonical[MAX_PATH]{};
            if (PathCanonicalizeA(canonical, path.c_str())) {
                if (DirectoryExists(canonical) && FileExists(std::string(canonical) + "\\AccountServerBinary2015.exe")) {
                    return std::string(canonical);
                }
            }
        }

        return exeDir;
    }

    std::string CConfigManager::DetectMysqlCliPath() {
        std::vector<std::string> searchPaths = {
            "C:\\AppServ\\MySQL\\bin\\mysql.exe",
            "C:\\Program Files\\MySQL\\MySQL Server 8.0\\bin\\mysql.exe",
            "C:\\Program Files\\MySQL\\MySQL Server 5.7\\bin\\mysql.exe",
            "C:\\Program Files (x86)\\MySQL\\MySQL Server 5.7\\bin\\mysql.exe",
            "C:\\xampp\\mysql\\bin\\mysql.exe",
            "C:\\wamp64\\bin\\mysql\\mysql5.7.36\\bin\\mysql.exe",
            "D:\\AppServ\\MySQL\\bin\\mysql.exe"
        };

        for (const auto& p : searchPaths) {
            if (FileExists(p)) {
                return p;
            }
        }

        // Check if mysql is on system PATH
        char buf[MAX_PATH]{};
        if (SearchPathA(nullptr, "mysql.exe", nullptr, MAX_PATH, buf, nullptr) > 0) {
            return std::string(buf);
        }

        return "C:\\AppServ\\MySQL\\bin\\mysql.exe";
    }

    bool CConfigManager::EnsureAllConfigsExist(const std::string& serverDir, const std::string& accountDir, const std::string& defaultIp) {
        // Ensure serverDir INIs
        WriteFileIfMissing(serverDir + "\\shell.ini", DEFAULT_SHELL_INI);
        WriteFileIfMissing(serverDir + "\\config.ini", DEFAULT_CONFIG_INI);
        WriteFileIfMissing(serverDir + "\\ServerGameConfig.ini", DEFAULT_SERVER_GAME_CONFIG_INI);
        WriteFileIfMissing(serverDir + "\\crossconn.ini", DEFAULT_CROSSCONN_INI);

        // Ensure accountDir INIs
        WriteFileIfMissing(accountDir + "\\Config.ini", DEFAULT_ACCOUNT_CONFIG_INI);

        return true;
    }

    bool CConfigManager::ApplyNetworkIP(const std::string& serverDir, const std::string& accountDir,
                                       const std::string& newIP, uint16_t gamePort, uint16_t authPort,
                                       const std::string& dbHost) {
        if (newIP.empty()) return false;

        EnsureAllConfigsExist(serverDir, accountDir, newIP);

        // 1. shell.ini
        std::string shellIni = serverDir + "\\shell.ini";
        WritePrivateProfileStringA("AccountServer", "ACCOUNT_IP", newIP.c_str(), shellIni.c_str());
        WritePrivateProfileStringA("CrossClient", "CrossServerIP", newIP.c_str(), shellIni.c_str());
        WritePrivateProfileStringA("ChangeServerClient", "ChangeServerIP", newIP.c_str(), shellIni.c_str());
        if (!dbHost.empty()) {
            WritePrivateProfileStringA("Database", "DB_IP", dbHost.c_str(), shellIni.c_str());
        }

        // 2. config.ini
        std::string configIni = serverDir + "\\config.ini";
        WritePrivateProfileStringA("GameServer", "GAMESERVER_IP", newIP.c_str(), configIni.c_str());
        WritePrivateProfileStringA("GameServer", "GAMESERVER_PORT", std::to_string(gamePort).c_str(), configIni.c_str());
        if (!dbHost.empty()) {
            WritePrivateProfileStringA("Database", "DBServer", dbHost.c_str(), configIni.c_str());
        }

        // 3. crossconn.ini
        std::string crossIni = serverDir + "\\crossconn.ini";
        WritePrivateProfileStringA("Client-IP-Config", "ClientIP1", newIP.c_str(), crossIni.c_str());

        // 4. AccountServer Config.ini
        std::string accIni = accountDir + "\\Config.ini";
        WritePrivateProfileStringA("AccountServer", "AuthPort", std::to_string(authPort).c_str(), accIni.c_str());
        if (!dbHost.empty()) {
            WritePrivateProfileStringA("AuthDatabase", "Host", dbHost.c_str(), accIni.c_str());
            WritePrivateProfileStringA("GameDatabase", "Host", dbHost.c_str(), accIni.c_str());
        }

        return true;
    }

    std::string CConfigManager::ReadCurrentServerIP(const std::string& serverDir) {
        char buf[128]{};
        std::string configIni = serverDir + "\\config.ini";
        GetPrivateProfileStringA("GameServer", "GAMESERVER_IP", "127.0.0.1", buf, sizeof(buf) - 1, configIni.c_str());
        return std::string(buf);
    }

    std::string CConfigManager::GenerateClientConnectionSnippet(const std::string& serverName, const std::string& ip, uint16_t authPort) {
        std::ostringstream ss;
        ss << "[Group0]\r\n"
           << "Group=Conquer\r\n"
           << "Server0=" << (serverName.empty() ? "ConquerOnline" : serverName) << " " << ip << " " << authPort << " 0\r\n";
        return ss.str();
    }
}
