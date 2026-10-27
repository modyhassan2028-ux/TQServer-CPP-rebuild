------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]周年庆点赞、签到(4.27-5.11)
--Purpose:		周年庆活动--点赞、签到(4.27-5.11)
--Creator:		王倩娜
--Created:		2015/07/04
------------------------------------------------------------------------------------

--	命名前缀
--	Anniversary2015_Like_

--	掩码说明

--task_detail 6412
-- stc(122,30) 单人当天的点赞次数。
-- stc(122,31) 周年庆礼包奖励的领取，一天一次。
-- stc(122,32) 外套奖励的领取，一天一次。
-- 50467 data1 记录全服当天的点赞次数。隔天需清理

-- LOGID	10002167

--常量表配置
local tAnniversary2015_Like_Cont = {}
	--活动时间
	tAnniversary2015_Like_Cont["ActivityTime"] = "2015-05-07 00:00 2015-05-27 23:59"
	tAnniversary2015_Like_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-05-06 23:59"

	--玩家等级要求
	tAnniversary2015_Like_Cont["Metempsychosis"] = 0
	tAnniversary2015_Like_Cont["Level"] = 80
	
	-- 掩码
	--stc(122,30) 单人当天的点赞次数。		["Like"]
	--stc(122,31) 周年庆礼包奖励的领取，一天一次。 ["LikeReward"]
	--stc(122,32) 外套奖励的领取，一天一次。 ["ExtraReward"]
	tAnniversary2015_Like_Cont["StcEvent"] = 122
	tAnniversary2015_Like_Cont["StcType"] = {}
	tAnniversary2015_Like_Cont["StcType"]["Like"] =30
	tAnniversary2015_Like_Cont["StcType"]["LikeReward"] =31
	tAnniversary2015_Like_Cont["StcType"]["ExtraReward"] =32
	tAnniversary2015_Like_Cont["RewardData"] = {}
	tAnniversary2015_Like_Cont["RewardData"]["Like"] = 100
	tAnniversary2015_Like_Cont["RewardData"]["LikeReward"] = 1
	tAnniversary2015_Like_Cont["RewardData"]["ExtraReward"] = 1
	
	--上线给包掩码
	tAnniversary2015_Like_Cont["Login"] = {}
	tAnniversary2015_Like_Cont["Login"]["StcEvent"] = 133
	tAnniversary2015_Like_Cont["Login"]["StcType"] = 68
	tAnniversary2015_Like_Cont["Login"]["Finish"] = 1

	
	
	-- 动态表
	tAnniversary2015_Like_Cont["Global"] = {}
		tAnniversary2015_Like_Cont["Global"]["Id"] = 50467
		tAnniversary2015_Like_Cont["Global"]["RewardData"] = 10000

	--背包空间
	tAnniversary2015_Like_Cont["BagSpace"] = 1

	-- 任务物品
	tAnniversary2015_Like_Cont["LikeItem"] = 711897
	tAnniversary2015_Like_Cont["CardItem"] = 3006048

	-- 奖励物品
	tAnniversary2015_Like_Cont["FestivalId"] = 3404
	tAnniversary2015_Like_Cont["LogId"] = 10002167
	tAnniversary2015_Like_Cont["ExtraReward"] = 3003481
	
	tAnniversary2015_Like_Cont["ExpLevel"] = 140
	tAnniversary2015_Like_Cont["ExpTime"] = 30
	
	local tAnniversary2015_Like_Goto = {}
		tAnniversary2015_Like_Goto["CellX"] = 287
		tAnniversary2015_Like_Goto["CellY"] = 369
		tAnniversary2015_Like_Goto["MapId"] = 1002

-- --各种光效
	local tAnniversary2015_Like_Effect = {}
		tAnniversary2015_Like_Effect[1] = "good"
		tAnniversary2015_Like_Effect[11] = "angelwing4"
		tAnniversary2015_Like_Effect[5] = "cool"
		tAnniversary2015_Like_Effect[55] = "angelwing5"
		tAnniversary2015_Like_Effect[10] = "wonderfull"
		tAnniversary2015_Like_Effect[110] = "angelwing6"
		tAnniversary2015_Like_Effect[100] = "perfect"
		tAnniversary2015_Like_Effect[1100] = "angelwing7"
		tAnniversary2015_Like_Effect["ReceiveReward"] = "angelwing"
	
-- --LOG 表
	local tAnniversary2015_Like_LOG = {}
		--打怪获得赞
		tAnniversary2015_Like_LOG["GetLike"] = "0,0,0,0,10002167,1[1],711897,%d"
		--点赞100次获奖
		tAnniversary2015_Like_LOG["LikeReward"] = "0,0,0,0,10002167,2[1],3007625,1"
		--点赞额外奖励
		tAnniversary2015_Like_LOG["LikeExReward"] = "0,0,0,0,10002167,2[2],3003481,1"
		--上交赞
		tAnniversary2015_Like_LOG["SubmitLike"] = "0,0,711897,%d,10002167,1[2],0,0"
		--上线获得卡
		tAnniversary2015_Like_LOG["GetCard"] = "0,0,0,0,10002167,2,3006048,1"
		--使用卡获得经验
		tAnniversary2015_Like_LOG["GetExp"] = "0,0,0,0,10002167,2,4,30"
	
--自检清理
	local tAnniversary2015_Like_ClearGlobal = {}
		tAnniversary2015_Like_ClearGlobal["ActivityTime"] = "00:00 00:05"
--概率
	local  tAnniversary2015_Like_Award = {}
	tAnniversary2015_Like_Award[711897] = {}
	tAnniversary2015_Like_Award[711897][1] = {}
	tAnniversary2015_Like_Award[711897][1]["ItemChanceSum"] = 1000					

	tAnniversary2015_Like_Award[711897][1][1] = {}
	tAnniversary2015_Like_Award[711897][1][1]["RandomItemChanceType"] = 2			
	tAnniversary2015_Like_Award[711897][1][1]["ItemChance"] = 600					
	tAnniversary2015_Like_Award[711897][1][1]["Item_1"] = 1							

	tAnniversary2015_Like_Award[711897][1][2] = {}
	tAnniversary2015_Like_Award[711897][1][2]["RandomItemChanceType"] = 2
	tAnniversary2015_Like_Award[711897][1][2]["ItemChance"] = 300
	tAnniversary2015_Like_Award[711897][1][2]["Item_1"] = 5

	tAnniversary2015_Like_Award[711897][1][3] = {}
	tAnniversary2015_Like_Award[711897][1][3]["RandomItemChanceType"] = 2
	tAnniversary2015_Like_Award[711897][1][3]["ItemChance"] = 90
	tAnniversary2015_Like_Award[711897][1][3]["Item_1"] = 10

	tAnniversary2015_Like_Award[711897][1][4] = {}
	tAnniversary2015_Like_Award[711897][1][4]["RandomItemChanceType"] = 2
	tAnniversary2015_Like_Award[711897][1][4]["ItemChance"] = 10
	tAnniversary2015_Like_Award[711897][1][4]["Item_1"] = 100

-- --------------------------------------逻辑部分-----------------------------------------
--点“赞”
function Anniversary2015_Like_DoLike(nNpcId)

	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_Like_Cont["Level"],tAnniversary2015_Like_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--存在物品
	local nLikeID = tAnniversary2015_Like_Cont["LikeItem"]
	if not Item_ChkItem(nLikeID) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	LinkNpcGossipFunc_New(nNpcId,"2-3")
end

--未领取过奖励
function Anniversary2015_Like_Complete(sType)
	local nEvent = tAnniversary2015_Like_Cont["StcEvent"]
	local nType = tAnniversary2015_Like_Cont["StcType"][sType]
	local nRewardData = tAnniversary2015_Like_Cont["RewardData"][sType]
	
	if Task_StcInterval(nEvent,tAnniversary2015_Like_Cont["StcType"]["Like"],1,4) then
		Task_SetStatistic(nEvent,tAnniversary2015_Like_Cont["StcType"]["Like"],0,1,0)
		Task_SetStcTimestamp(nEvent,tAnniversary2015_Like_Cont["StcType"]["Like"],0,0)
	end
	
	-- 判断是否完成任务
	if Task_ChkStcValue(nEvent,nType,">=",nRewardData) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			return true
		else
			return false
		end
	else
		return true
	end
end

--领取奖励
function	Anniversary2015_Like_GetReward(nNpcId,sType)
		-- 判断活动时间
	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nEvent = tAnniversary2015_Like_Cont["StcEvent"]
	local nType = tAnniversary2015_Like_Cont["StcType"][sType]
	local nRewardData = tAnniversary2015_Like_Cont["RewardData"][sType]

	--个人奖励
	if nType == tAnniversary2015_Like_Cont["StcType"]["Like"] then
		--是否已领取
		if not Anniversary2015_Like_Complete("LikeReward") then
			LinkNpcGossipFunc_New(nNpcId,"4-2")
			return
		end
		--点赞次数>=100
		if  Task_ChkStcValue(nEvent,nType,"<",nRewardData) then
			LinkNpcGossipFunc_New(nNpcId,"4-1")
			return
		end
		--背包空间
		if not User_CheckLeftSpace(tAnniversary2015_Like_Cont["BagSpace"]) then
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		end
		--打码给奖
		local nStcType = tAnniversary2015_Like_Cont["StcType"]["LikeReward"]
		local nComplete = tAnniversary2015_Like_Cont["RewardData"]["LikeReward"]
		Task_SetStatistic(nEvent,nStcType,nComplete,1,0)
		Task_SetStcTimestamp(nEvent,nStcType,0,0)

		FestivalGeneralPackage_GetGift(tAnniversary2015_Like_Cont["FestivalId"],tAnniversary2015_Like_Cont["LogId"])
		Sys_SaveActionFestivalLog(tAnniversary2015_Like_LOG["LikeReward"])
		User_EffectAdd("self",tAnniversary2015_Like_Effect["ReceiveReward"])
		LinkNpcGossipFunc_New(nNpcId,"4-4")
	end
	--全服奖励
	if nType == tAnniversary2015_Like_Cont["StcType"]["ExtraReward"] then
	--全服超过1w
		local nGlobalId = tAnniversary2015_Like_Cont["Global"]["Id"]
		local nLikeType = tAnniversary2015_Like_Cont["StcType"]["Like"]
	
		if Anniversary2015_Like_ClearGlbDetail(nGlobalId) then
		end 

		local nRewardData = tAnniversary2015_Like_Cont["Global"]["RewardData"]
		local nData1 = Get_SysDynaGlobalData1(nGlobalId)
		local nData5 = Get_SysDynaGlobalData5(nGlobalId)

		if nData1 < nRewardData then
			Anniversary2015_Like_CheckScore(nData1,"ExtraReward")
			return
		end
	--是否已领取
		if not Anniversary2015_Like_Complete("ExtraReward") then
			LinkNpcGossipFunc_New(nNpcId,"5-2")
			return
		end
	--点赞数非零
		if Task_ChkStcValue(nEvent,nLikeType,"==",0) then
			LinkNpcGossipFunc_New(nNpcId,"5-1")
			return
		end
	-- 空间
		if not User_CheckLeftSpace(tAnniversary2015_Like_Cont["BagSpace"]) then
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		end
	-- 打码给奖
		local nFinish = tAnniversary2015_Like_Cont["RewardData"]["ExtraReward"]

		Task_SetStatistic(nEvent,nType,nFinish,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		
		Item_AddItem(tAnniversary2015_Like_Cont["ExtraReward"])
		Sys_SaveActionFestivalLog(tAnniversary2015_Like_LOG["LikeExReward"])
		User_EffectAdd("self",tAnniversary2015_Like_Effect["ReceiveReward"])
		LinkNpcGossipFunc_New(nNpcId,"5-3")
	end 	
end
--查询赞数量
function Anniversary2015_Like_CheckScore(nNpcId,sType)
			-- 判断活动时间
	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nEvent = tAnniversary2015_Like_Cont["StcEvent"]
	local nType = tAnniversary2015_Like_Cont["StcType"][sType]
	--个人
	if sType == "Like" then
		--未点赞
		if Task_ChkStcValue(nEvent,nType,"==",0) then
			LinkNpcGossipFunc_New(nNpcId,"6-2")
			return
		end
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		end
		local nTemp = Get_UserStatisticValue(nEvent,nType)
		local str = string.format(tAnniversary2015_Like_Text[16495]["Text611"],nTemp)
		Sys_DialogText(str)
		Sys_DialogOption(tAnniversary2015_Like_Text[16495]["Option21"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()

		return
	--全服
	elseif sType == "ExtraReward" then
		local nGlobalId = tAnniversary2015_Like_Cont["Global"]["Id"]
		local nRewardData = tAnniversary2015_Like_Cont["Global"]["RewardData"]
	
		if Anniversary2015_Like_ClearGlbDetail(nGlobalId) then
		end 

		local nData1 = Get_SysDynaGlobalData1(nGlobalId)
		if nData1 >= tAnniversary2015_Like_Cont["Global"]["RewardData"] then
			local str = string.format(tAnniversary2015_Like_Text[16495]["Text711"],nData1)
			Sys_DialogText(str)
			Sys_DialogOption(tAnniversary2015_Like_Text[16495]["Option23"],"</F>NULL")
			Sys_DialogFace(nNpcId)
			Sys_DialogEnd()
		else
			local nDifference = nRewardData - nData1
			local str = string.format(tAnniversary2015_Like_Text[16495]["Text721"],nData1,nDifference)
			Sys_DialogText(str)
			Sys_DialogOption(tAnniversary2015_Like_Text[16495]["Option22"],"</F>NULL")
			Sys_DialogFace(nNpcId)
			Sys_DialogEnd()
		end		
	end	
end
--提交“赞”
function	Anniversary2015_Like_SubmitLike(nNpcId,nNum)
	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	local nLikeID = tAnniversary2015_Like_Cont["LikeItem"]
	if Item_ChkMulItem(nLikeID,nLikeID,nNum) and Item_DelMulItem(nLikeID,nLikeID,nNum) then
	-- 
	--判断隔天清理
		local nEvent = tAnniversary2015_Like_Cont["StcEvent"]
		local nType = tAnniversary2015_Like_Cont["StcType"]["Like"]
		local nEffect = nNum * 11
		local str_Log = string.format(tAnniversary2015_Like_LOG["SubmitLike"],nNum)
		local nGlobalId = tAnniversary2015_Like_Cont["Global"]["Id"]
		
		if Anniversary2015_Like_ClearGlbDetail(nGlobalId) then
		end 
		
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		end
		-- +掩码、重置时间、光效、对白。
		local nTemp = Get_UserStatisticValue(nEvent,nType) + nNum
		Task_SetStatistic(nEvent,nType,nTemp,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		--全服数量
		local nData1 = Get_SysDynaGlobalData1(nGlobalId) + nNum
		Sys_SetSynaGlobalData1(nGlobalId,nData1)
		
		Sys_SaveActionFestivalLog(str_Log)

		User_EffectAdd("self",tAnniversary2015_Like_Effect[nNum])
		User_EffectAdd("self",tAnniversary2015_Like_Effect[nEffect])
		
		local str = string.format(tAnniversary2015_Like_Text[16495]["Text321"],nNum)
		User_TalkChannel2005(str)
		LinkNpcGossipFunc_New(nNpcId,"2-3")

	else 
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
end

--怪物掉落
function Anniversary2015_Like_Monster()
	local nUserId = Get_UserId()
	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		return
	end
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_Like_Cont["Level"],tAnniversary2015_Like_Cont["Metempsychosis"]) then
		return
	end
	--满200就不给了。
	local nLikeID = tAnniversary2015_Like_Cont["LikeItem"]
	if Item_ChkMulItem(nLikeID,nLikeID,200) then
		return
	end
	if not User_CheckLeftSpace(tAnniversary2015_Like_Cont["BagSpace"]) then
			User_TalkChannel2005(tAnniversary2015_Like_Text["SpaceFull"],nUserId)
		return
	end
	-- 概率
	local flat,tNum = Probabil_RandomAward(tAnniversary2015_Like_Award[711897],1)  
	local nNum = tNum[1]["tAward"][1]["Item_1"]

	-- 给物品、log、给光效、对白
	if Item_AddItem(nLikeID,0,nNum) then
		local str_Text = string.format(tAnniversary2015_Like_Text["GetLike"],nNum)
		local str_Log = string.format(tAnniversary2015_Like_LOG["SubmitLike"],nNum)
		local nEffect = nNum * 11

		Sys_SaveActionFestivalLog(str_Log)
		User_EffectAdd("self",tAnniversary2015_Like_Effect[nNum])
		User_EffectAdd("self",tAnniversary2015_Like_Effect[nEffect])
		User_TalkChannel2005(str_Text)
	end	
end

function Anniversary2015_Like_ClearGlbDetail(nGlobalId)
	if  Sys_ChkDayTime(tAnniversary2015_Like_ClearGlobal["ActivityTime"]) then
		local nData5 = Get_SysDynaGlobalData5(nGlobalId)
		if nData5 == 0 then
			Sys_SetSynaGlobalData1(nGlobalId,0)
			Sys_SetSynaGlobalData5(nGlobalId,1)
		end
	else
		Sys_SetSynaGlobalData5(nGlobalId,0)
	end
end


function Anniversary2015_Like_ClearGlobal()
	if Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		local nGlobalId = tAnniversary2015_Like_Cont["Global"]["Id"]
		 Anniversary2015_Like_ClearGlbDetail(nGlobalId) 
	end 
end

--物品
function tAnniversary2015_Like_Pathfinding(nItemId)
	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		if Item_ChkItem(nItemId) then
			Item_DelItem(nItemId)
		end
		return
	end
	local nUserLev = Get_UserLevel()
	if Item_DelItem(nItemId) then
		if nUserLev < tAnniversary2015_Like_Cont["ExpLevel"] then
			User_AddExp(User_CalcTimeToExp(tAnniversary2015_Like_Cont["ExpTime"]))
			Sys_SaveActionFestivalLog(tAnniversary2015_Like_LOG["GetExp"])
			User_TalkChannel2005(tAnniversary2015_Like_Text[3006048]["GetExp"])
		end
		Sys_GotoSomeWhere(tAnniversary2015_Like_Goto["CellX"],tAnniversary2015_Like_Goto["CellY"],tAnniversary2015_Like_Goto["MapId"])
	end
end

--上线
function Anniversary2015_Like_Login()
	local nItemId = tAnniversary2015_Like_Cont["CardItem"]
	local nEvent = tAnniversary2015_Like_Cont["Login"]["StcEvent"]
	local nType = tAnniversary2015_Like_Cont["Login"]["StcType"]
	local nFinish = tAnniversary2015_Like_Cont["Login"]["Finish"]

	if not Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"]) then
		if Item_ChkItem(nItemId) then
			Item_DelItem(nItemId)
		end
		return
	end
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_Like_Cont["Level"],tAnniversary2015_Like_Cont["Metempsychosis"]) then
		return
	end

	if Task_ChkStcValue(nEvent,nType,"==",0) then
		if not User_CheckLeftSpace(tAnniversary2015_Like_Cont["BagSpace"]) then
			User_TalkChannel2005(tAnniversary2015_Like_Text[3006048]["SpaceFull"])
			return
		end
		if	Task_SetStatistic(nEvent,nType,1,1,0) then
			Item_AddItem(tAnniversary2015_Like_Cont["CardItem"])
			Sys_SaveActionFestivalLog(tAnniversary2015_Like_LOG["GetCard"])
			User_TalkChannel2005(tAnniversary2015_Like_Text[3006048]["GetCard"])
		end		
	end
end
--------------------------------------NPC模块-------------------------------------------
	--16495	求赞狂人高大上
	tNpcFace[2938] = 66
	tNpcGossip[16495] = tNpcGossip[16495] or DefaultNpc:new{}
	tNpcGossip[16495]["OptionHidden"] = 1


	--活动时间前
	tNpcGossip[16495]["Text1-1"] = {111,112,113}
	tNpcGossip[16495]["Text111"] = tAnniversary2015_Like_Text[16495]["Text111"]
	tNpcGossip[16495]["Text112"] = tAnniversary2015_Like_Text[16495]["Text112"]
	tNpcGossip[16495]["Text113"] = tAnniversary2015_Like_Text[16495]["Text113"]
	tNpcGossip[16495]["tOption1-1"] = {1}
	tNpcGossip[16495]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tAnniversary2015_Like_Cont["BeforeActivityTime"])
	end

	--活动时间中
	tNpcGossip[16495]["Text1-2"] = {121,122,123}
	tNpcGossip[16495]["Text121"] = tAnniversary2015_Like_Text[16495]["Text121"]
	tNpcGossip[16495]["Text122"] = tAnniversary2015_Like_Text[16495]["Text122"]
	tNpcGossip[16495]["Text123"] = tAnniversary2015_Like_Text[16495]["Text123"]
	tNpcGossip[16495]["tOption1-2"] = {3,4,5,6,7,8,9}
	tNpcGossip[16495]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"])
	end

	--活动时间后
	tNpcGossip[16495]["Text1-3"] = {131}
	tNpcGossip[16495]["Text131"] = tAnniversary2015_Like_Text[16495]["Text131"]
	tNpcGossip[16495]["tOption1-3"] = {2}

	--等级条件不足，提示
	tNpcGossip[16495]["Text2-1"] = {211}
	tNpcGossip[16495]["Text211"] = tAnniversary2015_Like_Text[16495]["Text211"]
	tNpcGossip[16495]["tOption2-1"] = {10}
	--没有赞
	tNpcGossip[16495]["Text2-2"] = {221}
	tNpcGossip[16495]["Text221"] = tAnniversary2015_Like_Text[16495]["Text221"]
	tNpcGossip[16495]["tOption2-2"] = {10}
	--提交赞
	tNpcGossip[16495]["Text2-3"] = {231,232,233}
	tNpcGossip[16495]["Text231"] = tAnniversary2015_Like_Text[16495]["Text231"]
	tNpcGossip[16495]["Text232"] = tAnniversary2015_Like_Text[16495]["Text232"]
	tNpcGossip[16495]["Text233"] = tAnniversary2015_Like_Text[16495]["Text233"]
	tNpcGossip[16495]["tOption2-3"] = {11,12,13,14,15}
	--提交赞数量不足
	tNpcGossip[16495]["Text3-1"] = {311}
	tNpcGossip[16495]["Text311"] = tAnniversary2015_Like_Text[16495]["Text311"]
	tNpcGossip[16495]["tOption3-1"] = {10}
	--成功点赞
	tNpcGossip[16495]["Text3-2"] = {321}
	tNpcGossip[16495]["Text321"] = tAnniversary2015_Like_Text[16495]["Text321"]
	tNpcGossip[16495]["tOption3-2"] = {16}

	--领取点“赞”狂人奖。
	tNpcGossip[16495]["Text4-1"] = {411}
	tNpcGossip[16495]["Text411"] = tAnniversary2015_Like_Text[16495]["Text411"]
	tNpcGossip[16495]["tOption4-1"] = {17}

	tNpcGossip[16495]["Text4-2"] = {421}
	tNpcGossip[16495]["Text421"] = tAnniversary2015_Like_Text[16495]["Text421"]
	tNpcGossip[16495]["tOption4-2"] = {18}
	
	tNpcGossip[16495]["Text4-3"] = {431}
	tNpcGossip[16495]["Text431"] = tAnniversary2015_Like_Text[16495]["Text431"]
	tNpcGossip[16495]["tOption4-3"] = {10}
	--领到奖励
	tNpcGossip[16495]["Text4-4"] = {441}
	tNpcGossip[16495]["Text441"] = tAnniversary2015_Like_Text[16495]["Text441"]
	tNpcGossip[16495]["tOption4-4"] = {19}

	--领取万“赞”狂欢奖。
	tNpcGossip[16495]["Text5-1"] = {511}
	tNpcGossip[16495]["Text511"] = tAnniversary2015_Like_Text[16495]["Text511"]
	tNpcGossip[16495]["tOption5-1"] = {20}

	tNpcGossip[16495]["Text5-2"] = {521}
	tNpcGossip[16495]["Text521"] = tAnniversary2015_Like_Text[16495]["Text521"]
	tNpcGossip[16495]["tOption5-2"] = {10}
	
	tNpcGossip[16495]["Text5-3"] = {531}
	tNpcGossip[16495]["Text531"] = tAnniversary2015_Like_Text[16495]["Text531"]
	tNpcGossip[16495]["tOption5-3"] = {19}

	--查看我的点“赞”数。
	tNpcGossip[16495]["Text6-1"] = {611}
	tNpcGossip[16495]["Text611"] = tAnniversary2015_Like_Text[16495]["Text611"]
	tNpcGossip[16495]["tOption6-1"] = {21}

	tNpcGossip[16495]["Text6-2"] = {621}
	tNpcGossip[16495]["Text621"] = tAnniversary2015_Like_Text[16495]["Text621"]
	tNpcGossip[16495]["tOption6-2"] = {22}

	--查看全服点“赞”数。
	tNpcGossip[16495]["Text7-1"] = {711}
	tNpcGossip[16495]["Text711"] = tAnniversary2015_Like_Text[16495]["Text711"]
	tNpcGossip[16495]["tOption7-1"] = {23}

	tNpcGossip[16495]["Text7-2"] = {721}
	tNpcGossip[16495]["Text721"] = tAnniversary2015_Like_Text[16495]["Text721"]
	tNpcGossip[16495]["tOption7-2"] = {22}

	--查看点“赞”规则。
	tNpcGossip[16495]["Text8-1"] = {811,812,813}
	tNpcGossip[16495]["Text811"] = tAnniversary2015_Like_Text[16495]["Text811"]
	tNpcGossip[16495]["Text812"] = tAnniversary2015_Like_Text[16495]["Text812"]
	tNpcGossip[16495]["Text813"] = tAnniversary2015_Like_Text[16495]["Text813"]
	tNpcGossip[16495]["tOption8-1"] = {24}


	
	
	--npc选项
	tNpcGossip[16495]["Option1"] = tAnniversary2015_Like_Text[16495]["Option1"]
	tNpcGossip[16495]["Option2"] = tAnniversary2015_Like_Text[16495]["Option2"]

	tNpcGossip[16495]["Option3"] = tAnniversary2015_Like_Text[16495]["Option3"]
	tNpcGossip[16495]["OptionFunc3"]="Anniversary2015_Like_DoLike</N>16495"
	tNpcGossip[16495]["OptionChkFunc3"] = function ()
		return  Sys_ChkFullTime(tAnniversary2015_Like_Cont["ActivityTime"])
	end
	tNpcGossip[16495]["Option4"] = tAnniversary2015_Like_Text[16495]["Option4"]
	tNpcGossip[16495]["OptionFunc4"]="Anniversary2015_Like_GetReward</N>16495</S>Like"
	tNpcGossip[16495]["Option5"] = tAnniversary2015_Like_Text[16495]["Option5"]
	tNpcGossip[16495]["OptionFunc5"]="Anniversary2015_Like_GetReward</N>16495</S>ExtraReward"
	tNpcGossip[16495]["Option6"] = tAnniversary2015_Like_Text[16495]["Option6"]
	tNpcGossip[16495]["OptionFunc6"]="Anniversary2015_Like_CheckScore</N>16495</S>Like"
	tNpcGossip[16495]["Option7"] = tAnniversary2015_Like_Text[16495]["Option7"]
	tNpcGossip[16495]["OptionFunc7"]="Anniversary2015_Like_CheckScore</N>16495</S>ExtraReward"
	tNpcGossip[16495]["Option8"] = tAnniversary2015_Like_Text[16495]["Option8"]
	tNpcGossip[16495]["OptionPoint8"] = "8-1"
	tNpcGossip[16495]["Option9"] = tAnniversary2015_Like_Text[16495]["Option9"]
	tNpcGossip[16495]["Option10"] = tAnniversary2015_Like_Text[16495]["Option10"]


	--提交赞
	tNpcGossip[16495]["Option11"] = tAnniversary2015_Like_Text[16495]["Option11"]
	tNpcGossip[16495]["OptionFunc11"]="Anniversary2015_Like_SubmitLike</N>16495</N>1"
	tNpcGossip[16495]["Option12"] = tAnniversary2015_Like_Text[16495]["Option12"]
	tNpcGossip[16495]["OptionFunc12"]="Anniversary2015_Like_SubmitLike</N>16495</N>5"
	tNpcGossip[16495]["Option13"] = tAnniversary2015_Like_Text[16495]["Option13"]
	tNpcGossip[16495]["OptionFunc13"]="Anniversary2015_Like_SubmitLike</N>16495</N>10"
	tNpcGossip[16495]["Option14"] = tAnniversary2015_Like_Text[16495]["Option14"]
	tNpcGossip[16495]["OptionFunc14"]="Anniversary2015_Like_SubmitLike</N>16495</N>100"
	tNpcGossip[16495]["Option15"] = tAnniversary2015_Like_Text[16495]["Option15"]
	tNpcGossip[16495]["Option16"] = tAnniversary2015_Like_Text[16495]["Option16"]
	tNpcGossip[16495]["Option17"] = tAnniversary2015_Like_Text[16495]["Option17"]
	tNpcGossip[16495]["Option18"] = tAnniversary2015_Like_Text[16495]["Option18"]
	tNpcGossip[16495]["Option19"] = tAnniversary2015_Like_Text[16495]["Option19"]
	tNpcGossip[16495]["Option20"] = tAnniversary2015_Like_Text[16495]["Option20"]
	tNpcGossip[16495]["Option21"] = tAnniversary2015_Like_Text[16495]["Option21"]
	tNpcGossip[16495]["Option22"] = tAnniversary2015_Like_Text[16495]["Option22"]
	tNpcGossip[16495]["Option23"] = tAnniversary2015_Like_Text[16495]["Option23"]
	tNpcGossip[16495]["Option24"] = tAnniversary2015_Like_Text[16495]["Option24"]
-------------------------------------------------------物品模块-------------------------------------------------------------
-- 玩转周年庆贺卡
tItem[3006048] = tItem[3006048] or {}

tItem[3006048]["Text1-1"] = {111,112,113,114}
tItem[3006048]["Text111"] = tAnniversary2015_Like_Text[3006048]["Text111"] 
tItem[3006048]["Text112"] = tAnniversary2015_Like_Text[3006048]["Text112"] 
tItem[3006048]["Text113"] = tAnniversary2015_Like_Text[3006048]["Text113"] 
tItem[3006048]["Text114"] = tAnniversary2015_Like_Text[3006048]["Text114"] 
tItem[3006048]["tOption1-1"] = {1}
tItem[3006048]["OptionFunc1"]="tAnniversary2015_Like_Pathfinding</N>3006048"

tItem[3006048]["Option1"] = tAnniversary2015_Like_Text[3006048]["Option1"]



--------------------------------------怪物掉落-------------------------------------------
-- 第一片区
-- 	1	叫天鸡	9593200
-- tMonster[1] = tMonster[1] or {}
-- tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
--table.insert(tMonster[1]["tFunction"],Anniversary2015_Like_Monster)

-- 	2	斑鸠王	9593210
--tMonster[2] = tMonster[2] or {}
--tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
--table.insert(tMonster[2]["tFunction"],Anniversary2015_Like_Monster)

--	3	罗罗鸟	9593220
-- tMonster[3] = tMonster[3] or {}
-- tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
-- table.insert(tMonster[3]["tFunction"],Anniversary2015_Like_Monster)

--	4	幽冥鬼斧王	9593230
-- tMonster[4] = tMonster[4] or {}
-- tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
-- table.insert(tMonster[4]["tFunction"],Anniversary2015_Like_Monster)

--	5	蹑空鬼斧王	9593240
-- tMonster[5] = tMonster[5] or {}
-- tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
-- table.insert(tMonster[5]["tFunction"],Anniversary2015_Like_Monster)


-- 第二片区
--	6	翼蛇	9593250
-- tMonster[6] = tMonster[6] or {}
-- tMonster[6]["tFunction"] = tMonster[6]["tFunction"] or {}
-- table.insert(tMonster[6]["tFunction"],Anniversary2015_Like_Monster)

--	7	土匪	9593260
-- tMonster[7] = tMonster[7] or {}
-- tMonster[7]["tFunction"] = tMonster[7]["tFunction"] or {}
-- table.insert(tMonster[7]["tFunction"],Anniversary2015_Like_Monster)

--	8	火鼠	9593270
-- tMonster[8] = tMonster[8] or {}
-- tMonster[8]["tFunction"] = tMonster[8]["tFunction"] or {}
-- table.insert(tMonster[8]["tFunction"],Anniversary2015_Like_Monster)

--	9	火精灵	9593280
-- tMonster[9] = tMonster[9] or {}
-- tMonster[9]["tFunction"] = tMonster[9]["tFunction"] or {}
-- table.insert(tMonster[9]["tFunction"],Anniversary2015_Like_Monster)

--	66	精悍土匪	9593290
-- tMonster[66] = tMonster[66] or {}
-- tMonster[66]["tFunction"] = tMonster[66]["tFunction"] or {}
-- table.insert(tMonster[66]["tFunction"],Anniversary2015_Like_Monster)

--	67	尖牙火鼠	9593300
-- tMonster[67] = tMonster[67] or {}
-- tMonster[67]["tFunction"] = tMonster[67]["tFunction"] or {}
-- table.insert(tMonster[67]["tFunction"],Anniversary2015_Like_Monster)


-- 第三片区
--	10	须猕猴	9593310
-- tMonster[10] = tMonster[10] or {}
-- tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
-- table.insert(tMonster[10]["tFunction"],Anniversary2015_Like_Monster)

--	11	巨臂猿	9593320
-- tMonster[11] = tMonster[11] or {}
-- tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
-- table.insert(tMonster[11]["tFunction"],Anniversary2015_Like_Monster)

--	12	天雷巨猿	9593330
-- tMonster[12] = tMonster[12] or {}
-- tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
-- table.insert(tMonster[12]["tFunction"],Anniversary2015_Like_Monster)

--	13	蛇人	9593340
-- tMonster[13] = tMonster[13] or {}
-- tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
-- table.insert(tMonster[13]["tFunction"],Anniversary2015_Like_Monster)


-- 第四片区
--	14	沙怪	9593350
-- tMonster[14] = tMonster[14] or {}
-- tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
-- table.insert(tMonster[14]["tFunction"],Anniversary2015_Like_Monster)

--	15	锤山怪	9593360
-- tMonster[15] = tMonster[15] or {}
-- tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
-- table.insert(tMonster[15]["tFunction"],Anniversary2015_Like_Monster)

--	16	巨石怪	9593370
-- tMonster[16] = tMonster[16] or {}
-- tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
-- table.insert(tMonster[16]["tFunction"],Anniversary2015_Like_Monster)

--	17	鬼刃	9593380
-- tMonster[17] = tMonster[17] or {}
-- tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
-- table.insert(tMonster[17]["tFunction"],Anniversary2015_Like_Monster)

--	73	砾沙怪	9593390
-- tMonster[73] = tMonster[73] or {}
-- tMonster[73]["tFunction"] = tMonster[73]["tFunction"] or {}
-- table.insert(tMonster[73]["tFunction"],Anniversary2015_Like_Monster)


-- 第五片区
--	18	金臂鸟人	4081200
-- tMonster[18] = tMonster[18] or {}
-- tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
-- table.insert(tMonster[18]["tFunction"],Anniversary2015_Like_Monster)

--	19	银羽鹰王	4081254
-- tMonster[19] = tMonster[19] or {}
-- tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
-- table.insert(tMonster[19]["tFunction"],Anniversary2015_Like_Monster)

--	55	湖岛强匪	4081258
-- tMonster[55] = tMonster[55] or {}
-- tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
-- table.insert(tMonster[55]["tFunction"],Anniversary2015_Like_Monster)

--	78	银羽鹰魔	4081255
-- tMonster[78] = tMonster[78] or {}
-- tMonster[78]["tFunction"] = tMonster[78]["tFunction"] or {}
-- table.insert(tMonster[78]["tFunction"],Anniversary2015_Like_Monster)

--	79	湖岛悍匪	4081259
-- tMonster[79] = tMonster[79] or {}
-- tMonster[79]["tFunction"] = tMonster[79]["tFunction"] or {}
-- table.insert(tMonster[79]["tFunction"],Anniversary2015_Like_Monster)

--	84	匪兵	9593450
-- tMonster[84] = tMonster[84] or {}
-- tMonster[84]["tFunction"] = tMonster[84]["tFunction"] or {}
-- table.insert(tMonster[84]["tFunction"],Anniversary2015_Like_Monster)

-- 第六片区
--	20	土墓蝠	9593460
-- tMonster[20] = tMonster[20] or {}
-- tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
-- table.insert(tMonster[20]["tFunction"],Anniversary2015_Like_Monster)

--	56	嗜血蝙蝠	9593470
-- tMonster[56] = tMonster[56] or {}
-- tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
-- table.insert(tMonster[56]["tFunction"],Anniversary2015_Like_Monster)

--	57	牛怪	9593480
-- tMonster[57] = tMonster[57] or {}
-- tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
-- table.insert(tMonster[57]["tFunction"],Anniversary2015_Like_Monster)

--	58	血影红魔	9593490
-- tMonster[58] = tMonster[58] or {}
-- tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
-- table.insert(tMonster[58]["tFunction"],Anniversary2015_Like_Monster)



-- 第七片区
--	2411	冰凌腾蛇	9979200
-- tMonster[2411] = tMonster[2411] or {}
-- tMonster[2411]["tFunction"] = tMonster[2411]["tFunction"] or {}
-- table.insert(tMonster[2411]["tFunction"],Anniversary2015_Like_Monster)

--	2416	冰煞邪刀	9979210
-- tMonster[2416] = tMonster[2416] or {}
-- tMonster[2416]["tFunction"] = tMonster[2416]["tFunction"] or {}
-- table.insert(tMonster[2416]["tFunction"],Anniversary2015_Like_Monster)



-- 第八片区
--	2686	深海亡魂	98054381
-- tMonster[2686] = tMonster[2686] or {}
-- tMonster[2686]["tFunction"] = tMonster[2686]["tFunction"] or {}
-- table.insert(tMonster[2686]["tFunction"],Anniversary2015_Like_Monster)

--	2687	深海魔魂	98054382
 -- tMonster[2687] = tMonster[2687] or {}
 -- tMonster[2687]["tFunction"] = tMonster[2687]["tFunction"] or {}
-- table.insert(tMonster[2687]["tFunction"],Anniversary2015_Like_Monster)



-- 时间自检触发
 --tSystem_Prompet_Func = tSystem_Prompet_Func or {}
-- table.insert(tSystem_Prompet_Func,Anniversary2015_Like_ClearGlobal)

--上线触发
-- table.insert(tSystem_PlayLogin_Func,Anniversary2015_Like_Login)


