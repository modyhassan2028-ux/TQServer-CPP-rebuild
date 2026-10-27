----------------------------------------------------------------------------
-- Imperial Character Test Lab
-- Custom PM test tooling. It is deliberately separate from original gameplay.
-- Jobs are created by the local desktop UI and safely resumed on player login.
----------------------------------------------------------------------------

local function CharacterLab_Field(nUserId, sSql)
    local value = User_DbField(sSql, nUserId)
    if value == nil or value == false then
        return nil
    end
    return tostring(value)
end

local function CharacterLab_Number(nUserId, sSql)
    return tonumber(CharacterLab_Field(nUserId, sSql)) or 0
end

function CharacterLab_ProcessPending()
    local nUserId = Get_UserId()
    if nUserId == nil or nUserId <= 0 then
        return
    end

    -- A processing job is also selected so an interrupted login can resume it.
    local nJobId = CharacterLab_Number(nUserId, string.format(
        "SELECT id FROM cq_character_lab_job WHERE player_id=%d AND status IN(0,2) ORDER BY id LIMIT 1",
        nUserId
    ))
    if nJobId <= 0 then
        return
    end

    ExcuteSql(string.format(
        "UPDATE cq_character_lab_job SET status=2 WHERE id=%d AND player_id=%d AND status IN(0,2) LIMIT 1",
        nJobId, nUserId
    ))

    local nResourcesApplied = CharacterLab_Number(nUserId, string.format(
        "SELECT resources_applied FROM cq_character_lab_job WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
        nJobId, nUserId
    ))
    local nChiPoints = CharacterLab_Number(nUserId, string.format(
        "SELECT chi_points FROM cq_character_lab_job WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
        nJobId, nUserId
    ))
    local nJiangHuPoints = CharacterLab_Number(nUserId, string.format(
        "SELECT jianghu_points FROM cq_character_lab_job WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
        nJobId, nUserId
    ))

    if nResourcesApplied == 0 then
        if nChiPoints > 0 then
            User_AddStrengthValue(nChiPoints, nUserId)
        end
        if nJiangHuPoints > 0 then
            User_AddCultivation(nJiangHuPoints, nUserId)
        end
        ExcuteSql(string.format(
            "UPDATE cq_character_lab_job SET resources_applied=1 WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
            nJobId, nUserId
        ))
    end

    -- Read all pending IDs first because successful rows change status while processing.
    local nPendingCount = CharacterLab_Number(nUserId, string.format(
        "SELECT COUNT(id) FROM cq_character_lab_job_item WHERE job_id=%d AND status=0",
        nJobId
    ))
    local tPendingIds = {}
    for nOffset = 0, nPendingCount - 1 do
        local nItemRowId = CharacterLab_Number(nUserId, string.format(
            "SELECT id FROM cq_character_lab_job_item WHERE job_id=%d AND status=0 ORDER BY id LIMIT %d,1",
            nJobId, nOffset
        ))
        if nItemRowId > 0 then
            table.insert(tPendingIds, nItemRowId)
        end
    end

    local nAddedCount = 0
    for _, nItemRowId in ipairs(tPendingIds) do
        local nItemType = CharacterLab_Number(nUserId, string.format(
            "SELECT item_type FROM cq_character_lab_job_item WHERE id=%d AND job_id=%d AND status=0 LIMIT 1",
            nItemRowId, nJobId
        ))
        local sItemAttr = CharacterLab_Field(nUserId, string.format(
            "SELECT CAST(item_attr AS CHAR) FROM cq_character_lab_job_item WHERE id=%d AND job_id=%d AND status=0 LIMIT 1",
            nItemRowId, nJobId
        ))
        if nItemType > 0 and sItemAttr ~= nil and sItemAttr ~= "" then
            -- MsgServer creates the item and calculates its native checksum here.
            local bAdded = Item_AddNewItem(nItemType, sItemAttr, nUserId)
            if bAdded then
                ExcuteSql(string.format(
                    "UPDATE cq_character_lab_job_item SET status=1,claimed_at=NOW() WHERE id=%d AND job_id=%d AND status=0 LIMIT 1",
                    nItemRowId, nJobId
                ))
                nAddedCount = nAddedCount + 1
            end
        end
    end

    local nRemaining = CharacterLab_Number(nUserId, string.format(
        "SELECT COUNT(id) FROM cq_character_lab_job_item WHERE job_id=%d AND status=0",
        nJobId
    ))
    if nRemaining == 0 then
        ExcuteSql(string.format(
            "UPDATE cq_character_lab_job SET status=1,claimed_at=NOW() WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
            nJobId, nUserId
        ))
    else
        -- Keep the request pending; only missing items are retried on the next login.
        ExcuteSql(string.format(
            "UPDATE cq_character_lab_job SET status=0 WHERE id=%d AND player_id=%d AND status=2 LIMIT 1",
            nJobId, nUserId
        ))
    end

    SaveCustomLog("CharacterTestLab", string.format(
        "player=%d job=%d chi=%d jianghu=%d added=%d remaining=%d",
        nUserId, nJobId, nChiPoints, nJiangHuPoints, nAddedCount, nRemaining
    ))
end

-- TablePlayLogin is loaded before this module.
table.insert(tSystem_PlayLogin_Func, CharacterLab_ProcessPending)