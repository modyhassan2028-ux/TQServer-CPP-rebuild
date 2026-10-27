------------------------------------------------------------------------------------
--Name:			[征服][任务脚本]跨服任务卫国英雄
--Purpose:		跨服任务卫国英雄
--Creator: 		郑鋆
--Created:		2014/12/10
------------------------------------------------------------------------------------

-- 命名前缀
-- ServiceTask_PatrioticHero

-- taskId : 30002

-- 常量表
local tServiceTask_PatrioticHero_Count = {}
	-- 玩家等级要求
	tServiceTask_PatrioticHero_Count["Metempsychosis"] = 1
	tServiceTask_PatrioticHero_Count["Level"] = 110
	-- 任务掩码
	tServiceTask_PatrioticHero_Count["TaskId"] = 30002
	-- 任务累计最大次数
	tServiceTask_PatrioticHero_Count["MaxAccumulateTimes"] = 7
	-- 积分奖励
	tServiceTask_PatrioticHero_Count["Score"] = 3
	tServiceTask_PatrioticHero_Count["KillEmoneyLog"] = "350	4309	0	0	1	"
	
	tServiceTask_PatrioticHero_Count["TaskTime"] = "3 00:00 5 22:00"
	tServiceTask_PatrioticHero_Count["ActiveTime"] = "21:00 21:30"
	
	tServiceTask_PatrioticHero_Count["MapId"] = 1002
	
--------------------------------------逻辑部分-----------------------------------------
-- 接受任务判断
function ServiceTask_PatrioticHero_Accept(nNpcId)
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tServiceTask_PatrioticHero_Count["Level"],tServiceTask_PatrioticHero_Count["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"101-1")
		return
	end

	local nTaskId = tServiceTask_PatrioticHero_Count["TaskId"]
	
	-- 判断是否有接任务
	if not Task_ChkTaskDetail(nTaskId) then
		-- 玩家接受任务
		Task_AddTaskDetail(nTaskId)
		Task_SetMaxAccumulateTimes(nTaskId,tServiceTask_PatrioticHero_Count["MaxAccumulateTimes"])
	end

	LinkNpcGossipFunc_New(nNpcId,"103-1")
end

-- 杀人判断
function ServiceTask_PatrioticHero_Kill(nKillUserId)
	-- 判断是否是周三到周五之间的20:45到21:30
	if not Sys_ChkWeedTime(tServiceTask_PatrioticHero_Count["TaskTime"]) then
		return
	elseif not Sys_ChkDayTime(tServiceTask_PatrioticHero_Count["ActiveTime"]) then
		return
	end
	
	local nMapId = Get_UserMapId(nKillUserId)
	
	if nMapId ~= tServiceTask_PatrioticHero_Count["MapId"] then
		return
	end
	
	local nKillLeagueId = Get_UserLeagueId(nKillUserId)
	local nTargetLeagueId = Get_TargetUserLeagueId()
	
	if nKillLeagueId <= 0 or nTargetLeagueId <= 0 then
		return
	end
	
	-- 判断是否是同个服务器的玩家
	if ((not User_IsCross()) and (not User_TargetIsCross())) then
		-- 判断是否是同盟玩家
		if nKillLeagueId == nTargetLeagueId then
			return
		end
	end

	Sys_SaveEmoneyBuy(tServiceTask_PatrioticHero_Count["KillEmoneyLog"])

	-- 队伍判断
	if Get_UserTeamAmount(nKillUserId) > 1 then
		User_TeamExeFuncByTeamer(1,string.format("ServiceTask_PatrioticHero_TeamShare</N>%d",nKillUserId))
		return
	end
	
	ServiceTask_PatrioticHero_TeamShare(nKillUserId)
end

-- 组队共享
function ServiceTask_PatrioticHero_TeamShare(nTriggerUserId)
	local nUserId = Get_UserId()

	-- 加积分
	if National_War_AddIntegral(tServiceTask_PatrioticHero_Count["Score"]) then
		local str = string.format(tServiceTask_PatrioticHero_Text["Kill"],tServiceTask_PatrioticHero_Count["Score"])
		if nUserId ~= nTriggerUserId then
			-- str = string.format(tServiceTask_PatrioticHero_Text["TeamKill"],tServiceTask_PatrioticHero_Count["Score"])
			str = tServiceTask_PatrioticHero_Text["TeamKill"]
		end
	
		-- 杀人提示
		User_TalkChannel2005(str,nUserId)
	end
	
	Sys_SaveActionParamLog("action_gz","0,0,0,0,18000078,2,1,0")
end

-- 玩家锁魂
function ServiceTask_PatrioticHero_KeepGhost()
	-- 判断是否是周三到周五之间的20:30到21:30
	if not Sys_ChkWeedTime(tServiceTask_PatrioticHero_Count["TaskTime"]) then
		return
	elseif not Sys_ChkDayTime(tServiceTask_PatrioticHero_Count["ActiveTime"]) then
		return
	end
	
	-- 判断是否在双龙城
	local nMapId = Get_UserMapId()
	
	if nMapId ~= tServiceTask_PatrioticHero_Count["MapId"] then
		return
	end
	
	local nKillLeagueId = Get_UserLeagueId()
	local nTargetLeagueId = Get_TargetUserLeagueId()

	if nKillLeagueId <= 0 or nTargetLeagueId <= 0 then
		return
	end
	
	-- 判断是否是同个服务器的玩家
	if ((not User_IsCross()) and (not User_TargetIsCross())) then
		-- 判断是否是同盟玩家
		if nKillLeagueId == nTargetLeagueId then
			return
		end
	end
	
	-- 队伍判断
	local nUserId = Get_UserId()
	if Get_UserTeamAmount(nUserId) > 1 then
		User_TeamExeFuncByTeamer(1,string.format("ServiceTask_PatrioticHero_KeepGhostShare</N>%d",nUserId))
		return
	end
	ServiceTask_PatrioticHero_KeepGhostShare(nUserId)
end

-- 玩家锁魂组队共享
function ServiceTask_PatrioticHero_KeepGhostShare(nUserId)
	local nPlayer_Id = Get_UserId()
	
	if National_War_AddIntegral(10) then
		local str = tServiceTask_PatrioticHero_Text["KeepGhost"]
		
		if nUserId ~= nPlayer_Id then
			str = tServiceTask_PatrioticHero_Text["KeepGhost_TeamShare"]
		end
		User_TalkChannel2005(str,nPlayer_Id)
	end
	Sys_SaveActionParamLog("action_gz","0,0,0,0,18000078,2,2,0")
end

-- 玩家复活
function ServiceTask_PatrioticHero_SaveUser()
	-- 判断是否是周三到周五之间的20:30到21:30
	if not Sys_ChkWeedTime(tServiceTask_PatrioticHero_Count["TaskTime"]) then
		return
	elseif not Sys_ChkDayTime(tServiceTask_PatrioticHero_Count["ActiveTime"]) then
		return
	end
	
	-- 判断是否在双龙城
	local nMapId = Get_UserMapId()
	
	if nMapId ~= tServiceTask_PatrioticHero_Count["MapId"] then
		return
	end
	
	-- 判断是否是同个服务器的玩家
	if (User_IsCross() and (not User_TargetIsCross())) or ((not User_IsCross()) and User_TargetIsCross()) then
		return
	end
	
	-- 判断是否不是同盟玩家
	local nKillLeagueId = Get_UserLeagueId()
	local nTargetLeagueId = Get_TargetUserLeagueId()

	if nKillLeagueId <= 0 or nTargetLeagueId <= 0 or nKillLeagueId ~= nTargetLeagueId then
		return
	end

	-- 队伍判断
	local nUserId = Get_UserId()
	if Get_UserTeamAmount(nUserId) > 1 then
		User_TeamExeFuncByTeamer(1,string.format("ServiceTask_PatrioticHero_SaveUserShare</N>%d",nUserId))
		return
	end
	ServiceTask_PatrioticHero_SaveUserShare(nUserId)
end

-- 玩家复活组队共享
function ServiceTask_PatrioticHero_SaveUserShare(nUserId)
	local nPlayer_Id = Get_UserId()
	if National_War_AddIntegral(3) then
	
		local str = tServiceTask_PatrioticHero_Text["SaveUser"]		
		if nUserId ~= nPlayer_Id then
			str = tServiceTask_PatrioticHero_Text["SaveUser_TeamShare"]
		end
		User_TalkChannel2005(str,nPlayer_Id)
	end
	Sys_SaveActionParamLog("action_gz","0,0,0,0,18000078,2,3,0")
end

-- 玩家解锁
function ServiceTask_PatrioticHero_ClearKeepGhost()
	-- 判断是否是周三到周五之间的20:30到21:30
	if not Sys_ChkWeedTime(tServiceTask_PatrioticHero_Count["TaskTime"]) then
		return
	elseif not Sys_ChkDayTime(tServiceTask_PatrioticHero_Count["ActiveTime"]) then
		return
	end
	
	-- 判断是否在双龙城
	local nMapId = Get_UserMapId()
	
	if nMapId ~= tServiceTask_PatrioticHero_Count["MapId"] then
		return
	end
	
	-- 判断是否是同个服务器的玩家
	if (User_IsCross() and (not User_TargetIsCross())) or ((not User_IsCross()) and User_TargetIsCross()) then
		return
	end
	
	-- 判断是否不是同盟玩家
	local nKillLeagueId = Get_UserLeagueId()
	local nTargetLeagueId = Get_TargetUserLeagueId()

	if nKillLeagueId <= 0 or nTargetLeagueId <= 0 or nKillLeagueId ~= nTargetLeagueId then
		return
	end
	
	-- 队伍判断
	local nUserId = Get_UserId()
	if Get_UserTeamAmount(nUserId) > 1 then
		User_TeamExeFuncByTeamer(1,string.format("ServiceTask_PatrioticHero_ClearKeepGhostShare</N>%d",nUserId))
		return
	end
	ServiceTask_PatrioticHero_ClearKeepGhostShare(nUserId)	
end

-- 玩家解锁组队共享
function ServiceTask_PatrioticHero_ClearKeepGhostShare(nUserId)
	local nPlayer_Id = Get_UserId()
	if National_War_AddIntegral(3) then	
		local str = tServiceTask_PatrioticHero_Text["ClearKeepGhost"]		
		if nUserId ~= nPlayer_Id then
			str = tServiceTask_PatrioticHero_Text["ClearKeepGhost_TeamShare"]
		end
		User_TalkChannel2005(str,nPlayer_Id)
	end
	Sys_SaveActionParamLog("action_gz","0,0,0,0,18000078,2,4,0")
end


--------------------------------------NPC模块-------------------------------------------
-- 跨服任务大使
tNpcGossip[17400] = tNpcGossip[17400] or DefaultNpc:new{}

-- 保家卫国任务对白
tNpcGossip[17400]["Text100-1"] = {10011,10012,10013}
tNpcGossip[17400]["Text10011"] = tServiceTask_PatrioticHero_Text[17400]["Text10011"]
tNpcGossip[17400]["Text10012"] = tServiceTask_PatrioticHero_Text[17400]["Text10012"]
tNpcGossip[17400]["Text10013"] = tServiceTask_PatrioticHero_Text[17400]["Text10013"]
tNpcGossip[17400]["tOption100-1"] = {109}
tNpcGossip[17400]["ChkFunc100-1"] = function ()
	return not User_IsCross()
end

tNpcGossip[17400]["Option101"] = tServiceTask_PatrioticHero_Text[17400]["Option101"]
tNpcGossip[17400]["OptionFunc101"]="ServiceTask_PatrioticHero_Accept</N>17400"
tNpcGossip[17400]["OptionChkFunc101"] = function ()
	return not Task_ChkTaskDetail(tServiceTask_PatrioticHero_Count["TaskId"])
end
tNpcGossip[17400]["Option109"] = tServiceTask_PatrioticHero_Text[17400]["Option109"]

tNpcGossip[17400]["Text100-2"] = {10021}
tNpcGossip[17400]["Text10021"] = tServiceTask_PatrioticHero_Text[17400]["Text10021"]
tNpcGossip[17400]["tOption100-2"] = {111}
tNpcGossip[17400]["Option111"] = tServiceTask_PatrioticHero_Text[17400]["Option111"]

-- 【玩家选接受任务、失败、玩家等级不足】
tNpcGossip[17400]["Text101-1"] = {10111,10112}
tNpcGossip[17400]["Text10111"] = tServiceTask_PatrioticHero_Text[17400]["Text10111"]
tNpcGossip[17400]["Text10112"] = tServiceTask_PatrioticHero_Text[17400]["Text10112"]
tNpcGossip[17400]["tOption101-1"] = {105}
tNpcGossip[17400]["Option105"] = tServiceTask_PatrioticHero_Text[17400]["Option105"]

-- 【玩家选接受任务、失败、当日完成该任务为0】
tNpcGossip[17400]["Text102-1"] = {10211}
tNpcGossip[17400]["Text10211"] = tServiceTask_PatrioticHero_Text[17400]["Text10211"]
tNpcGossip[17400]["tOption102-1"] = {105}

-- 【玩家选接受任务、成功、玩家接受任务】
tNpcGossip[17400]["Text103-1"] = {10311,10312}
tNpcGossip[17400]["Text10311"] = tServiceTask_PatrioticHero_Text[17400]["Text10311"]
tNpcGossip[17400]["Text10312"] = tServiceTask_PatrioticHero_Text[17400]["Text10312"]
tNpcGossip[17400]["tOption103-1"] = {106}
tNpcGossip[17400]["Option106"] = tServiceTask_PatrioticHero_Text[17400]["Option106"]

-- 选项
tNpcGossip[17400]["Option100"] = tServiceTask_PatrioticHero_Text[17400]["Option100"]
tNpcGossip[17400]["OptionPoint100"]="100"

-- 玩家死亡触发
tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
table.insert(tUserKilled["tFunction"],ServiceTask_PatrioticHero_Kill)

-- 玩家锁魂
tKeepGhost["tFunction"] = tKeepGhost["tFunction"] or {}
table.insert(tKeepGhost["tFunction"],ServiceTask_PatrioticHero_KeepGhost)

-- 玩家复活
tUserSave["tFunction"] = tUserSave["tFunction"] or {}
table.insert(tUserSave["tFunction"],ServiceTask_PatrioticHero_SaveUser)

-- 玩家解锁
tClearKeepGhost["tFunction"] = tClearKeepGhost["tFunction"] or {}
table.insert(tClearKeepGhost["tFunction"],ServiceTask_PatrioticHero_ClearKeepGhost)
