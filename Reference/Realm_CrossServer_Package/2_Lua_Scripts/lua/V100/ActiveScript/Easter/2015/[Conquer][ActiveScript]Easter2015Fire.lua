------------------------------------------------------------------------------------
--Name:			[英文征服][活动脚本]复活节活动之圣火传递(4.02-4.08)
--Purpose:		复活节活动之圣火传递
--Creator: 		丁晨
--Created:		2015/02/05
------------------------------------------------------------------------------------
--任务需求：
--1.	在双龙城活动区域摆下npc，用于介绍活动，领取圣火，领取奖励，领取每场第一名奖励。
--2.	比赛一天开设4场，每6小时1场。
--3.	玩家从npc处领取圣火，然后将圣火带到各家各户，为他们带来生命的祝福。
--坐标292,229   257,272    283,270   290,252    315,229这5个坐标。
--4.	完成圣火传递的玩家可以领取奖励。
--5.	如果是本场最快完成的玩家还有额外奖励。
--任务目标：将复活节圣火传递到家家户户。
--排名:50857
------------------------------------------------------------------------------------
--物品：

------------------------------------------------------------------------------------
--掩码说明
---stc(132,99) 记录场次与踩过的陷进

--LOGid 12000037
------------------------------------------------------------------------------------
--命名规范
-- Easter2015_
------------------------------------------------------------------------------------
--STC掩码
local tEaster2015_Fire_Stc = {}

	tEaster2015_Fire_Stc ={}
    tEaster2015_Fire_Stc["Event"] = 132
    tEaster2015_Fire_Stc["Type"] = 99
	
--活动开始时间
local tEaster2015_Fire_Time = {}
	tEaster2015_Fire_Time["Bef_Time"] = "2015-02-25 00:00 2015-04-01 23:59"
	tEaster2015_Fire_Time["Now_Time"] = "2015-04-02 00:00 2015-04-08 23:59"
--玩家限制 大于等于80级 或1转以上
local tEaster2015_Fire_PlayerLimit = {}
	tEaster2015_Fire_PlayerLimit["Level"] = 80
	tEaster2015_Fire_PlayerLimit["MinMetempsychosis"] = 0 
--陷阱坐标
local tEaster2015_Fire_Trap = {}
	tEaster2015_Fire_Trap["MapId"] = 1002
	
	tEaster2015_Fire_Trap[992394] = {}
	tEaster2015_Fire_Trap[992394]["PosX"] = 257
	tEaster2015_Fire_Trap[992394]["PosY"] = 272
	
	tEaster2015_Fire_Trap[992395] = {}
	tEaster2015_Fire_Trap[992395]["PosX"] = 283
	tEaster2015_Fire_Trap[992395]["PosY"] = 270
	
	tEaster2015_Fire_Trap[992396] = {}
	tEaster2015_Fire_Trap[992396]["PosX"] = 290
	tEaster2015_Fire_Trap[992396]["PosY"] = 252
	
	tEaster2015_Fire_Trap[992397] = {}
	tEaster2015_Fire_Trap[992397]["PosX"] = 292
	tEaster2015_Fire_Trap[992397]["PosY"] = 229
	
	tEaster2015_Fire_Trap[992398] = {}
	tEaster2015_Fire_Trap[992398]["PosX"] = 315
	tEaster2015_Fire_Trap[992398]["PosY"] = 229

--NPC坐标
local tEaster2015_Fire_Npc = {}
	tEaster2015_Fire_Npc["NpcId"] = 18289
	tEaster2015_Fire_Npc["MapId"] = 1002
	tEaster2015_Fire_Npc["PosX"] = 278
	tEaster2015_Fire_Npc["PosY"] = 385
--光效配置
local tEaster2015_Fire_Effect ={}
	tEaster2015_Fire_Effect["FireSpirit"] = "elf-standby_f"
	tEaster2015_Fire_Effect["TrapStamp"] = "m-b05"
	tEaster2015_Fire_Effect["GetRewards"] = "angelwing"
--活动Log
local tEaster2015_Fire_Log = {}
	--活动ID
	tEaster2015_Fire_Log["LogId"] = 12000037
	--活动参与
	tEaster2015_Fire_Log["Phase_1"] = "0,0,0,0,12000037,1[1],0,0"
	tEaster2015_Fire_Log["Phase_2"] = "0,0,0,0,12000037,1[2],0,0"
	--领取节日礼包log
	tEaster2015_Fire_Log["Phase_Gift"] = "0,0,0,0,12000037,2,3003625,1" 
--陷阱配置
local tEaster2015_Fire_TrapNum = {}
	tEaster2015_Fire_TrapNum[992394] = 1 
	tEaster2015_Fire_TrapNum[992395] = 2 
	tEaster2015_Fire_TrapNum[992396] = 4 
	tEaster2015_Fire_TrapNum[992397] = 8 
	tEaster2015_Fire_TrapNum[992398] = 16 
--陷阱配置2
local tEaster2015_Fire_NTrapNum ={}
	tEaster2015_Fire_NTrapNum["MinId"] = 992394
	tEaster2015_Fire_NTrapNum["MaxId"] = 992398
	tEaster2015_Fire_NTrapNum["UseId"] = 992393
	tEaster2015_Fire_NTrapNum["TrapCount"] = 5 
--场次配置
local tEaster2015_Fire_Session ={}
	tEaster2015_Fire_Session[1] = 32 
	tEaster2015_Fire_Session[2] = 64 
	tEaster2015_Fire_Session[3] = 128 
	tEaster2015_Fire_Session[4] = 256 
	
--这个场次已领取
local tEaster2015_Fire_Already ={}
	tEaster2015_Fire_Already[1] = 512
	
--场次时间
local tEaster2015_Fire_SessionTime = {}
	tEaster2015_Fire_SessionTime[1]= "08:00 11:59"
	tEaster2015_Fire_SessionTime[2]= "12:00 15:59"
	tEaster2015_Fire_SessionTime[3]= "16:00 21:59"
	tEaster2015_Fire_SessionTime[4]= "22:00 23:59"

--节日礼包配置
local tEaster2015_Fire_GiftReward={}
	tEaster2015_Fire_GiftReward["GiftBagId"] = 3381
	tEaster2015_Fire_GiftReward["BagLeft"] = 1
	tEaster2015_Fire_GiftReward["Check_Rank"] = 50857
	tEaster2015_Fire_GiftReward["OverFlow"] = 1	
	
--领取圣火精灵
function Easter2015_Fire_Sprite(nNpcId)
	--判断是否在活动期间
	if not Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--判断在活动期间 不再时间段
	if Easter2015_Fire_GetSession() == 0 then
		LinkNpcGossipFunc_New(nNpcId,"16-1")
		return
	end
	
	
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tEaster2015_Fire_PlayerLimit["Level"],tEaster2015_Fire_PlayerLimit["MinMetempsychosis"]) then
	
		--等级不足或未转世
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEvent = tEaster2015_Fire_Stc["Event"]
	local nType = tEaster2015_Fire_Stc["Type"]
	--隔天清空用户已领取的记录
	if  Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		User_EffectDel("self",tEaster2015_Fire_Effect["FireSpirit"])
		
	end
	
	
	--获取当前场次
	local nSession = Easter2015_Fire_GetSession()
	
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	--本轮已领取过
	if  User_TaskGetTypeNum(tEaster2015_Fire_Already[1],nData) then
		
		LinkNpcGossipFunc_New(nNpcId,"17-1")
		return
	end
	
	--是否在此阶段领取过
	if not  Task_ChkStcValue(nEvent,nType,"==",0) then
	
		--在此阶段领取过
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	

	
	--获取场次
	
	if not User_TaskGetTypeNum(nSession,nData) then
	
		--记录接到的场次
		nData = nData + nSession
		Task_SetStatistic(nEvent,nType,nData,1)
	end
	
	--满足条件 加光效
	User_EffectDel("self",tEaster2015_Fire_Effect["FireSpirit"])
	User_EffectAdd("self",tEaster2015_Fire_Effect["FireSpirit"])
	LinkNpcGossipFunc_New(nNpcId,"6-1")
	
	--领取任务log
	Sys_SaveActionFestivalLog(tEaster2015_Fire_Log["Phase_1"])
end

--获取当前场次
function Easter2015_Fire_GetSession()
	for k,v in pairs(tEaster2015_Fire_SessionTime) do
		if Sys_ChkDayTime(v) then
		
			--在场次时间
			return tEaster2015_Fire_Session[k]
		end
	end
	
	--不在场次时间 
	return 0
end

--判断场次、陷阱点是否正确
function Easter2015_Fire_Rule(nRule)
	--掩码
	local nEvent = tEaster2015_Fire_Stc["Event"]
	local nType = tEaster2015_Fire_Stc["Type"]
	local nData = Get_UserStatisticValue(nEvent,nType)

	if  not User_TaskGetTypeNum(nRule,nData) then
		return false
	end

	return true
end

--自动寻路
function Easter2015_Fire_FindWay(nIndex)
	local nMapId = tEaster2015_Fire_Trap["MapId"] 
	local nPosX = tEaster2015_Fire_Trap[nIndex]["PosX"]
	local nPosY = tEaster2015_Fire_Trap[nIndex]["PosY"]
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,0)
end

--地图光效
function Easter2015_Fire_MapEffect(nIndex)
	local nMapId = tEaster2015_Fire_Trap["MapId"] 
	local nPosX = tEaster2015_Fire_Trap[nIndex]["PosX"]
	local nPosY = tEaster2015_Fire_Trap[nIndex]["PosY"]
	Map_Effect(nMapId,nPosX,nPosY,tEaster2015_Fire_Effect["TrapStamp"])
end

--领取圣火奖励
function Easter2015_Fire_Reward(nNpcId)
	--判断是否在活动期间
	if not Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--判断在活动期间 不再时间段
	if Easter2015_Fire_GetSession() == 0 then
		LinkNpcGossipFunc_New(nNpcId,"16-1")
		return
	end
	
	
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tEaster2015_Fire_PlayerLimit["Level"],tEaster2015_Fire_PlayerLimit["MinMetempsychosis"]) then
	
		--等级不足或未转世
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEvent = tEaster2015_Fire_Stc["Event"]
	local nType = tEaster2015_Fire_Stc["Type"]
	
	
	--隔天清空用户已领取的记录
	if  Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	--已领取过
	if  User_TaskGetTypeNum(tEaster2015_Fire_Already[1],nData) then
		
		LinkNpcGossipFunc_New(nNpcId,"7-1")
		return
	end
	
	--没有完成任务
	
	for k,v in pairs(tEaster2015_Fire_TrapNum)do
		if not Easter2015_Fire_Rule(v) then
			LinkNpcGossipFunc_New(nNpcId,"8-1")
			return 
		end
	end
	
	--检测背包空间 
	if not User_CheckLeftSpace(tEaster2015_Fire_GiftReward["BagLeft"]) then 
	
		--背包满
		LinkNpcGossipFunc_New(nNpcId,"9-1")
		return
	end
	
	FestivalGeneralPackage_GetGift(tEaster2015_Fire_GiftReward["GiftBagId"],tEaster2015_Fire_Log["LogId"])
	
	--已领取当前场次
	nData = nData + tEaster2015_Fire_Already[1] 
	Task_SetStatistic(nEvent,nType,nData,1)
	User_EffectDel("self",tEaster2015_Fire_Effect["FireSpirit"])
	
	User_EffectAdd("self",tEaster2015_Fire_Effect["GetRewards"])
	--成功领取
	LinkNpcGossipFunc_New(nNpcId,"10-1")
	--完成任务log
	Sys_SaveActionFestivalLog(tEaster2015_Fire_Log["Phase_2"])
	
	--领取节日礼包log
	Sys_SaveActionFestivalLog(tEaster2015_Fire_Log["Phase_Gift"])
	
end

--领取额外奖励
function Easter2015_Fire_Overflow(nNpcId)
	--判断是否在活动期间
	if not Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--判断在活动期间 不再时间段
	if Easter2015_Fire_GetSession() == 0 then
		LinkNpcGossipFunc_New(nNpcId,"16-1")
		return
	end
	
	
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tEaster2015_Fire_PlayerLimit["Level"],tEaster2015_Fire_PlayerLimit["MinMetempsychosis"]) then
	
		--等级不足或未转世
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEvent = tEaster2015_Fire_Stc["Event"]
	local nType = tEaster2015_Fire_Stc["Type"]
	
	--隔天清空用户已领取的记录
	if  Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--不是第一个完成任务的
	if Get_SysDynaGlobalData0(tEaster2015_Fire_GiftReward["Check_Rank"])~= Get_UserId() then
		
		LinkNpcGossipFunc_New(nNpcId,"12-1")
		return
	end
	
	--已领取
	if Get_SysDynaGlobalData1(tEaster2015_Fire_GiftReward["Check_Rank"])==tEaster2015_Fire_GiftReward["OverFlow"] then
	
		LinkNpcGossipFunc_New(nNpcId,"11-1")
		return
	end
	
	--检测背包空间 
	if not User_CheckLeftSpace(tEaster2015_Fire_GiftReward["BagLeft"]) then 
	
		--背包满
		LinkNpcGossipFunc_New(nNpcId,"13-1")
		return
	end
	
	User_EffectAdd("self",tEaster2015_Fire_Effect["GetRewards"])
	--领取成功
	LinkNpcGossipFunc_New(nNpcId,"14-1")
	
	Sys_SetSynaGlobalData1(tEaster2015_Fire_GiftReward["Check_Rank"],tEaster2015_Fire_GiftReward["OverFlow"])
	
	FestivalGeneralPackage_GetGift(tEaster2015_Fire_GiftReward["GiftBagId"],tEaster2015_Fire_Log["LogId"])
	
	--领取节日礼包log
	Sys_SaveActionFestivalLog(tEaster2015_Fire_Log["Phase_Gift"])
end

--函数拆分数字
function User_TaskGetTypeNum(nNpcData,nData)
	local nPow = 0
	local nTemp = 0
	local bNpcData = false
	while nData ~= 0 and nData ~= nil do
		nTemp = nData % 2
		
		if nTemp ~= 0 then
--			print("nTemp" .. nTemp)
			if nNpcData == 2 ^ nPow then
				bNpcData = true
				break
			end
		end

		nPow = nPow + 1
		nData = (nData - nTemp) / 2
	end
	return bNpcData
end

--提前5分钟广播
function Easter2015_Fire_BefBroadCast()
	if  Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		Sys_TalkBroadcast(tEaster2015_Fire_Text["BefBroadCast"])
	end
end

--活动开始广播
function Easter2015_Fire_BroadCast()
	if  Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		Sys_TalkBroadcast(tEaster2015_Fire_Text["BroadCast"])
		Sys_ResetAllSynaGlobalData(tEaster2015_Fire_GiftReward["Check_Rank"])
	end
end

--NPC寻路
function Easter2015_Fire_FindWayNpc()
	--NPC坐标
	local nNpcId = tEaster2015_Fire_Npc["NpcId"] 
	local nMapId = tEaster2015_Fire_Npc["MapId"] 
	local nPosX = tEaster2015_Fire_Npc["PosX"]
	local nPosY = tEaster2015_Fire_Npc["PosY"] 
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

--陷阱Func 
function Easter2015_Fire_TrapFunc(nTrapId)
	local nEvent = tEaster2015_Fire_Stc["Event"]
	local nType = tEaster2015_Fire_Stc["Type"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	--本轮已领取过
	if  User_TaskGetTypeNum(tEaster2015_Fire_Already[1],nData) then
		return
	end
	
	
	--是否已完成任务
	local bSesion = true
	
	for k,v in pairs(tEaster2015_Fire_TrapNum)do
		if not Easter2015_Fire_Rule(v) then
			bSesion = false
		end
	end
	
	if bSesion then
		--是否第一个做完任务
		if Get_SysDynaGlobalData0(tEaster2015_Fire_GiftReward["Check_Rank"]) == 0 then
			Sys_SetSynaGlobalData0(tEaster2015_Fire_GiftReward["Check_Rank"],Get_UserId())
		end
		--第5个陷进直接回去找NPC 
		Sys_MsgBox(tEaster2015_Fire_Text["EndTrap"],"Easter2015_Fire_FindWayNpc")
		return 
	end

	
	--获取当前场次
	local nSession = Easter2015_Fire_GetSession()
	
	--当前场次有接任务
	if not Easter2015_Fire_Rule(nSession) then
		--当前场次已过清除掩码
		Task_SetStatistic(nEvent,nType,0,1)
		User_EffectDel("self",tEaster2015_Fire_Effect["FireSpirit"])
		return 
	end
	
	if not Easter2015_Fire_TrapOrder(nTrapId) then
		--获取下一个要踩的点并且移动过去
		Sys_MsgBox(tEaster2015_Fire_Text["SpriteGuide"],"Easter2015_Fire_GetPoint")
		return 
	end
	
	local nCurrIndex = nTrapId - tEaster2015_Fire_NTrapNum["UseId"]
	local nNextIndex = nCurrIndex + 1
	local sMsgText =string.format(tEaster2015_Fire_Text["BefTrap"],nCurrIndex,nNextIndex)
	
	--是否踩过陷进
	if not  Easter2015_Fire_Rule(tEaster2015_Fire_TrapNum[nTrapId]) then
		nData = nData +tEaster2015_Fire_TrapNum[nTrapId]
		Task_SetStatistic(nEvent,nType,nData,1)
		Easter2015_Fire_MapEffect(nTrapId)
	else
		--获取下一个要踩的点并且移动过去
		Sys_MsgBox(tEaster2015_Fire_Text["SpriteGuide"],"Easter2015_Fire_GetPoint")
		return 
	end
	
	--判断是否是前4个陷阱 
	if  nCurrIndex~= tEaster2015_Fire_NTrapNum["TrapCount"] then
		Sys_MsgBox(sMsgText,"Easter2015_Fire_FindWay</N>"..nTrapId+1)
	else
		
		--是否第一个做完任务
		if Get_SysDynaGlobalData0(tEaster2015_Fire_GiftReward["Check_Rank"]) == 0 then
			Sys_SetSynaGlobalData0(tEaster2015_Fire_GiftReward["Check_Rank"],Get_UserId())
		end
		--第5个陷进直接回去找NPC 
		Sys_MsgBox(tEaster2015_Fire_Text["EndTrap"],"Easter2015_Fire_FindWayNpc")
	end
end

--判断陷阱是否按照顺序
function Easter2015_Fire_TrapOrder(nTrapId)
	if nTrapId ~= tEaster2015_Fire_NTrapNum["MinId"] then
	
		for i= nTrapId-1,tEaster2015_Fire_NTrapNum["MinId"],-1 do
			if not Easter2015_Fire_Rule(tEaster2015_Fire_TrapNum[i]) then
				return false
			end
		end
	end
	
	return true
end

--上线添加精灵
function Easter2015_Fire_Priest_Login()
	
	--判断是否在活动期间
	if not Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"]) then
		return
	end

	--获取当前场次
	local nSession = Easter2015_Fire_GetSession()
	
	--当前场次有接任务
	if  Easter2015_Fire_Rule(nSession) then
		--当前场次已过清除掩码
		
		User_EffectAdd("self",tEaster2015_Fire_Effect["FireSpirit"])
	else
		User_EffectDel("self",tEaster2015_Fire_Effect["FireSpirit"])
	end
	
end

--获取当前踩到的点
function Easter2015_Fire_GetPoint()
	for i = tEaster2015_Fire_NTrapNum["MaxId"] ,tEaster2015_Fire_NTrapNum["MinId"],-1 do
		if Easter2015_Fire_Rule(tEaster2015_Fire_TrapNum[i]) then
			if i~= tEaster2015_Fire_NTrapNum["MaxId"] then
				Easter2015_Fire_FindWay(i+1)
				return 
			end
		else
			Easter2015_Fire_FindWay(tEaster2015_Fire_NTrapNum["MinId"])
		end
	end
end

--获取上一个完成的场次
function Easter2015_Fire_GetFinishSession()
	for k, v in pairs (tEaster2015_Fire_Session)do
		if Easter2015_Fire_Rule(v) then
			return v 
		end
	end
	return 0
end

--复活节圣火大使
tNpcFace[3575] = 216
tNpcGossip[18289] = tNpcGossip[18289] or DefaultNpc:new{}
tNpcGossip[18289]["OptionHidden"] = 1

--活动前对白
tNpcGossip[18289]["Text1-1"] = {111,112,113}
tNpcGossip[18289]["Text111"] = tEaster2015_Fire_Text[18289]["Text111"]
tNpcGossip[18289]["Text112"] = tEaster2015_Fire_Text[18289]["Text112"]
tNpcGossip[18289]["Text113"] = tEaster2015_Fire_Text[18289]["Text113"]
tNpcGossip[18289]["Option11"] = tEaster2015_Fire_Text[18289]["Option1"]
tNpcGossip[18289]["tOption1-1"] = {11}
tNpcGossip[18289]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tEaster2015_Fire_Time["Bef_Time"])
end

--活动中对白
tNpcGossip[18289]["Text1-2"] = {211,212,213}
tNpcGossip[18289]["Text211"] = tEaster2015_Fire_Text[18289]["Text115"]
tNpcGossip[18289]["Text212"] = tEaster2015_Fire_Text[18289]["Text116"]
tNpcGossip[18289]["Text213"] = tEaster2015_Fire_Text[18289]["Text117"]

tNpcGossip[18289]["Option21"] = tEaster2015_Fire_Text[18289]["Option3"]
tNpcGossip[18289]["Option22"] = tEaster2015_Fire_Text[18289]["Option4"]
tNpcGossip[18289]["Option23"] = tEaster2015_Fire_Text[18289]["Option5"]
tNpcGossip[18289]["Option24"] = tEaster2015_Fire_Text[18289]["Option6"]
tNpcGossip[18289]["Option25"] = tEaster2015_Fire_Text[18289]["Option7"]

tNpcGossip[18289]["tOption1-2"] = {21,22,23,24,25}
tNpcGossip[18289]["OptionFunc21"]="Easter2015_Fire_Sprite</N>18289"
tNpcGossip[18289]["OptionFunc22"]="Easter2015_Fire_Reward</N>18289"
tNpcGossip[18289]["OptionFunc23"]="Easter2015_Fire_Overflow</N>18289"
tNpcGossip[18289]["OptionFunc24"]="LinkNpcGossipFunc_New</N>18289</S>15-1"

tNpcGossip[18289]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tEaster2015_Fire_Time["Now_Time"])
end

--活动后对白
tNpcGossip[18289]["Text1-3"] = {311}
tNpcGossip[18289]["Text311"] = tEaster2015_Fire_Text[18289]["Text114"]
tNpcGossip[18289]["Option31"] = tEaster2015_Fire_Text[18289]["Option2"]
tNpcGossip[18289]["tOption1-3"] = {31}

------------------------------------------Option21------------------------------------------------
--已领取
tNpcGossip[18289]["Text4-1"] = {411}
tNpcGossip[18289]["Text411"] = tEaster2015_Fire_Text[18289]["Text118"]
tNpcGossip[18289]["Option41"] = tEaster2015_Fire_Text[18289]["Option8"]
tNpcGossip[18289]["Option42"] = tEaster2015_Fire_Text[18289]["Option20"]
tNpcGossip[18289]["tOption4-1"] = {41,42}
tNpcGossip[18289]["OptionChkFunc42"] = function ()
	--是否完成任务
	for k,v in pairs(tEaster2015_Fire_TrapNum)do
		if not Easter2015_Fire_Rule(v) then
			return true
		end
	end
	return false
end
tNpcGossip[18289]["OptionFunc42"]="Easter2015_Fire_GetPoint"
--条件不足
tNpcGossip[18289]["Text5-1"] = {511}
tNpcGossip[18289]["Text511"] = tEaster2015_Fire_Text[18289]["Text119"]
tNpcGossip[18289]["Option51"] = tEaster2015_Fire_Text[18289]["Option9"]
tNpcGossip[18289]["tOption5-1"] = {51}
--满足条件
tNpcGossip[18289]["Text6-1"] = {611}
tNpcGossip[18289]["Text611"] = tEaster2015_Fire_Text[18289]["Text120"]
tNpcGossip[18289]["Option61"] = tEaster2015_Fire_Text[18289]["Option10"]
tNpcGossip[18289]["tOption6-1"] = {61}
tNpcGossip[18289]["OptionFunc61"]="Easter2015_Fire_FindWay</N>992394"

------------------------------------------Option22------------------------------------------------
--已领取
tNpcGossip[18289]["Text7-1"] = {711}
tNpcGossip[18289]["Text711"] = tEaster2015_Fire_Text[18289]["Text121"]
tNpcGossip[18289]["Option71"] = tEaster2015_Fire_Text[18289]["Option11"]
tNpcGossip[18289]["tOption7-1"] = {71}
--条件不足
tNpcGossip[18289]["Text8-1"] = {811}
tNpcGossip[18289]["Text811"] = tEaster2015_Fire_Text[18289]["Text122"]
tNpcGossip[18289]["Option81"] = tEaster2015_Fire_Text[18289]["Option12"]
tNpcGossip[18289]["tOption8-1"] = {81}
--背包满
tNpcGossip[18289]["Text9-1"] = {911}
tNpcGossip[18289]["Text911"] = tEaster2015_Fire_Text[18289]["Text123"]
tNpcGossip[18289]["Option91"] = tEaster2015_Fire_Text[18289]["Option11"]
tNpcGossip[18289]["tOption9-1"] = {91}
--成功领取
tNpcGossip[18289]["Text10-1"] = {1011}
tNpcGossip[18289]["Text1011"] = tEaster2015_Fire_Text[18289]["Text124"]
tNpcGossip[18289]["Option101"] = tEaster2015_Fire_Text[18289]["Option14"]
tNpcGossip[18289]["tOption10-1"] = {101}

------------------------------------------Option23------------------------------------------------
--已领取
tNpcGossip[18289]["Text11-1"] = {1111}
tNpcGossip[18289]["Text1111"] = tEaster2015_Fire_Text[18289]["Text125"]
tNpcGossip[18289]["Option111"] = tEaster2015_Fire_Text[18289]["Option15"]
tNpcGossip[18289]["tOption11-1"] = {111}
--条件不足
tNpcGossip[18289]["Text12-1"] = {1211}
tNpcGossip[18289]["Text1211"] = tEaster2015_Fire_Text[18289]["Text126"]
tNpcGossip[18289]["Option121"] = tEaster2015_Fire_Text[18289]["Option16"]
tNpcGossip[18289]["tOption12-1"] = {121}
--背包满
tNpcGossip[18289]["Text13-1"] = {1311}
tNpcGossip[18289]["Text1311"] = tEaster2015_Fire_Text[18289]["Text127"]
tNpcGossip[18289]["Option131"] = tEaster2015_Fire_Text[18289]["Option17"]
tNpcGossip[18289]["tOption13-1"] = {131}
--成功领取
tNpcGossip[18289]["Text14-1"] = {1411}
tNpcGossip[18289]["Text1411"] = tEaster2015_Fire_Text[18289]["Text128"]
tNpcGossip[18289]["Option141"] = tEaster2015_Fire_Text[18289]["Option18"]
tNpcGossip[18289]["tOption14-1"] = {141}
------------------------------------------Option24------------------------------------------------
--了解活动详情
tNpcGossip[18289]["Text15-1"] = {1511,1512,1513,1514}
tNpcGossip[18289]["Text1511"] = tEaster2015_Fire_Text[18289]["Text129"]
tNpcGossip[18289]["Text1512"] = tEaster2015_Fire_Text[18289]["Text130"]
tNpcGossip[18289]["Text1513"] = tEaster2015_Fire_Text[18289]["Text131"]
tNpcGossip[18289]["Text1514"] = tEaster2015_Fire_Text[18289]["Text132"]
tNpcGossip[18289]["Option151"] = tEaster2015_Fire_Text[18289]["Option19"]
tNpcGossip[18289]["tOption15-1"] = {151}

--在活动期间 不再时间段
tNpcGossip[18289]["Text16-1"] = {1611}
tNpcGossip[18289]["Text1611"] = tEaster2015_Fire_Text["AbsentTime"]
tNpcGossip[18289]["Option161"] = tEaster2015_Fire_Text[18289]["Option19"]
tNpcGossip[18289]["tOption16-1"] = {161}

--本轮奖励已经领取过了 请等待下一轮
tNpcGossip[18289]["Text17-1"] = {1711}
tNpcGossip[18289]["Text1711"] = tEaster2015_Fire_Text["TimeGetAlready"]
tNpcGossip[18289]["Option171"] = tEaster2015_Fire_Text[18289]["Option19"]
tNpcGossip[18289]["tOption17-1"] = {161}


--时间函数触发 每天4场
--tOntimerMin_HM[0800] = tOntimerMin_HM[0800] or {}
--table.insert(tOntimerMin_HM[0800],Easter2015_Fire_BroadCast)
--tOntimerMin_HM[1200] = tOntimerMin_HM[1200] or {}
--table.insert(tOntimerMin_HM[1200],Easter2015_Fire_BroadCast)
--tOntimerMin_HM[1600] = tOntimerMin_HM[1600] or {}
--table.insert(tOntimerMin_HM[1600],Easter2015_Fire_BroadCast)
--tOntimerMin_HM[2200] = tOntimerMin_HM[2200] or {}
--table.insert(tOntimerMin_HM[2200],Easter2015_Fire_BroadCast)

--提前5分钟提示
--tOntimerMin_HM[0755] = tOntimerMin_HM[0755] or {}
--table.insert(tOntimerMin_HM[0755],Easter2015_Fire_BefBroadCast)
--tOntimerMin_HM[1155] = tOntimerMin_HM[1155] or {}
--table.insert(tOntimerMin_HM[1155],Easter2015_Fire_BefBroadCast)
--tOntimerMin_HM[1555] = tOntimerMin_HM[1555] or {}
--table.insert(tOntimerMin_HM[1555],Easter2015_Fire_BefBroadCast)
--tOntimerMin_HM[2155] = tOntimerMin_HM[2155] or {}
--table.insert(tOntimerMin_HM[2155],Easter2015_Fire_BefBroadCast)

--陷阱配置 
--tTrap[1274]= tTrap[1274] or {}
--tTrap[1274]["Function"] = function (nTrapId,nTrapType)
--	Easter2015_Fire_TrapFunc(nTrapId)
--end

--上线触发
--table.insert(tSystem_PlayLogin_Func,Easter2015_Fire_Priest_Login)