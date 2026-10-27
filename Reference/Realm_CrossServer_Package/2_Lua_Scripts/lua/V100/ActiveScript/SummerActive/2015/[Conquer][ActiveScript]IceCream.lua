------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]2015暑期活动之畅销冷饮(7.9-7.22)
--Creator: 		张世超
--Created:		2015/05/06
------------------------------------------------------------------------------------
-- 命名前缀
-- SummerActive2015IceCream_
-- logID 10001944

--活动时间
local tSummerActive2015IceCream_Time = {}
tSummerActive2015IceCream_Time["Beftime"] = "2014-01-01 00:00 2015-07-08 23:59"
tSummerActive2015IceCream_Time["Nowtime"] = "2015-07-09 00:00 2015-07-22 23:59"

--玩家等级要求
tSummerActive2015IceCream_Condition={}
tSummerActive2015IceCream_Condition["Metempsychosis"] = 0
tSummerActive2015IceCream_Condition["Level"] = 80

--收集物品id、数量、间隔时间、背包空间
tSummerActive2015IceCream_Condition["CollectItem"] = 711762
tSummerActive2015IceCream_Condition["CollectNum"] = 1
tSummerActive2015IceCream_Condition["CollectTime"] = 60
tSummerActive2015IceCream_Condition["NeedSpace"] = 1
tSummerActive2015IceCream_Condition["Distance"] = 3

--采集点寻路坐标
tSummerActive2015IceCream_Condition["MapId"] = 1002
tSummerActive2015IceCream_Condition["Cellx"] = 255
tSummerActive2015IceCream_Condition["Celly"] = 376


--采集npc分组
tSummerActive2015IceCream_Condition["Move"] = {}
tSummerActive2015IceCream_Condition["Move"]["Group1"] = {15814,15818,15822,15826,1002,253,370}
tSummerActive2015IceCream_Condition["Move"]["Group2"] = {15815,15819,15823,15827,1002,251,379}
tSummerActive2015IceCream_Condition["Move"]["Group3"] = {15816,15820,15824,15828,1002,256,386}
tSummerActive2015IceCream_Condition["Move"]["Group4"] = {15817,15821,15825,15829,1002,253,363}

tSummerActive2015IceCream_Condition["FestivalId"] = 3432
tSummerActive2015IceCream_Condition["LogId"] = 10001944

--活动掩码 
--掩码 11523 记录玩家完成任务次数
--掩码 11524 11526~11528 记录玩家采集时间戳
--
--
local tSummerActive2015IceCream_Stc = {}
tSummerActive2015IceCream_Stc[15813]={}
tSummerActive2015IceCream_Stc[15813]["EventType"] = 115
tSummerActive2015IceCream_Stc[15813]["DataType"] = 23
tSummerActive2015IceCream_Stc[15813]["New"] = 0
tSummerActive2015IceCream_Stc[15813]["Process"] = 1
tSummerActive2015IceCream_Stc[15813]["Complete"] = 2

--桔梗花（蓝）采集掩码
tSummerActive2015IceCream_Stc[15826]={}
tSummerActive2015IceCream_Stc[15826]["EventType"] = 115
tSummerActive2015IceCream_Stc[15826]["DataType"] = 24
tSummerActive2015IceCream_Stc[15826]["Collect"] = 1

tSummerActive2015IceCream_Stc[15827]={}
tSummerActive2015IceCream_Stc[15827]["EventType"] = 115
tSummerActive2015IceCream_Stc[15827]["DataType"] = 26
tSummerActive2015IceCream_Stc[15827]["Collect"] = 1

tSummerActive2015IceCream_Stc[15828]={}
tSummerActive2015IceCream_Stc[15828]["EventType"] = 115
tSummerActive2015IceCream_Stc[15828]["DataType"] = 27
tSummerActive2015IceCream_Stc[15828]["Collect"] = 1

tSummerActive2015IceCream_Stc[15829]={}
tSummerActive2015IceCream_Stc[15829]["EventType"] = 115
tSummerActive2015IceCream_Stc[15829]["DataType"] = 28
tSummerActive2015IceCream_Stc[15829]["Collect"] = 1



-- log表
local tSummerActive2015IceCream_Log = {}
tSummerActive2015IceCream_Log["CollectItem1"] = "0,0,0,0,10001944,2,711762,1"					--获得了1片蓝色桔梗花瓣
tSummerActive2015IceCream_Log["CollectItem2"] = "0,0,0,0,10001944,2,711762,2"					--获得了2片蓝色桔梗花瓣

--移出npc函数
function SummerActive2015_IceCream_MoveOut()
	Npc_MoveNpcPos(15814,5000,99,99)
	Npc_MoveNpcPos(15815,5000,99,99)
	Npc_MoveNpcPos(15816,5000,99,99)
	Npc_MoveNpcPos(15817,5000,99,99)
	Npc_MoveNpcPos(15818,5000,99,99)
	Npc_MoveNpcPos(15819,5000,99,99)
	Npc_MoveNpcPos(15820,5000,99,99)
	Npc_MoveNpcPos(15821,5000,99,99)
	Npc_MoveNpcPos(15822,5000,99,99)
	Npc_MoveNpcPos(15823,5000,99,99)
	Npc_MoveNpcPos(15824,5000,99,99)
	Npc_MoveNpcPos(15825,5000,99,99)
	Npc_MoveNpcPos(15826,5000,99,99)
	Npc_MoveNpcPos(15827,5000,99,99)
	Npc_MoveNpcPos(15828,5000,99,99)
	Npc_MoveNpcPos(15829,5000,99,99)

	if Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) then 
		local nRandom = 0
		local nNpcId = 0
		local nMapId = 0
		local nPosX = 0
		local nPosY = 0
	
		nRandom = math.random(1,4)
		nNpcId = tSummerActive2015IceCream_Condition["Move"]["Group1"][nRandom]
		nMapId = tSummerActive2015IceCream_Condition["Move"]["Group1"][5]
		nPosX = tSummerActive2015IceCream_Condition["Move"]["Group1"][6]
		nPosY = tSummerActive2015IceCream_Condition["Move"]["Group1"][7]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
	
		nRandom = math.random(1,4)
		nNpcId = tSummerActive2015IceCream_Condition["Move"]["Group2"][nRandom]
		nMapId = tSummerActive2015IceCream_Condition["Move"]["Group2"][5]
		nPosX = tSummerActive2015IceCream_Condition["Move"]["Group2"][6]
		nPosY = tSummerActive2015IceCream_Condition["Move"]["Group2"][7]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
	
		nRandom = math.random(1,4)
		nNpcId = tSummerActive2015IceCream_Condition["Move"]["Group3"][nRandom]
		nMapId = tSummerActive2015IceCream_Condition["Move"]["Group3"][5]
		nPosX = tSummerActive2015IceCream_Condition["Move"]["Group3"][6]
		nPosY = tSummerActive2015IceCream_Condition["Move"]["Group3"][7]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
	
		nRandom = math.random(1,4)
		nNpcId = tSummerActive2015IceCream_Condition["Move"]["Group4"][nRandom]
		nMapId = tSummerActive2015IceCream_Condition["Move"]["Group4"][5]
		nPosX = tSummerActive2015IceCream_Condition["Move"]["Group4"][6]
		nPosY = tSummerActive2015IceCream_Condition["Move"]["Group4"][7]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
	end
end	

--获得奖励
-- function SummerActive2015_IceCream_Gift(nNpcId)
	-- local nEvent = tSummerActive2015IceCream_Stc[15813]["EventType"]
	-- local nType = tSummerActive2015IceCream_Stc[15813]["DataType"]	
	-- local nMetempsychosis = tSummerActive2015IceCream_Condition["Metempsychosis"]
	
	-- Task_SetStatistic(nEvent,nType,tSummerActive2015IceCream_Stc[15813]["Complete"],1)
	-- Task_SetStcTimestamp(nEvent,nType,0)
	-- if nMetempsychosis >= 2 then
		-- Item_AddItem(tSummerActive2015IceCream_Condition["GiftMetempsychosis2"])
		-- Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["GiftMetempsychosis2"])
	-- elseif 	nMetempsychosis == 1 then
		-- Item_AddItem(tSummerActive2015IceCream_Condition["GiftMetempsychosis1"])
		-- Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["GiftMetempsychosis1"])
	-- else
		-- Item_AddItem(tSummerActive2015IceCream_Condition["GiftMetempsychosis0"])
		-- Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["GiftMetempsychosis0"])
	-- end
	-- Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox1"])
	-- User_EffectAdd("self","angelwing")
	
-- end

--上交蓝色桔梗花瓣。
function SummerActive2015_IceCream_HandIn(nNpcId)
	local nCollectItem = tSummerActive2015IceCream_Condition["CollectItem"]
	local nNum = tSummerActive2015IceCream_Condition["CollectNum"]
	local nEvent = tSummerActive2015IceCream_Stc[15813]["EventType"]
	local nType = tSummerActive2015IceCream_Stc[15813]["DataType"]	
	local nValue = 0
	nValue = Get_UserStatisticValue(nEvent,nType)
	
	if not Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) then 
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end	
	
	if nValue == tSummerActive2015IceCream_Stc[15813]["Complete"] then
		if not Task_StcInterval(nEvent,nType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"3-4")
			return
		end
	end

	if Item_ChkMulItem(nCollectItem,nCollectItem,nNum) then 
		Item_DelMulItem(nCollectItem,nCollectItem,nNum)
		
		Task_SetStatistic(nEvent,nType,tSummerActive2015IceCream_Stc[15813]["Complete"],1)
		Task_SetStcTimestamp(nEvent,nType,0)
		
		FestivalGeneralPackage_GetGift(tSummerActive2015IceCream_Condition["FestivalId"],tSummerActive2015IceCream_Condition["LogId"])
		
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox1"])
		User_EffectAdd("self","angelwing")
		return
	else
		LinkNpcGossipFunc_New(nNpcId,"3-5")
	end
end

--npc寻路
function SummerActive2015_IceCream_Back(nNpcId)
	local nMapId = Get_NpcMapID(nNpcId)
	local nCellx = Get_NpcPositionX(nNpcId)
	local nCelly = Get_NpcPositionY(nNpcId)
	Sys_GotoSomeWhere(nCellx,nCelly,nMapId,nNpcId)
end	

--采集点寻路
function SummerActive2015_IceCream_Guide(nNpcId)
	local nMapId = tSummerActive2015IceCream_Condition["MapId"]
	local nCellx = tSummerActive2015IceCream_Condition["Cellx"]
	local nCelly = tSummerActive2015IceCream_Condition["Celly"]
	if not Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) then 
		return
	end
	Sys_GotoSomeWhere(nCellx,nCelly,nMapId)
	User_TalkChannel2005(tSummerActive2015_IceCream_Text[15813]["MsgBox2"])
end

--我要帮忙
function SummerActive2015_IceCream_Help(nNpcId)
	local nLevel = tSummerActive2015IceCream_Condition["Level"]
	local nMetempsychosis = tSummerActive2015IceCream_Condition["Metempsychosis"]
	local nEvent = tSummerActive2015IceCream_Stc[15813]["EventType"]
	local nType = tSummerActive2015IceCream_Stc[15813]["DataType"]	
	local nValues = 0
	
	nValue = Get_UserStatisticValue(nEvent,nType)

	if not Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) then 
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then 
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	if nValue == tSummerActive2015IceCream_Stc[15813]["New"] then
		Task_SetStatistic(nEvent,nType,tSummerActive2015IceCream_Stc[15813]["Process"],1)
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return		
	elseif nValue == tSummerActive2015IceCream_Stc[15813]["Process"] then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return		
	elseif Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,tSummerActive2015IceCream_Stc[15813]["Process"],1)
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	else 
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
end

--采集函数
function SummerActive2015_IceCream_Collection()
	local nNpcId = Get_NpcId()

	if not Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox1"])
		return
	end
	if Item_ChkMulItem(tSummerActive2015IceCream_Condition["CollectItem"],tSummerActive2015IceCream_Condition["CollectItem"],tSummerActive2015IceCream_Condition["CollectNum"]) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox2"],"SummerActive2015_IceCream_Back</N>15813")
		return
	end
	if not User_CheckLeftSpace(tSummerActive2015IceCream_Condition["NeedSpace"]) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox3"])
		return
	end
	if not SummerActive2015_IceCream_CheckDistance(nNpcId) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox4"])
		return
	end
	if not SummerActive2015_IceCream_CheckTime(nNpcId) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox5"])
		return
	end	
	SummerActive2015_IceCream_GetItem(nNpcId)
end

--检测采集距离
function SummerActive2015_IceCream_CheckDistance(nNpcId)
	local nDistance = tSummerActive2015IceCream_Condition["Distance"]
	local nNpcPositionX = Get_NpcPositionX(nNpcId)
	local nNpcPositionY = Get_NpcPositionY(nNpcId)
	local nUserPositionX = Get_UserPositionX()
	local nUserPositionY = Get_UserPositionY()
	local nDistanceX = 0
	local nDistanceY = 0
	nDistanceX = math.abs(nNpcPositionX-nUserPositionX)
	nDistanceY = math.abs(nNpcPositionY-nUserPositionY)
	if nDistanceX > nDistance or nDistanceY > nDistance then
		return false
	else
		return true
	end
end

--检测采集时间间隔
function SummerActive2015_IceCream_CheckTime(nNpcId)

	local nEvent = tSummerActive2015IceCream_Stc[nNpcId]["EventType"]
	local nType = tSummerActive2015IceCream_Stc[nNpcId]["DataType"]
	local nValue = 0
	local nTime = tSummerActive2015IceCream_Condition["CollectTime"]
	nValue = Get_UserStatisticValue(nEvent,nType)
	
	if nValue == 0 or nValue == nil then
		return true
	elseif 	Task_StcInterval(nEvent,nType,nTime,0)	then
		return true
	else
		return false
	end
end

--获得花瓣
function SummerActive2015_IceCream_GetItem(nNpcId)
	local nEvent = tSummerActive2015IceCream_Stc[nNpcId]["EventType"]
	local nType = tSummerActive2015IceCream_Stc[nNpcId]["DataType"]
	local nCollect = tSummerActive2015IceCream_Stc[nNpcId]["Collect"]
	local nCollectItem = tSummerActive2015IceCream_Condition["CollectItem"]
	local nNum = tSummerActive2015IceCream_Condition["CollectNum"]
	Task_SetStatistic(nEvent,nType,nCollect,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	Item_AddItem(nCollectItem)
	Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["CollectItem1"])
	User_EffectAdd("self","angelwing")	
	
	-- local nRandom = math.random(0,9)
	-- if nRandom <= 6 or Item_ChkMulItem(nCollectItem,nCollectItem,nNum-1) then 
		-- Item_AddItem(nCollectItem)
		-- Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox6"])
		-- Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["CollectItem1"])
		-- User_EffectAdd("self","angelwing")
	-- else
		-- Item_AddItem(nCollectItem)
		-- Item_AddItem(nCollectItem)
		-- Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox7"])
		-- Sys_SaveActionFestivalLog(tSummerActive2015IceCream_Log["CollectItem2"])
		-- User_EffectAdd("self","angelwing")
	-- end
	
	if Item_ChkMulItem(nCollectItem,nCollectItem,nNum) then 
		Sys_MsgBox(tSummerActive2015_IceCream_Text[nNpcId]["MsgBox2"],"SummerActive2015_IceCream_Back</N>15813")
		return
	end
end	


--------------------------------------NPC模块-------------------------------------------
-- NPC头像
tNpcFace[2508] = 119


tNpcGossip[15814] = tNpcGossip[15814] or DefaultNpc:new{}
tNpcGossip[15818] = tNpcGossip[15818] or DefaultNpc:new{}
tNpcGossip[15822] = tNpcGossip[15822] or DefaultNpc:new{}
tNpcGossip[15826] = tNpcGossip[15826] or DefaultNpc:new{}
tNpcGossip[15813] = tNpcGossip[15813] or DefaultNpc:new{}

tNpcGossip[15814]["OptionHidden"] = 1
tNpcGossip[15818]["OptionHidden"] = 1
tNpcGossip[15822]["OptionHidden"] = 1
tNpcGossip[15826]["OptionHidden"] = 1
tNpcGossip[15813]["OptionHidden"] = 1


tNpcGossip[15814]["Text1-1"] = {111}
tNpcGossip[15814]["tOption1-1"] = {1}
tNpcGossip[15814]["Text111"] = tSummerActive2015_IceCream_Text[15814]["Text111"]
tNpcGossip[15814]["Option1"] = tSummerActive2015_IceCream_Text[15814]["Option1"]


tNpcGossip[15818]["Text1-1"] = {111}
tNpcGossip[15818]["tOption1-1"] = {1}
tNpcGossip[15818]["Text111"] = tSummerActive2015_IceCream_Text[15818]["Text111"]
tNpcGossip[15818]["Option1"] = tSummerActive2015_IceCream_Text[15818]["Option1"]


tNpcGossip[15822]["Text1-1"] = {111}
tNpcGossip[15822]["tOption1-1"] = {1}
tNpcGossip[15822]["Text111"] = tSummerActive2015_IceCream_Text[15822]["Text111"]
tNpcGossip[15822]["Option1"] = tSummerActive2015_IceCream_Text[15822]["Option1"]


tNpcGossip[15826]["Text1-1"] = {111,112}
tNpcGossip[15826]["tOption1-1"] = {1,2}
tNpcGossip[15826]["Text111"] = tSummerActive2015_IceCream_Text[15826]["Text111"]
tNpcGossip[15826]["Text112"] = tSummerActive2015_IceCream_Text[15826]["Text112"]
tNpcGossip[15826]["Option1"] = tSummerActive2015_IceCream_Text[15826]["Option1"]
tNpcGossip[15826]["Option2"] = tSummerActive2015_IceCream_Text[15826]["Option2"]
tNpcGossip[15826]["OptionFunc1"] = "SummerActive2015_IceCream_Collection"

tNpcGossip[15826]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"]) and Task_ChkStcValue(tSummerActive2015IceCream_Stc[15813]["EventType"],tSummerActive2015IceCream_Stc[15813]["DataType"],"==",tSummerActive2015IceCream_Stc[15813]["Process"])
end

tNpcGossip[15826]["Text1-2"] = {121}
tNpcGossip[15826]["tOption1-2"] = {10}
tNpcGossip[15826]["Text121"] = tSummerActive2015_IceCream_Text[15826]["Text121"]
tNpcGossip[15826]["Option10"] = tSummerActive2015_IceCream_Text[15826]["Option10"]


--冰淇淋女孩安妮 活动前对白
tNpcGossip[15813]["Text1-1"] = {111,112,113,114}
tNpcGossip[15813]["tOption1-1"] = {1}
tNpcGossip[15813]["Text111"] = tSummerActive2015_IceCream_Text[15813]["Text111"]
tNpcGossip[15813]["Text112"] = tSummerActive2015_IceCream_Text[15813]["Text112"]
tNpcGossip[15813]["Text113"] = tSummerActive2015_IceCream_Text[15813]["Text113"]
tNpcGossip[15813]["Text114"] = tSummerActive2015_IceCream_Text[15813]["Text114"]
tNpcGossip[15813]["Option1"] = tSummerActive2015_IceCream_Text[15813]["Option1"]
tNpcGossip[15813]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummerActive2015IceCream_Time["Beftime"])
end

--冰淇淋女孩安妮 活动后对白
tNpcGossip[15813]["Text1-2"] = {121,122}
tNpcGossip[15813]["tOption1-2"] = {2}
tNpcGossip[15813]["Text121"] = tSummerActive2015_IceCream_Text[15813]["Text121"]
tNpcGossip[15813]["Text122"] = tSummerActive2015_IceCream_Text[15813]["Text122"]
tNpcGossip[15813]["Option2"] = tSummerActive2015_IceCream_Text[15813]["Option2"]
tNpcGossip[15813]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tSummerActive2015IceCream_Time["Nowtime"])
end

--冰淇淋女孩安妮 活动对白
tNpcGossip[15813]["Text1-3"] = {131,132,133}
tNpcGossip[15813]["tOption1-3"] = {3,4,5,6}
tNpcGossip[15813]["Text131"] = tSummerActive2015_IceCream_Text[15813]["Text131"]
tNpcGossip[15813]["Text132"] = tSummerActive2015_IceCream_Text[15813]["Text132"]
tNpcGossip[15813]["Text133"] = tSummerActive2015_IceCream_Text[15813]["Text133"]
tNpcGossip[15813]["Option3"] = tSummerActive2015_IceCream_Text[15813]["Option3"]
tNpcGossip[15813]["Option4"] = tSummerActive2015_IceCream_Text[15813]["Option4"]
tNpcGossip[15813]["Option5"] = tSummerActive2015_IceCream_Text[15813]["Option5"]
tNpcGossip[15813]["Option6"] = tSummerActive2015_IceCream_Text[15813]["Option6"]
tNpcGossip[15813]["OptionFunc3"] = "SummerActive2015_IceCream_Help</N>15813"
tNpcGossip[15813]["OptionFunc4"] = "SummerActive2015_IceCream_HandIn</N>15813"
tNpcGossip[15813]["OptionPoint5"] = "2"

tNpcGossip[15813]["OptionChkFunc4"] = function ()
	return (Get_UserStatisticValue(tSummerActive2015IceCream_Stc[15813]["EventType"],tSummerActive2015IceCream_Stc[15813]["DataType"]) == tSummerActive2015IceCream_Stc[15813]["Process"])
end

--了解活动详情。
tNpcGossip[15813]["Text2-1"] = {211,212,213,214}
tNpcGossip[15813]["tOption2-1"] = {7}
tNpcGossip[15813]["Text211"] = tSummerActive2015_IceCream_Text[15813]["Text211"]
tNpcGossip[15813]["Text212"] = tSummerActive2015_IceCream_Text[15813]["Text212"]
tNpcGossip[15813]["Text213"] = tSummerActive2015_IceCream_Text[15813]["Text213"]
tNpcGossip[15813]["Text214"] = tSummerActive2015_IceCream_Text[15813]["Text214"]
tNpcGossip[15813]["Option7"] = tSummerActive2015_IceCream_Text[15813]["Option7"]


--等级判定	
tNpcGossip[15813]["Text3-1"] = {311,312}
tNpcGossip[15813]["tOption3-1"] = {10}
tNpcGossip[15813]["Text311"] = tSummerActive2015_IceCream_Text[15813]["Text311"]
tNpcGossip[15813]["Text312"] = tSummerActive2015_IceCream_Text[15813]["Text312"]
tNpcGossip[15813]["Option10"] = tSummerActive2015_IceCream_Text[15813]["Option10"]	

--接任务
tNpcGossip[15813]["Text3-2"] = {321,322}
tNpcGossip[15813]["tOption3-2"] = {11}
tNpcGossip[15813]["Text321"] = tSummerActive2015_IceCream_Text[15813]["Text321"]
tNpcGossip[15813]["Text322"] = tSummerActive2015_IceCream_Text[15813]["Text322"]
tNpcGossip[15813]["Option11"] = tSummerActive2015_IceCream_Text[15813]["Option11"]
tNpcGossip[15813]["OptionFunc11"] = "SummerActive2015_IceCream_Guide</N>15813"

--已接任务未上交
tNpcGossip[15813]["Text3-3"] = {331}
tNpcGossip[15813]["tOption3-3"] = {12}
tNpcGossip[15813]["Text331"] = tSummerActive2015_IceCream_Text[15813]["Text331"]
tNpcGossip[15813]["Option12"] = tSummerActive2015_IceCream_Text[15813]["Option12"]
tNpcGossip[15813]["OptionFunc12"] = "SummerActive2015_IceCream_Guide</N>15813"

--当天已完成
tNpcGossip[15813]["Text3-4"] = {341}
tNpcGossip[15813]["tOption3-4"] = {13}
tNpcGossip[15813]["Text341"] = tSummerActive2015_IceCream_Text[15813]["Text341"]
tNpcGossip[15813]["Option13"] = tSummerActive2015_IceCream_Text[15813]["Option13"]

--数量不足
tNpcGossip[15813]["Text3-5"] = {351}
tNpcGossip[15813]["tOption3-5"] = {14}
tNpcGossip[15813]["Text351"] = tSummerActive2015_IceCream_Text[15813]["Text351"]
tNpcGossip[15813]["Option14"] = tSummerActive2015_IceCream_Text[15813]["Option14"]


tNpcGossip[15815] = tNpcGossip[15814] or DefaultNpc:new{}
tNpcGossip[15816] = tNpcGossip[15814] or DefaultNpc:new{}
tNpcGossip[15817] = tNpcGossip[15814] or DefaultNpc:new{}

tNpcGossip[15819] = tNpcGossip[15818] or DefaultNpc:new{}
tNpcGossip[15820] = tNpcGossip[15818] or DefaultNpc:new{}
tNpcGossip[15821] = tNpcGossip[15818] or DefaultNpc:new{}

tNpcGossip[15823] = tNpcGossip[15822] or DefaultNpc:new{}
tNpcGossip[15824] = tNpcGossip[15822] or DefaultNpc:new{}
tNpcGossip[15825] = tNpcGossip[15822] or DefaultNpc:new{}

tNpcGossip[15827] = tNpcGossip[15826] or DefaultNpc:new{}
tNpcGossip[15828] = tNpcGossip[15826] or DefaultNpc:new{}
tNpcGossip[15829] = tNpcGossip[15826] or DefaultNpc:new{}

-- 时间自检触发
 -- tSystem_Prompet_Func = tSystem_Prompet_Func or {}
 -- table.insert(tSystem_Prompet_Func,SummerActive2015_IceCream_MoveOut)