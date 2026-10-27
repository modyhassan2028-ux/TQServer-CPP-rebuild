------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]跨服春节任务（2.15~3.5）--跨服拜乐
--Purpose:		
--Creator: 		张磊
--Created:		01/08/2015
------------------------------------------------------------------------------------


--[[
任务需求：
【简体征服】跨服春节任务（2.15-3.5）

根据设计师活动案制作跨服春节任务。

==跨服抢红包  张磊制作

]]--


------------------------------------------------------------------------------------
--[[掩码说明
掩码说明：35001
data1 : ==1 表示已经跨服过去获得赐福了

]]--

--LOGid 12000009
------------------------------------------------------------------------------------
--命名规范
--CrossFestivalTask_GrabEnvelope_
------------------------------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------常量表配置-------------------------------------------
local tCrossFestivalTask_GrabEnvelope_Cont = {}
	--活动时间、
	tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"] = "2015-02-19 00:00 2015-02-25 23:59"
	tCrossFestivalTask_GrabEnvelope_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-02-18 23:59"

	--玩家等级以及转世要求
	tCrossFestivalTask_GrabEnvelope_Cont["Metempsychosis"] = 2
	tCrossFestivalTask_GrabEnvelope_Cont["Level"] = 70
	
	--任务掩码
	tCrossFestivalTask_GrabEnvelope_Cont["TaskId"] = 35001
	tCrossFestivalTask_GrabEnvelope_Cont["nData1"] = 1
	
	tCrossFestivalTask_GrabEnvelope_Cont["TaskId_DL"] = 35002
	
	tCrossFestivalTask_GrabEnvelope_Cont["MapId"] = 3898
	tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000"] = 5000
	tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000_X"] = 50
	tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000_Y"] = 50
	
	--读条参数设置
	 tCrossFestivalTask_GrabEnvelope_Cont["Secs"] = 1
	-- tCrossFestivalTask_GrabEnvelope_Cont["Content"] = "烧毁战旗"
	 tCrossFestivalTask_GrabEnvelope_Cont["ActionId"] = 100
	
	--点灯笼读条设置
	tCrossFestivalTask_GrabEnvelope_Cont["Secs_Lantern"] = 1
	tCrossFestivalTask_GrabEnvelope_Cont["Content_Lantern"] = "烧毁灯笼"
	tCrossFestivalTask_GrabEnvelope_Cont["ActionId_Lantern"] = 100
	
	tCrossFestivalTask_GrabEnvelope_Cont["Content_LightBox"] = "烧毁宝箱"

	--光效参数设置
	tCrossFestivalTask_GrabEnvelope_Cont["SzObj"] = "self"
	--获得红包光效
	-- tCrossFestivalTask_GrabEnvelope_Cont["GetEffect"] = "fire-bomb"
	--领取奖励光效
	tCrossFestivalTask_GrabEnvelope_Cont["HandinEffect"] = "zf2-e300"
	--点灯笼光效
	tCrossFestivalTask_GrabEnvelope_Cont["ClickLanternEffect"] = "upnumeber5"
	--点击完灯笼的地面光效
	tCrossFestivalTask_GrabEnvelope_Cont["ClickCombustionEffect"] = "FF13"
	
	tCrossFestivalTask_GrabEnvelope_Cont["LightBox"] = "firemagic"
		
	
	--背包空间参数设置
	tCrossFestivalTask_GrabEnvelope_Cont["Space"] = 3
	
	--FestivalId
	tCrossFestivalTask_GrabEnvelope_Cont["FestivalId"] = 3376
	

	
local tCrossFestivalTask_GrabEnvelope_Log = {}
	--活动LOGid
	tCrossFestivalTask_GrabEnvelope_Log["FestivalLogId"] = 12000009
	tCrossFestivalTask_GrabEnvelope_Log["AcceptLog"] = "0,0,0,0,12000009,1[1],0,0"
	tCrossFestivalTask_GrabEnvelope_Log["ProcessLog"] = "0,0,0,0,12000009,1[2],0,0"
	tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"] = "0,0,0,0,12000009,2,%s,%s"

	
	
local tCrossFestivalTask_GrabEnvelope_Reward = {}
	--奖励   3002029	护心丹
	tCrossFestivalTask_GrabEnvelope_Reward["Item"] = 3002029
	tCrossFestivalTask_GrabEnvelope_Reward["Qi_Max"] = 5
	tCrossFestivalTask_GrabEnvelope_Reward["Qi"] = 1
	
	tCrossFestivalTask_GrabEnvelope_Reward["Practice_Max"] = 1000000
	tCrossFestivalTask_GrabEnvelope_Reward["Practice"] = 10000
	
	tCrossFestivalTask_GrabEnvelope_Reward["Item_Time"] = 2880

	
local tCrossFestivalTask_GrabEnvelope_Npc = {}

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_Id"] = 18263
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_X"] = 256
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_Y"] = 276
	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_Id"] = 18264
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_X"] = 257
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_Y"] = 338

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"] = {}	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_Id"] = 18265
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_X"] = 299
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_Y"] = 368

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"] = {}	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_Id"] = 18266
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_X"] = 367
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_Y"] = 342

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"] = {}	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_Id"] = 18267
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_X"] = 314
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_Y"] = 249	

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_Id"] = 18268
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_X"] = 182
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_Y"] = 169	
	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_Id"] = 18269
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_X"] = 160
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_Y"] = 193

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_Id"] = 18270
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_X"] = 178
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_Y"] = 345

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_Id"] = 18271
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_X"] = 172
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_Y"] = 310
	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_Id"] = 18272
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_X"] = 354
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_Y"] = 491
	
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_Id"] = 18273
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_X"] = 388
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_Y"] = 493

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_Id"] = 18274
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_X"] = 483
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_Y"] = 397

	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"] = {}
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_Id"] = 18275
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_X"] = 487
	tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_Y"] = 357
	
--新添加播放光效位置表

local tCrossFestivalTask_GrabEnvelope_Position = {}

	--宝箱
	tCrossFestivalTask_GrabEnvelope_Position["nMapId_Box"] = 1002
	tCrossFestivalTask_GrabEnvelope_Position["nNpcX_Box"] = 310
	tCrossFestivalTask_GrabEnvelope_Position["nNpcY_Box"] = 277	
	
------------------------------------------NPC对话-------------------------------------------





------------------------------------------逻辑部分----------------------------------------------

--接受任务弹出的条件
function CrossFestivalTask_GrabEnvelope_ShowCondit()
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		return false
	end
	
	if User_IsCross() then
		return false
	end
	
	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]
	if not Task_ChkTaskDetail(nTaskId) then
		return true
	end
	return false
end



--接取任务的时候
function CrossFestivalTask_GrabEnvelope_AcceptCondit(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		--活动时间后的对白
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nLevel = tCrossFestivalTask_GrabEnvelope_Cont["Level"]
	local nMetempsychosis = tCrossFestivalTask_GrabEnvelope_Cont["Metempsychosis"]
	--判断玩家等级情况
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		--等级不足提示
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]
	if Task_ChkTaskDetail(nTaskId) then
	
		--判断是否领取奖励了
		local nData6 = Get_TaskDetailData6(nTaskId)
	
		if nData6 >= 1 then
		--已经领取奖励提示
			LinkNpcGossipFunc_New(nNpcId,"12-1")
			return
		end
	
		local nData1 = Get_TaskDetailData1(nTaskId)
		local nAccpectData1 = tCrossFestivalTask_GrabEnvelope_Cont["nData1"]
	
		if nData1 == nAccpectData1 and nData1 ~= 0 then
			Sys_MsgBox(tCrossFestivalTask_GrabEnvelope_Text["SecStemp"])
			return
		end
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--没接过任务
	--给玩家接受任务
	Task_AddTaskDetail(nTaskId)
	
	--记录第一步LOG
	Sys_SaveActionFestivalLog(tCrossFestivalTask_GrabEnvelope_Log["AcceptLog"])
	LinkNpcGossipFunc_New(nNpcId,"2-1")
end

--获得赐福选项弹出的条件
function CrossFestivalTask_GrabEnvelope_TakeCondit()
	--活动时间
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		return false
	end
	
	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]

	--掩码值是否==0
	local nData6 = Get_TaskDetailData6(nTaskId)
	local nData1 = Get_TaskDetailData1(nTaskId)
	
	if Task_ChkTaskDetail(nTaskId) and nData6 == 0 and nData1 == 0 then
		return true
	end
	return false
end


--获得赐福（只有跨服玩家才能看到）
function CrossFestivalTask_GrabEnvelope_TakeRedEnvelope(nNpcId)
	--判断时间
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		--活动时间后的对白
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--判断玩家是否为跨服玩家
	if not User_IsCross() then
		--提示玩家只有跨服的玩家才能获得赐福
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	--判断玩家当前任务状态

	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]	
	if not Task_ChkTaskDetail(nTaskId) then
		LinkNpcGossipFunc_New(nNpcId,"7-1")
		
		return
	end
	
	local nData1 = Get_TaskDetailData1(nTaskId)	
	local nCompleteFlag = tCrossFestivalTask_GrabEnvelope_Cont["nData1"]
	
	if nData1 >= nCompleteFlag then
		Sys_MsgBox(tCrossFestivalTask_GrabEnvelope_Text["RepeatBlessing"])
		
		return
	end
	
	--读条领取红包（表现只是一个光效而已，并不是真实的物品）
	local nSecs = tCrossFestivalTask_GrabEnvelope_Cont["Secs"]
	local sContent = tCrossFestivalTask_GrabEnvelope_Cont["Content_LightBox"]
	local nActionId = tCrossFestivalTask_GrabEnvelope_Cont["ActionId"]
	
	User_SetExplore(nSecs,sContent,nActionId,"CrossFestivalTask_GrabEnvelope_ReadArticle</N>" .. nNpcId)
end

--读条后的函数
function CrossFestivalTask_GrabEnvelope_ReadArticle(nNpcId,nUserId)
	--判断时间
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		--活动时间后的对白
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--打掩码，给光效
	local nData1 = 	tCrossFestivalTask_GrabEnvelope_Cont["nData1"]
	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]
		
	Task_SetTaskDetailData1(nTaskId,nData1,nUserId)
	
	--local nSzObj = 	tCrossFestivalTask_GrabEnvelope_Cont["SzObj"]
	local sEffect = tCrossFestivalTask_GrabEnvelope_Cont["LightBox"]
	
	--在旗子或者宝箱处播放一个燃烧的光效
	local nMapId = tCrossFestivalTask_GrabEnvelope_Position["nMapId_Box"]
	local nPosX = tCrossFestivalTask_GrabEnvelope_Position["nNpcX_Box"]
	local nPosY = tCrossFestivalTask_GrabEnvelope_Position["nNpcY_Box"]
	local nNum = math.random(1,3)
	local sStr = nil
	local sUserName = Get_UserName(nUserId)

	
	if nNpcId == nil or nNpcId == 0 then
		return
	end
	
	if nNum == 1 then
			sStr = string.format(tCrossFestivalTask_GrabEnvelope_Text["MsgBox_2007_1"],sUserName)
		elseif nNum == 2 then
			sStr = tCrossFestivalTask_GrabEnvelope_Text["MsgBox_2007_2"]
		else
			sStr = string.format(tCrossFestivalTask_GrabEnvelope_Text["MsgBox_2007_3"],sUserName)
	end
	
	Map_Effect(nMapId,nPosX,nPosY,sEffect)
	
	--记录第二步LOG
	Sys_SaveActionFestivalLog(tCrossFestivalTask_GrabEnvelope_Log["ProcessLog"],nUserId)
	Sys_MsgBox(tCrossFestivalTask_GrabEnvelope_Text[17980]["CrossResiveEnvelope"])
	Sys_TalkBroadcast(sStr)
end


--领奖励选项
function CrossFestivalTask_GrabEnvelope_HandRedEnvelope(nNpcId)
	--判断时间
	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		--活动时间后的对白
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--是否为本服玩家
	if User_IsCross() then
		--提示玩家只有本服玩家才能领取奖励
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	

	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId"]
	if not Task_ChkTaskDetail(nTaskId) then
		Sys_MsgBox(tCrossFestivalTask_GrabEnvelope_Text["MsgAccept"])
		
		return
	end
	
	local nCompleteFlag = tCrossFestivalTask_GrabEnvelope_Cont["nData1"]
	local nData1 = Get_TaskDetailData1(nTaskId)
	local nData6 = Get_TaskDetailData6(nTaskId)
	
	if nData6 >= 1 then
		LinkNpcGossipFunc_New(nNpcId,"11-1")
		return
	end
	
	
	--判断玩家任务状态
	if nData1 < nCompleteFlag then
		LinkNpcGossipFunc_New(nNpcId,"13-1")
		
		return
	end
	

	--先直接给节日礼包（程序帮派基金的接口没有）
	--判断背包空间
	local nSpace = tCrossFestivalTask_GrabEnvelope_Cont["Space"]
	
	if not User_CheckLeftSpace(nSpace) then
		LinkNpcGossipFunc_New(nNpcId,"14-1")
		return
	end
	
	local nSzObj = 	tCrossFestivalTask_GrabEnvelope_Cont["SzObj"]
	local sEffect = tCrossFestivalTask_GrabEnvelope_Cont["HandinEffect"]
	
	local sEffectBless = tCrossFestivalTask_GrabEnvelope_Cont["GetEffect"]

	
	Task_SetTaskDetailData1(nTaskId,0)
	Task_SetTaskDetailData6(nTaskId,1)
	
	for i = 1,2 do
		FestivalGeneralPackage_GetGift(tCrossFestivalTask_GrabEnvelope_Cont["FestivalId"],tCrossFestivalTask_GrabEnvelope_Log["FestivalLogId"])
	end
	
	Item_AddItem(tCrossFestivalTask_GrabEnvelope_Reward["Item"],0,1,0,tCrossFestivalTask_GrabEnvelope_Reward["Item_Time"],1)
	
--nItemId,flag,addamount,monopoly,save_time,active
	
	local str = nil
	
	if User_IsAlreadyCreateGongFu(0) then
		local nUserQi = Get_UserGongFuInt(3003,0)
		local nUserPractice = Get_UserGongFuInt(3002,0)
		
		local nRewQ1 = tCrossFestivalTask_GrabEnvelope_Reward["Qi"]
		local nRewPractice = tCrossFestivalTask_GrabEnvelope_Reward["Practice"]
		
		local nMaxQ1 = tCrossFestivalTask_GrabEnvelope_Reward["Qi_Max"]
		local nMaxPractice = tCrossFestivalTask_GrabEnvelope_Reward["Practice_Max"]
		
		if nUserQi < nMaxQ1 then
			User_AddGongFuInt(3003,nRewQ1,0)
			if nUserPractice <= (nMaxPractice - nRewPractice) then
				User_AddGongFuInt(3002,nRewPractice,0)
				str = string.format(tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"],"3003625[3002029][16][17]","2[1][1][10000]")
				LinkNpcGossipFunc_New(nNpcId,"15-1")
			end
			str = string.format(tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"],"3003625[3002029][16]","2[1][1]")
			LinkNpcGossipFunc_New(nNpcId,"18-1")
			
		elseif nUserPractice <= (nMaxPractice - nRewPractice) then
				User_AddGongFuInt(3002,nRewPractice,0)
				str = string.format(tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"],"3003625[3002029][16][17]","2[1][1][10000]")
				LinkNpcGossipFunc_New(nNpcId,"16-1")
		else
		str = string.format(tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"],"3003625[3002029]","2[1]")
		LinkNpcGossipFunc_New(nNpcId,"17-1")
		end
	else
		LinkNpcGossipFunc_New(nNpcId,"17-1")
	end
	
	str = string.format(tCrossFestivalTask_GrabEnvelope_Log["CompleteLog"],"3003625[3002029]","2[1]")
		
	Sys_SaveActionFestivalLog(str)
	-- LinkNpcGossipFunc_New(nNpcId,"15-1")
	-- Sys_MsgBox(tCrossFestivalTask_GrabEnvelope_Text["NoSynCompleteTask"])
	--User_EffectDel(nSzObj,sEffectBless)
	User_EffectAdd(nSzObj,sEffect)

end



function CrossFestivalTask_GrabEnvelope_ClickLanterns(nNpcId)

	if not Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"]) then
		return
	end


	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId_DL"]
	
	if not Task_ChkTaskDetail(nTaskId) then
		return
	end
	
	local nData6 = Get_TaskDetailData6(nTaskId)
	
	if nData6 >= 3 then
		return
	end
	
	local nSecs = tCrossFestivalTask_GrabEnvelope_Cont["Secs_Lantern"]
	local sContent = tCrossFestivalTask_GrabEnvelope_Cont["Content_Lantern"]
	local nActionId = tCrossFestivalTask_GrabEnvelope_Cont["ActionId_Lantern"]
	
	User_SetExplore(nSecs,sContent,nActionId,"CrossFestivalTask_GrabEnvelope_ReadArticleLantern</N>" .. nNpcId)

end

function CrossFestivalTask_GrabEnvelope_ReadArticleLantern(nNpcId,nUserId)

	local nTaskId = tCrossFestivalTask_GrabEnvelope_Cont["TaskId_DL"]

	if not Task_ChkTaskDetail(nTaskId,nUserId) then
		return
	end

	local nData6 = Get_TaskDetailData6(nTaskId,nUserId)
	
	if nData6 >= 3 then
		return
	end	
	
	local nData4 = Get_TaskDetailData4(nTaskId,nUserId) + 5
	
	Task_SetTaskDetailData4(nTaskId,nData4,nUserId)
	
	local nMapId = tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000"]
	local nPosX_5000 = tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000_X"]
	local nPosY_5000 = tCrossFestivalTask_GrabEnvelope_Cont["MapId_5000_Y"]
	
	Npc_MoveNpcPos(nNpcId,nMapId,nPosX_5000,nPosY_5000)
	
	--光效
	User_EffectAdd(tCrossFestivalTask_GrabEnvelope_Cont["SzObj"],tCrossFestivalTask_GrabEnvelope_Cont["ClickLanternEffect"],nUserId)
	--光效
	User_EffectAdd(tCrossFestivalTask_GrabEnvelope_Cont["SzObj"],tCrossFestivalTask_GrabEnvelope_Cont["ClickCombustionEffect"],nUserId)

	User_TalkChannel2005(tCrossFestivalTask_GrabEnvelope_Text["ClickLantern"],nUserId)
end


function CrossFestivalTask_GrabEnvelope_MoveNpc()

	local nMapId = 	tCrossFestivalTask_GrabEnvelope_Cont["MapId"]
	
	local nNpcId_18263 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_Id"]
	local nNpcX_18263 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_X"]
	local nNpcY_18263 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18263"]["Npc_Y"]

	local nNpcId_18264 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_Id"]
	local nNpcX_18264 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_X"]
	local nNpcY_18264 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18264"]["Npc_Y"]

	local nNpcId_18265 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_Id"]
	local nNpcX_18265 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_X"]
	local nNpcY_18265 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18265"]["Npc_Y"]

	local nNpcId_18266 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_Id"]
	local nNpcX_18266 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_X"]
	local nNpcY_18266 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18266"]["Npc_Y"]

	local nNpcId_18267 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_Id"]
	local nNpcX_18267 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_X"]
	local nNpcY_18267 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18267"]["Npc_Y"]

	local nNpcId_18268 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_Id"]
	local nNpcX_18268 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_X"]
	local nNpcY_18268 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18268"]["Npc_Y"]

	local nNpcId_18269 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_Id"]
	local nNpcX_18269 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_X"]
	local nNpcY_18269 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18269"]["Npc_Y"]

	local nNpcId_18270 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_Id"]
	local nNpcX_18270 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_X"]
	local nNpcY_18270 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18270"]["Npc_Y"]

	local nNpcId_18271 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_Id"]
	local nNpcX_18271 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_X"]
	local nNpcY_18271 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18271"]["Npc_Y"]

	local nNpcId_18272 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_Id"]
	local nNpcX_18272 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_X"]
	local nNpcY_18272 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18272"]["Npc_Y"]

	local nNpcId_18273 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_Id"]
	local nNpcX_18273 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_X"]
	local nNpcY_18273 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18273"]["Npc_Y"]

	local nNpcId_18274 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_Id"]
	local nNpcX_18274 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_X"]
	local nNpcY_18274 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18274"]["Npc_Y"]

	local nNpcId_18275 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_Id"]
	local nNpcX_18275 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_X"]
	local nNpcY_18275 = tCrossFestivalTask_GrabEnvelope_Npc["Npc_18275"]["Npc_Y"]


	Npc_MoveNpcPos(nNpcId_18263,nMapId,nNpcX_18263,nNpcY_18263)
	Npc_MoveNpcPos(nNpcId_18264,nMapId,nNpcX_18264,nNpcY_18264)
	Npc_MoveNpcPos(nNpcId_18265,nMapId,nNpcX_18265,nNpcY_18265)
	Npc_MoveNpcPos(nNpcId_18266,nMapId,nNpcX_18266,nNpcY_18266)
	Npc_MoveNpcPos(nNpcId_18267,nMapId,nNpcX_18267,nNpcY_18267)
	Npc_MoveNpcPos(nNpcId_18268,nMapId,nNpcX_18268,nNpcY_18268)
	Npc_MoveNpcPos(nNpcId_18269,nMapId,nNpcX_18269,nNpcY_18269)

	Npc_MoveNpcPos(nNpcId_18270,nMapId,nNpcX_18270,nNpcY_18270)
	Npc_MoveNpcPos(nNpcId_18271,nMapId,nNpcX_18271,nNpcY_18271)
	Npc_MoveNpcPos(nNpcId_18272,nMapId,nNpcX_18272,nNpcY_18272)
	Npc_MoveNpcPos(nNpcId_18273,nMapId,nNpcX_18273,nNpcY_18273)
	Npc_MoveNpcPos(nNpcId_18274,nMapId,nNpcX_18274,nNpcY_18274)
	Npc_MoveNpcPos(nNpcId_18275,nMapId,nNpcX_18275,nNpcY_18275)

end



-----------------------------------------npc模块------------------------------------
--npc头像
-- 跨服任务大使
tNpcFace[3475] = 6
tNpcGossip[17280] = tNpcGossip[17280] or DefaultNpc:new{}
tNpcGossip[17280]["OptionHidden"] = 1

--tNpcFace[3522] = 67
tNpcGossip[17980] = tNpcGossip[17980] or DefaultNpc:new{}
tNpcGossip[17980]["OptionHidden"] = 1


--活动时间内
tNpcGossip[17280]["Text1-1"] = {111,112,113}
tNpcGossip[17280]["Text111"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text111"]
tNpcGossip[17280]["Text112"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text112"]
tNpcGossip[17280]["Text113"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text113"]
tNpcGossip[17280]["tOption1-1"] = {20,22,5}
tNpcGossip[17280]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["ActivityTime"])
end

--活动时间前
tNpcGossip[17280]["Text1-2"] = {121,122,123}
tNpcGossip[17280]["Text121"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text121"]
tNpcGossip[17280]["Text122"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text122"]
tNpcGossip[17280]["Text123"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text123"]
tNpcGossip[17280]["tOption1-2"] = {1,2,3,5}
tNpcGossip[17280]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tCrossFestivalTask_GrabEnvelope_Cont["BeforeActivityTime"])
end

--活动时间后
tNpcGossip[17280]["Text1-3"] = {131,132,133}
tNpcGossip[17280]["Text131"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text131"]
tNpcGossip[17280]["Text132"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text132"]
tNpcGossip[17280]["Text133"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text133"]
tNpcGossip[17280]["tOption1-3"] = {6}


------活动时间前，点击了解跨服访使节。
tNpcGossip[17280]["Text8-1"] = {811,812,813}
tNpcGossip[17280]["Text811"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text811"]
tNpcGossip[17280]["Text812"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text812"]
tNpcGossip[17280]["Text813"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text813"]
tNpcGossip[17280]["tOption8-1"] = {4,5}


------活动时间前，点击了解异兽争霸赛。
tNpcGossip[17280]["Text10-1"] = {1011,1012,1013}
tNpcGossip[17280]["Text1011"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1011"]
tNpcGossip[17280]["Text1012"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1012"]
tNpcGossip[17280]["Text1013"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1013"]
tNpcGossip[17280]["tOption10-1"] = {4,5}


tNpcGossip[17280]["Text4-1"] = {411,412,413}
tNpcGossip[17280]["Text411"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text411"]
tNpcGossip[17280]["Text412"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text412"]
tNpcGossip[17280]["Text413"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text413"]
tNpcGossip[17280]["tOption4-1"] = {11,5}

tNpcGossip[17280]["Text2-5"] = {251,252,253}
tNpcGossip[17280]["Text251"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text251"]
tNpcGossip[17280]["Text252"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text252"]
tNpcGossip[17280]["Text253"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text253"]
tNpcGossip[17280]["tOption2-5"] = {8,9,10,11,5}



--接受任务后的提示
tNpcGossip[17280]["Text2-1"] = {211,212}
tNpcGossip[17280]["Text211"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text211"]
tNpcGossip[17280]["Text212"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text212"]
tNpcGossip[17280]["tOption2-1"] = {5}

--等级不足
tNpcGossip[17280]["Text2-2"] = {221,222}
tNpcGossip[17280]["Text221"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text221"]
tNpcGossip[17280]["Text222"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text222"]
tNpcGossip[17280]["tOption2-2"] = {5}

tNpcGossip[17280]["Text2-3"] = {231}
tNpcGossip[17280]["Text231"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text231"]
tNpcGossip[17280]["tOption2-3"] = {5}

--已经领取过奖励点击领取奖励
tNpcGossip[17280]["Text11-1"] = {1101}
tNpcGossip[17280]["Text1101"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1101"]
tNpcGossip[17280]["tOption11-1"] = {18}

--完成任务点击接受任务
tNpcGossip[17280]["Text12-1"] = {1201}
tNpcGossip[17280]["Text1201"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1201"]
tNpcGossip[17280]["tOption12-1"] = {5}

--未完成任务点击领取奖励提示
tNpcGossip[17280]["Text13-1"] = {1301}
tNpcGossip[17280]["Text1301"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1301"]
tNpcGossip[17280]["tOption13-1"] = {16}


--赐福仙子
tNpcGossip[17980]["Text1-1"] = {111}
tNpcGossip[17980]["Text111"] = tCrossFestivalTask_GrabEnvelope_Text[17980]["Text111"]
tNpcGossip[17980]["tOption1-1"] = {13,15}

tNpcGossip[17980]["Text2-1"] = {211}
tNpcGossip[17980]["Text211"] = tCrossFestivalTask_GrabEnvelope_Text[17980]["Text211"]
tNpcGossip[17980]["tOption2-1"] = {14,5}

tNpcGossip[17280]["Text14-1"] = {1401}
tNpcGossip[17280]["Text1401"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1401"]
tNpcGossip[17280]["tOption14-1"] = {17}

tNpcGossip[17280]["Text15-1"] = {1501}
tNpcGossip[17280]["Text1501"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1501"]
tNpcGossip[17280]["tOption15-1"] = {19}

tNpcGossip[17280]["Text16-1"] = {1601}
tNpcGossip[17280]["Text1601"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1601"]
tNpcGossip[17280]["tOption16-1"] = {19}

tNpcGossip[17280]["Text17-1"] = {1701}
tNpcGossip[17280]["Text1701"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1701"]
tNpcGossip[17280]["tOption17-1"] = {19}

tNpcGossip[17280]["Text18-1"] = {1801}
tNpcGossip[17280]["Text1801"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Text1801"]
tNpcGossip[17280]["tOption18-1"] = {19}



-------------选项

--了解跨服访使节
tNpcGossip[17280]["Option1"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option1"]
tNpcGossip[17280]["OptionPoint1"] = "8-1"

--了解异兽争霸赛
tNpcGossip[17280]["Option3"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option3"]
tNpcGossip[17280]["OptionPoint3"] = "10-1"

--返回上一页。
tNpcGossip[17280]["Option4"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option4"]
tNpcGossip[17280]["OptionPoint4"] = "1-2"



----点击接受任务
tNpcGossip[17280]["Option8"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option8"]
tNpcGossip[17280]["OptionFunc8"]="CrossFestivalTask_GrabEnvelope_AcceptCondit</N>17280"
tNpcGossip[17280]["OptionChkFunc8"] = function ()
	return CrossFestivalTask_GrabEnvelope_ShowCondit()
end

----领取奖励
tNpcGossip[17280]["Option9"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option9"]
tNpcGossip[17280]["OptionFunc9"]="CrossFestivalTask_GrabEnvelope_HandRedEnvelope</N>17280"
tNpcGossip[17280]["OptionChkFunc9"] = function ()
	return not User_IsCross()
end

----了解活动详情
tNpcGossip[17280]["Option10"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option10"]
tNpcGossip[17280]["OptionPoint10"] = "4-1"

----返回上一页。
tNpcGossip[17280]["Option11"]=tCrossFestivalTask_GrabEnvelope_Text[17280]["Option11"]
tNpcGossip[17280]["OptionPoint11"] = "1-1"


----赐福拜访使节！
--春节快乐，我给您拜年啦！
tNpcGossip[17980]["Option13"]=tCrossFestivalTask_GrabEnvelope_Text[17980]["Option13"]
tNpcGossip[17980]["OptionPoint13"] = "2-1"
tNpcGossip[17980]["OptionChkFunc13"] = function ()
	return User_IsCross() and CrossFestivalTask_GrabEnvelope_TakeCondit()
end

----希望如此！
tNpcGossip[17980]["Option14"]=tCrossFestivalTask_GrabEnvelope_Text[17980]["Option14"]
tNpcGossip[17980]["OptionFunc14"]="CrossFestivalTask_GrabEnvelope_TakeRedEnvelope</N>17980"
tNpcGossip[17980]["OptionChkFunc14"] = function ()
	return User_IsCross() and CrossFestivalTask_GrabEnvelope_TakeCondit()
end

tNpcGossip[17280]["Option5"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option5"]
tNpcGossip[17280]["Option6"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option6"]
tNpcGossip[17980]["Option12"] = tCrossFestivalTask_GrabEnvelope_Text[17980]["Option12"]

tNpcGossip[17280]["Option20"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option20"]
tNpcGossip[17280]["OptionPoint20"] = "2-5"
tNpcGossip[17280]["OptionChkFunc20"] = function ()
	return not User_IsCross()
end

tNpcGossip[17280]["Option22"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option22"]
tNpcGossip[17280]["OptionPoint22"] = "200"
tNpcGossip[17280]["OptionChkFunc22"] = function ()
	return not User_IsCross() 
end


tNpcGossip[17980]["Option15"] = tCrossFestivalTask_GrabEnvelope_Text[17980]["Option15"]
tNpcGossip[17280]["Option16"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option16"]
tNpcGossip[17280]["Option17"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option17"]
tNpcGossip[17280]["Option18"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option18"]
tNpcGossip[17280]["Option19"] = tCrossFestivalTask_GrabEnvelope_Text[17280]["Option19"]



-----添加“军务备战总兵”和“军务备战参将”对白
tNpcFace[3567] = 87
tNpcGossip[18281] = tNpcGossip[18281] or DefaultNpc:new{}
tNpcGossip[18281]["OptionHidden"] = 1

tNpcGossip[18281]["Text1-1"] = {111,112}
tNpcGossip[18281]["Text111"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text111"]
tNpcGossip[18281]["Text112"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text112"]
tNpcGossip[18281]["tOption1-1"] = {40,41,42,43,44,45}

tNpcGossip[18281]["Text2-1"] = {211,212}
tNpcGossip[18281]["Text211"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text211"]
tNpcGossip[18281]["Text212"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text212"]
tNpcGossip[18281]["tOption2-1"] = {46,45}

tNpcGossip[18281]["Text3-1"] = {311,312}
tNpcGossip[18281]["Text311"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text311"]
tNpcGossip[18281]["Text312"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text312"]
tNpcGossip[18281]["tOption3-1"] = {47,48,49,46,45}

tNpcGossip[18281]["Text4-1"] = {411,412}
tNpcGossip[18281]["Text411"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text411"]
tNpcGossip[18281]["Text412"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text412"]
tNpcGossip[18281]["tOption4-1"] = {50,45}

tNpcGossip[18281]["Text5-1"] = {511,512}
tNpcGossip[18281]["Text511"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text511"]
tNpcGossip[18281]["Text512"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text512"]
tNpcGossip[18281]["tOption5-1"] = {50,45}

tNpcGossip[18281]["Text6-1"] = {611}
tNpcGossip[18281]["Text611"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text611"]
tNpcGossip[18281]["tOption6-1"] = {50,45}

tNpcGossip[18281]["Text7-1"] = {711}
tNpcGossip[18281]["Text711"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text711"]
tNpcGossip[18281]["tOption7-1"] = {46,45}

tNpcGossip[18281]["Text8-1"] = {811,812}
tNpcGossip[18281]["Text811"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text811"]
tNpcGossip[18281]["Text812"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text812"]
tNpcGossip[18281]["tOption8-1"] = {46,45}

tNpcGossip[18281]["Text9-1"] = {911,912}
tNpcGossip[18281]["Text911"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text911"]
tNpcGossip[18281]["tOption9-1"] = {51,52,53,54,46,45}

tNpcGossip[18281]["Text10-1"] = {1011,1012}
tNpcGossip[18281]["Text1011"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text1011"]
tNpcGossip[18281]["tOption10-1"] = {55,45}

tNpcGossip[18281]["Text11-1"] = {1111,1112}
tNpcGossip[18281]["Text1111"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text1111"]
tNpcGossip[18281]["tOption11-1"] = {55,45}

tNpcGossip[18281]["Text12-1"] = {1211,1212}
tNpcGossip[18281]["Text1211"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text1211"]
tNpcGossip[18281]["tOption12-1"] = {55,45}

tNpcGossip[18281]["Text13-1"] = {1311,1312}
tNpcGossip[18281]["Text1311"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Text1311"]
tNpcGossip[18281]["tOption13-1"] = {55,45}


tNpcFace[3568] = 107
tNpcGossip[18282] = tNpcGossip[18282] or DefaultNpc:new{}
tNpcGossip[18282]["OptionHidden"] = 1

tNpcGossip[18282]["Text1-1"] = {111,112,113}
tNpcGossip[18282]["Text111"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text111"]
tNpcGossip[18282]["Text112"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text112"]
tNpcGossip[18282]["Text113"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text113"]
tNpcGossip[18282]["tOption1-1"] = {60,61,62,63,65}

tNpcGossip[18282]["Text2-1"] = {211,212}
tNpcGossip[18282]["Text211"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text211"]
tNpcGossip[18282]["Text212"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text212"]
tNpcGossip[18282]["tOption2-1"] = {64,65}

tNpcGossip[18282]["Text3-1"] = {311,312}
tNpcGossip[18282]["Text311"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text311"]
tNpcGossip[18282]["Text312"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text312"]
tNpcGossip[18282]["tOption3-1"] = {64,65}

tNpcGossip[18282]["Text4-1"] = {411,412}
tNpcGossip[18282]["Text411"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text411"]
tNpcGossip[18282]["Text412"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text412"]
tNpcGossip[18282]["tOption4-1"] = {64,65}

tNpcGossip[18282]["Text5-1"] = {511,512}
tNpcGossip[18282]["Text511"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text511"]
tNpcGossip[18282]["Text512"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Text512"]
tNpcGossip[18282]["tOption5-1"] = {64,65}


--选项
tNpcGossip[18281]["Option40"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option40"]
tNpcGossip[18281]["OptionPoint40"] = "2-1"

tNpcGossip[18281]["Option41"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option41"]
tNpcGossip[18281]["OptionPoint41"] = "3-1"

tNpcGossip[18281]["Option42"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option42"]
tNpcGossip[18281]["OptionPoint42"] = "7-1"

tNpcGossip[18281]["Option43"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option43"]
tNpcGossip[18281]["OptionPoint43"] = "8-1"

tNpcGossip[18281]["Option44"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option44"]
tNpcGossip[18281]["OptionPoint44"] = "9-1"

tNpcGossip[18281]["Option45"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option45"]

tNpcGossip[18281]["Option46"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option46"]
tNpcGossip[18281]["OptionPoint46"] = "1-1"

tNpcGossip[18281]["Option47"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option47"]
tNpcGossip[18281]["OptionPoint47"] = "4-1"

tNpcGossip[18281]["Option48"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option48"]
tNpcGossip[18281]["OptionPoint48"] = "5-1"

tNpcGossip[18281]["Option49"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option49"]
tNpcGossip[18281]["OptionPoint49"] = "6-1"

tNpcGossip[18281]["Option50"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option50"]
tNpcGossip[18281]["OptionPoint50"] = "3-1"

tNpcGossip[18281]["Option51"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option51"]
tNpcGossip[18281]["OptionPoint51"] = "10-1"

tNpcGossip[18281]["Option52"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option52"]
tNpcGossip[18281]["OptionPoint52"] = "11-1"

tNpcGossip[18281]["Option53"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option53"]
tNpcGossip[18281]["OptionPoint53"] = "12-1"

tNpcGossip[18281]["Option54"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option54"]
tNpcGossip[18281]["OptionPoint54"] = "13-1"

tNpcGossip[18281]["Option55"] = tCrossFestivalTask_GrabEnvelope_Text[18281]["Option55"]
tNpcGossip[18281]["OptionPoint55"] = "9-1"

tNpcGossip[18282]["Option60"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option60"]
tNpcGossip[18282]["OptionPoint60"] = "2-1"

tNpcGossip[18282]["Option61"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option61"]
tNpcGossip[18282]["OptionPoint61"] = "3-1"

tNpcGossip[18282]["Option62"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option62"]
tNpcGossip[18282]["OptionPoint62"] = "4-1"

tNpcGossip[18282]["Option63"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option63"]
tNpcGossip[18282]["OptionPoint63"] = "5-1"

tNpcGossip[18282]["Option64"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option64"]
tNpcGossip[18282]["OptionPoint64"] = "1-1"

tNpcGossip[18282]["Option65"] = tCrossFestivalTask_GrabEnvelope_Text[18282]["Option65"]


----------------------------------------------------时间自检
--203W 移动npc
-- tOntimerMin_M[00] = tOntimerMin_M[00] or {}
-- table.insert(tOntimerMin_M[00],CrossFestivalTask_GrabEnvelope_MoveNpc)

-- tOntimerMin_M[10] = tOntimerMin_M[10] or {}
-- table.insert(tOntimerMin_M[10],CrossFestivalTask_GrabEnvelope_MoveNpc)

-- tOntimerMin_M[20] = tOntimerMin_M[20] or {}
-- table.insert(tOntimerMin_M[20],CrossFestivalTask_GrabEnvelope_MoveNpc)

-- tOntimerMin_M[30] = tOntimerMin_M[30] or {}
-- table.insert(tOntimerMin_M[30],CrossFestivalTask_GrabEnvelope_MoveNpc)

-- tOntimerMin_M[40] = tOntimerMin_M[40] or {}
-- table.insert(tOntimerMin_M[40],CrossFestivalTask_GrabEnvelope_MoveNpc)

-- tOntimerMin_M[50] = tOntimerMin_M[50] or {}
-- table.insert(tOntimerMin_M[50],CrossFestivalTask_GrabEnvelope_MoveNpc)









