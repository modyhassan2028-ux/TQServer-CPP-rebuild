------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]2015万圣节之女巫的南瓜
--Purpose:	2015万圣节之女巫的南瓜
--Creator: 	严振飞
--Created:	2015/07/23
------------------------------------------------------------------------------------
--掩码说明
---[1]	stc(128,66)	记录是否已领取奖励
---[2]	stc(129,28)	记录每天杀真身怪个数


--LOGid 10002306
------------------------------------------------------------------------------------
--命名规范
--Halloween2015_Witch__
------------------------------------------------------------------------------------
--STC掩码表
local tHalloween2015_Witch_Stc = {}
----------------------------------------
---------------------记录是否已领取奖励
	tHalloween2015_Witch_Stc[1] = {}
	tHalloween2015_Witch_Stc[1]["EventData"] = 128
	tHalloween2015_Witch_Stc[1]["TypeData"] = 66
	tHalloween2015_Witch_Stc[1]["Complete"] = 1
	
---------------------记录每天杀真身怪个数
	tHalloween2015_Witch_Stc[2] = {}
	tHalloween2015_Witch_Stc[2]["EventData"] = 129
	tHalloween2015_Witch_Stc[2]["TypeData"] = 28
	tHalloween2015_Witch_Stc[2]["Complete"] = 10


--动态存储表
local tHalloween2015_Witch_DynaGlobal = {}
	tHalloween2015_Witch_DynaGlobal[1] = 50927
	
------------------------------------------------------------------------------------
--活动数据
local tHalloween2015_Witch_Data = {}
	-- 活动时间
	tHalloween2015_Witch_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-10-28 23:59"
	tHalloween2015_Witch_Data["Festival_NowTime"] = "2015-10-29 00:00 2015-11-04 23:59"
	
	--等级，转世设置，满级
	tHalloween2015_Witch_Data["MinLevel"] = 80
	tHalloween2015_Witch_Data["MinMeto"] = 0
	tHalloween2015_Witch_Data["LevMax"] = 140
	
	-- 传送进活动地图
	tHalloween2015_Witch_Data[17055] = {}
	tHalloween2015_Witch_Data[17055]["MapId"] = 3859
	tHalloween2015_Witch_Data[17055]["PosX"] = 167
	tHalloween2015_Witch_Data[17055]["PosY"] = 213
	tHalloween2015_Witch_Data[17055]["BoundX"] = 5
	tHalloween2015_Witch_Data[17055]["BoundY"] = 5

	-- 传送会双龙城
	tHalloween2015_Witch_Data[17056] = {}
	tHalloween2015_Witch_Data[17056]["MapId"] = 1002
	tHalloween2015_Witch_Data[17056]["PosX"] = 275
	tHalloween2015_Witch_Data[17056]["PosY"] = 375
	tHalloween2015_Witch_Data[17056]["BoundX"] = 5
	tHalloween2015_Witch_Data[17056]["BoundY"] = 5

	--自动寻路数据
	tHalloween2015_Witch_Data[3859] = {}
	tHalloween2015_Witch_Data[3859]["PosX"] = 162
	tHalloween2015_Witch_Data[3859]["PosY"] = 217
	tHalloween2015_Witch_Data[3859]["MapId"] = 3859
	tHalloween2015_Witch_Data[3859]["NpcId"] = 17056
	
	-- 桑德拉的南瓜
	tHalloween2015_Witch_Data["PumpkinId"] = 3004666
	tHalloween2015_Witch_Data["PumpkinSaveTime"] = 60
	
	
	--背包空间
	tHalloween2015_Witch_Data["ChkSpace"] = 1
	
	-- 光效数据
	tHalloween2015_Witch_Data["EffectObj"] = "self"
	tHalloween2015_Witch_Data["Effect_1"] = "zf2-e280"

	-- cq_generator表ID
	tHalloween2015_Witch_Data["GenId"] = 17136
	tHalloween2015_Witch_Data["RealId"] = 7586

	--怪物掉落金币
	tHalloween2015_Witch_Data["DropMoney"] = 10000

------------------------------------------------------------------------------------
--活动LOG数据
local tHalloween2015_Witch_Log = {}
	tHalloween2015_Witch_Log["FestivalId"] = 3456
	tHalloween2015_Witch_Log["LogId"] = 10002306
	--（进\出）地图
	tHalloween2015_Witch_Log["ChgMap"] = {}
	tHalloween2015_Witch_Log["ChgMap"][17055] = "0,0,0,0,10002306,1[1],0,0" --进地图
	tHalloween2015_Witch_Log["ChgMap"][17056] = "0,0,0,0,10002306,1[2],0,0" --出地图
	-- 完成任务
	tHalloween2015_Witch_Log["GetReward"] = "0,0,3004666,1,10002306,1[3],0,0"
	-- 获得南瓜
	tHalloween2015_Witch_Log["Pumpkin"] = "0,0,0,0,10002306,2,3004666,1"
	-- 删除南瓜
	tHalloween2015_Witch_Log["DelItem"] = "0,0,3004666,1,10002306,3,0,0"
----------------------------------------几率配置--------------------------------------------
local tHalloween2015_Witch_Probabil = {}
	-- 【迷你捣蛋鬼】
	tHalloween2015_Witch_Probabil[7581] = {}
	tHalloween2015_Witch_Probabil[7581][1] = {}
	tHalloween2015_Witch_Probabil[7581][1]["ItemChanceSum"] = 10000
	-- 60%	没效果
	tHalloween2015_Witch_Probabil[7581][1][1] = {}
	tHalloween2015_Witch_Probabil[7581][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7581][1][1]["ItemChance"] = 6000
	tHalloween2015_Witch_Probabil[7581][1][1]["Item_1"] = 0
	-- 35%	变成小捣蛋鬼
	tHalloween2015_Witch_Probabil[7581][1][2] = {}
	tHalloween2015_Witch_Probabil[7581][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7581][1][2]["ItemChance"] = 3500
	tHalloween2015_Witch_Probabil[7581][1][2]["Item_1"] = 7582
	-- 5%	变成捣蛋鬼真身
	tHalloween2015_Witch_Probabil[7581][1][3] = {}
	tHalloween2015_Witch_Probabil[7581][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7581][1][3]["ItemChance"] = 500
	tHalloween2015_Witch_Probabil[7581][1][3]["Item_1"] = 7586

	-- 【小捣蛋鬼】
	tHalloween2015_Witch_Probabil[7582] = {}
	tHalloween2015_Witch_Probabil[7582][1] = {}
	tHalloween2015_Witch_Probabil[7582][1]["ItemChanceSum"] = 10000
	-- 55%	没效果
	tHalloween2015_Witch_Probabil[7582][1][1] = {}
	tHalloween2015_Witch_Probabil[7582][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7582][1][1]["ItemChance"] = 5500
	tHalloween2015_Witch_Probabil[7582][1][1]["Item_1"] = 0
	-- 35%	变成捣蛋鬼
	tHalloween2015_Witch_Probabil[7582][1][2] = {}
	tHalloween2015_Witch_Probabil[7582][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7582][1][2]["ItemChance"] = 3500
	tHalloween2015_Witch_Probabil[7582][1][2]["Item_1"] = 7583
	-- 10%	变成捣蛋鬼真身
	tHalloween2015_Witch_Probabil[7582][1][3] = {}
	tHalloween2015_Witch_Probabil[7582][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7582][1][3]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7582][1][3]["Item_1"] = 7586

	-- 【捣蛋鬼】
	tHalloween2015_Witch_Probabil[7583] = {}
	tHalloween2015_Witch_Probabil[7583][1] = {}
	tHalloween2015_Witch_Probabil[7583][1]["ItemChanceSum"] = 10000
	-- 45%	没效果
	tHalloween2015_Witch_Probabil[7583][1][1] = {}
	tHalloween2015_Witch_Probabil[7583][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7583][1][1]["ItemChance"] = 4500
	tHalloween2015_Witch_Probabil[7583][1][1]["Item_1"] = 0
	-- 40%	变成成年捣蛋鬼
	tHalloween2015_Witch_Probabil[7583][1][2] = {}
	tHalloween2015_Witch_Probabil[7583][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7583][1][2]["ItemChance"] = 4000
	tHalloween2015_Witch_Probabil[7583][1][2]["Item_1"] = 7584
	-- 15%	变成捣蛋鬼真身
	tHalloween2015_Witch_Probabil[7583][1][3] = {}
	tHalloween2015_Witch_Probabil[7583][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7583][1][3]["ItemChance"] = 1500
	tHalloween2015_Witch_Probabil[7583][1][3]["Item_1"] = 7586

	-- 【成年捣蛋鬼】
	tHalloween2015_Witch_Probabil[7584] = {}
	tHalloween2015_Witch_Probabil[7584][1] = {}
	tHalloween2015_Witch_Probabil[7584][1]["ItemChanceSum"] = 10000
	-- 35%	提示
	tHalloween2015_Witch_Probabil[7584][1][1] = {}
	tHalloween2015_Witch_Probabil[7584][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7584][1][1]["ItemChance"] = 3500
	tHalloween2015_Witch_Probabil[7584][1][1]["Item_1"] = 2005
	-- 45%	变成巨型捣蛋鬼
	tHalloween2015_Witch_Probabil[7584][1][2] = {}
	tHalloween2015_Witch_Probabil[7584][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7584][1][2]["ItemChance"] = 4500
	tHalloween2015_Witch_Probabil[7584][1][2]["Item_1"] = 7585
	-- 20%	变成捣蛋鬼真身
	tHalloween2015_Witch_Probabil[7584][1][3] = {}
	tHalloween2015_Witch_Probabil[7584][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7584][1][3]["ItemChance"] = 2000
	tHalloween2015_Witch_Probabil[7584][1][3]["Item_1"] = 7586

	-- 【巨型捣蛋鬼】
	tHalloween2015_Witch_Probabil[7585] = {}
	tHalloween2015_Witch_Probabil[7585][1] = {}
	tHalloween2015_Witch_Probabil[7585][1]["ItemChanceSum"] = 10000
	-- 40%	提示
	tHalloween2015_Witch_Probabil[7585][1][1] = {}
	tHalloween2015_Witch_Probabil[7585][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7585][1][1]["ItemChance"] = 4000
	tHalloween2015_Witch_Probabil[7585][1][1]["Item_1"] = 2005
	-- 60%	变成捣蛋鬼真身
	tHalloween2015_Witch_Probabil[7585][1][2] = {}
	tHalloween2015_Witch_Probabil[7585][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7585][1][2]["ItemChance"] = 6000
	tHalloween2015_Witch_Probabil[7585][1][2]["Item_1"] = 7586

	-- 【捣蛋鬼真身】
	tHalloween2015_Witch_Probabil[7586] = {}
	tHalloween2015_Witch_Probabil[7586][1] = {}
	tHalloween2015_Witch_Probabil[7586][1]["ItemChanceSum"] = 10000
	-- 50%	掉南瓜
	tHalloween2015_Witch_Probabil[7586][1][1] = {}
	tHalloween2015_Witch_Probabil[7586][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7586][1][1]["ItemChance"] = 5000
	tHalloween2015_Witch_Probabil[7586][1][1]["Item_1"] = 3004666
	-- 20%	随机普通宝石
	tHalloween2015_Witch_Probabil[7586][1][2] = {}
	tHalloween2015_Witch_Probabil[7586][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7586][1][2]["ItemChance"] = 2000
	tHalloween2015_Witch_Probabil[7586][1][2]["Item_1"] = 7587
	-- 15%	掉落流星
	tHalloween2015_Witch_Probabil[7586][1][3] = {}
	tHalloween2015_Witch_Probabil[7586][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7586][1][3]["ItemChance"] = 1500
	tHalloween2015_Witch_Probabil[7586][1][3]["Item_1"] = 1088001
	-- 15%	掉落5W金币
	tHalloween2015_Witch_Probabil[7586][1][4] = {}
	tHalloween2015_Witch_Probabil[7586][1][4]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7586][1][4]["ItemChance"] = 1500
	tHalloween2015_Witch_Probabil[7586][1][4]["Item_1"] = 50000

	
	
	-- 【普通宝石】
	tHalloween2015_Witch_Probabil[7587] = {}
	tHalloween2015_Witch_Probabil[7587][1] = {}
	tHalloween2015_Witch_Probabil[7587][1]["ItemChanceSum"] = 7000
	-- 1/7	普通金麟宝石
	tHalloween2015_Witch_Probabil[7587][1][1] = {}
	tHalloween2015_Witch_Probabil[7587][1][1]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][1]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][1]["Item_1"] = 700041
	-- 1/7	普通青虹宝石
	tHalloween2015_Witch_Probabil[7587][1][2] = {}
	tHalloween2015_Witch_Probabil[7587][1][2]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][2]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][2]["Item_1"] = 700031
	-- 1/7	普通惊鸿宝石
	tHalloween2015_Witch_Probabil[7587][1][3] = {}
	tHalloween2015_Witch_Probabil[7587][1][3]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][3]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][3]["Item_1"] = 700021
	-- 1/7	普通龙恨宝石
	tHalloween2015_Witch_Probabil[7587][1][4] = {}
	tHalloween2015_Witch_Probabil[7587][1][4]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][4]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][4]["Item_1"] = 700011
	-- 1/7	普通凤吟宝石
	tHalloween2015_Witch_Probabil[7587][1][5] = {}
	tHalloween2015_Witch_Probabil[7587][1][5]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][5]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][5]["Item_1"] = 700001
	-- 1/7	普通紫霞宝石
	tHalloween2015_Witch_Probabil[7587][1][6] = {}
	tHalloween2015_Witch_Probabil[7587][1][6]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][6]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][6]["Item_1"] = 700051
	-- 1/7	普通明月宝石
	tHalloween2015_Witch_Probabil[7587][1][7] = {}
	tHalloween2015_Witch_Probabil[7587][1][7]["RandomItemChanceType"] = 2
	tHalloween2015_Witch_Probabil[7587][1][7]["ItemChance"] = 1000
	tHalloween2015_Witch_Probabil[7587][1][7]["Item_1"] = 700061


---------------------------------------NPC函数---------------------------------------------

--传送逻辑
function Halloween2015_Witch_ChgMap(nNpcId)
	local nMapId = tHalloween2015_Witch_Data[nNpcId]["MapId"]
	local nPosX = tHalloween2015_Witch_Data[nNpcId]["PosX"]
	local nPosY = tHalloween2015_Witch_Data[nNpcId]["PosY"]
	local nBoundX = tHalloween2015_Witch_Data[nNpcId]["BoundX"]
	local nBoundY = tHalloween2015_Witch_Data[nNpcId]["BoundY"]
	
	--将玩家传送到地图的指定区域
	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBoundX,nBoundY)
	User_TalkChannel2005(tHalloween2015_Witch_Text[nNpcId]["ChgMap"])
	Sys_SaveActionFestivalLog(tHalloween2015_Witch_Log["ChgMap"][nNpcId])
end

-- 寻路函数
function Halloween2015_Witch_FindWay(nObject)
	local nPosX = tHalloween2015_Witch_Data[nObject]["PosX"]
	local nPosY = tHalloween2015_Witch_Data[nObject]["PosY"]
	local nMapId = tHalloween2015_Witch_Data[nObject]["MapId"]
	local nNpcId = tHalloween2015_Witch_Data[nObject]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end


-----------------------------------【女巫桑德拉】---------------------------------------
-- 传送选项函数
function Halloween2015_Witch_ChgMapOption(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	local nEventData_1 = tHalloween2015_Witch_Stc[1]["EventData"]
	local nTypeData_1 = tHalloween2015_Witch_Stc[1]["TypeData"]
	local nComplete_1 = tHalloween2015_Witch_Stc[1]["Complete"]

	-- 是否已领取奖励
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nComplete_1) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	--判断是否等级不足
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_Witch_Data["MinLevel"],tHalloween2015_Witch_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end

	--传送
	Halloween2015_Witch_ChgMap(nNpcId)
end

-- 我把你的南瓜找回来了！
function Halloween2015_Witch_PayPumpkin(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventData_1 = tHalloween2015_Witch_Stc[1]["EventData"]
	local nTypeData_1 = tHalloween2015_Witch_Stc[1]["TypeData"]
	local nComplete_1 = tHalloween2015_Witch_Stc[1]["Complete"]
	
	-- 是否已领取奖励
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nComplete_1) then
	
		-- 隔天
		if Task_StcInterval(nEventData_1,nTypeData_1,1,4) then
			return
		end
		
		-- 已完成未隔天
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 删除道具
	local nItemId = tHalloween2015_Witch_Data["PumpkinId"]
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Task_SetStatistic(nEventData_1,nTypeData_1,nComplete_1,1)
		Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)
		FestivalGeneralPackage_GetGift(tHalloween2015_Witch_Log["FestivalId"],tHalloween2015_Witch_Log["LogId"])
		User_EffectAdd(tHalloween2015_Witch_Data["EffectObj"],tHalloween2015_Witch_Data["Effect_1"])
		-- User_TalkChannel2005(tHalloween2015_Witch_Text[nNpcId]["GetReward"])
		Sys_SaveActionFestivalLog(tHalloween2015_Witch_Log["GetReward"])
	-- 没有任务道具
	else
		LinkNpcGossipFunc_New(nNpcId,"1-6")
	end
end


---------------------------------------怪物函数---------------------------------------------
-- 普通捣蛋鬼
function Halloween2015_Witch_Monster(nMonsterTypeId)
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		return
	end

	local flat,tItem = Probabil_RandomAward(tHalloween2015_Witch_Probabil[nMonsterTypeId],1)
	local nMonsterId = tItem[1]["tAward"][1]["Item_1"]
	
	-- 没效果
	if nMonsterId == 0 then
		return
	end
	
	-- 只出提示
	if nMonsterId == 2005 then
		User_TalkChannel2005(tHalloween2015_Witch_Text["DescText"])
		return
	end
	
	-- 怪物变大
	local nMapId = Get_UserMapId()
	local nPosX = Get_UserPositionX()
	local nPosY = Get_UserPositionY()
	local nGenId = tHalloween2015_Witch_Data["GenId"]
	local sTalkText = tHalloween2015_Witch_Text["MonsLarger"][nMonsterId]
	Monster_AddMonster(nMapId,nPosX,nPosY,nGenId,nMonsterId)
	User_TalkChannel2005(sTalkText)
end


---------------------------------------
-- 给南瓜函数
function Halloween2015_Witch_GetPumpkin(nEventData_2,nTypeData_2,nComplete_2)
	local nItemId = tHalloween2015_Witch_Data["PumpkinId"]
	
	-- 检查任务道具
	if Item_ChkItem(nItemId) then
		-- 怪物掉落金币
		if not Task_ChkStcValue(nEventData_2,nTypeData_2,">=",nComplete_2) then
			Task_AddStatistic(nEventData_2,nTypeData_2,1,1)
			Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
			Monster_SysDropMoney(tHalloween2015_Witch_Data["DropMoney"])
			return
		else
			return
		end
	end
	
	-- 背包空间
	if not User_CheckLeftSpace(tHalloween2015_Witch_Data["ChkSpace"]) then
		User_TalkChannel2005(tHalloween2015_Witch_Text["SpaceFull"])
		return
	end
	
	-- 给南瓜
	local nSaveTime = tHalloween2015_Witch_Data["PumpkinSaveTime"]
	Task_AddStatistic(nEventData_2,nTypeData_2,1,1)
	Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
	Item_AddItem(nItemId,0,0,0,nSaveTime,1)
	Sys_SaveActionFestivalLog(tHalloween2015_Witch_Log["Pumpkin"])
	User_TalkChannel2005(tHalloween2015_Witch_Text["Pumpkin"])
	Sys_MsgBox(tHalloween2015_Witch_Text["Pumpkin"],"Halloween2015_Witch_FindWay</N>3859")
end



-- 捣蛋鬼真身
function Halloween2015_Witch_MonsterReal(nMonsterTypeId)
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		return
	end
	
	-- 已领取奖励
	local nEventData_1 = tHalloween2015_Witch_Stc[1]["EventData"]
	local nTypeData_1 = tHalloween2015_Witch_Stc[1]["TypeData"]
	local nComplete_1 = tHalloween2015_Witch_Stc[1]["Complete"]
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nComplete_1) then
		-- 已完成，未隔天
		if not Task_StcInterval(nEventData_1,nTypeData_1,1,4) then
			return
			
		-- 已完成，隔天
		else
			Task_SetStatistic(nEventData_1,nTypeData_1,0,1)
			Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)
		end
	end

	-- 超过每天10个限制
	local nEventData_2 = tHalloween2015_Witch_Stc[2]["EventData"]
	local nTypeData_2 = tHalloween2015_Witch_Stc[2]["TypeData"]
	local nComplete_2 = tHalloween2015_Witch_Stc[2]["Complete"]
	if Task_ChkStcValue(nEventData_2,nTypeData_2,">=",nComplete_2) then
		-- 超过，未隔天
		if not Task_StcInterval(nEventData_2,nTypeData_2,1,4) then
			-- 给南瓜
			Halloween2015_Witch_GetPumpkin(nEventData_2,nTypeData_2,nComplete_2)
			return
		else
			Task_SetStatistic(nEventData_2,nTypeData_2,0,1)
			Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
		end
	end
	
	-- 未超过10个限制，走几率
	local flat,tItem = Probabil_RandomAward(tHalloween2015_Witch_Probabil[nMonsterTypeId],1)
	local nProbabil = tItem[1]["tAward"][1]["Item_1"]
	local nPumpkinId = tHalloween2015_Witch_Probabil[7586][1][1]["Item_1"]
	local nGemId = tHalloween2015_Witch_Probabil[7586][1][2]["Item_1"]
	local nMeteorId = tHalloween2015_Witch_Probabil[7586][1][3]["Item_1"]
	local nMoney = tHalloween2015_Witch_Probabil[7586][1][4]["Item_1"]
	
	--为掉落南瓜
	if nProbabil == nPumpkinId then
		-- 给南瓜
		Halloween2015_Witch_GetPumpkin(nEventData_2,nTypeData_2,nComplete_2)
		return
	end
	
	-- 杀怪次数+1
	Task_AddStatistic(nEventData_2,nTypeData_2,1,1)
	Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
	
	-- 为普通宝石
	if nProbabil == nGemId then
		local flat,tItem = Probabil_RandomAward(tHalloween2015_Witch_Probabil[nProbabil],1)
		local nAddGemId = tItem[1]["tAward"][1]["Item_1"]
		Monster_SysDropItem(nAddGemId)
		return
	end
	
	--为掉落流星
	if nProbabil == nMeteorId then
		Monster_SysDropItem(nProbabil)
		return
	end
	
	--为掉落金币
	if nProbabil == nMoney then
		Monster_SysDropMoney(nProbabil)
	end
end



------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[3164] = 175
tNpcFace[3797] = 175
---------------------NPC对话
------------------------------------------
-- 【==女巫桑德拉==】
tNpcGossip[17055] = tNpcGossip[17055] or DefaultNpc:new{}
tNpcGossip[17056] = tNpcGossip[17055] or DefaultNpc:new{}
tNpcGossip[17055]["OptionHidden"] = 1

-- 活动前
tNpcGossip[17055]["Text1-1"] = {111,112,113}
tNpcGossip[17055]["tOption1-1"] = {111}
tNpcGossip[17055]["Text111"] = tHalloween2015_Witch_Text[17055]["Text111"]
tNpcGossip[17055]["Text112"] = tHalloween2015_Witch_Text[17055]["Text112"]
tNpcGossip[17055]["Text113"] = tHalloween2015_Witch_Text[17055]["Text113"]
tNpcGossip[17055]["Option111"] = tHalloween2015_Witch_Text[17055]["Option111"]
tNpcGossip[17055]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_BefTime"])
end

-- 活动后
tNpcGossip[17055]["Text1-2"] = {121,122}
tNpcGossip[17055]["tOption1-2"] = {121}
tNpcGossip[17055]["Text121"] = tHalloween2015_Witch_Text[17055]["Text121"]
tNpcGossip[17055]["Text122"] = tHalloween2015_Witch_Text[17055]["Text122"]
tNpcGossip[17055]["Option121"] = tHalloween2015_Witch_Text[17055]["Option121"]
tNpcGossip[17055]["Option122"] = tHalloween2015_Witch_Text[17055]["Option121"]
tNpcGossip[17055]["OptionFunc122"] = "Halloween2015_Witch_ChgMap</N>17056"
tNpcGossip[17055]["ChkFunc1-2"] = function ()
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		local nMapId = Get_UserMapId()
		
		-- 双城城主NPC
		if nMapId == 1002 then
			tNpcGossip[17055]["tOption1-2"] = {121}
			
		-- 活动地图内主NPC
		else
			tNpcGossip[17055]["tOption1-2"] = {122}
		end
		return true
	else
		return false
	end
end


-- 活动中
tNpcGossip[17055]["Text1-3"] = {131,132,133}
tNpcGossip[17055]["tOption1-3"] = {131,132,133,134,135}
tNpcGossip[17055]["Text131"] = tHalloween2015_Witch_Text[17055]["Text131"]
tNpcGossip[17055]["Text132"] = tHalloween2015_Witch_Text[17055]["Text132"]
tNpcGossip[17055]["Text133"] = tHalloween2015_Witch_Text[17055]["Text133"]
tNpcGossip[17055]["Option131"] = tHalloween2015_Witch_Text[17055]["Option131"]
tNpcGossip[17055]["Option132"] = tHalloween2015_Witch_Text[17055]["Option132"]
tNpcGossip[17055]["Option133"] = tHalloween2015_Witch_Text[17055]["Option133"]
tNpcGossip[17055]["Option134"] = tHalloween2015_Witch_Text[17055]["Option134"]
tNpcGossip[17055]["Option135"] = tHalloween2015_Witch_Text[17055]["Option135"]
tNpcGossip[17055]["OptionFunc131"] = "Halloween2015_Witch_ChgMapOption</N>17055"
tNpcGossip[17055]["OptionFunc132"] = "Halloween2015_Witch_ChgMap</N>17056"
tNpcGossip[17055]["OptionFunc133"] = "Halloween2015_Witch_PayPumpkin</N>17055"
tNpcGossip[17055]["OptionPoint134"] = "2"
tNpcGossip[17055]["ChkFunc1-3"] = function ()
	local nMapId = Get_UserMapId()
	
	-- 双城城主NPC
	if nMapId == 1002 then
		tNpcGossip[17055]["Text1-3"] = {131,132,133}
		tNpcGossip[17055]["tOption1-3"] = {131,133,134,135}
		
	-- 活动地图内主NPC
	else
		tNpcGossip[17055]["Text1-3"] = {131,132}
		tNpcGossip[17055]["tOption1-3"] = {132,133,134,135}
	end
	
	return true
end

tNpcGossip[17055]["OptionChkFunc133"] = function ()
	local nEventData_1 = tHalloween2015_Witch_Stc[1]["EventData"]
	local nTypeData_1 = tHalloween2015_Witch_Stc[1]["TypeData"]
	local nComplete_1 = tHalloween2015_Witch_Stc[1]["Complete"]
	
	-- 是否已领取奖励
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nComplete_1) then
		
		-- 隔天
		if Task_StcInterval(nEventData_1,nTypeData_1,1,4) then
			local nEventData_2 = tHalloween2015_Witch_Stc[2]["EventData"]
			local nTypeData_2 = tHalloween2015_Witch_Stc[2]["TypeData"]
			local nComplete_2 = tHalloween2015_Witch_Stc[2]["Complete"]
			Task_SetStatistic(nEventData_1,nTypeData_1,0,1)
			Task_SetStatistic(nEventData_2,nTypeData_2,0,1)
			Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)
			Task_SetStcTimestamp(nEventData_2,nTypeData_2,0)
		end
	end
	
	return true
end

-- 已领取奖励
tNpcGossip[17055]["Text1-4"] = {141}
tNpcGossip[17055]["tOption1-4"] = {141}
tNpcGossip[17055]["Text141"] = tHalloween2015_Witch_Text[17055]["Text141"]
tNpcGossip[17055]["Option141"] = tHalloween2015_Witch_Text[17055]["Option141"]

-- 等级不足
tNpcGossip[17055]["Text1-5"] = {151}
tNpcGossip[17055]["tOption1-5"] = {151}
tNpcGossip[17055]["Text151"] = tHalloween2015_Witch_Text[17055]["Text151"]
tNpcGossip[17055]["Option151"] = tHalloween2015_Witch_Text[17055]["Option151"]

-- 没有任务道具
tNpcGossip[17055]["Text1-6"] = {161,162}
tNpcGossip[17055]["tOption1-6"] = {161}
tNpcGossip[17055]["Text161"] = tHalloween2015_Witch_Text[17055]["Text161"]
tNpcGossip[17055]["Text162"] = tHalloween2015_Witch_Text[17055]["Text162"]
tNpcGossip[17055]["Option161"] = tHalloween2015_Witch_Text[17055]["Option161"]



-- 【我具体要怎么做呢？】
tNpcGossip[17055]["Text2-1"] = {211,212,213,214}
tNpcGossip[17055]["tOption2-1"] = {211,212}
tNpcGossip[17055]["Text211"] = tHalloween2015_Witch_Text[17055]["Text211"]
tNpcGossip[17055]["Text212"] = tHalloween2015_Witch_Text[17055]["Text212"]
tNpcGossip[17055]["Text213"] = tHalloween2015_Witch_Text[17055]["Text213"]
tNpcGossip[17055]["Text214"] = tHalloween2015_Witch_Text[17055]["Text214"]
tNpcGossip[17055]["Option211"] = tHalloween2015_Witch_Text[17055]["Option211"]
tNpcGossip[17055]["Option212"] = tHalloween2015_Witch_Text[17055]["Option212"]
tNpcGossip[17055]["ChkFunc2-1"] = function ()
	-- 双城城主NPC
	if nMapId == 1002 then
		tNpcGossip[17055]["Text2-1"] = {211,213,214}
		
	-- 活动地图内主NPC
	else
		tNpcGossip[17055]["Text2-1"] = {212,213,214}
	end
	return true
end

-- 紫色的捣蛋鬼真身？
tNpcGossip[17055]["Text2-2"] = {221,222,223}
tNpcGossip[17055]["tOption2-2"] = {221}
tNpcGossip[17055]["Text221"] = tHalloween2015_Witch_Text[17055]["Text221"]
tNpcGossip[17055]["Text222"] = tHalloween2015_Witch_Text[17055]["Text222"]
tNpcGossip[17055]["Text223"] = tHalloween2015_Witch_Text[17055]["Text223"]
tNpcGossip[17055]["Option221"] = tHalloween2015_Witch_Text[17055]["Option221"]
tNpcGossip[17055]["OptionPoint211"] = "2-2"



------------------------------------------------【桑德拉的南瓜】------------------------------------------------
tItem[3004666] = tItem[3004666] or {}
tItem[3004666]["Function"] = function (nItemId,sItemName)
	-- 活动时间
	if not Sys_ChkFullTime(tHalloween2015_Witch_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tHalloween2015_Witch_Text["DelItem"])
			Sys_SaveActionFestivalLog(tHalloween2015_Witch_Log["DelItem"])
		end
		return
	end
	
	-- 活动时间内
	User_TalkChannel2005(tHalloween2015_Witch_Text["NowTime"])
end


-----------------------------------------怪物配置-------------------------------------------
-- 7581	迷你捣蛋鬼
tMonster[7581] = tMonster[7581] or {}
tMonster[7581]["tFunction"] = tMonster[7581]["tFunction"] or {}
table.insert(tMonster[7581]["tFunction"],Halloween2015_Witch_Monster)

-- 7582	小捣蛋鬼
tMonster[7582] = tMonster[7582] or {}
tMonster[7582]["tFunction"] = tMonster[7582]["tFunction"] or {}
table.insert(tMonster[7582]["tFunction"],Halloween2015_Witch_Monster)

-- 7583	捣蛋鬼
tMonster[7583] = tMonster[7583] or {}
tMonster[7583]["tFunction"] = tMonster[7583]["tFunction"] or {}
table.insert(tMonster[7583]["tFunction"],Halloween2015_Witch_Monster)

-- 7584	成年捣蛋鬼
tMonster[7584] = tMonster[7584] or {}
tMonster[7584]["tFunction"] = tMonster[7584]["tFunction"] or {}
table.insert(tMonster[7584]["tFunction"],Halloween2015_Witch_Monster)

-- 7585	巨型捣蛋鬼
tMonster[7585] = tMonster[7585] or {}
tMonster[7585]["tFunction"] = tMonster[7585]["tFunction"] or {}
table.insert(tMonster[7585]["tFunction"],Halloween2015_Witch_Monster)

-- 7585	捣蛋鬼真身
tMonster[7586] = tMonster[7586] or {}
tMonster[7586]["tFunction"] = tMonster[7586]["tFunction"] or {}
table.insert(tMonster[7586]["tFunction"],Halloween2015_Witch_MonsterReal)
