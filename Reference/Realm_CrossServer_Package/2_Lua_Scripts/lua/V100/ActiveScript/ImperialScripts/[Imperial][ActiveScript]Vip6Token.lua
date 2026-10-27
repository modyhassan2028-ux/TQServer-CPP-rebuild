------------------------------------------------------------------------------------
-- Name:        [Imperial][ActiveScript]Vip6Token.lua
-- Purpose:     Interactive Yes/No Dialog, Cumulative Stacking & Clean RAM/DB Auto Sync
------------------------------------------------------------------------------------

-- Use the original client-supported VIP 6 token type. Custom high IDs are
-- accepted by the database but are not rendered reliably by the 6173 client.
local VIP6_ITEM_ID = 3004123
local VIP6_VALUE = 223860

function Imperial_ResolveOriginalVipValue(nUserId, nCurrentVipValue)
    nUserId = tonumber(nUserId) or 0
    nCurrentVipValue = tonumber(nCurrentVipValue) or 0
    if nCurrentVipValue < VIP6_VALUE then
        return nCurrentVipValue
    end

    local sQuery = string.format("SELECT original_vip_value FROM cq_vip_subscriptions WHERE role_id = %d AND status = 'ACTIVE' ORDER BY start_time ASC, id ASC LIMIT 1", nUserId)
    local nOriginalVipValue = tonumber(User_DbField(sQuery, nUserId))
    if nOriginalVipValue ~= nil and nOriginalVipValue > 0 then
        return nOriginalVipValue
    end

    -- GetUserInt(1048) is not reliable on this source before the VIP object is
    -- initialized.  cq_user is the authoritative permanent progress snapshot.
    local nDatabaseVipValue = tonumber(User_DbField(string.format(
        "SELECT vip_value FROM cq_user WHERE id = %d LIMIT 1", nUserId), nUserId))
    if nDatabaseVipValue ~= nil then
        return nDatabaseVipValue
    end

    return nCurrentVipValue
end

-- Step 1: Confirmation Action Triggered on Clicking "Yes"
function Imperial_Vip6Token_ActivateConfirm()
    local nUserId = tonumber(Get_UserId()) or 0
    if nUserId <= 0 then return end

    -- Check item exists in bag
    if not Item_ChkItem(VIP6_ITEM_ID, 1) then
        return
    end

    local nTargetVipValue = VIP6_VALUE -- VIP 6 threshold points
    local nTargetVipLevel = 6      -- VIP Level 6

    -- Read the permanent VIP value before the temporary override.
    local nCurVipValue = Imperial_ResolveOriginalVipValue(nUserId, tonumber(GetUserInt(nUserId, 1048)) or 0)
    local nNow = os.time()
    local nDuration = 30 * 86400 -- Official 30 Days
    local nBaseExpire = tonumber(User_DbField(string.format("SELECT COALESCE(MAX(expire_time), %d) FROM cq_vip_subscriptions WHERE role_id=%d AND status='ACTIVE' AND expire_time>%d", nNow, nUserId, nNow), nUserId)) or nNow
    local nNewExpire = nBaseExpire + nDuration

    -- Persist and verify the subscription before consuming the paid token.
    local sInsertQuery = string.format(
        "INSERT INTO cq_vip_subscriptions (account_id, role_id, original_vip_value, target_vip_level, target_vip_value, duration_seconds, start_time, expire_time, status, is_test, created_at) VALUES ((SELECT account_id FROM cq_user WHERE id=%d), %d, %d, 6, %d, %d, %d, %d, 'ACTIVE', 0, NOW())",
        nUserId, nUserId, nCurVipValue, nTargetVipValue, nDuration, nNow, nNewExpire
    )
    User_DbField(sInsertQuery, nUserId)
    local nSubscriptionOk = tonumber(User_DbField(string.format("SELECT COUNT(*) FROM cq_vip_subscriptions WHERE role_id=%d AND status='ACTIVE' AND start_time=%d AND expire_time=%d", nUserId, nNow, nNewExpire), nUserId)) or 0
    if nSubscriptionOk < 1 then
        User_TalkChannel2005("VIP 6 activation could not be saved. The token was not consumed.", nUserId)
        return
    end

    -- AccountServer applies the effective value and sends the live client
    -- refresh.  Do not overwrite cq_user here: an extension may already have
    -- recharge points earned while the temporary VIP is active.

    if not Item_DelItem(VIP6_ITEM_ID, 1, 0, nUserId) then
        User_TalkChannel2005("VIP 6 was activated, but the token could not be consumed. Please contact support.", nUserId)
        return
    end

    local sExpDateStr = os.date("%Y-%m-%d %H:%M:%S", nNewExpire)

    User_TalkChannel2005(string.format(" Congratulations! You activated VIP 6 (+30 Days)! Active until: %s", sExpDateStr))
end


-- Register item in tItem table for LinkItemMain routing with Confirmation Dialog
tItem = tItem or {}
tItem[VIP6_ITEM_ID] = tItem[VIP6_ITEM_ID] or {}
tItem[VIP6_ITEM_ID]["Text1-1"] = {111}
tItem[VIP6_ITEM_ID]["Text111"] = "Are you sure you want to activate/extend your VIP 6 Token (30 Days)? Using this token will add +30 Days to your VIP 6 duration."
tItem[VIP6_ITEM_ID]["tOption1-1"] = {1, 2}
tItem[VIP6_ITEM_ID]["Option1"] = "Yes, activate VIP 6 (+30 Days)"
tItem[VIP6_ITEM_ID]["OptionFunc1"] = "Imperial_Vip6Token_ActivateConfirm"
tItem[VIP6_ITEM_ID]["Option2"] = "No, cancel"
tItem[VIP6_ITEM_ID]["OptionFunc2"] = ""

-- Register live pollers in tSystem_Prompet_Func
tSystem_Prompet_Func = tSystem_Prompet_Func or {}

