---Name:[简体征服][活动脚本]万圣节活动之杰克的游戏(10.29-11.4)
--Creator: 	陈莺
--Created:	2015/07/22
--------------------------------------------------------------------------------
--npc杰克  17057
--物品
-- 3007233 南瓜糕点
-- 3007234 数字卡牌1
-- 3007235 数字卡牌2
-- 3007236 数字卡牌3
-- 3007237 数字卡牌4
-- 3007238 数字卡牌5
-- 3007239 数字卡牌6
-- 3007240 数字卡牌7
-- 3007241 数字卡牌8
-- 3007242 数字卡牌9
--掩码说明
-- stc(128,67) =1 今日完成     
-- stc(128,68)  密码第一位     
-- stc(128,69)  第2位          
-- stc(128,70)  第3位          
-- stc(128,71)  第4位          
-- stc(128,72)  生成密码       
-- stc(129,30) >=1 单次提示已定
--命名规范
--Halloween2015_JackGame_

----------------------------------------------------------------------------------
--活动时间
local tHalloween2015_JackGame_Data= {}
	tHalloween2015_JackGame_Data["Bef_Time"]= "2014-05-18 00:00 2015-10-28 23:59"
	tHalloween2015_JackGame_Data["Now_Time"] = "2015-10-29 00:00 2015-11-04 23:59"
	tHalloween2015_JackGame_Data["Aft_Time"]= "2015-11-05 00:00 2016-10-01 23:59"
--等级
	tHalloween2015_JackGame_Data["Level"] = 80
	tHalloween2015_JackGame_Data["Metempsychosis"] = 0
--背包空间
	tHalloween2015_JackGame_Data["Space"] = 1
--坐标
	tHalloween2015_JackGame_Data["MapId"] = 1002
	tHalloween2015_JackGame_Data["BoundX"] = {}
	tHalloween2015_JackGame_Data["BoundY"] = {}
	
	tHalloween2015_JackGame_Data["BoundX"][1] = 289 
	tHalloween2015_JackGame_Data["BoundY"][1] = 401
	
	tHalloween2015_JackGame_Data["BoundX"][2] = 320 
	tHalloween2015_JackGame_Data["BoundY"][2] = 374
	
	tHalloween2015_JackGame_Data["BoundX"][3] = 282 
	tHalloween2015_JackGame_Data["BoundY"][3] = 345
	
	tHalloween2015_JackGame_Data["BoundX"][4] = 255 
	tHalloween2015_JackGame_Data["BoundY"][4] = 369
	
	tHalloween2015_JackGame_Data["AcceptLen"] = 4
	
local tHalloween2015_JackGame_Stc = {}
	tHalloween2015_JackGame_Stc["EventType"] = {}
	tHalloween2015_JackGame_Stc["DataType"] = {}

--stc(128,67) =1 今日完成
	tHalloween2015_JackGame_Stc["EventType"][8] = 128
	tHalloween2015_JackGame_Stc["DataType"][8] = 67
-- stc(128,68)  密码第一位
	tHalloween2015_JackGame_Stc["EventType"][1] = 128
	tHalloween2015_JackGame_Stc["DataType"][1] = 68
--stc(128,69)  第2位
	tHalloween2015_JackGame_Stc["EventType"][2] = 128
	tHalloween2015_JackGame_Stc["DataType"][2] = 69
--stc(128,70)  第3位
	tHalloween2015_JackGame_Stc["EventType"][3] = 128
	tHalloween2015_JackGame_Stc["DataType"][3] = 70
--stc(128,71)  第4位
	tHalloween2015_JackGame_Stc["EventType"][4] = 128
	tHalloween2015_JackGame_Stc["DataType"][4] = 71
--stc(128,72)  生成密码
	tHalloween2015_JackGame_Stc["EventType"][5] = 128
	tHalloween2015_JackGame_Stc["DataType"][5] = 72
--stc(129,30) >=1 单次提示已定
	tHalloween2015_JackGame_Stc["EventType"][6] = 129
	tHalloween2015_JackGame_Stc["DataType"][6] = 30
--stc(129,33)  吃糕点顺序
	tHalloween2015_JackGame_Stc["EventType"][7] = 129
	tHalloween2015_JackGame_Stc["DataType"][7] = 33

--物品
local tHalloween2015_JackGame_ItemId = {}
	tHalloween2015_JackGame_ItemId[3007233] = 3007233
	tHalloween2015_JackGame_ItemId[1] = 3007234
	tHalloween2015_JackGame_ItemId[2] = 3007235
	tHalloween2015_JackGame_ItemId[3] = 3007236
	tHalloween2015_JackGame_ItemId[4] = 3007237
	tHalloween2015_JackGame_ItemId[5] = 3007238
	tHalloween2015_JackGame_ItemId[6] = 3007239
	tHalloween2015_JackGame_ItemId[7] = 3007240
	tHalloween2015_JackGame_ItemId[8] = 3007241
	tHalloween2015_JackGame_ItemId[9] = 3007242

--log表
local tHalloween2015_JackGame_Log = {}

	tHalloween2015_JackGame_Log["Get"] = "0,0,0,0,10002307,2,3007233,4"
	tHalloween2015_JackGame_Log["Over"] = "0,0,3007233,1,10002307,3,0,0"
	tHalloween2015_JackGame_Log["AddItem"] = "0,0,3007233,1,10002307,2,%d,1"
	tHalloween2015_JackGame_Log["Finish"] = "0,0,0,0,10002307,2,3003625,1"
	tHalloween2015_JackGame_Log["Card"] = "0,0,%d,1,10002307,3,0,0"
	tHalloween2015_JackGame_Log["LogId"] = 10002307
	tHalloween2015_JackGame_Log["FestivalId"] = 3456

-----------------------------------逻辑部分---------------------------------------	
--我要领南瓜糕点！
function Halloween2015_JackGame_PumpkinCake(nNpcId)
	local nFinishEvent = tHalloween2015_JackGame_Stc["EventType"][8]
	local nFinishType = tHalloween2015_JackGame_Stc["DataType"][8]
	Halloween2015_JackGame_Clean()
--判断是否完成
	if Task_ChkStcValue(nFinishEvent,nFinishType,'>=',1) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end 
--检测物品
	if Item_ChkMulItem(tHalloween2015_JackGame_ItemId[3007233],tHalloween2015_JackGame_ItemId[9],1) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
--判断等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_JackGame_Data["Level"],tHalloween2015_JackGame_Data["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
	else
		Halloween2015_JackGame_CheckBag(nNpcId)
	end
end
--检查背包
function Halloween2015_JackGame_CheckBag(nNpcId)
	if not User_CheckLeftSpace(tHalloween2015_JackGame_Data["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
	Halloween2015_JackGame_CleanStc()
	Item_AddItem(tHalloween2015_JackGame_ItemId[3007233],0,4)
	Sys_SaveActionFestivalLog(tHalloween2015_JackGame_Log["Get"])
	LinkNpcGossipFunc_New(nNpcId,"3-5")
end 
--重新领取
function Halloween2015_JackGame_Receive(nItemId,nNpcId)
	local nEndItem = tHalloween2015_JackGame_ItemId[9]
	Halloween2015_JackGame_CleanStc()
	for nItem = nItemId,nEndItem do 
		if Item_ChkItem(nItem) then
			if Item_DelAllItemByType(nItem) then
			end 
		end
	end
	Halloween2015_JackGame_CheckBag(nNpcId)
end

---我要猜数字！
function Halloween2015_JackGame_GuessNumber(nNpcId)
	local nFinishEvent = tHalloween2015_JackGame_Stc["EventType"][8]
	local nFinishType = tHalloween2015_JackGame_Stc["DataType"][8]
	Halloween2015_JackGame_Clean()
--判断是否完成
	if Task_ChkStcValue(nFinishEvent,nFinishType,'>=',1) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	local nPasswordEvent = tHalloween2015_JackGame_Stc["EventType"][5]
	local nPasswordType = tHalloween2015_JackGame_Stc["DataType"][5]
	local nTipEvent = tHalloween2015_JackGame_Stc["EventType"][6] 
	local nTipType = tHalloween2015_JackGame_Stc["DataType"][6]
	local nOrderEvent = tHalloween2015_JackGame_Stc["EventType"][7]
	local nOrderData = tHalloween2015_JackGame_Stc["DataType"][7] 
	if not Item_ChkMulItem(tHalloween2015_JackGame_ItemId[3007233],tHalloween2015_JackGame_ItemId[9],1) then
		User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["NotAccept"])
		return
	end
--判断是否吃完南瓜糕点
	if Task_ChkStcValue(nOrderEvent,nOrderData,'<',4) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end 
	local nNum = Get_UserStatisticValue(nTipEvent,nTipType)
	if nNum <= 2 then 
		local nPassword = Get_UserStatisticValue(nPasswordEvent,nPasswordType)
		local nTipNum = 0
	
		for i=0,2 do
			if nNum == i then
				nTipNum = nPassword/(10^(3-i))
				nTipNum = math.floor(nTipNum)
				Halloween2015_JackGame_Tip(nNpcId,nTipNum,nPassword,nNum)
			end
		end
	else
		local nPassword = Get_UserStatisticValue(nPasswordEvent,nPasswordType)
		local nNum = 2
		nTipNum = nPassword/10
		nTipNum = math.floor(nTipNum)
		Halloween2015_JackGame_Tip(nNpcId,nTipNum,nPassword,nNum)
	end
end
--随机提示
function Halloween2015_JackGame_Tip(nNpcId,nTipNum,nPassword,nNum)

	local sStr = string.format(tHalloween2015_JackGame_Text[17057]["Text442"][nNum],nTipNum)
	Sys_DialogText(tHalloween2015_JackGame_Text[17057]["Text441"])
	Sys_DialogText(sStr)
	Sys_DialogOptEdit(tHalloween2015_JackGame_Text[17057]["Text443"],tHalloween2015_JackGame_Data["AcceptLen"],"Halloween2015_JackGame_Password</N>"..nPassword.."</N>"..nNpcId)
	Sys_DialogOption(tHalloween2015_JackGame_Text[17057]["Option16"],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end

--比较是否猜对数字
function Halloween2015_JackGame_Password(nPassword,nNpcId)
	local nFinishEvent = tHalloween2015_JackGame_Stc["EventType"][8]
	local nFinishType = tHalloween2015_JackGame_Stc["DataType"][8]
	local nGuessNo = tonumber(Get_SysAcceptStr())
	if nPassword == nGuessNo then
		local nStartItem = tHalloween2015_JackGame_ItemId[3007233]
		local nEndItem = tHalloween2015_JackGame_ItemId[9]
		for nItemId = nStartItem,nEndItem do 
			if Item_ChkItem(nItemId) then
				if Item_DelAllItemByType(nItemId) then
				end
			end
		end
		if not User_CheckLeftSpace(tHalloween2015_JackGame_Data["Space"]) then
			User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["Right"])
			return
		end
--猜对
		Task_SetStatistic(nFinishEvent,nFinishType,1,1)
		Task_SetStcTimestamp(nFinishEvent,nFinishType,0)
		Sys_SaveActionFestivalLog(tHalloween2015_JackGame_Log["Finish"])
		User_EffectAdd("self","zf2-e280")
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		FestivalGeneralPackage_GetGift(tHalloween2015_JackGame_Log["FestivalId"],tHalloween2015_JackGame_Log["LogId"])
--猜错
	else
		local nNum = math.random(1,4)
		local nUserId = Get_UserId()
		local nTipEvent = tHalloween2015_JackGame_Stc["EventType"][6] 
		local nTipType = tHalloween2015_JackGame_Stc["DataType"][6]
--甩出去
		Task_AddStatistic(nTipEvent,nTipType,1,1)
		Halloween2015_JackGame_Goto(nNum)
		Sys_MsgBox(tHalloween2015_JackGame_Text["MsgBox"]["Error"])
	end
end
--地点
function Halloween2015_JackGame_Goto(nNum)

	User_UserRandBoundTrans(tHalloween2015_JackGame_Data["MapId"],tHalloween2015_JackGame_Data["BoundX"][nNum],tHalloween2015_JackGame_Data["BoundY"][nNum],5,5)
end
--南瓜糕点 3007233
function Halloween2015_JackGame_ItemPumpkinCake()
--活动时间判断
	local nItemId = tHalloween2015_JackGame_ItemId[3007233]
	if not Sys_ChkFullTime(tHalloween2015_JackGame_Data["Now_Time"]) then
		if not Item_DelItem(nItemId) then
			return
		end
		Sys_SaveActionFestivalLog(tHalloween2015_JackGame_Log["Over"])
		User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["Over"])
		return
	end
--检测背包
	if not User_CheckLeftSpace(tHalloween2015_JackGame_Data["Space"]) then
		User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["BagFull"])
		return
	end
--3701
	User_SetExplore(1,tHalloween2015_JackGame_Text["MsgBox"]["Eat"],220,"Halloween2015_JackGame_RandomNum</N>"..nItemId)
end
--吃糖，获得随机数字
function Halloween2015_JackGame_RandomNum(nItemId)
	local nOrderEvent = tHalloween2015_JackGame_Stc["EventType"][7]
	local nOrderData = tHalloween2015_JackGame_Stc["DataType"][7] 
	local nPasswordEvent = tHalloween2015_JackGame_Stc["EventType"][5]
	local nPasswordType = tHalloween2015_JackGame_Stc["DataType"][5]
	if not Item_DelItem(nItemId) then
		return
	end
	local  nNum = math.random(1,9)
	local nItem = tHalloween2015_JackGame_ItemId[nNum]

	Item_AddItem(nItem)
	local slog = string.format(tHalloween2015_JackGame_Log["AddItem"],nItem)
	Sys_SaveActionFestivalLog(slog)
	Task_AddStatistic(nOrderEvent,nOrderData,1,1)
	Task_SetStcTimestamp(nOrderEvent,nOrderData,0)
---随机第几位数
	if Task_ChkStcValue(nOrderEvent,nOrderData,'<=',4) then
		local nAmount = 0 --需要随机数量
		local nFlag = 1 --表的下标
		local tPosition={}  --存剩下的位置
		for i=1,4 do
			if Task_ChkStcValue(tHalloween2015_JackGame_Stc["EventType"][i],tHalloween2015_JackGame_Stc["DataType"][i],'==',0) then
			nAmount = nAmount + 1
			tPosition[nFlag] = i
			nFlag = nFlag + 1
			end
		end
			local nc = math.random(1,nAmount)
			local ndata = tPosition[nc]
			Task_SetStatistic(tHalloween2015_JackGame_Stc["EventType"][ndata],tHalloween2015_JackGame_Stc["DataType"][ndata],nNum,1)
--生成密码
			local npassword =  Get_UserStatisticValue(nPasswordEvent,nPasswordType)
			npassword = npassword+nNum*10^(ndata-1)
			Task_SetStatistic(nPasswordEvent,nPasswordType,npassword,1)
		
	end
	if Task_ChkStcValue(nOrderEvent,nOrderData,'==',4) then
		Sys_MsgBox(tHalloween2015_JackGame_Text["MsgBox"]["Eat4"])
	end
end
--数字卡牌
function Halloween2015_JackGame_ItemNumCard()
	local nItemId = Get_ItemType()
	--活动时间判断
	if not Sys_ChkFullTime(tHalloween2015_JackGame_Data["Now_Time"]) then
		if Item_DelItem(nItemId) then
		local slog = string.format(tHalloween2015_JackGame_Log["Card"],nItemId)
		Sys_SaveActionFestivalLog(slog)
		User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["Over"])
		end
		return
	end
	User_TalkChannel2005(tHalloween2015_JackGame_Text["MsgBox"]["CardTip"])
end
--隔天清零函数
function Halloween2015_JackGame_Clean()
	local nFinishEvent = tHalloween2015_JackGame_Stc["EventType"][8]
	local nFinishType = tHalloween2015_JackGame_Stc["DataType"][8]
	if Task_ChkStcValue(nFinishEvent,nFinishType,'>=',1) and Task_StcInterval(nFinishEvent,nFinishType,1,4)then
		Halloween2015_JackGame_CleanStc()
	end 
end
--清掩码
function Halloween2015_JackGame_CleanStc()
 	for i=1,8 do
		Task_SetStatistic(tHalloween2015_JackGame_Stc["EventType"][i],tHalloween2015_JackGame_Stc["DataType"][i],0,1)
		Task_SetStcTimestamp(tHalloween2015_JackGame_Stc["EventType"][i],tHalloween2015_JackGame_Stc["DataType"][i],0)
	end 
end
-----------------------------------npc模板----------------------------------------
---NPC头像
tNpcFace[3165] = 195

---南瓜怪人杰克

tNpcGossip[17057] = tNpcGossip[17057] or DefaultNpc:new{}
tNpcGossip[17057]["OptionHidden"] = 1

--活动时间前
tNpcGossip[17057]["Text1-1"] = {111,112,113}
tNpcGossip[17057]["Text111"] = tHalloween2015_JackGame_Text[17057]["Text111"]
tNpcGossip[17057]["Text112"] = tHalloween2015_JackGame_Text[17057]["Text112"]
tNpcGossip[17057]["Text113"] = tHalloween2015_JackGame_Text[17057]["Text113"]
tNpcGossip[17057]["tOption1-1"] = {1}
tNpcGossip[17057]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tHalloween2015_JackGame_Data["Bef_Time"])
end
tNpcGossip[17057]["Option1"] = tHalloween2015_JackGame_Text[17057]["Option1"]
--活动时间中
tNpcGossip[17057]["Text1-2"] = {121,122,123}
tNpcGossip[17057]["Text121"] = tHalloween2015_JackGame_Text[17057]["Text121"]
tNpcGossip[17057]["Text122"] = tHalloween2015_JackGame_Text[17057]["Text122"]
tNpcGossip[17057]["Text123"] = tHalloween2015_JackGame_Text[17057]["Text123"]
tNpcGossip[17057]["tOption1-2"] = {2,3,4,5}
tNpcGossip[17057]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(tHalloween2015_JackGame_Data["Now_Time"])
end
tNpcGossip[17057]["Option2"] = tHalloween2015_JackGame_Text[17057]["Option2"]
tNpcGossip[17057]["OptionFunc2"]="Halloween2015_JackGame_PumpkinCake</N>17057"

tNpcGossip[17057]["Option3"] = tHalloween2015_JackGame_Text[17057]["Option3"]
tNpcGossip[17057]["OptionFunc3"]="Halloween2015_JackGame_GuessNumber</N>17057"

tNpcGossip[17057]["Option4"] = tHalloween2015_JackGame_Text[17057]["Option4"]
tNpcGossip[17057]["OptionPoint4"]="2-1"
tNpcGossip[17057]["Option5"] = tHalloween2015_JackGame_Text[17057]["Option5"]
--活动时间后
tNpcGossip[17057]["Text1-3"] = {131}
tNpcGossip[17057]["Text131"] = tHalloween2015_JackGame_Text[17057]["Text131"]
tNpcGossip[17057]["tOption1-3"] = {6}
tNpcGossip[17057]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tHalloween2015_JackGame_Data["Aft_Time"])
end
tNpcGossip[17057]["Option6"] = tHalloween2015_JackGame_Text[17057]["Option6"]
--这个小游戏要怎么玩
tNpcGossip[17057]["Text2-1"] = {211,212,213}
tNpcGossip[17057]["Text211"] = tHalloween2015_JackGame_Text[17057]["Text211"]
tNpcGossip[17057]["Text212"] = tHalloween2015_JackGame_Text[17057]["Text212"]
tNpcGossip[17057]["Text213"] = tHalloween2015_JackGame_Text[17057]["Text213"]
tNpcGossip[17057]["tOption2-1"] = {7}
tNpcGossip[17057]["Option7"] = tHalloween2015_JackGame_Text[17057]["Option7"]
tNpcGossip[17057]["OptionPoint7"]="2-2"

tNpcGossip[17057]["Text2-2"] = {221,222,223}
tNpcGossip[17057]["Text221"] = tHalloween2015_JackGame_Text[17057]["Text221"]
tNpcGossip[17057]["Text222"] = tHalloween2015_JackGame_Text[17057]["Text222"]
tNpcGossip[17057]["Text223"] = tHalloween2015_JackGame_Text[17057]["Text223"]
tNpcGossip[17057]["tOption2-2"] = {8}
tNpcGossip[17057]["Option8"] = tHalloween2015_JackGame_Text[17057]["Option8"]
--我要领南瓜糕点！
--今日已完成
tNpcGossip[17057]["Text3-1"] = {311,312}
tNpcGossip[17057]["Text311"] = tHalloween2015_JackGame_Text[17057]["Text311"]
tNpcGossip[17057]["Text312"] = tHalloween2015_JackGame_Text[17057]["Text312"]
tNpcGossip[17057]["tOption3-1"] = {9}
tNpcGossip[17057]["Option9"] = tHalloween2015_JackGame_Text[17057]["Option9"]
--有卡或糕点
tNpcGossip[17057]["Text3-2"] = {321,322}
tNpcGossip[17057]["Text321"] = tHalloween2015_JackGame_Text[17057]["Text321"]
tNpcGossip[17057]["Text322"] = tHalloween2015_JackGame_Text[17057]["Text322"]
tNpcGossip[17057]["tOption3-2"] = {10,11}
tNpcGossip[17057]["Option10"] = tHalloween2015_JackGame_Text[17057]["Option10"]
tNpcGossip[17057]["OptionFunc10"]="Halloween2015_JackGame_Receive</N>3007233</N>17057"
tNpcGossip[17057]["Option11"] = tHalloween2015_JackGame_Text[17057]["Option11"]
--等级判断
tNpcGossip[17057]["Text3-3"] = {331}
tNpcGossip[17057]["Text331"] = tHalloween2015_JackGame_Text[17057]["Text331"]
tNpcGossip[17057]["tOption3-3"] = {12}
tNpcGossip[17057]["Option12"] = tHalloween2015_JackGame_Text[17057]["Option12"]
--背包满
tNpcGossip[17057]["Text3-4"] = {341}
tNpcGossip[17057]["Text341"] = tHalloween2015_JackGame_Text[17057]["Text341"]
tNpcGossip[17057]["tOption3-4"] = {13}
tNpcGossip[17057]["Option13"] = tHalloween2015_JackGame_Text[17057]["Option13"]
----领取糕点
tNpcGossip[17057]["Text3-5"] = {351,352,353}
tNpcGossip[17057]["Text351"] = tHalloween2015_JackGame_Text[17057]["Text351"]
tNpcGossip[17057]["Text352"] = tHalloween2015_JackGame_Text[17057]["Text352"]
tNpcGossip[17057]["Text353"] = tHalloween2015_JackGame_Text[17057]["Text353"]
tNpcGossip[17057]["tOption3-5"] = {9}
--我要猜数字！
--今日已完成
tNpcGossip[17057]["Text4-1"] = {411,412}
tNpcGossip[17057]["Text411"] = tHalloween2015_JackGame_Text[17057]["Text411"]
tNpcGossip[17057]["Text412"] = tHalloween2015_JackGame_Text[17057]["Text412"]
tNpcGossip[17057]["tOption4-1"] = {9}

tNpcGossip[17057]["Text4-2"] = {421,422,423}
tNpcGossip[17057]["Text421"] = tHalloween2015_JackGame_Text[17057]["Text421"]
tNpcGossip[17057]["Text422"] = tHalloween2015_JackGame_Text[17057]["Text422"]
tNpcGossip[17057]["Text423"] = tHalloween2015_JackGame_Text[17057]["Text423"]
tNpcGossip[17057]["tOption4-2"] = {14}
tNpcGossip[17057]["Option14"] = tHalloween2015_JackGame_Text[17057]["Option14"]
--今日完成后
tNpcGossip[17057]["Text4-3"] = {431,432,433}
tNpcGossip[17057]["Text431"] = tHalloween2015_JackGame_Text[17057]["Text431"]
tNpcGossip[17057]["Text432"] = tHalloween2015_JackGame_Text[17057]["Text432"]
tNpcGossip[17057]["Text433"] = tHalloween2015_JackGame_Text[17057]["Text433"]
tNpcGossip[17057]["tOption4-3"] = {15}
tNpcGossip[17057]["Option15"] = tHalloween2015_JackGame_Text[17057]["Option15"]





