------------------------------------------------------------------------------------
--Name:			150826[简体征服][活动脚本]2015感恩节-火鸡总动园（11.24-11.30）
--Purpose:		火鸡总动园（11.24-11.30）
--Creator:		王倩娜
--Created:		2015-08-26
------------------------------------------------------------------------------------
--前缀ThanksGiving2015_FreeBirdsIntMacth_
--stc(130,04)	领奖掩码，1可领，2已领	
--stc(130,05)	每时段一次传送，1进入，隔1小时	
--stc(130,06)	积分，每次进入前清理	300

--50662 动态表 
-- data0  单数 偶数
-- data1  单数天的最高分
-- data3  最高分的玩家id

-- data2  偶数天的最高分
-- data4  最高分的玩家id

-- data5  奖励领取
-- datastr0  清理

---------------------------------table定义--------------------------------------
local tThanksGiving2015_FreeBirdsIntMacth_Cont = {}
	--活动时间
	tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"] = "2015-11-24 00:00 2015-11-30 23:59"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-11-23 23:59"
	
	tThanksGiving2015_FreeBirdsIntMacth_Cont["FirstDay"] = "2015-11-24 00:00 2015-11-24 23:59"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["LastDay"] = "2015-12-01 00:00 2015-12-01 23:59"

	tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"][1] = "10:00 10:29"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"][2] = "12:00 12:29"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"][3] = "18:00 18:29"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"][4] = "22:00 22:29"
	
	tThanksGiving2015_FreeBirdsIntMacth_Cont["ClearTime"] = "00:00 00:05"
	
	tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"][1] = "10:30 10:31"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"][2] = "12:30 12:31"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"][3] = "18:30 18:31"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"][4] = "22:30 22:31"
	
	
	--玩家等级要求
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Metempsychosis"] = 0
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Level"] = 80

	tThanksGiving2015_FreeBirdsIntMacth_Cont["MeteAwardLimit"] = 3
	-- 掩码
	--stc(130,04)	领奖掩码，1可领，2已领	
	--stc(130,05)	每时段一次传送，1进入，隔1小时	
	--stc(130,06)	积分，每次进入前清理	13006
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"] = {}
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["Event"] = 130
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["StcType"] = 04
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nRewardSign"] = 1
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nGetSign"] = 2

	tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"] = {}
		tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["Event"] = 130
		tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["StcType"] = 05
		tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["nChgSign"] = 1

	tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"] = {}
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["Event"] = 130
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["StcType"] = 06
		tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["nCountSign"] = 300

	tThanksGiving2015_FreeBirdsIntMacth_Cont["Space"] = 1
	-- 奖励物品
	tThanksGiving2015_FreeBirdsIntMacth_Cont["FestivalId"] = 3330
	tThanksGiving2015_FreeBirdsIntMacth_Cont["LogId"] = 12000199
	tThanksGiving2015_FreeBirdsIntMacth_Cont["ExtraExp"] = 200
	tThanksGiving2015_FreeBirdsIntMacth_Cont["ExtraCult"] = 100
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MaxLevel"] = 140

	--全局表
	--data0,data1,datastr1表示今天最高分,最高分id,最高分姓名
	--data2,data3,datastr3,data4表示昨日最高分,最高分id,最高分姓名,是否已经领取过奖励
	tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"] = 50662
	
	--log
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["GetExp"] = "0,0,0,0,12000199,2,4,200"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["GetCult"] = "0,0,0,0,12000199,2,6,100"
	tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["Start"] = "0,0,0,0,12000199,1,0,0"
		
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["MapId"] = 3883
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["PosX"] = 200
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["PosY"] = 205
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["BoundX"] = 5
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["BoundY"] = 5

	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225]["MapId"] = 1002
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225]["PosX"] = 274
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225]["PosY"] = 364
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225]["BoundX"] = 5
	tThanksGiving2015_FreeBirdsIntMacth_Cont[17225]["BoundY"] = 5
	
	-- 怪物积分
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"] = {}
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"][7631] = 1
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"][7632] = 2
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"][7633] = 3
	tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"][7634] = 5
---------------------------------逻辑定义--------------------------------------
-- 活动整点判断
function ThanksGiving2015_FreeBirdsIntMacth_CheakHourPoint(tHourPoint)

	for k,v in ipairs(tHourPoint) do
		if Sys_ChkDayTime(v) then
			return true
		end 
	end
	
	return false	 
end
-- 这就前去猎杀火鸡。
function ThanksGiving2015_FreeBirdsIntMacth_CheakTheGameMap(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--钟点判断
	local tHourPoint = tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"]
	if not ThanksGiving2015_FreeBirdsIntMacth_CheakHourPoint(tHourPoint) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tThanksGiving2015_FreeBirdsIntMacth_Cont["Level"],tThanksGiving2015_FreeBirdsIntMacth_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	-- 单日已完成任务
	--stc(130,04)	领奖掩码，1可领，2已领	
	local nRewardEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["Event"]
	local nRewardType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["StcType"]
	local nGetSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nGetSign"]

	if Task_ChkStcValue(nRewardEvent,nRewardType,">=",nGetSign) then
		 if not Task_StcInterval(nRewardEvent,nRewardType,1,4) then
			-- 今日已领奖励
			LinkNpcGossipFunc_New(nNpcId,"3-4")
			return
		else
			Task_SetStatistic(nRewardEvent,nRewardType,0,1,0)
			Task_SetStcTimestamp(nRewardEvent,nRewardType,0,0)
		end
	end
	
	-- stc(130,05)	每时段一次传送，1进入，隔1小时	
	local nChgMapEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["Event"]
	local nChgMapType = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["StcType"]
	local nChgMapSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["nChgSign"]

	if Task_ChkStcValue(nChgMapEvent,nChgMapType,">=",nChgMapSign) then
		 if not Task_StcInterval(nChgMapEvent,nChgMapType,1,2) then
			-- 一小时只能进入一次
			LinkNpcGossipFunc_New(nNpcId,"3-3")
			return
		end
	end
		
	--条件都符合
	LinkNpcGossipFunc_New(nNpcId,"3-5")

end
--传入地图
function ThanksGiving2015_FreeBirdsIntMacth_MovedGameMap(nNpcId)
	--积分清理
	local nCountEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["Event"]
	local nCountType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["StcType"]
	-- stc(130,05)	每时段一次传送
	local nChgMapEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["Event"]
	local nChgMapType = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["StcType"]
	local nChgMapSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["ChgMap"]["nChgSign"]
	--传送
	Task_SetStatistic(nChgMapEvent,nChgMapType,nChgMapSign,1,0)
	Task_SetStcTimestamp(nChgMapEvent,nChgMapType,0,0)
	
	Task_SetStatistic(nCountEvent,nCountType,0,1,0)
	Task_SetStcTimestamp(nCountEvent,nCountType,0,0)

	Sys_SaveActionFestivalLog(tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["Start"])

	ThanksGiving2015_FreeBirdsIntMacth_MovedToMap(nNpcId)
	
end
--移动地图
function ThanksGiving2015_FreeBirdsIntMacth_MovedToMap(nNpcId)
	local nMapId = tThanksGiving2015_FreeBirdsIntMacth_Cont[nNpcId]["MapId"]
	local nPosX = tThanksGiving2015_FreeBirdsIntMacth_Cont[nNpcId]["PosX"]
	local nPosY = tThanksGiving2015_FreeBirdsIntMacth_Cont[nNpcId]["PosY"]
	local nBoundX = tThanksGiving2015_FreeBirdsIntMacth_Cont[nNpcId]["BoundX"]
	local nBoundY = tThanksGiving2015_FreeBirdsIntMacth_Cont[nNpcId]["BoundY"]

	--将玩家传送到地图的指定区域
	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBoundX,nBoundY)
	User_TalkChannel2005(tThanksGiving2015_FreeBirdsIntMacth_Text["MsgText"]["MoveToMap"][nNpcId])

end
-- 领取猎杀火鸡奖励。
function ThanksGiving2015_FreeBirdsIntMacth_GetPersonalReward(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	--已领取
	local nRewardEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["Event"]
	local nRewardType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["StcType"]
	local nRewardSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nRewardSign"]
	local nGetSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nGetSign"]
	
	if not Task_ChkStcValue(nRewardEvent,nRewardType,">=",nRewardSign) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
		
	if Task_StcInterval(nRewardEvent,nRewardType,1,4) then
		Task_SetStatistic(nRewardEvent,nRewardType,0,1,0)
		Task_SetStcTimestamp(nRewardEvent,nRewardType,0,0)
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	if Task_ChkStcValue(nRewardEvent,nRewardType,">=",nGetSign) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	--空间
	if not User_CheckLeftSpace (tThanksGiving2015_FreeBirdsIntMacth_Cont["Space"]) then
		User_TalkChannel2005(tThanksGiving2015_FreeBirdsIntMacth_Text["MsgText"]["BagSpace"])
		return
	end
	--未领取
	if Task_ChkStcValue(nRewardEvent,nRewardType,"==",nRewardSign) then
		Task_SetStatistic(nRewardEvent,nRewardType,nGetSign,1,0)
		Task_SetStcTimestamp(nRewardEvent,nRewardType,0,0)
		FestivalGeneralPackage_GetGift(tThanksGiving2015_FreeBirdsIntMacth_Cont["FestivalId"],tThanksGiving2015_FreeBirdsIntMacth_Cont["LogId"])
		LinkNpcGossipFunc_New(nNpcId,"4-3")
	end
end
--猎杀信息
function ThanksGiving2015_FreeBirdsIntMacth_NewInformation(nNpcId)
	if ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal() then
	end

	--积分
	local nCountEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["Event"]
	local nCountType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["StcType"]
	
	--隔天清掉
	if Task_ChkStcValue(nCountEvent,nCountType,"~=",0) then
		 if Task_StcInterval(nCountEvent,nCountType,1,4) then
			Task_SetStatistic(nCountEvent,nCountType,0,1,0)
			Task_SetStcTimestamp(nCountEvent,nCountType,0,0)
		end
	end

	local nPersonalCount = Get_UserStatisticValue(nCountEvent,nCountType) 	
	local sPersonalScore = string.format(tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text611"],nPersonalCount)

	local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]
	local nData0 = Get_SysDynaGlobalData0(nGlobalId)

	if nData0 == 0 then
		ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()  --确认实时赋值问题
	end
	
	-- ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal()
	
	local nIndex = nData0 + 2
	local nMaxCount = Get_SysDynaGlobalData(nGlobalId,nData0)
	local nUserId = Get_SysDynaGlobalData(nGlobalId,nIndex)
	local sUserName = Get_UserName(nUserId)
	
	if nMaxCount == 0 then
		Sys_DialogText(sPersonalScore)
		Sys_DialogText(tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text612"])
		Sys_DialogOption(tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option23"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	else
		local sSeverScore = string.format(tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text613"],sUserName,nMaxCount)
		Sys_DialogText(sPersonalScore)
		Sys_DialogText(sSeverScore)
		Sys_DialogOption(tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option23"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end

end
-- 领取前一天额外奖励。
function ThanksGiving2015_FreeBirdsIntMacth_GetYestodayReward(nNpcId)
	if ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal() then
	end

	local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]
	local nData0 = Get_SysDynaGlobalData0(nGlobalId)
	local nUserId = Get_UserId()
	
	if nData0 == 0 then
		ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()  --确认实时赋值问题
	end
	
	-- data0为1，前一天是2、4；为2前一天是1、3
	local nIndex = 0
	if nData0 == 1 then
		nIndex = 4
	else
		nIndex = 3
	end
	local nRewardUserId = Get_SysDynaGlobalData(nGlobalId,nIndex)
	
	if nRewardUserId ~= nUserId then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	end
		
	local data5 = Get_SysDynaGlobalData5(nGlobalId)
	if data5 >= 1 then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	--准备给奖励
	Sys_SetSynaGlobalData5(nGlobalId,1)
	
	
	local nUserLev = Get_UserLevel()
	if nUserLev < tThanksGiving2015_FreeBirdsIntMacth_Cont["MaxLevel"] then
		local nExpTime = tThanksGiving2015_FreeBirdsIntMacth_Cont["ExtraExp"]

		User_AddExpTime(nExpTime)
		Sys_SaveActionFestivalLog(tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["GetExp"])
		LinkNpcGossipFunc_New(nNpcId,"5-3")
	else
		local nCultivation = tThanksGiving2015_FreeBirdsIntMacth_Cont["ExtraCult"]

		User_AddCultivation(nCultivation)
		Sys_SaveActionFestivalLog(tThanksGiving2015_FreeBirdsIntMacth_Cont["Log"]["GetCult"])
		LinkNpcGossipFunc_New(nNpcId,"5-4")
	end
end

function ThanksGiving2015_FreeBirdsIntMacth_MonsterDeath()
	-- 判断活动时间
	if not Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"]) then
		return 
	end
	
	--钟点判断
	local tHourPoint = tThanksGiving2015_FreeBirdsIntMacth_Cont["HourPoint"]
	if not ThanksGiving2015_FreeBirdsIntMacth_CheakHourPoint(tHourPoint) then
		return  
	end
		
	-- 积分累加
	local nCountEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["Event"]
	local nCountType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Count"]["StcType"]
	
	local nMonsId = Get_MonsterType()
	local nMonsCount = tThanksGiving2015_FreeBirdsIntMacth_Cont["MonsCount"][nMonsId]
	local nPersCount = Get_UserStatisticValue(nCountEvent,nCountType) 	
	local nTemp = nPersCount + nMonsCount
	
	Task_SetStatistic(nCountEvent,nCountType,nTemp,1,0)
	Task_SetStcTimestamp(nCountEvent,nCountType,0,0)

	-- local nUserScore = Get_UserStatisticValue(nCountEvent,nCountType) 	
	local sUserScore = string.format(tThanksGiving2015_FreeBirdsIntMacth_Text["MsgText"]["Tukey"][nMonsId],nTemp)

	User_TalkChannel2005(sUserScore)

	
	-- 判断300，设置可领奖
	if nTemp >= 300 then
		local nRewardEvent = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["Event"]
		local nRewardType = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["StcType"]
		local nRewardSign = tThanksGiving2015_FreeBirdsIntMacth_Cont["Reward"]["nRewardSign"]
		if not Task_ChkStcValue(nRewardEvent,nRewardType,">=",nRewardSign) then
			Task_SetStatistic(nRewardEvent,nRewardType,nRewardSign,1,0)
			Task_SetStcTimestamp(nRewardEvent,nRewardType,0,0)
			Sys_MsgBox(tThanksGiving2015_FreeBirdsIntMacth_Text["MsgText"]["CountTips"])
		end

	end
	
	-- 动态表比较。
	local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]
	local nData0 = Get_SysDynaGlobalData0(nGlobalId)
	local nUserId = Get_UserId()
	
	if nData0 == 0 then
		ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()  --确认实时赋值问题
	end
	
	local nMaxCount = Get_SysDynaGlobalData(nGlobalId,nData0)
	if nTemp > nMaxCount then
		local nIndex = nData0+2
		Sys_SetSynaGlobalData(nGlobalId,nData0,nTemp)
		Sys_SetSynaGlobalData(nGlobalId,nIndex,nUserId)
	end
	
end
function ThanksGiving2015_FreeBirdsIntMacth_SysChk()
	if not Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"]) then
		if Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["LastDay"]) then
			local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]
			Sys_SetSynaGlobalData(nGlobalId,0,2)
			ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal()
		end
		return
	end
	
	
	--实时赋值下data1
	ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()
	--清理领取奖励标示
	ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal()
	
	--清理地图
	ThanksGiving2015_FreeBirdsIntMacth_KickThePlayerOut()
	
	
end
-- 清理地图
function ThanksGiving2015_FreeBirdsIntMacth_KickThePlayerOut()
	local tKickTime = tThanksGiving2015_FreeBirdsIntMacth_Cont["KickTime"]
	if ThanksGiving2015_FreeBirdsIntMacth_CheakHourPoint(tKickTime) then
		local nMapId =tThanksGiving2015_FreeBirdsIntMacth_Cont[17224]["MapId"]
		Map_UserExeFunc(nMapId,-1,"ThanksGiving2015_FreeBirdsIntMacth_MovedToMap</N>17225")
	end
end
-- 每天前五分钟。清理领取奖励标示。。。‘
function ThanksGiving2015_FreeBirdsIntMacth_ClearTheGlobal()
	local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]
	--不在前五分钟。。
	if not Sys_ChkDayTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ClearTime"]) then
		Sys_SetSynaGlobalDataStr0(nGlobalId,"")
		return
	end

	local nData0 = Get_SysDynaGlobalData0(nGlobalId)
	if nData0 == 0 then
		ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()
	end
	
	local sDatastr0 = Get_SysDynaGlobalDataStr0(nGlobalId)

	if sDatastr0 ~= "" then
		return
	end		

	-- ndata0 为1.清理当天;那就是清理1,3.如果为2.那就是清理2,4
	local nUserId = 0 --玩家id下标
	nUserId = nData0 + 2
	
	Sys_SetSynaGlobalDataStr0(nGlobalId,"HavedReset")
	Sys_SetSynaGlobalData5(nGlobalId,0)
	Sys_SetSynaGlobalData(nGlobalId,nData0,0)
	Sys_SetSynaGlobalData(nGlobalId,nUserId,0)
	--清理干净了。。
	
end

-- 对data0进行赋值（排除活动后一天）
function ThanksGiving2015_FreeBirdsIntMacth_SetTheDayData0()
	local nTemp = 0
	local nGlobalId = tThanksGiving2015_FreeBirdsIntMacth_Cont["GlobalId"]

	local tFuZhiData0 ={[1] = "24 00:00 24 23:59",[2] = "25 00:00 25 23:59",[3] = "26 00:00 26 23:59",[4] = "27 00:00 27 23:59",[5] = "28 00:00 28 23:59",[6] = "29 00:00 29 23:59",[7] = "30 00:00 30 23:59",[8] = "01 00:00 01 23:59"}

	for k,v in ipairs(tFuZhiData0) do
		if Sys_ChkMonthTime(v) then
			nTemp = k
			break
		end
	end
	
	local nIndex = nTemp % 2
	if nIndex == 0 then
		nIndex = 2
	end
	
	Sys_SetSynaGlobalData(nGlobalId,0,nIndex)
end
-----------------------------------Npc模板--------------------------------------
--17224	宫廷御厨火鸡克星
tNpcFace[3245] = 69

tNpcGossip[17224] = tNpcGossip[17224] or DefaultNpc:new{}
tNpcGossip[17224]["OptionHidden"] = 1
	--活动前对话
	tNpcGossip[17224]["Text1-1"] = {111,112,113}
	tNpcGossip[17224]["Text111"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text111"]
	tNpcGossip[17224]["Text112"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text112"]
	tNpcGossip[17224]["Text113"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text113"]
	tNpcGossip[17224]["tOption1-1"] = {1}
	tNpcGossip[17224]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["BeforeActivityTime"])
	end
	tNpcGossip[17224]["Option1"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option1"]
	
	--中
	tNpcGossip[17224]["Text1-2"] = {121,122,123,124}
	tNpcGossip[17224]["Text121"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text121"]
	tNpcGossip[17224]["Text122"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text122"]
	tNpcGossip[17224]["Text123"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text123"]
	tNpcGossip[17224]["Text124"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text124"]
	tNpcGossip[17224]["tOption1-2"] = {2,3,4,5,6,7}
	tNpcGossip[17224]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["ActivityTime"])
	end
	-- 这就前去猎杀火鸡。
	tNpcGossip[17224]["Option2"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option2"]
	tNpcGossip[17224]["OptionFunc2"]="ThanksGiving2015_FreeBirdsIntMacth_CheakTheGameMap</N>17224"
	-- 领取猎杀火鸡奖励。		
	tNpcGossip[17224]["Option3"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option3"]
	tNpcGossip[17224]["OptionFunc3"]="ThanksGiving2015_FreeBirdsIntMacth_GetPersonalReward</N>17224"
	--领取前一天额外奖励。
	tNpcGossip[17224]["Option4"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option4"]
	tNpcGossip[17224]["OptionFunc4"]="ThanksGiving2015_FreeBirdsIntMacth_GetYestodayReward</N>17224"
	tNpcGossip[17224]["OptionChkFunc4"] = function ()
		return not Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["FirstDay"])
	end
	-- 查看当前猎杀信息。
	tNpcGossip[17224]["Option5"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option5"]
	tNpcGossip[17224]["OptionFunc5"]="ThanksGiving2015_FreeBirdsIntMacth_NewInformation</N>17224"
	-- 猎杀火鸡的规则？
	tNpcGossip[17224]["Option6"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option6"]
	tNpcGossip[17224]["OptionPoint6"] = "2-1"

	tNpcGossip[17224]["Option7"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option7"]

	-- 后
	tNpcGossip[17224]["Text1-3"] = {131,132}
	tNpcGossip[17224]["Text131"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text131"]
	tNpcGossip[17224]["Text132"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text132"]
	tNpcGossip[17224]["tOption1-3"] = {8,9}

	tNpcGossip[17224]["Option8"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option8"]
	tNpcGossip[17224]["OptionFunc8"]="ThanksGiving2015_FreeBirdsIntMacth_GetYestodayReward</N>17224"
	tNpcGossip[17224]["OptionChkFunc8"] = function ()
		return Sys_ChkFullTime(tThanksGiving2015_FreeBirdsIntMacth_Cont["LastDay"])
	end
	tNpcGossip[17224]["Option9"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option9"]

	-- 猎杀火鸡的规则？
	tNpcGossip[17224]["Text2-1"] = {211,212,213,214}
	tNpcGossip[17224]["Text211"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text211"]
	tNpcGossip[17224]["Text212"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text212"]
	tNpcGossip[17224]["Text213"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text213"]
	tNpcGossip[17224]["Text214"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text214"]
	tNpcGossip[17224]["tOption2-1"] = {10}
	tNpcGossip[17224]["Option10"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option10"]

	-- 不在刷怪时间
	tNpcGossip[17224]["Text3-1"] = {311,312,313}
	tNpcGossip[17224]["Text311"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text311"]
	tNpcGossip[17224]["Text312"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text312"]
	tNpcGossip[17224]["Text313"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text313"]
	tNpcGossip[17224]["tOption3-1"] = {11}
	tNpcGossip[17224]["Option11"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option11"]
	-- 玩家等级不足
	tNpcGossip[17224]["Text3-2"] = {321,322}
	tNpcGossip[17224]["Text321"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text321"]
	tNpcGossip[17224]["Text322"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text322"]
	tNpcGossip[17224]["tOption3-2"] = {12}
	tNpcGossip[17224]["Option12"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option12"]
	-- 玩家在该时段内已进去过一次，不让再进
	tNpcGossip[17224]["Text3-3"] = {331,332}
	tNpcGossip[17224]["Text331"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text331"]
	tNpcGossip[17224]["Text332"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text332"]
	tNpcGossip[17224]["tOption3-3"] = {13}
	tNpcGossip[17224]["Option13"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option13"]
	-- 当日已领取奖励、提示玩家再玩则不能领取奖励、玩家确认后进地图
	tNpcGossip[17224]["Text3-4"] = {341}
	tNpcGossip[17224]["Text341"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text341"]
	-- tNpcGossip[17224]["Text342"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text342"]
	tNpcGossip[17224]["tOption3-4"] = {15}
	-- tNpcGossip[17224]["Option14"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option14"]

	tNpcGossip[17224]["Option15"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option15"]
	-- 成功
	tNpcGossip[17224]["Text3-5"] = {351,352,353}
	tNpcGossip[17224]["Text351"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text351"]
	tNpcGossip[17224]["Text352"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text352"]
	tNpcGossip[17224]["Text353"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text353"]
	tNpcGossip[17224]["tOption3-5"] = {16}
	tNpcGossip[17224]["Option16"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option16"]
	tNpcGossip[17224]["OptionFunc16"]="ThanksGiving2015_FreeBirdsIntMacth_MovedGameMap</N>17224"
	
	-- 玩家未完成该活动
	tNpcGossip[17224]["Text4-1"] = {411,412}
	tNpcGossip[17224]["Text411"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text411"]
	tNpcGossip[17224]["Text412"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text412"]
	tNpcGossip[17224]["tOption4-1"] = {17}
	tNpcGossip[17224]["Option17"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option17"]
	-- 已领取当天奖励
	tNpcGossip[17224]["Text4-2"] = {421}
	tNpcGossip[17224]["Text421"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text421"]
	tNpcGossip[17224]["tOption4-2"] = {18}
	tNpcGossip[17224]["Option18"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option18"]
	-- 领取活动奖励
	tNpcGossip[17224]["Text4-3"] = {431,432}
	tNpcGossip[17224]["Text431"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text431"]
	tNpcGossip[17224]["Text432"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text432"]
	tNpcGossip[17224]["tOption4-3"] = {19}
	tNpcGossip[17224]["Option19"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option19"]
	
	-- 已领取额外奖励
	tNpcGossip[17224]["Text5-1"] = {511}
	tNpcGossip[17224]["Text511"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text511"]
	tNpcGossip[17224]["tOption5-1"] = {20}
	tNpcGossip[17224]["Option20"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option20"]
	-- 不是第一名
	tNpcGossip[17224]["Text5-2"] = {521,522}
	tNpcGossip[17224]["Text521"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text521"]
	tNpcGossip[17224]["Text522"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text522"]
	tNpcGossip[17224]["tOption5-2"] = {21}
	tNpcGossip[17224]["Option21"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option21"]
	-- 领取前一天额外奖励
	tNpcGossip[17224]["Text5-3"] = {531,532}
	tNpcGossip[17224]["Text531"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text531"]
	tNpcGossip[17224]["Text532"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text532"]
	tNpcGossip[17224]["tOption5-3"] = {22}
	tNpcGossip[17224]["Option22"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option22"]
	
	tNpcGossip[17224]["Text5-4"] = {541,542}
	tNpcGossip[17224]["Text541"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text541"]
	tNpcGossip[17224]["Text542"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text542"]
	tNpcGossip[17224]["tOption5-4"] = {22}
	
	-- 查看当天猎杀信息
	tNpcGossip[17224]["Text6-1"] = {611,612}
	tNpcGossip[17224]["Text611"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text611"]
	tNpcGossip[17224]["Text612"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Text612"]
	tNpcGossip[17224]["tOption6-1"] = {23}
	tNpcGossip[17224]["Option23"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17224]["Option23"]


	
	-- 地图内
	tNpcGossip[17225] = tNpcGossip[17225] or DefaultNpc:new{}
	tNpcGossip[17225]["OptionHidden"] = 1
	
	tNpcGossip[17225]["Text1-1"] = {111,112,113}
	tNpcGossip[17225]["Text111"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Text111"]
	tNpcGossip[17225]["Text112"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Text112"]
	tNpcGossip[17225]["Text113"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Text113"]
	tNpcGossip[17225]["tOption1-1"] = {1,2,3}
	tNpcGossip[17225]["Option1"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Option1"]
	tNpcGossip[17225]["OptionPoint1"] = "1-2"
	tNpcGossip[17225]["Option2"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Option2"]
	tNpcGossip[17225]["OptionFunc2"]="ThanksGiving2015_FreeBirdsIntMacth_NewInformation</N>17225"
	tNpcGossip[17225]["Option3"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Option3"]

	tNpcGossip[17225]["Text1-2"] = {121}
	tNpcGossip[17225]["Text121"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Text121"]
	tNpcGossip[17225]["tOption1-2"] = {4,5}
	tNpcGossip[17225]["Option4"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Option4"]
	tNpcGossip[17225]["OptionFunc4"]="ThanksGiving2015_FreeBirdsIntMacth_MovedToMap</N>17225"
	tNpcGossip[17225]["Option5"] = tThanksGiving2015_FreeBirdsIntMacth_Text[17225]["Option5"]
	

	
-- 7631,普通火鸡
tMonster[7631] = tMonster[7631] or {}
tMonster[7631]["tFunction"] = tMonster[7631]["tFunction"] or {}
table.insert(tMonster[7631]["tFunction"],ThanksGiving2015_FreeBirdsIntMacth_MonsterDeath)

-- 7632,暴躁的火鸡
tMonster[7632] = tMonster[7632] or {}
tMonster[7632]["tFunction"] = tMonster[7632]["tFunction"] or {}
table.insert(tMonster[7632]["tFunction"],ThanksGiving2015_FreeBirdsIntMacth_MonsterDeath)

-- 7633,愤怒的火鸡
tMonster[7633] = tMonster[7633] or {}
tMonster[7633]["tFunction"] = tMonster[7633]["tFunction"] or {}
table.insert(tMonster[7633]["tFunction"],ThanksGiving2015_FreeBirdsIntMacth_MonsterDeath)

-- 7634,燃烧的火鸡
tMonster[7634] = tMonster[7634] or {}
tMonster[7634]["tFunction"] = tMonster[7634]["tFunction"] or {}
table.insert(tMonster[7634]["tFunction"],ThanksGiving2015_FreeBirdsIntMacth_MonsterDeath)


-----------203w------------
tSystem_Prompet_Func = tSystem_Prompet_Func or {}
table.insert(tSystem_Prompet_Func,ThanksGiving2015_FreeBirdsIntMacth_SysChk)
