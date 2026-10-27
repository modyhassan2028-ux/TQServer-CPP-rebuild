------------------------------------------------------------------------------------
--Name:			跨服任务刺探SQL数据
--Purpose:		跨服任务刺探SQL数据
--Creator: 		张磊
--Created:		12/03/2014
------------------------------------------------------------------------------------


--[[
任务需求：
麻烦转单给任务部同学，配合服务端程序提供相关任务脚本。

任务来自：http://nderp.99.com/Forum/TopicList-200932.aspx

]]--


------------------------------------------------------------------------------------
--掩码说明
--30001

--data1 : 31表示已经对话完所有探子npc
--data2 : ==1 表示已经领取过今天的奖励

--Stc掩码说明：
--stc(137,08) >0 表示已经领取过了 50 积分礼包
--stc(137,09) >0 表示已经领取过了 150 积分礼包
--stc(137,10) >0 表示已经领取过了 300 积分礼包

--LOGid 6189
------------------------------------------------------------------------------------
--命名规范
--National_War_
------------------------------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------NPC头像配置-------------------------------------------


tNpcFace[3323] = 92 -- 跨服任务大使
tNpcFace[3392] = 218 -- 闹市潜伏者
tNpcFace[3393] = 206 -- 神秘卧底
tNpcFace[3394] = 84 -- 军营间谍
tNpcFace[3395] = 94 -- 朝廷细作
tNpcFace[3396] = 231 -- 武林探子

local tNational_War_Num = {}
tNational_War_Num[17401] = 1
tNational_War_Num[17402] = 2
tNational_War_Num[17403] = 4
tNational_War_Num[17404] = 8
tNational_War_Num[17405] = 16




---------------------------------------------------------------------

--常量表设置
local tNational_War_Cont = {}

--玩家等级要求
	tNational_War_Cont["Metempsychosis"] = 1
	tNational_War_Cont["Level"] = 110

--掩码
	tNational_War_Cont["task_detail"] = 30001

--玩家完成的表示
	tNational_War_Cont["data1"] = 31

--背包空间 --兑换积分礼包
	tNational_War_Cont["nSpace"] = 1
	
--背包空间 --完成任务领奖
	tNational_War_Cont["nSpace_Reward"] = 2
	
--完成任务次数
	tNational_War_Cont["nTimes"] = 1
--领取完三次奖励的标示
	tNational_War_Cont["nFlag"] = 1
--完成 光效
	tNational_War_Cont["Self"] = "self"	
	tNational_War_Cont["Effect"] = "angelwing"
	
--每次完成任务加的积分
	tNational_War_Cont["Add_JF"] = 25
	
--每次完成任务给黄金联赛积分25
	tNational_War_Cont["Golden_JF"] = 100
	
--护心丹 数量2
	tNational_War_Cont["Reward_Num"] = 2

--积分上限
	tNational_War_Cont["JF_Limit"] = 300
	
--礼包奖励分段
	tNational_War_Cont["50"] = 50
	tNational_War_Cont["150"] = 150
	tNational_War_Cont["300"] = 300
	
--天石完成任务消耗 5
	tNational_War_Cont["Emoney_10CP"] = 10
--修为上限
	tNational_War_Cont["User_NG"] = 9999999999
--黄金联赛积分上限 343700
	tNational_War_Cont["Golden_Limt"] = 343700
--战功上限
	tNational_War_Cont["User_XW"] = 9999999999
--魔君入侵
	tNational_War_Cont["Task_35007"] = 35007


local tNational_War_Item = {}

--50积分礼包
tNational_War_Item["3007108"] = 3007108
tNational_War_Item["3007109"] = 3007109
tNational_War_Item["3007110"] = 3007110

tNational_War_Item["Monoply"] = "0 1 0 10080 1"

--护心丹 2颗
tNational_War_Item["Item_3002029"] = 3002029
--属性
tNational_War_Item["Attribute_3002029"] = "0 2 0 0 1"
--数量
tNational_War_Item["Num_3002029"] = 2

local tNational_War_JF = {}

tNational_War_JF["Min"] = 50
tNational_War_JF["Mid"] = 150
tNational_War_JF["Max"] = 300

local tNational_War_JFPack = {}
tNational_War_JF[1] = 3007108
tNational_War_JF[2] = 3007109
tNational_War_JF[3] = 3007110

local tNational_War_PackStc = {}
tNational_War_PackStc[1] = {}
tNational_War_PackStc[1]["EventType"] = 137
tNational_War_PackStc[1]["DataType"] = 08

tNational_War_PackStc[2] = {}
tNational_War_PackStc[2]["EventType"] = 137
tNational_War_PackStc[2]["DataType"] = 09

tNational_War_PackStc[3] = {}
tNational_War_PackStc[3]["EventType"] = 137
tNational_War_PackStc[3]["DataType"] = 10

---------------------------------奖励配置---------------------------------
tNational_War_Item[3007108] = {}
tNational_War_Item[3007108]["User_ZG"] = 50
tNational_War_Item[3007108]["User_NG"] = 400
tNational_War_Item[3007108]["User_LMEmoney"] = 50

tNational_War_Item[3007109] = {}
tNational_War_Item[3007109]["Golden_JF"] = 50
tNational_War_Item[3007109]["User_ZG"] = 100
tNational_War_Item[3007109]["User_NG"] = 600
tNational_War_Item[3007109]["User_LMEmoney"] = 160

tNational_War_Item[3007110] = {}
tNational_War_Item[3007110]["Golden_JF"] = 100
tNational_War_Item[3007110]["User_ZG"] = 150
tNational_War_Item[3007110]["User_NG"] = 1000
tNational_War_Item[3007110]["User_LMEmoney"] = 360



local tNational_War_Stc = {}

tNational_War_Stc[50] = {}
tNational_War_Stc[50]["EventType"] = 137
tNational_War_Stc[50]["DataType"] = 08

tNational_War_Stc[150] = {}
tNational_War_Stc[150]["EventType"] = 137
tNational_War_Stc[150]["DataType"] = 09

tNational_War_Stc[300] = {}
tNational_War_Stc[300]["EventType"] = 137
tNational_War_Stc[300]["DataType"] = 10

local tNational_War_FindNpc = {}

tNational_War_FindNpc[1] = {}
tNational_War_FindNpc[1]["nMapId"] = 3935
tNational_War_FindNpc[1]["nPosX"] = 195
tNational_War_FindNpc[1]["nPosY"] = 174

tNational_War_FindNpc[2] = {}
tNational_War_FindNpc[2]["nMapId"] = 3935
tNational_War_FindNpc[2]["nPosX"] = 234
tNational_War_FindNpc[2]["nPosY"] = 243

tNational_War_FindNpc[3] = {}
tNational_War_FindNpc[3]["nMapId"] = 3935
tNational_War_FindNpc[3]["nPosX"] = 214
tNational_War_FindNpc[3]["nPosY"] = 284

tNational_War_FindNpc[4] = {}
tNational_War_FindNpc[4]["nMapId"] = 1002
tNational_War_FindNpc[4]["nPosX"] = 281
tNational_War_FindNpc[4]["nPosY"] = 291

local tNational_War_EmoneyLOG = {}
--参与
	tNational_War_EmoneyLOG["Participate"] = "350	4307	0	0	1	"
--完成
	tNational_War_EmoneyLOG["Complete"] = "350	4308	0	0	1	"
--付费完成
	tNational_War_EmoneyLOG["CostEmoney"] = "350	4314	10	10	1	"
--付费补足积分
	tNational_War_EmoneyLOG["FillUp"] = "350	4313	%d	%d	1	"

local tNational_War_ActionLog = {}
	tNational_War_ActionLog["LOG"] = "0,0,0,0,18000070,2,%d,1"
	
local tNational_War_JFCont = {}
	--积分段
	tNational_War_JFCont["Min"] = 50
	tNational_War_JFCont["Mid"] = 150
	tNational_War_JFCont["Max"] = 300
	
	--补足对应的天石
	tNational_War_JFCont[1] = 99
	tNational_War_JFCont[2] = 54
	tNational_War_JFCont[3] = 27
	
----------------------------------------------逻辑部分--------------------
--兑换对话显示
function National_War_Dialog(nNpcId)
	 -- local nNum = 0
	 -- if Task_ChkTaskDetail(35011) then
	 	-- nNum = Get_TaskDetailData1(35011)
	 -- end
	 str = string.format(tNational_War_Text[17400]["Text953"],National_War_ChkIntegral())

	Sys_DialogText(tNational_War_Text[17400]["Text951"])
	Sys_DialogText(tNational_War_Text[17400]["Text952"])
	Sys_DialogText(str)
	Sys_DialogOption(tNational_War_Text[17400]["Option33"],"</F>National_War_Points_For</N>17400</N>50")
	Sys_DialogOption(tNational_War_Text[17400]["Option34"],"</F>National_War_Points_For</N>17400</N>150")
	Sys_DialogOption(tNational_War_Text[17400]["Option35"],"</F>National_War_Points_For</N>17400</N>300")
	Sys_DialogOption(tNational_War_Text[17400]["Option50"],"</F>LinkNpcGossipFunc_New</N>17400</S>12-1")
	Sys_DialogOption(tNational_War_Text[17400]["Option40"],"</F>LinkNpcGossipFunc_New</N>17400</S>11-1")
	Sys_DialogOption(tNational_War_Text[17400]["Option41"])
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end

--付费补足积分
function National_War_CostCp(nNpcId)
	-- 玩家积分状态标示
	local nFlag = 0
	-- 判断玩家是否有功勋值掩码，没有直接创建并补满积分
	if not Task_ChkTaskDetail(35011) then
		Task_AddTaskDetail(35011)
		nFlag = 1
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Max"] then
		LinkNpcGossipFunc_New(nNpcId,"13-1")
		return
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Mid"] then
		nFlag = 3
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Min"] then
		nFlag = 2
	else
		nFlag = 1
	end
	
	-- 扣天石，补足功勋追
	if not User_AddEMoney(-tNational_War_JFCont[nFlag]) then
		LinkNpcGossipFunc_New(nNpcId,"14-1")
		return
	end
	
	-- 扣天石成功	
	Task_SetTaskDetailData6(35011,tNational_War_Cont["JF_Limit"])
	Task_SetTaskDetailData7(35011,os.time())
	
	local str = string.format(tNational_War_EmoneyLOG["FillUp"],tNational_War_JFCont[nFlag],tNational_War_JFCont[nFlag])
	Sys_SaveEmoneyBuy(str)
	User_TalkChannel2005(tNational_War_Text["CostCP"])
	LinkNpcGossipFunc_New(nNpcId,"9-5")
end




function National_War_AddIntegral(nData)
	if not Task_ChkTaskDetail(35011) then
		Task_AddTaskDetail(35011)
	end
	
	if Get_TaskDetailData6(35011) >= tNational_War_Cont["JF_Limit"] then
		return false
	end
	
	local nData6 = Get_TaskDetailData6(35011) + nData
	
	if nData6 >= tNational_War_Cont["JF_Limit"] then
		nData6 = tNational_War_Cont["JF_Limit"]
	end	
	
	Task_SetTaskDetailData6(35011,nData6)
	Task_SetTaskDetailData7(35011,os.time())
	return true
end


--积分查询
function National_War_ChkIntegral()
	local nData = 0
	if not Task_ChkTaskDetail(35011) then
		nData = 0
	else
		nData = Get_TaskDetailData6(35011)
	end
	
	return nData
end


--点击刺探任务   接受任务
function National_War_CheckDailyReset(nTask_detail)
	if not Task_ChkTaskDetail(nTask_detail) then
		Task_AddTaskDetail(nTask_detail,0)
		return
	end
	if Task_DetailInterval(nTask_detail,1,4) then
		Task_SetTaskDetailData1(nTask_detail,0)
		Task_SetTaskDetailData2(nTask_detail,0)
		Task_SetTaskDetailData3(nTask_detail,0)
		Task_SetTaskDetailData6(nTask_detail,0)
		Task_SetTaskDetailCompleteFlag(nTask_detail,0)
		Task_SetTaskDetailData7(nTask_detail,os.time())
	end
end

function National_War_AcceptTask(nNpcId)
	local nTask_detail = tNational_War_Cont["task_detail"]

	--判断玩家等级情况
	if not User_JudgeLevelAndMetempsychosis(tNational_War_Cont["Level"],tNational_War_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	if not Task_ChkTaskDetail(nTask_detail) then
		Task_AddTaskDetail(nTask_detail,0)
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	National_War_CheckDailyReset(nTask_detail)
	
	if Get_TaskDetailData6(nTask_detail) >= tNational_War_Cont["nTimes"] then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	if Get_TaskDetailData3(nTask_detail) ~= 0 then
		User_TalkChannel2005(tNational_War_Text["DirectlyRward"])
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"2-2")
end

function National_War_RewardItem(nNpcId)
	--判断玩家等级情况
	if not User_JudgeLevelAndMetempsychosis(tNational_War_Cont["Level"],tNational_War_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nTask_detail = tNational_War_Cont["task_detail"]

	if not Task_ChkTaskDetail(nTask_detail) then
		Task_AddTaskDetail(nTask_detail,0)
	end
	National_War_CheckDailyReset(nTask_detail)
	
	--判断当天是否完成1次了
	if Get_TaskDetailData6(nTask_detail) >= tNational_War_Cont["nTimes"] then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	--是否领取达到领取奖励条件(是否已经刺探了三个人了)
	if Get_TaskDetailData3(nTask_detail) == 0 then
		LinkNpcGossipFunc_New(nNpcId,"6-1")
		return
	end
	
		--判断背包空间
	local nSpace_Reward = tNational_War_Cont["nSpace_Reward"]
	if not User_CheckLeftSpace(nSpace_Reward) then
		LinkNpcGossipFunc_New(nNpcId,"10-1")
		return
	end
	
	local nData6 = Get_TaskDetailData6(nTask_detail) + 1
	Task_SetTaskDetailData6(nTask_detail,nData6)
	Task_SetTaskDetailData1(nTask_detail,0)
	Task_SetTaskDetailData2(nTask_detail,0)
	Task_SetTaskDetailData3(nTask_detail,0)
	Task_SetTaskDetailCompleteFlag(nTask_detail,1)
	local nTime = os.time()
	Task_SetTaskDetailData7(nTask_detail,nTime)

	--黄金联赛积分25
	GoldenLeaguePoints_Add(tNational_War_Cont["Golden_JF"])
	
	--给护心丹 激活
	Item_AddNewItem(tNational_War_Item["Item_3002029"],tNational_War_Item["Attribute_3002029"])
	
    Sys_SaveEmoneyBuy(tNational_War_EmoneyLOG["Complete"])
	LinkNpcGossipFunc_New(nNpcId,"5-1")
	User_EffectAdd(tNational_War_Cont["Self"],tNational_War_Cont["Effect"])
	
	local str_1 = ""
	--完成给积分
	if National_War_AddIntegral(tNational_War_Cont["Add_JF"]) then
		str_1 = string.format(tNational_War_Text["Get_JF"],tNational_War_Cont["Add_JF"],tNational_War_Item["Num_3002029"])
	else
		str_1 = string.format(tNational_War_Text["Get_JF_1"],tNational_War_Item["Num_3002029"])
	end
	User_TalkChannel2005(str_1)
end


--点击刺探的npc时完成刺探选项函数
function National_War_SpyConditJud()
	local nNpcId = Get_NpcId()
	local nTask_detail = tNational_War_Cont["task_detail"]

	National_War_CheckDailyReset(nTask_detail)
	
	if Get_TaskDetailData3(nTask_detail) ~= 0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return false
	end
	
	local nSumData = Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)

	if User_IsCross() and (not Sys_ParseNumbersContain(tNational_War_Num[nNpcId],nSumData)) then
		
		return true
	end
	
	return false

end

--该机密我记住了！
function National_War_SpyComplete(nNpcId)
	local nTask_detail = tNational_War_Cont["task_detail"]
	National_War_CheckDailyReset(nTask_detail)
	
	if Get_TaskDetailData3(nTask_detail) ~= 0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		Sys_MsgBox(tNational_War_Text["SysMsgCom"])
		return
	end
	
	local nSumData = Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)
	
	if not Sys_ParseNumbersContain(tNational_War_Num[nNpcId],nSumData) then
		if Get_TaskDetailData1(nTask_detail) == 0 then
			Task_SetTaskDetailData1(nTask_detail,tNational_War_Num[nNpcId])
		elseif Get_TaskDetailData2(nTask_detail) == 0 then
			Task_SetTaskDetailData2(nTask_detail,tNational_War_Num[nNpcId])
		else
			Task_SetTaskDetailData3(nTask_detail,tNational_War_Num[nNpcId])
		end
		Sys_SaveEmoneyBuy(tNational_War_EmoneyLOG["Participate"])
	end
	
	if Get_TaskDetailData3(nTask_detail) ~= 0 then
		Sys_MsgBox(tNational_War_Text["SysMsgCom"])
		return
	end
	User_TalkChannel2005(tNational_War_Text["SysMsg"])
end


--点击NPC时判断完成否
function  National_War_Complete()
	local nTask_detail = tNational_War_Cont["task_detail"]
	
	if not Task_ChkTaskDetail(nTask_detail) then
		return false
	end
	if  Get_TaskDetailData3(nTask_detail) ~= 0 or Get_TaskDetailData6(nTask_detail) then
		return true
	else
		return false
	end
	
end

--花费5天石直接完成任务
function National_War_SpyCompleteByFiveCP(nNpcId)
	local nTask_detail = tNational_War_Cont["task_detail"]
	
	if not Task_ChkTaskDetail(nTask_detail) then
		Task_AddTaskDetail(nTask_detail,0)
	end
	National_War_CheckDailyReset(nTask_detail)
	
	if Get_TaskDetailData6(nTask_detail) > 0 then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	--判断背包空间
	local nSpace_Reward = 	tNational_War_Cont["nSpace_Reward"]
	if not User_CheckLeftSpace(nSpace_Reward)  then
		LinkNpcGossipFunc_New(nNpcId,"10-1")
		return
	end
	
	local nMoney = Get_UserEMoney()
	
	if nMoney < tNational_War_Cont["Emoney_10CP"] then
		LinkNpcGossipFunc_New(nNpcId,"9-4")
		return
	end
	
	--满足条件
	if not User_AddEMoney(-tNational_War_Cont["Emoney_10CP"]) then
		return
	end
	
	local nData6 = Get_TaskDetailData6(nTask_detail) + 1
	Task_SetTaskDetailData6(nTask_detail,nData6)
	Task_SetTaskDetailData1(nTask_detail,0)
	Task_SetTaskDetailData2(nTask_detail,0)
	Task_SetTaskDetailData3(nTask_detail,0)
	Task_SetTaskDetailCompleteFlag(nTask_detail,1)
		
	local nTime = os.time()
	Task_SetTaskDetailData7(nTask_detail,nTime)
		
	--黄金联赛积分25
	GoldenLeaguePoints_Add(tNational_War_Cont["Golden_JF"])
	
	--给护心丹 激活
	Item_AddNewItem(tNational_War_Item["Item_3002029"],tNational_War_Item["Attribute_3002029"])
	
    Sys_SaveEmoneyBuy(tNational_War_EmoneyLOG["CostEmoney"])
	LinkNpcGossipFunc_New(nNpcId,"5-1")
	User_EffectAdd(tNational_War_Cont["Self"],tNational_War_Cont["Effect"])
	
	local str_1 = ""
	--完成给积分
	if National_War_AddIntegral(tNational_War_Cont["Add_JF"]) then
		str_1 = string.format(tNational_War_Text["Get_JF"],tNational_War_Cont["Add_JF"],tNational_War_Item["Num_3002029"])
	else
		str_1 = string.format(tNational_War_Text["Get_JF_1"],tNational_War_Item["Num_3002029"])
	end
	User_TalkChannel2005(str_1)
end

--积分兑换奖励
function National_War_Points_For(nNpcId,nJFNum)
--判断掩码情况
	if Task_StcInterval(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],1,4) then		
		Task_SetStatistic(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],0,1)	
		Task_SetStcTimestamp(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],0)
	end
	
	if Task_ChkStcValue(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],"==",1) then
		Sys_MsgBox(tNational_War_Text["GetRepeat"])
		return
	end
	--判断积分
	if National_War_ChkIntegral() == nil or National_War_ChkIntegral() < nJFNum then
		local sText = string.format(tNational_War_Text[17400]["Text961"],nJFNum)
			Sys_DialogText(sText)
			Sys_DialogOption(tNational_War_Text[17400]["Option36"])
			Sys_DialogFace()
			Sys_DialogEnd()	
	else
		local nSpace = tNational_War_Cont["nSpace"]
		if not User_CheckLeftSpace(nSpace) then
			LinkNpcGossipFunc_New(nNpcId,"9-9")
			return
		end
		
		Task_SetStatistic(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],1,1)
		Task_SetStcTimestamp(tNational_War_Stc[nJFNum]["EventType"],tNational_War_Stc[nJFNum]["DataType"],0)
		
		--给奖励
		if nJFNum == tNational_War_Cont["50"] then
			Item_AddNewItem(tNational_War_Item["3007108"],tNational_War_Item["Monoply"])
		elseif nJFNum == tNational_War_Cont["150"] then
			Item_AddNewItem(tNational_War_Item["3007109"],tNational_War_Item["Monoply"])
		elseif nJFNum == tNational_War_Cont["300"] then
			Item_AddNewItem(tNational_War_Item["3007110"],tNational_War_Item["Monoply"])
		end
		LinkNpcGossipFunc_New(nNpcId,"9-8")
	end
end


--积分礼包使用
function National_War_ItemUse(nItem)
	local str_1 = ""
	if nItem == tNational_War_Item["3007108"] then
		
		if Get_UserServiceValue() > (tNational_War_Cont["User_NG"] - tNational_War_Item[3007108]["User_ZG"]) then
			User_TalkChannel2005(tNational_War_Text["MoreCulture"])
			return
		end
		
		--修为没满
		--给奖励
		if not Item_DelItem(nItem) then
			return
		end
		User_AddServiceValue(tNational_War_Item[3007108]["User_ZG"])
		User_AddCultureValue(tNational_War_Item[3007108]["User_NG"])
		User_AddLeagueMoney(tNational_War_Item[3007108]["User_LMEmoney"])
		str_1 = string.format(tNational_War_Text["GetCultureValue"],tNational_War_Item[3007108]["User_NG"],tNational_War_Item[3007108]["User_ZG"],tNational_War_Item[3007108]["User_LMEmoney"])
		User_TalkChannel2005(str_1)
	elseif nItem == tNational_War_Item["3007109"] then
		
		if Get_UserServiceValue() > (tNational_War_Cont["User_NG"] - tNational_War_Item[3007109]["User_ZG"]) then
			User_TalkChannel2005(tNational_War_Text["MoreCulture"])
			return
		end
		--给奖励
		--给奖励
		if not Item_DelItem(nItem) then
			return
		end
		User_AddServiceValue(tNational_War_Item[3007109]["User_ZG"])
		User_AddCultureValue(tNational_War_Item[3007109]["User_NG"])
		User_AddLeagueMoney(tNational_War_Item[3007109]["User_LMEmoney"])
				
		--修为 未满，判断黄金联赛积分
		GoldenLeaguePoints_Add(tNational_War_Item[3007109]["Golden_JF"])


		str_1 = string.format(tNational_War_Text["GetCultureValue"],tNational_War_Item[3007109]["User_NG"],tNational_War_Item[3007109]["User_ZG"],tNational_War_Item[3007109]["User_LMEmoney"])

		User_TalkChannel2005(str_1)
		
	elseif nItem == tNational_War_Item["3007110"] then
		if Get_UserServiceValue() > (tNational_War_Cont["User_NG"] - tNational_War_Item[3007110]["User_ZG"]) then
			User_TalkChannel2005(tNational_War_Text["MoreCulture"])
			return
		end
		--给奖励
		--给奖励
		if not Item_DelItem(nItem) then
			return
		end
		User_AddServiceValue(tNational_War_Item[3007110]["User_ZG"])
		User_AddCultureValue(tNational_War_Item[3007110]["User_NG"])
		User_AddLeagueMoney(tNational_War_Item[3007110]["User_LMEmoney"])
				
		--修为 未满，判断黄金联赛积分
		GoldenLeaguePoints_Add(tNational_War_Item[3007110]["Golden_JF"])
		
		str_1 = string.format(tNational_War_Text["GetCultureValue"],tNational_War_Item[3007110]["User_NG"],tNational_War_Item[3007110]["User_ZG"],tNational_War_Item[3007110]["User_LMEmoney"])
		User_TalkChannel2005(str_1)
	end
end


--跨服物品使用
function National_War_FindWay(nItem,nFlag)
	Sys_GotoSomeWhere(tNational_War_FindNpc[nFlag]["nPosX"],tNational_War_FindNpc[nFlag]["nPosY"],tNational_War_FindNpc[nFlag]["nMapId"])	
end

-- 点击“跨服任务大使”直接判断积分给礼包
function National_War_GetJFPack()
	if not Task_ChkTaskDetail(35011) then
		return
	end
	
	-- 判断是否为跨服玩家  跨服玩家就不执行
	if User_IsCross() then
		return
	end
	
	local nFlag = 0
	local nNum = 0
	-- 判断玩家积分区间
	if Get_TaskDetailData6(35011) < tNational_War_JF["Min"] then
		return
	elseif Get_TaskDetailData6(35011) < tNational_War_JF["Mid"] then
		nFlag = 1
	elseif Get_TaskDetailData6(35011) < tNational_War_JF["Max"]then
		nFlag = 2
	else
		nFlag = 3
	end
	
	if nFlag > 0 then
		for i = 1,nFlag do
			--判断是否已经领取过了
			if Task_StcInterval(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],1,4) then		
				Task_SetStatistic(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],0,1)	
				Task_SetStcTimestamp(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],0)
			end
	
			if Task_ChkStcValue(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],"==",0) then
				--判断空间
				if not User_CheckLeftSpace(tNational_War_Cont["nSpace"]) then
					return
				end
				Task_SetStatistic(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],1,1)
				Task_SetStcTimestamp(tNational_War_PackStc[i]["EventType"],tNational_War_PackStc[i]["DataType"],0)
				
				if Item_AddNewItem(tNational_War_JF[i],tNational_War_Item["Monoply"]) then
					nNum = nNum + 1
					Sys_SaveActionTaskLog(string.format(tNational_War_ActionLog["LOG"],tNational_War_JF[i]))
				end
			end
		end
		if nNum > 0 then
			User_TalkChannel2005(tNational_War_Text["GetJFPack"])
		end
	end
end

-- 上线添加功勋值掩码 35011
function National_War_OnlAddTask()
	if not User_JudgeLevelAndMetempsychosis(tNational_War_Cont["Level"],tNational_War_Cont["Metempsychosis"]) then
		return
	end
	
	local nSpyTask = tNational_War_Cont["task_detail"]
	National_War_CheckDailyReset(nSpyTask)
	
	if not Task_ChkTaskDetail(35011) then
		Task_AddTaskDetail(35011)
	end
end


-------------------------------------------npc模块------------------------------------

--国战任务军师
tNpcGossip[17400] = tNpcGossip[17400] or DefaultNpc:new{}
tNpcGossip[17400]["OptionHidden"] = 1

tNpcGossip[17400]["Text1-1"] = {111,112,113}
tNpcGossip[17400]["Text111"] = tNational_War_Text[17400]["Text111"]
tNpcGossip[17400]["Text112"] = tNational_War_Text[17400]["Text112"]
tNpcGossip[17400]["Text113"] = tNational_War_Text[17400]["Text113"]
tNpcGossip[17400]["nPageNum"] = 6
tNpcGossip[17400]["tOption1-1"] = {1,301,10013,10016,600,750,499,498,700,100,4}
tNpcGossip[17400]["ChkFunc1-1"] = function ()
	 return not User_IsCross()
end

--点击主对白刺探选项进入下一层对白
tNpcGossip[17400]["Text2-1"] = {211,212,213}
tNpcGossip[17400]["Text211"] = tNational_War_Text[17400]["Text211"]
tNpcGossip[17400]["Text212"] = tNational_War_Text[17400]["Text212"]
tNpcGossip[17400]["Text213"] = tNational_War_Text[17400]["Text213"]
tNpcGossip[17400]["tOption2-1"] = {5,30,31,21}
tNpcGossip[17400]["ChkFunc2-1"] = function ()
	 return not User_IsCross()
end


--点击接受/完成任务刺探任务--接任务
tNpcGossip[17400]["Text2-2"] = {221,222,223}
tNpcGossip[17400]["Text221"] = tNational_War_Text[17400]["Text221"]
tNpcGossip[17400]["Text222"] = tNational_War_Text[17400]["Text222"]
tNpcGossip[17400]["Text223"] = tNational_War_Text[17400]["Text223"]
tNpcGossip[17400]["tOption2-2"] = {22}

--点击接受/完成任务刺探任务--完成任务
tNpcGossip[17400]["Text5-1"] = {511,512}
tNpcGossip[17400]["Text511"] = tNational_War_Text[17400]["Text511"]
tNpcGossip[17400]["Text512"] = tNational_War_Text[17400]["Text512"]
tNpcGossip[17400]["tOption5-1"] = {26}

--玩家未完成任务
tNpcGossip[17400]["Text6-1"] = {611,612}
tNpcGossip[17400]["Text611"] = tNational_War_Text[17400]["Text611"]
tNpcGossip[17400]["Text612"] = tNational_War_Text[17400]["Text612"]
tNpcGossip[17400]["tOption6-1"] = {24}

--玩家当天已经完成
tNpcGossip[17400]["Text4-1"] = {411}
tNpcGossip[17400]["Text411"] = tNational_War_Text[17400]["Text411"]
tNpcGossip[17400]["tOption4-1"] = {22}

--玩家等级不足
tNpcGossip[17400]["Text3-1"] = {311,312}
tNpcGossip[17400]["Text311"] = tNational_War_Text[17400]["Text311"]
tNpcGossip[17400]["Text312"] = tNational_War_Text[17400]["Text312"]
tNpcGossip[17400]["tOption3-1"] = {22}

--没任务提示
tNpcGossip[17400]["Text9-3"] = {931}
tNpcGossip[17400]["Text931"] = tNational_War_Text[17400]["Text931"] 
tNpcGossip[17400]["tOption9-3"] = {25}

--天石不足
tNpcGossip[17400]["Text9-4"] = {941}
tNpcGossip[17400]["Text941"] = tNational_War_Text[17400]["Text941"]
tNpcGossip[17400]["tOption9-4"] = {22}

--玖．跨服功勋值兑换奖励
tNpcGossip[17400]["Text9-5"] = {951,952,953}
tNpcGossip[17400]["Text951"] = tNational_War_Text[17400]["Text951"]
tNpcGossip[17400]["Text952"] = tNational_War_Text[17400]["Text952"]
tNpcGossip[17400]["Text953"] = tNational_War_Text[17400]["Text953"]
tNpcGossip[17400]["tOption9-5"] = {33,34,35,40,41}
tNpcGossip[17400]["ChkFunc9-5"] = function ()
	
	local nNum = 0
	if not Task_ChkTaskDetail(35011) then
		nNum = 0
	else
		nNum = Get_TaskDetailData6(35011)
	end
	tNpcGossip[17400]["Text953"] = string.format(tNational_War_Text[17400]["Text953"],nNum)
	return true
end

--【玩家选择、失败、积分未达到】
tNpcGossip[17400]["Text9-6"] = {961}
tNpcGossip[17400]["Text961"] = tNational_War_Text[17400]["Text961"]
tNpcGossip[17400]["tOption9-6"] = {36}


--【玩家选择、失败、已领取该礼包】
tNpcGossip[17400]["Text9-7"] = {971}
tNpcGossip[17400]["Text971"] = tNational_War_Text[17400]["Text971"]
tNpcGossip[17400]["tOption9-7"] = {37}

--【玩家选择、成功领取】
tNpcGossip[17400]["Text9-8"] = {981}
tNpcGossip[17400]["Text981"] = tNational_War_Text[17400]["Text981"]
tNpcGossip[17400]["tOption9-8"] = {38}

tNpcGossip[17400]["Text9-9"] = {991}
tNpcGossip[17400]["Text991"] = tNational_War_Text[17400]["Text991"]
tNpcGossip[17400]["tOption9-9"] = {37}

tNpcGossip[17400]["Text10-1"] = {1011}
tNpcGossip[17400]["Text1011"] = tNational_War_Text[17400]["Text1011"]
tNpcGossip[17400]["tOption10-1"] = {37}

--查看礼包奖励内容。
tNpcGossip[17400]["Text11-1"] = {1111,1112,1113}
tNpcGossip[17400]["Text1111"] = tNational_War_Text[17400]["Text1111"]
tNpcGossip[17400]["Text1112"] = tNational_War_Text[17400]["Text1112"]
tNpcGossip[17400]["Text1113"] = tNational_War_Text[17400]["Text1113"]
tNpcGossip[17400]["tOption11-1"] = {42}

-- 闹市潜伏者
tNpcGossip[17401] = tNpcGossip[17401] or DefaultNpc:new{}
tNpcGossip[17401]["OptionHidden"] = 1

--任务对白
tNpcGossip[17401]["Text1-1"] = {111,112}
tNpcGossip[17401]["Text111"] = tNational_War_Text[17401]["Text111"]
tNpcGossip[17401]["Text112"] = tNational_War_Text[17401]["Text112"]
tNpcGossip[17401]["tOption1-1"] = {9}
tNpcGossip[17401]["ChkFunc1-1"] = function ()
	return National_War_SpyConditJud()
end

--闲聊对白
tNpcGossip[17401]["Text1-2"] = {121}
tNpcGossip[17401]["Text121"] = tNational_War_Text[17401]["Text121"]
tNpcGossip[17401]["tOption1-2"] = {8}
tNpcGossip[17401]["ChkFunc1-2"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	 
	if not Task_ChkTaskDetail(nTask_detail) then
	 	return true
	elseif Get_TaskDetailData3(nTask_detail) ~=0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return true
	elseif Sys_ParseNumbersContain(tNational_War_Num[17401],Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)) then
		return false
	else
		return true
	end
end

tNpcGossip[17401]["Text1-3"] = {131}
tNpcGossip[17401]["Text131"] = tNational_War_Text[17401]["Text131"]
tNpcGossip[17401]["tOption1-3"] = {8}



-- 神秘卧底
tNpcGossip[17402] = tNpcGossip[17402] or DefaultNpc:new{}
tNpcGossip[17402]["OptionHidden"] = 1
--任务对白

tNpcGossip[17402]["Text1-1"] = {111,112}
tNpcGossip[17402]["Text111"] = tNational_War_Text[17402]["Text111"]
tNpcGossip[17402]["Text112"] = tNational_War_Text[17402]["Text112"]
tNpcGossip[17402]["tOption1-1"] = {11}
tNpcGossip[17402]["ChkFunc1-1"] = function ()
	return National_War_SpyConditJud()
end

--闲聊对白
tNpcGossip[17402]["Text1-2"] = {121}
tNpcGossip[17402]["Text121"] = tNational_War_Text[17402]["Text121"]
tNpcGossip[17402]["tOption1-2"] = {10}
tNpcGossip[17402]["ChkFunc1-2"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	 
	if not Task_ChkTaskDetail(nTask_detail) then
	 	return true
	elseif Get_TaskDetailData3(nTask_detail) ~=0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return true
	elseif Sys_ParseNumbersContain(tNational_War_Num[17402],Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)) then
		return false
	else
		return true
	end
end

tNpcGossip[17402]["Text1-3"] = {131}
tNpcGossip[17402]["Text131"] = tNational_War_Text[17402]["Text131"]
tNpcGossip[17402]["tOption1-3"] = {10}

-- 军营间谍
tNpcGossip[17403] = tNpcGossip[17403] or DefaultNpc:new{}
tNpcGossip[17403]["OptionHidden"] = 1

--任务对白

tNpcGossip[17403]["Text1-1"] = {111,112}
tNpcGossip[17403]["Text111"] = tNational_War_Text[17403]["Text111"]
tNpcGossip[17403]["Text112"] = tNational_War_Text[17403]["Text112"]
tNpcGossip[17403]["tOption1-1"] = {13}
tNpcGossip[17403]["ChkFunc1-1"] = function ()
	return National_War_SpyConditJud()
end

--闲聊对白
tNpcGossip[17403]["Text1-2"] = {121}
tNpcGossip[17403]["Text121"] = tNational_War_Text[17403]["Text121"]
tNpcGossip[17403]["tOption1-2"] = {12}
tNpcGossip[17403]["ChkFunc1-2"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	 
	if not Task_ChkTaskDetail(nTask_detail) then
	 	return true
	elseif Get_TaskDetailData3(nTask_detail) ~=0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return true
	elseif Sys_ParseNumbersContain(tNational_War_Num[17403],Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)) then
		return false
	else
		return true
	end
end

tNpcGossip[17403]["Text1-3"] = {131}
tNpcGossip[17403]["Text131"] = tNational_War_Text[17403]["Text131"]
tNpcGossip[17403]["tOption1-3"] = {12}

-- 朝廷细作
tNpcGossip[17404] = tNpcGossip[17404] or DefaultNpc:new{}
tNpcGossip[17404]["OptionHidden"] = 1

--任务对白
tNpcGossip[17404]["Text1-1"] = {111,112}
tNpcGossip[17404]["Text111"] = tNational_War_Text[17404]["Text111"]
tNpcGossip[17404]["Text112"] = tNational_War_Text[17404]["Text112"]
tNpcGossip[17404]["tOption1-1"] = {15}
tNpcGossip[17404]["ChkFunc1-1"] = function ()
	return National_War_SpyConditJud()
end

--闲聊对白
tNpcGossip[17404]["Text1-2"] = {121}
tNpcGossip[17404]["Text121"] = tNational_War_Text[17404]["Text121"]
tNpcGossip[17404]["tOption1-2"] = {14}
tNpcGossip[17404]["ChkFunc1-2"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	 
	if not Task_ChkTaskDetail(nTask_detail) then
	 	return true
	elseif Get_TaskDetailData3(nTask_detail) ~=0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return true
	elseif Sys_ParseNumbersContain(tNational_War_Num[17404],Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)) then
		return false
	else
		return true
	end
end

tNpcGossip[17404]["Text1-3"] = {131}
tNpcGossip[17404]["Text131"] = tNational_War_Text[17404]["Text131"]
tNpcGossip[17404]["tOption1-3"] = {14}


-- 武林探子
tNpcGossip[17405] = tNpcGossip[17405] or DefaultNpc:new{}
tNpcGossip[17405]["OptionHidden"] = 1


--任务对白
tNpcGossip[17405]["Text1-1"] = {111,112}
tNpcGossip[17405]["Text111"] = tNational_War_Text[17405]["Text111"]
tNpcGossip[17405]["Text112"] = tNational_War_Text[17405]["Text112"]
tNpcGossip[17405]["tOption1-1"] = {17}
tNpcGossip[17405]["ChkFunc1-1"] = function ()
	return National_War_SpyConditJud()
end

--闲聊对白
tNpcGossip[17405]["Text1-2"] = {121}
tNpcGossip[17405]["Text121"] = tNational_War_Text[17405]["Text121"]
tNpcGossip[17405]["tOption1-2"] = {16}
tNpcGossip[17405]["ChkFunc1-2"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	 
	if not Task_ChkTaskDetail(nTask_detail) then
	 	return true
	elseif Get_TaskDetailData3(nTask_detail) ~=0 or Get_TaskDetailData6(nTask_detail) ~= 0 then
		return true
	elseif Sys_ParseNumbersContain(tNational_War_Num[17405],Get_TaskDetailData1(nTask_detail) + Get_TaskDetailData2(nTask_detail) + Get_TaskDetailData3(nTask_detail)) then
		return false
	else
		return true
	end
end

tNpcGossip[17405]["Text1-3"] = {131}
tNpcGossip[17405]["Text131"] = tNational_War_Text[17405]["Text131"]
tNpcGossip[17405]["tOption1-3"] = {16}


--点击主对白刺探选项进入下一层对白
tNpcGossip[17400]["Option1"]=tNational_War_Text[17400]["Option1"]
tNpcGossip[17400]["OptionPoint1"] = "2-1"
tNpcGossip[17400]["OptionChkFunc1"] = function ()
	return  User_IsCross() == false
end


--第一层对白选项

tNpcGossip[17400]["Option4"]=tNational_War_Text[17400]["Option4"]

--第二层对白选项
tNpcGossip[17400]["Option5"]=tNational_War_Text[17400]["Option5"]
tNpcGossip[17400]["OptionFunc5"]="National_War_AcceptTask</N>17400"
tNpcGossip[17400]["OptionChkFunc5"] = function ()
	local nTask_detail = tNational_War_Cont["task_detail"]
	National_War_CheckDailyReset(nTask_detail)
	return Get_TaskDetailData3(nTask_detail) == 0 and Get_TaskDetailData6(nTask_detail) == 0
end

tNpcGossip[17400]["Option30"]=tNational_War_Text[17400]["Option30"]
tNpcGossip[17400]["OptionFunc30"]="National_War_RewardItem</N>17400"

tNpcGossip[17400]["Option31"]=tNational_War_Text[17400]["Option31"]
tNpcGossip[17400]["OptionFunc31"]="National_War_SpyCompleteByFiveCP</N>17400"

tNpcGossip[17400]["Option32"]=tNational_War_Text[17400]["Option32"]
tNpcGossip[17400]["OptionPoint32"] = "9-5"


----------------
tNpcGossip[17400]["Option33"]=tNational_War_Text[17400]["Option33"]
tNpcGossip[17400]["OptionFunc33"]="National_War_Points_For</N>17400</N>50"

tNpcGossip[17400]["Option34"]=tNational_War_Text[17400]["Option34"]
tNpcGossip[17400]["OptionFunc34"]="National_War_Points_For</N>17400</N>150"

tNpcGossip[17400]["Option35"]=tNational_War_Text[17400]["Option35"]
tNpcGossip[17400]["OptionFunc35"]="National_War_Points_For</N>17400</N>300"

tNpcGossip[17400]["Option40"]=tNational_War_Text[17400]["Option40"]
tNpcGossip[17400]["OptionPoint40"] = "11-1"

tNpcGossip[17400]["Option41"]=tNational_War_Text[17400]["Option41"]
tNpcGossip[17400]["Option42"]=tNational_War_Text[17400]["Option42"]


tNpcGossip[17400]["Option20"] = tNational_War_Text[17400]["Option20"]
tNpcGossip[17400]["Option21"] = tNational_War_Text[17400]["Option21"]
tNpcGossip[17400]["Option22"] = tNational_War_Text[17400]["Option22"]
tNpcGossip[17400]["Option23"] = tNational_War_Text[17400]["Option23"]
tNpcGossip[17400]["Option24"] = tNational_War_Text[17400]["Option24"]
tNpcGossip[17400]["Option25"] = tNational_War_Text[17400]["Option25"]
tNpcGossip[17400]["Option26"] = tNational_War_Text[17400]["Option26"]


tNpcGossip[17401]["Option8"]=tNational_War_Text[17401]["Option8"]
tNpcGossip[17401]["Option9"]=tNational_War_Text[17401]["Option9"]
tNpcGossip[17401]["OptionFunc9"]="National_War_SpyComplete</N>17401"

tNpcGossip[17402]["Option10"]=tNational_War_Text[17402]["Option10"]
tNpcGossip[17402]["Option11"]=tNational_War_Text[17402]["Option11"]
tNpcGossip[17402]["OptionFunc11"]="National_War_SpyComplete</N>17402"

tNpcGossip[17403]["Option12"]=tNational_War_Text[17403]["Option12"]
tNpcGossip[17403]["Option13"]=tNational_War_Text[17403]["Option13"]
tNpcGossip[17403]["OptionFunc13"]="National_War_SpyComplete</N>17403"

tNpcGossip[17404]["Option14"]=tNational_War_Text[17404]["Option14"]
tNpcGossip[17404]["Option15"]=tNational_War_Text[17404]["Option15"]
tNpcGossip[17404]["OptionFunc15"]="National_War_SpyComplete</N>17404"

tNpcGossip[17405]["Option16"]=tNational_War_Text[17405]["Option16"]
tNpcGossip[17405]["Option17"]=tNational_War_Text[17405]["Option17"]
tNpcGossip[17405]["OptionFunc17"]="National_War_SpyComplete</N>17405"


--物品对白配置模块
tItem[727505] = tItem[727505] or {}
tItem[727505]["Text1-1"] = {111,112}
tItem[727505]["Text111"] = tNational_War_Text[727505]["111"]
tItem[727505]["Text112"] = tNational_War_Text[727505]["112"]
tItem[727505]["tOption1-1"] = {10,1,2,3,4}
tItem[727505]["ChkFunc1-1"] = function()
	local nNum = 0
	if not Task_ChkTaskDetail(35011) then
		nNum = 0
	else
		nNum = Get_TaskDetailData6(35011)
	end
	
	tItem[727505]["Text112"] = string.format(tNational_War_Text[727505]["112"],nNum)
	return true
end


tItem[727505]["Text2-1"] = {211,212}
tItem[727505]["Text211"] = tNational_War_Text[727505]["211"]
tItem[727505]["Text212"] = tNational_War_Text[727505]["212"]
tItem[727505]["tOption2-1"] = {5}


tItem[727505]["Text2-2"] = {221,222}
tItem[727505]["Text221"] = tNational_War_Text[727505]["221"]
tItem[727505]["Text222"] = tNational_War_Text[727505]["222"]
tItem[727505]["tOption2-2"] = {6}
tItem[727505]["ChkFunc2-2"] = function()
	local nNum = 0
	if not Task_ChkTaskDetail(tNational_War_Cont["Task_35007"]) then
		nNum = 0
	else
		nNum = Get_TaskDetailData6(tNational_War_Cont["Task_35007"])
	end
	
	tItem[727505]["Text222"] = string.format(tNational_War_Text[727505]["222"],nNum)
	return true
end

tItem[727505]["Text2-3"] = {231,232}
tItem[727505]["Text231"] = tNational_War_Text[727505]["231"]
tItem[727505]["Text232"] = tNational_War_Text[727505]["232"]
tItem[727505]["tOption2-3"] = {7}

tItem[727505]["Text2-4"] = {241,242}
tItem[727505]["Text241"] = tNational_War_Text[727505]["241"]
tItem[727505]["Text242"] = tNational_War_Text[727505]["242"]
tItem[727505]["tOption2-4"] = {8}

tItem[727505]["Option1"] = tNational_War_Text[727505]["Option1"]
tItem[727505]["OptionPoint1"]="2-1"

tItem[727505]["Option2"] = tNational_War_Text[727505]["Option2"]
tItem[727505]["OptionPoint2"]="2-2"

tItem[727505]["Option3"] = tNational_War_Text[727505]["Option3"]
tItem[727505]["OptionPoint3"]="2-3"

tItem[727505]["Option4"] = tNational_War_Text[727505]["Option4"]
tItem[727505]["OptionPoint4"]="2-4"

tItem[727505]["Option5"] = tNational_War_Text[727505]["Option5"]
tItem[727505]["OptionFunc5"]="National_War_FindWay</N>727505</N>1"

tItem[727505]["Option6"] = tNational_War_Text[727505]["Option6"]

tItem[727505]["Option7"] = tNational_War_Text[727505]["Option7"]
tItem[727505]["OptionFunc7"]="National_War_FindWay</N>727505</N>2"

tItem[727505]["Option8"] = tNational_War_Text[727505]["Option8"]
tItem[727505]["OptionFunc8"]="National_War_FindWay</N>727505</N>3"

tItem[727505]["Option10"] = tNational_War_Text[727505]["Option10"]
tItem[727505]["OptionFunc10"]="National_War_FindWay</N>727505</N>4"

---------新添加需求
tNpcGossip[17400]["Text12-1"] = {1211,1212}
tNpcGossip[17400]["Text1211"] = tNational_War_Text[17400]["Text1211"]
tNpcGossip[17400]["Text1212"] = tNational_War_Text[17400]["Text1212"]
tNpcGossip[17400]["tOption12-1"] = {51,52}
tNpcGossip[17400]["ChkFunc12-1"] = function ()
	
	local nNum = 0
	if not Task_ChkTaskDetail(35011) then
		nNum = 0
	else
		nNum = Get_TaskDetailData6(35011)
	end
	
	tNpcGossip[17400]["Text1211"] = string.format(tNational_War_Text[17400]["Text1211"],nNum)
	return true
end

tNpcGossip[17400]["Option51"]=tNational_War_Text[17400]["Option51"]
tNpcGossip[17400]["OptionPoint51"] = "15"

tNpcGossip[17400]["Option52"]=tNational_War_Text[17400]["Option52"]

tNpcGossip[17400]["Text15-1"] = {1511}
tNpcGossip[17400]["Text1511"] = tNational_War_Text[17400]["Text1511"]
tNpcGossip[17400]["tOption15-1"] = {55,56}
tNpcGossip[17400]["ChkFunc15-1"] = function ()
	
	if not Task_ChkTaskDetail(35011) then
		Task_AddTaskDetail(35011)
		nFlag = 1
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Max"] then
		return false
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Mid"] then
		nFlag = 3
	elseif Get_TaskDetailData6(35011) >= tNational_War_JFCont["Min"] then
		nFlag = 2
	else
		nFlag = 1
	end
	
	tNpcGossip[17400]["Text1511"] = string.format(tNational_War_Text[17400]["Text1511"],tNational_War_JFCont[nFlag])
	return true
end

tNpcGossip[17400]["Text15-2"] = {1521}
tNpcGossip[17400]["Text1521"] = tNational_War_Text[17400]["Text1521"]
tNpcGossip[17400]["tOption15-2"] = {53}


tNpcGossip[17400]["Option55"] = tNational_War_Text[17400]["Option55"]
tNpcGossip[17400]["OptionFunc55"]="National_War_CostCp</N>17400"

tNpcGossip[17400]["Option56"] = tNational_War_Text[17400]["Option56"]


tNpcGossip[17400]["Text13-1"] = {1311}
tNpcGossip[17400]["Text1311"] = tNational_War_Text[17400]["Text1311"]
tNpcGossip[17400]["tOption13-1"] = {53}

tNpcGossip[17400]["Option53"] = tNational_War_Text[17400]["Option53"]

tNpcGossip[17400]["Text14-1"] = {1411}
tNpcGossip[17400]["Text1411"] = tNational_War_Text[17400]["Text1411"]
tNpcGossip[17400]["tOption14-1"] = {53}

tNpcGossip[17400]["Option54"] = tNational_War_Text[17400]["Option54"]

---------------------------------------------物品使用模块-------------------------------
tItem[3007108] = tItem[3007108] or {}
tItem[3007108]["Function"] = function(nItemId,sItemName)
	National_War_ItemUse(nItemId)
end

tItem[3007109] = tItem[3007109] or {}
tItem[3007109]["Function"] = function(nItemId,sItemName)
	National_War_ItemUse(nItemId)
end

tItem[3007110] = tItem[3007110] or {}
tItem[3007110]["Function"] = function(nItemId,sItemName)
	National_War_ItemUse(nItemId)
end

--------------------------------------------上线触发

-- 上线触发
table.insert(tSystem_PlayLogin_Func,National_War_OnlAddTask)
