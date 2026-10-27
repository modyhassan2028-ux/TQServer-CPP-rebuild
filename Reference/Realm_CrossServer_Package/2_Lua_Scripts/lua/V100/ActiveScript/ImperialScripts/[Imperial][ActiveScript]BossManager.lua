--------------------------------------------------------------------------------
-- Imperial Boss Manager
-- Custom bosses only. Native cq_generator/cq_action bosses are intentionally
-- outside this runtime and remain owned by their original server systems.
--------------------------------------------------------------------------------

dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]BossManagerConfig.lua")
dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DurableRewardQueue.lua")

local BOSS_PULSE_SECONDS = 5
local CHANCE_MAX = 100000

ImperialBossRuntime = ImperialBossRuntime or { state = {}, chains = {}, spawnSequence = 0, lastCommandToken = "" }
ImperialBossRuntime.state = ImperialBossRuntime.state or {}
ImperialBossRuntime.chains = ImperialBossRuntime.chains or {}
ImperialBossRuntime.spawnSequence = ImperialBossRuntime.spawnSequence or 0
ImperialBossRuntime.deathSequence = ImperialBossRuntime.deathSequence or 0
ImperialBossRuntime.configRevision = tostring(tImperialBossRevision or "")
ImperialBossRuntime.generation = (ImperialBossRuntime.generation or 0) + 1
local generation = ImperialBossRuntime.generation

local function Boss_Log(text)
    if Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[ImperialBoss] " .. tostring(text or ""))
    end
end

local function Boss_Find(key)
    for _, boss in ipairs(tImperialBossConfig or {}) do
        if boss.Key == key then return boss end
    end
    return nil
end

local function Boss_Replace(text, boss, location, killer)
    local result = tostring(text or "")
    result = string.gsub(result, "{boss}", tostring(boss.Name or boss.Key))
    result = string.gsub(result, "{map}", tostring(location and location.MapId or 0))
    result = string.gsub(result, "{x}", tostring(location and location.X or 0))
    result = string.gsub(result, "{y}", tostring(location and location.Y or 0))
    result = string.gsub(result, "{killer}", tostring(killer or "Unknown"))
    return result
end

local function Boss_Broadcast(text)
    if text ~= "" and Sys_SystemBroadcast ~= nil then Sys_SystemBroadcast(text) end
end

local function Boss_Count(boss)
    local count, seenMaps = 0, {}
    for _, location in ipairs(boss.Locations or {}) do
        if location.Enabled and not seenMaps[location.MapId] then
            seenMaps[location.MapId] = true
            local current = Monster_GetMonsterByGenId(location.MapId, boss.GeneratorId)
            count = count + (tonumber(current) or 0)
        end
    end
    return count
end

local function Boss_PickLocation(boss)
    local total = 0
    for _, location in ipairs(boss.Locations or {}) do
        if location.Enabled and (tonumber(location.Weight) or 0) > 0 then total = total + location.Weight end
    end
    if total <= 0 then return nil end
    local roll = math.random(1, total)
    for _, location in ipairs(boss.Locations or {}) do
        if location.Enabled and (tonumber(location.Weight) or 0) > 0 then
            roll = roll - location.Weight
            if roll <= 0 then return location end
        end
    end
    return nil
end

local function Boss_BeginInstance(boss, state, chainRunToken)
    ImperialBossRuntime.spawnSequence = ImperialBossRuntime.spawnSequence + 1
    if tostring(chainRunToken or "") ~= "" then
        state.instanceToken = tostring(chainRunToken) .. "_" .. tostring(boss.MonsterId)
    else
        state.instanceToken = tostring(os.time()) .. "_" .. tostring(ImperialBossRuntime.spawnSequence) .. "_" .. tostring(boss.MonsterId)
    end
    state.rewardedToken = nil
    if tostring(boss.ChainKey or "") ~= "" then
        local runToken = tostring(chainRunToken or "")
        if runToken == "" then runToken = state.instanceToken end
        state.chainRunToken = runToken
        ImperialBossRuntime.chains[boss.ChainKey] = runToken
    else
        state.chainRunToken = nil
    end
end

-- Safe bridge for another owned Lua event (for example Dragons War gates).
-- Unlike the panel's manual path this still requires the boss to be enabled.
function ImperialBoss_StartExternal(key, runToken)
    if tostring(runToken or "") == "" then return false end
    return ImperialBoss_Spawn(key, false, nil, nil, nil, tostring(runToken))
end

function ImperialBoss_AreEnabled(keys)
    for _,key in ipairs(keys or {}) do
        local boss=Boss_Find(key)
        if boss==nil or not boss.Enabled or Boss_PickLocation(boss)==nil then return false end
    end
    return true
end

function ImperialBoss_Spawn(key, manual, forcedMapId, forcedX, forcedY, chainRunToken)
    local boss = Boss_Find(key)
    if boss == nil then Boss_Log("spawn rejected; unknown key=" .. tostring(key)); return false end
    if not manual and not boss.Enabled then return false end
    local alive = Boss_Count(boss)
    if alive >= (tonumber(boss.MaxAlive) or 1) then return false end
    local location = nil
    if manual and tonumber(forcedMapId) and tonumber(forcedMapId) > 0 then
        for _, candidate in ipairs(boss.Locations or {}) do
            if candidate.Enabled and candidate.MapId == tonumber(forcedMapId) and
               candidate.X == tonumber(forcedX) and candidate.Y == tonumber(forcedY) then
                location = candidate
                break
            end
        end
    else
        location = Boss_PickLocation(boss)
    end
    if location == nil then Boss_Log("spawn rejected; no enabled location for " .. boss.Key); return false end
    local ok = Monster_AddMonster(location.MapId, location.X, location.Y, boss.GeneratorId, boss.MonsterId)
    if not ok then Boss_Log("CreateMonster failed for " .. boss.Key); return false end
    local state = ImperialBossRuntime.state[boss.Key] or {}
    Boss_BeginInstance(boss, state, chainRunToken)
    state.location = location
    state.spawnedAt = os.time()
    ImperialBossRuntime.state[boss.Key] = state
    Boss_Broadcast(Boss_Replace(boss.SpawnMessage, boss, location, ""))
    Boss_Log("spawned " .. boss.Key .. " map=" .. location.MapId .. " x=" .. location.X .. " y=" .. location.Y)
    return true
end

-- Native Action 2006 performs the actual creation for the panel's manual
-- Spawn button. Record that exact location and broadcast only after the
-- native bridge confirms success.
function ImperialBoss_MarkSpawned(key, mapId, x, y)
    local boss = Boss_Find(key)
    if boss == nil then return false end
    local location = { MapId=tonumber(mapId) or 0, X=tonumber(x) or 0, Y=tonumber(y) or 0 }
    local state = ImperialBossRuntime.state[key] or {}
    Boss_BeginInstance(boss, state, nil)
    state.location = location
    state.spawnedAt = os.time()
    ImperialBossRuntime.state[key] = state
    Boss_Broadcast(Boss_Replace(boss.SpawnMessage, boss, location, ""))
    Boss_Log("native action spawn confirmed " .. key .. " map=" .. location.MapId .. " x=" .. location.X .. " y=" .. location.Y)
    return true
end

function ImperialBoss_Remove(key)
    local boss = Boss_Find(key)
    if boss == nil then return false end
    local seenMaps = {}
    for _, location in ipairs(boss.Locations or {}) do
        if location.Enabled and not seenMaps[location.MapId] then
            seenMaps[location.MapId] = true
            Monster_DelMonster(location.MapId, boss.MonsterId)
        end
    end
    local state = ImperialBossRuntime.state[key] or {}
    state.spawnedAt = nil
    ImperialBossRuntime.state[key] = state
    Boss_Log("removed administratively " .. key)
    return true
end

local function Boss_QueueMail(boss, selected, userId, instanceToken)
    local items, money, emoney = {}, 0, 0
    for _, reward in ipairs(selected) do
        local amount = math.max(1, tonumber(reward.Amount) or 1)
        local value = math.max(0, tonumber(reward.Value) or 0)
        if reward.Kind == "Item" then table.insert(items,{ItemId=value,Amount=amount})
        elseif reward.Kind == "Silver" then money = money + value * amount
        elseif reward.Kind == "CPs" then emoney = emoney + value * amount end
    end
    if #items == 0 and money == 0 and emoney == 0 then return true end
    local contract = { Token=instanceToken, UserId=userId, Money=money, EMoney=emoney, EventId=tonumber(boss.MonsterId) or 0 }
    if #items == 1 then contract.ItemId=items[1].ItemId; contract.ItemCount=items[1].Amount else contract.Items=items end
    local ok, result = ImperialReward_Queue(contract)
    if not ok then Boss_Log("mail queue failed reason=" .. tostring(result)); return false end
    Boss_Log("durable reward queued token=" .. tostring(result) .. " user=" .. tostring(userId))
    return true
end

local function Boss_DeliverImmediate(reward, userId)
    local amount = tonumber(reward.Amount) or 1
    local value = tonumber(reward.Value) or 0
    if reward.Kind == "Item" then
        for _ = 1, amount do
            if reward.Delivery == "Ground" then Monster_SysDropItem(value, userId)
            else Item_AddItem(value,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,userId) end
        end
    elseif reward.Kind == "Silver" and User_AddMoney ~= nil then User_AddMoney(value * amount, userId)
    elseif reward.Kind == "CPs" and User_AddEMoney ~= nil then User_AddEMoney(value * amount, userId)
    elseif reward.Kind == "BoundCPs" and User_AddEMoneyMono ~= nil then User_AddEMoneyMono(value * amount, userId)
    end
    return true
end

local function Boss_SelectRewards(boss)
    local pools, order = {}, {}
    for _, reward in ipairs(boss.Rewards or {}) do
        if reward.Enabled then
            local pool = tostring(reward.Pool or "default")
            if pools[pool] == nil then pools[pool] = {}; table.insert(order, pool) end
            table.insert(pools[pool], reward)
        end
    end
    local selected = {}
    for _, pool in ipairs(order) do
        local rewards = pools[pool]
        local mode = tostring(rewards[1].Mode or "Independent")
        if mode == "Guaranteed" then
            for _, reward in ipairs(rewards) do table.insert(selected, reward) end
        elseif mode == "WeightedOne" then
            local total = 0
            for _, reward in ipairs(rewards) do total = total + math.max(0, tonumber(reward.Chance) or 0) end
            if total > 0 then
                local roll = math.random(1, total)
                for _, reward in ipairs(rewards) do
                    roll = roll - math.max(0, tonumber(reward.Chance) or 0)
                    if roll <= 0 then table.insert(selected, reward); break end
                end
            end
        else
            for _, reward in ipairs(rewards) do
                if math.random(1, CHANCE_MAX) <= (tonumber(reward.Chance) or 0) then
                    table.insert(selected, reward)
                end
            end
        end
    end
    return selected
end

local function Boss_DeliverRewards(boss, userId, instanceToken)
    local selected = Boss_SelectRewards(boss)
    local mail = {}
    for _, reward in ipairs(selected) do
        if reward.Delivery == "Mail" then table.insert(mail, reward)
        elseif not Boss_DeliverImmediate(reward, userId) then return false end
    end
    if #mail > 0 and not Boss_QueueMail(boss, mail, userId, instanceToken) then return false end
    return true
end

function ImperialBoss_ChainSpawn(nextBossKey, chainKey, runToken)
    if tostring(chainKey or "") == "" or ImperialBossRuntime.chains[chainKey] ~= runToken then
        Boss_Log("stale chain spawn ignored; chain=" .. tostring(chainKey) .. " next=" .. tostring(nextBossKey))
        return false
    end
    return ImperialBoss_Spawn(nextBossKey, true, nil, nil, nil, runToken)
end

function ImperialBoss_OnKilled(key, explicitUserId)
    local boss = Boss_Find(key)
    if boss == nil then return end
    local userId = tonumber(explicitUserId) or tonumber(Get_UserId()) or 0
    if userId <= 0 then Boss_Log("death ignored without a valid killer for " .. key); return end
    local state = ImperialBossRuntime.state[key] or {}
    local instanceToken = state.instanceToken
    if instanceToken == nil then
        -- A server restart may leave an owned clone alive while Lua memory is
        -- rebuilt. Recover a one-shot token instead of silently losing loot.
        ImperialBossRuntime.deathSequence = ImperialBossRuntime.deathSequence + 1
        instanceToken = tostring(os.time()) .. "_R_" .. tostring(ImperialBossRuntime.deathSequence) .. "_" .. tostring(boss.MonsterId)
        state.instanceToken = instanceToken
        if tostring(boss.ChainKey or "") ~= "" then
            state.chainRunToken = instanceToken
            ImperialBossRuntime.chains[boss.ChainKey] = instanceToken
        end
    end
    if state.rewardedToken == instanceToken then Boss_Log("duplicate death ignored for " .. key); return end
    if not Boss_DeliverRewards(boss, userId, instanceToken) then
        ImperialBossRuntime.state[key] = state
        Boss_Log("death reward persistence failed; chain stopped for " .. key)
        return
    end
    -- Queue publication is durable and mail titles are idempotent. Mark only
    -- after the entitlement has been atomically renamed to .req.
    state.rewardedToken = instanceToken
    local killer = Get_UserName(userId) or "Unknown"
    Boss_Broadcast(Boss_Replace(boss.KillMessage, boss, state.location, killer))
    state.spawnedAt = nil
    ImperialBossRuntime.state[key] = state
    if ImperialDragonsWar_OnBossKilled ~= nil then
        local ok, errorText = pcall(ImperialDragonsWar_OnBossKilled, key, userId)
        if not ok then Boss_Log("Dragons War death bridge failed key="..tostring(key).." error="..tostring(errorText)) end
    end
    local nextBossKey = tostring(boss.NextBossKey or "")
    local chainKey = tostring(boss.ChainKey or "")
    local runToken = state.chainRunToken
    if nextBossKey ~= "" and chainKey ~= "" and runToken ~= nil then
        local delay = math.max(0, tonumber(boss.NextDelaySeconds) or 0)
        if delay > 0 and Sys_SetLuaTimer ~= nil then
            Sys_SetLuaTimer(delay, "ImperialBoss_ChainSpawn</N>" .. nextBossKey .. "</N>" .. chainKey .. "</N>" .. runToken)
        else
            ImperialBoss_ChainSpawn(nextBossKey, chainKey, runToken)
        end
    elseif chainKey ~= "" and ImperialBossRuntime.chains[chainKey] == runToken then
        ImperialBossRuntime.chains[chainKey] = nil
    end
    Boss_Log("killed " .. key .. " by " .. tostring(killer) .. " user=" .. tostring(userId))
end

local function Boss_DayAllowed(boss, day)
    for _, configured in ipairs(boss.Days or {}) do if configured == day then return true end end
    return false
end

local function Boss_RunSchedule(boss, now)
    if not boss.Enabled or boss.AutoSchedule == false or not Boss_DayAllowed(boss, now.wday - 1) then return end
    local hhmm = string.format("%02d:%02d", now.hour, now.min)
    for _, configured in ipairs(boss.Times or {}) do
        if configured == hhmm then
            local token = os.date("%Y%m%d") .. ":" .. hhmm
            local state = ImperialBossRuntime.state[boss.Key] or {}
            if state.lastScheduleToken ~= token then
                state.lastScheduleToken = token
                ImperialBossRuntime.state[boss.Key] = state
                ImperialBoss_Spawn(boss.Key, false)
            end
        end
    end
end

local function Boss_Expire(boss, nowSeconds)
    local state = ImperialBossRuntime.state[boss.Key]
    local lifetime = tonumber(boss.LifeMinutes) or 0
    if lifetime <= 0 or state == nil or state.spawnedAt == nil or nowSeconds - state.spawnedAt < lifetime * 60 then return end
    for _, location in ipairs(boss.Locations or {}) do
        if location.Enabled then Monster_DelMonster(location.MapId, boss.MonsterId) end
    end
    state.spawnedAt = nil
    Boss_Log("expired " .. boss.Key)
end

function ImperialBoss_Pulse(requestGeneration)
    if requestGeneration ~= ImperialBossRuntime.generation then return end
    if ImperialBoss_RefreshConfig ~= nil then ImperialBoss_RefreshConfig() end
    local now, seconds = os.date("*t"), os.time()
    for _, boss in ipairs(tImperialBossConfig or {}) do
        Boss_RunSchedule(boss, now)
        Boss_Expire(boss, seconds)
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(BOSS_PULSE_SECONDS, "ImperialBoss_Pulse</N>" .. tostring(requestGeneration)) end
end

-- Remove only callbacks installed by this manager and install the current
-- revision. This is also used by the five-second live-config refresh.
function ImperialBoss_InstallHandlers()
    if type(g_ImperialBossOldHandlers) == "table" and type(tMonster) == "table" then
        for monsterId, oldHandler in pairs(g_ImperialBossOldHandlers) do
            local functions = tMonster[monsterId] and tMonster[monsterId]["tFunction"]
            if type(functions) == "table" then
                for index = #functions, 1, -1 do if functions[index] == oldHandler then table.remove(functions, index) end end
            end
        end
    end
    g_ImperialBossOldHandlers = {}
    tMonster = tMonster or {}
    for _, boss in ipairs(tImperialBossConfig or {}) do
        -- Disabled stops future schedules. Keep the callback for an already
        -- spawned owned clone so disabling cannot strand a live boss without
        -- its configured reward/chain completion behavior.
        if (tonumber(boss.MonsterId) or 0) > 0 then
            local key = boss.Key
            local handler = function() ImperialBoss_OnKilled(key) end
            tMonster[boss.MonsterId] = tMonster[boss.MonsterId] or {}
            tMonster[boss.MonsterId]["tFunction"] = tMonster[boss.MonsterId]["tFunction"] or {}
            table.insert(tMonster[boss.MonsterId]["tFunction"], handler)
            g_ImperialBossOldHandlers[boss.MonsterId] = handler
        end
    end
end

function ImperialBoss_ProcessCommand()
    if type(tImperialBossCommand) == "table" and tImperialBossCommand.Token ~= ImperialBossRuntime.lastCommandToken then
        ImperialBossRuntime.lastCommandToken = tImperialBossCommand.Token
        if tImperialBossCommand.Action == "spawn" then
            ImperialBoss_Spawn(tImperialBossCommand.BossKey, true,
                tImperialBossCommand.MapId, tImperialBossCommand.X, tImperialBossCommand.Y)
        elseif tImperialBossCommand.Action == "announce" then
            ImperialBoss_MarkSpawned(tImperialBossCommand.BossKey, tImperialBossCommand.MapId,
                tImperialBossCommand.X, tImperialBossCommand.Y)
        elseif tImperialBossCommand.Action == "remove" then ImperialBoss_Remove(tImperialBossCommand.BossKey) end
    end
end

function ImperialBoss_RefreshConfig()
    local ok, message = pcall(dofile, "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]BossManagerConfig.lua")
    if not ok then Boss_Log("live config rejected; " .. tostring(message)); return false end
    local revision = tostring(tImperialBossRevision or "")
    if revision == ImperialBossRuntime.configRevision then return true end
    ImperialBossRuntime.configRevision = revision
    ImperialBoss_InstallHandlers()
    ImperialBoss_ProcessCommand()
    Boss_Log("live config applied; revision=" .. revision)
    return true
end

ImperialBoss_InstallHandlers()
ImperialBoss_ProcessCommand()

if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(2, "ImperialBoss_Pulse</N>" .. tostring(generation)) end
