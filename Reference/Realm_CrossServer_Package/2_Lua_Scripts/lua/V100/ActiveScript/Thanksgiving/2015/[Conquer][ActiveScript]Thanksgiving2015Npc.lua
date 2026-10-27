------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]感恩节活动之感恩节大使
--Creator:		张世超
--Created:		2015/08/25
------------------------------------------------------------------------------------
--前缀 Thanksgiving2015_Npc_

---------------------------------table定义--------------------------------------
local tThanksgiving2015_Npc_Data = {}
--活动时间
	tThanksgiving2015_Npc_Data["Time"] = {}
	-- tThanksgiving2015_Npc_Data["Time"]["Before"] = "2015-01-01 00:00 2015-08-28 23:59"
	-- tThanksgiving2015_Npc_Data["Time"]["During"] = "2015-08-29 00:00 2015-09-02 23:59"
	tThanksgiving2015_Npc_Data["Time"]["Before"] = "2015-01-01 00:00 2015-11-23 23:59"
	tThanksgiving2015_Npc_Data["Time"]["During"] = "2015-11-24 00:00 2015-11-30 23:59"
	
--等级限制
	tThanksgiving2015_Npc_Data["Level"] = 80
	tThanksgiving2015_Npc_Data["Metempsychosis"] = 0

--相关数据
	tThanksgiving2015_Npc_Data["Space"] = 1
	tThanksgiving2015_Npc_Data["Cranberry"] = 3004937
	tThanksgiving2015_Npc_Data["Effect"] = "angelwing"	
	tThanksgiving2015_Npc_Data["BlessTime"] = 24
	
	
--log
	local tThanksgiving2015_Npc_Log = {}
	tThanksgiving2015_Npc_Log["Festival"] = 3330
	tThanksgiving2015_Npc_Log["Id"] = 10002350
	tThanksgiving2015_Npc_Log["CranberryTask"] = "0,0,3004937,1,10002350,2,3003625,1"
	tThanksgiving2015_Npc_Log["AllDone"] = "0,0,0,0,10002350,2,3003625,1"
	
--掩码
-- #stc(130,00)
-- #0：玩家还未获得过神奇的蔓越莓
-- #1：玩家上限获得神奇的蔓越莓
-- #2：玩家第一次使用蔓越莓获得24天祝福
-- #stc(130,01)
-- #判断玩家是否已领取过分享蔓越莓（拜访任务）的奖励

-- #stc(130,02) 每天完成全部任务奖励
-- #stc(130,09)  黄金脆皮火鸡活动。
-- #stc(130,10)  特赦火鸡活动。
-- #stc(130,11)  火鸡总动员活动。
-- #stc(130,12)  蔓越莓竞赛活动。
-- #stc(130,13)  敲宝箱活动。
-- #stc(130,14)  猩猩投果子活动。

local tThanksgiving2015_Npc_Stc = {}
-- #stc(130,00)
-- #0：玩家还未获得过神奇的蔓越莓
-- #1：玩家上限获得神奇的蔓越莓
-- #2：玩家第一次使用蔓越莓获得24天祝福
tThanksgiving2015_Npc_Stc["Cranberry"] = {}
tThanksgiving2015_Npc_Stc["Cranberry"]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Cranberry"]["DataType"] = 00
tThanksgiving2015_Npc_Stc["Cranberry"]["Complete"] = 2

-- #stc(130,01)
-- #判断玩家是否已领取过分享蔓越莓（拜访任务）的奖励
tThanksgiving2015_Npc_Stc["CranberryTask"] = {}
tThanksgiving2015_Npc_Stc["CranberryTask"]["EventType"] = 130
tThanksgiving2015_Npc_Stc["CranberryTask"]["DataType"] = 01
tThanksgiving2015_Npc_Stc["CranberryTask"]["Complete"] = 1

-- #stc(130,02)
-- #判断玩家是否已领取过全部完成奖励
tThanksgiving2015_Npc_Stc["AllDone"] = {}
tThanksgiving2015_Npc_Stc["AllDone"]["EventType"] = 130
tThanksgiving2015_Npc_Stc["AllDone"]["DataType"] = 02
tThanksgiving2015_Npc_Stc["AllDone"]["Complete"] = 6

tThanksgiving2015_Npc_Stc["Visit"] = {}
-- #stc(130,09)  黄金脆皮火鸡活动。
tThanksgiving2015_Npc_Stc["Visit"][1] = {}
tThanksgiving2015_Npc_Stc["Visit"][1]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][1]["DataType"] = 09
tThanksgiving2015_Npc_Stc["Visit"][1]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][1]["TaskEventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][1]["TaskDataType"] = 08
tThanksgiving2015_Npc_Stc["Visit"][1]["TaskComplete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][1]["NpcId"] = 17230

-- #stc(130,10)  特赦火鸡活动。
tThanksgiving2015_Npc_Stc["Visit"][2] = {}
tThanksgiving2015_Npc_Stc["Visit"][2]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][2]["DataType"] = 10
tThanksgiving2015_Npc_Stc["Visit"][2]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][2]["TaskEventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][2]["TaskDataType"] = 07
tThanksgiving2015_Npc_Stc["Visit"][2]["TaskComplete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][2]["NpcId"] = 17226

-- #stc(130,10)  特赦火鸡活动。
tThanksgiving2015_Npc_Stc["Visit"][3] = {}
tThanksgiving2015_Npc_Stc["Visit"][3]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][3]["DataType"] = 11
tThanksgiving2015_Npc_Stc["Visit"][3]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][3]["TaskEventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][3]["TaskDataType"] = 04
tThanksgiving2015_Npc_Stc["Visit"][3]["TaskComplete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][3]["NpcId"] = 17224


-- #stc(130,12)  蔓越莓竞赛活动。
tThanksgiving2015_Npc_Stc["Visit"][4] = {}
tThanksgiving2015_Npc_Stc["Visit"][4]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][4]["DataType"] = 12
tThanksgiving2015_Npc_Stc["Visit"][4]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][4]["TaskEventType"] = 129
tThanksgiving2015_Npc_Stc["Visit"][4]["TaskDataType"] = 52
tThanksgiving2015_Npc_Stc["Visit"][4]["TaskComplete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][4]["NpcId"] = 17176


---- #stc(130,13)  敲宝箱活动。
tThanksgiving2015_Npc_Stc["Visit"][5] = {}
tThanksgiving2015_Npc_Stc["Visit"][5]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][5]["DataType"] = 13
tThanksgiving2015_Npc_Stc["Visit"][5]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][5]["TaskEventType"] = 128
tThanksgiving2015_Npc_Stc["Visit"][5]["TaskDataType"] = 93
tThanksgiving2015_Npc_Stc["Visit"][5]["TaskComplete"] = 10
tThanksgiving2015_Npc_Stc["Visit"][5]["NpcId"] = 17095

-- #stc(130,14)  猩猩投果子活动。
tThanksgiving2015_Npc_Stc["Visit"][6] = {}
tThanksgiving2015_Npc_Stc["Visit"][6]["EventType"] = 130
tThanksgiving2015_Npc_Stc["Visit"][6]["DataType"] = 14
tThanksgiving2015_Npc_Stc["Visit"][6]["Complete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][6]["TaskEventType"] = 129
tThanksgiving2015_Npc_Stc["Visit"][6]["TaskDataType"] = 84
tThanksgiving2015_Npc_Stc["Visit"][6]["TaskComplete"] = 1
tThanksgiving2015_Npc_Stc["Visit"][6]["NpcId"] = 17195



---------------------------------逻辑定义--------------------------------------
function Thanksgiving2015_Npc_Visit()
	local nNpcId = Get_NpcId()


	local nItemId = tThanksgiving2015_Npc_Data["Cranberry"]
	if (not Item_ChkItem(nItemId)) or (not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"])) then
			
		return 
	end


	for i=1,#tThanksgiving2015_Npc_Stc["Visit"] do
	
		if  nNpcId == tThanksgiving2015_Npc_Stc["Visit"][i]["NpcId"] then 
			local nEvent = tThanksgiving2015_Npc_Stc["Visit"][i]["EventType"] 
			local nType = tThanksgiving2015_Npc_Stc["Visit"][i]["DataType"]
			local nData = Get_UserStatisticValue(nEvent,nType) or 0
			local sStr = Thanksgiving2015_Npc_Text["MessageBox"][i]
		
			if (nData == 0) then
				Task_SetStatistic(nEvent,nType,tThanksgiving2015_Npc_Stc["Visit"][i]["Complete"],1) 
				Sys_MsgBox(sStr)
			end
			
		end
	end
end



--我要领取完成全部活动的奖励。
function Thanksgiving2015_Npc_Gift(nNpcId)
	if not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	--等级判定
	
	if not User_JudgeLevelAndMetempsychosis(tThanksgiving2015_Npc_Data["Level"],tThanksgiving2015_Npc_Data["Metempsychosis"]) then 
		LinkNpcGossipFunc_New(nNpcId,"20-1")
		return
	end
	--已经领取奖励
	local nTaskEvent = tThanksgiving2015_Npc_Stc["AllDone"]["EventType"]
	local nTaskType = tThanksgiving2015_Npc_Stc["AllDone"]["DataType"]
	local nData = Get_UserStatisticValue(nTaskEvent,nTaskType) or 0
	local sLog = tThanksgiving2015_Npc_Log["AllDone"]
	local nSpaceNum = tThanksgiving2015_Npc_Data["Space"]
	
		
		
	if (nData >= tThanksgiving2015_Npc_Stc["AllDone"]["Complete"]) then
	
		if not Task_StcInterval(nTaskEvent,nTaskType,1,4) then 
			LinkNpcGossipFunc_New(nNpcId,"20-2")
			return
		else

			nData = 0 
			Task_SetStatistic(nTaskEvent,nTaskType,nData,1) 
			Task_SetStcTimestamp(nTaskEvent,nTaskType,0)
		end
	end	
	

	--未完成任务
	for i=1,#tThanksgiving2015_Npc_Stc["Visit"] do

		local nEvent = tThanksgiving2015_Npc_Stc["Visit"][i]["TaskEventType"] 
		local nType = tThanksgiving2015_Npc_Stc["Visit"][i]["TaskDataType"]
		local sName = Thanksgiving2015_Npc_Name[i]
		local nData = Get_UserStatisticValue(nEvent,nType) or 0
		
		if nData < tThanksgiving2015_Npc_Stc["Visit"][i]["TaskComplete"] or Task_StcInterval(nEvent,nType,1,4) then
			tNpcGossip[nNpcId]["Text2041"] = string.format(Thanksgiving2015_Npc_Text[nNpcId]["Text2041"],sName)
			LinkNpcGossipFunc_New(nNpcId,"20-4")
			return	
		end			

	end
	
	--领取奖励
	if not User_CheckLeftSpace(tThanksgiving2015_Npc_Data["Space"]) then 
		LinkNpcGossipFunc_New(nNpcId,"20-3")
		return		
	end
	
	Task_SetStatistic(nTaskEvent,nTaskType,tThanksgiving2015_Npc_Stc["AllDone"]["Complete"],1) 
	Task_SetStcTimestamp(nTaskEvent,nTaskType,0) 
	FestivalGeneralPackage_GetGift(tThanksgiving2015_Npc_Log["Festival"],tThanksgiving2015_Npc_Log["Id"])
	Sys_SaveActionLog(sLog)	
	User_EffectAdd("self",tThanksgiving2015_Npc_Data["Effect"])	
	LinkNpcGossipFunc_New(nNpcId,"20-5")

end



--寻路
function Thanksgiving2015_Npc_Lead(nNpcId,nTarget)
	if not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"]) then
		return
	end

	local nPosX = Get_NpcPositionX(nTarget)
	local nPosY = Get_NpcPositionY(nTarget)
	local nMapId = Get_NpcMapID(nTarget)
	local nNpcId = nTarget
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

--与庆典策划人们共享蔓越莓。
function Thanksgiving2015_Npc_Share(nNpcId)
	if not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	local bFlag = true
	for i=1,#tThanksgiving2015_Npc_Stc["Visit"] do
		local nEvent = tThanksgiving2015_Npc_Stc["Visit"][i]["EventType"] 
		local nType = tThanksgiving2015_Npc_Stc["Visit"][i]["DataType"]
		local nData = Get_UserStatisticValue(nEvent,nType) or 0
		if nData == 0 then
			bFlag = false and bFlag
		end
	end	
	
	if not bFlag then
		--未全部完成
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nEvent = tThanksgiving2015_Npc_Stc["CranberryTask"]["EventType"] 
	local nType = tThanksgiving2015_Npc_Stc["CranberryTask"]["DataType"]
	local nItemId = tThanksgiving2015_Npc_Data["Cranberry"]
	local sStr = Thanksgiving2015_Npc_Text["MessageBox1"] 
	local sStr1 = Thanksgiving2015_Npc_Text["MessageBox2"] 
	local sLog = tThanksgiving2015_Npc_Log["CranberryTask"]
	
	
	if not Item_ChkItem(nItemId) then
		User_TalkChannel2005(sStr)
		return false
	else
		--领取奖励
		Item_DelItem(nItemId)
		Task_SetStatistic(nEvent,nType,tThanksgiving2015_Npc_Stc["CranberryTask"]["Complete"],1) 
		FestivalGeneralPackage_GetGift(tThanksgiving2015_Npc_Log["Festival"],tThanksgiving2015_Npc_Log["Id"])
		Sys_SaveActionLog(sLog)	
		User_TalkChannel2005(sStr1)	
		User_EffectAdd("self",tThanksgiving2015_Npc_Data["Effect"])	
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		
	end
end


-----------------------------------Npc模板--------------------------------------
tNpcFace[3251] = 12
tNpcGossip[17231] = tNpcGossip[17231] or DefaultNpc:new{}
tNpcGossip[17231]["OptionHidden"] = 1

--活动前
tNpcGossip[17231]["Text1-1"] = {111,112}
tNpcGossip[17231]["tOption1-1"] = {1}
tNpcGossip[17231]["Text111"] = Thanksgiving2015_Npc_Text[17231]["Text111"]
tNpcGossip[17231]["Text112"] = Thanksgiving2015_Npc_Text[17231]["Text112"]
tNpcGossip[17231]["Option1"] = Thanksgiving2015_Npc_Text[17231]["Option1"]
tNpcGossip[17231]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["Before"])
end

--活动后
tNpcGossip[17231]["Text1-2"] = {121,122}
tNpcGossip[17231]["tOption1-2"] = {2}
tNpcGossip[17231]["Text121"] = Thanksgiving2015_Npc_Text[17231]["Text121"]
tNpcGossip[17231]["Text122"] = Thanksgiving2015_Npc_Text[17231]["Text122"]
tNpcGossip[17231]["Option2"] = Thanksgiving2015_Npc_Text[17231]["Option2"]
tNpcGossip[17231]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"])
end

--活动中
tNpcGossip[17231]["Text1-3"] = {131,132,133}
tNpcGossip[17231]["tOption1-3"] = {3,4,5,6}
tNpcGossip[17231]["Text131"] = Thanksgiving2015_Npc_Text[17231]["Text131"]
tNpcGossip[17231]["Text132"] = Thanksgiving2015_Npc_Text[17231]["Text132"]
tNpcGossip[17231]["Text133"] = Thanksgiving2015_Npc_Text[17231]["Text133"]
tNpcGossip[17231]["Option3"] = Thanksgiving2015_Npc_Text[17231]["Option3"]
tNpcGossip[17231]["Option4"] = Thanksgiving2015_Npc_Text[17231]["Option4"]
tNpcGossip[17231]["Option5"] = Thanksgiving2015_Npc_Text[17231]["Option5"]
tNpcGossip[17231]["Option6"] = Thanksgiving2015_Npc_Text[17231]["Option6"]
tNpcGossip[17231]["OptionFunc3"] = "Thanksgiving2015_Npc_Share</N>17231"
tNpcGossip[17231]["OptionPoint4"] = "2"
tNpcGossip[17231]["OptionFunc5"] = "Thanksgiving2015_Npc_Gift</N>17231"

tNpcGossip[17231]["OptionChkFunc3"] = function ()
	local nItemId = tThanksgiving2015_Npc_Data["Cranberry"]
	local nEvent =tThanksgiving2015_Npc_Stc["CranberryTask"]["EventType"] 
	local nType = tThanksgiving2015_Npc_Stc["CranberryTask"]["DataType"] 
	local nData = Get_UserStatisticValue(nEvent,nType) or 0
	
	if not Item_ChkItem(nItemId) then
		return false
	end
	if nData >= tThanksgiving2015_Npc_Stc["CranberryTask"]["Complete"] then
		return false	
	else 
		return true
	end
end

--未完成
tNpcGossip[17231]["Text3-1"] = {311,312,313}
tNpcGossip[17231]["tOption3-1"] = {10}
tNpcGossip[17231]["Text311"] = Thanksgiving2015_Npc_Text[17231]["Text311"]
tNpcGossip[17231]["Text312"] = Thanksgiving2015_Npc_Text[17231]["Text312"]
tNpcGossip[17231]["Text313"] = Thanksgiving2015_Npc_Text[17231]["Text313"]
tNpcGossip[17231]["Option10"] = Thanksgiving2015_Npc_Text[17231]["Option10"]

--领取奖励
tNpcGossip[17231]["Text3-2"] = {321}
tNpcGossip[17231]["tOption3-2"] = {11}
tNpcGossip[17231]["Text321"] = Thanksgiving2015_Npc_Text[17231]["Text321"]
tNpcGossip[17231]["Option11"] = Thanksgiving2015_Npc_Text[17231]["Option11"]

--我想了解一下活动详情。
tNpcGossip[17231]["Text2-1"] = {211,212,213}
tNpcGossip[17231]["tOption2-1"] = {20,21,22,23,24,25,26}
tNpcGossip[17231]["Text211"] = Thanksgiving2015_Npc_Text[17231]["Text211"]
tNpcGossip[17231]["Text212"] = Thanksgiving2015_Npc_Text[17231]["Text212"]
tNpcGossip[17231]["Text213"] = Thanksgiving2015_Npc_Text[17231]["Text213"]
tNpcGossip[17231]["Option20"] = Thanksgiving2015_Npc_Text[17231]["Option20"]
tNpcGossip[17231]["Option21"] = Thanksgiving2015_Npc_Text[17231]["Option21"]
tNpcGossip[17231]["Option22"] = Thanksgiving2015_Npc_Text[17231]["Option22"]
tNpcGossip[17231]["Option23"] = Thanksgiving2015_Npc_Text[17231]["Option23"]
tNpcGossip[17231]["Option24"] = Thanksgiving2015_Npc_Text[17231]["Option24"]
tNpcGossip[17231]["Option25"] = Thanksgiving2015_Npc_Text[17231]["Option25"]
tNpcGossip[17231]["Option26"] = Thanksgiving2015_Npc_Text[17231]["Option26"]
tNpcGossip[17231]["OptionPoint20"] = "11"
tNpcGossip[17231]["OptionPoint21"] = "12"
tNpcGossip[17231]["OptionPoint22"] = "13"
tNpcGossip[17231]["OptionPoint23"] = "14"
tNpcGossip[17231]["OptionPoint24"] = "15"
tNpcGossip[17231]["OptionPoint25"] = "16"

--黄金脆皮火鸡活动。
tNpcGossip[17231]["Text11-1"] = {1111,1112,1113}
tNpcGossip[17231]["tOption11-1"] = {30,31}
tNpcGossip[17231]["Text1111"] = Thanksgiving2015_Npc_Text[17231]["Text1111"]
tNpcGossip[17231]["Text1112"] = Thanksgiving2015_Npc_Text[17231]["Text1112"]
tNpcGossip[17231]["Text1113"] = Thanksgiving2015_Npc_Text[17231]["Text1113"]
tNpcGossip[17231]["Option30"] = Thanksgiving2015_Npc_Text[17231]["Option30"]
tNpcGossip[17231]["Option31"] = Thanksgiving2015_Npc_Text[17231]["Option31"]
tNpcGossip[17231]["OptionFunc30"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17230"
tNpcGossip[17231]["OptionPoint31"] = "2"

--特赦火鸡活动。
tNpcGossip[17231]["Text12-1"] = {1211,1212,1213}
tNpcGossip[17231]["tOption12-1"] = {32,31}
tNpcGossip[17231]["Text1211"] = Thanksgiving2015_Npc_Text[17231]["Text1211"]
tNpcGossip[17231]["Text1212"] = Thanksgiving2015_Npc_Text[17231]["Text1212"]
tNpcGossip[17231]["Text1213"] = Thanksgiving2015_Npc_Text[17231]["Text1213"]
tNpcGossip[17231]["Option32"] = Thanksgiving2015_Npc_Text[17231]["Option32"]
tNpcGossip[17231]["OptionFunc32"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17226"

--火鸡总动员活动。
tNpcGossip[17231]["Text13-1"] = {1311,1312,1313,1314}
tNpcGossip[17231]["tOption13-1"] = {33,31}
tNpcGossip[17231]["Text1311"] = Thanksgiving2015_Npc_Text[17231]["Text1311"]
tNpcGossip[17231]["Text1312"] = Thanksgiving2015_Npc_Text[17231]["Text1312"]
tNpcGossip[17231]["Text1313"] = Thanksgiving2015_Npc_Text[17231]["Text1313"]
tNpcGossip[17231]["Text1314"] = Thanksgiving2015_Npc_Text[17231]["Text1314"]
tNpcGossip[17231]["Option33"] = Thanksgiving2015_Npc_Text[17231]["Option33"]
tNpcGossip[17231]["OptionFunc33"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17224"

--蔓越莓竞赛活动。
tNpcGossip[17231]["Text14-1"] = {1411,1412,1413}
tNpcGossip[17231]["tOption14-1"] = {34,31}
tNpcGossip[17231]["Text1411"] = Thanksgiving2015_Npc_Text[17231]["Text1411"]
tNpcGossip[17231]["Text1412"] = Thanksgiving2015_Npc_Text[17231]["Text1412"]
tNpcGossip[17231]["Text1413"] = Thanksgiving2015_Npc_Text[17231]["Text1413"]
tNpcGossip[17231]["Option34"] = Thanksgiving2015_Npc_Text[17231]["Option34"]
tNpcGossip[17231]["OptionFunc34"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17176"

--敲宝箱活动。
tNpcGossip[17231]["Text15-1"] = {1511,1512,1513}
tNpcGossip[17231]["tOption15-1"] = {35,31}
tNpcGossip[17231]["Text1511"] = Thanksgiving2015_Npc_Text[17231]["Text1511"]
tNpcGossip[17231]["Text1512"] = Thanksgiving2015_Npc_Text[17231]["Text1512"]
tNpcGossip[17231]["Text1513"] = Thanksgiving2015_Npc_Text[17231]["Text1513"]
tNpcGossip[17231]["Option35"] = Thanksgiving2015_Npc_Text[17231]["Option35"]
tNpcGossip[17231]["OptionFunc35"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17095"

--猩猩投果子活动。
tNpcGossip[17231]["Text16-1"] = {1611,1612,1613}
tNpcGossip[17231]["tOption16-1"] = {36,31}
tNpcGossip[17231]["Text1611"] = Thanksgiving2015_Npc_Text[17231]["Text1611"]
tNpcGossip[17231]["Text1612"] = Thanksgiving2015_Npc_Text[17231]["Text1612"]
tNpcGossip[17231]["Text1613"] = Thanksgiving2015_Npc_Text[17231]["Text1613"]
tNpcGossip[17231]["Option36"] = Thanksgiving2015_Npc_Text[17231]["Option36"]
tNpcGossip[17231]["OptionFunc36"] = "Thanksgiving2015_Npc_Lead</N>17231</N>17195"

--等级
tNpcGossip[17231]["Text20-1"] = {2011}
tNpcGossip[17231]["tOption20-1"] = {40}
tNpcGossip[17231]["Text2011"] = Thanksgiving2015_Npc_Text[17231]["Text2011"]
tNpcGossip[17231]["Option40"] = Thanksgiving2015_Npc_Text[17231]["Option40"]

--已领取
tNpcGossip[17231]["Text20-2"] = {2021}
tNpcGossip[17231]["tOption20-2"] = {41}
tNpcGossip[17231]["Text2021"] = Thanksgiving2015_Npc_Text[17231]["Text2021"]
tNpcGossip[17231]["Option41"] = Thanksgiving2015_Npc_Text[17231]["Option41"]

--背包
tNpcGossip[17231]["Text20-3"] = {2031}
tNpcGossip[17231]["tOption20-3"] = {42}
tNpcGossip[17231]["Text2031"] = Thanksgiving2015_Npc_Text[17231]["Text2031"]
tNpcGossip[17231]["Option42"] = Thanksgiving2015_Npc_Text[17231]["Option42"]

--未完成
tNpcGossip[17231]["Text20-4"] = {2041}
tNpcGossip[17231]["tOption20-4"] = {43}
tNpcGossip[17231]["Text2041"] = Thanksgiving2015_Npc_Text[17231]["Text2041"]
tNpcGossip[17231]["Option43"] = Thanksgiving2015_Npc_Text[17231]["Option43"]

--领取奖励
tNpcGossip[17231]["Text20-5"] = {2051}
tNpcGossip[17231]["tOption20-5"] = {44}
tNpcGossip[17231]["Text2051"] = Thanksgiving2015_Npc_Text[17231]["Text2051"]
tNpcGossip[17231]["Option44"] = Thanksgiving2015_Npc_Text[17231]["Option44"]

------------------物品

-- tItem[3004937] = tItem[3004937] or {}
-- tItem[3004937]["Function"] = function(nItemId,sItemName)
	-- local nItemId = tThanksgiving2015_Npc_Data["Cranberry"]

	-- local sStr1 = Thanksgiving2015_Npc_Text["MessageBox3"]
	-- local sStr2 = Thanksgiving2015_Npc_Text["MessageBox4"]

    -- if not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"]) then
		-- Item_DelItem(nItemId)
		-- User_TalkChannel2005("sStr1")	
	-- else
		-- local nEvent = tThanksgiving2015_Npc_Stc["Cranberry"]["EventType"]
		-- local nType = tThanksgiving2015_Npc_Stc["Cranberry"]["DataType"]
		-- local nTime = tThanksgiving2015_Npc_Data["BlessTime"]
		-- local nData = Get_UserStatisticValue(nEvent,nType) or 0
		
		-- if not (nData >= tThanksgiving2015_Npc_Stc["Cranberry"]["Complete"]) then
			-- User_TalkChannel2005("22")	
		-- else
			-- User_TalkChannel2005("33")	
			-- Task_SetStatistic(nEvent,nType,tThanksgiving2015_Npc_Stc["Cranberry"]["Complete"],1) 
			-- User_TalkChannel2005("34")
			-- User_AddBless(nTime)
			-- User_TalkChannel2005("35")
			
			-- tItem[3004937]["Text1-1"] = {111,112,113}
			-- tItem[3004937]["Text111"] = Thanksgiving2015_Npc_Text[3004937]["111"]
			-- tItem[3004937]["Text112"] = Thanksgiving2015_Npc_Text[3004937]["112"]
			-- tItem[3004937]["Text113"] = Thanksgiving2015_Npc_Text[3004937]["113"]
			-- tItem[3004937]["tOption1-1"] = {1}
			

			-- User_TalkChannel2005("44")
		-- end
	-- end		
-- end

tItem[3004937] = tItem[3004937] or {}
tItem[3004937]["Text1-1"] = {111,112,113}
tItem[3004937]["Text111"] = Thanksgiving2015_Npc_Text[3004937]["111"]
tItem[3004937]["Text112"] = Thanksgiving2015_Npc_Text[3004937]["112"]
tItem[3004937]["Text113"] = Thanksgiving2015_Npc_Text[3004937]["113"]
tItem[3004937]["tOption1-1"] = {1}
tItem[3004937]["Option1"] = Thanksgiving2015_Npc_Text[3004937]["Option1"]
tItem[3004937]["OptionFunc1"]="Thanksgiving2015_Npc_Lead</N>3004937</N>17231"
tItem[3004937]["ChkFunc1-1"] = function ()
	local nItemId = tThanksgiving2015_Npc_Data["Cranberry"]
	local sStr1 = Thanksgiving2015_Npc_Text["MessageBox3"]
	local sStr2 = Thanksgiving2015_Npc_Text["MessageBox4"]

    if not Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"]) then
		Item_DelItem(nItemId)
		
	else
		local nEvent = tThanksgiving2015_Npc_Stc["Cranberry"]["EventType"]
		local nType = tThanksgiving2015_Npc_Stc["Cranberry"]["DataType"]
		local nTime = tThanksgiving2015_Npc_Data["BlessTime"]
		local nData = Get_UserStatisticValue(nEvent,nType) or 0

		if (nData >= tThanksgiving2015_Npc_Stc["Cranberry"]["Complete"]) then
			User_TalkChannel2005(sStr2)	
		else
			Task_SetStatistic(nEvent,nType,tThanksgiving2015_Npc_Stc["Cranberry"]["Complete"],1) 
			User_AddBless(nTime)
			User_EffectAdd("self",tThanksgiving2015_Npc_Data["Effect"])	

		end	
	end
	
	return Sys_ChkFullTime(tThanksgiving2015_Npc_Data["Time"]["During"])
end

tItem[3004937]["Text1-2"] = {121}
tItem[3004937]["Text121"] = Thanksgiving2015_Npc_Text[3004937]["121"]
tItem[3004937]["tOption1-2"] = {2}
tItem[3004937]["Option2"] = Thanksgiving2015_Npc_Text[3004937]["Option2"]





