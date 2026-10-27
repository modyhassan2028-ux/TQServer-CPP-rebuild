------------------------------------------------------------------------------------
--Name:		[英文征服][活动脚本]大漠寻宝活动
--Purpose:	大漠寻宝活动
--Creator: 	吴文鑫
--Created:	2015/07/15
------------------------------------------------------------------------------------

-- 命名前缀
-- TheTreasureHunt_

-- 掩码说明
-- 136	49		
--记录玩家进入哪种难度的闯关
--1	进入普通闯关
--2	进入危急闯关
--3	进入致命闯关

-- 136	50		
--记录当前闯关的关数
-- 1-8位对应的轮数
-- 10为当日已完成

-- 136	51	
--是否今日已领取过奖励	

--137	06
--记录副本开始的时间
--137	07
--记录副本是否开始
--137	12
--记录击杀怪物时的时间



-- 动态存储表说明
--80151	
--data0	记录	一帆风顺财富包/30万	限量（每个服活动期间限300个）
--data1	记录	龙珠（赠）			限量（每个服活动期间限100个）
--data2	记录	二龙戏珠财富包/80万	限量（每个服活动期间限300个）
--data3	记录	优质龙恨宝石		限量（每个服活动期间限200个）
--data4	记录	优质凤吟宝石		限量（每个服活动期间限200个）
--data5	记录	优质金麟宝石		限量（每个服活动期间限200个）

--80152
--data0	记录	优质惊鸿宝石		限量（每个服活动期间限200个）
--data1	记录	赤炼石+2			限量（每个服活动期间限300个）
--data2	记录	赤炼石+3			限量（每个服活动期间限150个）
--data3	记录	赤练石+5（赠）		限量（每个服活动期间限14个）
--data4	记录	龙珠（赠）			限量（每个服活动期间限100个）
--data5	记录	流星卷10个打包		限量（每个服活动期间限100个）

--80153
--data0	记录	二龙戏珠财富包/80万	限量（每个服活动期间限300个）
--data1	记录	绑定天石*100		限量（每个服活动期间限28个）
--data2	记录	优质龙恨宝石		限量（每个服活动期间限200个）
--data3	记录	优质凤吟宝石		限量（每个服活动期间限200个）
--data4	记录	赤炼石+6			限量（每个服活动期间限3个）
--data5	记录	马+6				限量（每个服活动期间限3个）

--80154
--data0	记录	龙珠				限量（每个服活动期间限200个）
--data1	记录	龙珠卷				限量（每个服活动期间限7个）
--data2	记录	流星卷10个打包/		限量（每个服活动期间限200个）
--data3	记录	优质玄元宝石		限量（每个服活动期间限5个）
--data4	记录	优质天怒宝石		限量（每个服活动期间限5个）
--data5	记录	优质地灵宝石		限量（每个服活动期间限5个）

--80155
--data0	记录	三元聚宝财富包/120万限量（每个服活动期间限300个）
--data1	记录	绑定天石*200		限量（每个服活动期间限7个）
--data2	记录	
--data3	记录
--data4	记录
--data5	记录

--50923
--data0	记录 今日普通闯关第1名难度玩家ID  DataStr0	姓名
--data1	记录 今日普通闯关第2名难度玩家ID  DataStr1  姓名
--data2	记录 今日普通闯关第3名难度玩家ID  DataStr2  姓名
--data3	记录 昨日普通闯关第1名难度玩家ID  DataStr3  姓名
--data4	记录 昨日普通闯关第2名难度玩家ID  DataStr4  姓名
--data5	记录 昨日普通闯关第3名难度玩家ID  DataStr5  姓名

--50924
--data0	记录 今日危急闯关第1名难度玩家ID  DataStr0	姓名
--data1	记录 今日危急闯关第2名难度玩家ID  DataStr1  姓名
--data2	记录 今日危急闯关第3名难度玩家ID  DataStr2  姓名
--data3	记录 昨日危急闯关第1名难度玩家ID  DataStr3  姓名
--data4	记录 昨日危急闯关第2名难度玩家ID  DataStr4  姓名
--data5	记录 昨日危急闯关第3名难度玩家ID  DataStr5  姓名

--50925
--data0	记录 今日致命闯关第1名难度玩家ID  DataStr0	姓名
--data1	记录 今日致命闯关第2名难度玩家ID  DataStr1  姓名
--data2	记录 今日致命闯关第3名难度玩家ID  DataStr2  姓名
--data3	记录 昨日致命闯关第1名难度玩家ID  DataStr3  姓名
--data4	记录 昨日致命闯关第2名难度玩家ID  DataStr4  姓名
--data5	记录 昨日致命闯关第3名难度玩家ID  DataStr5  姓名

--50926
--data0	记录 今日掩码是否已经重置赋值
--data1	记录
--data2	记录
--data3	记录
--data4	记录
--data5	记录

--50940
--data0	记录 今日普通闯关第1名难度玩家时间	
--data1	记录 今日普通闯关第2名难度玩家时间    
--data2	记录 今日普通闯关第3名难度玩家时间    
--data3	记录 今日危急闯关第1名难度玩家时间
--data4	记录 今日危急闯关第2名难度玩家时间
--data5	记录 今日危急闯关第3名难度玩家时间

--50941
--data0	记录 今日致命闯关第1名难度玩家时间
--data1	记录 今日致命闯关第2名难度玩家时间
--data2	记录 今日致命闯关第3名难度玩家时间
--data3	记录
--data4	记录
--data5	记录

-- 常量表
local tTheTreasureHunt_Constant = {}
	-- 活动时间
	tTheTreasureHunt_Constant["BeforeActivityTime"] = "2015-01-01 00:00 2015-08-30 23:59"
	tTheTreasureHunt_Constant["ActivityTime"] = "2015-08-31 00:00 2015-09-12 23:59"
	tTheTreasureHunt_Constant["Aftime"]  = "2015-09-14 00:00 2020-01-01 23:59"
	--活动第一天
	tTheTreasureHunt_Constant["FirstDay"] = "2015-08-31 00:00 2015-08-31 23:59"
	--活动结束后一天
	tTheTreasureHunt_Constant["LastDay"] = "2015-09-13 00:00 2015-09-13 23:59"
	--每日清掩码时间
	tTheTreasureHunt_Constant["ClearTime"] = "00:00 00:05"
	--每波宝箱击杀时间（秒）
	tTheTreasureHunt_Constant["DelayTime"] = 30
	tTheTreasureHunt_Constant["DelayTime1"] = 35
	--刷出不同boss时间的分隔（秒）
	tTheTreasureHunt_Constant["TimeLimit"] = 275
	--传入副本后与再次传入副本间隔时间（分钟）
	tTheTreasureHunt_Constant["EnterTimeLimit"] = 1
	
	
	-- 玩家等级要求
	tTheTreasureHunt_Constant["Metempsychosis"] = 1
	tTheTreasureHunt_Constant["Level"] = 100

	-- 满级
	tTheTreasureHunt_Constant["MaxLev"] = 140
	
	--完成今日龙穴任务
	tTheTreasureHunt_Constant["Complete"] = 10
	
	--副本任务编号
	tTheTreasureHunt_Constant["InstanceType"] = {}
	tTheTreasureHunt_Constant["InstanceType"][1] = 29
	tTheTreasureHunt_Constant["InstanceType"][2] = 30
	tTheTreasureHunt_Constant["InstanceType"][3] = 31
	
	--副本数量上限
	tTheTreasureHunt_Constant["nNumLimit"] = 200
	
	--创建副本记log
	tTheTreasureHunt_Constant["CopyLog"] = {}
	tTheTreasureHunt_Constant["CopyLog"][1] = "0,0,0,0,12000134,2,29,1"
	tTheTreasureHunt_Constant["CopyLog"][2] = "0,0,0,0,12000134,2,30,1"
	tTheTreasureHunt_Constant["CopyLog"][3] = "0,0,0,0,12000134,2,31,1"
	--杀怪记log
	tTheTreasureHunt_Constant["KillMonster"] = "0,0,0,0,12000134,3,%d,%d"
	
	
	--勇闯符ID
	-- tTheTreasureHunt_Constant["item"] = 3006950
	
	tTheTreasureHunt_Constant["EffectObj"] = "self"
	tTheTreasureHunt_Constant["Effect_1"] = "movego"
	tTheTreasureHunt_Constant["Effect_2"] = "moveback"
	tTheTreasureHunt_Constant["Effect_3"] = "zf2-e127"
	-- tTheTreasureHunt_Constant["Effect_4"] = "compose"
	-- tTheTreasureHunt_Constant["Effect_5"] = "eidolon"
	-- tTheTreasureHunt_Constant["Effect_6"] = "hunpo02"
	-- tTheTreasureHunt_Constant["Effect_7"] = "dispel"
	-- tTheTreasureHunt_Constant["Effect_8"] = "zf2-e300"
	-- tTheTreasureHunt_Constant["Effect_9"] = "zf2-e024"
	-- tTheTreasureHunt_Constant["Effect_10"] = "angelwing"
	
local tTheTreasureHunt_Power = {}
	--战力范围
	tTheTreasureHunt_Power[1] = 250
	tTheTreasureHunt_Power[2] = 331
	
local tTheTreasureHunt_Power1 = {}
	--战力范围
	tTheTreasureHunt_Power1[2] = 249
	tTheTreasureHunt_Power1[3] = 330
	
	
	
	
	
	-- 掩码表
local tTheTreasureHunt_Stc = {}
	tTheTreasureHunt_Stc["EventType"] = 136
	tTheTreasureHunt_Stc["DataType"] = {}
	tTheTreasureHunt_Stc["DataType"][1] = 49
	tTheTreasureHunt_Stc["DataType"][2] = 50
	tTheTreasureHunt_Stc["DataType"][3] = 51
	
	tTheTreasureHunt_Stc["EventType1"] = 137
	tTheTreasureHunt_Stc["DataType1"] = {}
	tTheTreasureHunt_Stc["DataType1"][1] = 06
	tTheTreasureHunt_Stc["DataType1"][2] = 07
	tTheTreasureHunt_Stc["DataType1"][3] = 12
	tTheTreasureHunt_Stc["DataType1"][4] = 89

	-- 动态存储表配置
	--记录物品限制上限
local tTheTreasureHunt_ItemGlobal = {}
	tTheTreasureHunt_ItemGlobal[1] = {}
	tTheTreasureHunt_ItemGlobal[1]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[1]["GlobalData"] = 0
	tTheTreasureHunt_ItemGlobal[1]["MaxData"] = 300

	tTheTreasureHunt_ItemGlobal[2] = {}
	tTheTreasureHunt_ItemGlobal[2]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[2]["GlobalData"] = 1
	tTheTreasureHunt_ItemGlobal[2]["MaxData"] = 100

	tTheTreasureHunt_ItemGlobal[3] = {}
	tTheTreasureHunt_ItemGlobal[3]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[3]["GlobalData"] = 2
	tTheTreasureHunt_ItemGlobal[3]["MaxData"] = 300
	
	tTheTreasureHunt_ItemGlobal[4] = {}
	tTheTreasureHunt_ItemGlobal[4]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[4]["GlobalData"] = 3
	tTheTreasureHunt_ItemGlobal[4]["MaxData"] = 200

	tTheTreasureHunt_ItemGlobal[5] = {}
	tTheTreasureHunt_ItemGlobal[5]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[5]["GlobalData"] = 4
	tTheTreasureHunt_ItemGlobal[5]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[6] = {}
	tTheTreasureHunt_ItemGlobal[6]["GlobalId"] = 80151
	tTheTreasureHunt_ItemGlobal[6]["GlobalData"] = 5
	tTheTreasureHunt_ItemGlobal[6]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[7] = {}
	tTheTreasureHunt_ItemGlobal[7]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[7]["GlobalData"] = 0
	tTheTreasureHunt_ItemGlobal[7]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[8] = {}
	tTheTreasureHunt_ItemGlobal[8]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[8]["GlobalData"] = 1
	tTheTreasureHunt_ItemGlobal[8]["MaxData"] = 300
	
	tTheTreasureHunt_ItemGlobal[9] = {}
	tTheTreasureHunt_ItemGlobal[9]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[9]["GlobalData"] = 2
	tTheTreasureHunt_ItemGlobal[9]["MaxData"] = 150

	tTheTreasureHunt_ItemGlobal[10] = {}
	tTheTreasureHunt_ItemGlobal[10]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[10]["GlobalData"] = 3
	tTheTreasureHunt_ItemGlobal[10]["MaxData"] = 14

	tTheTreasureHunt_ItemGlobal[11] = {}
	tTheTreasureHunt_ItemGlobal[11]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[11]["GlobalData"] = 4
	tTheTreasureHunt_ItemGlobal[11]["MaxData"] = 100
	
	tTheTreasureHunt_ItemGlobal[12] = {}
	tTheTreasureHunt_ItemGlobal[12]["GlobalId"] = 80152
	tTheTreasureHunt_ItemGlobal[12]["GlobalData"] = 5
	tTheTreasureHunt_ItemGlobal[12]["MaxData"] = 100
	
	tTheTreasureHunt_ItemGlobal[13] = {}
	tTheTreasureHunt_ItemGlobal[13]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[13]["GlobalData"] = 0
	tTheTreasureHunt_ItemGlobal[13]["MaxData"] = 300
	
	tTheTreasureHunt_ItemGlobal[14] = {}
	tTheTreasureHunt_ItemGlobal[14]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[14]["GlobalData"] = 1
	tTheTreasureHunt_ItemGlobal[14]["MaxData"] = 28
	
	tTheTreasureHunt_ItemGlobal[15] = {}
	tTheTreasureHunt_ItemGlobal[15]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[15]["GlobalData"] = 2
	tTheTreasureHunt_ItemGlobal[15]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[16] = {}
	tTheTreasureHunt_ItemGlobal[16]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[16]["GlobalData"] = 3
	tTheTreasureHunt_ItemGlobal[16]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[17] = {}
	tTheTreasureHunt_ItemGlobal[17]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[17]["GlobalData"] = 4
	tTheTreasureHunt_ItemGlobal[17]["MaxData"] = 3
	
	tTheTreasureHunt_ItemGlobal[18] = {}
	tTheTreasureHunt_ItemGlobal[18]["GlobalId"] = 80153
	tTheTreasureHunt_ItemGlobal[18]["GlobalData"] = 5
	tTheTreasureHunt_ItemGlobal[18]["MaxData"] = 3
	
	tTheTreasureHunt_ItemGlobal[19] = {}
	tTheTreasureHunt_ItemGlobal[19]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[19]["GlobalData"] = 0
	tTheTreasureHunt_ItemGlobal[19]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[20] = {}
	tTheTreasureHunt_ItemGlobal[20]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[20]["GlobalData"] = 1
	tTheTreasureHunt_ItemGlobal[20]["MaxData"] = 7
	
	tTheTreasureHunt_ItemGlobal[21] = {}
	tTheTreasureHunt_ItemGlobal[21]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[21]["GlobalData"] = 2
	tTheTreasureHunt_ItemGlobal[21]["MaxData"] = 200
	
	tTheTreasureHunt_ItemGlobal[22] = {}
	tTheTreasureHunt_ItemGlobal[22]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[22]["GlobalData"] = 3
	tTheTreasureHunt_ItemGlobal[22]["MaxData"] = 5
	
	tTheTreasureHunt_ItemGlobal[23] = {}
	tTheTreasureHunt_ItemGlobal[23]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[23]["GlobalData"] = 4
	tTheTreasureHunt_ItemGlobal[23]["MaxData"] = 5
	
	tTheTreasureHunt_ItemGlobal[24] = {}
	tTheTreasureHunt_ItemGlobal[24]["GlobalId"] = 80154
	tTheTreasureHunt_ItemGlobal[24]["GlobalData"] = 5
	tTheTreasureHunt_ItemGlobal[24]["MaxData"] = 5
	
	tTheTreasureHunt_ItemGlobal[25] = {}
	tTheTreasureHunt_ItemGlobal[25]["GlobalId"] = 80155
	tTheTreasureHunt_ItemGlobal[25]["GlobalData"] = 0
	tTheTreasureHunt_ItemGlobal[25]["MaxData"] = 300
	
	tTheTreasureHunt_ItemGlobal[26] = {}
	tTheTreasureHunt_ItemGlobal[26]["GlobalId"] = 80155
	tTheTreasureHunt_ItemGlobal[26]["GlobalData"] = 1
	tTheTreasureHunt_ItemGlobal[26]["MaxData"] = 7
	
	
local tTheTreasureHunt_TaskGlobal = {}
	
	tTheTreasureHunt_TaskGlobal[1] = {}
	tTheTreasureHunt_TaskGlobal[1]["GlobalId"] = 50923
	
	tTheTreasureHunt_TaskGlobal[2] = {}
	tTheTreasureHunt_TaskGlobal[2]["GlobalId"] = 50924
	
	tTheTreasureHunt_TaskGlobal[3] = {}
	tTheTreasureHunt_TaskGlobal[3]["GlobalId"] = 50925
		
	tTheTreasureHunt_TaskGlobal[4] = {}
	tTheTreasureHunt_TaskGlobal[4]["GlobalId"] = 50926

local tTheTreasureHunt_RankingGlobal = {}
	
	tTheTreasureHunt_RankingGlobal[1] = {}
	tTheTreasureHunt_RankingGlobal[1]["GlobalId"] = 50940
	tTheTreasureHunt_RankingGlobal[1]["GlobalData"] = {}
	tTheTreasureHunt_RankingGlobal[1]["GlobalData"][1] = 0
	tTheTreasureHunt_RankingGlobal[1]["GlobalData"][2] = 1
	tTheTreasureHunt_RankingGlobal[1]["GlobalData"][3] = 2
	
	tTheTreasureHunt_RankingGlobal[2] = {}
	tTheTreasureHunt_RankingGlobal[2]["GlobalId"] = 50940
	tTheTreasureHunt_RankingGlobal[2]["GlobalData"] = {}
	tTheTreasureHunt_RankingGlobal[2]["GlobalData"][1] = 3
	tTheTreasureHunt_RankingGlobal[2]["GlobalData"][2] = 4
	tTheTreasureHunt_RankingGlobal[2]["GlobalData"][3] = 5
	
	tTheTreasureHunt_RankingGlobal[3] = {}
	tTheTreasureHunt_RankingGlobal[3]["GlobalId"] = 50941
	tTheTreasureHunt_RankingGlobal[3]["GlobalData"] = {}
	tTheTreasureHunt_RankingGlobal[3]["GlobalData"][1] = 0
	tTheTreasureHunt_RankingGlobal[3]["GlobalData"][2] = 1
	tTheTreasureHunt_RankingGlobal[3]["GlobalData"][3] = 2
	
	
	
	-- 自动寻路
local tTheTreasureHunt_Auto = {}
	tTheTreasureHunt_Auto["MapId"] = 1002
	tTheTreasureHunt_Auto["CellX"] = 299
	tTheTreasureHunt_Auto["CellY"] = 285
	tTheTreasureHunt_Auto["NpcId"] = 18711

local tTheTreasureHunt_Leave = {}
	tTheTreasureHunt_Leave["MapId"] = 1002
	tTheTreasureHunt_Leave["CellX"] = 300
	tTheTreasureHunt_Leave["CellY"] = 287

	--刷怪坐标
local tTheTreasureHunt_BrushMonster = {}
	tTheTreasureHunt_BrushMonster[1] = {}
	tTheTreasureHunt_BrushMonster[1]["CellX"]= {}
	tTheTreasureHunt_BrushMonster[1]["CellX"][1] = 60
	tTheTreasureHunt_BrushMonster[1]["CellX"][2] = 53
	tTheTreasureHunt_BrushMonster[1]["CellX"][3] = 59
	tTheTreasureHunt_BrushMonster[1]["CellX"][4] = 65
	tTheTreasureHunt_BrushMonster[1]["CellX"][5] = 49
	
	tTheTreasureHunt_BrushMonster[1]["CellY"]= {}
	tTheTreasureHunt_BrushMonster[1]["CellY"][1] = 58
	tTheTreasureHunt_BrushMonster[1]["CellY"][2] = 62
	tTheTreasureHunt_BrushMonster[1]["CellY"][3] = 76
	tTheTreasureHunt_BrushMonster[1]["CellY"][4] = 69
	tTheTreasureHunt_BrushMonster[1]["CellY"][5] = 70

	tTheTreasureHunt_BrushMonster[2] = {}
	tTheTreasureHunt_BrushMonster[2]["CellX"]= {}
	tTheTreasureHunt_BrushMonster[2]["CellX"][1] = 60
	tTheTreasureHunt_BrushMonster[2]["CellX"][2] = 53
	tTheTreasureHunt_BrushMonster[2]["CellX"][3] = 59
	tTheTreasureHunt_BrushMonster[2]["CellX"][4] = 65
	tTheTreasureHunt_BrushMonster[2]["CellX"][5] = 49
	
	tTheTreasureHunt_BrushMonster[2]["CellY"]= {}
	tTheTreasureHunt_BrushMonster[2]["CellY"][1] = 58
	tTheTreasureHunt_BrushMonster[2]["CellY"][2] = 62
	tTheTreasureHunt_BrushMonster[2]["CellY"][3] = 76
	tTheTreasureHunt_BrushMonster[2]["CellY"][4] = 69
	tTheTreasureHunt_BrushMonster[2]["CellY"][5] = 70

	--刷boss坐标
local tTheTreasureHunt_BrushBoss = {}
	tTheTreasureHunt_BrushBoss["CellX"] = 60
	tTheTreasureHunt_BrushBoss["CellY"] = 67
	

local tTheTreasureHunt_Reward = {}

	tTheTreasureHunt_Reward[50923] = {}
	tTheTreasureHunt_Reward[50923][1] = {}
	tTheTreasureHunt_Reward[50923][1]["Space"] = 5
	tTheTreasureHunt_Reward[50923][1]["Cultivation"] = 300
	tTheTreasureHunt_Reward[50923][1]["ItemId"] = 723700
	tTheTreasureHunt_Reward[50923][1]["ItemAttr"] = "0 5 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50923][1]["Log"] = "0,0,0,0,12000134,2,6[723700],300[5]"
	
	tTheTreasureHunt_Reward[50923][2] = {}
	tTheTreasureHunt_Reward[50923][2]["Space"] = 4
	tTheTreasureHunt_Reward[50923][2]["Cultivation"] = 200
	tTheTreasureHunt_Reward[50923][2]["ItemId"] = 723700
	tTheTreasureHunt_Reward[50923][2]["ItemAttr"] = "0 4 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50923][2]["Log"] = "0,0,0,0,12000134,2,6[723700],200[4]"
	
	tTheTreasureHunt_Reward[50923][3] = {}
	tTheTreasureHunt_Reward[50923][3]["Space"] = 3
	tTheTreasureHunt_Reward[50923][3]["Cultivation"] = 100
	tTheTreasureHunt_Reward[50923][3]["ItemId"] = 723700
	tTheTreasureHunt_Reward[50923][3]["ItemAttr"] = "0 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50923][3]["Log"] = "0,0,0,0,12000134,2,6[723700],100[3]"
	
	
	tTheTreasureHunt_Reward[50924] = {}
	tTheTreasureHunt_Reward[50924][1] = {}
	tTheTreasureHunt_Reward[50924][1]["Space"] = 1
	tTheTreasureHunt_Reward[50924][1]["Strengthvalue"] = 500
	tTheTreasureHunt_Reward[50924][1]["ItemId"] = 3003125
	tTheTreasureHunt_Reward[50924][1]["ItemAttr"] = "0 5 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50924][1]["Log"] = "0,0,0,0,12000134,2,12[3003125],500[5]"
	
	tTheTreasureHunt_Reward[50924][2] = {}
	tTheTreasureHunt_Reward[50924][2]["Space"] = 1
	tTheTreasureHunt_Reward[50924][2]["Strengthvalue"] = 400
	tTheTreasureHunt_Reward[50924][2]["ItemId"] = 3003125
	tTheTreasureHunt_Reward[50924][2]["ItemAttr"] = "0 4 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50924][2]["Log"] = "0,0,0,0,12000134,2,12[3003125],400[4]"
	
	tTheTreasureHunt_Reward[50924][3] = {}
	tTheTreasureHunt_Reward[50924][3]["Space"] = 1
	tTheTreasureHunt_Reward[50924][3]["Strengthvalue"] = 300
	tTheTreasureHunt_Reward[50924][3]["ItemId"] = 3003125
	tTheTreasureHunt_Reward[50924][3]["ItemAttr"] = "0 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50924][3]["Log"] = "0,0,0,0,12000134,2,12[3003125],300[3]"
	
	
	tTheTreasureHunt_Reward[50925] = {}
	tTheTreasureHunt_Reward[50925][1] = {}
	tTheTreasureHunt_Reward[50925][1]["Space"] = 1
	tTheTreasureHunt_Reward[50925][1]["Strengthvalue"] = 1000
	tTheTreasureHunt_Reward[50925][1]["ItemId"] = 3003124
	tTheTreasureHunt_Reward[50925][1]["ItemAttr"] = "0 5 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50925][1]["Log"] = "0,0,0,0,12000134,2,12[3003124],1000[5]"

	tTheTreasureHunt_Reward[50925][2] = {}
	tTheTreasureHunt_Reward[50925][2]["Space"] = 1
	tTheTreasureHunt_Reward[50925][2]["Strengthvalue"] = 800
	tTheTreasureHunt_Reward[50925][2]["ItemId"] = 3003124
	tTheTreasureHunt_Reward[50925][2]["ItemAttr"] = "0 4 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50925][2]["Log"] = "0,0,0,0,12000134,2,12[3003124],800[4]"

	tTheTreasureHunt_Reward[50925][3] = {}
	tTheTreasureHunt_Reward[50925][3]["Space"] = 1
	tTheTreasureHunt_Reward[50925][3]["Strengthvalue"] = 500
	tTheTreasureHunt_Reward[50925][3]["ItemId"] = 3003124
	tTheTreasureHunt_Reward[50925][3]["ItemAttr"] = "0 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Reward[50925][3]["Log"] = "0,0,0,0,12000134,2,12[3003124],500[3]"
	
	
	-- 礼包配置
local tTheTreasureHunt_Item = {}
	-- 龙穴古书
	tTheTreasureHunt_Item[3006949] = {}
	tTheTreasureHunt_Item[3006949]["Exp"] = 30
	tTheTreasureHunt_Item[3006949]["Cultivation"] = 15
	tTheTreasureHunt_Item[3006949]["ExpLog"] = "0,0,3006949,1,12000134,2,4,30"
	tTheTreasureHunt_Item[3006949]["CultivationLog"] = "0,0,3006949,1,12000134,2,6,15"

	-- 勇闯符
	tTheTreasureHunt_Brave = {}
	tTheTreasureHunt_Brave[1] = 143
	tTheTreasureHunt_Brave[2] = 144
	tTheTreasureHunt_Brave[3] = 141
	tTheTreasureHunt_Brave[4] = 142
	tTheTreasureHunt_Brave[5] = 133
	tTheTreasureHunt_Brave[6] = 134
	tTheTreasureHunt_Brave[143] = 1000
	tTheTreasureHunt_Brave[144] = 1000
	tTheTreasureHunt_Brave[141] = 1000
	tTheTreasureHunt_Brave[142] = 1000
	tTheTreasureHunt_Brave[133] = 10
	tTheTreasureHunt_Brave[134] = 10
	tTheTreasureHunt_Brave["Secs"] = 300
	tTheTreasureHunt_Brave["Times"] = 1
	tTheTreasureHunt_Brave["RemainTime"] = 300
	tTheTreasureHunt_Brave["EndTime"] = 1
	tTheTreasureHunt_Brave["Recordable"] = 1
	-- tTheTreasureHunt_Brave["NpcName"] = "龙穴探秘者"
	-- tTheTreasureHunt_Brave["Log"] = "0,0,3006950,1,12000134,2,143[144][141][142][133][134],1000[1000][1000][1000][10][10]"

	
	
	
	
	
	-- 龙穴宝盒碎片
	tTheTreasureHunt_Item[3006953] = {}
	tTheTreasureHunt_Item[3006953]["ChkItemNum"] = 10
	tTheTreasureHunt_Item[3006953]["ItemId"] = 3006951
	tTheTreasureHunt_Item[3006953]["Log"] = "0,0,3006953,10,12000134,2,3006951,1"
	tTheTreasureHunt_Item[3006953]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006953]["Effect_1"] = "heal2-1"
	tTheTreasureHunt_Item[3006953]["Space"] = 1
	
	

	-- 15分钟经验包
	tTheTreasureHunt_Item[3007023] = {}
	tTheTreasureHunt_Item[3007023]["Exp"] = 15
	tTheTreasureHunt_Item[3007023]["Cultivation"] = 7
	tTheTreasureHunt_Item[3007023]["ExpLog"] = "0,0,3007023,1,12000134,2,4,15"
	tTheTreasureHunt_Item[3007023]["CultivationLog"] = "0,0,3007023,1,12000134,2,6,7"
	tTheTreasureHunt_Item[3007023]["Effect_1"] = "dispel"
	
	
	-- 30分钟经验包
	tTheTreasureHunt_Item[3007024] = {}
	tTheTreasureHunt_Item[3007024]["Exp"] = 30
	tTheTreasureHunt_Item[3007024]["Cultivation"] = 15
	tTheTreasureHunt_Item[3007024]["ExpLog"] = "0,0,3007024,1,12000134,2,4,30"
	tTheTreasureHunt_Item[3007024]["CultivationLog"] = "0,0,3007024,1,12000134,2,6,15"
	tTheTreasureHunt_Item[3007024]["Effect_1"] = "dispel"
	
	-- 60分钟经验包
	tTheTreasureHunt_Item[3007120] = {}
	tTheTreasureHunt_Item[3007120]["Exp"] = 60
	tTheTreasureHunt_Item[3007120]["Cultivation"] = 30
	tTheTreasureHunt_Item[3007120]["ExpLog"] = "0,0,3007120,1,12000134,2,4,60"
	tTheTreasureHunt_Item[3007120]["CultivationLog"] = "0,0,3007120,1,12000134,2,6,30"
	tTheTreasureHunt_Item[3007120]["Effect_1"] = "dispel"
	
	-- 10点修行值礼包
	tTheTreasureHunt_Item[3007119] = {}
	tTheTreasureHunt_Item[3007119]["Cultivation"] = 10
	tTheTreasureHunt_Item[3007119]["Log"] = "0,0,3007119,1,12000134,2,6,10"
	tTheTreasureHunt_Item[3007119]["Effect_1"] = "zf2-e300"
	
	-- 20点修行值礼包
	tTheTreasureHunt_Item[3007025] = {}
	tTheTreasureHunt_Item[3007025]["Cultivation"] = 20
	tTheTreasureHunt_Item[3007025]["Log"] = "0,0,3007025,1,12000134,2,6,20"
	tTheTreasureHunt_Item[3007025]["Effect_1"] = "zf2-e300"
	
	-- 40点修行值礼包
	tTheTreasureHunt_Item[3007026] = {}
	tTheTreasureHunt_Item[3007026]["Cultivation"] = 40
	tTheTreasureHunt_Item[3007026]["Log"] = "0,0,3007026,1,12000134,2,6,40"
	tTheTreasureHunt_Item[3007026]["Effect_1"] = "zf2-e300"
	
	-- 40点气力值礼包
	tTheTreasureHunt_Item[3007121] = {}
	tTheTreasureHunt_Item[3007121]["Strengthvalue"] = 40
	tTheTreasureHunt_Item[3007121]["Log"] = "0,0,3007121,1,12000134,2,12,40"
	tTheTreasureHunt_Item[3007121]["Effect_1"] = "angelwing"
	
	
	-- 20点气力值礼包
	tTheTreasureHunt_Item[3007122] = {}
	tTheTreasureHunt_Item[3007122]["Strengthvalue"] = 20
	tTheTreasureHunt_Item[3007122]["Log"] = "0,0,3007122,1,12000134,2,12,20"
	tTheTreasureHunt_Item[3007122]["Effect_1"] = "angelwing"
	
	-- 迷你银两包
	tTheTreasureHunt_Item[3007027] = {}
	tTheTreasureHunt_Item[3007027]["Money"] = 50000
	tTheTreasureHunt_Item[3007027]["Log"] = "0,0,3007027,1,12000134,2,1,50000"
	tTheTreasureHunt_Item[3007027]["Effect_1"] = "zf2-e024"
	
	
	-- 经济银两包
	tTheTreasureHunt_Item[3007028] = {}
	tTheTreasureHunt_Item[3007028]["Money"] = 100000
	tTheTreasureHunt_Item[3007028]["Log"] = "0,0,3007028,1,12000134,2,1,100000"
	tTheTreasureHunt_Item[3007028]["Effect_1"] = "zf2-e024"
	
	
	-- 丰足银两包
	tTheTreasureHunt_Item[3007029] = {}
	tTheTreasureHunt_Item[3007029]["Money"] = 200000
	tTheTreasureHunt_Item[3007029]["Log"] = "0,0,3007029,1,12000134,2,1,200000"
	tTheTreasureHunt_Item[3007029]["Effect_1"] = "zf2-e024"
	
	-- 3007031	+2SteedPack
	tTheTreasureHunt_Item[3007031] = {}
	tTheTreasureHunt_Item[3007031]["ItemId"] = 300000
	tTheTreasureHunt_Item[3007031]["ItemAttr"] = {}
	tTheTreasureHunt_Item[3007031]["ItemAttr"][1] = "0 1 3 0 0 0 65430 0 255 0 2 0 0 0 0 0 0 150 0 3"
	tTheTreasureHunt_Item[3007031]["ItemAttr"][2] = "0 1 3 0 0 0 16750080 255 150 0 2 0 0 0 0 0 0 0 0 3 "
	tTheTreasureHunt_Item[3007031]["ItemAttr"][3] = "0 1 3 0 0 0 9830655 150 0 0 2 0 0 0 0 0 0 255 0 3"
	tTheTreasureHunt_Item[3007031]["Log"] = {}
	tTheTreasureHunt_Item[3007031]["Log"][1] = "0,0,3007031,1,12000134,2,300000,65430"
	tTheTreasureHunt_Item[3007031]["Log"][2] = "0,0,3007031,1,12000134,2,300000,16750080"
	tTheTreasureHunt_Item[3007031]["Log"][3] = "0,0,3007031,1,12000134,2,300000,9830655"

	-- 3007032	+3SteedPack
	tTheTreasureHunt_Item[3007032] = {}
	tTheTreasureHunt_Item[3007032]["ItemId"] = 300000
	tTheTreasureHunt_Item[3007032]["ItemAttr"] = {}
	tTheTreasureHunt_Item[3007032]["ItemAttr"][1] = "0 1 3 0 0 0 65430 0 255 0 3 0 0 0 0 0 0 150 0 3"
	tTheTreasureHunt_Item[3007032]["ItemAttr"][2] = "0 1 3 0 0 0 16750080 255 150 0 3 0 0 0 0 0 0 0 0 3 "
	tTheTreasureHunt_Item[3007032]["ItemAttr"][3] = "0 1 3 0 0 0 9830655 150 0 0 3 0 0 0 0 0 0 255 0 3"
	
	tTheTreasureHunt_Item[3007032]["Log"] = {}
	tTheTreasureHunt_Item[3007032]["Log"][1] = "0,0,3007032,1,12000134,2,300000,65430"
	tTheTreasureHunt_Item[3007032]["Log"][2] = "0,0,3007032,1,12000134,2,300000,16750080"
	tTheTreasureHunt_Item[3007032]["Log"][3] = "0,0,3007032,1,12000134,2,300000,9830655"
	
	
	-- 龙穴宝盒
	tTheTreasureHunt_Item[3006951] = {}
	tTheTreasureHunt_Item[3006951]["ChkItemNum"] = 10
	tTheTreasureHunt_Item[3006951]["Space"] = 2
	
	tTheTreasureHunt_Item[3006951]["ItemId"] = 3007022
	tTheTreasureHunt_Item[3006951]["Log"] = "0,0,3006951,10,12000134,2,3007022,1"
	tTheTreasureHunt_Item[3006951]["ItemAttr"] = "0 1"
	
	tTheTreasureHunt_Item[3006951]["Effect"] = "eidolon"
	tTheTreasureHunt_Item[3006951]["Effect_1"] = "heal2-1"
	
	tTheTreasureHunt_Item[3006951]["EmoneyBuyLog"] = "350	20080	0	0	1	"
	
	
	tTheTreasureHunt_Item[3006951][1] = {}
	tTheTreasureHunt_Item[3006951][1]["ItemChanceSum"] = 10000

	
	-- 龙穴宝盒（0转，1转）
	-- 经验球（赠）*2	20%
	tTheTreasureHunt_Item[3006951][1][1] = {}
	tTheTreasureHunt_Item[3006951][1][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][1]["ItemChance"] = 2000
	tTheTreasureHunt_Item[3006951][1][1]["Item_1"] = 723700
	tTheTreasureHunt_Item[3006951][1][1]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][1]["Index"] = 1
	tTheTreasureHunt_Item[3006951][1][1]["Log"] = "0,0,3006951,1,12000103,2,723700,2"

	-- 小祈愿石（赠）	6%
	tTheTreasureHunt_Item[3006951][1][2] = {}
	tTheTreasureHunt_Item[3006951][1][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][2]["ItemChance"] = 600
	tTheTreasureHunt_Item[3006951][1][2]["Item_1"] = 1200000
	tTheTreasureHunt_Item[3006951][1][2]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][2]["Index"] = 2
	tTheTreasureHunt_Item[3006951][1][2]["Log"] = "0,0,3006951,1,12000103,2,1200000,1"

	-- 玄灵秘录/20修行值（赠）	8%
	tTheTreasureHunt_Item[3006951][1][3] = {}
	tTheTreasureHunt_Item[3006951][1][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][3]["ItemChance"] = 800
	tTheTreasureHunt_Item[3006951][1][3]["Item_1"] = 723341
	tTheTreasureHunt_Item[3006951][1][3]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][3]["Index"] = 3
	tTheTreasureHunt_Item[3006951][1][3]["Log"] = "0,0,3006951,1,12000103,2,723341,1"
	
	-- 赤炼石+1（赠）	15%
	tTheTreasureHunt_Item[3006951][1][4] = {}
	tTheTreasureHunt_Item[3006951][1][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][4]["ItemChance"] = 1500
	tTheTreasureHunt_Item[3006951][1][4]["Item_1"] = 730001
	tTheTreasureHunt_Item[3006951][1][4]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][4]["Index"] = 4
	tTheTreasureHunt_Item[3006951][1][4]["Log"] = "0,0,3006951,1,12000103,2,730001,1"
	
	-- 赤炼石+2（赠）	2%
	tTheTreasureHunt_Item[3006951][1][5] = {}
	tTheTreasureHunt_Item[3006951][1][5]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][5]["ItemChance"] = 200
	tTheTreasureHunt_Item[3006951][1][5]["Item_1"] = 730002
	tTheTreasureHunt_Item[3006951][1][5]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][5]["Index"] = 5
	tTheTreasureHunt_Item[3006951][1][5]["Log"] = "0,0,3006951,1,12000103,2,730002,1"
	
	-- 双倍经验药水（赠）*2	8%	
	tTheTreasureHunt_Item[3006951][1][6] = {}
	tTheTreasureHunt_Item[3006951][1][6]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][6]["ItemChance"] = 800
	tTheTreasureHunt_Item[3006951][1][6]["Item_1"] = 723017
	tTheTreasureHunt_Item[3006951][1][6]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][6]["Index"] = 6
	tTheTreasureHunt_Item[3006951][1][6]["Log"] = "0,0,3006951,1,12000103,2,723017,2"
	
	-- 马+2（赠）	2%
	tTheTreasureHunt_Item[3006951][1][7] = {}
	tTheTreasureHunt_Item[3006951][1][7]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][7]["ItemChance"] = 200
	tTheTreasureHunt_Item[3006951][1][7]["Item_1"] = 3007031
	tTheTreasureHunt_Item[3006951][1][7]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][7]["Index"] = 7
	tTheTreasureHunt_Item[3006951][1][7]["Log"] = "0,0,3006951,1,12000103,2,3007031,1"
	
	-- 龙珠（赠）	1%
	tTheTreasureHunt_Item[3006951][1][8] = {}
	tTheTreasureHunt_Item[3006951][1][8]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][8]["ItemChance"] = 100
	tTheTreasureHunt_Item[3006951][1][8]["Item_1"] = 1088000
	tTheTreasureHunt_Item[3006951][1][8]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][1][8]["Index"] = 8
	tTheTreasureHunt_Item[3006951][1][8]["Log"] = "0,0,3006951,1,12000103,2,1088000,1"
	
	-- 流星卷	20%
	tTheTreasureHunt_Item[3006951][1][9] = {}
	tTheTreasureHunt_Item[3006951][1][9]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][9]["ItemChance"] = 2000
	tTheTreasureHunt_Item[3006951][1][9]["Item_1"] = 720027
	tTheTreasureHunt_Item[3006951][1][9]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][1][9]["Index"] = 9
	tTheTreasureHunt_Item[3006951][1][9]["Log"] = "0,0,3006951,1,12000103,2,720027,1"
	
	-- 一帆风顺财富包/30万	8%
	tTheTreasureHunt_Item[3006951][1][10] = {}
	tTheTreasureHunt_Item[3006951][1][10]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][10]["ItemChance"] = 800
	tTheTreasureHunt_Item[3006951][1][10]["Item_1"] = 723713
	tTheTreasureHunt_Item[3006951][1][10]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][1][10]["Index"] = 10
	tTheTreasureHunt_Item[3006951][1][10]["Log"] = "0,0,3006951,1,12000103,2,723713,1"
	tTheTreasureHunt_Item[3006951][1][10]["Global"] = 1
	tTheTreasureHunt_Item[3006951][1][10]["GlobalItem"] = 1
		
		
	-- 良品随机宝石袋（除天怒、地灵、玄元外）	10%
	tTheTreasureHunt_Item[3006951][1][11] = {}
	tTheTreasureHunt_Item[3006951][1][11]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][1][11]["ItemChance"] = 1000
	tTheTreasureHunt_Item[3006951][1][11]["Item_1"] = 3003876
	tTheTreasureHunt_Item[3006951][1][11]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][1][11]["Index"] = 11
	tTheTreasureHunt_Item[3006951][1][11]["Log"] = "0,0,3006951,1,12000103,2,3003876,1"
	
	
	tTheTreasureHunt_Item[3006951][2] = {}
	tTheTreasureHunt_Item[3006951][2]["ItemChanceSum"] = 10000
	
	
	-- 龙穴宝盒（2转）
	-- 100气力包/729476（赠）*2	16%	3004579	100ChiPointsPack
	tTheTreasureHunt_Item[3006951][2][1] = {}
	tTheTreasureHunt_Item[3006951][2][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][1]["ItemChance"] = 1600
	tTheTreasureHunt_Item[3006951][2][1]["Item_1"] = 729476
	tTheTreasureHunt_Item[3006951][2][1]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][1]["Index"] = 1
	tTheTreasureHunt_Item[3006951][2][1]["Log"] = "0,0,3006951,1,12000103,2,729476,2"
	
	
	-- 免费强炼丹（赠）	10%
	tTheTreasureHunt_Item[3006951][2][2] = {}
	tTheTreasureHunt_Item[3006951][2][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][2]["ItemChance"] = 1000
	tTheTreasureHunt_Item[3006951][2][2]["Item_1"] = 3003124
	tTheTreasureHunt_Item[3006951][2][2]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][2]["Index"] = 2
	tTheTreasureHunt_Item[3006951][2][2]["Log"] = "0,0,3006951,1,12000103,2,3003124,1"
	
	
	-- 通神丹（赠）	8%
	tTheTreasureHunt_Item[3006951][2][3] = {}
	tTheTreasureHunt_Item[3006951][2][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][3]["ItemChance"] = 800
	tTheTreasureHunt_Item[3006951][2][3]["Item_1"] = 3003125
	tTheTreasureHunt_Item[3006951][2][3]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][3]["Index"] = 3
	tTheTreasureHunt_Item[3006951][2][3]["Log"] = "0,0,3006951,1,12000103,2,3003125,1"
	
	-- 护心丹/有时效（赠）*2	5%
	tTheTreasureHunt_Item[3006951][2][4] = {}
	tTheTreasureHunt_Item[3006951][2][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][4]["ItemChance"] = 500
	tTheTreasureHunt_Item[3006951][2][4]["Item_1"] = 3002029
	tTheTreasureHunt_Item[3006951][2][4]["ItemAttr"] = "0 2 3 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][4]["Index"] = 4
	tTheTreasureHunt_Item[3006951][2][4]["Log"] = "0,0,3006951,1,12000103,2,3002029,2"
	

	-- 赤炼石+1（赠）*2	10%
	tTheTreasureHunt_Item[3006951][2][5] = {}
	tTheTreasureHunt_Item[3006951][2][5]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][5]["ItemChance"] = 1000
	tTheTreasureHunt_Item[3006951][2][5]["Item_1"] = 730001
	tTheTreasureHunt_Item[3006951][2][5]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][5]["Index"] = 5
	tTheTreasureHunt_Item[3006951][2][5]["Log"] = "0,0,3006951,1,12000103,2,730001,2"
	
	-- 赤炼石+2（赠）*2	4%
	tTheTreasureHunt_Item[3006951][2][6] = {}
	tTheTreasureHunt_Item[3006951][2][6]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][6]["ItemChance"] = 400
	tTheTreasureHunt_Item[3006951][2][6]["Item_1"] = 730002
	tTheTreasureHunt_Item[3006951][2][6]["ItemAttr"] = "0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][6]["Index"] = 6
	tTheTreasureHunt_Item[3006951][2][6]["Log"] = "0,0,3006951,1,12000103,2,730002,2"
	
	
	-- 马+3（赠）	1%
	tTheTreasureHunt_Item[3006951][2][7] = {}
	tTheTreasureHunt_Item[3006951][2][7]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][7]["ItemChance"] = 100
	tTheTreasureHunt_Item[3006951][2][7]["Item_1"] = 3007032
	tTheTreasureHunt_Item[3006951][2][7]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][7]["Index"] = 7
	tTheTreasureHunt_Item[3006951][2][7]["Log"] = "0,0,3006951,1,12000103,2,3007032,1"
	
	-- 龙珠（赠）	1%
	tTheTreasureHunt_Item[3006951][2][8] = {}
	tTheTreasureHunt_Item[3006951][2][8]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][8]["ItemChance"] = 100
	tTheTreasureHunt_Item[3006951][2][8]["Item_1"] = 1088000
	tTheTreasureHunt_Item[3006951][2][8]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3006951][2][8]["Index"] = 8
	tTheTreasureHunt_Item[3006951][2][8]["Log"] = "0,0,3006951,1,12000103,2,1088000,1"
	tTheTreasureHunt_Item[3006951][2][8]["Global"] = 2
	tTheTreasureHunt_Item[3006951][2][8]["GlobalItem"] = 3
	
	-- 流星卷	25%
	tTheTreasureHunt_Item[3006951][2][9] = {}
	tTheTreasureHunt_Item[3006951][2][9]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][9]["ItemChance"] = 2500
	tTheTreasureHunt_Item[3006951][2][9]["Item_1"] = 720027
	tTheTreasureHunt_Item[3006951][2][9]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][9]["Index"] = 9
	tTheTreasureHunt_Item[3006951][2][9]["Log"] = "0,0,3006951,1,12000103,2,720027,1"
	

	-- 二龙戏珠财富包/80万	8%
	tTheTreasureHunt_Item[3006951][2][10] = {}
	tTheTreasureHunt_Item[3006951][2][10]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][10]["ItemChance"] = 800
	tTheTreasureHunt_Item[3006951][2][10]["Item_1"] = 723714
	tTheTreasureHunt_Item[3006951][2][10]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][10]["Index"] = 10
	tTheTreasureHunt_Item[3006951][2][10]["Log"] = "0,0,3006951,1,12000103,2,723714,1"
	tTheTreasureHunt_Item[3006951][2][10]["Global"] = 3
	tTheTreasureHunt_Item[3006951][2][10]["GlobalItem"] = 3
	
	
	
	-- 优质龙恨宝石	3.00%
	tTheTreasureHunt_Item[3006951][2][11] = {}
	tTheTreasureHunt_Item[3006951][2][11]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][11]["ItemChance"] = 300
	tTheTreasureHunt_Item[3006951][2][11]["Item_1"] = 700013
	tTheTreasureHunt_Item[3006951][2][11]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][11]["Index"] = 11
	tTheTreasureHunt_Item[3006951][2][11]["Log"] = "0,0,3006951,1,12000103,2,700013,1"
	tTheTreasureHunt_Item[3006951][2][11]["Global"] = 4
	tTheTreasureHunt_Item[3006951][2][11]["GlobalItem"] = 3
	
	-- 优质凤吟宝石	3.00%
	tTheTreasureHunt_Item[3006951][2][12] = {}
	tTheTreasureHunt_Item[3006951][2][12]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][12]["ItemChance"] = 300
	tTheTreasureHunt_Item[3006951][2][12]["Item_1"] = 700003
	tTheTreasureHunt_Item[3006951][2][12]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][12]["Index"] = 12
	tTheTreasureHunt_Item[3006951][2][12]["Log"] = "0,0,3006951,1,12000103,2,700003,1"
	tTheTreasureHunt_Item[3006951][2][12]["Global"] = 5
	tTheTreasureHunt_Item[3006951][2][12]["GlobalItem"] = 3
	
	-- 优质金麟宝石	3.00%
	tTheTreasureHunt_Item[3006951][2][13] = {}
	tTheTreasureHunt_Item[3006951][2][13]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][13]["ItemChance"] = 300
	tTheTreasureHunt_Item[3006951][2][13]["Item_1"] = 700043
	tTheTreasureHunt_Item[3006951][2][13]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][13]["Index"] = 13
	tTheTreasureHunt_Item[3006951][2][13]["Log"] = "0,0,3006951,1,12000103,2,700043,1"
	tTheTreasureHunt_Item[3006951][2][13]["Global"] = 6
	tTheTreasureHunt_Item[3006951][2][13]["GlobalItem"] = 3
	
	
	-- 优质惊鸿宝石	3.00%
	tTheTreasureHunt_Item[3006951][2][14] = {}
	tTheTreasureHunt_Item[3006951][2][14]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3006951][2][14]["ItemChance"] = 300
	tTheTreasureHunt_Item[3006951][2][14]["Item_1"] = 700023
	tTheTreasureHunt_Item[3006951][2][14]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3006951][2][14]["Index"] = 14
	tTheTreasureHunt_Item[3006951][2][14]["Log"] = "0,0,3006951,1,12000103,2,700023,1"
	tTheTreasureHunt_Item[3006951][2][14]["Global"] = 7
	tTheTreasureHunt_Item[3006951][2][14]["GlobalItem"] = 3
	
	
	
	
	-- 龙穴宝箱
	-- 龙穴宝箱（0转，1转）
	tTheTreasureHunt_Item[3007022] = {}
	tTheTreasureHunt_Item[3007022]["EmoneyMonoLimit"] = 999999799
	tTheTreasureHunt_Item[3007022]["Space"] = 1
	tTheTreasureHunt_Item[3007022]["Effect"] = "zf2-e280"
	
	tTheTreasureHunt_Item[3007022]["EmoneyBuyLog"] = "350	20081	0	0	1	"
	
	
	tTheTreasureHunt_Item[3007022][1] = {}
	tTheTreasureHunt_Item[3007022][1]["ItemChanceSum"] = 10000
	
-- 经验球大礼包（5颗）/727464	20.00%
	tTheTreasureHunt_Item[3007022][1][1] = {}
	tTheTreasureHunt_Item[3007022][1][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][1]["ItemChance"] = 2000
	tTheTreasureHunt_Item[3007022][1][1]["Item_1"] = 727464
	tTheTreasureHunt_Item[3007022][1][1]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][1]["Index"] = 1
	tTheTreasureHunt_Item[3007022][1][1]["Log"] = "0,0,3007022,1,12000103,2,727464,1"


-- 大块祈愿石	15%
	tTheTreasureHunt_Item[3007022][1][2] = {}
	tTheTreasureHunt_Item[3007022][1][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][2]["ItemChance"] = 1500
	tTheTreasureHunt_Item[3007022][1][2]["Item_1"] = 1200001
	tTheTreasureHunt_Item[3007022][1][2]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][2]["Index"] = 2
	tTheTreasureHunt_Item[3007022][1][2]["Log"] = "0,0,3007022,1,12000103,2,1200001,1"

-- 玄灵秘录大礼包/720894	15%
	tTheTreasureHunt_Item[3007022][1][3] = {}
	tTheTreasureHunt_Item[3007022][1][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][3]["ItemChance"] = 1500
	tTheTreasureHunt_Item[3007022][1][3]["Item_1"] = 720894
	tTheTreasureHunt_Item[3007022][1][3]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][3]["Index"] = 3
	tTheTreasureHunt_Item[3007022][1][3]["Log"] = "0,0,3007022,1,12000103,2,720894,1"

-- 赤炼石+2	15%
	tTheTreasureHunt_Item[3007022][1][4] = {}
	tTheTreasureHunt_Item[3007022][1][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][4]["ItemChance"] = 1500
	tTheTreasureHunt_Item[3007022][1][4]["Item_1"] = 730002
	tTheTreasureHunt_Item[3007022][1][4]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][4]["Index"] = 4
	tTheTreasureHunt_Item[3007022][1][4]["Log"] = "0,0,3007022,1,12000103,2,730002,1"
	tTheTreasureHunt_Item[3007022][1][4]["Global"] = 8
	tTheTreasureHunt_Item[3007022][1][4]["GlobalItem"] = 1
	
	
	
	
	
	
-- 赤炼石+3	8%
	tTheTreasureHunt_Item[3007022][1][5] = {}
	tTheTreasureHunt_Item[3007022][1][5]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][5]["ItemChance"] = 800
	tTheTreasureHunt_Item[3007022][1][5]["Item_1"] = 730003
	tTheTreasureHunt_Item[3007022][1][5]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][5]["Index"] = 5
	tTheTreasureHunt_Item[3007022][1][5]["Log"] = "0,0,3007022,1,12000103,2,730003,1"
	tTheTreasureHunt_Item[3007022][1][5]["Global"] = 9
	tTheTreasureHunt_Item[3007022][1][5]["GlobalItem"] = 1
	
	
	
-- 赤练石+5（赠）	1%
	tTheTreasureHunt_Item[3007022][1][6] = {}
	tTheTreasureHunt_Item[3007022][1][6]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][6]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][1][6]["Item_1"] = 730005
	tTheTreasureHunt_Item[3007022][1][6]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][1][6]["Index"] = 6
	tTheTreasureHunt_Item[3007022][1][6]["Log"] = "0,0,3007022,1,12000103,2,730005,1"
	tTheTreasureHunt_Item[3007022][1][6]["Global"] = 10
	tTheTreasureHunt_Item[3007022][1][6]["GlobalItem"] = 1
	
	
	
-- 马+3（赠）	4%
	tTheTreasureHunt_Item[3007022][1][7] = {}
	tTheTreasureHunt_Item[3007022][1][7]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][7]["ItemChance"] = 400
	tTheTreasureHunt_Item[3007022][1][7]["Item_1"] = 3007032
	tTheTreasureHunt_Item[3007022][1][7]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][1][7]["Index"] = 7
	tTheTreasureHunt_Item[3007022][1][7]["Log"] = "0,0,3007022,1,12000103,2,3007032,1"

-- 龙珠（赠）	1%
	tTheTreasureHunt_Item[3007022][1][8] = {}
	tTheTreasureHunt_Item[3007022][1][8]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][8]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][1][8]["Item_1"] = 1088000
	tTheTreasureHunt_Item[3007022][1][8]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][1][8]["Index"] = 8
	tTheTreasureHunt_Item[3007022][1][8]["Log"] = "0,0,3007022,1,12000103,2,1088000,1"
	tTheTreasureHunt_Item[3007022][1][8]["Global"] = 11
	tTheTreasureHunt_Item[3007022][1][8]["GlobalItem"] = 1
	
	
	
-- 流星卷10个打包/3004611	6%
	tTheTreasureHunt_Item[3007022][1][9] = {}
	tTheTreasureHunt_Item[3007022][1][9]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][9]["ItemChance"] = 600
	tTheTreasureHunt_Item[3007022][1][9]["Item_1"] = 3004611
	tTheTreasureHunt_Item[3007022][1][9]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][9]["Index"] = 9
	tTheTreasureHunt_Item[3007022][1][9]["Log"] = "0,0,3007022,1,12000103,2,3004611,1"
	tTheTreasureHunt_Item[3007022][1][9]["Global"] = 12
	tTheTreasureHunt_Item[3007022][1][9]["GlobalItem"] = 1
	
	
-- 二龙戏珠财富包/80万	8%
	tTheTreasureHunt_Item[3007022][1][10] = {}
	tTheTreasureHunt_Item[3007022][1][10]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][10]["ItemChance"] = 800
	tTheTreasureHunt_Item[3007022][1][10]["Item_1"] = 723714
	tTheTreasureHunt_Item[3007022][1][10]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][10]["Index"] = 10
	tTheTreasureHunt_Item[3007022][1][10]["Log"] = "0,0,3007022,1,12000103,2,723714,1"
	tTheTreasureHunt_Item[3007022][1][10]["Global"] = 13
	tTheTreasureHunt_Item[3007022][1][10]["GlobalItem"] = 1
	
	
	
-- 绑定天石*100	1%
	tTheTreasureHunt_Item[3007022][1][11] = {}
	tTheTreasureHunt_Item[3007022][1][11]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][11]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][1][11]["Item_1"] = 100
	tTheTreasureHunt_Item[3007022][1][11]["IsEmoney"] = true
	tTheTreasureHunt_Item[3007022][1][11]["Index"] = 11
	tTheTreasureHunt_Item[3007022][1][11]["Log"] = "0,0,3007022,1,12000103,2,3,100"
	tTheTreasureHunt_Item[3007022][1][11]["Global"] = 14
	tTheTreasureHunt_Item[3007022][1][11]["GlobalItem"] = 1
	
	
	
	
-- 优质龙恨宝石	3.00%
	tTheTreasureHunt_Item[3007022][1][12] = {}
	tTheTreasureHunt_Item[3007022][1][12]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][12]["ItemChance"] = 300
	tTheTreasureHunt_Item[3007022][1][12]["Item_1"] = 700013
	tTheTreasureHunt_Item[3007022][1][12]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][12]["Index"] = 12
	tTheTreasureHunt_Item[3007022][1][12]["Log"] = "0,0,3007022,1,12000103,2,700013,1"
	tTheTreasureHunt_Item[3007022][1][12]["Global"] = 15
	tTheTreasureHunt_Item[3007022][1][12]["GlobalItem"] = 1
	
	
	
-- 优质凤吟宝石	3.00%
	tTheTreasureHunt_Item[3007022][1][13] = {}
	tTheTreasureHunt_Item[3007022][1][13]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][1][13]["ItemChance"] = 300
	tTheTreasureHunt_Item[3007022][1][13]["Item_1"] = 700003
	tTheTreasureHunt_Item[3007022][1][13]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][1][13]["Index"] = 13
	tTheTreasureHunt_Item[3007022][1][13]["Log"] = "0,0,3007022,1,12000103,2,700003,1"
	tTheTreasureHunt_Item[3007022][1][13]["Global"] = 16
	tTheTreasureHunt_Item[3007022][1][13]["GlobalItem"] = 1
	
	
	
	-- 龙穴宝箱（2转）
	

	tTheTreasureHunt_Item[3007022][2]= {}
	tTheTreasureHunt_Item[3007022][2]["ItemChanceSum"] = 10000
-- 回气丹赠（500气力值）	10.00%
	tTheTreasureHunt_Item[3007022][2][1] = {}
	tTheTreasureHunt_Item[3007022][2][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][1]["ItemChance"] = 1000
	tTheTreasureHunt_Item[3007022][2][1]["Item_1"] = 729242
	tTheTreasureHunt_Item[3007022][2][1]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][2][1]["Index"] = 1
	tTheTreasureHunt_Item[3007022][2][1]["Log"] = "0,0,3007022,1,12000103,2,729242,1"

	
-- 梦幻强炼丹礼包/5个丹	20.00%
	tTheTreasureHunt_Item[3007022][2][2] = {}
	tTheTreasureHunt_Item[3007022][2][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][2]["ItemChance"] = 2000
	tTheTreasureHunt_Item[3007022][2][2]["Item_1"] = 3003134
	tTheTreasureHunt_Item[3007022][2][2]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][2]["Index"] = 2
	tTheTreasureHunt_Item[3007022][2][2]["Log"] = "0,0,3007022,1,12000103,2,3003134,1"


-- 梦幻通神丹（小爆丹）礼包/5个丹	20.00%
	tTheTreasureHunt_Item[3007022][2][3] = {}
	tTheTreasureHunt_Item[3007022][2][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][3]["ItemChance"] = 2000
	tTheTreasureHunt_Item[3007022][2][3]["Item_1"] = 3003141
	tTheTreasureHunt_Item[3007022][2][3]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][3]["Index"] = 3
	tTheTreasureHunt_Item[3007022][2][3]["Log"] = "0,0,3007022,1,12000103,2,3003141,1"

-- 强效护心丹	10.00%
	tTheTreasureHunt_Item[3007022][2][4] = {}
	tTheTreasureHunt_Item[3007022][2][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][4]["ItemChance"] = 1000
	tTheTreasureHunt_Item[3007022][2][4]["Item_1"] = 3002030
	tTheTreasureHunt_Item[3007022][2][4]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][4]["Index"] = 4
	tTheTreasureHunt_Item[3007022][2][4]["Log"] = "0,0,3007022,1,12000103,2,3002030,1"

-- 赤炼石+3	4.00%
	tTheTreasureHunt_Item[3007022][2][5] = {}
	tTheTreasureHunt_Item[3007022][2][5]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][5]["ItemChance"] = 400
	tTheTreasureHunt_Item[3007022][2][5]["Item_1"] = 730003
	tTheTreasureHunt_Item[3007022][2][5]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][5]["Index"] = 5
	tTheTreasureHunt_Item[3007022][2][5]["Log"] = "0,0,3007022,1,12000103,2,730003,1"



-- 赤炼石+6	0.05%
	tTheTreasureHunt_Item[3007022][2][6] = {}
	tTheTreasureHunt_Item[3007022][2][6]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][6]["ItemChance"] = 5
	tTheTreasureHunt_Item[3007022][2][6]["Item_1"] = 730006
	tTheTreasureHunt_Item[3007022][2][6]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][6]["Index"] = 6
	tTheTreasureHunt_Item[3007022][2][6]["Log"] = "0,0,3007022,1,12000103,2,730006,1"
	tTheTreasureHunt_Item[3007022][2][6]["Global"] = 17
	tTheTreasureHunt_Item[3007022][2][6]["GlobalItem"] = 3
	
	
-- 马+3	4.00%
	tTheTreasureHunt_Item[3007022][2][7] = {}
	tTheTreasureHunt_Item[3007022][2][7]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][7]["ItemChance"] = 400
	tTheTreasureHunt_Item[3007022][2][7]["Item_1"] = 727016
	tTheTreasureHunt_Item[3007022][2][7]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][7]["Index"] = 7
	tTheTreasureHunt_Item[3007022][2][7]["Log"] = "0,0,3007022,1,12000103,2,727016,1"


-- 马+6	0.05%	3002129
	tTheTreasureHunt_Item[3007022][2][8] = {}
	tTheTreasureHunt_Item[3007022][2][8]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][8]["ItemChance"] = 5
	tTheTreasureHunt_Item[3007022][2][8]["Item_1"] = 3002129
	tTheTreasureHunt_Item[3007022][2][8]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][8]["Index"] = 8
	tTheTreasureHunt_Item[3007022][2][8]["Log"] = "0,0,3007022,1,12000103,2,3002129,1"
	tTheTreasureHunt_Item[3007022][2][8]["Global"] = 18
	tTheTreasureHunt_Item[3007022][2][8]["GlobalItem"] = 3
	
	
-- 龙珠	1.00%
	tTheTreasureHunt_Item[3007022][2][9] = {}
	tTheTreasureHunt_Item[3007022][2][9]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][9]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][2][9]["Item_1"] = 1088000
	tTheTreasureHunt_Item[3007022][2][9]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][9]["Index"] = 9
	tTheTreasureHunt_Item[3007022][2][9]["Log"] = "0,0,3007022,1,12000103,2,1088000,1"
	tTheTreasureHunt_Item[3007022][2][9]["Global"] = 19
	tTheTreasureHunt_Item[3007022][2][9]["GlobalItem"] = 3
	
-- 龙珠卷	0.10%
	tTheTreasureHunt_Item[3007022][2][10] = {}
	tTheTreasureHunt_Item[3007022][2][10]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][10]["ItemChance"] = 10
	tTheTreasureHunt_Item[3007022][2][10]["Item_1"] = 720028
	tTheTreasureHunt_Item[3007022][2][10]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][10]["Index"] = 10
	tTheTreasureHunt_Item[3007022][2][10]["Log"] = "0,0,3007022,1,12000103,2,720028,1"
	tTheTreasureHunt_Item[3007022][2][10]["Global"] = 20
	tTheTreasureHunt_Item[3007022][2][10]["GlobalItem"] = 3

-- 流星卷10个打包/3004611	8.00%
	tTheTreasureHunt_Item[3007022][2][11] = {}
	tTheTreasureHunt_Item[3007022][2][11]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][11]["ItemChance"] = 800
	tTheTreasureHunt_Item[3007022][2][11]["Item_1"] = 3004611
	tTheTreasureHunt_Item[3007022][2][11]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][11]["Index"] = 11
	tTheTreasureHunt_Item[3007022][2][11]["Log"] = "0,0,3007022,1,12000103,2,3004611,1"
	tTheTreasureHunt_Item[3007022][2][11]["Global"] = 21
	tTheTreasureHunt_Item[3007022][2][11]["GlobalItem"] = 3


-- 优质玄元宝石	6.00%
	tTheTreasureHunt_Item[3007022][2][12] = {}
	tTheTreasureHunt_Item[3007022][2][12]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][12]["ItemChance"] = 600
	tTheTreasureHunt_Item[3007022][2][12]["Item_1"] = 700073
	tTheTreasureHunt_Item[3007022][2][12]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][12]["Index"] = 12
	tTheTreasureHunt_Item[3007022][2][12]["Log"] = "0,0,3007022,1,12000103,2,700073,1"
	tTheTreasureHunt_Item[3007022][2][12]["Global"] = 22
	tTheTreasureHunt_Item[3007022][2][12]["GlobalItem"] = 3
	
	
	
	
-- 优质天怒宝石	1.00%
	tTheTreasureHunt_Item[3007022][2][13] = {}
	tTheTreasureHunt_Item[3007022][2][13]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][13]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][2][13]["Item_1"] = 700103
	tTheTreasureHunt_Item[3007022][2][13]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][13]["Index"] = 13
	tTheTreasureHunt_Item[3007022][2][13]["Log"] = "0,0,3007022,1,12000103,2,700103,1"
	tTheTreasureHunt_Item[3007022][2][13]["Global"] = 23
	tTheTreasureHunt_Item[3007022][2][13]["GlobalItem"] = 3
	
	
	
	
	
-- 优质地灵宝石	1.00%
	tTheTreasureHunt_Item[3007022][2][14] = {}
	tTheTreasureHunt_Item[3007022][2][14]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][14]["ItemChance"] = 100
	tTheTreasureHunt_Item[3007022][2][14]["Item_1"] = 700123
	tTheTreasureHunt_Item[3007022][2][14]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][14]["Index"] = 14
	tTheTreasureHunt_Item[3007022][2][14]["Log"] = "0,0,3007022,1,12000103,2,700123,1"
	tTheTreasureHunt_Item[3007022][2][14]["Global"] = 24
	tTheTreasureHunt_Item[3007022][2][14]["GlobalItem"] = 3
	
	
-- 练气保护道具（赠）*1	0.80%
	tTheTreasureHunt_Item[3007022][2][15] = {}
	tTheTreasureHunt_Item[3007022][2][15]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][15]["ItemChance"] = 80
	tTheTreasureHunt_Item[3007022][2][15]["Item_1"] = 3005360
	tTheTreasureHunt_Item[3007022][2][15]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][2][15]["Index"] = 15
	tTheTreasureHunt_Item[3007022][2][15]["Log"] = "0,0,3007022,1,12000103,2,3005360,1"

-- 三元聚宝财富包/120万	8.00%
	tTheTreasureHunt_Item[3007022][2][16] = {}
	tTheTreasureHunt_Item[3007022][2][16]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][16]["ItemChance"] = 800
	tTheTreasureHunt_Item[3007022][2][16]["Item_1"] = 723715
	tTheTreasureHunt_Item[3007022][2][16]["ItemAttr"] = "0 1"
	tTheTreasureHunt_Item[3007022][2][16]["Index"] = 16
	tTheTreasureHunt_Item[3007022][2][16]["Log"] = "0,0,3007022,1,12000103,2,723715,1"
	tTheTreasureHunt_Item[3007022][2][16]["Global"] = 25
	tTheTreasureHunt_Item[3007022][2][16]["GlobalItem"] = 3
	
-- 绑定天石*200	2.00%
	tTheTreasureHunt_Item[3007022][2][17] = {}
	tTheTreasureHunt_Item[3007022][2][17]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][17]["ItemChance"] = 200
	tTheTreasureHunt_Item[3007022][2][17]["Item_1"] = 200
	tTheTreasureHunt_Item[3007022][2][17]["IsEmoney"] = true
	tTheTreasureHunt_Item[3007022][2][17]["Index"] = 17
	tTheTreasureHunt_Item[3007022][2][17]["Log"] = "0,0,3007022,1,12000103,2,3,200"
	tTheTreasureHunt_Item[3007022][2][17]["Global"] = 26
	tTheTreasureHunt_Item[3007022][2][17]["GlobalItem"] = 3

-- 固化石(赠)	4.00%
	tTheTreasureHunt_Item[3007022][2][18] = {}
	tTheTreasureHunt_Item[3007022][2][18]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Item[3007022][2][18]["ItemChance"] = 400
	tTheTreasureHunt_Item[3007022][2][18]["Item_1"] = 723694
	tTheTreasureHunt_Item[3007022][2][18]["ItemAttr"] = "0 1 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tTheTreasureHunt_Item[3007022][2][18]["Index"] = 18
	tTheTreasureHunt_Item[3007022][2][18]["Log"] = "0,0,3007022,1,12000103,2,723694,1"
	
-- 怪物数据
local tTheTreasureHunt_Monster = {}
	tTheTreasureHunt_Monster["nGenId"] = 17731
	tTheTreasureHunt_Monster["Money"] = 1000
	tTheTreasureHunt_Monster[1] = {}
	
	tTheTreasureHunt_Monster[1][1] = {}
	tTheTreasureHunt_Monster[1][1][1] = 7750
	tTheTreasureHunt_Monster[1][1][2] = 7751
	tTheTreasureHunt_Monster[1][1][3] = 7752
	tTheTreasureHunt_Monster[1][1][4] = 7753
	tTheTreasureHunt_Monster[1][1][5] = 7754
	tTheTreasureHunt_Monster[1][1][6] = 7755
	tTheTreasureHunt_Monster[1][1][7] = 7756
	tTheTreasureHunt_Monster[1][1][8] = 7757
	tTheTreasureHunt_Monster[1][1][9] = 7766
	
	
	tTheTreasureHunt_Monster[1][2] = {}
	tTheTreasureHunt_Monster[1][2][1] = 7758
	tTheTreasureHunt_Monster[1][2][2] = 7759
	tTheTreasureHunt_Monster[1][2][3] = 7760
	tTheTreasureHunt_Monster[1][2][4] = 7761
	tTheTreasureHunt_Monster[1][2][5] = 7762
	tTheTreasureHunt_Monster[1][2][6] = 7763
	tTheTreasureHunt_Monster[1][2][7] = 7764
	tTheTreasureHunt_Monster[1][2][8] = 7765
	tTheTreasureHunt_Monster[1][2][9] = 7767
	
	
	tTheTreasureHunt_Monster[2] = {}
	tTheTreasureHunt_Monster[2][1] = {}
	tTheTreasureHunt_Monster[2][1][1] = 7768
	tTheTreasureHunt_Monster[2][1][2] = 7769
	tTheTreasureHunt_Monster[2][1][3] = 7770
	tTheTreasureHunt_Monster[2][1][4] = 7771
	tTheTreasureHunt_Monster[2][1][5] = 7772
	tTheTreasureHunt_Monster[2][1][6] = 7773
	tTheTreasureHunt_Monster[2][1][7] = 7774
	tTheTreasureHunt_Monster[2][1][8] = 7775
	tTheTreasureHunt_Monster[2][1][9] = 7784
	
	tTheTreasureHunt_Monster[2][2] = {}
	tTheTreasureHunt_Monster[2][2][1] = 7776
	tTheTreasureHunt_Monster[2][2][2] = 7777
	tTheTreasureHunt_Monster[2][2][3] = 7778
	tTheTreasureHunt_Monster[2][2][4] = 7779
	tTheTreasureHunt_Monster[2][2][5] = 7780
	tTheTreasureHunt_Monster[2][2][6] = 7781
	tTheTreasureHunt_Monster[2][2][7] = 7782
	tTheTreasureHunt_Monster[2][2][8] = 7783
	tTheTreasureHunt_Monster[2][2][9] = 7785
		
	tTheTreasureHunt_Monster[3] = {}
	tTheTreasureHunt_Monster[3][1] = {}
	tTheTreasureHunt_Monster[3][1][1] = 7786
	tTheTreasureHunt_Monster[3][1][2] = 7787
	tTheTreasureHunt_Monster[3][1][3] = 7788
	tTheTreasureHunt_Monster[3][1][4] = 7789
	tTheTreasureHunt_Monster[3][1][5] = 7790
	tTheTreasureHunt_Monster[3][1][6] = 7791
	tTheTreasureHunt_Monster[3][1][7] = 7792
	tTheTreasureHunt_Monster[3][1][8] = 7793
	tTheTreasureHunt_Monster[3][1][9] = 7802
	
	tTheTreasureHunt_Monster[3][2] = {}
	tTheTreasureHunt_Monster[3][2][1] = 7794
	tTheTreasureHunt_Monster[3][2][2] = 7795
	tTheTreasureHunt_Monster[3][2][3] = 7796
	tTheTreasureHunt_Monster[3][2][4] = 7797
	tTheTreasureHunt_Monster[3][2][5] = 7798
	tTheTreasureHunt_Monster[3][2][6] = 7799
	tTheTreasureHunt_Monster[3][2][7] = 7800
	tTheTreasureHunt_Monster[3][2][8] = 7801
	tTheTreasureHunt_Monster[3][2][9] = 7803

	--怪物掉落
	--财宝铁箱(普通)
	tTheTreasureHunt_Monster[7750] = {}
	tTheTreasureHunt_Monster[7750]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7750]["Rank"] = 1
	tTheTreasureHunt_Monster[7750]["Mode"] = 1
	tTheTreasureHunt_Monster[7750]["Level"] = 1
	
	tTheTreasureHunt_Monster[7750][1] = {}
	tTheTreasureHunt_Monster[7750][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7750][1]["ItemChance"] = 2400
	tTheTreasureHunt_Monster[7750][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7750][1]["Index"] = 1
	tTheTreasureHunt_Monster[7750][1]["Log"] = "0,0,7750,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7750][2] = {}
	tTheTreasureHunt_Monster[7750][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7750][2]["ItemChance"] = 3200
	tTheTreasureHunt_Monster[7750][2]["Index"] = 2
	tTheTreasureHunt_Monster[7750][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7750][3] = {}
	tTheTreasureHunt_Monster[7750][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7750][3]["ItemChance"] = 4400
	tTheTreasureHunt_Monster[7750][3]["Index"] = 3
	
	--财宝铜箱(普通)
	tTheTreasureHunt_Monster[7751] = {}
	tTheTreasureHunt_Monster[7751]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7751]["Rank"] = 2
	tTheTreasureHunt_Monster[7751]["Mode"] = 1
	tTheTreasureHunt_Monster[7751]["Level"] = 1
	
	tTheTreasureHunt_Monster[7751][1] = {}
	tTheTreasureHunt_Monster[7751][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7751][1]["ItemChance"] = 3000
	tTheTreasureHunt_Monster[7751][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7751][1]["Index"] = 1
	tTheTreasureHunt_Monster[7751][1]["Log"] = "0,0,7751,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7751][2] = {}
	tTheTreasureHunt_Monster[7751][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7751][2]["ItemChance"] = 3000
	tTheTreasureHunt_Monster[7751][2]["Index"] = 2
	tTheTreasureHunt_Monster[7751][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7751][3] = {}
	tTheTreasureHunt_Monster[7751][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7751][3]["ItemChance"] = 4000
	tTheTreasureHunt_Monster[7751][3]["Index"] = 3
	
	--财宝银箱(普通)
	tTheTreasureHunt_Monster[7752] = {}
	tTheTreasureHunt_Monster[7752]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7752]["Rank"] = 3
	tTheTreasureHunt_Monster[7752]["Mode"] = 1
	tTheTreasureHunt_Monster[7752]["Level"] = 1
	
	tTheTreasureHunt_Monster[7752][1] = {}
	tTheTreasureHunt_Monster[7752][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7752][1]["ItemChance"] = 3600
	tTheTreasureHunt_Monster[7752][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7752][1]["Index"] = 1
	tTheTreasureHunt_Monster[7752][1]["Log"] = "0,0,7752,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7752][2] = {}
	tTheTreasureHunt_Monster[7752][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7752][2]["ItemChance"] = 2800
	tTheTreasureHunt_Monster[7752][2]["Index"] = 2
	tTheTreasureHunt_Monster[7752][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7752][3] = {}
	tTheTreasureHunt_Monster[7752][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7752][3]["ItemChance"] = 3600
	tTheTreasureHunt_Monster[7752][3]["Index"] = 3
	
	--财宝金箱(普通)
	tTheTreasureHunt_Monster[7753] = {}
	tTheTreasureHunt_Monster[7753]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7753]["Rank"] = 4
	tTheTreasureHunt_Monster[7753]["Mode"] = 1
	tTheTreasureHunt_Monster[7753]["Level"] = 1
	
	tTheTreasureHunt_Monster[7753][1] = {}
	tTheTreasureHunt_Monster[7753][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7753][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7753][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7753][1]["Index"] = 1
	tTheTreasureHunt_Monster[7753][1]["Log"] = "0,0,7753,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7753][2] = {}
	tTheTreasureHunt_Monster[7753][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7753][2]["ItemChance"] = 2600
	tTheTreasureHunt_Monster[7753][2]["Index"] = 2
	tTheTreasureHunt_Monster[7753][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7753][3] = {}
	tTheTreasureHunt_Monster[7753][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7753][3]["ItemChance"] = 3200
	tTheTreasureHunt_Monster[7753][3]["Index"] = 3
	
	--珍宝铁箱(普通)
	tTheTreasureHunt_Monster[7754] = {}
	tTheTreasureHunt_Monster[7754]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7754]["Rank"] = 5
	tTheTreasureHunt_Monster[7754]["Mode"] = 1
	tTheTreasureHunt_Monster[7754]["Level"] = 1
	
	tTheTreasureHunt_Monster[7754][1] = {}
	tTheTreasureHunt_Monster[7754][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7754][1]["ItemChance"] = 5200
	tTheTreasureHunt_Monster[7754][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7754][1]["Index"] = 1
	tTheTreasureHunt_Monster[7754][1]["Log"] = "0,0,7754,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7754][2] = {}
	tTheTreasureHunt_Monster[7754][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7754][2]["ItemChance"] = 2400
	tTheTreasureHunt_Monster[7754][2]["Index"] = 2
	tTheTreasureHunt_Monster[7754][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7754][3] = {}
	tTheTreasureHunt_Monster[7754][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7754][3]["ItemChance"] = 2400
	tTheTreasureHunt_Monster[7754][3]["Index"] = 3
	
	--珍宝铜箱(普通)
	tTheTreasureHunt_Monster[7755] = {}
	tTheTreasureHunt_Monster[7755]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7755]["Rank"] = 6
	tTheTreasureHunt_Monster[7755]["Mode"] = 1
	tTheTreasureHunt_Monster[7755]["Level"] = 1
	
	tTheTreasureHunt_Monster[7755][1] = {}
	tTheTreasureHunt_Monster[7755][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7755][1]["ItemChance"] = 6200
	tTheTreasureHunt_Monster[7755][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7755][1]["Index"] = 1
	tTheTreasureHunt_Monster[7755][1]["Log"] = "0,0,7755,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7755][2] = {}
	tTheTreasureHunt_Monster[7755][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7755][2]["ItemChance"] = 2200
	tTheTreasureHunt_Monster[7755][2]["Index"] = 2
	tTheTreasureHunt_Monster[7755][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7755][3] = {}
	tTheTreasureHunt_Monster[7755][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7755][3]["ItemChance"] = 1600
	tTheTreasureHunt_Monster[7755][3]["Index"] = 3
	
	
	--珍宝银箱(普通)
	tTheTreasureHunt_Monster[7756] = {}
	tTheTreasureHunt_Monster[7756]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7756]["Rank"] = 7
	tTheTreasureHunt_Monster[7756]["Mode"] = 1
	tTheTreasureHunt_Monster[7756]["Level"] = 1
	
	tTheTreasureHunt_Monster[7756][1] = {}
	tTheTreasureHunt_Monster[7756][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7756][1]["ItemChance"] = 7200
	tTheTreasureHunt_Monster[7756][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7756][1]["Index"] = 1
	tTheTreasureHunt_Monster[7756][1]["Log"] = "0,0,7756,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7756][2] = {}
	tTheTreasureHunt_Monster[7756][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7756][2]["ItemChance"] = 2000
	tTheTreasureHunt_Monster[7756][2]["Index"] = 2
	tTheTreasureHunt_Monster[7756][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7756][3] = {}
	tTheTreasureHunt_Monster[7756][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7756][3]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7756][3]["Index"] = 3
	
	--珍宝金箱(普通)
	tTheTreasureHunt_Monster[7757] = {}
	tTheTreasureHunt_Monster[7757]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7757]["Rank"] = 8
	tTheTreasureHunt_Monster[7757]["Mode"] = 1
	tTheTreasureHunt_Monster[7757]["Level"] = 1
	
	tTheTreasureHunt_Monster[7757][1] = {}
	tTheTreasureHunt_Monster[7757][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7757][1]["ItemChance"] = 8200
	tTheTreasureHunt_Monster[7757][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7757][1]["Index"] = 1
	tTheTreasureHunt_Monster[7757][1]["Log"] = "0,0,7757,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7757][2] = {}
	tTheTreasureHunt_Monster[7757][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7757][2]["ItemChance"] = 1800
	tTheTreasureHunt_Monster[7757][2]["Index"] = 2
	tTheTreasureHunt_Monster[7757][2]["Other"] = 1

	
	-- 财宝铁侍卫(普通)

	tTheTreasureHunt_Monster[7758] = {}
	tTheTreasureHunt_Monster[7758]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7758]["Rank"] = 1
	tTheTreasureHunt_Monster[7758]["Mode"] = 2
	tTheTreasureHunt_Monster[7758]["Level"] = 1
	
	tTheTreasureHunt_Monster[7758][1] = {}
	tTheTreasureHunt_Monster[7758][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7758][1]["ItemChance"] = 1200
	tTheTreasureHunt_Monster[7758][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7758][1]["Index"] = 1
	tTheTreasureHunt_Monster[7758][1]["Log"] = "0,0,7758,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7758][2] = {}
	tTheTreasureHunt_Monster[7758][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7758][2]["ItemChance"] = 3200
	tTheTreasureHunt_Monster[7758][2]["Index"] = 2
	tTheTreasureHunt_Monster[7758][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7758][3] = {}
	tTheTreasureHunt_Monster[7758][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7758][3]["ItemChance"] = 5600
	tTheTreasureHunt_Monster[7758][3]["Index"] = 3
	
	
	-- 财宝铜侍卫(普通)
	tTheTreasureHunt_Monster[7759] = {}
	tTheTreasureHunt_Monster[7759]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7759]["Rank"] = 2
	tTheTreasureHunt_Monster[7759]["Mode"] = 2
	tTheTreasureHunt_Monster[7759]["Level"] = 1
	
	tTheTreasureHunt_Monster[7759][1] = {}
	tTheTreasureHunt_Monster[7759][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7759][1]["ItemChance"] = 1500
	tTheTreasureHunt_Monster[7759][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7759][1]["Index"] = 1
	tTheTreasureHunt_Monster[7759][1]["Log"] = "0,0,7759,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7759][2] = {}
	tTheTreasureHunt_Monster[7759][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7759][2]["ItemChance"] = 3000
	tTheTreasureHunt_Monster[7759][2]["Index"] = 2
	tTheTreasureHunt_Monster[7759][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7759][3] = {}
	tTheTreasureHunt_Monster[7759][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7759][3]["ItemChance"] = 5500
	tTheTreasureHunt_Monster[7759][3]["Index"] = 3
	
	
	-- 财宝银侍卫(普通)
	tTheTreasureHunt_Monster[7760] = {}
	tTheTreasureHunt_Monster[7760]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7760]["Rank"] = 3
	tTheTreasureHunt_Monster[7760]["Mode"] = 2
	tTheTreasureHunt_Monster[7760]["Level"] = 1
	
	tTheTreasureHunt_Monster[7760][1] = {}
	tTheTreasureHunt_Monster[7760][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7760][1]["ItemChance"] = 1800
	tTheTreasureHunt_Monster[7760][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7760][1]["Index"] = 1
	tTheTreasureHunt_Monster[7760][1]["Log"] = "0,0,7760,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7760][2] = {}
	tTheTreasureHunt_Monster[7760][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7760][2]["ItemChance"] = 2800
	tTheTreasureHunt_Monster[7760][2]["Index"] = 2
	tTheTreasureHunt_Monster[7760][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7760][3] = {}
	tTheTreasureHunt_Monster[7760][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7760][3]["ItemChance"] = 5400
	tTheTreasureHunt_Monster[7760][3]["Index"] = 3
	

	-- 财宝金侍卫(普通)
	tTheTreasureHunt_Monster[7761] = {}
	tTheTreasureHunt_Monster[7761]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7761]["Rank"] = 4
	tTheTreasureHunt_Monster[7761]["Mode"] = 2
	tTheTreasureHunt_Monster[7761]["Level"] = 1
	
	tTheTreasureHunt_Monster[7761][1] = {}
	tTheTreasureHunt_Monster[7761][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7761][1]["ItemChance"] = 2100
	tTheTreasureHunt_Monster[7761][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7761][1]["Index"] = 1
	tTheTreasureHunt_Monster[7761][1]["Log"] = "0,0,7761,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7761][2] = {}
	tTheTreasureHunt_Monster[7761][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7761][2]["ItemChance"] = 2600
	tTheTreasureHunt_Monster[7761][2]["Index"] = 2
	tTheTreasureHunt_Monster[7761][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7761][3] = {}
	tTheTreasureHunt_Monster[7761][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7761][3]["ItemChance"] = 5300
	tTheTreasureHunt_Monster[7761][3]["Index"] = 3
	
	-- 珍宝铁侍卫(普通)
	tTheTreasureHunt_Monster[7762] = {}
	tTheTreasureHunt_Monster[7762]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7762]["Rank"] = 5
	tTheTreasureHunt_Monster[7762]["Mode"] = 2
	tTheTreasureHunt_Monster[7762]["Level"] = 1
	
	tTheTreasureHunt_Monster[7762][1] = {}
	tTheTreasureHunt_Monster[7762][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7762][1]["ItemChance"] = 2600
	tTheTreasureHunt_Monster[7762][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7762][1]["Index"] = 1
	tTheTreasureHunt_Monster[7762][1]["Log"] = "0,0,7762,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7762][2] = {}
	tTheTreasureHunt_Monster[7762][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7762][2]["ItemChance"] = 2400
	tTheTreasureHunt_Monster[7762][2]["Index"] = 2
	tTheTreasureHunt_Monster[7762][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7762][3] = {}
	tTheTreasureHunt_Monster[7762][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7762][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7762][3]["Index"] = 3
	
	-- 珍宝铜侍卫(普通)
	tTheTreasureHunt_Monster[7763] = {}
	tTheTreasureHunt_Monster[7763]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7763]["Rank"] = 6
	tTheTreasureHunt_Monster[7763]["Mode"] = 2
	tTheTreasureHunt_Monster[7763]["Level"] = 1
	
	tTheTreasureHunt_Monster[7763][1] = {}
	tTheTreasureHunt_Monster[7763][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7763][1]["ItemChance"] = 3100
	tTheTreasureHunt_Monster[7763][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7763][1]["Index"] = 1
	tTheTreasureHunt_Monster[7763][1]["Log"] = "0,0,7763,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7763][2] = {}
	tTheTreasureHunt_Monster[7763][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7763][2]["ItemChance"] = 2200
	tTheTreasureHunt_Monster[7763][2]["Index"] = 2
	tTheTreasureHunt_Monster[7763][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7763][3] = {}
	tTheTreasureHunt_Monster[7763][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7763][3]["ItemChance"] = 4700
	tTheTreasureHunt_Monster[7763][3]["Index"] = 3
	
	
	-- 珍宝银侍卫(普通)
	tTheTreasureHunt_Monster[7764] = {}
	tTheTreasureHunt_Monster[7764]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7764]["Rank"] = 7
	tTheTreasureHunt_Monster[7764]["Mode"] = 2
	tTheTreasureHunt_Monster[7764]["Level"] = 1
	
	tTheTreasureHunt_Monster[7764][1] = {}
	tTheTreasureHunt_Monster[7764][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7764][1]["ItemChance"] = 3600
	tTheTreasureHunt_Monster[7764][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7764][1]["Index"] = 1
	tTheTreasureHunt_Monster[7764][1]["Log"] = "0,0,7764,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7764][2] = {}
	tTheTreasureHunt_Monster[7764][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7764][2]["ItemChance"] = 2000
	tTheTreasureHunt_Monster[7764][2]["Index"] = 2
	tTheTreasureHunt_Monster[7764][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7764][3] = {}
	tTheTreasureHunt_Monster[7764][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7764][3]["ItemChance"] = 4400
	tTheTreasureHunt_Monster[7764][3]["Index"] = 3
	
	-- 珍宝金侍卫(普通)
	tTheTreasureHunt_Monster[7765] = {}
	tTheTreasureHunt_Monster[7765]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7765]["Rank"] = 8
	tTheTreasureHunt_Monster[7765]["Mode"] = 2
	tTheTreasureHunt_Monster[7765]["Level"] = 1
	
	tTheTreasureHunt_Monster[7765][1] = {}
	tTheTreasureHunt_Monster[7765][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7765][1]["ItemChance"] = 4100
	tTheTreasureHunt_Monster[7765][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7765][1]["Index"] = 1
	tTheTreasureHunt_Monster[7765][1]["Log"] = "0,0,7765,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7765][2] = {}
	tTheTreasureHunt_Monster[7765][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7765][2]["ItemChance"] = 1800
	tTheTreasureHunt_Monster[7765][2]["Index"] = 2
	tTheTreasureHunt_Monster[7765][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7765][3] = {}
	tTheTreasureHunt_Monster[7765][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7765][3]["ItemChance"] = 4100
	tTheTreasureHunt_Monster[7765][3]["Index"] = 3
	
-- 邪龙帝魂(普通)
	tTheTreasureHunt_Monster[7766] = {}
	tTheTreasureHunt_Monster[7766]["Rank"] = 9
	tTheTreasureHunt_Monster[7766]["Mode"] = 1
	tTheTreasureHunt_Monster[7766]["Level"] = 1
	tTheTreasureHunt_Monster[7766]["Item_1"] = {}
	tTheTreasureHunt_Monster[7766]["Item_1"][1] = 3006953
	tTheTreasureHunt_Monster[7766]["Item_1"][2] = 3007024
	tTheTreasureHunt_Monster[7766]["Item_1"][3] = 3007025
	tTheTreasureHunt_Monster[7766]["Item_1"][4] = 3007028
	tTheTreasureHunt_Monster[7766]["Num_1"] = {}
	tTheTreasureHunt_Monster[7766]["Num_1"][1] = 10
	tTheTreasureHunt_Monster[7766]["Num_1"][2] = 3
	tTheTreasureHunt_Monster[7766]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7766]["Num_1"][4] = 3
	

-- 邪龙王魂(普通)
	tTheTreasureHunt_Monster[7767] = {}
	tTheTreasureHunt_Monster[7767]["Rank"] = 9
	tTheTreasureHunt_Monster[7767]["Mode"] = 2
	tTheTreasureHunt_Monster[7767]["Level"] = 1
	tTheTreasureHunt_Monster[7767]["Item_1"] = {}
	tTheTreasureHunt_Monster[7767]["Item_1"][1] = 3006953
	tTheTreasureHunt_Monster[7767]["Item_1"][2] = 3007023
	tTheTreasureHunt_Monster[7767]["Item_1"][3] = 3007119
	tTheTreasureHunt_Monster[7767]["Item_1"][4] = 3007027
	tTheTreasureHunt_Monster[7767]["Num_1"] = {}
	tTheTreasureHunt_Monster[7767]["Num_1"][1] = 5
	tTheTreasureHunt_Monster[7767]["Num_1"][2] = 3
	tTheTreasureHunt_Monster[7767]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7767]["Num_1"][4] = 3
	
	
-- 财宝铁箱(危急)
	tTheTreasureHunt_Monster[7768] = {}
	tTheTreasureHunt_Monster[7768]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7768]["Rank"] = 1
	tTheTreasureHunt_Monster[7768]["Mode"] = 1
	tTheTreasureHunt_Monster[7768]["Level"] = 2
	
	tTheTreasureHunt_Monster[7768][1] = {}
	tTheTreasureHunt_Monster[7768][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7768][1]["ItemChance"] = 4800
	tTheTreasureHunt_Monster[7768][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7768][1]["Index"] = 1
	tTheTreasureHunt_Monster[7768][1]["Log"] = "0,0,7768,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7768][2] = {}
	tTheTreasureHunt_Monster[7768][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7768][2]["ItemChance"] = 2200
	tTheTreasureHunt_Monster[7768][2]["Index"] = 2
	tTheTreasureHunt_Monster[7768][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7768][3] = {}
	tTheTreasureHunt_Monster[7768][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7768][3]["ItemChance"] = 3000
	tTheTreasureHunt_Monster[7768][3]["Index"] = 3

-- 财宝铜箱(危急)
	tTheTreasureHunt_Monster[7769] = {}
	tTheTreasureHunt_Monster[7769]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7769]["Rank"] = 2
	tTheTreasureHunt_Monster[7769]["Mode"] = 1
	tTheTreasureHunt_Monster[7769]["Level"] = 2
	
	tTheTreasureHunt_Monster[7769][1] = {}
	tTheTreasureHunt_Monster[7769][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7769][1]["ItemChance"] = 6000
	tTheTreasureHunt_Monster[7769][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7769][1]["Index"] = 1
	tTheTreasureHunt_Monster[7769][1]["Log"] = "0,0,7769,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7769][2] = {}
	tTheTreasureHunt_Monster[7769][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7769][2]["ItemChance"] = 2000
	tTheTreasureHunt_Monster[7769][2]["Index"] = 2
	tTheTreasureHunt_Monster[7769][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7769][3] = {}
	tTheTreasureHunt_Monster[7769][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7769][3]["ItemChance"] = 2000
	tTheTreasureHunt_Monster[7769][3]["Index"] = 3

-- 财宝银箱(危急)
	tTheTreasureHunt_Monster[7770] = {}
	tTheTreasureHunt_Monster[7770]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7770]["Rank"] = 3
	tTheTreasureHunt_Monster[7770]["Mode"] = 1
	tTheTreasureHunt_Monster[7770]["Level"] = 2
	
	tTheTreasureHunt_Monster[7770][1] = {}
	tTheTreasureHunt_Monster[7770][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7770][1]["ItemChance"] = 7200
	tTheTreasureHunt_Monster[7770][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7770][1]["Index"] = 1
	tTheTreasureHunt_Monster[7770][1]["Log"] = "0,0,7770,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7770][2] = {}
	tTheTreasureHunt_Monster[7770][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7770][2]["ItemChance"] = 1800
	tTheTreasureHunt_Monster[7770][2]["Index"] = 2
	tTheTreasureHunt_Monster[7770][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7770][3] = {}
	tTheTreasureHunt_Monster[7770][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7770][3]["ItemChance"] = 1000
	tTheTreasureHunt_Monster[7770][3]["Index"] = 3

-- 财宝金箱(危急)
	tTheTreasureHunt_Monster[7771] = {}
	tTheTreasureHunt_Monster[7771]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7771]["Rank"] = 4
	tTheTreasureHunt_Monster[7771]["Mode"] = 1
	tTheTreasureHunt_Monster[7771]["Level"] = 2
	
	tTheTreasureHunt_Monster[7771][1] = {}
	tTheTreasureHunt_Monster[7771][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7771][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7771][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7771][1]["Index"] = 1
	tTheTreasureHunt_Monster[7771][1]["Log"] = "0,0,7771,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7771][2] = {}
	tTheTreasureHunt_Monster[7771][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7771][2]["ItemChance"] = 1600
	tTheTreasureHunt_Monster[7771][2]["Index"] = 2
	tTheTreasureHunt_Monster[7771][2]["Other"] = 1

-- 珍宝铁箱(危急)
	tTheTreasureHunt_Monster[7772] = {}
	tTheTreasureHunt_Monster[7772]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7772]["Rank"] = 5
	tTheTreasureHunt_Monster[7772]["Mode"] = 1
	tTheTreasureHunt_Monster[7772]["Level"] = 2
	
	tTheTreasureHunt_Monster[7772][1] = {}
	tTheTreasureHunt_Monster[7772][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7772][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7772][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7772][1]["Index"] = 1
	tTheTreasureHunt_Monster[7772][1]["Log"] = "0,0,7772,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7772][2] = {}
	tTheTreasureHunt_Monster[7772][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7772][2]["ItemChance"] = 1400
	tTheTreasureHunt_Monster[7772][2]["Index"] = 2
	tTheTreasureHunt_Monster[7772][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7772][3] = {}
	tTheTreasureHunt_Monster[7772][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7772][3]["ItemChance"] = 200
	tTheTreasureHunt_Monster[7772][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7772][3]["Index"] = 3
	tTheTreasureHunt_Monster[7772][3]["Log"] = "0,0,7772,1,12000103,2,3006951,1"
	
-- 珍宝铜箱(危急)
	tTheTreasureHunt_Monster[7773] = {}
	tTheTreasureHunt_Monster[7773]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7773]["Rank"] = 6
	tTheTreasureHunt_Monster[7773]["Mode"] = 1
	tTheTreasureHunt_Monster[7773]["Level"] = 2
	
	tTheTreasureHunt_Monster[7773][1] = {}
	tTheTreasureHunt_Monster[7773][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7773][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7773][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7773][1]["Index"] = 1
	tTheTreasureHunt_Monster[7773][1]["Log"] = "0,0,7773,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7773][2] = {}
	tTheTreasureHunt_Monster[7773][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7773][2]["ItemChance"] = 1200
	tTheTreasureHunt_Monster[7773][2]["Index"] = 2
	tTheTreasureHunt_Monster[7773][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7773][3] = {}
	tTheTreasureHunt_Monster[7773][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7773][3]["ItemChance"] = 400
	tTheTreasureHunt_Monster[7773][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7773][3]["Index"] = 3
	tTheTreasureHunt_Monster[7773][3]["Log"] = "0,0,7773,1,12000103,2,3006951,1"

-- 珍宝银箱(危急)
	tTheTreasureHunt_Monster[7774] = {}
	tTheTreasureHunt_Monster[7774]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7774]["Rank"] = 7
	tTheTreasureHunt_Monster[7774]["Mode"] = 1
	tTheTreasureHunt_Monster[7774]["Level"] = 2
	
	tTheTreasureHunt_Monster[7774][1] = {}
	tTheTreasureHunt_Monster[7774][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7774][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7774][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7774][1]["Index"] = 1
	tTheTreasureHunt_Monster[7774][1]["Log"] = "0,0,7773,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7774][2] = {}
	tTheTreasureHunt_Monster[7774][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7774][2]["ItemChance"] = 1000
	tTheTreasureHunt_Monster[7774][2]["Index"] = 2
	tTheTreasureHunt_Monster[7774][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7774][3] = {}
	tTheTreasureHunt_Monster[7774][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7774][3]["ItemChance"] = 600
	tTheTreasureHunt_Monster[7774][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7774][3]["Index"] = 3
	tTheTreasureHunt_Monster[7774][3]["Log"] = "0,0,7773,1,12000103,2,3006951,1"

-- 珍宝金箱(危急)
	tTheTreasureHunt_Monster[7775] = {}
	tTheTreasureHunt_Monster[7775]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7775]["Rank"] = 8
	tTheTreasureHunt_Monster[7775]["Mode"] = 1
	tTheTreasureHunt_Monster[7775]["Level"] = 2
	
	tTheTreasureHunt_Monster[7775][1] = {}
	tTheTreasureHunt_Monster[7775][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7775][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7775][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7775][1]["Index"] = 1
	tTheTreasureHunt_Monster[7775][1]["Log"] = "0,0,7775,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7775][2] = {}
	tTheTreasureHunt_Monster[7775][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7775][2]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7775][2]["Index"] = 2
	tTheTreasureHunt_Monster[7775][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7775][3] = {}
	tTheTreasureHunt_Monster[7775][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7775][3]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7775][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7775][3]["Index"] = 3
	tTheTreasureHunt_Monster[7775][3]["Log"] = "0,0,7775,1,12000103,2,3006951,1"
	
-- 财宝铁侍卫(危急)
	tTheTreasureHunt_Monster[7776] = {}
	tTheTreasureHunt_Monster[7776]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7776]["Rank"] = 1
	tTheTreasureHunt_Monster[7776]["Mode"] = 2
	tTheTreasureHunt_Monster[7776]["Level"] = 2
	
	tTheTreasureHunt_Monster[7776][1] = {}
	tTheTreasureHunt_Monster[7776][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7776][1]["ItemChance"] = 2400
	tTheTreasureHunt_Monster[7776][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7776][1]["Index"] = 1
	tTheTreasureHunt_Monster[7776][1]["Log"] = "0,0,7776,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7776][2] = {}
	tTheTreasureHunt_Monster[7776][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7776][2]["ItemChance"] = 1100
	tTheTreasureHunt_Monster[7776][2]["Index"] = 2
	tTheTreasureHunt_Monster[7776][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7776][3] = {}
	tTheTreasureHunt_Monster[7776][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7776][3]["ItemChance"] = 6500
	tTheTreasureHunt_Monster[7776][3]["Index"] = 3


-- 财宝铜侍卫(危急)
	tTheTreasureHunt_Monster[7777] = {}
	tTheTreasureHunt_Monster[7777]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7777]["Rank"] = 2
	tTheTreasureHunt_Monster[7777]["Mode"] = 2
	tTheTreasureHunt_Monster[7777]["Level"] = 2
	
	tTheTreasureHunt_Monster[7777][1] = {}
	tTheTreasureHunt_Monster[7777][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7777][1]["ItemChance"] = 3000
	tTheTreasureHunt_Monster[7777][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7777][1]["Index"] = 1
	tTheTreasureHunt_Monster[7777][1]["Log"] = "0,0,7777,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7777][2] = {}
	tTheTreasureHunt_Monster[7777][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7777][2]["ItemChance"] = 1000
	tTheTreasureHunt_Monster[7777][2]["Index"] = 2
	tTheTreasureHunt_Monster[7777][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7777][3] = {}
	tTheTreasureHunt_Monster[7777][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7777][3]["ItemChance"] = 6000
	tTheTreasureHunt_Monster[7777][3]["Index"] = 3


-- 财宝银侍卫(危急)
	tTheTreasureHunt_Monster[7778] = {}
	tTheTreasureHunt_Monster[7778]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7778]["Rank"] = 3
	tTheTreasureHunt_Monster[7778]["Mode"] = 2
	tTheTreasureHunt_Monster[7778]["Level"] = 2
	
	tTheTreasureHunt_Monster[7778][1] = {}
	tTheTreasureHunt_Monster[7778][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7778][1]["ItemChance"] = 3600
	tTheTreasureHunt_Monster[7778][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7778][1]["Index"] = 1
	tTheTreasureHunt_Monster[7778][1]["Log"] = "0,0,7778,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7778][2] = {}
	tTheTreasureHunt_Monster[7778][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7778][2]["ItemChance"] = 900
	tTheTreasureHunt_Monster[7778][2]["Index"] = 2
	tTheTreasureHunt_Monster[7778][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7778][3] = {}
	tTheTreasureHunt_Monster[7778][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7778][3]["ItemChance"] = 5500
	tTheTreasureHunt_Monster[7778][3]["Index"] = 3


-- 财宝金侍卫(危急)
	tTheTreasureHunt_Monster[7779] = {}
	tTheTreasureHunt_Monster[7779]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7779]["Rank"] = 4
	tTheTreasureHunt_Monster[7779]["Mode"] = 2
	tTheTreasureHunt_Monster[7779]["Level"] = 2
	
	tTheTreasureHunt_Monster[7779][1] = {}
	tTheTreasureHunt_Monster[7779][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7779][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7779][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7779][1]["Index"] = 1
	tTheTreasureHunt_Monster[7779][1]["Log"] = "0,0,7779,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7779][2] = {}
	tTheTreasureHunt_Monster[7779][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7779][2]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7779][2]["Index"] = 2
	tTheTreasureHunt_Monster[7779][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7779][3] = {}
	tTheTreasureHunt_Monster[7779][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7779][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7779][3]["Index"] = 3


-- 珍宝铁侍卫(危急)
	tTheTreasureHunt_Monster[7780] = {}
	tTheTreasureHunt_Monster[7780]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7780]["Rank"] = 5
	tTheTreasureHunt_Monster[7780]["Mode"] = 2
	tTheTreasureHunt_Monster[7780]["Level"] = 2
	
	tTheTreasureHunt_Monster[7780][1] = {}
	tTheTreasureHunt_Monster[7780][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7780][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7780][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7780][1]["Index"] = 1
	tTheTreasureHunt_Monster[7780][1]["Log"] = "0,0,7780,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7780][2] = {}
	tTheTreasureHunt_Monster[7780][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7780][2]["ItemChance"] = 700
	tTheTreasureHunt_Monster[7780][2]["Index"] = 2
	tTheTreasureHunt_Monster[7780][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7780][3] = {}
	tTheTreasureHunt_Monster[7780][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7780][3]["ItemChance"] = 100
	tTheTreasureHunt_Monster[7780][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7780][3]["Index"] = 3
	tTheTreasureHunt_Monster[7780][3]["Log"] = "0,0,7780,1,12000103,2,3006951,1"

	tTheTreasureHunt_Monster[7780][4] = {}
	tTheTreasureHunt_Monster[7780][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7780][4]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7780][4]["Index"] = 4
	
	
	
-- 珍宝铜侍卫(危急)
	tTheTreasureHunt_Monster[7781] = {}
	tTheTreasureHunt_Monster[7781]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7781]["Rank"] = 6
	tTheTreasureHunt_Monster[7781]["Mode"] = 2
	tTheTreasureHunt_Monster[7781]["Level"] = 2
	
	tTheTreasureHunt_Monster[7781][1] = {}
	tTheTreasureHunt_Monster[7781][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7781][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7781][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7781][1]["Index"] = 1
	tTheTreasureHunt_Monster[7781][1]["Log"] = "0,0,7781,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7781][2] = {}
	tTheTreasureHunt_Monster[7781][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7781][2]["ItemChance"] = 600
	tTheTreasureHunt_Monster[7781][2]["Index"] = 2
	tTheTreasureHunt_Monster[7781][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7781][3] = {}
	tTheTreasureHunt_Monster[7781][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7781][3]["ItemChance"] = 200
	tTheTreasureHunt_Monster[7781][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7781][3]["Index"] = 3
	tTheTreasureHunt_Monster[7781][3]["Log"] = "0,0,7781,1,12000103,2,3006951,1"

	tTheTreasureHunt_Monster[7781][4] = {}
	tTheTreasureHunt_Monster[7781][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7781][4]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7781][4]["Index"] = 4


-- 珍宝银侍卫(危急)
	tTheTreasureHunt_Monster[7782] = {}
	tTheTreasureHunt_Monster[7782]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7782]["Rank"] = 7
	tTheTreasureHunt_Monster[7782]["Mode"] = 2
	tTheTreasureHunt_Monster[7782]["Level"] = 2
	
	tTheTreasureHunt_Monster[7782][1] = {}
	tTheTreasureHunt_Monster[7782][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7782][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7782][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7782][1]["Index"] = 1
	tTheTreasureHunt_Monster[7782][1]["Log"] = "0,0,7782,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7782][2] = {}
	tTheTreasureHunt_Monster[7782][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7782][2]["ItemChance"] = 500
	tTheTreasureHunt_Monster[7782][2]["Index"] = 2
	tTheTreasureHunt_Monster[7782][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7782][3] = {}
	tTheTreasureHunt_Monster[7782][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7782][3]["ItemChance"] = 300
	tTheTreasureHunt_Monster[7782][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7782][3]["Index"] = 3
	tTheTreasureHunt_Monster[7782][3]["Log"] = "0,0,7782,1,12000103,2,3006951,1"

	tTheTreasureHunt_Monster[7782][4] = {}
	tTheTreasureHunt_Monster[7782][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7782][4]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7782][4]["Index"] = 4


-- 珍宝金侍卫(危急)
	tTheTreasureHunt_Monster[7783] = {}
	tTheTreasureHunt_Monster[7783]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7783]["Rank"] = 8
	tTheTreasureHunt_Monster[7783]["Mode"] = 2
	tTheTreasureHunt_Monster[7783]["Level"] = 2
	
	tTheTreasureHunt_Monster[7783][1] = {}
	tTheTreasureHunt_Monster[7783][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7783][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7783][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7783][1]["Index"] = 1
	tTheTreasureHunt_Monster[7783][1]["Log"] = "0,0,7783,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7783][2] = {}
	tTheTreasureHunt_Monster[7783][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7783][2]["ItemChance"] = 400
	tTheTreasureHunt_Monster[7783][2]["Index"] = 2
	tTheTreasureHunt_Monster[7783][2]["Other"] = 1
	
	tTheTreasureHunt_Monster[7783][3] = {}
	tTheTreasureHunt_Monster[7783][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7783][3]["ItemChance"] = 400
	tTheTreasureHunt_Monster[7783][3]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7783][3]["Index"] = 3
	tTheTreasureHunt_Monster[7783][3]["Log"] = "0,0,7783,1,12000103,2,3006951,1"

	tTheTreasureHunt_Monster[7783][4] = {}
	tTheTreasureHunt_Monster[7783][4]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7783][4]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7783][4]["Index"] = 4


-- 邪龙帝魂(危急)
	tTheTreasureHunt_Monster[7784] = {}
	tTheTreasureHunt_Monster[7784]["Rank"] = 9
	tTheTreasureHunt_Monster[7784]["Mode"] = 1
	tTheTreasureHunt_Monster[7784]["Level"] = 2
	tTheTreasureHunt_Monster[7784]["Item_1"] = {}
	tTheTreasureHunt_Monster[7784]["Item_1"][1] = 3006951
	tTheTreasureHunt_Monster[7784]["Item_1"][2] = 3006953
	tTheTreasureHunt_Monster[7784]["Item_1"][3] = 3007120
	tTheTreasureHunt_Monster[7784]["Item_1"][4] = 3007026
	tTheTreasureHunt_Monster[7784]["Item_1"][5] = 3007029
	tTheTreasureHunt_Monster[7784]["Num_1"] = {}
	tTheTreasureHunt_Monster[7784]["Num_1"][1] = 1
	tTheTreasureHunt_Monster[7784]["Num_1"][2] = 10
	tTheTreasureHunt_Monster[7784]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7784]["Num_1"][4] = 3
	tTheTreasureHunt_Monster[7784]["Num_1"][5] = 3
	
	
	
	
-- 邪龙王魂(危急)
	tTheTreasureHunt_Monster[7785] = {}
	tTheTreasureHunt_Monster[7785]["Rank"] = 9
	tTheTreasureHunt_Monster[7785]["Mode"] = 2
	tTheTreasureHunt_Monster[7785]["Level"] = 2
	tTheTreasureHunt_Monster[7785]["Item_1"] = {}
	tTheTreasureHunt_Monster[7785]["Item_1"][1] = 3006953
	tTheTreasureHunt_Monster[7785]["Item_1"][2] = 3007024
	tTheTreasureHunt_Monster[7785]["Item_1"][3] = 3007025
	tTheTreasureHunt_Monster[7785]["Item_1"][4] = 3007028
	tTheTreasureHunt_Monster[7785]["Num_1"] = {}
	tTheTreasureHunt_Monster[7785]["Num_1"][1] = 10
	tTheTreasureHunt_Monster[7785]["Num_1"][2] = 3
	tTheTreasureHunt_Monster[7785]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7785]["Num_1"][4] = 3


-- 财宝铁箱(致命)
	tTheTreasureHunt_Monster[7786] = {}
	tTheTreasureHunt_Monster[7786]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7786]["Rank"] = 1
	tTheTreasureHunt_Monster[7786]["Mode"] = 1
	tTheTreasureHunt_Monster[7786]["Level"] = 3
	
	tTheTreasureHunt_Monster[7786][1] = {}
	tTheTreasureHunt_Monster[7786][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7786][1]["ItemChance"] = 8000
	tTheTreasureHunt_Monster[7786][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7786][1]["Index"] = 1
	tTheTreasureHunt_Monster[7786][1]["Log"] = "0,0,7786,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7786][2] = {}
	tTheTreasureHunt_Monster[7786][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7786][2]["ItemChance"] = 2000
	tTheTreasureHunt_Monster[7786][2]["Index"] = 2
	tTheTreasureHunt_Monster[7786][2]["Other"] = 1

-- 财宝铜箱(致命)
	tTheTreasureHunt_Monster[7787] = {}
	tTheTreasureHunt_Monster[7787]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7787]["Rank"] = 2
	tTheTreasureHunt_Monster[7787]["Mode"] = 1
	tTheTreasureHunt_Monster[7787]["Level"] = 3
	
	tTheTreasureHunt_Monster[7787][1] = {}
	tTheTreasureHunt_Monster[7787][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7787][1]["ItemChance"] = 10000
	tTheTreasureHunt_Monster[7787][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7787][1]["Index"] = 1
	tTheTreasureHunt_Monster[7787][1]["Log"] = "0,0,7787,1,12000103,2,3006953,1"

-- 财宝银箱(致命)
	tTheTreasureHunt_Monster[7788] = {}
	tTheTreasureHunt_Monster[7788]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7788]["Rank"] = 3
	tTheTreasureHunt_Monster[7788]["Mode"] = 1
	tTheTreasureHunt_Monster[7788]["Level"] = 3
	
	tTheTreasureHunt_Monster[7788][1] = {}
	tTheTreasureHunt_Monster[7788][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7788][1]["ItemChance"] = 9800
	tTheTreasureHunt_Monster[7788][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7788][1]["Index"] = 1
	tTheTreasureHunt_Monster[7788][1]["Log"] = "0,0,7788,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7788][2] = {}
	tTheTreasureHunt_Monster[7788][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7788][2]["ItemChance"] = 200
	tTheTreasureHunt_Monster[7788][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7788][2]["Index"] = 2
	tTheTreasureHunt_Monster[7788][2]["Log"] = "0,0,7788,1,12000103,2,3006951,1"



-- 财宝金箱(致命)
	tTheTreasureHunt_Monster[7789] = {}
	tTheTreasureHunt_Monster[7789]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7789]["Rank"] = 4
	tTheTreasureHunt_Monster[7789]["Mode"] = 1
	tTheTreasureHunt_Monster[7789]["Level"] = 3
	
	tTheTreasureHunt_Monster[7789][1] = {}
	tTheTreasureHunt_Monster[7789][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7789][1]["ItemChance"] = 9600
	tTheTreasureHunt_Monster[7789][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7789][1]["Index"] = 1
	tTheTreasureHunt_Monster[7789][1]["Log"] = "0,0,7789,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7789][2] = {}
	tTheTreasureHunt_Monster[7789][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7789][2]["ItemChance"] = 400
	tTheTreasureHunt_Monster[7789][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7789][2]["Index"] = 2
	tTheTreasureHunt_Monster[7789][2]["Log"] = "0,0,7789,1,12000103,2,3006951,1"


-- 珍宝铁箱(致命)
	tTheTreasureHunt_Monster[7790] = {}
	tTheTreasureHunt_Monster[7790]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7790]["Rank"] = 5
	tTheTreasureHunt_Monster[7790]["Mode"] = 1
	tTheTreasureHunt_Monster[7790]["Level"] = 3
	
	tTheTreasureHunt_Monster[7790][1] = {}
	tTheTreasureHunt_Monster[7790][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7790][1]["ItemChance"] = 9200
	tTheTreasureHunt_Monster[7790][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7790][1]["Index"] = 1
	tTheTreasureHunt_Monster[7790][1]["Log"] = "0,0,7790,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7790][2] = {}
	tTheTreasureHunt_Monster[7790][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7790][2]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7790][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7790][2]["Index"] = 2
	tTheTreasureHunt_Monster[7790][2]["Log"] = "0,0,7790,1,12000103,2,3006951,1"

-- 珍宝铜箱(致命)
	tTheTreasureHunt_Monster[7791] = {}
	tTheTreasureHunt_Monster[7791]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7791]["Rank"] = 6
	tTheTreasureHunt_Monster[7791]["Mode"] = 1
	tTheTreasureHunt_Monster[7791]["Level"] = 3
	
	tTheTreasureHunt_Monster[7791][1] = {}
	tTheTreasureHunt_Monster[7791][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7791][1]["ItemChance"] = 8800
	tTheTreasureHunt_Monster[7791][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7791][1]["Index"] = 1
	tTheTreasureHunt_Monster[7791][1]["Log"] = "0,0,7791,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7791][2] = {}
	tTheTreasureHunt_Monster[7791][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7791][2]["ItemChance"] = 1200
	tTheTreasureHunt_Monster[7791][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7791][2]["Index"] = 2
	tTheTreasureHunt_Monster[7791][2]["Log"] = "0,0,7791,1,12000103,2,3006951,1"


-- 珍宝银箱(致命)
	tTheTreasureHunt_Monster[7792] = {}
	tTheTreasureHunt_Monster[7792]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7792]["Rank"] = 7
	tTheTreasureHunt_Monster[7792]["Mode"] = 1
	tTheTreasureHunt_Monster[7792]["Level"] = 3
	
	tTheTreasureHunt_Monster[7792][1] = {}
	tTheTreasureHunt_Monster[7792][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7792][1]["ItemChance"] = 8400
	tTheTreasureHunt_Monster[7792][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7792][1]["Index"] = 1
	tTheTreasureHunt_Monster[7792][1]["Log"] = "0,0,7792,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7792][2] = {}
	tTheTreasureHunt_Monster[7792][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7792][2]["ItemChance"] = 1600
	tTheTreasureHunt_Monster[7792][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7792][2]["Index"] = 2
	tTheTreasureHunt_Monster[7792][2]["Log"] = "0,0,7792,1,12000103,2,3006951,1"

-- 珍宝金箱(致命)
	tTheTreasureHunt_Monster[7793] = {}
	tTheTreasureHunt_Monster[7793]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7793]["Rank"] = 8
	tTheTreasureHunt_Monster[7793]["Mode"] = 1
	tTheTreasureHunt_Monster[7793]["Level"] = 3
	
	tTheTreasureHunt_Monster[7793][1] = {}
	tTheTreasureHunt_Monster[7793][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7793][1]["ItemChance"] = 8200
	tTheTreasureHunt_Monster[7793][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7793][1]["Index"] = 1
	tTheTreasureHunt_Monster[7793][1]["Log"] = "0,0,7793,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7793][2] = {}
	tTheTreasureHunt_Monster[7793][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7793][2]["ItemChance"] = 1800
	tTheTreasureHunt_Monster[7793][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7793][2]["Index"] = 2
	tTheTreasureHunt_Monster[7793][2]["Log"] = "0,0,7793,1,12000103,2,3006951,1"

-- 财宝铁侍卫(致命)
	tTheTreasureHunt_Monster[7794] = {}
	tTheTreasureHunt_Monster[7794]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7794]["Rank"] = 1
	tTheTreasureHunt_Monster[7794]["Mode"] = 2
	tTheTreasureHunt_Monster[7794]["Level"] = 3
	
	tTheTreasureHunt_Monster[7794][1] = {}
	tTheTreasureHunt_Monster[7794][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7794][1]["ItemChance"] = 4000
	tTheTreasureHunt_Monster[7794][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7794][1]["Index"] = 1
	tTheTreasureHunt_Monster[7794][1]["Log"] = "0,0,7794,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7794][2] = {}
	tTheTreasureHunt_Monster[7794][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7794][2]["ItemChance"] = 1000
	tTheTreasureHunt_Monster[7794][2]["Index"] = 2
	tTheTreasureHunt_Monster[7794][2]["Other"] = 1

	tTheTreasureHunt_Monster[7794][3] = {}
	tTheTreasureHunt_Monster[7794][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7794][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7794][3]["Index"] = 3
	tTheTreasureHunt_Monster[7794][3]["Other"] = 1
	
	
-- 财宝铜侍卫(致命)
	tTheTreasureHunt_Monster[7795] = {}
	tTheTreasureHunt_Monster[7795]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7795]["Rank"] = 2
	tTheTreasureHunt_Monster[7795]["Mode"] = 2
	tTheTreasureHunt_Monster[7795]["Level"] = 3
	
	tTheTreasureHunt_Monster[7795][1] = {}
	tTheTreasureHunt_Monster[7795][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7795][1]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7795][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7795][1]["Index"] = 1
	tTheTreasureHunt_Monster[7795][1]["Log"] = "0,0,7795,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7795][2] = {}
	tTheTreasureHunt_Monster[7795][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7795][2]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7795][2]["Index"] = 2


-- 财宝银侍卫(致命)
	tTheTreasureHunt_Monster[7796] = {}
	tTheTreasureHunt_Monster[7796]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7796]["Rank"] = 3
	tTheTreasureHunt_Monster[7796]["Mode"] = 2
	tTheTreasureHunt_Monster[7796]["Level"] = 3
	
	tTheTreasureHunt_Monster[7796][1] = {}
	tTheTreasureHunt_Monster[7796][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7796][1]["ItemChance"] = 4900
	tTheTreasureHunt_Monster[7796][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7796][1]["Index"] = 1
	tTheTreasureHunt_Monster[7796][1]["Log"] = "0,0,7796,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7796][2] = {}
	tTheTreasureHunt_Monster[7796][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7796][2]["ItemChance"] = 100
	tTheTreasureHunt_Monster[7796][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7796][2]["Index"] = 2
	tTheTreasureHunt_Monster[7796][2]["Log"] = "0,0,7796,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7796][3] = {}
	tTheTreasureHunt_Monster[7796][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7796][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7796][3]["Index"] = 3
	
	
-- 财宝金侍卫(致命)
	tTheTreasureHunt_Monster[7797] = {}
	tTheTreasureHunt_Monster[7797]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7797]["Rank"] = 4
	tTheTreasureHunt_Monster[7797]["Mode"] = 2
	tTheTreasureHunt_Monster[7797]["Level"] = 3
	
	tTheTreasureHunt_Monster[7797][1] = {}
	tTheTreasureHunt_Monster[7797][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7797][1]["ItemChance"] = 4800
	tTheTreasureHunt_Monster[7797][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7797][1]["Index"] = 1
	tTheTreasureHunt_Monster[7797][1]["Log"] = "0,0,7797,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7797][2] = {}
	tTheTreasureHunt_Monster[7797][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7797][2]["ItemChance"] = 200
	tTheTreasureHunt_Monster[7797][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7797][2]["Index"] = 2
	tTheTreasureHunt_Monster[7797][2]["Log"] = "0,0,7797,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7797][3] = {}
	tTheTreasureHunt_Monster[7797][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7797][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7797][3]["Index"] = 3

-- 珍宝铁侍卫(致命)
	tTheTreasureHunt_Monster[7798] = {}
	tTheTreasureHunt_Monster[7798]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7798]["Rank"] = 5
	tTheTreasureHunt_Monster[7798]["Mode"] = 2
	tTheTreasureHunt_Monster[7798]["Level"] = 3
	
	tTheTreasureHunt_Monster[7798][1] = {}
	tTheTreasureHunt_Monster[7798][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7798][1]["ItemChance"] = 4600
	tTheTreasureHunt_Monster[7798][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7798][1]["Index"] = 1
	tTheTreasureHunt_Monster[7798][1]["Log"] = "0,0,7798,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7798][2] = {}
	tTheTreasureHunt_Monster[7798][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7798][2]["ItemChance"] = 400
	tTheTreasureHunt_Monster[7798][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7798][2]["Index"] = 2
	tTheTreasureHunt_Monster[7798][2]["Log"] = "0,0,7798,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7798][3] = {}
	tTheTreasureHunt_Monster[7798][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7798][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7798][3]["Index"] = 3

-- 珍宝铜侍卫(致命)
	tTheTreasureHunt_Monster[7799] = {}
	tTheTreasureHunt_Monster[7799]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7799]["Rank"] = 6
	tTheTreasureHunt_Monster[7799]["Mode"] = 2
	tTheTreasureHunt_Monster[7799]["Level"] = 3
	
	tTheTreasureHunt_Monster[7799][1] = {}
	tTheTreasureHunt_Monster[7799][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7799][1]["ItemChance"] = 4400
	tTheTreasureHunt_Monster[7799][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7799][1]["Index"] = 1
	tTheTreasureHunt_Monster[7799][1]["Log"] = "0,0,7799,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7799][2] = {}
	tTheTreasureHunt_Monster[7799][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7799][2]["ItemChance"] = 600
	tTheTreasureHunt_Monster[7799][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7799][2]["Index"] = 2
	tTheTreasureHunt_Monster[7799][2]["Log"] = "0,0,7799,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7799][3] = {}
	tTheTreasureHunt_Monster[7799][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7799][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7799][3]["Index"] = 3

-- 珍宝银侍卫(致命)
	tTheTreasureHunt_Monster[7800] = {}
	tTheTreasureHunt_Monster[7800]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7800]["Rank"] = 7
	tTheTreasureHunt_Monster[7800]["Mode"] = 2
	tTheTreasureHunt_Monster[7800]["Level"] = 3
	
	tTheTreasureHunt_Monster[7800][1] = {}
	tTheTreasureHunt_Monster[7800][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7800][1]["ItemChance"] = 4200
	tTheTreasureHunt_Monster[7800][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7800][1]["Index"] = 1
	tTheTreasureHunt_Monster[7800][1]["Log"] = "0,0,7800,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7800][2] = {}
	tTheTreasureHunt_Monster[7800][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7800][2]["ItemChance"] = 800
	tTheTreasureHunt_Monster[7800][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7800][2]["Index"] = 2
	tTheTreasureHunt_Monster[7800][2]["Log"] = "0,0,7800,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7800][3] = {}
	tTheTreasureHunt_Monster[7800][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7800][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7800][3]["Index"] = 3

-- 珍宝金侍卫(致命)
	tTheTreasureHunt_Monster[7801] = {}
	tTheTreasureHunt_Monster[7801]["ItemChanceSum"] = 10000
	tTheTreasureHunt_Monster[7801]["Rank"] = 8
	tTheTreasureHunt_Monster[7801]["Mode"] = 2
	tTheTreasureHunt_Monster[7801]["Level"] = 3
	
	tTheTreasureHunt_Monster[7801][1] = {}
	tTheTreasureHunt_Monster[7801][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7801][1]["ItemChance"] = 4100
	tTheTreasureHunt_Monster[7801][1]["Item_1"] = 3006953
	tTheTreasureHunt_Monster[7801][1]["Index"] = 1
	tTheTreasureHunt_Monster[7801][1]["Log"] = "0,0,7801,1,12000103,2,3006953,1"

	tTheTreasureHunt_Monster[7801][2] = {}
	tTheTreasureHunt_Monster[7801][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7801][2]["ItemChance"] = 900
	tTheTreasureHunt_Monster[7801][2]["Item_1"] = 3006951
	tTheTreasureHunt_Monster[7801][2]["Index"] = 2
	tTheTreasureHunt_Monster[7801][2]["Log"] = "0,0,7801,1,12000103,2,3006951,1"
	
	tTheTreasureHunt_Monster[7801][3] = {}
	tTheTreasureHunt_Monster[7801][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster[7801][3]["ItemChance"] = 5000
	tTheTreasureHunt_Monster[7801][3]["Index"] = 3

-- 邪龙帝魂(致命)
	tTheTreasureHunt_Monster[7802] = {}
	tTheTreasureHunt_Monster[7802]["Rank"] = 9
	tTheTreasureHunt_Monster[7802]["Mode"] = 1
	tTheTreasureHunt_Monster[7802]["Level"] = 3
	tTheTreasureHunt_Monster[7802]["Item_1"] = {}
	tTheTreasureHunt_Monster[7802]["Item_1"][1] = 3006951
	tTheTreasureHunt_Monster[7802]["Item_1"][2] = 3006953
	tTheTreasureHunt_Monster[7802]["Item_1"][3] = 3007120
	tTheTreasureHunt_Monster[7802]["Item_1"][4] = 3007121
	tTheTreasureHunt_Monster[7802]["Item_1"][5] = 3007026
	tTheTreasureHunt_Monster[7802]["Item_1"][6] = 3007029
	tTheTreasureHunt_Monster[7802]["Num_1"] = {}
	tTheTreasureHunt_Monster[7802]["Num_1"][1] = 3
	tTheTreasureHunt_Monster[7802]["Num_1"][2] = 4
	tTheTreasureHunt_Monster[7802]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7802]["Num_1"][4] = 3
	tTheTreasureHunt_Monster[7802]["Num_1"][5] = 3
	tTheTreasureHunt_Monster[7802]["Num_1"][6] = 3
	
	
	-- 邪龙王魂(致命)
	tTheTreasureHunt_Monster[7803] = {}
	tTheTreasureHunt_Monster[7803]["Rank"] = 9
	tTheTreasureHunt_Monster[7803]["Mode"] = 2
	tTheTreasureHunt_Monster[7803]["Level"] = 3
	tTheTreasureHunt_Monster[7803]["Item_1"] = {}
	tTheTreasureHunt_Monster[7803]["Item_1"][1] = 3006951
	tTheTreasureHunt_Monster[7803]["Item_1"][2] = 3006953
	tTheTreasureHunt_Monster[7803]["Item_1"][3] = 3007024
	tTheTreasureHunt_Monster[7803]["Item_1"][4] = 3007122
	tTheTreasureHunt_Monster[7803]["Item_1"][5] = 3007025
	tTheTreasureHunt_Monster[7803]["Item_1"][6] = 3007028
	tTheTreasureHunt_Monster[7803]["Num_1"] = {}
	tTheTreasureHunt_Monster[7803]["Num_1"][1] = 1
	tTheTreasureHunt_Monster[7803]["Num_1"][2] = 7
	tTheTreasureHunt_Monster[7803]["Num_1"][3] = 3
	tTheTreasureHunt_Monster[7803]["Num_1"][4] = 3
	tTheTreasureHunt_Monster[7803]["Num_1"][5] = 3
	tTheTreasureHunt_Monster[7803]["Num_1"][6] = 3
	
	
--其他奖励
	tTheTreasureHunt_Monster["Other"] = {}
	tTheTreasureHunt_Monster["Other"]["ItemChanceSum"] = 10000

	tTheTreasureHunt_Monster["Other"][1] = {}
	tTheTreasureHunt_Monster["Other"][1]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster["Other"][1]["ItemChance"] = 5000
	tTheTreasureHunt_Monster["Other"][1]["Item_1"] = 1088001
	tTheTreasureHunt_Monster["Other"][1]["Index"] = 1
	tTheTreasureHunt_Monster["Other"][1]["Log"] = "0,0,0,0,12000103,2,1088001,1"
	
	tTheTreasureHunt_Monster["Other"][2] = {}
	tTheTreasureHunt_Monster["Other"][2]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster["Other"][2]["ItemChance"] = 3500
	tTheTreasureHunt_Monster["Other"][2]["Item_1"] = 723340
	tTheTreasureHunt_Monster["Other"][2]["Index"] = 2
	tTheTreasureHunt_Monster["Other"][2]["Log"] = "0,0,0,0,12000103,2,723340,1"
	
	tTheTreasureHunt_Monster["Other"][3] = {}
	tTheTreasureHunt_Monster["Other"][3]["RandomItemChanceType"] = 2
	tTheTreasureHunt_Monster["Other"][3]["ItemChance"] = 1500
	tTheTreasureHunt_Monster["Other"][3]["Item_1"] = 3003878
	tTheTreasureHunt_Monster["Other"][3]["Index"] = 3
	tTheTreasureHunt_Monster["Other"][3]["Log"] = "0,0,0,0,12000103,2,3003878,1"
	
local tTheTreasureHunt_BuyCharacter = {}
	tTheTreasureHunt_BuyCharacter["Emoney"] = 1
	-- tTheTreasureHunt_BuyCharacter["Item_1"] = 3006950
	-- tTheTreasureHunt_BuyCharacter["ItemAttr"] = "0 1"
	tTheTreasureHunt_BuyCharacter["Log"] = "1,0,0,0,12000134,2,143[144][141][142][133][134],1000[1000][1000][1000][10][10]"
	
	
--------------------------------------逻辑部分-------------------------------------------
--进入禁闭龙穴。
function TheTreasureHunt_Option4_18711(nNpcId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nLevel = Get_UserStatisticValue(nEvent,nLevelType)

	local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][2]
	
	
	if nLevel == 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
	else
		if Task_ChkStcValue(nEvent,nRankType,"==",tTheTreasureHunt_Constant["Complete"]) then
			if not Task_StcInterval(nEvent,nRankType,1,4) then
				LinkNpcGossipFunc_New(nNpcId,"2-1")
				return
			end
		end
	
		if Task_StcInterval(nEvent,nLevelType,1,4) then
		-- 隔天清掩码
			Task_SetStatistic(nEvent,nLevelType,0,1)
			Task_SetStcTimestamp(nEvent,nLevelType,0)
			Task_SetStatistic(nEvent,nRankType,0,1)
			Task_SetStcTimestamp(nEvent,nRankType,0)
			Task_SetStatistic(nEvent1,nType1,0,1)
			LinkNpcGossipFunc_New(nNpcId,"2-3")
		
			return
		end

		LinkNpcGossipFunc_New(nNpcId,"2-2")
		
		
	end
	
end

--进入龙穴
function TheTreasureHunt_EnterCave(nNpcId)
	if not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end
	
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	local nLev = Get_UserStatisticValue(nEvent,nLevelType)
	
	if Task_StcInterval(nEvent,nLevelType,1,4) then
		TheTreasureHunt_Option4_18711(nNpcId)
	else
		TheTreasureHunt_SelectionDifficulty(nNpcId,nLev)
		-- TheTreasureHunt_CreateCopy(nNpcId,nLev)
	end

end

--创建副本
function TheTreasureHunt_CreateCopy(nNpcId,nLev)

	local nTeamNum = Get_UserTeamNumbers()
	--判断玩家是否组队
	if nTeamNum > 1 then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	local nMapId = Get_UserMapId()
	local nNpcMapId = Get_NpcMapID()
	
	if nMapId ~= nNpcMapId then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	
	local nInstanceType = tTheTreasureHunt_Constant["InstanceType"][nLev]
	local nNumLimit = tTheTreasureHunt_Constant["nNumLimit"]
	local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][1]
	local nDelay = tTheTreasureHunt_Constant["EnterTimeLimit"]
	
	if not Task_StcInterval(nEvent1,nType1,nDelay,1) then
		LinkNpcGossipFunc_New(nNpcId,"6-1")
		return
	end
	

	-- Task_SetStatistic(nEvent1,nType1,0,1)
	-- Task_SetStcTimestamp(nEvent1,nType1,0)
	User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],tTheTreasureHunt_Constant["Effect_1"])
	User_EnterInstance(nInstanceType,nNumLimit)
	User_TalkChannel2005(tTheTreasureHunt_Text["EnterCave"])
	
	Sys_SaveActionFestivalLog(tTheTreasureHunt_Constant["CopyLog"][nLev])
	
	TheTreasureHunt_MissionStart()
	
	
end

--选择难度
function TheTreasureHunt_SelectionDifficulty(nNpcId,nLev)

	if not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end
	
	local nPower = Get_UserBattleLevel()
	local nPowerLimit = tTheTreasureHunt_Power[nLev]

	
	if nPowerLimit ~= nil then
		if nPower >= nPowerLimit then
			if nLev == 1 then
				LinkNpcGossipFunc_New(nNpcId,"2-6")
				return
			else
				LinkNpcGossipFunc_New(nNpcId,"2-7")
				return
			end
		end
	end
	
	local nPowerLimit1 = tTheTreasureHunt_Power1[nLev]
	if nPowerLimit1 ~= nil then
		if nPower <= nPowerLimit1 then
			if nLev == 2 then
				LinkNpcGossipFunc_New(nNpcId,"6-2")
				return
			else
				LinkNpcGossipFunc_New(nNpcId,"6-3")
				return
			end
		end
	end
	
	TheTreasureHunt_SetDifficulty(nNpcId,nLev)
	
end

--设定难度（打掩码）
function TheTreasureHunt_SetDifficulty(nNpcId,nLev)

	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]

	Task_SetStatistic(nEvent,nLevelType,nLev,1)
	Task_SetStcTimestamp(nEvent,nLevelType,0)
	
	if Task_StcInterval(nEvent,nLevelType,1,4) then
	-- 隔天重新打时间戳
		Task_SetStcTimestamp(nEvent,nRankType,0)
	end
	--创建副本
	Sys_SaveEmoneyBuy("350	20078	0	0	1	")

	TheTreasureHunt_CreateCopy(nNpcId,nLev)
end

--隔天动态存储表赋值
function TheTreasureHunt_SaveTaskGlobal()
	local nGlobalId = tTheTreasureHunt_TaskGlobal[4]["GlobalId"]
	local nData = Get_SysDynaGlobalData0(nGlobalId)
	if Sys_ChkDayTime(tTheTreasureHunt_Constant["ClearTime"]) then
		if nData == 0 then
			for i = 1,3 do
				local nGlobal = tTheTreasureHunt_TaskGlobal[i]["GlobalId"]
				local nData0 = Get_SysDynaGlobalData0(nGlobal)
				local nData1 = Get_SysDynaGlobalData1(nGlobal)
				local nData2 = Get_SysDynaGlobalData2(nGlobal)
				local sDataStr0 = Get_SysDynaGlobalDataStr0(nGlobal)
				local sDataStr1 = Get_SysDynaGlobalDataStr1(nGlobal)
				local sDataStr2 = Get_SysDynaGlobalDataStr2(nGlobal)
				
				Sys_SetSynaGlobalData3(nGlobal,nData0)
				Sys_SetSynaGlobalData4(nGlobal,nData1)
				Sys_SetSynaGlobalData5(nGlobal,nData2)
				Sys_SetSynaGlobalDataStr3(nGlobal,sDataStr0)
				Sys_SetSynaGlobalDataStr4(nGlobal,sDataStr1)
				Sys_SetSynaGlobalDataStr5(nGlobal,sDataStr2)
				
				Sys_SetSynaGlobalData0(nGlobal,0)
				Sys_SetSynaGlobalData1(nGlobal,0)
				Sys_SetSynaGlobalData2(nGlobal,0)
				Sys_SetSynaGlobalDataStr0(nGlobal,tTheTreasureHunt_Text["None"])
				Sys_SetSynaGlobalDataStr1(nGlobal,tTheTreasureHunt_Text["None"])
				Sys_SetSynaGlobalDataStr2(nGlobal,tTheTreasureHunt_Text["None"])
				Sys_ResetAllSynaGlobalData(tTheTreasureHunt_RankingGlobal[1]["GlobalId"])
				Sys_ResetAllSynaGlobalData(tTheTreasureHunt_RankingGlobal[3]["GlobalId"])
			end
			
			Sys_SetSynaGlobalData0(nGlobalId,1)
			
		end
	else
		Sys_SetSynaGlobalData0(nGlobalId,0)
	end
	
end
 
 --判断是否是前三名
function TheTreasureHunt_IsTopThree(nNpcId,nGlobalId)
	if not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		if not Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"]) then
			LinkNpcGossipFunc_New(nNpcId,"1-2")
			return
		end
	end
	TheTreasureHunt_SaveTaskGlobal()
	local nUserID = Get_UserId()
	local nData3 = Get_SysDynaGlobalData3(nGlobalId)
	local nData4 = Get_SysDynaGlobalData4(nGlobalId)
	local nData5 = Get_SysDynaGlobalData5(nGlobalId) 
	local nRank = 0
	
	if nUserID ~= nData3 and nUserID ~= nData4 and nUserID ~= nData5 then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return
	end
	
	if nUserID == nData3 then
		nRank = 1 
	elseif nUserID == nData4 then
		nRank = 2
	else
		nRank = 3
	end
	
	
	TheTreasureHunt_ReceiveReward(nNpcId,nGlobalId,nRank)

end

--领取奖励
function TheTreasureHunt_ReceiveReward(nNpcId,nGlobalId,nRank)
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nType = tTheTreasureHunt_Stc["DataType"][3]
	
	if not Task_StcInterval(nEvent,nType,1,4) then
		LinkNpcGossipFunc_New(nNpcId,"3-6")
		return
	end
	
	local nSpace = tTheTreasureHunt_Reward[nGlobalId][nRank]["Space"]
	
	if not User_CheckLeftSpace(nSpace) then
		LinkNpcGossipFunc_New(nNpcId,"3-7")
		return
	end
	
	local sLog = tTheTreasureHunt_Reward[nGlobalId][nRank]["Log"]
	local nGetItemId = tTheTreasureHunt_Reward[nGlobalId][nRank]["ItemId"]
	local nGetItemAttr = tTheTreasureHunt_Reward[nGlobalId][nRank]["ItemAttr"]
	
	
	Task_SetStatistic(nEvent,nType,1,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	-- 给修行值
	if tTheTreasureHunt_Reward[nGlobalId][nRank]["Cultivation"] then
		User_AddCultivation(tTheTreasureHunt_Reward[nGlobalId][nRank]["Cultivation"])
	end
	
	-- 给气力值
	if tTheTreasureHunt_Reward[nGlobalId][nRank]["Strengthvalue"] then
		User_AddStrengthValue(tTheTreasureHunt_Reward[nGlobalId][nRank]["Strengthvalue"])
	end
	
	-- 获得物品
	if nGetItemId ~= nil then
		Item_AddNewItem(nGetItemId,nGetItemAttr) 
	end
	
	-- 打log
	Sys_SaveActionFestivalLog(sLog)
	
	if nGlobalId == tTheTreasureHunt_TaskGlobal[1]["GlobalId"] then
		LinkNpcGossipFunc_New(nNpcId,"3-8")
	elseif	nGlobalId == tTheTreasureHunt_TaskGlobal[2]["GlobalId"] then
		LinkNpcGossipFunc_New(nNpcId,"3-9")
	else
		LinkNpcGossipFunc_New(nNpcId,"3-10")
	end
end

--开始闯关
function TheTreasureHunt_MissionStart()

	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	
	-- local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	-- local nType1 = tTheTreasureHunt_Stc["DataType1"][2]
	
	-- Task_SetStatistic(nEvent1,nType1,1,1)
	-- Task_SetStcTimestamp(nEvent1,nType1,0)
	
	local nLevel = Get_UserStatisticValue(nEvent,nLevelType)
	local nMapId = Get_UserMapId()
	local nMode = 1
	local nRank = 1
	local nNum = 5
	
	TheTreasureHunt_GetTime()
	TheTreasureHunt_BrushMonster(nMapId,nLevel,nMode,nRank,nNum)
	
	Sys_SetLuaTimer(tTheTreasureHunt_Constant["DelayTime"],string.format("TheTreasureHunt_BrushRound</N>%d</N>%d</N>%d</N>%d</N>%d",nMapId,nLevel,nMode,nRank,nNum))

end

--获得开始时间
function TheTreasureHunt_GetTime()
	local nEvent = tTheTreasureHunt_Stc["EventType1"]
	local nType = tTheTreasureHunt_Stc["DataType1"][1]
	Task_SetStatistic(nEvent,nType,1,1)
	Task_SetStcTimestamp(nEvent,nType,0)
end

--	
--刷出怪
function TheTreasureHunt_BrushMonster(nMapId,nLevel,nMode,nRank,nNum)
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nRank1 = Get_UserStatisticValue(nEvent,nRankType)
	
	local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][2]
	
	local nType2 = tTheTreasureHunt_Stc["DataType1"][4]
	
	Task_SetStatistic(nEvent1,nType2,0,1)
	
	if IsDropRank(nRank,nRank1) then
		if nRank1 ~= nRank then
			Task_SetStatistic(nEvent1,nType1,0,1)
		end
		Task_SetStatistic(nEvent,nRankType,nRank,1)
	end

	local nMonsterId = tTheTreasureHunt_Monster[nLevel][nMode][nRank]
	local nGenId = tTheTreasureHunt_Monster["nGenId"]
	
	
	for i = 1,nNum do
		if i > 5 then
			break
		end
		local nCellx = tTheTreasureHunt_BrushMonster[nMode]["CellX"][i]
		local nCelly = tTheTreasureHunt_BrushMonster[nMode]["CellY"][i]
		Monster_AddMonster(nMapId,nCellx,nCelly,nGenId,nMonsterId)
	end
	
	if nMode == 1 then
		User_TalkChannel2005(string.format(tTheTreasureHunt_BrushMonsterText[nMode],tTheTreasureHunt_MonsterNameText[nMonsterId]))
	else
		local nMonId = tTheTreasureHunt_Monster[nLevel][1][nRank]
		User_TalkChannel2005(string.format(tTheTreasureHunt_BrushMonsterText[nMode],tTheTreasureHunt_MonsterNameText[nMonId],tTheTreasureHunt_MonsterNameText[nMonsterId]))
	end
	

	if nMode == 1 then
		User_SetTimer(tTheTreasureHunt_Constant["DelayTime"],sFunc,1)
	
	end
	
end

---判断是否还存在宝箱刷怪
function TheTreasureHunt_BrushRound(nMapId,nLevel,nMode,nRank,nNum)
	
	local nMonsterId = tTheTreasureHunt_Monster[nLevel][nMode][nRank]
	nNum = Monster_GetMonsterByName(nMapId,tTheTreasureHunt_MonsterNameText[nMonsterId])

	if nNum > 0 then
		nMode = 2

		Monster_DelMonster(nMapId,nMonsterId)
		TheTreasureHunt_BrushMonster(nMapId,nLevel,nMode,nRank,nNum)
		return
	end

end

--打开商店
-- function TheTreasureHunt_OpenStore(nNpcId)
	-- User_OpenDialog(0,nNpcId)
-- end
--购买
function TheTreasureHunt_BuyCharacter(nNpcId)
	-- 判断背包空间
	-- if not User_CheckLeftSpace(1) then
		-- User_TalkChannel2005(tTheTreasureHunt_Text["NoSpace"])
		-- return
	-- end
	
	local nUserEmoney = Get_UserEMoney()

	if nUserEmoney < tTheTreasureHunt_BuyCharacter["Emoney"] then
		-- 天石数量不足提示
		User_TalkChannel2005(tTheTreasureHunt_Text["NoEmoney"])
		return
	end
	
	if not TheTreasureHunt_IsInMap() then
		User_TalkChannel2005(tTheTreasureHunt_Text["BraveNoUse"])
		return
	end
	
	local i = 0
	local nUserId = Get_UserId()
	
	for j = 1,6 do
		local nStatus = tTheTreasureHunt_Brave[j] 
		if User_ChkRoleStatus(nStatus,nUserId) then
			i = i + 1
		end
	end
	
	if i == 6 then 
		User_TalkChannel2005(tTheTreasureHunt_Text["HaveBrave"])
		return
	end
	
	User_AddEMoney(-tTheTreasureHunt_BuyCharacter["Emoney"])
	Sys_SaveEmoneyBuy(string.format("350	20075	%d	%d	1	",tTheTreasureHunt_BuyCharacter["Emoney"],tTheTreasureHunt_BuyCharacter["Emoney"]))
	Sys_SaveActionFestivalLog(tTheTreasureHunt_BuyCharacter["Log"])
	
	TheTreasureHunt_UseBrave()
	
	User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],tTheTreasureHunt_Constant["Effect_3"])
	
	User_TalkChannel2005(tTheTreasureHunt_Text["BuyCharacter"])
end


--离开龙穴
function TheTreasureHunt_LeaveCave(nNpcId)
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nRank = Get_UserStatisticValue(nEvent,nRankType)
	
	if nRank == 10 then
		User_TalkChannel2005(tTheTreasureHunt_Text["LeaveCave1"])
		TheTreasureHunt_ChgMap()
	else
		LinkNpcGossipFunc_New(nNpcId,"3-1")
	end
end


--传送地图
function TheTreasureHunt_ChgMap()
	TheTreasureHunt_ChkItemStatus()
	local nMapId = tTheTreasureHunt_Leave["MapId"]
	local nCellx = tTheTreasureHunt_Leave["CellX"]
	local nCelly = tTheTreasureHunt_Leave["CellY"]
	User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],tTheTreasureHunt_Constant["Effect_2"])
	User_ChgMap(nMapId,nCellx,nCelly,1)
	User_TalkChannel2005(tTheTreasureHunt_Text["LeaveCave"])
end


--前七波怪物逻辑
function TheTreasureHunt_MonsterDeath(nMonsterId)
	local nMapId = Get_UserMapId()
	
	local nNum = Monster_GetMonsterByName(nMapId,tTheTreasureHunt_MonsterNameText[nMonsterId])


	local nLevel = tTheTreasureHunt_Monster[nMonsterId]["Level"]
	local nMode = tTheTreasureHunt_Monster[nMonsterId]["Mode"]
	local nRank = tTheTreasureHunt_Monster[nMonsterId]["Rank"]
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nRank1 = Get_UserStatisticValue(nEvent,nRankType)
	
	local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][2]
	local nKillNum = Get_UserStatisticValue(nEvent1,nType1)
	
	
	
	if IsDropPower(nLevel) then 
		if IsDropRank(nRank,nRank1) and nKillNum < 5 then
			Task_SetStatistic(nEvent1,nType1,nKillNum+1,1)
			TheTreasureHunt_MonstersDropItem(nMonsterId,nMode)
		else
			User_TalkChannel2005(tTheTreasureHunt_Text["BeOverRank"])
		end
	else
		TheTreasureHunt_ChkItemStatus()
		User_ChgMap(tTheTreasureHunt_Leave["MapId"],tTheTreasureHunt_Leave["CellX"],tTheTreasureHunt_Leave["CellY"],1)
		Sys_MsgBox(tTheTreasureHunt_Text["BeOverPower1"])
		User_TalkChannel2005(tTheTreasureHunt_Text["BeOverPower"])
		return
	end
	
	User_TalkChannel2005(string.format(tTheTreasureHunt_MonsterDeathText[1],tTheTreasureHunt_MonsterNameText[nMonsterId]))

	local nType2 = tTheTreasureHunt_Stc["DataType1"][4]
	local nMark = Get_UserStatisticValue(nEvent1,nType2)
	if nNum == 0 and nMark == 0 then
		Task_SetStatistic(nEvent1,nType2,1,1)
		Sys_SaveActionFestivalLog(string.format(tTheTreasureHunt_Constant["KillMonster"],nLevel,nRank))
		Sys_SaveEmoneyBuy(string.format("350	20079	0	0	%d	",nRank))
		User_TalkChannel2005(string.format(tTheTreasureHunt_MonsterDeathText[2],tTheTreasureHunt_MonsterNameText[nMonsterId]))
		local nNum = 5
		nMode = 1
		nRank = nRank + 1
	
		-- TheTreasureHunt_BrushMonster(nMapId,nLevel,nMode,nRank,nNum)
		User_SetTimer(5,sFunc,1)
		Sys_SetLuaTimer(5,string.format("TheTreasureHunt_BrushMonster</N>%d</N>%d</N>%d</N>%d</N>%d",nMapId,nLevel,nMode,nRank,nNum))
		
		Sys_SetLuaTimer(tTheTreasureHunt_Constant["DelayTime1"],string.format("TheTreasureHunt_BrushRound</N>%d</N>%d</N>%d</N>%d</N>%d",nMapId,nLevel,nMode,nRank,nNum))
		
	end
	
	
	
end


--战斗力是否满足掉落条件
function IsDropPower(nLevel)
	local nPower = Get_UserBattleLevel()
	local nPower1 = tTheTreasureHunt_Power[nLevel]

	if nPower1 == nil then
		return true
	end
	
	if nPower >= nPower1 then
		return false
	else
		return true
	end

	return true
	
end

--是否已闯过此关
function IsDropRank(nRank,nRank1)

	if nRank1 > nRank then
		return false
	end
	return true
	
end


--获取当前时间与初始时间的时间差
function TheTreasureHunt_TimeDifference(nTime)
	local nEvent = tTheTreasureHunt_Stc["EventType1"]
	local nType = tTheTreasureHunt_Stc["DataType1"][1]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][3]
	
	Task_SetStatistic(nEvent,nType1,1,1)
	Task_SetStcTimestamp(nEvent,nType1,0)

	local nTime2 = Get_UserStcTimestampValue(nEvent,nType1)
	local nTime1 = Get_UserStcTimestampValue(nEvent,nType)
	
	nTime = nTime2 - nTime1
	
	return nTime
end
--最后一波怪逻辑
function TheTreasureHunt_MonsterDeath2(nMonsterId)
	local nMapId = Get_UserMapId()
	local nNum = Monster_GetMonsterByName(nMapId,tTheTreasureHunt_MonsterNameText[nMonsterId])
	local nMode = tTheTreasureHunt_Monster[nMonsterId]["Mode"]

	local nLevel = tTheTreasureHunt_Monster[nMonsterId]["Level"]
	local nRank = tTheTreasureHunt_Monster[nMonsterId]["Rank"]
	local nTime = 0
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nRank1 = Get_UserStatisticValue(nEvent,nRankType)
	
	local nEvent1 = tTheTreasureHunt_Stc["EventType1"]
	local nType1 = tTheTreasureHunt_Stc["DataType1"][2]
	local nKillNum = Get_UserStatisticValue(nEvent1,nType1)
	
	
	
	if IsDropPower(nLevel)then 
		if IsDropRank(nRank,nRank1) and nKillNum < 5 then
			Task_SetStatistic(nEvent1,nType1,nKillNum+1,1)
			TheTreasureHunt_MonstersDropItem(nMonsterId,nMode)
		else
			User_TalkChannel2005(tTheTreasureHunt_Text["BeOverRank"])
		end
	else
		TheTreasureHunt_ChkItemStatus()
		User_ChgMap(tTheTreasureHunt_Leave["MapId"],tTheTreasureHunt_Leave["CellX"],tTheTreasureHunt_Leave["CellY"],1)
		Sys_MsgBox(tTheTreasureHunt_Text["BeOverPower1"])
		User_TalkChannel2005(tTheTreasureHunt_Text["BeOverPower"])
		return
	end

	
	local nType2 = tTheTreasureHunt_Stc["DataType1"][4]
	local nMark = Get_UserStatisticValue(nEvent1,nType2)
	
	if nNum == 0 and nMark == 0 then
		Task_SetStatistic(nEvent1,nType2,1,1)
		Sys_SaveActionFestivalLog(string.format(tTheTreasureHunt_Constant["KillMonster"],nLevel,nRank))
		Sys_SaveEmoneyBuy(string.format("350	20079	0	0	%d	",nRank))
		nRank = nRank + 1
		nTime = TheTreasureHunt_TimeDifference(nTime)

		if nTime >= tTheTreasureHunt_Constant["TimeLimit"] then
			nMode = 2
		else
			nMode = 1
		end
		TheTreasureHunt_BrushBoss(nMapId,nLevel,nMode,nRank,nRank1)
	end
end

---刷出boss
function TheTreasureHunt_BrushBoss(nMapId,nLevel,nMode,nRank,nRank1)
	
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	

	
	
	if IsDropRank(nRank,nRank1) then
		Task_SetStatistic(nEvent,nRankType,nRank,1)
	end

	local nMonsterId = tTheTreasureHunt_Monster[nLevel][nMode][nRank]
	local nGenId = tTheTreasureHunt_Monster["nGenId"]
	local nCellx = tTheTreasureHunt_BrushBoss["CellX"]
	local nCelly = tTheTreasureHunt_BrushBoss["CellY"]
	User_TalkChannel2005(string.format(tTheTreasureHunt_MonsterBossText[nMode],tTheTreasureHunt_MonsterNameText[nMonsterId]))
	Monster_AddMonster(nMapId,nCellx,nCelly,nGenId,nMonsterId)

end


--boss逻辑
function TheTreasureHunt_MonsterDeath3(nMonsterId)
	local nRank = tTheTreasureHunt_Monster[nMonsterId]["Rank"]
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	local nRank1 = Get_UserStatisticValue(nEvent,nRankType)
	local nLevel = tTheTreasureHunt_Monster[nMonsterId]["Level"]
	local nTime = TheTreasureHunt_TimeDifference(nTime)
	
	
	if IsDropPower(nLevel)then 
		if not Task_ChkStcValue(nEvent,nRankType,"==",tTheTreasureHunt_Constant["Complete"]) then
			TheTreasureHunt_BossDropItem(nMonsterId)
			TheTreasureHunt_Comparison(nTime)
			Sys_SaveEmoneyBuy(string.format("350	20079	0	0	%d	",nRank))
		end
	else
		TheTreasureHunt_ChkItemStatus()
		User_ChgMap(tTheTreasureHunt_Leave["MapId"],tTheTreasureHunt_Leave["CellX"],tTheTreasureHunt_Leave["CellY"],1)
		Sys_MsgBox(tTheTreasureHunt_Text["BeOverPower1"])
		User_TalkChannel2005(tTheTreasureHunt_Text["BeOverPower"])
		return
	end
	
	Sys_SaveActionFestivalLog(string.format(tTheTreasureHunt_Constant["KillMonster"],nLevel,nRank))
	Task_SetStatistic(nEvent,nRankType,tTheTreasureHunt_Constant["Complete"],1)
	Task_SetStcTimestamp(nEvent,nRankType,0)
	
	Sys_MsgBox(string.format(tTheTreasureHunt_Text["Killboss"],tTheTreasureHunt_MonsterNameText[nMonsterId]))
	
end

--BOSS掉落
function TheTreasureHunt_BossDropItem(nMonsterId)
	local nItem
	local nNum
	
	for i = 1,6 do
		nItem = tTheTreasureHunt_Monster[nMonsterId]["Item_1"][i]
		nNum = tTheTreasureHunt_Monster[nMonsterId]["Num_1"][i]
		
		if nItem ~= nil then
			for j = 1,nNum do
				Monster_SysDropItem(nItem)
			end
		end
	end

end

--与前三名时间比较
function TheTreasureHunt_Comparison(nTime)
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	local nLevel = Get_UserStatisticValue(nEvent,nLevelType)
	
	local nGlobalId = tTheTreasureHunt_RankingGlobal[nLevel]["GlobalId"]
	local nGlobalId1 = tTheTreasureHunt_TaskGlobal[nLevel]["GlobalId"]
	
	local nUserID = Get_UserId()
	local sUserName = Get_UserName()
	
	local nUserID1 = Get_SysDynaGlobalData0(nGlobalId1)
	local nUserID2 = Get_SysDynaGlobalData1(nGlobalId1)
	local nUserID3 = Get_SysDynaGlobalData2(nGlobalId1)

	local sUserName1 = Get_SysDynaGlobalDataStr0(nGlobalId1)
	local sUserName2 = Get_SysDynaGlobalDataStr1(nGlobalId1)
	local sUserName3 = Get_SysDynaGlobalDataStr2(nGlobalId1)
	
	local nGlobalData1 = tTheTreasureHunt_RankingGlobal[nLevel]["GlobalData"][1]
	local nGlobalData2 = tTheTreasureHunt_RankingGlobal[nLevel]["GlobalData"][2]
	local nGlobalData3 = tTheTreasureHunt_RankingGlobal[nLevel]["GlobalData"][3]
	
	local nData1 = Get_SysDynaGlobalData(nGlobalId,nGlobalData1)
	local nData2 = Get_SysDynaGlobalData(nGlobalId,nGlobalData2)
	local nData3 = Get_SysDynaGlobalData(nGlobalId,nGlobalData3)
	
	local t = {}
	t[1] = (nData1 > 0 and {nData1,nUserID1,sUserName1}) or nil
	t[2] = (nData2 > 0 and {nData2,nUserID2,sUserName2}) or nil
	t[3] = (nData3 > 0 and {nData3,nUserID3,sUserName3}) or nil

	table.insert(t,{nTime,nUserID,sUserName})
	
	table.sort(t,function(a,b)
		return a[1] < b[1]
		end
	)
	
	for i=1,#t do
		if i > 3 then
			break
		end
		Sys_SetSynaGlobalData(nGlobalId,tTheTreasureHunt_RankingGlobal[nLevel]["GlobalData"][i],t[i][1])
		Sys_SetSynaGlobalData(nGlobalId1,i-1,t[i][2])
		Sys_SetSynaGlobalDataStr(nGlobalId1,i-1,t[i][3])
	end
	
	
end

--小怪掉落奖励
function TheTreasureHunt_MonstersDropItem(nMonsterId,nMode)
	if nMode == 1 then
		Monster_SysDropMoney(tTheTreasureHunt_Monster["Money"])
	end
	
	local nFlat,tAward = Probabil_RandomAward(tTheTreasureHunt_Monster,nMonsterId)
	local nItem = tAward[1]["tAward"][1]["Item_1"]
	local nOther = tAward[1]["tAward"][1]["Other"]
	local sLog = tAward[1]["tAward"][1]["Log"]
	
	if nOther ~= nil then
		local nFlat,tAward = Probabil_RandomAward(tTheTreasureHunt_Monster,"Other")
		local nItem = tAward[1]["tAward"][1]["Item_1"]
		local sLog = tAward[1]["tAward"][1]["Log"]
		Monster_SysDropItem(nItem)
		
		Sys_SaveActionFestivalLog(sLog)
		-- User_TalkChannel2005(tTheTreasureHunt_Text[nMonsterId][nItem])
		return
	end
	
	if nItem ~= nil then
		Monster_SysDropItem(nItem)
		Sys_SaveActionFestivalLog(sLog)
		-- User_TalkChannel2005(tTheTreasureHunt_Text[nMonsterId][nItem])
	end
	
end

-- 龙穴古书
function TheTreasureHunt_DragonBook(nItemId)
	-- 判断是否在活动时间内
	if not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_TalkChannel2005(tTheTreasureHunt_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	local nMapId = tTheTreasureHunt_Auto["MapId"]
	local nPosX = tTheTreasureHunt_Auto["CellX"]
	local nPosY = tTheTreasureHunt_Auto["CellY"]
	local nGotoNpcId = tTheTreasureHunt_Auto["NpcId"]
	local nLev = Get_UserLevel()
	local sContent = ""
	local sLog = ""
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nGotoNpcId)
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		if nLev < tTheTreasureHunt_Constant["MaxLev"] then
			User_AddExpTime(tTheTreasureHunt_Item[nItemId]["Exp"])
			sContent = tTheTreasureHunt_Text[nItemId]["RewardExp"]
			sLog = tTheTreasureHunt_Item[nItemId]["ExpLog"]
		else
			User_AddCultivation(tTheTreasureHunt_Item[nItemId]["Cultivation"])
			sContent = tTheTreasureHunt_Text[nItemId]["RewardCultivation"]
			sLog = tTheTreasureHunt_Item[nItemId]["CultivationLog"]
		end
		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
		
	end
end


-- 使用龙穴宝盒
function TheTreasureHunt_DragonBox(nItemId,nIndex)
	if nIndex == 1 then
		TheTreasureHunt_OpenDragonBox(nItemId)
	else
		TheTreasureHunt_UseItem(nItemId)
	end
end


-- 打开龙穴宝盒（宝箱）
function TheTreasureHunt_OpenDragonBox(nItemId)

	-- 判断背包空间
	if tTheTreasureHunt_Item[nItemId]["Space"] ~= nil then
		local nSpace = tTheTreasureHunt_Item[nItemId]["Space"]
		if not User_CheckLeftSpace(nSpace) then
			User_TalkChannel2005(tTheTreasureHunt_Text["NoSpace"])
			return
		end
	end
	
	-- 判断玩家赠品天石是否达到上限
	if tTheTreasureHunt_Item[nItemId]["EmoneyMonoLimit"] ~= nil then
		
		local nUserMonoEMoney = Get_UserMonoEMoney()
		local nEmoneyMonoLimit = tTheTreasureHunt_Item[nItemId]["EmoneyMonoLimit"]
		
		if nUserMonoEMoney > nEmoneyMonoLimit then
			User_TalkChannel2005(tTheTreasureHunt_Text["EmoneyMonoLimit"])
			return
		end
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 给奖励
		local nMete = Get_UserMetempsychosis()
		local nFlat,tAward
		
		if nMete < 2 then
			nMete = 1
			nFlat,tAward = Probabil_RandomAward(tTheTreasureHunt_Item[nItemId],1)
		else
			nMete = 2
			nFlat,tAward = Probabil_RandomAward(tTheTreasureHunt_Item[nItemId],2)
		end
	
		local nItem = tAward[1]["tAward"][1]["Item_1"]
		local nItemAttr = tAward[1]["tAward"][1]["ItemAttr"]
		local nIndex = tAward[1]["tAward"][1]["Index"]
		local sLog = tAward[1]["tAward"][1]["Log"]
		local bIsEmoney = tAward[1]["tAward"][1]["IsEmoney"]
		

		
		
		
		if tAward[1]["tAward"][1]["Global"] ~= nil then
			local nGlobal = tAward[1]["tAward"][1]["Global"]
			local nGlobalId = tTheTreasureHunt_ItemGlobal[nGlobal]["GlobalId"]
			local nGlobalData = tTheTreasureHunt_ItemGlobal[nGlobal]["GlobalData"]
			local nData = Get_SysDynaGlobalData(nGlobalId,nGlobalData)
	
			if nData < tTheTreasureHunt_ItemGlobal[nGlobal]["MaxData"] then
				Sys_SetSynaGlobalData(nGlobalId,nGlobalData,nData + 1)
			else 
				local nGlobalItem = tAward[1]["tAward"][1]["GlobalItem"]
				nItem = tTheTreasureHunt_Item[nItemId][nMete][nGlobalItem]["Item_1"]
				nItemAttr = tTheTreasureHunt_Item[nItemId][nMete][nGlobalItem]["ItemAttr"]
				nIndex = tTheTreasureHunt_Item[nItemId][nMete][nGlobalItem]["Index"]
				sLog = tTheTreasureHunt_Item[nItemId][nMete][nGlobalItem]["Log"]
				bIsEmoney = tTheTreasureHunt_Item[nItemId][nMete][nGlobalItem]["IsEmoney"]
			end
		end
		
		if bIsEmoney then
			User_AddEMoneyMono(nItem)
		else
			Item_AddNewItem(nItem,nItemAttr)
		end
		
		
		local sEffect = tTheTreasureHunt_Item[nItemId]["Effect"]
		
		if sEffect ~= nil then
			User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],sEffect)
		end
		
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		Sys_SaveEmoneyBuy(tTheTreasureHunt_Item[nItemId]["EmoneyBuyLog"])
		-- 给提示
		User_TalkChannel2005(tTheTreasureHunt_Text[nItemId][nMete][nIndex])
	end
end



-- 经验礼包使用
function TheTreasureHunt_UseExpPacks(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 判断玩家等级
		local nLev = Get_UserLevel()
		local sLog = ""
		local sContent
		
		if nLev < tTheTreasureHunt_Constant["MaxLev"] then
			User_AddExpTime(tTheTreasureHunt_Item[nItemId]["Exp"])
			sLog = tTheTreasureHunt_Item[nItemId]["ExpLog"]
			sContent = tTheTreasureHunt_Text[nItemId]["Exp"]
		else
			User_AddCultivation(tTheTreasureHunt_Item[nItemId]["Cultivation"])
			sLog = tTheTreasureHunt_Item[nItemId]["CultivationLog"]
			sContent = tTheTreasureHunt_Text[nItemId]["Cultivation"]
		end
		
		
		local sEffect = tTheTreasureHunt_Item[nItemId]["Effect_1"]
		
		if sEffect ~= nil then
			User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],sEffect)
		end
		
		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sContent)
	end
end


-- 物品使用
function TheTreasureHunt_UseItem(nItemId)
	-- 使用物品前判断
	-- 判断背包空间
	if tTheTreasureHunt_Item[nItemId]["Space"] ~= nil then
		local nSpace = tTheTreasureHunt_Item[nItemId]["Space"]
		if not User_CheckLeftSpace(nSpace) then
			User_TalkChannel2005(tTheTreasureHunt_Text["NoSpace"])
			return
		end
	end
	
	-- 判断玩家金币是否达到上限
	if tTheTreasureHunt_Item[nItemId]["Money"] ~= nil then
		local nAddMoney = tTheTreasureHunt_Item[nItemId]["Money"]
		if not User_CanPutMoney2Bag(nAddMoney) then
			User_TalkChannel2005(tTheTreasureHunt_Text["MoneyLimit"])
			return
		end
	end
	
	local nChkItemNum = tTheTreasureHunt_Item[nItemId]["ChkItemNum"] or 1
	
	-- 判断是否有足够的该物品
	if not Item_ChkMulItem(nItemId,nItemId,nChkItemNum) then
		if tTheTreasureHunt_Text[nItemId]["NoItem"] ~= nil then
			User_TalkChannel2005(tTheTreasureHunt_Text[nItemId]["NoItem"])
			return
		end
	end
	
	-- 删除物品
	if Item_DelMulItem(nItemId,nItemId,nChkItemNum) then
		local sLog = tTheTreasureHunt_Item[nItemId]["Log"]
		local sContent = tTheTreasureHunt_Text[nItemId]["UseItem"]
		
		-- 给修行值
		if tTheTreasureHunt_Item[nItemId]["Cultivation"] then
			User_AddCultivation(tTheTreasureHunt_Item[nItemId]["Cultivation"])
		end
		
		-- 给气力值
		if tTheTreasureHunt_Item[nItemId]["Strengthvalue"] then
			User_AddStrengthValue(tTheTreasureHunt_Item[nItemId]["Strengthvalue"])
		end
		
		-- 给金币
		if tTheTreasureHunt_Item[nItemId]["Money"] then
			User_AddMoney(tTheTreasureHunt_Item[nItemId]["Money"])
		end
		
		local nGetItemId = tTheTreasureHunt_Item[nItemId]["ItemId"]
		local nGetItemAttr = tTheTreasureHunt_Item[nItemId]["ItemAttr"]
		
		-- 随机马匹
		if nGetItemAttr ~= nil and type(nGetItemAttr) == "table" then
			local nRandom = math.random(1,#nGetItemAttr)
			nGetItemAttr = tTheTreasureHunt_Item[nItemId]["ItemAttr"][nRandom]
			sContent = tTheTreasureHunt_Text[nItemId]["UseItem"][nRandom]
			sLog = tTheTreasureHunt_Item[nItemId]["Log"][nRandom]
		end
		
		-- 获得物品
		if nGetItemId ~= nil then
			Item_AddNewItem(nGetItemId,nGetItemAttr) 
		end

		local sEffect = tTheTreasureHunt_Item[nItemId]["Effect_1"]
		
		if sEffect ~= nil then
			User_EffectAdd(tTheTreasureHunt_Constant["EffectObj"],sEffect)
		end
		
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		-- 给提示
		User_TalkChannel2005(sContent)
	end
end


-- 勇闯符
function TheTreasureHunt_UseBrave()
	local nSecs = tTheTreasureHunt_Brave["Secs"]
	local nTimes = tTheTreasureHunt_Brave["Times"]
	local nRemainTime = tTheTreasureHunt_Brave["RemainTime"]
	local nEndTime = tTheTreasureHunt_Brave["EndTime"]
	local nRecordable = tTheTreasureHunt_Brave["Recordable"]
	
	local nUserId = Get_UserId()

	for i = 1,6 do
		nStatus = tTheTreasureHunt_Brave[i] 
		nPower = tTheTreasureHunt_Brave[nStatus]
		User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
	end
	
end

function TheTreasureHunt_IsInMap()
	for i = 1,3 do
		local sNpcName = tTheTreasureHunt_Text["NpcName"][i]
		if Get_NpcCountByName(sNpcName) ~= 0 then
			return true
		end
	end
	
	return false
end

--身上有状态加成则删除
function TheTreasureHunt_ChkItemStatus()
	local i = 0
	local nUserId = Get_UserId()
	
	for j = 1,6 do
		local nStatus = tTheTreasureHunt_Brave[j] 
		if User_ChkRoleStatus(nStatus,nUserId) then
			i = i + 1
		end
	end
	
	if i == 6 then 
		for k = 1,6 do
			local nStatus = tTheTreasureHunt_Brave[k] 
			User_DelRoleStatus(nStatus,nUserId)
		end
	end

end

function TheTreasureHunt_ClearStatus()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) or Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"]) then
		TheTreasureHunt_ChkItemStatus()
	end
end



--------------------------------------NPC模块-------------------------------------------
--龙穴指引者
tNpcFace[3741] = 205
tNpcGossip[18711] = tNpcGossip[18711] or DefaultNpc:new{}
tNpcGossip[18711]["OptionHidden"] = 1


-- 活动前
tNpcGossip[18711]["Text1-1"] = {111,112}
tNpcGossip[18711]["Text111"] = tTheTreasureHunt_Text[18711]["111"]
tNpcGossip[18711]["Text112"] = tTheTreasureHunt_Text[18711]["112"]
tNpcGossip[18711]["tOption1-1"] = {1}
tNpcGossip[18711]["Option1"] = tTheTreasureHunt_Text[18711]["Option1"]
tNpcGossip[18711]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tTheTreasureHunt_Constant["BeforeActivityTime"])
end

--活动后
tNpcGossip[18711]["Text1-2"] = {121,122}
tNpcGossip[18711]["Text121"] = tTheTreasureHunt_Text[18711]["121"]
tNpcGossip[18711]["Text122"] = tTheTreasureHunt_Text[18711]["122"]
tNpcGossip[18711]["tOption1-2"] = {2}
tNpcGossip[18711]["Option2"] = tTheTreasureHunt_Text[18711]["Option2"]
tNpcGossip[18711]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tTheTreasureHunt_Constant["Aftime"])
end


--活动中（等级未满足条件）
tNpcGossip[18711]["Text1-3"] = {131,132,133}
tNpcGossip[18711]["Text131"] = tTheTreasureHunt_Text[18711]["131"]
tNpcGossip[18711]["Text132"] = tTheTreasureHunt_Text[18711]["132"]
tNpcGossip[18711]["Text133"] = tTheTreasureHunt_Text[18711]["133"]
tNpcGossip[18711]["tOption1-3"] = {3}
tNpcGossip[18711]["Option3"] = tTheTreasureHunt_Text[18711]["Option3"]
tNpcGossip[18711]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		local nLev = Get_UserLevel()
		local nMete = Get_UserMetempsychosis()
		local nLevLimit = tTheTreasureHunt_Constant["Level"]
		local nMeteLimit = tTheTreasureHunt_Constant["Metempsychosis"]
		
		if nMete < nMeteLimit and nLev < nLevLimit then
			return true
		else
			return false
		end
	else
		return false
	end
end

--活动中（等级满足条件）
tNpcGossip[18711]["Text1-4"] = {141,142,143,144}
tNpcGossip[18711]["Text141"] = tTheTreasureHunt_Text[18711]["141"]
tNpcGossip[18711]["Text142"] = tTheTreasureHunt_Text[18711]["142"]
tNpcGossip[18711]["Text143"] = tTheTreasureHunt_Text[18711]["143"]
tNpcGossip[18711]["Text144"] = tTheTreasureHunt_Text[18711]["144"]
tNpcGossip[18711]["tOption1-4"] = {4,5,7,8}
tNpcGossip[18711]["ChkFunc1-4"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		local nLev = Get_UserLevel()
		local nMete = Get_UserMetempsychosis()
		local nLevLimit = tTheTreasureHunt_Constant["Level"]
		local nMeteLimit = tTheTreasureHunt_Constant["Metempsychosis"]
		
		if nMete < nMeteLimit and nLev < nLevLimit then
			return false
		else
			return true
		end
		
	else
		return false
	end
end

tNpcGossip[18711]["Option4"] = tTheTreasureHunt_Text[18711]["Option4"]
tNpcGossip[18711]["OptionFunc4"] = "TheTreasureHunt_Option4_18711</N>18711"

tNpcGossip[18711]["Option5"] = tTheTreasureHunt_Text[18711]["Option5"]
tNpcGossip[18711]["OptionPoint5"]="7-1"

tNpcGossip[18711]["Option7"] = tTheTreasureHunt_Text[18711]["Option7"]
tNpcGossip[18711]["OptionPoint7"]="5-1"

tNpcGossip[18711]["Option8"] = tTheTreasureHunt_Text[18711]["Option8"]


tNpcGossip[18711]["Text1-5"] = {151,152}
tNpcGossip[18711]["Text151"] = tTheTreasureHunt_Text[18711]["121"]
tNpcGossip[18711]["Text152"] = tTheTreasureHunt_Text[18711]["122"]
tNpcGossip[18711]["tOption1-5"] = {62}
tNpcGossip[18711]["ChkFunc1-5"] = function ()
	return Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"])
end





tNpcGossip[18711]["Text2-1"] = {211}
tNpcGossip[18711]["Text211"] = tTheTreasureHunt_Text[18711]["211"]
tNpcGossip[18711]["tOption2-1"] = {9}
tNpcGossip[18711]["Option9"] = tTheTreasureHunt_Text[18711]["Option9"]


tNpcGossip[18711]["Text2-2"] = {221,222}
tNpcGossip[18711]["Text221"] = tTheTreasureHunt_Text[18711]["221"]
tNpcGossip[18711]["Text222"] = tTheTreasureHunt_Text[18711]["222"]
tNpcGossip[18711]["tOption2-2"] = {10}
tNpcGossip[18711]["Option10"] = tTheTreasureHunt_Text[18711]["Option10"]
tNpcGossip[18711]["OptionFunc10"] = "TheTreasureHunt_EnterCave</N>18711"


tNpcGossip[18711]["Text2-3"] = {231,232,233,234,235}
tNpcGossip[18711]["Text231"] = tTheTreasureHunt_Text[18711]["231"]
tNpcGossip[18711]["Text232"] = tTheTreasureHunt_Text[18711]["232"]
tNpcGossip[18711]["Text233"] = tTheTreasureHunt_Text[18711]["233"]
tNpcGossip[18711]["Text234"] = tTheTreasureHunt_Text[18711]["234"]
tNpcGossip[18711]["Text235"] = tTheTreasureHunt_Text[18711]["235"]
tNpcGossip[18711]["tOption2-3"] = {11,12,13,14}
tNpcGossip[18711]["Option11"] = tTheTreasureHunt_Text[18711]["Option11"]
tNpcGossip[18711]["Option12"] = tTheTreasureHunt_Text[18711]["Option12"]
tNpcGossip[18711]["Option13"] = tTheTreasureHunt_Text[18711]["Option13"]
tNpcGossip[18711]["Option14"] = tTheTreasureHunt_Text[18711]["Option14"]
tNpcGossip[18711]["OptionFunc11"] = "TheTreasureHunt_SelectionDifficulty</N>18711</N>1"
tNpcGossip[18711]["OptionFunc12"] = "TheTreasureHunt_SelectionDifficulty</N>18711</N>2"
tNpcGossip[18711]["OptionFunc13"] = "TheTreasureHunt_SelectionDifficulty</N>18711</N>3"

tNpcGossip[18711]["Text2-4"] = {241}
tNpcGossip[18711]["Text241"] = tTheTreasureHunt_Text[18711]["241"]
tNpcGossip[18711]["tOption2-4"] = {15}
tNpcGossip[18711]["Option15"] = tTheTreasureHunt_Text[18711]["Option15"]

tNpcGossip[18711]["Text2-5"] = {251}
tNpcGossip[18711]["Text251"] = tTheTreasureHunt_Text[18711]["251"]
tNpcGossip[18711]["tOption2-5"] = {16}
tNpcGossip[18711]["Option16"] = tTheTreasureHunt_Text[18711]["Option15"]

tNpcGossip[18711]["Text2-6"] = {261}
tNpcGossip[18711]["Text261"] = tTheTreasureHunt_Text[18711]["261"]
tNpcGossip[18711]["tOption2-6"] = {17,18}
tNpcGossip[18711]["Option17"] = tTheTreasureHunt_Text[18711]["Option17"]
tNpcGossip[18711]["Option18"] = tTheTreasureHunt_Text[18711]["Option18"]

tNpcGossip[18711]["OptionFunc17"] = "TheTreasureHunt_SetDifficulty</N>18711</N>1"
tNpcGossip[18711]["OptionFunc18"] = "TheTreasureHunt_Option4_18711</N>18711"

tNpcGossip[18711]["OptionChkFunc18"] = function ()
	local nEvent = tTheTreasureHunt_Stc["EventType"]
	local nLevelType = tTheTreasureHunt_Stc["DataType"][1]
	local nLev = Get_UserStatisticValue(nEvent,nLevelType)
	if nLev == 0 then
		return true
	else
		return false
	end
end

tNpcGossip[18711]["Text2-7"] = {271}
tNpcGossip[18711]["Text271"] = tTheTreasureHunt_Text[18711]["271"]
tNpcGossip[18711]["tOption2-7"] = {19,18}
tNpcGossip[18711]["Option19"] = tTheTreasureHunt_Text[18711]["Option19"]
tNpcGossip[18711]["OptionFunc19"] = "TheTreasureHunt_SetDifficulty</N>18711</N>2"


tNpcGossip[18711]["Text3-1"] = {311,312}
tNpcGossip[18711]["Text311"] = tTheTreasureHunt_Text[18711]["311"]
tNpcGossip[18711]["Text312"] = tTheTreasureHunt_Text[18711]["312"]
tNpcGossip[18711]["tOption3-1"] = {20,21,22,40,23}
tNpcGossip[18711]["Option20"] = tTheTreasureHunt_Text[18711]["Option20"]
tNpcGossip[18711]["OptionPoint20"]="3-2"
tNpcGossip[18711]["Option21"] = tTheTreasureHunt_Text[18711]["Option21"]
tNpcGossip[18711]["OptionPoint21"]="3-3"
tNpcGossip[18711]["Option22"] = tTheTreasureHunt_Text[18711]["Option22"]
tNpcGossip[18711]["OptionPoint22"]="3-4"
tNpcGossip[18711]["Option40"] = tTheTreasureHunt_Text[18711]["Option40"]
tNpcGossip[18711]["OptionPoint40"]="6-4"
tNpcGossip[18711]["Option23"] = tTheTreasureHunt_Text[18711]["Option23"]
tNpcGossip[18711]["OptionPoint23"]="7-1"



tNpcGossip[18711]["ChkFunc3-1"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) or Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"]) then
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-2")
		return false
	end
end

tNpcGossip[18711]["Text3-2"] = {321,322,323,324}
tNpcGossip[18711]["Text321"] = tTheTreasureHunt_Text[18711]["321"]
tNpcGossip[18711]["Text322"] = tTheTreasureHunt_Text[18711]["322"]
tNpcGossip[18711]["Text323"] = tTheTreasureHunt_Text[18711]["323"]
tNpcGossip[18711]["Text324"] = tTheTreasureHunt_Text[18711]["324"]
tNpcGossip[18711]["tOption3-2"] = {24,25,26}
tNpcGossip[18711]["Option24"] = tTheTreasureHunt_Text[18711]["Option24"]
tNpcGossip[18711]["Option25"] = tTheTreasureHunt_Text[18711]["Option25"]
tNpcGossip[18711]["OptionPoint25"]="3-1"
tNpcGossip[18711]["Option26"] = tTheTreasureHunt_Text[18711]["Option26"]
tNpcGossip[18711]["ChkFunc3-2"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) or Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"])then
	
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[1]["GlobalId"]
		local sDataStr3 = Get_SysDynaGlobalDataStr3(nGlobalId)
		local sDataStr4 = Get_SysDynaGlobalDataStr4(nGlobalId)
		local sDataStr5 = Get_SysDynaGlobalDataStr5(nGlobalId)
		
		tNpcGossip[18711]["Text322"] = string.format(tTheTreasureHunt_Text[18711]["322"],sDataStr3)
		tNpcGossip[18711]["Text323"] = string.format(tTheTreasureHunt_Text[18711]["323"],sDataStr4)
		tNpcGossip[18711]["Text324"] = string.format(tTheTreasureHunt_Text[18711]["324"],sDataStr5)
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-2")
		return false
	end
end

tNpcGossip[18711]["Text3-3"] = {331,332,333,334}
tNpcGossip[18711]["Text331"] = tTheTreasureHunt_Text[18711]["331"]
tNpcGossip[18711]["Text332"] = tTheTreasureHunt_Text[18711]["332"]
tNpcGossip[18711]["Text333"] = tTheTreasureHunt_Text[18711]["333"]
tNpcGossip[18711]["Text334"] = tTheTreasureHunt_Text[18711]["334"]
tNpcGossip[18711]["tOption3-3"] = {27,25,26}
tNpcGossip[18711]["Option27"] = tTheTreasureHunt_Text[18711]["Option27"]
tNpcGossip[18711]["ChkFunc3-3"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) or Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"]) then
	
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[2]["GlobalId"]
		local sDataStr3 = Get_SysDynaGlobalDataStr3(nGlobalId)
		local sDataStr4 = Get_SysDynaGlobalDataStr4(nGlobalId)
		local sDataStr5 = Get_SysDynaGlobalDataStr5(nGlobalId)

		
		tNpcGossip[18711]["Text332"] = string.format(tTheTreasureHunt_Text[18711]["332"],sDataStr3)
		tNpcGossip[18711]["Text333"] = string.format(tTheTreasureHunt_Text[18711]["333"],sDataStr4)
		tNpcGossip[18711]["Text334"] = string.format(tTheTreasureHunt_Text[18711]["334"],sDataStr5)
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-2")
		return false
	end
end

tNpcGossip[18711]["Text3-4"] = {341,342,343,344}
tNpcGossip[18711]["Text341"] = tTheTreasureHunt_Text[18711]["341"]
tNpcGossip[18711]["Text342"] = tTheTreasureHunt_Text[18711]["342"]
tNpcGossip[18711]["Text343"] = tTheTreasureHunt_Text[18711]["343"]
tNpcGossip[18711]["Text344"] = tTheTreasureHunt_Text[18711]["344"]
tNpcGossip[18711]["tOption3-4"] = {28,25,26}
tNpcGossip[18711]["Option28"] = tTheTreasureHunt_Text[18711]["Option28"]
tNpcGossip[18711]["ChkFunc3-4"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) or Sys_ChkFullTime(tTheTreasureHunt_Constant["LastDay"]) then
	
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[3]["GlobalId"]
		local sDataStr3 = Get_SysDynaGlobalDataStr3(nGlobalId)
		local sDataStr4 = Get_SysDynaGlobalDataStr4(nGlobalId)
		local sDataStr5 = Get_SysDynaGlobalDataStr5(nGlobalId)
		
		tNpcGossip[18711]["Text342"] = string.format(tTheTreasureHunt_Text[18711]["342"],sDataStr3)
		tNpcGossip[18711]["Text343"] = string.format(tTheTreasureHunt_Text[18711]["343"],sDataStr4)
		tNpcGossip[18711]["Text344"] = string.format(tTheTreasureHunt_Text[18711]["344"],sDataStr5)
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-2")
		return false
	end
end

tNpcGossip[18711]["OptionFunc24"] = "TheTreasureHunt_IsTopThree</N>18711</N>50923"
tNpcGossip[18711]["OptionFunc27"] = "TheTreasureHunt_IsTopThree</N>18711</N>50924"
tNpcGossip[18711]["OptionFunc28"] = "TheTreasureHunt_IsTopThree</N>18711</N>50925"

tNpcGossip[18711]["Text3-5"] = {351}
tNpcGossip[18711]["Text351"] = tTheTreasureHunt_Text[18711]["351"]
tNpcGossip[18711]["tOption3-5"] = {29}
tNpcGossip[18711]["Option29"] = tTheTreasureHunt_Text[18711]["Option29"]

tNpcGossip[18711]["Text3-6"] = {361}
tNpcGossip[18711]["Text361"] = tTheTreasureHunt_Text[18711]["361"]
tNpcGossip[18711]["tOption3-6"] = {30}
tNpcGossip[18711]["Option30"] = tTheTreasureHunt_Text[18711]["Option30"]


tNpcGossip[18711]["Text3-7"] = {371}
tNpcGossip[18711]["Text371"] = tTheTreasureHunt_Text[18711]["371"]
tNpcGossip[18711]["tOption3-7"] = {31}
tNpcGossip[18711]["Option31"] = tTheTreasureHunt_Text[18711]["Option31"]


tNpcGossip[18711]["Text3-8"] = {381,382}
tNpcGossip[18711]["Text381"] = tTheTreasureHunt_Text[18711]["381"]
tNpcGossip[18711]["Text382"] = tTheTreasureHunt_Text[18711]["382"]
tNpcGossip[18711]["tOption3-8"] = {32}
tNpcGossip[18711]["Option32"] = tTheTreasureHunt_Text[18711]["Option32"]
tNpcGossip[18711]["ChkFunc3-8"] = function ()
	local nGlobalId = tTheTreasureHunt_TaskGlobal[1]["GlobalId"]
	local nUserID = Get_UserId()
	local nData3 = Get_SysDynaGlobalData3(nGlobalId)
	local nData4 = Get_SysDynaGlobalData4(nGlobalId)
	local nData5 = Get_SysDynaGlobalData5(nGlobalId)
	local nRank = 0
	
	if nUserID == nData3 then
		nRank = 1
	elseif nUserID == nData4 then
		nRank = 2
	else
		nRank = 3
	end
	
	tNpcGossip[18711]["Text381"] = string.format(tTheTreasureHunt_Text[18711]["381"],nRank)
	
	return true

end

tNpcGossip[18711]["Text3-9"] = {391,392}
tNpcGossip[18711]["Text391"] = tTheTreasureHunt_Text[18711]["391"]
tNpcGossip[18711]["Text392"] = tTheTreasureHunt_Text[18711]["392"]
tNpcGossip[18711]["tOption3-9"] = {32}
tNpcGossip[18711]["ChkFunc3-9"] = function ()
	local nGlobalId = tTheTreasureHunt_TaskGlobal[2]["GlobalId"]
	local nUserID = Get_UserId()
	local nData3 = Get_SysDynaGlobalData3(nGlobalId)
	local nData4 = Get_SysDynaGlobalData4(nGlobalId)
	local nData5 = Get_SysDynaGlobalData5(nGlobalId)
	local nRank = 0
	
	if nUserID == nData3 then
		nRank = 1
	elseif nUserID == nData4 then
		nRank = 2
	else
		nRank = 3
	end
	
	tNpcGossip[18711]["Text391"] = string.format(tTheTreasureHunt_Text[18711]["391"],nRank)
	
	return true
end

tNpcGossip[18711]["Text3-10"] = {3101,3102}
tNpcGossip[18711]["Text3101"] = tTheTreasureHunt_Text[18711]["3101"]
tNpcGossip[18711]["Text3102"] = tTheTreasureHunt_Text[18711]["3102"]
tNpcGossip[18711]["tOption3-10"] = {32}
tNpcGossip[18711]["ChkFunc3-10"] = function ()
	local nGlobalId = tTheTreasureHunt_TaskGlobal[3]["GlobalId"]
	local nUserID = Get_UserId()
	local nData3 = Get_SysDynaGlobalData3(nGlobalId)
	local nData4 = Get_SysDynaGlobalData4(nGlobalId)
	local nData5 = Get_SysDynaGlobalData5(nGlobalId)
	local nRank = 0
	
	if nUserID == nData3 then
		nRank = 1
	elseif nUserID == nData4 then
		nRank = 2
	else
		nRank = 3
	end
	
	tNpcGossip[18711]["Text3101"] = string.format(tTheTreasureHunt_Text[18711]["3101"],nRank)
	
	return true
end


tNpcGossip[18711]["Text4-1"] = {411,412}
tNpcGossip[18711]["Text411"] = tTheTreasureHunt_Text[18711]["411"]
tNpcGossip[18711]["Text412"] = tTheTreasureHunt_Text[18711]["412"]
tNpcGossip[18711]["tOption4-1"] = {33,34,35,40,23}
tNpcGossip[18711]["Option33"] = tTheTreasureHunt_Text[18711]["Option33"]
tNpcGossip[18711]["OptionPoint33"]="4-2"
tNpcGossip[18711]["Option34"] = tTheTreasureHunt_Text[18711]["Option34"]
tNpcGossip[18711]["OptionPoint34"]="4-3"
tNpcGossip[18711]["Option35"] = tTheTreasureHunt_Text[18711]["Option35"]
tNpcGossip[18711]["OptionPoint35"]="4-4"
-- tNpcGossip[18711]["Option36"] = tTheTreasureHunt_Text[18711]["Option36"]
tNpcGossip[18711]["ChkFunc4-1"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-5")
		return false
	end
end

tNpcGossip[18711]["Text4-2"] = {421,422,423,424}
tNpcGossip[18711]["Text421"] = tTheTreasureHunt_Text[18711]["421"]
tNpcGossip[18711]["Text422"] = tTheTreasureHunt_Text[18711]["422"]
tNpcGossip[18711]["Text423"] = tTheTreasureHunt_Text[18711]["423"]
tNpcGossip[18711]["Text424"] = tTheTreasureHunt_Text[18711]["424"]
tNpcGossip[18711]["tOption4-2"] = {37}
tNpcGossip[18711]["Option37"] = tTheTreasureHunt_Text[18711]["Option37"]
tNpcGossip[18711]["OptionPoint37"]="4-1"
tNpcGossip[18711]["ChkFunc4-2"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[1]["GlobalId"]
		local sDataStr1 = Get_SysDynaGlobalDataStr0(nGlobalId)
		local sDataStr2 = Get_SysDynaGlobalDataStr1(nGlobalId)
		local sDataStr3 = Get_SysDynaGlobalDataStr2(nGlobalId)
		
		local nGlobalId1 = tTheTreasureHunt_RankingGlobal[1]["GlobalId"]
		local nData1 = Get_SysDynaGlobalData0(nGlobalId1)
		local nData2 = Get_SysDynaGlobalData1(nGlobalId1)
		local nData3 = Get_SysDynaGlobalData2(nGlobalId1)
		
		if nData1 == 0 then
			tNpcGossip[18711]["Text422"] = string.format(tTheTreasureHunt_Text[18711]["422"],sDataStr1)
		else
			tNpcGossip[18711]["Text422"] = string.format(tTheTreasureHunt_Text[18711]["425"],sDataStr1,nData1)
		end
		
		if nData2 == 0 then
			tNpcGossip[18711]["Text423"] = string.format(tTheTreasureHunt_Text[18711]["423"],sDataStr2)
		else
			tNpcGossip[18711]["Text423"] = string.format(tTheTreasureHunt_Text[18711]["426"],sDataStr2,nData2)
		end
		
		if nData3 == 0 then
			tNpcGossip[18711]["Text424"] = string.format(tTheTreasureHunt_Text[18711]["424"],sDataStr3)
		else
			tNpcGossip[18711]["Text424"] = string.format(tTheTreasureHunt_Text[18711]["427"],sDataStr3,nData3)
		end
		
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-5")
		return false
	end
end

tNpcGossip[18711]["Text4-3"] = {431,432,433,434}
tNpcGossip[18711]["Text431"] = tTheTreasureHunt_Text[18711]["431"]
tNpcGossip[18711]["Text432"] = tTheTreasureHunt_Text[18711]["432"]
tNpcGossip[18711]["Text433"] = tTheTreasureHunt_Text[18711]["433"]
tNpcGossip[18711]["Text434"] = tTheTreasureHunt_Text[18711]["434"]
tNpcGossip[18711]["tOption4-3"] = {37}
tNpcGossip[18711]["ChkFunc4-3"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[2]["GlobalId"]
		local sDataStr1 = Get_SysDynaGlobalDataStr0(nGlobalId)
		local sDataStr2 = Get_SysDynaGlobalDataStr1(nGlobalId)
		local sDataStr3 = Get_SysDynaGlobalDataStr2(nGlobalId)
		
		local nGlobalId1 = tTheTreasureHunt_RankingGlobal[2]["GlobalId"]
		local nData1 = Get_SysDynaGlobalData3(nGlobalId1)
		local nData2 = Get_SysDynaGlobalData4(nGlobalId1)
		local nData3 = Get_SysDynaGlobalData5(nGlobalId1)
		
		if nData1 == 0 then
			tNpcGossip[18711]["Text432"] = string.format(tTheTreasureHunt_Text[18711]["432"],sDataStr1)
		else
			tNpcGossip[18711]["Text432"] = string.format(tTheTreasureHunt_Text[18711]["435"],sDataStr1,nData1)
		end
		
		if nData2 == 0 then
			tNpcGossip[18711]["Text433"] = string.format(tTheTreasureHunt_Text[18711]["433"],sDataStr2)
		else
			tNpcGossip[18711]["Text433"] = string.format(tTheTreasureHunt_Text[18711]["436"],sDataStr2,nData2)
		end
		
		if nData3 == 0 then
			tNpcGossip[18711]["Text434"] = string.format(tTheTreasureHunt_Text[18711]["434"],sDataStr3)
		else
			tNpcGossip[18711]["Text434"] = string.format(tTheTreasureHunt_Text[18711]["437"],sDataStr3,nData3)
		end
		
		
		
		
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-5")
		return false
	end
end

tNpcGossip[18711]["Text4-4"] = {441,442,443,444}
tNpcGossip[18711]["Text441"] = tTheTreasureHunt_Text[18711]["441"]
tNpcGossip[18711]["Text442"] = tTheTreasureHunt_Text[18711]["442"]
tNpcGossip[18711]["Text443"] = tTheTreasureHunt_Text[18711]["443"]
tNpcGossip[18711]["Text444"] = tTheTreasureHunt_Text[18711]["444"]
tNpcGossip[18711]["tOption4-4"] = {37}
tNpcGossip[18711]["ChkFunc4-4"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		
		TheTreasureHunt_SaveTaskGlobal()
		
		local nGlobalId = tTheTreasureHunt_TaskGlobal[3]["GlobalId"]
		local sDataStr1 = Get_SysDynaGlobalDataStr0(nGlobalId)
		local sDataStr2 = Get_SysDynaGlobalDataStr1(nGlobalId)
		local sDataStr3 = Get_SysDynaGlobalDataStr2(nGlobalId)
		
		local nGlobalId1 = tTheTreasureHunt_RankingGlobal[3]["GlobalId"]
		local nData1 = Get_SysDynaGlobalData0(nGlobalId1)
		local nData2 = Get_SysDynaGlobalData1(nGlobalId1)
		local nData3 = Get_SysDynaGlobalData2(nGlobalId1)
		
		if nData1 == 0 then
			tNpcGossip[18711]["Text442"] = string.format(tTheTreasureHunt_Text[18711]["442"],sDataStr1)
		else
			tNpcGossip[18711]["Text442"] = string.format(tTheTreasureHunt_Text[18711]["445"],sDataStr1,nData1)
		end
		
		if nData2 == 0 then
			tNpcGossip[18711]["Text443"] = string.format(tTheTreasureHunt_Text[18711]["443"],sDataStr2)
		else
			tNpcGossip[18711]["Text443"] = string.format(tTheTreasureHunt_Text[18711]["446"],sDataStr2,nData2)
		end
		
		if nData3 == 0 then
			tNpcGossip[18711]["Text444"] = string.format(tTheTreasureHunt_Text[18711]["444"],sDataStr3)
		else
			tNpcGossip[18711]["Text444"] = string.format(tTheTreasureHunt_Text[18711]["447"],sDataStr3,nData3)
		end
		
		return true
	else
		LinkNpcGossipFunc_New(18711,"1-5")
		return false
	end
end

tNpcGossip[18711]["Text5-1"] = {511,512,513}
tNpcGossip[18711]["Text511"] = tTheTreasureHunt_Text[18711]["511"]
tNpcGossip[18711]["Text512"] = tTheTreasureHunt_Text[18711]["512"]
tNpcGossip[18711]["Text513"] = tTheTreasureHunt_Text[18711]["513"]
tNpcGossip[18711]["tOption5-1"] = {38}
tNpcGossip[18711]["Option38"] = tTheTreasureHunt_Text[18711]["Option38"]
-- tNpcGossip[18711]["Option39"] = tTheTreasureHunt_Text[18711]["Option39"]
-- tNpcGossip[18711]["Option41"] = tTheTreasureHunt_Text[18711]["Option41"]
-- tNpcGossip[18711]["Option42"] = tTheTreasureHunt_Text[18711]["Option42"]

tNpcGossip[18711]["OptionPoint38"]="5-2"
-- tNpcGossip[18711]["OptionPoint39"]="5-3"
-- tNpcGossip[18711]["OptionPoint41"]="1-4"



tNpcGossip[18711]["Text5-2"] = {521,522,523}
tNpcGossip[18711]["Text521"] = tTheTreasureHunt_Text[18711]["521"]
tNpcGossip[18711]["Text522"] = tTheTreasureHunt_Text[18711]["522"]
tNpcGossip[18711]["Text523"] = tTheTreasureHunt_Text[18711]["523"]
tNpcGossip[18711]["tOption5-2"] = {43}
tNpcGossip[18711]["Option43"] = tTheTreasureHunt_Text[18711]["Option43"]
-- tNpcGossip[18711]["Option44"] = tTheTreasureHunt_Text[18711]["Option44"]
tNpcGossip[18711]["OptionPoint43"]="5-3"


tNpcGossip[18711]["Text5-3"] = {531,532,533}
tNpcGossip[18711]["Text531"] = tTheTreasureHunt_Text[18711]["531"]
tNpcGossip[18711]["Text532"] = tTheTreasureHunt_Text[18711]["532"]
tNpcGossip[18711]["Text533"] = tTheTreasureHunt_Text[18711]["533"]
tNpcGossip[18711]["tOption5-3"] = {45,46,47,48}
tNpcGossip[18711]["Option45"] = tTheTreasureHunt_Text[18711]["Option45"]
tNpcGossip[18711]["Option46"] = tTheTreasureHunt_Text[18711]["Option46"]
tNpcGossip[18711]["Option47"] = tTheTreasureHunt_Text[18711]["Option47"]
tNpcGossip[18711]["Option48"] = tTheTreasureHunt_Text[18711]["Option48"]
-- tNpcGossip[18711]["Option49"] = tTheTreasureHunt_Text[18711]["Option49"]
tNpcGossip[18711]["OptionPoint45"]="5-5"
tNpcGossip[18711]["OptionPoint46"]="5-6"
tNpcGossip[18711]["OptionPoint47"]="5-7"
tNpcGossip[18711]["OptionPoint48"]="1-4"


tNpcGossip[18711]["Text5-4"] = {541}
tNpcGossip[18711]["Text541"] = tTheTreasureHunt_Text[18711]["541"]
tNpcGossip[18711]["tOption5-4"] = {50,51,52,53}
tNpcGossip[18711]["Option50"] = tTheTreasureHunt_Text[18711]["Option50"]
tNpcGossip[18711]["Option51"] = tTheTreasureHunt_Text[18711]["Option51"]
tNpcGossip[18711]["Option52"] = tTheTreasureHunt_Text[18711]["Option52"]
tNpcGossip[18711]["Option53"] = tTheTreasureHunt_Text[18711]["Option53"]
-- tNpcGossip[18711]["Option54"] = tTheTreasureHunt_Text[18711]["Option54"]
tNpcGossip[18711]["OptionPoint50"]="5-8"
tNpcGossip[18711]["OptionPoint51"]="5-9"
tNpcGossip[18711]["OptionPoint52"]="5-10"
tNpcGossip[18711]["OptionPoint53"]="4-1"




tNpcGossip[18711]["Text5-5"] = {551,552,553,554}
tNpcGossip[18711]["Text551"] = tTheTreasureHunt_Text[18711]["551"]
tNpcGossip[18711]["Text552"] = tTheTreasureHunt_Text[18711]["552"]
tNpcGossip[18711]["Text553"] = tTheTreasureHunt_Text[18711]["553"]
tNpcGossip[18711]["Text554"] = tTheTreasureHunt_Text[18711]["554"]
tNpcGossip[18711]["tOption5-5"] = {55}
tNpcGossip[18711]["Option55"] = tTheTreasureHunt_Text[18711]["Option55"]
-- tNpcGossip[18711]["Option56"] = tTheTreasureHunt_Text[18711]["Option56"]
tNpcGossip[18711]["OptionPoint55"]="5-3"

tNpcGossip[18711]["Text5-6"] = {561,562,563,564}
tNpcGossip[18711]["Text561"] = tTheTreasureHunt_Text[18711]["561"]
tNpcGossip[18711]["Text562"] = tTheTreasureHunt_Text[18711]["562"]
tNpcGossip[18711]["Text563"] = tTheTreasureHunt_Text[18711]["563"]
tNpcGossip[18711]["Text564"] = tTheTreasureHunt_Text[18711]["564"]
tNpcGossip[18711]["tOption5-6"] = {55}

tNpcGossip[18711]["Text5-7"] = {571,572,573,574}
tNpcGossip[18711]["Text571"] = tTheTreasureHunt_Text[18711]["571"]
tNpcGossip[18711]["Text572"] = tTheTreasureHunt_Text[18711]["572"]
tNpcGossip[18711]["Text573"] = tTheTreasureHunt_Text[18711]["573"]
tNpcGossip[18711]["Text574"] = tTheTreasureHunt_Text[18711]["574"]
tNpcGossip[18711]["tOption5-7"] = {55}

tNpcGossip[18711]["Text5-8"] = {581,582,583,584}
tNpcGossip[18711]["Text581"] = tTheTreasureHunt_Text[18711]["581"]
tNpcGossip[18711]["Text582"] = tTheTreasureHunt_Text[18711]["582"]
tNpcGossip[18711]["Text583"] = tTheTreasureHunt_Text[18711]["583"]
tNpcGossip[18711]["Text584"] = tTheTreasureHunt_Text[18711]["584"]
tNpcGossip[18711]["tOption5-8"] = {57}
tNpcGossip[18711]["Option57"] = tTheTreasureHunt_Text[18711]["Option57"]
tNpcGossip[18711]["OptionPoint57"]="5-4"

tNpcGossip[18711]["Text5-9"] = {591,592,593,594}
tNpcGossip[18711]["Text591"] = tTheTreasureHunt_Text[18711]["591"]
tNpcGossip[18711]["Text592"] = tTheTreasureHunt_Text[18711]["592"]
tNpcGossip[18711]["Text593"] = tTheTreasureHunt_Text[18711]["593"]
tNpcGossip[18711]["Text594"] = tTheTreasureHunt_Text[18711]["594"]
tNpcGossip[18711]["tOption5-9"] = {57}

tNpcGossip[18711]["Text5-10"] = {5101,5102,5103,5104}
tNpcGossip[18711]["Text5101"] = tTheTreasureHunt_Text[18711]["5101"]
tNpcGossip[18711]["Text5102"] = tTheTreasureHunt_Text[18711]["5102"]
tNpcGossip[18711]["Text5103"] = tTheTreasureHunt_Text[18711]["5103"]
tNpcGossip[18711]["Text5104"] = tTheTreasureHunt_Text[18711]["5104"]
tNpcGossip[18711]["tOption5-10"] = {57}

tNpcGossip[18711]["Text6-1"] = {611}
tNpcGossip[18711]["Text611"] = tTheTreasureHunt_Text[18711]["611"]
tNpcGossip[18711]["tOption6-1"] = {58}
tNpcGossip[18711]["Option58"] = tTheTreasureHunt_Text[18711]["Option58"]

tNpcGossip[18711]["Text6-4"] = {641}
tNpcGossip[18711]["Text641"] = tTheTreasureHunt_Text[18711]["541"]
tNpcGossip[18711]["tOption6-4"] = {50,51,52,59}
tNpcGossip[18711]["Option59"] = tTheTreasureHunt_Text[18711]["Option53"]
tNpcGossip[18711]["OptionPoint59"]="3-1"


tNpcGossip[18711]["Text6-2"] = {621}
tNpcGossip[18711]["Text621"] = tTheTreasureHunt_Text[18711]["621"]
tNpcGossip[18711]["tOption6-2"] = {60,18}
tNpcGossip[18711]["Option60"] = tTheTreasureHunt_Text[18711]["Option17"]
tNpcGossip[18711]["OptionFunc60"] = "TheTreasureHunt_SetDifficulty</N>18711</N>2"

tNpcGossip[18711]["Text6-3"] = {631}
tNpcGossip[18711]["Text631"] = tTheTreasureHunt_Text[18711]["621"]
tNpcGossip[18711]["tOption6-3"] = {61,18}
tNpcGossip[18711]["Option61"] = tTheTreasureHunt_Text[18711]["Option19"]
tNpcGossip[18711]["OptionFunc61"] = "TheTreasureHunt_SetDifficulty</N>18711</N>3"


tNpcGossip[18711]["Text7-1"] = {711}
tNpcGossip[18711]["Text711"] = tTheTreasureHunt_Text[18711]["711"]
tNpcGossip[18711]["tOption7-1"] = {62,63,64}

tNpcGossip[18711]["Option62"] = tTheTreasureHunt_Text[18711]["Option62"]
tNpcGossip[18711]["OptionPoint62"]="3-1"
tNpcGossip[18711]["OptionChkFunc62"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["FirstDay"]) then
		return false
	else
		return true
	end
end

tNpcGossip[18711]["Option63"] = tTheTreasureHunt_Text[18711]["Option63"]
tNpcGossip[18711]["OptionPoint63"]="4-1"

tNpcGossip[18711]["Option64"] = tTheTreasureHunt_Text[18711]["Option64"]
tNpcGossip[18711]["OptionPoint64"]="1-4"


--龙穴指引者
tNpcFace[3742] = 203
tNpcGossip[18712] = tNpcGossip[18712] or DefaultNpc:new{}
tNpcGossip[18712]["OptionHidden"] = 1

tNpcFace[3784] = 203
tNpcGossip[18789] = tNpcGossip[18712] or DefaultNpc:new{}

tNpcFace[3785] = 203
tNpcGossip[18790] = tNpcGossip[18712] or DefaultNpc:new{}




-- 活动外
tNpcGossip[18712]["Text1-1"] = {111,112}
tNpcGossip[18712]["Text111"] = tTheTreasureHunt_Text[18712]["111"]
tNpcGossip[18712]["Text112"] = tTheTreasureHunt_Text[18712]["112"]
tNpcGossip[18712]["tOption1-1"] = {1}
tNpcGossip[18712]["ChkFunc1-1"] = function ()
	return not Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"])
end

tNpcGossip[18712]["Option1"] = tTheTreasureHunt_Text[18712]["Option1"]
tNpcGossip[18712]["OptionFunc1"] = "TheTreasureHunt_ChgMap</N>18712"


tNpcGossip[18712]["Text1-2"] = {121,122,123}
tNpcGossip[18712]["Text121"] = tTheTreasureHunt_Text[18712]["121"]
tNpcGossip[18712]["Text122"] = tTheTreasureHunt_Text[18712]["122"]
tNpcGossip[18712]["Text123"] = tTheTreasureHunt_Text[18712]["123"]
tNpcGossip[18712]["tOption1-2"] = {3,4}
tNpcGossip[18712]["ChkFunc1-2"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		local nEvent = tTheTreasureHunt_Stc["EventType"]
		local nRankType = tTheTreasureHunt_Stc["DataType"][2]
		local nRank = Get_UserStatisticValue(nEvent,nRankType)
	
		if nRank == 10 then
			return false
		else
			return true
		end
	else
		return false
	end
end


-- tNpcGossip[18712]["Option2"] = tTheTreasureHunt_Text[18712]["Option2"]
tNpcGossip[18712]["Option3"] = tTheTreasureHunt_Text[18712]["Option3"]
tNpcGossip[18712]["Option4"] = tTheTreasureHunt_Text[18712]["Option4"]
-- tNpcGossip[18712]["Option5"] = tTheTreasureHunt_Text[18712]["Option5"]
-- tNpcGossip[18712]["Option8"] = tTheTreasureHunt_Text[18711]["Option6"]
-- tNpcGossip[18712]["Option6"] = tTheTreasureHunt_Text[18712]["Option6"]

-- tNpcGossip[18712]["OptionFunc2"] = "TheTreasureHunt_MissionStart</N>18712"
tNpcGossip[18712]["OptionFunc3"] = "TheTreasureHunt_BuyCharacter</N>18712"
tNpcGossip[18712]["OptionFunc4"] = "TheTreasureHunt_LeaveCave</N>18712"
-- tNpcGossip[18712]["OptionPoint5"]="2-1"
-- tNpcGossip[18712]["OptionPoint8"] = "4-1"

-- tNpcGossip[18712]["OptionChkFunc3"] = function ()
	-- local nEvent = tTheTreasureHunt_Stc["EventType"]
	-- local nRankType = tTheTreasureHunt_Stc["DataType"][2]
	-- local nRank = Get_UserStatisticValue(nEvent,nRankType)
	
	-- if nRank == 10 then
		-- return false
	-- else
		-- return true
	-- end
-- end

tNpcGossip[18712]["Text1-3"] = {131,132}
tNpcGossip[18712]["Text131"] = tTheTreasureHunt_Text[18712]["131"]
tNpcGossip[18712]["Text132"] = tTheTreasureHunt_Text[18712]["132"]
tNpcGossip[18712]["tOption1-3"] = {4}
tNpcGossip[18712]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tTheTreasureHunt_Constant["ActivityTime"]) then
		local nEvent = tTheTreasureHunt_Stc["EventType"]
		local nRankType = tTheTreasureHunt_Stc["DataType"][2]
		local nRank = Get_UserStatisticValue(nEvent,nRankType)

		if nRank == 10 then
			return true
		else
			return false
		end
	else
		return false
	end
end





tNpcGossip[18712]["Text3-1"] = {311,312}
tNpcGossip[18712]["Text311"] = tTheTreasureHunt_Text[18712]["311"]
tNpcGossip[18712]["Text312"] = tTheTreasureHunt_Text[18712]["312"]
tNpcGossip[18712]["tOption3-1"] = {27,28}
tNpcGossip[18712]["Option27"] = tTheTreasureHunt_Text[18712]["Option27"]
tNpcGossip[18712]["Option28"] = tTheTreasureHunt_Text[18712]["Option28"]
tNpcGossip[18712]["OptionFunc27"] = "TheTreasureHunt_ChgMap</N>18712"







--------------------------------------物品配置-------------------------------------------

-- 龙穴古书
tItem[3006949] = tItem[3006949] or {}
tItem[3006949]["Text1-1"] = {111,112}
tItem[3006949]["Text111"] = tTheTreasureHunt_Text[3006949]["111"]
tItem[3006949]["Text112"] = tTheTreasureHunt_Text[3006949]["112"]
tItem[3006949]["tOption1-1"] = {1}

tItem[3006949]["Option1"] = tTheTreasureHunt_Text[3006949]["Option1"]
tItem[3006949]["OptionFunc1"]="TheTreasureHunt_DragonBook</N>3006949"

-- 龙穴宝盒
tItem[3006951] = tItem[3006951] or {}
tItem[3006951]["Text1-1"] = {111,112}
tItem[3006951]["Text111"] = tTheTreasureHunt_Text[3006951]["111"]
tItem[3006951]["Text112"] = tTheTreasureHunt_Text[3006951]["112"]
tItem[3006951]["tOption1-1"] = {1,2}

tItem[3006951]["Option1"] = tTheTreasureHunt_Text[3006951]["Option1"]
tItem[3006951]["OptionFunc1"]="TheTreasureHunt_DragonBox</N>3006951</N>1"
tItem[3006951]["Option2"] = tTheTreasureHunt_Text[3006951]["Option2"]
tItem[3006951]["OptionFunc2"]="TheTreasureHunt_DragonBox</N>3006951</N>2"

-- 龙穴宝箱
tItem[3007022] = tItem[3007022] or {}
tItem[3007022]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_OpenDragonBox(nItemId)
end

-- 龙穴宝盒碎片
tItem[3006953] = tItem[3006953] or {}
tItem[3006953]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- +2SteedPack
tItem[3007031] = tItem[3007031] or {}
tItem[3007031]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- +3SteedPack
tItem[3007032] = tItem[3007032] or {}
tItem[3007032]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 15分钟经验包
tItem[3007023] = tItem[3007023] or {}
tItem[3007023]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseExpPacks(nItemId)
end

-- 30分钟经验包
tItem[3007024] = tItem[3007024] or {}
tItem[3007024]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseExpPacks(nItemId)
end

-- 60分钟经验包
tItem[3007120] = tItem[3007120] or {}
tItem[3007120]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseExpPacks(nItemId)
end

-- 10点修行值礼包
tItem[3007119] = tItem[3007119] or {}
tItem[3007119]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 20点修行值礼包
tItem[3007025] = tItem[3007025] or {}
tItem[3007025]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 40点修行值礼包
tItem[3007026] = tItem[3007026] or {}
tItem[3007026]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 40点气力值礼包
tItem[3007121] = tItem[3007121] or {}
tItem[3007121]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 20点气力值礼包
tItem[3007122] = tItem[3007122] or {}
tItem[3007122]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 迷你银两包
tItem[3007027] = tItem[3007027] or {}
tItem[3007027]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 经济银两包
tItem[3007028] = tItem[3007028] or {}
tItem[3007028]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end

-- 丰足银两包
tItem[3007029] = tItem[3007029] or {}
tItem[3007029]["Function"] = function(nItemId,sItemName)
	TheTreasureHunt_UseItem(nItemId)
end
-- 勇闯符 3006950
-- tItem[3006950] = tItem[3006950] or {}
-- tItem[3006950]["Function"] = function(nItemId,sItemName)
	-- TheTreasureHunt_UseBrave(nItemId)
-- end

--------------------------------------怪物掉落-------------------------------------------
-- tMonster[7750] = tMonster[7750] or {}
-- tMonster[7750]["tFunction"] = tMonster[7750]["tFunction"] or {}
-- table.insert(tMonster[7750]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7751] = tMonster[7751] or {}
-- tMonster[7751]["tFunction"] = tMonster[7751]["tFunction"] or {}
-- table.insert(tMonster[7751]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7752] = tMonster[7752] or {}
-- tMonster[7752]["tFunction"] = tMonster[7752]["tFunction"] or {}
-- table.insert(tMonster[7752]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7753] = tMonster[7753] or {}
-- tMonster[7753]["tFunction"] = tMonster[7753]["tFunction"] or {}
-- table.insert(tMonster[7753]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7754] = tMonster[7754] or {}
-- tMonster[7754]["tFunction"] = tMonster[7754]["tFunction"] or {}
-- table.insert(tMonster[7754]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7755] = tMonster[7755] or {}
-- tMonster[7755]["tFunction"] = tMonster[7755]["tFunction"] or {}
-- table.insert(tMonster[7755]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7756] = tMonster[7756] or {}
-- tMonster[7756]["tFunction"] = tMonster[7756]["tFunction"] or {}
-- table.insert(tMonster[7756]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7757] = tMonster[7757] or {}
-- tMonster[7757]["tFunction"] = tMonster[7757]["tFunction"] or {}
-- table.insert(tMonster[7757]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7758] = tMonster[7758] or {}
-- tMonster[7758]["tFunction"] = tMonster[7758]["tFunction"] or {}
-- table.insert(tMonster[7758]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7759] = tMonster[7759] or {}
-- tMonster[7759]["tFunction"] = tMonster[7759]["tFunction"] or {}
-- table.insert(tMonster[7759]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7760] = tMonster[7760] or {}
-- tMonster[7760]["tFunction"] = tMonster[7760]["tFunction"] or {}
-- table.insert(tMonster[7760]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7761] = tMonster[7761] or {}
-- tMonster[7761]["tFunction"] = tMonster[7761]["tFunction"] or {}
-- table.insert(tMonster[7761]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7762] = tMonster[7762] or {}
-- tMonster[7762]["tFunction"] = tMonster[7762]["tFunction"] or {}
-- table.insert(tMonster[7762]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7763] = tMonster[7763] or {}
-- tMonster[7763]["tFunction"] = tMonster[7763]["tFunction"] or {}
-- table.insert(tMonster[7763]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7764] = tMonster[7764] or {}
-- tMonster[7764]["tFunction"] = tMonster[7764]["tFunction"] or {}
-- table.insert(tMonster[7764]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7765] = tMonster[7765] or {}
-- tMonster[7765]["tFunction"] = tMonster[7765]["tFunction"] or {}
-- table.insert(tMonster[7765]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7766] = tMonster[7766] or {}
-- tMonster[7766]["tFunction"] = tMonster[7766]["tFunction"] or {}
-- table.insert(tMonster[7766]["tFunction"],TheTreasureHunt_MonsterDeath3)

-- tMonster[7767] = tMonster[7767] or {}
-- tMonster[7767]["tFunction"] = tMonster[7767]["tFunction"] or {}
-- table.insert(tMonster[7767]["tFunction"],TheTreasureHunt_MonsterDeath3)

-- tMonster[7768] = tMonster[7768] or {}
-- tMonster[7768]["tFunction"] = tMonster[7768]["tFunction"] or {}
-- table.insert(tMonster[7768]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7769] = tMonster[7769] or {}
-- tMonster[7769]["tFunction"] = tMonster[7769]["tFunction"] or {}
-- table.insert(tMonster[7769]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7770] = tMonster[7770] or {}
-- tMonster[7770]["tFunction"] = tMonster[7770]["tFunction"] or {}
-- table.insert(tMonster[7770]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7771] = tMonster[7771] or {}
-- tMonster[7771]["tFunction"] = tMonster[7771]["tFunction"] or {}
-- table.insert(tMonster[7771]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7772] = tMonster[7772] or {}
-- tMonster[7772]["tFunction"] = tMonster[7772]["tFunction"] or {}
-- table.insert(tMonster[7772]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7773] = tMonster[7773] or {}
-- tMonster[7773]["tFunction"] = tMonster[7773]["tFunction"] or {}
-- table.insert(tMonster[7773]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7774] = tMonster[7774] or {}
-- tMonster[7774]["tFunction"] = tMonster[7774]["tFunction"] or {}
-- table.insert(tMonster[7774]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7775] = tMonster[7775] or {}
-- tMonster[7775]["tFunction"] = tMonster[7775]["tFunction"] or {}
-- table.insert(tMonster[7775]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7776] = tMonster[7776] or {}
-- tMonster[7776]["tFunction"] = tMonster[7776]["tFunction"] or {}
-- table.insert(tMonster[7776]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7777] = tMonster[7777] or {}
-- tMonster[7777]["tFunction"] = tMonster[7777]["tFunction"] or {}
-- table.insert(tMonster[7777]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7778] = tMonster[7778] or {}
-- tMonster[7778]["tFunction"] = tMonster[7778]["tFunction"] or {}
-- table.insert(tMonster[7778]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7779] = tMonster[7779] or {}
-- tMonster[7779]["tFunction"] = tMonster[7779]["tFunction"] or {}
-- table.insert(tMonster[7779]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7780] = tMonster[7780] or {}
-- tMonster[7780]["tFunction"] = tMonster[7780]["tFunction"] or {}
-- table.insert(tMonster[7780]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7781] = tMonster[7781] or {}
-- tMonster[7781]["tFunction"] = tMonster[7781]["tFunction"] or {}
-- table.insert(tMonster[7781]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7782] = tMonster[7782] or {}
-- tMonster[7782]["tFunction"] = tMonster[7782]["tFunction"] or {}
-- table.insert(tMonster[7782]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7783] = tMonster[7783] or {}
-- tMonster[7783]["tFunction"] = tMonster[7783]["tFunction"] or {}
-- table.insert(tMonster[7783]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7784] = tMonster[7784] or {}
-- tMonster[7784]["tFunction"] = tMonster[7784]["tFunction"] or {}
-- table.insert(tMonster[7784]["tFunction"],TheTreasureHunt_MonsterDeath3)

-- tMonster[7785] = tMonster[7785] or {}
-- tMonster[7785]["tFunction"] = tMonster[7785]["tFunction"] or {}
-- table.insert(tMonster[7785]["tFunction"],TheTreasureHunt_MonsterDeath3)

-- tMonster[7786] = tMonster[7786] or {}
-- tMonster[7786]["tFunction"] = tMonster[7786]["tFunction"] or {}
-- table.insert(tMonster[7786]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7787] = tMonster[7787] or {}
-- tMonster[7787]["tFunction"] = tMonster[7787]["tFunction"] or {}
-- table.insert(tMonster[7787]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7788] = tMonster[7788] or {}
-- tMonster[7788]["tFunction"] = tMonster[7788]["tFunction"] or {}
-- table.insert(tMonster[7788]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7789] = tMonster[7789] or {}
-- tMonster[7789]["tFunction"] = tMonster[7789]["tFunction"] or {}
-- table.insert(tMonster[7789]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7790] = tMonster[7790] or {}
-- tMonster[7790]["tFunction"] = tMonster[7790]["tFunction"] or {}
-- table.insert(tMonster[7790]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7791] = tMonster[7791] or {}
-- tMonster[7791]["tFunction"] = tMonster[7791]["tFunction"] or {}
-- table.insert(tMonster[7791]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7792] = tMonster[7792] or {}
-- tMonster[7792]["tFunction"] = tMonster[7792]["tFunction"] or {}
-- table.insert(tMonster[7792]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7793] = tMonster[7793] or {}
-- tMonster[7793]["tFunction"] = tMonster[7793]["tFunction"] or {}
-- table.insert(tMonster[7793]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7794] = tMonster[7794] or {}
-- tMonster[7794]["tFunction"] = tMonster[7794]["tFunction"] or {}
-- table.insert(tMonster[7794]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7795] = tMonster[7795] or {}
-- tMonster[7795]["tFunction"] = tMonster[7795]["tFunction"] or {}
-- table.insert(tMonster[7795]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7796] = tMonster[7796] or {}
-- tMonster[7796]["tFunction"] = tMonster[7796]["tFunction"] or {}
-- table.insert(tMonster[7796]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7797] = tMonster[7797] or {}
-- tMonster[7797]["tFunction"] = tMonster[7797]["tFunction"] or {}
-- table.insert(tMonster[7797]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7798] = tMonster[7798] or {}
-- tMonster[7798]["tFunction"] = tMonster[7798]["tFunction"] or {}
-- table.insert(tMonster[7798]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7799] = tMonster[7799] or {}
-- tMonster[7799]["tFunction"] = tMonster[7799]["tFunction"] or {}
-- table.insert(tMonster[7799]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7800] = tMonster[7800] or {}
-- tMonster[7800]["tFunction"] = tMonster[7800]["tFunction"] or {}
-- table.insert(tMonster[7800]["tFunction"],TheTreasureHunt_MonsterDeath)

-- tMonster[7801] = tMonster[7801] or {}
-- tMonster[7801]["tFunction"] = tMonster[7801]["tFunction"] or {}
-- table.insert(tMonster[7801]["tFunction"],TheTreasureHunt_MonsterDeath2)

-- tMonster[7802] = tMonster[7802] or {}
-- tMonster[7802]["tFunction"] = tMonster[7802]["tFunction"] or {}
-- table.insert(tMonster[7802]["tFunction"],TheTreasureHunt_MonsterDeath3)

-- tMonster[7803] = tMonster[7803] or {}
-- tMonster[7803]["tFunction"] = tMonster[7803]["tFunction"] or {}
-- table.insert(tMonster[7803]["tFunction"],TheTreasureHunt_MonsterDeath3)

--时间自检
-- tSystem_Prompet_Func = tSystem_Prompet_Func or {}
-- table.insert(tSystem_Prompet_Func,TheTreasureHunt_SaveTaskGlobal)

--上限触发
-- tSystem_PlayLogin_Func = tSystem_PlayLogin_Func or {}
-- table.insert(tSystem_PlayLogin_Func,TheTreasureHunt_ClearStatus)