------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]万圣节活动之南瓜大赛
--Purpose:	万圣节活动之南瓜大赛
--Creator: 	郑鋆
--Created:	2015/08/12
------------------------------------------------------------------------------------

-- 命名前缀
-- Halloween2015_PumpkinContest_

-- 掩码说明
-- #stc(128,73) 1今日领取奖励
-- #stc(128,74) 单次上交南瓜总数
-- #stc(129,34) 比赛状态，1 开始。2 完成，时间300秒限制。
-- #stc(129,77) 控制一天就5次奖励

-- 常量表
local tHalloween2015_PumpkinContest_Count = {}
	tHalloween2015_PumpkinContest_Count["BeforeActivityTime"] = "2015-01-22 00:00 2015-10-28 23:59"
	tHalloween2015_PumpkinContest_Count["ActivityTime"] = "2015-10-29 00:00 2015-11-04 23:59"
	tHalloween2015_PumpkinContest_Count["ReceiveTime"] = "2015-10-30 00:00 2015-11-05 23:59"
	tHalloween2015_PumpkinContest_Count["EndRankTime"] = "2015-11-05 00:00 2015-11-05 23:59"
	
	-- 玩家等级要求
	tHalloween2015_PumpkinContest_Count["Metempsychosis"] = 0
	tHalloween2015_PumpkinContest_Count["Level"] = 80
	
	tHalloween2015_PumpkinContest_Count["GlobalId"] = 50630
	tHalloween2015_PumpkinContest_Count["TaskItem"] = 3004677
	-- 南瓜家具
	tHalloween2015_PumpkinContest_Count["Furniture3004678"] = 3004678
	-- 南瓜守护灵家具
	tHalloween2015_PumpkinContest_Count["Furniture3004679"] = 3004679
	tHalloween2015_PumpkinContest_Count["TimeDelay"] = 300
	
	tHalloween2015_PumpkinContest_Count["FestivalId"] = 3456
	tHalloween2015_PumpkinContest_Count["LogId"] = 10002308

-- 动态存储的数据
local tHalloween2015_PumpkinContest_Global = {}
	tHalloween2015_PumpkinContest_Global[1] = {}
	tHalloween2015_PumpkinContest_Global[1]["Time"] = "2015-10-29 00:00 2015-10-29 23:59"
	tHalloween2015_PumpkinContest_Global[1]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_Global[2] = {}
	tHalloween2015_PumpkinContest_Global[2]["Time"] = "2015-10-30 00:00 2015-10-30 23:59"
	tHalloween2015_PumpkinContest_Global[2]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_Global[3] = {}
	tHalloween2015_PumpkinContest_Global[3]["Time"] = "2015-10-31 00:00 2015-10-31 23:59"
	tHalloween2015_PumpkinContest_Global[3]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_Global[4] = {}
	tHalloween2015_PumpkinContest_Global[4]["Time"] = "2015-11-01 00:00 2015-11-01 23:59"
	tHalloween2015_PumpkinContest_Global[4]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_Global[5] = {}
	tHalloween2015_PumpkinContest_Global[5]["Time"] = "2015-11-02 00:00 2015-11-02 23:59"
	tHalloween2015_PumpkinContest_Global[5]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_Global[6] = {}
	tHalloween2015_PumpkinContest_Global[6]["Time"] = "2015-11-03 00:00 2015-11-03 23:59"
	tHalloween2015_PumpkinContest_Global[6]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_Global[7] = {}
	tHalloween2015_PumpkinContest_Global[7]["Time"] = "2015-11-04 00:00 2015-11-04 23:59"
	tHalloween2015_PumpkinContest_Global[7]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_Global[8] = {}
	tHalloween2015_PumpkinContest_Global[8]["Time"] = "2015-11-05 00:00 2015-11-05 23:59"
	tHalloween2015_PumpkinContest_Global[8]["GlobalPos"] = 2
	
-- 隔天清除动态掩码数据
-- 动态存储的数据
local tHalloween2015_PumpkinContest_ClearGlobal = {}
	tHalloween2015_PumpkinContest_ClearGlobal[1] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[1]["AllTime"] = "2015-10-30 00:00 2015-10-30 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[1]["Time"] = "2015-10-30 00:00 2015-10-30 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[1]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_ClearGlobal[2] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[2]["AllTime"] = "2015-10-31 00:00 2015-10-31 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[2]["Time"] = "2015-10-31 00:00 2015-10-31 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[2]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_ClearGlobal[3] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[3]["AllTime"] = "2015-11-01 00:00 2015-11-01 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[3]["Time"] = "2015-11-01 00:00 2015-11-01 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[3]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_ClearGlobal[4] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[4]["AllTime"] = "2015-11-02 00:00 2015-11-02 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[4]["Time"] = "2015-11-02 00:00 2015-11-02 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[4]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_ClearGlobal[5] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[5]["AllTime"] = "2015-11-03 00:00 2015-11-03 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[5]["Time"] = "2015-11-03 00:00 2015-11-03 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[5]["GlobalPos"] = 2
	
	tHalloween2015_PumpkinContest_ClearGlobal[6] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[6]["AllTime"] = "2015-11-04 00:00 2015-11-04 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[6]["Time"] = "2015-11-04 00:00 2015-11-04 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[6]["GlobalPos"] = 0
	
	tHalloween2015_PumpkinContest_ClearGlobal[7] = {}
	tHalloween2015_PumpkinContest_ClearGlobal[7]["AllTime"] = "2015-11-05 00:00 2015-11-05 23:59"
	tHalloween2015_PumpkinContest_ClearGlobal[7]["Time"] = "2015-11-05 00:00 2015-11-05 00:02"
	tHalloween2015_PumpkinContest_ClearGlobal[7]["GlobalPos"] = 2
	
-- stc掩码
local tHalloween2015_PumpkinContest_Stc = {}
	tHalloween2015_PumpkinContest_Stc[1] = {}
	tHalloween2015_PumpkinContest_Stc[1]["EventType"] = 128
	tHalloween2015_PumpkinContest_Stc[1]["DataType"] = 73
	tHalloween2015_PumpkinContest_Stc[1]["RewardData"] = 1
	
	tHalloween2015_PumpkinContest_Stc[2] = {}
	tHalloween2015_PumpkinContest_Stc[2]["EventType"] = 128
	tHalloween2015_PumpkinContest_Stc[2]["DataType"] = 74
	tHalloween2015_PumpkinContest_Stc[2]["RewardData"] = 5
	
	tHalloween2015_PumpkinContest_Stc[3] = {}
	tHalloween2015_PumpkinContest_Stc[3]["EventType"] = 129
	tHalloween2015_PumpkinContest_Stc[3]["DataType"] = 34
	tHalloween2015_PumpkinContest_Stc[3]["BeginData"] = 1
	tHalloween2015_PumpkinContest_Stc[3]["RewardData"] = 2
	
	tHalloween2015_PumpkinContest_Stc[4] = {}
	tHalloween2015_PumpkinContest_Stc[4]["EventType"] = 129
	tHalloween2015_PumpkinContest_Stc[4]["DataType"] = 77
	tHalloween2015_PumpkinContest_Stc[4]["RewardData"] = 5

-- 地图传送点
local tHalloween2015_PumpkinContest_ChgMap = {}
	-- 传送到农场
	tHalloween2015_PumpkinContest_ChgMap[1] = {}
	tHalloween2015_PumpkinContest_ChgMap[1]["MapId"] = 3860
	tHalloween2015_PumpkinContest_ChgMap[1]["PosX"] = 150
	tHalloween2015_PumpkinContest_ChgMap[1]["PosY"] = 208
	tHalloween2015_PumpkinContest_ChgMap[1]["Range"] = 5

	-- 传送到双龙城
	tHalloween2015_PumpkinContest_ChgMap[2] = {}
	tHalloween2015_PumpkinContest_ChgMap[2]["MapId"] = 1002
	tHalloween2015_PumpkinContest_ChgMap[2]["PosX"] = 275
	tHalloween2015_PumpkinContest_ChgMap[2]["PosY"] = 369
	tHalloween2015_PumpkinContest_ChgMap[2]["Range"] = 5

-- 状态表
local tHalloween2015_PumpkinContest_Status = {}
	-- 冰冻状态
	tHalloween2015_PumpkinContest_Status[1197] = {}
	tHalloween2015_PumpkinContest_Status[1197]["Status"] = 56
	tHalloween2015_PumpkinContest_Status[1197]["Power"] = 100
	tHalloween2015_PumpkinContest_Status[1197]["Secs"] = 3
	tHalloween2015_PumpkinContest_Status[1197]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1197]["RemainTime"] = 3
	tHalloween2015_PumpkinContest_Status[1197]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1197]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1197]["Index"] = "Frozen"
	
	-- 灼伤状态
	tHalloween2015_PumpkinContest_Status[1198] = {}
	tHalloween2015_PumpkinContest_Status[1198]["Status"] = 57
	tHalloween2015_PumpkinContest_Status[1198]["Power"] = 100
	tHalloween2015_PumpkinContest_Status[1198]["Secs"] = 5
	tHalloween2015_PumpkinContest_Status[1198]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1198]["RemainTime"] = 5
	tHalloween2015_PumpkinContest_Status[1198]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1198]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1198]["Effect"] = "bgfire"
	tHalloween2015_PumpkinContest_Status[1198]["Index"] = "Burn"
	
	-- 传送飞阵
	tHalloween2015_PumpkinContest_Status[1199] = {}
	tHalloween2015_PumpkinContest_Status[1199]["EffectObj"] = "self"
	tHalloween2015_PumpkinContest_Status[1199]["Effect"] = "movego"
	tHalloween2015_PumpkinContest_Status[1199]["Index"] = "FlyingArray"
	
	-- 飞行状态
	tHalloween2015_PumpkinContest_Status[1200] = {}
	tHalloween2015_PumpkinContest_Status[1200]["Status"] = 22
	tHalloween2015_PumpkinContest_Status[1200]["Power"] = 100
	tHalloween2015_PumpkinContest_Status[1200]["Secs"] = 10
	tHalloween2015_PumpkinContest_Status[1200]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1200]["RemainTime"] = 10
	tHalloween2015_PumpkinContest_Status[1200]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1200]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1200]["Index"] = "Flight"
	
	-- 振奋之劲
	tHalloween2015_PumpkinContest_Status[1201] = {}
	tHalloween2015_PumpkinContest_Status[1201]["Status"] = 18
	tHalloween2015_PumpkinContest_Status[1201]["Power"] = 30020
	tHalloween2015_PumpkinContest_Status[1201]["Secs"] = 10
	tHalloween2015_PumpkinContest_Status[1201]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1201]["RemainTime"] = 10
	tHalloween2015_PumpkinContest_Status[1201]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1201]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1201]["Index"] = "Exciting"
	
	-- 减速毒雾
	tHalloween2015_PumpkinContest_Status[1202] = {}
	tHalloween2015_PumpkinContest_Status[1202]["Status"] = 50
	tHalloween2015_PumpkinContest_Status[1202]["Power"] = 50
	tHalloween2015_PumpkinContest_Status[1202]["Secs"] = 5
	tHalloween2015_PumpkinContest_Status[1202]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1202]["RemainTime"] = 5
	tHalloween2015_PumpkinContest_Status[1202]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1202]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1202]["Index"] = "Decelerat"
	
	-- 眩晕风暴
	tHalloween2015_PumpkinContest_Status[1203] = {}
	tHalloween2015_PumpkinContest_Status[1203]["Status"] = 55
	tHalloween2015_PumpkinContest_Status[1203]["Power"] = 100
	tHalloween2015_PumpkinContest_Status[1203]["Secs"] = 3
	tHalloween2015_PumpkinContest_Status[1203]["Times"] = 1
	tHalloween2015_PumpkinContest_Status[1203]["RemainTime"] = 3
	tHalloween2015_PumpkinContest_Status[1203]["EndTime"] = 1
	tHalloween2015_PumpkinContest_Status[1203]["Recordable"] = 1
	tHalloween2015_PumpkinContest_Status[1203]["Index"] = "Vertigo"
-- 特效
local tHalloween2015_PumpkinContest_Effect = {}

	tHalloween2015_PumpkinContest_Effect[1] = {}
	tHalloween2015_PumpkinContest_Effect[1]["EffectObj"] = "self"
	tHalloween2015_PumpkinContest_Effect[1]["Effect"] = "zf2-e280"
	
	--获得南瓜/提交南瓜
	tHalloween2015_PumpkinContest_Effect[2] = {}
	tHalloween2015_PumpkinContest_Effect[2]["EffectObj"] = "self"
	tHalloween2015_PumpkinContest_Effect[2]["Effect"] = "angelwing6"
	
	--领取奖励
	tHalloween2015_PumpkinContest_Effect[3] = {}
	tHalloween2015_PumpkinContest_Effect[3]["EffectObj"] = "self"
	tHalloween2015_PumpkinContest_Effect[3]["Effect"] = "angelwing"
	
-- 传送飞阵的三个点
local tHalloween2015_PumpkinContest_ChgPos = {}
	tHalloween2015_PumpkinContest_ChgPos[1] = {}
	tHalloween2015_PumpkinContest_ChgPos[1]["CellX"] = 150
	tHalloween2015_PumpkinContest_ChgPos[1]["CellY"] = 72
	
	tHalloween2015_PumpkinContest_ChgPos[2] = {}
	tHalloween2015_PumpkinContest_ChgPos[2]["CellX"] = 142
	tHalloween2015_PumpkinContest_ChgPos[2]["CellY"] = 141
	
	tHalloween2015_PumpkinContest_ChgPos[3] = {}
	tHalloween2015_PumpkinContest_ChgPos[3]["CellX"] = 142
	tHalloween2015_PumpkinContest_ChgPos[3]["CellY"] = 201
	
	tHalloween2015_PumpkinContest_ChgPos["BoundCX"] = 5
	tHalloween2015_PumpkinContest_ChgPos["BoundCY"] = 5
	
-- 生成南瓜守护灵
local tHalloween2015_PumpkinContest_MonsterBorn = {}
	tHalloween2015_PumpkinContest_MonsterBorn["PosX"] = 146
	tHalloween2015_PumpkinContest_MonsterBorn["PosY"] = 70
	tHalloween2015_PumpkinContest_MonsterBorn["GenId"] = 17136
	tHalloween2015_PumpkinContest_MonsterBorn["MonsterId"] = 7587
	
-- 怪物出生地图特效
local tHalloween2015_PumpkinContest_MapEffect = {}
	tHalloween2015_PumpkinContest_MapEffect["PosX"] = 149
	tHalloween2015_PumpkinContest_MapEffect["PosY"] = 70
	tHalloween2015_PumpkinContest_MapEffect["Effect"] = "born"
	
-- 陷阱每分钟刷新位置
local tHalloween2015_PumpkinContest_TrapPos = {}
	tHalloween2015_PumpkinContest_TrapPos[1] = {}
	tHalloween2015_PumpkinContest_TrapPos[1]["TrapID"] = 1197
	tHalloween2015_PumpkinContest_TrapPos[1]["Look"] = 1037
	tHalloween2015_PumpkinContest_TrapPos[1]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[1]["PosX"] = 151
	tHalloween2015_PumpkinContest_TrapPos[1]["PosY"] = 158
	tHalloween2015_PumpkinContest_TrapPos[1]["NewPosX"] = 142
	tHalloween2015_PumpkinContest_TrapPos[1]["NewPosY"] = 178
	
	tHalloween2015_PumpkinContest_TrapPos[2] = {}
	tHalloween2015_PumpkinContest_TrapPos[2]["TrapID"] = 1198
	tHalloween2015_PumpkinContest_TrapPos[2]["Look"] = 1038
	tHalloween2015_PumpkinContest_TrapPos[2]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[2]["PosX"] = 140
	tHalloween2015_PumpkinContest_TrapPos[2]["PosY"] = 146
	tHalloween2015_PumpkinContest_TrapPos[2]["NewPosX"] = 150
	tHalloween2015_PumpkinContest_TrapPos[2]["NewPosY"] = 174
	
	tHalloween2015_PumpkinContest_TrapPos[3] = {}
	tHalloween2015_PumpkinContest_TrapPos[3]["TrapID"] = 1199
	tHalloween2015_PumpkinContest_TrapPos[3]["Look"] = 1039
	tHalloween2015_PumpkinContest_TrapPos[3]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[3]["PosX"] = 151
	tHalloween2015_PumpkinContest_TrapPos[3]["PosY"] = 141
	tHalloween2015_PumpkinContest_TrapPos[3]["NewPosX"] = 147
	tHalloween2015_PumpkinContest_TrapPos[3]["NewPosY"] = 161
	
	tHalloween2015_PumpkinContest_TrapPos[4] = {}
	tHalloween2015_PumpkinContest_TrapPos[4]["TrapID"] = 1200
	tHalloween2015_PumpkinContest_TrapPos[4]["Look"] = 1040
	tHalloween2015_PumpkinContest_TrapPos[4]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[4]["PosX"] = 138
	tHalloween2015_PumpkinContest_TrapPos[4]["PosY"] = 122
	tHalloween2015_PumpkinContest_TrapPos[4]["NewPosX"] = 145
	tHalloween2015_PumpkinContest_TrapPos[4]["NewPosY"] = 140
	
	tHalloween2015_PumpkinContest_TrapPos[5] = {}
	tHalloween2015_PumpkinContest_TrapPos[5]["TrapID"] = 1201
	tHalloween2015_PumpkinContest_TrapPos[5]["Look"] = 1041
	tHalloween2015_PumpkinContest_TrapPos[5]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[5]["PosX"] = 153
	tHalloween2015_PumpkinContest_TrapPos[5]["PosY"] = 115
	tHalloween2015_PumpkinContest_TrapPos[5]["NewPosX"] = 146
	tHalloween2015_PumpkinContest_TrapPos[5]["NewPosY"] = 128
	
	tHalloween2015_PumpkinContest_TrapPos[6] = {}
	tHalloween2015_PumpkinContest_TrapPos[6]["TrapID"] = 1202
	tHalloween2015_PumpkinContest_TrapPos[6]["Look"] = 1042
	tHalloween2015_PumpkinContest_TrapPos[6]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[6]["PosX"] = 141
	tHalloween2015_PumpkinContest_TrapPos[6]["PosY"] = 102
	tHalloween2015_PumpkinContest_TrapPos[6]["NewPosX"] = 144
	tHalloween2015_PumpkinContest_TrapPos[6]["NewPosY"] = 108
	
	tHalloween2015_PumpkinContest_TrapPos[7] = {}
	tHalloween2015_PumpkinContest_TrapPos[7]["TrapID"] = 1203
	tHalloween2015_PumpkinContest_TrapPos[7]["Look"] = 1043
	tHalloween2015_PumpkinContest_TrapPos[7]["MapID"] = 3860
	tHalloween2015_PumpkinContest_TrapPos[7]["PosX"] = 155
	tHalloween2015_PumpkinContest_TrapPos[7]["PosY"] = 89
	tHalloween2015_PumpkinContest_TrapPos[7]["NewPosX"] = 150
	tHalloween2015_PumpkinContest_TrapPos[7]["NewPosY"] = 96
	
	-- 陷阱范围扩大
	tHalloween2015_PumpkinContest_TrapPos["PosCX"] = 2
	tHalloween2015_PumpkinContest_TrapPos["PosCY"] = 2

--------------------------------------逻辑部分-------------------------------------------
-- 送我进农场。
function Halloween2015_PumpkinContest_SendToFarm(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_PumpkinContest_Count["Level"],tHalloween2015_PumpkinContest_Count["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 判断玩家身上是否有南瓜
	if Item_ChkItem(tHalloween2015_PumpkinContest_Count["TaskItem"]) then
		Item_DelAllItemByType(tHalloween2015_PumpkinContest_Count["TaskItem"])
	end
	
	local nMapId = tHalloween2015_PumpkinContest_ChgMap[1]["MapId"]
	local nPosX = tHalloween2015_PumpkinContest_ChgMap[1]["PosX"]
	local nPosY = tHalloween2015_PumpkinContest_ChgMap[1]["PosY"]
	local nRange = tHalloween2015_PumpkinContest_ChgMap[1]["Range"]

	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nRange,nRange)
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text[nNpcId]["ChgMap"])
end

-- 开始比赛
function Halloween2015_PumpkinContest_StartGame(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)

	if nData == tHalloween2015_PumpkinContest_Stc[3]["BeginData"] then
		return
	end
	
	-- 判断玩家身上是否有南瓜
	if Item_ChkItem(tHalloween2015_PumpkinContest_Count["TaskItem"]) then
		Item_DelAllItemByType(tHalloween2015_PumpkinContest_Count["TaskItem"])
	end
	
	-- 设置掩码
	Task_SetStatistic(tHalloween2015_PumpkinContest_Stc[2]["EventType"],tHalloween2015_PumpkinContest_Stc[2]["DataType"],0,1)
	Task_SetStcTimestamp(tHalloween2015_PumpkinContest_Stc[2]["EventType"],tHalloween2015_PumpkinContest_Stc[2]["DataType"],0)
	
	Task_SetStatistic(nEvent,nType,tHalloween2015_PumpkinContest_Stc[3]["BeginData"],1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	-- 打log
	Sys_SaveActionFestivalLog("0,0,0,0,10002308,1[1],0,0")
	
	-- 客户端显示倒计时
	User_SetTimer(tHalloween2015_PumpkinContest_Count["TimeDelay"],"Halloween2015_PumpkinContest_Countdown",1)
	
	Sys_MsgBox(tHalloween2015_PumpkinContest_Text[nNpcId]["Begin"])
end

-- 倒计时到期调用的接口
function Halloween2015_PumpkinContest_Countdown()
	local nEvent = tHalloween2015_PumpkinContest_Stc[2]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[2]["DataType"]
	local nRewardData = tHalloween2015_PumpkinContest_Stc[2]["RewardData"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	
	-- 判断是否完成任务 挑战失败
	if not (nData >= nRewardData) then
		Task_SetStatistic(nStateEvent,nStateType,0,1)
		Task_SetStcTimestamp(nStateEvent,nStateType,0)
		Sys_MsgBox(tHalloween2015_PumpkinContest_Text["Failure"])
		return
	end

	-- 设置任务完成
	Halloween2015_PumpkinContest_SetComplete()
	-- 更新动态存储表
	Halloween2015_PumpkinContest_Update(nData)
end

-- 设置任务完成接口
function Halloween2015_PumpkinContest_SetComplete()
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	
	-- 设置掩码
	Task_SetStatistic(nStateEvent,nStateType,tHalloween2015_PumpkinContest_Stc[3]["RewardData"],1)
	Task_SetStcTimestamp(nStateEvent,nStateType,0)
	-- 打log
	Sys_SaveActionFestivalLog("0,0,0,0,10002308,1[3],0,0")
	
	local nRewardEvent = tHalloween2015_PumpkinContest_Stc[1]["EventType"]
	local nRewardType = tHalloween2015_PumpkinContest_Stc[1]["DataType"]
	
	-- 判断今天是否领取过奖励
	if Task_ChkStcValue(nRewardEvent,nRewardType,">=",tHalloween2015_PumpkinContest_Stc[1]["RewardData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nRewardEvent,nRewardType,1,4) then
			Sys_MsgBox(tHalloween2015_PumpkinContest_Text["AlreadyAward"])
			return
		end
	end
	Sys_MsgBox(tHalloween2015_PumpkinContest_Text["Success"])
	
end

-- 更新动态存储表
function Halloween2015_PumpkinContest_Update(nData)
	local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
	
	for i,v in pairs(tHalloween2015_PumpkinContest_Global) do
		-- 检查服务器当前时间
		if Sys_ChkFullTime(v["Time"]) then  --if Sys_ChkFullTime(v) then
			local nGlobalPos = v["GlobalPos"]
			local nGlobalData = 0
			
			if nGlobalPos == 0 then
				nGlobalData = Get_SysDynaGlobalData0(nGlobalId) 
			else
				nGlobalData = Get_SysDynaGlobalData2(nGlobalId)
			end
			
			-- 刷新第一名数据
			if nGlobalData <= nData then
				Halloween2015_PumpkinContest_SetGlobalData(nGlobalPos,nData)
			end
		end
	end
end

-- 设置动态掩码值的接口
function Halloween2015_PumpkinContest_SetGlobalData(nGlobalPos,nData)
	local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
	local nUserId = Get_UserId()
	local sUserName = Get_UserName(nUserId)
	
	if nGlobalPos == 0 then
		Sys_SetSynaGlobalData0(nGlobalId,nData)
		Sys_SetSynaGlobalData1(nGlobalId,nUserId)
		Sys_SetSynaGlobalDataStr1(nGlobalId,sUserName)
	else
		Sys_SetSynaGlobalData2(nGlobalId,nData)
		Sys_SetSynaGlobalData3(nGlobalId,nUserId)
		Sys_SetSynaGlobalDataStr3(nGlobalId,sUserName)
	end
	
end

-- 获取动态掩码值的接口 nGetMark 1标志为取今日排名数值
function Halloween2015_PumpkinContest_GetGlobalData(nGetType,nGetMark)
	for i,v in pairs(tHalloween2015_PumpkinContest_Global) do
		local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
		if Sys_ChkFullTime(v["Time"]) then
			local nGlobalPos = v["GlobalPos"] 
			local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
			
			--查询今日第一名成绩
			if nGetMark == 1 then
				if nGlobalPos == 0 then
					if nGetType == 1 then
						return Get_SysDynaGlobalData0(nGlobalId)
					elseif nGetType == 2 then
						return Get_SysDynaGlobalData1(nGlobalId)
					elseif nGetType == 3 then
						return Get_SysDynaGlobalDataStr1(nGlobalId)
					end
				else
					if nGetType == 1 then
						return Get_SysDynaGlobalData2(nGlobalId)
					elseif nGetType == 2 then
						return Get_SysDynaGlobalData3(nGlobalId)
					elseif nGetType == 3 then
						return Get_SysDynaGlobalDataStr3(nGlobalId)
					end
				end
			end
			
			-- 领取昨天第一所以数据倒过来取
			if nGlobalPos == 0 then
				if nGetType == 1 then
					return Get_SysDynaGlobalData2(nGlobalId)
				elseif nGetType == 2 then
					return Get_SysDynaGlobalData3(nGlobalId)
				elseif nGetType == 3 then
					return Get_SysDynaGlobalDataStr3(nGlobalId)
				end
			else
				if nGetType == 1 then
					return Get_SysDynaGlobalData0(nGlobalId)
				elseif nGetType == 2 then
					return Get_SysDynaGlobalData1(nGlobalId)
				elseif nGetType == 3 then
					return Get_SysDynaGlobalDataStr1(nGlobalId)
				end
			end
		end
	end
	
	return 0
end

-- 领取奖励
function Halloween2015_PumpkinContest_ReceiveReward(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nRewardEvent = tHalloween2015_PumpkinContest_Stc[1]["EventType"]
	local nRewardType = tHalloween2015_PumpkinContest_Stc[1]["DataType"]
	
	-- 判断今天是否领取过奖励
	if Task_ChkStcValue(nRewardEvent,nRewardType,">=",tHalloween2015_PumpkinContest_Stc[1]["RewardData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nRewardEvent,nRewardType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"2-1")
			return
		end
	end
	
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	
	-- 判断任务是否完成
	-- if not Task_ChkStcValue(nStateEvent,nStateType,">=",tHalloween2015_PumpkinContest_Stc[3]["RewardData"]) then
		-- LinkNpcGossipFunc_New(nNpcId,"2-2")
		-- return
	if Task_StcInterval(nStateEvent,nStateType,1,4) then
		Task_SetStatistic(nStateEvent,nStateType,0,1)
		Task_SetStcTimestamp(nStateEvent,nStateType,0)
		Sys_MsgBox(tHalloween2015_PumpkinContest_Text["NoComplete"])
		return
	end
	
	local nCollectEvent = tHalloween2015_PumpkinContest_Stc[2]["EventType"]
	local nCollectType = tHalloween2015_PumpkinContest_Stc[2]["DataType"]
	
	if Task_ChkStcValue(nCollectEvent,nCollectType,">=",tHalloween2015_PumpkinContest_Stc[2]["RewardData"]) then
		-- 判断隔天
		if Task_StcInterval(nCollectEvent,nCollectType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(2) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 设置掩码
	Task_SetStatistic(nRewardEvent,nRewardType,tHalloween2015_PumpkinContest_Stc[1]["RewardData"],1)
	Task_SetStcTimestamp(nRewardEvent,nRewardType,0)
	
	Item_AddItem(tHalloween2015_PumpkinContest_Count["Furniture3004678"])
	-- 给通用礼包
	FestivalGeneralPackage_GetGift(tHalloween2015_PumpkinContest_Count["FestivalId"],tHalloween2015_PumpkinContest_Count["LogId"])
	
	-- 打log
	Sys_SaveActionFestivalLog("0,0,0,0,10002308,2,3004678,1")
	
	-- 播光效
	User_EffectAdd(tHalloween2015_PumpkinContest_Effect[1]["EffectObj"],tHalloween2015_PumpkinContest_Effect[1]["Effect"])
	
	-- 提示
	Sys_MsgBox(tHalloween2015_PumpkinContest_Text["Reward"])
end

-- 上交南瓜
function Halloween2015_PumpkinContest_HandInItem(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	local nEvent = tHalloween2015_PumpkinContest_Stc[2]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[2]["DataType"]
	
	-- 判断任务状态
	if not Task_ChkStcValue(nStateEvent,nStateType,"==",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		return
	end
	
	local nData = Get_UserStatisticValue(nEvent,nType)
	local nRewardData = tHalloween2015_PumpkinContest_Stc[2]["RewardData"]
	
	-- 判断是否超过300秒
	if Task_StcInterval(nStateEvent,nStateType,tHalloween2015_PumpkinContest_Count["TimeDelay"],0) then
		-- 判断是否完成任务
		if not (nData >= nRewardData) then
			Task_SetStatistic(nStateEvent,nStateType,0,1)
			Task_SetStcTimestamp(nStateEvent,nStateType,0)
			Sys_MsgBox(tHalloween2015_PumpkinContest_Text["Failure"])
			return
		end
		
		-- 设置任务完成
		Halloween2015_PumpkinContest_SetComplete()
		-- 更新动态存储表
		Halloween2015_PumpkinContest_Update(nData)
		return
	end
	
	-- 检测是否有任务物品
	if not Item_ChkItem(tHalloween2015_PumpkinContest_Count["TaskItem"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	if not Item_DelItem(tHalloween2015_PumpkinContest_Count["TaskItem"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--播放光效
	User_EffectAdd(tHalloween2015_PumpkinContest_Effect[2]["EffectObj"],tHalloween2015_PumpkinContest_Effect[2]["Effect"])
	
	-- 设置掩码
	Task_AddStatistic(nEvent,nType,1,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	-- 判断今天是否领取完小奖励
	local nLimitEvent = tHalloween2015_PumpkinContest_Stc[4]["EventType"]
	local nLimitType = tHalloween2015_PumpkinContest_Stc[4]["DataType"]
	
	if Task_ChkStcValue(nLimitEvent,nLimitType,">=",tHalloween2015_PumpkinContest_Stc[4]["RewardData"]) then
		-- 判断是否隔天
		if Task_StcInterval(nLimitEvent,nLimitType,1,4) then
			Task_SetStatistic(nLimitEvent,nLimitType,0,1)
			Task_SetStcTimestamp(nLimitEvent,nLimitType,0)
		else
			local sCount = string.format(tHalloween2015_PumpkinContest_Text["NormalHand"],nData + 1)
			Sys_MsgBox(sCount)
			return
		end
	end
	
	-- 设置掩码
	Task_AddStatistic(nLimitEvent,nLimitType,1,1)
	Task_SetStcTimestamp(nLimitEvent,nLimitType,0)
	
	local nLevel = Get_UserLevel()
	
	if nLevel >= G_User_MaxLev then
		User_AddCultivation(5)
		Sys_SaveActionFestivalLog("0,0,3004677,1,10002308,1[2],6,5")
		
		local sCount = string.format(tHalloween2015_PumpkinContest_Text["CultivatHand"],nData + 1)
		Sys_MsgBox(sCount)
	else
		User_AddExpTime(10)
		Sys_SaveActionFestivalLog("0,0,3004677,1,10002308,1[2],4,10")
		
		local sCount = string.format(tHalloween2015_PumpkinContest_Text["ExpHand"],nData + 1)
		Sys_MsgBox(sCount)
	end
end

-- 领取昨日第一奖励
function Halloween2015_PumpkinContest_ReceiveRankReward(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ReceiveTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nUserId = Get_UserId()
	local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
	-- 获取昨天排第一的玩家ID
	local nGlobalData = Halloween2015_PumpkinContest_GetGlobalData(2)
	
	if nGlobalData == 0 then
		return
	end
	
	-- 判断是否是昨天的第一名
	if nUserId ~= nGlobalData then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	local nGlobalData5 = Get_SysDynaGlobalData5(nGlobalId)
	-- 判断今天是否领取过奖励
	if nGlobalData5 >= 1 then
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-7")
		return
	end
	
	-- 设置动态掩码值
	Sys_SetSynaGlobalData5(nGlobalId,1)
	
	-- 给物品
	Item_AddItem(tHalloween2015_PumpkinContest_Count["Furniture3004679"])
	
	--播放光效
	User_EffectAdd(tHalloween2015_PumpkinContest_Effect[3]["EffectObj"],tHalloween2015_PumpkinContest_Effect[3]["Effect"])
	
	local nLevel = Get_UserLevel(nUserId)
	local sLog = "0,0,0,0,10002308,2,3004679,1"
	local sCount = tHalloween2015_PumpkinContest_Text["Rank"]
	
	if nLevel < G_User_MaxLev then
		User_AddExpTime(500,nUserId)
		sLog = "0,0,0,0,10002308,2,4[3004679],500[1]"
		sCount = tHalloween2015_PumpkinContest_Text["RankExp"]
	end
	
	Sys_SaveActionFestivalLog(sLog)
	Sys_MsgBox(sCount)
end

-- 查询今日第一名成绩
function Halloween2015_PumpkinContest_Query(nNpcId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nGlobalData = Halloween2015_PumpkinContest_GetGlobalData(1,1)
	
	if nGlobalData == 0 then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nUserId = Get_UserId()
	local nGlobalUserId = Halloween2015_PumpkinContest_GetGlobalData(2,1)
	
	if nUserId ~= nGlobalUserId then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
	else
		LinkNpcGossipFunc_New(nNpcId,"3-2")
	end
end

-- 传送回双龙城
function Halloween2015_PumpkinContest_ChgMapShuangLong()
	local nMapId = tHalloween2015_PumpkinContest_ChgMap[2]["MapId"]
	local nPosX = tHalloween2015_PumpkinContest_ChgMap[2]["PosX"]
	local nPosY = tHalloween2015_PumpkinContest_ChgMap[2]["PosY"]
	local nRange = tHalloween2015_PumpkinContest_ChgMap[2]["Range"]

	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nRange,nRange)
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["ChgMap"])
end

-- 采集南瓜
function Halloween2015_PumpkinContest_CollectPumpkin()
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		return
	end
	
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	-- 判断掩码状态
	if not Task_ChkStcValue(nStateEvent,nStateType,"==",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		Sys_MsgBox(tHalloween2015_PumpkinContest_Text["NotRegistered"])
		return
	end
	
	local nMapId = Get_UserMapId()
	local sMonsterName = tHalloween2015_PumpkinContest_Text["MonsterName"]
	local nMonsterNum = Monster_GetMonsterByName(nMapId,sMonsterName)
	
	-- 判断是否有南瓜守护灵
	if nMonsterNum > 0 then
		Sys_MsgBox(tHalloween2015_PumpkinContest_Text["HaveMonster"])
		return
	end
	
	local nNpcId = Get_NpcId()
	local nPosX = Get_NpcPositionX(nNpcId)
	local nPosY = Get_NpcPositionY(nNpcId)
	Map_Effect(nMapId,nPosX,nPosY,"angelwing")
	
	local nMonsterPosX = tHalloween2015_PumpkinContest_MonsterBorn["PosX"]
	local nMonsterPosY = tHalloween2015_PumpkinContest_MonsterBorn["PosY"]
	local nMonsterGenId = tHalloween2015_PumpkinContest_MonsterBorn["GenId"]
	local nMonsterID = tHalloween2015_PumpkinContest_MonsterBorn["MonsterId"]
	
	local nMapEffectPosX = tHalloween2015_PumpkinContest_MapEffect["PosX"]
	local nMapEffectPosY = tHalloween2015_PumpkinContest_MapEffect["PosY"]
	local nMapEffectName = tHalloween2015_PumpkinContest_MapEffect["Effect"]
	
	if Sys_Random(100,1000) then
		-- 生成南瓜守护灵
		Monster_AddMonster(nMapId,nMonsterPosX,nMonsterPosY,nMonsterGenId,nMonsterID)
		Map_Effect(nMapId,nMapEffectPosX,nMapEffectPosY,nMapEffectName)
		Sys_MsgBox(tHalloween2015_PumpkinContest_Text["HaveMonster"])
		return
	end
	
	Halloween2015_PumpkinContest_RewardTaskItem()
end

-- 获得南瓜
function Halloween2015_PumpkinContest_RewardTaskItem()
	-- 检测身上是否有南瓜
	if Item_ChkItem(tHalloween2015_PumpkinContest_Count["TaskItem"]) then
		User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["HaveTaskItem"])
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["NoSpace"])
		return
	end
	
	Item_AddItem(tHalloween2015_PumpkinContest_Count["TaskItem"])
	
	--播放光效
	User_EffectAdd(tHalloween2015_PumpkinContest_Effect[2]["EffectObj"],tHalloween2015_PumpkinContest_Effect[2]["Effect"])
	
	Sys_SaveActionFestivalLog("0,0,0,0,10002308,2,3004677,1")
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["RewardItem"])
end

-- 怪物死亡
function Halloween2015_PumpkinContest_KillMonster()
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		return
	end
	
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	-- 判断掩码状态
	if not Task_ChkStcValue(nStateEvent,nStateType,"==",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		return
	end
	
	if Sys_Random(100,1000) then
		local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
		local nGlobalData = Get_SysDynaGlobalData4(nGlobalId)
		
		if nGlobalData < 5 then
			Sys_SetSynaGlobalData4(nGlobalId,nGlobalData + 1)
			Halloween2015_PumpkinContest_RewardTaskItem()
		end
	end
end

-- 陷阱触发
function Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
	local nStatus = tHalloween2015_PumpkinContest_Status[nTrapType]["Status"]
	local nPower = tHalloween2015_PumpkinContest_Status[nTrapType]["Power"]
	local nSecs = tHalloween2015_PumpkinContest_Status[nTrapType]["Secs"]
	local nTimes = tHalloween2015_PumpkinContest_Status[nTrapType]["Times"]
	local nRemainTime = tHalloween2015_PumpkinContest_Status[nTrapType]["RemainTime"]
	local nEndTime = tHalloween2015_PumpkinContest_Status[nTrapType]["EndTime"]
	local nRecordable = tHalloween2015_PumpkinContest_Status[nTrapType]["Recordable"]	
	local sIndex = tHalloween2015_PumpkinContest_Status[nTrapType]["Index"]
	local sEffect = tHalloween2015_PumpkinContest_Status[nTrapType]["Effect"]
	local nUserId = Get_UserId()
	
	User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
	
	if sEffect ~= nil then
		User_EffectAdd("self",sEffect)
	end
	
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text[sIndex])
	Trap_EraseMapTrap()
end

-- 传送飞阵
function Halloween2015_PumpkinContest_FlyingArray(nTrapId,nTrapType)
	local sEffectObj = tHalloween2015_PumpkinContest_Status[nTrapType]["EffectObj"]
	local sEffect = tHalloween2015_PumpkinContest_Status[nTrapType]["Effect"]
	local sIndex = tHalloween2015_PumpkinContest_Status[nTrapType]["Index"]
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text[sIndex])
	User_EffectAdd(sEffectObj,sEffect)
	
	local nMapId = Get_UserMapId()
	
	-- 标志要去的其中一个点的mark
	local nMarkTrans = 0
	if Sys_Random(1000,3000) then
		nMarkTrans = 1
	elseif Sys_Random(1000,3000) then
		nMarkTrans = 2
	else
		nMarkTrans = 3
	end
	
	local nTransCellX = tHalloween2015_PumpkinContest_ChgPos[nMarkTrans]["CellX"]
	local nTransCellY = tHalloween2015_PumpkinContest_ChgPos[nMarkTrans]["CellY"]
	local nTransBoundCX = tHalloween2015_PumpkinContest_ChgPos["BoundCX"]
	local nTransBoundCY = tHalloween2015_PumpkinContest_ChgPos["BoundCY"]
	
	User_UserRandBoundTrans(nMapId,nTransCellX,nTransCellY,nTransBoundCX,nTransBoundCY)
	
	-- 删除一个陷阱
	Trap_EraseMapTrap()
end

-- 物品使用
function Halloween2015_PumpkinContest_UseItem(nItemId)
	-- 判断是否在活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(string.format("0,0,%s,1,10002308,1,0,0",tostring(nItemId)))
		User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["ItemOverdue"])
		return
	end
	
	User_TalkChannel2005(tHalloween2015_PumpkinContest_Text["ItemUse3004677"])
	
end

--时间自检
--每分钟刷陷阱
function Halloween2015_PumpkinContest_RefreshTrap()
	--删除同类型的陷阱 创建两个陷阱
	if Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"]) then
		for i,v in ipairs(tHalloween2015_PumpkinContest_TrapPos) do
			local nTrapID = tHalloween2015_PumpkinContest_TrapPos[i]["TrapID"]
			local nLook = tHalloween2015_PumpkinContest_TrapPos[i]["Look"]
			local nMapID = tHalloween2015_PumpkinContest_TrapPos[i]["MapID"]
			local nPosX = tHalloween2015_PumpkinContest_TrapPos[i]["PosX"]
			local nPosY = tHalloween2015_PumpkinContest_TrapPos[i]["PosY"]
			local nNewPosX = tHalloween2015_PumpkinContest_TrapPos[i]["NewPosX"]
			local nNewPosY = tHalloween2015_PumpkinContest_TrapPos[i]["NewPosY"]
			local nPosCX = tHalloween2015_PumpkinContest_TrapPos["PosCX"]
			local nPosCY = tHalloween2015_PumpkinContest_TrapPos["PosCY"]
			
			if Trap_DelMapTrap(nMapID,nTrapID) then
				Trap_CreateMapTrap(nTrapID,nLook,0,nMapID,nPosX,nPosY,nPosCX,nPosCX)
				Trap_CreateMapTrap(nTrapID,nLook,0,nMapID,nNewPosX,nNewPosY,nPosCX,nPosCX)
			end
		end
	end
end

--动态掩码的清理
--29、31、2、4data0 最大数量，data1玩家id ，datastr1玩家名字
--30、1、3 data2 最大数量，data3玩家id ，datastr3玩家名字
function Halloween2015_PumpkinContest_ClearGlobalData()
	for i,v in pairs(tHalloween2015_PumpkinContest_ClearGlobal) do
		local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
		local nGlobalPos = v["GlobalPos"]
		local sDataStr5 = Get_SysDynaGlobalDataStr5(nGlobalId)
		
		if Sys_ChkFullTime(v["AllTime"]) then
			if Sys_ChkFullTime(v["Time"]) then 
				if not (sDataStr5 == "1") then
					Sys_SetSynaGlobalDataStr5(nGlobalId,"1")
					if nGlobalPos == 0 then
						Sys_SetSynaGlobalData0(nGlobalId,0)
						Sys_SetSynaGlobalData1(nGlobalId,0)
						Sys_SetSynaGlobalDataStr1(nGlobalId,"0")
					else
						Sys_SetSynaGlobalData2(nGlobalId,0)
						Sys_SetSynaGlobalData3(nGlobalId,0)
						Sys_SetSynaGlobalDataStr3(nGlobalId,"0")
					end
					Sys_SetSynaGlobalData4(nGlobalId,0)
					Sys_SetSynaGlobalData5(nGlobalId,0)
				end
			else
				if sDataStr5 == "1" then
					Sys_SetSynaGlobalDataStr5(nGlobalId,"0")
				end
			end
		end
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 军方蔬菜供应商大瓜
tNpcFace[3166] = 60
tNpcGossip[17058] = tNpcGossip[17058] or DefaultNpc:new{}
tNpcGossip[17058]["OptionHidden"] = 1
-- 活动前
tNpcGossip[17058]["Text1-1"] = {111,112,113}
tNpcGossip[17058]["Text111"] = tHalloween2015_PumpkinContest_Text[17058]["111"]
tNpcGossip[17058]["Text112"] = tHalloween2015_PumpkinContest_Text[17058]["112"]
tNpcGossip[17058]["Text113"] = tHalloween2015_PumpkinContest_Text[17058]["113"]
tNpcGossip[17058]["tOption1-1"] = {1}
tNpcGossip[17058]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["BeforeActivityTime"])
end	

tNpcGossip[17058]["Option1"] = tHalloween2015_PumpkinContest_Text[17058]["Option1"]

-- 活动中
tNpcGossip[17058]["Text1-2"] = {121,122}
tNpcGossip[17058]["Text121"] = tHalloween2015_PumpkinContest_Text[17058]["121"]
tNpcGossip[17058]["Text122"] = tHalloween2015_PumpkinContest_Text[17058]["122"]
tNpcGossip[17058]["tOption1-2"] = {2,3,4}
tNpcGossip[17058]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"])
end	

tNpcGossip[17058]["Option2"] = tHalloween2015_PumpkinContest_Text[17058]["Option2"]
tNpcGossip[17058]["OptionFunc2"]="Halloween2015_PumpkinContest_SendToFarm</N>17058"
tNpcGossip[17058]["Option3"] = tHalloween2015_PumpkinContest_Text[17058]["Option3"]
tNpcGossip[17058]["OptionPoint3"]="2-1"
tNpcGossip[17058]["Option4"] = tHalloween2015_PumpkinContest_Text[17058]["Option4"]

-- 活动后
tNpcGossip[17058]["Text1-3"] = {131}
tNpcGossip[17058]["Text131"] = tHalloween2015_PumpkinContest_Text[17058]["131"]
tNpcGossip[17058]["tOption1-3"] = {5,6}
tNpcGossip[17058]["Option5"] = tHalloween2015_PumpkinContest_Text[17058]["Option5"]
tNpcGossip[17058]["OptionFunc5"]="Halloween2015_PumpkinContest_ReceiveRankReward</N>17058"
tNpcGossip[17058]["OptionChkFunc5"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["EndRankTime"])
end
tNpcGossip[17058]["Option6"] = tHalloween2015_PumpkinContest_Text[17058]["Option6"]

tNpcGossip[17058]["Text2-1"] = {211,212,213,214}
tNpcGossip[17058]["Text211"] = tHalloween2015_PumpkinContest_Text[17058]["211"]
tNpcGossip[17058]["Text212"] = tHalloween2015_PumpkinContest_Text[17058]["212"]
tNpcGossip[17058]["Text213"] = tHalloween2015_PumpkinContest_Text[17058]["213"]
tNpcGossip[17058]["Text214"] = tHalloween2015_PumpkinContest_Text[17058]["214"]
tNpcGossip[17058]["tOption2-1"] = {7,8}
tNpcGossip[17058]["Option7"] = tHalloween2015_PumpkinContest_Text[17058]["Option7"]
tNpcGossip[17058]["OptionPoint7"]="1"
tNpcGossip[17058]["Option8"] = tHalloween2015_PumpkinContest_Text[17058]["Option8"]

tNpcGossip[17058]["Text2-5"] = {251}
tNpcGossip[17058]["Text251"] = tHalloween2015_PumpkinContest_Text[17059]["251"]
tNpcGossip[17058]["tOption2-5"] = {14}
tNpcGossip[17058]["Option14"] = tHalloween2015_PumpkinContest_Text[17059]["Option14"]

tNpcGossip[17058]["Text2-6"] = {261}
tNpcGossip[17058]["Text261"] = tHalloween2015_PumpkinContest_Text[17059]["261"]
tNpcGossip[17058]["tOption2-6"] = {15}
tNpcGossip[17058]["Option15"] = tHalloween2015_PumpkinContest_Text[17059]["Option15"]

tNpcGossip[17058]["Text2-7"] = {271}
tNpcGossip[17058]["Text271"] = tHalloween2015_PumpkinContest_Text[17059]["271"]
tNpcGossip[17058]["tOption2-7"] = {16}
tNpcGossip[17058]["Option16"] = tHalloween2015_PumpkinContest_Text[17059]["Option16"]

tNpcGossip[17058]["Text3-1"] = {311}
tNpcGossip[17058]["Text311"] = tHalloween2015_PumpkinContest_Text[17058]["311"]
tNpcGossip[17058]["tOption3-1"] = {9}
tNpcGossip[17058]["Option9"] = tHalloween2015_PumpkinContest_Text[17058]["Option9"]

---------------------------------------------------------------------------- 小瓜
tNpcFace[3167] = 60
tNpcGossip[17059] = tNpcGossip[17059] or DefaultNpc:new{}
tNpcGossip[17059]["OptionHidden"] = 1
-- 活动前
tNpcGossip[17059]["Text1-1"] = {111,112,113}
tNpcGossip[17059]["Text111"] = tHalloween2015_PumpkinContest_Text[17058]["111"]
tNpcGossip[17059]["Text112"] = tHalloween2015_PumpkinContest_Text[17058]["112"]
tNpcGossip[17059]["Text113"] = tHalloween2015_PumpkinContest_Text[17058]["113"]
tNpcGossip[17059]["tOption1-1"] = {1}
tNpcGossip[17059]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["BeforeActivityTime"])
end	

tNpcGossip[17059]["Option1"] = tHalloween2015_PumpkinContest_Text[17058]["Option1"]

-- 活动中
tNpcGossip[17059]["Text1-2"] = {121,122}
tNpcGossip[17059]["Text121"] = tHalloween2015_PumpkinContest_Text[17059]["121"]
tNpcGossip[17059]["Text122"] = tHalloween2015_PumpkinContest_Text[17059]["122"]
tNpcGossip[17059]["tOption1-2"] = {2,3,4,5,6,7,8}
tNpcGossip[17059]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ActivityTime"])
end	

tNpcGossip[17059]["Option2"] = tHalloween2015_PumpkinContest_Text[17059]["Option2"]
tNpcGossip[17059]["OptionFunc2"]="Halloween2015_PumpkinContest_StartGame</N>17059"
tNpcGossip[17059]["OptionChkFunc2"] = function ()
	local nEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]

	if Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["RewardData"]) then
		return true
	elseif not Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		return true
	end
	
	return false
end

tNpcGossip[17059]["Option3"] = tHalloween2015_PumpkinContest_Text[17059]["Option3"]
tNpcGossip[17059]["OptionFunc3"]="Halloween2015_PumpkinContest_ReceiveReward</N>17059"
tNpcGossip[17059]["OptionChkFunc3"] = function ()
	local nStateEvent = tHalloween2015_PumpkinContest_Stc[2]["EventType"]
	local nStateType = tHalloween2015_PumpkinContest_Stc[2]["DataType"]
	
	local nEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]
	
	if Task_ChkStcValue(nStateEvent,nStateType,">=",tHalloween2015_PumpkinContest_Stc[2]["RewardData"]) then
		return true
	end
	
	if Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["RewardData"]) then
		return true
	elseif not Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		return true
	end
	
	return false
end

tNpcGossip[17059]["Option4"] = tHalloween2015_PumpkinContest_Text[17059]["Option4"]
tNpcGossip[17059]["OptionFunc4"]="Halloween2015_PumpkinContest_HandInItem</N>17059"
tNpcGossip[17059]["OptionChkFunc4"] = function ()
	local nEvent = tHalloween2015_PumpkinContest_Stc[3]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[3]["DataType"]

	if Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["RewardData"]) then
		return false
	elseif Task_ChkStcValue(nEvent,nType,">=",tHalloween2015_PumpkinContest_Stc[3]["BeginData"]) then
		return true
	end
	
	return false
end
tNpcGossip[17059]["Option5"] = tHalloween2015_PumpkinContest_Text[17059]["Option5"]
tNpcGossip[17059]["OptionFunc5"]="Halloween2015_PumpkinContest_ReceiveRankReward</N>17059"
tNpcGossip[17059]["OptionChkFunc5"] = function ()
	if not Sys_ChkFullTime(tHalloween2015_PumpkinContest_Count["ReceiveTime"]) then
		return false
	end
	
	local nGlobalId = tHalloween2015_PumpkinContest_Count["GlobalId"]
	local nData = Get_SysDynaGlobalData5(nGlobalId)
	
	
	if nData >= 1 then
		return false
	end
	
	local nUserId = Get_UserId()
	-- 获取昨天排第一的玩家ID
	local nGlobalData = Halloween2015_PumpkinContest_GetGlobalData(2)
	
	if nGlobalData == 0 then
		return
	end
	
	return true
end

tNpcGossip[17059]["Option6"] = tHalloween2015_PumpkinContest_Text[17059]["Option6"]
tNpcGossip[17059]["OptionFunc6"]="Halloween2015_PumpkinContest_Query</N>17059"
tNpcGossip[17059]["Option7"] = tHalloween2015_PumpkinContest_Text[17059]["Option7"]
tNpcGossip[17059]["OptionPoint7"]="4-1"
tNpcGossip[17059]["Option8"] = tHalloween2015_PumpkinContest_Text[17059]["Option8"]
tNpcGossip[17059]["OptionFunc8"]="Halloween2015_PumpkinContest_ChgMapShuangLong"

-- 活动后
tNpcGossip[17059]["Text1-3"] = {131}
tNpcGossip[17059]["Text131"] = tHalloween2015_PumpkinContest_Text[17059]["131"]
tNpcGossip[17059]["tOption1-3"] = {9}
tNpcGossip[17059]["Option9"] = tHalloween2015_PumpkinContest_Text[17059]["Option9"]
tNpcGossip[17059]["OptionFunc9"]="Halloween2015_PumpkinContest_ChgMapShuangLong"

tNpcGossip[17059]["Text2-1"] = {211}
tNpcGossip[17059]["Text211"] = tHalloween2015_PumpkinContest_Text[17059]["211"]
tNpcGossip[17059]["tOption2-1"] = {10}
tNpcGossip[17059]["Option10"] = tHalloween2015_PumpkinContest_Text[17059]["Option10"]

tNpcGossip[17059]["Text2-2"] = {221}
tNpcGossip[17059]["Text221"] = tHalloween2015_PumpkinContest_Text[17059]["221"]
tNpcGossip[17059]["tOption2-2"] = {11}
tNpcGossip[17059]["Option11"] = tHalloween2015_PumpkinContest_Text[17059]["Option11"]

tNpcGossip[17059]["Text2-3"] = {231}
tNpcGossip[17059]["Text231"] = tHalloween2015_PumpkinContest_Text[17059]["231"]
tNpcGossip[17059]["tOption2-3"] = {12}
tNpcGossip[17059]["Option12"] = tHalloween2015_PumpkinContest_Text[17059]["Option12"]

tNpcGossip[17059]["Text2-4"] = {241}
tNpcGossip[17059]["Text241"] = tHalloween2015_PumpkinContest_Text[17059]["241"]
tNpcGossip[17059]["tOption2-4"] = {13}
tNpcGossip[17059]["Option13"] = tHalloween2015_PumpkinContest_Text[17059]["Option13"]
tNpcGossip[17059]["ChkFunc2-4"] = function ()
	local nEvent = tHalloween2015_PumpkinContest_Stc[2]["EventType"]
	local nType = tHalloween2015_PumpkinContest_Stc[2]["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	tNpcGossip[17059]["Text241"] = string.format(tHalloween2015_PumpkinContest_Text[17059]["241"],nData)
	return true
end

tNpcGossip[17059]["Text2-5"] = {251}
tNpcGossip[17059]["Text251"] = tHalloween2015_PumpkinContest_Text[17059]["251"]
tNpcGossip[17059]["tOption2-5"] = {14}
tNpcGossip[17059]["Option14"] = tHalloween2015_PumpkinContest_Text[17059]["Option14"]

tNpcGossip[17059]["Text2-6"] = {261}
tNpcGossip[17059]["Text261"] = tHalloween2015_PumpkinContest_Text[17059]["261"]
tNpcGossip[17059]["tOption2-6"] = {15}
tNpcGossip[17059]["Option15"] = tHalloween2015_PumpkinContest_Text[17059]["Option15"]

tNpcGossip[17059]["Text2-7"] = {271}
tNpcGossip[17059]["Text271"] = tHalloween2015_PumpkinContest_Text[17059]["271"]
tNpcGossip[17059]["tOption2-7"] = {16}
tNpcGossip[17059]["Option16"] = tHalloween2015_PumpkinContest_Text[17059]["Option16"]

tNpcGossip[17059]["Text3-1"] = {311}
tNpcGossip[17059]["Text311"] = tHalloween2015_PumpkinContest_Text[17059]["311"]
tNpcGossip[17059]["tOption3-1"] = {17}
tNpcGossip[17059]["Option17"] = tHalloween2015_PumpkinContest_Text[17059]["Option17"]

tNpcGossip[17059]["Text3-2"] = {321}
tNpcGossip[17059]["Text321"] = tHalloween2015_PumpkinContest_Text[17059]["321"]
tNpcGossip[17059]["tOption3-2"] = {18}
tNpcGossip[17059]["Option18"] = tHalloween2015_PumpkinContest_Text[17059]["Option18"]
tNpcGossip[17059]["ChkFunc3-2"] = function ()
	local nData = Halloween2015_PumpkinContest_GetGlobalData(1,1)
	
	tNpcGossip[17059]["Text321"] = string.format(tHalloween2015_PumpkinContest_Text[17059]["321"],nData)
	return true
end

tNpcGossip[17059]["Text3-3"] = {331}
tNpcGossip[17059]["Text331"] = tHalloween2015_PumpkinContest_Text[17059]["331"]
tNpcGossip[17059]["tOption3-3"] = {19}
tNpcGossip[17059]["Option19"] = tHalloween2015_PumpkinContest_Text[17059]["Option19"]
tNpcGossip[17059]["ChkFunc3-3"] = function ()
	local nData = Halloween2015_PumpkinContest_GetGlobalData(1,1)
	local sUserName = Halloween2015_PumpkinContest_GetGlobalData(3,1)
	
	tNpcGossip[17059]["Text331"] = string.format(tHalloween2015_PumpkinContest_Text[17059]["331"],sUserName,nData)
	return true
end

tNpcGossip[17059]["Text4-1"] = {411}
tNpcGossip[17059]["Text411"] = tHalloween2015_PumpkinContest_Text[17059]["411"]
tNpcGossip[17059]["tOption4-1"] = {20,21}
tNpcGossip[17059]["Option20"] = tHalloween2015_PumpkinContest_Text[17059]["Option20"]
tNpcGossip[17059]["OptionPoint20"]="1"
tNpcGossip[17059]["Option21"] = tHalloween2015_PumpkinContest_Text[17059]["Option21"]

-------------------------------------物品使用模块-----------------------------------
-- 南瓜
tItem[3004677] = tItem[3004677] or {}
tItem[3004677]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinContest_Count["TaskItem"]
	
	Halloween2015_PumpkinContest_UseItem(nItemId)
end

-- 家具暂时不写lua
-- 南瓜家具
-- tItem[3004678] = tItem[3004678] or {}
-- tItem[3004678]["Function"] = function(nItemId,sItemName)
	-- local nItemId = tHalloween2015_PumpkinContest_Count["Furniture3004678"]
	
	-- Halloween2015_PumpkinContest_UseItem(nItemId)
-- end

-- 南瓜守护灵家具
-- tItem[3004679] = tItem[3004679] or {}
-- tItem[3004679]["Function"] = function(nItemId,sItemName)
	-- local nItemId = tHalloween2015_PumpkinContest_Count["Furniture3004679"]
	
	-- Halloween2015_PumpkinContest_UseItem(nItemId)
-- end

-------------------------------怪物模块-------------------------------------------------------------------------------
--7587   南瓜守护灵
tMonster[7587] = tMonster[7587] or {}
tMonster[7587]["tFunction"] = tMonster[7587]["tFunction"] or {}
table.insert(tMonster[7587]["tFunction"],Halloween2015_PumpkinContest_KillMonster)


--------------------------------------陷阱模块-------------------------------------------
tTrap[1197] = tTrap[1197] or {}
tTrap[1197]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end

tTrap[1198] = tTrap[1198] or {}
tTrap[1198]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end

tTrap[1199] = tTrap[1199] or {}
tTrap[1199]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_FlyingArray(nTrapId,nTrapType)
end

tTrap[1200] = tTrap[1200] or {}
tTrap[1200]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end

tTrap[1201] = tTrap[1201] or {}
tTrap[1201]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end

tTrap[1202] = tTrap[1202] or {}
tTrap[1202]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end

tTrap[1203] = tTrap[1203] or {}
tTrap[1203]["Function"] = function(nTrapId,nTrapType)
	Halloween2015_PumpkinContest_Trap(nTrapId,nTrapType)
end
---------------------------------------------时间自检--------------------------------------------
---活动时间：2015-10-29 00:00 2015-11-04 23:59

--tSystem_Prompet_Func		实时检测
table.insert(tSystem_Prompet_Func,Halloween2015_PumpkinContest_RefreshTrap)

table.insert(tSystem_Prompet_Func,Halloween2015_PumpkinContest_ClearGlobalData)
--tOntimerMin_HM	小时/分钟（每天的00点00分到00点02分执行）
--'00:00-00:02'
-- tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
-- table.insert(tOntimerMin_HM[0000],Halloween2015_PumpkinContest_ClearGlobalData)
-- tOntimerMin_HM[0001] = tOntimerMin_HM[0001] or {}
-- table.insert(tOntimerMin_HM[0001],Halloween2015_PumpkinContest_ClearGlobalData)
-- tOntimerMin_HM[0002] = tOntimerMin_HM[0002] or {}
-- table.insert(tOntimerMin_HM[0002],Halloween2015_PumpkinContest_ClearGlobalData)




