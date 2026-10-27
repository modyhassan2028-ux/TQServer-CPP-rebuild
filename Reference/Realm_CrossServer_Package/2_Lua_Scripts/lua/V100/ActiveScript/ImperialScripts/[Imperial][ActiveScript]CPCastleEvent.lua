----------------------------------------------------------------------------
-- Name:     [Imperial][ActiveScript]CPCastleEvent.lua
-- Purpose:  CP Castle Event Logic with VIP Rewards, Scoreboard HUD & Lifecycle
-- Version:  2.0 (6609-Aligned Lifecycle, Scoreboard & Auto-Eviction)
----------------------------------------------------------------------------

pcall(dofile, "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]CPCastleConfig.lua")

tNpcFace = tNpcFace or {}
tNpcFace[6115] = 32 -- lookface 61156: CP Castle entrance and exit

ImperialCpCastleRuntime = ImperialCpCastleRuntime or {
    generation = 0, revision = "", active = false, windowToken = "",
    scores = {}, windowEndEpoch = 0, playerCount = 0,
}
ImperialCpCastleRuntime.generation = ImperialCpCastleRuntime.generation + 1
ImperialCpCastleRuntime.revision = tostring(tCpCastleRevision or "")
ImperialCpCastleRuntime.scores = ImperialCpCastleRuntime.scores or {}
local CP_GENERATION = ImperialCpCastleRuntime.generation

local CP_CONFIG = tCpCastleConfig or {
    ENABLED                 = 1,
    FORCE_OPEN              = 0,
    NPC_ENTRANCE            = 999889,
    NPC_EXIT                = 999778,
    MAP_EVENT               = 9978,
    MAP_TOWN                = 1002,
    MONSTER_ID              = 3323,
    MIN_LEVEL               = 100,
    DROP_CHANCE             = 0.06,
    VIP6_CP_MULTIPLIER      = 1.0,
    VIP4_DOUBLE_DROP_CHANCE = 0.10,
    START_HOUR1             = 14,
    START_HOUR2             = 20,
    OPEN_DURATION           = 15,
}

CP_CONFIG.DROP_CHANCE = CP_CONFIG.DROP_CHANCE or 0.06
CP_CONFIG.ENABLED = CP_CONFIG.ENABLED == nil and 1 or CP_CONFIG.ENABLED
CP_CONFIG.FORCE_OPEN = CP_CONFIG.FORCE_OPEN or 0
CP_CONFIG.START_HOUR1 = CP_CONFIG.START_HOUR1 or 14
CP_CONFIG.START_HOUR2 = CP_CONFIG.START_HOUR2 or 20
CP_CONFIG.OPEN_DURATION = CP_CONFIG.OPEN_DURATION or 15

local EVENT_POOL = {}
local EVENT_POOL_KEYS = {}

local CP_DEFAULT_BAGS = {
    { ItemId = 721026, CPAmount = 50, Chance = 20, IsActive = true },
    { ItemId = 721027, CPAmount = 100, Chance = 20, IsActive = true },
    { ItemId = 721028, CPAmount = 200, Chance = 10, IsActive = true },
    { ItemId = 721029, CPAmount = 250, Chance = 10, IsActive = true },
    { ItemId = 721038, CPAmount = 500, Chance = 10, IsActive = true },
}

local function CP_Castle_RebuildPool()
    EVENT_POOL = {}
    EVENT_POOL_KEYS = {}
    local bags = tCpCastleBags or CP_DEFAULT_BAGS
    for i = 1, #bags do
        local bag = bags[i]
        local weight = math.max(0, math.floor(tonumber(bag.Chance) or 0))
        if bag.IsActive and tonumber(bag.ItemId) ~= nil and weight > 0 then
            EVENT_POOL[bag.ItemId] = { val = tonumber(bag.CPAmount) or 0, name = bag.DisplayName or "CPBag" }
            for _ = 1, weight do table.insert(EVENT_POOL_KEYS, bag.ItemId) end
        end
    end
end

CP_Castle_RebuildPool()

local function CP_Castle_HudLine(userId, channel, text)
    if userId ~= nil and userId > 0 and Talk ~= nil then Talk(userId, channel, tostring(text or "")) end
end

local function CP_Castle_ClearHud(userId)
    CP_Castle_HudLine(userId, 2108, "")
end

local function CP_Castle_FormatSeconds(seconds)
    seconds = math.max(0, math.floor(tonumber(seconds) or 0))
    return string.format("%02d:%02d", math.floor(seconds / 60), seconds % 60)
end

local function CP_Castle_CurrentWindow()
    if CP_CONFIG.FORCE_OPEN == 1 then
        return "force_" .. tostring(ImperialCpCastleRuntime.revision or ""), 900
    end
    if CP_CONFIG.ENABLED ~= 1 then return nil, 0 end
    local now = os.date("*t")
    local nHour = tonumber(now.hour) or 0
    local nMinute = tonumber(now.min) or 0
    local nSec = tonumber(now.sec) or 0
    local h1 = tonumber(CP_CONFIG.START_HOUR1) or 14
    local h2 = tonumber(CP_CONFIG.START_HOUR2) or 20
    local dur = math.max(1, tonumber(CP_CONFIG.OPEN_DURATION) or 15)

    if (nHour == h1 or nHour == h2) and nMinute < dur then
        local remainingSec = math.max(0, ((dur - nMinute) * 60) - nSec)
        local token = os.date("%Y%m%d") .. "_" .. tostring(nHour)
        return token, remainingSec
    end
    return nil, 0
end

local function CP_Castle_TopHunters(limit)
    limit = math.max(1, tonumber(limit) or 5)
    local rows = {}
    for name, score in pairs(ImperialCpCastleRuntime.scores or {}) do
        if (tonumber(score) or 0) > 0 then
            table.insert(rows, {name = name, score = tonumber(score) or 0})
        end
    end
    table.sort(rows, function(a, b)
        if a.score ~= b.score then return a.score > b.score end
        return a.name < b.name
    end)
    local top = {}
    for index = 1, math.min(limit, #rows) do
        table.insert(top, "*" .. tostring(index) .. "- " .. rows[index].name .. " : " .. tostring(rows[index].score) .. " Bags")
    end
    return top, rows[1]
end

function ImperialCpCastle_CountUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 and Get_UserMapId(userId) == CP_CONFIG.MAP_EVENT then
        ImperialCpCastleRuntime.playerCount = (tonumber(ImperialCpCastleRuntime.playerCount) or 0) + 1
    end
end

function ImperialCpCastle_HudUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId <= 0 or not ImperialCpCastleRuntime.active then return end
    if Get_UserMapId(userId) ~= CP_CONFIG.MAP_EVENT then return end
    local name = Get_UserName(userId) or ""
    local myScore = tonumber((ImperialCpCastleRuntime.scores or {})[name]) or 0
    local lines = CP_Castle_TopHunters(5)
    table.insert(lines, "-------------------")
    table.insert(lines, "Your Bags: " .. tostring(myScore))
    table.insert(lines, "Hunters: " .. tostring(tonumber(ImperialCpCastleRuntime.playerCount) or 1))
    local remainingSec = math.max(0, (tonumber(ImperialCpCastleRuntime.windowEndEpoch) or 0) - os.time())
    table.insert(lines, "Time left " .. CP_Castle_FormatSeconds(remainingSec))
    CP_Castle_HudLine(userId, 2108, "[CP Castle]")
    for _, line in ipairs(lines) do
        CP_Castle_HudLine(userId, 2109, line)
    end
end

function ImperialCpCastle_ReturnUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 and Get_UserMapId(userId) == CP_CONFIG.MAP_EVENT then
        CP_Castle_ClearHud(userId)
        User_TalkChannel2005("[CP Castle] The event window has ended. You have been returned to Twin City.", userId)
        User_ChgMap(CP_CONFIG.MAP_TOWN, 313, 294, 0, userId)
    end
end

-- =========================================================
-- ENTRANCE NPC (Twin City)
-- =========================================================

local function CP_Castle_InstallGossip()
    tNpcGossip = tNpcGossip or {}
    local nEntId = tonumber(CP_CONFIG.NPC_ENTRANCE) or 0
    local nExitId = tonumber(CP_CONFIG.NPC_EXIT) or 0
    if nEntId > 0 then
        tNpcGossip[nEntId] = tNpcGossip[nEntId] or DefaultNpc:new{}
        local entry = tNpcGossip[nEntId]
        entry["OptionHidden"] = 1
        entry["Text1-1"] = {111}
        entry["Text111"] = string.format(
            "Welcome to CP Castle. The live gates open daily at %02d:00 and %02d:00 for %d minutes.",
            tonumber(CP_CONFIG.START_HOUR1) or 14, tonumber(CP_CONFIG.START_HOUR2) or 20,
            tonumber(CP_CONFIG.OPEN_DURATION) or 15)
        entry["tOption1-1"] = {1, 2}
        entry["Option1"] = "Enter the CP Castle."
        entry["OptionFunc1"] = "CP_Castle_Enter</N>" .. nEntId
        entry["Option2"] = "I am not ready yet."
        entry["OptionFunc2"] = "CP_Castle_Close</N>" .. nEntId
    end
    if nExitId > 0 then
        tNpcGossip[nExitId] = tNpcGossip[nExitId] or DefaultNpc:new{}
        local exit = tNpcGossip[nExitId]
        exit["OptionHidden"] = 1
        exit["Text1-1"] = {111}
        exit["Text111"] = "Would you like me to teleport you back to Twin City?"
        exit["tOption1-1"] = {1, 2}
        exit["Option1"] = "Yes, send me back to Twin City."
        exit["OptionFunc1"] = "CP_Castle_Exit</N>" .. nExitId
        exit["Option2"] = "No, I will continue the fight."
        exit["OptionFunc2"] = "CP_Castle_ExitClose</N>" .. nExitId
    end
end

CP_Castle_InstallGossip()

-- =========================================================
-- CALLBACKS
-- =========================================================

function CP_Castle_Enter()
    local uid = Get_UserId()
    if not uid or uid <= 0 then return end

    local h1 = CP_CONFIG.START_HOUR1 or 14
    local h2 = CP_CONFIG.START_HOUR2 or 20
    local dur = CP_CONFIG.OPEN_DURATION or 15

    local token, _ = CP_Castle_CurrentWindow()
    local isOpen = (token ~= nil) or ImperialCpCastleRuntime.active

    if not isOpen then
        User_TalkChannel2005(string.format("The gates of CP Castle are currently closed. They open daily at %02d:00 and %02d:00 for %d minutes.", h1, h2, dur), uid)
        return
    end

    if Get_UserLevel(uid) < CP_CONFIG.MIN_LEVEL then
        User_TalkChannel2005(string.format("You must be at least level %d to enter the CP Castle.", CP_CONFIG.MIN_LEVEL), uid)
        return
    end

    User_ChgMap(CP_CONFIG.MAP_EVENT, 245, 241, 0, uid)
    ImperialCpCastle_HudUser(uid)
end

function CP_Castle_Close()
end

function CP_Castle_Exit()
    local uid = Get_UserId()
    if uid and uid > 0 then CP_Castle_ClearHud(uid) end
    User_ChgMap(CP_CONFIG.MAP_TOWN, 313, 294, 0, uid)
end

function CP_Castle_ExitClose()
end

-- =========================================================
-- DROP SYSTEM
-- =========================================================

function CP_Castle_DeliverItem(pUserId, nItemId, nVipLevel)
    local data = EVENT_POOL[nItemId]
    if not data then return end

    local playerName = Get_UserName(pUserId) or ""
    if playerName ~= "" then
        ImperialCpCastleRuntime.scores = ImperialCpCastleRuntime.scores or {}
        ImperialCpCastleRuntime.scores[playerName] = (tonumber(ImperialCpCastleRuntime.scores[playerName]) or 0) + 1
    end

    local hasSpace = User_CheckLeftSpace(1, pUserId)

    if nVipLevel >= 6 then
        local cps = math.floor(data.val * CP_CONFIG.VIP6_CP_MULTIPLIER)
        User_AddEMoney(cps, pUserId)
        User_TalkChannel2005(string.format("As a VIP6 member, your %s was converted to %d CPs directly!", data.name, cps), pUserId)
    elseif hasSpace then
        Item_AddItem(nItemId, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, pUserId)
        User_TalkChannel2005(string.format("You have received a %s!", data.name), pUserId)
    else
        local nMapId = Get_UserMapId(pUserId) or 9978
        local nX = Get_UserPositionX(pUserId) or 245
        local nY = Get_UserPositionY(pUserId) or 241
        Map_DropItem(nMapId, nX, nY, nItemId)
        User_TalkChannel2005("Your inventory is full! The CP Bag dropped on the ground.", pUserId)
    end

    if nVipLevel >= 4 and math.random() <= CP_CONFIG.VIP4_DOUBLE_DROP_CHANCE then
        User_TalkChannel2005("Lucky! Your VIP privileges triggered a Double Drop!", pUserId)
        if playerName ~= "" then
            ImperialCpCastleRuntime.scores[playerName] = (tonumber(ImperialCpCastleRuntime.scores[playerName]) or 0) + 1
        end
        if nVipLevel >= 6 then
            local cps = math.floor(data.val * CP_CONFIG.VIP6_CP_MULTIPLIER)
            User_AddEMoney(cps, pUserId)
        elseif User_CheckLeftSpace(1, pUserId) then
            Item_AddItem(nItemId, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, pUserId)
        else
            local nMapId = Get_UserMapId(pUserId) or 9978
            local nX = Get_UserPositionX(pUserId) or 245
            local nY = Get_UserPositionY(pUserId) or 241
            Map_DropItem(nMapId, nX, nY, nItemId)
        end
    end
end

-- =========================================================
-- MONSTER DROP HOOK
-- =========================================================

function CP_Castle_Monster_Drop()
    if Get_MonsterType() ~= CP_CONFIG.MONSTER_ID then
        return
    end
    local token, _ = CP_Castle_CurrentWindow()
    if not ImperialCpCastleRuntime.active and token == nil then
        return
    end

    local uid = tonumber(Get_UserId())
    if not uid or uid <= 0 then
        return
    end

    local vip = Get_UserVip(uid) or 0
    local chance = CP_CONFIG.DROP_CHANCE or 0.06

    if #EVENT_POOL_KEYS > 0 and math.random() <= chance then
        local item = EVENT_POOL_KEYS[math.random(1, #EVENT_POOL_KEYS)]
        CP_Castle_DeliverItem(uid, item, vip)
    end
end

-- =========================================================
-- REGISTER
-- =========================================================

tMonster[CP_CONFIG.MONSTER_ID] = tMonster[CP_CONFIG.MONSTER_ID] or {}
tMonster[CP_CONFIG.MONSTER_ID]["tFunction"] = tMonster[CP_CONFIG.MONSTER_ID]["tFunction"] or {}

if g_ImperialCpCastleOldDrop ~= nil then
    for index = #tMonster[CP_CONFIG.MONSTER_ID]["tFunction"], 1, -1 do
        if tMonster[CP_CONFIG.MONSTER_ID]["tFunction"][index] == g_ImperialCpCastleOldDrop then
            table.remove(tMonster[CP_CONFIG.MONSTER_ID]["tFunction"], index)
        end
    end
end
g_ImperialCpCastleOldDrop = CP_Castle_Monster_Drop
table.insert(tMonster[CP_CONFIG.MONSTER_ID]["tFunction"], g_ImperialCpCastleOldDrop)

local function CP_Castle_StartWindow(token, remainingSec)
    ImperialCpCastleRuntime.active = true
    ImperialCpCastleRuntime.windowToken = token
    ImperialCpCastleRuntime.scores = {}
    ImperialCpCastleRuntime.windowEndEpoch = os.time() + math.max(60, tonumber(remainingSec) or 900)
    if Sys_SystemBroadcast ~= nil then
        Sys_SystemBroadcast(string.format("[CP Castle] The CP Castle gates are now OPEN for %d minutes! Speak with the CP Castle Guard in Twin City!", tonumber(CP_CONFIG.OPEN_DURATION) or 15))
    end
end

local function CP_Castle_StopWindow(reason)
    if not ImperialCpCastleRuntime.active then return end
    local _, topHunter = CP_Castle_TopHunters(1)
    ImperialCpCastleRuntime.active = false
    ImperialCpCastleRuntime.windowToken = ""
    ImperialCpCastleRuntime.scores = {}
    if Map_UserExeFunc ~= nil then
        pcall(Map_UserExeFunc, CP_CONFIG.MAP_EVENT, -1, "ImperialCpCastle_ReturnUser")
    end
    if Sys_SystemBroadcast ~= nil then
        if topHunter ~= nil and topHunter.score > 0 then
            Sys_SystemBroadcast("[CP Castle] The CP Castle gates have closed! Top Hunter: " .. topHunter.name .. " (" .. tostring(topHunter.score) .. " bags). " .. tostring(reason or ""))
        else
            Sys_SystemBroadcast("[CP Castle] The CP Castle gates have closed! All hunters were returned to Twin City.")
        end
    end
end

function ImperialCpCastle_Pulse(requestGeneration)
    if requestGeneration ~= ImperialCpCastleRuntime.generation then return end
    local ok = pcall(dofile, "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]CPCastleConfig.lua")
    if ok then
        local revision = tostring(tCpCastleRevision or "")
        if revision ~= ImperialCpCastleRuntime.revision then
            ImperialCpCastleRuntime.revision = revision
            CP_CONFIG = tCpCastleConfig or CP_CONFIG
            CP_CONFIG.DROP_CHANCE = CP_CONFIG.DROP_CHANCE or 0.06
            CP_CONFIG.ENABLED = CP_CONFIG.ENABLED == nil and 1 or CP_CONFIG.ENABLED
            CP_CONFIG.FORCE_OPEN = CP_CONFIG.FORCE_OPEN or 0
            CP_CONFIG.START_HOUR1 = CP_CONFIG.START_HOUR1 or 14
            CP_CONFIG.START_HOUR2 = CP_CONFIG.START_HOUR2 or 20
            CP_CONFIG.OPEN_DURATION = CP_CONFIG.OPEN_DURATION or 15
            CP_Castle_RebuildPool()
            CP_Castle_InstallGossip()
        end
    elseif Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[ImperialCpCastle] live config parse failed")
    end

    local token, remainingSec = CP_Castle_CurrentWindow()
    if token ~= nil and (not ImperialCpCastleRuntime.active or ImperialCpCastleRuntime.windowToken ~= token) then
        if ImperialCpCastleRuntime.active then CP_Castle_StopWindow("Configuration updated.") end
        CP_Castle_StartWindow(token, remainingSec)
    elseif token == nil and ImperialCpCastleRuntime.active then
        CP_Castle_StopWindow("The event window has ended.")
    end

    if ImperialCpCastleRuntime.active then
        if remainingSec > 0 then ImperialCpCastleRuntime.windowEndEpoch = os.time() + remainingSec end
        ImperialCpCastleRuntime.playerCount = 0
        if Map_UserExeFunc ~= nil then
            pcall(Map_UserExeFunc, CP_CONFIG.MAP_EVENT, -1, "ImperialCpCastle_CountUser")
            pcall(Map_UserExeFunc, CP_CONFIG.MAP_EVENT, -1, "ImperialCpCastle_HudUser")
        end
    end

    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(5, "ImperialCpCastle_Pulse</N>" .. tostring(requestGeneration))
    end
end

if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(2, "ImperialCpCastle_Pulse</N>" .. tostring(CP_GENERATION)) end
