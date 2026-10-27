------------------------------------------------------------------------------------
--Name:			[征服][任务脚本]跨服任务开疆功臣
--Purpose:		跨服任务开疆功臣
--Creator: 		郑鋆
--Created:		2014/12/16
------------------------------------------------------------------------------------

-- 命名前缀
-- ServiceTask_HisHero

-- taskId : 30003

-- 常量表
local tServiceTask_HisHero_Count = {}
	-- 玩家等级要求
	tServiceTask_HisHero_Count["Metempsychosis"] = 1
	tServiceTask_HisHero_Count["Level"] = 110
	-- 任务掩码
	tServiceTask_HisHero_Count["TaskId"] = 30003
	-- 跨服地图限制
	tServiceTask_HisHero_Count["MapLimit"] = 2057
	-- 任务累计最大次数
	tServiceTask_HisHero_Count["MaxAccumulateTimes"] = 7
	-- 积分奖励
	tServiceTask_HisHero_Count["Score"] = 3
	tServiceTask_HisHero_Count["KillEmoneyLog"] = "350	4310	0	0	1	"

--------------------------------------逻辑部分-----------------------------------------
-- 接受任务判断
function ServiceTask_HisHero_Accept(nNpcId)
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tServiceTask_HisHero_Count["Level"],tServiceTask_HisHero_Count["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"201-1")
		return
	end

	local nTaskId = tServiceTask_HisHero_Count["TaskId"]
	
	-- 判断是否有接任务
	if not Task_ChkTaskDetail(nTaskId) then
		-- 玩家接受任务
		Task_AddTaskDetail(nTaskId)
		Task_SetMaxAccumulateTimes(nTaskId,tServiceTask_HisHero_Count["MaxAccumulateTimes"])
	end
	
	LinkNpcGossipFunc_New(nNpcId,"203-1")
end

-- 杀人判断
function ServiceTask_HisHero_Kill(nKillUserId)
	-- 判断杀人的玩家是否跨服玩家
	if not User_IsCross(nKillUserId) then
		return
	end
	
	-- 跨服战旗地图判断
	local nMap_Limit = tServiceTask_HisHero_Count["MapLimit"]
	
	if Get_UserMapId() == nMap_Limit then
		return
	end

	-- 判断掠夺战是否开启
	if not User_IsInPlunderWar() then
		return
	end
	
	Sys_SaveEmoneyBuy(tServiceTask_HisHero_Count["KillEmoneyLog"])
	
	-- 队伍判断
	if Get_UserTeamAmount() > 1 then
		User_TeamExeFuncByTeamer(1,string.format("ServiceTask_HisHero_TeamShare</N>%d",nKillUserId))
		return
	end
	
	ServiceTask_HisHero_TeamShare(nKillUserId)
end

-- 组队共享
function ServiceTask_HisHero_TeamShare(nTriggerUserId)
	-- 判断掠夺战是否开启
	if not User_IsInPlunderWar() then
		return
	end
	
	-- local nTaskId = tServiceTask_HisHero_Count["TaskId"]
	local nUserId = Get_UserId()
	
	-- 判断是否有接任务
	-- if not Task_ChkTaskDetail(nTaskId,nUserId) then
		-- return
	-- end

	-- local nData = Get_TaskDetailData1(nTaskId,nUserId) + 1
	-- Task_SetTaskDetailData1(nTaskId,nData,nUserId)
	
	-- 加积分
	if National_War_AddIntegral(tServiceTask_HisHero_Count["Score"]) then
		local str = string.format(tServiceTask_HisHero_Text["Kill"],tServiceTask_HisHero_Count["Score"])
		if nUserId ~= nTriggerUserId then
			str = string.format(tServiceTask_HisHero_Text["TeamKill"],tServiceTask_HisHero_Count["Score"])
		end
	
		-- 杀人提示
		User_TalkChannel2005(str,nUserId)
	end
end

-- 玩家锁魂
function ServiceTask_HisHero_KeepGhost()
	-- 判断是否是跨服玩家
	if not User_IsCross() then
		return
	end
	
	-- 判断掠夺战是否开启
	if not User_IsInPlunderWar() then
		return
	end
	
	-- 加积分
	if National_War_AddIntegral(1) then
		User_TalkChannel2005(tServiceTask_HisHero_Text["KeepGhost"])
	end
end

-- 玩家复活
function ServiceTask_HisHero_SaveUser()
	-- 判断是否是跨服玩家
	if not User_IsCross() then
		return
	end
	
	-- 判断掠夺战是否开启
	if not User_IsInPlunderWar() then
		return
	end
	
	-- 加积分
	if National_War_AddIntegral(1) then
		User_TalkChannel2005(tServiceTask_HisHero_Text["SaveUser"])
	end
end

-- 玩家解锁
function ServiceTask_HisHero_ClearKeepGhost()
	-- 判断是否是跨服玩家
	if not User_IsCross() then
		return
	end
	
	-- 判断掠夺战是否开启
	if not User_IsInPlunderWar() then
		return
	end
	
	-- 加积分
	if National_War_AddIntegral(1) then
		User_TalkChannel2005(tServiceTask_HisHero_Text["ClearKeepGhost"])
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 跨服任务大使
tNpcGossip[17400] = tNpcGossip[17400] or DefaultNpc:new{}

-- 主队白
tNpcGossip[17400]["Text200-1"] = {20011,20012,20013,20014}
tNpcGossip[17400]["Text20011"] = tServiceTask_HisHero_Text[17400]["Text20011"]
tNpcGossip[17400]["Text20012"] = tServiceTask_HisHero_Text[17400]["Text20012"]
tNpcGossip[17400]["Text20013"] = tServiceTask_HisHero_Text[17400]["Text20013"]
tNpcGossip[17400]["Text20014"] = tServiceTask_HisHero_Text[17400]["Text20014"]
tNpcGossip[17400]["tOption200-1"] = {209}
tNpcGossip[17400]["ChkFunc200-1"] = function ()
	return not User_IsCross()
end

tNpcGossip[17400]["Option201"] = tServiceTask_HisHero_Text[17400]["Option201"]
tNpcGossip[17400]["OptionFunc201"]="ServiceTask_HisHero_Accept</N>17400"
tNpcGossip[17400]["OptionChkFunc201"] = function ()
	return not Task_ChkTaskDetail(tServiceTask_HisHero_Count["TaskId"])
end

tNpcGossip[17400]["Option209"] = tServiceTask_HisHero_Text[17400]["Option209"]

-- 非本服玩家
tNpcGossip[17400]["Text200-2"] = {20021}
tNpcGossip[17400]["Text20021"] = tServiceTask_HisHero_Text[17400]["Text20021"]
tNpcGossip[17400]["tOption200-2"] = {211}
tNpcGossip[17400]["Option211"] = tServiceTask_HisHero_Text[17400]["Option211"]

-- 【玩家选接受任务、失败、玩家等级不足】
tNpcGossip[17400]["Text201-1"] = {20111,20112}
tNpcGossip[17400]["Text20111"] = tServiceTask_HisHero_Text[17400]["Text20111"]
tNpcGossip[17400]["Text20112"] = tServiceTask_HisHero_Text[17400]["Text20112"]
tNpcGossip[17400]["tOption101-1"] = {205}
tNpcGossip[17400]["Option205"] = tServiceTask_HisHero_Text[17400]["Option205"]

-- 【玩家选接受任务、失败、当日完成该任务为0】
tNpcGossip[17400]["Text202-1"] = {20211}
tNpcGossip[17400]["Text20211"] = tServiceTask_HisHero_Text[17400]["Text20211"]
tNpcGossip[17400]["tOption202-1"] = {205}

-- 【玩家选接受任务、成功、玩家接受任务】
tNpcGossip[17400]["Text203-1"] = {20311,20312}
tNpcGossip[17400]["Text20311"] = tServiceTask_HisHero_Text[17400]["Text20311"]
tNpcGossip[17400]["Text20312"] = tServiceTask_HisHero_Text[17400]["Text20312"]
tNpcGossip[17400]["tOption203-1"] = {206}
tNpcGossip[17400]["Option206"] = tServiceTask_HisHero_Text[17400]["Option206"]

-- NPC选项
tNpcGossip[17400]["Option200"] = tServiceTask_HisHero_Text[17400]["Option200"]
tNpcGossip[17400]["OptionPoint200"]="200"

-- 玩家死亡触发
-- tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
-- table.insert(tUserKilled["tFunction"],ServiceTask_HisHero_Kill)

-- 玩家锁魂
-- tKeepGhost["tFunction"] = tKeepGhost["tFunction"] or {}
-- table.insert(tKeepGhost["tFunction"],ServiceTask_HisHero_KeepGhost)

-- 玩家复活
-- tUserSave["tFunction"] = tUserSave["tFunction"] or {}
-- table.insert(tUserSave["tFunction"],ServiceTask_HisHero_SaveUser)

-- 玩家解锁
-- tClearKeepGhost["tFunction"] = tClearKeepGhost["tFunction"] or {}
-- table.insert(tClearKeepGhost["tFunction"],ServiceTask_HisHero_ClearKeepGhost)
