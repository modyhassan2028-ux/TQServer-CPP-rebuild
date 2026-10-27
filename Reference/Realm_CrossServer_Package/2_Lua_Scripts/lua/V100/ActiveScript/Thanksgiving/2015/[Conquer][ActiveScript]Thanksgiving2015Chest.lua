------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]感恩节活动之敲宝箱
--Creator:		张世超
--Created:		2015/08/25
------------------------------------------------------------------------------------
--前缀 Thanksgiving2015_Chest_

---------------------------------table定义--------------------------------------
local tThanksgiving2015_Chest_Data = {}
--活动时间
	tThanksgiving2015_Chest_Data["Time"] = {}
	-- tThanksgiving2015_Chest_Data["Time"]["Before"] = "2015-01-01 00:00 2015-08-28 23:59"
	-- tThanksgiving2015_Chest_Data["Time"]["During"] = "2015-08-29 00:00 2015-11-30 23:59"
	tThanksgiving2015_Chest_Data["Time"]["Before"] = "2015-01-01 00:00 2015-11-23 23:59"
	tThanksgiving2015_Chest_Data["Time"]["During"] = "2015-11-24 00:00 2015-11-30 23:59"
	
--等级限制
	tThanksgiving2015_Chest_Data["Space"] = 1

	tThanksgiving2015_Chest_Data["Level"] = 80
	tThanksgiving2015_Chest_Data["Metempsychosis"] = 0
--福地地图
	tThanksgiving2015_Chest_Data["Warehouse"] = {}	
	tThanksgiving2015_Chest_Data["Twinscity"] = {}	
	tThanksgiving2015_Chest_Data["Warehouse"]["MapId"] = 3866	
	tThanksgiving2015_Chest_Data["Warehouse"]["BoundX"] = 58	
	tThanksgiving2015_Chest_Data["Warehouse"]["BoundY"] = 56	
	tThanksgiving2015_Chest_Data["Warehouse"]["BoundCX"] = 5	
	tThanksgiving2015_Chest_Data["Warehouse"]["BoundCY"] = 5
	tThanksgiving2015_Chest_Data["Warehouse"]["Check"] = 1	
--双龙城
	tThanksgiving2015_Chest_Data["Twinscity"]["MapId"] = 1002	
	tThanksgiving2015_Chest_Data["Twinscity"]["BoundX"] = 285	
	tThanksgiving2015_Chest_Data["Twinscity"]["BoundY"] = 369	
	tThanksgiving2015_Chest_Data["Twinscity"]["BoundCX"] = 5	
	tThanksgiving2015_Chest_Data["Twinscity"]["BoundCY"] = 5
	tThanksgiving2015_Chest_Data["Twinscity"]["Check"] = 1	
	tThanksgiving2015_Chest_Data["Twinscity"]["Effect"] = "angelwing"	
	
	
	
--log
local tThanksgiving2015_Chest_Log = {}
tThanksgiving2015_Chest_Log["Festival"] = 3330
tThanksgiving2015_Chest_Log["Id"] = 10002316
tThanksgiving2015_Chest_Log["MoveIn"] = "0,0,0,0,10002316,1,0,0"
tThanksgiving2015_Chest_Log["Complete"] = "0,0,0,0,10002316,3,0,0"

--掩码
-- #stc(128,93)记录杀怪次数，10表示已经打到节日礼包
local tThanksgiving2015_Chest_Stc = {}
tThanksgiving2015_Chest_Stc["Chest"] = {}
tThanksgiving2015_Chest_Stc["Chest"]["EventType"] = 128
tThanksgiving2015_Chest_Stc["Chest"]["DataType"] = 93
tThanksgiving2015_Chest_Stc["Chest"]["Complete"] = 100
tThanksgiving2015_Chest_Stc["Chest"]["MaxTime"] = 3



-- 怪物掉落配置
local tThanksgiving2015_Chest_Monster = {}	
	tThanksgiving2015_Chest_Monster[7589] = {}
	tThanksgiving2015_Chest_Monster[7589][1] = {}
	tThanksgiving2015_Chest_Monster[7589][1]["ItemChanceSum"] = 100000
	tThanksgiving2015_Chest_Monster[7589][1]["Time"] = 1
	
	tThanksgiving2015_Chest_Monster[7589][1][1] = {}
	tThanksgiving2015_Chest_Monster[7589][1][1]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][1]["ItemChance"] = 45000
	tThanksgiving2015_Chest_Monster[7589][1][1]["Item_1"] = 1

	tThanksgiving2015_Chest_Monster[7589][1][2] = {}
	tThanksgiving2015_Chest_Monster[7589][1][2]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][2]["ItemChance"] = 15000
	tThanksgiving2015_Chest_Monster[7589][1][2]["Item_1"] = 2
	
	tThanksgiving2015_Chest_Monster[7589][1][3] = {}
	tThanksgiving2015_Chest_Monster[7589][1][3]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][3]["ItemChance"] = 5000
	tThanksgiving2015_Chest_Monster[7589][1][3]["Item_1"] = 3
	
	tThanksgiving2015_Chest_Monster[7589][1][4] = {}
	tThanksgiving2015_Chest_Monster[7589][1][4]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][4]["ItemChance"] = 10000
	tThanksgiving2015_Chest_Monster[7589][1][4]["Item_1"] = 4	

	tThanksgiving2015_Chest_Monster[7589][1][5] = {}
	tThanksgiving2015_Chest_Monster[7589][1][5]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][5]["ItemChance"] = 10000
	tThanksgiving2015_Chest_Monster[7589][1][5]["Item_1"] = 5	

	tThanksgiving2015_Chest_Monster[7589][1][6] = {}
	tThanksgiving2015_Chest_Monster[7589][1][6]["RandomItemChanceType"] = 2
	tThanksgiving2015_Chest_Monster[7589][1][6]["ItemChance"] = 15000
	tThanksgiving2015_Chest_Monster[7589][1][6]["Item_1"] = 6







---------------------------------逻辑定义--------------------------------------
math.randomseed(os.time())

function tThanksgiving2015_Chest_KillChest1()
		local sStr = Thanksgiving2015_Chest_Text["MessageBox3"]
		Monster_SysDropMoney(1000)
		User_TalkChannel2005(sStr)
end

function tThanksgiving2015_Chest_KillChest2()
		local sStr = Thanksgiving2015_Chest_Text["MessageBox4"]
		Monster_SysDropMoney(5000)
		Monster_SysDropMoney(5000)
		User_TalkChannel2005(sStr)
end	
	
function tThanksgiving2015_Chest_KillChest3()
		local sStr = Thanksgiving2015_Chest_Text["MessageBox5"]
		Monster_SysDropMoney(20000)
		Monster_SysDropMoney(20000)
		Monster_SysDropMoney(20000)
		Monster_SysDropMoney(20000)
		Monster_SysDropMoney(20000)
		User_TalkChannel2005(sStr)
end	
	
function tThanksgiving2015_Chest_KillChest4()
		local nMapId = Get_UserMapId()
		local nPosX = Get_UserPositionX()+math.random(-3,3)
		local nPosY = Get_UserPositionY()+math.random(-3,3)
		local sStr = Thanksgiving2015_Chest_Text["MessageBox6"]
		Monster_AddMonster(nMapId,nPosX,nPosY,17141,20)
		User_TalkChannel2005(sStr)
end	
	
function tThanksgiving2015_Chest_KillChest5()
		local nMapId = Get_UserMapId()
		local nPosX = Get_UserPositionX()+math.random(-3,3)
		local nPosY = Get_UserPositionY()+math.random(-3,3)
		local sStr = Thanksgiving2015_Chest_Text["MessageBox7"]
		Monster_AddMonster(nMapId,nPosX,nPosY,17141,57)
		User_TalkChannel2005(sStr)
end	

function tThanksgiving2015_Chest_KillChest6()
		local nEvent = tThanksgiving2015_Chest_Stc["Chest"]["EventType"] 
		local nType = tThanksgiving2015_Chest_Stc["Chest"]["DataType"]
		local nData = 0
		local sStrNoLeftSpace = Thanksgiving2015_Chest_Text["NoLeftSpace"]
		local sStr = Thanksgiving2015_Chest_Text["MessageBox8"]
		local sLog = tThanksgiving2015_Chest_Log["Complete"] 
		local nMapId = tThanksgiving2015_Chest_Data["Twinscity"]["MapId"] 
		local nBoundX = tThanksgiving2015_Chest_Data["Twinscity"]["BoundX"] 
		local nBoundY = tThanksgiving2015_Chest_Data["Twinscity"]["BoundY"] 
		local nBoundCX = tThanksgiving2015_Chest_Data["Twinscity"]["BoundCX"] 
		local nBoundCY = tThanksgiving2015_Chest_Data["Twinscity"]["BoundCY"] 
		local nCheck = tThanksgiving2015_Chest_Data["Twinscity"]["Check"]
		local nSpaceNum = tThanksgiving2015_Chest_Data["Space"]

		-- if not Task_ChkStatistic(nEvent,nType) then
			-- nData = nData+1
			-- Task_SetStatistic(nEvent,nType,nData,1)
		-- end		
		
		nData = Get_UserStatisticValue(nEvent,nType)
		
		if (nData >= tThanksgiving2015_Chest_Stc["Chest"]["MaxTime"]) then
			if not User_CheckLeftSpace(nSpaceNum) then
				User_TalkChannel2005(sStrNoLeftSpace)
				return
			end
			
			nData = tThanksgiving2015_Chest_Stc["Chest"]["Complete"]
			Task_SetStatistic(nEvent,nType,nData,1) 
			Task_SetStcTimestamp(nEvent,nType,0) 
			Sys_SaveActionLog(sLog)
			User_TalkChannel2005(sStr)
			User_EffectAdd("self",tThanksgiving2015_Chest_Data["Twinscity"]["Effect"])
			User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck)
			FestivalGeneralPackage_GetGift(tThanksgiving2015_Chest_Log["Festival"],tThanksgiving2015_Chest_Log["Id"])
				
		else
			Task_SetStatistic(nEvent,nType,nData,1) 
		end
		
		

end	


-- 1、修复打怪计数的概率
-- 3、背包满的情况下不触发游戏币掉落
--

function tThanksgiving2015_Chest_KillChest(nMonsterId)
	local nSpaceNum = tThanksgiving2015_Chest_Data["Space"]
	local sStrNoLeftSpace = Thanksgiving2015_Chest_Text["NoLeftSpace"]
	
	local nEvent = tThanksgiving2015_Chest_Stc["Chest"]["EventType"] 
	local nType = tThanksgiving2015_Chest_Stc["Chest"]["DataType"]
	
	local nData = 0

	
	if Sys_ChkFullTime(tThanksgiving2015_Chest_Data["Time"]["During"]) then
		if not Task_StcInterval(nEvent,nType,1,4) then
			if Task_ChkStcValue(nEvent,nType,">=",tThanksgiving2015_Chest_Stc["Chest"]["Complete"]) then
				return
			end
		else
			Task_SetStatistic(nEvent,nType,0,1) 
			Task_SetStcTimestamp(nEvent,nType,0)
		end
	end
--背包满的情况下不触发游戏币掉落	
	if not User_CheckLeftSpace(nSpaceNum) then
		User_TalkChannel2005(sStrNoLeftSpace)
		return
	end

--打怪计数	
	if Task_ChkStatistic(nEvent,nType) then
		nData = Get_UserStatisticValue(nEvent,nType)
	end		
	
	nData = nData+1
	Task_SetStatistic(nEvent,nType,nData,1)
	
	if (nData >= tThanksgiving2015_Chest_Stc["Chest"]["MaxTime"]) then
		tThanksgiving2015_Chest_KillChest6()
		return
	end
	
	
	
	local nDouble = 1
	local nTime = tThanksgiving2015_Chest_Monster[nMonsterId][nDouble]["Time"]
	for i = 1,nTime do
		local nFlat,tAward = Probabil_RandomAward(tThanksgiving2015_Chest_Monster[nMonsterId],nDouble)
		local nItem = tAward[1]["tAward"][1]["Item_1"]
		if 	nItem == 1 then
			tThanksgiving2015_Chest_KillChest1()
		elseif nItem == 2 then
			tThanksgiving2015_Chest_KillChest2()
		elseif nItem == 3 then
			tThanksgiving2015_Chest_KillChest3()
		elseif nItem == 4 then
			tThanksgiving2015_Chest_KillChest4()
		elseif nItem == 5 then
			tThanksgiving2015_Chest_KillChest5()
		else
			tThanksgiving2015_Chest_KillChest6()
		end
	end
	
end


function tThanksgiving2015_Chest_Accpect(nNpcId)
	local nEvent = tThanksgiving2015_Chest_Stc["Chest"]["EventType"] 
	local nType = tThanksgiving2015_Chest_Stc["Chest"]["DataType"]
	local nComplete = tThanksgiving2015_Chest_Stc["Chest"]["Complete"]
	local nLevel = tThanksgiving2015_Chest_Data["Level"]
	local nMetempsychosis = tThanksgiving2015_Chest_Data["Metempsychosis"]

	--等级判断
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end	
	--是否已经完成
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		--已完成
		LinkNpcGossipFunc_New(nNpcId,"3-2")
	else
		LinkNpcGossipFunc_New(nNpcId,"3-3")
	end
end

function tThanksgiving2015_Chest_MoveIn(nNpcId)
	local nMapId = tThanksgiving2015_Chest_Data["Warehouse"]["MapId"] 
	local nBoundX = tThanksgiving2015_Chest_Data["Warehouse"]["BoundX"] 
	local nBoundY = tThanksgiving2015_Chest_Data["Warehouse"]["BoundY"] 
	local nBoundCX = tThanksgiving2015_Chest_Data["Warehouse"]["BoundCX"] 
	local nBoundCY = tThanksgiving2015_Chest_Data["Warehouse"]["BoundCY"] 
	local nCheck = tThanksgiving2015_Chest_Data["Warehouse"]["Check"] 
	local sLog = tThanksgiving2015_Chest_Log["MoveIn"]
	local sStr = Thanksgiving2015_Chest_Text["MessageBox1"] 
	
	if not Sys_ChkFullTime(tThanksgiving2015_Chest_Data["Time"]["During"]) then 
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck)
	Sys_SaveActionLog(sLog)
	User_TalkChannel2005(sStr)
end

function tThanksgiving2015_Chest_LeaveOut(nNpcId)
	local nMapId = tThanksgiving2015_Chest_Data["Twinscity"]["MapId"] 
	local nBoundX = tThanksgiving2015_Chest_Data["Twinscity"]["BoundX"] 
	local nBoundY = tThanksgiving2015_Chest_Data["Twinscity"]["BoundY"] 
	local nBoundCX = tThanksgiving2015_Chest_Data["Twinscity"]["BoundCX"] 
	local nBoundCY = tThanksgiving2015_Chest_Data["Twinscity"]["BoundCY"] 
	local nCheck = tThanksgiving2015_Chest_Data["Twinscity"]["Check"] 
	local sStr = Thanksgiving2015_Chest_Text["MessageBox2"] 
	
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck)
	User_TalkChannel2005(sStr)
end

-----------------------------------Npc模板--------------------------------------
tNpcFace[3180] = 34
tNpcGossip[17095] = tNpcGossip[17095] or DefaultNpc:new{}
tNpcGossip[17095]["OptionHidden"] = 1

tNpcGossip[17096] = tNpcGossip[17096] or DefaultNpc:new{}
tNpcGossip[17096]["OptionHidden"] = 1

--活动前
tNpcGossip[17095]["Text1-1"] = {111,112,113,114}
tNpcGossip[17095]["tOption1-1"] = {1}
tNpcGossip[17095]["Text111"] = Thanksgiving2015_Chest_Text[17095]["Text111"]
tNpcGossip[17095]["Text112"] = Thanksgiving2015_Chest_Text[17095]["Text112"]
tNpcGossip[17095]["Text113"] = Thanksgiving2015_Chest_Text[17095]["Text113"]
tNpcGossip[17095]["Text114"] = Thanksgiving2015_Chest_Text[17095]["Text114"]
tNpcGossip[17095]["Option1"] = Thanksgiving2015_Chest_Text[17095]["Option1"]
--函数检查（根据需求使用）
tNpcGossip[17095]["ChkFunc1-1"] = function ()
 return Sys_ChkFullTime(tThanksgiving2015_Chest_Data["Time"]["Before"])
end

--活动时间后
tNpcGossip[17095]["Text1-2"] = {121}
tNpcGossip[17095]["tOption1-2"] = {2}
tNpcGossip[17095]["Text121"] = Thanksgiving2015_Chest_Text[17095]["Text121"]
tNpcGossip[17095]["Option2"] = Thanksgiving2015_Chest_Text[17095]["Option2"]
tNpcGossip[17095]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tThanksgiving2015_Chest_Data["Time"]["During"])
end

--活动时间内
tNpcGossip[17095]["Text1-3"] = {131,132,133,134}
tNpcGossip[17095]["tOption1-3"] = {3,4,5}
tNpcGossip[17095]["Text131"] = Thanksgiving2015_Chest_Text[17095]["Text131"]
tNpcGossip[17095]["Text132"] = Thanksgiving2015_Chest_Text[17095]["Text132"]
tNpcGossip[17095]["Text133"] = Thanksgiving2015_Chest_Text[17095]["Text133"]
tNpcGossip[17095]["Text134"] = Thanksgiving2015_Chest_Text[17095]["Text134"]
tNpcGossip[17095]["Option3"] = Thanksgiving2015_Chest_Text[17095]["Option3"]
tNpcGossip[17095]["Option4"] = Thanksgiving2015_Chest_Text[17095]["Option4"]
tNpcGossip[17095]["Option5"] = Thanksgiving2015_Chest_Text[17095]["Option5"]
tNpcGossip[17095]["OptionFunc3"] = "tThanksgiving2015_Chest_Accpect</N>17095"
tNpcGossip[17095]["OptionPoint4"] = "2"
tNpcGossip[17095]["OptionChkFunc3"] = function ()
	local nEvent = tThanksgiving2015_Chest_Stc["Chest"]["EventType"] 
	local nType = tThanksgiving2015_Chest_Stc["Chest"]["DataType"]
	local nComplete = tThanksgiving2015_Chest_Stc["Chest"]["Complete"]
	if not Task_ChkStatistic(nEvent,nType) then
		return true
	else
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1)  
		end
	end
	
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		return false
	else
		return true
	end
end

--怎么瓜分来着？
tNpcGossip[17095]["Text2-1"] = {211,212,213}
tNpcGossip[17095]["tOption2-1"] = {10}
tNpcGossip[17095]["Text211"] = Thanksgiving2015_Chest_Text[17095]["Text211"]
tNpcGossip[17095]["Text212"] = Thanksgiving2015_Chest_Text[17095]["Text212"]
tNpcGossip[17095]["Text213"] = Thanksgiving2015_Chest_Text[17095]["Text213"]
tNpcGossip[17095]["Option1"] = Thanksgiving2015_Chest_Text[17095]["Option10"]

--判断等级
tNpcGossip[17095]["Text3-1"] = {311,312}
tNpcGossip[17095]["tOption3-1"] = {11}
tNpcGossip[17095]["Text311"] = Thanksgiving2015_Chest_Text[17095]["Text311"]
tNpcGossip[17095]["Text312"] = Thanksgiving2015_Chest_Text[17095]["Text312"]
tNpcGossip[17095]["Option11"] = Thanksgiving2015_Chest_Text[17095]["Option11"]

--已完成
tNpcGossip[17095]["Text3-2"] = {321}
tNpcGossip[17095]["tOption3-2"] = {12}
tNpcGossip[17095]["Text321"] = Thanksgiving2015_Chest_Text[17095]["Text321"]
tNpcGossip[17095]["Option12"] = Thanksgiving2015_Chest_Text[17095]["Option12"]

--没有完成
tNpcGossip[17095]["Text3-3"] = {331,332}
tNpcGossip[17095]["tOption3-3"] = {13}
tNpcGossip[17095]["Text331"] = Thanksgiving2015_Chest_Text[17095]["Text331"]
tNpcGossip[17095]["Text332"] = Thanksgiving2015_Chest_Text[17095]["Text332"]
tNpcGossip[17095]["Option13"] = Thanksgiving2015_Chest_Text[17095]["Option13"]
tNpcGossip[17095]["OptionFunc13"] = "tThanksgiving2015_Chest_MoveIn</N>17095"

--地图内npc
tNpcGossip[17096]["Text1-1"] = {111,112}
tNpcGossip[17096]["tOption1-1"] = {1,2}
tNpcGossip[17096]["Text111"] = Thanksgiving2015_Chest_Text[17096]["Text111"]
tNpcGossip[17096]["Text112"] = Thanksgiving2015_Chest_Text[17096]["Text112"]
tNpcGossip[17096]["Option1"] = Thanksgiving2015_Chest_Text[17096]["Option1"]
tNpcGossip[17096]["Option2"] = Thanksgiving2015_Chest_Text[17096]["Option2"]
tNpcGossip[17096]["OptionFunc1"] = "tThanksgiving2015_Chest_LeaveOut</N>17096"


--------------------------------------怪物掉落-------------------------------------------
--	7589	神秘金宝箱
tMonster[7589] = tMonster[7589] or {}
tMonster[7589]["tFunction"] = tMonster[7589]["tFunction"] or {}
table.insert(tMonster[7589]["tFunction"],tThanksgiving2015_Chest_KillChest)



