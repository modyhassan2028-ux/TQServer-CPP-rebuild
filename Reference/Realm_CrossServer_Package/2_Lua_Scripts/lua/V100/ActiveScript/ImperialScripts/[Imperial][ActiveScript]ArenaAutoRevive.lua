-- Imperial Arena Auto Revive
-- Native combat writes validated map/user rows; this isolated Lua worker owns
-- the delayed revive so MsgServer combat threads are never blocked.

ImperialArenaAutoReviveRuntime = ImperialArenaAutoReviveRuntime or { generation=0 }
ImperialArenaAutoReviveRuntime.generation = ImperialArenaAutoReviveRuntime.generation + 1
local generation = ImperialArenaAutoReviveRuntime.generation

local function IAR_Log(text)
    if Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[ImperialArenaAutoRevive] " .. tostring(text or ""))
    end
end

function ImperialArenaAutoRevive_Do(userId,mapId,x,y)
    userId,mapId,x,y = tonumber(userId),tonumber(mapId),tonumber(x),tonumber(y)
    if userId == nil or userId < 1000000 or mapId == nil or x == nil or y == nil then return end
    local currentMap = tonumber(Get_UserMapId(userId)) or 0
    if currentMap ~= mapId then
        IAR_Log("cancelled map changed user="..tostring(userId).." map="..tostring(currentMap))
        return
    end
    local life = tonumber(Get_UserLife(userId)) or -1
    if life > 0 then
        IAR_Log("cancelled already alive user="..tostring(userId).." life="..tostring(life))
        return
    end
    local maxLife = tonumber(Get_UserMaxLife(userId)) or 0
    if maxLife <= 0 then return end

    -- Restore life first, then re-enter the exact valid death cell.  The map
    -- change clears ghost/death state and broadcasts a fresh screen object to
    -- nearby clients, preventing stale or invisible bodies.
    local okLife = User_AddLife(maxLife,userId)
    if okLife == false then
        IAR_Log("life restore failed user="..tostring(userId))
        return
    end
    local okMap = User_ChgMap(mapId,x,y,0,userId)
    if okMap == false then
        IAR_Log("screen refresh failed user="..tostring(userId))
    else
        IAR_Log("revived user="..tostring(userId).." map="..tostring(mapId)..
                " x="..tostring(x).." y="..tostring(y))
    end
end

local function IAR_DrainQueue()
    if io == nil or io.open == nil or os == nil or os.rename == nil then return end
    local queuePath,processingPath = "ArenaAutoRevive.queue","ArenaAutoRevive.processing"
    local processing = io.open(processingPath,"r")
    if processing == nil then
        if os.rename(queuePath,processingPath) == nil then return end
        processing = io.open(processingPath,"r")
        if processing == nil then return end
    end
    for line in processing:lines() do
        local userId,mapId,x,y,delay = string.match(line,"^IAR1|(%d+)|(%d+)|(%d+)|(%d+)|(%d+)$")
        userId,mapId,x,y,delay = tonumber(userId),tonumber(mapId),tonumber(x),tonumber(y),tonumber(delay)
        if userId ~= nil and userId >= 1000000 and mapId ~= nil and x ~= nil and y ~= nil and
           delay ~= nil and delay >= 1 and delay <= 60 and User_SetTimer ~= nil then
            local command = string.format("ImperialArenaAutoRevive_Do</N>%d</N>%d</N>%d</N>%d",userId,mapId,x,y)
            local ok = User_SetTimer(delay,command,0,userId)
            if ok == false then
                IAR_Log("timer rejected user="..tostring(userId))
            else
                IAR_Log("scheduled user="..tostring(userId).." delay="..tostring(delay))
            end
        else
            IAR_Log("discarded malformed native queue row")
        end
    end
    processing:close()
    if os.remove ~= nil then pcall(os.remove,processingPath) end
end

function ImperialArenaAutoRevive_Pulse(requestGeneration)
    if requestGeneration ~= ImperialArenaAutoReviveRuntime.generation then return end
    IAR_DrainQueue()
    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(1,"ImperialArenaAutoRevive_Pulse</N>"..tostring(requestGeneration))
    end
end

if Sys_SetLuaTimer ~= nil then
    Sys_SetLuaTimer(1,"ImperialArenaAutoRevive_Pulse</N>"..tostring(generation))
end

-- One startup diagnostic used to bind the server's real native revive API.
-- Keep the filter narrow; no gameplay data is changed here.
if generation == 1 then
    local matches = {}
    for key,value in pairs(_G) do
        if type(value) == "function" then
            local lower = string.lower(tostring(key))
            if string.find(lower,"reviv",1,true) or string.find(lower,"reliv",1,true) or
               string.find(lower,"resur",1,true) or string.find(lower,"reborn",1,true) or
               string.find(lower,"die",1,true) or string.find(lower,"action",1,true) then
                table.insert(matches,tostring(key))
            end
        end
    end
    table.sort(matches)
    IAR_Log("native-api="..table.concat(matches,","))
end
