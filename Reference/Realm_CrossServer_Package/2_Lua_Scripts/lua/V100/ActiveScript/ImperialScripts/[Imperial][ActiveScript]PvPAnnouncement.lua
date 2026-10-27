dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]PvPAnnouncementConfig.lua")

ImperialPvPAnnouncementRuntime = ImperialPvPAnnouncementRuntime or {generation=0}
ImperialPvPAnnouncementRuntime.generation = ImperialPvPAnnouncementRuntime.generation + 1
local generation = ImperialPvPAnnouncementRuntime.generation

local function IPVP_Log(text)
    if Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[ImperialPvPAnnouncement] " .. tostring(text or ""))
    end
end

local function IPVP_MapAllowed(mapId)
    local maps = (tImperialPvPAnnouncementConfig or {}).AllowedMaps or {}
    if #maps == 0 then return true end
    for _, configured in ipairs(maps) do
        if tonumber(configured) == tonumber(mapId) then return true end
    end
    return false
end

local function IPVP_DrainQueue()
    if io == nil or io.open == nil or os == nil or os.rename == nil then return end
    local queuePath, processingPath = "PvPAnnouncement.queue", "PvPAnnouncement.processing"
    local processing = io.open(processingPath, "r")
    if processing == nil then
        if os.rename(queuePath, processingPath) == nil then return end
        processing = io.open(processingPath, "r")
        if processing == nil then return end
    end
    for line in processing:lines() do
        local event, killerId, killer, victim, sequence = string.match(
            line, "^IPVP1|(%d+)|(%d+)|([^|]+)|([^|]+)|(%d+)$")
        event, killerId = tonumber(event), tonumber(killerId)
        if event ~= nil and event >= 1 and event <= 12 and killerId ~= nil and
           killerId >= 1000000 and killer ~= nil and victim ~= nil then
            local config = tImperialPvPAnnouncementConfig or {}
            local mapId = Get_UserMapId ~= nil and Get_UserMapId(killerId) or 0
            if config.Enabled == true and mapId > 0 and IPVP_MapAllowed(mapId) and
               User_TalkChannel2005 ~= nil then
                User_TalkChannel2005("#IKN1|"..tostring(event).."|"..killer.."|"..
                    victim.."|"..tostring(sequence).."#", killerId)
            end
        else
            IPVP_Log("discarded malformed queue row")
        end
    end
    processing:close()
    if os.remove ~= nil then pcall(os.remove, processingPath) end
end

function ImperialPvPAnnouncement_Pulse(requestGeneration)
    if requestGeneration ~= ImperialPvPAnnouncementRuntime.generation then return end
    local ok, errorText = pcall(dofile,
        "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]PvPAnnouncementConfig.lua")
    if not ok then IPVP_Log("live config parse failed: "..tostring(errorText)) end
    IPVP_DrainQueue()
    if Sys_SetLuaTimer ~= nil then
        Sys_SetLuaTimer(1,"ImperialPvPAnnouncement_Pulse</N>"..tostring(requestGeneration))
    end
end

if Sys_SetLuaTimer ~= nil then
    Sys_SetLuaTimer(1,"ImperialPvPAnnouncement_Pulse</N>"..tostring(generation))
end
