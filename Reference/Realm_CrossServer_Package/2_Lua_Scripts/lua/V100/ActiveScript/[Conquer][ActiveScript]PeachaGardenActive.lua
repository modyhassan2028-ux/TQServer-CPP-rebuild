------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]天机果活动
--Purpose:	天机果活动
--Creator: 	郑鋆
--Created:	2015/06/02
------------------------------------------------------------------------------------

-- 命名前缀
-- PeachaGardenActive_

-- 掩码说明
-- 134	30	记录玩家是否获得过背包信
-- 135	12	设置玩家打怪或者除草的数量
-- 135	13	设置玩家是否领取过力王酒
-- 135	14	设置玩家花费的力王酒量
-- 135	15	设置摘桃的次数
-- 136	02	设置是否显示二次确认提示，=1 不显示
-- 136	96	记录玩家要兑换的物品ID

-- lodid，2，xxxxx

-- logid,1[1],
-- logid,1[2],
-- logid,1[3],
-- logid,1[4],
-- logid,1[5],


-- 常量表
local tPeachaGardenActive_Constant = {}
	-- 活动时间
	tPeachaGardenActive_Constant["BeforeActivityTime"] = "2015-03-17 00:00 2015-07-13 23:59"
	tPeachaGardenActive_Constant["ActivityTime"] = "2015-07-14 00:00 2015-08-08 23:59"
	tPeachaGardenActive_Constant["ExchangeTime"] = "2015-08-01 00:00 2015-08-12 23:59"
	
	-- 玩家等级要求
	tPeachaGardenActive_Constant["Metempsychosis"] = 0
	tPeachaGardenActive_Constant["Level"] = 80
	
	-- 最大等级
	tPeachaGardenActive_Constant["MaxLev"] = 140
	
	tPeachaGardenActive_Constant["RecurrentNum"] = 5
	
	tPeachaGardenActive_Constant["RewarData"] = 1
	tPeachaGardenActive_Constant["DemandData"] = 10
	
	-- 力王酒ID
	tPeachaGardenActive_Constant["TaskItemId"] = 3006283
	-- 刷新力王神酒数量的花费
	tPeachaGardenActive_Constant["RefreshEmoney"] = 3
	
	tPeachaGardenActive_Constant["LogId"] = 12000088
	tPeachaGardenActive_Constant["GetItemLog"] = "0,0,0,0,12000088,1,%d,%d"
	
	-- 翻倍摘取的物品
	tPeachaGardenActive_Constant["Double"] = {}
	tPeachaGardenActive_Constant["Double"][4] = {}
	tPeachaGardenActive_Constant["Double"][4]["ItemId"] = 3006742
	tPeachaGardenActive_Constant["Double"][4]["Index"] = "5-2"
	tPeachaGardenActive_Constant["Double"][5] = {}
	tPeachaGardenActive_Constant["Double"][5]["ItemId"] = 3006743
	tPeachaGardenActive_Constant["Double"][5]["Index"] = "5-4"
	
	tPeachaGardenActive_Constant["EmoneyLog"] = "250	4060	0	0	1	"
	
	tPeachaGardenActive_Constant["MaxAttr"] = 900

-- 传送地图配置
local tPeachaGardenActive_ChgMapInfo = {}
	tPeachaGardenActive_ChgMapInfo[18619] = {}
	tPeachaGardenActive_ChgMapInfo[18619]["ActivityTime"] = "2015-07-14 00:00 2015-08-08 23:59"
	tPeachaGardenActive_ChgMapInfo[18619]["Level"] = 80
	tPeachaGardenActive_ChgMapInfo[18619]["Metempsychosis"] = 0
	tPeachaGardenActive_ChgMapInfo[18619]["MapId"] = 3937
	tPeachaGardenActive_ChgMapInfo[18619]["CellX"] = 36
	tPeachaGardenActive_ChgMapInfo[18619]["CellY"] = 35
	tPeachaGardenActive_ChgMapInfo[18619]["Range"] = 3
	
	tPeachaGardenActive_ChgMapInfo[18484] = {}
	tPeachaGardenActive_ChgMapInfo[18484]["Level"] = 1
	tPeachaGardenActive_ChgMapInfo[18484]["Metempsychosis"] = 0
	tPeachaGardenActive_ChgMapInfo[18484]["MapId"] = 1002
	tPeachaGardenActive_ChgMapInfo[18484]["CellX"] = 322
	tPeachaGardenActive_ChgMapInfo[18484]["CellY"] = 265
	tPeachaGardenActive_ChgMapInfo[18484]["Range"] = 3

-- 物品配置
local tPeachaGardenActive_Item = {}
	-- 调皮的蟠桃
	tPeachaGardenActive_Item[3006281] = {}
	tPeachaGardenActive_Item[3006281]["Cultivation"] = 15
	tPeachaGardenActive_Item[3006281]["CultivationLog"] = "0,0,3006281,1,12000088,1,6,15"
	tPeachaGardenActive_Item[3006281]["Exp"] = 30
	tPeachaGardenActive_Item[3006281]["ExpLog"] = "0,0,3006281,1,12000088,1,4,30"

local tPeachaGardenActive_PathFind = {}
	tPeachaGardenActive_PathFind[3006281] = {}
	tPeachaGardenActive_PathFind[3006281]["MapId"] = 1002
	tPeachaGardenActive_PathFind[3006281]["CellX"] = 321
	tPeachaGardenActive_PathFind[3006281]["CellY"] = 267
	tPeachaGardenActive_PathFind[3006281]["NpcId"] = 18619
	
	tPeachaGardenActive_PathFind[1] = {}
	tPeachaGardenActive_PathFind[1]["MapId"] = 3937
	tPeachaGardenActive_PathFind[1]["CellX"] = 62
	tPeachaGardenActive_PathFind[1]["CellY"] = 53
	tPeachaGardenActive_PathFind[1]["NpcId"] = 0
	
	tPeachaGardenActive_PathFind[2] = {}
	tPeachaGardenActive_PathFind[2]["MapId"] = 3937
	tPeachaGardenActive_PathFind[2]["CellX"] = 38
	tPeachaGardenActive_PathFind[2]["CellY"] = 31
	tPeachaGardenActive_PathFind[2]["NpcId"] = 18484
	
-- stc掩码
local tPeachaGardenActive_Stc = {}
	tPeachaGardenActive_Stc["EventType"] = 135
	tPeachaGardenActive_Stc["DataType"] = {}
	tPeachaGardenActive_Stc["DataType"][1] = 12
	tPeachaGardenActive_Stc["DataType"][2] = 13
	tPeachaGardenActive_Stc["DataType"][3] = 14
	tPeachaGardenActive_Stc["DataType"][4] = 15
	
	tPeachaGardenActive_Stc[1] = {}
	tPeachaGardenActive_Stc[1]["EventType"] = 136
	tPeachaGardenActive_Stc[1]["DataType"] = 2
	
	tPeachaGardenActive_Stc[2] = {}
	tPeachaGardenActive_Stc[2]["EventType"] = 136
	tPeachaGardenActive_Stc[2]["DataType"] = 3
	
	tPeachaGardenActive_Stc[3] = {}
	tPeachaGardenActive_Stc[3]["EventType"] = 136
	tPeachaGardenActive_Stc[3]["DataType"] = 96

-- 花费力王酒的数量
local tPeachaGardenActive_Cost = {}
	-- 第一次摘桃
	tPeachaGardenActive_Cost[1] = {}
	tPeachaGardenActive_Cost[1]["ItemNum"] = 1
	tPeachaGardenActive_Cost[1]["Effect"] = "eidolon"
	
	-- 第二次摘桃
	tPeachaGardenActive_Cost[2] = {}
	tPeachaGardenActive_Cost[2]["ItemNum"] = 2
	tPeachaGardenActive_Cost[2]["Effect"] = "zf2-e280"
	
	-- 第三次摘桃
	tPeachaGardenActive_Cost[3] = {}
	tPeachaGardenActive_Cost[3]["ItemNum"] = 3
	tPeachaGardenActive_Cost[3]["Effect"] = "fighter-s"
	
	-- 第四次摘桃
	tPeachaGardenActive_Cost[4] = {}
	tPeachaGardenActive_Cost[4]["ItemNum"] = 5
	tPeachaGardenActive_Cost[4]["Effect"] = "zf2-e129"
	
	-- 第五次摘桃
	tPeachaGardenActive_Cost[5] = {}
	tPeachaGardenActive_Cost[5]["ItemNum"] = 6
	tPeachaGardenActive_Cost[5]["Effect"] = "fighter"
	tPeachaGardenActive_Cost[5]["Additional"] = true
	
-- 摘蟠桃王累计消费对应的概率
local tPeachaGardenActive_PickPeachKing = {}
	-- 累计消费2223个力王酒	5.00%
	tPeachaGardenActive_PickPeachKing[1] = {}
	tPeachaGardenActive_PickPeachKing[1]["CostItemNum"] = 2223
	
	tPeachaGardenActive_PickPeachKing[1][1] = {}
	tPeachaGardenActive_PickPeachKing[1][1]["RandomItemChanceType"] = 3
	tPeachaGardenActive_PickPeachKing[1][1]["ItemSelfChanceSum"] = 100
	tPeachaGardenActive_PickPeachKing[1][1]["ItemChance"] = 5
	tPeachaGardenActive_PickPeachKing[1][1]["Item_1"] = 3006282
	tPeachaGardenActive_PickPeachKing[1][1]["Log"] = "0,0,0,0,12000088,2,3006282,1"

	-- 累计消费1112个力王酒	4.00%
	tPeachaGardenActive_PickPeachKing[2] = {}
	tPeachaGardenActive_PickPeachKing[2]["CostItemNum"] = 1112
	
	tPeachaGardenActive_PickPeachKing[2][1] = {}
	tPeachaGardenActive_PickPeachKing[2][1]["RandomItemChanceType"] = 3
	tPeachaGardenActive_PickPeachKing[2][1]["ItemSelfChanceSum"] = 100
	tPeachaGardenActive_PickPeachKing[2][1]["ItemChance"] = 4
	tPeachaGardenActive_PickPeachKing[2][1]["Item_1"] = 3006282
	tPeachaGardenActive_PickPeachKing[2][1]["Log"] = "0,0,0,0,12000088,2,3006282,1"

	-- 累计消费556个力王酒	3.00%
	tPeachaGardenActive_PickPeachKing[3] = {}
	tPeachaGardenActive_PickPeachKing[3]["CostItemNum"] = 556
	
	tPeachaGardenActive_PickPeachKing[3][1] = {}
	tPeachaGardenActive_PickPeachKing[3][1]["RandomItemChanceType"] = 3
	tPeachaGardenActive_PickPeachKing[3][1]["ItemSelfChanceSum"] = 100
	tPeachaGardenActive_PickPeachKing[3][1]["ItemChance"] = 3
	tPeachaGardenActive_PickPeachKing[3][1]["Item_1"] = 3006282
	tPeachaGardenActive_PickPeachKing[3][1]["Log"] = "0,0,0,0,12000088,2,3006282,1"

	-- 累计消费189个力王酒	2.00%
	tPeachaGardenActive_PickPeachKing[4] = {}
	tPeachaGardenActive_PickPeachKing[4]["CostItemNum"] = 189
	
	tPeachaGardenActive_PickPeachKing[4][1] = {}
	tPeachaGardenActive_PickPeachKing[4][1]["RandomItemChanceType"] = 3
	tPeachaGardenActive_PickPeachKing[4][1]["ItemSelfChanceSum"] = 100
	tPeachaGardenActive_PickPeachKing[4][1]["ItemChance"] = 2
	tPeachaGardenActive_PickPeachKing[4][1]["Item_1"] = 3006282
	tPeachaGardenActive_PickPeachKing[4][1]["Log"] = "0,0,0,0,12000088,2,3006282,1"

	-- 累计消费38个力王酒	1.00%
	tPeachaGardenActive_PickPeachKing[5] = {}
	tPeachaGardenActive_PickPeachKing[5]["CostItemNum"] = 38
	
	tPeachaGardenActive_PickPeachKing[5][1] = {}
	tPeachaGardenActive_PickPeachKing[5][1]["RandomItemChanceType"] = 3
	tPeachaGardenActive_PickPeachKing[5][1]["ItemSelfChanceSum"] = 100
	tPeachaGardenActive_PickPeachKing[5][1]["ItemChance"] = 1
	tPeachaGardenActive_PickPeachKing[5][1]["Item_1"] = 3006282
	tPeachaGardenActive_PickPeachKing[5][1]["Log"] = "0,0,0,0,12000088,2,3006282,1"

-- 摘桃的几率配置	
local tPeachaGardenActive_PickPeachesChance = {}
	-- 第一次摘桃
	tPeachaGardenActive_PickPeachesChance[1] = {}
	tPeachaGardenActive_PickPeachesChance[1]["ItemChanceSum"] = 10000
	tPeachaGardenActive_PickPeachesChance[1]["EmoneyLog"] = "250	4054	0	0	1	"
	
	-- 洗髓神露碎片（10合1）*1	30.00%
	tPeachaGardenActive_PickPeachesChance[1][1] = {}
	tPeachaGardenActive_PickPeachesChance[1][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[1][1]["ItemChance"] = 3000
	tPeachaGardenActive_PickPeachesChance[1][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[1][1]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[1][1]["Item_1"][1]["Id"] = 3006284
	tPeachaGardenActive_PickPeachesChance[1][1]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[1][1]["Log"] = "%s,12000088,1[1],3006284,1"
	tPeachaGardenActive_PickPeachesChance[1][1]["Index"] = "RewardOneItem"
	
	-- 秘令转化卷	40.00%
	tPeachaGardenActive_PickPeachesChance[1][2] = {}
	tPeachaGardenActive_PickPeachesChance[1][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[1][2]["ItemChance"] = 4000
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["Id"] = {}
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["Id"][1] = 3006285
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["Id"][2] = 3006798
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["Id"][3] = 3006799
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["Id"][4] = 3006800
	tPeachaGardenActive_PickPeachesChance[1][2]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[1][2]["Log"] = "%s,12000088,1[1],%d,1"
	tPeachaGardenActive_PickPeachesChance[1][2]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*1	30.00%
	tPeachaGardenActive_PickPeachesChance[1][3] = {}
	tPeachaGardenActive_PickPeachesChance[1][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[1][3]["ItemChance"] = 3000
	tPeachaGardenActive_PickPeachesChance[1][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[1][3]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[1][3]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[1][3]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[1][3]["Log"] = "%s,12000088,1[1],3006286,1"
	tPeachaGardenActive_PickPeachesChance[1][3]["Index"] = "RewardOneItem"
	
	-- 第二次摘桃
	tPeachaGardenActive_PickPeachesChance[2] = {}
	tPeachaGardenActive_PickPeachesChance[2]["ItemChanceSum"] = 10000
	tPeachaGardenActive_PickPeachesChance[2]["EmoneyLog"] = "250	4055	0	0	2	"
	
	-- 秘令赌博卷*1	28.00%
	tPeachaGardenActive_PickPeachesChance[2][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][1]["ItemChance"] = 2800
	tPeachaGardenActive_PickPeachesChance[2][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][1]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][1]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[2][1]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[2][1]["Log"] = "%s,12000088,1[2],3006286,1"
	tPeachaGardenActive_PickPeachesChance[2][1]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*2	8.00%
	tPeachaGardenActive_PickPeachesChance[2][2] = {}
	tPeachaGardenActive_PickPeachesChance[2][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][2]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[2][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][2]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][2]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[2][2]["Item_1"][1]["ItemAttr"] = "0 2"
	tPeachaGardenActive_PickPeachesChance[2][2]["Log"] = "%s,12000088,1[2],3006286,2"
	tPeachaGardenActive_PickPeachesChance[2][2]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*3	4.00%
	tPeachaGardenActive_PickPeachesChance[2][3] = {}
	tPeachaGardenActive_PickPeachesChance[2][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][3]["ItemChance"] = 400
	tPeachaGardenActive_PickPeachesChance[2][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][3]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][3]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[2][3]["Item_1"][1]["ItemAttr"] = "0 3"
	tPeachaGardenActive_PickPeachesChance[2][3]["Log"] = "%s,12000088,1[2],3006286,3"
	tPeachaGardenActive_PickPeachesChance[2][3]["Index"] = "RewardOneItem"
	
	-- 力量秘令转化卷+5点力量洗点丹	7.00%
	tPeachaGardenActive_PickPeachesChance[2][4] = {}
	tPeachaGardenActive_PickPeachesChance[2][4]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][4]["ItemChance"] = 700
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][1]["Id"] = 3006285
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][2]["Id"] = 3006288
	tPeachaGardenActive_PickPeachesChance[2][4]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[2][4]["Log"] = "%s,12000088,1[2],3006285[3006288],1[5]"
	tPeachaGardenActive_PickPeachesChance[2][4]["Index"] = "RewardItem"
	
	-- 敏捷秘令转化卷+5点敏捷洗点丹	7.00%
	tPeachaGardenActive_PickPeachesChance[2][5] = {}
	tPeachaGardenActive_PickPeachesChance[2][5]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][5]["ItemChance"] = 700
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][1]["Id"] = 3006798
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][2]["Id"] = 3006289
	tPeachaGardenActive_PickPeachesChance[2][5]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[2][5]["Log"] = "%s,12000088,1[2],3006798[3006289],1[5]"
	tPeachaGardenActive_PickPeachesChance[2][5]["Index"] = "RewardItem"
	
	-- 体质秘令转化卷+5点体质洗点丹	7.00%
	tPeachaGardenActive_PickPeachesChance[2][6] = {}
	tPeachaGardenActive_PickPeachesChance[2][6]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][6]["ItemChance"] = 700
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][1]["Id"] = 3006799
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][2]["Id"] = 3006322
	tPeachaGardenActive_PickPeachesChance[2][6]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[2][6]["Log"] = "%s,12000088,1[2],3006799[3006322],1[5]"
	tPeachaGardenActive_PickPeachesChance[2][6]["Index"] = "RewardItem"
	
	-- 精神秘令转化卷+5点精神洗点丹	7.00%
	tPeachaGardenActive_PickPeachesChance[2][7] = {}
	tPeachaGardenActive_PickPeachesChance[2][7]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][7]["ItemChance"] = 700
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][1]["Id"] = 3006800
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][2]["Id"] = 3006323
	tPeachaGardenActive_PickPeachesChance[2][7]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[2][7]["Log"] = "%s,12000088,1[2],3006800[3006323],1[5]"
	tPeachaGardenActive_PickPeachesChance[2][7]["Index"] = "RewardItem"
	
	-- 力王酒*2	32.00%
	tPeachaGardenActive_PickPeachesChance[2][8] = {}
	tPeachaGardenActive_PickPeachesChance[2][8]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[2][8]["ItemChance"] = 3200
	tPeachaGardenActive_PickPeachesChance[2][8]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[2][8]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[2][8]["Item_1"][1]["Id"] = 3006283
	tPeachaGardenActive_PickPeachesChance[2][8]["Item_1"][1]["ItemAttr"] = "0 2"
	tPeachaGardenActive_PickPeachesChance[2][8]["Log"] = "%s,12000088,1[2],3006283,2"
	tPeachaGardenActive_PickPeachesChance[2][8]["Index"] = "RewardOneItem"
	
	-- 第三次摘桃
	tPeachaGardenActive_PickPeachesChance[3] = {}
	tPeachaGardenActive_PickPeachesChance[3]["ItemChanceSum"] = 10000
	tPeachaGardenActive_PickPeachesChance[3]["EmoneyLog"] = "250	4056	0	0	3	"
	
	-- 秘令*2	5.00%
	tPeachaGardenActive_PickPeachesChance[3][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][1]["ItemChance"] = 500
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["Id"] = {}
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["Id"][1] = 3004895
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["Id"][2] = 3004896
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["Id"][3] = 3004897
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["Id"][4] = 3004898
	tPeachaGardenActive_PickPeachesChance[3][1]["Item_1"][1]["ItemAttr"] = "0 2"
	tPeachaGardenActive_PickPeachesChance[3][1]["Log"] = "%s,12000088,1[3],%d,2"
	tPeachaGardenActive_PickPeachesChance[3][1]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*2	23.00%
	tPeachaGardenActive_PickPeachesChance[3][2] = {}
	tPeachaGardenActive_PickPeachesChance[3][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][2]["ItemChance"] = 2300
	tPeachaGardenActive_PickPeachesChance[3][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][2]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][2]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][2]["Item_1"][1]["ItemAttr"] = "0 2"
	tPeachaGardenActive_PickPeachesChance[3][2]["Log"] = "%s,12000088,1[3],3006286,2"
	tPeachaGardenActive_PickPeachesChance[3][2]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*4	10.00%
	tPeachaGardenActive_PickPeachesChance[3][3] = {}
	tPeachaGardenActive_PickPeachesChance[3][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][3]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[3][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][3]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][3]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][3]["Item_1"][1]["ItemAttr"] = "0 4"
	tPeachaGardenActive_PickPeachesChance[3][3]["Log"] = "%s,12000088,1[3],3006286,4"
	tPeachaGardenActive_PickPeachesChance[3][3]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*1+5点力量洗点丹	8.00%
	tPeachaGardenActive_PickPeachesChance[3][4] = {}
	tPeachaGardenActive_PickPeachesChance[3][4]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][4]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][2]["Id"] = 3006288
	tPeachaGardenActive_PickPeachesChance[3][4]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[3][4]["Log"] = "%s,12000088,1[3],3006286[3006288],1[5]"
	tPeachaGardenActive_PickPeachesChance[3][4]["Index"] = "RewardItem"
	
	-- 秘令赌博卷*1+5点精神洗点丹	8.00%
	tPeachaGardenActive_PickPeachesChance[3][5] = {}
	tPeachaGardenActive_PickPeachesChance[3][5]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][5]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][2]["Id"] = 3006323
	tPeachaGardenActive_PickPeachesChance[3][5]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[3][5]["Log"] = "%s,12000088,1[3],3006286[3006323],1[5]"
	tPeachaGardenActive_PickPeachesChance[3][5]["Index"] = "RewardItem"
	
	-- 秘令赌博卷*1+5点生命洗点丹	8.00%
	tPeachaGardenActive_PickPeachesChance[3][6] = {}
	tPeachaGardenActive_PickPeachesChance[3][6]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][6]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][2]["Id"] = 3006322
	tPeachaGardenActive_PickPeachesChance[3][6]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[3][6]["Log"] = "%s,12000088,1[3],3006286[3006322],1[5]"
	tPeachaGardenActive_PickPeachesChance[3][6]["Index"] = "RewardItem"
	
	-- 秘令赌博卷*1+5点敏捷洗点丹	8.00%
	tPeachaGardenActive_PickPeachesChance[3][7] = {}
	tPeachaGardenActive_PickPeachesChance[3][7]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][7]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][2] = {}
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][2]["Id"] = 3006289
	tPeachaGardenActive_PickPeachesChance[3][7]["Item_1"][2]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[3][7]["Log"] = "%s,12000088,1[3],3006286[3006289],1[5]"
	tPeachaGardenActive_PickPeachesChance[3][7]["Index"] = "RewardItem"
	
	-- 力王酒*3	20.00%
	tPeachaGardenActive_PickPeachesChance[3][8] = {}
	tPeachaGardenActive_PickPeachesChance[3][8]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][8]["ItemChance"] = 2000
	tPeachaGardenActive_PickPeachesChance[3][8]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][8]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][8]["Item_1"][1]["Id"] = 3006283
	tPeachaGardenActive_PickPeachesChance[3][8]["Item_1"][1]["ItemAttr"] = "0 3"
	tPeachaGardenActive_PickPeachesChance[3][8]["Log"] = "%s,12000088,1[3],3006283,3"
	tPeachaGardenActive_PickPeachesChance[3][8]["Index"] = "RewardOneItem"
	
	-- 力王酒*4	10.00%
	tPeachaGardenActive_PickPeachesChance[3][9] = {}
	tPeachaGardenActive_PickPeachesChance[3][9]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3][9]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[3][9]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3][9]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[3][9]["Item_1"][1]["Id"] = 3006283
	tPeachaGardenActive_PickPeachesChance[3][9]["Item_1"][1]["ItemAttr"] = "0 4"
	tPeachaGardenActive_PickPeachesChance[3][9]["Log"] = "%s,12000088,1[3],3006283,4"
	tPeachaGardenActive_PickPeachesChance[3][9]["Index"] = "RewardOneItem"
	
	-- 第四次摘桃
	tPeachaGardenActive_PickPeachesChance[4] = {}
	tPeachaGardenActive_PickPeachesChance[4]["ItemChanceSum"] = 10000
	tPeachaGardenActive_PickPeachesChance[4]["EmoneyLog"] = "250	4057	0	0	5	"
	
	-- 秘令赌博卷*3	20.00%
	tPeachaGardenActive_PickPeachesChance[4][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][1]["ItemChance"] = 2000
	tPeachaGardenActive_PickPeachesChance[4][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][1]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][1]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][1]["Item_1"][1]["ItemAttr"] = "0 3"
	tPeachaGardenActive_PickPeachesChance[4][1]["Log"] = "%s,12000088,1[4],3006286,3"
	tPeachaGardenActive_PickPeachesChance[4][1]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*4	10.00%
	tPeachaGardenActive_PickPeachesChance[4][2] = {}
	tPeachaGardenActive_PickPeachesChance[4][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][2]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[4][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][2]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][2]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][2]["Item_1"][1]["ItemAttr"] = "0 4"
	tPeachaGardenActive_PickPeachesChance[4][2]["Log"] = "%s,12000088,1[4],3006286,4"
	tPeachaGardenActive_PickPeachesChance[4][2]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*5	8.00%
	tPeachaGardenActive_PickPeachesChance[4][3] = {}
	tPeachaGardenActive_PickPeachesChance[4][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][3]["ItemChance"] = 800
	tPeachaGardenActive_PickPeachesChance[4][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][3]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][3]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][3]["Item_1"][1]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[4][3]["Log"] = "%s,12000088,1[4],3006286,5"
	tPeachaGardenActive_PickPeachesChance[4][3]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*6	6.00%
	tPeachaGardenActive_PickPeachesChance[4][4] = {}
	tPeachaGardenActive_PickPeachesChance[4][4]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][4]["ItemChance"] = 600
	tPeachaGardenActive_PickPeachesChance[4][4]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][4]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][4]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][4]["Item_1"][1]["ItemAttr"] = "0 6"
	tPeachaGardenActive_PickPeachesChance[4][4]["Log"] = "%s,12000088,1[4],3006286,6"
	tPeachaGardenActive_PickPeachesChance[4][4]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*7	4.00%
	tPeachaGardenActive_PickPeachesChance[4][5] = {}
	tPeachaGardenActive_PickPeachesChance[4][5]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][5]["ItemChance"] = 400
	tPeachaGardenActive_PickPeachesChance[4][5]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][5]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][5]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][5]["Item_1"][1]["ItemAttr"] = "0 7"
	tPeachaGardenActive_PickPeachesChance[4][5]["Log"] = "%s,12000088,1[4],3006286,7"
	tPeachaGardenActive_PickPeachesChance[4][5]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*8	2.00%
	tPeachaGardenActive_PickPeachesChance[4][6] = {}
	tPeachaGardenActive_PickPeachesChance[4][6]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][6]["ItemChance"] = 200
	tPeachaGardenActive_PickPeachesChance[4][6]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][6]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][6]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[4][6]["Item_1"][1]["ItemAttr"] = "0 8"
	tPeachaGardenActive_PickPeachesChance[4][6]["Log"] = "%s,12000088,1[4],3006286,8"
	tPeachaGardenActive_PickPeachesChance[4][6]["Index"] = "RewardOneItem"
	
	-- 天机果(1~3点)	6.00%
	tPeachaGardenActive_PickPeachesChance[4][7] = {}
	tPeachaGardenActive_PickPeachesChance[4][7]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][7]["ItemChance"] = 600
	tPeachaGardenActive_PickPeachesChance[4][7]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][7]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][7]["Item_1"][1]["Id"] = 3001044
	tPeachaGardenActive_PickPeachesChance[4][7]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[4][7]["Log"] = "%s,12000088,1[4],3001044,1"
	tPeachaGardenActive_PickPeachesChance[4][7]["Index"] = "RewardOneItem"
	tPeachaGardenActive_PickPeachesChance[4][7]["Broadcast"] = true
	
	-- 2倍翻倍卷（4层以下含4层）	10.00%
	tPeachaGardenActive_PickPeachesChance[4][8] = {}
	tPeachaGardenActive_PickPeachesChance[4][8]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][8]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[4][8]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][8]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][8]["Item_1"][1]["Id"] = 3006742
	tPeachaGardenActive_PickPeachesChance[4][8]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[4][8]["Log"] = "%s,12000088,1[4],3006742,1"
	tPeachaGardenActive_PickPeachesChance[4][8]["Index"] = "RewardOneItem"
	
	-- 力王酒*6	14.00%
	tPeachaGardenActive_PickPeachesChance[4][9] = {}
	tPeachaGardenActive_PickPeachesChance[4][9]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][9]["ItemChance"] = 1400
	tPeachaGardenActive_PickPeachesChance[4][9]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][9]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][9]["Item_1"][1]["Id"] = 3006283
	tPeachaGardenActive_PickPeachesChance[4][9]["Item_1"][1]["ItemAttr"] = "0 6"
	tPeachaGardenActive_PickPeachesChance[4][9]["Log"] = "%s,12000088,1[4],3006283,6"
	tPeachaGardenActive_PickPeachesChance[4][9]["Index"] = "RewardOneItem"
	
	-- 力王酒*5	20.00%
	tPeachaGardenActive_PickPeachesChance[4][10] = {}
	tPeachaGardenActive_PickPeachesChance[4][10]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[4][10]["ItemChance"] = 2000
	tPeachaGardenActive_PickPeachesChance[4][10]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[4][10]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[4][10]["Item_1"][1]["Id"] = 3006283
	tPeachaGardenActive_PickPeachesChance[4][10]["Item_1"][1]["ItemAttr"] = "0 5"
	tPeachaGardenActive_PickPeachesChance[4][10]["Log"] = "%s,12000088,1[4],3006283,5"
	tPeachaGardenActive_PickPeachesChance[4][10]["Index"] = "RewardOneItem"
	
	-- 第五次摘桃
	tPeachaGardenActive_PickPeachesChance[5] = {}
	tPeachaGardenActive_PickPeachesChance[5]["ItemChanceSum"] = 10000
	tPeachaGardenActive_PickPeachesChance[5]["EmoneyLog"] = "250	4058	0	0	6	"
	
	-- 天机果(1~3点)	30.00%
	tPeachaGardenActive_PickPeachesChance[5][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][1]["ItemChance"] = 3000
	tPeachaGardenActive_PickPeachesChance[5][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][1]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][1]["Item_1"][1]["Id"] = 3001044
	tPeachaGardenActive_PickPeachesChance[5][1]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[5][1]["Log"] = "%s,12000088,1[5],3001044,1"
	tPeachaGardenActive_PickPeachesChance[5][1]["Index"] = "RewardOneItem"
	tPeachaGardenActive_PickPeachesChance[5][1]["Broadcast"] = true
	
	-- 超级天机果（2~5点）	10.00%
	tPeachaGardenActive_PickPeachesChance[5][2] = {}
	tPeachaGardenActive_PickPeachesChance[5][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][2]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[5][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][2]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][2]["Item_1"][1]["Id"] = 3006744
	tPeachaGardenActive_PickPeachesChance[5][2]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[5][2]["Log"] = "%s,12000088,1[5],3006744,1"
	tPeachaGardenActive_PickPeachesChance[5][2]["Index"] = "RewardOneItem"
	tPeachaGardenActive_PickPeachesChance[5][2]["Broadcast"] = true

	-- 2倍翻倍卷（5层适用）	10.00%
	tPeachaGardenActive_PickPeachesChance[5][3] = {}
	tPeachaGardenActive_PickPeachesChance[5][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][3]["ItemChance"] = 1000
	tPeachaGardenActive_PickPeachesChance[5][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][3]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][3]["Item_1"][1]["Id"] = 3006743
	tPeachaGardenActive_PickPeachesChance[5][3]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[5][3]["Log"] = "%s,12000088,1[5],3006743,1"
	tPeachaGardenActive_PickPeachesChance[5][3]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*10	18.00%
	tPeachaGardenActive_PickPeachesChance[5][4] = {}
	tPeachaGardenActive_PickPeachesChance[5][4]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][4]["ItemChance"] = 1800
	tPeachaGardenActive_PickPeachesChance[5][4]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][4]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][4]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[5][4]["Item_1"][1]["ItemAttr"] = "0 10"
	tPeachaGardenActive_PickPeachesChance[5][4]["Log"] = "%s,12000088,1[5],3006286,10"
	tPeachaGardenActive_PickPeachesChance[5][4]["Index"] = "RewardOneItem"
	
	-- 秘令赌博卷*12	14.00%
	tPeachaGardenActive_PickPeachesChance[5][5] = {}
	tPeachaGardenActive_PickPeachesChance[5][5]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][5]["ItemChance"] = 1400
	tPeachaGardenActive_PickPeachesChance[5][5]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][5]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][5]["Item_1"][1]["Id"] = 3006286
	tPeachaGardenActive_PickPeachesChance[5][5]["Item_1"][1]["ItemAttr"] = "0 12"
	tPeachaGardenActive_PickPeachesChance[5][5]["Log"] = "%s,12000088,1[5],3006286,12"
	tPeachaGardenActive_PickPeachesChance[5][5]["Index"] = "RewardOneItem"
	
	-- 2倍翻倍卷（4层以下含4层）	18.00%
	tPeachaGardenActive_PickPeachesChance[5][6] = {}
	tPeachaGardenActive_PickPeachesChance[5][6]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[5][6]["ItemChance"] = 1800
	tPeachaGardenActive_PickPeachesChance[5][6]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[5][6]["Item_1"][1] = {}
	tPeachaGardenActive_PickPeachesChance[5][6]["Item_1"][1]["Id"] = 3006742
	tPeachaGardenActive_PickPeachesChance[5][6]["Item_1"][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[5][6]["Log"] = "%s,12000088,1[5],3006742,1"
	tPeachaGardenActive_PickPeachesChance[5][6]["Index"] = "RewardOneItem"
	
	-- 小仙桃		3006286
	tPeachaGardenActive_PickPeachesChance[3006286] = {}
	tPeachaGardenActive_PickPeachesChance[3006286]["ItemChanceSum"] = 10000
	
	-- 获得1个密令	45%
	tPeachaGardenActive_PickPeachesChance[3006286][1] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006286][1]["ItemChance"] = 4500
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Item_1"][1] = 3004895
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Item_1"][2] = 3004896
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Item_1"][3] = 3004897
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Item_1"][4] = 3004898
	tPeachaGardenActive_PickPeachesChance[3006286][1]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Log"] = "0,0,3006286,1,12000088,1,%d,1"
	tPeachaGardenActive_PickPeachesChance[3006286][1]["Index"] = "One"
	
	-- 获得密令碎片（2合1）	54%
	tPeachaGardenActive_PickPeachesChance[3006286][2] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006286][2]["ItemChance"] = 5400
	tPeachaGardenActive_PickPeachesChance[3006286][2]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][2]["Item_1"][1] = 3006287
	tPeachaGardenActive_PickPeachesChance[3006286][2]["ItemAttr"] = "0 1"
	tPeachaGardenActive_PickPeachesChance[3006286][2]["Log"] = "0,0,3006286,1,12000088,1,%d,1"
	tPeachaGardenActive_PickPeachesChance[3006286][2]["Index"] = "One"
	
	-- 获得2个密令	1%
	tPeachaGardenActive_PickPeachesChance[3006286][3] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006286][3]["ItemChance"] = 100
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Item_1"] = {}
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Item_1"][1] = 3004895
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Item_1"][2] = 3004896
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Item_1"][3] = 3004897
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Item_1"][4] = 3004898
	tPeachaGardenActive_PickPeachesChance[3006286][3]["ItemAttr"] = "0 2"
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Log"] = "0,0,3006286,1,12000088,1,%d,2"
	tPeachaGardenActive_PickPeachesChance[3006286][3]["Index"] = "Two"
	
	-- 绝世蟠桃		3006744
	tPeachaGardenActive_PickPeachesChance[3006744] = {}
	tPeachaGardenActive_PickPeachesChance[3006744]["ItemChanceSum"] = 10000
	
	-- 2	60.00%
	tPeachaGardenActive_PickPeachesChance[3006744][1] = {}
	tPeachaGardenActive_PickPeachesChance[3006744][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006744][1]["ItemChance"] = 6000
	tPeachaGardenActive_PickPeachesChance[3006744][1]["Item_1"] = 2
	
	-- 3	20%
	tPeachaGardenActive_PickPeachesChance[3006744][2] = {}
	tPeachaGardenActive_PickPeachesChance[3006744][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006744][2]["ItemChance"] = 2000
	tPeachaGardenActive_PickPeachesChance[3006744][2]["Item_1"] = 3
	
	-- 4	15.00%
	tPeachaGardenActive_PickPeachesChance[3006744][3] = {}
	tPeachaGardenActive_PickPeachesChance[3006744][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006744][3]["ItemChance"] = 1500
	tPeachaGardenActive_PickPeachesChance[3006744][3]["Item_1"] = 4
	
	-- 5	5.00%
	tPeachaGardenActive_PickPeachesChance[3006744][4] = {}
	tPeachaGardenActive_PickPeachesChance[3006744][4]["RandomItemChanceType"] = 2
	tPeachaGardenActive_PickPeachesChance[3006744][4]["ItemChance"] = 500
	tPeachaGardenActive_PickPeachesChance[3006744][4]["Item_1"] = 5

local tPeachaGardenActive_Conversion = {}
	-- 秘令转化卡要转化的秘令
	tPeachaGardenActive_Conversion[3006285] = 3004895
	tPeachaGardenActive_Conversion[3006798] = 3004898
	tPeachaGardenActive_Conversion[3006799] = 3004897
	tPeachaGardenActive_Conversion[3006800] = 3004896
	-- 秘令转化卡转化后的秘令
	tPeachaGardenActive_Conversion[1] = {ItemId = 3004895,Index = "Strength"}
	tPeachaGardenActive_Conversion[2] = {ItemId = 3004898,Index = "Speed"}
	tPeachaGardenActive_Conversion[3] = {ItemId = 3004897,Index = "Health"}
	tPeachaGardenActive_Conversion[4] = {ItemId = 3004896,Index = "Soul"}

	
-- NPC移动规则表
local tPeachaGardenActive_NpcInfo = {}
	-- 蟠桃树NPC移动规则
	tPeachaGardenActive_NpcInfo[18599] = {NextIndex = 21,OneIndex = 1,OtherIndex = 21,RelatNpcId = 18609}
	tPeachaGardenActive_NpcInfo[18609] = {NextIndex = 1,OneIndex = 1,OtherIndex = 21,RelatNpcId = 18599}

	-- 杂草NPC移动规则
	tPeachaGardenActive_NpcInfo[18639] = {NextIndex = 16,OneIndex = 11,OtherIndex = 16}
	tPeachaGardenActive_NpcInfo[18640] = {NextIndex = 17,OneIndex = 12,OtherIndex = 17}
	tPeachaGardenActive_NpcInfo[18641] = {NextIndex = 18,OneIndex = 13,OtherIndex = 18}
	tPeachaGardenActive_NpcInfo[18642] = {NextIndex = 19,OneIndex = 14,OtherIndex = 19}
	tPeachaGardenActive_NpcInfo[18643] = {NextIndex = 20,OneIndex = 15,OtherIndex = 20}

-- 坐标配置表
local tPeachaGardenActive_PosInfo = {}	
	-- 蟠桃树的坐标
	tPeachaGardenActive_PosInfo[1] = {MapId = 3937,X = 28,Y = 28}

	-- 杂草的坐标
	tPeachaGardenActive_PosInfo[11] = {MapId = 3937,X = 53,Y = 30}	
	tPeachaGardenActive_PosInfo[12] = {MapId = 3937,X = 65,Y = 45}	
	tPeachaGardenActive_PosInfo[13] = {MapId = 3937,X = 77,Y = 51}	
	tPeachaGardenActive_PosInfo[14] = {MapId = 3937,X = 67,Y = 70}	
	tPeachaGardenActive_PosInfo[15] = {MapId = 3937,X = 54,Y = 78}	
	tPeachaGardenActive_PosInfo[16] = {MapId = 3937,X = 56,Y = 57}	
	tPeachaGardenActive_PosInfo[17] = {MapId = 3937,X = 44,Y = 61}	
	tPeachaGardenActive_PosInfo[18] = {MapId = 3937,X = 41,Y = 68}	
	tPeachaGardenActive_PosInfo[19] = {MapId = 3937,X = 29,Y = 54}	
	tPeachaGardenActive_PosInfo[20] = {MapId = 3937,X = 34,Y = 16}
	-- 集中营坐标
	tPeachaGardenActive_PosInfo[21] = {MapId = 5000,X = 100,Y = 100}	

-- 刷新力王神酒数量随机表
local tPeachaGardenActive_Refresh = {}
	tPeachaGardenActive_Refresh[1] = {}
	tPeachaGardenActive_Refresh[1]["ItemChanceSum"] = 10000
	
	-- 1	50.00%
	tPeachaGardenActive_Refresh[1][1] = {}
	tPeachaGardenActive_Refresh[1][1]["RandomItemChanceType"] = 2
	tPeachaGardenActive_Refresh[1][1]["ItemChance"] = 5000
	tPeachaGardenActive_Refresh[1][1]["Item_1"] = 1
	
	-- 2	40%
	tPeachaGardenActive_Refresh[1][2] = {}
	tPeachaGardenActive_Refresh[1][2]["RandomItemChanceType"] = 2
	tPeachaGardenActive_Refresh[1][2]["ItemChance"] = 4000
	tPeachaGardenActive_Refresh[1][2]["Item_1"] = 2
	
	-- 3	10.00%
	tPeachaGardenActive_Refresh[1][3] = {}
	tPeachaGardenActive_Refresh[1][3]["RandomItemChanceType"] = 2
	tPeachaGardenActive_Refresh[1][3]["ItemChance"] = 1000
	tPeachaGardenActive_Refresh[1][3]["Item_1"] = 3

-- 兑换的气力表
local tPeachaGardenActive_Exchange = {}
	-- 百炼天机果（1000点气力值）。
	tPeachaGardenActive_Exchange[3001044] = 1000
	-- 绝世蟠桃（2000点气力值）。
	tPeachaGardenActive_Exchange[3006744] = 2000
	-- 绝世蟠桃王（5000点气力值）。
	tPeachaGardenActive_Exchange[3006282] = 5000
	-- 双倍欣喜券（500点气力值）。
	tPeachaGardenActive_Exchange[3006742] = 500
	-- 双倍惊喜券（650点气力值）。
	tPeachaGardenActive_Exchange[3006743] = 650
	
--------------------------------------逻辑部分-----------------------------------------	
-- 使用背包信
function PeachaGardenActive_BackpackLetter(nItemId,nType,nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		if nNpcId == nil and Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	if nType == 1 or nNpcId ~= nil then
		PeachaGardenActive_PathFind(nItemId)
	elseif Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nLev = Get_UserLevel()
		local sContent = ""
		local sLog = ""
		
		if nLev >= tPeachaGardenActive_Constant["MaxLev"] then
			User_AddCultivation(tPeachaGardenActive_Item[nItemId]["Cultivation"])
			sContent = tPeachaGardenActive_Text[nItemId]["RewardCultivation"]
			sLog = tPeachaGardenActive_Item[nItemId]["CultivationLog"]
		else
			User_AddExpTime(tPeachaGardenActive_Item[nItemId]["Exp"])
			sContent = tPeachaGardenActive_Text[nItemId]["RewardExp"]
			sLog = tPeachaGardenActive_Item[nItemId]["ExpLog"]
		end

		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
	end
end

-- 传送地图
function PeachaGardenActive_ChgMap(nNpcId)
	-- 判断是否在可传送时间
	if tPeachaGardenActive_ChgMapInfo[nNpcId]["ActivityTime"] ~= nil and (not Sys_ChkFullTime(tPeachaGardenActive_ChgMapInfo[nNpcId]["ActivityTime"])) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断玩家等级
	if tPeachaGardenActive_ChgMapInfo[nNpcId]["Level"] ~= nil then
		if not User_JudgeLevelAndMetempsychosis(tPeachaGardenActive_ChgMapInfo[nNpcId]["Level"],tPeachaGardenActive_ChgMapInfo[nNpcId]["Metempsychosis"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-1")
			return
		end
	end

	local nMapId = tPeachaGardenActive_ChgMapInfo[nNpcId]["MapId"]
	local nCellX = tPeachaGardenActive_ChgMapInfo[nNpcId]["CellX"]
	local nCellY = tPeachaGardenActive_ChgMapInfo[nNpcId]["CellY"]
	local nRange = tPeachaGardenActive_ChgMapInfo[nNpcId]["Range"]
	
	User_UserRandBoundTrans(nMapId,nCellX,nCellY,nRange,nRange)
	User_TalkChannel2005(tPeachaGardenActive_Text[nNpcId]["ChgMap"])
	
	if tPeachaGardenActive_Text[nNpcId]["MsgBox"] ~= nil then
		Sys_MsgBox(tPeachaGardenActive_Text[nNpcId]["MsgBox"])
	end
end

-- 自动寻路
function PeachaGardenActive_PathFind(nType)
	local nMapId = tPeachaGardenActive_PathFind[nType]["MapId"]
	local nPosX = tPeachaGardenActive_PathFind[nType]["CellX"]
	local nPosY = tPeachaGardenActive_PathFind[nType]["CellY"]
	local nGotoNpcId = tPeachaGardenActive_PathFind[nType]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nGotoNpcId)
end

-- 领取大力神酒判断
function PeachaGardenActive_ReceiveHerculesWine(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nRewardType = tPeachaGardenActive_Stc["DataType"][2]
	
	-- 判断是否领取过
	if Task_ChkStcValue(nEventType,nRewardType,">=",tPeachaGardenActive_Constant["RewarData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nEventType,nRewardType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"2-1")
			return
		else
			Task_SetStatistic(nEventType,nRewardType,0,1)
			Task_SetStcTimestamp(nEventType,nRewardType,0)
		end
	end
	
	local nDemandType = tPeachaGardenActive_Stc["DataType"][1]
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDemandType,1,4) then
		Task_SetStatistic(nEventType,nDemandType,0,1)
		Task_SetStcTimestamp(nEventType,nDemandType,0)
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断任务是否完成
	if not Task_ChkStcValue(nEventType,nDemandType,">=",tPeachaGardenActive_Constant["DemandData"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(2) then
		Sys_MsgBox(tPeachaGardenActive_Text[nNpcId]["NoSpace"])
		return
	end

	local nItemNumEvent = tPeachaGardenActive_Stc[2]["EventType"]
	local nItemNumData = tPeachaGardenActive_Stc[2]["DataType"]
	
	if Task_ChkStcValue(nItemNumEvent,nItemNumData,"==",0) then
		Task_SetStatistic(nItemNumEvent,nItemNumData,1,1)
	end

	LinkNpcGossipFunc_New(nNpcId,"4-1")
end

-- 刷新力王神酒数量
function PeachaGardenActive_ReceiveHerculesRefresh(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(2) then
		Sys_MsgBox(tPeachaGardenActive_Text[nNpcId]["NoSpace"])
		return
	end
	
	local nUserEmoney = Get_UserEMoney()
	
	if nUserEmoney < tPeachaGardenActive_Constant["RefreshEmoney"] then
		-- 天石数量不足提示
		User_TalkChannel2005(tPeachaGardenActive_Text[nNpcId]["NoEmoney"])
		return
	end
	
	-- 扣天石
	User_AddEMoney(-tPeachaGardenActive_Constant["RefreshEmoney"])
	Sys_SaveEmoneyBuy(string.format("350	20060	%d	%d	1	",tPeachaGardenActive_Constant["RefreshEmoney"],tPeachaGardenActive_Constant["RefreshEmoney"]))
	
	-- 获取随机数量
	local nFlat,tAward = Probabil_RandomAward(tPeachaGardenActive_Refresh,1)
	local nItemNum = tAward[1]["tAward"][1]["Item_1"]
	local nItemNumEvent = tPeachaGardenActive_Stc[2]["EventType"]
	local nItemNumData = tPeachaGardenActive_Stc[2]["DataType"]
	
	Task_SetStatistic(nItemNumEvent,nItemNumData,nItemNum,1)
	LinkNpcGossipFunc_New(nNpcId,"4-1")
end

-- 领取大力神酒
function PeachaGardenActive_ReceiveHerculesSuccess(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(2) then
		Sys_MsgBox(tPeachaGardenActive_Text[nNpcId]["NoSpace"])
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nRewardType = tPeachaGardenActive_Stc["DataType"][2]
	local nItemNumEvent = tPeachaGardenActive_Stc[2]["EventType"]
	local nItemNumData = tPeachaGardenActive_Stc[2]["DataType"]
	local nItemNum = Get_UserStatisticValue(nItemNumEvent,nItemNumData)
	
	-- 设掩码
	Task_SetStatistic(nEventType,nRewardType,tPeachaGardenActive_Constant["RewarData"],1)
	Task_SetStcTimestamp(nEventType,nRewardType,0)
	Task_SetStatistic(nItemNumEvent,nItemNumData,1,1)
	
	-- 给物品
	Item_AddItem(tPeachaGardenActive_Constant["TaskItemId"],0,nItemNum)
	Item_AddItem(3006287)
	
	-- 打log
	local sLog = string.format("0,0,0,0,12000088,1,%d[3006287],%d[1]",tPeachaGardenActive_Constant["TaskItemId"],nItemNum)
	Sys_SaveActionFestivalLog(sLog)
	
	User_EffectAdd("self","angelwing")
	-- 提示
	local sContent = string.format(tPeachaGardenActive_Text[nNpcId]["RewardItem"],nItemNum)

	User_TalkChannel2005(sContent)
end 

-- 获取蟠桃的次数
function PeachaGardenActive_GetPickPeachesNum()
	local nEvent = tPeachaGardenActive_Stc["EventType"]
	local nDataType = tPeachaGardenActive_Stc["DataType"][4]
	local nData = Get_UserStatisticValue(nEvent,nDataType)
	
	return nData%tPeachaGardenActive_Constant["RecurrentNum"]
end

-- 采摘蟠桃前的判断
function PeachaGardenActive_CostJudge(nNpcId,sDouble)
	-- 判断是否要显示二次确认提示
	local nDisplayEvent = tPeachaGardenActive_Stc[1]["EventType"]
	local nDisplayData = tPeachaGardenActive_Stc[1]["DataType"]
	local nData = PeachaGardenActive_GetPickPeachesNum() + 1

	if Task_ChkStcValue(nDisplayEvent,nDisplayData,">=",1) then
		if sDouble == "true" then
			local nDoubleItemId = tPeachaGardenActive_Constant["Double"][nData]["ItemId"]
			PeachaGardenActive_PickPeaches(nNpcId,2,nDoubleItemId)
		else
			PeachaGardenActive_PickPeaches(nNpcId,1)
		end
		
		return
	end
	
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end

	-- 判断背包空间
	if sDouble == "true" then
		if not User_CheckLeftSpace(2) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	elseif not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	if sDouble == "true" then
		local nItemId = tPeachaGardenActive_Constant["Double"][nData]["ItemId"]
		
		if not Item_ChkItem(nItemId,1) then
			local sItemName = Get_ItemtypeName(nItemId)
			Sys_MsgBox(string.format(tPeachaGardenActive_Text[nNpcId]["NoItem"],sItemName))
			return
		end
	end

	-- 花费力王酒
	local nItemNum = tPeachaGardenActive_Cost[nData]["ItemNum"]
	local nItemId = tPeachaGardenActive_Constant["TaskItemId"]
	
	-- 判断是否有该物品
	if not Item_ChkMulItem(nItemId,nItemId,nItemNum,1) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	if sDouble == "true" then
		local sIndex = tPeachaGardenActive_Constant["Double"][nData]["Index"]
		LinkNpcGossipFunc_New(nNpcId,sIndex)
	else
		LinkNpcGossipFunc_New(nNpcId,"3-2")
	end
end

-- 摘桃
function PeachaGardenActive_PickPeaches(nNpcId,nTime,nDoubleItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end

	-- 检测是否有翻倍摘取的物品
	if nDoubleItemId ~= nil then
		if not Item_ChkItem(nDoubleItemId,1) then
			local sItemName = Get_ItemtypeName(nDoubleItemId)
			Sys_MsgBox(string.format(tPeachaGardenActive_Text[nNpcId]["NoItem"],sItemName))
			return
		end
		
		-- 判断背包空间
		if not User_CheckLeftSpace(2) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	elseif not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	local nData = PeachaGardenActive_GetPickPeachesNum() + 1
	local nEvent = tPeachaGardenActive_Stc["EventType"]
	local nDataType = tPeachaGardenActive_Stc["DataType"][4]
	
	-- 花费力王酒
	local nItemNum = tPeachaGardenActive_Cost[nData]["ItemNum"]
	local nItemId = tPeachaGardenActive_Constant["TaskItemId"]
	
	-- 判断物品数量
	if not Item_ChkMulItem(nItemId,nItemId,nItemNum,1) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 删除物品
	if not Item_DelMulItem(nItemId,nItemId,nItemNum,1) then
		return
	end
	
	-- 删除翻倍摘取的物品
	if nDoubleItemId ~= nil then
		if not Item_DelItem(nDoubleItemId) then
			return
		end
	end
	
	-- 设花费力王酒个数
	local nItemType = tPeachaGardenActive_Stc["DataType"][3]
	local nCostData = Get_UserStatisticValue(nEvent,nItemType)
	local sCost = string.format("0,0,%d,%d",nItemId,nItemNum)
	
	-- 设置掩码
	Task_SetStatistic(nEvent,nItemType,nCostData + nItemNum,1)
	-- 摘桃次数加1
	Task_AddStatistic(nEvent,nDataType,1,1)

	-- 给奖励的次数
	for index = 1,nTime do
		-- 获取随机奖励
		local nFlat,tAward = Probabil_RandomAward(tPeachaGardenActive_PickPeachesChance,nData)
		local tItem = tAward[1]["tAward"][1]["Item_1"]
		local sLog = tAward[1]["tAward"][1]["Log"]
		local sGetItem = ""
		local nGetItemNum = 0
		
		-- 给奖励
		for i,v in pairs (tItem) do
			local tItemAttr = Sys_Split(v["ItemAttr"]," ")
			local sItemNum = tItemAttr[2]
			local sItemName = ""
			
			-- 判断v["Id"]是否是一张表
			if type(v["Id"]) == "table" then
				local nRandom = math.random(1,#v["Id"])
				Item_AddNewItem(v["Id"][nRandom],v["ItemAttr"])
				
				sLog = string.format(sLog,sCost,v["Id"][nRandom])
				sItemName = Get_ItemtypeName(v["Id"][nRandom])
			else
				Item_AddNewItem(v["Id"],v["ItemAttr"])
				
				sLog = string.format(sLog,sCost)
				sItemName = Get_ItemtypeName(v["Id"])
			end

			local sItemInfo = string.format(tPeachaGardenActive_Text["GetItem"],sItemNum,sItemName)
			-- 获取奖励的描述
			if nGetItemNum == 0 then
				sGetItem = sItemInfo
			else
				sGetItem = string.format("%s%s%s",sGetItem,tPeachaGardenActive_Text["Symbol"],sItemInfo)
			end
			
			nGetItemNum  = nGetItemNum + 1
			
			-- 全服公告
			if tAward[1]["tAward"][1]["Broadcast"] == true then
				local sUserName = Get_UserName()
				local sContent = string.format(tPeachaGardenActive_Text["Broadcast"],sUserName,sItemName)
				
				Sys_SystemBroadcast(sContent)
			end
		end
	
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		
		-- 给提示
		local sText = string.format(tPeachaGardenActive_Text["RewardItem"],sGetItem)
		User_TalkChannel2005(sText)
	end
	
	-- 播光效
	User_EffectAdd("self",tPeachaGardenActive_Cost[nData]["Effect"])

	-- 出摘蟠桃王的对白
	if tPeachaGardenActive_Cost[nData]["Additional"] == true then
		local nNpcData0 = Get_NpcData0(nNpcId)
		
		if nNpcData0 > 0 and math.random(1,5) == 1 then
			LinkNpcGossipFunc_New(nNpcId,"4-1")
			return
		end
	end
	
	LinkNpcGossipFunc_New(nNpcId,"1")
end

-- 摘蟠桃王
function PeachaGardenActive_PeachKing(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nDataType = tPeachaGardenActive_Stc["DataType"][3]
	local nData = Get_UserStatisticValue(nEventType,nDataType)

	for nIndex = 1,#tPeachaGardenActive_PickPeachKing do
		-- 判断是哪个累计消费段
		if nData >= tPeachaGardenActive_PickPeachKing[nIndex]["CostItemNum"] then
			-- 获取随机奖励
			local nFlat,tAward = Probabil_RandomAward(tPeachaGardenActive_PickPeachKing,nIndex)
			
			if next(tAward[1]["tSelfItemChanceAward"]) ~= nil then
				-- 给物品
				Item_AddItem(tAward[1]["tSelfItemChanceAward"][1]["Item_1"])
				-- 打log
				Sys_SaveActionFestivalLog(tAward[1]["tSelfItemChanceAward"][1]["Log"])
				Sys_SaveEmoneyBuy(tPeachaGardenActive_Constant["EmoneyLog"])
				-- 给提示
				LinkNpcGossipFunc_New(nNpcId,"4-3")
				-- 移NPC
				PeachaGardenActive_MoveNpc()
				
				local sUserName = Get_UserName()
				local sItemName = Get_ItemtypeName(tAward[1]["tSelfItemChanceAward"][1]["Item_1"])
				local sContent = string.format(tPeachaGardenActive_Text["Broadcast"],sUserName,sItemName)
				
				Sys_SystemBroadcast(sContent)
				return
			end
		end
	end
	
	LinkNpcGossipFunc_New(nNpcId,"4-2")
end

-- 移动NPC
function PeachaGardenActive_MoveNpc(nNpcId)
	local nNpcId = nNpcId or Get_NpcId()
	
	if nNpcId == nil then
		return
	end

	local nIndex = tPeachaGardenActive_NpcInfo[nNpcId]["NextIndex"]
	
	-- 更改下次移动的索引
	if tPeachaGardenActive_NpcInfo[nNpcId]["NextIndex"] == tPeachaGardenActive_NpcInfo[nNpcId]["OneIndex"] then
		tPeachaGardenActive_NpcInfo[nNpcId]["NextIndex"] = tPeachaGardenActive_NpcInfo[nNpcId]["OtherIndex"]
	else
		tPeachaGardenActive_NpcInfo[nNpcId]["NextIndex"] = tPeachaGardenActive_NpcInfo[nNpcId]["OneIndex"]
	end

	-- 获取移动的位置
	PeachaGardenActive_MoveNpcPos(nNpcId,nIndex)

	-- 判断是否有相关联的NPC移动
	if tPeachaGardenActive_NpcInfo[nNpcId]["RelatNpcId"] ~= nil then
		local nMoveNpcId = tPeachaGardenActive_NpcInfo[nNpcId]["RelatNpcId"]
		nIndex = tPeachaGardenActive_NpcInfo[nMoveNpcId]["NextIndex"]

		PeachaGardenActive_MoveNpcPos(nMoveNpcId,nIndex)

		if tPeachaGardenActive_NpcInfo[nMoveNpcId]["NextIndex"] == tPeachaGardenActive_NpcInfo[nMoveNpcId]["OneIndex"] then
			tPeachaGardenActive_NpcInfo[nMoveNpcId]["NextIndex"] = tPeachaGardenActive_NpcInfo[nMoveNpcId]["OtherIndex"]
		else
			tPeachaGardenActive_NpcInfo[nMoveNpcId]["NextIndex"] = tPeachaGardenActive_NpcInfo[nMoveNpcId]["OneIndex"]
		end
	end
end

function PeachaGardenActive_MoveNpcPos(nNpcId,nIndex)
	local nMapId = tPeachaGardenActive_PosInfo[nIndex]["MapId"]
	local nPosX = tPeachaGardenActive_PosInfo[nIndex]["X"]
	local nPosY = tPeachaGardenActive_PosInfo[nIndex]["Y"]
	
	Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
end

-- 除草
function PeachaGardenActive_Weed()
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nRewardType = tPeachaGardenActive_Stc["DataType"][2]
	
	-- 判断今天是否领取过力王酒
	if Task_ChkStcValue(nEventType,nRewardType,">=",tPeachaGardenActive_Constant["RewarData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nEventType,nRewardType,1,4) then
			User_TalkChannel2005(tPeachaGardenActive_Text["NoWeed"])
			return
		end
	end
	
	local nNpcId = Get_NpcId()
	User_SetExplore(1,tPeachaGardenActive_Text["Weed"],140,string.format("PeachaGardenActive_WeedSuccess</N>%d",nNpcId))
end

-- 除草成功
function PeachaGardenActive_WeedSuccess(nNpcId)
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		return
	end

	PeachaGardenActive_Stc("WeedSuccess")
	PeachaGardenActive_MoveNpc(nNpcId)
end

-- 杀怪判断
function PeachaGardenActive_KillMonster(nMonsterId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nRewardType = tPeachaGardenActive_Stc["DataType"][2]
	
	-- 判断今天是否领取过力王酒
	if Task_ChkStcValue(nEventType,nRewardType,">=",tPeachaGardenActive_Constant["RewarData"]) then
		-- 判断是否隔天
		if not Task_StcInterval(nEventType,nRewardType,1,4) then
			return
		end
	end
	
	PeachaGardenActive_Stc("KillMonster")
end

-- 掩码操作
function PeachaGardenActive_Stc(sIndex)
	local nEventType = tPeachaGardenActive_Stc["EventType"]
	local nDemandType = tPeachaGardenActive_Stc["DataType"][1]

	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDemandType,1,4) then
		Task_SetStatistic(nEventType,nDemandType,0,1)
	end

	Task_AddStatistic(nEventType,nDemandType,1,1)
	Task_SetStcTimestamp(nEventType,nDemandType,0)

	-- 判断任务是否完成
	if Task_ChkStcValue(nEventType,nDemandType,">=",tPeachaGardenActive_Constant["DemandData"]) then
		User_TalkChannel2005(tPeachaGardenActive_Text["Demand"])
		
		Sys_MsgBox(tPeachaGardenActive_Text["Demand"],string.format("PeachaGardenActive_PathFind</N>%d",2))
	else
		local nData = Get_UserStatisticValue(nEventType,nDemandType)

		local nNeedData = tPeachaGardenActive_Constant["DemandData"] - nData
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[sIndex],nNeedData))
	end
end

-- 秘令转化卡
function PeachaGardenActive_Conversion(nItemId,nIndex)
	-- 判断是否有该物品
	if not Item_ChkItem(nItemId,1) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NoItem"])
		return
	end
	
	local nReqItemId = tPeachaGardenActive_Conversion[nItemId]
	-- 判断是否有要转化的密令
	if not Item_ChkItem(nReqItemId,1) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NoReqItem"])
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoSpace"])
		return
	end
	
	if Item_DelItem(nItemId) and Item_DelItem(nReqItemId) then
		local nAddItemId = tPeachaGardenActive_Conversion[nIndex]["ItemId"]
		Item_AddItem(nAddItemId)
		-- 打log
		Sys_SaveActionFestivalLog(string.format("0,0,%d[%d],1[1],12000088,2,%d,1",nItemId,nReqItemId,nAddItemId))
		User_EffectAdd("self","dispel")
		-- 给提示
		local sIndex = tPeachaGardenActive_Conversion[nIndex]["Index"]
		User_TalkChannel2005(tPeachaGardenActive_Text[sIndex])
	end
end

-- 大力神酒
function PeachaGardenActive_HerculesWine(nItemId,nNum)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId,1) and Item_DelAllItemByType(nItemId) then
			User_TalkChannel2005(tPeachaGardenActive_Text["BeOverdue"])
		end
		
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoSpace"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
		Item_AddItem(3006283,0,nNum)
		Sys_SaveActionFestivalLog(string.format("0,0,%d,1,12000088,2,3006283,%d",nItemId,nNum))
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["Success"])
	end
end

-- 获取玩家属性点
function PeachaGardenActive_GetAttrPoint(nType)
	-- 获取力量属性点
	if nType == 1 then
		return Get_UserStrength()
	-- 获取敏捷属性点
	elseif nType == 2 then
		return Get_UserSpeed()
	-- 获取体质属性点
	elseif nType == 3 then
		return Get_UserHealth()
	-- 获取精神属性点
	elseif nType == 4 then
		return Get_UserSoul()
	end
end

-- 洗点属性
function PeachaGardenActive_WashAttrPoint(nType)
	-- 洗力量属性点
	if nType == 1 then
		User_AddStrength(-1)
	-- 洗敏捷属性点
	elseif nType == 2 then
		User_AddSpeed(-1)
	-- 洗体质属性点
	elseif nType == 3 then
		User_AddHealth(-1)
	-- 洗精神属性点
	elseif nType == 4 then
		User_AddSoul(-1)
	end
end

-- 洗点丹
function PeachaGardenActive_WashDan(nItemId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tPeachaGardenActive_Text["BeOverdue"])
		end
		
		return
	end
	
	-- 判断玩家等级限制
	local nMetempsychosis = Get_UserMetempsychosis()
	
	if nMetempsychosis < 1 then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoMetempsychosis"])
		return
	end

	-- 获取玩家属性点
	local nAttrPoint = PeachaGardenActive_GetAttrPoint(nType)
	local tMinPoint = {1,1,2,1}
	
	if nAttrPoint < tMinPoint[nType] then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NoItem"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
		PeachaGardenActive_WashAttrPoint(nType)
		Sys_SaveActionFestivalLog(string.format("0,0,%d,1,12000088,1,0,0",nItemId))
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["Success"])
	end
end

-- 使用绝世蟠桃
function PeachaGardenActive_UsePeach(nItemId)
	if not Item_ChkItem(nItemId,1) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NotItem"])
		return
	end
	
	local nNum = 5
	local nMaxAttr = tPeachaGardenActive_Constant["MaxAttr"]
	local nNowAttr = PeachaGardenActive_GetAttr()
	
	-- 判断属性点是否满
	if nNowAttr >= nMaxAttr then
		User_TalkChannel2005(tPeachaGardenActive_Text["NotAttr"])
		return
	end
	
	if Item_DelItem(nItemId) then
		local nFlat,tAward = Probabil_RandomAward(tPeachaGardenActive_PickPeachesChance,nItemId)
		local sLog = "0,0,3006744,1,12000088,1,0,0"
		nNum = tAward[1]["tAward"][1]["Item_1"]

		if nNowAttr + nNum > nMaxAttr then
			nNum = nMaxAttr - nNowAttr
		end
		
		-- 加属性点
		User_AddAddPoint(nNum)
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		-- 播放光效
		User_EffectAdd("self","SuperXp")
		-- 给提示
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[nItemId]["Success"],nNum))
	end
end

-- 使用绝世蟠桃强效催化令
function PeachaGardenActive_UsePeachPowerful(nItemId,nPowerfulItemId)
	if not (Item_ChkItem(nItemId,1) and Item_ChkItem(nPowerfulItemId,1)) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NotPowerfulItem"])
		return
	end
	
	local nEmoney = Get_UserEMoney()
	-- 判断玩家天石数量
	if nEmoney < 20000 then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoEmoney"])
		return
	end
	
	local nNum = 50
	local sLog = "0,0,3006801[3006744],1[1],12000088,1,0,0"
	local nMaxAttr = tPeachaGardenActive_Constant["MaxAttr"]
	local nNowAttr = PeachaGardenActive_GetAttr()
	
	-- 判断属性点是否满
	if nNowAttr >= nMaxAttr then
		User_TalkChannel2005(tPeachaGardenActive_Text["NotAttr"])
		return
	elseif nNowAttr + nNum > nMaxAttr then
		nNum = nMaxAttr - nNowAttr
	end
	
	if Item_DelItem(nItemId) and Item_DelItem(nPowerfulItemId) and User_AddEMoney(-20000) then
		-- 加属性点
		User_AddAddPoint(nNum)
		
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		Sys_SaveEmoneyBuy("250	4059	20000	20000	1	")
		
		-- 播放光效
		User_EffectAdd("self","SuperXp")
		
		-- 给提示
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[nItemId]["Success"],nNum))
	end
end

-- 取消二次确认提示
function PeachaGardenActive_Display(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nDisplayEvent = tPeachaGardenActive_Stc[1]["EventType"]
	local nDisplayData = tPeachaGardenActive_Stc[1]["DataType"]
	
	Task_SetStatistic(nDisplayEvent,nDisplayData,1,1)
end

-- 判断属性点是否满
function PeachaGardenActive_JudgeAttr(nAddPoint)
	local nMaxAttr = 900
	local nStrength = Get_UserStrength()
	local nSpeed = Get_UserSpeed()
	local nHealth = Get_UserHealth()
	local nSoul = Get_UserSoul()
	local nPoint = Get_UserAddPoint()
	
	if nStrength + nSpeed + nHealth + nSoul + nPoint + nAddPoint > nMaxAttr then
		return false
	else
		return true
	end
end

-- 获取玩家现有属性点
function PeachaGardenActive_GetAttr()
	local nStrength = Get_UserStrength()
	local nSpeed = Get_UserSpeed()
	local nHealth = Get_UserHealth()
	local nSoul = Get_UserSoul()
	local nPoint = Get_UserAddPoint()
	
	return nStrength + nSpeed + nHealth + nSoul + nPoint
end

-- 选择兑换的物品
function PeachaGardenActive_ExchangeConfirm(nNpcId,nItemId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ExchangeTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	Task_SetStatistic(tPeachaGardenActive_Stc[3]["EventType"],tPeachaGardenActive_Stc[3]["DataType"],nItemId,1)
	LinkNpcGossipFunc_New(nNpcId,"2-1")
end

-- 兑换气力值
function PeachaGardenActive_Exchange(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ExchangeTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	-- 判断玩家属性点是否满
	local nAttr = PeachaGardenActive_GetAttr()
	local nMaxAttr = tPeachaGardenActive_Constant["MaxAttr"]
	
	if nAttr < nMaxAttr then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	
	local nEventType = tPeachaGardenActive_Stc[3]["EventType"]
	local nDataType = tPeachaGardenActive_Stc[3]["DataType"]
	local nItemId = Get_UserStatisticValue(nEventType,nDataType)
	
	if nItemId == 0 or nItemId == nil then
		return
	end

	local nScore = tPeachaGardenActive_Exchange[nItemId]

	-- 判断玩家身上是否有百炼天机果
	if not Item_ChkItem(nItemId,1) then
		Sys_MsgBox(tPeachaGardenActive_Text[nNpcId]["NoItem"])
		return
	end
	
	if Item_DelItem(nItemId,1) then
		User_AddStrengthValue(nScore)
		Sys_SaveActionFestivalLog(string.format("0,0,%d,1,12000088,2,12,%d",nItemId,nScore))
		Sys_MsgBox(string.format(tPeachaGardenActive_Text[nNpcId]["Success"],nScore))
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 蟠桃大仙
tNpcFace[3731] = 6
tNpcGossip[18484] = tNpcGossip[18484] or DefaultNpc:new{}
tNpcGossip[18484]["OptionHidden"] = 1

-- 活动中主对白
tNpcGossip[18484]["Text1-1"] = {111,112}
tNpcGossip[18484]["Text111"] = tPeachaGardenActive_Text[18484]["111"]
tNpcGossip[18484]["Text112"] = tPeachaGardenActive_Text[18484]["112"]
tNpcGossip[18484]["tOption1-1"] = {1,2,3}
tNpcGossip[18484]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"])
end

-- 活动后
tNpcGossip[18484]["Text1-2"] = {121,122}
tNpcGossip[18484]["Text121"] = tPeachaGardenActive_Text[18484]["121"]
tNpcGossip[18484]["tOption1-2"] = {5}

-- 拜求大力神酒
tNpcGossip[18484]["Text2-1"] = {211}
tNpcGossip[18484]["Text211"] = tPeachaGardenActive_Text[18484]["211"]
tNpcGossip[18484]["tOption2-1"] = {6}

-- 交任务、失败、未完成任务
tNpcGossip[18484]["Text2-2"] = {221}
tNpcGossip[18484]["Text221"] = tPeachaGardenActive_Text[18484]["221"]
tNpcGossip[18484]["tOption2-2"] = {7}

-- 交任务、成功
tNpcGossip[18484]["Text2-3"] = {231}
tNpcGossip[18484]["Text231"] = tPeachaGardenActive_Text[18484]["231"]
tNpcGossip[18484]["tOption2-3"] = {8}

-- 蟠桃游园会介绍
tNpcGossip[18484]["Text3-1"] = {311,312,313,314}
tNpcGossip[18484]["Text311"] = tPeachaGardenActive_Text[18484]["311"]
tNpcGossip[18484]["Text312"] = tPeachaGardenActive_Text[18484]["312"]
tNpcGossip[18484]["Text313"] = tPeachaGardenActive_Text[18484]["313"]
tNpcGossip[18484]["Text314"] = tPeachaGardenActive_Text[18484]["314"]
tNpcGossip[18484]["tOption3-1"] = {9}

tNpcGossip[18484]["Text3-2"] = {321,322,323,324,325,326,327}
tNpcGossip[18484]["Text321"] = tPeachaGardenActive_Text[18619]["321"]
tNpcGossip[18484]["Text322"] = tPeachaGardenActive_Text[18619]["322"]
tNpcGossip[18484]["Text323"] = tPeachaGardenActive_Text[18619]["323"]
tNpcGossip[18484]["Text324"] = tPeachaGardenActive_Text[18619]["324"]
tNpcGossip[18484]["Text325"] = tPeachaGardenActive_Text[18619]["325"]
tNpcGossip[18484]["Text326"] = tPeachaGardenActive_Text[18619]["326"]
tNpcGossip[18484]["Text327"] = tPeachaGardenActive_Text[18619]["327"]
tNpcGossip[18484]["tOption3-2"] = {10}

-- 选项
tNpcGossip[18484]["Option1"] = tPeachaGardenActive_Text[18484]["Option1"]
tNpcGossip[18484]["OptionFunc1"]="PeachaGardenActive_ReceiveHerculesWine</N>18484"
tNpcGossip[18484]["Option2"] = tPeachaGardenActive_Text[18484]["Option2"]
tNpcGossip[18484]["OptionFunc2"]="PeachaGardenActive_ChgMap</N>18484"
tNpcGossip[18484]["Option3"] = tPeachaGardenActive_Text[18484]["Option3"]
tNpcGossip[18484]["OptionPoint3"]="3"
tNpcGossip[18484]["Option5"] = tPeachaGardenActive_Text[18484]["Option5"]
tNpcGossip[18484]["Option6"] = tPeachaGardenActive_Text[18484]["Option6"]
tNpcGossip[18484]["Option7"] = tPeachaGardenActive_Text[18484]["Option7"]
tNpcGossip[18484]["OptionFunc7"]="PeachaGardenActive_PathFind</N>1"
tNpcGossip[18484]["Option8"] = tPeachaGardenActive_Text[18484]["Option8"]
tNpcGossip[18484]["Option9"] = tPeachaGardenActive_Text[18484]["Option9"]
tNpcGossip[18484]["OptionPoint9"]="3-2"
tNpcGossip[18484]["Option10"] = tPeachaGardenActive_Text[18619]["Option9"]
tNpcGossip[18484]["OptionPoint10"]="1"

tNpcGossip[18484]["Text4-1"] = {411,412}
tNpcGossip[18484]["Text411"] = tPeachaGardenActive_Text[18484]["411"]
tNpcGossip[18484]["Text412"] = tPeachaGardenActive_Text[18484]["412"]
tNpcGossip[18484]["tOption4-1"] = {11,12}
tNpcGossip[18484]["ChkFunc4-1"] = function ()
	local nItemNumEvent = tPeachaGardenActive_Stc[2]["EventType"]
	local nItemNumData = tPeachaGardenActive_Stc[2]["DataType"]
	local nItemNum = Get_UserStatisticValue(nItemNumEvent,nItemNumData)
	
	tNpcGossip[18484]["Text411"] = string.format(tPeachaGardenActive_Text[18484]["411"],nItemNum)
	return true
end

tNpcGossip[18484]["Option11"] = tPeachaGardenActive_Text[18484]["Option11"]
tNpcGossip[18484]["OptionFunc11"]="PeachaGardenActive_ReceiveHerculesSuccess</N>18484"
tNpcGossip[18484]["Option12"] = tPeachaGardenActive_Text[18484]["Option12"]
tNpcGossip[18484]["OptionFunc12"]="PeachaGardenActive_ReceiveHerculesRefresh</N>18484"

-- 蟠桃树
tNpcGossip[18599] = tNpcGossip[18599] or DefaultNpc:new{}
tNpcGossip[18609] = tNpcGossip[18599]
tNpcGossip[18599]["OptionHidden"] = 1

-- 活动前
tNpcGossip[18599]["Text1-1"] = {111}
tNpcGossip[18599]["Text111"] = tPeachaGardenActive_Text[18599]["111"]
tNpcGossip[18599]["tOption1-1"] = {1}
tNpcGossip[18599]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tPeachaGardenActive_Constant["BeforeActivityTime"])
end

-- 活动中主对白
tNpcGossip[18599]["Text1-2"] = {121,122,123,124,125}
tNpcGossip[18599]["Text121"] = tPeachaGardenActive_Text[18599]["121"]
tNpcGossip[18599]["Text122"] = tPeachaGardenActive_Text[18599]["122"]
tNpcGossip[18599]["Text123"] = tPeachaGardenActive_Text[18599]["123"]
tNpcGossip[18599]["Text124"] = tPeachaGardenActive_Text[18599]["124"]
tNpcGossip[18599]["Text125"] = tPeachaGardenActive_Text[18599]["122"]
tNpcGossip[18599]["tOption1-2"] = {3,18}
tNpcGossip[18599]["ChkFunc1-2"] = function ()
	local nData = PeachaGardenActive_GetPickPeachesNum()
	local tIndex = {}
	local tNextIndex = {}
	tIndex = {"123","125","127","129","1211"}
	tNextIndex = {"124","126","128","1210","1212"}
	tNpcGossip[18599]["Text123"] = tPeachaGardenActive_Text[18599][tIndex[nData + 1]]
	tNpcGossip[18599]["Text124"] = tPeachaGardenActive_Text[18599][tNextIndex[nData + 1]]

	return Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"])
end

-- 活动后
tNpcGossip[18599]["Text1-3"] = {131}
tNpcGossip[18599]["Text131"] = tPeachaGardenActive_Text[18599]["131"]
tNpcGossip[18599]["tOption1-3"] = {6}

-- 玩家选1、失败、非活动时间
tNpcGossip[18599]["Text2-1"] = {211}
tNpcGossip[18599]["Text211"] = tPeachaGardenActive_Text[18599]["211"]
tNpcGossip[18599]["tOption2-1"] = {7}

-- 玩家选1、失败、背包满
tNpcGossip[18599]["Text2-2"] = {221}
tNpcGossip[18599]["Text221"] = tPeachaGardenActive_Text[18599]["221"]
tNpcGossip[18599]["tOption2-2"] = {8}

-- 玩家选2、失败、玩家身上无此物品
tNpcGossip[18599]["Text3-1"] = {311}
tNpcGossip[18599]["Text311"] = tPeachaGardenActive_Text[18599]["311"]
tNpcGossip[18599]["tOption3-1"] = {12}

-- 玩家选2、二次确认扣除大力神酒
tNpcGossip[18599]["Text3-2"] = {321}
tNpcGossip[18599]["Text321"] = tPeachaGardenActive_Text[18599]["321"]
tNpcGossip[18599]["tOption3-2"] = {13,30,14}
tNpcGossip[18599]["ChkFunc3-2"] = function ()
	local nData = PeachaGardenActive_GetPickPeachesNum()
	local nItemNum = tPeachaGardenActive_Cost[nData + 1]["ItemNum"]
	
	tNpcGossip[18599]["Text321"] = string.format(tPeachaGardenActive_Text[18599]["321"],nData + 1,nItemNum)
	return true
end

-- 玩家第五次采摘蟠桃王单独对白
tNpcGossip[18599]["Text4-1"] = {411,412,413,414}
tNpcGossip[18599]["Text411"] = tPeachaGardenActive_Text[18599]["411"]
tNpcGossip[18599]["Text412"] = tPeachaGardenActive_Text[18599]["412"]
tNpcGossip[18599]["Text413"] = tPeachaGardenActive_Text[18599]["413"]
tNpcGossip[18599]["Text414"] = tPeachaGardenActive_Text[18599]["414"]
tNpcGossip[18599]["tOption4-1"] = {15}

tNpcGossip[18599]["Text4-2"] = {421}
tNpcGossip[18599]["Text421"] = tPeachaGardenActive_Text[18599]["421"]
tNpcGossip[18599]["tOption4-2"] = {16}

tNpcGossip[18599]["Text4-3"] = {431}
tNpcGossip[18599]["Text431"] = tPeachaGardenActive_Text[18599]["431"]
tNpcGossip[18599]["tOption4-3"] = {17}

tNpcGossip[18599]["Text5-2"] = {521}
tNpcGossip[18599]["Text521"] = tPeachaGardenActive_Text[18599]["521"]
tNpcGossip[18599]["tOption5-2"] = {22,23}

tNpcGossip[18599]["Text5-4"] = {541}
tNpcGossip[18599]["Text541"] = tPeachaGardenActive_Text[18599]["541"]
tNpcGossip[18599]["tOption5-4"] = {26,27}

tNpcGossip[18599]["Text6-1"] = {611}
tNpcGossip[18599]["Text611"] = tPeachaGardenActive_Text[18599]["611"]
tNpcGossip[18599]["tOption6-1"] = {28,29}

tNpcGossip[18599]["Option1"] = tPeachaGardenActive_Text[18599]["Option1"]

tNpcGossip[18599]["Option3"] = tPeachaGardenActive_Text[18599]["Option3"]
tNpcGossip[18599]["OptionFunc3"]="PeachaGardenActive_CostJudge</N>18599"
tNpcGossip[18599]["OptionChkFunc3"] = function ()
	local nData = PeachaGardenActive_GetPickPeachesNum()
	local nItemNum = tPeachaGardenActive_Cost[nData + 1]["ItemNum"]
	
	tNpcGossip[18599]["Option3"] = string.format(tPeachaGardenActive_Text[18599]["Option3"],nItemNum)
	return true
end

tNpcGossip[18599]["Option4"] = tPeachaGardenActive_Text[18599]["Option4"]
tNpcGossip[18599]["Option6"] = tPeachaGardenActive_Text[18599]["Option6"]
tNpcGossip[18599]["Option7"] = tPeachaGardenActive_Text[18599]["Option7"]
tNpcGossip[18599]["Option8"] = tPeachaGardenActive_Text[18599]["Option8"]

tNpcGossip[18599]["Option12"] = tPeachaGardenActive_Text[18599]["Option12"]
tNpcGossip[18599]["Option13"] = tPeachaGardenActive_Text[18599]["Option13"]
tNpcGossip[18599]["OptionFunc13"]="PeachaGardenActive_PickPeaches</N>18599</N>1"
tNpcGossip[18599]["Option14"] = tPeachaGardenActive_Text[18599]["Option14"]
tNpcGossip[18599]["Option15"] = tPeachaGardenActive_Text[18599]["Option15"]
tNpcGossip[18599]["OptionFunc15"]="PeachaGardenActive_PeachKing</N>18599"
tNpcGossip[18599]["Option16"] = tPeachaGardenActive_Text[18599]["Option16"]
tNpcGossip[18599]["Option17"] = tPeachaGardenActive_Text[18599]["Option17"]
tNpcGossip[18599]["Option18"] = tPeachaGardenActive_Text[18599]["Option18"]
tNpcGossip[18599]["OptionFunc18"]="PeachaGardenActive_CostJudge</N>18599</S>true"
tNpcGossip[18599]["OptionChkFunc18"] = function ()
	local nData = PeachaGardenActive_GetPickPeachesNum() + 1
	
	if nData == 4 and Item_ChkItem(3006742,1) then
		return true
	elseif nData == 5 and Item_ChkItem(3006743,1) then
		return true
	else
		return false
	end
end

tNpcGossip[18599]["Option22"] = tPeachaGardenActive_Text[18599]["Option22"]
tNpcGossip[18599]["OptionFunc22"]="PeachaGardenActive_PickPeaches</N>18599</N>2</N>3006742"
tNpcGossip[18599]["Option23"] = tPeachaGardenActive_Text[18599]["Option23"]

tNpcGossip[18599]["Option26"] = tPeachaGardenActive_Text[18599]["Option26"]
tNpcGossip[18599]["OptionFunc26"]="PeachaGardenActive_PickPeaches</N>18599</N>2</N>3006743"
tNpcGossip[18599]["Option27"] = tPeachaGardenActive_Text[18599]["Option27"]
tNpcGossip[18599]["Option28"] = tPeachaGardenActive_Text[18599]["Option28"]
tNpcGossip[18599]["OptionFunc28"]="PeachaGardenActive_Display</N>18599"
tNpcGossip[18599]["Option29"] = tPeachaGardenActive_Text[18599]["Option29"]
tNpcGossip[18599]["Option30"] = tPeachaGardenActive_Text[18599]["Option30"]
tNpcGossip[18599]["OptionPoint30"]="6-1"

-- 蟠桃树（市场）
tNpcGossip[18619] = tNpcGossip[18619] or DefaultNpc:new{}
tNpcGossip[18619]["OptionHidden"] = 1

-- 活动前
tNpcGossip[18619]["Text1-1"] = {111,112,113}
tNpcGossip[18619]["Text111"] = tPeachaGardenActive_Text[18619]["111"]
tNpcGossip[18619]["Text112"] = tPeachaGardenActive_Text[18619]["112"]
tNpcGossip[18619]["Text113"] = tPeachaGardenActive_Text[18619]["113"]
tNpcGossip[18619]["tOption1-1"] = {1}
tNpcGossip[18619]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tPeachaGardenActive_Constant["BeforeActivityTime"])
end

-- 活动中主对白
tNpcGossip[18619]["Text1-2"] = {121,122,123}
tNpcGossip[18619]["Text121"] = tPeachaGardenActive_Text[18619]["121"]
tNpcGossip[18619]["Text122"] = tPeachaGardenActive_Text[18619]["122"]
tNpcGossip[18619]["Text123"] = tPeachaGardenActive_Text[18619]["123"]
tNpcGossip[18619]["tOption1-2"] = {2,3,4}
tNpcGossip[18619]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"])
end

-- 活动后
tNpcGossip[18619]["Text1-3"] = {131}
tNpcGossip[18619]["Text131"] = tPeachaGardenActive_Text[18619]["131"]
tNpcGossip[18619]["tOption1-3"] = {5}

-- 玩家等级不足
tNpcGossip[18619]["Text2-1"] = {211,212}
tNpcGossip[18619]["Text211"] = tPeachaGardenActive_Text[18619]["211"]
tNpcGossip[18619]["Text212"] = tPeachaGardenActive_Text[18619]["212"]
tNpcGossip[18619]["tOption2-1"] = {6}

-- 非活动时间
tNpcGossip[18619]["Text2-2"] = {221}
tNpcGossip[18619]["Text221"] = tPeachaGardenActive_Text[18619]["221"]
tNpcGossip[18619]["tOption2-2"] = {7}

-- 蟠桃游园会介绍
tNpcGossip[18619]["Text3-1"] = {311,312,313,314}
tNpcGossip[18619]["Text311"] = tPeachaGardenActive_Text[18619]["311"]
tNpcGossip[18619]["Text312"] = tPeachaGardenActive_Text[18619]["312"]
tNpcGossip[18619]["Text313"] = tPeachaGardenActive_Text[18619]["313"]
tNpcGossip[18619]["Text314"] = tPeachaGardenActive_Text[18619]["314"]
tNpcGossip[18619]["tOption3-1"] = {8}

tNpcGossip[18619]["Text3-2"] = {321,322,323,324,325,326,327}
tNpcGossip[18619]["Text321"] = tPeachaGardenActive_Text[18619]["321"]
tNpcGossip[18619]["Text322"] = tPeachaGardenActive_Text[18619]["322"]
tNpcGossip[18619]["Text323"] = tPeachaGardenActive_Text[18619]["323"]
tNpcGossip[18619]["Text324"] = tPeachaGardenActive_Text[18619]["324"]
tNpcGossip[18619]["Text325"] = tPeachaGardenActive_Text[18619]["325"]
tNpcGossip[18619]["Text326"] = tPeachaGardenActive_Text[18619]["326"]
tNpcGossip[18619]["Text327"] = tPeachaGardenActive_Text[18619]["327"]
tNpcGossip[18619]["tOption3-2"] = {9}

tNpcGossip[18619]["Option1"] = tPeachaGardenActive_Text[18619]["Option1"]
tNpcGossip[18619]["Option2"] = tPeachaGardenActive_Text[18619]["Option2"]
tNpcGossip[18619]["OptionFunc2"]="PeachaGardenActive_ChgMap</N>18619"
tNpcGossip[18619]["Option3"] = tPeachaGardenActive_Text[18619]["Option3"]
tNpcGossip[18619]["OptionPoint3"]="3-1"
tNpcGossip[18619]["Option4"] = tPeachaGardenActive_Text[18619]["Option4"]
tNpcGossip[18619]["Option5"] = tPeachaGardenActive_Text[18619]["Option5"]
tNpcGossip[18619]["Option6"] = tPeachaGardenActive_Text[18619]["Option6"]
tNpcGossip[18619]["Option7"] = tPeachaGardenActive_Text[18619]["Option7"]
tNpcGossip[18619]["Option8"] = tPeachaGardenActive_Text[18619]["Option8"]
tNpcGossip[18619]["OptionPoint8"]="3-2"
tNpcGossip[18619]["Option9"] = tPeachaGardenActive_Text[18619]["Option9"]
tNpcGossip[18619]["OptionPoint9"]="1"

-- 桃园仙女
tNpcFace[3733] = 111
tNpcFace[3734] = 111

tNpcGossip[18601] = tNpcGossip[18601] or DefaultNpc:new{}
tNpcGossip[18601]["OptionHidden"] = 1

tNpcGossip[18601]["Text1-1"] = {111,112,113,114,115}
tNpcGossip[18601]["Text111"] = tPeachaGardenActive_Text[18601]["111"]
tNpcGossip[18601]["Text112"] = tPeachaGardenActive_Text[18601]["112"]
tNpcGossip[18601]["Text113"] = tPeachaGardenActive_Text[18601]["113"]
tNpcGossip[18601]["Text114"] = tPeachaGardenActive_Text[18601]["114"]
tNpcGossip[18601]["Text115"] = tPeachaGardenActive_Text[18601]["115"]
tNpcGossip[18601]["tOption1-1"] = {1}

tNpcGossip[18601]["Option1"] = tPeachaGardenActive_Text[18601]["Option1"]

tNpcGossip[18602] = tNpcGossip[18601]

-- 神机道长
tNpcFace[3774] = 6
tNpcGossip[18767] = tNpcGossip[18767] or DefaultNpc:new{}
tNpcGossip[18767]["OptionHidden"] = 1

-- 属性未满
tNpcGossip[18767]["Text1-1"] = {111}
tNpcGossip[18767]["Text111"] = tPeachaGardenActive_Text[18767]["111"]
tNpcGossip[18767]["tOption1-1"] = {1}
tNpcGossip[18767]["ChkFunc1-1"] = function ()
	return PeachaGardenActive_GetAttr() < tPeachaGardenActive_Constant["MaxAttr"] and Sys_ChkFullTime(tPeachaGardenActive_Constant["ExchangeTime"])
end

tNpcGossip[18767]["Option1"] = tPeachaGardenActive_Text[18767]["Option1"]

-- 属性满
tNpcGossip[18767]["Text1-2"] = {121,122,123}
tNpcGossip[18767]["Text121"] = tPeachaGardenActive_Text[18767]["121"]
tNpcGossip[18767]["Text122"] = tPeachaGardenActive_Text[18767]["122"]
tNpcGossip[18767]["Text123"] = tPeachaGardenActive_Text[18767]["123"]
tNpcGossip[18767]["tOption1-2"] = {2,3,4,5,6}
tNpcGossip[18767]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tPeachaGardenActive_Constant["ExchangeTime"])
end

tNpcGossip[18767]["Option2"] = tPeachaGardenActive_Text[18767]["Option2"]
tNpcGossip[18767]["OptionFunc2"]="PeachaGardenActive_ExchangeConfirm</N>18767</N>3001044"
tNpcGossip[18767]["Option3"] = tPeachaGardenActive_Text[18767]["Option3"]
tNpcGossip[18767]["OptionFunc3"]="PeachaGardenActive_ExchangeConfirm</N>18767</N>3006744"
tNpcGossip[18767]["Option4"] = tPeachaGardenActive_Text[18767]["Option4"]
tNpcGossip[18767]["OptionFunc4"]="PeachaGardenActive_ExchangeConfirm</N>18767</N>3006282"
tNpcGossip[18767]["Option5"] = tPeachaGardenActive_Text[18767]["Option5"]
tNpcGossip[18767]["OptionFunc5"]="PeachaGardenActive_ExchangeConfirm</N>18767</N>3006742"
tNpcGossip[18767]["Option6"] = tPeachaGardenActive_Text[18767]["Option6"]
tNpcGossip[18767]["OptionFunc6"]="PeachaGardenActive_ExchangeConfirm</N>18767</N>3006743"

-- 闲聊对白
tNpcGossip[18767]["Text1-3"] = {131,132,133}
tNpcGossip[18767]["Text131"] = tPeachaGardenActive_Text[18767]["131"]
tNpcGossip[18767]["Text132"] = tPeachaGardenActive_Text[18767]["132"]
tNpcGossip[18767]["Text133"] = tPeachaGardenActive_Text[18767]["133"]
tNpcGossip[18767]["tOption1-3"] = {9}
tNpcGossip[18767]["Option9"] = tPeachaGardenActive_Text[18767]["Option9"]

tNpcGossip[18767]["Text2-1"] = {211}
tNpcGossip[18767]["Text211"] = tPeachaGardenActive_Text[18767]["211"]
tNpcGossip[18767]["tOption2-1"] = {7,8}
tNpcGossip[18767]["ChkFunc2-1"] = function ()
	local nEventType = tPeachaGardenActive_Stc[3]["EventType"]
	local nDataType = tPeachaGardenActive_Stc[3]["DataType"]
	local nItemId = Get_UserStatisticValue(nEventType,nDataType)
	local sItemName = Get_ItemtypeName(nItemId)
	local nScore = tPeachaGardenActive_Exchange[nItemId]
	
	tNpcGossip[18767]["Text211"] = string.format(tPeachaGardenActive_Text[18767]["211"],sItemName,nScore)
	return true
end

tNpcGossip[18767]["Option7"] = tPeachaGardenActive_Text[18767]["Option7"]
tNpcGossip[18767]["OptionFunc7"]="PeachaGardenActive_Exchange</N>18767"
tNpcGossip[18767]["Option8"] = tPeachaGardenActive_Text[18767]["Option8"]

--------------------------------------物品配置-------------------------------------------
-- 调皮的蟠桃
tItem[3006281] = tItem[3006281] or {}
tItem[3006281]["Text1-1"] = {111,112,113}
tItem[3006281]["Text111"] = tPeachaGardenActive_Text[3006281]["111"]
tItem[3006281]["Text112"] = tPeachaGardenActive_Text[3006281]["112"]
tItem[3006281]["Text113"] = tPeachaGardenActive_Text[3006281]["113"]
tItem[3006281]["tOption1-1"] = {1,2}

tItem[3006281]["Option1"] = tPeachaGardenActive_Text[3006281]["Option1"]
tItem[3006281]["OptionFunc1"]="PeachaGardenActive_BackpackLetter</N>3006281</N>1"
tItem[3006281]["Option2"] = tPeachaGardenActive_Text[3006281]["Option2"]
tItem[3006281]["OptionFunc2"]="PeachaGardenActive_BackpackLetter</N>3006281</N>2"

-- 洗髓神露碎片
tItem[3006284] = tItem[3006284] or {}
tItem[3006284]["Function"] = function(nItemId,sItemName)
	if not Item_ChkMulItem(nItemId,nItemId,10,1) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NoItem"])
		return
	end
	
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoSpace"])
		return
	end
	
	if Item_DelMulItem(nItemId,nItemId,10,1) then
		Item_AddItem(3001045)
		Sys_SaveActionFestivalLog("0,0,3006284,10,12000088,1,3001045,1")
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["Success"])
	end
end

-- 小仙桃
tItem[3006286] = tItem[3006286] or {}
tItem[3006286]["Function"] = function(nItemId,sItemName)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tPeachaGardenActive_Text["BeOverdue"])
		end
		
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoSpace"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
		local nFlat,tAward = Probabil_RandomAward(tPeachaGardenActive_PickPeachesChance,nItemId)
		local nRandom = math.random(1,#tAward[1]["tAward"][1]["Item_1"])
		local nAddItemId = tAward[1]["tAward"][1]["Item_1"][nRandom]
		local sItemName = Get_ItemtypeName(nAddItemId)
		local sIndex = tAward[1]["tAward"][1]["Index"]
		
		-- 添加物品
		Item_AddNewItem(nAddItemId,tAward[1]["tAward"][1]["ItemAttr"])
		User_EffectAdd("self","angelwing")
		-- 打log
		Sys_SaveActionFestivalLog(string.format(tAward[1]["tAward"][1]["Log"],nAddItemId))
		-- 给提示
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[nItemId][sIndex],sItemName))
	end
end

-- 仙桃壳
tItem[3006287] = tItem[3006287] or {}
tItem[3006287]["Function"] = function(nItemId,sItemName)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tPeachaGardenActive_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tPeachaGardenActive_Text["BeOverdue"])
		end
		
		return
	end
	
	-- 判断物品是否够
	if not Item_ChkMulItem(nItemId,nItemId,2,1) then
		User_TalkChannel2005(tPeachaGardenActive_Text[nItemId]["NoItem"])
		return
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tPeachaGardenActive_Text["NoSpace"])
		return
	end

	if Item_DelMulItem(nItemId,nItemId,2,1) then
		local tGetItemId = {}
			tGetItemId[1] = 3004895
			tGetItemId[2] = 3004896
			tGetItemId[3] = 3004897
			tGetItemId[4] = 3004898
		local nRandom = math.random(1,#tGetItemId)
		local nGetItemId = tGetItemId[nRandom]
		local sItemName = Get_ItemtypeName(nGetItemId)
		
		-- 添加物品
		Item_AddItem(nGetItemId)
		Sys_SaveActionFestivalLog(string.format("0,0,3006287,2,12000088,1,%d,1",nGetItemId))
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[nItemId]["Success"],sItemName))
	end
end

-- 力量洗点丹
tItem[3006288] = tItem[3006288] or {}
tItem[3006288]["Text1-1"] = {111}
tItem[3006288]["Text111"] = tPeachaGardenActive_Text[3006288]["111"]
tItem[3006288]["tOption1-1"] = {1}
tItem[3006288]["Option1"] = tPeachaGardenActive_Text[3006288]["Option1"]
tItem[3006288]["OptionFunc1"]="PeachaGardenActive_WashDan</N>3006288</N>1"

-- 敏捷洗点丹
tItem[3006289] = tItem[3006289] or {}
tItem[3006289]["Text1-1"] = {111}
tItem[3006289]["Text111"] = tPeachaGardenActive_Text[3006289]["111"]
tItem[3006289]["tOption1-1"] = {1}
tItem[3006289]["Option1"] = tPeachaGardenActive_Text[3006289]["Option1"]
tItem[3006289]["OptionFunc1"]="PeachaGardenActive_WashDan</N>3006289</N>2"

-- 体质洗点丹
tItem[3006322] = tItem[3006322] or {}
tItem[3006322]["Text1-1"] = {111}
tItem[3006322]["Text111"] = tPeachaGardenActive_Text[3006322]["111"]
tItem[3006322]["tOption1-1"] = {1}
tItem[3006322]["Option1"] = tPeachaGardenActive_Text[3006322]["Option1"]
tItem[3006322]["OptionFunc1"]="PeachaGardenActive_WashDan</N>3006322</N>3"

-- 精神洗点丹
tItem[3006323] = tItem[3006323] or {}
tItem[3006323]["Text1-1"] = {111}
tItem[3006323]["Text111"] = tPeachaGardenActive_Text[3006323]["111"]
tItem[3006323]["tOption1-1"] = {1}
tItem[3006323]["Option1"] = tPeachaGardenActive_Text[3006323]["Option1"]
tItem[3006323]["OptionFunc1"]="PeachaGardenActive_WashDan</N>3006323</N>4"

-- 力量秘令转化卡
tItem[3006285] = tItem[3006285] or {}
tItem[3006285]["Text1-1"] = {111}
tItem[3006285]["Text111"] = tPeachaGardenActive_Text[3006285]["111"]
tItem[3006285]["tOption1-1"] = {1,2,3}

tItem[3006285]["Text2-1"] = {211}
tItem[3006285]["Text211"] = tPeachaGardenActive_Text[3006285]["211"]
tItem[3006285]["tOption2-1"] = {4,5}

tItem[3006285]["Text2-2"] = {221}
tItem[3006285]["Text221"] = tPeachaGardenActive_Text[3006285]["221"]
tItem[3006285]["tOption2-2"] = {6,7}

tItem[3006285]["Text2-3"] = {231}
tItem[3006285]["Text231"] = tPeachaGardenActive_Text[3006285]["231"]
tItem[3006285]["tOption2-3"] = {8,9}

tItem[3006285]["Option1"] = tPeachaGardenActive_Text[3006285]["Option1"]
tItem[3006285]["OptionPoint1"]="2-1"
tItem[3006285]["Option2"] = tPeachaGardenActive_Text[3006285]["Option2"]
tItem[3006285]["OptionPoint2"]="2-2"
tItem[3006285]["Option3"] = tPeachaGardenActive_Text[3006285]["Option3"]
tItem[3006285]["OptionPoint3"]="2-3"
tItem[3006285]["Option4"] = tPeachaGardenActive_Text[3006285]["Option4"]
tItem[3006285]["OptionFunc4"]="PeachaGardenActive_Conversion</N>3006285</N>4"
tItem[3006285]["Option5"] = tPeachaGardenActive_Text[3006285]["Option5"]
tItem[3006285]["Option6"] = tPeachaGardenActive_Text[3006285]["Option6"]
tItem[3006285]["OptionFunc6"]="PeachaGardenActive_Conversion</N>3006285</N>3"
tItem[3006285]["Option7"] = tPeachaGardenActive_Text[3006285]["Option7"]
tItem[3006285]["Option8"] = tPeachaGardenActive_Text[3006285]["Option8"]
tItem[3006285]["OptionFunc8"]="PeachaGardenActive_Conversion</N>3006285</N>2"
tItem[3006285]["Option9"] = tPeachaGardenActive_Text[3006285]["Option9"]

-- 敏捷秘令转化卡
tItem[3006798] = tItem[3006798] or {}
tItem[3006798]["Text1-1"] = {111}
tItem[3006798]["Text111"] = tPeachaGardenActive_Text[3006798]["111"]
tItem[3006798]["tOption1-1"] = {1,2,3}

tItem[3006798]["Text2-1"] = {211}
tItem[3006798]["Text211"] = tPeachaGardenActive_Text[3006798]["211"]
tItem[3006798]["tOption2-1"] = {4,5}

tItem[3006798]["Text2-2"] = {221}
tItem[3006798]["Text221"] = tPeachaGardenActive_Text[3006798]["221"]
tItem[3006798]["tOption2-2"] = {6,7}

tItem[3006798]["Text2-3"] = {231}
tItem[3006798]["Text231"] = tPeachaGardenActive_Text[3006798]["231"]
tItem[3006798]["tOption2-3"] = {8,9}

tItem[3006798]["Option1"] = tPeachaGardenActive_Text[3006798]["Option1"]
tItem[3006798]["OptionPoint1"]="2-1"
tItem[3006798]["Option2"] = tPeachaGardenActive_Text[3006798]["Option2"]
tItem[3006798]["OptionPoint2"]="2-2"
tItem[3006798]["Option3"] = tPeachaGardenActive_Text[3006798]["Option3"]
tItem[3006798]["OptionPoint3"]="2-3"
tItem[3006798]["Option4"] = tPeachaGardenActive_Text[3006798]["Option4"]
tItem[3006798]["OptionFunc4"]="PeachaGardenActive_Conversion</N>3006798</N>4"
tItem[3006798]["Option5"] = tPeachaGardenActive_Text[3006798]["Option5"]
tItem[3006798]["Option6"] = tPeachaGardenActive_Text[3006798]["Option6"]
tItem[3006798]["OptionFunc6"]="PeachaGardenActive_Conversion</N>3006798</N>3"
tItem[3006798]["Option7"] = tPeachaGardenActive_Text[3006798]["Option7"]
tItem[3006798]["Option8"] = tPeachaGardenActive_Text[3006798]["Option8"]
tItem[3006798]["OptionFunc8"]="PeachaGardenActive_Conversion</N>3006798</N>1"
tItem[3006798]["Option9"] = tPeachaGardenActive_Text[3006798]["Option9"]

-- 体质秘令转化卡
tItem[3006799] = tItem[3006799] or {}
tItem[3006799]["Text1-1"] = {111}
tItem[3006799]["Text111"] = tPeachaGardenActive_Text[3006799]["111"]
tItem[3006799]["tOption1-1"] = {1,2,3}

tItem[3006799]["Text2-1"] = {211}
tItem[3006799]["Text211"] = tPeachaGardenActive_Text[3006799]["211"]
tItem[3006799]["tOption2-1"] = {4,5}

tItem[3006799]["Text2-2"] = {221}
tItem[3006799]["Text221"] = tPeachaGardenActive_Text[3006799]["221"]
tItem[3006799]["tOption2-2"] = {6,7}

tItem[3006799]["Text2-3"] = {231}
tItem[3006799]["Text231"] = tPeachaGardenActive_Text[3006799]["231"]
tItem[3006799]["tOption2-3"] = {8,9}

tItem[3006799]["Option1"] = tPeachaGardenActive_Text[3006799]["Option1"]
tItem[3006799]["OptionPoint1"]="2-1"
tItem[3006799]["Option2"] = tPeachaGardenActive_Text[3006799]["Option2"]
tItem[3006799]["OptionPoint2"]="2-2"
tItem[3006799]["Option3"] = tPeachaGardenActive_Text[3006799]["Option3"]
tItem[3006799]["OptionPoint3"]="2-3"
tItem[3006799]["Option4"] = tPeachaGardenActive_Text[3006799]["Option4"]
tItem[3006799]["OptionFunc4"]="PeachaGardenActive_Conversion</N>3006799</N>1"
tItem[3006799]["Option5"] = tPeachaGardenActive_Text[3006799]["Option5"]
tItem[3006799]["Option6"] = tPeachaGardenActive_Text[3006799]["Option6"]
tItem[3006799]["OptionFunc6"]="PeachaGardenActive_Conversion</N>3006799</N>4"
tItem[3006799]["Option7"] = tPeachaGardenActive_Text[3006799]["Option7"]
tItem[3006799]["Option8"] = tPeachaGardenActive_Text[3006799]["Option8"]
tItem[3006799]["OptionFunc8"]="PeachaGardenActive_Conversion</N>3006799</N>2"
tItem[3006799]["Option9"] = tPeachaGardenActive_Text[3006799]["Option9"]

-- 精神秘令转化卡
tItem[3006800] = tItem[3006800] or {}
tItem[3006800]["Text1-1"] = {111}
tItem[3006800]["Text111"] = tPeachaGardenActive_Text[3006800]["111"]
tItem[3006800]["tOption1-1"] = {1,2,3}

tItem[3006800]["Text2-1"] = {211}
tItem[3006800]["Text211"] = tPeachaGardenActive_Text[3006800]["211"]
tItem[3006800]["tOption2-1"] = {4,5}

tItem[3006800]["Text2-2"] = {221}
tItem[3006800]["Text221"] = tPeachaGardenActive_Text[3006800]["221"]
tItem[3006800]["tOption2-2"] = {6,7}

tItem[3006800]["Text2-3"] = {231}
tItem[3006800]["Text231"] = tPeachaGardenActive_Text[3006800]["231"]
tItem[3006800]["tOption2-3"] = {8,9}

tItem[3006800]["Option1"] = tPeachaGardenActive_Text[3006800]["Option1"]
tItem[3006800]["OptionPoint1"]="2-1"
tItem[3006800]["Option2"] = tPeachaGardenActive_Text[3006800]["Option2"]
tItem[3006800]["OptionPoint2"]="2-2"
tItem[3006800]["Option3"] = tPeachaGardenActive_Text[3006800]["Option3"]
tItem[3006800]["OptionPoint3"]="2-3"
tItem[3006800]["Option4"] = tPeachaGardenActive_Text[3006800]["Option4"]
tItem[3006800]["OptionFunc4"]="PeachaGardenActive_Conversion</N>3006800</N>1"
tItem[3006800]["Option5"] = tPeachaGardenActive_Text[3006800]["Option5"]
tItem[3006800]["Option6"] = tPeachaGardenActive_Text[3006800]["Option6"]
tItem[3006800]["OptionFunc6"]="PeachaGardenActive_Conversion</N>3006800</N>3"
tItem[3006800]["Option7"] = tPeachaGardenActive_Text[3006800]["Option7"]
tItem[3006800]["Option8"] = tPeachaGardenActive_Text[3006800]["Option8"]
tItem[3006800]["OptionFunc8"]="PeachaGardenActive_Conversion</N>3006800</N>2"
tItem[3006800]["Option9"] = tPeachaGardenActive_Text[3006800]["Option9"]

-- 绝世蟠桃
tItem[3006744] = tItem[3006744] or {}
tItem[3006744]["Text1-1"] = {111}
tItem[3006744]["Text111"] = tPeachaGardenActive_Text[3006744]["111"]
tItem[3006744]["tOption1-1"] = {1,2}
tItem[3006744]["Option1"] = tPeachaGardenActive_Text[3006744]["Option1"]
tItem[3006744]["OptionFunc1"]="PeachaGardenActive_UsePeach</N>3006744"
tItem[3006744]["Option2"] = tPeachaGardenActive_Text[3006744]["Option2"]
tItem[3006744]["OptionPoint2"]="1-2"
tItem[3006744]["OptionChkFunc2"] = function ()
	return Item_ChkItem(3006801,1)
end

tItem[3006744]["Text1-2"] = {121}
tItem[3006744]["Text121"] = tPeachaGardenActive_Text[3006744]["121"]
tItem[3006744]["tOption1-2"] = {3,4}
tItem[3006744]["Option3"] = tPeachaGardenActive_Text[3006744]["Option3"]
tItem[3006744]["OptionFunc3"]="PeachaGardenActive_UsePeachPowerful</N>3006744</N>3006801"
tItem[3006744]["Option4"] = tPeachaGardenActive_Text[3006744]["Option4"]

-- 双拼大力神酒（2杯）
tItem[3006802] = tItem[3006802] or {}
tItem[3006802]["Function"] = function(nItemId,sItemName)
	PeachaGardenActive_HerculesWine(nItemId,2)
end

-- 特饮大力神酒（4杯）
tItem[3006803] = tItem[3006803] or {}
tItem[3006803]["Function"] = function(nItemId,sItemName)
	PeachaGardenActive_HerculesWine(nItemId,4)
end

-- 豪华大力神酒（6杯）
tItem[3006804] = tItem[3006804] or {}
tItem[3006804]["Function"] = function(nItemId,sItemName)
	PeachaGardenActive_HerculesWine(nItemId,6)
end

-- 蟠桃王
tItem[3006282] = tItem[3006282] or {}
tItem[3006282]["Function"] = function(nItemId,sItemName)
	local nMaxAttr = tPeachaGardenActive_Constant["MaxAttr"]
	local nNowAttr = PeachaGardenActive_GetAttr()
	
	if nNowAttr >= nMaxAttr then
		User_TalkChannel2005(tPeachaGardenActive_Text["NotAttr"])
		return
	end
	
	local nAddAttr = 50
	
	if nNowAttr + nAddAttr > nMaxAttr then
		nAddAttr = nMaxAttr - nNowAttr
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId) then
		User_AddHealth(nAddAttr)
		Sys_SaveActionFestivalLog("0,0,3006282,1,12000088,1,0,0")
		User_EffectAdd("self","zf2-e129")
		User_TalkChannel2005(string.format(tPeachaGardenActive_Text[nItemId]["Success"],nAddAttr))
	end
end

--------------------------------------怪物掉落-------------------------------------------
-- tMonster[7741] = tMonster[7741] or {}
-- tMonster[7741]["tFunction"] = tMonster[7741]["tFunction"] or {}
-- table.insert(tMonster[7741]["tFunction"],PeachaGardenActive_KillMonster)