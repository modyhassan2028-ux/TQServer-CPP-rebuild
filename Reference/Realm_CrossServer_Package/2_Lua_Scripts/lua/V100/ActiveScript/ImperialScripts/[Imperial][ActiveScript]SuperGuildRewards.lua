dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]DurableRewardQueue.lua")
dofile("lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]SuperGuildRewardsConfig.lua")

tNpcFace = tNpcFace or {}
tNpcFace[816] = 32 -- lookface 8167: Super Guild War Officer

ImperialSuperGuildRuntime=ImperialSuperGuildRuntime or {generation=0,revision=""}
ImperialSuperGuildRuntime.generation=ImperialSuperGuildRuntime.generation+1
ImperialSuperGuildRuntime.revision=tostring(tImperialSuperGuildRevision or "")
local generation=ImperialSuperGuildRuntime.generation

local function ISG_Log(text)if Sys_SaveAbnormalLog~=nil then Sys_SaveAbnormalLog("[ImperialSuperGuild] "..tostring(text or "")) end end
local function ISG_Minutes(value)local h,m=string.match(tostring(value or ""),"^(%d%d):(%d%d)$");h,m=tonumber(h),tonumber(m);if h==nil or m==nil or h>23 or m>59 then return nil end;return h*60+m end
local function ISG_Window(now)local c=tImperialSuperGuildConfig or {};if not c.Enabled or now.wday-1~=tonumber(c.ClaimDay) then return false end;local first,last=ISG_Minutes(c.ClaimStart),ISG_Minutes(c.ClaimFinish);local current=now.hour*60+now.min;return first~=nil and last~=nil and first<=last and current>=first and current<=last end
local function ISG_Safe(value)return string.gsub(tostring(value or ""),"[^%w_]","_") end
local function ISG_SlotPath(week,guild,role,slot)return "TournamentRewardQueue\\SGW_"..ISG_Safe(week).."_"..tostring(guild).."_"..role.."_"..tostring(slot)..".claim" end
local function ISG_Read(path)if io==nil or io.open==nil then return nil end;local file=io.open(path,"r");if file==nil then return nil end;local value=file:read("*l");file:close();return value end
local function ISG_Reserve(week,guild,role,userId,maximum)
    if io==nil or io.open==nil or os==nil or os.rename==nil then return nil,"lua-io-unavailable" end
    for slot=1,maximum do local path=ISG_SlotPath(week,guild,role,slot);if tonumber(ISG_Read(path))==userId then if ISG_Read(path..".complete")~=nil then return nil,"already-claimed" end;return path,"resume" end end
    for slot=1,maximum do local path=ISG_SlotPath(week,guild,role,slot);if ISG_Read(path)==nil then local temporary=path.."."..tostring(userId)..".tmp";local file=io.open(temporary,"w");if file~=nil then file:write(tostring(userId).."\n");file:flush();file:close();if os.rename(temporary,path)~=nil then return path,nil end;if os.remove~=nil then pcall(os.remove,temporary) end end end end
    return nil,"role-slots-full"
end
local function ISG_Complete(path)
    local temporary=path..".complete.tmp";local file=io.open(temporary,"w");if file==nil then return false end;file:write("done\n");file:flush();file:close();return os.rename(temporary,path..".complete")~=nil
end
local function ISG_Queue(rewards,userId,token)
    local items,money,emoney={},0,0;for _,reward in ipairs(rewards or {}) do local value=math.max(0,tonumber(reward.Value) or 0);local amount=math.max(1,tonumber(reward.Amount) or 1);if reward.Kind=="Item" then table.insert(items,{ItemId=value,Amount=amount}) elseif reward.Kind=="Silver" then money=money+value*amount elseif reward.Kind=="CPs" then emoney=emoney+value*amount end end
    local contract={Token=token,UserId=userId,Money=money,EMoney=emoney,EventId=1038};if #items==1 then contract.ItemId=items[1].ItemId;contract.ItemCount=items[1].Amount elseif #items>1 then contract.Items=items end;return ImperialReward_Queue(contract)
end
function ImperialSuperGuild_Claim()
    local c=tImperialSuperGuildConfig or {};local userId=tonumber(Get_UserId()) or 0;if userId<=0 then return end;if not ISG_Window(os.date("*t")) then User_TalkChannel2005("The Super Guild reward claim window is closed.",userId);return end
    local guildId=tonumber(Get_UserGuildId(userId)) or 0;local winner=tonumber(Get_MapOwnerId(c.WinnerMapId)) or 0;if guildId<=0 or winner<=0 or guildId~=winner then User_TalkChannel2005("Your guild is not the current Guild War winner.",userId);return end
    local rank=tonumber(Get_UserGuildRank(userId)) or 0;local role,rewards,status,maximum;if rank==100 then role="leader";rewards=c.LeaderRewards;status=c.LeaderStatus;maximum=1 elseif rank==90 then role="deputy";rewards=c.DeputyRewards;status=c.DeputyStatus;maximum=math.max(1,math.min(20,tonumber(c.MaxDeputies) or 6)) else User_TalkChannel2005("Only the winning Guild Leader or Deputy Leaders can claim this profile.",userId);return end
    local week=os.date("%Y_%W");local reservation,reason=ISG_Reserve(week,guildId,role,userId,maximum);if reservation==nil then User_TalkChannel2005(reason=="already-claimed" and "You already claimed this week's reward." or "All reward slots for this role are already claimed.",userId);return end
    local ok,queueReason=ISG_Queue(rewards,userId,"superguild_"..week.."_"..guildId.."_"..role.."_"..userId);if not ok then if os.remove~=nil then pcall(os.remove,reservation) end;ISG_Log("queue failed user="..userId.." reason="..tostring(queueReason));User_TalkChannel2005("Reward persistence failed safely; please try again.",userId);return end
    status=math.max(0,tonumber(status) or 0);if status>0 and User_AddRoleStatus~=nil then if User_ChkRoleStatus~=nil and User_ChkRoleStatus(status,userId) and User_DelRoleStatus~=nil then User_DelRoleStatus(status,userId) end;local seconds=math.max(1,tonumber(c.StatusSeconds) or 86400);User_AddRoleStatus(status,math.max(0,tonumber(c.StatusPower) or 200),0,seconds,0,seconds,1,0,0,userId) end;if not ISG_Complete(reservation) then ISG_Log("completion marker failed user="..userId);User_TalkChannel2005("Reward delivered, but completion logging needs an operator check.",userId);return end;if Sys_SystemBroadcast~=nil then Sys_SystemBroadcast(tostring(Get_UserName(userId) or "A winner").." claimed the "..role.." Super Guild War reward.") end
end
function ImperialSuperGuild_CloseDialog()end
local function ISG_InstallGossip()local id=tonumber((tImperialSuperGuildConfig or {}).ClaimNpcId) or 0;if id<=0 then return end;tNpcGossip=tNpcGossip or {};tNpcGossip[id]=tNpcGossip[id] or DefaultNpc:new{};local g=tNpcGossip[id];g["OptionHidden"]=1;g["Text1-1"]={111};g["Text111"]="Claim the optional Super Guild War Leader/Deputy reward profile?";g["tOption1-1"]={1,2};g["Option1"]="Claim my reward.";g["OptionFunc1"]="ImperialSuperGuild_Claim</N>"..id;g["Option2"]="Not now.";g["OptionFunc2"]="ImperialSuperGuild_CloseDialog</N>"..id end
function ImperialSuperGuild_Pulse(requestGeneration)if requestGeneration~=ImperialSuperGuildRuntime.generation then return end;local ok=pcall(dofile,"lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]SuperGuildRewardsConfig.lua");if ok then local revision=tostring(tImperialSuperGuildRevision or "");if revision~=ImperialSuperGuildRuntime.revision then ImperialSuperGuildRuntime.revision=revision;ISG_InstallGossip() end end;if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(5,"ImperialSuperGuild_Pulse</N>"..tostring(requestGeneration)) end end
ISG_InstallGossip();if Sys_SetLuaTimer~=nil then Sys_SetLuaTimer(5,"ImperialSuperGuild_Pulse</N>"..tostring(generation)) end
