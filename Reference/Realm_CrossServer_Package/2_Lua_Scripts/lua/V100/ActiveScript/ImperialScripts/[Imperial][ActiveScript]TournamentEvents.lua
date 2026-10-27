-- Imperial tournament registrations and MsgServer callbacks.

tNpcFace = tNpcFace or {}
tNpcFace[31] = 32 -- lookface 310: LMS and Skill Survival coordinators

tNpcGossip = tNpcGossip or {}
local function ITC_RegisterEventNpc(config)
    local npcId = config.NPC_ID
    local tournamentId = tonumber(config.ID) or 0
    tNpcGossip[npcId] = tNpcGossip[npcId] or DefaultNpc:new{}
    local gossip = tNpcGossip[npcId]
    gossip["OptionHidden"] = 1
    gossip["Text1-1"] = {111}
    gossip["Text111"] = config.NAME .. ":\nRegistration is open! Do you want to enter?"
    gossip["tOption1-1"] = {1, 2}
    gossip["Option1"] = "Register for the tournament."
    gossip["OptionFunc1"] = "ImperialTournament_Join</N>" .. npcId
    gossip["Option2"] = "Not now."
    gossip["OptionFunc2"] = "ImperialTournament_CloseDialog</N>" .. npcId
    gossip["Text1-2"] = {112}
    gossip["Text112"] = config.NAME .. ":\nRegistration is currently closed."
    gossip["tOption1-2"] = {2}
    gossip["ChkFunc1-1"] = function()
        return TournamentRuntime.state == "REGISTRATION" and
            TournamentRuntime.current ~= nil and
            ((tonumber(TournamentRuntime.current.ID) or -1) == tournamentId or
             (tonumber(TournamentRuntime.current.NPC_ID) or -1) == npcId)
    end
    gossip["ChkFunc1-2"] = function()
        return TournamentRuntime.state ~= "REGISTRATION" or
            TournamentRuntime.current == nil or
            ((tonumber(TournamentRuntime.current.ID) or -1) ~= tournamentId and
             (tonumber(TournamentRuntime.current.NPC_ID) or -1) ~= npcId)
    end
end

function ImperialTournament_RegisterEventNpcs(skipHide)
    for _,config in pairs(tTournamentConfigs) do ITC_RegisterEventNpc(config) end
    if not skipHide and ImperialTournament_HideInactiveCoordinators ~= nil then ImperialTournament_HideInactiveCoordinators() end
end

ImperialTournament_RegisterEventNpcs(true)

tUserKilled = tUserKilled or {}
tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
if g_oldImperialTournamentKillHandler ~= nil then
    for index = #tUserKilled["tFunction"], 1, -1 do
        if tUserKilled["tFunction"][index] == g_oldImperialTournamentKillHandler then table.remove(tUserKilled["tFunction"], index) end
    end
end
g_oldImperialTournamentKillHandler = ImperialTournament_OnKillSignal
table.insert(tUserKilled["tFunction"], ImperialTournament_OnKillSignal)

tOntimerMin_M = tOntimerMin_M or {}
local minute = 0
while minute <= 59 do
    tOntimerMin_M[minute] = tOntimerMin_M[minute] or {}
    if g_oldImperialTournamentTimerHandler ~= nil then
        for index = #tOntimerMin_M[minute], 1, -1 do
            if tOntimerMin_M[minute][index] == g_oldImperialTournamentTimerHandler then table.remove(tOntimerMin_M[minute], index) end
        end
    end
    table.insert(tOntimerMin_M[minute], ImperialTournament_TimerTick)
    minute = minute + 1
end
g_oldImperialTournamentTimerHandler = ImperialTournament_TimerTick

ImperialTournament_StartupRecovery()
