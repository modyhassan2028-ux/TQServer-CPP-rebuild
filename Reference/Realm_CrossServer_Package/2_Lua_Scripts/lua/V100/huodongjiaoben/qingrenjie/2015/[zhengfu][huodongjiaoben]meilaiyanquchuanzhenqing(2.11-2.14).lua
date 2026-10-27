----------------------------------------------------------------------------
--Name:		[征服][活动脚本]情人节活动（2.11-2.14）之眉来眼去传真情.lua
--Purpose:	情人节活动（2.11-2.14）之眉来眼去传真情
--Creator:	陈麟泉
--Created:	2014/11/05
----------------------------------------------------------------------------
-- npcid:10078-10079
-- itemtypeid：3001054-3001055
-- Stc： 	13122-13124
-- LogId：	10000455
-- taskId：	3349
----------------------------------------------------------------------------
--掩码说明：
----131 22：标识任务步骤
-----------= 0：未领取心法
-----------= 1：已领取心法 第一阶段
-----------= 2：第二阶段
-----------= 3：第三阶段
-----------= 4：修炼值达到满值（160）
-----------= 5：已领取节日通用礼包

----131 23：记录修炼值

----131 79：第四位标识是否已送素秋师妹玫瑰，第五位标识是否已送药师师兄玫瑰
-----------= 0：未送过
-----------= 1：已送过

-- 命名前缀
-- ValentinesDay2015_Flirt


----------------------------------------------------------------------------
--常量表
local tValentinesDay2015_Flirt_Constant = {}

----活动时间
tValentinesDay2015_Flirt_Constant["BeforeEventDate"] = "2015-01-01 00:00 2015-02-10 23:59"
tValentinesDay2015_Flirt_Constant["EventDate"] = "2015-02-11 00:00 2015-02-14 23:59"

----任务物品ID
tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"] = 3001054
tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"] = 3001055

----爱情玫瑰ID
tValentinesDay2015_Flirt_Constant["LoveRoseID"] = 3005410

----长梗玫瑰ID
tValentinesDay2015_Flirt_Constant["LongStemRoseID"] = 3005411

----LogId
tValentinesDay2015_Flirt_Constant["LogId"] = 10000455

----NpcID
tValentinesDay2015_Flirt_Constant["NpcId_Mal"] = 10079
tValentinesDay2015_Flirt_Constant["NpcId_Fem"] = 10078

----情人节活动总ID
tValentinesDay2015_Flirt_Constant["ValentinesDay2015_TaskID"] = 3353

----3个阶段所需修炼值
tValentinesDay2015_Flirt_Constant["ScoreRequired"] = {}
tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] = 9
tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] = 59
tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] = 159

--活动要求最低等级
tValentinesDay2015_Flirt_Constant["MinLevel"] = 80

--活动要求最低转世
tValentinesDay2015_Flirt_Constant["MinMeto"] = 0

--活动要求组队人数
tValentinesDay2015_Flirt_Constant["RequiredTeamNum"] = 2

--未送过玫瑰的掩码值
tValentinesDay2015_Flirt_Constant["HaveNotSent"] = 0

--寻路方法名
tValentinesDay2015_Flirt_Constant["FindWayFunc"] = "ValentinesDay2015_Flirt_FindWay"

--总NPC信息
tValentinesDay2015_Flirt_Constant["FatherPosX"] = 292
tValentinesDay2015_Flirt_Constant["FatherPosY"] = 369
tValentinesDay2015_Flirt_Constant["FatherMapId"] = 1002
tValentinesDay2015_Flirt_Constant["FatherNpcId"] = 17285

--寻路到总NPC方法
tValentinesDay2015_Flirt_Constant["GoToFather"] = "</F>ValentinesDay2015_Flirt_GoToFather"

--送长梗玫瑰给NPC光效
tValentinesDay2015_Flirt_Constant["MapEffect"] = "red-flower-charm2"

--送长梗玫瑰LOG
tValentinesDay2015_Flirt_Constant["LongStemRoseLog"] = "0,0,3005411,1,10002397,2,0,0"

--NPC坐标
tValentinesDay2015_Flirt_Constant["NpcInfo"] = {}
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"] = {}
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["Id"] = 10079
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellX"] = 287
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellY"] = 359
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["MapId"] = 1002

tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"] = {}
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["Id"] = 10078
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellX"] = 284
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellY"] = 359
tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["MapId"] = 1002

--检测日期返回值
local tValentinesDay2015_Flirt_DateValue = {}
tValentinesDay2015_Flirt_DateValue["BeforeEvent"] = 1
tValentinesDay2015_Flirt_DateValue["AtEvent"] = 2
tValentinesDay2015_Flirt_DateValue["AfterEvent"] = 3

--Log
local sValentinesDay2015_Flirt_LogConfig = "0,0,%s,%s,10000455,%s,%s,%s"

--掩码表
local tValentinesDay2015_Flirt_Stc = {}

tValentinesDay2015_Flirt_Stc["Phase"] = {}
tValentinesDay2015_Flirt_Stc["Phase"]["Event"] = 131
tValentinesDay2015_Flirt_Stc["Phase"]["Data"] = 22
tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] = 0
tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] = 1
tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] = 2
tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"] = 3
tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] = 4
tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] = 5

tValentinesDay2015_Flirt_Stc["Score"] = {}
tValentinesDay2015_Flirt_Stc["Score"]["Event"] = 131
tValentinesDay2015_Flirt_Stc["Score"]["Data"] = 23

tValentinesDay2015_Flirt_Stc["Rose"] = {}
tValentinesDay2015_Flirt_Stc["Rose"]["Event"] = 131
tValentinesDay2015_Flirt_Stc["Rose"]["Data"] = 79





----------------------------------------------------------------------------

--判断活动时间
function ValentinesDay2015_Flirt_ChkDate()
	if Sys_ChkFullTime(tValentinesDay2015_Flirt_Constant["BeforeEventDate"]) then
		return tValentinesDay2015_Flirt_DateValue["BeforeEvent"]
	elseif Sys_ChkFullTime(tValentinesDay2015_Flirt_Constant["EventDate"]) then
		return tValentinesDay2015_Flirt_DateValue["AtEvent"]
	else
		return tValentinesDay2015_Flirt_DateValue["AfterEvent"]
	end
end

--判断身上有没有心法
function ValentinesDay2015_Flirt_ChkQuestItem(nUserId)
	return Item_ChkMulItem(tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"],tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"],1,0,0,nUserId)
end

--判断是否为男性
function ValentinesDay2015_Flirt_IsMale(nUserId)
	if 1 == Get_UserSex(nUserId) then
		return true
	else
		return false
	end
end

--判断等级是满足0转80
function ValentinesDay2015_Flirt_ChkLevel(nUserId)
	if Get_UserMetempsychosis(nUserId) > tValentinesDay2015_Flirt_Constant["MinMeto"] then
		return true
	else
		if tValentinesDay2015_Flirt_Constant["MinLevel"] > Get_UserLevel(nUserId) then
			return false
		else
			return true
		end
	end
end

--判断组队是否为2个人
function ValentinesDay2015_Flirt_ChkTeamInfo(nUserId)
	if tValentinesDay2015_Flirt_Constant["RequiredTeamNum"] == Get_UserTeamNumbers(nUserId) then
		return true
	else
		return false
	end
end

--取任务步骤掩码
function ValentinesDay2015_Flirt_GetPhase(nUserId)
	if Task_ChkStatistic(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],nUserId) then
		return Get_UserStatisticValue(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],nUserId)
	else
		Task_SetStatistic(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],0,1,nUserId)
		return 0
	end
end

--置任务阶段掩码和打时间戳
function ValentinesDay2015_Flirt_SetPhase(nPhase,nUserId)
	Task_SetStatistic(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],nPhase,1,nUserId)
	if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == nPhase then
		Task_SetStcTimestamp(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],0,nUserId)
	end
end

--取修炼值掩码
function ValentinesDay2015_Flirt_GetScore(nUserId)
	if Task_ChkStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],nUserId) then
		return Get_UserStatisticValue(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],nUserId)
	else
		Task_SetStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],0,1,nUserId)
		return 0
	end
end

--修炼值+1
function ValentinesDay2015_Flirt_AddScore(nUserId)
	if Task_ChkStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],nUserId) then
		Task_AddStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],1,1,nUserId)
	else
		Task_SetStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],1,1,nUserId)
	end
end

--重置修炼值
function ValentinesDay2015_Flirt_ResetScore(nUserId)
	Task_SetStatistic(tValentinesDay2015_Flirt_Stc["Score"]["Event"],tValentinesDay2015_Flirt_Stc["Score"]["Data"],0,1,nUserId)
end

--打action_log
function ValentinesDay2015_Flirt_SaveLog(sDelID,sDelAmount,sType,sAwardId,sAwardAmount)
	local sText = string.format(sValentinesDay2015_Flirt_LogConfig,sDelID,sDelAmount,sType,sAwardId,sAwardAmount)
	Sys_SaveActionFestivalLog(sText)
end

--寻路到各自性别的任务NPC
function ValentinesDay2015_Flirt_FindWay(nUserId)
	if ValentinesDay2015_Flirt_IsMale(nUserId) then
		Sys_GotoSomeWhere(tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellX"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellY"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["MapId"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["Id"],nUserId)
	else
		Sys_GotoSomeWhere(tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellX"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellY"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["MapId"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["Id"],nUserId)
	end
end

--判断玩家性别是否和NPC性别一样
function ValentinesDay2015_Flirt_ChkSameSex()
	local nNpcId = Get_NpcId()
	local nUserId = Get_UserId()
	if tValentinesDay2015_Flirt_Constant["NpcId_Mal"] == nNpcId then
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			return true
		else
			return false
		end
	else
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			return false
		else
			return true
		end
	end
end

--领取&补领心法条件判断
function ValentinesDay2015_Flirt_ReceiveQuestItem()
	local nNpcId = Get_NpcId()
	local nUserId = Get_UserId()
	--判断活动时间
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] ~= ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_Npc()
		return
	end
	--判断等级
	if not ValentinesDay2015_Flirt_ChkLevel(nUserId) then
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["LevelNotEnough"],nUserId)
		return
	end
	--判断掩码
	local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
	if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
		if tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] ~= nPhase then
			--已接过任务
			if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then
				User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemExist"],nUserId)
			else
				ValentinesDay2015_Flirt_AddQuestItem(nUserId,nNpcId)
			end
		else
			--未接过任务
			ValentinesDay2015_Flirt_AddQuestItem(nUserId,nNpcId)
		end
	else
		--已领取奖励判断隔天
		if Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
			ValentinesDay2015_Flirt_AddQuestItem(nUserId,nNpcId)
		else
			User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["TaskFinished"],nUserId)
		end
	end
end

--置掩码并给玩家心法操作
----在做任务中不重置掩码
function ValentinesDay2015_Flirt_AddQuestItem(nUserId,nNpcId)
	--判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["BagFullItem"],nUserId)
		return
	end

	--判断性别分别给不同的心法，如果任务中不重置掩码
	if ValentinesDay2015_Flirt_IsMale(nUserId) then

		--男性
		if tValentinesDay2015_Flirt_Constant["NpcId_Fem"] == nNpcId then
			Sys_MsgBox(tValentinesDay2015_Flirt_NpcGossip[nNpcId]["SysMsg"]["WrongSex"])
		else
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
			if tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == nPhase then
				ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"],nUserId)
				ValentinesDay2015_Flirt_ResetScore(nUserId)
			end
			Item_AddItem(tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"])
			Sys_MsgBox(tValentinesDay2015_Flirt_NpcGossip[nNpcId]["SysMsg"]["ItemGet"])
			ValentinesDay2015_Flirt_SaveLog(0,0,"1[1]",tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"],1)
		end
	else

		--女性
		if tValentinesDay2015_Flirt_Constant["NpcId_Mal"] == nNpcId then
			Sys_MsgBox(tValentinesDay2015_Flirt_NpcGossip[nNpcId]["SysMsg"]["WrongSex"])
		else
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
			if tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == nPhase then
				ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"],nUserId)
				ValentinesDay2015_Flirt_ResetScore(nUserId)
			end
			Item_AddItem(tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"])
			Sys_MsgBox(tValentinesDay2015_Flirt_NpcGossip[nNpcId]["SysMsg"]["ItemGet"])
			ValentinesDay2015_Flirt_SaveLog(0,0,"1[1]",tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"],1)
		end
	end
end

--NPC对话封装
function ValentinesDay2015_Flirt_NpcTalking(nNpcId,sTopic)
	for i,v in pairs(tValentinesDay2015_Flirt_NpcGossip[nNpcId][sTopic]["TextNo"]) do
		local sText = "Text"..v
		Sys_DialogText(tValentinesDay2015_Flirt_NpcGossip[nNpcId][sTopic][sText])
	end
	for i,v in pairs(tValentinesDay2015_Flirt_NpcGossip[nNpcId][sTopic]["OptionNo"]) do
		local nPhase = ValentinesDay2015_Flirt_GetPhase(Get_UserId())
		if tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase and "AtEvent" == sTopic and 1 == v then
			--在做任务中，不显示"领取心法"选项
		else
			if (tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == nPhase or (not ValentinesDay2015_Flirt_ChkSameSex())) and "AtEvent" == sTopic and 2 == v then
				--不在做任务中，或者性别不对不显示"补领心法"选项
			else
				if "AtEvent" == sTopic and ValentinesDay2015_Flirt_IfLongStemRoseGivenOut(nNpcId) and 4 == v then
					--送过长柄玫瑰，不显示"送玫瑰"选项
				else
					local sOptionStr = "Option"..v
					local sOptionFunc = sOptionStr.."Func"
					Sys_DialogOption(tValentinesDay2015_Flirt_NpcGossip[nNpcId][sTopic][sOptionStr],tValentinesDay2015_Flirt_NpcGossip[nNpcId][sTopic][sOptionFunc])
				end
			end
		end
	end
	Sys_DialogFace()
	Sys_DialogEnd()
end

--接达到境界有何用
function ValentinesDay2015_Flirt_IntroduceReward()
	local nNpcId = Get_NpcId()
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"IntroduceReward")
	elseif tValentinesDay2015_Flirt_DateValue["AfterEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"AfterEvent")
	else
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"BeforeEvent")
	end
end

--接活动详情介绍
function ValentinesDay2015_Flirt_IntroduceEvent()
	local nNpcId = Get_NpcId()
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"IntroduceEvent")
	elseif tValentinesDay2015_Flirt_DateValue["AfterEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"AfterEvent")
	else
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"BeforeEvent")
	end
end

--NPC入口
function ValentinesDay2015_Flirt_Npc()
	local nNpcId = Get_NpcId()
	local nUserId = Get_UserId()

	if tValentinesDay2015_Flirt_DateValue["BeforeEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"BeforeEvent")
	elseif tValentinesDay2015_Flirt_DateValue["AfterEvent"] == ValentinesDay2015_Flirt_ChkDate() then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"AfterEvent")
	else
		--隔天掩码清零重置（只清已经领奖的玩家的掩码）
		if Task_ChkStatistic(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],nUserId) then
			if Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
					ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"],nUserId)
					ValentinesDay2015_Flirt_ResetScore(nUserId)
				end
			end
		end
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"AtEvent")
	end
end

--判断是否送过玫瑰
function ValentinesDay2015_Flirt_IfLongStemRoseGivenOut(nNpcId)
	local nUserId = Get_UserId()
	local nStcValue = Get_UserStatisticValue(tValentinesDay2015_Flirt_Stc["Rose"]["Event"],tValentinesDay2015_Flirt_Stc["Rose"]["Data"],nUserId)
	if tValentinesDay2015_Flirt_Constant["NpcId_Mal"] == nNpcId then
		nStcValue = math.modf(nStcValue/1000)%10
		if tValentinesDay2015_Flirt_Constant["HaveNotSent"] == nStcValue then
			return false
		end
	else
		nStcValue = math.modf(nStcValue/10000)%10
		if tValentinesDay2015_Flirt_Constant["HaveNotSent"] == nStcValue then
			return false
		end
	end
	return true
end

--送玫瑰
function ValentinesDay2015_Flirt_GiveLongStemRose()
	local nNpcId = Get_NpcId()
	local nUserId = Get_UserId()
	
	--检测是身上有没有长梗玫瑰
	if not Item_ChkItem(tValentinesDay2015_Flirt_Constant["LongStemRoseID"]) then
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"LongStemRoseNotFound")
		return
	end

	--根据NPC的性别 不同判断掩码
	if tValentinesDay2015_Flirt_Constant["NpcId_Mal"] == nNpcId then
		Task_AddStatistic(tValentinesDay2015_Flirt_Stc["Rose"]["Event"],tValentinesDay2015_Flirt_Stc["Rose"]["Data"],1000,1,nUserId)
		Item_DelItem(tValentinesDay2015_Flirt_Constant["LongStemRoseID"])
		Map_Effect(tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["MapId"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellX"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Male"]["CellY"],tValentinesDay2015_Flirt_Constant["MapEffect"])
		Sys_SaveActionFestivalLog(tValentinesDay2015_Flirt_Constant["LongStemRoseLog"])
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"GiveLongStemRose")
	else
		Task_AddStatistic(tValentinesDay2015_Flirt_Stc["Rose"]["Event"],tValentinesDay2015_Flirt_Stc["Rose"]["Data"],10000,1,nUserId)
		Item_DelItem(tValentinesDay2015_Flirt_Constant["LongStemRoseID"])
		Map_Effect(tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["MapId"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellX"],tValentinesDay2015_Flirt_Constant["NpcInfo"]["Female"]["CellY"],tValentinesDay2015_Flirt_Constant["MapEffect"])
		Sys_SaveActionFestivalLog(tValentinesDay2015_Flirt_Constant["LongStemRoseLog"])
		ValentinesDay2015_Flirt_NpcTalking(nNpcId,"GiveLongStemRose")
	end
	
	--判断是否送完6个玫瑰
	local nStcValue = Get_UserStatisticValue(tValentinesDay2015_Flirt_Stc["Rose"]["Event"],tValentinesDay2015_Flirt_Stc["Rose"]["Data"],nUserId)
	if 111111 == nStcValue then
		Sys_MsgBox(tValentinesDay2015_Priest_Text["Flower_Finish"],tValentinesDay2015_Flirt_Constant["GoToFather"])
	end
end

--寻路到总NPC
function ValentinesDay2015_Flirt_GoToFather()
	local nUserId = Get_UserId()
	Sys_GotoSomeWhere(tValentinesDay2015_Flirt_Constant["FatherPosX"],tValentinesDay2015_Flirt_Constant["FatherPosY"],tValentinesDay2015_Flirt_Constant["FatherMapId"],tValentinesDay2015_Flirt_Constant["FatherNpcId"],nUserId)
end

--怪物入口
function ValentinesDay2015_Flirt_Monster()
	--时间判断
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] ~= ValentinesDay2015_Flirt_ChkDate() then
		return
	end

	--判断任务掩码
	local nUserId = Get_UserId()
	local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
	
	-- 判断身上是否有接任务
	if nPhase <= tValentinesDay2015_Flirt_Stc["Phase"]["TaskNotAccept"] then
		return
	end
	
	if not tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase or not tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase or not tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"] == nPhase then
		return
	end

	--任务道具判断
	if not ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then
		--判断已领取奖励让完成任务的玩家也可以和未完成的一起做（1.7修改）
		if not tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
			if Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				if ValentinesDay2015_Flirt_IsMale(nUserId) then
					User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"],nUserId)
				else
					User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"],nUserId)
				end
				return
			end
		end
	end

	--队伍人数判断
	if not ValentinesDay2015_Flirt_ChkTeamInfo(nUserId) then
		local nTeamNum = Get_UserTeamNumbers(nUserId)
		if tValentinesDay2015_Flirt_Constant["RequiredTeamNum"] < nTeamNum then
			User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["WrongTeam"],nUserId)
		else
			ValentinesDay2015_Flirt_AddStcSingle()
		end
		return
	end

	--不同性别分别执行第一次全队触发
	if ValentinesDay2015_Flirt_IsMale(nUserId) then
		User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_FemAddStcFirst",nUserId)
	else
		User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_MalAddStcFirst",nUserId)
	end
end

--单人加修炼值
function ValentinesDay2015_Flirt_AddStcSingle()
	local nUserId = Get_UserId()
	if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then

		local nScore = ValentinesDay2015_Flirt_GetScore(nUserId)
		local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)

		--判断活动中，判断任务阶段；掩码操作，特效操作
		if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
			ValentinesDay2015_Flirt_AddScore(nUserId)
			if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase then
				if tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] <= nScore then
					ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"],nUserId)
					User_EffectAdd("self","tread_acc",nUserId)
				else
					User_EffectAdd("self","Intone2_1",nUserId)
				end
			elseif tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase then
				if tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] <= nScore then
					ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"],nUserId)
					User_EffectAdd("self","tread_acc",nUserId)
				else
					User_EffectAdd("self","red-flower-g-1",nUserId)
				end
			else
				if tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] <= nScore then
					ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Complete"],nUserId)
					User_EffectAdd("self","changefig",nUserId)
					Sys_MsgBox(tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"])
					ValentinesDay2015_Flirt_SaveLog(0,0,"1[4]",0,0)
				else
					User_EffectAdd("self","red-flower-r-1",nUserId)
				end
			end
		end

	else
		if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] <= ValentinesDay2015_Flirt_GetPhase(nUserId) then
			return
		end
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"],nUserId)
		else
			User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"],nUserId)
		end
	end
end

--加修炼值第一次全队触发（全队执行Lua时由男性触发,女性加掩码）
function ValentinesDay2015_Flirt_FemAddStcFirst()
	local nUserId = Get_UserId()
	if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then

		--判断是否是女性
		if not ValentinesDay2015_Flirt_IsMale(nUserId) then
			local nScore = ValentinesDay2015_Flirt_GetScore(nUserId)
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)

			--判断活动中，判断任务阶段；掩码操作，特效操作
			if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
				ValentinesDay2015_Flirt_AddScore(nUserId)
				if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","Intone2_1",nUserId)
					end
				elseif tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","red-flower-g-1",nUserId)
					end
				else
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Complete"],nUserId)
						User_EffectAdd("self","changefig",nUserId)
						Sys_MsgBox(tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"])
						ValentinesDay2015_Flirt_SaveLog(0,0,"1[4]",0,0)
					else
						User_EffectAdd("self","red-flower-r-1",nUserId)
					end
				end
			end

			--第二次触发给队友加修炼值
			User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_MalAddStcSecond",nUserId)
		end
	else
		--判断已领取奖励让完成任务的玩家也可以和未完成的一起做（1.7修改）
		if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
			if not Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_MalAddStcSecond",nUserId)
				return
			end
		end
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"],nUserId)
	end
end

--加修炼值第一次全队触发（全队执行Lua时由女性触发，男性加掩码）
function ValentinesDay2015_Flirt_MalAddStcFirst()
	local nUserId = Get_UserId()
	if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then

		--判断是否是男性
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			local nScore = ValentinesDay2015_Flirt_GetScore(nUserId)
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)

			--判断活动中，判断任务阶段；掩码操作，特效操作
			if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
				ValentinesDay2015_Flirt_AddScore(nUserId)
				if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","Intone2_1",nUserId)
					end
				elseif tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","red-flower-g-1",nUserId)
					end
				else
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Complete"],nUserId)
						User_EffectAdd("self","changefig",nUserId)
						Sys_MsgBox(tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"])
						ValentinesDay2015_Flirt_SaveLog(0,0,"1[4]",0,0)
					else
						User_EffectAdd("self","red-flower-r-1",nUserId)
					end
				end
			end

			--第二次触发给队友加修炼值
			User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_FemAddStcSecond",nUserId)
		end
	else
		--判断已领取奖励让完成任务的玩家也可以和未完成的一起做（1.7修改）
		if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
			if not Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				User_TeamExeFuncByTeamer(1,"ValentinesDay2015_Flirt_FemAddStcSecond",nUserId)
				return
			end
		end
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"],nUserId)
	end
end

--加修炼值第二次全队触发（全队执行Lua时由男性触发，女性加掩码）
function ValentinesDay2015_Flirt_FemAddStcSecond()
	local nUserId = Get_UserId()
	if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then

		--判断是否是女性
		if not ValentinesDay2015_Flirt_IsMale(nUserId) then
			local nScore = ValentinesDay2015_Flirt_GetScore(nUserId)
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
			if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
				ValentinesDay2015_Flirt_AddScore(nUserId)
				if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","Intone2_1",nUserId)
					end
				elseif tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","red-flower-g-1",nUserId)
					end
				else
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Complete"],nUserId)
						User_EffectAdd("self","changefig",nUserId)
						Sys_MsgBox(tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"])
						ValentinesDay2015_Flirt_SaveLog(0,0,"1[4]",0,0)
					else
						User_EffectAdd("self","red-flower-r-1",nUserId)
					end
				end
			end
		end
	else
		if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
			if not Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				return
			end
		end
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"],nUserId)
	end
end

--加修炼值第二次全队触发（全队执行Lua时由女性触发，男性加掩码）
function ValentinesDay2015_Flirt_MalAddStcSecond()
	local nUserId = Get_UserId()
	if ValentinesDay2015_Flirt_ChkQuestItem(nUserId) then

		--判断是否是男性
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			local nScore = ValentinesDay2015_Flirt_GetScore(nUserId)
			local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
			if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] ~= nPhase and tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] ~= nPhase then
				ValentinesDay2015_Flirt_AddScore(nUserId)
				if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][1] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","Intone2_1",nUserId)
					end
				elseif tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase then
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][2] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"],nUserId)
						User_EffectAdd("self","tread_acc",nUserId)
						ValentinesDay2015_Flirt_ExpAwards()
					else
						User_EffectAdd("self","red-flower-g-1",nUserId)
					end
				else
					if tValentinesDay2015_Flirt_Constant["ScoreRequired"][3] <= nScore then
						ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["Complete"],nUserId)
						User_EffectAdd("self","changefig",nUserId)
						Sys_MsgBox(tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"])
						ValentinesDay2015_Flirt_SaveLog(0,0,"1[4]",0,0)
					else
						User_EffectAdd("self","red-flower-r-1",nUserId)
					end
				end
			end
		end
	else
		if tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then
			if not Task_StcInterval(tValentinesDay2015_Flirt_Stc["Phase"]["Event"],tValentinesDay2015_Flirt_Stc["Phase"]["Data"],1,4) then
				return
			end
		end
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"],nUserId)
	end
end

--给1,2阶段经验奖励
function ValentinesDay2015_Flirt_ExpAwards()
	local nUserId = Get_UserId()
	local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId) - 1
	if 140 ~= Get_UserLevel(nUserId) then
		User_AddExp(User_CalcTimeToExp(tValentinesDay2015_Flirt_Reward[nPhase]["Amount"],nUserId),nUserId)
		User_TalkChannel2005(tValentinesDay2015_Flirt_Reward[nPhase]["SysMsg1"],nUserId)
		ValentinesDay2015_Flirt_SaveLog(0,0,"1["..(nPhase + 1).."]",4,tValentinesDay2015_Flirt_Reward[nPhase]["Amount"]/10)
	else
		local nAmount = tValentinesDay2015_Flirt_Reward[nPhase]["Amount"]/20
		User_AddCultivation(nAmount,nUserId)
		User_TalkChannel2005(tValentinesDay2015_Flirt_Reward[nPhase]["SysMsg2"],nUserId)
		ValentinesDay2015_Flirt_SaveLog(0,0,"1["..(nPhase + 1).."]",6,nAmount)
	end
end

--获得3阶段节日礼包和爱情玫瑰奖励
function ValentinesDay2015_Flirt_ItemAwards(nUserId)
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] == ValentinesDay2015_Flirt_ChkDate() and tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] == ValentinesDay2015_Flirt_GetPhase(nUserId) then

		--先删除物品，如果删除失败则返回并提示
		if not Item_DelMulItem(tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"],tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"],1,0,0,nUserId) then
			if ValentinesDay2015_Flirt_IsMale(nUserId) then
				User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"],nUserId)
			else
				User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"],nUserId)
			end
			return
		end

		--判断背包空间
		if not User_CheckLeftSpace(1) then
			User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["BagFullReward"],nUserId)
			return
		end

		--置掩码，给奖励 给提示
		ValentinesDay2015_Flirt_SetPhase(tValentinesDay2015_Flirt_Stc["Phase"]["RewardGet"],nUserId)
		FestivalGeneralPackage_GetGift(tValentinesDay2015_Flirt_Constant["ValentinesDay2015_TaskID"],tValentinesDay2015_Flirt_Constant["LogId"])
		Item_AddItem(tValentinesDay2015_Flirt_Constant["LoveRoseID"])
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["RewardGet"],nUserId)
		
		--区分物品打LOG
		if ValentinesDay2015_Flirt_IsMale(nUserId) then
			ValentinesDay2015_Flirt_SaveLog(tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"],1,"2",tValentinesDay2015_Flirt_Constant["LoveRoseID"],"1")
		else
			ValentinesDay2015_Flirt_SaveLog(tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"],1,"2",tValentinesDay2015_Flirt_Constant["LoveRoseID"],"1")
		end
	end
end

--物品入口
function ValentinesDay2015_Flirt_Item()
	local nUserId = Get_UserId()
	if tValentinesDay2015_Flirt_DateValue["AtEvent"] == ValentinesDay2015_Flirt_ChkDate() then

		local nPhase = ValentinesDay2015_Flirt_GetPhase(nUserId)
		local sText = ""

		--前3个阶段给的对白
		if tValentinesDay2015_Flirt_Stc["Phase"]["ItemGet"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["Phase2"] == nPhase or tValentinesDay2015_Flirt_Stc["Phase"]["Phase3"] == nPhase then
			sText = string.format(tValentinesDay2015_Flirt_ItemDialog[nPhase]["Text"],ValentinesDay2015_Flirt_GetScore(nUserId))
			Sys_DialogText(sText)
			Sys_DialogOption(tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option1"],tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option1Func"])
			-- Sys_DialogFace()
			Sys_DialogEnd()
		else

			--打满修炼值给的对白
			sText = string.format(tValentinesDay2015_Flirt_ItemDialog[nPhase]["Text"],ValentinesDay2015_Flirt_GetScore(nUserId))
			Sys_DialogText(sText)
			if tValentinesDay2015_Flirt_Stc["Phase"]["Complete"] == nPhase then
				Sys_DialogOption(tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option1"],tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option1Func"])
			end
			Sys_DialogOption(tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option2"],tValentinesDay2015_Flirt_ItemDialog[nPhase]["Option2Func"])
			-- Sys_DialogFace()
			Sys_DialogEnd()
		end
	else
		--物品过期删除
		Item_DelMulItem(tValentinesDay2015_Flirt_Constant["QuestItemID_Mal"],tValentinesDay2015_Flirt_Constant["QuestItemID_Fem"],1,0,0,nUserId)
		User_TalkChannel2005(tValentinesDay2015_Flirt_SysMsgContent["ItemExpired"],nUserId)
	end
end
-----------------------------------------------------------------------------------------
--NPCface
tNpcFace[3304] = 3
tNpcFace[3305] = 74

--素秋师妹
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["TextNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["OptionNo"] = {1, 2, 3, 4, 5}
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_ReceiveQuestItem"
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option2Func"] = "</F>ValentinesDay2015_Flirt_ReceiveQuestItem"
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option3Func"] = "</F>ValentinesDay2015_Flirt_IntroduceEvent"
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option4Func"] = "</F>ValentinesDay2015_Flirt_GiveLongStemRose"
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option5Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["TextNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["OptionNo"] = {1, 2, 3}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_IntroduceReward"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option2Func"] = "</F>ValentinesDay2015_Flirt_Npc"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option3Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["TextNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["OptionNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_Npc"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Option2Func"] = "</F>NULL"


tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"]["Text1"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"]["Option1"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tValentinesDay2015_Flirt_NpcGossip[10078]["LongStemRoseNotFound"]["Option1Func"] = "</F>NULL"


--药师师兄
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["OptionNo"] = {1, 2, 3, 4, 5}
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_ReceiveQuestItem"
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option2Func"] = "</F>ValentinesDay2015_Flirt_ReceiveQuestItem"
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option3Func"] = "</F>ValentinesDay2015_Flirt_IntroduceEvent"
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option4Func"] = "</F>ValentinesDay2015_Flirt_GiveLongStemRose"
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option5Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["TextNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["OptionNo"] = {1, 2, 3}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_IntroduceReward"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option2Func"] = "</F>ValentinesDay2015_Flirt_Npc"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option3Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["TextNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["OptionNo"] = {1, 2}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Option1Func"] = "</F>ValentinesDay2015_Flirt_Npc"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Option2Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"]["TextNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"]["Text1"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"]["OptionNo"] = {1}
tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"]["Option1"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tValentinesDay2015_Flirt_NpcGossip[10079]["LongStemRoseNotFound"]["Option1Func"] = "</F>NULL"


--心法
tValentinesDay2015_Flirt_ItemDialog[1]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_ItemDialog[2]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_ItemDialog[3]["Option1Func"] = "</F>NULL"

tValentinesDay2015_Flirt_ItemDialog[4]["Option1Func"] = "</F>ValentinesDay2015_Flirt_ItemAwards"
tValentinesDay2015_Flirt_ItemDialog[4]["Option2Func"] = "</F>NULL"


--奖励表
tValentinesDay2015_Flirt_Reward[1]["Type"] = "exp"
tValentinesDay2015_Flirt_Reward[1]["Amount"] = 200

tValentinesDay2015_Flirt_Reward[2]["Type"] = "exp"
tValentinesDay2015_Flirt_Reward[2]["Amount"] = 400
--------------------------------------怪物掉落-------------------------------------------
-- 第一片区
-- 	1	叫天鸡	9593200
tMonster[1] = tMonster[1] or {}
tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
table.insert(tMonster[1]["tFunction"],ValentinesDay2015_Flirt_Monster)

-- 	2	斑鸠王	9593210
tMonster[2] = tMonster[2] or {}
tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
table.insert(tMonster[2]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	3	罗罗鸟	9593220
tMonster[3] = tMonster[3] or {}
tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
table.insert(tMonster[3]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	4	幽冥鬼斧王	9593230
tMonster[4] = tMonster[4] or {}
tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
table.insert(tMonster[4]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	5	蹑空鬼斧王	9593240
tMonster[5] = tMonster[5] or {}
tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
table.insert(tMonster[5]["tFunction"],ValentinesDay2015_Flirt_Monster)


-- 第二片区
--	6	翼蛇	9593250
tMonster[6] = tMonster[6] or {}
tMonster[6]["tFunction"] = tMonster[6]["tFunction"] or {}
table.insert(tMonster[6]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	7	土匪	9593260
tMonster[7] = tMonster[7] or {}
tMonster[7]["tFunction"] = tMonster[7]["tFunction"] or {}
table.insert(tMonster[7]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	8	火鼠	9593270
tMonster[8] = tMonster[8] or {}
tMonster[8]["tFunction"] = tMonster[8]["tFunction"] or {}
table.insert(tMonster[8]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	9	火精灵	9593280
tMonster[9] = tMonster[9] or {}
tMonster[9]["tFunction"] = tMonster[9]["tFunction"] or {}
table.insert(tMonster[9]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	66	精悍土匪	9593290
tMonster[66] = tMonster[66] or {}
tMonster[66]["tFunction"] = tMonster[66]["tFunction"] or {}
table.insert(tMonster[66]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	67	尖牙火鼠	9593300
tMonster[67] = tMonster[67] or {}
tMonster[67]["tFunction"] = tMonster[67]["tFunction"] or {}
table.insert(tMonster[67]["tFunction"],ValentinesDay2015_Flirt_Monster)


-- 第三片区
--	10	须猕猴	9593310
tMonster[10] = tMonster[10] or {}
tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
table.insert(tMonster[10]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	11	巨臂猿	9593320
tMonster[11] = tMonster[11] or {}
tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
table.insert(tMonster[11]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	12	天雷巨猿	9593330
tMonster[12] = tMonster[12] or {}
tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
table.insert(tMonster[12]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	13	蛇人	9593340
tMonster[13] = tMonster[13] or {}
tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
table.insert(tMonster[13]["tFunction"],ValentinesDay2015_Flirt_Monster)


-- 第四片区
--	14	沙怪	9593350
tMonster[14] = tMonster[14] or {}
tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
table.insert(tMonster[14]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	15	锤山怪	9593360
tMonster[15] = tMonster[15] or {}
tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
table.insert(tMonster[15]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	16	巨石怪	9593370
tMonster[16] = tMonster[16] or {}
tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
table.insert(tMonster[16]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	17	鬼刃	9593380
tMonster[17] = tMonster[17] or {}
tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
table.insert(tMonster[17]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	73	砾沙怪	9593390
tMonster[73] = tMonster[73] or {}
tMonster[73]["tFunction"] = tMonster[73]["tFunction"] or {}
table.insert(tMonster[73]["tFunction"],ValentinesDay2015_Flirt_Monster)


-- 第五片区
--	18	金臂鸟人	4081200
tMonster[18] = tMonster[18] or {}
tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
table.insert(tMonster[18]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	19	银羽鹰王	4081254
tMonster[19] = tMonster[19] or {}
tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
table.insert(tMonster[19]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	55	湖岛强匪	4081258
tMonster[55] = tMonster[55] or {}
tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
table.insert(tMonster[55]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	78	银羽鹰魔	4081255
tMonster[78] = tMonster[78] or {}
tMonster[78]["tFunction"] = tMonster[78]["tFunction"] or {}
table.insert(tMonster[78]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	79	湖岛悍匪	4081259
tMonster[79] = tMonster[79] or {}
tMonster[79]["tFunction"] = tMonster[79]["tFunction"] or {}
table.insert(tMonster[79]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	84	匪兵	9593450
tMonster[84] = tMonster[84] or {}
tMonster[84]["tFunction"] = tMonster[84]["tFunction"] or {}
table.insert(tMonster[84]["tFunction"],ValentinesDay2015_Flirt_Monster)

-- 第六片区
--	20	土墓蝠	9593460
tMonster[20] = tMonster[20] or {}
tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
table.insert(tMonster[20]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	56	嗜血蝙蝠	9593470
tMonster[56] = tMonster[56] or {}
tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
table.insert(tMonster[56]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	57	牛怪	9593480
tMonster[57] = tMonster[57] or {}
tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
table.insert(tMonster[57]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	58	血影红魔	9593490
tMonster[58] = tMonster[58] or {}
tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
table.insert(tMonster[58]["tFunction"],ValentinesDay2015_Flirt_Monster)



-- 第七片区
--	2411	冰凌腾蛇	9979200
tMonster[2411] = tMonster[2411] or {}
tMonster[2411]["tFunction"] = tMonster[2411]["tFunction"] or {}
table.insert(tMonster[2411]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	2416	冰煞邪刀	9979210
tMonster[2416] = tMonster[2416] or {}
tMonster[2416]["tFunction"] = tMonster[2416]["tFunction"] or {}
table.insert(tMonster[2416]["tFunction"],ValentinesDay2015_Flirt_Monster)



-- 第八片区
--	2686	深海亡魂	98054381
tMonster[2686] = tMonster[2686] or {}
tMonster[2686]["tFunction"] = tMonster[2686]["tFunction"] or {}
table.insert(tMonster[2686]["tFunction"],ValentinesDay2015_Flirt_Monster)

--	2687	深海魔魂	98054382
tMonster[2687] = tMonster[2687] or {}
tMonster[2687]["tFunction"] = tMonster[2687]["tFunction"] or {}
table.insert(tMonster[2687]["tFunction"],ValentinesDay2015_Flirt_Monster)
