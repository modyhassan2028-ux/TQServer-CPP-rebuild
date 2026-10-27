------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]悬挂同心锁（2.11-2.14）
--Purpose:		2015年情人节悬挂同心锁（2.11-2.14）
--Creator: 		郑鋆
--Created:		2014/11/28
------------------------------------------------------------------------------------

-- 命名前缀
-- ValentinesDay2015_ConcentricLock

-- 掩码说明
-- stc掩码 131 53
-- =10 表示接受任务
-- =11 表示已使用同心锁
-- =12 表示已使用同心钥
-- =20 表示领取过奖励

-- logID 10002398

-- 常量表配置
local tValentinesDay2015_ConcentricLock_Cont = {}
	-- 活动时间
	tValentinesDay2015_ConcentricLock_Cont["ActivityTime"] = "2015-02-11 00:00 2015-02-14 23:59"
	tValentinesDay2015_ConcentricLock_Cont["BeforeActivityTime"] = "2014-02-11 00:00 2015-02-10 23:59"

	-- 等级要求
	tValentinesDay2015_ConcentricLock_Cont["Metempsychosis"] = 0
	tValentinesDay2015_ConcentricLock_Cont["Level"] = 80
	
	-- 掩码
	tValentinesDay2015_ConcentricLock_Cont["StcEvent"] = 131
	tValentinesDay2015_ConcentricLock_Cont["StcType"] = 53
	
	tValentinesDay2015_ConcentricLock_Cont["AcceptData"] = 10
	tValentinesDay2015_ConcentricLock_Cont["ProcessData"] = 11
	tValentinesDay2015_ConcentricLock_Cont["CompleteData"] = 12
	tValentinesDay2015_ConcentricLock_Cont["RewardData"] = 20
	
	-- 任务物品
	tValentinesDay2015_ConcentricLock_Cont["LockItem"] = 3005388
	tValentinesDay2015_ConcentricLock_Cont["KeyItem"] = 3005389
	
	-- 奖励物品
	tValentinesDay2015_ConcentricLock_Cont["RewardItem"] = 3005410
	tValentinesDay2015_ConcentricLock_Cont["FestivalId"] = 3353
	tValentinesDay2015_ConcentricLock_Cont["LogId"] = 10002398
	
	-- 坐标范围
	tValentinesDay2015_ConcentricLock_Cont["Interval"] = 5
	
	-- 读条的配置
	tValentinesDay2015_ConcentricLock_Cont["Secs"] = 3
	tValentinesDay2015_ConcentricLock_Cont["ActionId"] = 220
	
	-- 背包空间
	tValentinesDay2015_ConcentricLock_Cont["BagSpace"] = 2
	
	-- 领奖光效
	tValentinesDay2015_ConcentricLock_Cont["Effect"] = "gam_buss_ap"
	
	-- 比翼双飞鸟活动的陷阱ID
	tValentinesDay2015_ConcentricLock_Cont["BiyiBirds"] = 992310
	tValentinesDay2015_ConcentricLock_Cont["BiyiBirdsOther"] = 992311

-- 物品使用表	
local tValentinesDay2015_ConcentricLock_Item = {}
	-- 同心锁
	tValentinesDay2015_ConcentricLock_Item[3005388] = {}
	tValentinesDay2015_ConcentricLock_Item[3005388]["AcceptData"] = 10
	tValentinesDay2015_ConcentricLock_Item[3005388]["CompleteData"] = 11
	tValentinesDay2015_ConcentricLock_Item[3005388]["MapId"] = 1002
	tValentinesDay2015_ConcentricLock_Item[3005388]["CellX"] = 589
	tValentinesDay2015_ConcentricLock_Item[3005388]["CellY"] = 355
	tValentinesDay2015_ConcentricLock_Item[3005388]["NextMapId"] = 1002
	tValentinesDay2015_ConcentricLock_Item[3005388]["NextCellX"] = 132
	tValentinesDay2015_ConcentricLock_Item[3005388]["NextCellY"] = 345
	tValentinesDay2015_ConcentricLock_Item[3005388]["NextNpcId"] = 0
	tValentinesDay2015_ConcentricLock_Item[3005388]["CompleteEffect"] = "NEW-flower-charm2"
	tValentinesDay2015_ConcentricLock_Item[3005388]["Log"] = "ProcessLog"
	
	-- 同心钥
	tValentinesDay2015_ConcentricLock_Item[3005389] = {}
	tValentinesDay2015_ConcentricLock_Item[3005389]["AcceptData"] = 11
	tValentinesDay2015_ConcentricLock_Item[3005389]["CompleteData"] = 12
	tValentinesDay2015_ConcentricLock_Item[3005389]["MapId"] = 1002
	tValentinesDay2015_ConcentricLock_Item[3005389]["CellX"] = 132
	tValentinesDay2015_ConcentricLock_Item[3005389]["CellY"] = 345
	tValentinesDay2015_ConcentricLock_Item[3005389]["NextMapId"] = 1002
	tValentinesDay2015_ConcentricLock_Item[3005389]["NextCellX"] = 298
	tValentinesDay2015_ConcentricLock_Item[3005389]["NextCellY"] = 385
	tValentinesDay2015_ConcentricLock_Item[3005389]["NextNpcId"] = 17276
	tValentinesDay2015_ConcentricLock_Item[3005389]["CompleteEffect"] = "dbdance_body_new"
	tValentinesDay2015_ConcentricLock_Item[3005389]["Log"] = "CompleteLog"

-- 陷阱触发
	tValentinesDay2015_ConcentricLock_Trap = {}
	tValentinesDay2015_ConcentricLock_Trap[992303] = 10
	tValentinesDay2015_ConcentricLock_Trap[992304] = 11

-- log表
local tValentinesDay2015_ConcentricLock_Log = {}
	tValentinesDay2015_ConcentricLock_Log["AcceptLog"] = "0,0,0,0,10002398,1[1],3005388[3005389],1[1]"
	tValentinesDay2015_ConcentricLock_Log["ProcessLog"] = "0,0,3005388,1,10002398,1[2],0,0"
	tValentinesDay2015_ConcentricLock_Log["CompleteLog"] = "0,0,3005389,1,10002398,1[3],0,0"
	tValentinesDay2015_ConcentricLock_Log["RewardLog"] = "0,0,0,0,10002398,2,3005410,1"	

-- 在双龙城的情人节NPC
local tValentinesDay2015_ConcentricLock_MoveNpc = {}
	tValentinesDay2015_ConcentricLock_MoveNpc["MapId"] = 5000
	tValentinesDay2015_ConcentricLock_MoveNpc["PosX"] = 118
	tValentinesDay2015_ConcentricLock_MoveNpc["PosY"] = 153
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"] = {}
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][1] = 17285
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][2] = 17321
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][3] = 17302
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][4] = 17276
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][5] = 10078
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][6] = 10079
	tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"][7] = 17287

--------------------------------------逻辑部分-----------------------------------------
-- 判断玩家是否完成过任务
function ValentinesDay2015_ConcentricLock_Complete()
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	-- 判断是否完成任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_ConcentricLock_Cont["RewardData"]) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			
			return true
		else
			return false
		end
	else
		return true
	end
end

-- 玩家选我要挂锁条件判断
function ValentinesDay2015_ConcentricLock_SingleCondit(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tValentinesDay2015_ConcentricLock_Cont["Level"],tValentinesDay2015_ConcentricLock_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 判断玩家今天是否领取过奖励
	if not ValentinesDay2015_ConcentricLock_Complete() then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	-- 判断玩家背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_ConcentricLock_Cont["BagSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	local nLockItem = tValentinesDay2015_ConcentricLock_Cont["LockItem"]
	local nKeyItem = tValentinesDay2015_ConcentricLock_Cont["KeyItem"]

	-- 添加同心锁和同心钥
	if not Item_ChkItem(nLockItem) then
		Item_AddItem(nLockItem)
	end
	
	if not Item_ChkItem(nKeyItem) then
		Item_AddItem(nKeyItem)
	end

	-- 掩码记录
	Task_SetStatistic(nEvent,nType,tValentinesDay2015_ConcentricLock_Cont["AcceptData"],1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	Sys_SaveActionFestivalLog(tValentinesDay2015_ConcentricLock_Log["AcceptLog"])
	LinkNpcGossipFunc_New(nNpcId,"3-5")
end

-- 玩家补领物品
function ValentinesDay2015_ConcentricLock_Replacement(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tValentinesDay2015_ConcentricLock_Cont["Level"],tValentinesDay2015_ConcentricLock_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	-- 判断玩家今天是否完成过任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_ConcentricLock_Cont["CompleteData"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	-- 判断玩家背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_ConcentricLock_Cont["BagSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	local nLockItem = tValentinesDay2015_ConcentricLock_Cont["LockItem"]
	local nKeyItem = tValentinesDay2015_ConcentricLock_Cont["KeyItem"]

	-- 判断玩家掩码
	if Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["AcceptData"]) then
		-- 判断这两个物品是否都有
		if Item_ChkItem(nLockItem) and Item_ChkItem(nKeyItem) then
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		end
		
		-- 添加同心锁和同心钥
		if not Item_ChkItem(nLockItem) then
			Item_AddItem(nLockItem)
		end
		
		if not Item_ChkItem(nKeyItem) then
			Item_AddItem(nKeyItem)
		end
		
		LinkNpcGossipFunc_New(nNpcId,"4-4")
		return
		
	elseif Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["ProcessData"]) then
		-- 判断是否有同心钥
		if Item_ChkItem(nKeyItem) then
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		else
			Item_AddItem(nKeyItem)
			LinkNpcGossipFunc_New(nNpcId,"4-4")
			return
		end
	end
end

-- 玩家领取奖励
function ValentinesDay2015_ConcentricLock_RewardItem(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断玩家今天是否领取过奖励
	if not ValentinesDay2015_ConcentricLock_Complete() then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	-- 判断玩家今天是否完成过任务
	if not Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_ConcentricLock_Cont["CompleteData"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_ConcentricLock_Cont["BagSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end
	
	-- 掩码记录
	Task_SetStatistic(nEvent,nType,tValentinesDay2015_ConcentricLock_Cont["RewardData"],1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	-- 获取奖励
	FestivalGeneralPackage_GetGift(tValentinesDay2015_ConcentricLock_Cont["FestivalId"],tValentinesDay2015_ConcentricLock_Cont["LogId"])
	Item_AddItem(tValentinesDay2015_ConcentricLock_Cont["RewardItem"])
	Sys_SaveActionFestivalLog(tValentinesDay2015_ConcentricLock_Log["RewardLog"])
	User_EffectAdd("self",tValentinesDay2015_ConcentricLock_Cont["Effect"])
	LinkNpcGossipFunc_New(nNpcId,"5-4")
end

-- 物品使用
function ValentinesDay2015_ConcentricLock_UseItem(nItemId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text["BeOverdue"])
		end
		
		return
	end
	
	-- 判断玩家今天是否领取过奖励
	if not ValentinesDay2015_ConcentricLock_Complete() then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text["Excess"])
		end
		
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	-- 判断是否接任务
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text["NextDay"])
		end
		
		return
	end
	
	-- 判断是否完成任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_ConcentricLock_Item[nItemId]["CompleteData"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text["ExtraProps"])
		end
		
		return
	end
	
	-- 玩家不按照步骤，先去扔钥匙时拒绝的提示
	if not Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Item[nItemId]["AcceptData"]) then
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text["Step"])
		return
	end
	
	-- 判断玩家所在地图
	local nMapId = tValentinesDay2015_ConcentricLock_Item[nItemId]["MapId"]
	local nUserMapId = Get_UserMapId()
	if nUserMapId ~= nMapId then
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text[nItemId]["NoPosition"],string.format("ValentinesDay2015_ConcentricLock_Navigat</N>%d",nItemId))
		return
	end
	
	-- 判断玩家坐标
	local nMaxCellX = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellX"] + tValentinesDay2015_ConcentricLock_Cont["Interval"]
	local nMinCellX = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellX"] - tValentinesDay2015_ConcentricLock_Cont["Interval"]
	local nMaxCellY = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellY"] + tValentinesDay2015_ConcentricLock_Cont["Interval"]
	local nMinCellY = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellY"] - tValentinesDay2015_ConcentricLock_Cont["Interval"]

	local nUserCellX = Get_UserPositionX()
	local nUserCellY = Get_UserPositionY()
	
	if nUserCellX < nMinCellX or nUserCellX > nMaxCellX then
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text[nItemId]["NoPosition"],string.format("ValentinesDay2015_ConcentricLock_Navigat</N>%d",nItemId))
		return
	end
	
	if nUserCellY < nMinCellY or nUserCellY > nMaxCellY then
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text[nItemId]["NoPosition"],string.format("ValentinesDay2015_ConcentricLock_Navigat</N>%d",nItemId))
		return
	end

	-- 读条
	local nSecs = tValentinesDay2015_ConcentricLock_Cont["Secs"]
	local sContent = tValentinesDay2015_ConcentricLock_Text[nItemId]["Content"]
	local nActionId = tValentinesDay2015_ConcentricLock_Cont["ActionId"]
	local sFunc = string.format("ValentinesDay2015_ConcentricLock_UseItemSuccess</N>%d",nItemId)
	
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end

-- 物品使用成功后
function ValentinesDay2015_ConcentricLock_UseItemSuccess(nItemId)
	if nItemId == nil or type(nItemId) ~= "number" then
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 掩码记录
		Task_SetStatistic(nEvent,nType,tValentinesDay2015_ConcentricLock_Item[nItemId]["CompleteData"],1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		
		-- 打log
		local sLog = tValentinesDay2015_ConcentricLock_Item[nItemId]["Log"]
		Sys_SaveActionFestivalLog(tValentinesDay2015_ConcentricLock_Log[sLog])
		
		User_EffectAdd("self",tValentinesDay2015_ConcentricLock_Item[nItemId]["CompleteEffect"])
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text[nItemId]["Complete"],string.format("ValentinesDay2015_ConcentricLock_NavigatNext</N>%d",nItemId))
	end
end

-- 导航
function ValentinesDay2015_ConcentricLock_Navigat(nItemId)
	if nItemId == nil or type(nItemId) ~= "number" then
		return
	end
	
	local nMapId = tValentinesDay2015_ConcentricLock_Item[nItemId]["MapId"]
	local nPosX = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellX"]
	local nPosY = tValentinesDay2015_ConcentricLock_Item[nItemId]["CellY"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)
end

-- 导航下个任务点
function ValentinesDay2015_ConcentricLock_NavigatNext(nItemId)
	if nItemId == nil or type(nItemId) ~= "number" then
		return
	end
	
	local nMapId = tValentinesDay2015_ConcentricLock_Item[nItemId]["NextMapId"]
	local nPosX = tValentinesDay2015_ConcentricLock_Item[nItemId]["NextCellX"]
	local nPosY = tValentinesDay2015_ConcentricLock_Item[nItemId]["NextCellY"]
	local nNpcId = tValentinesDay2015_ConcentricLock_Item[nItemId]["NextNpcId"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

-- 请指引我完成所有步骤。
function ValentinesDay2015_ConcentricLock_Guide(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
	
	-- 判断是否完成任务
	if not ValentinesDay2015_ConcentricLock_Complete() then
		return
	end

	-- 判断是否接受任务
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	if Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["AcceptData"]) then
		ValentinesDay2015_ConcentricLock_Navigat(tValentinesDay2015_ConcentricLock_Cont["LockItem"])
	elseif Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["ProcessData"]) then
		ValentinesDay2015_ConcentricLock_Navigat(tValentinesDay2015_ConcentricLock_Cont["KeyItem"])
	end
end

-- 陷阱触发提示
function ValentinesDay2015_ConcentricLock_Trap(nTrapId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		return
	end
	
	local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
	local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]

	if tValentinesDay2015_ConcentricLock_Trap[nTrapId] ~= nil and Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Trap[nTrapId]) then
		Sys_MsgBox(tValentinesDay2015_ConcentricLock_Text[nTrapId])
	end
	
	return
end

-- 将情人节NPC移到集中营
function ValentinesDay2015_ConcentricLock_MoveNpc()
	-- 检测时间是否是活动时间后
	if Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["BeforeActivityTime"]) then
		return
	elseif Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"]) then
		return
	end

	-- 活动过后将双龙城的情人节NPC移回集中营
	local nMapId = tValentinesDay2015_ConcentricLock_MoveNpc["MapId"]
	local nPosX = tValentinesDay2015_ConcentricLock_MoveNpc["PosX"]
	local nPosY = tValentinesDay2015_ConcentricLock_MoveNpc["PosY"]
	
	for i,v in pairs(tValentinesDay2015_ConcentricLock_MoveNpc["NpcId"]) do
		local nNpcId = v
		local nNpcMapId = Get_NpcMapID(nNpcId)
		
		if nNpcMapId ~= nMapId then
			Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
		end
	end
end

--------------------------------------NPC模块-------------------------------------------
-- NPC头像
tNpcFace[3390] = 123

-- 红娘娇燕燕
tNpcGossip[17276] = tNpcGossip[17276] or DefaultNpc:new{}
tNpcGossip[17276]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[17276]["Text1-1"] = {111,112,113}
tNpcGossip[17276]["Text111"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text111"]
tNpcGossip[17276]["Text112"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text112"]
tNpcGossip[17276]["Text113"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text113"]
tNpcGossip[17276]["tOption1-1"] = {1}
tNpcGossip[17276]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["BeforeActivityTime"])
end

-- 活动后对白
tNpcGossip[17276]["Text1-2"] = {121,122}
tNpcGossip[17276]["Text121"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text121"]
tNpcGossip[17276]["Text122"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text122"]
tNpcGossip[17276]["tOption1-2"] = {2}
tNpcGossip[17276]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"])
end

-- 活动中对白
tNpcGossip[17276]["Text1-3"] = {131,132,133}
tNpcGossip[17276]["Text131"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text131"]
tNpcGossip[17276]["Text132"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text132"]
tNpcGossip[17276]["Text133"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text133"]
tNpcGossip[17276]["tOption1-3"] = {3,4,5,6,1000,7}
tNpcGossip[17276]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_ConcentricLock_Cont["ActivityTime"])
end

-- 玩家等级不足
tNpcGossip[17276]["Text3-1"] = {311,312}
tNpcGossip[17276]["Text311"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text311"]
tNpcGossip[17276]["Text312"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text312"]
tNpcGossip[17276]["tOption3-1"] = {9}

-- 玩家选1、失败、当日已完成该任务
tNpcGossip[17276]["Text3-2"] = {321}
tNpcGossip[17276]["Text321"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text321"]
tNpcGossip[17276]["tOption3-2"] = {10}

-- 玩家选1、失败、玩家处于异性组队状态
tNpcGossip[17276]["Text3-3"] = {331,332}
tNpcGossip[17276]["Text331"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text331"]
tNpcGossip[17276]["Text332"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text332"]
tNpcGossip[17276]["tOption3-3"] = {11}

-- 玩家选1、失败、玩家背包满
tNpcGossip[17276]["Text3-4"] = {341}
tNpcGossip[17276]["Text341"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text341"]
tNpcGossip[17276]["tOption3-4"] = {12}

-- 玩家选1、成功、给玩家道具、并导航到第一座桥
tNpcGossip[17276]["Text3-5"] = {351,352,353}
tNpcGossip[17276]["Text351"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text351"]
tNpcGossip[17276]["Text352"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text352"]
tNpcGossip[17276]["Text353"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text353"]
tNpcGossip[17276]["tOption3-5"] = {18}

-- 玩家选1、补领失败、玩家已完成任务提醒领取奖励
tNpcGossip[17276]["Text4-1"] = {411}
tNpcGossip[17276]["Text411"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text411"]
tNpcGossip[17276]["tOption4-1"] = {14}

-- 玩家选1、补领失败、玩家背包满
tNpcGossip[17276]["Text4-2"] = {421}
tNpcGossip[17276]["Text421"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text421"]
tNpcGossip[17276]["tOption4-2"] = {10}

-- 玩家选1、补领失败、玩家背包满
tNpcGossip[17276]["Text4-3"] = {431}
tNpcGossip[17276]["Text431"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text431"]
tNpcGossip[17276]["tOption4-3"] = {11}

-- 玩家选1、补领成功
tNpcGossip[17276]["Text4-4"] = {441,442,443}
tNpcGossip[17276]["Text441"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text441"]
tNpcGossip[17276]["Text442"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text442"]
tNpcGossip[17276]["Text443"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text443"]
tNpcGossip[17276]["tOption4-4"] = {13}

-- 玩家选2、失败、已领取当天奖励
tNpcGossip[17276]["Text5-1"] = {511}
tNpcGossip[17276]["Text511"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text511"]
tNpcGossip[17276]["tOption5-1"] = {15}

-- 玩家选2、失败、玩家未完该活动
tNpcGossip[17276]["Text5-2"] = {521}
tNpcGossip[17276]["Text521"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text521"]
tNpcGossip[17276]["tOption5-2"] = {10}

-- 玩家选4、失败、背包满
tNpcGossip[17276]["Text5-3"] = {531}
tNpcGossip[17276]["Text531"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text531"]
tNpcGossip[17276]["tOption5-3"] = {10}

-- 玩家选2、成功、领取活动奖励
tNpcGossip[17276]["Text5-4"] = {541}
tNpcGossip[17276]["Text541"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text541"]
tNpcGossip[17276]["tOption5-4"] = {16}

-- 玩家选3、活动介绍
tNpcGossip[17276]["Text6-1"] = {611,612,613,614}
tNpcGossip[17276]["Text611"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text611"]
tNpcGossip[17276]["Text612"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text612"]
tNpcGossip[17276]["Text613"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text613"]
tNpcGossip[17276]["Text614"] = tValentinesDay2015_ConcentricLock_Text[17276]["Text614"]
tNpcGossip[17276]["tOption6-1"] = {17}

-- 选项
tNpcGossip[17276]["Option1"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option1"]
tNpcGossip[17276]["Option2"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option2"]

tNpcGossip[17276]["Option3"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option3"]
tNpcGossip[17276]["OptionFunc3"] = "ValentinesDay2015_ConcentricLock_SingleCondit</N>17276"
tNpcGossip[17276]["OptionChkFunc3"] = function ()
	-- 判断玩家今天是否完成过任务
	if ValentinesDay2015_ConcentricLock_Complete() then
		local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
		local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
		
		if Task_ChkStcValue(nEvent,nType,"==",0) then
			return true
		end
	end
	
	return false
end

tNpcGossip[17276]["Option4"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option4"]
tNpcGossip[17276]["OptionFunc4"]="ValentinesDay2015_ConcentricLock_Replacement</N>17276"
tNpcGossip[17276]["OptionChkFunc4"] = function ()
	-- 判断玩家今天是否完成过任务
	if ValentinesDay2015_ConcentricLock_Complete() then
		local nEvent = tValentinesDay2015_ConcentricLock_Cont["StcEvent"]
		local nType = tValentinesDay2015_ConcentricLock_Cont["StcType"]
		
		if Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["AcceptData"]) or
			Task_ChkStcValue(nEvent,nType,"==",tValentinesDay2015_ConcentricLock_Cont["ProcessData"]) then
			return true
		end
	end
	
	return false
end

tNpcGossip[17276]["Option5"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option5"]
tNpcGossip[17276]["OptionFunc5"]="ValentinesDay2015_ConcentricLock_RewardItem</N>17276"

tNpcGossip[17276]["Option6"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option6"]
tNpcGossip[17276]["OptionPoint6"]="6"

tNpcGossip[17276]["Option7"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option7"]
tNpcGossip[17276]["Option9"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option9"]
tNpcGossip[17276]["Option10"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option10"]
tNpcGossip[17276]["Option11"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option11"]
tNpcGossip[17276]["Option12"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option12"]
tNpcGossip[17276]["Option13"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option13"]
tNpcGossip[17276]["OptionFunc13"]="ValentinesDay2015_ConcentricLock_Guide</N>17276"

tNpcGossip[17276]["Option14"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option14"]
tNpcGossip[17276]["Option15"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option15"]
tNpcGossip[17276]["Option16"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option16"]
tNpcGossip[17276]["Option17"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option17"]
tNpcGossip[17276]["Option18"] = tValentinesDay2015_ConcentricLock_Text[17276]["Option18"]
tNpcGossip[17276]["OptionFunc18"]="ValentinesDay2015_ConcentricLock_Guide</N>17276"

--------------------------------------物品模块-------------------------------------------
-- 同心锁
tItem[3005388] = tItem[3005388] or {}
tItem[3005388]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_ConcentricLock_UseItem(nItemId)
end

-- 同心钥
tItem[3005389] = tItem[3005389] or {}
tItem[3005389]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_ConcentricLock_UseItem(nItemId)
end

--------------------------------------陷阱触发-------------------------------------------

tTrap[1213] = tTrap[1213] or {}
tTrap[1213]["Function"] = function(nTrapId,nTrapType)
	if nTrapId == tValentinesDay2015_ConcentricLock_Cont["BiyiBirds"] or nTrapId == tValentinesDay2015_ConcentricLock_Cont["BiyiBirdsOther"] then
		ValentinesDay2015_BiyiBirds_Trap(nTrapId)
	else
		ValentinesDay2015_ConcentricLock_Trap(nTrapId)
	end
end

-- 时间自检触发
tSystem_Prompet_Func = tSystem_Prompet_Func or {}
table.insert(tSystem_Prompet_Func,ValentinesDay2015_ConcentricLock_MoveNpc)