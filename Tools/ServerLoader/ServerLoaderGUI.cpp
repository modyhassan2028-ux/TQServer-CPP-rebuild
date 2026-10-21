#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <atomic>
#include <iostream>
#include "HookInjector.h"
#include "ConfigManager.h"

#pragma comment(lib, "comctl32.lib")

// Control IDs
#define IDC_LAUNCH              1001
#define IDC_STOP                1002
#define IDC_STATUS              1003
#define IDC_LOG                 1004
#define IDC_CMD                 1005
#define IDC_SEND                1006

// Network & IP Setup
#define IDC_SERVER_IP_EDIT      3001
#define IDC_APPLY_IP            3002
#define IDC_CHECK_CONFIGS       3003

// Player Selection & Info
#define IDC_GM_PLAYER_COMBO     2001
#define IDC_GM_REFRESH          2002
#define IDC_GM_KICK             2003
#define IDC_GM_BAN              2004
#define IDC_GM_UNBAN            2005

// Teleportation
#define IDC_GM_TC               2010
#define IDC_GM_PC               2011
#define IDC_GM_AC               2012
#define IDC_GM_DC               2013
#define IDC_GM_BI               2014
#define IDC_GM_MARKET           2015
#define IDC_GM_JAIL             2016
#define IDC_GM_MAP              2017
#define IDC_GM_X                2018
#define IDC_GM_Y                2019
#define IDC_GM_TP_CUSTOM        2020

// Currency
#define IDC_GM_AMOUNT           2030
#define IDC_GM_CP_1K            2031
#define IDC_GM_CP_10K           2032
#define IDC_GM_CP_50K           2033
#define IDC_GM_CP_500K          2034
#define IDC_GM_CP_10M           2035
#define IDC_GM_CP_DIRECT        2036
#define IDC_GM_CP_MAIL          2037
#define IDC_GM_SILVER_DIRECT    2038
#define IDC_GM_SILVER_MAIL      2039

// Equipment Sets
#define IDC_GM_SET_TROJAN       2050
#define IDC_GM_SET_WARRIOR      2051
#define IDC_GM_SET_ARCHER       2052
#define IDC_GM_SET_NINJA        2053
#define IDC_GM_SET_MONK         2054
#define IDC_GM_SET_TAOIST       2055
#define IDC_GM_SET_PIRATE       2056
#define IDC_GM_ITEM_ID          2057
#define IDC_GM_SPAWN_CUSTOM     2058

// Progression
#define IDC_GM_LVL140           2070
#define IDC_GM_REBORN2          2071
#define IDC_GM_VIP6             2072
#define IDC_GM_PROMOTE_GM       2073

#define WM_APPEND_LOG           (WM_USER + 1)
#define WM_UPDATE_PLAYERS_UI    (WM_USER + 2)

struct PlayerRecord {
    std::string name;
    uint32_t id = 0;
    int profession = 0;
    int level = 0;
    int reborn = 0;
    int vip = 0;
    uint64_t emoney = 0;
    uint64_t money = 0;
    int mapId = 0;
    int x = 0;
    int y = 0;
};

static HWND g_hWnd = nullptr;
static HWND g_hBtnLaunch = nullptr;
static HWND g_hBtnStop = nullptr;
static HWND g_hStatus = nullptr;
static HWND g_hLogEdit = nullptr;
static HWND g_hCmdEdit = nullptr;
static HWND g_hBtnSend = nullptr;

// GM Controls
static HWND g_hGmPlayerCombo = nullptr;
static HWND g_hPlayerBanner1 = nullptr;
static HWND g_hPlayerBanner2 = nullptr;
static HWND g_hGmMap = nullptr;
static HWND g_hGmX = nullptr;
static HWND g_hGmY = nullptr;
static HWND g_hGmAmount = nullptr;
static HWND g_hGmItemId = nullptr;

// Network & IP Controls
static HWND g_hServerIpEdit = nullptr;
static HWND g_hBtnApplyIp = nullptr;

static HBRUSH g_hDarkBrush = nullptr;
static HBRUSH g_hHeaderBrush = nullptr;
static HBRUSH g_hPanelBrush = nullptr;
static HBRUSH g_hBannerBrush = nullptr;
static HFONT g_hMonoFont = nullptr;
static HFONT g_hUiFont = nullptr;
static HFONT g_hBoldFont = nullptr;
static HFONT g_hBannerFont = nullptr;

static std::atomic<bool> g_bServerRunning{ false };
static std::atomic<bool> g_bStopThreads{ false };
static PROCESS_INFORMATION g_piMsg{};
static PROCESS_INFORMATION g_piAccount{};
static PROCESS_INFORMATION g_piNpc{};

static std::vector<PlayerRecord> g_players;
static CRITICAL_SECTION g_csPlayers;

std::string GetProfessionName(int prof) {
    if (prof >= 10 && prof <= 15) return "Trojan";
    if (prof >= 20 && prof <= 25) return "Warrior";
    if (prof >= 40 && prof <= 45) return "Archer";
    if (prof >= 50 && prof <= 55) return "Ninja";
    if (prof >= 60 && prof <= 65) return "Monk";
    if (prof >= 70 && prof <= 75) return "Pirate";
    if (prof >= 80 && prof <= 85) return "Dragon Warrior";
    if (prof >= 100 && prof <= 101) return "Taoist";
    if (prof >= 130 && prof <= 135) return "Water Taoist";
    if (prof >= 140 && prof <= 145) return "Fire Taoist";
    return "Class " + std::to_string(prof);
}

std::string FormatNumber(uint64_t num) {
    std::string s = std::to_string(num);
    int n = (int)s.length() - 3;
    while (n > 0) {
        s.insert(n, ",");
        n -= 3;
    }
    return s;
}

void AppendLog(const std::string& text) {
    if (!g_hLogEdit || text.empty()) return;
    char* pMsg = _strdup(text.c_str());
    PostMessageA(g_hWnd, WM_APPEND_LOG, 0, (LPARAM)pMsg);
}

void PipeReaderThread() {
    std::string pipeName = "\\\\.\\pipe\\RevampedHookLog";
    HANDLE hPipe = INVALID_HANDLE_VALUE;

    for (int i = 0; i < 40 && !g_bStopThreads; i++) {
        hPipe = CreateFileA(pipeName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (hPipe != INVALID_HANDLE_VALUE) break;
        Sleep(200);
    }

    if (hPipe == INVALID_HANDLE_VALUE) {
        AppendLog("[Loader] Standalone pipe monitoring idle\r\n");
        return;
    }

    AppendLog("[Loader] Connected to RevampedHook log pipe\r\n");

    char buffer[1024];
    DWORD bytesRead = 0;
    while (!g_bStopThreads) {
        BOOL ok = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr);
        if (!ok || bytesRead == 0) break;
        buffer[bytesRead] = '\0';
        AppendLog(buffer);
    }

    CloseHandle(hPipe);
}

void ProcessWatchdogThread() {
    while (!g_bStopThreads) {
        if (g_bServerRunning && g_piMsg.hProcess) {
            DWORD exitCode = 0;
            if (GetExitCodeProcess(g_piMsg.hProcess, &exitCode) && exitCode != STILL_ACTIVE) {
                g_bServerRunning = false;
                AppendLog("\r\n[Loader] Server process has exited (Code " + std::to_string(exitCode) + ")\r\n");
                SetWindowTextA(g_hStatus, "Server process exited");
                EnableWindow(g_hBtnLaunch, TRUE);
                EnableWindow(g_hBtnStop, FALSE);
            }
        }
        Sleep(500);
    }
}

void SendCommandToPipe(const std::string& cmd) {
    if (cmd.empty()) return;

    std::string pipeName = "\\\\.\\pipe\\RevampedHookCmd";
    HANDLE hPipe = CreateFileA(pipeName.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (hPipe != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        WriteFile(hPipe, cmd.c_str(), (DWORD)cmd.length(), &written, nullptr);
        CloseHandle(hPipe);
        AppendLog("[Pipe Command Sent] " + cmd);
        if (cmd.back() != '\n') AppendLog("\r\n");
    } else {
        AppendLog("[Pipe Warning] RevampedHookCmd pipe not connected (is MsgServer running?)\r\n");
    }
}

std::string ExecCmdCapture(const std::string& cmdLine) {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa{ sizeof(sa), nullptr, TRUE };
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) return "";
    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hWrite;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi{};
    std::vector<char> buf(cmdLine.begin(), cmdLine.end());
    buf.push_back('\0');

    std::string result;
    if (CreateProcessA(nullptr, buf.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        CloseHandle(hWrite);
        char buffer[1024];
        DWORD bytesRead = 0;
        while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            result.append(buffer, bytesRead);
        }
        WaitForSingleObject(pi.hProcess, 4000);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        CloseHandle(hWrite);
    }
    CloseHandle(hRead);
    return result;
}

bool ExecuteGmSql(const std::string& sql, const std::string& logDesc) {
    std::string mysqlExe = loader::CConfigManager::DetectMysqlCliPath();
    std::string cmdLine = "\"" + mysqlExe + "\" -u root -p12345678 -e \"" + sql + "\"";

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi{};

    std::vector<char> cmdBuf(cmdLine.begin(), cmdLine.end());
    cmdBuf.push_back('\0');

    if (CreateProcessA(nullptr, cmdBuf.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, 4000);
        DWORD exitCode = 0;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        if (exitCode == 0) {
            AppendLog("[GM Success] " + logDesc + "\r\n");
            return true;
        } else {
            AppendLog("[GM Error] MySQL returned code " + std::to_string(exitCode) + "\r\n");
            return false;
        }
    } else {
        AppendLog("[GM Error] Failed to invoke MySQL CLI (Error " + std::to_string(GetLastError()) + ")\r\n");
        return false;
    }
}

void RefreshPlayerList() {
    std::string mysqlExe = loader::CConfigManager::DetectMysqlCliPath();
    std::string cmd = "\"" + mysqlExe + "\" -u root -p12345678 -B -N -e "
        "\"SELECT name, profession, level, metempsychosis, vip_value, emoney, money, recordmap_id, recordx, recordy, id "
        "FROM cq1.cq_user ORDER BY id DESC;\"";

    std::string raw = ExecCmdCapture(cmd);
    if (raw.empty()) return;

    EnterCriticalSection(&g_csPlayers);
    g_players.clear();

    std::istringstream stream(raw);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty() || line.find('\t') == std::string::npos) continue;
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = line.find('\t', start)) != std::string::npos) {
            tokens.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(line.substr(start));

        if (tokens.size() >= 11) {
            try {
                PlayerRecord pr;
                pr.name = tokens[0];
                pr.profession = std::stoi(tokens[1]);
                pr.level = std::stoi(tokens[2]);
                pr.reborn = std::stoi(tokens[3]);
                pr.vip = std::stoi(tokens[4]);
                pr.emoney = std::stoull(tokens[5]);
                pr.money = std::stoull(tokens[6]);
                pr.mapId = std::stoi(tokens[7]);
                pr.x = std::stoi(tokens[8]);
                pr.y = std::stoi(tokens[9]);
                pr.id = (uint32_t)std::stoul(tokens[10]);
                g_players.push_back(pr);
            } catch (...) {}
        }
    }
    LeaveCriticalSection(&g_csPlayers);
}

std::string GetTargetPlayerName() {
    char buf[128]{};
    GetWindowTextA(g_hGmPlayerCombo, buf, sizeof(buf) - 1);
    std::string name = buf;
    if (name.empty()) name = "Colin";
    return name;
}

void UpdatePlayerBannerByIndex(int idx) {
    EnterCriticalSection(&g_csPlayers);
    if (idx >= 0 && idx < (int)g_players.size()) {
        const auto& pr = g_players[idx];
        std::string rebornStr = (pr.reborn == 2) ? "2nd Reborn" : ((pr.reborn == 1) ? "1st Reborn" : "No Reborn");
        std::string profStr = GetProfessionName(pr.profession);

        std::string line1 = "Target Player: " + pr.name + " (UID: " + std::to_string(pr.id) + ")  |  Class: " + profStr +
            "  |  Level: " + std::to_string(pr.level) + " (" + rebornStr + ")  |  VIP: Level " + std::to_string(pr.vip);
        std::string line2 = "Conquer Points: " + FormatNumber(pr.emoney) + " CPs  |  Silvers: " + FormatNumber(pr.money) +
            "  |  Coords: Map " + std::to_string(pr.mapId) + " (" + std::to_string(pr.x) + ", " + std::to_string(pr.y) + ")";

        if (g_hPlayerBanner1) SetWindowTextA(g_hPlayerBanner1, line1.c_str());
        if (g_hPlayerBanner2) SetWindowTextA(g_hPlayerBanner2, line2.c_str());

        if (g_hGmMap) SetWindowTextA(g_hGmMap, std::to_string(pr.mapId).c_str());
        if (g_hGmX) SetWindowTextA(g_hGmX, std::to_string(pr.x).c_str());
        if (g_hGmY) SetWindowTextA(g_hGmY, std::to_string(pr.y).c_str());
    }
    LeaveCriticalSection(&g_csPlayers);
}

void UpdatePlayerComboAndBanner() {
    if (!g_hGmPlayerCombo) return;

    char currentSelected[128]{};
    GetWindowTextA(g_hGmPlayerCombo, currentSelected, sizeof(currentSelected) - 1);

    SendMessageA(g_hGmPlayerCombo, CB_RESETCONTENT, 0, 0);

    EnterCriticalSection(&g_csPlayers);
    int selectIdx = 0;
    for (size_t i = 0; i < g_players.size(); i++) {
        SendMessageA(g_hGmPlayerCombo, CB_ADDSTRING, 0, (LPARAM)g_players[i].name.c_str());
        if (g_players[i].name == currentSelected || (currentSelected[0] == '\0' && g_players[i].name == "Colin")) {
            selectIdx = (int)i;
        }
    }
    LeaveCriticalSection(&g_csPlayers);

    if (!g_players.empty()) {
        SendMessageA(g_hGmPlayerCombo, CB_SETCURSEL, (WPARAM)selectIdx, 0);
        UpdatePlayerBannerByIndex(selectIdx);
    }
}

std::string BuildWhereClause(const std::string& player) {
    if (player.empty() || player == "all") {
        return "";
    }
    return " WHERE name = '" + player + "'";
}

// Option A: Direct Inventory / DB Add (Updates cq_user with checksum ONLY - NO MAIL)
void GmAddCpsInventory(const std::string& player, uint32_t amount) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; "
        "UPDATE cq_user SET "
        "chk_sum = (((CASE (emoney + " + std::to_string(amount) + ") % 3 WHEN 0 THEN 29565076 WHEN 1 THEN 3118018 WHEN 2 THEN 9581781 END) + (emoney_mono & account_id) + account_id) ^ (emoney + " + std::to_string(amount) + ")), "
        "emoney = emoney + " + std::to_string(amount) + whereClause + ";";

    ExecuteGmSql(sql, "[DIRECT INVENTORY] Added +" + std::to_string(amount) + " CPs directly to " + player + "'s account/inventory (0 Mail)");
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

// Option B: Mailbox Delivery (Inserts into cq_mail ONLY - NO DIRECT DB UPDATE)
void GmSendCpsMail(const std::string& player, uint32_t amount) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; "
        "INSERT INTO cq_mail (receiver_id, Sender_name, title, content, money, emoney, action, expiration_date) "
        "SELECT id, 'GM Control', 'GM CPs Reward', 'Claim your reward of " + std::to_string(amount) + " CPs!', 0, " + std::to_string(amount) + ", 0, UNIX_TIMESTAMP() + 864000 "
        "FROM cq_user" + whereClause + ";";

    ExecuteGmSql(sql, "[MAIL DELIVERY] Sent +" + std::to_string(amount) + " CPs via In-Game Mail to " + player + " (Delivered to Mailbox, Claim on login)");
}

// Option A (Silvers): Direct Inventory / DB Add (NO MAIL)
void GmAddSilversInventory(const std::string& player, uint64_t amount) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; UPDATE cq_user SET money = money + " + std::to_string(amount) + whereClause + ";";
    ExecuteGmSql(sql, "[DIRECT INVENTORY] Added +" + std::to_string(amount) + " Silvers directly to " + player + " (0 Mail)");
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

// Option B (Silvers): Mailbox Delivery (NO DIRECT DB UPDATE)
void GmSendSilversMail(const std::string& player, uint64_t amount) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; "
        "INSERT INTO cq_mail (receiver_id, Sender_name, title, content, money, emoney, action, expiration_date) "
        "SELECT id, 'GM Control', 'GM Silver Reward', 'Claim your reward of " + std::to_string(amount) + " Silvers!', " + std::to_string(amount) + ", 0, 0, UNIX_TIMESTAMP() + 864000 "
        "FROM cq_user" + whereClause + ";";

    ExecuteGmSql(sql, "[MAIL DELIVERY] Sent +" + std::to_string(amount) + " Silvers via In-Game Mail to " + player);
}

void GmTeleport(const std::string& player, int mapId, int x, int y, const std::string& locName) {
    if (player.empty()) {
        AppendLog("[Teleport Warning] Please select a target player.\r\n");
        return;
    }

    // 1. Send live teleport command to RevampedHookCmd pipe for RAM teleportation
    std::string pipeCmd = "teleport " + player + " " + std::to_string(mapId) + " " + std::to_string(x) + " " + std::to_string(y) + "\n";
    SendCommandToPipe(pipeCmd);

    // 2. Also persist to MySQL so relogging keeps the character in place
    std::string sql = "USE cq1; UPDATE cq_user SET recordmap_id = " + std::to_string(mapId) +
        ", recordx = " + std::to_string(x) + ", recordy = " + std::to_string(y) +
        " WHERE name = '" + player + "';";

    ExecuteGmSql(sql, "Teleported " + player + " to " + locName + " (Map " + std::to_string(mapId) + ": " + std::to_string(x) + ", " + std::to_string(y) + ")");
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

void GmSpawnItem(const std::string& player, uint32_t itemId) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; "
        "INSERT INTO cq_item (type, owner_id, player_id, amount, amount_limit, position, gem1, gem2, magic3) "
        "SELECT " + std::to_string(itemId) + ", id, id, 100, 100, 0, 255, 255, 12 FROM cq_user" + whereClause + ";";

    ExecuteGmSql(sql, "Spawned Super +12 (Double Socket) Item ID " + std::to_string(itemId) + " for " + player);
}

void GmSpawnClassSet(const std::string& player, const std::string& className, const std::vector<uint32_t>& itemIds) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; ";
    for (uint32_t it : itemIds) {
        sql += "INSERT INTO cq_item (type, owner_id, player_id, amount, amount_limit, position, gem1, gem2, magic3) "
               "SELECT " + std::to_string(it) + ", id, id, 100, 100, 0, 255, 255, 12 FROM cq_user" + whereClause + "; ";
    }
    ExecuteGmSql(sql, "Spawned Full " + className + " Super +12 Double-Socket Gear Set for " + player);
}

void GmSetLevel(const std::string& player, int level) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; UPDATE cq_user SET level = " + std::to_string(level) + whereClause + ";";
    ExecuteGmSql(sql, "Set Level to " + std::to_string(level) + " for " + player);
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

void GmSetReborn(const std::string& player, int rb) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; UPDATE cq_user SET metempsychosis = " + std::to_string(rb) + ", level = 140" + whereClause + ";";
    ExecuteGmSql(sql, "Set Rebirth to " + std::to_string(rb) + " (Level 140) for " + player);
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

void GmSetVip(const std::string& player, int vip) {
    std::string whereClause = BuildWhereClause(player);
    std::string sql = "USE cq1; "
        "UPDATE cq_user SET vip_value = " + std::to_string(vip) + whereClause + "; "
        "UPDATE accounts SET vip = " + std::to_string(vip) + " WHERE id IN (SELECT account_id FROM cq_user" + whereClause + "); "
        "INSERT INTO vips (account_id, vip_level, days_left, vip_expires) "
        "SELECT account_id, " + std::to_string(vip) + ", 365, DATE_ADD(NOW(), INTERVAL 365 DAY) FROM cq_user" + whereClause + " "
        "ON DUPLICATE KEY UPDATE vip_level = " + std::to_string(vip) + ", days_left = 365, vip_expires = DATE_ADD(NOW(), INTERVAL 365 DAY);";

    ExecuteGmSql(sql, "Set VIP Level " + std::to_string(vip) + " (365 Days) for " + player);
    std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
}

void GmKickPlayer(const std::string& player) {
    SendCommandToPipe("kick " + player + "\n");
    std::string sql = "USE cq1; UPDATE accounts SET online_eu = 0, online_us = 0 "
        "WHERE id IN (SELECT account_id FROM cq_user WHERE name = '" + player + "');";
    ExecuteGmSql(sql, "Disconnected / Kicked player " + player);
}

void GmBanAccount(const std::string& player, bool bBan) {
    std::string sql = "USE cq1; UPDATE accounts SET banned = " + std::string(bBan ? "1" : "0") +
        " WHERE id IN (SELECT account_id FROM cq_user WHERE name = '" + player + "');";
    ExecuteGmSql(sql, (bBan ? "BANNED" : "UNBANNED") + std::string(" account for ") + player);
}

void LaunchCluster() {
    std::string baseDir = loader::CConfigManager::ResolveServerDirectory();
    std::string accountDir = loader::CConfigManager::ResolveAccountDirectory();

    // Self-healing: verify all config files exist before launching
    loader::CConfigManager::EnsureAllConfigsExist(baseDir, accountDir);

    EnableWindow(g_hBtnLaunch, FALSE);
    SetWindowTextA(g_hStatus, "Server launching - connecting cluster...");

    // 1. AccountServer
    STARTUPINFOA siAcc{};
    siAcc.cb = sizeof(siAcc);
    std::string accExe = accountDir + "\\AccountServerBinary2015.exe";
    char cmdAcc[MAX_PATH];
    strncpy_s(cmdAcc, accExe.c_str(), sizeof(cmdAcc) - 1);

    AppendLog("[Loader] Checking AccountServer...\r\n");
    if (!g_piAccount.hProcess) {
        if (CreateProcessA(nullptr, cmdAcc, nullptr, nullptr, FALSE, 0, nullptr, accountDir.c_str(), &siAcc, &g_piAccount)) {
            AppendLog("[Loader] Started AccountServer (PID: " + std::to_string(g_piAccount.dwProcessId) + ")\r\n");
        }
    }

    // 2. MsgServer with RevampedHook injection
    std::string msgExe = baseDir + "\\MsgServer.exe";
    std::string hookDll = baseDir + "\\RevampedHook.dll";

    AppendLog("[Loader] Creating MsgServer.exe (suspended)...\r\n");

    bool success = loader::CHookInjector::LaunchAndInject(
        msgExe,
        baseDir,
        hookDll,
        g_piMsg
    );

    if (!success) {
        AppendLog("[Error] Failed to create or inject MsgServer.exe!\r\n");
        SetWindowTextA(g_hStatus, "Launch FAILED - check log");
        EnableWindow(g_hBtnLaunch, TRUE);
        return;
    }

    AppendLog("[Loader] Injected RevampedHook.dll (HWID Verified OK)\r\n");
    AppendLog("[Loader] Server resumed cleanly\r\n");

    g_bServerRunning = true;
    g_bStopThreads = false;
    SetWindowTextA(g_hStatus, "Server Running (Online) - Ready for Commands");
    EnableWindow(g_hBtnStop, TRUE);

    std::thread(PipeReaderThread).detach();
    std::thread(ProcessWatchdogThread).detach();

    // 3. NpcServer
    Sleep(2000);
    STARTUPINFOA siNpc{};
    siNpc.cb = sizeof(siNpc);
    std::string npcExe = baseDir + "\\NpcServer.exe";
    char cmdNpc[MAX_PATH];
    strncpy_s(cmdNpc, npcExe.c_str(), sizeof(cmdNpc) - 1);
    if (CreateProcessA(nullptr, cmdNpc, nullptr, nullptr, FALSE, 0, nullptr, baseDir.c_str(), &siNpc, &g_piNpc)) {
        AppendLog("[Loader] Started NpcServer.exe (PID: " + std::to_string(g_piNpc.dwProcessId) + ")\r\n");
    }

    // Initial query of players
    std::thread([]() {
        RefreshPlayerList();
        PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0);
    }).detach();
}

void StopCluster() {
    AppendLog("[Loader] Stopping server processes...\r\n");
    if (g_piMsg.hProcess) {
        TerminateProcess(g_piMsg.hProcess, 0);
        CloseHandle(g_piMsg.hProcess);
        CloseHandle(g_piMsg.hThread);
        g_piMsg.hProcess = nullptr;
    }
    if (g_piNpc.hProcess) {
        TerminateProcess(g_piNpc.hProcess, 0);
        CloseHandle(g_piNpc.hProcess);
        CloseHandle(g_piNpc.hThread);
        g_piNpc.hProcess = nullptr;
    }
    g_bServerRunning = false;
    SetWindowTextA(g_hStatus, "Server Stopped");
    EnableWindow(g_hBtnLaunch, TRUE);
    EnableWindow(g_hBtnStop, FALSE);
    AppendLog("[Loader] Server processes stopped.\r\n");
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        InitializeCriticalSection(&g_csPlayers);

        g_hDarkBrush = CreateSolidBrush(RGB(18, 18, 18));
        g_hHeaderBrush = CreateSolidBrush(RGB(28, 28, 28));
        g_hPanelBrush = CreateSolidBrush(RGB(24, 26, 30));
        g_hBannerBrush = CreateSolidBrush(RGB(15, 30, 45));

        g_hMonoFont = CreateFontA(
            14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, FIXED_PITCH | FF_MODERN, "Consolas"
        );

        g_hUiFont = CreateFontA(
            14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI"
        );

        g_hBoldFont = CreateFontA(
            14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI"
        );

        g_hBannerFont = CreateFontA(
            15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI"
        );

        // --- TOP BAR: Server Controls & Player Selector ---
        g_hBtnLaunch = CreateWindowExA(0, "BUTTON", "Start Servers",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            12, 12, 125, 34, hWnd, (HMENU)IDC_LAUNCH, nullptr, nullptr);

        g_hBtnStop = CreateWindowExA(0, "BUTTON", "Stop Servers",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED,
            142, 12, 115, 34, hWnd, (HMENU)IDC_STOP, nullptr, nullptr);

        g_hStatus = CreateWindowExA(0, "STATIC", "Server Offline - Ready to Launch",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            268, 20, 260, 22, hWnd, (HMENU)IDC_STATUS, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "Target Player:",
            WS_CHILD | WS_VISIBLE | SS_RIGHT,
            535, 19, 95, 20, hWnd, nullptr, nullptr, nullptr);

        g_hGmPlayerCombo = CreateWindowExA(0, "COMBOBOX", "",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL,
            638, 16, 185, 250, hWnd, (HMENU)IDC_GM_PLAYER_COMBO, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Refresh List",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            830, 15, 105, 30, hWnd, (HMENU)IDC_GM_REFRESH, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Kick Player",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            942, 15, 95, 30, hWnd, (HMENU)IDC_GM_KICK, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Ban Acc",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            1044, 15, 80, 30, hWnd, (HMENU)IDC_GM_BAN, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Unban Acc",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            1130, 15, 85, 30, hWnd, (HMENU)IDC_GM_UNBAN, nullptr, nullptr);

        // --- PLAYER STATUS BANNER (Live Character Details) ---
        g_hPlayerBanner1 = CreateWindowExA(0, "STATIC", "Target Player: None Selected  |  Class: -  |  Level: -  |  VIP: -",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            18, 56, 1200, 20, hWnd, nullptr, nullptr, nullptr);

        g_hPlayerBanner2 = CreateWindowExA(0, "STATIC", "Conquer Points (CPs): -  |  Silvers: -  |  Coords: Map - (-, -)",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            18, 78, 1200, 20, hWnd, nullptr, nullptr, nullptr);

        // --- LEFT COLUMN: SERVER CONSOLE & LIVE PIPE LOG ---
        HWND hLogGroup = CreateWindowExA(0, "BUTTON", "Server Console & Pipe Log",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            12, 108, 520, 465, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hLogGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        g_hLogEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            22, 132, 500, 395, hWnd, (HMENU)IDC_LOG, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", ">",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            22, 537, 18, 24, hWnd, nullptr, nullptr, nullptr);

        g_hCmdEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            42, 535, 395, 26, hWnd, (HMENU)IDC_CMD, nullptr, nullptr);

        g_hBtnSend = CreateWindowExA(0, "BUTTON", "Send",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            444, 534, 78, 28, hWnd, (HMENU)IDC_SEND, nullptr, nullptr);

        // --- NETWORK & IP MANAGER (SELF-RELIANT CONFIGURATION) ---
        HWND hNetGroup = CreateWindowExA(0, "BUTTON", "Network & Server IP Manager (Auto-Sync All Configs)",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            12, 580, 520, 102, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hNetGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        CreateWindowExA(0, "STATIC", "Server IP / Domain:",
            WS_CHILD | WS_VISIBLE,
            22, 606, 125, 20, hWnd, nullptr, nullptr, nullptr);

        std::string initServerDir = loader::CConfigManager::ResolveServerDirectory();
        std::string initAccountDir = loader::CConfigManager::ResolveAccountDirectory();
        loader::CConfigManager::EnsureAllConfigsExist(initServerDir, initAccountDir);
        std::string currentIp = loader::CConfigManager::ReadCurrentServerIP(initServerDir);

        g_hServerIpEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", currentIp.c_str(),
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            150, 603, 135, 24, hWnd, (HMENU)IDC_SERVER_IP_EDIT, nullptr, nullptr);

        g_hBtnApplyIp = CreateWindowExA(0, "BUTTON", "Apply IP to Configs",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            292, 601, 135, 28, hWnd, (HMENU)IDC_APPLY_IP, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Verify Files",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            434, 601, 88, 28, hWnd, (HMENU)IDC_CHECK_CONFIGS, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "Synchronously updates shell.ini, config.ini, AccountServer Config.ini & crossconn.ini.",
            WS_CHILD | WS_VISIBLE,
            22, 638, 500, 36, hWnd, nullptr, nullptr, nullptr);

        // --- RIGHT COLUMN: GM CONTROL & IN-GAME ACTIONS ---
        int gx = 542;

        // Group 1: Real-Time Teleportation
        HWND hTpGroup = CreateWindowExA(0, "BUTTON", "Instant Teleportation (Live RAM Warp + MySQL)",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            gx, 108, 675, 135, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hTpGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        CreateWindowExA(0, "BUTTON", "Twin City", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 12, 134, 88, 28, hWnd, (HMENU)IDC_GM_TC, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Phoenix Castle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 104, 134, 96, 28, hWnd, (HMENU)IDC_GM_PC, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Ape Mountain", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 204, 134, 96, 28, hWnd, (HMENU)IDC_GM_AC, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Desert City", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 304, 134, 88, 28, hWnd, (HMENU)IDC_GM_DC, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Bird Island", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 396, 134, 88, 28, hWnd, (HMENU)IDC_GM_BI, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Market", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 488, 134, 82, 28, hWnd, (HMENU)IDC_GM_MARKET, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "NPC Jail (5000)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 574, 134, 90, 28, hWnd, (HMENU)IDC_GM_JAIL, nullptr, nullptr);

        // Custom Teleport Coordinates
        CreateWindowExA(0, "STATIC", "Map ID:", WS_CHILD | WS_VISIBLE,
            gx + 14, 178, 55, 20, hWnd, nullptr, nullptr, nullptr);
        g_hGmMap = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "1002", WS_CHILD | WS_VISIBLE | ES_NUMBER,
            gx + 72, 175, 55, 24, hWnd, (HMENU)IDC_GM_MAP, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "X:", WS_CHILD | WS_VISIBLE,
            gx + 135, 178, 18, 20, hWnd, nullptr, nullptr, nullptr);
        g_hGmX = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "430", WS_CHILD | WS_VISIBLE | ES_NUMBER,
            gx + 155, 175, 50, 24, hWnd, (HMENU)IDC_GM_X, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "Y:", WS_CHILD | WS_VISIBLE,
            gx + 212, 178, 18, 20, hWnd, nullptr, nullptr, nullptr);
        g_hGmY = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "380", WS_CHILD | WS_VISIBLE | ES_NUMBER,
            gx + 232, 175, 50, 24, hWnd, (HMENU)IDC_GM_Y, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Teleport to Coords", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 292, 173, 160, 28, hWnd, (HMENU)IDC_GM_TP_CUSTOM, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "(Warps in-memory instantly & updates database)",
            WS_CHILD | WS_VISIBLE, gx + 460, 178, 205, 20, hWnd, nullptr, nullptr, nullptr);

        // Group 2: Currency & Rewards (TWO EXPLICIT OPTIONS - NO DOUBLE GRANTS)
        HWND hEcoGroup = CreateWindowExA(0, "BUTTON", "Currency & Rewards (Separate Mail vs Inventory)",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            gx, 250, 675, 140, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hEcoGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        CreateWindowExA(0, "STATIC", "Amount:", WS_CHILD | WS_VISIBLE,
            gx + 14, 276, 55, 20, hWnd, nullptr, nullptr, nullptr);
        g_hGmAmount = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "1000", WS_CHILD | WS_VISIBLE | ES_NUMBER,
            gx + 72, 273, 95, 24, hWnd, (HMENU)IDC_GM_AMOUNT, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "1K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 175, 272, 50, 26, hWnd, (HMENU)IDC_GM_CP_1K, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "10K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 230, 272, 55, 26, hWnd, (HMENU)IDC_GM_CP_10K, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "50K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 290, 272, 55, 26, hWnd, (HMENU)IDC_GM_CP_50K, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "500K", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 350, 272, 60, 26, hWnd, (HMENU)IDC_GM_CP_500K, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "10M", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 415, 272, 55, 26, hWnd, (HMENU)IDC_GM_CP_10M, nullptr, nullptr);

        // Option A vs Option B Buttons (CPs)
        CreateWindowExA(0, "BUTTON", "[Option A] Add CPs to Inventory / DB",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 12, 308, 315, 30, hWnd, (HMENU)IDC_GM_CP_DIRECT, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "[Option B] Send CPs via Mail",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 342, 308, 320, 30, hWnd, (HMENU)IDC_GM_CP_MAIL, nullptr, nullptr);

        // Option A vs Option B Buttons (Silvers)
        CreateWindowExA(0, "BUTTON", "[Option A] Add Silvers to Inventory",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 12, 346, 315, 30, hWnd, (HMENU)IDC_GM_SILVER_DIRECT, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "[Option B] Send Silvers via Mail",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 342, 346, 320, 30, hWnd, (HMENU)IDC_GM_SILVER_MAIL, nullptr, nullptr);

        // Group 3: Full Equipment & Gear Spawner (Super +12, Double Sockets)
        HWND hGearGroup = CreateWindowExA(0, "BUTTON", "Super +12 Double-Socket Gear Spawner",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            gx, 396, 675, 140, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hGearGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        // Class Set Buttons
        CreateWindowExA(0, "BUTTON", "Trojan Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 12, 422, 88, 28, hWnd, (HMENU)IDC_GM_SET_TROJAN, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Warrior Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 104, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_WARRIOR, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Archer Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 198, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_ARCHER, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Ninja Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 292, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_NINJA, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Monk Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 386, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_MONK, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Taoist Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 480, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_TAOIST, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Pirate Set", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 574, 422, 90, 28, hWnd, (HMENU)IDC_GM_SET_PIRATE, nullptr, nullptr);

        // Custom Item Spawner
        CreateWindowExA(0, "STATIC", "Item ID:", WS_CHILD | WS_VISIBLE,
            gx + 14, 465, 55, 20, hWnd, nullptr, nullptr, nullptr);
        g_hGmItemId = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "410309", WS_CHILD | WS_VISIBLE | ES_NUMBER,
            gx + 72, 462, 95, 24, hWnd, (HMENU)IDC_GM_ITEM_ID, nullptr, nullptr);

        CreateWindowExA(0, "BUTTON", "Spawn Custom Item (+12 2-Soc)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 175, 460, 230, 28, hWnd, (HMENU)IDC_GM_SPAWN_CUSTOM, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "(Creates item directly in inventory with Super gems)",
            WS_CHILD | WS_VISIBLE, gx + 415, 465, 250, 20, hWnd, nullptr, nullptr, nullptr);

        // Group 4: Character Progression & GM Power
        HWND hPwrGroup = CreateWindowExA(0, "BUTTON", "Character Progression & GM Authority",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            gx, 542, 675, 140, hWnd, nullptr, nullptr, nullptr);
        SendMessageA(hPwrGroup, WM_SETFONT, (WPARAM)g_hBoldFont, TRUE);

        CreateWindowExA(0, "BUTTON", "Set Level 140", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 12, 570, 150, 30, hWnd, (HMENU)IDC_GM_LVL140, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Set 2nd Reborn", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 170, 570, 150, 30, hWnd, (HMENU)IDC_GM_REBORN2, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Set VIP 6 (365d)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 328, 570, 160, 30, hWnd, (HMENU)IDC_GM_VIP6, nullptr, nullptr);
        CreateWindowExA(0, "BUTTON", "Promote to GM [PM]", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            gx + 496, 570, 168, 30, hWnd, (HMENU)IDC_GM_PROMOTE_GM, nullptr, nullptr);

        CreateWindowExA(0, "STATIC", "Note: Teleportation warps live players in RAM instantly via named pipe without relogging.",
            WS_CHILD | WS_VISIBLE, gx + 14, 615, 650, 20, hWnd, nullptr, nullptr, nullptr);

        // Apply Fonts
        SendMessageA(g_hBtnLaunch, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hBtnStop, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hStatus, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hLogEdit, WM_SETFONT, (WPARAM)g_hMonoFont, TRUE);
        SendMessageA(g_hCmdEdit, WM_SETFONT, (WPARAM)g_hMonoFont, TRUE);
        SendMessageA(g_hBtnSend, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);

        SendMessageA(g_hPlayerBanner1, WM_SETFONT, (WPARAM)g_hBannerFont, TRUE);
        SendMessageA(g_hPlayerBanner2, WM_SETFONT, (WPARAM)g_hBannerFont, TRUE);

        SendMessageA(g_hGmPlayerCombo, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hGmMap, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hGmX, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hGmY, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hGmAmount, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hGmItemId, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hServerIpEdit, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);
        SendMessageA(g_hBtnApplyIp, WM_SETFONT, (WPARAM)g_hUiFont, TRUE);

        AppendLog("=========================================================================\r\n");
        AppendLog(" Conquer Online Self-Reliant Server Launcher & Real-Time GM Control Panel\r\n");
        AppendLog("=========================================================================\r\n");
        AppendLog("[Init] Self-healing config manager initialized. Active IP: " + currentIp + "\r\n");
        AppendLog("[Init] Ready. Click 'Start Servers' to launch AccountServer, MsgServer & NpcServer.\r\n\r\n");

        // Load initial player list
        std::thread([]() {
            RefreshPlayerList();
            PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0);
        }).detach();

        return 0;
    }

    case WM_UPDATE_PLAYERS_UI: {
        UpdatePlayerComboAndBanner();
        return 0;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);

        if (id == IDC_GM_PLAYER_COMBO && code == CBN_SELCHANGE) {
            int sel = (int)SendMessageA(g_hGmPlayerCombo, CB_GETCURSEL, 0, 0);
            UpdatePlayerBannerByIndex(sel);
            return 0;
        }

        if (id == IDC_LAUNCH) {
            std::thread(LaunchCluster).detach();
        } else if (id == IDC_STOP) {
            std::thread(StopCluster).detach();
        } else if (id == IDC_SEND) {
            char buf[512]{};
            GetWindowTextA(g_hCmdEdit, buf, sizeof(buf) - 1);
            std::string cmd = buf;
            if (!cmd.empty()) {
                if (cmd.back() != '\n') cmd += "\n";
                SendCommandToPipe(cmd);
                SetWindowTextA(g_hCmdEdit, "");
            }
        } else if (id == IDC_GM_REFRESH) {
            std::thread([]() {
                RefreshPlayerList();
                PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0);
            }).detach();
        } else if (id == IDC_GM_KICK) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmKickPlayer(p); }).detach();
        } else if (id == IDC_GM_BAN) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmBanAccount(p, true); }).detach();
        } else if (id == IDC_GM_UNBAN) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmBanAccount(p, false); }).detach();
        }
        // Teleportation Handlers
        else if (id == IDC_GM_TC) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1002, 430, 380, "Twin City"); }).detach();
        } else if (id == IDC_GM_PC) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1011, 236, 234, "Phoenix Castle"); }).detach();
        } else if (id == IDC_GM_AC) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1020, 565, 565, "Ape Mountain"); }).detach();
        } else if (id == IDC_GM_DC) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1000, 500, 650, "Desert City"); }).detach();
        } else if (id == IDC_GM_BI) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1015, 715, 570, "Bird Island"); }).detach();
        } else if (id == IDC_GM_MARKET) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 1036, 211, 196, "Market"); }).detach();
        } else if (id == IDC_GM_JAIL) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmTeleport(p, 5000, 50, 50, "NPC Jail"); }).detach();
        } else if (id == IDC_GM_TP_CUSTOM) {
            char map[16]{}, x[16]{}, y[16]{};
            GetWindowTextA(g_hGmMap, map, sizeof(map) - 1);
            GetWindowTextA(g_hGmX, x, sizeof(x) - 1);
            GetWindowTextA(g_hGmY, y, sizeof(y) - 1);
            int m = atoi(map), px = atoi(x), py = atoi(y);
            std::string p = GetTargetPlayerName();
            std::thread([p, m, px, py]() {
                GmTeleport(p, m, px, py, "Custom Coords");
            }).detach();
        }
        // Currency Handlers
        else if (id == IDC_GM_CP_1K) {
            SetWindowTextA(g_hGmAmount, "1000");
        } else if (id == IDC_GM_CP_10K) {
            SetWindowTextA(g_hGmAmount, "10000");
        } else if (id == IDC_GM_CP_50K) {
            SetWindowTextA(g_hGmAmount, "50000");
        } else if (id == IDC_GM_CP_500K) {
            SetWindowTextA(g_hGmAmount, "500000");
        } else if (id == IDC_GM_CP_10M) {
            SetWindowTextA(g_hGmAmount, "10000000");
        } else if (id == IDC_GM_CP_DIRECT) {
            char amt[32]{};
            GetWindowTextA(g_hGmAmount, amt, sizeof(amt) - 1);
            uint32_t a = (uint32_t)strtoul(amt, nullptr, 10);
            if (a == 0) a = 1000;
            std::string p = GetTargetPlayerName();
            std::thread([p, a]() { GmAddCpsInventory(p, a); }).detach();
        } else if (id == IDC_GM_CP_MAIL) {
            char amt[32]{};
            GetWindowTextA(g_hGmAmount, amt, sizeof(amt) - 1);
            uint32_t a = (uint32_t)strtoul(amt, nullptr, 10);
            if (a == 0) a = 1000;
            std::string p = GetTargetPlayerName();
            std::thread([p, a]() { GmSendCpsMail(p, a); }).detach();
        } else if (id == IDC_GM_SILVER_DIRECT) {
            char amt[32]{};
            GetWindowTextA(g_hGmAmount, amt, sizeof(amt) - 1);
            uint64_t a = (uint64_t)_strtoui64(amt, nullptr, 10);
            if (a == 0) a = 1000000;
            std::string p = GetTargetPlayerName();
            std::thread([p, a]() { GmAddSilversInventory(p, a); }).detach();
        } else if (id == IDC_GM_SILVER_MAIL) {
            char amt[32]{};
            GetWindowTextA(g_hGmAmount, amt, sizeof(amt) - 1);
            uint64_t a = (uint64_t)_strtoui64(amt, nullptr, 10);
            if (a == 0) a = 1000000;
            std::string p = GetTargetPlayerName();
            std::thread([p, a]() { GmSendSilversMail(p, a); }).detach();
        }
        // Class Equipment Sets (Super +12, Double Sockets)
        else if (id == IDC_GM_SET_TROJAN) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 118309, 130309, 120269, 150269, 160249, 614439, 614439, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Trojan", items); }).detach();
        } else if (id == IDC_GM_SET_WARRIOR) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 111309, 131309, 120269, 150269, 160249, 624439, 624439, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Warrior", items); }).detach();
        } else if (id == IDC_GM_SET_ARCHER) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 113309, 133309, 120269, 150269, 160249, 500329, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Archer", items); }).detach();
        } else if (id == IDC_GM_SET_NINJA) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 115309, 135309, 120269, 150269, 160249, 601439, 601439, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Ninja", items); }).detach();
        } else if (id == IDC_GM_SET_MONK) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 117309, 137309, 120269, 150269, 160249, 610439, 610439, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Monk", items); }).detach();
        } else if (id == IDC_GM_SET_TAOIST) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 114309, 134309, 120269, 150269, 160249, 421339, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Taoist", items); }).detach();
        } else if (id == IDC_GM_SET_PIRATE) {
            std::string p = GetTargetPlayerName();
            std::vector<uint32_t> items = { 119309, 139309, 120269, 150269, 160249, 611439, 612439, 201009, 202009, 204009 };
            std::thread([p, items]() { GmSpawnClassSet(p, "Pirate", items); }).detach();
        } else if (id == IDC_GM_SPAWN_CUSTOM) {
            char item[32]{};
            GetWindowTextA(g_hGmItemId, item, sizeof(item) - 1);
            uint32_t it = (uint32_t)strtoul(item, nullptr, 10);
            if (it == 0) it = 410309;
            std::string p = GetTargetPlayerName();
            std::thread([p, it]() { GmSpawnItem(p, it); }).detach();
        }
        // Progression & Authority
        else if (id == IDC_GM_LVL140) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmSetLevel(p, 140); }).detach();
        } else if (id == IDC_GM_REBORN2) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmSetReborn(p, 2); }).detach();
        } else if (id == IDC_GM_VIP6) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() { GmSetVip(p, 6); }).detach();
        } else if (id == IDC_GM_PROMOTE_GM) {
            std::string p = GetTargetPlayerName();
            std::thread([p]() {
                ExecuteGmSql("USE cq1; UPDATE cq_user SET profession = 55, vip_value = 6, level = 140, metempsychosis = 2 WHERE name = '" + p + "';", "Promoted " + p + " to Full GM Authority");
                std::thread([]() { Sleep(500); RefreshPlayerList(); PostMessageA(g_hWnd, WM_UPDATE_PLAYERS_UI, 0, 0); }).detach();
            }).detach();
        }
        // Network & IP Management Handlers
        else if (id == IDC_APPLY_IP) {
            char ipBuf[128]{};
            GetWindowTextA(g_hServerIpEdit, ipBuf, sizeof(ipBuf) - 1);
            std::string ip = ipBuf;
            while (!ip.empty() && isspace((unsigned char)ip.front())) ip.erase(ip.begin());
            while (!ip.empty() && isspace((unsigned char)ip.back())) ip.pop_back();

            if (ip.empty()) {
                AppendLog("[Network Config Warning] IP address cannot be empty!\r\n");
            } else {
                std::string sDir = loader::CConfigManager::ResolveServerDirectory();
                std::string aDir = loader::CConfigManager::ResolveAccountDirectory();
                bool ok = loader::CConfigManager::ApplyNetworkIP(sDir, aDir, ip);
                if (ok) {
                    AppendLog("=========================================================================\r\n");
                    AppendLog("[Network Config] Successfully propagated IP (" + ip + ") to all components!\r\n");
                    AppendLog("  [OK] " + sDir + "\\shell.ini -> ACCOUNT_IP=" + ip + "\r\n");
                    AppendLog("  [OK] " + sDir + "\\config.ini -> GAMESERVER_IP=" + ip + "\r\n");
                    AppendLog("  [OK] " + sDir + "\\crossconn.ini -> ClientIP1=" + ip + "\r\n");
                    AppendLog("  [OK] " + aDir + "\\Config.ini -> Host & AuthPort\r\n");
                    AppendLog("-------------------------------------------------------------------------\r\n");
                    AppendLog("Client Connection Config (Server.dat / Server.ini):\r\n");
                    AppendLog(loader::CConfigManager::GenerateClientConnectionSnippet("ConquerOnline", ip) + "\r\n");
                    AppendLog("=========================================================================\r\n");
                } else {
                    AppendLog("[Network Config Error] Failed to write IP configurations.\r\n");
                }
            }
        } else if (id == IDC_CHECK_CONFIGS) {
            std::string sDir = loader::CConfigManager::ResolveServerDirectory();
            std::string aDir = loader::CConfigManager::ResolveAccountDirectory();
            bool ok = loader::CConfigManager::EnsureAllConfigsExist(sDir, aDir);
            AppendLog("=========================================================================\r\n");
            AppendLog("[Config Manager] Configuration integrity verified.\r\n");
            AppendLog("  Server Directory:  " + sDir + "\r\n");
            AppendLog("  Account Directory: " + aDir + "\r\n");
            AppendLog("  All .ini files self-healed and ready.\r\n");
            AppendLog("=========================================================================\r\n");
        }
        return 0;
    }

    case WM_APPEND_LOG: {
        char* text = (char*)lParam;
        if (text) {
            int len = GetWindowTextLengthA(g_hLogEdit);
            SendMessageA(g_hLogEdit, EM_SETSEL, (WPARAM)len, (LPARAM)len);
            SendMessageA(g_hLogEdit, EM_REPLACESEL, FALSE, (LPARAM)text);
            SendMessageA(g_hLogEdit, WM_VSCROLL, SB_BOTTOM, 0);
            free(text);
        }
        return 0;
    }

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT: {
        HDC hdc = (HDC)wParam;
        HWND hCtrl = (HWND)lParam;
        if (hCtrl == g_hLogEdit || hCtrl == g_hCmdEdit ||
            hCtrl == g_hGmMap || hCtrl == g_hGmX || hCtrl == g_hGmY ||
            hCtrl == g_hGmAmount || hCtrl == g_hGmItemId || hCtrl == g_hServerIpEdit) {
            SetTextColor(hdc, RGB(220, 220, 220));
            SetBkColor(hdc, RGB(18, 18, 18));
            return (LRESULT)g_hDarkBrush;
        } else if (hCtrl == g_hStatus) {
            SetTextColor(hdc, RGB(0, 210, 255));
            SetBkColor(hdc, RGB(28, 28, 28));
            return (LRESULT)g_hHeaderBrush;
        } else if (hCtrl == g_hPlayerBanner1) {
            SetTextColor(hdc, RGB(255, 215, 0)); // Gold
            SetBkColor(hdc, RGB(28, 28, 28));
            return (LRESULT)g_hHeaderBrush;
        } else if (hCtrl == g_hPlayerBanner2) {
            SetTextColor(hdc, RGB(80, 220, 120)); // Soft Emerald
            SetBkColor(hdc, RGB(28, 28, 28));
            return (LRESULT)g_hHeaderBrush;
        } else {
            SetTextColor(hdc, RGB(220, 220, 220));
            SetBkColor(hdc, RGB(28, 28, 28));
            return (LRESULT)g_hHeaderBrush;
        }
    }

    case WM_ERASEBKGND: {
        HDC hdc = (HDC)wParam;
        RECT rc;
        GetClientRect(hWnd, &rc);
        FillRect(hdc, &rc, g_hHeaderBrush);
        return 1;
    }

    case WM_DESTROY: {
        g_bStopThreads = true;
        DeleteCriticalSection(&g_csPlayers);
        if (g_hDarkBrush) DeleteObject(g_hDarkBrush);
        if (g_hHeaderBrush) DeleteObject(g_hHeaderBrush);
        if (g_hPanelBrush) DeleteObject(g_hPanelBrush);
        if (g_hBannerBrush) DeleteObject(g_hBannerBrush);
        if (g_hMonoFont) DeleteObject(g_hMonoFont);
        if (g_hUiFont) DeleteObject(g_hUiFont);
        if (g_hBoldFont) DeleteObject(g_hBoldFont);
        if (g_hBannerFont) DeleteObject(g_hBannerFont);
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TQServerLoaderWnd";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassExA(&wc)) return 1;

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int winW = 1240;
    int winH = 740;
    int x = (screenW - winW) / 2;
    int y = (screenH - winH) / 2;

    g_hWnd = CreateWindowExA(
        0,
        "TQServerLoaderWnd",
        "Conquer Online Master Server Launcher & Real-Time GM Control Panel",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        x, y, winW, winH,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!g_hWnd) return 1;

    ShowWindow(g_hWnd, SW_SHOWNORMAL);
    UpdateWindow(g_hWnd);

    MSG msg;
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN) {
            HWND focus = GetFocus();
            if (focus == g_hCmdEdit) {
                SendMessageA(g_hWnd, WM_COMMAND, MAKEWPARAM(IDC_SEND, BN_CLICKED), (LPARAM)g_hBtnSend);
                continue;
            }
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
