-----------------------------------------------------------------------------------------------------
--Name:			[英文征服][活动脚本]劳工节活动之劳工大找茬(9.7-9.13)
--Purpose:		英文征服劳工节活动之劳工大找茬
--Creator: 		许乐
--Created:		2015/05/06
------------------------------------------------------------------------------------------------------
-- 命名前缀
-- LabourDay2015_FindMistake_

-- 掩码说明          
--stc(76,7)--stc(76,12):
-- stc(76,7)	当天完成1次此任务
-- stc(76,8)	每次找到正确NPC时的记录掩码，找到20个代表全部完成此任务
-- stc(76,9)  	是否有获得此任务
-- stc(76,10)	玩家是否领取过礼包
-- stc(76,11)	记录20个不同的npc是否被找到过的掩码
-- stc(76,12)  记录惩罚玩家10s的时间

-- logID:10000240
--FestivalId: 3436
--FestivalGeneralPackage stc：13485

-----------------------------------------常量表配置-----------------------------------------------
local tLabourDay2015_FindMistake_Cont = {}
	--活动时间
	tLabourDay2015_FindMistake_Cont["ActivityTime"] = "2015-09-07 00:00 2015-09-13 23:59"
	tLabourDay2015_FindMistake_Cont["BeforeActivityTime"] = "2014-09-01 00:00 2015-09-06 23:59"
	tLabourDay2015_FindMistake_Cont["AfterActivityTime"] = "2015-09-14 00:00 2020-09-06 23:59"
	
	--玩家等级要求
	tLabourDay2015_FindMistake_Cont["Metempsychosis"] = 0
	tLabourDay2015_FindMistake_Cont["Level"] = 80
	tLabourDay2015_FindMistake_Cont["LevTop"] = 140
	
	--奖励经验
	tLabourDay2015_FindMistake_Cont["exp"] = 15
	--惩罚HP
	tLabourDay2015_FindMistake_Cont["addlife1"] = -15
	tLabourDay2015_FindMistake_Cont["addlife2"] = -30
	--时间限制
	tLabourDay2015_FindMistake_Cont["CompleteTime"] = 300
	tLabourDay2015_FindMistake_Cont["PunishTime"] = 10
	
	--NPC坐标
	--8047 青龙校尉·萧勇对白
	tLabourDay2015_FindMistake_Cont[8047] = {}
	tLabourDay2015_FindMistake_Cont[8047]["CellX"] = 292
	tLabourDay2015_FindMistake_Cont[8047]["CellY"] = 385
	tLabourDay2015_FindMistake_Cont[8047]["Mapid"] = 1002

	--8048  白虎校尉·奉武对白
	tLabourDay2015_FindMistake_Cont[8048] = {}
	tLabourDay2015_FindMistake_Cont[8048]["CellX"] = 160
	tLabourDay2015_FindMistake_Cont[8048]["CellY"] = 217
	tLabourDay2015_FindMistake_Cont[8048]["Mapid"] = 2084
	
	tLabourDay2015_FindMistake_Cont["BoundCX"] = 3
	tLabourDay2015_FindMistake_Cont["BoundCY"] = 3

--掩码
local tLabourDay2015_FindMistake_Stc = {}
	-- 当天只可以完成1次此任务
	tLabourDay2015_FindMistake_Stc[1]={}
	tLabourDay2015_FindMistake_Stc[1]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[1]["DataType"] = 7
	tLabourDay2015_FindMistake_Stc[1]["Complete"] = 1
	
	--每次找到正确NPC时的记录掩码，找到20个代表全部完成此任务
	tLabourDay2015_FindMistake_Stc[2]={}
	tLabourDay2015_FindMistake_Stc[2]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[2]["DataType"] = 8
	tLabourDay2015_FindMistake_Stc[2]["Complete"] = 20
	
	--是否获得任务
	tLabourDay2015_FindMistake_Stc[3]={}
	tLabourDay2015_FindMistake_Stc[3]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[3]["DataType"] = 9
	tLabourDay2015_FindMistake_Stc[3]["Complete"] = 1
	
	--玩家是否领取过礼包
	tLabourDay2015_FindMistake_Stc[4]={}
	tLabourDay2015_FindMistake_Stc[4]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[4]["DataType"] = 10
	tLabourDay2015_FindMistake_Stc[4]["Complete"] = 1
	
	-- stc(76,11) 记录20个不同的npc是否被找到过的掩码
	tLabourDay2015_FindMistake_Num = {}
	tLabourDay2015_FindMistake_Num[8049] = 1
	tLabourDay2015_FindMistake_Num[8054] = 2
	tLabourDay2015_FindMistake_Num[8059] = 4
	tLabourDay2015_FindMistake_Num[8064] = 8
	tLabourDay2015_FindMistake_Num[8069] = 16
	tLabourDay2015_FindMistake_Num[8074] = 32
	tLabourDay2015_FindMistake_Num[8079] = 64
	tLabourDay2015_FindMistake_Num[8084] = 128
	tLabourDay2015_FindMistake_Num[8089] = 256
	tLabourDay2015_FindMistake_Num[8094] = 512
	tLabourDay2015_FindMistake_Num[8099] = 1024
	tLabourDay2015_FindMistake_Num[8104] = 2^11
	tLabourDay2015_FindMistake_Num[8109] = 2^12
	tLabourDay2015_FindMistake_Num[8114] = 2^13
	tLabourDay2015_FindMistake_Num[8119] = 2^14
	tLabourDay2015_FindMistake_Num[8124] = 2^15
	tLabourDay2015_FindMistake_Num[8129] = 2^16
	tLabourDay2015_FindMistake_Num[8134] = 2^17
	tLabourDay2015_FindMistake_Num[8139] = 2^18
	tLabourDay2015_FindMistake_Num[8144] = 2^19
	
	tLabourDay2015_FindMistake_Stc[5] = {}
	tLabourDay2015_FindMistake_Stc[5]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[5]["DataType"] = 11
	
	tLabourDay2015_FindMistake_Stc[6] = {}
	tLabourDay2015_FindMistake_Stc[6]["EventType"] = 76
	tLabourDay2015_FindMistake_Stc[6]["DataType"] = 12
	tLabourDay2015_FindMistake_Stc[6]["Complete"] = 1
	
	--奖励物品
	tLabourDay2015_FindMistake_Item = {}
	tLabourDay2015_FindMistake_Item["RewardSpace"] = 1
	
--logid: 10000240
local tLabourDay2015_FindMistake_Log = {}
	tLabourDay2015_FindMistake_Log["GetTaskLog"] = "0,0,0,0,10000240,1,0,0"
	tLabourDay2015_FindMistake_Log["FestivalId"] = 3436
	tLabourDay2015_FindMistake_Log["LogId"] = 10000240

local tLabourDay2015_FindMistake_Map = {}
	tLabourDay2015_FindMistake_Map["X"] = {}
	tLabourDay2015_FindMistake_Map["X"][1] =  155
	tLabourDay2015_FindMistake_Map["X"][2] =  80
	tLabourDay2015_FindMistake_Map["X"][3] =  197
	tLabourDay2015_FindMistake_Map["X"][4] =  100
	
	tLabourDay2015_FindMistake_Map["Y"] = {}
	tLabourDay2015_FindMistake_Map["Y"][1] =  90
	tLabourDay2015_FindMistake_Map["Y"][2] =  176
	tLabourDay2015_FindMistake_Map["Y"][3] =  150
	tLabourDay2015_FindMistake_Map["Y"][4] =  245

------------------------------------------------逻辑部分-------------------------------------------------
-- 判断活动时间
function LabourDay2015_FindMistake_TimeJudgement()
	if not Sys_ChkFullTime(tLabourDay2015_FindMistake_Cont["ActivityTime"]) then
		return false
	else
		return true
	end
end

--统一判断掩码
-- stc(76,7)	当天完成1次此任务 nStcNum=1
-- stc(76,8)	每次找到正确NPC时的记录掩码，找到20个代表全部完成此任务 nStcNum=2
-- stc(76,9)  	是否有获得此任务 nStcNum=3
-- stc(76,10)	玩家是否领取过礼包 nStcNum=4
function LabourDay2015_FindMistake_ChkStcComplete(nStcNum)
	local nEvent = tLabourDay2015_FindMistake_Stc[nStcNum]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[nStcNum]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[nStcNum]["Complete"]

	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)	
			return false
		else
			return true
		end
	else
		return false
	end
end

--判断领取奖励的条件（判断活动时间，判断是否完成此任务 stc(76,8) >= 20，判断玩家是否领取过奖励，判断背包空间）
function LabourDay2015_FindMistake_GetReward(nNpcId)
	-- 判断活动时间
	if not LabourDay2015_FindMistake_TimeJudgement() then
		--不在活动时间，活动后
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--判断是否完成此任务 stc(76,8) >= 20
	if not LabourDay2015_FindMistake_ChkStcComplete(2) then 
		--不满20个
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	-- 判断玩家是否领取过奖励
	if LabourDay2015_FindMistake_ChkStcComplete(4) then
		--领取过
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(tLabourDay2015_FindMistake_Item["RewardSpace"]) then
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["NoBagSpace"])
		return
	end
	
	-- 获得礼包掩码设值
	local nEvent = tLabourDay2015_FindMistake_Stc[4]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[4]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[4]["Complete"]
	Task_SetStatistic(nEvent,nType,nComplete,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	--领取奖励
	FestivalGeneralPackage_GetGift(tLabourDay2015_FindMistake_Log["FestivalId"],tLabourDay2015_FindMistake_Log["LogId"])
	User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["GetReward"])
end

--详细信息
function LabourDay2015_FindMistake_KnowDetails(nNpcId)
	LinkNpcGossipFunc_New(nNpcId,"4-1")
end

--进入西校场
function LabourDay2015_FindMistake_SendInMap(nNpcId)
	-- 判断活动时间
	if not LabourDay2015_FindMistake_TimeJudgement() then
		--不在活动时间，活动后
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断玩家等级
	local nLevel = tLabourDay2015_FindMistake_Cont["Level"]
	local nMete = tLabourDay2015_FindMistake_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	end
	
	-- 判断当前是否完成过此任务 ==1 
	if LabourDay2015_FindMistake_ChkStcComplete(1) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return 
	end
	
	if Task_StcInterval(tLabourDay2015_FindMistake_Stc[5]["EventType"],tLabourDay2015_FindMistake_Stc[5]["DataType"],1,4) then
		Task_SetStatistic(tLabourDay2015_FindMistake_Stc[5]["EventType"],tLabourDay2015_FindMistake_Stc[5]["DataType"],0,1,0)
		Task_SetStcTimestamp(tLabourDay2015_FindMistake_Stc[5]["EventType"],tLabourDay2015_FindMistake_Stc[5]["DataType"],0,0)
	end
	
	--如果5分钟时间内上下线，判断5分钟是否到，未到则进入继续找茬，到了则重置接任务的掩码
	local nEvent = tLabourDay2015_FindMistake_Stc[3]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[3]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[3]["Complete"]
	local nTime = tLabourDay2015_FindMistake_Cont["CompleteTime"]
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		if Task_StcInterval(nEvent,nType,nTime,0) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		end
	end
	
	--进入西校场
	local nMapId = tLabourDay2015_FindMistake_Cont[8048]["Mapid"]
	local nBoundX = tLabourDay2015_FindMistake_Cont[8048]["CellX"]
	local nBoundY = tLabourDay2015_FindMistake_Cont[8048]["CellY"]
	local nBoundCX = tLabourDay2015_FindMistake_Cont["BoundCX"]
	local nBoundCY = tLabourDay2015_FindMistake_Cont["BoundCY"]
	
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,1,0)
	User_TalkChannel2007(tLabourDay2015_FindMistake_Text["TalkChannel2007"]["GoInto"])
end

--奉武:接受任务
function LabourDay2015_FindMistake_HelpNpc(nNpcId)
	-- 判断玩家等级
	local nLevel = tLabourDay2015_FindMistake_Cont["Level"]
	local nMete = tLabourDay2015_FindMistake_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--已完成任务 找到20个
	if  LabourDay2015_FindMistake_ChkStcComplete(2) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--玩家当前已领取过任务，提示时间紧迫
	if LabourDay2015_FindMistake_ChkStcComplete(3) then	
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	--接Option1:我乐意帮你。
	LinkNpcGossipFunc_New(nNpcId,"2-1")

	-- 掩码设值stc(76,9) == 1
	local nEvent = tLabourDay2015_FindMistake_Stc[3]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[3]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[3]["Complete"]
	Task_SetStatistic(nEvent,nType,nComplete,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	Sys_SaveActionFestivalLog(tLabourDay2015_FindMistake_Log["GetTaskLog"])
	
	--玩家在西校场内时，定时器5分钟，超过5分钟，将玩家传送回去
	local nMapId = tLabourDay2015_FindMistake_Cont[8048]["Mapid"]
	if Get_UserMapId() == nMapId then
		User_SetTimer(tLabourDay2015_FindMistake_Cont["CompleteTime"],"</F>LabourDay2015_FindMistake_FiveMinutes",1)
	end
end

--五分钟时间到，传送回双龙城，掩码清零
function LabourDay2015_FindMistake_FiveMinutes()
	-- 判断活动时间
	if not LabourDay2015_FindMistake_TimeJudgement() then
		return
	end
	
	--判断是否在活动地图中，不在活动地图则不传送
	local nMapId_1= tLabourDay2015_FindMistake_Cont[8048]["Mapid"]
	if Get_UserMapId() ~= nMapId_1 then
		return
	end
	
	--传送回去
	local nMapId = tLabourDay2015_FindMistake_Cont[8047]["Mapid"]
	local nBoundX = tLabourDay2015_FindMistake_Cont[8047]["CellX"]
	local nBoundY = tLabourDay2015_FindMistake_Cont[8047]["CellY"]
	local nBoundCX = tLabourDay2015_FindMistake_Cont["BoundCX"]
	local nBoundCY = tLabourDay2015_FindMistake_Cont["BoundCY"]

	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,1,0)
	User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["TimeOut"])
	
	--如果5分钟被传出地图后正好完成了20个，完成任务，不清掩码
	if LabourDay2015_FindMistake_ChkStcComplete(2) then
		local nEvent = tLabourDay2015_FindMistake_Stc[1]["EventType"]
		local nType = tLabourDay2015_FindMistake_Stc[1]["DataType"]
		local nComplete = tLabourDay2015_FindMistake_Stc[1]["Complete"]
		-- 掩码设值stc(76,7) == 1
		Task_SetStatistic(nEvent,nType,nComplete,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["Successful"])
		return
	end
	
	--清除任务stc
	Task_SetStatistic(tLabourDay2015_FindMistake_Stc[1]["EventType"],tLabourDay2015_FindMistake_Stc[1]["DataType"],0,1,0)
	Task_SetStatistic(tLabourDay2015_FindMistake_Stc[2]["EventType"],tLabourDay2015_FindMistake_Stc[2]["DataType"],0,1,0)
	Task_SetStatistic(tLabourDay2015_FindMistake_Stc[3]["EventType"],tLabourDay2015_FindMistake_Stc[3]["DataType"],0,1,0)
	Task_SetStatistic(tLabourDay2015_FindMistake_Stc[5]["EventType"],tLabourDay2015_FindMistake_Stc[5]["DataType"],0,1,0)
end

--离开西校场
function LabourDay2015_FindMistake_LeaveMap(nNpcId)
	--切换地图,传送回去
	local nMapId = tLabourDay2015_FindMistake_Cont[8047]["Mapid"]
	local nBoundX = tLabourDay2015_FindMistake_Cont[8047]["CellX"]
	local nBoundY = tLabourDay2015_FindMistake_Cont[8047]["CellY"]
	local nBoundCX = tLabourDay2015_FindMistake_Cont["BoundCX"]
	local nBoundCY = tLabourDay2015_FindMistake_Cont["BoundCY"]

	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,1,0)
	User_TalkChannel2007(tLabourDay2015_FindMistake_Text["TalkChannel2007"]["GoBack"])
end

--点击正确的npc
function LabourDay2015_FindMistake_FindRightOne()
	local nNpcId = Get_NpcId()
	--判断当前是否有任务 stc(76,9) == 1
	if not LabourDay2015_FindMistake_ChkStcComplete(3) then
		--没有任务:提示不要打扰
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["NoTask"])
		return
	end
	
	--时间戳判断5分钟是否到，到了则传出地图，防止玩家上下线，计时器失效
	local nTime = tLabourDay2015_FindMistake_Cont["CompleteTime"]
	if Task_ChkStcValue(tLabourDay2015_FindMistake_Stc[3]["EventType"],tLabourDay2015_FindMistake_Stc[3]["DataType"],">=",tLabourDay2015_FindMistake_Stc[3]["Complete"]) then
		if Task_StcInterval(tLabourDay2015_FindMistake_Stc[3]["EventType"],tLabourDay2015_FindMistake_Stc[3]["DataType"],nTime,0) then
			LabourDay2015_FindMistake_FiveMinutes()
			return
		end
	end
	
	--判断是否在惩罚10s的时间内
	local nEvent = tLabourDay2015_FindMistake_Stc[6]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[6]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[6]["Complete"]
	local nTime = tLabourDay2015_FindMistake_Cont["PunishTime"]
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		if Task_StcInterval(nEvent,nType,nTime,0) then
			Task_SetStatistic(nEvent,nType,0,1,0)
		else
			User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["TimeNotOut"])
			return
		end
	end
	
	--如果stc(76,8) >= 20  完成任务
	if  LabourDay2015_FindMistake_ChkStcComplete(2) then
		local nEvent = tLabourDay2015_FindMistake_Stc[1]["EventType"]
		local nType = tLabourDay2015_FindMistake_Stc[1]["DataType"]
		local nComplete = tLabourDay2015_FindMistake_Stc[1]["Complete"]
		-- 掩码设值stc(76,7) == 1
		Task_SetStatistic(nEvent,nType,nComplete,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["Successful"])
		--找完20个自动传出地图
		local nMapId = tLabourDay2015_FindMistake_Cont[8047]["Mapid"]
		local nBoundX = tLabourDay2015_FindMistake_Cont[8047]["CellX"]
		local nBoundY = tLabourDay2015_FindMistake_Cont[8047]["CellY"]
		local nBoundCX = tLabourDay2015_FindMistake_Cont["BoundCX"]
		local nBoundCY = tLabourDay2015_FindMistake_Cont["BoundCY"]
		User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,1,0)
		return 
	end

	--判断20个正确的npc中的任意一个是否被找到过
	local nEvent = tLabourDay2015_FindMistake_Stc[5]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[5]["DataType"]
	local nValue = Get_UserStatisticValue(nEvent,nType)
	if Sys_ParseNumbersContain(tLabourDay2015_FindMistake_Num[nNpcId],nValue) then
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["FindNext"])
		return
	end
	
	--给正确的npc赋值
	local nEvent = tLabourDay2015_FindMistake_Stc[5]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[5]["DataType"]
	local nAddNum = tLabourDay2015_FindMistake_Num[nNpcId]
	Task_AddStatistic(nEvent,nType,nAddNum,1,0)
	
	-- stc(76,8) += 1 
	local nEvent = tLabourDay2015_FindMistake_Stc[2]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[2]["DataType"]
	Task_AddStatistic(nEvent,nType,1,1,0)
	
	--奖励玩家		
	--User_AddExpTime(15)
	if Get_UserLevel() < tLabourDay2015_FindMistake_Cont["LevTop"] then
		User_AddExpTime(tLabourDay2015_FindMistake_Cont["exp"])
	end
	User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["RightLabour"])
end

--点击错误的npc
function LabourDay2015_FindMistake_FindWrongOne()
	--判断玩家当前是否有任务stc(76,9) == 1
	if not LabourDay2015_FindMistake_ChkStcComplete(3) then
		--没有任务:提示不要打扰
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["NoTask"])
		return
	end
	
	if LabourDay2015_FindMistake_ChkStcComplete(2) then
		--完成任务 足够20个
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["Successful"])
		return
	end

	--时间戳判断5分钟是否到，到了则传出地图，防止玩家上下线，计时器失效
	local nTime = tLabourDay2015_FindMistake_Cont["CompleteTime"]
	if Task_ChkStcValue(tLabourDay2015_FindMistake_Stc[3]["EventType"],tLabourDay2015_FindMistake_Stc[3]["DataType"],">=",tLabourDay2015_FindMistake_Stc[3]["Complete"]) then
		if Task_StcInterval(tLabourDay2015_FindMistake_Stc[3]["EventType"],tLabourDay2015_FindMistake_Stc[3]["DataType"],nTime,0) then
			LabourDay2015_FindMistake_FiveMinutes()
			return
		end
	end
	
	--判断是否在惩罚10s的时间内
	local nEvent = tLabourDay2015_FindMistake_Stc[6]["EventType"]
	local nType = tLabourDay2015_FindMistake_Stc[6]["DataType"]
	local nComplete = tLabourDay2015_FindMistake_Stc[6]["Complete"]
	local nTime = tLabourDay2015_FindMistake_Cont["PunishTime"]
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		if Task_StcInterval(nEvent,nType,nTime,0) then
			Task_SetStatistic(nEvent,nType,0,1,0)
		else 
			User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["TimeNotOut"])
			return
		end
	end
	
	local nMapId = tLabourDay2015_FindMistake_Cont[8048]["Mapid"]
	--随机惩罚
	local nNum = math.random(1,8)
	if nNum == 1 or nNum == 2 then
		--让玩家反省10秒
		-- 掩码设值stc(76,12) == 1
		Task_SetStatistic(nEvent,nType,nComplete,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["WrongTimes"])
	elseif nNum >= 3 and nNum <= 6 then
		--随机被传送到地图某个位置
		local nNum1 = math.random(1,4)
		local nBoundX = tLabourDay2015_FindMistake_Map["X"][nNum1]
		local nBoundY = tLabourDay2015_FindMistake_Map["Y"][nNum1]
		User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,1,1,1,0)
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["WrongMaps"])
	elseif nNum == 7 then 
		--减血30
		User_AddLife(tLabourDay2015_FindMistake_Cont["addlife2"])
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["WrongBlood"])
	else
		--减血15
		User_AddLife(tLabourDay2015_FindMistake_Cont["addlife1"])
		User_TalkChannel2005(tLabourDay2015_FindMistake_Text["TalkChannel2005"]["WrongBlood"])
	end
end

--随机改变100个npc的位置
function LabourDay2015_FindMistake_ChangeNpcPosition()
	-- 判断活动时间
	if not LabourDay2015_FindMistake_TimeJudgement() then
		return
	end
	
	local nMapId = tLabourDay2015_FindMistake_Cont[8048]["Mapid"]
	--正确的npcid
	--nId_right[4大组][5个小组正确的npcid]
	local nId_right = {{8049,8054,8059,8064,8069},
									{8074,8079,8084,8089,8094},
									{8099,8104,8109,8114,8119},
									{8124,8129,8134,8139,8144}}
	--错误的npcid
	-- nId_wrong[4大组][5个小组][4个错误的npcid]
	local nId_wrong =	{{{8050,8051,8052,8053},{8055,8056,8057,8058},{8060,8061,8062,8063},{8065,8066,8067,8068},{8070,8071,8072,8073}},
									{{8075,8076,8077,8078},{8080,8081,8082,8083},{8085,8086,8087,8088},{8090,8091,8092,8093},{8095,8096,8097,8098}},
									{{8100,8101,8102,8103},{8105,8106,8107,8108},{8110,8111,8112,8113},{8115,8116,8117,8118},{8120,8121,8122,8123}},
									{{8125,8126,8127,8128},{8130,8131,8132,8133},{8135,8136,8137,8138},{8140,8141,8142,8143},{8145,8146,8147,8148}}}
	--各组内正确的npc与本组内的其余npc随机交换位置	
	local i,j,k = 1,1,1
	for i = 1,4 do 
		for j = 1,5 do
			local nPosX = Get_NpcPositionX(nId_right[i][j])
			local nPosY = Get_NpcPositionY(nId_right[i][j])
			for k = 1,4 do
				local nWrongX = Get_NpcPositionX(nId_wrong[i][j][k])
				local nWrongY = Get_NpcPositionY(nId_wrong[i][j][k])
				--同一组的x坐标相同
				if nPosX == nWrongX then
					--正确的与错误的交换位置
					local nNum = math.random(1,4)
					local  nPosY_NotChg = Get_NpcPositionY(nId_right[i][j])
					Npc_MoveNpcPos(nId_right[i][j],nMapId,nWrongX,Get_NpcPositionY(nId_wrong[i][j][nNum]))	
					Npc_MoveNpcPos(nId_wrong[i][j][nNum],nMapId,nPosX,nPosY_NotChg)
				end
			end
		end
	end
end

--203W时间触发 每隔5分钟改变100个npc的位置
-- tOntimerMin_M[00] = tOntimerMin_M[00] or {}
-- table.insert(tOntimerMin_M[00],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[05] = tOntimerMin_M[05] or {}
-- table.insert(tOntimerMin_M[05],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[10] = tOntimerMin_M[10] or {}
-- table.insert(tOntimerMin_M[10],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[15] = tOntimerMin_M[15] or {}
-- table.insert(tOntimerMin_M[15],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[20] = tOntimerMin_M[20] or {}
-- table.insert(tOntimerMin_M[20],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[25] = tOntimerMin_M[25] or {}
-- table.insert(tOntimerMin_M[25],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[30] = tOntimerMin_M[30] or {}
-- table.insert(tOntimerMin_M[30],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[35] = tOntimerMin_M[35] or {}
-- table.insert(tOntimerMin_M[35],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[40] = tOntimerMin_M[40] or {}
-- table.insert(tOntimerMin_M[40],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[45] = tOntimerMin_M[45] or {}
-- table.insert(tOntimerMin_M[45],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[50] = tOntimerMin_M[50] or {}
-- table.insert(tOntimerMin_M[50],LabourDay2015_FindMistake_ChangeNpcPosition)
-- tOntimerMin_M[55] = tOntimerMin_M[55] or {}
-- table.insert(tOntimerMin_M[55],LabourDay2015_FindMistake_ChangeNpcPosition)

------------------------------------------------NPC模块--------------------------------------------------
--8047 青龙校尉·萧勇对白
tNpcFace[450] = 101 
tNpcGossip[8047] = tNpcGossip[8047] or DefaultNpc:new{}
tNpcGossip[8047]["OptionHidden"] = 1

--活动前对白
tNpcGossip[8047]["Text1-1"] = {111,112,113}
tNpcGossip[8047]["Text111"] = tLabourDay2015_FindMistake_Text[8047]["Text111"]
tNpcGossip[8047]["Text112"] = tLabourDay2015_FindMistake_Text[8047]["Text112"]
tNpcGossip[8047]["Text113"] = tLabourDay2015_FindMistake_Text[8047]["Text113"]
tNpcGossip[8047]["tOption1-1"] = {1}
tNpcGossip[8047]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLabourDay2015_FindMistake_Cont["BeforeActivityTime"])
end

--活动后对白
tNpcGossip[8047]["Text1-2"] = {121}
tNpcGossip[8047]["Text121"] = tLabourDay2015_FindMistake_Text[8047]["Text121"]
tNpcGossip[8047]["tOption1-2"] = {2}
tNpcGossip[8047]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLabourDay2015_FindMistake_Cont["AfterActivityTime"])
end

--活动中对白
tNpcGossip[8047]["Text1-3"] = {131,132,133,134}
tNpcGossip[8047]["Text131"] = tLabourDay2015_FindMistake_Text[8047]["Text131"]
tNpcGossip[8047]["Text132"] = tLabourDay2015_FindMistake_Text[8047]["Text132"]
tNpcGossip[8047]["Text133"] = tLabourDay2015_FindMistake_Text[8047]["Text133"]
tNpcGossip[8047]["Text134"] = tLabourDay2015_FindMistake_Text[8047]["Text134"]
tNpcGossip[8047]["tOption1-3"] = {3,4,5,6}
tNpcGossip[8047]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tLabourDay2015_FindMistake_Cont["ActivityTime"])
end

--接Option3：我要领取奖励。
--每日只可领取一次
tNpcGossip[8047]["Text3-1"] = {311}
tNpcGossip[8047]["Text311"] = tLabourDay2015_FindMistake_Text[8047]["Text311"]
tNpcGossip[8047]["tOption3-1"] = {7}

--未完成任务，不可领取（不满20个）
tNpcGossip[8047]["Text3-2"] = {321,322}
tNpcGossip[8047]["Text321"] = tLabourDay2015_FindMistake_Text[8047]["Text321"]
tNpcGossip[8047]["Text322"] = tLabourDay2015_FindMistake_Text[8047]["Text322"]
tNpcGossip[8047]["tOption3-2"] = {9}

--接Option4：请说得详细一些。
tNpcGossip[8047]["Text4-1"] = {411,412,413,414}
tNpcGossip[8047]["Text411"] = tLabourDay2015_FindMistake_Text[8047]["Text411"]
tNpcGossip[8047]["Text412"] = tLabourDay2015_FindMistake_Text[8047]["Text412"]
tNpcGossip[8047]["Text413"] = tLabourDay2015_FindMistake_Text[8047]["Text413"]
tNpcGossip[8047]["Text414"] = tLabourDay2015_FindMistake_Text[8047]["Text414"]
tNpcGossip[8047]["tOption4-1"] = {5,8}

--接Option5：送我进入西校场。
--当天次数大于1次
tNpcGossip[8047]["Text5-1"] = {511,512}
tNpcGossip[8047]["Text511"] = tLabourDay2015_FindMistake_Text[8047]["Text511"]
tNpcGossip[8047]["Text512"] = tLabourDay2015_FindMistake_Text[8047]["Text512"]
tNpcGossip[8047]["tOption5-1"] = {7}

--等级不足
tNpcGossip[8047]["Text5-2"] = {521,522}
tNpcGossip[8047]["Text521"] = tLabourDay2015_FindMistake_Text[8047]["Text521"] 
tNpcGossip[8047]["Text522"] = tLabourDay2015_FindMistake_Text[8047]["Text522"] 
tNpcGossip[8047]["tOption5-2"] = {7}

--选项
tNpcGossip[8047]["Option1"] = tLabourDay2015_FindMistake_Text[8047]["Option1"]
tNpcGossip[8047]["Option2"] = tLabourDay2015_FindMistake_Text[8047]["Option2"]
--我要领取奖励。
tNpcGossip[8047]["Option3"] = tLabourDay2015_FindMistake_Text[8047]["Option3"]
tNpcGossip[8047]["OptionFunc3"]="LabourDay2015_FindMistake_GetReward</N>8047"

tNpcGossip[8047]["Option4"] = tLabourDay2015_FindMistake_Text[8047]["Option4"]
tNpcGossip[8047]["OptionFunc4"]="LabourDay2015_FindMistake_KnowDetails</N>8047"

--送我进入西校场。
tNpcGossip[8047]["Option5"] = tLabourDay2015_FindMistake_Text[8047]["Option5"]
tNpcGossip[8047]["OptionFunc5"]="LabourDay2015_FindMistake_SendInMap</N>8047"

tNpcGossip[8047]["Option6"] = tLabourDay2015_FindMistake_Text[8047]["Option6"]
tNpcGossip[8047]["Option7"] = tLabourDay2015_FindMistake_Text[8047]["Option7"]
tNpcGossip[8047]["Option8"] = tLabourDay2015_FindMistake_Text[8047]["Option8"]
tNpcGossip[8047]["Option9"] = tLabourDay2015_FindMistake_Text[8047]["Option9"]


--8048  白虎校尉·奉武对白
tNpcFace[451] = 59
tNpcGossip[8048] = tNpcGossip[8048] or DefaultNpc:new{}
tNpcGossip[8048]["OptionHidden"] = 1

--活动中对白
tNpcGossip[8048]["Text1-1"] = {111,112,113,114}
tNpcGossip[8048]["Text111"] = tLabourDay2015_FindMistake_Text[8048]["Text111"]
tNpcGossip[8048]["Text112"] = tLabourDay2015_FindMistake_Text[8048]["Text112"]
tNpcGossip[8048]["Text113"] = tLabourDay2015_FindMistake_Text[8048]["Text113"]
tNpcGossip[8048]["Text114"] = tLabourDay2015_FindMistake_Text[8048]["Text114"]
tNpcGossip[8048]["tOption1-1"] = {1,2,3}
tNpcGossip[8048]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLabourDay2015_FindMistake_Cont["ActivityTime"])
end
	
--接Option1:我乐意帮你。
tNpcGossip[8048]["Text2-1"] = {211,212,213,214}
tNpcGossip[8048]["Text211"] = tLabourDay2015_FindMistake_Text[8048]["Text211"]
tNpcGossip[8048]["Text212"] = tLabourDay2015_FindMistake_Text[8048]["Text212"]
tNpcGossip[8048]["Text213"] = tLabourDay2015_FindMistake_Text[8048]["Text213"]
tNpcGossip[8048]["Text214"] = tLabourDay2015_FindMistake_Text[8048]["Text214"]
tNpcGossip[8048]["tOption2-1"] = {4}

--等级不足
tNpcGossip[8048]["Text2-2"] = {221,222}
tNpcGossip[8048]["Text221"] = tLabourDay2015_FindMistake_Text[8048]["Text221"] 
tNpcGossip[8048]["Text222"] = tLabourDay2015_FindMistake_Text[8048]["Text222"] 
tNpcGossip[8048]["tOption2-2"] = {6}
--已接到任务
tNpcGossip[8048]["Text2-3"] = {231}
tNpcGossip[8048]["Text231"] = tLabourDay2015_FindMistake_Text[8048]["Text231"] 
tNpcGossip[8048]["tOption2-3"] = {5}
--已完成任务 找到20个
tNpcGossip[8048]["Text2-4"] = {241,242}
tNpcGossip[8048]["Text241"] = tLabourDay2015_FindMistake_Text[8048]["Text241"] 
tNpcGossip[8048]["Text242"] = tLabourDay2015_FindMistake_Text[8048]["Text242"] 
tNpcGossip[8048]["tOption2-4"] = {6}

--选项
tNpcGossip[8048]["Option1"] = tLabourDay2015_FindMistake_Text[8048]["Option1"]
tNpcGossip[8048]["OptionFunc1"]="LabourDay2015_FindMistake_HelpNpc</N>8048"

tNpcGossip[8048]["Option2"] = tLabourDay2015_FindMistake_Text[8048]["Option2"]
tNpcGossip[8048]["OptionFunc2"]="LabourDay2015_FindMistake_LeaveMap</N>8048"

tNpcGossip[8048]["Option3"] = tLabourDay2015_FindMistake_Text[8048]["Option3"]
tNpcGossip[8048]["Option4"] = tLabourDay2015_FindMistake_Text[8048]["Option4"]
tNpcGossip[8048]["Option5"] = tLabourDay2015_FindMistake_Text[8048]["Option5"]
tNpcGossip[8048]["Option6"] = tLabourDay2015_FindMistake_Text[8048]["Option6"]

