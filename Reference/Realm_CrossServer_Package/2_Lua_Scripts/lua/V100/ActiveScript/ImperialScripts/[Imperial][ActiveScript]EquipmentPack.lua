------------------------------------------------------------------------------------
-- Name:        [Imperial][ActiveScript]EquipmentPack
-- Purpose:     Gives class-specific equipment pack when player uses pack item
-- الغرض:       إعطاء باك معدات حسب الكلاس عند استخدام أيتم الباك
-- Generated:   Imperial Control Panel
------------------------------------------------------------------------------------

-- Load config from Imperial Control Panel (safe load - won't crash if file missing)
-- تحميل الإعدادات من لوحة التحكم (تحميل آمن - مش هيقع لو الملف مش موجود)
local bConfigLoaded = pcall(dofile, "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]EquipmentPackConfig.lua")
if not bConfigLoaded then
    Sys_SaveAbnormalLog("[Imperial] EquipmentPackConfig.lua not found - using defaults. Save from Control Panel to generate it.")
end

-- Use panel config or defaults
-- استخدام إعدادات البانل أو القيم الافتراضية
local PACK_ITEM_ID = tImperial_PackItemId or 3008302
local PACK_BAG_SPACE = tImperial_PackBagSpace or 12
local tSharedPack = tImperial_SharedPack or {}
local tClassPacks = tImperial_ClassPacks or {}

local function BuildEffectivePack(tClassPack, nBaseClass)
    local tResult = {}
    local function Merge(tSource, bFilterTargets)
        if type(tSource) ~= "table" then return end
        for i = 1, #tSource do
            local tItem = tSource[i]
            local nItemId = tItem and tonumber(tItem.ItemId) or 0
            local bAllowed = not bFilterTargets or type(tItem.Targets) ~= "table" or tItem.Targets[nBaseClass] == true
            if nItemId > 0 and bAllowed then
                -- Keep every configured row. Dual-wield professions intentionally
                -- need the same ItemId more than once.
                tResult[#tResult + 1] = tItem
            end
        end
    end
    Merge(tSharedPack, true)
    Merge(tClassPack, false)
    return tResult
end

-- Helper: Get base profession (10, 20, 40, 50, 60, 70, 80, 100)
-- دالة مساعدة: الحصول على الكلاس الأساسي
local function GetBaseProfession(nClass)
    if nClass >= 120 and nClass <= 125 then
        -- Kung Fu King: 120-125
        return 120
    elseif nClass >= 100 then
        -- Taoist: 100-145 -> 100
        return 100
    elseif nClass >= 50 and nClass <= 65 then
        -- Ninja Male (50-55) & Female (60-65) -> 50
        return 50
    end
    -- Others: first digit * 10 (e.g. 15 -> 10, 25 -> 20)
    return math.floor(nClass / 10) * 10
end

-- STC code for one-time-use tracking
-- كود STC لتتبع الاستخدام مرة واحدة
local PACK_STC_EVENT = 139
local PACK_STC_DATA = 50

-- Helper: Print debug messages to developer/PM accounts only
-- دالة مساعدة: طباعة رسائل الديباج لحسابات المطورين (PM/GM) فقط
local function DebugMsg(sMsg, nUserId)
    if not nUserId or nUserId <= 0 then return end
    local sName = Get_UserName(nUserId) or ""
    if string.find(sName, "%[PM%]") or string.find(sName, "%[GM%]") then
        User_TalkChannel2005(sMsg)
    end
end

-- Main function: triggered when player uses the pack item
-- الدالة الأساسية: تعمل لما اللاعب يستخدم أيتم الباك
function Imperial_EquipmentPack_UseItem(nItemTypeId)
    local nUserId = tonumber(Get_UserId()) or 0
    DebugMsg("DEBUG: UseItem function triggered!", nUserId)
    DebugMsg(string.format("DEBUG: Received ID=%s, Expected PACK_ITEM_ID=%s", tostring(nItemTypeId), tostring(PACK_ITEM_ID)), nUserId)
    
    if tonumber(nItemTypeId) ~= tonumber(PACK_ITEM_ID) then 
        DebugMsg("DEBUG: Item ID mismatch, aborting.", nUserId)
        return 
    end

    if nUserId <= 0 then return end
    if tImperial_PackEnabled == false then
        User_TalkChannel2005("The Starter Equipment Pack system is currently disabled.")
        return
    end
    DebugMsg("DEBUG: Player ID = " .. tostring(nUserId), nUserId)

    -- Check if already claimed (one-time use) - Bypassed for developer PM/GM test accounts
    -- التحقق إذا كان الأيتم اتاخد قبل كده (مرة واحدة بس) - يتم تخطيه للمطورين PM/GM لتسهيل التجربة
    local nClaimed = Get_UserStatisticValue(PACK_STC_EVENT, PACK_STC_DATA, nUserId) or 0
    DebugMsg("DEBUG: Claimed status = " .. tostring(nClaimed), nUserId)
    
    local sPlayerName = Get_UserName(nUserId) or ""
    local bIsDeveloper = string.find(sPlayerName, "%[PM%]") ~= nil or string.find(sPlayerName, "%[GM%]") ~= nil
    
    if nClaimed >= 1 and not bIsDeveloper then
        User_TalkChannel2005("You have already claimed your Equipment Pack.")
        return
    end

    -- Check level requirement (must be level 15 or higher to prevent server rejection of level 15 items)
    if Get_UserLevel(nUserId) < 15 then
        User_TalkChannel2005("You must be at least level 15 to open the Equipment Pack.", nUserId)
        return
    end

    -- Check bag space
    -- التحقق من مساحة الحقيبة
    -- Get player class and find pack
    -- الحصول على كلاس اللاعب وإيجاد الباك المناسب
    local nClass = Get_UserProfession(nUserId) or 10
    local nBaseClass = GetBaseProfession(nClass)
    local tPack = BuildEffectivePack(tClassPacks[nBaseClass], nBaseClass)
    
    DebugMsg(string.format("DEBUG: Class=%s, BaseClass=%s, PackExists=%s", tostring(nClass), tostring(nBaseClass), tostring(tPack ~= nil)), nUserId)

    if #tPack == 0 then
        User_TalkChannel2005("No equipment pack configured for your class.")
        return
    end

    -- Defense in depth: require enough space for the complete merged reward.
    local nRequiredSpace = math.max(tonumber(PACK_BAG_SPACE) or 0, #tPack)
    DebugMsg("DEBUG: Checking bag space: " .. tostring(nRequiredSpace), nUserId)
    if not User_CheckLeftSpace(nRequiredSpace, nUserId) then
        User_TalkChannel2005("Please make " .. nRequiredSpace .. " spaces in your inventory.", nUserId)
        return
    end

    -- Remove the pack item from inventory
    -- حذف أيتم الباك من الحقيبة
    local bDeleted = Item_DelItem(PACK_ITEM_ID, 1, 0, nUserId)
    DebugMsg("DEBUG: DelItem status = " .. tostring(bDeleted), nUserId)
    if not bDeleted then
        DebugMsg("DEBUG: Failed to delete pack item from inventory.", nUserId)
        return
    end

    -- Give all items in the pack
    -- إعطاء كل الأيتمات في الباك
    for i = 1, #tPack do
        local t = tPack[i]
        if t and t.ItemId and t.ItemId > 0 then
            Sys_SaveAbnormalLog(string.format("[Imperial Debug] Adding Item: ItemId=%s, Plus=%s, Bless=%s, Enchant=%s, Gem1=%s, Gem2=%s, Sock1=%s, Sock2=%s", 
                tostring(t.ItemId), tostring(t.Plus), tostring(t.Bless), tostring(t.Enchant), tostring(t.Gem1), tostring(t.Gem2), tostring(t.Sock1), tostring(t.Sock2)))
            -- Item_AddItem(itemId, flag, plus, monopoly, save_time, active, onlinetime, data,
            --              bless, add_life, addlevel_exp, enchant, gem1, gem2,
            --              socket1, socket2, amount, amount_limit, anti_monster, ident, color, userId)
            Item_AddItem(
                t.ItemId,           -- 1. nItemId
                0,                  -- 2. flag
                1,                  -- 3. addamount (quantity = 1)
                t.Monopoly or 0,    -- 4. monopoly
                0,                  -- 5. save_time
                0,                  -- 6. active
                0,                  -- 7. onlinetime
                0,                  -- 8. data
                t.Bless or 0,       -- 9. reduce_dmg (bless)
                t.Enchant or 0,     -- 10. add_life (Enchant HP)
                0,                  -- 11. addlevel_exp
                t.Plus or 0,        -- 12. magic3 (plus)
                t.Gem1 or 0,        -- 13. gem1
                t.Gem2 or 0,        -- 14. gem2
                t.Sock1 or 0,       -- 15. magic1 (socket 1)
                t.Sock2 or 0,       -- 16. magic2 (socket 2)
                0,                  -- 17. amount (durability)
                0,                  -- 18. amount_limit (durability limit)
                0,                  -- 19. anti_monster
                0,                  -- 20. ident
                t.Color or 0,       -- 21. color
                nUserId             -- 22. nUserId
            )
        end
    end

    -- Mark as claimed (one-time use)
    -- تسجيل إن الباك اتاخد (مرة واحدة)
    Task_SetStatistic(PACK_STC_EVENT, PACK_STC_DATA, 1, 1, nUserId)

    -- Notify player
    -- إشعار اللاعب
    User_TalkChannel2005("You received your Equipment Pack! Good luck!")
end

-- Register item function hook in the engine's default system
-- تسجيل الأيتم مع نظام تشغيل الأيتمات الافتراضي في السيرفر
tItem = tItem or {}
tItem[PACK_ITEM_ID] = tItem[PACK_ITEM_ID] or {}
tItem[PACK_ITEM_ID]["Function"] = function(nItemId, sItemName)
    Imperial_EquipmentPack_UseItem(nItemId)
end

-- Cleanup on reload
-- تنظيف عند إعادة التحميل
if g_oldImperial_EquipmentPack then
    g_oldImperial_EquipmentPack = nil
end
g_oldImperial_EquipmentPack = Imperial_EquipmentPack_UseItem
