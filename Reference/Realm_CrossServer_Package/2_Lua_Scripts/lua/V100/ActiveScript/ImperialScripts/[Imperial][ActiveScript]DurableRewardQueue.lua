-- Shared durable reward publisher. The native TournamentRewardMail worker
-- consumes ITR1 requests using durable receipts and holds uncertain outcomes.

local function IRW_FileExists(path)
    if io == nil or io.open == nil then return false end
    local ok, file = pcall(io.open, path, "r")
    if ok and file ~= nil then file:close(); return true end
    return false
end

local function IRW_Hash(value)
    local hash = 5381
    value = tostring(value or "")
    for index = 1, string.len(value) do hash = (hash * 33 + string.byte(value, index)) % 2147483647 end
    return hash
end

local function IRW_Hash2(value)
    local hash = 7919
    value = tostring(value or "")
    for index = 1, string.len(value) do
        hash = (hash * 131 + string.byte(value, index) + index) % 2147483629
    end
    return hash
end

local function IRW_U32(value)
    value = tonumber(value)
    if value == nil or value < 0 or value > 4294967295 or value ~= math.floor(value) then return nil end
    return value
end

function ImperialReward_Queue(contract)
    contract = contract or {}
    local userId = IRW_U32(contract.UserId)
    if userId == nil or userId == 0 then return false, "invalid-user-id" end
    local items, totalItems = {}, 0
    if type(contract.Items) == "table" then
        for _, item in ipairs(contract.Items) do
            local itemType = IRW_U32(item.ItemId)
            local itemCount = IRW_U32(item.Amount)
            if itemType == nil or itemCount == nil or itemType <= 0 or itemCount <= 0 or itemCount > 100 or totalItems > 100 - itemCount then return false, "invalid-bundle-item" end
            totalItems = totalItems + itemCount; table.insert(items, {ItemId=itemType,Amount=itemCount})
        end
    else
        local itemType = IRW_U32(contract.ItemId or 0)
        local itemCount = IRW_U32(contract.ItemCount or 0)
        if itemType == nil or itemCount == nil or itemCount > 100 or
           (itemCount > 0 and itemType == 0) or (itemType > 0 and itemCount == 0) then return false, "invalid-item" end
        if itemCount > 0 then items={{ItemId=itemType,Amount=itemCount}}; totalItems=itemCount end
    end
    local money = IRW_U32(contract.Money or 0)
    local emoney = IRW_U32(contract.EMoney or 0)
    local eventId = IRW_U32(contract.EventId or 0)
    if money == nil or emoney == nil or eventId == nil or #items > 20 or
       (totalItems == 0 and money == 0 and emoney == 0) then return false, "invalid-contract" end
    if io == nil or io.open == nil or os == nil or os.rename == nil then return false, "lua-io-unavailable" end

    -- Two independent hashes make a filename collision materially less likely
    -- than the old single 31-bit key while keeping the token inside the native
    -- queue worker's strict filename/title limits.
    local token = "R_" .. tostring(IRW_Hash(contract.Token)) .. "_" .. tostring(IRW_Hash2(contract.Token)) .. "_" .. tostring(userId) .. "_" .. tostring(eventId)
    local base = "TournamentRewardQueue\\" .. token
    local tempPath, requestPath = base .. ".tmp", base .. ".req"
    if IRW_FileExists(requestPath) or IRW_FileExists(base .. ".processing") or
       IRW_FileExists(base .. ".done") or IRW_FileExists(base .. ".processing.done") or
       IRW_FileExists(base .. ".processing.review") or IRW_FileExists(base .. ".nativeprocessing") or
       IRW_FileExists(base .. ".nativeprocessing.review") or
       IRW_FileExists(base .. ".nativeprocessing.done") then return true, token end
    local opened, file = pcall(io.open, tempPath, "w")
    if not opened or file == nil then return false, "queue-open-failed" end
    if #items <= 1 then
        local item = items[1] or {ItemId=0,Amount=0}
        file:write("ITR1 ", token, " ", userId, " ", item.ItemId, " ", item.Amount, " ", money, " ", emoney, " 0 ", eventId, "\n")
    else
        file:write("IRB1 ", token, " ", userId, " ", money, " ", emoney, " ", eventId, " ", #items)
        for _, item in ipairs(items) do file:write(" ", item.ItemId, " ", item.Amount) end
        file:write("\n")
    end
    file:flush(); file:close()
    if os.rename(tempPath, requestPath) == nil then
        if os.remove ~= nil then pcall(os.remove, tempPath) end
        return false, "queue-publish-failed"
    end
    return true, token
end
