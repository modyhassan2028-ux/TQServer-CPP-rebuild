--------------------------------------------------------------------------------
-- Imperial Quest Event Manager
-- Multi-monster Lua runtime. Rewards and populations are event-owned and must
-- never be stacked with GlobalDropV2.
--------------------------------------------------------------------------------

pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]QuestEventConfig.lua")

local IQE_PULSE_SECONDS=5
local IQE_CHANCE_MAX=100000

ImperialQuestEventRuntime=ImperialQuestEventRuntime or {state={},generation=0,lastCommandToken="",revision=""}
ImperialQuestEventRuntime.state=ImperialQuestEventRuntime.state or {}
ImperialQuestEventRuntime.generation=(ImperialQuestEventRuntime.generation or 0)+1
ImperialQuestEventRuntime.revision=tostring(tImperialQuestEventRevision or "")
local iqeGeneration=ImperialQuestEventRuntime.generation

local function IQE_Log(text)
    if Sys_SaveAbnormalLog~=nil then Sys_SaveAbnormalLog("[ImperialQuestEvent] "..tostring(text or "")) end
end

local function IQE_Find(key)
    for _,event in ipairs(tImperialQuestEvents or {}) do if event.Key==key then return event end end
    return nil
end

function ImperialQuestEvent_IsOwnedMonster(monsterId)
    local id=tonumber(monsterId) or 0
    for _,event in ipairs(tImperialQuestEvents or {}) do
        if id==(tonumber(event.SourceMonsterId) or 0) or id==(tonumber(event.MonsterId) or 0) then return true end
    end
    return false
end

local function IQE_Replace(text,event,killer,state)
    local result=tostring(text or "")
    result=string.gsub(result,"{event}",tostring(event.Name or event.Key))
    result=string.gsub(result,"{monster}",tostring(event.Name or event.Key))
    result=string.gsub(result,"{killer}",tostring(killer or "Unknown"))
    result=string.gsub(result,"{kills}",tostring(state and state.kills or 0))
    result=string.gsub(result,"{target}",tostring(event.TotalKills or 0))
    return result
end

local function IQE_Broadcast(text)
    if tostring(text or "")~="" and Sys_SystemBroadcast~=nil then Sys_SystemBroadcast(text) end
end

local function IQE_Count(event)
    local total,seen=0,{}
    for _,location in ipairs(event.Locations or {}) do
        if location.Enabled and not seen[location.MapId] then
            seen[location.MapId]=true
            total=total+(tonumber(Monster_GetMonsterByGenId(location.MapId,event.GeneratorId)) or 0)
        end
    end
    return total
end

local function IQE_PickLocation(event)
    local total=0
    for _,location in ipairs(event.Locations or {}) do if location.Enabled then total=total+math.max(0,tonumber(location.Weight) or 0) end end
    if total<=0 then return nil end
    local roll=math.random(1,total)
    for _,location in ipairs(event.Locations or {}) do
        if location.Enabled then
            roll=roll-math.max(0,tonumber(location.Weight) or 0)
            if roll<=0 then return location end
        end
    end
    return nil
end

local function IQE_SpawnOne(event)
    local location=IQE_PickLocation(event)
    if location==nil then return false end
    local radius=math.max(0,tonumber(location.Radius) or 0)
    local x=math.max(1,(tonumber(location.X) or 1)+(radius>0 and math.random(-radius,radius) or 0))
    local y=math.max(1,(tonumber(location.Y) or 1)+(radius>0 and math.random(-radius,radius) or 0))
    return Monster_AddMonster(location.MapId,x,y,event.GeneratorId,event.MonsterId)~=false
end

local function IQE_Remove(event)
    local seen={}
    for _,location in ipairs(event.Locations or {}) do
        if location.Enabled and not seen[location.MapId] then seen[location.MapId]=true; Monster_DelMonster(location.MapId,event.MonsterId) end
    end
end

local function IQE_SelectRewards(event)
    local pools,order={},{}
    for _,reward in ipairs(event.Rewards or {}) do
        if reward.Enabled then
            local pool=tostring(reward.Pool or "default")
            if pools[pool]==nil then pools[pool]={};table.insert(order,pool) end
            table.insert(pools[pool],reward)
        end
    end
    local selected={}
    for _,pool in ipairs(order) do
        local rewards=pools[pool]
        local mode=tostring(rewards[1].Mode or "Independent")
        if mode=="Guaranteed" then
            for _,reward in ipairs(rewards) do table.insert(selected,reward) end
        elseif mode=="WeightedOne" then
            local total=0
            for _,reward in ipairs(rewards) do total=total+math.max(0,tonumber(reward.Chance) or 0) end
            if total>0 then
                local roll=math.random(1,total)
                for _,reward in ipairs(rewards) do
                    roll=roll-math.max(0,tonumber(reward.Chance) or 0)
                    if roll<=0 then table.insert(selected,reward);break end
                end
            end
        else
            for _,reward in ipairs(rewards) do if math.random(1,IQE_CHANCE_MAX)<=(tonumber(reward.Chance) or 0) then table.insert(selected,reward) end end
        end
    end
    return selected
end

local function IQE_Deliver(event,userId)
    for _,reward in ipairs(IQE_SelectRewards(event)) do
        local amount=math.max(1,tonumber(reward.Amount) or 1)
        local value=math.max(0,tonumber(reward.Value) or 0)
        if reward.Kind=="Item" then
            for _=1,amount do
                if reward.Delivery=="Ground" then Monster_SysDropItem(value,userId)
                else Item_AddItem(value,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,userId) end
            end
        elseif reward.Kind=="Silver" and User_AddMoney~=nil then User_AddMoney(value*amount,userId)
        elseif reward.Kind=="CPs" and User_AddEMoney~=nil then User_AddEMoney(value*amount,userId)
        elseif reward.Kind=="BoundCPs" and User_AddEMoneyMono~=nil then User_AddEMoneyMono(value*amount,userId) end
    end
end

function ImperialQuestEvent_Start(key,manual)
    local event=IQE_Find(key)
    if event==nil or (not manual and not event.Enabled) or (tonumber(event.MonsterId) or 0)<=0 or (tonumber(event.GeneratorId) or 0)<=0 then return false end
    local now=os.time()
    local state=ImperialQuestEventRuntime.state[key] or {}
    if state.active then return false end
    if not manual and now<(tonumber(state.nextAllowedAt) or 0) then return false end
    state.active=true;state.kills=0;state.startedAt=now;state.nextRespawnAt=now
    ImperialQuestEventRuntime.state[key]=state
    IQE_Broadcast(IQE_Replace(event.StartMessage,event,"",state))
    IQE_Log("started key="..key)
    return true
end

function ImperialQuestEvent_Stop(key,reason)
    local event=IQE_Find(key)
    if event==nil then return false end
    local state=ImperialQuestEventRuntime.state[key] or {}
    IQE_Remove(event)
    state.active=false;state.startedAt=nil;state.nextRespawnAt=nil
    state.nextAllowedAt=os.time()+math.max(0,tonumber(event.RestartDelayMinutes) or 0)*60
    ImperialQuestEventRuntime.state[key]=state
    IQE_Broadcast(IQE_Replace(event.EndMessage,event,"",state))
    IQE_Log("stopped key="..key.." reason="..tostring(reason or "manual"))
    return true
end

function ImperialQuestEvent_OnKilled(key)
    local event=IQE_Find(key)
    if event==nil then return end
    local state=ImperialQuestEventRuntime.state[key] or {}
    if not state.active then return end
    local userId=tonumber(Get_UserId()) or 0
    if userId<=0 then return end
    state.kills=(tonumber(state.kills) or 0)+1
    state.nextRespawnAt=os.time()+math.max(0,tonumber(event.RespawnSeconds) or 0)
    ImperialQuestEventRuntime.state[key]=state
    IQE_Deliver(event,userId)
    IQE_Broadcast(IQE_Replace(event.KillMessage,event,Get_UserName(userId) or "Unknown",state))
    local target=tonumber(event.TotalKills) or 0
    if target>0 and state.kills>=target then ImperialQuestEvent_Stop(key,"kill target") end
end

local function IQE_DayAllowed(event,day)
    for _,configured in ipairs(event.Days or {}) do if configured==day then return true end end
    return false
end

local function IQE_Schedule(event,now)
    if not event.Enabled or not event.AutoSchedule or not IQE_DayAllowed(event,now.wday-1) then return end
    local hhmm=string.format("%02d:%02d",now.hour,now.min)
    for _,configured in ipairs(event.Times or {}) do
        if configured==hhmm then
            local token=os.date("%Y%m%d")..":"..hhmm
            local state=ImperialQuestEventRuntime.state[event.Key] or {}
            if state.lastScheduleToken~=token then state.lastScheduleToken=token;ImperialQuestEventRuntime.state[event.Key]=state;ImperialQuestEvent_Start(event.Key,false) end
        end
    end
end

local function IQE_Run(event,now)
    local state=ImperialQuestEventRuntime.state[event.Key]
    if state==nil or not state.active then return end
    local duration=tonumber(event.DurationMinutes) or 0
    if duration>0 and now-(tonumber(state.startedAt) or now)>=duration*60 then ImperialQuestEvent_Stop(event.Key,"duration");return end
    local alive=IQE_Count(event)
    local maximum=math.max(1,tonumber(event.MaxAlive) or 1)
    if alive>=maximum or now<(tonumber(state.nextRespawnAt) or 0) then return end
    local count=math.min(maximum-alive,math.max(1,tonumber(event.SpawnBatch) or 1))
    local spawned=0
    for _=1,count do if IQE_SpawnOne(event) then spawned=spawned+1 end end
    if spawned>0 and tostring(event.SpawnMessage or "")~="" then IQE_Broadcast(IQE_Replace(event.SpawnMessage,event,"",state)) end
    state.nextRespawnAt=now+math.max(0,tonumber(event.RespawnSeconds) or 0)
    ImperialQuestEventRuntime.state[event.Key]=state
end

local function IQE_InstallHandlers()
    if type(g_ImperialQuestEventOldHandlers)=="table" and type(tMonster)=="table" then
        for monsterId,old in pairs(g_ImperialQuestEventOldHandlers) do
            local functions=tMonster[monsterId] and tMonster[monsterId]["tFunction"]
            if type(functions)=="table" then for index=#functions,1,-1 do if functions[index]==old then table.remove(functions,index) end end end
        end
    end
    g_ImperialQuestEventOldHandlers={};tMonster=tMonster or {}
    for _,event in ipairs(tImperialQuestEvents or {}) do
        local monsterId=tonumber(event.MonsterId) or 0
        if monsterId>0 then
            local key=event.Key
            local handler=function() ImperialQuestEvent_OnKilled(key) end
            tMonster[monsterId]=tMonster[monsterId] or {};tMonster[monsterId]["tFunction"]=tMonster[monsterId]["tFunction"] or {}
            table.insert(tMonster[monsterId]["tFunction"],handler);g_ImperialQuestEventOldHandlers[monsterId]=handler
        end
    end
end

local function IQE_ProcessCommand()
    local command=tImperialQuestEventCommand
    if type(command)~="table" or tostring(command.Token or "")==ImperialQuestEventRuntime.lastCommandToken then return end
    ImperialQuestEventRuntime.lastCommandToken=tostring(command.Token or "")
    if command.Action=="start" then ImperialQuestEvent_Start(command.EventKey,true)
    elseif command.Action=="stop" then ImperialQuestEvent_Stop(command.EventKey,"manual")
    elseif command.Action=="reset" then ImperialQuestEvent_Stop(command.EventKey,"reset");local state=ImperialQuestEventRuntime.state[command.EventKey] or {};state.kills=0;state.nextAllowedAt=0;ImperialQuestEventRuntime.state[command.EventKey]=state end
end

function ImperialQuestEvent_Refresh()
    local ok,message=pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]QuestEventConfig.lua")
    if not ok then IQE_Log("config rejected: "..tostring(message));return false end
    local revision=tostring(tImperialQuestEventRevision or "")
    if revision~=ImperialQuestEventRuntime.revision then ImperialQuestEventRuntime.revision=revision;IQE_InstallHandlers();IQE_ProcessCommand();IQE_Log("config applied revision="..revision) end
    return true
end

function ImperialQuestEvent_Pulse(requestGeneration)
    if requestGeneration~=ImperialQuestEventRuntime.generation then return end
    ImperialQuestEvent_Refresh()
    local nowTable,now=os.date("*t"),os.time()
    for _,event in ipairs(tImperialQuestEvents or {}) do IQE_Schedule(event,nowTable);IQE_Run(event,now) end
    if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(IQE_PULSE_SECONDS,"ImperialQuestEvent_Pulse</N>"..tostring(requestGeneration)) end
end

IQE_InstallHandlers();IQE_ProcessCommand()
if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(2,"ImperialQuestEvent_Pulse</N>"..tostring(iqeGeneration)) end
