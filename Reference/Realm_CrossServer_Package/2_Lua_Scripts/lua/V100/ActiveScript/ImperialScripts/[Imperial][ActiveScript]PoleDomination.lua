dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]PoleDominationConfig.lua")

ImperialPoleRuntime = ImperialPoleRuntime or {
    generation=0,revision="",activeKey="",token="",pendingToken="",pendingAt=0,
    windowEndEpoch=0,activeMapId=0
}
ImperialPoleRuntime.generation = ImperialPoleRuntime.generation + 1
ImperialPoleRuntime.revision = tostring(tImperialPoleRevision or "")
local generation = ImperialPoleRuntime.generation

local function IPD_Log(text)
    if Sys_SaveAbnormalLog ~= nil then Sys_SaveAbnormalLog("[ImperialPole] " .. tostring(text or "")) end
end

local function IPD_HudLine(userId, channel, text)
    if userId ~= nil and userId > 0 and Talk ~= nil then Talk(userId, channel, tostring(text or "")) end
end

local function IPD_FormatSeconds(seconds)
    seconds = math.max(0, math.floor(tonumber(seconds) or 0))
    return string.format("%02d:%02d", math.floor(seconds / 60), seconds % 60)
end

local function IPD_Minutes(value)
    local hour, minute = string.match(tostring(value or ""), "^(%d%d):(%d%d)$")
    hour, minute = tonumber(hour), tonumber(minute)
    if hour == nil or minute == nil or hour > 23 or minute > 59 then return nil end
    return hour * 60 + minute
end

local function IPD_Find(key)
    for _, pole in ipairs((tImperialPoleConfig or {}).Poles or {}) do
        if tostring(pole.Key) == tostring(key) then return pole end
    end
    return nil
end

local function IPD_Name(pole)
    return "ImperialPole_" .. tostring((pole or {}).Key or "unknown")
end

function ImperialPole_ClearHudUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 then IPD_HudLine(userId, 2108, "") end
end

function ImperialPole_HudUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId <= 0 or ImperialPoleRuntime.activeKey == "" then return end
    local pole = IPD_Find(ImperialPoleRuntime.activeKey)
    if pole == nil or Get_UserMapId(userId) ~= tonumber(pole.MapId) then return end
    local remainingSec = math.max(0, (tonumber(ImperialPoleRuntime.windowEndEpoch) or 0) - os.time())
    IPD_HudLine(userId, 2108, "[Pole Domination]")
    IPD_HudLine(userId, 2109, "City: " .. tostring(pole.Name or pole.Key))
    IPD_HudLine(userId, 2109, "Coords: (" .. tostring(pole.X or 0) .. ", " .. tostring(pole.Y or 0) .. ")")
    IPD_HudLine(userId, 2109, "Reward: " .. tostring(pole.RewardCP or 0) .. " CPs")
    IPD_HudLine(userId, 2109, "-------------------")
    IPD_HudLine(userId, 2109, "Time left " .. IPD_FormatSeconds(remainingSec))
end

local function IPD_Remove(pole)
    if pole ~= nil and Npc_DelDynaNpc ~= nil then
        pcall(Npc_DelDynaNpc, tonumber(pole.MapId) or 0, "name", IPD_Name(pole))
    end
end

local function IPD_Stop()
    local prevPole = IPD_Find(ImperialPoleRuntime.activeKey)
    IPD_Remove(prevPole)
    if prevPole ~= nil and Map_UserExeFunc ~= nil then
        pcall(Map_UserExeFunc, tonumber(prevPole.MapId) or 0, -1, "ImperialPole_ClearHudUser")
    end
    ImperialPoleRuntime.activeKey = ""
    ImperialPoleRuntime.token = ""
    ImperialPoleRuntime.pendingToken = ""
    ImperialPoleRuntime.pendingAt = 0
end

local function IPD_Start(pole, token, remainingSec)
    if pole == nil or token == nil or token == "" then return end
    if ImperialPoleRuntime.token == token then return end
    if ImperialPoleRuntime.pendingToken ~= token then
        IPD_Stop()
        IPD_Remove(pole)
        ImperialPoleRuntime.pendingToken = token
        ImperialPoleRuntime.pendingAt = os.time()+3
        IPD_Log("preparing dynamic pole key="..tostring(pole.Key).." token="..token)
        return
    end
    if os.time() < (tonumber(ImperialPoleRuntime.pendingAt) or 0) then return end
    if Npc_CreateDynaNpc == nil then IPD_Log("Npc_CreateDynaNpc is unavailable"); return end
    local ok, result = pcall(
        Npc_CreateDynaNpc,
        IPD_Name(pole), 24, 17,
        tonumber(pole.Lookface) or 6800,
        2, 4,
        tonumber(pole.MapId) or 0,
        tonumber(pole.X) or 0,
        tonumber(pole.Y) or 0,
        tonumber(pole.Life) or 2000000,
        0,
        tonumber(pole.ActionId) or 0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,"0"
    )
    if not ok then
        IPD_Remove(pole)
        IPD_Log("dynamic pole creation exception key="..tostring(pole.Key).." error="..tostring(result))
        return
    end
    ImperialPoleRuntime.activeKey = tostring(pole.Key)
    ImperialPoleRuntime.token = token
    ImperialPoleRuntime.pendingToken = ""
    ImperialPoleRuntime.pendingAt = 0
    ImperialPoleRuntime.windowEndEpoch = os.time() + math.max(60, tonumber(remainingSec) or 1800)
    if Sys_SystemBroadcast ~= nil then
        Sys_SystemBroadcast(tostring(pole.Name).." Pole Domination has started at ("..tostring(pole.X)..","..tostring(pole.Y)..")!")
    end
    IPD_Log("started dynamic pole key="..tostring(pole.Key).." token="..token.." link="..tostring(pole.ActionId))
end

local function IPD_Scheduled(now)
    local config = tImperialPoleConfig or {}
    if not config.Enabled then return nil,nil,0 end
    local forced = tostring(config.ForcePoleKey or "")
    if forced ~= "" then
        local pole = IPD_Find(forced)
        if pole ~= nil then return pole,"force_"..tostring(tImperialPoleRevision or "").."_"..forced,1800 end
    end
    local current = now.hour * 60 + now.min
    local secInMin = tonumber(now.sec) or 0
    for _, pole in ipairs(config.Poles or {}) do
        local first = IPD_Minutes(pole.Time)
        local duration = math.max(1, math.min(180, tonumber(pole.DurationMinutes) or 1))
        if first ~= nil and current >= first and current < first + duration then
            local remainingSec = math.max(0, (((first + duration) - current) * 60) - secInMin)
            return pole,os.date("%Y%m%d").."_"..tostring(pole.Key).."_"..tostring(first),remainingSec
        end
    end
    return nil,nil,0
end

function ImperialPole_Pulse(requestGeneration)
    if requestGeneration ~= ImperialPoleRuntime.generation then return end
    local ok = pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]PoleDominationConfig.lua")
    if not ok then IPD_Log("live config parse failed") end
    local revision = tostring(tImperialPoleRevision or "")
    if revision ~= ImperialPoleRuntime.revision then
        ImperialPoleRuntime.revision = revision
        IPD_Stop()
    end
    local pole, token, remainingSec = IPD_Scheduled(os.date("*t"))
    if pole ~= nil then
        IPD_Start(pole, token, remainingSec)
        if ImperialPoleRuntime.activeKey ~= "" and Map_UserExeFunc ~= nil then
            if remainingSec > 0 then ImperialPoleRuntime.windowEndEpoch = os.time() + remainingSec end
            pcall(Map_UserExeFunc, tonumber(pole.MapId) or 0, -1, "ImperialPole_HudUser")
        end
    elseif ImperialPoleRuntime.activeKey ~= "" or ImperialPoleRuntime.pendingToken ~= "" then
        IPD_Stop()
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialPole_Pulse</N>"..tostring(requestGeneration)) end
end

if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(2,"ImperialPole_Pulse</N>"..tostring(generation)) end
