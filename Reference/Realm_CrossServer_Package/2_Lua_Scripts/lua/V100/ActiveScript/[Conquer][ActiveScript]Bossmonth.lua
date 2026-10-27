------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]boss月活动制作
--Creator: 		魏贻逵
--Created:		2015/08/04
------------------------------------------------------------------------------------
--命名前命名前缀 Bossmonth
-- 350 4325 购买随机品质配方（9T）
-- 350 4326 付费单次抽奖（39T）
-- 350 4327 付费十次抽奖（390T）
-- 350 4328 付费单次高级抽奖（199T）
-- 350 4329 付费十次高级抽奖（1990T）
-- 350 4330 获得赠品永久外套礼包
-- 350 4331 获得非赠品永久外套礼包
-- 350 4332 获得光效外套礼包

--掩码
local	tBossmonth_Stc = {}
		tBossmonth_Stc[4] = {}  --每天只能制作5次限制
		tBossmonth_Stc[4]["EventType"] = 137
		tBossmonth_Stc[4]["DataType"] = 23

local	tBossmonth_Time = {}
		tBossmonth_Time["Beftime"] = "2015-01-01 00:00 2015-12-02 23:59"
		tBossmonth_Time["Nowtime"] = "2015-12-03 00:00 2015-12-16 23:59"
		tBossmonth_Time["Aftime"] = "2015-12-17 00:00 2020-01-01 23:59"

local	tBossmonth_Cont = {}
		tBossmonth_Cont["Level"] = 100
		tBossmonth_Cont["Metempsychosis"] = 0
		tBossmonth_Cont["Space"] = 1

--背包信奖励
		tBossmonth_Cont["AddExpTime"] = 30 
		tBossmonth_Cont["AddCultivation"] = 15

--寻路坐标
		tBossmonth_Cont["Cellx"] = 294 
		tBossmonth_Cont["Celly"] = 226
		tBossmonth_Cont["MapId"] = 1036
		tBossmonth_Cont["NpcId"] = 10870

--购买1,10部件需要的银两 
		tBossmonth_Cont[3007163] = {}
		tBossmonth_Cont[3007163]["price"] = {}
		tBossmonth_Cont[3007163]["price"][1] = 100000
		tBossmonth_Cont[3007163]["price"][2] = 500000
		
		tBossmonth_Cont[3007163]["amount"] = {}
		tBossmonth_Cont[3007163]["amount"][1] = 1
		tBossmonth_Cont[3007163]["amount"][2] = 5
		
		tBossmonth_Cont[3007163]["Log"] = {}
		tBossmonth_Cont[3007163]["Log"][1] = "[100000],0,0,0,12000173,1[6],3007163,1"
		tBossmonth_Cont[3007163]["Log"][2] = "[500000],0,0,0,12000173,1[7],3007163,5"

		tBossmonth_Cont[3007164] = {}
		tBossmonth_Cont[3007164]["price"] = {}
		tBossmonth_Cont[3007164]["price"][1] = 100000
		tBossmonth_Cont[3007164]["price"][2] = 500000
		
		tBossmonth_Cont[3007164]["amount"] = {}
		tBossmonth_Cont[3007164]["amount"][1] = 1
		tBossmonth_Cont[3007164]["amount"][2] = 5
		
		tBossmonth_Cont[3007164]["Log"] = {}
		tBossmonth_Cont[3007164]["Log"][1] = "[100000],0,0,0,12000173,1[6],3007164,1"
		tBossmonth_Cont[3007164]["Log"][2] = "[500000],0,0,0,12000173,1[7],3007164,5"

		tBossmonth_Cont[3007165] = {}
		tBossmonth_Cont[3007165]["price"] = {}
		tBossmonth_Cont[3007165]["price"][1] = 100000
		tBossmonth_Cont[3007165]["price"][2] = 500000

		tBossmonth_Cont[3007165]["amount"] = {}
		tBossmonth_Cont[3007165]["amount"][1] = 1
		tBossmonth_Cont[3007165]["amount"][2] = 5

		tBossmonth_Cont[3007165]["Log"] = {}
		tBossmonth_Cont[3007165]["Log"][1] = "[100000],0,0,0,12000173,1[6],3007165,1"
		tBossmonth_Cont[3007165]["Log"][2] = "[500000],0,0,0,12000173,1[7],3007165,5"

--购买3种部件需要的银两
		tBossmonth_Cont["price"] = {}
		tBossmonth_Cont["price"][1] = 300000
		tBossmonth_Cont["price"][5] = 1500000
		
		tBossmonth_Cont["Log"] = {}
		tBossmonth_Cont["Log"][1] = "[300000],0,0,0,12000173,1[8],3007163[3007164][3007165],1[1][1]"
		tBossmonth_Cont["Log"][5] = "[1500000],0,0,0,12000173,1[9],3007163[3007164][3007165],5[5][5]"

		tBossmonth_Cont["ItemId"] = {}
		tBossmonth_Cont["ItemId"][1] = 3007163
		tBossmonth_Cont["ItemId"][2] = 3007164
		tBossmonth_Cont["ItemId"][3] = 3007165

--回收成品外套
		tBossmonth_Cont[3007201] = {}
		tBossmonth_Cont[3007201]["AddItem"] = 3007199
		tBossmonth_Cont[3007201]["Num"] = 1

		tBossmonth_Cont[3007201]["AwardItem"] = 193495
		tBossmonth_Cont[3007201]["Attr"] = "0 0 1 10080 0 0 0 1"
		tBossmonth_Cont[3007201]["Effect"] = "zf2-e129"
		tBossmonth_Cont[3007201]["Log"] = "0,0,3007201,1,12000173,2,193495,1"

		tBossmonth_Cont[3007202] = {}
		tBossmonth_Cont[3007202]["AddItem"] = 3007200
		tBossmonth_Cont[3007202]["Num"] = 3

		tBossmonth_Cont[3007202]["AwardItem"] = 193505
		tBossmonth_Cont[3007202]["Attr"] = "0 0 1 0 0 0 0 1"
		tBossmonth_Cont[3007202]["Effect"] = "zf2-e129"
		tBossmonth_Cont[3007202]["Log"] = "0,0,3007202,1,12000173,2,193505,1"

		tBossmonth_Cont[3007203] = {}
		tBossmonth_Cont[3007203]["AwardItem"] = 193515
		tBossmonth_Cont[3007203]["Attr"] = "0 0 0 0 0 0 0 1"
		tBossmonth_Cont[3007203]["Effect"] = "zf2-e129"
		tBossmonth_Cont[3007203]["Log"] = "0,0,3007203,1,12000173,2,193515,1"

		tBossmonth_Cont[3007204] = {}
		tBossmonth_Cont[3007204]["AwardItem"] = 193445
		tBossmonth_Cont[3007204]["Attr"] = "0 0 0 0 0 0 0 1"
		tBossmonth_Cont[3007204]["Effect"] = "accession"
		tBossmonth_Cont[3007204]["Log"] = "0,0,3007204,1,12000173,2,193445,1"

--研究高级配方
		tBossmonth_Cont[3007199] = {}
		tBossmonth_Cont[3007199]["Emoney"] = {}
		tBossmonth_Cont[3007199]["Emoney"][1] = 15

		tBossmonth_Cont[3007199]["EmoneyLog"] = {}
		tBossmonth_Cont[3007199]["EmoneyLog"][1] = "350	4326	15	15	1	"

		tBossmonth_Cont[3007200] = {}
		tBossmonth_Cont[3007200]["Emoney"] = {}
		tBossmonth_Cont[3007200]["Emoney"][1] = 77
		tBossmonth_Cont[3007200]["Emoney"][10] = 770

		tBossmonth_Cont[3007200]["EmoneyLog"] = {}
		tBossmonth_Cont[3007200]["EmoneyLog"][1] = "350	4328	77	77	1	"
		tBossmonth_Cont[3007200]["EmoneyLog"][10] = "350	4329	770	770	1	"


--活动结束后可兑换气力
		tBossmonth_Cont[3007199]["strengthvalue"] = 60
		tBossmonth_Cont[3007200]["strengthvalue"] = 300

--使用设计图制作外套所需要的材料
		tBossmonth_Cont["Material"] = {}
		tBossmonth_Cont["Material"][1] = 3007163
		tBossmonth_Cont["Material"][2] = 3007164
		tBossmonth_Cont["Material"][3] = 3007165

--各部件设计图制作的概率
		tBossmonth_Cont["Material"][3007168] = {}
		tBossmonth_Cont["Material"][3007168][1] = 3007183
		tBossmonth_Cont["Material"][3007168][2] = 3007184
		tBossmonth_Cont["Material"][3007168][3] = 3007185
		tBossmonth_Cont["Material"][3007168][4] = 3007186
		tBossmonth_Cont["Material"][3007168]["AwardItem"] = 3007163
		tBossmonth_Cont["Material"][3007168]["AddExpTime"] = 10
		tBossmonth_Cont["Material"][3007168]["AddCultivation"] = 5
		tBossmonth_Cont["Material"][3007168]["Log"] = "0,0,3007168[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],3007163,1"
		tBossmonth_Cont["Material"][3007168]["Log1"] = "0,0,3007168[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],4,10"
		tBossmonth_Cont["Material"][3007168]["Log2"] = "0,0,3007168[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],6,5"

		tBossmonth_Cont["Material"][3007169] = {}
		tBossmonth_Cont["Material"][3007169][1] = 3007183
		tBossmonth_Cont["Material"][3007169][2] = 3007184
		tBossmonth_Cont["Material"][3007169][3] = 3007185
		tBossmonth_Cont["Material"][3007169][4] = 3007186
		tBossmonth_Cont["Material"][3007169]["AwardItem"] = 3007164
		tBossmonth_Cont["Material"][3007169]["AddExpTime"] = 10
		tBossmonth_Cont["Material"][3007169]["AddCultivation"] = 5
		tBossmonth_Cont["Material"][3007169]["Log"] = "0,0,3007169[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],3007164,1"
		tBossmonth_Cont["Material"][3007169]["Log1"] = "0,0,3007169[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],4,10"
		tBossmonth_Cont["Material"][3007169]["Log2"] = "0,0,3007169[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],6,5"

		tBossmonth_Cont["Material"][3007170] = {}
		tBossmonth_Cont["Material"][3007170][1] = 3007183
		tBossmonth_Cont["Material"][3007170][2] = 3007184
		tBossmonth_Cont["Material"][3007170][3] = 3007185
		tBossmonth_Cont["Material"][3007170][4] = 3007186
		tBossmonth_Cont["Material"][3007170]["AwardItem"] = 3007165
		tBossmonth_Cont["Material"][3007170]["AddExpTime"] = 10
		tBossmonth_Cont["Material"][3007170]["AddCultivation"] = 5
		tBossmonth_Cont["Material"][3007170]["Log"] = "0,0,3007170[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],3007165,1"
		tBossmonth_Cont["Material"][3007170]["Log1"] = "0,0,3007170[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],4,10"
		tBossmonth_Cont["Material"][3007170]["Log2"] = "0,0,3007170[3007183][3007184][3007185][3007186],1[1][1][1][5],12000173,1[5],6,5"


--各品质图纸制作获得的经验修行值
		tBossmonth_Cont[3007158] = {}
		tBossmonth_Cont[3007158]["AddExpTime"] = 60 
		tBossmonth_Cont[3007158]["AddCultivation"] = 30
		tBossmonth_Cont[3007158]["ExpTimeLog"] = "0,0,0,0,12000173,2,4,60"
		tBossmonth_Cont[3007158]["CultivationLog"] = "0,0,0,0,12000173,2,6,30"

		tBossmonth_Cont[3007159] = {}
		tBossmonth_Cont[3007159]["AddExpTime"] = 120 
		tBossmonth_Cont[3007159]["AddCultivation"] = 60
		tBossmonth_Cont[3007159]["ExpTimeLog"] = "0,0,0,0,12000173,2,4,120"
		tBossmonth_Cont[3007159]["CultivationLog"] = "0,0,0,0,12000173,2,6,60"

		tBossmonth_Cont[3007159]["compose"] = 3007158
		tBossmonth_Cont[3007159]["Num"] = 5

		tBossmonth_Cont[3007160] = {}
		tBossmonth_Cont[3007160]["AddExpTime"] = 180 
		tBossmonth_Cont[3007160]["AddCultivation"] = 90
		tBossmonth_Cont[3007160]["ExpTimeLog"] = "0,0,0,0,12000173,2,4,180"
		tBossmonth_Cont[3007160]["CultivationLog"] = "0,0,0,0,12000173,2,6,90"
		
		tBossmonth_Cont[3007160]["compose"] = 3007159
		tBossmonth_Cont[3007160]["Num"] = 5

--碎片合成礼包
		tBossmonth_Cont[3007205] = {}
		tBossmonth_Cont[3007205]["Num"] = 7
		tBossmonth_Cont[3007205]["AwardItem"] = 3007201
		tBossmonth_Cont[3007205]["Attr"] = "0 0 1"
		tBossmonth_Cont[3007205]["Random_1"] = 1
		tBossmonth_Cont[3007205]["Random"] = 7
		tBossmonth_Cont[3007205]["AddExpTime"] = 20
		tBossmonth_Cont[3007205]["AddCultivation"] = 10
		tBossmonth_Cont[3007205]["Log"] = "0,0,3007205,1,12000173,2,3007201,1"
		tBossmonth_Cont[3007205]["Log1"] = "0,0,3007205,1,12000173,2,4,20"
		tBossmonth_Cont[3007205]["Log2"] = "0,0,3007205,1,12000173,2,6,10"
		tBossmonth_Cont[3007205]["Log3"] = "0,0,3007205,15,12000173,2,3007201,1"

		tBossmonth_Cont[3007206] = {}
		tBossmonth_Cont[3007206]["Num"] = 15
		tBossmonth_Cont[3007206]["AwardItem"] = 3007202
		tBossmonth_Cont[3007206]["Attr"] = "0 0 1"
		tBossmonth_Cont[3007206]["Random_1"] = 1
		tBossmonth_Cont[3007206]["Random"] = 15
		tBossmonth_Cont[3007206]["AddExpTime"] = 200
		tBossmonth_Cont[3007206]["AddCultivation"] = 100
		tBossmonth_Cont[3007206]["Log"] = "0,0,3007206,1,12000173,2,3007202,1"
		tBossmonth_Cont[3007206]["Log1"] = "0,0,3007206,1,12000173,2,4,200"
		tBossmonth_Cont[3007206]["Log2"] = "0,0,3007206,1,12000173,2,6,100"
		tBossmonth_Cont[3007206]["Log3"] = "0,0,3007206,15,12000173,2,3007202,1"
		tBossmonth_Cont[3007206]["EmoneyLog"] = "350	4330	0	0	1	"

		tBossmonth_Cont[3007209] = {}
		tBossmonth_Cont[3007209]["Num"] = 10
		tBossmonth_Cont[3007209]["AwardItem"] = 3007207
		tBossmonth_Cont[3007209]["Attr"] = "0"
		tBossmonth_Cont[3007209]["strengthvalue_1"] = 100
		tBossmonth_Cont[3007209]["strengthvalue"] = 200
		tBossmonth_Cont[3007209]["Random_1"] = 9
		tBossmonth_Cont[3007209]["Random"] = 100
		tBossmonth_Cont[3007209]["Log"] = "0,0,3007209,1,12000173,2,3007207,1"
		tBossmonth_Cont[3007209]["Log4"] = "0,0,3007209,1,12000173,2,12,100"
		tBossmonth_Cont[3007209]["Log3"] = "0,0,3007209,15,12000173,2,3007207,1"

		tBossmonth_Cont[3007210] = {}
		tBossmonth_Cont[3007210]["Num"] = 10
		tBossmonth_Cont[3007210]["AwardItem"] = 3007208
		tBossmonth_Cont[3007210]["Attr"] = "0"
		tBossmonth_Cont[3007210]["strengthvalue_1"] = 300
		tBossmonth_Cont[3007210]["strengthvalue"] = 600
		tBossmonth_Cont[3007210]["Random_1"] = 9
		tBossmonth_Cont[3007210]["Random"] = 100
		tBossmonth_Cont[3007210]["Log"] = "0,0,3007210,1,12000173,2,3007208,1"
		tBossmonth_Cont[3007210]["Log4"] = "0,0,3007210,1,12000173,2,12,300"
		tBossmonth_Cont[3007210]["Log3"] = "0,0,3007210,15,12000173,2,3007208,1"


--活动结束后物品可兑换成气力
		tBossmonth_Cont[3007211] = {}
		tBossmonth_Cont[3007211]["strengthvalue"] = 200

		tBossmonth_Cont[3007214] = {}
		tBossmonth_Cont[3007214]["strengthvalue"] = 600

--合成洗赠道具，光效道具所需要的材料
		tBossmonth_Cont[3007207] = {}
		tBossmonth_Cont[3007207]["AwardItem"] = 193515
		tBossmonth_Cont[3007207]["Attr"] = "0 0 0 0 0 0 0 1"
		tBossmonth_Cont[3007207]["strengthvalue"] = 200
		tBossmonth_Cont[3007207]["Log"] = "0,0,3007207[3007211][193505],1[15][1],12000173,2,193515,1"
		tBossmonth_Cont[3007207]["EmoneyLog"] = "350	4331	0	0	1	"

		tBossmonth_Cont[3007207][1] = {}
		tBossmonth_Cont[3007207][1]["Id"] = 3007211
		tBossmonth_Cont[3007207][1]["Attr"] = 0
		tBossmonth_Cont[3007207][1]["Num"] = 15

		tBossmonth_Cont[3007207][2] = {}
		tBossmonth_Cont[3007207][2]["Id"] = 193505
		tBossmonth_Cont[3007207][2]["Attr"] = 1
		tBossmonth_Cont[3007207][2]["Num"] = 1

		tBossmonth_Cont[3007208] = {}
		tBossmonth_Cont[3007208]["AwardItem"] = 193445
		tBossmonth_Cont[3007208]["Attr"] = "0 0 0 0 0 0 0 1"
		tBossmonth_Cont[3007208]["strengthvalue"] = 600
		tBossmonth_Cont[3007208]["Log"] = "0,0,3007208[3007214][193515],1[15][1],12000173,2,193445,1"
		tBossmonth_Cont[3007208]["EmoneyLog"] = "350	4332	0	0	1	"

		tBossmonth_Cont[3007208][1] = {}
		tBossmonth_Cont[3007208][1]["Id"] = 3007214
		tBossmonth_Cont[3007208][1]["Attr"] = 0
		tBossmonth_Cont[3007208][1]["Num"] = 15

		tBossmonth_Cont[3007208][2] = {}
		tBossmonth_Cont[3007208][2]["Id"] = 193515
		tBossmonth_Cont[3007208][2]["Attr"] = 0
		tBossmonth_Cont[3007208][2]["Num"] = 1

		tBossmonth_Cont["Drop"] = {}
		tBossmonth_Cont["Drop"][1] = 3007168
		tBossmonth_Cont["Drop"][2] = 3007169
		tBossmonth_Cont["Drop"][3] = 3007170

local	tBossmonth_Monster = {}  
		tBossmonth_Monster[1] = {10,11,12,13}
		tBossmonth_Monster[2] = {14,15,16,17,73}
		tBossmonth_Monster[3] = {18,19,55,78,79,84}
		tBossmonth_Monster[4] = {20,56,57,58,2411,2416,2686,2687}
		tBossmonth_Monster[5] = {7862}

--抽奖概率
local	tBossmonth_Lottery_random = {} 
		tBossmonth_Lottery_random[3007199] = {} 
		tBossmonth_Lottery_random[3007199]["Reward"] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Lottery_random[3007199]["Reward"][1][1] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][1]["ItemChance"] = 3000
		tBossmonth_Lottery_random[3007199]["Reward"][1][1]["Item_1"] = 3007221
		tBossmonth_Lottery_random[3007199]["Reward"][1][1]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][1]["Log"] = "0,0,0,0,12000173,2,3007221,1"

		tBossmonth_Lottery_random[3007199]["Reward"][1][2] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][2]["ItemChance"] = 3000
		tBossmonth_Lottery_random[3007199]["Reward"][1][2]["Item_1"] = 3007160
		tBossmonth_Lottery_random[3007199]["Reward"][1][2]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][2]["Log"] = "0,0,0,0,12000173,2,3007160,1"
		
		tBossmonth_Lottery_random[3007199]["Reward"][1][3] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][3]["ItemChance"] = 1880
		tBossmonth_Lottery_random[3007199]["Reward"][1][3]["Item_1"] = 3007205
		tBossmonth_Lottery_random[3007199]["Reward"][1][3]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][3]["Log"] = "0,0,0,0,12000173,2,3007205,1"
		
		tBossmonth_Lottery_random[3007199]["Reward"][1][4] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][4]["ItemChance"] = 100
		tBossmonth_Lottery_random[3007199]["Reward"][1][4]["Item_1"] = 3007206
		tBossmonth_Lottery_random[3007199]["Reward"][1][4]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][4]["Log"] = "0,0,0,0,12000173,2,3007206,1"

		tBossmonth_Lottery_random[3007199]["Reward"][1][5] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][5]["ItemChance"] = 1700
		tBossmonth_Lottery_random[3007199]["Reward"][1][5]["Item_1"] = 3007200
		tBossmonth_Lottery_random[3007199]["Reward"][1][5]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][5]["Log"] = "0,0,0,0,12000173,2,3007200,1"

		tBossmonth_Lottery_random[3007199]["Reward"][1][6] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][6]["ItemChance"] = 100
		tBossmonth_Lottery_random[3007199]["Reward"][1][6]["Item_1"] = 3007211
		tBossmonth_Lottery_random[3007199]["Reward"][1][6]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][6]["Log"] = "0,0,0,0,12000173,2,3007211,1"
		
		tBossmonth_Lottery_random[3007199]["Reward"][1][7] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][7]["ItemChance"] = 100
		tBossmonth_Lottery_random[3007199]["Reward"][1][7]["Item_1"] = 3007209
		tBossmonth_Lottery_random[3007199]["Reward"][1][7]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][7]["Log"] = "0,0,0,0,12000173,2,3007209,1"
		
		tBossmonth_Lottery_random[3007199]["Reward"][1][8] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][8]["ItemChance"] = 60
		tBossmonth_Lottery_random[3007199]["Reward"][1][8]["Item_1"] = 3007214
		tBossmonth_Lottery_random[3007199]["Reward"][1][8]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][8]["Log"] = "0,0,0,0,12000173,2,3007214,1"
		
		tBossmonth_Lottery_random[3007199]["Reward"][1][9] = {}
		tBossmonth_Lottery_random[3007199]["Reward"][1][9]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007199]["Reward"][1][9]["ItemChance"] = 60
		tBossmonth_Lottery_random[3007199]["Reward"][1][9]["Item_1"] = 3007210
		tBossmonth_Lottery_random[3007199]["Reward"][1][9]["Attr"] = 1
		tBossmonth_Lottery_random[3007199]["Reward"][1][9]["Log"] = "0,0,0,0,12000173,2,3007210,1"

		tBossmonth_Lottery_random[3007200] = {} 
		tBossmonth_Lottery_random[3007200]["Reward"] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1]["ItemChanceSum"] = 10000
		
		tBossmonth_Lottery_random[3007200]["Reward"][1][1] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][1]["ItemChance"] = 2200
		tBossmonth_Lottery_random[3007200]["Reward"][1][1]["Item_1"] = 3007206
		tBossmonth_Lottery_random[3007200]["Reward"][1][1]["Attr"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][1]["Log"] = "0,0,0,0,12000173,2,3007206,2"

		tBossmonth_Lottery_random[3007200]["Reward"][1][2] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][2]["ItemChance"] = 3400
		tBossmonth_Lottery_random[3007200]["Reward"][1][2]["Item_1"] = 3007211
		tBossmonth_Lottery_random[3007200]["Reward"][1][2]["Attr"] = 1
		tBossmonth_Lottery_random[3007200]["Reward"][1][2]["Log"] = "0,0,0,0,12000173,2,3007211,1"

		tBossmonth_Lottery_random[3007200]["Reward"][1][3] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][3]["ItemChance"] = 1700
		tBossmonth_Lottery_random[3007200]["Reward"][1][3]["Item_1"] = 3007209
		tBossmonth_Lottery_random[3007200]["Reward"][1][3]["Attr"] = 1
		tBossmonth_Lottery_random[3007200]["Reward"][1][3]["Log"] = "0,0,0,0,12000173,2,3007209,1"

		tBossmonth_Lottery_random[3007200]["Reward"][1][4] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][4]["ItemChance"] = 1800
		tBossmonth_Lottery_random[3007200]["Reward"][1][4]["Item_1"] = 3007214
		tBossmonth_Lottery_random[3007200]["Reward"][1][4]["Attr"] = 1
		tBossmonth_Lottery_random[3007200]["Reward"][1][4]["Log"] = "0,0,0,0,12000173,2,3007214,1"

		tBossmonth_Lottery_random[3007200]["Reward"][1][5] = {}
		tBossmonth_Lottery_random[3007200]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Lottery_random[3007200]["Reward"][1][5]["ItemChance"] = 900
		tBossmonth_Lottery_random[3007200]["Reward"][1][5]["Item_1"] = 3007210
		tBossmonth_Lottery_random[3007200]["Reward"][1][5]["Attr"] = 1
		tBossmonth_Lottery_random[3007200]["Reward"][1][5]["Log"] = "0,0,0,0,12000173,2,3007210,1"

local	tBossmonth_Make_random = {} 
		tBossmonth_Make_random[3007158] = {} --普通图纸制作的概率
		tBossmonth_Make_random[3007158]["Reward"] = {}
		tBossmonth_Make_random[3007158]["Reward"][1] = {}
		tBossmonth_Make_random[3007158]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Make_random[3007158]["Reward"][1][1] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][1]["ItemChance"] = 2000
		tBossmonth_Make_random[3007158]["Reward"][1][1]["Item_1"] = 3002029
		tBossmonth_Make_random[3007158]["Reward"][1][1]["Log"] = "0,0,3007158,1,12000173,2,3002029,1"
		tBossmonth_Make_random[3007158]["Reward"][1][1]["Effect"] = "angelwing"
		tBossmonth_Make_random[3007158]["Reward"][1][1]["Attr"] = "0 0 0 0 1"

		tBossmonth_Make_random[3007158]["Reward"][1][2] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][2]["ItemChance"] = 2000
		tBossmonth_Make_random[3007158]["Reward"][1][2]["Item_1"] = 3002554
		tBossmonth_Make_random[3007158]["Reward"][1][2]["Log"] = "0,0,3007158,1,12000173,2,3002554,1"
		tBossmonth_Make_random[3007158]["Reward"][1][2]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007158]["Reward"][1][3] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][3]["ItemChance"] = 1200
		tBossmonth_Make_random[3007158]["Reward"][1][3]["Item_1"] = 3007159
		tBossmonth_Make_random[3007158]["Reward"][1][3]["Log"] = "0,0,3007158,1,12000173,2,3007159,1"
		tBossmonth_Make_random[3007158]["Reward"][1][3]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007158]["Reward"][1][4] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][4]["ItemChance"] = 2400
		tBossmonth_Make_random[3007158]["Reward"][1][4]["Item_1"] = 3007205
		tBossmonth_Make_random[3007158]["Reward"][1][4]["Log"] = "0,0,3007158,1,12000173,2,3007205,1"
		tBossmonth_Make_random[3007158]["Reward"][1][4]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007158]["Reward"][1][5] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][5]["ItemChance"] = 800
		tBossmonth_Make_random[3007158]["Reward"][1][5]["Item_1"] = 3007206
		tBossmonth_Make_random[3007158]["Reward"][1][5]["Log"] = "0,0,3007158,1,12000173,2,3007206,1"
		tBossmonth_Make_random[3007158]["Reward"][1][5]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007158]["Reward"][1][6] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][6]["ItemChance"] = 600
		tBossmonth_Make_random[3007158]["Reward"][1][6]["Item_1"] = 3007201
		tBossmonth_Make_random[3007158]["Reward"][1][6]["Log"] = "0,0,3007158,1,12000173,2,3007201,1"
		tBossmonth_Make_random[3007158]["Reward"][1][6]["Effect"] = "zf2-e280"

		tBossmonth_Make_random[3007158]["Reward"][1][7] = {}
		tBossmonth_Make_random[3007158]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007158]["Reward"][1][7]["ItemChance"] = 1000
		tBossmonth_Make_random[3007158]["Reward"][1][7]["Item_1"] = 3007199
		tBossmonth_Make_random[3007158]["Reward"][1][7]["Log"] = "0,0,3007158,1,12000173,2,3007199,1"
		tBossmonth_Make_random[3007158]["Reward"][1][7]["Effect"] = "zf2-e280"

		tBossmonth_Make_random[3007159] = {} --良品图纸制作的概率
		tBossmonth_Make_random[3007159]["Reward"] = {}
		tBossmonth_Make_random[3007159]["Reward"][1] = {}
		tBossmonth_Make_random[3007159]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Make_random[3007159]["Reward"][1][1] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][1]["ItemChance"] = 2100
		tBossmonth_Make_random[3007159]["Reward"][1][1]["Item_1"] = 3002029
		tBossmonth_Make_random[3007159]["Reward"][1][1]["Log"] = "0,0,3007159,1,12000173,2,3002029,1"
		tBossmonth_Make_random[3007159]["Reward"][1][1]["Effect"] = "angelwing"
		tBossmonth_Make_random[3007159]["Reward"][1][1]["Attr"] = "0 0 0 0 1"

		tBossmonth_Make_random[3007159]["Reward"][1][2] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][2]["ItemChance"] = 2100
		tBossmonth_Make_random[3007159]["Reward"][1][2]["Item_1"] = 3002554
		tBossmonth_Make_random[3007159]["Reward"][1][2]["Log"] = "0,0,3007159,1,12000173,2,3002554,1"
		tBossmonth_Make_random[3007159]["Reward"][1][2]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007159]["Reward"][1][3] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][3]["ItemChance"] = 700
		tBossmonth_Make_random[3007159]["Reward"][1][3]["Item_1"] = 3007160
		tBossmonth_Make_random[3007159]["Reward"][1][3]["Log"] = "0,0,3007159,1,12000173,2,3007160,1"
		tBossmonth_Make_random[3007159]["Reward"][1][3]["Effect"] = "angelwing"

		tBossmonth_Make_random[3007159]["Reward"][1][4] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][4]["ItemChance"] = 2100
		tBossmonth_Make_random[3007159]["Reward"][1][4]["Item_1"] = 3007205
		tBossmonth_Make_random[3007159]["Reward"][1][4]["Log"] = "0,0,3007159,1,12000173,2,3007205,1"
		tBossmonth_Make_random[3007159]["Reward"][1][4]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007159]["Reward"][1][5] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][5]["ItemChance"] = 1000
		tBossmonth_Make_random[3007159]["Reward"][1][5]["Item_1"] = 3007206
		tBossmonth_Make_random[3007159]["Reward"][1][5]["Log"] = "0,0,3007159,1,12000173,2,3007206,1"
		tBossmonth_Make_random[3007159]["Reward"][1][5]["Effect"] = "angelwing"
		
		tBossmonth_Make_random[3007159]["Reward"][1][6] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][6]["ItemChance"] = 800
		tBossmonth_Make_random[3007159]["Reward"][1][6]["Item_1"] = 3007201
		tBossmonth_Make_random[3007159]["Reward"][1][6]["Log"] = "0,0,3007159,1,12000173,2,3007201,1"
		tBossmonth_Make_random[3007159]["Reward"][1][6]["Effect"] = "zf2-e280"
		
		tBossmonth_Make_random[3007159]["Reward"][1][7] = {}
		tBossmonth_Make_random[3007159]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007159]["Reward"][1][7]["ItemChance"] = 1200
		tBossmonth_Make_random[3007159]["Reward"][1][7]["Item_1"] = 3007199
		tBossmonth_Make_random[3007159]["Reward"][1][7]["Log"] = "0,0,3007159,1,12000173,2,3007199,1"
		tBossmonth_Make_random[3007159]["Reward"][1][7]["Effect"] = "zf2-e280"

		tBossmonth_Make_random[3007160] = {} --上品图纸制作的概率
		tBossmonth_Make_random[3007160]["Reward"] = {}
		tBossmonth_Make_random[3007160]["Reward"][1] = {}
		tBossmonth_Make_random[3007160]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Make_random[3007160]["Reward"][1][1] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][1]["ItemChance"] = 2200
		tBossmonth_Make_random[3007160]["Reward"][1][1]["Item_1"] = 3002029
		tBossmonth_Make_random[3007160]["Reward"][1][1]["Log"] = "0,0,3007160,1,12000173,2,3002029,1"
		tBossmonth_Make_random[3007160]["Reward"][1][1]["Effect"] = "angelwing"
		tBossmonth_Make_random[3007160]["Reward"][1][1]["Attr"] = "0 0 0 0 1"

		tBossmonth_Make_random[3007160]["Reward"][1][2] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][2]["ItemChance"] = 2200
		tBossmonth_Make_random[3007160]["Reward"][1][2]["Item_1"] = 3002554
		tBossmonth_Make_random[3007160]["Reward"][1][2]["Log"] = "0,0,3007160,1,12000173,2,3002554,1"
		tBossmonth_Make_random[3007160]["Reward"][1][2]["Effect"] = "angelwing"

		tBossmonth_Make_random[3007160]["Reward"][1][3] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][3]["ItemChance"] = 1800
		tBossmonth_Make_random[3007160]["Reward"][1][3]["Item_1"] = 3007205
		tBossmonth_Make_random[3007160]["Reward"][1][3]["Log"] = "0,0,3007160,1,12000173,2,3007205,1"
		tBossmonth_Make_random[3007160]["Reward"][1][3]["Effect"] = "angelwing"

		tBossmonth_Make_random[3007160]["Reward"][1][4] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][4]["ItemChance"] = 1200
		tBossmonth_Make_random[3007160]["Reward"][1][4]["Item_1"] = 3007206
		tBossmonth_Make_random[3007160]["Reward"][1][4]["Log"] = "0,0,3007160,1,12000173,2,3007206,1"
		tBossmonth_Make_random[3007160]["Reward"][1][4]["Effect"] = "angelwing"

		tBossmonth_Make_random[3007160]["Reward"][1][5] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][5]["ItemChance"] = 1000
		tBossmonth_Make_random[3007160]["Reward"][1][5]["Item_1"] = 3007201
		tBossmonth_Make_random[3007160]["Reward"][1][5]["Log"] = "0,0,3007160,1,12000173,2,3007201,1"
		tBossmonth_Make_random[3007160]["Reward"][1][5]["Effect"] = "zf2-e280"

		tBossmonth_Make_random[3007160]["Reward"][1][6] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][6]["ItemChance"] = 1500
		tBossmonth_Make_random[3007160]["Reward"][1][6]["Item_1"] = 3007199
		tBossmonth_Make_random[3007160]["Reward"][1][6]["Log"] = "0,0,3007160,1,12000173,2,3007199,1"
		tBossmonth_Make_random[3007160]["Reward"][1][6]["Effect"] = "zf2-e280"

		tBossmonth_Make_random[3007160]["Reward"][1][7] = {}
		tBossmonth_Make_random[3007160]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Make_random[3007160]["Reward"][1][7]["ItemChance"] = 100
		tBossmonth_Make_random[3007160]["Reward"][1][7]["Item_1"] = 3007200
		tBossmonth_Make_random[3007160]["Reward"][1][7]["Log"] = "0,0,3007160,1,12000173,2,3007200,1"
		tBossmonth_Make_random[3007160]["Reward"][1][7]["Effect"] = "zf2-e280"


--片区怪掉落
--第3片区
local	tBossmonth_Monster_random = {} 
		tBossmonth_Monster_random[1] = {} 
		tBossmonth_Monster_random[1]["Reward"] = {}
		tBossmonth_Monster_random[1]["Reward"][1] = {}
		tBossmonth_Monster_random[1]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Monster_random[1]["Reward"][1][1] = {}
		tBossmonth_Monster_random[1]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][1]["ItemChance"] = 275
		tBossmonth_Monster_random[1]["Reward"][1][1]["Item_1"] = 3007186

		tBossmonth_Monster_random[1]["Reward"][1][2] = {}
		tBossmonth_Monster_random[1]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][2]["ItemChance"] = 55
		tBossmonth_Monster_random[1]["Reward"][1][2]["Item_1"] = 3007183

		tBossmonth_Monster_random[1]["Reward"][1][3] = {}
		tBossmonth_Monster_random[1]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][3]["ItemChance"] = 55
		tBossmonth_Monster_random[1]["Reward"][1][3]["Item_1"] = 3007184

		tBossmonth_Monster_random[1]["Reward"][1][4] = {}
		tBossmonth_Monster_random[1]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][4]["ItemChance"] = 55
		tBossmonth_Monster_random[1]["Reward"][1][4]["Item_1"] = 3007185

		tBossmonth_Monster_random[1]["Reward"][1][5] = {}
		tBossmonth_Monster_random[1]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][5]["ItemChance"] = 50
		tBossmonth_Monster_random[1]["Reward"][1][5]["Item_1"] = 3007168

		tBossmonth_Monster_random[1]["Reward"][1][6] = {}
		tBossmonth_Monster_random[1]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][6]["ItemChance"] = 75
		tBossmonth_Monster_random[1]["Reward"][1][6]["Item_1"] = 3007158

		tBossmonth_Monster_random[1]["Reward"][1][7] = {}
		tBossmonth_Monster_random[1]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][7]["ItemChance"] = 10
		tBossmonth_Monster_random[1]["Reward"][1][7]["Item_1"] = 3007159

		tBossmonth_Monster_random[1]["Reward"][1][8] = {}
		tBossmonth_Monster_random[1]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[1]["Reward"][1][8]["ItemChance"] = 9425
		tBossmonth_Monster_random[1]["Reward"][1][8]["Item_1"] = nil

--第4片区
		tBossmonth_Monster_random[2] = {} 
		tBossmonth_Monster_random[2]["Reward"] = {}
		tBossmonth_Monster_random[2]["Reward"][1] = {}
		tBossmonth_Monster_random[2]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Monster_random[2]["Reward"][1][1] = {}
		tBossmonth_Monster_random[2]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][1]["ItemChance"] = 275
		tBossmonth_Monster_random[2]["Reward"][1][1]["Item_1"] = 3007186
		
		tBossmonth_Monster_random[2]["Reward"][1][2] = {}
		tBossmonth_Monster_random[2]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][2]["ItemChance"] = 55
		tBossmonth_Monster_random[2]["Reward"][1][2]["Item_1"] = 3007183
		
		tBossmonth_Monster_random[2]["Reward"][1][3] = {}
		tBossmonth_Monster_random[2]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][3]["ItemChance"] = 55
		tBossmonth_Monster_random[2]["Reward"][1][3]["Item_1"] = 3007184
		
		tBossmonth_Monster_random[2]["Reward"][1][4] = {}
		tBossmonth_Monster_random[2]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][4]["ItemChance"] = 55
		tBossmonth_Monster_random[2]["Reward"][1][4]["Item_1"] = 3007185
		
		tBossmonth_Monster_random[2]["Reward"][1][5] = {}
		tBossmonth_Monster_random[2]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][5]["ItemChance"] = 50
		tBossmonth_Monster_random[2]["Reward"][1][5]["Item_1"] = 3007169

		tBossmonth_Monster_random[2]["Reward"][1][6] = {}
		tBossmonth_Monster_random[2]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][6]["ItemChance"] = 75
		tBossmonth_Monster_random[2]["Reward"][1][6]["Item_1"] = 3007158

		tBossmonth_Monster_random[2]["Reward"][1][7] = {}
		tBossmonth_Monster_random[2]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][7]["ItemChance"] = 10
		tBossmonth_Monster_random[2]["Reward"][1][7]["Item_1"] = 3007159

		tBossmonth_Monster_random[2]["Reward"][1][8] = {}
		tBossmonth_Monster_random[2]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[2]["Reward"][1][8]["ItemChance"] = 9425
		tBossmonth_Monster_random[2]["Reward"][1][8]["Item_1"] = nil

--第5片区
		tBossmonth_Monster_random[3] = {} 
		tBossmonth_Monster_random[3]["Reward"] = {}
		tBossmonth_Monster_random[3]["Reward"][1] = {}
		tBossmonth_Monster_random[3]["Reward"][1]["ItemChanceSum"] = 10000
		
		tBossmonth_Monster_random[3]["Reward"][1][1] = {}
		tBossmonth_Monster_random[3]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][1]["ItemChance"] = 275
		tBossmonth_Monster_random[3]["Reward"][1][1]["Item_1"] = 3007186
		
		tBossmonth_Monster_random[3]["Reward"][1][2] = {}
		tBossmonth_Monster_random[3]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][2]["ItemChance"] = 55
		tBossmonth_Monster_random[3]["Reward"][1][2]["Item_1"] = 3007183
		
		tBossmonth_Monster_random[3]["Reward"][1][3] = {}
		tBossmonth_Monster_random[3]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][3]["ItemChance"] = 55
		tBossmonth_Monster_random[3]["Reward"][1][3]["Item_1"] = 3007184

		tBossmonth_Monster_random[3]["Reward"][1][4] = {}
		tBossmonth_Monster_random[3]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][4]["ItemChance"] = 55
		tBossmonth_Monster_random[3]["Reward"][1][4]["Item_1"] = 3007185
		
		tBossmonth_Monster_random[3]["Reward"][1][5] = {}
		tBossmonth_Monster_random[3]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][5]["ItemChance"] = 50
		tBossmonth_Monster_random[3]["Reward"][1][5]["Item_1"] = 3007170

		tBossmonth_Monster_random[3]["Reward"][1][6] = {}
		tBossmonth_Monster_random[3]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][6]["ItemChance"] = 75
		tBossmonth_Monster_random[3]["Reward"][1][6]["Item_1"] = 3007158

		tBossmonth_Monster_random[3]["Reward"][1][7] = {}
		tBossmonth_Monster_random[3]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][7]["ItemChance"] = 10
		tBossmonth_Monster_random[3]["Reward"][1][7]["Item_1"] = 3007159

		tBossmonth_Monster_random[3]["Reward"][1][8] = {}
		tBossmonth_Monster_random[3]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[3]["Reward"][1][8]["ItemChance"] = 9425
		tBossmonth_Monster_random[3]["Reward"][1][8]["Item_1"] = nil

--敦煌，冰封，海底
		tBossmonth_Monster_random[4] = {} 
		tBossmonth_Monster_random[4]["Reward"] = {}
		tBossmonth_Monster_random[4]["Reward"][1] = {}
		tBossmonth_Monster_random[4]["Reward"][1]["ItemChanceSum"] = 10000

		tBossmonth_Monster_random[4]["Reward"][1][1] = {}
		tBossmonth_Monster_random[4]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][1]["ItemChance"] = 265
		tBossmonth_Monster_random[4]["Reward"][1][1]["Item_1"] = 3007186
		
		tBossmonth_Monster_random[4]["Reward"][1][2] = {}
		tBossmonth_Monster_random[4]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][2]["ItemChance"] = 53
		tBossmonth_Monster_random[4]["Reward"][1][2]["Item_1"] = 3007183
		
		tBossmonth_Monster_random[4]["Reward"][1][3] = {}
		tBossmonth_Monster_random[4]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][3]["ItemChance"] = 53
		tBossmonth_Monster_random[4]["Reward"][1][3]["Item_1"] = 3007184
		
		tBossmonth_Monster_random[4]["Reward"][1][4] = {}
		tBossmonth_Monster_random[4]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][4]["ItemChance"] = 53
		tBossmonth_Monster_random[4]["Reward"][1][4]["Item_1"] = 3007185
		
		tBossmonth_Monster_random[4]["Reward"][1][5] = {}
		tBossmonth_Monster_random[4]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][5]["ItemChance"] = 16
		tBossmonth_Monster_random[4]["Reward"][1][5]["Item_1"] = 3007168
		
		tBossmonth_Monster_random[4]["Reward"][1][6] = {}
		tBossmonth_Monster_random[4]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][6]["ItemChance"] = 16
		tBossmonth_Monster_random[4]["Reward"][1][6]["Item_1"] = 3007169
		
		tBossmonth_Monster_random[4]["Reward"][1][7] = {}
		tBossmonth_Monster_random[4]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][7]["ItemChance"] = 16
		tBossmonth_Monster_random[4]["Reward"][1][7]["Item_1"] = 3007170

		tBossmonth_Monster_random[4]["Reward"][1][8] = {}
		tBossmonth_Monster_random[4]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][8]["ItemChance"] = 75
		tBossmonth_Monster_random[4]["Reward"][1][8]["Item_1"] = 3007158

		tBossmonth_Monster_random[4]["Reward"][1][9] = {}
		tBossmonth_Monster_random[4]["Reward"][1][9]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][9]["ItemChance"] = 10
		tBossmonth_Monster_random[4]["Reward"][1][9]["Item_1"] = 3007159

		tBossmonth_Monster_random[4]["Reward"][1][10] = {}
		tBossmonth_Monster_random[4]["Reward"][1][10]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[4]["Reward"][1][10]["ItemChance"] = 9443
		tBossmonth_Monster_random[4]["Reward"][1][10]["Item_1"] = nil

--boss掉落
		tBossmonth_Monster_random[5] = {} 
		tBossmonth_Monster_random[5]["Reward"] = {}
		tBossmonth_Monster_random[5]["Reward"][1] = {}
		tBossmonth_Monster_random[5]["Reward"][1]["ItemChanceSum"] = 10000
		
		tBossmonth_Monster_random[5]["Reward"][1][1] = {}
		tBossmonth_Monster_random[5]["Reward"][1][1]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][1]["ItemChance"] = 2200
		tBossmonth_Monster_random[5]["Reward"][1][1]["Item_1"] = 3007184
		
		tBossmonth_Monster_random[5]["Reward"][1][2] = {}
		tBossmonth_Monster_random[5]["Reward"][1][2]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][2]["ItemChance"] = 2200
		tBossmonth_Monster_random[5]["Reward"][1][2]["Item_1"] = 3007185
		
		tBossmonth_Monster_random[5]["Reward"][1][3] = {}
		tBossmonth_Monster_random[5]["Reward"][1][3]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][3]["ItemChance"] = 2200
		tBossmonth_Monster_random[5]["Reward"][1][3]["Item_1"] = 3007186

		tBossmonth_Monster_random[5]["Reward"][1][4] = {}
		tBossmonth_Monster_random[5]["Reward"][1][4]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][4]["ItemChance"] = 900
		tBossmonth_Monster_random[5]["Reward"][1][4]["Item_1"] = 3007168

		tBossmonth_Monster_random[5]["Reward"][1][5] = {}
		tBossmonth_Monster_random[5]["Reward"][1][5]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][5]["ItemChance"] = 900
		tBossmonth_Monster_random[5]["Reward"][1][5]["Item_1"] = 3007169

		tBossmonth_Monster_random[5]["Reward"][1][6] = {}
		tBossmonth_Monster_random[5]["Reward"][1][6]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][6]["ItemChance"] = 900
		tBossmonth_Monster_random[5]["Reward"][1][6]["Item_1"] = 3007170

		tBossmonth_Monster_random[5]["Reward"][1][7] = {}
		tBossmonth_Monster_random[5]["Reward"][1][7]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][7]["ItemChance"] = 400
		tBossmonth_Monster_random[5]["Reward"][1][7]["Item_1"] = 3007158
		tBossmonth_Monster_random[5]["Reward"][1][7]["SysDynaGlobalLimit"] = 80
		tBossmonth_Monster_random[5]["Reward"][1][7]["SysDynaGlobal"] = 50953
		
		tBossmonth_Monster_random[5]["Reward"][1][8] = {}
		tBossmonth_Monster_random[5]["Reward"][1][8]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][8]["ItemChance"] = 200
		tBossmonth_Monster_random[5]["Reward"][1][8]["Item_1"] = 3007159
		tBossmonth_Monster_random[5]["Reward"][1][8]["SysDynaGlobalLimit"] = 40
		tBossmonth_Monster_random[5]["Reward"][1][8]["SysDynaGlobal"] = 50954

		tBossmonth_Monster_random[5]["Reward"][1][9] = {}
		tBossmonth_Monster_random[5]["Reward"][1][9]["RandomItemChanceType"] = 2
		tBossmonth_Monster_random[5]["Reward"][1][9]["ItemChance"] = 100
		tBossmonth_Monster_random[5]["Reward"][1][9]["Item_1"] = 3007160
		tBossmonth_Monster_random[5]["Reward"][1][9]["SysDynaGlobalLimit"] = 16
		tBossmonth_Monster_random[5]["Reward"][1][9]["SysDynaGlobal"] = 50955


local	tBossmonth_log = {} --12000173
		tBossmonth_log[1] = "0,0,3007157,1,12000173,1[1],4,30"  --背包信30分钟经验
		tBossmonth_log[2] = "0,0,3007157,1,12000173,1[1],6,15"  --背包信15修行值
		tBossmonth_log[3] = "9,0,0,0,12000173,1,0,0" --花费9天石购买配方
		tBossmonth_log[4] = "[200000],0,0,0,12000173,1,0,0"  --花费20W随机配方
		tBossmonth_log[5] = "0,0,%d,%d,12000173,1,0,0" --花费物品进行抽奖
		tBossmonth_log[6] = "%d,0,0,0,12000173,1,0,0" --花费天石进行抽奖
		tBossmonth_log[7] = "0,0,0,0,12000173,2,%d,0" --领取配方
		tBossmonth_log[8] = "0,0,%d,%d,12000173,2,%d,%d" --回收成品外套

		tBossmonth_log["DropLog"] = "0,0,0,0,12000173,1[4],%d,1"
		tBossmonth_log["EmoneyLog"] = {}
		tBossmonth_log["EmoneyLog"][1] = "350	4325	9	9	1	"

-------------------------------------------------NPC逻辑部分-------------------------------------------------
--雪宝
--研究高级配方。
function Bossmonth_Option40_10870(nNpcId,nItemId,Num)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	if not Item_ChkMulItem (nItemId,nItemId,Num) then
		Sys_DialogText(tBossmonth_Text[nItemId][4][Num])
		Sys_DialogOption(tBossmonth_Text[nItemId][5][Num],"</F>Bossmonth_Option40_10870_1_1</N>10870</N>"..Num.."</N>"..nItemId)
		Sys_DialogOption(tBossmonth_Text[21]) 
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
		return
	end

	if not User_CheckLeftSpace(5) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	if Item_DelMulItem(nItemId,nItemId,Num) then
		local sLog = string.format(tBossmonth_log[5],nItemId,Num)
		Sys_SaveActionFestivalLog(sLog)
		Bossmonth_Option40_10870_Lottery(nNpcId,Num,nItemId)
	end
end


function Bossmonth_Option40_10870_Lottery(nNpcId,Num,nItemId)
	for i = 1,Num do
		local flat,tNum = Probabil_RandomAward(tBossmonth_Lottery_random[nItemId]["Reward"],1)  
		local nItemId_1 = tNum[1]["tAward"][1]["Item_1"]
		local sLog = tNum[1]["tAward"][1]["Log"]
		local nAttr = tNum[1]["tAward"][1]["Attr"]
		local sItemName = Get_ItemtypeName(nItemId_1)
		local sText = string.format(tBossmonth_Text[nItemId][6],nAttr,sItemName)
		Item_AddItem(nItemId_1,0,nAttr)
		User_TalkChannel2005(sText)
		User_EffectAdd("self","angelwing")
		Sys_SaveActionFestivalLog(sLog)
	end
		LinkNpcGossipFunc_New(nNpcId,"2-4")
end

--用天石
function Bossmonth_Option40_10870_1_1(nNpcId,nNum,nItemId)
	if not User_CheckLeftSpace(5) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	local nEmoney = Get_UserEMoney()
	if nEmoney >= tBossmonth_Cont[nItemId]["Emoney"][nNum] and User_AddEMoney(-tBossmonth_Cont[nItemId]["Emoney"][nNum]) then
		local nEmoney_1 = tBossmonth_Cont[nItemId]["Emoney"][nNum]
		local sLog = string.format(tBossmonth_log[6],nEmoney_1)
		Sys_SaveActionFestivalLog(sLog)
		Sys_SaveEmoneyBuy(tBossmonth_Cont[nItemId]["EmoneyLog"][nNum])
		Bossmonth_Option40_10870_Lottery(nNpcId,nNum,nItemId)
	else 
		LinkNpcGossipFunc_New(nNpcId,"4-1")

	end
end

--兑换辉煌版
function Bossmonth_Option70_10870(nNpcId)
	-- if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		-- LinkNpcGossipFunc_New(nNpcId,"1-2")
		-- return
	-- end

	if not Item_ChkMulItem (193445,193445,3) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	if Item_DelMulItem(193445,193445,3) then
		local sUserName = Get_UserName()
		local sText = string.format(tBossmonth_Text[35],sUserName)
		Item_AddItem(193525,0,0,0,0,0,0,0,1)
		Sys_SaveActionFestivalLog("0,0,193445,3,12000173,2,193525,1")
		User_TalkChannel2005(tBossmonth_Text[34])
		Sys_NormalBroadcast(sText)
		User_EffectAdd("self","accession")
	end

end

----------------------------------------
--新增兑换NPC
--5合1，二次确认
function Bossmonth_Option5_10888(nNpcId,nItemId)
	Sys_DialogText(tBossmonth_Text[nItemId][7])
	Sys_DialogOption(tBossmonth_Text[20],"</F>Bossmonth_Option5_10888_1</N>10888</N>"..nItemId)
	Sys_DialogOption(tBossmonth_Text[21]) 
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()

end

function Bossmonth_Option5_10888_1(nNpcId,nItemId)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	if not Item_ChkMulItem (tBossmonth_Cont[nItemId]["compose"],tBossmonth_Cont[nItemId]["compose"],tBossmonth_Cont[nItemId]["Num"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end

	if Item_DelMulItem (tBossmonth_Cont[nItemId]["compose"],tBossmonth_Cont[nItemId]["compose"],tBossmonth_Cont[nItemId]["Num"]) then
		Item_AddItem(nItemId)
		User_TalkChannel2005(tBossmonth_Text[nItemId][8])
		User_EffectAdd("self","angelwing")
	end

end

--回收成品外套
function Bossmonth_Option10_10888(nNpcId,nItemId)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end	

	if not Item_ChkItem(nItemId) then 
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	if Item_DelItem(nItemId) then
		local nAddItem = tBossmonth_Cont[nItemId]["AddItem"]
		local nNum = tBossmonth_Cont[nItemId]["Num"]
		local sLog = string.format(tBossmonth_log[8],nItemId,1,nAddItem,nNum)
		Item_AddItem(tBossmonth_Cont[nItemId]["AddItem"],0,tBossmonth_Cont[nItemId]["Num"])
		User_TalkChannel2005(tBossmonth_Text[nItemId]["Text"])
		Sys_SaveActionFestivalLog(sLog)
		User_EffectAdd("self","angelwing")
		LinkNpcGossipFunc_New(nNpcId,"2-1")
	end

end

--购买部件
function Bossmonth_Option30_10888(nNpcId,nItemId)
	Sys_DialogText(tBossmonth_Text[nItemId][1])
	Sys_DialogOption(tBossmonth_Text[10],"</F>Bossmonth_Option30_10888_Text</N>10888</N>1".."</N>"..nItemId) --购买1个（100,000银两）
	Sys_DialogOption(tBossmonth_Text[11],"</F>Bossmonth_Option30_10888_Text</N>10888</N>2".."</N>"..nItemId) --购买10个（1,000,000银两）
	Sys_DialogOption(tBossmonth_Text[12],"</F>Bossmonth_Option30_10888_2</N>10888") --上一页
	Sys_DialogOption(tBossmonth_Text[13]) --离开
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end

--2次确认
function Bossmonth_Option30_10888_Text(nNpcId,nOption,nItemId)
	Sys_DialogText(tBossmonth_Text[nItemId][2][nOption])
	Sys_DialogOption(tBossmonth_Text[20],"</F>Bossmonth_Option30_10888_1</N>10888</N>"..nOption.."</N>"..nItemId) 
	Sys_DialogOption(tBossmonth_Text[21])
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()

end


----购买1个或10个，通用
function Bossmonth_Option30_10888_1(nNpcId,nOption,nItemId)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end	

	if User_CanPutMoney2Bag(-tBossmonth_Cont[nItemId]["price"][nOption]) and User_AddMoney(-tBossmonth_Cont[nItemId]["price"][nOption]) then
		local nMoney = tBossmonth_Cont[nItemId]["price"][nOption]
		local nNum = tBossmonth_Cont[nItemId]["amount"][nOption]
		Item_AddItem(nItemId,0,tBossmonth_Cont[nItemId]["amount"][nOption])
		User_TalkChannel2005(tBossmonth_Text[nItemId][3][nOption])
		Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log"][nOption])
	else 
		LinkNpcGossipFunc_New(nNpcId,"4-2")
	end

end

function Bossmonth_Option30_10888_2(nNpcId)
	LinkNpcGossipFunc_New(nNpcId,"3-4")
end

--购买全套3种部件
function Bossmonth_Option40_10888(nNpcId,nNum)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	if not User_CheckLeftSpace(3) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end	

	local nMoney = tBossmonth_Cont["price"][nNum]
	if User_CanPutMoney2Bag(-nMoney) and User_AddMoney(-nMoney) then
		for i = 1,3 do
			Item_AddItem(tBossmonth_Cont["ItemId"][i],0,nNum)
		end
		User_TalkChannel2005(tBossmonth_Text[6][nNum])
		Sys_SaveActionFestivalLog(tBossmonth_Cont["Log"][nNum])
	else 
		LinkNpcGossipFunc_New(nNpcId,"4-2")
	end

end

-------------------------------------------------NPC模板部分-------------------------------------------------
--雪宝
tNpcFace[3780] = 220
tNpcGossip[10870] = tNpcGossip[10870] or DefaultNpc:new{}
tNpcGossip[10870]["OptionHidden"] = 1

--活动前
tNpcGossip[10870]["Text1-1"] = {111,112,113}
tNpcGossip[10870]["Text111"] = tBossmonth_Text[10870]["Text111"]
tNpcGossip[10870]["Text112"] = tBossmonth_Text[10870]["Text112"] 
tNpcGossip[10870]["Text113"] = tBossmonth_Text[10870]["Text113"]
tNpcGossip[10870]["tOption1-1"] = {1}
tNpcGossip[10870]["Option1"] = tBossmonth_Text[10870]["Option1"]
tNpcGossip[10870]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Beftime"])
end 

--活动后
tNpcGossip[10870]["Text1-2"] = {121,122}
tNpcGossip[10870]["Text121"] = tBossmonth_Text[10870]["Text121"]
tNpcGossip[10870]["Text122"] = tBossmonth_Text[10870]["Text122"]
tNpcGossip[10870]["tOption1-2"] = {2,8}
tNpcGossip[10870]["Option2"] = tBossmonth_Text[10870]["Option2"]
tNpcGossip[10870]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Aftime"])
end 

--活动中
--等级不够
tNpcGossip[10870]["Text1-3"] = {131,132}
tNpcGossip[10870]["Text131"] = tBossmonth_Text[10870]["Text131"]
tNpcGossip[10870]["Text132"] = tBossmonth_Text[10870]["Text132"]
tNpcGossip[10870]["tOption1-3"] = {3}
tNpcGossip[10870]["Option3"] = tBossmonth_Text[10870]["Option3"]
tNpcGossip[10870]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) and not User_JudgeLevelAndMetempsychosis(tBossmonth_Cont["Level"],tBossmonth_Cont["Metempsychosis"])
end 

--等级够
tNpcGossip[10870]["Text1-4"] = {141,142,143}
tNpcGossip[10870]["Text141"] = tBossmonth_Text[10870]["Text141"]
tNpcGossip[10870]["Text142"] = tBossmonth_Text[10870]["Text142"]
tNpcGossip[10870]["Text143"] = tBossmonth_Text[10870]["Text143"]
tNpcGossip[10870]["tOption1-4"] = {7,6,8}
tNpcGossip[10870]["Option7"] = tBossmonth_Text[10870]["Option7"]
tNpcGossip[10870]["Option6"] = tBossmonth_Text[10870]["Option6"]
tNpcGossip[10870]["Option8"] = tBossmonth_Text[10870]["Option8"]
tNpcGossip[10870]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) and User_JudgeLevelAndMetempsychosis(tBossmonth_Cont["Level"],tBossmonth_Cont["Metempsychosis"])
end 

--选项接的函数
tNpcGossip[10870]["OptionPoint7"]="2-5"
tNpcGossip[10870]["OptionPoint6"]="2-4"
tNpcGossip[10870]["OptionPoint8"]="2-6"

--选项1其他对话
tNpcGossip[10870]["Text2-2"] = {221}
tNpcGossip[10870]["Text221"] = tBossmonth_Text[10870]["Text221"]
tNpcGossip[10870]["tOption2-2"] = {10}

--选项3其他对话
tNpcGossip[10870]["Text2-4"] = {241,242,243}
tNpcGossip[10870]["Text241"] = tBossmonth_Text[10870]["Text241"]
tNpcGossip[10870]["Text242"] = tBossmonth_Text[10870]["Text242"]
tNpcGossip[10870]["Text243"] = tBossmonth_Text[10870]["Text243"]
tNpcGossip[10870]["tOption2-4"] = {40,41,42}
tNpcGossip[10870]["Option40"] = tBossmonth_Text[10870]["Option40"]
tNpcGossip[10870]["Option41"] = tBossmonth_Text[10870]["Option41"]
tNpcGossip[10870]["Option42"] = tBossmonth_Text[10870]["Option42"]
tNpcGossip[10870]["OptionFunc40"]="Bossmonth_Option40_10870</N>10870</N>3007199</N>1"
tNpcGossip[10870]["OptionPoint41"]="3-1"

--了解活动详情。
tNpcGossip[10870]["Text2-5"] = {251,252}
tNpcGossip[10870]["Text251"] = tBossmonth_Text[10870]["Text251"]
tNpcGossip[10870]["Text252"] = tBossmonth_Text[10870]["Text252"]
tNpcGossip[10870]["tOption2-5"] = {50,54,55}
tNpcGossip[10870]["Option50"] = tBossmonth_Text[10870]["Option50"]
tNpcGossip[10870]["Option54"] = tBossmonth_Text[10870]["Option54"]
tNpcGossip[10870]["Option55"] = tBossmonth_Text[10870]["Option55"]

tNpcGossip[10870]["OptionPoint50"]="3-4"
tNpcGossip[10870]["OptionPoint54"]="1"

--合成辉煌版2次确认
tNpcGossip[10870]["Text2-6"] = {261}
tNpcGossip[10870]["Text261"] = tBossmonth_Text[10870]["Text261"]
tNpcGossip[10870]["tOption2-6"] = {70,71}
tNpcGossip[10870]["Option70"] = tBossmonth_Text[10870]["Option70"]
tNpcGossip[10870]["Option71"] = tBossmonth_Text[10870]["Option71"]

tNpcGossip[10870]["OptionFunc70"]="Bossmonth_Option70_10870</N>10870"

--研究冰封之心。
tNpcGossip[10870]["Text3-1"] = {311,312}
tNpcGossip[10870]["Text311"] = tBossmonth_Text[10870]["Text311"]
tNpcGossip[10870]["tOption3-1"] = {51,52}
tNpcGossip[10870]["Option51"] = tBossmonth_Text[10870]["Option51"]
tNpcGossip[10870]["Option52"] = tBossmonth_Text[10870]["Option52"]
tNpcGossip[10870]["OptionFunc51"]="Bossmonth_Option40_10870</N>10870</N>3007200</N>1"
tNpcGossip[10870]["OptionFunc52"]="Bossmonth_Option40_10870</N>10870</N>3007200</N>10"

--了解妖物掉落。
tNpcGossip[10870]["Text3-4"] = {341,342}
tNpcGossip[10870]["Text341"] = tBossmonth_Text[10870]["Text341"]
tNpcGossip[10870]["Text342"] = tBossmonth_Text[10870]["Text342"]
tNpcGossip[10870]["tOption3-4"] = {60,61}
tNpcGossip[10870]["Option60"] = tBossmonth_Text[10870]["Option60"]
tNpcGossip[10870]["Option61"] = tBossmonth_Text[10870]["Option61"]
tNpcGossip[10870]["OptionPoint60"]="2-5"

--其他对话
tNpcGossip[10870]["Text4-1"] = {411}
tNpcGossip[10870]["Text411"] = tBossmonth_Text[10870]["Text411"]
tNpcGossip[10870]["tOption4-1"] = {100}
tNpcGossip[10870]["Option100"] = tBossmonth_Text[10870]["Option100"]

tNpcGossip[10870]["Text4-2"] = {421}
tNpcGossip[10870]["Text421"] = tBossmonth_Text[10870]["Text421"]
tNpcGossip[10870]["tOption4-2"] = {100}
tNpcGossip[10870]["Option100"] = tBossmonth_Text[10870]["Option100"]



-----------------------------------------------
--兑换npc
tNpcFace[3824] = 215
tNpcGossip[10888] = tNpcGossip[10888] or DefaultNpc:new{}
tNpcGossip[10888]["OptionHidden"] = 1

--活动前
tNpcGossip[10888]["Text1-1"] = {111,112}
tNpcGossip[10888]["Text111"] = tBossmonth_Text[10888]["Text111"]
tNpcGossip[10888]["Text112"] = tBossmonth_Text[10888]["Text112"]
tNpcGossip[10888]["tOption1-1"] = {1}
tNpcGossip[10888]["Option1"] = tBossmonth_Text[10888]["Option1"]
tNpcGossip[10888]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Beftime"])
end 

--活动后
tNpcGossip[10888]["Text1-2"] = {121}
tNpcGossip[10888]["Text121"] = tBossmonth_Text[10888]["Text121"]
tNpcGossip[10888]["tOption1-2"] = {2}
tNpcGossip[10888]["Option2"] = tBossmonth_Text[10888]["Option2"]
tNpcGossip[10888]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Aftime"])
end 

--活动中
--等级不够
tNpcGossip[10888]["Text1-3"] = {131}
tNpcGossip[10888]["Text131"] = tBossmonth_Text[10888]["Text131"]
tNpcGossip[10888]["tOption1-3"] = {3}
tNpcGossip[10888]["Option3"] = tBossmonth_Text[10888]["Option3"]
tNpcGossip[10888]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) and not User_JudgeLevelAndMetempsychosis(tBossmonth_Cont["Level"],tBossmonth_Cont["Metempsychosis"])
end 

--等级够
tNpcGossip[10888]["Text1-4"] = {141,142}
tNpcGossip[10888]["Text141"] = tBossmonth_Text[10888]["Text141"] 
tNpcGossip[10888]["Text142"] = tBossmonth_Text[10888]["Text142"]
tNpcGossip[10888]["tOption1-4"] = {5,6,7,8}
tNpcGossip[10888]["Option5"] = tBossmonth_Text[10888]["Option5"]
tNpcGossip[10888]["Option6"] = tBossmonth_Text[10888]["Option6"]
tNpcGossip[10888]["Option7"] = tBossmonth_Text[10888]["Option7"]
tNpcGossip[10888]["Option8"] = tBossmonth_Text[10888]["Option8"]
tNpcGossip[10888]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) and User_JudgeLevelAndMetempsychosis(tBossmonth_Cont["Level"],tBossmonth_Cont["Metempsychosis"])
end 

tNpcGossip[10888]["OptionChkFunc7"] = function ()
	return Item_ChkItem(3007201) or Item_ChkItem(3007202)
end

tNpcGossip[10888]["OptionFunc5"]="Bossmonth_Option5_10888</N>10888</N>3007159"
tNpcGossip[10888]["OptionFunc6"]="Bossmonth_Option5_10888</N>10888</N>3007160"
tNpcGossip[10888]["OptionPoint7"]="2-1"
tNpcGossip[10888]["OptionPoint8"]="2-2"

tNpcGossip[10888]["Text2-1"] = {211,212}
tNpcGossip[10888]["Text211"] = tBossmonth_Text[10888]["Text211"]
tNpcGossip[10888]["Text212"] = tBossmonth_Text[10888]["Text212"]
tNpcGossip[10888]["tOption2-1"] = {10,11,12,13}
tNpcGossip[10888]["Option10"] = tBossmonth_Text[10888]["Option10"]
tNpcGossip[10888]["Option11"] = tBossmonth_Text[10888]["Option11"]
tNpcGossip[10888]["Option12"] = tBossmonth_Text[10888]["Option12"]
tNpcGossip[10888]["Option13"] = tBossmonth_Text[10888]["Option13"]
tNpcGossip[10888]["OptionFunc10"]="Bossmonth_Option10_10888</N>10888</N>3007201"
tNpcGossip[10888]["OptionFunc11"]="Bossmonth_Option10_10888</N>10888</N>3007202"
tNpcGossip[10888]["OptionPoint12"]="1-4"

tNpcGossip[10888]["Text2-2"] = {221,222}
tNpcGossip[10888]["Text221"] = tBossmonth_Text[10888]["Text221"]
tNpcGossip[10888]["Text222"] = tBossmonth_Text[10888]["Text222"]
tNpcGossip[10888]["tOption2-2"] = {15,16}
tNpcGossip[10888]["Option15"] = tBossmonth_Text[10888]["Option15"]
tNpcGossip[10888]["Option16"] = tBossmonth_Text[10888]["Option16"]
tNpcGossip[10888]["OptionPoint15"]="3-4"

tNpcGossip[10888]["Text3-1"] = {311}
tNpcGossip[10888]["Text311"] = tBossmonth_Text[10888]["Text311"]
tNpcGossip[10888]["tOption3-1"] = {20}
tNpcGossip[10888]["Option20"] = tBossmonth_Text[10888]["Option20"]

tNpcGossip[10888]["Text3-2"] = {321}
tNpcGossip[10888]["Text321"] = tBossmonth_Text[10888]["Text321"]
tNpcGossip[10888]["tOption3-2"] = {20}

tNpcGossip[10888]["Text3-3"] = {331}
tNpcGossip[10888]["Text331"] = tBossmonth_Text[10888]["Text331"]
tNpcGossip[10888]["tOption3-3"] = {20}

tNpcGossip[10888]["Text3-4"] = {341}
tNpcGossip[10888]["Text341"] = tBossmonth_Text[10888]["Text341"]
tNpcGossip[10888]["tOption3-4"] = {30,31,32,33,34}
tNpcGossip[10888]["Option30"] = tBossmonth_Text[10888]["Option30"]
tNpcGossip[10888]["Option31"] = tBossmonth_Text[10888]["Option31"]
tNpcGossip[10888]["Option32"] = tBossmonth_Text[10888]["Option32"]
tNpcGossip[10888]["Option33"] = tBossmonth_Text[10888]["Option33"]
tNpcGossip[10888]["Option34"] = tBossmonth_Text[10888]["Option34"]

tNpcGossip[10888]["OptionFunc30"]="Bossmonth_Option30_10888</N>10888</N>3007163"
tNpcGossip[10888]["OptionFunc31"]="Bossmonth_Option30_10888</N>10888</N>3007164"
tNpcGossip[10888]["OptionFunc32"]="Bossmonth_Option30_10888</N>10888</N>3007165"
tNpcGossip[10888]["OptionPoint33"]="4-1"

tNpcGossip[10888]["Text4-1"] = {411}
tNpcGossip[10888]["Text411"] = tBossmonth_Text[10888]["Text411"]
tNpcGossip[10888]["tOption4-1"] = {40,41,42}
tNpcGossip[10888]["Option40"] = tBossmonth_Text[10888]["Option40"]
tNpcGossip[10888]["Option41"] = tBossmonth_Text[10888]["Option41"]
tNpcGossip[10888]["Option42"] = tBossmonth_Text[10888]["Option42"]

tNpcGossip[10888]["OptionPoint40"]="5-1"
tNpcGossip[10888]["OptionPoint41"]="5-2"
tNpcGossip[10888]["OptionPoint42"]="3-4"

tNpcGossip[10888]["Text4-2"] = {421}
tNpcGossip[10888]["Text421"] = tBossmonth_Text[10888]["Text421"]
tNpcGossip[10888]["tOption4-2"] = {20}

tNpcGossip[10888]["Text5-1"] = {511}
tNpcGossip[10888]["Text511"] = tBossmonth_Text[10888]["Text511"]
tNpcGossip[10888]["tOption5-1"] = {50,51}
tNpcGossip[10888]["Option50"] = tBossmonth_Text[10888]["Option50"]
tNpcGossip[10888]["Option51"] = tBossmonth_Text[10888]["Option51"]
tNpcGossip[10888]["OptionFunc50"]="Bossmonth_Option40_10888</N>10888</N>1"

tNpcGossip[10888]["Text5-2"] = {521}
tNpcGossip[10888]["Text521"] = tBossmonth_Text[10888]["Text521"] 
tNpcGossip[10888]["tOption5-2"] = {52,53}
tNpcGossip[10888]["Option52"] = tBossmonth_Text[10888]["Option52"]
tNpcGossip[10888]["Option53"] = tBossmonth_Text[10888]["Option53"]
tNpcGossip[10888]["OptionFunc52"]="Bossmonth_Option40_10888</N>10888</N>5"




-------------------------------------------------物品模板部分-------------------------------------------------
--背包信
tItem[3007157] = tItem[3007157] or {}
tItem[3007157]["Function"] = function(nItemId,sItemName)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId )then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end
	end

	Sys_DialogText(tBossmonth_Text[nItemId][2])
	Sys_DialogText(tBossmonth_Text[nItemId][3])
	Sys_DialogText(tBossmonth_Text[nItemId][4])
	Sys_DialogOption(tBossmonth_Text[nItemId][5],"</F>Bossmonth_Item_3007157</N>3007157") 
	Sys_DialogEnd()

end

--寻找雪宝
function Bossmonth_Item_3007157(nItemId)
	if Item_DelItem(nItemId) then
		if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end

		local nLevel = Get_UserLevel()
		if nLevel < 140 then
			User_AddExpTime(tBossmonth_Cont["AddExpTime"])
			User_TalkChannel2005(tBossmonth_Text[nItemId][6])
			Sys_SaveActionFestivalLog(tBossmonth_log[1])
		else
			User_AddCultivation(tBossmonth_Cont["AddCultivation"])
			User_TalkChannel2005(tBossmonth_Text[nItemId][7])
			Sys_SaveActionFestivalLog(tBossmonth_log[2])
		end

		Sys_GotoSomeWhere(tBossmonth_Cont["Cellx"],tBossmonth_Cont["Celly"],tBossmonth_Cont["MapId"],tBossmonth_Cont["NpcId"])
	end

end

--各品质冰雪奇缘设计图
function Bossmonth_Item_3007158()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[30])
			return
		end
	end

	if Task_StcInterval(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],1,4) then
		Task_SetStatistic(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],0,1,0)
		Task_SetStcTimestamp(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],0,0)
	end

	if Task_ChkStcValue(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],">=",5) then
		User_TalkChannel2005(tBossmonth_Text[33])
		return
	end

	for i =1,3 do
		if not Item_ChkItem(tBossmonth_Cont["Material"][i]) then
			User_TalkChannel2005(tBossmonth_Text[40])
			return
		end
	end

	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		User_TalkChannel2005(tBossmonth_Text[41])
		return
	end

	if not Item_DelItem(nItemId) then
		return
	end

	for j =1,3 do
		if not Item_DelItem(tBossmonth_Cont["Material"][j]) then
			return
		end
	end

	local flat,tNum = Probabil_RandomAward(tBossmonth_Make_random[nItemId]["Reward"],1)  
	local nItemId_1 = tNum[1]["tAward"][1]["Item_1"]
	local sEffect = tNum[1]["tAward"][1]["Effect"]
	local sAttr = tNum[1]["tAward"][1]["Attr"]
	local sLog = tNum[1]["tAward"][1]["Log"]

	Task_AddStatistic(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],1,1,0)
	Task_SetStcTimestamp(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],0,0)

	if sAttr ~= nil then
		Item_AddNewItem(nItemId_1,sAttr)
	else
		Item_AddItem(nItemId_1)
	end	

	if nItemId_1 == 3007202 then
		Sys_SaveEmoneyBuy(tNum[1]["tAward"][1]["EmoneyLog"])
	end

	Sys_SaveActionFestivalLog(sLog)
	User_EffectAdd("self",sEffect)

	local nLevel = Get_UserLevel()
	local nAddExpTime = tBossmonth_Cont[nItemId]["AddExpTime"]
	local nAddCultivation = tBossmonth_Cont[nItemId]["AddCultivation"]

	if nLevel < 140 then
		User_AddExpTime(nAddExpTime)
		Sys_MsgBox(tBossmonth_Text[nItemId][4][nItemId_1]..tBossmonth_Text[nItemId][5])
		Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["ExpTimeLog"])
	else
		User_AddCultivation(nAddCultivation)
		Sys_MsgBox(tBossmonth_Text[nItemId][4][nItemId_1]..tBossmonth_Text[nItemId][6])
		Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["CultivationLog"])
	end

end

--3个部件
function Bossmonth_Item_3007163()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][4])
			return
		end
	end

	for i = 3007158,3007160 do
		if Item_ChkItem(i) then
			User_TalkChannel2005(tBossmonth_Text[7])
			return
		end
	end

	User_TalkChannel2005(tBossmonth_Text[8])

end

--制造材料
function Bossmonth_Item_3007183()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end
	end

	for i = 3007168,3007170 do
		if Item_ChkItem(i) then
			User_TalkChannel2005(tBossmonth_Text[31] )
			return
		end
	end

	User_TalkChannel2005(tBossmonth_Text[32])

end

--3个部件的设计图
function Bossmonth_Item_3007168()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[30])
			return
		end
	end

	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		User_TalkChannel2005(tBossmonth_Text[41])
		return
	end

	for i =1,3 do
		if not Item_ChkItem(tBossmonth_Cont["Material"][nItemId][i]) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end
	end

	if not Item_ChkMulItem(tBossmonth_Cont["Material"][nItemId][4],tBossmonth_Cont["Material"][nItemId][4],5) then
		User_TalkChannel2005(tBossmonth_Text[nItemId][1])
		return
	end

	if Item_DelItem(nItemId) then
		for j =1,3 do
			if not Item_DelItem(tBossmonth_Cont["Material"][nItemId][j]) then
				return
			end
		end

		if not Item_DelMulItem(tBossmonth_Cont["Material"][nItemId][4],tBossmonth_Cont["Material"][nItemId][4],5) then
			return
		end
	end

		if Sys_Random(1,3) then
			Item_AddItem(tBossmonth_Cont["Material"][nItemId]["AwardItem"])
			User_TalkChannel2005(tBossmonth_Text[nItemId][4])
			User_EffectAdd("self","zf2-e280")
			Sys_SaveActionFestivalLog(tBossmonth_Cont["Material"][nItemId]["Log"])
		else
			local nLevel = Get_UserLevel()
			if nLevel < 140 then
				User_AddExpTime(tBossmonth_Cont["Material"][nItemId]["AddExpTime"])
				User_TalkChannel2005(tBossmonth_Text[nItemId][2])
				Sys_SaveActionFestivalLog(tBossmonth_Cont["Material"][nItemId]["Log1"])
			else
				User_AddCultivation(tBossmonth_Cont["Material"][nItemId]["AddCultivation"])
				User_TalkChannel2005(tBossmonth_Text[nItemId][3])
				Sys_SaveActionFestivalLog(tBossmonth_Cont["Material"][nItemId]["Log2"])
			end
				User_EffectAdd("self","angelwing")
		end	

end

--冰冻之心，冰封之心，洗赠，光效材料
function Bossmonth_Item_3007199()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_AddStrengthValue(tBossmonth_Cont[nItemId]["strengthvalue"])
			User_TalkChannel2005(tBossmonth_Text[nItemId]["strengthvalue"])
			return
		end
	else
		if nItemId == 3007199 then
			Sys_DialogText(tBossmonth_Text[nItemId][7])
			Sys_DialogOption(tBossmonth_Text[nItemId][8],"</F>Bossmonth_Item_3007199_1</N>"..nItemId) 
			Sys_DialogOption(tBossmonth_Text[nItemId][9],"</F>Bossmonth_Item_3007199_2</N>"..nItemId) 
			Sys_DialogEnd()
		end

		if nItemId == 3007200 then
			Bossmonth_Item_3007199_1(nItemId)
		end

		if nItemId == 3007211 or nItemId == 3007214 then
			User_TalkChannel2005(tBossmonth_Text[nItemId]["Text"])
		end
	end

end

--直接研究
function Bossmonth_Item_3007199_1(nItemId)
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tBossmonth_Text[41])
		return
	end
	
	if not Item_ChkItem(nItemId) then
		return
	end	

	if Item_DelItem(nItemId) then
		local flat,tNum = Probabil_RandomAward(tBossmonth_Lottery_random[nItemId]["Reward"],1)  
		local nItemId_1 = tNum[1]["tAward"][1]["Item_1"]
		local nAttr = tNum[1]["tAward"][1]["Attr"]
		local sItemName = Get_ItemtypeName(nItemId_1)
		local sText = string.format(tBossmonth_Text[nItemId][6],nAttr,sItemName)
		local sLog = tNum[1]["tAward"][1]["Log"]
		local sLog1 = string.format(tBossmonth_log[5],nItemId,1)
		Item_AddItem(nItemId_1,0,nAttr)
		User_TalkChannel2005(sText)
		User_EffectAdd("self","angelwing")
		Sys_SaveActionFestivalLog(sLog1)
		Sys_SaveActionFestivalLog(sLog)
	end
end

--6个碎片合成1个冰封之心
function Bossmonth_Item_3007199_2(nItemId)
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tBossmonth_Text[41])
		return
	end

	if not Item_ChkMulItem(nItemId,nItemId,6) then
		User_TalkChannel2005(tBossmonth_Text[nItemId][10])
		return
	end

	if Item_DelMulItem(nItemId,nItemId,6) then
		Item_AddItem(3007200)
		User_TalkChannel2005(tBossmonth_Text[nItemId][11])
		return
	end

end

--冰雪奇缘外套礼包
function Bossmonth_Item_3007201()
	local nItemId = Get_ItemType()
	if tBossmonth_Text[nItemId][1] ~= nil then
		Sys_DialogText(tBossmonth_Text[nItemId][1])
		Sys_DialogText(tBossmonth_Text[nItemId][2])
		Sys_DialogOption(tBossmonth_Text[20],"</F>Bossmonth_Item_3007201_1</N>"..nItemId) 
		Sys_DialogEnd()
	else
		Bossmonth_Item_3007201_1(nItemId)
	end	
end


function Bossmonth_Item_3007201_1(nItemId)
	if Item_DelItem(nItemId) then
		Item_AddNewItem(tBossmonth_Cont[nItemId]["AwardItem"],tBossmonth_Cont[nItemId]["Attr"])
		User_TalkChannel2005(tBossmonth_Text[nItemId]["AwardItem"])
		User_EffectAdd("self",tBossmonth_Cont[nItemId]["Effect"])
		Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log"])
		return
	end
end

--冰雪奇缘外套礼包碎片，洗赠碎片，光效碎片
function Bossmonth_Item_3007205()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			if tBossmonth_Cont[nItemId]["strengthvalue"] ~= nil then
				User_AddStrengthValue(tBossmonth_Cont[nItemId]["strengthvalue"])
			end
				User_TalkChannel2005(tBossmonth_Text[nItemId]["strengthvalue"])
		end
	else
		Sys_DialogText(tBossmonth_Text[nItemId][1])
		Sys_DialogText(tBossmonth_Text[nItemId][2])
		Sys_DialogOption(tBossmonth_Text[nItemId][3],"</F>Bossmonth_Item_3007205_1</N>1</N>"..nItemId) 
		Sys_DialogOption(tBossmonth_Text[nItemId][4],"</F>Bossmonth_Item_3007205_1</N>2</N>"..nItemId) 
		Sys_DialogEnd()
	end

end


function Bossmonth_Item_3007205_1(nOption,nItemId)
	if not User_CheckLeftSpace(tBossmonth_Cont["Space"]) then
		User_TalkChannel2005(tBossmonth_Text[41])
		return
	end

	local nItemId_1 = tBossmonth_Cont[nItemId]["AwardItem"]
	local sAttr = tBossmonth_Cont[nItemId]["Attr"]
	if nOption == 1 then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			if Sys_Random(tBossmonth_Cont[nItemId]["Random_1"],tBossmonth_Cont[nItemId]["Random"]) then
				Item_AddNewItem(nItemId_1,sAttr)
				User_TalkChannel2005(tBossmonth_Text[nItemId][5])
				User_EffectAdd("self","zf2-e280")
				Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log"])
				if tBossmonth_Cont[nItemId]["EmoneyLog"]~= nil then
					Sys_SaveEmoneyBuy(tBossmonth_Cont[nItemId]["EmoneyLog"])
				end

			else
				if tBossmonth_Cont[nItemId]["strengthvalue_1"]~= nil then
					User_AddStrengthValue(tBossmonth_Cont[nItemId]["strengthvalue_1"])
					User_TalkChannel2005(tBossmonth_Text[nItemId]["strengthvalue_1"])
					User_EffectAdd("self","disappear")
					Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log4"])
				end

				if tBossmonth_Cont[nItemId]["AddExpTime"]~= nil then
					local nLevel = Get_UserLevel()
						if nLevel < 140 then
							User_AddExpTime(tBossmonth_Cont[nItemId]["AddExpTime"])
							User_TalkChannel2005(tBossmonth_Text[nItemId][6][1])
							User_EffectAdd("self","angelwing")
							Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log1"])
						else
							User_AddCultivation(tBossmonth_Cont[nItemId]["AddCultivation"])
							User_TalkChannel2005(tBossmonth_Text[nItemId][6][2])
							User_EffectAdd("self","angelwing")
							Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log2"])
						end

				end
			end	
		else
					User_TalkChannel2005(tBossmonth_Text[nItemId][7])
		end
	end

	if nOption == 2 then
		if Item_ChkMulItem(nItemId,nItemId,tBossmonth_Cont[nItemId]["Num"]) and Item_DelMulItem(nItemId,nItemId,tBossmonth_Cont[nItemId]["Num"]) then
			Item_AddNewItem(nItemId_1,sAttr)
			User_TalkChannel2005(tBossmonth_Text[nItemId][5])
			User_EffectAdd("self","zf2-e280")
			Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log3"])
			if tBossmonth_Cont[nItemId]["EmoneyLog"]~= nil then
				Sys_SaveEmoneyBuy(tBossmonth_Cont[nItemId]["EmoneyLog"])
			end

		else
			User_TalkChannel2005(tBossmonth_Text[nItemId][7])
		end
	end

end

--洗赠道具，光效道具
function Bossmonth_Item_3007207()
	local nItemId = Get_ItemType()
	for i =1,2 do
		if not Item_ChkMulItem(tBossmonth_Cont[nItemId][i]["Id"],tBossmonth_Cont[nItemId][i]["Id"],tBossmonth_Cont[nItemId][i]["Num"],tBossmonth_Cont[nItemId][i]["Attr"]) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][2])
			return
		end
	end

	if Item_DelItem(nItemId) then
		for j =1,2 do
			if not Item_DelMulItem(tBossmonth_Cont[nItemId][j]["Id"],tBossmonth_Cont[nItemId][j]["Id"],tBossmonth_Cont[nItemId][j]["Num"],tBossmonth_Cont[nItemId][j]["Attr"]) then
				return
			end
		end

		Item_AddNewItem(tBossmonth_Cont[nItemId]["AwardItem"],tBossmonth_Cont[nItemId]["Attr"])
		User_TalkChannel2005(tBossmonth_Text[nItemId][3])
		User_EffectAdd("self","accession")
		Sys_SaveActionFestivalLog(tBossmonth_Cont[nItemId]["Log"])
		Sys_SaveEmoneyBuy(tBossmonth_Cont[nItemId]["EmoneyLog"])
	end

end

--配方重修秘诀
function Bossmonth_Item_3007220()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end
	end

	if Task_ChkStcValue(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],">",0) then
		if Item_DelItem(nItemId) then
			Task_AddStatistic(tBossmonth_Stc[4]["EventType"],tBossmonth_Stc[4]["DataType"],-1,1,0)
			User_TalkChannel2005(tBossmonth_Text[nItemId][2])
		end
	else
		User_TalkChannel2005(tBossmonth_Text[nItemId][3])
	end

end

--配方重修秘诀残页
function Bossmonth_Item_3007221()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		if Item_DelItem(nItemId) then
			User_TalkChannel2005(tBossmonth_Text[nItemId][1])
			return
		end
	end

	if not Item_ChkMulItem(nItemId,nItemId,7) then
		User_TalkChannel2005(tBossmonth_Text[nItemId][2])
		return
	end

	if Item_DelMulItem(nItemId,nItemId,7) then
		Item_AddItem(3007220)
		User_TalkChannel2005(tBossmonth_Text[nItemId][3])
	end

end


--怪物掉落
function Bossmonth_Monster(nMonsterTypeId)
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		return
	end

	local Area = 0
	for j = 1,5 do
		for _,v in pairs(tBossmonth_Monster[j]) do
			if nMonsterTypeId == v then
				Area = j
				break
			end
		end
	end

	local flat,tNum = Probabil_RandomAward(tBossmonth_Monster_random[Area]["Reward"],1)  
	local nItemId = tNum[1]["tAward"][1]["Item_1"]
	local nSysDynaGlobal = tNum[1]["tAward"][1]["SysDynaGlobal"]
	local nSysDynaGlobalLimit = tNum[1]["tAward"][1]["SysDynaGlobalLimit"] 

	if Area == 5 then														--判断是否是boss怪
		for i = 1,3 do														--额外掉落3个通用材料
			Monster_SysDropItem(3007186)
		end
	end

	if nSysDynaGlobal~= nil then																				--判断是否是限量物品
		local nSysDynaGlobalData = Get_SysDynaGlobalData1(nSysDynaGlobal)
		if nSysDynaGlobalData >= nSysDynaGlobalLimit then
			local nNum = math.random(1,3)
				Monster_SysDropItem(tBossmonth_Cont["Drop"][nNum])
				return
		else
			nSysDynaGlobalData = nSysDynaGlobalData + 1  -- 未超出限量加掩码和动态存储表
			Sys_SetSynaGlobalData1(nSysDynaGlobal,nSysDynaGlobalData)
		end	
	end

	if nItemId~= nil then  -- 掉落物品
		local sLog = string.format(tBossmonth_log["DropLog"],nItemId)
		Monster_SysDropItem(nItemId)
		Sys_SaveActionFestivalLog(sLog)
	end

end

--时间检测，清动态存储表
function Bossmonth_Monster_Timechk()
	if not Sys_ChkFullTime(tBossmonth_Time["Nowtime"]) then
		return
	end

	for i = 50953,50957 do
		Sys_ResetAllSynaGlobalData(i)
	end
	
end

--怪物掉落
-- 第三片区
-- 10	须猕猴	9593310
tMonster[10] = tMonster[10] or {}
tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
table.insert(tMonster[10]["tFunction"],Bossmonth_Monster)

-- 11	巨臂猿	9593320
tMonster[11] = tMonster[11] or {}
tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
table.insert(tMonster[11]["tFunction"],Bossmonth_Monster)

-- 12	天雷巨猿	9593330
tMonster[12] = tMonster[12] or {}
tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
table.insert(tMonster[12]["tFunction"],Bossmonth_Monster)

-- 13	蛇人	9593340
tMonster[13] = tMonster[13] or {}
tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
table.insert(tMonster[13]["tFunction"],Bossmonth_Monster)


-- 第四片区
-- 14	沙怪	9593350
tMonster[14] = tMonster[14] or {}
tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
table.insert(tMonster[14]["tFunction"],Bossmonth_Monster)

-- 15	锤山怪	9593360
tMonster[15] = tMonster[15] or {}
tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
table.insert(tMonster[15]["tFunction"],Bossmonth_Monster)

-- 16	巨石怪	9593370
tMonster[16] = tMonster[16] or {}
tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
table.insert(tMonster[16]["tFunction"],Bossmonth_Monster)

-- 17	鬼刃	9593380
tMonster[17] = tMonster[17] or {}
tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
table.insert(tMonster[17]["tFunction"],Bossmonth_Monster)

-- 73	砾沙怪	9593390
tMonster[73] = tMonster[73] or {}
tMonster[73]["tFunction"] = tMonster[73]["tFunction"] or {}
table.insert(tMonster[73]["tFunction"],Bossmonth_Monster)


-- 第五片区
-- 18	金臂鸟人	4081200
tMonster[18] = tMonster[18] or {}
tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
table.insert(tMonster[18]["tFunction"],Bossmonth_Monster)

-- 19	银羽鹰王	4081254
tMonster[19] = tMonster[19] or {}
tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
table.insert(tMonster[19]["tFunction"],Bossmonth_Monster)

-- 55	湖岛强匪	4081258
tMonster[55] = tMonster[55] or {}
tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
table.insert(tMonster[55]["tFunction"],Bossmonth_Monster)

-- 78	银羽鹰魔	4081255
tMonster[78] = tMonster[78] or {}
tMonster[78]["tFunction"] = tMonster[78]["tFunction"] or {}
table.insert(tMonster[78]["tFunction"],Bossmonth_Monster)

-- 79	湖岛悍匪	4081259
tMonster[79] = tMonster[79] or {}
tMonster[79]["tFunction"] = tMonster[79]["tFunction"] or {}
table.insert(tMonster[79]["tFunction"],Bossmonth_Monster)

-- 84	匪兵	9593450
tMonster[84] = tMonster[84] or {}
tMonster[84]["tFunction"] = tMonster[84]["tFunction"] or {}
table.insert(tMonster[84]["tFunction"],Bossmonth_Monster)

-- 第六片区
-- 20	土墓蝠	9593460
tMonster[20] = tMonster[20] or {}
tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
table.insert(tMonster[20]["tFunction"],Bossmonth_Monster)

-- 56	嗜血蝙蝠	9593470
tMonster[56] = tMonster[56] or {}
tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
table.insert(tMonster[56]["tFunction"],Bossmonth_Monster)

-- 57	牛怪	9593480
tMonster[57] = tMonster[57] or {}
tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
table.insert(tMonster[57]["tFunction"],Bossmonth_Monster)

-- 58	血影红魔	9593490
tMonster[58] = tMonster[58] or {}
tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
table.insert(tMonster[58]["tFunction"],Bossmonth_Monster)


-- 第七片区
-- 2411	冰凌腾蛇	9979200
tMonster[2411] = tMonster[2411] or {}
tMonster[2411]["tFunction"] = tMonster[2411]["tFunction"] or {}
table.insert(tMonster[2411]["tFunction"],Bossmonth_Monster)

-- 2416	冰煞邪刀	9979210
tMonster[2416] = tMonster[2416] or {}
tMonster[2416]["tFunction"] = tMonster[2416]["tFunction"] or {}
table.insert(tMonster[2416]["tFunction"],Bossmonth_Monster)


-- 第八片区
-- 2686	深海亡魂	98054381
tMonster[2686] = tMonster[2686] or {}
tMonster[2686]["tFunction"] = tMonster[2686]["tFunction"] or {}
table.insert(tMonster[2686]["tFunction"],Bossmonth_Monster)

-- 2687	深海魔魂	98054382
tMonster[2687] = tMonster[2687] or {}
tMonster[2687]["tFunction"] = tMonster[2687]["tFunction"] or {}
table.insert(tMonster[2687]["tFunction"],Bossmonth_Monster)

-- 冰封boss怪
tMonster[7862] = tMonster[7862] or {}
tMonster[7862]["tFunction"] = tMonster[7862]["tFunction"] or {}
table.insert(tMonster[7862]["tFunction"],Bossmonth_Monster)

--时间检测
tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
table.insert(tOntimerMin_HM[0000],Bossmonth_Monster_Timechk)

