dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DragonsWarConfig.lua")

tNpcFace = tNpcFace or {}
tNpcFace[31] = 32 -- lookface 310: Dragons War entrance and exit

ImperialDragonsWarRuntime = ImperialDragonsWarRuntime or {
    generation=0,revision="",open=false,windowToken="",pendingToken="",pendingAt=0,nameTag="",bossStage=0,
    windowEndEpoch=0,playerCount=0
}
ImperialDragonsWarRuntime.generation = ImperialDragonsWarRuntime.generation + 1
ImperialDragonsWarRuntime.revision = tostring(tImperialDragonsWarRevision or "")
ImperialDragonsWarRuntime.nameTag = tostring(os.time())
local generation = ImperialDragonsWarRuntime.generation

local function IDW_Log(text)
    if Sys_SaveAbnormalLog ~= nil then Sys_SaveAbnormalLog("[ImperialDragonsWar] " .. tostring(text or "")) end
end

local function IDW_HudLine(userId, channel, text)
    if userId ~= nil and userId > 0 and Talk ~= nil then Talk(userId, channel, tostring(text or "")) end
end

local function IDW_ClearHud(userId)
    IDW_HudLine(userId, 2108, "")
end

local function IDW_FormatSeconds(seconds)
    seconds = math.max(0, math.floor(tonumber(seconds) or 0))
    return string.format("%02d:%02d", math.floor(seconds / 60), seconds % 60)
end

local function IDW_DrainKillQueue()
    if io == nil or io.open == nil or os == nil or os.rename == nil then return end
    local queuePath, processingPath = "DragonsWarKill.queue", "DragonsWarKill.processing"
    local processing = io.open(processingPath, "r")
    if processing == nil then
        if os.rename(queuePath, processingPath) == nil then return end
        processing = io.open(processingPath, "r")
        if processing == nil then return end
    end
    for line in processing:lines() do
        local key, killerId = string.match(line,"^IDW1|([a-z0-9_]+)|(%d+)|%d+$")
        killerId = tonumber(killerId)
        if key ~= nil and killerId ~= nil and killerId >= 1000000 and
           ImperialBoss_OnKilled ~= nil then
            local ok, errorText = pcall(ImperialBoss_OnKilled,key,killerId)
            if not ok then IDW_Log("native death queue failed key="..tostring(key)..
                " error="..tostring(errorText)) end
        else
            IDW_Log("discarded malformed native death queue row")
        end
    end
    processing:close()
    if os.remove ~= nil then pcall(os.remove,processingPath) end
end

local function IDW_Minutes(value)
    local hour, minute = string.match(tostring(value or ""), "^(%d%d):(%d%d)$")
    hour, minute = tonumber(hour), tonumber(minute)
    if hour == nil or minute == nil or hour > 23 or minute > 59 then return nil end
    return hour * 60 + minute
end

local function IDW_WindowToken(now)
    local config = tImperialDragonsWarConfig or {}
    if not config.Enabled then return nil, 0 end
    if config.ForceOpen then return "force_"..tostring(tImperialDragonsWarRevision or ""), 1800 end
    local current = now.hour * 60 + now.min
    local secInMin = tonumber(now.sec) or 0
    for index, window in ipairs(config.Windows or {}) do
        local first, last = IDW_Minutes(window.Start), IDW_Minutes(window.Finish)
        if first ~= nil and last ~= nil and first < last and current >= first and current < last then
            local remainingSec = math.max(0, ((last - current) * 60) - secInMin)
            return os.date("%Y%m%d").."_"..tostring(index).."_"..tostring(first), remainingSec
        end
    end
    return nil, 0
end

function ImperialDragonsWar_CountUser(userId)
    local config = tImperialDragonsWarConfig or {}
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 and Get_UserMapId(userId) == tonumber(config.MapId) then
        ImperialDragonsWarRuntime.playerCount = (tonumber(ImperialDragonsWarRuntime.playerCount) or 0) + 1
    end
end

function ImperialDragonsWar_HudUser(userId)
    local config = tImperialDragonsWarConfig or {}
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId <= 0 or not ImperialDragonsWarRuntime.open then return end
    if Get_UserMapId(userId) ~= tonumber(config.MapId) then return end
    local keys = config.BossKeys or {}
    local totalStages = math.max(1, #keys)
    local stage = tonumber(ImperialDragonsWarRuntime.bossStage) or 1
    local stageText = "Stage " .. tostring(math.min(stage, totalStages)) .. "/" .. tostring(totalStages)
    if stage > totalStages then
        stageText = "All Dragons Defeated!"
    elseif keys[stage] ~= nil then
        stageText = stageText .. " (" .. tostring(keys[stage]) .. ")"
    end
    local remainingSec = math.max(0, (tonumber(ImperialDragonsWarRuntime.windowEndEpoch) or 0) - os.time())
    IDW_HudLine(userId, 2108, "[Dragons War]")
    IDW_HudLine(userId, 2109, "Boss: " .. stageText)
    IDW_HudLine(userId, 2109, "Fighters: " .. tostring(tonumber(ImperialDragonsWarRuntime.playerCount) or 1))
    IDW_HudLine(userId, 2109, "-------------------")
    IDW_HudLine(userId, 2109, "Time left " .. IDW_FormatSeconds(remainingSec))
end

local function IDW_GateName(gate)
    return "ImperialDG_"..tostring(ImperialDragonsWarRuntime.nameTag).."_"..
        tostring((gate or {}).Key or "unknown")
end

local function IDW_RemoveGates(config)
    config = config or tImperialDragonsWarConfig or {}
    if Npc_DelDynaNpc == nil then return end
    pcall(Npc_DelDynaNpc, tonumber(config.MapId) or 0, "type", "26")
    for _, gate in ipairs(config.Gates or {}) do
        pcall(Npc_DelDynaNpc, tonumber(config.MapId) or 0, "name", IDW_GateName(gate))
    end
end

local function IDW_CreateGates(config)
    if Npc_CreateDynaNpc == nil then IDW_Log("Npc_CreateDynaNpc is unavailable"); return false end
    local created = 0
    for _, gate in ipairs(config.Gates or {}) do
        local ok, result = pcall(
            Npc_CreateDynaNpc,
            IDW_GateName(gate), 26, 17,
            tonumber(gate.Lookface) or 277,
            2, 4,
            tonumber(config.MapId) or 1645,
            tonumber(gate.X) or 0,
            tonumber(gate.Y) or 0,
            tonumber(gate.Life) or 1000000,
            0,
            tonumber(config.GateActionId) or 10019200,
            0,0,0,0,0,0,0,0,
            0,0,0,0,"0"
        )
        if ok then created = created + 1
        else IDW_Log("gate creation exception key="..tostring(gate.Key).." error="..tostring(result)) end
    end
    return created == #(config.Gates or {})
end

local function IDW_StartBosses(token)
    local config = tImperialDragonsWarConfig or {}
    if ImperialBoss_StartExternal == nil then IDW_Log("Boss Manager bridge is unavailable"); return false end
    if ImperialBoss_AreEnabled ~= nil and not ImperialBoss_AreEnabled(config.BossKeys) then
        IDW_Log("one or more Dragons War bosses are disabled or have no location")
        return false
    end
    for _, key in ipairs(config.BossKeys or {}) do ImperialBoss_Remove(key) end
    local first = (config.BossKeys or {})[1]
    if first == nil then IDW_Log("boss phase has no configured first boss"); return false end
    ImperialDragonsWarRuntime.bossStage = 1
    local started = ImperialBoss_StartExternal(first,"dragons_"..tostring(token))
    IDW_Log("sequential boss phase requested token="..tostring(token).." stage=1 key="..tostring(first).." started="..tostring(started))
    return started == true
end

function ImperialDragonsWar_OnBossKilled(key)
    local runtime = ImperialDragonsWarRuntime
    local config = tImperialDragonsWarConfig or {}
    if not runtime.open or config.SequentialBosses == false then return false end
    local keys = config.BossKeys or {}
    local stage = tonumber(runtime.bossStage) or 0
    if stage < 1 or tostring(keys[stage] or "") ~= tostring(key or "") then
        IDW_Log("stale or out-of-order boss death ignored key="..tostring(key).." stage="..tostring(stage))
        return false
    end
    local nextStage = stage + 1
    local nextKey = keys[nextStage]
    if nextKey == nil then
        runtime.bossStage = #keys + 1
        IDW_Log("all sequential bosses defeated token="..tostring(runtime.windowToken))
        if Sys_SystemBroadcast ~= nil then
            Sys_SystemBroadcast("[Dragons War] All Dragon Bosses have been conquered!")
        end
        return true
    end
    runtime.bossStage = nextStage
    local started = ImperialBoss_StartExternal(nextKey,"dragons_"..tostring(runtime.windowToken))
    if not started then
        runtime.bossStage = stage
        IDW_Log("next sequential boss failed key="..tostring(nextKey).." stage="..tostring(nextStage))
        return false
    end
    IDW_Log("next sequential boss started key="..tostring(nextKey).." stage="..tostring(nextStage))
    return true
end

local function IDW_Close(config)
    config = config or tImperialDragonsWarConfig or {}
    IDW_RemoveGates(config)
    if ImperialBoss_Remove ~= nil then
        for _, key in ipairs(config.BossKeys or {}) do ImperialBoss_Remove(key) end
    end
    if Map_UserExeFunc ~= nil then Map_UserExeFunc(config.MapId,-1,"ImperialDragonsWar_ReturnUser") end
    ImperialDragonsWarRuntime.open = false
    ImperialDragonsWarRuntime.windowToken = ""
    ImperialDragonsWarRuntime.pendingToken = ""
    ImperialDragonsWarRuntime.pendingAt = 0
    ImperialDragonsWarRuntime.bossStage = 0
end

local function IDW_PrepareOpen(token)
    IDW_RemoveGates(tImperialDragonsWarConfig)
    ImperialDragonsWarRuntime.pendingToken = tostring(token or "")
    ImperialDragonsWarRuntime.pendingAt = os.time() + 3
    IDW_Log("preparing dynamic gates token="..tostring(token))
end

local function IDW_Open(token, remainingSec)
    local config = tImperialDragonsWarConfig or {}
    if not IDW_CreateGates(config) then
        IDW_RemoveGates(config)
        IDW_Log("event start aborted because not all 15 reference gates were created")
        return false
    end
    if not IDW_StartBosses(token) then
        IDW_RemoveGates(config)
        IDW_Log("event start aborted because all four reference bosses are not ready")
        return false
    end
    ImperialDragonsWarRuntime.open = true
    ImperialDragonsWarRuntime.windowToken = token
    ImperialDragonsWarRuntime.windowEndEpoch = os.time() + math.max(60, tonumber(remainingSec) or 1800)
    if Sys_SystemBroadcast ~= nil then Sys_SystemBroadcast(tostring(config.OpenMessage or "Dragons War is open.")) end
    return true
end

function ImperialDragonsWar_CloseDialog() end

function ImperialDragonsWar_ReturnUser(userId)
    local config = tImperialDragonsWarConfig or {}
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 and Get_UserMapId(userId) == tonumber(config.MapId) then
        IDW_ClearHud(userId)
        User_ChgMap(config.ReturnMapId,config.ReturnX,config.ReturnY,0,userId)
    end
end

function ImperialDragonsWar_Enter()
    local config = tImperialDragonsWarConfig or {}
    local userId = tonumber(Get_UserId()) or 0
    if userId <= 0 then return end
    if not ImperialDragonsWarRuntime.open then
        User_TalkChannel2005("Dragons War is currently closed.",userId)
        return
    end
    local minimum = math.max(1,tonumber(config.MinimumLevel) or 1)
    if Get_UserLevel(userId) < minimum then User_TalkChannel2005("You must be at least level "..tostring(minimum).." to enter Dragons War.",userId); return end
    local radius = math.max(0,math.min(20,tonumber(config.SpawnRadius) or 0))
    User_ChgMap(config.MapId,config.SpawnX+math.random(-radius,radius),config.SpawnY+math.random(-radius,radius),0,userId)
    ImperialDragonsWar_HudUser(userId)
end

function ImperialDragonsWar_Exit()
    local config = tImperialDragonsWarConfig or {}
    local userId = tonumber(Get_UserId()) or 0
    if userId > 0 then
        IDW_ClearHud(userId)
        User_ChgMap(config.ReturnMapId,config.ReturnX,config.ReturnY,0,userId)
    end
end

local function IDW_InstallGossip()
    local config = tImperialDragonsWarConfig or {}
    tNpcGossip = tNpcGossip or {}
    local entryId, exitId = tonumber(config.EntryNpcId) or 0, tonumber(config.ExitNpcId) or 0
    if entryId > 0 then
        tNpcGossip[entryId]=tNpcGossip[entryId] or DefaultNpc:new{}
        local gossip=tNpcGossip[entryId]; gossip["OptionHidden"]=1; gossip["Text1-1"]={111}
        gossip["Text111"]="Dragons War:\nEnter during an active event window?"
        gossip["tOption1-1"]={1,2}; gossip["Option1"]="Enter Dragons War."; gossip["OptionFunc1"]="ImperialDragonsWar_Enter</N>"..entryId
        gossip["Option2"]="Not now."; gossip["OptionFunc2"]="ImperialDragonsWar_CloseDialog</N>"..entryId
    end
    if exitId > 0 then
        tNpcGossip[exitId]=tNpcGossip[exitId] or DefaultNpc:new{}
        local gossip=tNpcGossip[exitId]; gossip["OptionHidden"]=1; gossip["Text1-1"]={111}
        gossip["Text111"]="I can return you safely to Twin City."
        gossip["tOption1-1"]={1,2}; gossip["Option1"]="Return to Twin City."; gossip["OptionFunc1"]="ImperialDragonsWar_Exit</N>"..exitId
        gossip["Option2"]="I will stay."; gossip["OptionFunc2"]="ImperialDragonsWar_CloseDialog</N>"..exitId
    end
end

function ImperialDragonsWar_Pulse(requestGeneration)
    if requestGeneration ~= ImperialDragonsWarRuntime.generation then return end
    IDW_DrainKillQueue()
    local previous = tImperialDragonsWarConfig
    local ok = pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DragonsWarConfig.lua")
    if not ok then IDW_Log("live config parse failed") end
    local revision = tostring(tImperialDragonsWarRevision or "")
    if revision ~= ImperialDragonsWarRuntime.revision then
        if ImperialDragonsWarRuntime.open then IDW_Close(previous) end
        ImperialDragonsWarRuntime.revision = revision
        IDW_InstallGossip()
    end
    local token, remainingSec = IDW_WindowToken(os.date("*t"))
    if token ~= nil and (not ImperialDragonsWarRuntime.open and ImperialDragonsWarRuntime.windowToken ~= token) then
        if ImperialDragonsWarRuntime.pendingToken ~= token then
            IDW_PrepareOpen(token)
        elseif os.time() >= (tonumber(ImperialDragonsWarRuntime.pendingAt) or 0) then
            ImperialDragonsWarRuntime.pendingToken = ""
            ImperialDragonsWarRuntime.pendingAt = 0
            IDW_Open(token, remainingSec)
        end
    elseif token == nil and ImperialDragonsWarRuntime.open then
        IDW_Close(tImperialDragonsWarConfig)
        if Sys_SystemBroadcast ~= nil then Sys_SystemBroadcast(tostring(tImperialDragonsWarConfig.CloseMessage or "Dragons War has ended.")) end
    elseif token == nil and ImperialDragonsWarRuntime.pendingToken ~= "" then
        IDW_RemoveGates(tImperialDragonsWarConfig)
        ImperialDragonsWarRuntime.pendingToken = ""
        ImperialDragonsWarRuntime.pendingAt = 0
    end
    if ImperialDragonsWarRuntime.open then
        if remainingSec > 0 then ImperialDragonsWarRuntime.windowEndEpoch = os.time() + remainingSec end
        ImperialDragonsWarRuntime.playerCount = 0
        if Map_UserExeFunc ~= nil and tImperialDragonsWarConfig ~= nil then
            pcall(Map_UserExeFunc, tImperialDragonsWarConfig.MapId, -1, "ImperialDragonsWar_CountUser")
            pcall(Map_UserExeFunc, tImperialDragonsWarConfig.MapId, -1, "ImperialDragonsWar_HudUser")
        end
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialDragonsWar_Pulse</N>"..tostring(requestGeneration)) end
end

IDW_InstallGossip()
ImperialDragonsWarRuntime.open = false
ImperialDragonsWarRuntime.pendingToken = ""
ImperialDragonsWarRuntime.pendingAt = 0
if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(2,"ImperialDragonsWar_Pulse</N>"..tostring(generation)) end
