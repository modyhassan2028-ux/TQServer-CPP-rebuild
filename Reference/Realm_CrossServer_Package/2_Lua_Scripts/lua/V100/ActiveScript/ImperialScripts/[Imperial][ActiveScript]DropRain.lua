dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DropRainConfig.lua")

ImperialDropRainRuntime = ImperialDropRainRuntime or {
    generation = 0,
    lastToken = "",
    lastScheduleToken = "",
    lastErrorToken = "",
    activeWavesLeft = 0,
    nextWaveAt = 0,
    activeConfig = nil,
}
ImperialDropRainRuntime.generation = ImperialDropRainRuntime.generation + 1
local generation = ImperialDropRainRuntime.generation

local IDR_DEFAULT_WINDOWS = {
    {Start = "15:30", Finish = "15:32"},
    {Start = "21:30", Finish = "21:32"},
}

local function IDR_Log(text)
    if Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[ImperialDropRain] " .. tostring(text or ""))
    end
end

local function IDR_Minutes(value)
    local hour, minute = string.match(tostring(value or ""), "^(%d%d):(%d%d)$")
    hour, minute = tonumber(hour), tonumber(minute)
    if hour == nil or minute == nil or hour > 23 or minute > 59 then return nil end
    return hour * 60 + minute
end

local function IDR_ScheduledToken(config, now)
    if config.Enabled ~= true then return nil end
    local windows = config.Windows or IDR_DEFAULT_WINDOWS
    local current = (tonumber(now.hour) or 0) * 60 + (tonumber(now.min) or 0)
    for index, win in ipairs(windows) do
        local first, last = IDR_Minutes(win.Start), IDR_Minutes(win.Finish)
        if first ~= nil and last ~= nil and current >= first and current < last then
            return "sched_" .. os.date("%Y%m%d") .. "_" .. tostring(index) .. "_" .. tostring(first)
        end
    end
    return nil
end

local function IDR_ReadReceipt()
    if io == nil or io.open == nil then return "" end
    local file = io.open("ImperialDropRain.last", "r")
    if file == nil then return "" end
    local token = tostring(file:read("*l") or "")
    file:close()
    return token
end

local function IDR_WriteReceipt(token)
    if io == nil or io.open == nil then return false end
    local file = io.open("ImperialDropRain.last.tmp", "w")
    if file == nil then return false end
    file:write(token)
    file:write("\n")
    file:close()
    if os ~= nil and os.remove ~= nil then pcall(os.remove, "ImperialDropRain.last") end
    if os ~= nil and os.rename ~= nil then
        return os.rename("ImperialDropRain.last.tmp", "ImperialDropRain.last") ~= nil
    end
    return false
end

local function IDR_SpawnWave(config, waveIndex, totalWaves)
    if Map_DropItem == nil then
        IDR_Log("run rejected: Map_DropItem is unavailable")
        return 0
    end
    local itemId = tonumber(config.BoxItemId) or 0
    local wanted, spawned = 0, 0
    if itemId <= 0 then IDR_Log("run rejected: invalid box item") return 0 end
    for _, location in ipairs(config.Locations or {}) do
        local mapId = tonumber(location.MapId) or 0
        local centerX = tonumber(location.CenterX) or 0
        local centerY = tonumber(location.CenterY) or 0
        local count = math.max(0, math.min(200, tonumber(location.BoxCount) or 0))
        local radius = math.max(0, math.min(100, tonumber(location.Radius) or 0))
        for _ = 1, count do
            wanted = wanted + 1
            local x = math.max(1, centerX + math.random(-radius, radius))
            local y = math.max(1, centerY + math.random(-radius, radius))
            local ok, result = pcall(Map_DropItem, mapId, x, y, itemId)
            if ok and result ~= false then
                spawned = spawned + 1
            else
                IDR_Log("drop rejected map=" .. tostring(mapId) ..
                    " x=" .. tostring(x) .. " y=" .. tostring(y))
            end
        end
    end
    if spawned > 0 and Sys_SystemBroadcast ~= nil then
        local baseMsg = tostring(config.Announcement or "[Drop Rain] Treasure boxes have fallen from the sky!")
        if totalWaves > 1 then
            Sys_SystemBroadcast(baseMsg .. " (Wave " .. tostring(waveIndex) .. "/" .. tostring(totalWaves) .. ")")
        else
            Sys_SystemBroadcast(baseMsg)
        end
    end
    IDR_Log("wave=" .. tostring(waveIndex) .. "/" .. tostring(totalWaves) .. " wanted=" .. tostring(wanted) .. " spawned=" .. tostring(spawned))
    return spawned
end

local function IDR_Run(config, token, isScheduled)
    if not isScheduled then
        ImperialDropRainRuntime.lastToken = token
        IDR_WriteReceipt(token)
    else
        ImperialDropRainRuntime.lastScheduleToken = token
    end
    local totalWaves = math.max(1, math.min(5, tonumber(config.WaveCount) or (isScheduled and 3 or 1)))
    IDR_SpawnWave(config, 1, totalWaves)
    if totalWaves > 1 then
        ImperialDropRainRuntime.activeWavesLeft = totalWaves - 1
        ImperialDropRainRuntime.totalWaves = totalWaves
        ImperialDropRainRuntime.nextWaveAt = os.time() + math.max(10, tonumber(config.WaveIntervalSeconds) or 20)
        ImperialDropRainRuntime.activeConfig = config
    end
end

function ImperialDropRain_Pulse(requestGeneration)
    if requestGeneration ~= ImperialDropRainRuntime.generation then return end
    local ok, errorText = pcall(dofile,
        "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DropRainConfig.lua")
    if ok then
        local config = tImperialDropRainConfig or {}
        local token = tostring(config.RunToken or "")
        if config.Enabled == true and token ~= "" and token ~= "0" and
           token ~= ImperialDropRainRuntime.lastToken then
            local receipt = IDR_ReadReceipt()
            if ImperialDropRainRuntime.lastToken == "" then
                ImperialDropRainRuntime.lastToken = receipt
            end
            if token ~= receipt then
                IDR_Run(config, token, false)
            else
                ImperialDropRainRuntime.lastToken = receipt
            end
        end
        local schedToken = IDR_ScheduledToken(config, os.date("*t"))
        if schedToken ~= nil and schedToken ~= ImperialDropRainRuntime.lastScheduleToken then
            IDR_Run(config, schedToken, true)
        end
        if (tonumber(ImperialDropRainRuntime.activeWavesLeft) or 0) > 0 and
           os.time() >= (tonumber(ImperialDropRainRuntime.nextWaveAt) or 0) then
            local totalWaves = tonumber(ImperialDropRainRuntime.totalWaves) or 3
            local currentWave = totalWaves - ImperialDropRainRuntime.activeWavesLeft + 1
            IDR_SpawnWave(ImperialDropRainRuntime.activeConfig or config, currentWave, totalWaves)
            ImperialDropRainRuntime.activeWavesLeft = ImperialDropRainRuntime.activeWavesLeft - 1
            ImperialDropRainRuntime.nextWaveAt = os.time() + math.max(10, tonumber(config.WaveIntervalSeconds) or 20)
        end
    else
        local token = tostring(errorText or "")
        if token ~= ImperialDropRainRuntime.lastErrorToken then
            ImperialDropRainRuntime.lastErrorToken = token
            IDR_Log("config parse failed: " .. token)
        end
    end
    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(2, "ImperialDropRain_Pulse</N>" .. tostring(requestGeneration))
    end
end

ImperialDropRainRuntime.lastToken = IDR_ReadReceipt()
if Sys_SetLuaTimer ~= nil then
    Sys_SetLuaTimer(2, "ImperialDropRain_Pulse</N>" .. tostring(generation))
end
