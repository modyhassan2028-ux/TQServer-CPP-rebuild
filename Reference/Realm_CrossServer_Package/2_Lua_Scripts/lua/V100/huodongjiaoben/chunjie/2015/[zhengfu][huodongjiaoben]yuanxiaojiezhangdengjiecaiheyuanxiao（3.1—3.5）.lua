------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]春节活动（元宵）之张灯结彩贺元宵（3.1—3.5）
--Creator: 		陈浩文
--Created:		2014/12/15
------------------------------------------------------------------------------------
-- 命名前缀
-- FestivalSpring2015_Zhangdengjiecai_

--活动时间
local tFestivalSpring2015_Zhangdengjiecai_Cont = {}
tFestivalSpring2015_Zhangdengjiecai_Cont["Beftime"]= "2014-02-11 00:00 2015-02-28 23:59"
tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"] = "2015-03-01 00:00 2015-03-5 23:59"

--玩家等级要求
tFestivalSpring2015_Zhangdengjiecai_Cont["Metempsychosis"] = 0
tFestivalSpring2015_Zhangdengjiecai_Cont["Level"] = 80

--返回双龙城坐标
tFestivalSpring2015_Zhangdengjiecai_Cont["MapId1"] = 1002
tFestivalSpring2015_Zhangdengjiecai_Cont["CellX1"] = 275
tFestivalSpring2015_Zhangdengjiecai_Cont["CellY1"] = 380
tFestivalSpring2015_Zhangdengjiecai_Cont["BoundCX1"] = 5
tFestivalSpring2015_Zhangdengjiecai_Cont["BoundCY1"] = 5

--寻路NPC 灯笼
tFestivalSpring2015_Zhangdengjiecai_Npc = {}
tFestivalSpring2015_Zhangdengjiecai_Npc["NpcId"] = 10754
tFestivalSpring2015_Zhangdengjiecai_Npc["MapId"] = 1002
tFestivalSpring2015_Zhangdengjiecai_Npc["CellX"] = 276
tFestivalSpring2015_Zhangdengjiecai_Npc["CellY"] = 372

-- log表
local tFestivalSpring2015_Zhangdengjiecai_Log = {}
tFestivalSpring2015_Zhangdengjiecai_Log["New"] = "0,0,0,0,10000463,1[1],0,0"
tFestivalSpring2015_Zhangdengjiecai_Log["Complete"] = "0,0,0,0,10000463,1[2],0,0"
tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddExpTime"] = "0,0,0,0,10000463,2,4,60"		   --60分钟经验
tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddBless"] = "0,0,0,0,10000463,2,5,24"			 --获得1天祝福
tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddCultivation"] = "0,0,0,0,10000463,2,6,30"	   --30修行值
tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddStrengthValue"] = "0,0,0,0,10000463,2,12,20"	--20气力值


--奖励掩码 1表示接任务 2表示领取奖励
local tFestivalSpring2015_Zhangdengjiecai_stc = {}
tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"] = 131
tFestivalSpring2015_Zhangdengjiecai_stc["StcType"] = 99
tFestivalSpring2015_Zhangdengjiecai_stc["New"] = 1
tFestivalSpring2015_Zhangdengjiecai_stc["Complete"] = 2

------------------------------------------------------------------------------------
--活动数据
local tFestivalSpring2015_Zhangdengjiecai_Data = {}
	--60分钟经验		25%（满级给修行值）
	tFestivalSpring2015_Zhangdengjiecai_Data["AddExp"] = 60
	--1天祝福			25%
	tFestivalSpring2015_Zhangdengjiecai_Data["AddBlessTime"] = 24
	--30修行值		 25%
	tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivation"] = 30
	--20气力值		 25%（没2转给经验）
	tFestivalSpring2015_Zhangdengjiecai_Data["AddStrengthValue"] = 20
	--60分钟经验对应的随机数
	tFestivalSpring2015_Zhangdengjiecai_Data["AddExpNum"] = 1
	--1天祝福对应的随机数
	tFestivalSpring2015_Zhangdengjiecai_Data["AddBlessTimeNum"] = 2
	--30修行值对应的随机数
	tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivationNum"] = 3
	--20气力值对应的随机数
	tFestivalSpring2015_Zhangdengjiecai_Data["AddStrengthValueNum"] = 4
	--满级给修行值
	tFestivalSpring2015_Zhangdengjiecai_Data["LevelCondition"] = 140
	--没2转给经验值
	tFestivalSpring2015_Zhangdengjiecai_Data["MetempsychosisCondition"] = 2
	--节日欢庆礼包
	tFestivalSpring2015_Zhangdengjiecai_Data["FestivalId"] = 3370		--节日欢庆礼包
	tFestivalSpring2015_Zhangdengjiecai_Data["LogId"] = 10000463
	--领取祝福光效
	tFestivalSpring2015_Zhangdengjiecai_Data["Effect"] = {}
	tFestivalSpring2015_Zhangdengjiecai_Data["Effect"][1] = "hunpo02"									   --自己
	tFestivalSpring2015_Zhangdengjiecai_Data["Effect"][2] = "zf2-e300"									  --周围的灯
	--文字烟花（元宵快乐）
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectObj"]={}
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectObj"][1] = "self"
	
	--所有点亮的灯笼坐标
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"]={} 
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][1] = 276
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][2] = 279
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][3] = 285
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][4] = 279
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][5] = 285
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"]={} 
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][1] = 372
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][2] = 378
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][3] = 378
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][4] = 368
	tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][5] = 368
	
------------------------------------------------------------------------------------
------------------------------------------
--自动寻路逻辑 点确定寻路到祝福灯笼旁边
function FestivalSpring2015_Zhangdengjiecai_Goto()
	local nEvent = tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"]
	local nType = tFestivalSpring2015_Zhangdengjiecai_stc["StcType"]
	
	--是否隔1天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--判断是否领奖
	if Task_ChkStcValue(nEvent,nType,"<",tFestivalSpring2015_Zhangdengjiecai_stc["Complete"]) then
		Sys_SaveActionFestivalLog(tFestivalSpring2015_Zhangdengjiecai_Log["New"])
		Task_SetStatistic(nEvent,nType,tFestivalSpring2015_Zhangdengjiecai_stc["New"],1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	Sys_GotoSomeWhere(tFestivalSpring2015_Zhangdengjiecai_Npc["CellX"],tFestivalSpring2015_Zhangdengjiecai_Npc["CellY"],tFestivalSpring2015_Zhangdengjiecai_Npc["MapId"],tFestivalSpring2015_Zhangdengjiecai_Npc["NpcId"])
	
end
------------------------------------------
--等级判断
function FestivalSpring2015_Zhangdengjiecai_level()
	local bPlayerLev = not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_Zhangdengjiecai_Cont["Level"],tFestivalSpring2015_Zhangdengjiecai_Cont["Metempsychosis"])
	return bPlayerLev
end

------------------------------------------
--判断是否接任务
function FestivalSpring2015_Zhangdengjiecai_accept()
	local nEvent = tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"]
	local nType = tFestivalSpring2015_Zhangdengjiecai_stc["StcType"]
	
	--是否隔1天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--判断是否接受
	if Task_ChkStcValue(nEvent,nType,"==",tFestivalSpring2015_Zhangdengjiecai_stc["New"]) or Task_ChkStcValue(nEvent,nType,"==",tFestivalSpring2015_Zhangdengjiecai_stc["Complete"]) then
		return true
	end
	return false
end

------------------------------------------
-- 单用STC掩码逻辑
function FestivalSpring2015_Zhangdengjiecai_ChkStc()
	local nEvent = tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"]
	local nType = tFestivalSpring2015_Zhangdengjiecai_stc["StcType"]
	--判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return false
	end
	
	--判断是否领奖
	if Task_ChkStcValue(nEvent,nType,"<",tFestivalSpring2015_Zhangdengjiecai_stc["Complete"]) then
		return false
	end
	return true
end

------------------------------------------

-- 获得奖励逻辑
function FestivalSpring2015_Zhangdengjiecai_GetAward(nNpcId,nPlaceNum)
	local nEvent = tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"]
	local nType = tFestivalSpring2015_Zhangdengjiecai_stc["StcType"]
	local nFestivalLog = nil
	local sMsgBox = ""
	
	Task_SetStatistic(nEvent,nType,tFestivalSpring2015_Zhangdengjiecai_stc["Complete"],1)
	Task_SetStcTimestamp(nEvent,nType,0)
	Sys_SaveActionFestivalLog(tFestivalSpring2015_Zhangdengjiecai_Log["Complete"])
	
	--60分钟经验
	if nPlaceNum == tFestivalSpring2015_Zhangdengjiecai_Data["AddExpNum"] then
		local nUserLev = Get_UserLevel()
		if nUserLev>=tFestivalSpring2015_Zhangdengjiecai_Data["LevelCondition"] then
			--满级给修行值
			User_AddCultivation(tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivation"])
			nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddCultivation"]
			sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text251"] 
		else
			--60分钟经验
			User_AddExpTime(tFestivalSpring2015_Zhangdengjiecai_Data["AddExp"])
			nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddExpTime"]
			sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text231"] 
		end
	--1天祝福
	elseif nPlaceNum == tFestivalSpring2015_Zhangdengjiecai_Data["AddBlessTimeNum"] then
		User_AddBless(tFestivalSpring2015_Zhangdengjiecai_Data["AddBlessTime"])
		nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddBless"]
		sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text241"] 
	--30修行值
	elseif nPlaceNum == tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivationNum"] then
		User_AddCultivation(tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivation"])
		nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddCultivation"]
		sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text251"] 

	--20气力值
	elseif nPlaceNum == tFestivalSpring2015_Zhangdengjiecai_Data["AddStrengthValueNum"] then
		local nMetempsychosis = Get_UserMetempsychosis()
		if nMetempsychosis < tFestivalSpring2015_Zhangdengjiecai_Data["MetempsychosisCondition"] then
			--没2转给经验值
			local nUserLev = Get_UserLevel()
			if nUserLev>=tFestivalSpring2015_Zhangdengjiecai_Data["LevelCondition"] then
				--满级给修行值
				User_AddCultivation(tFestivalSpring2015_Zhangdengjiecai_Data["AddCultivation"])
				nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddCultivation"]
				sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text251"] 
			else
				--60分钟经验
				User_AddExpTime(tFestivalSpring2015_Zhangdengjiecai_Data["AddExp"])
				nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddExpTime"]
				sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text231"]
			end
		else
			--20气力值
			User_AddStrengthValue(tFestivalSpring2015_Zhangdengjiecai_Data["AddStrengthValue"])
			nFestivalLog = tFestivalSpring2015_Zhangdengjiecai_Log["CompleteGet_AddStrengthValue"]
			sMsgBox = tFestivalSpring2015_Zhangdengjiecai_Text[nNpcId]["Text261"] 
		end
	end
	Sys_SaveActionFestivalLog(nFestivalLog)
	Sys_MsgBox(sMsgBox)
	return true
end

------------------------------------------

--成功领取
function FestivalSpring2015_Zhangdengjiecai_GetAwardSuccess(nNpcId)
	local nEvent = tFestivalSpring2015_Zhangdengjiecai_stc["StcEvent"]
	local nType = tFestivalSpring2015_Zhangdengjiecai_stc["StcType"]
	local nFestivalId = tFestivalSpring2015_Zhangdengjiecai_Data["FestivalId"]
	local nLogId = tFestivalSpring2015_Zhangdengjiecai_Data["LogId"]
	--是否隔1天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--判断是否领奖
	if Task_ChkStcValue(nEvent,nType,"==",tFestivalSpring2015_Zhangdengjiecai_stc["New"]) then
		--随机一种奖励
		FestivalSpring2015_Zhangdengjiecai_GetAward(nNpcId,math.random(tFestivalSpring2015_Zhangdengjiecai_Data["AddExpNum"],tFestivalSpring2015_Zhangdengjiecai_Data["AddStrengthValueNum"]))
		--节日欢庆礼包
		FestivalGeneralPackage_GetGift(nFestivalId,nLogId)
		--特效
		User_EffectAdd(tFestivalSpring2015_Zhangdengjiecai_Data["EffectObj"][1],tFestivalSpring2015_Zhangdengjiecai_Data["Effect"][1])
		Map_FireWorks2(tFestivalSpring2015_Zhangdengjiecai_Effect["Effect"])
		for i=1,#tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"] do
			local nMapId = tFestivalSpring2015_Zhangdengjiecai_Npc["MapId"]
			local nEffectCellX = tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellX"][i]
			local nEffectCellY=tFestivalSpring2015_Zhangdengjiecai_Data["EffectCellY"][i]
			local nEffect=tFestivalSpring2015_Zhangdengjiecai_Data["Effect"][2]
			Map_Effect(nMapId, nEffectCellX, nEffectCellY, nEffect)  
		end

	end
end
------------------------------------------
--对白链接
function FestivalSpring2015_Zhangdengjiecai_Option12_10753(nNpcId)
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_Zhangdengjiecai_Cont["Level"],tFestivalSpring2015_Zhangdengjiecai_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end 
	--今日已完成
	if FestivalSpring2015_Zhangdengjiecai_ChkStc() then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	FestivalSpring2015_Zhangdengjiecai_Goto()
end

---------------------------------------------------对话模板部分-----------------------------------------
-- //彩莲姑娘
tNpcFace[3576] = 116
tNpcGossip[10753] = tNpcGossip[10753] or DefaultNpc:new{}
tNpcGossip[10753]["OptionHidden"] = 1

--【第一层】--对白

tNpcGossip[10753]["Text1-1"] = {111,112,113}		-- 活动前
tNpcGossip[10753]["Text1-2"] = {121,122,123,124}	-- 活动中
tNpcGossip[10753]["Text1-3"] = {131,132}			-- 活动后
tNpcGossip[10753]["Text2-1"] = {211}			-- 等级不足
tNpcGossip[10753]["Text2-2"] = {221}			-- 今日已完成

-- 活动前
tNpcGossip[10753]["Text111"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text111"]
tNpcGossip[10753]["Text112"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text112"]
tNpcGossip[10753]["Text113"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text113"]
tNpcGossip[10753]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Beftime"])
end

-- 活动中
tNpcGossip[10753]["Text121"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text121"] 
tNpcGossip[10753]["Text122"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text122"]
tNpcGossip[10753]["Text123"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text123"]
tNpcGossip[10753]["Text124"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text124"]
tNpcGossip[10753]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"])
end

-- 活动后
tNpcGossip[10753]["Text131"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text131"] 
tNpcGossip[10753]["Text132"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text132"]
tNpcGossip[10753]["ChkFunc1-3"] = function ()
	return not Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"])
end

-- 等级不足
tNpcGossip[10753]["Text211"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text211"] 
-- 今日已完成
tNpcGossip[10753]["Text221"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text221"] 
--选项
tNpcGossip[10753]["tOption1-1"] = {11}
tNpcGossip[10753]["tOption1-2"] = {12,13}
tNpcGossip[10753]["tOption1-3"] = {14}
tNpcGossip[10753]["tOption2-1"] = {21}
tNpcGossip[10753]["tOption2-2"] = {22}
tNpcGossip[10753]["Option11"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option11"]
tNpcGossip[10753]["Option12"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option12"]
tNpcGossip[10753]["Option13"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option13"]
tNpcGossip[10753]["Option14"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option14"]
tNpcGossip[10753]["Option21"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option21"]
tNpcGossip[10753]["Option22"] = tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option22"]
tNpcGossip[10753]["OptionFunc12"]="FestivalSpring2015_Zhangdengjiecai_Option12_10753</N>10753"

----------------------------------------------------------------------------------------------
-- //祝福灯笼
tNpcGossip[10754] = tNpcGossip[10754] or DefaultNpc:new{}
tNpcGossip[10755] = tNpcGossip[10754] 
tNpcGossip[10756] = tNpcGossip[10754] 
tNpcGossip[10757] = tNpcGossip[10754] 
tNpcGossip[10758] = tNpcGossip[10754] 
tNpcGossip[10754]["OptionHidden"] = 1

--【第一层】--对白

tNpcGossip[10754]["Text1-1"] = {111}			-- 未接受任务
tNpcGossip[10754]["Text1-2"] = {121}			-- 接受任务
tNpcGossip[10754]["Text1-3"] = {131}			-- 已完成点灯对白

-- 未接受任务
tNpcGossip[10754]["Text111"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text111"]
tNpcGossip[10754]["ChkFunc1-1"] = function ()
	return (not Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"])) or (not FestivalSpring2015_Zhangdengjiecai_accept() )
end

-- 接受任务
tNpcGossip[10754]["Text121"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text121"] 
tNpcGossip[10754]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"]) and (FestivalSpring2015_Zhangdengjiecai_accept()) and not FestivalSpring2015_Zhangdengjiecai_ChkStc()
end

-- 已完成点灯对白 
tNpcGossip[10754]["Text131"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text131"] 
tNpcGossip[10754]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_Zhangdengjiecai_Cont["Nowtime"]) and (FestivalSpring2015_Zhangdengjiecai_accept()) and FestivalSpring2015_Zhangdengjiecai_ChkStc()
end

--选项
tNpcGossip[10754]["tOption1-1"] = {11}
tNpcGossip[10754]["tOption1-2"] = {12,13}
tNpcGossip[10754]["tOption1-3"] = {14}
tNpcGossip[10754]["tOption2-1"] = {21}
tNpcGossip[10754]["tOption2-2"] = {22}
tNpcGossip[10754]["Option11"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option11"]
tNpcGossip[10754]["Option12"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option12"]
tNpcGossip[10754]["Option13"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option13"]
tNpcGossip[10754]["Option14"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option14"]
tNpcGossip[10754]["Option21"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option21"]
tNpcGossip[10754]["Option22"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option22"]
tNpcGossip[10754]["OptionPoint12"] = "2"

--【点灯】
tNpcGossip[10754]["Text2-1"] = {211} 			--等级不足
tNpcGossip[10754]["Text2-2"] = {221} 			--背包空间不足
tNpcGossip[10754]["Text2-3"] = {231} 			--成功领取

--等级不足
tNpcGossip[10754]["Text211"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text211"] 
tNpcGossip[10754]["ChkFunc2-1"] = function ()
	return FestivalSpring2015_Zhangdengjiecai_level()
end

--背包空间不足
tNpcGossip[10754]["Text221"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text221"] 
tNpcGossip[10754]["ChkFunc2-2"] = function ()
	return not User_CheckLeftSpace(1)
end

--成功领取
tNpcGossip[10754]["Text231"] = tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text231"] 
tNpcGossip[10754]["ChkFunc2-3"] = function ()
	FestivalSpring2015_Zhangdengjiecai_GetAwardSuccess(10754)
	return false
end

