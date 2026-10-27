------------------------------------------------------------------------------------
--Name:			150728[简体征服][活动脚本]万圣节（10.29-11.4）之双龙游园
--Purpose:		万圣节（10.29-11.4）之双龙游园
--Creator:		黄昕哲
--Created:		2015/07/28
------------------------------------------------------------------------------------
--前缀	Halloween2015_Garden_
--复用2014年万圣节

--stc(128,75) 控制任务进度，1接受，2-5踩陷阱，6完成并领取奖励
--stc(129,35) 使用了变身符 cd 60秒
--------------------------------------------------------------------------------------相关数据表定义

local tHalloween2015_Garden_Data = {}
	--活动时间相关
	tHalloween2015_Garden_Data["BeforeAct"] = "2015-01-01 00:00 2015-10-28 23:59"
	tHalloween2015_Garden_Data["DuringAct"] = "2015-10-29 00:00 2015-11-04 23:59"
	
	--每天开启活动的时间
	tHalloween2015_Garden_Data["Act"] = {}
	tHalloween2015_Garden_Data["Act"][1] = "09:00 09:59"
	tHalloween2015_Garden_Data["Act"][2] = "12:00 12:59"
	tHalloween2015_Garden_Data["Act"][3] = "19:00 19:59"
	tHalloween2015_Garden_Data["Act"][4] = "22:00 22:59"
	
	--等级和转世
	tHalloween2015_Garden_Data["MinLev"] = 80
	tHalloween2015_Garden_Data["MaxLev"] = 140
	tHalloween2015_Garden_Data["MinMeto"] = 0
	
	--概率
	tHalloween2015_Garden_Data["Rate"] = {}
	tHalloween2015_Garden_Data["Rate"]["Transform"] = 9
	tHalloween2015_Garden_Data["Rate"]["Furniture"] = 6
	
	--id
	tHalloween2015_Garden_Data["TransformItem"] = 3007094
	tHalloween2015_Garden_Data["NpcId"] = 17080
	--家具
	tHalloween2015_Garden_Data["Furniture"] = {}
	tHalloween2015_Garden_Data["Furniture"][1] = 3007095
	tHalloween2015_Garden_Data["Furniture"][2] = 3007096
	tHalloween2015_Garden_Data["Furniture"][3] = 3007097
	tHalloween2015_Garden_Data["Furniture"][4] = 3007098
	tHalloween2015_Garden_Data["Furniture"][5] = 3007099
	tHalloween2015_Garden_Data["Furniture"][6] = 3007100
	
	--地图属性
	tHalloween2015_Garden_Data["MapType"] = 1024
	
	--家具摆放限制
	tHalloween2015_Garden_Data["FurnitureLimit"] = {}
	tHalloween2015_Garden_Data["FurnitureLimit"][2] = 8
	tHalloween2015_Garden_Data["FurnitureLimit"][3] = 9
	tHalloween2015_Garden_Data["FurnitureLimit"][4] = 10
	tHalloween2015_Garden_Data["FurnitureLimit"][5] = 12
	

--法术
local tHalloween2015_Garden_Magic = {}
tHalloween2015_Garden_Magic["Task"] = {}
tHalloween2015_Garden_Magic["Task"][1] = {12186,0,3053,3600}
tHalloween2015_Garden_Magic["Task"][2] = {12187,0,2150,3600}
tHalloween2015_Garden_Magic["Task"][3] = {12188,0,2478,3600}
tHalloween2015_Garden_Magic["Task"][4] = {12189,0,2171,3600}
tHalloween2015_Garden_Magic["Task"][5] = {12190,0,2030,3600}
tHalloween2015_Garden_Magic["Task"][6] = {12181,0,2104,3600}
tHalloween2015_Garden_Magic["Task"][7] = {12181,0,2104,3600}
tHalloween2015_Garden_Magic["Task"][8] = {12185,0,3610,3600}
tHalloween2015_Garden_Magic["Task"][9] = {12194,0,3055,3600}
tHalloween2015_Garden_Magic["Item"] = {}
tHalloween2015_Garden_Magic["Item"][1] = {12256,0,3053,60}
tHalloween2015_Garden_Magic["Item"][2] = {12257,0,2150,60}
tHalloween2015_Garden_Magic["Item"][3] = {12258,0,2478,60}
tHalloween2015_Garden_Magic["Item"][4] = {12259,0,2171,60}
tHalloween2015_Garden_Magic["Item"][5] = {12260,0,2030,60}
tHalloween2015_Garden_Magic["Item"][6] = {12262,0,2104,60}
tHalloween2015_Garden_Magic["Item"][7] = {12262,0,2104,60}
tHalloween2015_Garden_Magic["Item"][8] = {12263,0,3610,60}
tHalloween2015_Garden_Magic["Item"][9] = {12264,0,3055,60}
tHalloween2015_Garden_Magic["Effect"] = "relive"
tHalloween2015_Garden_Magic["Finish"] =  "angelwing"

--掩码记录
local tHalloween2015_Garden_Stc = {}
	tHalloween2015_Garden_Stc["Phase"] = {}
	tHalloween2015_Garden_Stc["Phase"]["EventType"] = 128
	tHalloween2015_Garden_Stc["Phase"]["DataType"] = 75
	
	tHalloween2015_Garden_Stc["Phase"]["GetTask"] = 1
	tHalloween2015_Garden_Stc["Phase"]["Trap1"] = 2
	tHalloween2015_Garden_Stc["Phase"]["Trap2"] = 3
	tHalloween2015_Garden_Stc["Phase"]["Trap3"] = 4
	tHalloween2015_Garden_Stc["Phase"]["Trap4"] = 5
	tHalloween2015_Garden_Stc["Phase"]["GetReward"] = 6
	
	tHalloween2015_Garden_Stc["Inv"] = {}
	tHalloween2015_Garden_Stc["Inv"]["EventType"] = 129
	tHalloween2015_Garden_Stc["Inv"]["DataType"] = 35
	
	tHalloween2015_Garden_Stc["Inv"]["Transform"] = 1
	tHalloween2015_Garden_Stc["Inv"]["Time"] = 60


--位置
local tHalloween2015_Garden_Pos = {}
tHalloween2015_Garden_Pos["MapId"] = 1002
--出发点
tHalloween2015_Garden_Pos["Start"] = {}
	tHalloween2015_Garden_Pos["Start"]["CellX"] = 284
	tHalloween2015_Garden_Pos["Start"]["CellY"] = 360
--变身点
tHalloween2015_Garden_Pos["Trap"] = {}
	tHalloween2015_Garden_Pos["Trap"][1] = {}
		tHalloween2015_Garden_Pos["Trap"][1]["CellX"] = 348
		tHalloween2015_Garden_Pos["Trap"][1]["CellY"] = 334
	tHalloween2015_Garden_Pos["Trap"][2] = {}
		tHalloween2015_Garden_Pos["Trap"][2]["CellX"] = 388
		tHalloween2015_Garden_Pos["Trap"][2]["CellY"] = 257
	tHalloween2015_Garden_Pos["Trap"][3] = {}
		tHalloween2015_Garden_Pos["Trap"][3]["CellX"] = 445
		tHalloween2015_Garden_Pos["Trap"][3]["CellY"] = 310
	tHalloween2015_Garden_Pos["Trap"][4] = {}
		tHalloween2015_Garden_Pos["Trap"][4]["CellX"] = 394
		tHalloween2015_Garden_Pos["Trap"][4]["CellY"] = 382
		
tHalloween2015_Garden_Pos["Envoy"] = {}
tHalloween2015_Garden_Pos["Envoy"]["CellX"] = 295
tHalloween2015_Garden_Pos["Envoy"]["CellY"] = 370
tHalloween2015_Garden_Pos["Envoy"]["Id"] = 18781

--log
local tHalloween2015_Garden_Log = {}
tHalloween2015_Garden_Log["FestivalId"] = 3456
tHalloween2015_Garden_Log["LogId"] = 10002309
tHalloween2015_Garden_Log["GetTask"] = "0,0,0,0,10002309,1[1],0,0"
tHalloween2015_Garden_Log["TaskFail"] = "0,0,0,0,10002309,1[7],0,0"
tHalloween2015_Garden_Log["FestivalPack"] = "0,0,0,0,10002309,2,3007094[3003625][%s],1[1][1]"

tHalloween2015_Garden_Log["TransformItemDel"] = "0,0,3007094,1,10002309,3,0,0"

tHalloween2015_Garden_Log["FurnitureDel"] = "0,0,%s,1,10002309,3,0,0"



--------------------------------------------------------------------------------------逻辑部分

--隔天清理以及检查任务阶段,用于决定选项的显示,返回true,显示"开始游园",返回false则不显示
function Halloween2015_Garden_PhaseChk()
	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	--完成任务且隔天,需要清理掩码
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["GetReward"]) and Task_StcInterval(nPhaseEvent,nPhaseType,1,4) then
		Task_SetStatistic(nPhaseEvent,nPhaseType,0,1,0)
		Task_SetStcTimestamp(nPhaseEvent,nPhaseType,0)
	end
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,"<=",tHalloween2015_Garden_Stc["Phase"]["GetTask"]) then
		return true
	end
	return false
end

--选择"开始游园"
function Halloween2015_Garden_ApplyTask(nNpcId)
	--检测活动时间
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	--检测玩家等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_Garden_Data["MinLev"],tHalloween2015_Garden_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--检测当前活动是否开启
	local nCounter = 0
	for _,v in pairs(tHalloween2015_Garden_Data["Act"]) do
		if Sys_ChkDayTime(v) then
			nCounter = nCounter + 1
		end
	end
	--时间均不符合
	if nCounter == 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	--检测任务阶段,已完成则不可接到任务,未接到则进行变装,已接到则提示
	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["GetReward"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["GetTask"]) and Get_UserTransformId() >= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	Halloween2015_Garden_StartTask()
end
	--未接到任务,开始任务
function Halloween2015_Garden_StartTask()

	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	Task_SetStatistic(nPhaseEvent,nPhaseType,tHalloween2015_Garden_Stc["Phase"]["GetTask"],1,0)
	Task_SetStcTimestamp(nPhaseEvent,nPhaseType,0)
	Sys_SaveActionFestivalLog(tHalloween2015_Garden_Log["GetTask"])
	--变装
	Halloween2015_Garden_Transform("Task")
	local nCellX = tHalloween2015_Garden_Pos["Trap"][1]["CellX"]
	local nCellY = tHalloween2015_Garden_Pos["Trap"][1]["CellY"]
	local nMapId = tHalloween2015_Garden_Pos["MapId"]
	Sys_MsgBox(tHalloween2015_Garden_Text[17080]["Msg1"])
	Halloween2015_Garden_AutoFindWay(1)
	User_TalkChannel2005(tHalloween2015_Garden_Text[17080]["Msg1"])
end

--自动寻路到下一点
function Halloween2015_Garden_AutoFindWay(nNext)
	local nMapId = tHalloween2015_Garden_Pos["MapId"]
	local nCellX = 0
	local nCellY = 0
	local nNpcId = nil
	if nNext == 0 then
		nCellX = tHalloween2015_Garden_Pos["Start"]["CellX"]
		nCellY = tHalloween2015_Garden_Pos["Start"]["CellY"]
		nNpcId = tHalloween2015_Garden_Data["NpcId"]
	else
		nCellX = tHalloween2015_Garden_Pos["Trap"][nNext]["CellX"]
		nCellY = tHalloween2015_Garden_Pos["Trap"][nNext]["CellY"]
	end
	Sys_GotoSomeWhere(nCellX,nCellY,nMapId,nNpcId)
end


--变装(包括物品和任务变身,根据传进的参数sMethod来决定变身)
function Halloween2015_Garden_Transform(sMethod)
	local nTransformType = math.random(tHalloween2015_Garden_Data["Rate"]["Transform"])
	local nSkillId = tHalloween2015_Garden_Magic[sMethod][nTransformType][1]
	local nSkillLev = tHalloween2015_Garden_Magic[sMethod][nTransformType][2]
	local nMonsterType = tHalloween2015_Garden_Magic[sMethod][nTransformType][3]
	local nRemainTime = tHalloween2015_Garden_Magic[sMethod][nTransformType][4]
	User_TransForm(nSkillId,nSkillLev,nMonsterType,nRemainTime)
	User_EffectAdd("self",tHalloween2015_Garden_Magic["Effect"])
end

--选择"完成游园"
function Halloween2015_Garden_ApplyReward(nNpcId)
	--检查活动时间
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	--检测任务阶段
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["GetReward"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["GetTask"]) and Task_StcInterval(nPhaseEvent,nPhaseType,1,2) then
		--超时,任务失败,清理
		Task_SetStatistic(nPhaseEvent,nPhaseType,0,1,0)
		Task_SetStcTimestamp(nPhaseEvent,nPhaseType,0)
		Sys_SaveActionFestivalLog(tHalloween2015_Garden_Log["TaskFail"])
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	--1小时内,进度判断 变形无=>重新开始任务,stc>=5=>完成任务给奖励,提示玩家,stc<5=>提示玩家,
	--未变身,重新开始任务
	if Get_UserTransformId() < 0 then
		Halloween2015_Garden_StartTask()
		return
	end
	--完成任务给奖励
	if Task_ChkStcValue(nPhaseEvent,nPhaseType,">=",tHalloween2015_Garden_Stc["Phase"]["Trap4"])then
		Halloween2015_Garden_GetReward(nNpcId)
		return
	end
	--提示玩家
	LinkNpcGossipFunc_New(nNpcId,"3-2")
end

--获取奖励
function Halloween2015_Garden_GetReward(nNpcId)
	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	--检测背包
	if not User_CheckLeftSpace(3) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	--背包有空位
	User_SetTransform(0)
	Task_SetStatistic(nPhaseEvent,nPhaseType,tHalloween2015_Garden_Stc["Phase"]["GetReward"],1,0)
	Task_SetStcTimestamp(nPhaseEvent,nPhaseType,0)
	--变身符
	Item_AddItem(tHalloween2015_Garden_Data["TransformItem"])
	User_EffectAdd("self",tHalloween2015_Garden_Magic["Finish"])
	--礼包
	FestivalGeneralPackage_GetGift(tHalloween2015_Garden_Log["FestivalId"],tHalloween2015_Garden_Log["LogId"])
		--获取骑宠家具
	local nFurniture = math.random(tHalloween2015_Garden_Data["Rate"]["Furniture"])
	Item_AddItem(tHalloween2015_Garden_Data["Furniture"][nFurniture])
	local sLog = string.format(tHalloween2015_Garden_Log["FestivalPack"],tHalloween2015_Garden_Data["Furniture"][nFurniture])
	Sys_SaveActionFestivalLog(sLog)
	User_TalkChannel2005(tHalloween2015_Garden_Text[17080]["Talk1"])
end

--trap调用函数,四个点1204-1207的坐标（249,235）,（298,205）,（302,149）,(350,256),分别对应phase=1-4
function Halloween2015_Garden_TrapProcess(nTrapId,nTrapType)
	--时间检测
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		return
	end
	local nPhaseEvent = tHalloween2015_Garden_Stc["Phase"]["EventType"]
	local nPhaseType = tHalloween2015_Garden_Stc["Phase"]["DataType"]
	--nPhase = 0-6
	local nPhase= Get_UserStatisticValue(nPhaseEvent,nPhaseType)
	local nTrapOrder = nTrapType - 1203
	--已领取过奖励或无任务的情况,无视
	if nPhase >= tHalloween2015_Garden_Stc["Phase"]["GetReward"] or nPhase <= 0 then
		return
	end
	--有任务且未变身的情况,重新开始任务
	if Get_UserTransformId() < 0 and nPhase > 0 then
		Sys_MsgBox(tHalloween2015_Garden_Text["Trap"]["Msg1"])
		Task_SetStatistic(nPhaseEvent,nPhaseType,0,1,0)
		Task_SetStcTimestamp(nPhaseEvent,nPhaseType,0)
		Halloween2015_Garden_AutoFindWay(0)
		return
	end
	--已到过所有的变装点
	if nPhase == tHalloween2015_Garden_Stc["Phase"]["Trap4"] then
		Halloween2015_Garden_TaskFinOnTrap()
		return
	end
	--处在和当前不对应的trap上
	if nPhase ~= nTrapOrder then
		Halloween2015_Garden_OnTrap(nPhase)
		return
	end
	--处在当前阶段对应的trap上,不是最后1个phase,当前phase+1,log,随机变身3600s,提示玩家下一个变装点
	if nPhase < tHalloween2015_Garden_Stc["Phase"]["Trap3"] then
		Task_SetStatistic(nPhaseEvent,nPhaseType,nPhase+1,1,0)
		Halloween2015_Garden_Transform("Task")
		Halloween2015_Garden_OnTrap(nPhase+1)
		Halloween2015_Garden_PhaseChk()
		return
	--最后的phase(nPhase = 4),phase+1,log,随机变身3600s,提示玩家完成任务
	else
		Task_SetStatistic(nPhaseEvent,nPhaseType,nPhase+1,1,0)
		Halloween2015_Garden_Transform("Task")
		local nCellX = tHalloween2015_Garden_Pos["Start"]["CellX"]
		local nCellY = tHalloween2015_Garden_Pos["Start"]["CellY"]
		local nMapId = tHalloween2015_Garden_Pos["MapId"]
		local nNpcId = tHalloween2015_Garden_Data["NpcId"]
		Sys_GotoSomeWhere(nCellX,nCellY,nMapId,nNpcId)
		Sys_MsgBox(tHalloween2015_Garden_Text["Trap"]["Msg3"])
		User_TalkChannel2005(tHalloween2015_Garden_Text["Trap"]["Msg3"])
		Halloween2015_Garden_PhaseChk()
		return
	end
end

--任务中,站到陷阱的情况(nphase=1时,需要站到1号trap)
function Halloween2015_Garden_OnTrap(nPhase)
	local nCellX = 0
	local nCellY = 0
	--提示玩家对应的坐标,以及自动寻路函数
	local sMsgToPlayer = ""
	if nPhase < tHalloween2015_Garden_Stc["Phase"]["Trap4"] then
		nCellX = tHalloween2015_Garden_Pos["Trap"][nPhase]["CellX"]
		nCellY = tHalloween2015_Garden_Pos["Trap"][nPhase]["CellY"]
		sMsgToPlayer = string.format(tHalloween2015_Garden_Text["Trap"]["Msg2"],nCellX,nCellY)
	else
		sMsgToPlayer = tHalloween2015_Garden_Text["Trap"]["Msg3"]
	end
	Sys_MsgBox(sMsgToPlayer)
	Halloween2015_Garden_AutoFindWay(nPhase)
	User_TalkChannel2005(sMsgToPlayer)
end

--已完成任务,又站到陷阱上的情况
function Halloween2015_Garden_TaskFinOnTrap()
	--变形了
	if Get_UserTransformId() >= 0 then
		Halloween2015_Garden_AutoFindWay(0)
		Sys_MsgBox(tHalloween2015_Garden_Text["Trap"]["Msg3"])
		return
	end
	--没变形,提示回到上一个点(第4个陷阱)去变身(相当于去过了3号陷阱)
	Halloween2015_Garden_OnTrap(tHalloween2015_Garden_Stc["Phase"]["Trap3"])
end

--变身符函数
function Halloween2015_Garden_TransItemProcess(nItemId)
	--过期删除
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		Sys_SaveActionFestivalLog(tHalloween2015_Garden_Log["TransformItemDel"])
		if Item_ChkItem(nItemId) then
			User_TalkChannel2005(tHalloween2015_Garden_Text[3007094]["Talk1"])
			Item_DelItem(nItemId)
		end
		return
	end
	--已经变身
	if Get_UserTransformId() >= 0 then
		User_TalkChannel2005(tHalloween2015_Garden_Text[3007094]["Talk2"])
		return
	end
	--未变身,检测掩码
	local nInvEvent = tHalloween2015_Garden_Stc["Inv"]["EventType"]
	local nInvType = tHalloween2015_Garden_Stc["Inv"]["DataType"]
	local nInvTransform = tHalloween2015_Garden_Stc["Inv"]["Transform"]
	local nInvTime = tHalloween2015_Garden_Stc["Inv"]["Time"]
	--时间间隔不足60s
	if Task_ChkStcValue(nInvEvent,nInvType,">=",nInvTransform)  and Task_StcInterval(nInvEvent,nInvType,nInvTime,0) then
		User_TalkChannel2005(tHalloween2015_Garden_Text[3007094]["Talk3"])
		return
	end
	Task_SetStatistic(nInvEvent,nInvType,nInvTransform,1,0)
	Task_SetStcTimestamp(nInvEvent,nInvType,0)
	if not Item_ChkItem(nItemId) then
		return
	end
	--存在物品,删除成功后变身
	if Item_DelItem(nItemId) then
		Halloween2015_Garden_Transform("Item")
	end
end


--家具统一调用函数
function Halloween2015_Garden_FurnitureProcess(nItemId,sItemName)
	--过期删除
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		Sys_SaveActionFestivalLog(string.format(tHalloween2015_Garden_Log["FurnitureDel"],nItemId))
		if Item_ChkItem(nItemId) then
			User_TalkChannel2005(tHalloween2015_Garden_Text[3007094]["Talk1"])
			Item_DelItem(nItemId)
		end
		return
	end
	--取玩家所在地图的id和属性,用于判断玩家是否在自己家中
	local nNowMapId = Get_UserMapId() 
	local nMapType = Get_MapType(nNowMapId)
	local nMapLev = Get_MapResLev(nNowMapId)
	--在期限内,检测地图属性是否为家庭属性1024,地图是否属于玩家
	if not Sys_ParseNumbersContain(tHalloween2015_Garden_Data["MapType"],nMapType) then
		User_TalkChannel2007(tHalloween2015_Garden_Text["Furniture"]["TalkError1"])
		return
	end
	if Get_MapOwnerId() ~= Get_UserId() then
		User_TalkChannel2007(tHalloween2015_Garden_Text["Furniture"]["TalkError2"])
		return
	end
	--当前地图为玩家的家,检测房子等级,获取家具上限
	local nFurnitureLimit = 0
	if 2 <= nMapLev and nMapLev < 6 then
		nFurnitureLimit = tHalloween2015_Garden_Data["FurnitureLimit"][nMapLev]
	else
		Sys_DialogText(tHalloween2015_Garden_Text["Furniture"]["Text121"])
		Sys_DialogOption(tHalloween2015_Garden_Text["Furniture"]["Option2"])
		Sys_DialogEnd()
		return
	end
	--判断玩家房子内的家具数量
	if Get_NpcCount() >= nFurnitureLimit then
		local sErrorTip = string.format(tHalloween2015_Garden_Text["Furniture"]["TalkError3"],nMapLev,tHalloween2015_Garden_Data["FurnitureLimit"][nMapLev])
		User_TalkChannel2007(sErrorTip)
		return
	end
	--创建一个npc
	local nNpcType = tHalloween2015_Garden_DynaNpc["Type"]
	local nNpcLookface = tHalloween2015_Garden_DynaNpc[nItemId][2]
	Npc_RequestLayNpcByItem("</F>Halloween2015_Garden_CreateNpc</N>" .. nItemId,nNpcType,nNpcLookface,0,0)
end

--创建npc后调用的函数
function Halloween2015_Garden_CreateNpc(nItemId)
	if Item_ChkItem(nItemId) then
		local sNpcName = tHalloween2015_Garden_DynaNpc[nItemId][1]
		local nNpcType = tHalloween2015_Garden_DynaNpc["Type"]
		local nNpcSort = tHalloween2015_Garden_DynaNpc["Sort"]
		local nNpcLookFace = tHalloween2015_Garden_DynaNpc[nItemId][2]
		local nNpcOwnertype = tHalloween2015_Garden_DynaNpc["Ownertype"]
		local nNpcLife = tHalloween2015_Garden_DynaNpc["Life"]
		local nNpcRegionType = tHalloween2015_Garden_DynaNpc["RegionType"]
		local nNpcBase = tHalloween2015_Garden_DynaNpc["Base"]
		local nNpcLinkid = tHalloween2015_Garden_DynaNpc["Linkid"]
		local nNpcTask0 = tHalloween2015_Garden_DynaNpc[nItemId][3]
		Npc_CreatLayNpcByItem(sNpcName,nNpcType,nNpcSort,nNpcLookFace,nNpcOwnertype,nNpcLife,nNpcRegionType,nNpcBase,nNpcLinkid,nNpcTask0)
		Item_DelItem(nItemId)
	end
end

--家具npc接出函数
function Halloween2015_Garden_TalkToFurniture(nItemId)
	local sNpcName = Get_ItemtypeName(nItemId)
	--检测是否是玩家的家
	if Get_MapOwnerId() ~= Get_UserId() then
		return
	end
	--检测是否在活动时间内
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		Npc_DelDynaByID()
		local sAfterDialog = string.format(tHalloween2015_Garden_Text["Furniture"]["Talk1"],sNpcName)
		User_TalkChannel2005(sAfterDialog)
		return
	end
	--活动时间内,可以收起家具
	local sRecycleDialog = string.format(tHalloween2015_Garden_Text["Furniture"]["Text111"],sNpcName)
	Sys_DialogText(sRecycleDialog)
	Sys_DialogOption(tHalloween2015_Garden_Text["Furniture"]["Option1"],"</F>Halloween2015_Garden_RecycleFurniture</N>" .. nItemId)
	Sys_DialogEnd()
end

--收起家具
function Halloween2015_Garden_RecycleFurniture(nItemId)
	--背包无空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tHalloween2015_Garden_Text["Furniture"]["TalkError4"] )
		return
	end
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		Npc_DelDynaByID()
		local sAfterDialog = string.format(tHalloween2015_Garden_Text["Furniture"]["Talk1"],sNpcName)
		User_TalkChannel2005(sAfterDialog)
		return
	end
	--有空间,先删除npc,给物品
	Npc_DelDynaByID()
	Item_AddItem(nItemId)
end

--------------------------------------------------------------------------------------Item部分
--变身符
tItem[3007094] = tItem[3007094] or {}
tItem[3007094]["Function"] = function(nItemId,sItemName)
	Halloween2015_Garden_TransItemProcess(nItemId)
end


--家具
for i = 3007095,3007100 do
	tItem[i] = tItem[i] or {}
	tItem[i]["Function"] = function(nItemId,sItemName)
		Halloween2015_Garden_FurnitureProcess(nItemId,sItemName)
	end
end

--背包信
tItem[3004809] = tItem[3004809] or {}
tItem[3004809]["Function"] = function(nItemId,sItemName)
	Halloween2015_Garden_PackLetter(nItemId)
end

function Halloween2015_Garden_PackLetter(nItemId)
	if not Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"]) then
		Item_DelItem(3004809)
		User_TalkChannel2005(tBackpackLetter_Text[3004809]["AftTime"])
		return
	end
	Sys_DialogText(tBackpackLetter_Text[3004809]["Dialog1"])
	Sys_DialogText(tBackpackLetter_Text[3004809]["Dialog2"])
	Sys_DialogOption(tBackpackLetter_Text[3004809]["Option1"],"</F>Halloween2015_Garden_UseLetter")
	Sys_DialogEnd()
end

function Halloween2015_Garden_UseLetter(nItemId)
	Item_DelItem(3004809)
	if Get_UserLevel() < tHalloween2015_Garden_Data["MaxLev"] then
	--未满级
		User_AddExpTime(30)
		User_TalkChannel2005(tBackpackLetter_Text[3004809]["Reward1"])
	else
		User_AddCultivation(15)
		User_TalkChannel2005(tBackpackLetter_Text[3004809]["Reward2"])
	end
	Sys_GotoSomeWhere(tHalloween2015_Garden_Pos["Envoy"]["CellX"],tHalloween2015_Garden_Pos["Envoy"]["CellY"],tHalloween2015_Garden_Pos["MapId"],tHalloween2015_Garden_Pos["Envoy"]["Id"])
end

--------------------------------------------------------------------------------------Npc部分

--游园大使小兔
tNpcFace[3169] = 193
tNpcGossip[17080] = tNpcGossip[17080] or DefaultNpc:new{}
tNpcGossip[17080]["OptionHidden"] = 1

--活动前
tNpcGossip[17080]["Text1-1"] = {111,112,113}
tNpcGossip[17080]["Text111"] = tHalloween2015_Garden_Text[17080]["Text111"]
tNpcGossip[17080]["Text112"] = tHalloween2015_Garden_Text[17080]["Text112"]
tNpcGossip[17080]["Text113"] = tHalloween2015_Garden_Text[17080]["Text113"]
tNpcGossip[17080]["tOption1-1"] = {1}
	tNpcGossip[17080]["Option1"] = tHalloween2015_Garden_Text[17080]["Option1"]
tNpcGossip[17080]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tHalloween2015_Garden_Data["BeforeAct"])
end

--活动中
tNpcGossip[17080]["Text1-2"] = {121,122,113}
tNpcGossip[17080]["Text121"] = tHalloween2015_Garden_Text[17080]["Text121"]
tNpcGossip[17080]["Text122"] = tHalloween2015_Garden_Text[17080]["Text122"]
tNpcGossip[17080]["Text123"] = tHalloween2015_Garden_Text[17080]["Text123"]
tNpcGossip[17080]["tOption1-2"] = {2,3,4,5}
	tNpcGossip[17080]["Option2"] = tHalloween2015_Garden_Text[17080]["Option2"]
		tNpcGossip[17080]["OptionFunc2"] = "Halloween2015_Garden_ApplyTask</N>17080"
		tNpcGossip[17080]["OptionChkFunc2"] = function()
			return Halloween2015_Garden_PhaseChk()
		end
	tNpcGossip[17080]["Option3"] = tHalloween2015_Garden_Text[17080]["Option3"]
		tNpcGossip[17080]["OptionFunc3"] = "Halloween2015_Garden_ApplyReward</N>17080"
		tNpcGossip[17080]["OptionChkFunc3"] = function()
			return not Halloween2015_Garden_PhaseChk()
		end
	tNpcGossip[17080]["Option4"] = tHalloween2015_Garden_Text[17080]["Option4"]
		tNpcGossip[17080]["OptionPoint4"] = "4-1"
	tNpcGossip[17080]["Option5"] = tHalloween2015_Garden_Text[17080]["Option5"]
tNpcGossip[17080]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(tHalloween2015_Garden_Data["DuringAct"])
end

--活动后
tNpcGossip[17080]["Text1-3"] = {131}
tNpcGossip[17080]["Text131"] = tHalloween2015_Garden_Text[17080]["Text131"]
tNpcGossip[17080]["tOption1-3"] = {6}
	tNpcGossip[17080]["Option6"] = tHalloween2015_Garden_Text[17080]["Option6"]

--开始游园
--等级不足
tNpcGossip[17080]["Text2-1"] = {211}
tNpcGossip[17080]["Text211"] = tHalloween2015_Garden_Text[17080]["Text211"]
tNpcGossip[17080]["tOption2-1"] = {7}
	tNpcGossip[17080]["Option7"] = tHalloween2015_Garden_Text[17080]["Option7"]

--时间段不正确
tNpcGossip[17080]["Text2-2"] = {221}
tNpcGossip[17080]["Text221"] = tHalloween2015_Garden_Text[17080]["Text221"]
tNpcGossip[17080]["tOption2-2"] = {8}
	tNpcGossip[17080]["Option8"] = tHalloween2015_Garden_Text[17080]["Option8"]

--已经完成
tNpcGossip[17080]["Text2-3"] = {231}
tNpcGossip[17080]["Text231"] = tHalloween2015_Garden_Text[17080]["Text231"]
tNpcGossip[17080]["tOption2-3"] = {9}
	tNpcGossip[17080]["Option9"] = tHalloween2015_Garden_Text[17080]["Option9"]

--参加活动
tNpcGossip[17080]["Text2-4"] = {241}
tNpcGossip[17080]["Text241"] = tHalloween2015_Garden_Text[17080]["Text241"]
tNpcGossip[17080]["tOption2-4"] = {10}
	tNpcGossip[17080]["Option10"] = tHalloween2015_Garden_Text[17080]["Option10"]

--完成游园
--已完成过
tNpcGossip[17080]["Text3-1"] = {311}
tNpcGossip[17080]["Text311"] = tHalloween2015_Garden_Text[17080]["Text311"]
tNpcGossip[17080]["tOption3-1"] = {11}
	tNpcGossip[17080]["Option11"] = tHalloween2015_Garden_Text[17080]["Option11"]

--超时,任务失败
tNpcGossip[17080]["Text3-2"] = {321}
tNpcGossip[17080]["Text321"] = tHalloween2015_Garden_Text[17080]["Text321"]
tNpcGossip[17080]["tOption3-2"] = {12}
	tNpcGossip[17080]["Option12"] = tHalloween2015_Garden_Text[17080]["Option12"]
	
--背包已满
tNpcGossip[17080]["Text3-3"] = {331}
tNpcGossip[17080]["Text331"] = tHalloween2015_Garden_Text[17080]["Text331"]
tNpcGossip[17080]["tOption3-3"] = {13}
	tNpcGossip[17080]["Option13"] = tHalloween2015_Garden_Text[17080]["Option13"]

--了解任务详情
tNpcGossip[17080]["Text4-1"] = {411,412,413,414}
tNpcGossip[17080]["Text411"] = tHalloween2015_Garden_Text[17080]["Text411"]
tNpcGossip[17080]["Text412"] = tHalloween2015_Garden_Text[17080]["Text412"]
tNpcGossip[17080]["Text413"] = tHalloween2015_Garden_Text[17080]["Text413"]
tNpcGossip[17080]["Text414"] = tHalloween2015_Garden_Text[17080]["Text414"]
tNpcGossip[17080]["tOption3-1"] = {14,15}
	tNpcGossip[17080]["Option14"] = tHalloween2015_Garden_Text[17080]["Option14"]
		tNpcGossip[17080]["OptionPoint14"] = "1-2"
	tNpcGossip[17080]["Option15"] = tHalloween2015_Garden_Text[17080]["Option15"]

--------------------------------------------------------------------------------------Trap部分
--traptypeid= 1204-1207
for i = 1204,1207 do
	tTrap[i] = tTrap[i] or {}
	tTrap[i]["Function"] = function(nTrapId,nTrapType)
		Halloween2015_Garden_TrapProcess(nTrapId,nTrapType)
	end
end