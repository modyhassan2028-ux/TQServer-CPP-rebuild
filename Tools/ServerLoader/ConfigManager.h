#pragma once
#include <string>
#include <vector>

namespace loader {
    class CConfigManager {
    public:
        // Automatically discovers base directories dynamically without relying on hardcoded absolute paths
        static std::string GetExecutableDirectory();
        static std::string ResolveServerDirectory(const std::string& preferred = "");
        static std::string ResolveAccountDirectory(const std::string& preferred = "");
        static std::string DetectMysqlCliPath();

        // Self-reliance: Ensures all required INI configs exist; auto-creates from embedded templates if missing
        static bool EnsureAllConfigsExist(const std::string& serverDir, const std::string& accountDir, const std::string& defaultIp = "127.0.0.1");

        // Single-click IP change across all server components
        static bool ApplyNetworkIP(const std::string& serverDir, const std::string& accountDir,
                                   const std::string& newIP, uint16_t gamePort = 5816, uint16_t authPort = 9960,
                                   const std::string& dbHost = "127.0.0.1");

        // Reads the current configured IP from shell.ini / config.ini
        static std::string ReadCurrentServerIP(const std::string& serverDir);

        // Generates Server.dat text / snippet for game client
        static std::string GenerateClientConnectionSnippet(const std::string& serverName, const std::string& ip, uint16_t authPort = 9960);
    };
}
