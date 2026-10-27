------------------------------------------------------------------------------------
--Name:			150616[简体征服][活动脚本]感恩节（11.24-11.30）-猩猩投果子
--Purpose:		感恩节（11.24-11.30）-猩猩投果子
--Creator:		黄昕哲
--Created:		2015/03/16
------------------------------------------------------------------------------------
--前缀ThanksGiving2015_ThrowFruit_
--npcid:阿土伯17195
--大饭桌17196/17265
--小澡盆17197/17266
--小炉子17198/17267
--小花瓶17199/17268

--[[
stc(129,83) 用于记录当前玩家的分数
stc(129,84) 用于记录当天玩家的最高分数

stc(129,85) 用于记录当天玩家参加活动的达到10分的奖励
	= 0 表示未获得奖励
	= 1 表示获得奖励
stc(129,86) 用于记录当天玩家参加活动的达到20分的额外奖励
	= 0 表示未获得奖励
	= 1 表示获得奖励
]]--
---------------------------------table定义--------------------------------------
local tThanksGiving2015_ThrowFruit_Data = {}
--活动时间
	tThanksGiving2015_ThrowFruit_Data["Time"] = {}
	tThanksGiving2015_ThrowFruit_Data["Time"]["Before"] = "2015-01-01 00:00 2015-11-23 23:59"
	tThanksGiving2015_ThrowFruit_Data["Time"]["During"] = "2015-11-24 00:00 2015-11-30 23:59"
	--用于领取前一天奖励的时间,比活动时间延后一天
	tThanksGiving2015_ThrowFruit_Data["Time"]["Delay"] = "2015-11-25 00:00 2015-12-01 23:59"
	tThanksGiving2015_ThrowFruit_Data["Time"]["DayTime"] = "00:00 00:00"
--限制
	tThanksGiving2015_ThrowFruit_Data["Lev"] = 80
	tThanksGiving2015_ThrowFruit_Data["MaxLev"] = 140
	tThanksGiving2015_ThrowFruit_Data["Metempsychosis"] = 0
--变形相关
tThanksGiving2015_ThrowFruit_Data["Transform"] = {}
	tThanksGiving2015_ThrowFruit_Data["Transform"]["Gorilla"] = 356
	tThanksGiving2015_ThrowFruit_Data["Transform"]["MagicType"] = 11930
	tThanksGiving2015_ThrowFruit_Data["Transform"]["MagicLevel"] = 0
	tThanksGiving2015_ThrowFruit_Data["Transform"]["Monster_Type"] = 31
	tThanksGiving2015_ThrowFruit_Data["Transform"]["TimeLimit"] = 60
	
--领奖需求分数,根据论坛反馈改动为15/25
tThanksGiving2015_ThrowFruit_Data["Point"] = {}
	tThanksGiving2015_ThrowFruit_Data["Point"]["Pass"] = 10
	tThanksGiving2015_ThrowFruit_Data["Point"]["Extra"] = 20
--光效
tThanksGiving2015_ThrowFruit_Data["Effect"] = {}
	tThanksGiving2015_ThrowFruit_Data["Effect"]["Top1"] = "zf2-e300"
	tThanksGiving2015_ThrowFruit_Data["Effect"]["BounceAndGoal"] = "superxp2"
	tThanksGiving2015_ThrowFruit_Data["Effect"]["Fall"] = "BodyDisapear"
	tThanksGiving2015_ThrowFruit_Data["Effect"]["Twist"] = "lounder"
--失血百分比
tThanksGiving2015_ThrowFruit_Data["DecLifePec"] = 20
--奖励
tThanksGiving2015_ThrowFruit_Data["Reward"] = {}
tThanksGiving2015_ThrowFruit_Data["Reward"]["Exp"] = 60
tThanksGiving2015_ThrowFruit_Data["Reward"]["Cult"] = 50
--投掷结果
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"] = {}
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Goal"] = 1
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["BounceAndGoal"] = 2
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["BounceAndOut"] = 3
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Out"] = 4
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Fall"] = 5
tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Twist"] = 6

--全局表
--data0,data1,datastr1表示今天最高分,最高分id,最高分姓名
--data2,data3,datastr3,data4表示昨日最高分,最高分id,最高分姓名,是否已经领取过奖励
tThanksGiving2015_ThrowFruit_Data["GlobalData"] = 50659
--数量
tThanksGiving2015_ThrowFruit_Data["Num"] = {}
tThanksGiving2015_ThrowFruit_Data["Num"]["GetFruit"] = 10

--眩晕状态nStatus,nPower,nSecs,nTimes,nunRemainTime,nunEndTime,nucRecordable
local tThanksGiving2015_ThrowFruit_Status = {}
tThanksGiving2015_ThrowFruit_Status["Status"] = 55
tThanksGiving2015_ThrowFruit_Status["Power"] = 200
tThanksGiving2015_ThrowFruit_Status["Remain1"] = 1
tThanksGiving2015_ThrowFruit_Status["Remain2"] = 2
tThanksGiving2015_ThrowFruit_Status["Times"] = 1
tThanksGiving2015_ThrowFruit_Status["EndTime"] = 1
tThanksGiving2015_ThrowFruit_Status["Recordable"] = 1

--log
local tThanksGiving2015_ThrowFruit_Log = {}
tThanksGiving2015_ThrowFruit_Log["Id"] = 10002339
tThanksGiving2015_ThrowFruit_Log["Transform"] = "0,0,0,0,10002339,1,0,0"
tThanksGiving2015_ThrowFruit_Log["GetExp"] = "0,0,0,0,10002339,2,4,60"
tThanksGiving2015_ThrowFruit_Log["GetCult"] = "0,0,0,0,10002339,2,6,50"
tThanksGiving2015_ThrowFruit_Log["GetFruit"] = "0,0,0,0,10002339,2,3004881,1"
tThanksGiving2015_ThrowFruit_Log["GetTop1"] = "0,0,0,0,10002339,3,1088000,1"
--掩码
local tThanksGiving2015_ThrowFruit_Stc = {}
--当前获得分数
tThanksGiving2015_ThrowFruit_Stc["Point"] = {}
tThanksGiving2015_ThrowFruit_Stc["Point"]["EventType"] = 129
tThanksGiving2015_ThrowFruit_Stc["Point"]["DataType"] = 83
--今日最高分数
tThanksGiving2015_ThrowFruit_Stc["TodayTop"] = {}
tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["EventType"] = 129
tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["DataType"] = 84
--今天是否领取过奖励
tThanksGiving2015_ThrowFruit_Stc["TodayReward"] = {}
tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["EventType"] = 129
tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["DataType"] = 85
tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["Before"] = 0
tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["After"] = 1
--今天是否领取过额外奖励
tThanksGiving2015_ThrowFruit_Stc["TodayExtra"] = {}
tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["EventType"] = 129
tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["DataType"] = 86
tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["Before"] = 0
tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["After"] = 1

--坐标
local tThanksGiving2015_ThrowFruit_Pos = {}
	tThanksGiving2015_ThrowFruit_Pos["MapId"] = 1002
	tThanksGiving2015_ThrowFruit_Pos["MinCellX"] = 270
	tThanksGiving2015_ThrowFruit_Pos["MaxCellX"] = 385
	tThanksGiving2015_ThrowFruit_Pos["MinCellY"] = 357
	tThanksGiving2015_ThrowFruit_Pos["MaxCellY"] = 387
	tThanksGiving2015_ThrowFruit_Pos[17195] = {}
	tThanksGiving2015_ThrowFruit_Pos[17195]["CellX"] = 282
	tThanksGiving2015_ThrowFruit_Pos[17195]["CellY"] = 360
	tThanksGiving2015_ThrowFruit_Pos[17265] = {}
	tThanksGiving2015_ThrowFruit_Pos[17265]["CellX"] = 285
	tThanksGiving2015_ThrowFruit_Pos[17265]["CellY"] = 360
	tThanksGiving2015_ThrowFruit_Pos[17266] = {}
	tThanksGiving2015_ThrowFruit_Pos[17266]["CellX"] = 275
	tThanksGiving2015_ThrowFruit_Pos[17266]["CellY"] = 350
	tThanksGiving2015_ThrowFruit_Pos[17267] = {}
	tThanksGiving2015_ThrowFruit_Pos[17267]["CellX"] = 280
	tThanksGiving2015_ThrowFruit_Pos[17267]["CellY"] = 350
	tThanksGiving2015_ThrowFruit_Pos[17268] = {}
	tThanksGiving2015_ThrowFruit_Pos[17268]["CellX"] = 285
	tThanksGiving2015_ThrowFruit_Pos[17268]["CellY"] = 350
	
--概率
local tThanksGiving2015_ThrowFruit_Rate = {}
	tThanksGiving2015_ThrowFruit_Rate["Persent"] = 10000
	tThanksGiving2015_ThrowFruit_Rate[1] = {}
		tThanksGiving2015_ThrowFruit_Rate[1]["Goal"] = 7000
		tThanksGiving2015_ThrowFruit_Rate[1]["BounceAndGoal"] = 2000
		tThanksGiving2015_ThrowFruit_Rate[1]["BounceAndOut"] = 1000
		tThanksGiving2015_ThrowFruit_Rate[1]["Out"] = 0
		tThanksGiving2015_ThrowFruit_Rate[1]["Fall"] = 0
		tThanksGiving2015_ThrowFruit_Rate[1]["Twist"] = 0
	tThanksGiving2015_ThrowFruit_Rate[2] = {}
		tThanksGiving2015_ThrowFruit_Rate[2]["Goal"] = 4000
		tThanksGiving2015_ThrowFruit_Rate[2]["BounceAndGoal"] = 1000
		tThanksGiving2015_ThrowFruit_Rate[2]["BounceAndOut"] = 1000
		tThanksGiving2015_ThrowFruit_Rate[2]["Out"] = 2500
		tThanksGiving2015_ThrowFruit_Rate[2]["Fall"] = 1000
		tThanksGiving2015_ThrowFruit_Rate[2]["Twist"] = 500
	tThanksGiving2015_ThrowFruit_Rate[3] = {}
		tThanksGiving2015_ThrowFruit_Rate[3]["Goal"] = 3000
		tThanksGiving2015_ThrowFruit_Rate[3]["BounceAndGoal"] = 500
		tThanksGiving2015_ThrowFruit_Rate[3]["BounceAndOut"] = 500
		tThanksGiving2015_ThrowFruit_Rate[3]["Out"] = 3500
		tThanksGiving2015_ThrowFruit_Rate[3]["Fall"] = 1500
		tThanksGiving2015_ThrowFruit_Rate[3]["Twist"] = 1000

--id
local tThanksGiving2015_ThrowFruit_Id = {}
	tThanksGiving2015_ThrowFruit_Id["Festival"] = 3330
	tThanksGiving2015_ThrowFruit_Id["Item"] = {}
	tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"] = 3004881
	tThanksGiving2015_ThrowFruit_Id["Item"]["Top1Reward"] = 1088000

---------------------------------逻辑定义--------------------------------------
--203w
function ThanksGiving2015_ThrowFruit_SysChk()
	--每天隔天时执行一次,设置dynadata50659,将昨天的数据搬到data2-3.data0,1,4重置为0
	if not Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["Delay"]) then
		return
	end
	local nTop1DataId = tThanksGiving2015_ThrowFruit_Data["GlobalData"]
	if Sys_ChkDayTime(tThanksGiving2015_ThrowFruit_Data["Time"]["DayTime"]) then
		Sys_SetSynaGlobalData2(nTop1DataId,Get_SysDynaGlobalData0(nTop1DataId))
		Sys_SetSynaGlobalData3(nTop1DataId,Get_SysDynaGlobalData1(nTop1DataId))
		Sys_SetSynaGlobalDataStr3(nTop1DataId,Get_SysDynaGlobalDataStr1(nTop1DataId))
		Sys_SetSynaGlobalData0(nTop1DataId,0)
		Sys_SetSynaGlobalData1(nTop1DataId,0)
		Sys_SetSynaGlobalDataStr1(nTop1DataId,"")
		Sys_SetSynaGlobalData4(nTop1DataId,0)
	end
end

--玩家隔天接任务前重置掩码
function ThanksGiving2015_ThrowFruit_ResetPlayer()
	--个人掩码隔天判断
	local nPointEvent = tThanksGiving2015_ThrowFruit_Stc["Point"]["EventType"]
	local nPointType = tThanksGiving2015_ThrowFruit_Stc["Point"]["DataType"]
	local nTodayTopEvent = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["EventType"]
	local nTodayTopType = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["DataType"]
	local nTodayRewardEvent = tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["EventType"]
	local nTodayRewardType = tThanksGiving2015_ThrowFruit_Stc["TodayReward"]["DataType"]
	local nTodayExtraEvent = tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["EventType"]
	local nTodayExtraType = tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["DataType"]
	if Task_StcInterval(nTodayTopEvent,nTodayTopType,1,4) then
		Task_SetStatistic(nPointEvent,nPointType,0,1,0)
		Task_SetStcTimestamp(nPointEvent,nPointType,0)
		Task_SetStatistic(nTodayTopEvent,nTodayTopType,0,1,0)
		Task_SetStcTimestamp(nTodayTopEvent,nTodayTopType,0)
		Task_SetStatistic(nTodayRewardEvent,nTodayRewardType,0,1,0)
		Task_SetStcTimestamp(nTodayRewardEvent,nTodayRewardType,0)
		Task_SetStatistic(nTodayExtraEvent,nTodayExtraType,0,1,0)
		Task_SetStcTimestamp(nTodayExtraEvent,nTodayExtraType,0)
	end
end


--判断是否在活动期间以及玩家变身状态是否为猩猩,参数nJudgeType不写的情况下不判断变形,返回true表活动中且变形正确
function ThanksGiving2015_ThrowFruit_Chk(nJudgeType)
	if not Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["During"]) then
		--活动过期
		return false
	end
	local sTrans = Get_UserTransformId()
	if nil ~= nJudgeType then
		if Get_UserTransformId() ~= tThanksGiving2015_ThrowFruit_Data["Transform"]["Gorilla"] then
			--未变形
			return false
		end
	end
	return true
end

--查看掩码
function ThanksGiving2015_ThrowFruit_ReadStc(sStcType)
	local nEvent = tThanksGiving2015_ThrowFruit_Stc[sStcType]["EventType"]
	local nType = tThanksGiving2015_ThrowFruit_Stc[sStcType]["DataType"]
	return Get_UserStatisticValue(nEvent,nType)
end

--写入掩码
function ThanksGiving2015_ThrowFruit_WriteStc(sStcType,nData)
	local nEvent = tThanksGiving2015_ThrowFruit_Stc[sStcType]["EventType"]
	local nType = tThanksGiving2015_ThrowFruit_Stc[sStcType]["DataType"]
	Task_SetStatistic(nEvent,nType,nData,1,0)
end

--参加活动
function ThanksGiving2015_ThrowFruit_JoinAct(nNpcId)
	if not ThanksGiving2015_ThrowFruit_Chk() then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	if not User_JudgeLevelAndMetempsychosis(tThanksGiving2015_ThrowFruit_Data["Lev"],tThanksGiving2015_ThrowFruit_Data["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	LinkNpcGossipFunc_New(nNpcId,"2-2")
end

--检测玩家是否满足任务要求条件
function ThanksGiving2015_ThrowFruit_JudgeUser(nNpcId)
	if ThanksGiving2015_ThrowFruit_Chk(1) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	--删除往年或今年的小青果
	local nFruitId = tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]
	if Item_ChkItem(nFruitId) then
		Item_DelAllItemByType(nFruitId)
	end
	--变身,重置当前分数,延时60秒进行变身结束结算,聊天框提示,log,对话
	local nSkill = tThanksGiving2015_ThrowFruit_Data["Transform"]["MagicType"]
	local nSkillType = tThanksGiving2015_ThrowFruit_Data["Transform"]["MagicLevel"]
	local nMonsterType = tThanksGiving2015_ThrowFruit_Data["Transform"]["Monster_Type"]
	local nTime = tThanksGiving2015_ThrowFruit_Data["Transform"]["TimeLimit"]
	User_TransForm(nSkill,nSkillType,nMonsterType,nTime)
	ThanksGiving2015_ThrowFruit_WriteStc("Point",0)
	--已有变身的倒计时,此处倒计时的时间不显示
	User_SetTimer(nTime,"ThanksGiving2015_ThrowFruit_TransEnd</N>" .. nNpcId,0)
	Sys_SaveActionFestivalLog(tThanksGiving2015_ThrowFruit_Log["Transform"])
	User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text['TalkChannel1'])
end

--变身结束--结算今日分数,今日最高分数比较
function ThanksGiving2015_ThrowFruit_TransEnd()
	local nPoint = ThanksGiving2015_ThrowFruit_ReadStc("Point")
	local nTodayTopEvent = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["EventType"]
	local nTodayTopType = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["DataType"]
	local nTodayTop = ThanksGiving2015_ThrowFruit_ReadStc("TodayTop")
	nTodayTop = math.max(nPoint,nTodayTop)
	ThanksGiving2015_ThrowFruit_WriteStc("TodayTop",nTodayTop)
	Task_SetStcTimestamp(nTodayTopEvent,nTodayTopType,0)
	local nDynaDataId = tThanksGiving2015_ThrowFruit_Data["GlobalData"]
	--今天最高分
	local nDynaTodayTop = Get_SysDynaGlobalData0(nDynaDataId)
	--玩家今日最高分数比今日全局最高分数更高
	if nDynaTodayTop < nTodayTop then
		--重置今天最高分/最高分id/最高分姓名
		Sys_SetSynaGlobalData0(nDynaDataId,nTodayTop)
		local nUserId = Get_UserId()
		Sys_SetSynaGlobalData1(nDynaDataId,nUserId)
		local sUserName = Get_UserName()
		Sys_SetSynaGlobalDataStr1(nDynaDataId,sUserName)
	end
	if Item_ChkItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
		if Item_DelAllItemByType(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
		end
	end
	if nPoint < tThanksGiving2015_ThrowFruit_Data["Point"]["Pass"] then
		local sLowPointDialog1 = string.format(tThanksGiving2015_ThrowFruit_Text["TransformEnd1"],nPoint)
		User_TalkChannel2005(sLowPointDialog1)
	elseif nPoint < tThanksGiving2015_ThrowFruit_Data["Point"]["Extra"] then
		local sLowPointDialog2 = string.format(tThanksGiving2015_ThrowFruit_Text["TransformEnd2"],nPoint)
		User_TalkChannel2005(sLowPointDialog2)
	else
		local sLowPointDialog3 = string.format(tThanksGiving2015_ThrowFruit_Text["TransformEnd3"],nPoint)
		User_TalkChannel2005(sLowPointDialog3)
	end
end
--领奖
function ThanksGiving2015_ThrowFruit_ApplyReward(nNpcId)
	if not ThanksGiving2015_ThrowFruit_Chk() then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
	end
	local nTodayTop = ThanksGiving2015_ThrowFruit_ReadStc("TodayTop")
	local nTodayReward = ThanksGiving2015_ThrowFruit_ReadStc("TodayReward")
	--检查分数,领奖,背包
	if nTodayTop < tThanksGiving2015_ThrowFruit_Data["Point"]["Pass"] then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	if nTodayReward > 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	--分数足够,未领过奖,背包有空位=>改变掩码,通用礼包,channel,log,对话
	ThanksGiving2015_ThrowFruit_WriteStc("TodayReward",1)
	User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text['TalkChannel2'])
	FestivalGeneralPackage_GetGift(tThanksGiving2015_ThrowFruit_Id["Festival"],tThanksGiving2015_ThrowFruit_Log["Id"])
	LinkNpcGossipFunc_New(nNpcId,"2-6")
end
--领取额外奖励
function ThanksGiving2015_ThrowFruit_ApplyExtra(nNpcId)
	if not ThanksGiving2015_ThrowFruit_Chk() then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	local nTodayTop = ThanksGiving2015_ThrowFruit_ReadStc("TodayTop")
	--分数未满
	if nTodayTop < tThanksGiving2015_ThrowFruit_Data["Point"]["Extra"] then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	local nTodayExtra = ThanksGiving2015_ThrowFruit_ReadStc("TodayExtra")
	--已领过奖
	if not (nTodayExtra == tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["Before"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	ThanksGiving2015_ThrowFruit_WriteStc("TodayExtra",tThanksGiving2015_ThrowFruit_Stc["TodayExtra"]["After"])
	if Get_UserLevel() < tThanksGiving2015_ThrowFruit_Data["MaxLev"] then
		--分数满足,未满级--经验,log
		User_AddExpTime(tThanksGiving2015_ThrowFruit_Data["Reward"]["Exp"])
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text['TalkChannel3'])
		Sys_SaveActionFestivalLog(tThanksGiving2015_ThrowFruit_Log["GetExp"])
		tNpcGossip[17195]["Text431"] = string.format(tThanksGiving2015_ThrowFruit_Text[17195]["Text431"],nTodayTop)
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	else
		--分数满足,满级--修行值,log
		User_AddCultivation(tThanksGiving2015_ThrowFruit_Data["Reward"]["Cult"])
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text['TalkChannel4'])
		Sys_SaveActionFestivalLog(tThanksGiving2015_ThrowFruit_Log["GetCult"])
		tNpcGossip[17195]["Text441"] = string.format(tThanksGiving2015_ThrowFruit_Text[17195]["Text441"],nTodayTop)
		LinkNpcGossipFunc_New(nNpcId,"4-4")
	end
end
--检查玩家是否当天最高分
function ThanksGiving2015_ThrowFruit_ChkTop(nNpcId)
	local nTodayPoint = ThanksGiving2015_ThrowFruit_ReadStc("TodayTop")
	local nTopId = Get_SysDynaGlobalData1(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	local nTopPoint = Get_SysDynaGlobalData0(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	if nTodayPoint == 0 then
		--未参加比赛
		tNpcGossip[17195]["Text531"] = string.format(tThanksGiving2015_ThrowFruit_Text[17195]["Text531"],nTopId,nTopPoint)
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end
	local nUserId = Get_UserId()
	--今天最高分id
	if nUserId == nTopId then
		--第一
		tNpcGossip[17195]["Text511"] = string.format(tThanksGiving2015_ThrowFruit_Text[17195]["Text511"],nTodayPoint)
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	else
		--不是第一,取今天最高分分数
		tNpcGossip[17195]["Text521"] = string.format(tThanksGiving2015_ThrowFruit_Text[17195]["Text521"],nTodayPoint,nTopId,nTopPoint)
		LinkNpcGossipFunc_New(nNpcId,"5-2")
	end
end
--昨天第一名奖励
function ThanksGiving2015_ThrowFruit_Top1Reward(nNpcId)
	--昨天最高分,最高分姓名,最高分id
	local nYDayTop = Get_SysDynaGlobalData3(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	local sYDTopName = Get_SysDynaGlobalDataStr3(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	local nYDTopPoint = Get_SysDynaGlobalData2(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	if nYDTopPoint <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"6-5")
		return
	end
	if nYDayTop ~= Get_UserId() then
		--不是冠军
		tNpcGossip[17195]["Text611"] = string.format(tNpcGossip[17195]["Text611"],sYDTopName,nYDTopPoint)
		LinkNpcGossipFunc_New(nNpcId,"6-1")
		return
	end
	--昨天最高分奖励
	local nYDayReward = Get_SysDynaGlobalData4(tThanksGiving2015_ThrowFruit_Data["GlobalData"])
	if nYDayReward ~= 0 then
		--已领过奖
		LinkNpcGossipFunc_New(nNpcId,"6-2")
		return
	end
	if not User_CheckLeftSpace(1) then
		--背包已满
		LinkNpcGossipFunc_New(nNpcId,"6-3")
		return
	end
	--给奖励 --掩码,物品(龙珠),提示,log,对话
	Sys_SetSynaGlobalData4(tThanksGiving2015_ThrowFruit_Data["GlobalData"],1)
	Item_AddItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Top1Reward"])
	Sys_SaveActionFestivalLog(tThanksGiving2015_ThrowFruit_Log["GetTop1"])
	User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text['TalkChannel5'])
	LinkNpcGossipFunc_New(nNpcId,"6-4")
end
--与大饭桌交谈
function ThanksGiving2015_ThrowFruit_TalkTable(nNpcId)
	if not ThanksGiving2015_ThrowFruit_Chk(1) then
		return
	end
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text["TalkChannel6"])
		return
	end
		--已有果子的情况
	if Item_ChkItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	User_SetExplore(1,tThanksGiving2015_ThrowFruit_Explorer["Choose"],220,"</F>ThanksGiving2015_ThrowFruit_GetFruit</N>" .. nNpcId)
end
--拿果子
function ThanksGiving2015_ThrowFruit_GetFruit(nNpcId)
	--背包已满的情况
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text["TalkChannel6"])
		return
	end
	local nFruitNum = tThanksGiving2015_ThrowFruit_Data["Num"]["GetFruit"]
	Item_AddItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"],0,nFruitNum)
	local sGetFruitDialog = string.format(tThanksGiving2015_ThrowFruit_Text["TalkChannel7"],nFruitNum)
	User_TalkChannel2005(sGetFruitDialog)
end

--丢水果,六个npc都接到此
function ThanksGiving2015_ThrowFruit_Throw(nNpcId)
	--为避免出错,统一将npcid转为同一个
	if nNpcId == 17197 then
		nNpcId = 17266
	elseif nNpcId == 17198 then
		nNpcId = 17267
	elseif nNpcId == 17199 then
		nNpcId = 17268
	end
	--点击选项后,再次判断当前时间和玩家变身状态
	if not ThanksGiving2015_ThrowFruit_Chk(1) then
		return
	end
	if not Item_ChkItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
		Sys_MsgBox(tThanksGiving2015_ThrowFruit_Text["Msg1"])
		return
	end
	if not ThanksGiving2015_ThrowFruit_JudgePos() then
		Sys_MsgBox(tThanksGiving2015_ThrowFruit_Text["Msg2"])
		return
	end
	--条件符合,删除物品,读条,根据概率取结果
	if Item_DelItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
	end
	User_SetExplore(1,tThanksGiving2015_ThrowFruit_Explorer["Throwing"],220,"</F>ThanksGiving2015_ThrowFruit_ThrowFin</N>" .. nNpcId)
end

--位置判断
function ThanksGiving2015_ThrowFruit_JudgePos()
	local nUserX = Get_UserPositionX()
	local nUserY = Get_UserPositionY()
	if (tThanksGiving2015_ThrowFruit_Pos["MinCellX"] <= nUserX and nUserX <= tThanksGiving2015_ThrowFruit_Pos["MaxCellX"]) then
		if (tThanksGiving2015_ThrowFruit_Pos["MinCellY"] <= nUserY and nUserY <= tThanksGiving2015_ThrowFruit_Pos["MaxCellY"]) then
			return true
		end
	end
	return false
end

--投掷结果
function ThanksGiving2015_ThrowFruit_ThrowFin(nNpcId)
	--读条后,再次判断当前时间和玩家变身状态
	if not ThanksGiving2015_ThrowFruit_Chk(1) then
		return
	end
	--nStatus表示投掷结果,并用来取对话,nPoint表示本次投掷所获得的分数,nNowPoint表示当前已获得的分数
	local nStatus = 0
	local nPoint = 0
	if nNpcId == 17266 then
		nPoint = 1
	elseif nNpcId == 17267 then
		nPoint = 2
	else
		nPoint = 3
	end
	local nRate = math.random(tThanksGiving2015_ThrowFruit_Rate["Persent"])
	local nRGoal = tThanksGiving2015_ThrowFruit_Rate[nPoint]["Goal"]
	local nRBGoal = nRGoal + tThanksGiving2015_ThrowFruit_Rate[nPoint]["BounceAndGoal"]
	local nRBOut = nRBGoal + tThanksGiving2015_ThrowFruit_Rate[nPoint]["BounceAndOut"]
	local nROut = nRBOut + tThanksGiving2015_ThrowFruit_Rate[nPoint]["Out"]
	local nRFall = nROut + tThanksGiving2015_ThrowFruit_Rate[nPoint]["Fall"]
	local nNowPoint = ThanksGiving2015_ThrowFruit_ReadStc("Point")
	--进了
	if nRate <= nRGoal then
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Goal"]
		nNowPoint = nNowPoint + nPoint 
	--弹了一下进了
	elseif nRate <= nRBGoal then
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["BounceAndGoal"]
		nNowPoint = nNowPoint + nPoint 
	--弹了一下没进
	elseif nRate <= nRBOut then
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["BounceAndOut"]
	--没进
	elseif nRate <= nROut then
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Out"]
	--摔倒
	elseif nRate <= nRFall then
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Fall"]
	--扭到脚
	else
		nStatus = tThanksGiving2015_ThrowFruit_Data["ThrowEnd"]["Twist"]
	end
	ThanksGiving2015_ThrowFruit_UserProcess(nStatus,nNpcId)
	User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text["TalkChannel" .. nPoint .. nStatus])
	ThanksGiving2015_ThrowFruit_WriteStc("Point",nNowPoint)
	--取出当前玩家分数,用于提示玩家
	ThanksGiving2015_ThrowFruit_ReadStc("Point")
	--假如背包里没有果子了,跳出对白
	if not Item_ChkItem(tThanksGiving2015_ThrowFruit_Id["Item"]["Fruit"]) then
		Sys_MsgBox(tThanksGiving2015_ThrowFruit_Text["Msg1"])
		return
	else
		LinkNpcGossipFunc_New(nNpcId,"1-2")
	end
end
--玩家投掷特效和状态,原函数过长影响阅读所以拖出来写
function ThanksGiving2015_ThrowFruit_UserProcess(nStatus,nNpcId)
	local nCellX = tThanksGiving2015_ThrowFruit_Pos[nNpcId]["CellX"]
	local nCellY = tThanksGiving2015_ThrowFruit_Pos[nNpcId]["CellY"]
	local nSStatus = tThanksGiving2015_ThrowFruit_Status["Status"]
	local nSPower = tThanksGiving2015_ThrowFruit_Status["Power"]
	local nSRemain1 = tThanksGiving2015_ThrowFruit_Status["Remain1"]
	local nSRemain2 = tThanksGiving2015_ThrowFruit_Status["Remain2"]
	local nSTimes = tThanksGiving2015_ThrowFruit_Status["Times"]
	local nSEndTime = tThanksGiving2015_ThrowFruit_Status["EndTime"]
	local nSRecordable = tThanksGiving2015_ThrowFruit_Status["Recordable"]
	local nUserId = Get_UserId()
	--弹了一下进了:分数,结果,npc光效
	if nStatus == 2 then
		Map_Effect(tThanksGiving2015_ThrowFruit_Pos["MapId"],nCellX,nCellY,tThanksGiving2015_ThrowFruit_Data["Effect"]["Fall"],tThanksGiving2015_ThrowFruit_Data["Effect"]["BounceAndGoal"])
	end
	--摔倒 :结果,玩家光效,眩晕2s
	if nStatus == 5 then
		User_EffectAdd("self",tThanksGiving2015_ThrowFruit_Data["Effect"]["Fall"])
		User_AddRoleStatus(nSStatus,nSPower,nSRemain2,nSTimes,nSRemain2,nSEndTime,nSRecordable,0,0,nUserId)
	end
	--扭到脚:结果,玩家光效,眩晕1s,-20%HP
	if nStatus == 6 then
		User_EffectAdd("self",tThanksGiving2015_ThrowFruit_Data["Effect"]["Twist"])
		User_AddRoleStatus(nSStatus,nSPower,nSRemain1,nSTimes,nSRemain1,nSEndTime,nSRecordable,0,0,nUserId)
		User_DecLifePercent(tThanksGiving2015_ThrowFruit_Data["DecLifePec"],1)
	end
end
---------------------------------物品部分--------------------------------------
--3004881小青果
tItem[3004881] = tItem[3004881] or {}
tItem[3004881]["Function"] = function(nItemId,sItemName)
	ThanksGiving2015_ThrowFruit_ItemProc(nItemId)
end

function ThanksGiving2015_ThrowFruit_ItemProc(nItemId)
	if not Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["During"]) then
		--非活动期间
		if Item_ChkItem(nItemId) then 
			if Item_DelItem(nItemId) then
			end
		end
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text["Msg3"])
		return
	end
	--活动期间
	if Get_UserMapId() ~= tThanksGiving2015_ThrowFruit_Pos["MapId"] then
		User_TalkChannel2005(tThanksGiving2015_ThrowFruit_Text["Msg4"])
	else
		local nCellX = tThanksGiving2015_ThrowFruit_Pos[17195]["CellX"]
		local nCellY = tThanksGiving2015_ThrowFruit_Pos[17195]["CellY"]
		local nMapId = tThanksGiving2015_ThrowFruit_Pos["MapId"]
		Sys_GotoSomeWhere(nCellX,nCellY,nMapId)
	end
end


-----------------------------------Npc模板--------------------------------------
--17195阿土伯,lookface= 26420
tNpcFace[2642] = 34
tNpcGossip[17195] = tNpcGossip[17195] or DefaultNpc:new{}
tNpcGossip[17195]["OptionHidden"] = 1
	--活动前对话
	tNpcGossip[17195]["Text1-1"] = {111,112}
	tNpcGossip[17195]["Text111"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text111"]
	tNpcGossip[17195]["Text112"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text112"]
	tNpcGossip[17195]["tOption1-1"] = {1}
	tNpcGossip[17195]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["Before"])
	end
	tNpcGossip[17195]["Option1"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option1"]
	--活动中对话
	tNpcGossip[17195]["Text1-2"] = {121}
	tNpcGossip[17195]["Text121"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text121"]
	tNpcGossip[17195]["tOption1-2"] = {100,5,6,7,8,9,10}
	tNpcGossip[17195]["ChkFunc1-2"] = function()
		ThanksGiving2015_ThrowFruit_ResetPlayer()
		return Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["During"])
	end
	--领取昨天奖励
	tNpcGossip[17195]["Option100"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option29"]
		tNpcGossip[17195]["OptionFunc100"] = "ThanksGiving2015_ThrowFruit_Top1Reward</N>17195"
		tNpcGossip[17195]["OptionChkFunc100"] = function()
			--存在昨天的冠军成绩
			return Get_SysDynaGlobalData2(tThanksGiving2015_ThrowFruit_Data["GlobalData"]) > 0
		end
	tNpcGossip[17195]["Option5"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option5"]
			tNpcGossip[17195]["OptionPoint5"] = "2-1"
	tNpcGossip[17195]["Option6"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option6"]
		tNpcGossip[17195]["OptionFunc6"] = "ThanksGiving2015_ThrowFruit_JoinAct</N>17195"
	tNpcGossip[17195]["Option7"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option7"]
		tNpcGossip[17195]["OptionFunc7"] = "ThanksGiving2015_ThrowFruit_ApplyReward</N>17195"
		tNpcGossip[17195]["OptionChkFunc7"] = function()
			--当日最好成绩大于0时才可见
			local nTodayTopEvent = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["EventType"]
			local nTodayTopType = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["DataType"]
			local nTodayTop = Get_UserStatisticValue(nTodayTopEvent,nTodayTopType)
			return nTodayTop > 0
		end
	tNpcGossip[17195]["Option8"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option8"]
		tNpcGossip[17195]["OptionFunc8"] = "ThanksGiving2015_ThrowFruit_ApplyExtra</N>17195"
		tNpcGossip[17195]["OptionChkFunc8"] = function()
			--当日最好成绩大于0时才可见
			local nTodayTopEvent = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["EventType"]
			local nTodayTopType = tThanksGiving2015_ThrowFruit_Stc["TodayTop"]["DataType"]
			local nTodayTop = Get_UserStatisticValue(nTodayTopEvent,nTodayTopType)
			return nTodayTop > 0
		end
	tNpcGossip[17195]["Option9"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option9"]
		tNpcGossip[17195]["OptionFunc9"] = "ThanksGiving2015_ThrowFruit_ChkTop</N>17195"
	tNpcGossip[17195]["Option10"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option10"]
	--活动后对话
	tNpcGossip[17195]["Text1-3"] = {131}
	tNpcGossip[17195]["Text131"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text131"]
	tNpcGossip[17195]["tOption1-3"] = {2,3}
	tNpcGossip[17195]["Option2"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option2"]
		tNpcGossip[17195]["OptionFunc2"] = "ThanksGiving2015_ThrowFruit_Top1Reward</N>17195"
		tNpcGossip[17195]["OptionChkFunc2"] = function()
			if not Sys_ChkFullTime(tThanksGiving2015_ThrowFruit_Data["Time"]["Delay"]) then
				return false
			end
			return true
		end
	tNpcGossip[17195]["Option3"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option3"]
--想了解一下规则
	tNpcGossip[17195]["Text2-1"] = {211,212}
	tNpcGossip[17195]["Text211"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text211"]
	tNpcGossip[17195]["Text212"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text212"]
	tNpcGossip[17195]["tOption2-1"] = {11,12}
	tNpcGossip[17195]["Option11"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option11"]
	tNpcGossip[17195]["OptionPoint11"] = "3-1"
	tNpcGossip[17195]["Option12"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option12"]
	tNpcGossip[17195]["OptionPoint12"] = "1-2"
--那么怎样计算分数呢？
	tNpcGossip[17195]["Text3-1"] = {311}
	tNpcGossip[17195]["Text311"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text311"]
	tNpcGossip[17195]["tOption3-1"] = {13}
	tNpcGossip[17195]["Option13"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option13"]
	
--我来参赛了！--变猩猩
	tNpcGossip[17195]["Text2-2"] = {221,222,223}
	tNpcGossip[17195]["Text221"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text221"]
	tNpcGossip[17195]["Text222"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text222"]
	tNpcGossip[17195]["Text223"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text223"]
	tNpcGossip[17195]["tOption2-2"] = {14,15}
	tNpcGossip[17195]["Option14"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option14"]
		tNpcGossip[17195]["OptionFunc14"] = "ThanksGiving2015_ThrowFruit_JudgeUser</N>17195"
	tNpcGossip[17195]["Option15"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option15"]
	--等级不足
	tNpcGossip[17195]["Text3-2"] = {321,322}
	tNpcGossip[17195]["Text321"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text321"]
	tNpcGossip[17195]["Text322"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text322"]
	tNpcGossip[17195]["tOption3-2"] = {16}
	tNpcGossip[17195]["Option16"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option16"]
	--变身成功
	tNpcGossip[17195]["Text3-3"] = {331}
	tNpcGossip[17195]["Text331"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text331"]
	tNpcGossip[17195]["tOption3-3"] = {17}
	tNpcGossip[17195]["Option17"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option17"]
--领取奖品
--分数不足
	tNpcGossip[17195]["Text2-3"] = {231}
	tNpcGossip[17195]["Text231"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text231"]
	tNpcGossip[17195]["tOption2-3"] = {19}
	tNpcGossip[17195]["Option19"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option19"]
--已领取过
	tNpcGossip[17195]["Text2-4"] = {241}
	tNpcGossip[17195]["Text241"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text241"]
	tNpcGossip[17195]["tOption2-4"] = {20}
	tNpcGossip[17195]["Option20"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option20"]
--背包已满
	tNpcGossip[17195]["Text2-5"] = {251}
	tNpcGossip[17195]["Text251"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text251"]
	tNpcGossip[17195]["tOption2-5"] = {21}
	tNpcGossip[17195]["Option21"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option21"]
	--给奖励
	tNpcGossip[17195]["Text2-6"] = {261}
	tNpcGossip[17195]["Text261"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text261"]
	tNpcGossip[17195]["tOption2-6"] = {22}
	tNpcGossip[17195]["Option22"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option22"]
		
--领取额外奖励
	tNpcGossip[17195]["Text4-1"] = {411}
	tNpcGossip[17195]["Text411"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text411"]
	tNpcGossip[17195]["tOption4-1"] = {23}
	tNpcGossip[17195]["Option20"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option20"]
--已领过奖
	tNpcGossip[17195]["Text4-2"] = {421}
	tNpcGossip[17195]["Text421"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text421"]
	tNpcGossip[17195]["tOption4-2"] = {37}
	tNpcGossip[17195]["Option37"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option37"]
--额外奖励,经验
	tNpcGossip[17195]["Text4-3"] = {431}
	tNpcGossip[17195]["Text431"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text431"]
	tNpcGossip[17195]["tOption4-3"] = {25}
	tNpcGossip[17195]["Option25"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option25"]
--额外奖励,修行值
	tNpcGossip[17195]["Text4-4"] = {441}
	tNpcGossip[17195]["Text441"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text441"]
	tNpcGossip[17195]["tOption4-4"] = {26}
	tNpcGossip[17195]["Option26"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option26"]
--查看排行榜
--当天第一名的情况
	tNpcGossip[17195]["Text5-1"] = {511}
	tNpcGossip[17195]["Text511"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text511"]
	tNpcGossip[17195]["tOption5-1"] = {27,28}
	tNpcGossip[17195]["Option27"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option27"]
		tNpcGossip[17195]["OptionFunc27"] = "ThanksGiving2015_ThrowFruit_Top1Reward</N>17195"
	tNpcGossip[17195]["Option28"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option28"]
--当天不是第一名的情况
	tNpcGossip[17195]["Text5-2"] = {521}
	tNpcGossip[17195]["Text521"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text521"]
	tNpcGossip[17195]["tOption5-2"] = {29,30}
	tNpcGossip[17195]["Option29"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option29"]
		tNpcGossip[17195]["OptionFunc29"] = "ThanksGiving2015_ThrowFruit_Top1Reward</N>17195"
		tNpcGossip[17195]["OptionChkFunc29"] = function()
			--存在昨天的冠军成绩
			return Get_SysDynaGlobalData2(tThanksGiving2015_ThrowFruit_Data["GlobalData"]) > 0
		end
	tNpcGossip[17195]["Option30"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option30"]
--尚未参加过比赛,和参加过只有对白不同,选项相同
	tNpcGossip[17195]["Text5-3"] = {531}
	tNpcGossip[17195]["Text531"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text531"]
	tNpcGossip[17195]["tOption5-3"] = {29,30}
	
--领取昨天奖励
	tNpcGossip[17195]["Text6-1"] = {611}
	tNpcGossip[17195]["Text611"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text611"]
	tNpcGossip[17195]["tOption6-1"] = {33}
	tNpcGossip[17195]["Option33"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option33"]
	
	tNpcGossip[17195]["Text6-2"] = {621}
	tNpcGossip[17195]["Text621"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text621"]
	tNpcGossip[17195]["tOption6-2"] = {34}
	tNpcGossip[17195]["Option34"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option34"]
	
	tNpcGossip[17195]["Text6-3"] = {631}
	tNpcGossip[17195]["Text631"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text631"]
	tNpcGossip[17195]["tOption6-3"] = {35}
	tNpcGossip[17195]["Option35"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option35"]
	
	tNpcGossip[17195]["Text6-4"] = {641}
	tNpcGossip[17195]["Text641"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text641"]
	tNpcGossip[17195]["tOption6-4"] = {36}
	tNpcGossip[17195]["Option36"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option36"]
	
	tNpcGossip[17195]["Text6-5"] = {651}
	tNpcGossip[17195]["Text651"] = tThanksGiving2015_ThrowFruit_Text[17195]["Text651"]
	tNpcGossip[17195]["tOption6-5"] = {37}
	tNpcGossip[17195]["Option37"] = tThanksGiving2015_ThrowFruit_Text[17195]["Option37"]

--17265/17196大饭桌lookface=876
tNpcGossip[17265] = tNpcGossip[17265] or DefaultNpc:new{}
tNpcGossip[17265]["OptionHidden"] = 1
--非活动中或变身状态不正确
	tNpcGossip[17265]["Text1-1"] = {111}
	tNpcGossip[17265]["Text111"] = tThanksGiving2015_ThrowFruit_Text[17265]["Text111"]
	tNpcGossip[17265]["tOption1-1"] = {1}
	tNpcGossip[17265]["ChkFunc1-1"] = function()
		return not ThanksGiving2015_ThrowFruit_Chk(1)
	end
	tNpcGossip[17265]["Option1"] = tThanksGiving2015_ThrowFruit_Text[17265]["Option1"]
--活动中
	tNpcGossip[17265]["Text1-2"] = {121,122}
	tNpcGossip[17265]["Text121"] = tThanksGiving2015_ThrowFruit_Text[17265]["Text121"]
	tNpcGossip[17265]["Text122"] = tThanksGiving2015_ThrowFruit_Text[17265]["Text122"]
	tNpcGossip[17265]["tOption1-2"] = {2,3}
	tNpcGossip[17265]["Option2"] = tThanksGiving2015_ThrowFruit_Text[17265]["Option2"]
	tNpcGossip[17265]["OptionFunc2"] = "ThanksGiving2015_ThrowFruit_TalkTable</N>17265"
	tNpcGossip[17265]["Option3"] = tThanksGiving2015_ThrowFruit_Text[17265]["Option3"]
	
	--背包已有果子
	tNpcGossip[17265]["Text2-1"] = {211}
	tNpcGossip[17265]["Text211"] = tThanksGiving2015_ThrowFruit_Text[17265]["Text211"]
	tNpcGossip[17265]["tOption2-1"] = {4}
	tNpcGossip[17265]["Option4"] = tThanksGiving2015_ThrowFruit_Text[17265]["Option4"]
	
	--17196和17265使用相同的模板
tNpcGossip[17196] = tNpcGossip[17265]

--17266/17197小澡盆lookface=680
--17267/17198小炉子lookface=700
--17268/17199小花瓶lookface=750
--三个npc对话相同,都套用模板
for nThrowTargetId = 17266,17268 do
	tNpcGossip[nThrowTargetId] = tNpcGossip[nThrowTargetId] or DefaultNpc:new{}
	tNpcGossip[nThrowTargetId]["OptionHidden"] = 1
	--非活动中或变身状态不正确
	tNpcGossip[nThrowTargetId]["Text1-1"] = {111}
	tNpcGossip[nThrowTargetId]["Text111"] = tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Text111"]
	tNpcGossip[nThrowTargetId]["tOption1-1"] = {1}
	tNpcGossip[nThrowTargetId]["ChkFunc1-1"] = function()
		return not ThanksGiving2015_ThrowFruit_Chk(1)
	end
	tNpcGossip[nThrowTargetId]["Option1"] = tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Option1"]
--活动中
	tNpcGossip[nThrowTargetId]["Text1-2"] = {121}
	tNpcGossip[nThrowTargetId]["Text121"] = tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Text121"]
	tNpcGossip[nThrowTargetId]["tOption1-2"] = {2,3}
	tNpcGossip[nThrowTargetId]["ChkFunc1-2"] = function()
		local nPointEvent = tThanksGiving2015_ThrowFruit_Stc["Point"]["EventType"]
		local nPointType = tThanksGiving2015_ThrowFruit_Stc["Point"]["DataType"]
		local nNowPoint = Get_UserStatisticValue(nPointEvent,nPointType)
		tNpcGossip[nThrowTargetId]["Text121"] = string.format(tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Text121"],nNowPoint)
		return true
	end
	tNpcGossip[nThrowTargetId]["Option2"] = tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Option2"]
	tNpcGossip[nThrowTargetId]["OptionFunc2"] = "ThanksGiving2015_ThrowFruit_Throw</N>" .. nThrowTargetId
	tNpcGossip[nThrowTargetId]["Option3"] = tThanksGiving2015_ThrowFruit_Text[nThrowTargetId]["Option3"]
end
tNpcGossip[17197] = tNpcGossip[17266]
tNpcGossip[17198] = tNpcGossip[17267]
tNpcGossip[17199] = tNpcGossip[17268]

-----------203w------------
table.insert(tSystem_Prompet_Func,ThanksGiving2015_ThrowFruit_SysChk)

