------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]暑期活动种瓜得瓜和总NPC
--Purpose:	暑期活动种瓜得瓜和总NPC
--Creator: 	郑鋆
--Created:	2015/05/04
------------------------------------------------------------------------------------

-- 命名前缀
-- SummerActive2015_ZhongGuaDeGua_

-- logId	12000091

-- 掩码使用情况
-- stc(134,39):表示玩家领取瓜种和cd
-- stc(134,40):玩家当天的分数~隔天重置
-- stc(134,41):玩家当天是否中5W游戏币奖励~隔天重置
-- stc(134,42):玩家当天是否领取60分礼包~隔天重置

-- 常量表
local tSummerActive2015_ZhongGuaDeGua_Constant = {}
	-- 活动时间
	tSummerActive2015_ZhongGuaDeGua_Constant["BeforeActivityTime"] = "2015-03-17 00:00 2015-07-08 23:59"
	tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"] = "2015-07-09 00:00 2015-07-22 23:59"
	tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"] = "00:00 22:59"
	tSummerActive2015_ZhongGuaDeGua_Constant["ReceiveTime"] = "2015-07-10 00:00 2015-07-23 22:59"
	tSummerActive2015_ZhongGuaDeGua_Constant["EndTime"] = "2015-07-23 00:00 2015-07-23 22:59"
	tSummerActive2015_ZhongGuaDeGua_Constant["AssignmentTime"] = "2015-07-09 00:00 2015-07-23 22:59"

	-- 等级限制
	tSummerActive2015_ZhongGuaDeGua_Constant["Metempsychosis"] = 0
	tSummerActive2015_ZhongGuaDeGua_Constant["Level"] = 80
	
	-- 动态存储表
	tSummerActive2015_ZhongGuaDeGua_Constant["RankGlobalId"] = 50868
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardGlobalId"] = 50869

	tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"] = {}
	tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][1] = 80044
	tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][2] = 80045
	tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][3] = 80046

	-- 领取种子的CD时间
	tSummerActive2015_ZhongGuaDeGua_Constant["SeedTime"] = 1
	tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemId"] = 3001503
	tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemNum"] = 10
	tSummerActive2015_ZhongGuaDeGua_Constant["SeedLog"] = "0,0,0,0,12000091,2,3001503,10"
	
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardData"] = 20
	
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"] = {}
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"][0] = 3001524
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"][1] = 3001525
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"][2] = 3001526
	tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"]["Log"] = "0,0,0,0,12000091,2,%d,1"
	
	-- 超级大奖需要的背包空间
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperRewardSpace"] = 11
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperRewardLog"] = "0,0,0,0,12000091,2,1088000[720027],1[10]"
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"] = {}
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][1]["ItemId"] = 1088000
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][1]["ItemNum"] = 1
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][2]["ItemId"] = 720027
	tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"][2]["ItemNum"] = 10
	
	tSummerActive2015_ZhongGuaDeGua_Constant["FestivalId"] = 3432
	tSummerActive2015_ZhongGuaDeGua_Constant["LogId"] = 12000091
	
-- stc掩码表
local tSummerActive2015_ZhongGuaDeGua_Stc = {}
	tSummerActive2015_ZhongGuaDeGua_Stc["EventType"] = 134
	tSummerActive2015_ZhongGuaDeGua_Stc["DataType"] = {}
	tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][1] = 39
	tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][2] = 40
	tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][3] = 41
	tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][4] = 42

-- 自动寻路表
local tSummerActive2015_ZhongGuaDeGua_AutoPath = {}
	-- 活动：追缉无影盗贼团。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[1] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[1]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[1]["CellX"] = 288
	tSummerActive2015_ZhongGuaDeGua_AutoPath[1]["CellY"] = 383
	tSummerActive2015_ZhongGuaDeGua_AutoPath[1]["NpcId"] = 10301
	-- 活动：魔术大师。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[2] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[2]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[2]["CellX"] = 272
	tSummerActive2015_ZhongGuaDeGua_AutoPath[2]["CellY"] = 360
	tSummerActive2015_ZhongGuaDeGua_AutoPath[2]["NpcId"] = 15811
	-- 活动：无畏勇者。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[3] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[3]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[3]["CellX"] = 275
	tSummerActive2015_ZhongGuaDeGua_AutoPath[3]["CellY"] = 385
	tSummerActive2015_ZhongGuaDeGua_AutoPath[3]["NpcId"] = 10296
	-- 活动：种瓜得瓜。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[4] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[4]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[4]["CellX"] = 277
	tSummerActive2015_ZhongGuaDeGua_AutoPath[4]["CellY"] = 360
	tSummerActive2015_ZhongGuaDeGua_AutoPath[4]["NpcId"] = 18510
	-- 活动：冰镇西瓜。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[5] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[5]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[5]["CellX"] = 300
	tSummerActive2015_ZhongGuaDeGua_AutoPath[5]["CellY"] = 379
	tSummerActive2015_ZhongGuaDeGua_AutoPath[5]["NpcId"] = 15806
	-- 活动：防晒大测验。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[6] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[6]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[6]["CellX"] = 284
	tSummerActive2015_ZhongGuaDeGua_AutoPath[6]["CellY"] = 360
	tSummerActive2015_ZhongGuaDeGua_AutoPath[6]["NpcId"] = 15810
	-- 活动：蓝桔梗冰淇淋。
	tSummerActive2015_ZhongGuaDeGua_AutoPath[7] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[7]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[7]["CellX"] = 295
	tSummerActive2015_ZhongGuaDeGua_AutoPath[7]["CellY"] = 383
	tSummerActive2015_ZhongGuaDeGua_AutoPath[7]["NpcId"] = 15813
	
	-- 使用西瓜
	tSummerActive2015_ZhongGuaDeGua_AutoPath[8] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[8]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[8]["CellX"] = 280
	tSummerActive2015_ZhongGuaDeGua_AutoPath[8]["CellY"] = 371
	tSummerActive2015_ZhongGuaDeGua_AutoPath[8]["NpcId"] = 0
	
	-- 夏日冰饮
	tSummerActive2015_ZhongGuaDeGua_AutoPath[9] = {}
	tSummerActive2015_ZhongGuaDeGua_AutoPath[9]["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_AutoPath[9]["CellX"] = 297
	tSummerActive2015_ZhongGuaDeGua_AutoPath[9]["CellY"] = 370
	tSummerActive2015_ZhongGuaDeGua_AutoPath[9]["NpcId"] = 18511

local tSummerActive2015_ZhongGuaDeGua_Watermelon = {}
	-- 绿皮西瓜
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1] = {}
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1]["ItemId"] = 711759
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1]["Log"] = "0,0,711759,1,12000091,2,0,0"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1]["Score"] = 1
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1]["Index"] = "4-4"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[1]["Effect"] = "angelwing3"
	-- 翡翠西瓜
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2] = {}
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2]["ItemId"] = 711760
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2]["Log"] = "0,0,711760,1,12000091,2,0,0"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2]["Score"] = 3
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2]["Index"] = "4-5"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[2]["Effect"] = "angelwing4"
	-- 白玉西瓜
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3] = {}
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3]["ItemId"] = 711761
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3]["Log"] = "0,0,711761,1,12000091,2,0,0"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3]["Score"] = 5
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3]["Index"] = "4-6"
	tSummerActive2015_ZhongGuaDeGua_Watermelon[3]["Effect"] = "angelwing5"

-- 使用西瓜
local tSummerActive2015_ZhongGuaDeGua_UseWatermelon = {}
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MapId"] = 1002
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MinCellX"] = 276
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MaxCellX"] = 286
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MinCellY"] = 365
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MaxCellY"] = 377
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["Second"] = 3
	tSummerActive2015_ZhongGuaDeGua_UseWatermelon["Action"] = 220

local tSummerActive2015_ZhongGuaDeGua_Chance = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503] = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503]["ItemChanceSum"] = 1000
	
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1] = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["ItemChance"] = 50
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["Item_1"] = 1
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["Log"] = "0,0,3001503,1,12000091,2,1,50000"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["Effect"] = "zf2-e024"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["Index"] = "Money"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][1]["Money"] = 50000
	
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2] = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["ItemChance"] = 150
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["Item_1"] = 711761
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["Log"] = "0,0,3001503,1,12000091,2,711761,1"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["Effect"] = "accession"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][2]["Index"] = "WhiteWatermelon"
	
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3] = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["ItemChance"] = 300
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["Item_1"] = 711760
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["Log"] = "0,0,3001503,1,12000091,2,711760,1"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["Effect"] = "eddy"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][3]["Index"] = "JadeWatermelon"
	
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4] = {}
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["ItemChance"] = 500
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["Item_1"] = 711759
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["Log"] = "0,0,3001503,1,12000091,2,711759,1"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_Chance[3001503][4]["Index"] = "GreenWatermelon"

local tSummerActive2015_ZhongGuaDeGua_Monster = {}
	-- 1	叫天鸡	94174270
	tSummerActive2015_ZhongGuaDeGua_Monster[1] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[1]["Level"] = 12
	-- 2	斑鸠王	94174280
	tSummerActive2015_ZhongGuaDeGua_Monster[2] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2]["Level"] = 18
	-- 3	罗罗鸟	94174290
	tSummerActive2015_ZhongGuaDeGua_Monster[3] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[3]["Level"] = 23
	-- 4	幽冥鬼斧94174300
	tSummerActive2015_ZhongGuaDeGua_Monster[4] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[4]["Level"] = 28
	-- 5	蹑空鬼斧94174310
	tSummerActive2015_ZhongGuaDeGua_Monster[5] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[5]["Level"] = 33
	-- 6	翼蛇	94174320
	tSummerActive2015_ZhongGuaDeGua_Monster[6] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[6]["Level"] = 38
	-- 7	土匪	94174330
	tSummerActive2015_ZhongGuaDeGua_Monster[7] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[7]["Level"] = 43
	-- 8	火鼠	94174340
	tSummerActive2015_ZhongGuaDeGua_Monster[8] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[8]["Level"] = 48
	-- 9	火精灵	94174350
	tSummerActive2015_ZhongGuaDeGua_Monster[9] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[9]["Level"] = 53
	-- 10	须猕猴	94174360
	tSummerActive2015_ZhongGuaDeGua_Monster[10] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[10]["Level"] = 58
	-- 66	精悍土匪	9593290
	tSummerActive2015_ZhongGuaDeGua_Monster[66] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[66]["Level"] = 43
	-- 67	尖牙火鼠	9593300
	tSummerActive2015_ZhongGuaDeGua_Monster[67] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[67]["Level"] = 48
	-- 11	巨臂猿	94174370
	tSummerActive2015_ZhongGuaDeGua_Monster[11] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[11]["Level"] = 63
	-- 12	天雷巨猿94174380
	tSummerActive2015_ZhongGuaDeGua_Monster[12] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[12]["Level"] = 68
	-- 13	蛇人	94174390
	tSummerActive2015_ZhongGuaDeGua_Monster[13] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[13]["Level"] = 73
	-- 14	沙怪	94174400
	tSummerActive2015_ZhongGuaDeGua_Monster[14] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[14]["Level"] = 78
	-- 15	锤山怪	94174410
	tSummerActive2015_ZhongGuaDeGua_Monster[15] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[15]["Level"] = 83
	-- 16	巨石怪	94174420
	tSummerActive2015_ZhongGuaDeGua_Monster[16] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[16]["Level"] = 88
	-- 17	鬼刃	94174430
	tSummerActive2015_ZhongGuaDeGua_Monster[17] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[17]["Level"] = 93
	-- 73	砾沙怪	9593390
	tSummerActive2015_ZhongGuaDeGua_Monster[73] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[73]["Level"] = 78
	-- 18	金臂鸟人94174440
	tSummerActive2015_ZhongGuaDeGua_Monster[18] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[18]["Level"] = 98
	-- 19	银羽鹰王94174450
	tSummerActive2015_ZhongGuaDeGua_Monster[19] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[19]["Level"] = 103
	-- 55	湖岛强匪94174460
	tSummerActive2015_ZhongGuaDeGua_Monster[55] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[55]["Level"] = 108
	-- 78	银羽鹰魔	4081255
	tSummerActive2015_ZhongGuaDeGua_Monster[78] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[78]["Level"] = 103
	-- 79	湖岛悍匪	4081259
	tSummerActive2015_ZhongGuaDeGua_Monster[79] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[79]["Level"] = 108
	-- 84	匪兵	9593450
	tSummerActive2015_ZhongGuaDeGua_Monster[84] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[84]["Level"] = 108
	-- 20	土墓蝠	94174470
	tSummerActive2015_ZhongGuaDeGua_Monster[20] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[20]["Level"] = 113
	-- 56	嗜血蝙蝠94174480
	tSummerActive2015_ZhongGuaDeGua_Monster[56] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[56]["Level"] = 118
	-- 57	牛怪	94174490
	tSummerActive2015_ZhongGuaDeGua_Monster[57] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[57]["Level"] = 123
	-- 58	血影红魔94174500
	tSummerActive2015_ZhongGuaDeGua_Monster[58] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[58]["Level"] = 128
	-- 2684	缚灵	9438000
	tSummerActive2015_ZhongGuaDeGua_Monster[2684] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2684]["Level"] = 141
	-- 2686	深海亡魂	9438010
	tSummerActive2015_ZhongGuaDeGua_Monster[2686] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2686]["Level"] = 141
	-- 2687	深海魔魂	98054382
	tSummerActive2015_ZhongGuaDeGua_Monster[2687] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2687]["Level"] = 141
	-- 2411	冰凌腾蛇	94174520
	tSummerActive2015_ZhongGuaDeGua_Monster[2411] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2411]["Level"] = 133
	-- 2416	冰煞邪刀	94174530
	tSummerActive2015_ZhongGuaDeGua_Monster[2416] = {}
	tSummerActive2015_ZhongGuaDeGua_Monster[2416]["Level"] = 138

local tSummerActive2015_ZhongGuaDeGua_RewardItem = {}
	-- 暑假欢笑大礼包
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524]["ItemChanceSum"] = 1000
	-- 聚神丹（赠）*1		10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["Item_1"] = 723700
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["Log"] = "0,0,3001524,1,12000091,2,723700,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][1]["Index"] = "PolyGodDan"
	-- 小祈愿石（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["Item_1"] = 1200000
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["Log"] = "0,0,3001524,1,12000091,2,1200000,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][2]["Index"] = "PrayerStone"
	-- 玄灵秘录（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["Item_1"] = 723341
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["Log"] = "0,0,3001524,1,12000091,2,723341,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][3]["Index"] = "XuanLingBalam"
	-- 昆仑雪水（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["Item_1"] = 723017
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["Log"] = "0,0,3001524,1,12000091,2,723017,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][4]["Index"] = "KunLunSnow"
	-- 记忆宝珠（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["Item_1"] = 720828
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["Log"] = "0,0,3001524,1,12000091,2,720828,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][5]["Index"] = "MemorySarah"
	-- 净尘纤水（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["Item_1"] = 721258
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["Log"] = "0,0,3001524,1,12000091,2,721258,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][6]["Index"] = "WaterFiberDust"
	-- 破城火雷（赠）*1	10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["Item_1"] = 721261
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["Log"] = "0,0,3001524,1,12000091,2,721261,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][7]["Index"] = "BreakTheCity"
	-- 金刚灵果（赠）*1	8%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["ItemChance"] = 80
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["Item_1"] = 711188
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["Log"] = "0,0,3001524,1,12000091,2,711188,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][8]["Index"] = "KingKongLing"
	-- 祖母绿（赠）*1		8%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["ItemChance"] = 80
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["Item_1"] = 1080001
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["Log"] = "0,0,3001524,1,12000091,2,1080001,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][9]["Index"] = "Emerald"
	-- 涅槃灵石（赠）*1	6%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["ItemChance"] = 60
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["Item_1"] = 721259
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["Log"] = "0,0,3001524,1,12000091,2,721259,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][10]["Index"] = "LingshiNirvana"
	-- 马鞍*5			4%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["ItemChance"] = 40
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["Item_1"] = 723903
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["ItemEffect"] = "0 5"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["Log"] = "0,0,3001524,1,12000091,2,723903,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][11]["Index"] = "Saddle"
	-- 淬炼礼包*1  720549	2%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["ItemChance"] = 20
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["Item_1"] = 720549
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["Log"] = "0,0,3001524,1,12000091,2,720549,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][12]["Index"] = "Cuilian"
	-- 普通天地玄*1		1%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["ItemChance"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][1]["Id"] = 700071
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][1]["Log"] = "0,0,3001524,1,12000091,2,700071,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][1]["Index"] = "XuanYuanGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][2]["Id"] = 700121
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][2]["Log"] = "0,0,3001524,1,12000091,2,700121,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][2]["Index"] = "LingGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][3]["Id"] = 700101
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][3]["Log"] = "0,0,3001524,1,12000091,2,700101,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Item_1"][3]["Index"] = "GemOfWrath"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][13]["Effect"] = "eidolon"
	-- 流星卷*1		1%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["ItemChance"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["Item_1"] = 720027
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["ItemEffect"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["Log"] = "0,0,3001524,1,12000091,2,720027,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001524][14]["Index"] = "MeteorVolume"

	-- 暑假欢笑大礼包
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525]["Space"] = 1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525]["ItemChanceSum"] = 1000
	-- 时装外套（7天时效）*1		15%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["ItemChance"] = 150
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][1]["Id"] = 185345
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][1]["Log"] = "0,0,3001525,1,12000091,2,185345,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][1]["Index"] = "MiaoStyle"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][2]["Id"] = 185365
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][2]["Log"] = "0,0,3001525,1,12000091,2,185365,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][2]["Index"] = "PrairieWind"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][3]["Id"] = 185375
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][3]["Log"] = "0,0,3001525,1,12000091,2,185375,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][3]["Index"] = "TianshanCharm"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][4]["Id"] = 186305
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][4]["Log"] = "0,0,3001525,1,12000091,2,186305,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][4]["Index"] = "CaiZhuang"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][5]["Id"] = 186315
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][5]["Log"] = "0,0,3001525,1,12000091,2,186315,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][5]["Index"] = "TajikCostumes"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][6]["Id"] = 186325
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][6]["Log"] = "0,0,3001525,1,12000091,2,186325,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Item_1"][6]["Index"] = "HomeStyle"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][1]["Effect"] = "eidolon"
	-- 骑宠外套（7天时效）		15%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["ItemChance"] = 150
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][1]["Id"] = 200200
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][1]["Log"] = "0,0,3001525,1,12000091,2,200200,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][1]["Index"] = "DevouringTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][2]["Id"] = 200201
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][2]["Log"] = "0,0,3001525,1,12000091,2,200201,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][2]["Index"] = "PurpleIceTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][3]["Id"] = 200202
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][3]["Log"] = "0,0,3001525,1,12000091,2,200202,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][3]["Index"] = "PurpleXuanHuLan"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][4]["Id"] = 200203
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][4]["Log"] = "0,0,3001525,1,12000091,2,200203,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][4]["Index"] = "JadeTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][5]["Id"] = 200204
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][5]["Log"] = "0,0,3001525,1,12000091,2,200204,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][5]["Index"] = "InkXuanLingHu"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][6]["Id"] = 200205
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][6]["Log"] = "0,0,3001525,1,12000091,2,200205,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Item_1"][6]["Index"] = "TheTigerSpirit"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][2]["Effect"] = "eidolon"
	-- 破城火雷*1		12%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["ItemChance"] = 120
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["Item_1"] = 721261
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["Log"] = "0,0,3001525,1,12000091,2,721261,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][3]["Index"] = "BreakTheCity"
	-- 记忆宝珠*1		12%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["ItemChance"] = 120
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["Item_1"] = 720828
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["Log"] = "0,0,3001525,1,12000091,2,720828,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][4]["Index"] = "MemorySarah"
	-- 良品宝石随机*2（天地玄除外）		10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][1]["Id"] = 700042
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][1]["Log"] = "0,0,3001525,1,12000091,2,700042,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][1]["Index"] = "JinLinGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][2]["Id"] = 700032
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][2]["Log"] = "0,0,3001525,1,12000091,2,700032,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][2]["Index"] = "GreenRainbowGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][3]["Id"] = 700022
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][3]["Log"] = "0,0,3001525,1,12000091,2,700022,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][3]["Index"] = "AJewel"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][4]["Id"] = 700012
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][4]["Log"] = "0,0,3001525,1,12000091,2,700012,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][4]["Index"] = "HateDragonGems"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][5]["Id"] = 700002
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][5]["Log"] = "0,0,3001525,1,12000091,2,700002,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][5]["Index"] = "FengYinGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][6]["Id"] = 700052
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][6]["Log"] = "0,0,3001525,1,12000091,2,700052,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][6]["Index"] = "PurpleGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][7] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][7]["Id"] = 700062
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][7]["Log"] = "0,0,3001525,1,12000091,2,700062,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Item_1"][7]["Index"] = "TheMoonGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["ItemEffect"] = "0 2"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][5]["Effect"] = "eidolon"
	-- 技能宝典大礼包*1		10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["Item_1"] = 720886
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["Log"] = "0,0,3001525,1,12000091,2,720886,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][6]["Index"] = "SkillBook"
	-- 精致神魂礼包*1		8%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["ItemChance"] = 80
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["Item_1"] = 3000107
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["Log"] = "0,0,3001525,1,12000091,2,3000107,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][7]["Index"] = "DelicateSpirit"
	-- 精致神魂礼包*1		6%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["ItemChance"] = 60
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["Item_1"] = 720399
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["Log"] = "0,0,3001525,1,12000091,2,720399,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][8]["Index"] = "SeniorCuilian"
	-- 清心符*1，720128，不能换天石		5%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["ItemChance"] = 50
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["Item_1"] = 720128
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["Log"] = "0,0,3001525,1,12000091,2,720128,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][9]["Index"] = "TheHeartBreaks"
	-- 月光宝盒，没洞，721022		4%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["ItemChance"] = 40
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["Item_1"] = 721022
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["Log"] = "0,0,3001525,1,12000091,2,721022,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][10]["Index"] = "Moonlight"
	-- 小乾坤袋*1 全服限制每天出5个，超出限制给清心符，720128，不能换天石		2%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["ItemChance"] = 20
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Item_1"] = 1100003
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Log"] = "0,0,3001525,1,12000091,2,1100003,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Index"] = "QianKundai"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["GlobalId"] = 80044
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["GlobalData"] = 0
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][11]["Key"] = 9
	-- 万商名典*1 全服限制每天出5个，超出限制给月光宝盒，没洞，721022		1%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["ItemChance"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Item_1"] = 710214
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Log"] = "0,0,3001525,1,12000091,2,710214,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Index"] = "BusinessDirectory"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["GlobalId"] = 80044
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["GlobalData"] = 1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001525][12]["Key"] = 10

	-- 暑假欢笑大礼包
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526]["Space"] = 1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526]["ItemChanceSum"] = 1000
	-- 时装外套（7天时效）*1		12%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["ItemChance"] = 120
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][1]["Id"] = 185345
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][1]["Log"] = "0,0,3001526,1,12000091,2,185345,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][1]["Index"] = "MiaoStyle"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][2]["Id"] = 185365
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][2]["Log"] = "0,0,3001526,1,12000091,2,185365,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][2]["Index"] = "PrairieWind"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][3]["Id"] = 185375
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][3]["Log"] = "0,0,3001526,1,12000091,2,185375,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][3]["Index"] = "TianshanCharm"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][4]["Id"] = 186305
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][4]["Log"] = "0,0,3001526,1,12000091,2,186305,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][4]["Index"] = "CaiZhuang"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][5]["Id"] = 186315
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][5]["Log"] = "0,0,3001526,1,12000091,2,186315,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][5]["Index"] = "TajikCostumes"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][6]["Id"] = 186325
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][6]["Log"] = "0,0,3001526,1,12000091,2,186325,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Item_1"][6]["Index"] = "HomeStyle"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["ItemEffect"] = "0 1 0 0 0 0 0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][1]["Effect"] = "eidolon"
	-- 武器外套神1（7天时效）*1		12%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["ItemChance"] = 120
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["Item_1"] = 728597
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["Log"] = "0,0,3001526,1,12000091,2,728597,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][2]["Index"] = "ExclusiveCoatArms"
	-- 骑宠外套（7天时效）		12%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["ItemChance"] = 120
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][1]["Id"] = 200200
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][1]["Log"] = "0,0,3001526,1,12000091,2,200200,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][1]["Index"] = "DevouringTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][2]["Id"] = 200201
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][2]["Log"] = "0,0,3001526,1,12000091,2,200201,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][2]["Index"] = "PurpleIceTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][3]["Id"] = 200202
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][3]["Log"] = "0,0,3001526,1,12000091,2,200202,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][3]["Index"] = "PurpleXuanHuLan"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][4]["Id"] = 200203
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][4]["Log"] = "0,0,3001526,1,12000091,2,200203,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][4]["Index"] = "JadeTiger"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][5]["Id"] = 200204
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][5]["Log"] = "0,0,3001526,1,12000091,2,200204,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][5]["Index"] = "InkXuanLingHu"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][6]["Id"] = 200205
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][6]["Log"] = "0,0,3001526,1,12000091,2,200205,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Item_1"][6]["Index"] = "TheTigerSpirit"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["ItemEffect"] = "0 1 0 0 0 0 0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][3]["Effect"] = "eidolon"
	-- 杜康酒*2		10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["Item_1"] = 723030
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["ItemEffect"] = "0 2"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["Log"] = "0,0,3001526,1,12000091,2,723030,2"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][4]["Index"] = "DukangWine"
	-- 高级淬炼礼包*1		10%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["ItemChance"] = 100
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["Item_1"] = 720399
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["Log"] = "0,0,3001526,1,12000091,2,720399,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][5]["Index"] = "SeniorCuilian"
	-- 精致神魂礼包*1		8%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["ItemChance"] = 80
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["Item_1"] = 3000107
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["Log"] = "0,0,3001526,1,12000091,2,3000107,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][6]["Index"] = "DelicateSpirit"
	-- 清心符，720128，不能换天石		8%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["ItemChance"] = 80
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["Item_1"] = 720128
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["Log"] = "0,0,3001526,1,12000091,2,720128,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][7]["Index"] = "TheHeartBreaks"
	-- 枣红马+2*1  全服限制每天出8个，超出限制给骑宠外套神1		5%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["ItemChance"] = 50
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Item_1"] = 300000
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["ItemEffect"] = "0 1 150 0 16750080 0 0 0 0 0 2 0 0 0 0 0 0 0 0 255"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Log"] = "0,0,3001526,1,12000091,2,300000,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Index"] = "TheMare"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["GlobalData"] = 0
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Data"] = 8
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][8]["Key"] = 3
	-- 赤炼石+2*1  全服限制每天出8个，超出限制给骑宠外套神1		5%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["ItemChance"] = 50
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Item_1"] = 730002
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Log"] = "0,0,3001526,1,12000091,2,730002,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Index"] = "RedRockLian"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["GlobalData"] = 1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Data"] = 8
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][9]["Key"] = 3
	-- 小乾坤袋*1  全服限制每天出5个，超出限制给武器外套神1		4%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["ItemChance"] = 40
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Item_1"] = 1100003
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Log"] = "0,0,3001526,1,12000091,2,1100003,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Index"] = "QianKundai"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["GlobalData"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][10]["Key"] = 2
	-- 桃源灵玉*3  全服限制每天出10次总共30个，超出限制给武器外套神1		4%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["ItemChance"] = 40
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Item_1"] = 711504
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["ItemEffect"] = "0 3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Log"] = "0,0,3001526,1,12000091,2,711504,3"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Index"] = "TaoyuanLingYu"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["GlobalData"] = 3
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Data"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][11]["Key"] = 2
	-- 优质宝石*1，随机，天地玄除外  全服限制每天出5个，超出限制给杜康酒*1		3%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["ItemChance"] = 30
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][1]["Id"] = 700043
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][1]["Log"] = "0,0,3001526,1,12000091,2,700043,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][1]["Index"] = "JinLinGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][2]["Id"] = 700033
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][2]["Log"] = "0,0,3001526,1,12000091,2,700033,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][2]["Index"] = "GreenRainbowGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][3]["Id"] = 700023
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][3]["Log"] = "0,0,3001526,1,12000091,2,700023,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][3]["Index"] = "AJewel"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][4] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][4]["Id"] = 700013
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][4]["Log"] = "0,0,3001526,1,12000091,2,700013,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][4]["Index"] = "HateDragonGems"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][5] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][5]["Id"] = 700003
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][5]["Log"] = "0,0,3001526,1,12000091,2,700003,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][5]["Index"] = "FengYinGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][6] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][6]["Id"] = 700053
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][6]["Log"] = "0,0,3001526,1,12000091,2,700053,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][6]["Index"] = "PurpleGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][7] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][7]["Id"] = 700063
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][7]["Log"] = "0,0,3001526,1,12000091,2,700063,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Item_1"][7]["Index"] = "TheMoonGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["GlobalData"] = 4
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][12]["Key"] = 16
	-- 日常任务重置符  全服限制每天出5个，超出限制给杜康酒*1		3%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["ItemChance"] = 30
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"] = 3001407
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Log"] = "0,0,3001526,1,12000091,2,3001407,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Index"] = "Reel"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["GlobalId"] = 80045
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["GlobalData"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Key"] = 16
	-- 良品天地玄*1  全服限制每天出5个，超出限制给精致神魂礼包*1		2%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["ItemChance"] = 20
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][1] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][1]["Id"] = 700122
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][1]["Log"] = "0,0,3001526,1,12000091,2,700122,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][1]["Index"] = "LingGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][2] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][2]["Id"] = 700102
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][2]["Log"] = "0,0,3001526,1,12000091,2,700102,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][2]["Index"] = "GemOfWrath"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][3] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][3]["Id"] = 700072
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][3]["Log"] = "0,0,3001526,1,12000091,2,700072,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Item_1"][3]["Index"] = "XuanYuanGem"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["GlobalId"] = 80046
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["GlobalData"] = 0
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][13]["Key"] = 6
	-- 150点气力值礼包  全服限制每天出5个，超出限制给高级淬炼礼包*1		1%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["ItemChance"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Item_1"] = 3000063
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Log"] = "0,0,3001526,1,12000091,2,3000063,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Index"] = "Strength"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["GlobalId"] = 80046
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["GlobalData"] = 1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Data"] = 5
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][14]["Key"] = 5
	-- 龙珠*1  全服限制每天出3个，全服公告，超过限制给清心符，720128，不能换天石		1%
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["RandomItemChanceType"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["ItemChance"] = 10
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Item_1"] = 1088000
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Log"] = "0,0,3001526,1,12000091,2,1088000,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Index"] = "DragonBall"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["GlobalId"] = 80046
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["GlobalData"] = 2
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Data"] = 3
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["Key"] = 7
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][15]["SysIndex"] = "SysMsg"
	-- 杜康酒*1
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16]["Item_1"] = 723030
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16]["ItemEffect"] = "0 1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16]["Log"] = "0,0,3001526,1,12000091,2,723030,1"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16]["Effect"] = "eidolon"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3001526][16]["Index"] = "OneDukangWine"

	tSummerActive2015_ZhongGuaDeGua_RewardItem[3006619] = {}
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3006619]["Cultivation"] = 15
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3006619]["CultivationLog"] = "0,0,3006619,1,12000091,2,6,15"
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3006619]["Exp"] = 30
	tSummerActive2015_ZhongGuaDeGua_RewardItem[3006619]["ExpLog"] = "0,0,3006619,1,12000091,2,4,30"
	
	
	
--------------------------------------逻辑部分-----------------------------------------	
-- 自动寻路
function SummerActive2015_ZhongGuaDeGua_AutoPath(nNpcId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	SummerActive2015_ZhongGuaDeGua_Path(nType)
end

-- 寻路函数
function SummerActive2015_ZhongGuaDeGua_Path(nType)
	local nMapId = tSummerActive2015_ZhongGuaDeGua_AutoPath[nType]["MapId"]
	local nCellX = tSummerActive2015_ZhongGuaDeGua_AutoPath[nType]["CellX"]
	local nCellY = tSummerActive2015_ZhongGuaDeGua_AutoPath[nType]["CellY"]
	local nTargetNpcId = tSummerActive2015_ZhongGuaDeGua_AutoPath[nType]["NpcId"]
	
	Sys_GotoSomeWhere(nCellX,nCellY,nMapId,nTargetNpcId)
end

-- 判断玩家等级
function SummerActive2015_ZhongGuaDeGua_JudgeLevel(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tSummerActive2015_ZhongGuaDeGua_Constant["Level"],tSummerActive2015_ZhongGuaDeGua_Constant["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return true
	end
	
	return false
end

-- 领取西瓜种子
function SummerActive2015_ZhongGuaDeGua_RewardWatermelon(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断玩家等级
	if SummerActive2015_ZhongGuaDeGua_JudgeLevel(nNpcId) then
		return
	end
	
	-- local nEventType = tSummerActive2015_ZhongGuaDeGua_Stc["EventType"]
	-- local nDataType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][1]
	
	-- 判断是否领取过种子
	-- if not Task_ChkStcValue(nEventType,nDataType,"==",0) then
		-- 判断领取种子CD时间
		-- if not Task_StcInterval(nEventType,nDataType,tSummerActive2015_ZhongGuaDeGua_Constant["SeedTime"],2) then
			-- LinkNpcGossipFunc_New(nNpcId,"3-2")
			-- return
		-- end
	-- end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["NoBag"])
		return
	end
	
	-- 设掩码值
	-- Task_SetStatistic(nEventType,nDataType,1,1)
	-- Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 给种子
	Item_AddItem(tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemId"],0,tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemNum"])
	
	-- 打log
	Sys_SaveActionFestivalLog(tSummerActive2015_ZhongGuaDeGua_Constant["SeedLog"])
	
	-- 对白
	LinkNpcGossipFunc_New(nNpcId,"3-3")
end

-- 上交西瓜
function SummerActive2015_ZhongGuaDeGua_HandWatermelon(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断是否在可上交的时间
	if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"4-2")
end

-- 兑换积分
function SummerActive2015_ZhongGuaDeGua_ExchangeIntegral(nNpcId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断是否在可上交的时间
	if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end

	-- 判断玩家等级
	if SummerActive2015_ZhongGuaDeGua_JudgeLevel(nNpcId) then
		return
	end
	
	local nItemId = tSummerActive2015_ZhongGuaDeGua_Watermelon[nType]["ItemId"]
	
	-- 判断身上是否有西瓜
	if not Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end
	
	-- 删除物品
	if Item_DelItem(nItemId) then
		Sys_SaveActionFestivalLog(tSummerActive2015_ZhongGuaDeGua_Watermelon[nType]["Log"])
		
		-- 设掩码
		local nEventType = tSummerActive2015_ZhongGuaDeGua_Stc["EventType"]
		local nDtaType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][2]
		
		-- 判断掩码隔天
		if Task_StcInterval(nEventType,nDtaType,1,4) then
			Task_SetStatistic(nEventType,nDtaType,0,1)
		end
		
		Task_AddStatistic(nEventType,nDtaType,tSummerActive2015_ZhongGuaDeGua_Watermelon[nType]["Score"],1)
		Task_SetStcTimestamp(nEventType,nDtaType,0)
		
		-- 播光效
		User_EffectAdd("self",tSummerActive2015_ZhongGuaDeGua_Watermelon[nType]["Effect"])
		
		-- 给提示
		LinkNpcGossipFunc_New(nNpcId,tSummerActive2015_ZhongGuaDeGua_Watermelon[nType]["Index"])
		
		-- 判断与第一名的差距
		local nData = Get_UserStatisticValue(nEventType,nDtaType)
		local nGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RankGlobalId"]
		local nGlobalData = Get_SysDynaGlobalData0(nGlobalId)
		
		if nData > nGlobalData then
			local nUserId = Get_UserId()
			local sUserName = Get_UserName(nUserId)
			
			Sys_SetSynaGlobalData0(nGlobalId,nData)
			Sys_SetSynaGlobalData1(nGlobalId,nUserId)
			Sys_SetSynaGlobalDataStr1(nGlobalId,sUserName)
		end
	end
end

-- 领取奖励
function SummerActive2015_ZhongGuaDeGua_ReceiveAward(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断是否在可上交的时间
	if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"5-2")
end

-- 领取60积分奖励
function SummerActive2015_ZhongGuaDeGua_ReceiveScoreAward(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断是否在可上交的时间
	if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEventType = tSummerActive2015_ZhongGuaDeGua_Stc["EventType"]
	local nAwardType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][4]
	
	-- 判断是否领取过
	if Task_ChkStcValue(nEventType,nAwardType,">=",1) then
		-- 判断是否隔天
		if Task_StcInterval(nEventType,nAwardType,1,4) then
			Task_SetStatistic(nEventType,nAwardType,0,1)
			Task_SetStcTimestamp(nEventType,nAwardType,0)
		else
			LinkNpcGossipFunc_New(nNpcId,"5-3")
			return
		end
	end
	
	local nScoreType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][2]
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nScoreType,1,4) then
		Task_SetStatistic(nEventType,nScoreType,0,1)
		Task_SetStcTimestamp(nEventType,nScoreType,0)
	end
	
	-- 判断积分是否大于60分
	if Task_ChkStcValue(nEventType,nScoreType,"<",tSummerActive2015_ZhongGuaDeGua_Constant["RewardData"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-4")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["NoBag"])
		return
	end
	
	-- 设掩码
	Task_SetStatistic(nEventType,nAwardType,1,1)
	Task_SetStcTimestamp(nEventType,nAwardType,0)
	
	-- 给奖励
	FestivalGeneralPackage_GetGift(tSummerActive2015_ZhongGuaDeGua_Constant["FestivalId"],tSummerActive2015_ZhongGuaDeGua_Constant["LogId"])
	
	-- 打log
	-- Sys_SaveActionFestivalLog(string.format(tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"]["Log"],nItemId))
	-- 播光效
	User_EffectAdd("self","fam_gain_special")
	-- 给提示
	LinkNpcGossipFunc_New(nNpcId,"5-5")
end

-- 领取超级大奖
function SummerActive2015_ZhongGuaDeGua_ReceiveGrandPrize(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ReceiveTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断是否是最后一天
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["EndTime"]) then
		if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
			LinkNpcGossipFunc_New(nNpcId,"5-1")
			return
		end
	end
	
	-- 判断是否是第一名玩家
	local nUserId = Get_UserId()
	local nGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RewardGlobalId"]
	local nFirstUserId = Get_SysDynaGlobalData1(nGlobalId)
	
	if nUserId ~= nFirstUserId then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 是否已经领取过了
	local nGlobalData = Get_SysDynaGlobalData0(nGlobalId)
	
	if nGlobalData ~= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tSummerActive2015_ZhongGuaDeGua_Constant["SuperRewardSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end

	-- 设掩码
	Sys_SetSynaGlobalData0(nGlobalId,1)
	-- 给物品
	for i,v in pairs (tSummerActive2015_ZhongGuaDeGua_Constant["SuperReward"]) do
		Item_AddItem(v["ItemId"],0,v["ItemNum"])
	end
	-- 打log
	Sys_SaveActionFestivalLog(tSummerActive2015_ZhongGuaDeGua_Constant["SuperRewardLog"])
	-- 播光效
	User_EffectAdd("self","zf2-e129")
	-- 给提示
	local sUserName = Get_UserName(nUserId)
	local sContent = string.format(tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["RewardItem"],sUserName)
	Sys_SystemBroadcast(sContent)
	LinkNpcGossipFunc_New(nNpcId,"2-5")
end

-- 查询积分
function SummerActive2015_ZhongGuaDeGua_QueryScore(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	local nEventType = tSummerActive2015_ZhongGuaDeGua_Stc["EventType"]
	local nDataType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][2]
	
	-- 判断是否隔天
	if Task_StcInterval(nEventType,nDataType,1,4) then
		Task_SetStatistic(nEventType,nDataType,0,1)
		Task_SetStcTimestamp(nEventType,nDataType,0)
	end
	
	-- 判断今天有没有上交西瓜
	if Task_ChkStcValue(nEventType,nDataType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"5-6")
		return
	end
	
	local nData = Get_UserStatisticValue(nEventType,nDataType)
	-- 判断是否是第一名玩家
	local nUserId = Get_UserId()
	local nGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RankGlobalId"]
	local nFirstUserId = Get_SysDynaGlobalData1(nGlobalId)
	local sText = ""
	local sOption = ""
	
	if nUserId == nFirstUserId then
		sText = string.format(tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["571"],nData)
		sOption = tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["Option42"]
	else
		sText = string.format(tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["581"],nData)
		sOption = tSummerActive2015_ZhongGuaDeGua_Text[nNpcId]["Option43"]
	end
	
	Sys_DialogText(sText)
	Sys_DialogOption(sOption)
	Sys_DialogFace()
	Sys_DialogEnd()
end

-- 赋值和清动态码
function SummerActive2015_ZhongGuaDeGua_Assignment()
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["AssignmentTime"]) then
		return
	end
	
	local nRankGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RankGlobalId"]
	local nRewardGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RewardGlobalId"]
	local nData2 = Get_SysDynaGlobalData2(nRankGlobalId)
	
	if Sys_ChkDayTime("00:00 00:29") then
		if nData2 == 0 then
			local nData1 = Get_SysDynaGlobalData1(nRankGlobalId)
			local sData1 = Get_SysDynaGlobalDataStr1(nRankGlobalId)
			
			Sys_SetSynaGlobalData0(nRewardGlobalId,0)
			Sys_SetSynaGlobalData1(nRewardGlobalId,nData1)
			Sys_SetSynaGlobalDataStr1(nRewardGlobalId,sData1)
			
			Sys_SetSynaGlobalData0(nRankGlobalId,0)
			Sys_SetSynaGlobalData1(nRankGlobalId,0)
			Sys_SetSynaGlobalData2(nRankGlobalId,1)
			Sys_SetSynaGlobalDataStr1(nRankGlobalId,"")
		end
	elseif nData2 == 1 then
		Sys_SetSynaGlobalData2(nRankGlobalId,0)
	end
end

-- 使用西瓜种子
function SummerActive2015_ZhongGuaDeGua_UseItem(nItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tSummerActive2015_ZhongGuaDeGua_Constant["Level"],tSummerActive2015_ZhongGuaDeGua_Constant["Metempsychosis"]) then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["Level"])
		return
	end
	
	-- 判断玩家地图
	local nMapId = Get_UserMapId()
	local nCellX = Get_UserPositionX()
	local nCellY = Get_UserPositionY()

	if nMapId ~= tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MapId"] or
		nCellX < tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MinCellX"] or nCellX > tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MaxCellX"] or
		nCellY < tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MinCellY"] or nCellY > tSummerActive2015_ZhongGuaDeGua_UseWatermelon["MaxCellY"] then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["Range"],string.format("SummerActive2015_ZhongGuaDeGua_Path</N>%d",8))
		return
	end

	local nSecs = tSummerActive2015_ZhongGuaDeGua_UseWatermelon["Second"]
	local nActionId = tSummerActive2015_ZhongGuaDeGua_UseWatermelon["Action"]
	local sContent = tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["Read"]
	local sFunc = string.format("SummerActive2015_ZhongGuaDeGua_UseWatermelon</N>%d",nItemId)
	
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end

function SummerActive2015_ZhongGuaDeGua_UseWatermelon(nItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["NoSpace"])
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nFlat,tAward = Probabil_RandomAward(tSummerActive2015_ZhongGuaDeGua_Chance,nItemId)
		local nAwardItemId = tAward[1]["tAward"][1]["Item_1"]
		local bAward = false
		
		-- 5%几率种金币
		if nAwardItemId == 1 then
			local nEventType = tSummerActive2015_ZhongGuaDeGua_Stc["EventType"]
			local nDataType = tSummerActive2015_ZhongGuaDeGua_Stc["DataType"][3]
			
			if Task_ChkStcValue(nEventType,nDataType,"==",0) or Task_StcInterval(nEventType,nDataType,1,4) then
				local nAddMoney = tAward[1]["tAward"][1]["Money"]
				
				-- 判断金币上限
				if User_CanPutMoney2Bag(nAddMoney) then
					-- 设掩码
					Task_SetStatistic(nEventType,nDataType,1,1)
					Task_SetStcTimestamp(nEventType,nDataType,0)
					
					-- 给金币
					User_AddMoney(nAddMoney)
					
					bAward = true
				else
					tAward[1]["tAward"][1] = tSummerActive2015_ZhongGuaDeGua_Chance[nItemId][2]
				end
			else
				tAward[1]["tAward"][1] = tSummerActive2015_ZhongGuaDeGua_Chance[nItemId][2]
			end
		end
		
		-- 给物品
		if bAward ~= true then
			nAwardItemId = tAward[1]["tAward"][1]["Item_1"]
			
			Item_AddItem(nAwardItemId)
		end

		-- 打log
		Sys_SaveActionFestivalLog(tAward[1]["tAward"][1]["Log"])
		-- 播光效
		--User_EffectAdd("self",tAward[1]["tAward"][1]["Effect"])
		-- 给提示
		User_TalkChannel2005(tSummerActive2015_ZhongGuaDeGua_Text[nItemId][tAward[1]["tAward"][1]["Index"]])
	end
end
	
-- 怪物掉落
function SummerActive2015_ZhongGuaDeGua_KillMonster(nMonsterTypeId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		return
	end
	
	local nLevel = Get_UserLevel()
	
	if nLevel >= tSummerActive2015_ZhongGuaDeGua_Monster[nMonsterTypeId]["Level"] then
		return
	end
	
	local nRandom = math.random(1,100)
	
	if nRandom <= 2 then
		-- 判断背包空间
		if not User_CheckLeftSpace(1) then
			return
		end
		
		Item_AddItem(tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemId"])
		Sys_SaveActionFestivalLog(string.format(tSummerActive2015_ZhongGuaDeGua_Constant["RewardItem"]["Log"],tSummerActive2015_ZhongGuaDeGua_Constant["SeedItemId"]))
		User_EffectAdd("self","hitstar")
		User_TalkChannel2005(tSummerActive2015_ZhongGuaDeGua_Text["KillMonster"])
	end
end

-- 礼包使用
function SummerActive2015_ZhongGuaDeGua_UsePackage(nItemId)
	-- 判断背包空间
	local nSpace = tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId]["Space"]
	if nSpace ~= nil and (not User_CheckLeftSpace(nSpace)) then
		Sys_MsgBox(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["NoSpace"])
		return
	end

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nFlat,tAward = Probabil_RandomAward(tSummerActive2015_ZhongGuaDeGua_RewardItem,nItemId)
		local nGlobalId = tAward[1]["tAward"][1]["GlobalId"]
		
		-- 判断是否有全服限制
		if nGlobalId ~= nil then
			local nGlobalData = tAward[1]["tAward"][1]["GlobalData"]
			local nMaxData = tAward[1]["tAward"][1]["Data"]
			local nData = Get_SysDynaGlobalData(nGlobalId,nGlobalData)
			local nKey = tAward[1]["tAward"][1]["Key"]
			
			if nData < nMaxData then
				Sys_SetSynaGlobalData(nGlobalId,nGlobalData,nData + 1)
			else
				tAward[1]["tAward"][1] = tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId][nKey]
			end
		end

		local nAwardItemId = tAward[1]["tAward"][1]["Item_1"]
		local sLog = ""
		local sMsg = ""
		local nGetItemId = 0
		
		-- 判断是否还要随机给物品
		if type(nAwardItemId) == "table" then
			local nRandom = math.random(1,#nAwardItemId)
			nGetItemId = nAwardItemId[nRandom]["Id"]
			sLog = nAwardItemId[nRandom]["Log"]
			sMsg = tSummerActive2015_ZhongGuaDeGua_Text[nItemId][nAwardItemId[nRandom]["Index"]]
		else
			nGetItemId = nAwardItemId
			sLog = tAward[1]["tAward"][1]["Log"]
			sMsg = tSummerActive2015_ZhongGuaDeGua_Text[nItemId][tAward[1]["tAward"][1]["Index"]]
		end
		
		-- 给奖励
		Item_AddNewItem(nGetItemId,tAward[1]["tAward"][1]["ItemEffect"])
		Sys_SaveActionFestivalLog(sLog)
		User_EffectAdd("self",tAward[1]["tAward"][1]["Effect"])
		Sys_MsgBox(sMsg)
		
		if tAward[1]["tAward"][1]["SysIndex"] ~= nil then
			local sContent = string.format(tSummerActive2015_ZhongGuaDeGua_Text[nRandom][tAward[1]["tAward"][1]["SysIndex"]],Get_UserName())
			Sys_SystemBroadcast(sContent)
		end
	end
end

-- 礼包动态掩码清除
function SummerActive2015_ZhongGuaDeGua_ItemGlobalRest()
	local nGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][1]
	local nData = Get_SysDynaGlobalData2(nGlobalId)

	if Sys_ChkDayTime("00:00 00:29") then
		if nData == 0 then
			Sys_SetSynaGlobalData0(nGlobalId,0)
			Sys_SetSynaGlobalData1(nGlobalId,0)
			Sys_ResetAllSynaGlobalData(tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][2])
			Sys_ResetAllSynaGlobalData(tSummerActive2015_ZhongGuaDeGua_Constant["ItemGlobal"][3])
			Sys_SetSynaGlobalData2(nGlobalId,1)
		end
	elseif nData == 1 then
		Sys_SetSynaGlobalData2(nGlobalId,0)
	end
end

-- 夏日冰饮使用
function SummerActive2015_ZhongGuaDeGua_IceDrink(nItemId,nType)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["BeOverdue"])
		end
		
		return
	end

	if nType == 1 then
		SummerActive2015_ZhongGuaDeGua_Path(9)
	elseif Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nLev = Get_UserLevel()
		local sContent = ""
		local sLog = ""
		
		if nLev >= 140 then
			User_AddCultivation(tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId]["Cultivation"])
			sContent = tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["RewardCultivation"]
			sLog = tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId]["CultivationLog"]
		else
			User_AddExpTime(tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId]["Exp"])
			sContent = tSummerActive2015_ZhongGuaDeGua_Text[nItemId]["RewardExp"]
			sLog = tSummerActive2015_ZhongGuaDeGua_RewardItem[nItemId]["ExpLog"]
		end

		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 西瓜太郎
tNpcFace[2494] = 68
tNpcGossip[18510] = tNpcGossip[18510] or DefaultNpc:new{}
tNpcGossip[18510]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[18510]["Text1-1"] = {111,112,113}
tNpcGossip[18510]["Text111"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["111"]
tNpcGossip[18510]["Text112"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["112"]
tNpcGossip[18510]["Text113"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["113"]
tNpcGossip[18510]["tOption1-1"] = {1}
tNpcGossip[18510]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["BeforeActivityTime"])
end

-- 活动中	00:00 22:59
tNpcGossip[18510]["Text1-2"] = {121,122,123}
tNpcGossip[18510]["Text121"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["121"]
tNpcGossip[18510]["Text122"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["122"]
tNpcGossip[18510]["Text123"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["123"]
tNpcGossip[18510]["tOption1-2"] = {2,3,4,5,6,7}
tNpcGossip[18510]["ChkFunc1-2"] = function ()
	if Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		if Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
			return true
		end
	end
	
	return false
end

-- 活动中	23点
tNpcGossip[18510]["Text1-3"] = {131,132,133}
tNpcGossip[18510]["Text131"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["131"]
tNpcGossip[18510]["Text132"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["132"]
tNpcGossip[18510]["Text133"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["133"]
tNpcGossip[18510]["tOption1-3"] = {8,9,10,11}
tNpcGossip[18510]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"]) then
		if not Sys_ChkDayTime(tSummerActive2015_ZhongGuaDeGua_Constant["HandTime"]) then
			return true
		end
	end
	
	return false
end

-- 活动后
tNpcGossip[18510]["Text1-4"] = {141,142,143}
tNpcGossip[18510]["Text141"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["141"]
tNpcGossip[18510]["Text142"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["142"]
tNpcGossip[18510]["Text143"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["143"]
tNpcGossip[18510]["tOption1-4"] = {12,13}

-- 已经结束
tNpcGossip[18510]["Text2-1"] = {211}
tNpcGossip[18510]["Text211"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["211"]
tNpcGossip[18510]["tOption2-1"] = {14}

-- 不是第一名玩家
tNpcGossip[18510]["Text2-2"] = {221}
tNpcGossip[18510]["Text221"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["221"]
tNpcGossip[18510]["tOption2-2"] = {15}

-- 领取过了
tNpcGossip[18510]["Text2-3"] = {231}
tNpcGossip[18510]["Text231"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["231"]
tNpcGossip[18510]["tOption2-3"] = {16}

-- 空间满
tNpcGossip[18510]["Text2-4"] = {241}
tNpcGossip[18510]["Text241"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["241"]
tNpcGossip[18510]["tOption2-4"] = {17}

-- 获得对白
tNpcGossip[18510]["Text2-5"] = {251}
tNpcGossip[18510]["Text251"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["251"]
tNpcGossip[18510]["tOption2-5"] = {18}

-- 等级不足
tNpcGossip[18510]["Text3-1"] = {311}
tNpcGossip[18510]["Text311"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["311"]
tNpcGossip[18510]["tOption3-1"] = {19}

-- cd
tNpcGossip[18510]["Text3-2"] = {321}
tNpcGossip[18510]["Text321"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["321"]
tNpcGossip[18510]["tOption3-2"] = {20}

-- 给西瓜种子
tNpcGossip[18510]["Text3-3"] = {331}
tNpcGossip[18510]["Text331"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["331"]
tNpcGossip[18510]["tOption3-3"] = {21}

-- 不在规定时间
tNpcGossip[18510]["Text4-1"] = {411}
tNpcGossip[18510]["Text411"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["411"]
tNpcGossip[18510]["tOption4-1"] = {22}

tNpcGossip[18510]["Text4-2"] = {421}
tNpcGossip[18510]["Text421"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["421"]
tNpcGossip[18510]["tOption4-2"] = {23,24,25,26}

-- 没有西瓜
tNpcGossip[18510]["Text4-3"] = {431}
tNpcGossip[18510]["Text431"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["431"]
tNpcGossip[18510]["tOption4-3"] = {27}

tNpcGossip[18510]["Text4-4"] = {441}
tNpcGossip[18510]["Text441"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["441"]
tNpcGossip[18510]["tOption4-4"] = {28,29}

tNpcGossip[18510]["Text4-5"] = {451}
tNpcGossip[18510]["Text451"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["451"]
tNpcGossip[18510]["tOption4-5"] = {30,31}

tNpcGossip[18510]["Text4-6"] = {461}
tNpcGossip[18510]["Text461"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["461"]
tNpcGossip[18510]["tOption4-6"] = {32,33}

tNpcGossip[18510]["Text5-1"] = {511}
tNpcGossip[18510]["Text511"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["511"]
tNpcGossip[18510]["tOption5-1"] = {34}

tNpcGossip[18510]["Text5-2"] = {521}
tNpcGossip[18510]["Text521"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["521"]
tNpcGossip[18510]["tOption5-2"] = {35,36,37}

-- 今天已经领过奖了
tNpcGossip[18510]["Text5-3"] = {531}
tNpcGossip[18510]["Text531"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["531"]
tNpcGossip[18510]["tOption5-3"] = {38}

-- 分数不足
tNpcGossip[18510]["Text5-4"] = {541}
tNpcGossip[18510]["Text541"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["541"]
tNpcGossip[18510]["tOption5-4"] = {39}

tNpcGossip[18510]["Text5-5"] = {551}
tNpcGossip[18510]["Text551"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["551"]
tNpcGossip[18510]["tOption5-5"] = {40}

tNpcGossip[18510]["Text5-6"] = {561}
tNpcGossip[18510]["Text561"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["561"]
tNpcGossip[18510]["tOption5-6"] = {41}

-- 第一
tNpcGossip[18510]["Text5-7"] = {571}
tNpcGossip[18510]["Text571"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["571"]
tNpcGossip[18510]["tOption5-7"] = {42}

-- 不是第一
tNpcGossip[18510]["Text5-8"] = {581}
tNpcGossip[18510]["Text581"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["581"]
tNpcGossip[18510]["tOption5-8"] = {43}

-- 我要了解更多。
tNpcGossip[18510]["Text6-1"] = {611,612,613,614}
tNpcGossip[18510]["Text611"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["611"]
tNpcGossip[18510]["Text612"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["612"]
tNpcGossip[18510]["Text613"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["613"]
tNpcGossip[18510]["Text614"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["614"]
tNpcGossip[18510]["tOption6-1"] = {44,45,46}

tNpcGossip[18510]["Text7-1"] = {711,712,713,714}
tNpcGossip[18510]["Text711"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["711"]
tNpcGossip[18510]["Text712"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["712"]
tNpcGossip[18510]["Text713"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["713"]
tNpcGossip[18510]["Text714"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["714"]
tNpcGossip[18510]["tOption7-1"] = {47,48}

-- 选项
tNpcGossip[18510]["Option1"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option1"]
tNpcGossip[18510]["Option2"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option2"]
tNpcGossip[18510]["OptionFunc2"]="SummerActive2015_ZhongGuaDeGua_RewardWatermelon</N>18510"
tNpcGossip[18510]["Option3"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option3"]
tNpcGossip[18510]["OptionFunc3"]="SummerActive2015_ZhongGuaDeGua_HandWatermelon</N>18510"
tNpcGossip[18510]["Option4"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option4"]
tNpcGossip[18510]["OptionFunc4"]="SummerActive2015_ZhongGuaDeGua_ReceiveAward</N>18510"
tNpcGossip[18510]["Option5"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option5"]
tNpcGossip[18510]["OptionFunc5"]="SummerActive2015_ZhongGuaDeGua_QueryScore</N>18510"
tNpcGossip[18510]["Option6"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option6"]
tNpcGossip[18510]["OptionPoint6"]="6"
tNpcGossip[18510]["Option7"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option7"]
tNpcGossip[18510]["Option8"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option8"]
tNpcGossip[18510]["OptionFunc8"]="SummerActive2015_ZhongGuaDeGua_RewardWatermelon</N>18510"
tNpcGossip[18510]["Option9"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option9"]
tNpcGossip[18510]["OptionFunc9"]="SummerActive2015_ZhongGuaDeGua_QueryScore</N>18510"
tNpcGossip[18510]["Option10"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option10"]
tNpcGossip[18510]["OptionPoint10"]="6"
tNpcGossip[18510]["Option11"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option11"]
tNpcGossip[18510]["Option12"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option12"]
tNpcGossip[18510]["OptionFunc12"]="SummerActive2015_ZhongGuaDeGua_ReceiveGrandPrize</N>18510"
tNpcGossip[18510]["OptionChkFunc12"] = function ()
	if Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["EndTime"]) then
		local nUserId = Get_UserId()
		local nGlobalId = tSummerActive2015_ZhongGuaDeGua_Constant["RewardGlobalId"]
		local nFirstUserId = Get_SysDynaGlobalData1(nGlobalId)
		
		if nUserId == nFirstUserId then
			return true
		end
	end
	
	return false
end
tNpcGossip[18510]["Option13"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option13"]
tNpcGossip[18510]["Option14"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option14"]
tNpcGossip[18510]["Option15"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option15"]
tNpcGossip[18510]["Option16"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option16"]
tNpcGossip[18510]["Option17"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option17"]
tNpcGossip[18510]["Option18"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option18"]
tNpcGossip[18510]["Option19"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option19"]
tNpcGossip[18510]["Option20"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option20"]
tNpcGossip[18510]["Option21"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option21"]
tNpcGossip[18510]["Option22"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option22"]
tNpcGossip[18510]["Option23"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option23"]
tNpcGossip[18510]["OptionFunc23"]="SummerActive2015_ZhongGuaDeGua_ExchangeIntegral</N>18510</N>1"
tNpcGossip[18510]["Option24"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option24"]
tNpcGossip[18510]["OptionFunc24"]="SummerActive2015_ZhongGuaDeGua_ExchangeIntegral</N>18510</N>2"
tNpcGossip[18510]["Option25"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option25"]
tNpcGossip[18510]["OptionFunc25"]="SummerActive2015_ZhongGuaDeGua_ExchangeIntegral</N>18510</N>3"
tNpcGossip[18510]["Option26"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option26"]
tNpcGossip[18510]["Option27"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option27"]
tNpcGossip[18510]["Option28"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option28"]
tNpcGossip[18510]["OptionFunc28"]="SummerActive2015_ZhongGuaDeGua_HandWatermelon</N>18510"
tNpcGossip[18510]["Option29"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option29"]
tNpcGossip[18510]["Option30"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option30"]
tNpcGossip[18510]["OptionFunc30"]="SummerActive2015_ZhongGuaDeGua_HandWatermelon</N>18510"
tNpcGossip[18510]["Option31"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option31"]
tNpcGossip[18510]["Option32"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option32"]
tNpcGossip[18510]["OptionFunc32"]="SummerActive2015_ZhongGuaDeGua_HandWatermelon</N>18510"
tNpcGossip[18510]["Option33"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option33"]
tNpcGossip[18510]["Option34"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option34"]
tNpcGossip[18510]["Option35"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option35"]
tNpcGossip[18510]["OptionFunc35"] = "SummerActive2015_ZhongGuaDeGua_ReceiveScoreAward</N>18510"
tNpcGossip[18510]["Option36"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option36"]
tNpcGossip[18510]["OptionFunc36"] = "SummerActive2015_ZhongGuaDeGua_ReceiveGrandPrize</N>18510"
tNpcGossip[18510]["OptionChkFunc36"] = function ()
	return Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ReceiveTime"])
end
tNpcGossip[18510]["Option37"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option37"]
tNpcGossip[18510]["Option38"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option38"]
tNpcGossip[18510]["Option39"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option39"]
tNpcGossip[18510]["Option40"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option40"]
tNpcGossip[18510]["Option41"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option41"]
tNpcGossip[18510]["Option42"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option42"]
tNpcGossip[18510]["Option43"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option43"]
tNpcGossip[18510]["Option44"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option44"]
tNpcGossip[18510]["OptionPoint44"]="7"
tNpcGossip[18510]["Option45"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option45"]
tNpcGossip[18510]["OptionPoint45"]="1"
tNpcGossip[18510]["Option46"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option46"]
tNpcGossip[18510]["Option47"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option47"]
tNpcGossip[18510]["OptionFunc47"]="SummerActive2015_ZhongGuaDeGua_RewardWatermelon</N>18510"
tNpcGossip[18510]["Option48"] = tSummerActive2015_ZhongGuaDeGua_Text[18510]["Option48"]
tNpcGossip[18510]["OptionPoint48"]="1"

-- 暑假欢笑大使
tNpcFace[2495] = 159
tNpcGossip[18511] = tNpcGossip[18511] or DefaultNpc:new{}
tNpcGossip[18511]["OptionHidden"] = 1

-- 活动前
tNpcGossip[18511]["Text1-1"] = {111,112,113}
tNpcGossip[18511]["Text111"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["111"]
tNpcGossip[18511]["Text112"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["112"]
tNpcGossip[18511]["Text113"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["113"]
tNpcGossip[18511]["tOption1-1"] = {1}
tNpcGossip[18511]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["BeforeActivityTime"])
end

-- 活动期间
tNpcGossip[18511]["Text1-2"] = {121,122}
tNpcGossip[18511]["Text121"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["121"]
tNpcGossip[18511]["Text122"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["122"]
tNpcGossip[18511]["tOption1-2"] = {2,3,4,5,6,7,8,9}
tNpcGossip[18511]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tSummerActive2015_ZhongGuaDeGua_Constant["ActivityTime"])
end

-- 活动后
tNpcGossip[18511]["Text1-3"] = {131,132}
tNpcGossip[18511]["Text131"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["131"]
tNpcGossip[18511]["Text132"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["132"]
tNpcGossip[18511]["tOption1-3"] = {10}

-- 活动：追缉无影盗贼团。
tNpcGossip[18511]["Text2-1"] = {211,212}
tNpcGossip[18511]["Text211"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["211"]
tNpcGossip[18511]["Text212"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["212"]
tNpcGossip[18511]["tOption2-1"] = {11,12}

-- 活动：魔术大师。
tNpcGossip[18511]["Text3-1"] = {311,312}
tNpcGossip[18511]["Text311"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["311"]
tNpcGossip[18511]["Text312"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["312"]
tNpcGossip[18511]["tOption3-1"] = {13,14}

-- 活动：无畏勇者。
tNpcGossip[18511]["Text4-1"] = {411,412}
tNpcGossip[18511]["Text411"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["411"]
tNpcGossip[18511]["Text412"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["412"]
tNpcGossip[18511]["tOption4-1"] = {15,16}

-- 活动：种瓜得瓜。
tNpcGossip[18511]["Text5-1"] = {511,512}
tNpcGossip[18511]["Text511"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["511"]
tNpcGossip[18511]["Text512"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["512"]
tNpcGossip[18511]["tOption5-1"] = {17,18}

-- 活动：冰镇西瓜。
tNpcGossip[18511]["Text6-1"] = {611,612}
tNpcGossip[18511]["Text611"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["611"]
tNpcGossip[18511]["Text612"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["612"]
tNpcGossip[18511]["tOption6-1"] = {19,20}

-- 活动：防晒大测验。
tNpcGossip[18511]["Text7-1"] = {711,712}
tNpcGossip[18511]["Text711"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["711"]
tNpcGossip[18511]["Text712"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["712"]
tNpcGossip[18511]["tOption7-1"] = {21,22}

-- 活动：蓝桔梗冰淇淋。
tNpcGossip[18511]["Text8-1"] = {811,812}
tNpcGossip[18511]["Text811"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["811"]
tNpcGossip[18511]["Text812"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["812"]
tNpcGossip[18511]["tOption8-1"] = {23,24}

-- 选项
tNpcGossip[18511]["Option1"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option1"]
tNpcGossip[18511]["Option2"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option2"]
tNpcGossip[18511]["OptionPoint2"]="2"
tNpcGossip[18511]["Option3"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option3"]
tNpcGossip[18511]["OptionPoint3"]="3"
tNpcGossip[18511]["Option4"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option4"]
tNpcGossip[18511]["OptionPoint4"]="4"
tNpcGossip[18511]["Option5"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option5"]
tNpcGossip[18511]["OptionPoint5"]="5"
tNpcGossip[18511]["Option6"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option6"]
tNpcGossip[18511]["OptionPoint6"]="6"
tNpcGossip[18511]["Option7"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option7"]
tNpcGossip[18511]["OptionPoint7"]="7"
tNpcGossip[18511]["Option8"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option8"]
tNpcGossip[18511]["OptionPoint8"]="8"
tNpcGossip[18511]["Option9"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option9"]
tNpcGossip[18511]["Option10"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option10"]
tNpcGossip[18511]["Option11"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option11"]
tNpcGossip[18511]["OptionFunc11"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>1"
tNpcGossip[18511]["Option12"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option12"]
tNpcGossip[18511]["OptionPoint12"]="1"
tNpcGossip[18511]["Option13"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option13"]
tNpcGossip[18511]["OptionFunc13"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>2"
tNpcGossip[18511]["Option14"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option14"]
tNpcGossip[18511]["OptionPoint14"]="1"
tNpcGossip[18511]["Option15"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option15"]
tNpcGossip[18511]["OptionFunc15"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>3"
tNpcGossip[18511]["Option16"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option16"]
tNpcGossip[18511]["OptionPoint16"]="1"
tNpcGossip[18511]["Option17"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option17"]
tNpcGossip[18511]["OptionFunc17"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>4"
tNpcGossip[18511]["Option18"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option18"]
tNpcGossip[18511]["OptionPoint18"]="1"
tNpcGossip[18511]["Option19"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option19"]
tNpcGossip[18511]["OptionFunc19"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>5"
tNpcGossip[18511]["Option20"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option20"]
tNpcGossip[18511]["OptionPoint20"]="1"
tNpcGossip[18511]["Option21"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option21"]
tNpcGossip[18511]["OptionFunc21"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>6"
tNpcGossip[18511]["Option22"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option22"]
tNpcGossip[18511]["OptionPoint22"]="1"
tNpcGossip[18511]["Option23"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option23"]
tNpcGossip[18511]["OptionFunc23"]="SummerActive2015_ZhongGuaDeGua_AutoPath</N>18511</N>7"
tNpcGossip[18511]["Option24"] = tSummerActive2015_ZhongGuaDeGua_Text[18511]["Option24"]
tNpcGossip[18511]["OptionPoint24"]="1"


-- 西瓜种子
tItem[3001503] = tItem[3001503] or {}
tItem[3001503]["Function"] = function(nItemId,sItemName)
	SummerActive2015_ZhongGuaDeGua_UseItem(nItemId)
end

-- 暑假欢笑大礼包
tItem[3001524] = tItem[3001524] or {}
tItem[3001524]["Function"] = function(nItemId,sItemName)
	SummerActive2015_ZhongGuaDeGua_UsePackage(nItemId)
end

-- 暑假欢笑大礼包
tItem[3001525] = tItem[3001525] or {}
tItem[3001525]["Function"] = function(nItemId,sItemName)
	SummerActive2015_ZhongGuaDeGua_UsePackage(nItemId)
end

-- 暑假欢笑大礼包
tItem[3001526] = tItem[3001526] or {}
tItem[3001526]["Function"] = function(nItemId,sItemName)
	SummerActive2015_ZhongGuaDeGua_UsePackage(nItemId)
end

-- 夏日冰饮
tItem[3006619] = tItem[3006619] or {}
tItem[3006619]["Text1-1"] = {111,112,113,114}
tItem[3006619]["Text111"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["111"]
tItem[3006619]["Text112"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["112"]
tItem[3006619]["Text113"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["113"]
tItem[3006619]["Text114"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["114"]
tItem[3006619]["tOption1-1"] = {1,2}

tItem[3006619]["Option1"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["Option1"]
tItem[3006619]["OptionFunc1"]="SummerActive2015_ZhongGuaDeGua_IceDrink</N>3006619</N>1"
tItem[3006619]["Option2"] = tSummerActive2015_ZhongGuaDeGua_Text[3006619]["Option2"]
tItem[3006619]["OptionFunc2"]="SummerActive2015_ZhongGuaDeGua_IceDrink</N>3006619</N>2"

--------------------------------------怪物掉落-------------------------------------------
-- 第一片区
-- 	1	叫天鸡	9593200
-- tMonster[1] = tMonster[1] or {}
-- tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
-- table.insert(tMonster[1]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

-- 	2	斑鸠王	9593210
-- tMonster[2] = tMonster[2] or {}
-- tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
-- table.insert(tMonster[2]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	3	罗罗鸟	9593220
-- tMonster[3] = tMonster[3] or {}
-- tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
-- table.insert(tMonster[3]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	4	幽冥鬼斧王	9593230
-- tMonster[4] = tMonster[4] or {}
-- tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
-- table.insert(tMonster[4]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	5	蹑空鬼斧王	9593240
-- tMonster[5] = tMonster[5] or {}
-- tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
-- table.insert(tMonster[5]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)


-- 第二片区
--	6	翼蛇	9593250
-- tMonster[6] = tMonster[6] or {}
-- tMonster[6]["tFunction"] = tMonster[6]["tFunction"] or {}
-- table.insert(tMonster[6]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	7	土匪	9593260
-- tMonster[7] = tMonster[7] or {}
-- tMonster[7]["tFunction"] = tMonster[7]["tFunction"] or {}
-- table.insert(tMonster[7]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	8	火鼠	9593270
-- tMonster[8] = tMonster[8] or {}
-- tMonster[8]["tFunction"] = tMonster[8]["tFunction"] or {}
-- table.insert(tMonster[8]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	9	火精灵	9593280
-- tMonster[9] = tMonster[9] or {}
-- tMonster[9]["tFunction"] = tMonster[9]["tFunction"] or {}
-- table.insert(tMonster[9]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	66	精悍土匪	9593290
-- tMonster[66] = tMonster[66] or {}
-- tMonster[66]["tFunction"] = tMonster[66]["tFunction"] or {}
-- table.insert(tMonster[66]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	67	尖牙火鼠	9593300
-- tMonster[67] = tMonster[67] or {}
-- tMonster[67]["tFunction"] = tMonster[67]["tFunction"] or {}
-- table.insert(tMonster[67]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)


-- 第三片区
--	10	须猕猴	9593310
-- tMonster[10] = tMonster[10] or {}
-- tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
-- table.insert(tMonster[10]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	11	巨臂猿	9593320
-- tMonster[11] = tMonster[11] or {}
-- tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
-- table.insert(tMonster[11]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	12	天雷巨猿	9593330
-- tMonster[12] = tMonster[12] or {}
-- tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
-- table.insert(tMonster[12]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	13	蛇人	9593340
-- tMonster[13] = tMonster[13] or {}
-- tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
-- table.insert(tMonster[13]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)


-- 第四片区
--	14	沙怪	9593350
-- tMonster[14] = tMonster[14] or {}
-- tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
-- table.insert(tMonster[14]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	15	锤山怪	9593360
-- tMonster[15] = tMonster[15] or {}
-- tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
-- table.insert(tMonster[15]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	16	巨石怪	9593370
-- tMonster[16] = tMonster[16] or {}
-- tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
-- table.insert(tMonster[16]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	17	鬼刃	9593380
-- tMonster[17] = tMonster[17] or {}
-- tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
-- table.insert(tMonster[17]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	73	砾沙怪	9593390
-- tMonster[73] = tMonster[73] or {}
-- tMonster[73]["tFunction"] = tMonster[73]["tFunction"] or {}
-- table.insert(tMonster[73]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)


-- 第五片区
--	18	金臂鸟人	4081200
-- tMonster[18] = tMonster[18] or {}
-- tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
-- table.insert(tMonster[18]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	19	银羽鹰王	4081254
-- tMonster[19] = tMonster[19] or {}
-- tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
-- table.insert(tMonster[19]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	55	湖岛强匪	4081258
-- tMonster[55] = tMonster[55] or {}
-- tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
-- table.insert(tMonster[55]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	78	银羽鹰魔	4081255
-- tMonster[78] = tMonster[78] or {}
-- tMonster[78]["tFunction"] = tMonster[78]["tFunction"] or {}
-- table.insert(tMonster[78]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	79	湖岛悍匪	4081259
-- tMonster[79] = tMonster[79] or {}
-- tMonster[79]["tFunction"] = tMonster[79]["tFunction"] or {}
-- table.insert(tMonster[79]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	84	匪兵	9593450
-- tMonster[84] = tMonster[84] or {}
-- tMonster[84]["tFunction"] = tMonster[84]["tFunction"] or {}
-- table.insert(tMonster[84]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

-- 第六片区
--	20	土墓蝠	9593460
-- tMonster[20] = tMonster[20] or {}
-- tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
-- table.insert(tMonster[20]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	56	嗜血蝙蝠	9593470
-- tMonster[56] = tMonster[56] or {}
-- tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
-- table.insert(tMonster[56]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	57	牛怪	9593480
-- tMonster[57] = tMonster[57] or {}
-- tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
-- table.insert(tMonster[57]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	58	血影红魔	9593490
-- tMonster[58] = tMonster[58] or {}
-- tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
-- table.insert(tMonster[58]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

-- 第七片区
--	2411	冰凌腾蛇	9979200
-- tMonster[2411] = tMonster[2411] or {}
-- tMonster[2411]["tFunction"] = tMonster[2411]["tFunction"] or {}
-- table.insert(tMonster[2411]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	2416	冰煞邪刀	9979210
-- tMonster[2416] = tMonster[2416] or {}
-- tMonster[2416]["tFunction"] = tMonster[2416]["tFunction"] or {}
-- table.insert(tMonster[2416]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

-- 第八片区
--	2686	深海亡魂	98054381
-- tMonster[2686] = tMonster[2686] or {}
-- tMonster[2686]["tFunction"] = tMonster[2686]["tFunction"] or {}
-- table.insert(tMonster[2686]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	2684	缚灵	98054376
-- tMonster[2684] = tMonster[2684] or {}
-- tMonster[2684]["tFunction"] = tMonster[2684]["tFunction"] or {}
-- table.insert(tMonster[2684]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)

--	2687	深海魔魂	98054382
-- tMonster[2687] = tMonster[2687] or {}
-- tMonster[2687]["tFunction"] = tMonster[2687]["tFunction"] or {}
-- table.insert(tMonster[2687]["tFunction"],SummerActive2015_ZhongGuaDeGua_KillMonster)


-- tSystem_Prompet_Func = tSystem_Prompet_Func or {}
-- table.insert(tSystem_Prompet_Func,SummerActive2015_ZhongGuaDeGua_Assignment)
-- table.insert(tSystem_Prompet_Func,SummerActive2015_ZhongGuaDeGua_ItemGlobalRest)