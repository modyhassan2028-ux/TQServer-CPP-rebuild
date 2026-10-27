-- Imperial NPC Patrol - server-authoritative one-tile movement for MsgServer 6173.
-- Explicit panel-authored waypoints avoid unsafe pathfinding through blocked cells.

ImperialNpcPatrolRuntime = ImperialNpcPatrolRuntime or {
    revision="", routes={}, pulse_busy=false, timer_generation=0, last_config_load=0,
    live_control_revision=""
}
ImperialNpcPatrolRuntime.timer_generation=(ImperialNpcPatrolRuntime.timer_generation or 0)+1
local imperialNpcPatrolTimerGeneration=ImperialNpcPatrolRuntime.timer_generation
local imperialNpcPatrolConfigPath="lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]NpcPatrolConfig.lua"
local imperialNpcLiveControlPath="lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]NpcLiveControl.lua"

-- The panel edits only the config. Reload it in-process so Save Live is honest
-- and never requires a MsgServer restart.
local function INP_ReloadConfig(now)
    if now-(ImperialNpcPatrolRuntime.last_config_load or 0)<5 then return end
    ImperialNpcPatrolRuntime.last_config_load=now
    pcall(dofile,imperialNpcPatrolConfigPath)
end

local function INP_Number(value, fallback)
    value=tonumber(value)
    if value==nil then return fallback end
    return math.floor(value)
end

local function INP_MoveSucceeded(value)
    return value~=nil and value~=false and value~=0
end

local function INP_Refresh()
    local revision=tostring(tImperialNpcPatrolRevision or "")
    if ImperialNpcPatrolRuntime.revision==revision then return end
    ImperialNpcPatrolRuntime.revision=revision
    local old=ImperialNpcPatrolRuntime.routes
    local nextState={}
    local routes=(tImperialNpcPatrolConfig and tImperialNpcPatrolConfig.Routes) or {}
    for index,route in ipairs(routes) do
        local npcId=INP_Number(route.NpcId,0)
        local points=type(route.Points)=="table" and route.Points or {}
        if npcId>0 and #points>=2 then
            local previous=old[npcId]
            nextState[npcId]={
                config=route, target=previous and previous.target or 1,
                direction=previous and previous.direction or 1,
                last_move=previous and previous.last_move or 0,
                last_talk=previous and previous.last_talk or 0,
                message_index=previous and previous.message_index or 0,
                move_confirmed=previous and previous.move_confirmed or false,
            }
        end
    end
    ImperialNpcPatrolRuntime.routes=nextState
end

-- The control panel writes one idempotent position command at a time. Static
-- cq_npc rows remain owned by the native server; this bridge only asks the
-- verified NpcMove interface to publish the new position to online clients.
local function INP_ProcessLiveControl()
    local loaded=pcall(dofile,imperialNpcLiveControlPath)
    if not loaded then return end
    local revision=tostring(tImperialNpcLiveRevision or "")
    if revision=="" or revision==ImperialNpcPatrolRuntime.live_control_revision then return end
    local command=tImperialNpcLiveCommand
    if type(command)~="table" or tostring(command.Operation or "")~="move" then return end
    local npcId=INP_Number(command.NpcId,0)
    local mapId=INP_Number(command.MapId,0)
    local x=INP_Number(command.X,0)
    local y=INP_Number(command.Y,0)
    if npcId<=0 or mapId<=0 or x<=0 or y<=0 or x>2000 or y>2000 then return end
    if INP_MoveSucceeded(Npc_MoveNpcPos(npcId,mapId,x,y)) then
        ImperialNpcPatrolRuntime.live_control_revision=revision
    end
end

local function INP_Talk(state,now)
    local route=state.config
    local messages=type(route.Messages)=="table" and route.Messages or {}
    -- A broadcast is not proof that the configured NPC exists on this map.
    -- Speak only after the native move owner confirms the actor is active.
    if state.move_confirmed~=true or #messages==0 or Map_SendBroadcastMsg==nil then return end
    local seconds=math.max(15,math.min(3600,INP_Number(route.TalkSeconds,45)))
    if now-state.last_talk<seconds then return end
    state.last_talk=now
    state.message_index=(state.message_index % #messages)+1
    local name=tostring(route.Name or "Town Civilian"):sub(1,32)
    local message=tostring(messages[state.message_index] or ""):gsub("[\r\n]"," "):sub(1,120)
    if message~="" then Map_SendBroadcastMsg(INP_Number(route.MapId,1002),"["..name.."] "..message) end
end

local function INP_NextTarget(state)
    local points=state.config.Points
    local target=state.target+state.direction
    if target>#points then
        if state.config.Loop==false then state.direction=-1 target=#points-1
        else target=1 end
    elseif target<1 then state.direction=1 target=2 end
    state.target=math.max(1,math.min(#points,target))
end

local function INP_Move(state, now)
    local route=state.config
    local seconds=math.max(1,math.min(60,INP_Number(route.StepSeconds,1)))
    if now-state.last_move<seconds then return end
    state.last_move=now
    local npcId=INP_Number(route.NpcId,0)
    local mapId=INP_Number(route.MapId,0)
    local point=route.Points[state.target]
    if npcId<=0 or mapId<=0 or type(point)~="table" then return end
    local currentX=INP_Number(Get_NpcPositionX(npcId),INP_Number(point[1],1))
    local currentY=INP_Number(Get_NpcPositionY(npcId),INP_Number(point[2],1))
    local targetX=INP_Number(point[1],currentX)
    local targetY=INP_Number(point[2],currentY)
    if currentX==targetX and currentY==targetY then
        if state.move_confirmed~=true then
            state.move_confirmed=INP_MoveSucceeded(Npc_MoveNpcPos(npcId,mapId,currentX,currentY))
            if state.move_confirmed~=true then return end
        end
        INP_NextTarget(state)
        return
    end
    local nextX=currentX
    local nextY=currentY
    if currentX<targetX then nextX=currentX+1 elseif currentX>targetX then nextX=currentX-1 end
    if currentY<targetY then nextY=currentY+1 elseif currentY>targetY then nextY=currentY-1 end
    state.move_confirmed=INP_MoveSucceeded(Npc_MoveNpcPos(npcId,mapId,nextX,nextY))
end

function ImperialNpcPatrol_Pulse(generation)
    generation=tonumber(generation) or imperialNpcPatrolTimerGeneration
    if generation~=ImperialNpcPatrolRuntime.timer_generation then return end
    if ImperialNpcPatrolRuntime.pulse_busy then return end
    ImperialNpcPatrolRuntime.pulse_busy=true
    pcall(function()
        local now=os.time()
        INP_ReloadConfig(now)
        INP_Refresh()
        INP_ProcessLiveControl()
        if tImperialNpcPatrolConfig and tImperialNpcPatrolConfig.Enabled==true then
            for _,state in pairs(ImperialNpcPatrolRuntime.routes) do INP_Move(state,now); INP_Talk(state,now) end
        end
    end)
    ImperialNpcPatrolRuntime.pulse_busy=false
    if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(1,"ImperialNpcPatrol_Pulse</N>"..tostring(generation)) end
end

pcall(dofile,imperialNpcPatrolConfigPath)
if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(1,"ImperialNpcPatrol_Pulse</N>"..tostring(imperialNpcPatrolTimerGeneration)) end
