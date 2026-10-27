-- Imperial Squama Event controller
-- Trap type 51 is routed to LinkTrapMain (action 94427500) by the panel.
-- Settings are polled from ServerGameConfig.ini and runtime coordinates are
-- published to SquamaEventState.ini for the WPF control panel.

local SQ_CONFIG_PATH = "ServerGameConfig.ini"
local SQ_STATE_PATH = "SquamaEventState.ini"
local SQ_TRAP_TYPE = 51
local SQ_TRAP_LOOK = 11
local SQ_PULSE_SECONDS = 3
local SQ_BOOTSTRAP_SECONDS = 30

ImperialSquamaRuntime = ImperialSquamaRuntime or {
    active = false, positions = {}, claiming = {}, commandToken = "", manualOverride = nil
}
local SQ_Runtime = ImperialSquamaRuntime
SQ_Runtime.positions = SQ_Runtime.positions or {}
SQ_Runtime.claiming = SQ_Runtime.claiming or {}
SQ_Runtime.generation = (SQ_Runtime.generation or 0) + 1

local function SQ_Trim(value)
    if type(value) ~= "string" then return "" end
    return (string.gsub(value, "^%s*(.-)%s*$", "%1"))
end

local function SQ_Bool(value, fallback)
    if value == nil then return fallback end
    value = string.lower(SQ_Trim(tostring(value)))
    if value == "true" or value == "1" or value == "yes" or value == "on" then return true end
    if value == "false" or value == "0" or value == "no" or value == "off" then return false end
    return fallback
end

local function SQ_Int(value, fallback, minimum, maximum)
    local number = tonumber(value)
    if number == nil then return fallback end
    number = math.floor(number)
    if number < minimum then return minimum end
    if number > maximum then return maximum end
    return number
end

local function SQ_Split(value)
    local result = {}
    for part in string.gmatch(tostring(value or ""), "([^,]+)") do table.insert(result, SQ_Trim(part)) end
    return result
end

local function SQ_ReadConfig()
    local values = {}
    if io ~= nil and io.open ~= nil then
        local ok, file = pcall(io.open, SQ_CONFIG_PATH, "r")
        if ok and file ~= nil then
            local section = ""
            for line in file:lines() do
                local clean = SQ_Trim(string.gsub(line, "[;#].*$", ""))
                local sectionName = string.match(clean, "^%[([^%]]+)%]$")
                if sectionName ~= nil then section = string.lower(SQ_Trim(sectionName))
                elseif section == "squamaevent" then
                    local key, value = string.match(clean, "^([^=]+)=(.*)$")
                    if key ~= nil then values[string.lower(SQ_Trim(key))] = SQ_Trim(value) end
                end
            end
            file:close()
        end
    end

    local config = {
        Enabled = SQ_Bool(values.enabled, false), AutoSchedule = SQ_Bool(values.autoschedule, false),
        DesiredRunning = SQ_Bool(values.desiredrunning, false), StartHour = SQ_Int(values.starthour, 20, 0, 23),
        StartMinute = SQ_Int(values.startminute, 0, 0, 59), DurationMinutes = SQ_Int(values.durationminutes, 120, 1, 1440),
        SpawnCount = SQ_Int(values.spawncount, 20, 1, 95), Command = string.lower(values.command or "save"),
        CommandToken = values.commandtoken or "", Rewards = {}, Candidates = {}, EnabledMaps = {}
    }
    local mapCount = SQ_Int(values.mapcount, 0, 0, 100)
    for index = 1, mapCount do
        local parts = SQ_Split(values["map" .. index])
        local mapId = tonumber(parts[1])
        if mapId ~= nil then config.EnabledMaps[math.floor(mapId)] = SQ_Bool(parts[2], true) end
    end
    local candidateCount = SQ_Int(values.candidatecount, 0, 0, 100)
    for index = 1, candidateCount do
        local parts = SQ_Split(values["candidate" .. index])
        local mapId, x, y = tonumber(parts[1]), tonumber(parts[2]), tonumber(parts[3])
        if mapId ~= nil and x ~= nil and y ~= nil and config.EnabledMaps[math.floor(mapId)] ~= false then
            table.insert(config.Candidates, { map = math.floor(mapId), x = math.floor(x), y = math.floor(y) })
        end
    end
    local rewardCount = SQ_Int(values.rewardcount, 0, 0, 20)
    for index = 1, rewardCount do
        local parts = SQ_Split(values["reward" .. index])
        local rewardType = string.lower(parts[1] or "")
        local value, weight = tonumber(parts[2]), tonumber(parts[3])
        if value ~= nil and value > 0 and weight ~= nil and weight > 0 and
            (rewardType == "item" or rewardType == "silver" or rewardType == "cp" or rewardType == "boundcp") then
            table.insert(config.Rewards, { type = rewardType, value = math.floor(value), weight = math.floor(weight),
                broadcast = SQ_Bool(parts[4], false), name = string.gsub(parts[5] or "Reward", "|", ",") })
        end
    end
    return config
end

local function SQ_WriteState(note)
    if io == nil or io.open == nil then return end
    local ok, file = pcall(io.open, SQ_STATE_PATH, "w")
    if not ok or file == nil then return end
    file:write("[SquamaEventState]\n")
    file:write("Active=" .. tostring(SQ_Runtime.active == true) .. "\n")
    file:write("PositionCount=" .. tostring(#SQ_Runtime.positions) .. "\n")
    file:write("Updated=" .. os.date("%Y-%m-%d %H:%M:%S") .. "\n")
    file:write("Note=" .. tostring(note or "") .. "\n")
    for index, position in ipairs(SQ_Runtime.positions) do
        file:write("Position" .. index .. "=" .. position.map .. "," .. position.x .. "," .. position.y .. "\n")
    end
    file:close()
end

local function SQ_DeleteAll()
    local maps = {}
    for _, position in ipairs(SQ_Runtime.positions) do maps[position.map] = true end
    if SQ_Runtime.config ~= nil then
        for _, candidate in ipairs(SQ_Runtime.config.Candidates or {}) do maps[candidate.map] = true end
    end
    for mapId, _ in pairs(maps) do
        if Trap_DelMapTrap ~= nil then pcall(Trap_DelMapTrap, mapId, SQ_TRAP_TYPE) end
    end
    SQ_Runtime.positions = {}
    SQ_Runtime.active = false
end

local function SQ_Stop(note)
    SQ_DeleteAll()
    SQ_WriteState(note or "Stopped")
end

local function SQ_ShuffledCopy(source)
    local result = {}
    for index, value in ipairs(source) do result[index] = value end
    for index = #result, 2, -1 do
        local other = math.random(1, index)
        result[index], result[other] = result[other], result[index]
    end
    return result
end

local function SQ_Start(config, note)
    SQ_DeleteAll()
    if #config.Candidates == 0 or #config.Rewards == 0 then
        SQ_WriteState("Cannot start: no candidates or rewards")
        return false
    end
    local candidates = SQ_ShuffledCopy(config.Candidates)
    local wanted = math.min(config.SpawnCount, #candidates)
    for index = 1, wanted do
        local spot = candidates[index]
        local ok, created = pcall(Trap_CreateMapTrap, SQ_TRAP_TYPE, SQ_TRAP_LOOK, 0, spot.map, spot.x, spot.y, 0, 0)
        if ok and created then table.insert(SQ_Runtime.positions, { map = spot.map, x = spot.x, y = spot.y }) end
    end
    SQ_Runtime.active = #SQ_Runtime.positions > 0
    SQ_WriteState(note or "Started with random positions")
    return SQ_Runtime.active
end

local function SQ_IsScheduleOpen(config)
    local now = os.date("*t")
    local current = now.hour * 60 + now.min
    local start = config.StartHour * 60 + config.StartMinute
    local finish = start + config.DurationMinutes
    if finish <= 1440 then return current >= start and current < finish end
    return current >= start or current < (finish - 1440)
end

local function SQ_Message(userId, message)
    if User_TalkChannel2005 ~= nil then User_TalkChannel2005("[Squama] " .. tostring(message), userId) end
end

local function SQ_SelectReward(rewards)
    local total = 0
    for _, reward in ipairs(rewards) do total = total + reward.weight end
    if total <= 0 then return nil end
    local roll, cursor = math.random(1, total), 0
    for _, reward in ipairs(rewards) do cursor = cursor + reward.weight; if roll <= cursor then return reward end end
    return rewards[#rewards]
end

function ImperialSquama_OnTrap(trapId, trapType)
    if trapType ~= SQ_TRAP_TYPE or not SQ_Runtime.active or SQ_Runtime.config == nil then return end
    trapId = tonumber(trapId) or 0
    if trapId <= 0 or SQ_Runtime.claiming[trapId] then return end
    local userId = tonumber(Get_UserId()) or 0
    if userId <= 0 then return end
    SQ_Runtime.claiming[trapId] = true
    local function deliveryFailed(message)
        SQ_Runtime.claiming[trapId] = nil
        SQ_Message(userId, message)
    end
    local reward = SQ_SelectReward(SQ_Runtime.config.Rewards)
    if reward == nil then deliveryFailed("No reward is configured. The Squama was left in place."); return end
    if reward.type == "item" then
        if User_CheckLeftSpace ~= nil and not User_CheckLeftSpace(1, userId) then deliveryFailed("Please make one free inventory space first."); return end
        if Item_AddNewItem == nil or Item_AddNewItem(reward.value, "", userId) == false then deliveryFailed("The item could not be delivered; the Squama was left in place."); return end
    elseif reward.type == "silver" then if User_AddMoney == nil or User_AddMoney(reward.value, userId) == false then deliveryFailed("Silver delivery failed; the Squama was left in place."); return end
    elseif reward.type == "cp" then if User_AddEMoney == nil or User_AddEMoney(reward.value, userId) == false then deliveryFailed("CP delivery failed; the Squama was left in place."); return end
    elseif reward.type == "boundcp" then if User_AddEMoneyMono == nil or User_AddEMoneyMono(reward.value, userId) == false then deliveryFailed("Bound CP delivery failed; the Squama was left in place."); return end end

    local mapId = tonumber(Get_TrapMAPID(trapId)) or 0
    local x = tonumber(Get_TrapPosX(trapId)) or 0
    local y = tonumber(Get_TrapPosY(trapId)) or 0
    SQ_Message(userId, "You found " .. tostring(reward.name) .. "!")
    if reward.broadcast and Map_SendBroadcastMsg ~= nil then Map_SendBroadcastMsg(mapId, "[Squama] A player found " .. tostring(reward.name) .. "!") end
    Trap_EraseMapTrap(trapId)
    SQ_Runtime.claiming[trapId] = nil
    for index = #SQ_Runtime.positions, 1, -1 do
        local position = SQ_Runtime.positions[index]
        if position.map == mapId and position.x == x and position.y == y then table.remove(SQ_Runtime.positions, index); break end
    end
    if #SQ_Runtime.positions == 0 then SQ_Runtime.active = false end
    SQ_WriteState("A Squama was claimed")
end

function ImperialSquama_Pulse(generation)
    generation = tonumber(generation) or 0
    if generation ~= SQ_Runtime.generation then return end
    local config = SQ_ReadConfig()
    SQ_Runtime.config = config
    local scheduleOpen = config.AutoSchedule and SQ_IsScheduleOpen(config) or false
    if SQ_Runtime.lastScheduleOpen == nil then SQ_Runtime.lastScheduleOpen = scheduleOpen
    elseif SQ_Runtime.lastScheduleOpen ~= scheduleOpen then SQ_Runtime.lastScheduleOpen = scheduleOpen; SQ_Runtime.manualOverride = nil end

    if config.CommandToken ~= "" and config.CommandToken ~= SQ_Runtime.commandToken then
        SQ_Runtime.commandToken = config.CommandToken
        if config.Command == "start" then SQ_Runtime.manualOverride = true
        elseif config.Command == "stop" then SQ_Runtime.manualOverride = false
        elseif config.Command == "reshuffle" then SQ_Runtime.manualOverride = true; SQ_Stop("Reshuffling"); SQ_Start(config, "Reshuffled to new random positions") end
    end
    local desired = config.DesiredRunning
    if config.AutoSchedule then desired = scheduleOpen end
    if SQ_Runtime.manualOverride ~= nil then desired = SQ_Runtime.manualOverride end
    if not config.Enabled then desired = false end
    if desired and not SQ_Runtime.active then SQ_Start(config, "Started")
    elseif not desired and SQ_Runtime.active then SQ_Stop("Stopped")
    elseif not desired then SQ_WriteState("Stopped") end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(SQ_PULSE_SECONDS, "ImperialSquama_Pulse</N>" .. tostring(generation)) end
end

tTrap = tTrap or {}
tTrap[SQ_TRAP_TYPE] = tTrap[SQ_TRAP_TYPE] or {}
tTrap[SQ_TRAP_TYPE]["Function"] = ImperialSquama_OnTrap

math.randomseed(os.time() + SQ_Runtime.generation * 997)
-- Active scripts are loaded while MsgServer is still constructing MapGroup.
-- Creating/deleting traps at that point reaches MapGroup before its
-- RoleManager exists and aborts the native server in mapgroup.h.  Match the
-- tournament controller's proven startup pattern and defer the first pulse;
-- generation checking above also makes this safe across /reloadlua.
if Sys_SetLuaTimer ~= nil then
    Sys_SetLuaTimer(SQ_BOOTSTRAP_SECONDS, "ImperialSquama_Pulse</N>" .. tostring(SQ_Runtime.generation))
end
