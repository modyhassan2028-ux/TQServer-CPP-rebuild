------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]2015感恩节之蔓越橘竞赛（11.24-11.30）
--Purpose:	2015感恩节之蔓越橘竞赛（11.24-11.30）
--Creator: 	严振飞
--Created:	2015/08/04
------------------------------------------------------------------------------------
--命名规范
--ThanksGiving2015_Cranberry_

--掩码说明
---[1]	stc(129,51)	记录每轮成绩
---[2]	stc(129,52)	记录每日最好成绩
---[3]	stc(129,53)	记录是否领取过奖励
---[4]	stc(129,54)	记录是否领取过额外奖励
---[5]	stc(129,99)	记录60秒倒计时是否结束

-- 动态码说明cq_dyna_global_data 50645
-- data0	记录目前最高成绩
-- data1	记录目前冠军的ID	datastr1,记录冠军的姓名
-- data2	记录全服昨天最高成绩
-- data3	记录昨天冠军的ID	datastr3,记录昨天冠军的姓名
-- data4	记录昨天冠军是否已经领过奖励
-- data5	动态存储表重置限制

------------------------------------------------------------------------------------
--STC掩码表
local tThanksGiving2015_Cranberry_Stc = {}
	-- stc(129,51)	记录每轮最好成绩
	tThanksGiving2015_Cranberry_Stc[1] = {}
	tThanksGiving2015_Cranberry_Stc[1]["EventData"] = 129
	tThanksGiving2015_Cranberry_Stc[1]["TypeData"] = 51
	tThanksGiving2015_Cranberry_Stc[1]["Reward"] = 15
	tThanksGiving2015_Cranberry_Stc[1]["AddReward"] = 20
	
	-- stc(129,52)	记录每日最好成绩
	tThanksGiving2015_Cranberry_Stc[2] = {}
	tThanksGiving2015_Cranberry_Stc[2]["EventData"] = 129
	tThanksGiving2015_Cranberry_Stc[2]["TypeData"] = 52
	
	-- stc(129,53)	记录是否领取过奖励
	tThanksGiving2015_Cranberry_Stc[3] = {}
	tThanksGiving2015_Cranberry_Stc[3]["EventData"] = 129
	tThanksGiving2015_Cranberry_Stc[3]["TypeData"] = 53
	tThanksGiving2015_Cranberry_Stc[3]["Complete"] = 1
	
	-- stc(129,54)	记录是否领取过奖励
	tThanksGiving2015_Cranberry_Stc[4] = {}
	tThanksGiving2015_Cranberry_Stc[4]["EventData"] = 129
	tThanksGiving2015_Cranberry_Stc[4]["TypeData"] = 54
	tThanksGiving2015_Cranberry_Stc[4]["Complete"] = 1

	-- stc(129,99)	记录60秒倒计时是否结束
	tThanksGiving2015_Cranberry_Stc[5] = {}
	tThanksGiving2015_Cranberry_Stc[5]["EventData"] = 129
	tThanksGiving2015_Cranberry_Stc[5]["TypeData"] = 99
	tThanksGiving2015_Cranberry_Stc[5]["Complete"] = 1

	


------------------------------------------------------------------------------------
--活动数据
local tThanksGiving2015_Cranberry_Data = {}
	-- 活动时间
	tThanksGiving2015_Cranberry_Data["Festival_BefTime"] = "2015-01-01 00:00 2015-11-23 23:59"
	tThanksGiving2015_Cranberry_Data["Festival_NowTime"] = "2015-11-24 00:00 2015-11-30 23:59"
	tThanksGiving2015_Cranberry_Data["Festival_1stTime"] = "2015-11-24 00:00 2015-11-24 23:59"
	tThanksGiving2015_Cranberry_Data["Festival_AftTime"] = "2015-12-01 00:00 2015-12-01 23:59"
	tThanksGiving2015_Cranberry_Data["Festival_203Time"] = "2015-11-24 00:00 2015-12-01 23:59"
	
	--等级，转世设置，满级
	tThanksGiving2015_Cranberry_Data["MinLevel"] = 80
	tThanksGiving2015_Cranberry_Data["MinMeto"] = 0
	tThanksGiving2015_Cranberry_Data["LevMax"] = 140
	
	-- 奖励蔓越橘个数
	tThanksGiving2015_Cranberry_Data["RewardNum"] = 15
	-- 额外奖励蔓越橘个数
	tThanksGiving2015_Cranberry_Data["AddRewardNum"] = 20

	-- 额外奖励
	tThanksGiving2015_Cranberry_Data["Type_Exp"] = 4 --经验
	tThanksGiving2015_Cranberry_Data["Type_Cul"] = 6 --修行值
	tThanksGiving2015_Cranberry_Data["Letter_Exp"] = 60
	tThanksGiving2015_Cranberry_Data["Letter_Cul"] = 50
	
	-- 额外对应对白编号
	tThanksGiving2015_Cranberry_Data["AddReward"] = {}
	tThanksGiving2015_Cranberry_Data["AddReward"][4] = "2-8"
	tThanksGiving2015_Cranberry_Data["AddReward"][6] = "2-9"
	tThanksGiving2015_Cranberry_Data["TextHead"] = {}
	tThanksGiving2015_Cranberry_Data["TextHead"][4] = "Text281"
	tThanksGiving2015_Cranberry_Data["TextHead"][6] = "Text291"

	-- 动态存储表
	tThanksGiving2015_Cranberry_Data["GlobalId"] = 50645
	
	--背包空间
	tThanksGiving2015_Cranberry_Data["ChkSpace"] = 1
	
	--昨天冠军奖励
	tThanksGiving2015_Cranberry_Data["YdayReward"] = 1088000
	
	-- 小果盆寻路数据
	tThanksGiving2015_Cranberry_Data[17264] = {}
	tThanksGiving2015_Cranberry_Data[17264]["NpcId"] = 17264
	tThanksGiving2015_Cranberry_Data[17264]["MapId"] = 1002
	tThanksGiving2015_Cranberry_Data[17264]["PosX"] = 298
	tThanksGiving2015_Cranberry_Data[17264]["PosY"] = 383

	-- 串蔓越橘倒计时数据
	tThanksGiving2015_Cranberry_Data["TimeDelay"] = 60
	tThanksGiving2015_Cranberry_Data["Type"] = 1
	
------------------------------------------------------------------------------------
-- 读条数据
local tThanksGiving2015_Cranberry_Explore = {}
	
	-- 快速串
	tThanksGiving2015_Cranberry_Explore[1] = {}
	tThanksGiving2015_Cranberry_Explore[1]["Secs"] = 2
	tThanksGiving2015_Cranberry_Explore[1]["ActionId"] = 220
	-- 认真串
	tThanksGiving2015_Cranberry_Explore[2] = {}
	tThanksGiving2015_Cranberry_Explore[2]["Secs"] = 4
	tThanksGiving2015_Cranberry_Explore[2]["ActionId"] = 220
	-- 技巧串
	tThanksGiving2015_Cranberry_Explore[3] = {}
	tThanksGiving2015_Cranberry_Explore[3]["Secs"] = 6
	tThanksGiving2015_Cranberry_Explore[3]["ActionId"] = 220
	
	-- 倒计时结束打断
	tThanksGiving2015_Cranberry_Explore["Stop"] = {}
	tThanksGiving2015_Cranberry_Explore["Stop"]["Secs"] = 1
	tThanksGiving2015_Cranberry_Explore["Stop"]["ActionId"] = 220

------------------------------------------------------------------------------------
--活动LOG数据
local tThanksGiving2015_Cranberry_Log = {}
	-- 节日礼包
	tThanksGiving2015_Cranberry_Log["FestivalId"] = 3330
	tThanksGiving2015_Cranberry_Log["LogId"] = 10002333
	-- 获得额外奖励
	tThanksGiving2015_Cranberry_Log["AddReward"] = "0,0,0,0,10002333,2,%d,%d"
	-- 获得昨天冠军奖励
	tThanksGiving2015_Cranberry_Log["YdayReward"] = "0,0,0,0,10002333,2,1088000,1"
	-- 开始串蔓越橘
	tThanksGiving2015_Cranberry_Log["TaskBegin"] = "0,0,0,0,10002333,1[1],0,0"
	-- 结束串蔓越橘
	tThanksGiving2015_Cranberry_Log["TaskEnd"] = "0,0,0,0,10002333,1[2],0,0"

------------------------------------------------------------------------------------
--几率配置表
local tThanksGiving2015_Cranberry_Probabil = {}
-- 【快速串】
	tThanksGiving2015_Cranberry_Probabil[1] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1]["ItemChanceSum"] = 10000
	-- 20%	串上2个
	tThanksGiving2015_Cranberry_Probabil[1][1][1] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1][1]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][1][1]["ItemChance"] = 2000
	tThanksGiving2015_Cranberry_Probabil[1][1][1]["Item_1"] = 2
	-- 55%	串上1个
	tThanksGiving2015_Cranberry_Probabil[1][1][2] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1][2]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][1][2]["ItemChance"] = 5500
	tThanksGiving2015_Cranberry_Probabil[1][1][2]["Item_1"] = 1
	-- 15%	没串上
	tThanksGiving2015_Cranberry_Probabil[1][1][3] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1][3]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][1][3]["ItemChance"] = 1500
	tThanksGiving2015_Cranberry_Probabil[1][1][3]["Item_1"] = 0
	-- 10%	反掉1个
	tThanksGiving2015_Cranberry_Probabil[1][1][4] = {}
	tThanksGiving2015_Cranberry_Probabil[1][1][4]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][1][4]["ItemChance"] = 1000
	tThanksGiving2015_Cranberry_Probabil[1][1][4]["Item_1"] = -1
	
-- 【认真串】
	tThanksGiving2015_Cranberry_Probabil[1][2] = {}
	tThanksGiving2015_Cranberry_Probabil[1][2]["ItemChanceSum"] = 10000
	-- 40%	串上2个
	tThanksGiving2015_Cranberry_Probabil[1][2][1] = {}
	tThanksGiving2015_Cranberry_Probabil[1][2][1]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][2][1]["ItemChance"] = 4000
	tThanksGiving2015_Cranberry_Probabil[1][2][1]["Item_1"] = 2
	-- 60%	串上1个
	tThanksGiving2015_Cranberry_Probabil[1][2][2] = {}
	tThanksGiving2015_Cranberry_Probabil[1][2][2]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][2][2]["ItemChance"] = 6000
	tThanksGiving2015_Cranberry_Probabil[1][2][2]["Item_1"] = 1
	
-- 【技巧串】
	tThanksGiving2015_Cranberry_Probabil[1][3] = {}
	tThanksGiving2015_Cranberry_Probabil[1][3]["ItemChanceSum"] = 10000
	-- 10%	串上5个
	tThanksGiving2015_Cranberry_Probabil[1][3][1] = {}
	tThanksGiving2015_Cranberry_Probabil[1][3][1]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][3][1]["ItemChance"] = 1000
	tThanksGiving2015_Cranberry_Probabil[1][3][1]["Item_1"] = 5
	-- 25%	串上3个
	tThanksGiving2015_Cranberry_Probabil[1][3][2] = {}
	tThanksGiving2015_Cranberry_Probabil[1][3][2]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][3][2]["ItemChance"] = 2500
	tThanksGiving2015_Cranberry_Probabil[1][3][2]["Item_1"] = 3
	-- 45%	串上2个
	tThanksGiving2015_Cranberry_Probabil[1][3][3] = {}
	tThanksGiving2015_Cranberry_Probabil[1][3][3]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][3][3]["ItemChance"] = 4500
	tThanksGiving2015_Cranberry_Probabil[1][3][3]["Item_1"] = 2
	-- 20%	反掉1个
	tThanksGiving2015_Cranberry_Probabil[1][3][4] = {}
	tThanksGiving2015_Cranberry_Probabil[1][3][4]["RandomItemChanceType"] = 2
	tThanksGiving2015_Cranberry_Probabil[1][3][4]["ItemChance"] = 2000
	tThanksGiving2015_Cranberry_Probabil[1][3][4]["Item_1"] = -1

	
---------------------------------逻辑定义--------------------------------------
-- 活动时间判断
function ThanksGiving2015_Cranberry_ChkTime(nNpcId,sNpcGossip)
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		-- 活动结束对白
		LinkNpcGossipFunc_New(nNpcId,"1-2")
	else
		LinkNpcGossipFunc_New(nNpcId,sNpcGossip)
	end
end


-- 寻路函数
function ThanksGiving2015_Cranberry_FindWay(nObject)
	local nPosX = tThanksGiving2015_Cranberry_Data[nObject]["PosX"]
	local nPosY = tThanksGiving2015_Cranberry_Data[nObject]["PosY"]
	local nMapId = tThanksGiving2015_Cranberry_Data[nObject]["MapId"]
	local nNpcId = tThanksGiving2015_Cranberry_Data[nObject]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end


-- 全部掩码重置
function ThanksGiving2015_Cranberry_ResetAllStc()
	local nTemp = 0
	for nStcNum = 2, #tThanksGiving2015_Cranberry_Stc do
		local nEventData = tThanksGiving2015_Cranberry_Stc[nStcNum]["EventData"]
		local nTypeData = tThanksGiving2015_Cranberry_Stc[nStcNum]["TypeData"]
		Task_SetStatistic(nEventData,nTypeData,0,1)
		
		-- 当天最好成绩打时间戳
		if nTemp == 0 then
			Task_SetStcTimestamp(nEventData,nTypeData,0)
			nTemp = nTemp + 1
		end
	end
end


------------------------------【我来领取奖励】-------------------------------------
function ThanksGiving2015_Cranberry_Reward(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 等级判断
	local nMinLev = tThanksGiving2015_Cranberry_Data["MinLevel"]
	local nMinMeto = tThanksGiving2015_Cranberry_Data["MinMeto"]
	if not User_JudgeLevelAndMetempsychosis(nMinLev,nMinMeto) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventData_2 = tThanksGiving2015_Cranberry_Stc[2]["EventData"]
	local nTypeData_2 = tThanksGiving2015_Cranberry_Stc[2]["TypeData"]
	local nEventData_3 = tThanksGiving2015_Cranberry_Stc[3]["EventData"]
	local nTypeData_3 = tThanksGiving2015_Cranberry_Stc[3]["TypeData"]
	local nComplete_3 = tThanksGiving2015_Cranberry_Stc[3]["Complete"]
	local nRewardNum = tThanksGiving2015_Cranberry_Data["RewardNum"]
	
	-- 是否未开始串
	if Task_ChkStcValue(nEventData_2,nTypeData_2,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
		
	-- 隔天
	elseif Task_StcInterval(nEventData_2,nTypeData_2,1,4) then
		--掩码重置
		ThanksGiving2015_Cranberry_ResetAllStc()
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
		
	-- 串蔓越橘个数是否足够
	elseif Task_ChkStcValue(nEventData_2,nTypeData_2,"<",nRewardNum) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
		
	-- 是否领过奖励
	elseif Task_ChkStcValue(nEventData_3,nTypeData_3,">=",nComplete_3) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 背包空间
	if not User_CheckLeftSpace(tThanksGiving2015_Cranberry_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	local nFestivalId = tThanksGiving2015_Cranberry_Log["FestivalId"]
	local nLogId = tThanksGiving2015_Cranberry_Log["LogId"]
	Task_SetStatistic(nEventData_3,nTypeData_3,nComplete_3,1)
	FestivalGeneralPackage_GetGift(nFestivalId,nLogId)
	LinkNpcGossipFunc_New(nNpcId,"2-5")
end

------------------------------【我来领取额外奖励】-------------------------------------
function ThanksGiving2015_Cranberry_AddReward(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	-- 等级判断
	local nMinLev = tThanksGiving2015_Cranberry_Data["MinLevel"]
	local nMinMeto = tThanksGiving2015_Cranberry_Data["MinMeto"]
	if not User_JudgeLevelAndMetempsychosis(nMinLev,nMinMeto) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end

	local nEventData_2 = tThanksGiving2015_Cranberry_Stc[2]["EventData"]
	local nTypeData_2 = tThanksGiving2015_Cranberry_Stc[2]["TypeData"]
	local nEventData_4 = tThanksGiving2015_Cranberry_Stc[4]["EventData"]
	local nTypeData_4 = tThanksGiving2015_Cranberry_Stc[4]["TypeData"]
	local nComplete_4 = tThanksGiving2015_Cranberry_Stc[4]["Complete"]
	local nAddRewardNum = tThanksGiving2015_Cranberry_Data["AddRewardNum"]

	-- 是否未开始串
	if Task_ChkStcValue(nEventData_2,nTypeData_2,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
		
	-- 隔天
	elseif Task_StcInterval(nEventData_2,nTypeData_2,1,4) then

		--掩码重置
		ThanksGiving2015_Cranberry_ResetAllStc()
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
		
	-- 串蔓越橘个数是否足够
	elseif Task_ChkStcValue(nEventData_2,nTypeData_2,"<",nAddRewardNum) then
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
		
	-- 是否领过奖励
	elseif Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then
		LinkNpcGossipFunc_New(nNpcId,"2-7")
		return
	end

	Task_AddStatistic(nEventData_4,nTypeData_4,nComplete_4,1)
	
	-- 满级判断
	local nLevMax = tThanksGiving2015_Cranberry_Data["LevMax"]
	local nUserLev = Get_UserLevel()
	local nAddType = 0
	local nAddValue = 0
	-- 给经验
	if nUserLev < nLevMax then
		nAddType = tThanksGiving2015_Cranberry_Data["Type_Exp"]
		nAddValue = tThanksGiving2015_Cranberry_Data["Letter_Exp"]
		User_AddExpTime(nAddValue)
	
	-- 给修行值
	else
		nAddType = tThanksGiving2015_Cranberry_Data["Type_Cul"]
		nAddValue = tThanksGiving2015_Cranberry_Data["Letter_Cul"]
		User_AddCultivation(nAddValue)
	end
	
	local nCranberry = Get_UserStatisticValue(nEventData_2,nTypeData_2)
	local sLogText = string.format(tThanksGiving2015_Cranberry_Log["AddReward"],nAddType,nAddValue)
	local sTalkText = tThanksGiving2015_Cranberry_Text["AddReward"][nAddType]
	local sIndex = tThanksGiving2015_Cranberry_Data["AddReward"][nAddType]
	local sHeadCont = tThanksGiving2015_Cranberry_Data["TextHead"][nAddType]
	local sTextHead = tThanksGiving2015_Cranberry_Text[17176][sHeadCont]
	tNpcGossip[17176][sHeadCont] = string.format(sTextHead,nCranberry)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
	LinkNpcGossipFunc_New(nNpcId,sIndex)
end


------------------------------【查看排行榜】-------------------------------------
function ThanksGiving2015_Cranberry_Rank(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventData_2 = tThanksGiving2015_Cranberry_Stc[2]["EventData"]
	local nTypeData_2 = tThanksGiving2015_Cranberry_Stc[2]["TypeData"]
	
	-- 隔天
	if Task_StcInterval(nEventData_2,nTypeData_2,1,4) then
		--掩码重置
		ThanksGiving2015_Cranberry_ResetAllStc()
	end
	
	local nUserId = Get_UserId()
	local nGlobalId = tThanksGiving2015_Cranberry_Data["GlobalId"]
	local nFirstId = Get_SysDynaGlobalData(nGlobalId,1)
	local nFirstScore = Get_SysDynaGlobalData(nGlobalId,0)
	local sFirstName = Get_SysDynaGlobalDataStr(nGlobalId,1)
	
	-- 第一名
	if nUserId == nFirstId then
		-- 是否第一天
		if Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_1stTime"]) then
			local sTextHead = tThanksGiving2015_Cranberry_Text[17176]["Text311"]
			tNpcGossip[17176]["Text311"] = string.format(sTextHead,nFirstScore)
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		else
			local sTextHead = tThanksGiving2015_Cranberry_Text[17176]["Text321"]
			tNpcGossip[17176]["Text321"] = string.format(sTextHead,nFirstScore)
			LinkNpcGossipFunc_New(nNpcId,"3-2")
			return
		end
	
	-- 不是第一名
	elseif Task_ChkStcValue(nEventData_2,nTypeData_2,"==",0) then
		-- 今天还未参加
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	
	-- 是否第一天
	elseif Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_1stTime"]) then
		local nStcScore = Get_UserStatisticValue(nEventData_2,nTypeData_2)
		local sTextHead = tThanksGiving2015_Cranberry_Text[17176]["Text341"]
		tNpcGossip[17176]["Text341"] = string.format(sTextHead,nStcScore,sFirstName,nFirstScore)
		LinkNpcGossipFunc_New(nNpcId,"3-4")
	else
		local nStcScore = Get_UserStatisticValue(nEventData_2,nTypeData_2)
		local sTextHead = tThanksGiving2015_Cranberry_Text[17176]["Text351"]
		tNpcGossip[17176]["Text351"] = string.format(sTextHead,nStcScore,sFirstName,nFirstScore)
		LinkNpcGossipFunc_New(nNpcId,"3-5")
	end
end


-----------领取昨天冠军奖励
function ThanksGiving2015_Cranberry_YdayReward(nNpcId)
	local nGlobalId = tThanksGiving2015_Cranberry_Data["GlobalId"]
	local nWinnerId = Get_SysDynaGlobalData(nGlobalId,3)
	local sWinnerName = Get_SysDynaGlobalDataStr(nGlobalId,3)
	local nYdayScore = Get_SysDynaGlobalData(nGlobalId,2)
	local nSysDyGlob_4 = Get_SysDynaGlobalData(nGlobalId,4)
	local nUserId = Get_UserId()
	
	-- 是否存在冠军
	if nWinnerId == 0 or nWinnerId == nil then
		LinkNpcGossipFunc_New(nNpcId,"4-5")
		return
	end
	
	-- 是否冠军
	if nUserId ~= nWinnerId then
		local sTextHead = tThanksGiving2015_Cranberry_Text[17176]["Text411"]
		tNpcGossip[17176]["Text411"] = string.format(sTextHead,sWinnerName,nYdayScore)
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
		
	-- 已领取奖励
	elseif nSysDyGlob_4 ~= 0 then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
		
	-- 背包空间
	elseif not User_CheckLeftSpace(tThanksGiving2015_Cranberry_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end
	
	-- 满足领奖条件
	Sys_SetSynaGlobalData4(tThanksGiving2015_Cranberry_Data["GlobalId"],1)
	Item_AddItem(tThanksGiving2015_Cranberry_Data["YdayReward"])
	Sys_SaveActionFestivalLog(tThanksGiving2015_Cranberry_Log["YdayReward"])
	User_TalkChannel2005(tThanksGiving2015_Cranberry_Text["YdayReward"])
	LinkNpcGossipFunc_New(nNpcId,"4-4")
end

------------------------------【小果盆】-------------------------------------
-- 串蔓越橘结束
function ThanksGiving2015_Cranberry_TaskEnd()
	local nEventData_1 = tThanksGiving2015_Cranberry_Stc[1]["EventData"]
	local nTypeData_1 = tThanksGiving2015_Cranberry_Stc[1]["TypeData"]
	local nEventData_2 = tThanksGiving2015_Cranberry_Stc[2]["EventData"]
	local nTypeData_2 = tThanksGiving2015_Cranberry_Stc[2]["TypeData"]
	local nNewScore = Get_UserStatisticValue(nEventData_1,nTypeData_1)
	local nBestScore = Get_UserStatisticValue(nEventData_2,nTypeData_2)
	local nGlobalId = tThanksGiving2015_Cranberry_Data["GlobalId"]
	local nServerBestScore = Get_SysDynaGlobalData(nGlobalId,0)
	
	if Task_StcInterval(nEventData_2,nTypeData_2,1,4) then
		--掩码重置
		ThanksGiving2015_Cranberry_ResetAllStc()
		Sys_MsgBox(tThanksGiving2015_Cranberry_Text["NextDay"])
		return
	end
	
	-- 新成绩是否为最好成绩
	if nNewScore > nBestScore then
		Task_SetStatistic(nEventData_2,nTypeData_2,nNewScore,1)
		Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
		
		-- 新成绩是否为全服第一
		if nNewScore > nServerBestScore then
			local nUserId = Get_UserId()
			local sUserName = Get_UserName(nUserId)
			Sys_SetSynaGlobalData0(nGlobalId,nNewScore)
			Sys_SetSynaGlobalData1(nGlobalId,nUserId)
			Sys_SetSynaGlobalDataStr1(nGlobalId,sUserName)
		end
	end

	local sBoxText = string.format(tThanksGiving2015_Cranberry_Text["TaskEnd"],nNewScore)
	Sys_SaveActionFestivalLog(tThanksGiving2015_Cranberry_Log["TaskEnd"])
	Sys_MsgBox(sBoxText)
end

-- 串蔓越橘进行中
function ThanksGiving2015_Cranberry_TaskDoing(nNpcId)
	local nEventData_1 = tThanksGiving2015_Cranberry_Stc[1]["EventData"]
	local nTypeData_1 = tThanksGiving2015_Cranberry_Stc[1]["TypeData"]
	local nEventData_5 = tThanksGiving2015_Cranberry_Stc[5]["EventData"]
	local nTypeData_5 = tThanksGiving2015_Cranberry_Stc[5]["TypeData"]
	local nComplete_5 = tThanksGiving2015_Cranberry_Stc[5]["Complete"]
	Task_SetStcTimestamp(nEventData_5,nTypeData_5,0)
	
	-- 是否为第一次串
	if Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0) then
		Task_SetStatistic(nEventData_5,nTypeData_5,nComplete_5,1)
		LinkNpcGossipFunc_New(nNpcId,"1-6")
		
	-- 第二次以后串
	else
		local nSecs = Get_UserStatisticValue(nEventData_1,nTypeData_1)
		local sTextHead = tThanksGiving2015_Cranberry_Text[17177]["Text171"]
		tNpcGossip[17177]["Text171"] = string.format(sTextHead,nSecs)
		LinkNpcGossipFunc_New(nNpcId,"1-7")
	end
end

-- 串蔓越橘倒计时中断
function ThanksGiving2015_Cranberry_TaskStop()
	local nEventData_5 = tThanksGiving2015_Cranberry_Stc[5]["EventData"]
	local nTypeData_5 = tThanksGiving2015_Cranberry_Stc[5]["TypeData"]
	Task_SetStatistic(nEventData_5,nTypeData_5,0,1)
	
	local nSecs = tThanksGiving2015_Cranberry_Explore["Stop"]["Secs"]
	local sContent = tThanksGiving2015_Cranberry_Text["Explore"]["Stop"]
	local nActionId = tThanksGiving2015_Cranberry_Explore["Stop"]["ActionId"]
	local sFunc = "ThanksGiving2015_Cranberry_TaskEnd"
	User_SetExplore(nSecs,sContent,nActionId,sFunc,sFunc)
end

-- 开始串蔓越橘
function ThanksGiving2015_Cranberry_TaskBegin(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventData_1 = tThanksGiving2015_Cranberry_Stc[1]["EventData"]
	local nTypeData_1 = tThanksGiving2015_Cranberry_Stc[1]["TypeData"]
	local nTimeDelay = tThanksGiving2015_Cranberry_Data["TimeDelay"]
	local sFunc = "ThanksGiving2015_Cranberry_TaskStop"
	local nType = tThanksGiving2015_Cranberry_Data["Type"]
	
	User_SetTimer(nTimeDelay,sFunc,nType)
	Task_SetStatistic(nEventData_1,nTypeData_1,0,1)
	Sys_SaveActionFestivalLog(tThanksGiving2015_Cranberry_Log["TaskBegin"])
	ThanksGiving2015_Cranberry_TaskDoing(nNpcId)
end


-- 小果盆接入函数
function ThanksGiving2015_Cranberry_BasinMain(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventData_2 = tThanksGiving2015_Cranberry_Stc[2]["EventData"]
	local nTypeData_2 = tThanksGiving2015_Cranberry_Stc[2]["TypeData"]

	-- 隔天
	if Task_StcInterval(nEventData_2,nTypeData_2,1,4) then
		--掩码重置
		ThanksGiving2015_Cranberry_ResetAllStc()
	end
	
	local nEventData_5 = tThanksGiving2015_Cranberry_Stc[5]["EventData"]
	local nTypeData_5 = tThanksGiving2015_Cranberry_Stc[5]["TypeData"]
	
	-- 隔天
	if Task_StcInterval(nEventData_5,nTypeData_5,1,4) then
		Task_SetStatistic(nEventData_5,nTypeData_5,0,1)
		-- 等级判断
		local nMinLev = tThanksGiving2015_Cranberry_Data["MinLevel"]
		local nMinMeto = tThanksGiving2015_Cranberry_Data["MinMeto"]
		if not User_JudgeLevelAndMetempsychosis(nMinLev,nMinMeto) then
			LinkNpcGossipFunc_New(nNpcId,"1-1")
			return
		end
		
	-- 未隔天
	elseif Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0) then
		-- 等级判断
		local nMinLev = tThanksGiving2015_Cranberry_Data["MinLevel"]
		local nMinMeto = tThanksGiving2015_Cranberry_Data["MinMeto"]
		if not User_JudgeLevelAndMetempsychosis(nMinLev,nMinMeto) then
			LinkNpcGossipFunc_New(nNpcId,"1-1")
			return
		end
		
	-- 倒计时未结束
	else --继续串蔓越橘
		ThanksGiving2015_Cranberry_TaskDoing(nNpcId)
		return
	end
	
	-- 活动中对白
	LinkNpcGossipFunc_New(nNpcId,"1-3")
end

-- 串蔓越橘
function ThanksGiving2015_Cranberry_TaskExplore(nNpcId,nMethod)
	local nEventData_1 = tThanksGiving2015_Cranberry_Stc[1]["EventData"]
	local nTypeData_1 = tThanksGiving2015_Cranberry_Stc[1]["TypeData"]
	-- 走几率
	local flat,tItem = Probabil_RandomAward(tThanksGiving2015_Cranberry_Probabil[1],nMethod)
	local nSuccessNum = tItem[1]["tAward"][1]["Item_1"]

	-- 增加的分数为负数
	if nSuccessNum < 0 then
		if Task_ChkStcValue(nEventData_1,nTypeData_1,"==",0) then
			
			-- 不是技巧串
			if nMethod ~= 3 then
				nSuccessNum = 0
				
			-- 为技巧串
			else
				nSuccessNum = 2
			end
		end
	end
	
	-- 置掩码+提示
	Task_AddStatistic(nEventData_1,nTypeData_1,nSuccessNum,1)
	ThanksGiving2015_Cranberry_TaskDoing(nNpcId)
	local sNumText = tostring(nSuccessNum)
	User_TalkChannel2005(tThanksGiving2015_Cranberry_Text["TaskExplore"][nMethod][sNumText])
end


-- 串蔓越橘选项接入
function ThanksGiving2015_Cranberry_TaskOption(nNpcId,nMethod)
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	-- 倒计时是否结束
	local nEventData_5 = tThanksGiving2015_Cranberry_Stc[5]["EventData"]
	local nTypeData_5 = tThanksGiving2015_Cranberry_Stc[5]["TypeData"]
	if Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0) then
		ThanksGiving2015_Cranberry_TaskEnd()
		return
	end
	
	local nSecs = tThanksGiving2015_Cranberry_Explore[nMethod]["Secs"]
	local sContent = tThanksGiving2015_Cranberry_Text["Explore"][nMethod]
	local nActionId = tThanksGiving2015_Cranberry_Explore[nMethod]["ActionId"]
	local sFunc = string.format("ThanksGiving2015_Cranberry_TaskExplore</N>%d</N>%d",nNpcId,nMethod)
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end

---------------------------------系统自检函数-------------------------------------------
-- 自检限制清除
function ThanksGiving2015_Cranberry_ResetLimit()
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_203Time"]) then
		return
	end
	
	Sys_SetSynaGlobalData5(tThanksGiving2015_Cranberry_Data["GlobalId"],0)
end


-- 动态存储表重置
function ThanksGiving2015_Cranberry_ResetGlobal()
	-- 活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_203Time"]) then
		return
	end
	
	local nGlobalId = tThanksGiving2015_Cranberry_Data["GlobalId"] 
	local nData_5 = Get_SysDynaGlobalData(nGlobalId,5)
	-- 重置限制判断
	if nData_5 ~= 0 then
		return
	end

	-- 取目前成绩数据
	local nData_0 = Get_SysDynaGlobalData(nGlobalId,0)		--目前冠军成绩
	local nData_1 = Get_SysDynaGlobalData(nGlobalId,1)		--目前冠军ID
	local sData_1 = Get_SysDynaGlobalDataStr(nGlobalId,1)	--目前冠军名字
	
	-- 记录昨天成绩数据
	Sys_SetSynaGlobalData2(nGlobalId,nData_0)				--昨天冠军成绩
	Sys_SetSynaGlobalData3(nGlobalId,nData_1)				--昨天冠军ID
	Sys_SetSynaGlobalDataStr3(nGlobalId,sData_1)			--昨天冠军名字
	
	-- 重置目前存储表
	Sys_SetSynaGlobalData0(nGlobalId,0)
	Sys_SetSynaGlobalData1(nGlobalId,0)
	Sys_SetSynaGlobalDataStr1(nGlobalId,"")
	
	-- 昨天冠军领奖重置
	Sys_SetSynaGlobalData4(nGlobalId,0)
	
	-- 自检限制
	Sys_SetSynaGlobalData5(nGlobalId,1)
end


---------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[3241] = 165
---------------------NPC对白
-- 【小莓姑娘】
tNpcGossip[17176] = tNpcGossip[17176] or DefaultNpc:new{}
tNpcGossip[17176]["OptionHidden"] = 1

-- 活动前
tNpcGossip[17176]["Text1-1"] = {111,112,113}
tNpcGossip[17176]["tOption1-1"] = {111}
tNpcGossip[17176]["Text111"] = tThanksGiving2015_Cranberry_Text[17176]["Text111"]
tNpcGossip[17176]["Text112"] = tThanksGiving2015_Cranberry_Text[17176]["Text112"]
tNpcGossip[17176]["Text113"] = tThanksGiving2015_Cranberry_Text[17176]["Text113"]
tNpcGossip[17176]["Option111"] = tThanksGiving2015_Cranberry_Text[17176]["Option111"]
tNpcGossip[17176]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_BefTime"])
end

-- 活动后
tNpcGossip[17176]["Text1-2"] = {121,122}
tNpcGossip[17176]["tOption1-2"] = {121,122}
tNpcGossip[17176]["Text121"] = tThanksGiving2015_Cranberry_Text[17176]["Text121"]
tNpcGossip[17176]["Text122"] = tThanksGiving2015_Cranberry_Text[17176]["Text122"]
tNpcGossip[17176]["Option121"] = tThanksGiving2015_Cranberry_Text[17176]["Option121"]
tNpcGossip[17176]["Option122"] = tThanksGiving2015_Cranberry_Text[17176]["Option122"]
tNpcGossip[17176]["OptionFunc121"] = "ThanksGiving2015_Cranberry_YdayReward</N>17176"
tNpcGossip[17176]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_NowTime"])
end
tNpcGossip[17176]["OptionChkFunc121"] = function ()
	return Sys_ChkFullTime(tThanksGiving2015_Cranberry_Data["Festival_AftTime"])
end

-- 活动中
tNpcGossip[17176]["Text1-3"] = {131,132,133,134,135}
tNpcGossip[17176]["tOption1-3"] = {131,132,133,134,135,136}
tNpcGossip[17176]["Text131"] = tThanksGiving2015_Cranberry_Text[17176]["Text131"]
tNpcGossip[17176]["Text132"] = tThanksGiving2015_Cranberry_Text[17176]["Text132"]
tNpcGossip[17176]["Text133"] = tThanksGiving2015_Cranberry_Text[17176]["Text133"]
tNpcGossip[17176]["Text134"] = tThanksGiving2015_Cranberry_Text[17176]["Text134"]
tNpcGossip[17176]["Text135"] = tThanksGiving2015_Cranberry_Text[17176]["Text135"]
tNpcGossip[17176]["Option131"] = tThanksGiving2015_Cranberry_Text[17176]["Option131"]
tNpcGossip[17176]["Option132"] = tThanksGiving2015_Cranberry_Text[17176]["Option132"]
tNpcGossip[17176]["Option133"] = tThanksGiving2015_Cranberry_Text[17176]["Option133"]
tNpcGossip[17176]["Option134"] = tThanksGiving2015_Cranberry_Text[17176]["Option134"]
tNpcGossip[17176]["Option135"] = tThanksGiving2015_Cranberry_Text[17176]["Option135"]
tNpcGossip[17176]["Option136"] = tThanksGiving2015_Cranberry_Text[17176]["Option136"]
tNpcGossip[17176]["OptionFunc131"] = "ThanksGiving2015_Cranberry_YdayReward</N>17176"
tNpcGossip[17176]["OptionFunc132"] = "ThanksGiving2015_Cranberry_ChkTime</N>17176</S>1-4"
tNpcGossip[17176]["OptionFunc133"] = "ThanksGiving2015_Cranberry_Rank</N>17176"
tNpcGossip[17176]["OptionFunc134"] = "ThanksGiving2015_Cranberry_Reward</N>17176"
tNpcGossip[17176]["OptionFunc135"] = "ThanksGiving2015_Cranberry_AddReward</N>17176"
tNpcGossip[17176]["OptionChkFunc131"] = function ()
	local nGlobalId = tThanksGiving2015_Cranberry_Data["GlobalId"]
	local nYdayWinner = Get_SysDynaGlobalData(nGlobalId,3)
	local nChkAward = Get_SysDynaGlobalData(nGlobalId,4)
	local nUserId = Get_UserId()
	
	-- 昨天冠军
	if nUserId == nYdayWinner then
		-- 未领奖
		if nChkAward == 0 then
			return true
		end
	end
	
	return false
end


-- 我想了解一下比赛规则
tNpcGossip[17176]["Text1-4"] = {141,142,143,144}
tNpcGossip[17176]["tOption1-4"] = {141,142}
tNpcGossip[17176]["Text141"] = tThanksGiving2015_Cranberry_Text[17176]["Text141"]
tNpcGossip[17176]["Text142"] = tThanksGiving2015_Cranberry_Text[17176]["Text142"]
tNpcGossip[17176]["Text143"] = tThanksGiving2015_Cranberry_Text[17176]["Text143"]
tNpcGossip[17176]["Text144"] = tThanksGiving2015_Cranberry_Text[17176]["Text144"]
tNpcGossip[17176]["Option141"] = tThanksGiving2015_Cranberry_Text[17176]["Option141"]
tNpcGossip[17176]["Option142"] = tThanksGiving2015_Cranberry_Text[17176]["Option142"]
tNpcGossip[17176]["OptionFunc141"] = "ThanksGiving2015_Cranberry_ChkTime</N>17176</S>1-5"
tNpcGossip[17176]["OptionPoint142"] = "1"

-- 应该怎么串蔓越橘呢？
tNpcGossip[17176]["Text1-5"] = {151,152,153,154}
tNpcGossip[17176]["tOption1-5"] = {151}
tNpcGossip[17176]["Text151"] = tThanksGiving2015_Cranberry_Text[17176]["Text151"]
tNpcGossip[17176]["Text152"] = tThanksGiving2015_Cranberry_Text[17176]["Text152"]
tNpcGossip[17176]["Text153"] = tThanksGiving2015_Cranberry_Text[17176]["Text153"]
tNpcGossip[17176]["Text154"] = tThanksGiving2015_Cranberry_Text[17176]["Text154"]
tNpcGossip[17176]["Option151"] = tThanksGiving2015_Cranberry_Text[17176]["Option151"]
tNpcGossip[17176]["OptionFunc151"] = "ThanksGiving2015_Cranberry_FindWay</N>17264"


-- 【我来领取奖励】
-- 等级不足
tNpcGossip[17176]["Text2-1"] = {211}
tNpcGossip[17176]["tOption2-1"] = {211}
tNpcGossip[17176]["Text211"] = tThanksGiving2015_Cranberry_Text[17176]["Text211"]
tNpcGossip[17176]["Option211"] = tThanksGiving2015_Cranberry_Text[17176]["Option211"]

-- 蔓越橘没串15个以上
tNpcGossip[17176]["Text2-2"] = {221}
tNpcGossip[17176]["tOption2-2"] = {221}
tNpcGossip[17176]["Text221"] = tThanksGiving2015_Cranberry_Text[17176]["Text221"]
tNpcGossip[17176]["Option221"] = tThanksGiving2015_Cranberry_Text[17176]["Option221"]

-- 已领取奖励
tNpcGossip[17176]["Text2-3"] = {231}
tNpcGossip[17176]["tOption2-3"] = {231}
tNpcGossip[17176]["Text231"] = tThanksGiving2015_Cranberry_Text[17176]["Text231"]
tNpcGossip[17176]["Option231"] = tThanksGiving2015_Cranberry_Text[17176]["Option231"]

-- 背包空间
tNpcGossip[17176]["Text2-4"] = {241}
tNpcGossip[17176]["tOption2-4"] = {241}
tNpcGossip[17176]["Text241"] = tThanksGiving2015_Cranberry_Text[17176]["Text241"]
tNpcGossip[17176]["Option241"] = tThanksGiving2015_Cranberry_Text[17176]["Option241"]

-- 获得节日礼包
tNpcGossip[17176]["Text2-5"] = {251}
tNpcGossip[17176]["tOption2-5"] = {251}
tNpcGossip[17176]["Text251"] = tThanksGiving2015_Cranberry_Text[17176]["Text251"]
tNpcGossip[17176]["Option251"] = tThanksGiving2015_Cranberry_Text[17176]["Option251"]

-- 额外奖励（数量不够）
tNpcGossip[17176]["Text2-6"] = {261}
tNpcGossip[17176]["tOption2-6"] = {261}
tNpcGossip[17176]["Text261"] = tThanksGiving2015_Cranberry_Text[17176]["Text261"]
tNpcGossip[17176]["Option261"] = tThanksGiving2015_Cranberry_Text[17176]["Option261"]

-- 额外奖励（已领取奖励）
tNpcGossip[17176]["Text2-7"] = {271}
tNpcGossip[17176]["tOption2-7"] = {271}
tNpcGossip[17176]["Text271"] = tThanksGiving2015_Cranberry_Text[17176]["Text271"]
tNpcGossip[17176]["Option271"] = tThanksGiving2015_Cranberry_Text[17176]["Option271"]


-- 额外奖励（经验）
tNpcGossip[17176]["Text2-8"] = {281,282}
tNpcGossip[17176]["tOption2-8"] = {281}
tNpcGossip[17176]["Text281"] = tThanksGiving2015_Cranberry_Text[17176]["Text281"]
tNpcGossip[17176]["Text282"] = tThanksGiving2015_Cranberry_Text[17176]["Text282"]
tNpcGossip[17176]["Option281"] = tThanksGiving2015_Cranberry_Text[17176]["Option281"]

-- 额外奖励（修行值）
tNpcGossip[17176]["Text2-9"] = {291,292}
tNpcGossip[17176]["tOption2-9"] = {291}
tNpcGossip[17176]["Text291"] = tThanksGiving2015_Cranberry_Text[17176]["Text291"]
tNpcGossip[17176]["Text292"] = tThanksGiving2015_Cranberry_Text[17176]["Text292"]
tNpcGossip[17176]["Option291"] = tThanksGiving2015_Cranberry_Text[17176]["Option291"]


-- 【查看排行榜】
-- 第一名（第一天）
tNpcGossip[17176]["Text3-1"] = {311}
tNpcGossip[17176]["tOption3-1"] = {311}
tNpcGossip[17176]["Text311"] = tThanksGiving2015_Cranberry_Text[17176]["Text311"]
tNpcGossip[17176]["Option311"] = tThanksGiving2015_Cranberry_Text[17176]["Option311"]

-- 第一名（非第一天）
tNpcGossip[17176]["Text3-2"] = {321}
tNpcGossip[17176]["tOption3-2"] = {321}
tNpcGossip[17176]["Text321"] = tThanksGiving2015_Cranberry_Text[17176]["Text321"]
tNpcGossip[17176]["Option321"] = tThanksGiving2015_Cranberry_Text[17176]["Option321"]
tNpcGossip[17176]["OptionFunc321"] = "ThanksGiving2015_Cranberry_YdayReward</N>17176"

-- 今天未参加比赛
tNpcGossip[17176]["Text3-3"] = {331}
tNpcGossip[17176]["tOption3-3"] = {331}
tNpcGossip[17176]["Text331"] = tThanksGiving2015_Cranberry_Text[17176]["Text331"]
tNpcGossip[17176]["Option331"] = tThanksGiving2015_Cranberry_Text[17176]["Option331"]

-- 非第一名（第一天）
tNpcGossip[17176]["Text3-4"] = {341,342}
tNpcGossip[17176]["tOption3-4"] = {341}
tNpcGossip[17176]["Text341"] = tThanksGiving2015_Cranberry_Text[17176]["Text341"]
tNpcGossip[17176]["Text342"] = tThanksGiving2015_Cranberry_Text[17176]["Text342"]
tNpcGossip[17176]["Option341"] = tThanksGiving2015_Cranberry_Text[17176]["Option341"]

-- 非第一名（非第一天）
tNpcGossip[17176]["Text3-5"] = {351,352}
tNpcGossip[17176]["tOption3-5"] = {351,352}
tNpcGossip[17176]["Text351"] = tThanksGiving2015_Cranberry_Text[17176]["Text351"]
tNpcGossip[17176]["Text352"] = tThanksGiving2015_Cranberry_Text[17176]["Text352"]
tNpcGossip[17176]["Option351"] = tThanksGiving2015_Cranberry_Text[17176]["Option351"]
tNpcGossip[17176]["Option352"] = tThanksGiving2015_Cranberry_Text[17176]["Option352"]
tNpcGossip[17176]["OptionFunc351"] = "ThanksGiving2015_Cranberry_YdayReward</N>17176"

-- 【领取昨天冠军奖励】
-- 不是昨天冠军
tNpcGossip[17176]["Text4-1"] = {411}
tNpcGossip[17176]["tOption4-1"] = {411}
tNpcGossip[17176]["Text411"] = tThanksGiving2015_Cranberry_Text[17176]["Text411"]
tNpcGossip[17176]["Option411"] = tThanksGiving2015_Cranberry_Text[17176]["Option411"]

-- 已领过奖励
tNpcGossip[17176]["Text4-2"] = {421}
tNpcGossip[17176]["tOption4-2"] = {421}
tNpcGossip[17176]["Text421"] = tThanksGiving2015_Cranberry_Text[17176]["Text421"]
tNpcGossip[17176]["Option421"] = tThanksGiving2015_Cranberry_Text[17176]["Option421"]

-- 背包空间
tNpcGossip[17176]["Text4-3"] = {431}
tNpcGossip[17176]["tOption4-3"] = {431}
tNpcGossip[17176]["Text431"] = tThanksGiving2015_Cranberry_Text[17176]["Text431"]
tNpcGossip[17176]["Option431"] = tThanksGiving2015_Cranberry_Text[17176]["Option431"]

-- 获得昨天冠军奖励
tNpcGossip[17176]["Text4-4"] = {441}
tNpcGossip[17176]["tOption4-4"] = {441}
tNpcGossip[17176]["Text441"] = tThanksGiving2015_Cranberry_Text[17176]["Text441"]
tNpcGossip[17176]["Option441"] = tThanksGiving2015_Cranberry_Text[17176]["Option441"]

-- 不存在昨天冠军
tNpcGossip[17176]["Text4-5"] = {451}
tNpcGossip[17176]["tOption4-5"] = {451}
tNpcGossip[17176]["Text451"] = tThanksGiving2015_Cranberry_Text[17176]["Text451"]
tNpcGossip[17176]["Option451"] = tThanksGiving2015_Cranberry_Text[17176]["Option451"]






------------------------------------------------------------------------------------
-- 【小果盆】
tNpcGossip[17177] = tNpcGossip[17177] or DefaultNpc:new{}
tNpcGossip[17264] = tNpcGossip[17177] or DefaultNpc:new{}
tNpcGossip[17177]["OptionHidden"] = 1

-- 等级不足
tNpcGossip[17177]["Text1-1"] = {111}
tNpcGossip[17177]["tOption1-1"] = {111}
tNpcGossip[17177]["Text111"] = tThanksGiving2015_Cranberry_Text[17177]["Text111"]
tNpcGossip[17177]["Option111"] = tThanksGiving2015_Cranberry_Text[17177]["Option111"]

-- 活动外
tNpcGossip[17177]["Text1-2"] = {121}
tNpcGossip[17177]["tOption1-2"] = {121}
tNpcGossip[17177]["Text121"] = tThanksGiving2015_Cranberry_Text[17177]["Text121"]
tNpcGossip[17177]["Option121"] = tThanksGiving2015_Cranberry_Text[17177]["Option121"]

-- 活动中对白
tNpcGossip[17177]["Text1-3"] = {131}
tNpcGossip[17177]["tOption1-3"] = {131,132,133}
tNpcGossip[17177]["Text131"] = tThanksGiving2015_Cranberry_Text[17177]["Text131"]
tNpcGossip[17177]["Option131"] = tThanksGiving2015_Cranberry_Text[17177]["Option131"]
tNpcGossip[17177]["Option132"] = tThanksGiving2015_Cranberry_Text[17177]["Option132"]
tNpcGossip[17177]["Option133"] = tThanksGiving2015_Cranberry_Text[17177]["Option133"]
tNpcGossip[17177]["OptionFunc131"] = "ThanksGiving2015_Cranberry_ChkTime</N>17177</S>1-4"
tNpcGossip[17177]["OptionFunc132"] = "ThanksGiving2015_Cranberry_TaskBegin</N>17177"


-- 规则是什么样的呢？
tNpcGossip[17177]["Text1-4"] = {141,142,143}
tNpcGossip[17177]["tOption1-4"] = {141,142}
tNpcGossip[17177]["Text141"] = tThanksGiving2015_Cranberry_Text[17177]["Text141"]
tNpcGossip[17177]["Text142"] = tThanksGiving2015_Cranberry_Text[17177]["Text142"]
tNpcGossip[17177]["Text143"] = tThanksGiving2015_Cranberry_Text[17177]["Text143"]
tNpcGossip[17177]["Option141"] = tThanksGiving2015_Cranberry_Text[17177]["Option141"]
tNpcGossip[17177]["Option142"] = tThanksGiving2015_Cranberry_Text[17177]["Option142"]
tNpcGossip[17177]["OptionFunc141"] = "ThanksGiving2015_Cranberry_ChkTime</N>17177</S>1-5"
tNpcGossip[17177]["OptionFunc142"] = "ThanksGiving2015_Cranberry_ChkTime</N>17177</S>1-3"


-- 应该怎么串蔓越橘呢？
tNpcGossip[17177]["Text1-5"] = {151,152,153,154}
tNpcGossip[17177]["tOption1-5"] = {151}
tNpcGossip[17177]["Text151"] = tThanksGiving2015_Cranberry_Text[17177]["Text151"]
tNpcGossip[17177]["Text152"] = tThanksGiving2015_Cranberry_Text[17177]["Text152"]
tNpcGossip[17177]["Text153"] = tThanksGiving2015_Cranberry_Text[17177]["Text153"]
tNpcGossip[17177]["Text154"] = tThanksGiving2015_Cranberry_Text[17177]["Text154"]
tNpcGossip[17177]["Option151"] = tThanksGiving2015_Cranberry_Text[17177]["Option151"]
tNpcGossip[17177]["OptionFunc151"] = "ThanksGiving2015_Cranberry_TaskBegin</N>17177"

-- 第一次串
tNpcGossip[17177]["Text1-6"] = {161,162,163}
tNpcGossip[17177]["tOption1-6"] = {161,162,163}
tNpcGossip[17177]["Text161"] = tThanksGiving2015_Cranberry_Text[17177]["Text161"]
tNpcGossip[17177]["Text162"] = tThanksGiving2015_Cranberry_Text[17177]["Text162"]
tNpcGossip[17177]["Text163"] = tThanksGiving2015_Cranberry_Text[17177]["Text163"]
tNpcGossip[17177]["Option161"] = tThanksGiving2015_Cranberry_Text[17177]["Option161"]
tNpcGossip[17177]["Option162"] = tThanksGiving2015_Cranberry_Text[17177]["Option162"]
tNpcGossip[17177]["Option163"] = tThanksGiving2015_Cranberry_Text[17177]["Option163"]
tNpcGossip[17177]["OptionFunc161"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>1"
tNpcGossip[17177]["OptionFunc162"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>2"
tNpcGossip[17177]["OptionFunc163"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>3"


-- 第二次以后串
tNpcGossip[17177]["Text1-7"] = {171,172,173}
tNpcGossip[17177]["tOption1-7"] = {171,172,173}
tNpcGossip[17177]["Text171"] = tThanksGiving2015_Cranberry_Text[17177]["Text171"]
tNpcGossip[17177]["Option171"] = tThanksGiving2015_Cranberry_Text[17177]["Option171"]
tNpcGossip[17177]["Option172"] = tThanksGiving2015_Cranberry_Text[17177]["Option172"]
tNpcGossip[17177]["Option173"] = tThanksGiving2015_Cranberry_Text[17177]["Option173"]
tNpcGossip[17177]["OptionFunc171"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>1"
tNpcGossip[17177]["OptionFunc172"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>2"
tNpcGossip[17177]["OptionFunc173"] = "ThanksGiving2015_Cranberry_TaskOption</N>17177</N>3"

------------------------------------------配置数据------------------------------------------
--时间函数触发
--'00:00 00:03'
tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
table.insert(tOntimerMin_HM[0000],ThanksGiving2015_Cranberry_ResetGlobal)
tOntimerMin_HM[0001] = tOntimerMin_HM[0001] or {}
table.insert(tOntimerMin_HM[0001],ThanksGiving2015_Cranberry_ResetGlobal)
tOntimerMin_HM[0002] = tOntimerMin_HM[0002] or {}
table.insert(tOntimerMin_HM[0002],ThanksGiving2015_Cranberry_ResetLimit)
tOntimerMin_HM[0003] = tOntimerMin_HM[0003] or {}
table.insert(tOntimerMin_HM[0003],ThanksGiving2015_Cranberry_ResetLimit)

