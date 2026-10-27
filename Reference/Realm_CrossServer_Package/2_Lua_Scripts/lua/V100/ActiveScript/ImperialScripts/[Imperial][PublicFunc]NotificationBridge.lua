-- Imperial 6173 notification bridge.
-- Mirrors high-signal event and boss broadcasts through a private marker.
-- Patched clients consume the marker, render the in-game card and show a
-- Windows notification whenever Conquer is in the background.

g_ImperialNotificationSequence = g_ImperialNotificationSequence or 0

g_ImperialOriginalSystemBroadcast = g_ImperialOriginalSystemBroadcast or Sys_SystemBroadcast
local Imperial_OriginalSystemBroadcast = g_ImperialOriginalSystemBroadcast

local function Imperial_NotificationSafeText(value, maximum)
    local text = tostring(value or "")
    text = string.gsub(text, "[|#\r\n]", " ")
    text = string.gsub(text, "[%c]", " ")
    if string.len(text) > maximum then text = string.sub(text, 1, maximum) end
    return text
end

function Imperial_NotificationBroadcast(nType, sTitle, sMessage, nDuration)
    local message = Imperial_NotificationSafeText(sMessage, 192)
    local title = Imperial_NotificationSafeText(sTitle, 48)
    if message == "" or title == "" then return false end
    g_ImperialNotificationSequence =
        (g_ImperialNotificationSequence + 1) % 1000000
    local duration = math.max(2000,
        math.min(30000, tonumber(nDuration) or 9000))
    local marker = string.format("#INT1|%d|%d|%s|%s|%d#",
        math.max(1, math.min(6, tonumber(nType) or 6)), duration,
        title, message, g_ImperialNotificationSequence)
    return BrocastMsg(2005, marker)
end

local function Imperial_TryAutomaticNotification(sContent)
    local lower = string.lower(tostring(sContent or ""))
    local active = string.find(lower, "start", 1, true) or
        string.find(lower, "open", 1, true) or
        string.find(lower, "spawn", 1, true) or
        string.find(lower, "appear", 1, true) or
        string.find(lower, "registration", 1, true) or
        string.find(lower, "ready", 1, true) or
        string.find(lower, "begun", 1, true)
    if not active then return end

    local boss = string.find(lower, "boss", 1, true) or
        string.find(lower, "titan", 1, true) or
        string.find(lower, "ganoderma", 1, true)
    if boss then
        Imperial_NotificationBroadcast(4, "Boss Alert", sContent, 11000)
        return
    end

    -- Event cards are now emitted by the native outgoing SYSTEM announcement
    -- observer. It covers native events too and rejects registration/countdown
    -- text. Mirroring them here would create a second notification owner.
end

function Sys_SystemBroadcast(sContent)
    local result = Imperial_OriginalSystemBroadcast(sContent)
    if type(sContent) == "string" then
        Imperial_TryAutomaticNotification(sContent)
    end
    return result
end
