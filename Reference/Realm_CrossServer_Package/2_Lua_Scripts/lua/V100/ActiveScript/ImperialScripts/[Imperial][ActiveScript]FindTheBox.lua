dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]FindTheBoxConfig.lua")

tNpcFace = tNpcFace or {}
tNpcFace[31] = 32 -- lookface 310: Find The Box envoy

local hadFindBoxRuntime = ImperialFindBoxRuntime ~= nil
ImperialFindBoxRuntime = ImperialFindBoxRuntime or {
    active=false, generation=0, revision="", pendingToken="", pendingAt=0,
    bootReadyAt=os.time()+30, scores={}, boxesOpenedSinceRefill=0, lastRefillAt=0,
    windowEndEpoch=0,
}
if hadFindBoxRuntime then ImperialFindBoxRuntime.bootReadyAt = os.time()+3 end
ImperialFindBoxRuntime.generation = ImperialFindBoxRuntime.generation + 1
ImperialFindBoxRuntime.revision = tostring(tImperialFindBoxRevision or "")
ImperialFindBoxRuntime.scores = ImperialFindBoxRuntime.scores or {}
ImperialFindBoxRuntime.boxesOpenedSinceRefill = ImperialFindBoxRuntime.boxesOpenedSinceRefill or 0
ImperialFindBoxRuntime.lastRefillAt = ImperialFindBoxRuntime.lastRefillAt or 0
local generation = ImperialFindBoxRuntime.generation

local function IFB_Log(text)
    if Sys_SaveAbnormalLog ~= nil then Sys_SaveAbnormalLog("[ImperialFindBox] " .. tostring(text or "")) end
end

local function IFB_HudLine(userId, channel, text)
    if userId ~= nil and userId > 0 and Talk ~= nil then Talk(userId, channel, tostring(text or "")) end
end

local function IFB_ClearHud(userId)
    IFB_HudLine(userId, 2108, "")
end

local function IFB_RecordBoxOpen(playerName, countOpened)
    if type(playerName) ~= "string" or playerName == "" then return end
    ImperialFindBoxRuntime.scores = ImperialFindBoxRuntime.scores or {}
    ImperialFindBoxRuntime.scores[playerName] = (tonumber(ImperialFindBoxRuntime.scores[playerName]) or 0) + (tonumber(countOpened) or 1)
    ImperialFindBoxRuntime.boxesOpenedSinceRefill = (tonumber(ImperialFindBoxRuntime.boxesOpenedSinceRefill) or 0) + (tonumber(countOpened) or 1)
end

local function IFB_DrainScoreQueue()
    if io == nil or io.open == nil or os == nil or os.rename == nil then return false end
    local queuePath = "FindTheBoxScore.queue"
    local processingPath = "FindTheBoxScore.processing"
    local processing = io.open(processingPath, "r")
    if processing == nil then
        if os.rename(queuePath, processingPath) == nil then return false end
        processing = io.open(processingPath, "r")
        if processing == nil then return false end
    end
    local hadRows = false
    for line in processing:lines() do
        local roleId, player, outcome = string.match(line, "^IFS1|(%d+)|([^|]+)|([^|\r\n]+)")
        if player ~= nil and outcome ~= nil then
            IFB_RecordBoxOpen(player, 1)
            hadRows = true
        end
    end
    processing:close()
    if os.remove ~= nil then pcall(os.remove, processingPath) end
    return hadRows
end

local function IFB_DrainBroadcastQueue()
    local scoredFromNative = IFB_DrainScoreQueue()
    if io == nil or io.open == nil or os == nil or os.rename == nil then return end
    local queuePath = "FindTheBoxBroadcast.queue"
    local processingPath = "FindTheBoxBroadcast.processing"
    local processing = io.open(processingPath, "r")
    if processing == nil then
        if os.rename(queuePath, processingPath) == nil then return end
        processing = io.open(processingPath, "r")
        if processing == nil then return end
    end
    local messages = {}
    for line in processing:lines() do
        local player, amount, itemName = string.match(
            line, "^IFB1|([^|]+)|(%d+)|([^|\r\n]+)$")
        amount = tonumber(amount)
        if player ~= nil and itemName ~= nil and amount ~= nil and
           amount >= 1 and amount <= 100 then
            if not scoredFromNative then
                IFB_RecordBoxOpen(player, 1)
            end
            table.insert(messages, "[Find The Box] " .. player ..
                " won " .. tostring(amount) .. " x " .. itemName .. "!")
        else
            IFB_Log("discarded malformed broadcast queue row")
        end
    end
    processing:close()
    if os.remove ~= nil then pcall(os.remove, processingPath) end
    if Sys_SystemBroadcast ~= nil then
        for _, message in ipairs(messages) do Sys_SystemBroadcast(message) end
    end
end

local function IFB_Minutes(value)
    local hour, minute = string.match(tostring(value or ""), "^(%d%d):(%d%d)$")
    hour, minute = tonumber(hour), tonumber(minute)
    if hour == nil or minute == nil or hour > 23 or minute > 59 then return nil end
    return hour * 60 + minute
end

local function IFB_Window(now)
    if tImperialFindBoxConfig.ForceOpen then
        return "force_" .. tostring(tImperialFindBoxRevision or ""), 1800
    end
    local current = now.hour * 60 + now.min
    local secInMin = tonumber(now.sec) or 0
    for index, window in ipairs(tImperialFindBoxConfig.Windows or {}) do
        local first, last = IFB_Minutes(window.Start), IFB_Minutes(window.Finish)
        if first ~= nil and last ~= nil and first < last and current >= first and current < last then
            local remainingSec = math.max(0, ((last - current) * 60) - secInMin)
            return os.date("%Y%m%d") .. "_" .. tostring(index) .. "_" .. tostring(first), remainingSec
        end
    end
    return nil, 0
end

local function IFB_FormatSeconds(seconds)
    seconds = math.max(0, math.floor(tonumber(seconds) or 0))
    return string.format("%02d:%02d", math.floor(seconds / 60), seconds % 60)
end

local function IFB_SortedTopScores(limit)
    limit = math.max(1, tonumber(limit) or 10)
    local rows = {}
    for name, score in pairs(ImperialFindBoxRuntime.scores or {}) do
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
        table.insert(top, "No " .. tostring(index) .. "- " .. rows[index].name .. " Opened " .. tostring(rows[index].score) .. " Boxes!")
    end
    return top, rows[1]
end

function ImperialFindBox_HudUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId <= 0 or not ImperialFindBoxRuntime.active then return end
    if Get_UserMapId(userId) ~= tImperialFindBoxConfig.MapId then return end
    local playerName = Get_UserName(userId) or ""
    local myScore = tonumber((ImperialFindBoxRuntime.scores or {})[playerName]) or 0
    local lines = IFB_SortedTopScores(10)
    if #lines == 0 then
        table.insert(lines, "Open boxes to climb the ranking!")
    end
    table.insert(lines, "-------------------")
    local remainingSec = math.max(0, (tonumber(ImperialFindBoxRuntime.windowEndEpoch) or 0) - os.time())
    table.insert(lines, "Time left: " .. IFB_FormatSeconds(remainingSec))
    IFB_HudLine(userId, 2108, "---Your Score: " .. tostring(myScore) .. "---")
    for _, line in ipairs(lines) do
        IFB_HudLine(userId, 2109, line)
    end
end

local function IFB_RemoveBoxes()
    if Monster_DelMonster ~= nil then Monster_DelMonster(tImperialFindBoxConfig.MapId, tImperialFindBoxConfig.BoxMonsterId) end
end

local function IFB_PickSpawnPoint()
    local zones=tImperialFindBoxConfig.SpawnZones or {}
    local total=0
    for _,zone in ipairs(zones) do total=total+math.max(0,tonumber(zone.Weight) or 0) end
    if total > 0 then
        local roll=math.random()*total
        for _,zone in ipairs(zones) do
            roll=roll-math.max(0,tonumber(zone.Weight) or 0)
            if roll <= 0 then
                local width=math.max(0,tonumber(zone.Width) or 0)
                local height=math.max(0,tonumber(zone.Height) or 0)
                return (tonumber(zone.X) or 1)+math.random(0,width),
                       (tonumber(zone.Y) or 1)+math.random(0,height)
            end
        end
    end
    local radius=math.max(0,tonumber(tImperialFindBoxConfig.SpawnRadius) or 0)
    return tImperialFindBoxConfig.SpawnX+math.random(-radius,radius),
           tImperialFindBoxConfig.SpawnY+math.random(-radius,radius)
end

local function IFB_SpawnBoxes(countToSpawn)
    if not ImperialFindBoxRuntime.active then return 0 end
    local wanted=math.max(1,math.min(100,tonumber(countToSpawn) or tonumber(tImperialFindBoxConfig.BoxCount) or 40))
    local spawned=0
    for _=1,wanted do
        local x,y=IFB_PickSpawnPoint()
        if Monster_AddMonster(tImperialFindBoxConfig.MapId,x,y,
            tImperialFindBoxConfig.GeneratorId,tImperialFindBoxConfig.BoxMonsterId) ~= false then
            spawned=spawned+1
        end
    end
    return spawned
end

local function IFB_SpawnRound()
    if not ImperialFindBoxRuntime.active then return 0 end
    local wanted=math.max(1,math.min(100,tonumber(tImperialFindBoxConfig.BoxCount) or 40))
    local spawned = IFB_SpawnBoxes(wanted)
    ImperialFindBoxRuntime.boxesOpenedSinceRefill = 0
    ImperialFindBoxRuntime.lastRefillAt = os.time()
    IFB_Log("round spawn wanted="..tostring(wanted).." accepted="..tostring(spawned))
    return spawned
end

local function IFB_CheckRefill()
    if not ImperialFindBoxRuntime.active then return end
    local now = os.time()
    local interval = math.max(15, tonumber(tImperialFindBoxConfig.RefillIntervalSeconds) or 30)
    if now - (tonumber(ImperialFindBoxRuntime.lastRefillAt) or 0) < interval then return end
    ImperialFindBoxRuntime.lastRefillAt = now
    local opened = math.max(0, tonumber(ImperialFindBoxRuntime.boxesOpenedSinceRefill) or 0)
    if opened <= 0 then return end
    local toSpawn = math.min(opened, math.max(1, tonumber(tImperialFindBoxConfig.BoxCount) or 100))
    local spawned = IFB_SpawnBoxes(toSpawn)
    ImperialFindBoxRuntime.boxesOpenedSinceRefill = math.max(0, opened - spawned)
    if spawned > 0 and Map_SendBroadcastMsg ~= nil then
        Map_SendBroadcastMsg(tImperialFindBoxConfig.MapId, "[Find The Box] " .. tostring(spawned) .. " new treasure boxes have appeared!")
    end
    IFB_Log("refill spawned=" .. tostring(spawned))
end

function ImperialFindBox_ReturnUser(userId)
    userId = tonumber(userId) or tonumber(Get_UserId()) or 0
    if userId > 0 and Get_UserMapId(userId) == tImperialFindBoxConfig.MapId then
        IFB_ClearHud(userId)
        User_ChgMap(tImperialFindBoxConfig.ReturnMapId, tImperialFindBoxConfig.ReturnX, tImperialFindBoxConfig.ReturnY, 0, userId)
    end
end

local function IFB_Stop(reason)
    if not ImperialFindBoxRuntime.active then return end
    local _, topHunter = IFB_SortedTopScores(1)
    IFB_RemoveBoxes()
    if Map_UserExeFunc ~= nil then Map_UserExeFunc(tImperialFindBoxConfig.MapId, -1, "ImperialFindBox_ReturnUser") end
    ImperialFindBoxRuntime.active = false
    ImperialFindBoxRuntime.runToken = nil
    ImperialFindBoxRuntime.scores = {}
    ImperialFindBoxRuntime.boxesOpenedSinceRefill = 0
    if Sys_SystemBroadcast ~= nil then
        if topHunter ~= nil and topHunter.score > 0 then
            Sys_SystemBroadcast("Find The Box has ended! Top Box Hunter: " .. topHunter.name .. " (" .. tostring(topHunter.score) .. " boxes). " .. tostring(reason or ""))
        else
            Sys_SystemBroadcast("Find The Box has ended. " .. tostring(reason or ""))
        end
    end
    IFB_Log("stopped reason=" .. tostring(reason or ""))
end

local function IFB_Start(windowToken, remainingSec)
    if ImperialFindBoxRuntime.active then return end
    IFB_RemoveBoxes()
    ImperialFindBoxRuntime.active = true
    ImperialFindBoxRuntime.runToken = windowToken
    ImperialFindBoxRuntime.scores = {}
    ImperialFindBoxRuntime.boxesOpenedSinceRefill = 0
    ImperialFindBoxRuntime.windowEndEpoch = os.time() + math.max(60, tonumber(remainingSec) or 1800)
    local spawned = IFB_SpawnRound()
    if spawned == 0 then
        ImperialFindBoxRuntime.active = false
        ImperialFindBoxRuntime.runToken = nil
        IFB_Log("start aborted: every box spawn failed; check generator " .. tostring(tImperialFindBoxConfig.GeneratorId))
        if Sys_SystemBroadcast ~= nil then Sys_SystemBroadcast("Find The Box could not start; the event was closed safely.") end
        return
    end
    if Sys_SystemBroadcast ~= nil then Sys_SystemBroadcast("Find The Box has started! Speak with the event envoy in Twin City (377, 312).") end
    IFB_Log("started token=" .. tostring(windowToken) .. " boxes=" .. tostring(spawned))
end

function ImperialFindBox_Join(npcId)
    local userId = tonumber(Get_UserId()) or 0
    if userId <= 0 then IFB_Log("join rejected: missing player context") return end
    if not ImperialFindBoxRuntime.active then Sys_MsgBox("Find The Box is currently closed.", userId); return end
    local entryX,entryY = IFB_PickSpawnPoint()
    local moved = User_ChgMap(tImperialFindBoxConfig.MapId, entryX, entryY, 0, userId)
    IFB_Log("join user=" .. tostring(userId) .. " npc=" .. tostring(npcId or 0) .. " map=" .. tostring(tImperialFindBoxConfig.MapId) .. " result=" .. tostring(moved))
    if moved == false then
        Sys_MsgBox("Find The Box could not move you to the event map. Please contact an administrator.", userId)
    else
        ImperialFindBox_HudUser(userId)
    end
end

local function IFB_InstallCallbacks()
    tMonster = tMonster or {}
    local id = tImperialFindBoxConfig.BoxMonsterId
    if g_ImperialFindBoxOldKill ~= nil and g_ImperialFindBoxOldMonsterId ~= nil and
       tMonster[g_ImperialFindBoxOldMonsterId] ~= nil and
       tMonster[g_ImperialFindBoxOldMonsterId]["tFunction"] ~= nil then
        local callbacks=tMonster[g_ImperialFindBoxOldMonsterId]["tFunction"]
        for index=#callbacks,1,-1 do
            if callbacks[index] == g_ImperialFindBoxOldKill then table.remove(callbacks,index) end
        end
    end
    g_ImperialFindBoxOldKill = nil
    g_ImperialFindBoxOldMonsterId = nil
    tNpcGossip = tNpcGossip or {}; local npcId=tImperialFindBoxConfig.EntryNpcId
    tNpcGossip[npcId]=tNpcGossip[npcId] or DefaultNpc:new{}; local gossip=tNpcGossip[npcId]
    gossip["OptionHidden"]=1; gossip["Text1-1"]={111}; gossip["Text111"]="Find The Box:\nEnter during an active event window?"
    gossip["tOption1-1"]={1,2}; gossip["Option1"]="Enter Find The Box."; gossip["OptionFunc1"]="ImperialFindBox_Join</N>"..npcId
    gossip["Option2"]="Not now."; gossip["OptionFunc2"]="ImperialTournament_CloseDialog</N>"..npcId
end

function ImperialFindBox_Pulse(requestGeneration)
    if requestGeneration ~= ImperialFindBoxRuntime.generation then return end
    IFB_DrainBroadcastQueue()
    local ok = pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]FindTheBoxConfig.lua")
    if not ok then IFB_Log("live config parse failed") end
    local revision=tostring(tImperialFindBoxRevision or "")
    if revision ~= ImperialFindBoxRuntime.revision then ImperialFindBoxRuntime.revision=revision; IFB_InstallCallbacks() end
    local windowToken, remainingSec = nil, 0
    if tImperialFindBoxConfig.Enabled then
        windowToken, remainingSec = IFB_Window(os.date("*t"))
    end
    if windowToken ~= nil and (not ImperialFindBoxRuntime.active or ImperialFindBoxRuntime.runToken ~= windowToken) then
        if ImperialFindBoxRuntime.active then IFB_Stop("The live event configuration changed.") end
        if ImperialFindBoxRuntime.pendingToken ~= windowToken then
            ImperialFindBoxRuntime.pendingToken = windowToken
            ImperialFindBoxRuntime.pendingAt = math.max(os.time()+3, tonumber(ImperialFindBoxRuntime.bootReadyAt) or 0)
            IFB_Log("round queued token="..tostring(windowToken).." at="..tostring(ImperialFindBoxRuntime.pendingAt))
        elseif os.time() >= (tonumber(ImperialFindBoxRuntime.pendingAt) or 0) then
            ImperialFindBoxRuntime.pendingToken = ""
            ImperialFindBoxRuntime.pendingAt = 0
            IFB_Start(windowToken, remainingSec)
        end
    elseif windowToken == nil and ImperialFindBoxRuntime.active then
        IFB_Stop("The event window closed.")
    end
    if windowToken == nil then
        ImperialFindBoxRuntime.pendingToken = ""
        ImperialFindBoxRuntime.pendingAt = 0
    end
    if ImperialFindBoxRuntime.active then
        if remainingSec > 0 then ImperialFindBoxRuntime.windowEndEpoch = os.time() + remainingSec end
        IFB_CheckRefill()
        if Map_UserExeFunc ~= nil then
            pcall(Map_UserExeFunc, tImperialFindBoxConfig.MapId, -1, "ImperialFindBox_HudUser")
        end
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialFindBox_Pulse</N>"..tostring(requestGeneration)) end
end

IFB_InstallCallbacks()
ImperialFindBoxRuntime.active = false
ImperialFindBoxRuntime.runToken = nil
ImperialFindBoxRuntime.pendingToken = ""
ImperialFindBoxRuntime.pendingAt = 0
if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(2,"ImperialFindBox_Pulse</N>"..tostring(generation)) end
