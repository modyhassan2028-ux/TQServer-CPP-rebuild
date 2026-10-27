------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]VIP特权月线上活动
--Purpose:		2015暑期活动-VIP特权月线上活动
--Creator: 		郑鋆
--Created:		2015/4/17
------------------------------------------------------------------------------------
-- 命名规则
-- VipPrivilegeOnlineActive2015_

-- logID
-- 12000076 ~ 12000079

-- 掩码说明
-- 134,15 记录玩家是否领取度假村凭证
-- 134,16 记录玩家是否完成过躺着享受阳光浴动作（=1表示完成）
-- 134,17 记录玩家是否完成过潜水观看海底世界动作（=1表示完成）
-- 134,18 记录玩家是否完成过坐着与鱼群互动动作（=1表示完成）
-- 134,19 记录玩家完成水的亲密接触活动的动作次数及领取奖励(=1,表示完成1个动作，2,3 =10表示领取过奖励)
-- 134,20 记录玩家是否完成飞镖靶子活动及领取奖励(=1,表示完成，=10表示领取过奖励)
-- 134,21 记录玩家是否领取过啤酒和炸鸡(=1,表示领取过)
-- 134,22 记录非VIP玩家是否进入过度假村
-- 134,23 记录玩家今天领取了几个礼包

-- 常量表
local tVipPrivilegeOnlineActive2015_Constant = {}
	-- 活动时间
	tVipPrivilegeOnlineActive2015_Constant["BeforeActivityTime"] = "2015-03-17 00:00 2015-07-14 23:59"
	tVipPrivilegeOnlineActive2015_Constant["ActivityTime"] = "2015-07-15 00:00 2015-07-22 23:59"

	-- 玩家等级要求
	tVipPrivilegeOnlineActive2015_Constant["Metempsychosis"] = 0
	tVipPrivilegeOnlineActive2015_Constant["Level"] = 80

	-- 度假村门票
	tVipPrivilegeOnlineActive2015_Constant["ResortTickets"] = 3004103
	-- 啤酒和炸鸡
	tVipPrivilegeOnlineActive2015_Constant["Beer"] = 3004104
	
	-- 需要的背包空间
	tVipPrivilegeOnlineActive2015_Constant["ItemSpace"] = 1
	
	-- 动态存储表
	tVipPrivilegeOnlineActive2015_Constant["GlobalId"] = 50865
	tVipPrivilegeOnlineActive2015_Constant["MaxData"] = 20
	
	tVipPrivilegeOnlineActive2015_Constant["CompleteData"] = 3
	tVipPrivilegeOnlineActive2015_Constant["RewardData"] = 10
	
	-- 节日礼包ID
	tVipPrivilegeOnlineActive2015_Constant["RewardItem"] = {}
	tVipPrivilegeOnlineActive2015_Constant["RewardItem"][0] = 3003625
	tVipPrivilegeOnlineActive2015_Constant["RewardItem"][1] = 3003626
	tVipPrivilegeOnlineActive2015_Constant["RewardItem"][2] = 3003627
	
-- log
local tVipPrivilegeOnlineActive2015_Log = {}
	tVipPrivilegeOnlineActive2015_Log["RewardItem"] = "0,0,0,0,12000076,2,%d,1"

-- stc掩码表
local tVipPrivilegeOnlineActive2015_Stc = {}
	tVipPrivilegeOnlineActive2015_Stc["EventType"] = 134
	
	tVipPrivilegeOnlineActive2015_Stc[1] = {}
	tVipPrivilegeOnlineActive2015_Stc[2] = {}
	tVipPrivilegeOnlineActive2015_Stc[3] = {}
	tVipPrivilegeOnlineActive2015_Stc[4] = {}
	tVipPrivilegeOnlineActive2015_Stc[5] = {}
	tVipPrivilegeOnlineActive2015_Stc[6] = {}
	tVipPrivilegeOnlineActive2015_Stc[7] = {}
	tVipPrivilegeOnlineActive2015_Stc[8] = {}
	tVipPrivilegeOnlineActive2015_Stc[9] = {}
	tVipPrivilegeOnlineActive2015_Stc[1]["DataType"] = 15
	tVipPrivilegeOnlineActive2015_Stc[2]["DataType"] = 16
	tVipPrivilegeOnlineActive2015_Stc[3]["DataType"] = 17
	tVipPrivilegeOnlineActive2015_Stc[4]["DataType"] = 18
	tVipPrivilegeOnlineActive2015_Stc[5]["DataType"] = 19
	tVipPrivilegeOnlineActive2015_Stc[6]["DataType"] = 20
	tVipPrivilegeOnlineActive2015_Stc[7]["DataType"] = 21
	tVipPrivilegeOnlineActive2015_Stc[8]["DataType"] = 22
	tVipPrivilegeOnlineActive2015_Stc[9]["DataType"] = 23

local tVipPrivilegeOnlineActive2015_MapInfo = {}
	-- 度假村
	tVipPrivilegeOnlineActive2015_MapInfo[1] = {}
	tVipPrivilegeOnlineActive2015_MapInfo[1]["MapId"] = 3938
	tVipPrivilegeOnlineActive2015_MapInfo[1]["CellX"] = 172
	tVipPrivilegeOnlineActive2015_MapInfo[1]["CellY"] = 147
	tVipPrivilegeOnlineActive2015_MapInfo[1]["Range"] = 3
	tVipPrivilegeOnlineActive2015_MapInfo[1]["Time"] = "2015-07-15 00:00 2015-07-22 23:59"
	
	-- 双龙城
	tVipPrivilegeOnlineActive2015_MapInfo[2] = {}
	tVipPrivilegeOnlineActive2015_MapInfo[2]["MapId"] = 1002
	tVipPrivilegeOnlineActive2015_MapInfo[2]["CellX"] = 302
	tVipPrivilegeOnlineActive2015_MapInfo[2]["CellY"] = 371
	tVipPrivilegeOnlineActive2015_MapInfo[2]["Range"] = 3
	tVipPrivilegeOnlineActive2015_MapInfo[2]["Time"] = "2015-03-15 00:00 2015-09-22 23:59"

-- 自动寻路
local tVipPrivilegeOnlineActive2015_Auto = {}
	tVipPrivilegeOnlineActive2015_Auto[1] = {}
	tVipPrivilegeOnlineActive2015_Auto[1]["MapId"] = 3938
	tVipPrivilegeOnlineActive2015_Auto[1]["CellX"] = 290
	tVipPrivilegeOnlineActive2015_Auto[1]["CellY"] = 278
	tVipPrivilegeOnlineActive2015_Auto[1]["NpcId"] = 0
	
	tVipPrivilegeOnlineActive2015_Auto[2] = {}
	tVipPrivilegeOnlineActive2015_Auto[2]["MapId"] = 3938
	tVipPrivilegeOnlineActive2015_Auto[2]["CellX"] = 254
	tVipPrivilegeOnlineActive2015_Auto[2]["CellY"] = 282
	tVipPrivilegeOnlineActive2015_Auto[2]["NpcId"] = 0

	tVipPrivilegeOnlineActive2015_Auto[3] = {}
	tVipPrivilegeOnlineActive2015_Auto[3]["MapId"] = 3938
	tVipPrivilegeOnlineActive2015_Auto[3]["CellX"] = 169
	tVipPrivilegeOnlineActive2015_Auto[3]["CellY"] = 153
	tVipPrivilegeOnlineActive2015_Auto[3]["NpcId"] = 18465
	
	tVipPrivilegeOnlineActive2015_Auto[4] = {}
	tVipPrivilegeOnlineActive2015_Auto[4]["MapId"] = 1002
	tVipPrivilegeOnlineActive2015_Auto[4]["CellX"] = 300
	tVipPrivilegeOnlineActive2015_Auto[4]["CellY"] = 366
	tVipPrivilegeOnlineActive2015_Auto[4]["NpcId"] = 18464

-- VIP等级对应的奖励	
local tVipPrivilegeOnlineActive2015_Vip = {}
	tVipPrivilegeOnlineActive2015_Vip[1] = {}
	tVipPrivilegeOnlineActive2015_Vip[1]["MinVipLev"] = 1
	tVipPrivilegeOnlineActive2015_Vip[1]["MaxVipLev"] = 2
	tVipPrivilegeOnlineActive2015_Vip[1]["ItemNum"] = 2
	tVipPrivilegeOnlineActive2015_Vip[1]["AddItemNum"] = {}
	tVipPrivilegeOnlineActive2015_Vip[1]["AddItemNum"][5] = 1
	tVipPrivilegeOnlineActive2015_Vip[1]["AddItemNum"][6] = 1
	
	tVipPrivilegeOnlineActive2015_Vip[2] = {}
	tVipPrivilegeOnlineActive2015_Vip[2]["MinVipLev"] = 3
	tVipPrivilegeOnlineActive2015_Vip[2]["MaxVipLev"] = 4
	tVipPrivilegeOnlineActive2015_Vip[2]["ItemNum"] = 3
	tVipPrivilegeOnlineActive2015_Vip[2]["AddItemNum"] = {}
	tVipPrivilegeOnlineActive2015_Vip[2]["AddItemNum"][5] = 1
	tVipPrivilegeOnlineActive2015_Vip[2]["AddItemNum"][6] = 2
	
	tVipPrivilegeOnlineActive2015_Vip[3] = {}
	tVipPrivilegeOnlineActive2015_Vip[3]["MinVipLev"] = 5
	tVipPrivilegeOnlineActive2015_Vip[3]["ItemNum"] = 4
	tVipPrivilegeOnlineActive2015_Vip[3]["AddItemNum"] = {}
	tVipPrivilegeOnlineActive2015_Vip[3]["AddItemNum"][5] = 1
	tVipPrivilegeOnlineActive2015_Vip[3]["AddItemNum"][6] = 3

-- 奖励配置
local tVipPrivilegeOnlineActive2015_RewardItem = {}
	tVipPrivilegeOnlineActive2015_RewardItem[5] = {}
	tVipPrivilegeOnlineActive2015_RewardItem[5]["CompleteData"] = 3
	tVipPrivilegeOnlineActive2015_RewardItem[5]["NoComplete"] = "2-3"
	tVipPrivilegeOnlineActive2015_RewardItem[5]["Reward"] = "2-4"
	tVipPrivilegeOnlineActive2015_RewardItem[5]["Log"] = "0,0,0,0,12000077,2,%d,%d"

	tVipPrivilegeOnlineActive2015_RewardItem[6] = {}
	tVipPrivilegeOnlineActive2015_RewardItem[6]["CompleteData"] = 1
	tVipPrivilegeOnlineActive2015_RewardItem[6]["NoComplete"] = "3-1"
	tVipPrivilegeOnlineActive2015_RewardItem[6]["Reward"] = "3-3"
	tVipPrivilegeOnlineActive2015_RewardItem[6]["Log"] = "0,0,0,0,12000078,2,%d,%d"

	tVipPrivilegeOnlineActive2015_RewardItem[3006618] = {}
	tVipPrivilegeOnlineActive2015_RewardItem[3006618]["Cultivation"] = 15
	tVipPrivilegeOnlineActive2015_RewardItem[3006618]["CultivationLog"] = "0,0,3006618,1,12000078,2,6,15"
	tVipPrivilegeOnlineActive2015_RewardItem[3006618]["Exp"] = 30
	tVipPrivilegeOnlineActive2015_RewardItem[3006618]["ExpLog"] = "0,0,3006618,1,12000078,2,4,30"
	
-- 水的亲密接触活动
local tVipPrivilegeOnlineActive2015_Warter = {}
	tVipPrivilegeOnlineActive2015_Warter[1] = {}
	tVipPrivilegeOnlineActive2015_Warter[1]["Stc"] = 16
	tVipPrivilegeOnlineActive2015_Warter[1]["Effect"] = "scene_transmissionsea"
	tVipPrivilegeOnlineActive2015_Warter[1]["ActionId"] = 271
	tVipPrivilegeOnlineActive2015_Warter[1]["Second"] = 3
	tVipPrivilegeOnlineActive2015_Warter[1]["Log"] = "0,0,0,0,12000077,1[1],0,0"

	tVipPrivilegeOnlineActive2015_Warter[2] = {}
	tVipPrivilegeOnlineActive2015_Warter[2]["Stc"] = 17
	tVipPrivilegeOnlineActive2015_Warter[2]["Effect"] = "spoondrift01"
	tVipPrivilegeOnlineActive2015_Warter[2]["ActionId"] = 220
	tVipPrivilegeOnlineActive2015_Warter[2]["Second"] = 3
	tVipPrivilegeOnlineActive2015_Warter[2]["Log"] = "0,0,0,0,12000077,1[2],0,0"
	
	tVipPrivilegeOnlineActive2015_Warter[3] = {}
	tVipPrivilegeOnlineActive2015_Warter[3]["Stc"] = 18
	tVipPrivilegeOnlineActive2015_Warter[3]["Effect"] = "scene_largefish"
	tVipPrivilegeOnlineActive2015_Warter[3]["ActionId"] = 250
	tVipPrivilegeOnlineActive2015_Warter[3]["Second"] = 3
	tVipPrivilegeOnlineActive2015_Warter[3]["Log"] = "0,0,0,0,12000077,1[3],0,0"

local tVipPrivilegeOnlineActive2015_Darts = {}
	tVipPrivilegeOnlineActive2015_Darts[1] = {}
	tVipPrivilegeOnlineActive2015_Darts[1]["ItemChanceSum"] = 1000
	
	tVipPrivilegeOnlineActive2015_Darts[1][1] = {}
	tVipPrivilegeOnlineActive2015_Darts[1][1]["RandomItemChanceType"] = 2
	tVipPrivilegeOnlineActive2015_Darts[1][1]["ItemChance"] = 500	
	tVipPrivilegeOnlineActive2015_Darts[1][1]["Item_1"] = 1					
	tVipPrivilegeOnlineActive2015_Darts[1][1]["Effect"] = "CircleUp"				
	tVipPrivilegeOnlineActive2015_Darts[1][1]["Reward"] = true		
	tVipPrivilegeOnlineActive2015_Darts[1][1]["Log"] = "0,0,0,0,12000078,1,0,0"		
	
	tVipPrivilegeOnlineActive2015_Darts[1][2] = {}
	tVipPrivilegeOnlineActive2015_Darts[1][2]["RandomItemChanceType"] = 2
	tVipPrivilegeOnlineActive2015_Darts[1][2]["ItemChance"] = 300	
	tVipPrivilegeOnlineActive2015_Darts[1][2]["Item_1"] = 2
	tVipPrivilegeOnlineActive2015_Darts[1][2]["Reward"] = false

	tVipPrivilegeOnlineActive2015_Darts[1][3] = {}
	tVipPrivilegeOnlineActive2015_Darts[1][3]["RandomItemChanceType"] = 2
	tVipPrivilegeOnlineActive2015_Darts[1][3]["ItemChance"] = 200	
	tVipPrivilegeOnlineActive2015_Darts[1][3]["Item_1"] = 3
	tVipPrivilegeOnlineActive2015_Darts[1][3]["Reward"] = false

local tVipPrivilegeOnlineActive2015_Reset = {}
	tVipPrivilegeOnlineActive2015_Reset[1] = {}
	tVipPrivilegeOnlineActive2015_Reset[1]["Time"] = "07:55 07:55"
	tVipPrivilegeOnlineActive2015_Reset[1]["IsMsg"] = true
	
	tVipPrivilegeOnlineActive2015_Reset[2] = {}
	tVipPrivilegeOnlineActive2015_Reset[2]["Time"] = "08:00 08:05"
	tVipPrivilegeOnlineActive2015_Reset[2]["IsMsg"] = false
	
	tVipPrivilegeOnlineActive2015_Reset[3] = {}
	tVipPrivilegeOnlineActive2015_Reset[3]["Time"] = "11:55 11:55"
	tVipPrivilegeOnlineActive2015_Reset[3]["IsMsg"] = true
	
	tVipPrivilegeOnlineActive2015_Reset[4] = {}
	tVipPrivilegeOnlineActive2015_Reset[4]["Time"] = "12:00 12:05"
	tVipPrivilegeOnlineActive2015_Reset[4]["IsMsg"] = false
	
	tVipPrivilegeOnlineActive2015_Reset[5] = {}
	tVipPrivilegeOnlineActive2015_Reset[5]["Time"] = "15:55 15:55"
	tVipPrivilegeOnlineActive2015_Reset[5]["IsMsg"] = true
	
	tVipPrivilegeOnlineActive2015_Reset[6] = {}
	tVipPrivilegeOnlineActive2015_Reset[6]["Time"] = "16:00 16:05"
	tVipPrivilegeOnlineActive2015_Reset[6]["IsMsg"] = false
	
	tVipPrivilegeOnlineActive2015_Reset[7] = {}
	tVipPrivilegeOnlineActive2015_Reset[7]["Time"] = "19:55 19:55"
	tVipPrivilegeOnlineActive2015_Reset[7]["IsMsg"] = true
	
	tVipPrivilegeOnlineActive2015_Reset[8] = {}
	tVipPrivilegeOnlineActive2015_Reset[8]["Time"] = "20:00 20:05"
	tVipPrivilegeOnlineActive2015_Reset[8]["IsMsg"] = false
	
	tVipPrivilegeOnlineActive2015_Reset[9] = {}
	tVipPrivilegeOnlineActive2015_Reset[9]["Time"] = "23:55 23:55"
	tVipPrivilegeOnlineActive2015_Reset[9]["IsMsg"] = true
	
	tVipPrivilegeOnlineActive2015_Reset[10] = {}
	tVipPrivilegeOnlineActive2015_Reset[10]["Time"] = "00:00 00:05"
	tVipPrivilegeOnlineActive2015_Reset[10]["IsMsg"] = false

--------------------------------------逻辑部分-----------------------------------------	
-- 进入VIP特权度假村
function VipPrivilegeOnlineActive2015_GetIntoMap(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断是否是VIP玩家
	local nVip = Get_UserVip()
	
	if nVip <= 0 then
		local nItemId = tVipPrivilegeOnlineActive2015_Constant["ResortTickets"]
		
		-- 检测是否有度假村门票
		if not Item_ChkItem(nItemId) then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end
		
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"3-4")
end
	
-- 非VIP玩家进入VIP特权度假村
function VipPrivilegeOnlineActive2015_NoVip(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nItemId = tVipPrivilegeOnlineActive2015_Constant["ResortTickets"]
	-- 检测是否有度假村门票
	if not Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[8]["DataType"]

	-- 判断非VIP玩家今天是否进入过度假村
	if Task_ChkStcValue(nEventType,nDataType,">",0) then
		if not Task_StcInterval(nEventType,nDataType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"3-3")
			return
		end
	end
	
	Task_SetStatistic(nEventType,nDataType,1,1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 删除物品
	if Item_DelItem(nItemId) then
		VipPrivilegeOnlineActive2015_ChgMap(nNpcId,1,"NoVIP")
	end
end

-- 传送地图
function VipPrivilegeOnlineActive2015_ChgMap(nNpcId,nType,sIndex)
	-- 判断是否在活动时间内
	if Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_MapInfo[nType]["Time"]) then
		local nMapId = tVipPrivilegeOnlineActive2015_MapInfo[nType]["MapId"]
		local nCellX = tVipPrivilegeOnlineActive2015_MapInfo[nType]["CellX"]
		local nCellY = tVipPrivilegeOnlineActive2015_MapInfo[nType]["CellY"]
		local nRange = tVipPrivilegeOnlineActive2015_MapInfo[nType]["Range"]
		
		User_UserRandBoundTrans(nMapId,nCellX,nCellY,nRange,nRange)
		User_TalkChannel2005(tVipPrivilegeOnlineActive2015_Text[nNpcId][sIndex])
	end
end	

-- 领取度假村门票
function VipPrivilegeOnlineActive2015_RewardResortTickets(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断是否是VIP玩家
	local nVip = Get_UserVip()
	
	if nVip > 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断玩家身上是否有度假村门票
	local nItemId = tVipPrivilegeOnlineActive2015_Constant["ResortTickets"]

	if Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断玩家今天是否进过度假村
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nIntoDataType = tVipPrivilegeOnlineActive2015_Stc[8]["DataType"]

	if Task_ChkStcValue(nEventType,nIntoDataType,">",0) then
		if not Task_StcInterval(nEventType,nIntoDataType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"2-3")
			return
		else
			Task_SetStatistic(nEventType,nIntoDataType,0,1)
			Task_SetStcTimestamp(nEventType,nIntoDataType,0)
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tVipPrivilegeOnlineActive2015_Constant["ItemSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[1]["DataType"]
	
	-- 判断掩码是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		Task_SetStatistic(nEventType,nDataType,0,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
	end

	-- 判断是否已领取过
	if Task_ChkStcValue(nEventType,nDataType,"==",0) then
		-- 判断本时段是否还有度假村凭证
		local nGlobalId = tVipPrivilegeOnlineActive2015_Constant["GlobalId"]
		local nMaxData = tVipPrivilegeOnlineActive2015_Constant["MaxData"]
		local nGlobalData = Get_SysDynaGlobalData1(nGlobalId)
		
		if nGlobalData >= nMaxData then
			LinkNpcGossipFunc_New(nNpcId,"2-5")
			return
		end
		
		Sys_SetSynaGlobalData1(nGlobalId,nGlobalData + 1)
	end
	
	Task_SetStatistic(nEventType,nDataType,1,1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 添加度假村门票
	Item_AddItem(nItemId)
	
	-- 打log
	local sLog = string.format(tVipPrivilegeOnlineActive2015_Log["RewardItem"],nItemId)
	Sys_SaveActionFestivalLog(sLog)
	
	-- 给提示
	User_TalkChannel2007(tVipPrivilegeOnlineActive2015_Text[nNpcId]["RewardItem"])
	LinkNpcGossipFunc_New(nNpcId,"2-6")
end

-- 自动寻路
function VipPrivilegeOnlineActive2015_Auto(nNpcId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		if nNpcId ~= nil then
			LinkNpcGossipFunc_New(nNpcId,"1-2")
		end
		
		return
	end

	local nMapId = tVipPrivilegeOnlineActive2015_Auto[nType]["MapId"]
	local nPosX = tVipPrivilegeOnlineActive2015_Auto[nType]["CellX"]
	local nPosY = tVipPrivilegeOnlineActive2015_Auto[nType]["CellY"]
	local nGotoNpcId = tVipPrivilegeOnlineActive2015_Auto[nType]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nGotoNpcId)
end

-- 我要“清凉一夏”
function VipPrivilegeOnlineActive2015_CoolSummer(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断是否是VIP玩家
	local nVip = Get_UserVip()
	
	if nVip <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[7]["DataType"]

	-- 判断是否领取过
	if Task_ChkStcValue(nEventType,nDataType,">",0) then
		-- 判断是否隔天
		if Task_StcInterval(nEventType,nDataType,1,4) then
			Task_SetStatistic(nEventType,nDataType,0,1)
			Task_SetStcTimestamp(nEventType,nDataType,0)
		else
			LinkNpcGossipFunc_New(nNpcId,"4-1")
			return
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tVipPrivilegeOnlineActive2015_Constant["ItemSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	-- 设掩码
	Task_SetStatistic(nEventType,nDataType,1,1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 给物品
	local nItemId = tVipPrivilegeOnlineActive2015_Constant["Beer"]
	
	Item_AddItem(nItemId,0,1,0,1440,1)
	-- 打log
	local sLog = string.format(tVipPrivilegeOnlineActive2015_Log["RewardItem"],nItemId)
	Sys_SaveActionFestivalLog(sLog)
	
	-- 给提示
	User_TalkChannel2005(tVipPrivilegeOnlineActive2015_Text[nNpcId]["RewardItem"])
	LinkNpcGossipFunc_New(nNpcId,"4-2")
end

-- 领取奖励
function VipPrivilegeOnlineActive2015_RewardItem(nNpcId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	-- 判断是否是VIP玩家
	local nVip = Get_UserVip()
	
	if nVip <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[nType]["DataType"]
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		Task_SetStatistic(nEventType,nDataType,0,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
		
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 判断是否领取过奖励
	if Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["RewardData"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断是否完成任务
	local nCompletData = tVipPrivilegeOnlineActive2015_RewardItem[nType]["CompleteData"]
	
	if Task_ChkStcValue(nEventType,nDataType,"<",nCompletData) then
		LinkNpcGossipFunc_New(nNpcId,tVipPrivilegeOnlineActive2015_RewardItem[nType]["NoComplete"])
		return
	end

	local nIndex = 1
	local nLen = #tVipPrivilegeOnlineActive2015_Vip 
	
	-- 判断VIP等级
	for i = 1,nLen do
		if i == nLen and nVip >= tVipPrivilegeOnlineActive2015_Vip[i]["MinVipLev"] then
			nIndex = i
			break
		elseif nVip >= tVipPrivilegeOnlineActive2015_Vip[i]["MinVipLev"] and nVip <= tVipPrivilegeOnlineActive2015_Vip[i]["MaxVipLev"] then
			nIndex = i
			break
		end
	end
	
	local nItemNum = tVipPrivilegeOnlineActive2015_Vip[nIndex]["ItemNum"]
	local nRewardDataType = tVipPrivilegeOnlineActive2015_Stc[9]["DataType"]
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nRewardDataType,1,4) then
		Task_SetStatistic(nEventType,nRewardDataType,0,1)
		Task_SetStcTimestamp(nEventType,nRewardDataType,0)
	end

	-- 判断今天领取礼包的个数是否超过
	if Task_ChkStcValue(nEventType,nRewardDataType,">=",nItemNum) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	-- 判断背包空间
	local nAddItemNum = tVipPrivilegeOnlineActive2015_Vip[nIndex]["AddItemNum"][nType]
	
	if not User_CheckLeftSpace(nAddItemNum) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	-- 置掩码
	Task_SetStatistic(nEventType,nDataType,tVipPrivilegeOnlineActive2015_Constant["RewardData"],1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	Task_AddStatistic(nEventType,nRewardDataType,nAddItemNum,1)
	Task_SetStcTimestamp(nEventType,nRewardDataType,0)
	
	-- 给奖励
	local nMetempsychosis = Get_UserMetempsychosis()
	local nItemId = 0
	
	if nMetempsychosis >= 2 then
		nItemId = tVipPrivilegeOnlineActive2015_Constant["RewardItem"][2]
	elseif nMetempsychosis >= 1 then
		nItemId = tVipPrivilegeOnlineActive2015_Constant["RewardItem"][1]
	else
		nItemId = tVipPrivilegeOnlineActive2015_Constant["RewardItem"][0]
	end
	
	Item_AddItem(nItemId,0,nAddItemNum,0,1440,1)
	
	local sLog = string.format(tVipPrivilegeOnlineActive2015_RewardItem[nType]["Log"],nItemId,nAddItemNum)
	Sys_SaveActionFestivalLog(sLog)
	
	LinkNpcGossipFunc_New(nNpcId,tVipPrivilegeOnlineActive2015_RewardItem[nType]["Reward"])
end

-- 度假毯项目
function VipPrivilegeOnlineActive2015_Warter(nNpcId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断是否是VIP玩家
	local nVip = Get_UserVip()
	
	if nVip <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[5]["DataType"]
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		Task_SetStatistic(nEventType,nDataType,0,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
	-- 判断是否已领取过奖励
	elseif Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["RewardData"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	-- 判断是否已完成毯子的所有选项
	elseif Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["CompleteData"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	local nCompletType = tVipPrivilegeOnlineActive2015_Warter[nType]["Stc"]
	
	if Task_StcInterval(nEventType,nCompletType,1,4) then
		Task_SetStatistic(nEventType,nCompletType,0,1)
		Task_SetStcTimestamp(nEventType,nCompletType,0)
	elseif Task_ChkStcValue(nEventType,nCompletType,">=",1) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	local nSecs = tVipPrivilegeOnlineActive2015_Warter[nType]["Second"]
	local sContent = tVipPrivilegeOnlineActive2015_Text[nNpcId]["Project"][nType]["Read"]
	local nActionId = tVipPrivilegeOnlineActive2015_Warter[nType]["ActionId"]
	local sFunc = string.format("VipPrivilegeOnlineActive2015_Explore</N>%d</N>%d",nType,nNpcId)
	local sEffect = tVipPrivilegeOnlineActive2015_Warter[nType]["Effect"]
	
	User_EffectAdd("self",sEffect)
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end

function VipPrivilegeOnlineActive2015_Explore(nType,nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		return
	end

	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nCompletType = tVipPrivilegeOnlineActive2015_Warter[nType]["Stc"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[5]["DataType"]
	
	-- 设掩码
	Task_SetStatistic(nEventType,nCompletType,1,1)
	Task_SetStcTimestamp(nEventType,nCompletType,0)
	
	Task_AddStatistic(nEventType,nDataType,1,1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 打log
	Sys_SaveActionFestivalLog(tVipPrivilegeOnlineActive2015_Warter[nType]["Log"])
	
	-- 提示
	User_TalkChannel2007(tVipPrivilegeOnlineActive2015_Text[nNpcId]["Project"][nType]["Complete"])
	
	if Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["CompleteData"]) then
		Sys_MsgBox(tVipPrivilegeOnlineActive2015_Text[nNpcId]["Project"]["Complete"],string.format("VipPrivilegeOnlineActive2015_Auto</N>%d</N>%d",nNpcId,3))
	end
end

-- 投掷飞镖
function VipPrivilegeOnlineActive2015_ThrowingDarts(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[6]["DataType"]
	local nVip = Get_UserVip() 
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		Task_SetStatistic(nEventType,nDataType,0,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
	elseif Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["RewardData"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	elseif Task_ChkStcValue(nEventType,nDataType,">=",1) then
		if nVip > 0 then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
		else
			LinkNpcGossipFunc_New(nNpcId,"2-1")
		end
		
		return
	end
	
	local nFlat,tAward = Probabil_RandomAward(tVipPrivilegeOnlineActive2015_Darts,1)
	local bReward = tAward[1]["tAward"][1]["Reward"]
	local nIndex = tAward[1]["tAward"][1]["Item_1"]
	
	-- 正中靶心
	if bReward then
		-- 设掩码
		Task_SetStatistic(nEventType,nDataType,1,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
		
		-- 播光效
		local sEffect = tAward[1]["tAward"][1]["Effect"]
		User_EffectAdd("self",sEffect)

		local nRandomNum = math.random(1,2)
		
		if nVip > 0 then
			Sys_SaveActionFestivalLog(tAward[1]["tAward"][1]["Log"])
			
			local sText = tVipPrivilegeOnlineActive2015_Text[nNpcId][nIndex]["Vip"][nRandomNum]
			Sys_MsgBox(sText)
			
			VipPrivilegeOnlineActive2015_Auto(nNpcId,3)
		else
			local sText = tVipPrivilegeOnlineActive2015_Text[nNpcId][nIndex]["NoVip"][nRandomNum]
			Sys_MsgBox(sText)
		end
	else
		local nRandomNum = math.random(1,2)
		Sys_MsgBox(tVipPrivilegeOnlineActive2015_Text[nNpcId][nIndex][nRandomNum])
	end
end

-- 动态掩码清零
function VipPrivilegeOnlineActive2015_Reset(nHour)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		return
	end
	
	local nIndex = 0
	
	for i = 1,#tVipPrivilegeOnlineActive2015_Reset do
		local sTime = tVipPrivilegeOnlineActive2015_Reset[i]["Time"]
		
		if Sys_ChkDayTime(sTime) then
			nIndex = i
			break
		end
	end
	
	-- 提示公告
	if nIndex ~= 0 and tVipPrivilegeOnlineActive2015_Reset[nIndex]["IsMsg"] then
		Sys_SystemBroadcast(tVipPrivilegeOnlineActive2015_Text["SysMsg"][nHour])
		return
	end

	local nGlobalId = tVipPrivilegeOnlineActive2015_Constant["GlobalId"]
	local nData0 = Get_SysDynaGlobalData0(nGlobalId)
	
	-- 动态掩码清零开关
	if nIndex == 0 then
		if nData0 ~= 0 then
			Sys_SetSynaGlobalData0(nGlobalId,0)
		end
		
		return
	end
	
	-- 动态掩码清零
	if not nData0 == 1 then
		Sys_SetSynaGlobalData1(nGlobalId,0)
		Sys_SetSynaGlobalData0(nGlobalId,1)
	end
end

-- VIP特权度假邀请卡使用
function VipPrivilegeOnlineActive2015_InvitatCard(nItemId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tVipPrivilegeOnlineActive2015_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	if nType == 1 then
		VipPrivilegeOnlineActive2015_Auto(nil,4)
	elseif Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nLev = Get_UserLevel()
		local sContent = ""
		local sLog = ""
		
		if nLev >= 140 then
			User_AddCultivation(tVipPrivilegeOnlineActive2015_RewardItem[nItemId]["Cultivation"])
			sContent = tVipPrivilegeOnlineActive2015_Text[nItemId]["RewardCultivation"]
			sLog = tVipPrivilegeOnlineActive2015_RewardItem[nItemId]["CultivationLog"]
		else
			User_AddExpTime(tVipPrivilegeOnlineActive2015_RewardItem[nItemId]["Exp"])
			sContent = tVipPrivilegeOnlineActive2015_Text[nItemId]["RewardExp"]
			sLog = tVipPrivilegeOnlineActive2015_RewardItem[nItemId]["ExpLog"]
		end

		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
	end
end

--------------------------------------NPC模块-------------------------------------------
-- VIP特权度假村导游先森
tNpcFace[3064] = 64
tNpcGossip[18464] = tNpcGossip[18464] or DefaultNpc:new{}
tNpcGossip[18464]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[18464]["Text1-1"] = {111,112,113,114}
tNpcGossip[18464]["Text111"] = tVipPrivilegeOnlineActive2015_Text[18464]["111"]
tNpcGossip[18464]["Text112"] = tVipPrivilegeOnlineActive2015_Text[18464]["112"]
tNpcGossip[18464]["Text113"] = tVipPrivilegeOnlineActive2015_Text[18464]["113"]
tNpcGossip[18464]["Text114"] = tVipPrivilegeOnlineActive2015_Text[18464]["114"]
tNpcGossip[18464]["tOption1-1"] = {1}
tNpcGossip[18464]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["BeforeActivityTime"])
end

-- 活动中对白
tNpcGossip[18464]["Text1-2"] = {121,122,123,124}
tNpcGossip[18464]["Text121"] = tVipPrivilegeOnlineActive2015_Text[18464]["121"]
tNpcGossip[18464]["Text122"] = tVipPrivilegeOnlineActive2015_Text[18464]["122"]
tNpcGossip[18464]["Text123"] = tVipPrivilegeOnlineActive2015_Text[18464]["123"]
tNpcGossip[18464]["Text124"] = tVipPrivilegeOnlineActive2015_Text[18464]["124"]
tNpcGossip[18464]["tOption1-2"] = {2,3,4,5}
tNpcGossip[18464]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"])
end

-- 活动后对白
tNpcGossip[18464]["Text1-3"] = {131}
tNpcGossip[18464]["Text131"] = tVipPrivilegeOnlineActive2015_Text[18464]["131"]
tNpcGossip[18464]["tOption1-3"] = {6}

-- VIP玩家
tNpcGossip[18464]["Text2-1"] = {211}
tNpcGossip[18464]["Text211"] = tVipPrivilegeOnlineActive2015_Text[18464]["211"]
tNpcGossip[18464]["tOption2-1"] = {7}

-- 玩家身上有度假村门票
tNpcGossip[18464]["Text2-2"] = {221}
tNpcGossip[18464]["Text221"] = tVipPrivilegeOnlineActive2015_Text[18464]["221"]
tNpcGossip[18464]["tOption2-2"] = {8}

-- 玩家今天进过度假村
tNpcGossip[18464]["Text2-3"] = {231}
tNpcGossip[18464]["Text231"] = tVipPrivilegeOnlineActive2015_Text[18464]["231"]
tNpcGossip[18464]["tOption2-3"] = {9}

-- 背包空间
tNpcGossip[18464]["Text2-4"] = {241}
tNpcGossip[18464]["Text241"] = tVipPrivilegeOnlineActive2015_Text[18464]["241"]
tNpcGossip[18464]["tOption2-4"] = {10}

-- 本时段没有度假村凭证
tNpcGossip[18464]["Text2-5"] = {251,252,253}
tNpcGossip[18464]["Text251"] = tVipPrivilegeOnlineActive2015_Text[18464]["251"]
tNpcGossip[18464]["Text252"] = tVipPrivilegeOnlineActive2015_Text[18464]["252"]
tNpcGossip[18464]["Text253"] = tVipPrivilegeOnlineActive2015_Text[18464]["253"]
tNpcGossip[18464]["tOption2-5"] = {11}

-- 领取度假村凭证
tNpcGossip[18464]["Text2-6"] = {261,262}
tNpcGossip[18464]["Text261"] = tVipPrivilegeOnlineActive2015_Text[18464]["261"]
tNpcGossip[18464]["Text262"] = tVipPrivilegeOnlineActive2015_Text[18464]["262"]
tNpcGossip[18464]["tOption2-6"] = {12}

-- 非VIP玩家没有度假村凭证
tNpcGossip[18464]["Text3-1"] = {311,312}
tNpcGossip[18464]["Text311"] = tVipPrivilegeOnlineActive2015_Text[18464]["311"]
tNpcGossip[18464]["Text312"] = tVipPrivilegeOnlineActive2015_Text[18464]["312"]
tNpcGossip[18464]["tOption3-1"] = {13}

-- 非VIP玩家有度假村凭证
tNpcGossip[18464]["Text3-2"] = {321}
tNpcGossip[18464]["Text321"] = tVipPrivilegeOnlineActive2015_Text[18464]["321"]
tNpcGossip[18464]["tOption3-2"] = {14}

-- 非VIP玩家进入过度假村
tNpcGossip[18464]["Text3-3"] = {331}
tNpcGossip[18464]["Text331"] = tVipPrivilegeOnlineActive2015_Text[18464]["331"]
tNpcGossip[18464]["tOption3-3"] = {15}

-- 非VIP玩家进入过度假村
tNpcGossip[18464]["Text3-4"] = {341}
tNpcGossip[18464]["Text341"] = tVipPrivilegeOnlineActive2015_Text[18464]["341"]
tNpcGossip[18464]["tOption3-4"] = {16}

-- 活动详情
tNpcGossip[18464]["Text4-1"] = {411,412,413,414}
tNpcGossip[18464]["Text411"] = tVipPrivilegeOnlineActive2015_Text[18464]["411"]
tNpcGossip[18464]["Text412"] = tVipPrivilegeOnlineActive2015_Text[18464]["412"]
tNpcGossip[18464]["Text413"] = tVipPrivilegeOnlineActive2015_Text[18464]["413"]
tNpcGossip[18464]["Text414"] = tVipPrivilegeOnlineActive2015_Text[18464]["414"]
tNpcGossip[18464]["tOption4-1"] = {17}

tNpcGossip[18464]["Text5-1"] = {511,512,513}
tNpcGossip[18464]["Text511"] = tVipPrivilegeOnlineActive2015_Text[18464]["511"]
tNpcGossip[18464]["Text512"] = tVipPrivilegeOnlineActive2015_Text[18464]["512"]
tNpcGossip[18464]["Text513"] = tVipPrivilegeOnlineActive2015_Text[18464]["513"]
tNpcGossip[18464]["tOption5-1"] = {18}

-- 选项
tNpcGossip[18464]["Option1"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option1"]
tNpcGossip[18464]["Option2"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option2"]
tNpcGossip[18464]["OptionFunc2"]="VipPrivilegeOnlineActive2015_GetIntoMap</N>18464"
tNpcGossip[18464]["Option3"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option3"]
tNpcGossip[18464]["OptionFunc3"]="VipPrivilegeOnlineActive2015_RewardResortTickets</N>18464"
tNpcGossip[18464]["Option4"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option4"]
tNpcGossip[18464]["OptionPoint4"]="4"
tNpcGossip[18464]["Option5"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option5"]
tNpcGossip[18464]["Option6"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option6"]
tNpcGossip[18464]["Option7"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option7"]
tNpcGossip[18464]["Option8"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option8"]
tNpcGossip[18464]["Option9"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option9"]
tNpcGossip[18464]["Option10"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option10"]
tNpcGossip[18464]["Option11"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option11"]
tNpcGossip[18464]["Option12"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option12"]
tNpcGossip[18464]["Option13"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option13"]
tNpcGossip[18464]["Option14"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option14"]
tNpcGossip[18464]["OptionFunc14"]="VipPrivilegeOnlineActive2015_NoVip</N>18464"
tNpcGossip[18464]["Option15"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option15"]
tNpcGossip[18464]["Option16"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option16"]
tNpcGossip[18464]["OptionFunc16"]="VipPrivilegeOnlineActive2015_ChgMap</N>18464</N>1</S>VIP"
tNpcGossip[18464]["Option17"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option17"]
tNpcGossip[18464]["OptionPoint17"]="5"
tNpcGossip[18464]["Option18"] = tVipPrivilegeOnlineActive2015_Text[18464]["Option18"]

-- 度假村招待专员夏呵呵
tNpcFace[3065] = 180
tNpcGossip[18465] = tNpcGossip[18465] or DefaultNpc:new{}
tNpcGossip[18465]["OptionHidden"] = 1

-- 活动中对白
tNpcGossip[18465]["Text1-1"] = {111,112,113}
tNpcGossip[18465]["Text111"] = tVipPrivilegeOnlineActive2015_Text[18465]["111"]
tNpcGossip[18465]["Text112"] = tVipPrivilegeOnlineActive2015_Text[18465]["112"]
tNpcGossip[18465]["Text113"] = tVipPrivilegeOnlineActive2015_Text[18465]["113"]
tNpcGossip[18465]["tOption1-1"] = {1,2,3,4,5,6,7,8}
tNpcGossip[18465]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"])
end

-- 活动后对白
tNpcGossip[18465]["Text1-2"] = {121}
tNpcGossip[18465]["Text121"] = tVipPrivilegeOnlineActive2015_Text[18465]["121"]
tNpcGossip[18465]["tOption1-2"] = {9}

-- 领取“水的亲密接触”礼物。
-- 非VIP玩家
tNpcGossip[18465]["Text2-1"] = {211}
tNpcGossip[18465]["Text211"] = tVipPrivilegeOnlineActive2015_Text[18465]["211"]
tNpcGossip[18465]["tOption2-1"] = {10}

-- 领取过奖励
tNpcGossip[18465]["Text2-2"] = {221}
tNpcGossip[18465]["Text221"] = tVipPrivilegeOnlineActive2015_Text[18465]["221"]
tNpcGossip[18465]["tOption2-2"] = {11}

-- 没有完成任务
tNpcGossip[18465]["Text2-3"] = {231,232}
tNpcGossip[18465]["Text231"] = tVipPrivilegeOnlineActive2015_Text[18465]["231"]
tNpcGossip[18465]["Text232"] = tVipPrivilegeOnlineActive2015_Text[18465]["232"]
tNpcGossip[18465]["tOption2-3"] = {12}

-- 领取奖励
tNpcGossip[18465]["Text2-4"] = {241,242}
tNpcGossip[18465]["Text241"] = tVipPrivilegeOnlineActive2015_Text[18465]["241"]
tNpcGossip[18465]["Text242"] = tVipPrivilegeOnlineActive2015_Text[18465]["242"]
tNpcGossip[18465]["tOption2-4"] = {13}

-- 领取“沙滩休闲飞镖”礼物。
-- 没有飞镖靶子
tNpcGossip[18465]["Text3-1"] = {311,312}
tNpcGossip[18465]["Text311"] = tVipPrivilegeOnlineActive2015_Text[18465]["311"]
tNpcGossip[18465]["Text312"] = tVipPrivilegeOnlineActive2015_Text[18465]["312"]
tNpcGossip[18465]["tOption3-1"] = {14}

-- 背包空间满
tNpcGossip[18465]["Text3-2"] = {321}
tNpcGossip[18465]["Text321"] = tVipPrivilegeOnlineActive2015_Text[18465]["321"]
tNpcGossip[18465]["tOption3-2"] = {15}

-- 背包空间满
tNpcGossip[18465]["Text3-3"] = {331,332}
tNpcGossip[18465]["Text331"] = tVipPrivilegeOnlineActive2015_Text[18465]["331"]
tNpcGossip[18465]["Text332"] = tVipPrivilegeOnlineActive2015_Text[18465]["332"]
tNpcGossip[18465]["tOption3-3"] = {16}

-- 我要“清凉一夏”。
-- 已领取过
tNpcGossip[18465]["Text4-1"] = {411}
tNpcGossip[18465]["Text411"] = tVipPrivilegeOnlineActive2015_Text[18465]["411"]
tNpcGossip[18465]["tOption4-1"] = {17}

-- 领取啤酒和炸鸡
tNpcGossip[18465]["Text4-2"] = {421,422}
tNpcGossip[18465]["Text421"] = tVipPrivilegeOnlineActive2015_Text[18465]["421"]
tNpcGossip[18465]["Text422"] = tVipPrivilegeOnlineActive2015_Text[18465]["422"]
tNpcGossip[18465]["tOption4-2"] = {18}

-- 活动总介绍。
tNpcGossip[18465]["Text5-1"] = {511,512,513}
tNpcGossip[18465]["Text511"] = tVipPrivilegeOnlineActive2015_Text[18465]["511"]
tNpcGossip[18465]["Text512"] = tVipPrivilegeOnlineActive2015_Text[18465]["512"]
tNpcGossip[18465]["Text513"] = tVipPrivilegeOnlineActive2015_Text[18465]["513"]
tNpcGossip[18465]["tOption5-1"] = {19}

tNpcGossip[18465]["Text6-1"] = {611,612,613}
tNpcGossip[18465]["Text611"] = tVipPrivilegeOnlineActive2015_Text[18465]["611"]
tNpcGossip[18465]["Text612"] = tVipPrivilegeOnlineActive2015_Text[18465]["612"]
tNpcGossip[18465]["Text613"] = tVipPrivilegeOnlineActive2015_Text[18465]["613"]
tNpcGossip[18465]["tOption6-1"] = {20}

-- 离开地图。
tNpcGossip[18465]["Text7-1"] = {711}
tNpcGossip[18465]["Text711"] = tVipPrivilegeOnlineActive2015_Text[18465]["711"]
tNpcGossip[18465]["tOption7-1"] = {21}

-- 选项
tNpcGossip[18465]["Option1"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option1"]
tNpcGossip[18465]["OptionFunc1"]="VipPrivilegeOnlineActive2015_Auto</N>18465</N>1"
tNpcGossip[18465]["OptionChkFunc1"] = function ()
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[5]["DataType"]
 
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		return true
	end
	
	if Task_ChkStcValue(nEventType,nDataType,">=",tVipPrivilegeOnlineActive2015_Constant["CompleteData"]) then
		return false
	else
		return true
	end
end

tNpcGossip[18465]["Option2"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option2"]
tNpcGossip[18465]["OptionFunc2"]="VipPrivilegeOnlineActive2015_Auto</N>18465</N>2"
tNpcGossip[18465]["OptionChkFunc2"] = function ()
	local nEventType = tVipPrivilegeOnlineActive2015_Stc["EventType"]
	local nDataType = tVipPrivilegeOnlineActive2015_Stc[6]["DataType"]
 
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		return true
	end
	
	if Task_ChkStcValue(nEventType,nDataType,">=",1) then
		return false
	else
		return true
	end
end

tNpcGossip[18465]["Option3"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option3"]
tNpcGossip[18465]["OptionFunc3"]="VipPrivilegeOnlineActive2015_CoolSummer</N>18465"
tNpcGossip[18465]["Option4"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option4"]
tNpcGossip[18465]["OptionFunc4"]="VipPrivilegeOnlineActive2015_RewardItem</N>18465</N>5"
tNpcGossip[18465]["Option5"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option5"]
tNpcGossip[18465]["OptionFunc5"]="VipPrivilegeOnlineActive2015_RewardItem</N>18465</N>6"
tNpcGossip[18465]["Option6"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option6"]
tNpcGossip[18465]["OptionPoint6"]="5"
tNpcGossip[18465]["Option7"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option7"]
tNpcGossip[18465]["OptionPoint7"]="7"
tNpcGossip[18465]["Option8"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option8"]
tNpcGossip[18465]["Option9"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option9"]
tNpcGossip[18465]["OptionPoint9"]="7"
tNpcGossip[18465]["Option10"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option10"]
tNpcGossip[18465]["Option11"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option11"]
tNpcGossip[18465]["Option12"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option12"]
tNpcGossip[18465]["Option13"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option13"]
tNpcGossip[18465]["Option14"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option14"]
tNpcGossip[18465]["Option15"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option15"]
tNpcGossip[18465]["Option16"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option16"]
tNpcGossip[18465]["Option17"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option17"]
tNpcGossip[18465]["Option18"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option18"]
tNpcGossip[18465]["Option19"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option19"]
tNpcGossip[18465]["OptionPoint19"]="6"
tNpcGossip[18465]["Option20"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option20"]
tNpcGossip[18465]["Option21"] = tVipPrivilegeOnlineActive2015_Text[18465]["Option21"]
tNpcGossip[18465]["OptionFunc21"]="VipPrivilegeOnlineActive2015_ChgMap</N>18465</N>2</S>VIP"

-- 度假毯
tNpcGossip[18467] = tNpcGossip[18467] or DefaultNpc:new{}
tNpcGossip[18467]["OptionHidden"] = 1

-- 活动中对白
tNpcGossip[18467]["Text1-1"] = {111,112,113}
tNpcGossip[18467]["Text111"] = tVipPrivilegeOnlineActive2015_Text[18467]["111"]
tNpcGossip[18467]["Text112"] = tVipPrivilegeOnlineActive2015_Text[18467]["112"]
tNpcGossip[18467]["Text113"] = tVipPrivilegeOnlineActive2015_Text[18467]["113"]
tNpcGossip[18467]["tOption1-1"] = {1,2,3,4}
tNpcGossip[18467]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"])
end

-- 闲聊对白
tNpcGossip[18467]["Text1-2"] = {121,122}
tNpcGossip[18467]["Text121"] = tVipPrivilegeOnlineActive2015_Text[18467]["121"]
tNpcGossip[18467]["Text122"] = tVipPrivilegeOnlineActive2015_Text[18467]["122"]
tNpcGossip[18467]["tOption1-2"] = {5}

-- 非VIP玩家
tNpcGossip[18467]["Text2-1"] = {211}
tNpcGossip[18467]["Text211"] = tVipPrivilegeOnlineActive2015_Text[18467]["211"]
tNpcGossip[18467]["tOption2-1"] = {6}

-- 已领取过奖励
tNpcGossip[18467]["Text2-2"] = {221,222}
tNpcGossip[18467]["Text221"] = tVipPrivilegeOnlineActive2015_Text[18467]["221"]
tNpcGossip[18467]["Text222"] = tVipPrivilegeOnlineActive2015_Text[18467]["222"]
tNpcGossip[18467]["tOption2-2"] = {7}

-- 已完成任务
tNpcGossip[18467]["Text2-3"] = {231,232}
tNpcGossip[18467]["Text231"] = tVipPrivilegeOnlineActive2015_Text[18467]["231"]
tNpcGossip[18467]["Text232"] = tVipPrivilegeOnlineActive2015_Text[18467]["232"]
tNpcGossip[18467]["tOption2-3"] = {8}

-- 已完成该选项
tNpcGossip[18467]["Text2-4"] = {241}
tNpcGossip[18467]["Text241"] = tVipPrivilegeOnlineActive2015_Text[18467]["241"]
tNpcGossip[18467]["tOption2-4"] = {9}

tNpcGossip[18467]["Option1"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option1"]
tNpcGossip[18467]["OptionFunc1"]="VipPrivilegeOnlineActive2015_Warter</N>18467</N>1"
tNpcGossip[18467]["Option2"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option2"]
tNpcGossip[18467]["OptionFunc2"]="VipPrivilegeOnlineActive2015_Warter</N>18467</N>2"
tNpcGossip[18467]["Option3"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option3"]
tNpcGossip[18467]["OptionFunc3"]="VipPrivilegeOnlineActive2015_Warter</N>18467</N>3"
tNpcGossip[18467]["Option4"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option4"]
tNpcGossip[18467]["Option5"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option5"]
tNpcGossip[18467]["Option6"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option6"]
tNpcGossip[18467]["Option7"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option7"]
tNpcGossip[18467]["Option8"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option8"]
tNpcGossip[18467]["OptionFunc8"]="VipPrivilegeOnlineActive2015_Auto</N>18467</N>3"
tNpcGossip[18467]["Option9"] = tVipPrivilegeOnlineActive2015_Text[18467]["Option9"]
tNpcGossip[18467]["OptionPoint9"]="1"

tNpcGossip[18468] = tNpcGossip[18467]
tNpcGossip[18469] = tNpcGossip[18467]
tNpcGossip[18470] = tNpcGossip[18467]

-- 飞镖靶子
tNpcGossip[18471] = tNpcGossip[18471] or DefaultNpc:new{}
tNpcGossip[18471]["OptionHidden"] = 1

-- 活动中对白
tNpcGossip[18471]["Text1-1"] = {111,112,113,114}
tNpcGossip[18471]["Text111"] = tVipPrivilegeOnlineActive2015_Text[18471]["111"]
tNpcGossip[18471]["Text112"] = tVipPrivilegeOnlineActive2015_Text[18471]["112"]
tNpcGossip[18471]["Text113"] = tVipPrivilegeOnlineActive2015_Text[18471]["113"]
tNpcGossip[18471]["Text114"] = tVipPrivilegeOnlineActive2015_Text[18471]["114"]
tNpcGossip[18471]["tOption1-1"] = {1,2}
tNpcGossip[18471]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"])
end

-- 闲聊对白
tNpcGossip[18471]["Text1-2"] = {121,122}
tNpcGossip[18471]["Text121"] = tVipPrivilegeOnlineActive2015_Text[18471]["121"]
tNpcGossip[18471]["Text122"] = tVipPrivilegeOnlineActive2015_Text[18471]["122"]
tNpcGossip[18471]["tOption1-2"] = {3}

-- 领取过奖励
tNpcGossip[18471]["Text2-1"] = {211}
tNpcGossip[18471]["Text211"] = tVipPrivilegeOnlineActive2015_Text[18471]["211"]
tNpcGossip[18471]["tOption2-1"] = {4}

-- VIP
tNpcGossip[18471]["Text2-2"] = {221,222}
tNpcGossip[18471]["Text221"] = tVipPrivilegeOnlineActive2015_Text[18471]["221"]
tNpcGossip[18471]["Text222"] = tVipPrivilegeOnlineActive2015_Text[18471]["222"]
tNpcGossip[18471]["tOption2-2"] = {5}

tNpcGossip[18471]["Option1"] = tVipPrivilegeOnlineActive2015_Text[18471]["Option1"]
tNpcGossip[18471]["OptionFunc1"]="VipPrivilegeOnlineActive2015_ThrowingDarts</N>18471"
tNpcGossip[18471]["Option2"] = tVipPrivilegeOnlineActive2015_Text[18471]["Option2"]
tNpcGossip[18471]["Option3"] = tVipPrivilegeOnlineActive2015_Text[18471]["Option3"]
tNpcGossip[18471]["Option4"] = tVipPrivilegeOnlineActive2015_Text[18471]["Option4"]
tNpcGossip[18471]["Option5"] = tVipPrivilegeOnlineActive2015_Text[18471]["Option5"]
tNpcGossip[18471]["OptionFunc5"]="VipPrivilegeOnlineActive2015_Auto</N>18471</N>3"

tNpcGossip[18472] = tNpcGossip[18471]
tNpcGossip[18473] = tNpcGossip[18471]

-- 啤酒和炸鸡
tItem[3004104] = tItem[3004104] or {}
tItem[3004104]["Function"] = function(nItemId,sItemName)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Sys_SaveActionFestivalLog("0,0,3004104,1,12000076,1,0,0")
		
		if not Sys_ChkFullTime(tVipPrivilegeOnlineActive2015_Constant["ActivityTime"]) then
			Sys_MsgBox(tVipPrivilegeOnlineActive2015_Text[nItemId]["BeOverdue"])
			return
		end
		
		User_TalkChannel2007(tVipPrivilegeOnlineActive2015_Text[nItemId]["Overdue"])
		
		local nVip = Get_UserVip()
		if nVip > 3 then
			User_EffectAdd("self","red-flower-smallrain-ten")
		else
			User_EffectAdd("self","red-flower-smallrain-five")
		end
	end
end

-- VIP特权度假邀请卡
tItem[3006618] = tItem[3006618] or {}
tItem[3006618]["Text1-1"] = {111,112,113,114,115}
tItem[3006618]["Text111"] = tVipPrivilegeOnlineActive2015_Text[3006618]["111"]
tItem[3006618]["Text112"] = tVipPrivilegeOnlineActive2015_Text[3006618]["112"]
tItem[3006618]["Text113"] = tVipPrivilegeOnlineActive2015_Text[3006618]["113"]
tItem[3006618]["Text114"] = tVipPrivilegeOnlineActive2015_Text[3006618]["114"]
tItem[3006618]["Text115"] = tVipPrivilegeOnlineActive2015_Text[3006618]["115"]
tItem[3006618]["tOption1-1"] = {1,2}

tItem[3006618]["Option1"] = tVipPrivilegeOnlineActive2015_Text[3006618]["Option1"]
tItem[3006618]["OptionFunc1"]="VipPrivilegeOnlineActive2015_InvitatCard</N>3006618</N>1"
tItem[3006618]["Option2"] = tVipPrivilegeOnlineActive2015_Text[3006618]["Option2"]
tItem[3006618]["OptionFunc2"]="VipPrivilegeOnlineActive2015_InvitatCard</N>3006618</N>2"

-- 时间自检触发
-- tSystem_Prompet_Func = tSystem_Prompet_Func or {}
-- table.insert(tSystem_Prompet_Func,VipPrivilegeOnlineActive2015_Reset)