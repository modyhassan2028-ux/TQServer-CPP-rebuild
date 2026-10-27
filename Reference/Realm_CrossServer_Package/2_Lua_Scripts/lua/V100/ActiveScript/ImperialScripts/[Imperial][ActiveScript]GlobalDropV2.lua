------------------------------------------------------------------------------------
-- GlobalDropV2: additive rewards only. Stock 6173 monster drops remain untouched.
------------------------------------------------------------------------------------

local DROP_CHANCE_MAX = 100000
local CONFIG_PATH = "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]GlobalDropConfig.lua"
local STATUS_PATH = "GlobalDropRuntime.status"

local tManagedEventMaps = {
    [1038]=true, [1645]=true, [7004]=true, [7012]=true, [7013]=true, [9100]=true, [9978]=true,
}
local tManagedEventMonsterIds = {}
for nId = 8501, 8526 do tManagedEventMonsterIds[nId] = true end
for nId = 8600, 8608 do tManagedEventMonsterIds[nId] = true end
tManagedEventMonsterIds[7862] = true

local tEquipBaseIds = {
    15003,16003,12002,15103,15201,12102,13000,13100,11700,11102,11800,11400,
    11300,42102,13300,13400,48002,41002,42002,50003,56002,53002,56102,90000
}

local function WriteRuntimeStatus(sText)
    pcall(function()
        local file = io.open(STATUS_PATH, "w")
        if file then
            file:write(string.gsub(tostring(sText or ""), "[\r\n]", " "))
            file:write("\n")
            file:close()
        end
    end)
end

local function IsIntegerInRange(value, minimum, maximum)
    local number = tonumber(value)
    return number and number == math.floor(number) and number >= minimum and number <= maximum
end

local function ValidateVipRows(rows, chanceField)
    if type(rows) ~= "table" then return false, "VIP rules are missing" end
    for vip = 0, 6 do
        local row = rows[vip]
        if type(row) ~= "table" then return false, "VIP " .. vip .. " rule is missing" end
        local chance = chanceField and row[chanceField] or row.Chance
        if chance ~= nil and not IsIntegerInRange(chance, 0, DROP_CHANCE_MAX) then
            return false, "VIP " .. vip .. " chance is invalid"
        end
    end
    return true
end

local function ValidateCandidate(config)
    if type(config) ~= "table" then return false, "configuration did not return a table" end
    if type(config.Revision) ~= "string" or config.Revision == "" then return false, "revision is missing" end
    if type(config.Settings) ~= "table" or type(config.Items) ~= "table" or
       type(config.Equipments) ~= "table" or type(config.MoneyMaps) ~= "table" or
       type(config.VipAutomation) ~= "table" then
        return false, "one or more required sections are missing"
    end
    if not IsIntegerInRange(config.Settings.MinUserLevel, 1, 140) or
       not IsIntegerInRange(config.Settings.LevelRange, 0, 140) or
       not IsIntegerInRange(config.Settings.OutOfRangeDivisor, 1, 100000) then
        return false, "global eligibility is invalid"
    end

    local itemCount = 0
    for _, item in ipairs(config.Items) do
        itemCount = itemCount + 1
        if not IsIntegerInRange(item.ItemId, 1, 4294967295) or
           not IsIntegerInRange(item.MapId or 0, 0, 4294967295) or
           not IsIntegerInRange(item.MonsterId or 0, 0, 4294967295) then
            return false, "an item ID or scope is invalid"
        end
        local ok, err = ValidateVipRows(item.VipRules)
        if not ok then return false, "item " .. item.ItemId .. ": " .. err end
        for vip = 0, 6 do
            local delivery = item.VipRules[vip].Delivery
            if delivery ~= "Ground" and delivery ~= "Bag" and delivery ~= "DirectCP" then
                return false, "item " .. item.ItemId .. ": invalid delivery"
            end
            if delivery == "DirectCP" and not item.IsCP then
                return false, "item " .. item.ItemId .. ": DirectCP requires a CP reward"
            end
        end
        if item.IsCP and not IsIntegerInRange(item.CPAmount, 1, 2000000000) then
            return false, "item " .. item.ItemId .. ": CP amount is invalid"
        end
    end

    local moneyCount = 0
    for mapId, map in pairs(config.MoneyMaps) do
        moneyCount = moneyCount + 1
        if not IsIntegerInRange(mapId, 1, 4294967295) then return false, "money map ID is invalid" end
        local ok, err = ValidateVipRows(map.VipRules)
        if not ok then return false, "money map " .. mapId .. ": " .. err end
        for vip = 0, 6 do
            if not IsIntegerInRange(map.VipRules[vip].Amount, 0, 2000000000) then
                return false, "money map " .. mapId .. ": amount is invalid"
            end
        end
    end

    for _, equipment in ipairs(config.Equipments) do
        if not IsIntegerInRange(equipment.QualityDigit, 0, 9) or type(equipment.VipRates) ~= "table" then
            return false, "equipment quality is invalid"
        end
        for vip = 0, 6 do
            if not IsIntegerInRange(equipment.VipRates[vip], 0, DROP_CHANCE_MAX) then
                return false, "equipment VIP rate is invalid"
            end
        end
    end
    for vip = 0, 6 do
        if type(config.VipAutomation[vip]) ~= "table" then return false, "VIP automation row is missing" end
        local specialTotal = 0
        for _, item in ipairs(config.Items) do
            if item.Enabled ~= false then
                local chance = tonumber(item.VipRules[vip].Chance) or 0
                specialTotal = specialTotal + chance
            end
        end
        if specialTotal > DROP_CHANCE_MAX then return false, "VIP " .. vip .. " special pool exceeds 100%" end
    end
    return true, nil, itemCount, moneyCount
end

function ImperialGlobalDrop_Reload()
    tImperialGlobalDropCandidate = nil
    local ok, err = pcall(dofile, CONFIG_PATH)
    if not ok then
        WriteRuntimeStatus("ERROR: GlobalDrop config load failed: " .. tostring(err))
        return false
    end
    local candidate = tImperialGlobalDropCandidate
    tImperialGlobalDropCandidate = nil
    local valid, reason, itemCount, moneyCount = ValidateCandidate(candidate)
    if not valid then
        WriteRuntimeStatus("ERROR: GlobalDrop revision rejected; previous revision remains active: " .. tostring(reason))
        return false
    end
    g_ImperialGlobalDropConfig = candidate
    WriteRuntimeStatus("OK: GlobalDrop revision=" .. candidate.Revision .. "; enabled=" ..
        tostring(candidate.Enabled ~= false) .. "; items=" .. itemCount .. "; moneyMaps=" .. moneyCount)
    return true
end

if not ImperialGlobalDrop_Reload() and type(g_ImperialGlobalDropConfig) ~= "table" then
    g_ImperialGlobalDropConfig = {
        Revision="fail-closed", Enabled=false,
        Settings={MinUserLevel=1,LevelRange=20,OutOfRangeDivisor=3},
        ExcludedMaps={},ExcludedMonsterIds={},MoneyMaps={},Items={},Equipments={},VipAutomation={}
    }
end

function GlobalMonsterDrop_GetMultiplier(nUserLevel, nMonsterLevel, settings)
    local denominator = 1
    if math.abs(nUserLevel - nMonsterLevel) > settings.LevelRange then
        denominator = denominator * settings.OutOfRangeDivisor
    end
    return 1, denominator
end

local function HasInventorySpace(nUserId)
    return type(User_CheckLeftSpace) ~= "function" or User_CheckLeftSpace(1, nUserId)
end

local function NotifyUser(message, nUserId)
    if not message or message == "" then return end
    if type(User_TalkChannel2005) == "function" then User_TalkChannel2005(message, nUserId)
    elseif type(User_TalkChannel2003) == "function" then User_TalkChannel2003(message, nUserId) end
end

local function DropNativeItem(nItemId, nUserId)
    local dropped = Monster_SysDropItem(nItemId)
    if dropped == false then dropped = Monster_SysDropItem(nItemId, nUserId) end
    return dropped ~= false
end

local function AddOneItemToBag(nItemId, nUserId)
    if not HasInventorySpace(nUserId) then return false end
    local result = Item_AddItem(nItemId,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,nUserId)
    return result ~= false and result ~= nil
end

local function DeliverItem(drop, delivery, nUserId)
    if delivery == "Bag" and AddOneItemToBag(drop.ItemId, nUserId) then
        NotifyUser(drop.InvMsg, nUserId)
        return "Bag"
    end
    if DropNativeItem(drop.ItemId, nUserId) then NotifyUser(drop.GroundMsg, nUserId) end
    return "Ground"
end

local function EffectiveItemChance(drop, vip, multiplierNumerator, multiplierDenominator)
    local rule = drop.VipRules and drop.VipRules[vip]
    local baseChance = rule and tonumber(rule.Chance) or tonumber(drop.Chance) or 0
    return math.max(0, math.floor(baseChance * multiplierNumerator / multiplierDenominator))
end

local tUserConvertPulse = {}

local function TryAutoConvert(nUserId, nFrom, nTo, nNeeded, message)
    if not Item_ChkAccItem(nFrom, nNeeded, 0, nUserId) or not HasInventorySpace(nUserId) then return false end
    if not Item_DelMulItem(nFrom, nFrom, nNeeded, 1, 0, nUserId) then return false end
    if not Item_AddItem(nTo,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,nUserId) then
        Item_AddItem(nFrom,0,nNeeded,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,nUserId)
        return false
    end
    NotifyUser(message, nUserId)
    return true
end

function GlobalMonsterDrop_OnMonsterKilled(nMonsterTypeId)
    local config = g_ImperialGlobalDropConfig
    if type(config) ~= "table" or config.Enabled == false then return end
    local nUserId = tonumber(Get_UserId())
    if not nUserId or nUserId <= 0 then return end
    local nMapId = tonumber(Get_UserMapId(nUserId)) or 0
    local nMonsterId = tonumber(nMonsterTypeId) or tonumber(Get_MonsterType()) or 0
    local questOwned = type(ImperialQuestEvent_IsOwnedMonster) == "function" and ImperialQuestEvent_IsOwnedMonster(nMonsterId)
    if tManagedEventMaps[nMapId] or tManagedEventMonsterIds[nMonsterId] or questOwned or
       (config.ExcludedMaps and config.ExcludedMaps[nMapId]) or
       (config.ExcludedMonsterIds and config.ExcludedMonsterIds[nMonsterId]) then return end

    local nVip = math.max(0, math.min(6, tonumber(Get_UserVip(nUserId)) or 0))
    local nUserLevel = tonumber(Get_UserLevel(nUserId)) or 0
    if nUserLevel < config.Settings.MinUserLevel then return end
    local nMonsterLevel = tonumber(Get_MonsterLevel()) or 1
    local nMulNum, nMulDen = GlobalMonsterDrop_GetMultiplier(nUserLevel, nMonsterLevel, config.Settings)

    local moneyMap = config.MoneyMaps[nMapId]
    if moneyMap and moneyMap.Enabled ~= false then
        local moneyRule = moneyMap.VipRules[nVip]
        local moneyChance = math.floor((moneyRule.Chance or 0) * nMulNum / nMulDen)
        if moneyRule.Amount > 0 and math.random(1, DROP_CHANCE_MAX) <= moneyChance and User_AddMoney then
            User_AddMoney(moneyRule.Amount, nUserId)
        end
    end

    local specialTotal = 0
    for _, drop in ipairs(config.Items) do
        if drop.Enabled ~= false and (drop.MapId == 0 or drop.MapId == nMapId) and
           (drop.MonsterId == 0 or drop.MonsterId == nMonsterId) then
            specialTotal = specialTotal + EffectiveItemChance(drop, nVip, nMulNum, nMulDen)
        end
    end
    local winner = nil
    if specialTotal > 0 and math.random(1, DROP_CHANCE_MAX) <= specialTotal then
        local winnerRoll, cursor = math.random(1, specialTotal), 0
        for _, drop in ipairs(config.Items) do
            if drop.Enabled ~= false and (drop.MapId == 0 or drop.MapId == nMapId) and
               (drop.MonsterId == 0 or drop.MonsterId == nMonsterId) then
                cursor = cursor + EffectiveItemChance(drop, nVip, nMulNum, nMulDen)
                if winnerRoll <= cursor then winner = drop break end
            end
        end
    end
    if winner then
        local vipRule = winner.VipRules[nVip]
        local delivery = vipRule and vipRule.Delivery or "Ground"
        if winner.IsCP and delivery == "DirectCP" then
            User_AddEMoney(winner.CPAmount, nUserId)
            local message = string.gsub(winner.DirectCPMsg or "You received {amount} CPs directly.", "{amount}", tostring(winner.CPAmount))
            NotifyUser(message, nUserId)
        else
            DeliverItem(winner, delivery, nUserId)
        end
        if winner.GlobalMsg and winner.GlobalMsg ~= "" and Sys_SystemBroadcast then
            local playerName = tostring(Get_UserName(nUserId) or "Someone")
            local formatted = string.gsub(tostring(winner.GlobalMsg), "{player}", function() return playerName end)
            if string.find(formatted, "%%", 1) then
                local okFormat, candidate = pcall(string.format, formatted, playerName)
                if okFormat and type(candidate) == "string" then
                    formatted = candidate
                else
                    formatted = string.gsub(formatted, "%%s", function() return playerName end)
                end
            end
            Sys_SystemBroadcast(formatted)
        end
    end

    for _, equipment in ipairs(config.Equipments) do
        local chance = equipment.VipRates[nVip] or equipment.Chance or 0
        chance = math.floor(chance * nMulNum / nMulDen)
        if equipment.Enabled ~= false and math.random(1, DROP_CHANCE_MAX) <= chance then
            local base = tEquipBaseIds[math.random(1, #tEquipBaseIds)]
            DropNativeItem((base * 10) + equipment.QualityDigit, nUserId)
            break
        end
    end

    local automation = config.VipAutomation[nVip] or {}
    local wonPackable = winner and (winner.ItemId == 1088001 or winner.ItemId == 1088000 or winner.ItemId == 720027 or winner.ItemId == 720028)
    local nowSec = os.time()
    if wonPackable or (nowSec - (tUserConvertPulse[nUserId] or 0) >= 3) then
        tUserConvertPulse[nUserId] = nowSec
        local packedMeteor = false
        local packedDb = false
        if automation.AutoPackMeteors then
            packedMeteor = TryAutoConvert(nUserId,1088001,720027,10,"Your Meteors have been packed into a MeteorScroll.")
        end
        if automation.AutoPackDragonBalls then
            packedDb = TryAutoConvert(nUserId,1088000,720028,10,"Your DragonBalls have been packed into a DBScroll.")
        end
        if automation.LargePackConversion then
            if packedMeteor or (winner and winner.ItemId == 720027) then
                TryAutoConvert(nUserId,720027,3004611,10,"")
            end
            if packedDb or (winner and winner.ItemId == 720028) then
                TryAutoConvert(nUserId,720028,3004615,10,"")
            end
        end
    end
end

if g_oldGlobalMonsterDrop then
    if type(tMonsterFunction) == "table" then
        for i = #tMonsterFunction, 1, -1 do
            if tMonsterFunction[i] == g_oldGlobalMonsterDrop then table.remove(tMonsterFunction, i) end
        end
    end
    if type(tMonster) == "table" then
        for _, info in pairs(tMonster) do
            if type(info) == "table" and type(info["tFunction"]) == "table" then
                for i = #info["tFunction"], 1, -1 do
                    if info["tFunction"][i] == g_oldGlobalMonsterDrop then table.remove(info["tFunction"], i) end
                end
            end
        end
    end
end

tMonsterFunction = tMonsterFunction or {}
table.insert(tMonsterFunction, GlobalMonsterDrop_OnMonsterKilled)
g_oldGlobalMonsterDrop = GlobalMonsterDrop_OnMonsterKilled
