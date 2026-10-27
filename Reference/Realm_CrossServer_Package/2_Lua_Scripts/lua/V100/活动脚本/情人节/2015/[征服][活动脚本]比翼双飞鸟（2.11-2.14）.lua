------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]比翼双飞鸟（2.11-2.14）
--Purpose:		2015年情人节比翼双飞鸟（2.11-2.14）
--Creator: 		郑鋆
--Created:		2014/11/28
------------------------------------------------------------------------------------

-- 命名前缀
-- ValentinesDay2015_BiyiBirds

-- 掩码说明
-- stc掩码 131 59
-- =100 表示接受任务
-- =200 表示完成任务
-- =300 表示领取过奖励

-- logID 10002399

-- 常量表配置
local tValentinesDay2015_BiyiBirds_Cont = {}
	-- 活动时间
	tValentinesDay2015_BiyiBirds_Cont["ActivityTime"] = "2015-02-11 00:00 2015-02-14 23:59"
	tValentinesDay2015_BiyiBirds_Cont["BeforeActivityTime"] = "2014-02-11 00:00 2015-02-10 23:59"

	-- 玩家等级要求
	tValentinesDay2015_BiyiBirds_Cont["Metempsychosis"] = 0
	tValentinesDay2015_BiyiBirds_Cont["Level"] = 80
	
	-- 掩码
	tValentinesDay2015_BiyiBirds_Cont["StcEvent"] = 131
	tValentinesDay2015_BiyiBirds_Cont["StcType"] = 59
	tValentinesDay2015_BiyiBirds_Cont["AcceptData"] = 100
	tValentinesDay2015_BiyiBirds_Cont["CompleteData"] = 200
	tValentinesDay2015_BiyiBirds_Cont["RewardData"] = 300
	
	-- 相关物品
	tValentinesDay2015_BiyiBirds_Cont["ItemOne"] = 3005441
	tValentinesDay2015_BiyiBirds_Cont["ItemTwo"] = 3005442
	tValentinesDay2015_BiyiBirds_Cont["ItemThree"] = 3005443
	tValentinesDay2015_BiyiBirds_Cont["ItemFour"] = 3005444
	
	-- 放飞点
	tValentinesDay2015_BiyiBirds_Cont["MapId"] = 1002
	tValentinesDay2015_BiyiBirds_Cont["CellX"] = 248
	tValentinesDay2015_BiyiBirds_Cont["CellY"] = 292
	tValentinesDay2015_BiyiBirds_Cont["Interval"] = 5
	
	-- NPC坐标
	tValentinesDay2015_BiyiBirds_Cont["NpcCellX"] = 286
	tValentinesDay2015_BiyiBirds_Cont["NpcCellY"] = 385
	tValentinesDay2015_BiyiBirds_Cont["NpcId"] = 17302
	
	-- 怪物点
	tValentinesDay2015_BiyiBirds_Cont["MonsterCellX"] = 337
	tValentinesDay2015_BiyiBirds_Cont["MonsterCellY"] = 420
	
	-- 奖励物品
	tValentinesDay2015_BiyiBirds_Cont["RewardItem"] = 3005410
	tValentinesDay2015_BiyiBirds_Cont["FestivalId"] = 3353
	tValentinesDay2015_BiyiBirds_Cont["LogId"] = 10002399
	
	tValentinesDay2015_BiyiBirds_Cont["ItemSpace"] = 1
	tValentinesDay2015_BiyiBirds_Cont["RewardSpace"] = 2
	
	-- 比翼双飞鸟活动的陷阱ID
	tValentinesDay2015_BiyiBirds_Cont["BiyiBirds"] = 992310

-- 物品使用表
local tValentinesDay2015_BiyiBirds_Item = {}
	tValentinesDay2015_BiyiBirds_Item[3005441] = {}
	tValentinesDay2015_BiyiBirds_Item[3005441]["RewardItem"] = 3005443
	tValentinesDay2015_BiyiBirds_Item[3005441]["Key"] = 1
	tValentinesDay2015_BiyiBirds_Item[3005441]["IsBit"] = false

	tValentinesDay2015_BiyiBirds_Item[3005442] = {}
	tValentinesDay2015_BiyiBirds_Item[3005442]["RewardItem"] = 3005444
	tValentinesDay2015_BiyiBirds_Item[3005442]["Key"] = 1
	tValentinesDay2015_BiyiBirds_Item[3005442]["IsBit"] = true

	tValentinesDay2015_BiyiBirds_Item[3005443] = {}
	tValentinesDay2015_BiyiBirds_Item[3005443]["ChkItem"] = 3005444
	
	tValentinesDay2015_BiyiBirds_Item[3005444] = {}
	tValentinesDay2015_BiyiBirds_Item[3005444]["ChkItem"] = 3005443
	
-- log表
local tValentinesDay2015_BiyiBirds_Log = {}
	tValentinesDay2015_BiyiBirds_Log["Log"] = "0,0,%d,%d,10002399,3,%d,%d"
	tValentinesDay2015_BiyiBirds_Log["AcceptLog"] = "0,0,0,0,10002399,1[1],0,0"
	tValentinesDay2015_BiyiBirds_Log["ProcessLog"] = "0,0,0,0,10002399,1[2],0,0"
	tValentinesDay2015_BiyiBirds_Log["CompleteLog"] = "0,0,3005443[3005444],1[1],10002399,1[3],0,0"
	tValentinesDay2015_BiyiBirds_Log["RewardLog"] = "0,0,0,0,10002399,2,3005410,1"

--------------------------------------逻辑部分-----------------------------------------
-- 所有函数都必须判断的
function ValentinesDay2015_BiyiBirds_MustJudge()
	-- 判断活动时间
	if Sys_ChkFullTime(tValentinesDay2015_BiyiBirds_Cont["ActivityTime"]) then
		return true
	else
		return false
	end
end

-- 判断玩家是否领取过奖励
function ValentinesDay2015_BiyiBirds_Complete()
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]

	-- 判断是否领取过奖励
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["RewardData"]) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			
			return true
		end
		
		return false
	else
		return true
	end
end

-- 玩家选1、	姑娘莫急，交给在下条件判断	
function ValentinesDay2015_BiyiBirds_SingleCondit(nNpcId)
	-- 判断活动时间
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tValentinesDay2015_BiyiBirds_Cont["Level"],tValentinesDay2015_BiyiBirds_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 判断玩家是否领取过奖励
	if not ValentinesDay2015_BiyiBirds_Complete() then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	-- 判断玩家是否已完成任务但还没有领奖
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]
	
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["CompleteData"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	-- 判断玩家是否已经接过任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["AcceptData"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return
	end
	
	-- 掩码设值
	Task_SetStatistic(nEvent,nType,tValentinesDay2015_BiyiBirds_Cont["AcceptData"],1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	Sys_SaveActionFestivalLog(tValentinesDay2015_BiyiBirds_Log["AcceptLog"])
	LinkNpcGossipFunc_New(nNpcId,"3-4")
end

-- 玩家领取奖励条件判断	
function ValentinesDay2015_BiyiBirds_RewardItem(nNpcId)
	-- 判断活动时间
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	-- 判断玩家是否领取过奖励
	if not ValentinesDay2015_BiyiBirds_Complete() then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end

	-- 判断玩家是否完成任务
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]
	
	if not Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["CompleteData"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end

	-- 判断玩家背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_BiyiBirds_Cont["RewardSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end

	-- 掩码设值
	Task_SetStatistic(nEvent,nType,tValentinesDay2015_BiyiBirds_Cont["RewardData"],1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	-- 领取奖励
	FestivalGeneralPackage_GetGift(tValentinesDay2015_BiyiBirds_Cont["FestivalId"],tValentinesDay2015_BiyiBirds_Cont["LogId"])
	Item_AddItem(tValentinesDay2015_BiyiBirds_Cont["RewardItem"])
	Sys_SaveActionFestivalLog(tValentinesDay2015_BiyiBirds_Log["RewardLog"])
	LinkNpcGossipFunc_New(nNpcId,"4-4")
	
	-- 删除多余任务物品
	Item_DelAllItemByType(tValentinesDay2015_BiyiBirds_Cont["ItemOne"])
	Item_DelAllItemByType(tValentinesDay2015_BiyiBirds_Cont["ItemTwo"])
	Item_DelAllItemByType(tValentinesDay2015_BiyiBirds_Cont["ItemThree"])
	Item_DelAllItemByType(tValentinesDay2015_BiyiBirds_Cont["ItemFour"])
end

-- 使用道具
function ValentinesDay2015_BiyiBirds_UseItemBox(nItemId)
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["BeOverdue"])
		end
		
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
		local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]

		-- 判断是否有完成任务
		if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["CompleteData"]) then
			-- 判断是否隔天
			if not Task_StcInterval(nEvent,nType,1,4) then
				Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["HaveComplete"])
			end
			
			return
		end
		
		-- 判断是否有接任务
		if Task_ChkStcValue(nEvent,nType,"==",0) then
			return
		end
		
		-- 获得的物品ID
		local nRewardItem = tValentinesDay2015_BiyiBirds_Item[nItemId]["RewardItem"]
		
		if not Item_ChkItem(nRewardItem) then
			-- 判断是否开启过一次
			local nValue = Get_UserStatisticValue(nEvent,nType)
			-- 取掩码个位数
			local nBitNum = nValue%10
			-- 取十位数
			local nTenNum = math.floor((nValue/10))%10
			-- 取百位数
			local nHundredNum = math.floor(nValue/100)
			
			local nKey = tValentinesDay2015_BiyiBirds_Item[nItemId]["Key"]
			local IsRewardItem = true
			local nIsKey = 0
			
			-- 取判断的值
			if tValentinesDay2015_BiyiBirds_Item[nItemId]["IsBit"] then
				nIsKey = nBitNum
			else
				nIsKey = nTenNum
			end
			
			if nIsKey < nKey then
				IsRewardItem = false
			end
			
			-- 给物品
			if IsRewardItem or Sys_Random(9,10) then
				Item_AddItem(nRewardItem)
				local str = string.format(tValentinesDay2015_BiyiBirds_Log["Log"],nItemId,1,nRewardItem,1)
				Sys_SaveActionFestivalLog(str)
				User_TalkChannel2005(tValentinesDay2015_BiyiBirds_Text[nItemId]["RewardItem"])
			else
				if tValentinesDay2015_BiyiBirds_Item[nItemId]["IsBit"] then
					nBitNum = 1
				else
					nTenNum = 1
				end
				
				nValue = nHundredNum*100 + nTenNum*10 + nBitNum
				-- 掩码设值
				Task_SetStatistic(nEvent,nType,nValue,1,0)
				Task_SetStcTimestamp(nEvent,nType,0,0)
				
				Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nItemId]["NoItem"])
				return
			end
		end
		
		-- 判断是否有两个笼子了
		if Item_ChkItem(tValentinesDay2015_BiyiBirds_Cont["ItemThree"]) and Item_ChkItem(tValentinesDay2015_BiyiBirds_Cont["ItemFour"]) then
			Sys_SaveActionFestivalLog(tValentinesDay2015_BiyiBirds_Log["ProcessLog"])
			Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["AllItem"],"ValentinesDay2015_BiyiBirds_Navigat")
			return
		end
	end
end

function ValentinesDay2015_BiyiBirds_UseItemCage(nItemId)
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["BeOverdue"])
		end
		
		return
	end
	
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]

	-- 判断是否有完成任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["CompleteData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nEvent,nType,1,4) then
			if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
				Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["HaveComplete"])
			end
		end
		
		return
	end
	
	-- 判断是否有接任务
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		end
		return
	end
	
	-- 判断是否有两个笼子
	local nOtherItem = tValentinesDay2015_BiyiBirds_Item[nItemId]["ChkItem"]
	if not (Item_ChkItem(nOtherItem) and Item_ChkItem(nItemId))then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["NotAllItem"])
		return
	end
	
	-- 判断玩家所在地图
	local nUserMapId = Get_UserMapId()
	
	if nUserMapId ~= tValentinesDay2015_BiyiBirds_Cont["MapId"] then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["UseItemNavigat"],"ValentinesDay2015_BiyiBirds_Navigat")
		return
	end
	
	-- 判断玩家坐标是否在放飞点附近
	local nMaxCellX = tValentinesDay2015_BiyiBirds_Cont["CellX"] + tValentinesDay2015_BiyiBirds_Cont["Interval"]
	local nMinCellX = tValentinesDay2015_BiyiBirds_Cont["CellX"] - tValentinesDay2015_BiyiBirds_Cont["Interval"]
	local nMaxCellY = tValentinesDay2015_BiyiBirds_Cont["CellY"] + tValentinesDay2015_BiyiBirds_Cont["Interval"]
	local nMinCellY = tValentinesDay2015_BiyiBirds_Cont["CellY"] - tValentinesDay2015_BiyiBirds_Cont["Interval"]
	
	local nUserCellX = Get_UserPositionX()
	local nUserCellY = Get_UserPositionY()
	
	if nUserCellX < nMinCellX or nUserCellX > nMaxCellX then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["UseItemNavigat"],"ValentinesDay2015_BiyiBirds_Navigat")
		return
	end
	
	if nUserCellY < nMinCellY or nUserCellY > nMaxCellY then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["UseItemNavigat"],"ValentinesDay2015_BiyiBirds_Navigat")
		return
	end
	
	-- 删除物品
	if Item_DelItem(nOtherItem) and Item_DelItem(nItemId) then
		-- 掩码设值
		Task_SetStatistic(nEvent,nType,tValentinesDay2015_BiyiBirds_Cont["CompleteData"],1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		Sys_SaveActionFestivalLog(tValentinesDay2015_BiyiBirds_Log["CompleteLog"])
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text["Complete"],"ValentinesDay2015_BiyiBirds_NavigatNpc")
		User_EffectAdd("self","pie")
	end
end

-- 导航到放飞点
function ValentinesDay2015_BiyiBirds_Navigat()
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		return
	end
	
	local nMapId = tValentinesDay2015_BiyiBirds_Cont["MapId"]
	local nPosX = tValentinesDay2015_BiyiBirds_Cont["CellX"]
	local nPosY = tValentinesDay2015_BiyiBirds_Cont["CellY"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)
end

-- 导航到NPC
function ValentinesDay2015_BiyiBirds_NavigatNpc()
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		return
	end
	
	local nMapId = tValentinesDay2015_BiyiBirds_Cont["MapId"]
	local nPosX = tValentinesDay2015_BiyiBirds_Cont["NpcCellX"]
	local nPosY = tValentinesDay2015_BiyiBirds_Cont["NpcCellY"]
	local nNpcId = tValentinesDay2015_BiyiBirds_Cont["NpcId"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

-- 导航到怪物点
function ValentinesDay2015_BiyiBirds_NavigatMonster()
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		return
	end
	
	local nMapId = tValentinesDay2015_BiyiBirds_Cont["MapId"]
	local nPosX = tValentinesDay2015_BiyiBirds_Cont["MonsterCellX"]
	local nPosY = tValentinesDay2015_BiyiBirds_Cont["MonsterCellY"]

	Sys_GotoSomeWhere(nPosX,nPosY,nMapId)
end

-- 陷阱提示
function ValentinesDay2015_BiyiBirds_Trap(nTrapId)
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		return
	end
	
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]
	
	-- 判断是否有接任务
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		return
	end
	
	-- 判断是否是否放飞点的陷阱
	if nTrapId ~= tValentinesDay2015_BiyiBirds_Cont["BiyiBirds"] then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nTrapId])
		return
	end
	
	-- 判断玩家身上是否有比翼之笼和双飞之笼
	local nItemThree = tValentinesDay2015_BiyiBirds_Cont["ItemThree"]
	local nItemFour = tValentinesDay2015_BiyiBirds_Cont["ItemFour"]
	
	if Item_ChkItem(nItemThree) and Item_ChkItem(nItemFour) then
		Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nTrapId][1])
	-- else
		-- Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nTrapId][2])
	end
end

-- 怪物掉落
function ValentinesDay2015_BiyiBirds_KillMonster()
	-- 判断是否在活动时间内
	if not ValentinesDay2015_BiyiBirds_MustJudge() then
		return
	end
	
	local nEvent = tValentinesDay2015_BiyiBirds_Cont["StcEvent"]
	local nType = tValentinesDay2015_BiyiBirds_Cont["StcType"]

	-- 判断是否有完成任务
	if Task_ChkStcValue(nEvent,nType,">=",tValentinesDay2015_BiyiBirds_Cont["CompleteData"]) then
		-- 判断是否隔天
		-- if not Task_StcInterval(nEvent,nType,1,4) then
			-- return
		-- end
		return
	end
	
	-- 判断是否有接任务
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_BiyiBirds_Cont["ItemSpace"]) then
		User_TalkChannel2005(tValentinesDay2015_BiyiBirds_Text["BagFull"])
		return
	end
	
	local nItemOne = tValentinesDay2015_BiyiBirds_Cont["ItemOne"]
	local nItemTwo = tValentinesDay2015_BiyiBirds_Cont["ItemTwo"]
	local nItemThree = tValentinesDay2015_BiyiBirds_Cont["ItemThree"]
	local nItemFour = tValentinesDay2015_BiyiBirds_Cont["ItemFour"]
	
	-- 判断是否开启过一次
	local nValue = Get_UserStatisticValue(nEvent,nType)
	-- 取掩码个位数
	local nBitNum = nValue%10
	-- 取十位数
	local nTenNum = math.floor((nValue/10))%10
	-- 取百位数
	local nHundredNum = math.floor(nValue/100)

	-- 掉落比翼之箱
	if not (Item_ChkItem(nItemOne) or Item_ChkItem(nItemThree)) then
		local nKey = tValentinesDay2015_BiyiBirds_Item[nItemOne]["Key"]
		
		if (nTenNum > nKey) or Sys_Random(4,10) then
			Item_AddItem(nItemOne)
			local str = string.format(tValentinesDay2015_BiyiBirds_Log["Log"],0,0,nItemOne,1)
			Sys_SaveActionFestivalLog(str)
			Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nItemOne]["Reward"])

			return
		end
	end
	
	-- 掉落双飞之箱
	if not (Item_ChkItem(nItemTwo) or Item_ChkItem(nItemFour)) then
		local nKey = tValentinesDay2015_BiyiBirds_Item[nItemTwo]["Key"]

		if (nBitNum > nKey) or Sys_Random(4,5) then
			Item_AddItem(nItemTwo)
			local str = string.format(tValentinesDay2015_BiyiBirds_Log["Log"],0,0,nItemTwo,1)
			Sys_SaveActionFestivalLog(str)
			Sys_MsgBox(tValentinesDay2015_BiyiBirds_Text[nItemTwo]["Reward"])
			return
		end
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 苏巧儿
tNpcFace[3350] = 122
tNpcGossip[17302] = tNpcGossip[17302] or DefaultNpc:new{}
tNpcGossip[17302]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[17302]["Text1-1"] = {111,112,113}
tNpcGossip[17302]["Text111"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text111"]
tNpcGossip[17302]["Text112"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text112"]
tNpcGossip[17302]["Text113"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text113"]
tNpcGossip[17302]["tOption1-1"] = {1}
tNpcGossip[17302]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_BiyiBirds_Cont["BeforeActivityTime"])
end

-- 活动后对白
tNpcGossip[17302]["Text1-2"] = {121,122}
tNpcGossip[17302]["Text121"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text121"]
tNpcGossip[17302]["Text122"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text122"]
tNpcGossip[17302]["tOption1-2"] = {2}
tNpcGossip[17302]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tValentinesDay2015_BiyiBirds_Cont["ActivityTime"])
end

-- 活动中对白
tNpcGossip[17302]["Text1-3"] = {131,132,133,134}
tNpcGossip[17302]["Text131"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text131"]
tNpcGossip[17302]["Text132"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text132"]
tNpcGossip[17302]["Text133"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text133"]
tNpcGossip[17302]["Text134"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text134"]
tNpcGossip[17302]["tOption1-3"] = {3,1000,4,5,6}
tNpcGossip[17302]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_BiyiBirds_Cont["ActivityTime"])
end

-- 接1?姑娘莫急，交给在下?等级不够
tNpcGossip[17302]["Text3-1"] = {311,312}
tNpcGossip[17302]["Text311"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text311"]
tNpcGossip[17302]["Text312"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text312"]
tNpcGossip[17302]["tOption3-1"] = {7}

-- 接1?姑娘莫急，交给在下?今天已完成过
tNpcGossip[17302]["Text3-2"] = {321,322}
tNpcGossip[17302]["Text321"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text321"]
tNpcGossip[17302]["Text322"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text322"]
tNpcGossip[17302]["tOption3-2"] = {8}

-- 接1?姑娘莫急，交给在下?今天已完成并未领取奖励
tNpcGossip[17302]["Text3-3"] = {331}
tNpcGossip[17302]["Text331"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text331"]
tNpcGossip[17302]["tOption3-3"] = {9}

-- 接1?姑娘莫急，交给在下?成功
tNpcGossip[17302]["Text3-4"] = {341,342,343,344}
tNpcGossip[17302]["Text341"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text341"]
tNpcGossip[17302]["Text342"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text342"]
tNpcGossip[17302]["Text343"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text343"]
tNpcGossip[17302]["Text344"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text344"]
tNpcGossip[17302]["tOption3-4"] = {10}

-- 【接1、姑娘莫急、玩家接任务但未完成任务】
tNpcGossip[17302]["Text3-5"] = {351}
tNpcGossip[17302]["Text351"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text351"]
tNpcGossip[17302]["tOption3-5"] = {10}

-- 接2?领取奖励?已领取过
tNpcGossip[17302]["Text4-1"] = {411,412}
tNpcGossip[17302]["Text411"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text411"]
tNpcGossip[17302]["Text412"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text412"]
tNpcGossip[17302]["tOption4-1"] = {11}

-- 接2?领取奖励?任务未完成
tNpcGossip[17302]["Text4-2"] = {421,422}
tNpcGossip[17302]["Text421"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text421"]
tNpcGossip[17302]["Text422"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text422"]
tNpcGossip[17302]["tOption4-2"] = {12}

-- 接2?领取奖励?玩家背包满
tNpcGossip[17302]["Text4-3"] = {431}
tNpcGossip[17302]["Text431"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text431"]
tNpcGossip[17302]["tOption4-3"] = {13}

-- 接2?领取奖励?成功领取
tNpcGossip[17302]["Text4-4"] = {441,442}
tNpcGossip[17302]["Text441"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text441"]
tNpcGossip[17302]["Text442"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text442"]
tNpcGossip[17302]["tOption4-4"] = {11}

-- 接3?可否请姑娘详细一说
tNpcGossip[17302]["Text5-1"] = {511,512,513,514}
tNpcGossip[17302]["Text511"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text511"]
tNpcGossip[17302]["Text512"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text512"]
tNpcGossip[17302]["Text513"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text513"]
tNpcGossip[17302]["Text514"] = tValentinesDay2015_BiyiBirds_Text[17302]["Text514"]
tNpcGossip[17302]["tOption5-1"] = {14}

-- 选项
tNpcGossip[17302]["Option1"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option1"]
tNpcGossip[17302]["Option2"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option2"]

tNpcGossip[17302]["Option3"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option3"]
tNpcGossip[17302]["OptionFunc3"]="ValentinesDay2015_BiyiBirds_SingleCondit</N>17302"

tNpcGossip[17302]["Option4"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option4"]
tNpcGossip[17302]["OptionFunc4"]="ValentinesDay2015_BiyiBirds_RewardItem</N>17302"

tNpcGossip[17302]["Option5"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option5"]
tNpcGossip[17302]["OptionPoint5"]="5"

tNpcGossip[17302]["Option6"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option6"]
tNpcGossip[17302]["Option7"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option7"]
tNpcGossip[17302]["Option8"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option8"]
tNpcGossip[17302]["Option9"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option9"]
tNpcGossip[17302]["Option10"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option10"]
tNpcGossip[17302]["OptionFunc10"]="ValentinesDay2015_BiyiBirds_NavigatMonster"

tNpcGossip[17302]["Option11"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option11"]
tNpcGossip[17302]["Option12"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option12"]
tNpcGossip[17302]["Option13"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option13"]
tNpcGossip[17302]["Option14"] = tValentinesDay2015_BiyiBirds_Text[17302]["Option14"]

--------------------------------------物品模块-------------------------------------------
-- 比翼之箱
tItem[3005441] = tItem[3005441] or {}
tItem[3005441]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_BiyiBirds_UseItemBox(nItemId)
end

-- 双飞之箱
tItem[3005442] = tItem[3005442] or {}
tItem[3005442]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_BiyiBirds_UseItemBox(nItemId)
end

-- 比翼之笼
tItem[3005443] = tItem[3005443] or {}
tItem[3005443]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_BiyiBirds_UseItemCage(nItemId)
end

-- 双飞之笼
tItem[3005444] = tItem[3005444] or {}
tItem[3005444]["Function"] = function(nItemId,sItemName)
	ValentinesDay2015_BiyiBirds_UseItemCage(nItemId)
end

--------------------------------------怪物掉落-------------------------------------------
-- 第一片区
-- 1,叫天鸡,9593200
tMonster[1] = tMonster[1] or {}
tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
table.insert(tMonster[1]["tFunction"],ValentinesDay2015_BiyiBirds_KillMonster)

-- 2,斑鸠王,9593210
tMonster[2] = tMonster[2] or {}
tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
table.insert(tMonster[2]["tFunction"],ValentinesDay2015_BiyiBirds_KillMonster)

-- 3,罗罗鸟,9593220
tMonster[3] = tMonster[3] or {}
tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
table.insert(tMonster[3]["tFunction"],ValentinesDay2015_BiyiBirds_KillMonster)

-- 4,幽冥鬼斧王,9593230
tMonster[4] = tMonster[4] or {}
tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
table.insert(tMonster[4]["tFunction"],ValentinesDay2015_BiyiBirds_KillMonster)

-- 5,蹑空鬼斧王,9593240
tMonster[5] = tMonster[5] or {}
tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
table.insert(tMonster[5]["tFunction"],ValentinesDay2015_BiyiBirds_KillMonster)