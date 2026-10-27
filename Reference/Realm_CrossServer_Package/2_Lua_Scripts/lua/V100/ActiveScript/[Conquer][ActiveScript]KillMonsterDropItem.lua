------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]打怪掉宝活动
--Purpose:	打怪掉宝活动
--Creator: 	郑鋆
--Created:	2015/05/10
------------------------------------------------------------------------------------

-- 命名前缀
-- KillMonsterDropItem_

-- 掩码说明
-- 134	89		记录10分钟经验礼包的次数
-- 134	90		记录30分钟经验礼包的次数
-- 134	91		记录50分钟经验礼包的次数
-- 134	92		记录杀怪的积分
-- 134	95		记录玩家的九幽积分
-- 134	96		记录玩家的兑换气力的次数
-- 134	97		记录玩家选择兑换的选项
-- 134	98		记录玩家杀怪的数量
-- 134	99		记录玩家是否领取过宝箱的奖励

-- 动态存储表说明
-- 50872	data0	记录10修行值礼包掉落数量
-- 50872	data1	记录30修行值礼包掉落数量
-- 50872	data2	记录50修行值礼包掉落数量
-- 50872	data3	记录10气力礼包掉落数量
-- 50872	data4	记录30气力礼包掉落数量
-- 50872	data5	记录50气力礼包掉落数量

-- 50873	data0	记录护心丹礼包掉落数量
-- 50873	data1	记录通神丹礼包掉落数量
-- 50873	data2	记录免费强炼丹礼包掉落数量
-- 50873	data3	记录一道真气礼包掉落数量
-- 50873	data4	记录1次修炼次数礼包掉落数量
-- 50873	data5	记录普通宝石礼包掉落数量

-- 50874	data0	记录良品宝石礼包掉落数量
-- 50874	data1	记录普通天地玄礼包掉落数量
-- 50874	data2	记录良品天地玄礼包掉落数量
-- 50874	data3	记录优质天地玄礼包掉落数量
-- 50874	data4	记录流星礼包掉落数量
-- 50874	data5	记录龙珠礼包掉落数量

-- 50875	data0	记录六阶神魂随机包
-- 50875	data1	记录神魂礼包洗非赠
-- 50875	data2	记录七阶武器神魂礼包
-- 50875	data3	记录七阶防具配饰神魂礼包
-- 50875	data4	记录赤炼石+1礼包掉落数量
-- 50875	data5	记录赤炼石+2礼包掉落数量

-- 50876	data2	记录赤炼石+3礼包掉落数量
-- 50876	data3	记录赤炼石+6礼包掉落数量
-- 50876	data4	记录七阶武器神魂碎片掉落数量
-- 50876	data5	记录七阶防具配饰神魂碎片掉落数量

-- 50876	data0	控制动态存储表清零开关

-- 常量表
local tKillMonsterDropItem_Constant = {}
	-- 活动时间
	tKillMonsterDropItem_Constant["BeforeActivityTime"] = "2015-05-11 00:00 2015-10-21 23:59"
	tKillMonsterDropItem_Constant["ActivityTime"] = "2015-10-22 00:00 2015-11-21 23:59"

	-- 玩家等级要求
	tKillMonsterDropItem_Constant["Metempsychosis"] = 2
	tKillMonsterDropItem_Constant["Level"] = 0

	-- 掉落的金币数量
	tKillMonsterDropItem_Constant["Money"] = 1000
	
	-- 地图上物品存在时间
	tKillMonsterDropItem_Constant["ExistTime"] = 120
	-- 满级
	tKillMonsterDropItem_Constant["MaxLev"] = 140
	-- 真气上限
	tKillMonsterDropItem_Constant["MaxQenuineqi"] = 5
	-- 修炼次数上限
	tKillMonsterDropItem_Constant["MaxPractNum"] = 1000000
	
	tKillMonsterDropItem_Constant["GlobalId"] = 50876
	
	tKillMonsterDropItem_Constant["RestGlobalTime"] = {}
	tKillMonsterDropItem_Constant["RestGlobalTime"][1] = "7:00 7:05"
	tKillMonsterDropItem_Constant["RestGlobalTime"][2] = "14:00 14:05"
	tKillMonsterDropItem_Constant["RestGlobalTime"][3] = "19:00 19:05"
	tKillMonsterDropItem_Constant["RestGlobalTime"][4] = "00:00 00:05"
	
	tKillMonsterDropItem_Constant["RestGlobal"] = {}
	tKillMonsterDropItem_Constant["RestGlobal"][1] = 50872
	tKillMonsterDropItem_Constant["RestGlobal"][2] = 50873
	tKillMonsterDropItem_Constant["RestGlobal"][3] = 50874
	tKillMonsterDropItem_Constant["RestGlobal"][4] = 50875

	-- 怪物log
	tKillMonsterDropItem_Constant["MonsterDeath"] = "0,0,%d,1,12000103,1,0,0"
	tKillMonsterDropItem_Constant["MonsterDrop"] = "0,0,%d,1,12000103,2,%d,%d"
	tKillMonsterDropItem_Constant["StrengthLog"] = "0,0,0,0,12000103,2,12,200"
	tKillMonsterDropItem_Constant["ScoreLog"] = "0,0,%d,1,12000103,2,0,0"
	
	-- 兑换气力值需要的积分
	tKillMonsterDropItem_Constant["Score"] = 1000
	tKillMonsterDropItem_Constant["StrengthValue"] = 200
	tKillMonsterDropItem_Constant["MaxTime"] = 10
	
	-- 杀怪任务
	tKillMonsterDropItem_Constant["RewardNum"] = 1
	tKillMonsterDropItem_Constant["MonsterNum"] = 10

	-- 九幽神魂礼包洗赠卷
	tKillMonsterDropItem_Constant[3006550] = {}
	tKillMonsterDropItem_Constant[3006550][1] = {}
	tKillMonsterDropItem_Constant[3006550][1]["ExchangeItem"] = 3006745
	tKillMonsterDropItem_Constant[3006550][1]["GetItem"] = 3004247
	tKillMonsterDropItem_Constant[3006550][1]["Log"] = "0,0,3006550[3006745],1[1],12000103,2,3004247,1"
	tKillMonsterDropItem_Constant[3006550][2] = {}
	tKillMonsterDropItem_Constant[3006550][2]["ExchangeItem"] = 3006746
	tKillMonsterDropItem_Constant[3006550][2]["GetItem"] = 3004248
	tKillMonsterDropItem_Constant[3006550][2]["Log"] = "0,0,3006550[3006746],1[1],12000103,2,3004248,1"
	
-- 掩码表
local tKillMonsterDropItem_Stc = {}
	tKillMonsterDropItem_Stc["EventType"] = 134
	tKillMonsterDropItem_Stc["DataType"] = {}
	tKillMonsterDropItem_Stc["DataType"][1] = 92
	tKillMonsterDropItem_Stc["DataType"][2] = 95
	tKillMonsterDropItem_Stc["DataType"][3] = 96
	tKillMonsterDropItem_Stc["DataType"][4] = 97
	tKillMonsterDropItem_Stc["DataType"][5] = 98
	tKillMonsterDropItem_Stc["DataType"][6] = 99

-- 怪物配置
local tKillMonsterDropItem_Monster = {}	
	-- 暗地游魂
	tKillMonsterDropItem_Monster[7697] = {}
	tKillMonsterDropItem_Monster[7697][1] = {}
	tKillMonsterDropItem_Monster[7697][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7697][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7697][1][1] = {}
	tKillMonsterDropItem_Monster[7697][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7697][1][1]["ItemChance"] = 150
	tKillMonsterDropItem_Monster[7697][1][1]["Item_1"] = 7697
	
	tKillMonsterDropItem_Monster[7697][1][2] = {}
	tKillMonsterDropItem_Monster[7697][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7697][1][2]["ItemChance"] = 200
	tKillMonsterDropItem_Monster[7697][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7697][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7697][1][3] = {}
	tKillMonsterDropItem_Monster[7697][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7697][1][3]["ItemChance"] = 100
	tKillMonsterDropItem_Monster[7697][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7697][1][4] = {}
	tKillMonsterDropItem_Monster[7697][1][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7697][1][4]["ItemChance"] = 9550
	tKillMonsterDropItem_Monster[7697][1][4]["Item_1"] = 0
	
	-- 虚空夜叉
	tKillMonsterDropItem_Monster[7698] = {}
	tKillMonsterDropItem_Monster[7698][1] = {}
	tKillMonsterDropItem_Monster[7698][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7698][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7698][1][1] = {}
	tKillMonsterDropItem_Monster[7698][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7698][1][1]["ItemChance"] = 170
	tKillMonsterDropItem_Monster[7698][1][1]["Item_1"] = 7698
	
	tKillMonsterDropItem_Monster[7698][1][2] = {}
	tKillMonsterDropItem_Monster[7698][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7698][1][2]["ItemChance"] = 200
	tKillMonsterDropItem_Monster[7698][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7698][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7698][1][3] = {}
	tKillMonsterDropItem_Monster[7698][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7698][1][3]["ItemChance"] = 100
	tKillMonsterDropItem_Monster[7698][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7698][1][4] = {}
	tKillMonsterDropItem_Monster[7698][1][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7698][1][4]["ItemChance"] = 9530
	tKillMonsterDropItem_Monster[7698][1][4]["Item_1"] = 0
	
	-- 地宫邪魅
	tKillMonsterDropItem_Monster[7699] = {}
	tKillMonsterDropItem_Monster[7699][1] = {}
	tKillMonsterDropItem_Monster[7699][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7699][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7699][1][1] = {}
	tKillMonsterDropItem_Monster[7699][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7699][1][1]["ItemChance"] = 190
	tKillMonsterDropItem_Monster[7699][1][1]["Item_1"] = 7699
	
	tKillMonsterDropItem_Monster[7699][1][2] = {}
	tKillMonsterDropItem_Monster[7699][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7699][1][2]["ItemChance"] = 200
	tKillMonsterDropItem_Monster[7699][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7699][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7699][1][3] = {}
	tKillMonsterDropItem_Monster[7699][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7699][1][3]["ItemChance"] = 100
	tKillMonsterDropItem_Monster[7699][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7699][1][4] = {}
	tKillMonsterDropItem_Monster[7699][1][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7699][1][4]["ItemChance"] = 9510
	tKillMonsterDropItem_Monster[7699][1][4]["Item_1"] = 0
	
	-- 暗地战魂
	tKillMonsterDropItem_Monster[7700] = {}
	tKillMonsterDropItem_Monster[7700][1] = {}
	tKillMonsterDropItem_Monster[7700][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7700][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7700][1][1] = {}
	tKillMonsterDropItem_Monster[7700][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7700][1][1]["ItemChance"] = 7500
	tKillMonsterDropItem_Monster[7700][1][1]["Item_1"] = 7700
	
	tKillMonsterDropItem_Monster[7700][1][2] = {}
	tKillMonsterDropItem_Monster[7700][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7700][1][2]["ItemChance"] = 1500
	tKillMonsterDropItem_Monster[7700][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7700][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7700][1][3] = {}
	tKillMonsterDropItem_Monster[7700][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7700][1][3]["ItemChance"] = 1000
	tKillMonsterDropItem_Monster[7700][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7700][1][4] = {}
	tKillMonsterDropItem_Monster[7700][1][4]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7700][1][4]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7700][1][4]["IsMoney"] = true

	tKillMonsterDropItem_Monster[7700][1][5] = {}
	tKillMonsterDropItem_Monster[7700][1][5]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7700][1][5]["Item_1"] = 1000040

	-- 虚空小将
	tKillMonsterDropItem_Monster[7701] = {}
	tKillMonsterDropItem_Monster[7701][1] = {}
	tKillMonsterDropItem_Monster[7701][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7701][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7701][1][1] = {}
	tKillMonsterDropItem_Monster[7701][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7701][1][1]["ItemChance"] = 8500
	tKillMonsterDropItem_Monster[7701][1][1]["Item_1"] = 7701
	
	tKillMonsterDropItem_Monster[7701][1][2] = {}
	tKillMonsterDropItem_Monster[7701][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7701][1][2]["ItemChance"] = 900
	tKillMonsterDropItem_Monster[7701][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7701][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7701][1][3] = {}
	tKillMonsterDropItem_Monster[7701][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7701][1][3]["ItemChance"] = 600
	tKillMonsterDropItem_Monster[7701][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7701][1][4] = {}
	tKillMonsterDropItem_Monster[7701][1][4]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7701][1][4]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7701][1][4]["IsMoney"] = true

	tKillMonsterDropItem_Monster[7701][1][5] = {}
	tKillMonsterDropItem_Monster[7701][1][5]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7701][1][5]["Item_1"] = 1000040

	-- 地宫邪魔
	tKillMonsterDropItem_Monster[7702] = {}
	tKillMonsterDropItem_Monster[7702][1] = {}
	tKillMonsterDropItem_Monster[7702][1]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Monster[7702][1]["Time"] = 1
	
	tKillMonsterDropItem_Monster[7702][1][1] = {}
	tKillMonsterDropItem_Monster[7702][1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7702][1][1]["ItemChance"] = 9500
	tKillMonsterDropItem_Monster[7702][1][1]["Item_1"] = 7702
	
	tKillMonsterDropItem_Monster[7702][1][2] = {}
	tKillMonsterDropItem_Monster[7702][1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7702][1][2]["ItemChance"] = 300
	tKillMonsterDropItem_Monster[7702][1][2]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7702][1][2]["IsMoney"] = true
	
	tKillMonsterDropItem_Monster[7702][1][3] = {}
	tKillMonsterDropItem_Monster[7702][1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Monster[7702][1][3]["ItemChance"] = 200
	tKillMonsterDropItem_Monster[7702][1][3]["Item_1"] = 1000040
	
	tKillMonsterDropItem_Monster[7702][1][4] = {}
	tKillMonsterDropItem_Monster[7702][1][4]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7702][1][4]["Item_1"] = 1000
	tKillMonsterDropItem_Monster[7702][1][4]["IsMoney"] = true

	tKillMonsterDropItem_Monster[7702][1][5] = {}
	tKillMonsterDropItem_Monster[7702][1][5]["RandomItemChanceType"] = 1
	tKillMonsterDropItem_Monster[7702][1][5]["Item_1"] = 1000040

	-- 幽寂豺狼
	tKillMonsterDropItem_Monster[7706] = {}
	tKillMonsterDropItem_Monster[7706]["MapId"] = 3943
	tKillMonsterDropItem_Monster[7706]["PosX"] = 295
	tKillMonsterDropItem_Monster[7706]["PosY"] = 264
	tKillMonsterDropItem_Monster[7706]["Generator"] = 17461
	
	-- 幽冥麒麟
	tKillMonsterDropItem_Monster[7707] = {}
	tKillMonsterDropItem_Monster[7707]["MapId"] = 3944
	tKillMonsterDropItem_Monster[7707]["PosX"] = 275
	tKillMonsterDropItem_Monster[7707]["PosY"] = 227
	tKillMonsterDropItem_Monster[7707]["Generator"] = 17501
	
	-- 九幽金睛兽
	tKillMonsterDropItem_Monster[7708] = {}
	tKillMonsterDropItem_Monster[7708]["MapId"] = 3945
	tKillMonsterDropItem_Monster[7708]["PosX"] = 168
	tKillMonsterDropItem_Monster[7708]["PosY"] = 170
	tKillMonsterDropItem_Monster[7708]["Generator"] = 17503
	
-- 地图
local tKillMonsterDropItem_ChgMap = {}
	tKillMonsterDropItem_ChgMap[992790] = {}
	tKillMonsterDropItem_ChgMap[992790]["MapId"] = 3942
	tKillMonsterDropItem_ChgMap[992790]["CellX"] = 49
	tKillMonsterDropItem_ChgMap[992790]["CellY"] = 77
	tKillMonsterDropItem_ChgMap[992790]["Range"] = 3
	tKillMonsterDropItem_ChgMap[992790]["Index"] = "NineQuietFam"
	-- 地宫守卫者中前往九幽地宫选项
	tKillMonsterDropItem_ChgMap[18515] = {}
	tKillMonsterDropItem_ChgMap[18515]["MapId"] = 3943
	tKillMonsterDropItem_ChgMap[18515]["CellX"] = 162
	tKillMonsterDropItem_ChgMap[18515]["CellY"] = 380
	tKillMonsterDropItem_ChgMap[18515]["Range"] = 7
	tKillMonsterDropItem_ChgMap[18515]["Index"] = "NineQuietFamOne"

	-- 陷阱传送点
	tKillMonsterDropItem_ChgMap[992783] = {}
	tKillMonsterDropItem_ChgMap[992783]["MapId"] = 1000
	tKillMonsterDropItem_ChgMap[992783]["CellX"] = 485
	tKillMonsterDropItem_ChgMap[992783]["CellY"] = 581
	tKillMonsterDropItem_ChgMap[992783]["Range"] = 3
	tKillMonsterDropItem_ChgMap[992783]["Index"] = "CloudGateClosed"
	
	tKillMonsterDropItem_ChgMap[992785] = {}
	tKillMonsterDropItem_ChgMap[992785]["MapId"] = 3942
	tKillMonsterDropItem_ChgMap[992785]["CellX"] = 53
	tKillMonsterDropItem_ChgMap[992785]["CellY"] = 36
	tKillMonsterDropItem_ChgMap[992785]["Range"] = 5
	tKillMonsterDropItem_ChgMap[992785]["Index"] = "NineQuietFam"

	tKillMonsterDropItem_ChgMap[992786] = {}
	tKillMonsterDropItem_ChgMap[992786]["MapId"] = 3944
	tKillMonsterDropItem_ChgMap[992786]["CellX"] = 186
	tKillMonsterDropItem_ChgMap[992786]["CellY"] = 159
	tKillMonsterDropItem_ChgMap[992786]["Range"] = 5
	tKillMonsterDropItem_ChgMap[992786]["Index"] = "NineQuietFamTwo"

	tKillMonsterDropItem_ChgMap[992787] = {}
	tKillMonsterDropItem_ChgMap[992787]["MapId"] = 3943
	tKillMonsterDropItem_ChgMap[992787]["CellX"] = 396
	tKillMonsterDropItem_ChgMap[992787]["CellY"] = 182
	tKillMonsterDropItem_ChgMap[992787]["Range"] = 5
	tKillMonsterDropItem_ChgMap[992787]["Index"] = "NineQuietFamOne"

	tKillMonsterDropItem_ChgMap[992788] = {}
	tKillMonsterDropItem_ChgMap[992788]["MapId"] = 3945
	tKillMonsterDropItem_ChgMap[992788]["CellX"] = 396
	tKillMonsterDropItem_ChgMap[992788]["CellY"] = 315
	tKillMonsterDropItem_ChgMap[992788]["Range"] = 5
	tKillMonsterDropItem_ChgMap[992788]["Index"] = "NineQuietFamThree"

	tKillMonsterDropItem_ChgMap[992789] = {}
	tKillMonsterDropItem_ChgMap[992789]["MapId"] = 3944
	tKillMonsterDropItem_ChgMap[992789]["CellX"] = 346
	tKillMonsterDropItem_ChgMap[992789]["CellY"] = 440
	tKillMonsterDropItem_ChgMap[992789]["Range"] = 5
	tKillMonsterDropItem_ChgMap[992789]["Index"] = "NineQuietFamTwo"
	
	tKillMonsterDropItem_ChgMap[93006010] = {}
	tKillMonsterDropItem_ChgMap[93006010]["MapId"] = 3942
	tKillMonsterDropItem_ChgMap[93006010]["CellX"] = 61
	tKillMonsterDropItem_ChgMap[93006010]["CellY"] = 55
	tKillMonsterDropItem_ChgMap[93006010]["Range"] = 3
	tKillMonsterDropItem_ChgMap[93006010]["Index"] = "NineQuietFam"

-- 动态存储表配置
local tKillMonsterDropItem_Global = {}
	tKillMonsterDropItem_Global[1] = {}
	tKillMonsterDropItem_Global[1]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[1]["GlobalData"] = 0
	tKillMonsterDropItem_Global[1]["MaxData"] = 750
	
	tKillMonsterDropItem_Global[2] = {}
	tKillMonsterDropItem_Global[2]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[2]["GlobalData"] = 1
	tKillMonsterDropItem_Global[2]["MaxData"] = 500
	
	tKillMonsterDropItem_Global[3] = {}
	tKillMonsterDropItem_Global[3]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[3]["GlobalData"] = 2
	tKillMonsterDropItem_Global[3]["MaxData"] = 400
	
	tKillMonsterDropItem_Global[4] = {}
	tKillMonsterDropItem_Global[4]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[4]["GlobalData"] = 3
	tKillMonsterDropItem_Global[4]["MaxData"] = 750
	
	tKillMonsterDropItem_Global[5] = {}
	tKillMonsterDropItem_Global[5]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[5]["GlobalData"] = 4
	tKillMonsterDropItem_Global[5]["MaxData"] = 500
	
	tKillMonsterDropItem_Global[6] = {}
	tKillMonsterDropItem_Global[6]["GlobalId"] = 50872
	tKillMonsterDropItem_Global[6]["GlobalData"] = 5
	tKillMonsterDropItem_Global[6]["MaxData"] = 400
	
	tKillMonsterDropItem_Global[7] = {}
	tKillMonsterDropItem_Global[7]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[7]["GlobalData"] = 0
	tKillMonsterDropItem_Global[7]["MaxData"] = 2000
	
	tKillMonsterDropItem_Global[8] = {}
	tKillMonsterDropItem_Global[8]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[8]["GlobalData"] = 1
	tKillMonsterDropItem_Global[8]["MaxData"] = 750
	
	tKillMonsterDropItem_Global[9] = {}
	tKillMonsterDropItem_Global[9]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[9]["GlobalData"] = 2
	tKillMonsterDropItem_Global[9]["MaxData"] = 500
	
	tKillMonsterDropItem_Global[10] = {}
	tKillMonsterDropItem_Global[10]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[10]["GlobalData"] = 3
	tKillMonsterDropItem_Global[10]["MaxData"] = 3000
	
	tKillMonsterDropItem_Global[11] = {}
	tKillMonsterDropItem_Global[11]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[11]["GlobalData"] = 4
	tKillMonsterDropItem_Global[11]["MaxData"] = 2000
	
	tKillMonsterDropItem_Global[12] = {}
	tKillMonsterDropItem_Global[12]["GlobalId"] = 50873
	tKillMonsterDropItem_Global[12]["GlobalData"] = 5
	tKillMonsterDropItem_Global[12]["MaxData"] = 1000
	
	tKillMonsterDropItem_Global[13] = {}
	tKillMonsterDropItem_Global[13]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[13]["GlobalData"] = 0
	tKillMonsterDropItem_Global[13]["MaxData"] = 200
	
	tKillMonsterDropItem_Global[14] = {}
	tKillMonsterDropItem_Global[14]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[14]["GlobalData"] = 1
	tKillMonsterDropItem_Global[14]["MaxData"] = 1000
	
	tKillMonsterDropItem_Global[15] = {}
	tKillMonsterDropItem_Global[15]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[15]["GlobalData"] = 2
	tKillMonsterDropItem_Global[15]["MaxData"] = 200
	
	tKillMonsterDropItem_Global[16] = {}
	tKillMonsterDropItem_Global[16]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[16]["GlobalData"] = 3
	tKillMonsterDropItem_Global[16]["MaxData"] = 6
	
	tKillMonsterDropItem_Global[17] = {}
	tKillMonsterDropItem_Global[17]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[17]["GlobalData"] = 4
	tKillMonsterDropItem_Global[17]["MaxData"] = 5000
	
	tKillMonsterDropItem_Global[18] = {}
	tKillMonsterDropItem_Global[18]["GlobalId"] = 50874
	tKillMonsterDropItem_Global[18]["GlobalData"] = 5
	tKillMonsterDropItem_Global[18]["MaxData"] = 25
	
	tKillMonsterDropItem_Global[19] = {}
	tKillMonsterDropItem_Global[19]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[19]["GlobalData"] = 0
	tKillMonsterDropItem_Global[19]["MaxData"] = 6
	
	tKillMonsterDropItem_Global[20] = {}
	tKillMonsterDropItem_Global[20]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[20]["GlobalData"] = 1
	tKillMonsterDropItem_Global[20]["MaxData"] = 3
	
	tKillMonsterDropItem_Global[21] = {}
	tKillMonsterDropItem_Global[21]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[21]["GlobalData"] = 2
	tKillMonsterDropItem_Global[21]["MaxData"] = 1
	
	tKillMonsterDropItem_Global[22] = {}
	tKillMonsterDropItem_Global[22]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[22]["GlobalData"] = 3
	tKillMonsterDropItem_Global[22]["MaxData"] = 2
	
	tKillMonsterDropItem_Global[23] = {}
	tKillMonsterDropItem_Global[23]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[23]["GlobalData"] = 4
	tKillMonsterDropItem_Global[23]["MaxData"] = 2250
	
	tKillMonsterDropItem_Global[24] = {}
	tKillMonsterDropItem_Global[24]["GlobalId"] = 50875
	tKillMonsterDropItem_Global[24]["GlobalData"] = 5
	tKillMonsterDropItem_Global[24]["MaxData"] = 225
	
	tKillMonsterDropItem_Global[25] = {}
	tKillMonsterDropItem_Global[25]["GlobalId"] = 50876
	tKillMonsterDropItem_Global[25]["GlobalData"] = 2
	tKillMonsterDropItem_Global[25]["MaxData"] = 40
	
	tKillMonsterDropItem_Global[26] = {}
	tKillMonsterDropItem_Global[26]["GlobalId"] = 50876
	tKillMonsterDropItem_Global[26]["GlobalData"] = 3
	tKillMonsterDropItem_Global[26]["MaxData"] = 1
	
	tKillMonsterDropItem_Global[27] = {}
	tKillMonsterDropItem_Global[27]["GlobalId"] = 50876
	tKillMonsterDropItem_Global[27]["GlobalData"] = 4
	tKillMonsterDropItem_Global[27]["MaxData"] = 3
	
	tKillMonsterDropItem_Global[28] = {}
	tKillMonsterDropItem_Global[28]["GlobalId"] = 50876
	tKillMonsterDropItem_Global[28]["GlobalData"] = 5
	tKillMonsterDropItem_Global[28]["MaxData"] = 7
	
-- 怪物掉落配置
local tKillMonsterDropItem_RewardItem = {}
	----------------------------- 一层普通怪
	tKillMonsterDropItem_RewardItem[7697] = {}
	tKillMonsterDropItem_RewardItem[7700] = tKillMonsterDropItem_RewardItem[7697]
	tKillMonsterDropItem_RewardItem[7697]["ItemChanceSum"] = 27000

	---- 赤炼石+2		200
	tKillMonsterDropItem_RewardItem[7697][1] = {}
	tKillMonsterDropItem_RewardItem[7697][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][1]["ItemChance"] = 200
	tKillMonsterDropItem_RewardItem[7697][1]["Item_1"] = 3006552
	tKillMonsterDropItem_RewardItem[7697][1]["IsGlobal"] = 24

	---- 赤炼石+1		2000
	tKillMonsterDropItem_RewardItem[7697][2] = {}
	tKillMonsterDropItem_RewardItem[7697][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][2]["ItemChance"] = 2000
	tKillMonsterDropItem_RewardItem[7697][2]["Item_1"] = 3006551
	tKillMonsterDropItem_RewardItem[7697][2]["IsGlobal"] = 23

	---- 流星		6000
	tKillMonsterDropItem_RewardItem[7697][3] = {}
	tKillMonsterDropItem_RewardItem[7697][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][3]["ItemChance"] = 6000
	tKillMonsterDropItem_RewardItem[7697][3]["Item_1"] = 1088001
	tKillMonsterDropItem_RewardItem[7697][3]["IsGlobal"] = 17

	---- 普通天地玄		1000
	tKillMonsterDropItem_RewardItem[7697][4] = {}
	tKillMonsterDropItem_RewardItem[7697][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][4]["ItemChance"] = 1000
	tKillMonsterDropItem_RewardItem[7697][4]["Item_1"] = {}
	tKillMonsterDropItem_RewardItem[7697][4]["Item_1"][1] = 700071
	tKillMonsterDropItem_RewardItem[7697][4]["Item_1"][2] = 700101
	tKillMonsterDropItem_RewardItem[7697][4]["Item_1"][3] = 700121
	tKillMonsterDropItem_RewardItem[7697][4]["IsGlobal"] = 14

	---- 普通宝石		4000
	tKillMonsterDropItem_RewardItem[7697][5] = {}
	tKillMonsterDropItem_RewardItem[7697][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][5]["ItemChance"] = 4000
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"] = {}
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][1] = 700001
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][2] = 700011
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][3] = 700021
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][4] = 700031
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][5] = 700041
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][6] = 700051
	tKillMonsterDropItem_RewardItem[7697][5]["Item_1"][7] = 700061
	tKillMonsterDropItem_RewardItem[7697][5]["IsGlobal"] = 12

	---- 1次修炼次数		1600
	tKillMonsterDropItem_RewardItem[7697][6] = {}
	tKillMonsterDropItem_RewardItem[7697][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][6]["ItemChance"] = 1600
	tKillMonsterDropItem_RewardItem[7697][6]["Item_1"] = 3006543
	tKillMonsterDropItem_RewardItem[7697][6]["IsGlobal"] = 11

	---- 一道真气		2400
	tKillMonsterDropItem_RewardItem[7697][7] = {}
	tKillMonsterDropItem_RewardItem[7697][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][7]["ItemChance"] = 2400
	tKillMonsterDropItem_RewardItem[7697][7]["Item_1"] = 3006542
	tKillMonsterDropItem_RewardItem[7697][7]["IsGlobal"] = 10

	---- 护心丹		800
	tKillMonsterDropItem_RewardItem[7697][8] = {}
	tKillMonsterDropItem_RewardItem[7697][8]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][8]["ItemChance"] = 800
	tKillMonsterDropItem_RewardItem[7697][8]["Item_1"] = 3002029
	tKillMonsterDropItem_RewardItem[7697][8]["IsGlobal"] = 7

	---- 10气力		3000
	tKillMonsterDropItem_RewardItem[7697][9] = {}
	tKillMonsterDropItem_RewardItem[7697][9]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][9]["ItemChance"] = 3000
	tKillMonsterDropItem_RewardItem[7697][9]["Item_1"] = 3006537
	tKillMonsterDropItem_RewardItem[7697][9]["IsGlobal"] = 4

	---- 10修行值		3000
	tKillMonsterDropItem_RewardItem[7697][10] = {}
	tKillMonsterDropItem_RewardItem[7697][10]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][10]["ItemChance"] = 3000
	tKillMonsterDropItem_RewardItem[7697][10]["Item_1"] = 3006534
	tKillMonsterDropItem_RewardItem[7697][10]["IsGlobal"] = 1

	---- 10分钟经验		3000
	tKillMonsterDropItem_RewardItem[7697][11] = {}
	tKillMonsterDropItem_RewardItem[7697][11]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7697][11]["ItemChance"] = 3000
	tKillMonsterDropItem_RewardItem[7697][11]["Item_1"] = 3006531

	---------------------------- 二层普通怪
	tKillMonsterDropItem_RewardItem[7698] = {}
	tKillMonsterDropItem_RewardItem[7701] = tKillMonsterDropItem_RewardItem[7698]
	tKillMonsterDropItem_RewardItem[7698]["ItemChanceSum"] = 30805

	---- 赤炼石+3			60
	tKillMonsterDropItem_RewardItem[7698][1] = {}
	tKillMonsterDropItem_RewardItem[7698][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][1]["ItemChance"] = 60
	tKillMonsterDropItem_RewardItem[7698][1]["Item_1"] = 3006553
	tKillMonsterDropItem_RewardItem[7698][1]["IsGlobal"] = 25

	---- 赤炼石+2				300
	tKillMonsterDropItem_RewardItem[7698][2] = {}
	tKillMonsterDropItem_RewardItem[7698][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][2]["ItemChance"] = 300
	tKillMonsterDropItem_RewardItem[7698][2]["Item_1"] = 3006552
	tKillMonsterDropItem_RewardItem[7698][2]["IsGlobal"] = 24

	---- 赤炼石+1				3000
	tKillMonsterDropItem_RewardItem[7698][3] = {}
	tKillMonsterDropItem_RewardItem[7698][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][3]["ItemChance"] = 3000
	tKillMonsterDropItem_RewardItem[7698][3]["Item_1"] = 3006551
	tKillMonsterDropItem_RewardItem[7698][3]["IsGlobal"] = 23

	---- 六阶神魂随机包				20
	tKillMonsterDropItem_RewardItem[7698][4] = {}
	tKillMonsterDropItem_RewardItem[7698][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][4]["ItemChance"] = 20
	tKillMonsterDropItem_RewardItem[7698][4]["Item_1"] = 3004059
	tKillMonsterDropItem_RewardItem[7698][4]["IsGlobal"] = 19

	---- 龙珠				25
	tKillMonsterDropItem_RewardItem[7698][5] = {}
	tKillMonsterDropItem_RewardItem[7698][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][5]["ItemChance"] = 25
	tKillMonsterDropItem_RewardItem[7698][5]["Item_1"] = 3006549
	tKillMonsterDropItem_RewardItem[7698][5]["IsGlobal"] = 18

	---- 流星				7500
	tKillMonsterDropItem_RewardItem[7698][6] = {}
	tKillMonsterDropItem_RewardItem[7698][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][6]["ItemChance"] = 7500
	tKillMonsterDropItem_RewardItem[7698][6]["Item_1"] = 1088001
	tKillMonsterDropItem_RewardItem[7698][6]["IsGlobal"] = 17

	---- 良品天地玄				200
	tKillMonsterDropItem_RewardItem[7698][7] = {}
	tKillMonsterDropItem_RewardItem[7698][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][7]["ItemChance"] = 200
	tKillMonsterDropItem_RewardItem[7698][7]["Item_1"] = 3006545
	tKillMonsterDropItem_RewardItem[7698][7]["IsGlobal"] = 15

	---- 普通天地玄				3000
	tKillMonsterDropItem_RewardItem[7698][8] = {}
	tKillMonsterDropItem_RewardItem[7698][8]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][8]["ItemChance"] = 3000
	tKillMonsterDropItem_RewardItem[7698][8]["Item_1"] = {}
	tKillMonsterDropItem_RewardItem[7698][8]["Item_1"][1] = 700071
	tKillMonsterDropItem_RewardItem[7698][8]["Item_1"][2] = 700101
	tKillMonsterDropItem_RewardItem[7698][8]["Item_1"][3] = 700121
	tKillMonsterDropItem_RewardItem[7698][8]["IsGlobal"] = 14

	---- 良品宝石				800
	tKillMonsterDropItem_RewardItem[7698][9] = {}
	tKillMonsterDropItem_RewardItem[7698][9]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][9]["ItemChance"] = 800
	tKillMonsterDropItem_RewardItem[7698][9]["Item_1"] = 3006544
	tKillMonsterDropItem_RewardItem[7698][9]["IsGlobal"] = 13

	---- 1次修炼次数				2400
	tKillMonsterDropItem_RewardItem[7698][10] = {}
	tKillMonsterDropItem_RewardItem[7698][10]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][10]["ItemChance"] = 2400
	tKillMonsterDropItem_RewardItem[7698][10]["Item_1"] = 3006543
	tKillMonsterDropItem_RewardItem[7698][10]["IsGlobal"] = 11

	---- 一道真气				3600
	tKillMonsterDropItem_RewardItem[7698][11] = {}
	tKillMonsterDropItem_RewardItem[7698][11]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][11]["ItemChance"] = 3600
	tKillMonsterDropItem_RewardItem[7698][11]["Item_1"] = 3006542
	tKillMonsterDropItem_RewardItem[7698][11]["IsGlobal"] = 10

	---- 免费强炼丹				500
	tKillMonsterDropItem_RewardItem[7698][12] = {}
	tKillMonsterDropItem_RewardItem[7698][12]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][12]["ItemChance"] = 500
	tKillMonsterDropItem_RewardItem[7698][12]["Item_1"] = 3006541
	tKillMonsterDropItem_RewardItem[7698][12]["IsGlobal"] = 9

	---- 通神丹				1000
	tKillMonsterDropItem_RewardItem[7698][13] = {}
	tKillMonsterDropItem_RewardItem[7698][13]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][13]["ItemChance"] = 1000
	tKillMonsterDropItem_RewardItem[7698][13]["Item_1"] = 3006540
	tKillMonsterDropItem_RewardItem[7698][13]["IsGlobal"] = 8

	---- 护心丹				2400
	tKillMonsterDropItem_RewardItem[7698][14] = {}
	tKillMonsterDropItem_RewardItem[7698][14]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][14]["ItemChance"] = 2400
	tKillMonsterDropItem_RewardItem[7698][14]["Item_1"] = 3002029
	tKillMonsterDropItem_RewardItem[7698][14]["IsGlobal"] = 7

	---- 30气力				2000
	tKillMonsterDropItem_RewardItem[7698][15] = {}
	tKillMonsterDropItem_RewardItem[7698][15]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][15]["ItemChance"] = 2000
	tKillMonsterDropItem_RewardItem[7698][15]["Item_1"] = 3006538
	tKillMonsterDropItem_RewardItem[7698][15]["IsGlobal"] = 5

	---- 30修行值				2000
	tKillMonsterDropItem_RewardItem[7698][16] = {}
	tKillMonsterDropItem_RewardItem[7698][16]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][16]["ItemChance"] = 2000
	tKillMonsterDropItem_RewardItem[7698][16]["Item_1"] = 3006535
	tKillMonsterDropItem_RewardItem[7698][16]["IsGlobal"] = 2

	---- 30分钟经验				2000
	tKillMonsterDropItem_RewardItem[7698][17] = {}
	tKillMonsterDropItem_RewardItem[7698][17]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7698][17]["ItemChance"] = 2000
	tKillMonsterDropItem_RewardItem[7698][17]["Item_1"] = 3006532

	---------------------------- 三层普通怪
	tKillMonsterDropItem_RewardItem[7699] = {}
	tKillMonsterDropItem_RewardItem[7702] = tKillMonsterDropItem_RewardItem[7699]
	tKillMonsterDropItem_RewardItem[7699]["ItemChanceSum"] = 34864
	
	---- 赤炼石+6				1
	tKillMonsterDropItem_RewardItem[7699][1] = {}
	tKillMonsterDropItem_RewardItem[7699][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][1]["ItemChance"] = 1
	tKillMonsterDropItem_RewardItem[7699][1]["Item_1"] = 3006554
	tKillMonsterDropItem_RewardItem[7699][1]["IsGlobal"] = 26

	---- 赤炼石+3				100
	tKillMonsterDropItem_RewardItem[7699][2] = {}
	tKillMonsterDropItem_RewardItem[7699][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][2]["ItemChance"] = 100
	tKillMonsterDropItem_RewardItem[7699][2]["Item_1"] = 3006553
	tKillMonsterDropItem_RewardItem[7699][2]["IsGlobal"] = 25

	---- 赤炼石+2				400
	tKillMonsterDropItem_RewardItem[7699][3] = {}
	tKillMonsterDropItem_RewardItem[7699][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][3]["ItemChance"] = 400
	tKillMonsterDropItem_RewardItem[7699][3]["Item_1"] = 3006552
	tKillMonsterDropItem_RewardItem[7699][3]["IsGlobal"] = 24

	---- 赤炼石+1				4000
	tKillMonsterDropItem_RewardItem[7699][4] = {}
	tKillMonsterDropItem_RewardItem[7699][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][4]["ItemChance"] = 4000
	tKillMonsterDropItem_RewardItem[7699][4]["Item_1"] = 3006551
	tKillMonsterDropItem_RewardItem[7699][4]["IsGlobal"] = 23

	---- 七阶防具配饰神魂礼包（赠）				4
	tKillMonsterDropItem_RewardItem[7699][5] = {}
	tKillMonsterDropItem_RewardItem[7699][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][5]["ItemChance"] = 4
	tKillMonsterDropItem_RewardItem[7699][5]["Item_1"] = 3006746
	tKillMonsterDropItem_RewardItem[7699][5]["IsGlobal"] = 22

	---- 七阶武器神魂礼包（赠）				4
	tKillMonsterDropItem_RewardItem[7699][6] = {}
	tKillMonsterDropItem_RewardItem[7699][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][6]["ItemChance"] = 4
	tKillMonsterDropItem_RewardItem[7699][6]["Item_1"] = 3006745
	tKillMonsterDropItem_RewardItem[7699][6]["IsGlobal"] = 21

	---- 神魂礼包洗非赠				12
	tKillMonsterDropItem_RewardItem[7699][7] = {}
	tKillMonsterDropItem_RewardItem[7699][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][7]["ItemChance"] = 12
	tKillMonsterDropItem_RewardItem[7699][7]["Item_1"] = 3006550
	tKillMonsterDropItem_RewardItem[7699][7]["IsGlobal"] = 20

	---- 六阶神魂随机包				4
	tKillMonsterDropItem_RewardItem[7699][8] = {}
	tKillMonsterDropItem_RewardItem[7699][8]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][8]["ItemChance"] = 4
	tKillMonsterDropItem_RewardItem[7699][8]["Item_1"] = 3004059
	tKillMonsterDropItem_RewardItem[7699][8]["IsGlobal"] = 19

	---- 龙珠				75
	tKillMonsterDropItem_RewardItem[7699][9] = {}
	tKillMonsterDropItem_RewardItem[7699][9]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][9]["ItemChance"] = 75
	tKillMonsterDropItem_RewardItem[7699][9]["Item_1"] = 3006549
	tKillMonsterDropItem_RewardItem[7699][9]["IsGlobal"] = 18

	---- 流星				6500
	tKillMonsterDropItem_RewardItem[7699][10] = {}
	tKillMonsterDropItem_RewardItem[7699][10]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][10]["ItemChance"] = 6500
	tKillMonsterDropItem_RewardItem[7699][10]["Item_1"] = 1088001
	tKillMonsterDropItem_RewardItem[7699][10]["IsGlobal"] = 17

	---- 优质天地玄				24
	tKillMonsterDropItem_RewardItem[7699][11] = {}
	tKillMonsterDropItem_RewardItem[7699][11]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][11]["ItemChance"] = 24
	tKillMonsterDropItem_RewardItem[7699][11]["Item_1"] = {}
	tKillMonsterDropItem_RewardItem[7699][11]["Item_1"][1] = 3006546
	tKillMonsterDropItem_RewardItem[7699][11]["Item_1"][2] = 3006547
	tKillMonsterDropItem_RewardItem[7699][11]["Item_1"][3] = 3006548
	tKillMonsterDropItem_RewardItem[7699][11]["IsGlobal"] = 16

	---- 良品天地玄				600
	tKillMonsterDropItem_RewardItem[7699][12] = {}
	tKillMonsterDropItem_RewardItem[7699][12]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][12]["ItemChance"] = 600
	tKillMonsterDropItem_RewardItem[7699][12]["Item_1"] = 3006545
	tKillMonsterDropItem_RewardItem[7699][12]["IsGlobal"] = 15

	---- 1次修炼次数				4000
	tKillMonsterDropItem_RewardItem[7699][13] = {}
	tKillMonsterDropItem_RewardItem[7699][13]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][13]["ItemChance"] = 4000
	tKillMonsterDropItem_RewardItem[7699][13]["Item_1"] = 3006543
	tKillMonsterDropItem_RewardItem[7699][13]["IsGlobal"] = 11

	---- 一道真气				6000
	tKillMonsterDropItem_RewardItem[7699][14] = {}
	tKillMonsterDropItem_RewardItem[7699][14]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][14]["ItemChance"] = 6000
	tKillMonsterDropItem_RewardItem[7699][14]["Item_1"] = 3006542
	tKillMonsterDropItem_RewardItem[7699][14]["IsGlobal"] = 10

	---- 免费强炼丹				1500
	tKillMonsterDropItem_RewardItem[7699][15] = {}
	tKillMonsterDropItem_RewardItem[7699][15]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][15]["ItemChance"] = 1500
	tKillMonsterDropItem_RewardItem[7699][15]["Item_1"] = 3006541
	tKillMonsterDropItem_RewardItem[7699][15]["IsGlobal"] = 9

	---- 通神丹				2000
	tKillMonsterDropItem_RewardItem[7699][16] = {}
	tKillMonsterDropItem_RewardItem[7699][16]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][16]["ItemChance"] = 2000
	tKillMonsterDropItem_RewardItem[7699][16]["Item_1"] = 3006540
	tKillMonsterDropItem_RewardItem[7699][16]["IsGlobal"] = 8

	---- 护心丹				4800
	tKillMonsterDropItem_RewardItem[7699][17] = {}
	tKillMonsterDropItem_RewardItem[7699][17]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][17]["ItemChance"] = 4800
	tKillMonsterDropItem_RewardItem[7699][17]["Item_1"] = 3002029
	tKillMonsterDropItem_RewardItem[7699][17]["IsGlobal"] = 7

	---- 50气力				1600
	tKillMonsterDropItem_RewardItem[7699][18] = {}
	tKillMonsterDropItem_RewardItem[7699][18]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][18]["ItemChance"] = 1600
	tKillMonsterDropItem_RewardItem[7699][18]["Item_1"] = 3006539
	tKillMonsterDropItem_RewardItem[7699][18]["IsGlobal"] = 6

	---- 50修行值				1600
	tKillMonsterDropItem_RewardItem[7699][19] = {}
	tKillMonsterDropItem_RewardItem[7699][19]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][19]["ItemChance"] = 1600
	tKillMonsterDropItem_RewardItem[7699][19]["Item_1"] = 3006536
	tKillMonsterDropItem_RewardItem[7699][19]["IsGlobal"] = 3

	---- 50分钟经验				1600
	tKillMonsterDropItem_RewardItem[7699][20] = {}
	tKillMonsterDropItem_RewardItem[7699][20]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][20]["ItemChance"] = 1600
	tKillMonsterDropItem_RewardItem[7699][20]["Item_1"] = 3006533

	---- 七阶武器神魂碎片				12
	tKillMonsterDropItem_RewardItem[7699][21] = {}
	tKillMonsterDropItem_RewardItem[7699][21]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][21]["ItemChance"] = 12
	tKillMonsterDropItem_RewardItem[7699][21]["Item_1"] = 3006765
	tKillMonsterDropItem_RewardItem[7699][21]["IsGlobal"] = 27
	
	---- 七阶武器神魂碎片				28
	tKillMonsterDropItem_RewardItem[7699][22] = {}
	tKillMonsterDropItem_RewardItem[7699][22]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_RewardItem[7699][22]["ItemChance"] = 28
	tKillMonsterDropItem_RewardItem[7699][22]["Item_1"] = 3006766
	tKillMonsterDropItem_RewardItem[7699][22]["IsGlobal"] = 28

	------------------------------- 幽暗地妖
	tKillMonsterDropItem_RewardItem[7703] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7703][1] = {}
	-- 赤炼石+1		3
	tKillMonsterDropItem_RewardItem[7703][1][1] = {}
	tKillMonsterDropItem_RewardItem[7703][1][1]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7703][1][1]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7703][1][1]["IsGlobal"] = 23
	
	-- 普通天地玄	3
	tKillMonsterDropItem_RewardItem[7703][1][2] = {}
	tKillMonsterDropItem_RewardItem[7703][1][2]["ItemId"] = {}
	tKillMonsterDropItem_RewardItem[7703][1][2]["ItemId"][1] = 700071
	tKillMonsterDropItem_RewardItem[7703][1][2]["ItemId"][2] = 700101
	tKillMonsterDropItem_RewardItem[7703][1][2]["ItemId"][3] = 700121
	tKillMonsterDropItem_RewardItem[7703][1][2]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7703][1][2]["IsGlobal"] = 14
	
	-- 普通宝石		5
	tKillMonsterDropItem_RewardItem[7703][1][3] = {}
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"] = {}
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][1] = 700001
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][2] = 700011
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][3] = 700021
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][4] = 700031
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][5] = 700041
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][6] = 700051
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemId"][7] = 700061
	tKillMonsterDropItem_RewardItem[7703][1][3]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7703][1][3]["IsGlobal"] = 12
	
	-- 10气力		5
	tKillMonsterDropItem_RewardItem[7703][1][4] = {}
	tKillMonsterDropItem_RewardItem[7703][1][4]["ItemId"] = 3006537
	tKillMonsterDropItem_RewardItem[7703][1][4]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7703][1][4]["IsGlobal"] = 4

	-- 流星		8
	tKillMonsterDropItem_RewardItem[7703][1][5] = {}
	tKillMonsterDropItem_RewardItem[7703][1][5]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7703][1][5]["ItemNum"] = 8
	tKillMonsterDropItem_RewardItem[7703][1][5]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7703][1][5]["Range"] = 19
	tKillMonsterDropItem_RewardItem[7703][1][5]["Sub"] = 10

	------------------------------- 幽影地魂
	tKillMonsterDropItem_RewardItem[7704] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7704][1] = {}
	-- 赤炼石+1		3
	tKillMonsterDropItem_RewardItem[7704][1][1] = {}
	tKillMonsterDropItem_RewardItem[7704][1][1]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7704][1][1]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7704][1][1]["IsGlobal"] = 23
	
	-- 普通天地玄	5
	tKillMonsterDropItem_RewardItem[7704][1][2] = {}
	tKillMonsterDropItem_RewardItem[7704][1][2]["ItemId"] = {}
	tKillMonsterDropItem_RewardItem[7704][1][2]["ItemId"][1] = 700071
	tKillMonsterDropItem_RewardItem[7704][1][2]["ItemId"][2] = 700101
	tKillMonsterDropItem_RewardItem[7704][1][2]["ItemId"][3] = 700121
	tKillMonsterDropItem_RewardItem[7704][1][2]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7704][1][2]["IsGlobal"] = 14
	
	-- 通神丹		5
	tKillMonsterDropItem_RewardItem[7704][1][3] = {}
	tKillMonsterDropItem_RewardItem[7704][1][3]["ItemId"] = 3006540
	tKillMonsterDropItem_RewardItem[7704][1][3]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7704][1][3]["IsGlobal"] = 8
	
	-- 30气力		3
	tKillMonsterDropItem_RewardItem[7704][1][4] = {}
	tKillMonsterDropItem_RewardItem[7704][1][4]["ItemId"] = 3006538
	tKillMonsterDropItem_RewardItem[7704][1][4]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7704][1][4]["IsGlobal"] = 5
	
	-- 流星		10
	tKillMonsterDropItem_RewardItem[7704][1][5] = {}
	tKillMonsterDropItem_RewardItem[7704][1][5]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7704][1][5]["ItemNum"] = 10
	tKillMonsterDropItem_RewardItem[7704][1][5]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7704][1][5]["Range"] = 19
	tKillMonsterDropItem_RewardItem[7704][1][5]["Sub"] = 10

	------------------------------- 幽游地魔
	tKillMonsterDropItem_RewardItem[7705] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7705][1] = {}
	-- 赤炼石+1		5
	tKillMonsterDropItem_RewardItem[7705][1][1] = {}
	tKillMonsterDropItem_RewardItem[7705][1][1]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7705][1][1]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7705][1][1]["IsGlobal"] = 23
	
	-- 普通天地玄	3
	tKillMonsterDropItem_RewardItem[7705][1][2] = {}
	tKillMonsterDropItem_RewardItem[7705][1][2]["ItemId"] = {}
	tKillMonsterDropItem_RewardItem[7705][1][2]["ItemId"][1] = 700071
	tKillMonsterDropItem_RewardItem[7705][1][2]["ItemId"][2] = 700101
	tKillMonsterDropItem_RewardItem[7705][1][2]["ItemId"][3] = 700121
	tKillMonsterDropItem_RewardItem[7705][1][2]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7705][1][2]["IsGlobal"] = 14
	
	-- 通神丹		5
	tKillMonsterDropItem_RewardItem[7705][1][3] = {}
	tKillMonsterDropItem_RewardItem[7705][1][3]["ItemId"] = 3006540
	tKillMonsterDropItem_RewardItem[7705][1][3]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7705][1][3]["IsGlobal"] = 8

	-- 50气力		3
	tKillMonsterDropItem_RewardItem[7705][1][4] = {}
	tKillMonsterDropItem_RewardItem[7705][1][4]["ItemId"] = 3006539
	tKillMonsterDropItem_RewardItem[7705][1][4]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7705][1][4]["IsGlobal"] = 6
	
	-- 流星		12
	tKillMonsterDropItem_RewardItem[7705][1][5] = {}
	tKillMonsterDropItem_RewardItem[7705][1][5]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7705][1][5]["ItemNum"] = 12
	tKillMonsterDropItem_RewardItem[7705][1][5]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7705][1][5]["Range"] = 19
	tKillMonsterDropItem_RewardItem[7705][1][5]["Sub"] = 10

	------------------------------- 幽寂豺狼
	tKillMonsterDropItem_RewardItem[7706] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7706][1] = {}
	-- 赤炼石+2		1
	tKillMonsterDropItem_RewardItem[7706][1][1] = {}
	tKillMonsterDropItem_RewardItem[7706][1][1]["ItemId"] = 3006552
	tKillMonsterDropItem_RewardItem[7706][1][1]["ItemNum"] = 1
	tKillMonsterDropItem_RewardItem[7706][1][1]["IsGlobal"] = 24
	
	-- 赤炼石+1		3
	tKillMonsterDropItem_RewardItem[7706][1][2] = {}
	tKillMonsterDropItem_RewardItem[7706][1][2]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7706][1][2]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7706][1][2]["IsGlobal"] = 23
	
	-- 龙珠		1
	tKillMonsterDropItem_RewardItem[7706][1][3] = {}
	tKillMonsterDropItem_RewardItem[7706][1][3]["ItemId"] = 3006549
	tKillMonsterDropItem_RewardItem[7706][1][3]["ItemNum"] = 1
	tKillMonsterDropItem_RewardItem[7706][1][3]["IsGlobal"] = 18
	
	-- 免费强炼丹		3
	tKillMonsterDropItem_RewardItem[7706][1][4] = {}
	tKillMonsterDropItem_RewardItem[7706][1][4]["ItemId"] = 3006541
	tKillMonsterDropItem_RewardItem[7706][1][4]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7706][1][4]["IsGlobal"] = 9
	
	-- 通神丹		5
	tKillMonsterDropItem_RewardItem[7706][1][5] = {}
	tKillMonsterDropItem_RewardItem[7706][1][5]["ItemId"] = 3006540
	tKillMonsterDropItem_RewardItem[7706][1][5]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7706][1][5]["IsGlobal"] = 8
	
	-- 护心丹		3
	tKillMonsterDropItem_RewardItem[7706][1][6] = {}
	tKillMonsterDropItem_RewardItem[7706][1][6]["ItemId"] = 3002029
	tKillMonsterDropItem_RewardItem[7706][1][6]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7706][1][6]["IsGlobal"] = 7
	
	-- 10气力		3
	tKillMonsterDropItem_RewardItem[7706][1][7] = {}
	tKillMonsterDropItem_RewardItem[7706][1][7]["ItemId"] = 3006537
	tKillMonsterDropItem_RewardItem[7706][1][7]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7706][1][7]["IsGlobal"] = 4
	
	-- 流星		16
	tKillMonsterDropItem_RewardItem[7706][1][8] = {}
	tKillMonsterDropItem_RewardItem[7706][1][8]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7706][1][8]["ItemNum"] = 16
	tKillMonsterDropItem_RewardItem[7706][1][8]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7706][1][8]["Range"] = 23
	tKillMonsterDropItem_RewardItem[7706][1][8]["Sub"] = 12

	------------------------------- 幽冥麒麟
	tKillMonsterDropItem_RewardItem[7707] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7707][1] = {}
	-- 赤炼石+3		1
	tKillMonsterDropItem_RewardItem[7707][1][1] = {}
	tKillMonsterDropItem_RewardItem[7707][1][1]["ItemId"] = 3006553
	tKillMonsterDropItem_RewardItem[7707][1][1]["ItemNum"] = 1
	tKillMonsterDropItem_RewardItem[7707][1][1]["IsGlobal"] = 25
	
	-- 赤炼石+1		3
	tKillMonsterDropItem_RewardItem[7707][1][2] = {}
	tKillMonsterDropItem_RewardItem[7707][1][2]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7707][1][2]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7707][1][2]["IsGlobal"] = 23

	-- 龙珠		1
	tKillMonsterDropItem_RewardItem[7707][1][3] = {}
	tKillMonsterDropItem_RewardItem[7707][1][3]["ItemId"] = 3006549
	tKillMonsterDropItem_RewardItem[7707][1][3]["ItemNum"] = 1
	tKillMonsterDropItem_RewardItem[7707][1][3]["IsGlobal"] = 18
	
	-- 免费强炼丹		3
	tKillMonsterDropItem_RewardItem[7707][1][4] = {}
	tKillMonsterDropItem_RewardItem[7707][1][4]["ItemId"] = 3006541
	tKillMonsterDropItem_RewardItem[7707][1][4]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7707][1][4]["IsGlobal"] = 9
	
	-- 通神丹		5
	tKillMonsterDropItem_RewardItem[7707][1][5] = {}
	tKillMonsterDropItem_RewardItem[7707][1][5]["ItemId"] = 3006540
	tKillMonsterDropItem_RewardItem[7707][1][5]["ItemNum"] = 5
	tKillMonsterDropItem_RewardItem[7707][1][5]["IsGlobal"] = 8
	
	-- 护心丹		3
	tKillMonsterDropItem_RewardItem[7707][1][6] = {}
	tKillMonsterDropItem_RewardItem[7707][1][6]["ItemId"] = 3002029
	tKillMonsterDropItem_RewardItem[7707][1][6]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7707][1][6]["IsGlobal"] = 7
	
	-- 30气力		3
	tKillMonsterDropItem_RewardItem[7707][1][7] = {}
	tKillMonsterDropItem_RewardItem[7707][1][7]["ItemId"] = 3006538
	tKillMonsterDropItem_RewardItem[7707][1][7]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7707][1][7]["IsGlobal"] = 5
	
	-- 流星		18
	tKillMonsterDropItem_RewardItem[7707][1][8] = {}
	tKillMonsterDropItem_RewardItem[7707][1][8]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7707][1][8]["ItemNum"] = 18
	tKillMonsterDropItem_RewardItem[7707][1][8]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7707][1][8]["Range"] = 23
	tKillMonsterDropItem_RewardItem[7707][1][8]["Sub"] = 12

	------------------------------- 九幽金睛兽
	tKillMonsterDropItem_RewardItem[7708] = {}
	-- 普通时间
	tKillMonsterDropItem_RewardItem[7708][1] = {}
	-- 赤炼石+3		1
	tKillMonsterDropItem_RewardItem[7708][1][1] = {}
	tKillMonsterDropItem_RewardItem[7708][1][1]["ItemId"] = 3006553
	tKillMonsterDropItem_RewardItem[7708][1][1]["ItemNum"] = 1
	tKillMonsterDropItem_RewardItem[7708][1][1]["IsGlobal"] = 25
	
	-- 赤炼石+1		3
	tKillMonsterDropItem_RewardItem[7708][1][2] = {}
	tKillMonsterDropItem_RewardItem[7708][1][2]["ItemId"] = 3006551
	tKillMonsterDropItem_RewardItem[7708][1][2]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][2]["IsGlobal"] = 23

	-- 良品天地玄		3
	tKillMonsterDropItem_RewardItem[7708][1][3] = {}
	tKillMonsterDropItem_RewardItem[7708][1][3]["ItemId"] = 3006545
	tKillMonsterDropItem_RewardItem[7708][1][3]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][3]["IsGlobal"] = 15
	
	-- 免费强炼丹		3
	tKillMonsterDropItem_RewardItem[7708][1][4] = {}
	tKillMonsterDropItem_RewardItem[7708][1][4]["ItemId"] = 3006541
	tKillMonsterDropItem_RewardItem[7708][1][4]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][4]["IsGlobal"] = 9
	
	-- 通神丹		3
	tKillMonsterDropItem_RewardItem[7708][1][5] = {}
	tKillMonsterDropItem_RewardItem[7708][1][5]["ItemId"] = 3006540
	tKillMonsterDropItem_RewardItem[7708][1][5]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][5]["IsGlobal"] = 8
	
	-- 护心丹		3
	tKillMonsterDropItem_RewardItem[7708][1][6] = {}
	tKillMonsterDropItem_RewardItem[7708][1][6]["ItemId"] = 3002029
	tKillMonsterDropItem_RewardItem[7708][1][6]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][6]["IsGlobal"] = 7
	
	-- 50气力		3
	tKillMonsterDropItem_RewardItem[7708][1][7] = {}
	tKillMonsterDropItem_RewardItem[7708][1][7]["ItemId"] = 3006539
	tKillMonsterDropItem_RewardItem[7708][1][7]["ItemNum"] = 3
	tKillMonsterDropItem_RewardItem[7708][1][7]["IsGlobal"] = 6
	
	-- 流星		20
	tKillMonsterDropItem_RewardItem[7708][1][8] = {}
	tKillMonsterDropItem_RewardItem[7708][1][8]["ItemId"] = 1088001
	tKillMonsterDropItem_RewardItem[7708][1][8]["ItemNum"] = 20
	tKillMonsterDropItem_RewardItem[7708][1][8]["IsAdditional"] = true
	tKillMonsterDropItem_RewardItem[7708][1][8]["Range"] = 23
	tKillMonsterDropItem_RewardItem[7708][1][8]["Sub"] = 12

-- BOSS的额外奖励
local tKillMonsterDropItem_Boss	= {}
	-- 幽暗地妖
	tKillMonsterDropItem_Boss[7703] = {}
	tKillMonsterDropItem_Boss[7703]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7703]["WorstItem"] = 3006552
	
	-- 龙珠				30%
	tKillMonsterDropItem_Boss[7703][1] = {}
	tKillMonsterDropItem_Boss[7703][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7703][1]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7703][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7703][1]["Item_1"][1] = 3006549
	tKillMonsterDropItem_Boss[7703][1]["IsGlobal"] = 18

	-- 六阶神魂随机包	20%
	tKillMonsterDropItem_Boss[7703][2] = {}
	tKillMonsterDropItem_Boss[7703][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7703][2]["ItemChance"] = 2000
	tKillMonsterDropItem_Boss[7703][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7703][2]["Item_1"][1] = 3004059
	tKillMonsterDropItem_Boss[7703][2]["IsGlobal"] = 19

	-- 赤炼石+2			30%
	tKillMonsterDropItem_Boss[7703][3] = {}
	tKillMonsterDropItem_Boss[7703][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7703][3]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7703][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7703][3]["Item_1"][1] = 3006552
	tKillMonsterDropItem_Boss[7703][3]["IsGlobal"] = 24

	-- 赤炼石+3			20%
	tKillMonsterDropItem_Boss[7703][4] = {}
	tKillMonsterDropItem_Boss[7703][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7703][4]["ItemChance"] = 2000
	tKillMonsterDropItem_Boss[7703][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7703][4]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7703][4]["IsGlobal"] = 25

	-- 幽影地魂
	tKillMonsterDropItem_Boss[7704] = {}
	tKillMonsterDropItem_Boss[7704]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7704]["WorstItem"] = 3006552
	
	-- 优质天地玄	1.50%
	tKillMonsterDropItem_Boss[7704][1] = {}
	tKillMonsterDropItem_Boss[7704][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][1]["ItemChance"] = 150
	tKillMonsterDropItem_Boss[7704][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][1]["Item_1"][1] = 3006546
	tKillMonsterDropItem_Boss[7704][1]["Item_1"][2] = 3006547
	tKillMonsterDropItem_Boss[7704][1]["Item_1"][3] = 3006548
	tKillMonsterDropItem_Boss[7704][1]["IsGlobal"] = 16

	-- 龙珠	30%
	tKillMonsterDropItem_Boss[7704][2] = {}
	tKillMonsterDropItem_Boss[7704][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][2]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7704][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][2]["Item_1"][1] = 3006549
	tKillMonsterDropItem_Boss[7704][2]["IsGlobal"] = 18

	-- 六阶神魂随机包	7%
	tKillMonsterDropItem_Boss[7704][3] = {}
	tKillMonsterDropItem_Boss[7704][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][3]["ItemChance"] = 700
	tKillMonsterDropItem_Boss[7704][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][3]["Item_1"][1] = 3004059
	tKillMonsterDropItem_Boss[7704][3]["IsGlobal"] = 19

	-- 神魂礼包洗非赠	0.50%
	tKillMonsterDropItem_Boss[7704][4] = {}
	tKillMonsterDropItem_Boss[7704][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][4]["ItemChance"] = 50
	tKillMonsterDropItem_Boss[7704][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][4]["Item_1"][1] = 3006550
	tKillMonsterDropItem_Boss[7704][4]["IsGlobal"] = 20

	-- 七阶武器神魂礼包		0.50%
	tKillMonsterDropItem_Boss[7704][5] = {}
	tKillMonsterDropItem_Boss[7704][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][5]["ItemChance"] = 50
	tKillMonsterDropItem_Boss[7704][5]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][5]["Item_1"][1] = 3006745
	tKillMonsterDropItem_Boss[7704][5]["IsGlobal"] = 21

	-- 七阶防具配饰神魂礼包		0.50%
	tKillMonsterDropItem_Boss[7704][6] = {}
	tKillMonsterDropItem_Boss[7704][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][6]["ItemChance"] = 50
	tKillMonsterDropItem_Boss[7704][6]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][6]["Item_1"][1] = 3006746
	tKillMonsterDropItem_Boss[7704][6]["IsGlobal"] = 22

	-- 赤炼石+2			50%
	tKillMonsterDropItem_Boss[7704][7] = {}
	tKillMonsterDropItem_Boss[7704][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][7]["ItemChance"] = 5000
	tKillMonsterDropItem_Boss[7704][7]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][7]["Item_1"][1] = 3006552
	tKillMonsterDropItem_Boss[7704][7]["IsGlobal"] = 24

	-- 赤炼石+3			10%
	tKillMonsterDropItem_Boss[7704][8] = {}
	tKillMonsterDropItem_Boss[7704][8]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7704][8]["ItemChance"] = 1000
	tKillMonsterDropItem_Boss[7704][8]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7704][8]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7704][8]["IsGlobal"] = 25

	-- 幽游地魔
	tKillMonsterDropItem_Boss[7705] = {}
	tKillMonsterDropItem_Boss[7705]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7705]["WorstItem"] = 3006552
	
	-- 优质天地玄	3%
	tKillMonsterDropItem_Boss[7705][1] = {}
	tKillMonsterDropItem_Boss[7705][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][1]["ItemChance"] = 300
	tKillMonsterDropItem_Boss[7705][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][1]["Item_1"][1] = 3006546
	tKillMonsterDropItem_Boss[7705][1]["Item_1"][2] = 3006547
	tKillMonsterDropItem_Boss[7705][1]["Item_1"][3] = 3006548
	tKillMonsterDropItem_Boss[7705][1]["IsGlobal"] = 16

	-- 龙珠	30%
	tKillMonsterDropItem_Boss[7705][2] = {}
	tKillMonsterDropItem_Boss[7705][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][2]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7705][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][2]["Item_1"][1] = 3006549
	tKillMonsterDropItem_Boss[7705][2]["IsGlobal"] = 18

	-- 六阶神魂随机包	3%
	tKillMonsterDropItem_Boss[7705][3] = {}
	tKillMonsterDropItem_Boss[7705][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][3]["ItemChance"] = 300
	tKillMonsterDropItem_Boss[7705][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][3]["Item_1"][1] = 3004059
	tKillMonsterDropItem_Boss[7705][3]["IsGlobal"] = 19

	-- 神魂礼包洗非赠	1%
	tKillMonsterDropItem_Boss[7705][4] = {}
	tKillMonsterDropItem_Boss[7705][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][4]["ItemChance"] = 100
	tKillMonsterDropItem_Boss[7705][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][4]["Item_1"][1] = 3006550
	tKillMonsterDropItem_Boss[7705][4]["IsGlobal"] = 20

	-- 七阶武器神魂礼包		1%
	tKillMonsterDropItem_Boss[7705][5] = {}
	tKillMonsterDropItem_Boss[7705][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][5]["ItemChance"] = 100
	tKillMonsterDropItem_Boss[7705][5]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][5]["Item_1"][1] = 3006745
	tKillMonsterDropItem_Boss[7705][5]["IsGlobal"] = 21

	-- 七阶防具配饰神魂礼包		1%
	tKillMonsterDropItem_Boss[7705][6] = {}
	tKillMonsterDropItem_Boss[7705][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][6]["ItemChance"] = 100
	tKillMonsterDropItem_Boss[7705][6]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][6]["Item_1"][1] = 3006746
	tKillMonsterDropItem_Boss[7705][6]["IsGlobal"] = 22

	-- 赤炼石+2			50%
	tKillMonsterDropItem_Boss[7705][7] = {}
	tKillMonsterDropItem_Boss[7705][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][7]["ItemChance"] = 5000
	tKillMonsterDropItem_Boss[7705][7]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][7]["Item_1"][1] = 3006552
	tKillMonsterDropItem_Boss[7705][7]["IsGlobal"] = 24

	-- 赤炼石+3			10%
	tKillMonsterDropItem_Boss[7705][8] = {}
	tKillMonsterDropItem_Boss[7705][8]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][8]["ItemChance"] = 1000
	tKillMonsterDropItem_Boss[7705][8]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][8]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7705][8]["IsGlobal"] = 25

	-- 赤炼石+6			1%
	tKillMonsterDropItem_Boss[7705][9] = {}
	tKillMonsterDropItem_Boss[7705][9]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7705][9]["ItemChance"] = 100
	tKillMonsterDropItem_Boss[7705][9]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7705][9]["Item_1"][1] = 3006554
	tKillMonsterDropItem_Boss[7705][9]["IsGlobal"] = 26

	-- 幽寂豺狼
	tKillMonsterDropItem_Boss[7706] = {}
	tKillMonsterDropItem_Boss[7706]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7706]["WorstItem"] = 3006553
	
	-- 良品天地玄	40%
	tKillMonsterDropItem_Boss[7706][1] = {}
	tKillMonsterDropItem_Boss[7706][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][1]["ItemChance"] = 4000
	tKillMonsterDropItem_Boss[7706][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][1]["Item_1"][1] = 3006545
	tKillMonsterDropItem_Boss[7706][1]["IsGlobal"] = 15

	-- 优质天地玄	5%
	tKillMonsterDropItem_Boss[7706][2] = {}
	tKillMonsterDropItem_Boss[7706][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][2]["ItemChance"] = 500
	tKillMonsterDropItem_Boss[7706][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][2]["Item_1"][1] = 3006546
	tKillMonsterDropItem_Boss[7706][2]["Item_1"][2] = 3006547
	tKillMonsterDropItem_Boss[7706][2]["Item_1"][3] = 3006548
	tKillMonsterDropItem_Boss[7706][2]["IsGlobal"] = 16

	-- 六阶神魂随机包	15%
	tKillMonsterDropItem_Boss[7706][3] = {}
	tKillMonsterDropItem_Boss[7706][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][3]["ItemChance"] = 1500
	tKillMonsterDropItem_Boss[7706][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][3]["Item_1"][1] = 3004059
	tKillMonsterDropItem_Boss[7706][3]["IsGlobal"] = 19

	-- 神魂礼包洗非赠	5%
	tKillMonsterDropItem_Boss[7706][4] = {}
	tKillMonsterDropItem_Boss[7706][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][4]["ItemChance"] = 500
	tKillMonsterDropItem_Boss[7706][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][4]["Item_1"][1] = 3006550
	tKillMonsterDropItem_Boss[7706][4]["IsGlobal"] = 20

	-- 七阶防具配饰神魂礼包		5%
	tKillMonsterDropItem_Boss[7706][5] = {}
	tKillMonsterDropItem_Boss[7706][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][5]["ItemChance"] = 500
	tKillMonsterDropItem_Boss[7706][5]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][5]["Item_1"][1] = 3006746
	tKillMonsterDropItem_Boss[7706][5]["IsGlobal"] = 22

	-- 赤炼石+3			30%
	tKillMonsterDropItem_Boss[7706][6] = {}
	tKillMonsterDropItem_Boss[7706][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7706][6]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7706][6]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7706][6]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7706][6]["IsGlobal"] = 25

	-- 幽冥麒麟
	tKillMonsterDropItem_Boss[7707] = {}
	tKillMonsterDropItem_Boss[7707]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7707]["WorstItem"] = 3006553
	
	-- 优质天地玄	15%
	tKillMonsterDropItem_Boss[7707][1] = {}
	tKillMonsterDropItem_Boss[7707][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][1]["ItemChance"] = 1500
	tKillMonsterDropItem_Boss[7707][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][1]["Item_1"][1] = 3006546
	tKillMonsterDropItem_Boss[7707][1]["Item_1"][2] = 3006547
	tKillMonsterDropItem_Boss[7707][1]["Item_1"][3] = 3006548
	tKillMonsterDropItem_Boss[7707][1]["IsGlobal"] = 16

	-- 六阶神魂随机包	30%
	tKillMonsterDropItem_Boss[7707][2] = {}
	tKillMonsterDropItem_Boss[7707][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][2]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7707][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][2]["Item_1"][1] = 3004059
	tKillMonsterDropItem_Boss[7707][2]["IsGlobal"] = 19

	-- 神魂礼包洗非赠	10%
	tKillMonsterDropItem_Boss[7707][3] = {}
	tKillMonsterDropItem_Boss[7707][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][3]["ItemChance"] = 1000
	tKillMonsterDropItem_Boss[7707][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][3]["Item_1"][1] = 3006550
	tKillMonsterDropItem_Boss[7707][3]["IsGlobal"] = 20

	-- 七阶武器神魂礼包		5%
	tKillMonsterDropItem_Boss[7707][4] = {}
	tKillMonsterDropItem_Boss[7707][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][4]["ItemChance"] = 500
	tKillMonsterDropItem_Boss[7707][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][4]["Item_1"][1] = 3006745
	tKillMonsterDropItem_Boss[7707][4]["IsGlobal"] = 21

	-- 七阶防具配饰神魂礼包		10%
	tKillMonsterDropItem_Boss[7707][5] = {}
	tKillMonsterDropItem_Boss[7707][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][5]["ItemChance"] = 1000
	tKillMonsterDropItem_Boss[7707][5]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][5]["Item_1"][1] = 3006746
	tKillMonsterDropItem_Boss[7707][5]["IsGlobal"] = 22

	-- 赤炼石+3		30%
	tKillMonsterDropItem_Boss[7707][6] = {}
	tKillMonsterDropItem_Boss[7707][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7707][6]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7707][6]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7707][6]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7707][6]["IsGlobal"] = 25

	-- 九幽金睛兽
	tKillMonsterDropItem_Boss[7708] = {}
	tKillMonsterDropItem_Boss[7708]["ItemChanceSum"] = 10000
	tKillMonsterDropItem_Boss[7708]["WorstItem"] = 3006553
	
	-- 优质天地玄	30%
	tKillMonsterDropItem_Boss[7708][1] = {}
	tKillMonsterDropItem_Boss[7708][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][1]["ItemChance"] = 3000
	tKillMonsterDropItem_Boss[7708][1]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][1]["Item_1"][1] = 3006546
	tKillMonsterDropItem_Boss[7708][1]["Item_1"][2] = 3006547
	tKillMonsterDropItem_Boss[7708][1]["Item_1"][3] = 3006548
	tKillMonsterDropItem_Boss[7708][1]["IsGlobal"] = 16

	-- 神魂礼包洗非赠	20%
	tKillMonsterDropItem_Boss[7708][2] = {}
	tKillMonsterDropItem_Boss[7708][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][2]["ItemChance"] = 2000
	tKillMonsterDropItem_Boss[7708][2]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][2]["Item_1"][1] = 3006550
	tKillMonsterDropItem_Boss[7708][2]["IsGlobal"] = 20

	-- 七阶武器神魂礼包		10%
	tKillMonsterDropItem_Boss[7708][3] = {}
	tKillMonsterDropItem_Boss[7708][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][3]["ItemChance"] = 1000
	tKillMonsterDropItem_Boss[7708][3]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][3]["Item_1"][1] = 3006745
	tKillMonsterDropItem_Boss[7708][3]["IsGlobal"] = 21

	-- 七阶防具配饰神魂礼包		20%
	tKillMonsterDropItem_Boss[7708][4] = {}
	tKillMonsterDropItem_Boss[7708][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][4]["ItemChance"] = 2000
	tKillMonsterDropItem_Boss[7708][4]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][4]["Item_1"][1] = 3006746
	tKillMonsterDropItem_Boss[7708][4]["IsGlobal"] = 22

	-- 赤炼石+3		15%
	tKillMonsterDropItem_Boss[7708][5] = {}
	tKillMonsterDropItem_Boss[7708][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][5]["ItemChance"] = 1500
	tKillMonsterDropItem_Boss[7708][5]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][5]["Item_1"][1] = 3006553
	tKillMonsterDropItem_Boss[7708][5]["IsGlobal"] = 25

	-- 赤炼石+6		5%
	tKillMonsterDropItem_Boss[7708][6] = {}
	tKillMonsterDropItem_Boss[7708][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_Boss[7708][6]["ItemChance"] = 500
	tKillMonsterDropItem_Boss[7708][6]["Item_1"] = {}
	tKillMonsterDropItem_Boss[7708][6]["Item_1"][1] = 3006554
	tKillMonsterDropItem_Boss[7708][6]["IsGlobal"] = 26

-- 礼包对应积分
local tKillMonsterDropItem_ExchangeScore = {}
	-- 良品宝石礼包
	tKillMonsterDropItem_ExchangeScore[3006544] = {}
	tKillMonsterDropItem_ExchangeScore[3006544]["Score"] = 10
	
	-- 良品稀有宝石礼包
	tKillMonsterDropItem_ExchangeScore[3006545] = {}
	tKillMonsterDropItem_ExchangeScore[3006545]["Score"] = 80
	
	-- 优质天怒宝石礼包。
	tKillMonsterDropItem_ExchangeScore[3006546] = {}
	tKillMonsterDropItem_ExchangeScore[3006546]["Score"] = 1600
	
	-- 优质地灵宝石礼包。
	tKillMonsterDropItem_ExchangeScore[3006547] = {}
	tKillMonsterDropItem_ExchangeScore[3006547]["Score"] = 1600
	
	-- 优质玄元宝石礼包。
	tKillMonsterDropItem_ExchangeScore[3006548] = {}
	tKillMonsterDropItem_ExchangeScore[3006548]["Score"] = 1600
	
	-- 龙珠礼包。
	tKillMonsterDropItem_ExchangeScore[3006549] = {}
	tKillMonsterDropItem_ExchangeScore[3006549]["Score"] = 240
	
	-- +1赤炼石礼包。
	tKillMonsterDropItem_ExchangeScore[3006551] = {}
	tKillMonsterDropItem_ExchangeScore[3006551]["Score"] = 25
	
	-- +2赤炼石礼包。
	tKillMonsterDropItem_ExchangeScore[3006552] = {}
	tKillMonsterDropItem_ExchangeScore[3006552]["Score"] = 100
	
	-- +3赤炼石礼包。
	tKillMonsterDropItem_ExchangeScore[3006553] = {}
	tKillMonsterDropItem_ExchangeScore[3006553]["Score"] = 300
	
	-- +6赤炼石礼包。
	tKillMonsterDropItem_ExchangeScore[3006554] = {}
	tKillMonsterDropItem_ExchangeScore[3006554]["Score"] = 8000

	-- 九幽神魂礼包洗赠卷
	tKillMonsterDropItem_ExchangeScore[3006550] = {}
	tKillMonsterDropItem_ExchangeScore[3006550]["Score"] = 1200

-- 小任务的奖励
local tKillMonsterDropItem_TaskReward = {}
	tKillMonsterDropItem_TaskReward[1] = {}
	tKillMonsterDropItem_TaskReward[1]["ItemChanceSum"] = 10000
	-- 究极通神丹（赠）		15%
	tKillMonsterDropItem_TaskReward[1][1] = {}
	tKillMonsterDropItem_TaskReward[1][1]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][1]["ItemChance"] = 1500
	tKillMonsterDropItem_TaskReward[1][1]["Item_1"] = 3003126
	tKillMonsterDropItem_TaskReward[1][1]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_TaskReward[1][1]["Index"] = 1
	tKillMonsterDropItem_TaskReward[1][1]["Log"] = "0,0,0,0,12000103,2,3003126,1"
	
	-- 护心丹		20%
	tKillMonsterDropItem_TaskReward[1][2] = {}
	tKillMonsterDropItem_TaskReward[1][2]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][2]["ItemChance"] = 2000
	tKillMonsterDropItem_TaskReward[1][2]["Item_1"] = 3002029
	tKillMonsterDropItem_TaskReward[1][2]["ItemAttr"] = "0 1 0 0 1"
	tKillMonsterDropItem_TaskReward[1][2]["Index"] = 2
	tKillMonsterDropItem_TaskReward[1][2]["Log"] = "0,0,0,0,12000103,2,3002029,1"
	
	-- +2赤练石（赠）		10%
	tKillMonsterDropItem_TaskReward[1][3] = {}
	tKillMonsterDropItem_TaskReward[1][3]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][3]["ItemChance"] = 1000
	tKillMonsterDropItem_TaskReward[1][3]["Item_1"] = 730002
	tKillMonsterDropItem_TaskReward[1][3]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_TaskReward[1][3]["Index"] = 3
	tKillMonsterDropItem_TaskReward[1][3]["Log"] = "0,0,0,0,12000103,2,730002,1"
	
	-- 免费强炼丹（赠）*2		10%
	tKillMonsterDropItem_TaskReward[1][4] = {}
	tKillMonsterDropItem_TaskReward[1][4]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][4]["ItemChance"] = 1000
	tKillMonsterDropItem_TaskReward[1][4]["Item_1"] = 3003124
	tKillMonsterDropItem_TaskReward[1][4]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_TaskReward[1][4]["Index"] = 4
	tKillMonsterDropItem_TaskReward[1][4]["Log"] = "0,0,0,0,12000103,2,3003124,2"
	
	-- 50点气力值		20%
	tKillMonsterDropItem_TaskReward[1][5] = {}
	tKillMonsterDropItem_TaskReward[1][5]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][5]["ItemChance"] = 2000
	tKillMonsterDropItem_TaskReward[1][5]["Item_1"] = 50
	tKillMonsterDropItem_TaskReward[1][5]["IsStrength"] = true
	tKillMonsterDropItem_TaskReward[1][5]["Index"] = 5
	tKillMonsterDropItem_TaskReward[1][5]["Log"] = "0,0,0,0,12000103,2,12,50"

	-- 10点赠品天石		10%
	tKillMonsterDropItem_TaskReward[1][6] = {}
	tKillMonsterDropItem_TaskReward[1][6]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][6]["ItemChance"] = 1000
	tKillMonsterDropItem_TaskReward[1][6]["Item_1"] = 10
	tKillMonsterDropItem_TaskReward[1][6]["IsEmoney"] = true
	tKillMonsterDropItem_TaskReward[1][6]["Index"] = 6
	tKillMonsterDropItem_TaskReward[1][6]["Log"] = "0,0,0,0,12000103,2,3,10"
	
	-- 60点修行值		15%
	tKillMonsterDropItem_TaskReward[1][7] = {}
	tKillMonsterDropItem_TaskReward[1][7]["RandomItemChanceType"] = 2
	tKillMonsterDropItem_TaskReward[1][7]["ItemChance"] = 1500
	tKillMonsterDropItem_TaskReward[1][7]["Item_1"] = 60
	tKillMonsterDropItem_TaskReward[1][7]["IsCultivation"] = true
	tKillMonsterDropItem_TaskReward[1][7]["Index"] = 7
	tKillMonsterDropItem_TaskReward[1][7]["Log"] = "0,0,0,0,12000103,2,6,60"

-- 礼包配置
local tKillMonsterDropItem_Item = {}
	-- 10分钟经验礼包
	tKillMonsterDropItem_Item[3006531] = {}
	tKillMonsterDropItem_Item[3006531]["EventType"] = 134
	tKillMonsterDropItem_Item[3006531]["DataType"] = 89
	tKillMonsterDropItem_Item[3006531]["MaxData"] = 10
	tKillMonsterDropItem_Item[3006531]["Exp"] = 10
	tKillMonsterDropItem_Item[3006531]["Cultivation"] = 5
	tKillMonsterDropItem_Item[3006531]["ExpLog"] = "0,0,3006531,1,12000103,2,4,10"
	tKillMonsterDropItem_Item[3006531]["CultivationLog"] = "0,0,3006531,1,12000103,2,6,5"

	-- 30分钟经验礼包
	tKillMonsterDropItem_Item[3006532] = {}
	tKillMonsterDropItem_Item[3006532]["EventType"] = 134
	tKillMonsterDropItem_Item[3006532]["DataType"] = 90
	tKillMonsterDropItem_Item[3006532]["MaxData"] = 10
	tKillMonsterDropItem_Item[3006532]["Exp"] = 30
	tKillMonsterDropItem_Item[3006532]["Cultivation"] = 15
	tKillMonsterDropItem_Item[3006532]["ExpLog"] = "0,0,3006532,1,12000103,2,4,30"
	tKillMonsterDropItem_Item[3006532]["CultivationLog"] = "0,0,3006532,1,12000103,2,6,15"

	-- 50分钟经验礼包
	tKillMonsterDropItem_Item[3006533] = {}
	tKillMonsterDropItem_Item[3006533]["EventType"] = 134
	tKillMonsterDropItem_Item[3006533]["DataType"] = 91
	tKillMonsterDropItem_Item[3006533]["MaxData"] = 10
	tKillMonsterDropItem_Item[3006533]["Exp"] = 50
	tKillMonsterDropItem_Item[3006533]["Cultivation"] = 25
	tKillMonsterDropItem_Item[3006533]["ExpLog"] = "0,0,3006533,1,12000103,2,4,50"
	tKillMonsterDropItem_Item[3006533]["CultivationLog"] = "0,0,3006533,1,12000103,2,6,25"

	-- 10点修行值礼包
	tKillMonsterDropItem_Item[3006534] = {}
	tKillMonsterDropItem_Item[3006534]["Cultivation"] = 10
	tKillMonsterDropItem_Item[3006534]["Log"] = "0,0,3006534,1,12000103,2,6,10"

	-- 30点修行值礼包
	tKillMonsterDropItem_Item[3006535] = {}
	tKillMonsterDropItem_Item[3006535]["Cultivation"] = 30
	tKillMonsterDropItem_Item[3006535]["Log"] = "0,0,3006535,1,12000103,2,6,30"

	-- 50点修行值礼包
	tKillMonsterDropItem_Item[3006536] = {}
	tKillMonsterDropItem_Item[3006536]["Cultivation"] = 50
	tKillMonsterDropItem_Item[3006536]["Log"] = "0,0,3006536,1,12000103,2,6,50"

	-- 10点气力值礼包
	tKillMonsterDropItem_Item[3006537] = {}
	tKillMonsterDropItem_Item[3006537]["StrengthValue"] = 10
	tKillMonsterDropItem_Item[3006537]["Log"] = "0,0,3006537,1,12000103,2,12,10"
	
	-- 30点气力值礼包
	tKillMonsterDropItem_Item[3006538] = {}
	tKillMonsterDropItem_Item[3006538]["StrengthValue"] = 30
	tKillMonsterDropItem_Item[3006538]["Log"] = "0,0,3006538,1,12000103,2,12,30"

	-- 50点气力值礼包
	tKillMonsterDropItem_Item[3006539] = {}
	tKillMonsterDropItem_Item[3006539]["StrengthValue"] = 50
	tKillMonsterDropItem_Item[3006539]["Log"] = "0,0,3006539,1,12000103,2,12,50"

	-- 通神丹礼包
	tKillMonsterDropItem_Item[3006540] = {}
	tKillMonsterDropItem_Item[3006540]["ItemId"] = 3003125
	tKillMonsterDropItem_Item[3006540]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006540]["Log"] = "0,0,3006540,1,12000103,2,3003125,1"
	tKillMonsterDropItem_Item[3006540]["Space"] = 1

	-- 免费强炼丹礼包
	tKillMonsterDropItem_Item[3006541] = {}
	tKillMonsterDropItem_Item[3006541]["ItemId"] = 3003124
	tKillMonsterDropItem_Item[3006541]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006541]["Log"] = "0,0,3006541,1,12000103,2,3003124,1"
	tKillMonsterDropItem_Item[3006541]["Space"] = 1
	
	-- 真气礼包
	tKillMonsterDropItem_Item[3006542] = {}
	tKillMonsterDropItem_Item[3006542]["ZhenQi"] = 1
	tKillMonsterDropItem_Item[3006542]["Log"] = "0,0,3006542,1,12000103,2,16,1"

	-- 修炼礼包
	tKillMonsterDropItem_Item[3006543] = {}
	tKillMonsterDropItem_Item[3006543]["PractNum"] = 10000
	tKillMonsterDropItem_Item[3006543]["Log"] = "0,0,3006543,1,12000103,2,17,1"

	-- 良品宝石礼包
	tKillMonsterDropItem_Item[3006544] = {}
	tKillMonsterDropItem_Item[3006544]["ItemId"] = {}
	tKillMonsterDropItem_Item[3006544]["ItemId"][1] = 700002
	tKillMonsterDropItem_Item[3006544]["ItemId"][2] = 700012
	tKillMonsterDropItem_Item[3006544]["ItemId"][3] = 700022
	tKillMonsterDropItem_Item[3006544]["ItemId"][4] = 700032
	tKillMonsterDropItem_Item[3006544]["ItemId"][5] = 700042
	tKillMonsterDropItem_Item[3006544]["ItemId"][6] = 700052
	tKillMonsterDropItem_Item[3006544]["ItemId"][7] = 700062
	tKillMonsterDropItem_Item[3006544]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006544]["Log"] = "0,0,3006544,1,12000103,2,%d,1"
	tKillMonsterDropItem_Item[3006544]["Space"] = 1
	
	-- 良品稀有宝石礼包
	tKillMonsterDropItem_Item[3006545] = {}
	tKillMonsterDropItem_Item[3006545]["ItemId"] = {}
	tKillMonsterDropItem_Item[3006545]["ItemId"][1] = 700072
	tKillMonsterDropItem_Item[3006545]["ItemId"][2] = 700102
	tKillMonsterDropItem_Item[3006545]["ItemId"][3] = 700122
	tKillMonsterDropItem_Item[3006545]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006545]["Log"] = "0,0,3006545,1,12000103,2,%d,1"
	tKillMonsterDropItem_Item[3006545]["Space"] = 1
	
	-- 优质天怒宝石礼包
	tKillMonsterDropItem_Item[3006546] = {}
	tKillMonsterDropItem_Item[3006546]["ItemId"] = 700103
	tKillMonsterDropItem_Item[3006546]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006546]["Log"] = "0,0,3006546,1,12000103,2,700103,1"
	tKillMonsterDropItem_Item[3006546]["Space"] = 1
	
	-- 优质地灵宝石礼包
	tKillMonsterDropItem_Item[3006547] = {}
	tKillMonsterDropItem_Item[3006547]["ItemId"] = 700123
	tKillMonsterDropItem_Item[3006547]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006547]["Log"] = "0,0,3006547,1,12000103,2,700123,1"
	tKillMonsterDropItem_Item[3006547]["Space"] = 1

	-- 优质玄元宝石礼包
	tKillMonsterDropItem_Item[3006548] = {}
	tKillMonsterDropItem_Item[3006548]["ItemId"] = 700073
	tKillMonsterDropItem_Item[3006548]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006548]["Log"] = "0,0,3006548,1,12000103,2,700073,1"
	tKillMonsterDropItem_Item[3006548]["Space"] = 1
	
	-- 龙珠礼包
	tKillMonsterDropItem_Item[3006549] = {}
	tKillMonsterDropItem_Item[3006549]["ItemId"] = 1088000
	tKillMonsterDropItem_Item[3006549]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006549]["Log"] = "0,0,3006549,1,12000103,2,1088000,1"
	tKillMonsterDropItem_Item[3006549]["Space"] = 1

	-- +1赤炼石礼包
	tKillMonsterDropItem_Item[3006551] = {}
	tKillMonsterDropItem_Item[3006551]["ItemId"] = 730001
	tKillMonsterDropItem_Item[3006551]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006551]["Log"] = "0,0,3006551,1,12000103,2,730001,1"
	tKillMonsterDropItem_Item[3006551]["Space"] = 1
	
	-- +2赤炼石礼包
	tKillMonsterDropItem_Item[3006552] = {}
	tKillMonsterDropItem_Item[3006552]["ItemId"] = 730002
	tKillMonsterDropItem_Item[3006552]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006552]["Log"] = "0,0,3006552,1,12000103,2,730002,1"
	tKillMonsterDropItem_Item[3006552]["Space"] = 1

	-- +3赤炼石礼包
	tKillMonsterDropItem_Item[3006553] = {}
	tKillMonsterDropItem_Item[3006553]["ItemId"] = 730003
	tKillMonsterDropItem_Item[3006553]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006553]["Log"] = "0,0,3006553,1,12000103,2,730003,1"
	tKillMonsterDropItem_Item[3006553]["Space"] = 1

	-- +6赤炼石礼包
	tKillMonsterDropItem_Item[3006554] = {}
	tKillMonsterDropItem_Item[3006554]["ItemId"] = 730006
	tKillMonsterDropItem_Item[3006554]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_Item[3006554]["Log"] = "0,0,3006554,1,12000103,2,730006,1"
	tKillMonsterDropItem_Item[3006554]["Space"] = 1

	-- 九幽藏宝图
	tKillMonsterDropItem_Item[3006699] = {}
	tKillMonsterDropItem_Item[3006699]["Cultivation"] = 15
	tKillMonsterDropItem_Item[3006699]["CultivationLog"] = "0,0,3006699,1,12000103,2,6,15"
	tKillMonsterDropItem_Item[3006699]["Exp"] = 30
	tKillMonsterDropItem_Item[3006699]["ExpLog"] = "0,0,3006699,1,12000103,2,4,30"
	tKillMonsterDropItem_Item[3006699]["MapId"] = 1000
	tKillMonsterDropItem_Item[3006699]["CellX"] = 485
	tKillMonsterDropItem_Item[3006699]["CellY"] = 578
	tKillMonsterDropItem_Item[3006699]["NpcId"] = 0

-- 神魂礼包配置
local tKillMonsterDropItem_SpiritGift = {}
	-- 七阶武器神魂礼包
	tKillMonsterDropItem_SpiritGift[3006745] = {}
	-- 鬼狱狂刀
	tKillMonsterDropItem_SpiritGift[3006745][1] = {}
	tKillMonsterDropItem_SpiritGift[3006745][1]["ItemId"] = 800020
	tKillMonsterDropItem_SpiritGift[3006745][1]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][1]["Log"] = "0,0,3006745,1,12000103,2,800020,1"

	-- 轰天巨锤
	tKillMonsterDropItem_SpiritGift[3006745][2] = {}
	tKillMonsterDropItem_SpiritGift[3006745][2]["ItemId"] = 800111
	tKillMonsterDropItem_SpiritGift[3006745][2]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][2]["Log"] = "0,0,3006745,1,12000103,2,800111,1"
	
	-- 破天长戟
	tKillMonsterDropItem_SpiritGift[3006745][3] = {}
	tKillMonsterDropItem_SpiritGift[3006745][3]["ItemId"] = 800215
	tKillMonsterDropItem_SpiritGift[3006745][3]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][3]["Log"] = "0,0,3006745,1,12000103,2,800215,1"
	
	-- 忏悔之剑
	tKillMonsterDropItem_SpiritGift[3006745][4] = {}
	tKillMonsterDropItem_SpiritGift[3006745][4]["ItemId"] = 800811
	tKillMonsterDropItem_SpiritGift[3006745][4]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][4]["Log"] = "0,0,3006745,1,12000103,2,800811,1"
	
	-- 轮回之枪
	tKillMonsterDropItem_SpiritGift[3006745][5] = {}
	tKillMonsterDropItem_SpiritGift[3006745][5]["ItemId"] = 800810
	tKillMonsterDropItem_SpiritGift[3006745][5]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][5]["Log"] = "0,0,3006745,1,12000103,2,800810,1"
	
	-- 幻影忍刀
	tKillMonsterDropItem_SpiritGift[3006745][6] = {}
	tKillMonsterDropItem_SpiritGift[3006745][6]["ItemId"] = 800142
	tKillMonsterDropItem_SpiritGift[3006745][6]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][6]["Log"] = "0,0,3006745,1,12000103,2,800142,1"
	
	-- 鬼恕龙牙
	tKillMonsterDropItem_SpiritGift[3006745][7] = {}
	tKillMonsterDropItem_SpiritGift[3006745][7]["ItemId"] = 800917
	tKillMonsterDropItem_SpiritGift[3006745][7]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][7]["Log"] = "0,0,3006745,1,12000103,2,800917,1"
	
	-- 屠神钩镰
	tKillMonsterDropItem_SpiritGift[3006745][8] = {}
	tKillMonsterDropItem_SpiritGift[3006745][8]["ItemId"] = 800255
	tKillMonsterDropItem_SpiritGift[3006745][8]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][8]["Log"] = "0,0,3006745,1,12000103,2,800255,1"
	
	-- 碎魂魔盾
	tKillMonsterDropItem_SpiritGift[3006745][9] = {}
	tKillMonsterDropItem_SpiritGift[3006745][9]["ItemId"] = 800422
	tKillMonsterDropItem_SpiritGift[3006745][9]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][9]["Log"] = "0,0,3006745,1,12000103,2,800422,1"
	
	-- 虚空宝剑
	tKillMonsterDropItem_SpiritGift[3006745][10] = {}
	tKillMonsterDropItem_SpiritGift[3006745][10]["ItemId"] = 800522
	tKillMonsterDropItem_SpiritGift[3006745][10]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][10]["Log"] = "0,0,3006745,1,12000103,2,800522,1"
	
	-- 逐日灵弓
	tKillMonsterDropItem_SpiritGift[3006745][11] = {}
	tKillMonsterDropItem_SpiritGift[3006745][11]["ItemId"] = 800618
	tKillMonsterDropItem_SpiritGift[3006745][11]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][11]["Log"] = "0,0,3006745,1,12000103,2,800618,1"
	
	-- 天道念珠
	tKillMonsterDropItem_SpiritGift[3006745][12] = {}
	tKillMonsterDropItem_SpiritGift[3006745][12]["ItemId"] = 800725
	tKillMonsterDropItem_SpiritGift[3006745][12]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][12]["Log"] = "0,0,3006745,1,12000103,2,800725,1"
	
	-- 鬼舞狂战
	tKillMonsterDropItem_SpiritGift[3006745][13] = {}
	tKillMonsterDropItem_SpiritGift[3006745][13]["ItemId"] = 801004
	tKillMonsterDropItem_SpiritGift[3006745][13]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][13]["Log"] = "0,0,3006745,1,12000103,2,801004,1"
	
	-- 无极合一拂尘
	tKillMonsterDropItem_SpiritGift[3006745][14] = {}
	tKillMonsterDropItem_SpiritGift[3006745][14]["ItemId"] = 801104
	tKillMonsterDropItem_SpiritGift[3006745][14]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006745][14]["Log"] = "0,0,3006745,1,12000103,2,801104,1"
	
	-- 七阶防具配饰神魂礼包
	tKillMonsterDropItem_SpiritGift[3006746] = {}
	-- 摧月魔冠
	tKillMonsterDropItem_SpiritGift[3006746][1] = {}
	tKillMonsterDropItem_SpiritGift[3006746][1]["ItemId"] = 820073
	tKillMonsterDropItem_SpiritGift[3006746][1]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][1]["Log"] = "0,0,3006746,1,12000103,2,820073,1"
	
	-- 斩日魔冠
	tKillMonsterDropItem_SpiritGift[3006746][2] = {}
	tKillMonsterDropItem_SpiritGift[3006746][2]["ItemId"] = 820074
	tKillMonsterDropItem_SpiritGift[3006746][2]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][2]["Log"] = "0,0,3006746,1,12000103,2,820074,1"
	
	-- 飞星仙冠
	tKillMonsterDropItem_SpiritGift[3006746][3] = {}
	tKillMonsterDropItem_SpiritGift[3006746][3]["ItemId"] = 820075
	tKillMonsterDropItem_SpiritGift[3006746][3]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][3]["Log"] = "0,0,3006746,1,12000103,2,820075,1"
	
	-- 冰辰仙冠
	tKillMonsterDropItem_SpiritGift[3006746][4] = {}
	tKillMonsterDropItem_SpiritGift[3006746][4]["ItemId"] = 820076
	tKillMonsterDropItem_SpiritGift[3006746][4]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][4]["Log"] = "0,0,3006746,1,12000103,2,820076,1"
	
	-- 幽冥魔铠
	tKillMonsterDropItem_SpiritGift[3006746][5] = {}
	tKillMonsterDropItem_SpiritGift[3006746][5]["ItemId"] = 822071
	tKillMonsterDropItem_SpiritGift[3006746][5]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][5]["Log"] = "0,0,3006746,1,12000103,2,822071,1"
	
	-- 蚀日仙铠
	tKillMonsterDropItem_SpiritGift[3006746][6] = {}
	tKillMonsterDropItem_SpiritGift[3006746][6]["ItemId"] = 822072
	tKillMonsterDropItem_SpiritGift[3006746][6]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][6]["Log"] = "0,0,3006746,1,12000103,2,822072,1"
	
	-- 苍炎香囊
	tKillMonsterDropItem_SpiritGift[3006746][7] = {}
	tKillMonsterDropItem_SpiritGift[3006746][7]["ItemId"] = 821034
	tKillMonsterDropItem_SpiritGift[3006746][7]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][7]["Log"] = "0,0,3006746,1,12000103,2,821034,1"
	
	-- 灵霄仙坠
	tKillMonsterDropItem_SpiritGift[3006746][8] = {}
	tKillMonsterDropItem_SpiritGift[3006746][8]["ItemId"] = 821033
	tKillMonsterDropItem_SpiritGift[3006746][8]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][8]["Log"] = "0,0,3006746,1,12000103,2,821033,1"
	
	-- 鹤唳魔戒
	tKillMonsterDropItem_SpiritGift[3006746][9] = {}
	tKillMonsterDropItem_SpiritGift[3006746][9]["ItemId"] = 823058
	tKillMonsterDropItem_SpiritGift[3006746][9]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][9]["Log"] = "0,0,3006746,1,12000103,2,823058,1"
	
	-- 飞龙魔戒
	tKillMonsterDropItem_SpiritGift[3006746][10] = {}
	tKillMonsterDropItem_SpiritGift[3006746][10]["ItemId"] = 823059
	tKillMonsterDropItem_SpiritGift[3006746][10]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][10]["Log"] = "0,0,3006746,1,12000103,2,823059,1"
	
	-- 玄冥扳指
	tKillMonsterDropItem_SpiritGift[3006746][11] = {}
	tKillMonsterDropItem_SpiritGift[3006746][11]["ItemId"] = 823061
	tKillMonsterDropItem_SpiritGift[3006746][11]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][11]["Log"] = "0,0,3006746,1,12000103,2,823061,1"
	
	-- 虎魄扳指
	tKillMonsterDropItem_SpiritGift[3006746][12] = {}
	tKillMonsterDropItem_SpiritGift[3006746][12]["ItemId"] = 823062
	tKillMonsterDropItem_SpiritGift[3006746][12]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][12]["Log"] = "0,0,3006746,1,12000103,2,823062,1"
	
	-- 惊虹仙镯
	tKillMonsterDropItem_SpiritGift[3006746][13] = {}
	tKillMonsterDropItem_SpiritGift[3006746][13]["ItemId"] = 823060
	tKillMonsterDropItem_SpiritGift[3006746][13]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][13]["Log"] = "0,0,3006746,1,12000103,2,823060,1"
	
	-- 灵狐魔履
	tKillMonsterDropItem_SpiritGift[3006746][14] = {}
	tKillMonsterDropItem_SpiritGift[3006746][14]["ItemId"] = 824018
	tKillMonsterDropItem_SpiritGift[3006746][14]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][14]["Log"] = "0,0,3006746,1,12000103,2,824018,1"
	
	-- 腾龙魔履
	tKillMonsterDropItem_SpiritGift[3006746][15] = {}
	tKillMonsterDropItem_SpiritGift[3006746][15]["ItemId"] = 824019
	tKillMonsterDropItem_SpiritGift[3006746][15]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][15]["Log"] = "0,0,3006746,1,12000103,2,824019,1"
	
	-- 天鹤仙履
	tKillMonsterDropItem_SpiritGift[3006746][16] = {}
	tKillMonsterDropItem_SpiritGift[3006746][16]["ItemId"] = 824020
	tKillMonsterDropItem_SpiritGift[3006746][16]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tKillMonsterDropItem_SpiritGift[3006746][16]["Log"] = "0,0,3006746,1,12000103,2,824020,1"


--------------------------------------逻辑部分-----------------------------------------	
-- 传送进地图
function KillMonsterDropItem_ChgMap(nIndex)
	-- 判断是否在活动时间内
	-- if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		-- return
	-- end
	
	if tKillMonsterDropItem_ChgMap[nIndex] ~= nil then
		local nMapId = tKillMonsterDropItem_ChgMap[nIndex]["MapId"]
		local nCellX = tKillMonsterDropItem_ChgMap[nIndex]["CellX"]
		local nCellY = tKillMonsterDropItem_ChgMap[nIndex]["CellY"]
		local nRange = tKillMonsterDropItem_ChgMap[nIndex]["Range"]
		local sIndex = tKillMonsterDropItem_ChgMap[nIndex]["Index"]
	
		User_UserRandBoundTrans(nMapId,nCellX,nCellY,nRange,nRange)
		User_TalkChannel2005(tKillMonsterDropItem_Text[sIndex])
	end
end

-- 进入九幽地宫一层前判断
function KillMonsterDropItem_JudgeChgMap(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tKillMonsterDropItem_Constant["Level"],tKillMonsterDropItem_Constant["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断玩家背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	KillMonsterDropItem_ChgMap(nNpcId)
	Sys_SaveEmoneyBuy("350	20082	0	0	1	")
end

-- 时间自检触发
function KillMonsterDropItem_CheckTime()
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		return
	end
	
	-- 动态存储表清零
	for i,v in pairs (tKillMonsterDropItem_Constant["RestGlobalTime"]) do
		local nGlobalId = tKillMonsterDropItem_Constant["GlobalId"]
		local nData = Get_SysDynaGlobalData0(nGlobalId)
		
		if Sys_ChkDayTime(v) then
			if nData == 0 then
				for index = 1,#tKillMonsterDropItem_Constant["RestGlobal"] do
					Sys_ResetAllSynaGlobalData(tKillMonsterDropItem_Constant["RestGlobal"][index])
				end
				
				-- +6赤炼石礼包掩码清零
				if i == 4 then
					Sys_SetSynaGlobalData3(nGlobalId,0)
				end

				Sys_SetSynaGlobalData2(nGlobalId,0)
				Sys_SetSynaGlobalData4(nGlobalId,0)
				Sys_SetSynaGlobalData5(nGlobalId,0)
				
				-- 动态存储开关设1
				Sys_SetSynaGlobalData0(nGlobalId,1)
			end
		elseif nData == 1 then
			Sys_SetSynaGlobalData0(nGlobalId,0)
		end
	end
end

-- 普通怪物死亡
function KillMonsterDropItem_OrdinaryMonsterDeath(nMonsterId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		return
	end
	
	local nDouble = 1
	local nTime = tKillMonsterDropItem_Monster[nMonsterId][nDouble]["Time"]
	
	for i = 1,nTime do
		-- 获取随机后给的奖励配置
		local nFlat,tAward = Probabil_RandomAward(tKillMonsterDropItem_Monster[nMonsterId],nDouble)
		local nItem = tAward[1]["tAward"][1]["Item_1"]
		
		-- 判断是否有掉落物品
		if nItem > 0 then
			-- 怪物掉落礼包
			if nItem == nMonsterId then
				KillMonsterDropItem_OrdinaryMonsterDrop(nMonsterId)
			-- 怪物掉落金钱
			elseif tAward[1]["tAward"][1]["IsMoney"] == true then
				Monster_SysDropMoney(nItem)
			-- 怪物掉落归元灵露
			else
				Monster_SysDropItem(nItem)
			end
		end
		
		-- 稀有怪的额外掉落
		for nIndex,v in pairs (tAward[1]["tAbsoluteAward"]) do
			if v["IsMoney"] == true then
				Monster_SysDropMoney(v["Item_1"])
			else
				Monster_SysDropItem(v["Item_1"])
			end
		end
	end

	-- 打怪任务
	-- 判断是否在活动时间内
	-- if Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		local nEvent = tKillMonsterDropItem_Stc["EventType"]
		local nMonsterType = tKillMonsterDropItem_Stc["DataType"][5]
		
		if Task_StcInterval(nEvent,nMonsterType,1,4) then
			Task_SetStatistic(nEvent,nMonsterType,0,1)
			Task_SetStcTimestamp(nEvent,nMonsterType,0)
		end
		
		if Task_ChkStcValue(nEvent,nMonsterType,"<",tKillMonsterDropItem_Constant["MonsterNum"]) then 
			Task_AddStatistic(nEvent,nMonsterType,1,1)
			
			if Task_ChkStcValue(nEvent,nMonsterType,"==",tKillMonsterDropItem_Constant["MonsterNum"]) then
				User_TalkChannel2005(tKillMonsterDropItem_Text[18537]["MonsterNum"])
			end
		end
	-- end
end

-- 普通怪物的掉落
function KillMonsterDropItem_OrdinaryMonsterDrop(nMonsterId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		return
	end
	
	local nFlat,tAward = Probabil_RandomAward(tKillMonsterDropItem_RewardItem,nMonsterId)
	
	if tAward[1]["tAward"][1]["IsGlobal"] ~= nil then
		local nIndex = tAward[1]["tAward"][1]["IsGlobal"]
		local nGlobalId = tKillMonsterDropItem_Global[nIndex]["GlobalId"]
		local nGlobalData = tKillMonsterDropItem_Global[nIndex]["GlobalData"]
		local nData = Get_SysDynaGlobalData(nGlobalId,nGlobalData)
		
		if nData < tKillMonsterDropItem_Global[nIndex]["MaxData"] then
			Sys_SetSynaGlobalData(nGlobalId,nGlobalData,nData + 1)
		else
			tAward[1]["tAward"][1]["IsMoney"] = true
		end
	end
	
	local nItemId = tAward[1]["tAward"][1]["Item_1"]
	local nDropType = 1
	local nDropNum = 1
	
	if tAward[1]["tAward"][1]["IsMoney"] == true then
		Monster_SysDropMoney(tKillMonsterDropItem_Constant["Money"])
		nDropNum = tKillMonsterDropItem_Constant["Money"]
	elseif type(nItemId) == "table" then
		local nRandom = math.random(1,#nItemId)
		Monster_SysDropItem(nItemId[nRandom])
		nDropType = nItemId[nRandom]
	else
		Monster_SysDropItem(nItemId)
		nDropType = nItemId
	end
	
	Sys_SaveActionFestivalLog(string.format(tKillMonsterDropItem_Constant["MonsterDrop"],nMonsterId,nDropType,nDropNum))
	
	-- 全服公告
	if tKillMonsterDropItem_Text[nDropType] ~= nil then
		local sUserName = Get_UserName()

		if tKillMonsterDropItem_Text[nDropType]["Broadcast"] ~= nil then
			Sys_SystemBroadcast(string.format(tKillMonsterDropItem_Text[nDropType]["Broadcast"],sUserName))
			Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nDropType]["Broadcast"],sUserName))
		elseif tKillMonsterDropItem_Text[nDropType]["TalkBroadcast"] ~= nil then
			Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nDropType]["TalkBroadcast"],sUserName))
		end
	end
end

-- BOSS死亡
function KillMonsterDropItem_BossMonsterDeath(nMonsterId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		return
	end
	
	local nDouble = 1
	local sUserName = Get_UserName()
	
	if tKillMonsterDropItem_Text[nMonsterId] ~= nil then
		Sys_SystemBroadcast(string.format(tKillMonsterDropItem_Text[nMonsterId],sUserName))
	end

	-- 额外掉落
	local nFlat,tAward = Probabil_RandomAward(tKillMonsterDropItem_Boss,nMonsterId)
	local isGlobal = tAward[1]["tAward"][1]["IsGlobal"]
	local nAdditGlobalId = tKillMonsterDropItem_Global[isGlobal]["GlobalId"]
	local nAdditGlobalData = tKillMonsterDropItem_Global[isGlobal]["GlobalData"]
	local nAdditData = Get_SysDynaGlobalData(nAdditGlobalId,nAdditGlobalData)
	local nAdditRandom = math.random(1,#tAward[1]["tAward"][1]["Item_1"])
	local nAdditItemId = tAward[1]["tAward"][1]["Item_1"][nAdditRandom]
	
	if nAdditData < tKillMonsterDropItem_Global[isGlobal]["MaxData"] then
		Sys_SetSynaGlobalData(nAdditGlobalId,nAdditGlobalData,nAdditData + 1)
	else
		nAdditItemId = tKillMonsterDropItem_Boss[nMonsterId]["WorstItem"]
	end
	
	Monster_SysDropItem(nAdditItemId)

	-- 全服公告
	if tKillMonsterDropItem_Text[nAdditItemId] ~= nil then
		if tKillMonsterDropItem_Text[nAdditItemId]["Broadcast"] ~= nil then
			Sys_SystemBroadcast(string.format(tKillMonsterDropItem_Text[nAdditItemId]["Broadcast"],sUserName))
			Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nAdditItemId]["Broadcast"],sUserName))
		elseif tKillMonsterDropItem_Text[nAdditItemId]["TalkBroadcast"] ~= nil then
			Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nAdditItemId]["TalkBroadcast"],sUserName))
		end
	end

	Sys_SaveActionFestivalLog(string.format(tKillMonsterDropItem_Constant["MonsterDrop"],nMonsterId,nAdditItemId,1))
	
	-- 固定掉落
	for i,v in pairs (tKillMonsterDropItem_RewardItem[nMonsterId][nDouble]) do
		local isAdditional = v["IsAdditional"]
		local nItemId = v["ItemId"]
		local nNum = v["ItemNum"]
		local nDropItemId = nItemId

		if isAdditional == true then
			local nRange = v["Range"]
			local nPosX = Get_UserPositionX() - v["Sub"]
			local nPosY = Get_UserPositionY() - v["Sub"]
			local nMapId = Get_UserMapId()

			Map_DropMultiItems(nMapId,nDropItemId,nPosX,nPosY,nRange,nRange,nNum,tKillMonsterDropItem_Constant["ExistTime"])
		elseif v["IsGlobal"] ~= nil then
			local nIndex = v["IsGlobal"]
			local nGlobalId = tKillMonsterDropItem_Global[nIndex]["GlobalId"]
			local nGlobalData = tKillMonsterDropItem_Global[nIndex]["GlobalData"]
			local nData = Get_SysDynaGlobalData(nGlobalId,nGlobalData)

			for j = 1,nNum do
				if type(nItemId) == "table" then
					local nRandom = math.random(1,#nItemId)
					nDropItemId = v["ItemId"][nRandom]
				end

				if nData < tKillMonsterDropItem_Global[nIndex]["MaxData"] then
					nData = nData + 1
					Monster_SysDropItem(nDropItemId)
				else
					Monster_SysDropMoney(tKillMonsterDropItem_Constant["Money"])
				end
			end

			Sys_SetSynaGlobalData(nGlobalId,nGlobalData,nData)
		else
			for j = 1,nNum do
				if type(nItemId) == "table" then
					local nRandom = math.random(1,#nItemId)
					nDropItemId = v["ItemId"][nRandom]
				end
				
				Monster_SysDropItem(nDropItemId)
			end
		end

		-- 全服公告
		if tKillMonsterDropItem_Text[nDropItemId] ~= nil then
			if tKillMonsterDropItem_Text[nDropItemId]["Broadcast"] ~= nil then
				Sys_SystemBroadcast(string.format(tKillMonsterDropItem_Text[nDropItemId]["Broadcast"],sUserName))
				Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nDropItemId]["Broadcast"],sUserName))
			elseif tKillMonsterDropItem_Text[nDropItemId]["TalkBroadcast"] ~= nil then
				Sys_TalkBroadcast(string.format(tKillMonsterDropItem_Text[nDropItemId]["TalkBroadcast"],sUserName))
			end
		end
		
		Sys_SaveActionFestivalLog(string.format(tKillMonsterDropItem_Constant["MonsterDrop"],nMonsterId,nDropItemId,nNum))
	end
end

-- 经验礼包使用
function KillMonsterDropItem_UseExpPacks(nItemId)
	local nEvent = tKillMonsterDropItem_Item[nItemId]["EventType"]
	local nType = tKillMonsterDropItem_Item[nItemId]["DataType"]
	
	-- 判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	-- 判断今天是否已经开过10次
	elseif Task_ChkStcValue(nEvent,nType,">=",tKillMonsterDropItem_Item[nItemId]["MaxData"]) then
		Sys_MsgBox(tKillMonsterDropItem_Text[nItemId]["Max"])
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 判断玩家等级
		local nLev = Get_UserLevel()
		local sLog = ""
		local sContent
		
		-- 设掩码值
		Task_AddStatistic(nEvent,nType,1,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		
		if nLev < tKillMonsterDropItem_Constant["MaxLev"] then
			User_AddExpTime(tKillMonsterDropItem_Item[nItemId]["Exp"])
			sLog = tKillMonsterDropItem_Item[nItemId]["ExpLog"]
			sContent = tKillMonsterDropItem_Text[nItemId]["Exp"]
		else
			User_AddCultivation(tKillMonsterDropItem_Item[nItemId]["Cultivation"])
			sLog = tKillMonsterDropItem_Item[nItemId]["CultivationLog"]
			sContent = tKillMonsterDropItem_Text[nItemId]["Cultivation"]
		end
		
		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2007(sContent)
	end
end

-- 物品使用
function KillMonsterDropItem_UseItem(nItemId)
	-- 使用物品前判断
	if tKillMonsterDropItem_Item[nItemId]["ZhenQi"] ~= nil or tKillMonsterDropItem_Item[nItemId]["PractNum"] ~= nil then
		-- 判断是否已经创建过功夫
		if not User_IsAlreadyCreateGongFu(0) then
			User_TalkChannel2007(tKillMonsterDropItem_Text[nItemId]["NoCreateGongFu"])
			return
		end
		
		local nMaxNum = 0
		local nNowNum = 0
		
		-- 判断真气值
		if tKillMonsterDropItem_Item[nItemId]["ZhenQi"] ~= nil then
			local nQenuineqi = Get_UserGongFuQiLev()
			nNowNum = nQenuineqi + tKillMonsterDropItem_Item[nItemId]["ZhenQi"]
			nMaxNum = tKillMonsterDropItem_Constant["MaxQenuineqi"]
		end
		
		-- 判断免费修炼次数
		if tKillMonsterDropItem_Item[nItemId]["PractNum"] ~= nil then
			local nPractNum = Get_UserGongFureePractNum()
			nNowNum = nPractNum + tKillMonsterDropItem_Item[nItemId]["PractNum"]
			nMaxNum = tKillMonsterDropItem_Constant["MaxPractNum"]
		end
		
		if nNowNum > nMaxNum then
			User_TalkChannel2007(tKillMonsterDropItem_Text[nItemId]["Full"])
			return
		end
	end
	
	-- 判断背包空间
	if tKillMonsterDropItem_Item[nItemId]["Space"] ~= nil then
		local nSpace = tKillMonsterDropItem_Item[nItemId]["Space"]
		if not User_CheckLeftSpace(nSpace) then
			User_TalkChannel2007(tKillMonsterDropItem_Text["NoSpace"])
			return
		end
	end
	
	local nChkItemNum = tKillMonsterDropItem_Item[nItemId]["ChkItemNum"] or 1
	
	-- 判断是否有足够的该物品
	if not Item_ChkMulItem(nItemId,nItemId,nChkItemNum) then
		User_TalkChannel2007(tKillMonsterDropItem_Text[nItemId]["NoItem"])
		return
	end
	
	-- 删除物品
	if Item_DelMulItem(nItemId,nItemId,nChkItemNum) then
		local sLog = tKillMonsterDropItem_Item[nItemId]["Log"]
		local sContent = tKillMonsterDropItem_Text[nItemId]["UseItem"]
		
		-- 给修行值
		if tKillMonsterDropItem_Item[nItemId]["Cultivation"] then
			User_AddCultivation(tKillMonsterDropItem_Item[nItemId]["Cultivation"])
		end
		
		-- 给气力值
		if tKillMonsterDropItem_Item[nItemId]["StrengthValue"] then
			User_AddStrengthValue(tKillMonsterDropItem_Item[nItemId]["StrengthValue"])
		end
		
		-- 给真气值
		if tKillMonsterDropItem_Item[nItemId]["ZhenQi"] ~= nil then
			User_AddGongFuQiLeve(tKillMonsterDropItem_Item[nItemId]["ZhenQi"])
		end
		
		-- 给免费修炼次数
		if tKillMonsterDropItem_Item[nItemId]["PractNum"] ~= nil then
			User_AddGongFuFreePractNum(tKillMonsterDropItem_Item[nItemId]["PractNum"])
		end
		
		local nGetItemId = tKillMonsterDropItem_Item[nItemId]["ItemId"]
		
		-- 随机宝石
		if nGetItemId ~= nil and type(nGetItemId) == "table" then
			local nRandom = math.random(1,#nGetItemId)
			nGetItemId = tKillMonsterDropItem_Item[nItemId]["ItemId"][nRandom]
			sLog = string.format(tKillMonsterDropItem_Item[nItemId]["Log"],nGetItemId)

			local nItemName = Get_ItemtypeName(nGetItemId)
			sContent = string.format(tKillMonsterDropItem_Text[nItemId]["UseItem"],nItemName)
		end
		
		-- 获得物品
		if nGetItemId ~= nil then
			Item_AddNewItem(nGetItemId,tKillMonsterDropItem_Item[nItemId]["ItemAttr"]) 
		end

		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		-- 给提示
		User_TalkChannel2007(sContent)
	end
end

-- 礼包兑换积分
function KillMonsterDropItem_PackageExchangeScore(nNpcId,nItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断是否有该礼包
	if not Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nData = tKillMonsterDropItem_Stc["DataType"][4]
	
	Task_SetStatistic(nEvent,nData,nItemId,1)
	LinkNpcGossipFunc_New(nNpcId,"2-4")
end

-- 确认兑换积分
function KillMonsterDropItem_EnSureExchangeScore(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nType = tKillMonsterDropItem_Stc["DataType"][4]
	local nItemId = Get_UserStatisticValue(nEvent,nType)
	
	-- 判断是否有该礼包
	if not Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 删除物品
	if Item_DelItem(nItemId) then
		local nScore = tKillMonsterDropItem_ExchangeScore[nItemId]["Score"]
		local nScoreType = tKillMonsterDropItem_Stc["DataType"][2]
		
		-- 设掩码值
		Task_AddStatistic(nEvent,nScoreType,nScore,1)
		Sys_SaveActionFestivalLog(string.format(tKillMonsterDropItem_Constant["ScoreLog"],nItemId))
		LinkNpcGossipFunc_New(nNpcId,"2-5")
	end
end

-- 积分兑换气力值
function KillMonsterDropItem_ScoreExchangeStrengthValue(nNpcId,nEnSure)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nType = tKillMonsterDropItem_Stc["DataType"][2]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	-- 判断积分值
	if nData < tKillMonsterDropItem_Constant["Score"] then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nTimeType = tKillMonsterDropItem_Stc["DataType"][3]
	
	-- 判断今天兑换次数
	if Task_ChkStcValue(nEvent,nTimeType,">=",tKillMonsterDropItem_Constant["MaxTime"]) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nTimeType,1,4) then
			Task_SetStatistic(nEvent,nTimeType,0,1)
			Task_SetStcTimestamp(nEvent,nTimeType,0)
		else
			LinkNpcGossipFunc_New(nNpcId,"3-2")
			return
		end
	end
	
	if nEnSure == 0 then
		-- 二次确认对白
		LinkNpcGossipFunc_New(nNpcId,"3-3")
	else
		-- 兑换气力值
		Task_AddStatistic(nEvent,nType,-tKillMonsterDropItem_Constant["Score"],1)
		Task_AddStatistic(nEvent,nTimeType,1,1)
		Task_SetStcTimestamp(nEvent,nTimeType,0)
		
		-- 给气力值
		User_AddStrengthValue(tKillMonsterDropItem_Constant["StrengthValue"])
		
		Sys_SaveActionFestivalLog(tKillMonsterDropItem_Constant["StrengthLog"])
		LinkNpcGossipFunc_New(nNpcId,"3-4")
	end
end

-- 打开宝箱
function KillMonsterDropItem_OpenTheChest(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nMonsterType = tKillMonsterDropItem_Stc["DataType"][5]
	local nRewardType = tKillMonsterDropItem_Stc["DataType"][6]
	
	-- 判断今天是否领取过奖励
	if Task_ChkStcValue(nEvent,nRewardType,">=",tKillMonsterDropItem_Constant["RewardNum"]) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nRewardType,1,4) then
			Task_SetStatistic(nEvent,nRewardType,0,1)
			Task_SetStcTimestamp(nEvent,nRewardType,0)
		else
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	end
	
	-- 判断杀怪掩码是否隔天
	if Task_StcInterval(nEvent,nMonsterType,1,4) then
		Task_SetStatistic(nEvent,nMonsterType,0,1)
		Task_SetStcTimestamp(nEvent,nMonsterType,0)

		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断杀怪数量
	if not Task_ChkStcValue(nEvent,nMonsterType,">=",tKillMonsterDropItem_Constant["MonsterNum"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 设置掩码
	Task_SetStatistic(nEvent,nRewardType,tKillMonsterDropItem_Constant["RewardNum"],1)
	Task_SetStcTimestamp(nEvent,nRewardType,0)
	
	-- 给奖励
	local nFlat,tAward = Probabil_RandomAward(tKillMonsterDropItem_TaskReward,1)
	local nItem = tAward[1]["tAward"][1]["Item_1"]
	
	-- 判断是否是给气力值
	if tAward[1]["tAward"][1]["IsStrength"] == true then
		User_AddStrengthValue(nItem)
	-- 判断是否是给赠品天石
	elseif tAward[1]["tAward"][1]["IsEmoney"] == true then
		User_AddEMoneyMono(nItem)
	-- 判断是否是给修行值
	elseif tAward[1]["tAward"][1]["IsCultivation"] == true then
		User_AddCultivation(nItem)
	else
		Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr"])
	end
	
	User_EffectAdd("self","angelwing")
	
	-- 打log
	Sys_SaveActionFestivalLog(tAward[1]["tAward"][1]["Log"])
	
	-- 给提示
	local nIndex = tAward[1]["tAward"][1]["Index"]
	User_TalkChannel2005(tKillMonsterDropItem_Text[nNpcId][nIndex])
end

-- 使用藏宝图
function KillMonsterDropItem_UseTreasureMap(nItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nLev = Get_UserLevel()
		local sContent = ""
		local sLog = ""
		
		if nLev >= tKillMonsterDropItem_Constant["MaxLev"] then
			User_AddCultivation(tKillMonsterDropItem_Item[nItemId]["Cultivation"])
			sContent = tKillMonsterDropItem_Text[nItemId]["RewardCultivation"]
			sLog = tKillMonsterDropItem_Item[nItemId]["CultivationLog"]
		else
			User_AddExpTime(tKillMonsterDropItem_Item[nItemId]["Exp"])
			sContent = tKillMonsterDropItem_Text[nItemId]["RewardExp"]
			sLog = tKillMonsterDropItem_Item[nItemId]["ExpLog"]
		end

		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
		
		local nMapId = tKillMonsterDropItem_Item[nItemId]["MapId"]
		local nPosX = tKillMonsterDropItem_Item[nItemId]["CellX"]
		local nPosY = tKillMonsterDropItem_Item[nItemId]["CellY"]
		local nGotoNpcId = tKillMonsterDropItem_Item[nItemId]["NpcId"]
	
		Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nGotoNpcId)
	end
end

-- 使用神魂礼包
function KillMonsterDropItem_UseSpiritGift(nItemId,nIndex)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 获得神魂
		local nAddItemId = tKillMonsterDropItem_SpiritGift[nItemId][nIndex]["ItemId"]
		Item_AddNewItem(nAddItemId,tKillMonsterDropItem_SpiritGift[nItemId][nIndex]["ItemAttr"])
		
		Sys_SaveActionFestivalLog(tKillMonsterDropItem_SpiritGift[nItemId][nIndex]["Log"])
		
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId][nAddItemId])
	end
end

-- 九幽神魂礼包洗赠卷
function KillMonsterDropItem_WashDonatedVolume(nItemId,nIndex)
	local nExchangeItem = tKillMonsterDropItem_Constant[nItemId][nIndex]["ExchangeItem"]
	
	if not Item_ChkItem(nExchangeItem) then
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId][nExchangeItem])
		return
	end
	
	if not Item_ChkItem(nItemId) then
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["NoItem"])
		return
	end
	
	if Item_DelItem(nItemId) and Item_DelItem(nExchangeItem) then
		local nGetItemId = tKillMonsterDropItem_Constant[nItemId][nIndex]["GetItem"]
		Item_AddItem(nGetItemId)
		Sys_SaveActionFestivalLog(tKillMonsterDropItem_Constant[nItemId][nIndex]["Log"])
		
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId][nGetItemId])
		return
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 地宫守卫者
tNpcFace[3662] = 105
tNpcGossip[18515] = tNpcGossip[18515] or DefaultNpc:new{}
tNpcGossip[18515]["OptionHidden"] = 1

tNpcGossip[18515]["Text1-1"] = {111,112}
tNpcGossip[18515]["Text111"] = tKillMonsterDropItem_Text[18515]["111"]
tNpcGossip[18515]["Text112"] = tKillMonsterDropItem_Text[18515]["112"]
tNpcGossip[18515]["tOption1-1"] = {1,3,4}
tNpcGossip[18515]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"])
end

tNpcGossip[18515]["Text1-2"] = {121}
tNpcGossip[18515]["Text121"] = tKillMonsterDropItem_Text[18515]["121"]
tNpcGossip[18515]["tOption1-2"] = {5}

-- 前往九幽地宫失败、等级不足
tNpcGossip[18515]["Text2-1"] = {211}
tNpcGossip[18515]["Text211"] = tKillMonsterDropItem_Text[18515]["211"]
tNpcGossip[18515]["tOption2-1"] = {6,9}

-- 前往九幽地宫失败、背包满
tNpcGossip[18515]["Text2-2"] = {221}
tNpcGossip[18515]["Text221"] = tKillMonsterDropItem_Text[18515]["221"]
tNpcGossip[18515]["tOption2-2"] = {7}

-- 前往九幽地宫失败、等级不足
tNpcGossip[18515]["Text3-1"] = {311,312,313}
tNpcGossip[18515]["Text311"] = tKillMonsterDropItem_Text[18515]["311"]
tNpcGossip[18515]["Text312"] = tKillMonsterDropItem_Text[18515]["312"]
tNpcGossip[18515]["Text313"] = tKillMonsterDropItem_Text[18515]["313"]
tNpcGossip[18515]["tOption3-1"] = {8}

tNpcGossip[18515]["Option1"] = tKillMonsterDropItem_Text[18515]["Option1"]
tNpcGossip[18515]["OptionFunc1"]="KillMonsterDropItem_JudgeChgMap</N>18515"
tNpcGossip[18515]["Option3"] = tKillMonsterDropItem_Text[18515]["Option3"]
tNpcGossip[18515]["OptionPoint3"]="3"
tNpcGossip[18515]["Option4"] = tKillMonsterDropItem_Text[18515]["Option4"]
tNpcGossip[18515]["Option5"] = tKillMonsterDropItem_Text[18515]["Option5"]
tNpcGossip[18515]["Option6"] = tKillMonsterDropItem_Text[18515]["Option6"]
tNpcGossip[18515]["OptionFunc6"]="KillMonsterDropItem_ChgMap</N>18515"
tNpcGossip[18515]["Option7"] = tKillMonsterDropItem_Text[18515]["Option7"]
tNpcGossip[18515]["Option8"] = tKillMonsterDropItem_Text[18515]["Option8"]
tNpcGossip[18515]["Option9"] = tKillMonsterDropItem_Text[18515]["Option9"]

-- 地宫宝物回收商
tNpcFace[3677] = 51
tNpcGossip[18536] = tNpcGossip[18536] or DefaultNpc:new{}
tNpcGossip[18536]["OptionHidden"] = 1

-- 活动中对白
tNpcGossip[18536]["Text1-1"] = {111,112,113}
tNpcGossip[18536]["Text111"] = tKillMonsterDropItem_Text[18536]["111"]
tNpcGossip[18536]["Text112"] = tKillMonsterDropItem_Text[18536]["112"]
tNpcGossip[18536]["Text113"] = tKillMonsterDropItem_Text[18536]["113"]
tNpcGossip[18536]["tOption1-1"] = {1,2,3}
tNpcGossip[18536]["ChkFunc1-1"] = function ()
	if Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"]) then
		local nEvent = tKillMonsterDropItem_Stc["EventType"]
		local nType = tKillMonsterDropItem_Stc["DataType"][2]
		local nData = Get_UserStatisticValue(nEvent,nType)
		
		tNpcGossip[18536]["Text113"] = string.format(tKillMonsterDropItem_Text[18536]["113"],nData)
		return true
	else
		return false
	end
end

-- 活动后对白
tNpcGossip[18536]["Text1-2"] = {121}
tNpcGossip[18536]["Text121"] = tKillMonsterDropItem_Text[18536]["121"]
tNpcGossip[18536]["tOption1-2"] = {4}

-- 礼包兑换积分
tNpcGossip[18536]["Text2-1"] = {211,212}
tNpcGossip[18536]["Text211"] = tKillMonsterDropItem_Text[18536]["211"]
tNpcGossip[18536]["Text212"] = tKillMonsterDropItem_Text[18536]["212"]
tNpcGossip[18536]["tOption2-1"] = {5,6,7,8,9,10,11,12}

tNpcGossip[18536]["Text2-2"] = {221,222}
tNpcGossip[18536]["Text221"] = tKillMonsterDropItem_Text[18536]["211"]
tNpcGossip[18536]["Text222"] = tKillMonsterDropItem_Text[18536]["212"]
tNpcGossip[18536]["tOption2-2"] = {13,14,15,16,28,17,18}

-- 玩家身上无该礼包
tNpcGossip[18536]["Text2-3"] = {231}
tNpcGossip[18536]["Text231"] = tKillMonsterDropItem_Text[18536]["231"]
tNpcGossip[18536]["tOption2-3"] = {19}

-- 二次确认
tNpcGossip[18536]["Text2-4"] = {241}
tNpcGossip[18536]["Text241"] = tKillMonsterDropItem_Text[18536]["241"]
tNpcGossip[18536]["ChkFunc2-4"] = function ()
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nType = tKillMonsterDropItem_Stc["DataType"][4]
	local nItemId = Get_UserStatisticValue(nEvent,nType)
	local nScore = tKillMonsterDropItem_ExchangeScore[nItemId]["Score"]
	local sItemName = Get_ItemtypeName(nItemId)
	
	tNpcGossip[18536]["Text241"] = string.format(tKillMonsterDropItem_Text[18536]["241"],sItemName,nScore)
	return true
end
tNpcGossip[18536]["tOption2-4"] = {20,21}

-- 成功
tNpcGossip[18536]["Text2-5"] = {251}
tNpcGossip[18536]["Text251"] = tKillMonsterDropItem_Text[18536]["251"]
tNpcGossip[18536]["ChkFunc2-5"] = function ()
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nType = tKillMonsterDropItem_Stc["DataType"][4]
	local nItemId = Get_UserStatisticValue(nEvent,nType)
	local nScore = tKillMonsterDropItem_ExchangeScore[nItemId]["Score"]

	tNpcGossip[18536]["Text251"] = string.format(tKillMonsterDropItem_Text[18536]["251"],nScore)
	return true
end
tNpcGossip[18536]["tOption2-5"] = {22}

-- 玩家选2、失败、积分不足
tNpcGossip[18536]["Text3-1"] = {311}
tNpcGossip[18536]["Text311"] = tKillMonsterDropItem_Text[18536]["311"]
tNpcGossip[18536]["tOption3-1"] = {23}

tNpcGossip[18536]["Text3-2"] = {321}
tNpcGossip[18536]["Text321"] = tKillMonsterDropItem_Text[18536]["321"]
tNpcGossip[18536]["tOption3-2"] = {24}

tNpcGossip[18536]["Text3-3"] = {331}
tNpcGossip[18536]["Text331"] = tKillMonsterDropItem_Text[18536]["331"]
tNpcGossip[18536]["ChkFunc3-3"] = function ()
	local nEvent = tKillMonsterDropItem_Stc["EventType"]
	local nType = tKillMonsterDropItem_Stc["DataType"][2]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	tNpcGossip[18536]["Text331"] = string.format(tKillMonsterDropItem_Text[18536]["331"],nData)
	return true
end
tNpcGossip[18536]["tOption3-3"] = {25,26}

tNpcGossip[18536]["Text3-4"] = {341}
tNpcGossip[18536]["Text341"] = tKillMonsterDropItem_Text[18536]["341"]
tNpcGossip[18536]["tOption3-4"] = {27}

tNpcGossip[18536]["Option1"] = tKillMonsterDropItem_Text[18536]["Option1"]
tNpcGossip[18536]["OptionPoint1"]="2"
tNpcGossip[18536]["Option2"] = tKillMonsterDropItem_Text[18536]["Option2"]
tNpcGossip[18536]["OptionFunc2"]="KillMonsterDropItem_ScoreExchangeStrengthValue</N>18536</N>0"
tNpcGossip[18536]["Option3"] = tKillMonsterDropItem_Text[18536]["Option3"]
tNpcGossip[18536]["Option4"] = tKillMonsterDropItem_Text[18536]["Option4"]
tNpcGossip[18536]["Option5"] = tKillMonsterDropItem_Text[18536]["Option5"]
tNpcGossip[18536]["OptionFunc5"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006544"
tNpcGossip[18536]["Option6"] = tKillMonsterDropItem_Text[18536]["Option6"]
tNpcGossip[18536]["OptionFunc6"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006545"
tNpcGossip[18536]["Option7"] = tKillMonsterDropItem_Text[18536]["Option7"]
tNpcGossip[18536]["OptionFunc7"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006546"
tNpcGossip[18536]["Option8"] = tKillMonsterDropItem_Text[18536]["Option8"]
tNpcGossip[18536]["OptionFunc8"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006547"
tNpcGossip[18536]["Option9"] = tKillMonsterDropItem_Text[18536]["Option9"]
tNpcGossip[18536]["OptionFunc9"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006548"
tNpcGossip[18536]["Option10"] = tKillMonsterDropItem_Text[18536]["Option10"]
tNpcGossip[18536]["OptionFunc10"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006549"
tNpcGossip[18536]["Option11"] = tKillMonsterDropItem_Text[18536]["Option11"]
tNpcGossip[18536]["OptionPoint11"]="2-2"
tNpcGossip[18536]["Option12"] = tKillMonsterDropItem_Text[18536]["Option12"]
tNpcGossip[18536]["OptionPoint12"]="1"
tNpcGossip[18536]["Option13"] = tKillMonsterDropItem_Text[18536]["Option13"]
tNpcGossip[18536]["OptionFunc13"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006551"
tNpcGossip[18536]["Option14"] = tKillMonsterDropItem_Text[18536]["Option14"]
tNpcGossip[18536]["OptionFunc14"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006552"
tNpcGossip[18536]["Option15"] = tKillMonsterDropItem_Text[18536]["Option15"]
tNpcGossip[18536]["OptionFunc15"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006553"
tNpcGossip[18536]["Option16"] = tKillMonsterDropItem_Text[18536]["Option16"]
tNpcGossip[18536]["OptionFunc16"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006554"
tNpcGossip[18536]["Option28"] = tKillMonsterDropItem_Text[18536]["Option28"]
tNpcGossip[18536]["OptionFunc28"]="KillMonsterDropItem_PackageExchangeScore</N>18536</N>3006550"
tNpcGossip[18536]["Option17"] = tKillMonsterDropItem_Text[18536]["Option17"]
tNpcGossip[18536]["OptionPoint17"]="2-1"
tNpcGossip[18536]["Option18"] = tKillMonsterDropItem_Text[18536]["Option18"]
tNpcGossip[18536]["OptionPoint18"]="1"
tNpcGossip[18536]["Option19"] = tKillMonsterDropItem_Text[18536]["Option19"]
tNpcGossip[18536]["Option20"] = tKillMonsterDropItem_Text[18536]["Option20"]
tNpcGossip[18536]["OptionFunc20"]="KillMonsterDropItem_EnSureExchangeScore</N>18536"
tNpcGossip[18536]["Option21"] = tKillMonsterDropItem_Text[18536]["Option21"]
tNpcGossip[18536]["Option22"] = tKillMonsterDropItem_Text[18536]["Option22"]
tNpcGossip[18536]["Option23"] = tKillMonsterDropItem_Text[18536]["Option23"]
tNpcGossip[18536]["Option24"] = tKillMonsterDropItem_Text[18536]["Option24"]
tNpcGossip[18536]["Option25"] = tKillMonsterDropItem_Text[18536]["Option25"]
tNpcGossip[18536]["OptionFunc25"]="KillMonsterDropItem_ScoreExchangeStrengthValue</N>18536</N>1"
tNpcGossip[18536]["Option26"] = tKillMonsterDropItem_Text[18536]["Option26"]
tNpcGossip[18536]["Option27"] = tKillMonsterDropItem_Text[18536]["Option27"]

-- 九幽宝箱
tNpcGossip[18537] = tNpcGossip[18537] or DefaultNpc:new{}
tNpcGossip[18537]["OptionHidden"] = 1

-- 活动中对白
tNpcGossip[18537]["Text1-1"] = {111,112,113}
tNpcGossip[18537]["Text111"] = tKillMonsterDropItem_Text[18537]["111"]
tNpcGossip[18537]["Text112"] = tKillMonsterDropItem_Text[18537]["112"]
tNpcGossip[18537]["Text113"] = tKillMonsterDropItem_Text[18537]["113"]
tNpcGossip[18537]["tOption1-1"] = {1,2}
tNpcGossip[18537]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tKillMonsterDropItem_Constant["ActivityTime"])
end

-- 活动后对白
tNpcGossip[18537]["Text1-2"] = {121}
tNpcGossip[18537]["Text121"] = tKillMonsterDropItem_Text[18537]["121"]
tNpcGossip[18537]["tOption1-2"] = {3}

-- 失败、需击杀10只
tNpcGossip[18537]["Text2-1"] = {211}
tNpcGossip[18537]["Text211"] = tKillMonsterDropItem_Text[18537]["211"]
tNpcGossip[18537]["tOption2-1"] = {4}

-- 失败每天只能打开1次
tNpcGossip[18537]["Text2-2"] = {221}
tNpcGossip[18537]["Text221"] = tKillMonsterDropItem_Text[18537]["221"]
tNpcGossip[18537]["tOption2-2"] = {5}

tNpcGossip[18537]["Text2-3"] = {231}
tNpcGossip[18537]["Text231"] = tKillMonsterDropItem_Text[18537]["231"]
tNpcGossip[18537]["tOption2-3"] = {6}

tNpcGossip[18537]["Option1"] = tKillMonsterDropItem_Text[18537]["Option1"]
tNpcGossip[18537]["OptionFunc1"]="KillMonsterDropItem_OpenTheChest</N>18537"
tNpcGossip[18537]["Option2"] = tKillMonsterDropItem_Text[18537]["Option2"]
tNpcGossip[18537]["Option3"] = tKillMonsterDropItem_Text[18537]["Option3"]
tNpcGossip[18537]["Option4"] = tKillMonsterDropItem_Text[18537]["Option4"]
tNpcGossip[18537]["OptionFunc4"]="Sys_GotoSomeWhere</N>58</N>49</N>3942</N>18515"
tNpcGossip[18537]["Option5"] = tKillMonsterDropItem_Text[18537]["Option5"]
tNpcGossip[18537]["Option6"] = tKillMonsterDropItem_Text[18537]["Option6"]

--------------------------------------物品配置-------------------------------------------
-- 10分钟经验礼包
tItem[3006531] = tItem[3006531] or {}
tItem[3006531]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseExpPacks(nItemId)
end

-- 30分钟经验礼包
tItem[3006532] = tItem[3006532] or {}
tItem[3006532]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseExpPacks(nItemId)
end

-- 50分钟经验礼包
tItem[3006533] = tItem[3006533] or {}
tItem[3006533]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseExpPacks(nItemId)
end

-- 10点修行值礼包
tItem[3006534] = tItem[3006534] or {}
tItem[3006534]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 30点修行值礼包
tItem[3006535] = tItem[3006535] or {}
tItem[3006535]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 50点修行值礼包
tItem[3006536] = tItem[3006536] or {}
tItem[3006536]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 10点气力值礼包
tItem[3006537] = tItem[3006537] or {}
tItem[3006537]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 30点气力值礼包
tItem[3006538] = tItem[3006538] or {}
tItem[3006538]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 50点气力值礼包
tItem[3006539] = tItem[3006539] or {}
tItem[3006539]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 通神丹礼包
tItem[3006540] = tItem[3006540] or {}
tItem[3006540]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 免费强炼丹礼包
tItem[3006541] = tItem[3006541] or {}
tItem[3006541]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 真气礼包
tItem[3006542] = tItem[3006542] or {}
tItem[3006542]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 修炼礼包
tItem[3006543] = tItem[3006543] or {}
tItem[3006543]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 良品宝石礼包
tItem[3006544] = tItem[3006544] or {}
tItem[3006544]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 良品稀有宝石礼包
tItem[3006545] = tItem[3006545] or {}
tItem[3006545]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 优质天怒宝石礼包
tItem[3006546] = tItem[3006546] or {}
tItem[3006546]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 优质地灵宝石礼包
tItem[3006547] = tItem[3006547] or {}
tItem[3006547]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 优质玄元宝石礼包
tItem[3006548] = tItem[3006548] or {}
tItem[3006548]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 龙珠礼包
tItem[3006549] = tItem[3006549] or {}
tItem[3006549]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- +1赤炼石礼包
tItem[3006551] = tItem[3006551] or {}
tItem[3006551]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- +2赤炼石礼包
tItem[3006552] = tItem[3006552] or {}
tItem[3006552]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- +3赤炼石礼包
tItem[3006553] = tItem[3006553] or {}
tItem[3006553]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- +6赤炼石礼包
tItem[3006554] = tItem[3006554] or {}
tItem[3006554]["Function"] = function(nItemId,sItemName)
	KillMonsterDropItem_UseItem(nItemId)
end

-- 九幽藏宝图
tItem[3006699] = tItem[3006699] or {}
tItem[3006699]["Text1-1"] = {111,112,113}
tItem[3006699]["Text111"] = tKillMonsterDropItem_Text[3006699]["111"]
tItem[3006699]["Text112"] = tKillMonsterDropItem_Text[3006699]["112"]
tItem[3006699]["Text113"] = tKillMonsterDropItem_Text[3006699]["113"]
tItem[3006699]["tOption1-1"] = {1}

tItem[3006699]["Option1"] = tKillMonsterDropItem_Text[3006699]["Option1"]
tItem[3006699]["OptionFunc1"]="KillMonsterDropItem_UseTreasureMap</N>3006699"

-- 七阶武器神魂礼包
tItem[3006745] = tItem[3006745] or {}
tItem[3006745]["Text1-1"] = {111}
tItem[3006745]["Text111"] = tKillMonsterDropItem_Text[3006745]["111"]
tItem[3006745]["tOption1-1"] = {1,2,3,4,5,6,7}

tItem[3006745]["Text5-1"] = {111}
tItem[3006745]["tOption5-1"] = {9,10,11,12,13,14,15}

tItem[3006745]["Text6-1"] = {111}
tItem[3006745]["tOption6-1"] = {16,17,18,19}

tItem[3006745]["Text2-1"] = {211}
tItem[3006745]["Text211"] = tKillMonsterDropItem_Text[3006745]["211"]
tItem[3006745]["tOption2-1"] = {20,21}

tItem[3006745]["Text2-2"] = {221}
tItem[3006745]["Text221"] = tKillMonsterDropItem_Text[3006745]["221"]
tItem[3006745]["tOption2-2"] = {22,21}

tItem[3006745]["Text2-3"] = {231}
tItem[3006745]["Text231"] = tKillMonsterDropItem_Text[3006745]["231"]
tItem[3006745]["tOption2-3"] = {23,21}

tItem[3006745]["Text2-4"] = {241}
tItem[3006745]["Text241"] = tKillMonsterDropItem_Text[3006745]["241"]
tItem[3006745]["tOption2-4"] = {24,21}

tItem[3006745]["Text2-5"] = {251}
tItem[3006745]["Text251"] = tKillMonsterDropItem_Text[3006745]["251"]
tItem[3006745]["tOption2-5"] = {25,21}

tItem[3006745]["Text2-6"] = {261}
tItem[3006745]["Text261"] = tKillMonsterDropItem_Text[3006745]["261"]
tItem[3006745]["tOption2-6"] = {26,21}

tItem[3006745]["Text3-1"] = {311}
tItem[3006745]["Text311"] = tKillMonsterDropItem_Text[3006745]["311"]
tItem[3006745]["tOption3-1"] = {27,21}

tItem[3006745]["Text3-2"] = {321}
tItem[3006745]["Text321"] = tKillMonsterDropItem_Text[3006745]["321"]
tItem[3006745]["tOption3-2"] = {28,21}

tItem[3006745]["Text3-3"] = {331}
tItem[3006745]["Text331"] = tKillMonsterDropItem_Text[3006745]["331"]
tItem[3006745]["tOption3-3"] = {29,21}

tItem[3006745]["Text3-4"] = {341}
tItem[3006745]["Text341"] = tKillMonsterDropItem_Text[3006745]["341"]
tItem[3006745]["tOption3-4"] = {30,21}

tItem[3006745]["Text3-5"] = {351}
tItem[3006745]["Text351"] = tKillMonsterDropItem_Text[3006745]["351"]
tItem[3006745]["tOption3-5"] = {31,21}

tItem[3006745]["Text4-1"] = {411}
tItem[3006745]["Text411"] = tKillMonsterDropItem_Text[3006745]["411"]
tItem[3006745]["tOption4-1"] = {32,21}

tItem[3006745]["Text4-2"] = {421}
tItem[3006745]["Text421"] = tKillMonsterDropItem_Text[3006745]["421"]
tItem[3006745]["tOption4-2"] = {33,21}

tItem[3006745]["Text4-3"] = {431}
tItem[3006745]["Text431"] = tKillMonsterDropItem_Text[3006745]["431"]
tItem[3006745]["tOption4-3"] = {34,21}

tItem[3006745]["Option1"] = tKillMonsterDropItem_Text[3006745]["Option1"]
tItem[3006745]["OptionPoint1"]="2-1"
tItem[3006745]["Option2"] = tKillMonsterDropItem_Text[3006745]["Option2"]
tItem[3006745]["OptionPoint2"]="2-2"
tItem[3006745]["Option3"] = tKillMonsterDropItem_Text[3006745]["Option3"]
tItem[3006745]["OptionPoint3"]="2-3"
tItem[3006745]["Option4"] = tKillMonsterDropItem_Text[3006745]["Option4"]
tItem[3006745]["OptionPoint4"]="2-4"
tItem[3006745]["Option5"] = tKillMonsterDropItem_Text[3006745]["Option5"]
tItem[3006745]["OptionPoint5"]="2-5"
tItem[3006745]["Option6"] = tKillMonsterDropItem_Text[3006745]["Option6"]
tItem[3006745]["OptionPoint6"]="2-6"
tItem[3006745]["Option7"] = tKillMonsterDropItem_Text[3006745]["Option7"]
tItem[3006745]["OptionPoint7"]="5-1"
tItem[3006745]["Option8"] = tKillMonsterDropItem_Text[3006745]["Option8"]

tItem[3006745]["Option9"] = tKillMonsterDropItem_Text[3006745]["Option9"]
tItem[3006745]["OptionPoint9"]="3-1"
tItem[3006745]["Option10"] = tKillMonsterDropItem_Text[3006745]["Option10"]
tItem[3006745]["OptionPoint10"]="3-2"
tItem[3006745]["Option11"] = tKillMonsterDropItem_Text[3006745]["Option11"]
tItem[3006745]["OptionPoint11"]="3-3"
tItem[3006745]["Option12"] = tKillMonsterDropItem_Text[3006745]["Option12"]
tItem[3006745]["OptionPoint12"]="3-4"
tItem[3006745]["Option13"] = tKillMonsterDropItem_Text[3006745]["Option13"]
tItem[3006745]["OptionPoint13"]="3-5"
tItem[3006745]["Option14"] = tKillMonsterDropItem_Text[3006745]["Option14"]
tItem[3006745]["OptionPoint14"]="1-1"
tItem[3006745]["Option15"] = tKillMonsterDropItem_Text[3006745]["Option15"]
tItem[3006745]["OptionPoint15"]="6-1"

tItem[3006745]["Option16"] = tKillMonsterDropItem_Text[3006745]["Option16"]
tItem[3006745]["OptionPoint16"]="4-1"
tItem[3006745]["Option17"] = tKillMonsterDropItem_Text[3006745]["Option17"]
tItem[3006745]["OptionPoint17"]="4-2"
tItem[3006745]["Option18"] = tKillMonsterDropItem_Text[3006745]["Option18"]
tItem[3006745]["OptionPoint18"]="4-3"
tItem[3006745]["Option19"] = tKillMonsterDropItem_Text[3006745]["Option19"]
tItem[3006745]["OptionPoint19"]="5-1"

tItem[3006745]["Option20"] = tKillMonsterDropItem_Text[3006745]["Option20"]
tItem[3006745]["OptionFunc20"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>1"
tItem[3006745]["Option21"] = tKillMonsterDropItem_Text[3006745]["Option21"]
tItem[3006745]["Option22"] = tKillMonsterDropItem_Text[3006745]["Option22"]
tItem[3006745]["OptionFunc22"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>2"
tItem[3006745]["Option23"] = tKillMonsterDropItem_Text[3006745]["Option23"]
tItem[3006745]["OptionFunc23"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>3"
tItem[3006745]["Option24"] = tKillMonsterDropItem_Text[3006745]["Option24"]
tItem[3006745]["OptionFunc24"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>4"
tItem[3006745]["Option25"] = tKillMonsterDropItem_Text[3006745]["Option25"]
tItem[3006745]["OptionFunc25"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>5"
tItem[3006745]["Option26"] = tKillMonsterDropItem_Text[3006745]["Option26"]
tItem[3006745]["OptionFunc26"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>6"
tItem[3006745]["Option27"] = tKillMonsterDropItem_Text[3006745]["Option27"]
tItem[3006745]["OptionFunc27"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>7"
tItem[3006745]["Option28"] = tKillMonsterDropItem_Text[3006745]["Option28"]
tItem[3006745]["OptionFunc28"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>8"
tItem[3006745]["Option29"] = tKillMonsterDropItem_Text[3006745]["Option29"]
tItem[3006745]["OptionFunc29"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>9"
tItem[3006745]["Option30"] = tKillMonsterDropItem_Text[3006745]["Option30"]
tItem[3006745]["OptionFunc30"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>10"
tItem[3006745]["Option31"] = tKillMonsterDropItem_Text[3006745]["Option31"]
tItem[3006745]["OptionFunc31"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>11"
tItem[3006745]["Option32"] = tKillMonsterDropItem_Text[3006745]["Option32"]
tItem[3006745]["OptionFunc32"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>12"
tItem[3006745]["Option33"] = tKillMonsterDropItem_Text[3006745]["Option33"]
tItem[3006745]["OptionFunc33"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>13"
tItem[3006745]["Option34"] = tKillMonsterDropItem_Text[3006745]["Option34"]
tItem[3006745]["OptionFunc34"]="KillMonsterDropItem_UseSpiritGift</N>3006745</N>14"

-- 七阶防具配饰神魂礼包（赠）
tItem[3006746] = tItem[3006746] or {}
tItem[3006746]["Text1-1"] = {111}
tItem[3006746]["Text111"] = tKillMonsterDropItem_Text[3006746]["111"]
tItem[3006746]["tOption1-1"] = {1,2,3,4,5}

tItem[3006746]["Text2-1"] = {211}
tItem[3006746]["Text211"] = tKillMonsterDropItem_Text[3006746]["211"]
tItem[3006746]["tOption2-1"] = {6,7,8,9,10}

tItem[3006746]["Text2-2"] = {221}
tItem[3006746]["Text221"] = tKillMonsterDropItem_Text[3006746]["221"]
tItem[3006746]["tOption2-2"] = {11,12,10}

tItem[3006746]["Text2-3"] = {231}
tItem[3006746]["Text231"] = tKillMonsterDropItem_Text[3006746]["231"]
tItem[3006746]["tOption2-3"] = {13,14,10}

tItem[3006746]["Text2-4"] = {241}
tItem[3006746]["Text241"] = tKillMonsterDropItem_Text[3006746]["241"]
tItem[3006746]["tOption2-4"] = {15,16,17,18,19,10}

tItem[3006746]["Text2-5"] = {251}
tItem[3006746]["Text251"] = tKillMonsterDropItem_Text[3006746]["251"]
tItem[3006746]["tOption2-5"] = {20,21,22,10}

tItem[3006746]["Text3-1"] = {311}
tItem[3006746]["Text311"] = tKillMonsterDropItem_Text[3006746]["311"]
tItem[3006746]["tOption3-1"] = {23,39}

tItem[3006746]["Text3-2"] = {321}
tItem[3006746]["Text321"] = tKillMonsterDropItem_Text[3006746]["321"]
tItem[3006746]["tOption3-2"] = {24,39}

tItem[3006746]["Text3-3"] = {331}
tItem[3006746]["Text331"] = tKillMonsterDropItem_Text[3006746]["331"]
tItem[3006746]["tOption3-3"] = {25,39}

tItem[3006746]["Text3-4"] = {341}
tItem[3006746]["Text341"] = tKillMonsterDropItem_Text[3006746]["341"]
tItem[3006746]["tOption3-4"] = {26,39}

tItem[3006746]["Text4-1"] = {411}
tItem[3006746]["Text411"] = tKillMonsterDropItem_Text[3006746]["411"]
tItem[3006746]["tOption4-1"] = {27,39}

tItem[3006746]["Text4-2"] = {421}
tItem[3006746]["Text421"] = tKillMonsterDropItem_Text[3006746]["421"]
tItem[3006746]["tOption4-2"] = {28,39}

tItem[3006746]["Text5-1"] = {511}
tItem[3006746]["Text511"] = tKillMonsterDropItem_Text[3006746]["511"]
tItem[3006746]["tOption5-1"] = {29,39}

tItem[3006746]["Text5-2"] = {521}
tItem[3006746]["Text521"] = tKillMonsterDropItem_Text[3006746]["521"]
tItem[3006746]["tOption5-2"] = {30,39}

tItem[3006746]["Text6-1"] = {611}
tItem[3006746]["Text611"] = tKillMonsterDropItem_Text[3006746]["611"]
tItem[3006746]["tOption6-1"] = {31,39}

tItem[3006746]["Text6-2"] = {621}
tItem[3006746]["Text621"] = tKillMonsterDropItem_Text[3006746]["621"]
tItem[3006746]["tOption6-2"] = {32,39}

tItem[3006746]["Text6-3"] = {631}
tItem[3006746]["Text631"] = tKillMonsterDropItem_Text[3006746]["631"]
tItem[3006746]["tOption6-3"] = {33,39}

tItem[3006746]["Text6-4"] = {641}
tItem[3006746]["Text641"] = tKillMonsterDropItem_Text[3006746]["641"]
tItem[3006746]["tOption6-4"] = {34,39}

tItem[3006746]["Text6-5"] = {651}
tItem[3006746]["Text651"] = tKillMonsterDropItem_Text[3006746]["651"]
tItem[3006746]["tOption6-5"] = {35,39}

tItem[3006746]["Text7-1"] = {711}
tItem[3006746]["Text711"] = tKillMonsterDropItem_Text[3006746]["711"]
tItem[3006746]["tOption7-1"] = {36,39}

tItem[3006746]["Text7-2"] = {721}
tItem[3006746]["Text721"] = tKillMonsterDropItem_Text[3006746]["721"]
tItem[3006746]["tOption7-2"] = {37,39}

tItem[3006746]["Text7-3"] = {731}
tItem[3006746]["Text731"] = tKillMonsterDropItem_Text[3006746]["731"]
tItem[3006746]["tOption7-3"] = {38,39}

tItem[3006746]["Option1"] = tKillMonsterDropItem_Text[3006746]["Option1"]
tItem[3006746]["OptionPoint1"]="2-1"
tItem[3006746]["Option2"] = tKillMonsterDropItem_Text[3006746]["Option2"]
tItem[3006746]["OptionPoint2"]="2-2"
tItem[3006746]["Option3"] = tKillMonsterDropItem_Text[3006746]["Option3"]
tItem[3006746]["OptionPoint3"]="2-3"
tItem[3006746]["Option4"] = tKillMonsterDropItem_Text[3006746]["Option4"]
tItem[3006746]["OptionPoint4"]="2-4"
tItem[3006746]["Option5"] = tKillMonsterDropItem_Text[3006746]["Option5"]
tItem[3006746]["OptionPoint5"]="2-5"

tItem[3006746]["Option6"] = tKillMonsterDropItem_Text[3006746]["Option6"]
tItem[3006746]["OptionPoint6"]="3-1"
tItem[3006746]["Option7"] = tKillMonsterDropItem_Text[3006746]["Option7"]
tItem[3006746]["OptionPoint7"]="3-2"
tItem[3006746]["Option8"] = tKillMonsterDropItem_Text[3006746]["Option8"]
tItem[3006746]["OptionPoint8"]="3-3"
tItem[3006746]["Option9"] = tKillMonsterDropItem_Text[3006746]["Option9"]
tItem[3006746]["OptionPoint9"]="3-4"
tItem[3006746]["Option10"] = tKillMonsterDropItem_Text[3006746]["Option10"]
tItem[3006746]["OptionPoint10"]="1"

tItem[3006746]["Option11"] = tKillMonsterDropItem_Text[3006746]["Option11"]
tItem[3006746]["OptionPoint11"]="4-1"
tItem[3006746]["Option12"] = tKillMonsterDropItem_Text[3006746]["Option12"]
tItem[3006746]["OptionPoint12"]="4-2"

tItem[3006746]["Option13"] = tKillMonsterDropItem_Text[3006746]["Option13"]
tItem[3006746]["OptionPoint13"]="5-1"
tItem[3006746]["Option14"] = tKillMonsterDropItem_Text[3006746]["Option14"]
tItem[3006746]["OptionPoint14"]="5-2"

tItem[3006746]["Option15"] = tKillMonsterDropItem_Text[3006746]["Option15"]
tItem[3006746]["OptionPoint15"]="6-1"
tItem[3006746]["Option16"] = tKillMonsterDropItem_Text[3006746]["Option16"]
tItem[3006746]["OptionPoint16"]="6-2"
tItem[3006746]["Option17"] = tKillMonsterDropItem_Text[3006746]["Option17"]
tItem[3006746]["OptionPoint17"]="6-3"
tItem[3006746]["Option18"] = tKillMonsterDropItem_Text[3006746]["Option18"]
tItem[3006746]["OptionPoint18"]="6-4"
tItem[3006746]["Option19"] = tKillMonsterDropItem_Text[3006746]["Option19"]
tItem[3006746]["OptionPoint19"]="6-5"

tItem[3006746]["Option20"] = tKillMonsterDropItem_Text[3006746]["Option20"]
tItem[3006746]["OptionPoint20"]="7-1"
tItem[3006746]["Option21"] = tKillMonsterDropItem_Text[3006746]["Option21"]
tItem[3006746]["OptionPoint21"]="7-2"
tItem[3006746]["Option22"] = tKillMonsterDropItem_Text[3006746]["Option22"]
tItem[3006746]["OptionPoint22"]="7-3"

tItem[3006746]["Option23"] = tKillMonsterDropItem_Text[3006746]["Option23"]
tItem[3006746]["OptionFunc23"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>1"
tItem[3006746]["Option24"] = tKillMonsterDropItem_Text[3006746]["Option24"]
tItem[3006746]["OptionFunc24"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>2"
tItem[3006746]["Option25"] = tKillMonsterDropItem_Text[3006746]["Option25"]
tItem[3006746]["OptionFunc25"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>3"
tItem[3006746]["Option26"] = tKillMonsterDropItem_Text[3006746]["Option26"]
tItem[3006746]["OptionFunc26"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>4"
tItem[3006746]["Option27"] = tKillMonsterDropItem_Text[3006746]["Option27"]
tItem[3006746]["OptionFunc27"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>5"
tItem[3006746]["Option28"] = tKillMonsterDropItem_Text[3006746]["Option28"]
tItem[3006746]["OptionFunc28"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>6"
tItem[3006746]["Option29"] = tKillMonsterDropItem_Text[3006746]["Option29"]
tItem[3006746]["OptionFunc29"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>7"
tItem[3006746]["Option30"] = tKillMonsterDropItem_Text[3006746]["Option30"]
tItem[3006746]["OptionFunc30"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>8"
tItem[3006746]["Option31"] = tKillMonsterDropItem_Text[3006746]["Option31"]
tItem[3006746]["OptionFunc31"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>9"
tItem[3006746]["Option32"] = tKillMonsterDropItem_Text[3006746]["Option32"]
tItem[3006746]["OptionFunc32"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>10"
tItem[3006746]["Option33"] = tKillMonsterDropItem_Text[3006746]["Option33"]
tItem[3006746]["OptionFunc33"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>11"
tItem[3006746]["Option34"] = tKillMonsterDropItem_Text[3006746]["Option34"]
tItem[3006746]["OptionFunc34"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>12"
tItem[3006746]["Option35"] = tKillMonsterDropItem_Text[3006746]["Option35"]
tItem[3006746]["OptionFunc35"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>13"
tItem[3006746]["Option36"] = tKillMonsterDropItem_Text[3006746]["Option36"]
tItem[3006746]["OptionFunc36"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>14"
tItem[3006746]["Option37"] = tKillMonsterDropItem_Text[3006746]["Option37"]
tItem[3006746]["OptionFunc37"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>15"
tItem[3006746]["Option38"] = tKillMonsterDropItem_Text[3006746]["Option38"]
tItem[3006746]["OptionFunc38"]="KillMonsterDropItem_UseSpiritGift</N>3006746</N>16"
tItem[3006746]["Option39"] = tKillMonsterDropItem_Text[3006746]["Option39"]

-- 九幽神魂礼包洗赠卷
tItem[3006550] = tItem[3006550] or {}
tItem[3006550]["Text1-1"] = {111}
tItem[3006550]["Text111"] = tKillMonsterDropItem_Text[3006550]["111"]
tItem[3006550]["tOption1-1"] = {1,2}

tItem[3006550]["Option1"] = tKillMonsterDropItem_Text[3006550]["Option1"]
tItem[3006550]["OptionFunc1"]="KillMonsterDropItem_WashDonatedVolume</N>3006550</N>1"
tItem[3006550]["Option2"] = tKillMonsterDropItem_Text[3006550]["Option2"]
tItem[3006550]["OptionFunc2"]="KillMonsterDropItem_WashDonatedVolume</N>3006550</N>2"

-- 七阶武器神魂礼包碎片（赠）
tItem[3006765] = tItem[3006765] or {}
tItem[3006765]["Function"] = function(nItemId,sItemName)
	if not Item_ChkMulItem(nItemId,nItemId,15) then
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["NoItem"])
		return
	end
	
	if Item_DelMulItem(nItemId,nItemId,15) then
		-- 添加物品
		Item_AddItem(3006745)
		-- 打log
		Sys_SaveActionFestivalLog("0,0,3006765,15,12000103,2,3006745,1")
		-- 给提示
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["CompoundItem"])
	end
end

-- 七阶武器神魂礼包碎片（赠）
tItem[3006766] = tItem[3006766] or {}
tItem[3006766]["Function"] = function(nItemId,sItemName)
	if not Item_ChkMulItem(nItemId,nItemId,15) then
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["NoItem"])
		return
	end
	
	if Item_DelMulItem(nItemId,nItemId,15) then
		-- 添加物品
		Item_AddItem(3006746)
		-- 打log
		Sys_SaveActionFestivalLog("0,0,3006766,15,12000103,2,3006746,1")
		-- 给提示
		User_TalkChannel2005(tKillMonsterDropItem_Text[nItemId]["CompoundItem"])
	end
end
--------------------------------------怪物掉落-------------------------------------------
--	7697	暗地游魂
tMonster[7697] = tMonster[7697] or {}
tMonster[7697]["tFunction"] = tMonster[7697]["tFunction"] or {}
table.insert(tMonster[7697]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7698	虚空夜叉
tMonster[7698] = tMonster[7698] or {}
tMonster[7698]["tFunction"] = tMonster[7698]["tFunction"] or {}
table.insert(tMonster[7698]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7699	地宫邪魅
tMonster[7699] = tMonster[7699] or {}
tMonster[7699]["tFunction"] = tMonster[7699]["tFunction"] or {}
table.insert(tMonster[7699]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7700	暗地战魂
tMonster[7700] = tMonster[7700] or {}
tMonster[7700]["tFunction"] = tMonster[7700]["tFunction"] or {}
table.insert(tMonster[7700]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7701	虚空小将
tMonster[7701] = tMonster[7701] or {}
tMonster[7701]["tFunction"] = tMonster[7701]["tFunction"] or {}
table.insert(tMonster[7701]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7702	地宫邪魔
tMonster[7702] = tMonster[7702] or {}
tMonster[7702]["tFunction"] = tMonster[7702]["tFunction"] or {}
table.insert(tMonster[7702]["tFunction"],KillMonsterDropItem_OrdinaryMonsterDeath)

--	7703	幽暗地妖
tMonster[7703] = tMonster[7703] or {}
tMonster[7703]["tFunction"] = tMonster[7703]["tFunction"] or {}
table.insert(tMonster[7703]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--	7704	幽影地魂
tMonster[7704] = tMonster[7704] or {}
tMonster[7704]["tFunction"] = tMonster[7704]["tFunction"] or {}
table.insert(tMonster[7704]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--	7705	幽游地魔
tMonster[7705] = tMonster[7705] or {}
tMonster[7705]["tFunction"] = tMonster[7705]["tFunction"] or {}
table.insert(tMonster[7705]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--	7706	幽寂豺狼
tMonster[7706] = tMonster[7706] or {}
tMonster[7706]["tFunction"] = tMonster[7706]["tFunction"] or {}
table.insert(tMonster[7706]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--	7707	幽冥麒麟
tMonster[7707] = tMonster[7707] or {}
tMonster[7707]["tFunction"] = tMonster[7707]["tFunction"] or {}
table.insert(tMonster[7707]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--	7708	九幽金睛兽
tMonster[7708] = tMonster[7708] or {}
tMonster[7708]["tFunction"] = tMonster[7708]["tFunction"] or {}
table.insert(tMonster[7708]["tFunction"],KillMonsterDropItem_BossMonsterDeath)

--------------------------------------陷阱配置-------------------------------------------
tTrap[1365] = tTrap[1365] or {}
tTrap[1365]["Function"] = function(nTrapId,nTrapType)
	KillMonsterDropItem_ChgMap(nTrapId)
end

tSystem_Prompet_Func = tSystem_Prompet_Func or {}
table.insert(tSystem_Prompet_Func,KillMonsterDropItem_CheckTime)