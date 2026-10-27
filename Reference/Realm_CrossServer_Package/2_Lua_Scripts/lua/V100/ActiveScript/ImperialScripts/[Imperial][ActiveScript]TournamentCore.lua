-- Imperial Tournament Core for MsgServer 6173 / Lua 5.1.
-- Native combat callbacks only enqueue identifiers. Score/elimination state,
-- rewards and cleanup always execute later on the guarded Lua timer.

local previousRunId = 0
if type(TournamentRuntime) == "table" then previousRunId = tonumber(TournamentRuntime.run_id) or 0 end

TournamentRuntime = {
    state = "IDLE", current = nil, run_id = previousRunId + 1,
    participants = {}, map_users = {}, rewarded = {},
    registration_deadline = 0, match_deadline = 0,
    pending_kills = {}, pending_scores = {}, announcements = {},
    pulse_busy = false, registration_pulse_busy = false,
    spawn_rotation = 0, dragon_holder = 0, recent_kill_pairs = {},
}
TournamentConfigRuntime = TournamentConfigRuntime or {generation=0,revision=""}
TournamentConfigRuntime.generation=(TournamentConfigRuntime.generation or 0)+1
TournamentConfigRuntime.revision=tostring(tTournamentConfigRevision or "")
local tournamentConfigGeneration=TournamentConfigRuntime.generation

local function ITC_System()
    return tTournamentSystemConfig
end

local function ITC_AllConfigs()
    local list = {}
    for key, config in pairs(tTournamentConfigs or {}) do
        list[key] = config
    end
    for key, config in pairs(tTournamentExtraConfigs or {}) do
        if list[key] == nil then list[key] = config end
    end
    return list
end

local function ITC_Now()
    if os ~= nil and os.time ~= nil then return tonumber(os.time()) or 0 end
    return 0
end

local function ITC_SecondsLeft(deadline)
    if deadline == nil or deadline <= 0 then return 0 end
    return math.max(0, deadline - ITC_Now())
end

local function ITC_FormatTime(seconds)
    seconds = math.max(0, math.floor(tonumber(seconds) or 0))
    return string.format("%02d:%02d", math.floor(seconds / 60), seconds % 60)
end

local function ITC_Count(value)
    local count = 0
    for _,_ in pairs(value or {}) do count = count + 1 end
    return count
end

local function ITC_MessageUser(userId, text)
    if userId ~= nil and userId > 0 then User_TalkChannel2005(tostring(text or ""), userId) end
end

local function ITC_Broadcast(text)
    Sys_SystemBroadcast("[Tournament] " .. tostring(text or ""))
end

local function ITC_MapBroadcast(text)
    if TournamentRuntime.current ~= nil then
        Map_SendBroadcastMsg(TournamentRuntime.current.MAP_ID, "[Tournament] " .. tostring(text or ""))
    end
end

local function ITC_HudLine(userId, channel, text)
    if userId ~= nil and userId > 0 and Talk ~= nil then Talk(userId, channel, tostring(text or "")) end
end

local function ITC_Hud(userId, title, lines)
    ITC_HudLine(userId, 2108, title)
    for _,line in ipairs(lines or {}) do ITC_HudLine(userId, 2109, line) end
end

local function ITC_ClearHud(userId)
    ITC_HudLine(userId, 2108, "")
end

local function ITC_ResetRuntime()
    TournamentRuntime.state = "IDLE"
    TournamentRuntime.current = nil
    TournamentRuntime.participants = {}
    TournamentRuntime.map_users = {}
    TournamentRuntime.rewarded = {}
    TournamentRuntime.registration_deadline = 0
    TournamentRuntime.match_deadline = 0
    TournamentRuntime.pending_kills = {}
    TournamentRuntime.pending_scores = {}
    TournamentRuntime.announcements = {}
    TournamentRuntime.pulse_busy = false
    TournamentRuntime.registration_pulse_busy = false
    TournamentRuntime.spawn_rotation = 0
    TournamentRuntime.dragon_holder = 0
    TournamentRuntime.recent_kill_pairs = {}
end

local function ITC_FileExists(path)
    if io == nil or io.open == nil then return false end
    local ok, file = pcall(io.open, path, "r")
    if ok and file ~= nil then file:close() return true end
    return false
end

local function ITC_RewardBridgeToken()
    if io == nil or io.open == nil then return nil, "lua-io-unavailable" end
    local ok, file = pcall(io.open, "TournamentRewardMail.ready", "rb")
    if not ok or file == nil then return nil, "bridge-marker-open-failed" end
    local readOk, content = pcall(function() return file:read("*a") end)
    pcall(function() file:close() end)
    if not readOk then return nil, "bridge-marker-read-failed" end
    local token = string.match(tostring(content or ""), "ITR3%s+([0-9]+_[0-9]+)")
    if token == nil or token == "" then return nil, "bridge-marker-format-invalid" end
    return token, nil
end

local function ITC_RewardUnavailable(userId, reason)
    reason = tostring(reason or "unknown")
    if Sys_SaveAbnormalLog ~= nil then
        pcall(Sys_SaveAbnormalLog, "[ImperialTournament][Reward] unavailable user=" .. tostring(userId) .. " reason=" .. reason)
    end
    ITC_MessageUser(userId, "Reward delivery is temporarily unavailable; please contact an administrator. [" .. reason .. "]")
end

local function ITC_ApplyRewardExtras(userId, config)
    local experience = math.max(0, tonumber(config.REWARD_EXP) or 0)
    if experience > 0 and User_AddExp ~= nil then User_AddExp(experience, userId) end

    local status = math.max(0, math.floor(tonumber(config.REWARD_STATUS) or 0))
    if status <= 0 or User_AddRoleStatus == nil then return end
    local power = math.max(0, math.floor(tonumber(config.REWARD_STATUS_POWER) or 200))
    local seconds = math.max(1, math.min(315360000, math.floor(tonumber(config.REWARD_STATUS_SECONDS) or 86400)))
    if User_ChkRoleStatus ~= nil and User_ChkRoleStatus(status, userId) and User_DelRoleStatus ~= nil then
        User_DelRoleStatus(status, userId)
    end
    User_AddRoleStatus(status, power, 0, seconds, 0, seconds, 1, 0, 0, userId)
end

local function ITC_RewardUser(userId, config)
    if userId == nil or userId <= 0 or config == nil or TournamentRuntime.rewarded[userId] then return end

    local count = math.max(0, tonumber(config.REWARD_ITEM_COUNT) or 0)
    local itemId = tonumber(config.REWARD_ITEM_ID) or 0
    if itemId <= 0 then count = 0 end
    local money = math.max(0, tonumber(config.REWARD_MONEY) or 0)
    local emoney = math.max(0, tonumber(config.REWARD_EMONEY) or 0)

    if count == 0 and money == 0 and emoney == 0 then
        TournamentRuntime.rewarded[userId] = true
        ITC_ApplyRewardExtras(userId, config)
        ITC_MessageUser(userId, "Your tournament reward has been delivered.")
        return
    end

    local stackLimit = 1
    if count > 0 and Get_ItemtypeAccumulateLimit ~= nil then
        stackLimit = tonumber(Get_ItemtypeAccumulateLimit(itemId)) or 1
        if stackLimit < 1 then stackLimit = 1 end
    end
    -- Native Auction mail accepts one live CItem per transaction. Stackable
    -- quantities remain one CItem; non-stackable quantities above one fail
    -- before creating anything, preventing partial multi-mail rewards.
    if count > 1 and stackLimit <= 1 then
        ITC_RewardUnavailable(userId, "non-stackable-count-must-be-one")
        return
    end
    if count > stackLimit then
        ITC_RewardUnavailable(userId, "reward-count-exceeds-stack-limit")
        return
    end

    local stamp = nil
    if os ~= nil and os.time ~= nil then stamp = os.time() end
    local bridgeToken, bridgeError = ITC_RewardBridgeToken()
    if stamp == nil then ITC_RewardUnavailable(userId, "lua-time-unavailable") return end
    if io == nil or io.open == nil then ITC_RewardUnavailable(userId, "lua-io-unavailable") return end
    if os == nil or os.rename == nil then ITC_RewardUnavailable(userId, "lua-rename-unavailable") return end
    if bridgeToken == nil then ITC_RewardUnavailable(userId, bridgeError) return end

    local token = tostring(stamp) .. "_" .. tostring(userId) .. "_" .. tostring(config.ID or 0)
    local base = "TournamentRewardQueue\\" .. token
    local tempPath = base .. ".tmp"
    local requestPath = base .. ".req"
    local donePath = base .. ".nativeprocessing.done"
    local opened, file = pcall(io.open, tempPath, "w")
    if not opened or file == nil then ITC_RewardUnavailable(userId, "reward-queue-open-failed") return end

    local function abortQueue(message)
        pcall(function() file:close() end)
        if os ~= nil and os.remove ~= nil then pcall(os.remove, tempPath) end
        ITC_MessageUser(userId, message)
    end

    local itemUid = 0
    if count > 0 then
        if Item_AddNewItem == nil or GetLastAddItemID == nil then
            abortQueue("Native item reward delivery is unavailable; please contact an administrator.")
            return
        end
        local itemAttr = config.REWARD_ITEM_ATTR or ""
        if count > 1 then itemAttr = "0 " .. tostring(count) end
        if not Item_AddNewItem(itemId, itemAttr, userId) then
            abortQueue("The native reward item could not be created; please contact an administrator.")
            return
        end
        itemUid = tonumber(GetLastAddItemID(userId)) or 0
        if itemUid <= 0 then
            abortQueue("The native reward item UID could not be resolved; please contact an administrator.")
            return
        end
    end

    local itemCount = itemUid > 0 and 1 or 0
    file:write("ITR3 ", bridgeToken, " ", token, " ", userId, " ", money, " ", emoney, " 0 ", config.ID or 0, " ", itemCount)
    if itemUid > 0 then file:write(" ", itemUid) end
    file:write("\n")
    file:flush()
    file:close()
    if os.rename(tempPath, requestPath) == nil then
        ITC_RewardUnavailable(userId, "reward-queue-publish-failed")
        return
    end

    -- This exported Lua getter is hooked only as a safe game-thread signal.
    GetLastAddItemID(userId)
    TournamentRuntime.rewarded[userId] = true
    ITC_ApplyRewardExtras(userId, config)
    if ITC_FileExists(donePath) then
        ITC_MessageUser(userId, "Your complete tournament reward was delivered to your mailbox.")
    elseif ITC_FileExists(base .. ".nativeprocessing.review") then
        ITC_MessageUser(userId, "Your tournament reward needs delivery verification. Please contact an administrator; do not repeat the claim.")
    else
        ITC_MessageUser(userId, "Your tournament reward is awaiting mailbox delivery confirmation.")
    end
end

local function ITC_HideCoordinator(config)
    if config == nil then return end
    if (config.NPC_ALWAYS_VISIBLE or 0) == 1 then return end
    Npc_MoveNpcPos(config.NPC_ID, config.NPC_MAP_ID, config.NPC_HIDE_X, config.NPC_HIDE_Y)
end

local function ITC_ShowCoordinator(config)
    if config ~= nil and (config.NPC_ALWAYS_VISIBLE or 0) ~= 1 then
        Npc_MoveNpcPos(config.NPC_ID, config.NPC_MAP_ID, config.NPC_X, config.NPC_Y)
    end
end

function ImperialTournament_HideInactiveCoordinators()
    for _,config in pairs(ITC_AllConfigs()) do
        if TournamentRuntime.state ~= "REGISTRATION" or TournamentRuntime.current ~= config then ITC_HideCoordinator(config) end
    end
end

local function ITC_RestoreVitals(userId)
    if userId == nil or userId <= 0 then return end
    local life = GetUserInt(userId, G_PLAYER_Life) or 0
    local maxLife = GetUserInt(userId, G_PLAYER_MaxLife) or 0
    if maxLife > life then User_AddLife(maxLife - life, userId) end
    local mana = GetUserInt(userId, G_PLAYER_Mana) or 0
    local maxMana = GetUserInt(userId, G_PLAYER_MaxMana) or 0
    if maxMana > mana and User_AddMana ~= nil then User_AddMana(maxMana - mana, userId) end
end

local function ITC_ReturnUser(userId)
    if userId == nil or userId <= 0 then return end
    local system = ITC_System()
    local data = TournamentRuntime.participants[userId]
    if data ~= nil and data.pk_before ~= nil then
        local currentPk = GetUserInt(userId, G_PLAYER_PK)
        if currentPk ~= nil and currentPk ~= data.pk_before then User_AddPk(data.pk_before - currentPk, userId) end
    end
    ITC_RestoreVitals(userId)
    ITC_ClearHud(userId)
    User_ChgMap(system.RETURN_MAP_ID, system.RETURN_X, system.RETURN_Y, 0, userId)
end

function ImperialTournament_ReturnMapUser(userId)
    userId = userId or Get_UserId()
    ITC_ReturnUser(userId)
end

function ImperialTournament_CaptureMapUser(userId)
    userId = userId or Get_UserId()
    if userId ~= nil and userId > 0 and TournamentRuntime.participants[userId] ~= nil then
        TournamentRuntime.map_users[userId] = true
    end
end

local function ITC_RefreshMapUsers()
    TournamentRuntime.map_users = {}
    if TournamentRuntime.current ~= nil then
        Map_UserExeFunc(TournamentRuntime.current.MAP_ID, -1, "ImperialTournament_CaptureMapUser")
    end
    return ITC_Count(TournamentRuntime.map_users)
end

local function ITC_CleanupMap(config)
    if config ~= nil then Map_UserExeFunc(config.MAP_ID, -1, "ImperialTournament_ReturnMapUser") end
end

local function ITC_OnlySurvivor()
    local survivor = 0
    local count = 0
    for userId,_ in pairs(TournamentRuntime.map_users) do
        survivor = userId
        count = count + 1
    end
    if count == 1 then return survivor end
    return 0
end

local function ITC_TopScoreEntries(limit)
    limit = math.max(1, tonumber(limit) or 5)
    local rows = {}
    for participantId,_ in pairs(TournamentRuntime.map_users) do
        local participant = TournamentRuntime.participants[participantId]
        if participant ~= nil then
            table.insert(rows, {
                userId = participantId,
                name = participant.name or Get_UserName(participantId) or tostring(participantId),
                score = tonumber(participant.score) or 0,
            })
        end
    end
    table.sort(rows, function(a, b)
        if a.score ~= b.score then return a.score > b.score end
        return a.userId < b.userId
    end)
    local top = {}
    for index = 1, math.min(limit, #rows) do
        table.insert(top, "*" .. tostring(index) .. "- " .. rows[index].name .. " : " .. tostring(rows[index].score))
    end
    return top
end

local function ITC_ShowRegistrationHud(userId)
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "REGISTRATION" then return end
    ITC_Hud(userId, "[" .. config.NAME .. "]", {
        "Status: Registered",
        "Starts in: " .. ITC_FormatTime(ITC_SecondsLeft(TournamentRuntime.registration_deadline)),
        "Players: " .. ITC_Count(TournamentRuntime.participants) .. "/" .. config.MAX_PLAYERS,
        "Minimum: " .. config.MIN_PLAYERS,
    })
end

local function ITC_ShowRunningHud(userId)
    local config = TournamentRuntime.current
    local data = TournamentRuntime.participants[userId]
    if config == nil or data == nil or not TournamentRuntime.map_users[userId] then return end
    local remainingSec = ITC_SecondsLeft(TournamentRuntime.match_deadline)
    local timeText = "Time left " .. ITC_FormatTime(remainingSec)
    local fightersCount = ITC_Count(TournamentRuntime.map_users)

    if config.MODE == "COOKING" then
        ITC_Hud(userId, "~~ " .. config.NAME .. " ~~", {
            "Score: " .. tostring(tonumber(data.score) or 0) .. " | Hunger: " .. tostring(tonumber(data.hunger) or 0),
            "Wood: " .. tostring(tonumber(data.wood) or 0) .. " | Water: " .. tostring(tonumber(data.water) or 0) .. " | Food: " .. tostring(tonumber(data.food) or 0),
            ((tonumber(data.fire_until) or 0) > ITC_Now()) and "Campfire: active" or "Campfire: not active",
            timeText,
        })
    elseif config.MODE == "SCORE" then
        local lines = ITC_TopScoreEntries(5)
        table.insert(lines, "-------------------")
        table.insert(lines, "Your Points: " .. tostring(tonumber(data.score) or 0) .. " (Streak: " .. tostring(tonumber(data.streak) or 0) .. ")")
        table.insert(lines, "Fighters: " .. tostring(fightersCount))
        table.insert(lines, timeText)
        ITC_Hud(userId, "[" .. config.NAME .. "]", lines)
    elseif config.MODE == "KNOCKOUT" then
        local maxHits = math.max(1, tonumber(config.MAX_HITS) or 5)
        local hitsLeft = math.max(0, maxHits - (tonumber(data.hits_taken) or 0))
        ITC_Hud(userId, "[" .. config.NAME .. "]", {
            "Survivors: " .. tostring(fightersCount),
            "Hits Remaining: " .. tostring(hitsLeft),
            "Hits Dealt: " .. tostring(tonumber(data.score) or 0),
            "-------------------",
            timeText,
        })
    elseif config.MODE == "KOTH" then
        local lines = ITC_TopScoreEntries(5)
        table.insert(lines, "-------------------")
        table.insert(lines, "Your Score: " .. tostring(tonumber(data.score) or 0) .. " / " .. tostring(tonumber(config.SCORE_LIMIT) or 300))
        if data.on_hill then
            table.insert(lines, "Status: ON THE HILL! (+" .. tostring(tonumber(config.HILL_POINTS_PER_SEC) or 5) .. " pts/sec)")
        else
            table.insert(lines, "Status: Off the hill")
        end
        table.insert(lines, "Fighters: " .. tostring(fightersCount))
        table.insert(lines, timeText)
        ITC_Hud(userId, "[" .. config.NAME .. "]", lines)
    elseif config.MODE == "DRAGON_PVP" then
        local lines = ITC_TopScoreEntries(5)
        local holderName = "None"
        if TournamentRuntime.dragon_holder > 0 and TournamentRuntime.participants[TournamentRuntime.dragon_holder] ~= nil then
            holderName = TournamentRuntime.participants[TournamentRuntime.dragon_holder].name or tostring(TournamentRuntime.dragon_holder)
        end
        table.insert(lines, "-------------------")
        table.insert(lines, "Dragon: " .. holderName)
        table.insert(lines, "Your Score: " .. tostring(tonumber(data.score) or 0) .. " / " .. tostring(tonumber(config.SCORE_LIMIT) or 300))
        table.insert(lines, "Fighters: " .. tostring(fightersCount))
        table.insert(lines, timeText)
        ITC_Hud(userId, "[" .. config.NAME .. "]", lines)
    else
        ITC_Hud(userId, "[" .. config.NAME .. "]", {
            "Survivors: " .. tostring(fightersCount),
            "Your Kills: " .. tostring(tonumber(data.kills) or 0),
            "-------------------",
            timeText,
        })
    end
end

function ImperialTournament_ShowRegistrationHud(userId)
    userId = userId or Get_UserId()
    if userId ~= nil and TournamentRuntime.participants[userId] ~= nil then ITC_ShowRegistrationHud(userId) end
end

function ImperialTournament_ShowRunningHud(userId)
    userId = userId or Get_UserId()
    ITC_ShowRunningHud(userId)
end

function ImperialTournament_End(reason, winnerId)
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state == "ENDING" then return end
    TournamentRuntime.state = "ENDING"
    pcall(ITC_RefreshMapUsers)

    if winnerId ~= nil and winnerId > 0 then
        local ok, errorText = pcall(ITC_RewardUser, winnerId, config)
        if not ok then ITC_RewardUnavailable(winnerId, "reward-runtime-error-" .. tostring(errorText)) end
        local winnerName = Get_UserName(winnerId) or tostring(winnerId)
        ITC_Broadcast(winnerName .. " won " .. config.NAME .. ". " .. tostring(reason or ""))
    else
        ITC_Broadcast(config.NAME .. " ended without a winner. " .. tostring(reason or ""))
    end

    for userId,_ in pairs(TournamentRuntime.participants) do pcall(ITC_ClearHud, userId) end
    pcall(ITC_CleanupMap, config)
    pcall(ITC_HideCoordinator, config)
    ITC_ResetRuntime()
end

local function ITC_SpreadPosition(baseX, baseY, radius, index)
    radius = math.max(0, math.floor(tonumber(radius) or 0))
    local side = (radius * 2) + 1
    local capacity = side * side
    local slot = ((index - 1 + (TournamentRuntime.spawn_rotation or 0)) % capacity)
    local offsetX = (slot % side) - radius
    local offsetY = math.floor(slot / side) - radius
    return math.max(1, baseX + offsetX), math.max(1, baseY + offsetY)
end

local function ITC_CornerPosition(config, index)
    if config ~= nil and type(tTournamentCornerSpawns) == "table" and type(tTournamentCornerSpawns[config.MAP_ID]) == "table" then
        local corners = tTournamentCornerSpawns[config.MAP_ID]
        if #corners > 0 then
            local slot = ((index - 1 + (TournamentRuntime.spawn_rotation or 0)) % #corners) + 1
            local corner = corners[slot]
            if corner ~= nil and tonumber(corner.X) and tonumber(corner.Y) then
                return tonumber(corner.X), tonumber(corner.Y)
            end
        end
    end
    return ITC_SpreadPosition(config.SPAWN_X, config.SPAWN_Y, config.SPAWN_RADIUS, index)
end

local function ITC_ApplyForceVitalsToUser(userId, config)
    if userId == nil or userId <= 0 or config == nil then return end
    if config.FORCE_LIFE ~= nil then
        local targetLife = config.FORCE_LIFE
        if config.MODE == "DRAGON_PVP" and TournamentRuntime.dragon_holder == userId then
            targetLife = 200
        end
        local life = GetUserInt(userId, G_PLAYER_Life) or 0
        if life > 0 and life ~= targetLife then User_AddLife(targetLife - life, userId) end
    end
    if config.FORCE_MANA ~= nil and User_AddMana ~= nil then
        local mana = GetUserInt(userId, G_PLAYER_Mana) or 0
        if mana ~= config.FORCE_MANA then User_AddMana(config.FORCE_MANA - mana, userId) end
    end
    if config.FORCE_EP ~= nil and User_AddEp ~= nil then
        local ep = GetUserInt(userId, G_PLAYER_EP) or 0
        if ep ~= config.FORCE_EP then User_AddEp(config.FORCE_EP - ep, userId) end
    end
end

local function ITC_MoveParticipant(userId, index)
    local config = TournamentRuntime.current
    local data = TournamentRuntime.participants[userId]
    if config == nil or data == nil then return false end
    ITC_RestoreVitals(userId)
    local x, y = ITC_CornerPosition(config, index)
    User_ChgMap(config.MAP_ID, x, y, 0, userId)
    if Get_UserMapId(userId) == config.MAP_ID then
        ITC_ApplyForceVitalsToUser(userId, config)
        return true
    end
    return false
end

local function ITC_RespawnAtCorner(userId)
    local config = TournamentRuntime.current
    if config == nil or userId == nil or userId <= 0 then return false end
    TournamentRuntime.spawn_rotation = (TournamentRuntime.spawn_rotation or 0) + 1
    ITC_RestoreVitals(userId)
    local x, y = ITC_CornerPosition(config, TournamentRuntime.spawn_rotation)
    User_ChgMap(config.MAP_ID, x, y, 0, userId)
    ITC_ApplyForceVitalsToUser(userId, config)
    return true
end

local function ITC_SortedParticipantIds()
    local ids = {}
    for userId,_ in pairs(TournamentRuntime.participants) do
        table.insert(ids, userId)
    end
    table.sort(ids)
    return ids
end

local function ITC_ClearNativeKillQueueFile()
    if os ~= nil and os.remove ~= nil then
        pcall(os.remove, "TournamentKill.queue")
    end
end

local function ITC_StartMatch()
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "REGISTRATION" then return end
    if ITC_Count(TournamentRuntime.participants) < config.MIN_PLAYERS then
        ImperialTournament_End("Not enough players.", 0)
        return
    end

    ITC_ClearNativeKillQueueFile()
    local ids = ITC_SortedParticipantIds()
    for index,userId in ipairs(ids) do
        local data = TournamentRuntime.participants[userId]
        data.pk_before = GetUserInt(userId, G_PLAYER_PK) or 0
        data.kills = 0
        data.streak = 0
        data.hits_taken = 0
        data.on_hill = false
        if not ITC_MoveParticipant(userId, index) then TournamentRuntime.participants[userId] = nil end
    end
    ITC_RefreshMapUsers()

    local playerCount = ITC_RefreshMapUsers()
    if playerCount < config.MIN_PLAYERS then
        ImperialTournament_End("Not enough players reached the arena.", 0)
        return
    end
    TournamentRuntime.state = "RUNNING"
    TournamentRuntime.match_deadline = ITC_Now() + (config.MATCH_MINUTES * 60)
    TournamentRuntime.pending_kills = {}
    TournamentRuntime.pending_scores = {}
    TournamentRuntime.recent_kill_pairs = {}
    TournamentRuntime.dragon_holder = 0
    if config.MODE == "DRAGON_PVP" and #ids > 0 then
        for _,uid in ipairs(ids) do
            if TournamentRuntime.map_users[uid] then
                TournamentRuntime.dragon_holder = uid
                ITC_ApplyForceVitalsToUser(uid, config)
                local holderName = Get_UserName(uid) or tostring(uid)
                ITC_MapBroadcast(holderName .. " is the first Dragon! Slay the Dragon to steal the power!")
                break
            end
        end
    end
    ITC_HideCoordinator(config)
    ITC_Broadcast("FIGHT! " .. config.NAME .. " has started. Good luck!")
    if config.MODE == "COOKING" then
        ITC_MapBroadcast(config.NAME .. " has started. Gather wood, water and food, light a campfire and cook before hunger reaches zero.")
    elseif config.MODE == "SCORE" then
        ITC_MapBroadcast("FIGHT! " .. config.NAME .. " has started. Each successful Fast Blade or Scent Sword hit gives one point and respawns your target!")
    elseif config.MODE == "KNOCKOUT" then
        ITC_MapBroadcast("FIGHT! " .. config.NAME .. " has started. Every player has " .. tostring(tonumber(config.MAX_HITS) or 5) .. " hits before elimination!")
    elseif config.MODE == "KOTH" then
        ITC_MapBroadcast("FIGHT! " .. config.NAME .. " has started. Hold the center hill (" .. tostring(config.HILL_X or 50) .. "," .. tostring(config.HILL_Y or 50) .. ") to earn points!")
    elseif config.MODE == "DRAGON_PVP" then
        ITC_MapBroadcast("FIGHT! " .. config.NAME .. " has started. First to " .. tostring(config.SCORE_LIMIT or 300) .. " points wins!")
    else
        ITC_MapBroadcast("FIGHT! " .. config.NAME .. " has started. Good luck!")
    end
    for userId,_ in pairs(TournamentRuntime.map_users) do ITC_ShowRunningHud(userId) end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(1, "ImperialTournament_RuntimePulse</N>" .. TournamentRuntime.run_id) end
end

function ImperialTournament_Open(config, manualRun)
    if config == nil or (config.ENABLED ~= 1 and manualRun ~= 1) then return false end
    if TournamentRuntime.state ~= "IDLE" then return false end
    TournamentRuntime.run_id = TournamentRuntime.run_id + 1
    TournamentRuntime.current = config
    TournamentRuntime.state = "REGISTRATION"
    TournamentRuntime.participants = {}
    TournamentRuntime.map_users = {}
    TournamentRuntime.rewarded = {}
    TournamentRuntime.pending_kills = {}
    TournamentRuntime.pending_scores = {}
    TournamentRuntime.announcements = {}
    TournamentRuntime.recent_kill_pairs = {}
    TournamentRuntime.dragon_holder = 0
    TournamentRuntime.registration_deadline = ITC_Now() + (config.REG_MINUTES * 60)
    TournamentRuntime.match_deadline = 0
    local radius = math.max(0, math.floor(tonumber(config.SPAWN_RADIUS) or 0))
    local capacity = ((radius * 2) + 1) * ((radius * 2) + 1)
    if math ~= nil and math.random ~= nil and capacity > 1 then
        TournamentRuntime.spawn_rotation = math.random(0, capacity - 1)
    else
        TournamentRuntime.spawn_rotation = TournamentRuntime.run_id % math.max(1, capacity)
    end

    ITC_CleanupMap(config)
    ITC_ShowCoordinator(config)
    ITC_Broadcast(config.NAME .. " registration is open for " .. config.REG_MINUTES .. " minute(s). Visit its Tournament NPC in Twin City.")
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(1, "ImperialTournament_RegistrationPulse</N>" .. TournamentRuntime.run_id) end
    return true
end

local function ITC_CheckRegistrationCountdowns(remaining)
    local config = TournamentRuntime.current
    if config == nil then return end
    local marks = {60, 30, 10, 5}
    for _,sec in ipairs(marks) do
        if remaining == sec and not TournamentRuntime.announcements["reg_" .. tostring(sec)] then
            TournamentRuntime.announcements["reg_" .. tostring(sec)] = true
            ITC_Broadcast(tostring(sec) .. " seconds left to join " .. config.NAME .. "!")
        end
    end
    if remaining <= 3 and remaining >= 1 and not TournamentRuntime.announcements["fight_" .. tostring(remaining)] then
        TournamentRuntime.announcements["fight_" .. tostring(remaining)] = true
        for userId,_ in pairs(TournamentRuntime.participants) do
            ITC_MessageUser(userId, "[" .. config.NAME .. "] Starting in " .. tostring(remaining) .. "..")
        end
    end
end

function ImperialTournament_RegistrationPulse(runId)
    if TournamentRuntime.state ~= "REGISTRATION" or TournamentRuntime.current == nil then return end
    if TournamentRuntime.run_id ~= runId or TournamentRuntime.registration_pulse_busy then return end
    TournamentRuntime.registration_pulse_busy = true
    local ok, errorText = pcall(function()
        local remaining = ITC_SecondsLeft(TournamentRuntime.registration_deadline)
        ITC_CheckRegistrationCountdowns(remaining)
        for userId,_ in pairs(TournamentRuntime.participants) do ITC_ShowRegistrationHud(userId) end
        if remaining <= 0 then ITC_StartMatch() end
    end)
    TournamentRuntime.registration_pulse_busy = false
    if not ok then
        ITC_Broadcast("Registration stopped safely after a runtime error: " .. tostring(errorText))
        if TournamentRuntime.state ~= "IDLE" then ImperialTournament_End("Registration runtime error.", 0) end
        return
    end
    if Sys_SetLuaTimer ~= nil and TournamentRuntime.state == "REGISTRATION" and TournamentRuntime.run_id == runId then
        Sys_SetLuaTimer(1, "ImperialTournament_RegistrationPulse</N>" .. runId)
    end
end

function ImperialTournament_RunNow(configKey)
    if type(configKey) ~= "string" then return false end
    if configKey == "REFRESH_NPCS" then ImperialTournament_HideInactiveCoordinators() return true end
    local all = ITC_AllConfigs()
    local config = all[configKey]
    if config == nil then return false end
    return ImperialTournament_Open(config, 1)
end

function ImperialTournament_StopNow()
    if TournamentRuntime.state == "IDLE" or TournamentRuntime.current == nil then return false end
    ImperialTournament_End("Stopped by the administrator.", 0)
    return true
end

function ImperialTournament_Join()
    local userId = Get_UserId()
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "REGISTRATION" then
        ITC_MessageUser(userId, "No tournament is accepting players right now.")
        return
    end
    if Get_UserLevel(userId) < config.MIN_LEVEL then ITC_MessageUser(userId, "You need level " .. config.MIN_LEVEL .. " to enter.") return end
    if type(config.REQUIRED_SKILLS_ANY) == "table" then
        local allowed = false
        for _,skillId in ipairs(config.REQUIRED_SKILLS_ANY) do
            if Magic_ChkType ~= nil and Magic_ChkType(skillId, userId) then
                allowed = true
                break
            end
        end
        if not allowed then ITC_MessageUser(userId, "You need Scent Sword or Fast Blade to enter this tournament.") return end
    end
    if tonumber(config.FORBIDDEN_EQUIP_POSITION) and tonumber(config.FORBIDDEN_EQUIP_SUBTYPE) and
       Get_ItemSubType ~= nil and Get_ItemSubType(config.FORBIDDEN_EQUIP_POSITION, userId) == config.FORBIDDEN_EQUIP_SUBTYPE then
        ITC_MessageUser(userId, "That equipped weapon is not allowed in this tournament.") return
    end
    if TournamentRuntime.participants[userId] ~= nil then ITC_MessageUser(userId, "You are already registered.") return end
    if ITC_Count(TournamentRuntime.participants) >= config.MAX_PLAYERS then ITC_MessageUser(userId, "The tournament is full.") return end

    TournamentRuntime.participants[userId] = {
        name = Get_UserName(userId), pk_before = GetUserInt(userId, G_PLAYER_PK) or 0,
        score = 0, kills = 0, streak = 0, hits_taken = 0, on_hill = false,
    }
    if config.MODE == "COOKING" then
        local data = TournamentRuntime.participants[userId]
        data.hunger = math.max(1, tonumber(config.HUNGER_START) or 100)
        data.wood, data.water, data.food, data.fire_until, data.last_action, data.last_hunger = 0, 0, 0, 0, 0, ITC_Now()
    end
    ITC_MessageUser(userId, "Registered for " .. config.NAME .. ". Stay online; you will be moved when registration closes.")
    ITC_ShowRegistrationHud(userId)
end

function ImperialTournament_CloseDialog()
end

local function ITC_RestoreProtectedPk()
    if TournamentRuntime.current == nil then return end
    for userId,data in pairs(TournamentRuntime.participants) do
        if TournamentRuntime.map_users[userId] and data.pk_before ~= nil then
            local currentPk = GetUserInt(userId, G_PLAYER_PK)
            if currentPk ~= nil and currentPk ~= data.pk_before then User_AddPk(data.pk_before - currentPk, userId) end
        end
    end
end

local function ITC_EliminateLastMan(victimId, killerId)
    if TournamentRuntime.participants[victimId] == nil then return end
    local config = TournamentRuntime.current
    local victimData = TournamentRuntime.participants[victimId]
    local victimName = (victimData and victimData.name) or Get_UserName(victimId) or tostring(victimId)
    if killerId ~= nil and killerId > 0 and killerId ~= victimId and TournamentRuntime.participants[killerId] ~= nil then
        local killerData = TournamentRuntime.participants[killerId]
        killerData.kills = (tonumber(killerData.kills) or 0) + 1
        killerData.score = (tonumber(killerData.score) or 0) + 1
        ITC_MessageUser(killerId, "You eliminated " .. victimName .. "! Kills: " .. tostring(killerData.kills))
    end
    ITC_MessageUser(victimId, "You have been eliminated from " .. (config and config.NAME or "the tournament") .. "!")
    ITC_ReturnUser(victimId)
    TournamentRuntime.participants[victimId] = nil
    local remaining = ITC_RefreshMapUsers()
    if remaining > 1 then
        ITC_MapBroadcast(victimName .. " was eliminated! (" .. tostring(remaining) .. " survivors remaining)")
    end
    local survivor = ITC_OnlySurvivor()
    if survivor > 0 then ImperialTournament_End("Last survivor standing.", survivor) end
end

local function ITC_AnnounceSkillStreak(killerName, streak)
    if streak == 3 then
        ITC_MapBroadcast(killerName .. " is on a Killing Spree! (3 hits in a row!)")
    elseif streak == 5 then
        ITC_MapBroadcast(killerName .. " is Dominating! (5 hits in a row!)")
    elseif streak == 7 then
        ITC_MapBroadcast(killerName .. " is Unstoppable! (7 hits in a row!)")
    elseif streak >= 10 and (streak % 5 == 0) then
        ITC_MapBroadcast(killerName .. " is GODLIKE! (" .. tostring(streak) .. " hits in a row!)")
    end
end

local function ITC_HandleCombatEvent(killerId, victimId, skillId)
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "RUNNING" then return false end
    victimId = tonumber(victimId) or 0
    killerId = tonumber(killerId) or 0
    if victimId <= 0 or TournamentRuntime.participants[victimId] == nil then return false end
    if Get_UserMapId(victimId) ~= config.MAP_ID then return false end

    local now = ITC_Now()
    local dedupKey = tostring(killerId) .. "_" .. tostring(victimId) .. "_" .. tostring(now)
    if TournamentRuntime.recent_kill_pairs[dedupKey] then return false end
    TournamentRuntime.recent_kill_pairs[dedupKey] = true

    if config.MODE == "ELIMINATION" then
        ITC_EliminateLastMan(victimId, killerId)
        return TournamentRuntime.state ~= "RUNNING"
    end

    local killer = TournamentRuntime.participants[killerId]
    local victim = TournamentRuntime.participants[victimId]
    local killerName = (killer and killer.name) or (killerId > 0 and Get_UserName(killerId)) or "Fighter"
    local victimName = (victim and victim.name) or Get_UserName(victimId) or "Fighter"

    if config.MODE == "SCORE" then
        if killer ~= nil and killerId ~= victimId and TournamentRuntime.map_users[killerId] then
            local points = math.max(1, tonumber(config.POINTS_PER_HIT) or 1)
            killer.score = (tonumber(killer.score) or 0) + points
            killer.kills = (tonumber(killer.kills) or 0) + 1
            killer.streak = (tonumber(killer.streak) or 0) + 1
            ITC_MessageUser(killerId, "You scored a hit on " .. victimName .. "! Total Points: " .. tostring(killer.score))
            ITC_AnnounceSkillStreak(killerName, killer.streak)
            if Sys_SaveAbnormalLog ~= nil then
                pcall(Sys_SaveAbnormalLog, "[ImperialTournament][Score] event=" .. tostring(config.NAME) ..
                    " killer=" .. tostring(killerId) .. " victim=" .. tostring(victimId) ..
                    " skill=" .. tostring(skillId or 0) .. " score=" .. tostring(killer.score))
            end
            local scoreLimit = math.max(0, tonumber(config.SCORE_LIMIT) or 0)
            if scoreLimit > 0 and killer.score >= scoreLimit then
                ImperialTournament_End("Score limit reached with " .. tostring(killer.score) .. " points.", killerId)
                return true
            end
        end
        if victim ~= nil then
            victim.streak = 0
            ITC_RespawnAtCorner(victimId)
            ITC_MessageUser(victimId, "You took a hit from " .. killerName .. "! Respawned at corner.")
        end
        return false
    elseif config.MODE == "KNOCKOUT" then
        local maxHits = math.max(1, tonumber(config.MAX_HITS) or 5)
        victim.hits_taken = (tonumber(victim.hits_taken) or 0) + 1
        if killer ~= nil and killerId ~= victimId then
            killer.score = (tonumber(killer.score) or 0) + 1
            killer.kills = (tonumber(killer.kills) or 0) + 1
        end
        if victim.hits_taken >= maxHits then
            ITC_MapBroadcast(victimName .. " was knocked out by " .. killerName .. "!")
            ITC_MessageUser(victimId, "You took " .. tostring(maxHits) .. " hits and are eliminated!")
            ITC_ReturnUser(victimId)
            TournamentRuntime.participants[victimId] = nil
            ITC_RefreshMapUsers()
            local survivor = ITC_OnlySurvivor()
            if survivor > 0 then
                ImperialTournament_End("Last fighter standing in " .. config.NAME .. "!", survivor)
                return true
            end
        else
            local left = maxHits - victim.hits_taken
            ITC_RespawnAtCorner(victimId)
            ITC_MessageUser(victimId, "You were hit by " .. killerName .. "! Hits left: " .. tostring(left))
            if killer ~= nil and killerId ~= victimId then
                ITC_MessageUser(killerId, "You hit " .. victimName .. "! They have " .. tostring(left) .. " hits left!")
            end
        end
        return false
    elseif config.MODE == "KOTH" then
        if killer ~= nil and killerId ~= victimId then
            killer.kills = (tonumber(killer.kills) or 0) + 1
            ITC_MessageUser(killerId, "You knocked " .. victimName .. " off the hill!")
        end
        victim.on_hill = false
        ITC_RespawnAtCorner(victimId)
        ITC_MessageUser(victimId, "You were knocked down by " .. killerName .. "! Respawned at corner.")
        return false
    elseif config.MODE == "DRAGON_PVP" then
        if killer ~= nil and killerId ~= victimId then
            if TournamentRuntime.dragon_holder == 0 or TournamentRuntime.dragon_holder == victimId then
                TournamentRuntime.dragon_holder = killerId
                local pts = math.max(1, tonumber(config.DRAGON_KILL_POINTS) or 5)
                killer.score = (tonumber(killer.score) or 0) + pts
                ITC_MapBroadcast(killerName .. " slayed the Dragon (" .. victimName .. ") and became the new Dragon!")
                ITC_ApplyForceVitalsToUser(killerId, config)
            elseif TournamentRuntime.dragon_holder == killerId then
                local pts = math.max(1, tonumber(config.DRAGON_KILL_POINTS) or 5)
                killer.score = (tonumber(killer.score) or 0) + pts
                ITC_MessageUser(killerId, "Dragon Kill! +" .. tostring(pts) .. " points! Total: " .. tostring(killer.score))
            else
                local pts = math.max(1, tonumber(config.NORMAL_KILL_POINTS) or 1)
                killer.score = (tonumber(killer.score) or 0) + pts
            end
            local scoreLimit = math.max(0, tonumber(config.SCORE_LIMIT) or 300)
            if scoreLimit > 0 and killer.score >= scoreLimit then
                ImperialTournament_End("Dragon War score limit (" .. tostring(scoreLimit) .. ") reached!", killerId)
                return true
            end
        end
        ITC_RespawnAtCorner(victimId)
        return false
    end
    return false
end

function ImperialTournament_OnKillSignal(killerId, victimId)
    local config = TournamentRuntime.current
    if TournamentRuntime.state ~= "RUNNING" or config == nil then return end
    if #TournamentRuntime.pending_kills >= 256 then return end
    local targetName = ""
    if (victimId == nil or victimId <= 0) and Get_TargetUserName ~= nil then targetName = Get_TargetUserName() or "" end
    table.insert(TournamentRuntime.pending_kills, {
        killer = tonumber(killerId) or 0, victim = tonumber(victimId) or 0,
        victim_name = targetName, run_id = TournamentRuntime.run_id,
    })
end

function ImperialTournament_OnScoreSignal(killerId, victimId, skillId)
    local config = TournamentRuntime.current
    if TournamentRuntime.state ~= "RUNNING" or config == nil then return end
    if #TournamentRuntime.pending_scores >= 512 then return end
    table.insert(TournamentRuntime.pending_scores, {
        killer = tonumber(killerId) or 0, victim = tonumber(victimId) or 0,
        skill = tonumber(skillId) or 0, run_id = TournamentRuntime.run_id,
    })
end

local function ITC_SkillIsAllowed(config, skillId)
    if skillId == nil or tonumber(skillId) == 0 then return true end
    if type(config.REQUIRED_SKILLS_ANY) ~= "table" then return true end
    for _,allowedId in ipairs(config.REQUIRED_SKILLS_ANY) do
        if tonumber(allowedId) == tonumber(skillId) then return true end
    end
    return false
end

local function ITC_DrainNativeKillQueue()
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "RUNNING" then return false end
    if io == nil or io.open == nil then return false end
    local ok, file = pcall(io.open, "TournamentKill.queue", "rb")
    if not ok or file == nil then return false end
    local readOk, content = pcall(function() return file:read("*a") end)
    pcall(function() file:close() end)
    ITC_ClearNativeKillQueueFile()
    if not readOk or type(content) ~= "string" or content == "" then return false end

    for line in string.gmatch(content, "[^\r\n]+") do
        if TournamentRuntime.state ~= "RUNNING" then return true end
        local kId, vId, atkType, mapId = string.match(line, "^ITK1|(%d+)|(%d+)|(%d+)|(%d+)|")
        if kId and vId and mapId then
            local numKiller = tonumber(kId) or 0
            local numVictim = tonumber(vId) or 0
            local numSkill = tonumber(atkType) or 0
            local numMap = tonumber(mapId) or 0
            if numMap == config.MAP_ID then
                if ITC_HandleCombatEvent(numKiller, numVictim, numSkill) then return true end
            end
        end
    end
    return TournamentRuntime.state ~= "RUNNING"
end

local function ITC_DrainScoreSignals()
    local config = TournamentRuntime.current
    local queue = TournamentRuntime.pending_scores
    TournamentRuntime.pending_scores = {}
    if config == nil then return false end
    for _,record in ipairs(queue) do
        if TournamentRuntime.state ~= "RUNNING" or record.run_id ~= TournamentRuntime.run_id then return true end
        local killerId = record.killer
        local victimId = record.victim
        if killerId > 0 and victimId > 0 and killerId ~= victimId and
           ITC_SkillIsAllowed(config, record.skill) then
            if ITC_HandleCombatEvent(killerId, victimId, record.skill) then return true end
        end
    end
    return TournamentRuntime.state ~= "RUNNING"
end

local function ITC_DrainKillSignals()
    local queue = TournamentRuntime.pending_kills
    TournamentRuntime.pending_kills = {}
    for _,record in ipairs(queue) do
        if TournamentRuntime.state ~= "RUNNING" or record.run_id ~= TournamentRuntime.run_id then return true end
        local victimId = record.victim
        if victimId == nil or victimId <= 0 then
            for participantId,data in pairs(TournamentRuntime.participants) do
                if data.name == record.victim_name then victimId = participantId break end
            end
        end
        if victimId ~= nil and victimId > 0 and TournamentRuntime.participants[victimId] ~= nil and Get_UserMapId(victimId) == TournamentRuntime.current.MAP_ID then
            if ITC_HandleCombatEvent(record.killer, victimId, 0) then return true end
        end
    end
    return TournamentRuntime.state ~= "RUNNING"
end

local function ITC_ReconcileNativeDeaths()
    local config = TournamentRuntime.current
    if config == nil then return false end
    local deadUsers = {}
    for userId,_ in pairs(TournamentRuntime.participants) do
        if TournamentRuntime.map_users[userId] and (GetUserInt(userId, G_PLAYER_Life) or 0) <= 0 then table.insert(deadUsers, userId) end
    end
    table.sort(deadUsers)
    for _,victimId in ipairs(deadUsers) do
        if TournamentRuntime.state ~= "RUNNING" or TournamentRuntime.current ~= config then return true end
        if TournamentRuntime.participants[victimId] ~= nil and Get_UserMapId(victimId) == config.MAP_ID then
            if config.MODE == "ELIMINATION" then
                ITC_EliminateLastMan(victimId, 0)
            else
                if ITC_HandleCombatEvent(0, victimId, 0) then return true end
            end
        end
    end
    return TournamentRuntime.state ~= "RUNNING"
end

local function ITC_UpdateKothAndDragonPulse()
    local config = TournamentRuntime.current
    if config == nil or TournamentRuntime.state ~= "RUNNING" then return false end
    if config.MODE == "KOTH" then
        local hillX = tonumber(config.HILL_X) or 50
        local hillY = tonumber(config.HILL_Y) or 50
        local hillRadius = tonumber(config.HILL_RADIUS) or 5
        local ptsPerSec = math.max(1, tonumber(config.HILL_POINTS_PER_SEC) or 5)
        local scoreLimit = math.max(0, tonumber(config.SCORE_LIMIT) or 300)
        for userId,_ in pairs(TournamentRuntime.map_users) do
            local data = TournamentRuntime.participants[userId]
            if data ~= nil and (GetUserInt(userId, G_PLAYER_Life) or 0) > 0 then
                local ux = tonumber(Get_UserPositionX(userId)) or 0
                local uy = tonumber(Get_UserPositionY(userId)) or 0
                if math.abs(ux - hillX) <= hillRadius and math.abs(uy - hillY) <= hillRadius then
                    data.on_hill = true
                    data.score = (tonumber(data.score) or 0) + ptsPerSec
                    if scoreLimit > 0 and data.score >= scoreLimit then
                        ImperialTournament_End("King Of The Hill score limit (" .. tostring(scoreLimit) .. ") reached!", userId)
                        return true
                    end
                else
                    data.on_hill = false
                end
            end
        end
    elseif config.MODE == "DRAGON_PVP" then
        local holder = TournamentRuntime.dragon_holder
        if holder <= 0 or not TournamentRuntime.map_users[holder] or TournamentRuntime.participants[holder] == nil then
            local ids = ITC_SortedParticipantIds()
            for _,uid in ipairs(ids) do
                if TournamentRuntime.map_users[uid] then
                    TournamentRuntime.dragon_holder = uid
                    holder = uid
                    ITC_ApplyForceVitalsToUser(uid, config)
                    break
                end
            end
        end
        if holder > 0 and TournamentRuntime.participants[holder] ~= nil then
            local data = TournamentRuntime.participants[holder]
            local pts = math.max(1, tonumber(config.DRAGON_POINTS_PER_SEC) or 3)
            local scoreLimit = math.max(0, tonumber(config.SCORE_LIMIT) or 300)
            data.score = (tonumber(data.score) or 0) + pts
            if scoreLimit > 0 and data.score >= scoreLimit then
                ImperialTournament_End("Dragon War score limit (" .. tostring(scoreLimit) .. ") reached!", holder)
                return true
            end
        end
    end
    return false
end

local function ITC_RemoveDepartedParticipants()
    local departed = {}
    for userId,_ in pairs(TournamentRuntime.participants) do
        if not TournamentRuntime.map_users[userId] then table.insert(departed, userId) end
    end
    for _,userId in ipairs(departed) do
        TournamentRuntime.participants[userId] = nil
        ITC_ClearHud(userId)
    end
end

local function ITC_EndByTime()
    local config = TournamentRuntime.current
    if config == nil then return end
    if config.MODE == "SCORE" or config.MODE == "COOKING" or config.MODE == "KOTH" or config.MODE == "DRAGON_PVP" then
        local winnerId = 0
        local topScore = -1
        local tied = false
        for userId,_ in pairs(TournamentRuntime.map_users) do
            local data = TournamentRuntime.participants[userId]
            local score = data and (tonumber(data.score) or 0) or 0
            if score > topScore then
                winnerId = userId
                topScore = score
                tied = false
            elseif score == topScore then
                tied = true
            end
        end
        if winnerId > 0 and not tied and topScore > 0 then
            ImperialTournament_End("Time limit reached with " .. tostring(topScore) .. " points.", winnerId)
        else
            ImperialTournament_End("Time limit reached with a tied score of " .. tostring(math.max(0, topScore)) .. ".", 0)
        end
        return
    elseif config.MODE == "KNOCKOUT" then
        local winnerId = 0
        local bestHitsTaken = 999999
        local tied = false
        for userId,_ in pairs(TournamentRuntime.map_users) do
            local data = TournamentRuntime.participants[userId]
            local taken = data and (tonumber(data.hits_taken) or 0) or 0
            if taken < bestHitsTaken then
                bestHitsTaken = taken
                winnerId = userId
                tied = false
            elseif taken == bestHitsTaken then
                tied = true
            end
        end
        if winnerId > 0 and not tied then
            ImperialTournament_End("Time limit reached; winner had fewest hits taken (" .. tostring(bestHitsTaken) .. ").", winnerId)
            return
        end
    elseif config.MODE == "ELIMINATION" then
        local winnerId = 0
        local topKills = -1
        local tied = false
        for userId,_ in pairs(TournamentRuntime.map_users) do
            local data = TournamentRuntime.participants[userId]
            local kills = data and (tonumber(data.kills) or 0) or 0
            if kills > topKills then
                topKills = kills
                winnerId = userId
                tied = false
            elseif kills == topKills then
                tied = true
            end
        end
        if winnerId > 0 and not tied and topKills > 0 then
            ImperialTournament_End("Time limit reached; winner by highest kills (" .. tostring(topKills) .. ").", winnerId)
            return
        end
    end
    ImperialTournament_End("Time limit reached.", 0)
end

local function ITC_RuntimePulseBody(runId)
    local config = TournamentRuntime.current
    local count = ITC_RefreshMapUsers()
    ITC_RestoreProtectedPk()
    if ITC_DrainNativeKillQueue() then return end
    if ITC_DrainKillSignals() then return end
    if ITC_DrainScoreSignals() then return end
    if ITC_ReconcileNativeDeaths() then return end
    if ITC_UpdateKothAndDragonPulse() then return end
    count = ITC_RefreshMapUsers()

    if config.MODE == "COOKING" then
        local now, drainEvery = ITC_Now(), math.max(1,tonumber(config.HUNGER_DRAIN_SECONDS) or 5)
        local starved = {}
        for userId,_ in pairs(TournamentRuntime.map_users) do
            local data=TournamentRuntime.participants[userId]
            if data and now-(tonumber(data.last_hunger) or now)>=drainEvery then
                local ticks=math.floor((now-(tonumber(data.last_hunger) or now))/drainEvery)
                data.last_hunger=(tonumber(data.last_hunger) or now)+ticks*drainEvery
                data.hunger=math.max(0,(tonumber(data.hunger) or 0)-ticks)
                if data.hunger<=0 then table.insert(starved,userId) end
            end
        end
        table.sort(starved)
        for _,userId in ipairs(starved) do
            if TournamentRuntime.participants[userId] then ITC_MessageUser(userId,"You were eliminated by hunger.");ITC_ReturnUser(userId);TournamentRuntime.participants[userId]=nil end
        end
        if #starved>0 then count=ITC_RefreshMapUsers() end
    end

    if config.FORCE_LIFE ~= nil or config.FORCE_MANA ~= nil or config.FORCE_EP ~= nil then
        for userId,_ in pairs(TournamentRuntime.map_users) do
            ITC_ApplyForceVitalsToUser(userId, config)
        end
    end
    ITC_RemoveDepartedParticipants()
    count = ITC_RefreshMapUsers()

    if count == 0 then ImperialTournament_End("All players left.", 0) return end
    if count == 1 and config.MODE ~= "COOKING" then ImperialTournament_End("Last active player remaining.", ITC_OnlySurvivor()) return end
    if ITC_SecondsLeft(TournamentRuntime.match_deadline) <= 0 then ITC_EndByTime() return end
    for userId,_ in pairs(TournamentRuntime.map_users) do ITC_ShowRunningHud(userId) end
end

function ImperialTournament_RuntimePulse(runId)
    if TournamentRuntime.state ~= "RUNNING" or TournamentRuntime.current == nil then return end
    if TournamentRuntime.run_id ~= runId or TournamentRuntime.pulse_busy then return end
    TournamentRuntime.pulse_busy = true
    local ok, errorText = pcall(ITC_RuntimePulseBody, runId)
    TournamentRuntime.pulse_busy = false
    if not ok then
        ITC_Broadcast("Tournament stopped safely after a runtime error: " .. tostring(errorText))
        if TournamentRuntime.state ~= "IDLE" then ImperialTournament_End("Tournament runtime error.", 0) end
        return
    end
    if Sys_SetLuaTimer ~= nil and TournamentRuntime.state == "RUNNING" and TournamentRuntime.run_id == runId then
        Sys_SetLuaTimer(1, "ImperialTournament_RuntimePulse</N>" .. runId)
    end
end

function ImperialTournament_TimerTick()
    local hour = tonumber(os.date("%H"))
    local minute = tonumber(os.date("%M"))
    if TournamentRuntime.state == "IDLE" then
        local scheduled = {}
        for _,config in pairs(ITC_AllConfigs()) do
            if config.ENABLED == 1 and config.START_MINUTE == minute and (config.START_HOUR == -1 or config.START_HOUR == hour) then
                table.insert(scheduled, config)
            end
        end
        table.sort(scheduled, function(a,b) return a.ID < b.ID end)
        if #scheduled > 0 then ImperialTournament_Open(scheduled[1]) end
    elseif TournamentRuntime.state == "RUNNING" and ITC_SecondsLeft(TournamentRuntime.match_deadline) <= 0 then
        ITC_EndByTime()
    end
end

function ImperialTournament_DeferredStartupRecovery(runId)
    if TournamentRuntime.run_id ~= runId or TournamentRuntime.state ~= "IDLE" then return end
    for _,config in pairs(ITC_AllConfigs()) do pcall(ITC_CleanupMap, config) end
    pcall(ImperialTournament_HideInactiveCoordinators)
end

function ImperialTournament_StartupRecovery()
    ITC_ResetRuntime()
    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(30, "ImperialTournament_DeferredStartupRecovery</N>" .. TournamentRuntime.run_id)
    end
end

function ImperialTournament_ConfigPulse(requestGeneration)
    if requestGeneration ~= TournamentConfigRuntime.generation then return end
    if TournamentRuntime.state == "IDLE" then
        local ok=pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]TournamentConfig.lua")
        if ok then
            local revision=tostring(tTournamentConfigRevision or "")
            if revision ~= TournamentConfigRuntime.revision then
                TournamentConfigRuntime.revision=revision
                if ImperialTournament_RegisterEventNpcs ~= nil then ImperialTournament_RegisterEventNpcs() end
            end
        end
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialTournament_ConfigPulse</N>"..tostring(requestGeneration)) end
end

if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialTournament_ConfigPulse</N>"..tostring(tournamentConfigGeneration)) end
