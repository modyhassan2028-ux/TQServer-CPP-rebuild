-----------------------------------------------------------------------------------------------------
--Name:			150810[简体征服][活动脚本]感恩节之特赦火鸡(11.24-11.30)
--Purpose:		感恩节活动之特赦火鸡
--Creator: 		许乐
--Created:		2015/08/10
------------------------------------------------------------------------------------------------------
-- 命名前缀
--Thanksgiving2015_AbsolveTurkey_

-- npcId:		17226-17229
-- npctype:	3246-3249
-- itemtype:	3007288

-- 掩码说明          
--stc(130,07)
--stc(130,07) = 1	表示已赦免火鸡

--logID:12000196
--FestivalId: 3330

-----------------------------------------常量表配置-----------------------------------------------
local tThanksgiving2015_AbsolveTurkey_Cont = {}
	--活动时间	
	tThanksgiving2015_AbsolveTurkey_Cont["BeforeActivityTime"] = "2014-09-01 00:00 2015-11-23 23:59"
	tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"] = "2015-11-24 00:00 2015-11-30 23:59"
	-- tThanksgiving2015_AbsolveTurkey_Cont["BeforeActivityTime"] = "2014-09-01 00:00 2015-08-23 23:59"
	-- tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"] = "2015-08-24 00:00 2015-11-30 23:59"


	--玩家等级要求
	tThanksgiving2015_AbsolveTurkey_Cont["Metempsychosis"] = 0
	tThanksgiving2015_AbsolveTurkey_Cont["Level"] = 80

	--房屋type
	tThanksgiving2015_AbsolveTurkey_Cont["House_Type"] = 1024
	
--火鸡npc外形
local tThanksgiving2015_AbsolveTurkey_Lookface = {}
	tThanksgiving2015_AbsolveTurkey_Lookface[3007288] = 32540
	
--掩码
local tThanksgiving2015_AbsolveTurkey_Stc = {}
	tThanksgiving2015_AbsolveTurkey_Stc["EventType"] = 130
	tThanksgiving2015_AbsolveTurkey_Stc["DataType"] = 07
	tThanksgiving2015_AbsolveTurkey_Stc["Complete"] = 1
	
--奖励物品
local tThanksgiving2015_AbsolveTurkey_Item = {}
	tThanksgiving2015_AbsolveTurkey_Item["BagSpace"] = 1
	tThanksgiving2015_AbsolveTurkey_Item["RewardSpace"] = 2
	tThanksgiving2015_AbsolveTurkey_Item["Item3007288"] = 3007288

local tThanksgiving2015_AbsolveTurkey_Log = {}
	tThanksgiving2015_AbsolveTurkey_Log["GetTurkey"] = "0,0,0,0,12000196,2,3007288,1"
	tThanksgiving2015_AbsolveTurkey_Log["DelItem"] = "0,0,3007288,1,12000196,3,0,0"
	tThanksgiving2015_AbsolveTurkey_Log["FestivalId"] = 3330
	tThanksgiving2015_AbsolveTurkey_Log["LogId"] = 12000196
	
--获得礼包的特效
local tThanksgiving2015_AbsolveTurkey_Effect = {}
	tThanksgiving2015_AbsolveTurkey_Effect[1] = "self"
	tThanksgiving2015_AbsolveTurkey_Effect[2] = "angelwing"

------------------------------------------------逻辑部分-------------------------------------------------
--判断掩码 stc(130,07)
function Thanksgiving2015_AbsolveTurkey_ChkStcComplete()
	local nEvent = tThanksgiving2015_AbsolveTurkey_Stc["EventType"]
	local nType = tThanksgiving2015_AbsolveTurkey_Stc["DataType"]
	local nComplete = tThanksgiving2015_AbsolveTurkey_Stc["Complete"]

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

--接Option2：赦免它
function Thanksgiving2015_AbsolveTurkey_Absolve(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	-- 判断玩家等级
	local nLevel = tThanksgiving2015_AbsolveTurkey_Cont["Level"]
	local nMete = tThanksgiving2015_AbsolveTurkey_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	--已赦免过，无法赦免
	if Thanksgiving2015_AbsolveTurkey_ChkStcComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--背包已满
	if not User_CheckLeftSpace(tThanksgiving2015_AbsolveTurkey_Item["RewardSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--设置掩码
	local nEvent = tThanksgiving2015_AbsolveTurkey_Stc["EventType"]
	local nType = tThanksgiving2015_AbsolveTurkey_Stc["DataType"]
	local nComplete = tThanksgiving2015_AbsolveTurkey_Stc["Complete"]
	Task_SetStatistic(nEvent,nType,nComplete,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	--给物品
	Item_AddItem(tThanksgiving2015_AbsolveTurkey_Item["Item3007288"])
	Sys_SaveActionFestivalLog(tThanksgiving2015_AbsolveTurkey_Log["GetTurkey"])
	FestivalGeneralPackage_GetGift(tThanksgiving2015_AbsolveTurkey_Log["FestivalId"],tThanksgiving2015_AbsolveTurkey_Log["LogId"])
	User_EffectAdd(tThanksgiving2015_AbsolveTurkey_Effect[1],tThanksgiving2015_AbsolveTurkey_Effect[2])
	--成功赦免
	LinkNpcGossipFunc_New(nNpcId,"2-1")
end

------------------------------------------------使用物品逻辑--------------------------------------------------
--使用家具
function Thanksgiving2015_AbsolveTurkey_UseItem(nItemId)
	if not Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		Item_DelItem(nItemId)
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["DatePassed"])
		return
	end
	
	--判断是否在房屋内使用
	local nHouseType = tThanksgiving2015_AbsolveTurkey_Cont["House_Type"]
	local nPlayerId = Get_UserId()
	local nUserMapType = Get_MapType()
	if not Sys_ParseNumbersContain(nHouseType,nUserMapType) then
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["NotInHouse"])
		return
	end
	
	local nMapOwnerId = Get_MapOwnerId()
	if nMapOwnerId ~= nPlayerId then
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["NotInHouse"])
		return
	end
	
	--判断房屋等级
	if Get_MapResLev() >= 6 or Get_MapResLev() < 2 then
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["NotReslev"])
		return
	end
	
	--判断房屋中的家具数量
	if Get_NpcCount() >= 12 then
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["EnoghNum"])
		return
	end
	
	Npc_RequestLayNpcByItem("Thanksgiving2015_AbsolveTurkey_CreateNpc</N>"..nItemId,2,tThanksgiving2015_AbsolveTurkey_Lookface[nItemId])
end

function Thanksgiving2015_AbsolveTurkey_CreateNpc(nItemId)
	if Npc_CreatLayNpcByItem(tThanksgiving2015_AbsolveTurkey_Text["Name"]["Furniture"],2,32,tThanksgiving2015_AbsolveTurkey_Lookface[nItemId],0,0,0,0,0,94466210) then 
		Item_DelItem(nItemId)
		return
	end
	return
end

--点击家具时，过期删除当前家具npc
function Thanksgiving2015_AbsolveTurkey_DelDynaNpcByItem(nItemId)
	if not Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		Npc_DelDynaByID()
		return
	end
	Sys_DialogText(tThanksgiving2015_AbsolveTurkey_Text[nItemId]["Text111"])
	Sys_DialogOption(tThanksgiving2015_AbsolveTurkey_Text[nItemId]["Option1"],"</F>Thanksgiving2015_AbsolveTurkey_FoldFurniture</N>"..nItemId)
	Sys_DialogEnd()
end

--收起家具
function Thanksgiving2015_AbsolveTurkey_FoldFurniture(nItemId)
	if not Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		Npc_DelDynaByID()
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["DeleteItem"])
		return
	end
	local nPlayerId = Get_UserId()
	local nMapOwnerId = Get_MapOwnerId()
	if nMapOwnerId ~= nPlayerId then
		return
	end
	if not User_CheckLeftSpace(tThanksgiving2015_AbsolveTurkey_Item["BagSpace"]) then
		User_TalkChannel2005(tThanksgiving2015_AbsolveTurkey_Text["FullBag"])
		return
	end
	Npc_DelDynaByID()
	Item_AddItem(nItemId)
end

------------------------------------------------NPC模块--------------------------------------------------
-- 17226  火鸡协会主席
tNpcFace[3246] = 110
tNpcGossip[17226] = tNpcGossip[17226] or DefaultNpc:new{}
tNpcGossip[17226]["OptionHidden"] = 1

--活动前对白
tNpcGossip[17226]["Text1-1"] = {111,112,113}
tNpcGossip[17226]["Text111"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text111"]
tNpcGossip[17226]["Text112"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text112"]
tNpcGossip[17226]["Text113"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text113"]
tNpcGossip[17226]["tOption1-1"] = {1}
tNpcGossip[17226]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["BeforeActivityTime"])
end

--活动中对白
tNpcGossip[17226]["Text1-2"] = {121,122,123}
tNpcGossip[17226]["Text121"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text121"]
tNpcGossip[17226]["Text122"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text122"]
tNpcGossip[17226]["Text123"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text123"]
tNpcGossip[17226]["tOption1-2"] = {3,4}
tNpcGossip[17226]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"])
end

--活动后对白
tNpcGossip[17226]["Text1-3"] = {131,132}
tNpcGossip[17226]["Text131"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text131"]
tNpcGossip[17226]["Text132"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text132"]
tNpcGossip[17226]["tOption1-3"] = {2}

--接Option3：请给我介绍介绍它们吧！
tNpcGossip[17226]["Text3-1"] = {311,312,313,314}
tNpcGossip[17226]["Text311"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text311"]
tNpcGossip[17226]["Text312"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text312"]
tNpcGossip[17226]["Text313"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text313"]
tNpcGossip[17226]["Text314"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Text314"]
tNpcGossip[17226]["tOption3-1"] = {5}

--选项
tNpcGossip[17226]["Option1"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Option1"]
tNpcGossip[17226]["Option2"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Option2"]
--请给我介绍介绍它们吧！
tNpcGossip[17226]["Option3"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Option3"]
tNpcGossip[17226]["OptionPoint3"]="3-1"
tNpcGossip[17226]["Option4"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Option4"]
tNpcGossip[17226]["Option5"] = tThanksgiving2015_AbsolveTurkey_Text[17226]["Option5"]


-- 17227  向阳火鸡
tNpcGossip[17227] = tNpcGossip[17227] or DefaultNpc:new{}
tNpcGossip[17227]["OptionHidden"] = 1

--活动中对白
tNpcGossip[17227]["Text1-1"] = {111}
tNpcGossip[17227]["Text111"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text111"]
tNpcGossip[17227]["tOption1-1"] = {1,2,3}
tNpcGossip[17227]["ChkFunc1-1"] = function ()
	local nNpcId = Get_NpcId()
	tNpcGossip[17227]["Text111"] = string.format(tThanksgiving2015_AbsolveTurkey_Text[17227]["Text111"],tThanksgiving2015_AbsolveTurkey_Text["Turkey"][nNpcId])
	return true
end

--接Option2：赦免它！
--成功赦免
tNpcGossip[17227]["Text2-1"] = {211,212}
tNpcGossip[17227]["Text211"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text211"]
tNpcGossip[17227]["Text212"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text212"]
tNpcGossip[17227]["tOption2-1"] = {4}
tNpcGossip[17227]["ChkFunc2-1"] = function ()
	local nNpcId = Get_NpcId()
	tNpcGossip[17227]["Text211"] = string.format(tThanksgiving2015_AbsolveTurkey_Text[17227]["Text211"],tThanksgiving2015_AbsolveTurkey_Text["Name"][nNpcId],tThanksgiving2015_AbsolveTurkey_Text["Name"][nNpcId])
	tNpcGossip[17227]["Text212"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text212"]
	return true
end
--已赦免过，无法赦免
tNpcGossip[17227]["Text2-2"] = {221}
tNpcGossip[17227]["Text221"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text221"]
tNpcGossip[17227]["tOption2-2"] = {5}
--等级不足
tNpcGossip[17227]["Text2-3"] = {231}
tNpcGossip[17227]["Text231"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text231"]
tNpcGossip[17227]["tOption2-3"] = {6}
--背包已满
tNpcGossip[17227]["Text2-4"] = {241}
tNpcGossip[17227]["Text241"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text241"]
tNpcGossip[17227]["tOption2-4"] = {7}
--不在活动时间
tNpcGossip[17227]["Text2-5"] = {251}
tNpcGossip[17227]["Text251"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Text251"]
tNpcGossip[17227]["tOption2-5"] = {6}

--选项
tNpcGossip[17227]["Option1"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option1"]
tNpcGossip[17227]["OptionChkFunc1"] = function ()
	if Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		return false
	else
		return true
	end
end
--赦免它！
tNpcGossip[17227]["Option2"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option2"]
tNpcGossip[17227]["OptionFunc2"]="Thanksgiving2015_AbsolveTurkey_Absolve</N>17227"
tNpcGossip[17227]["OptionChkFunc2"] = function ()
	if Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		return true
	else
		return false
	end
end
tNpcGossip[17227]["Option3"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option3"]
tNpcGossip[17227]["OptionChkFunc3"] = function ()
	if Sys_ChkFullTime(tThanksgiving2015_AbsolveTurkey_Cont["ActivityTime"]) then
		return true
	else
		return false
	end
end
tNpcGossip[17227]["Option4"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option4"]
tNpcGossip[17227]["Option5"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option5"]
tNpcGossip[17227]["Option6"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option6"]
tNpcGossip[17227]["Option7"] = tThanksgiving2015_AbsolveTurkey_Text[17227]["Option7"]

-- 17228  飞天火鸡
tNpcGossip[17228] = tNpcGossip[17227]
-- 17229  奔腾火鸡
tNpcGossip[17229] = tNpcGossip[17227]

