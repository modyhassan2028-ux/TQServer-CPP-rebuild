------------------------------------------------------------------------------------
--Name:			[简体征服][活动脚本]2015暑期活动-冰镇西瓜(7.9-7.22)
--Purpose:		
--Creator: 		张磊
--Created:		05/11/2015
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
--[[掩码说明
##stc(114,98):> 0 表示 在井里面放入了西瓜
##stc(114,99):>0 表示完成任务
]]--

--LOGid 12000094
------------------------------------------------------------------------------------
--命名规范
--SummerActivities_Watermelon__
------------------------------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------常量表配置-------------------------------------------
local SummerActivities_Watermelon_Cont = {}
	--活动时间、
	SummerActivities_Watermelon_Cont["ActivityTime"] = "2015-07-09 00:00 2015-07-22 23:59"
	SummerActivities_Watermelon_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-07-08 23:59"
	
	--玩家等级以及转世要求
	SummerActivities_Watermelon_Cont["Metempsychosis"] = 0
	SummerActivities_Watermelon_Cont["Level"] = 80
	
	SummerActivities_Watermelon_Cont["BagSpace"] = 1
	SummerActivities_Watermelon_Cont["PayMoney"] = 100
	--完成任务值
	SummerActivities_Watermelon_Cont["Complete"] = 1
	--放入水井中的值
	SummerActivities_Watermelon_Cont["Inthe"] = 1
	--放入水井中的时间间隔
	SummerActivities_Watermelon_Cont["Time_1"] = 60
	-- SummerActivities_Watermelon_Cont["Time_20"] = 1200
	-- SummerActivities_Watermelon_Cont["Time_30"] = 1800
	
	SummerActivities_Watermelon_Cont["FestivalId"] = 3432
	
	
	--光效
local SummerActivities_Watermelon_Effect = {}
	SummerActivities_Watermelon_Effect["DeleteMelon"] = "angelwing"
	SummerActivities_Watermelon_Effect["Self"] = "self"
	
local SummerActivities_Watermelon_Npc = {}	

	SummerActivities_Watermelon_Npc["Map"] = 1002
	SummerActivities_Watermelon_Npc["PosX"] = 245
	SummerActivities_Watermelon_Npc["PosY"] = 373
	
	SummerActivities_Watermelon_Npc["PosX_WP"] = 300
	SummerActivities_Watermelon_Npc["PosY_WP"] = 379
	
	--掩码	
local SummerActivities_Watermelon_Stc = {}
	--记录成功完成任务的掩码
	SummerActivities_Watermelon_Stc[1] = {}
	SummerActivities_Watermelon_Stc[1]["Event_type"] = 114
	SummerActivities_Watermelon_Stc[1]["Data_type"] = 98
	
	SummerActivities_Watermelon_Stc[2] = {}
	SummerActivities_Watermelon_Stc[2]["Event_type"] = 114
	SummerActivities_Watermelon_Stc[2]["Data_type"] = 99
	

local SummerActivities_Watermelon_Item = {}

	SummerActivities_Watermelon_Item["Melon"] = 3001498
	SummerActivities_Watermelon_Item["IcedMelon"] = 711758
	
	
local SummerActivities_Watermelon_Log = {}
	SummerActivities_Watermelon_Log["RewardItem"] = "0,0,%d,%d,12000094,2,%d,1"
	SummerActivities_Watermelon_Log["CompleteRewardItem"] = 12000094
	


------------------------------------------NPC对话-------------------------------------------

	
--------------------------------------逻辑部分-------------------------------------------
--判断任务完成情况
function SummerActivities_Watermelon_ChkComplete()
	
	local nEvent = SummerActivities_Watermelon_Stc[2]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[2]["Data_type"]
	local nComplete = SummerActivities_Watermelon_Cont["Complete"]
	
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

--购买西瓜
function SummerActivities_Watermelon_Buymelon(nNpcId)
	
	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nLevel = SummerActivities_Watermelon_Cont["Level"]
	local nMete = SummerActivities_Watermelon_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	if SummerActivities_Watermelon_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nMoney = SummerActivities_Watermelon_Cont["PayMoney"]
	if not User_CanPutMoney2Bag(-nMoney) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nSpace = SummerActivities_Watermelon_Cont["BagSpace"]
	if not User_CheckLeftSpace(nSpace) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end	
	
	local nMelon = SummerActivities_Watermelon_Item["Melon"]

		
	User_AddMoney(-1*nMoney)
	Item_AddItem(nMelon)
	Sys_SaveActionFestivalLog(string.format(SummerActivities_Watermelon_Log["RewardItem"],1,nMoney,nMelon))	
	Sys_MsgBox(SummerActivities_Watermelon_Text["BuyWatermelon"],"SummerActivities_Watermelon_FindWay")

	User_TalkChannel2005(SummerActivities_Watermelon_Text["BuyWatermelon"])
	
end

function SummerActivities_Watermelon_FindWay()
	local nMapId = SummerActivities_Watermelon_Npc["Map"]
	local nPosX = SummerActivities_Watermelon_Npc["PosX"]
	local nPosY = SummerActivities_Watermelon_Npc["PosY"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)
end

--取完西瓜后寻路到NPC
function SummerActivities_Watermelon_FindNpc()
	local nMapId = SummerActivities_Watermelon_Npc["Map"]
	local nPosX = SummerActivities_Watermelon_Npc["PosX_WP"]
	local nPosY = SummerActivities_Watermelon_Npc["PosY_WP"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)
end

--上交冰镇西瓜
function SummerActivities_Watermelon_HandIn(nNpcId)

	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nLevel = SummerActivities_Watermelon_Cont["Level"]
	local nMete = SummerActivities_Watermelon_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	if SummerActivities_Watermelon_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end	
	
	local nIcedMelon = SummerActivities_Watermelon_Item["IcedMelon"]
	if not Item_ChkItem(nIcedMelon) then
		LinkNpcGossipFunc_New(nNpcId,"6-1")
		return
	end
	
	local nEvent = SummerActivities_Watermelon_Stc[2]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[2]["Data_type"]
	local nComplete = SummerActivities_Watermelon_Cont["Complete"]
	
	if not Item_DelItem(nIcedMelon) then
		return
	end
	
	
	Task_SetStatistic(nEvent,nType,nComplete,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	FestivalGeneralPackage_GetGift(SummerActivities_Watermelon_Cont["FestivalId"],SummerActivities_Watermelon_Log["CompleteRewardItem"])
	
	Sys_MsgBox(SummerActivities_Watermelon_Text["CompleteMsg"])
	User_TalkChannel2005(SummerActivities_Watermelon_Text["CompleteMsg"])
end

--请给我指个方向。
function SummerActivities_Watermelon_Find(nNpcId)

	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--活动时间内给寻路
	
	local nMapId = SummerActivities_Watermelon_Npc["Map"]
	local nPosX = SummerActivities_Watermelon_Npc["PosX"]
	local nPosY = SummerActivities_Watermelon_Npc["PosY"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)

end

--水井

--放西瓜
function SummerActivities_Watermelon_PutMelon(nNpcId)
	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = SummerActivities_Watermelon_Stc[1]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[1]["Data_type"]
	local nData = SummerActivities_Watermelon_Cont["Inthe"]

	if Task_ChkStcValue(nEvent,nType,">=",nData) then
		LinkNpcGossipFunc_New(nNpcId,"9-1")
		return
	end
	
	local nMelon = SummerActivities_Watermelon_Item["Melon"]
	if not Item_ChkItem(nMelon) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	
	if not Item_DelItem(nMelon) then
		return
	end
	Task_SetStatistic(nEvent,nType,nData,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	LinkNpcGossipFunc_New(nNpcId,"3-1")
	--增加倒计时
	User_SetTimer(SummerActivities_Watermelon_Cont["Time_1"],"NULL",1)

end

--取出西瓜
function SummerActivities_Watermelon_TakeMelon(nNpcId)
	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = SummerActivities_Watermelon_Stc[1]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[1]["Data_type"]
	local nData = SummerActivities_Watermelon_Cont["Inthe"]
	
	if Task_ChkStcValue(nEvent,nType,"<",nData) then
		LinkNpcGossipFunc_New(nNpcId,"10-1")
		return
	end
	
	local nTme_1 = SummerActivities_Watermelon_Cont["Time_1"]
	-- local nTme_20 = SummerActivities_Watermelon_Cont["Time_20"]
	-- local nTme_30 = SummerActivities_Watermelon_Cont["Time_30"]
	local nSpace = SummerActivities_Watermelon_Cont["BagSpace"]
	local nIcedMelon = SummerActivities_Watermelon_Item["IcedMelon"]
	local nRand = 0
	
	if not Task_StcInterval(nEvent,nType,nTme_1,0) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return		
	else		
		if not User_CheckLeftSpace(nSpace) then
			LinkNpcGossipFunc_New(nNpcId,"6-1")
		else			
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			Item_AddItem(nIcedMelon)
			Sys_MsgBox(SummerActivities_Watermelon_Text["GetIcedWatermelon"],"SummerActivities_Watermelon_FindNpc")
		end
	end
end

function SummerActivities_Watermelon_GetMelon(nNpcId)
	if not Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = SummerActivities_Watermelon_Stc[1]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[1]["Data_type"]
	local nData = SummerActivities_Watermelon_Cont["Inthe"]
	
	if Task_ChkStcValue(nEvent,nType,"<",nData) then
		LinkNpcGossipFunc_New(nNpcId,"10-1")
		return
	end
	
	local nSpace = SummerActivities_Watermelon_Cont["BagSpace"]
	local nIcedMelon = SummerActivities_Watermelon_Item["IcedMelon"]

	if not User_CheckLeftSpace(nSpace) then
		LinkNpcGossipFunc_New(nNpcId,"6-1")
	else
		Task_SetStatistic(nEvent,nType,0,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		Item_AddItem(nIcedMelon)
		Sys_MsgBox(SummerActivities_Watermelon_Text["GetIcedWatermelon"])
	end
end

--西瓜的使用
function SummerActivities_Watermelon_ClickIcedMelon(nItemId)
	if Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		if not Item_DelItem(nItemId) then
			return
		end
		Sys_MsgBox(SummerActivities_Watermelon_Text["ClickMelonInTime"])
	else
		if not Item_DelItem(nItemId) then
			return
		end
		Sys_MsgBox(SummerActivities_Watermelon_Text["ClickMelonAfterTime"])
	end
		User_EffectAdd(SummerActivities_Watermelon_Effect["Self"],SummerActivities_Watermelon_Effect["DeleteMelon"])
end



--------------------------------------NPC模块-------------------------------------------
tNpcFace[2491] = 31
tNpcGossip[15806] = tNpcGossip[15806] or DefaultNpc:new{}
tNpcGossip[15806]["OptionHidden"] = 1

--活动前
tNpcGossip[15806]["Text1-1"] = {111,112,113}
tNpcGossip[15806]["Text111"] = SummerActivities_Watermelon_Text[15806]["Text111"]
tNpcGossip[15806]["Text112"] = SummerActivities_Watermelon_Text[15806]["Text112"]
tNpcGossip[15806]["Text113"] = SummerActivities_Watermelon_Text[15806]["Text113"]
tNpcGossip[15806]["tOption1-1"] = {1}
tNpcGossip[15806]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["BeforeActivityTime"])
end
--活动中
tNpcGossip[15806]["Text1-2"] = {121,122,123,124}
tNpcGossip[15806]["Text121"] = SummerActivities_Watermelon_Text[15806]["Text121"]
tNpcGossip[15806]["Text122"] = SummerActivities_Watermelon_Text[15806]["Text122"]
tNpcGossip[15806]["Text123"] = SummerActivities_Watermelon_Text[15806]["Text123"]
tNpcGossip[15806]["Text124"] = SummerActivities_Watermelon_Text[15806]["Text124"]
tNpcGossip[15806]["tOption1-2"] = {2,3,4,5}
tNpcGossip[15806]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

--活动后	
tNpcGossip[15806]["Text1-3"] = {131}
tNpcGossip[15806]["Text131"] = SummerActivities_Watermelon_Text[15806]["Text131"]
tNpcGossip[15806]["tOption1-3"] = {6}

--等级不够提示
tNpcGossip[15806]["Text2-1"] = {211,212}
tNpcGossip[15806]["Text211"] = SummerActivities_Watermelon_Text[15806]["Text211"]
tNpcGossip[15806]["Text212"] = SummerActivities_Watermelon_Text[15806]["Text212"]
tNpcGossip[15806]["tOption2-1"] = {7}

--玩家身上银两不够
tNpcGossip[15806]["Text3-1"] = {311}
tNpcGossip[15806]["Text311"] = SummerActivities_Watermelon_Text[15806]["Text311"]
tNpcGossip[15806]["tOption3-1"] = {7}

--玩家背包空间不足
tNpcGossip[15806]["Text4-1"] = {411}
tNpcGossip[15806]["Text411"] = SummerActivities_Watermelon_Text[15806]["Text411"]
tNpcGossip[15806]["tOption4-1"] = {7}

--当天已经领取了奖励
tNpcGossip[15806]["Text5-1"] = {511}
tNpcGossip[15806]["Text511"] = SummerActivities_Watermelon_Text[15806]["Text511"]
tNpcGossip[15806]["tOption5-1"] = {8}

--上交冰镇西瓜时没有西瓜
tNpcGossip[15806]["Text6-1"] = {611,612}
tNpcGossip[15806]["Text611"] = SummerActivities_Watermelon_Text[15806]["Text611"]
tNpcGossip[15806]["Text612"] = SummerActivities_Watermelon_Text[15806]["Text612"]
tNpcGossip[15806]["tOption6-1"] = {7}

--我要怎么帮你呢？
tNpcGossip[15806]["Text7-1"] = {711,712,713,714}
tNpcGossip[15806]["Text711"] = SummerActivities_Watermelon_Text[15806]["Text711"]
tNpcGossip[15806]["Text712"] = SummerActivities_Watermelon_Text[15806]["Text712"]
tNpcGossip[15806]["Text713"] = SummerActivities_Watermelon_Text[15806]["Text713"]
tNpcGossip[15806]["Text714"] = SummerActivities_Watermelon_Text[15806]["Text714"]
tNpcGossip[15806]["tOption7-1"] = {9,10}

--	--冰凉的水井
tNpcGossip[15807] = tNpcGossip[15807] or DefaultNpc:new{}
tNpcGossip[15807]["OptionHidden"] = 1

--活动时间内的对白
tNpcGossip[15807]["Text1-1"] = {111}
tNpcGossip[15807]["Text111"] = SummerActivities_Watermelon_Text[15807]["Text111"]
tNpcGossip[15807]["tOption1-1"] = {1,2,3}
tNpcGossip[15807]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

--非活动时间
tNpcGossip[15807]["Text1-2"] = {121}
tNpcGossip[15807]["Text121"] = SummerActivities_Watermelon_Text[15807]["Text121"]
tNpcGossip[15807]["tOption1-2"] = {3}

--放西瓜 - 没有西瓜
tNpcGossip[15807]["Text2-1"] = {211}
tNpcGossip[15807]["Text211"] = SummerActivities_Watermelon_Text[15807]["Text211"]
tNpcGossip[15807]["tOption2-1"] = {4}

--成功放入西瓜
tNpcGossip[15807]["Text3-1"] = {311}
tNpcGossip[15807]["Text311"] = SummerActivities_Watermelon_Text[15807]["Text311"]
tNpcGossip[15807]["tOption3-1"] = {5}

--取西瓜 - 不足10分钟
tNpcGossip[15807]["Text4-1"] = {411}
tNpcGossip[15807]["Text411"] = SummerActivities_Watermelon_Text[15807]["Text411"]
tNpcGossip[15807]["tOption4-1"] = {4}

--10分钟-20分钟
tNpcGossip[15807]["Text5-1"] = {511}
tNpcGossip[15807]["Text511"] = SummerActivities_Watermelon_Text[15807]["Text511"]
tNpcGossip[15807]["tOption5-1"] = {6,7}

--取出西瓜时 空间不足
tNpcGossip[15807]["Text6-1"] = {611}
tNpcGossip[15807]["Text611"] = SummerActivities_Watermelon_Text[15807]["Text611"]
tNpcGossip[15807]["tOption6-1"] = {5}

--30分钟以内取出失败
tNpcGossip[15807]["Text7-1"] = {711}
tNpcGossip[15807]["Text711"] = SummerActivities_Watermelon_Text[15807]["Text711"]
tNpcGossip[15807]["tOption7-1"] = {8}

--30分钟以上 取出失败
tNpcGossip[15807]["Text8-1"] = {811,812}
tNpcGossip[15807]["Text811"] = SummerActivities_Watermelon_Text[15807]["Text811"]
tNpcGossip[15807]["Text812"] = SummerActivities_Watermelon_Text[15807]["Text812"]
tNpcGossip[15807]["tOption8-1"] = {9}

tNpcGossip[15807]["Text9-1"] = {911}
tNpcGossip[15807]["Text911"] = SummerActivities_Watermelon_Text[15807]["Text911"]
tNpcGossip[15807]["tOption9-1"] = {10}

tNpcGossip[15807]["Text10-1"] = {911}
tNpcGossip[15807]["Text1011"] = SummerActivities_Watermelon_Text[15807]["Text1011"]
tNpcGossip[15807]["tOption10-1"] = {11}


--选项
tNpcGossip[15806]["Option1"] = SummerActivities_Watermelon_Text[15806]["Option1"]
tNpcGossip[15806]["Option2"] = SummerActivities_Watermelon_Text[15806]["Option2"]
tNpcGossip[15806]["OptionFunc2"]="SummerActivities_Watermelon_Buymelon</N>15806"
tNpcGossip[15806]["OptionChkFunc2"] = function ()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

tNpcGossip[15806]["Option3"] = SummerActivities_Watermelon_Text[15806]["Option3"]
tNpcGossip[15806]["OptionFunc3"]="SummerActivities_Watermelon_HandIn</N>15806"
tNpcGossip[15806]["OptionChkFunc3"] = function ()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

tNpcGossip[15806]["Option4"] = SummerActivities_Watermelon_Text[15806]["Option4"]
tNpcGossip[15806]["OptionPoint4"]="7-1"
tNpcGossip[15806]["OptionChkFunc4"] = function ()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

tNpcGossip[15806]["Option5"] = SummerActivities_Watermelon_Text[15806]["Option5"]
tNpcGossip[15806]["Option6"] = SummerActivities_Watermelon_Text[15806]["Option6"]
tNpcGossip[15806]["Option7"] = SummerActivities_Watermelon_Text[15806]["Option7"]
tNpcGossip[15806]["Option8"] = SummerActivities_Watermelon_Text[15806]["Option8"]


tNpcGossip[15806]["Option9"] = SummerActivities_Watermelon_Text[15806]["Option9"]
tNpcGossip[15806]["OptionFunc9"]="SummerActivities_Watermelon_Find</N>15806"
tNpcGossip[15806]["OptionChkFunc9"] = function ()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

tNpcGossip[15806]["Option10"] = SummerActivities_Watermelon_Text[15806]["Option10"]


--水井

tNpcGossip[15807]["Option1"] = SummerActivities_Watermelon_Text[15807]["Option1"]
tNpcGossip[15807]["OptionFunc1"]="SummerActivities_Watermelon_PutMelon</N>15807"
tNpcGossip[15807]["OptionChkFunc1"] = function ()
	local nEvent = SummerActivities_Watermelon_Stc[1]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[1]["Data_type"]
	local nData = SummerActivities_Watermelon_Cont["Inthe"]

	if Task_ChkStcValue(nEvent,nType,"<",nData) and Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		return true
	else
		return false
	end	
end

tNpcGossip[15807]["Option2"] = SummerActivities_Watermelon_Text[15807]["Option2"]
tNpcGossip[15807]["OptionFunc2"]="SummerActivities_Watermelon_TakeMelon</N>15807"
tNpcGossip[15807]["OptionChkFunc2"] = function ()
	local nEvent = SummerActivities_Watermelon_Stc[1]["Event_type"]
	local nType = SummerActivities_Watermelon_Stc[1]["Data_type"]
	local nData = SummerActivities_Watermelon_Cont["Inthe"]

	if Task_ChkStcValue(nEvent,nType,">=",nData) and Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"]) then
		return true
	else
		return false
	end	
end


tNpcGossip[15807]["Option3"] = SummerActivities_Watermelon_Text[15807]["Option3"]
tNpcGossip[15807]["Option4"] = SummerActivities_Watermelon_Text[15807]["Option4"]
tNpcGossip[15807]["Option5"] = SummerActivities_Watermelon_Text[15807]["Option5"]

tNpcGossip[15807]["Option6"] = SummerActivities_Watermelon_Text[15807]["Option6"]
tNpcGossip[15807]["OptionFunc6"]="SummerActivities_Watermelon_GetMelon</N>15807"
tNpcGossip[15807]["OptionChkFunc6"] = function ()
	return Sys_ChkFullTime(SummerActivities_Watermelon_Cont["ActivityTime"])
end

tNpcGossip[15807]["Option7"] = SummerActivities_Watermelon_Text[15807]["Option7"]
tNpcGossip[15807]["Option8"] = SummerActivities_Watermelon_Text[15807]["Option8"]
tNpcGossip[15807]["Option9"] = SummerActivities_Watermelon_Text[15807]["Option9"]
tNpcGossip[15807]["Option10"] = SummerActivities_Watermelon_Text[15807]["Option10"]
tNpcGossip[15807]["Option11"] = SummerActivities_Watermelon_Text[15807]["Option11"]
	
	

	
	
	
