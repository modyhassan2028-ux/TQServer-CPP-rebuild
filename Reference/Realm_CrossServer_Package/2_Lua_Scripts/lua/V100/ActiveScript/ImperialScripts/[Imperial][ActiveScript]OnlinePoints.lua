-- Imperial Online Sanctuary & Online Points System
-- Supports both the In-Game Grand Wardrobe-style Sanctuary UI and NPC 191020.
-- Balances, daily online seconds, and claims are saved in cq_statistic (event 9001).

local IOP_NPC_ID = 191020
tNpcFace = tNpcFace or {}
tNpcFace[3159] = 32 -- lookface 31590: Online Points Manager

local IOP_STAT_EVENT = 9001
local IOP_STAT_BALANCE = 1
local IOP_STAT_TODAY_SECONDS = 2
local IOP_STAT_TODAY_DATE = 3
local IOP_STAT_MARATHON_BASE = 200
local IOP_CONFIG_PATH = "ServerGameConfig.ini"
local IOP_QUEUE_PATH = "OnlinePointsQueue.txt"
local IOP_RESULT_PATH = "OnlinePointsResults.txt"
local IOP_MAX_REWARDS = 28
local IOP_MAX_MARATHONS = 6
local IOP_REWARD_OPTION_BASE = 1000
local IOP_CLOSE_OPTION = 1902

ImperialOnlinePointsRuntime = ImperialOnlinePointsRuntime or {
    sessions = {}, purchaseLocks = {}, configGeneration = 0, pulseCounter = 0
}
local IOP_Runtime = ImperialOnlinePointsRuntime
IOP_Runtime.sessions = IOP_Runtime.sessions or {}
IOP_Runtime.purchaseLocks = IOP_Runtime.purchaseLocks or {}
IOP_Runtime.configGeneration = (IOP_Runtime.configGeneration or 0) + 1
IOP_Runtime.pulseCounter = 0

local function IOP_Trim(value)
    if type(value) ~= "string" then return "" end
    return (string.gsub(value, "^%s*(.-)%s*$", "%1"))
end

local function IOP_ClampInteger(value, fallback, minimum, maximum)
    local number = tonumber(value)
    if number == nil then return fallback end
    number = math.floor(number)
    if number < minimum then return minimum end
    if number > maximum then return maximum end
    return number
end

local function IOP_ParseEnabled(value, fallback)
    if value == nil then return fallback end
    local normalized = string.lower(IOP_Trim(tostring(value)))
    if normalized == "1" or normalized == "true" or normalized == "yes" or normalized == "on" then return true end
    if normalized == "0" or normalized == "false" or normalized == "no" or normalized == "off" then return false end
    return fallback
end

local function IOP_GetTodayStamp()
    if os ~= nil and os.date ~= nil then
        local ok, stamp = pcall(os.date, "%Y%m%d")
        if ok and stamp ~= nil then
            return tonumber(stamp) or 0
        end
    end
    return 0
end

local function IOP_DefaultRewards()
    return {
        { ItemId = 730004, Cost = 510, ClaimLimit = 3, ClaimKey = 101, IsHot = true },
        { ItemId = 730003, Cost = 170, ClaimLimit = 3, ClaimKey = 102, IsHot = true },
        { ItemId = 3001044, Cost = 144, ClaimLimit = 3, ClaimKey = 103, IsHot = false }
    }
end

local function IOP_DefaultMarathons()
    return {
        { Minutes = 30,  BonusPoints = 25,  BonusItemId = 0,       Enabled = true },
        { Minutes = 60,  BonusPoints = 50,  BonusItemId = 1088001, Enabled = true },
        { Minutes = 120, BonusPoints = 100, BonusItemId = 1080001, Enabled = true },
        { Minutes = 180, BonusPoints = 150, BonusItemId = 0,       Enabled = true },
        { Minutes = 240, BonusPoints = 250, BonusItemId = 730003,  Enabled = true },
        { Minutes = 360, BonusPoints = 500, BonusItemId = 730004,  Enabled = true }
    }
end

local function IOP_DefaultConfig()
    return {
        Enabled = true,
        IntervalSeconds = 60,
        PointsPerInterval = 1,
        VipBonus = { [0] = 0, [1] = 1, [2] = 2, [3] = 3, [4] = 5, [5] = 8, [6] = 10 },
        Rewards = IOP_DefaultRewards(),
        Marathons = IOP_DefaultMarathons()
    }
end

local function IOP_ReadConfig()
    local values = {}
    if io ~= nil and io.open ~= nil then
        local opened, file = pcall(io.open, IOP_CONFIG_PATH, "r")
        if opened and file ~= nil then
            local section = ""
            for line in file:lines() do
                local clean = IOP_Trim(string.gsub(line, "[;#].*$", ""))
                local sectionName = string.match(clean, "^%[([^%]]+)%]$")
                if sectionName ~= nil then
                    section = string.lower(IOP_Trim(sectionName))
                elseif section == "onlinepoints" then
                    local key, value = string.match(clean, "^([^=]+)=(.*)$")
                    if key ~= nil then values[string.lower(IOP_Trim(key))] = IOP_Trim(value) end
                end
            end
            file:close()
        end
    end

    local config = IOP_DefaultConfig()
    config.Enabled = IOP_ParseEnabled(values.enabled, config.Enabled)
    config.IntervalSeconds = IOP_ClampInteger(values.intervalseconds, config.IntervalSeconds, 5, 86400)
    config.PointsPerInterval = IOP_ClampInteger(values.pointsperinterval, config.PointsPerInterval, 1, 100000)

    for vip = 0, 6 do
        local rawVip = values["vipbonus" .. tostring(vip)]
        if rawVip ~= nil then
            config.VipBonus[vip] = IOP_ClampInteger(rawVip, config.VipBonus[vip] or 0, 0, 100000)
        end
    end

    local rewardCount = tonumber(values.rewardcount)
    if rewardCount ~= nil then
        rewardCount = IOP_ClampInteger(rewardCount, 0, 0, IOP_MAX_REWARDS)
        config.Rewards = {}
        for index = 1, rewardCount do
            local raw = values["reward" .. tostring(index)] or ""
            local parts = {}
            for part in string.gmatch(raw, "([^,]+)") do table.insert(parts, IOP_Trim(part)) end
            local itemValue, costValue = parts[1], parts[2]
            if itemValue ~= nil and costValue ~= nil then
                table.insert(config.Rewards, {
                    ItemId = IOP_ClampInteger(itemValue, 0, 1, 4294967295),
                    Cost = IOP_ClampInteger(costValue, 0, 1, 2000000000),
                    ClaimLimit = IOP_ClampInteger(parts[3], 3, 1, 2000000000),
                    ClaimKey = IOP_ClampInteger(parts[4], 100 + index, 101, 2000000000),
                    IsHot = IOP_ParseEnabled(parts[5], false)
                })
            end
        end
    elseif values.rewarditemid ~= nil or values.rewardcost ~= nil then
        config.Rewards = {{
            ItemId = IOP_ClampInteger(values.rewarditemid, 730004, 1, 4294967295),
            Cost = IOP_ClampInteger(values.rewardcost, 510, 1, 2000000000),
            ClaimLimit = 3,
            ClaimKey = 101,
            IsHot = true
        }}
    end

    local marathonCount = tonumber(values.marathoncount)
    if marathonCount ~= nil then
        marathonCount = IOP_ClampInteger(marathonCount, 0, 0, IOP_MAX_MARATHONS)
        config.Marathons = {}
        for index = 1, marathonCount do
            local raw = values["marathon" .. tostring(index)] or ""
            local parts = {}
            for part in string.gmatch(raw, "([^,]+)") do table.insert(parts, IOP_Trim(part)) end
            if parts[1] ~= nil and parts[2] ~= nil then
                table.insert(config.Marathons, {
                    Minutes = IOP_ClampInteger(parts[1], 30 * index, 1, 1440),
                    BonusPoints = IOP_ClampInteger(parts[2], 25 * index, 0, 2000000000),
                    BonusItemId = IOP_ClampInteger(parts[3], 0, 0, 4294967295),
                    Enabled = IOP_ParseEnabled(parts[4], true)
                })
            end
        end
    end

    return config
end

local function IOP_GetItemName(itemId)
    if itemId == nil or itemId <= 0 then return "None" end
    if Get_ItemtypeName ~= nil then
        local ok, name = pcall(Get_ItemtypeName, itemId)
        if ok and type(name) == "string" and name ~= "" and name ~= "-1" then return name end
    end
    return "item " .. tostring(itemId)
end

local function IOP_Message(userId, message)
    if User_TalkChannel2005 ~= nil then
        pcall(User_TalkChannel2005, "[OnlinePoints] " .. message, userId)
    end
end

local function IOP_GetBalance(userId)
    local ok, raw = pcall(Get_UserStatisticValue, IOP_STAT_EVENT, IOP_STAT_BALANCE, userId)
    local value = (ok and tonumber(raw)) or 0
    if value < 0 then return 0 end
    return math.floor(value)
end

local function IOP_GetTodaySeconds(userId)
    local ok, raw = pcall(Get_UserStatisticValue, IOP_STAT_EVENT, IOP_STAT_TODAY_SECONDS, userId)
    local value = (ok and tonumber(raw)) or 0
    if value < 0 then return 0 end
    return math.floor(value)
end

local function IOP_EnsureDailyReset(userId)
    userId = tonumber(userId) or 0
    if userId <= 0 then return end
    local todayStamp = IOP_GetTodayStamp()
    if todayStamp <= 0 then return end
    local ok, rawDate = pcall(Get_UserStatisticValue, IOP_STAT_EVENT, IOP_STAT_TODAY_DATE, userId)
    local savedDate = (ok and tonumber(rawDate)) or 0
    if savedDate ~= todayStamp then
        pcall(Task_SetStatistic, IOP_STAT_EVENT, IOP_STAT_TODAY_DATE, todayStamp, 1, userId)
        pcall(Task_SetStatistic, IOP_STAT_EVENT, IOP_STAT_TODAY_SECONDS, 0, 1, userId)
        for tier = 1, IOP_MAX_MARATHONS do
            pcall(Task_SetStatistic, IOP_STAT_EVENT, IOP_STAT_MARATHON_BASE + tier, 0, 1, userId)
        end
    end
end

local function IOP_GetUserVipLevel(userId)
    userId = tonumber(userId) or 0
    if userId <= 0 or Get_UserVip == nil then return 0 end
    local ok, vip = pcall(Get_UserVip, userId)
    if not ok then return 0 end
    return IOP_ClampInteger(vip, 0, 0, 6)
end

local function IOP_GetClaimed(userId, reward)
    if userId <= 0 or reward == nil then return 0 end
    local ok, raw = pcall(Get_UserStatisticValue, IOP_STAT_EVENT, reward.ClaimKey, userId)
    local value = (ok and tonumber(raw)) or 0
    return math.max(0, math.floor(value))
end

local function IOP_UpdateNpcDialog(config, userId)
    if tNpcGossip == nil or tNpcGossip[IOP_NPC_ID] == nil then return end
    userId = tonumber(userId) or 0
    local gossip = tNpcGossip[IOP_NPC_ID]
    local options = {}
    for index = 1, IOP_MAX_REWARDS do
        local optionId = IOP_REWARD_OPTION_BASE + index
        gossip["Option" .. tostring(optionId)] = nil
        gossip["OptionFunc" .. tostring(optionId)] = nil
    end
    for index, reward in ipairs(config.Rewards) do
        local optionId = IOP_REWARD_OPTION_BASE + index
        local itemName = IOP_GetItemName(reward.ItemId)
        local claimed = IOP_GetClaimed(userId, reward)
        local remaining = math.max(0, reward.ClaimLimit - claimed)
        gossip["Option" .. tostring(optionId)] = itemName .. " - " .. reward.Cost ..
            " Points - Available (" .. remaining .. "/" .. reward.ClaimLimit .. ")"
        gossip["OptionFunc" .. tostring(optionId)] = "ImperialOnlinePoints_Exchange</N>" .. tostring(index)
        table.insert(options, optionId)
    end
    table.insert(options, IOP_CLOSE_OPTION)
    gossip["tOption1-1"] = options
    local balanceText = userId > 0 and tostring(IOP_GetBalance(userId)) or "0"
    gossip["Text111"] = "Welcome to the Imperial Online Sanctuary.\nYour current balance: " ..
        balanceText .. " Points.\nStay online to earn " ..
        config.PointsPerInterval .. "+ point(s) every " .. config.IntervalSeconds ..
        " second(s). Choose a reward below or use the Online Sanctuary button on your HUD."
    if #config.Rewards == 0 then
        gossip["Text111"] = gossip["Text111"] .. "\nNo rewards are available right now."
    end
end

function ImperialOnlinePoints_RefreshConfig(userId)
    local config = IOP_ReadConfig()
    IOP_Runtime.config = config
    userId = tonumber(userId) or 0
    if userId > 0 or not IOP_Runtime.dialogInitialized then
        IOP_UpdateNpcDialog(config, userId)
        IOP_Runtime.dialogInitialized = true
    end
    return config
end

local function IOP_ScheduleTick(userId, sessionToken, delay)
    if User_SetTimer == nil then return false end
    delay = IOP_ClampInteger(delay, 60, 5, 86400)
    return User_SetTimer(delay,
        "ImperialOnlinePoints_Tick</N>" .. tostring(userId) .. "</N>" .. tostring(sessionToken), 0, userId)
end

local function IOP_EnsureSession(userId)
    userId = tonumber(userId) or 0
    if userId <= 0 then return end
    IOP_EnsureDailyReset(userId)
    if IOP_Runtime.sessions[userId] == nil then
        IOP_Runtime.sessions[userId] = 1
        local config = IOP_Runtime.config or ImperialOnlinePoints_RefreshConfig()
        IOP_ScheduleTick(userId, 1, config.IntervalSeconds)
    end
end

function ImperialOnlinePoints_Tick(userId, sessionToken)
    userId = tonumber(userId) or 0
    sessionToken = tonumber(sessionToken) or 0
    if userId <= 0 or IOP_Runtime.sessions[userId] ~= sessionToken then return end
    local config = IOP_Runtime.config or ImperialOnlinePoints_RefreshConfig()
    IOP_EnsureDailyReset(userId)
    if config.Enabled then
        local vipLevel = IOP_GetUserVipLevel(userId)
        local vipBonus = (config.VipBonus and config.VipBonus[vipLevel]) or 0
        local totalAward = math.max(1, config.PointsPerInterval + vipBonus)
        local balance = IOP_GetBalance(userId)
        local updated = math.min(2000000000, balance + totalAward)
        local award = updated - balance
        local todaySec = IOP_GetTodaySeconds(userId)
        local updatedSec = math.min(86400, todaySec + config.IntervalSeconds)
        pcall(Task_SetStatistic, IOP_STAT_EVENT, IOP_STAT_TODAY_SECONDS, updatedSec, 1, userId)
        if award > 0 and Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, updated, 1, userId) then
            if vipBonus > 0 then
                IOP_Message(userId, "You received " .. award .. " OP (Base " .. config.PointsPerInterval .. " + VIP" .. vipLevel .. " Bonus " .. vipBonus .. "). Balance: " .. updated .. " OP.")
            else
                IOP_Message(userId, "You received " .. award .. " OP. Balance: " .. updated .. " OP.")
            end
        end
    end
    IOP_ScheduleTick(userId, sessionToken, config.IntervalSeconds)
end

function ImperialOnlinePoints_OnLogin()
    local userId = tonumber(Get_UserId()) or 0
    if userId <= 0 then return end
    IOP_EnsureDailyReset(userId)
    local nextToken = (IOP_Runtime.sessions[userId] or 0) + 1
    IOP_Runtime.sessions[userId] = nextToken
    local config = IOP_Runtime.config or ImperialOnlinePoints_RefreshConfig()
    IOP_ScheduleTick(userId, nextToken, config.IntervalSeconds)
end

function ImperialOnlinePoints_ExchangeByUser(userId, rewardIndex)
    userId = tonumber(userId) or 0
    rewardIndex = math.floor(tonumber(rewardIndex) or 0)
    if userId <= 0 then return false, "Invalid player session." end
    IOP_EnsureSession(userId)
    if IOP_Runtime.purchaseLocks[userId] then
        IOP_Message(userId, "An exchange is already being processed.")
        return false, "An exchange is already being processed."
    end
    IOP_Runtime.purchaseLocks[userId] = true
    local deductedBalance, originalBalance, savedClaimCount, originalClaimCount, savedClaimKey, rewardCreated = nil, nil, nil, nil, nil, false
    local resultOk = false
    local resultMsg = "Exchange failed."
    local ok, err = pcall(function()
        local config = ImperialOnlinePoints_RefreshConfig(userId)
        if not config.Enabled then
            resultMsg = "The Online Sanctuary is currently disabled."
            IOP_Message(userId, resultMsg)
            return
        end
        local reward = config.Rewards[rewardIndex]
        if reward == nil then
            resultMsg = "That reward is no longer configured."
            IOP_Message(userId, resultMsg)
            return
        end
        local itemName = IOP_GetItemName(reward.ItemId)
        if itemName == "item " .. tostring(reward.ItemId) then
            resultMsg = "The configured reward item does not exist."
            IOP_Message(userId, resultMsg)
            return
        end
        if not User_CheckLeftSpace(1, userId) then
            resultMsg = "Inventory full! Free at least 1 slot."
            IOP_Message(userId, resultMsg)
            return
        end
        local claimed = IOP_GetClaimed(userId, reward)
        if claimed >= reward.ClaimLimit then
            resultMsg = "Claim limit reached for " .. itemName .. " (" .. reward.ClaimLimit .. "/" .. reward.ClaimLimit .. ")."
            IOP_Message(userId, resultMsg)
            return
        end
        local balance = IOP_GetBalance(userId)
        if balance < reward.Cost then
            resultMsg = "Need " .. reward.Cost .. " OP (You have " .. balance .. " OP)."
            IOP_Message(userId, resultMsg)
            return
        end
        local newBalance = balance - reward.Cost
        if not Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, newBalance, 1, userId) then
            resultMsg = "Balance could not be saved."
            IOP_Message(userId, resultMsg)
            return
        end
        originalBalance, deductedBalance = balance, newBalance
        local newClaimCount = claimed + 1
        if not Task_SetStatistic(IOP_STAT_EVENT, reward.ClaimKey, newClaimCount, 1, userId) then
            Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, balance, 1, userId)
            deductedBalance = nil
            resultMsg = "Claim counter could not be saved. Points restored."
            IOP_Message(userId, resultMsg)
            return
        end
        originalClaimCount, savedClaimCount, savedClaimKey = claimed, newClaimCount, reward.ClaimKey
        if not Item_AddNewItem(reward.ItemId, "", userId) then
            Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, balance, 1, userId)
            Task_SetStatistic(IOP_STAT_EVENT, reward.ClaimKey, claimed, 1, userId)
            deductedBalance = nil
            savedClaimCount = nil
            resultMsg = "Item could not be created. Points restored."
            IOP_Message(userId, resultMsg)
            return
        end
        rewardCreated = true
        resultOk = true
        local remainingClaims = reward.ClaimLimit - newClaimCount
        resultMsg = "Redeemed " .. itemName .. "! Balance: " .. newBalance .. " OP (" .. remainingClaims .. "/" .. reward.ClaimLimit .. " left)."
        IOP_Message(userId, resultMsg)
    end)
    IOP_Runtime.purchaseLocks[userId] = nil
    if not ok then
        if deductedBalance ~= nil and not rewardCreated and originalBalance ~= nil then
            Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, originalBalance, 1, userId)
        end
        if savedClaimCount ~= nil and not rewardCreated and originalClaimCount ~= nil and savedClaimKey ~= nil then
            Task_SetStatistic(IOP_STAT_EVENT, savedClaimKey, originalClaimCount, 1, userId)
        end
        resultMsg = "The exchange failed safely."
        IOP_Message(userId, resultMsg)
        if Sys_SaveAbnormalLog ~= nil then
            Sys_SaveAbnormalLog("ImperialOnlinePoints exchange error for user " .. userId .. ": " .. tostring(err))
        end
    end
    return resultOk, resultMsg
end

function ImperialOnlinePoints_ClaimMarathonByUser(userId, tierIndex)
    userId = tonumber(userId) or 0
    tierIndex = math.floor(tonumber(tierIndex) or 0)
    if userId <= 0 then return false, "Invalid player session." end
    IOP_EnsureSession(userId)
    if IOP_Runtime.purchaseLocks[userId] then
        return false, "Another claim is already being processed."
    end
    IOP_Runtime.purchaseLocks[userId] = true
    local resultOk = false
    local resultMsg = "Milestone claim failed."
    local ok, err = pcall(function()
        local config = ImperialOnlinePoints_RefreshConfig(userId)
        if not config.Enabled then
            resultMsg = "The Online Sanctuary is currently disabled."
            IOP_Message(userId, resultMsg)
            return
        end
        local tier = config.Marathons and config.Marathons[tierIndex]
        if tier == nil or not tier.Enabled then
            resultMsg = "That marathon milestone is not active."
            IOP_Message(userId, resultMsg)
            return
        end
        local statKey = IOP_STAT_MARATHON_BASE + tierIndex
        local _, rawClaimed = pcall(Get_UserStatisticValue, IOP_STAT_EVENT, statKey, userId)
        if (tonumber(rawClaimed) or 0) >= 1 then
            resultMsg = "You already claimed this daily milestone today."
            IOP_Message(userId, resultMsg)
            return
        end
        local todaySec = IOP_GetTodaySeconds(userId)
        local reqSec = tier.Minutes * 60
        if todaySec < reqSec then
            local remMin = math.ceil((reqSec - todaySec) / 60)
            resultMsg = "Stay online " .. remMin .. " more minute(s) to unlock this chest."
            IOP_Message(userId, resultMsg)
            return
        end
        if tier.BonusItemId > 0 and not User_CheckLeftSpace(1, userId) then
            resultMsg = "Inventory full! Free at least 1 slot first."
            IOP_Message(userId, resultMsg)
            return
        end
        if not Task_SetStatistic(IOP_STAT_EVENT, statKey, 1, 1, userId) then
            resultMsg = "Could not record milestone claim."
            return
        end
        local balance = IOP_GetBalance(userId)
        local newBalance = math.min(2000000000, balance + tier.BonusPoints)
        if tier.BonusPoints > 0 and not Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, newBalance, 1, userId) then
            Task_SetStatistic(IOP_STAT_EVENT, statKey, 0, 1, userId)
            resultMsg = "Could not award bonus points."
            return
        end
        local itemText = ""
        if tier.BonusItemId > 0 then
            if not Item_AddNewItem(tier.BonusItemId, "", userId) then
                Task_SetStatistic(IOP_STAT_EVENT, statKey, 0, 1, userId)
                Task_SetStatistic(IOP_STAT_EVENT, IOP_STAT_BALANCE, balance, 1, userId)
                resultMsg = "Could not deliver bonus item. Restored state."
                return
            end
            itemText = " + " .. IOP_GetItemName(tier.BonusItemId)
        end
        resultOk = true
        resultMsg = "Daily " .. tier.Minutes .. "m Chest claimed! +" .. tier.BonusPoints .. " OP" .. itemText .. "."
        IOP_Message(userId, resultMsg)
    end)
    IOP_Runtime.purchaseLocks[userId] = nil
    if not ok and Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("ImperialOnlinePoints marathon error for user " .. userId .. ": " .. tostring(err))
    end
    return resultOk, resultMsg
end

function ImperialOnlinePoints_Exchange(rewardIndex)
    local userId = tonumber(Get_UserId()) or 0
    if userId <= 0 then return end
    ImperialOnlinePoints_ExchangeByUser(userId, rewardIndex)
end

local function IOP_AppendResult(reqId, okFlag, message, userId)
    if io == nil or io.open == nil or reqId == nil or reqId == "" then return end
    local opened, f = pcall(io.open, IOP_RESULT_PATH, "a")
    if opened and f ~= nil then
        local cleanMsg = string.gsub(tostring(message or ""), "[\r\n\t]", " ")
        local bal = userId > 0 and IOP_GetBalance(userId) or 0
        f:write(tostring(reqId) .. "\t" .. (okFlag and "1" or "0") .. "\t" .. tostring(bal) .. "\t" .. cleanMsg .. "\n")
        f:close()
    end
end

local function IOP_ProcessQueue()
    if io == nil or io.open == nil then return end
    local opened, f = pcall(io.open, IOP_QUEUE_PATH, "r")
    if not opened or f == nil then return end
    local lines = {}
    for line in f:lines() do
        local clean = IOP_Trim(line)
        if clean ~= "" then table.insert(lines, clean) end
    end
    f:close()
    if #lines == 0 then return end

    local cleared, wf = pcall(io.open, IOP_QUEUE_PATH, "w")
    if cleared and wf ~= nil then wf:close() end

    for _, line in ipairs(lines) do
        local parts = {}
        for part in string.gmatch(line, "([^,]+)") do table.insert(parts, IOP_Trim(part)) end
        local cmd = string.upper(parts[1] or "")
        local userId = tonumber(parts[2]) or 0
        local arg1 = tonumber(parts[3]) or 0
        local reqId = parts[4] or ""
        if userId > 0 then
            if cmd == "PING" then
                IOP_EnsureSession(userId)
            elseif cmd == "REDEEM" then
                local okFlag, msg = ImperialOnlinePoints_ExchangeByUser(userId, arg1)
                IOP_AppendResult(reqId, okFlag, msg, userId)
            elseif cmd == "MARATHON" then
                local okFlag, msg = ImperialOnlinePoints_ClaimMarathonByUser(userId, arg1)
                IOP_AppendResult(reqId, okFlag, msg, userId)
            end
        end
    end
end

function ImperialOnlinePoints_ConfigPulse(generation)
    generation = tonumber(generation) or 0
    if generation ~= IOP_Runtime.configGeneration then return end
    IOP_Runtime.pulseCounter = (IOP_Runtime.pulseCounter or 0) + 1
    if IOP_Runtime.pulseCounter % 5 == 1 or IOP_Runtime.config == nil then
        ImperialOnlinePoints_RefreshConfig()
    end
    pcall(IOP_ProcessQueue)
    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(1, "ImperialOnlinePoints_ConfigPulse</N>" .. tostring(generation))
    end
end

function ImperialOnlinePoints_CloseDialog()
end

tNpcGossip = tNpcGossip or {}
tNpcGossip[IOP_NPC_ID] = tNpcGossip[IOP_NPC_ID] or DefaultNpc:new{}
local IOP_Gossip = tNpcGossip[IOP_NPC_ID]
IOP_Gossip["OptionHidden"] = 1
IOP_Gossip["nPageNum"] = 8
IOP_Gossip["Text1-1"] = {111}
IOP_Gossip["Option" .. IOP_CLOSE_OPTION] = "I will decide later."
IOP_Gossip["OptionFunc" .. IOP_CLOSE_OPTION] = "ImperialOnlinePoints_CloseDialog"
IOP_Gossip["Text1-2"] = {112}
IOP_Gossip["Text112"] = "The Online Points Reward Center is temporarily unavailable. Please check again later."
IOP_Gossip["tOption1-2"] = {IOP_CLOSE_OPTION}
IOP_Gossip["ChkFunc1-1"] = function()
    local userId = tonumber(Get_UserId()) or 0
    return ImperialOnlinePoints_RefreshConfig(userId).Enabled
end
IOP_Gossip["ChkFunc1-2"] = function()
    local userId = tonumber(Get_UserId()) or 0
    return not ImperialOnlinePoints_RefreshConfig(userId).Enabled
end

tSystem_PlayLogin_Func = tSystem_PlayLogin_Func or {}
if g_oldImperialOnlinePointsLoginHandler ~= nil then
    for index = #tSystem_PlayLogin_Func, 1, -1 do
        if tSystem_PlayLogin_Func[index] == g_oldImperialOnlinePointsLoginHandler then
            table.remove(tSystem_PlayLogin_Func, index)
        end
    end
end
g_oldImperialOnlinePointsLoginHandler = ImperialOnlinePoints_OnLogin
table.insert(tSystem_PlayLogin_Func, ImperialOnlinePoints_OnLogin)

ImperialOnlinePoints_ConfigPulse(IOP_Runtime.configGeneration)
