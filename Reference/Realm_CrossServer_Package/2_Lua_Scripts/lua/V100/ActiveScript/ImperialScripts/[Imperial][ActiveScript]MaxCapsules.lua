------------------------------------------------------------------------------------
-- Name:        [Imperial][ActiveScript]MaxCapsules
-- Purpose:     Provides in-game capsule items to instantly max Chi or JiangHu
-- الغرض:       كبسولات لتكبير مستوى الشاي أو الجي يانج للحد الأقصى فوراً
------------------------------------------------------------------------------------

local CHI_CAPSULE_ID = 3008303
local JIANGHU_CAPSULE_ID = 3008304

-- Max Chi Function
function Imperial_MaxChi_UseItem(nItemId)
    local nUserId = tonumber(Get_UserId()) or 0
    if nUserId <= 0 then return end

    if not Item_ChkItem(CHI_CAPSULE_ID, 1) then
        User_TalkChannel2005("The Chi Max Capsule was not found in your inventory.", nUserId)
        return
    end

    -- Run database updates using ExcuteSql
    -- Check if record exists
    local nHasRecord = tonumber(User_DbField(string.format("SELECT COUNT(*) FROM cq_fate_player WHERE player_id = %d", nUserId), nUserId)) or 0
    
    if nHasRecord == 0 then
        -- Insert maxed stats (HP=64000, P-Atk=34000, M-Atk=14000, P-Def=74000 for all 4 gates)
        ExcuteSql(string.format("INSERT INTO cq_fate_player (player_id, fate1_attrib1, fate1_attrib2, fate1_attrib3, fate1_attrib4, fate2_attrib1, fate2_attrib2, fate2_attrib3, fate2_attrib4, fate3_attrib1, fate3_attrib2, fate3_attrib3, fate3_attrib4, fate4_attrib1, fate4_attrib2, fate4_attrib3, fate4_attrib4, attrib_lock_info) VALUES (%d, 63500, 30200, 10200, 72000, 63500, 30200, 10200, 72000, 63500, 30200, 10200, 72000, 63500, 30200, 10200, 72000, 0)", nUserId))
    else
        -- Update stats to max
        ExcuteSql(string.format("UPDATE cq_fate_player SET fate1_attrib1=63500, fate1_attrib2=30200, fate1_attrib3=10200, fate1_attrib4=72000, fate2_attrib1=63500, fate2_attrib2=30200, fate2_attrib3=10200, fate2_attrib4=72000, fate3_attrib1=63500, fate3_attrib2=30200, fate3_attrib3=10200, fate3_attrib4=72000, fate4_attrib1=63500, fate4_attrib2=30200, fate4_attrib3=10200, fate4_attrib4=72000 WHERE player_id = %d", nUserId))
    end

    local nVerified = tonumber(User_DbField(string.format("SELECT COUNT(*) FROM cq_fate_player WHERE player_id=%d AND fate1_attrib1=63500 AND fate1_attrib2=30200 AND fate1_attrib3=10200 AND fate1_attrib4=72000 AND fate2_attrib1=63500 AND fate2_attrib2=30200 AND fate2_attrib3=10200 AND fate2_attrib4=72000 AND fate3_attrib1=63500 AND fate3_attrib2=30200 AND fate3_attrib3=10200 AND fate3_attrib4=72000 AND fate4_attrib1=63500 AND fate4_attrib2=30200 AND fate4_attrib3=10200 AND fate4_attrib4=72000", nUserId), nUserId)) or 0
    if nVerified ~= 1 or not Item_DelItem(CHI_CAPSULE_ID, 1, 0, nUserId) then
        User_TalkChannel2005("Chi update could not be verified. The capsule was not consumed.", nUserId)
        return
    end

    User_TalkChannel2005("Your Chi has been successfully MAXED! Please relog to apply the stats.", nUserId)
end

-- Max JiangHu Function
function Imperial_MaxJiangHu_UseItem(nItemId)
    local nUserId = tonumber(Get_UserId()) or 0
    if nUserId <= 0 then return end

    if not Item_ChkItem(JIANGHU_CAPSULE_ID, 1) then
        User_TalkChannel2005("The JiangHu Max Capsule was not found in your inventory.", nUserId)
        return
    end

    -- Run database updates using ExcuteSql
    -- 1. General JiangHu record
    local nHasJh = tonumber(User_DbField(string.format("SELECT COUNT(*) FROM cq_jianghu_player WHERE player_id = %d", nUserId), nUserId)) or 0
    if nHasJh == 0 then
        local sPlayerName = Get_UserName(nUserId) or "Player"
        ExcuteSql(string.format("INSERT INTO cq_jianghu_player (player_id, enter_jianghu_flag, gongfu_name, power_level, genuine_qi_level, free_caltivate_param, total_power_value) VALUES (%d, 2, '%s', 1, 1, 920755, 81000)", nUserId, sPlayerName))
    else
        ExcuteSql(string.format("UPDATE cq_jianghu_player SET enter_jianghu_flag=2, power_level=1, genuine_qi_level=1, total_power_value=81000 WHERE player_id = %d", nUserId))
    end

    -- 2. Star powers (levels 1 to 9)
    -- Delete any existing star power rows for this player first to prevent duplicates
    ExcuteSql(string.format("DELETE FROM cq_jianghu_player_power WHERE player_id = %d", nUserId))

    -- Types to insert (13, 12, 2, 10, 1) and quality = 6 (golden star maxed)
    local tTypes = { 13, 12, 2, 10, 1, 12, 2, 10, 1 }
    for nLevel = 1, 9 do
        local nType = tTypes[nLevel] or 13
        ExcuteSql(string.format("INSERT INTO cq_jianghu_player_power (player_id, level, type1, quality1, type2, quality2, type3, quality3, type4, quality4, type5, quality5, type6, quality6, type7, quality7, type8, quality8, type9, quality9) VALUES (%d, %d, %d, 6, %d, 6, %d, 6, %d, 6, %d, 6, %d, 6, %d, 6, %d, 6, %d, 6)", 
            nUserId, nLevel, nType, nType, nType, nType, nType, nType, nType, nType, nType))
    end

    local nVerified = tonumber(User_DbField(string.format("SELECT COUNT(*) FROM cq_jianghu_player_power WHERE player_id=%d AND quality1=6 AND quality2=6 AND quality3=6 AND quality4=6 AND quality5=6 AND quality6=6 AND quality7=6 AND quality8=6 AND quality9=6", nUserId), nUserId)) or 0
    local nTotalPower = tonumber(User_DbField(string.format("SELECT total_power_value FROM cq_jianghu_player WHERE player_id=%d", nUserId), nUserId)) or 0
    if nVerified ~= 9 or nTotalPower ~= 81000 or not Item_DelItem(JIANGHU_CAPSULE_ID, 1, 0, nUserId) then
        User_TalkChannel2005("JiangHu update could not be verified. The capsule was not consumed.", nUserId)
        return
    end

    User_TalkChannel2005("Your JiangHu has been successfully MAXED! Please relog to apply the stats.", nUserId)
end

-- Register item hooks
tItem = tItem or {}

tItem[CHI_CAPSULE_ID] = tItem[CHI_CAPSULE_ID] or {}
tItem[CHI_CAPSULE_ID]["Function"] = function(nItemId, sItemName)
    Imperial_MaxChi_UseItem(nItemId)
end

tItem[JIANGHU_CAPSULE_ID] = tItem[JIANGHU_CAPSULE_ID] or {}
tItem[JIANGHU_CAPSULE_ID]["Function"] = function(nItemId, sItemName)
    Imperial_MaxJiangHu_UseItem(nItemId)
end
